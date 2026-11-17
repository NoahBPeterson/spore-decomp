// hashtable destructor (0x006aae00): clear() frees the nodes (DoFreeNodes 0xa39c20) and zeroes the count, then the
// bucket array is freed (0xf47380) unless it is the shared one-bucket array.
#include "game/types.h"

void FreeBuckets_6aae00(void* p);   // 0x00f47380

struct Node_6aae00;
struct Hashtable_6aae00 {
    uint32_t mHash;                           // +0x00
    Node_6aae00** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnElementCount;                  // +0x0c
    void DoFreeNodes(Node_6aae00** pBucketArray, unsigned n);   // 0x00a39c20
    ~Hashtable_6aae00();
};

// @ 0x006aae00
Hashtable_6aae00::~Hashtable_6aae00()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        FreeBuckets_6aae00(mpBucketArray);
}
