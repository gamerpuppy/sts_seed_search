
#ifndef STS_SEED_SEARCH_JAVA_RANDOM_H
#define STS_SEED_SEARCH_JAVA_RANDOM_H

#include <cstdint>
#include <algorithm>

namespace java {

class Random {
private:
///** use serialVersionUID from JDK 1.1 for interoperability */
//    std::int64_t serialVersionUID = 3905348978240129619LL;

    // atomic long
    std::int64_t seed;
    static constexpr std::int64_t multiplier = 0x5DEECE66DLL;
    static constexpr std::int64_t addend = 0xBLL;
    static constexpr std::int64_t mask = (1LL << 48) - 1;
    static constexpr double DOUBLE_UNIT = 0x1.0p-53; // 1.0 / (1L << 53)

    static std::int64_t initialScramble(std::int64_t seed) {
        return (seed ^ multiplier) & mask;
    }

public:
    Random(std::int64_t seed) : seed(initialScramble(seed)) {}

    std::int32_t next(std::int32_t bits) {
        seed = (seed * multiplier + addend) & mask;
        return static_cast<std::int32_t>(seed >> (48 - bits));
    }

    int32_t nextInt() {
        return next(32);
    }

    int32_t nextInt(int32_t bound) {
        int r = next(31);
        int m = bound - 1;
        if ((bound & m) == 0)  // i.e., bound is a power of 2
            r = static_cast<int32_t>( ((bound * static_cast<std::int64_t>(r)) >> 31) );
        else {
            for (int32_t u = r;
                 u - (r = u % bound) + m < 0;
                 u = next(31))
                ;
        }
        return r;
    }
};

namespace Collections {
    template <typename ForwardIterator>
    void shuffle(ForwardIterator begin, ForwardIterator end, java::Random rnd) {
        auto size = static_cast<int32_t>(end-begin);

        for (int i=size; i>1; i--) {
            std::swap(*(begin + i - 1), *(begin + rnd.nextInt(i)));
        }
    }
}


}


#endif //STS_SEED_SEARCH_JAVA_RANDOM_H
