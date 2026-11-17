// hashtable destructor (0x006aadd0): clear() frees the nodes (DoFreeNodes 0x6a85b0) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_6aadd0(void* p);   // 0x00f47380

struct Node_6aadd0;
struct Hashtable_6aadd0 {
    uint32_t mHash;                           // +0x00
    Node_6aadd0** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_6aadd0** pBucketArray, unsigned n);   // 0x006a85b0
    ~Hashtable_6aadd0();
};

// @ 0x006aadd0
Hashtable_6aadd0::~Hashtable_6aadd0()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_6aadd0(mpBucketArray);
}
