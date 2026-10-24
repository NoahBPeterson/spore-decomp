// Slice s00e01750 (batch bfs3, slice 14). Region 0xe01750-0xe02572.
// Global options UI: window-proc dispatch, activation, tooltips, and the
// context-sensitive Sporepedia / SporeGuide launchers.
// Optimised: /O2 /MD /Gy /TP /arch:SSE.
#include "types.h"

// ---------------------------------------------------------------------------
//  Opaque runtime helpers.  Declared only, never defined here; the trailing
//  address is the retail VA the object-file relocation must resolve to.
// ---------------------------------------------------------------------------
extern "C" void* __cdecl EA_Allocate(uint32_t size, const char* name, int a, int b,
                                     int c, int d);              // 0xf473a0
extern "C" void  __cdecl EA_Free(void* p);                       // 0xf47380

extern "C" void* __cdecl SP_GetCurrentGameMode();                // 0xb5b800
extern "C" void* __cdecl SP_MessageServer();                     // 0x67dcc0
extern "C" void* __cdecl SP_WindowManager();                     // 0x67caa0
extern "C" void* __cdecl SP_GameTimeManager();                   // 0xb3d380
extern "C" void* __cdecl SP_EffectsManager();                    // 0x67ddd0
extern "C" void* __cdecl SP_GetUniverseContext();                // 0x1021080
extern "C" void* __cdecl SP_GetPlayerHomePlanet();               // 0x1021370
extern "C" void* __cdecl SP_GetActivePlanet();                   // 0x1021260
extern "C" void* __cdecl SP_PropertyManager();                   // 0x67de30
extern "C" void* __cdecl SP_CivModeStrategyGet();                // 0xcf74c0
extern "C" void* __cdecl SP_TribeModeStrategyInstance();         // 0xcd40b0
extern "C" void* __cdecl SP_GetSetting3();                       // 0x401030
extern "C" void* __cdecl SP_SpaceGameGet();                      // 0x1002bd0
extern "C" void  __cdecl SPUI_BeginModal();
extern "C" void  __cdecl SPUI_EndModal();
extern "C" void  __cdecl FUN_00e00db0(void*, float);
extern "C" void  __cdecl FUN_00e01990();
extern "C" void  __cdecl FUN_00e01cc0();
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
extern "C" void  __cdecl FUN_0080fee0();
extern "C" void  __cdecl FUN_00810000();
extern "C" void  __cdecl FUN_008120d0();
extern "C" void  __cdecl FUN_00810090();
extern "C" void  __cdecl FUN_00835990();
extern "C" void  __cdecl FUN_00835ed0();
extern "C" void  __cdecl FUN_006b55c0();
extern "C" void  __cdecl FUN_005ca960();
extern "C" void  __cdecl FUN_005c2570();
extern "C" void  __cdecl FUN_00b5f950();
extern "C" void  __cdecl FUN_00b32250();
extern "C" void  __cdecl FUN_00b32280();

// ---------------------------------------------------------------------------
//  Global data.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
//  Opaque vtable-dispatched UI object.  Every slot returns void* (unused
//  return values are simply discarded); slots are named after their vtable
//  byte offset.  Only the offsets actually called by this slice are given a
//  parameter list; the rest keep the trivial () signature.
// ---------------------------------------------------------------------------
class cVtblObj {
public:
    virtual void* v000();
    virtual void* v004();
    virtual void* v008();
    virtual void* v00c(uint32_t id);                    // 0x00c  make/attach child
    virtual void* v010();
    virtual void* v014(uint32_t, void*, void*);         // 0x014  message send
    virtual void* v018(); virtual void* v01c();
    virtual void* v020(); virtual void* v024(); virtual void* v028(); virtual void* v02c();
    virtual void* v030(uint32_t, void*);                // 0x030  property set
    virtual void* v034(); virtual void* v038(); virtual void* v03c();
    virtual void* v040(); virtual void* v044(); virtual void* v048(); virtual void* v04c();
    virtual void* v050(); virtual void* v054(); virtual void* v058(); virtual void* v05c();
    virtual void* v060(); virtual void* v064(); virtual void* v068(); virtual void* v06c();
    virtual void* v070();                               // 0x070
    virtual void* v074(); virtual void* v078();
    virtual void* v07c(int, void*);                     // 0x07c  set visual state
    virtual void* v080(); virtual void* v084(); virtual void* v088(); virtual void* v08c();
    virtual void* v090(); virtual void* v094(); virtual void* v098(); virtual void* v09c();
    virtual void* v0a0(); virtual void* v0a4(); virtual void* v0a8(); virtual void* v0ac();
    virtual void* v0b0(); virtual void* v0b4(); virtual void* v0b8(); virtual void* v0bc();
    virtual void* v0c0(); virtual void* v0c4(); virtual void* v0c8(); virtual void* v0cc();
    virtual void* v0d0(); virtual void* v0d4(); virtual void* v0d8(); virtual void* v0dc();
    virtual void* v0e0(); virtual void* v0e4(); virtual void* v0e8(); virtual void* v0ec();
    virtual void* v0f0(); virtual void* v0f4(); virtual void* v0f8(); virtual void* v0fc();
    virtual void* v100();
    virtual void* v104(void* child);                    // 0x104  attach child object
};

// cSPUILayout: window lookup helper.
class cSPUILayout {
public:
    cVtblObj* FindWindowByID(uint32_t id, int a);       // va 008105b0
};

// Tip / tooltip window (own vtable + non-virtual text setter).
class cSPUITooltipWinProc {
public:
    virtual void* v000();                               // 0x00
    virtual void* v004();                               // 0x04
    void SetText(const wchar_t* text, void* a, char b); // va 00835ed0
};

// SP::cString (localised string, stack temp).
namespace SP {
class cString {
public:
    cString(uint32_t a, uint32_t b, const wchar_t* c);  // va 006b55c0+0x1b0 (0x6b5770)
    const wchar_t* GetText();                           // va 006b55c0
    ~cString();                                         // va 006b5240
};
}

// EA::Stopwatch.
class cStopwatch {
public:
    void Restart();                                     // va 00571e80
};

// SP::cGameTimeManager.
class cGameTimeManager {
public:
    void IncPauseGate(uint32_t id);                     // va 00b32220
};

// CurMgr.
class cCurMgr {
public:
    void* GetSystem();                                  // va 008013b0
    void  FindGlobal(uint32_t id);                      // va 00801b60
};

// cSPUIGlobalUI (the options window's root UI object).
class cSPUIGlobalUI {
public:
    void SetVisibility(int visible);                    // va 00e01350
};

// cAppModeSpace.
class cAppModeSpace {
public:
    void TransitionFromPlanetToSolar();                 // va 00fde3e0
};

// SP::cCivModeStrategy / SP::cTribeModeStrategy.
class cCivStrategy {
public:
    void* GetState();                                   // va 00cf74f0
};
class cTribeStrategy : public cVtblObj {
public:
    char TerrainNotHasKey();                            // va 00cd44a0
};

// space-mode check helper.
class cSpaceMode {
public:
    char Check();                                       // va 01065e20
};

// effect validity probe (this = the handle value).
class cEffectRef {
public:
    char IsActive();                                    // va 00d09660
};

// browser (Sporepedia asset browser), reached via SP_GetSetting3().
class cBrowser {
public:
    char CanSporepediaShowSporeGuide();                 // va 00644df0
    void ShowSporeGuide();                              // va 0064b6a0
};

// Translator (this = the global pointer object).
class cTranslator {
public:
    void SetUserName(void* name);                       // va 005cd160
};

// Out-parameter struct handed to the Sporepedia launcher (VA 0x64a990).
// The launcher owns the whole 0x48-byte block (see the original frame size).
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

// cActiveView: the WindowManager's active-view object (returned pointer points
// four bytes past the object start, so the flag lands at +0x289 of the result).
struct cActiveView {
    uint8_t pad00[0x289];
    uint8_t mActive;                                    // +0x289
};

// UI/NetworkActivityProc instance layout.
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

// cSPUIGlobalOptions: the options page controller.
class cSPUIGlobalOptions {
public:
    uint8_t      pad00[0x10];
    cSPUILayout* mLayout;                               // +0x10
    cVtblObj*    mWin14;                                // +0x14
    cVtblObj*    mWin18;                                // +0x18
    cVtblObj*    mWin1c;                                // +0x1c
    cVtblObj*    mWin20;                                // +0x20
    void Update();
};

// cSPUIGlobalUIRootWinProc: the options root window procedure.
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

// Game-mode ids compared by these functions.
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

struct AutoWin { void* mp; };
struct SPUILayout2 {
    void* FindWindowByID(void* id, int a);
    void  SetVisibility(void* v);
    void  Init(void* a, int b, int c);
    void  SetReloadCallback(void* cb, void* arg);
};

// ---------------------------------------------------------------------------
//  Private helpers used by cSPUIGlobalOptions::Update.
// ---------------------------------------------------------------------------
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

// Build a tooltip window and attach it to "win".  Mirrors the two inline
// blocks at 0x00e01a12 and 0x00e01ab9 (only the string id differs).
static void MakeTooltip(cVtblObj* win, uint32_t textId) {
    win->v07c(2, 0);
    cSPUITooltipWinProc* tip;
    void* mem = FUN_009512d0(0x68, 4, "UI/cSPUITooltipWinProc", FUN_009512c0());
    if (mem) {
        tip = (cSPUITooltipWinProc*)FUN_00835cc0(mem);
        if (tip) tip->v000();
    } else {
        tip = 0;
    }
    {
        SP::cString text(0xc0152a6d, textId, 0);
        tip->SetText(text.GetText(), (void*)-1, 1);
    }
    win->v104(tip);
    if (tip) tip->v004();
}

// Shared "begin the modal transition" tail used by two blocks of
// cSPUIGlobalUIRootWinProc::OnModalWindowEnd.
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

// ===========================================================================
//  0x00e01750  message dispatch (switch on sub-command)
// ===========================================================================
// @ 0x00e01750
char Dispatch(void* self, void* win, void* msg) {
    // Large switch; see nonmatching.txt.
    (void)self; (void)win; (void)msg;
    return 0;
}

// ===========================================================================
//  0x00e018c0  activate/deactivate (modal begin/end)
// ===========================================================================
// @ 0x00e018c0
void Activate(void* self, char on) {
    (void)self; (void)on;
}

// ===========================================================================
//  0x00e01990  global-options page refresh (windows + tooltips + net proc)
// ===========================================================================
// @ 0x00e01990
void cSPUIGlobalOptions::Update() {
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

// ===========================================================================
//  0x00e01ce0  nested FindWindowByID
// ===========================================================================
struct Ctl { char pad[8]; void* f08; };
struct GlobalOpts2 {
    char pad[0x5c];
    Ctl* p5c;
    void* FindWin(void* id);
};
// @ 0x00e01ce0
void* GlobalOpts2::FindWin(void* id) {
    if (p5c->f08 != 0) {
        return ((SPUILayout2*)p5c->f08)->FindWindowByID(id, 1);
    }
    return 0;
}

// ===========================================================================
//  0x00e01d00  show transition (timing + visibility)
// ===========================================================================
// @ 0x00e01d00
void ShowTransition(void* self) {
    (void)self;
}

// ===========================================================================
//  0x00e01db0  root-window modal message handler (state machine)
// ===========================================================================
// @ 0x00e01db0
void cSPUIGlobalUIRootWinProc::OnModalWindowEnd(uint32_t /*wparam*/, uint32_t msg) {
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

// ===========================================================================
//  0x00e02040  SP::ShowContextSensitiveSporepedia
// ===========================================================================
struct PlanetInfo { uint8_t pad00[0x18]; void* mName; };  // planet object name at +0x18
struct PlanetName { void* mName; };                        // cPlanet::GetName result
// @ 0x00e02040
void ShowContextSensitiveSporepedia(void* arg) {
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

// ===========================================================================
//  0x00e02200  SP::ShowContextSensitiveSporeGuide
// ===========================================================================
struct CivStrategyData { uint8_t pad00[0x148]; uint8_t mField148; };
struct EffectSlots {
    uint8_t pad00[0x20];
    void*   mField20;                                   // +0x20
    uint8_t pad24[0x38];
    void*   mField5c;                                   // +0x5c
    uint8_t pad60[0x20];
    void*   mField80;                                   // +0x80
};
// @ 0x00e02200
void ShowContextSensitiveSporeGuide(void* /*arg*/) {
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

// ===========================================================================
//  0x00e02430  create options dialog + tooltips
// ===========================================================================
// @ 0x00e02430
void CreateOptionsDialog(void* self) { (void)self; }