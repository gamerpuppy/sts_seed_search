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

    char getRoomSymbol(Room);

    struct MapNode {
        int x;
        int y;

        int parentCount = 0;
        std::array<int, 6> parents;

        int edgeCount = 0;
        std::array<int, 3> edges;

        int maxXParent = -1;
        int minXParent = 0x7FFFFFFF;
        Room room = Room::NONE;

        void addParent(int parent);
        void addEdge(int edge);
        char getRoomSymbol() const;
        int getMaxEdge() const;
        int getMinEdge() const;
        int getMaxXParent() const;
        int getMinXParent() const;
    };

    struct Map {
        std::array<std::array<MapNode, 7>, 15> nodes;

        MapNode &getNode(int x, int y);
        const MapNode &getNode(int x, int y) const;

        std::string toString(bool showRoomSymbols=true) const;
        static Map fromSeed(std::int64_t seed, int ascension= 0, int act= 1);

        void normalizeParents();
    };

    struct Path {
        static constexpr std::int64_t roomContainBits[] {
          0x0111111111111111LL,
          0x0222222222222222LL,
          0x0333333333333333LL,
          0x0444444444444444LL,
          0x0555555555555555LL,
          0x0666666666666666LL,
          0x0777777777777777LL,
          0x0888888888888888LL,
        };

        static constexpr std::int64_t defaultBitsValue = 0x0888888888888888LL;
        std::int64_t bits = defaultBitsValue;

        Path() : bits(defaultBitsValue) {};
        explicit Path (std::int64_t bits) : bits(bits) {};
        explicit Path(Room room) : bits(static_cast<int64_t>(room)+1) {};
        Path(const Path &rhs) = default;

        static Path fromBits(std::int64_t);
        static Path fromString(const std::string&);

        bool operator<(const Path&) const;
        bool contains(Room room) const;

        [[nodiscard]] Room roomAt(int y) const;
        [[nodiscard]] Path addRoom(Room room, int y) const;
        [[nodiscard]] std::string toString() const;
    };

    typedef std::function<int(MapNode)> NodePredicate;
    typedef std::function<bool(Path)> PathPredicate;
    typedef std::function<bool(Path path, Room nextRoom, int pathLength)> PathBuilderPredicate;

    void generateMap(Map &map, Random &mapRng);

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



}

#endif //STS_SEED_SEARCH_STS_MAP_H
