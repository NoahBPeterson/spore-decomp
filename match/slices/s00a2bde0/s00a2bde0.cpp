// hashtable destructor (0x00a2bde0): clear() frees the nodes (DoFreeNodes 0xa26f30) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_a2bde0(void* p);   // 0x00f47380

struct Node_a2bde0;
struct Hashtable_a2bde0 {
    uint32_t mHash;                           // +0x00
    Node_a2bde0** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_a2bde0** pBucketArray, unsigned n);   // 0x00a26f30
    ~Hashtable_a2bde0();
};

// @ 0x00a2bde0
Hashtable_a2bde0::~Hashtable_a2bde0()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_a2bde0(mpBucketArray);
}
