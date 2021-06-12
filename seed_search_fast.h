//
// Created by keega on 6/9/2021.
//

#ifndef STS_SEED_SEARCH_SEED_SEARCH_FAST_H
#define STS_SEED_SEARCH_SEED_SEARCH_FAST_H

#include <cstdint>

#include "java_random.h"

namespace sts::fast {

    class Random {
    private:
        static constexpr std::uint64_t ONE_IN_MOST_SIGNIFICANT = static_cast<std::uint64_t>(1) << 63;

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

        std::int32_t nextInt(std::int32_t n) {
            return static_cast<std::int32_t>(nextLong(static_cast<std::uint64_t>(n)));
        }


    public:

        Random(std::uint64_t seed) {
            seed0 = murmurHash3(seed == 0 ? ONE_IN_MOST_SIGNIFICANT : seed);
            seed1 = murmurHash3(seed0);
        }

        std::int32_t random(std::int32_t range) {
            return nextInt(range + 1);
        }

    };






}







#endif //STS_SEED_SEARCH_SEED_SEARCH_FAST_H
