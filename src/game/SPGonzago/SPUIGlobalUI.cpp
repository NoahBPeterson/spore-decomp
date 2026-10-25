// src/game/SPGonzago/SPUIGlobalUI.cpp -- migrated from slice(s) s00e033d0, s00e02580, s00e01750 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIGlobalUI.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cString.h"
#include "cSPUILayoutManager.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl EA_Allocate(uint32_t size, const char* name, int a, int b,
                                     int c, int d);              // 0xf473a0
extern "C" void* __cdecl SP_GetCurrentGameMode();                // 0xb5b800
extern "C" void* __cdecl SP_MessageServer();                     // 0x67dcc0
extern "C" void* __cdecl SP_WindowManager();                     // 0x67caa0
extern "C" void* __cdecl SP_GameTimeManager();                   // 0xb3d380
extern "C" void* __cdecl SP_GetUniverseContext();                // 0x1021080
extern "C" void* __cdecl SP_GetPlayerHomePlanet();               // 0x1021370
extern "C" void* __cdecl SP_GetActivePlanet();                   // 0x1021260
extern "C" void* __cdecl SP_PropertyManager();                   // 0x67de30
extern "C" void* __cdecl SP_CivModeStrategyGet();                // 0xcf74c0
extern "C" void* __cdecl SP_TribeModeStrategyInstance();         // 0xcd40b0
extern "C" void* __cdecl SP_GetSetting3();                       // 0x401030
extern "C" void* __cdecl SP_SpaceGameGet();                      // 0x1002bd0
extern "C" char  __cdecl FUN_00e01390();                         // 0xe01390
extern "C" char  __cdecl FUN_00e014a0();                         // 0xe014a0
extern "C" void* __cdecl FUN_009512c0();                         // 0x9512c0
extern "C" void* __cdecl FUN_009512d0(uint32_t, int, const char*, void*); // 0x9512d0
extern "C" void* __cdecl FUN_00835cc0(void*);                    // 0x835cc0 tooltip ctor
extern "C" void* __cdecl FUN_00c707e0(void*);                    // 0xc707e0 cPlanet::GetName
extern "C" void  __cdecl FUN_0064a990(void*);                    // 0x64a990 AdvancedLaunch
extern "C" void  __cdecl FUN_0064aba0(void*);                    // 0x64aba0 LaunchSporeGuide
extern "C" void* __cdecl FUN_00fd9c60(void*);                    // 0xfd9c60
extern "C" void* __cdecl FUN_0067cab0();                         // 0x67cab0
extern "C" void  __cdecl FUN_00809db0(void*, void*);             // 0x809db0 CalloutMessageBox
extern "C" void* __cdecl FUN_00a16f40(void*);                    // 0xa16f40 AsPPTypeParam
extern "C" void  __cdecl FUN_006a12a0(void*, uint32_t, void*);   // 0x6a12a0 GetPropertyAsKeyInstance
extern "C" void* __cdecl FUN_010666a0();                         // 0x10666a0
extern "C" uint8_t      g_bPaused;       // @ 0x16a1890
extern "C" char g_vtblContentValidationSummarizer[];  // @ 0x13ec458
extern "C" char g_vtblListenerBase[];                 // @ 0x13eb384
extern "C" char g_vtblNetworkActivityProc[];          // @ 0x147f0dc
extern "C" char g_vtblNetworkActivityProc04[];        // @ 0x147f0cc
extern "C" char g_vtblNetworkActivityProc0c[];        // @ 0x147f0bc

// ---- items of slice s00e01750 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EA_Allocate(uint32_t size, const char* name, int a, int b,
                                     int c, int d);              // 0xf473a0
extern "C" void* __cdecl SP_GetCurrentGameMode();                // 0xb5b800
extern "C" void* __cdecl SP_MessageServer();                     // 0x67dcc0
extern "C" void* __cdecl SP_WindowManager();                     // 0x67caa0
extern "C" void* __cdecl SP_GameTimeManager();                   // 0xb3d380
extern "C" void* __cdecl SP_GetUniverseContext();                // 0x1021080
extern "C" void* __cdecl SP_GetPlayerHomePlanet();               // 0x1021370
extern "C" void* __cdecl SP_GetActivePlanet();                   // 0x1021260
extern "C" void* __cdecl SP_PropertyManager();                   // 0x67de30
extern "C" void* __cdecl SP_CivModeStrategyGet();                // 0xcf74c0
extern "C" void* __cdecl SP_TribeModeStrategyInstance();         // 0xcd40b0
extern "C" void* __cdecl SP_GetSetting3();                       // 0x401030
extern "C" void* __cdecl SP_SpaceGameGet();                      // 0x1002bd0
extern "C" char  __cdecl FUN_00e01390();                         // 0xe01390
extern "C" char  __cdecl FUN_00e014a0();                         // 0xe014a0
extern "C" void* __cdecl FUN_009512c0();                         // 0x9512c0
extern "C" void* __cdecl FUN_009512d0(uint32_t, int, const char*, void*); // 0x9512d0
extern "C" void* __cdecl FUN_00835cc0(void*);                    // 0x835cc0 tooltip ctor
extern "C" void* __cdecl FUN_00c707e0(void*);                    // 0xc707e0 cPlanet::GetName
extern "C" void  __cdecl FUN_0064a990(void*);                    // 0x64a990 AdvancedLaunch
extern "C" void  __cdecl FUN_0064aba0(void*);                    // 0x64aba0 LaunchSporeGuide
extern "C" void* __cdecl FUN_00fd9c60(void*);                    // 0xfd9c60
extern "C" void* __cdecl FUN_0067cab0();                         // 0x67cab0
extern "C" void  __cdecl FUN_00809db0(void*, void*);             // 0x809db0 CalloutMessageBox
extern "C" void* __cdecl FUN_00a16f40(void*);                    // 0xa16f40 AsPPTypeParam
extern "C" void  __cdecl FUN_006a12a0(void*, uint32_t, void*);   // 0x6a12a0 GetPropertyAsKeyInstance
extern "C" void* __cdecl FUN_010666a0();                         // 0x10666a0
struct GlobalState {                     // @ 0x16c7aa4
    uint8_t pad00[0xcc];
    int     mFieldCC;                    // +0xcc
    int     mFieldD0;                    // +0xd0
};
extern "C" GlobalState* g_pGlobalState;  // @ 0x16c7aa4
class cTranslator;                       // cSPEditorShoppingTokenTranslator
extern "C" cTranslator* g_pTranslator;   // @ 0x15ee298
extern "C" uint8_t      g_bPaused;       // @ 0x16a1890
extern "C" char g_vtblContentValidationSummarizer[];  // @ 0x13ec458
extern "C" char g_vtblListenerBase[];                 // @ 0x13eb384
extern "C" char g_vtblNetworkActivityProc[];          // @ 0x147f0dc
extern "C" char g_vtblNetworkActivityProc04[];        // @ 0x147f0cc
extern "C" char g_vtblNetworkActivityProc0c[];        // @ 0x147f0bc
class cVtblObj {
public:
    virtual void* v000();
    virtual void* v004();
    virtual void* v008();
    virtual void* v00c(uint32_t id);                    // 0x00c  make/attach child
    virtual void* v010();
    virtual void* v014(uint32_t, void*, void*);         // 0x014  message send
virtual void* v018();
virtual void* v01c();
virtual void* v020();
virtual void* v024();
virtual void* v028();
virtual void* v02c();
    virtual void* v030(uint32_t, void*);                // 0x030  property set
virtual void* v034();
virtual void* v038();
virtual void* v03c();
virtual void* v040();
virtual void* v044();
virtual void* v048();
virtual void* v04c();
virtual void* v050();
virtual void* v054();
virtual void* v058();
virtual void* v05c();
virtual void* v060();
virtual void* v064();
virtual void* v068();
virtual void* v06c();
    virtual void* v070();                               // 0x070
virtual void* v074();
virtual void* v078();
    virtual void* v07c(int, void*);                     // 0x07c  set visual state
virtual void* v080();
virtual void* v084();
virtual void* v088();
virtual void* v08c();
virtual void* v090();
virtual void* v094();
virtual void* v098();
virtual void* v09c();
virtual void* v0a0();
virtual void* v0a4();
virtual void* v0a8();
virtual void* v0ac();
virtual void* v0b0();
virtual void* v0b4();
virtual void* v0b8();
virtual void* v0bc();
virtual void* v0c0();
virtual void* v0c4();
virtual void* v0c8();
virtual void* v0cc();
virtual void* v0d0();
virtual void* v0d4();
virtual void* v0d8();
virtual void* v0dc();
virtual void* v0e0();
virtual void* v0e4();
virtual void* v0e8();
virtual void* v0ec();
virtual void* v0f0();
virtual void* v0f4();
virtual void* v0f8();
virtual void* v0fc();
    virtual void* v100();
    virtual void* v104(void* child);                    // 0x104  attach child object
};
class cSPUILayout_s00e0_1750 {
public:
    cVtblObj* FindWindowByID(uint32_t id, int a);       // va 008105b0 0x008105b0
};
class cSPUITooltipWinProc_s00e0_1750 {
public:
    virtual void* v000();                               // 0x00
    virtual void* v004();                               // 0x04
    void SetText(const wchar_t* text, void* a, char b); // va 00835ed0 0x00835ed0
};
namespace SP {
class cString_s00e0_1750 {
public:
    cString_s00e0_1750(uint32_t a, uint32_t b, const wchar_t* c);  // va 006b55c0+0x1b0 (0x6b5770)
    const wchar_t* GetText();                           // va 006b55c0
    ~cString_s00e0_1750();                                         // va 006b5240
};
}
class cStopwatch {
public:
    void Restart();                                     // va 00571e80
};
class cGameTimeManager {
public:
    void IncPauseGate(uint32_t id);                     // va 00b32220
};
class cCurMgr {
public:
    void* GetSystem();                                  // va 008013b0
    void  FindGlobal(uint32_t id);                      // va 00801b60
};
class cSPUIGlobalUI {
public:
    void SetVisibility(int visible);                    // va 00e01350
};
class cAppModeSpace {
public:
    void TransitionFromPlanetToSolar();                 // va 00fde3e0
};
class cCivStrategy {
public:
    void* GetState();                                   // va 00cf74f0
};
class cTribeStrategy : public cVtblObj {
public:
    char TerrainNotHasKey();                            // va 00cd44a0
};
class cSpaceMode {
public:
    char Check();                                       // va 01065e20
};
class cEffectRef {
public:
    char IsActive();                                    // va 00d09660
};
class cBrowser {
public:
    char CanSporepediaShowSporeGuide();                 // va 00644df0
    void ShowSporeGuide();                              // va 0064b6a0
};
class cTranslator {
public:
    void SetUserName(void* name);                       // va 005cd160
};
struct SpLaunch {
    uint32_t mHash;                                     // +0x00
    uint32_t mMode;                                     // +0x04
    uint8_t  pad08[0x40];                               // +0x08 (launcher payload)
};
class cSporeLaunchCtx {
public:
    void Init(void* param);                             // va 00e01570
    void Finish();                                      // va 00644b60
};
struct cActiveView {
    uint8_t pad00[0x289];
    uint8_t mActive;                                    // +0x289
};
struct NetworkActivityProc {
    void*   mVtbl00;                                    // +0x00
    void*   mVtbl04;                                    // +0x04
    void*   mField08;                                   // +0x08
    void*   mVtbl0c;                                    // +0x0c
    float   mF10;                                       // +0x10
    float   mF14;                                       // +0x14
    float   mF18;                                       // +0x18
    float   mF1c;                                       // +0x1c
    float   mF20;                                       // +0x20
    float   mF24;                                       // +0x24
    uint8_t mB28;                                       // +0x28
    uint8_t pad29[3];
    void*   mField2c;                                   // +0x2c
    void*   mField30;                                   // +0x30
};
class cSPUIGlobalOptions {
public:
    uint8_t      pad00[0x10];
    cSPUILayout_s00e0_1750* mLayout;                               // +0x10
    cVtblObj*    mWin14;                                // +0x14
    cVtblObj*    mWin18;                                // +0x18
    cVtblObj*    mWin1c;                                // +0x1c
    cVtblObj*    mWin20;                                // +0x20
    void Update();
};
class cSPUIGlobalUIRootWinProc {
public:
    uint8_t        pad00[0x24];
    int            mState;                              // +0x24
    cStopwatch     mTimer;                              // +0x28
    uint8_t        pad2c[0x2c];
    void*          mField58;                            // +0x58
    cSPUIGlobalUI* mUI;                                 // +0x5c
    void OnModalWindowEnd(uint32_t wparam, uint32_t msg);
};
enum SpGameMode : uint32_t {
    kModeC00  = 0x1654c00,
    kModeC01  = 0x1654c01,
    kModeC02  = 0x1654c02,
    kModeC03  = 0x1654c03,
    kModeC04  = 0x1654c04,
    kModeC05  = 0x1654c05,
    kModeC10  = 0x1654c10,
    kModeNone = 0xffffffff,
    kModeGal  = 0x2ccd1d2
};
struct SPUILayout2 {
    void* FindWindowByID(void* id, int a);
    void  SetVisibility(void* v);
    void  Init(void* a, int b, int c);
    void  SetReloadCallback(void* cb, void* arg);
};
static void AssignWindow(cVtblObj** slot, cVtblObj* w) {
    cVtblObj* old = *slot;
    if (w != old) {
        if (w) w->v000();
        *slot = w;
        if (old) old->v004();
    }
}
static void InitNetworkActivityProc(NetworkActivityProc* p) {
    p->mVtbl04 = g_vtblContentValidationSummarizer;  // base ctor store (overwritten)
    p->mField08 = 0;
    p->mVtbl0c = g_vtblListenerBase;                 // base ctor store (overwritten)
    p->mVtbl00 = g_vtblNetworkActivityProc;
    p->mVtbl04 = g_vtblNetworkActivityProc04;
    p->mVtbl0c = g_vtblNetworkActivityProc0c;
    p->mF10 = 0.0f;
    p->mF14 = 0.0f;
    p->mF18 = 1.0f;
    p->mF1c = 0.0f;
    p->mF20 = 0.0f;
    p->mF24 = 0.0f;
    p->mB28 = 0;
    p->mField2c = 0;
    p->mField30 = 0;
}
static void MakeTooltip(cVtblObj* win, uint32_t textId) {
    win->v07c(2, 0);
    cSPUITooltipWinProc_s00e0_1750* tip;
    void* mem = FUN_009512d0(0x68, 4, "UI/cSPUITooltipWinProc", FUN_009512c0());
    if (mem) {
        tip = (cSPUITooltipWinProc_s00e0_1750*)FUN_00835cc0(mem);
        if (tip) tip->v000();
    } else {
        tip = 0;
    }
    {
        SP::cString_s00e0_1750 text(0xc0152a6d, textId, 0);
        tip->SetText(text.GetText(), (void*)-1, 1);
    }
    win->v104(tip);
    if (tip) tip->v004();
}
static void PauseGateOnce() {
    if (g_bPaused == 0) {
        ((cGameTimeManager*)SP_GameTimeManager())->IncPauseGate(0x4bf38a7);
    }
    g_bPaused = 1;
}
static void SpaceUniverseTransition() {
    if ((uint32_t)SP_GetCurrentGameMode() == (uint32_t)kModeC05 &&
        SP_GetUniverseContext() == 0) {
        ((cAppModeSpace*)FUN_00fd9c60(0))->TransitionFromPlanetToSolar();
    }
}
struct Ctl { char pad[8]; void* f08; };
struct GlobalOpts2 {
    char pad[0x5c];
    Ctl* p5c;
    void* FindWin(void* id);
};
struct PlanetInfo { uint8_t pad00[0x18]; void* mName; };  // planet object name at +0x18
struct PlanetName { void* mName; };                        // cPlanet::GetName result
struct CivStrategyData { uint8_t pad00[0x148]; uint8_t mField148; };
struct EffectSlots {
    uint8_t pad00[0x20];
    void*   mField20;                                   // +0x20
    uint8_t pad24[0x38];
    void*   mField5c;                                   // +0x5c
    uint8_t pad60[0x20];
    void*   mField80;                                   // +0x80
};
// ---- items of slice s00e01750 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" GlobalState* g_pGlobalState;  // @ 0x16c7aa4
extern "C" cTranslator* g_pTranslator;   // @ 0x15ee298

// ---- items of slice s00e02580 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char  g147f09c;        // 0x0147f09c
extern char  g147f0a0;        // 0x0147f0a0
extern char  g147f0a4;        // 0x0147f0a4
extern char  g147f0a8;        // 0x0147f0a8
extern char  g147f0ac;        // 0x0147f0ac
typedef unsigned int   uint32;
void*     MessageServer();                             // 0x0067dcc0
void*     FUN_00b3d410();                              // 0x00b3d410
char      FUN_00e00a40();                              // 0x00e00a40
char      FUN_00e00c40();                              // 0x00e00c40
void*     FUN_00b3d380();                              // 0x00b3d380  GameTimeManager
void*     FUN_00b5b800();                              // 0x00b5b800  GetCurrentGameMode
void*     FUN_01021080();                              // 0x01021080  GetUniverseContext
void*     FUN_0067cac0();                              // 0x0067cac0  (returns cUIHints*)
void*     FUN_0067cae0();                              // 0x0067cae0
void*     FUN_00cf74c0();                              // 0x00cf74c0  cCivModeStrategy::Get
void*     FUN_00cd40b0();                              // 0x00cd40b0  cTribeModeStrategy::Instance
void      FUN_00e3c6f0(int a, int b);                  // 0x00e3c6f0
void* __stdcall FUN_00b3d3f0(int a);                   // 0x00b3d3f0
void* __stdcall FUN_00b3d3e0(int a, int b, int c, int d, int e, int f); // 0x00b3d3e0 EventLog
void* __stdcall FUN_0067de90(int a);                   // 0x0067de90
void*     FUN_00572020(void* p, int v);                // 0x00572020
void*     FUN_00435ed0(uint32 id, void* p);            // 0x00435ed0  KillSetiEffects
void      FUN_00e009f0();                              // 0x00e009f0  on_ban_content_button
void  __fastcall FUN_0067c960(void* self);             // 0x0067c960  cUIHints::Update
void  __fastcall FUN_005fdf40(void* self);             // 0x005fdf40  AchievementNotifier::Update
char  __fastcall FUN_00e36fa0(void* self);             // 0x00e36fa0  (thiscall)
char  __fastcall FUN_00e393b0(void* self);             // 0x00e393b0  (thiscall)
char  __fastcall FUN_00cd44a0(void* self);             // 0x00cd44a0  (thiscall)
char  __fastcall FUN_01065e20(void* self);             // 0x01065e20  (thiscall)
void  __fastcall FUN_00e190c0(void* self);             // 0x00e190c0  (thiscall)
void  __fastcall FUN_00dd8640(void* self);             // 0x00dd8640  PostFeedbackEvent
struct Telemetry { void Flush(); };                    // 0x007ebce0
typedef void   (__thiscall *VF2)(void*, int, int);
typedef void   (__thiscall *VF3)(void*, int, int, int);
typedef void   (__thiscall *VF4)(void*, int, int, int, int);
typedef char   (__thiscall *VFC)(void*);
struct GameTimeManager {
    void  IncPauseGate(int v);                   // 0x00b32220
    void  DecPauseGate(int v);                   // 0x00b32250
    char  pad_00[0x48];
    uint32 m48;                                  // +0x48
};
struct ObjB {                                    // the object at [this+0x5c]+4
    char  pad_00[0x0c];
    char  m0c;                                   // +0x0c  byte flag
    char  pad_0d[0x14 - 0x0d];
    void* m14;                                   // +0x14
    char  pad_18[0x1c - 0x18];
    void* m1c;                                   // +0x1c
    char  pad_20[0x24 - 0x20];
    void* m24;                                   // +0x24
};
struct ObjA {                                    // the object at [this+0x5c]
    char  pad_00[4];
    ObjB* m04;                                   // +0x04
};
class UIThing {
public:
    char     pad_00[4];
    void*    m04;                                // +0x04  AutoRefCount<GlobalOptions>
    void*    m08;                                // +0x08  cSPUILayout*
    char     m0c;                                // +0x0c  byte flag
    char     pad_0d[3];
    void*    m10;                                // +0x10  cSPUILayout*
    uint32   m14;                                // +0x14
    void*    m18;                                // +0x18  window
    void*    m1c;                                // +0x1c
    void*    m20;                                // +0x20  window
    uint32   m24;                                // +0x24  state
    uint32   m28;                                // +0x28
    uint32   m2c;                                // +0x2c
    char     pad_30[0x3c - 0x30];
    uint32   m3c;                                // +0x3c
    uint32   m40;                                // +0x40
    uint32   m44;                                // +0x44
    char     pad_48[0x54 - 0x48];
    uint32   m54;                                // +0x54
    char     pad_58[4];
    ObjA*    m5c;                                // +0x5c

    void  FUN_00e02580(unsigned char enable);
    void  FUN_00e02900();
    void  FUN_00e02950();
    void  FUN_00e02a20();
    char  FUN_00e02af0();
    void  FUN_00e02e10();
    void  FUN_00e02e80();
    char  FUN_00e02f00(int a, void* msg);

    void  Enable(char v);                        // 0x00e018c0
    void* FindWindowByID(uint32 id);             // 0x00e01ce0
    void  FUN_00e00bb0();                        // 0x00e00bb0
    void  FUN_00e00bd0();                        // 0x00e00bd0
    void  FUN_00e00bf0();                        // 0x00e00bf0
    void  FUN_00e01d00();                        // 0x00e01d00  ShowTransition
    void  FUN_00e01270();                        // 0x00e01270
};
// ---- items of slice s00e02580 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_00e02c40();  // 0x00e02c40 (stays in the slice: not this object's)

// ---- items of slice s00e033d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl cof_new(unsigned, const char*, int, int, const char*, int); // 0xf473a0
extern "C" int   __cdecl FUN_00685520(int);                     // 0x00685520 IsWorldLayoutFlagSet
extern "C" void* __cdecl FUN_0067de40();                        // 0x0067de40
extern "C" void* __cdecl FUN_008105b0(int, int, int);           // 0x008105b0
extern "C" void* __cdecl FUN_0067dcc0();                        // 0x0067dcc0 MessageServer
extern "C" void* __cdecl FUN_00b5b820();                        // 0x00b5b820 GetCurrentGameModeAlt
extern "C" void* __cdecl FUN_00e01620(int, int);                // 0x00e01620
extern "C" char  __cdecl FUN_00e00ac0();                        // 0x00e00ac0
extern "C" char  __cdecl FUN_00e09540();                        // 0x00e09540
extern "C" char  __cdecl FUN_00dd1230();                        // 0x00dd1230
extern "C" void  __cdecl FUN_00e02200();                        // 0x00e02200
extern "C" void  __cdecl FUN_00e09600();                        // 0x00e09600
extern "C" void  __cdecl FUN_00e097c0();                        // 0x00e097c0
extern "C" void  __cdecl FUN_00dd14b0();                        // 0x00dd14b0
extern "C" void  __cdecl FUN_00dd12f0();                        // 0x00dd12f0
extern "C" void  __cdecl FUN_00e02e10(void*);                   // 0x00e02e10
typedef void  (__thiscall* TFnV)(void*);
typedef void  (__thiscall* TFnVI)(void*, int);
typedef void  (__thiscall* TFnVII)(void*, int, int);
typedef void  (__thiscall* TC_VIIII)(void*, int, int, int, int);
typedef void  (__thiscall* TFnVP)(void*, void*);
typedef void* (__thiscall* TFnP)(void*);
typedef void* (__thiscall* TFnPI)(void*, int);
typedef void* (__thiscall* TFnPII)(void*, int, int);
typedef void  (__thiscall* TC_V)(void*);
typedef void  (__thiscall* TC_VI)(void*, int);
typedef void  (__thiscall* TC_VII)(void*, int, int);
typedef void  (__thiscall* TC_VP)(void*, void*);
typedef void* (__thiscall* TC_P)(void*);
typedef void* (__thiscall* TC_PII)(void*, int, int);
#define VT(o, off) (*(void***)(o))[(off) / 4]
struct wstring {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08

    void __thiscall Assign(const wchar_t* first, const wchar_t* last); // 0x423650
    void __thiscall AllocateSelf(int n);                               // 0x429760
    void __thiscall RangeInit(const wchar_t* str);                     // 0x579a90
    void __thiscall Destroy();                                         // 0x5725a0
};
struct BanVec;
struct BanEntry {
    int     miId;      // +0x00
    wstring mName;     // +0x04
    int     miUnk10;   // +0x10
    wstring mText;     // +0x14
    int     miExtra;   // +0x20

    BanEntry* __thiscall CopyFrom(const BanEntry& src);   // 0x00e03830
};
struct BanVec {
    BanEntry* mpBegin;   // +0x00
    BanEntry* mpEnd;     // +0x04
    BanEntry* mpCap;     // +0x08

    BanEntry* __thiscall EraseLast(BanEntry* pos);                    // 0x00e03c30
    BanEntry* __thiscall Insert(BanEntry* pos, const BanEntry& val);  // 0x00e03ca0
};
struct BanTranslator {
    void*    mpVtbl;     // +0x00
    int      miUnk04;    // +0x04
    char     mbActive;   // +0x08 (BanContent+0x0c)
    char     mbHold;     // +0x09 (BanContent+0x0d)
    short    miPad0A;    // +0x0a
    int      miId;       // +0x0c
    wstring  mText;      // +0x10
    int      miUnk1C;    // +0x1c
    wstring  mExtra;     // +0x20
    int      miUnk2C;    // +0x2c
    BanVec   mList;      // +0x30

    bool __thiscall Format(const wchar_t* key, wchar_t* out);      // 0x00e03b80
};
struct BanContent {
    void*         mpVtbl;    // +0x00
    BanTranslator mTokens;   // +0x04

    void __thiscall Dtor();                     // 0x00e03930
    void __thiscall SetText(int id, const wchar_t* text, const void* extras); // 0x00e03590
    void __thiscall OnDeactivate(int a, int b); // 0x00e03e10
    void __thiscall OnToggle(char on);          // 0x00e03f40
    void __thiscall AddRow(int id, const wchar_t* name, const wchar_t* text); // 0x00e03e50
    void __thiscall Reactivate();               // 0x00e02e80 (external)
};
struct Stopwatch {
    long long mTicks;     // +0x00
    int       miPad08;    // +0x08
    int       miPad0C;    // +0x0c
    int       miPad10;    // +0x10
    float     mfScale;    // +0x14
};
struct CivPauseUI {
    int       miPad00[9];  // +0x00
    int       miState;     // +0x24
    Stopwatch mStop1;      // +0x28
    Stopwatch mStop2;      // +0x40
    int       miHandler;   // +0x58

    void __thiscall Pause();                  // 0x00e033d0
    bool __thiscall OnMessage(int id, int arg); // 0x00e03a90
};
struct UIMessage {
    int miPad00;   // +0x00
    int miPad04;   // +0x04
    int miType;    // +0x08
    int miId;      // +0x0c
    int miSub;     // +0x10
    int miFlag;    // +0x14
};
struct cSPUIGlobalOptions_s00e0_33d0 {
    int   miPad00[3];   // +0x00
    int   miType;       // +0x0c
    int   miId;         // +0x10
    int   miSub;        // +0x14

    void __thiscall Reactivate();                        // 0x00e02e80
    void __thiscall Enable(int on);                      // 0x00e018c0
    bool __thiscall HandleMessage(int arg, UIMessage* msg); // 0x00e039d0
};
struct cSPUILayout_s00e0_33d0;
struct cSPUIGlobalUI_s00e0_33d0 {
    void*            mpVtbl;        // +0x00
    cSPUIGlobalOptions_s00e0_33d0* mpOptions;  // +0x04
    cSPUILayout_s00e0_33d0*     mpLayout;      // +0x08
    BanContent       mBan;          // +0x0c
    int              miPad4C;       // +0x4c
    int              miPad50;       // +0x50
    void*            mpHandler;     // +0x54
    void*            mpHandlerThis; // +0x58
    int              miHandlerTag;  // +0x5c
    int              miHandlerCount;// +0x60
    int              miHandlerExtra;// +0x64

    bool __thiscall Init(int param);                                // 0x00e03620
    bool __thiscall Shutdown();                                     // 0x00e03740
    void* __thiscall Construct();                                   // 0x00e03ab0
    void __thiscall Destroy();                                      // 0x00e03b20
    void* __thiscall FindWindowByID(unsigned id);                   // 0x00e012b0
    void __thiscall ShowOptionWindows(char on);                     // 0x00e042d0
    bool __thiscall HandleMessage(unsigned msg, int arg);           // 0x00e03f80
    bool __thiscall AnyCivSlotUsed();                               // 0x00e042b0
    void* __thiscall AsInterface(unsigned id);                      // 0x00e04270
};
static unsigned char& g_bPaused_s00e0_33d0        = *(unsigned char*)0x016a1890;
static void*&         g_pTranslator_s00e0_33d0    = *(void**)0x0169e3e8;
static const unsigned kGameModeBase    = 0x01654c00;
static const unsigned kUIStrings       = 0x0147f238;
static inline void  GameTime_Dec(unsigned gate) { ((TC_VI)0x00b32250)(FUN_00b3d380(), (int)gate); }
static inline void  GameTime_Inc(unsigned gate) { ((TC_VI)0x00b32220)(FUN_00b3d380(), (int)gate); }
// ---- items of slice s00e033d0 end

// @ 0x00e01750
char Dispatch(void* self, void* win, void* msg)
{
    // Large switch; see nonmatching.txt.
    (void)self; (void)win; (void)msg;
    return 0;
}

// @ 0x00e018c0
void Activate(void* self, char on)
{
    (void)self; (void)on;
}

// @ 0x00e01990
void cSPUIGlobalOptions::Update()
{
    enum SpGameMode : uint32_t { kModeC00 = 0x1654c00, kModeC01 = 0x1654c01, kModeC02 = 0x1654c02, kModeC03 = 0x1654c03, kModeC04 = 0x1654c04, kModeC05 = 0x1654c05, kModeC10 = 0x1654c10, kModeNone = 0xffffffff, kModeGal = 0x2ccd1d2 };
    AssignWindow(&mWin14, mLayout->FindWindowByID(0xffffffffu, 1));
    AssignWindow(&mWin18, mLayout->FindWindowByID(0x615b50du, 1));

    uint32_t mode = (uint32_t)SP_GetCurrentGameMode();
    if (mode == (uint32_t)kModeC00) {
        cVtblObj* a = mLayout->FindWindowByID(0x62025f9u, 1);
        if (a) MakeTooltip(a, 0x678c04a);
        cVtblObj* b = mLayout->FindWindowByID(0x44ea79eu, 1);
        if (b) MakeTooltip(b, 0x678c04b);
    }

    AssignWindow(&mWin1c, mLayout->FindWindowByID(0x64c23f8u, 1));

    mode = (uint32_t)SP_GetCurrentGameMode();
    {
        cVtblObj* attach = 0;
        if (mode == (uint32_t)kModeC00 && mWin1c != 0)       attach = mWin1c;
        else if (mWin14 != 0)                                attach = mWin14;
        if (attach) attach->v104(this);
    }

    cVtblObj* net = mLayout->FindWindowByID(0x10ed852u, 1);
    if (net) {
        if (mode == (uint32_t)kModeC00) net->v104(this);
        void* obj = EA_Allocate(0x34, "UI/NetworkActivityProc", 0, 0, 0, 0);
        if (obj) InitNetworkActivityProc((NetworkActivityProc*)obj);
        net->v104(obj);
        net = (cVtblObj*)net->v00c(0x8ed27e7a);
    }
    AssignWindow(&mWin20, net);
}

// @ 0x00e01ce0
void* GlobalOpts2::FindWin(void* id)
{
    if (p5c->f08 != 0) {
        return ((SPUILayout2*)p5c->f08)->FindWindowByID(id, 1);
    }
    return 0;
}

// @ 0x00e01d00
void ShowTransition(void* self)
{
    (void)self;
}

// @ 0x00e01db0
void cSPUIGlobalUIRootWinProc::OnModalWindowEnd(uint32_t /*wparam*/, uint32_t msg)
{
    enum SpGameMode : uint32_t { kModeC00 = 0x1654c00, kModeC01 = 0x1654c01, kModeC02 = 0x1654c02, kModeC03 = 0x1654c03, kModeC04 = 0x1654c04, kModeC05 = 0x1654c05, kModeC10 = 0x1654c10, kModeNone = 0xffffffff, kModeGal = 0x2ccd1d2 };
    int st = mState;
    if (st == 1) {
        if (msg == 0x5107b17u) return;
        if (msg == 0x5107b1au) goto st9;
        goto common;
    }
    if (st == 2) {
        if (msg == 0x5107b17u) return;
        if (msg == 0x5107b1au) goto st10;
    }
common:
    if (msg == 0x5107b19u) { mState = 0; return; }
    if (msg == 0xfffffff1u) {
        if (st == 5) goto st9;
        if (st != 6) return;
        mState = 10; ShowTransition(this); return;
    }
    if (msg == 0x5107b1au) {
        if (st == 10 || st == 9) goto transition;
        if (st == 3 || st == 7) { mState = 5; goto enter_a; }
        if (st == 4 || st == 8) { mState = 6; goto enter_a; }
        return;
    }
    if (msg != 0x5107b17u) return;
    if (st == 7) goto st9;
    if (st == 8) goto st10;
    if (st == 4 || st == 3) goto callout;
    if (st == 10 || st == 9) goto enter_b;
    return;

st10:
    mState = 10;
    goto transition;
st9:
    mState = 9;
transition:
    ShowTransition(this);
    return;

enter_a: {
    cActiveView* v = (cActiveView*)((cVtblObj*)SP_WindowManager())->v004();
    v->mActive = 1;
    SpaceUniverseTransition();
    mField58 = ((cCurMgr*)FUN_0067cab0())->GetSystem();
    PauseGateOnce();
    mTimer.Restart();
    ((cCurMgr*)FUN_0067cab0())->FindGlobal(0x1003);
    mUI->SetVisibility(0);
    return;
}
enter_b: {
    SpaceUniverseTransition();
    if (mState == 9) mState = 5;
    else if (mState == 10) mState = 6;
    PauseGateOnce();
    mField58 = ((cCurMgr*)FUN_0067cab0())->GetSystem();
    mTimer.Restart();
    ((cCurMgr*)FUN_0067cab0())->FindGlobal(0x1003);
    mUI->SetVisibility(0);
    return;
}
callout:
    FUN_00809db0((void*)0x15a4878, (void*)0x15a4830);
    if (mState == 4) mState = 8;
    else if (mState == 3) mState = 7;
    return;
}

// @ 0x00e02040
void ShowContextSensitiveSporepedia(void* arg)
{
    enum SpGameMode : uint32_t { kModeC00 = 0x1654c00, kModeC01 = 0x1654c01, kModeC02 = 0x1654c02, kModeC03 = 0x1654c03, kModeC04 = 0x1654c04, kModeC05 = 0x1654c05, kModeC10 = 0x1654c10, kModeNone = 0xffffffff, kModeGal = 0x2ccd1d2 };
    if (!FUN_00e01390()) return;

    SpLaunch launch;
    ((cSporeLaunchCtx*)&launch)->Init(arg);

    uint32_t hash = 0u;
    uint32_t mode = (uint32_t)SP_GetCurrentGameMode();
    if ((int)mode < 0x1654c11) {
        if (mode == (uint32_t)kModeC10) {
            GlobalState* gs = g_pGlobalState;
            if (gs == 0) goto finish;
            if (gs->mFieldCC == 1) {
                hash = 0x5e726c14;
                ((cVtblObj*)SP_MessageServer())->v014(0x79816bd, 0, 0);
                goto do_launch;
            }
            if (gs->mFieldCC != 2) goto finish;
            if (gs->mFieldD0 == 2) {
                hash = 0xd95e4abc;
                if (g_pTranslator != 0) {
                    void* planet = SP_GetPlayerHomePlanet();
                    if (planet != 0) {
                        g_pTranslator->SetUserName(((PlanetInfo*)planet)->mName);
                    }
                }
                goto do_launch;
            }
            hash = 0xf6fefa3e;
            goto do_launch;
        }
        switch (mode) {
        case (uint32_t)kModeC00: hash = 0x817d7b6d; break;
        case (uint32_t)kModeC01: hash = 0x710c185a; break;
        case (uint32_t)kModeC02: hash = 0x8799ddcb; break;
        case (uint32_t)kModeC04: hash = 0x5126162d; break;
        case (uint32_t)kModeC05: hash = 0xfeb98c35; break;
        }
        goto lab_9a;
    }
    if (mode == (uint32_t)kModeGal) {
        hash = 0x7accc4a4;
        goto do_launch;
    }

lab_9a:
    if (mode != (uint32_t)kModeNone && mode != (uint32_t)kModeC10 && g_pTranslator != 0) {
        void* name;
        void* planet = SP_GetPlayerHomePlanet();
        if (planet != 0) {
            name = ((PlanetInfo*)planet)->mName;
        } else {
            planet = SP_GetActivePlanet();
            if (planet == 0) goto check;
            name = ((PlanetName*)FUN_00c707e0(planet))->mName;
        }
        g_pTranslator->SetUserName(name);
    }
check:
    if (hash == 0) goto finish;
do_launch:
    launch.mHash = (uint32_t)hash;
    launch.mMode = mode;
    FUN_0064a990(&launch);
finish:
    ((cSporeLaunchCtx*)&launch)->Finish();
}

// @ 0x00e02200
void ShowContextSensitiveSporeGuide(void* /*arg*/)
{
    enum SpGameMode : uint32_t { kModeC00 = 0x1654c00, kModeC01 = 0x1654c01, kModeC02 = 0x1654c02, kModeC03 = 0x1654c03, kModeC04 = 0x1654c04, kModeC05 = 0x1654c05, kModeC10 = 0x1654c10, kModeNone = 0xffffffff, kModeGal = 0x2ccd1d2 };
    cBrowser* browser = (cBrowser*)SP_GetSetting3();
    if (browser->CanSporepediaShowSporeGuide()) {
        bool toBig = false;
        if ((uint32_t)SP_GetCurrentGameMode() == (uint32_t)kModeC04 &&
            ((CivStrategyData*)SP_CivModeStrategyGet())->mField148 != 0) {
            toBig = true;
        }
        if (!toBig &&
            (uint32_t)SP_GetCurrentGameMode() == (uint32_t)kModeC02 &&
            ((cTribeStrategy*)SP_TribeModeStrategyInstance())->TerrainNotHasKey()) {
            toBig = true;
        }
        if (!toBig) {
            if ((uint32_t)SP_GetCurrentGameMode() != (uint32_t)kModeC05) {
                browser->ShowSporeGuide();
                return;
            }
            if (((cSpaceMode*)FUN_010666a0())->Check()) toBig = true;
            else { browser->ShowSporeGuide(); return; }
        }
    }

    if (!FUN_00e014a0()) return;

    uint32_t hash    = 0;
    cVtblObj* keyed  = 0;
    uint32_t mode = (uint32_t)SP_GetCurrentGameMode();
    if ((int)mode < 0x1654c11) {
        if (mode == (uint32_t)kModeC10) { hash = 0xa1167bc4; goto launch; }
        switch (mode) {
        case (uint32_t)kModeC00:
            hash = 0x54a11ee6;
            goto launch;
        case (uint32_t)kModeC01:
            hash = 0xaee816f4;
            goto launch;
        case (uint32_t)kModeC02: {
            void* r = ((cVtblObj*)SP_TribeModeStrategyInstance())->v070();
            if (((cEffectRef*)((EffectSlots*)r)->mField5c)->IsActive()) {
                cVtblObj* pm = (cVtblObj*)SP_PropertyManager();
                void* param = FUN_00a16f40(&keyed);
                pm->v030(0x6b3f727b, param);
                FUN_006a12a0(keyed, 0xd3a9b56, &hash);
                goto launch_check;
            }
            hash = 0x33d018d7;
            goto launch;
        }
        case (uint32_t)kModeC04: {
            void* st = ((cCivStrategy*)SP_CivModeStrategyGet())->GetState();
            if (((cEffectRef*)((EffectSlots*)st)->mField80)->IsActive()) {
                cVtblObj* pm = (cVtblObj*)SP_PropertyManager();
                void* param = FUN_00a16f40(&keyed);
                pm->v030(0x6b3f727b, param);
                FUN_006a12a0(keyed, 0x5ca318f3, &hash);
                goto launch_check;
            }
            hash = 0x18906190;
            goto launch;
        }
        case (uint32_t)kModeC05: {
            void* sg = SP_SpaceGameGet();
            if (((cEffectRef*)((EffectSlots*)sg)->mField20)->IsActive()) {
                cVtblObj* pm = (cVtblObj*)SP_PropertyManager();
                void* param = FUN_00a16f40(&keyed);
                pm->v030(0x6b3f727b, param);
                FUN_006a12a0(keyed, 0x2fd9f52e, &hash);
                goto launch_check;
            }
            hash = 0x45c88342;
            goto launch;
        }
        }
        goto launch_check;
    }
    if (mode == (uint32_t)kModeGal) { hash = 0xa1167bc4; goto launch; }

launch_check:
    if (hash == 0) goto cleanup;
launch:
    FUN_0064aba0((void*)hash);
cleanup:
    if (keyed) keyed->v004();
    return;
}

// @ 0x00e02f00
char UIThing::FUN_00e02f00(int a, void* msg)
{
    (void)a;
    if (*(int*)((char*)msg + 8) != 0xc) {
        if (*(int*)((char*)msg + 8) != 0x287259f6)
            return 0;
        uint32 id = *(uint32*)((char*)msg + 0xc);
        switch (id) {
        case 0x10ed852: {
            void* p = FindWindowByID(0x10ed874);
            if (p == 0)
                return 0;
            FUN_00572020(&g147f0a0, 1);
            FUN_00435ed0(0x5da7b944, &g147f0a0);
            char b = ((VFC)(*(void***)p)[0x28 / 4])(p);
            b = (b ^ 0xff) & 1;
            ((VF2)(*(void***)p)[0x7c / 4])(p, 1, b);
            void* ms = MessageServer();
            if (b != 0)
                ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x64a5044, 0, 0);
            else
                ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x64a504a, 0, 0);
            return 0;
        }
        case 0x10f366d:
            ((Telemetry*)FUN_0067de90(-1))->Flush();
            FUN_00e009f0();
            FUN_00572020(&g147f0a8, 1);
            FUN_00435ed0(0x6d719e97, &g147f0a8);
            switch ((uint32)FUN_00b5b800()) {
            case 0x01654c01:
            case 0x01654c02:
            case 0x01654c04:
            case 0x01654c05:
                if (m5c->m04->m0c == 0)
                    goto LAB_default;
                if (FUN_00e00a40() != 0 && FUN_00e00c40() == 0) {
                    m24 = 3; FUN_00e00bd0();
                    return 0;
                }
                m24 = 1; FUN_00e00bb0();
                return 0;
            case 0x01654c10:
                m24 = 1; FUN_00e00bb0();
                return 0;
            default:
            LAB_default:
                m24 = 9; FUN_00e01d00();
                return 0;
            }
        case 0x10f366e:
            ((Telemetry*)FUN_0067de90(-1))->Flush();
            FUN_00e009f0();
            FUN_00572020(&g147f0a4, 1);
            FUN_00435ed0(0x31c0d295, &g147f0a4);
            if (FUN_00b5b800() == (void*)0x01654c05 && FUN_01021080() == 0) {
                FUN_00dd8640(FUN_00b3d3e0(0x6251278c, 0x131a9f54, 0, 0, 1, 0));
                return 0;
            }
            m5c->m04->m0c = 0;
            {
                void* ms = MessageServer();
                ((VF4)(*(void***)ms)[0x18 / 4])(ms, 0x1cd20f0, 0, 0, 0);
            }
            return 0;
        case 0x2268ba4:
            FUN_00e009f0();
            FUN_00572020(&g147f0a4, 1);
            FUN_00435ed0(0x31c0d295, &g147f0a4);
            if (FUN_00b5b800() != (void*)0x01654c10) {
                if (m5c->m04->m0c == 0) {
                    m24 = 10; FUN_00e01d00();
                    return 0;
                }
                if (FUN_00e00a40() != 0 && FUN_00e00c40() == 0) {
                    m24 = 4; FUN_00e00bd0();
                    return 0;
                }
            }
            m24 = 2; FUN_00e00bb0();
            return 0;
        case 0x43b72d0:
            FUN_00e00bf0();
            return 0;
        case 0x447060a:
            FUN_00572020(&g147f0ac, 1);
            FUN_00435ed0(0x0d6c6c5c, &g147f0ac);
            FUN_00e02900();
            return 0;
        case 0x44827b8:
            if (FUN_00b5b800() == (void*)0x01654c04 &&
                *(char*)((char*)FUN_00cf74c0() + 0x148) != 0)
                return 0;
            if (FUN_00b5b800() == (void*)0x01654c02 &&
                FUN_00cd44a0(FUN_00cd40b0()) != 0)
                return 0;
            if (FUN_00b5b800() == (void*)0x01654c05 &&
                FUN_01065e20(FUN_010666a0()) != 0)
                return 0;
            ((GameTimeManager*)FUN_00b3d380())->IncPauseGate(0x4bf38a4);
            FUN_00e3c6f0(0, 0);
            return 0;
        case 0x44ea79e:
            FUN_00e02950();
            return 1;
        case 0x62025f9:
            FUN_00e02a20();
            return 1;
        case 0x6244208:
            FUN_00e190c0(FUN_00b3d3f0(0));
            return 0;
        case 0x6244660:
            FUN_00e02c40();
            return 0;
        case 0xd305ca84:
            FUN_00572020(&g147f09c, 1);
            FUN_00435ed0(0x6938ce2c, &g147f09c);
            FUN_00e01270();
            return 0;
        default:
            return 0;
        }
    }
    {
        char cVar2 = FUN_00e36fa0(FUN_00b3d410());
        char bVar4;
        if (((((GameTimeManager*)FUN_00b3d380())->m48 >> 1) & 1) != 0 &&
            FUN_00e393b0(FUN_00b3d410()) == 0)
            bVar4 = 1;
        else
            bVar4 = 0;
        if (cVar2 == 0 && bVar4 == 0) {
            FUN_0067c960(FUN_0067cac0());
            FUN_005fdf40(FUN_0067cae0());
        }
    }
    if ((m28 | m2c) != 0 || (m40 | m44) != 0) {
        void* ms = MessageServer();
        ((VF4)(*(void***)ms)[0x18 / 4])(ms, 0x685d440, 0, 0, 0);
    }
    return 0;
}

// @ 0x00e03620
bool cSPUIGlobalUI_s00e0_33d0::Init(int param)
{
    FUN_00dd12f0();
    FUN_00e09600();

    void* ms = FUN_0067dcc0();
    this->mpHandler      = ms;
    this->mpHandlerThis  = this;
    this->miHandlerTag   = (int)0x0147f238;
    this->miHandlerCount = 0xb;
    this->miHandlerExtra = 0;
    if (ms != 0 && this != 0) {
        for (unsigned i = 0; i < 0x2c; i += 4) {
            int tag = *(int*)(kUIStrings + i);
            ((TFnVII)VT(ms, 0x24))(ms, (int)this, tag);
        }
    }

    void* dlg = cof_new(0x18, "Simulator", 0, 0, 0, 0);
    if (dlg != 0)
        dlg = (void*)((TC_P)0x00810000)(dlg);

    void* old = this->mpLayout;
    if (dlg != old) {
        if (dlg != 0)
            ((TFnV)VT(dlg, 4))(dlg);
        this->mpLayout = (cSPUILayout_s00e0_33d0*)dlg;
        if (old != 0)
            ((TFnV)VT(old, 8))(old);
    }

    bool ok = false;
    if (this->mpLayout != 0) {
        if (((TFnPII)VT(this->mpLayout, 0x00))(this->mpLayout, 0, 0)) {
            ((TC_V)0x00e02af0)(this);
            ok = true;
        }
    }

    if (FUN_0067de40() != 0) {
        void* a = FUN_0067de40();
        void* b = ((TFnP)VT(a, 0x20))(a);
        if (b != 0) {
            void* p = (this != 0) ? (void*)((char*)this + 0x10) : 0;
            void* c = FUN_0067de40();
            void* d = ((TFnP)VT(c, 0x20))(c);
            ((TFnVP)VT(d, 0x1c))(d, p);
        }
    }
    return ok;
}

// @ 0x00e03740
bool cSPUIGlobalUI_s00e0_33d0::Shutdown()
{
    if (this->mpLayout != 0) {
        ((TC_VI)0x00811ad0)(this->mpLayout, 1);
        cSPUILayout_s00e0_33d0* p = this->mpLayout;
        if (p != 0) {
            this->mpLayout = 0;
            ((TFnV)VT(p, 8))(p);
        }
    }
    if (this->mpOptions != 0) {
        FUN_00e02e10(this->mpOptions);
        cSPUIGlobalOptions_s00e0_33d0* p = this->mpOptions;
        if (p != 0) {
            this->mpOptions = 0;
            ((TFnV)VT(p, 4))(p);
        }
    }
    FUN_00dd14b0();
    FUN_00e097c0();

    if (this->mpHandler != 0) {
        void* h = this->mpHandler;
        this->mpHandler = 0;
        ((TC_VIIII)0x00571db0)(h, (int)this->mpHandlerThis, this->miHandlerTag,
                               this->miHandlerCount, this->miHandlerExtra);
    }

    FUN_0067cac0();
    ((TC_V)0x0067ca40)(FUN_0067cac0());

    void* a = FUN_0067de40();
    void* b = ((TFnP)VT(a, 0x20))(a);
    ((TFnVI)VT(b, 0x20))(b, (int)g_pTranslator_s00e0_33d0);
    g_pTranslator_s00e0_33d0 = 0;

    if (FUN_0067de40() != 0) {
        void* c = FUN_0067de40();
        void* d = ((TFnP)VT(c, 0x20))(c);
        if (d != 0) {
            void* p = (this != 0) ? (void*)((char*)this + 0x10) : 0;
            void* e = FUN_0067de40();
            void* f = ((TFnP)VT(e, 0x20))(e);
            ((TFnVI)VT(f, 0x20))(f, (int)p);
        }
    }
    return true;
}

// @ 0x00e039d0
bool cSPUIGlobalOptions_s00e0_33d0::HandleMessage(int arg, UIMessage* msg)
{
    (void)arg;
    if (msg->miType == 1) {
        if (msg->miFlag == 0) {
            if (msg->miSub == 0x1b) {
                if (g_bPaused_s00e0_33d0 == 0) {
                    if (FUN_00e09540() == 0 && FUN_00dd1230() == 0) {
                        this->Reactivate();
                        return true;
                    }
                    FUN_00e009f0();
                }
                return true;
            }
            if (msg->miSub == 0x48 || msg->miSub == 0xbf) {
                FUN_00e02200();
                return true;
            }
        }
        if (msg->miFlag == 1 && msg->miSub == 0xbf) {
            FUN_00e02200();
            return true;
        }
    } else if (msg->miType == 0x287259f6) {
        if (msg->miId == 0x10ed852 || msg->miId == 0x595e0a8) {
            this->Reactivate();
            if (FUN_00b5b800() != (void*)kGameModeBase)
                return true;
        }
    }
    return false;
}

// @ 0x00e03a90
bool CivPauseUI::OnMessage(int id, int arg)
{
    (void)arg;
    if (id == 0x685d440)
        ((CivPauseUI*)((char*)this - 4))->Pause();
    return false;
}

// @ 0x00e03f40
void BanContent::OnToggle(char on)
{
    this->mTokens.mbHold = on;
    if (on != 0 && this->mTokens.mbActive == 0) {
        BanEntry* p = this->mTokens.mList.mpBegin;
        if (p != this->mTokens.mList.mpEnd) {
            this->SetText(p->miId, p->mName.mpBegin, p->mText.mpBegin);
            this->mTokens.mList.EraseLast(this->mTokens.mList.mpBegin);
        }
    }
}

// @ 0x00e03f80
bool cSPUIGlobalUI_s00e0_33d0::HandleMessage(unsigned msg, int arg)
{
    if (msg <= 0x05d1536c) {
        if (msg == 0x05d1536c) {
            if (this->mpOptions != 0 && this->mpOptions->miType != 0) {
                void* w = FUN_008105b0(this->mpOptions->miType, 0x44ea79e, 1);
                if (w != 0) {
                    void* b = ((TFnPI)VT(w, 0x0c))(w, (int)0x8ed27e7a);
                    if (b != 0)
                        ((TFnVII)VT(b, 0x28))(b, 4, 0);
                }
                if (FUN_00e00ac0() != 0) {
                    this->mpOptions->Enable(1);
                    return true;
                }
            }
        } else if (msg < 0x05120263) {
            if (msg == 0x05120262) {
                if (FUN_00b5b800() != (void*)0x01654c10) {
                    FUN_00e01620(1, arg);
                    return true;
                }
                if (FUN_00b5b820() == (void*)0x01654c05) {
                    FUN_00e01620(1, arg);
                    return true;
                }
            } else if (msg == 0x03867294) {
                if (this->mpLayout != 0) {
                    void* w = ((TC_PII)0x008105b0)(this->mpLayout, 0xd305ca84, 1);
                    void* b = (void*)((TC_P)0x005ca960)(w);
                    if (b != 0) {
                        char str[8];
                        ((TC_V)0x006b5060)(str);
                        if ((*(unsigned char*)((char*)FUN_00b3d380() + 0x48) & 1) == 0) {
                            ((TFnVII)VT(b, 0x28))(b, 4, 0);
                            ((TC_VII)0x006b54b0)(str, 0xf81c278b, 0);
                        } else {
                            ((TFnVII)VT(b, 0x28))(b, 4, 1);
                            ((TC_VII)0x006b54b0)(str, 0x0655200d, 0);
                        }
                        ((TC_VII)0x006b54b0)(str, 0xc0152a6d, 0);
                        const wchar_t* txt = (const wchar_t*)((TC_P)0x006b55c0)(str);
                        void* w2 = ((TFnPI)VT(b, 0x10))(b, (int)txt);
                        ((TC_VP)0x00806de0)(this, w2);
                        ((TC_V)0x006b5240)(str);
                        return true;
                    }
                }
            } else if (msg == 0x04471c60) {
                GameTime_Dec(0x4bf38a4);
                return true;
            }
        } else if (msg == 0x0539a4ce) {
            if (arg == 0) {
                GameTime_Inc(0x4bf38a6);
                return true;
            }
        } else if (msg == 0x0539a4cf) {
            if (arg == 0) {
                GameTime_Dec(0x4bf38a6);
                return true;
            }
        }
    } else if (msg < 0x07bd0aab) {
        if (msg == 0x07bd0aaa) {
            if (FUN_00685520(2) != 0) {
                this->mBan.AddRow(arg, (const wchar_t*)*(int*)(arg + 4),
                                  (const wchar_t*)*(int*)(arg + 8));
                return true;
            }
        } else if (msg == 0x06202731) {
            if (this->mpOptions != 0 && this->mpOptions->miType != 0) {
                void* w = FUN_008105b0(this->mpOptions->miType, 0x62025f9, 1);
                void* b = (void*)((TC_P)0x005ca960)(w);
                if (b != 0)
                    ((TFnVII)VT(b, 0x28))(b, 4, 0);
                if (FUN_00e00ac0() != 0) {
                    this->mpOptions->Enable(1);
                    return true;
                }
            }
        } else if (msg == 0x064eb18e) {
            if (this->mpOptions != 0) {
                this->mpOptions->Reactivate();
                return true;
            }
        }
    } else if (msg == 0x080d7451) {
        this->mBan.OnToggle(*(int*)arg != 0);
    }
    return true;
}
