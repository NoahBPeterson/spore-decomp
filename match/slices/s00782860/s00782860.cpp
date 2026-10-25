// Slice s00782860: E36 vector insert/push_back/temp-construction, spherical
// harmonic Legendre helpers and three SSE matrix rotations (0x782860..0x783585).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS- module (SSE mixed with x87).
#include "types.h"
#include <math.h>
#include <intrin.h>
#pragma intrinsic(_InterlockedExchangeAdd)

struct IRefObj { virtual void slot0(); virtual void Release(); };
struct E12 { void* p; int a; int b; };
struct Vec12 { E12* begin; E12* end; E12* cap; };
struct E36 {
    void* p0;                       // +0x00
    Vec12 v;                        // +0x04 (ends +0x10)
    char  pad_10[8];                // +0x10
    int   a;                        // +0x18
    unsigned char b;                // +0x1c
    int   c;                        // +0x20
};
struct ShadowBase { void Notify(); };
struct Sub14 { void FreeRange(void* a, void* b); };
struct Vector4 { float x, y, z, w; };

void* EastlAllocate(unsigned int size, const char* name, int a, int b, const char* file, int line);
void  EastlDeallocate(void* p, int a);
void  __fastcall FUN_00781a60(Vec12* self, int dummy, const Vec12* src);
void  __fastcall FUN_00781b10(Vec12* self, int dummy);
E36*  __fastcall FUN_00781c30(E36* self, int dummy, E36 arg);
E36*  FUN_00781b80(E36* first, E36* last, E36* dst);
void  FUN_00781cb0(E36* first, E36* last, E36* dst);
void  FUN_00782470(E36* first, E36* last, E36* dst);
void  __fastcall FUN_00782270(Vec12* self, int dummy, const Vec12* src);
void  __fastcall FUN_00782A60(int p, int dummy, const E36* src);
void  __fastcall FUN_00782860(int p, int dummy, const E36* pos, const E36* value);
void  FUN_00782800(int a, int b);
void  FUN_007806a0(void* self);
void  FUN_00780ab0(void* self);
float FUN_00782bb0(int n);
float FUN_00782db0(float t, int m, float x);
float FUN_00782d40(int a, int b);

extern int   g_153a2fc[16];
extern int   g_153a32c;
extern float g_13f4fd0;
extern float g_14853e0;
extern float g_1485544;
extern float g_140ebbc;
extern float g_140ebb8;
extern float g_153ae10;
extern double g_13f1298;
extern float g_1633e44, g_1633e50, g_1633e58, g_1633e60;
extern int   g_1633e48, g_1633e68;
extern float g_1633e4c, g_1633e54, g_1633e5c, g_1633e64;
extern float g_16340e0, g_16341d8, g_1634090, g_1634068, g_16340d8, g_1634108, g_16340a0;

// ---------------------------------------------------------------------------
// 0x00782BB0 : rising/falling factorial helper
// ---------------------------------------------------------------------------
// @ 0x00782bb0
float FUN_00782bb0(int n)
{
    float f;
    if (n < 0xd) {
        int v = g_153a2fc[n];
        double d = (double)v;                 // x87 fild keeps the extended result the original returns
        if (v < 0)
            d += (double)g_13f4fd0;
        return (float)d;
    }
    f = (float)g_153a32c;
    if (g_153a32c < 0)
        f = f + g_13f4fd0;
    if (7 < n - 0xc) {
        int i = n - 2;
        do {
            int a = i + 1, b = i, c = i - 1, d = i - 2, e = i - 3, gg = i - 4, h = i - 5;
            f = (float)n * f;
            n -= 8;
            i -= 8;
            f = f * (float)a; f = f * (float)b; f = f * (float)c; f = f * (float)d;
            f = f * (float)e; f = f * (float)gg; f = f * (float)h;
        } while (0x13 < n);
    }
    while (0xc < n) {
        f = (float)n * f;
        n -= 1;
    }
    return f;
}

// ---------------------------------------------------------------------------
// 0x00782D40 : normalisation factor
// ---------------------------------------------------------------------------
// @ 0x00782d40
float FUN_00782d40(int l, int m)
{
    if (m == 0)
        return (float)sqrt((double)((float)(l * 2 + 1) / (g_153ae10 * g_14853e0)));
    float a = FUN_00782bb0(l - m);
    float b = FUN_00782bb0(l + m);
    return (float)sqrt((double)((a * (float)(l * 2 + 1)) / ((g_153ae10 * g_14853e0) * b)));
}

// ---------------------------------------------------------------------------
// 0x00782C90 : out = m * (v.x,v.y,v.z)  (column accumulation)
// ---------------------------------------------------------------------------
// @ 0x00782c90
void FUN_00782c90(float* out, const float* m, const float* v)
{
    float vy = v[1];
    float vx = v[0];
    float vz = v[2];
    out[0] = (vy * m[4] + vx * m[0]) + vz * m[8];
    out[1] = (vy * m[5] + vx * m[1]) + vz * m[9];
    out[2] = (vy * m[6] + vx * m[2]) + vz * m[10];
    out[3] = (vy * m[7] + vx * m[3]) + vz * m[11];
}

// ---------------------------------------------------------------------------
// 0x00782CE0 : weighted sum of n 4-vectors
// ---------------------------------------------------------------------------
// @ 0x00782ce0
void FUN_00782ce0(float* out, int n, const float* m, const float* w)
{
    n = n - 1;
    float w0 = w[0];
    float r0 = w0 * m[0], r1 = w0 * m[1], r2 = w0 * m[2], r3 = w0 * m[3];
    out[0] = r0; out[1] = r1; out[2] = r2; out[3] = r3;
    if (0 < n) {
        do {
            float wi = w[1];
            const float* c = m + 4;
            m = m + 4;
            w = w + 1;
            n = n - 1;
            r0 = wi * c[0] + r0;
            r1 = wi * c[1] + r1;
            r2 = wi * c[2] + r2;
            r3 = wi * c[3] + r3;
        } while (0 < n);
        out[0] = r0; out[1] = r1; out[2] = r2; out[3] = r3;
    }
}

// ---------------------------------------------------------------------------
// 0x00783380 : build the 7 SH normalisation constants and copy out
// ---------------------------------------------------------------------------
// @ 0x00783380
void FUN_00783380(float* out)
{
    if ((g_1633e68 & 1) == 0) {
        g_1633e68 |= 1;
        g_1633e4c = (float)sqrt((double)g_153ae10);
        g_1633e54 = 0;
        g_1633e5c = 0;
        g_1633e64 = 0;
        g_1633e50 = (float)sqrt((double)(g_153ae10 * g_1485544));
        g_1633e58 = -(float)sqrt((double)(g_153ae10 * g_140ebbc));
        g_1633e60 = (float)sqrt((double)(g_153ae10 * g_140ebb8));
    }
    struct SH7 { float v[7]; };
    *(SH7*)out = *(SH7*)&g_1633e4c;
}

// ---------------------------------------------------------------------------
// 0x007831D0 : 7-degree SH polynomial evaluation
// ---------------------------------------------------------------------------
// @ 0x007831d0
void FUN_007831d0(float x, float* out)
{
    float x2 = x * x;
    float x3 = x2 * x;
    out[0] = (((1.0f - x) * g_16340e0) * g_153ae10) * 2.0f;
    float f6 = (1.0f - x2) * g_16341d8;
    float f4 = (0.5f - (x2 * 7.5f + ((x3 * x3) * 10.5f - (x2 * x2) * 17.5f))) * g_1634090;
    out[1] = ((1.0f - x2) * g_1634068) * g_153ae10;
    out[5] = (f4 * g_153ae10) * 2.0f;
    out[2] = ((f6 * g_153ae10) * x) * 2.0f;
    float f3 = ((x3 * 10.0f - (x3 * x2) * 7.0f) - x * 3.0f) * g_16340d8;
    out[3] = ((((6.0f - x2 * 5.0f) * x2 - 1.0f) * g_1634108) * g_153ae10) * 0.5f;
    out[4] = (f3 * g_153ae10) * 2.0f;
    out[6] = ((-((x3 * 35.0f + (((x2 * x2) * x3) * 33.0f - (x3 * x2) * 63.0f)) - x * 5.0f) * g_16340a0) * g_153ae10) * 2.0f;
}

// ---------------------------------------------------------------------------
// 0x00783130 : associated Legendre P(l,m) in sin/cos form
// ---------------------------------------------------------------------------
// @ 0x00783130
float FUN_00783130(float theta, unsigned m, float phi, float extra)
{
    if ((g_1633e48 & 1) == 0) {
        g_1633e48 |= 1;
        g_1633e44 = 1.4142135f;
    }
    float c = (float)cos((double)phi);
    int mm = (int)((m ^ ((int)m >> 31)) - ((int)m >> 31));
    float a = (float)FUN_00782db0(theta, mm, c);
    union { float f; int i; } tb;
    tb.f = theta;
    float b = FUN_00782d40(tb.i, mm);   // the original passes the float's bit pattern as the int l
    b = b * a;
    if (m != 0) {
        float ge = g_153ae10 + extra;       // SSE addss rounds g+extra to float, as the original does
        double t = (double)mm * (double)ge; // x87 fild/fmul keeps the extended product
        if (0 < (int)m)
            return cos(t) * g_1633e44 * b;
        return sin(t) * g_1633e44 * b;
    }
    return b;
}

// ---------------------------------------------------------------------------
// 0x00782B00 : cleanup + erase + virtual notify
// ---------------------------------------------------------------------------
// @ 0x00782b00
void __fastcall FUN_00782B00(int p)
{
    FUN_007806a0((char*)p - 8);
    FUN_00782800(*(int*)(p + 0x30), *(int*)(p + 0x34));
    (*(void(__thiscall**)(int))(*(int*)(p + 8) + 0x24))(p + 8);
}

// ---------------------------------------------------------------------------
// 0x00782B30 : build a temp E36 and push_back it
// ---------------------------------------------------------------------------
// @ 0x00782b30
void __fastcall FUN_00782B30(int p)
{
    E36 arg = {};
    arg.p0 = *(void**)(p + 0x10);
    FUN_00781a60(&arg.v, 0, (const Vec12*)(p + 0x14));
    arg.a = *(int*)(p + 0x21c);
    arg.b = *(unsigned char*)(p + 4);
    arg.c = *(int*)(p + 0x218);

    E36 tmp;
    FUN_00781c30(&tmp, 0, arg);         // deep-copies arg.v and destroys it
    FUN_00782A60(p + 0x28, 0, &tmp);
    FUN_00781b10(&tmp.v, 0);
}

// ---------------------------------------------------------------------------
// 0x00782A60 : push_back(E36)
// ---------------------------------------------------------------------------
__declspec(noinline)
// @ 0x00782a60
void __fastcall FUN_00782A60(int p, int dummy, const E36* src)
{
    E36* end = *(E36**)(p + 4);
    if (end < *(E36**)(p + 8)) {
        *(E36**)(p + 4) = end + 1;
        if (end) {
            end->p0 = src->p0;
            FUN_00781a60(&end->v, 0, &src->v);
            end->a = src->a;
            end->b = src->b;
            end->c = src->c;
        }
    } else {
        FUN_00782860(p, 0, end, src);
    }
}

// ---------------------------------------------------------------------------
// 0x00782860 : insert into E36 vector (reallocation path)
// ---------------------------------------------------------------------------
// @ 0x00782860
void __fastcall FUN_00782860(int p, int dummy, const E36* pos, const E36* value)
{
    E36* end = *(E36**)(p + 4);
    if (end != *(E36**)(p + 8)) {
        if (pos <= value && value < end)
            value = (const E36*)((const char*)value + 0x24);
        E36 tmp;
        tmp.p0 = end[-1].p0;
        FUN_00781a60(&tmp.v, 0, &end[-1].v);
        tmp.a = end[-1].a;
        tmp.b = end[-1].b;
        tmp.c = end[-1].c;
        FUN_00782470((E36*)pos, (E36*)((char*)end - 0x24), end);
        ((E36*)pos)->p0 = value->p0;
        FUN_00782270(&((E36*)pos)->v, 0, &value->v);
        ((E36*)pos)->a = value->a;
        ((E36*)pos)->b = value->b;
        ((E36*)pos)->c = value->c;
        *(E36**)(p + 4) = (E36*)((char*)end + 0x24);
        return;
    }
    int count = (int)(end - *(E36**)p) / 0x24;
    int cap = count ? count * 2 : 1;
    int alloc = cap * 0x24;
    E36* buf = (E36*)EastlAllocate(alloc, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    E36* e1 = (E36*)FUN_00781b80(*(E36**)p, (E36*)pos, buf);
    FUN_00781cb0(*(E36**)p, (E36*)pos, buf);
    if (e1) {
        e1->p0 = value->p0;
        FUN_00781a60(&e1->v, 0, &value->v);
        e1->a = value->a;
        e1->b = value->b;
        e1->c = value->c;
    }
    E36* oldEnd = *(E36**)(p + 4);
    E36* e2 = (E36*)FUN_00781b80((E36*)pos, oldEnd, (E36*)((char*)e1 + 0x24));
    FUN_00781cb0((E36*)pos, oldEnd, (E36*)((char*)e1 + 0x24));
    if (*(E36**)p && *(int*)((char*)*(E36**)p - 4) != 0)
        EastlDeallocate(*(E36**)p, 0);
    *(E36**)(p + 4) = e2;
    *(E36**)p = buf;
    *(E36**)(p + 8) = (E36*)((char*)buf + alloc);
}

// ---------------------------------------------------------------------------
// 0x00782DB0 : associated Legendre P_l^m (x)
// ---------------------------------------------------------------------------
// @ 0x00782db0
float FUN_00782db0(float lf, int m, float x)
{
    union { float f; int i; } lb;
    lb.f = lf;
    int l = lb.i;

    float f13 = 1.0f;
    volatile float f16 = 1.0f;
    volatile float acc;
    float local = 1.0f;
    if (0 < m) {
        int i = 1;
        float f12 = (float)sqrt((double)((1.0f - x) * (x + 1.0f)));
        if (7 < m) {
            unsigned n = (unsigned)m >> 3;
            i = (int)(n * 8 + 1);
            do {
                n = n - 1;
                float cf = f13;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                f13 = cf;
            } while (n != 0);
        }
        if (i <= m) {
            int k = (m - i) + 1;
            do {
                k = k - 1;
                acc = -f13; acc = acc * f12; acc = acc * f16; f16 = acc;
                f13 = f13 + 2.0f;
            } while (k != 0);
        }
        local = f16;
    }
    if (l == m)
        return local;
    float A0 = (float)(m * 2 + 1);
    acc = A0 * local; acc = acc * x;
    float prev1 = acc;
    if (l == m + 1)
        return prev1;
    float result = 0.0f;
    int i = m + 2;
    if (i <= l) {
        float prev2 = local;
        while (i <= l) {
            float A = (float)(i * 2 - 1);
            acc = A * prev1; acc = acc * x;
            float B = (float)(i + m - 1);
            float bp = B * prev2;
            acc = acc - bp;
            acc = acc / (float)(i - m);
            prev2 = prev1;
            prev1 = acc;
            result = acc;
            i = i + 1;
        }
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x00783410 : rotate a packed Vector4 list by angle
// ---------------------------------------------------------------------------
// @ 0x00783410
void FUN_00783410(float angle, int n, float* v)
{
    if (n < 2)
        return;
    float co = (float)cos((double)angle);
    float si = (float)sin((double)angle);
    Vector4* q = (Vector4*)v;

    __m128 CO = _mm_set_ss(co);
    __m128 SI = _mm_set_ss(si);
    __m128 cob = _mm_set1_ps(co);
    __m128 sib = _mm_set1_ps(si);

    __m128 lo1 = _mm_loadu_ps((const float*)&q[1]);
    __m128 hi1 = _mm_loadu_ps((const float*)&q[3]);
    _mm_storeu_ps((float*)&q[3], _mm_sub_ps(_mm_mul_ps(hi1, cob), _mm_mul_ps(lo1, sib)));
    _mm_storeu_ps((float*)&q[1], _mm_add_ps(_mm_mul_ps(lo1, cob), _mm_mul_ps(hi1, sib)));

    if (n < 3)
        return;

    float cs[1024];
    cs[0] = co;
    cs[1] = si;
    for (int i = 2; i < n; i++) {
        int pi = 2 * (i - 1);
        __m128 cp = _mm_set_ss(cs[pi - 2]);
        __m128 sp = _mm_set_ss(cs[pi - 1]);
        __m128 c = _mm_sub_ss(_mm_mul_ss(cp, CO), _mm_mul_ss(sp, SI));
        __m128 s = _mm_add_ss(_mm_mul_ss(cp, SI), _mm_mul_ss(sp, CO));
        cs[pi] = _mm_cvtss_f32(c);
        cs[pi + 1] = _mm_cvtss_f32(s);
        for (int m = i; m >= 1; m--) {
            __m128 cm = _mm_set1_ps(cs[2 * (m - 1)]);
            __m128 sm = _mm_set1_ps(cs[2 * (m - 1) + 1]);
            int lidx = i * i + i - m;
            int hidx = i * i + i + m;
            __m128 lv = _mm_loadu_ps((const float*)&q[lidx]);
            __m128 hv = _mm_loadu_ps((const float*)&q[hidx]);
            _mm_storeu_ps((float*)&q[hidx], _mm_sub_ps(_mm_mul_ps(cm, hv), _mm_mul_ps(sm, lv)));
            _mm_storeu_ps((float*)&q[lidx], _mm_add_ps(_mm_mul_ps(sm, hv), _mm_mul_ps(cm, lv)));
        }
    }
}
