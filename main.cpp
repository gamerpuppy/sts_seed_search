
#include <iostream>

#include <chrono>
#include <ctime>
#include <cmath>
#include <array>


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


    matcher.mustHaveCallingBellRewards(sts::BAG_OF_MARBLES, sts::PAPER_PHROG, sts::CHAMPION_BELT);
    sts::SeedSearcher searcher(matcher);

    long seedStart = 1234567890;
    long seedCount = (long)1e8;
    int threadCount = 16;

    std::cout <<  "searching " << seedCount << " seeds with " << threadCount << " threads, starting at " << seedStart << "\n";

    Timer timer;
    timer.start();

//    auto search = searcher.countMatching(123456700, seedCount);
    auto search = searcher.countMatchingMt(seedStart, seedCount, threadCount);


    std::cout << "found " << search << " results in " << timer.elapsedMilliseconds()
        << " millis" << std::endl;

//    for ( auto x : search) {
//        std::cout << sts::SeedHelper::getString(x) << "\n";
//    }

}



