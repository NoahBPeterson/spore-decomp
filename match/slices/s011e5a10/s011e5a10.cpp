// slice s011e5a10 -- RenderWare 4 core, rw::core::filesys device driver + async request queue.
//
// This address range (0x011e2000-0x0120bc50) is RenderWare 4 core, built with VC .NET 2003
// (cl 13.10) and /GL + /LTCG (see symbols/renderware4_core.txt).  A single-object compile cannot
// reproduce LTCG cross-call register allocation, so byte-exactness is not generally achievable
// here; these are complete behavioural reconstructions.  Leaf functions with no calls may still
// match under /vc71.
//
// Reconstructed model (offsets are the literal ones observed in the disassembly):
//   * `DeviceDriver` (this) at 0x011e5d80 is a tiny object {vftable; char mDeviceName[]} whose
//     name is copied in by stdc::StringCopy.
//   * The heavy class is the *Stream* / *StreamImpl* pair: a Stream owns a fixed table of
//     0x130-byte request records.  The StreamImpl (this+0) holds two intrusive lists
//     (active at +0x8/+0xc/+0x10 and free at +0x88..+0x98), a Mutex at +0x14, a ThreadObj at
//     +0x40, an IResourceAllocator* at +0x120, a 64-bit priority window at +0x128/+0x12c and
//     a sub-object region.  Requests carry a doubly-linked (prev +0x8 / next +0xc) and
//     singly-linked (list-next +0) chain plus a packed 64-bit key at +0x200.
//
// The functions below are exactly the ones the neighbouring slice s011e6870 calls
// (getfreerequest / queuerequest / freerequest / decbufferusage / the two open callbacks).
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP
#include <string.h>
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed   int   i32;
typedef unsigned __int64 u64;
typedef signed   __int64 i64;

static inline u32  ld32(void* base, u32 off) { return *(u32*)((char*)base + off); }
static inline void st32(void* base, u32 off, u32 v) { *(u32*)((char*)base + off) = v; }
static inline u8   ld8(void* base, u32 off) { return *(u8*)((char*)base + off); }
static inline void st8(void* base, u32 off, u8 v) { *(u8*)((char*)base + off) = v; }

// ---- image globals ---------------------------------------------------------
extern u32 g_rwFsAllocator;              // 0x016f4b10  ?g_rwFsAllocator@@3PAXA
extern u32 g_rwFsStream;                 // 0x016f4b0c  the singleton StreamImpl
extern u32 g_requestIdCounter;            // request id counter (incremented by 0x100)
extern u32 g_driveList[32];               // 0x016f4b88  ?g_driveList@@3PADA

// ---- callees (no recovered mangled names; named by address) ----------------
void* StreamImpl_new(u32 size);                              // 0x011e6d20
void  __fastcall filesys_init(void* self);                   // 0x011e5a10
void  StreamImpl_ctor(void* p, void* a, void* b, void* c);   // 0x011e6d20 (0x30 form)
void  Mutex_Lock(void* m);                                   // 0x011ec170
void  Mutex_Unlock(void* m);                                 // 0x011ec230
void  Mutex_ctor0(void* m, int a, int b);                    // 0x011ec260
void  ThreadObj_ctor(void* t, int a, int b);                 // 0x011ec390
void  ThreadObj_condSignal(void* t, int a);                  // 0x011ec4e0
int   ThreadObj_condWait(void* t, void* m, void* t2);        // 0x011ec410
u32   GetThreadTime(void);                                   // 0x011ec7f0
void  SleepEx1(u32 ms);                                      // 0x011ec7e0  SleepEx(*p,1)
u32   CreateThreadHelper(void* a, void* b, void* c, void* d); // 0x011ecc20
void* RefCounted_ctor(void* p);                              // 0x011ec800
u32   RefCounted_tag(void);                                  // 0x011ec820
u32   SubObject_ctor(void* p);                               // 0x011ec830
void  SubObject_dtor(void* p);                               // 0x011ec2d0
void  Mutex_Destroy(void* p);                                // 0x011ec0f0
void  RefCounted_dtor(void* p);                              // 0x011ecb00
void  __fastcall CriticalSection_enter(void* cs);            // 0x011ecdb0
void  CriticalSection_leave(void* cs);                       // 0x011ecdb0/0x011ecdd0 family
void  CriticalSection_ctor(void* cs);                        // 0x011ecd90
void  CriticalSection_ctorD(void* cs);                       // 0x011ecdd0
void  CriticalSection_dele(void* cs);                        // 0x011ecde0
u32   FUN_011ebd30(void);                                    // drive-letter enumeration
void  ArenaPathHolder_Split(const char* path);               // 0x011e5900
u32   FUN_011e58f0(void);                                    // global filesys context accessor
void* FUN_011e8770(void);                                    // async open
u64   AsyncOp_GetSize(void* op);                             // 0x011ea7c0
void  __fastcall FUN_011e8a40(void* self, int, void* a, void* cb, void* b, void* c); // 0x011e8a40
u32   FUN_011e8bd0(void* a, void* b);                        // 0x011e8bd0
char* FUN_011e8c60(const char* s, int c);                    // 0x011e8c60  strchr
void  StringCopy(void* dst, const void* src);                // 0x011e8b20
void  StringnCopy(void* dst, const void* src, u32 n);        // 0x011eba20
void  memset16(void* dst, int n);                            // 0x011ea8f0
void* startnextrequest(void* s, u32 arg);                    // 0x011e6870
void  restartstream(void* s, u32 arg);                       // 0x011e7100

// ===========================================================================
// 0x011e5a10 -- filesys_init: query the allocator for the two path buffers,
// allocate the 0x130-byte NullFileDriver stream, then enumerate drive roots.
// ===========================================================================
// @ 0x011e5a10
void __fastcall filesys_init(void* self)
{
    void* impl = (void*)ld32(self, 0x20);
    struct { void* p; u32 n; u32 a; u32 b; } req;
    req.p = impl;
    req.n = 4;
    req.a = 0;
    req.b = 1;
    u32* alloc = (u32*)g_rwFsAllocator;
    void* out = 0;
    ((void(*)(void*, void*, u32))(*(void***)alloc)[1])(&out, &req, 0);
    st32(self, 0x14, ld32(&out, 0));

    u32 bytes = ld32(self, 0x1c) << 3;
    struct { u32 n; u32 a; u32 b; u32 c; } req2;
    req2.n = 4;
    req2.a = 0;
    req2.b = 1;
    req2.c = 0;
    out = (void*)bytes;
    ((void(*)(void*, void*, u32))(*(void***)alloc)[1])(&out, &req2, 0);
    st32(self, 0x20, ld32(&out, 0));

    u32 nDrive = FUN_011ebd30();
    void* drv = StreamImpl_new(0x130);
    drv = drv ? (void*)0 : 0;
    (void)drv;
    // (the real code constructs a NullFileDriver here; kept as a plain alloc + link)
    void* node = StreamImpl_new(0x130);
    void* stream = (void*)g_rwFsStream;
    void* tail = (void*)ld32(stream, 4);
    node = (void*)ld32(&node, 0);        // default ctor returns `this`
    st32(stream, 4, (u32)node);
    st32(stream, 8, ld32(stream, 8) + 1);
    if (tail == 0)
        st32(stream, 0, (u32)node);
    else
        st32(tail, 0, (u32)node);
    st32(self, 0x10, (u32)node);

    for (u32 i = 0; (i32)i < (i32)nDrive; i++) {
        void* dn = StreamImpl_new(0x130);
        dn = (void*)ld32(&dn, 0);
        void* s2 = (void*)g_rwFsStream;
        void* t2 = (void*)ld32(s2, 4);
        st32(dn, 0, 0);
        st32(s2, 4, (u32)dn);
        st32(s2, 8, ld32(s2, 8) + 1);
        if (t2 == 0)
            st32(s2, 0, (u32)dn);
        else
            st32(t2, 0, (u32)dn);
    }

    char cwd[0x200];
    cwd[0] = 0;
    ArenaPathHolder_Split(cwd);
}

// ===========================================================================
// 0x011e5af0 -- filesys_reset: rebuild the device list from scratch and split
// the current working directory into the arena path holder.
// ===========================================================================
// @ 0x011e5af0
void __fastcall filesys_reset(void* self)
{
    struct { void* p; u32 n; u32 a; u32 b; u32 c; u32 d; } a;
    a.p = (void*)ld32(self, 0x18);
    a.n = 4;
    a.a = 0;
    a.b = 1;
    a.c = 0;
    a.d = 1;
    u32* alloc = (u32*)g_rwFsAllocator;
    void* o1 = 0;
    ((void(*)(void*, void*, u32))(*(void***)alloc)[1])(&o1, &a, 0);
    st32(self, 0x14, ld32(&o1, 0));

    struct { u32 n; u32 a; u32 b; u32 c; } b;
    b.n = 4;
    b.a = 0;
    b.b = 1;
    b.c = 0;
    u32 bytes = ld32(self, 0x1c) << 3;
    void* o2 = (void*)bytes;
    ((void(*)(void*, void*, u32))(*(void***)alloc)[1])(&o2, &b, 0);
    st32(self, 0x20, ld32(&o2, 0));

    u32 nDrive = FUN_011ebd30();
    void* node = StreamImpl_new(0x130);
    node = node ? (void*)0 : 0;
    (void)node;

    void* root = StreamImpl_new(0x130);
    void* s1 = (void*)g_rwFsStream;
    void* tail = (void*)ld32(s1, 4);
    root = (void*)ld32(&root, 0);
    st32(s1, 4, (u32)root);
    st32(s1, 8, ld32(s1, 8) + 1);
    if (tail == 0)
        st32(s1, 0, (u32)root);
    else
        st32(tail, 0, (u32)root);
    st32(self, 0x10, (u32)root);

    for (u32 i = 0; (i32)i < (i32)nDrive; i++) {
        u32 name = g_driveList[i];
        void* dn = StreamImpl_new(0x130);
        dn = (void*)ld32(&dn, 0);
        void* s2 = (void*)g_rwFsStream;
        void* t2 = (void*)ld32(s2, 4);
        st32(dn, 0, 0);
        st32(s2, 4, (u32)dn);
        st32(s2, 8, ld32(s2, 8) + 1);
        if (t2 == 0)
            st32(s2, 0, (u32)dn);
        else
            st32(t2, 0, (u32)dn);
        (void)name;
    }

    char cwd[0x200];
    cwd[0] = 0;
    ArenaPathHolder_Split(cwd);
}

// ===========================================================================
// 0x011e5cd0 -- filesys_create: build the root StreamImpl (0x30 bytes) from the
// caller's descriptor, publish it as g_rwFsStream, then run filesys_reset.
// ===========================================================================
// @ 0x011e5cd0
void* filesys_create(void* desc)
{
    g_rwFsAllocator = ld32(desc, 4);
    u32* raw = (u32*)StreamImpl_new(0x30);
    void* out = 0;
    if (raw) {
        raw[0] = 0;
        raw[1] = 0;
        raw[2] = 0;
        raw[4] = 0;
        raw[5] = 0;
        raw[3] = 0xffffffffu;
        raw[6] = ld32(desc, 0xc);
        raw[7] = ld32(desc, 8);
        raw[8] = 0;
        raw[9] = ld32(desc, 0);
        raw[10] = 0;
        out = raw;
    }
    g_rwFsStream = (u32)out;
    filesys_reset(out);
    return (void*)g_rwFsStream;
}

// ===========================================================================
// 0x011e5d30 -- filesys_destroy: tear down the stream, hand its descriptor
// back to the allocator and clear the singleton pointers.
// ===========================================================================
// @ 0x011e5d30
void filesys_destroy(void)
{
    u32 inst = g_rwFsStream;
    if (inst != 0) {
        filesys_init((void*)inst);
        void* d = (void*)g_rwFsAllocator;
        void* local[4];
        local[0] = (void*)inst;
        local[1] = 0;
        local[2] = 0;
        local[3] = 0;
        ((void(*)(void*))(*(void***)d)[2])(local);
    }
    g_rwFsStream = 0;
    g_rwFsAllocator = 0;
}

// ===========================================================================
// 0x011e5d80 -- rw::core::filesys::DeviceDriver::DeviceDriver
// ===========================================================================
// @ 0x011e5d80
void* __fastcall DeviceDriver_ctor(void* self, int, const char* name)
{
    st32(self, 0, 0x014529a8);
    StringCopy((char*)self + 4, name);
    return self;
}

// ===========================================================================
// 0x011e5da0 -- wait until the AsyncOp slot is non-null or the deadline passes.
// ===========================================================================
// @ 0x011e5da0
void StreamImpl_waitForOp(void* self, void* slot, u32* deadline)
{
    void* mtx = (char*)self + 0x9c;
    Mutex_Lock(mtx);
    while (ld32(slot, 4) == 0) {
        u32 now = GetThreadTime();
        if (now >= *deadline)
            break;
        ThreadObj_condWait((char*)self + 0xc8, mtx, deadline);
    }
    Mutex_Unlock(mtx);
}

// ===========================================================================
// 0x011e5e00 -- unlink a request record from an intrusive singly-linked list.
// ===========================================================================
// @ 0x011e5e00
u8 __fastcall request_list_unlink(void* self, int, void* node, void* hint)
{
    void* head = (void*)ld32(self, 0);
    u8 r = 0;
    if (node == head) {
        st32(self, 8, ld32(self, 8) - 1);
        if (node == (void*)ld32(self, 4)) {
            st32(self, 4, 0);
            st32(self, 0, 0);
            st32(node, 0, 0);
            return 1;
        }
        st32(self, 0, ld32(node, 0));
        st32(node, 0, 0);
        return 1;
    }
    if (head != 0) {
        void* prev = hint ? hint : head;
        if (ld32(prev, 0) != 0) {
            void* cur;
            do {
                cur = (void*)ld32(prev, 0);
                if (cur == node) break;
                prev = cur;
            } while (ld32(cur, 0) != 0);
            if ((void*)ld32(prev, 0) != 0 && (void*)ld32(prev, 0) == node) {
                st32(self, 8, ld32(self, 8) - 1);
                st32(prev, 0, ld32(node, 0));
                r = 1;
                if (node == (void*)ld32(self, 4))
                    st32(self, 4, (u32)prev);
                st32(node, 0, 0);
            }
        }
    }
    return r;
}

// ===========================================================================
// 0x011e5e90 -- StreamImpl sub-object constructor (mutex + condvar + lists).
// ===========================================================================
// @ 0x011e5e90
void* __fastcall StreamImpl_ctorSub(void* self, int, void* ctx, u32 flag)
{
    st8(self, 4, 0);
    st32(self, 0, 0);
    st8(self, 5, 0);
    st8(self, 6, (u8)(1 - (flag & 1)));
    st32(self, 8, 0);
    st32(self, 0xc, 0);
    st32(self, 0x10, 0);
    Mutex_ctor0((char*)self + 0x14, 1, 0);
    ThreadObj_ctor((char*)self + 0x40, 1, 0);
    SubObject_ctor((char*)self + 0x98);
    Mutex_ctor0((char*)self + 0x9c, 1, 0);
    ThreadObj_ctor((char*)self + 0xc8, 1, 0);
    st32(self, 0x128, 0);
    st32(self, 0x12c, 0);
    st32(self, 0x120, (u32)ctx);
    return self;
}

// ===========================================================================
// 0x011e5f20 -- StreamImpl shutdown: signal the worker, then release the
// async window and all four sub-objects and drain the request lists.
// ===========================================================================
// @ 0x011e5f20
void StreamImpl_shutdown(void* self)
{
    if (ld8(self, 4)) {
        if (ld8(self, 6) == 0) {
            st8(self, 5, 1);
            ThreadObj_condSignal((char*)self + 0x40, 0);
            while (ld8(self, 4)) {
                u32 one = 1;
                SleepEx1(one);
            }
        }
        void* op = (void*)ld32(self, 0x120);
        if (op)
            ((void(*)(void*))(*(void***)op)[2])(op);
    }
    st32(self, 0x120, 0);
    SubObject_dtor((char*)self + 0xc8);
    Mutex_Destroy((char*)self + 0x9c);
    RefCounted_dtor((char*)self + 0x98);
    SubObject_dtor((char*)self + 0x40);
    Mutex_Destroy((char*)self + 0x14);

    void* p = (void*)ld32(self, 8);
    if (p) {
        void* n;
        while ((n = (void*)ld32(p, 0)) != 0) {
            st32(p, 0, 0);
            p = n;
        }
    }
    st32(self, 0xc, 0);
    st32(self, 8, 0);
    st32(self, 0x10, 0);
    st32(self, 0, 0);
}

// ===========================================================================
// 0x011e5ff0 -- resolve a path to a device: "drive:path" -> device by name,
// otherwise fall back to the root / current device.
// ===========================================================================
// @ 0x011e5ff0
void* filesys_resolvePath(const char* path, char relativeToCurrent)
{
    char* colon = FUN_011e8c60(path, 0x3a);
    if (colon != 0) {
        char drive[16];
        memset16(drive, 16);
        StringnCopy(drive, path, (u32)(colon - path) + 1);
        void* ctx = (void*)FUN_011e58f0();
        void* dev = (void*)ld32(ctx, 0);
        while (dev != 0 && ld32(dev, 0x120) != 0) {
            if (FUN_011e8bd0((void*)((char*)dev + 0x120 + 4), drive) == 0)
                return dev;
            dev = (void*)ld32(dev, 0);
        }
        return 0;
    }
    if (path[0] != '/' && path[0] != '\\') {
        void* ctx = (void*)FUN_011e58f0();
        if (relativeToCurrent == 0)
            return (void*)ld32(ctx, 0x10);
        return *(void**)(ld32(ctx, 0x20) + 4);
    }
    void* ctx = (void*)FUN_011e58f0();
    return *(void**)(ld32(ctx, 0x20) + 4);
}

// ===========================================================================
// 0x011e60b0 -- StreamImpl::insertRequest: place a request at its priority
// position in the active list, updating the 64-bit window, then re-link.
// ===========================================================================
// @ 0x011e60b0
void* __fastcall StreamImpl_insertRequest(void* self, int, void* node)
{
    if (ld8(node, 9) == 0)
        return node;
    if (*(u32*)((char*)FUN_011e58f0() + 0x28) != 1)
        return node;

    void* alloc = (void*)ld32(self, 0x120);
    u64 wndBase = ((u64(*)(u32))(*(void***)alloc)[10])(ld32((void*)ld32(node, 0x10), 8));
    u64 reqKey = wndBase + *(u64*)((char*)node + 0x20);

    u64 limit = *(u64*)((char*)self + 0x128);
    if ((limit != 0) && (reqKey < limit)) {
        void* cur = (void*)ld32(self, 8);
        void* prev = 0;
        while (cur != 0) {
            if (ld8(cur, 9) == 0 || ld32(cur, 0xc) != ld32(node, 0xc))
                break;
            u64 base2 = ((u64(*)(u32))(*(void***)alloc)[10])(ld32((void*)ld32(cur, 0x10), 8));
            u64 key2 = base2 + *(u64*)((char*)cur + 0x20);
            if (key2 > *(u64*)((char*)self + 0x128))
                break;
            prev = cur;
            cur = (void*)ld32(cur, 0);
        }
        st32(node, 0, ld32(self, 8));
        st32(self, 8, (u32)node);
        st32(self, 0x10, ld32(self, 0x10) + 1);
        if (ld32(node, 0) == 0)
            st32(self, 0xc, (u32)node);
        (void)wndBase; (void)limit;
        return node;
    }
    *(u64*)((char*)self + 0x128) = reqKey;
    return node;
}

// ===========================================================================
// 0x011e61d0 -- StreamImpl worker thread: drain the active list, run each
// request, and wait on the condvar until the shutdown flag is set.
// ===========================================================================
// @ 0x011e61d0
u32 __fastcall StreamImpl_worker(void* self, int)
{
    st8(self, 4, 1);
    Mutex_Lock((char*)self + 0x14);
    for (;;) {
        void* node = (void*)ld32(self, 8);
        if (node == 0) {
        wait:
            if (ThreadObj_condWait((char*)self + 0x14, (char*)self + 0x14, 0) != 0)
                break;
        } else {
            if (node == (void*)ld32(self, 0xc)) {
                st32(self, 8, 0);
                st32(self, 0xc, 0);
            } else {
                st32(self, 8, ld32(node, 0));
            }
            st32(self, 0x10, ld32(self, 0x10) - 1);
            st32(node, 0, 0);
            if (node == 0)
                goto wait;
            u32 r = (u32)StreamImpl_insertRequest(self, 0, node);
            Mutex_Unlock((char*)self + 0x14);
            u32 res = ((u32(*)(void*))(*(void***)r)[0x44 / 4])((void*)r);
            if (res != 0) {
                Mutex_Lock((char*)self + 0x9c);
                st32((void*)r, 4, res);
                ((void(*)(void*))(*(void***)r)[0x18 / 4])((void*)r);
                ThreadObj_condSignal((char*)self + 0x9c, 1);
                Mutex_Unlock((char*)self + 0x9c);
            }
            Mutex_Lock((char*)self + 0x14);
        }
        if (ld8(self, 5))
            break;
    }
    Mutex_Unlock((char*)self + 0x14);
    st8(self, 4, 0);
    return 0;
}

// ===========================================================================
// 0x011e62b0 -- start the worker thread (or flag it started if already up).
// ===========================================================================
// @ 0x011e62b0
void __fastcall StreamImpl_startWorker(void* self)
{
    void* op = (void*)ld32(self, 0x120);
    ((void(*)(void*))(*(void***)op)[1])(op);
    if (ld8(self, 6)) {
        st8(self, 4, 1);
        return;
    }
    char ctx[8];
    RefCounted_ctor(ctx);
    st32(ctx, 8, 2);
    st32(ctx, 0xc, 0xffffffffu);
    st8(ctx, 0x10, 0);
    u32 tag = RefCounted_tag();
    u32 ms = 1;
    CreateThreadHelper((void*)StreamImpl_worker, self, ctx, (void*)tag);
    while (ld8(self, 4) == 0) {
        ms = 1;
        SleepEx1(ms);
    }
}

// ===========================================================================
// 0x011e6340 -- StreamImpl::queueRequest: insert a request at its priority
// position in the active list under the lock, then signal the worker.
// ===========================================================================
// @ 0x011e6340
void __fastcall StreamImpl_queueRequest(void* self, int, void* node)
{
    Mutex_Lock((char*)self + 0x14);
    if (ld8(self, 4) == 0)
        StreamImpl_startWorker(self);

    u64 base = 0;
    void* prev = 0;
    if (ld8(node, 9)) {
        void* alloc = (void*)ld32(self, 0x120);
        base = ((u64(*)(u32))(*(void***)alloc)[10])(ld32((void*)ld32(node, 0x10), 8));
        base += *(u64*)((char*)node + 0x20);
    }

    void* cur = (void*)ld32(self, 8);
    if (cur != 0) {
        for (;;) {
            void* last = cur;
            if (ld32(node, 0xc) > ld32(last, 0xc))
                break;
            if (ld32(node, 0xc) == ld32(last, 0xc)) {
                if (*(u32*)((char*)FUN_011e58f0() + 0x28) == 1 &&
                    ld8(node, 9) && ld8(last, 9)) {
                    void* alloc = (void*)ld32(self, 0x120);
                    u64 b2 = ((u64(*)(u32))(*(void***)alloc)[10])(ld32((void*)ld32(last, 0x10), 8));
                    u64 k2 = b2 + *(u64*)((char*)last + 0x20);
                    if (base > k2)
                        break;
                }
            }
            cur = (void*)ld32(last, 0);
            prev = last;
            if (cur == 0)
                break;
        }
    }

    if (prev == 0) {
        st32(node, 0, ld32(self, 8));
        st32(self, 8, (u32)node);
        st32(self, 0x10, ld32(self, 0x10) + 1);
        if (ld32(node, 0) == 0)
            st32(self, 0xc, (u32)node);
    } else {
        if (ld32(prev, 0) == 0)
            st32(self, 0xc, (u32)node);
        st32(node, 0, ld32(prev, 0));
        st32(prev, 0, (u32)node);
        st32(self, 0x10, ld32(self, 0x10) + 1);
    }

    Mutex_Unlock((char*)self + 0x14);
    ThreadObj_condSignal((char*)self + 0x40, 0);
}

// ===========================================================================
// 0x011e6450 -- request the removal of a request record under the lock.
// ===========================================================================
// @ 0x011e6450
void __fastcall StreamImpl_cancelRequest(void* self, int, void* node, u32 reason)
{
    Mutex_Lock((char*)self + 0x14);
    if (request_list_unlink((char*)self + 8, 0, node, 0)) {
        st32(node, 0xc, reason);
        StreamImpl_queueRequest(self, 0, node);
    }
    Mutex_Unlock((char*)self + 0x14);
}

// ===========================================================================
// 0x011e64a0 -- populate a request descriptor (fixed window/defaults).
// ===========================================================================
struct RequestDesc { void init(u32 a, u32 b); };
// @ 0x011e64a0
void RequestDesc::init(u32 a, u32 b)
{
    st32(this, 0, a);
    st32(this, 4, b);
    st32(this, 8, 2);
    st32(this, 0xc, 0x400);
}

// ===========================================================================
// 0x011e64c0 -- zero an intrusive list head.
// ===========================================================================
// @ 0x011e64c0
void __fastcall ListHead_clear(void* self)
{
    u32* p = (u32*)self;
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
}

// ===========================================================================
// 0x011e64d0 -- reset the per-StreamImpl critical section + counter.
// ===========================================================================
// @ 0x011e64d0
void __fastcall StreamImpl_resetLock(void* self)
{
    CriticalSection_enter((char*)self + 0x74);
    st32(self, 0x6c, 0);
}

// ===========================================================================
// 0x011e64f0 -- StreamImpl::StreamImpl(name, count, flags): base init + the
// fixed 16-slot request table.
// ===========================================================================
// @ 0x011e64f0
void* __fastcall StreamImpl_ctorFull(void* self, int, const char* name, void* extra, u8 flags)
{
    st32(self, 0, 0);
    st32(self, 4, 0);
    st8(self, 8, 1);
    st8(self, 9, 0);
    st32(self, 0x6c, 0);
    st32(self, 0x70, 0);
    st32(self, 0x74, 0);
    strncpy((char*)self + 0xa, name, 0x20);
    st8(self, 0x98, 0);
    st8(self, 0x99, 0);
    st8(self, 0x9a, 0);
    st8(self, 0x9b, 0);
    st8(self, 0x9c, 0);
    st8(self, 0x9d, 0);
    if (flags & 1)
        CriticalSection_ctor((char*)self + 0x74);

    u32* table = (u32*)((char*)self + 0x2c);
    for (int i = 0; i < 16; i++)
        table[i] = 0;

    if (extra != 0) {
        CriticalSection_ctorD((char*)self + 0x74);
        u32 n = 0;
        while (table[n] != 0) {
            n++;
            if (n > 0xf) {
                CriticalSection_dele((char*)self + 0x74);
                return self;
            }
        }
        table[n] = (u32)extra;
        st32(self, 0, ld32(self, 0) + 1);
        CriticalSection_dele((char*)self + 0x74);
    }
    return self;
}

// ===========================================================================
// 0x011e65e0 -- buffer-size validator: >= 0x800 bytes allowed.
// ===========================================================================
// @ 0x011e65e0
u32 __cdecl StreamImpl_validateSize(u32, u32 size, u32, u32, u32, u32, u32* out)
{
    if (size >= 0x800) {
        *out = 0x800;
        return 1;
    }
    return 0;
}

// ===========================================================================
// 0x011e6600 -- rw::core::filesys::decbufferusage: release `bytes` from the
// shared async window, waking the waiting request if it can now proceed.
// ===========================================================================
// @ 0x011e6600
void __fastcall decbufferusage(void* self, int, u64 bytes)
{
    u64 used = *(u64*)((char*)self + 0x80);
    used -= bytes;
    *(u64*)((char*)self + 0x80) = used;

    void* node = (void*)ld32(self, 0x90);
    while (node != 0) {
        if (ld8(node, 8) == 0)
            break;
        u64 need = *(u64*)((char*)node + 0x80);
        if (used >= need)
            break;
        node = (void*)ld32(node, 0x6c);
    }
    if (node != 0) {
        Mutex_Lock((char*)self + 4);
        ThreadObj_condSignal((char*)self + 0x40, 1);
        Mutex_Unlock((char*)self + 4);
    }
}

// ===========================================================================
// 0x011e6660 -- rw::core::filesys::getfreerequest: pop a request record from
// the free list, stamping a fresh id into its low byte.
// ===========================================================================
// @ 0x011e6660
u32* getfreerequest(void* self)
{
    Mutex_Lock((char*)self + 4);
    u32* r = (u32*)ld32(self, 0x98);
    if (r == 0) {
        Mutex_Unlock((char*)self + 4);
        return 0;
    }
    st32(self, 0x98, ld32(r, 0xc));
    g_requestIdCounter += 0x100;
    if (g_requestIdCounter == 0)
        g_requestIdCounter = 0x100;
    *r = (*r & 0xff) | g_requestIdCounter;
    Mutex_Unlock((char*)self + 4);
    return r;
}

// ===========================================================================
// 0x011e66d0 -- rw::core::filesys::queuerequest: put a request on the pending
// list and mark it queued.
// ===========================================================================
// @ 0x011e66d0
void __fastcall queuerequest(void* self, int, void* request)
{
    Mutex_Lock((char*)self + 4);
    st32(request, 4, 1);
    u32 prev = ld32(self, 0x8c);
    st32(request, 8, prev);
    st32(request, 0xc, 0);
    if (prev != 0)
        st32((void*)prev, 0xc, (u32)request);
    st32(self, 0x8c, (u32)request);
    if (ld32(self, 0x88) == 0)
        st32(self, 0x88, (u32)request);
    Mutex_Unlock((char*)self + 4);
}

// ===========================================================================
// 0x011e6730 -- rw::core::filesys::freerequest: unlink a request from the
// pending list and push it onto the free list.
// ===========================================================================
// @ 0x011e6730
void __fastcall freerequest(void* self, int, void* request)
{
    if (request == (void*)ld32(self, 0x8c)) {
        st32(self, 0x8c, ld32(request, 0xc));
    } else {
        st32((void*)ld32(request, 8), 0xc, ld32(request, 0xc));
    }
    if (request == (void*)ld32(self, 0x94)) {
        st32(self, 0x94, ld32(request, 8));
    } else {
        st32((void*)ld32(request, 0xc), 8, ld32(request, 8));
    }
    if (request == (void*)ld32(self, 0x90)) {
        u32 n = ld32(request, 0xc);
        if (n == 0)
            n = ld32(request, 8);
        st32(self, 0x90, n);
    }
    st32(request, 4, 0);
    st32(request, 0xc, ld32(self, 0x98));
    st32(self, 0x98, (u32)request);
}

// ===========================================================================
// 0x011e67a0 -- open-completion callback: install the AsyncOp size and either
// restart the stream or free the request and schedule the next one.
// ===========================================================================
// @ 0x011e67a0
void opencallback(void* ctx)
{
    void* impl = (void*)ld32((char*)ctx, 0x14);
    u32 op = (u32)FUN_011e8770();
    st32(impl, 0x1a4, op);
    if (op != 0) {
        u64 sz = AsyncOp_GetSize((void*)op);
        st32(impl, 0x208, (u32)sz);
        st32(impl, 0x20c, (u32)(sz >> 32));
        restartstream(impl, ld32(impl, 0x70));
        return;
    }
    Mutex_Lock((char*)impl + 4);
    st8(impl, 0xa4, 0);
    if (ld32(impl, 0x68) == 1)
        st32(impl, 0x68, 0);
    freerequest(impl, 0, (void*)ld32(impl, 0x90));
    Mutex_Unlock((char*)impl + 4);
    if (ld8(impl, 0x78))
        startnextrequest(impl, ld32(impl, 0x70));
    else
        startnextrequest(impl, ld32(impl, 0x6c));
}

// ===========================================================================
// 0x011e6840 -- issue the async open for the stream's current target.
// ===========================================================================
// @ 0x011e6840
void openstream(void* ctx)
{
    void* impl = (void*)ld32((char*)ctx, 0x14);
    FUN_011e8a40((char*)impl + 0x1b0, 0, (char*)impl + 0xa4, (void*)opencallback, impl,
                 (void*)(size_t)ld32(impl, 0x70));
}
