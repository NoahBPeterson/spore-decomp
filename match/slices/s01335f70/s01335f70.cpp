// Slice s01335f70 -- three anonymous static initializers that populate the
// Simulator attribute-descriptor tables (each 0x3c-byte record holds a member
// name, a hash, the member offset and a set of serialisation function pointers).
//
//  0x01335f70  FUN_01335f70   two __thiscall fills on the globals at 0x0168dc10 /
//                             0x0168dc54 plus an atexit() registration (ret)
//  0x01335fe0  $E401          builds 8 records into 0x015721f0 .. (ret)
//  0x013366e0  $E222          builds 13 records into 0x01572618 .. (ret)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (MSVC 2008 SP1).
#include "types.h"
#include <stdlib.h>
#include <float.h>

// ---- plain cdecl callees ---------------------------------------------------
void  __cdecl FUN_00c22e30(void);                       // 0x00c22e30
void  __cdecl FUN_013c35b0(void);                       // 0x013c35b0  atexit callback

// ---- member-style external callee ------------------------------------------
// The original is __thiscall; modelling it as a member function of a stub class
// makes the compiler emit `mov ecx,<this>; call`, the exact original encoding.
// Nothing is linked so the symbol is just a (masked) relocation.
struct MCFill {
    void f_00bc9e30(float maxValue, int a, int b, void* fn, const char* name);  // 0x00bc9e30
};

// ---- globals used verbatim --------------------------------------------------
extern char g_168dc10[];   // 0x0168dc10  attribute holder #1
extern char g_168dc54[];   // 0x0168dc54  attribute holder #2

// ===========================================================================
// 0x01335f70 -- static init: gift-immunity attributes + atexit()
// ===========================================================================
// @ 0x01335f70
void FUN_01335f70(void)
{
    ((MCFill*)&g_168dc10)->f_00bc9e30(FLT_MAX, 0, 0, (void*)&FUN_00c22e30, "GiftImmunity");
    ((MCFill*)&g_168dc54)->f_00bc9e30(FLT_MAX, 0, 0, (void*)&FUN_00c22e30, "MildGiftImmunity");
    atexit(&FUN_013c35b0);
}

// ===========================================================================
// attribute-descriptor record (0x3c bytes = 15 dwords)
// ===========================================================================
struct AttrDesc {
    const char* mName;      // +0x00  member name
    uint32_t    mHash;      // +0x04  name hash
    uint32_t    mOffset;    // +0x08  byte offset of the member
    uint32_t    mPad0c[3];  // +0x0c  (not written by these initializers)
    uint32_t    mZero18;    // +0x18
    uint32_t    mZero1c;    // +0x1c
    void*       mFn20;      // +0x20  DefaultOffset
    void*       mFn24;      // +0x24  writer
    void*       mFn28;      // +0x28  writer2
    void*       mFn2c;      // +0x2c  parser
    void*       mFn30;      // +0x30  parser2
    void*       mFn34;      // +0x34
    void*       mFn38;      // +0x38
};

// ---------------------------------------------------------------------------
// Handler references.
//
// Each serialisation handler is referenced through its own source symbol.
// Many of them are byte-identical in the original and the linker folded them
// (ICF) onto one address, so the *same* address shows up under several distinct
// symbols.  That is significant: the compiler does not treat two distinct
// symbols as one common sub-expression, so the constants that the original
// hoists into a register (`edx`/`ebp`/`ebx`) are exactly the addresses that are
// shared between consecutive records via one symbol, while the others are
// re-materialised per record.  Using a single symbol (or bare integer literals)
// for all of them makes MSVC hoist the wrong set and changes the code.
extern "C" {
char H_692ca0[];                                              // 0x00692ca0  (all records)

// $E401 (0x01335fe0)
char H_572810_0[], H_572810_1[], H_572810_2[], H_572810_3[];
char H_572810_4[], H_572810_5[], H_572810_6[], H_572810_7[];
char H_572840_0[], H_572840_1[], H_572840_2[], H_572840_3[];
char H_572840_4[], H_572840_5[], H_572840_6[], H_572840_7[];
char H_692ff0_0[], H_693090_1[], H_693090_2[], H_692ff0_3[];
char H_693090_4[], H_c2e4e0_5[], H_c2e4e0_6[], H_c2e4e0_7[];
char H_694ee0_0[], H_694f00_1[], H_694f00_2[], H_694ee0_3[];
char H_694fa0_4[], H_692fb0_g[];                              // _g shared by records 6,7,8
char H_b1fbf0_0[], H_b1fbf0_g[], H_b1fbf0_3[], H_b1fbf0_4[];
char H_b6f550_5[], H_b6f550_6[], H_b6f550_7[];
char H_57cde0_0[], H_675ca0_g[], H_57cde0_3[], H_57ce00_4[], H_ac8050_g[];

// $E222 (0x013366e0)
char J_ae3430_0[], J_ae3450_0[], J_693150_0[], J_695080_0[], J_ae5720_0[];
char J_572810_1[], J_572810_2[], J_572810_3[], J_572810_4[];
char J_572810_5[], J_572810_6[], J_572810_7[];
char J_572840_1[], J_572840_2[], J_572840_3[], J_572840_4[];
char J_572840_5[], J_572840_6[], J_572840_7[];
char J_693090_1[], J_693090_2[], J_693090_3[], J_693090_4[];
char J_693090_5[], J_693090_6[], J_693090_7[];
char J_694f00_1[], J_694f00_2[], J_694f00_3[], J_694f00_4[];
char J_694f00_5[], J_694f00_6[], J_694f00_7[];
char J_b1fbf0_0[], J_b1fbf0_gA[], J_675ca0_gA[];
char J_572810_8[], J_572810_9[], J_572840_8[], J_572840_9[];
char J_692ff0_8[], J_692ff0_9[], J_694ee0_8[], J_694ee0_9[];
char J_b1fbf0_gB[], J_57cde0_gB[];
char J_ac8750_10[], J_ac8780_10[], J_693090_10[], J_694fa0_10[];
char J_b1fbf0_10[], J_57ce00_10[];
char J_572810_11[], J_572810_12[], J_572840_11[], J_572840_12[];
char J_692ff0_11[], J_692ff0_12[], J_694ee0_11[], J_694ee0_12[];
}

extern AttrDesc g_tbl_15721f0[];   // 0x015721f0  table written by $E401

// ===========================================================================
// 0x01335fe0 -- $E401
// ===========================================================================
#define REC401(i,nm,h,of,s20,s24,s28,s2c,s30,s34,s38)           \
    d.mName = nm; d.mHash = h; d.mZero18 = 0; d.mZero1c = 0;    \
    d.mFn20 = (void*)s20; d.mFn24 = (void*)s24; d.mFn28 = (void*)s28; \
    d.mFn2c = (void*)s2c; d.mFn30 = (void*)s30;                 \
    d.mFn34 = (void*)s34; d.mFn38 = (void*)s38;                 \
    d.mOffset = of; g_tbl_15721f0[i] = d;

// @ 0x01335fe0
void FUN_01335fe0(void)
{
    AttrDesc d;
    REC401(0, "mSelectionGroup",             0x2e6e1b0, 0xff4,
           H_692ca0, H_572810_0, H_572840_0, H_692ff0_0, H_694ee0_0, H_b1fbf0_0, H_57cde0_0)
    REC401(1, "mFavoredGrasperlikeAppendage",0x2e6e1b1, 0xfc4,
           H_692ca0, H_572810_1, H_572840_1, H_693090_1, H_694f00_1, H_b1fbf0_g, H_675ca0_g)
    REC401(2, "mGrasperlikeAppendageForBundle",0x5f0d6f3,0xfc8,
           H_692ca0, H_572810_2, H_572840_2, H_693090_2, H_694f00_2, H_b1fbf0_g, H_675ca0_g)
    REC401(3, "mSpecializedTool",            0x2e6e1b2, 0x102c,
           H_692ca0, H_572810_3, H_572840_3, H_692ff0_3, H_694ee0_3, H_b1fbf0_3, H_57cde0_3)
    REC401(4, "mAffectedByRecruiting",       0x2e6e1ab, 0x1000,
           H_692ca0, H_572810_4, H_572840_4, H_693090_4, H_694fa0_4, H_b1fbf0_4, H_57ce00_4)
    REC401(5, "mpOwnerCity",                 0x2e6e1ad, 0x1010,
           H_692ca0, H_572810_5, H_572840_5, H_c2e4e0_5, H_692fb0_g, H_b6f550_5, H_ac8050_g)
    REC401(6, "mpOwnerTribe",                0x2e6e1af, 0x1014,
           H_692ca0, H_572810_6, H_572840_6, H_c2e4e0_6, H_692fb0_g, H_b6f550_6, H_ac8050_g)
    REC401(7, "mpHitSphere",                 0x6a814a9, 0x1030,
           H_692ca0, H_572810_7, H_572840_7, H_c2e4e0_7, H_692fb0_g, H_b6f550_7, H_ac8050_g)
}

extern AttrDesc g_tbl_1572618[];   // 0x01572618  table written by $E222

// ===========================================================================
// 0x013366e0 -- $E222
// ===========================================================================
#define REC222(i,nm,h,of,s20,s24,s28,s2c,s30,s34,s38)           \
    d.mName = nm; d.mHash = h; d.mZero18 = 0; d.mZero1c = 0;    \
    d.mFn20 = (void*)s20; d.mFn24 = (void*)s24; d.mFn28 = (void*)s28; \
    d.mFn2c = (void*)s2c; d.mFn30 = (void*)s30;                 \
    d.mFn34 = (void*)s34; d.mFn38 = (void*)s38;                 \
    d.mOffset = of; g_tbl_1572618[i] = d;

// @ 0x013366e0
void FUN_013366e0(void)
{
    AttrDesc d;
    REC222(0,  "mSpeciesKey",                0x540ff31f, 0x80,
            H_692ca0, J_ae3430_0, J_ae3450_0, J_693150_0, J_695080_0, J_b1fbf0_0, J_ae5720_0)
    REC222(1,  "mNumBefriended",             0x140ff31e, 0x8c,
            H_692ca0, J_572810_1, J_572840_1, J_693090_1, J_694f00_1, J_b1fbf0_gA, J_675ca0_gA)
    REC222(2,  "mNumKilled",                 0x140ff320, 0x90,
            H_692ca0, J_572810_2, J_572840_2, J_693090_2, J_694f00_2, J_b1fbf0_gA, J_675ca0_gA)
    REC222(3,  "mNumToKillForFearful",       0x940ff321, 0xac,
            H_692ca0, J_572810_3, J_572840_3, J_693090_3, J_694f00_3, J_b1fbf0_gA, J_675ca0_gA)
    REC222(4,  "mNumToKillForExtinction",    0xd40ff322, 0xb0,
            H_692ca0, J_572810_4, J_572840_4, J_693090_4, J_694f00_4, J_b1fbf0_gA, J_675ca0_gA)
    REC222(5,  "mNumToImpressForCurious",    0xf42532e2, 0xb4,
            H_692ca0, J_572810_5, J_572840_5, J_693090_5, J_694f00_5, J_b1fbf0_gA, J_675ca0_gA)
    REC222(6,  "mNumToImpressForFriendly",   0x942532e3, 0xb8,
            H_692ca0, J_572810_6, J_572840_6, J_693090_6, J_694f00_6, J_b1fbf0_gA, J_675ca0_gA)
    REC222(7,  "mNumToImpressForBestFriends",0x942532e4, 0xbc,
            H_692ca0, J_572810_7, J_572840_7, J_693090_7, J_694f00_7, J_b1fbf0_gA, J_675ca0_gA)
    REC222(8,  "mSocialEvoPointReward",      0xb4111890, 0x94,
            H_692ca0, J_572810_8, J_572840_8, J_692ff0_8, J_694ee0_8, J_b1fbf0_gB, J_57cde0_gB)
    REC222(9,  "mCombatEvoPointReward",      0x54113b0f, 0x98,
            H_692ca0, J_572810_9, J_572840_9, J_692ff0_9, J_694ee0_9, J_b1fbf0_gB, J_57cde0_gB)
    REC222(10, "mbMiniBoss",                 0xb52f62df, 0xc4,
            H_692ca0, J_ac8750_10, J_ac8780_10, J_693090_10, J_694fa0_10, J_b1fbf0_10, J_57ce00_10)
    REC222(11, "mFoodChainLevel",            0x61dc170, 0xc0,
            H_692ca0, J_572810_11, J_572840_11, J_692ff0_11, J_694ee0_11, J_b1fbf0_gB, J_57cde0_gB)
    REC222(12, "mRelationship",              0x943c7a58, 0xa0,
            H_692ca0, J_572810_12, J_572840_12, J_692ff0_12, J_694ee0_12, J_b1fbf0_gB, J_57cde0_gB)
}