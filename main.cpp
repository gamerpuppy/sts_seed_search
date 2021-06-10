
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

//void analyzeSeeds() {
//    std::string s;
//    do {
//        std::cin >> s;
//        auto seedLong = sts::SeedHelper::getLong(s);
//        auto res = sts::analyzePandorasBoxRewards(seedLong, sts::CharacterClass::DEFECT);
//        std::cout << s << " " << seedLong << " " << res.name << " " << res.count << std::endl;
//    } while (s != "q");
//}


int main(int argc, const char ** argv) {
//    analyzeSeeds();
//    runSearch(228076932372177LL);
    sts::SearchConfig config;
    std::cout << "Pandoras Box Seed Search by gamerpuppy" << "\n";
    std::cout << "--will output results to results.txt--\n";
    std::cout << "Enter number of threads to use" << std:: endl;
    std::cin >> config.threads;
    std::cout << "Enter -1 (for random start) or the seed to start start search at." << std::endl;
    std::cin >> config.startSeed;

    sts::runSearch(config);

    return 0;
}


