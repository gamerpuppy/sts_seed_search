

#ifndef STS_SEED_SEARCH_SEED_SEARCH_H
#define STS_SEED_SEARCH_SEED_SEARCH_H

#include <array>
#include <functional>
#include <utility>

#include "sts_impl.h"

namespace sts {

typedef std::function<bool(NeowBlessing)> NeowPredicate;
typedef std::function<bool(long)> SeedPredicate;





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
    bool match(std::int64_t seed) const;

    void mustHaveCallingBellRewards(Relic common, Relic uncommon, Relic rare);


};

class SeedSearcher {
private:
    SeedMatcher matcher;

public:
    SeedSearcher(SeedMatcher matcher) : matcher(std::move(matcher)) {}

    std::vector<std::int64_t> search(std::int64_t startSeed, std::int64_t count) const;
    std::int64_t countMatching(std::int64_t startSeed, std::int64_t count) const;


    std::int64_t countMatchingMt(std::int64_t startSeed, std::int64_t count, int threads) const;


};



}


#endif //STS_SEED_SEARCH_SEED_SEARCH_H
