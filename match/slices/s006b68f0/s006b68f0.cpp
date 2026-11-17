// hashtable destructor (0x006b68f0): clear() frees the nodes (DoFreeNodes 0x6b6570) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_6b68f0(void* p);   // 0x00f47380

struct Node_6b68f0;
struct Hashtable_6b68f0 {
    uint32_t mHash;                           // +0x00
    Node_6b68f0** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_6b68f0** pBucketArray, unsigned n);   // 0x006b6570
    ~Hashtable_6b68f0();
};

// @ 0x006b68f0
Hashtable_6b68f0::~Hashtable_6b68f0()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_6b68f0(mpBucketArray);
}
