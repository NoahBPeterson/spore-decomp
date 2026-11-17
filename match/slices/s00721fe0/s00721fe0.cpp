// hashtable destructor (0x00721fe0): clear() frees the nodes (DoFreeNodes 0x7611f0) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_721fe0(void* p);   // 0x00f47380

struct Node_721fe0;
struct Hashtable_721fe0 {
    uint32_t mHash;                           // +0x00
    Node_721fe0** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_721fe0** pBucketArray, unsigned n);   // 0x007611f0
    ~Hashtable_721fe0();
};

// @ 0x00721fe0
Hashtable_721fe0::~Hashtable_721fe0()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_721fe0(mpBucketArray);
}
