// Slice s00927be0 - pool allocator cores + critical-section locked wrappers.
// Optimized (/O2, no /GS cookies). The three large allocator cores are approximated.
#include "types.h"

extern "C" {
__declspec(dllimport) void __stdcall EnterCriticalSection(void*);
__declspec(dllimport) void __stdcall LeaveCriticalSection(void*);
}

struct CriSec {
    uint8_t pad[0x18];
    int     ref;      // +0x18
};

struct Chunk {
    uint32_t prevSize;   // +0
    uint32_t size;       // +4 (low 3 bits flags, 0x7ffffff8 size)
    Chunk*   fd;         // +8
    Chunk*   bk;         // +0xc
};

#define CHUNK_SIZE(p) ((p)->size & 0x7ffffff8)

// Soft-limit ("high fence") test: is chunk p (of size sz) allowed given the fence?
static inline bool FenceOK(uint32_t fence, uint32_t rev, Chunk* p, uint32_t sz)
{
    if (fence == 0)
        return true;
    if (rev == 0)
        return (uint32_t)p < fence;
    return fence <= sz + (uint32_t)p;
}

struct cLocalLightInfo {
    uint8_t  pad00[4];
    uint32_t maxFast;                // +0x04 (bit 0 = fast chunks present)
    uint8_t  pad08[0x430 - 8];
    uint32_t binMap[4];              // +0x430
    Chunk*   top;                    // +0x440
    Chunk*   lastRemainder;          // +0x444
    uint8_t  pad448[0x468 - 0x448];
    uint32_t fence;                  // +0x468 (high fence)
    uint8_t  fenceDisabled;          // +0x46c
    uint8_t  sysAllocEnabled;        // +0x46d
    uint8_t  pad46e[0x478 - 0x46e];
    uint32_t freeGuard;              // +0x478 (cleared around internal frees)
    uint8_t  pad47c[0x488 - 0x47c];
    int      mmapCount;              // +0x488
    uint8_t  pad48c[4];
    int      mmapMaxAllowed;         // +0x490
    uint32_t mmapThreshold;          // +0x494
    uint8_t  pad498[0x4ac - 0x498];
    bool (__cdecl* failFn)(cLocalLightInfo*, uint32_t, uint32_t, void*);   // +0x4ac
    void*    failCtx;                // +0x4b0
    uint32_t maxFailCount;           // +0x4b4
    uint8_t  pad4b8[0x4e4 - 0x4b8];
    CriSec* mCS;      // +0x4e4

    Chunk* Bin(uint32_t i) { return (Chunk*)((char*)this + 0x28 + i * 8); }

    __declspec(noinline) void* AllocCore(uint32_t size, uint32_t flags);   // 0x00927be0
    __declspec(noinline) void* AlignedAllocCore(uint32_t nBytes, uint32_t alignment, uint32_t offset, uint32_t flags); // 0x009282e0
    __declspec(noinline) void* ReallocCore(void* p, int sz, int a3);    // 0x00928730

    uint32_t BinIndex(uint32_t size);                  // 0x009267f0
    Chunk*   SplitChunk(Chunk* p, int size, uint32_t align, uint32_t a5, uint32_t a6, char flag); // 0x00926af0
    void     SetTop(Chunk* p, uint32_t size);          // 0x009268b0
    void     Free(void* mem);                          // 0x00926fd0

    __declspec(noinline) void* LockedAlloc(int a1, int a2, int a3, int a4, int a5, int a6);               // 0x009289f0
    __declspec(noinline) void* LockedAligned(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8); // 0x00928a30
    __declspec(noinline) void* LockedRealloc(int a1, int a2, int a3);                                     // 0x00928a80

    void  Shrink();                                    // 0x00927700 (consolidate fast chunks)
    void  PlaceInBin(Chunk* p, uint32_t sz, int z);    // 0x00926960
    void* BigAlloc(uint32_t size);                     // 0x00926f10
    Chunk* SysAlloc(uint32_t size);                    // 0x009272c0
};

uint32_t __cdecl RequestToSize(uint32_t req);          // 0x009267a0
void* __cdecl memcpy(void* dst, const void* src, unsigned count);      // 0x011e0744

extern cLocalLightInfo* g_pool;   // 0x016c8b44

// @ 0x009289f0
void* cLocalLightInfo::LockedAlloc(int a1, int a2, int a3, int a4, int a5, int a6)
{
    CriSec* cs = mCS;
    if (cs != 0) {
        EnterCriticalSection(cs);
        cs->ref++;
    }
    void* r = AllocCore(a1, a2);
    if (cs != 0) {
        cs->ref--;
        LeaveCriticalSection(cs);
    }
    return r;
}

// @ 0x00928a30
void* cLocalLightInfo::LockedAligned(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    CriSec* cs = mCS;
    if (cs != 0) {
        EnterCriticalSection(cs);
        cs->ref++;
    }
    void* r = AlignedAllocCore((uint32_t)a1, (uint32_t)a2, (uint32_t)a3, (uint32_t)a4);
    if (cs != 0) {
        cs->ref--;
        LeaveCriticalSection(cs);
    }
    return r;
}

// @ 0x00928a80
void* cLocalLightInfo::LockedRealloc(int a1, int a2, int a3)
{
    CriSec* cs = mCS;
    if (cs != 0) {
        EnterCriticalSection(cs);
        cs->ref++;
    }
    void* r = ReallocCore((void*)a1, a2, a3);
    if (cs != 0) {
        cs->ref--;
        LeaveCriticalSection(cs);
    }
    return r;
}

// @ 0x00928ad0
// Returns the block (eax from LockedAlloc, kept to ret in the original; the size-or-zero goes to
// *out via edx). This is StackAllocator's allocation callback; declared void, ours clobbered eax
// with the size and AllocateNewBlock wrote through it (hybrid crash at 0x928be9, 2026-10-12).
void* __cdecl Pool_AllocGlobal(unsigned size, unsigned* out)
{
    void* r = (void*)g_pool->LockedAlloc((int)size, 0, 0, 0, 0, 0);
    if (out != 0)
        *out = r ? size : 0;
    return r;
}

// ---------------------------------------------------------------- approximate cores
// @ 0x00927be0  SP::cSPMemPool::MallocCore (EA::Allocator::GeneralAllocator::MallocInternal)
void* cLocalLightInfo::AllocCore(uint32_t req, uint32_t flags)
{
    uint32_t idx = 0;
    uint32_t retries = 0;
    void* result = 0;
    uint32_t nb, rev, noBins;

    if (flags & 8)
        goto big;
    nb = RequestToSize(req);
restart:
    rev = flags & 1;
    noBins = flags & 0x200;
    if (noBins == 0) {
        if (nb <= maxFast && rev == 0) {
            Chunk** fb = (Chunk**)((char*)this + (nb >> 3) * 4);
            Chunk* p = *fb;
            if (p != 0) {
                p->size &= 0x7ffffffb;
                *fb = p->bk;
                return &p->fd;
            }
        }
        if (nb < 0x200) {
            idx = nb >> 3;
            Chunk* bin = Bin(idx);
            Chunk* p = bin->fd;
            if (p != bin) {
                if (fence != 0) {
                    bool ok;
                    if (rev == 0)
                        ok = (uint32_t)p < fence;
                    else
                        ok = (uint32_t)p + nb >= fence;
                    if (!ok)
                        goto mainloop;
                }
                *(uint32_t*)((char*)p + 4 + nb) |= 1;
                p->fd->bk = p->bk;
                p->bk->fd = p->fd;
                return &p->fd;
            }
        } else {
            if ((nb >> 6) <= 0x20)
                idx = (nb >> 6) + 0x38;
            else if ((nb >> 9) <= 0x14)
                idx = (nb >> 9) + 0x5b;
            else if ((nb >> 12) <= 10)
                idx = (nb >> 12) + 0x6e;
            else if ((nb >> 15) <= 4)
                idx = (nb >> 15) + 0x77;
            else if ((nb >> 18) <= 2)
                idx = (nb >> 18) + 0x7c;
            else
                idx = 0x7e;
            if (maxFast & 1)
                Shrink();
        }
    }
mainloop:
    for (;;) {
        if (noBins == 0) {
            Chunk* unsorted = Bin(1);
            Chunk* p = unsorted->fd;
            while (p != unsorted) {
                uint32_t fnc = fence;
                Chunk* nx = p->fd;
                uint32_t sz = CHUNK_SIZE(p);
                bool ok = FenceOK(fnc, rev, p, sz);
                if (nb < 0x200 && p == lastRemainder && nx == unsorted && nb + 0x10 < sz && ok) {
                    void* ret = &p->fd;
                    p->fd->bk = p->bk;
                    p->bk->fd = p->fd;
                    uint32_t rem = sz - nb;
                    if (rem > 0xf) {
                        Chunk* ub = unsorted->bk;
                        Chunk* r = (Chunk*)((char*)p + nb);
                        r->bk = ub;
                        r->fd = unsorted;
                        unsorted->bk = r;
                        ub->fd = r;
                        lastRemainder = r;
                        p->size = nb | 1;
                        r->size = rem | 1;
                        ((Chunk*)((char*)r + rem))->prevSize = rem;
                        return ret;
                    }
                    *(uint32_t*)((char*)p + 4 + sz) |= 1;
                    return ret;
                }
                unsorted->fd = nx;
                nx->bk = unsorted;
                if (sz == nb && ok) {
                    *(uint32_t*)((char*)p + 4 + sz) |= 1;
                    return &p->fd;
                }
                PlaceInBin(p, sz, 0);
                p = unsorted->fd;
            }

            if (nb >= 0x200) {
                Chunk* bin = Bin(idx);
                for (Chunk* q = bin->bk; q != bin; q = q->fd) {
                    uint32_t sz = CHUNK_SIZE(q);
                    if (nb <= sz) {
                        uint32_t fnc = fence;
                        bool take = false;
                        if (fnc == 0)
                            take = true;
                        else if (rev == 0)
                            take = (uint32_t)q < fnc;
                        else
                            take = fnc <= sz + (uint32_t)q;
                        if (take) {
                            void* ret = &q->fd;
                            q->fd->bk = q->bk;
                            q->bk->fd = q->fd;
                            uint32_t rem = sz - nb;
                            if (rem > 0xf) {
                                Chunk* ub = unsorted->bk;
                                Chunk* r = (Chunk*)((char*)q + nb);
                                r->fd = unsorted;
                                r->bk = ub;
                                unsorted->bk = r;
                                ub->fd = r;
                                q->size = nb | 1;
                                r->size = rem | 1;
                                ((Chunk*)((char*)r + rem))->prevSize = rem;
                                return ret;
                            }
                            *(uint32_t*)((char*)q + 4 + sz) |= 1;
                            return ret;
                        }
                    }
                }
            }

            idx++;
            Chunk* bin = Bin(idx);
            uint32_t word = (int)idx >> 5;
            uint32_t map = binMap[word];
            uint32_t bit = 1u << (idx & 0x1f);
            for (;;) {
                if (map < bit || bit == 0) {
                    uint32_t* mp = &binMap[word];
                    do {
                        word++;
                        mp++;
                        if (word > 3)
                            goto usetop;
                        map = *mp;
                    } while (map == 0);
                    bin = (Chunk*)((char*)this + 0x28 + word * 0x100);
                    bit = 1;
                }
                while ((map & bit) == 0) {
                    bin = (Chunk*)((char*)bin + 8);
                    bit = bit * 2;
                }
                Chunk* q = bin->fd;
                if (q == bin) {
                    map &= ~bit;
                    bin = (Chunk*)((char*)bin + 8);
                    binMap[word] = map;
                    bit = bit * 2;
                    continue;
                }
                uint32_t sz = q->size;
                uint32_t fnc = fence;
                for (;;) {
                    sz &= 0x7ffffff8;
                    if (fnc == 0 || FenceOK(fnc, rev, q, sz)) {
                        if (q == bin) {
                            bin = (Chunk*)((char*)bin + 8);
                            bit = bit * 2;
                            break;
                        }
                        void* ret = &q->fd;
                        q->fd->bk = q->bk;
                        q->bk->fd = q->fd;
                        uint32_t rem = sz - nb;
                        if (rem > 0xf) {
                            Chunk* ub = unsorted->bk;
                            Chunk* r = (Chunk*)((char*)q + nb);
                            r->fd = unsorted;
                            r->bk = ub;
                            unsorted->bk = r;
                            ub->fd = r;
                            if (nb < 0x200)
                                lastRemainder = r;
                            q->size = nb | 1;
                            r->size = rem | 1;
                            ((Chunk*)((char*)r + rem))->prevSize = rem;
                            return ret;
                        }
                        *(uint32_t*)((char*)q + 4 + sz) |= 1;
                        return ret;
                    }
                    q = q->fd;
                    sz = q->size;
                    if (q == bin) {
                        bin = (Chunk*)((char*)bin + 8);
                        bit = bit * 2;
                        break;
                    }
                }
            }
        }
    usetop:
        {
            Chunk* t = top;
            uint32_t tsz = CHUNK_SIZE(t);
            if (nb + 0x10 <= tsz) {
                Chunk* rem;
                Chunk* ret;
                uint32_t remSz;
                if (rev == 0) {
                    remSz = tsz - nb;
                    rem = (Chunk*)((char*)t + nb);
                    t->size = nb | 1;
                    rem->size = remSz | 1;
                    ret = t;
                } else {
                    ret = (Chunk*)((char*)t - nb + tsz);
                    rem = t;
                    if (((uint32_t)ret & 7) == 0) {
                        remSz = tsz - nb;
                        ret->size = nb;
                        *(uint32_t*)((char*)ret + 4 + nb) |= 1;
                        ((Chunk*)((char*)ret + nb))->prevSize = nb;
                    } else {
                        ret = (Chunk*)((uint32_t)ret & 0xfffffff8);
                        remSz = (uint32_t)ret - (uint32_t)t;
                        uint32_t rsz = tsz - remSz;
                        ret->size = rsz;
                        *(uint32_t*)((char*)ret + 4 + rsz) |= 1;
                        ((Chunk*)((char*)ret + rsz))->prevSize = rsz;
                    }
                }
                top = rem;
                rem->bk = rem;
                rem->fd = rem;
                rem->size = remSz | 1;
                ((Chunk*)((char*)rem + remSz))->prevSize = remSz;
                if (fenceDisabled == 0)
                    fence = (uint32_t)top + ((top->size >> 1) & 0x3ffffffc);
                return (char*)ret + 8;
            }
        }
        if ((maxFast & 1) == 0)
            break;
        Shrink();
        idx = nb >> 3;
    }

    if (noBins == 0) {
        if (sysAllocEnabled != 0 && nb >= mmapThreshold && mmapCount < mmapMaxAllowed) {
            result = BigAlloc(req);
            if (result != 0)
                return result;
        }
        if ((flags & 0x40000000) == 0 && fenceDisabled == 0) {
            if (rev == 0)
                flags |= 0x40000001;
            else
                flags = (flags & 0xfffffffc) | 0x40000000;
            idx = 0;
            retries = 0;
            result = 0;
            if (flags & 8)
                goto big;
        } else {
            if (sysAllocEnabled != 0) {
                Chunk* c = SysAlloc(nb);
                if (c != 0) {
                    *(uint32_t*)((char*)c + CHUNK_SIZE(c) + 4) |= 1;
                    result = (char*)c + 8;
                }
            }
            if (result != 0)
                return result;
            if (failFn == 0)
                return 0;
            retries++;
            if (retries >= maxFailCount)
                return 0;
            int depth = mCS->ref;
            int n = depth;
            if (n > 0) {
                do {
                    mCS->ref--;
                    LeaveCriticalSection(mCS);
                    n--;
                } while (n != 0);
            }
            bool okc = failFn(this, req, req + 0x40, failCtx);
            if (depth > 0) {
                do {
                    CriSec* cs = mCS;
                    EnterCriticalSection(cs);
                    cs->ref++;
                    depth--;
                } while (depth != 0);
            }
            if (!okc)
                return 0;
        }
    } else {
        flags &= 0xfffffdff;
    }
    goto restart;

big:
    return BigAlloc(req);
}

// @ 0x009282e0  pool aligned-alloc core (dlmalloc memalign with offset/flags)
void* cLocalLightInfo::AlignedAllocCore(uint32_t nBytes, uint32_t alignment, uint32_t offset, uint32_t flags)
{
    if (alignment <= 8 && offset == 0 && (flags & 0x400) == 0)
        return AllocCore(nBytes, flags);

    uint32_t align = alignment;
    if (align < 0x10)
        align = 0x10;
    if ((align & (align - 1)) != 0) {
        uint32_t a = align - 1;
        a |= a >> 1;
        a |= a >> 2;
        a |= a >> 4;
        a |= a >> 8;
        align = (a >> 16 | a) + 1;
    }
    if ((offset & 7) != 0)
        offset = (offset + 7) & 0xfffffff8u;

    uint32_t nb = nBytes + 0xb;
    if (nb <= 0x10)
        nb = 0x10;
    else
        nb &= 0xfffffff8u;
    uint32_t rev = flags & 1;

    if ((flags & 4) != 0 && (flags & 2) != 0) {
        uint32_t minChunk = 0;
        uint32_t maxChunk = 0;
        uint32_t idx = (nb < 0x200) ? (nb >> 3) : BinIndex(nb);

        Chunk* unsorted = Bin(1);
        for (Chunk* q = unsorted->bk; q != unsorted; q = q->bk) {
            uint32_t sz = q->size & 0x7ffffff8;
            if (nb <= sz) {
                uint32_t cand = (((uint32_t)q + align + 7 + offset) & (uint32_t)(-(int)align)) - offset - 8;
                if (cand + nb <= (uint32_t)q + sz && cand != 0) {
                    if ((uint32_t)q < (uint32_t)top - 0x1400000 &&
                        (minChunk == 0 || (uint32_t)q < minChunk))
                        minChunk = (uint32_t)q;
                    if ((uint32_t)top <= (uint32_t)q && maxChunk < (uint32_t)q)
                        maxChunk = (uint32_t)q;
                }
            }
        }
        for (uint32_t i = idx; i < 0x80; i++) {
            Chunk* bin = Bin(i);
            for (Chunk* q = bin->bk; q != bin; q = q->bk) {
                uint32_t sz = q->size & 0x7ffffff8;
                if (nb <= sz) {
                    uint32_t cand = (((uint32_t)q + align + 7 + offset) & (uint32_t)(-(int)align)) - offset - 8;
                    if (cand + nb <= (uint32_t)q + sz && cand != 0) {
                        if ((uint32_t)q < (uint32_t)top - 0x1400000 &&
                            (minChunk == 0 || (uint32_t)q < minChunk))
                            minChunk = (uint32_t)q;
                        if ((uint32_t)top <= (uint32_t)q && maxChunk < (uint32_t)q)
                            maxChunk = (uint32_t)q;
                    }
                }
            }
        }

        if (maxChunk != 0 && rev != 0) {
            Chunk* q = (Chunk*)maxChunk;
            return (char*)SplitChunk(q, (int)(q->size & 0x7ffffff8), align, nb, offset, 1) + 8;
        }

        Chunk* t = top;
        uint32_t tsz = t->size & 0x7ffffff8;
        if (tsz > 0x1400000)
            flags &= 0xfffffeffu;
        if (minChunk != 0 && (rev == 0 || (flags & 0x100) != 0)) {
            Chunk* q = (Chunk*)minChunk;
            return (char*)SplitChunk(q, (int)(q->size & 0x7ffffff8), align, nb, offset, 0) + 8;
        }
        if ((flags & 0x100) == 0 && tsz >= nb + align + 0x10 + offset && (flags & 1) != 0) {
            uint32_t delta = (((uint32_t)t + tsz - nb + offset + 8) & (uint32_t)(-(int)align)) - offset - 8;
            delta -= (uint32_t)t;
            uint32_t rem = tsz - delta;
            Chunk* ret = (Chunk*)((char*)t + delta);
            ret->size = rem;
            *(uint32_t*)((char*)ret + rem + 4) |= 1;
            *(uint32_t*)((char*)ret + rem) = rem;
            top = t;
            SetTop(t, delta);
            return (char*)ret + 8;
        }
    }

    void* p = AllocCore(nb + align + 0x10 + offset, flags);
    if (p == 0)
        return 0;

    Chunk* q = (Chunk*)((char*)p - 8);
    if (((uint32_t)p + offset) % align != 0) {
        q = (Chunk*)(((((uint32_t)p + align + offset - 1) & (uint32_t)(-(int)align)) - offset) - 8);
        Chunk* base = (Chunk*)((char*)p - 8);
        if ((uint32_t)((char*)q - (char*)base) < 0x10)
            q = (Chunk*)((char*)q + align);
        uint32_t delta = (uint32_t)q - (uint32_t)base;
        uint32_t newsize = (base->size & 0x7ffffff8) - delta;
        if ((base->size & 2) != 0) {
            q->prevSize = base->prevSize + delta;
            q->size = newsize | 2;
            *(uint32_t*)((char*)q + newsize) = newsize;
            return (char*)q + 8;
        }
        q->size = newsize | 1;
        *(uint32_t*)((char*)q + newsize + 4) |= 1;
        *(uint32_t*)((char*)q + newsize) = newsize;
        base->size = (base->size & 0x80000007) | delta;
        q->prevSize = delta;
        uint32_t saved = freeGuard;
        freeGuard = 0;
        Free((char*)base + 8);
        freeGuard = saved;
    }

    uint32_t qsize = q->size;
    if ((qsize & 2) != 0)
        return (char*)q + 8;
    qsize &= 0x7ffffff8;
    if (qsize <= nb + 0x10)
        return (char*)q + 8;

    uint32_t rem = qsize - nb;
    Chunk* tail = (Chunk*)((char*)q + nb);
    tail->size = rem | 1;
    *(uint32_t*)((char*)tail + rem + 4) |= 1;
    *(uint32_t*)((char*)tail + rem) = rem;
    q->size = (q->size & 0x80000007) | nb;

    if ((*(uint32_t*)((char*)tail + rem + 4) & 1) == 0) {
        Chunk* nx = (Chunk*)((char*)tail + rem);
        uint32_t nxSize = nx->size & 0x7ffffff8;
        nx->fd->bk = nx->bk;
        nx->bk->fd = nx->fd;
        uint32_t total = rem + nxSize;
        tail->size = total | 1;
        *(uint32_t*)((char*)tail + total) = total;
        if (tail == top || nx == top) {
            top = tail;
            SetTop(tail, total);
        } else {
            Chunk* unsorted = Bin(1);
            Chunk* bk = unsorted->bk;
            tail->fd = unsorted;
            tail->bk = bk;
            unsorted->bk = tail;
            bk->fd = tail;
        }
    } else {
        uint32_t saved = freeGuard;
        freeGuard = 0;
        Free((char*)tail + 8);
        freeGuard = saved;
    }
    return (char*)q + 8;
}

// @ 0x00928730  pool realloc core (dlmalloc realloc)
void* cLocalLightInfo::ReallocCore(void* p, int sz, int a3)
{
    if (p == 0)
        return AllocCore((uint32_t)sz, (uint32_t)a3);

    uint32_t nb = (uint32_t)sz + 0xb;
    if (nb <= 0x10)
        nb = 0x10;
    else
        nb &= 0xfffffff8u;
    Chunk* c = (Chunk*)((char*)p - 8);
    uint32_t head = c->size;
    uint32_t csize = head & 0x7ffffff8;

    if ((head & 2) != 0) {
        if (nb + 4 <= csize)
            return p;
        void* np = AllocCore(nb - 7, (uint32_t)a3);
        if (np == 0)
            return 0;
        uint32_t saved = freeGuard;
        freeGuard = 0;
        memcpy(np, p, csize - 8);
        Free(p);
        freeGuard = saved;
        return np;
    }

    uint32_t total = 0;
    if (nb <= csize) {
        total = csize;
    } else {
        Chunk* nx = (Chunk*)((char*)c + csize);
        if (nx == top) {
            uint32_t nsz = nx->size & 0x7ffffff8;
            if (csize + nsz >= nb + 0x10) {
                c->size = (head & 0x80000007) | nb;
                Chunk* nt = (Chunk*)((char*)c + nb);
                top = nt;
                SetTop(nt, csize + nsz - nb);
                return p;
            }
        }
        if (nx != top) {
            uint32_t nsz = nx->size & 0x7ffffff8;
            if ((*(uint32_t*)((char*)nx + nsz + 4) & 1) == 0) {
                if (nsz + csize >= nb) {
                    nx->fd->bk = nx->bk;
                    nx->bk->fd = nx->fd;
                    total = csize + nsz;
                }
            }
        }
        if (total == 0) {
            void* np = AllocCore(nb - 7, (uint32_t)a3);
            if (np == 0)
                return 0;
            Chunk* nc = (Chunk*)((char*)np - 8);
            if (nc == nx) {
                total = csize + (nc->size & 0x7ffffff8);
            } else {
                uint32_t copySize = csize - 4;
                uint32_t saved = freeGuard;
                freeGuard = 0;
                if (copySize > 0x20) {
                    memcpy(np, p, copySize);
                } else {
                    uint32_t* d = (uint32_t*)np;
                    const uint32_t* s = (const uint32_t*)p;
                    switch (copySize >> 2) {
                    case 8: *d++ = *s++;
                    case 7: *d++ = *s++;
                    case 6: *d++ = *s++;
                    case 5: *d++ = *s++;
                    case 4: *d++ = *s++;
                    case 3: *d++ = *s++;
                    case 2: *d++ = *s++;
                    case 1: *d = *s;
                    default: break;
                    }
                }
                Free(p);
                freeGuard = saved;
                return np;
            }
        }
    }

    uint32_t remaining = total - nb;
    if (remaining < 0x10) {
        c->size = (c->size & 0x80000007) | total;
        *(uint32_t*)((char*)c + total + 4) |= 1;
        return p;
    }
    c->size = (c->size & 0x80000007) | nb;
    Chunk* tail = (Chunk*)((char*)c + nb);
    tail->size = remaining | 1;
    *(uint32_t*)((char*)tail + remaining + 4) |= 1;
    *(uint32_t*)((char*)tail + remaining) = remaining;
    uint32_t saved = freeGuard;
    freeGuard = 0;
    Free((char*)tail + 8);
    freeGuard = saved;
    return p;
}