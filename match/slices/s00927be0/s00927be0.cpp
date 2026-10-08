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
    uint8_t  pad46e[0x488 - 0x46e];
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
    __declspec(noinline) void* AllocAligned(void* p, int sz, int a3, int a4); // 0x009282e0
    __declspec(noinline) void* ReallocCore(void* p, int sz, int a3);    // 0x00928730

    __declspec(noinline) void* LockedAlloc(int a1, int a2, int a3, int a4, int a5, int a6);               // 0x009289f0
    __declspec(noinline) void* LockedAligned(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8); // 0x00928a30
    __declspec(noinline) void* LockedRealloc(int a1, int a2, int a3);                                     // 0x00928a80

    void  Shrink();                                    // 0x00927700 (consolidate fast chunks)
    void  PlaceInBin(Chunk* p, uint32_t sz, int z);    // 0x00926960
    void* BigAlloc(uint32_t size);                     // 0x00926f10
    Chunk* SysAlloc(uint32_t size);                    // 0x009272c0
};

uint32_t __cdecl RequestToSize(uint32_t req);          // 0x009267a0

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
    void* r = AllocAligned((void*)a1, a2, a3, a4);
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
void __cdecl Pool_AllocGlobal(unsigned size, unsigned* out)
{
    unsigned r = (unsigned)g_pool->LockedAlloc((int)size, 0, 0, 0, 0, 0);
    if (out != 0)
        *out = r ? size : 0;
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

// @ 0x009282e0  (pool aligned-alloc core - approximated)
void* cLocalLightInfo::AllocAligned(void* p, int sz, int a3, int a4)
{
    (void)p; (void)sz; (void)a3; (void)a4;
    return 0;
}

// @ 0x00928730  (pool realloc core - approximated)
void* cLocalLightInfo::ReallocCore(void* p, int sz, int a3)
{
    (void)p; (void)sz; (void)a3;
    return 0;
}