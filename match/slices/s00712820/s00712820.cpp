// hashtable destructor (0x00712820): clear() frees the nodes (DoFreeNodes 0x712320) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_712820(void* p);   // 0x00f47380

struct Node_712820;
struct Hashtable_712820 {
    uint32_t mHash;                           // +0x00
    Node_712820** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_712820** pBucketArray, unsigned n);   // 0x00712320
    ~Hashtable_712820();
};

// @ 0x00712820
Hashtable_712820::~Hashtable_712820()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_712820(mpBucketArray);
}
