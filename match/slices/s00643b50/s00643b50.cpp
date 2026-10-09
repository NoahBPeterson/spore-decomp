// Editor resource hub, part 2 (0x00643b50..0x00644b8f). Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "../s00642530/s00642530.h"

void RemoveHandler(void* obj, uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // EA::Messaging::RemoveHandler // 0x00571db0
Entry* UMoveEntries(Entry* first, Entry* last, Entry* dest);                      // FUN_00c7ea30
void UMoveExtra(Entry** out, Entry* first, Entry* last, Entry* dest, uint32_t extra);// FUN_007f1890
Entry* CopyEntries(Entry* first, Entry* last, Entry* dest);                       // FUN_00705250
void* Alloc6(size_t, const char*, int, int, int, int);                            // EASTL_allocator_allocate (name-only form)

struct Profiler { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void Begin(); virtual void End(); };
Profiler* GetProfiler();                                                           // FUN_0068f4d0

typedef VecT<Entry> VecE;
struct KVMap { RCRef* operator_idx(const Key3* k); };
struct HubC { void Clear(); };

// @ 0x643b50
template <> void VecT<Entry>::set_capacity_impl(uint32_t n) {
    if (n != 0xffffffff && n > (uint32_t)(mpEnd - mpBegin)) {
        Entry* pNew = n ? (Entry*)NodeAlloc(n * 16) : 0;
        UMoveEntries(mpBegin, mpEnd, pNew);
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
        Entry* newEnd = pNew + (mpEnd - mpBegin);
        Entry* newCap = pNew + n;
        mpBegin = pNew;
        mpCap = newCap;
        mpEnd = newEnd;
        return;
    }
    if (n < (uint32_t)(mpEnd - mpBegin)) resize(n);
    VecE temp;
    temp.Init((uint32_t)(mpEnd - mpBegin), (char*)this + 0xc);
    Entry* r;
    UMoveExtra(&r, mpBegin, mpEnd, temp.mpBegin, n);
    temp.mpEnd = r;
    swap(temp);
    if (temp.mpBegin && ((int*)temp.mpBegin)[-1]) EASTL_allocator_deallocate(temp.mpBegin);
}

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
extern void* const g_vtbl_13ff768; extern void* const g_vtbl_13ff760; extern void* const g_vtbl_13ff750;

// @ 0x643c60
Hub3::~Hub3() {
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

// @ 0x643d30
void Hub3::ClearAll() {
    void* h = (void*)AT(uint32_t, 0x64);
    if (h) {
        AT(uint32_t, 0x64) = 0;
        RemoveHandler(h, AT(uint32_t, 0x68), AT(uint32_t, 0x6c), AT(uint32_t, 0x70), AT(uint32_t, 0x74));
    }
    EvTree* t0 = &AT(EvTree, 0x10);
    t0->DoNukeSubtree(t0->anchor.parent);
    t0->anchor.left = &t0->anchor;
    t0->anchor.parent = 0;
    *(uint8_t*)&t0->anchor.color = 0;
    t0->size = 0;
    t0->anchor.right = &t0->anchor;
    EvTree* t1 = &AT(EvTree, 0x2c);
    t1->DoNukeSubtree(t1->anchor.parent);
    t1->anchor.parent = 0;
    *(uint8_t*)&t1->anchor.color = 0;
    t1->size = 0;
    t1->anchor.left = &t1->anchor;
    t1->anchor.right = &t1->anchor;
    ((HubC*)this)->Clear();
}

struct CardData { CardData* ctor(); };
struct CardDataObj { CardDataObj* Construct(); };
typedef RCObj* (*FactoryFn)();

// @ 0x643db0
bool Hub3::Create(uint32_t type, RCObj** out) {
    RCRef ref;
    ref.mp = 0;
    RCObj* p = 0;
    switch (type) {
    case 0x2399be55: case 0x24682294: case 0x2b978c46: case 0x3d97a8e4: case 0x438f6347: case 0x476a98c7: {
        void* mem = EASTL_allocator_allocate(0x78, "Sporepedia/AssetData/cSPAssetDataOTDB", 0, 0, 0, 0);
        if (mem) {
            p = (RCObj*)((CardDataObj*)mem)->Construct();
            if (p) p->AddRef();
        }
        break;
    }
    default: {
        FactoryFn fn = (FactoryFn)*((MapUU*)&AT(char, 0x10))->operator_idx(&type);
        if (fn) {
            ref.Assign(fn());
            p = ref.mp;
        }
        break;
    }
    }
    if (p) {
        if (out) { *out = p; return true; }
        p->Release();
        return true;
    }
    return false;
}

// @ 0x643e70
void Hub3::AddResource(const Key3* key, RCObj* obj) {
    if (!obj) return;
    RCObj* o = obj;
    o->AddRef();
    uint32_t type = o->v9();
    Iter it = AT(EvTree, 0x2c).find(type);
    if (it.n != (RBNode*)&AT(char, 0x30)) {
        RCObj* conv = ((RCObj* (*)(RCObj*))((EvNode*)it.n)->val.mp)(o);
        if (conv != o) {
            if (conv) conv->AddRef();
            o->Release();
            o = conv;
        }
    }
    RCRef* slot = ((KVMap*)&AT(char, 0x48))->operator_idx(key);
    RCObj* old = slot->mp;
    if (o != old) {
        if (o) o->AddRef();
        slot->mp = o;
        if (old) old->Release();
    }
    if (o->v16()->a != 0)
        ((KVMap*)&AT(char, 0xa14))->operator_idx(o->v16())->Assign2(*(RCRef*)&o);
    o->Release();
}

// @ 0x643f70
void Hub3::Request(const Entry* e, char flag) {
    RCObj* obj = 0;
    if (AT(KTree, 0x48).find(*(const Key3*)e).n == (RBNode*)&AT(char, 0x4c)) {
        Iter it2 = AT(KTree, 0xa14).find(*(const Key3*)e);
        if (it2.n != (RBNode*)&AT(char, 0xa18)) {
            RCObj* o = ((KNode*)it2.n)->val.mp;
            if (o) {
                o->v20();
                AddResource((const Key3*)e, o);
                return;
            }
        }
        if (flag) {
            if (Create(e->b, &obj)) {
                obj->v1(e);
                AddResource((const Key3*)e, obj);
            }
            if (obj) obj->Release();
            return;
        }
        AT(VecE, 0x78).push_back(*e);
    }
}

// ---- list-node helpers (pool-backed list at +0x8c) ----
static inline void ListPush(PoolList& l, const Key3& k, RCObj* o) {
    LNode* n = (LNode*)l.pool.mpHead;
    if (n) l.pool.mpHead = n->next; else n = 0;
    Key3* kp = n ? &n->key : 0;
    if (kp) {
        *kp = k;
        n->val.mp = o;
        o->AddRef();
    }
    n->next = (LNode*)&l;
    n->prev = l.prev;
    l.prev->next = n;
    l.prev = n;
}

// @ 0x644040
void Hub3::Update(VecT<Key3>* out) {
    int skipped = 0;
    PoolList& l = AT(PoolList, 0x8c);
    LNode* p = l.next;
    if (p != (LNode*)&l) {
        do {
            RCObj* o = p->val.mp;
            Key3* k = &p->key;
            if (!o) {
                p = p->next;
                ++skipped;
            } else {
                o->AddRef();
                if (!o->v18()) {
                    p = p->next;
                    ++skipped;
                } else {
                    Iter it = AT(KTree, 0x48).find(*k);
                    if (it.n == (RBNode*)&AT(char, 0x4c)) {
                        AddResource(k, o);
                        if (out) out->push_back(*k);
                    }
                    LNode* next = p->next;
                    LNode* e = next->prev;
                    e->prev->next = e->next;
                    e->next->prev = e->prev;
                    if (e->val.mp) e->val.mp->Release();
                    e->next = (LNode*)l.pool.mpHead;
                    l.pool.mpHead = e;
                    p = next;
                }
            }
            if (o) o->Release();
        } while (p != (LNode*)&l);
    }
    int budget = ((-(int)(AT(uint8_t, 0xa10) != 0) & 0xffffffab) + 100) - skipped;
    GetProfiler()->Begin();
    VecE& v = AT(VecE, 0x78);
    while (v.mpBegin != v.mpEnd && budget > 0) {
        Entry* e = v.mpEnd - 1;
        RCObj* o = 0;
        Create(e->b, &o);
        if (o) {
            o->v17(e);
            if (o->v18()) {
                Iter it = AT(KTree, 0x48).find(*(Key3*)e);
                if (it.n == (RBNode*)&AT(char, 0x4c)) {
                    AddResource((Key3*)e, o);
                    if (out) out->push_back(*(Key3*)e);
                }
            } else {
                Key3 kk;
                kk.a = e->a; kk.b = e->b; kk.c = e->c;
                ListPush(l, kk, o);
                --budget;
            }
            v.mpEnd -= 1;
            o->Release();
        }
    }
    GetProfiler()->End();
}

// @ 0x6442e0
bool Hub3::Want(const Key3* k) {
    Iter it = AT(KTree, 0x48).find(*k);
    if (it.n != (RBNode*)&AT(char, 0x4c)) return true;
    PoolList& l = AT(PoolList, 0x8c);
    for (LNode* p = l.next; p != (LNode*)&l; p = p->next) {
        if (p->val.mp && p->key.a == k->a && p->key.b == k->b && p->key.c == k->c) return true;
    }
    VecE& v = AT(VecE, 0x78);
    Entry* e = v.mpBegin;
    if (e != v.mpEnd) {
        do {
            if (e->a == k->a && e->b == k->b && e->c == k->c) {
                int n = 0;
                for (LNode* q = l.next; q != (LNode*)&l; q = q->next) ++n;
                if (n >= 100) {
                    Entry* d = e;
                    Entry* s = e + 1;
                    if (s < v.mpEnd) { do { *d = *s; ++s; ++d; } while (s != v.mpEnd); }
                    v.mpEnd -= 1;
                    v.push_back(*e);
                    return true;
                }
                RCObj* o = 0;
                Create(e->b, &o);
                if (o) {
                    o->v17(e);
                    Key3 kk; kk.a = e->a; kk.b = e->b; kk.c = e->c;
                    ListPush(l, kk, o);
                    if (e + 1 < v.mpEnd) CopyEntries(e + 1, v.mpEnd, e);
                    v.mpEnd -= 1;
                    o->Release();
                }
                return true;
            }
            e = e + 1;
        } while (e != v.mpEnd);
    }
    return false;
}

// @ 0x644550
void Hub3::Load(VecT<Key3>* v, char b) {
    AT(uint8_t, 0xa10) = 0;
    ((HubC*)this)->Clear();
    if (v) {
        if (!b) AT(VecE, 0x78).Reserve((uint32_t)(((char*)v->mpEnd - (char*)v->mpBegin) >> 4));
        else AT(VecE, 0x78).set_capacity_impl(0xffffffff);
        int off = 0;
        int n = (int)(((char*)v->mpEnd - (char*)v->mpBegin) >> 4);
        if (n > 0) {
            do {
                Request((Entry*)((char*)v->mpBegin + off), b);
                off += 0x10;
            } while (--n);
        }
    }
}

// @ 0x6445c0
void Hub3::Load2(VecT<Key3>* src) {
    VecE tmp;
    tmp.mpBegin = 0; tmp.mpEnd = 0; tmp.mpCap = 0;
    tmp.Reserve((uint32_t)(src->mpEnd - src->mpBegin));
    for (uint32_t i = 0; i < (uint32_t)(src->mpEnd - src->mpBegin); ++i) {
        Entry e;
        e.a = src->mpBegin[i].a; e.b = src->mpBegin[i].b; e.c = src->mpBegin[i].c; e.d = 0;
        tmp.push_back(e);
    }
    AT(uint8_t, 0xa10) = 0;
    ((HubC*)this)->Clear();
    int n = (int)(tmp.mpEnd - tmp.mpBegin);
    VecE& v = AT(VecE, 0x78);
    v.Reserve(n);
    Entry* e = tmp.mpBegin;
    while (n > 0) {
        Iter it = AT(KTree, 0x48).find(*(Key3*)e);
        if (it.n == (RBNode*)&AT(char, 0x4c)) {
            Iter it2 = AT(KTree, 0xa14).find(*(Key3*)e);
            RCObj* o;
            if (it2.n == (RBNode*)&AT(char, 0xa18) || (o = ((KNode*)it2.n)->val.mp) == 0) {
                v.push_back(*e);
            } else {
                o->v20();
                AddResource((Key3*)e, o);
            }
        }
        ++e;
        --n;
        (void)0;
    }
    AT(uint8_t, 0xa10) = 1;
    if (tmp.mpBegin && ((int*)tmp.mpBegin)[-1]) EASTL_allocator_deallocate(tmp.mpBegin);
}

// ---- globals read by the launch-data factory and the dialog helpers ----
struct Q4 { uint32_t a, b, c, d; };
extern Q4 g15da784, g15da7c4;
struct PropOwner { char pad[0x3c]; struct { char pad[0x118]; int flag; }* inner; };
extern PropOwner* g_15fd918;
struct EditorLaunchData { EditorLaunchData* ctor(); };
struct SlotCall { virtual void s0(); virtual void s1(); };
#define OF(T, off) (*(T*)((char*)o + (off)))

// @ 0x6447c0
void MakeLaunchData(char flag, RCObj** out) {
    if (!out) return;
    bool b = flag != 0;
    Q4 q = g15da784;
    uint8_t bl = 1;
    uint8_t nb = 1;
    uint8_t bb = 0;
    uint8_t nb2 = bl;
    if (b) {
        q = g15da7c4;
        bl = 0; nb = 0; bb = 1; nb2 = bl;
    }
    if (g_15fd918->inner->flag != 0) bl = 0;
    void* mem = EASTL_allocator_allocate(0x9c, "Editor", 0, 0, 0, 0);
    char* o = (char*)(mem ? ((EditorLaunchData*)mem)->ctor() : 0);
    OF(uint32_t, 0x24) = q.a;
    OF(uint32_t, 0x28) = q.b;
    OF(uint32_t, 0x2c) = q.c;
    OF(uint8_t, 0x34) = nb;
    OF(uint32_t, 0x30) = q.d;
    OF(uint8_t, 0x3d) = bb;
    OF(uint8_t, 0x6d) = flag;
    OF(uint8_t, 0x6f) = nb2;
    OF(uint8_t, 0x36) = 1; OF(uint8_t, 0x37) = 1; OF(uint8_t, 0x38) = 1;
    OF(uint8_t, 0x3a) = bl;
    OF(uint8_t, 0x64) = 1;
    ((SlotCall*)o)->s1();
    *out = (RCObj*)o;
}

// @ 0x6448e0
uint8_t GetFlag() {
    uint8_t b = 0;
    MessageServer()->Send(0x12a93f05, &b, 0);
    return b;
}

// @ 0x644910
struct Msg910 { Key3 k; uint8_t flag; uint8_t pad[3]; Key3 out; };
uint8_t __stdcall Query910(const Key3* in, Key3* out) {
    Msg910 m;
    m.k = *in;
    m.flag = 1;
    m.out.a = 0; m.out.b = 0; m.out.c = 0;
    MessageServer()->Send(0xf1ff568b, &m, 0);
    *out = m.out;
    return m.flag;
}

// @ 0x644990
extern Key3 g1525858, g1525864, g1525870, g152587c, g15258ac;
void Dlg809db0(void* a, const Key3* k);
struct Dlg { char pad[0x4]; };
struct HubD {
    void Fn990();
    void Fn_a40();
};
void HubD::Fn990() {
    Key3 k; k.a = 0; k.b = 0; k.c = 0;
    uint8_t flag = 0;
    const Key3* p;
    if (AT(uint32_t, 0x22c) == 0) {
        MessageServer()->Send(0x12a93f05, &flag, 0);
        p = &g1525858;
        if (!flag) p = &g1525864;
    } else {
        MessageServer()->Send(0x12a93f05, &flag, 0);
        p = &g1525870;
        if (!flag) p = &g152587c;
    }
    k.a = p->a;
    k.b = p->b;
    k.c = p->c;
    Dlg809db0(&AT(char, 4), &k);
    AT(uint32_t, 0x230) = 1;
}

// @ 0x644a40
void HubD::Fn_a40() {
    void* p = this ? &AT(char, 4) : 0;
    Dlg809db0(p, &g15258ac);
    AT(uint32_t, 0x230) = 6;
}

// @ 0x644a80
struct RCBase { virtual void v0(); virtual void v1(); virtual void v2(); };
struct LocaleMsg {
    uint32_t vt0, vt1, f8; RCBase* owner; Key3 key; uint8_t b;
    LocaleMsg(RCBase* o, const Key3* k, uint8_t bb);
    void Dtor();
};
LocaleMsg::LocaleMsg(RCBase* o, const Key3* k, uint8_t bb) {
    *(volatile uint32_t*)&vt1 = 0x13ef094;
    f8 = 0;
    vt0 = 0x13ff800;
    vt1 = 0x13ff7fc;
    owner = o;
    if (o) o->v0();
    key = *k;
    b = bb;
}

// @ 0x644af0
void LocaleMsg::Dtor() {
    if (owner) owner->v1();
    vt1 = 0x13ef094;
    vt0 = 0x13eb918;
}

// @ 0x644b10
struct InitBlock {
    uint32_t id; uint32_t m4, m8, mc; bool b10, b11, b12, b13, b14; char p15[3];
    uint32_t m18, m1c, m20; bool b24; char p25[3]; uint32_t m28; bool b2c; char p2d[3];
    uint32_t m30, m34, m38, m3c, m40, m44;
    InitBlock* Init();
};
InitBlock* InitBlock::Init() {
    id = 0x578c04fa;
    m4 = 0; m8 = 0; mc = 0;
    b10 = false; b11 = false; b12 = false; b13 = true; b14 = false;
    m18 = 0; m1c = 0; m20 = 0;
    b24 = true;
    m28 = 0;
    b2c = false;
    m30 = 0xad0e52;
    m34 = 1;
    m38 = 0; m3c = 0; m40 = 0; m44 = 0;
    return this;
}

// @ 0x644b60
struct TwoRef { char pad[0x40]; RCBase* a; RCBase* b; void Release2(); };
void TwoRef::Release2() {
    RCBase* x = b;
    if (x) x->v2();
    RCBase* y = a;
    if (y) y->v2();
}
// --- equivalence checker address annotations
    void EASTL_allocator_allocate(...); // 0x00f473a0
    void EASTL_allocator_deallocate(...); // 0x00f47380
    void MessageServer(...); // 0x0067dcc0
    void RemoveHandler(...); // 0x00571db0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct PoolList {
    void clearList(); // 0x00642da0
};
struct KTree {
    void DoNuke(void*); // 0x00642d00
};
struct RCRef {
    void Assign2(int&); // 0x00642930
};
struct KVMap {
    void operator_idx(void*); // 0x00643ac0
};
}
