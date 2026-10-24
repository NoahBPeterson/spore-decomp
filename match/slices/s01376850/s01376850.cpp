// Slice s01376850 -- three SP global field-descriptor table initialisers (compiler-generated
// `$E`-style dynamic initializers in the image; 0x01376cc0 is named $E187 in the dev PDB).
//
// Each function fills a static array of 0x28-byte SP::cFieldDef records.  This is the exact
// record shape used by the sibling slices s013774e0 / s0137d820:
//   +0x00  hash of the previous record's name (SP::sHash)
//   +0x04  variable offset
//   +0x08  variable auxiliary offset
//   +0x0c  type code
//   +0x10  type descriptor pointer (Conv-wrapped)
//   +0x14  argument index
//   +0x18  default value (int, or float via the ICF-folded ConvF entry point)
//   +0x1c  field flags
//   +0x20  enum table pointer
//   +0x24  name pointer, hashed for the NEXT record's +0x00
//
// cl lowers the aggregate to a straight run of stores; the last record's +0x24 (which no
// following record hashes) is never stored, so it is omitted below.
//
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef unsigned int u32;

// 0x00e4a9c0 -- the 4-byte boxing pass-through used for every field value.  The int and float
// overloads were identical-code-folded; the compiler emits a call for either.
extern "C" int Conv(int);              // 0x00e4a9c0
extern "C" int ConvF(float);           // 0x00e4a9c0
// 0x00e4a9d0 -- SP::sHash(const char*).  Returns 0 for a null name.
extern "C" u32 SP_sHash(const char*);  // 0x00e4a9d0 (SP::sHash)

// Address-only references to type descriptors / enum tables / strings.
extern int  g_ctPopulation;  // 0x016b0a80  _DT_CELL_POPULATION_SP__3VcTypeDef_1_B
extern int  g_dtCell;        // 0x016ad4b0  _DT_CELL_SP__3VcTypeDef_1_B
extern int  g_kTilings;      // 0x01482a78  _kTilings_SP__3QBUcEnumParseInfo_ArgScript_EA__B
extern int  g_type1;         // 0x01482b28  PTR_s_type1_01482b28
extern char g_strSize[];     // 0x013f293c  "size"

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
};

} // namespace SP

using SP::cFieldDef;

extern cFieldDef g_16b1584[11];  // 0x016b1584
extern cFieldDef g_16b277c[9];   // 0x016b277c
extern cFieldDef g_16b119c[11];  // 0x016b119c

// ---------------------------------------------------------------------------
// @ 0x01376850  InitPropTable_16b1584
// ---------------------------------------------------------------------------
void InitPropTable_16b1584(void)
{
    g_16b1584[0].hash = SP_sHash(0);          g_16b1584[0].offset = 0x14;  g_16b1584[0].auxOffset = 0;
    g_16b1584[0].type = Conv(1);              g_16b1584[0].typeDesc = Conv(0);
    g_16b1584[0].argIndex = 0;                g_16b1584[0].defaultValue = Conv(0);
    g_16b1584[0].flags = 8;                   g_16b1584[0].enumTable = 0;  g_16b1584[0].name = 0;

    g_16b1584[1].hash = SP_sHash(0);          g_16b1584[1].offset = 0x28;  g_16b1584[1].auxOffset = 0;
    g_16b1584[1].type = Conv(1);              g_16b1584[1].typeDesc = Conv(0);
    g_16b1584[1].argIndex = 0;                g_16b1584[1].defaultValue = Conv(2);
    g_16b1584[1].flags = 8;                   g_16b1584[1].enumTable = 0;  g_16b1584[1].name = 0;

    g_16b1584[2].hash = SP_sHash(0);          g_16b1584[2].offset = 0x24;  g_16b1584[2].auxOffset = 0;
    g_16b1584[2].type = Conv(5);              g_16b1584[2].typeDesc = Conv(0);
    g_16b1584[2].argIndex = 0;                g_16b1584[2].defaultValue = Conv(0);
    g_16b1584[2].flags = 0;                   g_16b1584[2].enumTable = (int)&g_type1;
    g_16b1584[2].name = "count";

    g_16b1584[3].hash = SP_sHash("count");    g_16b1584[3].offset = 0x2c;  g_16b1584[3].auxOffset = 0;
    g_16b1584[3].type = Conv(2);              g_16b1584[3].typeDesc = Conv(0);
    g_16b1584[3].argIndex = 0;                g_16b1584[3].defaultValue = ConvF(-1.0f);
    g_16b1584[3].flags = 2;                   g_16b1584[3].enumTable = 0;
    g_16b1584[3].name = "count_med";

    g_16b1584[4].hash = SP_sHash("count_med"); g_16b1584[4].offset = 0x34; g_16b1584[4].auxOffset = 0;
    g_16b1584[4].type = Conv(2);              g_16b1584[4].typeDesc = Conv(0);
    g_16b1584[4].argIndex = 0;                g_16b1584[4].defaultValue = ConvF(-1.0f);
    g_16b1584[4].flags = 2;                   g_16b1584[4].enumTable = 0;
    g_16b1584[4].name = "count_easy";

    g_16b1584[5].hash = SP_sHash("count_easy"); g_16b1584[5].offset = 0x30; g_16b1584[5].auxOffset = 0;
    g_16b1584[5].type = Conv(2);              g_16b1584[5].typeDesc = Conv(0);
    g_16b1584[5].argIndex = 0;                g_16b1584[5].defaultValue = ConvF(-1.0f);
    g_16b1584[5].flags = 2;                   g_16b1584[5].enumTable = 0;
    g_16b1584[5].name = "count_hard";

    g_16b1584[6].hash = SP_sHash("count_hard"); g_16b1584[6].offset = 0x38; g_16b1584[6].auxOffset = 0;
    g_16b1584[6].type = Conv(2);              g_16b1584[6].typeDesc = Conv(0);
    g_16b1584[6].argIndex = 0;                g_16b1584[6].defaultValue = ConvF(-1.0f);
    g_16b1584[6].flags = 2;                   g_16b1584[6].enumTable = 0;
    g_16b1584[6].name = g_strSize;

    g_16b1584[7].hash = SP_sHash(g_strSize);  g_16b1584[7].offset = 0x3c;  g_16b1584[7].auxOffset = 0;
    g_16b1584[7].type = Conv(5);              g_16b1584[7].typeDesc = Conv(0);
    g_16b1584[7].argIndex = 0;                g_16b1584[7].defaultValue = Conv(1);
    g_16b1584[7].flags = 2;                   g_16b1584[7].enumTable = (int)&g_kTilings;
    g_16b1584[7].name = "zOffset";

    g_16b1584[8].hash = SP_sHash("zOffset");  g_16b1584[8].offset = 0xc;   g_16b1584[8].auxOffset = 0;
    g_16b1584[8].type = Conv(2);              g_16b1584[8].typeDesc = Conv(0);
    g_16b1584[8].argIndex = 0;                g_16b1584[8].defaultValue = ConvF(0.0f);
    g_16b1584[8].flags = 2;                   g_16b1584[8].enumTable = 0;
    g_16b1584[8].name = "zOffsetMax";

    g_16b1584[9].hash = SP_sHash("zOffsetMax"); g_16b1584[9].offset = 0x10; g_16b1584[9].auxOffset = 0;
    g_16b1584[9].type = Conv(2);              g_16b1584[9].typeDesc = Conv(0);
    g_16b1584[9].argIndex = 0;                g_16b1584[9].defaultValue = ConvF(0.0f);
    g_16b1584[9].flags = 2;                   g_16b1584[9].enumTable = 0;  g_16b1584[9].name = 0;

    g_16b1584[10].hash = SP_sHash(0);         g_16b1584[10].offset = -1;   g_16b1584[10].auxOffset = 0;
    g_16b1584[10].type = Conv(0);             g_16b1584[10].typeDesc = Conv(0);
    g_16b1584[10].argIndex = 0;               g_16b1584[10].defaultValue = Conv(0);
    g_16b1584[10].flags = 0;                  g_16b1584[10].enumTable = 0;
}

// ---------------------------------------------------------------------------
// @ 0x01376cc0  InitPropTable_16b277c   ($E187 in the dev PDB)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x01377070  InitPropTable_16b119c
// ---------------------------------------------------------------------------
void InitPropTable_16b119c(void)
{
    g_16b119c[0].hash = SP_sHash(0);          g_16b119c[0].offset = 0x14;  g_16b119c[0].auxOffset = 0;
    g_16b119c[0].type = Conv(1);              g_16b119c[0].typeDesc = Conv(0);
    g_16b119c[0].argIndex = 0;                g_16b119c[0].defaultValue = Conv(0);
    g_16b119c[0].flags = 8;                   g_16b119c[0].enumTable = 0;  g_16b119c[0].name = 0;

    g_16b119c[1].hash = SP_sHash(0);          g_16b119c[1].offset = 0x28;  g_16b119c[1].auxOffset = 0;
    g_16b119c[1].type = Conv(1);              g_16b119c[1].typeDesc = Conv(0);
    g_16b119c[1].argIndex = 0;                g_16b119c[1].defaultValue = Conv(0);
    g_16b119c[1].flags = 8;                   g_16b119c[1].enumTable = 0;  g_16b119c[1].name = 0;

    g_16b119c[2].hash = SP_sHash(0);          g_16b119c[2].offset = 0x18;  g_16b119c[2].auxOffset = 0;
    g_16b119c[2].type = Conv(3);              g_16b119c[2].typeDesc = Conv((int)&g_dtCell);
    g_16b119c[2].argIndex = 0;                g_16b119c[2].defaultValue = Conv(0);
    g_16b119c[2].flags = 0;                   g_16b119c[2].enumTable = 0;
    g_16b119c[2].name = "count";

    g_16b119c[3].hash = SP_sHash("count");    g_16b119c[3].offset = 0x2c;  g_16b119c[3].auxOffset = 0;
    g_16b119c[3].type = Conv(2);              g_16b119c[3].typeDesc = Conv(0);
    g_16b119c[3].argIndex = 0;                g_16b119c[3].defaultValue = ConvF(-1.0f);
    g_16b119c[3].flags = 2;                   g_16b119c[3].enumTable = 0;
    g_16b119c[3].name = "count_med";

    g_16b119c[4].hash = SP_sHash("count_med"); g_16b119c[4].offset = 0x34; g_16b119c[4].auxOffset = 0;
    g_16b119c[4].type = Conv(2);              g_16b119c[4].typeDesc = Conv(0);
    g_16b119c[4].argIndex = 0;                g_16b119c[4].defaultValue = ConvF(-1.0f);
    g_16b119c[4].flags = 2;                   g_16b119c[4].enumTable = 0;
    g_16b119c[4].name = "count_easy";

    g_16b119c[5].hash = SP_sHash("count_easy"); g_16b119c[5].offset = 0x30; g_16b119c[5].auxOffset = 0;
    g_16b119c[5].type = Conv(2);              g_16b119c[5].typeDesc = Conv(0);
    g_16b119c[5].argIndex = 0;                g_16b119c[5].defaultValue = ConvF(-1.0f);
    g_16b119c[5].flags = 2;                   g_16b119c[5].enumTable = 0;
    g_16b119c[5].name = "count_hard";

    g_16b119c[6].hash = SP_sHash("count_hard"); g_16b119c[6].offset = 0x38; g_16b119c[6].auxOffset = 0;
    g_16b119c[6].type = Conv(2);              g_16b119c[6].typeDesc = Conv(0);
    g_16b119c[6].argIndex = 0;                g_16b119c[6].defaultValue = ConvF(-1.0f);
    g_16b119c[6].flags = 2;                   g_16b119c[6].enumTable = 0;
    g_16b119c[6].name = g_strSize;

    g_16b119c[7].hash = SP_sHash(g_strSize);  g_16b119c[7].offset = 0x3c;  g_16b119c[7].auxOffset = 0;
    g_16b119c[7].type = Conv(5);              g_16b119c[7].typeDesc = Conv(0);
    g_16b119c[7].argIndex = 0;                g_16b119c[7].defaultValue = Conv(1);
    g_16b119c[7].flags = 2;                   g_16b119c[7].enumTable = (int)&g_kTilings;
    g_16b119c[7].name = "zOffset";

    g_16b119c[8].hash = SP_sHash("zOffset");  g_16b119c[8].offset = 0xc;   g_16b119c[8].auxOffset = 0;
    g_16b119c[8].type = Conv(2);              g_16b119c[8].typeDesc = Conv(0);
    g_16b119c[8].argIndex = 0;                g_16b119c[8].defaultValue = ConvF(0.0f);
    g_16b119c[8].flags = 2;                   g_16b119c[8].enumTable = 0;
    g_16b119c[8].name = "zOffsetMax";

    g_16b119c[9].hash = SP_sHash("zOffsetMax"); g_16b119c[9].offset = 0x10; g_16b119c[9].auxOffset = 0;
    g_16b119c[9].type = Conv(2);              g_16b119c[9].typeDesc = Conv(0);
    g_16b119c[9].argIndex = 0;                g_16b119c[9].defaultValue = ConvF(0.0f);
    g_16b119c[9].flags = 2;                   g_16b119c[9].enumTable = 0;  g_16b119c[9].name = 0;

    g_16b119c[10].hash = SP_sHash(0);         g_16b119c[10].offset = -1;   g_16b119c[10].auxOffset = 0;
    g_16b119c[10].type = Conv(0);             g_16b119c[10].typeDesc = Conv(0);
    g_16b119c[10].argIndex = 0;               g_16b119c[10].defaultValue = Conv(0);
    g_16b119c[10].flags = 0;                  g_16b119c[10].enumTable = 0;
}