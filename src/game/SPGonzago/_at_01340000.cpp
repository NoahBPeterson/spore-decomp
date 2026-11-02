// src/game/SPGonzago/_at_01340000.cpp -- migrated from slice(s) s0133ed00 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_01340000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s0133ed00 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
typedef void (*AttrFn)();
struct Attribute {
    const char* mpName;    // +0x00  attribute name ("mHealth", ...)
    u32         mKey;      // +0x04  hashed property key
    u32         mOffset;   // +0x08  byte offset of the member in the owner
    u32         mUnk0c;    // +0x0c  uninitialised in the original
    u32         mUnk10;    // +0x10  uninitialised in the original
    u32         mUnk14;    // +0x14  uninitialised in the original
    u32         mFlags18;  // +0x18  always 0
    u32         mFlags1c;  // +0x1c  always 0
    AttrFn      mpfn20;    // +0x20  default/offset accessor (0x692ca0)
    AttrFn      mpfn24;    // +0x24  writer/reader A
    AttrFn      mpfn28;    // +0x28  writer A
    AttrFn      mpfn2c;    // +0x2c  parser/reader A
    AttrFn      mpfn30;    // +0x30  parser A
    AttrFn      mpfn34;    // +0x34  init hook (0xb1fbf0)
    AttrFn      mpfn38;    // +0x38  serialiser
};
Attribute s_ufoAttrs[5];              // 0x01576840
#define ATTR(dst, nm, k, off, f0, f1, f2, f3, f4, f5, f6)          \
    do {                                                           \
        Attribute t;                                               \
        t.mpName = (nm);                                           \
        t.mKey = (k);                                              \
        t.mFlags18 = 0;                                            \
        t.mFlags1c = 0;                                            \
        t.mpfn20 = (AttrFn)(f0);                                   \
        t.mpfn24 = (AttrFn)(f1);                                   \
        t.mpfn28 = (AttrFn)(f2);                                   \
        t.mpfn2c = (AttrFn)(f3);                                   \
        t.mpfn30 = (AttrFn)(f4);                                   \
        t.mpfn34 = (AttrFn)(f5);                                   \
        t.mpfn38 = (AttrFn)(f6);                                   \
        t.mOffset = (off);                                         \
        (dst) = t;                                                 \
    } while (0)
// ---- items of slice s0133ed00 end

// @ 0x01347610
void FUN_01347610()
{
    ATTR(s_ufoAttrs[0], "mUFOType", 0x648cfb0, 4,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_ufoAttrs[1], "mPosition", 0x648cfb6, 8,
         0x692ca0, 0xb6e3a0, 0xac88c0, 0x6930f0, 0x695010, 0xb1fbf0, 0xacbba0);
    ATTR(s_ufoAttrs[2], "mHealth", 0x648cfba, 0x14,
         0x692ca0, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80);
    ATTR(s_ufoAttrs[3], "mMaxHealth", 0x648cfbe, 0x18,
         0x692ca0, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80);
    ATTR(s_ufoAttrs[4], "mBomberIndex", 0x648cfc2, 0x1c,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
}
