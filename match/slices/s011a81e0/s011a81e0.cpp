// Slice s011a81e0 (gold1 #9) -- OpenSSL 0.9.8g (lib_cblock / lib_openssl).
//
// Reproduces the exact upstream OpenSSL 0.9.8g source bodies (macros/types hand
// expanded) compiled with the Spore build's OpenSSL flags, which is the route to
// byte-identity for the statically linked OpenSSL block (see
// third_party/cblock_resolution.csv).  ssl3_accept lives in its own translation
// unit (ssl3_accept.cpp) because the whole s3_srvr.c is needed for its static
// helpers' register calling conventions.
//
// Flags: /O2 /arch:SSE /MD /Gy /TP  (see manifest.txt)
#include "types.h"
#include <string.h>

// ===========================================================================
// crypto/asn1/evp_asn1.c
// ===========================================================================
struct asn1_string_st {
    int length;
    int type;
    unsigned char *data;
    long flags;
};
struct asn1_type_st {
    int type;
    union {
        char *ptr;
        struct asn1_string_st *octet_string;
    } value;
};
typedef struct asn1_type_st ASN1_TYPE;

extern "C" void __cdecl ERR_put_error(int lib, int func, int reason, int file, int line);

// @ 0x011a9e70  ASN1_TYPE_get_octetstring
extern "C" int __cdecl ASN1_TYPE_get_octetstring(ASN1_TYPE *a, unsigned char *data, int max_len)
{
    int ret, num;
    unsigned char *p;

    if ((a->type != 4) || (a->value.octet_string == 0)) {
        ERR_put_error(0xd, 0x87, 0x6d, 0, 0);   /* ASN1_F_ASN1_TYPE_GET_OCTETSTRING, ASN1_R_DATA_IS_WRONG */
        return -1;
    }
    p = a->value.octet_string->data;            /* M_ASN1_STRING_data */
    ret = a->value.octet_string->length;        /* M_ASN1_STRING_length */
    if (ret < max_len)
        num = ret;
    else
        num = max_len;
    memcpy(data, p, num);
    return ret;
}

// ===========================================================================
// crypto/engine/eng_lib.c
// ===========================================================================
struct crypto_ex_data_st { void *sk; int dummy; };
struct engine_st {
    char pad0[0x2c];
    void (__cdecl *destroy)(struct engine_st *);
    char pad1[0x4c - 0x2c - 4];
    int struct_ref;
    char pad2[0x54 - 0x4c - 4];
    struct crypto_ex_data_st ex_data;
};
typedef struct engine_st ENGINE;

extern "C" int  __cdecl CRYPTO_add_lock(int *pointer, int amount, int type, const char *file, int line);
extern "C" void __cdecl CRYPTO_free_ex_data(int class_index, void *obj, void *ad);
extern "C" void __cdecl CRYPTO_free(void *addr);

// @ 0x011a9db0  engine_free_util
extern "C" int __cdecl engine_free_util(ENGINE *e, int locked)
{
    int i;

    if (e == 0) {
        ERR_put_error(0x26, 0x6c, 0x43, 0, 0);   /* ENGINE_F_ENGINE_FREE_UTIL, ERR_R_PASSED_NULL_PARAMETER */
        return 0;
    }
    if (locked)
        i = CRYPTO_add_lock(&e->struct_ref, -1, 0x1e, "eng_lib.c", 0x74);  /* CRYPTO_LOCK_ENGINE */
    else {
        --e->struct_ref;
        i = e->struct_ref;
    }
    if (i > 0) return 1;
    if (e->destroy)
        e->destroy(e);
    CRYPTO_free_ex_data(9, e, &e->ex_data);      /* CRYPTO_EX_INDEX_ENGINE */
    CRYPTO_free(e);                              /* OPENSSL_free */
    return 1;
}

// ===========================================================================
// crypto/evp/e_rc2.c
// ===========================================================================
// @ 0x011a9590  rc2_magic_to_meth (static; first argument in EAX)
static int rc2_magic_to_meth(int i)
{
    if (i == 0x3a) return 128;                   /* RC2_128_MAGIC */
    else if (i == 0x78) return 64;               /* RC2_64_MAGIC */
    else if (i == 0xa0) return 40;               /* RC2_40_MAGIC */
    else {
        ERR_put_error(6, 0x6d, 0x6c, 0, 0);      /* EVP_F_RC2_MAGIC_TO_METH, EVP_R_UNSUPPORTED_KEY_SIZE */
        return 0;
    }
}

// rc2_magic_to_meth is a static helper whose argument arrives in EAX because its
// only caller (rc2_get_asn1_type_and_iv) is in the same translation unit.  This
// minimal anchor reproduces that caller-side convention so the helper body comes
// out byte-identical.  It is not one of the slice's functions.
int __cdecl rc2_convert_anchor(int num)
{
    return rc2_magic_to_meth(num);
}

// ===========================================================================
// crypto/evp/c_alld.c
// ===========================================================================
extern "C" void *__cdecl EVP_md2(void);
extern "C" void *__cdecl EVP_md4(void);
extern "C" void *__cdecl EVP_md5(void);
extern "C" void *__cdecl EVP_sha(void);
extern "C" void *__cdecl EVP_dss(void);
extern "C" void *__cdecl EVP_sha1(void);
extern "C" void *__cdecl EVP_dss1(void);
extern "C" void *__cdecl EVP_ecdsa(void);
extern "C" void *__cdecl EVP_ripemd160(void);
extern "C" void *__cdecl EVP_sha224(void);
extern "C" void *__cdecl EVP_sha256(void);
extern "C" void *__cdecl EVP_sha384(void);
extern "C" void __cdecl EVP_add_digest(void *md);
extern "C" void __cdecl OBJ_NAME_add(const char *name, int type, const char *data);

// @ 0x011a8ae0  OpenSSL_add_all_digests
// (the compiled order differs from the upstream 0.9.8g c_alld.c: the *_alias
//  calls precede the digest they alias, and SHA512 is absent).
extern "C" void __cdecl OpenSSL_add_all_digests(void)
{
    EVP_add_digest(EVP_md2());
    EVP_add_digest(EVP_md4());
    OBJ_NAME_add("ssl2-md5", 0x8001, "MD5");
    OBJ_NAME_add("ssl3-md5", 0x8001, "MD5");
    EVP_add_digest(EVP_md5());
    EVP_add_digest(EVP_sha());
    EVP_add_digest(EVP_dss());
    OBJ_NAME_add("ssl3-sha1", 0x8001, "SHA1");
    OBJ_NAME_add("RSA-SHA1-2", 0x8001, "RSA-SHA1");
    EVP_add_digest(EVP_sha1());
    OBJ_NAME_add("DSA-SHA1-old", 0x8001, "DSA-SHA1");
    OBJ_NAME_add("DSS1", 0x8001, "DSA-SHA1");
    OBJ_NAME_add("dss1", 0x8001, "DSA-SHA1");
    EVP_add_digest(EVP_dss1());
    EVP_add_digest(EVP_ecdsa());
    OBJ_NAME_add("ripemd", 0x8001, "RIPEMD160");
    OBJ_NAME_add("rmd160", 0x8001, "RIPEMD160");
    EVP_add_digest(EVP_ripemd160());
    EVP_add_digest(EVP_sha224());
    EVP_add_digest(EVP_sha256());
    EVP_add_digest(EVP_sha384());
}

// ===========================================================================
// crypto/evp/c_allc.c
// ===========================================================================
extern "C" void *__cdecl EVP_des_cfb(void);
extern "C" void *__cdecl EVP_des_cfb1(void);
extern "C" void *__cdecl EVP_des_cfb8(void);
extern "C" void *__cdecl EVP_des_ede_cfb(void);
extern "C" void *__cdecl EVP_des_ede3_cfb(void);
extern "C" void *__cdecl EVP_des_ofb(void);
extern "C" void *__cdecl EVP_des_ede_ofb(void);
extern "C" void *__cdecl EVP_des_ede3_ofb(void);
extern "C" void *__cdecl EVP_desx_cbc(void);
extern "C" void *__cdecl EVP_des_cbc(void);
extern "C" void *__cdecl EVP_des_ede_cbc(void);
extern "C" void *__cdecl EVP_des_ede3_cbc(void);
extern "C" void *__cdecl EVP_des_ecb(void);
extern "C" void *__cdecl EVP_des_ede(void);
extern "C" void *__cdecl EVP_des_ede3(void);
extern "C" void *__cdecl EVP_rc4(void);
extern "C" void *__cdecl EVP_rc4_40(void);
extern "C" void *__cdecl EVP_rc2_ecb(void);
extern "C" void *__cdecl EVP_rc2_cfb(void);
extern "C" void *__cdecl EVP_rc2_ofb(void);
extern "C" void *__cdecl EVP_rc2_cbc(void);
extern "C" void *__cdecl EVP_rc2_40_cbc(void);
extern "C" void *__cdecl EVP_rc2_64_cbc(void);
extern "C" void *__cdecl EVP_cast5_ecb(void);
extern "C" void *__cdecl EVP_cast5_cfb(void);
extern "C" void *__cdecl EVP_cast5_ofb(void);
extern "C" void *__cdecl EVP_cast5_cbc(void);
extern "C" void *__cdecl EVP_aes_128_ecb(void);
extern "C" void *__cdecl EVP_aes_128_cbc(void);
extern "C" void *__cdecl EVP_aes_128_cfb(void);
extern "C" void *__cdecl EVP_aes_128_cfb1(void);
extern "C" void *__cdecl EVP_aes_128_cfb8(void);
extern "C" void *__cdecl EVP_aes_128_ofb(void);
extern "C" void *__cdecl EVP_aes_192_ecb(void);
extern "C" void *__cdecl EVP_aes_192_cbc(void);
extern "C" void *__cdecl EVP_aes_192_cfb(void);
extern "C" void *__cdecl EVP_aes_192_cfb1(void);
extern "C" void *__cdecl EVP_aes_192_cfb8(void);
extern "C" void *__cdecl EVP_aes_192_ofb(void);
extern "C" void *__cdecl EVP_aes_256_ecb(void);
extern "C" void *__cdecl EVP_aes_256_cbc(void);
extern "C" void *__cdecl EVP_aes_256_cfb(void);
extern "C" void *__cdecl EVP_aes_256_cfb1(void);
extern "C" void *__cdecl EVP_aes_256_cfb8(void);
extern "C" void *__cdecl EVP_aes_256_ofb(void);
extern "C" void __cdecl EVP_add_cipher(void *cipher);
extern "C" void __cdecl PKCS12_PBE_add(void);
extern "C" void __cdecl PKCS5_PBE_add(void);

// @ 0x011a8c30  OpenSSL_add_all_ciphers
// Spore build: DES, RC4, RC2, CAST and AES enabled; IDEA/SEED/BF/RC5/CAMELLIA off.
extern "C" void __cdecl OpenSSL_add_all_ciphers(void)
{
    EVP_add_cipher(EVP_des_cfb());
    EVP_add_cipher(EVP_des_cfb1());
    EVP_add_cipher(EVP_des_cfb8());
    EVP_add_cipher(EVP_des_ede_cfb());
    EVP_add_cipher(EVP_des_ede3_cfb());
    EVP_add_cipher(EVP_des_ofb());
    EVP_add_cipher(EVP_des_ede_ofb());
    EVP_add_cipher(EVP_des_ede3_ofb());
    EVP_add_cipher(EVP_desx_cbc());
    OBJ_NAME_add("DESX", 0x8002, "DESX-CBC");
    OBJ_NAME_add("desx", 0x8002, "DESX-CBC");
    EVP_add_cipher(EVP_des_cbc());
    OBJ_NAME_add("DES", 0x8002, "DES-CBC");
    OBJ_NAME_add("des", 0x8002, "DES-CBC");
    EVP_add_cipher(EVP_des_ede_cbc());
    EVP_add_cipher(EVP_des_ede3_cbc());
    OBJ_NAME_add("DES3", 0x8002, "DES-EDE3-CBC");
    OBJ_NAME_add("des3", 0x8002, "DES-EDE3-CBC");
    EVP_add_cipher(EVP_des_ecb());
    EVP_add_cipher(EVP_des_ede());
    EVP_add_cipher(EVP_des_ede3());
    EVP_add_cipher(EVP_rc4());
    EVP_add_cipher(EVP_rc4_40());
    EVP_add_cipher(EVP_rc2_ecb());
    EVP_add_cipher(EVP_rc2_cfb());
    EVP_add_cipher(EVP_rc2_ofb());
    EVP_add_cipher(EVP_rc2_cbc());
    EVP_add_cipher(EVP_rc2_40_cbc());
    EVP_add_cipher(EVP_rc2_64_cbc());
    OBJ_NAME_add("RC2", 0x8002, "RC2-CBC");
    OBJ_NAME_add("rc2", 0x8002, "RC2-CBC");
    EVP_add_cipher(EVP_cast5_ecb());
    EVP_add_cipher(EVP_cast5_cfb());
    EVP_add_cipher(EVP_cast5_ofb());
    EVP_add_cipher(EVP_cast5_cbc());
    OBJ_NAME_add("CAST", 0x8002, "CAST5-CBC");
    OBJ_NAME_add("cast", 0x8002, "CAST5-CBC");
    OBJ_NAME_add("CAST-cbc", 0x8002, "CAST5-CBC");
    OBJ_NAME_add("cast-cbc", 0x8002, "CAST5-CBC");
    EVP_add_cipher(EVP_aes_128_ecb());
    EVP_add_cipher(EVP_aes_128_cbc());
    EVP_add_cipher(EVP_aes_128_cfb());
    EVP_add_cipher(EVP_aes_128_cfb1());
    EVP_add_cipher(EVP_aes_128_cfb8());
    EVP_add_cipher(EVP_aes_128_ofb());
    OBJ_NAME_add("AES128", 0x8002, "AES-128-CBC");
    OBJ_NAME_add("aes128", 0x8002, "AES-128-CBC");
    EVP_add_cipher(EVP_aes_192_ecb());
    EVP_add_cipher(EVP_aes_192_cbc());
    EVP_add_cipher(EVP_aes_192_cfb());
    EVP_add_cipher(EVP_aes_192_cfb1());
    EVP_add_cipher(EVP_aes_192_cfb8());
    EVP_add_cipher(EVP_aes_192_ofb());
    OBJ_NAME_add("AES192", 0x8002, "AES-192-CBC");
    OBJ_NAME_add("aes192", 0x8002, "AES-192-CBC");
    EVP_add_cipher(EVP_aes_256_ecb());
    EVP_add_cipher(EVP_aes_256_cbc());
    EVP_add_cipher(EVP_aes_256_cfb());
    EVP_add_cipher(EVP_aes_256_cfb1());
    EVP_add_cipher(EVP_aes_256_cfb8());
    EVP_add_cipher(EVP_aes_256_ofb());
    OBJ_NAME_add("AES256", 0x8002, "AES-256-CBC");
    OBJ_NAME_add("aes256", 0x8002, "AES-256-CBC");
    PKCS12_PBE_add();
    PKCS5_PBE_add();
}
