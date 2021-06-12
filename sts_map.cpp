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

static inline int randRange(Random &rng, int min, int max) {
    return rng.random(max - min) + min;
}

void insertEdge(MapNode &mapNode, Edge edge, int idx) {
    for (int x = mapNode.edgeCount; x > idx; --x) {
        mapNode.edges[x] = mapNode.edges[x-1];
    }
    mapNode.edges[idx] = edge;
    ++mapNode.edgeCount;
}

int compareEdges(const Edge &e0, const Edge &e1) {
    if (e0.dstX > e1.dstX) {
        return 1;
    }
    if (e0.dstX < e1.dstX) {
        return -1;
    }
    if (e0.dstY == e1.dstY) {
        return 0;
    }
    return e0.dstY > e1.dstY ? 1 : -1;
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


void MapNode::addParent(MapNode *node) {
//    int cur = 0;
//    while (true) {
//        if (parentCount == cur) {
//            parents[cur] = node;
//            ++edgeCount;
//            return;
//        }
//        bool res = compareEdges(edge, edges[cur]);
//        if (!res) {
//            insertEdge(*this, edge, cur);
//            return;
//        }
//        ++cur;
//    }
    parents[parentCount++] = node;
}

void MapNode::addEdge(Edge edge) {
    int cur = 0;
    while (true) {
        if (edgeCount == cur) {
            edges[cur] = edge;
            ++edgeCount;
            return;
        }

        int res = compareEdges(edge, edges[cur]);
        if (res == 0) {
            return;
        } else if (res < 0) {
            insertEdge(*this, edge, cur);
            return;
        }
        ++cur;
    }
}

Edge &MapNode::getMaxEdge() {
    assert(edgeCount > 0);
    return edges.at(edgeCount-1);
}

Edge &MapNode::getMinEdge() {
    assert(edgeCount > 0);
    return edges.at(0);
}

MapNode *MapNode::getMaxXParent() {
    assert(parentCount > 0);

    MapNode *maxParent = parents[0];
    for (int i = 1; i < parentCount; i++) {
        if (parents[i]->x > maxParent->x) {
            maxParent = parents[i];
        }
    }
    return maxParent;
}

MapNode *MapNode::getMinXParent() {
    assert(parentCount > 0);

    MapNode *minParent = parents[0];
    for (int i = 1; i < parentCount; i++) {
        if (parents[i]->x < minParent->x) {
            minParent = parents[i];
        }
    }
    return minParent;
}

void removeEdge(MapNode &node, int idx) {
    for (int i = idx; i < node.edgeCount-1; i++) {
        std::swap(node.edges[i], node.edges[i+1]);
    }
    --node.edgeCount;
}

void filterRedundantEdgesFromFirstRow(Map &map) {
    bool nodesVisited[MAP_WIDTH] = {false};
    for (auto &node : map.nodes.at(0)) {
        for (int i = node.edgeCount-1; i >= 0 ; --i) {
            int x = node.edges[i].dstX;
            if (nodesVisited[x]) {
                removeEdge(node, i);
            } else {
                nodesVisited[x] = true;
            }
        }
    }
}

MapNode *getCommonAncestor(MapNode &node1, MapNode &node2) {

    if (node1.y != node2.y) {
        int x = 0;
    }
    assert(node1.y == node2.y);
    assert(&node1 != &node2);

    MapNode *l_node;
    MapNode *r_node;
    if (node1.x < node2.y) {
        l_node = &node1;
        r_node = &node2;
    } else {
        l_node = &node2;
        r_node = &node1;
    }

    int current_y = node1.y;

    while(true) {
        if (!(current_y >= 0 && current_y >= node1.y - MAX_ANCESTOR_GAP)) {
            return nullptr;
        }
        if (l_node->parentCount == 0 || r_node->parentCount == 0) {
            return nullptr;
        }

        l_node = l_node->getMaxXParent();
        r_node = r_node->getMinXParent();

        if (l_node == r_node) {
            return l_node;
        }
        --current_y;
    }
}


void _createPathsHelper(Map &map, Random &rng, MapNode &currentNode, MapNode* &targetNodeCandidate, MapNode &parent, int edgeDstX, int &newEdgeX, int &newEdgeY) {
    if (&parent == &currentNode) {
        return;
    }

    MapNode *ancestor = getCommonAncestor(parent, currentNode);
    if (ancestor == nullptr) {
        return;
    }

    int ancestor_gap = newEdgeY - ancestor->y;
    if (ancestor_gap >= MIN_ANCESTOR_GAP) {
        return;
    }

    if (targetNodeCandidate->x > currentNode.x) {
        newEdgeX = edgeDstX + randRange(rng, -1, 0);
        if (newEdgeX < 0) {
            newEdgeX = edgeDstX;
        }
    } else if (targetNodeCandidate->x == currentNode.x) {
        newEdgeX = edgeDstX + randRange(rng, -1, 1);
        if (newEdgeX > ROW_END_NODE) {
            newEdgeX = edgeDstX - 1;
        } else if (newEdgeX < 0) {
            newEdgeX = edgeDstX + 1;
        }
    } else {
        newEdgeX = edgeDstX + randRange(rng, 0, 1);
        if (newEdgeX > ROW_END_NODE) {
            newEdgeX = edgeDstX;
        }
    }

    targetNodeCandidate = &map.getNode(newEdgeX, newEdgeY);
}


void _createPaths(Map &map, Random &rng, Edge edge) {
    MapNode &currentNode = map.getNode(edge.dstX, edge.dstY);

    if (edge.dstY + 1 >= MAP_HEIGHT) {
        Edge newEdge(3, edge.dstY + 2);
        currentNode.addEdge(newEdge);
        return;

    }

    int min;
    int max;

    if (edge.dstX == 0) {
        min = 0;
        max = 1;
    } else if (edge.dstX == ROW_END_NODE) {
        min = -1;
        max = 0;
    } else {
        min = -1;
        max = 1;
    }

    int newEdgeX = edge.dstX + randRange(rng, min, max);
    int newEdgeY = edge.dstY + 1;
    MapNode *targetNodeCandidate = &map.getNode(newEdgeX, newEdgeY);

//    ArrayList<MapRoomNode> parents = targetNodeCandidate.getParents();

    const int parentCount = targetNodeCandidate->parentCount;
    std::array<MapNode*, 6> *parents = &targetNodeCandidate->parents;

    for (int i = 0; i < parentCount; i++) {
        _createPathsHelper(map, rng, currentNode, targetNodeCandidate, *(parents->at(i)), edge.dstX, newEdgeX, newEdgeY);
    }

    // todo organize these ifs better
    MapNode *right_node;
    Edge *left_edge_of_right_node;
    if (edge.dstX != 0) {
//        right_node = (MapRoomNode)((ArrayList)nodes.get(edge.dstY)).get(edge.dstX - 1);
        right_node = &map.getNode(edge.dstX-1, edge.dstY);

        if (right_node->edgeCount > 0) {
            left_edge_of_right_node = &right_node->getMaxEdge();
            if (left_edge_of_right_node->dstX > newEdgeX) {
                newEdgeX = left_edge_of_right_node->dstX;
            }
        }
    }

    if (edge.dstX < ROW_END_NODE) {
        right_node = &map.getNode(edge.dstX+1, edge.dstY);
        if (right_node->edgeCount > 0) {
            left_edge_of_right_node = &right_node->getMinEdge();
            if (left_edge_of_right_node->dstX < newEdgeX) {
                newEdgeX = left_edge_of_right_node->dstX;
            }
        }
    }


//    targetNodeCandidate.addParent(currentNode);
//    return _createPaths(nodes, newEdge, rng);

    Edge newEdge(newEdgeX, newEdgeY);
    currentNode.addEdge(newEdge);
    map.getNode(newEdgeX, newEdgeY).addParent(&currentNode);

    _createPaths(map, rng, newEdge);
}

void createPaths(Map &map, Random &mapRng) {
    int firstStartingNode = -1;
    for(int i = 0; i < PATH_DENSITY; ++i) {
        int startingNode = randRange(mapRng, 0, MAP_WIDTH-1);
        if (i == 0) {
            firstStartingNode = startingNode;
        }

        while(startingNode == firstStartingNode && i == 1) {
            startingNode = randRange(mapRng, 0, MAP_WIDTH-1);
        }

        _createPaths(map, mapRng, Edge(startingNode, 0));
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
                const auto &edge = &node.edges[i];
                if (edge->dstX < node.x) {
                    node_symbol = "\\";
                }

                if (edge->dstX == node.x) {
                    mid = "|";
                }

                if (edge->dstX > node.x) {
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
                        if (lower_node.edges[i].dstX == node.x) {
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

bool ruleSiblingMatches(Map &map, MapNode node, Room roomToBeSet) {
    for (int i = 0; i < node.parentCount; i++) {
        const MapNode &parent = *node.parents[i];
        for (int c = 0; c < parent.edgeCount; c++) {

            if (parent.edges[c].dstX == node.x) {
                continue;
            }

            const auto &sibling = map.getNode(parent.edges[c].dstX, node.y);
            if (sibling.room == roomToBeSet) {
                return false;
            }
        }
    }
    return true;
}

bool ruleParentMatches(MapNode node, Room roomToBeSet) {
    for (int i = 0; i < node.parentCount; i++) {
        Room parentRoom = node.parents[i]->room;
        if (roomToBeSet == parentRoom) {
            return false;
        }
    }
    return true;
}


int getNextRoomIdxAccordingToRules(Map &map, MapNode node, Room *rooms, int roomsSize) {

    bool triedAssignRoom[5] = { false };

    for (int i = 0; i < roomsSize; i++) {
        Room room = rooms[i];

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
            case Room::MONSTER:
                if (!ruleSiblingMatches(map, node, room)) {
                    continue;
                }
                return i;

            default:
                break;
        }

        bool canSet = ruleParentMatches(node, room)
                && ruleSiblingMatches(map, node, room);
        if (canSet) {
            return i;
        }
    }

    return -1;
}

void removeElement(Room *rooms, int idx, int size) {
    for (int i = idx; i < size-1; ++i) {
        rooms[i] = rooms[i+1];
    }
}


// idea: remove rooms basically in reverse, shifting the head of the array forward instead
void assignRoomsToNodes(Map &map, Room *rooms, int roomsSize) {
    for (int row = 1; row < MAP_HEIGHT-1; ++row) {
        if (row == 8) {
            continue;
        }
        for (auto &node : map.nodes.at(row)) {
            if (node.edgeCount <= 0) {
                continue;
            }
            int roomIdx = getNextRoomIdxAccordingToRules(map, node, rooms, roomsSize);
            if (roomIdx != -1) {
                node.room = rooms[roomIdx];
                removeElement(rooms, roomIdx, roomsSize--);
            } else {
                // this line replaces last minute node checker
                node.room = sts::Room::MONSTER;
            }
        }
    }
}


// dont think this is necessary
void lastMinuteNodeChecker(Map &map) {
    for (int rowIdx = 1; rowIdx < MAP_HEIGHT-1; ++rowIdx) {
        auto &row = map.nodes.at(rowIdx);

        for (auto &node : row) {
            if (node.edgeCount > 0 && node.room == sts::Room::NONE) {
                node.room = sts::Room::MONSTER;
            }
        }
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


void sts::generateMap(Map &map, sts::Random &mapRng) {
    initNodes(map);
    createPaths(map, mapRng);
    filterRedundantEdgesFromFirstRow(map);
    assignRooms(map, mapRng);
}

void sts::mapTest() {
//    for (std::int64_t seed = 0; seed < 10000; seed++) {
//        sts::Map map;
//        sts::generateMap(map, sts::Random(seed+1));
//    }
    std::int64_t seed = 8;
    sts::Random mapRng(seed+1);
    sts::Map map;
    sts::generateMap(map, mapRng);

    std::cout << map.toString(true);
}

