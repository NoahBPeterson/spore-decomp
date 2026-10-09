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
extern "C" void  __cdecl FUN_0080fee0();
extern "C" void* __cdecl FUN_0080fee0_new(uint32_t);
extern "C" void* __cdecl FUN_00810620();
extern "C" void  __cdecl FUN_00805080();
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
extern "C" void  __cdecl FUN_00e02040();
extern "C" void  __cdecl FUN_00644b10();
extern "C" void  __cdecl FUN_00644b60();

// globals
int g_16a1344_dummy;
void* g_16a1344;
uint8_t g_16a15fc_byte;
void* g_016a15fc;
int g_16c7aa4[0x40];
int g_15fd918;
void* g_15a487c;
void* g_15a4878;
int g_15a4848, g_15a483c;
uint8_t g_16a0c80;

struct SPUILayout {
    void* FindWindowByID(void* id, int a);
    void  SetVisibility(void* v);
    char  IsVisible();
};
struct GUIRootObj {
    void  resetA();   // 0x0093a2e0 (equiv t3)
    void  resetB();   // 0x0093a2e0 (equiv t3)
};
struct GlobalUI {
    void* pad0;
    void* f04;
    void* f08;
    void* FindWindowByID(void* id);
    char  FUN_12d0(void* id);
    void  SetVisibility(void* v);
    char  IsVisible();
    void  FUN_1250(void* x);
};

// ===========================================================================
//  0x00e00760  context-sensitive sporepedia launcher
// ===========================================================================
// @ 0x00e00760
void ShowContextSporepedia(void* self, void* info) {
    // Complex; see partial.txt.
    *(uint8_t*)((char*)self + 4) = 0;
    if (info) {
        FUN_00644b10();
        FUN_00e02040();
        FUN_00644b60();
    }
}

// ===========================================================================
//  0x00e008e0  some manager ctor
// ===========================================================================
// @ 0x00e008e0
void* MgrCtor(void* self) {
    *(uint8_t*)((char*)self + 4) = 0;
    *(void**)self = (void*)0x147f000;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = 0;
    *(void**)((char*)self + 0x10) = 0;
    FUN_0093a560();
    FUN_0093a560();
    *(void**)((char*)self + 0x54) = 0;
    *(void**)((char*)self + 0x58) = 0;
    *(void**)((char*)self + 0x5c) = 0;
    FUN_0093a560();
    FUN_0093a480();
    *(void**)((char*)self + 0x90) = 0;
    *(void**)((char*)self + 0x94) = 0;
    *(void**)((char*)self + 0x98) = 0;
    *(uint8_t*)((char*)self + 0x50) = 0;
    *(int*)((char*)self + 0x68) = -1;
    g_016a15fc = self;
    return self;
}

// @ 0x00e00970
void MgrDtor(void* self) {
    FUN_004b5440();
    void* p = *(void**)((char*)self + 0x54);
    if (p != 0 && *((int*)p - 1) != 0) {
        EA_Free(p);
    }
    FUN_00de5ee0();
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
        int ctx = (int)FUN_01015df0();   // placeholder; GetUniverseContext
        (void)ctx;
    }
    // Simplified predicate; see nonmatching.txt.
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
    return 0;
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
char FUN_00e00c40_impl() { return 0; }

// @ 0x00e00d20
char FUN_00e00d20_impl() {
    if (SP_GetCurrentGameMode() == (void*)0x1654c00) {
        return 0;
    }
    if (FUN_00e00c40_impl()) {
        return 0;
    }
    if (FUN_006a25a0() == 0) { /* placeholder */ }
    return 1;
}

// @ 0x00e00d90
uint32_t __fastcall FUN_00e00d90_impl(int self) {
    return (-(int)(*(bool*)(self + 0x28)) & 2) | 0x410;
}

// @ 0x00e00db0
void FUN_00e00db0_impl(void* self, float dt) {
    FUN_00805080();
    float a = *(float*)((char*)self + 0x20);
    float b = *(float*)((char*)self + 0x24);
    (void)a; (void)b; (void)dt;
}

// @ 0x00e00e90
void FUN_00e00e90_impl(void* self) { (void)self; }

// ===========================================================================
//  0x00e00ec0  UI::cSPUIGlobalOptions ctor
// ===========================================================================
// @ 0x00e00ec0
void* GlobalOptionsCtor(void* self) {
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
void GlobalOptionsDtor(void* self) {
    *(void**)self = (void*)0x147f17c;
    *(void**)((char*)self + 4) = (void*)0x147f16c;
    FUN_006b5240();
    FUN_006b5240();
    *(void**)self = (void*)0x13eb938;
    *(void**)((char*)self + 4) = (void*)0x13ec458;
}

// @ 0x00e00fe0
void GlobalOptionsReset(void* self) { (void)self; }

// @ 0x00e01090
void* DtorF1(void* self, unsigned int flags) {
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
void* WinProcCtor(void* self, void* arg) {
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
    FUN_0093a560();
    FUN_0093a560();
    *(void**)((char*)self + 0x58) = 0;
    *(void**)((char*)self + 0x5c) = arg;
    g_15a487c = self;
    FUN_0093a1a0();
    FUN_0093a1a0();
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
void WinProcDtor(void* self) {
    *(void**)self = (void*)0x147f1c8;
    *(void**)((char*)self + 4) = (void*)0x147f1b8;
    *(void**)((char*)self + 8) = (void*)0x147f1a8;
    void* h = *(void**)((char*)self + 0x10);
    if (h != 0) {
        h = 0;
        FUN_00571db0(h, *(void**)((char*)self + 0x14), *(void**)((char*)self + 0x18),
                     *(void**)((char*)self + 0x1c), *(void**)((char*)self + 0x20));
    }
    g_15a487c = 0;
    g_15a4878 = 0;
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
    FUN_006a17e0();
    g = SP_GameTimeManager();
    FUN_00b32280();
    (void)g;
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
char GlobalUI::FUN_12d0(void* id) {
    void* layout = f08;
    if (layout == 0) return 0;
    void* w = (void*)FUN_008105b0();
    if (w == 0) return 0;
    void* c = (void*)(*(void*(__thiscall**)(void*, uint32_t, int))(*(void**)((char*)w + 0xf0)))(w, 0x665fe90, 0);
    if (c == 0) return 0;
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
char FUN_00e01390_impl() { return 0; }

// @ 0x00e014a0
char FUN_00e014a0_impl() { return 0; }

// ===========================================================================
//  0x00e01570  small POD copy with refcounted members
// ===========================================================================
// @ 0x00e01570
void* PodCopy(void* s, void* o) {
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
void* NetworkActivityCtor(void* self) {
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
void* NetworkActivityDtor(void* self, unsigned int flags) {
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
