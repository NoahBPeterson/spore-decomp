// Slice s007e2960: eastl hashtable find for an 8-byte key.  Retail shape: thiscall with a hidden
// sret iterator, `ret 8`; the key and the result iterator are passed by pointer.  The compare functor
// reloads the key each step (a _ReadWriteBarrier inside the walk keeps the hash's loads from being
// hoisted), and the bucket count stays live in a register.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <intrin.h>

typedef unsigned int u32;

// hash_code_base<Key, pair<Key const, T>, use_first<...>, string_hash<Key>, equal_to<Key> >: the three
// empty functors share the first word.
struct HFunctorBase {
    u32 muWord;
    u32 hash(uint64_t k) const { return (u32)k ^ (u32)(k >> 32); }
};

struct HNode {
    uint64_t mKey;     // +0x00
    u32      mnField8; // +0x08
    HNode*   mpNext;   // +0x0c
};

struct HIter {
    HNode*  mpNode;    // +0x00
    HNode** mppBucket; // +0x04
};

struct HTable {
    u32   mCodeBase;         // +0x00
    HNode** mpBucketArray;   // +0x04
    u32   mnBucketCount;     // +0x08
    u32   mnElementCount;    // +0x0c

    void find(HIter* out, const uint64_t* key) const;   // 0x007e2960
};

// @ 0x007e2960
void HTable::find(HIter* out, const uint64_t* key) const
{
    u32 count = mnBucketCount;
    HNode** buckets = mpBucketArray;
    u32 h = ((const HFunctorBase*)this)->hash(*key) % count;
    HNode** pBucket = buckets + h;
    HNode* pNode = *pBucket;
    volatile HIter it;
    if (pNode) {
        do {
            _ReadWriteBarrier();
            if (*key == pNode->mKey) {
                it.mpNode = pNode;
                it.mppBucket = pBucket;
                goto done;
            }
            pNode = pNode->mpNext;
        } while (pNode);
    }
    it.mpNode = buckets[count];
    it.mppBucket = buckets + count;
done:
    out->mpNode = it.mpNode;
    out->mppBucket = it.mppBucket;
}
