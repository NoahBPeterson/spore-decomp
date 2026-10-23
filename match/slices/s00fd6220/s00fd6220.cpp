// s00fd6220 -- VP6 video decoder slice (BurnoutDecomp lib_b5rw / vp6.obj)
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include <string.h>

extern "C" void* __cdecl memset(void*, int, unsigned int);   // IAT thunk 0x011e073e
#pragma function(memset)

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;

// ---------------------------------------------------------------- externals
extern "C" void* FUN_00fd47a0(unsigned size, int align);   // 0x00fd47a0
extern "C" void  FUN_00fd47b0(void* p);                    // 0x00fd47b0
extern "C" void  FUN_00fd0390(void* out);                  // 0x00fd0390
extern "C" void  FUN_00fd4520(void* p, int x);             // 0x00fd4520
extern "C" int   FUN_00fd4780(void* p);                    // 0x00fd4780
extern "C" int   FUN_00fd6050(void* p);                    // 0x00fd6050
extern "C" void  FUN_00fd2a30(int a, int b);               // 0x00fd2a30
extern "C" int   FUN_00fd4ad0(void* p);                    // 0x00fd4ad0
extern "C" void  FUN_00fd5e90(void** pp);                  // 0x00fd5e90
extern "C" void  FUN_00fd6090(void* p);                    // 0x00fd6090
extern "C" void  FUN_00fd3c10(void* p);                    // 0x00fd3c10
extern "C" void  FUN_00fd47c0(void* p);                    // 0x00fd47c0
extern "C" void  FUN_00fd49b0(void* p);                    // 0x00fd49b0
extern "C" void* FUN_00fd5ee0(void);                       // 0x00fd5ee0
extern "C" void  vp6_bitreader_init(int* br, const u8* src); // 0x00fd29d0

extern "C" void (*g_vp6_emms)(void);      // 0x016d9418
extern "C" int   g_vp6_mode;              // 0x016d940c
extern "C" int   g_vp6_scratch[72];       // 0x016d9420
extern "C" int   g_vp6_filter[0x41][2];   // 0x015b3bb8
extern "C" int   g_vp6_deq[];             // 0x01493860 ({int mul; int add;} x 5 per band)

// ---------------------------------------------------------------- types
struct ScanBufs {
    int            pad00[20];   // 0x00..0x4f
    u8*            buf0;        // 0x50
    u8*            buf1;        // 0x54
    u8*            raw0;        // 0x58
    u8*            raw1;        // 0x5c
};

struct Vp6Ctx {
    u8   pad0000[0xf4];
    ScanBufs* scan;             // 0x0f4
    u8*  frame;                 // 0x0f8
    u8   b0fc[0x124 - 0x0fc];   // 0x0fc
    int  br[6];                 // 0x124
    int  f13c;                  // 0x13c
    int  f140;                  // 0x140
    int  f144;                  // 0x144
    int  f148;                  // 0x148
    int  f14c;                  // 0x14c
    int  f150;                  // 0x150
    int  f154;                  // 0x154
    int  f158;                  // 0x158
    int  f15c;                  // 0x15c
    u8   pad0160[0x168 - 0x160];
    int  f168;                  // 0x168
    u8   pad016c[0x194 - 0x16c];
    int  f194;                  // 0x194
    int  f198;                  // 0x198
    int  f19c;                  // 0x19c
    u8   pad01a0[0x1bc - 0x1a0];
    int  f1bc;                  // 0x1bc
    int  f1c0;                  // 0x1c0
    int  f1c4;                  // 0x1c4
    int  f1c8;                  // 0x1c8
    u8   pad01cc[0x32c - 0x1cc];
    int  f32c;                  // 0x32c
    u8   pad0330[0x238c - 0x330];
    int  f238c;                 // 0x238c
    u8   pad2390[0x39a3 - 0x2390];
    u8   f39a3[0x3b45 - 0x39a3];// 0x39a3
    u8   f3b45[0x3b62 - 0x3b45];// 0x3b45
    u8   f3b62;                 // 0x3b62
};

#define EX1(SRC, DST) \
    { s16 v = SRC; int x; if (v < 0) x = 0; else if (v > 0xff) x = 0xff; else x = v; DST = (u8)x; }
#define EXPAND8(SRC, DST) \
    EX1(SRC[0], DST[0]) EX1(SRC[1], DST[1]) EX1(SRC[2], DST[2]) EX1(SRC[3], DST[3]) \
    EX1(SRC[4], DST[4]) EX1(SRC[5], DST[5]) EX1(SRC[6], DST[6]) EX1(SRC[7], DST[7])

// @ 0x00fd6220
static __declspec(noinline) int vp6_scan_init(ScanBufs* p)
{
    if (p->raw0 != 0) FUN_00fd47b0(p->raw0);
    p->raw0 = 0;
    p->buf0 = 0;
    if (p->raw1 != 0) FUN_00fd47b0(p->raw1);
    p->raw1 = 0;
    p->buf1 = 0;
    p->raw0 = (u8*)FUN_00fd47a0(0xa0, 0);
    if (p->raw0 == 0) goto fail;
    p->buf0 = (u8*)(((unsigned)p->raw0 + 0x1f) & 0xffffffe0);
    p->raw1 = (u8*)FUN_00fd47a0(0xa0, 0);
    if (p->raw1 == 0) {
        if (p->raw0 != 0) FUN_00fd47b0(p->raw0);
        goto fail;
    }
    p->buf1 = (u8*)(((unsigned)p->raw1 + 0x1f) & 0xffffffe0);
    return 1;
fail:
    p->raw0 = 0;
    p->buf0 = 0;
    if (p->raw1 != 0) FUN_00fd47b0(p->raw1);
    p->raw1 = 0;
    p->buf1 = 0;
    return 0;
}

// @ 0x00fd62d0
extern "C" void vp6_scan_destroy(ScanBufs** pp)
{
    ScanBufs* p = *pp;
    if (p != 0) {
        if (p->raw0 != 0) FUN_00fd47b0(p->raw0);
        p->raw0 = 0;
        p->buf0 = 0;
        if (p->raw1 != 0) FUN_00fd47b0(p->raw1);
        p->raw1 = 0;
        p->buf1 = 0;
        FUN_00fd47b0(*pp);
        *pp = 0;
    }
}

// @ 0x00fd6320
extern "C" __declspec(noinline) ScanBufs* vp6_scan_create(void)
{
    ScanBufs* q = (ScanBufs*)FUN_00fd47a0(0x60, 0);
    if (q == 0) return 0;
    memset(q, 0, 0x60);
    if (!vp6_scan_init(q))
        vp6_scan_destroy(&q);
    return q;
}

// @ 0x00fd6370
extern "C" void vp6_expand(u8* dst, s16* src, int dstStride, int srcStride)
{
    for (int i = 0; i < 8; i++) {
        EXPAND8(src, dst)
        src += srcStride;
        dst += dstStride;
    }
}

// @ 0x00fd64b0
extern "C" void vp6_fill_row(s16* buf, u8* dst, s16* src, int stride)
{
    s16* d = buf;
    for (int i = 0; i < 8; i++) {
        d[0] = (s16)(src[0] + 0x80);
        d[1] = (s16)(src[1] + 0x80);
        d[2] = (s16)(src[2] + 0x80);
        d[3] = (s16)(src[3] + 0x80);
        d[4] = (s16)(src[4] + 0x80);
        d[5] = (s16)(src[5] + 0x80);
        d[6] = (s16)(src[6] + 0x80);
        d[7] = (s16)(src[7] + 0x80);
        d += 8;
        src += 8;
    }
    vp6_expand(dst, buf, stride, 8);
}

// @ 0x00fd6550
#define A8(B) \
    p[B-2] = (s16)((u16)src[0] + (u16)pred[B+0]); \
    p[B-1] = (s16)((u16)src[1] + (u16)pred[B+1]); \
    p[B+0] = (s16)((u16)src[2] + (u16)pred[B+2]); \
    p[B+1] = (s16)((u16)src[3] + (u16)pred[B+3]); \
    p[B+2] = (s16)((u16)src[4] + (u16)pred[B+4]); \
    p[B+3] = (s16)((u16)src[5] + (u16)pred[B+5]); \
    p[B+4] = (s16)((u16)src[6] + (u16)pred[B+6]); \
    p[B+5] = (s16)((u16)src[7] + (u16)pred[B+7]);

extern "C" void vp6_add_pred(s16* buf, u8* dst, u8* src, s16* pred, int stride)
{
    s16* p = buf + 2;
    int n = 2;
    do {
        A8(0)
        src += stride;
        A8(8)
        src += stride;
        A8(16)
        src += stride;
        A8(24)
        src += stride;
        pred += 32;
        p += 32;
    } while (--n);
    vp6_expand(dst, buf, stride, 8);
}

// @ 0x00fd6740
#define ADD32(A) \
    (A)[0] += pred[0];   (A)[1] += pred[1];   (A)[2] += pred[2];   (A)[3] += pred[3]; \
    (A)[4] += pred[4];   (A)[5] += pred[5];   (A)[6] += pred[6];   (A)[7] += pred[7]; \
    (A)[8] += pred[8];   (A)[9] += pred[9];   (A)[10] += pred[10]; (A)[11] += pred[11]; \
    (A)[12] += pred[12]; (A)[13] += pred[13]; (A)[14] += pred[14]; (A)[15] += pred[15]; \
    (A)[16] += pred[16]; (A)[17] += pred[17]; (A)[18] += pred[18]; (A)[19] += pred[19]; \
    (A)[20] += pred[20]; (A)[21] += pred[21]; (A)[22] += pred[22]; (A)[23] += pred[23]; \
    (A)[24] += pred[24]; (A)[25] += pred[25]; (A)[26] += pred[26]; (A)[27] += pred[27]; \
    (A)[28] += pred[28]; (A)[29] += pred[29]; (A)[30] += pred[30]; (A)[31] += pred[31];

extern "C" void vp6_add_rows(s16* acc, s16* pred, u8* dst, int stride)
{
    s16* save = acc;
    int n = 2;
    do {
        ADD32(acc)
        acc += 32;
        pred += 32;
    } while (--n);
    vp6_expand(dst, save, stride, 8);
}

// @ 0x00fd6880
#define DQ(J, OFF) \
    { int v = (s[J-1] * *(int*)((u8*)g_vp6_deq + i + OFF) + 0x80) >> 8; \
      v += *(int*)((u8*)g_vp6_deq + i + OFF + 4); \
      if (v > 0xff) v = 0xff; else if (v < 1) v = 1; \
      d[J-1] = (u8)v; }

extern "C" void vp6_dequant_rows(Vp6Ctx* ctx)
{
    u8* d;
    u8* s;
    int r;
    g_vp6_emms();
    d = (u8*)((int)ctx + 0x3b45);
    s = (u8*)((int)ctx + 0x39a3);
    r = 2;
    do {
        unsigned i;
        for (i = 0; i < 0x18; i += 8) {
            DQ(0, 0x00)
            DQ(1, 0x18)
            DQ(2, 0x30)
            DQ(3, 0x48)
            DQ(4, 0x60)
            d += 5;
        }
        s += 0xb;
    } while (--r);
}

// @ 0x00fd69c0
extern "C" int vp6_ctx_create(Vp6Ctx** pp, int a, int b)
{
    *pp = (Vp6Ctx*)FUN_00fd5ee0();
    (*pp)->f150 = a;
    (*pp)->f154 = b;
    (*pp)->f148 = FUN_00fd6050(&(*pp)->f150);
    (*pp)->scan = vp6_scan_create();
    (*pp)->f168 = g_vp6_mode;
    if (FUN_00fd4ad0(*pp) == 0) {
        FUN_00fd5e90((void**)pp);
        return 0;
    }
    *(int*)((u8*)(*pp)->scan + 8) = 0;
    return 1;
}

// @ 0x00fd6a50
extern "C" void vp6_frame_info(Vp6Ctx* ctx, int* out)
{
    out[0] = ctx->f150;
    out[1] = ctx->f154;
    out[2] = ctx->f158;
    out[3] = (int)((unsigned)ctx->f150 >> 1);
    out[4] = (int)((unsigned)ctx->f154 >> 1);
    out[5] = ctx->f15c;
    out[6] = (ctx->f158 + 1) * 0x30 + ctx->f1c4 + ctx->f194;
    out[7] = ctx->f198 + (ctx->f15c + 1) * 0x18 + ctx->f1c4;
    out[8] = ctx->f19c + (ctx->f15c + 1) * 0x18 + ctx->f1c4;
    out[9] = ctx->f1c4 + ctx->f194;
    g_vp6_emms();
}

// @ 0x00fd6b00
static __declspec(noinline) int vp6_decode_row(Vp6Ctx* ctx, int off)
{
    int local;
    FUN_00fd0390(&local);
    FUN_00fd4520(&ctx->b0fc[0], off);
    if (FUN_00fd4780(ctx) == 0) return -1;
    if (ctx->f238c != 0) {
        ctx->f13c = 0;
        ctx->f140 = 0;
        ctx->f144 = (int)(ctx->frame + off);
    } else {
        vp6_bitreader_init(ctx->br, ctx->frame + off);
    }
    FUN_00fd3c10(ctx);
    int prev = ctx->f1c4;
    ctx->f1c4 = ctx->f1bc;
    ctx->f1bc = ctx->f1c8 ? ctx->f1c8 : prev;
    ctx->f1c8 = 0;
    FUN_00fd2a30(ctx->f148, ctx->f1c4);
    if (ctx->f3b62 == 0 || ctx->f32c != 0) {
        ctx->f1c8 = ctx->f1c0;
        ctx->f1c0 = ctx->f1c4;
    }
    g_vp6_emms();
    return 0;
}

// stand-in caller (original call site 0x00fd6bf0 lies outside this slice)
extern "C" int vp6_decode_row_caller(Vp6Ctx* ctx, int off)
{
    return vp6_decode_row(ctx, off);
}

// @ 0x00fd6c10
extern "C" int vp6_ctx_destroy(Vp6Ctx** pp)
{
    if (*pp != 0) {
        vp6_scan_destroy(&(*pp)->scan);
        FUN_00fd6090(&(*pp)->f148);
        FUN_00fd47c0(*pp);
        FUN_00fd49b0(*pp);
        FUN_00fd5e90((void**)pp);
    }
    return 1;
}

// @ 0x00fd6c60
extern "C" void vp6_widen(u8* src, u16* dst, int stride)
{
    int i = 8;
    do {
        dst[0] = (u16)src[0];
        dst[1] = (u16)src[1];
        dst[2] = (u16)src[2];
        dst[3] = (u16)src[3];
        dst[4] = (u16)src[4];
        dst[5] = (u16)src[5];
        dst[6] = (u16)src[6];
        dst[7] = (u16)src[7];
        src += stride;
        dst += 8;
    } while (--i);
}

// @ 0x00fd6cd0
extern "C" void vp6_filter_block(u8* src, s16* dst, int stride, int* f1, int* f2)
{
    int r;
    int* t = g_vp6_scratch + 2;
    for (r = 9; r != 0; --r) {
        t[-2] = (src[1] * f1[1] + src[0] * f1[0] + 0x40) >> 7;
        t[-1] = (src[2] * f1[1] + src[1] * f1[0] + 0x40) >> 7;
        t[ 0] = (src[3] * f1[1] + src[2] * f1[0] + 0x40) >> 7;
        t[ 1] = (src[3] * f1[0] + src[4] * f1[1] + 0x40) >> 7;
        t[ 2] = (src[5] * f1[1] + src[4] * f1[0] + 0x40) >> 7;
        t[ 3] = (src[5] * f1[0] + src[6] * f1[1] + 0x40) >> 7;
        t[ 4] = (src[6] * f1[0] + src[7] * f1[1] + 0x40) >> 7;
        t[ 5] = (src[7] * f1[0] + src[8] * f1[1] + 0x40) >> 7;
        src += stride;
        t += 8;
    }
    {
        int* q = g_vp6_scratch;
        s16* dp = dst + 2;
        for (r = 8; r != 0; --r) {
            dp[-2] = (s16)((q[ 0] * f2[0] + q[ 8] * f2[1] + 0x40) >> 7);
            dp[-1] = (s16)((q[ 1] * f2[0] + q[ 9] * f2[1] + 0x40) >> 7);
            dp[ 0] = (s16)((q[ 2] * f2[0] + q[10] * f2[1] + 0x40) >> 7);
            dp[ 1] = (s16)((q[ 3] * f2[0] + q[11] * f2[1] + 0x40) >> 7);
            dp[ 2] = (s16)((q[ 4] * f2[0] + q[12] * f2[1] + 0x40) >> 7);
            dp[ 3] = (s16)((q[ 5] * f2[0] + q[13] * f2[1] + 0x40) >> 7);
            dp[ 4] = (s16)((q[ 6] * f2[0] + q[14] * f2[1] + 0x40) >> 7);
            dp[ 5] = (s16)((q[ 7] * f2[0] + q[15] * f2[1] + 0x40) >> 7);
            q += 8;
            dp += 8;
        }
    }
}

// @ 0x00fd6ed0
extern "C" void vp6_filter_row(u8* p1, u8* p2, s16* dst, int stride, int fA, int fB)
{
    int diff = (int)p2 - (int)p1;
    if (diff < 0) {
        diff = (int)p1 - (int)p2;
        p1 = p2;
    }
    if (diff == 1) {
        int i = 8;
        do {
            dst[0] = (s16)((p1[0] * g_vp6_filter[fA][0] + p1[1] * g_vp6_filter[fA][1] + 0x40) >> 7);
            dst[1] = (s16)((p1[1] * g_vp6_filter[fA][0] + p1[2] * g_vp6_filter[fA][1] + 0x40) >> 7);
            dst[2] = (s16)((p1[2] * g_vp6_filter[fA][0] + p1[3] * g_vp6_filter[fA][1] + 0x40) >> 7);
            dst[3] = (s16)((p1[3] * g_vp6_filter[fA][0] + p1[4] * g_vp6_filter[fA][1] + 0x40) >> 7);
            dst[4] = (s16)((p1[4] * g_vp6_filter[fA][0] + p1[5] * g_vp6_filter[fA][1] + 0x40) >> 7);
            dst[5] = (s16)((p1[5] * g_vp6_filter[fA][0] + p1[6] * g_vp6_filter[fA][1] + 0x40) >> 7);
            dst[6] = (s16)((p1[6] * g_vp6_filter[fA][0] + p1[7] * g_vp6_filter[fA][1] + 0x40) >> 7);
            dst[7] = (s16)((p1[7] * g_vp6_filter[fA][0] + p1[8] * g_vp6_filter[fA][1] + 0x40) >> 7);
            p1 += stride;
            dst += 8;
        } while (--i);
        return;
    }
    if (diff == stride) {
        int i = 8;
        do {
            dst[0] = (s16)((p1[stride] * g_vp6_filter[fB][1] + p1[0] * g_vp6_filter[fB][0] + 0x40) >> 7);
            dst[1] = (s16)((p1[stride+1] * g_vp6_filter[fB][1] + p1[1] * g_vp6_filter[fB][0] + 0x40) >> 7);
            dst[2] = (s16)((p1[stride+2] * g_vp6_filter[fB][1] + p1[2] * g_vp6_filter[fB][0] + 0x40) >> 7);
            dst[3] = (s16)((p1[stride+3] * g_vp6_filter[fB][1] + p1[3] * g_vp6_filter[fB][0] + 0x40) >> 7);
            dst[4] = (s16)((p1[stride+4] * g_vp6_filter[fB][1] + p1[4] * g_vp6_filter[fB][0] + 0x40) >> 7);
            dst[5] = (s16)((p1[stride+5] * g_vp6_filter[fB][1] + p1[5] * g_vp6_filter[fB][0] + 0x40) >> 7);
            dst[6] = (s16)((p1[stride+6] * g_vp6_filter[fB][1] + p1[6] * g_vp6_filter[fB][0] + 0x40) >> 7);
            dst[7] = (s16)((p1[stride+7] * g_vp6_filter[fB][1] + p1[7] * g_vp6_filter[fB][0] + 0x40) >> 7);
            p1 += stride;
            dst += 8;
        } while (--i);
        return;
    }
    if (diff == stride - 1) p1--;
    else if (diff != stride + 1) return;
    vp6_filter_block(p1, dst, stride, &g_vp6_filter[fA][0], &g_vp6_filter[fB][0]);
}
