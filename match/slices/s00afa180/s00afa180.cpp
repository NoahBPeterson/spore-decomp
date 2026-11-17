// hashtable::DoRehash (0x00afa180): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_afa180(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_afa180(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_afa180 {
    uint32_t mKey;                            // +0x00
    char     mRest[0x1c];
    Node_afa180* mpNext;                         // +0x20
};
struct Hashtable_afa180 {
    uint32_t mHash;                           // +0x00
    Node_afa180** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_afa180** DoAllocateBuckets(unsigned n) {
        Node_afa180** const pBucketArray = (Node_afa180**)EaAlloc_afa180((n + 1) * sizeof(Node_afa180*), "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_afa180*));
        pBucketArray[n] = (Node_afa180*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_afa180** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_afa180(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x00afa180
void Hashtable_afa180::DoRehash(unsigned nNewBucketCount)
{
    Node_afa180** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_afa180* pNode;
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
