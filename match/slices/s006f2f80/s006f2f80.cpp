// hashtable destructor (0x006f2f80): clear() frees the nodes (DoFreeNodes 0x6f2430) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_6f2f80(void* p);   // 0x00f47380

struct Node_6f2f80;
struct Hashtable_6f2f80 {
    uint32_t mHash;                           // +0x00
    Node_6f2f80** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_6f2f80** pBucketArray, unsigned n);   // 0x006f2430
    ~Hashtable_6f2f80();
};

// @ 0x006f2f80
Hashtable_6f2f80::~Hashtable_6f2f80()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_6f2f80(mpBucketArray);
}
