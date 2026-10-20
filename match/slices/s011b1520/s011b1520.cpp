// Decompiled source for gold3 slice s011b1520.
//
// The analyser labelled this range lib_cblock, but it is OpenSSL 1.0.x (the
// lib_openssl naming on the callees is the giveaway): the EC_KEY / EC_GROUP
// method-table dispatchers from crypto/ec/ec_lib.c, EC_KEY_new_method,
// EC_KEY_copy, EC_KEY_set_public_key_affine_coordinates, the ECDSA_SIG method
// table (crypto/ecdsa/ecs_lib.c), an ASN.1 date helper, the EC_EX_DATA chain
// helper and a multi-precision multiply-accumulate routine.
//
// Build: /vc71 /O2 /MD /Gy /TP.
#include "types.h"

// ---- OpenSSL error reporting / allocation -------------------------------
// @ 0x01180d50  ERR_put_error(int lib, int func, int reason, const char* file, int line)
extern "C" void ERR_put_error(int lib, int func, int reason, const char* file, int line);
// @ 0x01183410  CRYPTO_malloc(int num, const char* file, int line)
extern "C" void* CRYPTO_malloc(int num, const char* file, int line);
// @ 0x011835c0  CRYPTO_free(void* addr)
extern "C" void CRYPTO_free(void* addr);
// @ 0x01183740  CRYPTO_free of a REF structure
extern "C" void CRYPTO_free_ref(void* addr);
// @ 0x01183400  CRYPTO_new_ex_data(int class_id, void* obj, void* ad)
extern "C" int  CRYPTO_new_ex_data(int class_id, void* obj, void* ad);

// ---- bignum / EC primitives (elsewhere in the image) ---------------------
// @ 0x011c8ff0  ASN1_UTCTIME_set_string / tm helper
extern "C" int  asn1_utctime_helper(int tm, int t, int n);
// @ 0x011c9210  ASN1_GENERALIZEDTIME variant
extern "C" int  asn1_gentime_helper(int tm, int t, int n);
// @ 0x011a...?  OPENSSL_gmtime(const time_t*, struct tm*)
extern "C" void* OPENSSL_gmtime(const void* timer, void* result);
// @ 0x011ca400  ENGINE_get_default_ECDSA()
extern "C" void* ENGINE_get_default_ECDSA(void);
// @ 0x011cac10  ECDSA_OpenSSL()
extern "C" void* ECDSA_OpenSSL(void);
// @ 0x011cac20  ECDSA_METHOD_set_engine / ECDSA_METHOD_new
extern "C" void* ECDSA_METHOD_new(void* meth);
extern "C" int   BN_init(void* bn);
extern "C" int   BN_copy(void* to, const void* from);
extern "C" int   BN_set_word(void* a, unsigned long w);
extern "C" void  EC_POINT_clear_free(void* p);
// @ 0x01181c??  EC_EX_DATA_free_all_data
extern "C" void  EC_EX_DATA_free_all_data(void* list);

// globals touched by this slice
extern void* g_ecdsaDefaultMethod;   // 0x016f21e8

// forward declarations of the intra-slice entry points
int* ec_key_new_method(int* meth);                       // 0x011b2140
int  ec_compare_public_key(void* a, void* b);            // 0x011b2240
int  ec_ex_data_set_data(void** head, void* data,
                         void* dupFn, void* setFn, void* freeFn);   // 0x011b1f80
// @ 0x011e0744  memory copy used for the 0x3c/0x40 blob in EC_KEY_copy
extern "C" int eastl_vector_do_insert_value(void* dst, const void* src, int len);

// parameter strings used by the mallocs
static const char kEcLibC[]   = ".\\crypto\\ec\\ec_lib.c";
static const char kEcsLibC[]  = ".\\crypto\\ecdsa\\ecs_lib.c";

// ---------------------------------------------------------------------------
// EC method-table dispatchers.  Every EC_GROUP/EC_KEY operation is
//   if (this->meth-><slot> == 0) { ERR_put_error(0x10, func, 0x42, 0, 0); return 0; }
//   if (<identity comparison fails>) { ERR_put_error(0x10, func, 0x65, 0, 0); return 0; }
//   return this->meth-><slot>(args...);
// The method pointer is the first word of the object.
// ---------------------------------------------------------------------------

// @ 0x011b1ef0
void* ec_group_precompute_mult(void* group)
{
    void* fn = *(void**)((char*)*(void**)group + 0x14);
    if (fn == 0) {
        ERR_put_error(0x10, 0x6d, 0x42, 0, 0);
        return 0;
    }
    typedef void* (*Fn)(void*);
    return ((Fn)fn)(group);
}

// @ 0x011b1f20
void* ec_group_make_affine(void* group)
{
    void* fn = *(void**)((char*)*(void**)group + 0x14);
    if (fn == 0) {
        ERR_put_error(0x10, 0xb0, 0x42, 0, 0);
        return 0;
    }
    typedef void* (*Fn)(void*);
    return ((Fn)fn)(group);
}

// @ 0x011b1f50
void* ec_group_points_clear(void* group)
{
    void* fn = *(void**)((char*)*(void**)group + 0x1c);
    if (fn == 0) {
        ERR_put_error(0x10, 0xad, 0x42, 0, 0);
        return 0;
    }
    typedef void* (*Fn)(void*);
    return ((Fn)fn)(group);
}

// @ 0x011b2240
int ec_compare_public_key(void* a, void* b)
{
    void* fn = *(void**)((char*)*(void**)a + 0x30);
    if (fn == 0) {
        ERR_put_error(0x10, 0x72, 0x42, 0, 0);
        return 0;
    }
    if (*(void**)a != *(void**)b) {
        ERR_put_error(0x10, 0x72, 0x65, 0, 0);
        return 0;
    }
    if (a == b)
        return 1;
    typedef int (*Fn)(void*, void*);
    return ((Fn)fn)(a, b);
}

// @ 0x011b2300
int ec_precompute_mult2(void* a, void* b)
{
    void* fn = *(void**)((char*)*(void**)a + 0x34);
    if (fn == 0) {
        ERR_put_error(0x10, 0x7f, 0x42, 0, 0);
        return 0;
    }
    if (*(void**)a != *(void**)b) {
        ERR_put_error(0x10, 0x7f, 0x65, 0, 0);
        return 0;
    }
    typedef int (*Fn)(void*, void*);
    return ((Fn)fn)(a, b);
}

// @ 0x011b2350
int ec_group_op_38(void* a, void* b, void* c, void* d, void* e, void* f)
{
    void* fn = *(void**)((char*)*(void**)a + 0x38);
    if (fn == 0) {
        ERR_put_error(0x10, 0x7e, 0x42, 0, 0);
        return 0;
    }
    if (*(void**)a != *(void**)b) {
        ERR_put_error(0x10, 0x7e, 0x65, 0, 0);
        return 0;
    }
    typedef int (*Fn)(void*, void*, void*, void*, void*, void*);
    return ((Fn)fn)(a, b, c, d, e, f);
}

// @ 0x011b25f0
int ec_group_op_4c(void* a, void* b, void* c, void* d, void* e, void* f)
{
    void* fn = *(void**)((char*)*(void**)a + 0x4c);
    if (fn == 0) {
        ERR_put_error(0x10, 0x7b, 0x42, 0, 0);
        return 0;
    }
    if (*(void**)a != *(void**)b) {
        ERR_put_error(0x10, 0x7b, 0x65, 0, 0);
        return 0;
    }
    typedef int (*Fn)(void*, void*, void*, void*, void*, void*);
    return ((Fn)fn)(a, b, c, d, e, f);
}

// @ 0x011b26b0
int ec_group_op_54(void* a, void* b, void* c, void* d, void* e)
{
    void* fn = *(void**)((char*)*(void**)a + 0x54);
    if (fn == 0) {
        ERR_put_error(0x10, 0x70, 0x42, 0, 0);
        return 0;
    }
    if (*(void**)a == *(void**)b && *(void**)b == *(void**)c && *(void**)c == *(void**)d) {
        typedef int (*Fn)(void*, void*, void*, void*, void*);
        return ((Fn)fn)(a, b, c, d, e);
    }
    ERR_put_error(0x10, 0x70, 0x65, 0, 0);
    return 0;
}

// @ 0x011b2720
int ec_group_op_58(void* a, void* b, void* c, void* d)
{
    void* fn = *(void**)((char*)*(void**)a + 0x58);
    if (fn == 0) {
        ERR_put_error(0x10, 0x73, 0x42, 0, 0);
        return 0;
    }
    if (*(void**)a == *(void**)b && *(void**)b == *(void**)c) {
        typedef int (*Fn)(void*, void*, void*, void*);
        return ((Fn)fn)(a, b, c, d);
    }
    ERR_put_error(0x10, 0x73, 0x65, 0, 0);
    return 0;
}

// @ 0x011b2780
int ec_group_op_5c(void* a, void* b, void* c)
{
    if (*(void**)((char*)*(void**)a + 0x58) == 0) {
        ERR_put_error(0x10, 0xd2, 0x42, 0, 0);
        return 0;
    }
    if (*(void**)a != *(void**)b) {
        ERR_put_error(0x10, 0xd2, 0x65, 0, 0);
        return 0;
    }
    typedef int (*Fn)(void*, void*, void*);
    return ((Fn)*(void**)((char*)*(void**)a + 0x5c))(a, b, c);
}

// @ 0x011b27e0
int ec_group_op_60(void* a, void* b)
{
    void* fn = *(void**)((char*)*(void**)a + 0x60);
    if (fn == 0) {
        ERR_put_error(0x10, 0x76, 0x42, 0, 0);
        return 0;
    }
    if (*(void**)a != *(void**)b) {
        ERR_put_error(0x10, 0x76, 0x65, 0, 0);
        return 0;
    }
    typedef int (*Fn)(void*, void*);
    return ((Fn)fn)(a, b);
}

// @ 0x011b2830
int ec_group_op_64(void* a, void* b, void* c)
{
    void* fn = *(void**)((char*)*(void**)a + 0x64);
    if (fn == 0) {
        ERR_put_error(0x10, 0x77, 0x42, 0, 0);
        return 0;
    }
    if (*(void**)a != *(void**)b) {
        ERR_put_error(0x10, 0x77, 0x65, 0, 0);
        return 0;
    }
    typedef int (*Fn)(void*, void*, void*);
    return ((Fn)fn)(a, b, c);
}

// @ 0x011b2880
int ec_group_op_68(void* a, void* b, void* c, void* d)
{
    void* fn = *(void**)((char*)*(void**)a + 0x68);
    if (fn == 0) {
        ERR_put_error(0x10, 0x71, 0x42, 0, 0);
        return 0;
    }
    if (*(void**)a == *(void**)b && *(void**)b == *(void**)c) {
        typedef int (*Fn)(void*, void*, void*, void*);
        return ((Fn)fn)(a, b, c, d);
    }
    ERR_put_error(0x10, 0x71, 0x65, 0, 0);
    return 0;
}

// @ 0x011b28e0
int ec_group_op_6c(void* a, void* b, void* c)
{
    void* fn = *(void**)((char*)*(void**)a + 0x6c);
    if (fn == 0) {
        ERR_put_error(0x10, 0x78, 0x42, 0, 0);
        return 0;
    }
    if (*(void**)a != *(void**)b) {
        ERR_put_error(0x10, 0x78, 0x65, 0, 0);
        return 0;
    }
    typedef int (*Fn)(void*, void*, void*);
    return ((Fn)fn)(a, b, c);
}

// @ 0x011b2930  (checks an array of `n` group pointers share this group's method)
int ec_group_op_70(void* a, unsigned n, void* const* arr, void* d)
{
    void* fn = *(void**)((char*)*(void**)a + 0x70);
    if (fn == 0) {
        ERR_put_error(0x10, 0x88, 0x42, 0, 0);
        return 0;
    }
    for (unsigned i = 0; i < n; ++i) {
        if (*(void**)a != *(void**)arr[i]) {
            ERR_put_error(0x10, 0x88, 0x65, 0, 0);
            return 0;
        }
    }
    typedef int (*Fn)(void*, unsigned, void* const*, void*);
    return ((Fn)fn)(a, n, arr, d);
}

// ---------------------------------------------------------------------------
// crypto/ec/ec_lib.c helpers
// ---------------------------------------------------------------------------

// EC_EX_DATA node: { next(+0), int (*free)(void*)(+4), void* data(+8),
//                    int (*dup)(void*)(+0xc), void* (*set)(void*)(+0x10), ... }
// @ 0x011b1f80  EC_EX_DATA_set_data(EC_EXTRA_DATA** head, void* data,
//                                    void* (*dup)(void*), void* (*set)(void*),
//                                    void (*free)(void*))
int ec_ex_data_set_data(void** head, void* data, void* dupFn, void* setFn, void* freeFn)
{
    if (head == 0)
        return 0;

    for (void** p = (void**)*head; p != 0; p = (void**)*p) {
        if (p[2] == dupFn && p[3] == setFn && p[4] == freeFn) {
            ERR_put_error(0x10, 0xd3, 0x6c, 0, 0);
            return 0;
        }
    }

    if (data != 0) {
        void** node = (void**)CRYPTO_malloc(0x14, kEcLibC, 0x23a);
        if (node == 0)
            return 0;
        node[1] = data;
        node[2] = dupFn;
        node[3] = setFn;
        node[4] = freeFn;
        node[0] = *head;
        *head = node;
    }
    return 1;
}

// @ 0x011b1d20  EC_KEY_new_by_curve_name-ish: allocate a 0xa8 EC_KEY, initialise
// the BN fields, then run the method's init.
void* ec_key_new_by_method(void* meth)
{
    if (meth == 0) {
        ERR_put_error(0x10, 0x6c, 0x43, 0, 0);
        return 0;
    }
    if (*(void**)((char*)meth + 4) == 0) {
        ERR_put_error(0x10, 0x6c, 0x42, 0, 0);
        return 0;
    }
    int* key = (int*)CRYPTO_malloc(0xa8, kEcLibC, 0x5b);
    if (key == 0) {
        ERR_put_error(0x10, 0x6c, 0x41, 0, 0);
        return 0;
    }
    key[0]  = (int)meth;
    key[0x11] = 0;
    key[1]    = 0;
    BN_init(key + 2);
    BN_init(key + 7);
    key[0xc]  = 0;
    key[0xd]  = 0;
    key[0xe]  = 4;
    key[0xf]  = 0;
    key[0x10] = 0;

    typedef int (*Fn)(void*);
    if (((Fn)*(void**)((char*)meth + 4))(key) == 0) {
        CRYPTO_free_ref(key);
        return 0;
    }
    return key;
}

// @ 0x011b2140  EC_KEY_new_method(EC_KEY_METHOD* method)
int* ec_key_new_method(int* meth)
{
    if (meth == 0) {
        ERR_put_error(0x10, 0x79, 0x43, 0, 0);
        return 0;
    }
    if (*(int*)((char*)*meth + 0x24) == 0) {
        ERR_put_error(0x10, 0x79, 0x42, 0, 0);
        return 0;
    }
    int* key = (int*)CRYPTO_malloc(0x44, kEcLibC, 0x2c4);
    if (key == 0) {
        ERR_put_error(0x10, 0x79, 0x41, 0, 0);
        return 0;
    }
    int* m = (int*)*meth;
    *key = (int)m;
    typedef int (*Fn)(void*);
    if (((Fn)m[9])(key) == 0) {          // m[9] == *(meth + 0x24)
        CRYPTO_free(key);
        return 0;
    }
    return key;
}

// @ 0x011b2d60  EC_KEY_set_public_key_affine_coordinates(EC_KEY* key, EC_POINT* pub,
//                                                     BIGNUM* x, BIGNUM* y)
int ec_key_set_public_key_affine_coordinates(int key, void* pub, void* x, void* y)
{
    if (pub == 0) {
        ERR_put_error(0x10, 0x6f, 0x43, 0, 0);
        return 0;
    }
    if (*(int*)(key + 4) == 0) {
        int* k = ec_key_new_method((int*)key);
        *(int**)(key + 4) = k;
        if (k == 0)
            return 0;
    }
    if (ec_compare_public_key(*(void**)(key + 4), pub) == 0)
        return 0;

    if (x == 0) {
        BN_set_word((void*)(key + 8), 0);
    } else if (BN_copy((void*)(key + 8), x) == 0) {
        return 0;
    }

    if (y == 0) {
        BN_set_word((void*)(key + 0x1c), 0);
    } else if (BN_copy((void*)(key + 0x1c), y) == 0) {
        return 0;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// crypto/ecdsa/ecs_lib.c
// ---------------------------------------------------------------------------
// The original receives the pre-set ECDSA_METHOD in edi (the caller sets it up);
// that register argument cannot be expressed in C, so it is read from a global.
extern void* s_ecdsaMethod;   // register-argument stand-in

// @ 0x011b3030  ECDSA_SIG_new / ECDSA_METHOD method-table init
void* ecdsa_sig_new(void)
{
    int* sig = (int*)CRYPTO_malloc(0x18, kEcsLibC, 0x6f);
    if (sig == 0) {
        ERR_put_error(0x2a, 100, 0x41, 0, 0);
        return 0;
    }
    *sig = 0;
    if (g_ecdsaDefaultMethod == 0)
        g_ecdsaDefaultMethod = ENGINE_get_default_ECDSA();
    sig[3] = (int)g_ecdsaDefaultMethod;
    sig[1] = (int)s_ecdsaMethod;
    if (sig[1] == 0) {
        sig[1] = (int)ECDSA_OpenSSL();
    }
    if (sig[1] != 0) {
        void* m = (void*)(int)ECDSA_METHOD_new((void*)sig[1]);
        sig[3] = (int)m;
        if (m == 0) {
            ERR_put_error(0x2a, 100, 0x26, 0, 0);
            CRYPTO_free_ref((void*)sig[1]);
            CRYPTO_free(sig);
            return 0;
        }
    }
    sig[2] = *(int*)((char*)sig[3] + 0x10);
    CRYPTO_new_ex_data(0xc, sig, sig + 4);
    return sig;
}

// @ 0x011b3460  ASN.1 INTEGER decode helper (used by d2i_ECDSA_SIG)
int ecs_int_decode(unsigned* out, unsigned char* in, int len, void* p4, void* p5, int param6)
{
    (void)p4; (void)p5;
    if (len < 5) {
        char negative = (len != 0) && ((in[0] & 0x80) != 0);
        unsigned v = 0;
        for (int i = 0; i < len; ++i) {
            unsigned char byte = negative ? (unsigned char)~in[i] : in[i];
            v = (v << 8) | (unsigned)byte;
        }
        if (negative)
            v = 0u - v - 1u;
        if (v != *(unsigned*)((char*)param6 + 0x14)) {
            *out = v;
            return 1;
        }
    }
    ERR_put_error(0xd, 0xa6, 0x80, 0, 0);
    return 0;
}

// ---------------------------------------------------------------------------
// EC_KEY_copy / EC_POINT method dispatch (0x011b2b70)
// ---------------------------------------------------------------------------
// @ 0x011b2b70  EC_KEY_copy(EC_KEY* dest, const EC_KEY* src)
int ec_key_copy(int dest, int src)
{
    if (*(int*)((char*)*(int**)dest + 0x10) == 0) {
        ERR_put_error(0x10, 0x6a, 0x42, 0, 0);
        return 0;
    }
    if (*(int**)dest != *(int**)src) {
        ERR_put_error(0x10, 0x6a, 0x65, 0, 0);
        return 0;
    }
    if (dest == src)
        return 1;

    int* lhead = (int*)(dest + 0x44);
    EC_EX_DATA_free_all_data(lhead);

    for (int* node = *(int**)(src + 0x44); node != 0; node = (int*)node[0]) {
        typedef int (*DupFn)(int);
        int dup = ((DupFn)node[2])(node[1]);
        if (dup == 0)
            return 0;
        if (ec_ex_data_set_data((void**)(dest + 0x44), (void*)dup,
                                (void*)node[2], (void*)node[3], (void*)node[4]) == 0)
            return 0;
    }

    if (*(int*)(src + 4) == 0) {
        if (*(int*)(dest + 4) != 0) {
            EC_POINT_clear_free(*(void**)(dest + 4));
            *(int*)(dest + 4) = 0;
        }
    } else {
        if (*(int*)(dest + 4) == 0) {
            int* k = ec_key_new_method((int*)dest);
            *(int**)(dest + 4) = k;
            if (k == 0)
                return 0;
        }
        if (ec_compare_public_key(*(void**)(dest + 4), *(void**)(src + 4)) == 0)
            return 0;
    }

    if (BN_copy((void*)(dest + 8), (const void*)(src + 8)) == 0)
        return 0;
    if (BN_copy((void*)(dest + 0x1c), (const void*)(src + 0x1c)) == 0)
        return 0;

    *(int*)(dest + 0x30) = *(int*)(src + 0x30);
    *(int*)(dest + 0x34) = *(int*)(src + 0x34);
    *(int*)(dest + 0x38) = *(int*)(src + 0x38);

    int old = *(int*)(dest + 0x3c);
    if (*(int*)(src + 0x3c) != 0) {
        if (old != 0)
            CRYPTO_free((void*)old);
        int n = *(int*)(src + 0x40);
        *(int*)(dest + 0x3c) = (int)CRYPTO_malloc(n, kEcLibC, 0xe6);
        if (*(int*)(dest + 0x3c) == 0)
            return 0;
        if (eastl_vector_do_insert_value(*(void**)(dest + 0x3c), *(void**)(src + 0x3c),
                               *(int*)(src + 0x40)) == 0)
            return 0;
        *(int*)(dest + 0x40) = *(int*)(src + 0x40);
        typedef int (*Fn)(void*, void*);
        return ((Fn)*(void**)((char*)*(void**)dest + 0x10))((void*)dest, (void*)src);
    }

    if (old != 0)
        CRYPTO_free((void*)old);
    *(int*)(dest + 0x3c) = 0;
    *(int*)(dest + 0x40) = 0;
    typedef int (*Fn)(void*, void*);
    return ((Fn)*(void**)((char*)*(void**)dest + 0x10))((void*)dest, (void*)src);
}

// @ 0x011c0744  BN_copy wrapper used for the 0x3c/0x40 blob

// ---------------------------------------------------------------------------
// crypto/asn1/a_time.c
// ---------------------------------------------------------------------------
// @ 0x011b1c70  ASN1_TIME_set_string / generalized-vs-utc dispatch
int asn1_time_set_string(int a, int t, int n)
{
    char tm[0x24];
    int* p = (int*)OPENSSL_gmtime((const void*)t, tm);
    if (p == 0) {
        ERR_put_error(0xd, 0xaf, 0xad, 0, 0);
        return 0;
    }
    if (p[5] > 0x31 && p[5] < 0x96)
        return asn1_gentime_helper(a, t, n);
    return asn1_utctime_helper(a, t, n);
}


// ---------------------------------------------------------------------------
// bn_sqr_comba4 -- squares the 4-word value `pa` into the 8-word value `r`.
// 16-bit half-limb multiplication with explicit carry propagation, exactly as
// the comba schoolbook expansion in bn_mul.c / bn_sqr.c does it.
// ---------------------------------------------------------------------------
// @ 0x011b1520
void bn_sqr_comba4(unsigned* r, const unsigned* pa)
{
    const unsigned *puVar1;
    unsigned uVar2, uVar3, uVar4, uVar5, uVar6, uVar8;
    int      iVar7, iVar9;
    unsigned local_8, local_4;
    unsigned carry = 0;

    puVar1 = pa;
    uVar2 = *pa & 0xffff;
    uVar6 = *pa >> 0x10;
    uVar3 = uVar2 * uVar6 * 0x20000;
    local_4 = uVar6 * uVar6 + (uVar2 * uVar6 >> 0xf);
    uVar2 = uVar2 * uVar2 + uVar3;
    if (uVar2 < uVar3) {
      local_4 = local_4 + 1;
    }
    *r = uVar2;
    iVar7 = (unsigned)*(unsigned short *)((int)pa + 6) * (unsigned)*(unsigned short *)((int)pa + 2);
    uVar3 = (unsigned)*(unsigned short *)((int)pa + 6) * (unsigned)(unsigned short)*pa;
    uVar2 = (unsigned)(unsigned short)pa[1] * (unsigned)*(unsigned short *)((int)pa + 2) + uVar3;
    if (uVar2 < uVar3) {
      iVar7 = iVar7 + 0x10000;
    }
    uVar3 = (unsigned)(unsigned short)pa[1] * (unsigned)(unsigned short)*pa + uVar2 * 0x10000;
    iVar7 = iVar7 + (uVar2 >> 0x10);
    if (uVar3 < uVar2 * 0x10000) {
      iVar7 = iVar7 + 1;
    }
    uVar2 = (unsigned)(iVar7 < 0);
    iVar7 = iVar7 * 2;
    if ((int)uVar3 < 0) {
      iVar7 = iVar7 + 1;
    }
    local_4 = local_4 + uVar3 * 2;
    if ((local_4 < uVar3 * 2) && (iVar7 = iVar7 + 1, iVar7 == 0)) {
      uVar2 = uVar2 + 1;
    }
    r[1] = local_4;
    uVar6 = pa[1] & 0xffff;
    uVar8 = pa[1] >> 0x10;
    uVar3 = uVar6 * uVar8 * 0x20000;
    uVar4 = uVar6 * uVar6 + uVar3;
    uVar6 = uVar8 * uVar8 + (uVar6 * uVar8 >> 0xf);
    if (uVar4 < uVar3) {
      uVar6 = uVar6 + 1;
    }
    if (iVar7 + uVar4 < uVar4) {
      uVar6 = uVar6 + 1;
    }
    local_8 = (unsigned)(uVar2 + uVar6 < uVar6);
    iVar9 = (unsigned)*(unsigned short *)((int)pa + 10) * (unsigned)*(unsigned short *)((int)pa + 2);
    uVar8 = (unsigned)*(unsigned short *)((int)pa + 10) * (unsigned)(unsigned short)*pa;
    uVar3 = (unsigned)(unsigned short)pa[2] * (unsigned)*(unsigned short *)((int)pa + 2) + uVar8;
    if (uVar3 < uVar8) {
      iVar9 = iVar9 + 0x10000;
    }
    iVar9 = iVar9 + (uVar3 >> 0x10);
    uVar8 = (unsigned)(unsigned short)pa[2] * (unsigned)(unsigned short)*pa + uVar3 * 0x10000;
    if (uVar8 < uVar3 * 0x10000) {
      iVar9 = iVar9 + 1;
    }
    if (iVar9 < 0) {
      local_8 = local_8 + 1;
    }
    uVar3 = iVar9 * 2;
    if ((int)uVar8 < 0) {
      uVar3 = uVar3 + 1;
    }
    uVar4 = iVar7 + uVar4 + uVar8 * 2;
    if ((uVar4 < uVar8 * 2) && (uVar3 = uVar3 + 1, uVar3 == 0)) {
      local_8 = local_8 + 1;
    }
    uVar2 = uVar2 + uVar6 + uVar3;
    if (uVar2 < uVar3) {
      local_8 = local_8 + 1;
    }
    r[2] = uVar4;
    iVar7 = (unsigned)*(unsigned short *)((int)pa + 0xe) * (unsigned)*(unsigned short *)((int)pa + 2);
    uVar6 = (unsigned)*(unsigned short *)((int)pa + 0xe) * (unsigned)(unsigned short)*pa;
    uVar3 = (unsigned)(unsigned short)pa[3] * (unsigned)*(unsigned short *)((int)pa + 2) + uVar6;
    if (uVar3 < uVar6) {
      iVar7 = iVar7 + 0x10000;
    }
    iVar7 = iVar7 + (uVar3 >> 0x10);
    uVar6 = (unsigned)(unsigned short)pa[3] * (unsigned)(unsigned short)*pa + uVar3 * 0x10000;
    if (uVar6 < uVar3 * 0x10000) {
      iVar7 = iVar7 + 1;
    }
    local_4 = (unsigned)(iVar7 < 0);
    uVar3 = iVar7 * 2;
    if ((int)uVar6 < 0) {
      uVar3 = uVar3 + 1;
    }
    uVar2 = uVar2 + uVar6 * 2;
    if ((uVar2 < uVar6 * 2) && (uVar3 = uVar3 + 1, uVar3 == 0)) {
      local_4 = local_4 + 1;
    }
    if (local_8 + uVar3 < uVar3) {
      local_4 = local_4 + 1;
    }
    iVar7 = (unsigned)*(unsigned short *)((int)pa + 10) * (unsigned)*(unsigned short *)((int)pa + 6);
    uVar4 = (unsigned)*(unsigned short *)((int)pa + 10) * (unsigned)(unsigned short)pa[1];
    uVar6 = (unsigned)(unsigned short)pa[2] * (unsigned)*(unsigned short *)((int)pa + 6) + uVar4;
    if (uVar6 < uVar4) {
      iVar7 = iVar7 + 0x10000;
    }
    uVar4 = (unsigned)(unsigned short)pa[2] * (unsigned)(unsigned short)pa[1] + uVar6 * 0x10000;
    iVar7 = iVar7 + (uVar6 >> 0x10);
    if (uVar4 < uVar6 * 0x10000) {
      iVar7 = iVar7 + 1;
    }
    if (iVar7 < 0) {
      local_4 = local_4 + 1;
    }
    uVar6 = iVar7 * 2;
    if ((int)uVar4 < 0) {
      uVar6 = uVar6 + 1;
    }
    uVar2 = uVar2 + uVar4 * 2;
    if ((uVar2 < uVar4 * 2) && (uVar6 = uVar6 + 1, uVar6 == 0)) {
      local_4 = local_4 + 1;
    }
    uVar3 = local_8 + uVar3 + uVar6;
    if (uVar3 < uVar6) {
      local_4 = local_4 + 1;
    }
    r[3] = uVar2;
    uVar6 = pa[2] & 0xffff;
    uVar8 = pa[2] >> 0x10;
    uVar2 = uVar6 * uVar8 * 0x20000;
    uVar4 = uVar6 * uVar6 + uVar2;
    uVar6 = uVar8 * uVar8 + (uVar6 * uVar8 >> 0xf);
    if (uVar4 < uVar2) {
      uVar6 = uVar6 + 1;
    }
    uVar3 = uVar3 + uVar4;
    if (uVar3 < uVar4) {
      uVar6 = uVar6 + 1;
    }
    pa = (unsigned *)(unsigned)(local_4 + uVar6 < uVar6);
    iVar7 = (unsigned)*(unsigned short *)((int)puVar1 + 0xe) * (unsigned)*(unsigned short *)((int)puVar1 + 6);
    uVar4 = (unsigned)*(unsigned short *)((int)puVar1 + 0xe) * (unsigned)(unsigned short)puVar1[1];
    uVar2 = (unsigned)(unsigned short)puVar1[3] * (unsigned)*(unsigned short *)((int)puVar1 + 6) + uVar4;
    if (uVar2 < uVar4) {
      iVar7 = iVar7 + 0x10000;
    }
    iVar7 = iVar7 + (uVar2 >> 0x10);
    uVar4 = (unsigned)(unsigned short)puVar1[3] * (unsigned)(unsigned short)puVar1[1] + uVar2 * 0x10000;
    if (uVar4 < uVar2 * 0x10000) {
      iVar7 = iVar7 + 1;
    }
    if (iVar7 < 0) {
      pa = (unsigned *)((int)pa + 1);
    }
    uVar2 = iVar7 * 2;
    if ((int)uVar4 < 0) {
      uVar2 = uVar2 + 1;
    }
    uVar3 = uVar3 + uVar4 * 2;
    if ((uVar3 < uVar4 * 2) && (uVar2 = uVar2 + 1, uVar2 == 0)) {
      pa = (unsigned *)((int)pa + 1);
    }
    uVar6 = local_4 + uVar6 + uVar2;
    if (uVar6 < uVar2) {
      pa = (unsigned *)((int)pa + 1);
    }
    r[4] = uVar3;
    iVar7 = (unsigned)*(unsigned short *)((int)puVar1 + 0xe) * (unsigned)*(unsigned short *)((int)puVar1 + 10);
    uVar3 = (unsigned)*(unsigned short *)((int)puVar1 + 0xe) * (unsigned)(unsigned short)puVar1[2];
    uVar2 = (unsigned)(unsigned short)puVar1[3] * (unsigned)*(unsigned short *)((int)puVar1 + 10) + uVar3;
    if (uVar2 < uVar3) {
      iVar7 = iVar7 + 0x10000;
    }
    uVar3 = (unsigned)(unsigned short)puVar1[3] * (unsigned)(unsigned short)puVar1[2] + uVar2 * 0x10000;
    iVar7 = iVar7 + (uVar2 >> 0x10);
    if (uVar3 < uVar2 * 0x10000) {
      iVar7 = iVar7 + 1;
    }
    uVar4 = (unsigned)(iVar7 < 0);
    uVar2 = iVar7 * 2;
    if ((int)uVar3 < 0) {
      uVar2 = uVar2 + 1;
    }
    uVar6 = uVar6 + uVar3 * 2;
    if ((uVar6 < uVar3 * 2) && (uVar2 = uVar2 + 1, uVar2 == 0)) {
      uVar4 = uVar4 + 1;
    }
    if (carry + uVar2 < uVar2) {
      uVar4 = uVar4 + 1;
    }
    r[5] = uVar6;
    uVar3 = puVar1[3] & 0xffff;
    uVar5 = puVar1[3] >> 0x10;
    uVar8 = uVar3 * uVar5 * 0x20000;
    uVar6 = uVar3 * uVar3 + uVar8;
    iVar7 = uVar5 * uVar5 + (uVar3 * uVar5 >> 0xf);
    if (uVar6 < uVar8) {
      iVar7 = iVar7 + 1;
    }
    uVar2 = (int)pa + uVar2 + uVar6;
    if (uVar2 < uVar6) {
      iVar7 = iVar7 + 1;
    }
    r[6] = uVar2;
    r[7] = iVar7 + uVar4;
    return;
}
