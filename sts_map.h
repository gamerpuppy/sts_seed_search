//
// Created by keega on 6/11/2021.
//

#ifndef STS_SEED_SEARCH_STS_MAP_H
#define STS_SEED_SEARCH_STS_MAP_H


#include "sts_impl.h"
#include <string>
#include <iostream>
#include <functional>
#include <set>

//#define SINGLE_PATH

namespace sts {

    enum class Room {
        SHOP = 0,
        REST,
        EVENT,
        ELITE,
        MONSTER,
        TREASURE,
        BOSS,
        NONE,
    };

    enum class EliteBuff {
        STRENGTH = 0,
        MAX_HP,
        METALLICIZE, 
        REGENERATE, 
        NONE,
    };

    static const char* roomStrings[] = {
        "SHOP",
        "REST",
        "EVENT",
        "ELITE",
        "MONSTER",
        "TREASURE",
        "BOSS",
        "NONE",
    };

    static const char* eliteBuffStrings[] = {
        "STRENGTH",
        "MAX_HP",
        "METALLICIZE", 
        "REGENERATE", 
        "NONE",
    };

    char getRoomSymbol(Room);

    struct MapNode {
        int8_t x;
        int8_t y;

        int8_t parentCount = 0;
        std::array<int8_t, 6> parents;
        int8_t parentBits = 0;
        int8_t parentMults[7] = {};
        

        int8_t edgeCount = 0;
        std::array<int8_t, 3> edges;
        int8_t edgeBits = 0;

        int maxXParent = -1;
        int minXParent = 0x7FFFFFFF;
        Room room = Room::NONE;

        void addParent(int8_t parent);
        void addEdge(int8_t edge);
        char getRoomSymbol() const;
        int8_t getMaxEdge() const;
        int8_t getMinEdge() const;
        int8_t getMaxXParent() const;
        int8_t getMinXParent() const;
    };

    struct Map {
        
        /*
        NEIGH is used in cPANX and gCA
        c = NEIGH[a][b] means:
            a in {0, ..., 112} is the set of neighbors of a node as bits
                valid neighborhoods are always intervals of length 0, 1, 2, or 3
            b in {0, 1} indicates whether we want the min or max neighbor
            c in {0, ..., 8} indicates information of the min or max neighbor
                {0, ..., 6}: the min or max neighbor
                {7, 8} a useful convention to indicate invalid or empty neighborhoods
                
        */
        static constexpr int8_t NEIGH[113][2] = {7,8,0,0,1,1,0,1,2,2,0,2,1,2,0,2,3,3,7,8,1,3,7,8,2,3,7,8,1,3,7,8,4,4,7,8,7,8,7,8,2,4,7,8,7,8,7,8,3,4,7,8,7,8,7,8,2,4,7,8,7,8,7,8,5,5,7,8,7,8,7,8,7,8,7,8,7,8,7,8,3,5,7,8,7,8,7,8,7,8,7,8,7,8,7,8,4,5,7,8,7,8,7,8,7,8,7,8,7,8,7,8,3,5,7,8,7,8,7,8,7,8,7,8,7,8,7,8,6,6,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,4,6,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,5,6,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,4,6};

        int8_t burningEliteX = -1;
        int8_t burningEliteY = -1;
        bool isBad = false;
        int8_t firstFloorSixX = -1;
        EliteBuff eliteBuff = EliteBuff::NONE;
        std::array<std::array<MapNode, 7>, 15> nodes;

        MapNode &getNode(int8_t x, int8_t y);
        const MapNode &getNode(int8_t x, int8_t y) const;

        std::string toString(bool showRoomSymbols=true) const;
        static Map fromSeed(std::int64_t seed, int ascension= 0, int act= 1, bool assignBurningElite=false, bool isBadMap=false);

        void normalizeParents();
    };

    struct Path {
        static constexpr std::uint64_t roomContainBits[] {
          0x0111111111111111LL,
          0x0222222222222222LL,
          0x0333333333333333LL,
          0x0444444444444444LL,
          0x0555555555555555LL,
          0x0666666666666666LL,
          0x0777777777777777LL,
          0x0888888888888888LL,
        };

        static constexpr std::uint64_t defaultBitsValue = 0xF888888888888888LL;
        std::uint64_t bits = defaultBitsValue;

        Path() : bits(defaultBitsValue) {};
        explicit Path (std::uint64_t bits) : bits(bits) {};
        explicit Path(Room room) : bits(static_cast<uint64_t>(room)+1) {};
        Path(const Path &rhs) = default;

        static Path fromBits(std::uint64_t);
        static Path fromString(const std::string&);
        static Path fromString(const std::string&, int idxOfBurningElite);

        bool operator<(const Path&) const;
        bool contains(Room room) const;

        [[nodiscard]] int getIdxOfBurningElite() const;
        [[nodiscard]] Path setIdxOfBurningElite(int idx) const;
        [[nodiscard]] Room roomAt(int y) const;
        [[nodiscard]] Path addRoom(Room room, int y) const;
        [[nodiscard]] std::string toString(int begin=0, int end=15) const;
        [[nodiscard]] std::string toPrettyString() const;
    };

    typedef std::function<int(MapNode)> NodePredicate;
    typedef std::function<bool(Path)> PathPredicate;
    typedef std::function<bool(Path path, Room nextRoom, int pathLength)> PathBuilderPredicate;

    void generateMap(Map &map, Random &mapRng);
    void assignBurningElite(Map &map, Random &mapRng);

    void mapTest(std::int64_t seed);

    void printStats();

    bool testSeedForSinglePath(std::int64_t seed, int length);

    std::vector<std::int64_t> findSinglePathSeeds(std::int64_t start, std::int64_t count, int length);

    int getPathSingleLength(std::int64_t seed);

    int getPathTotalSingleLength(std::int64_t seed);

    bool isForcedMonsterIntoEliteFight(std::int64_t seed);

    int getMinMapWeight(const Map &map, NodePredicate predicate);
    int getMaxMapWeight(const Map &map, NodePredicate predicate);

    std::set<Path> getUniquePaths(const Map &map);
    std::set<Path> getPathsMatching(const Map&, const PathBuilderPredicate &);
    Path getLeftMostPath(const Map& map, int length=15);



}

#endif //STS_SEED_SEARCH_STS_MAP_H
