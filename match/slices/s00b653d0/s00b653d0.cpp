// Slice s00b653d0: geometry/transform helpers (MSVC 2008 SP1, /O2).
#include "types.h"
#include <math.h>
#include <intrin.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

// ---- dummy-virtual macros (slot n = byte offset n*4) ----
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

struct HkMem { G3 virtual void* f10(u32, u32); };   // vtable slot 4 (0x10)

// ---- external stubs ----
struct M3 { void FUN_0041cb40(void*); };            // Matrix3::Assign (ecx=dest)
struct Obj103 {                                     // hkEntity-like
    int* FUN_00496140(void*, int);
    void FUN_00aef570(void*);
    void FUN_01088ae0();
};
struct Obj103b { float* FUN_00aef400(); };
struct HkT { void FUN_0107db10(void*, u32, u32); };
struct Dtor { void FUN_00453460(); };

char __cdecl FUN_00b64a60(u32,u32,u32,u32,void*,void*,u32);
void __cdecl FUN_010edf70(void*,void*,void*,u32);
u32  __cdecl FUN_010c1fe0(u32,u32,u32,void*,float);
void __cdecl FUN_00b65710(float* out, float* in);

typedef void* (__stdcall *TlsGetValueFn)(u32);

struct C103 {
    void m655f0(C103* src);
    void FUN_00b659f0(int* param_2, int* g1, float* pt);
};

// ===========================================================================
// @ 0x00B653D0
// ===========================================================================
struct Matrix3f { float m[9]; };

u32 __cdecl FUN_00b653d0(u32 p1, u32 p2, u32 p3, float* p4, u32 p5)
{
    u32 local_74, local_70, local_6c, local_68, local_64, local_60;
    u32 local_5c, local_58, local_54;
    u32 local_50, local_4c, local_48, local_44, local_40, local_3c;
    u16 local_38; short local_36;
    u32 local_34, local_30, local_2c, local_28;
    Matrix3f local_24;

    local_36 = 0;
    local_38 = 0;
    ((M3*)&local_24)->FUN_0041cb40((void*)0x16872f8);
    local_38 |= 4;
    local_58 = *(u32*)&p4[1] ^ 0x80000000u;
    local_5c = *(u32*)&p4[0] ^ 0x80000000u;
    local_36 = local_36 + 2;
    local_54 = *(u32*)&p4[2] ^ 0x80000000u;
    local_28 = p3;
    local_74 = 0;
    local_70 = 0;
    local_6c = 0x80000000u;
    local_34 = local_5c;
    local_30 = local_58;
    local_2c = local_54;

    char c = FUN_00b64a60(p1, p2, 0, 0, &local_38, &local_74, 0);
    u32 u = local_6c;
    if (c != 0) {
        local_68 = local_74;
        local_64 = local_70;
        local_60 = 0x10;
        local_50 = 0; local_4c = 0; local_48 = 0x80000000u;
        local_44 = 0; local_40 = 0; local_3c = 0x80000000u;
        local_5c = 0; local_58 = 0; local_54 = 0x80000000u;
        FUN_010edf70(&local_68, &local_50, &local_5c, 1);

        void* g_mem = *(void**)0x16e4178;
        void* mem = ((HkMem*)g_mem)->f10(0x50, 0x24);
        *(u16*)((char*)mem + 4) = 0x50;

        float ftmp = *(float*)0x15ba104;
        float vec[3];
        vec[0] = *(float*)&local_64;
        vec[1] = *(float*)((char*)&local_64 + 4);
        vec[2] = *(float*)((char*)&local_64 + 8);
        u32 shape = FUN_010c1fe0(local_70, local_6c, local_68, vec, ftmp);
        u32 eax = shape;
        u = local_5c;

        if ((local_5c & 0x80000000u) == 0) {
            void* tls = ((TlsGetValueFn)*(void**)0x13cc2bc)(*(u32*)0x16e4174);
            ((HkT*)tls)->FUN_0107db10((void*)local_64, u << 4, 0x14);
        }
        ((Dtor*)&local_34)->FUN_00453460();
        u = local_74;
        if ((local_74 & 0x80000000u) == 0) {
            void* tls = ((TlsGetValueFn)*(void**)0x13cc2bc)(*(u32*)0x16e4174);
            ((HkT*)tls)->FUN_0107db10((void*)local_74, u << 4, 0x14);
        }
        return eax;
    }
    if ((local_6c & 0x80000000u) == 0) {
        void* tls = ((TlsGetValueFn)*(void**)0x13cc2bc)(*(u32*)0x16e4174);
        ((HkT*)tls)->FUN_0107db10((void*)local_74, u << 4, 0x14);
    }
    return 0;
}

// ===========================================================================
// @ 0x00B655F0
// ===========================================================================
struct G103 {
    int      k0;      // +0x00
    int      pad[3];  // +0x04..0x0c
    float    f10, f14, f18, f1c; // +0x10..
    float*   p20;     // +0x20
    float*   p24;     // +0x24
    int      k28, k2c;
};

void C103::m655f0(C103* src)
{
    G103* d = (G103*)this;
    G103* s = (G103*)src;
    d->k0 = s->k0;
    d->f10 = s->f10;
    d->f14 = s->f14;
    d->f18 = s->f18;
    d->f1c = s->f1c;
    _ReadWriteBarrier();
    float* p = d->p20;
    if (p != 0) {
        float* q = s->p20;
        if (q != 0) {
            p[0] = q[0];
            p[1] = q[1];
            p[2] = q[2];
            p[3] = q[3];
        }
    }
    float* p2 = d->p24;
    if (p2 != 0) {
        float* q2 = s->p24;
        if (q2 != 0)
            p2[0] = q2[0];
    }
    d->k28 = s->k28;
    d->k2c = s->k2c;
}

// ===========================================================================
// @ 0x00B65660
// ===========================================================================
void __cdecl FUN_00b65660(int* a, int* b, C103* dst)
{
    if (*a == 0)
        goto Ldb;
    if (*b == 0)
        goto Leb;
    {
        float ax = *(float*)((char*)a + 0x10);
        float ay = *(float*)((char*)a + 0x14);
        float az = *(float*)((char*)a + 0x18);
        float bx = *(float*)((char*)b + 0x10);
        float by = *(float*)((char*)b + 0x14);
        float bz = *(float*)((char*)b + 0x18);
        float ma = (ax * ax + ay * ay) + az * az;
        float mb = (bx * bx + by * by) + bz * bz;
        if (ma <= mb)
            goto Le0;
    }
    dst->m655f0((C103*)a);
    return;
Ldb:
    if (*b == 0)
        goto Leb;
Le0:
    dst->m655f0((C103*)b);
    return;
Leb:
    if (*a != 0) {
        dst->m655f0((C103*)a);
        return;
    }
    *(int*)dst = 0;
}

// ===========================================================================
// @ 0x00B65710
// ===========================================================================
void __cdecl FUN_00b65710(float* out, float* in)
{
    float x = in[0];
    float y = in[1];
    float z = in[2];
    float w = in[3];
    if (0.001f < (x * x + y * y) + z * z) {
        float len2 = (x * x + y * y) + z * z;
        __declspec(align(16)) float r = 0.0f;   // retail frame is 16-aligned; keeps r out of the push-ecx scratch slot
        if (len2 != 0.0f) {
            __asm {
                fld    len2
                fsqrt
                fld1
                fdivrp st(1), st(0)
                fstp   r
            }
        }
        out[0] = r * x;
        out[1] = r * y;
        out[2] = r * z;
        out[3] = r * w;
    } else {
        out[0] = *(float*)0x156ae70;
        out[1] = *(float*)0x156ae74;
        out[2] = *(float*)0x156ae78;
        out[3] = *(float*)0x156ae7c;
    }
}

// ===========================================================================
// @ 0x00B65820
// ===========================================================================
void __cdecl FUN_00b65820(int param_1, float* param_2)
{
    float sq = (param_2[0] * param_2[0] + param_2[1] * param_2[1]) + param_2[2] * param_2[2];
    if (*(float*)0x1464940 <= sq) {
        int local[2];
        int* r0 = ((Obj103*)param_1)->FUN_00496140(local, 0);
        if (*r0 == 3) {
            int* r1 = ((Obj103*)param_1)->FUN_00496140(local, 4);
            int obj = *r1;
            if (obj != 0) {
                *(int*)(obj + 0xcc) = 0;
                ((Obj103*)obj)->FUN_00aef570(param_2);
                return;
            }
        }
        ((Obj103*)param_1)->FUN_01088ae0();
        int o = *(int*)(param_1 + 0x58);
        void** vt = *(void***)o;
        ((void(__thiscall*)(int, float*))vt[0x60 / 4])(o, param_2);
    }
}

// ===========================================================================
// @ 0x00B658C0
// ===========================================================================
float* __cdecl FUN_00b658c0(float* out, int param_2)
{
    int local[2];
    int* r0 = ((Obj103*)param_2)->FUN_00496140(local, 0);
    if (*r0 == 3) {
        int* r1 = ((Obj103*)param_2)->FUN_00496140(local, 4);
        int obj = *r1;
        if (obj != 0) {
            float* p = ((Obj103b*)obj)->FUN_00aef400();
            out[0] = p[0];
            out[1] = p[1];
            out[2] = p[2];
            out[3] = p[3];
            return out;
        }
    }
    float* p = (float*)(*(int*)(param_2 + 0x58));
    out[0] = p[0xd0 / 4];
    out[1] = p[0xd0 / 4 + 1];
    out[2] = p[0xd0 / 4 + 2];
    out[3] = p[0xd0 / 4 + 3];
    return out;
}

// ===========================================================================
// @ 0x00B65950
// ===========================================================================
void __cdecl FUN_00b65950(float* out, int param_2)
{
    int local[2];
    int* r0 = ((Obj103*)param_2)->FUN_00496140(local, 0);
    if (*r0 == 3) {
        int* r1 = ((Obj103*)param_2)->FUN_00496140(local, 4);
        if (*r1 != 0) {
            out[0] = *(float*)0x16e42d0;
            out[1] = *(float*)0x16e42d4;
            out[2] = *(float*)0x16e42d8;
            out[3] = *(float*)0x16e42dc;
            return;
        }
    }
    int iVar1 = *(int*)(param_2 + 0x58);
    out[0] = *(float*)(iVar1 + 0xe0);
    out[1] = *(float*)(iVar1 + 0xe4);
    out[2] = *(float*)(iVar1 + 0xe8);
    out[3] = *(float*)(iVar1 + 0xec);
}

static float mag2(int* p)
{
    float x = *(float*)((char*)p + 0x10);
    float y = *(float*)((char*)p + 0x14);
    float z = *(float*)((char*)p + 0x18);
    return (x * x + y * y) + z * z;
}

// ===========================================================================
// @ 0x00B659F0
// ===========================================================================
void C103::FUN_00b659f0(int* param_2, int* g1, float* pt)
{
    if (*param_2 == 0) {
        if (*(int*)g1 != 0) {
            this->m655f0((C103*)g1);
            return;
        }
    } else if (*(int*)g1 != 0) {
        if (mag2(param_2) <= mag2(g1)) {
            this->m655f0((C103*)g1);
            return;
        }
        this->m655f0((C103*)param_2);
        return;
    }
    if (*param_2 != 0) {
        float dz = *(float*)((char*)param_2 + 0x18) - pt[2];
        float dx = *(float*)((char*)param_2 + 0x10) - pt[0];
        float dy = *(float*)((char*)param_2 + 0x14) - pt[1];
        float n[4];
        FUN_00b65710(n, pt);
        float dot = (n[0] * dx + n[1] * dy) + n[2] * dz;
        if (pt[4] >= dot && dot >= pt[5]) {
            this->m655f0((C103*)param_2);
            return;
        }
    }
    *(int*)this = 0;
}
