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
        NONE,
        EVENT,
        MONSTER,
        ELITE,
        BURNING_ELITE,
        REST,
        SHOP,
        TREASURE,
    };

    struct Edge {
        int srcX = 0;
        int srcY = -1;
        int dstX = 0;
        int dstY = 0;

        Edge() = default;
        Edge(int srcX, int srcY, int dstX, int dstY) : srcX(srcX), srcY(srcY), dstX(dstX), dstY(dstY) {}
    };



    struct MapNode {
        int x;
        int y;
        int parentCount = 0;
        std::array<MapNode*, 6> parents;
        int edgeCount = 0;
        std::array<Edge, 3> edges;

        Room room = Room::NONE;


        char getRoomSymbol() const;

        void addParent(MapNode *node);
        void addEdge(Edge edge);
        Edge &getMaxEdge();
        Edge &getMinEdge();
        MapNode *getMaxXParent();
        MapNode *getMinXParent();
    };

    struct Map {
        std::array<std::array<MapNode, 7>, 15> rooms;
        MapNode &getNode(int x, int y);

        std::string toString(bool showRoomSymbols) const;
    };

    void generateMap(Map &map, Random mapRng);

    void mapTest();

}




#endif //STS_SEED_SEARCH_STS_MAP_H
