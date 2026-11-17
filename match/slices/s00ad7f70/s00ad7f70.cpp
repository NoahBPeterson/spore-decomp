// hashtable::DoRehash (0x00ad7f70): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_ad7f70(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_ad7f70(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_ad7f70 {
    uint32_t mKey;                            // +0x00
    char     mRest[0x34];
    Node_ad7f70* mpNext;                         // +0x38
};
struct Hashtable_ad7f70 {
    uint32_t mHash;                           // +0x00
    Node_ad7f70** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_ad7f70** DoAllocateBuckets(unsigned n) {
        Node_ad7f70** const pBucketArray = (Node_ad7f70**)EaAlloc_ad7f70((n + 1) * sizeof(Node_ad7f70*), "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_ad7f70*));
        pBucketArray[n] = (Node_ad7f70*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_ad7f70** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_ad7f70(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x00ad7f70
void Hashtable_ad7f70::DoRehash(unsigned nNewBucketCount)
{
    Node_ad7f70** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_ad7f70* pNode;
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
