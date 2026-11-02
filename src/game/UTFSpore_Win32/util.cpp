// src/game/UTFSpore_Win32/util.cpp -- migrated from slice(s) s008d1b30, s008d0c10 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/util.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include <math.h>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void* tsi_AllocMem(int tbl, int size);

// ---- items of slice s008d0c10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct tsiMemObject;
struct hashEntry;
struct tsiMemObject {          // size 0xb0
    unsigned long stamp1;      // +0x00
    long numPointers;          // +0x04
    long maxPointers;          // +0x08
    void** base;               // +0x0c
    int env[16];               // +0x10  setjmp buffer
    void* fast_base[7];        // +0x50
    unsigned long fast_size[7];// +0x6c
    int fast_free[7];          // +0x88
    unsigned long ii;          // +0xa4
    unsigned long state;       // +0xa8
    unsigned long stamp2;      // +0xac
};
struct hashEntry {             // size 0x4
    unsigned short key;        // +0x0
    unsigned short value;      // +0x2
};
struct hashClass {             // size 0x30
    tsiMemObject* mem;         // +0x00
    long x;                    // +0x04
    long numItems;             // +0x08
    long maxItems;             // +0x0c
    long enum_x;               // +0x10
    long m;                    // +0x14
    void* stringsAreEqual;     // +0x18
    void* privPtr;             // +0x1c
    hashEntry* hash;           // +0x20
    hashEntry* UE_hash;        // +0x24
    long first_UE_code;        // +0x28
    long num_UE_codes;         // +0x2c
};
extern "C" void* tsi_AllocMem(int tbl, int size);
int __fastcall FUN_008d1960(unsigned n);
// ---- items of slice s008d0c10 end

// ---- items of slice s008d1b30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void tsi_DeAllocMem(void* pool, void* p);
struct TsiHashExtra {
    const char* mpName;       // +0x00
    unsigned short mValue;    // +0x04 (+2 pad)
};
struct TsiHashClass {
    void*    mpPool;          // +0x00  pool passed to tsi_DeAllocMem
    int      mnFreeSlot;      // +0x04  current/next open bucket
    int      mnUsedCount;     // +0x08  number of used buckets
    void*    mpfnHashStr;     // +0x0c
    int      mnReserved10;    // +0x10
    int      mnBuckets;       // +0x14  hash modulus (idiv divisor)
    void*    mpfnCompare;     // +0x18  (int(*)(void* ctx, const char* str, unsigned short key))
    void*    mpCompareArg;    // +0x1c  first argument of the compare callback
    unsigned short* mpTable;  // +0x20  [key,value] pairs
    TsiHashExtra* mpExtra;    // +0x24  optional side table
    int      mnReserved28;    // +0x28
    int      mnExtraCount;    // +0x2c
};
int get_using_uint16_hashClass(TsiHashClass* h, unsigned key, unsigned short* outValue);               // 0x8d1ac0
// ---- items of slice s008d1b30 end

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
        unsigned lo1 = (unsigned)param_1 & 0xffff;
        unsigned lo2 = (unsigned)param_2 & 0xffff;
        return (int)(((hi1 * 0x10000 + lo1) * hi2 + lo2 * hi1) * 0x400
                     + ((lo2 * lo1) >> 6)) * sign;
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
void util_ComputeIntersection(short p1, short p2, short p3, short p4, short p5, short p6, short p7, short p8, short* o1, short* o2)
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
int __fastcall FUN_008d1960(unsigned param_1)
{
    if ((param_1 & 1) == 0)
        return 0;
    if ((int)param_1 % 3 == 0)
        return 0;
    if ((int)param_1 % 5 == 0)
        return 0;
    if ((int)param_1 % 7 == 0)
        return 0;
    if ((int)param_1 > 0xb) {
        if ((int)param_1 % 0xb == 0)
            return 0;
        if ((int)param_1 > 0xd) {
            if ((int)param_1 % 0xd == 0)
                return 0;
        }
    }
    return 1;
}

// @ 0x008d1a00
int* New_hashClass(int param_1, int param_2, int param_3, int param_4)
{
    hashClass* h;
    int size;
    int i;
    h = (hashClass*)tsi_AllocMem(param_1, 0x30);
    h->maxItems = param_2;
    h->stringsAreEqual = (void*)param_3;
    h->privPtr = (void*)param_4;
    size = ((param_2 * 2 + 3) / 3 + 2 + param_2) >> 1;
    size = size * 2 + 3;
    h->mem = (tsiMemObject*)param_1;
    h->numItems = 0;
    h->enum_x = 0;
    h->UE_hash = 0;
    h->first_UE_code = 0x100;
    h->num_UE_codes = 0;
    i = FUN_008d1960((unsigned)size);
    while (i == 0) {
        size += 2;
        i = FUN_008d1960((unsigned)size);
    }
    h->m = size;
    h->hash = (hashEntry*)tsi_AllocMem(param_1, size * 4);
    i = 0;
    if (size > 0) {
        do {
            h->hash[i].key = 0xffff;
            h->hash[i].value = 0xffff;
            ++i;
        } while (i < size);
    }
    return (int*)h;
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

// @ 0x008d1b30
int get_using_str_hashClass(TsiHashClass* h, const char* str, unsigned short* outValue)
{
    const char* p = str;
    int key = 0;
    while (*p) {
        key = (key * 0x100 + (signed char)*p) % h->mnBuckets;
        p++;
    }
    for (;;) {
        unsigned short* e = &h->mpTable[key * 2];
        if (e[0] == 0xffff && e[1] == 0xffff)
            break;
        int (__cdecl* cmp)(void*, const char*, unsigned short);
        cmp = (int (__cdecl*)(void*, const char*, unsigned short))h->mpfnCompare;
        if (cmp(h->mpCompareArg, str, e[0]) != 0) {
            h->mnFreeSlot = key;
            *outValue = h->mpTable[key * 2 + 1];
            return 1;
        }
        key = (key + 1) % h->mnBuckets;
    }
    h->mnFreeSlot = key;
    TsiHashExtra* ex = h->mpExtra;
    if (ex) {
        for (int i = 0; i < h->mnExtraCount; ++i) {
            if (strcmp(ex[i].mpName, str) == 0) {
                *outValue = ex[i].mValue;
                return 1;
            }
        }
    }
    *outValue = 0xffff;
    return 0;
}

// @ 0x008d1c50
void put_hashClass(TsiHashClass* h, unsigned key, unsigned short value, const char* str)
{
    unsigned short* table = h->mpTable;
    unsigned short found;
    int ok;
    if (str)
        ok = get_using_str_hashClass(h, str, &found);
    else
        ok = get_using_uint16_hashClass(h, key, &found);
    if (ok) {
        table[h->mnFreeSlot * 2 + 1] = value;
        return;
    }
    table[h->mnFreeSlot * 2] = (unsigned short)key;
    table[h->mnFreeSlot * 2 + 1] = value;
    h->mnUsedCount++;
}

// @ 0x008d1cb0
void Delete_hashClass(TsiHashClass* h)
{
    if (!h)
        return;
    if (h->mpExtra)
        tsi_DeAllocMem(h->mpPool, h->mpExtra);
    tsi_DeAllocMem(h->mpPool, h->mpTable);
    tsi_DeAllocMem(h->mpPool, h);
}
