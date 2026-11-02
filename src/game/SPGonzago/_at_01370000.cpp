// src/game/SPGonzago/_at_01370000.cpp -- migrated from slice(s) s0137d820, s01373120, s01364b20 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_01370000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int      __cdecl atexit(void (__cdecl*)());
extern "C" uint32_t __cdecl FNVHash(const char* name, uint32_t seed, int lowercased);  // 0x00932e80
extern const char g_propKey147d3b8;                        // 0x0147d3b8
extern const char g_propKey14811f0;                        // 0x014811f0
extern const char g_propKey1481e20;                        // 0x01481e20
extern const float kLineColorTopA;                         // 0x0144359c 0.03
extern const float kLineColorTopB;                         // 0x0148223c 0.44
extern const float kLineColorTopC;                         // 0x01482238 0.22
extern const float kLineColorMiddleA;                      // 0x01482254 0.29
extern const float kLineColorMiddleB;                      // 0x01482250 0.74
extern const float kLineColorMiddleC;                      // 0x013f6a20 0.85
extern const float kColorOne;                              // 0x01485720 1.0F
extern void FUN_013c75c0();                                // 0x013c75c0 atexit destructor
extern void FUN_013c75d0();                                // 0x013c75d0 atexit destructor
extern void FUN_013c78d0();                                // 0x013c78d0 atexit destructor
extern void FUN_013c7900();                                // 0x013c7900 atexit destructor
extern void FUN_013c7a80();                                // 0x013c7a80 atexit destructor
extern void FUN_013c7a90();                                // 0x013c7a90 atexit destructor
extern bool        g_spuiLayoutInitialized;                // 0x015a51d4
extern void        FUN_013c72d0();                         // 0x013c72d0 atexit destructor
#pragma warning(disable: 4100)

// ---- items of slice s01364b20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int      __cdecl atexit(void (__cdecl*)());
extern "C" uint32_t __cdecl FNVHash(const char* name, uint32_t seed, int lowercased);  // 0x00932e80
struct PropertyNode {
    const char*  mpKey;                                    // +0x00
    uint32_t     mHash;                                    // +0x04
    PropertyNode* mpNext;                                  // +0x08
};
struct GGEProperty : PropertyNode {                        // 0x18 bytes
    float        mValue0c;                                 // +0x0c
    float        mValue10;                                 // +0x10
    float        mValue14;                                 // +0x14
};
struct UIProperty : PropertyNode {                         // 0x18 bytes
    uint32_t     mValue0c;                                 // +0x0c
    uint32_t     mValue10;                                 // +0x10
    uint32_t     mValue14;                                 // +0x14
};
struct LineColorProperty : PropertyNode {                  // 0x1c bytes
    float        mRed;                                     // +0x0c
    float        mGreen;                                   // +0x10
    float        mBlue;                                    // +0x14
    float        mAlpha;                                   // +0x18
};
extern GGEProperty  kImpostorOffsetDialog;                 // 0x016ac5e0
extern PropertyNode* sProgressBarProperties;              // 0x015a55e8
extern PropertyNode* sDialogLayoutProperties;             // 0x015a57d0
extern UIProperty   kProgressBarSuccessSound;              // 0x016ac318
extern UIProperty   kProgressBarFailSound;                 // 0x016ac330
extern UIProperty   kBackgroundEffectID;                   // 0x016ac618
extern LineColorProperty* sLineColorProperties;            // 0x015a59f4
extern LineColorProperty  kLineColorTop;                   // 0x016ace34
extern LineColorProperty  kLineColorMiddle;                // 0x016ace50
extern const char g_propKey147d3b8;                        // 0x0147d3b8
extern const char g_propKey14811f0;                        // 0x014811f0
extern const char g_propKey1481e20;                        // 0x01481e20
extern const float kLineColorTopA;                         // 0x0144359c 0.03
extern const float kLineColorTopB;                         // 0x0148223c 0.44
extern const float kLineColorTopC;                         // 0x01482238 0.22
extern const float kLineColorMiddleA;                      // 0x01482254 0.29
extern const float kLineColorMiddleB;                      // 0x01482250 0.74
extern const float kLineColorMiddleC;                      // 0x013f6a20 0.85
extern const float kColorOne;                              // 0x01485720 1.0F
extern void FUN_013c75c0();                                // 0x013c75c0 atexit destructor
extern void FUN_013c75d0();                                // 0x013c75d0 atexit destructor
extern void FUN_013c78d0();                                // 0x013c78d0 atexit destructor
extern void FUN_013c7900();                                // 0x013c7900 atexit destructor
extern void FUN_013c7a80();                                // 0x013c7a80 atexit destructor
extern void FUN_013c7a90();                                // 0x013c7a90 atexit destructor
class cSPUILayout_s0136_4b20 {
public:
    cSPUILayout_s0136_4b20* FUN_00810000();                           // 0x00810000 (constructor)
};
extern cSPUILayout_s0136_4b20 g_spuiLayout;                           // 0x015a51bc
extern bool        g_spuiLayoutInitialized;                // 0x015a51d4
extern void        FUN_013c72d0();                         // 0x013c72d0 atexit destructor
// ---- items of slice s01364b20 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern GGEProperty  kImpostorOffsetDialog;                 // 0x016ac5e0
extern PropertyNode* sProgressBarProperties;              // 0x015a55e8
extern PropertyNode* sDialogLayoutProperties;             // 0x015a57d0
extern UIProperty   kProgressBarSuccessSound;              // 0x016ac318
extern UIProperty   kProgressBarFailSound;                 // 0x016ac330
extern UIProperty   kBackgroundEffectID;                   // 0x016ac618
extern LineColorProperty* sLineColorProperties;            // 0x015a59f4
extern LineColorProperty  kLineColorTop;                   // 0x016ace34
extern LineColorProperty  kLineColorMiddle;                // 0x016ace50
extern cSPUILayout_s0136_4b20 g_spuiLayout;                           // 0x015a51bc

// ---- items of slice s01373120 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float gColorRed_1482268;     // 0x01482268
extern const float gColorGreen_13fe160;   // 0x013fe160
extern const float gColorBlue_1481ca8;    // 0x01481ca8
extern const float gColorBorder_1482290;  // 0x01482290
extern const float gColorOne_1485720;     // 0x01485720
class cColorEntry
{
public:
    void*         mpClass;                // +0x00  (0x01481e20)
    uint32_t      mHash;                  // +0x04
    cColorEntry*  mpNext;                 // +0x08
    float         mR;                     // +0x0c
    float         mG;                     // +0x10
    float         mB;                     // +0x14
    float         mA;                     // +0x18
};
extern cColorEntry* gpColorList;          // 0x015a59f4
extern cColorEntry  gLineColorBottom;     // 0x016ace6c
extern cColorEntry  gLineColorDropShadow; // 0x016ace88
extern cColorEntry  gLineColorBorder;     // 0x016acea4
// ---- items of slice s01373120 end

// ---- items of slice s0137d820 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gRadius;       // 0x015a7c68
extern float gRadiusSq;     // 0x016b3c34
extern float gRadiusCb;     // 0x016b3c38
extern float gAngleUnit;    // 0x015a7c24
extern float gAngleScale;   // 0x016b3c3c
// ---- items of slice s0137d820 end

// @ 0x01370490
void init_15a51bc()
{
    g_spuiLayout.FUN_00810000();
    g_spuiLayoutInitialized = false;
    atexit(&FUN_013c72d0);
}

// @ 0x01370950
void init_16ac318()
{
    kProgressBarSuccessSound.mHash = FNVHash("ProgressBarSuccessSound", 0x811c9dc5, 1);
    kProgressBarSuccessSound.mpNext = sProgressBarProperties;
    sProgressBarProperties = &kProgressBarSuccessSound;
    kProgressBarSuccessSound.mpKey = &g_propKey14811f0;
    kProgressBarSuccessSound.mValue0c = 0;
    kProgressBarSuccessSound.mValue10 = 0;
    kProgressBarSuccessSound.mValue14 = 0;
    atexit(&FUN_013c75c0);
}

// @ 0x013709b0
void init_16ac330()
{
    kProgressBarFailSound.mHash = FNVHash("ProgressBarFailSound", 0x811c9dc5, 1);
    kProgressBarFailSound.mpNext = sProgressBarProperties;
    sProgressBarProperties = &kProgressBarFailSound;
    kProgressBarFailSound.mpKey = &g_propKey14811f0;
    kProgressBarFailSound.mValue0c = 0;
    kProgressBarFailSound.mValue10 = 0;
    kProgressBarFailSound.mValue14 = 0;
    atexit(&FUN_013c75d0);
}

// @ 0x013716e0
void init_16ac5e0()
{
    kImpostorOffsetDialog.mHash = FNVHash("ImpostorOffset", 0x811c9dc5, 1);
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
{
    kBackgroundEffectID.mHash = FNVHash("BackgroundEffectID", 0x811c9dc5, 1);
    kBackgroundEffectID.mpNext = sDialogLayoutProperties;
    sDialogLayoutProperties = &kBackgroundEffectID;
    kBackgroundEffectID.mpKey = &g_propKey14811f0;
    kBackgroundEffectID.mValue0c = 0;
    kBackgroundEffectID.mValue10 = 0;
    kBackgroundEffectID.mValue14 = 0;
    atexit(&FUN_013c7900);
}

// @ 0x01373000
void init_16ace34()
{
    kLineColorTop.mHash = FNVHash("LineColorTop", 0x811c9dc5, 1);
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
    kLineColorMiddle.mHash = FNVHash("LineColorMiddle", 0x811c9dc5, 1);
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
    uint32_t nHash = FNVHash("LineColorBottom", 0x811c9dc5, 1);

    gLineColorBottom.mR = gColorRed_1482268;
    gLineColorBottom.mG = gColorGreen_13fe160;
    float fB = gColorBlue_1481ca8;
    gLineColorBottom.mHash = nHash;
    gLineColorBottom.mpNext = gpColorList;
    gLineColorBottom.mB = fB;
    float fA = gColorOne_1485720;
    gpColorList = &gLineColorBottom;
    gLineColorBottom.mpClass = (void*)0x01481e20;
    gLineColorBottom.mA = fA;

    atexit((void (__cdecl*)(void))0x013c7aa0);
}

// @ 0x013731b0
void __declspec(noinline) InitLineColorDropShadow()
{
    uint32_t nHash = FNVHash("LineColorDropShadow", 0x811c9dc5, 1);

    gLineColorDropShadow.mHash = nHash;
    gLineColorDropShadow.mpNext = gpColorList;
    gLineColorDropShadow.mR = 0.0f;
    gLineColorDropShadow.mG = 0.0f;
    gLineColorDropShadow.mB = 0.0f;
    float fA = gColorBlue_1481ca8;
    gpColorList = &gLineColorDropShadow;
    gLineColorDropShadow.mpClass = (void*)0x01481e20;
    gLineColorDropShadow.mA = fA;

    atexit((void (__cdecl*)(void))0x013c7ab0);
}

// @ 0x01373220
void __declspec(noinline) InitLineColorBorder()
{
    uint32_t nHash = FNVHash("LineColorBorder", 0x811c9dc5, 1);

    float fRGB = gColorBorder_1482290;
    gLineColorBorder.mHash = nHash;
    gLineColorBorder.mpNext = gpColorList;
    gLineColorBorder.mR = fRGB;
    gLineColorBorder.mG = fRGB;
    gLineColorBorder.mB = fRGB;
    float fA = gColorOne_1485720;
    gpColorList = &gLineColorBorder;
    gLineColorBorder.mpClass = (void*)0x01481e20;
    gLineColorBorder.mA = fA;

    atexit((void (__cdecl*)(void))0x013c7ac0);
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
