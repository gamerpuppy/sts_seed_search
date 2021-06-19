//
// Created by keega on 6/13/2021.
//

#ifndef STS_SEED_SEARCH_STS_EVENTS_H
#define STS_SEED_SEARCH_STS_EVENTS_H

#include "sts_impl.h"
#include "sts_map.h"

namespace sts {

    constexpr float SHRINE_CHANCE = 0.25F;


    enum class Event {
        INVALID=0,
        MONSTER,
        TREASURE,
        SHOP,
        ACCURSED_BLACKSMITH,
        ADDICT,
        BACK_TO_BASICS,
        BEGGAR,
        BIG_FISH,
        BONFIRE_ELEMENTALS,
        COLOSSEUM,
        CURSED_TOME,
        DEAD_ADVENTURER,
        DESIGNER,
        DRUG_DEALER,
        DUPLICATOR,
        FACE_TRADER,
        FALLING,
        FORGOTTEN_ALTAR,
        FOUNTAIN_OF_CLEANSING,
        GHOSTS,
        GOLDEN_IDOL,
        GOLDEN_SHRINE,
        GOLDEN_WING,
        KNOWING_SKULL,
        LAB,
        LIARS_GAME,
        LIVING_WALL,
        MASKED_BANDITS,
        MATCH_AND_KEEP,
        MINDBLOOM,
        MUSHROOMS,
        MYSTERIOUS_SPHERE,
        NEST,
        NLOTH,
        NOTE_FOR_YOURSELF,
        PURIFIER,
        SCRAP_OOZE,
        SECRET_PORTAL,
        SENSORY_STONE,
        SHINING_LIGHT,
        THE_CLERIC,
        THE_JOUST,
        THE_LIBRARY,
        THE_MAUSOLEUM,
        THE_MOAI_HEAD,
        THE_WOMAN_IN_BLUE,
        TOMB_OF_LORD_RED_MASK,
        TRANSMORGRIFIER,
        UPGRADE_SHRINE,
        VAMPIRES,
        WE_MEET_AGAIN,
        WHEEL_OF_CHANGE,
        WINDING_HALLS,
        WORLD_OF_GOOP,
    };

    static const char* eventStrings[] = {
            "INVALID",
            "MONSTER",
            "TREASURE",
            "SHOP",
            "Accursed Blacksmith",
            "Addict",
            "Back to Basics",
            "Beggar",
            "Big Fish",
            "Bonfire Elementals",
            "Colosseum",
            "Cursed Tome",
            "Dead Adventurer",
            "Designer",
            "Drug Dealer",
            "Duplicator",
            "Face Trader",
            "Falling",
            "Forgotten Altar",
            "Fountain of Cleansing",
            "Ghosts",
            "Golden Idol",
            "Golden Shrine",
            "Golden Wing",
            "Knowing Skull",
            "Lab",
            "Liars Game",
            "Living Wall",
            "Masked Bandits",
            "Match and Keep",
            "Mindbloom",
            "Mushrooms",
            "Mysterious Sphere",
            "Nest",
            "Nloth",
            "Note For Yourself",
            "Purifier",
            "Scrap Ooze",
            "Secret Portal",
            "Sensory Stone",
            "Shining Light",
            "The Cleric",
            "The Joust",
            "The Library",
            "The Mausoleum",
            "The Moai Head",
            "The Woman in Blue",
            "Tomb of Lord Red Mask",
            "Transmorgrifier",
            "Upgrade Shrine",
            "Vampires",
            "We Meet Again",
            "Wheel of Change",
            "Winding Halls",
            "World of Goop",
    };

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
        int choiceCount;
        Card cards[4];
    };

    struct Rewards {
        int goldCount = 0;
        int gold[2];

        int cardRewardCount = 0;
        CardReward cards[2];

        int relicCount = 0;
        Relic relics[2];

        int potionCount = 0;
        Potion potions[3];

        bool emeraldKey;
        bool sapphireKey;


        void addGold(int goldAmt) {
            gold[goldCount++] = goldAmt;
        }

        void addRelic(Relic relic) {
            relics[relicCount++] = relic;
        }

        void addPotion(Potion potion) {
            potions[potionCount++] = potion;
        }

    };

    struct RelicShopItem {
        Relic relic;
        bool upgraded;
        int cost;
    };

    struct CardShopItem {
        Card card;
        bool upgraded;
        int cost;
    };

    struct PotionShopItem {
        Potion potion;
        int cost;
    };

    struct ShopScreen {
        std::array<RelicShopItem,3> relics;
        std::array<CardShopItem, 7> cards;
        std::array<PotionShopItem, 3> potions;
        int cardRemovalCost;
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

        Room curRoom = Room::NONE;

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
        void initCards(ShopScreen &shop);



    public:
        static GameState createGameState(std::int64_t seed, int ascension) {
            GameState ret;
            ret.seed = seed;
            ret.eventRng = Random(seed);
            ret.floor = 0;

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

        Event getEventRoomEvent();
        Rewards getCombatRewards(GameState &s, Room room, bool roomHasEmeraldKey=false);

        bool relicCanSpawn(Relic relic) const;
        Relic returnRandomRelic(RelicTier tier, bool front=true);
        Relic returnNonCampfireRelic(RelicTier tier);

        void addPotionToRewards(Rewards &rewards);

        CardRarity rollCardRarity();
        std::array<Card,4> getRewardCards();
    };

    RelicTier rollRandomRelicTier(Random &relicRng);

    Potion returnRandomPotion(Random &potionRng, CharacterClass c, bool limited=false);
    Potion returnRandomPotion(Random &potionRng, PotionRarity rarity, CharacterClass c, bool limited=false);

    Potion getRandomPotion(Random &potionRng, CharacterClass c=CharacterClass::IRONCLAD);
    Potion getPotionFromPool(int idx, CharacterClass characterClass);

    Card getRandomCard(Random &cardRng, CardRarity rarity, CardType type, CharacterClass c);
    Card getCard(Random &cardRng, CardRarity rarity, CharacterClass c);
    Card getAnyColorCard(Random &cardRng, CardRarity rarity);

}



#endif //STS_SEED_SEARCH_STS_EVENTS_H
