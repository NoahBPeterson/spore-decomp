// hashtable::DoRehash (0x005d6740): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_5d6740(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_5d6740(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_5d6740 {
    uint32_t mKey;                            // +0x00
    char     mRest[0x4];
    Node_5d6740* mpNext;                         // +0x8
};
struct Hashtable_5d6740 {
    uint32_t mHash;                           // +0x00
    Node_5d6740** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_5d6740** DoAllocateBuckets(unsigned n) {
        Node_5d6740** const pBucketArray = (Node_5d6740**)EaAlloc_5d6740((n + 1) * sizeof(Node_5d6740*), "Editor", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_5d6740*));
        pBucketArray[n] = (Node_5d6740*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_5d6740** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_5d6740(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x005d6740
void Hashtable_5d6740::DoRehash(unsigned nNewBucketCount)
{
    Node_5d6740** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_5d6740* pNode;
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
