

#ifndef STS_SEED_SEARCH_SEED_SEARCH_H
#define STS_SEED_SEARCH_SEED_SEARCH_H

#include <array>
#include <functional>
#include <utility>

#include "sts_impl.h"

namespace sts {

typedef std::function<bool(NeowBlessing)> NeowPredicate;
typedef std::function<bool(std::int64_t)> SeedPredicate;
typedef std::function<bool(std::array<Card,10>)> PandoraPredicate;

class SeedMatcher {
private:
    struct SeedPredicateWrapper {
        int order = 0;
        SeedPredicate predicate;
        SeedPredicateWrapper(int order, SeedPredicate predicate) : order(order), predicate(std::move(predicate)) {}
    };

    std::vector<SeedPredicateWrapper> predicates;

public:
    void addPredicate(SeedPredicate p);
    void addNeowPredicate(NeowPredicate p);
    void addPandoraPredicate(CharacterClass character, PandoraPredicate p);

    bool match(std::int64_t seed) const;

    void mustHaveCallingBellRewards(Relic common, Relic uncommon, Relic rare);
    void mustGetBossRelicFromSwap(Relic bossRelic);


};

class SeedSearcher {
private:
    SeedMatcher matcher;

public:
    SeedSearcher(SeedMatcher matcher) : matcher(std::move(matcher)) {}

    std::vector<std::int64_t> search(std::int64_t startSeed, std::int64_t count) const;
    std::vector<std::int64_t> searchMt(int64_t startSeed, int64_t count, int threadCount) const;



    std::int64_t countMatching(std::int64_t startSeed, std::int64_t count) const;
    std::int64_t countMatchingMt(std::int64_t startSeed, std::int64_t count, int threads) const;

    std::string getFirstMatching(std::int64_t startSeed, std::int64_t maxCount) const;


};


struct ThreadData {
    const SeedMatcher *m;
    std::int64_t startSeed;
    std::int64_t count;
    int threadCount;
    int threadId;
    std::int64_t *foundOutCount;
    std::vector<std::int64_t> *foundOutRet;

    ThreadData(const SeedMatcher *m, int64_t startSeed, int64_t count, int threadCount, int threadId,
               int64_t *foundOutCount) : m(m), startSeed(startSeed), count(count), threadCount(threadCount),
                                         threadId(threadId), foundOutCount(foundOutCount) {}

    ThreadData(const SeedMatcher *m, int64_t startSeed, int64_t count, int threadCount, int threadId,
               std::vector<int64_t> *foundOutRet) : m(m), startSeed(startSeed), count(count), threadCount(threadCount),
                                                    threadId(threadId), foundOutRet(foundOutRet) {}
};


struct seed_result {
    int count;
    const char* name;
};


Card getCard(int idx, CharacterClass characterClass);
seed_result analyzePandorasBoxRewards(std::int64_t seed, CharacterClass characterClass);



}


#endif //STS_SEED_SEARCH_SEED_SEARCH_H
