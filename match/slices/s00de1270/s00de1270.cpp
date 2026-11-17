// hashtable::DoRehash (0x00de1270): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_de1270(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_de1270(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_de1270 {
    uint32_t mKey;                            // +0x00
    char     mRest[0x14];
    Node_de1270* mpNext;                         // +0x18
};
struct Hashtable_de1270 {
    uint32_t mHash;                           // +0x00
    Node_de1270** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_de1270** DoAllocateBuckets(unsigned n) {
        Node_de1270** const pBucketArray = (Node_de1270**)EaAlloc_de1270((n + 1) * sizeof(Node_de1270*), "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_de1270*));
        pBucketArray[n] = (Node_de1270*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_de1270** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_de1270(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x00de1270
void Hashtable_de1270::DoRehash(unsigned nNewBucketCount)
{
    Node_de1270** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_de1270* pNode;
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
