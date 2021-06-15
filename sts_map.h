//
// Created by keega on 6/11/2021.
//

#ifndef STS_SEED_SEARCH_STS_MAP_H
#define STS_SEED_SEARCH_STS_MAP_H


#include "sts_impl.h"
#include <string>
#include <iostream>

//#define SINGLE_PATH

namespace sts {

    enum class Room {
        SHOP=0,
        REST,
        EVENT,
        ELITE,
        MONSTER,
        TREASURE,
        NONE,
    };

    struct MapNode {
        int x;
        int y;
        int parentCount = 0;
        std::array<int, 6> parents;
        int edgeCount = 0;

#ifdef SINGLE_PATH
        std::array<int, 1> edges;
        Room room;
#else
        int maxXParent = -1;
        int minXParent = 0x7FFFFFFF;
        std::array<int, 3> edges;
        Room room = Room::NONE;
#endif


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


        std::string toString(bool showRoomSymbols) const;
    };

    void generateMap(Map &map, Random &mapRng);

    void mapTest(std::int64_t seed);

    void printStats();

    bool testSeedForSinglePath(std::int64_t seed, int length);

    std::vector<std::int64_t> findSinglePathSeeds(std::int64_t start, std::int64_t count, int length);

    int getPathSingleLength(std::int64_t seed);

    int getPathTotalSingleLength(std::int64_t seed);

    int getForcedMonsterFightCount(std::int64_t seed);
    bool isForcedMonsterIntoEliteFight(std::int64_t seed);

    void printOutComes();
}




#endif //STS_SEED_SEARCH_STS_MAP_H
