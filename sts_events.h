//
// Created by keega on 6/13/2021.
//

#ifndef STS_SEED_SEARCH_STS_EVENTS_H
#define STS_SEED_SEARCH_STS_EVENTS_H

#include "sts_impl.h"
#include "sts_map.h"

#include "java_random.h"

namespace sts {





    constexpr float SHRINE_CHANCE = 0.25F;




    const std::array<Event,14> specialOneTimeEventsAsc0 { Event::ACCURSED_BLACKSMITH, Event::BONFIRE_ELEMENTALS, Event::DESIGNER, Event::DUPLICATOR, Event::FACE_TRADER, Event::FOUNTAIN_OF_CLEANSING, Event::KNOWING_SKULL, Event::LAB, Event::NLOTH, Event::NOTE_FOR_YOURSELF, Event::SECRET_PORTAL, Event::THE_JOUST, Event::WE_MEET_AGAIN, Event::THE_WOMAN_IN_BLUE };
    const std::array<Event,13> specialOneTimeEventsAsc15 { Event::ACCURSED_BLACKSMITH, Event::BONFIRE_ELEMENTALS, Event::DESIGNER, Event::DUPLICATOR, Event::FACE_TRADER, Event::FOUNTAIN_OF_CLEANSING, Event::KNOWING_SKULL, Event::LAB, Event::NLOTH, Event::SECRET_PORTAL, Event::THE_JOUST, Event::WE_MEET_AGAIN, Event::THE_WOMAN_IN_BLUE };

    namespace Act1 {
        const std::array<Event,11> eventList { Event::BIG_FISH, Event::THE_CLERIC, Event::DEAD_ADVENTURER, Event::GOLDEN_IDOL, Event::GOLDEN_WING, Event::WORLD_OF_GOOP, Event::LIARS_GAME, Event::LIVING_WALL, Event::MUSHROOMS, Event::SCRAP_OOZE, Event::SHINING_LIGHT };
        const std::array<Event,6> shrineList { Event::MATCH_AND_KEEP, Event::GOLDEN_SHRINE, Event::TRANSMORGRIFIER, Event::PURIFIER, Event::UPGRADE_SHRINE, Event::WHEEL_OF_CHANGE };
    }

    namespace Act2 {
        const std::array<Event,13> eventList { Event::ADDICT, Event::BACK_TO_BASICS, Event::BEGGAR, Event::COLOSSEUM, Event::CURSED_TOME, Event::DRUG_DEALER, Event::FORGOTTEN_ALTAR, Event::GHOSTS, Event::MASKED_BANDITS, Event::NEST, Event::THE_LIBRARY, Event::THE_MAUSOLEUM, Event::VAMPIRES };
        const std::array<Event,6> shrineList { Event::MATCH_AND_KEEP, Event::WHEEL_OF_CHANGE, Event::GOLDEN_SHRINE, Event::TRANSMORGRIFIER, Event::PURIFIER, Event::UPGRADE_SHRINE };
    }


    struct CardReward {
        int cardCount;
        std::array<Card,4> cards;
    };

    struct Rewards {
        int goldRewardCount = 0;
        int gold[2];

        int cardRewardCount = 0;
        CardReward cards[2];

        int relicCount = 0;
        Relic relics[2];

        int potionCount = 0;
        Potion potions[3];

        bool emeraldKey = false;
        bool sapphireKey = false;


        void addGold(int goldAmt) {
            gold[goldRewardCount++] = goldAmt;
        }

        void addRelic(Relic relic) {
            relics[relicCount++] = relic;
        }

        void addPotion(Potion potion) {
            potions[potionCount++] = potion;
        }

        std::string toString() const;

    };

    struct RelicShopItem {
        Relic relic;
        bool upgraded;
        int price;
    };

    struct CardShopItem {
        Card card;
        int price;

        CardShopItem() = default;
        CardShopItem(Card card) : card(card) {}
    };

    struct PotionShopItem {
        Potion potion;
        int price;
    };

    struct ShopScreen {
        std::array<RelicShopItem, 3> relics;
        std::array<CardShopItem, 7> cards;
        std::array<PotionShopItem, 3> potions;
        int cardRemovalCost;

        std::string toString(bool withPrices=false) const;
    };

    struct GameState {
        CharacterClass characterClass = CharacterClass::IRONCLAD;

        std::int64_t seed;
        std::vector<Event> eventList;
        std::vector<Event> shrineList;
        std::vector<Event> specialOneTimeEventList;

        std::vector<Relic> commonRelicPool;
        std::vector<Relic> uncommonRelicPool;
        std::vector<Relic> rareRelicPool;
        std::vector<Relic> shopRelicPool;
        std::vector<Relic> bossRelicPool;

        std::set<Relic> relics;

        Random treasureRng = Random(0);
        Random eventRng = Random(0);
        Random relicRng = Random(0);
        Random potionRng = Random(0);
        Random cardRng = Random(0);
        Random merchantRng = Random(0);
        Random monsterRng = Random(0);


        int monsterListOffset = 0;
        int monsterListSize = 0;
        std::array<MonsterEncounter, 15> monsterList;

        int eliteMonsterListSize = 0;
        std::array<MonsterEncounter, 3> eliteMonsterList;

        MonsterEncounter boss;

        int floor = 0;
        int curPlayerHealth = 80;
        int maxPlayerHealth = 80;
        int playerGold = 99;
        int curMapNodeY = 0;
        int act = 1;
        float playtime = 0;


        float monsterChance = 0.1f;
        float shopChance = 0.03f;
        float treasureChance = 0.02f;

        int potionChance = 0;
        int cardChanceAdjustment = 5;


        int tinyChestCounter = 0;

        bool skipReq_THE_MOAI_HEAD =        false;
        bool skipReq_THE_CLERIC =           false;
        bool skipReq_BEGGAR =               false;

        bool skipReq_FOUNTAIN_OF_CLEANSING =    false;
        bool skipReq_DESIGNER =                 false;
        bool skipReq_KNOWING_SKULL =            false;
        bool skipReq_NLOTH =                    false;
        bool skipReq_WOMAN_IN_BLUE =            false;
        bool skipReq_SECRET_PORTAL =            false;
        bool skipReq_THE_JOUST =                false;

    private:
        void shopInitCards(ShopScreen &shop);
        void shopInitRelics(ShopScreen &shop);
        void shopInitPotions(ShopScreen &shop);
        RelicTier rollRelicTierShop();


    public:
        static GameState createGameState(std::int64_t seed, int ascension) {
            GameState ret;
            ret.seed = seed;

            ret.eventRng = Random(seed);
            ret.treasureRng = Random(seed);
            ret.eventRng = Random(seed);
            ret.relicRng = Random(seed);
            ret.potionRng = Random(seed);
            ret.cardRng = Random(seed);
            ret.merchantRng = Random(seed);
            ret.monsterRng = Random(seed);

            ret.floor = 0;

            ret.commonRelicPool.insert(ret.commonRelicPool.end(), Ironclad::commonRelicPool.begin(), Ironclad::commonRelicPool.end());
            ret.uncommonRelicPool.insert(ret.uncommonRelicPool.end(), Ironclad::uncommonRelicPool.begin(), Ironclad::uncommonRelicPool.end());
            ret.rareRelicPool.insert(ret.rareRelicPool.end(), Ironclad::rareRelicPool.begin(), Ironclad::rareRelicPool.end());
            ret.shopRelicPool.insert(ret.shopRelicPool.end(), Ironclad::shopRelicPool.begin(), Ironclad::shopRelicPool.end());
            ret.bossRelicPool.insert(ret.bossRelicPool.end(), Ironclad::bossRelicPool.begin(), Ironclad::bossRelicPool.end());


            java::Collections::shuffle(ret.commonRelicPool.begin(), ret.commonRelicPool.end(), java::Random(ret.relicRng.nextLong()));
            java::Collections::shuffle(ret.uncommonRelicPool.begin(), ret.uncommonRelicPool.end(), java::Random(ret.relicRng.nextLong()));
            java::Collections::shuffle(ret.rareRelicPool.begin(), ret.rareRelicPool.end(), java::Random(ret.relicRng.nextLong()));
            java::Collections::shuffle(ret.shopRelicPool.begin(), ret.shopRelicPool.end(), java::Random(ret.relicRng.nextLong()));
            java::Collections::shuffle(ret.bossRelicPool.begin(), ret.bossRelicPool.end(), java::Random(ret.relicRng.nextLong()));



            ret.eventList.insert(ret.eventList.begin(), Act1::eventList.begin(), Act1::eventList.end());
            ret.shrineList.insert(ret.shrineList.begin(), Act1::shrineList.begin(), Act1::shrineList.end());
            if (ascension < 15) {
                ret.specialOneTimeEventList.insert(ret.specialOneTimeEventList.begin(), specialOneTimeEventsAsc0.begin(), specialOneTimeEventsAsc0.end());
            } else {
                ret.specialOneTimeEventList.insert(ret.specialOneTimeEventList.begin(), specialOneTimeEventsAsc15.begin(), specialOneTimeEventsAsc15.end());
            }

            return ret;
        }


        bool playerHasRelic(Relic relic) const {
            return relics.find(relic) != relics.end();
        }

        bool playerisCursed() const {return true;}

        int playerRelicsSize() const {return 1;}

        bool playerHasCardType(CardType type) const {return true;}

        bool canSpawnBottledLightning() const {
            // has skill that is not a basic
            return true;
        }

        bool hasLessThanTwoCampfireRelics() const {return true;}

        void resetEventHelperProbabilities() {
            monsterChance = 0.1f;
            shopChance = 0.03f;
            treasureChance = 0.02f;
        }


        ShopScreen getShopScreen();
        Rewards getCombatRewards(Room room, bool roomHasEmeraldKey=false);

        Event getEventRoomEvent();

        bool relicCanSpawn(Relic relic, Room room) const;
        Relic returnRandomRelic(RelicTier tier, Room room, bool front=true);
        Relic returnNonCampfireRelic(RelicTier tier, Room room);

        void addPotionToRewards(Rewards &rewards);
        CardReward getCardReward();

        CardRarity rollCardRarity();
        CardRarity rollCardRarityShop();


        void initEnemies();
        void generateWeakEnemies(int count);
        void generateStrongEnemies(int count);
        void generateElites();

        void populateMonsterList(const MonsterEncounter monsters[], const float weights[], int monstersSize, int numMonsters);
    };

    RelicTier rollRelicTier(Random &relicRng);

    Potion returnRandomPotion(Random &potionRng, CharacterClass c, bool limited=false);
    Potion returnRandomPotion(Random &potionRng, PotionRarity rarity, CharacterClass c, bool limited=false);

    Potion getRandomPotion(Random &potionRng, CharacterClass c=CharacterClass::IRONCLAD);
    Potion getPotionFromPool(int idx, CharacterClass characterClass);

    Card getRandomCard(Random &cardRng, CardType type, CardRarity rarity, CharacterClass c);

    Card getCard(Random &cardRng, CardRarity rarity, CharacterClass c);
    Card getAnyColorCard(Random &cardRng, CardRarity rarity);

    Card getColorlessCardFromPool(Random &cardRng, CardRarity rarity);

    MonsterEncounter getBoss(Random &monsterRng, int act);


}



#endif //STS_SEED_SEARCH_STS_EVENTS_H
