// Slice s00dddd20 (batch bfs3, slice 11). Region 0xdddd20-0xddea3a.
// Galaxy game-entry app mode / camera input camera-controller helpers.
// Optimised: /O2 /MD /Gy /TP /arch:SSE.
#include "types.h"
#include <math.h>
#include <new>

extern "C" void* __cdecl EA_Allocate(uint32_t size, const char* name, int a, int b,
                                     int c, int d);              // 0xf473a0
extern "C" void  __cdecl EA_Free(void* p);                       // 0xf47380

extern "C" void* __cdecl SP_PropertyManager();                   // 0x67de30
extern "C" void* __cdecl SP_MessageServer();                     // 0x67dcc0
extern "C" void* __cdecl SP_App();                               // 0x67dd10
extern "C" void* __cdecl SP_CheatManager();                      // 0x67de20
extern "C" double __cdecl CRT_pow();                             // 0x11e08f0
extern "C" char  __cdecl FUN_006bb5e0();
extern "C" char  __cdecl FUN_006a1400(void*, uint32_t, void**);
extern "C" void  __cdecl FUN_00685520();
extern "C" void  __cdecl FUN_006895b0();
extern "C" void  __cdecl FUN_00de6be0();
extern "C" void  __cdecl FUN_00de76b0();
extern "C" void  __cdecl FUN_00ddfec0();
extern "C" void  __cdecl FUN_0083bcd0();
extern "C" void  __cdecl FUN_0083c800();
extern "C" void  __cdecl FUN_0083b9d0_(void*, void*);
extern "C" void  __cdecl FUN_00f2dde0_();
extern "C" void  __cdecl FUN_0083a9f0();
extern "C" void  __cdecl FUN_00423650();                          // WString_Assign
extern "C" void  __cdecl FUN_00c2e4e0();
extern "C" char  __cdecl FUN_006237d0();
extern "C" void  __cdecl FUN_00ddddf0(void*, int);
extern "C" void  __cdecl FUN_00dddf30();
extern "C" void* __cdecl operator_new_prop();

// ---------------------------------------------------------------------------
// Globals referenced by absolute address in the original (names arbitrary;
// references are masked relocations).
// ---------------------------------------------------------------------------
float g_15a3000, g_15a3004, g_15a3008, g_15a3014, g_15a3018, g_15a301c;
float g_15a308c, g_15a3090;
float g_1f4;                          // placeholder
float g_camera_roll;                  // 0x15a30a0
float g_camera_pitch;                 // 0x15a30a4
float g_15a30ac;
float g_16a10bc, g_16a10c0, g_16a10d8, g_16a10dc;
void* g_16a10c8;
int   g_15a30bc, g_15a30c4;
uint8_t g_15a3068;
void* g_16a1344;
int   g_15a2df8;
// camera controller state (0x15a3048 block)
float g_cc0, g_cc4, g_cc8;            // 0x15a3048/4c/50
float g_cct0, g_cct4, g_cct8;         // 0x15a3054/58/5c
// 0x15a30ec..0x15a3130 block for FUN_00dde900
int   g_30ec, g_30f0, g_30f4;
int   g_3114, g_3118;
float g_311c, g_3120, g_3124;
int   g_3128, g_312c, g_3130;
// 0x15a3094 / 0x16a10c8 setters
float g_15a3094;
uint8_t g_16a0c80;

struct Vec3 { float x, y, z; };
struct PropVal { int pad_00; uint16_t type12; uint8_t flags10; };
struct PropMgr2 {
    int pad_00;
    char getProp(uint32_t a, void* b, void** out);   // vtable slot 0x2c
};
struct PropMgrVF { PropMgr2* vf() { return *(PropMgr2**)this; } };

struct Obj2 {
    int pad_00;
    char getProp(uint32_t a, void* b, void** out);   // vtable slot 0x24
};

// ===========================================================================
//  0x00dddd20  compare/assign a Vector3 member against a property
// ===========================================================================
// @ 0x00dddd20
char VecUpdate(void* self, void* prop) {
    void* out = 0;
    if (!((Obj2*)prop)->getProp(*(uint32_t*)((char*)self + 4), 0, &out)) {
        return 0;
    }
    PropVal* pv = (PropVal*)out;
    Vec3 v;
    uint16_t t = pv->type12;
    if (t == 0x31 || t == 0x10) {
        if ((pv->flags10 & 0x30) != 0) {
            v.x = *(float*)pv;
            v.y = *(float*)((char*)pv + 4);
            v.z = *(float*)((char*)pv + 8);
        } else {
            return 0;
        }
    } else {
        FUN_006bb5e0();
    }
    if (*(float*)((char*)self + 0xc) != v.x ||
        *(float*)((char*)self + 0x10) != v.y ||
        *(float*)((char*)self + 0x14) != v.z) {
        *(float*)((char*)self + 0xc) = v.x;
        *(float*)((char*)self + 0x10) = v.y;
        *(float*)((char*)self + 0x14) = v.z;
        return 1;
    }
    return 0;
}

// ===========================================================================
//  0x00ddddf0  fetch a property into a member if id matches
// ===========================================================================
// @ 0x00ddddf0
char PropFetch(void* self, uint32_t a, uint32_t b) {
    if (*(int*)((char*)self + 4) != -1) {
        return 0;
    }
    void* prop = 0;
    char r = 0;
    if (SP_PropertyManager() != 0) {
        PropMgr2* pm = *(PropMgr2**)SP_PropertyManager();
        if (prop) {
            prop = 0;
        }
        pm->getProp(a, (void*)b, &prop);
    }
    if (prop) {
        r = FUN_006237d0();
    }
    return r;
}

// ===========================================================================
//  0x00ddde80  allocate a small object and register it
// ===========================================================================
struct SmallReg { void* vt0; void* vt1; int a; int b; };
struct Registrator {
    void reg(SmallReg* obj, uint32_t id, const char* name);  // vtable slot 0x20
};
// @ 0x00ddde80
void RegisterSmall(void* param) {
    SmallReg* o = (SmallReg*)EA_Allocate(0x10, "App", 0, 0, 0, 0);
    if (o != 0) {
        o->vt1 = (void*)0x13ec458;
        o->a = 0;
        o->vt0 = (void*)0x147d360;
        o->vt1 = (void*)0x147d34c;
        o->b = 0;
    } else {
        o = 0;
    }
    ((Registrator*)param)->reg(o, 0x2ccd1d2, "GalaxyGameEntry");
}

// ===========================================================================
//  0x00dddf30  ArgScript command constructor
// ===========================================================================
struct ArgScript { void* vt; int pad[3]; int arg10; int arg14; };
struct ArgSpec {
    ArgSpec(int);
    void ConstructSpec(const char*, const char*, int, const char*,
                       const char*, int, const char*, int);
};
// @ 0x00dddf30
ArgScript* MakeLevelCheats(ArgScript* self, int arg) {
    FUN_0083c800();
    self->vt = (void*)0x147d41c;
    self->arg10 = arg;
    new ((ArgSpec*)((char*)self + 0x14)) ArgSpec(1);
    ((ArgSpec*)((char*)self + 0x14))->ConstructSpec(
        "Level Cheats", "-unlock^", 0, "Unlocks all game levels",
        "-unlockAdventures^", 1, "Unlocks all Maxis adventures", 0);
    return self;
}

// ===========================================================================
//  0x00dddf90  ArgScript command parse
// ===========================================================================
struct ArgCmd { void* vt; int f04; char pad[0x7c]; uint32_t flags84; };
// @ 0x00dddf90
void ArgCmd_Parse(ArgCmd* self, void* arg) {
    FUN_0083b9d0_(arg, *(void**)((char*)self + 4));
    if (*(uint8_t*)((char*)self + 0x84) & 1) {
        *(uint8_t*)((char*)g_16a1344 + 0x1f5) = 1;
    }
    if ((*(uint32_t*)((char*)self + 0x84) >> 1) & 1) {
        FUN_00f2dde0_();
    }
}

// ===========================================================================
//  0x00dddfd0  SP::cGalaxyGameEntryAppMode::Init
// ===========================================================================
// @ 0x00dddfd0
char GalaxyGameEntry_Init(void* self, void* mode) {
    // Large body: simulator creation, message registration, property reads and
    // cheat registration.  See partial.txt.
    (void)self; (void)mode;
    FUN_00de6be0();
    FUN_00de76b0();
    *(int*)((char*)g_16a1344 + 0x1ec) = 1;
    return 1;
}

// ===========================================================================
//  0x00dde2b0  camera-controller field initialiser
// ===========================================================================
struct CamCtl {
    int f04, f08, f0c;
    float f10, f14, f18, f1c;
    float f20, f24, f28, f2c;
    float f30, f34, f38, f3c;
    float f40, f44, f48, f4c;
    float f50, f54, f58, f5c, f60, f64, f68;
    void init(void* arg2, const Vec3* v);
};
// @ 0x00dde2b0
void CamCtl::init(void* arg2, const Vec3* v) {
    f30 = g_15a308c;
    f1c = g_15a3090;
    f10 = v->x; f14 = v->y; f18 = v->z;
    f24 = g_15a3094;
    f2c = *(float*)0x13ec4d0;
    f40 = v->x; f44 = v->y; f48 = v->z;
    f34 = g_cc0; f38 = g_cc4; f3c = g_cc8;
    f4c = f34; f50 = f38; f54 = f3c;
    f04 = 0;
    f08 = 500;
    f0c = 0;
    (void)arg2;
}

// ===========================================================================
//  0x00dde350  camera-controller update
// ===========================================================================
// @ 0x00dde350
void CamCtl_Update(CamCtl* self, int dt) {
    *(int*)&self->f08 += dt;
    double q = (double)(unsigned int)self->f08 / (double)(unsigned int)self->f04;
    if (1.0 < q) {
        void* ms = SP_MessageServer();
        (*(void(__thiscall**)(void*, uint32_t, void*, void*))*(void**)((char*)ms + 0))(ms, 0x4360e14, 0, 0);
        self->f08 = 0;
        g_16a10c8 = (void*)0x15a30b4;
    }
    self->f10 = (self->f0c - self->f14) * (float)(1.0 - q) + self->f14;
}

// ===========================================================================
//  0x00dde400  input key handler
// ===========================================================================
// @ 0x00dde400
char CamCtl_Key(CamCtl* self, uint32_t key) {
    if (key == 0xbb || key == 0x6b) {
        g_camera_roll = self->f18 * *(float*)0x147dab8;
    }
    if (key == 0xbd || key == 0x6d) {
        g_camera_roll = self->f18 * *(float*)0x13f08c0;
    }
    if (key == 0x25 || key == 0xbc || key == 0x64) {
        g_camera_pitch = self->f1c * g_16a10dc * *(float*)0x13f1cac;
    }
    if (key == 0x27 || key == 0xbe || key == 0x66) {
        g_camera_pitch = self->f1c * g_16a10dc * *(float*)0x14000fc;
    }
    return 0;
}

// @ 0x00dde4b0
char __stdcall CamCtl_ResetPitch(int, int) {
    g_camera_pitch = 0.0f;
    return 0;
}

// @ 0x00dde4c0
void CamCtl_Set2(CamCtl* self, int a, float v1, float v2) {
    self->f20 = v1;
    self->f24 = v2;
    g_16a10c0 = v1;
    g_16a10bc = v2;
    *(uint8_t*)((char*)self + 0x40) = 1;
    (void)a;
}

// @ 0x00dde4f0
char CamCtl_Reset2(CamCtl* self) {
    *(uint8_t*)((char*)self + 0x40) = 0;
    g_camera_pitch = 0.0f;
    g_15a30ac = 0.0f;
    return 1;
}

// @ 0x00dde510
char __stdcall CamCtl_SetGlobals(float v1, float v2, int) {
    g_16a10c0 = v1;
    g_16a10bc = v2;
    return 0;
}

// @ 0x00dde540
char CamCtl_Zoom(CamCtl* self, int n) {
    g_camera_roll = -(((float)n * self->f14) * *(float*)0x13eb8a0 * self->f18);
    return 0;
}

// @ 0x00dde570
void CamCtl_ResetGlobals() {
    g_15a30bc = 0;
    g_15a30c4 = 2;
}

// @ 0x00dde590
void __stdcall CamCtl_Release(void* x) {
    if (g_16a10c8 != 0) {
        (*(void(__thiscall**)(void*))*(void**)((char*)g_16a10c8 + 0))((void*)0);
    }
    (void)x;
}

// @ 0x00dde5b0
void __stdcall CamCtl_SetFlag(uint8_t v) {
    g_15a3068 = v;
}

// ===========================================================================
//  0x00dde5d0  camera-controller physics integration
// ===========================================================================
// @ 0x00dde5d0
void CamCtl_Integrate(CamCtl* self, float dt) {
    // Large x87 body; see partial.txt.
    (void)self; (void)dt;
}

// ===========================================================================
//  0x00dde7f0  easing helper
// ===========================================================================
// @ 0x00dde7f0
double Ease(double t, double p) {
    double x = t * 2.0;
    if (x < 1.0) {
        double a = sqrt(1.0 / p) * x;
        return a * a * p * 0.5;
    }
    double a = (2.0 - x) * sqrt(1.0 / p);
    return 1.0 - a * a * p * 0.5;
}

// ===========================================================================
//  0x00dde860  camera-controller per-frame update
// ===========================================================================
// @ 0x00dde860
void CamCtl_Tick(int ms) {
    float f = (float)ms * *(float*)0x13f9428;
    CamCtl_Integrate((CamCtl*)0x15a3048, f);
    g_cc0 += (g_cct0 - g_cc0) * *(float*)0x147da80;
    g_cc4 += (g_cct4 - g_cc4) * *(float*)0x147da80;
    g_cc8 += (g_cct8 - g_cc8) * *(float*)0x147da80;
}

// ===========================================================================
//  0x00dde900  initialise a camera-controller preset
// ===========================================================================
// @ 0x00dde900
void CamCtl_Preset(float f) {
    g_3118 = 0;
    g_3114 = (int)(f * *(float*)0x13ec5b4);
    g_311c = g_15a3094;
    g_3120 = g_15a3094;
    g_3124 = *(float*)0x13f1cac;
    g_3128 = g_30ec;
    g_312c = g_30f0;
    g_3130 = g_30f4;
    g_16a10c8 = (void*)0x15a3110;
}

// ===========================================================================
//  0x00dde9e0  reset camera-controller preset
// ===========================================================================
// @ 0x00dde9e0
void CamCtl_PresetReset() {
    g_cct0 = 0.0f;
    g_cct4 = 0.0f;
    g_cct8 = *(float*)0x147da94;
    g_cc0 = 0.0f;
    g_cc4 = 0.0f;
    g_cc8 = *(float*)0x147da94;
    g_16a10c8 = (void*)0x15a30b4;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
