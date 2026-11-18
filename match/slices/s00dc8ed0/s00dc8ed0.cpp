// @ 0x00dc8ed0
// Retail symbol (PDB): eastl::hashtable<SP::cLocomotiveObject *,
//   eastl::pair<SP::cLocomotiveObject * const, SP::cMovingFormation::cEntityInfo>, ...>::operator=
// The EASTL instantiation is out of scope, so this stand-in reproduces its 0x20-byte layout and
// compiles to the same copy-and-swap code: copy-construct a temporary (0x00dc8a60), Swap (0x00dc8ba0),
// then run the inlined bucket-array destructor (FreeChains 0x00ba2980, operator delete[] when count > 1).
#include "game/types.h"
#include <new>

struct CultureHashNode;

// Hash container used by the moving formation's vehicle data.
struct CultureHash {
    uint32_t mAllocator;
    CultureHashNode** mBuckets;
    uint32_t mBucketCount;
    uint32_t mElementCount;
    uint32_t mRehashPolicy[3];
    uint32_t mHashPolicy;

    CultureHash(const CultureHash& other); // 0x00dc8a60
    void Swap(CultureHash& other);         // 0x00dc8ba0
    void FreeChains(CultureHashNode** buckets, uint32_t count); // 0x00ba2980
    CultureHash& operator=(const CultureHash& other);
};

CultureHash& CultureHash::operator=(const CultureHash& other)
{
    if (this != &other) {
        CultureHash temporary(other);
        Swap(temporary);
        temporary.FreeChains(temporary.mBuckets, temporary.mBucketCount);
        temporary.mElementCount = 0;
        if (temporary.mBucketCount > 1)
            operator delete[](temporary.mBuckets);
    }
    return *this;
}
