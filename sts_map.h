//
// Created by keega on 6/11/2021.
//

#ifndef STS_SEED_SEARCH_STS_MAP_H
#define STS_SEED_SEARCH_STS_MAP_H


#include "sts_impl.h"
#include <string>
#include <iostream>

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
        int maxXParent = -1;
        int minXParent = 0x7FFFFFFF;

        int edgeCount = 0;
        std::array<int, 3> edges;

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


        std::string toString(bool showRoomSymbols) const;
    };

    void generateMap(Map &map, Random &mapRng);

    void mapTest();

    void printStats();

}




#endif //STS_SEED_SEARCH_STS_MAP_H
