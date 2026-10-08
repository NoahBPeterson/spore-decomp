// Slice s01142a20: RenderWare 4 audio core (rw::audio) - MIX mixer create/submit,
// voice pitch/detune helpers, and the SIMD sample-decode/convert routines.
// Built with VC .NET 2003 (cl 13.10) + /GL /LTCG, /arch:SSE.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <string.h>

// ---------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------

struct System;

extern "C" void* g_16e8174;       // 0x16e8174  mixer voice array base
extern "C" int   g_numChannels;   // 0x15bfe38  mixer channel count
extern "C" int*  g_16e8084;       // 0x16e8084  per-channel enabled flags (pointer)
extern "C" int*  g_16f16fc;       // 0x16f16fc  per-channel decoder-instance ptrs (pointer)
extern "C" float* g_16e8170;      // 0x16e8170  mix accumulate buffer (pointer)
extern "C" float g_16e8158[];     // 0x16e8158  per-bus mix accumulate
extern "C" void* g_16e8120;       // 0x16e8120
extern "C" float* g_16e8124;      // 0x16e8124
extern "C" void* g_16e8128[];     // 0x16e8128  mixer output buffers
extern "C" void* g_16e8140[];     // 0x16e8140  mixer output buffers (aligned)
extern "C" uint8_t g_numOutputs;  // 0x16e8079
extern "C" uint8_t g_16e807c;     // 0x16e807c
extern "C" void* g_16e8070;       // 0x16e8070
extern "C" int   g_16e8074;       // 0x16e8074  stop-callback
extern "C" int   g_16e8078;       // 0x16e8078
extern "C" int   g_16e8080;       // 0x16e8080  post-slice callback
extern "C" int   g_16e8178;       // 0x16e8178  stretch fn
extern "C" int   g_16e817c;       // 0x16e817c
extern "C" int   g_16f1700;       // 0x16f1700
extern "C" int   g_16e7c1c;       // 0x16e7c1c  callbacks-enabled flag
extern "C" uint8_t g_16e7c23;     // 0x16e7c23
extern "C" void* g_sndvoices;     // 0x16e7c78  voice record array (0x84)
extern "C" uint8_t g_15bffe0[];   // 0x15bffe0
extern "C" uint8_t g_15bfee0[];   // 0x15bfee0
extern "C" uint32_t g_tab300[];   // 0x14cb300
extern "C" uint32_t g_tab2c4[];   // 0x14cb2c4
extern "C" System* g_system;      // 0x16e61a8

class System {
public:
    uint8_t pad00[0x14];
    void* Alloc(int size, const char* name, int align, int flags); // 0x112c820
    void  Free(void* p, int flags);                                // 0x112c850
};

// ---------------------------------------------------------------------------
// Callees
// ---------------------------------------------------------------------------

void  FUN_01156510(void*);                        // 0x1156510
void  FUN_01156520(void*);                        // 0x1156520
void  FUN_01159850(void*);                        // 0x1159850
void  FUN_01133450(void);                         // 0x1133450
void  FUN_01133460(void);                         // 0x1133460
void  FUN_01156780(void);                         // 0x1156780
void  MIX_createFxglobals(void);                  // 0x11566f0
void  FUN_01159810(void);                         // 0x1159810
void  FUN_011597d0(void);                         // 0x11597d0
void  FUN_01159760(void);                         // 0x1159760
void  SNDMEMI_alloc(void*, int);                  // 0x113ec90
void  FUN_01142100(float*, float*);               // 0x1142100
int   FUN_01142470(void*);                        // 0x1142470
void  MIX_stop(int);                              // 0x1142960
void* FUN_011e0744(void*, const void*, uint32_t); // 0x11e0744 (memcpy)
void* FUN_01156bb0(void);                         // (unused placeholder)
int   FUN_01141150(uint32_t);                     // 0x1141150
int   FUN_01156660(int, void*);                   // 0x1156660
void  SNDPLATFORM_stop(int);                      // 0x1140ab0
extern "C" int   iSNDdetunetolinear(uint32_t);     // 0x1143310
extern "C" void  FUN_01143460(int, void*);         // 0x1143460
void  FUN_01142c90(void*, int);                   // 0x1142c90
void  FUN_01158d00(void);                         // 0x1158d00
void  FUN_01158c60(void);                         // 0x1158c60
void  FUN_01158be0(void);                         // 0x1158be0
void  FUN_01142650(int);                          // 0x1142650
void  FUN_01142670(void*);                        // 0x1142670

typedef int (__cdecl *MixCodecFn2)(void*, int, void*, void*, int);
typedef int (__cdecl *StretchFn2)(int, float, float*, float*);


// ===========================================================================
//  FUN_01142a20
// ===========================================================================
// @ 0x01142a20
extern "C" void FUN_01142a20(int a, int b, float f)
{
    *(float*)((char*)g_16e8174 + 0x1c + (a * 0x17 + b) * 4) = f;
    *((char*)g_16e8174 + a * 0x5c + 1) = 1;
}

// ===========================================================================
//  FUN_01142a50
// ===========================================================================
// @ 0x01142a50
extern "C" void FUN_01142a50(int a, int b, float f)
{
    *(float*)(*(int*)((char*)g_16e8174 + a * 0x5c + 0x38) + b * 4) = f;
    *((char*)g_16e8174 + a * 0x5c + 1) = 1;
}

// ===========================================================================
//  MIX_create  0x01142a80
// ===========================================================================
// @ 0x01142a80
extern "C" void MIX_create(int* cfg)
{
    FUN_01156510((void*)&FUN_01142650);
    FUN_01156520((void*)&FUN_01142670);
    FUN_01159850((void*)0x112e9a0);
    g_16e8070 = (void*)cfg[0];
    g_16e8074 = cfg[1];
    g_16e8078 = cfg[2];
    FUN_01133450();
    MIX_createFxglobals();
    for (int i = 0; i < g_numChannels; i++)
        g_16e8084[i] = 0;

    char* p = (char*)&g_16e8120;
    do {
        void* buf = g_system->Alloc(0x10bc, "Mixer Ping Pong Temp Buf", 0x10, 0);
        *(void**)(p - 8) = buf;
        *(uint32_t*)p = ((uint32_t)buf + 0x47) & 0xffffffc0;
        p += 4;
    } while ((int)p < (int)&g_16e8128);

    for (int i = 0; i < (g_16e8078 >> 8); i++) {
        void* buf = g_system->Alloc(0x440, "Mixer Output Buffer", 0x10, 0);
        g_16e8128[i] = buf;
        g_16e8140[i] = (void*)(((uint32_t)buf + 0x3f) & 0xffffffc0);
    }

    if ((uint8_t)g_16e8078 != 0) {
        int sz = (g_numChannels * 8 + 0x5c) * ((uint8_t)g_16e8078);
        g_16e8174 = g_system->Alloc(sz, "Mixer Voice State", 0x10, 0);
        SNDMEMI_alloc(g_16e8174, sz);
        char* v = (char*)g_16e8174 + ((uint8_t)g_16e8078) * 0x5c;
        for (int i = 0; i < (uint8_t)g_16e8078; i++) {
            *(int*)((char*)g_16e8174 + i * 0x5c + 0x34) = (int)v;
            v += g_numChannels * 4;
            *(int*)((char*)g_16e8174 + i * 0x5c + 0x38) = (int)v;
            v += g_numChannels * 4;
        }
    }

    FUN_01133460();
    FUN_01159810();
    FUN_011597d0();
    FUN_01159760();
    g_16e817c = (int)&FUN_01158d00;
    g_16e8178 = (int)&FUN_01158c60;
    if ((g_16e7c23 & 2) == 0)
        g_16e8178 = (int)&FUN_01158be0;
    for (int i = 0; i < (g_16e8078 >> 8); i++)
        SNDMEMI_alloc(g_16e8140[i], 0x400);
}

// ===========================================================================
//  FUN_01142c90   (mixer submit / slice)
// ===========================================================================
// @ 0x01142c90
extern "C" void FUN_01142c90(int* out, int nsamples)
{
    for (int i = 0; i < g_numChannels; i++) {
        if (g_16e8084[i] != 0 && g_16e8170[i] != 0.0f)
            FUN_01142100(&g_16e8170[i], (float*)(size_t)g_16f16fc[i]);
    }
    for (int i = 0; i < (int)g_numOutputs; i++) {
        SNDMEMI_alloc(g_16e8140[i], nsamples * 4);
        float* d;
        if (g_16e8158[i] != 0.0f) {
            d = (float*)g_16e8140[i];
            d[0]  = g_16e8158[i] * 0.94117647f + d[0];
            d[1]  = g_16e8158[i] * 0.88235294f + d[1];
            d[2]  = g_16e8158[i] * 0.82352942f + d[2];
            d[3]  = g_16e8158[i] * 0.76470590f + d[3];
            d[4]  = g_16e8158[i] * 0.70588237f + d[4];
            d[5]  = g_16e8158[i] * 0.64705884f + d[5];
            d[6]  = g_16e8158[i] * 0.58823532f + d[6];
            d[7]  = g_16e8158[i] * 0.52941179f + d[7];
            d[8]  = g_16e8158[i] * 0.47058824f + d[8];
            d[9]  = g_16e8158[i] * 0.41176471f + d[9];
            d[10] = g_16e8158[i] * 0.35294119f + d[10];
            d[11] = g_16e8158[i] * 0.29411766f + d[11];
            d[12] = g_16e8158[i] * 0.23529412f + d[12];
            d[13] = g_16e8158[i] * 0.17647059f + d[13];
            d[14] = g_16e8158[i] * 0.11764706f + d[14];
            d[15] = g_16e8158[i] * 0.05882353f + d[15];
            g_16e8158[i] = 0.0f;
        }
    }

    int voiceIdx = 0;
    for (int vi = 0; vi < (uint8_t)g_16e8078; vi++) {
        char* v = (char*)g_16e8174 + vi * 0x5c;
        if (v[0] == 2) {
            int consumed;
            int need;
            if (v[1] == 0) {
                consumed = 0;
                need = nsamples;
            } else {
                consumed = FUN_01142470(v);
                v[1] = 0;
                need = nsamples - consumed;
            }
            if (need != 0) {
                void* codec = *(void**)(v + 0x40);
                int r = (*(MixCodecFn2*)codec)(codec, need, g_16e8120, g_16e8124, 0);
                if (r < 0) {
                    MIX_stop(vi);
                    ((void (*)(int))g_16e8074)(vi);
                } else if (r != 0) {
                    *(float*)(v + 0x3c) = g_16e8124[r - 1];
                    for (int j = 0; j < (int)g_numOutputs; j++) {
                        float fv = *(float*)(v + 0x1c + j * 4);
                        if (fv != 0.0f)
                            ((StretchFn2)g_16e8178)(r, fv, g_16e8124,
                                (float*)((char*)g_16e8140[j] + consumed * 4));
                    }
                    for (int j = 0; j < g_numChannels; j++) {
                        if (g_16e8084[j] != 0) {
                            float fv = *(float*)(*(int*)(v + 0x38) + j * 4);
                            if (fv != 0.0f) {
                                ((StretchFn2)g_16e8178)(r, fv, g_16e8124,
                                    (float*)((char*)(size_t)g_16f16fc[j] + consumed * 4));
                                g_16f1700 = 0;
                            }
                        }
                    }
                }
            }
        }
        voiceIdx++;
    }
    if (g_16e8080 != 0)
        ((void (*)(int))g_16e8080)(nsamples);
    if (g_numOutputs != 0) {
        for (int i = 0; i < (int)g_numOutputs; i++) {
            FUN_011e0744((void*)out[i], g_16e8140[i], nsamples * 4);
        }
    }
    for (int i = 0; i < (int)g_numOutputs; i++) {
        float* p = (float*)out[i];
        for (int k = 0; k < nsamples; k++)
            p[k] = p[k] * 3.05e-05f;
    }
}

// ===========================================================================
//  FUN_011431a0
// ===========================================================================
// @ 0x011431a0
extern "C" void FUN_011431a0(int* src, int total)
{
    int local[6];
    for (int i = 0; i < (int)g_numOutputs; i++)
        local[i] = src[i];
    while (total > 0) {
        int n = total < 0x101 ? total : 0x100;
        FUN_01142c90(local, n);
        for (int i = 0; i < (int)g_numOutputs; i++)
            local[i] += 0x400;
        total -= 0x100;
    }
}

// ===========================================================================
//  FUN_01143210
// ===========================================================================
// @ 0x01143210
extern "C" void FUN_01143210(int index)
{
    char* v = (char*)g_sndvoices + index * 0x84;
    float f = (float)(int)*(int16_t*)(v + 0x42) * (float)(int)*(int8_t*)(v + 0x2b)
            * *(float*)(v + 0x38) * 6.2000123e-05f;
    *(float*)(v + 0x48) = f;
    int p = *(int*)(v + 0x74);
    if (p != 0)
        *(float*)(v + 0x48) = (float)(int)*(int8_t*)(*(uint8_t*)(v + 0x50) + p) * f
                            * 0.0078740157f;
    p = *(int*)(v + 0x70);
    if (p != 0) {
        float t = *(float*)(v + 0x48) * 127.0f;
        int idx;
        __asm { cvtss2si eax, t }
        __asm { mov idx, eax }
        *(float*)(v + 0x48) = (float)(int)*(int8_t*)(p + idx);
    }
}

// ===========================================================================
//  FUN_011432a0
// ===========================================================================
// @ 0x011432a0
extern "C" int FUN_011432a0(uint32_t handle)
{
    if (g_16e7c1c == 0)
        return 0xfffffff6;
    int idx = FUN_01141150(handle);
    if (idx >= 0) {
        int local = -1;
        int r = FUN_01156660(idx, &local);
        while (r != 0) {
            SNDPLATFORM_stop(local);
            r = FUN_01156660(idx, &local);
        }
    }
    return idx;
}

// ===========================================================================
//  iSNDdetunetolinear  0x01143310
// ===========================================================================
// @ 0x01143310
extern "C" int iSNDdetunetolinear(uint32_t param)
{
    int shift = 0x1000;
    if ((int)param > 0x4af) {
        uint32_t q = param / 0x4b0;
        param = param % 0x4b0;
        do {
            shift *= 2;
            q--;
        } while (q != 0);
    }
    if ((int)param < -0x4af) {
        int n = (-(int)param - 0x4b0) / 0x4b0 + 1;
        param = param + n * 0x4b0;
        do {
            shift >>= 1;
            n--;
        } while (n != 0);
    }
    int r = (int)(param * 0x369d) >> 0x10;
    if (r < -0xff)
        r = -0xff;
    if (r >= 0)
        return (int)((uint32_t)(g_15bfee0[r] + 0x100) * (uint32_t)shift) >> 8;
    return (int)((uint32_t)(g_15bffe0[r] + 0x100) * (uint32_t)shift) >> 9;
}

// ===========================================================================
//  FUN_011433b0
// ===========================================================================
// @ 0x011433b0
extern "C" void FUN_011433b0(int index)
{
    char* v = (char*)g_sndvoices + index * 0x84;
    if (*(int16_t*)(v + 0x7e) == 0) {
        int pitch = *(int16_t*)(v + 0x7c);
        int p = *(int*)(v + 0x78);
        if (p != 0) {
            pitch += ((*(int8_t*)(*(uint8_t*)(v + 0x68) + p) - 0x40)
                      * (int)*(int16_t*)(v + 0x26)) >> 6;
        }
        *(int16_t*)(v + 0x7e) = (int16_t)iSNDdetunetolinear((uint32_t)pitch);
    }
    *(int16_t*)(v + 0x82) = (int16_t)(((uint32_t)*(uint16_t*)(v + 0x80)
                                       * (uint32_t)*(uint16_t*)(v + 0x7e)) >> 0xc);
}

// ===========================================================================
//  FUN_01143430
// ===========================================================================
// @ 0x01143430
extern "C" void FUN_01143430(uint8_t a, int b, uint16_t c, int* d, int e, int f)
{
    d[0] = f;
    *(uint16_t*)((char*)d + 0xc) = 0;
    *(uint16_t*)((char*)d + 0xe) = c;
    *((uint8_t*)d + 0x10) = a;
    d[1] = e;
}

// ===========================================================================
//  FUN_01143460   (decode 16 raw bytes -> filter coefficients, SIMD)
// ===========================================================================
// @ 0x01143460
// INCOMPLETE: the MMX second stage (15-iteration nibble matrix decode) is not
// reconstructed here; see partial.txt.
extern "C" void FUN_01143460(int src, void* dstf)
{
    uint8_t* s = (uint8_t*)src;
    float* out = (float*)dstf;
    for (int i = 0; i < 4; i++) {
        uint8_t b0 = s[0];
        uint32_t lo = b0 & 0xf;
        (void)g_tab300[lo * 2 + 1];
        (void)g_tab300[lo * 2];
        uint8_t b2 = s[2];
        (void)g_tab2c4[b2 & 0xf];
        float f1 = (float)(int)((int8_t)s[1] * 0x100 + (b0 & 0xf0)) * 3.0517578e-05f;
        out[0] = f1;
        float f2 = (float)(int)((int8_t)s[3] * 0x100 + (b2 & 0xf0)) * 3.0517578e-05f;
        out[1] = f2;
        s += 4;
        out += 0x80 / 4;
    }
}

// ===========================================================================
//  FUN_01143600
// ===========================================================================
// @ 0x01143600
extern "C" void FUN_01143600(int p, int param2)
{
    int rem = 0;
    int off = 0;
    if (*(int*)(p + 0x38) < 1) {
        char* e = (char*)(*(int*)(p + 0x24) + (uint32_t)*(uint8_t*)(p + 0x30) * 0x14 + p);
        if (*(int*)(e + 0xc) == 0) {
            e = 0;
        } else {
            (*(uint8_t*)(p + 0x30))++;
            if (*(uint8_t*)(p + 0x32) <= *(uint8_t*)(p + 0x30))
                *(uint8_t*)(p + 0x30) = 0;
        }
        if (*(int8_t*)(e + 0x10) == 0) {
            *(int*)(p + 0x38) = 0;
            *(int*)(p + 0x34) = 0;
        }
        int base = *(int*)e;
        *(int*)(p + 0x34) = base;
        int t = (*(int*)(e + 8) + ((*(int*)(e + 8) >> 31) & 0x7f)) >> 7;
        *(int*)(p + 0x34) = *(uint8_t*)(p + 0x2e) * t * 0x4c + base;
        off = *(int*)(e + 8) - t * 0x80;
        *(int*)(p + 0x38) = *(int*)(e + 0xc) - *(int*)(e + 8);
    }
    uint32_t n = *(uint8_t*)(p + 0x2e);
    int src = *(int*)(p + 0x34);
    for (uint32_t i = 0; i < n; i++) {
        int d = *(int*)(param2 + 4) + (uint32_t)*(uint16_t*)(param2 + 0xe) * i * 4;
        FUN_01143460(src, (void*)d);
        *(int*)(p + 0x34) += 0x4c;
        if (off > 0)
            memmove((void*)d, (void*)(d + off * 4), (0x80 - off) * 4);
    }
    int dec = off > 0 ? 0x80 - off : 0x80;
    *(int*)(p + 0x38) -= dec;
}

// ===========================================================================
//  FUN_011436e0
// ===========================================================================
// @ 0x011436e0
extern "C" void FUN_011436e0(int p, int param2, uint32_t count)
{
    if (*(int*)(p + 0x38) < 1) {
        char* e = (char*)(*(int*)(p + 0x24) + (uint32_t)*(uint8_t*)(p + 0x30) * 0x14 + p);
        if (*(int*)(e + 0xc) == 0) {
            e = 0;
        } else {
            (*(uint8_t*)(p + 0x30))++;
            if (*(uint8_t*)(p + 0x32) <= *(uint8_t*)(p + 0x30))
                *(uint8_t*)(p + 0x30) = 0;
        }
        if (*(int8_t*)(e + 0x10) == 0) {
            *(int*)(p + 0x34) = 0;
            *(int*)(p + 0x38) = 0;
        }
        *(int*)(p + 0x34) = *(int*)e;
        *(int*)(p + 0x38) = *(int*)(e + 0xc);
    }
    uint32_t n = *(uint8_t*)(p + 0x2e);
    int src = *(int*)(p + 0x34);
    for (uint32_t c = 0; c < n; c++) {
        int d = *(int*)(param2 + 4) + (uint32_t)*(uint16_t*)(param2 + 0xe) * c * 4;
        uint8_t* pb = (uint8_t*)(src + c);
        uint32_t k = 0;
        if ((int)count > 3) {
            uint32_t n4 = ((count - 4) >> 2) + 1;
            float* pd = (float*)(d + 8);
            k = n4 * 4;
            do {
                pd[-2] = (float)(int)(pb[0] - 0x80) * 0.0078125f;
                pd[-1] = (float)(int)(pb[1] - 0x80) * 0.0078125f;
                pd[0]  = (float)(int)(pb[2] - 0x80) * 0.0078125f;
                pd[1]  = (float)(int)(pb[3] - 0x80) * 0.0078125f;
                pb += 4;
                pd += 4;
                n4--;
            } while (n4 != 0);
        }
        for (; k < count; k++) {
            *(float*)(d + k * 4) = (float)(int)(*pb - 0x80) * 0.0078125f;
            pb++;
        }
    }
    *(int*)(p + 0x34) += n * count;
    *(int*)(p + 0x38) -= count;
}

// ===========================================================================
//  FUN_01143830
// ===========================================================================
// @ 0x01143830
extern "C" void FUN_01143830(int p, int param2, uint32_t count)
{
    if (*(int*)(p + 0x38) < 1) {
        char* e = (char*)(*(int*)(p + 0x24) + (uint32_t)*(uint8_t*)(p + 0x30) * 0x14 + p);
        if (*(int*)(e + 0xc) == 0) {
            e = 0;
        } else {
            (*(uint8_t*)(p + 0x30))++;
            if (*(uint8_t*)(p + 0x32) <= *(uint8_t*)(p + 0x30))
                *(uint8_t*)(p + 0x30) = 0;
        }
        if (*(int8_t*)(e + 0x10) == 0) {
            *(int*)(p + 0x34) = 0;
            *(int*)(p + 0x38) = 0;
        }
        *(int*)(p + 0x34) = *(int*)e;
        *(int*)(p + 0x38) = *(int*)(e + 0xc);
    }
    uint32_t n = *(uint8_t*)(p + 0x2e);
    int src = *(int*)(p + 0x34);
    for (uint32_t c = 0; c < n; c++) {
        int d = *(int*)(param2 + 4) + (uint32_t)*(uint16_t*)(param2 + 0xe) * c * 4;
        char* pb = (char*)(src + c);
        uint32_t k = 0;
        if ((int)count > 3) {
            uint32_t n4 = ((count - 4) >> 2) + 1;
            float* pd = (float*)(d + 8);
            k = n4 * 4;
            do {
                pd[-2] = (float)(int)pb[0] * 0.0078125f;
                pd[-1] = (float)(int)pb[1] * 0.0078125f;
                pd[0]  = (float)(int)pb[2] * 0.0078125f;
                pd[1]  = (float)(int)pb[3] * 0.0078125f;
                pb += 4;
                pd += 4;
                n4--;
            } while (n4 != 0);
        }
        for (; k < count; k++) {
            *(float*)(d + k * 4) = (float)(int)*pb * 0.0078125f;
            pb++;
        }
    }
    *(int*)(p + 0x34) += n * count;
    *(int*)(p + 0x38) -= count;
}
