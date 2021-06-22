
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
    auto cs = parseCandidates("single-paths-new");
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

//void asdf(CardColor color, CardType type, CardRarity rarity) {
//
////    int count = 0;
////    std::cout << "SkillsCardArray { ";
////    for (int i = 0; i < CardPools::cardPool.at((int)color).size(); ++i) {
////        auto card = CardPools::cardPool.at((int)color).at(i);
////        bool matches = cardTypes[(int)card] == type &&
////                       cardColors[(int)card] == color &&
////                       cardRarities[(int)card] == rarity;
////
////        if (matches) {
////            std::cout << "Card::" << cardEnumNames[(int)card] << ",";
////            ++count;
////        }
////    }
////    std::cout << " },\n";
////    std::cout << count << '\n';
//}


// red { attacks {common uncommon rare} skills {common uncommon rare} powers {common uncommon rare} }
// green { attacks {common uncommon rare} skills {common uncommon rare} powers {common uncommon rare} }
// blue { attacks {common uncommon rare} skills {common uncommon rare} powers {common uncommon rare} }
// purple { attacks {common uncommon rare} skills {common uncommon rare} powers {common uncommon rare} }


#include <cstring>
#include <cassert>

bool cardLessThanById(Card a, Card b) {
    int ia = (int)a;
    int ib = (int)b;


    auto ac = cardIds[ia];
    auto bc = cardIds[ib];

    int res = std::strcmp(ac, bc);

    return res == -1;
}


int startIndices[4][3][3];
int groupSize[4][3][3];

void asdf4(const std::vector<Card> &allSorted, std::vector<Card> &outCards, CardColor color, CardType type, CardRarity rarity) {

    int startIdx = static_cast<int>(outCards.size());
    startIndices[(int)color][(int)type][(int)rarity] = startIdx;


    for (auto card : allSorted) {
        auto idx = (int)card;

        bool matches = cardColors[idx] == color &&
                cardTypes[idx] == type &&
                cardRarities[idx] == rarity;
        if (matches) {
            outCards.push_back(card);
        }
    }

    int size = static_cast<int>(outCards.size())-startIdx;
    groupSize[(int)color][(int)type][(int)rarity] = size;

}

void asdf2() {
    std::vector<Card> allSorted;
    for (int i = 1; i < 371; ++i) {
        Card c = static_cast<Card>(i);

        allSorted.push_back(c);
    }

    std::sort(allSorted.begin(), allSorted.end(), cardLessThanById);

    for (auto card : allSorted) {
        std::cout << cardIds[(int)card] << '\n';
    }

    std::vector<Card> outCards;
    for (int colorIdx = 0; colorIdx < 4; ++colorIdx) {
        CardColor color = (CardColor)colorIdx;
        for (int typeIdx = 0; typeIdx < 3; ++typeIdx) {
            CardType type = (CardType)typeIdx;
            for (int rarityIdx = 0; rarityIdx < 3; ++rarityIdx) {
                CardRarity rarity = (CardRarity)rarityIdx;
                asdf4(allSorted, outCards, color, type, rarity);
            }
        }
    }

    std::cout << "{";
    for (auto c : outCards) {
        assert((int)c <= 370 && (int)c >= 0);
        std::cout << "Card::"<< cardEnumNames[(int)c] << ',';
    }
    std::cout << "};\n";



}

void generateCardBlob() {
    asdf2();

    std::cout << "{";
    for (int c = 0; c < 4; ++c) {
        std::cout << "{";
        for (int t = 0; t < 3; ++t) {
            std::cout << "{";
            for (int r = 0; r < 3; ++r) {
                std::cout << startIndices[c][t][r] << ",";
            }
            std::cout << "},";
        }
        std::cout << "},";
    }
    std::cout << "}";


    std::cout << '\n';

    std::cout << "{";
    for (int c = 0; c < 4; ++c) {
        std::cout << "{";
        for (int t = 0; t < 3; ++t) {
            std::cout << "{";
            for (int r = 0; r < 3; ++r) {
                std::cout << groupSize[c][t][r] << ",";
            }
            std::cout << "},";
        }
        std::cout << "},";
    }
    std::cout << "}";
}

void asdfColorless() {
    std::vector<Card> allSorted;
    for (int i = 1; i < 371; ++i) {
        Card c = static_cast<Card>(i);

        bool matches = cardColors[(int)c] == sts::CardColor::COLORLESS &&
                cardRarities[(int)c] != sts::CardRarity::BASIC &&
                cardRarities[(int)c] != sts::CardRarity::SPECIAL &&
                cardTypes[(int)c] != sts::CardType::STATUS;

        if (matches) {
            allSorted.push_back(c);
        }
    }

    std::sort(allSorted.begin(), allSorted.end(), cardLessThanById);


    std::array<std::vector<Card>,3> vecs = {};

    for (int rarity = 0; rarity < 3; ++rarity) {
        for (auto x : allSorted) {
            if (cardRarities[(int)x] == (CardRarity)rarity) {
                vecs[rarity].push_back(x);
            }
        }
    }

    std::cout << "{ ";
    for (int i = 0; i < 3; ++i) {
        for (auto x : vecs[i]) {
            std::cout << "Card::" << cardEnumNames[(int)x] << ',';
        }
    }
    std::cout << " };";
    std::cout << vecs[0].size() << '\n';
    std::cout << vecs[1].size() << '\n';
    std::cout << vecs[2].size() << '\n';

}


int main(int argc, const char ** argv) {

    std::string seedStr = "1234567";
    std::int64_t seed = SeedHelper::getLong(seedStr);
    Map map = Map::fromSeed(seed, 0, 1);
    std::cout << seedStr  << '\n';
    std::cout << map.toString() << '\n';
    GameState gs = GameState::createGameState(seed, 0);

    gs.initEnemies();



//
//    gs.floor = 1;
//    auto r = gs.getCombatRewards(sts::Room::MONSTER, false);
//    std::cout << r.toString() << '\n';
//
//    gs.floor = 2;
//    r = gs.getCombatRewards(sts::Room::MONSTER, false);
//    std::cout << r.toString() << '\n';
//
//    gs.floor = 3;
//    auto ss = gs.getShopScreen();
//    std::cout << ss.toString(true) << '\n';
//
//    gs.floor = 4;
//    r = gs.getCombatRewards(sts::Room::MONSTER, false);
//    std::cout << r.toString() << '\n';
//
//    gs.floor = 5;
//    r = gs.getCombatRewards(sts::Room::MONSTER, false);
//    std::cout << r.toString() << '\n';


//    describeSeeds({SeedHelper::getLong("DCBWYBYGSM")});
//    runCandidateFilter();

    return 0;
}
