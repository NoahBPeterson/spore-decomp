// hashtable destructor (0x00711320): clear() frees the nodes (DoFreeNodes 0x70fd00) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_711320(void* p);   // 0x00f47380

struct Node_711320;
struct Hashtable_711320 {
    uint32_t mHash;                           // +0x00
    Node_711320** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_711320** pBucketArray, unsigned n);   // 0x0070fd00
    ~Hashtable_711320();
};

// @ 0x00711320
Hashtable_711320::~Hashtable_711320()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_711320(mpBucketArray);
}
