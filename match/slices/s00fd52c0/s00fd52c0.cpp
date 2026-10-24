// Slice s00fd52c0 -- On2 VP6 decoder (lib_b5rw / vp6.obj): the C (non-SIMD)
// pixel-filter kernels plus the codec-context helpers that allocate and
// release the decoder's work buffers.
//
//  0x00fd52c0  8-tap 8x8 separable filter (pass1 8->8, pass2 8->8 with rounding)
//  0x00fd56c0  sparse 4x4 -> 8x8 outer-product seed for the 4-tap filter
//  0x00fd5770  4-tap 8x8 separable filter
//  0x00fd5d50  DC-only fill (single tap, 32 dwords)
//  0x00fd5d90  release the three coefficient planes
//  0x00fd5e00  allocate the three coefficient planes
//  0x00fd5e90  destroy a decoder context
//  0x00fd5ee0  create a decoder context
//  0x00fd5fa0  one-time VP6 initialisation
//  0x00fd5fc0  derive the plane geometry record from the frame dimensions
//  0x00fd6050  allocate + fill the geometry record
//  0x00fd6090  release the geometry record
//  0x00fd60b0  default (non-SIMD) expand: build the edge permutation table
//  0x00fd60e0  fill the prediction buffers from the frame type / edge map
//  0x00fd61f0  re-expand the prediction buffers when the frame type changed
//
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include <string.h>

extern "C" void* __cdecl memset(void*, int, unsigned int);   // IAT thunk 0x011e073e
#pragma function(memset)

extern "C" void __stosd(unsigned* dst, unsigned val, unsigned count);
#pragma intrinsic(__stosd)

typedef unsigned char  u8;
typedef unsigned short u16;
typedef short          s16;

struct ScanBufs;

// ---------------------------------------------------------------- callees
extern "C" void* FUN_00fd47a0(int size, int zero);                 // 0x00fd47a0
extern "C" void  FUN_00fd47b0(void* p);                            // 0x00fd47b0
extern "C" void  FUN_00fd4ed0(const short*, const short*, int*);   // 0x00fd4ed0
extern "C" int   FUN_00fd03b0(void);                               // 0x00fd03b0
extern "C" void  FUN_00fd03c0(void);                               // 0x00fd03c0
extern "C" void  FUN_00fd6cc0(void);                               // 0x00fd6cc0
extern "C" void  vp6_scan_destroy(ScanBufs** pp);                  // 0x00fd62d0
__declspec(noinline) extern "C" void FUN_00fd6090(void** p);        // 0x00fd6090

// ---------------------------------------------------------------- globals
extern "C" int   g_vp6_mode;                 // 0x016d940c
extern "C" void (*g_vp6ExpandFn)(void*);     // 0x016d9414
extern "C" void* p_vp6_filter_[0x41];        // 0x016d9588

union Vp6TabEntry { int d; u16 w[2]; };
extern "C" const Vp6TabEntry DAT_01492cf0[]; // 0x01492cf0 frame-type -> filter flags
extern "C" const Vp6TabEntry DAT_01492df0[]; // 0x01492df0
extern "C" const u16 DAT_01492ef0[];         // 0x01492ef0
extern "C" const u16 DAT_01492f70[];         // 0x01492f70
extern "C" const int DAT_01492ff0[];         // 0x01492ff0 edge permutation
extern "C" int DAT_014930f0[];               // 0x014930f0

// ---------------------------------------------------------------- types
// Coefficient-scan record allocated by vp6_scan_create (0x00fd6320).
struct ScanBufs {
    int   frameType;     // 0x00 frame-type index
    int   f04;           // 0x04
    int   f08;           // 0x08
    int*  f0c;           // 0x0c filter-table pointer set by the expand fn
    u8    edges[0x40];   // 0x10 edge map (filled by FUN_00fd60b0)
    u16*  buf0;          // 0x50 prediction buffer 0
    u16*  buf1;          // 0x54 prediction buffer 1
    u8*   raw0;          // 0x58 unaligned base of buf0
    u8*   raw1;          // 0x5c unaligned base of buf1
};

// Decoder context (0x3b64 bytes). Only the members this slice touches are
// named; the rest are padding to the retail offsets.
#pragma pack(push, 2)
struct Vp6Ctx {
    u8        pad0000[0xf4];
    ScanBufs* scan;       // 0x0f4 coefficient-scan record
    u8        pad0f8[0x148 - 0x0f8];
    int*      geom;       // 0x148 geometry record (FUN_00fd6050)
    u8        pad14c[0x150 - 0x14c];
    int       width;      // 0x150
    int       height;     // 0x154
    int       f158;       // 0x158
    int       f15c;       // 0x15c
    int       f160;       // 0x160
    int       f164;       // 0x164
    u8        pad168[0x16c - 0x168];
    int       f16c;       // 0x16c
    u8        pad170[0x1cc - 0x170];
    u8*       buf0;       // 0x1cc aligned plane 0
    u8*       raw0;       // 0x1d0 unaligned plane 0
    u8*       buf1;       // 0x1d4 aligned plane 1
    u8*       raw1;       // 0x1d8 unaligned plane 1
    u8*       buf2;       // 0x1dc aligned plane 2
    u8*       raw2;       // 0x1e0 unaligned plane 2
    void**    filterTab;  // 0x1e4 pointer to p_vp6_filter_
    u8        pad1e8[0x39a2 - 0x1e8];
    int       f39a2;      // 0x39a2
    int       f39a6;      // 0x39a6
    int       f39aa;      // 0x39aa
    int       f39ae;      // 0x39ae
    int       f39b2;      // 0x39b2
    u16       f39b6;      // 0x39b6
    u8        f39b8[0x18c]; // 0x39b8
};
#pragma pack(pop)

// =================================================================== filters

// @ 0x00fd52c0
void FUN_00fd52c0(const short* p1, const short* p2, short* dst)
{
    int buf[64];
    int r, c;

    FUN_00fd4ed0(p2, p1, buf);

    // pass 1: horizontal 8-tap filter over each of the 8 rows
    for (r = 0; r < 8; r++) {
        int* p = buf + r * 8;
        int t0 = p[0], t1 = p[1], t2 = p[2], t3 = p[3];
        int t4 = p[4], t5 = p[5], t6 = p[6], t7 = p[7];
        if ((t0 | t1 | t2 | t3 | t4 | t5 | t6 | t7) != 0) {
            int P  = ((t7 * 0x31f1) >> 16) + ((t1 * 0xfb15) >> 16);
            int Q  = ((t1 * 0x31f1) >> 16) - ((t7 * 0xfb15) >> 16);
            int T  = ((t3 * 0xd4db) >> 16) + ((t5 * 0x8e3a) >> 16);
            int W  = ((t5 * 0xd4db) >> 16) - ((t3 * 0x8e3a) >> 16);
            int Z  = ((t0 + t4) * 0xb505) >> 16;
            int AA = ((t0 - t4) * 0xb505) >> 16;
            int AC = ((t2 * 0xec83) >> 16) + ((t6 * 0x61f8) >> 16);
            int AB = ((t2 * 0x61f8) >> 16) - ((t6 * 0xec83) >> 16);
            int AF = ((Q - W) * 0xb505) >> 16;
            int AI = ((P - T) * 0xb505) >> 16;

            p[0] = (short)((T + P) + (AC + Z));
            p[7] = (short)((AC + Z) - (T + P));
            p[1] = (short)((AA + AI) + (AF + AB));
            p[2] = (short)((AA + AI) - (AF + AB));
            p[3] = (short)((W + Q) + (Z - AC));
            p[4] = (short)((Z - AC) - (W + Q));
            p[5] = (short)((AF - AB) + (AA - AI));
            p[6] = (short)((AA - AI) - (AF - AB));
        }
    }

    // pass 2: vertical 8-tap filter over each of the 8 columns, with rounding
    for (c = 0; c < 8; c++) {
        int q0 = buf[0 * 8 + c], q1 = buf[1 * 8 + c], q2 = buf[2 * 8 + c], q3 = buf[3 * 8 + c];
        int q4 = buf[4 * 8 + c], q5 = buf[5 * 8 + c], q6 = buf[6 * 8 + c], q7 = buf[7 * 8 + c];
        if ((q0 | q1 | q2 | q3 | q4 | q5 | q6 | q7) != 0) {
            int P  = ((q7 * 0x31f1) >> 16) + ((q1 * 0xfb15) >> 16);
            int Q  = ((q1 * 0x31f1) >> 16) - ((q7 * 0xfb15) >> 16);
            int T  = ((q3 * 0xd4db) >> 16) + ((q5 * 0x8e3a) >> 16);
            int S  = ((q5 * 0xd4db) >> 16) - ((q3 * 0x8e3a) >> 16);
            int Z  = ((q0 + q4) * 0xb505) >> 16;
            int AA = ((q0 - q4) * 0xb505) >> 16;
            int AC = ((q6 * 0x61f8) >> 16) + ((q2 * 0xec83) >> 16);
            int AB = ((q2 * 0x61f8) >> 16) - ((q6 * 0xec83) >> 16);
            int AF = ((Q - S) * 0xb505) >> 16;
            int AI = ((P - T) * 0xb505) >> 16;

            int TP  = T + P;
            int SQ  = S + Q;
            int ACZ = AC + Z + 8;
            int AIA = AI + AA + 8;
            int ZAC = Z - AC + 8;
            int AAI = AA - AI + 8;
            int ABF = AB + AF;
            int AFB = AF - AB;

            dst[0 * 8 + c] = (short)((ACZ + TP) >> 4);
            dst[7 * 8 + c] = (short)((ACZ - TP) >> 4);
            dst[1 * 8 + c] = (short)((ABF + AIA) >> 4);
            dst[2 * 8 + c] = (short)((AIA - ABF) >> 4);
            dst[3 * 8 + c] = (short)((ZAC + SQ) >> 4);
            dst[4 * 8 + c] = (short)((ZAC - SQ) >> 4);
            dst[5 * 8 + c] = (short)((AAI + AFB) >> 4);
            dst[6 * 8 + c] = (short)((AAI - AFB) >> 4);
        } else {
            for (r = 0; r < 8; r++)
                dst[r * 8 + c] = 0;
        }
    }
}

// @ 0x00fd56c0
void FUN_00fd56c0(const short* x, const short* y, int* dst)
{
    memset(dst, 0, 0x100);
    dst[0]  = (int)x[0] * (int)y[0];
    dst[1]  = (int)x[1] * (int)y[1];
    dst[8]  = (int)x[2] * (int)y[2];
    dst[16] = (int)x[3] * (int)y[3];
    dst[9]  = (int)x[4] * (int)y[4];
    dst[2]  = (int)x[5] * (int)y[5];
    dst[3]  = (int)x[6] * (int)y[6];
    dst[10] = (int)x[7] * (int)y[7];
    dst[17] = (int)x[8] * (int)y[8];
    dst[24] = (int)x[9] * (int)y[9];
}

// @ 0x00fd5770
void FUN_00fd5770(const short* p1, const short* p2, short* dst)
{
    int buf[64];
    int b, c, r;

    FUN_00fd56c0(p2, p1, buf);

    // pass 1: expand each of the 4 populated rows from 4 taps to 8 outputs
    for (b = 0; b < 4; b++) {
        int* p = buf + b * 8;
        int x0 = p[0], x1 = p[1], x2 = p[2], x3 = p[3];
        if ((x0 | x1 | x2 | x3) != 0) {
            int A = -((x3 * 0x8e3a) >> 16);
            int B = (x1 * 0xfb15) >> 16;
            int C = (x3 * 0xd4db) >> 16;
            int E = C + B;
            int F = (x1 * 0x31f1) >> 16;
            int D = B - C;
            int G = F - A;
            int H = (D * 0xb505) >> 16;
            int I = A + F;
            int J = (x0 * 0xb505) >> 16;
            int K = (x2 * 0x61f8) >> 16;
            int M = (G * 0xb505) >> 16;
            int N = (x2 * 0xec83) >> 16;
            int L = H + J;
            int O = J - N;
            int P = N + J;
            int Q = J - H;
            int R = M + K;
            int S = M - K;
            int T = E + P;
            int U = P - E;

            p[0] = (short)T;
            p[1] = (short)(L + R);
            p[2] = (short)(L - R);
            p[3] = (short)(I + O);
            p[4] = (short)(O - I);
            p[5] = (short)(Q + S);
            p[6] = (short)(Q - S);
            p[7] = (short)U;
        }
    }

    // pass 2: vertical 4-tap filter, 8 outputs per column, with rounding
    for (c = 0; c < 8; c++) {
        int x0 = buf[24 + c], x1 = buf[c], x2 = buf[16 + c], x3 = buf[8 + c];
        if ((x0 | x1 | x2 | x3) != 0) {
            int a3 = (x3 * 0x31f1) >> 16;
            int b1 = (x1 * 0xb505) >> 16;
            int c3 = (x3 * 0xfb15) >> 16;
            int d0 = -((x0 * 0x8e3a) >> 16);
            int e0 = (x0 * 0xd4db) >> 16;
            int F = c3 - e0;
            int G = e0 + c3;
            int H = a3 - d0;
            int I = d0 + a3;
            int J = (H * 0xb505) >> 16;
            int N = (F * 0xb505) >> 16;
            int K = (x2 * 0x61f8) >> 16;
            int M = (x2 * 0xec83) >> 16;
            int O = b1;

            dst[0 * 8 + c] = (short)((M + O + 8 + G) >> 4);
            dst[1 * 8 + c] = (short)((N + O + 8 + K + J) >> 4);
            dst[2 * 8 + c] = (short)((N + O + 8 - (K + J)) >> 4);
            dst[3 * 8 + c] = (short)((O - M + 8 + I) >> 4);
            dst[4 * 8 + c] = (short)((O - M + 8 - I) >> 4);
            dst[5 * 8 + c] = (short)((O - N + 8 + (J - K)) >> 4);
            dst[6 * 8 + c] = (short)((O - N + 8 - (J - K)) >> 4);
            dst[7 * 8 + c] = (short)((M + O + 8 - G) >> 4);
        } else {
            for (r = 0; r < 8; r++)
                dst[r * 8 + c] = 0;
        }
    }
}

// @ 0x00fd5d50
void FUN_00fd5d50(const short* a, const short* b, unsigned* dst)
{
    int v = ((int)a[0] * (int)b[0] + 15) >> 5;
    unsigned short s = (unsigned short)v;
    __stosd(dst, (unsigned)s | ((unsigned)s << 16), 0x20);
}

// =================================================================== context

// @ 0x00fd5d90
__declspec(noinline) void FUN_00fd5d90(Vp6Ctx* p)
{
    if (p->raw0 != 0) FUN_00fd47b0(p->raw0);
    if (p->raw2 != 0) FUN_00fd47b0(p->raw2);
    if (p->raw1 != 0) FUN_00fd47b0(p->raw1);
    p->raw0 = 0;
    p->raw2 = 0;
    p->raw1 = 0;
    p->buf0 = 0;
    p->buf2 = 0;
    p->buf1 = 0;
}

// @ 0x00fd5e00
int FUN_00fd5e00(Vp6Ctx* p)
{
    FUN_00fd5d90(p);
    p->raw0 = (u8*)FUN_00fd47a0(0xa0, 0);
    if (p->raw0 == 0) {
        FUN_00fd5d90(p);
        return 0;
    }
    p->buf0 = (u8*)(((unsigned)p->raw0 + 0x1f) & 0xffffffe0);
    p->raw2 = (u8*)FUN_00fd47a0(0xa0, 0);
    if (p->raw2 == 0) {
        FUN_00fd5d90(p);
        return 0;
    }
    p->buf2 = (u8*)(((unsigned)p->raw2 + 0x1f) & 0xffffffe0);
    p->raw1 = (u8*)FUN_00fd47a0(0xa0, 0);
    if (p->raw1 == 0) {
        FUN_00fd5d90(p);
        return 0;
    }
    p->buf1 = (u8*)(((unsigned)p->raw1 + 0x1f) & 0xffffffe0);
    return 1;
}

// @ 0x00fd5e90
void FUN_00fd5e90(Vp6Ctx** pp)
{
    if (*pp != 0) {
        FUN_00fd5d90(*pp);
        vp6_scan_destroy(&(*pp)->scan);
        FUN_00fd6090((void**)&(*pp)->geom);
    }
    FUN_00fd47b0(*pp);
    *pp = 0;
}

// @ 0x00fd5ee0
Vp6Ctx* FUN_00fd5ee0(void)
{
    Vp6Ctx* p = (Vp6Ctx*)FUN_00fd47a0(0x3b64, 0);
    if (p != 0) {
        memset(p, 0, 0x3b64);
        p->width = 0;
        p->height = 0;
        p->f158 = 0;
        p->f15c = 0;
        p->f160 = 0;
        if (FUN_00fd5e00(p) != 0) {
            p->f16c = 0;
            p->f164 = 0;
            p->filterTab = p_vp6_filter_;
            p->f39a2 = 0;
            p->f39a6 = 0;
            p->f39aa = 0;
            p->f39ae = 0;
            p->f39b2 = 0;
            p->f39b6 = 0;
            memset(p->f39b8, 0, 0x18c);
            return p;
        }
        FUN_00fd47b0(p);
    }
    return 0;
}

// @ 0x00fd5fa0
void FUN_00fd5fa0(void)
{
    g_vp6_mode = FUN_00fd03b0();
    FUN_00fd03c0();
    FUN_00fd6cc0();
}

// @ 0x00fd5fc0
void FUN_00fd5fc0(int* out, const unsigned* dims)
{
    out[3] = dims[0] >> 3;
    out[4] = dims[1] >> 3;

    unsigned a = dims[2];
    out[5] = a;
    unsigned b = dims[3];
    out[6] = b;

    unsigned q = (a - 8 * out[3]) >> 1;
    out[0] = (a + 1) * q;
    out[7] = q;

    unsigned r = q >> 1;
    out[1] = (dims[1] + 2 * q) * a + (b + 1) * r;
    out[2] = r * b + (dims[1] + 2 * q) * a + r + ((dims[1] >> 1) + q) * b;
}

// @ 0x00fd6050
void* FUN_00fd6050(const unsigned* dims)
{
    int* p = (int*)FUN_00fd47a0(0x20, 0);
    if (p != 0) {
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[4] = 0;
        p[5] = 0;
        p[6] = 0;
        p[7] = 0;
        FUN_00fd5fc0(p, dims);
    }
    return p;
}

// @ 0x00fd6090
__declspec(noinline) void FUN_00fd6090(void** p)
{
    if (*p != 0) {
        FUN_00fd47b0(*p);
        *p = 0;
    }
}

// @ 0x00fd60b0
void FUN_00fd60b0(ScanBufs* p)
{
    int i;
    p->f0c = DAT_014930f0;
    for (i = 0; i < 0x40; i++)
        p->edges[DAT_01492ff0[i]] = (u8)i;
}

// @ 0x00fd60e0
void FUN_00fd60e0(ScanBufs* p)
{
    u8* e = p->edges + 2;
    u8* e2;
    int i;

    i = 0x15;
    do {
        p->buf0[e[-1]] = (u16)(DAT_01492cf0[p->frameType].w[0] * 4);
        p->buf0[e[0]]  = (u16)(DAT_01492cf0[p->frameType].w[0] * 4);
        p->buf0[e[1]]  = (u16)(DAT_01492cf0[p->frameType].w[0] * 4);
        e += 3;
    } while (--i);

    p->buf0[0] = (u16)(DAT_01492ef0[p->frameType] * 4);

    e2 = p->edges + 2;
    i = 0x15;
    do {
        p->buf1[e2[-1]] = (u16)(DAT_01492df0[p->frameType].w[0] * 4);
        p->buf1[e2[0]]  = (u16)(DAT_01492df0[p->frameType].w[0] * 4);
        p->buf1[e2[1]]  = (u16)(DAT_01492df0[p->frameType].w[0] * 4);
        e2 += 3;
    } while (--i);

    p->buf1[0] = (u16)(DAT_01492f70[p->frameType] * 4);
}

// @ 0x00fd61f0
void FUN_00fd61f0(ScanBufs* p)
{
    if (DAT_01492cf0[p->frameType].d != p->f08) {
        p->f08 = p->f04;
        g_vp6ExpandFn(p);
        FUN_00fd60e0(p);
    }
}
