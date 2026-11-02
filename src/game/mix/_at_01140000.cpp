// src/game/mix/_at_01140000.cpp -- migrated from slice(s) s01141a90 by tools/migrate/rewrite.py
// Object file: mix/_at_01140000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/System.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* g_mixvoices;     // 0x16e8174
extern "C" uint8_t g_numOutputs;  // 0x16e8079
extern "C" uint8_t g_16e807c;     // 0x16e807c
extern "C" void* g_16e8120;       // 0x16e8120
extern "C" void* g_16e8118;       // 0x16e8118
extern "C" void* g_16e8128[];     // 0x16e8128
extern "C" void FUN_01142270(float, float, float*, float*);  // 0x1142270

// ---- items of slice s01141a90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SndFilter;
struct Dec19;
struct System;
extern "C" void* g_mixvoices;     // 0x16e8174
extern "C" uint8_t g_numOutputs;  // 0x16e8079
extern "C" uint8_t g_16e807c;     // 0x16e807c
extern "C" void* g_16e8120;       // 0x16e8120
extern "C" void* g_16e8118;       // 0x16e8118
extern "C" void* g_16e8128[];     // 0x16e8128
extern "C" System* g_system;      // 0x16e61a8
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
void  FUN_01158b10(void*, void*, int, int);        // 0x1158b10
void* FUN_011e0744(void*, const void*, uint32_t);// 0x11e0744  (memcpy thunk)
void  SNDMEMI_alloc(void*, int);                   // 0x113ec90
void  FUN_011741b0(void*);                         // 0x11741b0
void  FUN_01133450(void);                          // 0x1133450
void  FUN_01156780(void);                          // 0x1156780
void  FUN_01133460(void);                          // 0x1133460
extern "C" void FUN_01142270(float, float, float*, float*);  // 0x1142270
// ---- items of slice s01141a90 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" System* g_system;      // 0x16e61a8

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

// @ 0x01141f10
extern "C" int FUN_01141f10(SndFilter* f)
{
    return *(int*)((char*)f->decoder + 0x10);
}

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

// @ 0x01142650
extern "C" void* FUN_01142650(int size)
{
    return g_system->Alloc(size, "New Dummy ID", 0x10, 0);
}

// @ 0x01142670
extern "C" void FUN_01142670(void* p)
{
    g_system->Free(p, 0);
}

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

// @ 0x01142730
extern "C" void FUN_01142730(uint8_t p)
{
    g_16e807c = p;
}
