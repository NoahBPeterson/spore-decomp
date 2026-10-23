// Slice s00dda3b0 -- ten functions from the SporeApp image (VAs 0x00dda3b0 .. 0x00ddaf70).
//
//  * 0x00dda920 / 0x00dda9a0 are an ObjA (size 0x74) constructor/destructor and are byte-exact.
//  * 0x00dda6d0 / 0x00dda810 / 0x00ddab10 / 0x00ddada0 operate on a larger "controller" object
//    (CObj, >= 0x100 bytes) whose floats drive the vehicle/pose integrator.
//  * 0x00dda3b0 is a small CB member that toggles three sub-objects through deep vtable slots.
//  * 0x00dda500 carries its output object in EDI; modelled as an explicit first pointer
//    parameter and verified equiv PASS. 0x00ddaa20 takes its argument in EAX ([LTCG] custom
//    register ABI, docs/codegen.md s11.4), which a single-object compile cannot reproduce.
//  * 0x00ddaf70 fills a 12-byte result with a random element of a 12-byte-element vector.
//
// flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast  (per-row overrides in manifest.txt)
#include "types.h"
#include <intrin.h>
#include <math.h>

typedef union {
    long long QuadPart;
    struct { unsigned LowPart; int HighPart; };
} LI;
extern "C" int __stdcall QueryPerformanceCounter(LI* p);   // 0x013cc2b8 (IAT)

// --------------------------------------------------------------------- data
extern float DAT_016a0b0c, DAT_016a0b10, DAT_016a0b14, DAT_016a0b58;
extern float DAT_016a0ba4, DAT_016a0ba8, DAT_016a0bac, DAT_016a0ff8;
extern float DAT_016a0fd8, DAT_016a0fe8, DAT_016a1018, DAT_016a1028;
extern float DAT_016a0b28[9];
extern int   DAT_016a0b90, DAT_016a0b94;
class ObjA;
extern ObjA* DAT_016a0b08;                              // 0x016a0b08  ObjA singleton

// --------------------------------------------------------------------- engine helpers
extern void  EASTL_allocator_deallocate(void*);         // 0x00f47380  cdecl
extern void* FUN_0067dd50();                            // 0x0067dd50
extern void* FUN_0067dd10();                            // 0x0067dd10
extern void* FUN_0067cb40();                            // 0x0067cb40
extern float* FUN_00dd93d0();                           // 0x00dd93d0
extern float* FUN_00dd91b0();                           // 0x00dd91b0
extern void  FUN_00dd9080();                            // 0x00dd9080
extern float FUN_00572a10(float, float);                // 0x00572a10
// both are __thiscall on the singleton at 0x01601760 (the original loads ecx before each call)
struct GlobalTimer {
    double FUN_009360d0();                              // 0x009360d0
    int    FUN_00a68fb0(int);                           // 0x00a68fb0
};
#define G_TIMER ((GlobalTimer*)0x1601760)
// __thiscall on the 64-bit tick counter at &CObj::b0 (the original loads ecx = &p->b0)
struct TimeBase {
    unsigned __int64 FUN_0093a3a0();                    // 0x0093a3a0
};
// 0x00dde590  __thiscall (ecx = the map object, one stack arg)
struct IvObj {
    void FUN_00dde590(void* q);                         // 0x00dde590
};
// 0x0041cb40  __thiscall Matrix3 Assign (dst = ecx, src on the stack; recorded in symbols/slices)
class Matrix3 { public: void Assign(const void* src); };
// engine helpers below are __thiscall (receiver in ecx, remaining args on the stack)
struct Dest {
    void  FUN_004e39a0(int a, int b);                   // 0x004e39a0  destroy a temp
    void  FUN_006bac90(void* src);                      // 0x006bac90
    void  FUN_006b9440(void* arg);                      // 0x006b9440
    void* FUN_00558830(int z);                          // 0x00558830  build, returns the out buffer
    void* FUN_00558960(int a, int b, int c);            // 0x00558960  build, returns the out buffer
};

#define VT(o)       (*(void***)(o))
#define VSLOT(o, n) (VT(o)[(n) / 4])

static __forceinline char  vc0_char(void* o, int n)
{ return ((char(__thiscall*)(void*))VSLOT(o, n))(o); }
static __forceinline void  vc1_void(void* o, int n, int a)
{ ((void(__thiscall*)(void*, int))VSLOT(o, n))(o, a); }
static __forceinline void* vc1_ret(void* o, int n, int a)
{ return ((void*(__thiscall*)(void*, int))VSLOT(o, n))(o, a); }
static __forceinline void* vc2_ret(void* o, int n, int a, int b)
{ return ((void*(__thiscall*)(void*, int, int))VSLOT(o, n))(o, a, b); }
static __forceinline void* vc0_ret(void* o, int n)
{ return ((void*(__thiscall*)(void*))VSLOT(o, n))(o); }

// --------------------------------------------------------------------- ObjA (0x74): ctor/dtor + angle helper
struct Mat3 {
    float m[9];                       // +0x00 (0x24 bytes)
    void copy(const void* src);       // 0x0041cb40  thiscall (dst=ecx, src=stack)
};

class Rel { public: virtual void vf0(); virtual void vf1(); };

class ObjA {
public:
    void* p00;      // +0x00
    int   f04;      // +0x04
    int   f08;      // +0x08
    char  gap0c[8]; // +0x0c
    Rel*  p14;      // +0x14
    Rel*  p18;      // +0x18
    Rel*  p1c;      // +0x1c
    Rel*  p20;      // +0x20
    void* p24;      // +0x24
    int   f28;      // +0x28
    int   f2c;      // +0x2c
    char  gap30[8]; // +0x30
    short w38;      // +0x38
    short w3a;      // +0x3a
    float f3c;      // +0x3c
    float f40;      // +0x40
    float f44;      // +0x44
    float f48;      // +0x48
    Mat3  m4c;      // +0x4c
    Rel*  p70;      // +0x70

    ObjA* FUN_00dda920();
    void  FUN_00dda9a0();
    float FUN_00dda160(void* pt3, int z);   // 0x00dda160
};

// --------------------------------------------------------------------- CObj: controller used by dda6d0/dda810/ddab10/ddada0
struct CObj {
    char          pad00[0x0c];
    float         f0c;                  // +0x0c
    float         f10;                  // +0x10
    float         f14;                  // +0x14
    char          pad18[0x24 - 0x18];
    float         f24;                  // +0x24
    float         f28;                  // +0x28
    float         f2c;                  // +0x2c
    char          pad30[0x48 - 0x30];
    float         f48;                  // +0x48
    float         f4c;                  // +0x4c
    float         f50;                  // +0x50
    float         f54;                  // +0x54
    char          pad58[0x98 - 0x58];
    float         f98;                  // +0x98
    char          pad9c[0xa8 - 0x9c];
    float         fa8;                  // +0xa8
    char          padac[0xb0 - 0xac];
    unsigned      b0;                   // +0xb0
    unsigned      b4;                   // +0xb4
    unsigned      b8;                   // +0xb8
    unsigned      bc;                   // +0xbc
    int           c0;                   // +0xc0
    float         c4;                   // +0xc4
    char          padc8[0xd5 - 0xc8];
    unsigned char d5;                   // +0xd5
    char          padd6[0xd8 - 0xd6];
    unsigned char d8;                   // +0xd8
    float         dc;                   // +0xdc
    float         e0;                   // +0xe0
    float         e4;                   // +0xe4
    float         e8;                   // +0xe8
    float         ec;                   // +0xec
    float         f0;                   // +0xf0
    void*         f4;                   // +0xf4
};

// --------------------------------------------------------------------- CB: 0x00dda3b0
class CB {
public:
    char  pad00[0x14];
    void* p14;                          // +0x14
    void* p18;                          // +0x18
    void* p1c;                          // +0x1c
    void  m3b0(char param_2);
};

// --------------------------------------------------------------------- local structs
struct Q {                              // 0x00dda500 normalised pose
    short a, b;
    float x, y, z, w;
    float m[9];
};
struct S9 { int v[9]; };                // 0x00ddaf70 nine-dword payload
struct Vec12 { char* b; char* e; char* c; };
typedef void (__cdecl* CB34)(void*, void*, S9, S9);

// ==================================================================== 0x00dda3b0
// @ 0x00dda3b0
void CB::m3b0(char param_2)
{
    void* v = this->p18;
    if (param_2 == 0) {
        if (vc0_char(v, 0x138) != 0) {
            vc1_void(this->p1c, 0x134, 0);
            vc1_void(this->p14, 0x134, 0);
            vc1_void(this->p18, 0x134, 0);
            vc1_void(FUN_0067dd50(), 0x50, 0x14);
            vc1_void(FUN_0067dd50(), 0x50, 0x0d);
            vc1_void(FUN_0067dd50(), 0x50, 0x1a);
            return;
        }
    } else {
        if (vc0_char(v, 0x138) == 0) {
            vc1_void(this->p1c, 0x134, 1);
            vc1_void(this->p18, 0x134, 1);
            vc1_void(this->p14, 0x134, 1);
            vc1_void(FUN_0067dd50(), 0x4c, (int)vc2_ret(this->p18, 0x13c, 0x14, 0));
            vc1_void(FUN_0067dd50(), 0x4c, (int)vc2_ret(this->p14, 0x13c, 0x0d, 0));
            vc1_void(FUN_0067dd50(), 0x4c, (int)vc2_ret(this->p1c, 0x13c, 0x1a, 0));
        }
    }
}

// ==================================================================== 0x00dda500
// The original keeps its output object in EDI across the whole body (custom register ABI); the
// object is modelled here as an explicit first parameter (equiv PASS, see nonmatching.txt).
// @ 0x00dda500
void FUN_00dda500(void* edi)
{
    void* p = FUN_0067dd10();
    p = vc0_ret(p, 0x50);
    p = vc0_ret(p, 0x38);
    int iv = 0;
    if (p != 0) {
        vc1_ret(p, 0x0c, 0x7ba6612);
        iv = (int)vc1_ret(p, 0x0c, 0x7ba65f3);
    }

    Q q;
    q.a = 0;
    q.b = 0;
    q.x = DAT_016a0b0c;
    q.y = DAT_016a0b10;
    q.z = DAT_016a0b14;
    q.w = 1.0f;
    ((Matrix3*)q.m)->Assign(DAT_016a0b28);

    if (iv != 0) {
        ((IvObj*)iv)->FUN_00dde590(&q);
        float r = 1.0f / sqrt(q.x * q.x + q.y * q.y + q.z * q.z + 1e-8f);
        float v1 = q.y * r * DAT_016a0bac - q.z * r * DAT_016a0ba8;
        float v2 = q.z * r * DAT_016a0ba4 - DAT_016a0bac * q.x * r;
        float v3 = DAT_016a0ba8 * q.x * r - q.y * r * DAT_016a0ba4;
        if (0.01 < sqrt(v1 * v1 + v2 * v2 + v3 * v3)) {
            float* s = FUN_00dd91b0();
            float* out = (float*)((char*)edi + 0x48);
            out[0] = s[0];
            out[1] = s[1];
            out[2] = s[2];
            out[3] = s[3];
        }
    }
}

// ==================================================================== 0x00dda6d0
// @ 0x00dda6d0
void __stdcall FUN_00dda6d0(CObj* param_1)
{
    int n = 0;
    float fx, fy;
    unsigned z;
    float local[3];
    while (1) {
        float* pf = FUN_00dd93d0();
        fy = pf[1];
        fx = pf[0];
        z = 0xc4160000u;                // local[2] = -600.0f  (kept as raw bits below)
        local[0] = fx;
        local[1] = fy;
        local[2] = *(float*)&z;
        if (35.0f <= sqrt(pf[2] * pf[2] + fx * fx + fy * fy) &&
            30.0f <= DAT_016a0b08->FUN_00dda160(local, 0))
            break;
        n = n + 1;
        if (999 < n)
            return;
    }
    if (n < 1000) {
        double t = G_TIMER->FUN_009360d0();
        double v = (t + 1.0) * 20.0;
        float f;
        if (10.0 <= v)
            f = 10.0f;
        else if (5.0 <= v)
            f = (float)v;
        else
            f = 5.0f;
        param_1->e0 = f;
        param_1->f0c = fx;
        param_1->f10 = fy;
        param_1->d5 = 0;
        *(unsigned*)&param_1->f14 = z;
        float r = FUN_00572a10(DAT_016a0fd8, DAT_016a0fe8);
        param_1->fa8 = r;
        param_1->f98 = r;
        param_1->dc = FUN_00572a10(DAT_016a1028, DAT_016a1018);
    }
}

// ==================================================================== 0x00dda810
// @ 0x00dda810
bool __stdcall FUN_00dda810(CObj* p, float dt)
{
    if (p->d8 != 0)
        FUN_00dda500(p);

    LI li;
    if (!(p->b0 == 0 && p->b4 == 0)) {
        li.QuadPart = (long long)((TimeBase*)&p->b0)->FUN_0093a3a0();
        if (!(p->e4 < (float)(long long)li.QuadPart * p->c4))
            return p->d5 == 0;
    }

    double t = G_TIMER->FUN_009360d0();
    double v = (t + 1.0) * 5.0;
    double r;
    if (10.0 <= v)
        r = 10.0;
    else if (5.0 <= v)
        r = v;
    else
        r = 5.0;
    p->e4 = (float)r;
    if (p->c0 == 1) {
        unsigned __int64 ts = __rdtsc();
        p->b0 = (unsigned)ts;
        p->b4 = (unsigned)(ts >> 32);
    } else {
        QueryPerformanceCounter(&li);
        *(LI*)&p->b0 = li;
    }
    p->b8 = 0;
    p->bc = 0;
    int idx = G_TIMER->FUN_00a68fb0((DAT_016a0b94 - DAT_016a0b90) >> 2);
    void* sub = p->f4;
    ((void(__thiscall*)(void*, unsigned, int))VSLOT(sub, 4))(sub, *(unsigned*)(DAT_016a0b90 + idx * 4), 0);
    return p->d5 == 0;
}

// ==================================================================== 0x00dda920
// @ 0x00dda920
ObjA* ObjA::FUN_00dda920()
{
    p00 = 0;
    f04 = 0;
    f08 = 0;
    p14 = 0;
    p18 = 0;
    p1c = 0;
    p20 = 0;
    p24 = 0;
    f28 = 0;
    f2c = 0;
    _ReadWriteBarrier();
    w38 = 0;
    w3a = 0;
    f3c = DAT_016a0b0c;
    f40 = DAT_016a0b10;
    f44 = DAT_016a0b14;
    f48 = 1.0f;
    m4c.copy(DAT_016a0b28);
    p70 = 0;
    return this;
}

// ==================================================================== 0x00dda9a0
// @ 0x00dda9a0
void ObjA::FUN_00dda9a0()
{
    Rel* r70 = p70;
    if (r70 != 0)
        r70->vf1();
    if (p24 != 0 && *(int*)((char*)p24 - 4) != 0)
        EASTL_allocator_deallocate(p24);
    Rel* r20 = p20;
    if (r20 != 0)
        r20->vf1();
    Rel* r1c = p1c;
    if (r1c != 0)
        r1c->vf1();
    Rel* r18 = p18;
    if (r18 != 0)
        r18->vf1();
    Rel* r14 = p14;
    if (r14 != 0)
        r14->vf1();
    if (p00 != 0 && *(int*)((char*)p00 - 4) != 0)
        EASTL_allocator_deallocate(p00);
}

// ==================================================================== 0x00ddaa20
// Entered with the argument in EAX and the receiver in ECX (custom register ABI): modelled here
// with the argument as an explicit parameter (equiv UNSUPPORTED, see nonmatching.txt).
// @ 0x00ddaa20
void FUN_00ddaa20(void* self, void* arg)
{
    if (arg == 0)
        return;

    void* r = ((void*(__thiscall*)(void*, int, void*))VSLOT(self, 0xa8))(self, -1, arg);
    if (r == 0)
        return;

    void* sub = *(void**)((char*)r + 8);

    Q q;
    q.a = 0;
    q.b = 0;
    q.x = DAT_016a0b0c;
    q.y = DAT_016a0b10;
    q.z = DAT_016a0b14;
    q.w = 1.0f;
    ((Matrix3*)q.m)->Assign(DAT_016a0b28);

    Q q2;
    q2.a = 0;
    q2.b = 0;
    q2.x = 0.0f;
    q2.y = 0.0f;
    q2.z = 0.0f;
    q2.w = 1.0f;
    ((Dest*)&q)->FUN_006bac90(&q2);
    ((Dest*)&q2)->FUN_006b9440(sub);
}

// ==================================================================== 0x00ddab10
// @ 0x00ddab10
char __stdcall FUN_00ddab10(CObj* p, float dt)
{
    float f7 = p->f4c;
    float f1 = p->f48;
    float ang = p->dc * DAT_016a0b58 * dt * 0.5f;
    float s = sin(ang);
    float c = cos(ang);
    float a = p->ec * s;
    float b = p->e8 * s;
    float d = p->f0 * s;
    float f2 = p->f50;
    float f3 = p->f54;
    p->f48 = f3 * b + c * f1 + (f7 * d - f2 * a);
    p->f4c = f3 * a + f7 * c + (f2 * b - d * f1);
    p->f50 = f3 * d + f2 * c + (a * f1 - f7 * b);
    p->f54 = p->f54 * c - (f2 * d + f7 * a + f1 * b);

    float len = p->f0c * p->f0c + p->f10 * p->f10 + p->f14 * p->f14;
    if (1.0f < len) {
        float inv = DAT_016a0ff8 / len;
        float x = p->f0c;
        float n = 1.0f / sqrt(x * x + p->f10 * p->f10 + p->f14 * p->f14 + 1e-8f);
        p->f24 = -(x * n) * inv;
        p->f28 = -(p->f10 * n) * inv;
        p->f2c = -(p->f14 * n) * inv;
    }
    FUN_00dd9080();
    return 1;
}

// ==================================================================== 0x00ddada0
// @ 0x00ddada0
int __stdcall FUN_00ddada0(CObj* p, float dt)
{
    float f1 = p->f4c;
    float f2 = p->f48;
    float ang = p->dc * DAT_016a0b58 * dt * 0.5f;
    float s = sin(ang);
    float c = cos(ang);
    float a = p->ec * s;
    float d = p->f0 * s;
    float f3 = p->f50;
    float b = s * p->e8;
    float f4 = p->f54;
    p->f48 = f4 * b + f2 * c + (f1 * d - f3 * a);
    p->f4c = f4 * a + f1 * c + (f3 * b - f2 * d);
    p->f50 = f4 * d + f3 * c + (f2 * a - f1 * b);
    p->f54 = p->f54 * c - (f3 * d + f1 * a + f2 * b);

    if (p->e0 <= p->f14 && p->f14 != p->e0)
        FUN_00dda6d0(p);
    return 1;
}

// ==================================================================== 0x00ddaf70
// @ 0x00ddaf70
void* FUN_00ddaf70(void* param_1, int param_2)
{
    Vec12 v;
    v.b = 0;
    v.e = 0;
    v.c = 0;
    void* obj = FUN_0067cb40();

    S9 t1, t2;
    ((Dest*)&t1)->FUN_00558830(0);
    ((Dest*)&t2)->FUN_00558960(0x2dc9d1e, 0, param_2);

    CB34 fn = (CB34)VSLOT(obj, 0x34);
    fn(obj, &v, t1, t2);
    ((Dest*)&t2)->FUN_004e39a0(0, 0);
    ((Dest*)&t1)->FUN_004e39a0(0, 0);

    if (v.b == v.e) {
        *(int*)param_1 = 0;
        ((int*)param_1)[1] = 0;
        ((int*)param_1)[2] = 0;
        if (v.b != 0 && *(int*)(v.b - 4) != 0)
            EASTL_allocator_deallocate(v.b);
    } else {
        unsigned n = (unsigned)G_TIMER->FUN_00a68fb0(0x7fffffff);
        n = n % (unsigned)((v.e - v.b) / 0xc);
        char* src = v.b + n * 0xc;
        ((int*)param_1)[0] = ((int*)src)[0];
        ((int*)param_1)[1] = ((int*)src)[1];
        ((int*)param_1)[2] = ((int*)src)[2];
        if (v.b != 0 && *(int*)(v.b - 4) != 0)
            EASTL_allocator_deallocate(v.b);
    }
    return param_1;
}
