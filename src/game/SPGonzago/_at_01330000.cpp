// src/game/SPGonzago/_at_01330000.cpp -- migrated from slice(s) s0133ed00, s01339640, s01335f70 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_01330000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern char g_168dc10[];   // 0x0168dc10  attribute holder #1
extern char g_168dc54[];   // 0x0168dc54  attribute holder #2
#include <stdlib.h>
#include <float.h>

// ---- items of slice s01335f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl FUN_00c22e30(void);                       // 0x00c22e30
void  __cdecl FUN_013c35b0(void);                       // 0x013c35b0  atexit callback
struct MCFill {
    void f_00bc9e30(float maxValue, int a, int b, void* fn, const char* name);  // 0x00bc9e30
};
extern char g_168dc10[];   // 0x0168dc10  attribute holder #1
extern char g_168dc54[];   // 0x0168dc54  attribute holder #2
// ---- items of slice s01335f70 end

// ---- items of slice s01339640 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void cStringCtor();                               // 0x006b5060
extern "C" void StaticStringDtor();                          // 0x013c3a20
extern "C" int atexit(void (__cdecl*)());                    // 0x011e07ef
namespace SP {
struct cString_s0133_9640 {
    uint32_t mData[5];                                       // 0x14 bytes
};
}
namespace SP {
extern cString_s0133_9640 gStringTable[10];                             // 0x0168ef48
}
// ---- items of slice s01339640 end

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
Attribute s_creatureStateAttrs[5];    // 0x01575468
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

// @ 0x01335f70
void FUN_01335f70(void)
{
    ((MCFill*)&g_168dc10)->f_00bc9e30(FLT_MAX, 0, 0, (void*)&FUN_00c22e30, "GiftImmunity");
    ((MCFill*)&g_168dc54)->f_00bc9e30(FLT_MAX, 0, 0, (void*)&FUN_00c22e30, "MildGiftImmunity");
    atexit(&FUN_013c35b0);
}

// @ 0x0133b9f0
void StaticStringInit()
{
    SP::cString_s0133_9640* p = SP::gStringTable;
    int n = 9;
    do {
        ((void (__thiscall*)(void*))cStringCtor)(p);
        ++p;
        --n;
    } while (n >= 0);
    atexit(StaticStringDtor);
}

// @ 0x0133ed00
void FUN_0133ed00()
{
    ATTR(s_creatureStateAttrs[0], "mChangeArchetypeState", 0x3385389d, 0x1f0,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_creatureStateAttrs[1], "mProgressSoFar", 0x3385389e, 0x1fc,
         0x692ca0, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0);
    ATTR(s_creatureStateAttrs[2], "mChangeArchetypeTo", 0x3385389f, 0x1f4,
         0x692ca0, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0);
    ATTR(s_creatureStateAttrs[3], "mNumTotalActions", 0x338538a0, 0x1f8,
         0x692ca0, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0);
    ATTR(s_creatureStateAttrs[4], "mKeyHistory", 0x338538a1, 0x200,
         0x692ca0, 0xb04e00, 0xc761c0, 0xc2e4e0, 0x692fb0, 0xb1fbf0, 0xeafe40);
}
