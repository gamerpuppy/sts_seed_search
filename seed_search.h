

#ifndef STS_SEED_SEARCH_SEED_SEARCH_H
#define STS_SEED_SEARCH_SEED_SEARCH_H

#include <array>
#include <functional>
#include <utility>

#include "sts_impl.h"

namespace sts {

    struct ThreadData {
        std::int64_t startSeed;
        std::int64_t endSeed;
        int threadCount;
        int threadId;
        std::vector<std::int64_t> *foundVec;

        ThreadData(int64_t startSeed, int64_t endSeed, int threadCount, int threadId,
                   std::vector<int64_t> *foundVec) : startSeed(startSeed), endSeed(endSeed), threadCount(threadCount),
                                                     threadId(threadId), foundVec(foundVec) {}
    };


    struct PandorasBoxRewardResult {
        int count;
        const char *name;
    };

    std::vector<int64_t> testPandorasForDefectWatcherMt(std::int64_t startSeed, std::int64_t endSeed, int threadCount);

    struct SearchConfig {
        std::string resultsFile = "results.txt";
        std::int64_t blockAmount = 50000000000LL;
        std::int64_t startSeed = -1;
        int threads = 1;
    };

    struct candidate {
        std::int64_t start;
        std::int64_t end;
        std::int32_t stride;

};
    void runSearch(SearchConfig config);
    std::vector<std::int64_t> runSearch2(const std::vector<candidate> &candidates);


    void describeSeeds(const std::vector<std::int64_t> seeds);

    void test();



    std::vector<std::int64_t> findSinglePathSeedsMt(std::int64_t start, std::int64_t count, int threadCount, int length);




}



#endif //STS_SEED_SEARCH_SEED_SEARCH_H
