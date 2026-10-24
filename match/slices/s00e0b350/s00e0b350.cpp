// Slice s00e0b350 - SporeApp 0x00e0b350..0x00e0c1f0 (cSPUIMinimapWin region).
// All functions are __thiscall with `this` in ecx unless noted otherwise.
// Base flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"
#include <wchar.h>
#include <string.h>
#include <math.h>
#include <intrin.h>

typedef unsigned int  uint;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// ---- externals (hex names resolve by address) --------------------------------
void* __cdecl FUN_00806370(void* p);                       // 0x00806370
void  __cdecl FUN_00806a60(void* a, void* b, int c, int d); // 0x00806a60
float* __cdecl FUN_00e0b350(float* out, void* a2, float* a3, float* a4, float f5, float* a6);
float* __cdecl FUN_00e0b580(float* out, void* a2, float* a3, float* a4, float* a5, float f6, void* a7);
float* __cdecl FUN_00e0b580b(void* out, void* in);          // 0x00e0b580 (2-arg view)
char  __cdecl FUN_00e0a950();                              // 0x00e0a950
u32   __cdecl FUN_00e0a9a0(float* p, int a, void* b);       // 0x00e0a9a0
static inline float Call_E0AA80(void* p, float a, float b) {
    return ((float (__thiscall*)(void*, float, float))0x00e0aa80)(p, a, b);
}
void* __cdecl FUN_00b5b800();                              // 0x00b5b800
u32   __cdecl FUN_00b3d380();                              // 0x00b3d380
int   __cdecl FUN_01002bd0();                              // 0x01002bd0
u32   __cdecl FUN_01021080();                              // 0x01021080
void* __cdecl FUN_00ffbe50(float* p, int a, int b, int c, int d); // 0x00ffbe50
u32   __cdecl FUN_00ffc350(void* p);                       // 0x00ffc350
void* __cdecl FUN_00b3d300();                              // 0x00b3d300
void* __cdecl FUN_00b1fdb0(void* p);                       // 0x00b1fdb0
u32   __cdecl FUN_00c1c1d0(void* p, int a, float* b, float c, float d); // 0x00c1c1d0
u32   __cdecl FUN_00b3d280();                              // 0x00b3d280
void  __cdecl FUN_00b146a0(float* p, int a, int b);         // 0x00b146a0
void  __cdecl FUN_00b16270();                              // 0x00b16270
void* __cdecl FUN_00cf74c0(int a, ...);                    // 0x00cf74c0
void* __cdecl FUN_00cf74f0();                              // 0x00cf74f0
u32   __cdecl FUN_00cf2520(void* p, int a, int b, float* c); // 0x00cf2520
u32   __cdecl FUN_00cf8d70(void* p, int a);                // 0x00cf8d70
void* __cdecl FUN_00cd40b0();                              // 0x00cd40b0
u32   __cdecl FUN_00cd02d0(float* p);                      // 0x00cd02d0
void  __cdecl FUN_00cd4b70(int a);                         // 0x00cd4b70
u32   __cdecl FUN_00cd4460(u32 key);                       // 0x00cd4460
u32   __cdecl FUN_00cd6980(void* p, u32 key);              // 0x00cd6980
void* __cdecl FUN_00b3d350();                              // 0x00b3d350
void* __cdecl FUN_0067dd10();                              // 0x0067dd10  SP::App
extern "C" int __stdcall QueryPerformanceCounter(void* p);

// ---- vtable-slot call helpers -----------------------------------------------
static inline void RefAddRef(void* p) {
    ((void (__thiscall*)(void*))*((void***)*(void**)p + 0))(p);
}
static inline void RefRelease(void* p) {
    ((void (__thiscall*)(void*))*((void***)*(void**)p + 1))(p);
}
static inline void VT_90(void* p) {
    ((void (__thiscall*)(void*))*((void***)*(void**)p + 0x90 / 4))(p);
}
static inline void* VT_38(void* p) {
    return ((void* (__thiscall*)(void*))*((void***)*(void**)p + 0x38 / 4))(p);
}
static inline void VT_7C(void* p, int a, int b) {
    ((void (__thiscall*)(void*, int, int))*((void***)*(void**)p + 0x7c / 4))(p, a, b);
}
static inline void* VT_A8(void* p) {
    return ((void* (__thiscall*)(void*))*((void***)*(void**)p + 0xa8 / 4))(p);
}
static inline void VT_18(void* p, void* out, int a, int b) {
    ((void (__thiscall*)(void*, void*, int, int))*((void***)*(void**)p + 0x18 / 4))(p, out, a, b);
}
static inline void VT_74(void* p, float a, float b) {
    ((void (__thiscall*)(void*, float, float))*((void***)*(void**)p + 0x74 / 4))(p, a, b);
}
static inline void VT_EC(void* p, void* a) {
    ((void (__thiscall*)(void*, void*))*((void***)*(void**)p + 0xec / 4))(p, a);
}
static inline int VT_0C_0(void* p) {
    return ((int (__thiscall*)(void*))*((void***)*(void**)p + 0xc / 4))(p);
}
static inline void VT_70(void* p, void* a) {
    ((void (__thiscall*)(void*, void*))*((void***)*(void**)p + 0x70 / 4))(p, a);
}
static inline void VT_8C(void* p) {
    ((void (__thiscall*)(void*))*((void***)*(void**)p + 0x8c / 4))(p);
}

// ---- value types -------------------------------------------------------------
struct ObjB {                     // 0x24 bytes, ref-counted pointer at 0x14
    u32   m0;
    float m4;
    float m8;
    float mC;
    u32   m10;
    void* mRef;
    float m18;
    u32   m1C;
    u32   m20;

    ObjB* FUN_00e0bd70(const ObjB& o);                 // 0x00e0bd70
};

struct ObjC {                     // 0x24 bytes, ref-counted pointer at 0x14
    u32   m0;
    u32   m4;
    u32   m8;
    u32   mC;
    u32   m10;
    void* mRef;
    float m18;
    u32   m1C;
    u32   m20;

    ObjC* FUN_00e0bdc0(const ObjC& o);                 // 0x00e0bdc0
};

struct cSPUIMinimapWin {
    void* mp000;                                       // 0x000
    void* mpObj4;                                      // 0x004  object (vtable at +4)
    char  pad008[0x1f8 - 0x08];
    float mF1F8;                                       // 0x1f8
    float mF1FC;                                       // 0x1fc
    char  pad200[0x218 - 0x200];
    float mF218;                                       // 0x218
    float mF21C;                                       // 0x21c
    float mF220;                                       // 0x220
    char  pad224[0x23c - 0x224];
    int   mI23C;                                       // 0x23c
    int   mI240;                                       // 0x240
    char  pad244[0x254 - 0x244];
    void* mpField254;                                  // 0x254
    void* mpField258;                                  // 0x258
    char  pad25C[0x280 - 0x25c];
    u8    mBytes280[0x84];                             // 0x280
    float mVec304[3];                                  // 0x304
    char  pad310[0x338 - 0x310];
    float mVec338[3];                                  // 0x338  icon position
    float mVec344[3];                                  // 0x344
    float mF350;                                       // 0x350
    char  pad354[0x35c - 0x354];
    u32   mFlags35C;                                   // 0x35c
    char  pad360[0x98c - 0x360];
    void* mpField98C;                                  // 0x98c  ref-counted

    void  FUN_00e0b970();                              // 0x00e0b970
    char  FUN_00e0bcb0(void* p2, float* out, void* p4); // 0x00e0bcb0
    void  FUN_00e0be50();                              // 0x00e0be50
    u32   FUN_00e0b990(float* p2, int p3, void* p4, char p5); // 0x00e0b990
    void  FUN_00e0c1f0(float* v);                      // 0x00e0c1f0
    void  ComputeIconPositionFromMinimapCoords(float* p2, void* p3, char p4); // 0x00e0bf40
};

// =============================================================================
// @ 0x00e0b350
float* FUN_00e0b350(float* out, void* a2, float* a3, float* a4, float f5, float* a6)
{
    (void)a2;
    float ay = a4[1];
    float ax = a4[0];
    float az = a4[2];
    out[0] = 0.0f;
    out[1] = 0.0f;
    float lim    = *(float*)0x15a4c00;
    float halfpi = *(float*)0x15a4bfc;
    float pi     = *(float*)0x16a2024;
    float pitchA = (float)atan2((double)az, (double)sqrtf(ay * ay + ax * ax));
    float half   = 0.5f;
    float yawA   = (float)atan2((double)ay, (double)ax);
    float dA     = (halfpi - yawA) - f5;
    float b      = dA;
    float by = a3[1];
    float bx = a3[0];
    float yawB = halfpi - (float)atan2((double)by, (double)bx);
    float d    = yawB;
    float pitchB = (float)atan2((double)a3[2], (double)sqrtf(bx * bx + by * by));
    if (dA <= 0.0f) {
        if (0.0f < d) {
            d = yawB - pi;
            if (lim < fabsf((yawB - pi) - dA))
                b = b - pi;
        }
    } else {
        if (d < 0.0f) {
            d = pi + d;
            yawB = d;
        }
        if (lim < fabsf(yawB - dA))
            b = pi + b;
    }
    float v1 = 1.0f - (d - b) / (f5 * 2.0f);
    float v0 = 1.0f - (pitchB - (pitchA - f5 * half)) / f5;
    out[1] = v0;
    out[0] = v1;
    if (lim <= f5)
        return out;
    if (a6 && (1.0f < v1 || 1.0f < v0 || v1 < 0.0f || v0 < 0.0f))
        *a6 = (float)atan2((double)v0 - (double)half, (double)v1 - (double)half);
    float c0 = 0.0f;
    if (0.0f <= v0)
        c0 = v0;
    if (1.0f <= c0)
        c0 = 1.0f;
    out[1] = c0;
    float c1 = 0.0f;
    if (0.0f <= v1)
        c1 = v1;
    if (1.0f <= c1)
        c1 = 1.0f;
    out[0] = c1;
    return out;
}

// @ 0x00e0b580
float* FUN_00e0b580(float* out, void* a2, float* a3, float* a4, float* a5, float f6, void* a7)
{
    (void)a2;
    void* gm = FUN_00b5b800();
    if (gm != (void*)0x1654c05 && gm != (void*)0x1654c04)
        return FUN_00e0b350(out, a2, a3, a4, f6, (float*)a7);

    float v6 = a3[0];
    float v7 = a3[1];
    float v11 = a3[2];
    float n2 = 1.0f / sqrtf(v11 * v11 + (v7 * v7 + v6 * v6) + 1e-08f);
    float u14 = a5[1];
    float u13 = a5[2];
    float u1  = a5[0];
    float w8  = u13 * a4[1] - u14 * a4[2];
    float w9  = u1 * a4[2] - a4[0] * u13;
    float w12 = a4[0] * u14 - u1 * a4[1];
    float n3 = 1.0f / sqrtf(w9 * w9 + (w12 * w12 + w8 * w8) + 1e-08f);
    float dot = (u14 * (v7 * n2) + u13 * (v11 * n2)) + u1 * (v6 * n2);
    v11 = v11 * n2 - u13 * dot;
    u13 = v6 * n2 - u1 * dot;
    u14 = v7 * n2 - u14 * dot;
    float n4 = 1.0f / sqrtf(u14 * u14 + (v11 * v11 + u13 * u13) + 1e-08f);
    float ang1 = (float)acos((double)((float)((n4 * u13) * (n3 * w8)) +
                                       (float)((v11 * n4) * (w12 * n3)) +
                                       (float)((u14 * n4) * (w9 * n3))));
    if ((n4 * u13) * (n3 * w8) + (v11 * n4) * (w12 * n3) + (u14 * n4) * (w9 * n3) < 0.0f)
        ang1 = *(float*)0x16a2024 - ang1;
    float a1 = ang1 / (f6 * 2.0f);
    float a0 = (float)((double)acos(0.0) / (double)f6);
    if (f6 < *(float*)0x15a4c00) {
        float c0 = 0.0f;
        if (0.0f <= a0)
            c0 = a0;
        if (1.0f <= c0)
            c0 = 1.0f;
        a0 = c0;
        float c1 = 0.0f;
        if (0.0f <= a1)
            c1 = a1;
        if (1.0f <= c1)
            c1 = 1.0f;
        a1 = c1;
        out[0] = a0;
        out[1] = a1;
        return out;
    }
    out[0] = a1;
    out[1] = a0;
    return out;
}

// @ 0x00e0b970
void cSPUIMinimapWin::FUN_00e0b970()
{
    void* p = mpField254;
    if (p)
        return VT_90((char*)p + 4);
}

// @ 0x00e0bcb0
char cSPUIMinimapWin::FUN_00e0bcb0(void* p2, float* out, void* p4)
{
    void* g = FUN_00b3d350();
    void* o = g ? *(void**)((char*)g + 0x24) : 0;
    if (!o)
        return 0;
    if (VT_0C_0(o) == 0)
        return 0;
    void* r = ((void* (__thiscall*)(void*, void*, float*, float*, float, void*))
               ((void***)*(void**)o)[0xc / 4])(o, p2, mVec338, mVec344, mF350, p4);
    float buf[2];
    float* tmp = FUN_00e0b580b(buf, r);
    out[0] = tmp[0];
    out[1] = tmp[1];
    out[1] = (float)mI240 * out[1];
    float y = out[1];
    float x = (float)mI23C * out[0];
    out[0] = Call_E0AA80(this, x, y);
    return 1;
}

// @ 0x00e0c1f0
void cSPUIMinimapWin::FUN_00e0c1f0(float* v)
{
    float x = v[0];
    float y = v[1];
    float z = v[2];
    float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f);
    mVec338[0] = x * inv;
    mVec338[1] = y * inv;
    mVec338[2] = z * inv;
    VT_90((char*)this + 4);
    VT_8C(this);
    mFlags35C |= 3;
}

// @ 0x00e0b990
u32 cSPUIMinimapWin::FUN_00e0b990(float* p2, int p3, void* p4, char p5)
{
    char cVar2 = FUN_00e0a950();
    u64 stamp;
    if (*(u32*)0x16a2038 == 1) {
        u64 t = __rdtsc();
        stamp = t;
        *(u32*)0x16a2028 = (u32)t;
    } else {
        QueryPerformanceCounter(&stamp);
        *(u32*)0x16a2028 = (u32)stamp;
    }
    u32 r = 0;
    *(u32*)0x16a2030 = 0;
    *(u32*)0x16a2034 = 0;
    *(u32*)0x16a1fa0 = 0;
    float dy = p2[1] - mVec304[1];
    float dx = p2[0] - mVec304[0];
    float dz = p2[2] - mVec304[2];
    *(u32*)0x16a202c = (u32)(stamp >> 32);
    if (0.001f < (dy * dy + dx * dx) + dz * dz) {
        void* mode = FUN_00b5b800();
        if (mode == (void*)0x1654c05) {
            u32 t = FUN_00b3d380();
            if ((*(u8*)(t + 0x48) & 1) == 0) {
                int sg = FUN_01002bd0();
                r = 0;
                if (sg != 0 && FUN_01021080() == 0) {
                    void* ufo = FUN_00ffbe50(p2, 0, 1, 0, 0);
                    r = FUN_00ffc350(ufo);
                    return r & 0xffffff00;
                }
            }
        } else if (mode == (void*)0x1654c01) {
            void* nm = FUN_00b3d300();
            void* av = FUN_00b1fdb0(nm);
            r = 0;
            if (av) {
                r = FUN_00c1c1d0(av, 2, p2, 1.0f, 2.0f);
                return r & 0xffffff00;
            }
        } else {
            r = FUN_00b3d280();
            if (r != 0) {
                if (mode == (void*)0x1654c04) {
                    if (p5 != 0) {
                        if (p3 != 0x3ea) {
                            FUN_00b146a0(p2, 1, 0);
                            FUN_00b16270();
                            void* st = FUN_00cf74c0(0);
                            r = FUN_00cf8d70(st, 0);
                            return r & 0xffffff00;
                        }
                        FUN_00cf74c0(0, 2, p2);
                        void* cs = FUN_00cf74f0();
                        r = FUN_00cf2520(cs, 0, 2, p2);
                        return r & 0xffffff00;
                    }
                    if (cVar2 != 0) {
                        if (p3 == 1000) {
                            FUN_00b146a0(p2, 1, 1);
                            void* st = FUN_00cf74c0(0);
                            r = FUN_00cf8d70(st, 0);
                            return r & 0xffffff00;
                        }
                        return r & 0xffffff00;
                    }
                } else {
                    if (p5 != 0) {
                        void* ts = FUN_00cd40b0();
                        if (p3 == 0x3ea) {
                            VT_70(ts, p2);
                            r = FUN_00cd02d0(p2);
                            return r & 0xffffff00;
                        }
                        FUN_00b146a0(p2, 1, 0);
                        FUN_00b16270();
                        FUN_00cd4b70(0);
                        r = FUN_00cd4460(0x56d1871);
                        if ((char)r == 0 && (r = FUN_00cd4460(0x64be5ff), (char)r != 0)) {
                            r = FUN_00cd6980(ts, 0x64d44f9);
                            return r & 0xffffff00;
                        }
                        return r & 0xffffff00;
                    }
                    if (cVar2 != 0) {
                        if (p3 == 1000) {
                            FUN_00b146a0(p2, 1, 1);
                            void* ts = FUN_00cd40b0();
                            FUN_00cd4b70(0);
                            r = FUN_00cd4460(0x56d1871);
                            if ((char)r == 0 && (r = FUN_00cd4460(0x64be5ff), (char)r != 0)) {
                                r = FUN_00cd6980(ts, 0x64d44f9);
                                return r & 0xffffff00;
                            }
                        }
                        return r & 0xffffff00;
                    }
                }
                r = FUN_00e0a9a0(p2, p3, p4);
            }
        }
    }
    return r & 0xffffff00;
}

// @ 0x00e0bf40
void cSPUIMinimapWin::ComputeIconPositionFromMinimapCoords(float* p2, void* p3, char p4)
{
    float* r1 = (float*)VT_38(p3);
    float lo0 = r1[0];
    float lo1 = r1[1];
    float lo2 = r1[2];
    float lo3 = r1[3];
    float x = p2[0];
    float y = p2[1];
    float edge = (float)mBytes280[(int)(mF218 * y) + 0x30] * mF220;
    void* iw = mpObj4;
    int flag = 1;
    float* r2 = (float*)VT_38(iw);
    float inner0 = r2[0];
    float inner2 = r2[2];
    void* app = FUN_0067dd10();
    void* gm = VT_38(app);
    float big = (lo2 - lo0) * 2.0f;
    if ((gm == (void*)0x1654c02 || (gm == (void*)0x1654c10 && p4 == 0)) &&
        (x < big + edge || ((inner2 - inner0) - edge) - big < x))
        flag = 0;
    float halfH = (lo3 - lo1) * 0.5f;
    if ((gm != (void*)0x1654c02 && (gm != (void*)0x1654c10 || p4 != 0)) ||
        (halfH <= y && y <= ((float*)VT_38(iw))[3] - ((float*)VT_38(iw))[1] - halfH)) {
        float* r3 = (float*)VT_38(iw);
        if (halfH <= y && (r3[3] - r3[1]) - halfH < y)
            VT_38(iw);
    } else {
        flag = 0;
    }
    void* o = (void*)((void* (__thiscall*)(void*, int, int))
                      ((void***)*(void**)p3)[0x7c / 4])(p3, 1, flag);
    float w = lo3 - lo1;
    ((void (__thiscall*)(void*, float, float))
     ((void***)*(void**)o)[0x64 / 4])(o, w, y);
}

// @ 0x00e0bd70
ObjB* ObjB::FUN_00e0bd70(const ObjB& o)
{
    m0  = o.m0;
    m4  = o.m4;
    m8  = o.m8;
    mC  = o.mC;
    m10 = o.m10;
    mRef = o.mRef;
    if (mRef)
        RefAddRef(mRef);
    m18 = o.m18;
    m1C = o.m1C;
    m20 = o.m20;
    return this;
}

// @ 0x00e0bdc0
ObjC* ObjC::FUN_00e0bdc0(const ObjC& o)
{
    m0  = o.m0;
    m4  = o.m4;
    m8  = o.m8;
    mC  = o.mC;
    m10 = o.m10;
    void* nv = o.mRef;
    if (nv != mRef) {
        void* old = mRef;
        if (nv)
            RefAddRef(nv);
        mRef = nv;
        if (old)
            RefRelease(old);
    }
    m18 = o.m18;
    m1C = o.m1C;
    m20 = o.m20;
    return this;
}

// @ 0x00e0be50
void cSPUIMinimapWin::FUN_00e0be50()
{
    void* base = this ? (char*)this + 4 : 0;
    void* nv = FUN_00806370(base);
    void* old = mpField98C;
    if (nv != old) {
        if (nv)
            RefAddRef(nv);
        mpField98C = nv;
        if (old)
            RefRelease(old);
    }
    VT_7C(mpField98C, 0x10, 1);
    VT_7C(mpField98C, 1, 0);
    FUN_00806a60(mpField98C, mpField258, 0x24a451fc, -1);
    void* r = VT_A8(mpField98C);
    if (r) {
        float pos[2];
        VT_18(r, pos, 0, 0);
        VT_74(mpField98C, pos[0], pos[1]);
    }
    VT_EC((char*)this + 4, mpField98C);
}
