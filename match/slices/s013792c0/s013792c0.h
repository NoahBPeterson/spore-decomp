// Slice s013792c0 — global property-table initialisers.
// Each function fills a static array of 0x28-byte property descriptors:
//   +0x00  name hash (SP::sHash)
//   +0x04  small code / flags
//   +0x08  small code / flags
//   +0x0c  value 0   (through the 4-byte pass-through helper)
//   +0x10  value 1
//   +0x14  index / flags
//   +0x18  default value
//   +0x1c  small code / flags
//   +0x20  small code / pointer
//   +0x24  name pointer (fed to the next row's sHash; untouched on the terminator)
// Every table ends with a terminator row written only up to +0x20 (the +0x24
// word is left untouched), so it is modelled as the last array element and the
// last field is simply never assigned.
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#pragma once

typedef unsigned int u32;

struct PropDesc
{
    u32 hash;   // +0x00  sHash of the row's name
    u32 f04;    // +0x04
    u32 f08;    // +0x08
    u32 f0c;    // +0x0c  value 0
    u32 f10;    // +0x10  value 1
    u32 f14;    // +0x14
    u32 f18;    // +0x18  default value
    u32 f1c;    // +0x1c
    u32 f20;    // +0x20
    u32 f24;    // +0x24  name pointer (untouched on the terminator)
};

extern "C" {

// 0x00e4a9d0 — SP::sHash(const char*).  Returns 0 for a null name.
u32 SP_sHash(const char* name);

// 0x00e4a9c0 — 4-byte pass-through used to build the value words.  The int
// and float overloads were identical and folded together (ICF).
u32 PropValI(u32 v);
u32 PropValF(float v);

extern PropDesc g_15a68b4[13];  // 0x015a68b4  12 rows + terminator
extern PropDesc g_16b2434[4];   // 0x016b2434   3 rows + terminator
extern PropDesc g_16b1a0c[7];   // 0x016b1a0c   6 rows + terminator
extern PropDesc g_15a78e4[3];   // 0x015a78e4   2 rows + terminator
extern PropDesc g_16b25ec[4];   // 0x016b25ec   3 rows + terminator
extern PropDesc g_16b1e1c[4];   // 0x016b1e1c   3 rows + terminator
extern PropDesc g_16b2d6c[4];   // 0x016b2d6c   3 rows + terminator
extern PropDesc g_15a63dc[4];   // 0x015a63dc   3 rows + terminator

}
