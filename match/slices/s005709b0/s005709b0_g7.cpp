// slice s005709b0 (gold7): merge-join of a feature vector against a
// {key, weight} vector. Same module build as the committed source (/Od /Ob1),
// with /fp:fast so the scalar float multiply stays in SSE.
#include "types.h"

// 12-byte feature key: {cID (2 x uint32), float} (same type as s005709b0.cpp).
struct Key12 {
    uint32_t mA;    // +0x00
    uint32_t mB;    // +0x04
    float mC;       // +0x08
};

struct cFeatureVector {
    Key12* mpBegin;     // +0x00
    Key12* mpEnd;       // +0x04
    Key12* mpCapacity;  // +0x08
};

// 8-byte {key, weight} entry of the weight vector.
struct WeightPair {
    uint32_t mKey;  // +0x00
    float mVal;     // +0x04
};

struct WeightVector {
    WeightPair* mpBegin;    // +0x00
    WeightPair* mpEnd;      // +0x04
};

// @ 0x00571530
// For every feature key, advance the weight cursor to the matching key and
// scale the feature value by that weight. Fails on any unmatched key.
bool IntersectWeights(const cFeatureVector* a, const WeightVector* b)
{
    WeightPair* wtIt = b->mpBegin;
    WeightPair* wtEnd = b->mpEnd;
    Key12* fit = a->mpBegin;
    Key12* fitEnd = a->mpEnd;

    for (; fit != fitEnd; ++fit)
    {
        for (; wtIt != wtEnd && wtIt->mKey < fit->mA; ++wtIt)
            ;
        if (wtIt == wtEnd || wtIt->mKey != fit->mA)
            return false;
        fit->mC *= wtIt->mVal;
    }
    return true;
}
