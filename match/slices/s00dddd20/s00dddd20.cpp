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
extern "C" char  __cdecl FUN_00685520(int mode);
extern "C" void* __cdecl FUN_006895b0();
extern "C" void  __cdecl FUN_00de6be0();
extern "C" void  __cdecl FUN_00de76b0();
extern "C" void  __cdecl FUN_00ddfec0();
extern "C" void  __cdecl FUN_0083bcd0();
extern "C" void  __cdecl FUN_0083c800();
struct ArgSub { void Parse(void* arg, void* x); };   // 0x0083b9d0 thiscall
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
extern float g_neg0p1_13eb964;        // 0x13eb964 = -0.1f (yaw-velocity threshold)
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
    ArgSpec(int);   // 0x0083a9f0 (equiv t3)
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
struct ArgCmd { void* vt; int f04; char pad[0x7c]; uint32_t flags84;
    void Parse(void* arg); };
// @ 0x00dddf90
void ArgCmd::Parse(void* arg) {
    ArgCmd* self = this;
    ((ArgSub*)((char*)self + 0x14))->Parse(arg, *(void**)((char*)self + 4));
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
struct SimObject {                                  // galaxy-entry simulator (0x274 bytes)
    uint8_t  mPad00[0xf0];
    void*    mpField0f0;                            // +0x0f0
    uint8_t  mPad0f4[0x100 - 0xf4];
    uint8_t  mByte100;                              // +0x100
    uint8_t  mPad101[0x1ec - 0x101];
    uint32_t mField1ec;                             // +0x1ec
    SimObject* ctor();                              // 0x00de6be0 (returns this)
    void setup();                                   // 0x00de76b0
};

struct PropTarget {                                 // property target object at 0x15a2ff8
    char Fetch(int id, int value);                  // 0x00ddddf0
};

struct WStringBuf {                                 // eastl string: begin / end / capacity
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpEndCap;
    void assign(wchar_t* first, wchar_t* last);     // 0x00423650
};

struct SimRef { void update(); };                   // 0x00c2e4e0
struct LevelCheats { void Construct(void* owner); };// 0x00dddf30

class cGalaxyGameEntryAppMode {
public:
    uint8_t mPad00[0x0c];
    void*   mpField0c;                              // +0x0c
    char Init(void* mode);
};

static inline void** VtableOf(void* p) { return *(void***)p; }

bool __cdecl GetPropertyAsString16(void* list, uint32_t id, WStringBuf* out);  // 0x006a1400

extern const char kSimulatorAllocName[];    // 0x013f09b4 "Simulator"

WStringBuf g_galaxyProp0;    // 0x16a0cf8
WStringBuf g_galaxyProp1;    // 0x16a0d08
WStringBuf g_galaxyProp2;    // 0x16a0d24
WStringBuf g_galaxyProp3;    // 0x16a0d44
WStringBuf g_galaxyProp4;    // 0x16a109c
WStringBuf g_galaxyProp5;    // 0x16a10ac

// @ 0x00dddfd0
char cGalaxyGameEntryAppMode::Init(void* mode) {
    (void)mode;
    SimObject* sim = (SimObject*)EA_Allocate(0x274, kSimulatorAllocName, 0, 0, 0, 0);
    if (sim != 0)
        sim = sim->ctor();
    else
        sim = 0;
    g_16a1344 = sim;
    sim->mByte100 = 0;
    ((SimObject*)g_16a1344)->mpField0f0 = mpField0c;

    // 0x00685520: game-mode/property-list availability probe.
    if (FUN_00685520(2) != 0)
        g_15a2df8 = 0x48f7da6b;

    // Register the galaxy-entry message handler with the app message server.
    void* app = SP_App();
    void* msgReg = ((void* (__thiscall*)(void*))VtableOf(app)[0x50 / 4])(app);
    ((void (__thiscall*)(void*, uint32_t, void*))VtableOf(msgReg)[0x20 / 4])(
        msgReg, 0x43c6e06, (void*)0xddfec0);

    // Attach the current property target to the galaxy entry mode.
    ((PropTarget*)0x15a2ff8)->Fetch(g_15a2df8, 0);

    // Read the six localised galaxy-entry strings from the property list.
    void* out = 0;
    void* pm = SP_PropertyManager();
    char found = ((char (__thiscall*)(void*, int, void*, void**))VtableOf(pm)[0x2c / 4])(
        pm, g_15a2df8, 0, &out);
    if (found) {
        WStringBuf str;
        str.mpBegin = (wchar_t*)0x1667bac;
        str.mpEnd = (wchar_t*)0x1667bac;
        str.mpEndCap = (wchar_t*)0x1667bae;
        if (GetPropertyAsString16(out, 0x21d994c5, &str))
            g_galaxyProp0.assign(str.mpBegin, str.mpEnd);
        if (GetPropertyAsString16(out, 0x90be803e, &str))
            g_galaxyProp1.assign(str.mpBegin, str.mpEnd);
        if (GetPropertyAsString16(out, 0xaf963138, &str))
            g_galaxyProp2.assign(str.mpBegin, str.mpEnd);
        if (GetPropertyAsString16(out, 0xd6f8f4a4, &str))
            g_galaxyProp3.assign(str.mpBegin, str.mpEnd);
        if (GetPropertyAsString16(out, 0x9e64a562, &str))
            g_galaxyProp4.assign(str.mpBegin, str.mpEnd);
        if (GetPropertyAsString16(out, 0xab444460, &str))
            g_galaxyProp5.assign(str.mpBegin, str.mpEnd);
        if ((int)(((uint32_t)str.mpEndCap - (uint32_t)str.mpBegin) & ~1u) > 2 && str.mpBegin != 0)
            EA_Free(str.mpBegin);
    }

    ((SimObject*)g_16a1344)->setup();
    ((SimObject*)g_16a1344)->mField1ec = 1;

    // 0x006895b0: register the galaxy entry state with its manager.
    void* mgr = FUN_006895b0();
    ((void (__thiscall*)(void*, uint32_t, uint32_t, int))VtableOf(mgr)[0x1c / 4])(
        mgr, 0x4530082, 0x147d434, 0);

    ((SimRef*)mpField0c)->update();

    // Register the level-cheat console command once per process.
    void* cheat = SP_CheatManager();
    if (cheat != 0 && g_16a0c80 == 0) {
        LevelCheats* cheats = (LevelCheats*)EA_Allocate(0xdc, kSimulatorAllocName, 0, 0, 0, 0);
        if (cheats != 0)
            cheats->Construct(this);
        else
            cheats = 0;
        ((void (__thiscall*)(void*, uint32_t, void*, int))VtableOf(cheat)[0x18 / 4])(
            cheat, 0x147d2e4, cheats, 1);
        g_16a0c80 = 1;
    }

    if (out != 0)
        ((void (__thiscall*)(void*))VtableOf(out)[1])(out);
    return 1;
}

// ===========================================================================
//  0x00dde2b0  camera-controller field initialiser
// ===========================================================================
struct CamCtl {
    int pad00;
    int f04, f08;
    float f0c;
    float f10, f14, f18, f1c;
    union { float f20; uint8_t mFlag20; };   // +0x20: float payload / low-byte flag
    float f24, f28, f2c;
    float f30, f34, f38, f3c;
    float f40, f44, f48, f4c;
    float f50, f54, f58, f5c, f60, f64, f68;
    void init(void* arg2, const Vec3* v);
    void Integrate(float dt);
    void Update(int dt, int unused);
    char Set2(int a, float v1, float v2, int unused);
    char Reset2(int a, int b, int c, int d);
    char Zoom(int n, int b, int c, int d);
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
void CamCtl::Update(int dt, int unused) {
    CamCtl* self = this; (void)unused;
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
char CamCtl::Set2(int a, float v1, float v2, int unused) {
    CamCtl* self = this; (void)unused;
    self->f20 = v1;
    self->f24 = v2;
    g_16a10c0 = v1;
    g_16a10bc = v2;
    *(uint8_t*)((char*)self + 0x40) = 1;
    (void)a;
    return 1;
}

// @ 0x00dde4f0
char CamCtl::Reset2(int a, int b, int c, int d) {
    CamCtl* self = this; (void)a; (void)b; (void)c; (void)d;
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
char CamCtl::Zoom(int n, int b, int c, int d) {
    (void)b; (void)c; (void)d;
    __asm {
        cvtsi2ss xmm0, dword ptr [n]
        mulss xmm0, dword ptr [ecx + 14h]
        mulss xmm0, dword ptr ds:[13eb8a0h]
        mulss xmm0, dword ptr [ecx + 18h]
        xorps xmm0, xmmword ptr ds:[13eb8b0h]
        movss dword ptr [g_camera_roll], xmm0
        xor al, al
    }
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
void CamCtl::Integrate(float dt) {
    // Target pitch approach: f58 is the pitch velocity, f4c the pitch angle.
    float a = (f40 - f4c) * g_15a3004;
    f58 = (float)((double)a * (double)dt + pow((double)g_15a3000, (double)dt) * (double)f58);
    f4c = f4c + f58 * dt;
    if (f38 > f4c)
        f4c = f38;
    if (f4c > f3c)
        f4c = f3c;

    // Yaw velocity f60: damped by the pow curve, with two configuration gains.
    float old5c = f5c;
    double p;
    if (g_neg0p1_13eb964 > old5c * f60)
        p = pow((double)g_15a3008, (double)dt) * (double)g_15a3018;
    else {
        p = pow((double)g_15a3008, (double)dt);
        if (mFlag20)
            p = p * (double)g_15a301c;
    }
    // The retail code rounds each product to float (mulss/addss); the volatile
    // temporaries force the same per-operation rounding out of the x87 unit.
    volatile float v1 = old5c * dt;
    volatile float v2 = (float)p * f60;
    f60 = v1 + v2;

    // Yaw angle, wrapped below by the full turn range.
    float new44 = f44 + f60 * dt;
    f44 = new44;

    // Roll limit: positive band, otherwise the mirrored negative band.
    float lim = 0.0f;
    if (f48 >= 0.0f && f24 > f48 && f64 >= 0.0f && f28 > f64)
        lim = f28;
    else if (f48 <= 0.0f && f48 > -f24 && f64 > -f28 && f64 <= 0.0f)
        lim = -f28;

    // Roll velocity and angle with the two-sided clamps.
    f68 = (float)(pow((double)g_15a3014, (double)dt) * (double)f68
                  + ((double)f64 + (double)lim) * (double)dt);
    f48 = f48 + f68 * dt;
    if (f48 > f34) {
        f48 = f34;
        if (f68 > 0.0f)
            f68 = 0.0f;
    }
    if (f30 > f48) {
        f48 = f30;
        if (0.0f > f68)
            f68 = 0.0f;
    }

    if (new44 > g_16a10d8)
        f44 = new44 - g_16a10d8;
    if (0.0f > f44)
        f44 = f44 + g_16a10d8;
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
void __stdcall CamCtl_Tick(int ms, int unused) {
    (void)unused;
    float f = (float)(unsigned int)ms * *(float*)0x13f9428;
    ((CamCtl*)0x15a3048)->Integrate(f);
    float k = *(float*)0x147da80;
    float d0 = g_cct0 - g_cc0;
    float d1 = g_cct4 - g_cc4;
    float d2 = g_cct8 - g_cc8;
    g_cc0 += d0 * k;
    g_cc4 += d1 * k;
    g_cc8 += d2 * k;
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
