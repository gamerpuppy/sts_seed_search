//
// Created by keega on 6/9/2021.
//

#ifndef STS_SEED_SEARCH_STS_CONSTANTS_H
#define STS_SEED_SEARCH_STS_CONSTANTS_H

namespace sts {

    enum class Event {
        INVALID = 0,
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

    static const char *eventStrings[] = {
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

    enum class Card {
        INVALID = 0,
        ACCURACY,
        ACROBATICS,
        ADRENALINE,
        AFTER_IMAGE,
        AGGREGATE,
        ALCHEMIZE,
        ALL_FOR_ONE,
        ALL_OUT_ATTACK,
        ALPHA,
        AMPLIFY,
        ANGER,
        APOTHEOSIS,
        APPARITION,
        ARMAMENTS,
        ASCENDERS_BANE,
        AUTO_SHIELDS,
        A_THOUSAND_CUTS,
        BACKFLIP,
        BACKSTAB,
        BALL_LIGHTNING,
        BANDAGE_UP,
        BANE,
        BARRAGE,
        BARRICADE,
        BASH,
        BATTLE_HYMN,
        BATTLE_TRANCE,
        BEAM_CELL,
        BECOME_ALMIGHTY,
        BERSERK,
        BETA,
        BIASED_COGNITION,
        BITE,
        BLADE_DANCE,
        BLASPHEMY,
        BLIND,
        BLIZZARD,
        BLOODLETTING,
        BLOOD_FOR_BLOOD,
        BLUDGEON,
        BLUR,
        BODY_SLAM,
        BOOT_SEQUENCE,
        BOUNCING_FLASK,
        BOWLING_BASH,
        BRILLIANCE,
        BRUTALITY,
        BUFFER,
        BULLET_TIME,
        BULLSEYE,
        BURN,
        BURNING_PACT,
        BURST,
        CALCULATED_GAMBLE,
        CALTROPS,
        CAPACITOR,
        CARNAGE,
        CARVE_REALITY,
        CATALYST,
        CHAOS,
        CHARGE_BATTERY,
        CHILL,
        CHOKE,
        CHRYSALIS,
        CLASH,
        CLAW,
        CLEAVE,
        CLOAK_AND_DAGGER,
        CLOTHESLINE,
        CLUMSY,
        COLD_SNAP,
        COLLECT,
        COMBUST,
        COMPILE_DRIVER,
        CONCENTRATE,
        CONCLUDE,
        CONJURE_BLADE,
        CONSECRATE,
        CONSUME,
        COOLHEADED,
        CORE_SURGE,
        CORPSE_EXPLOSION,
        CORRUPTION,
        CREATIVE_AI,
        CRESCENDO,
        CRIPPLING_CLOUD,
        CRUSH_JOINTS,
        CURSE_OF_THE_BELL,
        CUT_THROUGH_FATE,
        DAGGER_SPRAY,
        DAGGER_THROW,
        DARKNESS,
        DARK_EMBRACE,
        DARK_SHACKLES,
        DASH,
        DAZED,
        DEADLY_POISON,
        DECAY,
        DECEIVE_REALITY,
        DEEP_BREATH,
        DEFEND_BLUE,
        DEFEND_GREEN,
        DEFEND_PURPLE,
        DEFEND_RED,
        DEFLECT,
        DEFRAGMENT,
        DEMON_FORM,
        DEUS_EX_MACHINA,
        DEVA_FORM,
        DEVOTION,
        DIE_DIE_DIE,
        DISARM,
        DISCOVERY,
        DISTRACTION,
        DODGE_AND_ROLL,
        DOOM_AND_GLOOM,
        DOPPELGANGER,
        DOUBLE_ENERGY,
        DOUBLE_TAP,
        DOUBT,
        DRAMATIC_ENTRANCE,
        DROPKICK,
        DUALCAST,
        DUAL_WIELD,
        ECHO_FORM,
        ELECTRODYNAMICS,
        EMPTY_BODY,
        EMPTY_FIST,
        EMPTY_MIND,
        ENDLESS_AGONY,
        ENLIGHTENMENT,
        ENTRENCH,
        ENVENOM,
        EQUILIBRIUM,
        ERUPTION,
        ESCAPE_PLAN,
        ESTABLISHMENT,
        EVALUATE,
        EVISCERATE,
        EVOLVE,
        EXHUME,
        EXPERTISE,
        EXPUNGER,
        FAME_AND_FORTUNE,
        FASTING,
        FEAR_NO_EVIL,
        FEED,
        FEEL_NO_PAIN,
        FIEND_FIRE,
        FINESSE,
        FINISHER,
        FIRE_BREATHING,
        FISSION,
        FLAME_BARRIER,
        FLASH_OF_STEEL,
        FLECHETTES,
        FLEX,
        FLURRY_OF_BLOWS,
        FLYING_KNEE,
        FLYING_SLEEVES,
        FOLLOW_UP,
        FOOTWORK,
        FORCE_FIELD,
        FOREIGN_INFLUENCE,
        FORESIGHT,
        FORETHOUGHT,
        FTL,
        FUSION,
        GENETIC_ALGORITHM,
        GHOSTLY_ARMOR,
        GLACIER,
        GLASS_KNIFE,
        GOOD_INSTINCTS,
        GO_FOR_THE_EYES,
        GRAND_FINALE,
        HALT,
        HAND_OF_GREED,
        HAVOC,
        HEADBUTT,
        HEATSINKS,
        HEAVY_BLADE,
        HEEL_HOOK,
        HELLO_WORLD,
        HEMOKINESIS,
        HOLOGRAM,
        HYPERBEAM,
        IMMOLATE,
        IMPATIENCE,
        IMPERVIOUS,
        INDIGNATION,
        INFERNAL_BLADE,
        INFINITE_BLADES,
        INFLAME,
        INJURY,
        INNER_PEACE,
        INSIGHT,
        INTIMIDATE,
        IRON_WAVE,
        JAX,
        JACK_OF_ALL_TRADES,
        JUDGMENT,
        JUGGERNAUT,
        JUST_LUCKY,
        LEAP,
        LEG_SWEEP,
        LESSON_LEARNED,
        LIKE_WATER,
        LIMIT_BREAK,
        LIVE_FOREVER,
        LOOP,
        MACHINE_LEARNING,
        MADNESS,
        MAGNETISM,
        MALAISE,
        MASTERFUL_STAB,
        MASTER_OF_STRATEGY,
        MASTER_REALITY,
        MAYHEM,
        MEDITATE,
        MELTER,
        MENTAL_FORTRESS,
        METALLICIZE,
        METAMORPHOSIS,
        METEOR_STRIKE,
        MIND_BLAST,
        MIRACLE,
        MULTI_CAST,
        NECRONOMICURSE,
        NEUTRALIZE,
        NIGHTMARE,
        NIRVANA,
        NORMALITY,
        NOXIOUS_FUMES,
        OFFERING,
        OMEGA,
        OMNISCIENCE,
        OUTMANEUVER,
        OVERCLOCK,
        PAIN,
        PANACEA,
        PANACHE,
        PANIC_BUTTON,
        PARASITE,
        PERFECTED_STRIKE,
        PERSEVERANCE,
        PHANTASMAL_KILLER,
        PIERCING_WAIL,
        POISONED_STAB,
        POMMEL_STRIKE,
        POWER_THROUGH,
        PRAY,
        PREDATOR,
        PREPARED,
        PRESSURE_POINTS,
        PRIDE,
        PROSTRATE,
        PROTECT,
        PUMMEL,
        PURITY,
        QUICK_SLASH,
        RAGE,
        RAGNAROK,
        RAINBOW,
        RAMPAGE,
        REACH_HEAVEN,
        REAPER,
        REBOOT,
        REBOUND,
        RECKLESS_CHARGE,
        RECURSION,
        RECYCLE,
        REFLEX,
        REGRET,
        REINFORCED_BODY,
        REPROGRAM,
        RIDDLE_WITH_HOLES,
        RIP_AND_TEAR,
        RITUAL_DAGGER,
        RUPTURE,
        RUSHDOWN,
        SADISTIC_NATURE,
        SAFETY,
        SANCTITY,
        SANDS_OF_TIME,
        SASH_WHIP,
        SCRAPE,
        SCRAWL,
        SEARING_BLOW,
        SECOND_WIND,
        SECRET_TECHNIQUE,
        SECRET_WEAPON,
        SEEING_RED,
        SEEK,
        SELF_REPAIR,
        SENTINEL,
        SETUP,
        SEVER_SOUL,
        SHAME,
        SHIV,
        SHOCKWAVE,
        SHRUG_IT_OFF,
        SIGNATURE_MOVE,
        SIMMERING_FURY,
        SKEWER,
        SKIM,
        SLICE,
        SLIMED,
        SMITE,
        SNEAKY_STRIKE,
        SPIRIT_SHIELD,
        SPOT_WEAKNESS,
        STACK,
        STATIC_DISCHARGE,
        STEAM_BARRIER,
        STORM,
        STORM_OF_STEEL,
        STREAMLINE,
        STRIKE_BLUE,
        STRIKE_GREEN,
        STRIKE_PURPLE,
        STRIKE_RED,
        STUDY,
        SUCKER_PUNCH,
        SUNDER,
        SURVIVOR,
        SWEEPING_BEAM,
        SWIFT_STRIKE,
        SWIVEL,
        SWORD_BOOMERANG,
        TACTICIAN,
        TALK_TO_THE_HAND,
        TANTRUM,
        TEMPEST,
        TERROR,
        THE_BOMB,
        THINKING_AHEAD,
        THIRD_EYE,
        THROUGH_VIOLENCE,
        THUNDERCLAP,
        THUNDER_STRIKE,
        TOOLS_OF_THE_TRADE,
        TRANQUILITY,
        TRANSMUTATION,
        TRIP,
        TRUE_GRIT,
        TURBO,
        TWIN_STRIKE,
        UNLOAD,
        UPPERCUT,
        VAULT,
        VIGILANCE,
        VIOLENCE,
        VOID,
        WALLOP,
        WARCRY,
        WAVE_OF_THE_HAND,
        WEAVE,
        WELL_LAID_PLANS,
        WHEEL_KICK,
        WHIRLWIND,
        WHITE_NOISE,
        WILD_STRIKE,
        WINDMILL_STRIKE,
        WISH,
        WORSHIP,
        WOUND,
        WRAITH_FORM,
        WREATH_OF_FLAME,
        WRITHE,
        ZAP,
    };

    enum class CardRarity {
        COMMON = 0,
        UNCOMMON,
        RARE,
        BASIC,
        SPECIAL,
        CURSE,
        INVALID,
    };

    enum class CardColor {
        RED = 0,
        GREEN,
        BLUE,
        PURPLE,
        COLORLESS,
        CURSE,
        INVALID,
    };

    enum Relic {
        INVALID = 0,
        AKABEKO,
        ANCHOR,
        ANCIENT_TEA_SET,
        ART_OF_WAR,
        ASTROLABE,
        BAG_OF_MARBLES,
        BAG_OF_PREPARATION,
        BIRD_FACED_URN,
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
        DU_VU_DOLL,
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
        GOLD_PLATED_CABLES,
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
        NLOTHS_GIFT,
        NLOTHS_HUNGRY_FACE,
        NECRONOMICON,
        NEOWS_LAMENT,
        NILRYS_CODEX,
        NINJA_SCROLL,
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
        SELF_FORMING_CLAY,
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

        CIRCLET,
        RED_CIRCLET, // todo fix
    };

    enum class PotionRarity {
        COMMON,
        UNCOMMON,
        RARE,
        PLACEHOLDER,
    };


    enum class Potion {
        INVALID = 0,
        AMBROSIA,
        ANCIENT_POTION,

        ATTACK_POTION,
        BLESSING_OF_THE_FORGE,
        BLOCK_POTION,
        BLOOD_POTION,

        BOTTLED_MIRACLE,
        COLORLESS_POTION,
        CULTIST_POTION,
        CUNNING_POTION,

        DEXTERITY_POTION,
        DISTILLED_CHAOS,
        DUPLICATION_POTION,
        ELIXIR_POTION,

        ENERGY_POTION,
        ENTROPIC_BREW,
        ESSENCE_OF_DARKNESS,
        ESSENCE_OF_STEEL,

        EXPLOSIVE_POTION,
        FAIRY_POTION,
        FEAR_POTION,
        FIRE_POTION,

        FLEX_POTION, // called SteroidPotion in game code
        FOCUS_POTION,
        FRUIT_JUICE,
        GAMBLERS_BREW,

        GHOST_IN_A_JAR,
        HEART_OF_IRON,
        LIQUID_BRONZE,
        LIQUID_MEMORIES,

        POISON_POTION,
        POTION_OF_CAPACITY,
        POWER_POTION,
        REGEN_POTION,

        SKILL_POTION,
        SMOKE_BOMB,
        SNECKO_OIL,
        SPEED_POTION,

        STANCE_POTION,
        STRENGTH_POTION,
        SWIFT_POTION,
        WEAK_POTION,
    };

    static constexpr const char* const potionNames[] {
        "Invalid",
        "Ambrosia",
        "Ancient Potion",
        "Attack Potion",
        "Blessing Of The Forge",
        "Block Potion",
        "Blood Potion",
        "Bottled Miracle",
        "Colorless Potion",
        "Cultist Potion",
        "Cunning Potion",
        "Dexterity Potion",
        "Distilled Chaos",
        "Duplication Potion",
        "Elixir Potion",
        "Energy Potion",
        "Entropic Brew",
        "Essence Of Darkness",
        "Essence Of Steel",
        "Explosive Potion",
        "Fairy Potion",
        "Fear Potion",
        "Fire Potion",
        "Flex Potion",
        "Focus Potion",
        "Fruit Juice",
        "Gamblers Brew",
        "Ghost In A Jar",
        "Heart Of Iron",
        "Liquid Bronze",
        "Liquid Memories",
        "Poison Potion",
        "Potion Of Capacity",
        "Power Potion",
        "Regen Potion",
        "Skill Potion",
        "Smoke Bomb",
        "Snecko Oil",
        "Speed Potion",
        "Stance Potion",
        "Strength Potion",
        "Swift Potion",
        "Weak Potion",
    };


    static const PotionRarity potionRarities[] = {
        PotionRarity::PLACEHOLDER,
        PotionRarity::RARE,     // Ambrosia
        PotionRarity::UNCOMMON, // Ancient Potion

        PotionRarity::COMMON,   // Attack Potion
        PotionRarity::COMMON,   // Blessing of the Forge
        PotionRarity::COMMON,   // Block Potion
        PotionRarity::COMMON,   // Blood Potion

        PotionRarity::COMMON,   // Bottled Miracle
        PotionRarity::COMMON,   // Colorless Potion
        PotionRarity::RARE,     // Cultist Potion
        PotionRarity::UNCOMMON, // Cunning Potion

        PotionRarity::COMMON,   // Dexterity Potion
        PotionRarity::UNCOMMON, // Distilled Chaos
        PotionRarity::UNCOMMON, // Duplication Potion
        PotionRarity::UNCOMMON, // Elixir Potion

        PotionRarity::COMMON,   // Energy Potion
        PotionRarity::RARE,     // Entropic Brew
        PotionRarity::RARE,     // Essence of Darkness
        PotionRarity::UNCOMMON, // Essence of Steel

        PotionRarity::COMMON,   // Explosive Potion
        PotionRarity::RARE,     // Fairy Potion
        PotionRarity::COMMON,   // Fear Potion
        PotionRarity::COMMON,   // Fire Potion

        PotionRarity::COMMON,   // Flex Potion
        PotionRarity::COMMON,   // Focus Potion
        PotionRarity::RARE,     // Fruit Juice
        PotionRarity::UNCOMMON, // Gamblers Brew

        PotionRarity::RARE,     // Ghost in a Jar
        PotionRarity::RARE,     // Heart of Iron
        PotionRarity::UNCOMMON, // Liquid Bronze
        PotionRarity::UNCOMMON, // Liquid Memories

        PotionRarity::COMMON,   // Poison Potion
        PotionRarity::UNCOMMON, // Potion of Capacity
        PotionRarity::COMMON,   // Power Potion
        PotionRarity::UNCOMMON, // Regen Potion

        PotionRarity::COMMON,   // Skill Potion
        PotionRarity::RARE,     // Smoke Bomb
        PotionRarity::RARE,     // Snecko Oil
        PotionRarity::COMMON,   // Speed Potion

        PotionRarity::UNCOMMON, // Stance Potion
        PotionRarity::COMMON,   // Strength Potion
        PotionRarity::COMMON,   // Swift Potion
        PotionRarity::COMMON,   // Weak Potion
    };

    enum class RelicTier {
        COMMON=0,
        UNCOMMON,
        RARE,
        BOSS,
        SHOP,
        STARTER,
        SPECIAL,
        INVALID,
    };

    static const char* relicTierStrings[] = {
            "DEPRECATED",
            "STARTER",
            "COMMON",
            "UNCOMMON",
            "RARE",
            "SPECIAL",
            "BOSS",
            "SHOP",
    };


    enum class MonsterEncounter {
        INVALID=0,
        // Act 1 Weak
        CULTIST,
        JAW_WORM,
        TWO_LOUSE,
        SMALL_SLIMES,
        BLUE_SLAVER,
        GREMLIN_GANG,
        LOOTER,
        LARGE_SLIME,
        LOTS_OF_SLIMES,
        EXORDIUM_THUGS,
        EXORDIUM_WILDLIFE,
        RED_SLAVER,
        THREE_LOUSE,
        TWO_FUNGI_BEASTS,
        GREMLIN_NOB,
        LAGAVULIN,
        THREE_SENTRIES,
        SLIME_BOSS,
        THE_GUARDIAN,
        HEXAGHOST,

        // Act 2
        SPHERIC_GUARDIAN,
        CHOSEN,
        SHELL_PARASITE,
        THREE_BYRDS,
        TWO_THIEVES,
        CHOSEN_AND_BYRDS,
        SENTRY_AND_SPHERE,
        SNAKE_PLANT,
        SNECKO,
        CENTURION_AND_HEALER,
        CULTIST_AND_CHOSEN,
        THREE_CULTIST,
        SHELLED_PARASITE_AND_FUNGI,
        GREMLIN_LEADER,
        SLAVERS,
        BOOK_OF_STABBING,
        AUTOMATON,
        COLLECTOR,
        CHAMP,

        // Act 3
        THREE_DARKLINGS,
        ORB_WALKER,
        THREE_SHAPES,
        SPIRE_GROWTH,
        TRANSIENT,
        FOUR_SHAPES,
        MAW,
        SPHERE_AND_TWO_SHAPES,
        JAW_WORM_HORDE,
        WRITHING_MASS,
        GIANT_HEAD,
        NEMESIS,
        REPTOMANCER,
        AWAKENED_ONE,
        TIME_EATER,
        DONU_AND_DECA,

        // Act 4
        SHIELD_AND_SPEAR,
        THE_HEART,
    };

    typedef MonsterEncounter ME;

    static constexpr const char * const monsterEncounterStrings[] = {
            "INVALID",
            "Cultist",
            "Jaw Worm",
            "Two Louse",
            "Small Slimes",
            "Blue Slaver",
            "Gremlin Gang",
            "Looter",
            "Large Slime",
            "Lots Of Slimes",
            "Exordium Thugs",
            "Exordium Wildlife",
            "Red Slaver",
            "Three Louse",
            "Two Fungi Beasts",
            "Gremlin Nob",
            "Lagavulin",
            "Three Sentries",
            "Slime Boss",
            "The Guardian",
            "Hexaghost",
            "Spheric Guardian",
            "Chosen",
            "Shell Parasite",
            "Three Byrds",
            "Two Thieves",
            "Chosen And Byrds",
            "Sentry And Sphere",
            "Snake Plant",
            "Snecko",
            "Centurion And Healer",
            "Cultist And Chosen",
            "Three Cultist",
            "Shelled Parasite And Fungi",
            "Gremlin Leader",
            "Slavers",
            "Book Of Stabbing",
            "Automaton",
            "Collector",
            "Champ",
            "Three Darklings",
            "Orb Walker",
            "Three Shapes",
            "Spire Growth",
            "Transient",
            "Four Shapes",
            "Maw",
            "Sphere And Two Shapes",
            "Jaw Worm Horde",
            "Writhing Mass",
            "Giant Head",
            "Nemesis",
            "Reptomancer",
            "Awakened One",
            "Time Eater",
            "Donu And Deca",
            "Shield And Spear",
            "The Heart",
    };

    enum class CharacterClass {
        IRONCLAD=0,
        SILENT,
        DEFECT,
        WATCHER,
        INVALID,
    };

    enum class CardType {
        ATTACK=0,
        SKILL,
        POWER,
        CURSE,
        STATUS,
        INVALID,
    };

    constexpr int SMALL_CHEST_CHANCE = 50;
    constexpr int MEDIUM_CHEST_CHANCE = 33;
    constexpr int LARGE_CHEST_CHANCE = 17;
    constexpr int COMMON_RELIC_CHANCE = 50;
    constexpr int UNCOMMON_RELIC_CHANCE = 33;
    constexpr int RARE_RELIC_CHANCE = 17;

    // common, uncommon, rare
    static constexpr const int potionRarityPrices[] = {50,75,100};

    // COMMON, UNCOMMON, RARE, BOSS, SHOP, STARTER, SPECIAL
    static constexpr const int  relicTierPrices[] = {150,250,300,999,150,300,400};

    static constexpr const char* const relicNames[] = { "INVALID", "Akabeko","Anchor","Ancient Tea Set","Art of War","Astrolabe","Bag of Marbles","Bag of Preparation","Bird-Faced Urn","Black Blood","Black Star","Bloody Idol","Blood Vial","Blue Candle","Bottled Flame","Bottled Lightning","Bottled Tornado","Brimstone","Bronze Scales","Burning Blood","Busted Crown","Calipers","Calling Bell","Captain's Wheel","Cauldron","Centennial Puzzle","Ceramic Fish","Champion Belt","Charon's Ashes","Chemical X","Cloak Clasp","Clockwork Souvenir","Coffee Dripper","Cracked Core","Cultist Headpiece","Cursed Key","Damaru","Darkstone Periapt","Data Disk","Dead Branch","Dolly's Mirror","Dream Catcher","Duality","Du-Vu Doll","Ectoplasm","Emotion Chip","Empty Cage","Enchiridion","Eternal Feather","Face Of Cleric","Fossilized Helix","Frozen Core","Frozen Egg","Frozen Eye","Fusion Hammer","Gambling Chip","Ginger","Girya","Golden Eye","Golden Idol","Gold-Plated Cables","Gremlin Horn","Gremlin Visage","Hand Drill","Happy Flower","Holy Water","Horn Cleat","Hovering Kite","Ice Cream","Incense Burner","Ink Bottle","Inserter","Juzu Bracelet","Kunai","Lantern","Lee's Waffle","Letter Opener","Lizard Tail","Magic Flower","Mango","Mark of Pain","Mark of the Bloom","Matryoshka","Maw Bank","Meal Ticket","Meat on the Bone","Medical Kit","Melange","Membership Card","Mercury Hourglass","Molten Egg","Mummified Hand","Mutagenic Strength","N'loth's Gift","N'loth's Hungry Face","Necronomicon","Neow's Lament","Nilry's Codex","Ninja Scroll","Nuclear Battery","Nunchaku","Oddly Smooth Stone","Odd Mushroom","Old Coin","Omamori","Orange Pellets","Orichalcum","Ornamental Fan","Orrery","Pandora's Box","Pantograph","Paper Krane","Paper Phrog","Peace Pipe","Pear","Pen Nib","Philosopher's Stone","Pocketwatch","Potion Belt","Prayer Wheel","Preserved Insect","Prismatic Shard","Pure Water","Question Card","Red Mask","Red Skull","Regal Pillow","Ring of the Serpent","Ring of the Snake","Runic Capacitor","Runic Cube","Runic Dome","Runic Pyramid","Sacred Bark","Self-Forming Clay","Shovel","Shuriken","Singing Bowl","Slaver's Collar","Sling of Courage","Smiling Mask","Snecko Eye","Snecko Skull","Sozu","Spirit Poop","Ssserpent Head","Stone Calendar","Strange Spoon","Strawberry","Strike Dummy","Sundial","Symbiotic Virus","Teardrop Locket","The Abacus","The Boot","The Courier","The Specimen","Thread and Needle","Tingsha","Tiny Chest","Tiny House","Toolbox","Torii","Tough Bandages","Toxic Egg","Toy Ornithopter","Tungsten Rod","Turnip","Twisted Funnel","Unceasing Top","Vajra","Velvet Choker","Violet Lotus","Warped Tongs","War Paint","Whetstone","White Beast Statue","Wing Boots","Wrist Blade", };
    static constexpr const char* const relicIds[] = { "INVALID", "Akabeko","Anchor","Ancient Tea Set","Art of War","Astrolabe","Bag of Marbles","Bag of Preparation","Bird Faced Urn","Black Blood","Black Star","Bloody Idol","Blood Vial","Blue Candle","Bottled Flame","Bottled Lightning","Bottled Tornado","Brimstone","Bronze Scales","Burning Blood","Busted Crown","Calipers","Calling Bell","CaptainsWheel","Cauldron","Centennial Puzzle","CeramicFish","Champion Belt","Charon's Ashes","Chemical X","CloakClasp","ClockworkSouvenir","Coffee Dripper","Cracked Core","CultistMask","Cursed Key","Damaru","Darkstone Periapt","DataDisk","Dead Branch","DollysMirror","Dream Catcher","Yang","Du-Vu Doll","Ectoplasm","Emotion Chip","Empty Cage","Enchiridion","Eternal Feather","FaceOfCleric","FossilizedHelix","FrozenCore","Frozen Egg 2","Frozen Eye","Fusion Hammer","Gambling Chip","Ginger","Girya","GoldenEye","Golden Idol","Cables","Gremlin Horn","GremlinMask","HandDrill","Happy Flower","HolyWater","HornCleat","HoveringKite","Ice Cream","Incense Burner","InkBottle","Inserter","Juzu Bracelet","Kunai","Lantern","Lee's Waffle","Letter Opener","Lizard Tail","Magic Flower","Mango","Mark of Pain","Mark of the Bloom","Matryoshka","MawBank","MealTicket","Meat on the Bone","Medical Kit","Melange","Membership Card","Mercury Hourglass","Molten Egg 2","Mummified Hand","MutagenicStrength","Nloth's Gift","NlothsMask","Necronomicon","NeowsBlessing","Nilry's Codex","Ninja Scroll","Nuclear Battery","Nunchaku","Oddly Smooth Stone","Odd Mushroom","Old Coin","Omamori","OrangePellets","Orichalcum","Ornamental Fan","Orrery","Pandora's Box","Pantograph","Paper Crane","Paper Frog","Peace Pipe","Pear","Pen Nib","Philosopher's Stone","Pocketwatch","Potion Belt","Prayer Wheel","PreservedInsect","PrismaticShard","PureWater","Question Card","Red Mask","Red Skull","Regal Pillow","Ring of the Serpent","Ring of the Snake","Runic Capacitor","Runic Cube","Runic Dome","Runic Pyramid","SacredBark","Self Forming Clay","Shovel","Shuriken","Singing Bowl","SlaversCollar","Sling","Smiling Mask","Snecko Eye","Snake Skull","Sozu","Spirit Poop","SsserpentHead","StoneCalendar","Strange Spoon","Strawberry","StrikeDummy","Sundial","Symbiotic Virus","TeardropLocket","TheAbacus","Boot","The Courier","The Specimen","Thread and Needle","Tingsha","Tiny Chest","Tiny House","Toolbox","Torii","Tough Bandages","Toxic Egg 2","Toy Ornithopter","TungstenRod","Turnip","TwistedFunnel","Unceasing Top","Vajra","Velvet Choker","VioletLotus","WarpedTongs","War Paint","Whetstone","White Beast Statue","WingedGreaves","WristBlade", };
    static constexpr const RelicTier relicTiers[] = { RelicTier::INVALID, RelicTier::COMMON,RelicTier::COMMON,RelicTier::COMMON,RelicTier::COMMON,RelicTier::BOSS,RelicTier::COMMON,RelicTier::COMMON,RelicTier::RARE,RelicTier::BOSS,RelicTier::BOSS,RelicTier::SPECIAL,RelicTier::COMMON,RelicTier::UNCOMMON,RelicTier::UNCOMMON,RelicTier::UNCOMMON,RelicTier::UNCOMMON,RelicTier::SHOP,RelicTier::COMMON,RelicTier::STARTER,RelicTier::BOSS,RelicTier::RARE,RelicTier::BOSS,RelicTier::RARE,RelicTier::SHOP,RelicTier::COMMON,RelicTier::COMMON,RelicTier::RARE,RelicTier::RARE,RelicTier::SHOP,RelicTier::RARE,RelicTier::SHOP,RelicTier::BOSS,RelicTier::STARTER,RelicTier::SPECIAL,RelicTier::BOSS,RelicTier::COMMON,RelicTier::UNCOMMON,RelicTier::COMMON,RelicTier::RARE,RelicTier::SHOP,RelicTier::COMMON,RelicTier::UNCOMMON,RelicTier::RARE,RelicTier::BOSS,RelicTier::RARE,RelicTier::BOSS,RelicTier::SPECIAL,RelicTier::UNCOMMON,RelicTier::SPECIAL,RelicTier::RARE,RelicTier::BOSS,RelicTier::UNCOMMON,RelicTier::SHOP,RelicTier::BOSS,RelicTier::RARE,RelicTier::RARE,RelicTier::RARE,RelicTier::RARE,RelicTier::SPECIAL,RelicTier::UNCOMMON,RelicTier::UNCOMMON,RelicTier::SPECIAL,RelicTier::SHOP,RelicTier::COMMON,RelicTier::BOSS,RelicTier::UNCOMMON,RelicTier::BOSS,RelicTier::RARE,RelicTier::RARE,RelicTier::UNCOMMON,RelicTier::BOSS,RelicTier::COMMON,RelicTier::UNCOMMON,RelicTier::COMMON,RelicTier::SHOP,RelicTier::UNCOMMON,RelicTier::RARE,RelicTier::RARE,RelicTier::RARE,RelicTier::BOSS,RelicTier::SPECIAL,RelicTier::UNCOMMON,RelicTier::COMMON,RelicTier::COMMON,RelicTier::UNCOMMON,RelicTier::SHOP,RelicTier::SHOP,RelicTier::SHOP,RelicTier::UNCOMMON,RelicTier::UNCOMMON,RelicTier::UNCOMMON,RelicTier::SPECIAL,RelicTier::SPECIAL,RelicTier::SPECIAL,RelicTier::SPECIAL,RelicTier::SPECIAL,RelicTier::SPECIAL,RelicTier::UNCOMMON,RelicTier::BOSS,RelicTier::COMMON,RelicTier::COMMON,RelicTier::SPECIAL,RelicTier::RARE,RelicTier::COMMON,RelicTier::SHOP,RelicTier::COMMON,RelicTier::UNCOMMON,RelicTier::SHOP,RelicTier::BOSS,RelicTier::UNCOMMON,RelicTier::UNCOMMON,RelicTier::UNCOMMON,RelicTier::RARE,RelicTier::UNCOMMON,RelicTier::COMMON,RelicTier::BOSS,RelicTier::RARE,RelicTier::COMMON,RelicTier::RARE,RelicTier::COMMON,RelicTier::SHOP,RelicTier::STARTER,RelicTier::UNCOMMON,RelicTier::SPECIAL,RelicTier::COMMON,RelicTier::COMMON,RelicTier::BOSS,RelicTier::STARTER,RelicTier::SHOP,RelicTier::BOSS,RelicTier::BOSS,RelicTier::BOSS,RelicTier::BOSS,RelicTier::UNCOMMON,RelicTier::RARE,RelicTier::UNCOMMON,RelicTier::UNCOMMON,RelicTier::BOSS,RelicTier::SHOP,RelicTier::COMMON,RelicTier::BOSS,RelicTier::COMMON,RelicTier::BOSS,RelicTier::SPECIAL,RelicTier::SPECIAL,RelicTier::RARE,RelicTier::SHOP,RelicTier::COMMON,RelicTier::UNCOMMON,RelicTier::UNCOMMON,RelicTier::UNCOMMON,RelicTier::UNCOMMON,RelicTier::SHOP,RelicTier::COMMON,RelicTier::UNCOMMON,RelicTier::RARE,RelicTier::RARE,RelicTier::RARE,RelicTier::COMMON,RelicTier::BOSS,RelicTier::SHOP,RelicTier::RARE,RelicTier::RARE,RelicTier::UNCOMMON,RelicTier::COMMON,RelicTier::RARE,RelicTier::RARE,RelicTier::SHOP,RelicTier::RARE,RelicTier::COMMON,RelicTier::BOSS,RelicTier::BOSS,RelicTier::SPECIAL,RelicTier::COMMON,RelicTier::COMMON,RelicTier::UNCOMMON,RelicTier::RARE,RelicTier::BOSS, };


    static constexpr const char* const cardEnumNames[]  = { "INVALID", "ACCURACY","ACROBATICS","ADRENALINE","AFTER_IMAGE","AGGREGATE","ALCHEMIZE","ALL_FOR_ONE","ALL_OUT_ATTACK","ALPHA","AMPLIFY","ANGER","APOTHEOSIS","APPARITION","ARMAMENTS","ASCENDER'S_BANE","AUTO_SHIELDS","A_THOUSAND_CUTS","BACKFLIP","BACKSTAB","BALL_LIGHTNING","BANDAGE_UP","BANE","BARRAGE","BARRICADE","BASH","BATTLE_HYMN","BATTLE_TRANCE","BEAM_CELL","BECOME_ALMIGHTY","BERSERK","BETA","BIASED_COGNITION","BITE","BLADE_DANCE","BLASPHEMY","BLIND","BLIZZARD","BLOODLETTING","BLOOD_FOR_BLOOD","BLUDGEON","BLUR","BODY_SLAM","BOOT_SEQUENCE","BOUNCING_FLASK","BOWLING_BASH","BRILLIANCE","BRUTALITY","BUFFER","BULLET_TIME","BULLSEYE","BURN","BURNING_PACT","BURST","CALCULATED_GAMBLE","CALTROPS","CAPACITOR","CARNAGE","CARVE_REALITY","CATALYST","CHAOS","CHARGE_BATTERY","CHILL","CHOKE","CHRYSALIS","CLASH","CLAW","CLEAVE","CLOAK_AND_DAGGER","CLOTHESLINE","CLUMSY","COLD_SNAP","COLLECT","COMBUST","COMPILE_DRIVER","CONCENTRATE","CONCLUDE","CONJURE_BLADE","CONSECRATE","CONSUME","COOLHEADED","CORE_SURGE","CORPSE_EXPLOSION","CORRUPTION","CREATIVE_AI","CRESCENDO","CRIPPLING_CLOUD","CRUSH_JOINTS","CURSE_OF_THE_BELL","CUT_THROUGH_FATE","DAGGER_SPRAY","DAGGER_THROW","DARKNESS","DARK_EMBRACE","DARK_SHACKLES","DASH","DAZED","DEADLY_POISON","DECAY","DECEIVE_REALITY","DEEP_BREATH","DEFEND","DEFEND","DEFEND","DEFEND","DEFLECT","DEFRAGMENT","DEMON_FORM","DEUS_EX_MACHINA","DEVA_FORM","DEVOTION","DIE_DIE_DIE","DISARM","DISCOVERY","DISTRACTION","DODGE_AND_ROLL","DOOM_AND_GLOOM","DOPPELGANGER","DOUBLE_ENERGY","DOUBLE_TAP","DOUBT","DRAMATIC_ENTRANCE","DROPKICK","DUALCAST","DUAL_WIELD","ECHO_FORM","ELECTRODYNAMICS","EMPTY_BODY","EMPTY_FIST","EMPTY_MIND","ENDLESS_AGONY","ENLIGHTENMENT","ENTRENCH","ENVENOM","EQUILIBRIUM","ERUPTION","ESCAPE_PLAN","ESTABLISHMENT","EVALUATE","EVISCERATE","EVOLVE","EXHUME","EXPERTISE","EXPUNGER","FAME_AND_FORTUNE","FASTING","FEAR_NO_EVIL","FEED","FEEL_NO_PAIN","FIEND_FIRE","FINESSE","FINISHER","FIRE_BREATHING","FISSION","FLAME_BARRIER","FLASH_OF_STEEL","FLECHETTES","FLEX","FLURRY_OF_BLOWS","FLYING_KNEE","FLYING_SLEEVES","FOLLOW_UP","FOOTWORK","FORCE_FIELD","FOREIGN_INFLUENCE","FORESIGHT","FORETHOUGHT","FTL","FUSION","GENETIC_ALGORITHM","GHOSTLY_ARMOR","GLACIER","GLASS_KNIFE","GOOD_INSTINCTS","GO_FOR_THE_EYES","GRAND_FINALE","HALT","HAND_OF_GREED","HAVOC","HEADBUTT","HEATSINKS","HEAVY_BLADE","HEEL_HOOK","HELLO_WORLD","HEMOKINESIS","HOLOGRAM","HYPERBEAM","IMMOLATE","IMPATIENCE","IMPERVIOUS","INDIGNATION","INFERNAL_BLADE","INFINITE_BLADES","INFLAME","INJURY","INNER_PEACE","INSIGHT","INTIMIDATE","IRON_WAVE","J.A.X.","JACK_OF_ALL_TRADES","JUDGMENT","JUGGERNAUT","JUST_LUCKY","LEAP","LEG_SWEEP","LESSON_LEARNED","LIKE_WATER","LIMIT_BREAK","LIVE_FOREVER","LOOP","MACHINE_LEARNING","MADNESS","MAGNETISM","MALAISE","MASTERFUL_STAB","MASTER_OF_STRATEGY","MASTER_REALITY","MAYHEM","MEDITATE","MELTER","MENTAL_FORTRESS","METALLICIZE","METAMORPHOSIS","METEOR_STRIKE","MIND_BLAST","MIRACLE","MULTI_CAST","NECRONOMICURSE","NEUTRALIZE","NIGHTMARE","NIRVANA","NORMALITY","NOXIOUS_FUMES","OFFERING","OMEGA","OMNISCIENCE","OUTMANEUVER","OVERCLOCK","PAIN","PANACEA","PANACHE","PANIC_BUTTON","PARASITE","PERFECTED_STRIKE","PERSEVERANCE","PHANTASMAL_KILLER","PIERCING_WAIL","POISONED_STAB","POMMEL_STRIKE","POWER_THROUGH","PRAY","PREDATOR","PREPARED","PRESSURE_POINTS","PRIDE","PROSTRATE","PROTECT","PUMMEL","PURITY","QUICK_SLASH","RAGE","RAGNAROK","RAINBOW","RAMPAGE","REACH_HEAVEN","REAPER","REBOOT","REBOUND","RECKLESS_CHARGE","RECURSION","RECYCLE","REFLEX","REGRET","REINFORCED_BODY","REPROGRAM","RIDDLE_WITH_HOLES","RIP_AND_TEAR","RITUAL_DAGGER","RUPTURE","RUSHDOWN","SADISTIC_NATURE","SAFETY","SANCTITY","SANDS_OF_TIME","SASH_WHIP","SCRAPE","SCRAWL","SEARING_BLOW","SECOND_WIND","SECRET_TECHNIQUE","SECRET_WEAPON","SEEING_RED","SEEK","SELF_REPAIR","SENTINEL","SETUP","SEVER_SOUL","SHAME","SHIV","SHOCKWAVE","SHRUG_IT_OFF","SIGNATURE_MOVE","SIMMERING_FURY","SKEWER","SKIM","SLICE","SLIMED","SMITE","SNEAKY_STRIKE","SPIRIT_SHIELD","SPOT_WEAKNESS","STACK","STATIC_DISCHARGE","STEAM_BARRIER","STORM","STORM_OF_STEEL","STREAMLINE","STRIKE","STRIKE","STRIKE","STRIKE","STUDY","SUCKER_PUNCH","SUNDER","SURVIVOR","SWEEPING_BEAM","SWIFT_STRIKE","SWIVEL","SWORD_BOOMERANG","TACTICIAN","TALK_TO_THE_HAND","TANTRUM","TEMPEST","TERROR","THE_BOMB","THINKING_AHEAD","THIRD_EYE","THROUGH_VIOLENCE","THUNDERCLAP","THUNDER_STRIKE","TOOLS_OF_THE_TRADE","TRANQUILITY","TRANSMUTATION","TRIP","TRUE_GRIT","TURBO","TWIN_STRIKE","UNLOAD","UPPERCUT","VAULT","VIGILANCE","VIOLENCE","VOID","WALLOP","WARCRY","WAVE_OF_THE_HAND","WEAVE","WELL_LAID_PLANS","WHEEL_KICK","WHIRLWIND","WHITE_NOISE","WILD_STRIKE","WINDMILL_STRIKE","WISH","WORSHIP","WOUND","WRAITH_FORM","WREATH_OF_FLAME","WRITHE","ZAP", };
    static constexpr const char* const cardNames[] = { "INVALID", "Accuracy","Acrobatics","Adrenaline","After Image","Aggregate","Alchemize","All for One","All-Out Attack","Alpha","Amplify","Anger","Apotheosis","Apparition","Armaments","Ascender's Bane","Auto-Shields","A Thousand Cuts","Backflip","Backstab","Ball Lightning","Bandage Up","Bane","Barrage","Barricade","Bash","Battle Hymn","Battle Trance","Beam Cell","Become Almighty","Berserk","Beta","Biased Cognition","Bite","Blade Dance","Blasphemy","Blind","Blizzard","Bloodletting","Blood for Blood","Bludgeon","Blur","Body Slam","Boot Sequence","Bouncing Flask","Bowling Bash","Brilliance","Brutality","Buffer","Bullet Time","Bullseye","Burn","Burning Pact","Burst","Calculated Gamble","Caltrops","Capacitor","Carnage","Carve Reality","Catalyst","Chaos","Charge Battery","Chill","Choke","Chrysalis","Clash","Claw","Cleave","Cloak and Dagger","Clothesline","Clumsy","Cold Snap","Collect","Combust","Compile Driver","Concentrate","Conclude","Conjure Blade","Consecrate","Consume","Coolheaded","Core Surge","Corpse Explosion","Corruption","Creative AI","Crescendo","Crippling Cloud","Crush Joints","Curse of the Bell","Cut Through Fate","Dagger Spray","Dagger Throw","Darkness","Dark Embrace","Dark Shackles","Dash","Dazed","Deadly Poison","Decay","Deceive Reality","Deep Breath","Defend","Defend","Defend","Defend","Deflect","Defragment","Demon Form","Deus Ex Machina","Deva Form","Devotion","Die Die Die","Disarm","Discovery","Distraction","Dodge and Roll","Doom and Gloom","Doppelganger","Double Energy","Double Tap","Doubt","Dramatic Entrance","Dropkick","Dualcast","Dual Wield","Echo Form","Electrodynamics","Empty Body","Empty Fist","Empty Mind","Endless Agony","Enlightenment","Entrench","Envenom","Equilibrium","Eruption","Escape Plan","Establishment","Evaluate","Eviscerate","Evolve","Exhume","Expertise","Expunger","Fame and Fortune","Fasting","Fear No Evil","Feed","Feel No Pain","Fiend Fire","Finesse","Finisher","Fire Breathing","Fission","Flame Barrier","Flash of Steel","Flechettes","Flex","Flurry of Blows","Flying Knee","Flying Sleeves","Follow-Up","Footwork","Force Field","Foreign Influence","Foresight","Forethought","FTL","Fusion","Genetic Algorithm","Ghostly Armor","Glacier","Glass Knife","Good Instincts","Go for the Eyes","Grand Finale","Halt","Hand of Greed","Havoc","Headbutt","Heatsinks","Heavy Blade","Heel Hook","Hello World","Hemokinesis","Hologram","Hyperbeam","Immolate","Impatience","Impervious","Indignation","Infernal Blade","Infinite Blades","Inflame","Injury","Inner Peace","Insight","Intimidate","Iron Wave","J.A.X.","Jack of All Trades","Judgment","Juggernaut","Just Lucky","Leap","Leg Sweep","Lesson Learned","Like Water","Limit Break","Live Forever","Loop","Machine Learning","Madness","Magnetism","Malaise","Masterful Stab","Master of Strategy","Master Reality","Mayhem","Meditate","Melter","Mental Fortress","Metallicize","Metamorphosis","Meteor Strike","Mind Blast","Miracle","Multi-Cast","Necronomicurse","Neutralize","Nightmare","Nirvana","Normality","Noxious Fumes","Offering","Omega","Omniscience","Outmaneuver","Overclock","Pain","Panacea","Panache","Panic Button","Parasite","Perfected Strike","Perseverance","Phantasmal Killer","Piercing Wail","Poisoned Stab","Pommel Strike","Power Through","Pray","Predator","Prepared","Pressure Points","Pride","Prostrate","Protect","Pummel","Purity","Quick Slash","Rage","Ragnarok","Rainbow","Rampage","Reach Heaven","Reaper","Reboot","Rebound","Reckless Charge","Recursion","Recycle","Reflex","Regret","Reinforced Body","Reprogram","Riddle with Holes","Rip and Tear","Ritual Dagger","Rupture","Rushdown","Sadistic Nature","Safety","Sanctity","Sands of Time","Sash Whip","Scrape","Scrawl","Searing Blow","Second Wind","Secret Technique","Secret Weapon","Seeing Red","Seek","Self Repair","Sentinel","Setup","Sever Soul","Shame","Shiv","Shockwave","Shrug It Off","Signature Move","Simmering Fury","Skewer","Skim","Slice","Slimed","Smite","Sneaky Strike","Spirit Shield","Spot Weakness","Stack","Static Discharge","Steam Barrier","Storm","Storm of Steel","Streamline","Strike","Strike","Strike","Strike","Study","Sucker Punch","Sunder","Survivor","Sweeping Beam","Swift Strike","Swivel","Sword Boomerang","Tactician","Talk to the Hand","Tantrum","Tempest","Terror","The Bomb","Thinking Ahead","Third Eye","Through Violence","Thunderclap","Thunder Strike","Tools of the Trade","Tranquility","Transmutation","Trip","True Grit","TURBO","Twin Strike","Unload","Uppercut","Vault","Vigilance","Violence","Void","Wallop","Warcry","Wave of the Hand","Weave","Well-Laid Plans","Wheel Kick","Whirlwind","White Noise","Wild Strike","Windmill Strike","Wish","Worship","Wound","Wraith Form","Wreath of Flame","Writhe","Zap", };
    static constexpr const char* const cardIds[]  = { "INVALID", "Accuracy","Acrobatics","Adrenaline","After Image","Aggregate","Venomology","All For One","All Out Attack","Alpha","Amplify","Anger","Apotheosis","Ghostly","Armaments","AscendersBane","Auto Shields","A Thousand Cuts","Backflip","Backstab","Ball Lightning","Bandage Up","Bane","Barrage","Barricade","Bash","BattleHymn","Battle Trance","Beam Cell","BecomeAlmighty","Berserk","Beta","Biased Cognition","Bite","Blade Dance","Blasphemy","Blind","Blizzard","Bloodletting","Blood for Blood","Bludgeon","Blur","Body Slam","BootSequence","Bouncing Flask","BowlingBash","Brilliance","Brutality","Buffer","Bullet Time","Lockon","Burn","Burning Pact","Burst","Calculated Gamble","Caltrops","Capacitor","Carnage","CarveReality","Catalyst","Chaos","Conserve Battery","Chill","Choke","Chrysalis","Clash","Gash","Cleave","Cloak And Dagger","Clothesline","Clumsy","Cold Snap","Collect","Combust","Compile Driver","Concentrate","Conclude","ConjureBlade","Consecrate","Consume","Coolheaded","Core Surge","Corpse Explosion","Corruption","Creative AI","Crescendo","Crippling Poison","CrushJoints","CurseOfTheBell","CutThroughFate","Dagger Spray","Dagger Throw","Darkness","Dark Embrace","Dark Shackles","Dash","Dazed","Deadly Poison","Decay","DeceiveReality","Deep Breath","Defend_P","Defend_R","Defend_G","Defend_B","Deflect","Defragment","Demon Form","DeusExMachina","DevaForm","Devotion","Die Die Die","Disarm","Discovery","Distraction","Dodge and Roll","Doom and Gloom","Doppelganger","Double Energy","Double Tap","Doubt","Dramatic Entrance","Dropkick","Dualcast","Dual Wield","Echo Form","Electrodynamics","EmptyBody","EmptyFist","EmptyMind","Endless Agony","Enlightenment","Entrench","Envenom","Undo","Eruption","Escape Plan","Establishment","Evaluate","Eviscerate","Evolve","Exhume","Expertise","Expunger","FameAndFortune","Fasting2","FearNoEvil","Feed","Feel No Pain","Fiend Fire","Finesse","Finisher","Fire Breathing","Fission","Flame Barrier","Flash of Steel","Flechettes","Flex","FlurryOfBlows","Flying Knee","FlyingSleeves","FollowUp","Footwork","Force Field","ForeignInfluence","Wireheading","Forethought","FTL","Fusion","Genetic Algorithm","Ghostly Armor","Glacier","Glass Knife","Good Instincts","Go for the Eyes","Grand Finale","Halt","HandOfGreed","Havoc","Headbutt","Heatsinks","Heavy Blade","Heel Hook","Hello World","Hemokinesis","Hologram","Hyperbeam","Immolate","Impatience","Impervious","Indignation","Infernal Blade","Infinite Blades","Inflame","Injury","InnerPeace","Insight","Intimidate","Iron Wave","J.A.X.","Jack Of All Trades","Judgement","Juggernaut","JustLucky","Leap","Leg Sweep","LessonLearned","LikeWater","Limit Break","LiveForever","Loop","Machine Learning","Madness","Magnetism","Malaise","Masterful Stab","Master of Strategy","MasterReality","Mayhem","Meditate","Melter","MentalFortress","Metallicize","Metamorphosis","Meteor Strike","Mind Blast","Miracle","Multi-Cast","Necronomicurse","Neutralize","Night Terror","Nirvana","Normality","Noxious Fumes","Offering","Omega","Omniscience","Outmaneuver","Steam Power","Pain","Panacea","Panache","PanicButton","Parasite","Perfected Strike","Perseverance","Phantasmal Killer","PiercingWail","Poisoned Stab","Pommel Strike","Power Through","Pray","Predator","Prepared","PathToVictory","Pride","Prostrate","Protect","Pummel","Purity","Quick Slash","Rage","Ragnarok","Rainbow","Rampage","ReachHeaven","Reaper","Reboot","Rebound","Reckless Charge","Redo","Recycle","Reflex","Regret","Reinforced Body","Reprogram","Riddle With Holes","Rip and Tear","RitualDagger","Rupture","Adaptation","Sadistic Nature","Safety","Sanctity","SandsOfTime","SashWhip","Scrape","Scrawl","Searing Blow","Second Wind","Secret Technique","Secret Weapon","Seeing Red","Seek","Self Repair","Sentinel","Setup","Sever Soul","Shame","Shiv","Shockwave","Shrug It Off","SignatureMove","Vengeance","Skewer","Skim","Slice","Slimed","Smite","Underhanded Strike","SpiritShield","Spot Weakness","Stack","Static Discharge","Steam","Storm","Storm of Steel","Streamline","Strike_B","Strike_G","Strike_R","Strike_P","Study","Sucker Punch","Sunder","Survivor","Sweeping Beam","Swift Strike","Swivel","Sword Boomerang","Tactician","TalkToTheHand","Tantrum","Tempest","Terror","The Bomb","Thinking Ahead","ThirdEye","ThroughViolence","Thunderclap","Thunder Strike","Tools of the Trade","ClearTheMind","Transmutation","Trip","True Grit","Turbo","Twin Strike","Unload","Uppercut","Vault","Vigilance","Violence","Void","Wallop","Warcry","WaveOfTheHand","Weave","Well Laid Plans","WheelKick","Whirlwind","White Noise","Wild Strike","WindmillStrike","Wish","Worship","Wound","Wraith Form v2","WreathOfFlame","Writhe","Zap", };

    static constexpr const CardRarity cardRarities[] = { CardRarity::INVALID, CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::COMMON,CardRarity::RARE,CardRarity::SPECIAL,CardRarity::COMMON,CardRarity::SPECIAL,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::COMMON,CardRarity::RARE,CardRarity::BASIC,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::SPECIAL,CardRarity::RARE,CardRarity::SPECIAL,CardRarity::RARE,CardRarity::SPECIAL,CardRarity::COMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::RARE,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::COMMON,CardRarity::COMMON,CardRarity::COMMON,CardRarity::COMMON,CardRarity::COMMON,CardRarity::CURSE,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::RARE,CardRarity::RARE,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::SPECIAL,CardRarity::COMMON,CardRarity::COMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::COMMON,CardRarity::CURSE,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::BASIC,CardRarity::BASIC,CardRarity::BASIC,CardRarity::BASIC,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::RARE,CardRarity::RARE,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::CURSE,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::BASIC,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::COMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::BASIC,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::SPECIAL,CardRarity::SPECIAL,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::COMMON,CardRarity::COMMON,CardRarity::COMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::RARE,CardRarity::COMMON,CardRarity::RARE,CardRarity::COMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::CURSE,CardRarity::UNCOMMON,CardRarity::SPECIAL,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::SPECIAL,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::COMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::SPECIAL,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::SPECIAL,CardRarity::RARE,CardRarity::SPECIAL,CardRarity::BASIC,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::CURSE,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::SPECIAL,CardRarity::RARE,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::CURSE,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::CURSE,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::COMMON,CardRarity::COMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::COMMON,CardRarity::SPECIAL,CardRarity::COMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::CURSE,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::SPECIAL,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::SPECIAL,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::CURSE,CardRarity::SPECIAL,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::COMMON,CardRarity::SPECIAL,CardRarity::COMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::COMMON,CardRarity::BASIC,CardRarity::BASIC,CardRarity::BASIC,CardRarity::BASIC,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::BASIC,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::COMMON,CardRarity::SPECIAL,CardRarity::COMMON,CardRarity::RARE,CardRarity::RARE,CardRarity::COMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::COMMON,CardRarity::COMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::BASIC,CardRarity::RARE,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::UNCOMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::COMMON,CardRarity::RARE,CardRarity::UNCOMMON,CardRarity::CURSE,CardRarity::BASIC, };
    static constexpr const CardColor cardColors[] = { CardColor::INVALID, CardColor::GREEN,CardColor::GREEN,CardColor::GREEN,CardColor::GREEN,CardColor::BLUE,CardColor::GREEN,CardColor::BLUE,CardColor::GREEN,CardColor::PURPLE,CardColor::BLUE,CardColor::RED,CardColor::COLORLESS,CardColor::COLORLESS,CardColor::RED,CardColor::CURSE,CardColor::BLUE,CardColor::GREEN,CardColor::GREEN,CardColor::GREEN,CardColor::BLUE,CardColor::COLORLESS,CardColor::GREEN,CardColor::BLUE,CardColor::RED,CardColor::RED,CardColor::PURPLE,CardColor::RED,CardColor::BLUE,CardColor::COLORLESS,CardColor::RED,CardColor::COLORLESS,CardColor::BLUE,CardColor::COLORLESS,CardColor::GREEN,CardColor::PURPLE,CardColor::COLORLESS,CardColor::BLUE,CardColor::RED,CardColor::RED,CardColor::RED,CardColor::GREEN,CardColor::RED,CardColor::BLUE,CardColor::GREEN,CardColor::PURPLE,CardColor::PURPLE,CardColor::RED,CardColor::BLUE,CardColor::GREEN,CardColor::BLUE,CardColor::COLORLESS,CardColor::RED,CardColor::GREEN,CardColor::GREEN,CardColor::GREEN,CardColor::BLUE,CardColor::RED,CardColor::PURPLE,CardColor::GREEN,CardColor::BLUE,CardColor::BLUE,CardColor::BLUE,CardColor::GREEN,CardColor::COLORLESS,CardColor::RED,CardColor::BLUE,CardColor::RED,CardColor::GREEN,CardColor::RED,CardColor::CURSE,CardColor::BLUE,CardColor::PURPLE,CardColor::RED,CardColor::BLUE,CardColor::GREEN,CardColor::PURPLE,CardColor::PURPLE,CardColor::PURPLE,CardColor::BLUE,CardColor::BLUE,CardColor::BLUE,CardColor::GREEN,CardColor::RED,CardColor::BLUE,CardColor::PURPLE,CardColor::GREEN,CardColor::PURPLE,CardColor::CURSE,CardColor::PURPLE,CardColor::GREEN,CardColor::GREEN,CardColor::BLUE,CardColor::RED,CardColor::COLORLESS,CardColor::GREEN,CardColor::COLORLESS,CardColor::GREEN,CardColor::CURSE,CardColor::PURPLE,CardColor::COLORLESS,CardColor::PURPLE,CardColor::RED,CardColor::GREEN,CardColor::BLUE,CardColor::GREEN,CardColor::BLUE,CardColor::RED,CardColor::PURPLE,CardColor::PURPLE,CardColor::PURPLE,CardColor::GREEN,CardColor::RED,CardColor::COLORLESS,CardColor::GREEN,CardColor::GREEN,CardColor::BLUE,CardColor::GREEN,CardColor::BLUE,CardColor::RED,CardColor::CURSE,CardColor::COLORLESS,CardColor::RED,CardColor::BLUE,CardColor::RED,CardColor::BLUE,CardColor::BLUE,CardColor::PURPLE,CardColor::PURPLE,CardColor::PURPLE,CardColor::GREEN,CardColor::COLORLESS,CardColor::RED,CardColor::GREEN,CardColor::BLUE,CardColor::PURPLE,CardColor::GREEN,CardColor::PURPLE,CardColor::PURPLE,CardColor::GREEN,CardColor::RED,CardColor::RED,CardColor::GREEN,CardColor::COLORLESS,CardColor::COLORLESS,CardColor::PURPLE,CardColor::PURPLE,CardColor::RED,CardColor::RED,CardColor::RED,CardColor::COLORLESS,CardColor::GREEN,CardColor::RED,CardColor::BLUE,CardColor::RED,CardColor::COLORLESS,CardColor::GREEN,CardColor::RED,CardColor::PURPLE,CardColor::GREEN,CardColor::PURPLE,CardColor::PURPLE,CardColor::GREEN,CardColor::BLUE,CardColor::PURPLE,CardColor::PURPLE,CardColor::COLORLESS,CardColor::BLUE,CardColor::BLUE,CardColor::BLUE,CardColor::RED,CardColor::BLUE,CardColor::GREEN,CardColor::COLORLESS,CardColor::BLUE,CardColor::GREEN,CardColor::PURPLE,CardColor::COLORLESS,CardColor::RED,CardColor::RED,CardColor::BLUE,CardColor::RED,CardColor::GREEN,CardColor::BLUE,CardColor::RED,CardColor::BLUE,CardColor::BLUE,CardColor::RED,CardColor::COLORLESS,CardColor::RED,CardColor::PURPLE,CardColor::RED,CardColor::GREEN,CardColor::RED,CardColor::CURSE,CardColor::PURPLE,CardColor::COLORLESS,CardColor::RED,CardColor::RED,CardColor::COLORLESS,CardColor::COLORLESS,CardColor::PURPLE,CardColor::RED,CardColor::PURPLE,CardColor::BLUE,CardColor::GREEN,CardColor::PURPLE,CardColor::PURPLE,CardColor::RED,CardColor::COLORLESS,CardColor::BLUE,CardColor::BLUE,CardColor::COLORLESS,CardColor::COLORLESS,CardColor::GREEN,CardColor::GREEN,CardColor::COLORLESS,CardColor::PURPLE,CardColor::COLORLESS,CardColor::PURPLE,CardColor::BLUE,CardColor::PURPLE,CardColor::RED,CardColor::COLORLESS,CardColor::BLUE,CardColor::COLORLESS,CardColor::COLORLESS,CardColor::BLUE,CardColor::CURSE,CardColor::GREEN,CardColor::GREEN,CardColor::PURPLE,CardColor::CURSE,CardColor::GREEN,CardColor::RED,CardColor::COLORLESS,CardColor::PURPLE,CardColor::GREEN,CardColor::BLUE,CardColor::CURSE,CardColor::COLORLESS,CardColor::COLORLESS,CardColor::COLORLESS,CardColor::CURSE,CardColor::RED,CardColor::PURPLE,CardColor::GREEN,CardColor::GREEN,CardColor::GREEN,CardColor::RED,CardColor::RED,CardColor::PURPLE,CardColor::GREEN,CardColor::GREEN,CardColor::PURPLE,CardColor::CURSE,CardColor::PURPLE,CardColor::PURPLE,CardColor::RED,CardColor::COLORLESS,CardColor::GREEN,CardColor::RED,CardColor::PURPLE,CardColor::BLUE,CardColor::RED,CardColor::PURPLE,CardColor::RED,CardColor::BLUE,CardColor::BLUE,CardColor::RED,CardColor::BLUE,CardColor::BLUE,CardColor::GREEN,CardColor::CURSE,CardColor::BLUE,CardColor::BLUE,CardColor::GREEN,CardColor::BLUE,CardColor::COLORLESS,CardColor::RED,CardColor::PURPLE,CardColor::COLORLESS,CardColor::COLORLESS,CardColor::PURPLE,CardColor::PURPLE,CardColor::PURPLE,CardColor::BLUE,CardColor::PURPLE,CardColor::RED,CardColor::RED,CardColor::COLORLESS,CardColor::COLORLESS,CardColor::RED,CardColor::BLUE,CardColor::BLUE,CardColor::RED,CardColor::GREEN,CardColor::RED,CardColor::CURSE,CardColor::COLORLESS,CardColor::RED,CardColor::RED,CardColor::PURPLE,CardColor::PURPLE,CardColor::GREEN,CardColor::BLUE,CardColor::GREEN,CardColor::COLORLESS,CardColor::COLORLESS,CardColor::GREEN,CardColor::PURPLE,CardColor::RED,CardColor::BLUE,CardColor::BLUE,CardColor::BLUE,CardColor::BLUE,CardColor::GREEN,CardColor::BLUE,CardColor::BLUE,CardColor::GREEN,CardColor::RED,CardColor::PURPLE,CardColor::PURPLE,CardColor::GREEN,CardColor::BLUE,CardColor::GREEN,CardColor::BLUE,CardColor::COLORLESS,CardColor::PURPLE,CardColor::RED,CardColor::GREEN,CardColor::PURPLE,CardColor::PURPLE,CardColor::BLUE,CardColor::GREEN,CardColor::COLORLESS,CardColor::COLORLESS,CardColor::PURPLE,CardColor::COLORLESS,CardColor::RED,CardColor::BLUE,CardColor::GREEN,CardColor::PURPLE,CardColor::COLORLESS,CardColor::COLORLESS,CardColor::RED,CardColor::BLUE,CardColor::RED,CardColor::GREEN,CardColor::RED,CardColor::PURPLE,CardColor::PURPLE,CardColor::COLORLESS,CardColor::COLORLESS,CardColor::PURPLE,CardColor::RED,CardColor::PURPLE,CardColor::PURPLE,CardColor::GREEN,CardColor::PURPLE,CardColor::RED,CardColor::BLUE,CardColor::RED,CardColor::PURPLE,CardColor::PURPLE,CardColor::PURPLE,CardColor::COLORLESS,CardColor::GREEN,CardColor::PURPLE,CardColor::CURSE,CardColor::BLUE, };
    static constexpr const CardType cardTypes[] = { CardType::INVALID, CardType::POWER,CardType::SKILL,CardType::SKILL,CardType::POWER,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::CURSE,CardType::SKILL,CardType::POWER,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::POWER,CardType::ATTACK,CardType::POWER,CardType::SKILL,CardType::ATTACK,CardType::POWER,CardType::POWER,CardType::SKILL,CardType::POWER,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::POWER,CardType::POWER,CardType::SKILL,CardType::ATTACK,CardType::STATUS,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::POWER,CardType::POWER,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::CURSE,CardType::ATTACK,CardType::SKILL,CardType::POWER,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::POWER,CardType::POWER,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::CURSE,CardType::ATTACK,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::POWER,CardType::SKILL,CardType::ATTACK,CardType::STATUS,CardType::SKILL,CardType::CURSE,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::POWER,CardType::POWER,CardType::SKILL,CardType::POWER,CardType::POWER,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::CURSE,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::POWER,CardType::POWER,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::POWER,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::POWER,CardType::SKILL,CardType::ATTACK,CardType::POWER,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::POWER,CardType::ATTACK,CardType::ATTACK,CardType::POWER,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::POWER,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::ATTACK,CardType::ATTACK,CardType::POWER,CardType::SKILL,CardType::SKILL,CardType::POWER,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::POWER,CardType::ATTACK,CardType::ATTACK,CardType::POWER,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::POWER,CardType::POWER,CardType::CURSE,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::POWER,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::POWER,CardType::SKILL,CardType::POWER,CardType::POWER,CardType::POWER,CardType::SKILL,CardType::POWER,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::POWER,CardType::POWER,CardType::SKILL,CardType::ATTACK,CardType::POWER,CardType::POWER,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::CURSE,CardType::ATTACK,CardType::SKILL,CardType::POWER,CardType::CURSE,CardType::POWER,CardType::SKILL,CardType::POWER,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::CURSE,CardType::SKILL,CardType::POWER,CardType::SKILL,CardType::CURSE,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::CURSE,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::CURSE,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::ATTACK,CardType::POWER,CardType::POWER,CardType::POWER,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::POWER,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::CURSE,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::STATUS,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::POWER,CardType::SKILL,CardType::POWER,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::ATTACK,CardType::ATTACK,CardType::ATTACK,CardType::POWER,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::ATTACK,CardType::POWER,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::SKILL,CardType::STATUS,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::ATTACK,CardType::POWER,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::ATTACK,CardType::ATTACK,CardType::SKILL,CardType::SKILL,CardType::STATUS,CardType::POWER,CardType::SKILL,CardType::CURSE,CardType::SKILL, };

    static constexpr std::array<Card, 76> allColorCommonCards = {Card::GO_FOR_THE_EYES, Card::CONSECRATE, Card::CLOAK_AND_DAGGER, Card::BOWLING_BASH, Card::SNEAKY_STRIKE, Card::ANGER, Card::CLEAVE, Card::BALL_LIGHTNING, Card::WARCRY, Card::FLYING_SLEEVES, Card::STREAMLINE, Card::DEADLY_POISON, Card::FLEX, Card::RECURSION, Card::DAGGER_SPRAY, Card::HALT, Card::BANE, Card::JUST_LUCKY, Card::FLURRY_OF_BLOWS, Card::BLADE_DANCE, Card::DEFLECT, Card::COMPILE_DRIVER, Card::PROTECT, Card::DAGGER_THROW, Card::THIRD_EYE, Card::IRON_WAVE, Card::POISONED_STAB, Card::BODY_SLAM, Card::TRUE_GRIT, Card::BARRAGE, Card::CRESCENDO, Card::TRANQUILITY, Card::EMPTY_BODY, Card::SHRUG_IT_OFF, Card::CLASH, Card::STACK, Card::THUNDERCLAP, Card::REBOUND, Card::SASH_WHIP, Card::POMMEL_STRIKE, Card::ACROBATICS, Card::QUICK_SLASH, Card::TWIN_STRIKE, Card::CLAW, Card::CLOTHESLINE, Card::COOLHEADED, Card::CUT_THROUGH_FATE, Card::TURBO, Card::ARMAMENTS, Card::HAVOC, Card::SWEEPING_BEAM, Card::HEADBUTT, Card::CHARGE_BATTERY, Card::WILD_STRIKE, Card::HEAVY_BLADE, Card::HOLOGRAM, Card::FOLLOW_UP, Card::BEAM_CELL, Card::LEAP, Card::PRESSURE_POINTS, Card::SLICE, Card::BACKFLIP, Card::OUTMANEUVER, Card::COLD_SNAP, Card::CRUSH_JOINTS, Card::PERFECTED_STRIKE, Card::EVALUATE, Card::PREPARED, Card::SWORD_BOOMERANG, Card::PROSTRATE, Card::PIERCING_WAIL, Card::SUCKER_PUNCH, Card::STEAM_BARRIER, Card::DODGE_AND_ROLL, Card::EMPTY_FIST, Card::FLYING_KNEE, };
    static constexpr std::array<Card, 160> allColorUncommonCards = {Card::CRIPPLING_CLOUD, Card::STORM, Card::SPOT_WEAKNESS, Card::GENETIC_ALGORITHM, Card::OVERCLOCK, Card::HELLO_WORLD, Card::DARK_SHACKLES, Card::WHEEL_KICK, Card::SUNDER, Card::GLACIER, Card::INFLAME, Card::SIMMERING_FURY, Card::FORESIGHT, Card::CONSUME, Card::POWER_THROUGH, Card::DUAL_WIELD, Card::LEG_SWEEP, Card::PANIC_BUTTON, Card::FUSION, Card::CATALYST, Card::SANCTITY, Card::TACTICIAN, Card::INFERNAL_BLADE, Card::TALK_TO_THE_HAND, Card::BATTLE_HYMN, Card::TRIP, Card::INDIGNATION, Card::WINDMILL_STRIKE, Card::RECKLESS_CHARGE, Card::FOREIGN_INFLUENCE, Card::AGGREGATE, Card::EXPERTISE, Card::DRAMATIC_ENTRANCE, Card::HEMOKINESIS, Card::BLIZZARD, Card::CHAOS, Card::INTIMIDATE, Card::CHOKE, Card::CALTROPS, Card::IMPATIENCE, Card::BLUR, Card::LIKE_WATER, Card::SETUP, Card::BLOOD_FOR_BLOOD, Card::FASTING, Card::CARVE_REALITY, Card::WALLOP, Card::FLAME_BARRIER, Card::ENDLESS_AGONY, Card::WREATH_OF_FLAME, Card::COLLECT, Card::MELTER, Card::PUMMEL, Card::BURNING_PACT, Card::RIDDLE_WITH_HOLES, Card::METALLICIZE, Card::SELF_REPAIR, Card::INNER_PEACE, Card::RUSHDOWN, Card::LOOP, Card::BLIND, Card::SKEWER, Card::CHILL, Card::BOOT_SEQUENCE, Card::DECEIVE_REALITY, Card::MENTAL_FORTRESS, Card::SHOCKWAVE, Card::RAMPAGE, Card::STATIC_DISCHARGE, Card::HEATSINKS, Card::BANDAGE_UP, Card::SEVER_SOUL, Card::WHIRLWIND, Card::CALCULATED_GAMBLE, Card::TEMPEST, Card::COMBUST, Card::DEEP_BREATH, Card::ESCAPE_PLAN, Card::REACH_HEAVEN, Card::FINISHER, Card::DARK_EMBRACE, Card::WELL_LAID_PLANS, Card::FEAR_NO_EVIL, Card::SEEING_RED, Card::SANDS_OF_TIME, Card::DISARM, Card::EQUILIBRIUM, Card::TERROR, Card::FORCE_FIELD, Card::FEEL_NO_PAIN, Card::FTL, Card::RIP_AND_TEAR, Card::DARKNESS, Card::HEEL_HOOK, Card::DOUBLE_ENERGY, Card::RAGE, Card::REINFORCED_BODY, Card::ENTRENCH, Card::NOXIOUS_FUMES, Card::INFINITE_BLADES, Card::WAVE_OF_THE_HAND, Card::REFLEX, Card::STUDY, Card::SENTINEL, Card::MEDITATE, Card::EVISCERATE, Card::FLASH_OF_STEEL, Card::BATTLE_TRANCE, Card::FORETHOUGHT, Card::AUTO_SHIELDS, Card::PERSEVERANCE, Card::SWIVEL, Card::SEARING_BLOW, Card::REPROGRAM, Card::SECOND_WIND, Card::ENLIGHTENMENT, Card::PURITY, Card::PANACEA, Card::BULLSEYE, Card::DASH, Card::WORSHIP, Card::CONCLUDE, Card::BACKSTAB, Card::SCRAPE, Card::RUPTURE, Card::DISCOVERY, Card::BOUNCING_FLASK, Card::FINESSE, Card::RECYCLE, Card::BLOODLETTING, Card::CONCENTRATE, Card::SKIM, Card::WHITE_NOISE, Card::CAPACITOR, Card::FLECHETTES, Card::TANTRUM, Card::CARNAGE, Card::MASTERFUL_STAB, Card::NIRVANA, Card::GOOD_INSTINCTS, Card::DROPKICK, Card::SWIFT_STRIKE, Card::ACCURACY, Card::EMPTY_MIND, Card::DEFRAGMENT, Card::JACK_OF_ALL_TRADES, Card::FIRE_BREATHING, Card::GHOSTLY_ARMOR, Card::WEAVE, Card::SIGNATURE_MOVE, Card::UPPERCUT, Card::MIND_BLAST, Card::DOOM_AND_GLOOM, Card::EVOLVE, Card::FOOTWORK, Card::DISTRACTION, Card::ALL_OUT_ATTACK, Card::PREDATOR, Card::PRAY, Card::MADNESS, };
    static constexpr std::array<Card, 84> allColorRareCards = {Card::IMMOLATE, Card::GRAND_FINALE, Card::DEUS_EX_MACHINA, Card::A_THOUSAND_CUTS, Card::CORE_SURGE, Card::FISSION, Card::CREATIVE_AI, Card::GLASS_KNIFE, Card::STORM_OF_STEEL, Card::SADISTIC_NATURE, Card::OFFERING, Card::EXHUME, Card::BULLET_TIME, Card::REAPER, Card::AFTER_IMAGE, Card::UNLOAD, Card::AMPLIFY, Card::BRUTALITY, Card::NIGHTMARE, Card::REBOOT, Card::ALL_FOR_ONE, Card::TOOLS_OF_THE_TRADE, Card::ECHO_FORM, Card::JUGGERNAUT, Card::DEVA_FORM, Card::THE_BOMB, Card::SPIRIT_SHIELD, Card::IMPERVIOUS, Card::METEOR_STRIKE, Card::ESTABLISHMENT, Card::SEEK, Card::WRAITH_FORM, Card::BERSERK, Card::RAINBOW, Card::BURST, Card::DOPPELGANGER, Card::OMNISCIENCE, Card::ENVENOM, Card::ADRENALINE, Card::WISH, Card::ALPHA, Card::VAULT, Card::SCRAWL, Card::LESSON_LEARNED, Card::SECRET_TECHNIQUE, Card::DIE_DIE_DIE, Card::RAGNAROK, Card::BUFFER, Card::ELECTRODYNAMICS, Card::VIOLENCE, Card::PANACHE, Card::FIEND_FIRE, Card::BARRICADE, Card::SECRET_WEAPON, Card::APOTHEOSIS, Card::CORRUPTION, Card::BLASPHEMY, Card::MACHINE_LEARNING, Card::LIMIT_BREAK, Card::PHANTASMAL_KILLER, Card::MALAISE, Card::MAYHEM, Card::HAND_OF_GREED, Card::BIASED_COGNITION, Card::DEVOTION, Card::CORPSE_EXPLOSION, Card::TRANSMUTATION, Card::CHRYSALIS, Card::FEED, Card::ALCHEMIZE, Card::BLUDGEON, Card::BRILLIANCE, Card::MAGNETISM, Card::MASTER_OF_STRATEGY, Card::THUNDER_STRIKE, Card::MASTER_REALITY, Card::HYPERBEAM, Card::DEMON_FORM, Card::METAMORPHOSIS, Card::MULTI_CAST, Card::DOUBLE_TAP, Card::CONJURE_BLADE, Card::JUDGMENT, Card::THINKING_AHEAD, };
    static constexpr std::array<Card, 10> curseCardPool = { Card::REGRET, Card::WRITHE, Card::DECAY, Card::PAIN, Card::PARASITE, Card::DOUBT, Card::INJURY, Card::CLUMSY, Card::NORMALITY, Card::SHAME };

    namespace CardPools {
        const Card cardPool[4][72] {
                { Card::SWORD_BOOMERANG, Card::PERFECTED_STRIKE, Card::HEAVY_BLADE, Card::WILD_STRIKE, Card::HEADBUTT, Card::HAVOC, Card::ARMAMENTS, Card::CLOTHESLINE, Card::TWIN_STRIKE, Card::POMMEL_STRIKE, Card::THUNDERCLAP, Card::CLASH, Card::SHRUG_IT_OFF, Card::TRUE_GRIT,Card::BODY_SLAM, Card::IRON_WAVE, Card::FLEX, Card::WARCRY, Card::CLEAVE, Card::ANGER, Card::EVOLVE, Card::UPPERCUT, Card::GHOSTLY_ARMOR, Card::FIRE_BREATHING, Card::DROPKICK, Card::CARNAGE, Card::BLOODLETTING, Card::RUPTURE, Card::SECOND_WIND, Card::SEARING_BLOW, Card::BATTLE_TRANCE, Card::SENTINEL, Card::ENTRENCH, Card::RAGE, Card::FEEL_NO_PAIN, Card::DISARM, Card::SEEING_RED, Card::DARK_EMBRACE, Card::COMBUST, Card::WHIRLWIND, Card::SEVER_SOUL, Card::RAMPAGE, Card::SHOCKWAVE, Card::METALLICIZE, Card::BURNING_PACT, Card::PUMMEL, Card::FLAME_BARRIER, Card::BLOOD_FOR_BLOOD, Card::INTIMIDATE, Card::HEMOKINESIS, Card::RECKLESS_CHARGE, Card::INFERNAL_BLADE, Card::DUAL_WIELD, Card::POWER_THROUGH, Card::INFLAME, Card::SPOT_WEAKNESS, Card::DOUBLE_TAP, Card::DEMON_FORM, Card::BLUDGEON, Card::FEED, Card::LIMIT_BREAK, Card::CORRUPTION, Card::BARRICADE, Card::FIEND_FIRE, Card::BERSERK, Card::IMPERVIOUS, Card::JUGGERNAUT, Card::BRUTALITY, Card::REAPER, Card::EXHUME, Card::OFFERING,Card::IMMOLATE },
                { Card::FLYING_KNEE, Card::DODGE_AND_ROLL, Card::SUCKER_PUNCH, Card::PIERCING_WAIL, Card::PREPARED, Card::OUTMANEUVER, Card::BACKFLIP, Card::SLICE, Card::QUICK_SLASH, Card::ACROBATICS, Card::POISONED_STAB, Card::DAGGER_THROW, Card::DEFLECT, Card::BLADE_DANCE, Card::BANE, Card::DAGGER_SPRAY, Card::DEADLY_POISON, Card::SNEAKY_STRIKE, Card::CLOAK_AND_DAGGER, Card::PREDATOR, Card::ALL_OUT_ATTACK, Card::DISTRACTION, Card::FOOTWORK, Card::ACCURACY, Card::MASTERFUL_STAB, Card::FLECHETTES, Card::CONCENTRATE, Card::BOUNCING_FLASK, Card::BACKSTAB, Card::DASH, Card::EVISCERATE, Card::REFLEX, Card::INFINITE_BLADES, Card::NOXIOUS_FUMES, Card::HEEL_HOOK, Card::TERROR, Card::WELL_LAID_PLANS, Card::FINISHER, Card::ESCAPE_PLAN, Card::CALCULATED_GAMBLE, Card::SKEWER, Card::RIDDLE_WITH_HOLES, Card::ENDLESS_AGONY, Card::SETUP, Card::BLUR, Card::CALTROPS, Card::CHOKE, Card::EXPERTISE, Card::TACTICIAN, Card::CATALYST, Card::LEG_SWEEP, Card::CRIPPLING_CLOUD, Card::ALCHEMIZE, Card::CORPSE_EXPLOSION, Card::MALAISE, Card::PHANTASMAL_KILLER, Card::DIE_DIE_DIE, Card::ADRENALINE, Card::ENVENOM, Card::DOPPELGANGER, Card::BURST, Card::WRAITH_FORM, Card::TOOLS_OF_THE_TRADE, Card::NIGHTMARE, Card::UNLOAD, Card::AFTER_IMAGE, Card::BULLET_TIME, Card::STORM_OF_STEEL, Card::GLASS_KNIFE, Card::A_THOUSAND_CUTS, Card::GRAND_FINALE },
                { Card::STEAM_BARRIER, Card::COLD_SNAP, Card::LEAP, Card::BEAM_CELL, Card::HOLOGRAM, Card::CHARGE_BATTERY, Card::SWEEPING_BEAM, Card::TURBO, Card::COOLHEADED, Card::CLAW, Card::REBOUND, Card::STACK, Card::BARRAGE, Card::COMPILE_DRIVER, Card::RECURSION, Card::STREAMLINE, Card::BALL_LIGHTNING, Card::GO_FOR_THE_EYES, Card::DOOM_AND_GLOOM, Card::DEFRAGMENT, Card::CAPACITOR, Card::WHITE_NOISE, Card::SKIM, Card::RECYCLE, Card::SCRAPE, Card::BULLSEYE, Card::REPROGRAM, Card::AUTO_SHIELDS, Card::REINFORCED_BODY, Card::DOUBLE_ENERGY, Card::DARKNESS, Card::RIP_AND_TEAR, Card::FTL, Card::FORCE_FIELD, Card::EQUILIBRIUM, Card::TEMPEST, Card::HEATSINKS, Card::STATIC_DISCHARGE, Card::BOOT_SEQUENCE, Card::CHILL, Card::LOOP, Card::SELF_REPAIR, Card::MELTER, Card::CHAOS, Card::BLIZZARD, Card::AGGREGATE, Card::FUSION, Card::CONSUME, Card::GLACIER, Card::SUNDER, Card::HELLO_WORLD, Card::OVERCLOCK, Card::GENETIC_ALGORITHM, Card::STORM, Card::MULTI_CAST, Card::HYPERBEAM, Card::THUNDER_STRIKE, Card::BIASED_COGNITION, Card::MACHINE_LEARNING, Card::ELECTRODYNAMICS, Card::BUFFER, Card::RAINBOW, Card::SEEK, Card::METEOR_STRIKE, Card::ECHO_FORM, Card::ALL_FOR_ONE, Card::REBOOT, Card::AMPLIFY, Card::CREATIVE_AI, Card::FISSION, Card::CORE_SURGE },
                { Card::EMPTY_FIST, Card::PROSTRATE, Card::EVALUATE, Card::CRUSH_JOINTS, Card::PRESSURE_POINTS, Card::FOLLOW_UP, Card::CUT_THROUGH_FATE, Card::SASH_WHIP, Card::EMPTY_BODY, Card::TRANQUILITY, Card::CRESCENDO, Card::THIRD_EYE, Card::PROTECT, Card::FLURRY_OF_BLOWS, Card::JUST_LUCKY, Card::HALT, Card::FLYING_SLEEVES, Card::BOWLING_BASH, Card::CONSECRATE, Card::PRAY, Card::SIGNATURE_MOVE, Card::WEAVE, Card::EMPTY_MIND, Card::NIRVANA, Card::TANTRUM, Card::CONCLUDE, Card::WORSHIP, Card::SWIVEL, Card::PERSEVERANCE, Card::MEDITATE, Card::STUDY, Card::WAVE_OF_THE_HAND, Card::SANDS_OF_TIME, Card::FEAR_NO_EVIL, Card::REACH_HEAVEN, Card::MENTAL_FORTRESS, Card::DECEIVE_REALITY, Card::RUSHDOWN, Card::INNER_PEACE, Card::COLLECT, Card::WREATH_OF_FLAME, Card::WALLOP, Card::CARVE_REALITY, Card::FASTING, Card::LIKE_WATER, Card::FOREIGN_INFLUENCE, Card::WINDMILL_STRIKE, Card::INDIGNATION, Card::BATTLE_HYMN, Card::TALK_TO_THE_HAND, Card::SANCTITY, Card::FORESIGHT, Card::SIMMERING_FURY, Card::WHEEL_KICK, Card::JUDGMENT, Card::CONJURE_BLADE, Card::MASTER_REALITY, Card::BRILLIANCE, Card::DEVOTION, Card::BLASPHEMY, Card::RAGNAROK, Card::LESSON_LEARNED, Card::SCRAWL, Card::VAULT, Card::ALPHA, Card::WISH, Card::OMNISCIENCE, Card::ESTABLISHMENT, Card::SPIRIT_SHIELD, Card::DEVA_FORM, Card::DEUS_EX_MACHINA },
        };
        const int cardPoolSize[4] {72,71,71,71};

        static const Card * getCardPoolForClass(CharacterClass c) {
            return cardPool[(int)c];
        }

        static int getCardPoolSizeForClass(CharacterClass c) {
            return cardPoolSize[(int)c];
        }


        static constexpr Card cardBlob[] = {Card::ANGER,Card::BODY_SLAM,Card::CLASH,Card::CLEAVE,Card::CLOTHESLINE,Card::HEADBUTT,Card::HEAVY_BLADE,Card::IRON_WAVE,Card::PERFECTED_STRIKE,Card::POMMEL_STRIKE,Card::SWORD_BOOMERANG,Card::THUNDERCLAP,Card::TWIN_STRIKE,Card::WILD_STRIKE,Card::BLOOD_FOR_BLOOD,Card::CARNAGE,Card::DROPKICK,Card::HEMOKINESIS,Card::PUMMEL,Card::RAMPAGE,Card::RECKLESS_CHARGE,Card::SEARING_BLOW,Card::SEVER_SOUL,Card::UPPERCUT,Card::WHIRLWIND,Card::BLUDGEON,Card::FEED,Card::FIEND_FIRE,Card::IMMOLATE,Card::REAPER,Card::ARMAMENTS,Card::FLEX,Card::HAVOC,Card::SHRUG_IT_OFF,Card::TRUE_GRIT,Card::WARCRY,Card::BATTLE_TRANCE,Card::BLOODLETTING,Card::BURNING_PACT,Card::DISARM,Card::DUAL_WIELD,Card::ENTRENCH,Card::FLAME_BARRIER,Card::GHOSTLY_ARMOR,Card::INFERNAL_BLADE,Card::INTIMIDATE,Card::POWER_THROUGH,Card::RAGE,Card::SECOND_WIND,Card::SEEING_RED,Card::SENTINEL,Card::SHOCKWAVE,Card::SPOT_WEAKNESS,Card::DOUBLE_TAP,Card::EXHUME,Card::IMPERVIOUS,Card::LIMIT_BREAK,Card::OFFERING,Card::COMBUST,Card::DARK_EMBRACE,Card::EVOLVE,Card::FEEL_NO_PAIN,Card::FIRE_BREATHING,Card::INFLAME,Card::METALLICIZE,Card::RUPTURE,Card::BARRICADE,Card::BERSERK,Card::BRUTALITY,Card::CORRUPTION,Card::DEMON_FORM,Card::JUGGERNAUT,Card::BANE,Card::DAGGER_SPRAY,Card::DAGGER_THROW,Card::FLYING_KNEE,Card::POISONED_STAB,Card::QUICK_SLASH,Card::SLICE,Card::SUCKER_PUNCH,Card::SNEAKY_STRIKE,Card::ALL_OUT_ATTACK,Card::BACKSTAB,Card::CHOKE,Card::DASH,Card::ENDLESS_AGONY,Card::EVISCERATE,Card::FINISHER,Card::FLECHETTES,Card::HEEL_HOOK,Card::MASTERFUL_STAB,Card::PREDATOR,Card::RIDDLE_WITH_HOLES,Card::SKEWER,Card::DIE_DIE_DIE,Card::GLASS_KNIFE,Card::GRAND_FINALE,Card::UNLOAD,Card::ACROBATICS,Card::BACKFLIP,Card::BLADE_DANCE,Card::CLOAK_AND_DAGGER,Card::DEADLY_POISON,Card::DEFLECT,Card::DODGE_AND_ROLL,Card::OUTMANEUVER,Card::PIERCING_WAIL,Card::PREPARED,Card::BLUR,Card::BOUNCING_FLASK,Card::CALCULATED_GAMBLE,Card::CATALYST,Card::CONCENTRATE,Card::CRIPPLING_CLOUD,Card::DISTRACTION,Card::ESCAPE_PLAN,Card::EXPERTISE,Card::LEG_SWEEP,Card::REFLEX,Card::SETUP,Card::TACTICIAN,Card::TERROR,Card::ADRENALINE,Card::BULLET_TIME,Card::BURST,Card::CORPSE_EXPLOSION,Card::DOPPELGANGER,Card::MALAISE,Card::NIGHTMARE,Card::PHANTASMAL_KILLER,Card::STORM_OF_STEEL,Card::ALCHEMIZE,Card::ACCURACY,Card::CALTROPS,Card::FOOTWORK,Card::INFINITE_BLADES,Card::NOXIOUS_FUMES,Card::WELL_LAID_PLANS,Card::A_THOUSAND_CUTS,Card::AFTER_IMAGE,Card::ENVENOM,Card::TOOLS_OF_THE_TRADE,Card::WRAITH_FORM,Card::BALL_LIGHTNING,Card::BARRAGE,Card::BEAM_CELL,Card::COLD_SNAP,Card::COMPILE_DRIVER,Card::CLAW,Card::GO_FOR_THE_EYES,Card::REBOUND,Card::STREAMLINE,Card::SWEEPING_BEAM,Card::BLIZZARD,Card::DOOM_AND_GLOOM,Card::FTL,Card::BULLSEYE,Card::MELTER,Card::RIP_AND_TEAR,Card::SCRAPE,Card::SUNDER,Card::ALL_FOR_ONE,Card::CORE_SURGE,Card::HYPERBEAM,Card::METEOR_STRIKE,Card::THUNDER_STRIKE,Card::CHARGE_BATTERY,Card::COOLHEADED,Card::HOLOGRAM,Card::LEAP,Card::RECURSION,Card::STACK,Card::STEAM_BARRIER,Card::TURBO,Card::AGGREGATE,Card::AUTO_SHIELDS,Card::BOOT_SEQUENCE,Card::CHAOS,Card::CHILL,Card::CONSUME,Card::DARKNESS,Card::DOUBLE_ENERGY,Card::FORCE_FIELD,Card::FUSION,Card::GENETIC_ALGORITHM,Card::GLACIER,Card::RECYCLE,Card::REINFORCED_BODY,Card::REPROGRAM,Card::SKIM,Card::OVERCLOCK,Card::TEMPEST,Card::EQUILIBRIUM,Card::WHITE_NOISE,Card::AMPLIFY,Card::FISSION,Card::MULTI_CAST,Card::RAINBOW,Card::REBOOT,Card::SEEK,Card::CAPACITOR,Card::DEFRAGMENT,Card::HEATSINKS,Card::HELLO_WORLD,Card::LOOP,Card::SELF_REPAIR,Card::STATIC_DISCHARGE,Card::STORM,Card::BIASED_COGNITION,Card::BUFFER,Card::CREATIVE_AI,Card::ECHO_FORM,Card::ELECTRODYNAMICS,Card::MACHINE_LEARNING,Card::BOWLING_BASH,Card::CONSECRATE,Card::CRUSH_JOINTS,Card::CUT_THROUGH_FATE,Card::EMPTY_FIST,Card::FLURRY_OF_BLOWS,Card::FLYING_SLEEVES,Card::FOLLOW_UP,Card::JUST_LUCKY,Card::SASH_WHIP,Card::CARVE_REALITY,Card::CONCLUDE,Card::FEAR_NO_EVIL,Card::REACH_HEAVEN,Card::SANDS_OF_TIME,Card::SIGNATURE_MOVE,Card::TALK_TO_THE_HAND,Card::TANTRUM,Card::WALLOP,Card::WEAVE,Card::WHEEL_KICK,Card::WINDMILL_STRIKE,Card::BRILLIANCE,Card::LESSON_LEARNED,Card::RAGNAROK,Card::TRANQUILITY,Card::CRESCENDO,Card::EMPTY_BODY,Card::EVALUATE,Card::HALT,Card::PRESSURE_POINTS,Card::PROSTRATE,Card::PROTECT,Card::THIRD_EYE,Card::COLLECT,Card::DECEIVE_REALITY,Card::EMPTY_MIND,Card::FOREIGN_INFLUENCE,Card::INDIGNATION,Card::INNER_PEACE,Card::MEDITATE,Card::PERSEVERANCE,Card::PRAY,Card::SANCTITY,Card::SWIVEL,Card::SIMMERING_FURY,Card::WAVE_OF_THE_HAND,Card::WORSHIP,Card::WREATH_OF_FLAME,Card::ALPHA,Card::BLASPHEMY,Card::CONJURE_BLADE,Card::DEUS_EX_MACHINA,Card::JUDGMENT,Card::OMNISCIENCE,Card::SCRAWL,Card::SPIRIT_SHIELD,Card::VAULT,Card::WISH,Card::RUSHDOWN,Card::BATTLE_HYMN,Card::FASTING,Card::LIKE_WATER,Card::MENTAL_FORTRESS,Card::NIRVANA,Card::STUDY,Card::FORESIGHT,Card::DEVA_FORM,Card::DEVOTION,Card::ESTABLISHMENT,Card::MASTER_REALITY,};
        static constexpr int groupOffset[4][3][3] {{{0, 14, 25,}, {30, 36, 53,}, {58, 58, 66,},}, {{72, 81, 94,}, {98, 108, 122,}, {132, 132, 138,},}, {{143, 153, 161,}, {166, 174, 194,}, {200, 200, 208,},}, {{214, 224, 236,}, {239, 248, 263,}, {273, 273, 281,},},};
        static constexpr int groupSize[4][3][3] {{{14,11,5,},{6,17,5,},{0,8,6,},},{{9,13,4,},{10,14,10,},{0,6,5,},},{{10,8,5,},{8,20,6,},{0,8,6,},},{{10,12,3,},{9,15,10,},{0,8,4,},}};

        static constexpr Card colorlessCardBlob[] { Card::BANDAGE_UP,Card::BLIND,Card::DARK_SHACKLES,Card::DEEP_BREATH,Card::DISCOVERY,Card::DRAMATIC_ENTRANCE,Card::ENLIGHTENMENT,Card::FINESSE,Card::FLASH_OF_STEEL,Card::FORETHOUGHT,Card::GOOD_INSTINCTS,Card::IMPATIENCE,Card::JACK_OF_ALL_TRADES,Card::MADNESS,Card::MIND_BLAST,Card::PANACEA,Card::PANIC_BUTTON,Card::PURITY,Card::SWIFT_STRIKE,Card::TRIP,Card::APOTHEOSIS,Card::CHRYSALIS,Card::HAND_OF_GREED,Card::MAGNETISM,Card::MASTER_OF_STRATEGY,Card::MAYHEM,Card::METAMORPHOSIS,Card::PANACHE,Card::SADISTIC_NATURE,Card::SECRET_TECHNIQUE,Card::SECRET_WEAPON,Card::THE_BOMB,Card::THINKING_AHEAD,Card::TRANSMUTATION,Card::VIOLENCE, };
        static constexpr int colorlessGroupSize[3] = {0, 20, 15};
        static constexpr int colorlessGroupOffset[3] = {0, 0, 20};


        static int getGroupOffset(CardColor color, CardType type, CardRarity rarity) {
            return groupOffset[static_cast<int>(color)][static_cast<int>(type)][static_cast<int>(rarity)];
        }

        static int getGroupSize(CardColor color, CardType type, CardRarity rarity) {
            return groupSize[static_cast<int>(color)][static_cast<int>(type)][static_cast<int>(rarity)];
        }

        static int getGroupSize(CharacterClass c, CardType type, CardRarity rarity) {
            return getGroupSize((CardColor)c, type, rarity);
        }

        static Card getCardAt(CardColor color, CardType type, CardRarity rarity, int offset) {
            int startIdx = getGroupOffset(color, type, rarity);
            return cardBlob[startIdx+offset];
        }

        static Card getCardAt(CharacterClass c, CardType type, CardRarity rarity, int offset) {
            return getCardAt((CardColor)c, type, rarity, offset);
        }

        static int getColorlessGroupSize(CardRarity rarity) {
            return colorlessGroupSize[(int)rarity];
        }

        static Card getColorlessCardAt(CardRarity rarity, int offset) {
            int startIdx = colorlessGroupOffset[(int)rarity];
            return colorlessCardBlob[startIdx+offset];
        }


//        static constexpr std::array<std::array<Card,40>> commonAttackPool = {
//
//        };

//        static constexpr std::arrayCardColor

    }

    namespace Ironclad {
        static constexpr std::array<Relic, 33> commonRelicPool = {WHETSTONE, THE_BOOT, BLOOD_VIAL, MEAL_TICKET, PEN_NIB, AKABEKO, LANTERN, REGAL_PILLOW, BAG_OF_PREPARATION, ANCIENT_TEA_SET, SMILING_MASK, POTION_BELT, PRESERVED_INSECT, OMAMORI, MAW_BANK, ART_OF_WAR, TOY_ORNITHOPTER, CERAMIC_FISH, VAJRA, CENTENNIAL_PUZZLE, STRAWBERRY, HAPPY_FLOWER, ODDLY_SMOOTH_STONE, WAR_PAINT, BRONZE_SCALES, JUZU_BRACELET, DREAM_CATCHER, NUNCHAKU, TINY_CHEST, ORICHALCUM, ANCHOR, BAG_OF_MARBLES, RED_SKULL};
        static constexpr std::array<Relic, 30> uncommonRelicPool = {BOTTLED_TORNADO, SUNDIAL, KUNAI, PEAR, BLUE_CANDLE, ETERNAL_FEATHER, STRIKE_DUMMY, SINGING_BOWL, MATRYOSHKA, INK_BOTTLE, THE_COURIER, FROZEN_EGG, ORNAMENTAL_FAN, BOTTLED_LIGHTNING, GREMLIN_HORN, HORN_CLEAT, TOXIC_EGG, LETTER_OPENER, QUESTION_CARD, BOTTLED_FLAME, SHURIKEN, MOLTEN_EGG, MEAT_ON_THE_BONE, DARKSTONE_PERIAPT, MUMMIFIED_HAND, PANTOGRAPH, WHITE_BEAST_STATUE, MERCURY_HOURGLASS, SELF_FORMING_CLAY, PAPER_PHROG};
        static constexpr std::array<Relic, 28> rareRelicPool = {GINGER, OLD_COIN, BIRD_FACED_URN, UNCEASING_TOP, TORII, STONE_CALENDAR, SHOVEL, WING_BOOTS, THREAD_AND_NEEDLE, TURNIP, ICE_CREAM, CALIPERS, LIZARD_TAIL, PRAYER_WHEEL, GIRYA, DEAD_BRANCH, DU_VU_DOLL, POCKETWATCH, MANGO, INCENSE_BURNER, GAMBLING_CHIP, PEACE_PIPE, CAPTAINS_WHEEL, FOSSILIZED_HELIX, TUNGSTEN_ROD, MAGIC_FLOWER, CHARONS_ASHES, CHAMPION_BELT};
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

        static constexpr std::array<Potion, 33> potions = { Potion::BLOOD_POTION, Potion::ELIXIR_POTION, Potion::HEART_OF_IRON, Potion::BLOCK_POTION, Potion::DEXTERITY_POTION, Potion::ENERGY_POTION, Potion::EXPLOSIVE_POTION, Potion::FIRE_POTION, Potion::STRENGTH_POTION, Potion::SWIFT_POTION, Potion::WEAK_POTION, Potion::FEAR_POTION, Potion::ATTACK_POTION, Potion::SKILL_POTION, Potion::POWER_POTION, Potion::COLORLESS_POTION, Potion::FLEX_POTION, Potion::SPEED_POTION, Potion::BLESSING_OF_THE_FORGE, Potion::REGEN_POTION, Potion::ANCIENT_POTION, Potion::LIQUID_BRONZE, Potion::GAMBLERS_BREW, Potion::ESSENCE_OF_STEEL, Potion::DUPLICATION_POTION, Potion::DISTILLED_CHAOS, Potion::LIQUID_MEMORIES, Potion::CULTIST_POTION, Potion::FRUIT_JUICE, Potion::SNECKO_OIL, Potion::FAIRY_POTION, Potion::SMOKE_BOMB, Potion::ENTROPIC_BREW };
    };

    namespace Silent {
        static constexpr std::array<Relic, 22> bossRelicPool = {FUSION_HAMMER, VELVET_CHOKER, RUNIC_DOME, SLAVERS_COLLAR, SNECKO_EYE, PANDORAS_BOX, CURSED_KEY, BUSTED_CROWN, ECTOPLASM, TINY_HOUSE, SOZU, PHILOSOPHERS_STONE, ASTROLABE, BLACK_STAR, SACRED_BARK, EMPTY_CAGE, RUNIC_PYRAMID, CALLING_BELL, COFFEE_DRIPPER, WRIST_BLADE, HOVERING_KITE, RING_OF_THE_SERPENT};

        static constexpr std::array<Card, 71> cardPool = {Card::FLYING_KNEE, Card::DODGE_AND_ROLL, Card::SUCKER_PUNCH, Card::PIERCING_WAIL, Card::PREPARED, Card::OUTMANEUVER, Card::BACKFLIP, Card::SLICE, Card::QUICK_SLASH, Card::ACROBATICS, Card::POISONED_STAB, Card::DAGGER_THROW, Card::DEFLECT, Card::BLADE_DANCE, Card::BANE, Card::DAGGER_SPRAY, Card::DEADLY_POISON, Card::SNEAKY_STRIKE, Card::CLOAK_AND_DAGGER, Card::PREDATOR, Card::ALL_OUT_ATTACK, Card::DISTRACTION, Card::FOOTWORK, Card::ACCURACY, Card::MASTERFUL_STAB, Card::FLECHETTES, Card::CONCENTRATE, Card::BOUNCING_FLASK, Card::BACKSTAB, Card::DASH, Card::EVISCERATE, Card::REFLEX, Card::INFINITE_BLADES, Card::NOXIOUS_FUMES, Card::HEEL_HOOK, Card::TERROR, Card::WELL_LAID_PLANS, Card::FINISHER, Card::ESCAPE_PLAN, Card::CALCULATED_GAMBLE, Card::SKEWER, Card::RIDDLE_WITH_HOLES, Card::ENDLESS_AGONY, Card::SETUP, Card::BLUR, Card::CALTROPS, Card::CHOKE, Card::EXPERTISE, Card::TACTICIAN, Card::CATALYST, Card::LEG_SWEEP, Card::CRIPPLING_CLOUD, Card::ALCHEMIZE, Card::CORPSE_EXPLOSION, Card::MALAISE, Card::PHANTASMAL_KILLER, Card::DIE_DIE_DIE, Card::ADRENALINE, Card::ENVENOM, Card::DOPPELGANGER, Card::BURST, Card::WRAITH_FORM, Card::TOOLS_OF_THE_TRADE, Card::NIGHTMARE, Card::UNLOAD, Card::AFTER_IMAGE, Card::BULLET_TIME, Card::STORM_OF_STEEL, Card::GLASS_KNIFE, Card::A_THOUSAND_CUTS, Card::GRAND_FINALE };
        static constexpr std::array<Card, 20> commonCardPool = { Card::CLOAK_AND_DAGGER, Card::SNEAKY_STRIKE, Card::DEADLY_POISON, Card::DAGGER_SPRAY, Card::BANE, Card::BLADE_DANCE, Card::DEFLECT, Card::DAGGER_THROW, Card::POISONED_STAB, Card::ACROBATICS, Card::QUICK_SLASH, Card::SLICE, Card::BACKFLIP, Card::OUTMANEUVER, Card::PREPARED, Card::PIERCING_WAIL, Card::SUCKER_PUNCH, Card::DODGE_AND_ROLL, Card::FLYING_KNEE };
        static constexpr std::array<Card, 33> uncommonCardPool = { Card::CRIPPLING_CLOUD, Card::LEG_SWEEP, Card::CATALYST, Card::TACTICIAN, Card::EXPERTISE, Card::CHOKE, Card::CALTROPS, Card::BLUR, Card::SETUP, Card::ENDLESS_AGONY, Card::RIDDLE_WITH_HOLES, Card::SKEWER, Card::CALCULATED_GAMBLE, Card::ESCAPE_PLAN, Card::FINISHER, Card::WELL_LAID_PLANS, Card::TERROR, Card::HEEL_HOOK, Card::NOXIOUS_FUMES, Card::INFINITE_BLADES, Card::REFLEX, Card::EVISCERATE, Card::DASH, Card::BACKSTAB, Card::BOUNCING_FLASK, Card::CONCENTRATE, Card::FLECHETTES, Card::MASTERFUL_STAB, Card::ACCURACY, Card::FOOTWORK, Card::DISTRACTION, Card::ALL_OUT_ATTACK, Card::PREDATOR };
        static constexpr std::array<Card, 19> rareCardPool = { Card::GRAND_FINALE, Card::A_THOUSAND_CUTS, Card::GLASS_KNIFE, Card::STORM_OF_STEEL, Card::BULLET_TIME, Card::AFTER_IMAGE, Card::UNLOAD, Card::NIGHTMARE, Card::TOOLS_OF_THE_TRADE, Card::WRAITH_FORM, Card::BURST, Card::DOPPELGANGER, Card::ENVENOM, Card::ADRENALINE, Card::DIE_DIE_DIE, Card::PHANTASMAL_KILLER, Card::MALAISE, Card::CORPSE_EXPLOSION, Card::ALCHEMIZE };

        static constexpr std::array<Potion, 33> potions = { Potion::POISON_POTION, Potion::CUNNING_POTION, Potion::GHOST_IN_A_JAR, Potion::BLOCK_POTION, Potion::DEXTERITY_POTION, Potion::ENERGY_POTION, Potion::EXPLOSIVE_POTION, Potion::FIRE_POTION, Potion::STRENGTH_POTION, Potion::SWIFT_POTION, Potion::WEAK_POTION, Potion::FEAR_POTION, Potion::ATTACK_POTION, Potion::SKILL_POTION, Potion::POWER_POTION, Potion::COLORLESS_POTION, Potion::FLEX_POTION, Potion::SPEED_POTION, Potion::BLESSING_OF_THE_FORGE, Potion::REGEN_POTION, Potion::ANCIENT_POTION, Potion::LIQUID_BRONZE, Potion::GAMBLERS_BREW, Potion::ESSENCE_OF_STEEL, Potion::DUPLICATION_POTION, Potion::DISTILLED_CHAOS, Potion::LIQUID_MEMORIES, Potion::CULTIST_POTION, Potion::FRUIT_JUICE, Potion::SNECKO_OIL, Potion::FAIRY_POTION, Potion::SMOKE_BOMB, Potion::ENTROPIC_BREW };
    };

    namespace Defect {
        static constexpr std::array<Relic, 33> commonRelicPool = { WHETSTONE, THE_BOOT, BLOOD_VIAL, MEAL_TICKET, PEN_NIB, AKABEKO, LANTERN, REGAL_PILLOW, BAG_OF_PREPARATION, ANCIENT_TEA_SET, SMILING_MASK, POTION_BELT, PRESERVED_INSECT, OMAMORI, MAW_BANK, ART_OF_WAR, TOY_ORNITHOPTER, CERAMIC_FISH, VAJRA, CENTENNIAL_PUZZLE, STRAWBERRY, HAPPY_FLOWER, ODDLY_SMOOTH_STONE, WAR_PAINT, BRONZE_SCALES, JUZU_BRACELET, DREAM_CATCHER, NUNCHAKU, TINY_CHEST, ORICHALCUM, ANCHOR, BAG_OF_MARBLES, DATA_DISK };
        static constexpr std::array<Relic, 30> uncommonRelicPool = { BOTTLED_TORNADO, SUNDIAL, KUNAI, PEAR, BLUE_CANDLE, ETERNAL_FEATHER, STRIKE_DUMMY, SINGING_BOWL, MATRYOSHKA, INK_BOTTLE, THE_COURIER, FROZEN_EGG, ORNAMENTAL_FAN, BOTTLED_LIGHTNING, GREMLIN_HORN, HORN_CLEAT, TOXIC_EGG, LETTER_OPENER, QUESTION_CARD, BOTTLED_FLAME, SHURIKEN, MOLTEN_EGG, MEAT_ON_THE_BONE, DARKSTONE_PERIAPT, MUMMIFIED_HAND, PANTOGRAPH, WHITE_BEAST_STATUE, MERCURY_HOURGLASS, SYMBIOTIC_VIRUS, GOLD_PLATED_CABLES };
        static constexpr std::array<Relic, 26> rareRelicPool = { GINGER, OLD_COIN, BIRD_FACED_URN, UNCEASING_TOP, TORII, STONE_CALENDAR, SHOVEL, WING_BOOTS, THREAD_AND_NEEDLE, TURNIP, ICE_CREAM, CALIPERS, LIZARD_TAIL, PRAYER_WHEEL, GIRYA, DEAD_BRANCH, DU_VU_DOLL, POCKETWATCH, MANGO, INCENSE_BURNER, GAMBLING_CHIP, PEACE_PIPE, CAPTAINS_WHEEL, FOSSILIZED_HELIX, EMOTION_CHIP };
        static constexpr std::array<Relic, 22> bossRelicPool = { FUSION_HAMMER, VELVET_CHOKER, RUNIC_DOME, SLAVERS_COLLAR, SNECKO_EYE, PANDORAS_BOX, CURSED_KEY, BUSTED_CROWN, ECTOPLASM, TINY_HOUSE, SOZU, PHILOSOPHERS_STONE, ASTROLABE, BLACK_STAR, SACRED_BARK, EMPTY_CAGE, RUNIC_PYRAMID, CALLING_BELL, COFFEE_DRIPPER, INSERTER, FROZEN_CORE, NUCLEAR_BATTERY };

        static constexpr std::array<Card, 71> cardPool = {Card::STEAM_BARRIER, Card::COLD_SNAP, Card::LEAP, Card::BEAM_CELL, Card::HOLOGRAM, Card::CHARGE_BATTERY, Card::SWEEPING_BEAM, Card::TURBO, Card::COOLHEADED, Card::CLAW, Card::REBOUND, Card::STACK, Card::BARRAGE, Card::COMPILE_DRIVER, Card::RECURSION, Card::STREAMLINE, Card::BALL_LIGHTNING, Card::GO_FOR_THE_EYES, Card::DOOM_AND_GLOOM, Card::DEFRAGMENT, Card::CAPACITOR, Card::WHITE_NOISE, Card::SKIM, Card::RECYCLE, Card::SCRAPE, Card::BULLSEYE, Card::REPROGRAM, Card::AUTO_SHIELDS, Card::REINFORCED_BODY, Card::DOUBLE_ENERGY, Card::DARKNESS, Card::RIP_AND_TEAR, Card::FTL, Card::FORCE_FIELD, Card::EQUILIBRIUM, Card::TEMPEST, Card::HEATSINKS, Card::STATIC_DISCHARGE, Card::BOOT_SEQUENCE, Card::CHILL, Card::LOOP, Card::SELF_REPAIR, Card::MELTER, Card::CHAOS, Card::BLIZZARD, Card::AGGREGATE, Card::FUSION, Card::CONSUME, Card::GLACIER, Card::SUNDER, Card::HELLO_WORLD, Card::OVERCLOCK, Card::GENETIC_ALGORITHM, Card::STORM, Card::MULTI_CAST, Card::HYPERBEAM, Card::THUNDER_STRIKE, Card::BIASED_COGNITION, Card::MACHINE_LEARNING, Card::ELECTRODYNAMICS, Card::BUFFER, Card::RAINBOW, Card::SEEK, Card::METEOR_STRIKE, Card::ECHO_FORM, Card::ALL_FOR_ONE, Card::REBOOT, Card::AMPLIFY, Card::CREATIVE_AI, Card::FISSION, Card::CORE_SURGE };
        static constexpr std::array<Card, 18> commonCardPool = { Card::GO_FOR_THE_EYES, Card::BALL_LIGHTNING, Card::STREAMLINE, Card::RECURSION, Card::COMPILE_DRIVER, Card::BARRAGE, Card::STACK, Card::REBOUND, Card::CLAW, Card::COOLHEADED, Card::TURBO, Card::SWEEPING_BEAM, Card::CHARGE_BATTERY, Card::HOLOGRAM, Card::BEAM_CELL, Card::LEAP, Card::COLD_SNAP, Card::STEAM_BARRIER };
        static constexpr std::array<Card, 36> uncommonCardPool = { Card::STORM, Card::GENETIC_ALGORITHM, Card::OVERCLOCK, Card::HELLO_WORLD, Card::SUNDER, Card::GLACIER, Card::CONSUME, Card::FUSION, Card::AGGREGATE, Card::BLIZZARD, Card::CHAOS, Card::MELTER, Card::SELF_REPAIR, Card::LOOP, Card::CHILL, Card::BOOT_SEQUENCE, Card::STATIC_DISCHARGE, Card::HEATSINKS, Card::TEMPEST, Card::EQUILIBRIUM, Card::FORCE_FIELD, Card::FTL, Card::RIP_AND_TEAR, Card::DARKNESS, Card::DOUBLE_ENERGY, Card::REINFORCED_BODY, Card::AUTO_SHIELDS, Card::REPROGRAM, Card::BULLSEYE, Card::SCRAPE, Card::RECYCLE, Card::SKIM, Card::WHITE_NOISE, Card::CAPACITOR, Card::DEFRAGMENT, Card::DOOM_AND_GLOOM };
        static constexpr std::array<Card, 17> rareCardPool = { Card::CORE_SURGE, Card::FISSION, Card::CREATIVE_AI, Card::AMPLIFY, Card::REBOOT, Card::ALL_FOR_ONE, Card::ECHO_FORM, Card::METEOR_STRIKE, Card::SEEK, Card::RAINBOW, Card::BUFFER, Card::ELECTRODYNAMICS, Card::MACHINE_LEARNING, Card::BIASED_COGNITION, Card::THUNDER_STRIKE, Card::HYPERBEAM, Card::MULTI_CAST };

        static constexpr std::array<Potion, 33> potions = { Potion::FOCUS_POTION, Potion::POTION_OF_CAPACITY, Potion::ESSENCE_OF_DARKNESS, Potion::BLOCK_POTION, Potion::DEXTERITY_POTION, Potion::ENERGY_POTION, Potion::EXPLOSIVE_POTION, Potion::FIRE_POTION, Potion::STRENGTH_POTION, Potion::SWIFT_POTION, Potion::WEAK_POTION, Potion::FEAR_POTION, Potion::ATTACK_POTION, Potion::SKILL_POTION, Potion::POWER_POTION, Potion::COLORLESS_POTION, Potion::FLEX_POTION, Potion::SPEED_POTION, Potion::BLESSING_OF_THE_FORGE, Potion::REGEN_POTION, Potion::ANCIENT_POTION, Potion::LIQUID_BRONZE, Potion::GAMBLERS_BREW, Potion::ESSENCE_OF_STEEL, Potion::DUPLICATION_POTION, Potion::DISTILLED_CHAOS, Potion::LIQUID_MEMORIES, Potion::CULTIST_POTION, Potion::FRUIT_JUICE, Potion::SNECKO_OIL, Potion::FAIRY_POTION, Potion::SMOKE_BOMB, Potion::ENTROPIC_BREW };
    };

    namespace Watcher {
        static constexpr std::array<Relic, 21> bossRelicPool = {FUSION_HAMMER, VELVET_CHOKER, RUNIC_DOME, SLAVERS_COLLAR, SNECKO_EYE, PANDORAS_BOX, CURSED_KEY, BUSTED_CROWN, ECTOPLASM, TINY_HOUSE, SOZU, PHILOSOPHERS_STONE, ASTROLABE, BLACK_STAR, SACRED_BARK, EMPTY_CAGE, RUNIC_PYRAMID, CALLING_BELL, COFFEE_DRIPPER, HOLY_WATER, VIOLET_LOTUS};

        static constexpr std::array<Card, 71> cardPool = { Card::EMPTY_FIST, Card::PROSTRATE, Card::EVALUATE, Card::CRUSH_JOINTS, Card::PRESSURE_POINTS, Card::FOLLOW_UP, Card::CUT_THROUGH_FATE, Card::SASH_WHIP, Card::EMPTY_BODY, Card::TRANQUILITY, Card::CRESCENDO, Card::THIRD_EYE, Card::PROTECT, Card::FLURRY_OF_BLOWS, Card::JUST_LUCKY, Card::HALT, Card::FLYING_SLEEVES, Card::BOWLING_BASH, Card::CONSECRATE, Card::PRAY, Card::SIGNATURE_MOVE, Card::WEAVE, Card::EMPTY_MIND, Card::NIRVANA, Card::TANTRUM, Card::CONCLUDE, Card::WORSHIP, Card::SWIVEL, Card::PERSEVERANCE, Card::MEDITATE, Card::STUDY, Card::WAVE_OF_THE_HAND, Card::SANDS_OF_TIME, Card::FEAR_NO_EVIL, Card::REACH_HEAVEN, Card::MENTAL_FORTRESS, Card::DECEIVE_REALITY, Card::RUSHDOWN, Card::INNER_PEACE, Card::COLLECT, Card::WREATH_OF_FLAME, Card::WALLOP, Card::CARVE_REALITY, Card::FASTING, Card::LIKE_WATER, Card::FOREIGN_INFLUENCE, Card::WINDMILL_STRIKE, Card::INDIGNATION, Card::BATTLE_HYMN, Card::TALK_TO_THE_HAND, Card::SANCTITY, Card::FORESIGHT, Card::SIMMERING_FURY, Card::WHEEL_KICK, Card::JUDGMENT, Card::CONJURE_BLADE, Card::MASTER_REALITY, Card::BRILLIANCE, Card::DEVOTION, Card::BLASPHEMY, Card::RAGNAROK, Card::LESSON_LEARNED, Card::SCRAWL, Card::VAULT, Card::ALPHA, Card::WISH, Card::OMNISCIENCE, Card::ESTABLISHMENT, Card::SPIRIT_SHIELD, Card::DEVA_FORM, Card::DEUS_EX_MACHINA };
        static constexpr std::array<Card, 19> commonCardPool = { Card::CONSECRATE, Card::BOWLING_BASH, Card::FLYING_SLEEVES, Card::HALT, Card::JUST_LUCKY, Card::FLURRY_OF_BLOWS, Card::PROTECT, Card::THIRD_EYE, Card::CRESCENDO, Card::TRANQUILITY, Card::EMPTY_BODY, Card::SASH_WHIP, Card::CUT_THROUGH_FATE, Card::FOLLOW_UP, Card::PRESSURE_POINTS, Card::CRUSH_JOINTS, Card::EVALUATE, Card::PROSTRATE, Card::EMPTY_FIST };
        static constexpr std::array<Card, 35> uncommonCardPool = { Card::WHEEL_KICK, Card::SIMMERING_FURY, Card::FORESIGHT, Card::SANCTITY, Card::TALK_TO_THE_HAND, Card::BATTLE_HYMN, Card::INDIGNATION, Card::WINDMILL_STRIKE, Card::FOREIGN_INFLUENCE, Card::LIKE_WATER, Card::FASTING, Card::CARVE_REALITY, Card::WALLOP, Card::WREATH_OF_FLAME, Card::COLLECT, Card::INNER_PEACE, Card::RUSHDOWN, Card::DECEIVE_REALITY, Card::MENTAL_FORTRESS, Card::REACH_HEAVEN, Card::FEAR_NO_EVIL, Card::SANDS_OF_TIME, Card::WAVE_OF_THE_HAND, Card::STUDY, Card::MEDITATE, Card::PERSEVERANCE, Card::SWIVEL, Card::WORSHIP, Card::CONCLUDE, Card::TANTRUM, Card::NIRVANA, Card::EMPTY_MIND, Card::WEAVE, Card::SIGNATURE_MOVE, Card::PRAY };
        static constexpr std::array<Card, 17> rareCardPool = { Card::DEUS_EX_MACHINA, Card::DEVA_FORM, Card::SPIRIT_SHIELD, Card::ESTABLISHMENT, Card::OMNISCIENCE, Card::WISH, Card::ALPHA, Card::VAULT, Card::SCRAWL, Card::LESSON_LEARNED, Card::RAGNAROK, Card::BLASPHEMY, Card::DEVOTION, Card::BRILLIANCE, Card::MASTER_REALITY, Card::CONJURE_BLADE, Card::JUDGMENT };

        static constexpr std::array<Potion, 33> potions = { Potion::BOTTLED_MIRACLE, Potion::STANCE_POTION, Potion::AMBROSIA, Potion::BLOCK_POTION, Potion::DEXTERITY_POTION, Potion::ENERGY_POTION, Potion::EXPLOSIVE_POTION, Potion::FIRE_POTION, Potion::STRENGTH_POTION, Potion::SWIFT_POTION, Potion::WEAK_POTION, Potion::FEAR_POTION, Potion::ATTACK_POTION, Potion::SKILL_POTION, Potion::POWER_POTION, Potion::COLORLESS_POTION, Potion::FLEX_POTION, Potion::SPEED_POTION, Potion::BLESSING_OF_THE_FORGE, Potion::REGEN_POTION, Potion::ANCIENT_POTION, Potion::LIQUID_BRONZE, Potion::GAMBLERS_BREW, Potion::ESSENCE_OF_STEEL, Potion::DUPLICATION_POTION, Potion::DISTILLED_CHAOS, Potion::LIQUID_MEMORIES, Potion::CULTIST_POTION, Potion::FRUIT_JUICE, Potion::SNECKO_OIL, Potion::FAIRY_POTION, Potion::SMOKE_BOMB, Potion::ENTROPIC_BREW };
    };

}


#endif //STS_SEED_SEARCH_STS_CONSTANTS_H
