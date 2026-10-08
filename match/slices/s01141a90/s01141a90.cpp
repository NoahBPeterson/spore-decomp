// Slice s01141a90: RenderWare 4 audio core (rw::audio) - EALayer3 decode filters
// (mono/stereo/looped variants), MIX mixer voice init/stop, and float-mix helpers.
// Built with VC .NET 2003 (cl 13.10) + /GL /LTCG.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------

struct SndFilter;
struct Dec19;
struct System;

// 0x16e8064 : looped mono/stereo decoder node
extern "C" Dec19* g_16e8064;      // 0x16e8064
// 0x16e8068 : mono/stereo decoder node
extern "C" Dec19* g_16e8068;      // 0x16e8068
// 0x16e8174 : mixer voice array (0x5c bytes per voice)
extern "C" void* g_mixvoices;     // 0x16e8174
// 0x15bfe38 : mixer output channel count
extern "C" int g_numChannels;     // 0x15bfe38
// 0x16e8079 : mixer output bus count (byte)
extern "C" uint8_t g_numOutputs;  // 0x16e8079
// 0x16e807c : scratch byte
extern "C" uint8_t g_16e807c;     // 0x16e807c
// 0x16e8124 : per-instance float buffer
extern "C" float* g_16e8124;      // 0x16e8124
// 0x16e8120 : per-instance
extern "C" void* g_16e8120;       // 0x16e8120
// 0x16e8118 : per-instance head (loop 0x16e8118..0x16e8120)
extern "C" void* g_16e8118;       // 0x16e8118
// 0x16e8128 : per-bus instance array
extern "C" void* g_16e8128[];     // 0x16e8128
extern "C" void* g_16e8140[];     // 0x16e8140  mixer output buffers (aligned)
// 0x16e8170 : mix accumulate buffer
extern "C" float* g_16e8170;      // 0x16e8170
// 0x16e8158 : mix accumulate buffer 2
extern "C" float g_16e8158[];     // 0x16e8158
// 0x16e8084 : per-channel enabled flags (pointer to int array)
extern "C" int* g_16e8084;        // 0x16e8084
// 0x16f16fc : per-channel decoder-instance pointers (pointer to pointer array)
extern "C" int* g_16f16fc;        // 0x16f16fc
// 0x16e8178 : time-stretch decode function pointer
extern "C" int g_16e8178;         // 0x16e8178
// 0x16e8088 : decoder factory table
extern "C" int g_16e8088[];       // 0x16e8088
// 0x16e80d0 : decoder factory size table
extern "C" int g_16e80d0[];       // 0x16e80d0
// 0x16e7c23 : per-voice flag byte
extern "C" uint8_t g_16e7c23;     // 0x16e7c23
// 0x16e61a8 : System singleton
extern "C" System* g_system;      // 0x16e61a8

// ---------------------------------------------------------------------------
// Structures
// ---------------------------------------------------------------------------

struct Dec19 {               // EALayer3 decoder node
    void*    codec;          // +0x00
    int      f04;            // +0x04
    int      f08;            // +0x08
    uint16_t w0c;            // +0x0c
    uint16_t w0e;            // +0x0e
    int      f10;            // +0x10
    int      f14;            // +0x14
    uint8_t  b18;            // +0x18
    uint8_t  b19;            // +0x19
};

struct SndFilter {           // decode filter object
    void*    filterfn;       // +0x00
    void*    restorefn;      // +0x04
    uint8_t  pad08[0x12];
    uint8_t  b1a;            // +0x1a
    uint8_t  pad1b;
    Dec19*   decoder;        // +0x1c
    int      f20;            // +0x20
    int      mode;           // +0x24
    int      f28;            // +0x28
    int      f2c;            // +0x2c
    int      f30;            // +0x30
};

struct Patch19 {             // patch/params argument of the init functions
    int      f00;            // +0x00
    int      f04;            // +0x04
    int      mode;           // +0x08
    int      f0c;            // +0x0c
    int      f10;            // +0x10
    int      f14;            // +0x14
    uint8_t  pad18[0xc];
    int      f24;            // +0x24
};

struct Codec {               // decoder instance (this = Dec19::codec)
    int  FUN_01156df0(void** out, int n);          // 0x1156df0
    void FUN_01156dd0();                           // 0x1156dd0
    void FUN_01156d70(void* p, int n, void* q);    // 0x1156d70
    void FUN_01157410();                           // 0x1157410
    void FUN_01157430();                           // 0x1157430
};

class System {
public:
    uint8_t pad00[0x14];
    void* Alloc(int size, const char* name, int align, int flags); // 0x112c820
    void  Free(void* p, int flags);                                // 0x112c850
};

struct MixVoice {            // 0x5c bytes
    uint8_t state;           // +0x00
    uint8_t b01;             // +0x01
    uint8_t pad02[2];
    float   f04[12];         // +0x04
    float*  p34;             // +0x34
    float*  p38;             // +0x38
    float   f3c;             // +0x3c
    void*   p40;             // +0x40
    int     f44;             // +0x44
    void*   p48;             // +0x48
    void*   p4c;             // +0x4c
    int     f50;             // +0x50
    int     f54;             // +0x54
    int     f58;             // +0x58
};

struct MixInstanceInit {     // argument block for a decoder factory
    int p4, p5, p7, p8, p9, p10, voice, flag, p11, out;
};

// ---------------------------------------------------------------------------
// Callees
// ---------------------------------------------------------------------------

void  FUN_01158b10(void*, void*, int, int);        // 0x1158b10
void* FUN_011e0744(void*, const void*, uint32_t);// 0x11e0744  (memcpy thunk)
void  SNDMEMI_alloc(void*, int);                   // 0x113ec90
void* FUN_011402c0(int);                           // 0x11402c0
void  FUN_011741b0(void*);                         // 0x11741b0
void  FUN_01133450(void);                          // 0x1133450
void  FUN_01156780(void);                          // 0x1156780
void  FUN_01133460(void);                          // 0x1133460
void  FUN_011596d0(void*, void*);                  // 0x11596d0
void  FUN_01159630(void*, int, int);               // 0x1159630
void  FUN_0116bda0(void);                          // 0x116bda0
extern "C" void FUN_01142270(float, float, float*, float*);  // 0x1142270

typedef int (__cdecl *MixDecodeFn)(void*, void*);
typedef int (__cdecl *MixCodecFn)(void*, int, void*, void*, int);
typedef int (__cdecl *StretchFn)(int, float, float*, float*);

// ===========================================================================
//  FUN_01141a90  (looped-decode filter pull)
// ===========================================================================
// @ 0x01141a90
extern "C" int FUN_01141a90(SndFilter* f, int n, int unused, void* buf)
{
    int local_c = 0;
    for (;;) {
        if (n < 1)
            return local_c;
        Dec19* d = f->decoder;
        int iVar3, iVar4;
        if (f->b1a == 0) {
            if (f->mode == 2) {
                int need = (uint32_t)d->w0c + n;
                if (d->f08 < need)
                    FUN_01158b10(&d->f04, &d->f08, need, 4);
            }
            void* out[2];
            out[0] = buf;
            out[1] = (f->mode == 2) ? (void*)(d->f04 + (uint32_t)d->w0c * 4) : 0;
            iVar4 = ((Codec*)d->codec)->FUN_01156df0(out, n);
            f->f20 += iVar4;
            local_c += iVar4;
            iVar3 = n;
        } else {
            if (f->mode <= 2) {
                FUN_011e0744(buf, (void*)(d->f04 + (uint32_t)d->w0e * 4), n * 4);
                iVar4 = n;
                iVar3 = 0;
                local_c = n;
            } else {
                void* out[2];
                out[0] = buf;
                out[1] = 0;
                iVar4 = ((Codec*)d->codec)->FUN_01156df0(out, n);
                f->f20 += iVar4;
                local_c += iVar4;
                iVar3 = n;
            }
        }
        buf = (char*)buf + iVar4 * 4;
        if (f->mode < 3) {
            int16_t* p = (int16_t*)((char*)d + 0xc + f->b1a * 2);
            *p = (int16_t)(*p + iVar4);
            if (d->w0c == d->w0e) {
                d->w0c = 0;
                d->w0e = 0;
            }
        }
        if (iVar4 < iVar3) {
            f->f20 = f->f28;
            ((Codec*)d->codec)->FUN_01156dd0();
            ((Codec*)d->codec)->FUN_01156d70((void*)f->f30, 0x7fffffff,
                                             (void*)((f->f2c - f->f28) + 1));
        }
        n = iVar3 - iVar4;
    }
}

// ===========================================================================
//  FUN_01141bc0  (release looped-decode filter)
// ===========================================================================
// @ 0x01141bc0
extern "C" void FUN_01141bc0(SndFilter* f)
{
    if (f->decoder != 0) {
        f->decoder->f10--;
        if (f->decoder->f10 == 0) {
            void* c = f->decoder->codec;
            if (c != 0) {
                ((Codec*)c)->FUN_01157430();
                FUN_011741b0(c);
            }
            void* p = (void*)f->decoder->f04;
            if (p != 0) {
                g_system->Free(p, 0);
                f->decoder->f04 = 0;
            }
            g_system->Free(f->decoder, 0);
            f->decoder = 0;
        }
    }
}

// ===========================================================================
//  SFILTER_unpackealayer3linit  0x01141c30
// ===========================================================================
// @ 0x01141c30
extern "C" void SFILTER_unpackealayer3linit(SndFilter* f, Patch19* patch)
{
    Dec19* saved = g_16e8064;
    (void)saved;
    if (patch->mode == 2) {
        if (f->b1a == 0) {
            g_16e8064 = (Dec19*)g_system->Alloc(0x14, "StereoLoopedEALayer3Decode", 0x10, 0);
            f->decoder = g_16e8064;
            void* d = FUN_011402c0(0x1d8);
            if (d != 0) {
                ((Codec*)d)->FUN_01157410();
                ((Codec*)d)->FUN_01156dd0();
            } else {
                d = 0;
            }
            g_16e8064->codec = d;
            ((Codec*)g_16e8064->codec)->FUN_01156dd0();
            f->f30 = patch->f04;
            f->f28 = patch->f10;
            f->f2c = patch->f14;
            ((Codec*)g_16e8064->codec)->FUN_01156d70((void*)patch->f00, 0x7fffffff,
                                                     (void*)patch->f10);
            g_16e8064->w0c = 0;
            g_16e8064->w0e = 0;
            g_16e8064->f10 = 1;
            g_16e8064->f04 = 0;
            g_16e8064->f08 = 0;
        } else {
            f->decoder = g_16e8064;
            g_16e8064->f10 = 2;
        }
    } else {
        g_16e8064 = (Dec19*)g_system->Alloc(0x14, "LoopEALayer3Decode", 0x10, 0);
        f->decoder = g_16e8064;
        void* d = FUN_011402c0(0x1d8);
        if (d != 0) {
            ((Codec*)d)->FUN_01157410();
            ((Codec*)d)->FUN_01156dd0();
        } else {
            d = 0;
        }
        g_16e8064->codec = d;
        ((Codec*)g_16e8064->codec)->FUN_01156dd0();
        f->f30 = patch->f04;
        f->f28 = patch->f10;
        f->f2c = patch->f14;
        ((Codec*)g_16e8064->codec)->FUN_01156d70((void*)patch->f00, 0x7fffffff,
                                                 (void*)patch->f10);
        g_16e8064->w0c = 0;
        f->decoder->f10 = 1;
        f->decoder->f04 = 0;
        f->decoder->f08 = 0;
    }
    f->filterfn = (void*)&FUN_01141a90;
    f->restorefn = (void*)&FUN_01141bc0;
    patch->f24 = (int)&FUN_0116bda0;
    f->f20 = 0;
    f->mode = patch->mode;
}

// ===========================================================================
//  FUN_01141dd0  (mono/stereo-decode filter pull)
// ===========================================================================
// @ 0x01141dd0
extern "C" int FUN_01141dd0(SndFilter* f, int n, int unused, void* buf)
{
    Dec19* d = f->decoder;
    if (d->f14 <= d->f10)
        return -1;
    int extra;
    if (d->f14 - d->f10 < n) {
        extra = (d->f10 - d->f14) + n;
        n = d->f14 - d->f10;
    } else {
        extra = 0;
    }
    d = f->decoder;
    if (d->b18 == 2) {
        if (f->b1a == 0) {
            int need = (uint32_t)d->w0c + n;
            if (d->f08 < need)
                FUN_01158b10(&d->f04, &d->f08, need, 4);
            void* out[2];
            out[0] = buf;
            out[1] = (void*)(d->f04 + (uint32_t)d->w0c * 4);
            ((Codec*)d->codec)->FUN_01156df0(out, n);
            goto label;
        }
        FUN_011e0744(buf, (void*)(d->f04 + (uint32_t)d->w0e * 4), n * 4);
    } else {
        void* out[2];
        out[0] = buf;
        out[1] = 0;
        ((Codec*)d->codec)->FUN_01156df0(out, n);
    }
    d->f10 += n;
label:
    if (extra != 0)
        SNDMEMI_alloc((char*)buf + n * 4, extra * 4);
    if (f->decoder->b18 < 3) {
        int16_t* p = (int16_t*)((char*)f->decoder + 0xc + f->b1a * 2);
        *p = (int16_t)(*p + n);
        if (f->decoder->w0c == f->decoder->w0e) {
            f->decoder->w0c = 0;
            f->decoder->w0e = 0;
        }
    }
    return 1;
}

// ===========================================================================
//  FUN_01141f10   (get consumed count)
// ===========================================================================
// @ 0x01141f10
extern "C" int FUN_01141f10(SndFilter* f)
{
    return *(int*)((char*)f->decoder + 0x10);
}

// ===========================================================================
//  FUN_01141f20   (release mono/stereo-decode filter)
// ===========================================================================
// @ 0x01141f20
extern "C" void FUN_01141f20(SndFilter* f)
{
    if (f->decoder != 0) {
        f->decoder->b19--;
        if (f->decoder->b19 == 0) {
            void* c = f->decoder->codec;
            if (c != 0) {
                ((Codec*)c)->FUN_01157430();
                FUN_011741b0(c);
            }
            void* p = (void*)f->decoder->f04;
            if (p != 0) {
                g_system->Free(p, 0);
                f->decoder->f04 = 0;
            }
            g_system->Free(f->decoder, 0);
            f->decoder = 0;
        }
    }
}

// ===========================================================================
//  SFILTER_unpackealayer3init  0x01141f90
// ===========================================================================
// @ 0x01141f90
extern "C" void SFILTER_unpackealayer3init(SndFilter* f, Patch19* patch)
{
    if (patch->mode == 2) {
        if (f->b1a != 0) {
            f->decoder = g_16e8068;
            f->decoder->b19 = 2;
            goto label;
        }
        g_16e8068 = (Dec19*)g_system->Alloc(0x1c, "StereoEaLayer3Decode", 0x10, 0);
        f->decoder = g_16e8068;
        void* d = FUN_011402c0(0x1d8);
        if (d != 0) {
            ((Codec*)d)->FUN_01157410();
            ((Codec*)d)->FUN_01156dd0();
        } else {
            d = 0;
        }
        g_16e8068->codec = d;
        ((Codec*)g_16e8068->codec)->FUN_01156dd0();
        ((Codec*)g_16e8068->codec)->FUN_01156d70((void*)patch->f00, 0x7fffffff,
                                                 (void*)patch->f0c);
        g_16e8068->w0c = 0;
        g_16e8068->w0e = 0;
    } else {
        g_16e8068 = (Dec19*)g_system->Alloc(0x1c, "MonoEaLayer3Decode", 0x10, 0);
        f->decoder = g_16e8068;
        void* d = FUN_011402c0(0x1d8);
        if (d != 0) {
            ((Codec*)d)->FUN_01157410();
            ((Codec*)d)->FUN_01156dd0();
        } else {
            d = 0;
        }
        g_16e8068->codec = d;
        ((Codec*)g_16e8068->codec)->FUN_01156dd0();
        ((Codec*)g_16e8068->codec)->FUN_01156d70((void*)patch->f00, 0x7fffffff,
                                                 (void*)patch->f0c);
        g_16e8068->w0c = 0;
    }
    f->decoder->b19 = 1;
    f->decoder->f04 = 0;
    f->decoder->f08 = 0;
label:
    f->filterfn = (void*)&FUN_01141dd0;
    f->restorefn = (void*)&FUN_01141f20;
    patch->f24 = (int)&FUN_01141f10;
    f->decoder->f14 = patch->f0c;
    f->decoder->f10 = 0;
    f->decoder->b18 = (uint8_t)patch->mode;
}

// ===========================================================================
//  FUN_01142100   (crossfade accumulate, 16 coefficients)
// ===========================================================================
// @ 0x01142100
extern "C" void FUN_01142100(float* src, float* dst)
{
    dst[0]  = *src * 0.94117647f + dst[0];
    dst[1]  = *src * 0.88235294f + dst[1];
    dst[2]  = *src * 0.82352942f + dst[2];
    dst[3]  = *src * 0.76470590f + dst[3];
    dst[4]  = *src * 0.70588237f + dst[4];
    dst[5]  = *src * 0.64705884f + dst[5];
    dst[6]  = *src * 0.58823532f + dst[6];
    dst[7]  = *src * 0.52941179f + dst[7];
    dst[8]  = *src * 0.47058824f + dst[8];
    dst[9]  = *src * 0.41176471f + dst[9];
    dst[10] = *src * 0.35294119f + dst[10];
    dst[11] = *src * 0.29411766f + dst[11];
    dst[12] = *src * 0.23529412f + dst[12];
    dst[13] = *src * 0.17647059f + dst[13];
    dst[14] = *src * 0.11764706f + dst[14];
    dst[15] = *src * 0.05882353f + dst[15];
    *src = 0.0f;
}

// ===========================================================================
//  FUN_01142270   (ramp accumulate over 16 coefficients)
// ===========================================================================
// @ 0x01142270
extern "C" void FUN_01142270(float a, float b, float* c, float* d)
{
    float f = (b - a) * 0.05882353f;
    d[0]  = (f + a) * c[0] + d[0];
    d[1]  = (f * 2.0f + a) * c[1] + d[1];
    d[2]  = (f * 3.0f + a) * c[2] + d[2];
    d[3]  = (f * 4.0f + a) * c[3] + d[3];
    d[4]  = (f * 5.0f + a) * c[4] + d[4];
    d[5]  = (f * 6.0f + a) * c[5] + d[5];
    d[6]  = (f * 7.0f + a) * c[6] + d[6];
    d[7]  = (f * 8.0f + a) * c[7] + d[7];
    d[8]  = (f * 9.0f + a) * c[8] + d[8];
    d[9]  = (f * 10.0f + a) * c[9] + d[9];
    d[10] = (f * 11.0f + a) * c[10] + d[10];
    d[11] = (f * 12.0f + a) * c[11] + d[11];
    d[12] = (f * 13.0f + a) * c[12] + d[12];
    d[13] = (f * 14.0f + a) * c[13] + d[13];
    d[14] = (f * 15.0f + a) * c[14] + d[14];
    d[15] = (f * 16.0f + a) * c[15] + d[15];
}

// ===========================================================================
//  FUN_01142470   (mixer instance tick)
// ===========================================================================
// @ 0x01142470
extern "C" int FUN_01142470(MixVoice* v)
{
    int r = (*(MixCodecFn*)v->p40)(v->p40, 0x10, g_16e8120, g_16e8124, 0);
    if (r > 0) {
        v->f3c = g_16e8124[15];
        for (int i = 0; i < g_numChannels; i++) {
            if (g_16e8084[i] != 0) {
                float f1 = v->p38[i];
                float f2 = v->p34[i];
                if (f2 == f1) {
                    if (f1 != 0.0f)
                        ((StretchFn)g_16e8178)(0x10, f1, g_16e8124,
                                               (float*)(size_t)g_16f16fc[i]);
                } else {
                    FUN_01142270(f2, f1, g_16e8124, (float*)(size_t)g_16f16fc[i]);
                    v->p34[i] = v->p38[i];
                }
            }
        }
        for (int i = 0; i < (int)g_numOutputs; i++) {
            float f1 = *(float*)((char*)v + 0x1c + i * 4);
            float lo = *(float*)((char*)v + 0x04 + i * 4);
            if (lo == f1) {
                if (f1 != 0.0f)
                    ((StretchFn)g_16e8178)(0x10, f1, g_16e8124,
                                           (float*)(size_t)g_16e8140[i]);
            } else {
                FUN_01142270(lo, f1, g_16e8124,
                             (float*)(size_t)g_16e8140[i]);
                *(float*)((char*)v + 0x04 + i * 4) = *(float*)((char*)v + 0x1c + i * 4);
            }
        }
        return 0x10;
    }
    for (int i = 0; i < g_numChannels; i++)
        v->p34[i] = v->p38[i];
    for (int i = 0; i < (int)g_numOutputs; i++)
        v->f04[i] = v->f04[6 + i];
    return 0;
}

// ===========================================================================
//  FUN_01142650  (dummy-id alloc)
// ===========================================================================
// @ 0x01142650
extern "C" void* FUN_01142650(int size)
{
    return g_system->Alloc(size, "New Dummy ID", 0x10, 0);
}

// ===========================================================================
//  FUN_01142670
// ===========================================================================
// @ 0x01142670
extern "C" void FUN_01142670(void* p)
{
    g_system->Free(p, 0);
}

// ===========================================================================
//  FUN_01142690   (shutdown mixer subsystem)
// ===========================================================================
// @ 0x01142690
extern "C" void FUN_01142690(void)
{
    FUN_01133450();
    FUN_01156780();
    if (g_mixvoices != 0) {
        g_system->Free(g_mixvoices, 0);
        g_mixvoices = 0;
    }
    void** p = &g_16e8118;
    do {
        if (*p != 0) {
            g_system->Free(*p, 0);
            *p = 0;
        }
        p++;
    } while ((int)p < (int)&g_16e8120);
    for (int i = 0; i < (int)g_numOutputs; i++) {
        if (g_16e8128[i] != 0) {
            g_system->Free(g_16e8128[i], 0);
            g_16e8128[i] = 0;
        }
    }
    FUN_01133460();
}

// ===========================================================================
//  FUN_01142730
// ===========================================================================
// @ 0x01142730
extern "C" void FUN_01142730(uint8_t p)
{
    g_16e807c = p;
}

// ===========================================================================
//  MIX_playinit  0x01142740
// ===========================================================================
// @ 0x01142740
extern "C" void MIX_playinit(int voice, int fmt, int a3, int a4, int a5, int a6,
                             int a7, int a8, int a9, int a10, int a11, uint8_t a12)
{
    MixVoice* v = (MixVoice*)((char*)g_mixvoices + voice * 0x5c);
    v->p40 = 0;
    v->p48 = 0;
    v->f50 = 0;
    v->f54 = 0;
    v->f58 = 0;
    v->p4c = 0;

    int idx = -1;
    if (fmt == 8) idx = 0;
    else if (fmt == 10) idx = 1;
    else if (fmt == 4) idx = 2;
    else if (fmt == 0x16) idx = 3;
    else if (fmt == 0x10) idx = 4;
    else if (fmt == 0x17) idx = 5;

    int sel = 0;
    if (a3 == 1) {
        if (a10 > 0)
            sel = 1;
    } else if (a3 == 0) {
        sel = 2;
    }
    sel = sel + idx * 3;

    if (g_16e8088[sel] != 0) {
        void* inst = g_system->Alloc(g_16e80d0[sel], "Mixer Decoder Instance Data", 0x10, 0);
        v->p48 = inst;
        MixInstanceInit init;
        init.p4 = a4;
        init.p5 = a5;
        init.p7 = a7;
        init.p8 = a8;
        init.p9 = a9;
        init.p10 = a10;
        init.voice = voice;
        init.flag = g_16e7c23;
        init.p11 = a11;
        init.out = 0;
        *(int*)((char*)v->p48 + 4) = 0;
        *(uint16_t*)((char*)v->p48 + 0x18) = 0xf0;
        *(uint8_t*)((char*)v->p48 + 0x1a) = a12;
        ((MixDecodeFn)g_16e8088[sel])(v->p48, &init);
        v->f44 = init.out;
        FUN_011596d0(&v->p40, v->p48);
    }

    if (a6 != 0) {
        if (a3 != 0)
            voice = -1;
        void* ts = g_system->Alloc(0x1834, "Mixer Time Stretch Instance Data", 0x10, 0);
        v->p4c = ts;
        *(int*)((char*)ts + 4) = 0;
        *(uint16_t*)((char*)v->p4c + 0x18) = 200;
        *(uint8_t*)((char*)v->p4c + 0x1a) = a12;
        FUN_01159630(v->p4c, a6, voice);
        FUN_011596d0(&v->p40, v->p4c);
    }
    v->state = 1;
}

// ===========================================================================
//  FUN_01142900
// ===========================================================================
// @ 0x01142900
extern "C" void FUN_01142900(int voice)
{
    MixVoice* v = (MixVoice*)((char*)g_mixvoices + voice * 0x5c);
    v->f3c = 0.0f;
    v->b01 = 0;
    for (int i = 0; i < g_numChannels; i++)
        v->p34[i] = v->p38[i];
    int i = 0;
    if (g_numOutputs != 0) {
        do {
            v->f04[i] = v->f04[6 + i];
            i++;
        } while (i < g_numOutputs);
    }
    v->state = 2;
}

// ===========================================================================
//  MIX_stop  0x01142960
// ===========================================================================
// @ 0x01142960
extern "C" void MIX_stop(int voice)
{
    MixVoice* v = (MixVoice*)((char*)g_mixvoices + voice * 0x5c);
    for (int i = 0; i < g_numChannels; i++) {
        g_16e8170[i] = v->p34[i] * v->f3c + g_16e8170[i];
    }
    int i = 0;
    if (g_numOutputs != 0) {
        do {
            g_16e8158[i] = v->f04[i] * v->f3c + g_16e8158[i];
            i++;
        } while (i < g_numOutputs);
    }
    for (;;) {
        int fn = *(int*)((char*)v->p40 + 4);
        if (fn != 0)
            ((void (*)(void*))fn)(v->p40);
        void* next = *(void**)((char*)v->p40 + 8);
        g_system->Free(v->p40, 0);
        v->p40 = next;
        if (next == 0)
            break;
    }
    v->state = 0;
}
