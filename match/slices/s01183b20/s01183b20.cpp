// slice s01183b20 -- statically linked OpenSSL 0.9.8g RC4 + ex_data + buffer (lib_cblock).
// Module flags: /O2 /MD /Gy /TP  (same region as slices s01182870 / s011869d0).
// Call targets are masked relocations, so only callee *signatures* matter.
#include "types.h"

typedef unsigned int u32;

// ---- OpenSSL callees (cdecl unless noted) ---------------------------------
void* __cdecl CRYPTO_malloc(int num, const char* file, int line);
void* __cdecl CRYPTO_realloc(void* p, int num, const char* file, int line);
void* __cdecl CRYPTO_realloc_clean(void* p, int old, int num, const char* file, int line);
void  __cdecl FUN_011835c0(void* p);                                   // OPENSSL_free
void  __cdecl OPENSSL_cleanse(void* p, int n);
void  __cdecl ERR_put_error(int lib, int func, int reason, const char* file, int line);
void  __cdecl CRYPTO_lock(int mode, int type, const char* file, int line);
void* __cdecl operator_new__(void* p, int c, int n);                   // memset-ish

int   __cdecl FUN_0117df20(void);                                      // sk_new_null
int   __cdecl FUN_0117dde0(void* sk);                                  // sk_num
int   __cdecl sk_push(void* sk, void* p);
void  __cdecl sk_set(void* sk, int i, void* p);
void* __cdecl sk_value(void* sk, int i);
void  __cdecl sk_free(void* sk);
void* __cdecl lh_retrieve(void* lh, void* key);
void  __cdecl lh_insert(void* lh, void* data);
int   __cdecl ex_data_check(void);
char* __cdecl BUF_strlcpy(char* dst, char* src, u32 n);

// ---- globals --------------------------------------------------------------
extern u32 DAT_016f1c90;
extern void* DAT_016f1c8c;
extern unsigned char DAT_016f1c98;
extern u32 DAT_016f20c0, DAT_016f20c4;
extern unsigned char DAT_016f20ac;
extern double _DAT_016f20d0;
extern u32 DAT_016f20c8, DAT_016f20cc, DAT_016f20d8;

// ===========================================================================
// @ 0x01183b20  RC4
// ===========================================================================
struct RC4_KEY { u32 x; u32 y; u32 data[256]; };

void __cdecl FUN_01183b20(RC4_KEY* key, u32 len, const unsigned char* indata,
                          unsigned char* outdata)
{
    register u32* d;
    register u32 x, y, tx, ty;
    int i;
    x = key->x;
    y = key->y;
    d = key->data;

#define RC4_STEP(in, out) \
    x = ((x + 1) & 0xff); tx = d[x]; y = ((tx + y) & 0xff); ty = d[y]; \
    d[x] = ty; d[y] = tx; (out) = (unsigned char)(d[(tx + ty) & 0xff] ^ (in));

    for (i = 0; i < (int)(len & ~7u); i += 8) {
        RC4_STEP(indata[0], outdata[0]);
        RC4_STEP(indata[1], outdata[1]);
        RC4_STEP(indata[2], outdata[2]);
        RC4_STEP(indata[3], outdata[3]);
        RC4_STEP(indata[4], outdata[4]);
        RC4_STEP(indata[5], outdata[5]);
        RC4_STEP(indata[6], outdata[6]);
        RC4_STEP(indata[7], outdata[7]);
        indata += 8;
        outdata += 8;
    }
    for (i = len & 7; i != 0; i--) {
        RC4_STEP(indata[0], outdata[0]);
        indata++;
        outdata++;
    }
#undef RC4_STEP
    key->x = x;
    key->y = y;
}

// ===========================================================================
// @ 0x01183f70  ex_data_get_item
// ===========================================================================
u32* __cdecl FUN_01183f70(void)
{
    u32* puVar2;
    u32* puVar3;
    if ((DAT_016f1c90 == 0) && (ex_data_check() == 0))
        return 0;
    CRYPTO_lock(9, 2, ".\\crypto\\ex_data.c", 300);
    int key = 0;
    puVar2 = (u32*)lh_retrieve((void*)DAT_016f1c90, &key);
    if (puVar2 == 0) {
        puVar3 = (u32*)CRYPTO_malloc(0xc, ".\\crypto\\ex_data.c", 0x130);
        if (puVar3 != 0) {
            *puVar3 = 0;
            puVar3[2] = 0;
            int iVar1 = FUN_0117df20();
            puVar3[1] = iVar1;
            if (iVar1 == 0) {
                FUN_011835c0(puVar3);
            } else {
                lh_insert((void*)DAT_016f1c90, puVar3);
                puVar2 = puVar3;
            }
        }
    }
    CRYPTO_lock(10, 2, ".\\crypto\\ex_data.c", 0x141);
    if (puVar2 == 0)
        ERR_put_error(0xf, 0x69, 0x41, 0, 0);
    return puVar2;
}

// ===========================================================================
// @ 0x01184040  ex_data_new_index  (impl pointer arrives in EDI)
// ===========================================================================
int __cdecl FUN_01184040(int* impl, int param_1, int param_2, int param_3,
                         int param_4, int param_5)
{
    u32* puVar1 = (u32*)CRYPTO_malloc(0x14, ".\\crypto\\ex_data.c", 0x14f);
    if (puVar1 == 0) {
        ERR_put_error(0xf, 0x68, 0x41, 0, 0);
        return -1;
    }
    puVar1[0] = param_1;
    puVar1[1] = param_2;
    puVar1[2] = param_3;
    puVar1[4] = param_4;
    puVar1[3] = param_5;
    CRYPTO_lock(9, 2, ".\\crypto\\ex_data.c", 0x15a);
    int iVar2 = FUN_0117dde0((void*)impl[1]);
    if (iVar2 <= impl[2]) {
        iVar2 = -1;
        int iVar3;
        do {
            iVar3 = sk_push((void*)impl[1], 0);
            if (iVar3 == 0) {
                ERR_put_error(0xf, 0x68, 0x41, 0, 0);
                FUN_011835c0(puVar1);
                goto LAB_011840fa;
            }
            iVar3 = FUN_0117dde0((void*)impl[1]);
        } while (iVar3 <= impl[2]);
    }
    iVar2 = impl[2];
    impl[2] = iVar2 + 1;
    sk_set((void*)impl[1], iVar2, puVar1);
LAB_011840fa:
    CRYPTO_lock(10, 2, ".\\crypto\\ex_data.c", 0x167);
    return iVar2;
}

// ===========================================================================
// @ 0x01184320  sk_set (grow-and-set)
// ===========================================================================
int __cdecl FUN_01184320(int* param_1, int param_2, int param_3)
{
    if (*param_1 == 0) {
        int iVar1 = FUN_0117df20();
        *param_1 = iVar1;
        if (iVar1 == 0) {
            ERR_put_error(0xf, 0x66, 0x41, 0, 0);
            return 0;
        }
    }
    int iVar1 = FUN_0117dde0((void*)*param_1);
    while (1) {
        if (iVar1 > param_2) {
            sk_set((void*)*param_1, param_2, (void*)param_3);
            return 1;
        }
        int iVar2 = sk_push((void*)*param_1, 0);
        if (iVar2 == 0) break;
        iVar1 = iVar1 + 1;
    }
    ERR_put_error(0xf, 0x66, 0x41, 0, 0);
    return 0;
}

// ===========================================================================
// @ 0x011843b0  CRYPTO_new_ex_data
// ===========================================================================
int __cdecl FUN_011843b0(int param_1, int param_2, int* param_3)
{
    int iVar6 = 0;
    int iVar2 = (int)FUN_01183f70();
    if (iVar2 == 0)
        return 0;
    *param_3 = 0;
    CRYPTO_lock(5, 2, ".\\crypto\\ex_data.c", 0x199);
    int iVar3 = FUN_0117dde0(*(void**)(iVar2 + 4));
    if (0 < iVar3) {
        iVar6 = (int)CRYPTO_malloc(iVar3 * 4, ".\\crypto\\ex_data.c", 0x19d);
        if (iVar6 != 0) {
            for (int iVar5 = 0; iVar5 < iVar3; iVar5 = iVar5 + 1) {
                int uVar4 = (int)sk_value(*(void**)(iVar2 + 4), iVar5);
                *(int*)(iVar6 + iVar5 * 4) = uVar4;
            }
        }
    }
    CRYPTO_lock(6, 2, ".\\crypto\\ex_data.c", 0x1a4);
    if ((0 < iVar3) && (iVar6 == 0)) {
        ERR_put_error(0xf, 0x6c, 0x41, 0, 0);
        return 0;
    }
    for (int iVar2b = 0; iVar2b < iVar3; iVar2b = iVar2b + 1) {
        int iVar5 = *(int*)(iVar6 + iVar2b * 4);
        if ((iVar5 != 0) && (*(int*)(iVar5 + 8) != 0)) {
            int uVar4 = 0;
            if (*param_3 != 0) {
                iVar5 = FUN_0117dde0((void*)*param_3);
                if (iVar2b < iVar5)
                    uVar4 = (int)sk_value((void*)*param_3, iVar2b);
                else
                    uVar4 = 0;
            }
            u32* puVar1 = *(u32**)(iVar6 + iVar2b * 4);
            (*(void(**)(int, int, int*, int, u32, u32))(puVar1[2]))
                (param_2, uVar4, param_3, iVar2b, puVar1[0], puVar1[1]);
        }
    }
    if (iVar6 != 0)
        FUN_011835c0((void*)iVar6);
    return 1;
}

// ===========================================================================
// @ 0x011844e0  CRYPTO_free_ex_data
// ===========================================================================
int __cdecl FUN_011844e0(int param_1, int param_2, int* param_3)
{
    int iVar6 = 0;
    if (*param_3 == 0)
        return 1;
    int iVar2 = (int)FUN_01183f70();
    if (iVar2 == 0)
        return 0;
    CRYPTO_lock(5, 2, ".\\crypto\\ex_data.c", 0x1c5);
    int iVar3 = FUN_0117dde0(*(void**)(iVar2 + 4));
    int iVar4 = FUN_0117dde0((void*)*param_3);
    if (iVar4 < iVar3)
        iVar3 = iVar4;
    if (0 < iVar3) {
        iVar6 = (int)CRYPTO_malloc(iVar3 * 4, ".\\crypto\\ex_data.c", 0x1cc);
        if (iVar6 != 0) {
            for (iVar4 = 0; iVar4 < iVar3; iVar4 = iVar4 + 1) {
                int uVar5 = (int)sk_value(*(void**)(iVar2 + 4), iVar4);
                *(int*)(iVar6 + iVar4 * 4) = uVar5;
            }
        }
    }
    CRYPTO_lock(6, 2, ".\\crypto\\ex_data.c", 0x1d3);
    if ((0 < iVar3) && (iVar6 == 0)) {
        ERR_put_error(0xf, 0x6a, 0x41, 0, 0);
        return 0;
    }
    for (int iVar2b = 0; iVar2b < iVar3; iVar2b = iVar2b + 1) {
        int uVar5 = 0;
        if (*param_3 != 0) {
            iVar4 = FUN_0117dde0((void*)*param_3);
            if (iVar2b < iVar4)
                uVar5 = (int)sk_value((void*)*param_3, iVar2b);
            else
                uVar5 = 0;
        }
        u32* puVar1 = *(u32**)(iVar6 + iVar2b * 4);
        int uStack_4 = uVar5;
        if ((puVar1 != 0) && (puVar1[4] != 0)) {
            (*(void(**)(int, int*, int*, int, u32, u32))(puVar1[4]))
                (param_2, param_3, &uStack_4, iVar2b, puVar1[0], puVar1[1]);
        }
        FUN_01184320((int*)param_2, iVar2b, uStack_4);
    }
    if (iVar6 != 0)
        FUN_011835c0((void*)iVar6);
    return 1;
}

// ===========================================================================
// @ 0x01184640  CRYPTO_free_ex_data cleanup
// ===========================================================================
void __cdecl FUN_01184640(int param_1, int param_2, int* param_3)
{
    int iVar6 = 0;
    int iVar2 = (int)FUN_01183f70();
    if (iVar2 != 0) {
        CRYPTO_lock(5, 2, ".\\crypto\\ex_data.c", 0x1f0);
        int iVar3 = FUN_0117dde0(*(void**)(iVar2 + 4));
        if (0 < iVar3) {
            iVar6 = (int)CRYPTO_malloc(iVar3 * 4, ".\\crypto\\ex_data.c", 500);
            if (iVar6 != 0) {
                for (int iVar5 = 0; iVar5 < iVar3; iVar5 = iVar5 + 1) {
                    int uVar4 = (int)sk_value(*(void**)(iVar2 + 4), iVar5);
                    *(int*)(iVar6 + iVar5 * 4) = uVar4;
                }
            }
        }
        CRYPTO_lock(6, 2, ".\\crypto\\ex_data.c", 0x1fb);
        if ((0 < iVar3) && (iVar6 == 0)) {
            ERR_put_error(0xf, 0x6b, 0x41, 0, 0);
            return;
        }
        for (int iVar2b = 0; iVar2b < iVar3; iVar2b = iVar2b + 1) {
            int iVar5 = *(int*)(iVar6 + iVar2b * 4);
            if ((iVar5 != 0) && (*(int*)(iVar5 + 0xc) != 0)) {
                int uVar4 = 0;
                if (*param_3 != 0) {
                    iVar5 = FUN_0117dde0((void*)*param_3);
                    if (iVar2b < iVar5)
                        uVar4 = (int)sk_value((void*)*param_3, iVar2b);
                    else
                        uVar4 = 0;
                }
                u32* puVar1 = *(u32**)(iVar6 + iVar2b * 4);
                (*(void(**)(int, int, int*, int, u32, u32))(puVar1[3]))
                    (param_2, uVar4, param_3, iVar2b, puVar1[0], puVar1[1]);
            }
        }
        if (iVar6 != 0)
            FUN_011835c0((void*)iVar6);
        if (*param_3 != 0) {
            sk_free((void*)*param_3);
            *param_3 = 0;
        }
    }
}

// ===========================================================================
// @ 0x01184770  BUF_MEM_new
// ===========================================================================
u32* __cdecl FUN_01184770(void)
{
    u32* puVar1 = (u32*)CRYPTO_malloc(0xc, ".\\crypto\\buffer\\buffer.c", 0x43);
    if (puVar1 == 0) {
        ERR_put_error(7, 0x65, 0x41, 0, 0);
        return 0;
    }
    *puVar1 = 0;
    puVar1[2] = 0;
    puVar1[1] = 0;
    return puVar1;
}

// ===========================================================================
// @ 0x011847f0  BUF_MEM_grow
// ===========================================================================
int __cdecl FUN_011847f0(int* param_1, int param_2)
{
    int iVar1 = *param_1;
    if (iVar1 < param_2) {
        if (param_1[2] < param_2) {
            iVar1 = ((param_2 + 3) / 3) * 4;
            int iVar2;
            if (param_1[1] == 0)
                iVar2 = (int)CRYPTO_malloc(iVar1, ".\\crypto\\buffer\\buffer.c", 0x6e);
            else
                iVar2 = (int)CRYPTO_realloc((void*)param_1[1], iVar1, ".\\crypto\\buffer\\buffer.c", 0x70);
            if (iVar2 == 0) {
                ERR_put_error(7, 100, 0x41, 0, 0);
                return 0;
            }
            param_1[1] = iVar2;
            param_1[2] = iVar1;
            operator_new__((void*)(*param_1 + iVar2), 0, param_2 - *param_1);
            *param_1 = param_2;
            return param_2;
        }
        operator_new__((void*)(param_1[1] + iVar1), 0, param_2 - iVar1);
    }
    *param_1 = param_2;
    return param_2;
}

// ===========================================================================
// @ 0x011848a0  BUF_MEM_grow_clean
// ===========================================================================
int __cdecl FUN_011848a0(int* param_1, int param_2)
{
    int iVar1 = *param_1;
    if (iVar1 >= param_2) {
        operator_new__((void*)(param_1[1] + param_2), 0, iVar1 - param_2);
        *param_1 = param_2;
        return param_2;
    }
    if (param_1[2] >= param_2) {
        operator_new__((void*)(param_1[1] + iVar1), 0, param_2 - iVar1);
        *param_1 = param_2;
        return param_2;
    }
    iVar1 = ((param_2 + 3) / 3) * 4;
    int iVar2;
    if (param_1[1] == 0)
        iVar2 = (int)CRYPTO_malloc(iVar1, ".\\crypto\\buffer\\buffer.c", 0x93);
    else
        iVar2 = (int)CRYPTO_realloc_clean((void*)param_1[1], param_1[2], iVar1,
                                          ".\\crypto\\buffer\\buffer.c", 0x95);
    if (iVar2 == 0) {
        ERR_put_error(7, 0x69, 0x41, 0, 0);
        return 0;
    }
    param_1[1] = iVar2;
    param_1[2] = iVar1;
    operator_new__((void*)(*param_1 + iVar2), 0, param_2 - *param_1);
    *param_1 = param_2;
    return param_2;
}

// ===========================================================================
// @ 0x01184a20  BUF_strndup
// ===========================================================================
int __cdecl FUN_01184a20(int param_1, int param_2)
{
    if (param_1 == 0)
        return 0;
    int iVar1 = (int)CRYPTO_malloc(param_2 + 1, ".\\crypto\\buffer\\buffer.c", 0xb1);
    if (iVar1 == 0) {
        ERR_put_error(7, 0x68, 0x41, 0, 0);
        return 0;
    }
    BUF_strlcpy((char*)iVar1, (char*)param_1, param_2 + 1);
    return iVar1;
}

// ===========================================================================
// @ 0x01185850  ssleay_rand_cleanup
// ===========================================================================
void __cdecl FUN_01185850(void)
{
    OPENSSL_cleanse(&DAT_016f1c98, 0x413);
    DAT_016f20c0 = 0;
    DAT_016f20c4 = 0;
    OPENSSL_cleanse(&DAT_016f20ac, 0x14);
    _DAT_016f20d0 = 0;
    DAT_016f20c8 = 0;
    DAT_016f20cc = 0;
    DAT_016f20d8 = 0;
}
