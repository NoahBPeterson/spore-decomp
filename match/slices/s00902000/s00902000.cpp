// hashtable::DoRehash (0x00902000): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_902000(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_902000(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_902000 {
    uint32_t mKey;                            // +0x00
    char     mRest[0x4];
    Node_902000* mpNext;                         // +0x8
};
struct Hashtable_902000 {
    uint32_t mHash;                           // +0x00
    Node_902000** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_902000** DoAllocateBuckets(unsigned n) {
        Node_902000** const pBucketArray = (Node_902000**)EaAlloc_902000((n + 1) * sizeof(Node_902000*), "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_902000*));
        pBucketArray[n] = (Node_902000*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_902000** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_902000(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x00902000
void Hashtable_902000::DoRehash(unsigned nNewBucketCount)
{
    Node_902000** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_902000* pNode;
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
