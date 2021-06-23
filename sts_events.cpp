//
// Created by keega on 6/13/2021.
//

#include <cmath>
#include "sts_events.h"

#include <sstream>

using namespace sts;

void appendCardReward(std::stringstream &ss, CardReward cardReward) {
    ss << "{ ";
    for (int i = 0; i < 4; ++i) {
        Card c = cardReward.cards[i];

        if (c == sts::Card::INVALID) {
            break;
        }

        ss << cardNames[(int)c] << ", ";
    }
    ss << "}";
}



std::string Rewards::toString() const {
    std::stringstream ss;
    ss << "Reward {\n";
    for (int i = 0; i < cardRewardCount; ++i) {
        appendCardReward(ss, cards[i]);
        ss << '\n';
    }

    for (int i = 0; i < goldRewardCount; ++i) {
        auto g = gold[i];
        ss << std::to_string(g) << "g" << '\n';
    }

    for (int i = 0; i < potionCount; ++i) {
        auto p = potions[i];
        ss << potionNames[(int)p] << '\n';
    }

    for (int i = 0; i < relicCount; ++i) {
        auto r = relics[i];
        ss << relicNames[r] << '\n';
    }

    if (emeraldKey) {
        ss << "emerald key\n";
    }
    if (sapphireKey) {
        ss << "sapphire key\n";
    }

    ss << "}\n";

    return ss.str();
}


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


Room roll(GameState &s, Room room) {
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
        int shopSize = (room == sts::Room::SHOP ? 0 : (int) (s.shopChance * 100)) + monsterSize;
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

std::string ShopScreen::toString(bool withPrices) const {
    std::stringstream ss;
    ss << "Shop { ";
    ss << '\n';
    for (int i = 0; i < cards.size(); ++i) {
        Card c = cards[i].card;
        ss << cardNames[(int)c];
        if (withPrices) {
            ss << ":";
            ss << std::to_string(cards[i].price);
        }
        ss << ", ";
    }
    ss << '\n';

    for (int i = 0; i < relics.size(); ++i) {
        Relic r = relics[i].relic;

        ss << relicNames[(int)r];
        if (withPrices) {
            ss << ":";
            ss << relics[i].price;
        }
        ss << ", ";
    }
    ss << '\n';
    for (int i = 0; i < potions.size(); ++i) {
        Potion p = potions[i].potion;

        ss << potionNames[(int)p];
        if (withPrices) {
            ss << ":";
            ss << potions[i].price;
        }
        ss << ", ";
    }
    ss << '\n';
    ss << " }";

    return ss.str();
}


Event GameState::getEventRoomEvent() {
        auto res = roll(*this, Room::EVENT);
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



Rewards GameState::getCombatRewards(Room room, bool roomHasEmeraldKey) {
    Rewards rewards;
    if (room == sts::Room::MONSTER) {
        rewards.addGold(treasureRng.random(10,20));

    } else if (room == sts::Room::ELITE){
        rewards.addGold(treasureRng.random(25,35));
        rewards.addRelic(returnRandomRelic(rollRelicTier(relicRng), room));
        if (playerHasRelic(BLACK_STAR)) {
            rewards.addRelic(returnNonCampfireRelic(rollRelicTier(relicRng), room));
        }
        rewards.emeraldKey = roomHasEmeraldKey;

    } else {
        // room == BOSS
        Random miscRng(seed+floor);
        int goldReward = 100 + miscRng.random(-5,5);
        rewards.addGold(goldReward);
    }

    // not if the act is beyond or ending??
    addPotionToRewards(rewards);


    // cards
    // if !event.noCardsInRewards and not treasure Room or rest room and other conditions
    rewards.cards[0] = getCardReward();
    rewards.cardRewardCount = 1;
//    if (room == Room::BOSS) {
//
//
//    } else {
//
//
//    }


    return rewards;
}

bool GameState::relicCanSpawn(Relic relic, Room room) const {
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
            return floor <= 48 && room != Room::SHOP;

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
RelicTier sts::rollRelicTier(Random &relicRng) {
    int roll = relicRng.random(0,99);
    if (roll < 50) {
        return RelicTier::COMMON;
    } else if (roll > 82) {
        return RelicTier::RARE;
    } else {
        return RelicTier::UNCOMMON;
    }
}

Relic GameState::returnRandomRelic(RelicTier tier, Room room, bool front) {

    Relic retVal = INVALID;
    std::vector<Relic> *vec;

    switch(tier) {

        case RelicTier::COMMON:
            if (commonRelicPool.empty()) {
                retVal = returnRandomRelic(RelicTier::UNCOMMON, room);
            } else {
                vec = &commonRelicPool;
            }
            break;

        case RelicTier::UNCOMMON:
            if (uncommonRelicPool.empty()) {
                retVal = returnRandomRelic(RelicTier::RARE, room);
            } else {
                vec = &uncommonRelicPool;
            }
            break;

        case RelicTier::RARE:
            if (rareRelicPool.empty()) {
                retVal = CIRCLET;
            } else {
                vec = &rareRelicPool;
            }
            break;

        case RelicTier::SHOP:
            if (shopRelicPool.empty()) {
                retVal = returnRandomRelic(RelicTier::UNCOMMON, room);
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

    bool canSpawn = relicCanSpawn(retVal, room);
    if (canSpawn) {
        return retVal;
    } else {
        return returnRandomRelic(tier, room, false);
    }
}

bool isCampfireRelic(Relic r) {
    return r == PEACE_PIPE || r == SHOVEL || r == GIRYA;
}

Relic GameState::returnNonCampfireRelic(RelicTier tier, Room room) {
    Relic relic;
    do {
        relic = returnRandomRelic(tier, room);
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
    // assume if in a monsters room, they didnt escape
    int chance = 40 + potionChance;

    if (playerHasRelic(WHITE_BEAST_STATUE)) {
        chance = 100;
    }

    int rewardsSize = rewards.potionCount + rewards.relicCount + rewards.goldRewardCount + rewards.cardRewardCount;
    if (rewardsSize >= 4) {
        chance = 0;
    }

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

    } else if (roll >= rareCardChance + BASE_UNCOMMON_CHANCE) {

        return CardRarity::COMMON;

    } else {
        return CardRarity::UNCOMMON;
    }
}

CardRarity GameState::rollCardRarityShop() {
    static constexpr int BASE_RARE_CHANCE = 9;
    static constexpr int BASE_UNCOMMON_CHANCE = 37;

    int roll = cardRng.random(99);
    roll += cardChanceAdjustment;

    if (roll < BASE_RARE_CHANCE) {
        return CardRarity::RARE;

    } else if (roll >= BASE_RARE_CHANCE + BASE_UNCOMMON_CHANCE) {

        return CardRarity::COMMON;

    } else {
        return CardRarity::UNCOMMON;
    }
}


CardReward GameState::getCardReward() {
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

    CardReward reward{numCards, cardReward};
    return reward;
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
            return Card::INVALID;
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
            return Card::INVALID;
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
            return Card::INVALID;
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
            return Card::INVALID;
    }
}

Card sts::getCard(Random &cardRng, CardRarity rarity, CharacterClass c) {
    switch (c) {
        case CharacterClass::IRONCLAD:  return getIroncladCard(cardRng, rarity);
        case CharacterClass::SILENT:    return getSilentCard(cardRng, rarity);
        case CharacterClass::DEFECT:    return getDefectCard(cardRng, rarity);
        case CharacterClass::WATCHER:   return getWatcherCard(cardRng, rarity);
        default: return sts::Card::INVALID;
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

        default: return Card::INVALID;
    }
}

Card sts::getColorlessCardFromPool(Random &cardRng, CardRarity rarity) {
    int size = CardPools::getColorlessGroupSize(rarity);
    int idx = cardRng.random(size-1);
    return CardPools::getColorlessCardAt(rarity, idx);
}

Card sts::getRandomCard(Random &cardRng, CardType type, CardRarity rarity, CharacterClass c) {
    int size = CardPools::getGroupSize(c, type, rarity);
    int idx = cardRng.random(size-1);
    return CardPools::getCardAt(c, type, rarity, idx);
}

void shopAssignRandomCardExluding(GameState &gs, CardType type, Card excludeCard, Card &card, CardRarity &rarity) {
    do {
        rarity = gs.rollCardRarityShop();
        card = getRandomCard(gs.cardRng, type, rarity, gs.characterClass);
    }while (card == excludeCard);
}

ShopScreen GameState::getShopScreen() {
    ShopScreen shopScreen;
    shopInitCards(shopScreen);
    shopInitRelics(shopScreen);
    shopInitPotions(shopScreen);
    return shopScreen;
}

void GameState::shopInitCards(ShopScreen &shop) {
    CardRarity rarities[5];

    shop.cards[1] = CardShopItem();
    shop.cards[3] = CardShopItem();

    rarities[0] = rollCardRarityShop();
    shop.cards[0] = getRandomCard(cardRng, CardType::ATTACK, rarities[0], characterClass);
    shopAssignRandomCardExluding(*this, CardType::ATTACK, shop.cards[0].card, shop.cards[1].card, rarities[1]);

    rarities[2] = rollCardRarityShop();
    shop.cards[2] = getRandomCard(cardRng, CardType::SKILL, rarities[2], characterClass);
    shopAssignRandomCardExluding(*this, CardType::SKILL, shop.cards[2].card, shop.cards[3].card, rarities[3]);

    rarities[4] = rollCardRarityShop();
    rarities[4] = rarities[4] == CardRarity::COMMON ? CardRarity::UNCOMMON : CardRarity::RARE;
    shop.cards[4] = getRandomCard(cardRng, CardType::POWER, rarities[4], characterClass);

    shop.cards[5] = getColorlessCardFromPool(cardRng, CardRarity::UNCOMMON);
    shop.cards[6] = getColorlessCardFromPool(cardRng, CardRarity::RARE);

    static const int rarityCosts[] {50,75,150};
    for (int i = 0; i < 5; ++i) {

        float tmpPrice = rarityCosts[(int)rarities[i]] * merchantRng.random(0.9f, 1.1f);
        shop.cards[i].price = static_cast<int>(tmpPrice);
    }

    shop.cards[5].price = rarityCosts[(int)CardRarity::UNCOMMON] * merchantRng.random(0.9f, 1.1f) * 1.2f;
    shop.cards[6].price = rarityCosts[(int)CardRarity::RARE] * merchantRng.random(0.9f, 1.1f) * 1.2f;

    int saleIdx = merchantRng.random(4);
    shop.cards[saleIdx].price /= 2;
}


void GameState::shopInitRelics(ShopScreen &shop) {
    RelicTier tiers[2];

    tiers[0] = rollRelicTierShop();
    shop.relics[0].relic = returnRandomRelic(tiers[0], Room::SHOP, false);
    shop.relics[0].price = std::round(relicTierPrices[(int)tiers[0]] * merchantRng.random(0.95f, 1.05f));

    tiers[1] = rollRelicTierShop();
    shop.relics[1].relic = returnRandomRelic(tiers[1], Room::SHOP, false);
    shop.relics[1].price = std::round(relicTierPrices[(int)tiers[1]] * merchantRng.random(0.95f, 1.05f));


    shop.relics[2].relic = returnRandomRelic(RelicTier::SHOP, Room::SHOP, false);
    shop.relics[2].price = std::round(relicTierPrices[(int)RelicTier::SHOP] * merchantRng.random(0.95f, 1.05f));
}



void GameState::shopInitPotions(ShopScreen &shop) {
    for (int i = 0; i < 3; ++i) {
        shop.potions[i].potion = returnRandomPotion(potionRng, characterClass);
        const auto rarity = potionRarities[(int)shop.potions[i].potion];
        const int basePrice = potionRarityPrices[(int)rarity];
        shop.potions[i].price = std::round( basePrice * merchantRng.random(0.95f, 1.05f));
    }

}

RelicTier GameState::rollRelicTierShop() {
    int roll = merchantRng.random(99);
    if (roll < 48) {
        return RelicTier::COMMON;
    } else if (roll < 82) {
        return RelicTier::UNCOMMON;
    } else {
        return RelicTier::RARE;
    }
}


void GameState::initEnemies() {
    generateWeakEnemies();
    generateStrongEnemies();
    generateElites();
    boss = getBoss(monsterRng, act);
}




int rollWeightedIdx(float roll, const float *weights, int weightSize) {
    // the base game method can return "ERROR"
    float curWeight = 0.0f;
    for (int i = 0; i < weightSize; ++i) {
        curWeight += weights[i];
        if (roll < curWeight) {
            return i;
        }
    }
    return weightSize - 1;
}


void GameState::populateMonsterList(const MonsterEncounter monsters[], const float weights[], int monstersSize, int numMonsters) {
    for(int i = 0; i < numMonsters; ++i) {
        if (monsterListSize == 0) {
            int idx = rollWeightedIdx(monsterRng.random(), weights, monstersSize);
            monsterList[monsterListSize++] = monsters[idx];

        } else {
            int idx = rollWeightedIdx(monsterRng.random(), weights, monstersSize);
            MonsterEncounter toAdd = monsters[idx];

            if (toAdd != monsterList[monsterListSize-1] &&
                    (monsterListSize < 2 || toAdd != monsterList[monsterListSize-2]) )
            {
                monsterList[monsterListSize++] = toAdd;

            } else {
                --i;
            }
        }
    }
}

void GameState::populateFirstStrongEnemy(const MonsterEncounter monsters[], const float weights[], int monstersSize) {
    auto lastMonster = monsterList[monsterListSize-1];
    while (true) {
        int idx = rollWeightedIdx(monsterRng.random(), weights, monstersSize);
        auto toAdd = monsters[idx];

        switch (toAdd) {

            case MonsterEncounter::LARGE_SLIME:
            case MonsterEncounter::LOTS_OF_SLIMES:
                if (lastMonster == MonsterEncounter::SMALL_SLIMES) {
                    continue;
                }
                break;

            case MonsterEncounter::THREE_LOUSE:
                if (lastMonster == MonsterEncounter::TWO_LOUSE) {
                    continue;
                }
                break;


            case MonsterEncounter::CHOSEN_AND_BYRDS:
                break;
            case MonsterEncounter::SENTRY_AND_SPHERE:
                break;
            case MonsterEncounter::SNAKE_PLANT:
                break;
            case MonsterEncounter::SNECKO:
                break;
            case MonsterEncounter::CENTURION_AND_HEALER:
                break;
            case MonsterEncounter::CULTIST_AND_CHOSEN:
                break;
            case MonsterEncounter::THREE_CULTIST:
                break;
            case MonsterEncounter::SHELLED_PARASITE_AND_FUNGI:
                break;


            case MonsterEncounter::SPIRE_GROWTH:
                break;
            case MonsterEncounter::TRANSIENT:
                break;
            case MonsterEncounter::FOUR_SHAPES:
                break;
            case MonsterEncounter::MAW:
                break;
            case MonsterEncounter::SPHERE_AND_TWO_SHAPES:
                break;
            case MonsterEncounter::JAW_WORM_HORDE:
                break;
            case MonsterEncounter::WRITHING_MASS:
                break;

            default: // should not happen
                break;
        }

        monsterList[monsterListSize++] = toAdd;
        return;
    }
}





void GameState::generateWeakEnemies() {
    constexpr MonsterEncounter weakEnemies[3][5] = {
            { ME::CULTIST, ME::JAW_WORM, ME::TWO_LOUSE, ME::SMALL_SLIMES },
            { ME::SPHERIC_GUARDIAN, ME::CHOSEN, ME::SHELL_PARASITE, ME::THREE_BYRDS, ME::TWO_THIEVES },
            { ME::THREE_DARKLINGS, ME::ORB_WALKER, ME::THREE_SHAPES },
    };
    constexpr float weakWeights[3][5] = {
            { 1.0f/4, 1.0f/4, 1.0f/4, 1.0f/4 },
            { 1.0f/5, 1.0f/5, 1.0f/5, 1.0f/5, 1.0f/5 },
            { 1.0f/3, 1.0f/3, 1.0f/3 }
    };
    constexpr int weakCount[3] {4,5,3};

    populateMonsterList(weakEnemies[act-1], weakWeights[act - 1], weakCount[act - 1], act == 1 ? 3 : 2);
}

void GameState::generateStrongEnemies() {
    constexpr MonsterEncounter strongEnemies[3][10] = {
            { ME::GREMLIN_GANG, ME::LOTS_OF_SLIMES, ME::RED_SLAVER, ME::EXORDIUM_THUGS, ME::EXORDIUM_WILDLIFE, ME::BLUE_SLAVER, ME::LOOTER, ME::LARGE_SLIME, ME::THREE_LOUSE, ME::TWO_FUNGI_BEASTS },
            { ME::CHOSEN_AND_BYRDS, ME::SENTRY_AND_SPHERE, ME::CULTIST_AND_CHOSEN, ME::THREE_CULTIST, ME::SHELLED_PARASITE_AND_FUNGI, ME::SNECKO, ME::SNAKE_PLANT, ME::CENTURION_AND_HEALER },
            { ME::SPIRE_GROWTH, ME::TRANSIENT, ME::FOUR_SHAPES, ME::MAW, ME::SPHERE_AND_TWO_SHAPES, ME::JAW_WORM_HORDE, ME::THREE_DARKLINGS, ME::WRITHING_MASS }
    };
    constexpr float strongWeights[3][10] = {
            { 1.0f/16, 1.0f/16, 1.0f/16, 1.5f/16, 1.5f/16, 2.0f/16, 2.0f/16, 2.0f/16, 2.0f/16, 2.0f/16 },
            { 2.0f/29, 2.0f/29, 3.0f/29, 3.0f/29, 3.0f/29, 4.0f/29, 6.0f/29, 6.0f/29 },
            { 1.0f/8, 1.0f/8, 1.0f/8, 1.0f/8, 1.0f/8, 1.0f/8, 1.0f/8, 1.0f/8,},
    };
    constexpr int strongCount[3] {10, 8, 8};

    populateFirstStrongEnemy(strongEnemies[act-1], strongWeights[act-1], strongCount[act-1]);
    populateMonsterList(strongEnemies[act-1], strongWeights[act-1], strongCount[act-1], 12);
}



int rollElite(Random &monsterRng) {
    float roll = monsterRng.random();

    float currentWeight = 0.0f;
    currentWeight += 1.0f/3;
    if (roll < 1.0f/3) {
        return 0;
    }

    if (roll < 2.0f/3) {
        return 1;
    } else {
        return 2;
    }
}

void GameState::generateElites() {
    static const MonsterEncounter elites[3][3] = {
            { ME::GREMLIN_NOB, ME::LAGAVULIN, ME::THREE_SENTRIES },
            { ME::GREMLIN_LEADER, ME::SLAVERS, ME::BOOK_OF_STABBING },
            { ME::GIANT_HEAD, ME::NEMESIS, ME::REPTOMANCER },
    };

    for(int i = 0; i < 10; ++i) {
        if (eliteMonsterListSize == 0) {
            eliteMonsterList[eliteMonsterListSize++] = elites[act-1][rollElite(monsterRng)];
        } else {
            auto toAdd = elites[act-1][rollElite(monsterRng)];
            if (toAdd != eliteMonsterList[eliteMonsterListSize-1]) {
                eliteMonsterList[eliteMonsterListSize++] = toAdd;
            } else {
                --i;
            }
        }
    }
}


MonsterEncounter sts::getBoss(Random &monsterRng, int act) {
    static const MonsterEncounter bosses[3][3] = {
            { ME::THE_GUARDIAN, ME::HEXAGHOST, ME::SLIME_BOSS },
            { ME::AUTOMATON, ME::COLLECTOR, ME::CHAMP },
            { ME::AWAKENED_ONE, ME::TIME_EATER, ME::DONU_AND_DECA },
    };

    int indices[3] = {0,1,2};

    java::Collections::shuffle(indices, indices+3, java::Random(monsterRng.randomLong()));
    return bosses[act-1][indices[0]];
}



















