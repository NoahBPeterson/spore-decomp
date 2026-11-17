// hashtable destructor (0x00702e70): clear() frees the nodes (DoFreeNodes 0x702660) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_702e70(void* p);   // 0x00f47380

struct Node_702e70;
struct Hashtable_702e70 {
    uint32_t mHash;                           // +0x00
    Node_702e70** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_702e70** pBucketArray, unsigned n);   // 0x00702660
    ~Hashtable_702e70();
};

// @ 0x00702e70
Hashtable_702e70::~Hashtable_702e70()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_702e70(mpBucketArray);
}
