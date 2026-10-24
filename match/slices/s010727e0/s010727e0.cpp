// Slice s010727e0 (batch hk1): SP::cSPUISpace::DoMessage, 0x01072d40, 2481 bytes.
//
// PARTIAL. Implemented from the asm/decompile card: the entry check, the type-10 focus path,
// the type-7 audio path, the type-2 Esc/Enter path, the FUN_01066780 call, the 0x3e1a6a5
// pie-window path, the 0x2c38aba and 0x2699440 leaves, and the 0x2e1b720 family (star-map
// filter toggle). The remaining id leaves (0x2e1cbd7 range, 0x37ab944, 0x37e9018, the
// 0x453ef531/0x505a4528/0x287259f6 family, the terraform block, the comm paths 0x65680e8 and
// 0x65ce2da) and the shared tail at 0x01073599 are NOT reproduced; the function returns false
// for them, so this is not a complete implementation.
//
// Calling conventions (from call sites): `mov ecx,...` before a call = thiscall; no `add esp`
// after the call = callee pops (ret N).

#include "types.h"

namespace EA {
namespace Audio {
void* GetSystemAT();                                   // cdecl, no args
}
}

uint32_t GetRecorderState();                            // 0x00435e90, cdecl, no args
void*    WindowManager();                               // 0x0067caa0, cdecl, no args
void*    interface_cast_IWinButton(void* window);       // 0x005ca960, cdecl, 1 arg
uint32_t convertStarMapButtonToFilter(uint32_t id);     // 0x010659c0, cdecl, 1 arg
void     FUN_00e02c40();                                // 0x00e02c40, cdecl, no args
void*    FUN_01046fc0();                                // 0x01046fc0, getter, no args
void*    FUN_01015df0(uint32_t value);                  // 0x01015df0, stdcall, 1 arg (callee pops)
void*    operator_new_0x1c(uint32_t size, const char* name, uint32_t a, uint32_t b, uint32_t c, uint32_t d);
                                                        // 0x00f473a0 operator new, cdecl, 6 args

uint32_t GetPlayerEmpireId();                           // 0x01021090, cdecl, no args
void*    SpaceGameGet();                                // 0x01002bd0, cdecl, no args
void*    GetUFOSimulator();                             // 0x00ffbe50, cdecl, no args
void*    GetPlayerEmpire();                             // 0x01021300, cdecl, no args
void*    GameInputManager();                            // 0x00b3d250, cdecl, no args
void*    GameTimeManager();                             // 0x00b3d380, cdecl, no args
void*    GetResourceManager();                          // 0x0067dcd0, cdecl, no args
void*    GetUpdater490();                               // 0x00b3d490, cdecl, no args
void*    GetSpeciesManager();                           // 0x00401090, getter, no args
void*    GetGlobalImageKey(void* empire, int a);        // 0x00dd1ca0, ignores args
void     FUN_00812d80(int on);                          // 0x00812d80, stdcall, 1 arg
void     FUN_00fe76d0(void* self, int mode);            // 0x00fe76d0, thiscall, 1 arg
void     FUN_01071c20(void* self, uint32_t state);      // 0x01071c20, thiscall, 1 arg
uint8_t  FUN_00ffc0c0(void* self);                      // 0x00ffc0c0, thiscall, no args
uint8_t  FUN_00eed840(const void* key);                 // 0x00eed840, cdecl, 1 arg
uint8_t  FUN_00eed970(const void* a, const void* b);    // 0x00eed970, cdecl, 2 args
void*    FUN_00c30f90(void* empire);                    // 0x00c30f90, thiscall, no args
void*    FUN_0106b7e0(void* self, void* key);           // 0x0106b7e0, thiscall, 1 arg
void     SetImageFromKey(void* win, void* key);         // 0x00e2f5c0, cdecl, 2 args
uint32_t ColorRGBToU32(void* color);                    // 0x00458a40, cdecl, 1 arg
void     SetTooltipText(void* win, void* text, int a, int b);  // 0x00806de0, cdecl, 4 args
uint32_t IncPauseGate(void* mgr, uint32_t id);          // 0x00b32220, thiscall, 1 arg
void     GetEmpireColor(void* empire, void* out);       // 0x00c32cd0, thiscall, 1 arg
void*    GetAssetName(void* asset);                     // 0x00414e10, thiscall, no args
void*    GetAssetSummary(void* asset);                  // 0x005508c0, thiscall, no args
void     FUN_00dd2320(void* self, void* empire);        // 0x00dd2320, thiscall, 1 arg

namespace SP {

struct Vec3i { uint32_t mX, mY, mZ; };

struct cLayout {
    void* FindWindowByID(uint32_t id, int recurse);         // 0x008105b0, thiscall, 2 args
    void  SetParentWin(void* child, int a, uint32_t id);    // 0x008121b0, thiscall, 3 args
};

struct cSPUIGlobalUI {
    void* FindWindowByID(uint32_t id);                  // 0x00e012b0, thiscall, 1 arg
};

struct cCommandDeleteCargoButtonState {
    void* Ctor(void* owner, uint32_t window);           // 0x010665c0, thiscall, 2 args; returns this
};

class cStarMap { public:
    void FilterHelper(uint32_t filter, uint32_t on);    // 0x01048b40, thiscall, 2 args
};

struct cFloatOwner {
    void FUN_01015f30(uint32_t value);                  // 0x01015f30, thiscall, 1 arg
};

class cSPUISpace { public:
    uint8_t  pad00[0x10];
    void*    mpCommandDeleteCargoButtonState;           // +0x10
    uint32_t mDeleteButtonWindow;                       // +0x14
    uint8_t  pad18[0x224 - 0x18];
    cSPUIGlobalUI* mpGlobalUI;                          // +0x224
    uint8_t  pad228[0x258 - 0x228];
    cLayout* mpLayout;                                  // +0x258
    uint8_t  pad25c[0x694 - 0x25c];
    void*    mpOverlay694;                              // +0x694 (loaded, not used in this partial)

    static void KillSetiEffects(uint32_t id, uint32_t state);  // 0x00435ed0, cdecl, 2 args

    void     FUN_010727e0(void* param_2, uint32_t param_3); // 0x010727e0, thiscall, 2 args, ret 8
    void     FUN_01066230(int on);                      // 0x01066230, thiscall, 1 arg
    void     FUN_0106b7e0(void* win, void* key);        // 0x0106b7e0, thiscall, 2 args
    void     FUN_0106f3d0();                            // 0x0106f3d0, thiscall, no args
    bool     DoMessage(void* param_2, uint32_t* msg);   // 0x01072d40, thiscall, 2 args, ret 8
    bool     DoFocusChange(void* param_2, uint32_t* msg);  // 0x0106fc90, thiscall, 2 args
    void     FUN_01066780(void* param_2, uint32_t* msg);   // 0x01066780, thiscall, 2 args
    bool     FUN_01065e20();                            // 0x01065e20, thiscall, no args
    uint32_t FUN_01067b60();                            // 0x01067b60, thiscall, no args
    void     FUN_010666b0();                            // 0x010666b0, thiscall, no args
};

}  // namespace SP

using SP::cSPUISpace;

namespace {

// Virtual call: `this` in ECX, slot at byte offset `off` of the vtable.
typedef uint32_t (__thiscall* FnRet0)(void*);
typedef void     (__thiscall* FnVoid0)(void*);
typedef void     (__thiscall* FnVoid3)(void*, void*, void*, uint32_t);
typedef void     (__thiscall* FnVoidVA)(void*, uint32_t, uint32_t);

inline void** VTable(void* p) { return *(void***)p; }

inline uint32_t VCallRet(void* obj, uint32_t off) {
    return ((FnRet0)VTable(obj)[off / 4])(obj);
}
inline void VCallVoid(void* obj, uint32_t off) {
    ((FnVoid0)VTable(obj)[off / 4])(obj);
}
inline void VCallVoidArgs(void* obj, uint32_t off, uint32_t a, uint32_t b) {
    ((FnVoidVA)VTable(obj)[off / 4])(obj, a, b);
}

// Audio: slot 8 (0x20) of the system audio object, or 0 when absent.
uint32_t AudioSlot8() {
    void* at = EA::Audio::GetSystemAT();
    if (at) return VCallRet(at, 0x20);
    return 0;
}

// Msg key for the pie-window path: 16 bytes; the two leading words are not initialized in the
// original (see the card), and the two trailing words hold the terraform key 0x410812a.
struct PieKey {
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
};

}  // namespace

namespace SP {

// @ 0x01072d40
bool cSPUISpace::DoMessage(void* param_2, uint32_t* msg)
{
    if (msg[3] == *(uint32_t*)0x015b90d8) {
        return false;
    }
    void* piVar3 = (void*)VCallRet(param_2, 0x1c);

    if (msg[2] == 10) {
        return DoFocusChange(param_2, msg);
    }
    if (msg[2] == 7 && (VCallRet(param_2, 0x28) & 2) == 0) {
        KillSetiEffects(0x566853b1u, AudioSlot8());
    }
    if (msg[2] == 2 && (msg[4] == 0x1b || msg[4] == 0xd)) {
        void* w = mpGlobalUI->FindWindowByID(0x664c270);
        if (VCallRet(w, 0x28) & 1) {
            VCallVoidArgs(w, 0x7c, 1, 0);
            return true;
        }
    }
    FUN_01066780(param_2, msg);

    uint32_t id = msg[3];

    if (id == 0x3e1a6a5u) {
        KillSetiEffects(0x399e11fbu, AudioSlot8());
        if (VCallRet(param_2, 0x1c) != 0xffffffffu) {
            return false;
        }
        if (msg[2] != 0x287259f6u) {
            return false;
        }
        if (mpCommandDeleteCargoButtonState != 0) {
            return true;
        }
        void* obj = operator_new_0x1c(0x1c, "Simulator", 0, 0, 0, 0);
        void* cmd = 0;
        if (obj) {
            cmd = static_cast<SP::cCommandDeleteCargoButtonState*>(obj)->Ctor(this, mDeleteButtonWindow);
        }
        mpCommandDeleteCargoButtonState = cmd;
        void* w = mpGlobalUI->FindWindowByID(0xffffffffu);
        (void)w;  // FUN_00572660(w): ARC constructor on the window reference; not reproduced yet.
        PieKey key;
        key.a = 0;
        key.b = 0;
        key.c = 0x410812au;
        key.d = 0x410812au;
        void* wm = WindowManager();
        ((FnVoid3)VTable(wm)[0x10 / 4])(wm, param_2, piVar3, 0);
        (void)key;
        if (piVar3 != 0) {
            VCallVoid(piVar3, 4);
        }
        return true;
    }

    switch (id) {
    case 0x2c38abau: {
        void* owner = FUN_01015df0(0);
        static_cast<cFloatOwner*>(owner)->FUN_01015f30(0);
        return true;
    }
    case 0x2699440u:
        FUN_00e02c40();
        return true;
    case 0x2e1b720u:
    case 0x2e1b6f8u:
    case 0x2e1b708u:
    case 0x2e1cbd7u:
    case 0x2e1b72cu:
    case 0x2e1b73cu: {
        uint32_t recorderState = GetRecorderState();
        KillSetiEffects(0xb2a58920u, recorderState);
        void* window = mpGlobalUI->FindWindowByID(id);
        if (window == 0) {
            return true;
        }
        void* button = interface_cast_IWinButton(window);
        if (button == 0) {
            return true;
        }
        uint32_t filter = convertStarMapButtonToFilter(id);
        if (VCallRet(button, 0x20) & 4) {
            static_cast<cStarMap*>(FUN_01046fc0())->FilterHelper(filter, 1);
        }
        if ((VCallRet(button, 0x20) & 4) == 0) {
            static_cast<cStarMap*>(FUN_01046fc0())->FilterHelper(filter, 0);
        }
        FUN_010666b0();
        return true;
    }
    default:
        break;
    }

    // Not reproduced: the remaining id leaves and the shared tail at 0x01073599.
    return false;
}

// ---------------------------------------------------------------------------
// 0x010727e0  creature tooltip / slot-bar refresh
// ---------------------------------------------------------------------------
namespace {

typedef void  (__thiscall *FnV2i)(void*, int, int);
typedef void  (__thiscall *FnV1p)(void*, const void*);
typedef float*(__thiscall *FnArea)(void*);
typedef void  (__thiscall *FnV1f4)(void*, const float*);
typedef void  (__thiscall *FnV1u)(void*, uint32_t);
typedef void* (__thiscall *FnObj)(void*);
typedef void  (__thiscall *FnV0)(void*);
typedef void* (__thiscall *FnP1u)(void*, uint32_t);
typedef void  (__thiscall *FnV6)(void*, const void*, void**,
                                 int, int, int, int);

inline void** SlotTable(void* o) { return *(void***)o; }
inline void*  Slot(void* o, uint32_t off) { return SlotTable(o)[off / 4]; }

inline void  WinSetVisible(void* w, int a, int b) { ((FnV2i)Slot(w, 0x7c))(w, a, b); }
inline void  WinSetText(void* w, const void* t) { ((FnV1p)Slot(w, 0x80))(w, t); }
inline float* WinGetArea(void* w) { return ((FnArea)Slot(w, 0x38))(w); }
inline void  WinSetArea(void* w, const float* r) { ((FnV1f4)Slot(w, 0x6c))(w, r); }
inline void  WinSetColor(void* w, uint32_t c) { ((FnV1u)Slot(w, 0xac))(w, c); }
inline void  RefRelease(void* o) { ((FnV0)Slot(o, 4))(o); }
inline void  ObjV00(void* o) { ((FnV0)Slot(o, 0))(o); }

}  // namespace

struct Key { uint32_t mA, mB, mC; };

struct cSpaceGame {
    uint8_t      pad00[0x14];
    cSPUISpace*  mpSpaceUI;                 // +0x14
};

struct cOverlay {
    void    SetMode(int mode);              // 0x00fe76d0
    uint8_t Test();                         // 0x00ffc0c0
};

struct cKeyObj {
    void SetState(uint32_t state);          // 0x01071c20
};

struct cStarAccess {
    uint32_t GetState();                    // 0x00b8d9b0
};

struct cInvSub {
    uint8_t      pad00[0x13c];
    cStarAccess* mpStar;                    // +0x13c
};

struct cInventory {
    uint8_t   pad00[0x75c];
    cInvSub*  mp75c;                        // +0x75c
};

struct cSimulator {
    cInventory* GetPlayerInventory();       // 0x00a1ad60
};

struct cInputMgr {
    uint8_t  pad00[0x110];
    uint32_t mCounter;                      // +0x110
};

struct cEmpireObj {
    Vec3i* GetIds();                        // 0x00c30f90
    void   GetColor(void* out);             // 0x00c32cd0
};

struct cSpeciesMgr {
    void* GetProfile(const void* key);      // 0x004df550
};

struct cImageKey {
    void* FUN_00dd2320(void* empire);       // 0x00dd2320
};

struct cGameTimeMgr {
    uint32_t IncPauseGate(uint32_t id);     // 0x00b32220
};

struct cUpdater {
    void BindSlotCreature(void* scenario, uint32_t a, const float* pos,
                          void* data, int b, void* win);   // 0x00ae8d00
    void SwapSlotObjects(void* a, void* b, int slot, int flag); // 0x00ae7e10
};

struct cAsset {
    const wchar_t* GetName();               // 0x00414e10
    const wchar_t* GetSummary();            // 0x005508c0
};

struct cString {
    uint32_t m00, m04, m08, m0c;
    uint8_t  m10, m11, mPad[2];
    cString(uint32_t a, uint32_t b, const wchar_t* c);  // 0x006b5770
    ~cString();                                          // 0x006b5240
    void* GetText();                                     // 0x006b55c0
};

extern uint32_t DAT_015b9108;                   // 0x015b9108
extern uint8_t  DAT_013ec468;                   // 0x013ec468
extern const float kHalf;                       // 0x01471064
extern const float kOne;                        // 0x01485720

// @ 0x010727e0
void cSPUISpace::FUN_010727e0(void* param_2, uint32_t param_3)
{
    cSpaceGame* game = (cSpaceGame*)SpaceGameGet();
    cSPUISpace* space = game ? game->mpSpaceUI : 0;
    void* win = space->mpGlobalUI->FindWindowByID(0x5e66e88);
    if (win) {
        mpLayout->SetParentWin(0, 1, 0x5b598fa);
        mpLayout->SetParentWin(win, 1, 0x5b598fa);
    }
    win = mpLayout->FindWindowByID(0x755f180, 1);
    if (win)
        WinSetVisible(win, 1, 1);

    cEmpireObj* empire = (cEmpireObj*)GetPlayerEmpire();
    Vec3i ids = *empire->GetIds();

    uint32_t state = 0;
    cSimulator* sim = (cSimulator*)GetUFOSimulator();
    cInventory* inv = sim->GetPlayerInventory();
    if (inv->mp75c)
        state = inv->mp75c->mpStar->GetState();

    Key key  = { state,   0x366a930d, DAT_015b9108 };
    Key key2 = { ids.mX,  0x30bdee3,  DAT_015b9108 };
    ((cKeyObj*)this)->SetState(state);

    if (*(uint8_t*)param_2 != 0) {
        if (param_3 == 0x7ce1750)
            ((cOverlay*)mpOverlay694)->SetMode(0);
        else if (param_3 == 0x7ce3cb0)
            ((cOverlay*)mpOverlay694)->SetMode(2);
    } else if (((cOverlay*)mpOverlay694)->Test()) {
        ((cOverlay*)mpOverlay694)->SetMode(0);
    } else {
        void* ref = 0;
        void* mgr = GetResourceManager();
        if (ref)
            RefRelease(ref);
        ((FnV6)Slot(mgr, 0xc))(mgr, &key2, &ref, 0, 0, 0, 0);
        if (ref) {
            void* asset = ((FnP1u)Slot(ref, 0xc))(ref, 0x30bdee3);
            if (asset) {
                ObjV00(asset);
                const wchar_t* name = ((cAsset*)asset)->GetName();
                const wchar_t* summary = ((cAsset*)asset)->GetSummary();
                win = mpLayout->FindWindowByID(0x75608a4, 1);
                if (win) {
                    WinSetVisible(win, 1, 1);
                    WinSetText(win, summary);
                }
                win = mpLayout->FindWindowByID(0x76b68d2, 1);
                if (win) {
                    WinSetVisible(win, 1, 1);
                    WinSetText(win, name);
                }
            }
            win = mpLayout->FindWindowByID(0x7c7c590, 1);
            if (win) {
                if (FUN_00eed840(&ids)) {
                    cString tip(0x3dade1bb, 0x7ec9f8c, 0);
                    WinSetText(win, tip.GetText());
                    WinSetVisible(win, 1, 1);
                } else if (FUN_00eed970(&ids, &key)) {
                    cString tip(0x3dade1bb, 0x7ec9f8b, 0);
                    WinSetText(win, tip.GetText());
                    WinSetVisible(win, 1, 1);
                } else {
                    WinSetVisible(win, 1, 0);
                }
            }
            Key iconKey = { ids.mX, 0x2f7d0004, DAT_015b9108 };
            win = mpLayout->FindWindowByID(0x756083b, 1);
            if (win) {
                FUN_0106b7e0(win, &iconKey);
                float* area = WinGetArea(win);
                float x0 = area[0], y0 = area[1];
                float x1 = area[2], y1 = area[3];
                float cx = (x0 + x1) * kHalf;
                float cy = (y0 + y1) * kHalf;
                float wdt = x1 - x0;
                float hgt = y1 - y0;
                float rad = (wdt > hgt ? hgt : wdt) * kHalf;
                float rect[4] = { cx - rad, cy - rad, cx + rad, cy + rad };
                WinSetArea(win, rect);
            }
            ((cOverlay*)mpOverlay694)->SetMode(1);
            RefRelease(ref);
        }
    }

    cSpaceGame* game2 = (cSpaceGame*)SpaceGameGet();
    cSPUISpace* space2 = game2 ? game2->mpSpaceUI : 0;
    ((cInputMgr*)GameInputManager())->mCounter++;
    void* wm = WindowManager();
    void* modal = ((FnObj)Slot(wm, 4))(wm);
    if (modal && modal != (void*)4)
        FUN_00812d80(1);
    space2->FUN_01066230(1);

    win = mpLayout->FindWindowByID(0x7551618, 1);
    if (win) {
        float rgb[3] = { kOne, kOne, kOne };
        ((cUpdater*)GetUpdater490())->BindSlotCreature(&ids, 0x4d594c50, rgb, 0, 0, win);
        ((cUpdater*)GetUpdater490())->SwapSlotObjects(0, 0, 0, 1);
    }

    empire = (cEmpireObj*)GetPlayerEmpire();
    Vec3i* ids2 = empire->GetIds();
    cSpeciesMgr* species = (cSpeciesMgr*)GetSpeciesManager();
    if (species->GetProfile(ids2)) {
        for (uint32_t id = 0x7746f28; id <= 0x7746f33; id++) {
            void* w = mpLayout->FindWindowByID(id, 1);
            if (w)
                SetTooltipText(w, &DAT_013ec468, -1, 1);
        }
    }

    empire = (cEmpireObj*)GetPlayerEmpire();
    win = mpLayout->FindWindowByID(0x5edff88, 1);
    if (win) {
        void* keyObj = GetGlobalImageKey(empire, 0);
        void* image = ((cImageKey*)keyObj)->FUN_00dd2320(empire);
        SetImageFromKey(win, image);
    }
    win = mpLayout->FindWindowByID(0x6243260, 1);
    if (win) {
        uint8_t color[12];
        empire->GetColor(color);
        WinSetColor(win, ColorRGBToU32(color));
    }
    ((cGameTimeMgr*)GameTimeManager())->IncPauseGate(0x7e9e4b7);
    FUN_0106f3d0();
}

}  // namespace SP
