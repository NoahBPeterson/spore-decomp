// Slice s00edcfc0 -- 0x00edcfc0..0x00eddf30  (/O2 /MD /Gy /TP /fp:fast)
//
// Helpers of the Spore scenario editor's script UI
// (UI::cScenarioEditModeScriptUI).  Several functions are not members: they are
// plain helpers/constructors taking the editor object on the stack.  The object
// is an MI UI aggregate: vtable at +0, a "view" subobject at +0x14, a subobject
// at +0x4c, ref-counted UI element pointers at +0x18..+0x48 and a set of audio
// state fields at +0x2c/+0x30 / +0x34.
//
// Byte-exact where reproducible; every function below is a complete behavioral
// reconstruction.
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------- globals
extern void* DAT_016c7aa4;          // outer app object (-> mgr at +0x74, srv at +0x7c)
extern int   DAT_0148a518[];        // table of element indices
extern int   DAT_0148a544[];        // table of element ids
extern int   DAT_0148a574[];
extern int   DAT_0148a5a4[];
extern int   DAT_0148a5d4[];
extern int   DAT_0148a604[];
extern int   DAT_0148a634[];
extern int   DAT_0148a664[];

struct Mgr {
    char pad00[0x10];
    int  f10;                        // +0x10  scenario object base
    int F3e8a0(int);
    int F3dc70(int);
    int F3bcb0();
    int F3be60(int);
    bool F40500(int*, int, int);
    bool F3e6d0(int, int*, int, int);
    bool F3c750(int*, int);
    bool F420d0(int, int*, int, int, int);
    int F3bf60();
    int F3bf70();
    int F254d0();
};
struct Mgr14 { char pad[4]; int F3be60(int); };
struct Mgr74 { void* p74; void* p78; void* p7c; };

#define MGR()  (*(Mgr**)((char*)DAT_016c7aa4 + 0x74))
#define SRV()  (*(void**)((char*)DAT_016c7aa4 + 0x7c))

// virtual-call helpers (vtable slot addressed by byte offset)
#define VTP(p)          (*(void***)(p))
#define VC0(p,off)      (((int (__thiscall*)(void*))       VTP(p)[(off)/4])((void*)(p)))
#define VC1(p,off,a)    (((int (__thiscall*)(void*,int))   VTP(p)[(off)/4])((void*)(p),(int)(a)))
#define VC2(p,off,a,b)  (((int (__thiscall*)(void*,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b)))
#define VC3(p,off,a,b,c)(((int (__thiscall*)(void*,int,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b),(int)(c)))
#define VCP0(p,off)     (((void*(__thiscall*)(void*))     VTP(p)[(off)/4])((void*)(p)))
#define VCP1(p,off,a)   (((void*(__thiscall*)(void*,int)) VTP(p)[(off)/4])((void*)(p),(int)(a)))
#define VCP2(p,off,a,b) (((void*(__thiscall*)(void*,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b)))
#define VCP3(vt,off,p,a,b) (((void*(__thiscall*)(void*,int,int))((void**)(vt))[(off)/4])((void*)(p),(int)(a),(int)(b)))

// ---------------------------------------------------------------- shared stubs
struct cString { void Load(int, int, int); };
struct Element { char pad[4]; void SetChecked(int a, int b); };
struct Checker { char pad[4]; bool F254d0(); int F25330(); int F25490(); };
struct Sink    { char pad[4]; int F00830d10(int); };
struct Notify  { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void va(); virtual void vb(); virtual void vc(); virtual void vd(); virtual void ve(); virtual void vf(); virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4(); virtual void w5(); virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9(); virtual void wa(); virtual void wb(); virtual void wc(); virtual void wd(); virtual void we(); virtual void wf(); virtual void x0(); virtual void x1(); virtual void x2(); virtual void x3(); virtual void x4(); virtual void x5(); virtual void x6(); virtual void x7(); virtual void x8(); virtual void x9(); virtual void xa(); virtual void xb(); virtual void xc(); virtual void xd(); virtual void xe(); virtual void xf(); virtual void y0(); virtual void y1(); virtual void y2(); virtual void y3(); virtual void y4(); virtual void y5(); virtual void y6(); virtual void y7(); virtual void y8(); virtual void y9(); virtual void ya(); virtual void yb(); virtual void yc(); virtual void yd(); virtual void ye(); virtual void yf(); virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3(); virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7(); virtual void z8(); virtual void z9(); virtual void za(); virtual void zb(); virtual void zc(); virtual void zd(); virtual void ze(); virtual void zf(); };

// editor object: only the fields touched here
struct C {
    char pad00[0x18];
    void* p18;                       // +0x18   ref-counted object (dtor via +4)
    char pad1c[0x04];                // +0x1c   (handled as separate dwords below)
    int  p20;                        // +0x20   ref-counted
    int  p24;                        // +0x24
    int  p28;                        // +0x28
    int  v2c;                        // +0x2c   selected verb/index
    int  p30;                        // +0x30   audio handle
    int  vec34[3];                   // +0x34   Vector3
    char pad40[0x4c-0x40];
    char sub4c[0x70];                // +0x4c   embedded subobject (FUN_00e0a390)
    void* pbc;                       // +0xbc
    void* pc0;                       // +0xc0
    char c4;                         // +0xc4
    char c5;                         // +0xc5
    char c6;                         // +0xc6
    char padc7;
    int  c8;                         // +0xc8
    char padcc[0xd0-0xcc];
    void* pd0;                       // +0xd0
    void* pd4;                       // +0xd4
    void* pd8;                       // +0xd8
    char paddc[0xf0-0xdc];
    int  hf0;                        // +0xf0   message handler id
    int  hf4, hf8, hfc, h100;
    int  v104;                       // +0x104
    int  v108;                       // +0x108

    void f00edd440(float* outA, float* outB);
    void f00edda20();
    void f00eddb00();
    void f00eddbe0();
    void f00eddc50(int* param_1);
    void f00edde30(int param);
    void f00edde90();
};

// ============================================================ 0x00edcfc0
struct RatioObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual int GetStart(); virtual void s9(); virtual int GetA();
    virtual void s11(); virtual int GetB();
};
struct Root {
    virtual void r0(); virtual void r1(); virtual void r2(); virtual RatioObj* Find(int);
};
// @ 0x00edcfc0
float __cdecl f00edcfc0(int* param_1)
{
    if (param_1 != 0) {
        RatioObj* p = ((Root*)param_1)->Find(0xf00a8a0);
        if (p != 0) {
            int a = p->GetA();
            int b = p->GetB();
            int c = p->GetStart();
            return (float)(c - a) / (float)(b - a);
        }
    }
    return 0.0f;
}

// ============================================================ 0x00edd020
extern "C" int FUN_00eece20(int);
extern "C" int FUN_00efc520();
// @ 0x00edd020
void __cdecl f00edd020(int* param_1, int param_2, cString* param_3)
{
    int iVar3 = *param_1;
    int h;
    Mgr* m;
    if (param_2 == -2)
        goto lab8e;
    m = MGR();
    h = FUN_00eece20(m->F3e8a0(param_2));
    switch (h) {
    case (int)0xe34e8a60: goto lab8e;
    case (int)0xb10e526f:
    case (int)0xd37c1045:
    case 0x5b3d1d0d:      goto laba4;
    case (int)0xcf56099a:
    case 0x6031c03a:      goto lab108;
    default: return;
    }
lab8e:
    m = MGR();
    param_3->Load(0x21851ebe, DAT_0148a574[iVar3], 0);
    if (iVar3 == 2 && param_2 != -2) {
        int a = FUN_00efc520();
        int b = m->F3e8a0(param_2);
        int* p = (int*)(a * 0x4e0 + *(int*)(b + 0x70));
        if (p != 0 && *(char*)((char*)p + 2) != 0)
            param_3->Load(0x21851ebe, 0x7b5154c, 0);
    }
    return;
laba4:
    param_3->Load(0x21851ebe, DAT_0148a5a4[iVar3], 0);
    return;
lab108:
    param_3->Load(0x21851ebe, DAT_0148a5d4[iVar3], 0);
    return;
}

// ============================================================ 0x00edd130
// @ 0x00edd130
void __cdecl f00edd130(int* param_1, cString* param_2)
{
    void* srv = SRV();
    int iVar2 = param_1[1];
    int iVar1;
    int h;
    if (srv != 0)
        *(int**)((char*)srv + 0x10) = param_1;
    iVar1 = MGR()->F3e8a0(iVar2);
    if (iVar2 == -2 || iVar1 == 0) {
lab_b0:
        param_2->Load(0x21851ebe, DAT_0148a604[*param_1], 0);
        if (*param_1 == 2 && iVar1 != 0) {
            int r = FUN_00efc520() * 0x4e0 + *(int*)(iVar1 + 0x70);
            if (r != 0 && *(char*)(r + 2) != 0) {
                param_2->Load(0x21851ebe, DAT_0148a634[*param_1], 0);
                return;
            }
        }
        return;
    }
    h = FUN_00eece20(iVar1);
    switch (h) {
    case (int)0xe34e8a60: goto lab_b0;
    case (int)0xb10e526f:
    case (int)0xd37c1045:
    case 0x5b3d1d0d:      goto lab192;
    case (int)0xcf56099a:
    case 0x6031c03a:      goto lab215;
    default: return;
    }
lab192:
    param_2->Load(0x21851ebe, DAT_0148a634[*param_1], 0);
    return;
lab215:
    param_2->Load(0x21851ebe, DAT_0148a664[*param_1], 0);
    return;
}

// ============================================================ 0x00edd240
struct V3 { int x, y, z; };
struct PropObj { V3* F25190(void* a, V3* b); };
// @ 0x00edd240
V3* __cdecl f00edd240(V3* out, int id)
{
    out->x = 0;
    out->y = 0;
    out->z = 0;
    if (id == -2) {
        V3* p = (V3*)MGR()->F3bcb0();
        out->x = p->x;
        out->z = p->z;
        out->y = 0x2f7d0004;
    } else {
        PropObj* v = (PropObj*)MGR()->F3e8a0(id);
        if (v != 0) {
            V3 tmp;
            V3* r = v->F25190(&tmp, out);
            *out = *r;
        }
    }
    return out;
}

// ============================================================ 0x00edd2d0
extern "C" int FUN_00efc8f0();
extern "C" int FUN_00efe5b0();
// @ 0x00edd2d0
bool __cdecl f00edd2d0(int* param_1)
{
    bool result = false;
    int* p = (int*)FUN_00efc8f0();
    if (p != 0) {
        Mgr* m = MGR();
        int u = FUN_00efe5b0();
        if (m->F3dc70(u) != 0) {
            *param_1 = *p;
            result = true;
        }
    }
    return result;
}

// ============================================================ 0x00edd310
// @ 0x00edd310
void __cdecl f00edd310(int* param_1, int param_2, int param_3)
{
    *param_1 = param_2;
    param_1[3] = 1;
    Checker* v = (Checker*)MGR()->F3e8a0(param_3);
    if (param_2 == 9 && v != 0) {
        if (!v->F254d0()) {
            param_1[2] = param_3;
            param_1[1] = -1;
            return;
        }
    }
    param_1[1] = param_3;
    param_1[2] = -1;
}

// ============================================================ 0x00edd370
// @ 0x00edd370
bool __cdecl f00edd370(int* param_1, int param_2, int param_3)
{
    bool ok = false;
    int* p1 = param_1;
    Mgr* m = MGR();
    if (m->F40500(p1, FUN_00efc520(), 0)) {
        if (m->F3e6d0(param_2, p1, FUN_00efc520(), 0)) {
            ok = true;
            if (m->F3c750(p1, -1)) {
                p1[0x61] = 0x17;
                return false;
            }
            if (m->F420d0(FUN_00efc520(), p1, param_3, 0, 0)) {
                p1[0x61] = 0x18;
                return false;
            }
            if (*p1 == 5) {
                int a = m->F3bf60();
                int b = m->F3bf70();
                if (a - b < 1) {
                    p1[0x61] = 0x16;
                    return false;
                }
            }
        }
    }
    return ok;
}

// ============================================================ 0x00edd440
struct R6 { float x0, y0, z0, x1, y1, z1; };
struct R4 { float x, y, w, h; };
extern "C" void* SP_App();
extern "C" int   FUN_007c4180(void* self);
extern "C" void  SPUIHelpers_GetMainWindowArea(R4* out);
extern float g_1485720;
extern float g_1471064;

// @ 0x00edd440
void C::f00edd440(float* outA, float* outB)
{
    void* obj = *(void**)((char*)this + 0xc);
    if (obj == 0)
        return;
    R6 local;
    R6* r = (R6*)VCP1(obj, 0x6c, (int)&local);
    float cx = (r->x0 + r->x1) * 0.5f;
    float cy = (r->y1 + r->y0) * 0.5f;
    float cz = (r->z1 + r->z0) * 0.5f;
    float c[3] = { cx, cy, cz };
    void* app = SP_App();
    float s[3];
    float* res = (float*)VCP2(app, 0x58, (int)s, (int)c);
    FUN_007c4180(res);
    R4 area;
    SPUIHelpers_GetMainWindowArea(&area);
    float t = (s[0] + g_1485720) * g_1471064;
    if (t <= 0.0f) t = 0.0f;
    if (g_1485720 <= t) t = g_1485720;
    *outA = t * area.w;
    t = (g_1485720 - s[0]) * g_1471064;
    if (t <= 0.0f) t = 0.0f;
    if (g_1485720 <= t) t = g_1485720;
    *outB = t * area.h;
}

// ============================================================ 0x00edd580
extern void* VT_14426a0;
extern void* VT_13eb394;
extern void* VT_140b5a0;
extern void* VT_148a80c;
extern void* VT_148a7f0;
extern void* VT_148a7e4;
extern void* VT_148a7dc;
extern void* VT_148a7d8;
extern void* VT_13eb938;
extern void* VT_13ec458;
extern "C" void FUN_00e0a390(void*);
extern "C" void FUN_00e0a400(void*);
extern "C" void* SP_MessageServer();
// @ 0x00edd580
void* __fastcall f00edd580(C* self)
{
    char* t = (char*)self;
    *(int*)(t + 4) = 0;
    *(void**)(t + 8) = &VT_14426a0;
    *(void**)(t + 0x10) = &VT_13eb394;
    *(void**)(t + 0x14) = &VT_140b5a0;
    *(void**)(t) = &VT_148a80c;
    *(void**)(t + 8) = &VT_148a7f0;
    *(void**)(t + 0xc) = &VT_148a7e4;
    *(void**)(t + 0x10) = &VT_148a7dc;
    *(void**)(t + 0x14) = &VT_148a7d8;
    *(int*)(t + 0x18) = 0;
    *(int*)(t + 0x1c) = 0;
    *(int*)(t + 0x20) = 0;
    *(int*)(t + 0x24) = 0;
    *(int*)(t + 0x28) = 0;
    *(int*)(t + 0x2c) = 0;
    *(int*)(t + 0x30) = 0;
    *(int*)(t + 0x34) = 0;
    *(int*)(t + 0x38) = 0;
    *(int*)(t + 0x3c) = 0;
    *(int*)(t + 0x40) = 0;
    *(int*)(t + 0x44) = 0;
    *(int*)(t + 0x48) = 0;
    FUN_00e0a390(t + 0x4c);
    *(int*)(t + 0xbc) = 0;
    *(int*)(t + 0xc0) = 0;
    *(char*)(t + 0xc4) = 0;
    *(char*)(t + 0xc5) = 0;
    *(char*)(t + 0xc6) = 0;
    *(int*)(t + 0xc8) = -1;
    *(int*)(t + 0xd0) = 0;
    *(int*)(t + 0xd4) = 0;
    *(int*)(t + 0xd8) = 0;
    *(int*)(t + 0xf0) = 0;
    *(int*)(t + 0xf4) = 0;
    *(int*)(t + 0xf8) = 0;
    *(int*)(t + 0xfc) = 0;
    *(int*)(t + 0x100) = 0;
    *(int*)(t + 0x104) = 0x867a9ee9;
    *(int*)(t + 0x108) = 0;
    void* ms = SP_MessageServer();
    if (ms != 0) {
        void* ms2 = SP_MessageServer();
        VC2(ms2, 0x24, (int)(t + 0x10), 0x65ff54a);
    }
    return self;
}

// ============================================================ 0x00edd6b0
extern "C" void EA_Messaging_RemoveHandler(int, int, int, int, int);
// @ 0x00edd6b0
void __fastcall f00edd6b0(C* self)
{
    char* t = (char*)self;
    *(void**)(t) = &VT_148a80c;
    *(void**)(t + 8) = &VT_148a7f0;
    *(void**)(t + 0xc) = &VT_148a7e4;
    *(void**)(t + 0x10) = &VT_148a7dc;
    *(void**)(t + 0x14) = &VT_148a7d8;
    void* ms = SP_MessageServer();
    if (ms != 0) {
        void* ms2 = SP_MessageServer();
        VC3(ms2, 0x2c, (int)(t + 0x10), 0x65ff54a, 0xffffd8f1);
    }
    int h = *(int*)(t + 0xf0);
    if (h != 0) {
        *(int*)(t + 0xf0) = 0;
        EA_Messaging_RemoveHandler(h, *(int*)(t + 0xf4), *(int*)(t + 0xf8), *(int*)(t + 0xfc), *(int*)(t + 0x100));
    }
    if (*(int*)(t + 0xd8) != 0) VC0(*(void**)(t + 0xd8), 4);
    if (*(int*)(t + 0xd4) != 0) VC0(*(void**)(t + 0xd4), 4);
    if (*(int*)(t + 0xc0) != 0) VC0(*(void**)(t + 0xc0), 4);
    if (*(int*)(t + 0xbc) != 0) VC0(*(void**)(t + 0xbc), 4);
    FUN_00e0a400(t + 0x4c);
    if (*(int*)(t + 0x48) != 0) VC0(*(void**)(t + 0x48), 8);
    if (*(int*)(t + 0x44) != 0) VC0(*(void**)(t + 0x44), 8);
    if (*(int*)(t + 0x40) != 0) VC0(*(void**)(t + 0x40), 8);
    if (*(int*)(t + 0x28) != 0) VC0(*(void**)(t + 0x28), 4);
    if (*(int*)(t + 0x24) != 0) VC0(*(void**)(t + 0x24), 4);
    if (*(int*)(t + 0x20) != 0) VC0(*(void**)(t + 0x20), 4);
    if (*(int*)(t + 0x1c) != 0) VC0(*(void**)(t + 0x1c), 4);
    if (*(int*)(t + 0x18) != 0) VC0((void*)(*(int*)(t + 0x18) + 4), 8);
    *(void**)(t + 0x10) = &VT_13eb394;
    *(void**)(t + 8) = &VT_13eb938;
    *(void**)(t) = &VT_13ec458;
}

// ============================================================ 0x00edd810
extern "C" void* SP_WindowManager();
extern "C" void* EA_UTFWin_MultiHeapObject_operator_new(int);
struct LitMgr { char pad[4]; void* GetWorldMainWindow(); };
// @ 0x00edd810
void __fastcall f00edd810(C* self)
{
    char* t = (char*)self;
    if (*(int*)(t + 0xd4) == 0)
        return;
    void* wm = SP_WindowManager();
    VC2(wm, 0x5c, 1, *(int*)(t + 0xd4));
    void* alloc = EA_UTFWin_MultiHeapObject_operator_new(0x5b598fa);
    void* mw = ((LitMgr*)alloc)->GetWorldMainWindow();
    VC1(mw, 0xdc, *(int*)(t + 0xd4));
    VC1(*(void**)(t + 0xd8), 0xd8, *(int*)(t + 0xd4));
    void* pd8 = *(void**)(t + 0xd8);
    if (pd8 != 0) {
        *(int*)(t + 0xd8) = 0;
        VC0(pd8, 4);
    }
    VC1(*(void**)(t + 0xd4), 0x6c, (int)(t + 0xdc));
    VC1(*(void**)(t + 0xd4), 0x5c, *(int*)(t + 0xec));
    VC1(*(void**)(t + 0xd4), 0x78, 0x747d67b);
    void* pd4 = *(void**)(t + 0xd4);
    if (pd4 != 0) {
        *(int*)(t + 0xd4) = 0;
        VC0(pd4, 4);
    }
}

// ============================================================ 0x00edd8f0
struct Base { char pad[4]; int F26360(); };
void __stdcall f00edd8f0(void* p)
{
    if (p != 0)
        VC2(p, 0x7c, 1, 1);
    int id = VC0(p, 0x1c);
    Mgr* m = MGR();
    int val;
    void* z;
    if (id == 0x71725b0) {
        val = ((Base*)((char*)m->f10 + 0x7c))->F26360();
        z = VCP2(p, 0xf0, 0x7172970, 1);
    } else if (id == 0x7172600) {
        int v0 = ((Base*)((char*)m->f10 + 0xb8))->F26360();
        void* q = VCP2(p, 0xf0, 0x7172950, 1);
        if (q != 0) {
            void* r = VCP1(q, 0xc, 0xcf428691);
            if (r != 0) {
                VC1(r, 0x68, 0xc0);
                VC2(r, 0x60, v0, 0);
            }
        }
        val = ((Base*)((char*)m->f10 + 0xf4))->F26360();
        z = VCP2(p, 0xf0, 0x7172960, 1);
    } else {
        return;
    }
    if (z != 0) {
        void* r = VCP1(z, 0xc, 0xcf428691);
        if (r != 0) {
            VC1(r, 0x68, 0xc0);
            VC2(r, 0x60, val, 0);
        }
    }
}

// ============================================================ 0x00edda20
extern "C" void SetGlobalProperty(int, float);
extern "C" void FUN_00572020(int, int);
// @ 0x00edda20
void C::f00edda20()
{
    if (p30 != 0) {
        SetGlobalProperty(0x8dff6314, 0.0f);
        FUN_00572020(p30, 0);
        p30 = 0;
    }
    if (p20 != 0) {
        void* a = VCP2((void*)p20, 0xf0, 0x447c040, 1);
        if (a != 0) VC2(a, 0x7c, 1, v2c != 0);
        void* b = VCP2((void*)p20, 0xf0, 0x5ca82b7, 1);
        if (b != 0) VC2(b, 0x7c, 1, v2c == 0);
        void* c = VCP2((void*)p20, 0xf0, 0x7ccbd48, 1);
        if (c != 0) VC2(c, 0x7c, 1, v2c != 0);
    }
}

// ============================================================ 0x00eddb00
extern "C" void* EA_Audio_GetSystemAT();
extern "C" void* SP_AudioSystem();
extern "C" void FUN_00657240(int, int, float*);
extern "C" void SP_EditorUtils_PlayEditorSound(int, int, int, float);
extern "C" void FUN_006572b0(int);
// @ 0x00eddb00
void C::f00eddb00()
{
    if (v2c == 0 || p30 != 0)
        return;
    SetGlobalProperty(0x8dff6314, 1.0f);
    void* sys = EA_Audio_GetSystemAT();
    int h;
    if (sys == 0) h = 0;
    else h = VC0(sys, 0x20);
    p30 = h;
    void* as = (void*)VC0(SP_AudioSystem(), 0x1c);
    as = (void*)VC1(as, 0x10, 0);
    float v[3];
    v[0] = *(float*)((char*)as);
    v[1] = *(float*)((char*)as + 4);
    v[2] = *(float*)((char*)as + 8);
    FUN_00657240(v2c, p30, v);
    SP_EditorUtils_PlayEditorSound(p30, 0x12d2a4d4, 0, 0.0f);
    SP_EditorUtils_PlayEditorSound(p30, 0xba134192, 0, 0.0f);
    FUN_006572b0(p30);
}

// ============================================================ 0x00eddbE0
// @ 0x00eddbe0
void C::f00eddbe0()
{
    if (p30 != 0) {
        SetGlobalProperty(0x8dff6314, 0.0f);
        FUN_00572020(p30, 0);
        p30 = 0;
    }
    v2c = 0;
    Mgr* m = MGR();
    if (m != 0) {
        int r = m->F3be60(FUN_00efc520());
        if (r != 0)
            *(int*)(r + 0x80) = 0;
    }
    f00edda20();
}

// ============================================================ 0x00eddc50
extern "C" void* EA_Audio_Eapd_Debug_ObjectError();
extern "C" int  SP_GetPropertyAsText(void*, int, void*);
extern "C" void SPUIHelpers_SetTooltipText(void*);
// @ 0x00eddc50
void C::f00eddc50(int* param_1)
{
    if (p30 != 0) {
        SetGlobalProperty(0x8dff6314, 0.0f);
        FUN_00572020(p30, 0);
        p30 = 0;
    }
    vec34[0] = param_1[0];
    vec34[1] = param_1[1];
    vec34[2] = param_1[2];
    void* local = 0;
    void* e = EA_Audio_Eapd_Debug_ObjectError();
    if (local != 0) {
        local = 0;
        VC0(local, 4);
    }
    void* prop = 0;
    VCP3(VTP(e), 0xc, e, (int)param_1, (int)&prop);
    if (prop != 0) {
        cString text;
        if (SP_GetPropertyAsText(prop, 0x71e9bd1, &text)) {
            void* win = *(void**)((char*)this + 0x20);
            void* tt = VCP2(win, 0xf0, 0x7ccbd48, 1);
            SPUIHelpers_SetTooltipText(tt);
        }
        if (prop != 0) {
            char rr = ((char(__thiscall*)(void*, int, void*))VTP(prop)[0x24/4])(prop, 0xb6878619, 0);
            (void)rr;
        }
        if (*(int*)((char*)DAT_016c7aa4 + 0x74) != 0) {
            int r = MGR()->F3be60(FUN_00efc520());
            if (r != 0)
                *(int*)(r + 0x80) = v2c;
        }
        f00edda20();
    }
}

// ============================================================ 0x00edddc0
struct Sub14 {
    char pad[0x100];
    char b1;
    void f00edddc0(int* param_2);
};
struct SubD4 { void F72b0(); };
// @ 0x00edddc0
void Sub14::f00edddc0(int* param_2)
{
    char* edi = (char*)this;
    ((C*)(edi - 0x14))->f00eddc50(param_2);
    if (*(int*)(edi + 0xc) != 0) {
        void* w = VCP2(*(void**)(edi + 0xc), 0xf0, 0x75f60b0, 1);
        if (w != 0) {
            VC2(w, 0x7c, 1, 1);
            void* wm = SP_WindowManager();
            VC2(wm, 0x4c, 0, (int)w);
        }
        *(char*)(edi + 0xb1) = 1;
    }
    ((SubD4*)*(void**)((char*)DAT_016c7aa4 + 0xd4))->F72b0();
}

// ============================================================ 0x00edde30
// @ 0x00edde30
void C::f00edde30(int param)
{
    char* t = (char*)this;
    *(int*)(t + 0x108) = param;
    if (*(char*)(t + 0xc6) != 0) {
        unsigned i = 0;
        do {
            int idx = *(int*)((char*)DAT_0148a518 + i);
            bool sel = (idx == *(int*)(t + 0x108));
            int val = DAT_0148a544[idx];
            ((Element*)*(void**)(t + 0xbc))->SetChecked(val, sel);
            i += 4;
        } while (i < 0x2c);
    }
}

// ============================================================ 0x00edde90
// @ 0x00edde90
void C::f00edde90()
{
    char* t = (char*)this;
    *(int*)(t + 0x108) = 0;
    if (*(char*)(t + 0xc6) != 0) {
        unsigned i = 0;
        do {
            int idx = *(int*)((char*)DAT_0148a518 + i);
            ((Element*)*(void**)(t + 0xbc))->SetChecked(DAT_0148a544[idx], 1);
            i += 4;
        } while (i < 0x2c);
    }
}

// ============================================================ 0x00eddee0
// @ 0x00eddee0
int __cdecl f00eddee0(void* p, int param_2)
{
    if (p != 0) {
        void* q = VCP2(p, 0xf0, 0x742cbe0 + param_2, 1);
        q = VCP0(q, 0xa8);
        if (q != 0) {
            void* r = VCP1(q, 0xc, 0x53eb526);
            if (r != 0)
                return ((Sink*)r)->F00830d10(0);
        }
    }
    return -1;
}

// ============================================================ 0x00eddf30
// @ 0x00eddf30
bool __cdecl f00eddf30(int param_1, int param_2, int param_3, int param_4)
{
    bool result = false;
    if (param_2 == param_3)
        return result;
    if (param_3 == -2)
        return param_4 != 0x742bdb0;
    Mgr* m = MGR();
    Checker* o = (Checker*)m->F3e8a0(param_3);
    if (o == 0)
        return result;
    if (param_4 == 0x742bdb0) return o->F254d0();
    if (param_4 == 0x742bdc0) return o->F25330();
    if (param_4 == 0x742bdd0) return o->F25490();
    return result;
}
