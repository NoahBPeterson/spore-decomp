// hashtable::DoRehash (0x006f1980): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_6f1980(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_6f1980(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_6f1980 {
    uint32_t mKey;                            // +0x00
    char     mRest[0x8];
    Node_6f1980* mpNext;                         // +0xc
};
struct Hashtable_6f1980 {
    uint32_t mHash;                           // +0x00
    Node_6f1980** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_6f1980** DoAllocateBuckets(unsigned n) {
        Node_6f1980** const pBucketArray = (Node_6f1980**)EaAlloc_6f1980((n + 1) * sizeof(Node_6f1980*), "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_6f1980*));
        pBucketArray[n] = (Node_6f1980*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_6f1980** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_6f1980(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x006f1980
void Hashtable_6f1980::DoRehash(unsigned nNewBucketCount)
{
    Node_6f1980** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_6f1980* pNode;
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
