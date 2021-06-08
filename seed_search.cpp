
#include "seed_search.h"

#include <array>
#include <algorithm>
#include <thread>

#include "java_random.h"

using namespace sts;

std::vector<std::int64_t> SeedSearcher::search(std::int64_t startSeed, std::int64_t count) const {
    std::vector<std::int64_t> foundSeeds;
    for (std::int64_t seed = startSeed; seed < startSeed+count; ++seed) {
        if (matcher.match(seed)) {
            foundSeeds.push_back(seed);
        }
    }
    return foundSeeds;
}

std::int64_t SeedSearcher::countMatching(std::int64_t startSeed, std::int64_t count) const {
    std::int64_t found = 0;
    for (std::int64_t seed = startSeed; seed < startSeed+count; ++seed) {
        if (matcher.match(seed)) {
            ++found;
        }
    }
    return found;
}


struct ThreadData {
    SeedMatcher m;
    std::int64_t startSeed, count;
    int threadCount, threadId;
    std::int64_t &foundOut;

    ThreadData(SeedMatcher m, int64_t startSeed, int64_t count, int threadCount, int threadId, int64_t &foundOut)
            : m(m), startSeed(startSeed), count(count), threadCount(threadCount), threadId(threadId),
              foundOut(foundOut) {}
};


void countMatchingMtHelper(ThreadData d) {
    for (std::int64_t seed = d.startSeed+d.threadId; seed < d.startSeed+d.count; seed += d.threadCount) {
        if (d.m.match(seed)) {
            ++d.foundOut;
        }
    }
}

std::int64_t SeedSearcher::countMatchingMt(std::int64_t startSeed, std::int64_t count, int threadCount) const {

    std::thread *threads[threadCount];
    std::int64_t results[threadCount];

    for (int tid = 0; tid < threadCount; ++tid) {
        results[tid] = 0;
        ThreadData data(matcher, startSeed, count, threadCount, tid, results[tid]);
        threads[tid] = new std::thread(countMatchingMtHelper, data);
    }

    std::int64_t total = 0;
    for (int tid = 0; tid < threadCount; ++tid) {
        threads[tid]->join();
        delete threads[tid];
        total += results[tid];
    }

    return total;
}


void SeedMatcher::addPredicate(SeedPredicate p) {
    predicates.emplace_back(1, p);
}

void SeedMatcher::addNeowPredicate(NeowPredicate p) {
    predicates.emplace_back(0, [=](long seed) {
            return p(Neow::generateRewards(seed));
        }
    );
}

bool SeedMatcher::match(std::int64_t seed) const{
    return std::all_of(predicates.begin(), predicates.end(), [seed](auto &p) { return p.predicate(seed); } );
}

void SeedMatcher::mustHaveCallingBellRewards(Relic common, Relic uncommon, Relic rare) {
    addPredicate([=](long seed) {

        sts::Random relicRng = sts::Random(seed);

        java::Random commonRandom(relicRng.randomLong());
        java::Random uncommonRandom(relicRng.randomLong());
        java::Random rareRandom(relicRng.randomLong());
        relicRng.randomLong();
        java::Random bossRandom(relicRng.randomLong());

        auto boss = sts::Ironclad::bossRelicPool;
        java::Collections::shuffle( boss.begin(), boss.end(), bossRandom);
        if (boss[0] != sts::CALLING_BELL) {
            return false;
        }

        auto c = sts::Ironclad::commonRelicPool;
        java::Collections::shuffle( c.begin(), c.end(), commonRandom);
        if (c[0] != common) {
            return false;
        }

        auto uc = sts::Ironclad::uncommonRelicPool;
        java::Collections::shuffle( uc.begin(), uc.end(), uncommonRandom);
        if (uc[0] != uncommon) {
            return false;
        }

        auto r = sts::Ironclad::rareRelicPool;
        java::Collections::shuffle( r.begin(), r.end(), rareRandom);
        if (r[0] != rare) {
            return false;
        }

        return true;
    });
}