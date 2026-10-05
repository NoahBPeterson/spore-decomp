// Slice s00705660 (batch w2g1, slice 35): lighting-world helpers, small
// vector/struct copy helpers and EASTL vector-of-bool routines.
#include "types.h"
#include <xmmintrin.h>
#include <math.h>

void __stdcall sub_406540(void*, void*, int, int, void*); // EASTL fill/uninitialized helper
void sub_41cb40(void*, void*);                    // Matrix3::Assign
void __fastcall sub_620230(void*);                // intrusive_list_base dtor
void  sub_f47380(void*);                          // operator delete
void* sub_f473a0(unsigned, const char*, int, int, int, int);
void  sub_11e0744(void*, void*, void*);           // DoInsertValue
void  sub_13cc480(void*, void*, int);             // memmove (IAT)

struct __declspec(align(16)) V16 { __m128 m; };
struct __declspec(align(16)) V32 { __m128 a, b; };

// ==========================================================================
// @ 0x00705920  SP::cLightingWorld::GetLightingStateConfig
// ==========================================================================
struct W5920 {
    uint32_t pad[4];        // 0x00
    int**    m10;           // 0x10
    int* get();
};
int* W5920::get()
{
    int** p = m10;
    return p ? *p : 0;
}

// ==========================================================================
// @ 0x00705bb0
// ==========================================================================
struct S11 {
    int   a, b, c;          // 0x00
    float d, e, f, g, h;    // 0x0c
    int   i, j, k;          // 0x20
    S11& operator=(const S11& s);
};
S11& S11::operator=(const S11& s)
{
    a = s.a; b = s.b; c = s.c;
    d = s.d; e = s.e; f = s.f; g = s.g; h = s.h;
    i = s.i; j = s.j; k = s.k;
    return *this;
}

// ==========================================================================
// @ 0x00705c00
// ==========================================================================
struct S7 {
    float f[7];
    S7& operator=(const S7& s);
};
S7& S7::operator=(const S7& s)
{
    f[0] = s.f[0]; f[1] = s.f[1]; f[2] = s.f[2]; f[3] = s.f[3];
    f[4] = s.f[4]; f[5] = s.f[5]; f[6] = s.f[6];
    return *this;
}

// ==========================================================================
// @ 0x00705e90  fill [first,last) with *value
// ==========================================================================
void fill_705e90(__m128* first, __m128* last, const __m128* value)
{
    for (; first != last; ++first)
        *first = *value;
}

// ==========================================================================
// @ 0x00705ec0  fill n elements (destination may be null) with *value
// ==========================================================================
void fill_705ec0(__m128* first, unsigned n, const __m128* value)
{
    for (; n != 0; --n) {
        if (first)
            *first = *value;
        ++first;
    }
}

// ==========================================================================
// @ 0x00705c40  copy [first,last) forward into dst, reporting the end
// ==========================================================================
void copy_705c40(V32** out, V32* first, V32* last, V32* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst) {
                dst->a = _mm_load_ps((const float*)&first->a);
                dst->b = _mm_load_ps((const float*)&first->b);
            }
            ++first;
            ++dst;
        } while (first != last);
        *out = dst;
    }
}

// ==========================================================================
// @ 0x00705ef0  destructor: list dtor + two possibly-null owned buffers
// ==========================================================================
struct W5ef0 {
    void* buf0;             // 0x00
    uint32_t pad[4];
    void* buf14;            // 0x14
    uint32_t pad2[5];
    void dtor();
};
void W5ef0::dtor()
{
    sub_620230((char*)this + 0x2c);
    void* q = buf14;
    if (q != 0 && *(int*)((char*)q - 4) != 0)
        sub_f47380(q);
    q = buf0;
    if (q != 0 && *(int*)((char*)q - 4) != 0)
        sub_f47380(q);
}

// ==========================================================================
// @ 0x00705660  point -> packed 4-bit lighting-grid coordinate
// ==========================================================================
int FUN_00705660(float* a, float* b, float param)
{
    if (param == 0.0f)
        return -1;
    unsigned u1 = (unsigned)(int)(((a[0] - b[0]) / (b[3] - b[0])) * 16.0f);
    unsigned u2 = (unsigned)(int)(((a[1] - b[1]) / (b[4] - b[1])) * 16.0f);
    unsigned u3 = (unsigned)(int)(((a[2] - b[2]) / (b[5] - b[2])) * 4.0f);
    if ((((u2 | u1) & 0xfffffff3U | u3) & 0xfffffffcU) != 0)
        return -1;
    return (u3 * 16 + u2) * 16 + u1;
}

// ==========================================================================
// @ 0x00705970  inverse-blend factor for a distance range
// ==========================================================================
struct W5970 {
    uint32_t pad[4];
    float* m10;             // 0x10
    float f(int a2, float p3);
};
float W5970::f(int a2, float p3)
{
    (void)a2;
    float* b = m10;
    float d = b[0x4c] - b[0x4b];
    if (d < 0.0f)
        return 1.0f;
    if (d == 0.0f) {
        if (p3 < b[0x4b])
            return 1.0f;
        return 0.0f;
    }
    float r = (b[0x4c] - p3) / d;
    float m = r;
    if (m < 0.0f)
        m = 0.0f;
    if (m > 1.0f)
        m = 1.0f;
    return m;
}

// ==========================================================================
// @ 0x00705a20  SP::cLightingManager::SetAtmosphereModel
// ==========================================================================
struct V4 { float x, y, z, w; };
struct W5a20 {
    uint32_t pad[0x12];     // 0x00
    float sunx, suny, sunz; // 0x48
    int   nphases;          // 0x54
    V4    phases[1];        // 0x58
    void setAtm(float* v, int n, float* ph);
};
void W5a20::setAtm(float* v, int n, float* ph)
{
    float inv = 1.0f / sqrtf(((v[0] * v[0] + v[1] * v[1]) + v[2] * v[2]) + 1e-08f);
    sunx = v[0] * inv;
    suny = inv * v[1];
    sunz = inv * v[2];
    nphases = n;
    int cnt = n < 10 ? n : 10;
    for (int i = 0; i < cnt; i++) {
        phases[i].x = ph[0];
        phases[i].y = ph[1];
        phases[i].z = ph[2];
        phases[i].w = ph[3];
        ph += 4;
    }
}

// ==========================================================================
// @ 0x00705af0  linear search over a 0x144-byte-element array
// ==========================================================================
struct W5af0 {
    uint32_t pad[6];        // 0x00
    int*     begin;         // 0x18
    int*     end;           // 0x1c
    void* find(int key);
};
void* W5af0::find(int key)
{
    int n = (int)((char*)end - (char*)begin) / 0x144;
    for (int i = 0; i < n; i++) {
        int* p = (int*)((char*)begin + i * 0x144);
        if (*p != 0 && *(int*)(*p + 8) == key)
            return p;
    }
    return 0;
}

// ==========================================================================
// @ 0x00705b50  copy a shader-data record, deep-copying its coefficient array
// ==========================================================================
void fn705030() {}
struct V4b { float x, y, z, w; };
struct Big5b50 {
    uint8_t  f0;            // 0x00
    uint8_t  f1;            // 0x01
    uint16_t f2;            // 0x02
    float    f4, f8, fc, f10; // 0x04
    char     pad14[0xc];    // 0x14
    __m128   m20;           // 0x20
    V4b      coeffs[25];    // 0x30
    Big5b50* copy(const Big5b50* s);
};
Big5b50* Big5b50::copy(const Big5b50* s)
{
    f0 = s->f0;
    f1 = s->f1;
    f2 = s->f2;
    f4 = s->f4;
    f8 = s->f8;
    fc = s->fc;
    f10 = s->f10;
    m20 = s->m20;
    sub_406540(&coeffs[0], (void*)&s->coeffs[0], 0x10, 0x19, (void*)fn705030);
    return this;
}

// ==========================================================================
// @ 0x00705c80  partial: eastl vector<...>::DoInsertValue (bit-packed)
// ==========================================================================
void FUN_00705c80(void* self, int n) { (void)self; (void)n; }

// ==========================================================================
// @ 0x00705db0  partial: eastl vector<bool> reserve/init
// ==========================================================================
void FUN_00705db0(void* self, unsigned n) { (void)self; (void)n; }

// ==========================================================================
// @ 0x00705740  partial: light-sample projection (477-byte /Od-style math)
// ==========================================================================
void FUN_00705740(int a, float* b, float c, int d) { (void)a; (void)b; (void)c; (void)d; }

// ==========================================================================
// @ 0x00705f40  partial: 556-byte lighting/shadow update
// ==========================================================================
void FUN_00705f40(void* self, void* a) { (void)self; (void)a; }
