
#include "seed_search.h"

#include <array>
#include <algorithm>
#include <thread>
#include <iostream>
#include <chrono>

#include "java_random.h"
#include "seed_search_fast.h"

using namespace sts;

std::vector<std::int64_t> SeedSearcher::search(std::int64_t startSeed, std::int64_t count) const {
    std::vector<std::int64_t> foundSeeds;
    for (std::int64_t seed = startSeed; seed < startSeed+count; ++seed) {
        if (matcher.match(seed)) {
            foundSeeds.push_back(seed);
        }
    }
    return foundSeeds;
}

std::int64_t SeedSearcher::countMatching(std::int64_t startSeed, std::int64_t count) const {
    std::int64_t found = 0;
    for (std::int64_t seed = startSeed; seed < startSeed+count; ++seed) {
        if (matcher.match(seed)) {
            ++found;
        }
    }
    return found;
}

void countMatchingMtHelper(ThreadData d) {
    for (std::int64_t seed = d.startSeed+d.threadId; seed < d.startSeed+d.count; seed += d.threadCount) {
        if (d.m->match(seed)) {
            ++*d.foundOutCount;
        }
    }
}

std::int64_t SeedSearcher::countMatchingMt(std::int64_t startSeed, std::int64_t count, int threadCount) const {

    std::thread *threads[threadCount];
    std::int64_t results[threadCount];

    for (int tid = 0; tid < threadCount; ++tid) {
        results[tid] = 0;
        ThreadData data(&matcher, startSeed, count, threadCount, tid, &results[tid]);
        threads[tid] = new std::thread(countMatchingMtHelper, data);
    }

    std::int64_t total = 0;
    for (int tid = 0; tid < threadCount; ++tid) {
        threads[tid]->join();
        delete threads[tid];
        total += results[tid];
    }

    return total;
}

int getMaxCount(long seed) {
    sts::Random cardRandomRng(seed);
    int sameLastCardCount = 1;
    int maxSameLastCardCount = 1;
    int lastIdx = cardRandomRng.random(70);
    for (int i = 1; i < 8; i++) {
        int idx = cardRandomRng.random(70);
        if (lastIdx == idx) {
            sameLastCardCount++;
            if (sameLastCardCount > maxSameLastCardCount) {
                maxSameLastCardCount = sameLastCardCount;
            }
        } else {
            lastIdx = idx;
            sameLastCardCount = 0;
        }
    }
    return maxSameLastCardCount;
}

void printSeedFind(std::int64_t seed, CharacterClass characterClass) {
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    auto seedStr = sts::SeedHelper::getString(seed);
    auto res = analyzePandorasBoxRewards(seed, characterClass);
    std::cout << "seed " << seedStr << " " << seed << " " << res.name << " " << res.count <<  " " << std::ctime(&end_time);
    std::cout.flush();
}

void searchMtHelper(ThreadData d) {
    for (std::int64_t seed = d.startSeed+d.threadId; seed < d.startSeed+d.count; seed += d.threadCount) {
        if (d.m->match(seed)) {
            d.foundOutRet->push_back(seed);
            printSeedFind(seed, CharacterClass::DEFECT);
        }
    }
}

std::vector<std::int64_t> SeedSearcher::searchMt(std::int64_t startSeed, std::int64_t count, int threadCount) const {
    std::thread *threads[threadCount];
    std::vector<std::int64_t> results[threadCount];

    for (int tid = 0; tid < threadCount; ++tid) {
        ThreadData data(&matcher, startSeed, count, threadCount, tid, &results[tid]);
        threads[tid] = new std::thread(searchMtHelper, data);
    }

    std::vector<std::int64_t> combined;
    for (int tid = 0; tid < threadCount; ++tid) {
        threads[tid]->join();
        combined.insert(combined.end(), results[tid].begin(), results[tid].end());
        delete threads[tid];
    }

    std::sort(combined.begin(), combined.end());
    return combined;
}

std::string SeedSearcher::getFirstMatching(std::int64_t startSeed, std::int64_t maxCount) const {
    for (std::int64_t seed = startSeed; seed < startSeed+maxCount; ++seed) {
        if (matcher.match(seed)) {
            return SeedHelper::getString(seed);
        }
    }
    return "found no seeds";
}

void SeedMatcher::addPredicate(SeedPredicate p) {
    predicates.emplace_back(1, p);
}

void SeedMatcher::addNeowPredicate(NeowPredicate p) {
    predicates.emplace_back(0, [=](long seed) {
            return p(Neow::generateRewards(seed));
        }
    );
}

void SeedMatcher::addPandoraPredicate(CharacterClass character, PandoraPredicate p) {
    switch (character) {
        case CharacterClass::IRONCLAD: {
            predicates.emplace_back(1, [=](std::int64_t seed) {
                std::array<Card, 10> cards;
                sts::Random cardRandomRng(seed);
                for (int i = 0; i < 9; i++) {
                    cards[i] = Ironclad::cardPool[cardRandomRng.random(71)];
                }
                return p(cards);
            });
            break;
        }

        case CharacterClass::SILENT:
            break;
        case CharacterClass::DEFECT:
        {
            predicates.emplace_back(1, [=](std::int64_t seed) {
                std::array<Card, 10> cards;
                sts::Random cardRandomRng(seed);
                for (int i = 0; i < 9; i++) {
                    cards[i] = Defect::cardPool[cardRandomRng.random(70)];
                }
                return p(cards);
            });
            break;
        }
        case CharacterClass::WATCHER:
            break;
    }
}

bool SeedMatcher::match(std::int64_t seed) const{
    return std::all_of(predicates.begin(), predicates.end(), [seed](auto &p) { return p.predicate(seed); } );
}

void SeedMatcher::mustHaveCallingBellRewards(Relic common, Relic uncommon, Relic rare) {
    addPredicate([=](long seed) {

        sts::Random relicRng = sts::Random(seed);

        java::Random commonRandom(relicRng.randomLong());
        java::Random uncommonRandom(relicRng.randomLong());
        java::Random rareRandom(relicRng.randomLong());
        relicRng.randomLong();
        java::Random bossRandom(relicRng.randomLong());

        auto boss = sts::Ironclad::bossRelicPool;
        java::Collections::shuffle( boss.begin(), boss.end(), bossRandom);
        if (boss[0] != sts::CALLING_BELL) {
            return false;
        }

        auto c = sts::Ironclad::commonRelicPool;
        java::Collections::shuffle( c.begin(), c.end(), commonRandom);
        if (c[0] != common) {
            return false;
        }

        auto uc = sts::Ironclad::uncommonRelicPool;
        java::Collections::shuffle( uc.begin(), uc.end(), uncommonRandom);
        if (uc[0] != uncommon) {
            return false;
        }

        auto r = sts::Ironclad::rareRelicPool;
        java::Collections::shuffle( r.begin(), r.end(), rareRandom);
        if (r[0] != rare) {
            return false;
        }

        return true;
    });
}

void SeedMatcher::mustGetBossRelicFromSwap(Relic bossRelic) {
    addPredicate([=](std::int64_t seed) {
        auto relicRng = sts::Random(seed);
        relicRng.randomLong();
        relicRng.randomLong();
        relicRng.randomLong();
        relicRng.randomLong();
        java::Random bossRandom(relicRng.randomLong());

        auto boss = sts::Ironclad::bossRelicPool;
        java::Collections::shuffle( boss.begin(), boss.end(), bossRandom);
        return boss[0] == bossRelic;
    });
}

Card getCardFromPool(int idx, CharacterClass characterClass) {
    switch (characterClass) {
        case CharacterClass::IRONCLAD:
            return Ironclad::cardPool[idx];

        case CharacterClass::SILENT:
            return Silent::cardPool[idx];

        case CharacterClass::DEFECT:
            return Defect::cardPool[idx];

        case CharacterClass::WATCHER:
            return Watcher::cardPool[idx];
    }
}

seed_result analyzePandorasBoxRewards(std::int64_t seed, CharacterClass characterClass) {
    int numTransformedCards;
    int cardPoolSize;
    switch (characterClass) {
        case CharacterClass::IRONCLAD:
            cardPoolSize = Ironclad::cardPool.size();
            numTransformedCards = 9;
            break;
        case CharacterClass::SILENT:
            cardPoolSize = Silent::cardPool.size();
            numTransformedCards = 10;
            break;
        case CharacterClass::DEFECT:
            cardPoolSize = Defect::cardPool.size();
            numTransformedCards = 8;
            break;
        case CharacterClass::WATCHER:
            cardPoolSize = Watcher::cardPool.size();
            numTransformedCards = 8;
            break;
    }

    sts::Random cardRandomRng(seed);

    sts::Card cards[8];

    int sameLastCardCount = 1;
    int maxSameLastCardCount = 1;

    cards[0] = getCard(cardRandomRng.random(cardPoolSize), characterClass);
    sts::Card maxCard = cards[0];

    for (int i = 1; i < numTransformedCards; i++) {
        cards[i] = getCard(cardRandomRng.random(cardPoolSize), characterClass);
        if (cards[i-1] == cards[i]) {
            sameLastCardCount++;
            if (sameLastCardCount > maxSameLastCardCount) {
                maxSameLastCardCount = sameLastCardCount;
                maxCard = cards[i];
            }
        } else {
            sameLastCardCount = 1;
        }

    }

    seed_result ret;
    ret.count = maxSameLastCardCount;
    ret.name = sts::cardNames[(int)maxCard];
    return ret;
}




inline bool testSeedForPandorasRelic(std::int64_t seed) {
    auto relicRng = sts::Random(seed);
    relicRng.randomLong();
    relicRng.randomLong();
    relicRng.randomLong();
    relicRng.randomLong();
    java::Random bossRandom(relicRng.randomLong());

    auto boss = sts::Defect::bossRelicPool;
    java::Collections::shuffle( boss.begin(), boss.end(), bossRandom);
    return boss[0] == sts::PANDORAS_BOX;
}

inline bool testSeed(std::int64_t seed) {
    sts::fast::Random rand(seed);

    // 0
    auto num = rand.random(70);

    // 1
    if (rand.random(70) != num) {
        return false;
    }
    // 2
    if (rand.random(70) != num) {
        return false;
    }
    // 3
    if (rand.random(70) != num) {
        return false;
    }
    // 4
    if (rand.random(70) != num) {
        return false;
    }
    // 5
    if (rand.random(70) != num) {
        return false;
    }
    // 6
    if (rand.random(70) != num) {
        return false;
    }
    // 7
    if (rand.random(70) != num) {
        return false;
    }

    return testSeedForPandorasRelic(seed);
}

std::vector<std::int64_t> testPandoraSeedsForDefectWatcherMt(ThreadData data) {
    std::int64_t start = 300000000000000LL;
    auto count = static_cast<std::int64_t>(1e9);

    std::vector<std::int64_t>
    for (std::int64_t seed = start; seed < start+count; seed++) {
        if (testSeed(seed)) {

        }
    }
}







































