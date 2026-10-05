// Slice s00782860: E36 vector insert/push_back/temp-construction, spherical
// harmonic Legendre helpers and three SSE matrix rotations (0x782860..0x783585).
// /O2 /MD /Gy /EHsc /TP module (SSE mixed with x87).
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
    bool  b;                        // +0x1c
    int   c;                        // +0x20
};
struct ShadowBase { void Notify(); };
struct Sub14 { void FreeRange(void* a, void* b); };

void* EastlAllocate(unsigned int size, const char* name, int a, int b, const char* file, int line);
void  EastlDeallocate(void* p, int a);
void  FUN_00781a60(Vec12* self, const Vec12* src);
void  FUN_00781b10(Vec12* self);
void  FUN_00781c30(E36* self, int a, const void* src);
E36*  FUN_00781b80(E36* first, E36* last, E36* dst);
void  FUN_00781cb0(E36* first, E36* last, E36* dst);
void  FUN_00782470(E36* first, E36* last, E36* dst);
void  FUN_00782270(Vec12* self, const Vec12* src);
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
float FUN_00782bb0(int n)
{
    float f;
    if (n < 0xd) {
        int v = g_153a2fc[n];
        f = (float)v;
        if (v < 0)
            f = (float)v + g_13f4fd0;
        return f;
    }
    f = (float)g_153a32c;
    if (g_153a32c < 0)
        f = f + g_13f4fd0;
    if (7 < n - 0xc) {
        int i = n - 2;
        do {
            int a = i + 1, b = i, c = i - 1, d = i - 2, e = i - 3, gg = i - 4, h = i - 5;
            n -= 8;
            i -= 8;
            f = (float)n * f;
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
float FUN_00783130(float theta, unsigned m, float phi, float extra)
{
    if ((g_1633e48 & 1) == 0) {
        g_1633e48 |= 1;
        g_1633e44 = 1.4142135f;
    }
    float c = (float)cos((double)theta);
    int mm = (int)((m ^ ((int)m >> 31)) - ((int)m >> 31));
    float a = (float)FUN_00782db0(theta, mm, c);
    float b = FUN_00782d40((int)theta, mm);
    b = b * a;
    if (m != 0) {
        float t = (float)((int)mm * (g_153ae10 + extra));
        if (0 < (int)m)
            return ((float)cos((double)t) * g_1633e44) * b;
        return (((float)sin((double)t) * g_1633e44) * b);
    }
    return b;
}

// ---------------------------------------------------------------------------
// 0x00782B00 : cleanup + erase + virtual notify
// ---------------------------------------------------------------------------
void __fastcall FUN_00782B00(int p)
{
    FUN_007806a0((char*)p - 8);
    FUN_00782800(*(int*)(p + 0x30), *(int*)(p + 0x34));
    (*(void(__thiscall**)(int))(*(int*)(p + 8) + 0x24))(p + 8);
}

// ---------------------------------------------------------------------------
// 0x00782B30 : build a temp E36 and push_back it
// ---------------------------------------------------------------------------
void __fastcall FUN_00782B30(int p)
{
    unsigned char b = *(unsigned char*)(p + 4);
    int a = *(int*)(p + 0x21c);
    int c = *(int*)(p + 0x218);
    Vec12 v;
    FUN_00781a60(&v, (const Vec12*)(p + 0x14));
    E36 tmp;
    FUN_00781c30(&tmp, *(int*)(p + 0x10), 0);
    tmp.a = a; tmp.b = b; tmp.c = c;
    // push_back(&mVec at p+0x28, &tmp) -- argument shape approximate
    (void)v;
    FUN_00781b10(&v);
}

// ---------------------------------------------------------------------------
// 0x00782A60 : push_back(E36)
// ---------------------------------------------------------------------------
void __fastcall FUN_00782A60(int p, const E36* src)
{
    E36* end = *(E36**)(p + 4);
    if (end < *(E36**)(p + 8)) {
        *(E36**)(p + 4) = (E36*)((char*)end + 0x24);
        if (end) {
            end->p0 = src->p0;
            FUN_00781a60(&end->v, &src->v);
            end->a = src->a;
            end->b = src->b;
            end->c = src->c;
        }
    } else {
        // FUN_00782860(end, src) -- reallocation path (see partial.txt)
    }
}

// ---------------------------------------------------------------------------
// 0x00782860 : insert into E36 vector (reallocation path)
// ---------------------------------------------------------------------------
void __fastcall FUN_00782860(int p, const E36* pos, const E36* value)
{
    E36* end = *(E36**)(p + 4);
    if (end != *(E36**)(p + 8)) {
        if (pos <= value && value < end)
            value = (const E36*)((const char*)value + 0x24);
        E36 tmp;
        tmp.p0 = end[-1].p0;
        FUN_00781a60(&tmp.v, &end[-1].v);
        tmp.a = end[-1].a;
        tmp.b = end[-1].b;
        tmp.c = end[-1].c;
        FUN_00782470((E36*)pos, (E36*)((char*)end - 0x24), end);
        ((E36*)pos)->p0 = value->p0;
        FUN_00782270(&((E36*)pos)->v, &value->v);
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
        FUN_00781a60(&e1->v, &value->v);
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
float FUN_00782db0(float lf, int m, float x)
{
    unsigned u = (unsigned)lf;
    float f13 = 1.0f, f16 = 1.0f, f12;
    float local = 1.0f;
    if (0 < m) {
        int i = 1;
        f12 = (float)sqrt((double)((1.0f - x) * (x + 1.0f)));
        if (7 < m) {
            unsigned n = (unsigned)m >> 3;
            i = (int)(n * 8 + 1);
            do {
                n = n - 1;
                float a = (f13 + 2.0f) + 2.0f;
                float b = a + 2.0f;
                float c = b + 2.0f;
                float d = c + 2.0f;
                float e = d + 2.0f;
                float f = e + 2.0f;
                f16 = -f13 * f12 * f16;
                f16 = -(f13 + 2.0f) * f12 * f16;
                f16 = -a * f12 * f16;
                f16 = -b * f12 * f16;
                f16 = -c * f12 * f16;
                f16 = -d * f12 * f16;
                f16 = -e * f12 * f16;
                f16 = -f * f12 * f16;
                f13 = f + 2.0f;
                local = f16;
            } while (n != 0);
        }
        if (i <= m) {
            int k = (m - i) + 1;
            do {
                k = k - 1;
                local = (-f13 * f12) * local;
                f13 = f13 + 2.0f;
            } while (k != 0);
        }
    }
    if (lf != (float)m) {
        f13 = ((float)(m * 2 + 1) * local) * x;
        bool flag = lf != (float)(m + 1);
        float result = f13;
        if (flag) {
            int i = m + 2;
            result = 0.0f;
            if (i <= (int)u) {
                // eight-way unrolled recurrence (see partial.txt)
                while (i <= (int)u) {
                    float t = f13;
                    result = (((float)(i * 2 - 1) * t) * x - (float)(i + m - 1) * local) / (float)(i - m);
                    f13 = result;
                    local = t;
                    i = i + 1;
                }
            }
        }
        return result;
    }
    return local;
}

// ---------------------------------------------------------------------------
// 0x00783410 : rotate a packed Vector4 list by angle
// ---------------------------------------------------------------------------
void FUN_00783410(float angle, int n, float* v)
{
    if (n <= 1)
        return;
    float co = (float)cos((double)angle);
    float si = (float)sin((double)angle);
    float* p = v + 4;
    // first column pair rotation (2x2)
    float a = p[-4], b = p[-3], c = p[-2], d = p[-1];
    p[-4] = co * a - si * p[0];
    p[-3] = co * b - si * p[1];
    p[-2] = co * c - si * p[2];
    p[-1] = co * d - si * p[3];
    (void)a; (void)b; (void)c; (void)d;
    // remaining blocks (see partial.txt)
}
