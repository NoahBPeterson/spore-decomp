// slice s01179f60 -- statically linked OpenSSL 0.9.8g BIGNUM / RSA_sign core (lib_cblock).
// Module flags: /O2 /MD /Gy /EHsc /TP  (same as the adjacent OpenSSL slice s01177a10).
// Call targets are masked relocations, so only callee *signatures* matter.
#include "types.h"

typedef unsigned int u32;

// ---- OpenSSL callees (cdecl unless noted) ---------------------------------
void* __cdecl CRYPTO_malloc(int num, const char* file, int line);
void  __cdecl FUN_011835c0(void* p);                                  // OPENSSL_free
void  __cdecl ERR_put_error(int lib, int func, int reason, const char* file, int line);
int   __cdecl BN_copy(void* a, void* b);
void* __cdecl bn_expand2(void* a, int words);
void  __cdecl BN_free(void* a);
void  __cdecl BN_set_word(void* a, unsigned int w);
int   __cdecl BN_mul_word(void* a, unsigned int w);
int   __cdecl BN_add_word(void* a, unsigned int w);
unsigned int __cdecl BN_div_word(void* a, unsigned int w);
int   __cdecl BN_num_bits(void* a);
void  __cdecl OPENSSL_cleanse(void* p, int n);

int   __cdecl RSA_size(void* r);
int   __cdecl RSA_private_encrypt(int flen, int from, int to, void* rsa, int padding);
int   __cdecl RSA_public_decrypt(int flen, int from, int to, void* rsa, int padding);

void* __cdecl FUN_0117f770(int a);
void* __cdecl FUN_0117b100(int a);
int   __cdecl FUN_011895b0(int** a, ...);
int*  __cdecl FUN_01189590(int a, int* b, int c);
void  __cdecl FUN_011895d0(int* a);
int   __cdecl FUN_01190020(void* fn, const char* name, int a, int b, int c, int d);
int   __cdecl FUN_01193a90(int a, void* b, void* c, void* d);
int   __cdecl FUN_01196970(void);
void* __cdecl FUN_01177470(int a);
void  __cdecl FUN_01177260(void* a, int b, int c, int d);

int   __cdecl sk_num(void* sk);
int   __cdecl sk_push(void* sk, void* p);
void  __cdecl sk_zero(void* sk);
void  __cdecl sk_free(void* sk);
void* __cdecl FUN_0117df20(void);
void  __cdecl BIO_snprintf(char* buf, char* lim, const char* fmt, ...);

void  __cdecl ssl_set_cert_masks(void* s, void* masks);
int   __cdecl ssl_clear_bad_session(void* s);
void  __cdecl ssl_clear_cipher_ctx(void* s);
void  __cdecl SSL_SESSION_free(void* s);
void  __cdecl BUF_MEM_free(void* p);
void* __cdecl BIO_pop(void* b);
void* __cdecl BIO_push(void* a, void* b);
int   __cdecl BIO_int_ctrl(void* b, int cmd, long larg, int iarg);
int   __cdecl ASN1_TYPE_get(void* a);
int   __cdecl OBJ_obj2nid(void* a);
void* __cdecl __iob_func(void);
int   __cdecl fprintf(void* f, const char* fmt, ...);

extern char DAT_014dfcc4[];

// ---- OpenSSL structure shapes used by the RSA signature path --------------
struct EVP_MD_ST;
struct RSA {
    char pad0[8];
    void* meth;             // +0x08
};

// ===========================================================================
// @ 0x01179f60  RSA_sign
// ===========================================================================
unsigned int __cdecl FUN_01179f60(int param_1, int param_2, int param_3,
                                  int param_4, int* param_5, int param_6)
{
    int local_30 = 0;
    int* local_28;
    int* local_24;
    int local_20;
    int local_1c;
    int local_18[2];
    int local_10[2];
    int local_8;
    int iVar4 = param_6;

    if (((*(unsigned char*)(param_6 + 0x3c) & 0x40) != 0)) {
        int (*pcVar1)(int, int, int, int, int*, int) =
            *(int(**)(int, int, int, int, int*, int))(*(int*)(param_6 + 8) + 0x2c);
        if (pcVar1 != 0)
            return pcVar1(param_1, param_2, param_3, param_4, param_5, param_6);
    }
    int iVar5;
    if (param_1 == 0x72) {
        iVar5 = 0x24;
        if (param_3 != 0x24) {
            ERR_put_error(4, 0x75, 0x83, 0, 0);
            return 0;
        }
    } else {
        local_28 = local_18;
        iVar5 = (int)FUN_0117f770(param_1);
        *local_28 = iVar5;
        if (*local_28 == 0) {
            ERR_put_error(4, 0x75, 0x75, 0, 0);
            return 0;
        }
        if (*(int*)(*local_28 + 0xc) == 0) {
            ERR_put_error(4, 0x75, 0x74, 0, 0);
            return 0;
        }
        local_20 = 5;
        local_1c = 0;
        local_28[1] = (int)&local_20;
        local_24 = local_10;
        local_8 = param_2;
        local_10[0] = param_3;
        iVar5 = FUN_011895b0(&local_28);
        param_2 = 0;
    }
    int iVar3 = RSA_size((void*)iVar4);
    if (iVar3 - 0xb < iVar5) {
        ERR_put_error(4, 0x75, 0x70, 0, 0);
        return 0;
    }
    if (param_1 != 0x72) {
        param_2 = (int)CRYPTO_malloc(iVar3 + 1, ".\\crypto\\rsa\\rsa_sign.c", 0x7a);
        if (param_2 == 0) {
            ERR_put_error(4, 0x75, 0x41, 0, 0);
            return 0;
        }
        param_6 = param_2;
        FUN_011895b0(&local_28, &param_6);
        local_30 = param_2;
    }
    iVar4 = RSA_private_encrypt(iVar5, param_2, param_4, (void*)iVar4, 1);
    if (0 < iVar4)
        *param_5 = iVar4;
    if (param_1 != 0x72) {
        OPENSSL_cleanse((void*)local_30, iVar3 + 1);
        FUN_011835c0((void*)local_30);
    }
    return (unsigned int)(0 < iVar4);
}

// ===========================================================================
// @ 0x0117a150  RSA_verify
// ===========================================================================
int __cdecl FUN_0117a150(int param_1, int* param_2, unsigned int param_3,
                         int param_4, int param_5, int param_6)
{
    int local_8 = 0;
    int iStack_4;
    int iVar2 = RSA_size((void*)param_6);
    if (param_5 != iVar2) {
        ERR_put_error(4, 0x77, 0x77, 0, 0);
        return 0;
    }
    if ((*(unsigned char*)(param_6 + 0x3c) & 0x40) != 0) {
        int (*pcVar1)(int, int*, unsigned int, int, int, int) =
            *(int(**)(int, int*, unsigned int, int, int, int))(*(int*)(param_6 + 8) + 0x30);
        if (pcVar1 != 0)
            return pcVar1(param_1, param_2, param_3, param_4, param_5, param_6);
    }
    iVar2 = (int)CRYPTO_malloc(param_5, ".\\crypto\\rsa\\rsa_sign.c", 0xa4);
    if (iVar2 == 0) {
        ERR_put_error(4, 0x77, 0x41, 0, 0);
        return 0;
    }
    if ((param_1 == 0x72) && (param_3 != 0x24)) {
        ERR_put_error(4, 0x77, 0x83, 0, 0);
        goto LAB_0117a393;
    }
    int iVar4 = RSA_public_decrypt(param_5, param_4, iVar2, (void*)param_6, 1);
    if (iVar4 < 1)
        goto LAB_0117a393;
    if (param_1 == 0x72) {
        if (iVar4 == 0x24) {
            iVar4 = iVar2 - (int)param_2;
            unsigned int uVar7 = 0x24;
            do {
                if (*(int*)(iVar4 + (int)param_2) != *param_2)
                    goto LAB_0117a273;
                uVar7 = uVar7 - 4;
                param_2 = param_2 + 1;
            } while (3 < uVar7);
            local_8 = 1;
        } else {
LAB_0117a273:
            ERR_put_error(4, 0x77, 0x68, 0, 0);
        }
        goto LAB_0117a393;
    }
    iStack_4 = iVar2;
    int* piVar5 = FUN_01189590(0, &iStack_4, iVar4);
    if (piVar5 == 0)
        goto LAB_0117a393;
    if ((iStack_4 != iVar4 + iVar2) ||
        ((*(int*)(*piVar5 + 4) != 0 &&
          (iVar4 = ASN1_TYPE_get(*(void**)(*piVar5 + 4)), iVar4 != 5))))
        goto LAB_0117a374;
    iVar4 = OBJ_obj2nid(*(void**)*piVar5);
    if (iVar4 == param_1) {
LAB_0117a31d:
        if (*(unsigned int*)piVar5[1] != param_3) {
LAB_0117a374:
            {
                unsigned int uVar3 = 0x68;
                ERR_put_error(4, 0x77, uVar3, 0, 0);
                FUN_011895d0(piVar5);
                goto LAB_0117a393;
            }
        }
        int* piVar8 = (int*)((unsigned int*)piVar5[1])[2];
        for (; 3 < param_3; param_3 = param_3 - 4) {
            if (*param_2 != *piVar8)
                goto LAB_0117a374;
            piVar8 = piVar8 + 1;
            param_2 = param_2 + 1;
        }
        if ((param_3 != 0) &&
            (((char)*piVar8 != (char)*param_2 ||
              ((1 < param_3 &&
                ((*(char*)((int)piVar8 + 1) != *(char*)((int)param_2 + 1) ||
                  ((2 < param_3 &&
                    (*(char*)((int)piVar8 + 2) != *(char*)((int)param_2 + 2)))))))))))
            goto LAB_0117a374;
        local_8 = 1;
    } else {
        if (param_1 == 4) {
            if (iVar4 == 8) {
LAB_0117a305:
                {
                    const char* fmt = "signature has problems, re-make with post SSLeay045\n";
                    void* pFVar6 = __iob_func();
                    fprintf((char*)pFVar6 + 2 * 0x14, fmt);
                }
                goto LAB_0117a31d;
            }
        } else if ((param_1 == 3) && (iVar4 == 7))
            goto LAB_0117a305;
        {
            unsigned int uVar3 = 100;
            ERR_put_error(4, 0x77, uVar3, 0, 0);
        }
    }
    FUN_011895d0(piVar5);
LAB_0117a393:
    OPENSSL_cleanse((void*)iVar2, param_5);
    FUN_011835c0((void*)iVar2);
    return local_8;
}

// ===========================================================================
// @ 0x0117a3c0  BN_bn2dec
// ===========================================================================
char* __cdecl FUN_0117a3c0(int param_1)
{
    char cVar1;
    int bVar2 = 0;
    int local_c = 0;
    int iVar3 = BN_num_bits((void*)param_1);
    int iVar8 = (iVar3 * 3) / 1000 + (iVar3 * 3) / 10;
    iVar3 = iVar8 + 2;
    int* puVar4 = (int*)CRYPTO_malloc((iVar3 / 9) * 4 + 4, ".\\crypto\\bn\\bn_print.c", 0x76);
    char* pcVar5 = (char*)CRYPTO_malloc(iVar8 + 5, ".\\crypto\\bn\\bn_print.c", 0x77);
    if ((pcVar5 == 0) || (puVar4 == 0)) {
        ERR_put_error(3, 0x68, 0x41, 0, 0);
    } else {
        local_c = (int)FUN_0117b100(param_1);
        if (local_c != 0) {
            if (*(int*)(local_c + 4) == 0) {
                *pcVar5 = '0';
                pcVar5[1] = '\0';
                bVar2 = 1;
            } else {
                char* pcVar7 = pcVar5;
                if (*(int*)(local_c + 0xc) != 0) {
                    *pcVar5 = '-';
                    pcVar7 = pcVar5 + 1;
                }
                iVar8 = *(int*)(local_c + 4);
                int* puVar9 = puVar4;
                while (iVar8 != 0) {
                    unsigned int uVar6 = BN_div_word((void*)local_c, 1000000000);
                    *puVar9 = uVar6;
                    puVar9 = puVar9 + 1;
                    iVar8 = *(int*)(local_c + 4);
                }
                BIO_snprintf(pcVar7, pcVar5 + (iVar3 - (int)pcVar7) + 3, DAT_014dfcc4,
                             puVar9[-1]);
                cVar1 = *pcVar7;
                while (cVar1 != '\0') {
                    pcVar7 = pcVar7 + 1;
                    cVar1 = *pcVar7;
                }
                while (puVar9 = puVar9 - 1, puVar9 != puVar4) {
                    BIO_snprintf(pcVar7, pcVar5 + (iVar3 - (int)pcVar7) + 3, "%09lu",
                                 puVar9[-1]);
                    cVar1 = *pcVar7;
                    while (cVar1 != '\0') {
                        pcVar7 = pcVar7 + 1;
                        cVar1 = *pcVar7;
                    }
                }
                bVar2 = 1;
            }
        }
    }
    if (puVar4 != 0)
        FUN_011835c0(puVar4);
    if (local_c != 0)
        BN_free((void*)local_c);
    if ((!bVar2) && (pcVar5 != 0)) {
        FUN_011835c0(pcVar5);
        return 0;
    }
    return pcVar5;
}

// ===========================================================================
// @ 0x0117a9d0  BN_new
// ===========================================================================
void* __cdecl FUN_0117a9d0(void)
{
    int* puVar1 = (int*)CRYPTO_malloc(0x14, ".\\crypto\\bn\\bn_lib.c", 0x12e);
    if (puVar1 == 0) {
        ERR_put_error(3, 0x71, 0x41, 0, 0);
        return 0;
    }
    puVar1[4] = 1;
    puVar1[1] = 0;
    puVar1[3] = 0;
    puVar1[2] = 0;
    *puVar1 = 0;
    return puVar1;
}

// ===========================================================================
// @ 0x0117aa10  bn_expand   (size arrives in EAX -- custom register convention)
// ===========================================================================
void* __cdecl FUN_0117aa10(int* param_1, int bits)
{
    int* puVar4;
    int* puVar6;
    int* puVar5;
    int iVar7;
    if (0xffffff < bits) {
        ERR_put_error(3, 0x78, 0x72, 0, 0);
        return 0;
    }
    if ((*(unsigned char*)(param_1 + 4) & 2) == 0) {
        puVar4 = (int*)CRYPTO_malloc(bits * 4, ".\\crypto\\bn\\bn_lib.c", 0x150);
        if (puVar4 == 0) {
            ERR_put_error(3, 0x78, 0x41, 0, 0);
            return 0;
        }
        puVar6 = (int*)*param_1;
        if (puVar6 != 0) {
            puVar5 = puVar4;
            for (iVar7 = param_1[1] >> 2; 0 < iVar7; iVar7 = iVar7 + -1) {
                int uVar1 = puVar6[1];
                int uVar2 = puVar6[2];
                int uVar3 = puVar6[3];
                *puVar5 = *puVar6;
                puVar5[1] = uVar1;
                puVar5[2] = uVar2;
                puVar5[3] = uVar3;
                puVar5 = puVar5 + 4;
                puVar6 = puVar6 + 4;
            }
            unsigned int uVar8 = param_1[1] & 3;
            if (uVar8 != 1) {
                if (uVar8 != 2) {
                    if (uVar8 != 3)
                        return puVar4;
                    puVar5[2] = puVar6[2];
                }
                puVar5[1] = puVar6[1];
            }
            *puVar5 = *puVar6;
        }
        return puVar4;
    }
    ERR_put_error(3, 0x78, 0x69, 0, 0);
    return 0;
}

// ===========================================================================
// @ 0x0117ac80  BN_bin2bn
// ===========================================================================
int* __cdecl FUN_0117ac80(unsigned char* param_1, int param_2, int* param_3)
{
    int* piVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    unsigned int uVar4;
    int iVar5;
    int* local_4 = 0;

    if (param_3 == 0) {
        local_4 = (int*)CRYPTO_malloc(0x14, ".\\crypto\\bn\\bn_lib.c", 0x12e);
        if (local_4 == 0) {
            ERR_put_error(3, 0x71, 0x41, 0, 0);
            local_4 = 0;
        } else {
            local_4[4] = 1;
            local_4[1] = 0;
            local_4[3] = 0;
            local_4[2] = 0;
            *local_4 = 0;
        }
        param_3 = local_4;
        if (local_4 == 0)
            return 0;
    }
    if (param_2 == 0) {
        param_3[1] = 0;
        return param_3;
    }
    iVar5 = ((unsigned int)(param_2 - 1) >> 2) + 1;
    piVar1 = param_3;
    if (param_3[2] < iVar5)
        piVar1 = (int*)bn_expand2(param_3, iVar5);
    if (piVar1 != 0) {
        param_3[1] = iVar5;
        param_3[3] = 0;
        iVar5 = iVar5 * 4;
        uVar2 = 0;
        uVar3 = (param_2 - 1U) & 3;
        do {
            uVar2 = uVar2 << 8 | (unsigned int)*param_1;
            param_2 = param_2 + -1;
            param_1 = param_1 + 1;
            uVar4 = uVar3 - 1;
            if (uVar3 == 0) {
                iVar5 = iVar5 + -4;
                *(unsigned int*)(iVar5 + *param_3) = uVar2;
                uVar2 = 0;
                uVar4 = 3;
            }
            uVar3 = uVar4;
        } while (param_2 != 0);
        if (0 < param_3[1]) {
            piVar1 = (int*)(*param_3 + -4 + param_3[1] * 4);
            do {
                iVar5 = *piVar1;
                piVar1 = piVar1 + -1;
                if (iVar5 != 0)
                    return param_3;
                param_3[1] = param_3[1] + -1;
            } while (0 < param_3[1]);
        }
        return param_3;
    }
    if (local_4 != 0)
        BN_free(local_4);
    return 0;
}

// ===========================================================================
// @ 0x0117b100  BN_dup
// ===========================================================================
void* __cdecl FUN_0117b100(int param_1)
{
    int* puVar1;
    int iVar2;
    if (param_1 == 0)
        return 0;
    puVar1 = (int*)CRYPTO_malloc(0x14, ".\\crypto\\bn\\bn_lib.c", 0x12e);
    if (puVar1 == 0) {
        ERR_put_error(3, 0x71, 0x41, 0, 0);
        return 0;
    }
    puVar1[4] = 1;
    puVar1[1] = 0;
    puVar1[3] = 0;
    puVar1[2] = 0;
    *puVar1 = 0;
    iVar2 = BN_copy(puVar1, (void*)param_1);
    if (iVar2 == 0) {
        BN_free(puVar1);
        return 0;
    }
    return puVar1;
}

// ===========================================================================
// @ 0x0117b1e0
// ===========================================================================
void __cdecl FUN_0117b1e0(int param_1, int param_2, int param_3, int param_4)
{
    FUN_01190020((void*)0x011910c0, "X509 CRL", param_1, param_2, param_3, param_4);
}

// ===========================================================================
// @ 0x0117b210
// ===========================================================================
void __cdecl FUN_0117b210(int param_1, int param_2, int param_3, int param_4)
{
    FUN_01190020((void*)0x01192e50, "DH PARAMETERS", param_1, param_2, param_3, param_4);
}

// ===========================================================================
// @ 0x0117b410
// ===========================================================================
struct SSL_METHOD_B410 {
    char pad[0x18];
    int (__cdecl* fn)(void* s);
};

int __cdecl FUN_0117b410(int param_1)
{
    if (*(int*)(param_1 + 0x20) == 0) {
        ERR_put_error(0x14, 0xdf, 0x114, 0, 0);
        return -1;
    }
    if ((*(unsigned char*)(param_1 + 0x30) & 2) != 0) {
        *(int*)(param_1 + 0x18) = 1;
        return 0;
    }
    SSL_METHOD_B410* m = (SSL_METHOD_B410*)*(void**)(param_1 + 8);
    return m->fn((void*)param_1);
}

// ===========================================================================
// @ 0x0117b460
// ===========================================================================
struct SSL_METHOD_B460 {
    char pad[0x1c];
    int (__cdecl* fn)(void* s);
};

int __cdecl FUN_0117b460(int param_1)
{
    if (*(int*)(param_1 + 0x20) == 0) {
        ERR_put_error(0x14, 0x10e, 0x114, 0, 0);
        return -1;
    }
    if ((*(unsigned char*)(param_1 + 0x30) & 2) != 0)
        return 0;
    SSL_METHOD_B460* m = (SSL_METHOD_B460*)*(void**)(param_1 + 8);
    return m->fn((void*)param_1);
}

// ===========================================================================
// @ 0x0117b4a0
// ===========================================================================
struct SSL_METHOD_B4A0 {
    char pad[0x20];
    int (__cdecl* fn)(void* s);
};

int __cdecl FUN_0117b4a0(int param_1)
{
    if (*(int*)(param_1 + 0x20) == 0) {
        ERR_put_error(0x14, 0xd0, 0x114, 0, 0);
        return -1;
    }
    if ((*(unsigned char*)(param_1 + 0x30) & 1) != 0) {
        *(int*)(param_1 + 0x18) = 1;
        ERR_put_error(0x14, 0xd0, 0xcf, 0, 0);
        return -1;
    }
    SSL_METHOD_B4A0* m = (SSL_METHOD_B4A0*)*(void**)(param_1 + 8);
    return m->fn((void*)param_1);
}

// ===========================================================================
// @ 0x0117b780
// ===========================================================================
int __cdecl FUN_0117b780(int* param_1, int param_2)
{
    int iVar1 = FUN_01193a90(*param_1, param_1 + 1, param_1 + 2, (void*)param_2);
    if (iVar1 != 0) {
        iVar1 = sk_num((void*)iVar1);
        if (iVar1 == 0) {
            ERR_put_error(0x14, 0x10d, 0xb9, 0, 0);
            return 0;
        }
        return 1;
    }
    return 0;
}

// ===========================================================================
// @ 0x0117b840
// ===========================================================================
int __cdecl FUN_0117b840(int param_1, int param_2, int param_3, int* param_4)
{
    int iVar1 = param_1;
    int iVar2 = (*(int(**)(int, int))(*(int*)(param_1 + 8) + 0x4c))(0, 0);
    if (param_3 % iVar2 != 0) {
        ERR_put_error(0x14, 0xa1, 0x97, 0, 0);
        return 0;
    }
    if ((param_4 == 0) || (param_1 = *param_4, param_1 == 0)) {
        param_1 = (int)FUN_0117df20();
    } else {
        sk_zero((void*)param_1);
    }
    int iVar4 = 0;
    if (0 < param_3) {
        do {
            int iVar3 = (*(int(**)(int))(*(int*)(iVar1 + 8) + 0x48))(param_2);
            param_2 = param_2 + iVar2;
            if ((iVar3 != 0) && (iVar3 = sk_push((void*)param_1, (void*)iVar3), iVar3 == 0)) {
                ERR_put_error(0x14, 0xa1, 0x41, 0, 0);
                if ((param_4 == 0) || (*param_4 == 0))
                    sk_free((void*)param_1);
                return 0;
            }
            iVar4 = iVar4 + iVar2;
        } while (iVar4 < param_3);
    }
    if (param_4 != 0)
        *param_4 = param_1;
    return param_1;
}

// ===========================================================================
// @ 0x0117bf80
// ===========================================================================
int __cdecl FUN_0117bf80(int param_1)
{
    int iVar1 = *(int*)(param_1 + 0x94);
    ssl_set_cert_masks((void*)iVar1, *(void**)(*(int*)(param_1 + 0x58) + 0x358));
    unsigned int uVar2 = *(unsigned int*)(*(int*)(*(int*)(param_1 + 0x58) + 0x358) + 0xc);
    if (((uVar2 & 0x40) != 0) || ((uVar2 & 0x4000) != 0))
        return *(int*)(iVar1 + 0x50);
    if ((uVar2 & 2) != 0)
        return *(int*)(iVar1 + 0x40);
    if ((uVar2 & 4) != 0)
        return *(int*)(iVar1 + 0x48);
    if ((uVar2 & 0x200) != 0)
        return *(int*)(iVar1 + 0x38);
    if ((uVar2 & 0x100) != 0)
        return *(int*)(iVar1 + 0x28 + (unsigned int)(*(int*)(iVar1 + 0x28) == 0) * 8);
    if ((uVar2 & 0x2000) == 0)
        ERR_put_error(0x14, 0xb6, 0x44, 0, 0);
    return 0;
}

// ===========================================================================
// @ 0x0117c040
// ===========================================================================
int __cdecl FUN_0117c040(int param_1, int param_2)
{
    unsigned int uVar1 = *(unsigned int*)(param_2 + 0xc);
    int iVar2 = *(int*)(param_1 + 0x94);
    int iVar3;
    if (((uVar1 & 0x200) != 0) && (iVar3 = *(int*)(iVar2 + 0x3c), iVar3 != 0))
        return iVar3;
    if ((uVar1 & 0x100) != 0) {
        iVar3 = *(int*)(iVar2 + 0x34);
        if (iVar3 == 0)
            return *(int*)(iVar2 + 0x2c);
    } else if (((uVar1 & 0x4000) == 0) || (iVar3 = *(int*)(iVar2 + 0x54), iVar3 == 0)) {
        ERR_put_error(0x14, 0xb7, 0x44, 0, 0);
        iVar3 = 0;
    }
    return iVar3;
}

// ===========================================================================
// @ 0x0117c300
// ===========================================================================
int __cdecl FUN_0117c300(int param_1, int param_2)
{
    int iVar2 = *(int*)(param_1 + 0x14);
    if (iVar2 == 0) {
        int uVar1 = FUN_01196970();
        iVar2 = (int)FUN_01177470(uVar1);
        if (iVar2 == 0)
            return 0;
        *(int*)(param_1 + 0x14) = iVar2;
    } else if (iVar2 == *(int*)(param_1 + 0x10)) {
        int uVar1 = (int)BIO_pop(*(void**)(param_1 + 0x10));
        *(int*)(param_1 + 0x10) = uVar1;
    }
    FUN_01177260((void*)iVar2, 1, 0, 0);
    int iVar3 = BIO_int_ctrl((void*)iVar2, 0x75, 1, 0);
    if (iVar3 == 0) {
        ERR_put_error(0x14, 0xb8, 7, 0, 0);
        return 0;
    }
    if (param_2 != 0) {
        if (*(int*)(param_1 + 0x10) != iVar2) {
            int uVar1 = (int)BIO_push((void*)iVar2, *(void**)(param_1 + 0x10));
            *(int*)(param_1 + 0x10) = uVar1;
            return 1;
        }
    } else if (*(int*)(param_1 + 0x10) == iVar2) {
        int uVar1 = (int)BIO_pop((void*)iVar2);
        *(int*)(param_1 + 0x10) = uVar1;
    }
    return 1;
}

// ===========================================================================
// @ 0x0117c440
// ===========================================================================
int __cdecl FUN_0117c440(int* param_1)
{
    if (param_1[2] == 0) {
        ERR_put_error(0x14, 0xa4, 0xbc, 0, 0);
        return 0;
    }
    if (ssl_clear_bad_session(param_1) != 0) {
        SSL_SESSION_free((void*)param_1[0x2f]);
        param_1[0x2f] = 0;
    }
    param_1[0x34] = 0;
    param_1[0x1b] = 0;
    param_1[0xc] = 0;
    if (param_1[10] != 0) {
        ERR_put_error(0x14, 0xa4, 0x44, 0, 0);
        return 0;
    }
    param_1[1] = 0;
    param_1[0xd] = ((-(unsigned int)(param_1[9] != 0) & 0x1000) + 0x1000) | 0x4000;
    int uVar1 = *(int*)param_1[2];
    *param_1 = uVar1;
    param_1[0x41] = uVar1;
    param_1[6] = 1;
    param_1[0xe] = 0xf0;
    if (param_1[0xf] != 0) {
        BUF_MEM_free((void*)param_1[0xf]);
        param_1[0xf] = 0;
    }
    ssl_clear_cipher_ctx(param_1);
    param_1[0x40] = 0;
    if (param_1[7] == 0 && param_1[0x2f] == 0 && *(int*)param_1[2] != *(int*)param_1[0x36]) {
        (*(void(**)(void*))((char*)param_1[2] + 0xc))((void*)param_1);
        param_1[2] = *(int*)param_1[0x36];
        if ((*(int(**)(void*))((char*)param_1[2] + 4))((void*)param_1) == 0)
            return 0;
    } else {
        (*(void(**)(void*))((char*)param_1[2] + 8))((void*)param_1);
    }
    return 1;
}
