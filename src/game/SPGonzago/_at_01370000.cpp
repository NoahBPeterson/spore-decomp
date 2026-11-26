// src/game/SPGonzago/_at_01370000.cpp -- startup initializers for the SPGonzago UI property tables, line colors and
// the radius/angle constants. Compiled from slice(s) s0137d820, s01373120 and s01364b20.
//
// Function bodies keep the compiler-visible shape of the retail code (declaration order, store order and
// __declspec(noinline) are codegen levers). Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" void FUN_013c7aa0();
extern "C" void FUN_013c7ab0();
extern "C" void FUN_013c7ac0();
extern "C" char g_1481e20[];

#include "game/types.h"

extern "C" int      __cdecl atexit(void (__cdecl*)());
extern "C" uint32_t __cdecl FNVHash(const char* name, uint32_t seed, int lowercased);  // 0x00932e80

// FNV-1a 32-bit offset basis, the seed every property and color name is hashed with.
static const uint32_t kFnvOffsetBasis = 0x811c9dc5;

// Property list nodes. The retail layouts are local stand-ins, not yet the canonical classes.
struct PropertyNode {
    const char*   mpKey;      // +0x00
    uint32_t      mHash;      // +0x04
    PropertyNode* mpNext;     // +0x08
};

struct GGEProperty : PropertyNode {    // 0x18 bytes
    float mValue0c;                    // +0x0c
    float mValue10;                    // +0x10
    float mValue14;                    // +0x14
};

struct UIProperty : PropertyNode {     // 0x18 bytes
    uint32_t mValue0c;                 // +0x0c
    uint32_t mValue10;                 // +0x10
    uint32_t mValue14;                 // +0x14
};

struct LineColorProperty : PropertyNode {  // 0x1c bytes
    float mRed;                            // +0x0c
    float mGreen;                          // +0x10
    float mBlue;                           // +0x14
    float mAlpha;                          // +0x18
};

// Color list entry used for the line colors that are pushed onto gpColorList.
class cColorEntry {
public:
    void*        mpClass;     // +0x00  (0x01481e20)
    uint32_t     mHash;       // +0x04
    cColorEntry* mpNext;      // +0x08
    float        mR;          // +0x0c
    float        mG;          // +0x10
    float        mB;          // +0x14
    float        mA;          // +0x18
};

// Layout singleton. Only the constructor-like call at 0x00810000 is needed here.
class cSPUILayout_s0136_4b20 {
public:
    cSPUILayout_s0136_4b20* FUN_00810000();                // 0x00810000 (constructor)
};

// Property tables and their key strings (addresses in the comments).
extern GGEProperty   kImpostorOffsetDialog;            // 0x016ac5e0
extern PropertyNode* sProgressBarProperties;           // 0x015a55e8
extern PropertyNode* sDialogLayoutProperties;          // 0x015a57d0
extern UIProperty    kProgressBarSuccessSound;         // 0x016ac318
extern UIProperty    kProgressBarFailSound;            // 0x016ac330
extern UIProperty    kBackgroundEffectID;              // 0x016ac618
extern LineColorProperty* sLineColorProperties;        // 0x015a59f4
extern LineColorProperty  kLineColorTop;               // 0x016ace34
extern LineColorProperty  kLineColorMiddle;            // 0x016ace50
extern const char g_propKey147d3b8;                    // 0x0147d3b8
extern const char g_propKey14811f0;                    // 0x014811f0
extern const char g_propKey1481e20;                    // 0x01481e20

// Line color constants (addresses in the comments).
extern const float kLineColorTopA;                     // 0x0144359c 0.03
extern const float kLineColorTopB;                     // 0x0148223c 0.44
extern const float kLineColorTopC;                     // 0x01482238 0.22
extern const float kLineColorMiddleA;                  // 0x01482254 0.29
extern const float kLineColorMiddleB;                  // 0x01482250 0.74
extern const float kLineColorMiddleC;                  // 0x013f6a20 0.85
extern const float kColorOne;                          // 0x01485720 1.0F
extern const float kColorRed;                          // 0x01482268
extern const float kColorGreen;                        // 0x013fe160
extern const float kColorBlue;                         // 0x01481ca8
extern const float kColorBorder;                       // 0x01482290

// Color list, and the three line colors that are pushed onto it.
extern cColorEntry*  gpColorList;                      // 0x015a59f4
extern cColorEntry   gLineColorBottom;                 // 0x016ace6c
extern cColorEntry   gLineColorDropShadow;             // 0x016ace88
extern cColorEntry   gLineColorBorder;                 // 0x016acea4

// Layout singleton and its init flag.
extern cSPUILayout_s0136_4b20 g_spuiLayout;            // 0x015a51bc
extern bool           g_spuiLayoutInitialized;         // 0x015a51d4

// atexit destructors (addresses in the comments).
extern void FUN_013c72d0();                            // 0x013c72d0
extern void FUN_013c75c0();                            // 0x013c75c0
extern void FUN_013c75d0();                            // 0x013c75d0
extern void FUN_013c78d0();                            // 0x013c78d0
extern void FUN_013c7900();                            // 0x013c7900
extern void FUN_013c7a80();                            // 0x013c7a80
extern void FUN_013c7a90();                            // 0x013c7a90

// Radius and angle constants used by FUN_0137ec20..FUN_0137ec60.
extern float gRadius;       // 0x015a7c68
extern float gRadiusSq;     // 0x016b3c34
extern float gRadiusCb;     // 0x016b3c38
extern float gAngleUnit;    // 0x015a7c24
extern float gAngleScale;   // 0x016b3c3c

#pragma warning(disable: 4100)

// ---- items of slice s0137e810 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_016b0c3cVtable[];            // 0x1482dfc
extern "C" void Func013c7d70();             // 0x13c7d70
struct InitObj {
    void** m_vtable;            // 0x00
    void* m_field04;            // 0x04
    void* m_field08;            // 0x08

    void Init();
};
extern InitObj g_016b0c3c;                  // 0x16b0c3c
// ---- items of slice s0137e810 end

// ---- items of slice s0137ea70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_f_015a7b98;   // 0x015a7b98
extern float g_f_016b39cc;   // 0x016b39cc
// ---- items of slice s0137ea70 end

// ---- items of slice s0137ea90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_16b39cc;   // 0x016b39cc
extern const float g_15a7b88;   // 0x015a7b88
extern const float g_140f334;   // 0x0140f334
extern const float g_140f32c;   // 0x0140f32c
extern float g_16b39d0;         // 0x016b39d0
// ---- items of slice s0137ea90 end

// @ 0x01370490
void init_15a51bc()
{
    g_spuiLayout.FUN_00810000();
    g_spuiLayoutInitialized = false;
    atexit(&FUN_013c72d0);
}

// @ 0x01370950
void init_16ac318()
{    struct LocalKey {
        uint32_t mInstance;
        uint32_t mType;
        uint32_t mGroup;
        LocalKey() : mInstance(0), mType(0), mGroup(0) {}
    };
    LocalKey k;
    kProgressBarSuccessSound.mHash = FNVHash("ProgressBarSuccessSound", 0x811c9dc5, 1);
    kProgressBarSuccessSound.mpNext = sProgressBarProperties;
    sProgressBarProperties = &kProgressBarSuccessSound;
    kProgressBarSuccessSound.mpKey = &g_propKey14811f0;
    *(LocalKey*)&kProgressBarSuccessSound.mValue0c = k;
    atexit(&FUN_013c75c0);}

// @ 0x013709b0
void init_16ac330()
{    struct LocalKey {
        uint32_t mInstance;
        uint32_t mType;
        uint32_t mGroup;
        LocalKey() : mInstance(0), mType(0), mGroup(0) {}
    };
    LocalKey k;
    kProgressBarFailSound.mHash = FNVHash("ProgressBarFailSound", 0x811c9dc5, 1);
    kProgressBarFailSound.mpNext = sProgressBarProperties;
    sProgressBarProperties = &kProgressBarFailSound;
    kProgressBarFailSound.mpKey = &g_propKey14811f0;
    *(LocalKey*)&kProgressBarFailSound.mValue0c = k;
    atexit(&FUN_013c75d0);}

// @ 0x013716e0
void init_16ac5e0()
{
    kImpostorOffsetDialog.mHash = FNVHash("ImpostorOffset", kFnvOffsetBasis, 1);
    kImpostorOffsetDialog.mpNext = sDialogLayoutProperties;
    sDialogLayoutProperties = &kImpostorOffsetDialog;
    kImpostorOffsetDialog.mpKey = &g_propKey147d3b8;
    kImpostorOffsetDialog.mValue0c = 0.0F;
    kImpostorOffsetDialog.mValue10 = 0.0F;
    kImpostorOffsetDialog.mValue14 = 0.0F;
    atexit(&FUN_013c78d0);
}

// @ 0x013717e0
void init_16ac618()
{    struct LocalKey {
        uint32_t mInstance;
        uint32_t mType;
        uint32_t mGroup;
        LocalKey() : mInstance(0), mType(0), mGroup(0) {}
    };
    LocalKey k;
    kBackgroundEffectID.mHash = FNVHash("BackgroundEffectID", 0x811c9dc5, 1);
    kBackgroundEffectID.mpNext = sDialogLayoutProperties;
    sDialogLayoutProperties = &kBackgroundEffectID;
    kBackgroundEffectID.mpKey = &g_propKey14811f0;
    *(LocalKey*)&kBackgroundEffectID.mValue0c = k;
    atexit(&FUN_013c7900);}

// @ 0x01373000
void init_16ace34()
{
    kLineColorTop.mHash = FNVHash("LineColorTop", kFnvOffsetBasis, 1);
    kLineColorTop.mRed = kLineColorTopA;
    kLineColorTop.mGreen = kLineColorTopB;
    kLineColorTop.mBlue = kLineColorTopC;
    kLineColorTop.mpNext = sLineColorProperties;
    sLineColorProperties = &kLineColorTop;
    kLineColorTop.mpKey = &g_propKey1481e20;
    kLineColorTop.mAlpha = kColorOne;
    atexit(&FUN_013c7a80);
}

// @ 0x01373090
void init_16ace50()
{
    kLineColorMiddle.mHash = FNVHash("LineColorMiddle", kFnvOffsetBasis, 1);
    kLineColorMiddle.mRed = kLineColorMiddleA;
    kLineColorMiddle.mGreen = kLineColorMiddleB;
    kLineColorMiddle.mBlue = kLineColorMiddleC;
    kLineColorMiddle.mpNext = sLineColorProperties;
    sLineColorProperties = &kLineColorMiddle;
    kLineColorMiddle.mpKey = &g_propKey1481e20;
    kLineColorMiddle.mAlpha = kColorOne;
    atexit(&FUN_013c7a90);
}

// @ 0x01373120
void __declspec(noinline) InitLineColorBottom()
{
    uint32_t nHash = FNVHash("LineColorBottom", kFnvOffsetBasis, 1);

    gLineColorBottom.mR = kColorRed;
    gLineColorBottom.mG = kColorGreen;
    float fB = kColorBlue;
    gLineColorBottom.mHash = nHash;
    gLineColorBottom.mpNext = gpColorList;
    gLineColorBottom.mB = fB;
    float fA = kColorOne;
    gpColorList = &gLineColorBottom;
    gLineColorBottom.mpClass = (void*)g_1481e20;  // g_propKey1481e20
    gLineColorBottom.mA = fA;

    atexit((void (__cdecl*)(void))FUN_013c7aa0);
}

// @ 0x013731b0
void __declspec(noinline) InitLineColorDropShadow()
{
    uint32_t nHash = FNVHash("LineColorDropShadow", kFnvOffsetBasis, 1);

    gLineColorDropShadow.mHash = nHash;
    gLineColorDropShadow.mpNext = gpColorList;
    gLineColorDropShadow.mR = 0.0f;
    gLineColorDropShadow.mG = 0.0f;
    gLineColorDropShadow.mB = 0.0f;
    float fA = kColorBlue;
    gpColorList = &gLineColorDropShadow;
    gLineColorDropShadow.mpClass = (void*)g_1481e20;  // g_propKey1481e20
    gLineColorDropShadow.mA = fA;

    atexit((void (__cdecl*)(void))FUN_013c7ab0);
}

// @ 0x01373220
void __declspec(noinline) InitLineColorBorder()
{
    uint32_t nHash = FNVHash("LineColorBorder", kFnvOffsetBasis, 1);

    float fRGB = kColorBorder;
    gLineColorBorder.mHash = nHash;
    gLineColorBorder.mpNext = gpColorList;
    gLineColorBorder.mR = fRGB;
    gLineColorBorder.mG = fRGB;
    gLineColorBorder.mB = fRGB;
    float fA = kColorOne;
    gpColorList = &gLineColorBorder;
    gLineColorBorder.mpClass = (void*)g_1481e20;  // g_propKey1481e20
    gLineColorBorder.mA = fA;

    atexit((void (__cdecl*)(void))FUN_013c7ac0);
}

// @ 0x0137e810
void InitObject()
{
    g_016b0c3c.Init();
    g_016b0c3c.m_vtable = g_016b0c3cVtable;
    atexit(Func013c7d70);
}

// @ 0x0137ea70
void FUN_0137ea70()
{
    float v = g_f_015a7b98;
    g_f_016b39cc = v * v * v;
}

// @ 0x0137ea90
void FUN_0137ea90()
{
    g_16b39d0 = g_140f32c / (g_16b39cc * g_15a7b88 * g_140f334);
}

// @ 0x0137ec20
void FUN_0137ec20(void)
{ gRadiusSq = gRadius * gRadius; }

// @ 0x0137ec40
void FUN_0137ec40(void)
{ gRadiusCb = gRadius * gRadius * gRadius; }

// @ 0x0137ec60
void FUN_0137ec60(void)
{ gAngleScale = 315.0f / ((gRadiusCb * gAngleUnit) * 64.0f); }
