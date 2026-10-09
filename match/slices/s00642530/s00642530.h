#pragma once
// Editor feedback/resource-event hub (0x00642530..0x00643b4f). /O2 /MD /Gy /TP /GS- /arch:SSE
#include "types.h"
typedef unsigned int size_t;

void* EASTL_allocator_allocate(size_t, const char*, int, int, const char*, int); // 0x00f473a0
void EASTL_allocator_deallocate(void*); // 0x00f47380
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

#define EASTL_ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
static inline void* NodeAlloc(size_t n) { return EASTL_allocator_allocate(n, "Editor", 0, 0, EASTL_ALLOC_FILE, 0xd1); }

#define AT(T, off) (*(T*)((char*)this + (off)))

// ---- intrusive refcounted object: primary vptr at 0, refcount interface at +0x10 ----
struct IRC { virtual void AddRef(); virtual void Release(); };
struct Key3;
struct RCObj {
    virtual void v0(); virtual void v1(const void*); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual uint32_t v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual Key3* v16(); virtual void v17(const void*); virtual bool v18(); virtual void v19(); virtual void v20();
    uint32_t pad[3];
    void AddRef() { ((IRC*)((char*)this + 0x10))->AddRef(); }
    void Release() { ((IRC*)((char*)this + 0x10))->Release(); }
};
struct RCRef {
    RCObj* mp;
    RCRef& Assign(RCObj* p);
    RCRef& Assign2(const RCRef& o);
};
// @ 0x6428c0
struct Key3 {
    uint32_t a, b, c;
    bool operator<(const Key3& o) const {
        if (a != o.a) return a < o.a;
        if (c != o.c) return c < o.c;
        return b < o.b;
    }
};
struct Entry { uint32_t a, b, c, d; };

// ---- red-black tree plumbing ----
struct RBNode { RBNode* right; RBNode* left; RBNode* parent; uint32_t color; };
namespace eastl {
RBNode* RBTreeIncrement(RBNode*);
void RBTreeErase(RBNode*, RBNode*);
void RBTreeInsert(RBNode*, RBNode*, RBNode*, int);
}
struct Tag {};
struct Iter { RBNode* n; Iter() {} Iter(const Iter& o) : n(o.n) {} };
struct EvNode : RBNode { uint32_t key; RCRef val; };
struct EvTree {
    uint32_t first; RBNode anchor; uint32_t size; uint32_t alloc;
    Iter find(const uint32_t& k);
    void DoNukeSubtree(RBNode* n);
};
struct KNode : RBNode { Key3 key; RCRef val; };
struct KTree {
    uint32_t first; RBNode anchor; uint32_t size; uint32_t alloc;
    Iter find(const Key3& k);
    void erase(Iter* out, KNode* n);
    void DoNuke(KNode* n);
};

// ---- list with fixed pool ----
struct LNode { LNode* next; LNode* prev; Key3 key; RCRef val; };
struct LIter { LNode* n; LIter() {} LIter(const LIter& o) : n(o.n) {} };
struct fixed_pool_base { void* mpHead; void* init(void*, size_t, size_t, size_t, size_t); };
struct PoolList {
    LNode* next; LNode* prev; fixed_pool_base pool;
    uint32_t buf[0x258];
    PoolList();
    void clearList();
    int size();
    void erase(LNode** out, LIter pos);
};

struct MsgServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Send(uint32_t id, void* data, int); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void Register(void* listener, uint32_t id);
};
MsgServer* MessageServer();
uint32_t HashKey(void* h, uint32_t id);

template <class T> struct VecT {
    T* mpBegin; T* mpEnd; T* mpCap;
    void DoInsertValue(T* pos, const T& v);
    void DoInsertValues(T* pos, uint32_t n, const T& v);
    void push_back(const T& v) {
        if (mpEnd < mpCap) ::new((void*)mpEnd++) T(v);
        else DoInsertValue(mpEnd, v);
    }
    void resize(uint32_t n);
    void Reserve(uint32_t n);
    void set_capacity_impl(uint32_t n);
    void Init(uint32_t n, void* alloc);
    void swap(VecT& o);
};
typedef VecT<uint32_t> VecU;

struct UUNode : RBNode { uint32_t key; uint32_t val; };
struct MapUU { uint32_t first; RBNode anchor; uint32_t size; uint32_t alloc;
    Iter DoInsertValueHint(Iter hint, const uint32_t* kv, Tag);
    uint32_t* operator_idx(const uint32_t* k);
};
struct KMapNode : RBNode { Key3 key; uint32_t val; };
struct KMap {
    uint32_t first; RBNode anchor; uint32_t size; uint32_t alloc;
    void lower_bound(Iter* out, const Key3& k);
    void DoInsertValue(Iter* out, const Key3* kv, bool);
    void DoInsertAt(Iter* out, RBNode* parent, const Key3* kv, int side);
};

struct Target { void Set(const void* p); };

