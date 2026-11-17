// hashtable destructor (0x00713530): clear() frees the nodes (DoFreeNodes 0x712b20) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_713530(void* p);   // 0x00f47380

struct Node_713530;
struct Hashtable_713530 {
    uint32_t mHash;                           // +0x00
    Node_713530** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_713530** pBucketArray, unsigned n);   // 0x00712b20
    ~Hashtable_713530();
};

// @ 0x00713530
Hashtable_713530::~Hashtable_713530()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_713530(mpBucketArray);
}
