//
// Created by keega on 6/13/2021.
//

#include "sts_events.h"

using namespace sts;


bool canAddShrine(Event event, const GameState &s) {
    switch (event) {

        case sts::Event::FOUNTAIN_OF_CLEANSING:
            return s.skipReq_FOUNTAIN_OF_CLEANSING || s.playerisCursed();

        case Event::DESIGNER:
            return  (s.act == 2 || s.act == 3) && (s.skipReq_DESIGNER || s.playerGold >= 75);

        case Event::DUPLICATOR:
            return s.act == 2 || s.act == 3;

        case Event::FACE_TRADER:
            return s.act == 1 || s.act == 2;

        case Event::KNOWING_SKULL:
            return s.act == 2 && (s.skipReq_KNOWING_SKULL || s.curPlayerHealth > 12);

        case Event::NLOTH:
            return s.act == 2 && (s.skipReq_NLOTH || s.playerRelicsSize() >= 2);

        case Event::THE_JOUST:
            return s.act == 2 && (s.skipReq_THE_JOUST || s.playerGold >= 50);

        case Event::THE_WOMAN_IN_BLUE:
            return s.act == 2 && (s.skipReq_WOMAN_IN_BLUE || s.playerGold >= 50);

        case Event::SECRET_PORTAL:
            return s.act == 3 && (s.skipReq_SECRET_PORTAL || s.playtime >= 800.0f);

        default:
            return true;
    }
}


Event getShrine(Random rng, GameState &s) {
    int tempLength = 0;
    Event tempShrines[20];

    for (auto shrine : s.shrineList) {
        tempShrines[tempLength++] = shrine;
    }

    for (auto event : s.specialOneTimeEventList) {
        if (canAddShrine(event, s)) {
            tempShrines[tempLength++] = event;
        }
    }

    auto idx = rng.random(tempLength-1);
    return tempShrines[idx];
}


bool canAddEvent(Event event, const GameState &s) {
    switch (event) {
        case Event::DEAD_ADVENTURER:
        case Event::MUSHROOMS:
            return s.floor > 6;

        case Event::THE_MOAI_HEAD: {
            bool playerAtLessHalf =
                    s.curPlayerHealth <= s.maxPlayerHealth/2;
            return s.skipReq_THE_MOAI_HEAD || (playerAtLessHalf || s.playerHasRelic(GOLDEN_IDOL));
        }

        case Event::THE_CLERIC:
            return s.skipReq_THE_CLERIC || s.playerGold >= 35;

        case Event::BEGGAR:
            return s.skipReq_BEGGAR || s.playerGold >= 75;

        case Event::COLOSSEUM:
            return s.curMapNodeY > 7;

        default:
            return true;
    }
}

Event getEvent(Random rng, GameState &s) {
    int tempLength = 0;
    Event tempEvents[14];

    for (auto event : s.eventList) {
        if (canAddEvent(event, s)) {
            tempEvents[tempLength++] = event;
        }
    }

    auto idx = rng.random(tempLength-1);
    Event event = tempEvents[idx];

    auto eventListPos = std::find(s.eventList.begin(), s.eventList.end(), event);
    s.eventList.erase(eventListPos);
    return tempEvents[idx];
}

// AbstractDungeon.generateEvent()
Event generateEvent(Random rng, GameState &s) {
    auto roll = rng.random(1.0f);

    if (roll >= SHRINE_CHANCE) {
        auto event = getEvent(rng, s);
        if (event == sts::Event::INVALID) {
            return getShrine(rng, s);
        }
        return event;
    }

    if (s.shrineList.empty() && s.specialOneTimeEventList.empty()) {

        if (s.eventList.empty()) {
            return sts::Event::INVALID;
        } else {
            return getEvent(rng, s);
        }

    } else {
        return getShrine(rng, s);
    }
}


Room roll(GameState &s) {
    float roll = s.eventRng.random();
    Room choice = Room::NONE;

    if (s.playerHasRelic(TINY_CHEST)) {
        s.tinyChestCounter = 0;
        if (s.tinyChestCounter == 4) {
            s.tinyChestCounter = 0;
            choice = sts::Room::TREASURE;
        }
    }

    if (choice != sts::Room::TREASURE) {
        int monsterSize = (int) (s.monsterChance * 100);
        int shopSize = (s.lastRoom == sts::Room::SHOP ? 0 : (int) (s.shopChance * 100)) + monsterSize;
        int treasureSize = (int) (s.treasureChance * 100) + shopSize;

        int idx = (int) (roll * 100);

        if (idx < monsterSize) {
            choice = Room::MONSTER;
        } else if (idx < shopSize) {
            choice = Room::SHOP;
        } else if (idx < treasureSize) {
            choice = Room::TREASURE;
        } else {
            choice = Room::EVENT;
        }
    }

    if (choice == Room::MONSTER) {
        if (s.playerHasRelic(JUZU_BRACELET)) {
            choice = Room::EVENT;
        }
        s.monsterChance = 0.1F;
    } else {
        s.monsterChance += 0.1F;
    }

    if (choice == Room::SHOP) {
        s.shopChance = 0.03F;
    } else {
        s.shopChance += 0.03F;
    }

    if (choice == Room::TREASURE) {
        s.treasureChance = 0.02F;
    } else {
        s.treasureChance += 0.02F;
    }

    return choice;
}


Event sts::getEventRoomEvent(GameState &s) {
        auto res = roll(s);
        switch (res) {
            case Room::EVENT: {
                auto event = generateEvent(s.eventRng, s);
                return event;
            }

            case Room::SHOP:
                return Event::SHOP;
            case Room::MONSTER:
                return Event::MONSTER;
            case Room::TREASURE:
                return Event::TREASURE;

            default:
                return Event::INVALID;
        }
}























