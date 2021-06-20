//
// Created by keega on 6/11/2021.
//

#include "sts_map.h"
#include "java_random.h"

#include <cassert>
#include <cmath>
#include <unordered_set>

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

constexpr float ELITE_ROOM_CHANCE_A0 = 0.08f;
constexpr float ELITE_ROOM_CHANCE_A1 = ELITE_ROOM_CHANCE_A0 * 1.6f;


char sts::getRoomSymbol(Room room) {
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


void createPaths(Map &map, Random &mapRng);
void filterRedundantEdgesFromFirstRow(Map &map);
void assignRooms(Map &map, Random &mapRng, int ascensionLevel=0);

MapNode &Map::getNode(int x, int y) {
    return nodes.at(y).at(x);
}

const MapNode &Map::getNode(int x, int y) const {
    return nodes.at(y).at(x);
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

Map Map::fromSeed(std::int64_t seed, int ascension, int act, bool setBurning) {
    Map map;
    initNodes(map);
    auto offset = act == 1 ? 1 : act*(100*(act-1));
    Random mapRng(seed+offset);
    createPaths(map, mapRng);
    filterRedundantEdgesFromFirstRow(map);
    assignRooms(map, mapRng, ascension);
    if (setBurning) {
        assignBurningElite(map, mapRng);
    }
    return map;
}

void Map::normalizeParents() {
    for (int row = 1; row < 15; ++row) {
        for (int col = 0; col < 7; ++col) {
            auto &node = getNode(col, row);
            bool found[7] = {false};
            for (int i = 0; i < node.parentCount; ++i) {
                found[node.parents[i]] = true;
            }
            node.parentCount = 0;
            for (int i = 0; i < 7; ++i) {
                if (found[i]) {
                    node.addParent(i);
                }
            }
        }
    }
}

Path Path::fromBits(std::uint64_t bits) {
    std::int64_t newBits = 0;
    for (int y = 0; y < 15; ++y) {
        auto bitsAtY = bits >> ((14-y)*4) & 0xF;
        newBits |= (bitsAtY+1) << (y*4);
    }
    return Path(newBits);
}

Path Path::fromString(const std::string &str) {
    Path path;
    for (int y = 0; y < str.size(); ++y) {
        Room room;
        switch (str.at(y)) {
            case '$': room = Room::SHOP; break;
            case 'R': room = Room::REST; break;
            case '?': room = Room::EVENT; break;
            case 'E': room = Room::ELITE; break;
            case 'M': room = Room::MONSTER; break;
            case 'T': room = Room::TREASURE; break;
            case 'B': room = Room::BOSS; break;
            default: room = Room::NONE;
        }
        path = path.addRoom(room, y);
    }

    return path;
}

Path Path::fromString(const std::string &s, int idxOfBurningElite) {
    return Path::fromString(s).setIdxOfBurningElite(idxOfBurningElite);
}

bool Path::operator<(const Path &rhs) const {
    return bits < rhs.bits;
}

bool Path::contains(Room room) const {
    return bits & roomContainBits[(int)room];
}

Path Path::setIdxOfBurningElite(int idx) const {
    auto newBits = (bits & 0x0FFFFFFFFFFFFFFFFULL) | (static_cast<std::uint64_t>(idx)  << 60);
    return Path(newBits);
}

int Path::getIdxOfBurningElite() const {
    return static_cast<int>(bits >> 60);
}

Room Path::roomAt(int y) const {
    auto roomBits = (bits >> ((14-y)*4)) & 0xF;
    return static_cast<Room>(roomBits-1);
}

Path Path::addRoom(Room room, int y) const {
    int shiftAmt = ((14-y)*4);
    auto maskedBits = bits & ~(0xFLL << shiftAmt);

    auto roomBits = (static_cast<std::int64_t>(room)+1) << shiftAmt;
    auto newBits = maskedBits | roomBits;
    Path ret(newBits);
    return ret;
}

std::string Path::toString(int begin, int end) const {
    std::string str;
    for (int y = begin; y < end; ++y) {
        Room room = roomAt(y);
        str += getRoomSymbol(room);
    }
    return str;
}

std::string Path::toPrettyString() const {
    std::string str;
    for (int y = 0; y < 14; ++y) {
        Room room = roomAt(y);
        str += getRoomSymbol(room);
        str += " - ";
    }
    Room room = roomAt(14);
    str += getRoomSymbol(room);
    return str;
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
    return sts::getRoomSymbol(room);
}

void MapNode::addParent(int parent) {
    parents[parentCount++] = parent;

#ifndef SINGLE_PATH
    maxXParent = std::max(parent, maxXParent);
    minXParent = std::min(parent, minXParent);
#endif
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
#ifdef SINGLE_PATH
    int maxParent = parents[0];
    for (int i = 1; i < parentCount; i++) {
        if (parents[i] > maxParent) {
            maxParent = parents[i];
        }
    }
    return maxParent;
#else
    return maxXParent;
#endif
}

inline int MapNode::getMinXParent() const {
#ifdef SINGLE_PATH
    int minParent = parents[0];
    for (int i = 1; i < parentCount; i++) {
        if (parents[i] < minParent) {
            minParent = parents[i];
        }
    }
    return minParent;
#else
    return minXParent;
#endif
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

RoomCounts getRoomCountsAndAssignFixed(Map &map) {
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

void fillRoomArray(Room *arr, RoomCounts counts, float eliteRoomChance) {

    int shopCount = static_cast<int>(std::round(counts.total * SHOP_ROOM_CHANCE));
    int restCount = static_cast<int>(std::round(counts.total * REST_ROOM_CHANCE));
    int treasureCount = static_cast<int>(std::round(counts.total * TREASURE_ROOM_CHANCE));
    int eliteCount = static_cast<int>(std::round(counts.total * eliteRoomChance));
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

void assignRooms(Map &map, Random &rng, int ascensionLevel) {
    RoomCounts counts = getRoomCountsAndAssignFixed(map);

    Room rooms[counts.unassigned];
    fillRoomArray(rooms, counts, ascensionLevel > 0 ? ELITE_ROOM_CHANCE_A1 : ELITE_ROOM_CHANCE_A0);

    for (int i=counts.unassigned; i>1; i--) {
        std::swap(rooms[i-1], rooms[rng.nextInt(i)]);
    }

    assignRoomsToNodes(map, rooms, counts.unassigned);
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

struct IntTuple {
    int x;
    int y;

    IntTuple() = default;
    IntTuple(int x, int y) : x(x), y(y) {}
};

void sts::assignBurningElite(Map &map, Random &mapRng) {
    int eliteRoomCount = 0;
    std::array<IntTuple,14> eliteRooms;

    for (int row = 0; row < 15; ++row) {
        for (int col = 0; col < 7; ++col) {
            if (map.getNode(row,col).room == sts::Room::ELITE) {
                eliteRooms[eliteRoomCount++] = IntTuple(col,row);
            }
        }
    }

    // if number of elite rooms is 1 it will crash the base game too.
    int idx = mapRng.random(eliteRoomCount-1);
    map.burningEliteX = eliteRooms.at(idx).x;
    map.burningEliteY = eliteRooms.at(idx).y;
}


void sts::printStats() {
//    std::cout << "total same parents " << totalSameParents << std::endl;
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

bool createSinglePathTestIteration(Map &map, Random &rng, int startX, int length) {
    int curX = startX;
    for (int curY = 0; curY < MAP_HEIGHT-1; ++curY) {
        int newX = chooseNewPath(map, rng, curX, curY);

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

int sts::getPathSingleLength(std::int64_t seed) {
    Map map;
    Random random(seed+1);
    generateMap(map, random);


    for (int row = 1; row < MAP_HEIGHT; ++row) {
        int count = 0;
        for (int col = 0; col < MAP_WIDTH; ++col) {
            if (map.getNode(col, row).parentCount > 0) {
                ++count;
            }
        }
        if (count > 1) {
            return row-1;
        }
    }
    return 14;
}

int sts::getPathTotalSingleLength(std::int64_t seed) {
    Map map;
    Random random(seed+1);
    generateMap(map, random);

    int total = 0;
    for (int row = 1; row < MAP_HEIGHT; ++row) {
        int count = 0;
        for (int col = 0; col < MAP_WIDTH; ++col) {
            if (map.getNode(col, row).parentCount > 0) {
                ++count;
            }
        }
        if (count == 1) {
            ++total;
        }
    }
    return total;
}

//int sts::getForcedMonsterFightCount(std::int64_t seed) {
//    Map map;
//    Random random(seed+1);
//    generateMap(map, random);
//
//    int total = 0;
//    for (int row = 1; row < MAP_HEIGHT; ++row) {
//
//        bool matches = true;
//        for (int col = 0; col < MAP_WIDTH; ++col) {
//            if (map.getNode(col, row).parentCount > 0 &&
//                !(map.getNode(col, row).room == Room::MONSTER  || map.getNode(col, row).room == Room::ELITE) ) {
//                matches = false;
//               break;
//            }
//        }
//        if (matches) {
//            ++total;
//        }
//    }
//    return total;
//}

bool rowIsAllRoomType(const Map &map, int row, Room room) {
    for (int col = 0; col < MAP_WIDTH; ++col) {
        if (map.getNode(col, row).parentCount > 0 &&
            map.getNode(col, row).room != room) {
            return false;
        }
    }
    return true;
}

bool sts::isForcedMonsterIntoEliteFight(std::int64_t seed) {
    Map map;
    Random random(seed+1);
    generateMap(map, random);

    for (int row = 1; row <= 4; ++row) {
        if (!rowIsAllRoomType(map, row, Room::MONSTER)) {
            return false;
        }
    }
    return rowIsAllRoomType(map, 5, Room::ELITE);
}



int sts::getMinMapWeight(const Map &map, NodePredicate predicate) {
    std::array<int,7> prevWeights = {0};
    std::array<int,7> curWeights = {0};


    for (int col = 0; col < 7; ++col) {
        auto node = map.getNode(col,0);
        if (node.edgeCount == 0) {
            continue;
        }

        prevWeights[col] = predicate(node);
    }


    for (int row = 1; row < 15; ++row) {

        if (row == 14) {
            std::fill(curWeights.begin(), curWeights.end(), 0x7FFFFFFF);
        }

        for (int col = 0; col < 7; ++col) {
            auto node = map.getNode(col, row);
            if (node.edgeCount == 0) {
                continue;
            }

            int min = prevWeights[node.parents[0]];
            for (int pIdx = 1; pIdx < node.parentCount; ++pIdx) {
                if (prevWeights[node.parents[pIdx]] < min)  {
                    min = prevWeights[node.parents[pIdx]];
                }
            }

            int nodeValue = predicate(node);
            curWeights[col] = nodeValue + min;
        }
        prevWeights = curWeights;
    }

    int min = prevWeights[0];
    for (int i = 1; i < 7; ++i) {
        if (prevWeights[i] < min) {
            min = prevWeights[i];
        }
    }
    return min;
}

int sts::getMaxMapWeight(const Map &map, NodePredicate predicate) {
    std::array<int,7> prevWeights = {0};
    std::array<int,7> curWeights = {0};


    for (int col = 0; col < 7; ++col) {
        auto node = map.getNode(col,0);
        if (node.edgeCount == 0) {
            continue;
        }

        prevWeights[col] = predicate(node);
    }


    for (int row = 1; row < 15; ++row) {
        if (row == 14) {
            std::fill(curWeights.begin(), curWeights.end(), -0x7FFFFFFF-1);
        }
        for (int col = 0; col < 7; ++col) {
            auto node = map.getNode(col, row);

            if (node.edgeCount == 0) {
                continue;
            }

            int max = prevWeights[node.parents[0]];
            for (int pIdx = 1; pIdx < node.parentCount; ++pIdx) {
                if (prevWeights[node.parents[pIdx]] > max)  {
                    max = prevWeights[node.parents[pIdx]];
                }
            }

            int nodeValue = predicate(node);
            curWeights[col] = nodeValue + max;
        }
        prevWeights = curWeights;
    }

    int max = prevWeights[0];
    for (int i = 1; i < 7; ++i) {
        if (prevWeights[i] > max) {
            max = prevWeights[i];
        }
    }
    return max;
}



void addSets(std::unordered_set<std::int64_t> &out, const std::unordered_set<std::int64_t> &in, const MapNode &node) {
    std::int64_t bits = (static_cast<std::int64_t>(node.room)+1) << ((14-node.y)*4);

    for (std::int64_t path : in) {
        out.insert(path | bits);
    }
}



std::set<Path> sts::getUniquePaths(const Map &map) {
    std::array<std::unordered_set<std::int64_t>,7> prevSets = {};
    std::array<std::unordered_set<std::int64_t>,7> curSets = {};

    for (int col = 0; col < 7; ++col) {
        auto node = map.getNode(col,0);
        if (node.edgeCount == 0) {
            continue;
        }
        std::int64_t bits = (static_cast<std::int64_t>(node.room)+1) << ((14-node.y)*4);
        prevSets.at(col).insert(bits);
    }

    for (int row = 1; row < 15; ++row) {
        for (int col = 0; col < 7; ++col) {

            auto node = map.getNode(col, row);
            curSets.at(col) = {};

            for (int i = 0; i < node.parentCount; ++i) {
                int parentCol = node.parents[i];
                addSets(curSets.at((col)), prevSets.at(parentCol), node);
            }
        }

        for (int i = 0; i < 7; ++i) {
            prevSets.at(i) = std::move(curSets.at(i));
        }

    }


    std::set<Path> uniquePaths;
    for (const auto& pathSet : prevSets) {
        for (std::int64_t bits : pathSet) {
            uniquePaths.insert(Path(bits));
        }
    }

    return uniquePaths;
}

void addPathSets(std::set<Path> &out, const std::set<Path> &in, const MapNode &node, const PathBuilderPredicate &p) {
    for (auto path : in) {
        if (p(path, node.room, node.y)) {
            out.insert( path.addRoom(node.room, node.y) );
        }
    }
}

std::set<Path> sts::getPathsMatching(const Map &map, const PathBuilderPredicate &p) {

    std::array<std::set<Path>,7> prevPaths = {};
    std::array<std::set<Path>,7> curPaths = {};

    for (int col = 0; col < 7; ++col) {
        auto node = map.getNode(col,0);
        if (node.edgeCount == 0) {
            continue;
        }
        Path path(node.room);
        if (p(path, node.room, node.y)) {
            curPaths.at(col).insert(path);
        }
    }

    for (int row = 1; row < 15; ++row) {

        bool allEmpty = true;
        for (int i = 0; i < 7; ++i) {
            if (!curPaths.at(i).empty()) {
                allEmpty = false;
            }
            prevPaths.at(i) = std::move(curPaths.at(i));
        }
        if (allEmpty) {
            return {};
        }

        for (int col = 0; col < 7; ++col) {
            auto node = map.getNode(col, row);

            for (int i = 0; i < node.parentCount; ++i) {
                int parentCol = node.parents[i];
                addPathSets(curPaths.at(col), prevPaths.at(parentCol), node, p);
            }
        }
    }

    std::set<Path> paths;
    for (const auto& pathSet : curPaths) {
        for (auto path : pathSet) {
            paths.insert(path);
        }
    }

    return paths;
}

Path sts::getLeftMostPath(const Map &map, int length) {
    Path path;
    for (int x = 0; x < 7; ++x) {
        auto node = map.getNode(x,0);
        if (node.edgeCount > 0) {
            path = path.addRoom(node.room, 0);
            break;
        }
    }
    for (int y = 0; y < length; ++y) {
        for (int x = 0; x < 7; ++x) {
            auto node = map.getNode(x,y);
            if (node.parentCount > 0) {
                path = path.addRoom(node.room, y);
                break;
            }
        }
    }
    return path;
}


void sts::mapTest(std::int64_t seed) {
    Random mapRng(seed+1);
    sts::Map map;
    sts::generateMap(map, mapRng);
    auto x = randRange(mapRng, 0, 6);
    std::cout << x << '\n';
    std::cout << map.toString(true) << std::endl;
    std::cout << getPathSingleLength(seed) << std::endl;
}




