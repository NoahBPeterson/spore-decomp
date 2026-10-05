// Slice s00711de0 (separate TU): eastl::hash_map<uint32_t, SP::cMaterialInternal>::operator[].
// Kept apart from s00711de0.cpp so that cl's nothrow analysis does not strip the EH frames of
// the accessors in that file (which are byte-exact).
// /O2 /MD /Gy /EHsc /TP /GS-
#include <new>
#include "types.h"

struct MatNode;

// The hashtable find / insert helpers are out of line in the image (0x0070F690 find, 0x00712920
// insertion helper).  Declared here only to give this reconstruction its shape.
void __cdecl HashtableFind(const void* self, const uint32_t* key, void* out);   // 0x0070F690
void __cdecl HashtableInsert(const void* self, void* out, const void* value, uint8_t tag); // 0x00712920

struct MaterialInternal {
    uint8_t mPresent;      // +0x00
    char pad0[3];
    void* mpState;         // +0x04
    char pad1[0x18 - 0x08];
    uint32_t mKey;         // +0x18
};

struct MatMap2 {
    char mData[0x40];
    MaterialInternal& operator[](const uint32_t& key);
};

// @ 0x007129E0
MaterialInternal& MatMap2::operator[](const uint32_t& key)
{
    void* it[2];
    HashtableFind(this, &key, it);
    if (it[0] != 0)
        return *(MaterialInternal*)it[0];
    struct Pair { const uint32_t first; MaterialInternal second; };
    Pair value = { key, MaterialInternal() };
    uint8_t out[12];
    HashtableInsert(this, out, &value, 0);
    return *(MaterialInternal*)*(uint32_t*)out;
}
