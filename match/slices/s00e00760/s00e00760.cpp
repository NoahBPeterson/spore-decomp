// Slice s00e00760 (batch bfs3, slice 13). Region 0xe00760-0xe0174b.
// Global-UI root window proc, options object, network activity proc and various
// game-mode predicates.  Optimised: /O2 /MD /Gy /TP /arch:SSE.
#include "types.h"

extern "C" void* __cdecl EA_Allocate(uint32_t size, const char* name, int a, int b,
                                     int c, int d);              // 0xf473a0
extern "C" void  __cdecl EA_Free(void* p);                       // 0xf47380

extern "C" void* __cdecl SP_GetCurrentGameMode();                // 0xb5b800
extern "C" void* __cdecl SP_MessageServer();                     // 0x67dcc0
extern "C" void* __cdecl SP_WindowManager();                     // 0x67caa0
extern "C" void* __cdecl SP_GameTimeManager();                   // 0xb3d380
extern "C" void* __cdecl SP_SpaceGameGet();                      // 0x1002bd0
extern "C" void* __cdecl SP_NounManager();                       // 0xb3d300
extern "C" char  __cdecl FUN_00dd1230();
extern "C" char  __cdecl FUN_00e09540();
extern "C" char  __cdecl FUN_00cd44a0();
extern "C" char  __cdecl FUN_00a98020();
extern "C" char  __cdecl FUN_00ae9390();
extern "C" char  __cdecl FUN_01065e20();
extern "C" char  __cdecl FUN_00ed9e60(int);
extern "C" void* __cdecl FUN_00b3d4d0();
extern "C" void* __cdecl FUN_00cf74c0();
extern "C" void* __cdecl FUN_01015df0();
extern "C" void* __cdecl FUN_010666a0();
extern "C" void* __cdecl FUN_00ffbe50();
extern "C" void* __cdecl FUN_00b3d4a0();
extern "C" void* __cdecl FUN_00b18e40();
extern "C" void  __cdecl FUN_00b32280();
extern "C" void  __cdecl FUN_00b32250();
extern "C" void  __cdecl FUN_00b32220();
extern "C" void  __cdecl FUN_00e3c6f0();
extern "C" void  __cdecl FUN_006035d0();
extern "C" int   __cdecl FUN_006a25a0();
extern "C" void  __cdecl FUN_006a17e0();
extern "C" void  __cdecl FUN_00809db0(void*, void*);
extern "C" void* __stdcall FUN_0080fee0(uint32_t tag);
extern "C" void* __cdecl FUN_0080fee0_new(uint32_t);
extern "C" void* __cdecl FUN_00810620();
extern "C" float __cdecl FUN_00805080();
extern "C" void* __cdecl FUN_008105b0();
extern "C" void* __cdecl FUN_00810590();
extern "C" char  __cdecl FUN_00810070();
extern "C" void  __cdecl FUN_00f280f0(void*);
extern "C" void  __cdecl FUN_006b5770();
extern "C" void  __cdecl FUN_006b5240();
extern "C" void  __cdecl FUN_00571db0(void*, void*, void*, void*, void*);
extern "C" void  __cdecl FUN_0093a560();
extern "C" void  __cdecl FUN_0093a1a0();
extern "C" void  __cdecl FUN_0093a480();
extern "C" void  __cdecl FUN_0093a2e0();
extern "C" void  __cdecl FUN_004b5440();
extern "C" void  __cdecl FUN_00de5ee0();
extern "C" void* __cdecl FUN_00de0a90();
extern "C" void  __cdecl FUN_00e02040(void* arg);
extern "C" void  __cdecl FUN_00644b10();
extern "C" void  __cdecl FUN_00644b60();
extern "C" void  __cdecl FUN_00808230(void* obj, void* p);   // 0x808230 (cdecl, 2 args)
extern "C" double __cdecl cos(double);
#pragma intrinsic(cos)

// Two-level virtual-slot dispatch helpers (object -> vtable -> slot).
typedef void  (__thiscall* VFnV)(void*);
typedef char  (__thiscall* VFnC)(void*);
typedef int   (__thiscall* VFnI)(void*);
typedef void* (__thiscall* VFnP)(void*);
typedef void* (__thiscall* VFnPU)(void*, uint32_t);
typedef void* (__thiscall* VFnPUI)(void*, uint32_t, int);
typedef void  (__thiscall* VFnVV)(void*, void*);
typedef void  (__thiscall* VFnVFF)(void*, float, float);
#define VSLOT(o, off) (*(void**)((char*)(*(void**)(o)) + (off)))

// ---------------------------------------------------------------------------
//  Helpers reached from the mode predicates and the window helpers.  The
//  original calls them with the object in ecx, so each is modelled as a member
//  function of an opaque class (the symbol is never defined here).
// ---------------------------------------------------------------------------
extern "C" int   __cdecl FUN_01021080();                 // 0x01021080 GetUniverseContext
extern "C" void* __cdecl FUN_00cd40b0();                 // 0x00cd40b0 cTribeModeStrategy::Instance
extern "C" void* __cdecl FUN_00b3d4d0();                 // 0x00b3d4d0
extern "C" void* __cdecl FUN_00cf74c0();                 // 0x00cf74c0 civ-mode strategy
extern "C" void* __cdecl FUN_010666a0();                 // 0x010666a0 space-mode helper
extern "C" void* __cdecl FUN_00ffbe50();                 // 0x00ffbe50
extern "C" void* __cdecl FUN_00b3d4a0();                 // 0x00b3d4a0
extern "C" void* __cdecl FUN_01015df0();                 // 0x01015df0 universe context
extern "C" void* __stdcall FUN_00805070(uint32_t tag);     // 0x00805070 curator lookup

// Opaque "this-call target": the original invokes each as a virtual/non-virtual
// method on the object named by its caller.
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

// An object constructor with the shipped `__thiscall` ABI (ecx = storage).
struct AllocObj { void* FUN_00de0a90(void* gp, int flag); };

// The launcher object whose window proc this slice implements.
struct CtxObj { void ShowContextSporepedia(void* info); uint8_t PeekObjFlag(void* p); };

// globals
int g_16a1344_dummy;
void* g_16a1344;
uint8_t g_16a15fc_byte;
void* g_016a15fc;
void* g_16c7aa4;
int g_15fd918;
float g_16a18d8;
void* g_15a487c;
void* g_15a4878;
int g_15a4848, g_15a483c;
uint8_t g_16a0c80;

struct MgrObj { void* Ctor(); void Dtor(); };
struct OptObj { void* Ctor(); void Dtor(); void* DelDtor(unsigned int flags); void Reset(); };
// cSPUIGlobalOptions member window slots (Reset reads these by name).
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
    void  FUN_00e00db0(float dt);
    char  FUN_00e00e90(uint32_t msg, void* arg);
    uint8_t pad00[0x10];
    float   f10;         // +0x10
    float   f14;         // +0x14
    float   f18;         // +0x18
    float   f1c;         // +0x1c
    float   f20;         // +0x20
    float   f24;         // +0x24
    uint8_t f28;         // +0x28
    uint8_t pad29[3];
    void*   p2c;         // +0x2c
    void*   p30;         // +0x30
};
struct SPUILayout {
    void* FindWindowByID(void* id, int a);
    void  SetVisibility(void* v);
    char  IsVisible();
};
// EA::Stopwatch / EA::LimitStopwatch layout (member functions give the shipped __thiscall ABI).
struct StopwatchObj {
    void  FUN_0093a560(int units, int start);   // EA::Stopwatch::Stopwatch
    void  FUN_0093a1a0(int units);              // EA::Stopwatch::SetUnits
    uint64_t mnStartTime;                       // +0x00
    uint64_t mnTotalElapsedTime;                // +0x08
    int      mnUnits;                           // +0x10
    float    mfCyclesToUnitsCoefficient;        // +0x14
};
struct LimitStopwatchObj : StopwatchObj {
    uint64_t mnEndTime;                         // +0x18
    void  FUN_0093a480(unsigned int limit, int start);   // EA::LimitStopwatch::SetTimeLimit
};
struct RefVecObj {
    void  FUN_004b5440();                       // vector-of-refcounted destructor
    void  FUN_00de5ee0(void* begin, void* end); // destroy range (this = vector)
    void* mpBegin;                              // +0x00
    void* mpEnd;                                // +0x04
    void* mpEndCap;                             // +0x08
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

// ===========================================================================
//  0x00e00760  context-sensitive sporepedia launcher
// ===========================================================================
struct LaunchCtx {                       // stack temp built by 0x00644b10
    uint32_t pad00;                      // +0x00
    uint32_t pad04;                      // +0x04
    uint32_t pad08;                      // +0x08
    void*    mpObj;                      // +0x0c  allocated launcher object
    uint8_t  f10;                        // +0x10
    uint16_t pad11;                      // +0x11
    uint8_t  f13;                        // +0x13
    uint32_t pad14;                      // +0x14
    uint32_t f18;                        // +0x18
    uint32_t f1c;                        // +0x1c
    uint32_t f20;                        // +0x20
    uint8_t  f24;                        // +0x24
    uint32_t pad2c;                      // +0x2c
    void Ctor();                         // 0x00644b10
    void Dtor();                         // 0x00644b60
};
// @ 0x00e00760
// NOTE: the original writes `flag` through the low byte of its saved-edi slot ([esp+0x58]) and
// passes the full dword to FUN_00de0a90, and calls LaunchCtx::Ctor (0x644b10) once per arm of
// the info+0x44 branch; that frame layout is what makes it 378 bytes.  Our /O2 build keeps
// `flag` in a real 8-bit local, hoists the Ctor above the branch and joins the allocations, so
// the emitted code is smaller but the observable behaviour is the same.
void CtxObj::ShowContextSporepedia(void* info) {
    ((uint8_t*)this)[4] = 0;
    if (info == 0) return;
    char bMatch = (*(uint32_t*)((char*)info + 0xc) == 0x13c5a95eu) ? 1 : 0;
    void* obj = 0;
    void* p = *(void**)((char*)info + 0x10);
    if (p != 0) {
        obj = ((VFnPU)VSLOT(p, 0xc))(p, 0xf5e905cdu);
        if (obj != 0) {
            ((VFnV)VSLOT(obj, 0))(obj);
        }
    }
    if (!bMatch && ((uint8_t*)info)[0x44] != 0) goto done1;
    if (((uint8_t*)g_16a1344)[0x24d] != 0) goto done1;
    {
        LaunchCtx launch;
        uint8_t flag = 0;
        if (obj != 0) flag = ((uint8_t*)obj)[0x10];
        launch.Ctor();
        launch.f18 = *(uint32_t*)((char*)info + 0x18);
        launch.f1c = *(uint32_t*)((char*)info + 0x1c);
        launch.f20 = *(uint32_t*)((char*)info + 0x20);
        if (((uint8_t*)info)[0x44] != 0) {
            launch.f24 = 0;
            void* mem = EA_Allocate(0x14, (const char*)0x13fa29c, 0, 0, 0, 0);
            launch.mpObj = mem ? ((AllocObj*)mem)->FUN_00de0a90(g_16a1344, 0) : 0;
        } else {
            launch.f13 = (uint8_t)(bMatch == 0);
            launch.f24 = 1;
            void* mem = EA_Allocate(0x14, (const char*)0x13fa29c, 0, 0, 0, 0);
            launch.mpObj = mem ? ((AllocObj*)mem)->FUN_00de0a90(g_16a1344, flag) : 0;
        }
        FUN_00e02040(&launch);
        launch.Dtor();
    }
done1:
    if (obj != 0) {
        ((VFnV)VSLOT(obj, 4))(obj);
    }
}

// ===========================================================================
//  0x00e008e0  some manager ctor
// ===========================================================================
// @ 0x00e008e0
void* MgrObj::Ctor() {
    void* self = this;
    *(uint8_t*)((char*)self + 4) = 0;
    *(void**)self = (void*)0x147f000;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = 0;
    *(void**)((char*)self + 0x10) = 0;
    ((StopwatchObj*)((char*)self + 0x20))->FUN_0093a560(0, 0);
    ((StopwatchObj*)((char*)self + 0x38))->FUN_0093a560(0, 0);
    *(void**)((char*)self + 0x54) = 0;
    *(void**)((char*)self + 0x58) = 0;
    *(void**)((char*)self + 0x5c) = 0;
    ((LimitStopwatchObj*)((char*)self + 0x70))->FUN_0093a560(0, 0);
    ((LimitStopwatchObj*)((char*)self + 0x70))->FUN_0093a480(0, 0);
    *(void**)((char*)self + 0x90) = 0;
    *(void**)((char*)self + 0x94) = 0;
    *(void**)((char*)self + 0x98) = 0;
    *(uint8_t*)((char*)self + 0x50) = 0;
    *(int*)((char*)self + 0x68) = -1;
    g_016a15fc = self;
    return self;
}

// @ 0x00e00970
void MgrObj::Dtor() {
    void* self = this;
    ((RefVecObj*)((char*)self + 0x90))->FUN_004b5440();
    void* p = *(void**)((char*)self + 0x54);
    if (p != 0 && *((int*)p - 1) != 0) {
        EA_Free(p);
    }
    ((RefVecObj*)((char*)self + 8))->FUN_00de5ee0(*(void**)((char*)self + 8),
                                                  *(void**)((char*)self + 0xc));
    p = *(void**)((char*)self + 8);
    if (p != 0 && *((int*)p - 1) != 0) {
        EA_Free(p);
    }
    *(void**)self = (void*)0x147dba8;
}

// ===========================================================================
//  0x00e009f0  on_ban_content_button
// ===========================================================================
struct MsgSrv { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                virtual void v4(); virtual void send(uint32_t, int, int); };
// @ 0x00e009f0
void on_ban_content_button() {
    if (FUN_00dd1230()) {
        ((MsgSrv*)SP_MessageServer())->send(0x44eaa93, 0, 0);
    } else if (FUN_00e09540()) {
        ((MsgSrv*)SP_MessageServer())->send(0x620222b, 0, 0);
    }
}

// @ 0x00e00a40
char IsGameModeAllowed() {
    if (SP_GetCurrentGameMode() == (void*)0x1654c05) {
        if (FUN_01021080() != 1 && FUN_01021080() != 2) return 0;
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
int MenuKind() {
    int r = 0x80;
    if (SP_GetCurrentGameMode() != (void*)0x1654c00) {
        r += 1;
    }
    return r;
}

// @ 0x00e00ac0
char FUN_00e00ac0_impl() {
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
char FUN_00e00b00_impl() {
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
void FUN_00e00bb0_impl() { FUN_00809db0(&g_15a4878, &g_15a4848); }
// @ 0x00e00bd0
void FUN_00e00bd0_impl() { FUN_00809db0(&g_15a4878, &g_15a483c); }

// @ 0x00e00bf0
void FUN_00e00bf0_impl() {
    if (FUN_00dd1230()) {
        ((MsgSrv*)SP_MessageServer())->send(0x44eaa93, 0, 0);
    } else if (FUN_00e09540()) {
        ((MsgSrv*)SP_MessageServer())->send(0x620222b, 0, 0);
    }
    FUN_006035d0();
}

// @ 0x00e00c40
char FUN_00e00c40_impl() {
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
char FUN_00e00d20_impl() {
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
uint32_t __fastcall FUN_00e00d90_impl(int self) {
    // The binary's `movzx/neg/sbb` is a "byte != 0" test; reading the byte through a bool*
    // is undefined for values other than 0/1, so test the raw byte instead.
    uint8_t b = *(uint8_t*)(self + 0x28);
    return ((uint32_t)-(int)(b != 0) & 2) | 0x410;
}

// @ 0x00e00db0
void NetObj::FUN_00e00db0(float dt) {
    float t = FUN_00805080();
    if (dt > 0.0f) {
        if (f28 == 0) {
            f20 = t;
            f24 = t + dt;
            f28 = 1;
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
            f28 = 0;
            ((VFnVV)VSLOT(p2c, 0x104))(p2c, this);
        }
    }
}

// @ 0x00e00e90
char NetObj::FUN_00e00e90(uint32_t msg, void* arg) {
    if (msg == 0x656435b) {
        ((NetObj*)((char*)this - 0xc))->FUN_00e00db0(*(float*)((char*)arg + 8));
        return 1;
    }
    return 0;
}

// ===========================================================================
//  0x00e00ec0  UI::cSPUIGlobalOptions ctor
// ===========================================================================
// @ 0x00e00ec0
void* OptObj::Ctor() {
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
void OptObj::Dtor() {
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
void OptObj::Reset() {
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
void* OptObj::DelDtor(unsigned int flags) {
    void* self = this;
    *(void**)self = (void*)0x147f198;
    *(void**)((char*)self + 4) = 0;
    if (flags & 1) {
        EA_Free(self);
    }
    return self;
}

// ===========================================================================
//  0x00e010c0  cSPUIGlobalUIRootWinProc ctor
// ===========================================================================
// @ 0x00e010c0
void* WinObj::Ctor(void* arg) {
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
void WinObj::Dtor() {
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
void GlobalUI::FUN_1250(void* x) {
    GUIRootObj* p = (GUIRootObj*)f04;
    if (p != 0) {
        p->resetA();
        p->resetB();
    }
    (void)x;
}

// @ 0x00e01270
void FUN_00e01270_impl() {
    void* g = SP_GameTimeManager();
    uint8_t b = *(uint8_t*)((char*)g + 0x48);
    int v = (~(int)b) & 1;                       // `not al; and al,1`
    void* propList = (void*)(uint32_t)g_15fd918;
    ((DirectPropListObj*)propList)->FUN_006a17e0(0x387d0a8u, v);
    g = SP_GameTimeManager();
    ((GameTimeMgrObj*)g)->FUN_00b32280((void*)0x4bf38a8);
}

// @ 0x00e012b0
void* GlobalUI::FindWindowByID(void* id) {
    SPUILayout* p = (SPUILayout*)f08;
    if (p != 0) {
        return p->FindWindowByID(id, 1);
    }
    return 0;
}

// @ 0x00e012d0
char GlobalUI::FUN_12d0(void* id, float f) {
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
void GlobalUI::SetVisibility(void* v) {
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
char GlobalUI::IsVisible() {
    SPUILayout* p = (SPUILayout*)f08;
    if (p != 0) {
        return p->IsVisible();
    }
    return 0;
}

// @ 0x00e01390
char FUN_00e01390_impl() {
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
char FUN_00e014a0_impl() {
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

// ===========================================================================
//  0x00e01570  small POD copy with refcounted members
// ===========================================================================
// @ 0x00e01570
void* PodObj::Copy(void* o) {
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
void FUN_00e01620_impl(uint8_t pause) {
    if (pause) {
        FUN_00b32220();
        FUN_00e3c6f0();
    } else {
        FUN_00b32250();
    }
}

// ===========================================================================
//  0x00e01690  UI::NetworkActivityProc ctor
// ===========================================================================
// @ 0x00e01690
void* NetObj::Ctor() {
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
void* NetObj::DelDtor(unsigned int flags) {
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
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
