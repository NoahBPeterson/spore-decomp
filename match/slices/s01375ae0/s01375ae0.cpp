// Slice s01375ae0 -- dynamic initializer $E179 at 0x01375e30.
//
// It fills a table of SP::cFieldDef (same record shape as FIELDS_DT_CELL_GLOBALS
// in slice s0137bcc0) at 0x015a5fc8: the field descriptors of the microbe-stage
// cell resource ("name", "structure", "eat", "ai", ..., "pieces").  The dev
// build has a FIELDS_DT_CELL table that is absent from the retail globals list,
// and the entries reference DT_EAT_DATA / DT_AI_DATA / DT_CELL / DT_LOOT_TABLE,
// so the name below is a strong guess.  The source is the real global aggregate;
// cl 2008 lowers it to the compiler-generated `??__E` initializer.
#include "types.h"

// Non-inlinable accessors used by the table initializers (they live in another
// translation unit; the compiler emits a call for every field value they wrap).
extern int Conv(int);                  // FUN_00e4a9c0
extern uint32_t sHash(const char*);    // SP::sHash (0x00e4a9d0)

// Type descriptions, enum tables and default-value objects referenced by the table.
extern int DT_LOCALIZED_STRING;   // 0x016b116c
extern int DT_EAT_DATA;           // 0x016b0ee4
extern int DT_AI_DATA;            // 0x016b0a28
extern int DT_LOOT_TABLE;         // _DT_LOOT_TABLE_SP__3VcTypeDef_1_B
extern int DT_CELL;               // _DT_CELL_SP__3VcTypeDef_1_B
extern int g_defaultName;         // 0x016ad2b0
extern int g_dtStructure;         // 0x016ad454
extern int g_defaultEat;          // 0x015a5d14
extern int g_defaultAiNormal;     // 0x016ad1f8
extern int g_defaultAi;           // 0x015a5d20 (ai_hard / ai_easy)
extern int g_defaultSize;         // 0x015a5fbc (float3 {1,1,0})
extern int g_enumCellType;        // 0x014828a8
extern int g_enumUnlockType;      // 0x01482988
extern int g_enumDensity;         // 0x01482870
extern int g_enumSound;           // 0x014828f8

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

#define BOOL_F      Conv(6), Conv(0), 0, Conv(0), 6, 0
#define INT_F(v)    Conv(1), Conv(0), 0, Conv(v), 6, 0
#define ENUM_F(e)   Conv(5), Conv(0), 0, Conv(0), 4, (int)&e
#define REF_F(dt)   Conv(3), Conv((int)&dt), 0, Conv(0), 4, 0
#define SUB_F(dt, d) Conv((int)&dt), Conv(0), 0, Conv((int)&d), 6, 0

// @ 0x01375e30
cFieldDef FIELDS_DT_CELL[] = {
    /* 0*/ { "name", sHash("name"), 4, 0, SUB_F(DT_LOCALIZED_STRING, g_defaultName) },
    /* 1*/ { "structure", sHash("structure"), 0, 0, Conv(3), Conv((int)&g_dtStructure), 0, Conv(0), 4, 0 },
    /* 2*/ { "eat", sHash("eat"), 0x30c, 0, SUB_F(DT_EAT_DATA, g_defaultEat) },
    /* 3*/ { "ai", sHash("ai"), 0xe0, 0, SUB_F(DT_AI_DATA, g_defaultAiNormal) },
    /* 4*/ { "ai_hard", sHash("ai_hard"), 0x194, 0, SUB_F(DT_AI_DATA, g_defaultAi) },
    /* 5*/ { "ai_easy", sHash("ai_easy"), 0x248, 0, SUB_F(DT_AI_DATA, g_defaultAi) },
    /* 6*/ { "friendGroup", sHash("friendGroup"), 0x2fc, 0, INT_F(0) },
    /* 7*/ { "wontAttackPlayer", sHash("wontAttackPlayer"), 0x300, 0, BOOL_F },
    /* 8*/ { "wontAttackPlayerWhenSmall", sHash("wontAttackPlayerWhenSmall"), 0x301, 0, BOOL_F },
    /* 9*/ { "hp", sHash("hp"), 0xa8, 0, INT_F(2) },
    /*10*/ { "fixedOrientation", sHash("fixedOrientation"), 0xac, 0, BOOL_F },
    /*11*/ { "size", sHash("size"), 0x304, 0, Conv(0xb), Conv(0), 0, Conv((int)&g_defaultSize), 6, 0 },
    /*12*/ { "triggersEscapeMission", sHash("triggersEscapeMission"), 0x318, 0, BOOL_F },
    /*13*/ { "flags", sHash("flags"), 0xb0, 0, INT_F(0) },
    /*14*/ { "cellType", sHash("cellType"), 0xb4, 0, ENUM_F(g_enumCellType) },
    /*15*/ { "unlockType", sHash("unlockType"), 0xb8, 0, ENUM_F(g_enumUnlockType) },
    /*16*/ { "density", sHash("density"), 0xbc, 0, ENUM_F(g_enumDensity) },
    /*17*/ { "sound", sHash("sound"), 0xc0, 0, ENUM_F(g_enumSound) },
    /*18*/ { "explosionTable", sHash("explosionTable"), 0xd8, 0, REF_F(DT_LOOT_TABLE) },
    /*19*/ { "loot", sHash("loot"), 0xd4, 0, REF_F(DT_LOOT_TABLE) },
    /*20*/ { "leak", sHash("leak"), 0xcc, 0, REF_F(DT_CELL) },
    /*21*/ { "expel", sHash("expel"), 0xd0, 0, REF_F(DT_CELL) },
    /*22*/ { "poison", sHash("poison"), 0xdc, 0, REF_F(DT_CELL) },
    /*23*/ { "break", sHash("break"), 0xc4, 0, REF_F(DT_CELL) },
    /*24*/ { "pieces", sHash("pieces"), 200, 0, REF_F(DT_LOOT_TABLE) },
    /*25*/ { 0, sHash(0), -1, 0, Conv(0), Conv(0), 0, Conv(0), 0, 0 },
};

} // namespace SP
