// hashtable destructor (0x008471d0): clear() frees the nodes (DoFreeNodes 0x846630) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_8471d0(void* p);   // 0x00f47380

struct Node_8471d0;
struct Hashtable_8471d0 {
    uint32_t mHash;                           // +0x00
    Node_8471d0** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_8471d0** pBucketArray, unsigned n);   // 0x00846630
    ~Hashtable_8471d0();
};

// @ 0x008471d0
Hashtable_8471d0::~Hashtable_8471d0()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_8471d0(mpBucketArray);
}
