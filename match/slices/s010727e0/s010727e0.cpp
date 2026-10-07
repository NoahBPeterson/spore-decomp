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

namespace SP {

struct cSPUIGlobalUI {
    void* FindWindowByID(uint32_t id);                  // 0x00e012b0, thiscall, 1 arg
};

struct cCommandDeleteCargoButtonState {
    void* Ctor(void* owner, uint32_t window);           // 0x010665c0, thiscall, 2 args; returns this
};

struct cStarMap {
    void FilterHelper(uint32_t filter, uint32_t on);    // 0x01048b40, thiscall, 2 args
};

struct cFloatOwner {
    void FUN_01015f30(uint32_t value);                  // 0x01015f30, thiscall, 1 arg
};

struct cSPUISpace {
    uint8_t  pad00[0x10];
    void*    mpCommandDeleteCargoButtonState;           // +0x10
    uint32_t mDeleteButtonWindow;                       // +0x14
    uint8_t  pad18[0x224 - 0x18];
    cSPUIGlobalUI* mpGlobalUI;                          // +0x224
    uint8_t  pad228[0x694 - 0x228];
    void*    mpOverlay694;                              // +0x694 (loaded, not used in this partial)

    static void KillSetiEffects(uint32_t id, uint32_t state);  // 0x00435ed0, cdecl, 2 args

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

}  // namespace SP
