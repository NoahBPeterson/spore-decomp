// Slice s011869d0 -- lib_cblock (OpenSSL BIGNUM context) helpers.
// Module flags: /O2 /MD /Gy /TP
#include "types.h"

// ---------------------------------------------------------------- openssl externs
extern "C" void  __cdecl ERR_put_error(int lib, int func, int reason, int file, int line);  // 0x1180d50
extern "C" int   __cdecl BN_copy(int dst, int src);                                        // 0x117ab40
extern "C" int   __cdecl BN_mod_mul(int r, int a, int b, int m, int ctx);                  // 0x11ad640
extern "C" int   __cdecl FUN_011875c0(int, int, int, int, int, int);                       // 0x11875c0
extern "C" void* __cdecl CRYPTO_malloc(int num, const char* file, int line);               // 0x1183410
extern "C" int   __cdecl BN_STACK_push(int a);                                             // 0x11878b0
extern "C" int   __cdecl BN_POOL_get(void);                                                // 0x1187990
extern "C" int   __cdecl BN_set_word(int a, int w);                                        // 0x117ac20

static const char kBnCtxFile[] = ".\\crypto\\bn\\bn_ctx.c";

// ---------------------------------------------------------------- big skeletons
// @ 0x011869d0 -- large BN routine; skeleton.
void lib_cblock_FUN_011869d0(void) {}
// @ 0x01186d30 -- large BN routine; skeleton.
void lib_cblock_FUN_01186d30(void) {}
// @ 0x011875c0 -- large BN routine; skeleton.
void lib_cblock_FUN_011875c0(void) {}
// @ 0x01187be0 -- large BN routine; skeleton.
void lib_cblock_FUN_01187be0(void) {}

// @ 0x01187540
int lib_cblock_BN_mod_mul_wrap(int param_1, int param_2, int* param_3, int param_4)
{
    int r = 1;
    if (*param_3 != 0 && param_3[1] != 0) {
        if (param_2 != 0) {
            if (BN_copy(param_2, param_3[1]) == 0) {
                r = 0;
            }
        }
        if (BN_mod_mul(param_1, param_1, *param_3, param_3[3], param_4) == 0) {
            r = 0;
        }
        return r;
    }
    ERR_put_error(3, 0x64, 0x6b, 0, 0);
    return 0;
}

// @ 0x011877a0
int lib_cblock_BN_mod_mul_wrap2(int* param_1, int param_2)
{
    int v = *param_1;
    int r = 0;
    if (v == 0 || param_1[1] == 0) {
        ERR_put_error(3, 0x67, 0x6b, 0, 0);
        goto END;
    }
    param_1[5] = param_1[5] - 1;
    if ((param_1[5] == 0) && (param_1[2] != 0) && ((*(char*)((char*)param_1 + 0x18) & 2) == 0)) {
        v = FUN_011875c0((int)param_1, 0, 0, param_2, 0, 0);
        if (v == 0) {
            goto END;
        }
    } else if ((*(char*)((char*)param_1 + 0x18) & 1) == 0) {
        v = BN_mod_mul(v, v, v, param_1[3], param_2);
        if (v == 0) {
            goto END;
        }
        v = param_1[1];
        v = BN_mod_mul(v, v, v, param_1[3], param_2);
        if (v == 0) {
            goto END;
        }
    }
    r = 1;
END:
    if (param_1[5] == 0) {
        param_1[5] = 0x20;
    }
    return r;
}

// @ 0x01187840
int lib_cblock_BN_mod_mul_wrap3(int param_1, int param_2, int* param_3, int param_4)
{
    if (*param_3 != 0 && param_3[1] != 0) {
        int v = param_3[1];
        int m = param_3[3];
        if (param_2 != 0) {
            v = param_2;
        }
        v = BN_mod_mul(param_1, param_1, v, m, param_4);
        if (v >= 0) {
            if (lib_cblock_BN_mod_mul_wrap2(param_3, param_4) == 0) {
                return 0;
            }
        }
        return v;
    }
    ERR_put_error(3, 0x65, 0x6b, 0, 0);
    return 0;
}

// @ 0x01187a80
int* lib_cblock_BN_CTX_new(void)
{
    int* p = (int*)CRYPTO_malloc(0x2c, kBnCtxFile, 0xd8);
    if (p == 0) {
        ERR_put_error(3, 0x6a, 0x41, 0, 0);
        return 0;
    }
    p[2] = 0;
    p[1] = 0;
    p[0] = 0;
    p[4] = 0;
    p[3] = 0;
    p[5] = 0;
    p[7] = 0;
    p[6] = 0;
    p[8] = 0;
    p[9] = 0;
    p[10] = 0;
    return p;
}

// @ 0x01187b00
void lib_cblock_BN_STACK_push(int param_1)
{
    if (*(int*)(param_1 + 0x24) == 0 && *(int*)(param_1 + 0x28) == 0) {
        if (BN_STACK_push(*(int*)(param_1 + 0x20)) == 0) {
            ERR_put_error(3, 0x81, 0x6d, 0, 0);
            ++*(int*)(param_1 + 0x24);
        }
    } else {
        ++*(int*)(param_1 + 0x24);
    }
}

// @ 0x01187b90
int lib_cblock_BN_POOL_get(int param_1)
{
    if (*(int*)(param_1 + 0x24) == 0 && *(int*)(param_1 + 0x28) == 0) {
        int r = BN_POOL_get();
        if (r == 0) {
            *(int*)(param_1 + 0x28) = 1;
            ERR_put_error(3, 0x74, 0x6d, 0, 0);
            return 0;
        }
        BN_set_word(r, 0);
        ++*(int*)(param_1 + 0x20);
        return r;
    }
    return 0;
}
