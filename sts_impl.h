
#ifndef STS_SEED_SEARCH_STS_IMPL_H
#define STS_SEED_SEARCH_STS_IMPL_H

#include <cstdint>
#include <algorithm>
#include <string>
#include <array>
#include <vector>

#include "sts_constants.h"

namespace sts {

class Random {
public:
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
        } while (bits - value + (n - static_cast<std::uint64_t>(1)) < static_cast<std::int64_t>(0));
        return static_cast<std::int64_t>(value);
    }

    std::int32_t nextInt() {
        return static_cast<std::int32_t>(nextLong());
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

    std::int32_t nextInt(std::int32_t n) {
        return static_cast<std::int32_t>(nextLong(static_cast<std::uint64_t>(n)));
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

namespace Ironclad {
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

namespace Silent {
    static constexpr std::array<Relic, 22> bossRelicPool = {FUSION_HAMMER, VELVET_CHOKER, RUNIC_DOME, SLAVERS_COLLAR, SNECKO_EYE, PANDORAS_BOX, CURSED_KEY, BUSTED_CROWN, ECTOPLASM, TINY_HOUSE, SOZU, PHILOSOPHERS_STONE, ASTROLABE, BLACK_STAR, SACRED_BARK, EMPTY_CAGE, RUNIC_PYRAMID, CALLING_BELL, COFFEE_DRIPPER, WRIST_BLADE, HOVERING_KITE, RING_OF_THE_SERPENT};
    static constexpr std::array<Card, 71> cardPool = {Card::FLYING_KNEE, Card::DODGE_AND_ROLL, Card::SUCKER_PUNCH, Card::PIERCING_WAIL, Card::PREPARED, Card::OUTMANEUVER, Card::BACKFLIP, Card::SLICE, Card::QUICK_SLASH, Card::ACROBATICS, Card::POISONED_STAB, Card::DAGGER_THROW, Card::DEFLECT, Card::BLADE_DANCE, Card::BANE, Card::DAGGER_SPRAY, Card::DEADLY_POISON, Card::SNEAKY_STRIKE, Card::CLOAK_AND_DAGGER, Card::PREDATOR, Card::ALL_OUT_ATTACK, Card::DISTRACTION, Card::FOOTWORK, Card::ACCURACY, Card::MASTERFUL_STAB, Card::FLECHETTES, Card::CONCENTRATE, Card::BOUNCING_FLASK, Card::BACKSTAB, Card::DASH, Card::EVISCERATE, Card::REFLEX, Card::INFINITE_BLADES, Card::NOXIOUS_FUMES, Card::HEEL_HOOK, Card::TERROR, Card::WELL_LAID_PLANS, Card::FINISHER, Card::ESCAPE_PLAN, Card::CALCULATED_GAMBLE, Card::SKEWER, Card::RIDDLE_WITH_HOLES, Card::ENDLESS_AGONY, Card::SETUP, Card::BLUR, Card::CALTROPS, Card::CHOKE, Card::EXPERTISE, Card::TACTICIAN, Card::CATALYST, Card::LEG_SWEEP, Card::CRIPPLING_CLOUD, Card::ALCHEMIZE, Card::CORPSE_EXPLOSION, Card::MALAISE, Card::PHANTASMAL_KILLER, Card::DIE_DIE_DIE, Card::ADRENALINE, Card::ENVENOM, Card::DOPPELGANGER, Card::BURST, Card::WRAITH_FORM, Card::TOOLS_OF_THE_TRADE, Card::NIGHTMARE, Card::UNLOAD, Card::AFTER_IMAGE, Card::BULLET_TIME, Card::STORM_OF_STEEL, Card::GLASS_KNIFE, Card::A_THOUSAND_CUTS, Card::GRAND_FINALE};

};

namespace Defect {
    static constexpr std::array<Relic, 33> commonRelicPool = {WHETSTONE, THE_BOOT, BLOOD_VIAL, MEAL_TICKET, PEN_NIB, AKABEKO, LANTERN, REGAL_PILLOW, BAG_OF_PREPARATION, ANCIENT_TEA_SET, SMILING_MASK, POTION_BELT, PRESERVED_INSECT, OMAMORI, MAW_BANK, ART_OF_WAR, TOY_ORNITHOPTER, CERAMIC_FISH, VAJRA, CENTENNIAL_PUZZLE, STRAWBERRY, HAPPY_FLOWER, ODDLY_SMOOTH_STONE, WAR_PAINT, BRONZE_SCALES, JUZU_BRACELET, DREAM_CATCHER, NUNCHAKU, TINY_CHEST, ORICHALCUM, ANCHOR, BAG_OF_MARBLES, DATA_DISK};
    static constexpr std::array<Relic, 30> uncommonRelicPool = {BOTTLED_TORNADO, SUNDIAL, KUNAI, PEAR, BLUE_CANDLE, ETERNAL_FEATHER, STRIKE_DUMMY, SINGING_BOWL, MATRYOSHKA, INK_BOTTLE, THE_COURIER, FROZEN_EGG, ORNAMENTAL_FAN, BOTTLED_LIGHTNING, GREMLIN_HORN, HORN_CLEAT, TOXIC_EGG, LETTER_OPENER, QUESTION_CARD, BOTTLED_FLAME, SHURIKEN, MOLTEN_EGG, MEAT_ON_THE_BONE, DARKSTONE_PERIAPT, MUMMIFIED_HAND, PANTOGRAPH, WHITE_BEAST_STATUE, MERCURY_HOURGLASS, SYMBIOTIC_VIRUS, GOLDPLATED_CABLES};
    static constexpr std::array<Relic, 26> rareRelicPool = {GINGER, OLD_COIN, BIRDFACED_URN, UNCEASING_TOP, TORII, STONE_CALENDAR, SHOVEL, WING_BOOTS, THREAD_AND_NEEDLE, TURNIP, ICE_CREAM, CALIPERS, LIZARD_TAIL, PRAYER_WHEEL, GIRYA, DEAD_BRANCH, DUVU_DOLL, POCKETWATCH, MANGO, INCENSE_BURNER, GAMBLING_CHIP, PEACE_PIPE, CAPTAINS_WHEEL, FOSSILIZED_HELIX, EMOTION_CHIP};
    static constexpr std::array<Relic, 22> bossRelicPool = {FUSION_HAMMER, VELVET_CHOKER, RUNIC_DOME, SLAVERS_COLLAR, SNECKO_EYE, PANDORAS_BOX, CURSED_KEY, BUSTED_CROWN, ECTOPLASM, TINY_HOUSE, SOZU, PHILOSOPHERS_STONE, ASTROLABE, BLACK_STAR, SACRED_BARK, EMPTY_CAGE, RUNIC_PYRAMID, CALLING_BELL, COFFEE_DRIPPER, INSERTER, FROZEN_CORE, NUCLEAR_BATTERY};

    static constexpr std::array<Card, 71> cardPool = {Card::STEAM_BARRIER, Card::COLD_SNAP, Card::LEAP, Card::BEAM_CELL, Card::HOLOGRAM, Card::CHARGE_BATTERY, Card::SWEEPING_BEAM, Card::TURBO, Card::COOLHEADED, Card::CLAW, Card::REBOUND, Card::STACK, Card::BARRAGE, Card::COMPILE_DRIVER, Card::RECURSION, Card::STREAMLINE, Card::BALL_LIGHTNING, Card::GO_FOR_THE_EYES, Card::DOOM_AND_GLOOM, Card::DEFRAGMENT, Card::CAPACITOR, Card::WHITE_NOISE, Card::SKIM, Card::RECYCLE, Card::SCRAPE, Card::BULLSEYE, Card::REPROGRAM, Card::AUTO_SHIELDS, Card::REINFORCED_BODY, Card::DOUBLE_ENERGY, Card::DARKNESS, Card::RIP_AND_TEAR, Card::FTL, Card::FORCE_FIELD, Card::EQUILIBRIUM, Card::TEMPEST, Card::HEATSINKS, Card::STATIC_DISCHARGE, Card::BOOT_SEQUENCE, Card::CHILL, Card::LOOP, Card::SELF_REPAIR, Card::MELTER, Card::CHAOS, Card::BLIZZARD, Card::AGGREGATE, Card::FUSION, Card::CONSUME, Card::GLACIER, Card::SUNDER, Card::HELLO_WORLD, Card::OVERCLOCK, Card::GENETIC_ALGORITHM, Card::STORM, Card::MULTI_CAST, Card::HYPERBEAM, Card::THUNDER_STRIKE, Card::BIASED_COGNITION, Card::MACHINE_LEARNING, Card::ELECTRODYNAMICS, Card::BUFFER, Card::RAINBOW, Card::SEEK, Card::METEOR_STRIKE, Card::ECHO_FORM, Card::ALL_FOR_ONE, Card::REBOOT, Card::AMPLIFY, Card::CREATIVE_AI, Card::FISSION, Card::CORE_SURGE,};
};

namespace Watcher {
    static constexpr std::array<Relic, 21> bossRelicPool = {FUSION_HAMMER, VELVET_CHOKER, RUNIC_DOME, SLAVERS_COLLAR, SNECKO_EYE, PANDORAS_BOX, CURSED_KEY, BUSTED_CROWN, ECTOPLASM, TINY_HOUSE, SOZU, PHILOSOPHERS_STONE, ASTROLABE, BLACK_STAR, SACRED_BARK, EMPTY_CAGE, RUNIC_PYRAMID, CALLING_BELL, COFFEE_DRIPPER, HOLY_WATER, VIOLET_LOTUS};
    static constexpr std::array<Card, 71> cardPool = {Card::EMPTY_FIST, Card::PROSTRATE, Card::EVALUATE, Card::CRUSH_JOINTS, Card::PRESSURE_POINTS, Card::FOLLOW_UP, Card::CUT_THROUGH_FATE, Card::SASH_WHIP, Card::EMPTY_BODY, Card::TRANQUILITY, Card::CRESCENDO, Card::THIRD_EYE, Card::PROTECT, Card::FLURRY_OF_BLOWS, Card::JUST_LUCKY, Card::HALT, Card::FLYING_SLEEVES, Card::BOWLING_BASH, Card::CONSECRATE, Card::PRAY, Card::SIGNATURE_MOVE, Card::WEAVE, Card::EMPTY_MIND, Card::NIRVANA, Card::TANTRUM, Card::CONCLUDE, Card::WORSHIP, Card::SWIVEL, Card::PERSEVERANCE, Card::MEDITATE, Card::STUDY, Card::WAVE_OF_THE_HAND, Card::SANDS_OF_TIME, Card::FEAR_NO_EVIL, Card::REACH_HEAVEN, Card::MENTAL_FORTRESS, Card::DECEIVE_REALITY, Card::RUSHDOWN, Card::INNER_PEACE, Card::COLLECT, Card::WREATH_OF_FLAME, Card::WALLOP, Card::CARVE_REALITY, Card::FASTING, Card::LIKE_WATER, Card::FOREIGN_INFLUENCE, Card::WINDMILL_STRIKE, Card::INDIGNATION, Card::BATTLE_HYMN, Card::TALK_TO_THE_HAND, Card::SANCTITY, Card::FORESIGHT, Card::SIMMERING_FURY, Card::WHEEL_KICK, Card::JUDGMENT, Card::CONJURE_BLADE, Card::MASTER_REALITY, Card::BRILLIANCE, Card::DEVOTION, Card::BLASPHEMY, Card::RAGNAROK, Card::LESSON_LEARNED, Card::SCRAWL, Card::VAULT, Card::ALPHA, Card::WISH, Card::OMNISCIENCE, Card::ESTABLISHMENT, Card::SPIRIT_SHIELD, Card::DEVA_FORM, Card::DEUS_EX_MACHINA};
};

namespace Neow {
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

std::vector<std::int64_t> testPandoraSeedsForDefectWatcher(std::int64_t startSeed, std::int64_t endSeed, int threads);

}

#endif //STS_SEED_SEARCH_STS_IMPL_H
