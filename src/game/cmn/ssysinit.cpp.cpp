// src/game/cmn/ssysinit.cpp.cpp -- migrated from slice(s) s0113ec90 by tools/migrate/rewrite.py
// Object file: cmn/ssysinit.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s0113ec90 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define A8(a)  (*(unsigned char*)(a))
#define A16(a) (*(unsigned short*)(a))
#define A32(a) (*(unsigned int*)(a))
#define Af(a)  (*(float*)(a))
#define Ap(a)  (*(void**)(a))
int   __cdecl Sub_1140760(void);                       // 0x1140760
void  __cdecl Sub_1140780(void);                       // 0x1140780
int   __cdecl Sub_11330e0(void);                       // 0x11330e0
void  __cdecl Sub_1156380(void);                       // 0x1156380
void  __cdecl Sub_1142690(void);                       // 0x1142690
void  __cdecl SNDPLATFORM_restore(void);               // 0x1140870
void  __cdecl Sub_1133450(void);                       // 0x1133450
void  __cdecl Sub_1133460(void);                       // 0x1133460
int   __cdecl SNDPLATFORM_init(void);                  // 0x1140810
void  __cdecl Sub_1156480(int a);                      // 0x1156480
void  __cdecl Sub_11563b0(void);                       // 0x11563b0
void  __cdecl SNDI_precalcaztospkrvol(void);           // 0x1155f40
void  __cdecl MIX_create(void* desc);                  // 0x1142a80
void  __fastcall Sys16_Free(void* self, int pad, void* p, int z);   // 0x112c850
void* __fastcall Sys16_Alloc(void* self, int pad, unsigned size, const char* name,
                             unsigned align, unsigned zero);        // 0x112c820
// ---- items of slice s0113ec90 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern unsigned char g_16e7c1c;   // 0x16e7c1c

// @ 0x0113ec90
void SNDMEMI_alloc(void* dst, int size)
{
    unsigned char* p = (unsigned char*)dst;
    int n = size;
    if (((unsigned)p & 7) != 0) {
        if ((((unsigned)p & 1) != 0) && n >= 1) { *p = 0; p++; n--; }
        if ((((unsigned)p & 2) != 0) && n >= 2) { *(unsigned short*)p = 0; p += 2; n -= 2; }
        if ((((unsigned)p & 4) != 0) && n >= 4) { *(unsigned*)p = 0; p += 4; n -= 4; }
    }
    if (n >= 0) {
        while (n - 0x20 >= 0) {
            *(unsigned*)p = 0; *(unsigned*)(p + 4) = 0;
            *(unsigned*)(p + 8) = 0; *(unsigned*)(p + 0xc) = 0;
            *((unsigned*)p + 4) = 0; *((unsigned*)p + 5) = 0;
            *((unsigned*)p + 6) = 0; *((unsigned*)p + 7) = 0;
            p += 0x20; n -= 0x20;
        }
        while (n - 8 >= 0) {
            *(unsigned*)p = 0; *(unsigned*)(p + 4) = 0;
            p += 8; n -= 8;
        }
        if (n != 0) {
            if ((n & 4) != 0) { *(unsigned*)p = 0; p += 4; }
            if ((n & 2) != 0) { *(unsigned short*)p = 0; p += 2; }
            if ((n & 1) != 0) { *p = 0; }
        }
    }
}

// @ 0x0113eda0
int F_0113eda0(unsigned* out)
{
    if (A32(0x16e7bec) == 0) {
        A8(0x16e7bf0) = 0xff;
        A16(0x16e7bf8) = 0x10;
        A8(0x16e7bfe) = 0x10;
        A8(0x16e7bfb) = 1;
        A8(0x16e7bfa) = 0x20;
        A8(0x16e7bfd) = 0x19;
        A8(0x16e7bff) = 5;
        A8(0x16e7c00) = 1;
        A32(0x16e7be8) = Sub_1140760();
        A32(0x16e7c0c) = A32(0x16e7bf4);
        A32(0x16e7c10) = A32(0x16e7bf8);
        A32(0x16e7c14) = A32(0x16e7bfc);
        A32(0x16e7c18) = A32(0x16e7c00);
        A32(0x16e7bec) = 1;
    }
    unsigned r = A32(0x16e7be8);
    unsigned* src = (unsigned*)0x16e7bf0;
    for (int i = 0; i < 7; i++) out[i] = src[i];
    return (int)r;
}

// @ 0x0113ee40
int F_0113ee40(unsigned* p)
{
    A32(0x16e7bf4) = p[1];
    A32(0x16e7bf8) = p[2];
    A32(0x16e7bfc) = p[3];
    A32(0x16e7c00) = p[4];
    A32(0x16e7c04) = p[5];
    A32(0x16e7c08) = p[6];
    unsigned ecx = p[3];
    if ((unsigned char)(ecx >> 16) > 0x20) {
        A8(0x16e7bfe) = 0x20;
    }
    unsigned edx = p[2];
    unsigned char al = A8(0x16e7bf0);
    if ((unsigned char)(edx >> 16) > al) {
        A8(0x16e7bfa) = al;
    }
    unsigned short ax = A8(0x16e7bfa);
    A16(0x16e7c20) = ax;
    if (ax > 0xff) A16(0x16e7c20) = 0xff;
    Sub_1140780();
    A32(0x16e7c0c) = A32(0x16e7bf4);
    A32(0x16e7c18) = A32(0x16e7c00);
    Af(0x16e6264) = 10.0f;
    A32(0x16e7c10) = A32(0x16e7bf8);
    A32(0x16e7c14) = A32(0x16e7bfc);
    return 0;
}

// @ 0x0113ef00
namespace  {
int SNDSYS_restore()
{
    if (Sub_11330e0() == 0) return -14;
    if (Ap(0x16e7c68) != 0) ((void(__cdecl*)())Ap(0x16e7c68))();
    if (Ap(0x16e7c6c) != 0) ((void(__cdecl*)())Ap(0x16e7c6c))();
    if (Ap(0x16e7c74) != 0) ((void(__cdecl*)())Ap(0x16e7c74))();
    Sub_1156380();
    if (Ap(0x16e7c70) != 0) ((void(__cdecl*)(int))Ap(0x16e7c70))(-1);
    Sub_1142690();
    SNDPLATFORM_restore();
    Sub_1133450();
    void* sys = Ap(0x16e61a8);
    Sys16_Free(sys, 0, Ap(0x16e7c78), 0);
    Sys16_Free(sys, 0, Ap(0x16e7c7c), 0);
    Sub_1133460();
    g_16e7c1c = 0;
    return 0;
}
}  // namespace 

// @ 0x0113ef90
namespace  {
int SNDSYSI_chanpubinit()
{
    int nch = (int)(short)A16(0x16e7c20);
    int chan = A32(0x15bfe38) + 0x21;
    int size = chan * nch * 4;
    void* sys = Ap(0x16e61a8);
    void* base = Sys16_Alloc(sys, 0, (unsigned)size, "Common Voice State", 0x10, 0);
    A32(0x16e7c78) = (unsigned)base;
    SNDMEMI_alloc((char *)base, size);
    int stride = A32(0x15bfe38);
    int off = nch * 0x84 + (int)base;
    int i = 0;
    if (nch > 0) {
        do {
            *(int*)(A32(0x16e7c78) + i * 0x84 + 0x64) = off;
            int n = A32(0x15bfe38);
            int j = 0;
            if (n > 0) {
                do {
                    *(float*)(*(int*)(A32(0x16e7c78) + i * 0x84 + 0x64) + j * 4) = 1.0f;
                    j++;
                } while (j < (int)A32(0x15bfe38));
            }
            i++;
            off += A32(0x15bfe38) * 4;
        } while (i < nch);
    }
    return 0;
}
}  // namespace 

// @ 0x0113f060
namespace  {
int SNDSYSI_init()
{
    if (g_16e7c1c != 0) return 0;
    if (A16(0x16e7c20) == 0) {
        int r = F_0113eda0((unsigned*)0x16e7bf0);
        if (r < 0) return r;
        F_0113ee40((unsigned*)0x16e7bf0);
    }
    Sub_1156480((int)A32(0x16e7bf4));
    g_16e7c1c = 1;
    Sub_1133450();
    SNDSYSI_chanpubinit();
    unsigned sz = (unsigned)A16(0x16e7bf8) * 8;
    void* sys = Ap(0x16e61a8);
    void* p = Sys16_Alloc(sys, 0, sz, "Bank List Array", 0x10, 0);
    A32(0x16e7c7c) = (unsigned)p;
    SNDMEMI_alloc((char *)p, (int)sz);
    Sub_1133460();
    A32(0x16e7c24) = 0;
    Af(0x15bfe34) = 1.0f;
    A8(0x16e7c22) = 0;
    A8(0x16e7c1d) = 0;
    A8(0x16e7c1e) = 0;
    int r = SNDPLATFORM_init();
    if (r < 0) {
        SNDPLATFORM_restore();
        g_16e7c1c = 0;
        return r;
    }
    unsigned char body[0x14];
    *(unsigned char*)&body[0] = A8(0x16e7bfa);
    *(unsigned char*)&body[1] = (unsigned char)(A8(0x16e7c00) + A8(0x16e7bff));
    float sr = Af((unsigned)Ap(0x16e61a8) + 0xc0);
    *(int*)&body[2] = (int)sr;
    void* fp = (void*)0x1141020;
    *(void**)&body[6] = fp;
    body[0x0a] = 0;
    MIX_create(body);
    A8(0x16e7be4) = (unsigned char)(A8(0x16e7c00) + A8(0x16e7bff));
    Sub_11563b0();
    SNDI_precalcaztospkrvol();
    return 0;
}
}  // namespace 
