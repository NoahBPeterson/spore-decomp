// hashtable destructor (0x00711350): clear() frees the nodes (DoFreeNodes 0x70ff50) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_711350(void* p);   // 0x00f47380

struct Node_711350;
struct Hashtable_711350 {
    uint32_t mHash;                           // +0x00
    Node_711350** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_711350** pBucketArray, unsigned n);   // 0x0070ff50
    ~Hashtable_711350();
};

// @ 0x00711350
Hashtable_711350::~Hashtable_711350()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_711350(mpBucketArray);
}
