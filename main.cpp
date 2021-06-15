
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
    auto cs = parseCandidates("candidates-10.txt");
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

void runMapBenchmark() {
    Timer timer;
    timer.start();
    std::int64_t seedStart = 777777;
    std::int64_t seedCount = (std::int64_t) 5e5;

    int eventCount = 0;
    int edgeCount = 0;

    for (std::int64_t x = 0; x < seedCount; ++x) {
        auto seed = seedStart + x;

        sts::Random mapRng(seed+1);
        sts::Map map;
        sts::generateMap(map, mapRng);


        edgeCount += map.getNode(0,11).edgeCount;
        if (map.getNode(0,13).room == sts::Room::EVENT) {
            ++eventCount;
        }
    }

    double millis = timer.elapsedMilliseconds();

    std::cout << timer.elapsedMilliseconds() << " ms" << std::endl;
    std::cout << seedCount/millis << " seeds/ms" << std::endl;

    std::cout << eventCount << std::endl;
    std::cout << edgeCount << std::endl;
}

// 2:47-10-56

void findSinglePathSeeds() {
    Timer timer;
    timer.start();

    std::int64_t seedStart = 46000000000000LL;
    std::int64_t seedCount = (std::int64_t)5e8;
    std::cout << "start: " << seedStart << " count: " << seedCount << std::endl;

    auto res = sts::findSinglePathSeedsMt(seedStart, seedCount, 16, 4);

//    for (auto x : res) {
//        std::cout << sts::SeedHelper::getString(x) << "\n";
//    }

    double millis = timer.elapsedMilliseconds();

    std::cout << res.size() << " found" << std::endl;
    std::cout << millis << " ms" << std::endl;
    std::cout << seedCount/millis << " seeds/ms" << std::endl;
}


std::vector<std::int64_t> parseSeeds(std::string fName) {
    std::ifstream input(fName);

    std::vector<std::int64_t> ret;

    std::string line;
    while (std::getline(input, line)) {
        ret.push_back(sts::SeedHelper::getLong(line));
    }
    return ret;
};

struct SeedResult {
    std::int64_t seed;
    int attribute;

    SeedResult(int64_t seed, int attribute) : seed(seed), attribute(attribute) {}
};

bool compareSeedResults(const SeedResult &a, const SeedResult &b) {
    return a.attribute > b.attribute;
}


int main(int argc, const char ** argv) {

    auto seeds = parseSeeds("single-paths-2");

    std::vector<SeedResult> results;
    for (auto seed : seeds) {
//        int length = sts::getPathSingleLength(seed);
//        int length = sts::getPathTotalSingleLength(seed);
        int length = sts::getForcedMonsterFightCount(seed);
//        bool matches = sts::isForcedMonsterIntoEliteFight(seed);


        results.emplace_back(seed, length);
    }

    std::sort(results.begin(), results.end(), compareSeedResults);

    for (auto res : results) {
        std::cout << res.attribute << " " << sts::SeedHelper::getString(res.seed) << '\n';
    }




//
//    std::cout << sizeof(sts::MapNode) << std::endl;
//    std::cout << sizeof(sts::Map) << std::endl;

//    runMapBenchmark();

//    sts::printStats();
//    sts::mapTest(46006654027332);

//    std::cout << sts::SeedHelper::getString(5000000+1527);

//    sts::findSinglePathSeeds(223125166216516LL, (std::int64_t)1e9, 4);

//    findSinglePathSeeds();



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