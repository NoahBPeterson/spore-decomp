// Slice s007046e0 (batch w2g1, slice 34): Editor resource/bitmap property
// constructors, a type-dispatch factory, and EA::Swarm/text vector helpers.
#include "types.h"
#include <intrin.h>
#include <xmmintrin.h>
#include <math.h>
#include <new>
#pragma intrinsic(_InterlockedExchange)

// --------------------------------------------------------------------------
// external callees / globals (all relocation-masked, so any decl works)
// --------------------------------------------------------------------------
void  sub_704500(void*, void*, int);
int   sub_7045d0(void*, void*);
int   sub_704400(void*, void*);
int   sub_704620(void*, void*);
int   sub_704670(void*, void*);
int   sub_7046c0(void*, void*);
void* sub_f473a0(unsigned size, const char* name, int, int, int, int); // EA_alloc
void  sub_b5f950(void**, void*);                                       // AutoRefCount::operator=

extern int g_types[6];     // 0x140c5f4 (masked)

// --------------------------------------------------------------------------
// Editor property-bitmap hierarchy (base vtable + a secondary polymorphic
// base at +0x18; all vtable targets are relocation-masked).
// --------------------------------------------------------------------------
struct Base0 {
    virtual void b0();
    virtual void b1();
    virtual void b2();
    volatile int mRef;              // +0x04
    int f08, f0c, f10, f14;         // +0x08
    Base0();
};
struct Base1 {
    virtual void s0();
    virtual void s1();
    int f1c, f20, f24, f28;         // +0x1c
    Base1();
};
struct Base1n {                     // secondary base with an empty ctor
    virtual void s0();
    virtual void s1();
    int f1c, f20, f24, f28;
    Base1n();
};
struct Base1f {                     // secondary base that pre-initialises all four
    virtual void s0();
    virtual void s1();
    int f1c, f20, f24, f28;
    Base1f();
};
struct DerA : Base0, Base1n {
    virtual void b0();
    virtual void s0();
    DerA();
};
struct DerB : Base0, Base1 {
    virtual void b0();
    virtual void s0();
    int f2c;
    DerB();
};
struct DerC : Base0, Base1 {
    virtual void b0();
    virtual void s0();
    DerC();
};
struct DerD : Base0, Base1 {
    virtual void b0();
    virtual void s0();
    DerD();
};
struct DerE : Base0, Base1 {
    virtual void b0();
    virtual void s0();
    DerE();
};
struct DerF : Base0, Base1f {
    virtual void b0();
    virtual void s0();
    int f2c;
    DerF();
};
struct DerG : Base0, Base1f {
    virtual void b0();
    virtual void s0();
    DerG();
};

struct RBase {
    virtual void r0();
    virtual void r1();
    volatile int mRef;              // +0x04
    RBase();
};
struct RDer : RBase {
    virtual void r0();
    RDer();
};

struct IVt {
    virtual void* v0();
    virtual void* v1();
    virtual void* v2();
    virtual void* v3();
    virtual void* v4();     // +0x10
    virtual void* v5();     // +0x14
    virtual void* v6();     // +0x18
    virtual int   v7(void*, void*, void*, void*); // +0x24
};

struct __declspec(align(16)) Vec16 { float x, y, z, w; };
struct __declspec(align(16)) V32 { __m128 a, b; };
struct Quad16 { uint32_t w[4]; };

// ==========================================================================
// @ 0x007046e0
// ==========================================================================
void FUN_007046e0(void* a, void* b)
{
    sub_704500(a, b, *(int*)((char*)b + 0x20) * *(int*)((char*)b + 0x1c) * 4);
}

// ==========================================================================
// @ 0x00704700
// ==========================================================================
void FUN_00704700(void* a, void* b)
{
    sub_704500(a, b, *(int*)((char*)b + 0x20) * *(int*)((char*)b + 0x1c) * 6);
}

// ==========================================================================
// @ 0x00704730
// ==========================================================================
int FUN_00704730(IVt* obj, int* out, int a3, int a4)
{
    (void)a3;
    int* p = (int*)obj->v4();
    out[2] = p[0];
    out[3] = a4;
    out[4] = p[2];
    void* b = obj->v6();
    int* q = (int*)obj->v4();
    switch (q[1] + 0xfc1bde17) {
    case 0:
    case 1:
        return sub_7045d0(b, out);
    case 2:
    case 3:
    case 4:
    case 6:
        return sub_704400(b, out);
    default:
        return 0;
    }
}

// ==========================================================================
// @ 0x00704830
// ==========================================================================
int __stdcall FUN_00704830(int* out, unsigned n)
{
    if (out != 0) {
        if (n >= 6) {
            out[0] = g_types[0];
            out[1] = g_types[1];
            out[2] = g_types[2];
            out[3] = g_types[3];
            out[4] = g_types[4];
            out[5] = g_types[5];
            return 6;
        }
        return 0;
    }
    return 6;
}

// ==========================================================================
// @ 0x00704890
// ==========================================================================
bool __stdcall FUN_00704890(int a, int b)
{
    switch (b + 0xfc1bde17) {
    case 0:
        return a == 0x5e90982;
    case 1:
        return a == 0x5e90983;
    case 2:
        return a == 0x5e90985 || a == 0x5e9098a;
    case 3:
        return a == 0x5e90984 || a == 0x5e90989;
    case 4:
        return a == 0x5e90986 || a == 0x5e90987;
    case 6:
        return a == 0x5e90988;
    default:
        return false;
    }
}

// ==========================================================================
// property-bitmap constructors (@ 00704b30 .. 00704d80)
// ==========================================================================
Base0::Base0() { _InterlockedExchange((volatile long*)&mRef, 0); f08 = 0; f0c = 0; f10 = 0; f14 = 0; }
Base1::Base1() { f1c = 0; f20 = 0; f28 = 0; }
Base1n::Base1n() {}
Base1f::Base1f() { f1c = 0; f20 = 0; f24 = -1; f28 = 0; }

DerA::DerA() { f1c = 0; f20 = 0; f24 = -1; f28 = 0; }   // 0x00704b30
DerB::DerB() { f2c = 0; f24 = 0; }            // 0x00704b80
DerC::DerC() { f24 = 1; }                     // 0x00704bd0
DerD::DerD() { f24 = 2; }                     // 0x00704c20
DerE::DerE() { f24 = 3; }                     // 0x00704c70
DerF::DerF() { f2c = 0; }                     // 0x00704cc0
DerG::DerG() {}                               // 0x00704d30

RBase::RBase() { _InterlockedExchange((volatile long*)&mRef, 0); }
RDer::RDer() {}                               // 0x00704d80

// ==========================================================================
// @ 0x00705030
// ==========================================================================
struct Ctx30 {
    __m128 v;
    Ctx30& operator=(const Ctx30& s);
};
Ctx30& Ctx30::operator=(const Ctx30& s) { v = s.v; return *this; }

// ==========================================================================
// @ 0x007050e0
// ==========================================================================
struct Big {
    char pad[0x18];
    int f18, f1c, f20, f24, f28, f2c, f30;
    void set_7050e0(int a, int* p);
    void get_705190(int* out);
};
void Big::set_7050e0(int a, int* p)
{
    f18 = a;
    if (p != 0) {
        f28 = p[3];
        f2c = p[4];
        f30 = p[5];
        f1c = p[0];
        f20 = p[1];
        f24 = p[2];
    }
}

// ==========================================================================
// @ 0x00705190
// ==========================================================================
struct Big50 {
    char pad[0x48];
    int f48, f4c, f50;
    void get_705190(int* out);
};
void Big50::get_705190(int* out)
{
    out[0] = f48;
    out[1] = f4c;
    out[2] = f50;
}

// ==========================================================================
// @ 0x007051b0
// ==========================================================================
struct Fog98 { int x[0x26]; };
struct BigF8 {
    char pad[0xf8];
    Fog98 fog;
    void set_7051b0(const Fog98* src);
};
void BigF8::set_7051b0(const Fog98* src) { fog = *src; }

// ==========================================================================
// @ 0x007051e0
// ==========================================================================
V32* copy_7051e0(const V32* first, const V32* last, V32* out)
{
    for (; first != last; ++first, ++out) {
        if (out) {
            out->a = _mm_load_ps((const float*)&first->a);
            out->b = _mm_load_ps((const float*)&first->b);
        }
    }
    return out;
}

// ==========================================================================
// @ 0x00705220
// ==========================================================================
V32* copy_backward_705220(const V32* first, const V32* last, V32* out)
{
    while (last != first) {
        --last;
        --out;
        out->a = _mm_load_ps((const float*)&last->a);
        out->b = _mm_load_ps((const float*)&last->b);
    }
    return out;
}

// ==========================================================================
// @ 0x00705250
// ==========================================================================
Quad16* copy_705250(const Quad16* first, const Quad16* last, Quad16* result)
{
    for (; first != last; ++first, ++result)
        *result = *first;
    return result;
}

// ==========================================================================
// @ 0x00705290
// ==========================================================================
struct V3 { float x, y, z; };

void mul_705290(V3* a, V3* b)
{
    V3 r;
    r.x = a->x * b->x;
    r.y = a->y * b->y;
    r.z = a->z * b->z;
    *a = r;
}

// ==========================================================================
// @ 0x00705050
// ==========================================================================
struct E5 { int f0, f1, f2, f3, f4; };

int FUN_00705050(int n, E5* p)
{
    int s = 0;
    for (int i = 0; i < n; i++)
        s += (p[i].f4 - p[i].f2) * (p[i].f3 - p[i].f1);
    return s;
}

// ==========================================================================
// @ 0x00705120  SP::cShaderDataLightingInfo::operator=
// ==========================================================================
struct cShaderDataLightingInfo {
    uint8_t  mType;         // +0x00
    uint8_t  mNumCoeffs;    // +0x01
    uint16_t mDummy;        // +0x02
    int      f04, f08, f0c; // +0x04
    float    mCelStrength;  // +0x10
    char     pad14[0xc];    // +0x14
    __m128   mBaseLight;    // +0x20
    __m128   mCoeffs[25];   // +0x30
    cShaderDataLightingInfo& operator=(const cShaderDataLightingInfo& s);
};
cShaderDataLightingInfo&
cShaderDataLightingInfo::operator=(const cShaderDataLightingInfo& s)
{
    mType = s.mType;
    mNumCoeffs = s.mNumCoeffs;
    mDummy = s.mDummy;
    f04 = s.f04;
    f08 = s.f08;
    f0c = s.f0c;
    mCelStrength = s.mCelStrength;
    mBaseLight = s.mBaseLight;
    for (int i = 0; i < 25; i++)
        mCoeffs[i] = s.mCoeffs[i];
    return *this;
}

// ==========================================================================
// @ 0x00704950  dispatch a loaded record to the per-format loader
// ==========================================================================
struct Res4950 {
    virtual void r0();
    virtual void r1();   // +0x04  AddRef
    virtual void r2();   // +0x08  Release
};
struct Factory4950 {
    virtual void f0(); virtual void f1(); virtual void f2();
    virtual void f3(); virtual void f4(); virtual void f5();
    virtual Res4950* Create();   // +0x18
};

bool FUN_00704950(int param_1, Factory4950* param_2, int param_3, int param_4)
{
    (void)param_3;
    Res4950* p = param_2->Create();
    if (p)
        p->r1();
    if (p == 0)
        return false;
    bool r = false;
    if (*(int*)(param_1 + 0xc) == param_4) {
        switch (*(int*)(param_1 + 0xc)) {
        case 0x3e421e9: r = (bool)sub_704620(p, (void*)param_1); break;
        case 0x3e421ea: r = (bool)sub_704670(p, (void*)param_1); break;
        case 0x3e421eb: r = (bool)((int(__cdecl*)(void*, void*))&FUN_00704700)(p, (void*)param_1); break;
        case 0x3e421ec: r = (bool)sub_7046c0(p, (void*)param_1); break;
        case 0x3e421ed: r = (bool)((int(__cdecl*)(void*, void*))&FUN_007046e0)(p, (void*)param_1); break;
        case 0x3e421ef: r = (bool)((int(__cdecl*)(void*, void*))&FUN_00704700)(p, (void*)param_1); break;
        default: break;
        }
    }
    p->r2();
    return r;
}

// ==========================================================================
// @ 0x00704dc0  property-bitmap factory (alloc + construct by format id)
// ==========================================================================
bool FUN_00704dc0(void** out, int type, int param_3)
{
    (void)param_3;
    void* p = 0;
    switch (type + 0xfc1bde17) {
    case 0: {
        DerB* q = (DerB*)sub_f473a0(0x30, "RenderAsset", 0, 0, 0, 0);
        if (q) new (q) DerB();
        p = q;
        break;
    }
    case 1: {
        DerC* q = (DerC*)sub_f473a0(0x2c, "RenderAsset", 0, 0, 0, 0);
        if (q) new (q) DerC();
        p = q;
        break;
    }
    case 2: {
        DerD* q = (DerD*)sub_f473a0(0x2c, "RenderAsset", 0, 0, 0, 0);
        if (q) new (q) DerD();
        p = q;
        break;
    }
    case 3: {
        DerE* q = (DerE*)sub_f473a0(0x2c, "RenderAsset", 0, 0, 0, 0);
        if (q) new (q) DerE();
        p = q;
        break;
    }
    case 4: {
        DerF* q = (DerF*)sub_f473a0(0x30, "RenderAsset", 0, 0, 0, 0);
        if (q) new (q) DerF();
        p = q;
        break;
    }
    case 6: {
        DerG* q = (DerG*)sub_f473a0(0x2c, "RenderAsset", 0, 0, 0, 0);
        if (q) new (q) DerG();
        p = q;
        break;
    }
    default:
        return false;
    }
    void* local = 0;
    sub_b5f950(&local, p);
    if (local != 0) {
        *out = local;
        ((void(__thiscall*)(void*))(*(void***)local)[0])(local);
        ((void(__thiscall*)(void*))(*(void***)local)[1])(local);
        return true;
    }
    return false;
}

// ==========================================================================
// @ 0x00704f60  construct + register a property bitmap through a virtual
// ==========================================================================
int FUN_00704f60(char* self, IVt* param_2, void** param_3, int param_4, int param_5)
{
    void* local = 0;
    int* q = (int*)param_2->v4();
    FUN_00704dc0(&local, param_5, q[1]);
    if (local != 0) {
        int (*fn)(char*, IVt*, void*, int, int) =
            (int (*)(char*, IVt*, void*, int, int))(*(void***)self)[9];
        if ((*fn)(self, param_2, local, param_4, param_5)) {
            *param_3 = local;
            ((void(__thiscall*)(void*))(*(void***)local)[0])(local);
            ((void(__thiscall*)(void*))(*(void***)local)[1])(local);
            return 1;
        }
    }
    if (local != 0)
        ((void(__thiscall*)(void*))(*(void***)local)[1])(local);
    return 0;
}

// ==========================================================================
// @ 0x007052e0  direction -> cubemap texel (32x32 faces)
// ==========================================================================
int FUN_007052e0(float* v, float param)
{
    if (param < 0.5f)
        return -1;
    float x = v[0], y = v[1], z = v[2];
    float ax = fabsf(x), ay = fabsf(y), az = fabsf(z);
    float r7, r8;
    int face;
    if (az < ax || az < ay) {
        if (ay < ax) {
            r7 = (y / x + 1.0f) * 0.5f;
            r8 = (z / ax + 1.0f) * 0.5f;
            face = 2;
            if (x < 0.0f)
                face = 3;
        } else {
            r7 = (z / y + 1.0f) * 0.5f;
            r8 = (x / ay + 1.0f) * 0.5f;
            face = (y < 0.0f) ? 5 : 4;
        }
    } else {
        r7 = (x / z + 1.0f) * 0.5f;
        r8 = (y / az + 1.0f) * 0.5f;
        face = (z < 0.0f) ? 1 : 0;
    }
    int A = (int)(r8 * 32.0f);
    int B = (int)(r7 * 32.0f);
    return ((face * 32 - (A >> 5)) + A) * 32 - (B >> 5) + B;
}

// ==========================================================================
// @ 0x00705470  direction -> cubemap texel (16x16 faces), |v| >= sqrt(10)
// ==========================================================================
int FUN_00705470(float* v, float param)
{
    if (param == 0.0f)
        return -1;
    float x = v[0], y = v[1], z = v[2];
    if ((x * x + y * y) + z * z < 10.0f)
        return -1;
    float ax = fabsf(x), ay = fabsf(y), az = fabsf(z);
    float r7, r8;
    int face;
    if (az < ax || az < ay) {
        if (ay < ax) {
            r7 = (y / x + 1.0f) * 0.5f;
            r8 = (z / ax + 1.0f) * 0.5f;
            face = 2;
            if (x < 0.0f)
                face = 3;
        } else {
            r7 = (z / y + 1.0f) * 0.5f;
            r8 = (x / ay + 1.0f) * 0.5f;
            face = (y < 0.0f) ? 5 : 4;
        }
    } else {
        r7 = (x / z + 1.0f) * 0.5f;
        r8 = (y / az + 1.0f) * 0.5f;
        face = (z < 0.0f) ? 1 : 0;
    }
    int A = (int)(r8 * 16.0f);
    int B = (int)(r7 * 16.0f);
    return ((face * 16 - (A >> 4)) + A) * 16 - (B >> 4) + B;
}
