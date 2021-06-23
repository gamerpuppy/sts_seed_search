
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



int main(int argc, const char ** argv) {

    runNormalSearch();

//    std::uint64_t seed = 1;
//    auto vec = testSeedsMt(1, 100, 8, [](auto seed) {
//        return Neow::generateRewards(seed).at(1).r == Neow::Reward::THREE_ENEMY_KILL;
//    });
//    for (auto x : vec) {
//        std::cout << SeedHelper::getString(x) << '\n';
//    }

//    std::string seedStr = "4";
//    std::int64_t seed = SeedHelper::getLong(seedStr);
//    Map map = Map::fromSeed(seed, 0, 1);
//    std::cout << seedStr  << '\n';
//    std::cout << map.toString() << '\n';
//    GameState gs = GameState::createGameState(seed, 0);
//
//    gs.initEnemies();
//
//    for (int i = 0; i < gs.monsterListSize; ++i) {
//        std::cout << monsterEncounterStrings[(int)gs.monsterList[i]] << ", ";
//    }
//    std::cout << '\n';
//
//    for (int i = 0; i < gs.eliteMonsterListSize; ++i) {
//        std::cout << monsterEncounterStrings[(int)gs.eliteMonsterList[i]] << ", ";
//    }
//    std::cout << '\n';
//
//    std::cout << monsterEncounterStrings[(int)gs.boss] << '\n';
//
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
//    auto event = gs.getEventRoomEvent();
//    std::cout << eventStrings[(int)event] << '\n';
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
//

//    describeSeeds({SeedHelper::getLong("DCBWYBYGSM")});
//    runCandidateFilter();

    return 0;
}
