// src/game/SPBake/SPEditorResource.cpp -- migrated from slice(s) s00525360, s004bafc0 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorResource.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00525360 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct sp_vector_allocator {
    uint32_t mFlags[2];
    void* allocate(uint32_t n, uint32_t align, uint32_t ofs);
};
template <typename T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    ~VectorBase();      // declined inline in the original
};
struct VectorU32 : VectorBase<uint32_t> {
    typedef uint32_t size_type;
    bool empty() const;
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    uint32_t* erase(uint32_t* first, uint32_t* last);     // 0x004769b0
    void clear() { erase(mpBegin, mpEnd); }
};
// ---- items of slice s00525360 end

// @ 0x004bbd20
uint32_t GetTypeForCategory(uint32_t code, uint8_t useSpecial)
{
    if (useSpecial && code == 0x8a)
        return 0x366a930d;
    switch (code) {
    case 0x61: return 0x3d97a8e4;
    case 0x62: return 0x2b978c46;
    case 0x63: return 0x2399be55;
    case 0x64: return 0x24682294;
    case 0x65: return 0x476a98c7;
    case 0x66: return 0x438f6347;
    case 0xc0: return 0x04f684a4;
    default: return (uint32_t)-1;
    }
}

// @ 0x00526430
bool VectorU32::empty() const
{
    return mpBegin == mpEnd;
}
