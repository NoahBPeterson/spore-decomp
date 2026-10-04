// Editor resource hub (0x00642530..0x00643b4f). Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "s00642530.h"

// @ 0x6428c0
RCRef& RCRef::Assign(RCObj* p) {
    RCObj* old = mp;
    if (p != old) { if (p) p->AddRef(); mp = p; if (old) old->Release(); }
    return *this;
}
// @ 0x642930
RCRef& RCRef::Assign2(const RCRef& o) {
    RCObj* p = o.mp; RCObj* old = mp;
    if (p != old) { if (p) p->AddRef(); mp = p; if (old) old->Release(); }
    return *this;
}

// ============ class with a message handler (ctl) ============
struct Ctl {
    char pad0[0x24];
    bool f24, f25, f26;
    char pad1;
    uint32_t m28;
    int mode;
    union { float f; uint32_t i; } v0;
    float v1, v2;
    char pad2[4];
    Target tgt;
    void HandleMessage(const uint32_t* m);
};

// @ 0x642530
void Ctl::HandleMessage(const uint32_t* m) {
    switch (m[0]) {
    case 0x2dc9d1e:
        if (m[1] == 0x2e1a75d) m28 = m[2];
        return;
    case 0x2f05c57 + 1:
    case 0x2f05c57 + 2:
    case 0x2f05c5f:
    case 0x3fea1a0:
        if (m[1] == 0x2e1a7ff) {
            if (mode == 2) { mode = 0; v0.i = 0; v1 = -1.0f; v2 = -1.0f; }
            else if (mode != 0) return;
            if (m[0] == 0x2f05c58 && 0.0f < *(const float*)&m[2]) v0.i |= 2;
            if (m[0] == 0x2f05c59 && 0.0f < *(const float*)&m[2]) v0.i |= 1;
            if (m[0] == 0x3fea1a0) v1 = *(const float*)&m[2];
            if (m[0] == 0x2f05c5f) { v2 = *(const float*)&m[2]; return; }
        }
        return;
    case 0x429d47c:
    case 0x429d47d:
    case 0x429d47e:
        if (m[1] == 0x2e1a7ff) {
            if (mode == 2) { mode = 1; v0.f = -1.0f; v1 = -1.0f; v2 = -1.0f; }
            else if (mode != 1) return;
            if (m[0] == 0x429d47c) v0.f = *(const float*)&m[2];
            if (m[0] == 0x429d47d) v1 = *(const float*)&m[2];
            if (m[0] == 0x429d47e) { v2 = *(const float*)&m[2]; return; }
        }
        return;
    case 0x17a1c72d:
        if (m[1] == 0x2e1a75d) tgt.Set(&m[2]);
        return;
    case 0x665f917:
        if (m[1] == 0x2e1a75d) f25 = m[2] == 1;
        return;
    case 0x67b82d8:
        if (m[1] == 0x2e1a75d) f26 = m[2] == 1;
        return;
    case 0x54a32960:
        if (m[1] == 0x2e1a75d) f24 = m[2] == 1;
        return;
    }
}

// ============ hub ============
struct Hub {
    char pad[0x10];
    bool GetEventIDs(VecU* v);
    void Init();
    RCObj* FindA(uint32_t k);
    RCObj* FindB(uint32_t k);
    bool OnMessage(uint32_t id, const uint32_t* m);
    void Remove(const Key3* k);
    void Clear();
    int IsEmpty();
    int PendingCount();
};

// @ 0x642700
bool Hub::GetEventIDs(VecU* v) {
    if (AT(uint32_t, 8) == 0x2b978c46) {
        void* h = &AT(uint32_t, 4);
        v->push_back(HashKey(h, 0xa426730b));
        v->push_back(HashKey(h, 0xad56080c));
        v->push_back(HashKey(h, 0xf71fa311));
        v->push_back(HashKey(h, 0xbeb528cb));
        v->push_back(HashKey(h, 0x2db6dad3));
        return true;
    }
    return false;
}

// @ 0x642860
extern void* g_vtbl_13ff74c[];
struct Reg {
    char pad[0x64];
    MsgServer* server; void* sub; void* kind; uint32_t one; uint32_t zero;
    void Init();
};
void Reg::Init() {
    void* p = this ? (char*)this + 4 : 0;
    MsgServer* s = MessageServer();
    server = s;
    sub = p;
    kind = (void*)0x13ff74c;
    one = 1;
    zero = 0;
    if (s && p) s->Register(p, 0x4249453);
}


// @ 0x642910
int Hub::IsEmpty() {
    if (AT(uint32_t, 0x78) == AT(uint32_t, 0x7c) && AT(uint32_t, 0x8c) == (uint32_t)&AT(uint32_t, 0x8c))
        return 1;
    return 0;
}

// @ 0x6429d0
struct KV {
    Key3 key; RCRef val;
    KV(const KV& o) : key(o.key), val(o.val) { if (val.mp) val.mp->AddRef(); }
    KV(const Key3& k) : key(k) { val.mp = 0; }
};
void* __stdcall AllocKVNode(const KV* src) {
    char* node = (char*)NodeAlloc(0x20);
    new((void*)(node + 0x10)) KV(*src);
    return node;
}

// @ 0x642c10
RCObj* Hub::FindA(uint32_t k) {
    RBNode* n = AT(EvTree, 0x10).find(k).n;
    if (n != (RBNode*)&AT(char, 0x14)) return ((EvNode*)n)->val.mp;
    return 0;
}
// @ 0x642c40
RCObj* Hub::FindB(uint32_t k) {
    RBNode* n = AT(EvTree, 0x2c).find(k).n;
    if (n != (RBNode*)&AT(char, 0x30)) return ((EvNode*)n)->val.mp;
    return 0;
}

// @ 0x642d00
void KTree::DoNuke(KNode* n) {
    while (n) {
        DoNuke((KNode*)n->right);
        KNode* l = (KNode*)n->left;
        if (n->val.mp) n->val.mp->Release();
        EASTL_allocator_deallocate(n);
        n = l;
    }
}

// @ 0x642da0
void PoolList::clearList() {
    LNode* p = next;
    while (p != (LNode*)this) {
        LNode* cur = p;
        p = p->next;
        if (cur->val.mp) cur->val.mp->Release();
        cur->next = (LNode*)pool.mpHead;
        pool.mpHead = cur;
    }
}


// @ 0x643060
int Hub::PendingCount() {
    int n = 0;
    for (uint32_t* p = (uint32_t*)AT(uint32_t, 0x8c); p != &AT(uint32_t, 0x8c); p = (uint32_t*)*p) ++n;
    return n;
}

// @ 0x643080
void KTree::erase(Iter* out, KNode* n) {
    --size;
    RBNode* nx = eastl::RBTreeIncrement(n);
    eastl::RBTreeErase(n, &anchor);
    if (n->val.mp) n->val.mp->Release();
    EASTL_allocator_deallocate(n);
    out->n = nx;
}

// @ 0x6430d0
void PoolList::erase(LNode** out, LIter pos) {
    pos.n = pos.n->next;
    LNode* e = pos.n->prev;
    e->prev->next = e->next;
    e->next->prev = e->prev;
    if (e->val.mp) e->val.mp->Release();
    e->next = (LNode*)pool.mpHead;
    pool.mpHead = e;
    *out = pos.n;
}

// ---- helpers called by vector<Entry> / rbtree (bodies in other slices) ----
void MoveUninit(Entry** out, Entry* first, Entry* last, Entry* dest, Entry* extra);
Entry* CopyBackward(Entry* first, Entry* last, Entry* destEnd);
void FillRange(Entry* first, Entry* last, const Entry* v);
void FillN(Entry* dest, uint32_t n, const Entry* v, Entry* extra);
Entry* UCopy(Entry* first, Entry* last, Entry* dest);
Entry* CopyRange(Entry* first, Entry* last, Entry* dest);   // eastl copy_impl<RunInfo*>

// @ 0x642ec0
template <> void VecT<Entry>::DoInsertValues(Entry* pos, uint32_t n, const Entry& value) {
    if (n <= (uint32_t)(mpCap - mpEnd)) {
        if (n > 0) {
            const Entry temp = value;
            Entry* oldEnd = mpEnd;
            const uint32_t nExtra = (uint32_t)(oldEnd - pos);
            if (n < nExtra) {
                Entry* r;
                MoveUninit(&r, oldEnd - n, oldEnd, oldEnd, pos);
                mpEnd += n;
                CopyBackward(pos, oldEnd - n, oldEnd);
                FillRange(pos, pos + n, &temp);
            } else {
                FillN(oldEnd, n - nExtra, &temp, pos);
                mpEnd += n - nExtra;
                Entry* r;
                MoveUninit(&r, pos, oldEnd, mpEnd, pos);
                mpEnd += nExtra;
                FillRange(pos, oldEnd, &temp);
            }
        }
    } else {
        uint32_t nPrev = (uint32_t)(mpEnd - mpBegin);
        uint32_t nNew = nPrev ? nPrev * 2 : 1;
        if (nNew < nPrev + n) nNew = nPrev + n;
        Entry* pNewData = nNew ? (Entry*)NodeAlloc(nNew * 16) : 0;
        Entry* pNewEnd = UCopy(mpBegin, pos, pNewData);
        FillN(pNewEnd, n, &value, pos);
        pNewEnd = UCopy(pos, mpEnd, pNewEnd + n);
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCap = pNewData + nNew;
    }
}

// @ 0x643790  (instantiated via explicit instantiation below)
// @ 0x6437d0
template <> void VecT<Entry>::resize(uint32_t n) {
    uint32_t cur = (uint32_t)(mpEnd - mpBegin);
    if (n > cur) {
        Entry v;
        v.a = 0; v.b = 0; v.c = 0;
        DoInsertValues(mpEnd, n - cur, v);
    } else {
        Entry* first = mpBegin + n;
        Entry* last = mpEnd;
        CopyRange(last, mpEnd, first);
        mpEnd -= (last - first);
    }
}
template struct VecT<Entry>;

// @ 0x6433a0
struct KVMap {
    uint32_t first; RBNode anchor; uint32_t size; uint32_t alloc;
    Iter lower_bound(const Key3* k);
    RCRef* operator_idx(const Key3* k);
    void DoInsertValueHint(Iter* out, Iter hint, const KV* kv, Tag);
    Iter DoInsertValueHintK(Iter hint, const KV* kv, Tag);
    void DoInsertValueImpl(Iter* out, RBNode* parent, const KV* kv, Tag);
    void DoInsertValue(Iter* out, const KV* kv, Tag);
};
void KVMap::DoInsertValueHint(Iter* out, Iter pos, const KV* kv, Tag tag) {
    RBNode* hint = pos.n;
    if (hint == anchor.right || hint == &anchor) {
        if (size && ((KNode*)anchor.right)->key < kv->key) {
            DoInsertValueImpl(out, anchor.right, kv, Tag());
            return;
        }
        Iter it;
        DoInsertValue(&it, kv, Tag());
        out->n = it.n;
        return;
    }
    RBNode* next = eastl::RBTreeIncrement(hint);
    if (((KNode*)hint)->key < kv->key && kv->key < ((KNode*)next)->key) {
        if (hint->right) {
            void* node = AllocKVNode(kv);
            eastl::RBTreeInsert((RBNode*)node, next, &anchor, 0);
            ++size;
            out->n = (RBNode*)node;
            return;
        }
        DoInsertValueImpl(out, hint, kv, Tag());
        return;
    }
    Iter it;
    DoInsertValue(&it, kv, Tag());
    out->n = it.n;
}

// @ 0x643500
struct HubB {
    bool OnMessage(uint32_t id, const uint32_t* m);
};
bool HubB::OnMessage(uint32_t id, const uint32_t* m) {
    if (id == 0x4249453) {
        Key3 key;
        key.a = m[6]; key.b = m[2]; key.c = m[4];
        KTree& t = AT(KTree, 0xa10);
        Iter it = t.find(key);
        if (it.n != &t.anchor) {
            Iter r;
            t.erase(&r, (KNode*)it.n);
            return false;
        }
        PoolList& l = AT(PoolList, 0x88);
        for (LNode* p = l.next; p != (LNode*)&l; p = p->next) {
            RCObj* o = p->val.mp;
            if (o && p->key.a == key.a && p->key.b == key.b && p->key.c == key.c) {
                o->v19();
                o->v2();
                LNode* r;
                LIter pi; pi.n = p; l.erase(&r, pi);
            }
        }
    }
    return false;
}

// @ 0x6435e0
void Hub::Remove(const Key3* k) {
    KTree& t = AT(KTree, 0x48);
    Iter it = t.find(*k);
    if (it.n != (RBNode*)&AT(char, 0x4c)) {
        KNode* n = (KNode*)it.n;
        n->val.mp->v2();
        Iter r;
        t.erase(&r, n);
        return;
    }
    PoolList& l = AT(PoolList, 0x8c);
    for (LNode* p = l.next; p != (LNode*)&AT(char, 0x8c); p = p->next) {
        RCObj* o = p->val.mp;
        if (o && p->key.a == k->a && p->key.b == k->b && p->key.c == k->c) {
            o->v19();
            o->v2();
            LNode* e = p->next->prev;
            e->prev->next = e->next;
            e->next->prev = e->prev;
            if (e->val.mp) e->val.mp->Release();
            e->next = (LNode*)l.pool.mpHead;
            l.pool.mpHead = e;
            return;
        }
    }
    VecT<Entry>& v = AT(VecT<Entry>, 0x78);
    Entry* e = v.mpBegin;
    Entry* end = v.mpEnd;
    if (e != end) {
        while (e->a != k->a || e->b != k->b || e->c != k->c) {
            e = e + 1;
            if (e == end) return;
        }
        Entry* src = e + 1;
        if (src < end) {
            do { *e = *src; ++src; ++e; } while (src != end);
        }
        v.mpEnd = v.mpEnd - 1;
    }
}

// @ 0x643740
PoolList::PoolList() {
    fixed_pool_base tmp;
    tmp.mpHead = 0;
    tmp.init(buf, 0x960, 0x18, 4, 0);
    next = 0;
    prev = 0;
    pool.mpHead = 0;
    pool.init(tmp.mpHead, 0x960, 0x18, 4, 0);
    next = (LNode*)this;
    prev = (LNode*)this;
}

// @ 0x643840
struct Hub2 {
    char pad[0xa2c];
    Hub2();
    void Clear();
};
extern void* const g_vtbl_13eb394[];
Hub2::Hub2() {
    uint32_t zero = 0;
    uint32_t ebx = 0;
    volatile uint32_t* v = (volatile uint32_t*)this;
    v[1] = 0x13eb394;
    v[2] = 0x13ec458;
    v[3] = ebx;
    v[0] = 0x13ff768;
    v[1] = 0x13ff760;
    v[2] = 0x13ff750;
    // tree at 0x10 (anchor 0x14)
    AT(uint32_t, 0x18) = zero; AT(uint32_t, 0x1c) = zero; AT(uint32_t, 0x20) = zero;
    AT(uint32_t, 0x1c) = ebx; AT(uint8_t, 0x20) = (uint8_t)ebx; AT(uint32_t, 0x24) = ebx;
    { uint32_t* a = &AT(uint32_t, 0x14); *a = (uint32_t)a; AT(uint32_t, 0x18) = (uint32_t)a; }
    // tree at 0x2c (anchor 0x30)
    AT(uint32_t, 0x34) = zero; AT(uint32_t, 0x38) = zero; AT(uint32_t, 0x3c) = zero;
    AT(uint32_t, 0x38) = ebx; AT(uint8_t, 0x3c) = (uint8_t)ebx; AT(uint32_t, 0x40) = ebx;
    { uint32_t* a = &AT(uint32_t, 0x30); *a = (uint32_t)a; AT(uint32_t, 0x34) = (uint32_t)a; }
    // tree at 0x48 (anchor 0x4c)
    AT(uint32_t, 0x50) = zero; AT(uint32_t, 0x54) = zero; AT(uint32_t, 0x58) = zero;
    { uint32_t* a = &AT(uint32_t, 0x4c); *a = (uint32_t)a; AT(uint32_t, 0x50) = (uint32_t)a; }
    AT(uint32_t, 0x54) = ebx; AT(uint8_t, 0x58) = (uint8_t)ebx; AT(uint32_t, 0x5c) = ebx;
    AT(uint32_t, 0x64) = ebx; AT(uint32_t, 0x68) = ebx; AT(uint32_t, 0x6c) = ebx;
    AT(uint32_t, 0x70) = ebx; AT(uint32_t, 0x74) = ebx; AT(uint32_t, 0x78) = ebx;
    AT(uint32_t, 0x7c) = ebx; AT(uint32_t, 0x80) = ebx;
    new((void*)&AT(PoolList, 0x8c)) PoolList();
    AT(uint8_t, 0xa10) = (uint8_t)ebx;
    uint32_t* n = &AT(uint32_t, 0xa18);
    n[1] = zero; n[2] = zero; n[3] = zero;
    AT(uint32_t, 0xa1c) = (uint32_t)n;
    *n = (uint32_t)n;
    AT(uint32_t, 0xa20) = ebx; AT(uint8_t, 0xa24) = (uint8_t)ebx; AT(uint32_t, 0xa28) = ebx;
}

// @ 0x643940
void Hub::Clear() {
    KTree& t = AT(KTree, 0x48);
    for (RBNode* n = t.anchor.left; n != &t.anchor; n = eastl::RBTreeIncrement(n))
        ((KNode*)n)->val.mp->v2();
    t.DoNuke((KNode*)t.anchor.parent);
    t.anchor.left = &t.anchor;
    t.anchor.right = &t.anchor;
    t.anchor.parent = 0;
    *(uint8_t*)&t.anchor.color = 0;
    t.size = 0;
    PoolList& l = AT(PoolList, 0x8c);
    for (LNode* p = l.next; p != (LNode*)&l; p = p->next) {
        if (p->val.mp) { p->val.mp->v19(); p->val.mp->v2(); }
    }
    l.clearList();
    l.next = (LNode*)&l;
    l.prev = (LNode*)&l;
    VecT<Entry>& v = AT(VecT<Entry>, 0x78);
    Entry* first = v.mpBegin;
    Entry* last = v.mpEnd;
    Entry* d = first;
    for (Entry* s = last; s != v.mpEnd; ++s, ++d) *d = *s;
    v.mpEnd -= (last - first);
}

// @ 0x643a40
uint32_t* MapUU::operator_idx(const uint32_t* k) {
    RBNode* pNode = anchor.parent;
    RBNode* pEnd = &anchor;
    while (pNode) {
        if (!(((UUNode*)pNode)->key < *k)) { pEnd = pNode; pNode = pNode->left; }
        else pNode = pNode->right;
    }
    if (pEnd == &anchor || *k < ((UUNode*)pEnd)->key) {
        uint32_t kv[2];
        kv[0] = *k; kv[1] = 0;
        Iter hi; hi.n = pEnd;
        Iter it = DoInsertValueHint(hi, kv, Tag());
        pEnd = it.n;
    }
    return &((UUNode*)pEnd)->val;
}

// @ 0x643ac0
RCRef* KVMap::operator_idx(const Key3* k) {
    Iter it = lower_bound(k);
    if (it.n == &anchor || *k < ((KNode*)it.n)->key) {
        KV v(*k);
        it = DoInsertValueHintK(it, &v, Tag());
    }
    return &((KNode*)it.n)->val;
}
