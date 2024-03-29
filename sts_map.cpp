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

MapNode &Map::getNode(int8_t x, int8_t y) {
    return nodes.at(y).at(x);
}

const MapNode &Map::getNode(int8_t x, int8_t y) const {
    return nodes.at(y).at(x);
}


void initNodes(Map &map) {
    for (int8_t y = 0; y < MAP_HEIGHT; y++) {
        for (int8_t x = 0; x < MAP_WIDTH; x++) {
            auto &node = map.nodes.at(y).at(x);
            node.x = x;
            node.y = y;
        }
    }
}

Map Map::fromSeed(std::int64_t seed, int ascension, int act, bool setBurning, bool isBadMap) {
    Map map;
    initNodes(map);
    auto offset = act == 1 ? 1 : act*(100*(act-1));
    Random mapRng(seed+offset);
    createPaths(map, mapRng);
    filterRedundantEdgesFromFirstRow(map);
    assignRooms(map, mapRng, ascension);
    if (setBurning or isBadMap) {
        assignBurningElite(map, mapRng);
    }
    return map;
}

void Map::normalizeParents() {
    for (int8_t row = 1; row < 15; ++row) {
        for (int8_t col = 0; col < 7; ++col) {
            auto &node = getNode(col, row);
            bool found[7] = {false};
            for (int8_t i = 0; i < node.parentCount; ++i) {
                found[node.parents[i]] = true;
            }
            node.parentCount = 0;
            for (int8_t i = 0; i < 7; ++i) {
                if (found[i]) {
                    node.addParent(i);
                }
            }
        }
    }
}

bool Map::hasSpeedyPath(){
	
	int currfloor = 0;
	
	for (int i = 0; i < 6; i++){
		MapNode mynode = nodes[0][i];
		char mysymb = mynode.getRoomSymbol();
		if (mysymb == 'M'){
			currfloor |= 1<<i;
		}
	}
	
	for (int y = 0; currfloor and y < 14; y++){
		int nextfloor = 0;
		int x = 0;
		if (currfloor){
			while(currfloor){
				if (currfloor & 1){
					MapNode mynode = nodes[y][x];
					for (int i = 0; i < mynode.edgeCount; i++){
						MapNode nextnode = nodes[y+1][mynode.edges[i]];
						char nextsymb = nextnode.getRoomSymbol();
						if (nextsymb != 'M' and nextsymb != 'E'){
							nextfloor |= 1<<nextnode.x;
							//std::cout << "x,y =\t" << x << ',' << y << " sees: \t" << nextnode.x << "\n";
						}
					}
				}
				x++;
				currfloor >>= 1;
			}
			
			currfloor = nextfloor;
		}
		
		else{
			return false;
		}
	}
	
	return currfloor != 0;
}

/*
remove redundant nodes
if nodes A & B have the same label, 
and DOWN(A) is a subset of DOWN(B), 
and UP(A) is a subset of UP(B), then 
A may be erased
*/
int Map::reduceContractions(bool verbose){
    int ctr = 0;
    
    for (int y = 0; y < MAP_HEIGHT; y++){
        
        if (verbose){
            std::cout << "\ny = " << y << "...\n";
        }
        
        for (int i = 0; i < MAP_WIDTH; i++){
            
            MapNode &node1 = nodes[y][i];
            
            if (node1.room == Room::NONE){
                continue;
            }
            
            if (verbose){
                std::cout << "\tx1 = " << i << " has up/down: "
                    << static_cast<int>(node1.edgeBits) << "/"
                    << static_cast<int>(node1.parentBits) << '\n';
            }
            
            for (int j = i+1; j < MAP_WIDTH; j++){
                MapNode &node2 = nodes[y][j];
                
                if (verbose){
                    std::cout << "\t\tx2 = " << j << " has up/down: "
                            << static_cast<int>(node2.edgeBits) << "/"
                            << static_cast<int>(node2.parentBits) << '\n';
                }
                
                if (node1.room != Room::NONE && node1.room == node2.room){
                    if (
                        (node1.parentBits & node2.parentBits) == node1.parentBits
                        && (node1.edgeBits & node2.edgeBits) == node1.edgeBits
                    ){
                        if (verbose){
                            std::cout << "\t\tREDUNDANCY: " << i << node1.getRoomSymbol() 
                                << " -> " << j << node2.getRoomSymbol() << '\n';
                        }
                        
                        node1.room = Room::NONE;
                        ctr++;
                    }
                    
                    else if (
                        (node1.parentBits & node2.parentBits) == node2.parentBits
                        && (node1.edgeBits & node2.edgeBits) == node2.edgeBits
                    ){
                        if (verbose){
                            std::cout << "\t\tREDUNDANCY: " << j << node2.getRoomSymbol() << 
                                " -> " << i << node1.getRoomSymbol() << '\n';
                        }
                        
                        node2.room = Room::NONE;
                        ctr++;
                        
                    }
                }
            }
        }
    }
    return ctr;
}

Path Path::fromBits(std::uint64_t bits) {
    std::int64_t newBits = 0;
    for (int8_t y = 0; y < 15; ++y) {
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

void MapNode::addParent(int8_t parent) {
    parents[parentCount++] = parent;
    
    parentBits |= 1<<parent;
    parentMults[parent]++;

#ifndef SINGLE_PATH
    maxXParent = std::max(static_cast<int>(parent), maxXParent);
    minXParent = std::min(static_cast<int>(parent), minXParent);
#endif
}

inline void MapNode::addEdge(int8_t edge) {
    int8_t cur = 0;
    
    edgeBits |= 1 << edge;
    
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

inline int8_t MapNode::getMaxEdge() const {
//    assert(edgeCount > 0);
    //return edges.at(edgeCount-1);
    
    return Map::NEIGH[edgeBits][1];
}

inline int8_t MapNode::getMinEdge() const {
//    assert(edgeCount > 0);
    //return edges.at(0);
    
    return Map::NEIGH[edgeBits][0];
}

inline int8_t MapNode::getMaxXParent() const {
    return Map::NEIGH[parentBits][1];
#ifdef SINGLE_PATH
    int8_t maxParent = parents[0];
    for (int8_t i = 1; i < parentCount; i++) {
        if (parents[i] > maxParent) {
            maxParent = parents[i];
        }
    }
    return maxParent;
#else
    return maxXParent;
#endif
}

inline int8_t MapNode::getMinXParent() const {
    return Map::NEIGH[parentBits][0];
#ifdef SINGLE_PATH
    int8_t minParent = parents[0];
    for (int8_t i = 1; i < parentCount; i++) {
        if (parents[i] < minParent) {
            minParent = parents[i];
        }
    }
    return minParent;
#else
    return minXParent;
#endif
}

/*
removeEdge & removeParent* first used in filterRedundantEdgesFromFirstRow
delete edges by swapping entries from edge array backwards & adjusting edge count
same for parents
*/
void removeEdge(MapNode &node, int8_t idx) {
    for (int8_t i = idx; i < node.edgeCount-1; i++) {
        std::swap(node.edges[i], node.edges[i+1]);
    }
    --node.edgeCount;
    
    node.edgeBits = 0;
    for (int8_t i = 0; i < node.edgeCount; i++){
        node.edgeBits |= 1 << node.edges[i];
    }
}

void removeParentAtIdx(MapNode &node, int8_t parentIdx) {
    for (int8_t i = parentIdx; i < node.parentCount-1; ++i) {
        node.parents[i] = node.parents[i+1];
    }
    --node.parentCount;
}

void removeParent(MapNode &node, int8_t parent) {
    for (int8_t i = node.parentCount-1; i >= 0; --i) {
        if (node.parents[i] == parent) {
            removeParentAtIdx(node, i);
        }
    }
    
    node.parentBits = 0;
    for (int8_t i = 0; i < node.parentCount; i++){
        node.parentBits |= 1 << node.parents[i];
    }
}

void filterRedundantEdgesFromFirstRow(Map &map) {
    bool nodesVisited[MAP_WIDTH] = {false};
    for (auto &node : map.nodes.at(0)) {
        for (int8_t i = node.edgeCount-1; i >= 0 ; --i) {
            int8_t x = node.edges[i];
            if (nodesVisited[x]) {
                removeParent(map.getNode(x, 1), node.x);
                removeEdge(node, i);
            } else {
                nodesVisited[x] = true;
            }
        }
    }
}

inline bool getCommonAncestor(const Map &map, const uint8_t x1, const uint8_t x2, const uint8_t y) {
    /* old code:
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
    */
    constexpr int8_t FLIP[7][14] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0};
	return Map::NEIGH[
		map.getNode(x1 + (x2-x1)*FLIP[x1][y], y).parentBits][1] == 
		Map::NEIGH[map.getNode(x2 + (x1-x2)*FLIP[x1][y], y).parentBits][0];
}

inline int8_t choosePathParentLoopRandomizer(const Map &map, Random &rng, const int8_t curX, const int8_t curY, int8_t newX) {
    /* old code:
    const MapNode &newEdgeDest = map.getNode(newX, curY + 1);
    
    for (int8_t i = 0; i < newEdgeDest.parentCount; i++) {
        int8_t parentX = newEdgeDest.parents.at(i);
        if (curX == parentX) {
            continue;
        }
        if (getCommonAncestor(map, parentX, curX, curY)) {
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
    */
    const MapNode &newEdgeDest = map.getNode(newX, curY + 1);
	
	static constexpr int8_t LR[7] = {6,13,27,54,108,88,48};
	
    const int8_t neigh = newEdgeDest.parentBits & LR[curX];
	int8_t mult = 0;
	
	static constexpr int8_t MINMAX[97][2] = {7,7,0,7,1,7,0,1,2,7,0,2,1,2,7,7,3,7,0,3,1,3,7,7,2,3,7,7,7,7,7,7,4,7,0,4,1,4,7,7,2,4,7,7,7,7,7,7,3,4,7,7,7,7,7,7,7,7,7,7,7,7,7,7,5,7,0,5,1,5,7,7,2,5,7,7,7,7,7,7,3,5,7,7,7,7,7,7,7,7,7,7,7,7,7,7,4,5,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,7,0,6,1,6,7,7,2,6,7,7,7,7,7,7,3,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,4,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,5,6};
	
	int8_t i = MINMAX[neigh][0];
	if (i < 7){
		if (getCommonAncestor(map, i, curX, curY)) {
            mult += newEdgeDest.parentMults[i];
        }
		i = MINMAX[neigh][1];
		
		if (i < 7 && getCommonAncestor(map, i, curX, curY)) {
			mult += newEdgeDest.parentMults[i];
		}
		
	}
	
	static constexpr int8_t cPPLR[7][7][6] = {1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,2,1,2,0,1,2,0,1,2,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,2,3,2,3,2,3,2,3,2,3,2,3,1,2,3,1,2,3,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,2,3,4,2,3,4,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5,3,4,5,3,4,5,3,4,3,4,3,4,3,4,3,4,3,4,5,6,5,6,5,6,5,6,5,6,5,6,5,6,5,6,5,6,5,6,5,6,5,6,5,6,5,6,5,6,4,5,6,4,5,6,4,5,4,5,4,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,5,6,5,5,6,5};
	for (int8_t i = 0; i < mult; i++){
		newX = cPPLR[curX][newX][rng.nextInt(6)];
	}
	
    return newX;
}

inline int8_t choosePathAdjustNewX(const Map &map, const int8_t curX, const int8_t curY, int8_t newEdgeX) {
    /* old code:
    if (curX != 0) {
        auto right_node = map.getNode(curX - 1, curY);
        if (right_node.edgeCount > 0) {
            int8_t left_edge_of_right_node = right_node.getMaxEdge();
            if (left_edge_of_right_node > newEdgeX) {
                newEdgeX = left_edge_of_right_node;
            }
        }
    }

    if (curX < ROW_END_NODE) {
        auto right_node = map.getNode(curX + 1, curY);
        if (right_node.edgeCount > 0) {
            int8_t left_edge_of_right_node = right_node.getMinEdge();
            if (left_edge_of_right_node < newEdgeX) {
                newEdgeX = left_edge_of_right_node;
            }
        }
    }
    return newEdgeX;
    */
    
    static constexpr int8_t LEFT[7] = {7,0,1,2,3,4,5};
	static constexpr int8_t cPANX[7][9][8] = {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,2,2,2,2,2,2,0,1,2,3,3,3,3,3,0,1,2,3,4,4,4,4,0,1,2,3,4,5,5,5,0,1,2,3,4,5,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,2,2,2,2,2,2,0,1,2,3,3,3,3,3,0,1,2,3,4,4,4,4,0,1,2,3,4,5,5,5,0,1,2,3,4,5,6,6,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,2,2,2,2,2,2,0,1,2,2,2,2,2,2,0,1,2,2,2,2,2,2,0,1,2,3,3,3,3,3,0,1,2,3,4,4,4,4,0,1,2,3,4,5,5,5,0,1,2,3,4,5,6,6,0,1,2,2,2,2,2,2,0,1,2,2,2,2,2,2,0,1,2,3,3,3,3,3,0,1,2,3,3,3,3,3,0,1,2,3,3,3,3,3,0,1,2,3,3,3,3,3,0,1,2,3,4,4,4,4,0,1,2,3,4,5,5,5,0,1,2,3,4,5,6,6,0,1,2,3,3,3,3,3,0,1,2,3,3,3,3,3,0,1,2,3,4,4,4,4,0,1,2,3,4,4,4,4,0,1,2,3,4,4,4,4,0,1,2,3,4,4,4,4,0,1,2,3,4,4,4,4,0,1,2,3,4,5,5,5,0,1,2,3,4,5,6,6,0,1,2,3,4,4,4,4,0,1,2,3,4,4,4,4,0,1,2,3,4,5,5,5,0,1,2,3,4,5,5,5,0,1,2,3,4,5,5,5,0,1,2,3,4,5,5,5,0,1,2,3,4,5,5,5,0,1,2,3,4,5,5,5,0,1,2,3,4,5,6,6,0,1,2,3,4,5,5,5,0,1,2,3,4,5,5,5,0,1,2,3,4,5,6,6,0,1,2,3,4,5,6,6,0,1,2,3,4,5,6,6,0,1,2,3,4,5,6,6,0,1,2,3,4,5,6,6,0,1,2,3,4,5,6,6,0,1,2,3,4,5,6,6,0,1,2,3,4,5,6,6,0,1,2,3,4,5,6,6};
	
	return cPANX[
		newEdgeX][
		Map::NEIGH[map.getNode(LEFT[curX], curY).edgeBits][1]][
		Map::NEIGH[map.getNode(curX + 1, curY).edgeBits][0]
	];
}

int8_t chooseNewPath(Map &map, Random &rng, const uint8_t curX, const uint8_t curY) {
    /* old code:
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
    */
    
    static constexpr int8_t NEXT[7][6] = {0,1,0,1,0,1,0,1,2,0,1,2,1,2,3,1,2,3,2,3,4,2,3,4,3,4,5,3,4,5,4,5,6,4,5,6,5,6,5,6,5,6};
	int8_t newEdgeX = choosePathParentLoopRandomizer(map, rng, curX, curY, NEXT[curX][rng.nextInt(6)]);
    return choosePathAdjustNewX(map, curX, curY, newEdgeX);



}

void createPathsIteration(Map &map, Random &rng, const uint8_t startX) {
    uint8_t curX = startX;
    for (uint8_t curY = 0; curY < MAP_HEIGHT-1; ++curY) {
        const uint8_t newX = chooseNewPath(map, rng, curX, curY);
        map.getNode(curX, curY).addEdge(newX);
        map.getNode(newX, curY+1).addParent(curX);
        curX = newX;
    }
    map.getNode(curX, 14).addEdge(3);
}

void createPaths(Map &map, Random &mapRng) {
    const uint8_t firstStartX = randRange(mapRng, 0, MAP_WIDTH - 1);
    createPathsIteration(map, mapRng, firstStartX);

    for(uint8_t i = 1; i < PATH_DENSITY; ++i) {
        uint8_t startX = randRange(mapRng, 0, MAP_WIDTH - 1);

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

        /*
        I added an 8th (dud) node to each row 
        it caused an extra "   " to be added to each row
        now we explicitly check only 7 nodes on each row
        */
        //for (auto &node : nodes.at(row_num)) {
        for (int i = 0; i < MAP_WIDTH; i++){
            auto &node = nodes.at(row_num)[i];
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

        /*
        I added an 8th (dud) node to each row 
        it caused an extra "   " to be added to each row
        now we explicitly check only 7 nodes on each row
        */
        //for (auto &node : nodes.at(row_num)) {
        for (int i = 0; i < MAP_WIDTH; i++){
            auto &node = nodes.at(row_num)[i];
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


/*
prints map to a string in the following format:
a1,a2,b1,b2,...
    15 * 7 pairs of integers separated by commas

each pair x1,x2 encodes information about a node:
    x1: the node type
        SHOP = 0,
        REST = 1,
        EVENT = 2,
        ELITE (burning) = 3,
        MONSTER = 4,
        TREASURE = 5,
        BOSS = 6,
        NONE = 7,
        ELITE (normal) = 8
    x2:
        the set of edges (i.e., its out-neighborhood)
        encoded as an 8-bit integer

the pair correspond to nodes which are sorted 
w.r.t the (y, x) lexicographic ordering
e.g., (y1, x1) comes before (y2, x2) iff
    y1 < y2, OR 
    y1 = y2 AND x1 < x2
*/
std::string Map::toGraphString() const {
    std::string lstr, estr;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        std::cout << "y = " << y << '\n';
        auto &row = nodes.at(y);
        for (int x = 0; x < MAP_WIDTH; x++){
            auto &node = row[x];
            
            lstr += 
                (
                    node.room == Room::ELITE 
                    && y == burningEliteY 
                    && x == burningEliteX) 
                ? 'F' : node.getRoomSymbol();
            
            /*
            std::cout << "\tx = " << x 
            << " (" << node.getRoomSymbol() << ") ["
            << static_cast<int>(node.edgeBits) << "]\n" ;
            
            for (int i = 0; i < node.edgeCount; i++){
                int x2 = node.edges[i];
                auto &node2 = nodes[y+1][x2];
                std::cout << " \t\t~ " << x2 
                << " (" << node2.getRoomSymbol() << ")\n";
            }
            */
            
            estr += std::to_string(static_cast<int>(node.edgeBits)) + ',';
        }
    }
    
    return lstr + estr;
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
        auto &row = map.nodes.at(r);
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

        auto &row = map.nodes.at(r);
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
            if (map.getNode(col,row).room == sts::Room::ELITE) {
                eliteRooms[eliteRoomCount++] = IntTuple(col,row);
            }
        }
    }

    // if number of elite rooms is 1 it will crash the base game too.
    int idx = mapRng.random(eliteRoomCount-1);
    map.burningEliteX = eliteRooms.at(idx).x;
    map.burningEliteY = eliteRooms.at(idx).y;
    int buff = mapRng.random(3);
    switch (buff) {
    case 0:
        map.eliteBuff = EliteBuff::STRENGTH;
        break;
    case 1:
        map.eliteBuff = EliteBuff::MAX_HP;
        break;
    case 2:
        map.eliteBuff = EliteBuff::METALLICIZE;
        break;
    case 3:
        map.eliteBuff = EliteBuff::REGENERATE;
        break;
    default:
        map.eliteBuff = EliteBuff::NONE;
    }
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