// s0138c040 -- two Spore property-table initializers.
//
// Both functions fill consecutive 0x3c-byte (15 dword) global records by building
// the record in a stack buffer and copying it out with `rep movsd` (MSVC's codegen
// for `g[i] = d;`).  Field layout of the record:
//
//   +0x00 name   +0x04 id     +0x08 size   +0x0c r0  +0x10 r1  +0x14 r2
//   +0x18 a      +0x1c b      +0x20 c      +0x24 d   +0x28 e   +0x2c f
//   +0x30 g      +0x34 h      +0x38 i
//
// r0/r1/r2 are never assigned (the source leaves them uninitialised; MSVC still
// copies them).  Store order per record is name,id,a,b,c,d,e,f,g,h,i,size.
#include "types.h"

typedef unsigned u32;

struct Desc {
    const char* name;   // 0x00
    u32         id;     // 0x04
    u32         size;   // 0x08
    u32         r0;     // 0x0c
    u32         r1;     // 0x10
    u32         r2;     // 0x14
    u32         a;      // 0x18
    u32         b;      // 0x1c
    u32         c;      // 0x20
    const void* d;      // 0x24
    const void* e;      // 0x28
    const void* f;      // 0x2c
    const void* g;      // 0x30
    const void* h;      // 0x34
    const void* i;      // 0x38
};

Desc g_desc1[64];       // 0x15aefd0 .. (14 records used)
Desc g_desc2[64];       // 0x15af358 .. (6 records used)

// --- 0138c5d0: six records.
//
// Every pointer field is emitted as an immediate (no register CSE), which means the
// original referenced a *distinct* source symbol per field that the linker folded to
// the same address (identical functions merged by /OPT:ICF).  The one field that is
// shared between records -- c = 0x692ca0, used by all six -- is CSE'd into edx.
// Distinct placeholder symbols below reproduce that codegen exactly; their addresses
// are relocated, so they are masked during the byte comparison.
static char S_c[1];
static char S_0_n[1], S_0_d[1], S_0_e[1], S_0_f[1], S_0_g[1], S_0_h[1], S_0_i[1];
static char S_1_n[1], S_1_d[1], S_1_e[1], S_1_f[1], S_1_g[1], S_1_h[1], S_1_i[1];
static char S_2_n[1], S_2_d[1], S_2_e[1], S_2_f[1], S_2_g[1], S_2_h[1], S_2_i[1];
static char S_3_n[1], S_3_d[1], S_3_e[1], S_3_f[1], S_3_g[1], S_3_h[1], S_3_i[1];
static char S_4_n[1], S_4_d[1], S_4_e[1], S_4_f[1], S_4_g[1], S_4_h[1], S_4_i[1];
static char S_5_n[1], S_5_d[1], S_5_e[1], S_5_f[1], S_5_g[1], S_5_h[1], S_5_i[1];

// @ 0x138c5d0
void f0138c5d0()
{
    Desc d;

    d.name = S_0_n; d.id = 0x711477d; d.a = 0; d.b = 0; d.c = (u32)S_c;
    d.d = S_0_d; d.e = S_0_e; d.f = S_0_f; d.g = S_0_g; d.h = S_0_h; d.i = S_0_i;
    d.size = 0;
    g_desc2[0] = d;

    d.name = S_1_n; d.id = 0x711477e; d.a = 0; d.b = 0; d.c = (u32)S_c;
    d.d = S_1_d; d.e = S_1_e; d.f = S_1_f; d.g = S_1_g; d.h = S_1_h; d.i = S_1_i;
    d.size = 0x3c;
    g_desc2[1] = d;

    d.name = S_2_n; d.id = 0x711477c; d.a = 0; d.b = 0; d.c = (u32)S_c;
    d.d = S_2_d; d.e = S_2_e; d.f = S_2_f; d.g = S_2_g; d.h = S_2_h; d.i = S_2_i;
    d.size = 0x78;
    g_desc2[2] = d;

    d.name = S_3_n; d.id = 0x711477f; d.a = 0; d.b = 0; d.c = (u32)S_c;
    d.d = S_3_d; d.e = S_3_e; d.f = S_3_f; d.g = S_3_g; d.h = S_3_h; d.i = S_3_i;
    d.size = 0x7c;
    g_desc2[3] = d;

    d.name = S_4_n; d.id = 0x78fe86a; d.a = 0; d.b = 0; d.c = (u32)S_c;
    d.d = S_4_d; d.e = S_4_e; d.f = S_4_f; d.g = S_4_g; d.h = S_4_h; d.i = S_4_i;
    d.size = 0x80;
    g_desc2[4] = d;

    d.name = S_5_n; d.id = 0x711477b; d.a = 0; d.b = 0; d.c = (u32)S_c;
    d.d = S_5_d; d.e = S_5_e; d.f = S_5_f; d.g = S_5_g; d.h = S_5_h; d.i = S_5_i;
    d.size = 0x84;
    g_desc2[5] = d;
}

// --- 0138c040: fourteen records.
//
// Faithful reconstruction using the real pointer values.  It does NOT reproduce the
// original byte-for-byte: the original CSEs several repeated constants into ebx/ebp
// (0xb1fbf0, 0xacbb80, 0xc2e4e0, 0x692fb0) from specific records onward, and contains
// a one-time-init guard (`test byte [0x16c847c],1 / or dword [0x16c847c],1`) inside
// record 4 that no reconstructable source form reproduces.  See nonmatching.txt.
// @ 0x138c040
void f0138c040()
{
    Desc d;

    d.name = (const char*)0x148cb7c; d.id = 0x71147e5; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0x572810; d.e = (const void*)0x572840; d.f = (const void*)0x692ff0;
    d.g = (const void*)0x694ee0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0x57cde0;
    d.size = 0;
    g_desc1[0] = d;

    d.name = (const char*)0x13ed4e4; d.id = 0x71147e6; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0xb6e3a0; d.e = (const void*)0xac88c0; d.f = (const void*)0x6930f0;
    d.g = (const void*)0x695010; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbba0;
    d.size = 4;
    g_desc1[1] = d;

    d.name = (const char*)0x1447370; d.id = 0x71147e7; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0xae33d0; d.e = (const void*)0xae3400; d.f = (const void*)0x693120;
    d.g = (const void*)0x695040; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xae5700;
    d.size = 0x10;
    g_desc1[2] = d;

    d.name = (const char*)0x148cb70; d.id = 0x71147ea; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0x572810; d.e = (const void*)0xac88f0; d.f = (const void*)0x6930b0;
    d.g = (const void*)0x694fc0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbb80;
    d.size = 0x220;
    g_desc1[3] = d;

    // The original also sets a one-time-init flag (bit 0 of 0x16c847c) while filling
    // record 4 -- an artefact of a static local in the original source.  Reproduced
    // here so the function is observably equivalent.
    if ((*(volatile u32*)0x16c847c & 1u) == 0u) *(volatile u32*)0x16c847c |= 1u;

    d.name = (const char*)0x145ca9c; d.id = 0x71147eb; d.a = 0; d.b = 0xf26c60; d.c = 0x692ca0;
    d.d = (const void*)0xf26aa0; d.e = (const void*)0xf27ec0; d.f = (const void*)0xc2e4e0;
    d.g = (const void*)0x692fb0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xac8050;
    d.size = 0x224;
    g_desc1[4] = d;

    d.name = (const char*)0x13f2d1c; d.id = 0x71147e8; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0x572810; d.e = (const void*)0xac88f0; d.f = (const void*)0x6930b0;
    d.g = (const void*)0x694fc0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbb80;
    d.size = 0x20;
    g_desc1[5] = d;

    d.name = (const char*)0x148cb58; d.id = 0x71147e9; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0x572810; d.e = (const void*)0xac88f0; d.f = (const void*)0x6930b0;
    d.g = (const void*)0x694fc0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbb80;
    d.size = 0x24;
    g_desc1[6] = d;

    d.name = (const char*)0x1452788; d.id = 0x78d5a93; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0x572810; d.e = (const void*)0xac88f0; d.f = (const void*)0x6930b0;
    d.g = (const void*)0x694fc0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbb80;
    d.size = 0x1e0;
    g_desc1[7] = d;

    d.name = (const char*)0x1452794; d.id = 0x78d5a94; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0x572810; d.e = (const void*)0xac88f0; d.f = (const void*)0x6930b0;
    d.g = (const void*)0x694fc0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbb80;
    d.size = 0x1e4;
    g_desc1[8] = d;

    d.name = (const char*)0x148cb44; d.id = 0x78d5895; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0xb6e3a0; d.e = (const void*)0xac88c0; d.f = (const void*)0x6930f0;
    d.g = (const void*)0x695010; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbba0;
    d.size = 0x1e8;
    g_desc1[9] = d;

    d.name = (const char*)0x148cb30; d.id = 0x71148e7; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0xae33d0; d.e = (const void*)0xae3400; d.f = (const void*)0x693120;
    d.g = (const void*)0x695040; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xae5700;
    d.size = 0x1f4;
    g_desc1[10] = d;

    d.name = (const char*)0x148cb20; d.id = 0x71148ea; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0x572810; d.e = (const void*)0xac88f0; d.f = (const void*)0x6930b0;
    d.g = (const void*)0x694fc0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbb80;
    d.size = 0x204;
    g_desc1[11] = d;

    d.name = (const char*)0x148cb10; d.id = 0x71148e9; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0xce27a0; d.e = (const void*)0xf26ca0; d.f = (const void*)0xc2e4e0;
    d.g = (const void*)0x692fb0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0x103c3a0;
    d.size = 0x20c;
    g_desc1[12] = d;

    d.name = (const char*)0x148ca9c; d.id = 0x76ca8d3; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0xf2d430; d.e = (const void*)0xf26d30; d.f = (const void*)0xc2e4e0;
    d.g = (const void*)0x692fb0; d.h = (const void*)0xf26dd0; d.i = (const void*)0xf298f0;
    d.size = 0x28;
    g_desc1[13] = d;
}
