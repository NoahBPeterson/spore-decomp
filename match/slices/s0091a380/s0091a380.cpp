// hashtable::DoRehash (0x0091a380): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_91a380(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_91a380(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_91a380 {
    uint32_t mKey;                            // +0x00
    char     mRest[0x44];
    Node_91a380* mpNext;                         // +0x48
};
struct Hashtable_91a380 {
    uint32_t mHash;                           // +0x00
    Node_91a380** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_91a380** DoAllocateBuckets(unsigned n) {
        Node_91a380** const pBucketArray = (Node_91a380**)EaAlloc_91a380((n + 1) * sizeof(Node_91a380*), "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_91a380*));
        pBucketArray[n] = (Node_91a380*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_91a380** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_91a380(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x0091a380
void Hashtable_91a380::DoRehash(unsigned nNewBucketCount)
{
    Node_91a380** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_91a380* pNode;
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
