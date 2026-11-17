// hashtable::DoRehash (0x00998870): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_998870(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_998870(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_998870 {
    uint32_t mKey;                            // +0x00
    uint32_t mKey4;                           // +0x04
    uint32_t mKey8;                           // +0x08
    char     mRest[0x4];
    Node_998870* mpNext;                         // +0x10
};
struct Hashtable_998870 {
    uint32_t mHash;                           // +0x00
    Node_998870** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_998870** DoAllocateBuckets(unsigned n) {
        Node_998870** const pBucketArray = (Node_998870**)EaAlloc_998870((n + 1) * sizeof(Node_998870*), "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_998870*));
        pBucketArray[n] = (Node_998870*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_998870** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_998870(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x00998870
void Hashtable_998870::DoRehash(unsigned nNewBucketCount)
{
    Node_998870** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_998870* pNode;
        while ((pNode = mpBucketArray[i]) != 0) {
            const unsigned nBucketIndex = (pNode->mKey8 ^ pNode->mKey) % nNewBucketCount;
            mpBucketArray[i] = pNode->mpNext;
            pNode->mpNext = pBucketArray[nBucketIndex];
            pBucketArray[nBucketIndex] = pNode;
        }
    }

    DoFreeBuckets(mpBucketArray, mnBucketCount);
    mnBucketCount = nNewBucketCount;
    mpBucketArray = pBucketArray;
}
