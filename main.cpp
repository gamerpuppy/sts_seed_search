
#include <iostream>

#include <chrono>
#include <ctime>
#include <cmath>
#include <array>
#include <random>


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


int main() {

    sts::SeedMatcher matcher;
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

//    matcher.addPandoraPredicate(sts::CharacterClass::IRONCLAD, [](std::array<sts::Card, 10> cards) {
//        int count = 0;
//        for (int i = 0; i < 9; i++) {
//            if (cards[i] == sts::Card::REAPER) {
//                ++count;
//            }
//        }
//        return count >= 7;
//    });

//    matcher.addPredicate([](std::int64_t seed) {
//        sts::Random cardRandomRng(seed);
//        int count = 0;
//        for (int i = 0; i < 9; i++) {
//            sts::Card card = sts::Ironclad::cardPool[cardRandomRng.random(71)];
//            if (card == sts::Card::REAPER) {
//                ++count;
//            }
//        }
//        return count >= 7;
//    });

    matcher.addPredicate([](std::int64_t seed) {
        sts::Random cardRandomRng(seed);
        int count = 0;
        int sameLastCardCount = 1;
        int maxSameLastCardCount = 1;
        sts::Card lastCard = sts::Ironclad::cardPool[cardRandomRng.random(71)];
        if (lastCard == sts::Card::REAPER) {
            ++count;
        }

        for (int i = 1; i < 9; i++) {
            sts::Card card = sts::Ironclad::cardPool[cardRandomRng.random(71)];
            if (card == sts::Card::REAPER) {
                ++count;
            }
            if (lastCard == card) {
                sameLastCardCount++;
                if (sameLastCardCount > maxSameLastCardCount) {
                    maxSameLastCardCount = sameLastCardCount;
                }
            } else {
                lastCard = card;
                sameLastCardCount = 0;
            }

        }
        return count >= 7 || maxSameLastCardCount == 7;
    });


    matcher.mustGetBossRelicFromSwap(sts::PANDORAS_BOX);

    sts::SeedSearcher searcher(matcher);

    std::int64_t seedStart = 600000000000000LL;
//    std::int64_t seedStart = 124314589110LL;
    auto seedCount = static_cast<std::int64_t>(1e14);
    int threadCount = 16;

//    std::cout << searcher.getFirstMatching(seedStart, seedCount) << std::endl;


    std::cout <<  "searching " << seedCount << " seeds with " << threadCount << " threads, starting at " << seedStart << "\n";

    Timer timer;
    timer.start();

    auto search = searcher.searchMt(seedStart, seedCount, threadCount);
//    auto search  = searcher.search(seedStart, seedCount);
//    auto search = searcher.countMatching(123456700, seedCount);
//    auto search = searcher.countMatchingMt(seedStart, seedCount, threadCount);


    std::cout << "found " << search.size() << " results in " << timer.elapsedMilliseconds()
        << " millis" << std::endl;

    for (auto x : search) {
        std::cout << sts::SeedHelper::getString(x) << "\n";
    }







}







