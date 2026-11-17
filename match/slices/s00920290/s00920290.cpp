// hashtable::DoRehash (0x00920290): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_920290(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_920290(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_920290 {
    uint32_t mKey;                            // +0x00
    char     mRest[0x8];
    Node_920290* mpNext;                         // +0xc
};
struct Hashtable_920290 {
    uint32_t mHash;                           // +0x00
    Node_920290** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_920290** DoAllocateBuckets(unsigned n) {
        Node_920290** const pBucketArray = (Node_920290**)EaAlloc_920290((n + 1) * sizeof(Node_920290*), "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_920290*));
        pBucketArray[n] = (Node_920290*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_920290** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_920290(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x00920290
void Hashtable_920290::DoRehash(unsigned nNewBucketCount)
{
    Node_920290** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_920290* pNode;
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
