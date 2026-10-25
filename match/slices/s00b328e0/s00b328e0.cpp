// Slice s00b328e0 -- game-mode enter/leave helpers of the SP space tool.
//
// Every function here is a straight-line sequence of subsystem lookups, mode
// comparisons and teardown/setup calls.  The singleton accessors have no
// arguments (they only read a global) and are modelled as free functions
// returning the subsystem object; the calls that retail makes with the object
// in ecx are member functions of that object.  Mode keys are the engine's
// 0x01654c00..0x01654c10 "app mode" tag values.
//
// Flags: default VS2008 x86 (/O2 /MD /Gy /EHsc /TP).
#include "types.h"

typedef unsigned int  u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------
// The subsystem object.  Only calls are modelled: no data members are needed
// here, every member below is an external function whose address is given.
// ---------------------------------------------------------------------------
struct Obj;

struct Obj {
    void  FUN_00b7dec0();                 // 0x00b7dec0
    void  FUN_00ac7080();                 // 0x00ac7080  cGroundLayer::clear
    void  FUN_00ac4f50();                 // 0x00ac4f50  cAStar::drain
    void  FUN_00ac1500();                 // 0x00ac1500
    void  FUN_00acd210();                 // 0x00acd210
    void  FUN_00ad0bd0();                 // 0x00ad0bd0
    void  FUN_00ad2560(u32 mode);         // 0x00ad2560  cCityVisualizer::setActiveVignette
    void  FUN_00ae7de0();                 // 0x00ae7de0  SelIdxReset
    void  FUN_00af0f30();                 // 0x00af0f30
    void  FUN_00af1020();                 // 0x00af1020
    void  FUN_00ae7df0(u32 mode);         // 0x00ae7df0  SelIdxSet
    void  FUN_00aeb680(u32 mode);         // 0x00aeb680
    void  FUN_00aeb700();                 // 0x00aeb700
    void  FUN_00b0c190(u32 unload);       // 0x00b0c190  cPlanetManager::Unload
    void  FUN_00b0c520(u32 key);          // 0x00b0c520  cPlanetManager::SetCurrentKey
    void  FUN_00b26320();                 // 0x00b26320
    void  FUN_00b26600();                 // 0x00b26600  cGameNounManager::FUN_00b26600
    void  FUN_00b267c0(u32 mode);         // 0x00b267c0
    void  FUN_00b2f680(u32 mode);         // 0x00b2f680
    void  FUN_00b2f710();                 // 0x00b2f710
    void  FUN_00b33d00();                 // 0x00b33d00
    void  FUN_00b33d40(u32 mode);         // 0x00b33d40
    void  FUN_00b33dd0();                 // 0x00b33dd0
    void  FUN_00b4b7b0();                 // 0x00b4b7b0
    void  FUN_00b3d7a0();                 // 0x00b3d7a0
    void  FUN_00b79a50();                 // 0x00b79a50
    void  FUN_00b79aa0();                 // 0x00b79aa0
    void  FUN_00b7f390(u32 mode);         // 0x00b7f390
    void  FUN_00b8d2f0();                 // 0x00b8d2f0
    void  FUN_00b8ff60();                 // 0x00b8ff60
    void  FUN_00b90480();                 // 0x00b90480
    void  FUN_00ba3310();                 // 0x00ba3310  clear
    void  FUN_00ba70b0();                 // 0x00ba70b0
    void  FUN_00ba8160(u32 mode);         // 0x00ba8160
    void  FUN_00bad810();                 // 0x00bad810  cStarManager::Reset
    void  FUN_00bb7620();                 // 0x00bb7620
    void  FUN_00bb8b20();                 // 0x00bb8b20  LoadStarDatabase
    void  FUN_00bbfe80();                 // 0x00bbfe80
    void  FUN_00bc20e0(u32 subject);      // 0x00bc20e0  SetSubject
    void  FUN_00bc8040();                 // 0x00bc8040
    void  FUN_00bc8200();                 // 0x00bc8200
    void  FUN_00bc83f0();                 // 0x00bc83f0  thunk of 0x00bc8200
    void  FUN_00bcb700();                 // 0x00bcb700
    void  FUN_00c2e4e0();                 // 0x00c2e4e0  EAP audio sys_gui
    void  FUN_00cd56e0();                 // 0x00cd56e0  cTribeModeStrategy
    void  FUN_00cf8fd0();                 // 0x00cf8fd0  cCivModeStrategy
    void  FUN_00d392f0();                 // 0x00d392f0  cLocatingOwner
    void  FUN_00dd6d70();                 // 0x00dd6d70  cSPUIEventLog::clear_events
    void  FUN_00dd8da0(u32 visible);      // 0x00dd8da0  SetVisibility
    void  FUN_00e15a10(u32 mode);         // 0x00e15a10
    void  FUN_00e180d0();                 // 0x00e180d0  ReleaseAll
    void  FUN_00e18340();                 // 0x00e18340  RemoveHandlerAndRelease
    void  FUN_00fdbee0();                 // 0x00fdbee0  EnterSpaceGame
    void  FUN_00fdc710();                 // 0x00fdc710  TransitionFromLoadToPlanet
    void  FUN_00fe0160();                 // 0x00fe0160  cAppModeSpace
    void  FUN_00fe0570();                 // 0x00fe0570  InitSpaceMode
    void  FUN_00fe19a0();                 // 0x00fe19a0  cAppModeSpace
    Obj*  FUN_00ac79d0();                 // 0x00ac79d0  cGroundEditorRes::getContainer
    void  FUN_00ac7a40(u32 container);    // 0x00ac7a40  drainNouns
};

// ---------------------------------------------------------------------------
// Singleton accessors: read a global, take no arguments.
// ---------------------------------------------------------------------------
Obj* FUN_0067caa0();   // 0x0067caa0  SP::WindowManager
Obj* FUN_0067dd60();   // 0x0067dd60
Obj* FUN_0067dcc0();   // 0x0067dcc0  MessageServer
Obj* FUN_00b3d240();   // 0x00b3d240
Obj* FUN_00b3d260();   // 0x00b3d260  SP::BehaviorManager
Obj* FUN_00b3d290();   // 0x00b3d290
Obj* FUN_00b3d2a0();   // 0x00b3d2a0  SP::StarManager
Obj* FUN_00b3d2b0();   // 0x00b3d2b0
Obj* FUN_00b3d300();   // 0x00b3d300  SP::NounManager
Obj* FUN_00b3d310();   // 0x00b3d310
Obj* FUN_00b3d340();   // 0x00b3d340
Obj* FUN_00b3d350();   // 0x00b3d350  SP::PlanetModel
Obj* FUN_00b3d360();   // 0x00b3d360
Obj* FUN_00b3d370();   // 0x00b3d370
Obj* FUN_00b3d3b0();   // 0x00b3d3b0
Obj* FUN_00b3d3c0();   // 0x00b3d3c0
Obj* FUN_00b3d3e0();   // 0x00b3d3e0  SP::EventLog
Obj* FUN_00b3d400();   // 0x00b3d400
Obj* FUN_00b3d410();   // 0x00b3d410
Obj* FUN_00b3d420();   // 0x00b3d420
Obj* FUN_00b3d430();   // 0x00b3d430  SP::TerraformingManager
Obj* FUN_00b3d440();   // 0x00b3d440
Obj* FUN_00b3d480();   // 0x00b3d480
Obj* FUN_00b3d490();   // 0x00b3d490
Obj* FUN_00b3d4a0();   // 0x00b3d4a0  CommManager
Obj* FUN_00b3d4c0();   // 0x00b3d4c0
Obj* FUN_00b3d7a0();   // 0x00b3d7a0
Obj* FUN_00bc8000();   // 0x00bc8000
Obj* FUN_00af13b0();   // 0x00af13b0  CreateLayoutManager
Obj* FUN_00fd9c60();   // 0x00fd9c60  cAppModeSpace
Obj* FUN_00d37cb0();   // 0x00d37cb0
Obj* FUN_00d38840();   // 0x00d38840  cCreatureModeStrategy::Instance
Obj* FUN_00cd3440();   // 0x00cd3440
Obj* FUN_00cd40b0();   // 0x00cd40b0  cTribeModeStrategy::Instance
Obj* FUN_00d004b0();   // 0x00d004b0
Obj* FUN_00cf74c0();   // 0x00cf74c0  cCivModeStrategy::Get

// ---------------------------------------------------------------------------
// Plain functions (no object).
// ---------------------------------------------------------------------------
void FUN_00ba51f0();                                  // 0x00ba51f0
void FUN_00e3c760();                                  // 0x00e3c760
void FUN_00e4bc70();                                  // 0x00e4bc70
void FUN_00bcb6c0();                                  // 0x00bcb6c0
void FUN_00bcb700();                                  // 0x00bcb700
void FUN_01022580();                                  // 0x01022580  StartBackgroundSim
void FUN_01022460();                                  // 0x01022460  ShutdownBackgroundSimulator
void FUN_01021960(int mode);                          // 0x01021960
void FUN_010219b0(int a, int b);                      // 0x010219b0
int  FUN_01021080();                                  // 0x01021080  GetUniverseContext

// The app property list lives behind a global pointer at 0x015fd918.
struct PropList {
    bool GetDescription(u32 id);                      // 0x006a25a0
    void SetBoolProperty(u32 id, bool value);         // 0x006a17e0
};
extern PropList* gAppPropertyList;                    // 0x015fd918
extern Obj* gLayoutMgr;                               // 0x015e4ef0  layout manager singleton

// ---------------------------------------------------------------------------
// Data layouts touched by the mode switches.
// ---------------------------------------------------------------------------
struct Window {
    u8 pad00[0x28d];
    u8 mWindowClosed;        // +0x28d
};

// Window manager: the second virtual slot hands back the active window.
struct WindowManager {
    virtual void*  FUN_00(void);
    virtual char*  FUN_04(void);
};

struct AppMode {
    u8 pad00[0x88];
    u8 mSpacePending;        // +0x88
};

// ---------------------------------------------------------------------------
// Virtual dispatch helpers (slot is the byte offset into the vtable).
// ---------------------------------------------------------------------------
struct VObj { };

static inline void* vcall0(void* p, int slot)
{
    typedef void* (VObj::*PMF)();
    PMF f;
    *(void**)&f = ((void**)*(void***)p)[slot / 4];
    return (((VObj*)p)->*f)();
}

static inline void vcall1(void* p, int slot, u32 a)
{
    typedef void (VObj::*PMF)(u32);
    PMF f;
    *(void**)&f = ((void**)*(void***)p)[slot / 4];
    (((VObj*)p)->*f)(a);
}

static inline void vcall3(void* p, int slot, u32 a, u32 b, u32 c)
{
    typedef void (VObj::*PMF)(u32, u32, u32);
    PMF f;
    *(void**)&f = ((void**)*(void***)p)[slot / 4];
    (((VObj*)p)->*f)(a, b, c);
}

// Mode keys used by every dispatcher in this slice.
enum {
    kMode00 = 0x1654c00,   // DAT_01654c00
    kMode01 = 0x1654c01,   // DAT_01654c01
    kMode02 = 0x1654c02,   // DAT_01654c02
    kMode03 = 0x1654c03,   // DAT_01654c03
    kMode04 = 0x1654c04,   // DAT_01654c04
    kMode05 = 0x1654c05,   // gAppNameTag
    kMode10 = 0x1654c10,   // DAT_01654c10
    kNoMode = 0xdbdba1      // LAB_00dbdb9f_2 is not a mode
};

// The mode arms of 0x00b33350: offsets 3 and 6..15 of the 0x00..0x10 range.
static inline bool ModeArm(int mode)
{
    switch (mode) {
    case kMode03:
    case 0x1654c06: case 0x1654c07: case 0x1654c08: case 0x1654c09:
    case 0x1654c0a: case 0x1654c0b: case 0x1654c0c: case 0x1654c0d:
    case 0x1654c0e: case 0x1654c0f:
        return true;
    default:
        return false;
    }
}

// ===========================================================================
// 0x00b328e0 -- set the "game mode active" property and reset the selection.
// ===========================================================================
// @ 0x00b328e0
void FUN_00b328e0(int mode)
{
    if (gAppPropertyList->GetDescription(0x66439bf9)) {
        bool active;
        switch ((u32)mode - kMode00) {
        case 0:
        case 1:
        case 2:
            active = true;
            break;
        case 3:
        case 4:
        case 5:
            active = false;
            break;
        default:
            active = false;
            break;
        }
        gAppPropertyList->SetBoolProperty(0xc3f9e250, active);
    }

    FUN_00b3d490()->FUN_00ae7df0((u32)mode);
    FUN_00b3d3e0()->FUN_00dd8da0(0);
}

// ===========================================================================
// 0x00b32970 -- leave a mode: refresh the HUD, clear events and notify the
// message server about the new mode.
// ===========================================================================
// @ 0x00b32970
void FUN_00b32970(u32 fromMode, int mode)
{
    vcall0(FUN_0067dd60(), 0x18);

    if (FUN_00b3d3e0() != 0) {
        FUN_00b3d3e0()->FUN_00dd8da0(1);
        if (fromMode != kNoMode)
            FUN_00b3d3e0()->FUN_00dd6d70();
    }

    u32 event;
    switch (mode) {
    case kMode01: event = 0x26b05664; break;
    case kMode02: event = 0x24947c07; break;
    case kMode03: event = 0x2ab05c28; break;
    case kMode04:
    case kMode05: event = 0x2887b6de; break;
    default:
        return;
    }

    vcall3(FUN_0067dcc0(), 0x14, 0x6579712, event, 0);
}

// ===========================================================================
// 0x00b32a10 -- clear the active mode flag and drain rendering state.
// ===========================================================================
// @ 0x00b32a10
void FUN_00b32a10(u32 prevMode, u32 nextMode)
{
    if (gAppPropertyList->GetDescription(0x66439bf9))
        gAppPropertyList->SetBoolProperty(0xc3f9e250, false);

    FUN_00b3d360()->FUN_00b7dec0();
    FUN_00b3d370()->FUN_00ac7080();
    FUN_00bc8000()->FUN_00bc83f0();
    FUN_00b3d490()->FUN_00ae7de0();

    if (prevMode != kNoMode && nextMode != kNoMode &&
        prevMode != kMode10 && nextMode != kMode10)
        FUN_00b3d4a0()->FUN_00aeb700();
}

// ===========================================================================
// 0x00b32aa0 -- tear down a running mode session.
// ===========================================================================
// @ 0x00b32aa0
void FUN_00b32aa0()
{
    FUN_00b3d360()->FUN_00b7dec0();
    FUN_00b3d290()->FUN_00ac4f50();
    FUN_00b3d290()->FUN_00ac1500();
    vcall0(FUN_00b3d260(), 0x30);
    FUN_00b3d4a0()->FUN_00aeb700();
    FUN_00b3d3b0()->FUN_00b2f710();
    FUN_00b3d3c0()->FUN_00b79a50();
    FUN_00b3d400()->FUN_00e18340();

    if (FUN_00b3d3e0() != 0)
        FUN_00b3d3e0()->FUN_00dd6d70();
}

// ===========================================================================
// 0x00b32b20 -- full mode shutdown (cheap "return to front end").
// ===========================================================================
// @ 0x00b32b20
void FUN_00b32b20()
{
    // WindowManager's second vtable slot returns a subobject 4 bytes into the
    // window; back up to the object and mark it closed.
    char* p = ((WindowManager*)FUN_0067caa0())->FUN_04();
    Window* win = p ? (Window*)(p - 4) : 0;
    win->mWindowClosed = 0;

    FUN_00ba51f0();
    FUN_00e3c760();
    FUN_00b3d430()->FUN_00bbfe80();
    FUN_00b3d480()->FUN_00acd210();
    FUN_00b3d480()->FUN_00ad0bd0();
    vcall0(FUN_00b3d2b0(), 0x64);
    FUN_00b3d420()->FUN_00b8ff60();
    FUN_00b3d240()->FUN_00b33dd0();
    FUN_00b3d3e0()->FUN_00dd6d70();
    FUN_00b3d300()->FUN_00b26600();
    vcall0(FUN_00b3d310(), 0x10);
    FUN_00b3d4c0()->FUN_00ba3310();
    FUN_00b3d440()->FUN_00b0c190(1);
    FUN_00b3d350()->FUN_00b8d2f0();

    FUN_01022460();
    FUN_01021960(-1);
    FUN_010219b0(0, 0);

    FUN_00b3d2a0()->FUN_00ba70b0();
    FUN_00bc8000()->FUN_00bc8040();
    FUN_00af13b0()->FUN_00af0f30();
    FUN_00b3d2a0()->FUN_00bad810();
    FUN_00b3d2a0()->FUN_00bb8b20();
    FUN_00b3d2a0()->FUN_00bb7620();
    FUN_00bcb700();
    FUN_00b3d340()->FUN_00b267c0(0);
}

// ===========================================================================
// 0x00b32c60 -- leave a mode (teardown chain), with an editor-mode fixup.
// ===========================================================================
// @ 0x00b32c60
void FUN_00b32c60(int mode)
{
    if (mode == kMode10)
        FUN_00e4bc70();

    FUN_00b3d360()->FUN_00b7dec0();
    FUN_00b3d290()->FUN_00ac4f50();
    FUN_00b3d290()->FUN_00ac1500();
    vcall0(FUN_00b3d260(), 0x30);
    FUN_00b3d4a0()->FUN_00aeb700();
    FUN_00b3d3b0()->FUN_00b2f710();
    FUN_00b3d3c0()->FUN_00b79a50();
    FUN_00b3d400()->FUN_00e18340();
}

// ===========================================================================
// 0x00b32ce0 -- shutdown shared with 0x00b32b20 (no window fixup).
// ===========================================================================
// @ 0x00b32ce0
void FUN_00b32ce0()
{
    FUN_00ba51f0();
    FUN_00e3c760();
    FUN_00b3d430()->FUN_00bbfe80();
    FUN_00b3d480()->FUN_00acd210();
    FUN_00b3d480()->FUN_00ad0bd0();
    vcall0(FUN_00b3d2b0(), 0x64);
    FUN_00b3d420()->FUN_00b8ff60();
    FUN_00b3d240()->FUN_00b33dd0();
    FUN_00b3d3e0()->FUN_00dd6d70();
    FUN_00b3d300()->FUN_00b26600();
    vcall0(FUN_00b3d310(), 0x10);
    FUN_00b3d4c0()->FUN_00ba3310();
    FUN_00b3d440()->FUN_00b0c190(1);
    FUN_00b3d350()->FUN_00b8d2f0();

    FUN_01022460();
    FUN_01021960(-1);
    FUN_010219b0(0, 0);

    FUN_00b3d2a0()->FUN_00ba70b0();
    FUN_00bc8000()->FUN_00bc8040();
    FUN_00af13b0()->FUN_00af0f30();
    FUN_00bcb700();
}

// ===========================================================================
// 0x00b32dd0 -- enter a mode: build the HUD, plant the mode key everywhere.
// ===========================================================================
// @ 0x00b32dd0
void FUN_00b32dd0(u32 mode)
{
    FUN_00bcb6c0();
    FUN_00b3d2a0()->FUN_00ba8160(mode);
    FUN_01022580();
    FUN_00b3d4a0()->FUN_00aeb680(mode);

    if (mode != kMode10)
        FUN_00b3d480()->FUN_00ad2560(mode);

    FUN_00b3d400()->FUN_00e15a10(mode);

    if (mode != kMode00)
        FUN_00b3d240()->FUN_00b33d40(mode);

    vcall1(FUN_00b3d310(), 0x14, mode);
    FUN_00b3d420()->FUN_00b90480();
    vcall0(gLayoutMgr, 0x50);
    FUN_00bc8000()->FUN_00bc8200();
    FUN_00af13b0()->FUN_00af1020();
}

// ===========================================================================
// 0x00b32e80 -- enter a mode and select its strategy (creature/tribe/civ/space).
// ===========================================================================
// @ 0x00b32e80
void FUN_00b32e80(int mode)
{
    FUN_00b3d360()->FUN_00b7dec0();
    vcall0(FUN_00b3d2b0(), 0x60);
    FUN_00b3d290()->FUN_00ac1500();

    if (mode != kMode00)
        FUN_00b3d240()->FUN_00b33d40((u32)mode);

    FUN_00b3d350()->FUN_00b7f390((u32)mode);
    FUN_00b3d430()->FUN_00bc20e0((u32)mode);
    FUN_00b3d3b0()->FUN_00b2f680((u32)mode);
    FUN_00b3d440()->FUN_00b0c520((u32)mode);
    FUN_00b3d340()->FUN_00b267c0(0);

    switch ((u32)mode - kMode00) {
    case 0x1654c01 - kMode00:
    case 0x1654c02 - kMode00:
    case 0x1654c04 - kMode00:
        FUN_00b3d3c0()->FUN_00b79aa0();
        break;
    case 0x1654c05 - kMode00:
        ((AppMode*)FUN_00fd9c60())->mSpacePending = 0;
        FUN_00fd9c60()->FUN_00fe0570();
        FUN_00b3d3c0()->FUN_00b79aa0();
        break;
    case 0x1654c03 - kMode00:
    case 0:
        return;
    }
}

// ===========================================================================
// 0x00b32f60 -- remap the mode key and propagate it to the managers.
// ===========================================================================
// @ 0x00b32f60
void FUN_00b32f60(int mode)
{
    FUN_01022580();

    u32 mapped;
    switch (mode) {
    case kMode00: mapped = kMode01; break;
    case kMode01: mapped = kMode02; break;
    case kMode02: mapped = kMode04; break;
    case kMode03: mapped = kMode05; break;
    case kMode04: mapped = kMode05; break;
    default:      mapped = 0xffffffff; break;
    }

    FUN_00b3d4a0()->FUN_00aeb680(mapped);
    FUN_00b3d480()->FUN_00ad2560(mapped);
    FUN_00b3d240()->FUN_00b33d40(mapped);
    FUN_00b3d420()->FUN_00b90480();
    vcall1(FUN_00b3d310(), 0x14, mapped);
    FUN_00b3d2a0()->FUN_00ba8160(mapped);
    FUN_00b3d400()->FUN_00e180d0();

    Obj* editor = FUN_00b3d2b0();
    u32 nouns = (u32)editor->FUN_00ac79d0();
    FUN_00b3d2b0()->FUN_00ac7a40(nouns);
}

// ===========================================================================
// 0x00b33030 -- enter a mode (strategy-free variant used by the UI).
// ===========================================================================
// @ 0x00b33030
void FUN_00b33030(int mode)
{
    FUN_00b3d350()->FUN_00b7f390((u32)mode);
    FUN_00b3d430()->FUN_00bc20e0((u32)mode);
    FUN_00b3d3b0()->FUN_00b2f680((u32)mode);
    FUN_00b3d440()->FUN_00b0c520((u32)mode);

    if (mode > kMode01)
        vcall0(FUN_00b3d2b0(), 0x60);

    switch (mode) {
    case kMode01:
    case kMode02:
    case kMode04:
        FUN_00b3d3c0()->FUN_00b79aa0();
        break;
    case kMode05:
        FUN_00b3d3c0()->FUN_00b79aa0();
        ((AppMode*)FUN_00fd9c60())->mSpacePending = 1;
        FUN_00fd9c60()->FUN_00fe0160();
        break;
    }
}

// ===========================================================================
// 0x00b330e0 -- small mode-entry helper (HUD + key, no strategy).
// ===========================================================================
// @ 0x00b330e0
void FUN_00b330e0(u32 mode)
{
    FUN_00bcb6c0();
    FUN_00b3d4a0()->FUN_00aeb680(mode);
    FUN_00b3d240()->FUN_00b33d40(mode);
    FUN_00b3d420()->FUN_00b90480();
    vcall1(FUN_00b3d310(), 0x14, mode);
    FUN_00b3d400()->FUN_00e15a10(mode);
}

// ===========================================================================
// 0x00b33130 -- main mode dispatch: per-mode strategy activation.
// ===========================================================================
// @ 0x00b33130
void FUN_00b33130(int mode)
{
    FUN_00b3d3e0()->FUN_00dd6d70();
    if (mode != kMode05)
        FUN_01022580();

    FUN_00b3d290()->FUN_00ac1500();
    FUN_00b3d440()->FUN_00b0c520((u32)mode);
    FUN_00b3d430()->FUN_00bc20e0((u32)mode);
    FUN_00b3d3b0()->FUN_00b2f680((u32)mode);
    FUN_00b3d350()->FUN_00b7f390((u32)mode);

    switch (mode) {
    case kMode01: {
        FUN_00b3d480()->FUN_00ad2560((u32)mode);
        FUN_00b3d310()->FUN_00b3d7a0();
        FUN_00b3d3c0()->FUN_00b79aa0();
        Obj* owner = FUN_00d37cb0();
        Obj* strategy = FUN_00d38840();
        if (owner == 0 && strategy != 0)
            strategy->FUN_00d392f0();
        break;
    }
    case kMode02: {
        FUN_00b3d480()->FUN_00ad2560((u32)mode);
        FUN_00b3d310()->FUN_00b3d7a0();
        FUN_00b3d3c0()->FUN_00b79aa0();
        Obj* owner = FUN_00cd3440();
        Obj* strategy = FUN_00cd40b0();
        if (owner == 0 && strategy != 0)
            strategy->FUN_00cd56e0();
        break;
    }
    case kMode04: {
        FUN_00b3d480()->FUN_00acd210();
        FUN_00b3d480()->FUN_00ad2560((u32)mode);
        FUN_00b3d310()->FUN_00b3d7a0();
        FUN_00b3d3c0()->FUN_00b79aa0();
        Obj* owner = FUN_00d004b0();
        Obj* strategy = FUN_00cf74c0();
        if (owner == 0 && strategy != 0)
            strategy->FUN_00cf8fd0();
        break;
    }
    case kMode05: {
        FUN_00b3d480()->FUN_00acd210();
        FUN_00b3d480()->FUN_00ad2560((u32)mode);
        int ctx = FUN_01021080();
        switch (ctx) {
        case 0:
            FUN_00fd9c60()->FUN_00fdc710();
            break;
        case 1:
            FUN_00fd9c60()->FUN_00fe19a0();
            break;
        case 2:
            FUN_00fd9c60()->FUN_00fdbee0();
            break;
        }
        break;
    }
    case kMode10:
        FUN_00b3d310()->FUN_00b3d7a0();
        FUN_00b3d3c0()->FUN_00b79aa0();
        break;
    }

    vcall0(FUN_00b3d2b0(), 0x60);
    FUN_00b3d340()->FUN_00b267c0(0);
}

// ===========================================================================
// 0x00b33350 -- shutdown + restart of the space/planet presentation.
// ===========================================================================
// @ 0x00b33350
void FUN_00b33350(int mode)
{
    FUN_00ba51f0();
    FUN_00e3c760();
    FUN_00b3d290()->FUN_00ac4f50();
    vcall0(FUN_00b3d2b0(), 0x5c);
    FUN_00b3d4a0()->FUN_00aeb700();
    FUN_00b3d240()->FUN_00b33d00();
    FUN_00b3d3e0()->FUN_00dd6d70();
    FUN_00b3d310()->FUN_00b4b7b0();
    FUN_00b3d410()->FUN_00c2e4e0();
    FUN_00b3d400()->FUN_00e18340();

    switch ((u32)mode - kMode00) {
    case 0:
    case 1:
    case 2:
    case 4:
    case 5:
    case 16:
        FUN_00b3d420()->FUN_00b8ff60();
        FUN_00b3d3b0()->FUN_00b2f710();
        FUN_00b3d3c0()->FUN_00b79a50();
        FUN_00b3d430()->FUN_00bbfe80();
        FUN_00b3d350()->FUN_00b8d2f0();
        break;
    case 3:
    case 6: case 7: case 8: case 9:
    case 10: case 11: case 12: case 13:
    case 14: case 15:
        break;
    }

    FUN_00b3d300()->FUN_00b26320();

    switch ((u32)mode - kMode00) {
    case 0:
    case 1:
    case 2:
    case 4:
    case 5:
    case 16:
        FUN_00b3d440()->FUN_00b0c190(1);
        break;
    case 3:
    case 6: case 7: case 8: case 9:
    case 10: case 11: case 12: case 13:
    case 14: case 15:
        break;
    }

    FUN_01022460();

    switch (mode) {
    case kMode01:
    case kMode02:
    case kMode04:
        FUN_01021960(-1);
        FUN_010219b0(0, 0);
        break;
    }

    vcall0(FUN_00b3d2a0(), 0x50);
    FUN_00bc8000()->FUN_00bc8200();
    FUN_00af13b0()->FUN_00af1020();
}

// ===========================================================================
// 0x00b334e0 -- mode entry for the editor tag.
// ===========================================================================
// @ 0x00b334e0
void FUN_00b334e0()
{
    FUN_00bcb6c0();
    FUN_00b3d240()->FUN_00b33d40(kMode10);
    vcall1(FUN_00b3d310(), 0x14, kMode10);
    FUN_00b3d420()->FUN_00b90480();
    vcall0(gLayoutMgr, 0x50);
    FUN_00bc8000()->FUN_00bc8200();
    FUN_00af13b0()->FUN_00af1020();
}

// ===========================================================================
// 0x00b33540 -- mode teardown for the editor tag.
// ===========================================================================
// @ 0x00b33540
void FUN_00b33540()
{
    FUN_00b3d360()->FUN_00b7dec0();
    vcall0(FUN_00b3d2b0(), 0x60);
    FUN_00b3d290()->FUN_00ac1500();
    FUN_00b3d240()->FUN_00b33d40(kMode10);
    FUN_00b3d350()->FUN_00b7f390(kMode10);
    FUN_00b3d430()->FUN_00bc20e0(kMode10);
    FUN_00b3d3b0()->FUN_00b2f680(kMode10);
    FUN_00b3d440()->FUN_00b0c520(kMode10);
    FUN_00b3d340()->FUN_00b267c0(0);
}
