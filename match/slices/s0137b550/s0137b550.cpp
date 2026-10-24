// s0137b550 -- three __cdecl static initialisers that populate the SP
// reflection property-descriptor tables for the space-stage effect tools
// ($E311 at 0x0137b550, $E315 at 0x0137b890) and the space transporter tool
// (0x0137bb60 / FUN_0137bb60).
//
// Each routine is a straight-line run of descriptor-slot stores whose values
// come from SP::sHash() (entry-name hashes), PropValF() (typed defaults) and
// pointer constants (the entry's name string, and the data-type descriptor
// addresses).  The tables are arrays of 32-bit slots, exactly as laid out in
// the image.
//
// Build flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned char u8;
typedef unsigned int  u32;
typedef int           i32;
typedef float         f32;

namespace SP {
    u32 sHash(const char *text);                 // 0x00e4a9d0  ?sHash@SP@@YAIPBD@Z
}

// The property-value constructor is overloaded on the argument type.  The
// original declares separate integer / float / pointer entry points whose
// identical bodies the linker folds onto 0x00e4a9c0; keeping the overloads
// reproduces the exact argument encoding of the original call sites (immediate
// integer push / x87 float push / descriptor address push).
u32 PropValF(i32 value);                          // small integer default
u32 PropValF(f32 value);                          // float default
u32 PropValF(const void *value);                  // data-type descriptor address

// ---------------------------------------------------------------------------
// float constants and descriptor / enum-table globals referenced by the tables
// ---------------------------------------------------------------------------
extern const f32 DAT_013eb1bc;                    // 0x013eb1bc  -1.0f
extern const f32 DAT_01473c70;                    // 0x01473c70  +10.0f

extern const u8 DT_EFFECTMAP_ENTRY_BACKGROUND;        // 0x016b0ad8
extern const u8 DT_EFFECTMAP_ENTRY_FOREGROUND;        // 0x016ad5e4
extern const u8 DT_EFFECTMAP_ENTRY_TRACER;            // 0x016b0b8c
extern const u8 DT_EFFECTMAP_ENTRY_TRACER_BACKGROUND; // 0x016ad614
extern const u8 DT_EFFECTMAP_ENTRY_SKYBOX;            // 0x016ad484
extern const u8 DT_EFFECTMAP_ENTRY_TILE_BACKGROUND;   // 0x016b0cd0

// the tiling enumeration parse-info block pointed at by the "tilingGrid" entry
extern const u8 g_kTilingsEnumParseInfo;         // 0x01482a78

// ---------------------------------------------------------------------------
// the three descriptor tables (one 32-bit slot per four bytes of the image)
// ---------------------------------------------------------------------------
extern u32 g_e311Table[79];    // 0x016b28e4 .. 0x016b2a1c  ($E311, tiling tool)
extern u32 g_e315Table[69];    // 0x015a679c .. 0x015a68ac  ($E315, effect map)
extern u32 g_transportTable[29]; // 0x015a7b14 .. 0x015a7b84 (transporter tool)

// ---------------------------------------------------------------------------
// $E311 -- tiling-grid property descriptor table
// ---------------------------------------------------------------------------
// @ 0x0137b550
void E311_InitTilingTable(void)
{
    g_e311Table[0]  = SP::sHash(0);
    g_e311Table[1]  = 4;
    g_e311Table[2]  = 0;
    g_e311Table[3]  = PropValF(1);
    g_e311Table[4]  = PropValF(0);
    g_e311Table[5]  = 0;
    g_e311Table[6]  = PropValF(5);
    g_e311Table[7]  = 8;
    g_e311Table[8]  = 0;
    g_e311Table[9]  = 0;
    g_e311Table[10] = SP::sHash(0);
    g_e311Table[11] = 0;
    g_e311Table[12] = 0;
    g_e311Table[13] = PropValF(7);
    g_e311Table[14] = PropValF(0);
    g_e311Table[15] = 0;
    g_e311Table[16] = PropValF(0);
    g_e311Table[17] = 0;
    g_e311Table[18] = 0;
    g_e311Table[19] = 0;
    g_e311Table[20] = SP::sHash(0);
    g_e311Table[21] = 8;
    g_e311Table[22] = 0;
    g_e311Table[23] = PropValF(2);
    g_e311Table[24] = PropValF(0);
    g_e311Table[25] = 1;
    g_e311Table[26] = PropValF(DAT_013eb1bc);
    g_e311Table[27] = 0;
    g_e311Table[28] = 0;
    g_e311Table[29] = 0;
    g_e311Table[30] = SP::sHash(0);
    g_e311Table[31] = 0xc;
    g_e311Table[32] = 0;
    g_e311Table[33] = PropValF(2);
    g_e311Table[34] = PropValF(0);
    g_e311Table[35] = 2;
    g_e311Table[36] = PropValF(DAT_013eb1bc);
    g_e311Table[37] = 0;
    g_e311Table[38] = 0;
    g_e311Table[39] = 0;
    g_e311Table[40] = SP::sHash(0);
    g_e311Table[41] = 0x10;
    g_e311Table[42] = 0;
    g_e311Table[43] = PropValF(2);
    g_e311Table[44] = PropValF(0);
    g_e311Table[45] = 3;
    g_e311Table[46] = PropValF(DAT_013eb1bc);
    g_e311Table[47] = 0;
    g_e311Table[48] = 0;
    g_e311Table[49] = 0;
    g_e311Table[50] = SP::sHash(0);
    g_e311Table[51] = 0x14;
    g_e311Table[52] = 0;
    g_e311Table[53] = PropValF(2);
    g_e311Table[54] = PropValF(0);
    g_e311Table[55] = 4;
    g_e311Table[56] = PropValF(DAT_013eb1bc);
    g_e311Table[57] = 0;
    g_e311Table[58] = 0;
    g_e311Table[59] = (u32)"tilingGrid";
    g_e311Table[60] = SP::sHash("tilingGrid");
    g_e311Table[61] = 0x18;
    g_e311Table[62] = 0;
    g_e311Table[63] = PropValF(5);
    g_e311Table[64] = PropValF(0);
    g_e311Table[65] = 0;
    g_e311Table[66] = PropValF(0);
    g_e311Table[67] = 2;
    g_e311Table[68] = (u32)&g_kTilingsEnumParseInfo;
    g_e311Table[69] = 0;
    g_e311Table[70] = SP::sHash(0);
    g_e311Table[71] = 0xffffffff;
    g_e311Table[72] = 0;
    g_e311Table[73] = PropValF(0);
    g_e311Table[74] = PropValF(0);
    g_e311Table[75] = 0;
    g_e311Table[76] = PropValF(0);
    g_e311Table[77] = 0;
    g_e311Table[78] = 0;
}

// ---------------------------------------------------------------------------
// $E315 -- effect-map property descriptor table
// ---------------------------------------------------------------------------
// @ 0x0137b890
void E315_InitEffectMapTable(void)
{
    g_e315Table[0]  = SP::sHash("background");
    g_e315Table[1]  = 4;
    g_e315Table[2]  = 0;
    g_e315Table[3]  = PropValF(&DT_EFFECTMAP_ENTRY_BACKGROUND);
    g_e315Table[4]  = PropValF(4);
    g_e315Table[5]  = 0;
    g_e315Table[6]  = PropValF(0);
    g_e315Table[7]  = 4;
    g_e315Table[8]  = 0;
    g_e315Table[9]  = (u32)"foreground";
    g_e315Table[10] = SP::sHash("foreground");
    g_e315Table[11] = 4;
    g_e315Table[12] = 0;
    g_e315Table[13] = PropValF(&DT_EFFECTMAP_ENTRY_FOREGROUND);
    g_e315Table[14] = PropValF(4);
    g_e315Table[15] = 0;
    g_e315Table[16] = PropValF(0);
    g_e315Table[17] = 4;
    g_e315Table[18] = 0;
    g_e315Table[19] = (u32)"tracer";
    g_e315Table[20] = SP::sHash("tracer");
    g_e315Table[21] = 4;
    g_e315Table[22] = 0;
    g_e315Table[23] = PropValF(&DT_EFFECTMAP_ENTRY_TRACER);
    g_e315Table[24] = PropValF(4);
    g_e315Table[25] = 0;
    g_e315Table[26] = PropValF(0);
    g_e315Table[27] = 4;
    g_e315Table[28] = 0;
    g_e315Table[29] = (u32)"tracer_background";
    g_e315Table[30] = SP::sHash("tracer_background");
    g_e315Table[31] = 4;
    g_e315Table[32] = 0;
    g_e315Table[33] = PropValF(&DT_EFFECTMAP_ENTRY_TRACER_BACKGROUND);
    g_e315Table[34] = PropValF(4);
    g_e315Table[35] = 0;
    g_e315Table[36] = PropValF(0);
    g_e315Table[37] = 4;
    g_e315Table[38] = 0;
    g_e315Table[39] = (u32)"skybox";
    g_e315Table[40] = SP::sHash("skybox");
    g_e315Table[41] = 4;
    g_e315Table[42] = 0;
    g_e315Table[43] = PropValF(&DT_EFFECTMAP_ENTRY_SKYBOX);
    g_e315Table[44] = PropValF(4);
    g_e315Table[45] = 0;
    g_e315Table[46] = PropValF(0);
    g_e315Table[47] = 4;
    g_e315Table[48] = 0;
    g_e315Table[49] = (u32)"tile_background";
    g_e315Table[50] = SP::sHash("tile_background");
    g_e315Table[51] = 4;
    g_e315Table[52] = 0;
    g_e315Table[53] = PropValF(&DT_EFFECTMAP_ENTRY_TILE_BACKGROUND);
    g_e315Table[54] = PropValF(4);
    g_e315Table[55] = 0;
    g_e315Table[56] = PropValF(0);
    g_e315Table[57] = 4;
    g_e315Table[58] = 0;
    g_e315Table[59] = 0;
    g_e315Table[60] = SP::sHash(0);
    g_e315Table[61] = 0xffffffff;
    g_e315Table[62] = 0;
    g_e315Table[63] = PropValF(0);
    g_e315Table[64] = PropValF(0);
    g_e315Table[65] = 0;
    g_e315Table[66] = PropValF(0);
    g_e315Table[67] = 0;
    g_e315Table[68] = 0;
}

// ---------------------------------------------------------------------------
// FUN_0137bb60 -- space transporter property descriptor table
// ---------------------------------------------------------------------------
// @ 0x0137bb60
void FUN_0137bb60(void)
{
    g_transportTable[0]  = SP::sHash("teleportCost");
    g_transportTable[1]  = 0;
    g_transportTable[2]  = 0;
    g_transportTable[3]  = PropValF(1);
    g_transportTable[4]  = PropValF(0);
    g_transportTable[5]  = 0;
    g_transportTable[6]  = PropValF(10);
    g_transportTable[7]  = 6;
    g_transportTable[8]  = 0;
    g_transportTable[9]  = (u32)"teleportRange";
    g_transportTable[10] = SP::sHash("teleportRange");
    g_transportTable[11] = 4;
    g_transportTable[12] = 0;
    g_transportTable[13] = PropValF(2);
    g_transportTable[14] = PropValF(0);
    g_transportTable[15] = 0;
    g_transportTable[16] = PropValF(DAT_01473c70);
    g_transportTable[17] = 6;
    g_transportTable[18] = 0;
    g_transportTable[19] = 0;
    g_transportTable[20] = SP::sHash(0);
    g_transportTable[21] = 0xffffffff;
    g_transportTable[22] = 0;
    g_transportTable[23] = PropValF(0);
    g_transportTable[24] = PropValF(0);
    g_transportTable[25] = 0;
    g_transportTable[26] = PropValF(0);
    g_transportTable[27] = 0;
    g_transportTable[28] = 0;
}