// hashtable destructor (0x007c7470): clear() frees the nodes (DoFreeNodes 0x7c7050) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_7c7470(void* p);   // 0x00f47380

struct Node_7c7470;
struct Hashtable_7c7470 {
    uint32_t mHash;                           // +0x00
    Node_7c7470** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_7c7470** pBucketArray, unsigned n);   // 0x007c7050
    ~Hashtable_7c7470();
};

// @ 0x007c7470
Hashtable_7c7470::~Hashtable_7c7470()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_7c7470(mpBucketArray);
}
