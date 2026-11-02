// src/game/SPGonzago/SPEllipticalOrbit.cpp -- migrated from slice(s) s0138d560 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPEllipticalOrbit.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s0138d560 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PropertyDesc {
    unsigned int name;   // +0x00  const char* (VA)
    unsigned int hash;   // +0x04
    unsigned int size;   // +0x08  byte size of the value
    unsigned int unk0c;  // +0x0c  uninitialised in the original
    unsigned int unk10;  // +0x10  uninitialised in the original
    unsigned int unk14;  // +0x14  uninitialised in the original
    unsigned int fn0;    // +0x18
    unsigned int fn1;    // +0x1c
    unsigned int fn2;    // +0x20
    unsigned int fn3;    // +0x24
    unsigned int fn4;    // +0x28
    unsigned int fn5;    // +0x2c
    unsigned int fn6;    // +0x30
    unsigned int fn7;    // +0x34
    unsigned int fn8;    // +0x38
};
// ---- items of slice s0138d560 end

// @ 0x01396110
void init_15b4568()
{
    static const PropertyDesc desc[5] = {
        { 0x1494424, 0x374176b, 0x00,  0,0,0, 0,0,
          0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00 },
        { 0x1494414, 0x3741796, 0x04,  0,0,0, 0,0,
          0x692ca0, 0xb6e3a0, 0xac88c0, 0x6930f0, 0x695010, 0xb1fbf0, 0xacbba0 },
        { 0x1494404, 0x3741811, 0x10,  0,0,0, 0,0,
          0x692ca0, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80 },
        { 0x14943f8, 0x374181f, 0x14,  0,0,0, 0,0,
          0x692ca0, 0xb6e3a0, 0xac88c0, 0x6930f0, 0x695010, 0xb1fbf0, 0xacbba0 },
        { 0x14943f0, 0x374182d, 0x20,  0,0,0, 0,0,
          0x692ca0, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80 },
    };
    PropertyDesc* dst = (PropertyDesc*)0x15b4568;
    for (int i = 0; i < 5; ++i)
        dst[i] = desc[i];
}
