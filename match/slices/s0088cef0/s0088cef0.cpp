// Slice s0088cef0 -- EA::Text string-keyed hash map: look up a key given as a bare
// pointer (find_as).  Hashes the key characters with FNV-1, modulos by the bucket
// count and walks the bucket chain through the shared node-compare helper.
// Flags: /O2 /MD /GS- /GR- /TP /arch:SSE /fp:fast
#include "types.h"

struct Str16 {
    const uint16_t* mpBegin;
    const uint16_t* mpEnd;
    const uint16_t* mpCapacity;
    const uint16_t* mpAlloc;
};

extern "C" void* __cdecl FUN_0088c720(void* bucketHead, const Str16& keyRef, unsigned hash);

struct HashIter {
    void*  mpNode;
    void** mpBucket;

    HashIter() : mpNode(0), mpBucket(0) {}
    HashIter(void* node, void** bucket) : mpNode(node), mpBucket(bucket) {}
};

struct StringKeyMap {
    char      pad0[4];
    void**    mpBucketArray;      // +0x04
    unsigned  mnBucketCount;      // +0x08

    HashIter find_as(const Str16& key) const;
};

// @ 0x0088cef0
HashIter StringKeyMap::find_as(const Str16& key) const
{
    unsigned hash = 0x811c9dc5;
    const uint16_t* p = key.mpBegin;
    unsigned c = *p;
    while (c) {
        hash *= 0x1000193;
        ++p;
        hash ^= c;
        c = *p;
    }

    unsigned count = mnBucketCount;
    void** array = mpBucketArray;
    unsigned bucket = hash % count;
    void** slot = &array[bucket];
    void* node = FUN_0088c720(array[bucket], key, hash);

    if (node)
        return HashIter(node, slot);
    return HashIter(array[count], &array[count]);
}
