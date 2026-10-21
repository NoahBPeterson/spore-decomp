// slice s008d0c10 -- TSI font-engine memory handler + utility math.
// Compile: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// FreeType-style allocator hooks exported elsewhere.
extern "C" void* ff_malloc(unsigned size);
extern "C" void  ff_free(void* p);
extern "C" void* ff_realloc(void* p, unsigned size);
extern "C" int   setjmp3(void* jmpbuf, int n);
extern "C" void  longjmp(void* jmpbuf, int val);

// ---- externals referenced by the sfnt class constructor ----------------
extern "C" int   FUN_008cf330(void* self, int a);
extern "C" int   CacheKeyTables_sfntClass(int a, int b);
extern "C" int   FUN_008cc2a0(int a);
extern "C" int   tsi_NewT1Class(int a, int b, int c);
extern "C" int   New_FFT1HintClass(int a, int b);
extern "C" int   GetEntireStreamIntoMemory(int a, int b);
extern "C" int   New_T1kernClass(int a, int b, int c);
extern "C" int   Delete_kernClass(int a);
extern "C" int   tsi_NewPFRClass(int a, int b, int c);
extern "C" int   FUN_008bf290(int a, int b, int c);
extern "C" int   FUN_008bf270(int a, int b, int c, int d);
extern "C" int   FUN_008cf390(int a, int b);
extern "C" int   FUN_008cf450(int a, int b);
extern "C" int   FUN_008cb790(int a, int b);
extern "C" int   Get_Cached_AW(int a, int b);
extern "C" int   FUN_008cef90(void* self);
extern "C" int   FUN_008b8c80(int a, int b);
extern "C" int   FUN_008be220(int a, int b);
extern "C" int   GetUPEM(void* self, int* out);
extern "C" int   FUN_011e0cac(void* p, int a);

// Fast-memory-block helper (defined below, used by the ctor).
extern "C" void* tsi_AllocMem(int tbl, int size);
extern "C" void  tsi_DeAllocMem(int tbl, void* p);
extern "C" void  tsi_EmergencyShutDown(int tbl);

// ---------------------------------------------------------------------------
// @ 0x008d0c10
void* FF_New_sfntClass(int param_1, short params, int param_3, int param_4,
                       int param_5, int param_6, int* out_err)
{
    unsigned char* o;
    int i2;
    short ax;
    if (out_err == 0)
        goto fail;

    i2 = setjmp3((char*)param_1 + 0x10, 0);
    *out_err = i2;
    if (i2 != 0)
        goto fail;

    o = (unsigned char*)tsi_AllocMem(param_1, 0xf8);
    *(int*)(o + 0xdc) = param_3;
    *(int*)(o + 0xe8) = param_1;
    *(int*)(o + 0xe0) = param_5;
    *(int*)(o + 0xe4) = 0;
    *(int*)(o + 0x04) = 0;
    *(int*)(o + 0x08) = 0;
    *(int*)(o + 0x0c) = 0;
    *(int*)(o + 0x10) = 0;
    *(int*)(o + 0x14) = 0;
    *(int*)(o + 0x18) = 0;
    *(int*)(o + 0xf4) = 1;
    *(int*)(o + 0x00) = 0;
    *(int*)(o + 0x50) = 0;
    *(int*)(o + 0x60) = 0;
    *(int*)(o + 0x64) = 0;
    *(int*)(o + 0x68) = 0;
    *(int*)(o + 0x6c) = 0;
    *(int*)(o + 0x54) = 0;
    *(int*)(o + 0x58) = 0;
    *(int*)(o + 0x2c) = 0;
    *(int*)(o + 0x30) = 0;
    *(int*)(o + 0x34) = 0;
    *(int*)(o + 0x70) = 0;
    *(int*)(o + 0x74) = 0;
    *(int*)(o + 0x5c) = 0;
    *(int*)(o + 0xec) = 0;
    *(int*)(o + 0x38) = 0;
    *(int*)(o + 0x3c) = 0;
    *(short*)(o + 0x1c) = 0;
    FUN_008cf330(o, param_6);
    *(int*)(o + 0x9c) = -1;
    *(int*)(o + 0xa0) = -1;
    *(short*)(o + 0x98) = 0;
    ax = params;
    *(int*)(o + 0xa4) = 0;
    *(int*)(o + 0x20) = 0;
    *(int*)(o + 0x24) = 0;
    *(int*)(o + 0x28) = 0;
    *(int*)(o + 0x44) = 0;
    *(int*)(o + 0x48) = 0;
    *(int*)(o + 0x4c) = 0;
    *(int*)(o + 0xc0) = 0;
    *(int*)(o + 0xc4) = 0;
    *(int*)(o + 0xc8) = 0;
    *(int*)(o + 0x78) = 0;
    *(int*)(o + 0x7c) = 0;
    *(int*)(o + 0x80) = 0;
    *(int*)(o + 0x84) = 0;

    if (ax == 7) {
        if (CacheKeyTables_sfntClass(*(int*)(o + 0xdc), param_4) == 0) {
            *out_err = 0x2729;
            return 0;
        }
    }

    if (ax == 2 || ax == 5 || (ax == 7 && *(int*)(o + 0x7c) == 0)) {
        if (ax != 7 && CacheKeyTables_sfntClass(*(int*)(o + 0xdc), param_4) == 0) {
            *out_err = 0x2729;
            return 0;
        }
    } else if (ax == 1) {
        int u4 = FUN_008cc2a0(param_4);
        int t1 = tsi_NewT1Class(param_1, param_4, u4);
        *(int*)(o + 0x20) = t1;
        if (t1 == 0)
            goto dealloc;
        {
            int upem = GetUPEM(o, 0);
            int hint = New_FFT1HintClass(param_1, upem);
            *(int*)(o + 0x48) = hint;
        }
        if (param_6 != 0) {
            int u5 = FUN_008cc2a0(param_6);
            int buf = GetEntireStreamIntoMemory(param_6, u5);
            int kern = New_T1kernClass(*(int*)(o + 0x20), param_1, buf);
            *(int*)(o + 0x74) = kern;
            if (*(short*)(*(int*)(**(int**)(kern + 0xc) + 0x10) + 4) == 0) {
                Delete_kernClass(kern);
                *(int*)(o + 0x74) = 0;
            }
        }
        *(int*)(o + 0x0c) = (int)&FUN_008b8c80;
        *(int*)(o + 0x10) = *(int*)(o + 0x20);
        if (*(int*)(o + 0xac) != 0) {
            int upem = GetUPEM(o, (int*)(o + 0xb0));
            (*(void(**)(int, int, int))*(int*)(o + 0xac))(*(int*)(o + 0x68), *(int*)(o + 0xe8), upem);
        }
        {
            int t = *(int*)(o + 0x20);
            *(int*)(o + 0x90) = *(int*)(t + 0x214);
            *(short*)(o + 0x94) = *(short*)(t + 0x218);
            *(short*)(o + 0x96) = *(short*)(t + 0x21a);
        }
    } else if (ax == 0x16 || (ax == 7 && *(int*)(o + 0x78) != 0)) {
        int r;
        if (*(int*)(o + 0x78) == 0)
            r = FUN_008bf290(param_1, *(int*)(o + 0xdc), param_4);
        else
            r = FUN_008bf270(param_1, *(int*)(o + 0xdc), param_4, *(int*)(o + 0x78));
        *(int*)(o + 0x24) = r;
        *(int*)(o + 0x0c) = (int)&FUN_008be220;
        *(int*)(o + 0x10) = r;
        if (*(int*)(o + 0xac) != 0) {
            int upem = GetUPEM(o, (int*)(o + 0xb0));
            (*(void(**)(int, int, int))*(int*)(o + 0xac))(*(int*)(o + 0x68), *(int*)(o + 0xe8), upem);
        }
        {
            int t = *(int*)(o + 0x24);
            *(int*)(o + 0x90) = *(int*)(t + 0x514);
            *(short*)(o + 0x94) = *(short*)(t + 0x518);
            *(short*)(o + 0x96) = *(short*)(t + 0x51a);
        }
    } else {
        int pfr;
        if (ax != 3)
            goto dealloc;
        pfr = tsi_NewPFRClass(param_1, *(int*)(o + 0xdc), param_4);
        *(int*)(o + 0x28) = pfr;
        *(int*)(o + 0x74) = *(int*)(pfr + 0x128);
        *(int*)(o + 0x68) = *(int*)(pfr + 0x100);
        *(int*)(pfr + 0x100) = 0;
        pfr = *(int*)(o + 0x28);
        *(int*)(o + 0xf4) = *(int*)(pfr + 0x10);
        *(short*)(o + 0x94) = *(short*)(pfr + 0x1e8);
        *(short*)(o + 0x96) = *(short*)(pfr + 0x1ea);
        *(int*)(o + 0x90) = *(int*)(pfr + 0x1e4);
        if (*(int*)(o + 0xac) != 0) {
            int upem = GetUPEM(o, (int*)(o + 0xb0));
            (*(void(**)(int, int, int))*(int*)(o + 0xac))(*(int*)(o + 0x68), *(int*)(o + 0xe8), upem);
        }
        if (*(int*)(o + 0x48) == 0) {
            int upem = GetUPEM(o, 0);
            *(int*)(o + 0x48) = New_FFT1HintClass(param_1, upem);
        }
    }

    if (*(int*)(o + 0x68) == 0) {
        *(int*)(o + 0x04) = (int)&Get_Cached_AW;
        *(int*)(o + 0x08) = (int)o;
    } else {
        *(int*)(o + 0x04) = (int)&FUN_008cf390;
        *(int*)(o + 0x08) = *(int*)(o + 0x68);
    }

    {
        int u5 = FUN_008cef90(o);
        *(int*)(o + 0xf0) = u5;
        if (*(int*)(o + 0x50) != 0 && *(short*)(*(int*)(o + 0x50) + 0x38) == 0x7d2) {
            if (*(int*)(o + 0x34) == 0) {
                if (*(int*)(o + 0x0c) == 0) {
                    *(int*)(o + 0x04) = (int)&FUN_008cf450;
                    *(int*)(o + 0x08) = (int)o;
                }
            } else {
                *(int*)(o + 0x0c) = (int)&FUN_008cb790;
                *(int*)(o + 0x10) = *(int*)(o + 0x34);
            }
        }
    }
    *(int*)(o + 0xd4) = 0x8000;
    *(int*)(o + 0xd8) = 0x8000;
    return o;

dealloc:
    tsi_DeAllocMem(param_1, o);
    *out_err = 0x2729;
    return 0;

fail:
    tsi_EmergencyShutDown(param_1);
    return 0;
}

// @ 0x008d10c0
void tsi_Error(int param_1, int param_2)
{
    if (param_1 != 0) {
        *(int*)(param_1 + 0xa8) = 0x5500aaff;
        longjmp((void*)(param_1 + 0x10), param_2);
    }
}

// @ 0x008d10f0
void* tsi_NewCustomSizeMemhandler(int* out_err, int count)
{
    unsigned char* m;
    int* tbl;
    int i;
    *out_err = 0;
    m = (unsigned char*)ff_malloc(0xb0);
    if (m == 0)
        goto err;
    *(int*)(m + 8) = count;
    *(int*)(m + 0) = 0xab1500ff;
    *(int*)(m + 0xa8) = 0xaa005501;
    *(int*)(m + 0xac) = 0xa5a55a5a;
    *(int*)(m + 4) = 0;
    *(int*)(m + 0xa4) = 0;
    tbl = (int*)ff_malloc(count * 4);
    *(int**)(m + 0xc) = tbl;
    if (tbl == 0) {
        ff_free(m);
        goto err;
    }
    i = 0;
    if (count > 0) {
        do {
            tbl[i] = 0;
            ++i;
        } while (i < count);
    }
    *(int*)(m + 0x50) = 0;
    *(int*)(m + 0x6c) = 0;
    *(int*)(m + 0x54) = 0;
    *(int*)(m + 0x70) = 0;
    *(int*)(m + 0x58) = 0;
    *(int*)(m + 0x74) = 0;
    *(int*)(m + 0x5c) = 0;
    *(int*)(m + 0x78) = 0;
    *(int*)(m + 0x60) = 0;
    *(int*)(m + 0x7c) = 0;
    *(int*)(m + 0x64) = 0;
    *(int*)(m + 0x80) = 0;
    *(int*)(m + 0x68) = 0;
    *(int*)(m + 0x84) = 0;
    *(int*)(m + 0x88) = 1;
    *(int*)(m + 0x8c) = 1;
    *(int*)(m + 0x90) = 1;
    *(int*)(m + 0x94) = 1;
    *(int*)(m + 0x98) = 1;
    *(int*)(m + 0x9c) = 1;
    *(int*)(m + 0xa0) = 1;
    return m;
err:
    *out_err = 0x2718;
    return 0;
}

// @ 0x008d1210
void tsi_EmergencyShutDown(int param_1)
{
    int i;
    int n;
    int* tbl;
    if (param_1 == 0)
        return;
    n = *(int*)(param_1 + 8);
    tbl = *(int**)(param_1 + 0xc);
    i = 0;
    if (n > 0) {
        do {
            int p = tbl[i];
            if (p != 0)
                ff_free((void*)p);
            ++i;
        } while (i < n);
    }
    ff_free(tbl);
    ff_free((void*)param_1);
}

// @ 0x008d1260
void* tsi_AllocMem(int param_1, int param_2)
{
    unsigned char* h;
    int n;
    int slot;
    int cnt;
    h = (unsigned char*)ff_malloc(param_2 + 0x12);
    if (h == 0 && param_1 != 0) {
        *(int*)(param_1 + 0xa8) = 0x5500aaff;
        longjmp((void*)(param_1 + 0x10), 0x2718);
    }
    *(int*)(h + 0) = (int)0xaa53c5aa;
    *(int*)(h + 4) = param_2;
    h[param_2 + 0x10] = 0x5a;
    h[param_2 + 0x11] = 0xf0;
    n = *(int*)(param_1 + 8);
    if (*(int*)(param_1 + 4) >= n) {
        *(int*)(param_1 + 0xa8) = 0x5500aaff;
        longjmp((void*)(param_1 + 0x10), 0x271c);
    }
    slot = *(int*)(param_1 + 0xa4);
    cnt = 0;
    if (n > 0) {
        do {
            if (*(int*)(*(int*)(param_1 + 0xc) + slot * 4) == 0) {
                *(void**)(*(int*)(param_1 + 0xc) + slot * 4) = h;
                *(int*)(h + 8) = slot;
                ++*(int*)(param_1 + 4);
                break;
            }
            ++cnt;
            slot = (slot + 1) % n;
        } while (cnt < n);
    }
    *(int*)(param_1 + 0xa4) = slot;
    if (cnt < n) {
        return h + 0x10;
    }
    *(int*)(param_1 + 0xa8) = 0x5500aaff;
    longjmp((void*)(param_1 + 0x10), 0x2721);
    return 0;
}

// @ 0x008d1330
void* tsi_ReAllocMem(int param_1, char* param_2, int param_3)
{
    char* base;
    int n;
    int slot;
    void* np;
    if (param_2 == 0)
        return 0;
    base = param_2 - 0x10;
    if ((*(int*)base != (int)0xaa53c5aa && param_1 != 0) ||
        (base[*(int*)(base + 4) + 0x10] != 0x5a && param_1 != 0) ||
        (base[*(int*)(base + 4) + 0x11] != (char)0xf0 && param_1 != 0)) {
        *(int*)(param_1 + 0xa8) = 0x5500aaff;
        longjmp((void*)(param_1 + 0x10), 0x2719);
    }
    n = *(int*)(param_1 + 4);
    if (n < 1 || *(int*)(param_1 + 8) < n) {
        *(int*)(param_1 + 0xa8) = 0x5500aaff;
        longjmp((void*)(param_1 + 0x10), 0x271d);
    }
    slot = *(int*)(base + 8);
    np = ff_realloc(base, param_3 + 0x12);
    *(void**)(*(int*)(param_1 + 0xc) + slot * 4) = np;
    if (np == 0) {
        *(int*)(param_1 + 0xa8) = 0x5500aaff;
        longjmp((void*)(param_1 + 0x10), 0x271e);
    }
    if (*(int*)np != (int)0xaa53c5aa) {
        *(int*)(param_1 + 0xa8) = 0x5500aaff;
        longjmp((void*)(param_1 + 0x10), 0x2719);
    }
    *(int*)((char*)np + 4) = param_3;
    *((char*)np + param_3 + 0x10) = 0x5a;
    *((char*)np + param_3 + 0x11) = (char)0xf0;
    if (slot >= *(int*)(param_1 + 8)) {
        *(int*)(param_1 + 0xa8) = 0x5500aaff;
        longjmp((void*)(param_1 + 0x10), 0x271f);
    }
    return (char*)np + 0x10;
}

// @ 0x008d1440
void tsi_DeAllocMem(int param_1, char* param_2)
{
    char* base;
    int slot;
    if (param_2 == 0)
        return;
    base = param_2 - 0x10;
    if ((*(int*)base != (int)0xaa53c5aa && param_1 != 0) ||
        (base[*(int*)(base + 4) + 0x10] != 0x5a && param_1 != 0) ||
        (base[*(int*)(base + 4) + 0x11] != (char)0xf0 && param_1 != 0)) {
        *(int*)(param_1 + 0xa8) = 0x5500aaff;
        longjmp((void*)(param_1 + 0x10), 0x2719);
    }
    slot = *(int*)(base + 8);
    if (*(char**)(*(int*)(param_1 + 0xc) + slot * 4) != base) {
        *(int*)(param_1 + 0xa8) = 0x5500aaff;
        longjmp((void*)(param_1 + 0x10), 0x271f);
    }
    *(void**)(*(int*)(param_1 + 0xc) + slot * 4) = 0;
    --*(int*)(param_1 + 4);
    ff_free(base);
}

// @ 0x008d14d0
void* tsi_FastAllocN(int param_1, unsigned param_2, int param_3)
{
    if (*(int*)(param_1 + 0x88 + param_3 * 4) != 0) {
        *(int*)(param_1 + 0x88 + param_3 * 4) = 0;
        if (param_2 > *(unsigned*)(param_1 + 0x6c + param_3 * 4)) {
            tsi_DeAllocMem(param_1, *(char**)(param_1 + 0x50 + param_3 * 4));
            *(void**)(param_1 + 0x50 + param_3 * 4) = tsi_AllocMem(param_1, param_2);
            *(unsigned*)(param_1 + 0x6c + param_3 * 4) = param_2;
        }
        return *(void**)(param_1 + 0x50 + param_3 * 4);
    }
    return tsi_AllocMem(param_1, param_2);
}

// @ 0x008d1530
void tsi_FreeFastMemBlocks(int param_1)
{
    int* p = (int*)(param_1 + 0x50);
    int n = 7;
    do {
        tsi_DeAllocMem(param_1, (char*)p[0]);
        p[0] = 0;
        p[7] = 0;
        p[0xe] = 1;
        ++p;
        --n;
    } while (n != 0);
}

// @ 0x008d1570
void tsi_DeleteMemhandler(int param_1)
{
    tsi_FreeFastMemBlocks(param_1);
    ff_free(*(void**)(param_1 + 0xc));
    ff_free((void*)param_1);
}

// @ 0x008d1590
int util_FixMul(int param_1, int param_2)
{
    int sign;
    if (param_1 < 0) {
        param_1 = -param_1;
        sign = -1;
        if (param_2 >= 0)
            goto calc;
        sign = 1;
    } else {
        sign = 1;
        if (param_2 >= 0)
            goto calc;
        sign = -1;
    }
    param_2 = -param_2;
calc:
    {
        unsigned hi1 = (param_1 >> 0x10) & 0xffff;
        unsigned hi2 = (param_2 >> 0x10) & 0xffff;
        unsigned lo1 = param_1 & 0xffff;
        unsigned lo2 = param_2 & 0xffff;
        return (int)(((lo1 * lo2) >> 0x10) + lo2 * hi1 + lo1 * hi2 + hi1 * hi2 * 0x10000) * sign;
    }
}

// @ 0x008d1600
int util_FixMulDiv(int param_1, int param_2)
{
    int sign;
    if (param_1 < 0) {
        param_1 = -param_1;
        sign = -1;
        if (param_2 >= 0)
            goto calc;
        sign = 1;
    } else {
        sign = 1;
        if (param_2 >= 0)
            goto calc;
        sign = -1;
    }
    param_2 = -param_2;
calc:
    {
        unsigned hi1 = (param_1 >> 0x10) & 0xffff;
        unsigned hi2 = (param_2 >> 0x10) & 0xffff;
        return (int)(((hi1 * 0x10000 + (param_1 & 0xffff)) * hi2
                      + (param_2 & 0xffff) * hi1) * 0x400
                     + (((param_2 & 0xffff) * (param_1 & 0xffff)) >> 6)) * sign;
    }
}

// @ 0x008d1670
int util_ShortFracMul(int param_1, short param_2)
{
    int sign;
    if (param_1 < 0) {
        param_1 = -param_1;
        sign = -1;
        if (param_2 >= 0)
            goto calc;
        sign = 1;
    } else {
        sign = 1;
        if (param_2 >= 0)
            goto calc;
        sign = -1;
    }
    param_2 = (short)-param_2;
calc:
    {
        unsigned u = (unsigned short)param_2;
        unsigned hi1 = (param_1 >> 0x10) & 0xffff;
        return (int)((((param_1 & 0xffff) * u + 0x2000) >> 0xe) + hi1 * u * 4) * sign;
    }
}

// @ 0x008d16d0
int util_FixDiv(unsigned param_1, unsigned param_2)
{
    unsigned q;
    unsigned rem;
    int sign;
    if ((int)param_1 < 0) {
        param_1 = -param_1;
        sign = -1;
        if ((int)param_2 >= 0)
            goto div;
        sign = 1;
    } else {
        sign = 1;
        if ((int)param_2 >= 0)
            goto div;
        sign = -1;
    }
    param_2 = -param_2;
div:
    q = param_1 / param_2;
    rem = param_1 % param_2;
    q = q * 0x10000;
    while (rem > 0xffff) {
        rem >>= 1;
        param_2 = (unsigned)((int)param_2 >> 1);
    }
    return (int)((rem << 0x10) / param_2 + q) * sign;
}

// @ 0x008d1730
int util_FixSin(int param_1)
{
    int d;
    int i1;
    int i3;
    if (param_1 > 0x5a0000)
        param_1 = 0x5a0000;
    else if (param_1 < 0)
        param_1 = 0;
    d = param_1 / 0x5a - 0x8000;
    i1 = (d * d) >> 0xf;
    i3 = (i1 * d) >> 0xf;
    {
        int r = ((((i1 * i1) >> 0xf) * 0x2c7) >> 0xf)
              + ((((i3 * i1) >> 0xf) * 0x72) >> 0xf)
              + ((d * 0x4716) >> 0xe)
              + ((i1 * -0x37cc) >> 0xf)
              + 0xb507
              + ((i3 * -0xe9e) >> 0xf);
        if (r > 0x10000)
            r = 0x10000;
        return r;
    }
}

// @ 0x008d17d0
int util_EuclidianDistance(int param_1, int param_2)
{
    int x, y, t;
    if (param_1 < 0)
        param_1 = -param_1;
    if (param_2 < 0)
        param_2 = -param_2;
    if (param_1 == 0)
        return param_2;
    if (param_2 == 0)
        return param_1;
    if (param_1 > param_2)
        t = (param_2 >> 1) + param_1;
    else
        t = (param_1 >> 1) + param_2;
    {
        int u, v;
        u = util_FixMul(param_1, util_FixDiv(param_1, t));
        v = util_FixMul(param_2, util_FixDiv(param_2, t));
        t = (v + 1 + u + t) >> 1;
        u = util_FixMul(param_1, util_FixDiv(param_1, t));
        v = util_FixMul(param_2, util_FixDiv(param_2, t));
        t = (v + 1 + u + t) >> 1;
        u = util_FixMul(param_1, util_FixDiv(param_1, t));
        v = util_FixMul(param_2, util_FixDiv(param_2, t));
        return (v + 1 + u + t) >> 1;
    }
}

// @ 0x008d1890
void util_ComputeIntersection(short p1, short p2, short p3, short p4,
                              short p5, short p6, short p7, short p8,
                              short* o1, short* o2)
{
    int dx, dy;
    int num, den;
    dx = p3 - p1;
    dy = p4 - p2;
    den = (p7 - p5) * dy - (p8 - p6) * dx;
    if (den != 0) {
        int num2 = (p6 - p2) * dx - (p5 - p1) * dy;
        int u = util_FixDiv((unsigned)num2, (unsigned)den);
        *o1 = (short)(util_FixMul(p7 - p5, u) + p5);
        *o2 = (short)(util_FixMul(p8 - p6, u) + p6);
        return;
    }
    {
        int a = p3 + p5;
        *o1 = (short)((a - (a >> 31)) >> 1);
        a = p4 + p6;
        *o2 = (short)((a - (a >> 31)) >> 1);
    }
}

// @ 0x008d1960
int FUN_008d1960(unsigned param_1)
{
    if ((param_1 & 1) == 0)
        return 0;
    if (param_1 - ((int)param_1 / 3) * 3 == 0)
        return 0;
    if (param_1 - ((int)param_1 / 5) * 5 == 0)
        return 0;
    if ((int)(param_1 - ((int)param_1 / 7) * 7) == 0)
        return 0;
    if ((int)param_1 > 0xb) {
        if (param_1 - ((int)param_1 / 0xb) * 0xb == 0)
            return 0;
        if ((int)param_1 > 0xd) {
            if (param_1 - ((int)param_1 / 0xd) * 0xd == 0)
                return 0;
        }
    }
    return 1;
}

// @ 0x008d1a00
int* New_hashClass(int param_1, int param_2, int param_3, int param_4)
{
    int* h;
    int size;
    int i;
    h = (int*)tsi_AllocMem(param_1, 0x30);
    h[6] = param_3;
    h[7] = param_4;
    size = ((param_2 * 2 + 3) / 3 + 2 + param_2) >> 1;
    size = size * 2 + 3;
    h[3] = param_2;
    h[0] = param_1;
    h[2] = 0;
    h[4] = 0;
    h[9] = 0;
    h[10] = 0x100;
    h[0xb] = 0;
    i = FUN_008d1960((unsigned)size);
    while (i == 0) {
        size += 2;
        i = FUN_008d1960((unsigned)size);
    }
    h[5] = size;
    h[8] = (int)tsi_AllocMem(param_1, size * 4);
    i = 0;
    if (size > 0) {
        do {
            *(short*)(h[8] + i * 4) = (short)0xffff;
            *(short*)(h[8] + i * 4 + 2) = (short)0xffff;
            ++i;
        } while (i < size);
    }
    return h;
}

// @ 0x008d1ac0
int get_using_uint16_hashClass(int param_1, unsigned short param_2, unsigned short* out)
{
    int* tbl = *(int**)(param_1 + 0x20);
    int mod = *(int*)(param_1 + 0x14);
    unsigned idx = param_2;
    int slot;
    for (;;) {
        slot = (int)idx % mod;
        unsigned short v = *(unsigned short*)((char*)tbl + slot * 4);
        if (v == 0xffff && *(short*)((char*)tbl + slot * 4 + 2) == (short)0xffff)
            break;
        if (v == param_2) {
            *(int*)(param_1 + 4) = slot;
            *out = *(unsigned short*)((char*)tbl + slot * 4 + 2);
            return 1;
        }
        idx = slot + 1;
    }
    *(int*)(param_1 + 4) = slot;
    *out = 0xffff;
    return 0;
}
