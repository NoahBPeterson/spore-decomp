#include "types.h"

// Square of a 256-bit little-endian integer (8 x 32-bit words) into a 512-bit
// result (16 words): OpenSSL-style bn_sqr_comba8, built without BN_LLONG/BN_UMULT,
// so every 32x32 product is formed from 16x16-bit halves (mul64/sqr64 macros of
// bn_lcl.h) and accumulated column-wise into a three-word carry chain.
typedef unsigned long BN_ULONG;

#define BN_BITS4    16
#define BN_MASK2    (0xffffffffL)
#define BN_MASK2l   (0xffff)
#define BN_MASK2h1  (0xffff8000L)
#define BN_TBIT     (0x80000000L)

#define LBITS(a)    ((a) & BN_MASK2l)
#define HBITS(a)    (((a) >> BN_BITS4) & BN_MASK2l)
#define L2HBITS(a)  (((a) << BN_BITS4) & BN_MASK2)

#define mul64(l, h, bl, bh) \
    { \
    BN_ULONG m, m1, lt, ht; \
    lt = l; \
    ht = h; \
    m = (bh) * (lt); \
    lt = (bl) * (lt); \
    m1 = (bl) * (ht); \
    ht = (bh) * (ht); \
    m = (m + m1) & BN_MASK2; if (m < m1) ht += L2HBITS((BN_ULONG)1); \
    ht += HBITS(m); \
    m1 = L2HBITS(m); \
    lt = (lt + m1) & BN_MASK2; if (lt < m1) ht++; \
    (l) = lt; \
    (h) = ht; \
    }

#define sqr64(lo, ho, in) \
    { \
    BN_ULONG l, h, m; \
    h = (in); \
    l = LBITS(h); \
    h = HBITS(h); \
    m = (l) * (h); \
    l *= l; \
    h *= h; \
    h += (m & BN_MASK2h1) >> (BN_BITS4 - 1); \
    m = (m & BN_MASK2l) << (BN_BITS4 + 1); \
    l = (l + m) & BN_MASK2; if (l < m) h++; \
    (lo) = l; \
    (ho) = h; \
    }

#define mul_add_c2(a, b, c0, c1, c2) \
    t1 = LBITS(a); t2 = HBITS(a); \
    bl = LBITS(b); bh = HBITS(b); \
    mul64(t1, t2, bl, bh); \
    if (t2 & BN_TBIT) c2++; \
    t2 = (t2 + t2) & BN_MASK2; \
    if (t1 & BN_TBIT) t2++; \
    t1 = (t1 + t1) & BN_MASK2; \
    c0 = (c0 + t1) & BN_MASK2; \
    if ((c0 < t1) && (((++t2) & BN_MASK2) == 0)) c2++; \
    c1 = (c1 + t2) & BN_MASK2; if (c1 < t2) c2++;

#define sqr_add_c(a, i, c0, c1, c2) \
    sqr64(t1, t2, (a)[i]); \
    c0 = (c0 + t1) & BN_MASK2; if (c0 < t1) t2++; \
    c1 = (c1 + t2) & BN_MASK2; if (c1 < t2) c2++;

#define sqr_add_c2(a, i, j, c0, c1, c2) \
    mul_add_c2((a)[i], (a)[j], c0, c1, c2)

// @ 0x011b0500
void __cdecl lib_cblock_Square8(BN_ULONG* r, const BN_ULONG* a)
{
    BN_ULONG t1, t2;
    BN_ULONG bl, bh;
    BN_ULONG c1, c2, c3;

    c1 = 0;
    c2 = 0;
    c3 = 0;
    sqr_add_c(a, 0, c1, c2, c3);
    r[0] = c1;
    c1 = 0;
    sqr_add_c2(a, 1, 0, c2, c3, c1);
    r[1] = c2;
    c2 = 0;
    sqr_add_c(a, 1, c3, c1, c2);
    sqr_add_c2(a, 2, 0, c3, c1, c2);
    r[2] = c3;
    c3 = 0;
    sqr_add_c2(a, 3, 0, c1, c2, c3);
    sqr_add_c2(a, 2, 1, c1, c2, c3);
    r[3] = c1;
    c1 = 0;
    sqr_add_c(a, 2, c2, c3, c1);
    sqr_add_c2(a, 3, 1, c2, c3, c1);
    sqr_add_c2(a, 4, 0, c2, c3, c1);
    r[4] = c2;
    c2 = 0;
    sqr_add_c2(a, 5, 0, c3, c1, c2);
    sqr_add_c2(a, 4, 1, c3, c1, c2);
    sqr_add_c2(a, 3, 2, c3, c1, c2);
    r[5] = c3;
    c3 = 0;
    sqr_add_c(a, 3, c1, c2, c3);
    sqr_add_c2(a, 4, 2, c1, c2, c3);
    sqr_add_c2(a, 5, 1, c1, c2, c3);
    sqr_add_c2(a, 6, 0, c1, c2, c3);
    r[6] = c1;
    c1 = 0;
    sqr_add_c2(a, 7, 0, c2, c3, c1);
    sqr_add_c2(a, 6, 1, c2, c3, c1);
    sqr_add_c2(a, 5, 2, c2, c3, c1);
    sqr_add_c2(a, 4, 3, c2, c3, c1);
    r[7] = c2;
    c2 = 0;
    sqr_add_c(a, 4, c3, c1, c2);
    sqr_add_c2(a, 5, 3, c3, c1, c2);
    sqr_add_c2(a, 6, 2, c3, c1, c2);
    sqr_add_c2(a, 7, 1, c3, c1, c2);
    r[8] = c3;
    c3 = 0;
    sqr_add_c2(a, 7, 2, c1, c2, c3);
    sqr_add_c2(a, 6, 3, c1, c2, c3);
    sqr_add_c2(a, 5, 4, c1, c2, c3);
    r[9] = c1;
    c1 = 0;
    sqr_add_c(a, 5, c2, c3, c1);
    sqr_add_c2(a, 6, 4, c2, c3, c1);
    sqr_add_c2(a, 7, 3, c2, c3, c1);
    r[10] = c2;
    c2 = 0;
    sqr_add_c2(a, 7, 4, c3, c1, c2);
    sqr_add_c2(a, 6, 5, c3, c1, c2);
    r[11] = c3;
    c3 = 0;
    sqr_add_c(a, 6, c1, c2, c3);
    sqr_add_c2(a, 7, 5, c1, c2, c3);
    r[12] = c1;
    c1 = 0;
    sqr_add_c2(a, 7, 6, c2, c3, c1);
    r[13] = c2;
    c2 = 0;
    sqr_add_c(a, 7, c3, c1, c2);
    r[14] = c3;
    r[15] = c1;
}
