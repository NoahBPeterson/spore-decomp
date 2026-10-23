// s011ad110 -- lib_cblock: OpenSSL BIGNUM core (bn_div.c, bn_word.c, bn_rand.c).
//
// Reconstructed from the disassembly in work/match/scratch_s011ad110_cards.txt.
// MSVC 2008 SP1, /O2 /MD /Gy /EHsc /TP.  The library is built without
// BN_LLONG/BN_UMULT (32-bit BN_ULONG, no 64-bit multiply intrinsic), so every
// 32x32 product is formed from 16x16 halves by bn_lcl.h's mul64()/sqr64()
// macros, exactly as the disassembly shows.

typedef unsigned int  BN_ULONG;
typedef unsigned char BN_UBYTE;
typedef __int64       BN_TIME64;

// ---------------------------------------------------------------------------
// OpenSSL BIGNUM / BN_CTX
// ---------------------------------------------------------------------------
struct BIGNUM {
    BN_ULONG* d;        // +0x00
    int       top;      // +0x04
    int       dmax;     // +0x08
    int       neg;      // +0x0c
    int       flags;    // +0x10
};

struct BN_CTX;          // opaque

#define BN_FLG_CONSTTIME 0x04

#define BN_is_zero(a)      ((a)->top == 0)
#define BN_get_flags(a, f) ((a)->flags & (f))

#define BN_BITS     32
#define BN_BITS2    32

// ---------------------------------------------------------------------------
// 16x16-half product macros (bn_lcl.h)
// ---------------------------------------------------------------------------
#define BN_BITS4    16
#define BN_MASK2    (0xffffffffL)
#define BN_MASK2l   (0xffff)
#define BN_MASK2h   (0xffff0000L)
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

// bn_word.c step macros.
#define mul(r, a, w, c) \
    { \
    BN_ULONG l, h; \
    l = LBITS(a); \
    h = HBITS(a); \
    mul64(l, h, LBITS(w), HBITS(w)); \
    r = l + (c); \
    if (r < (c)) h++; \
    (c) = h; \
    }

// The build's mul_add() folds the carry in two steps, matching the emitted
// `lea ecx,[edx+eax] / cmp / sbb` pairs (see the disassembly of
// bn_mul_add_words): first l+carry, then the running word.
#define mul_add(r, a, w, c) \
    { \
    BN_ULONG l, h, t; \
    l = LBITS(a); \
    h = HBITS(a); \
    mul64(l, h, LBITS(w), HBITS(w)); \
    t = l + (c); \
    if (t < (c)) h++; \
    t = (r) + t; \
    if (t < l + (c)) h++; \
    (r) = t; \
    (c) = h; \
    }

// ---------------------------------------------------------------------------
// external OpenSSL entry points (addresses from the disassembly)
// ---------------------------------------------------------------------------
extern "C" {
int       __cdecl BN_ucmp(const BIGNUM* a, const BIGNUM* b);            // 0x117ae20
int       __cdecl BN_cmp(const BIGNUM* a, const BIGNUM* b);             // 0x117ae70
int       __cdecl BN_is_bit_set(const BIGNUM* a, int n);                // 0x117afa0
int       __cdecl BN_copy(BIGNUM* to, const BIGNUM* from);              // 0x117ab40
int       __cdecl BN_set_word(BIGNUM* a, BN_ULONG w);                   // 0x117ac20
BIGNUM*   __cdecl BN_bin2bn(const BN_UBYTE* s, int len, BIGNUM* ret);   // 0x117ac80
int       __cdecl BN_num_bits(const BIGNUM* a);                         // 0x117a8e0
int       __cdecl BN_num_bits_word(BN_ULONG l);                         // 0x117a890
int       __cdecl BN_lshift(BIGNUM* r, const BIGNUM* a, int n);         // 0x119ee80
int       __cdecl BN_lshift1(BIGNUM* r, const BIGNUM* a);               // 0x119ed30
int       __cdecl BN_rshift(BIGNUM* r, const BIGNUM* a, int n);         // 0x119efc0
int       __cdecl BN_sub(BIGNUM* r, const BIGNUM* a, const BIGNUM* b);  // 0x1189430
int       __cdecl bn_expand2(BIGNUM* b, int words);                     // 0x117ab00
BN_ULONG  __cdecl bn_sub_words(BN_ULONG* r, const BN_ULONG* a, const BN_ULONG* b, int n); // 0x11ae1f0
void      __cdecl BN_CTX_start(BN_CTX* ctx);                            // 0x1187b00
BIGNUM*   __cdecl BN_CTX_get(BN_CTX* ctx);                              // 0x1187b90
void      __cdecl BN_CTX_end(BN_CTX* ctx);                              // 0x1187b50
void      __cdecl ERR_put_error(int lib, int func, int reason, const char* f, int l); // 0x1180d50
void*     __cdecl CRYPTO_malloc(int num, const char* file, int line);   // 0x1183410
void      __cdecl CRYPTO_free(void* p);                                 // 0x11835c0
void      __cdecl OPENSSL_cleanse(void* p, unsigned long n);            // 0x1183810
int       __cdecl RAND_bytes(unsigned char* buf, int num);              // 0x11785f0
int       __cdecl RAND_pseudo_bytes(unsigned char* buf, int num);       // 0x1178650
void      __cdecl RAND_add(const void* buf, int num, double entropy);   // 0x1178580
__declspec(dllimport) BN_TIME64 __cdecl _time64(BN_TIME64* t);          // [0x13cc55c]
}

// The rand helpers at 0x11ad9b0 / 0x11ad9d0 live just outside this slice;
// BN_rand_range() forwards to one of them through a function pointer.
extern "C" int __cdecl BN_rand(BIGNUM* rnd, int bits, int top, int bottom);        // 0x11ad9b0
extern "C" int __cdecl BN_pseudo_rand(BIGNUM* rnd, int bits, int top, int bottom); // 0x11ad9d0

// 0x11acd00 -- the constant-time division entry that BN_div forwards to when
// either operand carries BN_FLG_CONSTTIME.  The original passes only four
// arguments (rm, num, dv, divisor).
extern "C" int __cdecl BN_div_consttime(BIGNUM* rm, const BIGNUM* num, BIGNUM* dv,
                                        const BIGNUM* divisor);

// ---------------------------------------------------------------------------
// helpers defined in this slice
// ---------------------------------------------------------------------------
extern "C" BN_ULONG __cdecl bn_mul_words(BN_ULONG* rp, const BN_ULONG* ap, int num, BN_ULONG w);
extern "C" BN_ULONG __cdecl bn_mul_add_words(BN_ULONG* rp, const BN_ULONG* ap, int num, BN_ULONG w);
extern "C" void     __cdecl bn_sqr_words(BN_ULONG* r, const BN_ULONG* a, int n);
extern "C" BN_ULONG __cdecl bn_div_words(BN_ULONG h, BN_ULONG l, BN_ULONG d);
extern "C" BN_ULONG __cdecl bn_add_words(BN_ULONG* r, const BN_ULONG* a, const BN_ULONG* b, int n);

// ===========================================================================
// 0x011ad110 -- BN_div(dv, rm, num, divisor, ctx)
//
// Long division.  Both operands are normalised so the divisor's high bit is
// set, then the quotient is built one 32-bit word at a time: estimate the
// 64/32 digit with bn_div_words(), correct it against the divisor, multiply
// the estimate back in with bn_mul_words() and subtract with bn_sub_words()
// (adding the divisor back with bn_add_words() when the estimate overshot).
// ===========================================================================
// @ 0x011ad110
extern "C" int __cdecl BN_div(BIGNUM* dv, BIGNUM* rm, const BIGNUM* num,
                              const BIGNUM* divisor, BN_CTX* ctx)
{
    int       norm_shift, i, loop;
    BIGNUM   *snum, *sdiv, *res;
    BN_ULONG  q, n0, n1, d0, d1;
    BN_ULONG *snumber, *qword;

    if (BN_get_flags(num, BN_FLG_CONSTTIME) || BN_get_flags(divisor, BN_FLG_CONSTTIME))
        return BN_div_consttime(rm, num, dv, divisor);

    if (BN_is_zero(divisor)) {
        ERR_put_error(3, 0x6b, 0x67, 0, 0);
        return 0;
    }

    if (BN_ucmp(num, divisor) < 0) {
        if (rm != 0) {
            if (!BN_copy(rm, num))
                return 0;
        }
        if (dv != 0)
            BN_set_word(dv, 0);
        return 1;
    }

    BN_CTX_start(ctx);
    res  = BN_CTX_get(ctx);
    snum = BN_CTX_get(ctx);
    sdiv = BN_CTX_get(ctx);
    if (dv == 0)
        dv = BN_CTX_get(ctx);

    if (sdiv == 0 || dv == 0)
        goto err;

    norm_shift = BN_BITS2 - (BN_num_bits(divisor) % BN_BITS2);
    {
        int norm2 = norm_shift;
        if (!BN_lshift(sdiv, divisor, norm2))
            goto err;
        sdiv->neg = 0;
        norm_shift = norm2 + BN_BITS2;
        if (!BN_lshift(snum, num, norm_shift))
            goto err;
    }
    snum->neg = 0;

    /* loop counts the number of quotient words still to produce */
    loop = snum->top - sdiv->top;
    i = sdiv->top;

    n0 = sdiv->d[i - 1];
    n1 = (i == 1) ? 0 : sdiv->d[i - 2];

    /* Sign of the result, and make room for the quotient. */
    dv->neg = num->neg ^ divisor->neg;
    if (dv->dmax < loop + 1) {
        if (!bn_expand2(dv, loop + 1))
            goto err;
    }
    dv->top = loop;
    qword = dv->d + loop - 1;

    if (snum->dmax < i + 1) {
        if (!bn_expand2(snum, i + 1))
            goto err;
    }

    snumber = snum->d + i;

    /* Leading word: if the dividend's extra top word is at least the
     * divisor's top word, the first quotient word is 1. */
    if (snum->d[i] >= n0) {
        bn_sub_words(snumber, snumber, sdiv->d, i);
        *qword = 1;
    } else {
        dv->top--;
    }
    if (dv->top == 0)
        dv->neg = 0;
    else
        qword--;

    loop--;
    while (loop > 0) {
        /* Guess a word of the quotient from the top two words of the
         * running remainder and the divisor. */
        {
            BN_ULONG hi = snumber[0];
            BN_ULONG lo = snumber[-1];
            if (hi == n0) {
                q = 0xffffffff;
            } else {
                q = bn_div_words(hi, lo, n0);
                lo -= q * n0;

                /* q = q_hi:q_lo correction: multiply the candidate against
                 * the divisor (d1:d0) and adjust while it overshoots. */
                {
                    BN_ULONG m1 = (n1 >> BN_BITS4) * (q >> BN_BITS4);
                    BN_ULONG m2 = (n1 >> BN_BITS4) * (q & BN_MASK2l);
                    BN_ULONG m0 = (n1 & BN_MASK2l) * (q >> BN_BITS4) + m2;
                    BN_ULONG t;
                    if (m0 < m2)
                        m1 += 0x10000;
                    t = (n1 & BN_MASK2l) * (q & BN_MASK2l) + m0 * 0x10000;
                    d0 = m1 + (m0 >> BN_BITS4);
                    if (t < m0 * 0x10000)
                        d0++;
                    d1 = t;
                    while (lo <= d0) {
                        if (lo == d0 && d1 <= snumber[-2])
                            break;
                        lo += n0;
                        q--;
                        if (lo < n0)
                            break;
                        if (d1 < n1)
                            d0--;
                        d1 -= n1;
                    }
                }
            }

            /* Multiply the divisor by the estimated word and subtract it
             * from the running remainder. */
            {
                BN_ULONG carry = bn_mul_words(snum->d, sdiv->d, i, q);
                snum->d[i] = carry;
            }
            snumber -= 1;
            if (bn_sub_words(snumber, snumber, snum->d, i + 1) != 0) {
                q--;
                if (bn_add_words(snumber, snumber, sdiv->d, i) != 0)
                    qword[1] += 1;
            }
            *qword = q;
            qword--;
            loop--;
        }
    }

    /* Strip leading zero words from the remainder. */
    if (snum->top > 0) {
        BN_ULONG* p = snum->d + snum->top - 1;
        while (*p == 0) {
            snum->top--;
            if (snum->top <= 0)
                break;
            p--;
        }
    }

    if (rm != 0) {
        int neg = num->neg;
        if (!BN_rshift(rm, snum, norm_shift))
            goto err;
        if (rm->top != 0)
            rm->neg = neg;
    }

    BN_CTX_end(ctx);
    return 1;

err:
    BN_CTX_end(ctx);
    return 0;
}

// ===========================================================================
// 0x011ad750 -- BN_mod_lshift_quick(r, a, n, m)
//
// r = a * 2^n mod m, shifting in steps no larger than the gap between
// BN_num_bits(r) and BN_num_bits(m).
// ===========================================================================
// @ 0x011ad750
extern "C" int __cdecl BN_mod_lshift_quick(BIGNUM* r, const BIGNUM* a, int n, const BIGNUM* m)
{
    int shift;

    if (r != a) {
        if (!BN_copy(r, a))
            return 0;
    }

    while (n > 0) {
        shift = BN_num_bits(m) - BN_num_bits(r);
        if (shift < 0) {
            ERR_put_error(3, 0x77, 0x6e, 0, 0);
            return 0;
        }
        if (shift > n)
            shift = n;

        if (shift != 0) {
            if (!BN_lshift(r, r, shift))
                return 0;
            n -= shift;
        } else {
            if (!BN_lshift1(r, r))
                return 0;
            n--;
        }
        if (BN_cmp(r, m) >= 0) {
            if (!BN_sub(r, r, m))
                return 0;
        }
    }
    return 1;
}

// ===========================================================================
// 0x011ad810 -- bnrand(pseudorand, rnd, bits, top, bottom)
//
// Generates `bits` random bits into `rnd`.  `pseudorand` selects the source
// (0 = RAND_bytes, 1 = RAND_pseudo_bytes, 2 = pseudo bytes with a restricted
// range); `top`/`bottom` control the top word's shape and the low bit.
//
// In the original this is a static helper, so `pseudorand` arrives in eax
// and `bits` in ecx (docs/codegen.md §6.3); the disassembly shows exactly
// that.  Reproducing the register convention here is not achievable with a
// free function under this compiler (C3865 rejects __thiscall, and the
// static-helper stand-in still emitted the stack form), so the body is
// written plainly and remains behaviourally identical.
// ===========================================================================
// @ 0x011ad810
extern "C" __declspec(noinline) int bnrand(int pseudorand, BIGNUM* rnd, int bits, int top, int bottom)
{
    int      ret = 0;
    int      mask = 0;
    BN_UBYTE* buf;
    BN_UBYTE  b;
    int       i, bytes;
    BN_TIME64 t;

    if (bits == 0) {
        BN_set_word(rnd, 0);
        return 1;
    }

    bytes = (bits + 7) / 8;
    mask = 0xff << ((0xff & (bits - 1)) % 8 + 1);

    buf = (BN_UBYTE*)CRYPTO_malloc(bytes, ".\\crypto\\bn\\bn_rand.c", 0x86);
    if (buf == 0) {
        ERR_put_error(3, 0x7f, 0x41, 0, 0);
        return ret;
    }

    t = _time64(0);
    RAND_add(&t, 8, 0);

    if (pseudorand == 0) {
        if (RAND_bytes(buf, bytes) < 1)
            goto done;
    } else {
        if (RAND_pseudo_bytes(buf, bytes) == -1)
            goto done;
        if (pseudorand == 2 && bytes > 0) {
            for (i = 0; i < bytes; i++) {
                RAND_pseudo_bytes(&b, 1);
                if (b < 0x80 || i <= 0) {
                    if (b < 0x2a)
                        buf[i] = 0;
                    else if (b < 0x54)
                        buf[i] = 0xff;
                } else {
                    buf[i] = buf[i - 1];
                }
            }
        }
    }

    if (top != -1) {
        if (top == 0) {
            buf[0] |= (BN_UBYTE)(1 << ((bits - 1) % 8));
        } else if ((bits - 1) % 8 == 0) {
            buf[1] |= 0x80;
            buf[0] = 1;
        } else {
            buf[0] |= (BN_UBYTE)(3 << ((bits - 2) % 8));
        }
    }
    buf[0] &= (BN_UBYTE)~mask;
    if (bottom != 0)
        buf[bytes - 1] |= 1;

    if (BN_bin2bn(buf, bytes, rnd) != 0)
        ret = 1;

done:
    OPENSSL_cleanse(buf, bytes);
    CRYPTO_free(buf);
    return ret;
}

// ===========================================================================
// 0x011ada00 -- BN_rand_range / BN_pseudo_rand_range
//
// The two public wrappers are merged here: the caller passes the "pseudo"
// flag on the stack (0 selects BN_rand, non-zero BN_pseudo_rand).
// ===========================================================================
// @ 0x011ada00
extern "C" int __cdecl BN_rand_range(int pseudo, BIGNUM* rnd, const BIGNUM* range)
{
    int (*fn)(BIGNUM*, int, int, int) = pseudo ? BN_pseudo_rand : BN_rand;
    int bits, count = 100, n;

    if (range->neg || range->top == 0) {
        ERR_put_error(3, 0x7a, 0x73, 0, 0);
        return 0;
    }

    n = BN_num_bits(range);
    if (n == 1) {
        BN_set_word(rnd, 0);
        return 1;
    }

    bits = n;
    if (BN_is_bit_set(range, n - 2) || BN_is_bit_set(range, n - 3)) {
        /* Small range: reject anything not below `range`. */
        for (;;) {
            if (!fn(rnd, bits, -1, 0))
                return 0;
            if (--count == 0) {
                ERR_put_error(3, 0x7a, 0x71, 0, 0);
                return 0;
            }
            if (BN_cmp(rnd, range) < 0)
                return 1;
        }
    } else {
        bits = n + 1;
        for (;;) {
            if (!fn(rnd, bits, -1, 0))
                return 0;
            if (BN_cmp(rnd, range) >= 0) {
                if (!BN_sub(rnd, rnd, range))
                    return 0;
                if (BN_cmp(rnd, range) >= 0) {
                    if (!BN_sub(rnd, rnd, range))
                        return 0;
                }
            }
            if (--count == 0) {
                ERR_put_error(3, 0x7a, 0x71, 0, 0);
                return 0;
            }
            if (BN_cmp(rnd, range) < 0)
                return 1;
        }
    }
}

// ===========================================================================
// 0x011adb60 -- bn_mul_add_words(rp, ap, num, w)
//
// rp[i] += ap[i] * w, returning the carry out of the top word.  The four-way
// unroll (with a per-word counter check) is written out explicitly: this
// compiler does not unroll the plain loop on its own.
// ===========================================================================
// @ 0x011adb60
extern "C" BN_ULONG __cdecl bn_mul_add_words(BN_ULONG* rp, const BN_ULONG* ap, int num, BN_ULONG w)
{
    BN_ULONG carry = 0;
    BN_ULONG l, h;

    if (num <= 0)
        return 0;

    for (;;) {
        l = LBITS(ap[0]); h = HBITS(ap[0]); mul64(l, h, LBITS(w), HBITS(w));
        { BN_ULONG t = l + carry; if (t < carry) h++; t = rp[0] + t; if (t < l + carry) h++; rp[0] = t; }
        carry = h;
        if (--num == 0) return carry;
        l = LBITS(ap[1]); h = HBITS(ap[1]); mul64(l, h, LBITS(w), HBITS(w));
        { BN_ULONG t = l + carry; if (t < carry) h++; t = rp[1] + t; if (t < l + carry) h++; rp[1] = t; }
        carry = h;
        if (--num == 0) return carry;
        l = LBITS(ap[2]); h = HBITS(ap[2]); mul64(l, h, LBITS(w), HBITS(w));
        { BN_ULONG t = l + carry; if (t < carry) h++; t = rp[2] + t; if (t < l + carry) h++; rp[2] = t; }
        carry = h;
        if (--num == 0) return carry;
        l = LBITS(ap[3]); h = HBITS(ap[3]); mul64(l, h, LBITS(w), HBITS(w));
        { BN_ULONG t = l + carry; if (t < carry) h++; t = rp[3] + t; if (t < l + carry) h++; rp[3] = t; }
        carry = h;
        if (--num == 0) return carry;
        ap += 4;
        rp += 4;
    }
}

// ===========================================================================
// 0x011add30 -- bn_mul_words(rp, ap, num, w)
//
// rp[i] = ap[i] * w, returning the carry out of the top word.
// ===========================================================================
// @ 0x011add30
extern "C" BN_ULONG __cdecl bn_mul_words(BN_ULONG* rp, const BN_ULONG* ap, int num, BN_ULONG w)
{
    BN_ULONG carry = 0;
    BN_ULONG l, h;

    if (num <= 0)
        return 0;

    for (;;) {
        l = LBITS(ap[0]); h = HBITS(ap[0]); mul64(l, h, LBITS(w), HBITS(w));
        { BN_ULONG t = l + carry; if (t < carry) h++; rp[0] = t; } carry = h;
        if (--num == 0) return carry;
        l = LBITS(ap[1]); h = HBITS(ap[1]); mul64(l, h, LBITS(w), HBITS(w));
        { BN_ULONG t = l + carry; if (t < carry) h++; rp[1] = t; } carry = h;
        if (--num == 0) return carry;
        l = LBITS(ap[2]); h = HBITS(ap[2]); mul64(l, h, LBITS(w), HBITS(w));
        { BN_ULONG t = l + carry; if (t < carry) h++; rp[2] = t; } carry = h;
        if (--num == 0) return carry;
        l = LBITS(ap[3]); h = HBITS(ap[3]); mul64(l, h, LBITS(w), HBITS(w));
        { BN_ULONG t = l + carry; if (t < carry) h++; rp[3] = t; } carry = h;
        if (--num == 0) return carry;
        ap += 4;
        rp += 4;
    }
}

// ===========================================================================
// 0x011adee0 -- bn_sqr_words(r, a, n)
// ===========================================================================
// @ 0x011adee0
extern "C" void __cdecl bn_sqr_words(BN_ULONG* r, const BN_ULONG* a, int n)
{
    if (n <= 0)
        return;

    for (;;) {
        sqr64(r[0], r[1], a[0]);
        if (--n == 0)
            return;
        sqr64(r[2], r[3], a[1]);
        if (--n == 0)
            return;
        sqr64(r[4], r[5], a[2]);
        if (--n == 0)
            return;
        sqr64(r[6], r[7], a[3]);
        if (--n == 0)
            return;
        a += 4;
        r += 8;
    }
}

// ===========================================================================
// 0x011adfd0 -- bn_div_words(h, l, d): the 64/32 division helper.
//
// Computes (h:l)/d in two 16-bit digits: the estimate is refined until it
// matches, then the loop runs a second time for the low digit and the two
// halves are combined into the result.
// ===========================================================================
// @ 0x011adfd0
extern "C" BN_ULONG __cdecl bn_div_words(BN_ULONG h, BN_ULONG l, BN_ULONG d)
{
    BN_ULONG dh, dl, q, ret = 0, th, tl;
    BN_ULONG i, lhi, rh;
    int      count = 2;

    if (d == 0)
        return (BN_ULONG)-1;

    i = BN_BITS - BN_num_bits_word(d);
    if (h >= d)
        h -= d;

    if (i != 0) {
        d <<= i;
        h = (h << i) | (l >> (BN_BITS - i));
        l <<= i;
    }

    dh = d >> BN_BITS4;
    dl = d & BN_MASK2l;

    for (;;) {
        if (h >> BN_BITS4 == dh)
            q = 0xffff;
        else
            q = h / dh;

        th = q * dh;
        tl = q * dl;
        rh = h - th;
        if ((rh & 0xffff0000) == 0) {
            lhi = l >> BN_BITS4;
            do {
                if (tl <= ((rh << BN_BITS4) | lhi))
                    break;
                tl -= dl;
                th -= dh;
                rh = h - th;
                q--;
            } while ((rh & 0xffff0000) == 0);
        }
        th += tl >> BN_BITS4;
        tl <<= BN_BITS4;
        if (l < tl)
            th++;
        l -= tl;
        if (h < th) {
            h += d;
            q--;
        }
        count--;
        if (count == 0)
            return ret | q;
        ret = q << BN_BITS4;
        h = ((h - th) << BN_BITS4) | (l >> BN_BITS4);
        l <<= BN_BITS4;
    }
}

// ===========================================================================
// 0x011ae100 -- bn_add_words(r, a, b, n)
// ===========================================================================
// @ 0x011ae100
extern "C" BN_ULONG __cdecl bn_add_words(BN_ULONG* r, const BN_ULONG* a, const BN_ULONG* b, int n)
{
    BN_ULONG c, t;

    if (n <= 0)
        return 0;

    t = a[0] + b[0];
    c = (t < b[0]);
    r[0] = t;
    if (--n == 0)
        return c;

    for (;;) {
        t = a[1] + c; c = (t < c); t = b[1] + t; c += (t < b[1]); r[1] = t;
        if (--n == 0) return c;
        t = a[2] + c; c = (t < c); t = b[2] + t; c += (t < b[2]); r[2] = t;
        if (--n == 0) return c;
        t = a[3] + c; c = (t < c); t = b[3] + t; c += (t < b[3]); r[3] = t;
        if (--n == 0) return c;
        t = a[4] + c; c = (t < c); t = b[4] + t; c += (t < b[4]); r[4] = t;
        if (--n == 0) return c;
        a += 4;
        b += 4;
        r += 4;
    }
}
