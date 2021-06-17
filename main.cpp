
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
#include "sts_events.h"

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

using namespace sts;


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
    std::int64_t seedStart = 77774566677;
    std::int64_t seedCount = (std::int64_t) 1e7;

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
    std::int64_t attribute;

    SeedResult() = default;
    SeedResult(int64_t seed, int attribute) : seed(seed), attribute(attribute) {}
    bool operator<(const SeedResult &rhs) const {
        if (attribute == rhs.attribute) {
            return seed < rhs.seed;
        }
        return attribute < rhs.attribute;
    }
};

bool compareSeedResults(const SeedResult &a, const SeedResult &b) {
    if (a.attribute == b.attribute) {
        return a.seed > b.seed;
    }
    return a.attribute > b.attribute;
}




void testSeedsForBossNeows() {
    sts::testSeedForNeowBossEvent(SeedHelper::getLong("54576PMR8ICQY"));

}


struct SeedResultStats {
    SeedResult min;
    SeedResult median;
    SeedResult max;

    double avg;
    double variance;
};

SeedResultStats getStats(std::vector<SeedResult> vec) {
    SeedResultStats stats;

    std::sort(vec.begin(), vec.end());
    stats.min = vec.front();
    stats.median = vec.at(vec.size()/2 + 1);
    stats.max = vec.back();


    std::int64_t agg = 0;
    for (auto r : vec) {
        agg += r.attribute;
    }

    double avg = (double) agg / vec.size();

    double varianceSum = 0;
    for (auto r : vec) {
        varianceSum += (avg-r.attribute)*(avg-r.attribute);
    }

    stats.avg = avg;
    stats.variance = varianceSum / vec.size();
    return stats;
}


void testSeedsForUniquePaths(std::int64_t seedStart, std::int64_t seedCount) {
    Timer timer;
    timer.start();
    std::cout << "testSeedsForUniquePaths start: " << seedStart << " count: " << seedCount << std::endl;

    std::vector<SeedResult> vec;

    for (std::int64_t seed = seedStart; seed < seedStart + seedCount; ++seed) {
        Map map = Map::fromSeed(seed, 0, 1);
        map.normalizeParents();
        vec.emplace_back(seed, getUniquePaths(map).size());
    }
    double millis = timer.elapsedMilliseconds();


    SeedResultStats stats = getStats(vec);


    SeedResult min = vec.front();
    std::cout << Map::fromSeed(min.seed).toString() << '\n';
    std::cout << "min: " << SeedHelper::getString(min.seed) << " " << min.attribute << "\n";


    SeedResult max = stats.max;
    std::cout << Map::fromSeed(max.seed).toString() << '\n';
    std::cout << "max: " << SeedHelper::getString(max.seed) << " " << max.attribute << "\n";

    SeedResult med = stats.median;
    std::cout << Map::fromSeed(med.seed).toString() << '\n';
    std::cout << "median: " << SeedHelper::getString(med.seed) << " " << med.attribute << "\n";

    std::cout << "variance: " << stats.variance << " stddev: " << sqrt(stats.variance) << " avg: " << stats.avg << "\n";

    std::cout << millis << " ms" << std::endl;
    std::cout << seedCount / millis << " seeds/ms" << std::endl;
}


void testSeeds(std::int64_t start, std::int64_t count, const SeedPredicate& predicate) {

    Timer timer;
    timer.start();
    std::cout << "testSeeds start: " << start << " count: " << count << std::endl;

    std::vector<std::int64_t> vec;

    for (std::int64_t seed = start; seed < start + count; ++seed) {
        if (predicate(seed)) {
            vec.push_back(seed);
        }
    }
    double millis = timer.elapsedMilliseconds();
    for (auto seed : vec) {
        std::cout << SeedHelper::getString(seed) << '\n';
    }
    std::cout << "found: " << vec.size() << " " << (double)vec.size()*100 / count << "%" << '\n';
    std::cout << millis << " ms" << '\n';
    std::cout << count / millis << " seeds/ms" << std::endl;
}


int main(int argc, const char ** argv) {

//    testSeeds(12512566,1e5, testSeedForNeowBossEvent);

    std::int64_t seed = SeedHelper::getLong("8C3DE");
    testSeedForNeowBossEvent(seed);


    GameState gameState = GameState::createGameState(seed, 0);
    gameState.lastRoom = Room::MONSTER;

    Path path = Path::fromString("M????R?RT$R$??R");

    for (int y = 0; y < 15; y++) {
        gameState.floor = y+1;
        Room room = path.roomAt(y);
        if (room == Room::NONE) {
            break;
        }

        if (room == sts::Room::EVENT) {
            auto res = getEventRoomEvent(gameState);

            if (res == Event::MONSTER) {
                gameState.lastRoom = Room::MONSTER;
            } else if (res == Event::SHOP) {
                gameState.lastRoom = Room::SHOP;
            } else {
                gameState.lastRoom = Room::EVENT;
            }

        } else {
            gameState.lastRoom = room;
        }
    }

    gameState.floor += 2;
    gameState.act = 2;
    gameState.lastRoom = sts::Room::BOSS;

    gameState.eventList.clear();
    gameState.eventList.insert(gameState.eventList.begin(), Act2::eventList.begin(), Act2::eventList.end());

    gameState.shrineList.clear();
    gameState.shrineList.insert(gameState.shrineList.begin(), Act2::shrineList.begin(), Act2::shrineList.end());

    gameState.resetEventHelperProbabilities();

    path = Path::fromString("M??");

    for (int y = 0; y < 15; y++) {
        ++gameState.floor;
        Room room = path.roomAt(y);
        if (room == Room::NONE) {
            break;
        }

        if (room == sts::Room::EVENT) {
            auto res = getEventRoomEvent(gameState);
            std::cout << eventStrings[(int)res] << std::endl;

            if (res == Event::MONSTER) {
                gameState.lastRoom = Room::MONSTER;
            } else if (res == Event::SHOP) {
                gameState.lastRoom = Room::SHOP;
            } else {
                gameState.lastRoom = Room::EVENT;
            }

        } else {
            std::cout << roomStrings[(int)room] << std::endl;
            gameState.lastRoom = room;
        }


    }

    std::cout << Random(seed+20).randomBoolean(0.3) << std::endl;


//    testSeedsForUniquePaths(724535456146, 1e7);

//    Map map = Map::fromSeed(SeedHelper::getLong("8BXNY"));
//    std::cout << map.toString(true) << std::endl;
//
//    auto uniques = sts::getUniquePaths(map);
//    std::cout << uniques.size() << std::endl;
//
//    std::cout << std::hex << std::uppercase;
//    for (auto p : uniques) {
////        std::cout <<  p.bits << std::endl;
//        std::cout << p.toString() << std::endl;
//    }

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






//    testSeedsForBossNeows();

//    auto seeds = parseSeeds("single-paths");
//
//    std::vector<SeedResult> results;
//    for (auto seed : seeds) {
//        auto map = sts::Map::fromSeed(seed, 20, 1);
////
////        int singleLength = sts::getPathSingleLength(seed);
////        int singleLengthTotal = sts::getPathTotalSingleLength(seed);
//
////        int attribute = sts::getMinMapWeight(map, [](auto node){ return node.room == sts::Room::ELITE ? 1 : 0; });
//
////        int attribute = sts::getMinMapWeight(map, [](auto node){ return node.room == sts::Room::MONSTER; });
//        int attribute = sts::getMinMapWeight(map,
//                                                          [](auto node){ return node.room == sts::Room::MONSTER
//                                                                                || node.room == sts::Room::ELITE; });
//
////        int attribute = sts::getMaxMapWeight(map, [](auto node) { return node.room == sts::Room::ELITE; });
//
////        bool isForcedElite = sts::isForcedMonsterIntoEliteFight(seed);
//
//
//        results.emplace_back(seed, attribute);
//    }
//
//    std::sort(results.begin(), results.end(), compareSeedResults);
//
//    for (auto res : results) {
//        std::cout << res.attribute << " " << sts::SeedHelper::getString(res.seed) << '\n';
//    }
//
//
//    auto res = *results.begin();
//    Map map = Map::fromSeed(res.seed);
//    std::cout << map.toString(true) << std::endl;
//    std::cout << SeedHelper::getString(res.seed) << " score: " << res.attribute << '\n';
//

