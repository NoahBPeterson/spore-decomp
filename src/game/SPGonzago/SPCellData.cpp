// src/game/SPGonzago/SPCellData.cpp -- migrated from slice(s) s0137b550, s013792c0, s013774e0, s01376850, s01374720, s01373120 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCellData.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s01373120 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP
{
    uint32_t __cdecl sHash(const char* pName);                             // 0x00e4a9d0
    uint32_t __cdecl PropValF(float nValue);                               // 0x00e4a9c0
    uint32_t __cdecl PropValF(int nValue);                                 // 0x00e4a9c0
    uint32_t __cdecl PropValF(const void* pValue);                         // 0x00e4a9c0
}
struct cPropRecord
{
    uint32_t     mPad00;                  // +0x00
    uint32_t     mDefault;                // +0x04  (PropValF result)
    int32_t      mType;                   // +0x08
    uint32_t     mPad0c;                  // +0x0c
    const char*  mpName;                  // +0x10
    uint32_t     mHash;                   // +0x14
    int32_t      mOffset;                 // +0x18
    uint32_t     mPad1c;                  // +0x1c
    uint32_t     mValue1;                 // +0x20
    uint32_t     mValue2;                 // +0x24
};
extern cPropRecord gPropTable_16b2c40[];  // 0x016b2c40
extern cPropRecord gPropTable_16b1430[];  // 0x016b1430
extern cPropRecord gPropTable_15a7948[];  // 0x015a7948
// ---- items of slice s01373120 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cPropRecord gPropTable_16b2c40[];  // 0x016b2c40
extern cPropRecord gPropTable_16b1430[];  // 0x016b1430
extern cPropRecord gPropTable_15a7948[];  // 0x015a7948

// ---- items of slice s01374720 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int FUN_00e4a9c0(...);   // builds a property type descriptor
extern "C" int sHash(...);          // SP::sHash
extern int  G[0x200];                 // the table at 0x016b312c
extern char UNK_014829f0, UNK_01482928;
extern char DAT_01483154, PTR_DAT_014828a8;
extern char _DT_LOOT_TABLE_SP__3VcTypeDef_1_B;
extern char _DT_CELL_SP__3VcTypeDef_1_B;
// ---- items of slice s01374720 end

// ---- items of slice s01376850 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int Conv(int);              // 0x00e4a9c0
extern "C" int ConvF(float);           // 0x00e4a9c0
extern int  g_ctPopulation;  // 0x016b0a80  _DT_CELL_POPULATION_SP__3VcTypeDef_1_B
typedef unsigned int u32;
extern "C" u32 SP_sHash(const char*);  // 0x00e4a9d0 (SP::sHash)
namespace SP {
struct cFieldDef {
    u32         hash;         // +0x00
    int         offset;       // +0x04
    int         auxOffset;    // +0x08
    int         type;         // +0x0c
    int         typeDesc;     // +0x10
    int         argIndex;     // +0x14
    int         defaultValue; // +0x18
    int         flags;        // +0x1c
    int         enumTable;    // +0x20
    const char* name;         // +0x24
};  // namespace SP
}
using SP::cFieldDef;
extern cFieldDef g_16b277c[9];   // 0x016b277c
// ---- items of slice s01376850 end

// ---- items of slice s013774e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_dtCell;        // 0x016ad4b0  _DT_CELL_SP__3VcTypeDef_1_B
extern int g_dtPopulation;  // 0x016b0a80  _DT_CELL_POPULATION...
extern int g_dtDistribute;  // 0x016ad3fc  DT_CELL_DISTRIBUTE
extern int g_dtCluster;     // 0x016b0d28  DT_CELL_CLUSTER
extern int g_dtPlant;       // 0x016b0bb8  DT_CELL_PLANT
extern int g_dtEncounter;   // 0x016b0ca4  DT_CELL_ENCOUNTER
extern int g_dtLevelEntry;  // 0x016b10a4  DT_LEVEL_ENTRY
extern int g_dtAdvectEntry; // 0x016b0f3c  DT_ADVECT_ENTRY
extern int g_kTilings;      // 0x01482a78  _kTilings_SP__3QBUcEnumParseInfo_ArgScript_EA__B
extern cFieldDef g_16b222c[13];  // 0x016b222c
extern cFieldDef g_15a77cc[7];   // 0x015a77cc
extern cFieldDef g_16b2e0c[4];   // 0x016b2e0c
extern cFieldDef g_16b209c[7];   // 0x016b209c
extern cFieldDef g_15a7754[3];   // 0x015a7754
extern cFieldDef g_16b1bc4[3];   // 0x016b1bc4
// ---- items of slice s013774e0 end

// ---- items of slice s013792c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
extern "C" u32 PropValI(u32 v);
extern "C" u32 PropValF(float v);
extern "C" extern PropDesc g_15a68b4[13];  // 0x015a68b4  12 rows + terminator
extern "C" extern PropDesc g_16b1a0c[7];   // 0x016b1a0c   6 rows + terminator
extern "C" extern PropDesc g_15a78e4[3];   // 0x015a78e4   2 rows + terminator
// ---- items of slice s013792c0 end

// ---- items of slice s0137b550 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
typedef int           i32;
typedef float         f32;
namespace SP {
    u32 sHash_s0137_b550(const char *text);                 // 0x00e4a9d0  ?sHash@SP@@YAIPBD@Z
}
extern const f32 DAT_013eb1bc;                    // 0x013eb1bc  -1.0f
extern const u8 DT_EFFECTMAP_ENTRY_BACKGROUND;        // 0x016b0ad8
extern const u8 DT_EFFECTMAP_ENTRY_FOREGROUND;        // 0x016ad5e4
extern const u8 DT_EFFECTMAP_ENTRY_TRACER;            // 0x016b0b8c
extern const u8 DT_EFFECTMAP_ENTRY_TRACER_BACKGROUND; // 0x016ad614
extern const u8 DT_EFFECTMAP_ENTRY_SKYBOX;            // 0x016ad484
extern const u8 DT_EFFECTMAP_ENTRY_TILE_BACKGROUND;   // 0x016b0cd0
extern const u8 g_kTilingsEnumParseInfo;         // 0x01482a78
extern u32 g_e311Table[79];    // 0x016b28e4 .. 0x016b2a1c  ($E311, tiling tool)
extern u32 g_e315Table[69];    // 0x015a679c .. 0x015a68ac  ($E315, effect map)
// ---- items of slice s0137b550 end

// @ 0x01373c20
void __declspec(noinline) InitPropTable_16b2c40()
{
    cPropRecord* p = gPropTable_16b2c40;

    p[0].mHash = SP::sHash(0);
    p[0].mOffset = 0;
    p[0].mPad1c = 0;
    p[0].mValue1 = SP::PropValF(1);
    p[0].mValue2 = SP::PropValF(0);

    p[1].mPad00 = 0;
    p[1].mDefault = SP::PropValF(1);
    p[1].mType = 8;
    p[1].mPad0c = 0;
    p[1].mpName = 0;
    p[1].mHash = SP::sHash(0);
    p[1].mOffset = 4;
    p[1].mPad1c = 0;
    p[1].mValue1 = SP::PropValF(3);
    p[1].mValue2 = SP::PropValF((const void*)0x016ad4b0);

    p[2].mPad00 = 0;
    p[2].mDefault = SP::PropValF(0);
    p[2].mType = 0;
    p[2].mPad0c = 0;
    p[2].mpName = "weight";
    p[2].mHash = SP::sHash("weight");
    p[2].mOffset = 0xc;
    p[2].mPad1c = 0;
    p[2].mValue1 = SP::PropValF(2);
    p[2].mValue2 = SP::PropValF(0);

    p[3].mPad00 = 0;
    p[3].mDefault = SP::PropValF(1.0f);
    p[3].mType = 2;
    p[3].mPad0c = 0;
    p[3].mpName = "count";
    p[3].mHash = SP::sHash("count");
    p[3].mOffset = 0x10;
    p[3].mPad1c = 0;
    p[3].mValue1 = SP::PropValF(1);
    p[3].mValue2 = SP::PropValF(0);

    p[4].mPad00 = 0;
    p[4].mDefault = SP::PropValF(1);
    p[4].mType = 2;
    p[4].mPad0c = 0;
    p[4].mpName = "countDelta";
    p[4].mHash = SP::sHash("countDelta");
    p[4].mOffset = 0x14;
    p[4].mPad1c = 0;
    p[4].mValue1 = SP::PropValF(1);
    p[4].mValue2 = SP::PropValF(0);

    p[5].mPad00 = 0;
    p[5].mDefault = SP::PropValF(0);
    p[5].mType = 2;
    p[5].mPad0c = 0;
    p[5].mpName = "levelOffset";
    p[5].mHash = SP::sHash("levelOffset");
    p[5].mOffset = 0x18;
    p[5].mPad1c = 0;
    p[5].mValue1 = SP::PropValF(1);
    p[5].mValue2 = SP::PropValF(0);

    p[6].mPad00 = 0;
    p[6].mDefault = SP::PropValF(0);
    p[6].mType = 2;
    p[6].mPad0c = 0;
    p[6].mpName = 0;
    p[6].mHash = SP::sHash(0);
    p[6].mOffset = -1;
    p[6].mPad1c = 0;
    p[6].mValue1 = SP::PropValF(0);
    p[6].mValue2 = SP::PropValF(0);

    p[7].mPad00 = 0;
    p[7].mDefault = SP::PropValF(0);
    p[7].mType = 0;
    p[7].mPad0c = 0;
}

// @ 0x01373ef0
void __declspec(noinline) InitPropTable_16b1430()
{
    cPropRecord* p = gPropTable_16b1430;

    p[0].mHash = SP::sHash(0);
    p[0].mOffset = 0;
    p[0].mPad1c = 0;
    p[0].mValue1 = SP::PropValF(1);
    p[0].mValue2 = SP::PropValF(0);

    p[1].mPad00 = 0;
    p[1].mDefault = SP::PropValF(2);
    p[1].mType = 8;
    p[1].mPad0c = 0;
    p[1].mpName = 0;
    p[1].mHash = SP::sHash(0);
    p[1].mOffset = 8;
    p[1].mPad1c = 0;
    p[1].mValue1 = SP::PropValF(3);
    p[1].mValue2 = SP::PropValF((const void*)0x016b1020);

    p[2].mPad00 = 0;
    p[2].mDefault = SP::PropValF(0);
    p[2].mType = 0;
    p[2].mPad0c = 0;
    p[2].mpName = "weight";
    p[2].mHash = SP::sHash("weight");
    p[2].mOffset = 0xc;
    p[2].mPad1c = 0;
    p[2].mValue1 = SP::PropValF(2);
    p[2].mValue2 = SP::PropValF(0);

    p[3].mPad00 = 0;
    p[3].mDefault = SP::PropValF(1.0f);
    p[3].mType = 2;
    p[3].mPad0c = 0;
    p[3].mpName = "count";
    p[3].mHash = SP::sHash("count");
    p[3].mOffset = 0x10;
    p[3].mPad1c = 0;
    p[3].mValue1 = SP::PropValF(1);
    p[3].mValue2 = SP::PropValF(0);

    p[4].mPad00 = 0;
    p[4].mDefault = SP::PropValF(1);
    p[4].mType = 2;
    p[4].mPad0c = 0;
    p[4].mpName = "countDelta";
    p[4].mHash = SP::sHash("countDelta");
    p[4].mOffset = 0x14;
    p[4].mPad1c = 0;
    p[4].mValue1 = SP::PropValF(1);
    p[4].mValue2 = SP::PropValF(0);

    p[5].mPad00 = 0;
    p[5].mDefault = SP::PropValF(0);
    p[5].mType = 2;
    p[5].mPad0c = 0;
    p[5].mpName = 0;
    p[5].mHash = SP::sHash(0);
    p[5].mOffset = -1;
    p[5].mPad1c = 0;
    p[5].mValue1 = SP::PropValF(0);
    p[5].mValue2 = SP::PropValF(0);

    p[6].mPad00 = 0;
    p[6].mDefault = SP::PropValF(0);
    p[6].mType = 0;
    p[6].mPad0c = 0;
}

// @ 0x013742c0
void __declspec(noinline) InitPropTable_15a7948()
{
    cPropRecord* p = gPropTable_15a7948;

    p[0].mHash = SP::sHash("table");
    p[0].mOffset = 0;
    p[0].mPad1c = 4;
    p[0].mValue1 = SP::PropValF((const void*)0x016b0f8c);
    p[0].mValue2 = SP::PropValF(4);

    p[1].mPad00 = 0;
    p[1].mDefault = SP::PropValF(0);
    p[1].mType = 4;
    p[1].mPad0c = 0;
    p[1].mpName = "cell";
    p[1].mHash = SP::sHash("cell");
    p[1].mOffset = 0;
    p[1].mPad1c = 4;
    p[1].mValue1 = SP::PropValF((const void*)0x016b0a54);
    p[1].mValue2 = SP::PropValF(4);

    p[2].mPad00 = 0;
    p[2].mDefault = SP::PropValF(0);
    p[2].mType = 4;
    p[2].mPad0c = 0;
    p[2].mpName = "nothing";
    p[2].mHash = SP::sHash("nothing");
    p[2].mOffset = 0;
    p[2].mPad1c = 4;
    p[2].mValue1 = SP::PropValF((const void*)0x016b0ea8);
    p[2].mValue2 = SP::PropValF(4);

    p[3].mPad00 = 0;
    p[3].mDefault = SP::PropValF(0);
    p[3].mType = 4;
    p[3].mPad0c = 0;
    p[3].mpName = "expelForce";
    p[3].mHash = SP::sHash("expelForce");
    p[3].mOffset = 0x14;
    p[3].mPad1c = 0;
    p[3].mValue1 = SP::PropValF(2);
    p[3].mValue2 = SP::PropValF(0);

    p[4].mPad00 = 0;
    p[4].mDefault = SP::PropValF(0.0f);
    p[4].mType = 6;
    p[4].mPad0c = 0;
    p[4].mpName = "effect";
    p[4].mHash = SP::sHash("effect");
    p[4].mOffset = 0x18;
    p[4].mPad1c = 0x18;
    p[4].mValue1 = SP::PropValF(7);
    p[4].mValue2 = SP::PropValF(0);

    p[5].mPad00 = 0;
    p[5].mDefault = SP::PropValF(0);
    p[5].mType = 6;
    p[5].mPad0c = 0;
    p[5].mpName = "mustHavePart";
    p[5].mHash = SP::sHash("mustHavePart");
    p[5].mOffset = 0x1c;
    p[5].mPad1c = 0;
    p[5].mValue1 = SP::PropValF(6);
    p[5].mValue2 = SP::PropValF(0);

    p[6].mPad00 = 0;
    p[6].mDefault = SP::PropValF(0);
    p[6].mType = 6;
    p[6].mPad0c = 0;
    p[6].mpName = "minRadius";
    p[6].mHash = SP::sHash("minRadius");
    p[6].mOffset = 8;
    p[6].mPad1c = 0;
    p[6].mValue1 = SP::PropValF(2);
    p[6].mValue2 = SP::PropValF(0);

    p[7].mPad00 = 0;
    p[7].mDefault = SP::PropValF(0.0f);
    p[7].mType = 6;
    p[7].mPad0c = 0;
    p[7].mpName = "maxRadius";
    p[7].mHash = SP::sHash("maxRadius");
    p[7].mOffset = 0xc;
    p[7].mPad1c = 0;
    p[7].mValue1 = SP::PropValF(2);
    p[7].mValue2 = SP::PropValF(0);

    p[8].mPad00 = 0;
    p[8].mDefault = SP::PropValF(0.0f);
    p[8].mType = 6;
    p[8].mPad0c = 0;
    p[8].mpName = "initialAlpha";
    p[8].mHash = SP::sHash("initialAlpha");
    p[8].mOffset = 0x10;
    p[8].mPad1c = 0;
    p[8].mValue1 = SP::PropValF(2);
    p[8].mValue2 = SP::PropValF(0);

    p[9].mPad00 = 0;
    p[9].mDefault = SP::PropValF(1.0f);
    p[9].mType = 6;
    p[9].mPad0c = 0;
    p[9].mpName = "delay";
    p[9].mHash = SP::sHash("delay");
    p[9].mOffset = 0x20;
    p[9].mPad1c = 0;
    p[9].mValue1 = SP::PropValF(2);
    p[9].mValue2 = SP::PropValF(0);

    p[10].mPad00 = 0;
    p[10].mDefault = SP::PropValF(0.0f);
    p[10].mType = 6;
    p[10].mPad0c = 0;
    p[10].mpName = 0;
    p[10].mHash = SP::sHash(0);
    p[10].mOffset = -1;
    p[10].mPad1c = 0;
    p[10].mValue1 = SP::PropValF(0);
    p[10].mValue2 = SP::PropValF(0);

    p[11].mPad00 = 0;
    p[11].mDefault = SP::PropValF(0);
    p[11].mType = 0;
    p[11].mPad0c = 0;
}

// @ 0x01374720
void FUN_01374720(void)
{
// 509 stores
  G[0x000] = sHash(0);
  G[0x001] = 0;
  G[0x002] = 0;
  G[0x003] = FUN_00e4a9c0(5);
  G[0x004] = FUN_00e4a9c0(0);
  G[0x005] = 0;
  G[0x006] = FUN_00e4a9c0(0);
  G[0x007] = 0;
  G[0x008] = (int)&UNK_014829f0;
  G[0x009] = (int)"movementStyle";
  G[0x00a] = sHash("movementStyle");
  G[0x00b] = 0x10;
  G[0x00c] = 0;
  G[0x00d] = FUN_00e4a9c0(5);
  G[0x00e] = FUN_00e4a9c0(0);
  G[0x00f] = 0;
  G[0x010] = FUN_00e4a9c0(0);
  G[0x011] = 2;
  G[0x012] = (int)&UNK_01482928;
  G[0x013] = (int)"flocking";
  G[0x014] = sHash("flocking");
  G[0x015] = 0x14;
  G[0x016] = 0;
  G[0x017] = FUN_00e4a9c0(6);
  G[0x018] = FUN_00e4a9c0(0);
  G[0x019] = 0;
  G[0x01a] = FUN_00e4a9c0(0);
  G[0x01b] = 2;
  G[0x01c] = 0;
  G[0x01d] = (int)"speed";
  G[0x01e] = sHash("speed");
  G[0x01f] = 0x18;
  G[0x020] = 0;
  G[0x021] = FUN_00e4a9c0(2);
  G[0x022] = FUN_00e4a9c0(0);
  G[0x023] = 0;
  G[0x024] = FUN_00e4a9c0(0x3f800000);
  G[0x025] = 2;
  G[0x026] = 0;
  G[0x027] = (int)"wanderSpeed";
  G[0x028] = sHash("wanderSpeed");
  G[0x029] = 0x20;
  G[0x02a] = 0;
  G[0x02b] = FUN_00e4a9c0(2);
  G[0x02c] = FUN_00e4a9c0(0);
  G[0x02d] = 0;
  G[0x02e] = FUN_00e4a9c0(0);
  G[0x02f] = 2;
  G[0x030] = 0;
  G[0x031] = (int)"chaseSpeed";
  G[0x032] = sHash("chaseSpeed");
  G[0x033] = 0x1c;
  G[0x034] = 0;
  G[0x035] = FUN_00e4a9c0(2);
  G[0x036] = FUN_00e4a9c0(0);
  G[0x037] = 0;
  G[0x038] = FUN_00e4a9c0(0);
  G[0x039] = 2;
  G[0x03a] = 0;
  G[0x03b] = (int)"fleeSpeed";
  G[0x03c] = sHash("fleeSpeed");
  G[0x03d] = 0x24;
  G[0x03e] = 0;
  G[0x03f] = FUN_00e4a9c0(2);
  G[0x040] = FUN_00e4a9c0(0);
  G[0x041] = 0;
  G[0x042] = FUN_00e4a9c0(0);
  G[0x043] = 2;
  G[0x044] = 0;
  G[0x045] = (int)"turnFactor";
  G[0x046] = sHash("turnFactor");
  G[0x047] = 0x40;
  G[0x048] = 0;
  G[0x049] = FUN_00e4a9c0(2);
  G[0x04a] = FUN_00e4a9c0(0);
  G[0x04b] = 0;
  G[0x04c] = FUN_00e4a9c0(0x3f800000);
  G[0x04d] = 2;
  G[0x04e] = 0;
  G[0x04f] = (int)"axialMovement";
  G[0x050] = sHash("axialMovement");
  G[0x051] = 0x44;
  G[0x052] = 0;
  G[0x053] = FUN_00e4a9c0(6);
  G[0x054] = FUN_00e4a9c0(0);
  G[0x055] = 0;
  G[0x056] = FUN_00e4a9c0(0);
  G[0x057] = 2;
  G[0x058] = 0;
  G[0x059] = (int)"spawnTime";
  G[0x05a] = sHash("spawnTime");
  G[0x05b] = 0x48;
  G[0x05c] = 0;
  G[0x05d] = FUN_00e4a9c0(2);
  G[0x05e] = FUN_00e4a9c0(0);
  G[0x05f] = 0;
  G[0x060] = FUN_00e4a9c0(0);
  G[0x061] = 2;
  G[0x062] = 0;
  G[0x063] = (int)"spawnRestTime";
  G[0x064] = sHash("spawnRestTime");
  G[0x065] = 0x4c;
  G[0x066] = 0;
  G[0x067] = FUN_00e4a9c0(2);
  G[0x068] = FUN_00e4a9c0(0);
  G[0x069] = 0;
  G[0x06a] = FUN_00e4a9c0(0);
  G[0x06b] = 2;
  G[0x06c] = 0;
  G[0x06d] = (int)"spawnOutput";
  G[0x06e] = sHash("spawnOutput");
  G[0x06f] = 0x50;
  G[0x070] = 0;
  G[0x071] = FUN_00e4a9c0(3);
  G[0x072] = FUN_00e4a9c0((int)&_DT_LOOT_TABLE_SP__3VcTypeDef_1_B);
  G[0x073] = 0;
  G[0x074] = FUN_00e4a9c0(0);
  G[0x075] = 2;
  G[0x076] = 0;
  G[0x077] = (int)"arcLength";
  G[0x078] = sHash("arcLength");
  G[0x079] = 0x54;
  G[0x07a] = 0;
  G[0x07b] = FUN_00e4a9c0(2);
  G[0x07c] = FUN_00e4a9c0(0);
  G[0x07d] = 0;
  G[0x07e] = FUN_00e4a9c0(0x40400000);
  G[0x07f] = 2;
  G[0x080] = 0;
  G[0x081] = (int)"arcLengthSecondary";
  G[0x082] = sHash("arcLengthSecondary");
  G[0x083] = 0x58;
  G[0x084] = 0;
  G[0x085] = FUN_00e4a9c0(2);
  G[0x086] = FUN_00e4a9c0(0);
  G[0x087] = 0;
  G[0x088] = FUN_00e4a9c0(0);
  G[0x089] = 2;
  G[0x08a] = 0;
  G[0x08b] = (int)"numArcs";
  G[0x08c] = sHash("numArcs");
  G[0x08d] = 0x5c;
  G[0x08e] = 0;
  G[0x08f] = FUN_00e4a9c0(1);
  G[0x090] = FUN_00e4a9c0(0);
  G[0x091] = 0;
  G[0x092] = FUN_00e4a9c0(3);
  G[0x093] = 2;
  G[0x094] = 0;
  G[0x095] = (int)"awarenessRadius";
  G[0x096] = sHash("awarenessRadius");
  G[0x097] = 4;
  G[0x098] = 0;
  G[0x099] = FUN_00e4a9c0(2);
  G[0x09a] = FUN_00e4a9c0(0);
  G[0x09b] = 0;
  G[0x09c] = FUN_00e4a9c0(0x41200000);
  G[0x09d] = 2;
  G[0x09e] = 0;
  G[0x09f] = (int)"awarenessRadiusFood";
  G[0x0a0] = sHash("awarenessRadiusFood");
  G[0x0a1] = 8;
  G[0x0a2] = 0;
  G[0x0a3] = FUN_00e4a9c0(2);
  G[0x0a4] = FUN_00e4a9c0(0);
  G[0x0a5] = 0;
  G[0x0a6] = FUN_00e4a9c0(0);
  G[0x0a7] = 2;
  G[0x0a8] = 0;
  G[0x0a9] = (int)"awarenessRadiusPredator";
  G[0x0aa] = sHash("awarenessRadiusPredator");
  G[0x0ab] = 0xc;
  G[0x0ac] = 0;
  G[0x0ad] = FUN_00e4a9c0(2);
  G[0x0ae] = FUN_00e4a9c0(0);
  G[0x0af] = 0;
  G[0x0b0] = FUN_00e4a9c0(0);
  G[0x0b1] = 2;
  G[0x0b2] = 0;
  G[0x0b3] = (int)"keyTransformation";
  G[0x0b4] = sHash("keyTransformation");
  G[0x0b5] = 0x60;
  G[0x0b6] = 0;
  G[0x0b7] = FUN_00e4a9c0(3);
  G[0x0b8] = FUN_00e4a9c0((int)&_DT_CELL_SP__3VcTypeDef_1_B);
  G[0x0b9] = 0;
  G[0x0ba] = FUN_00e4a9c0(0);
  G[0x0bb] = 2;
  G[0x0bc] = 0;
  G[0x0bd] = (int)"keyProjectile";
  G[0x0be] = sHash("keyProjectile");
  G[0x0bf] = 100;
  G[0x0c0] = 0;
  G[0x0c1] = FUN_00e4a9c0(3);
  G[0x0c2] = FUN_00e4a9c0((int)&_DT_CELL_SP__3VcTypeDef_1_B);
  G[0x0c3] = 0;
  G[0x0c4] = FUN_00e4a9c0(0);
  G[0x0c5] = 2;
  G[0x0c6] = 0;
  G[0x0c7] = (int)&DAT_01483154;
  G[0x0c8] = sHash((int)&DAT_01483154);
  G[0x0c9] = 0x68;
  G[0x0ca] = 0;
  G[0x0cb] = FUN_00e4a9c0(5);
  G[0x0cc] = FUN_00e4a9c0(0);
  G[0x0cd] = 0;
  G[0x0ce] = FUN_00e4a9c0(3);
  G[0x0cf] = 2;
  G[0x0d0] = (int)&PTR_DAT_014828a8;
  G[0x0d1] = (int)"growCount";
  G[0x0d2] = sHash("growCount");
  G[0x0d3] = 0x6c;
  G[0x0d4] = 0;
  G[0x0d5] = FUN_00e4a9c0(1);
  G[0x0d6] = FUN_00e4a9c0(0);
  G[0x0d7] = 0;
  G[0x0d8] = FUN_00e4a9c0(0);
  G[0x0d9] = 2;
  G[0x0da] = 0;
  G[0x0db] = (int)"digestionCount";
  G[0x0dc] = sHash("digestionCount");
  G[0x0dd] = 0x70;
  G[0x0de] = 0;
  G[0x0df] = FUN_00e4a9c0(1);
  G[0x0e0] = FUN_00e4a9c0(0);
  G[0x0e1] = 0;
  G[0x0e2] = FUN_00e4a9c0(0);
  G[0x0e3] = 2;
  G[0x0e4] = 0;
  G[0x0e5] = (int)"digestionTime";
  G[0x0e6] = sHash("digestionTime");
  G[0x0e7] = 0x74;
  G[0x0e8] = 0;
  G[0x0e9] = FUN_00e4a9c0(2);
  G[0x0ea] = FUN_00e4a9c0(0);
  G[0x0eb] = 0;
  G[0x0ec] = FUN_00e4a9c0(0);
  G[0x0ed] = 2;
  G[0x0ee] = 0;
  G[0x0ef] = (int)"digestionOutput";
  G[0x0f0] = sHash("digestionOutput");
  G[0x0f1] = 0x78;
  G[0x0f2] = 0;
  G[0x0f3] = FUN_00e4a9c0(3);
  G[0x0f4] = FUN_00e4a9c0((int)&_DT_LOOT_TABLE_SP__3VcTypeDef_1_B);
  G[0x0f5] = 0;
  G[0x0f6] = FUN_00e4a9c0(0);
  G[0x0f7] = 2;
  G[0x0f8] = 0;
  G[0x0f9] = (int)"fleeTime";
  G[0x0fa] = sHash("fleeTime");
  G[0x0fb] = 0x7c;
  G[0x0fc] = 0;
  G[0x0fd] = FUN_00e4a9c0(2);
  G[0x0fe] = FUN_00e4a9c0(0);
  G[0x0ff] = 0;
  G[0x100] = FUN_00e4a9c0(0x40a00000);
  G[0x101] = 2;
  G[0x102] = 0;
  G[0x103] = (int)"fleeRestTime";
  G[0x104] = sHash("fleeRestTime");
  G[0x105] = 0x80;
  G[0x106] = 0;
  G[0x107] = FUN_00e4a9c0(2);
  G[0x108] = FUN_00e4a9c0(0);
  G[0x109] = 0;
  G[0x10a] = FUN_00e4a9c0(0);
  G[0x10b] = 2;
  G[0x10c] = 0;
  G[0x10d] = (int)"chaseTime";
  G[0x10e] = sHash("chaseTime");
  G[0x10f] = 0x84;
  G[0x110] = 0;
  G[0x111] = FUN_00e4a9c0(2);
  G[0x112] = FUN_00e4a9c0(0);
  G[0x113] = 0;
  G[0x114] = FUN_00e4a9c0(0x461c4000);
  G[0x115] = 2;
  G[0x116] = 0;
  G[0x117] = (int)"chaseRestTime";
  G[0x118] = sHash("chaseRestTime");
  G[0x119] = 0x88;
  G[0x11a] = 0;
  G[0x11b] = FUN_00e4a9c0(2);
  G[0x11c] = FUN_00e4a9c0(0);
  G[0x11d] = 0;
  G[0x11e] = FUN_00e4a9c0(0);
  G[0x11f] = 2;
  G[0x120] = 0;
  G[0x121] = (int)"chasesDamage";
  G[0x122] = sHash("chasesDamage");
  G[0x123] = 0x8c;
  G[0x124] = 0;
  G[0x125] = FUN_00e4a9c0(6);
  G[0x126] = FUN_00e4a9c0(0);
  G[0x127] = 0;
  G[0x128] = FUN_00e4a9c0(1);
  G[0x129] = 2;
  G[0x12a] = 0;
  G[0x12b] = (int)"fearsMouths";
  G[0x12c] = sHash("fearsMouths");
  G[0x12d] = 0x8d;
  G[0x12e] = 0;
  G[0x12f] = FUN_00e4a9c0(6);
  G[0x130] = FUN_00e4a9c0(0);
  G[0x131] = 0;
  G[0x132] = FUN_00e4a9c0(1);
  G[0x133] = 2;
  G[0x134] = 0;
  G[0x135] = (int)"fearsWeapons";
  G[0x136] = sHash("fearsWeapons");
  G[0x137] = 0x8e;
  G[0x138] = 0;
  G[0x139] = FUN_00e4a9c0(6);
  G[0x13a] = FUN_00e4a9c0(0);
  G[0x13b] = 0;
  G[0x13c] = FUN_00e4a9c0(1);
  G[0x13d] = 2;
  G[0x13e] = 0;
  G[0x13f] = (int)"fearsDamage";
  G[0x140] = sHash("fearsDamage");
  G[0x141] = 0x91;
  G[0x142] = 0;
  G[0x143] = FUN_00e4a9c0(6);
  G[0x144] = FUN_00e4a9c0(0);
  G[0x145] = 0;
  G[0x146] = FUN_00e4a9c0(1);
  G[0x147] = 2;
  G[0x148] = 0;
  G[0x149] = (int)"fearsElectric";
  G[0x14a] = sHash("fearsElectric");
  G[0x14b] = 0x8f;
  G[0x14c] = 0;
  G[0x14d] = FUN_00e4a9c0(6);
  G[0x14e] = FUN_00e4a9c0(0);
  G[0x14f] = 0;
  G[0x150] = FUN_00e4a9c0(1);
  G[0x151] = 2;
  G[0x152] = 0;
  G[0x153] = (int)"fearsPoison";
  G[0x154] = sHash("fearsPoison");
  G[0x155] = 0x90;
  G[0x156] = 0;
  G[0x157] = FUN_00e4a9c0(6);
  G[0x158] = FUN_00e4a9c0(0);
  G[0x159] = 0;
  G[0x15a] = FUN_00e4a9c0(1);
  G[0x15b] = 2;
  G[0x15c] = 0;
  G[0x15d] = (int)"ignoresFood";
  G[0x15e] = sHash("ignoresFood");
  G[0x15f] = 0x92;
  G[0x160] = 0;
  G[0x161] = FUN_00e4a9c0(6);
  G[0x162] = FUN_00e4a9c0(0);
  G[0x163] = 0;
  G[0x164] = FUN_00e4a9c0(0);
  G[0x165] = 2;
  G[0x166] = 0;
  G[0x167] = (int)"poisonRecharge";
  G[0x168] = sHash("poisonRecharge");
  G[0x169] = 0xa4;
  G[0x16a] = 0;
  G[0x16b] = FUN_00e4a9c0(2);
  G[0x16c] = FUN_00e4a9c0(0);
  G[0x16d] = 0;
  G[0x16e] = FUN_00e4a9c0(0);
  G[0x16f] = 2;
  G[0x170] = 0;
  G[0x171] = (int)"electricRecharge";
  G[0x172] = sHash("electricRecharge");
  G[0x173] = 0xa8;
  G[0x174] = 0;
  G[0x175] = FUN_00e4a9c0(2);
  G[0x176] = FUN_00e4a9c0(0);
  G[0x177] = 0;
  G[0x178] = FUN_00e4a9c0(0xbf800000);
  G[0x179] = 2;
  G[0x17a] = 0;
  G[0x17b] = (int)"electricRechargeVsSmall";
  G[0x17c] = sHash("electricRechargeVsSmall");
  G[0x17d] = 0xac;
  G[0x17e] = 0;
  G[0x17f] = FUN_00e4a9c0(2);
  G[0x180] = FUN_00e4a9c0(0);
  G[0x181] = 0;
  G[0x182] = FUN_00e4a9c0(0xbf800000);
  G[0x183] = 2;
  G[0x184] = 0;
  G[0x185] = (int)"electricDischarge";
  G[0x186] = sHash("electricDischarge");
  G[0x187] = 0xb0;
  G[0x188] = 0;
  G[0x189] = FUN_00e4a9c0(2);
  G[0x18a] = FUN_00e4a9c0(0);
  G[0x18b] = 0;
  G[0x18c] = FUN_00e4a9c0(0);
  G[0x18d] = 2;
  G[0x18e] = 0;
  G[0x18f] = (int)"awakeTime";
  G[0x190] = sHash("awakeTime");
  G[0x191] = 0x94;
  G[0x192] = 0;
  G[0x193] = FUN_00e4a9c0(2);
  G[0x194] = FUN_00e4a9c0(0);
  G[0x195] = 0;
  G[0x196] = FUN_00e4a9c0(0);
  G[0x197] = 2;
  G[0x198] = 0;
  G[0x199] = (int)"sleepTime";
  G[0x19a] = sHash("sleepTime");
  G[0x19b] = 0x98;
  G[0x19c] = 0;
  G[0x19d] = FUN_00e4a9c0(2);
  G[0x19e] = FUN_00e4a9c0(0);
  G[0x19f] = 0;
  G[0x1a0] = FUN_00e4a9c0(0);
  G[0x1a1] = 2;
  G[0x1a2] = 0;
  G[0x1a3] = (int)"growAmount";
  G[0x1a4] = sHash("growAmount");
  G[0x1a5] = 0x9c;
  G[0x1a6] = 0;
  G[0x1a7] = FUN_00e4a9c0(1);
  G[0x1a8] = FUN_00e4a9c0(0);
  G[0x1a9] = 0;
  G[0x1aa] = FUN_00e4a9c0(1);
  G[0x1ab] = 2;
  G[0x1ac] = 0;
  G[0x1ad] = (int)"hatchDuration";
  G[0x1ae] = sHash("hatchDuration");
  G[0x1af] = 0xa0;
  G[0x1b0] = 0;
  G[0x1b1] = FUN_00e4a9c0(2);
  G[0x1b2] = FUN_00e4a9c0(0);
  G[0x1b3] = 0;
  G[0x1b4] = FUN_00e4a9c0(0x41200000);
  G[0x1b5] = 2;
  G[0x1b6] = 0;
  G[0x1b7] = (int)"fearsNearbyDamageRadius";
  G[0x1b8] = sHash("fearsNearbyDamageRadius");
  G[0x1b9] = 0x28;
  G[0x1ba] = 0;
  G[0x1bb] = FUN_00e4a9c0(2);
  G[0x1bc] = FUN_00e4a9c0(0);
  G[0x1bd] = 0;
  G[0x1be] = FUN_00e4a9c0(0);
  G[0x1bf] = 2;
  G[0x1c0] = 0;
  G[0x1c1] = (int)"fearsNearbyDeathRadius";
  G[0x1c2] = sHash("fearsNearbyDeathRadius");
  G[0x1c3] = 0x2c;
  G[0x1c4] = 0;
  G[0x1c5] = FUN_00e4a9c0(2);
  G[0x1c6] = FUN_00e4a9c0(0);
  G[0x1c7] = 0;
  G[0x1c8] = FUN_00e4a9c0(0);
  G[0x1c9] = 2;
  G[0x1ca] = 0;
  G[0x1cb] = (int)"fearsNearbyDamageTime";
  G[0x1cc] = sHash("fearsNearbyDamageTime");
  G[0x1cd] = 0x30;
  G[0x1ce] = 0;
  G[0x1cf] = FUN_00e4a9c0(2);
  G[0x1d0] = FUN_00e4a9c0(0);
  G[0x1d1] = 0;
  G[0x1d2] = FUN_00e4a9c0(0);
  G[0x1d3] = 2;
  G[0x1d4] = 0;
  G[0x1d5] = (int)"fearsNearbyDeathTime";
  G[0x1d6] = sHash("fearsNearbyDeathTime");
  G[0x1d7] = 0x34;
  G[0x1d8] = 0;
  G[0x1d9] = FUN_00e4a9c0(2);
  G[0x1da] = FUN_00e4a9c0(0);
  G[0x1db] = 0;
  G[0x1dc] = FUN_00e4a9c0(0);
  G[0x1dd] = 2;
  G[0x1de] = 0;
  G[0x1df] = (int)"protectRadius";
  G[0x1e0] = sHash("protectRadius");
  G[0x1e1] = 0x38;
  G[0x1e2] = 0;
  G[0x1e3] = FUN_00e4a9c0(2);
  G[0x1e4] = FUN_00e4a9c0(0);
  G[0x1e5] = 0;
  G[0x1e6] = FUN_00e4a9c0(0);
  G[0x1e7] = 2;
  G[0x1e8] = 0;
  G[0x1e9] = (int)"protectTime";
  G[0x1ea] = sHash("protectTime");
  G[0x1eb] = 0x3c;
  G[0x1ec] = 0;
  G[0x1ed] = FUN_00e4a9c0(2);
  G[0x1ee] = FUN_00e4a9c0(0);
  G[0x1ef] = 0;
  G[0x1f0] = FUN_00e4a9c0(0);
  G[0x1f1] = 2;
  G[0x1f2] = 0;
  G[0x1f3] = 0;
  G[0x1f4] = sHash(0);
  G[0x1f5] = 0xffffffff;
  G[0x1f6] = 0;
  G[0x1f7] = FUN_00e4a9c0(0);
  G[0x1f8] = FUN_00e4a9c0(0);
  G[0x1f9] = 0;
  G[0x1fa] = FUN_00e4a9c0(0);
  G[0x1fb] = 0;
  G[0x1fc] = 0;
}

// @ 0x01376cc0
void InitPropTable_16b277c(void)
{
    g_16b277c[0].hash = SP_sHash(0);          g_16b277c[0].offset = 0x14;  g_16b277c[0].auxOffset = 0;
    g_16b277c[0].type = Conv(1);              g_16b277c[0].typeDesc = Conv(0);
    g_16b277c[0].argIndex = 0;                g_16b277c[0].defaultValue = Conv(0);
    g_16b277c[0].flags = 8;                   g_16b277c[0].enumTable = 0;  g_16b277c[0].name = 0;

    g_16b277c[1].hash = SP_sHash(0);          g_16b277c[1].offset = 0x28;  g_16b277c[1].auxOffset = 0;
    g_16b277c[1].type = Conv(1);              g_16b277c[1].typeDesc = Conv(0);
    g_16b277c[1].argIndex = 0;                g_16b277c[1].defaultValue = Conv(3);
    g_16b277c[1].flags = 8;                   g_16b277c[1].enumTable = 0;  g_16b277c[1].name = 0;

    g_16b277c[2].hash = SP_sHash(0);          g_16b277c[2].offset = 0x20;  g_16b277c[2].auxOffset = 0;
    g_16b277c[2].type = Conv(3);              g_16b277c[2].typeDesc = Conv((int)&g_ctPopulation);
    g_16b277c[2].argIndex = 0;                g_16b277c[2].defaultValue = Conv(0);
    g_16b277c[2].flags = 0;                   g_16b277c[2].enumTable = 0;
    g_16b277c[2].name = "encounterScale";

    g_16b277c[3].hash = SP_sHash("encounterScale"); g_16b277c[3].offset = 0x48; g_16b277c[3].auxOffset = 0;
    g_16b277c[3].type = Conv(2);              g_16b277c[3].typeDesc = Conv(0);
    g_16b277c[3].argIndex = 0;                g_16b277c[3].defaultValue = ConvF(0.5f);
    g_16b277c[3].flags = 2;                   g_16b277c[3].enumTable = 0;
    g_16b277c[3].name = "count";

    g_16b277c[4].hash = SP_sHash("count");    g_16b277c[4].offset = 0x2c;  g_16b277c[4].auxOffset = 0;
    g_16b277c[4].type = Conv(2);              g_16b277c[4].typeDesc = Conv(0);
    g_16b277c[4].argIndex = 0;                g_16b277c[4].defaultValue = ConvF(-1.0f);
    g_16b277c[4].flags = 2;                   g_16b277c[4].enumTable = 0;
    g_16b277c[4].name = "count_med";

    g_16b277c[5].hash = SP_sHash("count_med"); g_16b277c[5].offset = 0x34; g_16b277c[5].auxOffset = 0;
    g_16b277c[5].type = Conv(2);              g_16b277c[5].typeDesc = Conv(0);
    g_16b277c[5].argIndex = 0;                g_16b277c[5].defaultValue = ConvF(-1.0f);
    g_16b277c[5].flags = 2;                   g_16b277c[5].enumTable = 0;
    g_16b277c[5].name = "count_easy";

    g_16b277c[6].hash = SP_sHash("count_easy"); g_16b277c[6].offset = 0x30; g_16b277c[6].auxOffset = 0;
    g_16b277c[6].type = Conv(2);              g_16b277c[6].typeDesc = Conv(0);
    g_16b277c[6].argIndex = 0;                g_16b277c[6].defaultValue = ConvF(-1.0f);
    g_16b277c[6].flags = 2;                   g_16b277c[6].enumTable = 0;
    g_16b277c[6].name = "count_hard";

    g_16b277c[7].hash = SP_sHash("count_hard"); g_16b277c[7].offset = 0x38; g_16b277c[7].auxOffset = 0;
    g_16b277c[7].type = Conv(2);              g_16b277c[7].typeDesc = Conv(0);
    g_16b277c[7].argIndex = 0;                g_16b277c[7].defaultValue = ConvF(-1.0f);
    g_16b277c[7].flags = 2;                   g_16b277c[7].enumTable = 0;  g_16b277c[7].name = 0;

    g_16b277c[8].hash = SP_sHash(0);          g_16b277c[8].offset = -1;    g_16b277c[8].auxOffset = 0;
    g_16b277c[8].type = Conv(0);              g_16b277c[8].typeDesc = Conv(0);
    g_16b277c[8].argIndex = 0;                g_16b277c[8].defaultValue = Conv(0);
    g_16b277c[8].flags = 0;                   g_16b277c[8].enumTable = 0;
}

// @ 0x013774e0
void InitPropTable_16b222c(void)
{
    g_16b222c[0].hash = SP_sHash(0);          g_16b222c[0].offset = 0x14;  g_16b222c[0].auxOffset = 0;
    g_16b222c[0].type = Conv(1);              g_16b222c[0].typeDesc = Conv(0);
    g_16b222c[0].argIndex = 0;                g_16b222c[0].defaultValue = Conv(0);
    g_16b222c[0].flags = 8;                   g_16b222c[0].enumTable = 0;   g_16b222c[0].name = 0;

    g_16b222c[1].hash = SP_sHash(0);          g_16b222c[1].offset = 0x28;  g_16b222c[1].auxOffset = 0;
    g_16b222c[1].type = Conv(1);              g_16b222c[1].typeDesc = Conv(0);
    g_16b222c[1].argIndex = 0;                g_16b222c[1].defaultValue = Conv(1);
    g_16b222c[1].flags = 8;                   g_16b222c[1].enumTable = 0;   g_16b222c[1].name = 0;

    g_16b222c[2].hash = SP_sHash(0);          g_16b222c[2].offset = 0x1c;  g_16b222c[2].auxOffset = 0;
    g_16b222c[2].type = Conv(3);              g_16b222c[2].typeDesc = Conv((int)&g_dtCell);
    g_16b222c[2].argIndex = 0;                g_16b222c[2].defaultValue = Conv(0);
    g_16b222c[2].flags = 0;                   g_16b222c[2].enumTable = 0;   g_16b222c[2].name = "parts";

    g_16b222c[3].hash = SP_sHash("parts");    g_16b222c[3].offset = 0x40;  g_16b222c[3].auxOffset = 0;
    g_16b222c[3].type = Conv(1);              g_16b222c[3].typeDesc = Conv(0);
    g_16b222c[3].argIndex = 0;                g_16b222c[3].defaultValue = Conv(5);
    g_16b222c[3].flags = 2;                   g_16b222c[3].enumTable = 0;   g_16b222c[3].name = "count";

    g_16b222c[4].hash = SP_sHash("count");    g_16b222c[4].offset = 0x2c;  g_16b222c[4].auxOffset = 0;
    g_16b222c[4].type = Conv(2);              g_16b222c[4].typeDesc = Conv(0);
    g_16b222c[4].argIndex = 0;                g_16b222c[4].defaultValue = ConvF(-1.0f);
    g_16b222c[4].flags = 2;                   g_16b222c[4].enumTable = 0;   g_16b222c[4].name = "count_med";

    g_16b222c[5].hash = SP_sHash("count_med"); g_16b222c[5].offset = 0x34; g_16b222c[5].auxOffset = 0;
    g_16b222c[5].type = Conv(2);              g_16b222c[5].typeDesc = Conv(0);
    g_16b222c[5].argIndex = 0;                g_16b222c[5].defaultValue = ConvF(-1.0f);
    g_16b222c[5].flags = 2;                   g_16b222c[5].enumTable = 0;   g_16b222c[5].name = "count_easy";

    g_16b222c[6].hash = SP_sHash("count_easy"); g_16b222c[6].offset = 0x30; g_16b222c[6].auxOffset = 0;
    g_16b222c[6].type = Conv(2);              g_16b222c[6].typeDesc = Conv(0);
    g_16b222c[6].argIndex = 0;                g_16b222c[6].defaultValue = ConvF(-1.0f);
    g_16b222c[6].flags = 2;                   g_16b222c[6].enumTable = 0;   g_16b222c[6].name = "count_hard";

    g_16b222c[7].hash = SP_sHash("count_hard"); g_16b222c[7].offset = 0x38; g_16b222c[7].auxOffset = 0;
    g_16b222c[7].type = Conv(2);              g_16b222c[7].typeDesc = Conv(0);
    g_16b222c[7].argIndex = 0;                g_16b222c[7].defaultValue = ConvF(-1.0f);
    g_16b222c[7].flags = 2;                   g_16b222c[7].enumTable = 0;   g_16b222c[7].name = "size";

    g_16b222c[8].hash = SP_sHash("size");     g_16b222c[8].offset = 0x3c;  g_16b222c[8].auxOffset = 0;
    g_16b222c[8].type = Conv(5);              g_16b222c[8].typeDesc = Conv(0);
    g_16b222c[8].argIndex = 0;                g_16b222c[8].defaultValue = Conv(1);
    g_16b222c[8].flags = 2;                   g_16b222c[8].enumTable = (int)&g_kTilings;
    g_16b222c[8].name = "zOffset";

    g_16b222c[9].hash = SP_sHash("zOffset");  g_16b222c[9].offset = 0xc;   g_16b222c[9].auxOffset = 0;
    g_16b222c[9].type = Conv(2);              g_16b222c[9].typeDesc = Conv(0);
    g_16b222c[9].argIndex = 0;                g_16b222c[9].defaultValue = ConvF(0.0f);
    g_16b222c[9].flags = 2;                   g_16b222c[9].enumTable = 0;   g_16b222c[9].name = "zOffsetMax";

    g_16b222c[10].hash = SP_sHash("zOffsetMax"); g_16b222c[10].offset = 0x10; g_16b222c[10].auxOffset = 0;
    g_16b222c[10].type = Conv(2);             g_16b222c[10].typeDesc = Conv(0);
    g_16b222c[10].argIndex = 0;               g_16b222c[10].defaultValue = ConvF(0.0f);
    g_16b222c[10].flags = 2;                  g_16b222c[10].enumTable = 0;  g_16b222c[10].name = "linear";

    g_16b222c[11].hash = SP_sHash("linear");  g_16b222c[11].offset = 0x44; g_16b222c[11].auxOffset = 0;
    g_16b222c[11].type = Conv(6);             g_16b222c[11].typeDesc = Conv(0);
    g_16b222c[11].argIndex = 0;               g_16b222c[11].defaultValue = Conv(0);
    g_16b222c[11].flags = 2;                  g_16b222c[11].enumTable = 0;  g_16b222c[11].name = 0;

    g_16b222c[12].hash = SP_sHash(0);         g_16b222c[12].offset = -1;   g_16b222c[12].auxOffset = 0;
    g_16b222c[12].type = Conv(0);             g_16b222c[12].typeDesc = Conv(0);
    g_16b222c[12].argIndex = 0;               g_16b222c[12].defaultValue = Conv(0);
    g_16b222c[12].flags = 0;                  g_16b222c[12].enumTable = 0;
}

// @ 0x01377a10
void InitPropTable_15a77cc(void)
{
    g_15a77cc[0].hash = SP_sHash("scale");    g_15a77cc[0].offset = 0;     g_15a77cc[0].auxOffset = 0;
    g_15a77cc[0].type = Conv(5);              g_15a77cc[0].typeDesc = Conv(0);
    g_15a77cc[0].argIndex = 0;                g_15a77cc[0].defaultValue = Conv(0);
    g_15a77cc[0].flags = 4;                   g_15a77cc[0].enumTable = (int)&g_kTilings;
    g_15a77cc[0].name = "maskTexture";

    g_15a77cc[1].hash = SP_sHash("maskTexture"); g_15a77cc[1].offset = 4;  g_15a77cc[1].auxOffset = 4;
    g_15a77cc[1].type = Conv(7);              g_15a77cc[1].typeDesc = Conv(0);
    g_15a77cc[1].argIndex = 0;                g_15a77cc[1].defaultValue = Conv(0);
    g_15a77cc[1].flags = 6;                   g_15a77cc[1].enumTable = 0;   g_15a77cc[1].name = "distribute";

    g_15a77cc[2].hash = SP_sHash("distribute"); g_15a77cc[2].offset = 0xc; g_15a77cc[2].auxOffset = 8;
    g_15a77cc[2].type = Conv((int)&g_dtDistribute); g_15a77cc[2].typeDesc = Conv(4);
    g_15a77cc[2].argIndex = 0;                g_15a77cc[2].defaultValue = Conv(0);
    g_15a77cc[2].flags = 4;                   g_15a77cc[2].enumTable = 0;   g_15a77cc[2].name = "cluster";

    g_15a77cc[3].hash = SP_sHash("cluster");  g_15a77cc[3].offset = 0xc;   g_15a77cc[3].auxOffset = 8;
    g_15a77cc[3].type = Conv((int)&g_dtCluster); g_15a77cc[3].typeDesc = Conv(4);
    g_15a77cc[3].argIndex = 0;                g_15a77cc[3].defaultValue = Conv(0);
    g_15a77cc[3].flags = 4;                   g_15a77cc[3].enumTable = 0;   g_15a77cc[3].name = "plant";

    g_15a77cc[4].hash = SP_sHash("plant");    g_15a77cc[4].offset = 0xc;   g_15a77cc[4].auxOffset = 8;
    g_15a77cc[4].type = Conv((int)&g_dtPlant); g_15a77cc[4].typeDesc = Conv(4);
    g_15a77cc[4].argIndex = 0;                g_15a77cc[4].defaultValue = Conv(0);
    g_15a77cc[4].flags = 4;                   g_15a77cc[4].enumTable = 0;   g_15a77cc[4].name = "encounter";

    g_15a77cc[5].hash = SP_sHash("encounter"); g_15a77cc[5].offset = 0xc;  g_15a77cc[5].auxOffset = 8;
    g_15a77cc[5].type = Conv((int)&g_dtEncounter); g_15a77cc[5].typeDesc = Conv(4);
    g_15a77cc[5].argIndex = 0;                g_15a77cc[5].defaultValue = Conv(0);
    g_15a77cc[5].flags = 4;                   g_15a77cc[5].enumTable = 0;   g_15a77cc[5].name = 0;

    g_15a77cc[6].hash = SP_sHash(0);          g_15a77cc[6].offset = -1;    g_15a77cc[6].auxOffset = 0;
    g_15a77cc[6].type = Conv(0);              g_15a77cc[6].typeDesc = Conv(0);
    g_15a77cc[6].argIndex = 0;                g_15a77cc[6].defaultValue = Conv(0);
    g_15a77cc[6].flags = 0;                   g_15a77cc[6].enumTable = 0;
}

// @ 0x01377cf0
void InitPropTable_16b2e0c(void)
{
    g_16b2e0c[0].hash = SP_sHash(0);          g_16b2e0c[0].offset = 0;     g_16b2e0c[0].auxOffset = 0;
    g_16b2e0c[0].type = Conv(3);              g_16b2e0c[0].typeDesc = Conv((int)&g_dtPopulation);
    g_16b2e0c[0].argIndex = 0;                g_16b2e0c[0].defaultValue = Conv(0);
    g_16b2e0c[0].flags = 0;                   g_16b2e0c[0].enumTable = 0;   g_16b2e0c[0].name = "startTile";

    g_16b2e0c[1].hash = SP_sHash("startTile"); g_16b2e0c[1].offset = 4;    g_16b2e0c[1].auxOffset = 0;
    g_16b2e0c[1].type = Conv(6);              g_16b2e0c[1].typeDesc = Conv(0);
    g_16b2e0c[1].argIndex = 0;                g_16b2e0c[1].defaultValue = Conv(0);
    g_16b2e0c[1].flags = 2;                   g_16b2e0c[1].enumTable = 0;   g_16b2e0c[1].name = "playerSize";

    g_16b2e0c[2].hash = SP_sHash("playerSize"); g_16b2e0c[2].offset = 8;   g_16b2e0c[2].auxOffset = 0;
    g_16b2e0c[2].type = Conv(5);              g_16b2e0c[2].typeDesc = Conv(0);
    g_16b2e0c[2].argIndex = 0;                g_16b2e0c[2].defaultValue = Conv(-1);
    g_16b2e0c[2].flags = 2;                   g_16b2e0c[2].enumTable = (int)&g_kTilings;
    g_16b2e0c[2].name = 0;

    g_16b2e0c[3].hash = SP_sHash(0);          g_16b2e0c[3].offset = -1;    g_16b2e0c[3].auxOffset = 0;
    g_16b2e0c[3].type = Conv(0);              g_16b2e0c[3].typeDesc = Conv(0);
    g_16b2e0c[3].argIndex = 0;                g_16b2e0c[3].defaultValue = Conv(0);
    g_16b2e0c[3].flags = 0;                   g_16b2e0c[3].enumTable = 0;
}

// @ 0x01377ec0
void InitPropTable_16b209c(void)
{
    g_16b209c[0].hash = SP_sHash(0);          g_16b209c[0].offset = 0;     g_16b209c[0].auxOffset = 0;
    g_16b209c[0].type = Conv(5);              g_16b209c[0].typeDesc = Conv(0);
    g_16b209c[0].argIndex = 0;                g_16b209c[0].defaultValue = Conv(0);
    g_16b209c[0].flags = 0;                   g_16b209c[0].enumTable = (int)&g_kTilings;
    g_16b209c[0].name = 0;

    g_16b209c[1].hash = SP_sHash(0);          g_16b209c[1].offset = 0x14;  g_16b209c[1].auxOffset = 0x14;
    g_16b209c[1].type = Conv(7);              g_16b209c[1].typeDesc = Conv(0);
    g_16b209c[1].argIndex = 1;                g_16b209c[1].defaultValue = Conv(0);
    g_16b209c[1].flags = 0;                   g_16b209c[1].enumTable = 0;   g_16b209c[1].name = "playerSize";

    g_16b209c[2].hash = SP_sHash("playerSize"); g_16b209c[2].offset = 4;   g_16b209c[2].auxOffset = 0;
    g_16b209c[2].type = Conv(5);              g_16b209c[2].typeDesc = Conv(0);
    g_16b209c[2].argIndex = 0;                g_16b209c[2].defaultValue = Conv(-1);
    g_16b209c[2].flags = 2;                   g_16b209c[2].enumTable = (int)&g_kTilings;
    g_16b209c[2].name = "strength";

    g_16b209c[3].hash = SP_sHash("strength"); g_16b209c[3].offset = 8;    g_16b209c[3].auxOffset = 0;
    g_16b209c[3].type = Conv(2);              g_16b209c[3].typeDesc = Conv(0);
    g_16b209c[3].argIndex = 0;                g_16b209c[3].defaultValue = ConvF(3.5f);
    g_16b209c[3].flags = 2;                   g_16b209c[3].enumTable = 0;   g_16b209c[3].name = "variance";

    g_16b209c[4].hash = SP_sHash("variance"); g_16b209c[4].offset = 0xc;  g_16b209c[4].auxOffset = 0;
    g_16b209c[4].type = Conv(2);              g_16b209c[4].typeDesc = Conv(0);
    g_16b209c[4].argIndex = 0;                g_16b209c[4].defaultValue = ConvF(0.0f);
    g_16b209c[4].flags = 2;                   g_16b209c[4].enumTable = 0;   g_16b209c[4].name = "period";

    g_16b209c[5].hash = SP_sHash("period");   g_16b209c[5].offset = 0x10;  g_16b209c[5].auxOffset = 0;
    g_16b209c[5].type = Conv(2);              g_16b209c[5].typeDesc = Conv(0);
    g_16b209c[5].argIndex = 0;                g_16b209c[5].defaultValue = ConvF(1.0f);
    g_16b209c[5].flags = 2;                   g_16b209c[5].enumTable = 0;   g_16b209c[5].name = 0;

    g_16b209c[6].hash = SP_sHash(0);          g_16b209c[6].offset = -1;    g_16b209c[6].auxOffset = 0;
    g_16b209c[6].type = Conv(0);              g_16b209c[6].typeDesc = Conv(0);
    g_16b209c[6].argIndex = 0;                g_16b209c[6].defaultValue = Conv(0);
    g_16b209c[6].flags = 0;                   g_16b209c[6].enumTable = 0;
}

// @ 0x013781a0
void InitPropTable_15a7754(void)
{
    g_15a7754[0].hash = SP_sHash("populate"); g_15a7754[0].offset = 4;    g_15a7754[0].auxOffset = 0;
    g_15a7754[0].type = Conv((int)&g_dtLevelEntry); g_15a7754[0].typeDesc = Conv(4);
    g_15a7754[0].argIndex = 0;                g_15a7754[0].defaultValue = Conv(0);
    g_15a7754[0].flags = 4;                   g_15a7754[0].enumTable = 0;   g_15a7754[0].name = "advect";

    g_15a7754[1].hash = SP_sHash("advect");   g_15a7754[1].offset = 0xc;   g_15a7754[1].auxOffset = 8;
    g_15a7754[1].type = Conv((int)&g_dtAdvectEntry); g_15a7754[1].typeDesc = Conv(4);
    g_15a7754[1].argIndex = 0;                g_15a7754[1].defaultValue = Conv(0);
    g_15a7754[1].flags = 4;                   g_15a7754[1].enumTable = 0;   g_15a7754[1].name = 0;

    g_15a7754[2].hash = SP_sHash(0);          g_15a7754[2].offset = -1;    g_15a7754[2].auxOffset = 0;
    g_15a7754[2].type = Conv(0);              g_15a7754[2].typeDesc = Conv(0);
    g_15a7754[2].argIndex = 0;                g_15a7754[2].defaultValue = Conv(0);
    g_15a7754[2].flags = 0;                   g_15a7754[2].enumTable = 0;
}

// @ 0x01378300
void InitPropTable_16b1bc4(void)
{
    g_16b1bc4[0].hash = SP_sHash(0);          g_16b1bc4[0].offset = 0;     g_16b1bc4[0].auxOffset = 0;
    g_16b1bc4[0].type = Conv(1);              g_16b1bc4[0].typeDesc = Conv(0);
    g_16b1bc4[0].argIndex = 0;                g_16b1bc4[0].defaultValue = Conv(0);
    g_16b1bc4[0].flags = 8;                   g_16b1bc4[0].enumTable = 0;   g_16b1bc4[0].name = 0;

    g_16b1bc4[1].hash = SP_sHash(0);          g_16b1bc4[1].offset = 4;     g_16b1bc4[1].auxOffset = 0;
    g_16b1bc4[1].type = Conv(2);              g_16b1bc4[1].typeDesc = Conv(0);
    g_16b1bc4[1].argIndex = 0;                g_16b1bc4[1].defaultValue = Conv(0);
    g_16b1bc4[1].flags = 0;                   g_16b1bc4[1].enumTable = 0;   g_16b1bc4[1].name = 0;

    g_16b1bc4[2].hash = SP_sHash(0);          g_16b1bc4[2].offset = -1;    g_16b1bc4[2].auxOffset = 0;
    g_16b1bc4[2].type = Conv(0);              g_16b1bc4[2].typeDesc = Conv(0);
    g_16b1bc4[2].argIndex = 0;                g_16b1bc4[2].defaultValue = Conv(0);
    g_16b1bc4[2].flags = 0;                   g_16b1bc4[2].enumTable = 0;
}

// @ 0x013792c0
void InitPropTable_15a68b4(void)
{
    g_15a68b4[0].hash = SP_sHash((const char*)0x01435f20);
    g_15a68b4[0].f04 = 0;
    g_15a68b4[0].f08 = 4;
    g_15a68b4[0].f0c = PropValI(0x016b0dac);
    g_15a68b4[0].f10 = PropValI(4);
    g_15a68b4[0].f14 = 0;
    g_15a68b4[0].f18 = PropValI(0);
    g_15a68b4[0].f1c = 4;
    g_15a68b4[0].f20 = 0;
    g_15a68b4[0].f24 = 0x0145511c;

    g_15a68b4[1].hash = SP_sHash((const char*)0x0145511c);
    g_15a68b4[1].f04 = 0;
    g_15a68b4[1].f08 = 4;
    g_15a68b4[1].f0c = PropValI(0x016ad5b8);
    g_15a68b4[1].f10 = PropValI(4);
    g_15a68b4[1].f14 = 0;
    g_15a68b4[1].f18 = PropValI(0);
    g_15a68b4[1].f1c = 4;
    g_15a68b4[1].f20 = 0;
    g_15a68b4[1].f24 = 0x0142ed24;

    g_15a68b4[2].hash = SP_sHash((const char*)0x0142ed24);
    g_15a68b4[2].f04 = 0;
    g_15a68b4[2].f08 = 4;
    g_15a68b4[2].f0c = PropValI(0x016b0e44);
    g_15a68b4[2].f10 = PropValI(4);
    g_15a68b4[2].f14 = 0;
    g_15a68b4[2].f18 = PropValI(0);
    g_15a68b4[2].f1c = 4;
    g_15a68b4[2].f20 = 0;
    g_15a68b4[2].f24 = 0x0142ed14;

    g_15a68b4[3].hash = SP_sHash((const char*)0x0142ed14);
    g_15a68b4[3].f04 = 0;
    g_15a68b4[3].f08 = 4;
    g_15a68b4[3].f0c = PropValI(0x016ad58c);
    g_15a68b4[3].f10 = PropValI(4);
    g_15a68b4[3].f14 = 0;
    g_15a68b4[3].f18 = PropValI(0);
    g_15a68b4[3].f1c = 4;
    g_15a68b4[3].f20 = 0;
    g_15a68b4[3].f24 = 0x0148345c;

    g_15a68b4[4].hash = SP_sHash((const char*)0x0148345c);
    g_15a68b4[4].f04 = 0;
    g_15a68b4[4].f08 = 4;
    g_15a68b4[4].f0c = PropValI(0x016b0f10);
    g_15a68b4[4].f10 = PropValI(4);
    g_15a68b4[4].f14 = 0;
    g_15a68b4[4].f18 = PropValI(0);
    g_15a68b4[4].f1c = 4;
    g_15a68b4[4].f20 = 0;
    g_15a68b4[4].f24 = 0x01483450;

    g_15a68b4[5].hash = SP_sHash((const char*)0x01483450);
    g_15a68b4[5].f04 = 0;
    g_15a68b4[5].f08 = 4;
    g_15a68b4[5].f0c = PropValI(0x016b0b04);
    g_15a68b4[5].f10 = PropValI(4);
    g_15a68b4[5].f14 = 0;
    g_15a68b4[5].f18 = PropValI(0);
    g_15a68b4[5].f1c = 4;
    g_15a68b4[5].f20 = 0;
    g_15a68b4[5].f24 = 0x0145a568;

    g_15a68b4[6].hash = SP_sHash((const char*)0x0145a568);
    g_15a68b4[6].f04 = 0;
    g_15a68b4[6].f08 = 4;
    g_15a68b4[6].f0c = PropValI(0x016b0b30);
    g_15a68b4[6].f10 = PropValI(4);
    g_15a68b4[6].f14 = 0;
    g_15a68b4[6].f18 = PropValI(0);
    g_15a68b4[6].f1c = 4;
    g_15a68b4[6].f20 = 0;
    g_15a68b4[6].f24 = 0x01483154;

    g_15a68b4[7].hash = SP_sHash((const char*)0x01483154);
    g_15a68b4[7].f04 = 0;
    g_15a68b4[7].f08 = 4;
    g_15a68b4[7].f0c = PropValI(0x016ad560);
    g_15a68b4[7].f10 = PropValI(4);
    g_15a68b4[7].f14 = 0;
    g_15a68b4[7].f18 = PropValI(0);
    g_15a68b4[7].f1c = 4;
    g_15a68b4[7].f20 = 0;
    g_15a68b4[7].f24 = 0x01483444;

    g_15a68b4[8].hash = SP_sHash((const char*)0x01483444);
    g_15a68b4[8].f04 = 0;
    g_15a68b4[8].f08 = 4;
    g_15a68b4[8].f0c = PropValI(0x016b0c78);
    g_15a68b4[8].f10 = PropValI(4);
    g_15a68b4[8].f14 = 0;
    g_15a68b4[8].f18 = PropValI(0);
    g_15a68b4[8].f1c = 4;
    g_15a68b4[8].f20 = 0;
    g_15a68b4[8].f24 = 0x01483438;

    g_15a68b4[9].hash = SP_sHash((const char*)0x01483438);
    g_15a68b4[9].f04 = 0;
    g_15a68b4[9].f08 = 4;
    g_15a68b4[9].f0c = PropValI(0x016b0e7c);
    g_15a68b4[9].f10 = PropValI(4);
    g_15a68b4[9].f14 = 0;
    g_15a68b4[9].f18 = PropValI(0);
    g_15a68b4[9].f1c = 4;
    g_15a68b4[9].f20 = 0;
    g_15a68b4[9].f24 = 0x01483430;

    g_15a68b4[10].hash = SP_sHash((const char*)0x01483430);
    g_15a68b4[10].f04 = 0;
    g_15a68b4[10].f08 = 4;
    g_15a68b4[10].f0c = PropValI(0x016b0e18);
    g_15a68b4[10].f10 = PropValI(4);
    g_15a68b4[10].f14 = 0;
    g_15a68b4[10].f18 = PropValI(0);
    g_15a68b4[10].f1c = 4;
    g_15a68b4[10].f20 = 0;
    g_15a68b4[10].f24 = 0x01482758;

    g_15a68b4[11].hash = SP_sHash((const char*)0x01482758);
    g_15a68b4[11].f04 = 0;
    g_15a68b4[11].f08 = 4;
    g_15a68b4[11].f0c = PropValI(0x016b0c10);
    g_15a68b4[11].f10 = PropValI(4);
    g_15a68b4[11].f14 = 0;
    g_15a68b4[11].f18 = PropValI(0);
    g_15a68b4[11].f1c = 4;
    g_15a68b4[11].f20 = 0;
    g_15a68b4[11].f24 = 0;

    g_15a68b4[12].hash = SP_sHash(0);
    g_15a68b4[12].f04 = 0xffffffff;
    g_15a68b4[12].f08 = 0;
    g_15a68b4[12].f0c = PropValI(0);
    g_15a68b4[12].f10 = PropValI(0);
    g_15a68b4[12].f14 = 0;
    g_15a68b4[12].f18 = PropValI(0);
    g_15a68b4[12].f1c = 0;
    g_15a68b4[12].f20 = 0;
}

// @ 0x01379970
void InitPropTable_16b1a0c(void)
{
    g_16b1a0c[0].hash = SP_sHash(0);
    g_16b1a0c[0].f04 = 0;
    g_16b1a0c[0].f08 = 0;
    g_16b1a0c[0].f0c = PropValI(5);
    g_16b1a0c[0].f10 = PropValI(0);
    g_16b1a0c[0].f14 = 0;
    g_16b1a0c[0].f18 = PropValI(1);
    g_16b1a0c[0].f1c = 8;
    g_16b1a0c[0].f20 = 0;
    g_16b1a0c[0].f24 = 0x01482f10;

    g_16b1a0c[1].hash = SP_sHash((const char*)0x01482f10);
    g_16b1a0c[1].f04 = 8;
    g_16b1a0c[1].f08 = 0;
    g_16b1a0c[1].f0c = PropValI(2);
    g_16b1a0c[1].f10 = PropValI(0);
    g_16b1a0c[1].f14 = 0;
    g_16b1a0c[1].f18 = PropValF(1.0f);
    g_16b1a0c[1].f1c = 2;
    g_16b1a0c[1].f20 = 0;
    g_16b1a0c[1].f24 = 0x014834a8;

    g_16b1a0c[2].hash = SP_sHash((const char*)0x014834a8);
    g_16b1a0c[2].f04 = 0xc;
    g_16b1a0c[2].f08 = 0;
    g_16b1a0c[2].f0c = PropValI(1);
    g_16b1a0c[2].f10 = PropValI(0);
    g_16b1a0c[2].f14 = 0;
    g_16b1a0c[2].f18 = PropValI(-1);
    g_16b1a0c[2].f1c = 2;
    g_16b1a0c[2].f20 = 0;
    g_16b1a0c[2].f24 = 0x0148349c;

    g_16b1a0c[3].hash = SP_sHash((const char*)0x0148349c);
    g_16b1a0c[3].f04 = 0x10;
    g_16b1a0c[3].f08 = 0;
    g_16b1a0c[3].f0c = PropValI(1);
    g_16b1a0c[3].f10 = PropValI(0);
    g_16b1a0c[3].f14 = 0;
    g_16b1a0c[3].f18 = PropValI(-1);
    g_16b1a0c[3].f1c = 2;
    g_16b1a0c[3].f20 = 0;
    g_16b1a0c[3].f24 = 0x01483490;

    g_16b1a0c[4].hash = SP_sHash((const char*)0x01483490);
    g_16b1a0c[4].f04 = 0x14;
    g_16b1a0c[4].f08 = 0;
    g_16b1a0c[4].f0c = PropValI(1);
    g_16b1a0c[4].f10 = PropValI(0);
    g_16b1a0c[4].f14 = 0;
    g_16b1a0c[4].f18 = PropValI(-1);
    g_16b1a0c[4].f1c = 2;
    g_16b1a0c[4].f20 = 0;
    g_16b1a0c[4].f24 = 0x01483484;

    g_16b1a0c[5].hash = SP_sHash((const char*)0x01483484);
    g_16b1a0c[5].f04 = 0x18;
    g_16b1a0c[5].f08 = 0;
    g_16b1a0c[5].f0c = PropValI(1);
    g_16b1a0c[5].f10 = PropValI(0);
    g_16b1a0c[5].f14 = 0;
    g_16b1a0c[5].f18 = PropValI(-1);
    g_16b1a0c[5].f1c = 2;
    g_16b1a0c[5].f20 = 0;
    g_16b1a0c[5].f24 = 0;

    g_16b1a0c[6].hash = SP_sHash(0);
    g_16b1a0c[6].f04 = 0xffffffff;
    g_16b1a0c[6].f08 = 0;
    g_16b1a0c[6].f0c = PropValI(0);
    g_16b1a0c[6].f10 = PropValI(0);
    g_16b1a0c[6].f14 = 0;
    g_16b1a0c[6].f18 = PropValI(0);
    g_16b1a0c[6].f1c = 0;
    g_16b1a0c[6].f20 = 0;
}

// @ 0x01379c40
void InitPropTable_15a78e4(void)
{
    g_15a78e4[0].hash = SP_sHash((const char*)0x0145ed30);
    g_15a78e4[0].f04 = 4;
    g_15a78e4[0].f08 = 0;
    g_15a78e4[0].f0c = PropValI(0x016b0c4c);
    g_15a78e4[0].f10 = PropValI(4);
    g_15a78e4[0].f14 = 0;
    g_15a78e4[0].f18 = PropValI(0);
    g_15a78e4[0].f1c = 4;
    g_15a78e4[0].f20 = 0;
    g_15a78e4[0].f24 = 0x014834c4;

    g_15a78e4[1].hash = SP_sHash((const char*)0x014834c4);
    g_15a78e4[1].f04 = 4;
    g_15a78e4[1].f08 = 0;
    g_15a78e4[1].f0c = PropValI(0x016b0fb8);
    g_15a78e4[1].f10 = PropValI(4);
    g_15a78e4[1].f14 = 0;
    g_15a78e4[1].f18 = PropValI(0);
    g_15a78e4[1].f1c = 4;
    g_15a78e4[1].f20 = 0;
    g_15a78e4[1].f24 = 0;

    g_15a78e4[2].hash = SP_sHash(0);
    g_15a78e4[2].f04 = 0xffffffff;
    g_15a78e4[2].f08 = 0;
    g_15a78e4[2].f0c = PropValI(0);
    g_15a78e4[2].f10 = PropValI(0);
    g_15a78e4[2].f14 = 0;
    g_15a78e4[2].f18 = PropValI(0);
    g_15a78e4[2].f1c = 0;
    g_15a78e4[2].f20 = 0;
}

// @ 0x0137b550
void E311_InitTilingTable(void)
{
    using SP::PropValF;   // the TU's PropValF overload set lives in namespace SP; the slice called the global one (same three overloads)
    g_e311Table[0]  = SP::sHash_s0137_b550(0);
    g_e311Table[1]  = 4;
    g_e311Table[2]  = 0;
    g_e311Table[3]  = PropValF(1);
    g_e311Table[4]  = PropValF(0);
    g_e311Table[5]  = 0;
    g_e311Table[6]  = PropValF(5);
    g_e311Table[7]  = 8;
    g_e311Table[8]  = 0;
    g_e311Table[9]  = 0;
    g_e311Table[10] = SP::sHash_s0137_b550(0);
    g_e311Table[11] = 0;
    g_e311Table[12] = 0;
    g_e311Table[13] = PropValF(7);
    g_e311Table[14] = PropValF(0);
    g_e311Table[15] = 0;
    g_e311Table[16] = PropValF(0);
    g_e311Table[17] = 0;
    g_e311Table[18] = 0;
    g_e311Table[19] = 0;
    g_e311Table[20] = SP::sHash_s0137_b550(0);
    g_e311Table[21] = 8;
    g_e311Table[22] = 0;
    g_e311Table[23] = PropValF(2);
    g_e311Table[24] = PropValF(0);
    g_e311Table[25] = 1;
    g_e311Table[26] = PropValF(DAT_013eb1bc);
    g_e311Table[27] = 0;
    g_e311Table[28] = 0;
    g_e311Table[29] = 0;
    g_e311Table[30] = SP::sHash_s0137_b550(0);
    g_e311Table[31] = 0xc;
    g_e311Table[32] = 0;
    g_e311Table[33] = PropValF(2);
    g_e311Table[34] = PropValF(0);
    g_e311Table[35] = 2;
    g_e311Table[36] = PropValF(DAT_013eb1bc);
    g_e311Table[37] = 0;
    g_e311Table[38] = 0;
    g_e311Table[39] = 0;
    g_e311Table[40] = SP::sHash_s0137_b550(0);
    g_e311Table[41] = 0x10;
    g_e311Table[42] = 0;
    g_e311Table[43] = PropValF(2);
    g_e311Table[44] = PropValF(0);
    g_e311Table[45] = 3;
    g_e311Table[46] = PropValF(DAT_013eb1bc);
    g_e311Table[47] = 0;
    g_e311Table[48] = 0;
    g_e311Table[49] = 0;
    g_e311Table[50] = SP::sHash_s0137_b550(0);
    g_e311Table[51] = 0x14;
    g_e311Table[52] = 0;
    g_e311Table[53] = PropValF(2);
    g_e311Table[54] = PropValF(0);
    g_e311Table[55] = 4;
    g_e311Table[56] = PropValF(DAT_013eb1bc);
    g_e311Table[57] = 0;
    g_e311Table[58] = 0;
    g_e311Table[59] = (u32)"tilingGrid";
    g_e311Table[60] = SP::sHash_s0137_b550("tilingGrid");
    g_e311Table[61] = 0x18;
    g_e311Table[62] = 0;
    g_e311Table[63] = PropValF(5);
    g_e311Table[64] = PropValF(0);
    g_e311Table[65] = 0;
    g_e311Table[66] = PropValF(0);
    g_e311Table[67] = 2;
    g_e311Table[68] = (u32)&g_kTilingsEnumParseInfo;
    g_e311Table[69] = 0;
    g_e311Table[70] = SP::sHash_s0137_b550(0);
    g_e311Table[71] = 0xffffffff;
    g_e311Table[72] = 0;
    g_e311Table[73] = PropValF(0);
    g_e311Table[74] = PropValF(0);
    g_e311Table[75] = 0;
    g_e311Table[76] = PropValF(0);
    g_e311Table[77] = 0;
    g_e311Table[78] = 0;
}

// @ 0x0137b890
void E315_InitEffectMapTable(void)
{
    using SP::PropValF;   // see 0137b550: restores the slice's three overloads of PropValF
    g_e315Table[0]  = SP::sHash_s0137_b550("background");
    g_e315Table[1]  = 4;
    g_e315Table[2]  = 0;
    g_e315Table[3]  = PropValF(&DT_EFFECTMAP_ENTRY_BACKGROUND);
    g_e315Table[4]  = PropValF(4);
    g_e315Table[5]  = 0;
    g_e315Table[6]  = PropValF(0);
    g_e315Table[7]  = 4;
    g_e315Table[8]  = 0;
    g_e315Table[9]  = (u32)"foreground";
    g_e315Table[10] = SP::sHash_s0137_b550("foreground");
    g_e315Table[11] = 4;
    g_e315Table[12] = 0;
    g_e315Table[13] = PropValF(&DT_EFFECTMAP_ENTRY_FOREGROUND);
    g_e315Table[14] = PropValF(4);
    g_e315Table[15] = 0;
    g_e315Table[16] = PropValF(0);
    g_e315Table[17] = 4;
    g_e315Table[18] = 0;
    g_e315Table[19] = (u32)"tracer";
    g_e315Table[20] = SP::sHash_s0137_b550("tracer");
    g_e315Table[21] = 4;
    g_e315Table[22] = 0;
    g_e315Table[23] = PropValF(&DT_EFFECTMAP_ENTRY_TRACER);
    g_e315Table[24] = PropValF(4);
    g_e315Table[25] = 0;
    g_e315Table[26] = PropValF(0);
    g_e315Table[27] = 4;
    g_e315Table[28] = 0;
    g_e315Table[29] = (u32)"tracer_background";
    g_e315Table[30] = SP::sHash_s0137_b550("tracer_background");
    g_e315Table[31] = 4;
    g_e315Table[32] = 0;
    g_e315Table[33] = PropValF(&DT_EFFECTMAP_ENTRY_TRACER_BACKGROUND);
    g_e315Table[34] = PropValF(4);
    g_e315Table[35] = 0;
    g_e315Table[36] = PropValF(0);
    g_e315Table[37] = 4;
    g_e315Table[38] = 0;
    g_e315Table[39] = (u32)"skybox";
    g_e315Table[40] = SP::sHash_s0137_b550("skybox");
    g_e315Table[41] = 4;
    g_e315Table[42] = 0;
    g_e315Table[43] = PropValF(&DT_EFFECTMAP_ENTRY_SKYBOX);
    g_e315Table[44] = PropValF(4);
    g_e315Table[45] = 0;
    g_e315Table[46] = PropValF(0);
    g_e315Table[47] = 4;
    g_e315Table[48] = 0;
    g_e315Table[49] = (u32)"tile_background";
    g_e315Table[50] = SP::sHash_s0137_b550("tile_background");
    g_e315Table[51] = 4;
    g_e315Table[52] = 0;
    g_e315Table[53] = PropValF(&DT_EFFECTMAP_ENTRY_TILE_BACKGROUND);
    g_e315Table[54] = PropValF(4);
    g_e315Table[55] = 0;
    g_e315Table[56] = PropValF(0);
    g_e315Table[57] = 4;
    g_e315Table[58] = 0;
    g_e315Table[59] = 0;
    g_e315Table[60] = SP::sHash_s0137_b550(0);
    g_e315Table[61] = 0xffffffff;
    g_e315Table[62] = 0;
    g_e315Table[63] = PropValF(0);
    g_e315Table[64] = PropValF(0);
    g_e315Table[65] = 0;
    g_e315Table[66] = PropValF(0);
    g_e315Table[67] = 0;
    g_e315Table[68] = 0;
}
