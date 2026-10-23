// Slice s0137a490 — global property-table initialisers.
// Each function fills a static array of 0x28-byte property descriptors:
//   +0x00  name hash (SP::sHash)
//   +0x04  type code (4, 8, 0xc, 0x10, 0x14, 0xffffffff)
//   +0x08  zero
//   +0x0c  value 0   (through the 4-byte pass-through helper)
//   +0x10  value 1
//   +0x14  index
//   +0x18  default value
//   +0x1c  zero / small code
//   +0x20  zero
//   +0x24  zero  (left untouched on the final record)
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#pragma once

typedef unsigned int u32;

struct PropDesc
{
    u32 name;    // +0x00  sHash of the property name
    u32 type;    // +0x04
    u32 unk08;   // +0x08
    u32 val0;    // +0x0c
    u32 val1;    // +0x10
    u32 index;   // +0x14
    u32 defVal;  // +0x18
    u32 unk1C;   // +0x1c
    u32 unk20;   // +0x20
    u32 unk24;   // +0x24
};

extern "C" {

// 0x00e4a9d0 — SP::sHash(const char*).  Returns 0 for a null name.
u32 SP_sHash(const char* name);

// 0x00e4a9c0 — 4-byte pass-through used to build the value words.  The int
// and float overloads were identical and folded together (ICF).
u32 PropValI(u32 v);
u32 PropValF(float v);

extern PropDesc g_15a674c[2];   // 0x015a674c  "color" style descriptor
extern PropDesc g_16b17b4[3];   // 0x016b17b4
extern PropDesc g_16b1d04[7];   // 0x016b1d04
extern PropDesc g_16b3014[7];   // 0x016b3014
extern PropDesc g_16b2b3c[7];   // 0x016b2b3c
extern PropDesc g_16b2a24[7];   // 0x016b2a24
extern PropDesc g_16b24d4[7];   // 0x016b24d4

// 0x013eb1bc — shared -1.0f literal in the original image.
extern const float g_negOne;

}
