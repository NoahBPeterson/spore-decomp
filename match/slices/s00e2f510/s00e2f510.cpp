// hashtable::DoRehash (0x00e2f510): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_e2f510(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_e2f510(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_e2f510 {
    uint32_t mKey;                            // +0x00
    char     mRest[0x10];
    Node_e2f510* mpNext;                         // +0x14
};
struct Hashtable_e2f510 {
    uint32_t mHash;                           // +0x00
    Node_e2f510** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_e2f510** DoAllocateBuckets(unsigned n) {
        Node_e2f510** const pBucketArray = (Node_e2f510**)EaAlloc_e2f510((n + 1) * sizeof(Node_e2f510*), "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_e2f510*));
        pBucketArray[n] = (Node_e2f510*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_e2f510** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_e2f510(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x00e2f510
void Hashtable_e2f510::DoRehash(unsigned nNewBucketCount)
{
    Node_e2f510** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_e2f510* pNode;
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
