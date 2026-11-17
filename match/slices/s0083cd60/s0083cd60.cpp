// hashtable destructor (0x0083cd60): clear() frees the nodes (DoFreeNodes 0x83cad0) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_83cd60(void* p);   // 0x00f47380

struct Node_83cd60;
struct Hashtable_83cd60 {
    uint32_t mHash;                           // +0x00
    Node_83cd60** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_83cd60** pBucketArray, unsigned n);   // 0x0083cad0
    ~Hashtable_83cd60();
};

// @ 0x0083cd60
Hashtable_83cd60::~Hashtable_83cd60()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_83cd60(mpBucketArray);
}
