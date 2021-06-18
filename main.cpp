
#include <iostream>


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


void readSinglePathSeeds() {

    std::ofstream os("single-paths.csv");

    os << "Act 1 Seed, Act 2 Seed, Act 3 Seed, Single Path Length, Total Single Path Length,";
    os << "Path A0, Unique Paths A0,";
    os << "Min ? A0, Min R A0, Min M A0, Min E A0, Min Combat A0,";
    os << "Max ? A0, Max R A0, Max M A0, Max E A0, Max Combat A0,";
    os << "Path A1+, Unique Paths A1,";
    os << "Min ? A1, Min R A1, Min M A1, Min E A1, Min Combat A1,";
    os << "Max ? A1, Max R A1, Max M A1, Max E A1, Max Combat A1\n";


    auto seeds = parseSeeds("single-paths-final");
    std::sort(seeds.begin(), seeds.end());

    for (auto seed : seeds) {
        auto map0 = sts::Map::fromSeed(seed, 0, 1);
        auto map1 = sts::Map::fromSeed(seed, 1, 1);

        int singlePathLength = sts::getPathSingleLength(seed)+1;
        int totalSinglePathLength = sts::getPathTotalSingleLength(seed)+1;


        auto act1Seed = SeedHelper::getString(seed);
        auto act2Seed = SeedHelper::getString(seed-199);
        auto act3Seed = SeedHelper::getString(seed-599);

        os << act1Seed << ',' << act2Seed << ',' << act3Seed << ',' << singlePathLength << ',' << totalSinglePathLength << ',';

        std::string pathStr0 = getLeftMostPath(map0, singlePathLength).toString(0, singlePathLength);
        auto uniquePathCount0 = sts::getUniquePaths(map0).size();


        int minQuestion0 = sts::getMinMapWeight(map0, [](auto node){ return node.room == sts::Room::EVENT ? 1 : 0; });
        int minRest0 = sts::getMinMapWeight(map0, [](auto node){ return node.room == sts::Room::REST ? 1 : 0; });
        int minMonsters0 = sts::getMinMapWeight(map0, [](auto node){ return node.room == sts::Room::MONSTER ? 1 : 0; });
        int minElites0 = sts::getMinMapWeight(map0, [](auto node){ return node.room == sts::Room::ELITE ? 1 : 0; });
        int minCombats0 = sts::getMinMapWeight(map0, [](auto node){ return (node.room == sts::Room::MONSTER || node.room == sts::Room::ELITE) ? 1 : 0; });

        int maxQuestion0 = sts::getMaxMapWeight(map0, [](auto node){ return node.room == sts::Room::EVENT ? 1 : 0; });
        int maxRest0 = sts::getMaxMapWeight(map0, [](auto node){ return node.room == sts::Room::REST ? 1 : 0; });
        int maxMonsters0 = sts::getMaxMapWeight(map0, [](auto node){ return node.room == sts::Room::MONSTER ? 1 : 0; });
        int maxElites0 = sts::getMaxMapWeight(map0, [](auto node){ return node.room == sts::Room::ELITE ? 1 : 0; });
        int maxCombats0 = sts::getMaxMapWeight(map0, [](auto node){ return (node.room == sts::Room::MONSTER || node.room == sts::Room::ELITE) ? 1 : 0; });

        os << pathStr0 << ',' << uniquePathCount0 << ',';
        os << minQuestion0 << ',' << minRest0 << ',' << minMonsters0 << ',' << minElites0 << ',' << minCombats0 << ',';
        os << maxQuestion0 << ',' << maxRest0 << ',' << maxMonsters0 << ',' << maxElites0 << ',' << maxCombats0 << ',';

        auto uniquePathCount1 = sts::getUniquePaths(map1).size();
        std::string pathStr1 = getLeftMostPath(map1, singlePathLength).toString(0, singlePathLength);

        int minQuestion1 = sts::getMinMapWeight(map1, [](auto node){ return node.room == sts::Room::EVENT ? 1 : 0; });
        int minRest1 = sts::getMinMapWeight(map1, [](auto node){ return node.room == sts::Room::REST ? 1 : 0; });
        int minMonsters1 = sts::getMinMapWeight(map1, [](auto node){ return node.room == sts::Room::MONSTER ? 1 : 0; });
        int minElites1 = sts::getMinMapWeight(map1, [](auto node){ return node.room == sts::Room::ELITE ? 1 : 0; });
        int minCombats1 = sts::getMinMapWeight(map1, [](auto node){ return (node.room == sts::Room::MONSTER || node.room == sts::Room::ELITE) ? 1 : 0; });

        int maxQuestion1 = sts::getMaxMapWeight(map1, [](auto node){ return node.room == sts::Room::EVENT ? 1 : 0; });
        int maxRest1 = sts::getMaxMapWeight(map1, [](auto node){ return node.room == sts::Room::REST ? 1 : 0; });
        int maxMonsters1 = sts::getMaxMapWeight(map1, [](auto node){ return node.room == sts::Room::MONSTER ? 1 : 0; });
        int maxElites1 = sts::getMaxMapWeight(map1, [](auto node){ return node.room == sts::Room::ELITE ? 1 : 0; });
        int maxCombats1 = sts::getMaxMapWeight(map1, [](auto node){ return (node.room == sts::Room::MONSTER || node.room == sts::Room::ELITE) ? 1 : 0; });

        os << pathStr1 << ',' << uniquePathCount1 << ',';
        os << minQuestion1 << ',' << minRest1 << ',' << minMonsters1 << ',' << minElites1 << ',' << minCombats1 << ',';
        os << maxQuestion1 << ',' << maxRest1 << ',' << maxMonsters1 << ',' << maxElites1 << ',' << maxCombats1 << '\n';



//        bool isForcedElite = sts::isForcedMonsterIntoEliteFight(seed);
//        int attribute = testSeedForNeowBossEvent(seed);


    }
    os.close();

//    std::sort(results.begin(), results.end(), compareSeedResults);
//
//    for (auto res : results) {
//        std::cout << res.attribute << " " << sts::SeedHelper::getString(res.seed) << '\n';
//    }

}

bool testSeedForMinCombats(const std::int64_t seed) {
    {
        Random neowRng(seed);
        neowRng.random(0,5);
        int idx = 6+neowRng.random(0,4);
        if (static_cast<Neow::Reward>(idx) != sts::Neow::Reward::THREE_ENEMY_KILL) {
            return false;
        }
    }

    Map act1 = Map::fromSeed(seed, 0);
    auto candidatePaths1 = getPathsMatching(act1, [](auto path, auto nextRoom, auto pathLength) {
        return pathLength == 0 || (nextRoom != Room::MONSTER && nextRoom != Room::ELITE);
    });

    bool validatedAct1 = std::any_of(candidatePaths1.begin(),candidatePaths1.end(),
                            [=](auto p){ return validateNeowBossPath(seed, p);
                            });

    if (!validatedAct1) {
        return false;
    }

    Map act2 = Map::fromSeed(seed, 0, 2);

    auto candidatePaths2 = getPathsMatching(act2, [](auto path, auto nextRoom, auto pathLength) {
        return pathLength == 0 || (nextRoom != Room::MONSTER && nextRoom != Room::ELITE);
    });

    return !candidatePaths2.empty();
}


int main(int argc, const char ** argv) {

//    std::int64_t seed = SeedHelper::getLong("69WKC6PKQJ95");
//    Map map = Map::fromSeed(seed, 0, 2);
//    std::cout << seed  << std::endl;
//    std::cout << map.toString() << std::endl;
//
//    auto candidatePaths2 = getPathsMatching(map, [](auto path, auto nextRoom, auto pathLength) {
//        return pathLength == 0 || (nextRoom != Room::MONSTER && nextRoom != Room::ELITE);
//    });

//    auto seedLong = SeedHelper::getLong("2TJUGXNV8D");
//
//    auto act1Seed = seedLong;
//    auto act2Seed = seedLong-199;
//    auto act3Seed = seedLong-599;
//
//    std::cout << Map::fromSeed(act1Seed, 0 , 1).toString() << '\n';
//    std::cout << Map::fromSeed(act2Seed, 0 , 2).toString() << '\n';
//    std::cout << Map::fromSeed(act3Seed, 0 , 3).toString() << '\n';
//
//    std::cout << SeedHelper::getString(act2Seed) << '\n';
//    std::cout << SeedHelper::getString(act3Seed) << '\n';


//    std::cout << SeedHelper::getString(seedLong-1-offset);



//    readSinglePathSeeds();
//    testSeeds(8225124566,1e9, testSeedForMinCombats);



//    std::default_random_engine generator;
//    std::uniform_int_distribution<std::int64_t> distribution(0,LONG_LONG_MAX);
//    std::int64_t randomStart = distribution(generator);
////    testSeedsMt(randomStart, 8e9, 16, testSeedForMinCombats, true, true);
////    testSeedsMt(randomStart, 1e10, 16, testSeedForFruitJuiceNeows, true, true);
//    testSeedsMt(randomStart, 1e6, 16, testSeedForCardReward, false, true);



//    testSeeds(12512566,1e5, testSeedForNeowBossEvent);

//    std::int64_t seed = SeedHelper::getLong("8C3DE");
//    testSeedForNeowBossEvent(seed);
//
//
//    GameState gameState = GameState::createGameState(seed, 0);
//    gameState.curRoom = Room::MONSTER;
//
//    Path path = Path::fromString("M????R?RT$R$??R");
//
//    for (int y = 0; y < 15; y++) {
//        gameState.floor = y+1;
//        Room room = path.roomAt(y);
//        if (room == Room::NONE) {
//            break;
//        }
//
//        if (room == sts::Room::EVENT) {
//            auto res = getEventRoomEvent(gameState);
//
//            if (res == Event::MONSTER) {
//                gameState.curRoom = Room::MONSTER;
//            } else if (res == Event::SHOP) {
//                gameState.curRoom = Room::SHOP;
//            } else {
//                gameState.curRoom = Room::EVENT;
//            }
//
//        } else {
//            gameState.curRoom = room;
//        }
//    }
//
//    gameState.floor += 2;
//    gameState.act = 2;
//    gameState.curRoom = sts::Room::BOSS;
//
//    gameState.eventList.clear();
//    gameState.eventList.insert(gameState.eventList.begin(), Act2::eventList.begin(), Act2::eventList.end());
//
//    gameState.shrineList.clear();
//    gameState.shrineList.insert(gameState.shrineList.begin(), Act2::shrineList.begin(), Act2::shrineList.end());
//
//    gameState.resetEventHelperProbabilities();
//
//    path = Path::fromString("M??");
//
//    for (int y = 0; y < 15; y++) {
//        ++gameState.floor;
//        Room room = path.roomAt(y);
//        if (room == Room::NONE) {
//            break;
//        }
//
//        if (room == sts::Room::EVENT) {
//            auto res = getEventRoomEvent(gameState);
//            std::cout << eventStrings[(int)res] << std::endl;
//
//            if (res == Event::MONSTER) {
//                gameState.curRoom = Room::MONSTER;
//            } else if (res == Event::SHOP) {
//                gameState.curRoom = Room::SHOP;
//            } else {
//                gameState.curRoom = Room::EVENT;
//            }
//
//        } else {
//            std::cout << roomStrings[(int)room] << std::endl;
//            gameState.curRoom = room;
//        }
//
//
//    }
//
//    std::cout << Random(seed+20).randomBoolean(0.3) << std::endl;


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

