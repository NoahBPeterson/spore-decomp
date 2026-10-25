// src/game/SPGonzago/SPStarManager.cpp -- migrated from slice(s) s013277d0, s0050f8b0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPStarManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s0050f8b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots() { unsigned int s[N]; }
struct T12 { uint32_t a, b, c; };
// ---- items of slice s0050f8b0 end

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
#define ROW(dst, nm, ky, of, f24, f28, f2c, f30, f38)   \
    attr.name   = (const char*)(nm);                     \
    attr.key    = (uint32_t)(ky);                        \
    attr.z18    = 0;                                     \
    attr.z1c    = 0;                                     \
    attr.dflt   = (void*)0x692ca0;                       \
    attr.w24    = (void*)(f24);                          \
    attr.w28    = (void*)(f28);                          \
    attr.w2c    = (void*)(f2c);                          \
    attr.w30    = (void*)(f30);                          \
    attr.offset = (uint32_t)(of);                        \
    attr.w34    = (void*)0xb1fbf0;                       \
    attr.w38    = (void*)(f38);                          \
    *(SimAttr*)(dst) = attr;
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

// @ 0x0050f8b0
T12* UninitRelocate12(T12* first, T12* last, T12* dest)
{
    uint8_t tag = 0;
    (void)tag;
    ScratchSlots<6>();
    T12* d = dest;
    for (T12* p = first; p != last; ++p, ++d) {
        if (d) {
            d->a = p->a;
            d->b = p->b;
            d->c = p->c;
        }
    }
    for (T12* q = first; q != last; ++q) {}
    return d;
}

// @ 0x013277d0
void __cdecl FUN_013277d0(void)
{
    SimAttr attr;
    ROW(0x156cb70, 0x1465750, 0x3d58bf2, 0x70, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156cbac, 0x145bc18, 0x3d58bf1, 0x3c, 0xb6e3a0, 0xac88c0, 0x6930f0, 0x695010, 0xacbba0)
    ROW(0x156cbe8, 0x14665d4, 0x3e95e04, 0x48, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0x57cde0)
    ROW(0x156cc24, 0x14665c8, 0x3d58bf6, 0x4c, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0x57cde0)
    ROW(0x156cc60, 0x1411e88, 0x3d58bf4, 0x60, 0xac87c0, 0xac87f0, 0x694c80, 0x694c10, 0xacbbc0)
    ROW(0x156cc9c, 0x145ca9c, 0x3d58bf3, 0x5c, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156ccd8, 0x14665b4, 0x3d58bf5, 0x74, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xae5720)
    ROW(0x156cd14, 0x14665a4, 0x3d58bf7, 0x58, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156cd50, 0x1466598, 0x3f1389b, 0x54, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156cd8c, 0x1466584, 0x3f1389a, 0x0c, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156cdc8, 0x1466570, 0x3f1389c, 0x18, 0xb26970, 0xb26990, 0xc2e4e0, 0x692fb0, 0xac8050)
    ROW(0x156ce04, 0x1466558, 0x3f1389d, 0x10, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156ce40, 0x1466540, 0x3f1389e, 0x14, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156ce7c, 0x1466534, 0x51a1188, 0xac, 0xbb9cd0, 0xbb9d00, 0x693070, 0x694f80, 0x595a50)
}

// @ 0x01328ee0
void __cdecl FUN_01328ee0(void)
{
    SimAttr attr;
    ROWF(0x156cfe0, 0x14667b8, 0x4e3b373, 0x00, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0)
    ROWF(0x156d01c, 0x14667a8, 0x4e3b37d, 0x04, 0xb6e3a0, 0xac88c0, 0x6930f0, 0x695010, 0xb1fbf0, 0xacbba0)
    ROWF(0x156d058, 0x145ca9c, 0x4e3b37e, 0x28, 0xbb9cd0, 0xbb9d00, 0x693070, 0x694f80, 0xb1fbf0, 0x595a50)
    ROWF(0x156d094, 0x1466798, 0x4e3b37f, 0x12, 0xbb9cd0, 0xbb9d00, 0x693070, 0x694f80, 0xb1fbf0, 0x595a50)
    ROWF(0x156d0d0, 0x1466790, 0x4e3b380, 0x10, 0xbc3270, 0xff05d0, 0x693030, 0x694f40, 0xb1fbf0, 0xbc3470)
    ROWF(0x156d10c, 0x1466788, 0x5c41511, 0x14, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80)
    ROWF(0x156d148, 0x1466778, 0x5d0f859, 0x18, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0)
    ROWF(0x156d184, 0x1465750, 0x5de82a2, 0x1c, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xb1fbf0, 0xae5720)
}
