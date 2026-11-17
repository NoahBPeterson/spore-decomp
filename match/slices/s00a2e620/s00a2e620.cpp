// hashtable destructor (0x00a2e620): clear() frees the nodes (DoFreeNodes 0xb6fdf0) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_a2e620(void* p);   // 0x00f47380

struct Node_a2e620;
struct Hashtable_a2e620 {
    uint32_t mHash;                           // +0x00
    Node_a2e620** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_a2e620** pBucketArray, unsigned n);   // 0x00b6fdf0
    ~Hashtable_a2e620();
};

// @ 0x00a2e620
Hashtable_a2e620::~Hashtable_a2e620()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_a2e620(mpBucketArray);
}
