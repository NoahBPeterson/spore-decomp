// Slice s006ad5c0: resource manager / LRU cache module.
// Most functions are /O2 with no frame pointer; a few are /Od with old-style EH.
// Callees outside the slice are declared as members of stub classes so that the
// compiler emits a __thiscall `mov ecx, ...; call` (addresses are masked relocs).
#include "../../include/types.h"

// ---------------------------------------------------------------------------
// globals (undefined externs -> DIR32 relocations, masked by the verifier)
// ---------------------------------------------------------------------------
extern void* g_pRegistry;   // 0x1603118
extern char  g_caches[];    // 0x16032a8, array of cLRUCache, stride 0x150
extern char  g_cachesEnd[]; // 0x1604118

// ---------------------------------------------------------------------------
// stub classes
// ---------------------------------------------------------------------------
struct cLRUCache {
    void Clear();          // FUN_006ad350
    void Reset();          // FUN_006ad270
    void Do(int);          // FUN_006ada20
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
struct cAsyncResourceRequest {
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
// 006adc90  create the KRMap singleton and size three LRU caches  (partial)
// ---------------------------------------------------------------------------
void __fastcall FUN_006adc90(void* self, void* arg)
{
    (void)self; (void)arg;
    // partial: zone_new(0x58) -> FUN_006adb40, publish to g_pRegistry, notify,
    // then FUN_006ada20(0x10/0x40/0x20) on three cache globals.
}

// ---------------------------------------------------------------------------
// 006add30  sub-list ctor  (partial)
// ---------------------------------------------------------------------------
void __fastcall FUN_006add30(void* self, void* a)
{
    *(void**)((char*)self + 0x10) = (char*)self + 0x18;
    *(void**)((char*)self + 4) = (char*)self + 0x18;
    *(void**)self = (char*)self + 0x18;
    *(void**)((char*)self + 8) = (char*)self + 0x38;
    void* x = *(void**)a;
    void* y = *(void**)((char*)a + 4);
    ((Sub970*)self)->Do(x, y, a);
}

// ---------------------------------------------------------------------------
// 006adda0  allocate one pool node and copy-construct the value  (partial)
// ---------------------------------------------------------------------------
void* __fastcall FUN_006adda0(void* a)
{
    void* n = ea_eastl_alloc(
        0x40, &vtbl_14093bc, 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (n) {
        *(void**)n = *(void**)a;
        ((void(__fastcall*)(void*, void*))FUN_006add30)((char*)n + 4, (char*)a + 4);
    }
    *(int*)((char*)n + 0x3c) = 0;
    return n;
}

// ---------------------------------------------------------------------------
// 006ae120  dtor (vtable reset + two releases)
// ---------------------------------------------------------------------------
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
// complex functions left as partial skeletons (see partial.txt)
// ---------------------------------------------------------------------------
void FUN_006ad5c0() {}
void FUN_006ada20() {}
void FUN_006adb40() {}
void FUN_006adee0() {}
void FUN_006ae3f0() {}
void FUN_006ae590() {}
void FUN_006ae880() {}


