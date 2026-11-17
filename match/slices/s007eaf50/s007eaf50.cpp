// hashtable::DoRehash (0x007eaf50): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_7eaf50(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_7eaf50(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_7eaf50 {
    uint32_t mKey;                            // +0x00
    char     mRest[0xc];
    Node_7eaf50* mpNext;                         // +0x10
};
struct Hashtable_7eaf50 {
    uint32_t mHash;                           // +0x00
    Node_7eaf50** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_7eaf50** DoAllocateBuckets(unsigned n) {
        Node_7eaf50** const pBucketArray = (Node_7eaf50**)EaAlloc_7eaf50((n + 1) * sizeof(Node_7eaf50*), "App", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_7eaf50*));
        pBucketArray[n] = (Node_7eaf50*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_7eaf50** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_7eaf50(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x007eaf50
void Hashtable_7eaf50::DoRehash(unsigned nNewBucketCount)
{
    Node_7eaf50** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_7eaf50* pNode;
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
