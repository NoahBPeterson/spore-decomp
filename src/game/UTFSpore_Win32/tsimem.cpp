// src/game/UTFSpore_Win32/tsimem.cpp -- migrated from slice(s) s008d0c10 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/tsimem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) __declspec(noreturn)
void __cdecl longjmp(void* env, int val);    // __imp_longjmp
extern "C" void* tsi_AllocMem(int tbl, int size);
extern "C" void  tsi_DeAllocMem(int tbl, char* p);
extern "C" void  tsi_EmergencyShutDown(int tbl);

// ---- items of slice s008d0c10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct tsiMemObject;
struct tsiMemHeader {          // 16-byte header in front of every user block
    unsigned long stamp1;      // +0x00  0xaa53c5aa
    unsigned long size;        // +0x04  user byte count
    long index;                // +0x08  slot in tsiMemObject::base
    unsigned long pad_0c;      // +0x0c
    unsigned char data[1];     // +0x10  user bytes, then 'Z', 0xf0 guard
};
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
void* ff_malloc(unsigned size);              // 0x008a7760  ?ff_malloc@@YAPAXI@Z
void  ff_free(void* p);                      // 0x008a7770  ?ff_free@@YAXPAX@Z
void* ff_realloc(void* p, unsigned size);    // 0x008a7780  ?ff_realloc@@YAPAXPAXI@Z
extern "C" __declspec(dllimport) __declspec(noreturn)
void __cdecl longjmp(void* env, int val);    // __imp_longjmp
extern "C" void* tsi_AllocMem(int tbl, int size);
extern "C" void  tsi_DeAllocMem(int tbl, char* p);
extern "C" void  tsi_EmergencyShutDown(int tbl);
// ---- items of slice s008d0c10 end

// @ 0x008d10c0
void tsi_Error(int param_1, int param_2)
{
    tsiMemObject* mem = (tsiMemObject*)param_1;
    if (mem != 0) {
        mem->state = 0x5500aaff;
        longjmp(mem->env, param_2);
    }
}

// @ 0x008d10f0
void* tsi_NewCustomSizeMemhandler(int* out_err, int count)
{
    tsiMemObject* m;
    int i;
    *out_err = 0;
    m = (tsiMemObject*)ff_malloc(0xb0);
    if (m == 0)
        goto err;
    m->maxPointers = count;
    m->stamp1 = 0xab1500ff;
    m->state = 0xaa005501;
    m->stamp2 = 0xa5a55a5a;
    m->numPointers = 0;
    m->ii = 0;
    m->base = (void**)ff_malloc(count * 4);
    if (m->base != 0) {
        i = 0;
        if (m->maxPointers > 0) {
            do {
                m->base[i] = 0;
                ++i;
            } while (i < m->maxPointers);
        }
        m->fast_base[0] = 0;
        m->fast_size[0] = 0;
        m->fast_base[1] = 0;
        m->fast_size[1] = 0;
        m->fast_base[2] = 0;
        m->fast_size[2] = 0;
        m->fast_base[3] = 0;
        m->fast_size[3] = 0;
        m->fast_base[4] = 0;
        m->fast_size[4] = 0;
        m->fast_base[5] = 0;
        m->fast_size[5] = 0;
        m->fast_base[6] = 0;
        m->fast_size[6] = 0;
        m->fast_free[0] = 1;
        m->fast_free[1] = 1;
        m->fast_free[2] = 1;
        m->fast_free[3] = 1;
        m->fast_free[4] = 1;
        m->fast_free[5] = 1;
        m->fast_free[6] = 1;
        return m;
    }
    ff_free(m);
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
    tsiMemObject* mem = (tsiMemObject*)param_1;
    tsiMemHeader* h;
    long n;
    unsigned long slot;
    int cnt;
    h = (tsiMemHeader*)ff_malloc(param_2 + 0x12);
    if (h == 0 && mem != 0) {
        mem->state = 0x5500aaff;
        longjmp(mem->env, 0x2718);
    }
    h->stamp1 = 0xaa53c5aa;
    h->size = param_2;
    h->data[param_2] = 0x5a;
    h->data[param_2 + 1] = 0xf0;
    n = mem->maxPointers;
    if (mem->numPointers >= n) {
        mem->state = 0x5500aaff;
        longjmp(mem->env, 0x271c);
    }
    slot = mem->ii;
    cnt = 0;
    {
    void** base = mem->base;
    if (n > 0) {
        do {
            if (base[slot] == 0) {
                base[slot] = h;
                h->index = (long)slot;
                ++mem->numPointers;
                break;
            }
            ++cnt;
            slot = (slot + 1) % n;
        } while (cnt < n);
    }
    }
    mem->ii = slot;
    if (cnt >= n) {
        mem->state = 0x5500aaff;
        longjmp(mem->env, 0x2721);
    }
    return h->data;
}

// @ 0x008d1330
void* tsi_ReAllocMem(int param_1, char* param_2, int param_3)
{
    if (param_2 != 0) {
        tsiMemObject* mem = (tsiMemObject*)param_1;
        tsiMemHeader* base = (tsiMemHeader*)(param_2 - 0x10);
        tsiMemHeader* np;
        void** tbl;
        long nPtr;
        long slot;
        if (base->stamp1 != 0xaa53c5aa && mem != 0) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x2719);
        }
        unsigned long sz = base->size;
        if (base->data[sz] != 0x5a && mem != 0) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x2719);
        }
        if (base->data[sz + 1] != 0xf0 && mem != 0) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x2719);
        }
        nPtr = mem->numPointers;
        tbl = mem->base;
        if (nPtr <= 0)
            goto badptr;
        if (nPtr > mem->maxPointers)
            goto badptr;
        goto ptr_ok;
    badptr:
        mem->state = 0x5500aaff;
        longjmp(mem->env, 0x271d);
    ptr_ok:
        slot = base->index;
        np = (tsiMemHeader*)ff_realloc(base, param_3 + 0x12);
        tbl[slot] = np;
        if (np == 0) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x271e);
        }
        if (np->stamp1 != 0xaa53c5aa) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x2719);
        }
        np->size = param_3;
        np->data[param_3] = 0x5a;
        np->data[param_3 + 1] = 0xf0;
        if (slot >= mem->maxPointers) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x271f);
        }
        return np->data;
    }
    return 0;
}

// @ 0x008d1440
void tsi_DeAllocMem(int param_1, char* param_2)
{
    if (param_2 != 0) {
        tsiMemObject* mem = (tsiMemObject*)param_1;
        tsiMemHeader* base = (tsiMemHeader*)(param_2 - 0x10);
        long slot;
        void** tbl;
        if (base->stamp1 != 0xaa53c5aa && mem != 0) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x2719);
        }
        unsigned long sz = base->size;
        if (base->data[sz] != 0x5a && mem != 0) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x2719);
        }
        if (base->data[sz + 1] != 0xf0 && mem != 0) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x2719);
        }
        tbl = mem->base;
        slot = base->index;
        if (tbl[slot] != (void*)base) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x271f);
        }
        tbl[slot] = 0;
        --mem->numPointers;
        ff_free(base);
    }
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
