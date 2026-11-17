// hashtable::DoRehash (0x0080a540): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_80a540(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_80a540(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_80a540 {
    uint32_t mKey;                            // +0x00
    uint32_t mKey4;                           // +0x04
    uint32_t mKey8;                           // +0x08
    char     mRest[0x24];
    Node_80a540* mpNext;                         // +0x30
};
struct Hashtable_80a540 {
    uint32_t mHash;                           // +0x00
    Node_80a540** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_80a540** DoAllocateBuckets(unsigned n) {
        Node_80a540** const pBucketArray = (Node_80a540**)EaAlloc_80a540((n + 1) * sizeof(Node_80a540*), "UI", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_80a540*));
        pBucketArray[n] = (Node_80a540*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_80a540** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_80a540(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x0080a540
void Hashtable_80a540::DoRehash(unsigned nNewBucketCount)
{
    Node_80a540** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_80a540* pNode;
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
