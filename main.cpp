
#include <iostream>

#include <chrono>
#include <ctime>
#include <cmath>
#include <array>
#include <random>
#include <fstream>


#include "sts_impl.h"
#include "seed_search.h"
#include "java_random.h"

class Timer
{
public:
    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }

    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }

    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;

        if(m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }

        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }

    double elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
};


void runSearch(std::int64_t seedStart, std::int64_t seedEnd) {
    sts::SeedMatcher matcher;
//    matcher.addPredicate([](std::int64_t seed) {
//        sts::Random cardRandomRng(seed);
//
//        bool haveMissed = false;
//        int lastIdx = cardRandomRng.random(70);
//        {
//            int idx = cardRandomRng.random(70);
//
//            if (lastIdx != idx) {
//                haveMissed = true;
//                lastIdx = idx;
//            }
//        }
//
//        int end = 8;
//        for (int i = 2; i < end; i++) {
//            int idx = cardRandomRng.random(70);
//            if (lastIdx != idx) {
//                if (i < end-1) {
//                    return false;
//                } else {
//                    return !haveMissed;
//                }
//            }
//        }
//        return true;
//    });

    matcher.addPredicate([](std::int64_t seed) {
        sts::Random cardRandomRng(seed);
        std::int64_t res = cardRandomRng.random(70);
        for (int i = 0; i < 8; ++i) {
            if (cardRandomRng.random(70) != res) {
                return false;
            }
        }
        return true;
    });


    matcher.mustGetBossRelicFromSwap(sts::PANDORAS_BOX);
    sts::SeedSearcher searcher(matcher);


//    std::cout << searcher.getFirstMatching(0,1000000000);

    auto seedCount = seedEnd-seedStart;
    int threadCount = 16;
    std::cout <<  "searching " << seedCount << " seeds with " << threadCount << " threads, starting at " << seedStart << "\n";
    Timer timer;
    timer.start();

//    auto search = searcher.searchMt(seedStart, seedCount, threadCount);
    auto search = searcher.countMatching(seedStart, seedCount);

    std::cout << "found " << search << " results in " << timer.elapsedMilliseconds()
              << " millis" << std::endl;
//    for (auto x : search) {
//        std::cout << sts::SeedHelper::getString(x) << "\n";
//    }

}


void analyzeSeeds() {
    std::string s;
    do {
        std::cin >> s;
        auto seedLong = sts::SeedHelper::getLong(s);
        auto res = sts::analyzePandorasBoxRewards(seedLong, sts::CharacterClass::DEFECT);
        std::cout << s << " " << seedLong << " " << res.name << " " << res.count << std::endl;
    } while (s != "q");
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
    sts::Random rand(seed);

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

int main(int argc, const char ** argv) {
//    analyzeSeeds();
//    runSearch(228076932372177LL);

    Timer timer;
    timer.start();

    std::int64_t start = 300000000000000LL;
    auto count = static_cast<std::int64_t>(1e9);

    long found = 0;

    for (std::int64_t seed = start; seed < start+count; seed++) {
        if (testSeed(seed)) {
            found++;
        }
    }

    std::cout << "found " << found << " results in " << timer.elapsedMilliseconds()
              << " millis" << std::endl;


//    runSearch(300000000000000LL, 300000000000000LL+static_cast<std::int64_t>(1e9));
}


//    matcher.addPandoraPredicate(sts::CharacterClass::DEFECT, [](std::array<sts::Card, 10> cards) {
//        int count = 0;
//        for (int i = 0; i < 8; i++) {
//            if (cards[i] == sts::Card::CLAW) {
//                ++count;
//            }
//        }
//        return count >= 6;
//    });

//
//    matcher.addPredicate([](std::int64_t seed) {
//        sts::Random cardRandomRng(seed);
//        int count = 0;
//        int sameLastCardCount = 1;
//        int maxSameLastCardCount = 1;
//        sts::Card lastCard = sts::Ironclad::cardPool[cardRandomRng.random(71)];
//        if (lastCard == sts::Card::REAPER) {
//            ++count;
//        }
//
//        for (int i = 1; i < 9; i++) {
//            sts::Card card = sts::Ironclad::cardPool[cardRandomRng.random(71)];
//            if (card == sts::Card::REAPER) {
//                ++count;
//            }
//            if (lastCard == card) {
//                sameLastCardCount++;
//                if (sameLastCardCount > maxSameLastCardCount) {
//                    maxSameLastCardCount = sameLastCardCount;
//                }
//            } else {
//                lastCard = card;
//                sameLastCardCount = 0;
//            }
//
//        }
//        return count >= 7 || maxSameLastCardCount == 7;
//    });
//
//

//    matcher.addNeowPredicate([](auto blessing) {
//        return blessing[1].r == sts::Neow::Reward::RANDOM_COMMON_RELIC;
//    });
//    matcher.addPredicate([](long seed) {
//        java::Random relicRng(sts::Random(seed).randomLong());
//        auto commonRelicsCopy = sts::Ironclad::commonRelicPool;
//        java::Collections::shuffle( commonRelicsCopy.begin(), commonRelicsCopy.end(), relicRng);
//
//        return commonRelicsCopy[0] == sts::POTION_BELT;
//    });
//    matcher.mustHaveCallingBellRewards(sts::BAG_OF_MARBLES, sts::PAPER_PHROG, sts::CHAMPION_BELT);





