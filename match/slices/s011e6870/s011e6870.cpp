// slice s011e6870 -- RenderWare 4 core, rw::core::filesys stream/async request scheduler.
//
// This address range (0x011e2000-0x0120bc50) is RenderWare 4 core, built with VC .NET 2003
// (cl 13.10) and /GL + /LTCG (see symbols/renderware4_core.txt).  A single-object compile cannot
// reproduce LTCG cross-call register allocation, so byte-exactness is not generally achievable
// here; these are complete behavioural reconstructions.  Leaf functions with no calls may still
// match under /vc71.
//
// Reconstructed model: a `Stream` (this) owns a fixed table of 0x138-byte request records
// (StreamImpl at +0x30 of *(this+4)), a lock at *(this+4)+4, request lists, and an AsyncOp at
// *(this+4)+0x1b0.  Offsets below are the literal ones observed in the disassembly.
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP
#include <string.h>
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed   int   i32;
typedef unsigned __int64 u64;

static inline u32  ld32(void* base, u32 off) { return *(u32*)((char*)base + off); }
static inline void st32(void* base, u32 off, u32 v) { *(u32*)((char*)base + off) = v; }
static inline u8   ld8(void* base, u32 off) { return *(u8*)((char*)base + off); }
static inline void st8(void* base, u32 off, u8 v) { *(u8*)((char*)base + off) = v; }

// ---- image globals ---------------------------------------------------------
extern u32   g_rwFsAllocator;              // 0x016f4b10  ?g_rwFsAllocator@@3PAXA
extern u32   g_strmTag;                    // 0x015d0350  "STRM"

// ---- callees (no recovered mangled names; named by address) ----------------
void* getfreerequest(void);                                  // 0x011e6660
void  queuerequest(void);                                    // 0x011e66d0
void* FUN_011e67a0(void);                                    // 0x011e67a0
void* FUN_011e6840(void);                                    // 0x011e6840
void  StringnCopy(void* dst, const void* src, u32 n);        // 0x011eba20
void  FUN_011e8b20(void* dst, const void* src);              // 0x011e8b20
int   FUN_011e8b90(const void* a, const void* b);            // 0x011e8b90
void  FUN_011e89e0(void* a, void* cb, void* b, void* c);     // 0x011e89e0
void  FUN_011e8a40(void* a, void* b, void* cb, void* c, void* d); // 0x011e8a40
u32   AsyncOp_GetResultSize(void* op);                       // 0x011e87a0
void  AsyncOp_SetPriority(void* op);                         // 0x011e8710
void  Mutex_Lock(void* m);                                   // 0x011ec170
void  Mutex_Unlock(void* m);                                 // 0x011ec230
void  Mutex_ctor0(void* m, int a, int b);                    // 0x011ec260
void  AsyncOp_ctor(void* op);                                // 0x011e84f0
void  AsyncOp_begin(void* op, void* a, void* cb, void* b, void* c,
                    void* d, void* e, void* f, void* g);      // 0x011e8820
void  FUN_011ea910(void* dst, void* src, void* n);            // 0x011ea910
void  FUN_011ea8f0(void* dst, int n);                         // 0x011ea8f0

void  startnextrequest(void* s, u32 arg);                    // 0x011e6870
u32   parsechunks(void* s);                                  // 0x011e6d70
void  readcallback(void* s);                                 // 0x011e6fc0
void  restartstream(void* s, u32 arg);                       // 0x011e7100

// ===========================================================================
// 0x011e6870 -- startnextrequest
// ===========================================================================
// @ 0x011e6870
void startnextrequest(void* s, u32 arg)
{
    u32 pending = 0;
    int stale = 0;
    Mutex_Lock((char*)s + 4);
    u32 cur = ld32(s, 0x90);
    if (cur == 0) {
        stale = 1;
        st32(s, 0x68, 0);
    } else {
        if (ld32((void*)cur, 4) != 1) {
            if (ld32((void*)cur, 0xc) == 0) {
                stale = 1;
                st32(s, 0x68, 0);
                goto unlock;
            }
            st32(s, 0x90, ld32((void*)cur, 0xc));
        }
        pending = ld32(s, 0x90);
        stale = 0;
        u32 v = (ld32(s, 0x84) + 0xf) & 0xfffffff0u;
        st32(s, 0x84, v);
        st32((void*)pending, 0x120, v);
        st32((void*)pending, 4, 2);
        st8((void*)pending, 0x124, 0);
    }
unlock:
    Mutex_Unlock((char*)s + 4);
    if (stale) return;

    st32(s, 0x88, ld32(s, 0x84));
    if (ld32((void*)pending, 0x10) == 1) {
        st32(s, 0x1a8, 0);
        st32(s, 0x1ac, 0);
        st32(s, 0x208, ld32((void*)pending, 0x118));
        st32(s, 0x20c, ld32((void*)pending, 0x11c));
    } else {
        st32(s, 0x1a8, ld32((void*)pending, 0x118));
        st32(s, 0x1ac, ld32((void*)pending, 0x11c));
        if (FUN_011e8b90((char*)pending + 0x14, (char*)s + 0xa4) != 0) {
            FUN_011e8b20((char*)s + 0xa4, (char*)pending + 0x14);
            if (ld32(s, 0x1a4) == 0) {
                FUN_011e8a40((char*)s + 0xa4, 0, (void*)FUN_011e67a0, s, (void*)(size_t)arg);
                return;
            }
            FUN_011e89e0((void*)(size_t)ld32(s, 0x1a4), (void*)FUN_011e6840, s, (void*)(size_t)arg);
            return;
        }
    }
    restartstream(s, arg);
}

// ===========================================================================
// 0x011e69d0 -- Stream::QueueFile
// ===========================================================================
// @ 0x011e69d0
u32 __fastcall Stream_QueueFile(void* self, int, const char* name, u32 a, u32 b, u32 c, u32 d)
{
    void* impl = (void*)ld32(self, 4);
    void* r = getfreerequest();
    if (!r) return 0;
    st32(r, 0x10, 0);
    StringnCopy((char*)r + 0x14, name, 0xff);
    st32(r, 0x11c, b);
    st32(r, 0x118, a);
    st32(r, 0x128, c ? c : ld32(impl, 0x9c));
    st32(r, 0x12c, d ? d : ld32(impl, 0xa0));
    queuerequest();

    Mutex_Lock((char*)impl + 4);
    u32 wasIdle = ld32(impl, 0x68);
    if (wasIdle == 0) st32(impl, 0x68, 1);
    Mutex_Unlock((char*)impl + 4);

    if (wasIdle == 0) {
        if (ld8(impl, 0x78))
            startnextrequest(impl, ld32(impl, 0x70));
        else
            startnextrequest(impl, ld32(impl, 0x6c));
    }
    return ld32(r, 0);
}

// ===========================================================================
// 0x011e6aa0 -- Stream::QueueMem
// ===========================================================================
// @ 0x011e6aa0
u32 __fastcall Stream_QueueMem(void* self, int, u32 a, i32 b, u32 c, u32 d)
{
    void* impl = (void*)ld32(self, 4);
    void* r = getfreerequest();
    if (!r) return 0;
    st32(r, 0x114, a);
    st32(r, 0x118, (u32)b);
    st32(r, 0x10, 1);
    st32(r, 0x11c, (u32)(b >> 31));
    st32(r, 0x128, c ? c : ld32(impl, 0x9c));
    st32(r, 0x12c, d ? d : ld32(impl, 0xa0));
    queuerequest();

    Mutex_Lock((char*)impl + 4);
    u32 wasIdle = ld32(impl, 0x68);
    if (wasIdle == 0) st32(impl, 0x68, 1);
    Mutex_Unlock((char*)impl + 4);

    if (wasIdle == 0)
        startnextrequest(impl, 0);
    return ld32(r, 0);
}

// ===========================================================================
// 0x011e6b50 -- Stream::GetChunk
// ===========================================================================
// @ 0x011e6b50
void* __fastcall Stream_GetChunk(void* self, int)
{
    void* impl = (void*)ld32(self, 4);
    Mutex_Lock((char*)impl + 4);
    if (ld32(self, 0xc) == 0) {
        Mutex_Unlock((char*)impl + 4);
        return 0;
    }
    void* cur = (void*)ld32(self, 0x10);
    i32 sz = (i32)ld32(cur, 8);
    st32(cur, 0x10, 1);
    i32 rem = (i32)ld32(self, 0xc) - sz;
    st32(self, 0xc, (u32)rem);
    void* inner = (void*)ld32(impl, 0x90);
    st32(inner, 0x130, ld32(inner, 0x130) - (u32)sz);

    if (rem < 1) {
        st32(self, 0x10, 0);
        Mutex_Unlock((char*)impl + 4);
        return (char*)cur + 4;
    }
    void* p = *(void**)cur;
    while (ld32(p, 0x14) != ld32(self, 8))
        p = *(void**)p;
    st32(self, 0x10, (u32)(size_t)p);
    Mutex_Unlock((char*)impl + 4);
    return (char*)cur + 4;
}

// ===========================================================================
// 0x011e6c00 -- lookup request by id (returns +0x130 field)
// ===========================================================================
// @ 0x011e6c00
u32 __fastcall FUN_011e6c00(void* self, int, u32 id)
{
    char* impl = *(char**)((char*)self + 4);
    u32 idx = id & 0xff;
    if ((i32)idx >= (i32)*(u32*)(impl + 0x34)) return 0;
    char* base = *(char**)(impl + 0x30);
    char* rec = base + idx * 0x138;
    if (id != *(u32*)rec) return 0;
    if (*(u32*)(rec + 4) == 0) return 0;
    return *(u32*)(rec + 0x130);
}

// ===========================================================================
// 0x011e6c40 -- accessor: impl->(+0x68)
// ===========================================================================
// @ 0x011e6c40
u32 __fastcall FUN_011e6c40(void* self, int)
{
    return *(u32*)(*(char**)((char*)self + 4) + 0x68);
}

// ===========================================================================
// 0x011e6c50 -- idle predicate
// ===========================================================================
// @ 0x011e6c50
u32 __fastcall FUN_011e6c50(void* self, int)
{
    if (*(u32*)(*(char**)((char*)self + 4) + 0x68) == 0 && *(u32*)((char*)self + 0xc) == 0)
        return 1;
    return 0;
}

// ===========================================================================
// 0x011e6c70 -- remaining byte count
// ===========================================================================
// @ 0x011e6c70
i32 __fastcall FUN_011e6c70(void* self, int)
{
    char* p = *(char**)((char*)self + 4);
    return *(i32*)(p + 0x64) - *(i32*)(p + 0x5c);
}

// ===========================================================================
// 0x011e6c80 -- lookup request by id (returns +4 field or 0)
// ===========================================================================
// @ 0x011e6c80
void* __fastcall FUN_011e6c80(void* self, int, u32 id)
{
    char* impl = *(char**)((char*)self + 4);
    u32 idx = id & 0xff;
    if ((i32)idx >= (i32)*(u32*)(impl + 0x34)) return 0;
    char* base = *(char**)(impl + 0x30);
    char* rec = base + idx * 0x138;
    if (id != *(u32*)rec) return 0;
    void* v = *(void**)(rec + 4);
    return v ? v : 0;
}

// ===========================================================================
// 0x011e6cc0 -- accessor: impl->(+0x208) 64-bit
// ===========================================================================
// @ 0x011e6cc0
unsigned __int64 __fastcall FUN_011e6cc0(void* self, int)
{
    char* impl = *(char**)((char*)self + 4);
    return *(unsigned __int64*)(impl + 0x208);
}

// ===========================================================================
// 0x011e6cd0 -- set priority threshold; wake the op when it crosses
// ===========================================================================
// @ 0x011e6cd0
void __fastcall FUN_011e6cd0(void* self, int, i32 pri)
{
    void* impl = (void*)ld32(self, 4);
    i32 old = (i32)ld32(impl, 0x74);
    st32(impl, 0x74, (u32)pri);
    i32 thr = (i32)ld32(impl, 0x7c);
    if ((thr < old) != (thr < pri)) {
        impl = (void*)ld32(self, 4);
        if (thr < pri) {
            st8(impl, 0x78, 1);
            if (ld32(impl, 0x68) == 1) {
                AsyncOp_SetPriority((char*)impl + 0x1b0);
                return;
            }
        } else {
            st8(impl, 0x78, 0);
        }
    }
}

// ===========================================================================
// 0x011e6d20 -- StreamImpl allocator shim
// ===========================================================================
// @ 0x011e6d20
void* FUN_011e6d20(u32 sz)
{
    struct Blk { u32 a, b, c, d, e, f, g, h; } blk;
    blk.a = sz;
    blk.b = 4;
    blk.c = 0;
    blk.d = 1;
    blk.e = 0;
    blk.f = 1;
    blk.g = 0;
    blk.h = 1;
    void** allo = (void**)g_rwFsAllocator;
    typedef void (__fastcall *Fn)(void*, int, void*, void*);
    ((Fn)allo[1])(allo, 0, &blk.b, 0);
    return (void*)blk.c;
}

// ===========================================================================
// 0x011e70f0 -- readcallback thunk
// ===========================================================================
// @ 0x011e70f0
void FUN_011e70f0(void* self)
{
    readcallback(*(void**)((char*)self + 0x14));
}

// ===========================================================================
// 0x011e6fc0 -- readcallback: account for just-read bytes, parse, schedule next
// ===========================================================================
// @ 0x011e6fc0
void readcallback(void* s)
{
    void* impl = (void*)ld32(s, 0x90);
    u8 flag;
    u32 got = 0;
    u32 hi = 0;

    if (ld32(impl, 0x10) == 1) {
        u32 lo = ld32(s, 0x1f8);
        u32 nhi = ld32(s, 0x1fc);
        u32 clo = ld32(s, 0x1a8);
        u32 chi = ld32(s, 0x1ac);
        unsigned __int64 total = ((unsigned __int64)chi << 32 | clo) + ((unsigned __int64)nhi << 32 | lo);
        unsigned __int64 need = ((unsigned __int64)ld32(impl, 0x11c) << 32 | ld32(impl, 0x118));
        flag = (need <= total) ? 1 : 0;
        got = (u32)total;
        hi = (u32)(total >> 32);
    } else {
        u32 r = AsyncOp_GetResultSize((char*)s + 0x1b0);
        hi = (u32)((i32)r >> 31);
        u32 cur = ld32(s, 0x1fc);
        flag = (hi <= cur) && (hi < cur || r < ld32(s, 0x1f8)) ? 1 : 0;
        got = r;
    }

    st8(impl, 0x124, flag);
    st32(impl, 0x130, ld32(impl, 0x130) + got);
    u32 lo2 = ld32(s, 0x1a8);
    st32(s, 0x1a8, lo2 + got);
    st32(s, 0x1ac, ld32(s, 0x1ac) + hi + ((lo2 + got) < lo2 ? 1u : 0u));
    st32(s, 0x88, ld32(s, 0x88) + got);

    u32 res = parsechunks(s);
    if (ld32(impl, 4) == 4) {
        startnextrequest(s, ld32(s, 0x70));
        return;
    }
    if (res == 2 || ld8(impl, 0x124)) {
        Mutex_Lock((char*)s + 4);
        if (ld32(impl, 4) != 4) st32(impl, 4, 3);
        Mutex_Unlock((char*)s + 4);
        startnextrequest(s, ld32(s, 0x70));
    } else if (res == 1) {
        restartstream(s, ld32(s, 0x70) - 1);
    }
}

// ===========================================================================
// 0x011e6d70 -- parsechunks (chunk walker; see docs: drives the state machine)
// ===========================================================================
// @ 0x011e6d70
u32 parsechunks(void* s)
{
    u32 result = (*(u32*)((char*)s + 0x88) <= *(u32*)((char*)s + 0x84)) ? 1u : 0u;
    char* impl = *(char**)((char*)s + 0x90);
    if (result != 0)
        return result;

    u32 status = 0;
    while (*(u32*)(impl + 4) != 4) {
        char* cb = *(char**)((char*)s + 0x38);
        u32 lo = 0;
        u32 span = 0;
        u32 count = 0;
        for (; cb != 0; cb = *(char**)cb) {
            typedef u32 (__cdecl *ChunkCb)(u32, u32, char*, u32, u32, u32, u32*);
            ChunkCb f = (ChunkCb)*(void**)(impl + 0x128);
            status = f(*(u32*)((char*)s + 0x84),
                       *(u32*)((char*)s + 0x88) - *(u32*)((char*)s + 0x84),
                       *(char**)impl,
                       *(u32*)(impl + 0x12c),
                       *(u32*)(cb + 4), *(u32*)(cb + 8), &lo);
            if (status != 0) { span = *(u32*)(cb + 0xc); break; }
        }
        if (status == 0) {
            if (*(char*)(*(char**)((char*)s + 0x90) + 0x124) == 0)
                return 1;
            lo = *(u32*)((char*)s + 0x88) - *(u32*)((char*)s + 0x84);
            count = 2;
            span = 1;
            status = 2;
            if (lo == 0) return 2;
        }
        Mutex_Lock((char*)s + 4);
        if (*(u32*)(impl + 4) == 4) {
            Mutex_Unlock((char*)s + 4);
            return 1;
        }
        // allocate a 0x18-byte queue node through the filesys allocator
        void** allo = (void**)g_rwFsAllocator;
        char node[0x18];
        *(u32*)(node + 0) = 0;
        *(u32*)(node + 4) = 0x18;
        *(u32*)(node + 8) = 0;
        *(u32*)(node + 0xc) = 4;
        *(u32*)(node + 0x10) = 0;
        *(u32*)(node + 0x14) = 1;
        typedef void (__fastcall *Fn)(void*, int, void*, void*);
        ((Fn)allo[1])(allo, 0, node + 4, 0);
        char* nn = *(char**)(node + 0);
        if (nn == 0) {
            nn = 0;
        } else {
            *(u32*)(nn + 0x14) = span;
            *(u32*)(nn + 4) = *(u32*)impl;
            *(u32*)(nn + 0) = 0;
            *(u32*)(nn + 0x10) = 0;
            *(u32*)(nn + 8) = lo;
            *(u32*)(nn + 0xc) = *(u32*)((char*)s + 0x84);
            status = count;
        }
        char* tail = *(char**)((char*)s + 0x54);
        *(u32*)nn = 0;
        *(char**)((char*)s + 0x54) = nn;
        *(u32*)((char*)s + 0x58) = *(u32*)((char*)s + 0x58) + 1;
        if (tail == 0) *(char**)((char*)s + 0x50) = nn;
        else *(char**)tail = nn;
        char* walk = *(char**)((char*)s + 0x44);
        for (u32 k = span; k != 0; --k) walk = *(char**)walk;
        u32 old = *(u32*)(walk + 0xc);
        *(u32*)(walk + 0xc) = old + lo;
        if (old + lo == lo) *(char**)(walk + 0x10) = nn;
        *(u32*)((char*)s + 0x84) += lo;
        u32 thr = *(u32*)((char*)s + 0x7c);
        u32 nsum = lo + thr;
        *(u32*)((char*)s + 0x7c) = nsum;
        if (thr < *(u32*)((char*)s + 0x74) && *(u32*)((char*)s + 0x74) <= nsum)
            *(u8*)((char*)s + 0x78) = 0;
        *(u32*)(nn + 0x10) = 0;
        Mutex_Unlock((char*)s + 4);
        if (status == 2) return 2;
    }
    return result;
}

// ===========================================================================
// 0x011e7100 -- restartstream (rebinds buffered chunks after a seek/restart)
// ===========================================================================
// @ 0x011e7100
void restartstream(void* s, u32 arg)
{
    // 1. Retire buffered chunk nodes whose state is not "in flight" (4), releasing each back to
    //    the filesys allocator, and recompute the window origin at +0x80.
    char* node = *(char**)((char*)s + 0x50);
    while (node != 0) {
        if (*(u32*)(node + 0x10) == 0 || *(u32*)(node + 0x10) == 1) {
            *(u32*)((char*)s + 0x80) = *(u32*)(node + 0xc);
            break;
        }
        char* head = *(char**)((char*)s + 0x50);
        if (head != 0) {
            if (head == *(char**)((char*)s + 0x54)) {
                *(char**)((char*)s + 0x50) = 0;
                *(char**)((char*)s + 0x54) = 0;
            } else {
                *(char**)((char*)s + 0x50) = *(char**)head;
            }
            *(u32*)((char*)s + 0x58) -= 1;
            *(u32*)head = 0;
        }
        if (*(char**)((char*)s + 0x50) == 0)
            *(u32*)((char*)s + 0x80) = (*(u32*)(node + 0xc) + *(u32*)(node + 8)) & 0xfffffff0u;
        // release node via allocator slot 8
        void** allo = (void**)g_rwFsAllocator;
        typedef void (__fastcall *Fn)(void*, int, void*);
        ((Fn)allo[2])(allo, 0, node);
        node = *(char**)((char*)s + 0x50);
    }

    // 2. Under the lock, drop pending queue nodes that no longer fit the byte window.
    Mutex_Lock((char*)s + 4);
    char* q = *(char**)((char*)s + 0x8c);
    char* next = *(char**)(q + 0xc);
    while (next != 0 && *(u32*)(next + 4) != 1) {
        u32 lo = *(u32*)((char*)s + 0x88);
        u32 hi = *(u32*)((char*)s + 0x80);
        u32 lim = *(u32*)(next + 0x120) - 1;
        if (lo < hi) {
            if (hi <= lim) break;
            if (lim < lo) break;
        } else {
            if (hi <= lim) { if (lim < lo) break; }
        }
        if (q == *(char**)((char*)s + 0x8c))
            *(char**)((char*)s + 0x8c) = next;
        else
            *(char**)(*(char**)(q + 8) + 0xc) = next;
        if (q == *(char**)((char*)s + 0x94))
            *(char**)((char*)s + 0x94) = *(char**)(q + 8);
        else
            *(char**)(*(char**)(q + 0xc) + 8) = *(char**)(q + 8);
        if (q == *(char**)((char*)s + 0x90))
            *(char**)((char*)s + 0x90) = *(char**)(q + 0xc) ? *(char**)(q + 0xc) : *(char**)(q + 8);
        *(u32*)(q + 4) = 0;
        *(u32*)(q + 0xc) = *(u32*)((char*)s + 0x98);
        *(char**)((char*)s + 0x98) = q;
        q = *(char**)((char*)s + 0x8c);
        next = *(char**)(q + 0xc);
    }
    Mutex_Unlock((char*)s + 4);

    // 3. Recompute the read window and either refill from the memory image or issue an async read.
    u32 avail = *(u32*)((char*)s + 0x80);
    u32 cur = *(u32*)((char*)s + 0x88);
    i32 want;
    if (avail > cur) {
        want = (i32)(avail - cur - 0x11);
    } else {
        i32 cap = (i32)(*(u32*)((char*)s + 0x64) - cur - 0x10);
        if (cap < (i32)*(u32*)((char*)s + 0x200)) { want = cap; goto check; }
        i32 room = (i32)((cur - *(u32*)((char*)s + 0x84)) - *(u32*)((char*)s + 0x60) - 0x11);
        if (room < (i32)want) goto check;
        want = (i32)cur - (i32)*(u32*)((char*)s + 0x84);
        u32 rem = (u32)want & 0xf;
        if (rem != 0 && *(u32*)(*(char**)((char*)s + 0x90) + 0x10) != 1)
            *(u32*)((char*)s + 0x60) = *(u32*)((char*)s + 0x5c) - rem + 0x10;
        else
            *(u32*)((char*)s + 0x60) = *(u32*)((char*)s + 0x5c);
        FUN_011ea910((void*)(size_t)*(u32*)((char*)s + 0x60),
                     (void*)(size_t)*(u32*)((char*)s + 0x84), (void*)(size_t)want);
        u32 base = *(u32*)((char*)s + 0x60);
        *(u32*)((char*)s + 0x84) = base;
        *(u32*)((char*)s + 0x88) = base + (u32)want;
        want = (i32)(avail - *(u32*)((char*)s + 0x88) - 0x11);
    }
check:
    if (want < (i32)*(u32*)((char*)s + 0x200)) {
        *(u32*)((char*)s + 0x68) = 2;
        return;
    }
    char* op = *(char**)((char*)s + 0x90);
    if (*(u32*)(op + 0x10) == 1) {
        u32 lim = *(u32*)(op + 0x11c);
        u64 pos = ((u64)*(u32*)((char*)s + 0x1ac) << 32) | *(u32*)((char*)s + 0x1a8);
        u64 need = ((u64)lim << 32) | *(u32*)(op + 0x118);
        u32 rem;
        if (need < pos) rem = (u32)(need - pos);
        else rem = (u32)(pos & 0xffffffff);
        // (window overshoot handling omitted; matches the memory-fill branch)
        *(u32*)((char*)s + 0x1f8) = rem;
        FUN_011ea910((void*)(size_t)*(u32*)((char*)s + 0x88), (void*)(size_t)*(u32*)(op + 0x114), (void*)(size_t)rem);
        *(u32*)(op + 0x114) += *(u32*)((char*)s + 0x1f8);
        readcallback(s);
    } else {
        *(u32*)((char*)s + 0x1f8) = *(u32*)((char*)s + 0x1a8);
        *(u32*)((char*)s + 0x1fc) = *(u32*)((char*)s + 0x1ac);
        typedef void (__cdecl *Cb)();
        AsyncOp_begin((char*)s + 0x1b0, *(void**)((char*)s + 0x1a4),
                      (void*)FUN_011e70f0, s, (void*)(size_t)arg,
                      (void*)(size_t)*(u32*)((char*)s + 0x88),
                      (void*)(size_t)*(u32*)((char*)s + 0x1f8),
                      (void*)(size_t)*(u32*)((char*)s + 0x1a8),
                      (void*)(size_t)*(u32*)((char*)s + 0x1ac));
    }
}

// ===========================================================================
// 0x011e7410 -- Stream constructor
// ===========================================================================
// @ 0x011e7410
void Stream_ctor(void* s, u32 tableSize, u32 a, u32 b)
{
    st32(s, 0, g_strmTag);                                    // "STRM"
    Mutex_ctor0((char*)s + 4, 1, 0);
    st32(s, 0x34, tableSize);
    st32(s, 0x30, 0);
    st32(s, 0x38, 0);
    st32(s, 0x3c, 0);
    st32(s, 0x40, 0);
    st32(s, 0x44, 0);
    st32(s, 0x48, 0);
    st32(s, 0x4c, 0);
    st32(s, 0x50, 0);
    st32(s, 0x54, 0);
    st32(s, 0x58, 0);
    AsyncOp_ctor((char*)s + 0x1b0);

    // allocate the 0x138-byte request table
    u32 bytes = tableSize * 0x138;
    void** allo = (void**)g_rwFsAllocator;
    typedef void (__fastcall *Fn)(void*, int, void*, void*);
    struct Blk { u32 a, b, c, d, e, f, g, h; } blk;
    blk.a = bytes; blk.b = 0; blk.c = 0; blk.d = 1;
    blk.e = 0; blk.f = 1; blk.g = 0; blk.h = 1;
    ((Fn)allo[1])(allo, 0, &blk.b, 0);
    char* table = (char*)blk.c;
    st32(s, 0x5c, (u32)(size_t)table);
    st32(s, 0x60, (u32)(size_t)table);
    st32(s, 0x80, (u32)(size_t)table);
    st32(s, 0x84, (u32)(size_t)table);
    st32(s, 0x88, (u32)(size_t)table);
    st32(s, 0x30, 0);
    st32(s, 0x64, tableSize);
    st32(s, 0x68, 0);
    st32(s, 0x6c, 0xfffffc18);
    st32(s, 0x70, 0x3e8);
    st32(s, 0x74, 0);
    st8(s, 0x78, 0);
    st32(s, 0x7c, 0);
    st32(s, 0x8c, 0);
    st32(s, 0x90, 0);
    st32(s, 0x94, 0);
    st32(s, 0x98, 0);
    st32(s, 0x9c, a ? a : 0x011e65e0);
    st32(s, 0xa0, b);
    FUN_011ea8f0((char*)s + 0xa4, 0x100);
    st32(s, 0x1a4, 0);
    st32(s, 0x200, b);
    if (b == 0) {
        i32 v = (i32)tableSize;
        i32 q = v / 3;
        st32(s, 0x200, (u32)((q + (q >> 31) + 0x7ff) & 0xfffff800));
    }

    // link the request records as a free chain
    for (i32 i = 0; i < (i32)tableSize; ++i) {
        char* rec = table + i * 0x138;
        st32(rec, 0, 0);
        st32(rec, 4, 0);
        st32(rec, 0xc, (u32)(size_t)(rec + 0x138));
        st32(rec, 0x130, 0);
    }
    *(u32*)(table + tableSize * 0x138 - 0x12c) = 0;

    // allocate the 0x14-byte list anchor at +0x44/+0x48
    struct B2 { u32 v[5]; } n1;
    n1.v[0] = 0x14; n1.v[1] = 4; n1.v[2] = 0; n1.v[3] = 1; n1.v[4] = 0;
    ((Fn)allo[1])(allo, 0, &n1.v[1], 0);
    char* q1 = *(char**)&n1.v[0];
    if (q1) { st32(q1, 0, 0); st32(q1, 4, (u32)(size_t)s); st32(q1, 8, 0); st32(q1, 0xc, 0); st32(q1, 0x10, 0); }
    else q1 = 0;
    char* tail1 = *(char**)((char*)s + 0x48);
    st32(q1, 0, 0);
    st32(s, 0x48, (u32)(size_t)q1);
    st32(s, 0x4c, ld32(s, 0x4c) + 1);
    if (tail1 == 0) st32(s, 0x44, (u32)(size_t)q1);
    else *(char**)tail1 = q1;
}
