// hashtable::DoRehash (0x005f7cf0): allocate a cleared bucket array (with the end sentinel), move every node into its
// new bucket (key % nNewBucketCount), free the old array and switch to the new one.
#include "game/types.h"

void* EaAlloc_5f7cf0(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void  FreeBuckets_5f7cf0(void* p);                       // 0x00f47380
extern "C" void* __cdecl memset(void* dst, int c, size_t n);

struct Node_5f7cf0 {
    uint32_t mKey;                            // +0x00
    uint32_t mKey4;                           // +0x04
    uint32_t mKey8;                           // +0x08
    char     mRest[0xc];
    Node_5f7cf0* mpNext;                         // +0x18
};
struct Hashtable_5f7cf0 {
    uint32_t mHash;                           // +0x00
    Node_5f7cf0** mpBucketArray;                 // +0x04
    unsigned mnBucketCount;                   // +0x08
    Node_5f7cf0** DoAllocateBuckets(unsigned n) {
        Node_5f7cf0** const pBucketArray = (Node_5f7cf0**)EaAlloc_5f7cf0((n + 1) * sizeof(Node_5f7cf0*), "Editor", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memset(pBucketArray, 0, n * sizeof(Node_5f7cf0*));
        pBucketArray[n] = (Node_5f7cf0*)~(size_t)0;
        return pBucketArray;
    }
    void DoFreeBuckets(Node_5f7cf0** pBucketArray, unsigned n) {
        if (n > 1)
            FreeBuckets_5f7cf0(pBucketArray);
    }
    void DoRehash(unsigned nNewBucketCount);
};

// @ 0x005f7cf0
void Hashtable_5f7cf0::DoRehash(unsigned nNewBucketCount)
{
    Node_5f7cf0** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    for (unsigned i = 0; i < mnBucketCount; ++i) {
        Node_5f7cf0* pNode;
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
