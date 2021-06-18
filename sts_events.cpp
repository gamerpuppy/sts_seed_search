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
        int shopSize = (s.curRoom == sts::Room::SHOP ? 0 : (int) (s.shopChance * 100)) + monsterSize;
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


Event GameState::getEventRoomEvent() {
        auto res = roll(*this);
        switch (res) {
            case Room::EVENT: {
                auto event = generateEvent(eventRng, *this);
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



Rewards GameState::getCombatRewards(GameState &s, Room room, bool roomHasEmeraldKey) {
    Rewards rewards;
    if (room == sts::Room::MONSTER) {
        rewards.addGold(s.treasureRng.random(10,20));

    } else if (room == sts::Room::ELITE){
        rewards.addGold(s.treasureRng.random(25,35));
        rewards.addRelic(returnRandomRelic(rollRandomRelicTier(s.relicRng)));
        if (playerHasRelic(BLACK_STAR)) {
            rewards.addRelic(returnNonCampfireRelic(rollRandomRelicTier(s.relicRng)));
        }
        rewards.emeraldKey = roomHasEmeraldKey;

    } else {
        // room == BOSS
        Random miscRng(s.seed+s.floor);
        int goldReward = 100 + miscRng.random(-5,5);
        rewards.addGold(goldReward);
    }

    // not if the act is beyond or ending??
    addPotionToRewards(rewards);

    // cards

    return rewards;
}



bool GameState::relicCanSpawn(Relic relic) const {
    switch (relic) {

        case FROZEN_CORE:
            return playerHasRelic(CRACKED_CORE);

        case BURNING_BLOOD:
            return playerHasRelic(BURNING_BLOOD);

        case RING_OF_THE_SERPENT:
            return playerHasRelic(RING_OF_THE_SNAKE);

        case HOLY_WATER:
            return playerHasRelic(PURE_WATER);

        case ECTOPLASM:
            return act > 1;

        case TINY_CHEST:
            return floor <= 35;

        case WING_BOOTS:
        case MATRYOSHKA:
            return floor <= 40;

        case GIRYA:
        case PEACE_PIPE:
        case SHOVEL:
            return floor < 48 && hasLessThanTwoCampfireRelics();

        case MAW_BANK:
        case OLD_COIN:
        case SMILING_MASK:
            return floor <= 48 && curRoom != Room::SHOP;

        case ANCIENT_TEA_SET:
        case CERAMIC_FISH:
        case DARKSTONE_PERIAPT:
        case DREAM_CATCHER:
        case FROZEN_EGG:
        case JUZU_BRACELET:
        case MEAL_TICKET:
        case MEAT_ON_THE_BONE:
        case MOLTEN_EGG:
        case OMAMORI:
        case POTION_BELT:
        case PRAYER_WHEEL:
        case QUESTION_CARD:
        case REGAL_PILLOW:
        case SINGING_BOWL:
        case THE_COURIER:
        case TOXIC_EGG:
            return floor <= 48;

        case PRESERVED_INSECT:
            return floor <= 52;

        default:
            return true;
    }
}

// MonsterRoomElite
RelicTier sts::rollRandomRelicTier(Random &relicRng) {
    int roll = relicRng.random(0,99);
    if (roll < 50) {
        return RelicTier::COMMON;
    } else if (roll > 82) {
        return RelicTier::RARE;
    } else {
        return RelicTier::UNCOMMON;
    }
}

Relic GameState::returnRandomRelic(RelicTier tier, bool front) {

    Relic retVal = INVALID;
    std::vector<Relic> *vec;

    switch(tier) {

        case RelicTier::COMMON:
            if (commonRelicPool.empty()) {
                retVal = returnRandomRelic(RelicTier::UNCOMMON);
            } else {
                vec = &commonRelicPool;
            }
            break;

        case RelicTier::UNCOMMON:
            if (uncommonRelicPool.empty()) {
                retVal = returnRandomRelic(RelicTier::RARE);
            } else {
                vec = &uncommonRelicPool;
            }
            break;

        case RelicTier::RARE:
            if (rareRelicPool.empty()) {
                retVal = Relic::CIRCLET;
            } else {
                vec = &rareRelicPool;
            }
            break;

        case RelicTier::SHOP:
            if (shopRelicPool.empty()) {
                retVal = returnRandomRelic(RelicTier::UNCOMMON);
            } else {
                vec = &shopRelicPool;
            }
            break;

        case RelicTier::BOSS:
            if (bossRelicPool.empty()) {
                retVal = RED_CIRCLET;
            } else {
                vec = &bossRelicPool;
            }
            break;

        default:
            break;
    };

    if (retVal == INVALID) {
        if (front) {
            retVal = vec->front();
            vec->erase(vec->begin());
        } else {
            retVal = vec->back();
            vec->erase(vec->end()-1);
        }
    }

    bool canSpawn = relicCanSpawn(retVal);
    if (canSpawn) {
        return retVal;
    } else {
        return returnRandomRelic(tier, false);
    }
}

bool isCampfireRelic(Relic r) {
    return r == PEACE_PIPE || r == SHOVEL || r == GIRYA;
}

Relic GameState::returnNonCampfireRelic(RelicTier tier) {
    Relic relic;
    do {
        relic = returnRandomRelic(tier);
    } while(isCampfireRelic(relic));
    return relic;
}


Potion sts::returnRandomPotion(Random &potionRng, CharacterClass c, bool limited) {
    PotionRarity rarity;

    int roll = potionRng.random(0,99);
    if (roll < 65) {
        rarity = PotionRarity::COMMON;
    } else if (roll < 90) {
        rarity = PotionRarity::UNCOMMON;
    } else {
        rarity = PotionRarity::RARE;
    }

    return returnRandomPotion(potionRng, rarity, c, limited);
}

Potion sts::returnRandomPotion(Random &potionRng, PotionRarity rarity, CharacterClass c, bool limited) {
    // this is dumb.
    Potion temp = getRandomPotion(potionRng, c);
    bool spamCheck = limited;
    while(potionRarities[static_cast<int>(temp)] != rarity || spamCheck) {
        spamCheck = limited;
        temp = getRandomPotion(potionRng, c);
        if (temp != Potion::FRUIT_JUICE) {
            spamCheck = false;
        }
    }
    return temp;
}

Potion sts::getRandomPotion(Random &potionRng, CharacterClass c) {
    int idx = potionRng.random(32); // all characters have 33 possible potions
    return getPotionFromPool(idx, c);
}

void GameState::addPotionToRewards(Rewards &rewards) {
    int chance = 0;
    if (curRoom == Room::ELITE ||
        curRoom == Room::MONSTER ||
        curRoom == Room::EVENT
    ) {
        // if normal and monsters can not have escaped
        chance = 40 + potionChance;
    }

    if (playerHasRelic(WHITE_BEAST_STATUE)) {
        chance = 100;
    }

    // todo ?
//    if (rewards.size() >= 4) {
//        chance = 0;
//    }

    if (potionRng.random(99) >= chance) {
        potionChance += 10;

    } else {
        rewards.addPotion(returnRandomPotion(potionRng, characterClass, false));
        potionChance -= 10;
    }
}


Potion sts::getPotionFromPool(int idx, CharacterClass characterClass) {
    switch (characterClass) {
        case CharacterClass::IRONCLAD:
            return Ironclad::potions.at(idx);

        case CharacterClass::SILENT:
            return Silent::potions.at(idx);

        case CharacterClass::DEFECT:
            return Defect::potions.at(idx);

        case CharacterClass::WATCHER:
            return Watcher::potions.at(idx);

        default:
            return Potion::INVALID;
    }

}


//        cardBlizzStartOffset = 5;
//        cardBlizzRandomizer = cardBlizzStartOffset;
//        cardBlizzGrowth = 1;
//        cardBlizzMaxOffset = -40;

CardRarity GameState::rollCardRarity() {
    static constexpr int BASE_RARE_CHANCE = 3;
    static constexpr int BASE_UNCOMMON_CHANCE = 37;

    int roll = cardRng.random(99) + cardChanceAdjustment;

    int rareCardChance = playerHasRelic(NLOTHS_GIFT) ? 9 : 3;

    if (roll < rareCardChance) {
        return CardRarity::RARE;
    } else if (roll < rareCardChance + BASE_UNCOMMON_CHANCE) {
        return CardRarity::UNCOMMON;
    } else {
        return CardRarity::COMMON;
    }
}




std::array<Card, 4> GameState::getRewardCards() {
    int numCards = 3;
    if (playerHasRelic(QUESTION_CARD)) {
        numCards += 1;
    }
    if (playerHasRelic(BUSTED_CROWN)) {
        numCards -= 2;
    }

    std::array<Card, 4> cardReward = {};
    std::array<CardRarity, 4> rewardRarities = {};

    for (int i = 0; i < numCards; ++i) {
        auto rarity = rollCardRarity();

        rewardRarities.at(i) = rarity;
        switch (rarity) {
            case CardRarity::COMMON:
                cardChanceAdjustment  = std::max(cardChanceAdjustment-1, -40);
                break;

            case CardRarity::RARE:
                cardChanceAdjustment = 5;
                break;

            default:
                break;
        }

        Card card;
        bool hasDuplicate = true;
        while (hasDuplicate) {

            if (playerHasRelic(PRISMATIC_SHARD)) {
                card = getAnyColorCard(cardRng, rarity);
            } else {
                card = getCard(cardRng, rarity, characterClass);
            }

            hasDuplicate = false;
            for (int x = 0; x < i; ++x) {
                if (cardReward.at(x) == card) {
                    hasDuplicate = true;
                    break;
                }
            }
        }
        cardReward.at(i) = card;
    }

    // upgrades


    for (int i = 0; i < numCards; ++i) {
        if (rewardRarities.at(i) != CardRarity::RARE) {
            cardRng.randomBoolean(0);
        }
    }

    return cardReward;
}


Card getIroncladCard(Random &cardRng, CardRarity rarity) {
    switch (rarity) {

        case CardRarity::COMMON: {
            int idx = cardRng.random(static_cast<int>(Ironclad::commonCardPool.size()-1));
            return Ironclad::commonCardPool.at(idx);
        }

        case CardRarity::UNCOMMON: {
            int idx = cardRng.random(static_cast<int>(Ironclad::uncommonCardPool.size()-1));
            return Ironclad::uncommonCardPool.at(idx);
        }

        case CardRarity::RARE: {
            int idx = cardRng.random(static_cast<int>(Ironclad::rareCardPool.size()-1));
            return Ironclad::rareCardPool.at(idx);
        }

        case CardRarity::CURSE: {
            int idx = cardRng.random(static_cast<int>(curseCardPool.size() - 1));
            return curseCardPool.at(idx);
        }

        default:
            return Card::NONE;
    }
}

Card getSilentCard(Random &cardRng, CardRarity rarity) {
    switch (rarity) {

        case CardRarity::COMMON: {
            int idx = cardRng.random(static_cast<int>(Silent::commonCardPool.size())-1);
            return Silent::commonCardPool.at(idx);
        }

        case CardRarity::UNCOMMON: {
            int idx = cardRng.random(static_cast<int>(Silent::uncommonCardPool.size())-1);
            return Silent::uncommonCardPool.at(idx);
        }

        case CardRarity::RARE: {
            int idx = cardRng.random(static_cast<int>(Silent::rareCardPool.size())-1);
            return Silent::rareCardPool.at(idx);
        }

        case CardRarity::CURSE: {
            int idx = cardRng.random(static_cast<int>(curseCardPool.size()) - 1);
            return curseCardPool.at(idx);
        }

        default:
            return Card::NONE;
    }
}

Card getDefectCard(Random &cardRng, CardRarity rarity) {
    switch (rarity) {

        case CardRarity::COMMON: {
            int idx = cardRng.random(static_cast<int>(Defect::commonCardPool.size())-1);
            return Defect::commonCardPool.at(idx);
        }

        case CardRarity::UNCOMMON: {
            int idx = cardRng.random(static_cast<int>(Defect::uncommonCardPool.size())-1);
            return Defect::uncommonCardPool.at(idx);
        }

        case CardRarity::RARE: {
            int idx = cardRng.random(static_cast<int>(Defect::rareCardPool.size())-1);
            return Defect::rareCardPool.at(idx);
        }

        case CardRarity::CURSE: {
            int idx = cardRng.random(static_cast<int>(curseCardPool.size()) - 1);
            return curseCardPool.at(idx);
        }

        default:
            return Card::NONE;
    }
}

Card getWatcherCard(Random &cardRng, CardRarity rarity) {
    switch (rarity) {

        case CardRarity::COMMON: {
            int idx = cardRng.random(static_cast<int>(Watcher::commonCardPool.size())-1);
            return Watcher::commonCardPool.at(idx);
        }

        case CardRarity::UNCOMMON: {
            int idx = cardRng.random(static_cast<int>(Watcher::uncommonCardPool.size())-1);
            return Watcher::uncommonCardPool.at(idx);
        }

        case CardRarity::RARE: {
            int idx = cardRng.random(static_cast<int>(Watcher::rareCardPool.size())-1);
            return Watcher::rareCardPool.at(idx);
        }

        case CardRarity::CURSE: {
            int idx = cardRng.random(static_cast<int>(curseCardPool.size()) - 1);
            return curseCardPool.at(idx);
        }

        default:
            return Card::NONE;
    }
}

Card sts::getCard(Random &cardRng, CardRarity rarity, CharacterClass c) {
    switch (c) {
        case CharacterClass::IRONCLAD:  return getIroncladCard(cardRng, rarity);
        case CharacterClass::SILENT:    return getSilentCard(cardRng, rarity);
        case CharacterClass::DEFECT:    return getDefectCard(cardRng, rarity);
        case CharacterClass::WATCHER:   return getWatcherCard(cardRng, rarity);
        default: return sts::Card::NONE;
    }
}

Card sts::getAnyColorCard(Random &cardRng, CardRarity rarity) {
    switch (rarity) {
        case CardRarity::COMMON: {
            int idx = cardRng.random(static_cast<int>(allColorCommonCards.size()) - 1);
            return allColorCommonCards.at(idx);
        }

        case CardRarity::UNCOMMON: {
            int idx = cardRng.random(static_cast<int>(allColorUncommonCards.size())-1);
            return allColorUncommonCards.at(idx);
        }

        case CardRarity::RARE: {
            int idx = cardRng.random(static_cast<int>(allColorRareCards.size())-1);
            return allColorRareCards.at(idx);
        }

        default: return Card::NONE;
    }
}

//
//public static ArrayList<AbstractCard> getRewardCards() {
//    ArrayList<AbstractCard> retVal = new ArrayList();
//    int numCards = 3;
//
//    AbstractRelic r;
//    for(Iterator var2 = player.relics.iterator(); var2.hasNext(); numCards = r.changeNumberOfCardsInReward(numCards)) {
//        r = (AbstractRelic)var2.next();
//    }
//
//    if (ModHelper.isModEnabled("Binary")) {
//        --numCards;
//    }
//
//    AbstractCard card;
//    for(int i = 0; i < numCards; ++i) {
//        CardRarity rarity = rollRarity();
//        card = null;
//        switch(rarity) {
//            case COMMON:
//                cardBlizzRandomizer -= cardBlizzGrowth;
//                if (cardBlizzRandomizer <= cardBlizzMaxOffset) {
//                    cardBlizzRandomizer = cardBlizzMaxOffset;
//                }
//            case UNCOMMON:
//                break;
//            case RARE:
//                cardBlizzRandomizer = cardBlizzStartOffset;
//                break;
//            default:
//                logger.info("WTF?");
//        }
//
//        boolean containsDupe = true;
//
//        while(true) {
//            while(containsDupe) {
//                containsDupe = false;
//                if (player.hasRelic("PrismaticShard")) {
//                    card = CardLibrary.getAnyColorCard(rarity);
//                } else {
//                    card = getCard(rarity);
//                }
//
//                Iterator var6 = retVal.iterator();
//
//                while(var6.hasNext()) {
//                    AbstractCard c = (AbstractCard)var6.next();
//                    if (c.cardID.equals(card.cardID)) {
//                        containsDupe = true;
//                        break;
//                    }
//                }
//            }
//
//            if (card != null) {
//                retVal.add(card);
//            }
//            break;
//        }
//    }
//
//    ArrayList<AbstractCard> retVal2 = new ArrayList();
//    Iterator var11 = retVal.iterator();
//
//    while(var11.hasNext()) {
//        card = (AbstractCard)var11.next();
//        retVal2.add(card.makeCopy());
//    }
//
//    var11 = retVal2.iterator();
//
//    while(true) {
//        while(var11.hasNext()) {
//            card = (AbstractCard)var11.next();
//            if (card.rarity != CardRarity.RARE && cardRng.randomBoolean(cardUpgradedChance) && card.canUpgrade()) {
//                card.upgrade();
//            } else {
//                Iterator var12 = player.relics.iterator();
//
//                while(var12.hasNext()) {
//                    AbstractRelic r = (AbstractRelic)var12.next();
//                    r.onPreviewObtainCard(card);
//                }
//            }
//        }
//
//        return retVal2;
//    }
//}




