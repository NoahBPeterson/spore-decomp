// Slice s0134f690 (batch gold6): the SP::cPlanet attribute-descriptor table initialiser.
//
// Flags: /O2 /MD /Gy /EHsc /TP
//
// The function fills a global array of 0x3c-byte Simulator::Attribute records, one per
// serialised cPlanet member. Each record is assembled in a stack temporary and then
// copied over the slot with an inlined rep movsd, which is what the retail image does.
// The field layout below is read off the retail stores; the three words at +0x0c, +0x10
// and +0x14 are not touched by this initialiser (they are left for the runtime base
// initialiser), so they stay unnamed-but-allocated here as well.

#include "types.h"

typedef unsigned int u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------
// addresses of the descriptor callbacks / default-offset object (image resident,
// so every immediate below is a relocated absolute address)
// ---------------------------------------------------------------------------
extern char gSimAttributeDefaultOffset;      // 0x00692ca0  Simulator::Attribute::DefaultOffset
extern char FUN_00c724d0;                    // 0x00c724d0
extern char cAgentOrderManager_ActivateOne;  // 0x00bca960
extern char UTFWin_ILayoutElement_SetSerializer;  // 0x00c2e4e0
extern char ClearBuffer;                     // 0x00692fb0
extern char FUN_00b6f550;                    // 0x00b6f550
extern char FUN_00ac8050;                    // 0x00ac8050
extern char FUN_00c72500;                    // 0x00c72500
extern char FUN_00bdd350;                    // 0x00bdd350
extern char operator__SP_cPlanet;            // 0x00c3b930  operator>>(SP::cPlanet)
extern char FUN_00b6e3a0;                    // 0x00b6e3a0
extern char FUN_00ac88c0;                    // 0x00ac88c0
extern char ParseVector3;                    // 0x006930f0
extern char FUN_00695010;                    // 0x00695010
extern char UTFWin_Window_Initialize;        // 0x00b1fbf0
extern char FUN_00acbba0;                    // 0x00acbba0
extern char FUN_00ae3470;                    // 0x00ae3470
extern char FUN_00ae3490;                    // 0x00ae3490
extern char FUN_00ae3310;                    // 0x00ae3310
extern char FUN_00b72e30;                    // 0x00b72e30
extern char FUN_00b74a40;                    // 0x00b74a40
extern char FUN_00572810;                    // 0x00572810
extern char WriteUint32Value;                // 0x00572840
extern char ParseULong;                      // 0x00693090
extern char FUN_00694f00;                    // 0x00694f00
extern char ParseLong;                       // 0x00692ff0
extern char FUN_00694ee0;                    // 0x00694ee0
extern char FUN_0057cde0;                    // 0x0057cde0
extern char FUN_00ac87c0;                    // 0x00ac87c0
extern char FUN_00ac87f0;                    // 0x00ac87f0
extern char FUN_00ac88f0;                    // 0x00ac88f0
extern char FUN_00694c80;                    // 0x00694c80
extern char FUN_00694c10;                    // 0x00694c10
extern char FUN_00acbbc0;                    // 0x00acbbc0
extern char ParseFloat;                      // 0x006930b0
extern char FUN_00694fc0;                    // 0x00694fc0
extern char FUN_00acbb80;                    // 0x00acbb80
extern char Simulator_ToXml;                 // 0x00675ca0

// ---------------------------------------------------------------------------
// the attribute descriptor + the global table
// ---------------------------------------------------------------------------
struct SimAttribute {
    const char* mName;          // +0x00
    u32         mHash;          // +0x04
    u32         mOffset;        // +0x08  offsetof(cPlanet, member)
    u32         mBaseA;         // +0x0c  left to the runtime base initialiser
    u32         mBaseB;         // +0x10
    u32         mBaseC;         // +0x14
    u32         mDefaultLow;    // +0x18
    u32         mDefaultHigh;   // +0x1c
    void*       mFnDefault;     // +0x20  Simulator::Attribute::DefaultOffset
    void*       mFnSave;        // +0x24
    void*       mFnLoad;        // +0x28
    void*       mFnParse;       // +0x2c
    void*       mFnEdit;        // +0x30
    void*       mFnUI;          // +0x34
    void*       mFnExtra;       // +0x38
};

extern SimAttribute gPlanetAttributes[12];   // 0x01578890

// ---------------------------------------------------------------------------
// @ 0x0134f690
// ---------------------------------------------------------------------------
void RegisterPlanetAttributes()
{
    SimAttribute t;

    t.mName = "mpPlanetSim";
    t.mHash = 0x35d9760;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00c724d0;
    t.mFnLoad = &cAgentOrderManager_ActivateOne;
    t.mFnParse = &UTFWin_ILayoutElement_SetSerializer;
    t.mFnEdit = &ClearBuffer;
    t.mFnUI = &FUN_00b6f550;
    t.mFnExtra = &FUN_00ac8050;
    t.mOffset = 0x154;
    gPlanetAttributes[0] = t;

    t.mName = "mpVisiblePlanet";
    t.mHash = 0x4457f99;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00c72500;
    t.mFnLoad = &FUN_00bdd350;
    t.mFnParse = &UTFWin_ILayoutElement_SetSerializer;
    t.mFnEdit = &ClearBuffer;
    t.mFnUI = &FUN_00b6f550;
    t.mFnExtra = &FUN_00ac8050;
    t.mOffset = 0x18c;
    gPlanetAttributes[1] = t;

    t.mName = "mParent";
    t.mHash = 0x30d5fd2;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &operator__SP_cPlanet;
    t.mFnLoad = &FUN_00bdd350;
    t.mFnParse = &UTFWin_ILayoutElement_SetSerializer;
    t.mFnEdit = &ClearBuffer;
    t.mFnUI = &FUN_00b6f550;
    t.mFnExtra = &FUN_00ac8050;
    t.mOffset = 0x1c0;
    gPlanetAttributes[2] = t;

    t.mName = "mOrbitedPlanetLastKnownPosition";
    t.mHash = 0x37d2e7b;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00b6e3a0;
    t.mFnLoad = &FUN_00ac88c0;
    t.mFnParse = &ParseVector3;
    t.mFnEdit = &FUN_00695010;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &FUN_00acbba0;
    t.mOffset = 0x148;
    gPlanetAttributes[3] = t;

    t.mName = "mTimeSinceLastColonyPlaced";
    t.mHash = 0x57a58cf;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00ae3470;
    t.mFnLoad = &FUN_00ae3490;
    t.mFnParse = &UTFWin_ILayoutElement_SetSerializer;
    t.mFnEdit = &ClearBuffer;
    t.mFnUI = &FUN_00ae3310;
    t.mFnExtra = &FUN_00ac8050;
    t.mOffset = 0x198;
    gPlanetAttributes[4] = t;

    t.mName = "mPlanetFlags";
    t.mHash = 0x35d5a50;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00b72e30;
    t.mFnLoad = &FUN_00b74a40;
    t.mFnParse = &UTFWin_ILayoutElement_SetSerializer;
    t.mFnEdit = &ClearBuffer;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &FUN_00ac8050;
    t.mOffset = 0x1bc;
    gPlanetAttributes[5] = t;

    t.mName = "mPlanetKey";
    t.mHash = 0x355f943;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00572810;
    t.mFnLoad = &WriteUint32Value;
    t.mFnParse = &ParseULong;
    t.mFnEdit = &FUN_00694f00;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &Simulator_ToXml;
    t.mOffset = 0x140;
    gPlanetAttributes[6] = t;

    t.mName = "mNumSpecializedBehaviorUFOs";
    t.mHash = 0x519a04c;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00572810;
    t.mFnLoad = &WriteUint32Value;
    t.mFnParse = &ParseLong;
    t.mFnEdit = &FUN_00694ee0;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &FUN_0057cde0;
    t.mOffset = 0x108;
    gPlanetAttributes[7] = t;

    t.mName = "mImpostorModel";
    t.mHash = 0x3742a6e;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00ac87c0;
    t.mFnLoad = &FUN_00ac87f0;
    t.mFnParse = &FUN_00694c80;
    t.mFnEdit = &FUN_00694c10;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &FUN_00acbbc0;
    t.mOffset = 0x15c;
    gPlanetAttributes[8] = t;

    t.mName = "mEffectScript";
    t.mHash = 0x3742a83;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00572810;
    t.mFnLoad = &WriteUint32Value;
    t.mFnParse = &ParseULong;
    t.mFnEdit = &FUN_00694f00;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &Simulator_ToXml;
    t.mOffset = 0x16c;
    gPlanetAttributes[9] = t;

    t.mName = "mPlanetScale";
    t.mHash = 0x3741dd7;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00572810;
    t.mFnLoad = &FUN_00ac88f0;
    t.mFnParse = &ParseFloat;
    t.mFnEdit = &FUN_00694fc0;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &FUN_00acbb80;
    t.mOffset = 0x184;
    gPlanetAttributes[10] = t;

    t.mName = "mStarterWorldID";
    t.mHash = 0x3742ea6;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00572810;
    t.mFnLoad = &WriteUint32Value;
    t.mFnParse = &ParseULong;
    t.mFnEdit = &FUN_00694f00;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &Simulator_ToXml;
    t.mOffset = 0x144;
    gPlanetAttributes[11] = t;
}