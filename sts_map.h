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
        int edgeCount = 0;
        std::array<int, 3> edges;

        Room room = Room::NONE;

        char getRoomSymbol() const;

        void addParent(int parentX);
        void addEdge(int edge);

        int &getMaxEdge();
        int &getMinEdge();
        int getMaxXParent() const;
        int getMinXParent() const;
    };

    struct Map {
        std::array<std::array<MapNode, 7>, 15> nodes;
        MapNode &getNode(int x, int y);

        std::string toString(bool showRoomSymbols) const;
    };

    void generateMap(Map &map, Random &mapRng);

    void mapTest();

}




#endif //STS_SEED_SEARCH_STS_MAP_H
