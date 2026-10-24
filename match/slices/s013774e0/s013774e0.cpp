// Slice s013774e0 -- SP global field-descriptor table initialisers (compiler-generated
// `??__E`-style dynamic initializers named $E195/$E199/$E203/$E207/$E211/$E215 in the image).
//
// Each function fills a static array of 0x28-byte SP::cFieldDef records.  The record layout
// (matching the FIELDS_DT_* tables of slice s0137d820) is:
//   +0x00  hash of the field name (SP::sHash)
//   +0x04  variable offset
//   +0x08  variable auxiliary offset
//   +0x0c  type code (little enum described by the +0x10 type descriptor)
//   +0x10  type descriptor pointer (Conv-wrapped)
//   +0x14  argument index
//   +0x18  default value (int or float, Conv-wrapped)
//   +0x1c  field flags
//   +0x20  enum table pointer
//   +0x24  name pointer hashed for the NEXT record's +0x00
//
// cl lowers the aggregate to a straight run of stores; the record's own name pointer lives at
// +0x24, so writing g[i].name reproduces the store the original emits for g[i+1].hash's key.
// The very first record's name pointer (base-4) and the last record's +0x24 are not stored,
// matching the original (they are never referenced as a following record's key).
//
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef unsigned int u32;

// 0x00e4a9c0 -- the 4-byte pass-through used to box every field value.  The int and float
// overloads were folded together (ICF); the compiler emits a call for either.
extern "C" int Conv(int);              // 0x00e4a9c0
extern "C" int ConvF(float);           // 0x00e4a9c0
// 0x00e4a9d0 -- SP::sHash(const char*).  Returns 0 for a null name.
extern "C" u32 SP_sHash(const char*);  // 0x00e4a9d0 (SP::sHash)

// Type descriptors / enum tables referenced by the tables (address-only references).
extern int g_dtCell;        // 0x016ad4b0  _DT_CELL_SP__3VcTypeDef_1_B
extern int g_dtPopulation;  // 0x016b0a80  _DT_CELL_POPULATION...
extern int g_dtDistribute;  // 0x016ad3fc  DT_CELL_DISTRIBUTE
extern int g_dtCluster;     // 0x016b0d28  DT_CELL_CLUSTER
extern int g_dtPlant;       // 0x016b0bb8  DT_CELL_PLANT
extern int g_dtEncounter;   // 0x016b0ca4  DT_CELL_ENCOUNTER
extern int g_dtLevelEntry;  // 0x016b10a4  DT_LEVEL_ENTRY
extern int g_dtAdvectEntry; // 0x016b0f3c  DT_ADVECT_ENTRY
extern int g_kTilings;      // 0x01482a78  _kTilings_SP__3QBUcEnumParseInfo_ArgScript_EA__B

namespace SP {

struct cFieldDef {
    u32         hash;        // +0x00
    int         offset;      // +0x04
    int         auxOffset;   // +0x08
    int         type;        // +0x0c
    int         typeDesc;    // +0x10
    int         argIndex;    // +0x14
    int         defaultValue;// +0x18
    int         flags;       // +0x1c
    int         enumTable;   // +0x20
    const char* name;        // +0x24  (key hashed by the following record)
};

} // namespace SP

using SP::cFieldDef;

extern cFieldDef g_16b222c[13];  // 0x016b222c
extern cFieldDef g_15a77cc[7];   // 0x015a77cc
extern cFieldDef g_16b2e0c[4];   // 0x016b2e0c
extern cFieldDef g_16b209c[7];   // 0x016b209c
extern cFieldDef g_15a7754[3];   // 0x015a7754
extern cFieldDef g_16b1bc4[3];   // 0x016b1bc4

// ---------------------------------------------------------------------------
// @ 0x013774e0  InitPropTable_16b222c
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x01377a10  InitPropTable_15a77cc
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x01377cf0  InitPropTable_16b2e0c
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x01377ec0  InitPropTable_16b209c
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x013781a0  InitPropTable_15a7754
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x01378300  InitPropTable_16b1bc4
// ---------------------------------------------------------------------------
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