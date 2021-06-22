
#include "seed_search.h"

#include <array>
#include <algorithm>
#include <thread>
#include <iostream>
#include <chrono>
#include <fstream>
#include <random>

#include "java_random.h"
#include "seed_search_fast.h"
#include "sts_map.h"
#include "sts_events.h"


using namespace sts;

std::string getTime() {
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string timeStr(std::ctime(&time));
    timeStr.erase(timeStr.end()-1, timeStr.end());
    return timeStr;
}

inline bool testSeedForPandorasRelic(std::int64_t seed, CharacterClass characterClass) {
    Random relicRng(seed);
    relicRng.randomLong();
    relicRng.randomLong();
    relicRng.randomLong();
    relicRng.randomLong();
    java::Random bossRandom(relicRng.randomLong());

    Relic bossRelic;
    switch (characterClass) {
        case CharacterClass::IRONCLAD: {
            auto boss = sts::Ironclad::bossRelicPool;
            java::Collections::shuffle( boss.begin(), boss.end(), bossRandom);
            bossRelic = boss[0];
            break;
        }

        case CharacterClass::SILENT: {
            auto boss = sts::Silent::bossRelicPool;
            java::Collections::shuffle( boss.begin(), boss.end(), bossRandom);
            bossRelic = boss[0];
            break;
        }

        case CharacterClass::DEFECT: {
            auto boss = sts::Defect::bossRelicPool;
            java::Collections::shuffle( boss.begin(), boss.end(), bossRandom);
            bossRelic = boss[0];
            break;
        }

        case CharacterClass::WATCHER: {
            auto boss = sts::Watcher::bossRelicPool;
            java::Collections::shuffle( boss.begin(), boss.end(), bossRandom);
            bossRelic = boss[0];
            break;
        }
    }

    return bossRelic == PANDORAS_BOX;
}

static std::ofstream *fileOut;

Card getCard(int idx, CharacterClass characterClass) {
    switch (characterClass) {
        case CharacterClass::IRONCLAD:
            return Ironclad::cardPool[idx];

        case CharacterClass::SILENT:
            return Silent::cardPool[idx];

        case CharacterClass::DEFECT:
            return Defect::cardPool[idx];

        case CharacterClass::WATCHER:
            return Watcher::cardPool[idx];

        default:
            return Card::ACCURACY;
    }
}

PandorasBoxRewardResult analyzePandorasBoxRewards(std::int64_t seed, CharacterClass c) {
    static int pandoraCardsTransformed[4] = {9,10,8,8};

    int numTransformedCards = pandoraCardsTransformed[static_cast<int>(c)];
    int cardPoolSize = CardPools::getCardPoolSizeForClass(c);
    const Card *cardPool = CardPools::getCardPoolForClass(c);

    sts::Random cardRandomRng(seed);

    Card cards[10];

    for (int i = 0; i < numTransformedCards; ++i) {
        cards[i] = cardPool[cardRandomRng.random(cardPoolSize-1)];
    }

    std::sort(cards, cards+numTransformedCards);

    int maxCount = 0;
    sts::Card maxCard;

    Card lastCard = cards[0];
    int lastCount = 1;
    for (int i = 1; i < numTransformedCards; ++i) {
        Card card = cards[i];
        if (card == lastCard) {
            lastCount++;
        } else {
            if (lastCount > maxCount) {
                maxCard = card;
                maxCount = lastCount;
            }
            lastCard = card;
            lastCount = 1;
        }

    }
    if (lastCount > maxCount) {
        maxCard = lastCard;
        maxCount = lastCount;
    }

    PandorasBoxRewardResult ret;
    ret.count = maxCount;
    ret.name = sts::cardNames[(int)maxCard];
    return ret;
}




inline bool testSeedSDW(std::int64_t seed) {
    sts::Random rand(seed);
    const int cardPoolSizeMinusOne = Defect::cardPool.size()-1;

    auto num = rand.random(cardPoolSizeMinusOne);
    int strikeCount = 1;
    for (int i = 0; i < 6; ++i) {
        if (rand.random(cardPoolSizeMinusOne) != num && !strikeCount--) {
            return false;
        }
    }
    return testSeedForPandorasRelic(seed, CharacterClass::DEFECT)
           || testSeedForPandorasRelic(seed, CharacterClass::WATCHER);
}

inline bool testSeedIronclad(std::int64_t seed) {
    sts::Random rand(seed);
    const int cardPoolSizeMinusOne = Ironclad::cardPool.size()-1;

    auto num = rand.random(cardPoolSizeMinusOne);
    int strikeCount = 1;
    for (int i = 0; i < 6; ++i) {
        if (rand.random(cardPoolSizeMinusOne) != num && !strikeCount--) {
            return false;
        }
    }
    return true;
}


void logSeed(std::int64_t seed) {
    std::string seedStr = SeedHelper::getString(seed);
    auto time = getTime();
    if (testSeedSDW(seed)) {
        if (testSeedForPandorasRelic(seed, CharacterClass::DEFECT)) {
            auto res = analyzePandorasBoxRewards(seed, CharacterClass::DEFECT);
            std::cout << time << " seed " << seedStr << " " << seed << " " << res.name << " " << res.count << std::endl;

            auto res2 = analyzePandorasBoxRewards(seed, CharacterClass::SILENT);
            std::cout << time << " seed " << seedStr << " " << seed << " " << res2.name << " " << res2.count << std::endl;
        }

        if (testSeedForPandorasRelic(seed, CharacterClass::WATCHER)) {
            auto res = analyzePandorasBoxRewards(seed, CharacterClass::WATCHER);
            std::cout << time << " seed " << seedStr << " " << seed << " " << res.name << " " << res.count << std::endl;
        }

    }
    if (testSeedIronclad(seed)) {
        auto res = analyzePandorasBoxRewards(seed, CharacterClass::IRONCLAD);
        std::cout << time << " seed " << seedStr << " " << seed << " " << res.name << " " << res.count << std::endl;
    }
}


inline bool testCandidateSeed(std::int64_t seed) {
    return testSeedSDW(seed) || testSeedIronclad(seed);
}


void testPandoraSeedsForDefectWatcherMtHelper(ThreadData data) {
    for (std::int64_t seed = data.startSeed+data.threadId; seed < data.endSeed; seed += data.threadCount) {
        if (testCandidateSeed(seed)) {
//            logSeed(seed);
            data.foundVec->push_back(seed);
        }
    }
}


std::vector<int64_t> sts::testPandorasForDefectWatcherMt(std::int64_t startSeed, std::int64_t endSeed, int threadCount) {
    std::thread *threads[threadCount];
    std::vector<std::int64_t> results[threadCount];

    for (int tid = 0; tid < threadCount; ++tid) {
        ThreadData data(startSeed, endSeed, threadCount, tid, &results[tid]);
        threads[tid] = new std::thread(testPandoraSeedsForDefectWatcherMtHelper, data);
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

void sts::runSearch(SearchConfig config) {
//    if (config.startSeed == -1) {
//        time_t t;
//        srand((unsigned) time(&t));
//        config.startSeed = static_cast<std::int64_t>(rand()%1000000)*config.blockAmount;
//    }

//    fileOut = new std::ofstream(config.resultsFile, std::ios_base::app);

//    while (true) {
    std::int64_t endSeed = config.startSeed+config.blockAmount;
    std::string time = getTime();
    std::cout << time << " searching seeds from " << config.startSeed << "(" << (double)config.startSeed / 1e12 << "T)" << " to " << endSeed << "(" << (double)endSeed/ 1e12 << "T)" << std::endl;
//    *fileOut << time << " searching 50B seeds starting at: " << config.startSeed << "(" << (double)config.startSeed / 1e12 << "T)" << std::endl;

    auto matchedSeedsVec = testPandorasForDefectWatcherMt(config.startSeed, endSeed, config.threads);
    time = getTime();
    std::cout << time << " found " << matchedSeedsVec.size() << " results" << std::endl;
//    *fileOut << time << " found " << matchedSeedsVec.size() << " results" << std::endl;
//    fileOut->flush();
    config.startSeed += config.blockAmount;
//    }
}




void testCandidateSeedsMt(ThreadData data) {
    for (std::int64_t seed = data.startSeed; seed < data.endSeed; seed += data.threadCount) {
        if (testCandidateSeed(seed)) {
//            logSeed(seed);
            data.foundVec->push_back(seed);
        }
    }
}


std::vector<int64_t> testCandidatesMt(const std::vector<candidate> &candidates, int offset, int threadCount) {
    std::thread *threads[threadCount];
    std::vector<std::int64_t> results[threadCount];

    for (int tid = 0; tid < threadCount; ++tid) {
        if (offset+tid >= candidates.size()) {
            break;
        }
        candidate c = candidates[offset+tid];
        ThreadData data(c.start, c.end, c.stride, tid, &results[tid]);
        threads[tid] = new std::thread(testCandidateSeedsMt, data);
    }

    std::vector<std::int64_t> combined;
    for (int tid = 0; tid < threadCount; ++tid) {
        if (offset+tid >= candidates.size()) {
            break;
        }
        threads[tid]->join();
        combined.insert(combined.end(), results[tid].begin(), results[tid].end());
        delete threads[tid];
    }

    std::sort(combined.begin(), combined.end());
    return combined;
}


std::vector<std::int64_t> sts::runSearch2(const std::vector<candidate> &candidates) {
    std::vector<std::int64_t> matchedSeeds;

    int threads = 8;
    int offset = 0;
    while (offset < candidates.size()) {
        std::string time = getTime();
        auto matchedSeedsVec = testCandidatesMt(candidates, offset, threads);
        matchedSeeds.insert(matchedSeeds.end(), matchedSeedsVec.begin(), matchedSeedsVec.end());
        time = getTime();
        std::cout << time << " found " << matchedSeedsVec.size() << " results" << std::endl;
        offset += threads;
    }

    return matchedSeeds;
}


void sts::describeSeeds(const std::vector<std::int64_t> seeds) {

    for (auto seed : seeds) {
        std::string seedStr = SeedHelper::getString(seed);

        if (testSeedIronclad(seed)) {
            if (testSeedForPandorasRelic(seed, CharacterClass::IRONCLAD)) {
                auto res = analyzePandorasBoxRewards(seed, CharacterClass::IRONCLAD);
                std::cout << "Ironclad, " <<  seedStr << ", " << res.name << ", " << res.count << std::endl;
            }

        } else if (testSeedSDW(seed)) {
            if (testSeedForPandorasRelic(seed, CharacterClass::DEFECT)) {
                auto res = analyzePandorasBoxRewards(seed, CharacterClass::DEFECT);
                std::cout << "Defect, " << seedStr << ", " << res.name << ", " << res.count << std::endl;

                auto res2 = analyzePandorasBoxRewards(seed, CharacterClass::SILENT);
                std::cout << "Silent, " << seedStr << ", " << res2.name << ", " << res2.count << std::endl;
            }

            if (testSeedForPandorasRelic(seed, CharacterClass::WATCHER)) {
                auto res = analyzePandorasBoxRewards(seed, CharacterClass::WATCHER);
                std::cout << "Watcher, " <<  seedStr << ", " << res.name << ", " << res.count << std::endl;
            }
        }


    }
}

void findSinglePathSeedsMtHelper(ThreadData data, int length) {
    for (std::int64_t seed = data.startSeed+data.threadId; seed < data.endSeed; seed += data.threadCount) {
        if (testSeedForSinglePath(seed, length)) {
            std::cout << SeedHelper::getString(seed) << std::endl;
            data.foundVec->push_back(seed);
        }
    }

//    for (std::int64_t seed = data.startSeed+data.threadId; seed < data.endSeed; seed += data.threadCount) {
//        if (isForcedMonsterIntoEliteFight(seed)) {
//            std::cout << SeedHelper::getString(seed) << std::endl;
//            data.foundVec->push_back(seed);
//        }
//    }
}

std::vector<std::int64_t> sts::findSinglePathSeedsMt(std::int64_t start, std::int64_t count, int threadCount, int length) {
    std::thread *threads[threadCount];
    std::vector<std::int64_t> results[threadCount];

    for (int tid = 0; tid < threadCount; ++tid) {
        ThreadData data(start, start+count, threadCount, tid, &results[tid]);
        threads[tid] = new std::thread(findSinglePathSeedsMtHelper, data, length);
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


bool sts::validateNeowBossPath(std::int64_t seed, const Path& p) {
    GameState gameState = GameState::createGameState(seed, 0);

//    std::cout << p.toString() << std::endl;

    for (int y = 1; y < 14; y++) {
        gameState.floor = y+1;
        Room room = p.roomAt(y);

        if (room == sts::Room::EVENT) {
            auto res = gameState.getEventRoomEvent();

            if (res == Event::MONSTER) {
                return false;
            } else if (res == Event::SHOP) {

            } else {

            }

        } else {

        }
    }


    return true;
}


bool sts::testSeedForNeowBossEvent(const std::int64_t seed) {
    Map map = Map::fromSeed(seed, 0);

    auto candidatePaths = getPathsMatching(map, [](auto path, auto nextRoom, auto pathLength) {
        return pathLength == 0 || (nextRoom != Room::MONSTER && nextRoom != Room::ELITE);
    });


    return std::any_of(candidatePaths.begin(),candidatePaths.end(),
                       [=](auto p){ return validateNeowBossPath(seed, p);
    });
}


bool sts::testSeedForFruitJuiceNeows(const std::int64_t seed) {
    Random neowRng(seed);
    neowRng.random(0, 5);
    auto reward = static_cast<Neow::Reward>(6 + neowRng.random(0, 4));
    if (reward != Neow::Reward::THREE_SMALL_POTIONS) {
        return false;
    }


    Random potionRng(seed);
    for (int i = 0; i < 3; ++i) {
        bool fruitJuice = potionRng.random(0,32) == 28;
        if(!fruitJuice) {
            return false;
        }
    }

    int potionChance = 40;

    for (int i = 0; i < 2; ++i) {
        int roll = potionRng.random(0,99);
        if (roll < potionChance) {
            potionChance -= 10;
            auto p = returnRandomPotion(potionRng, CharacterClass::IRONCLAD, false);
            if (p != Potion::FRUIT_JUICE) {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;


    return true;
}

bool sts::testSeedForCardReward(std::int64_t seed) {
    GameState gameState = GameState::createGameState(seed, 0);
    gameState.cardRng = Random(seed);
    gameState.characterClass = CharacterClass::WATCHER;
    auto reward = gameState.getCardReward();

    bool containFlex = false;
    bool containLimitBreak = false;
    for (int i  = 0; i < 3; ++i) {
        if (reward.cards[i] == Card::WALLOP) {
            containFlex = true;
        } else if (reward.cards[i] == Card::TALK_TO_THE_HAND) {
            containLimitBreak = true;
        }
    }
    return containFlex && containLimitBreak;
}


void testSeedsMtHelper(ThreadData d) {
    for (std::int64_t seed = d.startSeed+d.threadId; seed < d.endSeed; seed += d.threadCount) {
        if (d.predicate(seed)) {
            if (d.printWhenFound) {
                std::cout << SeedHelper::getString(seed) << std::endl;
            }
            d.foundVec->push_back(seed);
        }
    }
}

std::vector<std::int64_t> sts::testSeedsMt(std::int64_t start, std::int64_t count, int threadCount, const SeedPredicate& predicate, bool printWhenFound, bool logStats) {
    Timer timer;
    if (logStats) {
        timer.start();
        std::cout << "testSeeds start: " << start << " count: " << count << std::endl;
    }

    std::thread *threads[threadCount];
    std::vector<std::int64_t> results[threadCount];

    for (int tid = 0; tid < threadCount; ++tid) {
        ThreadData data(start, start+count, threadCount, tid, &results[tid]);
        data.predicate = predicate;
        data.printWhenFound = printWhenFound;
        threads[tid] = new std::thread(testSeedsMtHelper, data);
    }

    std::vector<std::int64_t> combined;
    for (int tid = 0; tid < threadCount; ++tid) {
        threads[tid]->join();
        combined.insert(combined.end(), results[tid].begin(), results[tid].end());
        delete threads[tid];
    }

    std::sort(combined.begin(), combined.end());

    if (logStats) {
        double millis = timer.elapsedMilliseconds();
        for (auto seed : combined) {
            std::cout << SeedHelper::getString(seed) << '\n';
        }

        std::cout << "found: " << combined.size() << " " << (double)combined.size()*100 / count << "%" << '\n';
        std::cout << millis << " ms" << '\n';
        std::cout << count / millis << " seeds/ms" << std::endl;
    }

    return combined;


//    Timer timer;
//    timer.start();
//    std::cout << "testSeeds start: " << start << " count: " << count << std::endl;
//
//    std::vector<std::int64_t> vec;
//
//    for (std::int64_t seed = start; seed < start + count; ++seed) {
//        if (predicate(seed)) {
//            vec.push_back(seed);
//        }
//    }
//    double millis = timer.elapsedMilliseconds();
//    for (auto seed : vec) {
//        std::cout << SeedHelper::getString(seed) << '\n';
//    }
//    std::cout << "found: " << vec.size() << " " << (double)vec.size()*100 / count << "%" << '\n';
//    std::cout << millis << " ms" << '\n';
//    std::cout << count / millis << " seeds/ms" << std::endl;
}







