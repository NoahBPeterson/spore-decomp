// hashtable::DoRehash (0x00c29710): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_c29710(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_c29710(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_c29710 {
    uint32_t mKey;                            // +0x00
    char     mRest[0x820];
    Node_c29710* mpNext;                         // +0x824
};
struct Hashtable_c29710 {
    uint32_t mHash;                           // +0x00
    Node_c29710** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_c29710** DoAllocateBuckets(unsigned n) {
        Node_c29710** const pBucketArray = (Node_c29710**)EaAlloc_c29710((n + 1) * sizeof(Node_c29710*), "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_c29710*));
        pBucketArray[n] = (Node_c29710*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_c29710** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_c29710(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x00c29710
void Hashtable_c29710::DoRehash(unsigned nNewBucketCount)
{
    Node_c29710** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_c29710* pNode;
        while ((pNode = mpBucketArray[i]) != 0) {
            const unsigned nBucketIndex = pNode->mKey % nNewBucketCount;
            mpBucketArray[i] = pNode->mpNext;
            pNode->mpNext = pBucketArray[nBucketIndex];
            pBucketArray[nBucketIndex] = pNode;
        }
    }

    DoFreeBuckets(mpBucketArray, mnBucketCount);
    mnBucketCount = nNewBucketCount;
    mpBucketArray = pBucketArray;
}
