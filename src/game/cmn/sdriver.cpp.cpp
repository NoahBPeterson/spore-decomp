// src/game/cmn/sdriver.cpp.cpp -- migrated from slice(s) s0113fc50 by tools/migrate/rewrite.py
// Object file: cmn/sdriver.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s0113fc50 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define A16(a) (*(unsigned short*)(a))
#define A32(a) (*(unsigned int*)(a))
#define Af(a)  (*(float*)(a))
#define Ap(a)  (*(void**)(a))
void  __cdecl Sub_1142a50(int, int, float);             // 0x1142a50
void  __cdecl Sub_1142960(int);                         // 0x1142960
void  __cdecl Sub_11568a0(int, int);                    // 0x11568a0 (MIX_setpitch)
void  __cdecl Sub_1156960(int, float);                  // 0x1156960 (MIX_setlowpass)
void  __cdecl Sub_1156a60(int, int);                    // 0x1156a60 (MIX_sethighpass)
void  __cdecl Sub_1133450(void);                        // 0x1133450
void  __cdecl Sub_1133460(void);                        // 0x1133460
void  __cdecl SNDMEMI_alloc16(void* p, int size);       // 0x113ec90 (slice 16)
void  __cdecl SNDVOICEI_free(int);                      // 0x1141020 (slice 16)
void* __fastcall Sys17_Alloc(void* self, int pad, unsigned size, const char* name,
                             unsigned align, unsigned zero);   // 0x112c820
void  __fastcall Sys17_Free(void* self, int pad, void* p, int z); // 0x112c850
#define D  (A32(0x16e7c78))
#define SYSPTR (Ap(0x16e61a8))
void FUN_01140930(int a, int val);
int  F_01140a70(int a, int ch);
// ---- items of slice s0113fc50 end

// @ 0x01140810
namespace  {
int SNDPLATFORM_init()
{
    Sub_1133450();
    int n = (int)(short)A16(0x16e7c20) * 0x18;
    void* p = Sys17_Alloc(SYSPTR, 0, (unsigned)n, "Platform voices", 0x10, 0);
    A32(0x16e804c) = (unsigned)p;
    SNDMEMI_alloc16(p, n);
    Sub_1133460();
    return 0;
}
}  // namespace 

// @ 0x01140870
namespace  {
int SNDPLATFORM_restore()
{
    Sub_1133450();
    Sys17_Free(SYSPTR, 0, (void*)A32(0x16e804c), 0);
    Sub_1133460();
    return 0;
}
}  // namespace 

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
namespace  {
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
}  // namespace 

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
namespace  {
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
}  // namespace 
