// Slice s011559a0 -- SND / rw::audio::core audio library: Pan3D plug-in azimuth
// updates, the azimuth->speaker volume table builder, the CPU feature probe and the
// MIX resample/FX global management.  Same module as s0113ec90; original used
// VC .NET 2003 (/vc71) + /GL + /LTCG.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "../../include/types.h"
#include <math.h>
#include <intrin.h>
#include <xmmintrin.h>

// ---- direct global access (image .data) ------------------------------------
#define A8(a)  (*(unsigned char*)(a))
#define A16(a) (*(unsigned short*)(a))
#define A32(a) (*(unsigned int*)(a))
#define Af(a)  (*(float*)(a))
#define Ap(a)  (*(void**)(a))

struct OSVERSIONINFOA {
    unsigned long dwOSVersionInfoSize;
    unsigned long dwMajorVersion;
    unsigned long dwMinorVersion;
    unsigned long dwBuildNumber;
    unsigned long dwPlatformId;
    char          szCSDVersion[128];
};

extern "C" __declspec(dllimport) int __stdcall GetVersionExA(OSVERSIONINFOA* osvi); // 0x13cc0e0

// ---- callees ---------------------------------------------------------------
void  __cdecl Sub_1133450(void);                       // 0x1133450
void  __cdecl Sub_1133460(void);                       // 0x1133460
void  __cdecl SNDMEMI_alloc(void* dst, int size);      // 0x113ec90
void* __fastcall Sys16_Alloc(void* self, int pad, unsigned size, const char* name,
                             unsigned align, unsigned zero);          // 0x112c820
void  __fastcall Sys16_Free(void* self, int pad, void* p, int z);     // 0x112c850
void  __cdecl Sub_11e0744(void* dst, void* src, unsigned count);      // 0x11e0744
void  __cdecl Sub_11594e0(int a);                      // 0x11594e0
int   __cdecl Sub_11686e0(void);                       // 0x11686e0
void  __cdecl Sub_11686fd(int* out, int leaf);         // 0x11686fd
float __cdecl Sub_1163ce0(float x);                    // 0x1163ce0
float __cdecl Sub_1163c30(float x);                    // 0x1163c30
void  __cdecl Sub_1168960(void* st, int a, int b);     // 0x1168960
void  __cdecl Sub_11596d0(void* a, void* b);           // 0x11596d0
void  __cdecl Sub_1168730(void* st, int pitch);        // 0x1168730

// declaration-only thiscall stubs
struct PlugInStub { void Initialize(); };                              // 0x114f4f0
struct MixStub    { void FUN_0114f100(void* a, void* b, void* c); };   // 0x114f100
struct SubObj {
    void FUN_011604d0(void* buf, int n);       // 0x11604d0
    void FUN_01160540(void);                   // 0x1160540
    void FUN_01160790(void* ctx, void* buf);   // 0x1160790
};

struct VoiceStub {
    char           pad00[0x40];
    float          mFilt[0x20];      // +0x40
    float          mSpan;            // +0xc0
    char           padc4[0x08];      // +0xc4
    unsigned short mSubOff;          // +0xcc
    void FUN_01155bb0(float a, float b);   // 0x1155bb0
    void FUN_011558f0(float a, float b);   // 0x11558f0
};

static inline int Rnd255(double v) {
    return _mm_cvtss_si32(_mm_set_ss((float)(v * 255.0)));
}

// The original computes the sinc coefficients with x87 `fsin` (no CRT `sin` import);
// reproduce the exact extended-precision sequence so no import is called and the
// stored single is bit-identical.
static float X87Sinc(int t, float upper, float lower) {
    volatile int          tt = t;
    volatile float        up = upper, lo = lower, pi = 3.1415927f;
    float r;
    __asm {
        fild  tt
        fld   st(0)
        fmul  up
        fsin
        fld   st(1)
        fmul  lo
        fsin
        fsubp st(1), st(0)
        fld   st(1)
        fmul  pi
        fdivp st(1), st(0)
        fstp  r
    }
    return r;
}

// CPUID is not an intrinsic in cl 13.10; the original used an __asm block for it.
static void CpuId(int* out, int leaf) {
    int* p = out;
    __asm {
        push ebx
        mov  eax, leaf
        cpuid
        mov  [p], eax
        mov  [p+4], ebx
        mov  [p+8], ecx
        mov  [p+12], edx
        pop  ebx
    }
}

// @ 0x011559a0
int FUN_011559a0(int obj, int ctx) {
    float inv = 1.0f / Af(*(int*)(ctx + 0x30018) + 0xc);
    float a = (Af(obj + 0x28) * inv) * 6.2831855f;
    float b = (Af(obj + 0x30) * inv) * 6.2831855f;
    if (a < 0.003141593f) a = 0.003141593f;
    else if (a > 3.138451f) a = 3.138451f;
    if (b < 0.003141593f) b = 0.003141593f;

    if ((!(a <= 1.5707964f) || !(b > (3.1415927f - a) * 2.0f)) &&
        (!(a > 1.5707964f) || !(b > a * 2.0f))) {
        if (a != Af(obj + 0xac) || b != Af(obj + 0xb0)) {
            ((VoiceStub*)obj)->FUN_011558f0(a, b);
            Af(obj + 0xac) = a;
            Af(obj + 0xb0) = b;
        }
        int iVar1 = *(int*)(ctx + 0x3000c);
        int iVar2 = *(int*)(ctx + 0x30010);
        for (int i = 0; i < (int)A8(obj + 0x21); i++) {
            ((MixStub*)(obj + 0x38 + i * 0x10))->FUN_0114f100(
                (void*)(*(int*)(iVar2 + 4) + A16(iVar2 + 0xe) * i * 4),
                (void*)(*(int*)(iVar1 + 4) + A16(iVar1 + 0xe) * i * 4),
                (void*)(obj + 0x98));
        }
        *(int*)(ctx + 0x3000c) = iVar2;
        *(int*)(ctx + 0x30010) = iVar1;
        return 1;
    }

    float eoa = Af(obj + 0xac);
    float eob = Af(obj + 0xb0);
    if ((!(eoa <= 1.5707964f) || !(eob > (3.1415927f - eoa) * 2.0f)) &&
        (!(eoa > 1.5707964f) || !(eob > eoa * 2.0f))) {
        for (int i = 0; i < (int)A8(obj + 0x21); i++)
            ((PlugInStub*)(obj + 0x38 + i * 0x10))->Initialize();
    }
    Af(obj + 0xac) = a;
    Af(obj + 0xb0) = b;
    return 1;
}

// @ 0x01155bb0
void VoiceStub::FUN_01155bb0(float param_2, float param_3) {
    float lower = param_2 - param_3 * 0.5f;
    if (lower < 0.0f) lower = 0.0f;
    float upper = param_3 * 0.5f + param_2;
    if (upper > 3.1415927f) upper = 3.1415927f;

    float* p = mFilt;
    for (int i = 0; i < 0x20; i++)
        p[i] = X87Sinc(i - 32, upper, lower);
    mSpan = (upper - lower) * 0.31830987f;
    volatile float* spanp = &mSpan;
    ((SubObj*)((char*)this + mSubOff))->FUN_011604d0(mFilt, 0x40);
    *spanp = *spanp;
}

// @ 0x01155c80
int FUN_01155c80(int obj, int ctx) {
    float inv = 1.0f / Af(*(int*)(ctx + 0x30018) + 0xc);
    float a = (Af(obj + 0x28) * inv) * 6.2831855f;
    float b = (Af(obj + 0x30) * inv) * 6.2831855f;
    if (a < 0.0f) a = 0.0f;
    else if (a > 3.1415927f) a = 3.1415927f;
    if (b < 0.0f) b = 0.0f;

    int sub = obj + (unsigned short)A16(obj + 0xcc);
    if ((!(a <= 1.5707964f) || !(b > (3.1415927f - a) * 2.0f)) &&
        (!(a > 1.5707964f) || !(b > a * 2.0f))) {
        if (a != Af(obj + 0xc4) || b != Af(obj + 0xc8)) {
            ((VoiceStub*)obj)->FUN_01155bb0(a, b);
            Af(obj + 0xc4) = a;
            Af(obj + 0xc8) = b;
        }
        ((SubObj*)sub)->FUN_01160790((void*)ctx, (void*)(obj + 0x40));
        return 1;
    }
    float eoa = Af(obj + 0xc4);
    float eob = Af(obj + 0xc8);
    if ((!(eoa <= 1.5707964f) || !(eob > (3.1415927f - eoa) * 2.0f)) &&
        (!(eoa > 1.5707964f) || !(eob > eoa * 2.0f))) {
        ((SubObj*)sub)->FUN_01160540();
    }
    Af(obj + 0xc4) = a;
    Af(obj + 0xc8) = b;
    return 1;
}

// @ 0x01155e10
int FUN_01155e10(int obj, int ctx) {
    if (*(int*)(obj + 0x3c) != 0) {
        if (*(int*)(obj + 0x48) == 0)
            *(int*)(obj + 0x48) = (int)(double)Af(*(int*)(ctx + 0x30018) + 0xc);
        int iVar3 = *(int*)(ctx + 0x3000c);
        int iVar4 = *(int*)(*(int*)(*(int*)(obj + 4)) + 0xc);
        unsigned char* src = (unsigned char*)(iVar4 - 0xc00);
        *(int*)(*(int*)(*(int*)(obj + 4)) + 0xc) = (int)src;
        unsigned nch = A8(obj + 0x20);
        for (unsigned c = 0; c < nch; c++) {
            unsigned short stride = A16(iVar3 + 0xe);
            int base = *(int*)(iVar3 + 4);
            for (int s = 0; s < 0x100; s++) {
                float f = Af(base + stride * c * 4 + s * 4);
                if (f > 1.0f) f = 1.0f;
                else if (f < -1.0f) f = -1.0f;
                unsigned char* d = src + (nch * s + c) * 2;
                int v = (int)(f * 32767.0f);
                d[0] = (unsigned char)(v >> 8);
                d[1] = (unsigned char)v;
            }
        }
        Sub_11e0744((void*)A32(obj + 0x40), src, nch << 9);
        *(int*)(*(int*)(*(int*)(obj + 4)) + 0xc) = iVar4;
        A8(obj + 0x4c) = 1;
    }
    return 1;
}

// @ 0x01155f40
void SNDI_precalcaztospkrvol(void) {
    Sub_1133450();
    A32(0x16f16d0) = (unsigned)Sys16_Alloc(Ap(0x16e61a8), 0,
                                           (unsigned)A8(0x16e7bff) << 8,
                                           "Azimuth to Spkr Table", 0x10, 0);
    Sub_1133460();

    unsigned nch = A8(0x16e7bff);
    unsigned p = A32(0x16f16d0);
    for (int i = 0; i < (int)nch; i++) { A32(0x16f16b8 + i * 4) = p; p += 0x100; }

    for (unsigned sp = 0; sp < 0x100; sp++) {
        float ang = (float)((sp & 0xff) << 8) * 0.005493164f;
        if (nch == 1) {
            *(unsigned char*)(A32(0x16f16b8) + sp) = 0x7f;
            continue;
        }
        for (int i = 0; i < (int)nch; i++)
            *(unsigned char*)(sp + A32(0x16f16b8 + i * 4)) = 0;

        if (ang > Af(0x16e7bd0)) {
            if (ang < Af(0x16e7bcc + nch * 4)) {
                for (int i = 0; i < (int)nch; i++) {
                    if (Af(0x16e7bd0 + i * 4) <= ang && ang <= Af(0x16e7bd4 + i * 4)) {
                        float hi = Af(0x16e7bd4 + i * 4) * 0.017453294f;
                        float t = ((ang * 0.017453294f - hi) /
                                   (Af(0x16e7bd0 + i * 4) * 0.017453294f - hi)) * 1.5707964f;
                        *(unsigned char*)(sp + A32(0x16f16b8 + i * 4)) = (unsigned char)Rnd255(Sub_1163ce0(t));
                        *(unsigned char*)(sp + A32(0x16f16bc + i * 4)) = (unsigned char)Rnd255(Sub_1163c30(t));
                    }
                }
            } else {
                float hi = ((360.0f - Af(0x16e7bcc + nch * 4)) * -1.0f) * 0.017453294f;
                float t = ((((360.0f - ang) * -1.0f) * 0.017453294f - hi) /
                           (Af(0x16e7bd0) * 0.017453294f - hi)) * 1.5707964f;
                *(unsigned char*)(A32(0x16f16b8) + sp) = (unsigned char)Rnd255(Sub_1163ce0(t));
                *(unsigned char*)(sp + A32(0x16f16b4 + nch * 4)) = (unsigned char)Rnd255(Sub_1163c30(t));
            }
        } else if (nch < 5) {
            float hi = ((360.0f - Af(0x16e7bcc + nch * 4)) * -1.0f) * 0.017453294f;
            float t = ((ang * 0.017453294f - hi) /
                       (Af(0x16e7bd0) * 0.017453294f - hi)) * 1.5707964f;
            *(unsigned char*)(A32(0x16f16b8) + sp) = (unsigned char)Rnd255(Sub_1163ce0(t));
            *(unsigned char*)(sp + A32(0x16f16b4 + nch * 4)) = (unsigned char)Rnd255(Sub_1163c30(t));
        } else {
            float t = (((ang * 0.017453294f - Af(0x16e7bd4) * 0.017453294f) /
                        (Af(0x16e7bd0) * 0.017453294f - Af(0x16e7bd4) * 0.017453294f))) * 1.5707964f;
            *(unsigned char*)(A32(0x16f16b8) + sp) = (unsigned char)Rnd255(Sub_1163ce0(t));
            *(unsigned char*)(A32(0x16f16bc) + sp) = (unsigned char)Rnd255(Sub_1163c30(t));
        }
    }
}

// @ 0x01156310
void FUN_01156310(int param_1, float* param_2) {
    int edx = (param_1 >> 8) & 0xff;
    if (A8(0x16e7bff) == 0) {
        param_2[5] = 0.0f;
        return;
    }
    for (int i = 0; i < (int)A8(0x16e7bff); i++)
        param_2[i] = (float)(*(unsigned char*)(A32(0x16f16b8 + i * 4) + edx)) * 0.003921569f;
    param_2[5] = 0.0f;
}

// @ 0x01156380
void FUN_01156380(void) {
    Sub_1133450();
    if (A32(0x16f16d0) != 0)
        Sys16_Free(Ap(0x16e61a8), 0, Ap(0x16f16d0), 0);
    A32(0x16f16d0) = 0;
    Sub_1133460();
}

// @ 0x011563b0
void FUN_011563b0(void) {
    A32(0x16e7bd0) = 0;
    A16(0x16e7c8c) = 0xe000;
    A16(0x16e7c8e) = 0x2000;
    A16(0x16e7ca4) = 0xe000;
    A32(0x16e7bd4) = 0x42340000;   // 45.0f
    A16(0x16e7ca6) = 0x2000;
    A16(0x16e7ca8) = 0xa000;
    A16(0x16e7caa) = 0x6000;
    A32(0x16e7bd8) = 0x43070000;   // 135.0f
    A16(0x16e7cbc) = 0xe000;
    A16(0x16e7cbe) = 0;
    A16(0x16e7cc0) = 0x2000;
    A32(0x16e7bdc) = 0x43610000;   // 225.0f
    A32(0x16e7be0) = 0x439d8000;   // 315.0f
    A16(0x16e7cc2) = 0xa000;
    A16(0x16e7cc4) = 0x6000;
    A16(0x16e7cc6) = 0;
}

// @ 0x01156480
void FUN_01156480(int param_1) {
    A32(0x16f16d4) = A32(0x15c3828) + param_1;
    A32(0x16f16d8) = A32(0x15c382c) + param_1;
    A32(0x16f16dc) = A32(0x15c3830) + param_1;
    A32(0x16f16e0) = A32(0x15c3834) + param_1;
    A32(0x16f16e4) = A32(0x15c3838) + param_1;
    A32(0x16f16e8) = A32(0x15c383c) + param_1;
}

// @ 0x011564e0
void FUN_011564e0(int param_1) {
    unsigned short v = A16(param_1 + 0xa);
    unsigned short r;
    if (v > 0x2000) r = 0x2000;
    else if (v < 0x800) r = 0x800;
    else return;
    A16(param_1 + 0xa) = r;
}

// @ 0x01156530
uint64_t FUN_01156530(void) {
    OSVERSIONINFOA os;
    os.dwOSVersionInfoSize = 0x94;
    GetVersionExA(&os);
    int win95 = 0;
    if (os.dwPlatformId == 1 && os.dwMinorVersion == 0) win95 = 1;

    uint32_t r = 1;
    int cpu[4];
    CpuId(cpu, 0);
    if (cpu[0] < 1) return ((uint64_t)1 << 32) | r;
    CpuId(cpu, 1);
    if ((cpu[3] & 0x2000000) && !win95) r = 3;
    CpuId(cpu, 0x80000001);
    if (cpu[3] & 0x80000000) r |= 4;
    return ((uint64_t)1 << 32) | r;
}

// @ 0x01156660
int FUN_01156660(int param_1, int* param_2) {
    unsigned char c = A8(param_1 * 0x84 + 0x24 + A32(0x16e7c78));
    if (c == 0) {
        if (*param_2 < 0) { *param_2 = param_1; return 1; }
    } else {
        *param_2 = *param_2 + 1;
        if (*param_2 < (int)(short)A16(0x16e7c20)) {
            do {
                int p = *param_2 * 0x84 + A32(0x16e7c78);
                if ((unsigned char)*(int*)(p + 0x24) == c &&
                    A8(p + 0x69) == 1 && *(int*)p >= 0)
                    return 1;
                *param_2 = *param_2 + 1;
            } while (*param_2 < (int)(short)A16(0x16e7c20));
        }
    }
    return 0;
}

// @ 0x011566f0
void MIX_createFxglobals(void) {
    int n = *(int*)0x15bfe38;
    int sz = n * 0xc;
    void* p = Sys16_Alloc(Ap(0x16e61a8), 0, (unsigned)sz, "Global FX mems", 0x10, 0);
    A32(0x16f16fc) = (unsigned)p;
    A32(0x16e8084) = (unsigned)p + n * 4;
    A32(0x16e8170) = (unsigned)p + n * 8;
    SNDMEMI_alloc(p, sz);
    void* q = Sys16_Alloc(Ap(0x16e61a8), 0, (unsigned)(n * 4), "Global FX mems", 0x10, 0);
    A32(0x16f1704) = (unsigned)q;
    SNDMEMI_alloc(q, n * 4);
    A32(0x16f1710) = 1;
}

// @ 0x01156780
void FUN_01156780(void) {
    if (A32(0x16f1710) != 0) {
        Sys16_Free(Ap(0x16e61a8), 0, Ap(0x16f16fc), 0);
        int* tbl = (int*)A32(0x16f1704);
        for (int i = 0; i < *(int*)0x15bfe38; i++) {
            int* node = (int*)tbl[i];
            while (node != 0) {
                int* next = (int*)node[0];
                Sys16_Free(Ap(0x16e61a8), 0, node, 0);
                node = next;
            }
        }
        Sys16_Free(Ap(0x16e61a8), 0, (void*)A32(0x16f1704), 0);
        A32(0x16f1710) = 0;
    }
}

// @ 0x01156800
unsigned FUN_01156800(void) {
    OSVERSIONINFOA os;
    int win95 = 0;
    os.dwOSVersionInfoSize = 0x94;
    GetVersionExA(&os);
    unsigned r = 1;
    if (os.dwPlatformId == 1 && os.dwMinorVersion == 0) win95 = 1;
    if (Sub_11686e0() != 0) {
        int cpu[4];
        Sub_11686fd(cpu, 0);
        if (cpu[0] >= 1) {
            Sub_11686fd(cpu, 1);
            if ((cpu[3] & 0x2000000) && !win95) r = 3;
            Sub_11686fd(cpu, 0x80000001);
            if (cpu[3] & 0x80000000) r |= 4;
        }
    }
    return r;
}

// @ 0x011568a0
void MIX_setpitch(int param_1, int param_2) {
    int p = param_1 * 0x5c + A32(0x16e8174);
    if (param_2 > 0x40000) param_2 = 0x40000;
    if (*(int*)(p + 0x50) == 0) {
        void* st = Sys16_Alloc(Ap(0x16e61a8), 0, 0x3c, "Resample Filter State", 0x10, 0);
        *(int*)(p + 0x50) = (int)st;
        int b = (A8(0x16e807c) >= 0x32) ? 1 : 0;
        *(int*)((char*)st + 4) = 0;
        A16((char*)st + 0x18) = 0xa0;
        A8((char*)st + 0x1a) = 0;
        Sub_1168960(st, A8(0x16e7c23), b);
        Sub_11596d0((void*)(p + 0x40), st);
    }
    Sub_1168730((void*)*(int*)(p + 0x50), param_2);
}

// @ 0x01156940
void FUN_01156940(int param_1) {
    int p = param_1 * 0x5c + A32(0x16e8174);
    if (*(int*)(p + 0x4c) != 0)
        Sub_11594e0(*(int*)(p + 0x4c));
}
