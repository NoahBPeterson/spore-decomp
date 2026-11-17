// hashtable::DoRehash (0x0070e7e0): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_70e7e0(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_70e7e0(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_70e7e0 {
    uint32_t mKey;                            // +0x00
    char     mRest[0x4];
    Node_70e7e0* mpNext;                         // +0x8
};
struct Hashtable_70e7e0 {
    uint32_t mHash;                           // +0x00
    Node_70e7e0** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_70e7e0** DoAllocateBuckets(unsigned n) {
        Node_70e7e0** const pBucketArray = (Node_70e7e0**)EaAlloc_70e7e0((n + 1) * sizeof(Node_70e7e0*), "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_70e7e0*));
        pBucketArray[n] = (Node_70e7e0*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_70e7e0** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_70e7e0(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x0070e7e0
void Hashtable_70e7e0::DoRehash(unsigned nNewBucketCount)
{
    Node_70e7e0** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_70e7e0* pNode;
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
