// Slice s00711de0 (separate TU): eastl::hash_map<uint32_t, SP::cMaterialInternal>::operator[].
// Kept apart from s00711de0.cpp so that cl's nothrow analysis does not strip the EH frames of
// the accessors in that file (which are byte-exact).
// /O2 /MD /Gy /EHsc /TP /GS-
#include <new>
#include "types.h"

void operator delete[](void* p);

// eastl fixed_vector<void*,16>: the vector base holds the three cursors, the fixed_vector adds an
// allocator word, the address of the inline buffer and the 4-slot inline buffer itself.
struct VecBase {
    void* mpBegin;         // +0x00
    void* mpEnd;           // +0x04
    void* mpCapacity;      // +0x08
    void DestroyRange(void** first, void** last);       // 0x0070F520
};

struct TailVec {                        // 0x28
    void*    mpBegin;       // +0x00
    void*    mpEnd;         // +0x04
    void*    mpCapacity;    // +0x08
    uint32_t mAllocator;    // +0x0c
    void*    mpLocal;       // +0x10 (address of mBuffer)
    uint32_t mPad14;        // +0x14
    char     mBuffer[16];   // +0x18
};

struct MaterialInternal {               // SP::cMaterialInternal (0x48)
    uint8_t  mnFlags;       // +0x00
    char     pad0[0x14 - 1];
    int32_t  mnRefCount;    // +0x14
    uint32_t mnId;          // +0x18
    uint32_t mnExternalId;  // +0x1c
    TailVec  mTextures;     // +0x20
};

struct State2850 {                      // hashtable node value: pair<const uint32_t, cMaterialInternal> (0x4c)
    uint32_t mKey;                      // +0x00
    MaterialInternal mValue;            // +0x04
    State2850* CopyFrom2(const State2850& a, const State2850& b);   // 0x00712850
};

struct HashTable {                      // eastl::hashtable header
    uint32_t  mFunctors;      // +0x00
    void**    mpBucketArray;  // +0x04
    uint32_t  mnBucketCount;  // +0x08
    uint32_t  mnElementCount; // +0x0c
};

// The out-of-line hashtable find for this map (see synth/eastl_hashtable_find_u32).
struct Hashtable_0070f690 {
    struct iterator {
        void*  mpNode;
        void** mpBucket;
        iterator() : mpNode(0), mpBucket(0) {}
        iterator(void* p, void** b) : mpNode(p), mpBucket(b) {}
    };
    iterator find(const uint32_t& key);                 // 0x0070F690
};

// The out-of-line node-insertion helper (thiscall: ecx = table, 3 stack arguments).
typedef void (__thiscall *InsertFn)(void* self, void* out, const void* value, uint32_t tag);
#define FUN_00712920 ((InsertFn)0x00712920)

struct MatMap2 : HashTable {
    MaterialInternal& operator[](const uint32_t& key);
};

// @ 0x007129E0
MaterialInternal& MatMap2::operator[](const uint32_t& key)
{
    Hashtable_0070f690* table = (Hashtable_0070f690*)this;
    Hashtable_0070f690::iterator it = table->find(key);

    void**   buckets = mpBucketArray;
    uint32_t count   = mnBucketCount;
    if (it.mpNode != *(void**)((char*)buckets + (size_t)count * 4))
        return *(MaterialInternal*)((char*)it.mpNode + 4);

    // Build the default cMaterialInternal (empty inline texture vector) and the node value from
    // the key, then insert it and tear the two temporaries down again.
    MaterialInternal def;
    def.mnFlags = 0;
    def.mnRefCount = 1;
    def.mnId = 0xffffffffu;
    def.mnExternalId = 0;
    def.mTextures.mpBegin = def.mTextures.mBuffer;
    def.mTextures.mpEnd = def.mTextures.mBuffer;
    def.mTextures.mpCapacity = def.mTextures.mBuffer + 16;
    def.mTextures.mpLocal = def.mTextures.mBuffer;

    State2850 value;
    value.CopyFrom2(*(const State2850*)&key, *(const State2850*)&def);

    uint32_t tag = 0;
    FUN_00712920(this, &it, &value, tag);
    MaterialInternal& result = *(MaterialInternal*)((char*)it.mpNode + 4);

    ((VecBase*)&value.mValue.mTextures)->DestroyRange(
        (void**)value.mValue.mTextures.mpBegin, (void**)value.mValue.mTextures.mpEnd);
    if (value.mValue.mTextures.mpBegin != 0 &&
        value.mValue.mTextures.mpBegin != value.mValue.mTextures.mpLocal)
        operator delete[](value.mValue.mTextures.mpBegin);

    ((VecBase*)&def.mTextures)->DestroyRange(
        (void**)def.mTextures.mpBegin, (void**)def.mTextures.mpEnd);
    if (def.mTextures.mpBegin != 0 && def.mTextures.mpBegin != def.mTextures.mpLocal)
        operator delete[](def.mTextures.mpBegin);

    return result;
}
