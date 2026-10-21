// Slice s006ad5c0: resource manager / LRU cache module.
// Most functions are /O2 with no frame pointer; a few are /Od with old-style EH.
// Callees outside the slice are declared as members of stub classes so that the
// compiler emits a __thiscall `mov ecx, ...; call` (addresses are masked relocs).
#include "../../include/types.h"
#include <intrin.h>

#ifndef LOCK
#define LOCK()
#define UNLOCK()
#endif


template <class T> static inline T _clamp_dec(T& x) { x = x - 1; return x; }

// ---------------------------------------------------------------------------
// globals (undefined externs -> DIR32 relocations, masked by the verifier)
// ---------------------------------------------------------------------------
extern void* g_pRegistry;   // 0x1603118
extern char  g_caches[];    // 0x16032a8, array of cLRUCache, stride 0x150
extern char  g_cachesEnd[]; // 0x1604118

// ---------------------------------------------------------------------------
// stub classes
// ---------------------------------------------------------------------------
struct LRUEntry { void* obj; int refs; };
struct cLRUCache {
    char pad[4];
    LRUEntry* beg;      // +4
    LRUEntry* end;      // +8
    char pad2[0x120 - 0xc];
    char lock;          // +0x120
    void Clear();          // FUN_006ad350
    void Reset();          // FUN_006ad270
    void Do(unsigned);     // FUN_006ada20
    void Destroy(void** base, unsigned count);  // 006ad910
};

// Build a virtual call through vtable slot `idx` (byte offset idx*4).
template <class T> static inline T* VT(void* p) { return (T*)*(void***)p; }

#define VFN(off) (*(void***)p)[(off) / 4]

// ---------------------------------------------------------------------------
// 006ad7c0  void SP::FlushCache(int)
// ---------------------------------------------------------------------------
namespace SP {
void FlushCache(int x);
}

void SP::FlushCache(int x)
{
    if (x == 0 || x == 1) {
        void* p = g_pRegistry;
        ((void(__thiscall*)(void*, int))VFN(0x28))(p, 0);
    } else if ((unsigned)(x - 3) <= 0xa) {
        ((cLRUCache*)(g_caches + (x - 3) * 0x150))->Clear();
    }
}

// ---------------------------------------------------------------------------
// 006ad800  void FUN_006ad800(int n)
// ---------------------------------------------------------------------------
// @ 0x006ad800
void FUN_006ad800(int n)
{
    int c = n;
    if (c > 0) {
        do {
            void* p = g_pRegistry;
            ((void(__thiscall*)(void*, int))VFN(0x28))(p, 0);
            cLRUCache* q = (cLRUCache*)g_caches;
            do {
                q->Clear();
                q = (cLRUCache*)((char*)q + 0x150);
            } while ((int)q < (int)g_cachesEnd);
        } while (--c);
    }
}

// ---------------------------------------------------------------------------
// 006ad850  void FUN_006ad850(void* p)
// ---------------------------------------------------------------------------
void FUN_006ad850(void* p)
{
    ((void(__thiscall*)(void*, int, void*, int))VFN(0x64))(p, 0, g_pRegistry, 0);
    g_pRegistry = 0;
    cLRUCache* q = (cLRUCache*)g_caches;
    do {
        q->Reset();
        q = (cLRUCache*)((char*)q + 0x150);
    } while ((int)q < (int)g_cachesEnd);
}

// ---------------------------------------------------------------------------
// 006adc60  void FUN_006adc60(int x, int a)
// ---------------------------------------------------------------------------
void FUN_006adc60(int x, int a)
{
    if ((unsigned)(x - 3) <= 0xa)
        ((cLRUCache*)(g_caches + (x - 3) * 0x150))->Do(a);
}

// ---------------------------------------------------------------------------
// 006ae020  void FUN_006ae020(void** p)
// ---------------------------------------------------------------------------
void __fastcall FUN_006ae020(void** p)
{
    void* q = *p;
    ((void(__thiscall*)(void*))(*(void***)q)[9])(q);
}

// ---------------------------------------------------------------------------
// 006ae060  void* SP::cAsyncResourceRequest::AsInterface(int iid)
// ---------------------------------------------------------------------------
namespace SP {
class cAsyncResourceRequest { public:
    void* AsInterface(int iid);
};
}

void* SP::cAsyncResourceRequest::AsInterface(int iid)
{
    if (iid == 0x3a11b3f || iid == 0xae9cb0fa || iid == 0xee3f516e ||
        iid == 0x3a212ac)
        return this;
    return 0;
}

// ---------------------------------------------------------------------------
// 006ae110  void FUN_006ae110(void** p)
// ---------------------------------------------------------------------------
struct Job {
    void f();   // 0x690120
};

void __fastcall FUN_006ae110(void** p)
{
    Job* q = (Job*)*p;
    if (q)
        q->f();
}

// ---------------------------------------------------------------------------
// 006ae280  bool FUN_006ae280(int self)
// ---------------------------------------------------------------------------
struct JobManager {
    int ContinueJob();   // 0x68f970
};

// @ 0x006ae280
bool __fastcall FUN_006ae280(int self)
{
    JobManager* j = *(JobManager**)(self + 0xc);
    if (j) {
        unsigned r = (unsigned)j->ContinueJob();
        return r - 7 <= 1;
    }
    return true;
}

// ---------------------------------------------------------------------------
// shared externs for the /O2 helpers below
// ---------------------------------------------------------------------------
extern "C" void ea_dealloc(void*);          // 0x00f47380
extern void FUN_00690c90();                 // (stub; real decl below)
extern char g_callbackMap[];                // 0x152f79c  hash_map<unsigned, vector>
extern void FUN_006ae090(void*);            // 0x006ae090 callback thunk
struct Releasable { virtual void s0(); virtual void Release(); };

// ---------------------------------------------------------------------------
// 006ad910  void cLRUCache::Destroy(void** base, unsigned count)
// ---------------------------------------------------------------------------
void cLRUCache::Destroy(void** base, unsigned count)
{
    for (unsigned i = 0; i < count; ++i) {
        char* n = (char*)base[i];
        while (n) {
            char* cur = n;
            n = *(char**)(n + 0x3c);
            void* p = *(void**)(cur + 4);
            if (p && p != *(void**)(cur + 0x14))
                ea_dealloc(p);
            ea_dealloc(cur);
        }
        base[i] = 0;
    }
}

// ---------------------------------------------------------------------------
// 006adfe0  void SP::AddRegistrationCallback(unsigned key, void* cb)
// ---------------------------------------------------------------------------
namespace SP {
struct RCVector { void* x0; void** fill; void** cap; };
struct CallbackMap { RCVector* operator[](const unsigned* key); };
struct RCVectorOps { void Grow(void** p, void** v); };
void AddRegistrationCallback(unsigned key, void* cb);
}

void SP::AddRegistrationCallback(unsigned key, void* cb)
{
    RCVector* v = ((CallbackMap*)g_callbackMap)->operator[](&key);
    void** p = v->fill;
    if (p < v->cap) {
        v->fill = p + 1;
        if (p)
            *p = cb;
    } else {
        ((RCVectorOps*)v)->Grow(p, &cb);
    }
}

// ---------------------------------------------------------------------------
// 006ae0d0  unsigned char FUN_006ae0d0(void** self)
// ---------------------------------------------------------------------------
unsigned char __fastcall FUN_006ae0d0(void** self)
{
    unsigned char r =
        ((unsigned char(__thiscall*)(void*))(*(void***)self[2])[8])(self[2]);
    ((void(__thiscall*)(void*))(*(void***)self)[1])(self);
    return r;
}

// ---------------------------------------------------------------------------
// 006ae0f0  unsigned char FUN_006ae0f0(void** self)
// ---------------------------------------------------------------------------
unsigned char __fastcall FUN_006ae0f0(void** self)
{
    unsigned char r =
        ((unsigned char(__thiscall*)(void*))(*(void***)self[2])[9])(self[2]);
    ((void(__thiscall*)(void*))(*(void***)self)[2])(self);
    return r;
}

// ---------------------------------------------------------------------------
// 006ae2f0  bool FUN_006ae2f0(char* p1, void* p2)
// ---------------------------------------------------------------------------
// @ 0x006ae2f0
bool FUN_006ae2f0(char* p1, void* p2)
{
    void (*oldFn)(void*);
    void* oldObj;
    if (p2) {
        (*(void(__thiscall**)(void*))(*(void***)p2))(p2);
        oldFn = *(void(**)(void*))(p1 + 0x24);
        oldObj = *(void**)(p1 + 0x20);
        *(void**)(p1 + 0x20) = p2;
        *(void(**)(void*))(p1 + 0x24) = &FUN_006ae090;
    } else {
        oldFn = *(void(**)(void*))(p1 + 0x24);
        oldObj = *(void**)(p1 + 0x20);
        *(void**)(p1 + 0x20) = 0;
        *(void(**)(void*))(p1 + 0x24) = 0;
    }
    if (oldFn)
        oldFn(oldObj);
    return true;
}

// ---------------------------------------------------------------------------
// 006ae4c0  bool Self::Get(void** out)
// ---------------------------------------------------------------------------
struct ObjX {
    void fn();             // FUN_006926b0
};
struct IfaceX {
    virtual void slot0();
};
struct Self {
    ObjX* mC;              // +0xc
    bool Get(void** out);
};

// @ 0x006ae4c0
bool Self::Get(void** out)
{
    ObjX* p = *(ObjX**)((char*)this + 0xc);
    if (p) {
        p->fn();
        IfaceX* q = *(IfaceX**)(*(int*)((char*)this + 0xc) + 0x20);
        if (q)
            q->slot0();
        *out = q;
        return q != 0;
    }
    IfaceX* q = 0;
    *out = q;
    return q != 0;
}

// ---------------------------------------------------------------------------
// 006ae600  void RBTree::DoNukeSubtree(RBNode* n)
// ---------------------------------------------------------------------------
struct RBNode { RBNode* left; RBNode* right; char pad[0x1c - 8]; Releasable* mgr; };
struct RBTree {
    char pad[0x18];
    RBNode* freeList;    // 0x18
    char pad2[4];        // 0x1c
    RBNode* poolBegin;   // 0x20
    RBNode* poolEnd;     // 0x24
    void DoNukeSubtree(RBNode* n);
};

void RBTree::DoNukeSubtree(RBNode* n)
{
    while (n) {
        DoNukeSubtree(n->left);
        RBNode* next = n->right;
        Releasable* mgr = (Releasable*)n->mgr;
        if (mgr)
            mgr->Release();
        if (n < poolBegin || n >= poolEnd) {
            ea_dealloc(n);
        } else {
            n->left = freeList;
            freeList = n;
        }
        n = next;
    }
}

// ===========================================================================
// remaining functions in the slice
// ===========================================================================
extern void* vtbl_154df28;
extern void* vtbl_14093bc;
extern void* vtbl_14093cc;
extern void* vtbl_13effb8;
extern void* vtbl_13eb938;
extern void* vtbl_13ef094;
extern void* vtbl_14094b4;
extern void* vtbl_14094b0;
extern void* vtbl_13fa72c;
extern "C" void* ea_zone_new(unsigned size, void* zone, int, int, int, int); // 0x926020
extern "C" void* ea_eastl_alloc(unsigned size, void* zone, int, int, const char* file, int line); // 0xf473a0
extern "C" void ea_zone_delete(void*);      // 0x926060
extern "C" void* ea_get_manager();          // 0x67dcd0
struct Sub140 { void Init(void* a); };      // FUN_006ac140
struct KRSub  { void Destroy(); };          // FUN_006ad0f0
struct Job0   { void GetStatus(); };        // 0x690120
struct Job2   { void Add(); };              // FUN_0068f950
struct Sub970 { void Do(void* x, void* y, void* a); }; // FUN_006ad970
struct Sub26b0{ void fn(); };               // FUN_006926b0

// ---------------------------------------------------------------------------
// 006ad890  ctor
// ---------------------------------------------------------------------------
// @ 0x006ad890
void __fastcall FUN_006ad890(void* self, void* a)
{
    *(int*)((char*)self + 8) = 0;
    *(int*)((char*)self + 0xc) = 0;
    *(float*)((char*)self + 0x10) = 1.0f;
    *(float*)((char*)self + 0x14) = 2.0f;
    *(int*)((char*)self + 0x18) = 0;
    ((Sub140*)((char*)self + 0x1c))->Init(a);
    *(int*)((char*)self + 0xc) = 0;
    *(int*)((char*)self + 0x18) = 0;
    *(int*)((char*)self + 8) = 1;
    *(void**)((char*)self + 4) = &vtbl_154df28;
}

// ---------------------------------------------------------------------------
// 006adbf0  scalar deleting dtor of the KRMap singleton
// ---------------------------------------------------------------------------
// @ 0x006adbf0
void __fastcall FUN_006adbf0(void* self, unsigned char flag)
{
    *(void**)self = &vtbl_14093cc;
    g_pRegistry = 0;
    ((KRSub*)((char*)self + 0xc))->Destroy();
    *(void**)self = &vtbl_13effb8;
    if (flag & 1)
        ea_zone_delete(self);
}

// ---------------------------------------------------------------------------
// 006adc90  create the KRMap singleton and size three LRU caches
// ---------------------------------------------------------------------------
extern "C" void* ea_zone_new2(unsigned size, void* zone);   // 0x926020
void* __fastcall FUN_006adb40(void* self);

// @ 0x006adc90
void __fastcall FUN_006adc90(void* self, int* arg)
{
    (void)self;
    void* p = ea_zone_new2(0x58, &vtbl_14093bc);
    if (!p)
        g_pRegistry = 0;
    else
        FUN_006adb40(p);
    ((void(__thiscall*)(int*, int, void*, int))(*(void***)arg)[0x64 / 4])(arg, 1, g_pRegistry, 0);
    ((cLRUCache*)(g_caches))->Do(0x10);
    ((cLRUCache*)(g_caches + 0x150))->Do(0x40);
    ((cLRUCache*)(g_caches + 0x2a0))->Do(0x20);
}

// ---------------------------------------------------------------------------
// 006add30  unsigned SList::Init(void* a)   (__thiscall, ret 4)
// ---------------------------------------------------------------------------
struct SList {
    unsigned Init(void* a);
};

// @ 0x006add30
unsigned SList::Init(void* a)
{
    char* s = (char*)this;
    char* p = s + 0x18;
    *(void**)(s + 0x10) = p;
    *(void**)(s + 4) = p;
    *(void**)s = p;
    *(void**)(s + 8) = p + 0x20;
    ((Sub970*)s)->Do(*(void**)a, *(void**)((char*)a + 4), a);
    return (unsigned)this;
}

// ---------------------------------------------------------------------------
// 006adda0  void* __stdcall FUN_006adda0(void* a)  (pool node alloc)
// ---------------------------------------------------------------------------
// @ 0x006adda0
void* __stdcall FUN_006adda0(void* a)
{
    void* n = ea_eastl_alloc(
        0x40, &vtbl_14093bc, 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (n) {
        *(void**)n = *(void**)a;
        ((SList*)((char*)n + 4))->Init((char*)a + 4);
    }
    *(int*)((char*)n + 0x3c) = 0;
    return n;
}

// ---------------------------------------------------------------------------
// 006ae120  dtor (vtable reset + two releases)
// ---------------------------------------------------------------------------
// @ 0x006ae120
void __fastcall FUN_006ae120(void* self)
{
    void* p = *(void**)((char*)self + 0x10);
    if (p)
        ((void(__thiscall*)(void*))(*(void***)p)[2])(p);
    void* q = *(void**)((char*)self + 0xc);
    if (q)
        ((void(__thiscall*)(void*))(*(void***)q)[2])(q);
    *(void**)self = &vtbl_13eb938;
    *(void**)((char*)self + 4) = &vtbl_13ef094;
}

// ---------------------------------------------------------------------------
// 006ae190  dtor
// ---------------------------------------------------------------------------
// @ 0x006ae190
void __fastcall FUN_006ae190(void* self)
{
    void* p = *(void**)((char*)self + 0xc);
    if (p)
        ((void(__thiscall*)(void*))(*(void***)p)[2])(p);
    void* q = *(void**)((char*)self + 8);
    if (q)
        ((void(__thiscall*)(void*))(*(void***)q)[2])(q);
    *(void**)self = &vtbl_13effb8;
}

// ---------------------------------------------------------------------------
// 006ae210  rbtree_node dtor
// ---------------------------------------------------------------------------
// @ 0x006ae210
void __fastcall FUN_006ae210(void* self)
{
    *(void**)self = &vtbl_14094b4;
    *(void**)((char*)self + 4) = &vtbl_14094b0;
    void* p = *(void**)((char*)self + 0xc);
    if (p)
        ((Job0*)p)->GetStatus();
    *(void**)self = &vtbl_13eb938;
    *(void**)((char*)self + 4) = &vtbl_13ef094;
}

// ---------------------------------------------------------------------------
// 006ae2a0  AutoRefCount::operator=
// ---------------------------------------------------------------------------
// @ 0x006ae2a0
void* __fastcall FUN_006ae2a0(void* self, void* p)
{
    int* old = *(int**)self;
    if (p != old) {
        if (p)
            *(int*)((char*)p + 8) = *(int*)((char*)p + 8) + 1;
        *(void**)self = p;
        if (old) {
            int* rc = (int*)((char*)old + 8);
            int n = *(volatile int*)rc += -1;
            if (n == 1) {
                *(volatile int*)rc = 1;
                void* recv = (char*)old + 4;
                if (*(void**)recv)
                    (*(void(__thiscall**)(void*, int))(*(void***)recv))(recv, 1);
            }
        }
    }
    return self;
}

// ---------------------------------------------------------------------------
// 006ae510  Resource::Async ctor
// ---------------------------------------------------------------------------
// @ 0x006ae510
void* __fastcall FUN_006ae510(void* self, void* arg)
{
    *(void**)self = &vtbl_13fa72c;
    *(void**)((char*)self + 4) = &vtbl_13ef094;
    *(void**)((char*)self + 8) = 0;
    *(void**)self = &vtbl_14094b4;
    *(void**)((char*)self + 4) = &vtbl_14094b0;
    int v = *(int*)arg;
    *(int*)((char*)self + 0xc) = v;
    if (v)
        ((Job2*)v)->Add();
    return self;
}

// ---------------------------------------------------------------------------
// 006ae660  pool node alloc from freelist  (partial)
// ---------------------------------------------------------------------------
void* __fastcall FUN_006ae660(void* self, void* val)
{
    void* n = *(void**)((char*)self + 0x18);
    if (n)
        *(void**)((char*)self + 0x18) = *(void**)n;
    else
        n = ea_eastl_alloc(*(unsigned*)((char*)self + 0x28), &vtbl_14093bc, 0, 0,
                           "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                           0xd1);
    void* d = (char*)n + 0x10;
    if (d) {
        *(void**)d = *(void**)val;
        *(void**)((char*)d + 4) = *(void**)((char*)val + 4);
        *(void**)((char*)d + 8) = *(void**)((char*)val + 8);
        *(void**)((char*)d + 0xc) = *(void**)((char*)val + 0xc);
        void* r = *(void**)((char*)d + 0xc);
        if (r)
            (*(void(__thiscall**)(void*))(*(void***)r))(r);
    }
    return n;
}

// ---------------------------------------------------------------------------
// 006ae590  void RBTreeX::Remove(void** out, RBNodeX* n)   (__thiscall, ret 8)
// ---------------------------------------------------------------------------
extern "C" void* F_921580(void*);
extern "C" void  F_921880(void*, void*);

struct RBNodeX { RBNodeX* left; char pad[0x18]; void* mgr; };   // left @0, mgr @0x1c
struct RBTreeX {
    char pad0[4];
    char sub;                  // 0x04
    char pad1[0x14 - 5];
    int  count;                // 0x14
    RBNodeX* freeList;         // 0x18
    char pad2[0x20 - 0x1c];
    RBNodeX* poolBegin;        // 0x20
    RBNodeX* poolEnd;          // 0x24
    void Remove(void** out, RBNodeX* n);
};

// @ 0x006ae590
void RBTreeX::Remove(void** out, RBNodeX* n)
{
    _clamp_dec(count);
    void* r = F_921580(n);
    F_921880(n, &sub);
    if (n->mgr)
        ((Releasable*)n->mgr)->Release();
    if ((char*)n < (char*)poolBegin || (char*)n >= (char*)poolEnd) {
        ea_dealloc(n);
    } else {
        n->left = freeList;
        freeList = n;
    }
    *out = r;
}

// ---------------------------------------------------------------------------
// 006ae3f0  bool RegistryHost::Find(int a, void** out)   (__thiscall, ret 8)
// ---------------------------------------------------------------------------
extern "C" void F_9221b0(void* cs);
extern "C" void F_922270(void* cs);
extern "C" void F_a21dc0(void* out, void* arg);
struct RefObj { virtual void s0(); virtual void s1(); };

struct RegistryHost {
    char pad[0x10];
    char cs;        // 0x10
    char pad2[0x30];
    char map;       // 0x40
    char endMarker; // 0x44
    bool Find(int a, void** out);
};

// @ 0x006ae3f0
bool RegistryHost::Find(int a, void** out)
{
    (void)a;
    F_9221b0(&cs);
    void* it = &endMarker;
    F_a21dc0(&it, &a);
    if (it != &endMarker) {
        RefObj* p = *(RefObj**)((char*)it + 0x1c);
        *out = p;
        p->s0();
        F_922270(&cs);
        return true;
    }
    F_922270(&cs);
    return false;
}

// ---------------------------------------------------------------------------
// 006ad5c0  LRU cache flush: walk buckets, drop refs, run callbacks, GC
// ---------------------------------------------------------------------------
extern "C" void F_6abfa0(void*);                 // 0x6abfa0
extern "C" int  F_6ac0d0(void*);                 // 0x6ac0d0
extern "C" void F_6ad180(void*);                 // 0x6ad180
extern "C" void F_6aca20(void*, void*, void*);   // 0x6aca20
extern "C" void F_6ac630(void*);                 // 0x6ac630
extern "C" void F_7c80c0(void);                  // 0x7c80c0

// @ 0x006ad5c0
void* __fastcall FUN_006ad5c0(void* self, void* filter)
{
    char   buf[1024];       // vector of removed (node, iterator) pairs
    char*  end = buf;
    char*  vec = buf;
    void*  f = filter;

    F_6abfa0((char*)self + 0x48);

    int* it   = *(int**)((char*)self + 0x10);
    int  v    = *it;
    if (v == 0) {
        do { ++it; v = *it; } while (v == 0);
    }
    int* cur  = it;
    int  stop = *(int*)((char*)self + 0x10) + *(int*)((char*)self + 0x14) * 4;

    while (v != stop) {
        void* node = (void*)v;
        void* ref  = *(void**)((char*)node + 0xc);
        int   next = *(int*)((char*)node + 0x10);
        while (next == 0) { ++cur; next = *cur; }

        int pass = 0;
        if (f == 0 || ((unsigned char(__thiscall*)(void*, void*))(((void**)f)[1]))(f, node) != 0) {
            if (ref == 0) {
                pass = 1;
            } else {
                void* q = ((void* (__thiscall*)(void*, int))(((void**)ref)[3]))(ref, 0x355d6f5);
                if (q == 0 || *(int*)((char*)q + 0x14) == 0 || F_6ac0d0(ref) == 1)
                    pass = 1;
            }
            if (pass && (f != 0 || F_6ac0d0((void*)v) != 1)) {
                if (((int (__thiscall*)(void*))(((void**)ref)[4]))(ref) == 1) {
                    F_6ad180((char*)self + 0x30);
                    void* r = *(void**)((char*)node + 0xc);
                    *(void**)((char*)node + 0xc) = 0;
                    void* old = *(void**)(end - 4);
                    *(void**)(end - 4) = r;
                    if (old)
                        ((void(__thiscall*)(void*))(((void**)old)[1]))(old);
                    /* append the (node, cur) pair to the removal vector */
                    *(void**)end = node;
                    *(void**)(end + 4) = cur;
                    F_6aca20(vec, end, end + 8);
                    end += 8;
                }
            }
        }
        v = next;
    }

    LOCK();
    *(int*)((char*)self + 0x48) = *(int*)((char*)self + 0x48) - 1;
    UNLOCK();
    LOCK();
    *(int*)((char*)self + 0x50) = *(int*)((char*)self + 0x50) + 1;
    UNLOCK();

    unsigned n = (unsigned)(end - vec) >> 2;
    for (unsigned i = 0; i < n; ++i)
        F_6ac630(vec);
    F_7c80c0();
    return self;
}

// ---------------------------------------------------------------------------
// 006ada20  cLRUCache::Do(unsigned)  resize + refcount-triggered GC
// ---------------------------------------------------------------------------
extern "C" void F_6ace70(void*, void*);   // 0x6ace70
extern "C" void F_6acaa0(void*, unsigned, void*); // 0x6acaa0
extern "C" void F_9221b0(void*);          // 0x9221b0
extern "C" void F_922270(void*);          // 0x922270

// @ 0x006ada20
void cLRUCache::Do(unsigned n)
{
    cLRUCache* t = this;
    F_9221b0(&t->lock);
    unsigned cnt = (unsigned)((char*)t->end - (char*)t->beg) >> 3;
    for (unsigned i = n; i < cnt; ++i) {
        if (t->beg[i].obj != 0) {
            int* rc = &t->beg[i].refs;
            int old = _InterlockedExchangeAdd((volatile long*)rc, 0);
            if ((old >> 1) == 1 && g_pRegistry != 0)
                F_6ace70((char*)t->beg[i].obj + 8, t->beg[i].obj);
        }
    }
    unsigned have = (unsigned)((char*)t->end - (char*)t->beg) >> 3;
    if (have < n) {
        void* st[2];
        st[0] = 0;
        st[1] = (void*)1000;
        F_6acaa0(t->end, n - have, st);
    } else {
        t->end = t->beg + n;
    }
    F_922270(&t->lock);
}

// ---------------------------------------------------------------------------
// 006adb40  KRMap singleton ctor
// ---------------------------------------------------------------------------
struct BufObj { void Fn(); };             // 0x9265b0

// @ 0x006adb40
void* __fastcall FUN_006adb40(void* self)
{
    char* s = (char*)self;
    *(void**)s = &vtbl_14093bc;
    _InterlockedExchange((volatile long*)(s + 4), 0);
    *(void**)s = &vtbl_14093cc;
    *(unsigned char*)(s + 8) = 0;

    char tmp[32];
    ((Sub140*)tmp)->Init((void*)"App/cCache/KRMap");
    FUN_006ad890(s + 0xc, tmp);
    ((BufObj*)tmp)->Fn();

    _InterlockedExchange((volatile long*)(s + 0x48), 0);
    _InterlockedExchange((volatile long*)(s + 0x4c), 0);
    _InterlockedExchange((volatile long*)(s + 0x50), 0);
    *(int*)(s + 0x54) = (*(volatile char*)0x154c478 != 0) ? 100 : 0;
    return self;
}

// ---------------------------------------------------------------------------
// 006adee0  hash_map::operator[] (find or insert)
// ---------------------------------------------------------------------------
struct HashFind { void Find(void* out, void* key); };        // 0x6ac490
struct HashMapOps { void Insert(void* out, void* key, unsigned char flag); }; // 0x6ade20

// @ 0x006adee0
int* __fastcall FUN_006adee0(void* self, void* key)
{
    char* s = (char*)self;
    char  ctl[0x90];

    ((HashFind*)s)->Find(ctl, key);
    unsigned node = *(unsigned*)ctl;
    if (node == *(unsigned*)(*(int*)(s + 4) + *(int*)(s + 8) * 4)) {
        char     nodebuf[0x40];
        unsigned keyval = *(unsigned*)key;
        void*    range[2];
        range[0] = &keyval;
        range[1] = (char*)&keyval + 4;
        ((SList*)(nodebuf + 4))->Init(range);

        unsigned out[3];
        out[0] = 0;
        ((HashMapOps*)s)->Insert(out, &keyval, (unsigned char)out[0]);
        node = out[0];
    }
    return (int*)(node + 4);
}

// ---------------------------------------------------------------------------
// 006ae880  cAsyncResourceManager::RequestComplete
// ---------------------------------------------------------------------------
extern "C" void* F_67dcd0(void);                 // 0x67dcd0
extern char g_mapLock[];                         // 0x1409448
struct Inserter { void Insert(void* p, int one); };
struct MapLookup { void Find(void** out, void* key); };  // 0xa21dc0

// @ 0x006ae880
void __fastcall FUN_006ae880(void* self, void* p, void* rec)
{
    char* s = (char*)self;
    if (rec) {
        *(void**)((char*)rec + 8)   = *(void**)p;
        *(void**)((char*)rec + 0xc) = *(void**)((char*)p + 4);
        *(void**)((char*)rec + 0x10) = *(void**)((char*)p + 8);
        Inserter* m = (Inserter*)F_67dcd0();
        m->Insert(rec, 1);
    }
    F_9221b0(g_mapLock);
    void* it = 0;
    ((MapLookup*)(s + 0x40))->Find(&it, p);
    if (it != s + 0x44)
        ((RBTreeX*)(s + 0x24))->Remove(&it, (RBNodeX*)it);
    F_922270(g_mapLock);
}


