
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


using namespace sts;

std::string getTime() {
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string timeStr(std::ctime(&time));
    timeStr.erase(timeStr.end()-1, timeStr.end());
    return timeStr;
}

inline bool testSeedForPandorasRelic(std::int64_t seed, CharacterClass characterClass) {
    auto relicRng = sts::Random(seed);
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

    return bossRelic == sts::PANDORAS_BOX;
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

PandorasBoxRewardResult analyzePandorasBoxRewards(std::int64_t seed, CharacterClass characterClass) {
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

    cards[0] = getCard(cardRandomRng.random(cardPoolSize-1), characterClass);
    sts::Card maxCard = cards[0];

    for (int i = 1; i < numTransformedCards; i++) {
        cards[i] = getCard(cardRandomRng.random(cardPoolSize-1), characterClass);
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

    PandorasBoxRewardResult ret;
    ret.count = maxSameLastCardCount;
    ret.name = sts::normalCardNames[(int)maxCard];
    return ret;
}


void logSeed(std::int64_t seed) {
    std::string seedStr = SeedHelper::getString(seed);

    if (testSeedForPandorasRelic(seed, CharacterClass::DEFECT)) {
        auto res = analyzePandorasBoxRewards(seed, CharacterClass::DEFECT);
        std::cout << getTime() << " seed " << seedStr << " " << seed << " " << res.name << " " << res.count << std::endl;
    }

    if (testSeedForPandorasRelic(seed, CharacterClass::WATCHER)) {
        auto res = analyzePandorasBoxRewards(seed, CharacterClass::WATCHER);
        std::cout << getTime() << " seed " << seedStr << " " << seed << " " << res.name << " " << res.count << std::endl;
    }

}

inline bool testSeed(std::int64_t seed) {
    sts::fast::Random rand(seed);

    const int cardPoolSizeMinusOne = Defect::cardPool.size()-1;

    // 0
    auto num = rand.random(cardPoolSizeMinusOne);

    // 1
    if (rand.random(cardPoolSizeMinusOne) != num) {
        return false;
    }
    // 2
    if (rand.random(cardPoolSizeMinusOne) != num) {
        return false;
    }
    // 3
    if (rand.random(cardPoolSizeMinusOne) != num) {
        return false;
    }
    // 4
    if (rand.random(cardPoolSizeMinusOne) != num) {
        return false;
    }
    // 5
    if (rand.random(cardPoolSizeMinusOne) != num) {
        return false;
    }
    // 6
    if (rand.random(cardPoolSizeMinusOne) != num) {
        return false;
    }
//    // 7
//    if (rand.random(70) != num) {
//        return false;
//    }
//    return testSeedForPandorasRelic(seed, CharacterClass::IRONCLAD);

    return testSeedForPandorasRelic(seed, CharacterClass::DEFECT)
        || testSeedForPandorasRelic(seed, CharacterClass::WATCHER);
}

void sts::test() {
    testSeed(164734);
}

void testPandoraSeedsForDefectWatcherMtHelper(ThreadData data) {
    for (std::int64_t seed = data.startSeed+data.threadId; seed < data.endSeed; seed += data.threadCount) {
        if (testSeed(seed)) {
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




void testPandoraSeedsForDefectWatcherMtHelper2(ThreadData data) {
    for (std::int64_t seed = data.startSeed+data.threadId; seed < data.endSeed; seed += data.threadCount) {
        if (testSeed(seed)) {
//            logSeed(seed);
            data.foundVec->push_back(seed);
        }
    }
}


std::vector<int64_t> testPandorasForDefectWatcherMt2(const std::vector<candidate> &candidates, int offset, int threadCount) {
    std::thread *threads[threadCount];
    std::vector<std::int64_t> results[threadCount];

    for (int tid = 0; tid < threadCount; ++tid) {
        if (offset+tid >= candidates.size()) {
            break;
        }
        candidate c = candidates[offset+tid];
        ThreadData data(c.start, c.end, c.stride, tid, &results[tid]);
        threads[tid] = new std::thread(testPandoraSeedsForDefectWatcherMtHelper2, data);
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

    int offset = 0;
    while (offset < candidates.size()) {
        std::string time = getTime();
        auto matchedSeedsVec = testPandorasForDefectWatcherMt2(candidates, offset, 16);
        matchedSeeds.insert(matchedSeeds.end(), matchedSeedsVec.begin(), matchedSeedsVec.end());
        time = getTime();
//        std::cout << time << " found " << matchedSeedsVec.size() << " results" << std::endl;
        offset += 16;
    }

    return matchedSeeds;
}


void sts::describeSeeds(const std::vector<std::int64_t> seeds) {

    for (auto seed : seeds) {
        std::string seedStr = SeedHelper::getString(seed);

//        if (testSeedForPandorasRelic(seed, CharacterClass::IRONCLAD)) {
//            auto res = analyzePandorasBoxRewards(seed, CharacterClass::IRONCLAD);
//            std::cout << "Ironclad, " << seedStr << ", " << res.name << ", " << res.count << std::endl;
//        }


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

void findSinglePathSeedsMtHelper(ThreadData data, int length) {
    for (std::int64_t seed = data.startSeed+data.threadId; seed < data.endSeed; seed += data.threadCount) {
        if (testSeedForSinglePath(seed, length)) {
            std::cout << SeedHelper::getString(seed) << std::endl;
            data.foundVec->push_back(seed);
        }
    }
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













