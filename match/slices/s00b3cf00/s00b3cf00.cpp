// Slice s00b3cf00: creature/vehicle controller helpers (MSVC 2008 SP1, /O2).
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// dummy-virtual macros: `struct Vn { G(n-1) virtual R m(...); };` puts m at
// vtable byte offset n*4, so `((Vn*)p)->m()` emits `mov ecx,p; mov eax,[ecx]; call [eax+n*4]`.
// ---------------------------------------------------------------------------
#define G0  virtual void z00();
#define G1  G0  virtual void z01();
#define G2  G1  virtual void z02();
#define G3  G2  virtual void z03();
#define G4  G3  virtual void z04();
#define G5  G4  virtual void z05();
#define G6  G5  virtual void z06();
#define G7  G6  virtual void z07();
#define G8  G7  virtual void z08();
#define G9  G8  virtual void z09();
#define G10 G9  virtual void z10();
#define G11 G10 virtual void z11();
#define G12 G11 virtual void z12();
#define G13 G12 virtual void z13();
#define G14 G13 virtual void z14();
#define G15 G14 virtual void z15();
#define G16 G15 virtual void z16();
#define G17 G16 virtual void z17();
#define G18 G17 virtual void z18();
#define G19 G18 virtual void z19();
#define G20 G19 virtual void z20();
#define G21 G20 virtual void z21();
#define G22 G21 virtual void z22();
#define G23 G22 virtual void z23();
#define G24 G23 virtual void z24();
#define G25 G24 virtual void z25();
#define G26 G25 virtual void z26();
#define G27 G26 virtual void z27();
#define G28 G27 virtual void z28();
#define G29 G28 virtual void z29();
#define G30 G29 virtual void z30();
#define G31 G30 virtual void z31();
#define G32 G31 virtual void z32();
#define G33 G32 virtual void z33();
#define G34 G33 virtual void z34();
#define G35 G34 virtual void z35();
#define G36 G35 virtual void z36();
#define G37 G36 virtual void z37();
#define G38 G37 virtual void z38();
#define G39 G38 virtual void z39();
#define G40 G39 virtual void z40();
#define G41 G40 virtual void z41();
#define G42 G41 virtual void z42();
#define G43 G42 virtual void z43();
#define G44 G43 virtual void z44();
#define G45 G44 virtual void z45();
#define G46 G45 virtual void z46();
#define G47 G46 virtual void z47();
#define G48 G47 virtual void z48();
#define G49 G48 virtual void z49();
#define G50 G49 virtual void z50();
#define G51 G50 virtual void z51();
#define G52 G51 virtual void z52();
#define G53 G52 virtual void z53();
#define G54 G53 virtual void z54();

struct V00 { virtual void      f00(); };
struct V04 { G0  virtual void      f04(); };
struct V1C { G6  virtual void*     f1C(unsigned id); };
struct V20 { G7  virtual void      f20(void* a, unsigned id); };
struct V24 { G8  virtual bool      f24(unsigned id, void* out); };
struct V30 { G11 virtual bool      f30(unsigned id, void* out); };
struct V48 { G17 virtual bool      f48(); };
struct V68 { G25 virtual void*     f68(); };
struct V6C { G26 virtual void*     f6C(void* out); };
struct V70 { G27 virtual float     f70(); };
struct VAC { G42 virtual void*     fAC(void* a); };
struct VB0 { G43 virtual void*     fB0(); };
struct VB8 { G45 virtual void*     fB8(unsigned id); };
struct VD8 { G53 virtual float     fD8(); };

// ---------------------------------------------------------------------------
// external callees
// ---------------------------------------------------------------------------
void* __cdecl SP_GetCurrentGameMode();       // 0x00b5b800
void* __cdecl SP_PropertyManager();           // 0x0067de30
void* __cdecl SP_MessageServer();             // 0x0067dcc0
void* __cdecl SP_ModelManager();              // 0x0067dd80
bool  __cdecl IsFinite(float f);              // 0x0059ab10
void* __cdecl FUN_00b3d3c0(void* p);          // 0x00b3d3c0
void* __cdecl FUN_00b7c480(void* p);          // 0x00b7c480
void* __cdecl FUN_00b7c360(void* a, void* b); // 0x00b7c360
void  __cdecl FUN_00b50ff0();                 // 0x00b50ff0
void  __cdecl FUN_00b515e0();                 // 0x00b515e0
void  __cdecl FUN_00b5a2d0();                 // 0x00b5a2d0
void* __cdecl FUN_010212f0();                 // 0x010212f0

extern unsigned char g_167ece0;      // 0x0167ece0
extern float g_167ec2c, g_167ec30, g_167ec34; // 0x0167ec2c
extern float g_167eb8c, g_167eb90, g_167eb94; // 0x0167eb8c
extern float g_15695fc;              // 0x015695fc
extern void* g_167eae4;              // 0x0167eae4

// ---------------------------------------------------------------------------
// object layouts
// ---------------------------------------------------------------------------
struct Obj40 {
    char pad0[0x44];
    float f44;                       // +0x44
    char pad48[0x70 - 0x48];
    unsigned char b70;               // +0x70
    unsigned char b71;               // +0x71
    char pad72[0x75 - 0x72];
    unsigned char b75;               // +0x75
    char pad76[0x1f0 - 0x76];
    int  n1f0;                       // +0x1f0

    float* GetVelocity();            // 0x00d20610
    float* GetBounding();            // 0x00c41d50
};

struct C101 {
    char  pad0[4];
    int   nMode;                     // +0x04
    char  pad8[0xc - 8];
    int   nC;                        // +0x0c
    float f10;                       // +0x10
    float f14;                       // +0x14
    float f18;                       // +0x18
    float f1c, f20, f24;             // +0x1c
    float f28, f2c, f30;             // +0x28
    unsigned char b34, b35, b36, b37;// +0x34
    char  pad38[0x40 - 0x38];
    Obj40* p40;                      // +0x40
    char  pad44[0x68 - 0x44];
    int   n68, n6c;                  // +0x68
    char  pad70[0xe0 - 0x70];
    float e0, e4, e8;                // +0xe0
    float ec, f0, f4;                // +0xec
    char  padf8[0x1f8 - 0xf8];
    float arr;                       // +0xf8 (base of per-index vec3 array)

    float M_cf00();
    void  M_cf40();
    bool  M_d5f0();
    float M_d630();
    void* M_d6a0();
    void  M_d730();
    void  M_d7a0();
    void* M_d8c0();
    void  M_d9c0(float* out);
    void  M_da90(float* out, int idx, C101* other);
    void  M_dbb0();
    float M_dcd0();
    bool  M_dd40();
    void  M_dda0(float* a, float* b);
    void  M_dec0(float* v);
};

struct Neigh { bool IsValid(void* e); };          // 0x00c02600
struct Neigh2 { bool IsValid(void* e); };         // 0x00c03520
struct FB57  { void f515e0(); void f5a2d0(); };   // thiscall on C101
struct C7C   { void* f360(void*); void* f480(void*); }; // 0xb7c360 / 0xb7c480
struct PropObj { char pad[0x12]; short mType; };  // has GetFloat()
struct PropObjF : PropObj { float* GetFloat(); }; // 0x0041ea70
struct C4F { void* f(); };                        // 0x00c4f030 (ecx = g_167eae4)
struct C0C { void* f(); };                        // 0x00c0c2f0 (ecx = object)
struct PropGroup { G8  virtual bool GetProp(unsigned id, PropObjF** out); }; // slot 0x24
struct PropMgr   { G11 virtual bool GetGroup(unsigned id, PropGroup** out); }; // slot 0x30

// ---------------------------------------------------------------------------
// @ 0x00B3CF00
// ---------------------------------------------------------------------------
float C101::M_cf00()
{
    void* m = SP_GetCurrentGameMode();
    if (m == (void*)0x01654c01)
        return f14;
    if (m == (void*)0x01654c02)
        return f1c;
    if (m == (void*)0x01654c04)
        return f24;
    if (m == (void*)0x01654c05)
        return f2c;
    return 1000.0f;
}

// ---------------------------------------------------------------------------
// 0x00B3CF40 helper: read one float property
// ---------------------------------------------------------------------------
static void ReadFloatProp(PropGroup* pg, unsigned id, float* dst)
{
    PropObjF* p = 0;
    if (pg->GetProp(id, &p)) {
        if (p && p->mType == 0xd)
            *dst = *p->GetFloat();
    }
}

// @ 0x00B3CF40  read 12 named float properties into this[0..0x2c]
void C101::M_cf40()
{
    PropGroup* pg = 0;
    PropMgr* pm = (PropMgr*)SP_PropertyManager();
    pm->GetGroup(0x39393837u, &pg);
    if (pg) {
        ReadFloatProp(pg, 0x041bacb8u, (float*)((char*)this + 0x00));
        ReadFloatProp(pg, 0x041b8f40u, (float*)((char*)this + 0x04));
        ReadFloatProp(pg, 0x041b8f45u, (float*)((char*)this + 0x08));
        ReadFloatProp(pg, 0x041b8f48u, (float*)((char*)this + 0x0c));
        ReadFloatProp(pg, 0x05dfdaaau, (float*)((char*)this + 0x10));
        ReadFloatProp(pg, 0x05dfdaaeu, (float*)((char*)this + 0x14));
        ReadFloatProp(pg, 0x05dfdab2u, (float*)((char*)this + 0x18));
        ReadFloatProp(pg, 0x05dfdab5u, (float*)((char*)this + 0x1c));
        ReadFloatProp(pg, 0x05dfdab8u, (float*)((char*)this + 0x20));
        ReadFloatProp(pg, 0x05dfdabau, (float*)((char*)this + 0x24));
        ReadFloatProp(pg, 0x05dfdabdu, (float*)((char*)this + 0x28));
        ReadFloatProp(pg, 0x05dfdac2u, (float*)((char*)this + 0x2c));
    }
}

// ---------------------------------------------------------------------------
// @ 0x00B3D2C0  SP::RelationshipManager
// ---------------------------------------------------------------------------
void* __cdecl SP_RelationshipManager()
{
    void* m = SP_GetCurrentGameMode();
    if ((int)m < 0x01654c06) {
        if (m == (void*)0x01654c05)
            return ((C4F*)g_167eae4)->f();
        if (m != (void*)0x01654c02 && m != (void*)0x01654c04)
            return 0;
    } else if (m != (void*)0x01654c10) {
        if (m != (void*)0x02ccd1d2)
            return 0;
        return ((C4F*)g_167eae4)->f();
    }
    return FUN_010212f0();
}

// ---------------------------------------------------------------------------
// @ 0x00B3D520  SP::GonzagoModelWorld
// ---------------------------------------------------------------------------
void* __cdecl SP_GonzagoModelWorld()
{
    void* mm = SP_ModelManager();
    void* p = ((V1C*)mm)->f1C(0x00eb9968u);
    if (p) {
        ((V00*)p)->f00();
        ((V04*)p)->f04();
    }
    return p;
}

// ---------------------------------------------------------------------------
// @ 0x00B3D550
// ---------------------------------------------------------------------------
bool __cdecl FUN_00b3d550(float* v)
{
    if (((*(unsigned*)&v[3] & 0x7fffffffu) == 0) ||
        (((*(unsigned*)&v[3] - 0x00800000u) & 0x7f800000u) < 0x7f000000u)) {
        if (((*(unsigned*)&v[0] & 0x7fffffffu) == 0) ||
            (((*(unsigned*)&v[0] - 0x00800000u) & 0x7f800000u) < 0x7f000000u)) {
            if (((*(unsigned*)&v[1] & 0x7fffffffu) == 0) ||
                (((*(unsigned*)&v[1] - 0x00800000u) & 0x7f800000u) < 0x7f000000u)) {
                if (IsFinite(v[2]))
                    return true;
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00B3D5F0
// ---------------------------------------------------------------------------
bool C101::M_d5f0()
{
    switch (nMode) {
    case 0: goto body;
    case 1: goto body;
    case 2:
        return true;
    }
    return false;
body:
    {
        Obj40* o = p40;
        if (o->b75 != 0 && (o->b70 != 0 || b35 != 0))
            return true;
        return false;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00B3D630
// ---------------------------------------------------------------------------
float C101::M_d630()
{
    float local = 0.0f;
    if (f18 > 0.0f)
        return f18;
    switch (nMode) {
    case 0: goto mode01;
    case 1: goto mode01;
    case 2:
        local = p40->f44;
        break;
    }
    return f10 * local;
mode01:
    {
        float r = ((V70*)p40)->f70();
        return r * f10;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00B3D6A0
// ---------------------------------------------------------------------------
void* C101::M_d6a0()
{
    switch (nMode) {
    case 0: goto body;
    case 1: goto body;
    case 2:
        return ((C7C*)FUN_00b3d3c0(p40))->f480(p40);
    }
    return 0;
body:
    {
        Obj40* o = p40;
        void* a = ((VB0*)o)->fB0();
        void* b = ((VAC*)o)->fAC(a);
        return ((C7C*)FUN_00b3d3c0(b))->f360(b);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00B3D700  min/max packed into a dword (lo16=min, hi16=max)
// ---------------------------------------------------------------------------
struct S16 { unsigned short lo, hi; };
S16 __cdecl FUN_00b3d700(unsigned a, unsigned b)
{
    S16 r;
    if (a < b) { r.hi = (unsigned short)a; r.lo = (unsigned short)b; }
    else       { r.hi = (unsigned short)b; r.lo = (unsigned short)a; }
    return r;
}

// ---------------------------------------------------------------------------
// @ 0x00B3D730
// ---------------------------------------------------------------------------
void C101::M_d730()
{
    void* self = (char*)this - 4;
    void* ms = SP_MessageServer();
    ((V20*)ms)->f20(self, 0x0182c582u);
    ms = SP_MessageServer();
    ((V20*)ms)->f20(self, 0x01a0219eu);
    ms = SP_MessageServer();
    ((V20*)ms)->f20(self, 0x025630b7u);
    ms = SP_MessageServer();
    ((V20*)ms)->f20(self, 0x031018b9u);
    ms = SP_MessageServer();
    ((V20*)ms)->f20(self, 0x000f62deu);
    FUN_00b50ff0();
}

// ---------------------------------------------------------------------------
// @ 0x00B3D7A0
// ---------------------------------------------------------------------------
void C101::M_d7a0()
{
    ((FB57*)this)->f515e0();
    ((FB57*)this)->f5a2d0();
    g_167ece0 = 1;
}

// ---------------------------------------------------------------------------
// @ 0x00B3D850
// ---------------------------------------------------------------------------
void** __fastcall FUN_00b3d850(void** self)
{
    do {
        *(int*)self += 4;
        if (*self == self[1])
            break;
    } while (!((Neigh*)((char*)self + 8))->IsValid(*(void**)*self));
    return self;
}

// ---------------------------------------------------------------------------
// @ 0x00B3D870
// ---------------------------------------------------------------------------
void** __fastcall FUN_00b3d870(void** self)
{
    do {
        *(int*)self += 4;
        if (*self == self[1])
            break;
    } while (!((Neigh2*)((char*)self + 8))->IsValid(*(void**)*self));
    return self;
}

// ---------------------------------------------------------------------------
// @ 0x00B3D8C0
// ---------------------------------------------------------------------------
void* C101::M_d8c0()
{
    n68 = 0;
    n6c = 0;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00B3D8D0  normalized cross product
// ---------------------------------------------------------------------------
void __cdecl FUN_00b3d8d0(float* out, float* b, float* c, float p4, float p5, float p6)
{
    float f1 = c[0] - b[0];
    float f2 = c[1] - b[1];
    p4 = p4 - c[0];
    p5 = p5 - c[1];
    float f3 = c[2] - b[2];
    p6 = p6 - c[2];
    float f4 = p6 * f2 - p5 * f3;
    f2 = p5 * f1 - p4 * f2;
    f3 = p4 * f3 - p6 * f1;
    volatile double v4 = f4, v3 = f3, v2 = f2;
    double d = v4 * v4 + (v3 * v3 + v2 * v2);
    float inv = (float)(1.0 / sqrt(d));
    out[0] = inv * f4;
    out[1] = f3 * inv;
    out[2] = f2 * inv;
}

// ---------------------------------------------------------------------------
// @ 0x00B3D9C0  this[out] = centre/size vector for the current controller
// ---------------------------------------------------------------------------
void C101::M_d9c0(float* out)
{
    float b0[6], b1[6];
    float* p;
    float v;
    switch (nMode) {
    case 0:
        p = (float*)((V6C*)p40)->f6C(b1);
        v = p[0] + p[3];
        break;
    case 1:
        p = (float*)((V6C*)p40)->f6C(b0);
        v = p[3] + p[0];
        break;
    case 2: {
        Obj40* o = p40;
        out[0] = *(float*)((char*)o + 0x38);
        out[1] = *(float*)((char*)o + 0x3c);
        out[2] = *(float*)((char*)o + 0x40);
        return;
    }
    default:
        return;
    }
    out[0] = v * 0.5f;
    out[1] = (p[4] + p[1]) * 0.5f;
    out[2] = (p[5] + p[2]) * 0.5f;
}

// ---------------------------------------------------------------------------
// @ 0x00B3DA90
// ---------------------------------------------------------------------------
void C101::M_da90(float* out, int idx, C101* other)
{
    switch (nC) {
    case 2: {
        float* p = (float*)((char*)this + 0xf8 + idx * 0xc);
        out[0] = p[0];
        out[1] = p[1];
        out[2] = p[2];
        return;
    }
    case 0:
    case 1: {
        float a[3], b[3];
        M_d9c0(a);
        other->M_d9c0(b);
        float x = b[0] - a[0];
        float y = b[1] - a[1];
        float z = b[2] - a[2];
        volatile double vx = x, vy = y, vz = z;
        double d = vx * vx + (vy * vy + vz * vz) + 1e-08;
        float s = (float)(1.0 / sqrt(d));
        out[0] = s * x;
        out[1] = y * s;
        out[2] = z * s;
        return;
    }
    default:
        out[0] = g_167ec2c;
        out[1] = g_167ec30;
        out[2] = g_167ec34;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00B3DBB0
// ---------------------------------------------------------------------------
void C101::M_dbb0()
{
    b37 = 0;
    switch (nMode) {
    case 0: {
        b36 = 0;
        float* v = p40->GetVelocity();
        f1c = v[0]; f20 = v[1]; f24 = v[2];
        v = p40->GetBounding();
        f28 = v[0]; f2c = v[1]; f30 = v[2];
        switch (p40->n1f0) {
        case 0: case 1: case 6: case 7:
            b34 = 1;
            return;
        default:
            b34 = 0;
            return;
        }
    }
    case 1:
        if (f1c == g_167eb8c && f20 == g_167eb90 && f24 == g_167eb94)
            b36 = 0;
        else
            b36 = 1;
        return;
    case 2:
        b36 = 0;
        f1c = g_167eb8c; f20 = g_167eb90; f24 = g_167eb94;
        f28 = g_167eb8c; f2c = g_167eb90; f30 = g_167eb94;
        return;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00B3DCD0
// ---------------------------------------------------------------------------
float C101::M_dcd0()
{
    switch (nMode) {
    case 0: {
        Obj40* o = p40;
        if (o->b71 != 0) {
            float z = 0.0f;
            return z;
        }
        return 1.0f / ((VD8*)o)->fD8();
    }
    case 1: {
        Obj40* o = p40;
        if (o->b71 == 0) {
            float* p = (float*)((V68*)o)->f68();
            return 1.0f / (((p[3] - p[0]) * (p[4] - p[1])) * (p[5] - p[2]) * g_15695fc);
        }
        break;
    }
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00B3DD40
// ---------------------------------------------------------------------------
bool C101::M_dd40()
{
    if (nMode != 0)
        return false;
    Obj40* o = p40;
    if (o != 0) {
        void* e = ((VB8*)o)->fB8(0xce9f6639u);
        if (e != 0) {
            if (*((unsigned char*)e + 0xf90) != 0) {
                void* r = ((C0C*)e)->f();
                if (r != 0)
                    return false;
            }
            return true;
        }
    }
    return ((V48*)o)->f48() == false;
}

// ---------------------------------------------------------------------------
// @ 0x00B3DDA0
// ---------------------------------------------------------------------------
void C101::M_dda0(float* pa, float* pb)
{
    char c;
    switch (nMode) {
    case 0: goto get;
    case 1: goto get;
    default:
        return;
    }
get:
    c = p40->b71;
    if (c != 0)
        return;

    float local[3];
    M_d9c0(local);
    e8 = pb[2] + e8;
    e4 = e4 + pb[1];
    e0 = e0 + pb[0];
    ec = ec + (pb[2] * (pa[1] - local[1]) - pb[1] * (pa[2] - local[2]));
    f0 = f0 + (pb[0] * (pa[2] - local[2]) - pb[2] * (pa[0] - local[0]));
    f4 = f4 + (pb[1] * (pa[0] - local[0]) - pb[0] * (pa[1] - local[1]));
}

// ---------------------------------------------------------------------------
// @ 0x00B3DEC0
// ---------------------------------------------------------------------------
void C101::M_dec0(float* v)
{
    float s = M_dcd0();
    if (s > 1.5258789e-05f) {
        if (nMode == 0) {
            f1c = f1c + v[0] * s;
            f20 = v[1] * s + f20;
            f24 = v[2] * s + f24;
            b36 = 1;
        } else if (nMode == 1) {
            f1c = v[0] * s + f1c;
            f20 = f20 + v[1] * s;
            f24 = f24 + v[2] * s;
            b36 = 1;
        }
    }
}
