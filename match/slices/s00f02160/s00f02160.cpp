// Slice s00f02160 -- scenario tutorial placement implementation (ctor/dtor, global teardown,
// update dispatch).  Region flags: /O2 /MD /Gy /TP
#include "types.h"
#include <math.h>

struct V3    { float x, y, z; };                    // EA::Vector3 (12 bytes)
struct Quat4 { float x, y, z, w; };                 // EA::Quaternion (16 bytes)
struct Plane4 { float x, y, z, w; void build(); };  // 0x00efd8e0 (plane ctor)
struct RectT  { void assign(const void*); };        // 0x00572600 ret 4
struct PM     { V3* f_b82110(Plane4*, V3*, V3*); };  // 0x00b82110 ret 0xc

extern void*   g_mgr;             // 0x016c7b88 (singleton pointer variable)
extern uint8_t g_015acb40;        // 0x015acb40
extern void*   g_Simulator;       // 0x016c7aa4
extern uint8_t g_15ad328[];       // 0x015ad328 (ScenarioTutorialsPlacement instance)
extern float   g_f16c7b98;        // 0x016c7b98
extern float   g_f16c7b9c;        // 0x016c7b9c
extern float   g_f16c7ba0;        // 0x016c7ba0

extern "C" void* __cdecl operator_new6(unsigned, const char*, int, int, const char*, int); // 0xf473a0
extern "C" void  __cdecl operator_delete_(void*);          // 0x00f47380
extern "C" void* __cdecl FUN_0067dd10();                    // 0x0067dd10  SP::App
extern "C" void  __cdecl FUN_00f31fd0(void*);               // 0x00f31fd0
extern "C" void* __cdecl FUN_00eebf80(void*);               // 0x00eebf80
extern "C" void* __cdecl FUN_00b18e00(void*);               // 0x00b18e00
extern "C" void* __cdecl FUN_00b3d350();                    // 0x00b3d350  SP::PlanetModel
extern "C" void* __cdecl FUN_00efc830(void*);               // 0x00efc830
extern "C" void* __cdecl FUN_007dcb00(void*, const void*, const void*); // 0x007dcb00
extern "C" void  __cdecl FUN_007c4900(void*, void*);        // 0x007c4900
extern "C" void  __cdecl FUN_00f01140(void*, void*, void*, int, int);   // 0x00f01140
extern "C" void  __cdecl FUN_00eef4b0(void*);               // 0x00eef4b0
extern "C" void  __cdecl FUN_00eec940(void*, int);          // 0x00eec940
extern "C" void  __cdecl FUN_00eee760(void*, void*);        // 0x00eee760
extern "C" void  __cdecl SP_QuaternionFromDirections(void*, const void*, const void*); // 0x698180

struct SW {                       // EA::Stopwatch at +0xb0
    void ctor(int, int);          // 0x93a560
    void SetTimeLimit(int, int);  // 0x93a480
};
struct X { void run(); };
extern "C" void f_eff0c0_ext();   // 0x00eff0c0
extern "C" void f_efd020_ext();   // 0x00efd020
extern "C" void f01c20_ext();     // 0x00f01c20
extern "C" void f00f80_ext();     // 0x00f00f80
struct Ref {
    virtual void v0();
    virtual void v4();
};
struct V4 {
    void* p0;
    int   f4;
    int   f8;
    float fC;
};

struct Vec;                       // 0x00dfb850
struct Big;
struct GObj;
struct WndC;
struct Vec30;
struct VecBox;

// eastl-style vector header helper.
struct Vec {
    void destroy(void* b, void* e);              // 0x00dfb850 ret 8
};

// The scenario/big data object obtained from FUN_00eebf80(Mgr->fC).
struct Big {
    void* h0;                     // +0x00
    char  pad04[0x0c];            // +0x04 .. +0x0f
    float rc10[4];                // +0x10  a RectT<float>
    float f20;                    // +0x20
    char  pad24[4];
    char* begin;                  // +0x28
    char* end;                    // +0x2c
    char  pad30[0x1b4];           // +0x30 .. +0x1e3
    float f1e4;                   // +0x1e4
    float v1e8[3];                // +0x1e8  a Vector3
    float rc1f4[4];               // +0x1f4  a RectT<float>
    float f204;                   // +0x204
    char  pad208[4];
    int*  p20c;                   // +0x20c
    void* assign(void* src);      // 0x00dfd3a0 ret 4  (copy into this)
};

// The scene object obtained from FUN_00eebf80(Mgr->f4) / FUN_00b18e00(Mgr->fC).
struct GObj {
    void* vtable;                 // +0x00
    char  pad04[0x1c];            // +0x04 .. +0x1f
    uint8_t b20;                  // +0x20
    void  f45970();               // 0x00f45970
    void  f45a80();               // 0x00f45a80
    void  f414b0();               // 0x00f414b0
    void  f42a00(void*);          // 0x00f42a00 ret 4
    GObj* f3e8a0(void*);          // 0x00f3e8a0 ret 4
    void  f3da90(void*, int);     // 0x00f3da90 ret 8
    void  f3bbd0(void*, int);     // 0x00f3bbd0 ret 8
    char  f253e0();               // 0x00f253e0
};

// The simulator singleton (0x016c7aa4); only the +0x74 GObj* is used here.
struct Sim {
    char  pad00[0x74];            // +0x00 .. +0x73
    GObj* p74;                    // +0x74
};
#define SIM ((Sim*)g_Simulator)

// Terrain/island object returned by WndC::v0c(0x74e0069) and FUN_00efc830().
struct Ter {
    char  pad000[0x128];          // +0x000 .. +0x127
    float f128;                   // +0x128
    float f12c;                   // +0x12c
    float f130;                   // +0x130
    float f134;                   // +0x134
    char  pad138[0x30];           // +0x138 .. +0x167
    float f168;                   // +0x168
    float f16c;                   // +0x16c
    float f170;                   // +0x170
    float f174;                   // +0x174
};

// A UTK window/object (Mgr->f8 / Mgr->f10 / Mgr->f14, and Mgr->fC).
struct SubWnd {                   // the inner window stored inline at WndC+0x34
    void* vtable;                 // +0x34
};
struct WndC {
    void* vtable;                 // +0x00
    char  pad04[0x30];            // +0x04 .. +0x33
    SubWnd sub34;                 // +0x34  (an inner window, has its own vtable)
    char  pad38[0x144];           // +0x38 .. +0x17b
    float f17c;                   // +0x17c
    char  pad180[0x18];           // +0x180 .. +0x197
    float f198;                   // +0x198
    float f19c;                   // +0x19c
    float f1a0;                   // +0x1a0
    float f1a4;                   // +0x1a4   (also rc198[3])
    float f1a8;                   // +0x1a8   (also rc1a4[1])
    float f1ac;                   // +0x1ac
    float f1b0;                   // +0x1b0
    float f_efc4c0();                     // 0x00efc4c0
    void  f_efce30(void*, void*, float);   // 0x00efce30 ret 0xc
};

// The eastl-style record container at Mgr+0x8c (and used for locals).
struct VecBox {
    void* begin;                  // +0x00
    void* end;                    // +0x04
    void* cap;                    // +0x08
    void* f0c;                    // +0x0c
    char  pad10[8];               // +0x10
    void  fromVec(void* src);     // 0x00f02d80 ret 4
    void  build(int n, void* src); // 0x00dfa400 ret 8
};

// The Mgr->0x30 vector helper object.
struct Vec30 {
    char  pad[4];
    bool  f_c68250(void*);        // 0x00c68250 ret 4
    void  check(void*, bool*);    // 0x00c688a0 ret 8
    void  f_c64940(void*);        // 0x00c64940 ret 4
};

// The global manager (points at 0x016c7b88).
struct Mgr {
    int   curIdx;                 // +0x00
    void* f4;                     // +0x04
    void* f8;                     // +0x08
    void* fC;                     // +0x0c
    void* f10;                    // +0x10
    void* f14;                    // +0x14
    char  pad18[0x10];            // +0x18 .. +0x27
    void* f28;                    // +0x28
    void* f2c;                    // +0x2c
    char  vec30[0x24];            // +0x30
    void* f54;                    // +0x54
    void* f58;                    // +0x58
    char  pad5c[0x0c];            // +0x5c .. +0x67
    int   f68;                    // +0x68
    char  pad6c[0x20];            // +0x6c .. +0x8b
    VecBox vec8c;                 // +0x8c
    uint8_t fA4;                  // +0xa4
};

#define MGR ((Mgr*)g_mgr)
#define VEC30 ((Vec30*)((char*)MGR + 0x30))

struct PL {
    void*  vtable;    // +0x00
    uint8_t b4;       // +0x04
    uint8_t b5;       // +0x05
    uint8_t b6;       // +0x06
    uint8_t b7;       // +0x07
    void*  pGame;     // +0x08  (the scene GObj)
    V4*    pC;        // +0x0c
    void*  p10;       // +0x10
    char   pad14[0x168];   // +0x14 .. +0x17b
    float  f17c;      // +0x17c
    void  f02160();              // 0x00f02160
    void  f02670();              // 0x00f02670
    void  f02700();              // 0x00f02700
    int   f02a10(int, int, float); // 0x00f02a10 ret 0xc
    void  f02b00();              // 0x00f02b00
    PL*   f02b80();              // 0x00f02b80
    PL*   ctor_2cd0();           // 0x00f02cd0
    void  f02c50();              // 0x00f02c50
    PL*   f02d30(int);           // 0x00f02d30 ret 4
    void  f02e00();              // 0x00f02e00
    void  f03010();              // 0x00f03010
    void  f030a0();              // 0x00f030a0
    void  SetObjectEx(void*);        // 0x00eff280 ret 4
    void  CommitObject(void*);       // 0x00eff360 ret 4
    void  AdjustPlacement(void*, float); // 0x00f01030 ret 8
    char  UpdatePlacement(void*);    // 0x00f00e50 ret 4
    void  MsgTeardown();             // 0x00f00d10
    void  ClearObject();             // 0x00eff3b0
    char  CheckObject(void*);        // 0x00efeae0 ret 8
};
extern void* g_vtbl_148b708[];   // 0x0148b708  (the PL vtable itself)
extern void* g_vtbl_148b788[];   // 0x0148b788  (the ScenarioTutorialsPlacement vtable)

// @ 0x00f02b80
PL* PL::f02b80()
{
    char* s = (char*)this;
    *(int*)(s + 0x00) = 0;
    *(int*)(s + 0x04) = 0;
    *(int*)(s + 0x08) = 0;
    *(int*)(s + 0x0c) = 0;
    *(int*)(s + 0x10) = 0;
    *(int*)(s + 0x14) = 0;
    *(int*)(s + 0x18) = 0;
    *(int*)(s + 0x1c) = 0;
    *(int*)(s + 0x20) = 0;
    *(int*)(s + 0x24) = 0;
    *(int*)(s + 0x28) = 0;
    *(int*)(s + 0x2c) = 0;
    *(int*)(s + 0x34) = 0;
    *(int*)(s + 0x38) = 0;
    *(int*)(s + 0x3c) = 0;
    *(int*)(s + 0x54) = 0;
    *(int*)(s + 0x58) = 0;
    *(int*)(s + 0x5c) = 0;
    *(int*)(s + 0x60) = 0;
    *(int*)(s + 0x8c) = 0;
    *(int*)(s + 0x90) = 0;
    *(int*)(s + 0x94) = 0;
    SW* sw = (SW*)(s + 0xb0);
    *(uint8_t*)(s + 0xa5) = 1;
    *(int*)(s + 0xa8) = 0;
    *(int*)(s + 0xac) = 0;
    sw->ctor(4, 0);
    sw->SetTimeLimit(0, 0);
    return this;
}

// @ 0x00f02cd0
PL* PL::ctor_2cd0()
{
    PL* self = this;
    *(void**)self = g_vtbl_148b708;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = 0;
    *(void**)((char*)self + 0x10) = 0;
    void* m = operator_new6(0x10, (const char*)0x148b76c, 0, 0, 0, 0);
    if (m) {
        FUN_00f31fd0(m);
        *(void**)((char*)self + 0xc) = m;
    } else {
        *(void**)((char*)self + 0xc) = 0;
    }
    self->f02670();
    return self;
}

// @ 0x00f02d30
PL* PL::f02d30(int flag)
{
    V4* p = pC;
    vtable = g_vtbl_148b708;
    if (p) {
        void* o = p->p0;
        if (o) ((Ref*)o)->v4();
        operator_delete_(p);
    }
    *(void**)((char*)this + 0xc) = 0;
    if (flag & 1) operator_delete_(this);
    return this;
}

// @ 0x00f02dd0
void __cdecl destroy_global_2dd0()
{
    X* p = (X*)g_mgr;
    if (p) {
        p->run();
        operator_delete_(p);
    }
    g_mgr = 0;
}

// @ 0x00f02670
void PL::f02670()
{
    void* sim = g_Simulator;
    *(void**)((char*)this + 8) = sim ? *(void**)((char*)sim + 0x18) : 0;
    void** vt = *(void***)this;
    ((void(__thiscall*)(void*, int))vt[0x18 / 4])(this, 0);
    b5 = 0;
    b6 = 0;
    b7 = 0;
    V4 tmp;
    tmp.p0 = 0; tmp.f4 = 0; tmp.f8 = 0; tmp.fC = 0;
    FUN_00f31fd0(&tmp);
    V4* dst = pC;
    void* old = dst->p0;
    void* nw = tmp.p0;
    if (nw != old) {
        if (nw) ((Ref*)nw)->v0();
        dst->p0 = nw;
        if (old) ((Ref*)old)->v4();
    }
    dst->f4 = tmp.f4;
    dst->f8 = tmp.f8;
    dst->fC = tmp.fC;
    if (tmp.p0) ((Ref*)tmp.p0)->v4();
}

// @ 0x00f02b00
void PL::f02b00()
{
    void** vt = *(void***)this;
    if (!((bool(__thiscall*)(void*))vt[0x38 / 4])(this)) return;
    void* a = FUN_0067dd10();
    void** va = *(void***)a;
    void* b = ((void*(__thiscall*)(void*))va[0x50 / 4])(a);
    void** vb = *(void***)b;
    void* c = ((void*(__thiscall*)(void*))vb[0x38 / 4])(b);
    if (c) {
        void** vc = *(void***)c;
        void* d = ((void*(__thiscall*)(void*, int))vc[0x0c / 4])(c, 0x11966ed);
        if (d) {
            if (*(uint8_t*)((char*)d + 0x319) == 0) return;
        }
    }
    if (*(int*)((char*)g_mgr + 0x10) != 0) { f00f80_ext(); f_eff0c0_ext(); return; }
    if (*(int*)((char*)g_mgr + 0xc) != 0) { f02700(); f_eff0c0_ext(); return; }
    if (b5) f00f80_ext();
    f_eff0c0_ext();
}

// @ 0x00f02c50
void PL::f02c50()
{
    void** vt = *(void***)this;
    if (!((bool(__thiscall*)(void*))vt[0x38 / 4])(this)) return;
    void* a = FUN_0067dd10();
    void** va = *(void***)a;
    void* b = ((void*(__thiscall*)(void*))va[0x50 / 4])(a);
    void** vb = *(void***)b;
    void* c = ((void*(__thiscall*)(void*))vb[0x38 / 4])(b);
    if (c) {
        void** vc = *(void***)c;
        void* d = ((void*(__thiscall*)(void*, int))vc[0x0c / 4])(c, 0x11966ed);
        if (d && *(uint8_t*)((char*)d + 0x319) == 0) return;
    }
    if (*(int*)((char*)g_mgr + 0x10) != 0) { f02160(); f_efd020_ext(); return; }
    if (*(int*)((char*)g_mgr + 0xc) != 0) { f01c20_ext(); }
    f_efd020_ext();
}

// ===================================================================
// Completion pass: the six previously-stubbed functions.
// ===================================================================

// @ 0x00f02a10
int PL::f02a10(int msg, int, float c)
{
    void* f4 = MGR->f4;
    switch (msg) {
    case 0:
        if (MGR->f10 == 0) {
            if (MGR->fC != 0) ClearObject();
        } else {
            MsgTeardown();
        }
        MGR->f68 = 0;
        ((void(__thiscall*)(PL*, int))((void**)vtable)[0x18 / 4])(this, 0);
        b6 = 0;
        return 1;
    case 1:
        if (b4 != 0 && MGR->fC == 0) {
            if (MGR->f10 != 0) { SetObjectEx(f4); return 1; }
            CommitObject(f4);
            return 1;
        }
        return 0;
    case 6:
        AdjustPlacement(f4, c);
        return 1;
    case 0xb:
        if (b4 != 0) return (int)(unsigned char)UpdatePlacement(f4);
        return 0;
    default:
        return 1;
    }
}

// @ 0x00f03010
void PL::f03010()
{
    Big* b = (Big*)pC;
    vtable = g_vtbl_148b788;
    if (b) {
        if (b->p20c && b->p20c[-1]) operator_delete_(b->p20c);
        ((Vec*)&b->begin)->destroy(b->begin, b->end);
        if (b->begin && ((int*)b->begin)[-1]) operator_delete_(b->begin);
        operator_delete_(b);
    }
    pC = 0;
}

// @ 0x00f02e00
void PL::f02e00()
{
    if (!g_mgr) return;
    Big* obj = (Big*)FUN_00eebf80(MGR->f4);
    if (!obj) return;
    GObj* scene = (GObj*)((GObj*)pGame)->f3e8a0(obj->h0);

    WndC* wf8 = (WndC*)MGR->f8;
    if (wf8) {
        void* w = ((void*(__thiscall*)(void*, unsigned))((void**)wf8->vtable)[0x0c / 4])(wf8, 0x76c67df);
        if (w && w != MGR->f28) {
            if (!VEC30->f_c68250(w)) return;
            (*(GObj*)pGame).f45970();
            if (scene->b20 == 0) {
                char* e = obj->begin + MGR->curIdx * 0x34;
                bool ok;
                VEC30->check(e + 0x1c, &ok);
                if (ok) *(int*)(e + 0x30) = 2;
            } else {
                int n = (int)((obj->end - obj->begin) / 0x34);
                for (int i = 0; i < n; ++i) {
                    char* e = obj->begin + i * 0x34;
                    bool ok;
                    VEC30->check(e + 0x1c, &ok);
                    if (ok) *(int*)(e + 0x30) = 2;
                }
            }
            (*(GObj*)pGame).f45a80();
            if (MGR->f10 == MGR->f8 && MGR->f10) {
                void* p = MGR->f10;
                MGR->f10 = 0;
                (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p);
            }
            if (MGR->f8) {
                void* p = MGR->f8;
                MGR->f8 = 0;
                (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p);
            }
            return;
        }
    }

    (*(GObj*)pGame).f45970();
    VecBox local;
    local.fromVec(&MGR->vec8c);
    ((void(__thiscall*)(PL*, int))((void**)vtable)[0x20 / 4])(this, 0);
    (*(GObj*)pGame).f42a00(obj);
    if (g_015acb40) FUN_00eec940(&local, 0);
    FUN_00eef4b0(&local);
    (*(GObj*)pGame).f414b0();
    (*(GObj*)pGame).f45a80();
    if (local.begin && ((int*)local.begin)[-1]) operator_delete_(local.begin);
}

// @ 0x00f030a0
void PL::f030a0()
{
    if (!g_mgr) return;
    Big* obj = (Big*)FUN_00eebf80(MGR->f4);
    if (!obj) return;
    (*(GObj*)pGame).f45970();

    VecBox local;
    int n = (int)(((char*)MGR->vec8c.end - (char*)MGR->vec8c.begin) >> 5);
    local.build(n, &MGR->vec8c.f0c);
    FUN_00f01140(&local, MGR->vec8c.begin, MGR->vec8c.end,
                 (int)local.end, (int)local.begin);
    local.cap = local.begin;
    ((Big*)pC)->assign(obj);

    ((void(__thiscall*)(PL*, int))((void**)vtable)[0x20 / 4])(this, 0);
    (*(GObj*)pGame).f42a00(obj);
    if (g_015acb40) FUN_00eec940(&local, 0);
    FUN_00eef4b0(&local);
    (*(GObj*)pGame).f414b0();
    (*(GObj*)pGame).f45a80();
    if (local.begin && ((int*)local.begin)[-1]) operator_delete_(local.begin);
}

// @ 0x00f02700
void PL::f02700()
{
    void* fC = MGR->fC;
    void* it = FUN_00b18e00(fC);
    FUN_00eebf80(fC);

    Plane4 plane;
    plane.build();                       // 0x00efd8e0

    void* app = FUN_0067dd10();
    V3 a, b;
    ((void(__thiscall*)(void*, V3*, V3*))((void**)app)[0x58 / 4])(app, &a, &b);
    FUN_007c4900(&a, &b);
    a.x += plane.x; a.y += plane.y; a.z += plane.z;

    void* pm = FUN_00b3d350();
    V3* res = ((PM*)pm)->f_b82110(&plane, &a, &b);
    if (res->x == g_f16c7b98 && res->y == g_f16c7b9c && res->z == g_f16c7ba0)
        return;

    V3 target = *res;
    V3* pFrom = (V3*)((void*(__thiscall*)(void*))((void**)it)[0x2c / 4])(it);   // slot 0x2c
    V3 from = *pFrom;
    Quat4* pw = (Quat4*)((void*(__thiscall*)(void*))((void**)it)[0x30 / 4])(it); // slot 0x30
    Quat4 q;
    SP_QuaternionFromDirections(&q, &from, &target);

    float t0 = pw->z * q.y - pw->y * q.z;
    float t1 = q.z * pw->x - pw->z * q.x;
    float t2 = pw->y * q.x - q.y * pw->x;
    float nx = (q.w * pw->x + pw->w * q.x) + t0;
    float ny = (q.w * pw->y + pw->w * q.y) + t1;
    float nz = (q.w * pw->z + pw->w * q.z) + t2;
    float nw = pw->w * q.w - ((pw->z * q.z + pw->y * q.y) + pw->x * q.x);
    float inv = 1.0f / sqrtf(ny * ny + (nz * nz + (nx * nx + nw * nw)));
    Quat4 norm;
    norm.x = inv * nx; norm.y = inv * ny; norm.z = inv * nz; norm.w = inv * nw;

    ((void(__thiscall*)(void*, V3*))((void**)it)[0x38 / 4])(it, &target);     // slot 0x38
    ((void(__thiscall*)(void*, Quat4*))((void**)it)[0x3c / 4])(it, &norm);    // slot 0x3c
}

// @ 0x00f02160
void PL::f02160()
{
    Mgr* m = MGR;
    if (!m->fC || !m->f10) {
        if (g_015acb40 && m->f4) SIM->p74->f3bbd0(m->f4, 0);
        return;
    }

    Big* eso = (Big*)FUN_00eebf80(m->fC);
    void* w10 = m->f10;
    int state = (int)((void*(__thiscall*)(void*))((void**)*(void**)w10)[0x38 / 4])(w10);

    if (state == 0x771ad6a) {
        WndC* wp = (WndC*)m->f10;
        ((void(__thiscall*)(void*))((void**)wp->vtable)[0x5c / 4])(wp);
        if ((void*)wp == m->f2c) {
            GObj* sc = SIM->p74->f3e8a0(eso->h0);
            if (sc->b20 == 0) {
                *(float*)(eso->begin + m->curIdx * 0x34) = wp->f17c;
            } else {
                int n = (int)((eso->end - eso->begin) / 0x34);
                for (int i = 0; i < n; ++i)
                    *(float*)(eso->begin + i * 0x34) = wp->f17c;
            }
        } else if ((void*)wp == m->f54) {
            void** vc = *(void***)m->fC;
            Ter* t = (Ter*)((void*(__thiscall*)(void*, unsigned))vc[0x0c / 4])(m->fC, 0x74e0069);
            if (t) eso->f1e4 = wp->f_efc4c0() * (t->f16c - t->f168) + t->f168;
            Ter* r = (Ter*)FUN_00efc830(m->fC);
            if (!r) return;
            eso->f1e4 = wp->f_efc4c0() * (r->f12c - r->f128) + r->f128;
        } else if ((void*)wp == m->f58) {
            void** vc = *(void***)m->fC;
            Ter* t = (Ter*)((void*(__thiscall*)(void*, unsigned))vc[0x0c / 4])(m->fC, 0x74e0069);
            if (t) eso->f20 = wp->f_efc4c0() * (t->f174 - t->f170) + t->f170;
            Ter* r = (Ter*)FUN_00efc830(m->fC);
            if (!r) return;
            eso->f20 = wp->f_efc4c0() * (r->f134 - r->f130) + r->f130;
        }
        return;
    }

    if (state == 0x76c67df) {
        WndC* wp = (WndC*)m->f10;
        ((void(__thiscall*)(void*))((void**)wp->vtable)[0x5c / 4])(wp);
        GObj* sc = ((GObj*)pGame)->f3e8a0(eso->h0);
        if (sc->f253e0() != 0) {
            void* sub = ((void*(__thiscall*)(void*))((void**)wp->sub34.vtable)[0x2c / 4])(&wp->sub34);
            Quat4 q;
            SP_QuaternionFromDirections(&q, eso->v1e8, sub);
            eso->v1e8[0] = ((float*)sub)[0];
            eso->v1e8[1] = ((float*)sub)[1];
            eso->v1e8[2] = ((float*)sub)[2];
            float loA, loB;
            void* r = FUN_007dcb00(&loA, &loB, eso->rc1f4);
            ((RectT*)eso->rc1f4)->assign(r);
            ((WndC*)m->fC)->f_efce30(eso->v1e8, eso->rc1f4, eso->f204);
            return;
        }
        VEC30->f_c64940(wp);
        if (sc->b20 == 0) {
            char* e = eso->begin + m->curIdx * 0x34;
            bool ok;
            VEC30->check(e + 0x1c, &ok);
            if (ok) *(int*)(e + 0x30) = 2;
        } else {
            int n = (int)((eso->end - eso->begin) / 0x34);
            for (int i = 0; i < n; ++i) {
                char* e = eso->begin + i * 0x34;
                bool ok;
                VEC30->check(e + 0x1c, &ok);
                if (ok) *(int*)(e + 0x30) = 2;
            }
        }
        return;
    }

    if (state == 0x7a81824) {
        WndC* wp = (WndC*)m->f10;
        ((void(__thiscall*)(void*))((void**)wp->vtable)[0x5c / 4])(wp);
        if ((void*)wp == m->f14) {
            eso->rc1f4[0] = wp->f1a4; eso->rc1f4[1] = wp->f1a8;
            eso->rc1f4[2] = wp->f1ac; eso->rc1f4[3] = wp->f1b0;
            ((WndC*)m->fC)->f_efce30(eso->v1e8, eso->rc1f4, eso->f204);
        } else {
            eso->rc10[0] = wp->f1a4; eso->rc10[1] = wp->f1a8;
            eso->rc10[2] = wp->f1ac; eso->rc10[3] = wp->f1b0;
        }
        ((GObj*)pGame)->f3da90(eso, 0);
        if (g_015acb40) FUN_00eee760(eso, &MGR->vec8c);
        char chk = ((PL*)g_15ad328)->CheckObject(m->fC);
        SIM->p74->f3bbd0(m->fC, chk == 0);
        return;
    }

    if (state == 0x7abdd8d) {
        WndC* wp = (WndC*)m->f10;
        ((void(__thiscall*)(void*))((void**)wp->vtable)[0x5c / 4])(wp);
        eso->rc10[0] = wp->f198; eso->rc10[1] = wp->f19c;
        eso->rc10[2] = wp->f1a0; eso->rc10[3] = wp->f1a4;
        ((GObj*)pGame)->f3da90(eso, 0);
        char chk = ((PL*)g_15ad328)->CheckObject(m->fC);
        SIM->p74->f3bbd0(m->fC, chk == 0);
        return;
    }
}