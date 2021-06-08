
#ifndef STS_SEED_SEARCH_STS_IMPL_H
#define STS_SEED_SEARCH_STS_IMPL_H

#include <cstdint>

namespace sts {

class Random {
private:
    static constexpr double NORM_DOUBLE = 1.1102230246251565E-16;
    static constexpr double NORM_FLOAT = 5.9604644775390625E-8;
    static constexpr std::uint64_t ONE_IN_MOST_SIGNIFICANT = static_cast<std::uint64_t>(1) << 63;


    std::int32_t counter;
    std::uint64_t seed0;
    std::uint64_t seed1;

    static constexpr std::uint64_t murmurHash3(std::uint64_t x) {
        x ^= x >> 33;
        x *= static_cast<std::int64_t>(-49064778989728563L);
        x ^= x >> 33;
        x *= static_cast<std::int64_t>(-4265267296055464877L);
        x ^= x >> 33;
        return x;
    }

    std::int64_t nextLong() {
        std::uint64_t s1 = seed0;
        std::uint64_t s0 = seed1;
        seed0 = s0;
        s1 ^= s1 << 23;

        seed1 = s1 ^ s0 ^ s1 >> static_cast<std::uint64_t>(17) ^ s0 >> static_cast<std::uint64_t>(26);
        return static_cast<std::int64_t>(seed1 + s0);
    }

    // n must be greater than 0
    std::int64_t nextLong(std::uint64_t n) {
        std::uint64_t bits;
        std::uint64_t value;
        do {
            bits = static_cast<std::uint64_t>(nextLong()) >> 1;
            value = bits % n;
        } while (bits - value + (n - static_cast<std::uint64_t>(1)) < static_cast<std::uint64_t>(0));
        return static_cast<std::int64_t>(value);
    }

    std::int32_t nextInt() {
        return static_cast<std::int32_t>(nextLong());
    }

    std::int32_t nextInt(std::int32_t n) {
        return static_cast<std::int32_t>(nextLong(static_cast<std::uint64_t>(n)));
    }

    double nextDouble() {
        std::uint64_t x = static_cast<std::uint64_t>(nextLong()) >> 11;
        return static_cast<double>(x) * NORM_DOUBLE;
    }

    float nextFloat() {
        std::uint64_t x = static_cast<std::uint64_t>(nextLong()) >> 40;
        double d = static_cast<double>(x) * NORM_FLOAT;
        return static_cast<float>(d);
    }

    bool nextBoolean() {
        return (nextLong() & static_cast<std::int64_t>(1)) != static_cast<std::int64_t>(0);
    }


public:

    Random(std::uint64_t seed) {
        counter = 0;
        seed0 = murmurHash3(seed == 0 ? ONE_IN_MOST_SIGNIFICANT : seed);
        seed1 = murmurHash3(seed0);
    }

    Random(std::uint64_t seed, std::int32_t targetCounter) : Random(seed) {
        for (int i = 0; i < targetCounter; i++) {
            random(999);
        }
    }

    std::int32_t random(std::int32_t range) {
        ++counter;
        return nextInt(range + 1);
    }

    std::int32_t random(std::int32_t start, std::int32_t end) {
        ++counter;
        return start + nextInt(end - start + 1);
    }

    std::int64_t random(std::int64_t range) {
        ++counter;
        double d = nextDouble() * static_cast<double>(range);
        return static_cast<std::int64_t>(d);
    }

    std::int64_t random(std::int64_t start, std::int64_t end) {
        ++counter;
        double d = nextDouble() * static_cast<double>(end - start);
        return start + static_cast<int64_t>(d);
    }

    float random() {
        ++counter;
        return nextFloat();
    }

    float random(float range) {
        ++counter;
        return nextFloat() * range;
    }

    float random(float start, float end) {
        ++counter;
        return start + nextFloat() * (end - start);
    }

    std::int64_t randomLong() {
        ++counter;
        return nextLong();
    }

    bool randomBoolean() {
        return nextBoolean();
    }

};

struct SeedHelper {
private:

    static constexpr int SEED_BASE = 35;

    static int getDigitValue(char c) {
        if (c < 'A') {
            return c - '0';
        }
        if (c < 'O') {
            return c - 'A' + 10;
        }
        return c - 'A' + 9;
    }

public:
    static std::string getString(std::int64_t seed) {
        constexpr auto chars = "0123456789ABCDEFGHIJKLMNPQRSTUVWXYZ";

        std::uint64_t uSeed = static_cast<std::uint64_t>(seed);
        std::string str;

        do {
            int rem = static_cast<int>(uSeed % SEED_BASE);
            uSeed /= SEED_BASE;
            str += chars[rem];
        } while (uSeed != 0);

        for (int i = 0; i < str.size() / 2; i++) {
            std::swap(str[i], str[str.size() - 1 - i]);
        }
        return str;
    }

    static std::int64_t getLong(const std::string &seed) {
        std::int64_t ret = 0;
        for (auto it = seed.begin(); it != seed.end(); ++it) {
            ret *= SEED_BASE;
            char c = *it;
            int value = getDigitValue(c);
            ret += value;
        }
        return ret;
    }


};

enum Relic {
        AKABEKO=0,
        ANCHOR,
        ANCIENT_TEA_SET,
        ART_OF_WAR,
        ASTROLABE,
        BAG_OF_MARBLES,
        BAG_OF_PREPARATION,
        BIRDFACED_URN,
        BLACK_BLOOD,
        BLACK_STAR,
        BLOODY_IDOL,
        BLOOD_VIAL,
        BLUE_CANDLE,
        BOTTLED_FLAME,
        BOTTLED_LIGHTNING,
        BOTTLED_TORNADO,
        BRIMSTONE,
        BRONZE_SCALES,
        BURNING_BLOOD,
        BUSTED_CROWN,
        CALIPERS,
        CALLING_BELL,
        CAPTAINS_WHEEL,
        CAULDRON,
        CENTENNIAL_PUZZLE,
        CERAMIC_FISH,
        CHAMPION_BELT,
        CHARONS_ASHES,
        CHEMICAL_X,
        CLOAK_CLASP,
        CLOCKWORK_SOUVENIR,
        COFFEE_DRIPPER,
        CRACKED_CORE,
        CULTIST_HEADPIECE,
        CURSED_KEY,
        DAMARU,
        DARKSTONE_PERIAPT,
        DATA_DISK,
        DEAD_BRANCH,
        DOLLYS_MIRROR,
        DREAM_CATCHER,
        DUALITY,
        DUVU_DOLL,
        ECTOPLASM,
        EMOTION_CHIP,
        EMPTY_CAGE,
        ENCHIRIDION,
        ETERNAL_FEATHER,
        FACE_OF_CLERIC,
        FOSSILIZED_HELIX,
        FROZEN_CORE,
        FROZEN_EGG,
        FROZEN_EYE,
        FUSION_HAMMER,
        GAMBLING_CHIP,
        GINGER,
        GIRYA,
        GOLDEN_EYE,
        GOLDEN_IDOL,
        GOLDPLATED_CABLES,
        GREMLIN_HORN,
        GREMLIN_VISAGE,
        HAND_DRILL,
        HAPPY_FLOWER,
        HOLY_WATER,
        HORN_CLEAT,
        HOVERING_KITE,
        ICE_CREAM,
        INCENSE_BURNER,
        INK_BOTTLE,
        INSERTER,
        JUZU_BRACELET,
        KUNAI,
        LANTERN,
        LEES_WAFFLE,
        LETTER_OPENER,
        LIZARD_TAIL,
        MAGIC_FLOWER,
        MANGO,
        MARK_OF_PAIN,
        MARK_OF_THE_BLOOM,
        MATRYOSHKA,
        MAW_BANK,
        MEAL_TICKET,
        MEAT_ON_THE_BONE,
        MEDICAL_KIT,
        MELANGE,
        MEMBERSHIP_CARD,
        MERCURY_HOURGLASS,
        MOLTEN_EGG,
        MUMMIFIED_HAND,
        MUTAGENIC_STRENGTH,
        NECRONOMICON,
        NEOWS_LAMENT,
        NILRYS_CODEX,
        NINJA_SCROLL,
        NLOTHS_GIFT,
        NLOTHS_HUNGRY_FACE,
        NUCLEAR_BATTERY,
        NUNCHAKU,
        ODDLY_SMOOTH_STONE,
        ODD_MUSHROOM,
        OLD_COIN,
        OMAMORI,
        ORANGE_PELLETS,
        ORICHALCUM,
        ORNAMENTAL_FAN,
        ORRERY,
        PANDORAS_BOX,
        PANTOGRAPH,
        PAPER_KRANE,
        PAPER_PHROG,
        PEACE_PIPE,
        PEAR,
        PEN_NIB,
        PHILOSOPHERS_STONE,
        POCKETWATCH,
        POTION_BELT,
        PRAYER_WHEEL,
        PRESERVED_INSECT,
        PRISMATIC_SHARD,
        PURE_WATER,
        QUESTION_CARD,
        RED_MASK,
        RED_SKULL,
        REGAL_PILLOW,
        RING_OF_THE_SERPENT,
        RING_OF_THE_SNAKE,
        RUNIC_CAPACITOR,
        RUNIC_CUBE,
        RUNIC_DOME,
        RUNIC_PYRAMID,
        SACRED_BARK,
        SELFFORMING_CLAY,
        SHOVEL,
        SHURIKEN,
        SINGING_BOWL,
        SLAVERS_COLLAR,
        SLING_OF_COURAGE,
        SMILING_MASK,
        SNECKO_EYE,
        SNECKO_SKULL,
        SOZU,
        SPIRIT_POOP,
        SSSERPENT_HEAD,
        STONE_CALENDAR,
        STRANGE_SPOON,
        STRAWBERRY,
        STRIKE_DUMMY,
        SUNDIAL,
        SYMBIOTIC_VIRUS,
        TEARDROP_LOCKET,
        THE_ABACUS,
        THE_BOOT,
        THE_COURIER,
        THE_SPECIMEN,
        THREAD_AND_NEEDLE,
        TINGSHA,
        TINY_CHEST,
        TINY_HOUSE,
        TOOLBOX,
        TORII,
        TOUGH_BANDAGES,
        TOXIC_EGG,
        TOY_ORNITHOPTER,
        TUNGSTEN_ROD,
        TURNIP,
        TWISTED_FUNNEL,
        UNCEASING_TOP,
        VAJRA,
        VELVET_CHOKER,
        VIOLET_LOTUS,
        WARPED_TONGS,
        WAR_PAINT,
        WHETSTONE,
        WHITE_BEAST_STATUE,
        WING_BOOTS,
        WRIST_BLADE,
    };

enum class Card {
    IMMOLATE,
    SPOT_WEAKNESS,
    ANGER,
    CLEAVE,
    WARCRY,
    INFLAME,
    OFFERING,
    EXHUME,
    POWER_THROUGH,
    DUAL_WIELD,
    FLEX,
    REAPER,
    INFERNAL_BLADE,
    BRUTALITY,
    IRON_WAVE,
    RECKLESS_CHARGE,
    HEMOKINESIS,
    INTIMIDATE,
    JUGGERNAUT,
    BODY_SLAM,
    TRUE_GRIT,
    BLOOD_FOR_BLOOD,
    IMPERVIOUS,
    SHRUG_IT_OFF,
    CLASH,
    THUNDERCLAP,
    FLAME_BARRIER,
    BERSERK,
    PUMMEL,
    BURNING_PACT,
    METALLICIZE,
    POMMEL_STRIKE,
    TWIN_STRIKE,
    BASH,
    CLOTHESLINE,
    SHOCKWAVE,
    RAMPAGE,
    SEVER_SOUL,
    WHIRLWIND,
    COMBUST,
    DARK_EMBRACE,
    SEEING_RED,
    DISARM,
    FIEND_FIRE,
    BARRICADE,
    ARMAMENTS,
    HAVOC,
    FEEL_NO_PAIN,
    CORRUPTION,
    RAGE,
    HEADBUTT,
    LIMIT_BREAK,
    ENTRENCH,
    DEFEND,
    SENTINEL,
    WILD_STRIKE,
    BATTLE_TRANCE,
    HEAVY_BLADE,
    SEARING_BLOW,
    SECOND_WIND,
    FEED,
    RUPTURE,
    BLUDGEON,
    BLOODLETTING,
    PERFECTED_STRIKE,
    CARNAGE,
    DROPKICK,
    SWORD_BOOMERANG,
    DEMON_FORM,
    FIRE_BREATHING,
    GHOSTLY_ARMOR,
    UPPERCUT,
    EVOLVE,
    DOUBLE_TAP,
    STRIKE,
};

enum class CharacterClass {
    IRONCLAD,
    SILENT,
    DEFECT,
    WATCHER
};


struct Ironclad {
    static constexpr std::array<Relic, 33> commonRelicPool = {WHETSTONE, THE_BOOT, BLOOD_VIAL, MEAL_TICKET, PEN_NIB, AKABEKO, LANTERN, REGAL_PILLOW, BAG_OF_PREPARATION, ANCIENT_TEA_SET, SMILING_MASK, POTION_BELT, PRESERVED_INSECT, OMAMORI, MAW_BANK, ART_OF_WAR, TOY_ORNITHOPTER, CERAMIC_FISH, VAJRA, CENTENNIAL_PUZZLE, STRAWBERRY, HAPPY_FLOWER, ODDLY_SMOOTH_STONE, WAR_PAINT, BRONZE_SCALES, JUZU_BRACELET, DREAM_CATCHER, NUNCHAKU, TINY_CHEST, ORICHALCUM, ANCHOR, BAG_OF_MARBLES, RED_SKULL};
    static constexpr std::array<Relic, 30> uncommonRelicPool = {BOTTLED_TORNADO, SUNDIAL, KUNAI, PEAR, BLUE_CANDLE, ETERNAL_FEATHER, STRIKE_DUMMY, SINGING_BOWL, MATRYOSHKA, INK_BOTTLE, THE_COURIER, FROZEN_EGG, ORNAMENTAL_FAN, BOTTLED_LIGHTNING, GREMLIN_HORN, HORN_CLEAT, TOXIC_EGG, LETTER_OPENER, QUESTION_CARD, BOTTLED_FLAME, SHURIKEN, MOLTEN_EGG, MEAT_ON_THE_BONE, DARKSTONE_PERIAPT, MUMMIFIED_HAND, PANTOGRAPH, WHITE_BEAST_STATUE, MERCURY_HOURGLASS, SELFFORMING_CLAY, PAPER_PHROG};
    static constexpr std::array<Relic, 28> rareRelicPool = {GINGER, OLD_COIN, BIRDFACED_URN, UNCEASING_TOP, TORII, STONE_CALENDAR, SHOVEL, WING_BOOTS, THREAD_AND_NEEDLE, TURNIP, ICE_CREAM, CALIPERS, LIZARD_TAIL, PRAYER_WHEEL, GIRYA, DEAD_BRANCH, DUVU_DOLL, POCKETWATCH, MANGO, INCENSE_BURNER, GAMBLING_CHIP, PEACE_PIPE, CAPTAINS_WHEEL, FOSSILIZED_HELIX, TUNGSTEN_ROD, MAGIC_FLOWER, CHARONS_ASHES, CHAMPION_BELT};
    static constexpr std::array<Relic, 22> bossRelicPool = {FUSION_HAMMER, VELVET_CHOKER, RUNIC_DOME, SLAVERS_COLLAR, SNECKO_EYE, PANDORAS_BOX, CURSED_KEY, BUSTED_CROWN, ECTOPLASM, TINY_HOUSE, SOZU, PHILOSOPHERS_STONE, ASTROLABE, BLACK_STAR, SACRED_BARK, EMPTY_CAGE, RUNIC_PYRAMID, CALLING_BELL, COFFEE_DRIPPER, BLACK_BLOOD, MARK_OF_PAIN, RUNIC_CUBE};
    static constexpr std::array<Relic, 17> shopRelicPool = {SLING_OF_COURAGE, HAND_DRILL, TOOLBOX, CHEMICAL_X, LEES_WAFFLE, ORRERY, DOLLYS_MIRROR, ORANGE_PELLETS, PRISMATIC_SHARD, CLOCKWORK_SOUVENIR, FROZEN_EYE, THE_ABACUS, MEDICAL_KIT, CAULDRON, STRANGE_SPOON, MEMBERSHIP_CARD, BRIMSTONE};

    static constexpr std::array<Card, 20> commonCardPool = {Card::ANGER, Card::CLEAVE, Card::WARCRY, Card::FLEX, Card::IRON_WAVE,Card::BODY_SLAM, Card::TRUE_GRIT, Card::SHRUG_IT_OFF, Card::CLASH, Card::THUNDERCLAP, Card::POMMEL_STRIKE, Card::TWIN_STRIKE, Card::CLOTHESLINE, Card::ARMAMENTS, Card::HAVOC, Card::HEADBUTT, Card::WILD_STRIKE, Card::HEAVY_BLADE, Card::PERFECTED_STRIKE, Card::SWORD_BOOMERANG };
    static constexpr std::array<Card, 36> uncommonCardPool = {Card::SPOT_WEAKNESS, Card::INFLAME, Card::POWER_THROUGH, Card::DUAL_WIELD, Card::INFERNAL_BLADE, Card::RECKLESS_CHARGE, Card::HEMOKINESIS, Card::INTIMIDATE, Card::BLOOD_FOR_BLOOD, Card::FLAME_BARRIER, Card::PUMMEL, Card::BURNING_PACT, Card::METALLICIZE, Card::SHOCKWAVE, Card::RAMPAGE, Card::SEVER_SOUL, Card::WHIRLWIND, Card::COMBUST, Card::DARK_EMBRACE, Card::SEEING_RED, Card::DISARM, Card::FEEL_NO_PAIN, Card::RAGE, Card::ENTRENCH, Card::SENTINEL, Card::BATTLE_TRANCE, Card::SEARING_BLOW, Card::SECOND_WIND, Card::RUPTURE, Card::BLOODLETTING, Card::CARNAGE, Card::DROPKICK, Card::FIRE_BREATHING, Card::GHOSTLY_ARMOR, Card::UPPERCUT, Card::EVOLVE};
    static constexpr std::array<Card, 16> rareCardPool = {Card::IMMOLATE, Card::OFFERING, Card::EXHUME, Card::REAPER, Card::BRUTALITY, Card::JUGGERNAUT, Card::IMPERVIOUS, Card::BERSERK, Card::FIEND_FIRE, Card::BARRICADE, Card::CORRUPTION, Card::LIMIT_BREAK, Card::FEED, Card::BLUDGEON, Card::DEMON_FORM, Card::DOUBLE_TAP};
    static constexpr std::array<Card, 72> cardPool = {
            Card::SWORD_BOOMERANG, Card::PERFECTED_STRIKE, Card::HEAVY_BLADE, Card::WILD_STRIKE, Card::HEADBUTT, Card::HAVOC, Card::ARMAMENTS, Card::CLOTHESLINE, Card::TWIN_STRIKE, Card::POMMEL_STRIKE, Card::THUNDERCLAP, Card::CLASH, Card::SHRUG_IT_OFF, Card::TRUE_GRIT,Card::BODY_SLAM, Card::IRON_WAVE, Card::FLEX, Card::WARCRY, Card::CLEAVE,Card::ANGER,
            Card::EVOLVE, Card::UPPERCUT, Card::GHOSTLY_ARMOR, Card::FIRE_BREATHING, Card::DROPKICK, Card::CARNAGE, Card::BLOODLETTING, Card::RUPTURE, Card::SECOND_WIND, Card::SEARING_BLOW, Card::BATTLE_TRANCE, Card::SENTINEL, Card::ENTRENCH, Card::RAGE, Card::FEEL_NO_PAIN, Card::DISARM, Card::SEEING_RED, Card::DARK_EMBRACE, Card::COMBUST, Card::WHIRLWIND, Card::SEVER_SOUL, Card::RAMPAGE, Card::SHOCKWAVE, Card::METALLICIZE, Card::BURNING_PACT, Card::PUMMEL, Card::FLAME_BARRIER, Card::BLOOD_FOR_BLOOD, Card::INTIMIDATE, Card::HEMOKINESIS, Card::RECKLESS_CHARGE, Card::INFERNAL_BLADE, Card::DUAL_WIELD, Card::POWER_THROUGH, Card::INFLAME,Card::SPOT_WEAKNESS,
            Card::DOUBLE_TAP, Card::DEMON_FORM, Card::BLUDGEON, Card::FEED, Card::LIMIT_BREAK, Card::CORRUPTION, Card::BARRICADE, Card::FIEND_FIRE, Card::BERSERK, Card::IMPERVIOUS, Card::JUGGERNAUT, Card::BRUTALITY, Card::REAPER, Card::EXHUME, Card::OFFERING,Card::IMMOLATE,
    };
};

struct Neow {

    enum class Reward {

        THREE_CARDS=0,
        ONE_RANDOM_RARE_CARD,
        REMOVE_CARD,
        UPGRADE_CARD,
        TRANSFORM_CARD,
        RANDOM_COLORLESS,

        THREE_SMALL_POTIONS,
        RANDOM_COMMON_RELIC,
        TEN_PERCENT_HP_BONUS,
        THREE_ENEMY_KILL,
        HUNDRED_GOLD,

        RANDOM_COLORLESS_2,
        REMOVE_TWO,
        ONE_RARE_RELIC,
        THREE_RARE_CARDS,
        TWO_FIFTY_GOLD,
        TRANSFORM_TWO_CARDS,
        TWENTY_PERCENT_HP_BONUS,

        BOSS_RELIC,
    };

    enum class Drawback {
        NONE=0,

        TEN_PERCENT_HP_LOSS,
        NO_GOLD,
        CURSE,
        PERCENT_DAMAGE,

        LOSE_STARTER_RELIC,
    };

    struct Option {
        Reward r;
        Drawback d;
    };

    static std::array<Option, 4> generateRewards(long seed) {
        Random r(seed);
        std::array<Option, 4> rewards;
        rewards[0].r = static_cast<Reward>(r.random(0, 5));
        rewards[0].d = Drawback::NONE;
        rewards[1].r = static_cast<Reward>(6 + r.random(0, 4));
        rewards[1].d = Drawback::NONE;

        rewards[2].d = static_cast<Drawback>(1 + r.random(0, 3));
        switch (rewards[2].d) {
            case Drawback::TEN_PERCENT_HP_LOSS: {
                static constexpr Reward myRewards[]{
                        Reward::RANDOM_COLORLESS_2,
                        Reward::REMOVE_TWO,
                        Reward::ONE_RARE_RELIC,
                        Reward::THREE_RARE_CARDS,
                        Reward::TWO_FIFTY_GOLD,
                        Reward::TRANSFORM_TWO_CARDS,
                };
                rewards[2].r = myRewards[r.random(0, 5)];
                break;
            }

            case Drawback::NO_GOLD: {
                static constexpr Reward myRewards[]{
                        Reward::RANDOM_COLORLESS_2,
                        Reward::REMOVE_TWO,
                        Reward::ONE_RARE_RELIC,
                        Reward::THREE_RARE_CARDS,
                        Reward::TRANSFORM_TWO_CARDS,
                        Reward::TWENTY_PERCENT_HP_BONUS,
                };
                rewards[2].r = myRewards[r.random(0, 5)];
                break;
            }

            case Drawback::CURSE: {
                static constexpr Reward myRewards[]{
                        Reward::RANDOM_COLORLESS_2,
                        Reward::ONE_RARE_RELIC,
                        Reward::THREE_RARE_CARDS,
                        Reward::TWO_FIFTY_GOLD,
                        Reward::TRANSFORM_TWO_CARDS,
                        Reward::TWENTY_PERCENT_HP_BONUS,
                };
                rewards[2].r = myRewards[r.random(0, 5)];
                break;
            }

            case Drawback::PERCENT_DAMAGE:
                rewards[2].r = static_cast<Reward>(11 + r.random(0, 7));
                break;

            default:    // should not happen
                break;

        }

        rewards[3].r = Reward::BOSS_RELIC;
        rewards[3].d = Drawback::LOSE_STARTER_RELIC;

        return rewards;
    }
};

typedef std::array<Neow::Option, 4> NeowBlessing;


}

#endif //STS_SEED_SEARCH_STS_IMPL_H
