

#ifndef STS_SEED_SEARCH_SEED_SEARCH_H
#define STS_SEED_SEARCH_SEED_SEARCH_H

#include <array>
#include <functional>
#include <utility>
#include <chrono>

#include "sts_impl.h"

namespace sts {

    class Timer
    {
    public:
        void start()
        {
            m_StartTime = std::chrono::system_clock::now();
            m_bRunning = true;
        }

        void stop()
        {
            m_EndTime = std::chrono::system_clock::now();
            m_bRunning = false;
        }

        double elapsedMilliseconds()
        {
            std::chrono::time_point<std::chrono::system_clock> endTime;

            if(m_bRunning)
            {
                endTime = std::chrono::system_clock::now();
            }
            else
            {
                endTime = m_EndTime;
            }

            return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
        }

        double elapsedSeconds()
        {
            return elapsedMilliseconds() / 1000.0;
        }

    private:
        std::chrono::time_point<std::chrono::system_clock> m_StartTime;
        std::chrono::time_point<std::chrono::system_clock> m_EndTime;
        bool                                               m_bRunning = false;
    };

    typedef std::function<bool(std::int64_t)> SeedPredicate;



    struct ThreadData {
        std::int64_t startSeed;
        std::int64_t endSeed;
        int threadCount;
        int threadId;
        std::vector<std::int64_t> *foundVec;
        bool printWhenFound = false;
        SeedPredicate predicate;


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


    std::vector<std::int64_t>
    findSinglePathSeedsMt(std::int64_t start, std::int64_t count, int threadCount, int length);




    class Path;
    bool validateNeowBossPath(std::int64_t seed, const Path &p);
    bool testSeedForNeowBossEvent(std::int64_t seed);

    bool testSeedForCardReward(std::int64_t seed);

    bool testSeedForFruitJuiceNeows(std::int64_t);

    std::vector<std::int64_t> testSeedsMt(std::int64_t start, std::int64_t count, int threadCount, const SeedPredicate& predicate, bool printWhenFound= false, bool logStats= false);


}

#endif //STS_SEED_SEARCH_SEED_SEARCH_H
