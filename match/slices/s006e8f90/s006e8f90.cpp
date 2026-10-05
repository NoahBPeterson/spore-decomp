// Slice s006e8f90 -- camera/entity transform + bounds helpers.
// Field offsets are raw (real class layouts uncertain); callees are relocation-masked.
#include <string.h>
#include <intrin.h>
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef unsigned long long u64;

struct E5 {
    void  r7c5350(float);
    void  r7c4ba0(float);
    void  r7c4bc0(float);
    int   r7c4010(void*);
    void  r41cb40(void*);     // rw::math::Matrix33::Assign
    void  r76c210(int);
    void  r76ba30(int, int, int, int, int, int, int, int, int, int, int, int);
    void  r7c50b0(int, int, int);
};

extern void*  f67dd40();
extern void*  f67dd50();
extern void   f_f47380(void*);   // EASTL_allocator_deallocate
extern void   f6e6e90(void*, void*);
extern float  g1533c74;
extern char   g13ec47c;
extern void*  g1618f60;
extern "C" double sqrt(double);

#define VFN(p, off)  (*(void***)(p))[((off) >> 2)]

struct S5 {
    char m_unk[0x240];

    // 0x6e8f90
    void m8f90(float a, float b, float c, unsigned char flags);
    // 0x6e9120
    int  m9120(uint a, uint b);
    // 0x6e9150
    void m9150(int i);
    // 0x6e91c0
    void m91c0();
    // 0x6e91e0
    void m91e0(int a, int b);
    // 0x6e9230
    void m9230(void* src);
    // 0x6e9330
    void m9330(void* src);
    // 0x6e94a0 (free, but declared here for convenience) -- not used
    // 0x6e9530
    void m9530();
    // 0x6e95a0
    void m95a0(unsigned char* p);
    // 0x6e9910
    void m9910(float d);
    // 0x6e9990
    void m9990();
    // 0x6e9a30
    void m9a30();
    // 0x6e9b00
    void m9b00();
    // 0x6e9bf0
    void m9bf0();
    // 0x6e9cc0
    void* m9cc0();
    // 0x6e9d50
    void m9d50(void* out);
};

// 0x6e94a0 -- free function
int f94a0(int p1, int p2, int p3);

// ---------------------------------------------------------------------------
// @ 0x006e8f90
void S5::m8f90(float a, float b, float c, unsigned char flags)
{
    void* o = *(void**)((char*)this + 0xc);
    if (o == 0 || ((int(__thiscall*)(void*))VFN(o, 0x3c))(o) == 0) {
        if (0.0f < a)
            ((E5*)(*(void**)((char*)this + 4)))->r7c5350(a * 360.0f);
        if (0.0f < b)
            ((E5*)(*(void**)((char*)this + 4)))->r7c4ba0(b);
        if (c <= 0.0f)
            return;
        ((E5*)(*(void**)((char*)this + 4)))->r7c4bc0(c);
        return;
    }
    float v[3];
    v[0] = a; v[1] = b; v[2] = c;
    if ((flags & 0x10) != 0) {
        if (0.0f < a)
            ((void(__thiscall*)(void*, int, float*))VFN(o, 4))(o, 0x109d352, &v[0]);
        if (0.0f < b)
            ((void(__thiscall*)(void*, int, float*))VFN(o, 4))(o, 0x109d372, &v[1]);
        if (c <= 0.0f)
            return;
        ((void(__thiscall*)(void*, int, float*))VFN(o, 4))(o, 0x109d375, &v[2]);
        return;
    }
    if (0.0f < a)
        ((void(__thiscall*)(void*, int, float*))VFN(o, 4))(o, 0x109d174, &v[0]);
    if (0.0f < b)
        ((void(__thiscall*)(void*, int, float*))VFN(o, 4))(o, 0x109d1aa, &v[1]);
    if (c <= 0.0f)
        return;
    ((void(__thiscall*)(void*, int, float*))VFN(o, 4))(o, 0x109d1af, &v[2]);
}

// ---------------------------------------------------------------------------
// @ 0x006e9120
int S5::m9120(uint a, uint b)
{
    void* p = *(void**)((char*)this + 0xc);
    if (p != 0 && (a | b) != 0 && (a & b) != 0xffffffff)
        ((void(__thiscall*)(void*, uint))VFN(p, 0x34))(p, a);
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x006e9150
void S5::m9150(int i)
{
    int cnt = (*(int*)((char*)this + 0x14) - *(int*)((char*)this + 0x10)) >> 2;
    if (i < cnt - 1) {
        *(int*)(*(int*)((char*)this + 0x10) + i * 4) = -1;
    } else {
        *(int*)((char*)this + 0x14) -= 4;
        int v = *(int*)(*(int*)((char*)this + 0x14) - 4);
        while (v < 0) {
            *(int*)((char*)this + 0x14) -= 4;
            v = *(int*)(*(int*)((char*)this + 0x14) - 4);
        }
        void* o = *(void**)((char*)this + 0xc);
        ((void(__thiscall*)(void*, int))VFN(o, 0x54))(
            o, *(int*)(*(int*)((char*)this + 0x14) - 4));
        if ((uint)((*(int*)((char*)this + 0x14) - *(int*)((char*)this + 0x10)) & 0xfffffffc) == 4)
            *(int*)((char*)this + 0x14) -= 4;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e91c0
void S5::m91c0()
{
    void* p = *(void**)((char*)this + 8);
    if (p)
        ((E5*)p)->r76c210(0x692ea61);
}

// ---------------------------------------------------------------------------
// @ 0x006e91e0
void S5::m91e0(int a, int b)
{
    if (*(int*)((char*)this + 8) != 0) {
        void* q = f67dd40();
        if (((char(__thiscall*)(void*))VFN(q, 0x38))(q) == 0) {
            ((E5*)(*(void**)((char*)this + 8)))->r76ba30(a, b, 0, b == 0, 0, 0, 0, (int)&g13ec47c, 0, 0, 0, 0);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e9230
void S5::m9230(void* src)
{
    char* d = (char*)this;
    char* s = (char*)src;
    // compiler-generated copy ctor shape (EH); reproduced structurally
    *(uint*)d = *(uint*)s;
    for (int i = 0; i < 8; i++)
        ((uint*)d)[i + 2] = ((uint*)s)[i + 2];
    d += 0x28;
    s += 0x28;
    *(void**)d = *(void**)s;
    if (*(void**)d)
        (*(int*)((char*)*(void**)d + 8))++;
    d += 4; s += 4;
    *(void**)d = *(void**)s;
    if (*(void**)d)
        (*(int*)((char*)d - 4 + 0xc))++;
    d += 4; s += 4;
    for (int i = 0; i < 6; i++) {
        *(float*)d = *(float*)s;
        d += 4; s += 4;
    }
    *(uchar*)d = *(uchar*)s; d++; s++;
    *(uchar*)d = *(uchar*)s; d++; s++;
    for (int i = 0; i < 5; i++) {
        *(uint*)d = *(uint*)s;
        d += 4; s += 4;
    }
    d += 4;
    *(void**)d = *(void**)s;
    if (*(void**)d)
        ((void(__thiscall*)(void*))VFN(*(void**)d, 4))(*(void**)d);
}

// ---------------------------------------------------------------------------
// @ 0x006e9330
void S5::m9330(void* src)
{
    char* d = (char*)this;
    char* s = (char*)src;
    *(uint*)d = *(uint*)s;
    memcpy(d + 8, s + 8, 32);
    *(void**)(d + 0x28) = *(void**)(s + 0x28);
    if (*(void**)(d + 0x28))
        (*(int*)((char*)*(void**)(d + 0x28) + 4))++;
    *(float*)(d + 0x2c) = *(float*)(s + 0x2c);
    *(float*)(d + 0x30) = *(float*)(s + 0x30);
    *(float*)(d + 0x34) = *(float*)(s + 0x34);
    *(float*)(d + 0x38) = *(float*)(s + 0x38);
    *(float*)(d + 0x3c) = *(float*)(s + 0x3c);
    *(float*)(d + 0x40) = *(float*)(s + 0x40);
    *(float*)(d + 0x44) = *(float*)(s + 0x44);
    *(uchar*)(d + 0x48) = *(uchar*)(s + 0x48);
    *(uchar*)(d + 0x49) = *(uchar*)(s + 0x49);
    *(float*)(d + 0x4c) = *(float*)(s + 0x4c);
    *(float*)(d + 0x50) = *(float*)(s + 0x50);
    *(float*)(d + 0x54) = *(float*)(s + 0x54);
    *(float*)(d + 0x58) = *(float*)(s + 0x58);
    *(uint*)(d + 0x5c) = *(uint*)(s + 0x5c);
    *(uint*)(d + 0x60) = *(uint*)(s + 0x60);
    *(uint*)(d + 0x64) = *(uint*)(s + 0x64);
    *(uint*)(d + 0x68) = *(uint*)(s + 0x68);
}

// ---------------------------------------------------------------------------
// @ 0x006e94a0
int f94a0(int p1, int p2, int p3)
{
    if (p1 != p2) {
        do {
            void* r = *(void**)(p1 + 0x28);
            if (r != 0) {
                unsigned n = *(unsigned*)((char*)r + 4);
                n += 0xffffffffu;
                *(unsigned*)((char*)r + 4) = n;
                if (n == 0) {
                    *(int*)((char*)r + 4) = 1;
                    _ReadWriteBarrier();
                    ((void(__thiscall*)(void*, int))VFN(r, 0))(r, 1);
                }
            }
            p1 += 0x70;
            p3 += 0x70;
        } while (p1 != p2);
    }
    return p3;
}

// ---------------------------------------------------------------------------
// @ 0x006e9530
struct Vec3 { float x, y, z; };
static inline Vec3 MakeV3(float c)
{
    Vec3 v;
    v.x = c; v.y = c; v.z = c;
    return v;
}
void S5::m9530()
{
    float c = g1533c74;
    *(Vec3*)((char*)this) = MakeV3(c);
    *(Vec3*)((char*)this + 0xc) = MakeV3(-c);
}

// ---------------------------------------------------------------------------
// @ 0x006e95a0
void S5::m95a0(unsigned char* p)
{
    float* self = (float*)this;
    float C = g1533c74;
    if (self[0] == C || self[0] == -C)
        return;
    if ((p[0] >> 1 & 1) != 0) {
        float f4 = self[3], f7 = self[1], f9 = self[2];
        float f5 = self[4], f8 = self[5];
        float f1 = self[3], f2 = self[4], f12 = self[5];
        float f3 = *(float*)(p + 0x10) * 0.5f;
        float m[6];
        f6e6e90(p + 0x14, m);
        float f11 = (f8 - f9) * f3;
        float f10 = (f5 - f7) * f3;
        f8 = (f4 - self[0]) * f3;
        f4 = (m[3] * f11 + m[0] * f10) + m[5] * f8;
        f5 = (m[2] * f11 + m[4] * f10) + m[1] * f8;
        f12 = (f12 + f9) * f3;
        f9 = (f1 + self[0]) * f3;
        float f6 = (m[1] * f11 + m[2] * f10) + m[3] * f8;
        f3 = (f2 + f7) * f3;
        f8 = *(float*)(p + 4) +
             ((*(float*)(p + 0x2c) * f12 + *(float*)(p + 0x20) * f3) +
              f9 * *(float*)(p + 0x14));
        f7 = *(float*)(p + 8) +
             ((*(float*)(p + 0x30) * f12 + *(float*)(p + 0x24) * f3) +
              *(float*)(p + 0x18) * f9);
        f9 = *(float*)(p + 0xc) +
             ((*(float*)(p + 0x34) * f12 + *(float*)(p + 0x28) * f3) +
              *(float*)(p + 0x1c) * f9);
        self[0] = f8 - f4;
        self[1] = f7 - f5;
        self[2] = f9 - f6;
        self[3] = f4 + f8;
        self[4] = f5 + f7;
        self[5] = f6 + f9;
        return;
    }
    float k = *(float*)(p + 0x10);
    float s0 = self[0], s2 = self[2], s1 = self[1];
    self[0] = s0 * k;
    self[2] = s2 * k;
    self[1] = k * s1;
    float a8 = *(float*)(p + 8), ac = *(float*)(p + 0xc);
    self[0] = s0 * k + *(float*)(p + 4);
    self[1] = a8 + k * s1;
    self[2] = ac + s2 * k;
    float k2 = *(float*)(p + 0x10);
    self[3] = self[3] * k2;
    self[4] = self[4] * k2;
    self[5] = self[5] * k2;
    float b8 = *(float*)(p + 8), bc = *(float*)(p + 0xc);
    self[3] = *(float*)(p + 4) + self[3];
    self[4] = b8 + self[4];
    self[5] = bc + self[5];
}

// ---------------------------------------------------------------------------
// @ 0x006e9910
void S5::m9910(float d)
{
    float* p = (float*)this;
    float f = p[0];
    float C = g1533c74;
    if (f != C && f != -C) {
        p[0] = f - d;
        p[1] = p[1] - d;
        p[2] = p[2] - d;
        p[3] = p[3] + d;
        p[4] = p[4] + d;
        p[5] = p[5] + d;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e9990
void S5::m9990()
{
    char* self = (char*)this;
    *(void**)self = (void*)0x140af90;
    {
        int a = *(int*)(self + 0x10);
        if (a != 0 && *(int*)(a - 4) != 0)
            f_f47380((void*)a);
    }
    {
        void* p = *(void**)(self + 0xc);
        if (p)
            ((void(__thiscall*)(void*))VFN(p, 0xc))(p);
    }
    {
        int p = *(int*)(self + 8);
        if (p) {
            void* q = *(void**)(p + 8);
            ((void(__thiscall*)(void*))VFN(q, 0xc))(q);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e9a30
void S5::m9a30()
{
    char* self = (char*)this;
    {
        int a = *(int*)(self + 0x30d68);
        if (a != 0 && *(int*)(a - 4) != 0)
            f_f47380((void*)a);
    }
    {
        int a = *(int*)(self + 0x30d54);
        if (a != 0 && *(int*)(a - 4) != 0)
            f_f47380((void*)a);
    }
    {
        int* p = *(int**)(self + 4);
        if (p) {
            int n = p[1] - 1;
            p[1] = n;
            if (n == 0) {
                p[1] = 1;
                ((void(__thiscall*)(void*, int))VFN(p, 0))(p, 1);
            }
        }
    }
    {
        int* p = *(int**)self;
        if (p) {
            int* c = (int*)((char*)p + 8);
            int n = *c - 1;
            *c = n;
            if (n < 1) {
                *c = n + 1;
                return;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e9b00
void S5::m9b00()
{
    char* p = (char*)this;
    *(uint*)(p + 0) = 0;
    *(int*)(p + 8) = -1;
    *(int*)(p + 0xc) = -1;
    *(uchar*)(p + 0x10) = 0;
    *(uchar*)(p + 0x11) = 0;
    *(uchar*)(p + 0x12) = 0;
    *(uchar*)(p + 0x13) = 0;
    *(ushort*)(p + 0x14) = 0;
    *(float*)(p + 0x18) = 0.0f;
    *(int*)(p + 0x20) = -1;
    *(int*)(p + 0x24) = -1;
    *(int*)(p + 0x28) = 0;
    *(int*)(p + 0x2c) = 0;
    float C = g1533c74;
    *(float*)(p + 0x30) = C;
    *(float*)(p + 0x34) = C;
    *(float*)(p + 0x38) = C;
    float N = -C;
    *(float*)(p + 0x3c) = N;
    *(float*)(p + 0x40) = N;
    *(float*)(p + 0x44) = N;
    *(uchar*)(p + 0x48) = 0;
    *(uchar*)(p + 0x49) = 0;
    float one = 1.0f;
    *(float*)(p + 0x4c) = one;
    *(float*)(p + 0x50) = one;
    *(float*)(p + 0x54) = one;
    *(float*)(p + 0x58) = one;
    *(int*)(p + 0x5c) = 0;
    *(int*)(p + 0x60) = 0;
    *(int*)(p + 0x64) = 0;
    *(int*)(p + 0x68) = 0;
    *(int*)(p + 0x6c) = 0;
}

// ---------------------------------------------------------------------------
// @ 0x006e9bf0
void S5::m9bf0()
{
    char* p = (char*)this;
    *(uint*)(p + 0) = 0;
    *(float*)(p + 0x18) = 0.0f;
    float C = g1533c74;
    *(uchar*)(p + 0x10) = 0;
    *(uchar*)(p + 0x11) = 0;
    *(uchar*)(p + 0x12) = 0;
    *(uchar*)(p + 0x13) = 0;
    *(int*)(p + 8) = -1;
    *(int*)(p + 0xc) = -1;
    *(int*)(p + 0x20) = -1;
    *(int*)(p + 0x24) = -1;
    *(ushort*)(p + 0x14) = 0;
    *(int*)(p + 0x28) = 0;
    *(float*)(p + 0x2c) = C;
    *(float*)(p + 0x30) = C;
    *(float*)(p + 0x34) = C;
    float N = -C;
    *(float*)(p + 0x38) = N;
    *(float*)(p + 0x3c) = N;
    *(float*)(p + 0x40) = N;
    float one = 1.0f;
    *(float*)(p + 0x44) = one;
    *(uchar*)(p + 0x48) = 0;
    *(uchar*)(p + 0x49) = 0;
    *(float*)(p + 0x4c) = one;
    *(float*)(p + 0x50) = one;
    *(float*)(p + 0x54) = one;
    *(float*)(p + 0x58) = one;
    *(int*)(p + 0x5c) = 0;
    *(int*)(p + 0x60) = 0;
    *(int*)(p + 0x64) = 0;
    *(int*)(p + 0x68) = 0;
}

// ---------------------------------------------------------------------------
// @ 0x006e9cc0
void* S5::m9cc0()
{
    char* p = (char*)this;
    float one = 1.0f;
    *(uint*)(p + 0) = 0;
    *(float*)(p + 4) = one;
    *(float*)(p + 8) = one;
    *(float*)(p + 0xc) = one;
    *(float*)(p + 0x10) = one;
    *(float*)(p + 0x14) = one;
    *(ushort*)(p + 0x1a) = 0;
    *(ushort*)(p + 0x18) = 0;
    *(float*)(p + 0x1c) = *(float*)0x1618de0;
    *(float*)(p + 0x20) = *(float*)0x1618de4;
    *(float*)(p + 0x24) = *(float*)0x1618de8;
    *(float*)(p + 0x28) = one;
    ((E5*)(p + 0x2c))->r41cb40(&g1618f60);
    *(uchar*)(p + 0x50) = 0;
    *(uchar*)(p + 0x51) = 0;
    *(int*)(p + 0x54) = 0;
    *(int*)(p + 0x58) = 0;
    *(int*)(p + 0x5c) = 0;
    *(int*)(p + 0x60) = 0;
    *(int*)(p + 0x64) = -1;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x006e9d50
void S5::m9d50(void* out)
{
    char* self = (char*)this;
    char* o = (char*)out;
    int* src = *(int**)(self + 0x20);
    if (!src)
        return;
    *(int*)(o + 0x5c) = src[0];
    *(int*)(o + 0x60) = src[1];
    *(int*)(o + 0x64) = src[2];
    *(int*)(o + 0x68) = src[4];
    *(int*)(o + 0x6c) = src[5];
    *(int*)(o + 0x70) = src[6];
    *(int*)(o + 0x74) = src[8];
    *(int*)(o + 0x78) = src[9];
    *(int*)(o + 0x7c) = src[10];
    *(int*)(o + 0x80) = src[0xc];
    *(int*)(o + 0x84) = src[0xd];
    *(int*)(o + 0x88) = src[0xe];
    if (*(char*)(self + 0x1e5) == 0) {
        *(int*)(o + 0x8c) = src[0xc];
        *(int*)(o + 0x90) = src[0xd];
        *(int*)(o + 0x94) = src[0xe];
    } else {
        *(int*)(o + 0x8c) = *(int*)(self + 0x1e8);
        *(int*)(o + 0x90) = *(int*)(self + 0x1ec);
        *(int*)(o + 0x94) = *(int*)(self + 0x1f0);
    }
    int* s = (int*)(*(int*)(self + 0x20) + 0xc0);
    int* d = (int*)(o + 0x1c);
    for (int i = 0; i < 0x10; i++)
        d[i] = s[i];
    if (*(char*)(self + 0x1f4) == 0) {
        *(char*)(o + 0xb0) = 0;
        *(int*)(self + 0x44) = (int)o;
        *(char*)(self + 0x1f4) = 0;
        return;
    }
    int rect[4];
    ((E5*)(*(void**)(self + 0x20)))->r7c4010(rect);
    int v1 = *(int*)(self + 0x1f8);
    int v2 = *(int*)(self + 0x1fc);
    *(int*)(o + 0x98) = *(int*)(o + 0x80);
    *(int*)(o + 0x9c) = *(int*)(o + 0x84);
    *(int*)(o + 0xa0) = *(int*)(o + 0x88);
    int m = *(int*)(self + 0x20);
    float fy = (float)((rect[2] - v2) * 2) / (float)(rect[3] - rect[2]) + 1.0f;
    float fx = (float)((v1 - rect[0]) * 2) / (float)(rect[1] - rect[0]) - 1.0f;
    float w = 1.0f / (((*(float*)(m + 0x11c) * fy + *(float*)(m + 0x10c) * fx) +
                       *(float*)(m + 0x13c)) + *(float*)(m + 0x12c));
    float fz = (((*(float*)(m + 0x118) * fy + *(float*)(m + 0x108) * fx) +
                 *(float*)(m + 0x138)) + *(float*)(m + 0x128)) * w - *(float*)(o + 0xa0);
    float fyy = (((*(float*)(m + 0x114) * fy + *(float*)(m + 0x104) * fx) +
                  *(float*)(m + 0x134)) + *(float*)(m + 0x124)) * w - *(float*)(o + 0x9c);
    float fxx = (((*(float*)(m + 0x110) * fy + *(float*)(m + 0x100) * fx) +
                  *(float*)(m + 0x130)) + *(float*)(m + 0x120)) * w - *(float*)(o + 0x98);
    *(char*)(o + 0xb0) = 1;
    float n = 1.0f / (float)sqrt((double)((fxx * fxx + (fyy * fyy + fz * fz)) + 1e-08f));
    *(float*)(o + 0xa4) = n * fxx;
    *(float*)(o + 0xa8) = fyy * n;
    *(float*)(o + 0xac) = fz * n;
    *(uint*)(o + 0xb8) = *(uint*)(o + 0xb4) ^ *(uint*)(self + 0x200);
    *(uint*)(o + 0xb4) = *(uint*)(self + 0x200);
    *(int*)(self + 0x44) = (int)o;
    *(char*)(self + 0x1f4) = 0;
}
