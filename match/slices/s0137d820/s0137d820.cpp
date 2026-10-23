// Slice s0137d820 -- SPGonzago/SPCellGame.obj (cell stage), attachment field tables and a
// handful of global numeric/table initializers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (cell TU; no /EHsc)
#include "types.h"

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

// Non-inlinable accessors used by the table initializers (they live in another TU; the
// compiler emits a call for every value they wrap).
extern int    Conv(int);              // 0x00e4a9c0
extern uint32 sHash(const char*);     // 0x00e4a9d0 (SP::sHash)

// Type descriptions / enum tables / default-value objects referenced by the tables.
extern int g_dtStructure;      // 0x016ad454 (DT_STRUCTURE)
extern int g_dtRandom;         // 0x016ad428
extern int g_defaultColor;     // 0x015a5dfc
extern int g_kTilings;         // 0x01482a78 (_kTilings_SP__3QBUcEnumParseInfo_ArgScript_EA__B)

extern float gFMax;            // 0x014851e8  ( 3.4028235e38)
extern float gFMin;            // 0x013f51ac  (-3.4028235e38)

namespace SP {

struct cFieldDef {
    const char* name;                // +0x00
    int         hash_name;           // +0x04
    int         variable_offset;     // +0x08
    int         variable_aux_offset; // +0x0c
    int         type;                // +0x10
    int         type_aux;            // +0x14
    int         argument_index;      // +0x18
    int         default_value;       // +0x1c
    int         field_flags;         // +0x20
    int         enum_table;          // +0x24
};

// ---------------------------------------------------------------- field tables
// Every attachment type repeats the same three "base" records (a type selector at +4, a
// structure reference at +0x10 and the shared "bone" field), followed by type-specific
// fields and a { 0, sHash(0), -1, ... } terminator.

// @ 0x0137d820  dynamic initializer of FIELDS_DT_ATTACHMENT_STRUCTURE (0x016b1b20)
cFieldDef FIELDS_DT_ATTACHMENT_STRUCTURE[] = {
    { 0, sHash(0), 4, 0, Conv(5), Conv(0), 0, Conv(2), 8, 0 },
    { 0, sHash(0), 8, 0, Conv(3), Conv((int)&g_dtStructure), 0, Conv(0), 0, 0 },
    { "bone", sHash("bone"), 0, 0, Conv(1), Conv(0), 0, Conv(-1), 2, 0 },
    { 0, sHash(0), -1, 0, Conv(0), Conv(0), 0, Conv(0), 0, 0 },
};

// @ 0x0137d9d0  dynamic initializer of FIELDS_DT_ATTACHMENT_EFFECT (0x016b1350)
cFieldDef FIELDS_DT_ATTACHMENT_EFFECT[] = {
    { 0, sHash(0), 4, 0, Conv(5), Conv(0), 0, Conv(1), 8, 0 },
    { 0, sHash(0), 0x10, 0x10, Conv(7), Conv(0), 0, Conv(0), 0, 0 },
    { "bone", sHash("bone"), 0, 0, Conv(1), Conv(0), 0, Conv(-1), 2, 0 },
    { "levelMin", sHash("levelMin"), 0x14, 0, Conv(5), Conv(0), 0, Conv(-1), 2, (int)&g_kTilings },
    { "levelMax", sHash("levelMax"), 0x18, 0, Conv(5), Conv(0), 0, Conv(-1), 2, (int)&g_kTilings },
    { 0, sHash(0), -1, 0, Conv(0), Conv(0), 0, Conv(0), 0, 0 },
};

// @ 0x0137dc50  dynamic initializer of FIELDS_DT_ATTACHMENT_MODEL (0x016b1c38)
cFieldDef FIELDS_DT_ATTACHMENT_MODEL[] = {
    { 0, sHash(0), 4, 0, Conv(5), Conv(0), 0, Conv(0), 8, 0 },
    { 0, sHash(0), 0x10, 0x10, Conv(7), Conv(0), 0, Conv(0), 0, 0 },
    { "bone", sHash("bone"), 0, 0, Conv(1), Conv(0), 0, Conv(-1), 2, 0 },
    { "color", sHash("color"), 0x1c, 0, Conv(8), Conv(0), 0, Conv((int)&g_defaultColor), 2, 0 },
    { 0, sHash(0), -1, 0, Conv(0), Conv(0), 0, Conv(0), 0, 0 },
};

// @ 0x0137de60  dynamic initializer of FIELDS_DT_ATTACHMENT_CREATURE (0x016b2688)
cFieldDef FIELDS_DT_ATTACHMENT_CREATURE[] = {
    { 0, sHash(0), 4, 0, Conv(5), Conv(0), 0, Conv(3), 8, 0 },
    { 0, sHash(0), 0x10, 0x10, Conv(7), Conv(0), 0, Conv(0), 0, 0 },
    { 0, sHash(0), -1, 0, Conv(0), Conv(0), 0, Conv(0), 0, 0 },
};

// @ 0x0137dfb0  dynamic initializer of FIELDS_DT_ATTACHMENT_RANDOM_CREATURE (0x016b1918)
cFieldDef FIELDS_DT_ATTACHMENT_RANDOM_CREATURE[] = {
    { 0, sHash(0), 4, 0, Conv(5), Conv(0), 0, Conv(4), 8, 0 },
    { 0, sHash(0), 0xc, 0, Conv(3), Conv((int)&g_dtRandom), 0, Conv(0), 0, 0 },
    { 0, sHash(0), -1, 0, Conv(0), Conv(0), 0, Conv(0), 0, 0 },
};

} // namespace SP

// ---------------------------------------------------------------- numeric inits
extern float gRadius;       // 0x015a7c68
extern float gRadiusSq;     // 0x016b3c34
extern float gRadiusCb;     // 0x016b3c38
extern float gAngleUnit;    // 0x015a7c24
extern float gAngleScale;   // 0x016b3c3c

// @ 0x0137ec20
void FUN_0137ec20(void) { gRadiusSq = gRadius * gRadius; }

// @ 0x0137ec40
void FUN_0137ec40(void) { gRadiusCb = gRadius * gRadius * gRadius; }

// @ 0x0137ec60
void FUN_0137ec60(void) { gAngleScale = 315.0f / ((gRadiusCb * gAngleUnit) * 64.0f); }

// ---------------------------------------------------------------- bounding boxes
struct Vec3 { float x, y, z; };
struct cSPBoundingBox { Vec3 min; Vec3 max; };

extern cSPBoundingBox gCellGameExtents;            // 0x016b3c88
extern cSPBoundingBox gCellGameBackgroundExtents;  // 0x016b3ca0

// @ 0x0137ed40
void FUN_0137ed40(void) {
    Vec3 mn; mn.x = gFMax; mn.y = gFMax; mn.z = gFMax;
    gCellGameExtents.min = mn;
    Vec3 mx; mx.x = gFMin; mx.y = gFMin; mx.z = gFMin;
    gCellGameExtents.max = mx;
}

// @ 0x0137edc0
void FUN_0137edc0(void) {
    Vec3 mn; mn.x = gFMax; mn.y = gFMax; mn.z = gFMax;
    gCellGameBackgroundExtents.min = mn;
    Vec3 mx; mx.x = gFMin; mx.y = gFMin; mx.z = gFMin;
    gCellGameBackgroundExtents.max = mx;
}

// ---------------------------------------------------------------- property table
// The cell game attribute table (3 records, 0x3c bytes each, at 0x015a7d48) uses the same
// Simulator::Attribute record as the s0137ef90 table: a 0x3c-byte aggregate built in one reused
// stack temp by a small constructor and copied out with rep movsd. The constructor's store order
// (name, id, pCurrentObject, setDefaultFunction, offsetFunction, readFunction, writeFunction,
// readTextFunction, writeTextFunction, validateFunction, toXmlFunction, offset) reproduces the
// original exactly, including the re-materialization of the common callbacks per record.

typedef void (*PFN)(void);

extern void FUN_00692ca0();  // DefaultOffset  (offsetFunction)
extern void FUN_00572810();  // Read4<int>
extern void FUN_00572840();  // Write4<int>
extern void FUN_00692ff0();  // ReadText
extern void FUN_00694ee0();  // WriteText
extern void FUN_00b1fbf0();  // AlwaysValid
extern void FUN_0057cde0();  // ToXml

struct Attribute {
    /* 00h */ const char* name;
    /* 04h */ int         id;
    /* 08h */ int         offset;
    /* 0Ch */ int         field_0C;   // not initialized
    /* 10h */ int         field_10;   // not initialized
    /* 14h */ int         field_14;   // not initialized
    /* 18h */ void*       pCurrentObject;
    /* 1Ch */ PFN         setDefaultFunction;
    /* 20h */ PFN         offsetFunction;
    /* 24h */ PFN         readFunction;
    /* 28h */ PFN         writeFunction;
    /* 2Ch */ PFN         readTextFunction;
    /* 30h */ PFN         writeTextFunction;
    /* 34h */ PFN         validateFunction;
    /* 38h */ PFN         toXmlFunction;

    Attribute(const char* pName, int nID, int nOffset,
              PFN pOffset, PFN pRead, PFN pWrite,
              PFN pReadText, PFN pWriteText, PFN pValidate, PFN pToXml,
              PFN pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = pOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }
};

struct AttrSlot { uint32_t d[15]; };
extern AttrSlot g_cellGame_sAttributes[3];   // 0x015a7d48

#define CELL_ATTR  &FUN_00692ca0, &FUN_00572810, &FUN_00572840, &FUN_00692ff0, &FUN_00694ee0, &FUN_00b1fbf0, &FUN_0057cde0
#define CELL_ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&g_cellGame_sAttributes[IDX] = a; }

// @ 0x0137ee40
void FUN_0137ee40(void) {
    CELL_ADD(0, "state",         0xabce0000, 0, CELL_ATTR)
    CELL_ADD(1, "progress",      0xabce0001, 4, CELL_ATTR)
    CELL_ADD(2, "plantProgress", 0xabce0002, 8, CELL_ATTR)
}
