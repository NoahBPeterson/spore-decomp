// slice s01195b10 -- OpenSSL 0.9.8g X509/DH/BIO glue (lib_cblock / lib_openssl).
// Module flags: /O2 /MD /Gy /TP.  See manifest.txt / nonmatching.txt / partial.txt.
#include "types.h"
#include <string.h>

typedef unsigned int u32;
struct DH; struct X509;

// ---- OpenSSL callees -------------------------------------------------------
void* __cdecl CRYPTO_malloc(int num, const char* file, int line);
void  __cdecl CRYPTO_free(void* p);
void  __cdecl ERR_put_error(int lib, int func, int reason, const char* file, int line);
int   __cdecl CRYPTO_new_ex_data(int class_id, void* obj, void* ad);
int   __cdecl CRYPTO_free_ex_data(int class_id, void* obj, void* ad);
int   __cdecl FUN_011836c0(int p);
void  __cdecl FUN_011835c0(void* p);
void  __cdecl FUN_01183740(void* p);
int   __cdecl FUN_011b6ee0();
void* __cdecl FUN_011b7230();
int   __cdecl FUN_011b7240(void* p);
void  __cdecl BIO_clear_flags(void* b, int flags);
void  __cdecl BIO_copy_next_retry(void* b);
void  __cdecl FUN_01176f90(void* b, int flags);
int   __cdecl FUN_01176fc0(void* b, void* out, int len);
int   __cdecl FUN_0117df20();
int   __cdecl FUN_01198210(int flag);
void  __cdecl CRYPTO_lock(int mode, int type, const char* file, int line);
int   __cdecl sk_find(void* st, void* p);
void* __cdecl sk_value(void* st, int i);
void  __cdecl x509v3_cache_extensions();

extern int DAT_016f2138;
extern void* DAT_016f2134;
extern char DAT_015cd938;
extern void* DAT_015cd944;

// @ 0x011965f0  (DH_new)
void* __cdecl FUN_011965f0(int param_1);
// @ 0x01198420  (asn1_ex_clear / primitive free, custom eax convention)
void __fastcall FUN_01198420(void* in_eax, void* in_edx);

// ---------------------------------------------------------------------------
// @ 0x01196850
// ---------------------------------------------------------------------------
int __cdecl FUN_01196850(void)
{
    return (int)FUN_011965f0(0);
}

// ---------------------------------------------------------------------------
// @ 0x011965f0  (DH_new)
// ---------------------------------------------------------------------------
void* __cdecl FUN_011965f0(int param_1)
{
    char* p = (char*)CRYPTO_malloc(0x4c, ".\\crypto\\dh\\dh_lib.c", 0x6f);
    if (p == 0) {
        ERR_put_error(5, 0x69, 0x41, 0, 0);
        return 0;
    }
    if (DAT_016f2138 == 0)
        DAT_016f2138 = FUN_011b6ee0();
    *(int*)(p + 0x44) = DAT_016f2138;
    if (param_1 != 0) {
        if (FUN_011836c0(param_1) == 0) {
            ERR_put_error(5, 0x69, 0x26, 0, 0);
            FUN_011835c0(p);
            return 0;
        }
        *(int*)(p + 0x48) = param_1;
    } else {
        *(int*)(p + 0x48) = (int)FUN_011b7230();
    }
    if (*(int*)(p + 0x48) != 0) {
        int i = (int)FUN_011b7240(*(void**)(p + 0x48));
        *(int*)(p + 0x44) = i;
        if (i == 0) {
            ERR_put_error(5, 0x69, 0x26, 0, 0);
            FUN_01183740(*(void**)(p + 0x48));
            FUN_011835c0(p);
            return 0;
        }
    }
    *(int*)(p + 0x00) = 0;
    *(int*)(p + 0x04) = 0;
    *(int*)(p + 0x08) = 0;
    *(int*)(p + 0x0c) = 0;
    *(int*)(p + 0x10) = 0;
    *(int*)(p + 0x14) = 0;
    *(int*)(p + 0x18) = 0;
    *(int*)(p + 0x24) = 0;
    *(int*)(p + 0x28) = 0;
    *(int*)(p + 0x2c) = 0;
    *(int*)(p + 0x30) = 0;
    *(int*)(p + 0x34) = 0;
    *(int*)(p + 0x20) = 0;
    *(int*)(p + 0x38) = 1;
    *(int*)(p + 0x1c) = *(int*)(*(int*)(p + 0x44) + 0x18);
    CRYPTO_new_ex_data(8, p, p + 0x3c);
    void* cb = *(void**)(*(int*)(p + 0x44) + 0x10);
    if (cb != 0) {
        if (((int(__cdecl*)(void*))cb)(p) == 0) {
            if (*(int*)(p + 0x48) != 0)
                FUN_01183740(*(void**)(p + 0x48));
            CRYPTO_free_ex_data(8, p, p + 0x3c);
            FUN_011835c0(p);
            p = 0;
        }
    }
    return p;
}

// ---------------------------------------------------------------------------
// @ 0x011964f0  (X509_check_purpose)
// ---------------------------------------------------------------------------
int __cdecl FUN_011964f0(int* x, int id, int ca)
{
    if ((*(u32*)((char*)x + 0x28) & 0x100) == 0) {
        CRYPTO_lock(9, 3, ".\\crypto\\x509v3\\v3_purp.c", 0x70);
        x509v3_cache_extensions();
        CRYPTO_lock(10, 3, ".\\crypto\\x509v3\\v3_purp.c", 0x72);
    }
    if (id == -1)
        return 1;
    if ((u32)(id - 1) <= 7) {
        id = id - 1;
    } else {
        int local = id;
        if (DAT_016f2134 == 0)
            return -1;
        id = sk_find(DAT_016f2134, &local);
        if (id == -1)
            return -1;
        id = id + 8;
    }
    if (id == -1)
        return -1;
    if (id >= 0) {
        if (id > 7) {
            int* v = (int*)sk_value(DAT_016f2134, id - 8);
            return ((int(__cdecl*)(void*, void*, int))v[3])(v, x, ca);
        }
        void* ent = (char*)&DAT_015cd938 + id * 0x1c;
        int (*fn)(void*, void*, int) =
            (int(__cdecl*)(void*, void*, int))((void**)&DAT_015cd944)[id * 7];
        return fn(ent, x, ca);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x01196a90  (BIO_ctrl-ish read helper)
// ---------------------------------------------------------------------------
int __cdecl FUN_01196a90(int param_1, void* param_2, int param_3)
{
    if (param_2 == 0)
        return 0;
    int* pi = *(int**)(param_1 + 0x20);
    if (pi == 0 || *(int*)(param_1 + 0x24) == 0)
        return 0;
    int total = 0;
    FUN_01176f90((void*)param_1, 0xf);
    for (;;) {
        int s = pi[3];
        if (s != 0) {
            if (param_3 < s)
                s = param_3;
            memcpy(param_2, (void*)(pi[2] + pi[4]), s);
            pi[4] += s;
            pi[3] -= s;
            total += s;
            if (param_3 == s)
                return total;
            param_3 -= s;
            param_2 = (char*)param_2 + s;
        }
        if (*pi < param_3)
            break;
        s = FUN_01176fc0(*(void**)(param_1 + 0x24), (void*)pi[2], *pi);
        if (s < 1) {
            BIO_copy_next_retry((void*)param_1);
            if (s < 0)
                return (total > 0) ? total : s;
            if (s == 0)
                return total;
        }
        pi[4] = 0;
        pi[3] = s;
    }
    for (;;) {
        int s = FUN_01176fc0(*(void**)(param_1 + 0x24), param_2, param_3);
        if (s < 1) {
            BIO_copy_next_retry((void*)param_1);
            if (s < 0) {
                if (total < 1)
                    total = s;
                return total;
            }
            if (s == 0)
                return total;
        }
        total += s;
        if (param_3 == s)
            return total;
        param_2 = (char*)param_2 + s;
        param_3 -= s;
    }
}

// ---------------------------------------------------------------------------
// @ 0x011984b0
// ---------------------------------------------------------------------------
int __cdecl FUN_011984b0(int* param_1, u32* param_2)
{
    u32 flags = *param_2;
    if ((flags & 1) != 0) {
        if ((flags & 0x306) != 0) {
            *param_1 = 0;
            return 1;
        }
        FUN_01198420(*(void**)((char*)param_2 + 0x10), param_1);
        return 1;
    }
    if ((flags & 0x300) != 0) {
        *param_1 = 0;
        return 1;
    }
    if ((flags & 6) != 0) {
        int i = FUN_0117df20();
        if (i == 0) {
            ERR_put_error(0xd, 0x85, 0x41, 0, 0);
            return 0;
        }
        *param_1 = i;
        return 1;
    }
    return FUN_01198210(flags & 0x400);
}

// ---------------------------------------------------------------------------
// @ 0x01195b10  (not reconstructed; see partial.txt)
// ---------------------------------------------------------------------------
int __cdecl FUN_01195b10(void)
{
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x01196d20  (not reconstructed; see partial.txt)
// ---------------------------------------------------------------------------
int __cdecl FUN_01196d20(void)
{
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x01197550  (not reconstructed; see partial.txt)
// ---------------------------------------------------------------------------
int __cdecl FUN_01197550(void)
{
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x01198420  (asn1 primitive clear; custom eax register convention -- only a stub)
// ---------------------------------------------------------------------------
__declspec(noinline) void __fastcall FUN_01198420(void* in_eax, void* in_edx)
{
    (void)in_eax; (void)in_edx;
}

// ---------------------------------------------------------------------------
// @ 0x01198210  (not reconstructed; see partial.txt)
// ---------------------------------------------------------------------------
int __cdecl FUN_01198210(int flag)
{
    (void)flag;
    return 0;
}
