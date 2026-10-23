// Slice s011dc2c0 -- bundled OpenSSL 0.9.8g elliptic-curve / bignum NIST code.
//   ec_GFp_simple_point2oct          (0x011dc2c0)
//   ec_GFp_simple_oct2point          (0x011dc560)
//   ec_GFp_simple_make_affine        (0x011dd650)
//   ec_GFp_simple_points_make_affine (0x011dd740)
//   _init_256_data                   (0x011de110)
//   BN_nist_mod_256                  (0x011de160)
//   _init_384_data                   (0x011de5f0)
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            s32;
typedef unsigned int   BN_ULONG;   // BN_BITS2 == 32 build

// ---------------------------------------------------------------------------
// BIGNUM as laid out in the retail build (20-byte stride, see ecp_smpl usage)
// ---------------------------------------------------------------------------
struct BIGNUM {
    BN_ULONG* d;      // +0x00
    int       top;    // +0x04
    int       dmax;   // +0x08
    int       neg;    // +0x0c
    int       flags;  // +0x10
};

struct EC_GROUP;
struct BN_CTX;

// EC_POINT: meth, X(+4), Y(+0x18), Z(+0x2c), Z_is_one(+0x40)
struct EC_POINT {
    const void* meth;      // +0x00
    BIGNUM      X;         // +0x04
    BIGNUM      Y;         // +0x18
    BIGNUM      Z;         // +0x2c
    int         Z_is_one;  // +0x40
};

// EC_METHOD: only the slots used below (offsets from retail ecp_smpl vtable table)
struct EC_METHOD {
    void* m00[0x80 / 4];                                   // +0x00 .. +0x7c
    int (*field_mul)(const EC_GROUP*, BIGNUM*, const BIGNUM*, const BIGNUM*, BN_CTX*); // +0x80
    int (*field_sqr)(const EC_GROUP*, BIGNUM*, const BIGNUM*, BN_CTX*);                 // +0x84
    void* m88;                                              // +0x88
    int (*field_encode)(const EC_GROUP*, BIGNUM*, const BIGNUM*, BN_CTX*);              // +0x8c
    void* m90;                                              // +0x90
    int (*field_set_to_one)(const EC_GROUP*, BIGNUM*, BN_CTX*);                         // +0x94
};

// EC_GROUP: meth, generator, order, cofactor, ... field at +0x48
struct EC_GROUP {
    const EC_METHOD* meth;// +0x00
    void*       generator; // +0x04
    BIGNUM      order;     // +0x08
    BIGNUM      cofactor;  // +0x1c
    int         curve_name;// +0x30
    int         asn1_flag; // +0x34
    int         asn1_form; // +0x38
    u8*         seed;      // +0x3c
    u32         seed_len;  // +0x40
    void*       extra_data;// +0x44
    BIGNUM      field;     // +0x48
};

// BN_CTX is opaque here; only manipulated through the BN_CTX_* entry points.
struct BN_CTX;

// ---------------------------------------------------------------------------
// external callees (retail VAs in comments; bodies live in other slices)
// ---------------------------------------------------------------------------
void  __cdecl ERR_put_error(int lib, int func, int reason, const char* file, int line); // 0x1180d50
int   __cdecl BN_num_bits(const BIGNUM* a);                         // 0x117a8e0
#define BN_num_bytes(a)  ((BN_num_bits(a) + 7) / 8)
BN_CTX* __cdecl BN_CTX_new();                                       // 0x1187a80
void  __cdecl BN_CTX_start(BN_CTX* ctx);                            // 0x1187b00
BIGNUM* __cdecl BN_CTX_get(BN_CTX* ctx);                            // 0x1187b90
void  __cdecl BN_CTX_end(BN_CTX* ctx);                              // 0x1187b50
void  __cdecl BN_CTX_free(BN_CTX* ctx);                             // 0x1187ad0
int   __cdecl BN_bn2bin(const BIGNUM* a, u8* to);                   // 0x117ada0
BIGNUM* __cdecl BN_bin2bn(const u8* s, int len, BIGNUM* ret);       // 0x117ac80
int   __cdecl BN_ucmp(const BIGNUM* a, const BIGNUM* b);            // 0x117ae20
int   __cdecl BN_copy(BIGNUM* a, const BIGNUM* b);                  // 0x117ab40
int   __cdecl BN_usub(BIGNUM* r, const BIGNUM* a, const BIGNUM* b); // 0x117b0a0
int   __cdecl BN_set_word(BIGNUM* a, BN_ULONG w);                   // 0x117ac20
BIGNUM* __cdecl BN_new();                                           // 0x117a9d0
void  __cdecl BN_clear_free(BIGNUM* a);                             // 0x117a910
void* __cdecl CRYPTO_malloc(int num, const char* file, int line);   // 0x1183410
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);
void  __cdecl CRYPTO_free(void* p);                                 // 0x11835c0
void  __cdecl CRYPTO_lock(int mode, int type, const char* file, int line); // 0x1181540
int   __cdecl BN_mod_inverse(BIGNUM* ret, const BIGNUM* a, const BIGNUM* n, BN_CTX* ctx); // 0x1187e90

// field / method helpers (retail VAs; all in lib_cblock / lib_openssl)
int   __cdecl EC_POINT_is_at_infinity(const EC_GROUP* group, const EC_POINT* point);   // 0x11b27e0
int   __cdecl EC_POINT_get_affine_coordinates_GFp(const EC_GROUP* g, const EC_POINT* p, BIGNUM* x, BIGNUM* y, BN_CTX* ctx); // 0x11b2470
int   __cdecl EC_POINT_set_affine_coordinates_GFp(const EC_GROUP* g, EC_POINT* p, const BIGNUM* x, const BIGNUM* y, BN_CTX* ctx); // 0x11b23b0
int   __cdecl EC_POINT_set_compressed_coordinates_GFp(const EC_GROUP* g, EC_POINT* p, const BIGNUM* x, int y_bit, BN_CTX* ctx);  // 0x11b2530
int   __cdecl EC_POINT_is_on_curve(const EC_GROUP* g, const EC_POINT* p, BN_CTX* ctx);  // 0x11b2830
int   __cdecl EC_POINT_set_to_infinity(const EC_GROUP* g, EC_POINT* p);                 // 0x11b2300
BIGNUM* __cdecl bn_expand2(BIGNUM* a, int words);                   // 0x117ab00
#define bn_wexpand(a, words)  (((a)->dmax >= (words)) ? (a) : bn_expand2((a), (words)))
int   __cdecl bn_add_words(BN_ULONG* r, const BN_ULONG* a, const BN_ULONG* b, int n);  // 0x11ae100
int   __cdecl bn_sub_words(BN_ULONG* r, const BN_ULONG* a, const BN_ULONG* b, int n);  // 0x11ae1f0
int   __cdecl nist_cp_bn_0(BN_ULONG* buf, const BN_ULONG* a, int top, int max);        // 0x11ddc00
int   __cdecl BN_nist_mod_256(BIGNUM* r, const BIGNUM* a, const BIGNUM* field, BN_CTX* ctx); // 0x117b... (self)
BN_ULONG* __cdecl BN_nist_p_256_ref();                              // not used; placeholder

// open-coded helpers from bn.h / ecp_smpl.c
static inline int BN_is_zero(const BIGNUM* a) { return a->top == 0; }
static __forceinline int BN_is_odd(const BIGNUM* a) { return a->top > 0 && (a->d[0] & 1); }
static inline int BN_is_one(const BIGNUM* a)
    { return a->top == 1 && a->d[0] == 1; }

// ---------------------------------------------------------------------------
// NIST 256/384 modulus tables (retail .rdata/.data blobs)
// ---------------------------------------------------------------------------
extern "C" const BN_ULONG _nist_p_256[8];      // 0x014f4c1c
extern "C" const BN_ULONG _nist_p_384[12];     // 0x014f4c3c
BN_ULONG _256_data[8 * 6];                     // 0x016f23c8
int      _is_set_256_data;                     // 0x016f2608
BN_ULONG _384_data[12 * 8];                    // 0x016f2488
int      _is_set_384_data;                     // 0x016f260c

#define BN_NIST_256_TOP 8
#define BN_NIST_384_TOP 12
#define BN_TBIT  ((BN_ULONG)0x80000000)
#define BN_MASK2 (0xffffffff)

// nist_set_256(t_d, buf, a1..a8) with a_p == 0 meaning "set that word to 0"
#define bn_32_set_0(to, n)   (to)[n] = 0
#define nist_cp_bn(buf, a, top) \
    { \
    int _i; \
    BN_ULONG* _tmp1 = (buf), *_tmp2 = (a); \
    for (_i = (top); _i != 0; _i--) \
        *_tmp1++ = *_tmp2++; \
    }
#define nist_set_256(to, from, a1, a2, a3, a4, a5, a6, a7, a8) \
    { \
    if (a8 != 0) to[0] = (from)[(a8) - 8]; else bn_32_set_0(to, 0); \
    if (a7 != 0) to[1] = (from)[(a7) - 8]; else bn_32_set_0(to, 1); \
    if (a6 != 0) to[2] = (from)[(a6) - 8]; else bn_32_set_0(to, 2); \
    if (a5 != 0) to[3] = (from)[(a5) - 8]; else bn_32_set_0(to, 3); \
    if (a4 != 0) to[4] = (from)[(a4) - 8]; else bn_32_set_0(to, 4); \
    if (a3 != 0) to[5] = (from)[(a3) - 8]; else bn_32_set_0(to, 5); \
    if (a2 != 0) to[6] = (from)[(a2) - 8]; else bn_32_set_0(to, 6); \
    if (a1 != 0) to[7] = (from)[(a1) - 8]; else bn_32_set_0(to, 7); \
    }

// ---------------------------------------------------------------------------
// async off: nothing here; functions defined in retail order.
// ---------------------------------------------------------------------------

// @ 0x011dc2c0
u32 __cdecl ec_GFp_simple_point2oct(const EC_GROUP* group, const EC_POINT* point, int form,
                                    u8* buf, u32 len, BN_CTX* ctx)
{
    u32      ret;
    BN_CTX*  new_ctx = 0;
    int      used_ctx = 0;
    BIGNUM*  x, *y;
    u32      field_len, i, skip;

    if ((form != 2) && (form != 4) && (form != 6)) {
        ERR_put_error(0x10, 0x68, 0x68, 0, 0);
        goto err;
    }

    if (EC_POINT_is_at_infinity(group, point)) {
        if (buf != 0) {
            if (len < 1) {
                ERR_put_error(0x10, 0x68, 0x64, 0, 0);
                return 0;
            }
            buf[0] = 0;
        }
        return 1;
    }

    field_len = BN_num_bytes(&group->field);
    ret = (form == 2) ? 1 + field_len : 1 + 2 * field_len;

    if (buf != 0) {
        if (len < ret) {
            ERR_put_error(0x10, 0x68, 0x64, 0, 0);
            goto err;
        }

        if (ctx == 0) {
            ctx = new_ctx = BN_CTX_new();
            if (ctx == 0)
                return 0;
        }

        BN_CTX_start(ctx);
        used_ctx = 1;
        x = BN_CTX_get(ctx);
        y = BN_CTX_get(ctx);
        if (y == 0) goto err;

        if (!EC_POINT_get_affine_coordinates_GFp(group, point, x, y, ctx)) goto err;

        if ((form == 2 || form == 6) && BN_is_odd(y))
            buf[0] = (u8)(form + 1);
        else
            buf[0] = (u8)form;

        i = 1;

        skip = field_len - BN_num_bytes(x);
        if (skip > field_len) {
            ERR_put_error(0x10, 0x68, 0x44, 0, 0);
            goto err;
        }
        while (skip > 0) {
            buf[i++] = 0;
            skip--;
        }
        skip = BN_bn2bin(x, buf + i);
        i += skip;
        if (i != 1 + field_len) {
            ERR_put_error(0x10, 0x68, 0x44, 0, 0);
            goto err;
        }

        if (form == 4 || form == 6) {
            skip = field_len - BN_num_bytes(y);
            if (skip > field_len) {
                ERR_put_error(0x10, 0x68, 0x44, 0, 0);
                goto err;
            }
            while (skip > 0) {
                buf[i++] = 0;
                skip--;
            }
            skip = BN_bn2bin(y, buf + i);
            i += skip;
        }

        if (i != ret) {
            ERR_put_error(0x10, 0x68, 0x44, 0, 0);
            goto err;
        }
    }

    if (used_ctx)
        BN_CTX_end(ctx);
    if (new_ctx != 0)
        BN_CTX_free(new_ctx);
    return ret;

 err:
    if (used_ctx)
        BN_CTX_end(ctx);
    if (new_ctx != 0)
        BN_CTX_free(new_ctx);
    return 0;
}

// @ 0x011dc560
int __cdecl ec_GFp_simple_oct2point(const EC_GROUP* group, EC_POINT* point,
                                    const u8* buf, u32 len, BN_CTX* ctx)
{
    int      form;
    int      y_bit;
    BN_CTX*  new_ctx = 0;
    BIGNUM*  x, *y;
    u32      field_len, enc_len;
    int      ret = 0;

    if (len == 0) {
        ERR_put_error(0x10, 0x67, 0x64, 0, 0);
        return 0;
    }
    form = buf[0];
    y_bit = form & 1;
    form = form & ~1U;
    if ((form != 0) && (form != 2) && (form != 4) && (form != 6)) {
        ERR_put_error(0x10, 0x67, 0x66, 0, 0);
        return 0;
    }
    if ((form == 0 || form == 4) && y_bit) {
        ERR_put_error(0x10, 0x67, 0x66, 0, 0);
        return 0;
    }

    if (form == 0) {
        if (len != 1) {
            ERR_put_error(0x10, 0x67, 0x66, 0, 0);
            return 0;
        }
        return EC_POINT_set_to_infinity(group, point);
    }

    field_len = BN_num_bytes(&group->field);
    enc_len = (form == 2) ? 1 + field_len : 1 + 2 * field_len;

    if (len != enc_len) {
        ERR_put_error(0x10, 0x67, 0x66, 0, 0);
        return 0;
    }

    if (ctx == 0) {
        ctx = new_ctx = BN_CTX_new();
        if (ctx == 0)
            return 0;
    }

    BN_CTX_start(ctx);
    x = BN_CTX_get(ctx);
    y = BN_CTX_get(ctx);
    if (y == 0) goto err;

    if (!BN_bin2bn(buf + 1, (int)field_len, x)) goto err;
    if (BN_ucmp(x, &group->field) >= 0) {
        ERR_put_error(0x10, 0x67, 0x66, 0, 0);
        goto err;
    }

    if (form == 2) {
        if (!EC_POINT_set_compressed_coordinates_GFp(group, point, x, y_bit, ctx)) goto err;
    } else {
        if (!BN_bin2bn(buf + 1 + field_len, (int)field_len, y)) goto err;
        if (BN_ucmp(y, &group->field) >= 0) {
            ERR_put_error(0x10, 0x67, 0x66, 0, 0);
            goto err;
        }
        if (form == 6) {
            if (y_bit != BN_is_odd(y)) {
                ERR_put_error(0x10, 0x67, 0x66, 0, 0);
                goto err;
            }
        }
        if (!EC_POINT_set_affine_coordinates_GFp(group, point, x, y, ctx)) goto err;
    }

    if (!EC_POINT_is_on_curve(group, point, ctx)) {
        ERR_put_error(0x10, 0x67, 0x6b, 0, 0);
        goto err;
    }

    ret = 1;

 err:
    BN_CTX_end(ctx);
    if (new_ctx != 0)
        BN_CTX_free(new_ctx);
    return ret;
}

// @ 0x011dd650
int __cdecl ec_GFp_simple_make_affine(const EC_GROUP* group, EC_POINT* point, BN_CTX* ctx)
{
    BN_CTX* new_ctx = 0;
    BIGNUM* x, *y;
    int     ret = 0;

    if (point->Z_is_one || EC_POINT_is_at_infinity(group, point))
        return 1;

    if (ctx == 0) {
        ctx = new_ctx = BN_CTX_new();
        if (ctx == 0)
            return 0;
    }

    BN_CTX_start(ctx);
    x = BN_CTX_get(ctx);
    y = BN_CTX_get(ctx);
    if (y == 0) goto err;

    if (!EC_POINT_get_affine_coordinates_GFp(group, point, x, y, ctx)) goto err;
    if (!EC_POINT_set_affine_coordinates_GFp(group, point, x, y, ctx)) goto err;
    if (!point->Z_is_one) {
        ERR_put_error(0x10, 0x66, 0x44, 0, 0);
        goto err;
    }

    ret = 1;

 err:
    BN_CTX_end(ctx);
    if (new_ctx != 0)
        BN_CTX_free(new_ctx);
    return ret;
}

// @ 0x011dd740
int __cdecl ec_GFp_simple_points_make_affine(const EC_GROUP* group, u32 num,
                                             EC_POINT** points, BN_CTX* ctx)
{
    BN_CTX*  new_ctx = 0;
    BIGNUM*  tmp0, *tmp1;
    u32      pow2 = 0;
    BIGNUM** heap = 0;
    u32      i;
    int      ret = 0;

    if (num == 0)
        return 1;

    if (ctx == 0) {
        ctx = new_ctx = BN_CTX_new();
        if (ctx == 0)
            return 0;
    }

    BN_CTX_start(ctx);
    tmp0 = BN_CTX_get(ctx);
    tmp1 = BN_CTX_get(ctx);
    if (tmp0 == 0 || tmp1 == 0) goto err;

    pow2 = 1;
    while (num > pow2)
        pow2 <<= 1;
    pow2 <<= 1;

    heap = (BIGNUM**)CRYPTO_malloc((int)(pow2 * sizeof(heap[0])),
                                   ".\\crypto\\ec\\ecp_smpl.c", 0x625);
    if (heap == 0) goto err;

    heap[0] = 0;
    for (i = pow2 / 2 - 1; i > 0; i--)
        heap[i] = 0;
    for (i = 0; i < num; i++)
        heap[pow2 / 2 + i] = &points[i]->Z;
    for (i = pow2 / 2 + num; i < pow2; i++)
        heap[i] = 0;

    for (i = pow2 / 2 - 1; i > 0; i--) {
        heap[i] = BN_new();
        if (heap[i] == 0) goto err;

        if (heap[2 * i] != 0) {
            if ((heap[2 * i + 1] == 0) || BN_is_zero(heap[2 * i + 1])) {
                if (!BN_copy(heap[i], heap[2 * i])) goto err;
            } else {
                if (BN_is_zero(heap[2 * i])) {
                    if (!BN_copy(heap[i], heap[2 * i + 1])) goto err;
                } else {
                    if (!group->meth->field_mul(group, heap[i], heap[2 * i], heap[2 * i + 1], ctx))
                        goto err;
                }
            }
        }
    }

    if (!BN_is_zero(heap[1])) {
        if (!BN_mod_inverse(heap[1], heap[1], &group->field, ctx)) {
            ERR_put_error(0x10, 0x89, 3, 0, 0);
            goto err;
        }
    }
    if (group->meth->field_encode != 0) {
        if (!group->meth->field_encode(group, heap[1], heap[1], ctx)) goto err;
        if (!group->meth->field_encode(group, heap[1], heap[1], ctx)) goto err;
    }

    for (i = 2; i < pow2 / 2 + num; i += 2) {
        if ((heap[i + 1] != 0) && !BN_is_zero(heap[i + 1])) {
            if (!group->meth->field_mul(group, tmp0, heap[i / 2], heap[i + 1], ctx)) goto err;
            if (!group->meth->field_mul(group, tmp1, heap[i / 2], heap[i], ctx)) goto err;
            if (!BN_copy(heap[i], tmp0)) goto err;
            if (!BN_copy(heap[i + 1], tmp1)) goto err;
        } else {
            if (!BN_copy(heap[i], heap[i / 2])) goto err;
        }
    }

    for (i = 0; i < num; i++) {
        EC_POINT* p = points[i];

        if (!BN_is_zero(&p->Z)) {
            if (!group->meth->field_sqr(group, tmp1, &p->Z, ctx)) goto err;
            if (!group->meth->field_mul(group, &p->X, &p->X, tmp1, ctx)) goto err;

            if (!group->meth->field_mul(group, tmp1, tmp1, &p->Z, ctx)) goto err;
            if (!group->meth->field_mul(group, &p->Y, &p->Y, tmp1, ctx)) goto err;

            if (group->meth->field_set_to_one != 0) {
                if (!group->meth->field_set_to_one(group, &p->Z, ctx)) goto err;
            } else {
                if (!BN_set_word(&p->Z, 1)) goto err;
            }

            p->Z_is_one = 1;
        }
    }

    ret = 1;

 err:
    BN_CTX_end(ctx);
    if (new_ctx != 0)
        BN_CTX_free(new_ctx);
    if (heap != 0) {
        pow2 >>= 1;
        while (pow2 = pow2 - 1, pow2 != 0) {
            if (heap[pow2] != 0)
                BN_clear_free(heap[pow2]);
        }
        CRYPTO_free(heap);
    }
    return ret;
}

// @ 0x011de110
void __cdecl _init_256_data()
{
    int          i;
    BN_ULONG*    tmp1 = _256_data;
    BN_ULONG*    tmp2 = tmp1;

    memcpy(tmp1, (void*)_nist_p_256, BN_NIST_256_TOP * sizeof(BN_ULONG));
    tmp1 += BN_NIST_256_TOP;

    for (i = 0; i < 5; i++) {
        bn_add_words(tmp1, _nist_p_256, tmp2, BN_NIST_256_TOP);
        tmp2 = tmp1;
        tmp1 += BN_NIST_256_TOP;
    }
    _is_set_256_data = 1;
}

// @ 0x011de160
int __cdecl BN_nist_mod_256(BIGNUM* r, const BIGNUM* a, const BIGNUM* field, BN_CTX* ctx)
{
    int       i, top = a->top;
    int       carry = 0;
    BN_ULONG* a_d = a->d, *r_d;
    BN_ULONG  t_d[BN_NIST_256_TOP],
              t_d2[BN_NIST_256_TOP],
              buf[BN_NIST_256_TOP];

    if (!_is_set_256_data) {
        CRYPTO_lock(9, 0x23, ".\\crypto\\bn\\bn_nist.c", 0x1c7);
        if (!_is_set_256_data)
            _init_256_data();
        CRYPTO_lock(10, 0x23, ".\\crypto\\bn\\bn_nist.c", 0x1cc);
    }

    i = BN_ucmp(field, a);
    if (i == 0) {
        BN_set_word(r, 0);
        return 1;
    } else if (i > 0)
        return (r == a) ? 1 : (BN_copy(r, a) != 0);

    if (top == BN_NIST_256_TOP)
        return BN_usub(r, a, field);

    if (r != a) {
        if (!bn_wexpand(r, BN_NIST_256_TOP))
            return 0;
        r_d = r->d;
        nist_cp_bn(r_d, a_d, BN_NIST_256_TOP);
    } else
        r_d = a_d;

    /* nist_cp_bn_0(buf, a_d + BN_NIST_256_TOP, top - BN_NIST_256_TOP, BN_NIST_256_TOP) */
    nist_cp_bn_0(buf, a_d + BN_NIST_256_TOP, top - BN_NIST_256_TOP, BN_NIST_256_TOP);

    /*S1*/
    nist_set_256(t_d, buf, 15, 14, 13, 12, 11, 0, 0, 0);
    /*S2*/
    nist_set_256(t_d2, buf, 0, 15, 14, 13, 12, 0, 0, 0);
    if (bn_add_words(t_d, t_d, t_d2, BN_NIST_256_TOP))
        carry = 2;
    /* left shift */
    {
        BN_ULONG* ap = t_d;
        BN_ULONG  t, c = 0;
        for (i = BN_NIST_256_TOP; i != 0; --i) {
            t = *ap;
            *(ap++) = ((t << 1) | c) & BN_MASK2;
            c = (t & BN_TBIT) ? 1 : 0;
        }
        if (c)
            ++carry;
    }

    if (bn_add_words(r_d, r_d, t_d, BN_NIST_256_TOP))
        ++carry;
    /*S3*/
    nist_set_256(t_d, buf, 15, 14, 0, 0, 0, 10, 9, 8);
    if (bn_add_words(r_d, r_d, t_d, BN_NIST_256_TOP))
        ++carry;
    /*S4*/
    nist_set_256(t_d, buf, 8, 13, 15, 14, 13, 11, 10, 9);
    if (bn_add_words(r_d, r_d, t_d, BN_NIST_256_TOP))
        ++carry;
    /*D1*/
    nist_set_256(t_d, buf, 10, 8, 0, 0, 0, 13, 12, 11);
    if (bn_sub_words(r_d, r_d, t_d, BN_NIST_256_TOP))
        --carry;
    /*D2*/
    nist_set_256(t_d, buf, 11, 9, 0, 0, 15, 14, 13, 12);
    if (bn_sub_words(r_d, r_d, t_d, BN_NIST_256_TOP))
        --carry;
    /*D3*/
    nist_set_256(t_d, buf, 12, 0, 10, 9, 8, 15, 14, 13);
    if (bn_sub_words(r_d, r_d, t_d, BN_NIST_256_TOP))
        --carry;
    /*D4*/
    nist_set_256(t_d, buf, 13, 0, 11, 10, 9, 0, 15, 14);
    if (bn_sub_words(r_d, r_d, t_d, BN_NIST_256_TOP))
        --carry;

    if (carry) {
        if (carry > 0)
            bn_sub_words(r_d, r_d, _256_data + BN_NIST_256_TOP * --carry, BN_NIST_256_TOP);
        else {
            carry = -carry;
            bn_add_words(r_d, r_d, _256_data + BN_NIST_256_TOP * --carry, BN_NIST_256_TOP);
        }
    }

    r->top = BN_NIST_256_TOP;
    /* bn_correct_top(r) */
    {
        BN_ULONG* rp = r->d + r->top - 1;
        while (r->top > 0 && *rp == 0) {
            r->top--;
            rp--;
        }
    }
    if (BN_ucmp(r, field) >= 0) {
        bn_sub_words(r_d, r_d, _nist_p_256, BN_NIST_256_TOP);
        {
            BN_ULONG* rp = r->d + r->top - 1;
            while (r->top > 0 && *rp == 0) {
                r->top--;
                rp--;
            }
        }
    }
    return 1;
}

// @ 0x011de5f0
void __cdecl _init_384_data()
{
    int          i;
    BN_ULONG*    tmp1 = _384_data;
    BN_ULONG*    tmp2 = tmp1;

    memcpy(tmp1, (void*)_nist_p_384, BN_NIST_384_TOP * sizeof(BN_ULONG));
    tmp1 += BN_NIST_384_TOP;

    for (i = 0; i < 7; i++) {
        bn_add_words(tmp1, _nist_p_384, tmp2, BN_NIST_384_TOP);
        tmp2 = tmp1;
        tmp1 += BN_NIST_384_TOP;
    }
    _is_set_384_data = 1;
}
