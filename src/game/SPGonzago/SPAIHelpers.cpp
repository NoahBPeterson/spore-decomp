// src/game/SPGonzago/SPAIHelpers.cpp -- migrated from slice(s) s013277d0, s00422950 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAIHelpers.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Variant.h"

// ---- items of slice s00422950 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec12 {
    uint32_t x, y, z;
};
struct Variant {
    uint32_t data[4];
    uint16_t flags;  // bit1: locked to type, bit2: needs reset
    uint16_t type;
    void Reset(int);                                                            // 0x0093DB80
    void SetSlow(int type, int, const void* v, int size, int);                   // 0x0093DD80
    Variant* SetChar(const char* v);
    Variant* SetU32(const uint32_t* v);
    Variant* SetVec12(const Vec12* v);
};
// ---- items of slice s00422950 end

// ---- items of slice s013277d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SimAttr {
    const char* name;    // +0x00
    uint32_t    key;     // +0x04
    uint32_t    offset;  // +0x08
    uint32_t    r0c;     // +0x0c  (never assigned)
    uint32_t    r10;     // +0x10  (never assigned)
    uint32_t    r14;     // +0x14  (never assigned)
    uint32_t    z18;     // +0x18
    uint32_t    z1c;     // +0x1c
    void*       dflt;    // +0x20  Simulator::Attribute::DefaultOffset (0x692ca0)
    void*       w24;     // +0x24
    void*       w28;     // +0x28
    void*       w2c;     // +0x2c
    void*       w30;     // +0x30
    void*       w34;     // +0x34  0xb1fbf0 UTFWin::Window::Initialize
    void*       w38;     // +0x38
};
#define ROWF(dst, nm, ky, of, f24, f28, f2c, f30, f34, f38) \
    attr.name   = (const char*)(nm);                         \
    attr.key    = (uint32_t)(ky);                            \
    attr.z18    = 0;                                         \
    attr.z1c    = 0;                                         \
    attr.dflt   = (void*)0x692ca0;                           \
    attr.w24    = (void*)(f24);                              \
    attr.w28    = (void*)(f28);                              \
    attr.w2c    = (void*)(f2c);                              \
    attr.w30    = (void*)(f30);                              \
    attr.offset = (uint32_t)(of);                            \
    attr.w34    = (void*)(f34);                              \
    attr.w38    = (void*)(f38);                              \
    *(SimAttr*)(dst) = attr;
// ---- items of slice s013277d0 end

// @ 0x00422f40
Variant* Variant::SetVec12(const Vec12* v)
{
    if (flags & 4)
        Reset(1);
    if (1 && (!(flags & 2) || type == 0x20)) {
        *(Vec12*)this = *v;
        type = 0x20;
        flags = flags & 2;
    } else {
        SetSlow(0x20, 0, v, 12, 1);
    }
    return this;
}

// @ 0x01329420
void __cdecl FUN_01329420(void)
{
    SimAttr attr;
    ROWF(0x156d2a8, 0x14665d4, 0x4bfec52, 0x00, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0)
    ROWF(0x156d2e4, 0x145fcb4, 0x57a4efc, 0x08, 0xae3470, 0xae3490, 0xc2e4e0, 0x692fb0, 0xae3310, 0xac8050)
    ROWF(0x156d320, 0x14669f8, 0x4bfec53, 0x28, 0xbca770, 0xbca960, 0xc2e4e0, 0x692fb0, 0xbca7e0, 0xac8050)
    ROWF(0x156d35c, 0x14669ec, 0x4bfec54, 0x39, 0xbca2e0, 0xbca2e0, 0xc2e4e0, 0x692fb0, 0xb1fbf0, 0xac8050)
    ROWF(0x156d398, 0x14669e0, 0x4bfec55, 0x4d, 0xbca2e0, 0xbca2e0, 0xc2e4e0, 0x692fb0, 0xb1fbf0, 0xac8050)
    ROWF(0x156d3d4, 0x14669d4, 0x4bfec56, 0x61, 0xbca2e0, 0xbca2e0, 0xc2e4e0, 0x692fb0, 0xb1fbf0, 0xac8050)
    ROWF(0x156d410, 0x14669c8, 0x4bfec57, 0x75, 0xbca2e0, 0xbca2e0, 0xc2e4e0, 0x692fb0, 0xb1fbf0, 0xac8050)
    ROWF(0x156d44c, 0x14669bc, 0x4bfec58, 0x38, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00)
    ROWF(0x156d488, 0x14669a8, 0x4bfec59, 0x2c, 0xb6e3a0, 0xac88c0, 0x6930f0, 0x695010, 0xb1fbf0, 0xacbba0)
}
