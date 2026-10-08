// Slice s0113ec90 -- SND audio library core: global-state init/restore, per-play packet
// submission and the voice/packet helpers.  Original used VC .NET 2003 (/vc71) + /GL + /LTCG.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "../../include/types.h"

// ---- direct global access (image .data) ------------------------------------
#define A8(a)  (*(unsigned char*)(a))
#define A16(a) (*(unsigned short*)(a))
#define A32(a) (*(unsigned int*)(a))
#define Af(a)  (*(float*)(a))
#define Ap(a)  (*(void**)(a))

extern unsigned char g_16e7c1c;   // 0x16e7c1c

// ---- callees ---------------------------------------------------------------
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
void  __cdecl Sub_11564e0(int a);                      // 0x11564e0
int   __cdecl SNDVOICEI_alloc(int a, int b, int* out, int c, int d); // 0x1140cb0
int   __cdecl Sub_1140b70(int a, int b, int c, int d, void* e);      // 0x1140b70
void  __cdecl SNDVOICEI_free(int a);                   // 0x1141020
void  __cdecl Sub_113fc50(void* p);                    // 0x113fc50 (slice 17)
void  __cdecl Sub_11433b0(int a);                      // 0x11433b0
void  __cdecl Sub_11432a0(int a);                      // 0x11432a0
int   __cdecl Sub_1141150(int a);                      // 0x1141150
int   __cdecl Sub_1156660(int a, int* out);            // 0x1156660
void  __cdecl Sub_1140890(int a);                      // 0x1140890
void  __fastcall Sys16_Free(void* self, int pad, void* p, int z);   // 0x112c850
void* __fastcall Sys16_Alloc(void* self, int pad, unsigned size, const char* name,
                             unsigned align, unsigned zero);        // 0x112c820

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
int SNDSYS_restore(void)
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

// @ 0x0113ef90
int SNDSYSI_chanpubinit(void)
{
    int nch = (int)(short)A16(0x16e7c20);
    int chan = A32(0x15bfe38) + 0x21;
    int size = chan * nch * 4;
    void* sys = Ap(0x16e61a8);
    void* base = Sys16_Alloc(sys, 0, (unsigned)size, "Common Voice State", 0x10, 0);
    A32(0x16e7c78) = (unsigned)base;
    SNDMEMI_alloc(base, size);
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

// @ 0x0113f060
int SNDSYSI_init(void)
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
    SNDMEMI_alloc(p, (int)sz);
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

// @ 0x0113f1c0
int F_0113f1c0(int n)
{
    return n * 0x20 + 0x98;
}

// @ 0x0113f1d0
int F_0113f1d0(int a, int b, int c, int* obj, int sizeParam)
{
    if (g_16e7c1c == 0) return -10;
    Sub_1133450();
    int i = 0;
    if (A8(0x16e7bfe) != 0) {
        do {
            unsigned* tbl = (unsigned*)0x16e7fcc;
            if (tbl[i] == 0) {
                ((short*)obj)[8] = (short)((sizeParam - 0x98) >> 5);
                obj[0x14] = a;
                obj[0x15] = b;
                obj[0x16] = c;
                *obj = -1;
                tbl[i] = (unsigned)obj;
                Sub_1133460();
                return i;
            }
            i++;
        } while (i < (int)A8(0x16e7bfe));
    }
    Sub_1133460();
    return -9;
}

// @ 0x0113f250
int F_0113f250(int index, int* desc, short* param3, char* param4)
{
    if (g_16e7c1c == 0) return -10;
    Sub_11564e0((int)param4);
    unsigned uVar3 = (unsigned)*(unsigned char*)((char*)desc + 2);
    unsigned* tbl = (unsigned*)0x16e7fcc;
    int* pkt = (int*)tbl[index];
    if (pkt == 0) return -1;
    pkt[0x17] = *desc;
    pkt[1] = 0;
    pkt[0x12] = 0;
    pkt[0x13] = 0;
    pkt[3] = 0;
    pkt[2] = 0;
    *(unsigned short*)((char*)pkt + 0x46) = 0;
    *(unsigned short*)(pkt + 0x11) = 0;
    int local1c = 0;
    unsigned char* pb = (unsigned char*)pkt;
    if (pb[0x5e] != 0) {
        int* pl = (int*)((char*)param3 + 20);
        unsigned* p9 = (unsigned*)(pkt + 0x18);
        unsigned* p4 = (unsigned*)(pkt + 10);
        do {
            local1c++;
            *(unsigned*)((char*)p9 - 0x50) = 0;
            *(unsigned short*)(p4 + 3) = 0;
            *(unsigned short*)p4 = 0;
            int v = *pl;
            pl++;
            *p9 = (unsigned)v;
            p4 = (unsigned*)((char*)p4 + 2);
            p9++;
        } while (local1c < (int)(unsigned char)pb[0x5e]);
    }
    for (;;) {
        int local8;
        int iv = SNDVOICEI_alloc((int)uVar3, 0x65, &local8, 0, (int)A16(0x16e7bf8 + 2));
        if (iv < 0) { *pkt = -9; return *pkt; }
        *pkt = local8;
        int li = -1;
        if (*(unsigned char*)((char*)desc + 2) != 0) {
            short best = -1;
            int* pl = (int*)(iv * 0x84 + 4 + A32(0x16e7c78));
            int k = 0;
            do {
                short v = (short)*pl;
                if (best < v) { li = k; best = v; }
                pl = (int*)((char*)pl + 2);
                k++;
            } while (k < (int)(unsigned char)*(unsigned char*)((char*)desc + 2));
        }
        pb[0x42] = (unsigned char)li;
        int base = iv * 0x84 + (int)A32(0x16e7c78);
        *(int*)(base + 0x18) = -1;
        *(int*)(base + 0x14) = 0;
        *(short*)(base + 0x20) = (short)*desc;
        *(unsigned char*)(base + 0x22) = *(unsigned char*)((char*)desc + 3);
        *(unsigned char*)(base + 0x23) = *(unsigned char*)((char*)desc + 2);
        if (*(unsigned char*)((char*)desc + 2) == 1) {
            *(unsigned short*)(base + 0x1c) = *(unsigned short*)(param4 + 6);
        } else {
            Sub_113fc50((void*)base);
        }
        *(unsigned short*)(base + 0x12) = 0xffff;
        *(unsigned short*)(base + 0x4c) = 0;
        *(unsigned short*)(base + 0x7c) = *param3;
        *(unsigned short*)(base + 0x80) = *(unsigned short*)(param4 + 8);
        *(unsigned char*)(base + 0x1e) = param4[4];
        **(float**)(base + 100) = (float)(int)param4[4] * 0.007874016f;
        *(unsigned char*)(base + 0x24) = 0;
        *(unsigned char*)(base + 0x25) = 0;
        *(unsigned*)(base + 0x78) = 0;
        *(float*)(base + 0x38) = (float)(int)*param4 * 0.007874016f;
        unsigned nd = (unsigned)*(unsigned char*)((char*)desc + 2);
        int i10 = 0;
        if (nd != 0) {
            do {
                *(short*)(base + 0x54 + i10 * 2) =
                    param3[i10 + 4] - *(short*)(0x16e7c74 + (i10 + nd * 6) * 2);
                int vi = *(short*)(base + 4 + i10 * 2) * 0x84 + (int)A32(0x16e7c78);
                *(char*)(vi + 99) = param4[3];
                *(unsigned char*)(vi + 0x2b) = *(unsigned char*)((char*)param3 + 3);
                *(unsigned*)(vi + 0x38) = *(unsigned*)(base + 0x38);
                *(unsigned*)(vi + 0x70) = 0;
                *(unsigned*)(vi + 0x30) = 0;
                *(unsigned*)(vi + 0x48) = *(unsigned*)(vi + 0x38);
                *(unsigned char*)(vi + 0x60) = 1;
                *(unsigned char*)(vi + 0x62) = 0;
                *(unsigned char*)(vi + 0x61) = 0;
                *(unsigned*)(vi + 0x40) = 0x7f0000;
                *(unsigned*)(vi + 0x44) = 0x7fffffff;
                *(unsigned*)(vi + 0x3c) = 0;
                *(unsigned*)(vi + 0x6c) = 0;
                *(unsigned*)(vi + 0x74) = 0;
                *(unsigned char*)(vi + 0x1f) = (i10 == 5);
                nd = *(unsigned char*)((char*)desc + 2);
                i10++;
            } while (i10 < (int)nd);
        }
        local1c = 0;
        if (*(unsigned char*)((char*)desc + 2) != 0) {
            short* ps = (short*)(base + 0x54);
            do {
                int ch = (int)*(ps - 0x28);
                short sv = *ps;
                ps++;
                short* dst = (short*)(ch * 0x84 + (int)A32(0x16e7c78) + 0x1c);
                *dst = (short)(*dst + sv);
                local1c++;
            } while (local1c < (int)(unsigned char)*(unsigned char*)((char*)desc + 2));
        }
        *(unsigned short*)(base + 0x7e) = 0;
        Sub_11433b0(iv);
        int r = Sub_1140b70(iv, *(unsigned short*)(param4 + 10), *(unsigned short*)(param4 + 0xc),
                            *(unsigned short*)(param4 + 0xe), param3);
        if (r >= 0) {
            int ecx2 = *pkt;
            return ecx2;
        }
        if (uVar3 != 0) {
            int q = iv * 0x84 + 4;
            unsigned cnt = uVar3;
            do {
                SNDVOICEI_free((int)*(short*)(q + (int)A32(0x16e7c78)));
                q += 2;
                cnt--;
            } while (cnt != 0);
        }
        *pkt = r;
    }
}

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

// @ 0x0113fa70  (thiscall object: +4 src, +8 dst, +0xc count, +0x14 chans)
struct PktCursor {
    char pad0[0x0c];
    int count;      // +0x0c
    char pad10[0x14 - 0x10];
    short chans;    // +0x14

    void Decode3(int srcs, int maxCount);
};

void PktCursor::Decode3(int srcs, int maxCount)
{
    int n = count;
    if (n == 0) return;
    if (maxCount < n) n = maxCount;
    int i = 0;
    if (n > 0) {
        do {
            short c = 0;
            if (chans > 0) {
                do {
                    unsigned short* d = (unsigned short*)(*(int*)(srcs + c * 4) + i * 2);
                    *(unsigned short**)((char*)this + 8) = d;
                    unsigned char* s = *(unsigned char**)((char*)this + 4);
                    *d = (unsigned short)((s[2] << 8) | s[1]);
                    *(int*)((char*)this + 4) = (int)s + 3;
                    c++;
                } while (c < chans);
            }
            i++;
        } while (i < n);
    }
    count -= n;
}

// @ 0x0113fb20
struct PktCursor2 {
    char pad0[0x0c];
    int count;      // +0x0c
    char pad10[0x14 - 0x10];
    short chans;    // +0x14

    void Decode2(int srcs, int maxCount);
};

void PktCursor2::Decode2(int srcs, int maxCount)
{
    int n = count;
    if (n == 0) return;
    if (maxCount < n) n = maxCount;
    int i = 0;
    if (n > 0) {
        do {
            short c = 0;
            if (chans > 0) {
                do {
                    unsigned short* d = (unsigned short*)(*(int*)(srcs + c * 4) + i * 2);
                    *(unsigned short**)((char*)this + 8) = d;
                    unsigned short s = **(unsigned short**)((char*)this + 4);
                    *d = s;
                    *(int*)((char*)this + 4) = *(int*)((char*)this + 4) + 2;
                    c++;
                } while (c < chans);
            }
            i++;
        } while (i < n);
    }
    count -= n;
}

// @ 0x0113fba0
int F_0113fba0(int a, unsigned b)
{
    if (g_16e7c1c == 0) return -10;
    int handle = Sub_1141150(a);
    if (handle < 0) return handle;
    int local = -1;
    int r = Sub_1156660(handle, &local);
    while (r != 0) {
        int o = local * 0x84 + (int)A32(0x16e7c78);
        if (*(unsigned short*)(o + 0x80) == b) return 0;
        *(unsigned short*)(o + 0x80) = (unsigned short)b;
        Sub_11433b0(local);
        Sub_1140890(local);
        r = Sub_1156660(handle, &local);
    }
    return handle;
}
