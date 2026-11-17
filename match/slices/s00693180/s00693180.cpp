// hashtable::DoRehash (0x00693180): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_693180(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_693180(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_693180 {
    uint32_t mKey;                            // +0x00
    char     mRest[0x4];
    Node_693180* mpNext;                         // +0x8
};
struct Hashtable_693180 {
    uint32_t mHash;                           // +0x00
    Node_693180** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_693180** DoAllocateBuckets(unsigned n) {
        Node_693180** const pBucketArray = (Node_693180**)EaAlloc_693180((n + 1) * sizeof(Node_693180*), "App", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_693180*));
        pBucketArray[n] = (Node_693180*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_693180** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_693180(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x00693180
void Hashtable_693180::DoRehash(unsigned nNewBucketCount)
{
    Node_693180** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_693180* pNode;
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
