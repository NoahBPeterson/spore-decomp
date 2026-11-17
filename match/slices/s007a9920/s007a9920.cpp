// hashtable::DoRehash (0x007a9920): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_7a9920(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_7a9920(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_7a9920 {
    uint32_t mKey;                            // +0x00
    uint32_t mKey4;                           // +0x04
    uint32_t mKey8;                           // +0x08
    char     mRest[0x4];
    Node_7a9920* mpNext;                         // +0x10
};
struct Hashtable_7a9920 {
    uint32_t mHash;                           // +0x00
    Node_7a9920** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_7a9920** DoAllocateBuckets(unsigned n) {
        Node_7a9920** const pBucketArray = (Node_7a9920**)EaAlloc_7a9920((n + 1) * sizeof(Node_7a9920*), "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_7a9920*));
        pBucketArray[n] = (Node_7a9920*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_7a9920** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_7a9920(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x007a9920
void Hashtable_7a9920::DoRehash(unsigned nNewBucketCount)
{
    Node_7a9920** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_7a9920* pNode;
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
