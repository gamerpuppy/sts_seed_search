

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


    void runSearch(SearchConfig config);

}


#endif //STS_SEED_SEARCH_SEED_SEARCH_H
