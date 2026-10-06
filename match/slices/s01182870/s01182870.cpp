// Slice s01182870 -- lib_cblock (OpenSSL ENGINE + cblock dispatch) helpers.
// Module flags: /O2 /MD /Gy /TP
#include "types.h"

// ---------------------------------------------------------------- openssl externs
extern "C" void __cdecl ERR_put_error(int lib, int func, int reason, int file, int line);  // 0x1180d50
extern "C" void __cdecl CRYPTO_lock(int mode, int type, const char* file, int line);       // 0x1181540
extern "C" int  __cdecl FUN_011a9db0(int a, int b);                                        // 0x11a9db0
extern "C" void __cdecl FUN_011a8c30(void);                                                // 0x11a8c30
extern "C" void __cdecl FUN_011a8ae0(void);                                                // 0x11a8ae0
extern "C" void __cdecl FUN_00c2e4e0(void);                                                // 0x00c2e4e0
extern "C" void* __cdecl FUN_011a8a70(void);                                               // 0x11a8a70
extern "C" void* __cdecl FUN_011a60d0(void);                                               // 0x11a60d0
extern "C" void* __cdecl FUN_011a8ad0(void);                                               // 0x11a8ad0
extern "C" void* __cdecl FUN_011a8aa0(void);                                               // 0x11a8aa0

static const char kEngInitFile[] = ".\\crypto\\engine\\eng_init.c";

// ---------------------------------------------------------------- 01182870 / 01182ae0 / 011831f0
// @ 0x01182870 -- large cblock routine; approximated.
void lib_cblock_FUN_01182870(void) {}

// @ 0x01182ae0 -- very large cblock routine; approximated.
void lib_cblock_FUN_01182ae0(void) {}

// @ 0x01182ac0
void* lib_cblock_FUN_01182ac0(int id)
{
    if (id == 0x300) return FUN_011a8a70();
    if (id == 0x301) return FUN_011a60d0();
    return 0;
}

// @ 0x011831b0
void* lib_cblock_FUN_011831b0(int id)
{
    if (id == 0x300) return FUN_011a8ad0();
    if (id == 0x301) return FUN_011a8aa0();
    return 0;
}

// @ 0x011831e0
void lib_cblock_FUN_011831e0(void)
{
    FUN_00c2e4e0();
    FUN_011a8c30();
    FUN_011a8ae0();
}

// @ 0x011831f0 -- medium cblock routine; approximated.
void lib_cblock_FUN_011831f0(void) {}

// @ 0x01183630
int lib_cblock_engine_finish(int param_1, int param_2)
{
    int* piVar1 = (int*)(param_1 + 0x50);
    *piVar1 = *piVar1 - 1;
    int iVar3 = 1;
    if ((*piVar1 == 0) && (*(int*)(param_1 + 0x34) != 0)) {
        if (param_2 != 0) {
            CRYPTO_lock(0xa, 0x1e, kEngInitFile, 0x61);
        }
        iVar3 = (*(int(__cdecl*)(int))*(int*)(param_1 + 0x34))(param_1);
        if (param_2 != 0) {
            CRYPTO_lock(9, 0x1e, kEngInitFile, 0x64);
        }
        if (iVar3 == 0) {
            return 0;
        }
    }
    if (FUN_011a9db0(param_1, 0) == 0) {
        ERR_put_error(0x26, 0xbf, 0x6a, 0, 0);
        return 0;
    }
    return iVar3;
}

// @ 0x011836c0
int lib_cblock_engine_init(int param_1)
{
    if (param_1 == 0) {
        ERR_put_error(0x26, 0x77, 0x43, 0, 0);
        return 0;
    }
    CRYPTO_lock(9, 0x1e, kEngInitFile, 0x81);
    int iVar1 = 1;
    if ((*(int*)(param_1 + 0x50) == 0) && (*(int*)(param_1 + 0x30) != 0)) {
        iVar1 = (*(int(__cdecl*)(int))*(int*)(param_1 + 0x30))(param_1);
        if (iVar1 == 0) {
            goto LAB_LOCK;
        }
    }
    *(int*)(param_1 + 0x4c) = *(int*)(param_1 + 0x4c) + 1;
    *(int*)(param_1 + 0x50) = *(int*)(param_1 + 0x50) + 1;
LAB_LOCK:
    CRYPTO_lock(0xa, 0x1e, kEngInitFile, 0x83);
    return iVar1;
}

// @ 0x01183740
int lib_cblock_engine_finish2(int param_1)
{
    if (param_1 == 0) {
        ERR_put_error(0x26, 0x6b, 0x43, 0, 0);
        return 0;
    }
    CRYPTO_lock(9, 0x1e, kEngInitFile, 0x91);
    int* piVar1 = (int*)(param_1 + 0x50);
    *piVar1 = *piVar1 - 1;
    int iVar3 = 1;
    if ((*piVar1 == 0) && (*(int*)(param_1 + 0x34) != 0)) {
        CRYPTO_lock(0xa, 0x1e, kEngInitFile, 0x61);
        iVar3 = (*(int(__cdecl*)(int))*(int*)(param_1 + 0x34))(param_1);
        CRYPTO_lock(9, 0x1e, kEngInitFile, 0x64);
        if (iVar3 == 0) {
            goto D6;
        }
    }
    if (FUN_011a9db0(param_1, 0) != 0) {
        goto D8;
    }
    ERR_put_error(0x26, 0xbf, 0x6a, 0, 0);
D6:
    iVar3 = 0;
D8:
    CRYPTO_lock(0xa, 0x1e, kEngInitFile, 0x93);
    if (iVar3 == 0) {
        ERR_put_error(0x26, 0x6b, 0x6a, 0, 0);
        return 0;
    }
    return iVar3;
}

// @ 0x011838a0
void* lib_cblock_getPtr(void* p)
{
    return *(void**)p;
}

// @ 0x011839f0
int lib_cblock_dispatch(int param_1, int param_2)
{
    int (*fn)(int, int, int, int) = (int(*)(int, int, int, int))*(int*)(param_1 + 0x24);
    if (fn != 0) {
        int iVar1 = fn(param_1, (int)&param_1, 0, param_2);
        if (iVar1 != 0) {
            return param_1;
        }
    }
    ERR_put_error(0x26, 0xb9, 0x92, 0, 0);
    return 0;
}
