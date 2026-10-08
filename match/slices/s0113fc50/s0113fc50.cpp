// Slice s0113fc50 -- SND audio library: sample-format decoders, per-play control wrappers and
// the platform voice layer.  Original used VC .NET 2003 (/vc71) + /GL + /LTCG.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "../../include/types.h"

#define A8(a)  (*(unsigned char*)(a))
#define A16(a) (*(unsigned short*)(a))
#define A32(a) (*(unsigned int*)(a))
#define Af(a)  (*(float*)(a))
#define Ad(a)  (*(double*)(a))
#define Ap(a)  (*(void**)(a))

extern unsigned char g_16e7c1c;   // 0x16e7c1c

extern "C" {
    __declspec(dllimport) double __cdecl ldexp(double, int);   // msvcr90
    __declspec(dllimport) void   __cdecl free(void*);          // 0x16f16f4
}

// ---- callees ---------------------------------------------------------------
void  __cdecl F_0113fec0(int);                          // 0x113fec0 (slice 16)
void  __cdecl Sub_11406d0(int);                         // 0x11406d0
void  __cdecl Sub_1140650(int);                         // 0x1140650
void  __cdecl Sub_1143210(int);                         // 0x1143210
void  __cdecl Sub_11432a0(int);                         // 0x11432a0
int   __cdecl Sub_1141150(int);                         // 0x1141150
int   __cdecl Sub_1156660(int, int*);                   // 0x1156660
void  __cdecl Sub_11442a20(int, int, float);            // thunk placeholder (see Sub_1142a20)
void  __cdecl Sub_1142a20(int, int, float);             // 0x1142a20
void  __cdecl Sub_1142a50(int, int, float);             // 0x1142a50
void  __cdecl Sub_1142960(int);                         // 0x1142960
void  __cdecl Sub_1156310(int, int);                    // 0x1156310
void  __cdecl Sub_11568a0(int, int);                    // 0x11568a0 (MIX_setpitch)
void  __cdecl Sub_1156960(int, float);                  // 0x1156960 (MIX_setlowpass)
void  __cdecl Sub_1156a60(int, int);                    // 0x1156a60 (MIX_sethighpass)
void  __cdecl Sub_1156b40(int, int, int);               // 0x1156b40 (MIX_filteradd)
void  __cdecl Sub_1142730(int);                         // 0x1142730
int   __cdecl Sub_1156800(void);                        // 0x1156800
void  __cdecl Sub_1133450(void);                        // 0x1133450
void  __cdecl Sub_1133460(void);                        // 0x1133460
void  __cdecl SNDMEMI_alloc16(void* p, int size);       // 0x113ec90 (slice 16)
void  __cdecl SNDVOICEI_free(int);                      // 0x1141020 (slice 16)
void* __fastcall Sys17_Alloc(void* self, int pad, unsigned size, const char* name,
                             unsigned align, unsigned zero);   // 0x112c820
void  __fastcall Sys17_Free(void* self, int pad, void* p, int z); // 0x112c850

#define D  (A32(0x16e7c78))
#define NCH (A32(0x15bfe38))
#define SYSPTR (Ap(0x16e61a8))

// forward declarations of functions defined later in this file
void FUN_01140930(int a, int val);
void SNDPLATFORM_highpass(int a, int val);
int  F_01140b20(int a, int val);
int  F_01140a70(int a, int ch);
float F_01140190(unsigned char* p);

// ---------------------------------------------------------------------------
// sample-format decoder objects
// ---------------------------------------------------------------------------
struct SndDecoder {
    char         pad0[0x04];
    unsigned char* src;    // +0x04
    short*       dst;      // +0x08
    int          count;    // +0x0c
    int          field10;  // +0x10
    short        chans;    // +0x14

    void SetState(short* p);            // 0x1140380
    void DecodeS16(int srcs, int n);    // 0x11402f0
    void DecodeRaw(int srcs, int n);    // 0x11403b0
    void DecodeSwap(int srcs, int n);   // 0x1140460
    void DecodeMul(int srcs, int n);    // 0x1140560
    int  Setup(void* buf, int a, int n);// 0x1140530
    void* Dtor(unsigned char flags);    // 0x11404f0
};

// @ 0x01140380
void SndDecoder::SetState(short* p)
{
    *(short*)((char*)this + 0x14) = *p;
}

// @ 0x011402f0
void SndDecoder::DecodeS16(int srcs, int n)
{
    int c = count;
    if (c == 0) return;
    if (n < c) c = n;
    int i = 0;
    if (c > 0) {
        do {
            short s = 0;
            if (chans > 0) {
                do {
                    short* d = (short*)(*(int*)(srcs + s * 4) + i * 2);
                    dst = d;
                    *d = (short)((*src - 0x80) * 0x100);
                    src = src + 1;
                    s++;
                } while (s < chans);
            }
            i++;
        } while (i < c);
    }
    count = count - c;
}

// @ 0x011403b0
void SndDecoder::DecodeRaw(int srcs, int n)
{
    int c = count;
    if (c == 0) return;
    if (n < c) c = n;
    int i = 0;
    if (c > 0) {
        do {
            short s = 0;
            if (chans > 0) {
                do {
                    unsigned short* d = (unsigned short*)(*(int*)(srcs + s * 4) + i * 2);
                    dst = (short*)d;
                    *d = (unsigned short)((src[0] << 8) | src[1]);
                    src = src + 3;
                    s++;
                } while (s < chans);
            }
            i++;
        } while (i < c);
    }
    count = count - c;
}

// @ 0x01140460
void SndDecoder::DecodeSwap(int srcs, int n)
{
    int c = count;
    if (c == 0) return;
    if (n < c) c = n;
    int i = 0;
    if (c > 0) {
        do {
            short s = 0;
            if (chans > 0) {
                do {
                    unsigned short* d = (unsigned short*)(*(int*)(srcs + s * 4) + i * 2);
                    dst = (short*)d;
                    unsigned short v = *(unsigned short*)src;
                    *d = (unsigned short)((v >> 8) | (v << 8));
                    src = src + 2;
                    s++;
                } while (s < chans);
            }
            i++;
        } while (i < c);
    }
    count = count - c;
}

// @ 0x01140560
void SndDecoder::DecodeMul(int srcs, int n)
{
    int c = count;
    if (c == 0) return;
    if (n < c) c = n;
    int i = 0;
    if (c > 0) {
        do {
            short s = 0;
            if (chans > 0) {
                do {
                    short* d = (short*)(*(int*)(srcs + s * 4) + i * 2);
                    dst = d;
                    *d = (short)((unsigned short)*src * 0x100);
                    src = src + 1;
                    s++;
                } while (s < chans);
            }
            i++;
        } while (i < c);
    }
    count = count - c;
}

// @ 0x01140530
int SndDecoder::Setup(void* buf, int a, int n)
{
    if (buf != 0 && count == 0) {
        count = n;
        src = (unsigned char*)buf;
        field10 = a;
        return 0;
    }
    return -1;
}

// @ 0x011404f0
void* SndDecoder::Dtor(unsigned char flags)
{
    *(void**)this = (void*)0x14cafa0;
    if ((flags & 1) != 0) {
        (*(void(__cdecl**)(void*))0x16f16f4)(this);
    }
    return this;
}

// ---------------------------------------------------------------------------
// helpers
// ---------------------------------------------------------------------------

// @ 0x0113fc50
void F_0113fc50(void* o)
{
    unsigned char* p = (unsigned char*)o;
    unsigned char chans = p[0x23];
    int i = 0;
    if (chans != 0) {
        short* ps = (short*)(p + 4);
        do {
            short slot = *ps;
            unsigned short v = (unsigned short)(A8(0x14cafd2 + (unsigned)chans * 6 + i) << 8);
            *(unsigned short*)(slot * 0x84 + 0x1c + D) = v;
            i++;
            ps++;
        } while (i < (int)chans);
    }
}

// @ 0x0113fca0
int F_0113fca0(void* o)
{
    unsigned char* b = (unsigned char*)o;
    b[2] = 0;
    b[3] = 0x7f;
    b[4] = 0x40;
    b[5] = 0;
    b[6] = 0;
    *(unsigned short*)o = 0;
    *(unsigned*)(b + 0x44) = 0;
    *(unsigned*)(b + 0x54) = 0;
    *(unsigned*)(b + 0x48) = 0;
    *(unsigned*)(b + 0x58) = 0;
    *(unsigned*)(b + 0x4c) = 0;
    *(unsigned*)(b + 0x5c) = 0;
    *(unsigned*)(b + 0x50) = 0;
    *(unsigned*)(b + 0x60) = 0;
    short* pw = (short*)(b + 8);
    unsigned* pd = (unsigned*)(b + 0x14);
    for (int i = 0; i < 6; i++) {
        *pw = 0;
        *pd = 0;
        pw++;
        pd++;
    }
    return 0;
}

// @ 0x0113fd00
int F_0113fd00(int a, unsigned char b)
{
    if (g_16e7c1c == 0) return -10;
    int handle = Sub_1141150(a);
    if (handle >= 0) {
        int local = -1;
        int r = Sub_1156660(handle, &local);
        while (r != 0) {
            int o = local * 0x84 + D;
            int i = 0;
            if (*(char*)(o + 0x23) != 0) {
                short* ps = (short*)(o + 4);
                do {
                    short v = *ps;
                    *(unsigned char*)(v * 0x84 + D + 0x63) = b;
                    Sub_11406d0(v);
                    i++;
                    ps++;
                } while (i < (int)*(unsigned char*)(o + 0x23));
            }
            r = Sub_1156660(handle, &local);
        }
    }
    return handle;
}

// @ 0x0113fdd0
int F_0113fdd0(int a, int ch, int val)
{
    if (g_16e7c1c == 0) return -10;
    int handle = Sub_1141150(a);
    if (handle >= 0) {
        int local = -1;
        int r = Sub_1156660(handle, &local);
        while (r != 0) {
            int o = local * 0x84 + D;
            int i = 0;
            if (*(char*)(o + 0x23) != 0) {
                float f = (float)val * 0.007874016f;
                short* ps = (short*)(o + 4);
                do {
                    short v = *ps;
                    *(float*)(*(int*)(v * 0x84 + 100 + D) + ch * 4) = f;
                    F_01140a70(v, ch);
                    i++;
                    ps++;
                } while (i < (int)*(unsigned char*)(o + 0x23));
            }
            r = Sub_1156660(handle, &local);
        }
    }
    return handle;
}

// @ 0x0113fec0
void F_0113fec0(int a)
{
    Sub_1140650(a);
    int i = 0;
    if ((int)NCH > 0) {
        do {
            F_01140a70(a, i);
            i++;
        } while (i < (int)NCH);
    }
}

// @ 0x0113ff00
int F_0113ff00(int a, int val)
{
    if (g_16e7c1c == 0) return -10;
    int handle = Sub_1141150(a);
    if (handle >= 0) {
        float f = (float)val * 0.007874016f;
        int local = -1;
        int r = Sub_1156660(handle, &local);
        while (r != 0) {
            int o = local * 0x84 + D;
            int i = 0;
            if (*(char*)(o + 0x23) != 0) {
                short* ps = (short*)(o + 4);
                do {
                    short v = *ps;
                    int vo = v * 0x84 + D;
                    *(unsigned*)(vo + 0x30) = 0;
                    if (*(float*)(vo + 0x38) != f) {
                        *(float*)(vo + 0x38) = f;
                        Sub_1143210(v);
                        Sub_1140650(v);
                        int k = 0;
                        if ((int)NCH > 0) {
                            do {
                                F_01140a70(v, k);
                                k++;
                            } while (k < (int)NCH);
                        }
                    }
                    i++;
                    ps++;
                } while (i < (int)*(unsigned char*)(o + 0x23));
            }
            r = Sub_1156660(handle, &local);
        }
    }
    return handle;
}

// @ 0x01140030
int F_01140030(int a, int val)
{
    if (g_16e7c1c == 0) return -10;
    int handle = Sub_1141150(a);
    if (handle >= 0) {
        int local = -1;
        int r = Sub_1156660(handle, &local);
        while (r != 0) {
            FUN_01140930(local, val);
            r = Sub_1156660(handle, &local);
        }
    }
    return handle;
}

// @ 0x011400a0
int F_011400a0(int a, int val)
{
    if (g_16e7c1c == 0) return -10;
    int handle = Sub_1141150(a);
    if (handle >= 0) {
        int local = -1;
        int r = Sub_1156660(handle, &local);
        while (r != 0) {
            SNDPLATFORM_highpass(local, val);
            r = Sub_1156660(handle, &local);
        }
    }
    return handle;
}

// @ 0x011405e0
int F_011405e0(int a, int val)
{
    if (g_16e7c1c == 0) return -10;
    int handle = Sub_1141150(a);
    if (handle >= 0) {
        int local = -1;
        int r = Sub_1156660(handle, &local);
        while (r != 0) {
            F_01140b20(local, val);
            r = Sub_1156660(handle, &local);
        }
    }
    return handle;
}

// @ 0x01140110
char* F_01140110(char* p, unsigned tag, int n)
{
    char c2 = (char)(tag >> 16);
    char c3 = (char)(tag >> 8);
    for (;;) {
        if (n < 1) return 0;
        char c1 = (char)(tag >> 24);
        if (p[0] == c1 && p[1] == c2 && p[2] == c3 && p[3] == (char)tag) {
            if (!(c1 == 'd' && c2 == 'a' && c3 == 't' && (char)tag == 'a')) return p;
            if (*(unsigned*)(p + 4) != 0) return p;
        }
        n--;
        p++;
    }
}

// @ 0x01140190
float F_01140190(unsigned char* p)
{
    unsigned int hi = (((unsigned)(signed char)p[0] & 0x7f) << 8) | p[1];
    int mid = (int)(((unsigned)p[2] << 24) | ((unsigned)p[3] << 16) | ((unsigned)p[4] << 8) | p[5]);
    int lo  = (int)(((unsigned)p[6] << 24) | ((unsigned)p[7] << 16) | ((unsigned)p[8] << 8) | p[9]);
    double res;
    if (hi == 0) {
        if (mid == 0 && lo == 0) {
            res = 0.0;
            goto sign;
        }
    } else if (hi == 0x7fff) {
        res = Ad(0x15bfe78);
        goto sign;
    }
    {
        double a = ldexp((double)(mid - 0x80000000) + 2147483648.0, (int)hi - 0x401e);
        double b = ldexp((double)(lo - 0x80000000) + 2147483648.0, (int)hi - 0x403e);
        res = a + b;
    }
sign:
    if (p[0] & 0x80) res = -res;
    return (float)res;
}

// @ 0x01140290
float F_01140290(void* p)
{
    unsigned char buf[12];
    *(unsigned*)&buf[0] = *(unsigned*)p;
    *(unsigned*)&buf[4] = *(unsigned*)((char*)p + 4);
    *(unsigned short*)&buf[8] = *(unsigned short*)((char*)p + 8);
    return F_01140190(buf);
}

// @ 0x01140650
void FUN_01140650(int a)
{
    int o = a * 0x84 + D;
    int tbl = A32(0x16e804c) + a * 0x18;
    char c = *(char*)(o + 99);
    float f = *(float*)(o + 0x48);
    int i = 0;
    if (A8(0x16e7be4) != 0) {
        do {
            Sub_1142a20(a, i, *(float*)(tbl + i * 4) * (((float)(int)c * f) * 0.007874016f));
            i++;
        } while (i < (int)A8(0x16e7be4));
    }
}

// @ 0x011406e0
void FUN_011406e0(int a)
{
    int o = a * 0x84 + D;
    int v = A32(0x16e804c) + a * 0x18;
    if (*(char*)(o + 0x1f) == 0) {
        Sub_1156310(*(unsigned short*)(o + 0x1c), v);
        F_0113fec0(a);
        return;
    }
    int i = 0;
    if (A8(0x16e7be4) != 0) {
        do {
            *(unsigned*)(v + i * 4) = 0;
            i++;
        } while (i < (int)A8(0x16e7be4));
    }
    *(unsigned*)(v + 0x14) = 0x3f800000;
    F_0113fec0(a);
}

// @ 0x01140760
int F_01140760(void)
{
    A8(0x16e7bfc) = 1;
    A8(0x16e7c23) = (unsigned char)Sub_1156800();
    return 0;
}

// @ 0x01140780
int F_01140780(void)
{
    Sub_1142730(A8(0x16e7bfd));
    if (g_16e7c1c != 0) {
        A32(0x16e7bf4) = A32(0x16e7c0c);
        A32(0x16e7bf8) = A32(0x16e7c10);
        A8(0x16e7bfd) = A8(0x16e7bfd);
        A32(0x16e7bfc) = A32(0x16e7c14);
        A32(0x16e7c00) = A32(0x16e7c18);
        return 0;
    }
    if (A8(0x16e7bfc) != 0) {
        if ((Sub_1156800() & 2) != 0) {
            A8(0x16e7c23) |= 2;
            return 0;
        }
    }
    A8(0x16e7c23) &= 0xfd;
    A8(0x16e7bfc) = 0;
    return 0;
}

// @ 0x01140810
int SNDPLATFORM_init(void)
{
    Sub_1133450();
    int n = (int)(short)A16(0x16e7c20) * 0x18;
    void* p = Sys17_Alloc(SYSPTR, 0, (unsigned)n, "Platform voices", 0x10, 0);
    A32(0x16e804c) = (unsigned)p;
    SNDMEMI_alloc16(p, n);
    Sub_1133460();
    return 0;
}

// @ 0x01140870
int SNDPLATFORM_restore(void)
{
    Sub_1133450();
    Sys17_Free(SYSPTR, 0, (void*)A32(0x16e804c), 0);
    Sub_1133460();
    return 0;
}

// @ 0x01140890
int F_01140890(int a)
{
    float sr = Af((char*)SYSPTR + 0xc0);
    int o = a * 0x84 + D;
    unsigned short u2 = *(unsigned short*)(o + 0x20);
    int denom = (int)sr;
    unsigned q = ((unsigned)u2 << 16) / (unsigned)denom;
    unsigned short u3 = *(unsigned short*)(o + 0x82);
    int pitch = (int)((unsigned)(q * u3) >> 12);
    int i = 0;
    if (*(char*)(o + 0x23) != 0) {
        short* ps = (short*)(o + 4);
        do {
            Sub_11568a0(*ps, pitch);
            i++;
            ps++;
        } while (i < (int)*(unsigned char*)(o + 0x23));
    }
    return 0;
}

// @ 0x01140930
void FUN_01140930(int a, int val)
{
    float sr = Af((char*)SYSPTR + 0xc0);
    int o = a * 0x84 + D;
    int i = 0;
    if (*(char*)(o + 0x23) != 0) {
        short* ps = (short*)(o + 4);
        do {
            Sub_1156960(*ps, (1.0f / (sr * 0.5f)) * (float)val);
            i++;
            ps++;
        } while (i < (int)*(unsigned char*)(o + 0x23));
    }
}

// @ 0x011409b0
void SNDPLATFORM_highpass(int a, int val)
{
    int o = a * 0x84 + D;
    int i = 0;
    if (*(char*)(o + 0x23) != 0) {
        short* ps = (short*)(o + 4);
        do {
            Sub_1156a60(*ps, val);
            i++;
            ps++;
        } while (i < (int)*(unsigned char*)(o + 0x23));
    }
}

// @ 0x01140a00
int F_01140a00(int a)
{
    short s = *(short*)(a * 0x84 + D + 0x28);
    if (s != -1) return (int)s;
    return a;
}

// @ 0x01140a20
int F_01140a20(int a)
{
    short s = *(short*)(a * 0x84 + D + 0x28);
    if (s != -1) {
        int i = 1;
        short* p = (short*)(s * 0x84 + D + 6);
        do {
            if (*p == a) return i;
            i++;
            p++;
        } while (i < 6);
    }
    return 0;
}

// @ 0x01140a70
int F_01140a70(int a, int ch)
{
    int o = a * 0x84 + D;
    Sub_1142a50(a, ch, *(float*)(*(int*)(o + 0x64) + ch * 4) * *(float*)(o + 0x48));
    return 0;
}

// @ 0x01140ab0
int SNDPLATFORM_stop(int a)
{
    int o = a * 0x84 + D;
    int i = 0;
    if (*(char*)(o + 0x23) != 0) {
        short* ps = (short*)(o + 4);
        do {
            Sub_1142960(*ps);
            i++;
            ps++;
        } while (i < (int)*(unsigned char*)(o + 0x23));
    }
    i = 0;
    if (*(char*)(o + 0x23) != 0) {
        short* ps = (short*)(o + 4);
        do {
            SNDVOICEI_free(*ps);
            i++;
            ps++;
        } while (i < (int)*(unsigned char*)(o + 0x23));
    }
    return 0;
}

// @ 0x01140b20
int F_01140b20(int a, int val)
{
    int o = a * 0x84 + D;
    int i = 0;
    if (*(char*)(o + 0x23) != 0) {
        short* ps = (short*)(o + 4);
        do {
            Sub_1156b40(*ps, i, val);
            i++;
            ps++;
        } while (i < (int)*(unsigned char*)(o + 0x23));
    }
    return 0;
}
