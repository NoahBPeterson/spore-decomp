// src/game/SPEditors/SPAssetListData.cpp -- migrated from slice(s) s00643b50, s00642530, s004bafc0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPAssetListData.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00642530 begin (TODO(rewrite): local stubs, replace by canonical classes)
void EASTL_allocator_deallocate(void*); // 0x00f47380
struct IRC { virtual void AddRef(); virtual void Release(); };
struct Key3;
struct RCObj {
virtual void v0();
virtual void v1(const void*);
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual uint32_t v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual Key3* v16();
virtual void v17(const void*);
virtual bool v18();
virtual void v19();
virtual void v20();
    uint32_t pad[3];
    void AddRef() { ((IRC*)((char*)this + 0x10))->AddRef(); }
    void Release() { ((IRC*)((char*)this + 0x10))->Release(); }
};
struct RCRef {
    RCObj* mp;
    RCRef& Assign(RCObj* p);
    RCRef& Assign2(const RCRef& o);
};
struct Key3 {
    uint32_t a, b, c;
    bool operator<(const Key3& o) const {
        if (a != o.a) return a < o.a;
        if (c != o.c) return c < o.c;
        return b < o.b;
    }
};
struct RBNode { RBNode* right; RBNode* left; RBNode* parent; uint32_t color; };
struct Iter { RBNode* n; Iter() {} Iter(const Iter& o) : n(o.n) {} };
struct KNode : RBNode { Key3 key; RCRef val; };
struct KTree {
    uint32_t first; RBNode anchor; uint32_t size; uint32_t alloc;
    Iter find(const Key3& k);   // 0x00a21dc0 (equiv t2)
    void erase(Iter* out, KNode* n);
    void DoNuke(KNode* n);
};
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
// ---- items of slice s00642530 end

// ---- items of slice s00643b50 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(size_t, void* p) { return p; }
#define AT(T, off) (*(T*)((char*)this + (off)))
struct Entry { uint32_t a, b, c, d; };
struct EvTree {
    uint32_t first; RBNode anchor; uint32_t size; uint32_t alloc;
    Iter find(const uint32_t& k);
    void DoNukeSubtree(RBNode* n);   // 0x009a9600 (equiv t2)
};
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
void RemoveHandler(void* obj, uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // EA::Messaging::RemoveHandler // 0x00571db0
struct Hub3 {
    char pad[0x10];
    ~Hub3();
    void ClearAll();
    bool Create(uint32_t type, RCObj** out);
    void AddResource(const Key3* key, RCObj* obj);
    void Request(const Entry* e, char flag);
    void Update(VecT<Key3>* out);
    bool Want(const Key3* k);
    void Load(VecT<Key3>* v, char b);
    void Load2(VecT<Key3>* src);
};
// ---- items of slice s00643b50 end

// @ 0x004bbe20
bool IsBakeableType(uint32_t type, uint8_t useSpecial)
{
    if (useSpecial && type == 0x366a930d)
        return true;
    switch (type) {
    case 0x3d97a8e4:
    case 0x2399be55:
    case 0x24682294:
    case 0x2b978c46:
    case 0x438f6347:
    case 0x476a98c7:
        return true;
    default:
        return false;
    }
}

// @ 0x00642d00
void KTree::DoNuke(KNode* n)
{
    while (n) {
        DoNuke((KNode*)n->right);
        KNode* l = (KNode*)n->left;
        if (n->val.mp) n->val.mp->Release();
        EASTL_allocator_deallocate(n);
        n = l;
    }
}

// @ 0x00642da0
void PoolList::clearList()
{
    LNode* p = next;
    while (p != (LNode*)this) {
        LNode* cur = p;
        p = p->next;
        if (cur->val.mp) cur->val.mp->Release();
        cur->next = (LNode*)pool.mpHead;
        pool.mpHead = cur;
    }
}

// @ 0x00643c60
Hub3::~Hub3()
{
    volatile uint32_t* vt = (volatile uint32_t*)this;
    vt[0] = 0x13ff768;
    vt[1] = 0x13ff760;
    vt[2] = 0x13ff750;
    KTree* t = &AT(KTree, 0xa14);
    t->DoNuke((KNode*)t->anchor.parent);
    ((PoolList*)&AT(char, 0x8c))->clearList();
    uint32_t* vb = (uint32_t*)AT(uint32_t, 0x78);
    if (vb && ((int*)vb)[-1]) EASTL_allocator_deallocate(vb);
    void* h = (void*)AT(uint32_t, 0x64);
    if (h) {
        AT(uint32_t, 0x64) = 0;
        RemoveHandler(h, AT(uint32_t, 0x68), AT(uint32_t, 0x6c), AT(uint32_t, 0x70), AT(uint32_t, 0x74));
    }
    AT(KTree, 0x48).DoNuke((KNode*)AT(RBNode*, 0x54));
    AT(EvTree, 0x2c).DoNukeSubtree(AT(RBNode*, 0x38));
    AT(EvTree, 0x10).DoNukeSubtree(AT(RBNode*, 0x1c));
    vt[2] = 0x13ec458;
    vt[1] = 0x13eb394;
    vt[0] = 0x13eb938;
}
