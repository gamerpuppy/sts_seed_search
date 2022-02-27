
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
        x *= static_cast<std::uint64_t>(-49064778989728563LL);
        x ^= x >> 33;
        x *= static_cast<std::uint64_t>(-4265267296055464877LL);
        x ^= x >> 33;
        return x;
    }

    std::uint64_t nextLong() {
        std::uint64_t s1 = seed0;
        std::uint64_t s0 = seed1;
        seed0 = s0;
        s1 ^= s1 << 23;

        seed1 = s1 ^ s0 ^ s1 >> 17 ^ s0 >> 26;
        return seed1 + s0;
    }


    // n must be greater than 0
    std::uint64_t nextLong(std::uint64_t n) {
        std::uint64_t bits;
        std::uint64_t value;
        do {
            bits = static_cast<std::uint64_t>(nextLong()) >> 1;
            value = bits % n;
        } while (static_cast<int64_t>(bits - value + n - 1) < 0LL);
        return static_cast<std::uint64_t>(value);
    }

    std::int32_t nextInt() {
        return static_cast<std::int32_t>(nextLong());
    }

    double nextDouble() {
        auto x = nextLong() >> 11;
        return static_cast<double>(x) * NORM_DOUBLE;
    }

    float nextFloat() {
        auto x = nextLong() >> 40;
        double d = static_cast<double>(x) * NORM_FLOAT;
        return static_cast<float>(d);
    }

    bool nextBoolean() {
        return (nextLong() & 1ULL) != 0ULL;
    }

    bool randomBoolean(float chance) {
        ++counter;
        return nextFloat() < chance;
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
        return static_cast<std::int32_t>(nextLong(n));
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
                rewards[2].r = static_cast<Reward>(11 + r.random(0, 6));
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
