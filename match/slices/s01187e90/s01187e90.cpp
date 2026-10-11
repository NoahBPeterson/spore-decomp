// Slice s01187e90 -- OpenSSL 0.9.8g BIGNUM inverse (bn_gcd.c / bn_add.c) and
// BIO print integer/float formatters (bio/b_print.c), linked into SporeApp.exe
// (lib_openssl / lib_cblock).
//
// Module flags: /O2 /MD /Gy /TP  (the original openssl objects were /TC but the
// codegen is identical; BN_LLONG is undefined so BN_ULONG is 32-bit unsigned long,
// and HAVE_LONG_LONG is off so fmtint's LLONG is a 32-bit long, LDOUBLE a double).
// See manifest.txt / nonmatching.txt / partial.txt.
#include "types.h"
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <ctype.h>
#include <limits.h>

// ------------------------------------------------------------------ BIGNUM
typedef unsigned long BN_ULONG;

struct BIGNUM {
    BN_ULONG *d;
    int top;
    int dmax;
    int neg;
    int flags;
};
typedef struct bn_ctx_st BN_CTX;

#define BN_FLG_MALLOCED    0x01
#define BN_FLG_STATIC_DATA 0x02
#define BN_FLG_CONSTTIME   0x04
#define BN_MASK2           (0xffffffffL)

#define BN_with_flags(dest, b, n) ((dest)->d = (b)->d, (dest)->top = (b)->top, \
                                   (dest)->dmax = (b)->dmax, (dest)->neg = (b)->neg, \
                                   (dest)->flags = (((dest)->flags & BN_FLG_MALLOCED) | \
                                                    ((b)->flags & ~BN_FLG_MALLOCED) | \
                                                    BN_FLG_STATIC_DATA | (n)))

#define BN_get_flags(b, n) ((b)->flags & (n))
#define BN_is_zero(a)      ((a)->top == 0)
#define BN_abs_is_word(a, w) \
    ((((a)->top == 1) && ((a)->d[0] == (BN_ULONG)(w))) || (((w) == 0) && ((a)->top == 0)))
#define BN_is_one(a)       (BN_abs_is_word((a), 1) && !(a)->neg)
#define BN_is_word(a, w)   (BN_abs_is_word((a), (w)) && (!(w) || !(a)->neg))
#define BN_is_odd(a)       (((a)->top > 0) && ((a)->d[0] & 1))
#define BN_one(a)          (BN_set_word((a), 1))
#define BN_zero(a)         (BN_set_word((a), 0))
#define bn_check_top(a)
#define bn_wexpand(a, words) (((words) <= (a)->dmax) ? (a) : bn_expand2((a), (words)))

// ---- OpenSSL callees (all __cdecl) ----------------------------------------
extern "C" void    __cdecl ERR_put_error(int lib, int func, int reason, int file, int line); // 0x1180d50
extern "C" void    __cdecl BN_CTX_start(BN_CTX *ctx);                                       // 0x1187b00
extern "C" BIGNUM *__cdecl BN_CTX_get(BN_CTX *ctx);                                         // 0x1187b90
extern "C" void    __cdecl BN_CTX_end(BN_CTX *ctx);                                         // 0x1187b50
extern "C" BIGNUM *__cdecl BN_new(void);                                                    // 0x117a9d0
extern "C" void    __cdecl BN_free(BIGNUM *a);                                              // 0x117a970
extern "C" int     __cdecl BN_set_word(BIGNUM *a, BN_ULONG w);                              // 0x117ac20
extern "C" int     __cdecl BN_copy(BIGNUM *to, const BIGNUM *from);                         // 0x117ab40
extern "C" int     __cdecl BN_ucmp(const BIGNUM *a, const BIGNUM *b);                       // 0x117ae20
extern "C" int     __cdecl BN_uadd(BIGNUM *r, const BIGNUM *a, const BIGNUM *b);            // 0x1189220
extern "C" int     __cdecl BN_usub(BIGNUM *r, const BIGNUM *a, const BIGNUM *b);            // 0x11892f0
extern "C" int     __cdecl BN_nnmod(BIGNUM *r, const BIGNUM *m, const BIGNUM *d, BN_CTX *ctx); // 0x11ad520
extern "C" int     __cdecl BN_num_bits(const BIGNUM *a);                                    // 0x117a8e0
extern "C" int     __cdecl BN_is_bit_set(const BIGNUM *a, int n);                           // 0x117afa0
extern "C" int     __cdecl BN_rshift1(BIGNUM *r, BIGNUM *a);
extern "C" int     __cdecl BN_rshift(BIGNUM *r, BIGNUM *a, int n);
extern "C" int     __cdecl BN_lshift1(BIGNUM *r, BIGNUM *a);
extern "C" int     __cdecl BN_lshift(BIGNUM *r, const BIGNUM *a, int n);
extern "C" int     __cdecl BN_add(BIGNUM *r, const BIGNUM *a, const BIGNUM *b);
extern "C" int     __cdecl BN_sub(BIGNUM *r, const BIGNUM *a, const BIGNUM *b);
extern "C" int     __cdecl BN_mul(BIGNUM *r, const BIGNUM *a, const BIGNUM *b, BN_CTX *ctx);
extern "C" int     __cdecl BN_mul_word(BIGNUM *a, BN_ULONG w);
extern "C" int     __cdecl BN_div(BIGNUM *dv, BIGNUM *rem, const BIGNUM *m, const BIGNUM *d, BN_CTX *ctx);
static BIGNUM *BN_mod_inverse_no_branch(BIGNUM *in, const BIGNUM *a, const BIGNUM *n, BN_CTX *ctx); // 0x1187be0
extern "C" BIGNUM *__cdecl bn_expand2(BIGNUM *b, int words);                                // 0x117ab00

// ---------------------------------------------------------------------------
// @ 0x01187e90  BN_mod_inverse (bn_gcd.c)
// ---------------------------------------------------------------------------
extern "C" BIGNUM *__cdecl BN_mod_inverse(BIGNUM *in, const BIGNUM *a, const BIGNUM *n, BN_CTX *ctx)
{
    BIGNUM *A, *B, *X, *Y, *M, *D, *T, *R = 0;
    BIGNUM *ret = 0;
    int sign;

    if ((BN_get_flags(a, BN_FLG_CONSTTIME) != 0) ||
        (BN_get_flags(n, BN_FLG_CONSTTIME) != 0)) {
        return BN_mod_inverse_no_branch(in, a, n, ctx);
    }

    BN_CTX_start(ctx);
    A = BN_CTX_get(ctx);
    B = BN_CTX_get(ctx);
    X = BN_CTX_get(ctx);
    D = BN_CTX_get(ctx);
    M = BN_CTX_get(ctx);
    Y = BN_CTX_get(ctx);
    T = BN_CTX_get(ctx);
    if (T == 0) goto err;

    if (in == 0)
        R = BN_new();
    else
        R = in;
    if (R == 0) goto err;

    BN_one(X);
    BN_zero(Y);
    if (BN_copy(B, a) == 0) goto err;
    if (BN_copy(A, n) == 0) goto err;
    A->neg = 0;
    if (B->neg || (BN_ucmp(B, A) >= 0)) {
        if (!BN_nnmod(B, B, A, ctx)) goto err;
    }
    sign = -1;

    if (BN_is_odd(n) && (BN_num_bits(n) <= 2048)) {
        int shift;

        while (!BN_is_zero(B)) {
            shift = 0;
            while (!BN_is_bit_set(B, shift)) {
                shift++;
                if (BN_is_odd(X)) {
                    if (!BN_uadd(X, X, n)) goto err;
                }
                if (!BN_rshift1(X, X)) goto err;
            }
            if (shift > 0) {
                if (!BN_rshift(B, B, shift)) goto err;
            }

            shift = 0;
            while (!BN_is_bit_set(A, shift)) {
                shift++;
                if (BN_is_odd(Y)) {
                    if (!BN_uadd(Y, Y, n)) goto err;
                }
                if (!BN_rshift1(Y, Y)) goto err;
            }
            if (shift > 0) {
                if (!BN_rshift(A, A, shift)) goto err;
            }

            if (BN_ucmp(B, A) >= 0) {
                if (!BN_uadd(X, X, Y)) goto err;
                if (!BN_usub(B, B, A)) goto err;
            } else {
                if (!BN_uadd(Y, Y, X)) goto err;
                if (!BN_usub(A, A, B)) goto err;
            }
        }
    } else {
        while (!BN_is_zero(B)) {
            BIGNUM *tmp;

            if (BN_num_bits(A) == BN_num_bits(B)) {
                if (!BN_one(D)) goto err;
                if (!BN_sub(M, A, B)) goto err;
            } else if (BN_num_bits(A) == BN_num_bits(B) + 1) {
                if (!BN_lshift1(T, B)) goto err;
                if (BN_ucmp(A, T) < 0) {
                    if (!BN_one(D)) goto err;
                    if (!BN_sub(M, A, B)) goto err;
                } else {
                    if (!BN_sub(M, A, T)) goto err;
                    if (!BN_add(D, T, B)) goto err;
                    if (BN_ucmp(A, D) < 0) {
                        if (!BN_set_word(D, 2)) goto err;
                    } else {
                        if (!BN_set_word(D, 3)) goto err;
                        if (!BN_sub(M, M, B)) goto err;
                    }
                }
            } else {
                if (!BN_div(D, M, A, B, ctx)) goto err;
            }

            tmp = A;
            A = B;
            B = M;

            if (BN_is_one(D)) {
                if (!BN_add(tmp, X, Y)) goto err;
            } else {
                if (BN_is_word(D, 2)) {
                    if (!BN_lshift1(tmp, X)) goto err;
                } else if (BN_is_word(D, 4)) {
                    if (!BN_lshift(tmp, X, 2)) goto err;
                } else if (D->top == 1) {
                    if (!BN_copy(tmp, X)) goto err;
                    if (!BN_mul_word(tmp, D->d[0])) goto err;
                } else {
                    if (!BN_mul(tmp, D, X, ctx)) goto err;
                }
                if (!BN_add(tmp, tmp, Y)) goto err;
            }

            M = Y;
            Y = X;
            X = tmp;
            sign = -sign;
        }
    }

    if (sign < 0) {
        if (!BN_sub(Y, n, Y)) goto err;
    }

    if (BN_is_one(A)) {
        if (!Y->neg && BN_ucmp(Y, n) < 0) {
            if (!BN_copy(R, Y)) goto err;
        } else {
            if (!BN_nnmod(R, Y, n, ctx)) goto err;
        }
    } else {
        ERR_put_error(3, 0x6e, 0x6c, 0, 0);
        goto err;
    }
    ret = R;
err:
    if ((ret == 0) && (in == 0)) BN_free(R);
    BN_CTX_end(ctx);
    return ret;
}

// static helper of bn_gcd.c: BN_mod_inverse_no_branch.  Kept here as a static
// function so that cl applies the same per-TU register calling convention to the
// call inside BN_mod_inverse as the original translation unit did.
static BIGNUM *BN_mod_inverse_no_branch(BIGNUM *in, const BIGNUM *a, const BIGNUM *n, BN_CTX *ctx)
{
    BIGNUM *A, *B, *X, *Y, *M, *D, *T, *R = 0;
    BIGNUM local_A, local_B;
    BIGNUM *pA, *pB;
    BIGNUM *ret = 0;
    int sign;

    BN_CTX_start(ctx);
    A = BN_CTX_get(ctx);
    B = BN_CTX_get(ctx);
    X = BN_CTX_get(ctx);
    D = BN_CTX_get(ctx);
    M = BN_CTX_get(ctx);
    Y = BN_CTX_get(ctx);
    T = BN_CTX_get(ctx);
    if (T == 0) goto err;

    if (in == 0)
        R = BN_new();
    else
        R = in;
    if (R == 0) goto err;

    BN_one(X);
    BN_zero(Y);
    if (BN_copy(B, a) == 0) goto err;
    if (BN_copy(A, n) == 0) goto err;
    A->neg = 0;

    if (B->neg || (BN_ucmp(B, A) >= 0)) {
        pB = &local_B;
        BN_with_flags(pB, B, BN_FLG_CONSTTIME);
        if (!BN_nnmod(B, pB, A, ctx)) goto err;
    }
    sign = -1;

    while (!BN_is_zero(B)) {
        BIGNUM *tmp;

        pA = &local_A;
        BN_with_flags(pA, A, BN_FLG_CONSTTIME);

        if (!BN_div(D, M, pA, B, ctx)) goto err;

        tmp = A;
        A = B;
        B = M;

        if (!BN_mul(tmp, D, X, ctx)) goto err;
        if (!BN_add(tmp, tmp, Y)) goto err;

        M = Y;
        Y = X;
        X = tmp;
        sign = -sign;
    }

    if (sign < 0) {
        if (!BN_sub(Y, n, Y)) goto err;
    }

    if (BN_is_one(A)) {
        if (!Y->neg && BN_ucmp(Y, n) < 0) {
            if (!BN_copy(R, Y)) goto err;
        } else {
            if (!BN_nnmod(R, Y, n, ctx)) goto err;
        }
    } else {
        ERR_put_error(3, 0x68, 0x6c, 0, 0);   /* BN_F_BN_MOD_INVERSE_NO_BRANCH, BN_R_NO_INVERSE */
        goto err;
    }
    ret = R;
err:
    if ((ret == 0) && (in == 0)) BN_free(R);
    BN_CTX_end(ctx);
    return ret;
}

// ---------------------------------------------------------------------------
// @ 0x011892f0  BN_usub (bn_add.c)
// ---------------------------------------------------------------------------
extern "C" int __cdecl BN_usub(BIGNUM *r, const BIGNUM *a, const BIGNUM *b)
{
    int max, min, dif;
    BN_ULONG t1, t2, *ap, *bp, *rp;
    int i, carry;

    max = a->top;
    min = b->top;
    dif = max - min;

    if (dif < 0) {
        ERR_put_error(3, 0x73, 0x64, 0, 0);
        return 0;
    }

    if (bn_wexpand(r, max) == 0)
        return 0;

    ap = a->d;
    bp = b->d;
    rp = r->d;

    carry = 0;
    for (i = min; i != 0; i--) {
        t1 = *(ap++);
        t2 = *(bp++);
        if (carry) {
            carry = (t1 <= t2);
            t1 = (t1 - t2 - 1) & BN_MASK2;
        } else {
            carry = (t1 < t2);
            t1 = (t1 - t2) & BN_MASK2;
        }
        *(rp++) = t1 & BN_MASK2;
    }
    if (carry) {
        if (!dif)
            return 0;
        while (dif) {
            dif--;
            t1 = *(ap++);
            t2 = (t1 - 1) & BN_MASK2;
            *(rp++) = t2;
            if (t1)
                break;
        }
    }
    if (rp != ap) {
        for (;;) {
            if (!dif--) break;
            rp[0] = ap[0];
            if (!dif--) break;
            rp[1] = ap[1];
            if (!dif--) break;
            rp[2] = ap[2];
            if (!dif--) break;
            rp[3] = ap[3];
            rp += 4;
            ap += 4;
        }
    }

    r->top = max;
    r->neg = 0;
    {
        BN_ULONG *ftl;
        if (r->top > 0) {
            for (ftl = &r->d[r->top - 1]; r->top > 0; r->top--)
                if (*(ftl--)) break;
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// bio/b_print.c formatters
// ---------------------------------------------------------------------------
#include <string.h>

#define LLONG   long            // HAVE_LONG_LONG is off
typedef double LDOUBLE;         // HAVE_LONG_DOUBLE is off

#define DP_S_DEFAULT    0
#define DP_S_FLAGS      1
#define DP_S_MIN        2
#define DP_S_DOT        3
#define DP_S_MAX        4
#define DP_S_MOD        5
#define DP_S_CONV       6
#define DP_S_DONE       7

#define DP_F_MINUS      (1 << 0)
#define DP_F_PLUS       (1 << 1)
#define DP_F_SPACE      (1 << 2)
#define DP_F_NUM        (1 << 3)
#define DP_F_ZERO       (1 << 4)
#define DP_F_UP         (1 << 5)
#define DP_F_UNSIGNED   (1 << 6)

#define DP_C_SHORT      1
#define DP_C_LONG       2
#define DP_C_LDOUBLE    3
#define DP_C_LLONG      4

#define char_to_int(p)  (p - '0')
#define OSSL_MAX(p, q)  ((p >= q) ? p : q)
#define DECIMAL_SIZE(type) ((sizeof(type) * 8 + 2) / 3 + 1)

typedef unsigned int size_t_;
struct bio_st;
typedef struct bio_st BIO;

void *__cdecl OPENSSL_malloc(int num);
void *__cdecl OPENSSL_realloc(void *p, int num);
int   __cdecl BIO_write(BIO *b, const void *data, int dlen);

// doapr_outch and fmtstr are the static helpers from the same b_print.c
// translation unit.  They are included so cl reproduces the per-TU register
// calling conventions of fmtint/fmtfp (same for _dopr below, the only caller).
static void doapr_outch(char **sbuffer, char **buffer, size_t_ *currlen,
                        size_t_ *maxlen, int c)                       // 0x1189660
{
    assert(*sbuffer != NULL || buffer != NULL);

    if (buffer) {
        while (*currlen >= *maxlen) {
            if (*buffer == NULL) {
                if (*maxlen == 0)
                    *maxlen = 1024;
                *buffer = (char *)OPENSSL_malloc(*maxlen);
                if (*currlen > 0) {
                    assert(*sbuffer != NULL);
                    memcpy(*buffer, *sbuffer, *currlen);
                }
                *sbuffer = NULL;
            } else {
                *maxlen += 1024;
                *buffer = (char *)OPENSSL_realloc(*buffer, *maxlen);
            }
        }
        assert(*sbuffer != NULL || *buffer != NULL);
    }

    if (*currlen < *maxlen) {
        if (*sbuffer)
            (*sbuffer)[(*currlen)++] = (char)c;
        else
            (*buffer)[(*currlen)++] = (char)c;
    }
    return;
}

static void fmtstr(char **sbuffer, char **buffer, size_t_ *currlen,
                   size_t_ *maxlen, const char *value, int flags, int min,
                   int max)                                          // 0x1189700
{
    int padlen, strln;
    int cnt = 0;

    if (value == 0)
        value = "<NULL>";
    for (strln = 0; value[strln]; ++strln)
        ;
    padlen = min - strln;
    if (padlen < 0)
        padlen = 0;
    if (flags & DP_F_MINUS)
        padlen = -padlen;

    while ((padlen > 0) && (cnt < max)) {
        doapr_outch(sbuffer, buffer, currlen, maxlen, ' ');
        --padlen;
        ++cnt;
    }
    while (*value && (cnt < max)) {
        doapr_outch(sbuffer, buffer, currlen, maxlen, *value++);
        ++cnt;
    }
    while ((padlen < 0) && (cnt < max)) {
        doapr_outch(sbuffer, buffer, currlen, maxlen, ' ');
        ++padlen;
        ++cnt;
    }
}

// @ 0x011897e0  fmtint
static void fmtint(char **sbuffer, char **buffer, size_t_ *currlen,
                   size_t_ *maxlen, LLONG value, int base, int min,
                   int max, int flags)
{
    int signvalue = 0;
    const char *prefix = "";
    unsigned LLONG uvalue;
    char convert[DECIMAL_SIZE(value) + 3];
    int place = 0;
    int spadlen = 0;
    int zpadlen = 0;
    int caps = 0;

    if (max < 0)
        max = 0;
    uvalue = value;
    if (!(flags & DP_F_UNSIGNED)) {
        if (value < 0) {
            signvalue = '-';
            uvalue = -value;
        } else if (flags & DP_F_PLUS)
            signvalue = '+';
        else if (flags & DP_F_SPACE)
            signvalue = ' ';
    }
    if (flags & DP_F_NUM) {
        if (base == 8) prefix = "0";
        if (base == 16) prefix = "0x";
    }
    if (flags & DP_F_UP)
        caps = 1;
    do {
        convert[place++] =
            (caps ? "0123456789ABCDEF" : "0123456789abcdef")
            [uvalue % (unsigned)base];
        uvalue = (uvalue / (unsigned)base);
    } while (uvalue && (place < (int)sizeof(convert)));
    if (place == sizeof(convert))
        place--;
    convert[place] = 0;

    zpadlen = max - place;
    spadlen = min - OSSL_MAX(max, place) - (signvalue ? 1 : 0) - strlen(prefix);
    if (zpadlen < 0)
        zpadlen = 0;
    if (spadlen < 0)
        spadlen = 0;
    if (flags & DP_F_ZERO) {
        zpadlen = OSSL_MAX(zpadlen, spadlen);
        spadlen = 0;
    }
    if (flags & DP_F_MINUS)
        spadlen = -spadlen;

    while (spadlen > 0) {
        doapr_outch(sbuffer, buffer, currlen, maxlen, ' ');
        --spadlen;
    }

    if (signvalue)
        doapr_outch(sbuffer, buffer, currlen, maxlen, signvalue);

    while (*prefix) {
        doapr_outch(sbuffer, buffer, currlen, maxlen, *prefix);
        prefix++;
    }

    if (zpadlen > 0) {
        while (zpadlen > 0) {
            doapr_outch(sbuffer, buffer, currlen, maxlen, '0');
            --zpadlen;
        }
    }
    while (place > 0)
        doapr_outch(sbuffer, buffer, currlen, maxlen, convert[--place]);

    while (spadlen < 0) {
        doapr_outch(sbuffer, buffer, currlen, maxlen, ' ');
        ++spadlen;
    }
}

// @ 0x01189a30  fmtfp
static LDOUBLE abs_val(LDOUBLE value)
{
    LDOUBLE result = value;
    if (value < 0)
        result = -value;
    return result;
}

static LDOUBLE pow_10(int in_exp)
{
    LDOUBLE result = 1;
    while (in_exp) {
        result *= 10;
        in_exp--;
    }
    return result;
}

static long roundv(LDOUBLE value)
{
    long intpart;
    intpart = (long)value;
    value = value - intpart;
    if (value >= 0.5)
        intpart++;
    return intpart;
}

static void fmtfp(char **sbuffer, char **buffer, size_t_ *currlen,
                  size_t_ *maxlen, LDOUBLE fvalue, int min, int max,
                  int flags)
{
    int signvalue = 0;
    LDOUBLE ufvalue;
    char iconvert[20];
    char fconvert[20];
    int iplace = 0;
    int fplace = 0;
    int padlen = 0;
    int zpadlen = 0;
    int caps = 0;
    long intpart;
    long fracpart;
    long max10;

    if (max < 0)
        max = 6;
    ufvalue = abs_val(fvalue);
    if (fvalue < 0)
        signvalue = '-';
    else if (flags & DP_F_PLUS)
        signvalue = '+';
    else if (flags & DP_F_SPACE)
        signvalue = ' ';

    intpart = (long)ufvalue;

    if (max > 9)
        max = 9;

    max10 = roundv(pow_10(max));
    fracpart = roundv(pow_10(max) * (ufvalue - intpart));

    if (fracpart >= max10) {
        intpart++;
        fracpart -= max10;
    }

    do {
        iconvert[iplace++] =
            (caps ? "0123456789ABCDEF" : "0123456789abcdef")[intpart % 10];
        intpart = (intpart / 10);
    } while (intpart && (iplace < (int)sizeof(iconvert)));
    if (iplace == sizeof iconvert)
        iplace--;
    iconvert[iplace] = 0;

    do {
        fconvert[fplace++] =
            (caps ? "0123456789ABCDEF" : "0123456789abcdef")[fracpart % 10];
        fracpart = (fracpart / 10);
    } while (fplace < max);
    if (fplace == sizeof fconvert)
        fplace--;
    fconvert[fplace] = 0;

    padlen = min - iplace - max - 1 - ((signvalue) ? 1 : 0);
    zpadlen = max - fplace;
    if (zpadlen < 0)
        zpadlen = 0;
    if (padlen < 0)
        padlen = 0;
    if (flags & DP_F_MINUS)
        padlen = -padlen;

    if ((flags & DP_F_ZERO) && (padlen > 0)) {
        if (signvalue) {
            doapr_outch(sbuffer, buffer, currlen, maxlen, signvalue);
            --padlen;
            signvalue = 0;
        }
        while (padlen > 0) {
            doapr_outch(sbuffer, buffer, currlen, maxlen, '0');
            --padlen;
        }
    }
    while (padlen > 0) {
        doapr_outch(sbuffer, buffer, currlen, maxlen, ' ');
        --padlen;
    }
    if (signvalue)
        doapr_outch(sbuffer, buffer, currlen, maxlen, signvalue);

    while (iplace > 0)
        doapr_outch(sbuffer, buffer, currlen, maxlen, iconvert[--iplace]);

    if (max > 0 || (flags & DP_F_NUM)) {
        doapr_outch(sbuffer, buffer, currlen, maxlen, '.');

        while (fplace > 0)
            doapr_outch(sbuffer, buffer, currlen, maxlen, fconvert[--fplace]);
    }
    while (zpadlen > 0) {
        doapr_outch(sbuffer, buffer, currlen, maxlen, '0');
        --zpadlen;
    }

    while (padlen < 0) {
        doapr_outch(sbuffer, buffer, currlen, maxlen, ' ');
        ++padlen;
    }
}

// _dopr is b_print.c's static formatter driver and the only caller of
// fmtint/fmtfp; BIO_vsnprintf is one of its callers.  Both are reproduced here
// (they belong to neighbouring slices) purely so the register calling
// conventions above come out identical.
static void _dopr(char **sbuffer, char **buffer, size_t_ *maxlen,
                  size_t_ *retlen, int *truncated, const char *format,
                  va_list args)                                     // 0x1189d60
{
    char ch;
    LLONG value;
    LDOUBLE fvalue;
    char *strvalue;
    int min;
    int max;
    int state;
    int flags;
    int cflags;
    size_t_ currlen;

    state = DP_S_DEFAULT;
    flags = currlen = cflags = min = 0;
    max = -1;
    ch = *format++;

    while (state != DP_S_DONE) {
        if (ch == '\0' || (buffer == NULL && currlen >= *maxlen))
            state = DP_S_DONE;

        switch (state) {
        case DP_S_DEFAULT:
            if (ch == '%')
                state = DP_S_FLAGS;
            else
                doapr_outch(sbuffer, buffer, &currlen, maxlen, ch);
            ch = *format++;
            break;
        case DP_S_FLAGS:
            switch (ch) {
            case '-': flags |= DP_F_MINUS; ch = *format++; break;
            case '+': flags |= DP_F_PLUS; ch = *format++; break;
            case ' ': flags |= DP_F_SPACE; ch = *format++; break;
            case '#': flags |= DP_F_NUM; ch = *format++; break;
            case '0': flags |= DP_F_ZERO; ch = *format++; break;
            default: state = DP_S_MIN; break;
            }
            break;
        case DP_S_MIN:
            if (isdigit((unsigned char)ch)) {
                min = 10 * min + char_to_int(ch);
                ch = *format++;
            } else if (ch == '*') {
                min = va_arg(args, int);
                ch = *format++;
                state = DP_S_DOT;
            } else
                state = DP_S_DOT;
            break;
        case DP_S_DOT:
            if (ch == '.') {
                state = DP_S_MAX;
                ch = *format++;
            } else
                state = DP_S_MOD;
            break;
        case DP_S_MAX:
            if (isdigit((unsigned char)ch)) {
                if (max < 0)
                    max = 0;
                max = 10 * max + char_to_int(ch);
                ch = *format++;
            } else if (ch == '*') {
                max = va_arg(args, int);
                ch = *format++;
                state = DP_S_MOD;
            } else
                state = DP_S_MOD;
            break;
        case DP_S_MOD:
            switch (ch) {
            case 'h': cflags = DP_C_SHORT; ch = *format++; break;
            case 'l':
                if (*format == 'l') { cflags = DP_C_LLONG; format++; }
                else cflags = DP_C_LONG;
                ch = *format++;
                break;
            case 'q': cflags = DP_C_LLONG; ch = *format++; break;
            case 'L': cflags = DP_C_LDOUBLE; ch = *format++; break;
            default: break;
            }
            state = DP_S_CONV;
            break;
        case DP_S_CONV:
            switch (ch) {
            case 'd':
            case 'i':
                switch (cflags) {
                case DP_C_SHORT: value = (short int)va_arg(args, int); break;
                case DP_C_LONG: value = va_arg(args, long int); break;
                case DP_C_LLONG: value = va_arg(args, LLONG); break;
                default: value = va_arg(args, int); break;
                }
                fmtint(sbuffer, buffer, &currlen, maxlen, value, 10, min, max, flags);
                break;
            case 'X':
                flags |= DP_F_UP;
            case 'x':
            case 'o':
            case 'u':
                flags |= DP_F_UNSIGNED;
                switch (cflags) {
                case DP_C_SHORT: value = (unsigned short int)va_arg(args, unsigned int); break;
                case DP_C_LONG: value = (LLONG) va_arg(args, unsigned long int); break;
                case DP_C_LLONG: value = va_arg(args, unsigned LLONG); break;
                default: value = (LLONG) va_arg(args, unsigned int); break;
                }
                fmtint(sbuffer, buffer, &currlen, maxlen, value,
                       ch == 'o' ? 8 : (ch == 'u' ? 10 : 16), min, max, flags);
                break;
            case 'f':
                if (cflags == DP_C_LDOUBLE)
                    fvalue = va_arg(args, LDOUBLE);
                else
                    fvalue = va_arg(args, double);
                fmtfp(sbuffer, buffer, &currlen, maxlen, fvalue, min, max, flags);
                break;
            case 'E':
                flags |= DP_F_UP;
            case 'e':
                if (cflags == DP_C_LDOUBLE) fvalue = va_arg(args, LDOUBLE);
                else fvalue = va_arg(args, double);
                break;
            case 'G':
                flags |= DP_F_UP;
            case 'g':
                if (cflags == DP_C_LDOUBLE) fvalue = va_arg(args, LDOUBLE);
                else fvalue = va_arg(args, double);
                break;
            case 'c':
                doapr_outch(sbuffer, buffer, &currlen, maxlen, va_arg(args, int));
                break;
            case 's':
                strvalue = va_arg(args, char *);
                if (max < 0) {
                    if (buffer) max = INT_MAX;
                    else max = *maxlen;
                }
                fmtstr(sbuffer, buffer, &currlen, maxlen, strvalue, flags, min, max);
                break;
            case 'p':
                value = (long)va_arg(args, void *);
                fmtint(sbuffer, buffer, &currlen, maxlen, value, 16, min, max, flags | DP_F_NUM);
                break;
            case 'n':
                if (cflags == DP_C_SHORT) { short int *num; num = va_arg(args, short int *); *num = currlen; }
                else if (cflags == DP_C_LONG) { long int *num; num = va_arg(args, long int *); *num = (long int)currlen; }
                else if (cflags == DP_C_LLONG) { LLONG *num; num = va_arg(args, LLONG *); *num = (LLONG)currlen; }
                else { int *num; num = va_arg(args, int *); *num = currlen; }
                break;
            case '%':
                doapr_outch(sbuffer, buffer, &currlen, maxlen, ch);
                break;
            case 'w':
                ch = *format++;
                break;
            default:
                break;
            }
            ch = *format++;
            state = DP_S_DEFAULT;
            flags = cflags = min = 0;
            max = -1;
            break;
        case DP_S_DONE:
            break;
        default:
            break;
        }
    }
    *truncated = (currlen > *maxlen - 1);
    if (*truncated)
        currlen = *maxlen - 1;
    doapr_outch(sbuffer, buffer, &currlen, maxlen, '\0');
    *retlen = currlen - 1;
    return;
}

int __cdecl BIO_vsnprintf(char *buf, size_t_ n, const char *format, va_list args) // 0x118a300
{
    size_t_ retlen;
    int truncated;

    _dopr(&buf, NULL, &n, &retlen, &truncated, format, args);
    if (truncated)
        return -1;
    else
        return (retlen <= INT_MAX) ? (int)retlen : -1;
}
