// slice s01177a10 -- OpenSSL 0.9.8g base64 BIO and RSA/AES glue (lib_cblock / lib_openssl).
// Module flags: /O2 /MD /Gy /TP (no SSE needed).  See manifest.txt / nonmatching.txt / partial.txt.
//
// The instrumented names come from a static OpenSSL link: AES_set_encrypt_key, EVP_Encode*,
// BIO_*, RSA_new, BN_*, CRYPTO_*.  Only the signatures of the callees matter here (call
// targets are masked relocations).
#include "types.h"
#include <string.h>

typedef unsigned int u32;

// ---- OpenSSL callees (cdecl unless noted) ---------------------------------
void* __cdecl CRYPTO_malloc(int num, const char* file, int line);
void  __cdecl CRYPTO_free(void* p);
void  __cdecl ERR_put_error(int lib, int func, int reason, const char* file, int line);
int   __cdecl CRYPTO_new_ex_data(int class_id, void* obj, void* ad);
int   __cdecl CRYPTO_free_ex_data(int class_id, void* obj, void* ad);
int   __cdecl FUN_011861a0();
void* __cdecl FUN_011874c0();
int   __cdecl FUN_011836c0(int p);
void  __cdecl FUN_011835c0(void* p);
void* __cdecl FUN_011874d0(void* p);
void  __cdecl FUN_01183740(void* p);
void  __cdecl BIO_clear_flags(void* b, int flags);
void  __cdecl BIO_copy_next_retry(void* b);
int   __cdecl BIO_test_flags(void* b, int flags);
void  __cdecl EVP_EncodeInit(void* ctx);
int   __cdecl EVP_EncodeBlock(unsigned char* out, const unsigned char* in, int inlen);
void  __cdecl EVP_EncodeUpdate(void* ctx, unsigned char* out, int* outl, const unsigned char* in, int inl);
int   __cdecl EVP_DecodeInit(void* ctx);
int   __cdecl EVP_DecodeUpdate(void* ctx, unsigned char* out, int* outl, const unsigned char* in, int inl);
int   __cdecl EVP_DecodeBlock(unsigned char* out, const unsigned char* in, int inlen);
int   __cdecl FUN_01177070(void* b, void* out, int len);
int   __cdecl FUN_0116fc0(void* b, void* out, int len);
void* __cdecl FUN_01187a80();
void  __cdecl FUN_01187b00();
int   __cdecl FUN_01187b90(void* ctx);
void* __cdecl FUN_01187ad0();
int   __cdecl rsa_get_public_exp(void* a, void* b, void* c);
int   __cdecl RAND_status();
void  __cdecl RAND_add(const void* buf, int num, double entropy);
int   __cdecl FUN_011875c0(int a, void* b, void* c, void* d, void* e, void* f);
void* __cdecl CRYPTO_thread_id();
void  __cdecl FUN_011875b0(void* p, void* id);
void  __cdecl BN_BLINDING_set_thread_id(void* p, void* id);
void  __cdecl BN_CTX_end(void* ctx);
void  __cdecl BN_CTX_free(void* ctx);
void  __cdecl BN_free(void* p);

// @ 0x01178710  (AES_set_encrypt_key -- see partial.txt; real body not reproduced)
int __cdecl FUN_01178710(const unsigned char* userKey, int bits, void* key);
int __cdecl AES_set_decrypt_key(const void* userKey, int bits, void* key);
// @ 0x011799f0  (RSA_new)
void* __cdecl FUN_011799f0(int param_1);

extern int DAT_016f1950;

// ---------------------------------------------------------------------------
// @ 0x01179f50
// ---------------------------------------------------------------------------
int __cdecl FUN_01179f50(void)
{
    return (int)FUN_011799f0(0);
}

// ---------------------------------------------------------------------------
// @ 0x011784b0
// ---------------------------------------------------------------------------
int __cdecl FUN_011784b0(int* a, void* key, int unused, int enc)
{
    int f = *(int*)(*(int*)a + 0x10) & 7;
    int r;
    if (f == 3 || f == 4 || enc != 0) {
        void* out = (void*)a[0x18];
        int bits = a[0x16] * 8;
        r = FUN_01178710((const unsigned char*)key, bits, out);
    } else {
        void* out = (void*)a[0x18];
        int bits = a[0x16] * 8;
        r = AES_set_decrypt_key(key, bits, out);
    }
    if (r < 0) {
        ERR_put_error(6, 0x85, 0x8f, 0, 0);
        return 0;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x011799f0  (RSA_new)
// ---------------------------------------------------------------------------
void* __cdecl FUN_011799f0(int param_1)
{
    char* p = (char*)CRYPTO_malloc(0x58, ".\\crypto\\rsa\\rsa_lib.c", 0x84);
    if (p == 0) {
        ERR_put_error(4, 0x6a, 0x41, 0, 0);
        return 0;
    }
    if (DAT_016f1950 == 0)
        DAT_016f1950 = FUN_011861a0();
    *(int*)(p + 8) = DAT_016f1950;
    if (param_1 != 0) {
        if (FUN_011836c0(param_1) == 0) {
            ERR_put_error(4, 0x6a, 0x26, 0, 0);
            FUN_011835c0(p);
            return 0;
        }
        *(int*)(p + 0xc) = param_1;
    } else {
        *(int*)(p + 0xc) = (int)FUN_011874c0();
    }
    if (*(int*)(p + 0xc) != 0) {
        int i = (int)FUN_011874d0(*(void**)(p + 0xc));
        *(int*)(p + 8) = i;
        if (i == 0) {
            ERR_put_error(4, 0x6a, 0x26, 0, 0);
            FUN_01183740(*(void**)(p + 0xc));
            FUN_011835c0(p);
            return 0;
        }
    }
    *(int*)(p + 0x00) = 0;
    *(int*)(p + 0x04) = 0;
    *(int*)(p + 0x10) = 0;
    *(int*)(p + 0x14) = 0;
    *(int*)(p + 0x18) = 0;
    *(int*)(p + 0x1c) = 0;
    *(int*)(p + 0x20) = 0;
    *(int*)(p + 0x24) = 0;
    *(int*)(p + 0x28) = 0;
    *(int*)(p + 0x2c) = 0;
    *(int*)(p + 0x38) = 1;
    *(int*)(p + 0x40) = 0;
    *(int*)(p + 0x44) = 0;
    *(int*)(p + 0x48) = 0;
    *(int*)(p + 0x50) = 0;
    *(int*)(p + 0x54) = 0;
    *(int*)(p + 0x4c) = 0;
    *(int*)(p + 0x3c) = *(int*)(*(int*)(p + 8) + 0x24);
    CRYPTO_new_ex_data(6, p, p + 0x30);
    void* cb = *(void**)(*(int*)(p + 8) + 0x1c);
    if (cb != 0) {
        if (((int(__cdecl*)(void*))cb)(p) == 0) {
            if (*(int*)(p + 0xc) != 0)
                FUN_01183740(*(void**)(p + 0xc));
            CRYPTO_free_ex_data(6, p, p + 0x30);
            FUN_011835c0(p);
            p = 0;
        }
    }
    return p;
}

// ---------------------------------------------------------------------------
// @ 0x01179dd0  (RSA_blinding_on)
// ---------------------------------------------------------------------------
int __cdecl FUN_01179dd0(int param_1, int param_2)
{
    int iVar6 = 0;
    int iVar2 = param_2;
    if (param_2 == 0) {
        iVar2 = (int)FUN_01187a80();
        if (iVar2 == 0)
            return 0;
    }
    FUN_01187b00();
    int iVar3 = FUN_01187b90((void*)iVar2);
    if (iVar3 == 0) {
        ERR_put_error(4, 0x88, 0x41, 0, 0);
    } else {
        iVar3 = *(int*)(param_1 + 0x14);
        if (iVar3 == 0) {
            iVar3 = rsa_get_public_exp(*(void**)(param_1 + 0x18),
                                       *(void**)(param_1 + 0x1c),
                                       *(void**)(param_1 + 0x20));
            if (iVar3 == 0) {
                ERR_put_error(4, 0x88, 0x8c, 0, 0);
                goto done;
            }
        }
        iVar6 = RAND_status();
        if (iVar6 == 0) {
            int* pi = *(int**)(param_1 + 0x18);
            if (pi != 0 && *pi != 0)
                RAND_add(pi, pi[2] * 4, 0.0);
        }
        u32* pu;
        int local_14, local_10, local_c, local_8; u32 local_4;
        if ((*(u32*)(param_1 + 0x3c) & 0x100) == 0) {
            int* src = *(int**)(param_1 + 0x10);
            local_14 = src[0]; local_10 = src[1]; local_c = src[2]; local_8 = src[3];
            local_4 = (src[4] & 0xfffffffe) | 6;
            pu = (u32*)&local_14;
        } else {
            pu = *(u32**)(param_1 + 0x10);
        }
        iVar6 = FUN_011875c0(0, (void*)iVar3, pu, (void*)iVar2,
                             *(void**)(*(int*)(param_1 + 8) + 0x18),
                             *(void**)(param_1 + 0x40));
        if (iVar6 == 0) {
            ERR_put_error(4, 0x88, 3, 0, 0);
        } else {
            FUN_011875b0((void*)iVar6, CRYPTO_thread_id());
        }
    }
done:
    BN_CTX_end((void*)iVar2);
    if (param_2 == 0)
        BN_CTX_free((void*)iVar2);
    if (*(int*)(param_1 + 0x14) == 0)
        BN_free((void*)iVar3);
    return iVar6;
}

// ---------------------------------------------------------------------------
// @ 0x01177dd0  (BIO_f_base64 enc_write)
// ---------------------------------------------------------------------------
int __cdecl FUN_01177dd0(int param_1, void* param_2, int param_3)
{
    int sVar2 = param_3;
    int* piVar1 = *(int**)(param_1 + 0x20);
    BIO_clear_flags((void*)param_1, 0xf);
    if (piVar1[4] != 1) {
        piVar1[4] = 1;
        piVar1[0] = 0;
        piVar1[1] = 0;
        piVar1[2] = 0;
        EVP_EncodeInit(piVar1 + 7);
    }
    int iVar6 = piVar1[0] - piVar1[1];
    while (0 < iVar6) {
        int n = FUN_01177070(*(void**)(param_1 + 0x24), (char*)piVar1 + piVar1[1] + 0x7c, iVar6);
        if (n < 1) {
            BIO_copy_next_retry((void*)param_1);
            return n;
        }
        piVar1[1] += n;
        iVar6 -= n;
    }
    piVar1[1] = 0;
    piVar1[0] = 0;
    if (param_2 == 0 || param_3 <= 0)
        return 0;
    do {
        int sVar3 = param_3;
        if (param_3 > 0x400)
            sVar3 = 0x400;
        u32 uVar4 = (u32)BIO_test_flags((void*)param_1, 0xffffffff);
        if ((uVar4 & 0x100) == 0) {
            EVP_EncodeUpdate(piVar1 + 7, (unsigned char*)(piVar1 + 0x1f), piVar1,
                             (const unsigned char*)param_2, sVar3);
        } else if (piVar1[2] < 1) {
            if (sVar3 < 3) {
                memcpy((char*)piVar1 + 0x65a, param_2, sVar3);
                piVar1[2] = sVar3;
                return sVar2;
            }
            sVar3 = (sVar3 / 3) * 3;
            piVar1[0] = EVP_EncodeBlock((unsigned char*)(piVar1 + 0x1f),
                                        (const unsigned char*)param_2, sVar3);
        } else {
            sVar3 = 3 - piVar1[2];
            if (param_3 < sVar3)
                sVar3 = param_3;
            memcpy((char*)piVar1 + piVar1[2] + 0x65a, param_2, sVar3);
            piVar1[2] += sVar3;
            if (piVar1[2] < 3)
                return sVar2;
            piVar1[0] = EVP_EncodeBlock((unsigned char*)(piVar1 + 0x1f),
                                        (const unsigned char*)((char*)piVar1 + 0x65a), piVar1[2]);
            piVar1[2] = 0;
        }
        param_3 -= sVar3;
        param_2 = (char*)param_2 + sVar3;
        iVar6 = piVar1[0];
        piVar1[1] = 0;
        while (0 < iVar6) {
            int n = FUN_01177070(*(void**)(param_1 + 0x24), (char*)piVar1 + piVar1[1] + 0x7c, iVar6);
            if (n < 1) {
                BIO_copy_next_retry((void*)param_1);
                return sVar2;
            }
            piVar1[1] += n;
            iVar6 -= n;
        }
        piVar1[0] = 0;
        piVar1[1] = 0;
    } while (param_3 > 0);
    return sVar2;
}

// ---------------------------------------------------------------------------
// @ 0x01178710  (AES_set_encrypt_key)
// The OpenSSL key schedule was not re-derived.  This body keeps the same external
// behaviour contract but is incomplete; see partial.txt.
// ---------------------------------------------------------------------------
int __cdecl FUN_01178710(const unsigned char* userKey, int bits, void* key)
{
    if (userKey == 0 || key == 0)
        return -1;
    if (bits != 0x80 && bits != 0xc0 && bits != 0x100)
        return -2;
    *(int*)((char*)key + 0xf0) = (bits == 0xc0) ? 12 : ((bits == 0x100) ? 14 : 10);
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x01177a10  (BIO_f_base64 enc_read)
// Not reconstructed; see partial.txt.
// ---------------------------------------------------------------------------
int __cdecl FUN_01177a10(int param_1, void* param_2, int param_3)
{
    (void)param_1; (void)param_2; (void)param_3;
    return 0;
}
