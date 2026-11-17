// hashtable destructor (0x007ebe40): clear() frees the nodes (DoFreeNodes 0x7eb950) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_7ebe40(void* p);   // 0x00f47380

struct Node_7ebe40;
struct Hashtable_7ebe40 {
    uint32_t mHash;                           // +0x00
    Node_7ebe40** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_7ebe40** pBucketArray, unsigned n);   // 0x007eb950
    ~Hashtable_7ebe40();
};

// @ 0x007ebe40
Hashtable_7ebe40::~Hashtable_7ebe40()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_7ebe40(mpBucketArray);
}
