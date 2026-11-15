// src/game/cmn/spktplay.cpp.cpp -- migrated from slice(s) s0113ec90 by tools/migrate/rewrite.py
// Object file: cmn/spktplay.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern unsigned char g_16e7c1c;   // 0x16e7c1c

// ---- items of slice s0113ec90 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define A8(a)  (*(unsigned char*)(a))
#define A32(a) (*(unsigned int*)(a))
#define Ap(a)  (*(void**)(a))
extern unsigned char g_16e7c1c;   // 0x16e7c1c
void  __cdecl Sub_1133450(void);                       // 0x1133450
void  __cdecl Sub_1133460(void);                       // 0x1133460
void  __cdecl Sub_11432a0(int a);                      // 0x11432a0
void  __fastcall Sys16_Free(void* self, int pad, void* p, int z);   // 0x112c850
// ---- items of slice s0113ec90 end

// @ 0x0113f5c0
int SNDPKTPLAY_submit(int index, int src)
{
    if (g_16e7c1c == 0) return -10;
    unsigned* tbl = (unsigned*)0x16e7fcc;
    int o = (int)tbl[index];
    if (o == 0) return -1;
    int i = 0;
    if (A8(o + 0x5e) != 0) {
        short* ps = (short*)(o + 0x34);
        do {
            if ((int)*(short*)(o + 0x40) - 1 <= (int)*ps) return -13;
            i++;
            ps++;
        } while (i < (int)A8(o + 0x5e));
    }
    int off = (int)*(short*)(o + 0x46) * 0x20;
    int* dst = (int*)(off + 0x78 + o);
    dst[1] = dst[1] ^ ((*(unsigned*)(off + 0x7c + o) ^ *(unsigned*)(src + 4)) & 0x7fffffff);
    dst[1] = (*(unsigned*)(src + 4) & 0x80000000u) | (dst[1] & 0x7fffffff);
    *dst = *(int*)(o + 4);
    if (A8(o + 0x5e) != 0) {
        int* d = dst + 2;
        short* ps = (short*)(o + 0x34);
        int* sp = (int*)(src + 0xc);
        int j = 0;
        do {
            *d = *sp;
            *ps = (short)(*ps + 1);
            j++;
            sp++;
            d++;
            ps++;
        } while (j < (int)A8(o + 0x5e));
    }
    *(unsigned*)(o + 0x48) = (*(unsigned*)(src + 4) & 0x7fffffff) + *(int*)(o + 0x48);
    int ret = *(int*)(o + 4);
    *(int*)(o + 4) = *(int*)(o + 4) + 1;
    *(short*)(o + 0x46) = (short)(*(short*)(o + 0x46) + 1);
    if (*(short*)(o + 0x40) <= *(short*)(o + 0x46)) {
        *(unsigned short*)(o + 0x46) = 0;
    }
    return ret;
}

// @ 0x0113f6c0
int F_0113f6c0(int index)
{
    int mx = 0;
    if (g_16e7c1c == 0) return -10;
    unsigned* tbl = (unsigned*)0x16e7fcc;
    int o = (int)tbl[index];
    if (o != 0) {
        int i = 0;
        if (A8(o + 0x5e) != 0) {
            short* ps = (short*)(o + 0x34);
            do {
                if (mx <= (int)*ps) mx = (int)*ps;
                i++;
                ps++;
            } while (i < (int)A8(o + 0x5e));
        }
        return ((int)*(short*)(o + 0x40) - mx) + -1;
    }
    return -1;
}

// @ 0x0113f720
int F_0113f720(int index)
{
    if (g_16e7c1c == 0) return -10;
    unsigned* tbl = (unsigned*)0x16e7fcc;
    int o = (int)tbl[index];
    if (o == 0) return -1;
    int b = *(int*)(o + 0x48);
    int a = *(int*)(o + 0x4c);
    return a + b;
}

// @ 0x0113f750
int F_0113f750(int index)
{
    if (g_16e7c1c == 0) return -10;
    Sub_1133450();
    unsigned* tbl = (unsigned*)0x16e7fcc;
    tbl[index] = 0;
    Sub_1133460();
    return 0;
}

// @ 0x0113f780
int F_0113f780(int index, int ch, int* out1, int* out2)
{
    int gcc = (int)A32(0x16e7cc8);
    int o = (int)((unsigned*)0x16e7fcc)[index];
    int b6 = 1;
    int b7 = 1;
    int i8 = 0;
    if (o == 0) return 0;
    if (A8(o + 0x5e) != 0) {
        unsigned* pu = (unsigned*)(o + 0x10);
        do {
            if (*pu <= *(unsigned*)(o + 8)) b6 = 0;
            i8++;
            pu++;
        } while (i8 < (int)A8(o + 0x5e));
        if (!b6) goto LAB_F821;
    }
    {
        short sv = *(short*)(o + 0x44);
        if (*(int*)(o + 0x50) != 0) {
            *(unsigned short*)(0x16e7ccc + gcc * 8 + 0) = 1;
            *(unsigned short*)(0x16e7ccc + gcc * 8 + 2) = (unsigned short)index;
            *(unsigned*)(0x16e7ccc + gcc * 8 + 4) = *(unsigned*)(sv * 0x20 + o + 0x80);
            A32(0x16e7cc8) = A32(0x16e7cc8) + 1;
        }
    }
    *(short*)(o + 0x44) = (short)(*(short*)(o + 0x44) + 1);
    *(int*)(o + 8) = *(int*)(o + 8) + 1;
    if (*(short*)(o + 0x40) <= *(short*)(o + 0x44)) {
        *(unsigned short*)(o + 0x44) = 0;
    }
LAB_F821:
    if (*(short*)(o + 0x34 + ch * 2) == 0) return 0;
    {
        int vo = *(short*)(o + 0x28 + ch * 2) * 0x20 + 0x78 + o;
        *out1 = (*(int*)(vo + 4) * 2) >> 1;
        *out2 = *(int*)(vo + 4) >> 0x1f;
        short* ps = (short*)(o + 0x28 + ch * 2);
        *ps = (short)(*ps + 1);
        int* pi = (int*)(o + 0x10 + ch * 4);
        *pi = *pi + 1;
        int k = 0;
        unsigned* pu = (unsigned*)(o + 0x10);
        for (;;) {
            if (*pu <= *(unsigned*)(o + 0xc)) b7 = 0;
            k++;
            pu++;
            if (!b7) break;
            if ((int)A8(o + 0x5e) <= k) {
                *(int*)(o + 0xc) = *(int*)(o + 0xc) + 1;
                *(int*)(o + 0x48) = *(int*)(o + 0x48) - ((*(int*)(vo + 4) * 2) >> 1);
                *(int*)(o + 0x4c) = *(int*)(o + 0x4c) + ((*(int*)(vo + 4) * 2) >> 1);
                goto LAB_F8B3;
            }
        }
        if (!b7) goto LAB_F8B3;
        *(int*)(o + 0xc) = *(int*)(o + 0xc) + 1;
        *(int*)(o + 0x48) = *(int*)(o + 0x48) - ((*(int*)(vo + 4) * 2) >> 1);
        *(int*)(o + 0x4c) = *(int*)(o + 0x4c) + ((*(int*)(vo + 4) * 2) >> 1);
    LAB_F8B3:
        if (*(short*)(o + 0x40) <= *(short*)(o + 0x28 + ch * 2)) {
            *(unsigned short*)(o + 0x28 + ch * 2) = 0;
        }
        *(short*)(o + 0x34 + ch * 2) = (short)(*(short*)(o + 0x34 + ch * 2) - 1);
        int r = *(int*)(vo + 8 + ch * 4);
        if (r != 0) return r;
        return -1;
    }
}

// @ 0x0113f8f0
void F_0113f8f0(int index, int p2, int p3)
{
    int o = (int)((unsigned*)0x16e7fcc)[index];
    if (o != 0 && p2 == (int)*(char*)(o + 0x42)) {
        *(int*)(o + 0x4c) = *(int*)(o + 0x4c) - p3;
        if (*(int*)(o + 0x54) != 0) {
            int n = (int)A32(0x16e7cc8);
            *(unsigned short*)(0x16e7ccc + n * 8 + 0) = 0;
            *(unsigned short*)(0x16e7ccc + n * 8 + 2) = (unsigned short)index;
            *(unsigned*)(0x16e7ccc + n * 8 + 4) = (unsigned)p3;
            A32(0x16e7cc8) = A32(0x16e7cc8) + 1;
        }
    }
}

// @ 0x0113f940
void F_0113f940(void)
{
    int i = 0;
    if ((int)A32(0x16e7cc8) > 0) {
        unsigned* pu = (unsigned*)0x16e7cd0;
        do {
            int o = (int)((unsigned*)0x16e7fcc)[*(unsigned short*)((char*)pu - 2)];
            if (o != 0) {
                if (*(short*)((char*)pu - 4) == 0) {
                    ((void(__cdecl*)(unsigned, unsigned, unsigned))*(void**)(o + 0x54))(
                        *(unsigned short*)((char*)pu + -2), *pu, *(unsigned*)(o + 0x58));
                } else {
                    ((void(__cdecl*)(unsigned, unsigned))*(void**)(o + 0x50))(
                        *pu, *(unsigned*)(o + 0x58));
                }
            }
            i++;
            pu += 2;
        } while (i < (int)A32(0x16e7cc8));
        A32(0x16e7cc8) = 0;
        return;
    }
    A32(0x16e7cc8) = 0;
}

// @ 0x0113f9b0
int F_0113f9b0(int index)
{
    if (g_16e7c1c == 0) return -10;
    int* o = (int*)((unsigned*)0x16e7fcc)[index];
    if (o != 0) {
        Sub_11432a0(*o);
        F_0113f940();
        if (*o >= 0) {
            int i = 0;
            *o = -1;
            if (*(unsigned char*)((char*)o + 0x5e) != 0) {
                int* p = o + 0x18;
                do {
                    if (*p != 0) {
                        Sys16_Free(Ap(0x16e61a8), 0, (void*)*p, 0);
                        *p = 0;
                    }
                    i++;
                    p++;
                } while (i < (int)*(unsigned char*)((char*)o + 0x5e));
            }
        }
        return 0;
    }
    return -1;
}
