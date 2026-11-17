// hashtable destructor (0x006a5f40): clear() frees the nodes (DoFreeNodes 0x42a7b0) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_6a5f40(void* p);   // 0x00f47380

struct Node_6a5f40;
struct Hashtable_6a5f40 {
    uint32_t mHash;                           // +0x00
    Node_6a5f40** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_6a5f40** pBucketArray, unsigned n);   // 0x0042a7b0
    ~Hashtable_6a5f40();
};

// @ 0x006a5f40
Hashtable_6a5f40::~Hashtable_6a5f40()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_6a5f40(mpBucketArray);
}
