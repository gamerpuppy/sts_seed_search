
#include <iostream>

#include <chrono>
#include <ctime>
#include <cmath>
#include <array>
#include <random>
#include <fstream>
#include <sstream>


#include "sts_impl.h"
#include "seed_search.h"
#include "java_random.h"
#include "sts_map.h"

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


std::vector<sts::candidate> parseCandidates(std::string fName) {
    std::ifstream input(fName);


    std::vector<sts::candidate> ret;

    std::string line;
    while (std::getline(input, line)) {
        std::stringstream inputStringStream(line);
        sts::candidate c;
        std::int32_t offset;
        std::int64_t start;
        std::int64_t end;
        std::int32_t stride;


        inputStringStream >> offset;
        inputStringStream >> start;
        inputStringStream >> end;
        inputStringStream >> stride;


        c.start = start;
        c.end = end;
        c.stride = stride;

        ret.push_back(c);
    }
    return ret;
};


void runCandidateFilter() {
    auto cs = parseCandidates("output5.txt");
    auto res = sts::runSearch2(cs);

    std::sort(res.begin(), res.end());

    sts::describeSeeds(res);

}

void runNormalSearch() {
    sts::SearchConfig config;
    std::cout << "Pandoras Box Seed Search by gamerpuppy" << "\n";
    std::cout << "--will output results to results.txt--\n";
    std::cout << "Enter number of threads to use" << std:: endl;
    std::cin >> config.threads;
    std::cout << "Enter -1 (for random start) or the seed to start start search at." << std::endl;
    std::cin >> config.startSeed;
//
}

void readAndDescribeSeeds(std::string fName) {
    std::ifstream input(fName);
    std::string seedStr;
    std::vector<std::int64_t> seeds;
    while (std::getline(input, seedStr)) {
        seeds.push_back(sts::SeedHelper::getLong(seedStr));
    }
    sts::describeSeeds(seeds);
}

int main(int argc, const char ** argv) {

    sts::mapTest();

//    std::int64_t seedStart = 0;
//    std::int64_t seedCount = (std::int64_t) 1e7;
//
//    int eventCount = 0;
//
//    for (std::int64_t x = 0; x < seedCount; ++x) {
//        auto seed = seedStart + x;
//
//        sts::Random mapRng(seed+1);
//        sts::Map map;
//        sts::generateMap(map, mapRng);
//
//        if (map.getNode(0,0).room == sts::Room::EVENT) {
//            ++eventCount;
//        }
//    }
//
//    std::cout << eventCount << std::endl;

//    for (int i = 0; i < 285; i++) {
//        std::cout << sts::cardNames[i] << " " << sts::normalCardNames[i] << '\n';
//    }
//    readAndDescribeSeeds("seeds.txt");
//
//    std::vector<std::int64_t> seeds = {sts::SeedHelper::getLong("FGZ8HEJLPY")};
//    sts::describeSeeds(seeds);

//    runCandidateFilter();
    return 0;
}


