
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
    static constexpr std::int32_t BINARYSEARCH_THRESHOLD   = 5000;
    static constexpr std::int32_t REVERSE_THRESHOLD        =   18;
    static constexpr std::int32_t SHUFFLE_THRESHOLD        =    5;
    static constexpr std::int32_t FILL_THRESHOLD           =   25;
    static constexpr std::int32_t ROTATE_THRESHOLD         =  100;
    static constexpr std::int32_t COPY_THRESHOLD           =   10;
    static constexpr std::int32_t REPLACEALL_THRESHOLD     =   11;
    static constexpr std::int32_t INDEXOFSUBLIST_THRESHOLD =   35;

    // only works for collections with random access or size < shuffle threshold
    template <typename ForwardIterator>
    void shuffle(ForwardIterator begin, ForwardIterator end, java::Random &r) {
        Random rnd = r;
        auto size = static_cast<int32_t>(end-begin);

        for (int i=size; i>1; i--) {
            std::swap(*(begin + i - 1), *(begin + rnd.nextInt(i)));
        }
    }

}


}



//
///**
// * Returns a pseudorandom, uniformly distributed {@code int} value
// * between 0 (inclusive) and the specified value (exclusive), drawn from
// * this random number generator's sequence.  The general contract of
// * {@code nextInt} is that one {@code int} value in the specified range
// * is pseudorandomly generated and returned.  All {@code bound} possible
// * {@code int} values are produced with (approximately) equal
// * probability.  The method {@code nextInt(int bound)} is implemented by
// * class {@code Random} as if by:
// *  <pre> {@code
// * public int nextInt(int bound) {
// *   if (bound <= 0)
// *     throw new IllegalArgumentException("bound must be positive");
// *
// *   if ((bound & -bound) == bound)  // i.e., bound is a power of 2
// *     return (int)((bound * (long)next(31)) >> 31);
// *
// *   int bits, val;
// *   do {
// *       bits = next(31);
// *       val = bits % bound;
// *   } while (bits - val + (bound-1) < 0);
// *   return val;
// * }}</pre>
// *
// * <p>The hedge "approximately" is used in the foregoing description only
// * because the next method is only approximately an unbiased source of
// * independently chosen bits.  If it were a perfect source of randomly
// * chosen bits, then the algorithm shown would choose {@code int}
// * values from the stated range with perfect uniformity.
// * <p>
// * The algorithm is slightly tricky.  It rejects values that would result
// * in an uneven distribution (due to the fact that 2^31 is not divisible
// * by n). The probability of a value being rejected depends on n.  The
// * worst case is n=2^30+1, for which the probability of a reject is 1/2,
// * and the expected number of iterations before the loop terminates is 2.
// * <p>
// * The algorithm treats the case where n is a power of two specially: it
// * returns the correct number of high-order bits from the underlying
// * pseudo-random number generator.  In the absence of special treatment,
// * the correct number of <i>low-order</i> bits would be returned.  Linear
// * congruential pseudo-random number generators such as the one
// * implemented by this class are known to have short periods in the
// * sequence of values of their low-order bits.  Thus, this special case
// * greatly increases the length of the sequence of values returned by
// * successive calls to this method if n is a small power of two.
// *
// * @param bound the upper bound (exclusive).  Must be positive.
// * @return the next pseudorandom, uniformly distributed {@code int}
// *         value between zero (inclusive) and {@code bound} (exclusive)
// *         from this random number generator's sequence
// * @throws IllegalArgumentException if bound is not positive
// * @since 1.2
// */
//public int nextInt(int bound) {
//    if (bound <= 0)
//        throw new IllegalArgumentException(BadBound);
//
//    int r = next(31);
//    int m = bound - 1;
//    if ((bound & m) == 0)  // i.e., bound is a power of 2
//        r = (int)((bound * (long)r) >> 31);
//    else {
//        for (int u = r;
//             u - (r = u % bound) + m < 0;
//             u = next(31))
//            ;
//    }
//    return r;
//}
//
///**
// * Returns the next pseudorandom, uniformly distributed {@code long}
// * value from this random number generator's sequence. The general
// * contract of {@code nextLong} is that one {@code long} value is
// * pseudorandomly generated and returned.
// *
// * <p>The method {@code nextLong} is implemented by class {@code Random}
// * as if by:
// *  <pre> {@code
// * public long nextLong() {
// *   return ((long)next(32) << 32) + next(32);
// * }}</pre>
// *
// * Because class {@code Random} uses a seed with only 48 bits,
// * this algorithm will not return all possible {@code long} values.
// *
// * @return the next pseudorandom, uniformly distributed {@code long}
// *         value from this random number generator's sequence
// */
//public long nextLong() {
//    // it's okay that the bottom word remains signed.
//    return ((long)(next(32)) << 32) + next(32);
//}
//
///**
// * Returns the next pseudorandom, uniformly distributed
// * {@code boolean} value from this random number generator's
// * sequence. The general contract of {@code nextBoolean} is that one
// * {@code boolean} value is pseudorandomly generated and returned.  The
// * values {@code true} and {@code false} are produced with
// * (approximately) equal probability.
// *
// * <p>The method {@code nextBoolean} is implemented by class {@code Random}
// * as if by:
// *  <pre> {@code
// * public boolean nextBoolean() {
// *   return next(1) != 0;
// * }}</pre>
// *
// * @return the next pseudorandom, uniformly distributed
// *         {@code boolean} value from this random number generator's
// *         sequence
// * @since 1.2
// */
//public boolean nextBoolean() {
//    return next(1) != 0;
//}
//
///**
// * Returns the next pseudorandom, uniformly distributed {@code float}
// * value between {@code 0.0} and {@code 1.0} from this random
// * number generator's sequence.
// *
// * <p>The general contract of {@code nextFloat} is that one
// * {@code float} value, chosen (approximately) uniformly from the
// * range {@code 0.0f} (inclusive) to {@code 1.0f} (exclusive), is
// * pseudorandomly generated and returned. All 2<sup>24</sup> possible
// * {@code float} values of the form <i>m&nbsp;x&nbsp;</i>2<sup>-24</sup>,
// * where <i>m</i> is a positive integer less than 2<sup>24</sup>, are
// * produced with (approximately) equal probability.
// *
// * <p>The method {@code nextFloat} is implemented by class {@code Random}
// * as if by:
// *  <pre> {@code
// * public float nextFloat() {
// *   return next(24) / ((float)(1 << 24));
// * }}</pre>
// *
// * <p>The hedge "approximately" is used in the foregoing description only
// * because the next method is only approximately an unbiased source of
// * independently chosen bits. If it were a perfect source of randomly
// * chosen bits, then the algorithm shown would choose {@code float}
// * values from the stated range with perfect uniformity.<p>
// * [In early versions of Java, the result was incorrectly calculated as:
// *  <pre> {@code
// *   return next(30) / ((float)(1 << 30));}</pre>
// * This might seem to be equivalent, if not better, but in fact it
// * introduced a slight nonuniformity because of the bias in the rounding
// * of floating-point numbers: it was slightly more likely that the
// * low-order bit of the significand would be 0 than that it would be 1.]
// *
// * @return the next pseudorandom, uniformly distributed {@code float}
// *         value between {@code 0.0} and {@code 1.0} from this
// *         random number generator's sequence
// */
//public float nextFloat() {
//    return next(24) / ((float)(1 << 24));
//}
//
///**
// * Returns the next pseudorandom, uniformly distributed
// * {@code double} value between {@code 0.0} and
// * {@code 1.0} from this random number generator's sequence.
// *
// * <p>The general contract of {@code nextDouble} is that one
// * {@code double} value, chosen (approximately) uniformly from the
// * range {@code 0.0d} (inclusive) to {@code 1.0d} (exclusive), is
// * pseudorandomly generated and returned.
// *
// * <p>The method {@code nextDouble} is implemented by class {@code Random}
// * as if by:
// *  <pre> {@code
// * public double nextDouble() {
// *   return (((long)next(26) << 27) + next(27))
// *     / (double)(1L << 53);
// * }}</pre>
// *
// * <p>The hedge "approximately" is used in the foregoing description only
// * because the {@code next} method is only approximately an unbiased
// * source of independently chosen bits. If it were a perfect source of
// * randomly chosen bits, then the algorithm shown would choose
// * {@code double} values from the stated range with perfect uniformity.
// * <p>[In early versions of Java, the result was incorrectly calculated as:
// *  <pre> {@code
// *   return (((long)next(27) << 27) + next(27))
// *     / (double)(1L << 54);}</pre>
// * This might seem to be equivalent, if not better, but in fact it
// * introduced a large nonuniformity because of the bias in the rounding
// * of floating-point numbers: it was three times as likely that the
// * low-order bit of the significand would be 0 than that it would be 1!
// * This nonuniformity probably doesn't matter much in practice, but we
// * strive for perfection.]
// *
// * @return the next pseudorandom, uniformly distributed {@code double}
// *         value between {@code 0.0} and {@code 1.0} from this
// *         random number generator's sequence
// * @see Math#random
// */
//public double nextDouble() {
//    return (((long)(next(26)) << 27) + next(27)) * DOUBLE_UNIT;
//}
//
//private double nextNextGaussian;
//private boolean haveNextNextGaussian = false;
//
///**
// * Returns the next pseudorandom, Gaussian ("normally") distributed
// * {@code double} value with mean {@code 0.0} and standard
// * deviation {@code 1.0} from this random number generator's sequence.
// * <p>
// * The general contract of {@code nextGaussian} is that one
// * {@code double} value, chosen from (approximately) the usual
// * normal distribution with mean {@code 0.0} and standard deviation
// * {@code 1.0}, is pseudorandomly generated and returned.
// *
// * <p>The method {@code nextGaussian} is implemented by class
// * {@code Random} as if by a threadsafe version of the following:
// *  <pre> {@code
// * private double nextNextGaussian;
// * private boolean haveNextNextGaussian = false;
// *
// * public double nextGaussian() {
// *   if (haveNextNextGaussian) {
// *     haveNextNextGaussian = false;
// *     return nextNextGaussian;
// *   } else {
// *     double v1, v2, s;
// *     do {
// *       v1 = 2 * nextDouble() - 1;   // between -1.0 and 1.0
// *       v2 = 2 * nextDouble() - 1;   // between -1.0 and 1.0
// *       s = v1 * v1 + v2 * v2;
// *     } while (s >= 1 || s == 0);
// *     double multiplier = StrictMath.sqrt(-2 * StrictMath.log(s)/s);
// *     nextNextGaussian = v2 * multiplier;
// *     haveNextNextGaussian = true;
// *     return v1 * multiplier;
// *   }
// * }}</pre>
// * This uses the <i>polar method</i> of G. E. P. Box, M. E. Muller, and
// * G. Marsaglia, as described by Donald E. Knuth in <i>The Art of
// * Computer Programming</i>, Volume 3: <i>Seminumerical Algorithms</i>,
// * section 3.4.1, subsection C, algorithm P. Note that it generates two
// * independent values at the cost of only one call to {@code StrictMath.log}
// * and one call to {@code StrictMath.sqrt}.
// *
// * @return the next pseudorandom, Gaussian ("normally") distributed
// *         {@code double} value with mean {@code 0.0} and
// *         standard deviation {@code 1.0} from this random number
// *         generator's sequence
// */
////synchronized public double nextGaussian() {
////    // See Knuth, ACP, Section 3.4.1 Algorithm C.
////    if (haveNextNextGaussian) {
////        haveNextNextGaussian = false;
////        return nextNextGaussian;
////    } else {
////        double v1, v2, s;
////        do {
////            v1 = 2 * nextDouble() - 1; // between -1 and 1
////            v2 = 2 * nextDouble() - 1; // between -1 and 1
////            s = v1 * v1 + v2 * v2;
////        } while (s >= 1 || s == 0);
////        double multiplier = StrictMath.sqrt(-2 * StrictMath.log(s)/s);
////        nextNextGaussian = v2 * multiplier;
////        haveNextNextGaussian = true;
////        return v1 * multiplier;
////    }
////}
//
//}



#endif //STS_SEED_SEARCH_JAVA_RANDOM_H
