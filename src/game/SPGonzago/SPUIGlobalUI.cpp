// src/game/SPGonzago/SPUIGlobalUI.cpp -- migrated from slice(s) s00e00760, s00e033d0, s00e02580, s00e01750 by tools/migrate/rewrite.py
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
struct GlobalState {                     // @ 0x16c7aa4
    uint8_t pad00[0xcc];
    int     mFieldCC;                    // +0xcc
    int     mFieldD0;                    // +0xd0
};
extern "C" GlobalState* g_pGlobalState;  // @ 0x16c7aa4
class cTranslator;                       // cSPEditorShoppingTokenTranslator
extern "C" cTranslator* g_pTranslator;   // @ 0x15ee298
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
struct SPUILayout2;
struct Ctl { char pad[8]; SPUILayout2* f08; };
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

// ---- items of slice s00e02580 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char  g147f09c;        // 0x0147f09c
extern char  g147f0a0;        // 0x0147f0a0
extern char  g147f0a4;        // 0x0147f0a4
extern char  g147f0a8;        // 0x0147f0a8
extern char  g147f0ac;        // 0x0147f0ac
extern char  g15a4ae0;        // 0x015a4ae0
extern void* g169e3e8;        // 0x0169e3e8  gpCreatureTokenTranslator
extern void* g16c7aa4;        // 0x016c7aa4  (pointer to a global object)
extern char  gSimulatorName[];    // 0x013f09b4 "Simulator"
extern char  gRootWinProcName[];  // 0x0147f214 "Simulator/cSPUIGlobalUIRootWinProc"
extern char  gGlobalOptionsName[];// 0x0147f1fc "UI/cSPUIGlobalOptions"
typedef unsigned short wchar16;
typedef unsigned int   uint32;
void*     MessageServer();                             // 0x0067dcc0
void*     FUN_00b3d410();                              // 0x00b3d410
char      FUN_00e00a40();                              // 0x00e00a40
char      FUN_00e00c40();                              // 0x00e00c40
char      FUN_00e00d20();                              // 0x00e00d20
void*     FUN_00b3d380();                              // 0x00b3d380  GameTimeManager
void*     FUN_00b5b800();                              // 0x00b5b800  GetCurrentGameMode
void*     FUN_01021080();                              // 0x01021080  GetUniverseContext
void*     FUN_0080fee0();                              // 0x0080fee0  MultiHeapObject::operator_new
void*     FUN_00f473a0(uint32 n, const char* file, uint32 a, uint32 b, uint32 c, uint32 d);
void      FUN_00f47380(void* p);                       // 0x00f47380  operator delete[]
void      FUN_00e02040(void* a);                       // 0x00e02040  ShowContextSensitiveSporepedia
void*     FUN_0067cac0();                              // 0x0067cac0  (returns cUIHints*)
void*     FUN_0067cae0();                              // 0x0067cae0
void*     FUN_00cf74c0();                              // 0x00cf74c0  cCivModeStrategy::Get
void*     FUN_00cd40b0();                              // 0x00cd40b0  cTribeModeStrategy::Instance
void*     FUN_01002bd0();                              // 0x01002bd0  SpaceGameGet
void      FUN_00e3c6f0(int a, int b);                  // 0x00e3c6f0
void* __stdcall FUN_00b3d3f0(int a);                   // 0x00b3d3f0
void* __stdcall FUN_00b3d3e0(int a, int b, int c, int d, int e, int f); // 0x00b3d3e0 EventLog
void* __stdcall FUN_0067de90(int a);                   // 0x0067de90
void*     FUN_00572020(void* p, int v);                // 0x00572020
void*     FUN_00435ed0(uint32 id, void* p);            // 0x00435ed0  KillSetiEffects
void      FUN_00e009f0();                              // 0x00e009f0  on_ban_content_button
void      FUN_00809c50(void* p, int a, int b);         // 0x00809c50  SPUIHelpers::EndModal
void* __fastcall FUN_00644b10(void* self);             // 0x00644b10  (returns self)
void  __fastcall FUN_00644b60(void* self);             // 0x00644b60  (dtor)
void* __fastcall FUN_00e00ec0(void* self);             // 0x00e00ec0  ctor
void* __fastcall FUN_00d486f0(void* self);             // 0x00d486f0  ctor
void  __fastcall FUN_0067c960(void* self);             // 0x0067c960  cUIHints::Update
void  __fastcall FUN_005fdf40(void* self);             // 0x005fdf40  AchievementNotifier::Update
char  __fastcall FUN_00e36fa0(void* self);             // 0x00e36fa0  (thiscall)
char  __fastcall FUN_00e393b0(void* self);             // 0x00e393b0  (thiscall)
char  __fastcall FUN_00cd44a0(void* self);             // 0x00cd44a0  (thiscall)
char  __fastcall FUN_01065e20(void* self);             // 0x01065e20  (thiscall)
void* __fastcall FUN_00bfc5f0(void* self);             // 0x00bfc5f0  (thiscall)
void  __fastcall FUN_00e190c0(void* self);             // 0x00e190c0  (thiscall)
void  __fastcall FUN_00dd8640(void* self);             // 0x00dd8640  PostFeedbackEvent
struct HintsSink { void Set(void* a); };               // 0x0067ca50
struct WinProc   { void* ctor(void* owner); };         // 0x00e010c0
struct Telemetry { void Flush(); };                    // 0x007ebce0
typedef void   (__thiscall *VF0)(void*);
typedef void   (__thiscall *VF1)(void*, int);
typedef void   (__thiscall *VF2)(void*, int, int);
typedef void   (__thiscall *VF3)(void*, int, int, int);
typedef void   (__thiscall *VF4)(void*, int, int, int, int);
typedef void*  (__thiscall *VFP)(void*);
typedef void*  (__thiscall *VFP2)(void*, int, int);
typedef char   (__thiscall *VFC)(void*);
typedef int    (__thiscall *VFCI)(void*);
struct Layout {                                  // cSPUILayout
    void* FindWindowByID(uint32 id, int b);      // 0x008105b0
    void  Shutdown(int v);                       // 0x00811ad0
};
struct LayoutManager {                           // cSPUILayoutManager
    void  SetAllWorldsVisibility(char v);        // 0x008106a0
    void  Method10660(uint32 id, char v);        // 0x00810660
    void* GetWorldMainWindow(uint32 id);         // 0x00810620
};
struct GameTimeManager {
    void  IncPauseGate(int v);                   // 0x00b32220
    void  DecPauseGate(int v);                   // 0x00b32250
    char  pad_00[0x48];
    uint32 m48;                                  // +0x48
};
struct GlobalOptions {                           // UI::cSPUIGlobalOptions
    char  pad_00[0x14];
    void* m14;                                   // +0x14
    void  CreateDialog();                        // 0x00e02430
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
struct WStr {
    uint32 begin;                                // +0x00
    uint32 end;                                  // +0x04
    uint32 cap;                                  // +0x08
    uint32 pad;                                  // +0x0c
    void   assign(const wchar16* first, const wchar16* last);   // 0x00423650
};
struct Elem24 {
    uint32 m00;                                  // +0x00
    WStr   s1;                                   // +0x04
    WStr   s2;                                   // +0x14
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

// ---- items of slice s00e00760 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl EA_Free(void* p);                       // 0xf47380
extern "C" void* __cdecl FUN_00b3d4d0();                 // 0x00b3d4d0
extern "C" void* __cdecl FUN_01015df0();                 // 0x01015df0 universe context
extern "C" void* __cdecl FUN_00ffbe50();                 // 0x00ffbe50
extern "C" void* __cdecl FUN_00b3d4a0();                 // 0x00b3d4a0
extern "C" void  __cdecl FUN_00b32280();
extern "C" void  __cdecl FUN_00b32250();
extern "C" void  __cdecl FUN_00b32220();
extern "C" void  __cdecl FUN_00e3c6f0();
extern "C" void  __cdecl FUN_006035d0();
extern "C" void  __cdecl FUN_006a17e0();
extern "C" void* __stdcall FUN_0080fee0(uint32_t tag);
extern "C" void* __cdecl FUN_00810620();
extern "C" float __cdecl FUN_00805080();
extern "C" void  __cdecl FUN_006b5770();
extern "C" void  __cdecl FUN_006b5240();
extern "C" void  __cdecl FUN_00571db0(void*, void*, void*, void*, void*);
extern "C" void  __cdecl FUN_0093a560();
extern "C" void  __cdecl FUN_0093a1a0();
extern "C" void  __cdecl FUN_00808230(void* obj, void* p);   // 0x808230 (cdecl, 2 args)
extern "C" double __cdecl cos(double);
extern "C" void* __stdcall FUN_00805070(uint32_t tag);     // 0x00805070 curator lookup
#pragma intrinsic(cos)
typedef void  (__thiscall* VFnV)(void*);
typedef char  (__thiscall* VFnC)(void*);
typedef int   (__thiscall* VFnI)(void*);
typedef void* (__thiscall* VFnP)(void*);
typedef void* (__thiscall* VFnPUI)(void*, uint32_t, int);
typedef void  (__thiscall* VFnVV)(void*, void*);
typedef void  (__thiscall* VFnVFF)(void*, float, float);
#define VSLOT(o, off) (*(void**)((char*)(*(void**)(o)) + (off)))
extern "C" int   __cdecl FUN_01021080_s00e0_0760();                 // 0x01021080 GetUniverseContext
struct TC {
    char  F_00b18e40();                 // 0x00b18e40
    char  F_00a98020();                 // 0x00a98020
    char  F_00ae9390();                 // 0x00ae9390
    int   F_008e7f80();                 // 0x008e7f80
    void* F_00a1ad60();                 // 0x00a1ad60
    char  F_006a25a0(uint32_t key);     // 0x006a25a0 property query
    char  F_00cd44a0();                 // 0x00cd44a0 TerrainNotHasKey
    char  F_01065e20();                 // 0x01065e20
    void* F_00bfc5f0();                 // 0x00bfc5f0
    char  F_00ed9e60(int a);            // 0x00ed9e60
    void* F_00810620();                 // 0x00810620 CurMgr lookup
};
void* g_16c7aa4;
int g_15fd918;
float g_16a18d8;
void* g_15a487c;
void* g_15a4878;
int g_15a4848, g_15a483c;
struct OptObj { void* Ctor(); void Dtor(); void* DelDtor(unsigned int flags); void Reset(); };
struct OptLayout {
    uint8_t pad00[0x14];
    void*   mWin14;      // +0x14
    void*   mWin18;      // +0x18
    void*   mWin1c;      // +0x1c
    void*   mWin20;      // +0x20
};
struct WinObj { void* Ctor(void* arg); void Dtor(); };
struct PodObj { void* Copy(void* o); };
struct NetObj {
    void* Ctor();
    void* DelDtor(unsigned int flags);
    uint32_t GetEventFlags() const;
    void  FUN_00e00db0(float dt);
    char  FUN_00e00e90(uint32_t msg, void* arg);
    uint8_t pad00[0x10];
    float   f10;         // +0x10
    float   f14;         // +0x14
    float   f18;         // +0x18
    float   f1c;         // +0x1c
    float   f20;         // +0x20
    float   f24;         // +0x24
    uint8_t mbActive;    // +0x28
    uint8_t pad29[3];
    void*   p2c;         // +0x2c
    void*   p30;         // +0x30
};
struct SPUILayout {
    void* FindWindowByID(void* id, int a);
    void  SetVisibility(void* v);
    char  IsVisible();
};
struct StopwatchObj {
    void  FUN_0093a560(int units, int start);   // EA::Stopwatch::Stopwatch
    void  FUN_0093a1a0(int units);              // EA::Stopwatch::SetUnits
    uint64_t mnStartTime;                       // +0x00
    uint64_t mnTotalElapsedTime;                // +0x08
    int      mnUnits;                           // +0x10
    float    mfCyclesToUnitsCoefficient;        // +0x14
};
struct RefObj1 { virtual void v0(); virtual void Release(); };                 // Release = vtable+4
struct RefObj2 { virtual void v0(); virtual void v1(); virtual void Release(); }; // Release = vtable+8
struct CStringObj { void FUN_006b5240(); };                                    // cString destructor
struct DirectPropListObj { void FUN_006a17e0(unsigned int key, int value); };   // SetBoolProperty (thiscall)
struct GameTimeMgrObj { void FUN_00b32280(void* arg); };                        // TogglePauseGate (thiscall)
struct GUIRootObj {
    void  resetA();   // 0x0093a2e0 (equiv t3)
    void  resetB();   // 0x0093a2e0 (equiv t3)
};
struct GlobalUI {
    void* pad0;
    void* f04;
    void* f08;
    void* FindWindowByID(void* id);
    char  FUN_12d0(void* id, float f);
    void  SetVisibility(void* v);
    char  IsVisible();
    void  FUN_1250(void* x);
};
struct MsgSrv { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                virtual void v4(); virtual void send(uint32_t, int, int); };
// ---- items of slice s00e00760 end

// @ 0x00e009f0
void on_ban_content_button()
{
    if (FUN_00dd1230()) {
        ((MsgSrv*)SP_MessageServer())->send(0x44eaa93, 0, 0);
    } else if (FUN_00e09540()) {
        ((MsgSrv*)SP_MessageServer())->send(0x620222b, 0, 0);
    }
}

// @ 0x00e00a40
char IsGameModeAllowed()
{
    if (SP_GetCurrentGameMode() == (void*)0x1654c05) {
        if (FUN_01021080_s00e0_0760() != 1 && FUN_01021080_s00e0_0760() != 2) return 0;
    }
    if (SP_GetCurrentGameMode() == (void*)0x1654c02) {
        if (((TC*)FUN_00cd40b0())->F_00cd44a0()) return 0;
    }
    if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
        if (*(int*)((char*)g_16c7aa4 + 0xcc) != 1) return 0;
    }
    return 1;
}

// @ 0x00e00aa0
int MenuKind()
{
    int r = 0x80;
    if (SP_GetCurrentGameMode() != (void*)0x1654c00) {
        r += 1;
    }
    return r;
}

// @ 0x00e00ac0
char FUN_00e00ac0_impl()
{
    void* w = (void*)FUN_00810620();
    if (w != 0) {
        void* r = (void*)(*(void*(__thiscall**)(void*, uint32_t, int))(*(void**)((char*)w + 0xf0)))(w, 0x615b50d, 1);
        if (r != 0) {
            return (*(char(__thiscall**)(void*))(*(void**)((char*)r + 0x28)))(r) & 1;
        }
    }
    return 0;
}

// @ 0x00e00b00
char FUN_00e00b00_impl()
{
    char r = 0;
    void* w = ((TC*)FUN_0080fee0(0x5f1bfc10))->F_00810620();
    if (w != 0) {
        void* a = ((VFnPUI)VSLOT(w, 0xf0))(w, 0x615b50d, 1);
        if (a != 0 && (((VFnC)VSLOT(a, 0x28))(a) & 1)) {
            void* wm = SP_WindowManager();
            void* g = ((VFnP)VSLOT(wm, 0x84))(wm);
            if (g != 0 && ((VFnI)VSLOT(g, 0x1c))(g) == 0x6318e78) {
                return 1;
            }
            void* w2 = ((TC*)FUN_00805070(0x5b598f7))->F_00810620();
            if (w2 != 0) {
                void* a2 = ((VFnPUI)VSLOT(w2, 0xf0))(w2, 0x43c8b98, 0);
                if (a2 != 0 && (((VFnC)VSLOT(a2, 0x28))(a2) & 1)) {
                    return 1;
                }
            }
        }
    }
    return r;
}

// @ 0x00e00bb0
void FUN_00e00bb0_impl()
{ FUN_00809db0(&g_15a4878, &g_15a4848); }

// @ 0x00e00bd0
void FUN_00e00bd0_impl()
{ FUN_00809db0(&g_15a4878, &g_15a483c); }

// @ 0x00e00bf0
void FUN_00e00bf0_impl()
{
    if (FUN_00dd1230()) {
        ((MsgSrv*)SP_MessageServer())->send(0x44eaa93, 0, 0);
    } else if (FUN_00e09540()) {
        ((MsgSrv*)SP_MessageServer())->send(0x620222b, 0, 0);
    }
    FUN_006035d0();
}

// @ 0x00e00c40
char FUN_00e00c40_impl()
{
    char prop = (char)((TC*)(uint32_t)g_15fd918)->F_006a25a0(0xd5797c10);
    bool m = (SP_GetCurrentGameMode() == (void*)0x1654c05);
    bool b0 = m && (((TC*)SP_SpaceGameGet())->F_00b18e40() != 0);
    bool b2 = m && (((TC*)FUN_01015df0())->F_00a98020() != 0);
    bool b1 = m && (((TC*)((char*)((TC*)FUN_00ffbe50())->F_00a1ad60() + 0x508))->F_008e7f80() == 2);
    bool bv = m && (((uint8_t*)FUN_00ffbe50())[0x18] != 0);
    if (b0) return 1;
    if (b1) return 1;
    if (bv) return 1;
    if (b2 && prop == 0) return 1;
    void* g = FUN_00b3d4a0();
    if (g != 0 && ((TC*)g)->F_00ae9390()) return 1;
    return 0;
}

// @ 0x00e00d20
char FUN_00e00d20_impl()
{
    if (SP_GetCurrentGameMode() == (void*)0x1654c00) {
        return 0;
    }
    if (FUN_00e00c40_impl()) {
        return 0;
    }
    if (((TC*)(uint32_t)g_15fd918)->F_006a25a0(0xd5797c10)) {
        return 1;
    }
    if (SP_GetCurrentGameMode() != (void*)0x1654c05) {
        return 1;
    }
    if (((TC*)FUN_01015df0())->F_00a98020()) {
        return 0;
    }
    return 1;
}

// @ 0x00e00d90
uint32_t NetObj::GetEventFlags() const
{
    return (mbActive ? 2 : 0) | 0x410;
}

// @ 0x00e00db0
void NetObj::FUN_00e00db0(float dt)
{
    float t = FUN_00805080();
    if (dt > 0.0f) {
        if (mbActive == 0) {
            f20 = t;
            f24 = t + dt;
            mbActive = 1;
            ((VFnVV)VSLOT(p2c, 0x104))(p2c, this);
        } else {
            f24 = f20 + dt;
        }
    }
    float delta = t - f20;
    f20 = t;
    f1c = f1c - g_16a18d8 * delta * 0.5f;
    FUN_00808230(p30, &f10);
    if (f20 > f24) {
        if (cos(f1c) > 0.98f) {
            mbActive = 0;
            ((VFnVV)VSLOT(p2c, 0x104))(p2c, this);
        }
    }
}

// @ 0x00e00e90
char NetObj::FUN_00e00e90(uint32_t msg, void* arg)
{
    if (msg == 0x656435b) {
        ((NetObj*)((char*)this - 0xc))->FUN_00e00db0(*(float*)((char*)arg + 8));
        return 1;
    }
    return 0;
}

// @ 0x00e00ec0
void* OptObj::Ctor()
{
    void* self = this;
    *(void**)((char*)self + 4) = (void*)0x13ec458;
    *(void**)((char*)self + 8) = 0;
    *(void**)self = (void*)0x147f17c;
    *(void**)((char*)self + 4) = (void*)0x147f16c;
    *(void**)((char*)self + 0x10) = 0;
    *(void**)((char*)self + 0x14) = 0;
    *(void**)((char*)self + 0x18) = 0;
    *(void**)((char*)self + 0x1c) = 0;
    *(void**)((char*)self + 0x20) = 0;
    *(void**)((char*)self + 0x24) = 0;
    FUN_006b5770();
    *(void**)((char*)self + 0x3c) = 0;
    FUN_006b5770();
    *(void**)((char*)self + 0x54) = 0;
    return self;
}

// @ 0x00e00f40
void OptObj::Dtor()
{
    void* self = this;
    *(void**)self = (void*)0x147f17c;
    *(void**)((char*)self + 4) = (void*)0x147f16c;
    void* p54 = *(void**)((char*)self + 0x54);
    if (p54 != 0) ((RefObj1*)p54)->Release();
    ((CStringObj*)((char*)self + 0x40))->FUN_006b5240();
    void* p3c = *(void**)((char*)self + 0x3c);
    if (p3c != 0) ((RefObj1*)p3c)->Release();
    ((CStringObj*)((char*)self + 0x28))->FUN_006b5240();
    void* p24 = *(void**)((char*)self + 0x24);
    if (p24 != 0) ((RefObj1*)p24)->Release();
    void* p20 = *(void**)((char*)self + 0x20);
    if (p20 != 0) ((RefObj1*)p20)->Release();
    void* p1c = *(void**)((char*)self + 0x1c);
    if (p1c != 0) ((RefObj1*)p1c)->Release();
    void* p18 = *(void**)((char*)self + 0x18);
    if (p18 != 0) ((RefObj1*)p18)->Release();
    void* p14 = *(void**)((char*)self + 0x14);
    if (p14 != 0) ((RefObj1*)p14)->Release();
    void* p10 = *(void**)((char*)self + 0x10);
    if (p10 != 0) ((RefObj2*)p10)->Release();
    *(void**)self = (void*)0x13eb938;
    *(void**)((char*)self + 4) = (void*)0x13ec458;
}

// @ 0x00e00fe0
void OptObj::Reset()
{
    void* mode = SP_GetCurrentGameMode();
    OptLayout* lay = (OptLayout*)this;
    if (lay->mWin1c != 0) {
        if (mode == (void*)0x1654c00) {
            ((VFnVV)VSLOT(lay->mWin1c, 0x108))(lay->mWin1c, this);
        }
        if (lay->mWin1c != 0) {
            void* p = lay->mWin1c;
            lay->mWin1c = 0;
            ((VFnV)VSLOT(p, 4))(p);
        }
    }
    if (lay->mWin20 != 0) {
        if (mode == (void*)0x1654c00) {
            void* r = ((VFnP)VSLOT(lay->mWin20, 0x10))(lay->mWin20);
            ((VFnVV)VSLOT(r, 0x108))(r, this);
        }
        if (lay->mWin20 != 0) {
            void* p = lay->mWin20;
            lay->mWin20 = 0;
            ((VFnV)VSLOT(p, 4))(p);
        }
    }
    if (lay->mWin14 != 0) {
        if (mode != (void*)0x1654c00) {
            ((VFnVV)VSLOT(lay->mWin14, 0x108))(lay->mWin14, this);
        }
        if (lay->mWin14 != 0) {
            void* p = lay->mWin14;
            lay->mWin14 = 0;
            ((VFnV)VSLOT(p, 4))(p);
        }
    }
}

// @ 0x00e01090
void* OptObj::DelDtor(unsigned int flags)
{
    void* self = this;
    *(void**)self = (void*)0x147f198;
    *(void**)((char*)self + 4) = 0;
    if (flags & 1) {
        EA_Free(self);
    }
    return self;
}

// @ 0x00e010c0
void* WinObj::Ctor(void* arg)
{
    void* self = this;
    *(void**)((char*)self + 4) = (void*)0x13eb384;
    *(void**)((char*)self + 8) = (void*)0x13ec458;
    *(void**)((char*)self + 0xc) = 0;
    *(void**)self = (void*)0x147f1c8;
    *(void**)((char*)self + 4) = (void*)0x147f1b8;
    *(void**)((char*)self + 8) = (void*)0x147f1a8;
    *(void**)((char*)self + 0x10) = 0;
    *(void**)((char*)self + 0x14) = 0;
    *(void**)((char*)self + 0x18) = 0;
    *(void**)((char*)self + 0x1c) = 0;
    *(void**)((char*)self + 0x20) = 0;
    *(void**)((char*)self + 0x24) = 0;
    ((StopwatchObj*)((char*)self + 0x28))->FUN_0093a560(0, 0);
    ((StopwatchObj*)((char*)self + 0x40))->FUN_0093a560(0, 0);
    *(void**)((char*)self + 0x58) = 0;
    *(void**)((char*)self + 0x5c) = arg;
    g_15a487c = self;
    ((StopwatchObj*)((char*)self + 0x28))->FUN_0093a1a0(4);
    ((StopwatchObj*)((char*)self + 0x40))->FUN_0093a1a0(4);
    void* ms = SP_MessageServer();
    *(void**)((char*)self + 0x10) = ms;
    *(void**)((char*)self + 0x14) = (char*)self + 4;
    *(void**)((char*)self + 0x18) = (void*)0x147f1a4;
    *(void**)((char*)self + 0x1c) = (void*)1;
    *(void**)((char*)self + 0x20) = 0;
    if (ms != 0) {
        (*(void(__thiscall**)(void*, void*, uint32_t))(*(void**)((char*)ms + 0x24)))(ms, (char*)self + 4, 0x685d440);
    }
    return self;
}

// @ 0x00e011a0
void WinObj::Dtor()
{
    void* self = this;
    *(void**)self = (void*)0x147f1c8;
    *(void**)((char*)self + 4) = (void*)0x147f1b8;
    *(void**)((char*)self + 8) = (void*)0x147f1a8;
    void* h = *(void**)((char*)self + 0x10);
    if (h != 0) {
        void* a1 = *(void**)((char*)self + 0x14);
        void* a2 = *(void**)((char*)self + 0x18);
        void* a3 = *(void**)((char*)self + 0x1c);
        void* a4 = *(void**)((char*)self + 0x20);
        *(void**)((char*)self + 0x10) = 0;
        FUN_00571db0(h, a1, a2, a3, a4);
    }
    g_15a487c = 0;
    // The compiler could not prove the callee leaves +0x10 zeroed, so the original has a
    // second identical teardown block; keep it so a callee that writes +0x10 behaves alike.
    h = *(void**)((char*)self + 0x10);
    if (h != 0) {
        void* a1 = *(void**)((char*)self + 0x14);
        void* a2 = *(void**)((char*)self + 0x18);
        void* a3 = *(void**)((char*)self + 0x1c);
        void* a4 = *(void**)((char*)self + 0x20);
        *(void**)((char*)self + 0x10) = 0;
        FUN_00571db0(h, a1, a2, a3, a4);
    }
    *(void**)((char*)self + 8) = (void*)0x13ec458;
    *(void**)((char*)self + 4) = (void*)0x13eb394;
    *(void**)self = (void*)0x13eb938;
}

// @ 0x00e01250
void GlobalUI::FUN_1250(void* x)
{
    GUIRootObj* p = (GUIRootObj*)f04;
    if (p != 0) {
        p->resetA();
        p->resetB();
    }
    (void)x;
}

// @ 0x00e01270
void FUN_00e01270_impl()
{
    void* g = SP_GameTimeManager();
    uint8_t b = *(uint8_t*)((char*)g + 0x48);
    int v = (~(int)b) & 1;                       // `not al; and al,1`
    void* propList = (void*)(uint32_t)g_15fd918;
    ((DirectPropListObj*)propList)->FUN_006a17e0(0x387d0a8u, v);
    g = SP_GameTimeManager();
    ((GameTimeMgrObj*)g)->FUN_00b32280((void*)0x4bf38a8);
}

// @ 0x00e012b0
void* GlobalUI::FindWindowByID(void* id)
{
    SPUILayout* p = (SPUILayout*)f08;
    if (p != 0) {
        return p->FindWindowByID(id, 1);
    }
    return 0;
}

// @ 0x00e012d0
char GlobalUI::FUN_12d0(void* id, float f)
{
    SPUILayout* layout = (SPUILayout*)f08;
    if (layout == 0) return 0;
    void* w = layout->FindWindowByID(id, 1);
    if (w == 0) return 0;
    void* c = ((VFnPUI)VSLOT(w, 0xf0))(w, 0x665fe90, 0);
    if (c == 0) return 0;
    float* r = (float*)((VFnP)VSLOT(c, 0x38))(c);
    float h = r[3] - r[1];
    float wd = (r[2] - r[0]) * f;
    ((VFnVFF)VSLOT(w, 0x74))(w, wd, h);
    return 1;
}

// @ 0x00e01350
void GlobalUI::SetVisibility(void* v)
{
    SPUILayout* p = (SPUILayout*)f08;
    if (p != 0) {
        p->SetVisibility(v);
    }
    void* p2 = f04;
    if (p2 != 0) {
        SPUILayout* p3 = *(SPUILayout**)((char*)p2 + 0x10);
        if (p3 != 0) {
            p3->SetVisibility(v);
        }
    }
}

// @ 0x00e01380
char GlobalUI::IsVisible()
{
    SPUILayout* p = (SPUILayout*)f08;
    if (p != 0) {
        return p->IsVisible();
    }
    return 0;
}

// @ 0x00e01390
char FUN_00e01390_impl()
{
    if (FUN_00b3d4d0() != 0) {
        int v = *(int*)((char*)FUN_00b3d4d0() + 0x2c);
        if (v == 1 || v == 2) return 0;
    }
    void* wm = SP_WindowManager();
    if (((VFnP)VSLOT(wm, 0x84))(wm) != 0) return 0;
    if (FUN_00e00c40_impl()) return 0;
    if (SP_GetCurrentGameMode() == (void*)0x1654c04) {
        if (((uint8_t*)FUN_00cf74c0())[0x148] != 0) return 0;
    }
    if (SP_GetCurrentGameMode() == (void*)0x1654c02) {
        if (((TC*)FUN_00cd40b0())->F_00cd44a0()) return 0;
    }
    if (SP_GetCurrentGameMode() == (void*)0x1654c05) {
        if (((TC*)FUN_010666a0())->F_01065e20()) return 0;
    }
    if (SP_GetCurrentGameMode() == (void*)0x1654c05) {
        if (((uint8_t*)((TC*)SP_SpaceGameGet())->F_00bfc5f0())[0xa0] != 0) return 0;
    }
    if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
        if (*(int*)((char*)g_16c7aa4 + 0xcc) == 2) {
            int v = *(int*)((char*)*(void**)((char*)g_16c7aa4 + 0x78) + 0x90);
            if (v == 6 || v == 5) return 0;
        }
    }
    if (*(int*)((char*)g_16c7aa4 + 0xcc) != 1) return 1;
    char r = ((TC*)*(void**)((char*)g_16c7aa4 + 0x10))->F_00ed9e60(1);
    if (r) return 1;
    return 0;
}

// @ 0x00e014a0
char FUN_00e014a0_impl()
{
    char bl;
    if (FUN_00e01390_impl()) {
        bl = 1;
    } else {
        bl = 0;
        void* w = ((TC*)FUN_0080fee0(0x5f1bfc10))->F_00810620();
        if (w != 0) {
            void* a = ((VFnPUI)VSLOT(w, 0xf0))(w, 0x615b50d, 1);
            if (a != 0) {
                if (((VFnC)VSLOT(a, 0x28))(a) & 1) bl = 1;
            }
        }
    }
    if (SP_GetCurrentGameMode() == (void*)0x1654c04) {
        if (((uint8_t*)FUN_00cf74c0())[0x148] != 0) return 0;
    }
    if (SP_GetCurrentGameMode() == (void*)0x1654c02) {
        if (((TC*)FUN_00cd40b0())->F_00cd44a0()) return 0;
    }
    if (SP_GetCurrentGameMode() == (void*)0x1654c05) {
        if (((TC*)FUN_010666a0())->F_01065e20()) return 0;
    }
    if (SP_GetCurrentGameMode() == (void*)0x1654c05) {
        if (((uint8_t*)((TC*)SP_SpaceGameGet())->F_00bfc5f0())[0xa0] != 0) return 0;
    }
    return bl;
}

// @ 0x00e01570
void* PodObj::Copy(void* o)
{
    void* s = this;
    *(uint32_t*)s = *(uint32_t*)o;
    *((uint32_t*)s + 1) = *((uint32_t*)o + 1);
    *((uint32_t*)s + 2) = *((uint32_t*)o + 2);
    *((uint32_t*)s + 3) = *((uint32_t*)o + 3);
    *((uint8_t*)s + 0x10) = *((uint8_t*)o + 0x10);
    *((uint8_t*)s + 0x11) = *((uint8_t*)o + 0x11);
    *((uint8_t*)s + 0x12) = *((uint8_t*)o + 0x12);
    *((uint8_t*)s + 0x13) = *((uint8_t*)o + 0x13);
    *((uint8_t*)s + 0x14) = *((uint8_t*)o + 0x14);
    *((uint32_t*)s + 6) = *((uint32_t*)o + 6);
    *((uint32_t*)s + 7) = *((uint32_t*)o + 7);
    *((uint32_t*)s + 8) = *((uint32_t*)o + 8);
    *((uint8_t*)s + 0x24) = *((uint8_t*)o + 0x24);
    *((uint32_t*)s + 10) = *((uint32_t*)o + 10);
    *((uint8_t*)s + 0x2c) = *((uint8_t*)o + 0x2c);
    *((uint32_t*)s + 0xc) = *((uint32_t*)o + 0xc);
    *((uint32_t*)s + 0xd) = *((uint32_t*)o + 0xd);
    *((uint32_t*)s + 0xe) = *((uint32_t*)o + 0xe);
    *((uint32_t*)s + 0xf) = *((uint32_t*)o + 0xf);
    *((uint32_t*)s + 0x10) = *((uint32_t*)o + 0x10);
    uint32_t r = *((uint32_t*)o + 0x10);
    if (r != 0) {
        (*(void(__thiscall**)(uint32_t))(*(uint32_t*)r + 4))(r);
    }
    *((uint32_t*)s + 0x11) = *((uint32_t*)o + 0x11);
    uint32_t r2 = *((uint32_t*)o + 0x11);
    if (r2 != 0) {
        (*(void(__thiscall**)(uint32_t))(*(uint32_t*)r2 + 4))(r2);
    }
    return s;
}

// @ 0x00e01620
void FUN_00e01620_impl(uint8_t pause)
{
    if (pause) {
        FUN_00b32220();
        FUN_00e3c6f0();
    } else {
        FUN_00b32250();
    }
}

// @ 0x00e01690
void* NetObj::Ctor()
{
    void* self = this;
    *(void**)((char*)self + 4) = (void*)0x13ec458;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = (void*)0x13eb384;
    *(void**)self = (void*)0x147f0dc;
    *(void**)((char*)self + 4) = (void*)0x147f0cc;
    *(void**)((char*)self + 0xc) = (void*)0x147f0bc;
    *(float*)((char*)self + 0x10) = 0.0f;
    *(float*)((char*)self + 0x14) = 0.0f;
    *(float*)((char*)self + 0x18) = 1.0f;
    *(float*)((char*)self + 0x1c) = 0.0f;
    *(float*)((char*)self + 0x20) = 0.0f;
    *(float*)((char*)self + 0x24) = 0.0f;
    *(uint8_t*)((char*)self + 0x28) = 0;
    *(void**)((char*)self + 0x2c) = 0;
    *(void**)((char*)self + 0x30) = 0;
    return self;
}

// @ 0x00e016f0
void* NetObj::DelDtor(unsigned int flags)
{
    void* self = this;
    *(void**)self = (void*)0x147f0dc;
    *(void**)((char*)self + 4) = (void*)0x147f0cc;
    *(void**)((char*)self + 0xc) = (void*)0x147f0bc;
    *(void**)((char*)self + 0xc) = (void*)0x13eb394;
    *(void**)((char*)self + 4) = (void*)0x13ec458;
    *(void**)self = (void*)0x13eb938;
    if (flags & 1) {
        EA_Free(self);
    }
    return self;
}

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
    SPUILayout2* pLayout = p5c->f08;
    return pLayout ? pLayout->FindWindowByID(id, 1) : 0;
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

// @ 0x00e02430
void CreateOptionsDialog(void* self)
{ (void)self; }

// @ 0x00e02580
void UIThing::FUN_00e02580(unsigned char enable)
{
    if (FUN_00dd1230() != 0) {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x44eaa93, 0, 0);
    } else {
        if (FUN_00e09540() != 0) {
            void* ms = MessageServer();
            ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x620222b, 0, 0);
        }
    }
    if (m18 != 0)
        ((VF2)(*(void***)m18)[0x7c / 4])(m18, 1, enable);
    if (FUN_00b5b800() != (void*)0x01654c00) {
        GameTimeManager* gm = (GameTimeManager*)FUN_00b3d380();
        if (enable == 0)
            gm->DecPauseGate(0x4bf38a4);
        else
            gm->IncPauseGate(0x4bf38a4);
    }
    LayoutManager* lm = (LayoutManager*)FUN_0080fee0();
    if (enable != 0)
        lm->SetAllWorldsVisibility(0);
    lm->Method10660(0x5b598f7, enable);
    lm->Method10660(0x5b598f6, enable);
    lm->Method10660(0x5b598f9, enable);
    lm->Method10660(0x5f1bfc10, enable);
    if (enable == 0)
        lm->SetAllWorldsVisibility(1);
    Enable(enable);
    if (m20 != 0)
        ((VF2)(*(void***)m20)[0x28 / 4])(m20, 4, enable);
    if (enable == 0) {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x64a504a, 0, 0);
        ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x695d2f5, 0, 0);
        return;
    }
    m0c = 1;
    char cFlag = FUN_00e00a40();
    void* w1 = ((Layout*)m10)->FindWindowByID(0x10f366e, 1);
    void* w2 = ((Layout*)m10)->FindWindowByID(0x44ea79e, 1);
    void* w3 = ((Layout*)m10)->FindWindowByID(0x62025f9, 1);
    void* w4 = ((Layout*)m10)->FindWindowByID(0x447060a, 1);
    if (FUN_00b5b800() == (void*)0x01654c05)
        FUN_01002bd0();
    char cVar3 = FUN_00e00c40();
    char bVar1;
    if (FUN_00b5b800() == (void*)0x01654c04 &&
        *(char*)((char*)FUN_00cf74c0() + 0x148) == 1)
        bVar1 = 1;
    else if (FUN_00b5b800() == (void*)0x01654c02 && FUN_00cd44a0(FUN_00cd40b0()) == 1)
        bVar1 = 1;
    else if (FUN_00b5b800() == (void*)0x01654c05 &&
             FUN_01065e20(FUN_010666a0()) == 1)
        bVar1 = 1;
    else if (FUN_00b5b800() == (void*)0x01654c05 &&
             *(char*)((char*)FUN_00bfc5f0(FUN_01002bd0()) + 0xa0) != 0)
        bVar1 = 1;
    else
        bVar1 = 0;
    char cVar2;
    if (cFlag != 0 && cVar3 == 0)
        cVar2 = 1;
    else
        cVar2 = 0;
    if (w4 != 0)
        ((VF2)(*(void***)w4)[0x7c / 4])(w4, 2, !bVar1);
    if (w2 != 0) {
        uint32 v;
        if (cVar3 != 0 || FUN_00b5b800() == (void*)0x01654c00)
            v = 0;
        else
            v = 1;
        ((VF2)(*(void***)w2)[0x7c / 4])(w2, 2, v);
    }
    if (w3 != 0) {
        uint32 v;
        if (bVar1 != 0)
            v = 0;
        else if (FUN_00e00d20() != 0)
            v = 1;
        else
            v = 0;
        ((VF2)(*(void***)w3)[0x7c / 4])(w3, 2, v);
    }
    if (w1 == 0)
        goto LAB_msg_show;
    ((VF2)(*(void***)w1)[0x7c / 4])(w1, 2, cVar2);
    if (cVar2 == 0) {
        if (FUN_00b5b800() == (void*)0x01654c10) {
            void* g = g16c7aa4;
            if (*(int*)((char*)g + 0xcc) != 2 || *(int*)((char*)g + 0xd0) != 2)
                goto LAB_msg_show;
            ((VF1)(*(void***)w1)[0x104 / 4])(w1, (int)m3c);
        } else if (FUN_00b5b800() != (void*)0x01654c05) {
            ((VF1)(*(void***)w1)[0x104 / 4])(w1, (int)m54);
        } else {
            ((VF1)(*(void***)w1)[0x104 / 4])(w1, (int)m3c);
        }
    } else {
        ((VF1)(*(void***)w1)[0x108 / 4])(w1, (int)m3c);
        ((VF1)(*(void***)w1)[0x108 / 4])(w1, (int)m54);
    }
LAB_msg_show:
    {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x64a5044, 0, 0);
        ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x695d2ed, 0, 0);
    }
}

// @ 0x00e02900
void UIThing::FUN_00e02900()
{
    if (FUN_00dd1230() != 0) {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x44eaa93, 0, 0);
        return FUN_00e02200();
    }
    if (FUN_00e09540() != 0) {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x620222b, 0, 0);
    }
    return FUN_00e02200();
}

// @ 0x00e02950
void UIThing::FUN_00e02950()
{
    char cVar2 = FUN_00dd1230();
    if (FUN_00dd1230() != 0) {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x44eaa93, 0, 0);
    } else {
        if (FUN_00e09540() != 0) {
            void* ms = MessageServer();
            ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x620222b, 0, 0);
        }
    }
    if (cVar2 != 0)
        return;
    {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x44eaa93, 0, 0);
    }
    if (m5c == 0)
        return;
    ObjB* obj = m5c->m04;
    if (obj == 0)
        return;
    if (obj->m1c != 0)
        ((VF2)(*(void***)obj->m1c)[0x7c / 4])(obj->m1c, 1, 0);
    if (FUN_00b5b800() != (void*)0x01654c00)
        FUN_00809c50((void*)obj->m14, 0, 0);
    if (obj->m24 != 0) {
        ((VF1)(*(void***)obj->m24)[0xc / 4])(obj->m24, 0);
        void* p = obj->m24;
        if (p != 0) {
            obj->m24 = 0;
            return ((VF0)(*(void***)p)[4 / 4])(p);
        }
    }
}

// @ 0x00e02a20
void UIThing::FUN_00e02a20()
{
    char cVar2 = FUN_00e09540();
    if (FUN_00dd1230() != 0) {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x44eaa93, 0, 0);
    } else {
        if (FUN_00e09540() != 0) {
            void* ms = MessageServer();
            ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x620222b, 0, 0);
        }
    }
    if (cVar2 != 0)
        return;
    {
        void* ms = MessageServer();
        ((VF3)(*(void***)ms)[0x14 / 4])(ms, 0x620222b, 0, 0);
    }
    if (m5c == 0)
        return;
    ObjB* obj = m5c->m04;
    if (obj == 0)
        return;
    if (obj->m1c != 0)
        ((VF2)(*(void***)obj->m1c)[0x7c / 4])(obj->m1c, 1, 0);
    if (FUN_00b5b800() != (void*)0x01654c00)
        FUN_00809c50((void*)obj->m14, 0, 0);
    if (obj->m24 != 0) {
        ((VF1)(*(void***)obj->m24)[0xc / 4])(obj->m24, 0);
        void* p = obj->m24;
        if (p != 0) {
            obj->m24 = 0;
            return ((VF0)(*(void***)p)[4 / 4])(p);
        }
    }
}

// @ 0x00e02af0
char UIThing::FUN_00e02af0()
{
    GlobalOptions* piVar4 = 0;
    ObjB* piVar2 = 0;
    if (m08 != 0) {
        piVar2 = (ObjB*)((Layout*)m08)->FindWindowByID(0xffffffff, 1);
        if (piVar2 != 0) {
            void* pv = FUN_00f473a0(0x60, gRootWinProcName, 0, 0, 0, 0);
            void* obj = 0;
            if (pv != 0)
                obj = ((WinProc*)pv)->ctor(this);
            ((VF1)(*(void***)piVar2)[0x104 / 4])(piVar2, (int)obj);
            if (m08 != 0) {
                if (((Layout*)m08)->FindWindowByID(0x10ed874, 1) != 0)
                    goto LAB_end;
            }
            void* g = FUN_00f473a0(0x58, gGlobalOptionsName, 0, 0, 0, 0);
            if (g != 0)
                piVar4 = (GlobalOptions*)FUN_00e00ec0(g);
            GlobalOptions* piVar1 = (GlobalOptions*)m04;
            if (piVar4 != piVar1) {
                if (piVar4 != 0)
                    ((VF0)(*(void***)piVar4)[0])(piVar4);
                m04 = piVar4;
                if (piVar1 != 0)
                    ((VF0)(*(void***)piVar1)[1])(piVar1);
            }
            ((GlobalOptions*)m04)->CreateDialog();
            void* q = ((GlobalOptions*)m04)->m14;
            if (q != 0)
                ((VF1)(*(void***)q)[0x104 / 4])(q, (int)obj);
        }
    }
LAB_end:
    ((HintsSink*)FUN_0067cac0())->Set(&g15a4ae0);
    {
        void* r = FUN_00f473a0(0x30, gSimulatorName, 0, 0, 0, 0);
        void* gp;
        if (r == 0)
            gp = 0;
        else
            gp = FUN_00d486f0(r);
        g169e3e8 = gp;
        void* q2 = FUN_0067de40();
        void* q3 = ((VFP)(*(void***)q2)[0x20 / 4])(q2);
        ((VF1)(*(void***)q3)[0x1c / 4])(q3, (int)gp);
    }
    return piVar2 != 0;
}

// @ 0x00e02c40
void FUN_00e02c40()
{
    char buf[0x48];
    void* r = FUN_00644b10(buf);
    FUN_00e02040(r);
    FUN_00644b60(buf);
}

// @ 0x00e02c60
void __stdcall FUN_00e02c60(Elem24* begin, Elem24* end)
{
    for (; begin < end; begin += 1) {
        if (((int)((begin->s2.cap - begin->s2.begin) & 0xfffffffeu) > 2) &&
            begin->s2.begin != 0)
            FUN_00f47380((void*)begin->s2.begin);
        if (((int)((begin->s1.cap - begin->s1.begin) & 0xfffffffeu) > 2) &&
            begin->s1.begin != 0)
            FUN_00f47380((void*)begin->s1.begin);
    }
}

// @ 0x00e02cc0
Elem24* FUN_00e02cc0(Elem24* begin, Elem24* end, Elem24* dst)
{
    if (begin != end) {
        do {
            if (((int)((begin->s2.cap - begin->s2.begin) & 0xfffffffeu) > 2) &&
                begin->s2.begin != 0)
                FUN_00f47380((void*)begin->s2.begin);
            if (((int)((begin->s1.cap - begin->s1.begin) & 0xfffffffeu) > 2) &&
                begin->s1.begin != 0)
                FUN_00f47380((void*)begin->s1.begin);
            begin += 1;
            dst += 1;
        } while (begin != end);
    }
    return dst;
}

// @ 0x00e02d30
Elem24* FUN_00e02d30(Elem24* src, Elem24* srcEnd, Elem24* dst)
{
    if (src != srcEnd) {
        do {
            dst->m00 = src->m00;
            WStr* ss1 = &src->s1;
            WStr* ss2 = &src->s2;
            WStr* ds1 = &dst->s1;
            WStr* ds2 = &dst->s2;
            if (ss1 != ds1)
                ds1->assign((const wchar16*)ss1->begin, (const wchar16*)ss1->end);
            if (ss2 != ds2)
                ds2->assign((const wchar16*)ss2->begin, (const wchar16*)ss2->end);
            dst += 1;
            src += 1;
        } while (src != srcEnd);
    }
    return dst;
}

// @ 0x00e02da0
Elem24* FUN_00e02da0(Elem24* first, Elem24* last, Elem24* dstEnd)
{
    if (last != first) {
        do {
            last -= 1;
            dstEnd -= 1;
            dstEnd->m00 = last->m00;
            if (&last->s1 != &dstEnd->s1)
                dstEnd->s1.assign((const wchar16*)last->s1.begin, (const wchar16*)last->s1.end);
            if (&last->s2 != &dstEnd->s2)
                dstEnd->s2.assign((const wchar16*)last->s2.begin, (const wchar16*)last->s2.end);
        } while (last != first);
    }
    return dstEnd;
}

// @ 0x00e02e10
void UIThing::FUN_00e02e10()
{
    char c = 0;
    void* w = ((LayoutManager*)FUN_0080fee0())->GetWorldMainWindow(0x5f1bfc10);
    if (w != 0) {
        void* x = ((VFP2)(*(void***)w)[0xf0 / 4])(w, 0x615b50d, 1);
        if (x != 0) {
            c = ((VFC)(*(void***)x)[0x28 / 4])(x);
            if ((c & 1) != 0)
                FUN_00e02580(0);
        }
    }
    if (m10 != 0) {
        ((Layout*)m10)->Shutdown(1);
        if (m10 != 0) {
            void* p = m10;
            m10 = 0;
            ((VF0)(*(void***)p)[8 / 4])(p);
        }
    }
}

// @ 0x00e02e80
void UIThing::FUN_00e02e80()
{
    if (m18 == 0)
        return;
    FUN_00572020(&g147f0a0, 1);
    FUN_00435ed0(0x5da7b944, &g147f0a0);
    unsigned char bl = 0;
    void* w = ((LayoutManager*)FUN_0080fee0())->GetWorldMainWindow(0x5f1bfc10);
    if (w != 0) {
        void* x = ((VFP2)(*(void***)w)[0xf0 / 4])(w, 0x615b50d, 1);
        if (x != 0) {
            bl = (unsigned char)((VFCI)(*(void***)x)[0x28 / 4])(x);
            bl &= 1;
        }
    }
    FUN_00e02580(bl == 0);
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
