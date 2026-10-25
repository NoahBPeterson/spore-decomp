// Slice s010727e0 (batch part2): SP::cSPUISpace::DoMessage, 0x01072d40 (2481 bytes) and
// SP::cSPUISpace::ShowCreatureTooltip, 0x010727e0 (1376 bytes).
//
// DoMessage is the cSPUISpace message dispatcher: the message-header check at +0xc, the
// focus-change / audio / Esc-Enter pre-steps, cSPUISpace::FUN_01066780, then a compare tree
// over the message id with one leaf per UI command (pie window, star-map filters, terraform
// store, comm hand-off, minimap / star-map toggles, creature tooltip, ...) and the shared
// tail at 0x01073599 that maps the window sub-id to the tool index.
//
// ShowCreatureTooltip refreshes the creature tooltip / slot-bar panel.
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE

#include "types.h"

namespace EA {
namespace Audio {
void* GetSystemAT();                                 // 0x00a206f0, cdecl, no args
}
}

uint32_t GetRecorderState();                         // 0x00435e90, cdecl, no args
void     RecordEvent2(uint32_t id, uint32_t state);  // 0x00435ed0, cdecl, 2 args
void*    WindowManager();                            // 0x0067caa0, cdecl, no args
void*    interface_cast_IWinButton(void* window);    // 0x005ca960, cdecl, 1 arg
uint32_t convertStarMapButtonToFilter(uint32_t id);  // 0x010659c0, cdecl, 1 arg
void     FUN_00e02c40();                             // 0x00e02c40, cdecl, no args
void*    FUN_01046fc0();                             // 0x01046fc0, cdecl, no args
void*    FUN_01015df0();                             // 0x01015df0, cdecl, no args
void*    operator_new(unsigned size, const char* name, int a, int b,
                      int c, int d);                 // 0x00f473a0, cdecl, 6 args
void*    AutoRefCount_Ctor(void* pObject);           // 0x00572660, cdecl, 1 arg; returns the slot
void     ShowContextSensitiveSporeGuide();           // 0x00e02200, cdecl, no args (param unused)

uint32_t GetUniverseContext();                       // 0x01021080, static, no args
void*    SpaceGameGet();                             // 0x01002bd0, cdecl, no args
uint8_t  FUN_00b18e40(void* ecx);                    // 0x00b18e40, thiscall, no args
void*    GetUFOSimulator();                          // 0x00ffbe50, cdecl, no args
uint8_t  FUN_00ffc0c0(void* ecx);                    // 0x00ffc0c0, thiscall, no args
void*    FUN_01021240();                             // 0x01021240, cdecl, no args
void*    FUN_010212a0();                             // 0x010212a0, cdecl, no args
void*    GetPlayerEmpire();                          // 0x01021300, cdecl, no args
void*    GameInputManager();                         // 0x00b3d250, cdecl, no args
void*    GetGameTerrainCursor();                     // 0x00b30d70, cdecl, no args
void*    GameTimeManager();                          // 0x00b3d380, cdecl, no args
void*    GetResourceManager();                       // 0x0067dcd0, cdecl, no args
void*    GetUpdater490();                            // 0x00b3d490, cdecl, no args
void*    GetSpeciesManager();                        // 0x00401090, cdecl, no args
void*    FUN_00b3d3f0();                             // 0x00b3d3f0, cdecl, no args
void*    GetGlobalImageKey(void* empire, void* arg); // 0x00dd1ca0, cdecl, 2 args, ignores them
void     SetImageFromKey(void* win, void* key);      // 0x00e2f5c0, cdecl, 2 args
void     SetTooltipText(void* win, void* text, int a, int b);  // 0x00806de0, cdecl, 4 args
uint32_t ColorRGBToU32(void* color);                 // 0x00458a40, cdecl, 1 arg
uint8_t  FUN_00eed840(const void* key);              // 0x00eed840, cdecl, 1 arg
uint8_t  FUN_00eed970(const void* a, const void* b); // 0x00eed970, cdecl, 2 args
uint8_t  FUN_004eb930(void* out, void* in);          // 0x004eb930, cdecl, 2 args
uint8_t  FUN_0106b7e0(void* a, void* b);             // 0x0106b7e0, __stdcall, 2 args, callee pops
void     ForwardWindowMessage_7590(uint32_t a, uint32_t b);  // 0x00fe7590, cdecl, 2 args

namespace SP {

struct Vec3i { uint32_t mX, mY, mZ; };

// ---------------------------------------------------------------------------
// UI objects
// ---------------------------------------------------------------------------
struct IWindow {
    uint32_t v00();
    uint32_t v04();
    uint32_t v08();
    uint32_t v0c();
    uint32_t v10();
    uint32_t v14();
    uint32_t v18();
    uint32_t v1c();                                  // +0x1c  command id
    uint32_t v20();                                  // +0x20  flags
    uint32_t v24();                                  // +0x24
    uint32_t v28(uint32_t a, uint32_t b);            // +0x28  state setter
    uint32_t v2c(); uint32_t v30(); uint32_t v34();
    uint32_t v38();                                  // +0x38  area rect getter
    uint32_t v3c(); uint32_t v40(); uint32_t v44();
    uint32_t v48(); uint32_t v4c(); uint32_t v50();
    uint32_t v54(); uint32_t v58(); uint32_t v5c();
    uint32_t v60(); uint32_t v64(); uint32_t v68();
    uint32_t v6c(const void* area);                  // +0x6c  set area
    uint32_t v70(); uint32_t v74(); uint32_t v78();
    uint32_t v7c(uint32_t a, uint32_t b);            // +0x7c  show / flag
    uint32_t v80(const void* text);                  // +0x80  set text
    uint32_t v84(); uint32_t v88(); uint32_t v8c();
    uint32_t v90(); uint32_t v94(); uint32_t v98();
    uint32_t v9c(); uint32_t va0(); uint32_t va4();
    uint32_t va8(); uint32_t vac(uint32_t color);    // +0xac  set colour
};

struct cSPUIGlobalUI {
    IWindow* FindWindowByID(uint32_t id);            // 0x00e012b0, thiscall, 1 arg
};

struct cSPUILayout {
    IWindow* FindWindowByID(uint32_t id, int recurse);     // 0x008105b0, thiscall, 2 args
    void     SetParentWin(void* child, int a, uint32_t id);  // 0x008121b0, thiscall, 3 args
};

// ---------------------------------------------------------------------------
// leaf helpers
// ---------------------------------------------------------------------------
struct cStarMap {
    void FilterHelper(uint32_t filter, uint32_t on);       // 0x01048b40, thiscall, 2 args
};

struct cFloatOwner {
    void FUN_01015f30(float value);                        // 0x01015f30, thiscall, 1 arg, ret 4
};

struct cCommandDeleteCargoButtonState {
    void* Ctor(void* owner, uint32_t window);              // 0x010665c0, thiscall, 2 args
    uint32_t v00(); uint32_t v04();
    uint32_t v08(uint32_t flag);                           // +0x08
};

struct cOverlay {
    void    SetMode(int mode);                             // 0x00fe76d0, thiscall, 1 arg
    uint8_t Test();                                        // 0x00ffc0c0, thiscall, no args
    void    Show();                                        // 0x00fe7e10, thiscall, no args
    void    Hide(int on);                                  // 0x00fe7280, thiscall, 1 arg
};

void FUN_00812d80(void* ecx, int on);                      // 0x00812d80, thiscall, 1 arg

struct cMissionCardPanel {
    uint8_t ShouldShow(uint32_t id);                       // 0x00e18c70, thiscall, 1 arg
    void    ShowPanel(uint32_t id);                        // 0x00e190c0, thiscall, 1 arg
};

struct cTerraform {
    void* GetOld (void* out);                              // 0x00bbc4f0, thiscall, 1 arg; returns out
    void* GetNew (void* out);                              // 0x00bbc510, thiscall, 1 arg; returns out
    void  StoreEmpty();                                    // 0x00bbc4a0, thiscall, no args
    void  Store3(int x, int y, int z);                     // 0x00bbc410, thiscall, 3 args
    void  Store3B(int x, int y, int z);                    // 0x00bbc460, thiscall, 3 args
};
void* TerraformingManager();                               // 0x00b3d430, cdecl, no args

struct cStarAccess {
    uint32_t GetState();                                   // 0x00b8d9b0, thiscall, no args
};

struct cInvSub {
    uint8_t      pad00[0x13c];
    cStarAccess* mpStar;                                   // +0x13c
};

struct cInventory {
    uint8_t  pad00[0x75c];
    cInvSub* mp75c;                                        // +0x75c
};

struct cSimulator {
    cInventory* GetPlayerInventory();                      // 0x00a1ad60, thiscall, no args
};

struct cSpaceGameObj {
    uint8_t pad00[0x14];
    void*   mpSpaceUI;                                     // +0x14
    void*   GetAvatar();                                   // 0x00b1fdb0, thiscall, no args
};

struct cCommContext {
    uint32_t GetCommContext();                             // 0x00ce6950, thiscall, no args
};

struct cStarManagerAccess {
    void* GetEmpireByID(uint32_t id);                      // 0x00ba9370, thiscall, 1 arg
};
void* StarManager();                                       // 0x00b3d2a0, cdecl, no args
void* CommManager();                                       // 0x00b3d4a0, cdecl, no args
void  CommAdd(uint32_t empire, uint32_t ctx,
              uint32_t a, uint32_t b, int c, int d);       // 0x00aeb720, thiscall, 6 args
void  CommRemove(uint32_t empire, uint32_t ctx,
                 uint32_t a, uint32_t b);                  // 0x00aeaa80, thiscall, 4 args

uint8_t FUN_00b8d970(void* ecx);                           // 0x00b8d970, thiscall, no args
uint32_t FUN_00b8dab0(void* ecx);                          // 0x00b8dab0, thiscall, no args

struct cInputMgr {
    uint8_t  pad00[0x110];
    uint32_t mCounter;                                     // +0x110
};

struct cEmpire {
    Vec3i* GetIds();                                       // 0x00c30f90, thiscall, no args
    void*  GetColor(void* out);                            // 0x00c32cd0, thiscall, 1 arg; returns out
    uint8_t pad00[0x84];
    uint32_t mId;                                          // +0x84
};

struct cSpeciesMgr {
    void* GetProfile(const Vec3i* key);                    // 0x004df550, thiscall, 1 arg
};

struct cImageKey {
    IWindow* FUN_00dd2320(void* empire, void* arg);        // 0x00dd2320, thiscall, 2 args
};

struct cAsset {
    uint32_t       v00();                                  // +0x00
    const wchar_t* GetName();                              // 0x00414e10, thiscall, no args
    const wchar_t* GetSummary();                           // 0x005508c0, thiscall, no args
};

struct cString {
    uint32_t m00, m04, m08, m0c;
    uint8_t  m10, m11, mPad[2];
    cString(uint32_t a, uint32_t b, const wchar_t* c);     // 0x006b5770
    ~cString();                                            // 0x006b5240
    void* GetText();                                       // 0x006b55c0
};

struct cUpdater {
    void BindSlotCreature(void* ids, uint32_t a, const float* rgb,
                          int b, int c, void* win);        // 0x00ae8d00, thiscall, 6 args
    void SwapSlotObjects(int a, int b, int c, int d);      // 0x00ae7e10, thiscall, 4 args
};

extern uint32_t DAT_015b90d8;                              // 0x015b90d8
extern uint32_t DAT_015b9108;                              // 0x015b9108
extern uint8_t  DAT_013ec468;                              // 0x013ec468
extern const float kHalf;                                  // 0x01471064
extern const float kOne;                                   // 0x01485720

// ---------------------------------------------------------------------------
// SP::cSPUISpace
// ---------------------------------------------------------------------------
class cSPUISpace {
public:
    uint8_t        pad00[0x10];
    void*          mpCommandDeleteCargoButtonState;        // +0x10
    uint32_t       mDeleteButtonWindow;                    // +0x14
    uint8_t        pad18[0x224 - 0x18];
    cSPUIGlobalUI* mpGlobalUI;                             // +0x224
    uint8_t        pad228[0x258 - 0x228];
    cSPUILayout*   mpLayout;                               // +0x258
    uint8_t        pad25c[0x5d0 - 0x25c];
    uint8_t        mb5d0;                                  // +0x5d0
    uint8_t        pad5d1[0x694 - 0x5d1];
    cOverlay*      mpOverlay;                              // +0x694

    // helpers (each keeps its original VA annotation for the difftest resolver)
    bool     DoFocusChange(void* target, const void* msg);   // 0x0106fc90
    void     FUN_01066780(void* target, const void* msg);    // 0x01066780
    bool     FUN_01065e20();                                 // 0x01065e20
    uint32_t FUN_01067b60();                                 // 0x01067b60
    void     FUN_010666b0();                                 // 0x010666b0
    void*    FUN_01067ef0(uint32_t arg);                     // 0x01067ef0
    void     FUN_0106f1a0(void* blk, char mode);             // 0x0106f1a0
    uint8_t  FUN_01067fb0();                                 // 0x01067fb0  ToggleSlotsUI
    uint8_t  FUN_01066570();                                 // 0x01066570
    uint8_t  FUN_01068080();                                 // 0x01068080  ToggleMinimapUI
    uint8_t  FUN_01068140();                                 // 0x01068140  UpdateStarMapFilters
    uint8_t  FUN_01068350();                                 // 0x01068350
    uint32_t FUN_01066150(uint32_t id);                      // 0x01066150
    void     FUN_0106e3e0(uint32_t index);                   // 0x0106e3e0  ToggleToolUI
    void     FUN_0106e940(uint32_t index);                   // 0x0106e940
    void     FUN_0106ea40(uint32_t index);                   // 0x0106ea40
    void     FUN_0106f3d0();                                 // 0x0106f3d0
    void     FUN_0106f540();                                 // 0x0106f540
    void     FUN_01066230(int on);                           // 0x01066230
    void     FUN_01071c20(uint32_t state);                   // 0x01071c20  SetupFoodwebWindows

    bool DoMessage(void* target, uint32_t* msg);             // 0x01072d40, ret 8
    void ShowCreatureTooltip(void* arg1, uint32_t arg2);     // 0x010727e0, ret 8
};

}  // namespace SP

using SP::cSPUISpace;
using SP::IWindow;
using SP::Vec3i;

namespace {

typedef uint32_t (__thiscall* FnU0)(void*);
typedef void     (__thiscall* FnV0)(void*);
typedef void     (__thiscall* FnV2)(void*, uint32_t, uint32_t);
typedef void     (__thiscall* FnVP2)(void*, void*, void*);
typedef void     (__thiscall* FnVU1)(void*, uint32_t);
typedef uint32_t (__thiscall* FnRU1)(void*, uint32_t);
typedef void*    (__thiscall* FnPU1)(void*, uint32_t);
typedef void*    (__thiscall* FnObj)(void*);
typedef void     (__thiscall* FnVP2_6)(void*, const void*, void*, int, int, int, int);
typedef void     (__thiscall* FnVP2_1)(void*, const void*);

inline void** Vt(void* p) { return *(void***)p; }

uint32_t VCall0(void* o, uint32_t off) { return ((FnU0)Vt(o)[off / 4])(o); }
uint32_t VCallU1(void* o, uint32_t off, uint32_t a) { return ((FnRU1)Vt(o)[off / 4])(o, a); }
void     VCallV0(void* o, uint32_t off) { ((FnV0)Vt(o)[off / 4])(o); }
void     VCallV2(void* o, uint32_t off, uint32_t a, uint32_t b) {
    ((FnV2)Vt(o)[off / 4])(o, a, b);
}
void     VCallVP2(void* o, uint32_t off, void* a, void* b) {
    ((FnVP2)Vt(o)[off / 4])(o, a, b);
}
void     VCallVP2_1(void* o, uint32_t off, const void* a) { ((FnVP2_1)Vt(o)[off / 4])(o, a); }
void*    VCallP1(void* o, uint32_t off, uint32_t a) { return ((FnPU1)Vt(o)[off / 4])(o, a); }

uint32_t AudioSlot8()
{
    void* at = EA::Audio::GetSystemAT();
    return at ? VCall0(at, 0x20) : 0;
}

inline uint32_t Lu32(const void* p) { return *(const uint32_t*)p; }

}  // namespace

// ---------------------------------------------------------------------------
// @ 0x01072d40  cSPUISpace::DoMessage
// ---------------------------------------------------------------------------
bool cSPUISpace::DoMessage(void* target, uint32_t* msg)
{
    if (msg[3] == DAT_015b90d8)
        return false;

    void* win = (void*)VCall0(target, 0x1c);

    if (msg[2] == 10)
        return DoFocusChange(target, msg);

    if (msg[2] == 7 && (VCall0(target, 0x28) & 2) == 0)
        RecordEvent2(0x566853b1u, AudioSlot8());

    if (msg[2] == 2 && (msg[4] == 0x1b || msg[4] == 0xd)) {
        IWindow* w = mpGlobalUI->FindWindowByID(0x664c270);
        if (w && (VCall0(w, 0x28) & 1)) {
            VCallV2(w, 0x7c, 1, 0);
            return true;
        }
    }

    FUN_01066780(target, msg);

    uint32_t id = msg[3];

    if (id == 0x3e1a6a5u) {
        RecordEvent2(0x399e11fbu, AudioSlot8());
        if (VCall0(target, 0x1c) != 0xffffffffu)
            return false;
        if (msg[2] != 0x287259f6u)
            return false;
        if (mpCommandDeleteCargoButtonState != 0)
            return true;

        void* pObj = operator_new(0x1c, "Simulator", 0, 0, 0, 0);
        if (pObj)
            pObj = ((SP::cCommandDeleteCargoButtonState*)pObj)->Ctor(this, mDeleteButtonWindow);
        else
            pObj = 0;
        mpCommandDeleteCargoButtonState = pObj;

        IWindow* w = mpGlobalUI->FindWindowByID(0xffffffffu);
        AutoRefCount_Ctor(w);

        uint32_t k[4];
        k[2] = 0x410812au;
        k[3] = 0x410812au;

        void* wm = WindowManager();
        VCallVP2(wm, 0x10, win, k);
        if (win)
            VCallV0(win, 4);
        return true;
    }

    if (id == 0x2e1b720u || id == 0x2e1b6f8u || id == 0x2e1b708u ||
        id == 0x2e1cbd7u || id == 0x2e1b72cu || id == 0x2e1b73cu) {
        RecordEvent2(0xb2a58920u, GetRecorderState());
        IWindow* w = mpGlobalUI->FindWindowByID(id);
        if (w == 0)
            return true;
        void* button = interface_cast_IWinButton(w);
        if (button == 0)
            return true;
        uint32_t filter = convertStarMapButtonToFilter(id);
        cStarMap* sm = (cStarMap*)FUN_01046fc0();
        if (VCall0(button, 0x20) & 4)
            sm->FilterHelper(filter, 1);
        if ((VCall0(button, 0x20) & 4) == 0)
            sm->FilterHelper(filter, 0);
        FUN_010666b0();
        return true;
    }

    if (id == 0x2c38abau) {
        ((cFloatOwner*)FUN_01015df0())->FUN_01015f30(0.0f);
        return true;
    }
    if (id == 0x2699440u) {
        FUN_00e02c40();
        return true;
    }
    if (id == 0x17f29bfu) {
        if (FUN_01065e20())
            return false;
        return FUN_01067b60() != 0;
    }

    if (id == 0x37ab944u) {
        if (msg[2] != 0x287259f6u)
            return true;
        if (GetUniverseContext() != 0)
            return true;
        void* input = GameInputManager();
        ((FnV2)Vt(input)[0x64 / 4])(input, 0x37ab944u, 1);
        void* cursor = GetGameTerrainCursor();
        VCallV0(cursor, 0x64);
        return true;
    }

    if (id == 0x37e9018u) {
        if (msg[2] != 0x287259f6u)
            return true;

        void* blk = FUN_01067ef0((uint32_t)win);
        uint32_t mode = *(uint32_t*)((uint8_t*)blk + 0x18);
        if (mode != 0) {
            if (mode != 3)
                return true;
            FUN_0106f1a0(blk, 1);
            return true;
        }

        uint8_t bOld = (*(uint32_t*)((uint8_t*)blk + 0x10) == 0);
        Vec3i tmp;
        cTerraform* tm = (cTerraform*)TerraformingManager();
        Vec3i* src = (Vec3i*)(bOld ? tm->GetOld(&tmp) : tm->GetNew(&tmp));
        Vec3i cur;
        cur.mX = src->mX;
        cur.mY = src->mY;
        cur.mZ = src->mZ;
        Vec3i here = *(Vec3i*)((uint8_t*)blk + 4);

        if (FUN_004eb930(&cur, &here)) {
            ((cTerraform*)TerraformingManager())->StoreEmpty();
            RecordEvent2(0x53eca8bdu, GetRecorderState());
            return true;
        }
        if (bOld)
            ((cTerraform*)TerraformingManager())->Store3((int)here.mX, (int)here.mY, (int)here.mZ);
        else
            ((cTerraform*)TerraformingManager())->Store3B((int)here.mX, (int)here.mY, (int)here.mZ);
        RecordEvent2(0x3c7c63bcu, GetRecorderState());
        return true;
    }

    if (id == 0x447060au) {
        ShowContextSensitiveSporeGuide();
        return true;
    }

    if (id == 0x410812au) {
        if (VCall0(target, 0x1c) != 0xffffffffu)
            return false;
        if (FUN_01066570()) {
            IWindow* w = mpGlobalUI->FindWindowByID(0xffffffffu);
            AutoRefCount_Ctor(w);
            uint32_t k[4];
            k[0] = 0x410812au;
            k[1] = 0x410812au;
            void* wm = WindowManager();
            VCallVP2(wm, 0x18, win, k);
            goto shared_tail;
        }
        if (mpCommandDeleteCargoButtonState != 0)
            VCallU1(mpCommandDeleteCargoButtonState, 8, 1);
        mpCommandDeleteCargoButtonState = 0;
        return true;
    }

    if (id == 0x4359752u) {
        if (msg[2] != 0x287259f6u)
            return true;
        mb5d0 = (msg[5] != 0) ? 1 : 0;
        FUN_01067fb0();
        RecordEvent2(0xefaaa0c7u, GetRecorderState());
        return true;
    }

    if (id == 0x5232c00u) {
        if (msg[2] != 0x18)
            return true;
        void* button = interface_cast_IWinButton((void*)msg[0]);
        if (button == 0)
            return true;
        uint32_t flags = VCall0(button, 0x20);
        VCallV2(button, 0x28, 4, ((flags >> 2) & 1) == 0 ? 1 : 0);
        return true;
    }

    if (id == 0x562a141u) {
        if (msg[2] != 0x287259f6u)
            return false;
        uint8_t b = FUN_01068080();
        RecordEvent2(0x98b8139du + (b ? 0x6c491d1au : 0), GetRecorderState());
        return true;
    }

    if (id == 0x65680e8u || id == 0x65ce2da) {
        if (msg[2] != 0x287259f6u)
            return true;
        if (FUN_00b18e40(SpaceGameGet()))
            return true;
        if (FUN_00ffc0c0(GetUFOSimulator()))
            return true;

        void* avatarMgr = FUN_01021240();
        void* vec = VCallP1(avatarMgr, 0x00bba790, 0);
        uint32_t* begin = *(uint32_t**)vec;
        uint32_t* end   = *((uint32_t**)vec + 1);
        void* found = 0;
        int count = (int)(end - begin);
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                void* o = (void*)begin[i];
                uint32_t s = *(uint32_t*)((uint8_t*)o + 0x28);
                if (s == 1 || s == 0)
                    continue;
                if (FUN_00b8d970(o))
                    continue;
                if (FUN_00b8dab0(o) == 5) {
                    found = o;
                    break;
                }
            }
        }
        if (!found)
            return true;

        void* game = FUN_01021240();
        uint32_t avatarId = (uint32_t)((FnObj)Vt(game)[0x00b1fdb0 / 4])(game);
        void* empire = ((cStarManagerAccess*)StarManager())->GetEmpireByID(avatarId);
        uint32_t empireId = *(uint32_t*)((uint8_t*)empire + 0x84);
        void* ctxObj = FUN_010212a0();
        uint32_t ctx = ((cCommContext*)ctxObj)->GetCommContext();

        if (id == 0x65680e8u) {
            CommAdd(empireId, ctx, 0xc8fbf7d7u, 0x934c7dd1u, 0, 0);
        } else {
            CommRemove(empireId, ctx, 0x95bbbbfcu, 0xdd33319cu);
            void* e2 = ((cStarManagerAccess*)StarManager())->GetEmpireByID(avatarId);
            uint32_t id2 = *(uint32_t*)((uint8_t*)e2 + 0x84);
            void* c2 = FUN_010212a0();
            uint32_t ctx2 = ((cCommContext*)c2)->GetCommContext();
            CommAdd(id2, ctx2, 0xc8fbf7d7u, 0xd2a61d3u, 0, 0);
        }
        return true;
    }

    if (id == 0x674c4d0u) {
        if (msg[2] == 0x287259f6u) {
            IWindow* w = mpGlobalUI->FindWindowByID(0x664c270);
            if (w)
                VCallV2(w, 0x7c, 1, 0);
        }
        return true;
    }

    if (id == 0x7bb7790u) {
        void* tm = GameTimeManager();
        if ((Lu32((uint8_t*)tm + 0x48) & 1) && !FUN_01068350()) {
            ForwardWindowMessage_7590(4, 0);
        } else {
            void* o = FUN_00b3d3f0();
            if (VCallU1(o, 0x00e18c70, 0)) {
                o = FUN_00b3d3f0();
                ((FnVU1)Vt(o)[0x00e190c0 / 4])(o, 0);
            }
        }
        if (FUN_01068350()) {
            VCallV0(mpOverlay, 0x00fe7e10);
            FUN_0106f540();
        } else {
            ((cOverlay*)mpOverlay)->Hide(1);
            ShowCreatureTooltip(0, 0);
        }
        goto shared_tail;
    }

    if (id == 0x453ef531u) {
        if (msg[2] != 0x287259f6u)
            return false;
        uint8_t b = FUN_01068140();
        RecordEvent2(0x98b8139du + (b ? 0x6c491d1au : 0), GetRecorderState());
        return true;
    }

    if (id == 0x505a4528u)
        return true;

    if (msg[2] != 0x287259f6u)
        return false;
    {
        uint32_t r = FUN_01066150(id);
        if (r == 0)
            goto shared_tail;
        FUN_0106e3e0(r);
        RecordEvent2(0xefaaa0c7u, GetRecorderState());
        return true;
    }

shared_tail:
    if (msg[2] != 0x287259f6u)
        return false;
    win = (void*)msg[0];
    if (win == 0)
        return false;
    {
        uint32_t sub = VCall0(win, 0x20);
        if (sub == 0x447b980u || sub == 0x447b981u || sub == 0x447b982u) {
            FUN_0106ea40(sub - 0x447b980u);
            return false;
        }
        if (sub == 0x447b968u || sub == 0x447b969u || sub == 0x447b96au) {
            FUN_0106e940(sub - 0x447b968u);
            return false;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x010727e0  cSPUISpace::ShowCreatureTooltip
// ---------------------------------------------------------------------------
void cSPUISpace::ShowCreatureTooltip(void* arg1, uint32_t arg2)
{
    void* game = SpaceGameGet();
    void* spaceUI = game ? *(void**)((uint8_t*)game + 0x14) : 0;

    IWindow* w = ((cSPUISpace*)spaceUI)->mpGlobalUI->FindWindowByID(0x5e66e88);
    if (w) {
        mpLayout->SetParentWin(0, 1, 0x5b598fa);
        mpLayout->SetParentWin(w, 1, 0x5b598fa);
    }
    w = mpLayout->FindWindowByID(0x755f180, 1);
    if (w)
        VCallV2(w, 0x7c, 1, 1);

    cEmpire* empire = (cEmpire*)GetPlayerEmpire();
    Vec3i ids = *empire->GetIds();

    // foodweb key (used by the SetupFoodwebWindows call and the tooltip lookup)
    uint32_t state = 0;
    cSimulator* sim = (cSimulator*)GetUFOSimulator();
    cInventory* inv = sim->GetPlayerInventory();
    if (inv->mp75c)
        state = inv->mp75c->mpStar->GetState();

    uint32_t foodwebKey[3];
    foodwebKey[0] = state;
    foodwebKey[1] = 0x366a930du;
    foodwebKey[2] = DAT_015b9108;

    FUN_01071c20(state);

    if (*(uint8_t*)arg1 != 0) {
        if (arg2 == 0x7ce1750u)
            ((cOverlay*)mpOverlay)->SetMode(0);
        else if (arg2 == 0x7ce3cb0u)
            ((cOverlay*)mpOverlay)->SetMode(2);
    } else if (((cOverlay*)mpOverlay)->Test()) {
        ((cOverlay*)mpOverlay)->SetMode(0);
    } else {
        // asset lookup for this creature
        uint32_t iconKey[3];
        iconKey[0] = ids.mX;
        iconKey[1] = 0x30bdee3u;
        iconKey[2] = DAT_015b9108;

        void* res = 0;
        void* mgr = GetResourceManager();
        ((FnVP2_6)Vt(mgr)[0xc / 4])(mgr, iconKey, &res, 0, 0, 0, 0);
        if (res) {
            void* asset = VCallP1(res, 0xc, 0x30bdee3u);
            if (asset) {
                ((FnU0)Vt(asset)[0])(asset);
                const wchar_t* name = ((cAsset*)asset)->GetName();
                const wchar_t* summary = ((cAsset*)asset)->GetSummary();
                w = mpLayout->FindWindowByID(0x75608a4, 1);
                if (w) {
                    VCallV2(w, 0x7c, 1, 1);
                    VCallVP2_1(w, 0x80, (void*)summary);
                }
                w = mpLayout->FindWindowByID(0x76b68d2, 1);
                if (w) {
                    VCallV2(w, 0x7c, 1, 1);
                    VCallVP2_1(w, 0x80, (void*)name);
                }
            }
            w = mpLayout->FindWindowByID(0x7c7c590, 1);
            if (w) {
                if (FUN_00eed840(&ids)) {
                    cString tip(0x3dade1bbu, 0x7ec9f8cu, 0);
                    VCallVP2_1(w, 0x80, tip.GetText());
                    VCallV2(w, 0x7c, 1, 1);
                } else if (FUN_00eed970(&ids, foodwebKey)) {
                    cString tip(0x3dade1bbu, 0x7ec9f8bu, 0);
                    VCallVP2_1(w, 0x80, tip.GetText());
                    VCallV2(w, 0x7c, 1, 1);
                } else {
                    VCallV2(w, 0x7c, 1, 0);
                }
            }
            uint32_t imgKey[3];
            imgKey[0] = ids.mX;
            imgKey[1] = 0x2f7d0004u;
            imgKey[2] = DAT_015b9108;

            w = mpLayout->FindWindowByID(0x756083b, 1);
            if (w) {
                if (FUN_0106b7e0(w, imgKey)) {
                    float* area = (float*)VCall0(w, 0x38);
                    float x0 = area[0], y0 = area[1];
                    float x1 = area[2], y1 = area[3];
                    float cx = (x0 + x1) * kHalf;
                    float cy = (y0 + y1) * kHalf;
                    float ww = x1 - x0;
                    float hh = y1 - y0;
                    float rad = (ww > hh ? hh : ww) * kHalf;
                    float rect[4] = { cx - rad, cy - rad, cx + rad, cy + rad };
                    VCallVP2_1(w, 0x6c, rect);
                }
            }
            ((cOverlay*)mpOverlay)->SetMode(1);
            VCallV0(res, 4);
        }
    }

    void* game2 = SpaceGameGet();
    void* spaceUI2 = game2 ? *(void**)((uint8_t*)game2 + 0x14) : 0;
    ((cInputMgr*)GameInputManager())->mCounter++;
    void* wm = WindowManager();
    void* modal = ((FnObj)Vt(wm)[4 / 4])(wm);
    if (modal && (uint8_t*)modal - 4 != 0)
        FUN_00812d80((uint8_t*)modal - 4, 1);
    ((cSPUISpace*)spaceUI2)->FUN_01066230(1);

    w = mpLayout->FindWindowByID(0x7551618, 1);
    if (w) {
        float rgb[3] = { kOne, kOne, kOne };
        ((cUpdater*)GetUpdater490())->BindSlotCreature(&ids, 0x4d594c50u, rgb, 0, 0, w);
        ((cUpdater*)GetUpdater490())->SwapSlotObjects(1, 0, 0, 0);
    }

    Vec3i ids2 = *((cEmpire*)GetPlayerEmpire())->GetIds();
    if (((cSpeciesMgr*)GetSpeciesManager())->GetProfile(&ids2)) {
        for (uint32_t id = 0x7746f28u; id <= 0x7746f33u; id++) {
            w = mpLayout->FindWindowByID(id, 1);
            if (w)
                SetTooltipText(w, &DAT_013ec468, -1, 1);
        }
    }

    cEmpire* empire2 = (cEmpire*)GetPlayerEmpire();
    w = mpLayout->FindWindowByID(0x5edff88, 1);
    if (w) {
        void* keyObj = GetGlobalImageKey(empire2, 0);
        IWindow* image = ((cImageKey*)keyObj)->FUN_00dd2320(empire2, 0);
        SetImageFromKey(w, image);
    }
    w = mpLayout->FindWindowByID(0x6243260, 1);
    if (w) {
        uint8_t color[12];
        empire2->GetColor(color);
        VCallU1(w, 0xac, ColorRGBToU32(color));
    }

    void* gtm = GameTimeManager();
    ((FnVU1)Vt(gtm)[0x00b32220 / 4])(gtm, 0x7e9e4b7u);
    FUN_0106f3d0();
}
