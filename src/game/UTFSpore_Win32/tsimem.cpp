// Memory handler pool.  Every user block carries a 16-byte header (tsiMemHeader) whose
// stamp1, size and index the pool validates on every call, with a 'Z'/0xf0 guard after the
// user bytes.  The pool object (tsiMemObject) keeps a slot table (base) plus seven fast
// blocks, and reports every error by longjmp() through its own setjmp buffer (env).

#include "game/types.h"

// underlying C allocator (address in the comment)
void* ff_malloc(unsigned size);              // 0x008a7760  ?ff_malloc@@YAPAXI@Z
void  ff_free(void* p);                      // 0x008a7770  ?ff_free@@YAXPAX@Z
void* ff_realloc(void* p, unsigned size);    // 0x008a7780  ?ff_realloc@@YAPAXPAXI@Z
extern "C" __declspec(dllimport) __declspec(noreturn)
void __cdecl longjmp(void* env, int val);    // __imp_longjmp

// Error codes passed to longjmp by tsi_Error.
enum {
    TSI_ERR_BAD_BLOCK   = 0x2718,  // allocation failed / corrupt block header
    TSI_ERR_BAD_STAMP   = 0x2719,  // header stamp or guard byte wrong
    TSI_ERR_TOO_MANY    = 0x271c,  // slot table full
    TSI_ERR_BAD_HANDLE  = 0x271d,  // live-pointer count out of range
    TSI_ERR_REALLOC     = 0x271e,  // realloc returned no memory
    TSI_ERR_BAD_SLOT    = 0x271f,  // slot does not own the block
    TSI_ERR_NO_SLOT     = 0x2721   // no free slot found in a full table
};

// Header stamp word and the guard byte pair that ends every block.
static const unsigned long kStamp1 = 0xaa53c5aa;
static const unsigned long kStateError = 0x5500aaff;
static const unsigned char kGuard1 = 0x5a;   // 'Z'
static const unsigned char kGuard2 = 0xf0;
static const int kNumFastBlocks = 7;         // length of the fast_base/fast_size/fast_free arrays

struct tsiMemObject;

struct tsiMemHeader {          // 16-byte header in front of every user block
    unsigned long stamp1;      // +0x00  kStamp1
    unsigned long size;        // +0x04  user byte count
    long index;                // +0x08  slot in tsiMemObject::base
    unsigned long pad_0c;      // +0x0c
    unsigned char data[1];     // +0x10  user bytes, then 'Z', 0xf0 guard
};
struct tsiMemObject {          // size 0xb0
    unsigned long stamp1;      // +0x00
    long numPointers;          // +0x04  slots in use
    long maxPointers;          // +0x08  slots allocated
    void** base;               // +0x0c  slot table
    int env[16];               // +0x10  setjmp buffer
    void* fast_base[7];        // +0x50  seven cacheable fast blocks
    unsigned long fast_size[7];// +0x6c  size each fast block was allocated with
    int fast_free[7];          // +0x88  non-zero when the fast block is free
    unsigned long ii;          // +0xa4  next slot to search from
    unsigned long state;       // +0xa8
    unsigned long stamp2;      // +0xac
};

extern "C" void* tsi_AllocMem(int tbl, int size);           // 0x008d1260
extern "C" void  tsi_DeAllocMem(int tbl, char* p);          // 0x008d1440
extern "C" void  tsi_EmergencyShutDown(int tbl);            // 0x008d1210

// @ 0x008d10c0
void tsi_Error(int tbl, int code)
{
    tsiMemObject* mem = (tsiMemObject*)tbl;
    if (mem != 0) {
        mem->state = kStateError;
        longjmp(mem->env, code);
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
void tsi_EmergencyShutDown(int tbl)
{
    tsiMemObject* mem = (tsiMemObject*)tbl;
    int* slots;
    long i;
    long n;
    if (mem == 0)
        return;
    n = mem->maxPointers;
    slots = (int*)mem->base;
    i = 0;
    if (n > 0) {
        do {
            int p = slots[i];
            if (p != 0)
                ff_free((void*)p);
            ++i;
        } while (i < n);
    }
    ff_free(slots);
    ff_free(mem);
}

// @ 0x008d1260
void* tsi_AllocMem(int tbl, int size)
{
    tsiMemObject* mem = (tsiMemObject*)tbl;
    tsiMemHeader* h;
    long n;
    unsigned long slot;
    int cnt;
    h = (tsiMemHeader*)ff_malloc(size + 0x12);
    if (h == 0 && mem != 0) {
        mem->state = kStateError;
        longjmp(mem->env, TSI_ERR_BAD_BLOCK);
    }
    h->stamp1 = kStamp1;
    h->size = size;
    h->data[size] = kGuard1;
    h->data[size + 1] = kGuard2;
    n = mem->maxPointers;
    if (mem->numPointers >= n) {
        mem->state = kStateError;
        longjmp(mem->env, TSI_ERR_TOO_MANY);
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
        mem->state = kStateError;
        longjmp(mem->env, TSI_ERR_NO_SLOT);
    }
    return h->data;
}

// @ 0x008d1330
void* tsi_ReAllocMem(int tbl, char* p, int size)
{
    if (p != 0) {
        tsiMemObject* mem = (tsiMemObject*)tbl;
        tsiMemHeader* base = (tsiMemHeader*)(p - 0x10);
        tsiMemHeader* np;
        void** slots;
        long nPtr;
        long slot;
        if (base->stamp1 != kStamp1 && mem != 0) {
            mem->state = kStateError;
            longjmp(mem->env, TSI_ERR_BAD_STAMP);
        }
        unsigned long sz = base->size;
        if (base->data[sz] != kGuard1 && mem != 0) {
            mem->state = kStateError;
            longjmp(mem->env, TSI_ERR_BAD_STAMP);
        }
        if (base->data[sz + 1] != kGuard2 && mem != 0) {
            mem->state = kStateError;
            longjmp(mem->env, TSI_ERR_BAD_STAMP);
        }
        nPtr = mem->numPointers;
        slots = mem->base;
        if (nPtr <= 0)
            goto badptr;
        if (nPtr > mem->maxPointers)
            goto badptr;
        goto ptr_ok;
    badptr:
        mem->state = kStateError;
        longjmp(mem->env, TSI_ERR_BAD_HANDLE);
    ptr_ok:
        slot = base->index;
        np = (tsiMemHeader*)ff_realloc(base, size + 0x12);
        slots[slot] = np;
        if (np == 0) {
            mem->state = kStateError;
            longjmp(mem->env, TSI_ERR_REALLOC);
        }
        if (np->stamp1 != kStamp1) {
            mem->state = kStateError;
            longjmp(mem->env, TSI_ERR_BAD_STAMP);
        }
        np->size = size;
        np->data[size] = kGuard1;
        np->data[size + 1] = kGuard2;
        if (slot >= mem->maxPointers) {
            mem->state = kStateError;
            longjmp(mem->env, TSI_ERR_BAD_SLOT);
        }
        return np->data;
    }
    return 0;
}

// @ 0x008d1440
void tsi_DeAllocMem(int tbl, char* p)
{
    if (p != 0) {
        tsiMemObject* mem = (tsiMemObject*)tbl;
        tsiMemHeader* base = (tsiMemHeader*)(p - 0x10);
        long slot;
        void** slots;
        if (base->stamp1 != kStamp1 && mem != 0) {
            mem->state = kStateError;
            longjmp(mem->env, TSI_ERR_BAD_STAMP);
        }
        unsigned long sz = base->size;
        if (base->data[sz] != kGuard1 && mem != 0) {
            mem->state = kStateError;
            longjmp(mem->env, TSI_ERR_BAD_STAMP);
        }
        if (base->data[sz + 1] != kGuard2 && mem != 0) {
            mem->state = kStateError;
            longjmp(mem->env, TSI_ERR_BAD_STAMP);
        }
        slots = mem->base;
        slot = base->index;
        if (slots[slot] != (void*)base) {
            mem->state = kStateError;
            longjmp(mem->env, TSI_ERR_BAD_SLOT);
        }
        slots[slot] = 0;
        --mem->numPointers;
        ff_free(base);
    }
}

// @ 0x008d14d0
void* tsi_FastAllocN(int tbl, unsigned size, int i)
{
    tsiMemObject* mem = (tsiMemObject*)tbl;
    if (mem->fast_free[i] != 0) {
        mem->fast_free[i] = 0;
        if (size > mem->fast_size[i]) {
            tsi_DeAllocMem(tbl, (char*)mem->fast_base[i]);
            mem->fast_base[i] = tsi_AllocMem(tbl, size);
            mem->fast_size[i] = size;
        }
        return mem->fast_base[i];
    }
    return tsi_AllocMem(tbl, size);
}

// @ 0x008d1530
void tsi_FreeFastMemBlocks(int tbl)
{
    tsiMemObject* mem = (tsiMemObject*)tbl;
    int i = 0;
    do {
        tsi_DeAllocMem(tbl, (char*)mem->fast_base[i]);
        mem->fast_base[i] = 0;
        mem->fast_size[i] = 0;
        mem->fast_free[i] = 1;
        ++i;
    } while (i < kNumFastBlocks);
}

// @ 0x008d1570
void tsi_DeleteMemhandler(int tbl)
{
    tsiMemObject* mem = (tsiMemObject*)tbl;
    tsi_FreeFastMemBlocks(tbl);
    ff_free(mem->base);
    ff_free(mem);
}
