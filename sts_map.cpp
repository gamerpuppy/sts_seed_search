//
// Created by keega on 6/11/2021.
//

#include "sts_map.h"
#include "java_random.h"

#include <cassert>
#include <cmath>

using namespace sts;

constexpr int MAP_HEIGHT = 15;
constexpr int MAP_WIDTH = 7;
constexpr int PATH_DENSITY = 6;

constexpr int MIN_ANCESTOR_GAP = 3;
constexpr int MAX_ANCESTOR_GAP = 5;

constexpr int ROW_END_NODE = MAP_WIDTH-1;

constexpr float SHOP_ROOM_CHANCE = 0.05F;
constexpr float REST_ROOM_CHANCE = 0.12F;
constexpr float TREASURE_ROOM_CHANCE = 0.0f;
constexpr float EVENT_ROOM_CHANCE = 0.22f;

constexpr float ELITE_ROOM_CHANCE = 0.08f;
//constexpr float ELITE_ROOM_CHANCE_A0 = 0.08f;
//constexpr float ELITE_ROOM_CHANCE_A1 = ELITE_ROOM_CHANCE_A0 * 1.6f;


MapNode &Map::getNode(int x, int y) {
    return nodes.at(y).at(x);
}

const MapNode &Map::getNode(int x, int y) const {
    return nodes.at(y).at(x);
}

static inline int randRange(Random &rng, int min, int max) {
    return rng.random(max - min) + min;
}

inline void insertEdge(MapNode &mapNode, int dstX, int idx) {
    for (int x = mapNode.edgeCount; x > idx; --x) {
        mapNode.edges[x] = mapNode.edges[x-1];
    }
    mapNode.edges[idx] = dstX;
    ++mapNode.edgeCount;
}

char MapNode::getRoomSymbol() const {
    switch(room) {
        case Room::NONE: return 'N';
        case Room::EVENT: return '?';
        case Room::MONSTER: return 'M';
        case Room::ELITE: return 'E';
//        case Room::BURNING_ELITE:
        case Room::REST: return 'R';
        case Room::SHOP: return '$';
        case Room::TREASURE: return 'T';
        default: return 'I';
    }
}

void MapNode::addParent(int parent) {
    parents[parentCount++] = parent;

    maxXParent = std::max(parent, maxXParent);
    minXParent = std::min(parent, minXParent);

//    if (parent > maxXParent) {
//        maxXParent = parent;
//    }
//    if (parent < minXParent) {
//        minXParent = parent;
//    }

//    lastParentAdded = parent;
//    ++totalParentsAdded;
//
//    int cur = 0;
//    while (true) {
//        if (cur == parentCount) {
//            parents[cur] = parent;
//            ++parentCount;
//            return;
//        }
//
//        if (parent == parents[cur]) {
//            return;
//        }
//
//        if (parent < parents[cur]) {
//            for (int i = parentCount; i > cur; --i) {
//                parents[i] = parents[i-1];
//            }
//            parents[cur] = parent;
//            ++parentCount;
//            return;
//        }
//        ++cur;
//    }
}

inline void MapNode::addEdge(int edge) {
    int cur = 0;
    while (true) {
        if (cur == edgeCount) {
            edges[cur] = edge;
            ++edgeCount;
            return;
        }

        if (edge == edges[cur]) {
            return;
        }

        if (edge < edges[cur]) {
            insertEdge(*this, edge, cur);
            return;
        }
        ++cur;
    }
}

inline int MapNode::getMaxEdge() const {
//    assert(edgeCount > 0);
    return edges.at(edgeCount-1);
}

inline int MapNode::getMinEdge() const {
//    assert(edgeCount > 0);
    return edges.at(0);
}

inline int MapNode::getMaxXParent() const {
//    assert(parentCount > 0);
    return maxXParent;

//    int maxParent = parents[0];
//    for (int i = 1; i < parentCount; i++) {
//        if (parents[i] > maxParent) {
//            maxParent = parents[i];
//        }
//    }
//    return maxParent;
}

inline int MapNode::getMinXParent() const {
//    assert(parentCount > 0);
    return minXParent;

//    int minParent = parents[0];
//    for (int i = 1; i < parentCount; i++) {
//        if (parents[i] < minParent) {
//            minParent = parents[i];
//        }
//    }
//    return minParent;
}

void removeEdge(MapNode &node, int idx) {
    for (int i = idx; i < node.edgeCount-1; i++) {
        std::swap(node.edges[i], node.edges[i+1]);
    }
    --node.edgeCount;
}

void removeParentAtIdx(MapNode &node, int parentIdx) {
    for (int i = parentIdx; i < node.parentCount-1; ++i) {
        node.parents[i] = node.parents[i+1];
    }
    --node.parentCount;
}

void removeParent(MapNode &node, int parent) {
    for (int i = node.parentCount-1; i >= 0; --i) {
        if (node.parents[i] == parent) {
            removeParentAtIdx(node, i);
        }
    }
}

void filterRedundantEdgesFromFirstRow(Map &map) {
    bool nodesVisited[MAP_WIDTH] = {false};
    for (auto &node : map.nodes.at(0)) {
        for (int i = node.edgeCount-1; i >= 0 ; --i) {
            int x = node.edges[i];
            if (nodesVisited[x]) {
                removeParent(map.getNode(x, 1), node.x);
                removeEdge(node, i);
            } else {
                nodesVisited[x] = true;
            }
        }
    }
}

inline int getCommonAncestor(const Map &map, int x1, int x2, int y) {
    if (y < 0) {
        return -1;
    }

    int l_node;
    int r_node;
    if (x1 < y) {
        l_node = x1;
        r_node = x2;
    } else {
        l_node = x2;
        r_node = x1;
    }

    if (map.getNode(l_node, y).parentCount == 0 || map.getNode(r_node, y).parentCount == 0) {
        return -1;
    }

    int leftX = map.getNode(l_node, y).getMaxXParent();
    if (leftX == map.getNode(r_node, y).getMinXParent()) {
        return leftX;
    }
    return -1;
}


inline int choosePathParentLoopRandomizer(const Map &map, Random &rng, int curX, int curY, int newX) {
    const MapNode &newEdgeDest = map.getNode(newX, curY + 1);

    for (int i = 0; i < newEdgeDest.parentCount; i++) {
        int parentX = newEdgeDest.parents.at(i);
        if (curX == parentX) {
            continue;
        }
        if (getCommonAncestor(map, parentX, curX, curY) == -1) {
            continue;
        }

        if (newX > curX) {
            newX = curX + randRange(rng, -1, 0);
            if (newX < 0) {
                newX = curX;
            }
        } else if (newX == curX) {
            newX = curX + randRange(rng, -1, 1);
            if (newX > ROW_END_NODE) {
                newX = curX - 1;
            } else if (newX < 0) {
                newX = curX + 1;
            }
        } else {
            newX = curX + randRange(rng, 0, 1);
            if (newX > ROW_END_NODE) {
                newX = curX;
            }
        }
    }

    return newX;
}

inline int choosePathAdjustNewX(const Map &map, int curX, int curY, int newEdgeX) {
    if (curX != 0) {
        auto right_node = map.getNode(curX - 1, curY);
        if (right_node.edgeCount > 0) {
            int left_edge_of_right_node = right_node.getMaxEdge();
            if (left_edge_of_right_node > newEdgeX) {
                newEdgeX = left_edge_of_right_node;
            }
        }
    }

    if (curX < ROW_END_NODE) {
        auto right_node = map.getNode(curX + 1, curY);
        if (right_node.edgeCount > 0) {
            int left_edge_of_right_node = right_node.getMinEdge();
            if (left_edge_of_right_node < newEdgeX) {
                newEdgeX = left_edge_of_right_node;
            }
        }
    }
    return newEdgeX;
}


int chooseNewPath(Map &map, Random &rng, int curX, int curY) {
    MapNode &currentNode = map.getNode(curX, curY);

    int min;
    int max;
    if (curX == 0) {
        min = 0;
        max = 1;
    } else if (curX == ROW_END_NODE) {
        min = -1;
        max = 0;
    } else {
        min = -1;
        max = 1;
    }

    int newEdgeX = curX + randRange(rng, min, max);
    newEdgeX = choosePathParentLoopRandomizer(map, rng, curX, curY, newEdgeX);
    newEdgeX = choosePathAdjustNewX(map, curX, curY, newEdgeX);

   return newEdgeX;
}

void createPathsIteration(Map &map, Random &rng, int startX) {
    int curX = startX;
    for (int curY = 0; curY < MAP_HEIGHT-1; ++curY) {
        int newX = chooseNewPath(map, rng, curX, curY);
        map.getNode(curX, curY).addEdge(newX);
        map.getNode(newX, curY+1).addParent(curX);
        curX = newX;
    }
    map.getNode(curX, 14).addEdge(3);
}

void createPaths(Map &map, Random &mapRng) {
    int firstStartX = randRange(mapRng, 0, MAP_WIDTH - 1);
    createPathsIteration(map, mapRng, firstStartX);

    for(int i = 1; i < PATH_DENSITY; ++i) {
        int startX = randRange(mapRng, 0, MAP_WIDTH - 1);

        while(startX == firstStartX && i == 1) {
            startX = randRange(mapRng, 0, MAP_WIDTH - 1);
        }

        createPathsIteration(map, mapRng, startX);
    }
}

std::string paddingGenerator(int length) {
    std::string ret;
    for(int i = 0; i < length; ++i) {
        ret += ' ';
    }
    return ret;
}

std::string Map::toString(bool showRoomSymbols) const {
    std::string str;

    int lastRow = 14;
    int left_padding_size = 5;

    for(int row_num = 14; row_num >= 0; row_num--) {
        str.append("\n ").append(paddingGenerator(left_padding_size));


        for (auto &node : nodes.at(row_num)) {
            std::string right = " ";
            std::string mid = " ";
            std::string node_symbol = " ";

            for (int i = 0; i < node.edgeCount; ++i) {
                const int edge = node.edges[i];
                if (edge < node.x) {
                    node_symbol = "\\";
                }

                if (edge == node.x) {
                    mid = "|";
                }

                if (edge > node.x) {
                    right = "/";
                }
            }
            str.append(node_symbol).append(mid).append(right);
        }

        str.append("\n").append(std::to_string(row_num)).append(" ");
        str.append(paddingGenerator(left_padding_size - (int)std::to_string(row_num).length()));

        for (auto &node : nodes.at(row_num)) {
            std::string node_symbol = " ";

            if (row_num == lastRow) {
                for (auto &lower_node : nodes.at(row_num - 1)) {
                    for (int i = 0; i < lower_node.edgeCount; i++) {
                        if (lower_node.edges[i] == node.x) {
                            node_symbol = showRoomSymbols ? node.getRoomSymbol() : '*';
                        }
                    }
                }
            } else {
                if (node.edgeCount > 0) {
                    node_symbol = showRoomSymbols ? node.getRoomSymbol() : '*';
                }
            }
            str.append(" ").append(node_symbol).append(" ");
        }
    }

    return str;
}

struct RoomCounts {
    float total = 0;
    int unassigned = 0;
};

RoomCounts  getRoomCountsAndAssignFixed(Map &map) {
    const int monsterRow = 0;
    const int treasureRow = 8;

    const int restRow = static_cast<int>(MAP_HEIGHT-1);
    const int restRowBug = static_cast<int>(MAP_HEIGHT-2);

    RoomCounts counts;
    for (int row = 0; row < MAP_HEIGHT; ++row) {

        for (auto &node : map.nodes.at(row)) {
            if (node.edgeCount <= 0) {
                continue;
            }

            switch (row) {
                case monsterRow:
                    node.room = Room::MONSTER;
                    ++counts.total;
                    break;

                case treasureRow:
                    node.room = Room::TREASURE;
                    ++counts.total;
                    break;

                case restRow:
                    node.room = Room::REST;
                    ++counts.total;
                    break;

                case restRowBug:
                    ++counts.unassigned;
                    break;

                default:
                    ++counts.unassigned;
                    ++counts.total;
            }
        }
    }

    return counts;
}

void fillRoomArray(Room *arr, RoomCounts counts) {

    int shopCount = static_cast<int>(std::round(counts.total * SHOP_ROOM_CHANCE));
    int restCount = static_cast<int>(std::round(counts.total * REST_ROOM_CHANCE));
    int treasureCount = static_cast<int>(std::round(counts.total * TREASURE_ROOM_CHANCE));
    int eliteCount = static_cast<int>(std::round(counts.total * ELITE_ROOM_CHANCE));
    int eventCount = static_cast<int>(std::round(counts.total * EVENT_ROOM_CHANCE));

    int i = 0;
    int end = shopCount;
    for (; i < shopCount; ++i) {
        arr[i] = Room::SHOP;
    }

    end += restCount;
    for (; i < end; ++i) {
        arr[i] = Room::REST;
    }

    end += treasureCount;
    for (; i < end; ++i) {
        arr[i] = Room::TREASURE;
    }


    end += eliteCount;
    for (; i < end; ++i) {
        arr[i] = Room::ELITE;
    }

    end += eventCount;
    for (; i < end; ++i) {
        arr[i] = Room::EVENT;
    }

    assert(i < counts.total); // this means that a really weird map was generated?>? is this possible?
    for (; i < counts.unassigned; ++i) {
        arr[i] = Room::MONSTER;
    }

}

struct RoomConstructorData {
    Room *rooms;
    int roomCount;
    int offset = 0;

    std::uint64_t rowData = 0;
    std::uint64_t prevRowData;

    std::uint64_t siblingMasks[MAP_WIDTH] = {0};
    std::uint64_t nextSiblingMasks[MAP_WIDTH] = {0};

    std::uint64_t parentMasks[MAP_WIDTH] = {0};
    std::uint64_t nextParentMasks[MAP_WIDTH] = {0};

    constexpr static std::uint64_t masks[] {
            0x0101010101010101ULL,
            0x0202020202020202ULL,
            0x0404040404040404ULL,
            0x0808080808080808ULL,
            0x1010101010101010ULL,
            0x2020202020202020ULL,
            0x4040404040404040ULL
    };


    RoomConstructorData(Room *rooms, int roomCount) : rooms(rooms), roomCount(roomCount) {}

    void setData(const MapNode &node) {
        if (node.edgeCount == 1) {
            for (int i = 0; i < node.edgeCount; i++) {
                nextParentMasks[node.edges[i]] |= 0xFFULL << (node.x*8);
            }

        } else {
            std::uint64_t siblingMask = 0;
            for (int i = 0; i < node.edgeCount; i++) {
                int edge = node.edges[i];
                siblingMask |= 0xFFULL << (node.edges[i]*8U);
                nextSiblingMasks[edge] |= siblingMask;
                nextParentMasks[edge] |= 0xFFULL << (node.x*8U);
            }
        }
    }

    void setCurDataOnly(const MapNode &node) {
        rowData |= 1ULL << ((unsigned int)node.room + node.x*8U);
    }

    void setNextDataOnly(const MapNode &node) {
        if (node.edgeCount == 1) {
            for (int i = 0; i < node.edgeCount; i++) {
                nextParentMasks[node.edges[i]] |= 0xFFULL << (node.x*8U);
            }

        } else {
            std::uint64_t siblingMask = 0;
            for (int i = 0; i < node.edgeCount; i++) {
                int edge = node.edges[i];
                siblingMask |= 0xFFULL << (node.edges[i]*8U);
                nextSiblingMasks[edge] |= siblingMask;
                nextParentMasks[edge] |= 0xFFULL << (node.x*8U);
            }
        }
    }

    void removeElement(int idx) {
        for (int i = idx; i > offset; --i) {
            rooms[i] = rooms[i-1];
        }
        ++offset;
    }

    void nextRow() {
        prevRowData = rowData;
        rowData = 0;

        for (int i = 0; i < MAP_WIDTH; i++) {
            siblingMasks[i] = nextSiblingMasks[i];
            nextSiblingMasks[i] = 0;

            parentMasks[i] = nextParentMasks[i];
            nextParentMasks[i] = 0;
        }
    }


};

bool doesSiblingMatch(const RoomConstructorData &data, int nodeX, Room roomToBeSet) {
    return data.rowData & data.siblingMasks[nodeX] & RoomConstructorData::masks[(int)roomToBeSet];
}

bool doesParentMatch(const RoomConstructorData &data, int nodeX, Room roomToBeSet) {
    return data.prevRowData & data.parentMasks[nodeX] & RoomConstructorData::masks[(int)roomToBeSet];
}

void assignRoomToNode(Map &map, MapNode &node, RoomConstructorData &data) {
    bool triedAssignRoom[5] = { false };

    for (int i = data.offset; i < data.roomCount; i++) {
        Room room = data.rooms[i];

        if (triedAssignRoom[(int)room]) {
            continue;
        }
        triedAssignRoom[(int)room] = true;

        switch (room) {
            case Room::SHOP:
                break;

            case Room::ELITE:
                if (node.y <= 4) {
                    continue;
                }
                break;

            case Room::REST:
                if (node.y <= 4) {
                    continue;
                }
                if (node.y >= 13) {
                    continue;
                }
                break;

            case Room::EVENT:
                if (doesSiblingMatch(data, node.x, room)) {
                    continue;
                } else {
                    node.room = Room::EVENT;
                    data.rowData |= 1ULL << ((unsigned int)Room::EVENT + node.x*8U);
                    data.removeElement(i);
                    return;
                }

            case Room::MONSTER:
                if (doesSiblingMatch(data, node.x, room)) {
                   continue;
                }
                node.room = Room::MONSTER;
                data.rowData |= 1ULL << ((unsigned int)Room::MONSTER + node.x*8U);
                data.removeElement(i);
                return;

            default:
                break;
        }

        bool canSet = !doesParentMatch(data, node.x, room)
                      && !doesSiblingMatch(data, node.x, room);
        if (canSet) {
            node.room = room;
            data.rowData |= 1ULL << ((unsigned int)node.room + node.x*8U);
            data.removeElement(i);
            return;
        }
    }

    node.room = sts::Room::MONSTER;
}

void assignRoomsRow(Map &map, RoomConstructorData &data, int row) {
    for (auto &node : map.nodes.at(row)) {
        if (node.edgeCount <= 0) {
            continue;
        }

        if (row == 0 || row == 8) {
            data.setNextDataOnly(node);
        } else if (row == 7 || row == 13) {
            assignRoomToNode(map, node, data);
            data.setCurDataOnly(node);
        } else {
            assignRoomToNode(map, node, data);
            data.setData(node);
        }
    }
    data.nextRow();
}

// idea: remove rooms basically in reverse, shifting the head of the array forward instead
void assignRoomsToNodes(Map &map, Room *rooms, int roomsSize) {
    RoomConstructorData data(rooms, roomsSize);
    for (int row = 0; row < MAP_HEIGHT-1; ++row) {
        assignRoomsRow(map, data, row);
    }
}

void assignRooms(Map &map, Random &rng) {
    RoomCounts counts = getRoomCountsAndAssignFixed(map);

    Room rooms[counts.unassigned];
    fillRoomArray(rooms, counts);

    for (int i=counts.unassigned; i>1; i--) {
        std::swap(rooms[i-1], rooms[rng.nextInt(i)]);
    }

    assignRoomsToNodes(map, rooms, counts.unassigned);
//    lastMinuteNodeChecker(map);
    return;
}

void initNodes(Map &map) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            auto &node = map.nodes.at(y).at(x);
            node.x = x;
            node.y = y;
        }
    }
}

void normalizeMap(Map &map) {
    int newIndices[MAP_HEIGHT][MAP_WIDTH];

    Map copy = map;

    for (int r = MAP_HEIGHT-1; r >= 0; --r) {
        std::array<MapNode, MAP_WIDTH> &row = map.nodes.at(r);
        int open = 0;

        for (int c = 0; c < MAP_WIDTH; ++c) {
            MapNode &cur = row.at(c);
            if (cur.edgeCount <= 0) {
                ++open;
                continue;
            }


            if (r != MAP_HEIGHT-1) {
                for (int e = 0; e < cur.edgeCount; ++e) {
                    cur.edges[e] = newIndices[r+1][cur.edges[e]];
                }
            }

            if (open > 0) {
                row.at(c-open) = cur;
                row.at(c-open).x = c-open;
                cur.edgeCount = 0;
                newIndices[r][c] = c-open;
            } else {
                newIndices[r][c] = c;
            }
        }
    }

    for (int r = MAP_HEIGHT-1; r > 0; --r) {

        std::array<MapNode, MAP_WIDTH> &row = map.nodes.at(r);
        for (int c = 0; c < MAP_WIDTH; ++c) {
            MapNode &node = row.at(c);
            if (node.edgeCount == 0) {
                break;
            }
            int count = 0;
            bool haveSeen[MAP_WIDTH] = {false};
            for (int p = 0; p < node.parentCount; ++p) {
                int parent = node.parents[p];
                if (!haveSeen[parent]) {
                    node.parents[count++] = newIndices[r-1][parent];
                    haveSeen[parent] = true;
                }
            }
            node.parentCount = count;
        }
    }
}

void sts::generateMap(Map &map, sts::Random &mapRng) {
    initNodes(map);
    createPaths(map, mapRng);
    filterRedundantEdgesFromFirstRow(map);
    assignRooms(map, mapRng);
}





void sts::printStats() {
//    std::cout << "total same parents " << totalSameParents << std::endl;
}

void sts::mapTest() {
//    for (std::int64_t seed = 0; seed < 10000; seed++) {
//        sts::Map map;
//        sts::generateMap(map, sts::Random(seed+1));
//    }

    std::int64_t seed =     273;
//    std::int64_t seed = 8;
    sts::Random mapRng(seed+1);
    sts::Map map;
    sts::generateMap(map, mapRng);
    std::cout << map.toString(true) << std::endl;



//    for (std::int64_t seed = 1; seed < 1000; seed++) {
//        sts::Random mapRng(seed+1);
//        sts::Map map;
//        sts::generateMap(map, mapRng);
//        std::cout << (map.getNode(0,13).room == Room::EVENT ? 1 : 0) << std::endl;
////        std::cout << seed << std::endl;
////        std::cout << map.toString(true) << std::endl;
//    }


}


int chooseNewPathFirstTest(Map &map, Random &rng, int curX, int curY) {
    MapNode &currentNode = map.getNode(curX, curY);

    int min;
    int max;
    if (curX == 0) {
        min = 0;
        max = 1;
    } else if (curX == ROW_END_NODE) {
        min = -1;
        max = 0;
    } else {
        min = -1;
        max = 1;
    }

    return curX + randRange(rng, min, max);
}

void createSinglePathTestFirstIteration(Map &map, Random &rng, int startX) {
    int curX = startX;
    for (int curY = 0; curY < MAP_HEIGHT-1; ++curY) {
        int newX = chooseNewPathFirstTest(map, rng, curX, curY);
        auto &nextNode = map.getNode(newX, curY+1);
        map.getNode(curX, curY).addEdge(newX);
        map.getNode(newX, curY+1).addParent(curX);
        curX = newX;
    }
    map.getNode(curX, 14).addEdge(3);
}


inline int chooseNewSinglePathTest(Map &map, Random &rng, int curX, int curY) {
    MapNode &currentNode = map.getNode(curX, curY);

    int min;
    int max;
    if (curX == 0) {
        min = 0;
        max = 1;
    } else if (curX == ROW_END_NODE) {
        min = -1;
        max = 0;
    } else {
        min = -1;
        max = 1;
    }

    int newEdgeX = curX + randRange(rng, min, max);
    newEdgeX = choosePathParentLoopRandomizer(map, rng, curX, curY, newEdgeX);
    return newEdgeX;
}

bool createSinglePathTestIteration(Map &map, Random &rng, int startX, int length) {
    int curX = startX;
    for (int curY = 0; curY < MAP_HEIGHT-1; ++curY) {
        int newX = chooseNewSinglePathTest(map, rng, curX, curY);


        auto &nextNode = map.getNode(newX, curY+1);
        if (curY < length && nextNode.parentCount == 0) {
            return false;
        }

        map.getNode(curX, curY).addEdge(newX);
        map.getNode(newX, curY+1).addParent(curX);
        curX = newX;
    }
    map.getNode(curX, 14).addEdge(3);
    return true;
}

bool createPathsSinglePathTest(Map &map, Random &mapRng, int length) {
    int firstStartX = randRange(mapRng, 0, MAP_WIDTH - 1);
    createSinglePathTestFirstIteration(map, mapRng, firstStartX);

    for(int i = 1; i < PATH_DENSITY; ++i) {
        int startX = randRange(mapRng, 0, MAP_WIDTH - 1);

        while(startX == firstStartX && i == 1) {
            startX = randRange(mapRng, 0, MAP_WIDTH - 1);
        }

        bool res = createSinglePathTestIteration(map, mapRng, startX, length);
        if (!res) {
            return false;
        }
    }
    return true;
}

inline bool sts::testSeedForSinglePath(std::int64_t seed, int length) {
    Random mapRng(seed+1);
    sts::Map map;
    initNodes(map);
    return createPathsSinglePathTest(map, mapRng, length);

}

std::vector<std::int64_t> sts::findSinglePathSeeds(std::int64_t start, std::int64_t count, int length) {
    std::vector<std::int64_t> ret;

    for (std::int64_t seed = start; seed < start+count; ++seed) {
        if (testSeedForSinglePath(seed, length)) {
            ret.push_back(seed);
            std::cout << SeedHelper::getString(seed) << std::endl;
        }
    }
    return ret;
}
