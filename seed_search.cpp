
#include "seed_search.h"

#include <array>
#include <algorithm>
#include <thread>
#include <iostream>

#include "java_random.h"

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

struct ThreadData {
    const SeedMatcher *m;
    std::int64_t startSeed;
    std::int64_t count;
    int threadCount;
    int threadId;
    std::int64_t *foundOutCount;
    std::vector<std::int64_t> *foundOutRet;

    ThreadData(const SeedMatcher *m, int64_t startSeed, int64_t count, int threadCount, int threadId,
               int64_t *foundOutCount) : m(m), startSeed(startSeed), count(count), threadCount(threadCount),
                                         threadId(threadId), foundOutCount(foundOutCount) {}

    ThreadData(const SeedMatcher *m, int64_t startSeed, int64_t count, int threadCount, int threadId,
               std::vector<int64_t> *foundOutRet) : m(m), startSeed(startSeed), count(count), threadCount(threadCount),
                                                    threadId(threadId), foundOutRet(foundOutRet) {}
};


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

void searchMtHelper(ThreadData d) {
    for (std::int64_t seed = d.startSeed+d.threadId; seed < d.startSeed+d.count; seed += d.threadCount) {
        if (d.m->match(seed)) {
            d.foundOutRet->push_back(seed);
            std::cout << SeedHelper::getString(seed) << std::endl;
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
            break;
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
