// hashtable destructor (0x00840220): clear() frees the nodes (DoFreeNodes 0x83fee0) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_840220(void* p);   // 0x00f47380

struct Node_840220;
struct Hashtable_840220 {
    uint32_t mHash;                           // +0x00
    Node_840220** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_840220** pBucketArray, unsigned n);   // 0x0083fee0
    ~Hashtable_840220();
};

// @ 0x00840220
Hashtable_840220::~Hashtable_840220()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_840220(mpBucketArray);
}
