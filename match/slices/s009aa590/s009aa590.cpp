// slice s009aa590 -- nSPCreatureAnim animation manager helpers: EASTL red-black tree map<S4,S3> nodes,
// heap helpers, vectors of intrusive refs, and the manager (Mgr) that owns two trees.
#include "types.h"
#include <string.h>

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t, void* p) { return p; }

#define EASTL_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define EANEW(sz) operator new[]((sz), "EASTL", 0, 0, EASTL_FILE, 0xd1)

// ---- intrusive-refcounted payload types (names unknown) ----
struct RefB { void AddRef(); void Release(); };               // 0x009B3450 / 0x009C26A0
struct RefC { void AddRef(); void Release(); void Fn(int); }; // 0x0099C970 / 0x009A3630 / 0x009A3080
struct Z { int pad; int size; };
struct RefD { Z* z; int pad; uint32_t stamp; void AddRef(); void Release(); }; // 0x009AC2A0 / 0x009AE1C0
struct RefE { void AddRef(); void Release(); };               // 0x00A17060 / creature_instance_data::Release 0x009C4CC0

struct S4 { RefB* p; uint32_t a, b, c; };          // map key: compares p, a, c
struct S3 { RefC* p; RefD* q; int r; };
struct Pair {
    S4 first; S3 second;
    Pair(const Pair& s);                            // 0x009AA6C0
    Pair(const S4& k, const S3& v);                 // 0x009AA9F0
};

struct Node { Node* right; Node* left; Node* parent; int color; };
struct NodeP : Node { Pair v; };                    // 0x2c
struct NodeQ : Node { RefB* k; RefE* v; };          // 0x18

namespace eastl {
Node* __cdecl RBTreeIncrement(const Node*);
Node* __cdecl RBTreeDecrement(const Node*);
void  __cdecl RBTreeErase(Node* n, Node* anchor);
void  __cdecl RBTreeInsert(Node* n, Node* parent, Node* anchor, int side);
}

struct TagT {};
struct Cmp {};

static inline bool KeyLess(const S4& x, const S4& y)
{
    if ((uint32_t)x.p < (uint32_t)y.p) return true;
    if ((uint32_t)x.p == (uint32_t)y.p) {
        if (x.a < y.a) return true;
        if (x.a == y.a) return x.c < y.c;
    }
    return false;
}

// @ 0x009AA6C0
__declspec(noinline) Pair::Pair(const Pair& s)
{
    first.p = s.first.p;
    if (first.p) first.p->AddRef();
    first.a = s.first.a; first.b = s.first.b; first.c = s.first.c;
    second.p = s.second.p;
    if (second.p) second.p->AddRef();
    second.q = s.second.q;
    if (second.q) second.q->AddRef();
    second.r = s.second.r;
}

// @ 0x009AA9F0
__declspec(noinline) Pair::Pair(const S4& k, const S3& v)
{
    first.p = k.p;
    if (first.p) first.p->AddRef();
    first.a = k.a; first.b = k.b; first.c = k.c;
    second.p = v.p;
    if (second.p) second.p->AddRef();
    second.q = v.q;
    if (second.q) second.q->AddRef();
    second.r = v.r;
}

struct Iter { Node* n; Iter() {} Iter(const Iter& o) : n(o.n) {} };
struct IterBool { Iter it; bool ok; };

struct TreeP {
    uint8_t pad0; Node anchor_; // anchor at +4
    int size;
    Iter LowerBound(const S4* k);
    Iter Find(const S4* k);
    bool Less(const S4* a, const S4* b);
    Iter InsertNode(Node* pos, const Pair* v, bool left);
    IterBool InsertUnique(const Pair* v, TagT t);
    Iter Erase(Iter n);
    void DoNuke(Node* n);
    Iter InsertHint(Iter pos, const Pair* v, TagT t);
};

// @ 0x009AA590
Iter TreeP::LowerBound(const S4* k)
{
    Node* pEnd = &anchor_;
    Node* cur = anchor_.parent;
    if (cur) {
        do {
            if (!KeyLess(((NodeP*)cur)->v.first, *k)) {
                pEnd = cur;
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        } while (cur);
    }
    Iter r; r.n = pEnd;
    return r;
}

// ---- heap helpers over an array of pointers to elements whose ->z->pad... (key at elem+0x24 -> +8) ----
struct HeapElem { char pad[0x24]; RefD* d; };
struct HP { HeapElem* p; HP() {} HP(const HP& o) : p(o.p) {} };
static inline uint32_t HKey(const HP& e) { return e.p->d->stamp; }

// @ 0x009AA5E0
void PushHeap(HP* first, int topPosition, int position, HP value, Cmp)
{
    for (int parentPosition = (position - 1) >> 1;
         (position > topPosition) && HKey(first[parentPosition]) > HKey(value);
         parentPosition = (position - 1) >> 1) {
        first[position] = first[parentPosition];
        position = parentPosition;
    }
    first[position] = value;
}

// @ 0x009AA640
void AdjustHeap(HP* first, int topPosition, int heapSize, int position, HP value, Cmp c)
{
    int childPosition = 2 * position + 2;
    for (; childPosition < heapSize; childPosition = 2 * (childPosition + 1)) {
        HeapElem* a = first[childPosition].p;
        HeapElem* b = first[childPosition - 1].p;
        if (a->d->stamp > b->d->stamp)
            --childPosition;
        first[position] = first[childPosition];
        position = childPosition;
    }
    if (childPosition == heapSize) {
        first[position] = first[childPosition - 1];
        position = childPosition - 1;
    }
    PushHeap(first, topPosition, position, value, c);
}

// @ 0x009AA720  copy_backward of smart pointers
RefC** CopyBackward(RefC** first, RefC** last, RefC** dEnd)
{
    while (last != first) {
        RefC* s = *--last;
        RefC* old = *--dEnd;
        if (s != old) {
            if (s) s->AddRef();
            *dEnd = s;
            if (old) old->Release();
        }
    }
    return dEnd;
}

// ---- assignment operators ----
struct S4Ref { RefB* p; int a, b, c; S4Ref& operator=(const S4Ref& o); };
struct S3Ref { RefC* p; RefD* q; int r; S3Ref& operator=(const S3Ref& o); };

// @ 0x009AA770
S4Ref& S4Ref::operator=(const S4Ref& o)
{
    RefB* old = p;
    RefB* n = o.p;
    if (n != old) {
        if (n) n->AddRef();
        p = n;
        if (old) old->Release();
    }
    a = o.a; b = o.b; c = o.c;
    return *this;
}

// @ 0x009AA7C0
S3Ref& S3Ref::operator=(const S3Ref& o)
{
    RefC* old = p;
    RefC* n = o.p;
    if (n != old) {
        if (n) n->AddRef();
        p = n;
        if (old) old->Release();
    }
    RefD* n2 = o.q;
    RefD* old2 = q;
    if (n2 != old2) {
        if (n2) n2->AddRef();
        q = n2;
        if (old2) old2->Release();
    }
    r = o.r;
    return *this;
}

// ---- vectors ----
struct VecP { RefC** b; RefC** e; RefC** cap; void DoInsertValue(RefC** pos, RefC* const* v); void push_back(RefC* const* v); };
struct VecR { void** b; void** e; void** cap; void Reserve(uint32_t n); void DoInsertValue(void** pos, void* const* v); };

// @ 0x009AAB80
void VecR::Reserve(uint32_t n)
{
    if (n > (uint32_t)(cap - b)) {
        void** pNew = n ? (void**)EANEW(n * 4) : 0;
        void** d = pNew;
        void** pEnd = e;
        for (void** s = b; s != pEnd; ++s, ++d)
            if (d) *d = *s;
        if (b && ((int*)b)[-1]) operator delete[](b);
        int cnt = (int)(e - b);
        b = pNew;
        e = pNew + cnt;
        cap = pNew + n;
    }
}

static inline void** UCopy(void** first, void** last, void** result)
{
    for (; first != last; ++first, ++result)
        if (result) *result = *first;
    return result;
}

// @ 0x009AB030
void VecR::DoInsertValue(void** position, void* const* value)
{
    if (e != cap) {
        void* const* pValue = value;
        if (value >= position && value < e)
            ++pValue;
        if (e) *e = e[-1];
        void** d = e;
        void** s = e - 1;
        while (s != position) { --d; --s; *d = *s; }
        *position = *pValue;
        e += 1;
        return;
    }
    const uint32_t nPrevSize = (uint32_t)(e - b);
    const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
    void** pNewData = nNewSize ? (void**)EANEW(nNewSize * 4) : 0;
    void** pNewEnd = UCopy(b, position, pNewData);
    if (pNewEnd) *pNewEnd = *value;
    pNewEnd = UCopy(position, e, ++pNewEnd);
    if (b && ((int*)b)[-1]) operator delete[](b);
    b = pNewData;
    e = pNewEnd;
    cap = pNewData + nNewSize;
}

// @ 0x009AB170
void VecP::DoInsertValue(RefC** position, RefC* const* value)
{
    if (e != cap) {
        RefC* const* pValue = value;
        if (value >= position && value < e)
            ++pValue;
        if (e) {
            RefC* t = e[-1];
            *e = t;
            if (t) t->AddRef();
        }
        CopyBackward(position, e - 1, e);
        RefC* s = *pValue;
        RefC* old = *position;
        if (s != old) {
            if (s) s->AddRef();
            *position = s;
            if (old) old->Release();
        }
        e += 1;
        return;
    }
    const uint32_t nPrevSize = (uint32_t)(e - b);
    const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
    RefC** pNewData = nNewSize ? (RefC**)EANEW(nNewSize * 4) : 0;
    int nBytes = (char*)position - (char*)b;
    RefC** pNewPos = (RefC**)memcpy(pNewData, b, nBytes) + (nBytes >> 2);
    if (pNewPos) { *pNewPos = *value; if (*pNewPos) (*pNewPos)->AddRef(); }
    int nBytes2 = (char*)e - (char*)position;
    ++pNewPos;
    RefC** pNewEnd = (RefC**)memcpy(pNewPos, position, nBytes2) + (nBytes2 >> 2);
    if (b && ((int*)b)[-1]) operator delete[](b);
    e = pNewEnd;
    b = pNewData;
    cap = pNewData + nNewSize;
}

// @ 0x009AB3F0
void VecP::push_back(RefC* const* v)
{
    RefC** p = e;
    if (p < cap) {
        e = p + 1;
        if (p) { *p = *v; if (*p) (*p)->AddRef(); }
    } else {
        DoInsertValue(p, v);
    }
}


// @ 0x009AAA50
struct QVal { RefB* k; RefE* v; };
NodeQ* __stdcall AllocNodeQ(const QVal* src)
{
    NodeQ* n = (NodeQ*)EANEW(0x18);
    QVal* pv = (QVal*)&n->k;
    if (pv) {
        pv->k = src->k;
        if (pv->k) pv->k->AddRef();
        pv->v = src->v;
        if (pv->v) pv->v->AddRef();
    }
    return n;
}

// @ 0x009AAC20
Iter TreeP::InsertNode(Node* pos, const Pair* v, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pos == &anchor_ || KeyLess(v->first, ((NodeP*)pos)->v.first))
        side = 0;
    else
        side = 1;
    NodeP* n = (NodeP*)EANEW(0x2c);
    if (&n->v) new (&n->v) Pair(*v);
    eastl::RBTreeInsert(n, pos, &anchor_, side);
    ++size;
    Iter r; r.n = n;
    return r;
}

// @ 0x009AACC0
IterBool TreeP::InsertUnique(const Pair* v, TagT)
{
    Node* pCurrent = anchor_.parent;
    Node* pLowerBound = &anchor_;
    Node* pParent = &anchor_;
    bool bLess = true;
    while (pCurrent) {
        pParent = pCurrent;
        bLess = KeyLess(v->first, ((NodeP*)pCurrent)->v.first);
        pCurrent = bLess ? pCurrent->left : pCurrent->right;
    }
    pLowerBound = pParent;
    if (bLess) {
        if (pParent == anchor_.left) {
            IterBool r;
            r.it = InsertNode(pParent, v, false);
            r.ok = true;
            return r;
        }
        pLowerBound = eastl::RBTreeDecrement(pParent);
    }
    if (KeyLess(((NodeP*)pLowerBound)->v.first, v->first)) {
        IterBool r;
        r.it = InsertNode(pParent, v, false);
        r.ok = true;
        return r;
    }
    IterBool r;
    r.it.n = pLowerBound;
    r.ok = false;
    return r;
}

// @ 0x009AB2C0
Iter TreeP::InsertHint(Iter position, const Pair* v, TagT)
{
    Node* pRightmost = anchor_.right;
    if (position.n != pRightmost && position.n != &anchor_) {
        Node* itNext = eastl::RBTreeIncrement(position.n);
        if (KeyLess(((NodeP*)position.n)->v.first, v->first) && Less(&v->first, &((NodeP*)itNext)->v.first)) {
            if (position.n->right)
                return InsertNode(itNext, v, true);
            return InsertNode(position.n, v, false);
        }
        return InsertUnique(v, TagT()).it;
    }
    if (size && KeyLess(((NodeP*)pRightmost)->v.first, v->first))
        return InsertNode(pRightmost, v, false);
    return InsertUnique(v, TagT()).it;
}

// @ 0x009AADB0
Iter TreeP::Erase(Iter position)
{
    Node* n = position.n;
    --size;
    position.n = eastl::RBTreeIncrement(n);
    eastl::RBTreeErase(n, &anchor_);
    NodeP* np = (NodeP*)n;
    if (np->v.second.q) np->v.second.q->Release();
    if (np->v.second.p) np->v.second.p->Release();
    if (np->v.first.p) np->v.first.p->Release();
    operator delete[](n);
    return position;
}

// @ 0x009AAE10
void TreeP::DoNuke(Node* n)
{
    while (n) {
        DoNuke(n->right);
        Node* next = n->left;
        NodeP* np = (NodeP*)n;
        if (np->v.second.q) np->v.second.q->Release();
        if (np->v.second.p) np->v.second.p->Release();
        if (np->v.first.p) np->v.first.p->Release();
        operator delete[](n);
        n = next;
    }
}

// ---- tree Q: map<RefB, RefE> ----
struct TreeQ {
    uint8_t pad0; Node anchor_;
    int size;
    Iter Erase(Iter n);
    Iter Erase2(Iter n);
    void DoNuke(Node* n);
};

// @ 0x009AAE70
Iter TreeQ::Erase(Iter position)
{
    Node* n = position.n;
    --size;
    position.n = eastl::RBTreeIncrement(n);
    eastl::RBTreeErase(n, &anchor_);
    NodeQ* nq = (NodeQ*)n;
    if (nq->v) nq->v->Release();
    if (nq->k) nq->k->Release();
    operator delete[](n);
    return position;
}

// @ 0x009AB150
Iter TreeQ::Erase2(Iter n)
{
    return Erase(n);
}

// @ 0x009AAED0
void TreeQ::DoNuke(Node* n)
{
    while (n) {
        DoNuke(n->right);
        Node* next = n->left;
        NodeQ* nq = (NodeQ*)n;
        if (nq->v) nq->v->Release();
        if (nq->k) nq->k->Release();
        operator delete[](n);
        n = next;
    }
}

// ---- Obj / frame builder ----
struct Elem { char pad[700]; };
struct Obj { char pad[0x2e4]; Elem* begin; Elem* end; };
bool __cdecl F9aa440(Obj* o, Elem* e);

// @ 0x009AA950
void __cdecl CollectBits(Obj* o, int* outCount, uint32_t* bits)
{
    bits[0] = 0; bits[1] = 0; bits[2] = 0; bits[3] = 0; bits[4] = 0; bits[5] = 0; bits[6] = 0; bits[7] = 0;
    uint32_t i = 0;
    *outCount = 0;
    int n = (int)((char*)o->end - (char*)o->begin) / 700;
    if (n > 0) {
        int off = 0;
        do {
            if (F9aa440(o, (Elem*)((char*)o->begin + off))) {
                if (i < 0xff)
                    bits[i >> 5] |= 1u << (i & 0x1f);
                ++*outCount;
            }
            off += 700;
            ++i;
        } while ((int)i < n);
    }
}

struct BakedData { char pad[0x10]; uint32_t count; };
struct Baked {
    BakedData* d;
    void Create(int n, int count, const float* rate);
    void F9ae350(int a, float b, Obj* o, void* p2);
};
void __cdecl F9a9c00(Obj* o, void* p2, float f);
void __cdecl F9aa3a0(Obj* o, void* p2, Baked* b, uint32_t n);

// @ 0x009AAAB0
void __cdecl BuildBaked(Obj* o, void* p2, Baked* b, float t, float rate)
{
    t = t * rate + 1.5f;
    int n = (int)t;
    F9a9c00(o, p2, 0.0f);
    uint32_t bits[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    CollectBits(o, (int*)&t, bits);
    float r = rate;
    b->Create(n, *(int*)&t, &r);
    b->F9ae350(0, 0.0f, o, p2);
    if (b->d && b->d->count > 1)
        F9aa3a0(o, p2, b, b->d->count - 1);
}

// ---- Mgr ----
struct TreeU {
    uint8_t pad0; Node anchor_;
    int size;
    Iter Find(const uint32_t* k);
};
struct ObjX { char pad[0x110]; int f110; };
extern uint32_t g_counter;      // 0x0166C0C8
extern VecP* g_vecP;            // 0x0166C064

struct Mgr {
    int total;
    TreeP t1;
    int pad1c;
    TreeU t2;
    int pad38;
    S4Ref s4;
    Mgr();
    int CountRefs(RefB* p);
    RefD* Add(RefB* k, ObjX* o, int v);
    void RemoveEntry(Iter* pit);
    int RemoveAll(int key, int max);
};

// @ 0x009AA820
int Mgr::CountRefs(RefB* p)
{
    int n = 0;
    uint32_t key = (uint32_t)p;
    if (p) p->AddRef();
    bool found = t2.Find(&key).n != &t2.anchor_;
    if (p) p->Release();
    if (found) n = 2;
    if (s4.p == p) ++n;
    for (Node* x = t1.anchor_.left; x != &t1.anchor_; x = eastl::RBTreeIncrement(x))
        if (((NodeP*)x)->v.first.p == p) ++n;
    return n;
}

// @ 0x009AA8A0
RefD* Mgr::Add(RefB* k, ObjX* o, int v)
{
    S4 key;
    key.p = 0;
    if (k) { k->AddRef(); key.p = k; }
    RefB* held = key.p;
    key.a = (uint32_t)o;
    key.b = o ? o->f110 : 0;
    key.c = v;
    Iter it = t1.Find(&key);
    if (it.n != &t1.anchor_) {
        NodeP* n = (NodeP*)it.n;
        RefD* const& qq = n->v.second.q;
        qq->stamp = g_counter;
        ++g_counter;
        RefD* r = qq;
        if (held) held->Release();
        return r;
    }
    if (held) held->Release();
    return 0;
}

// @ 0x009AB430
Mgr::Mgr()
{
    t1.pad0 = 0;
    t1.anchor_.left = 0; t1.anchor_.parent = 0; t1.anchor_.color = 0;
    t1.anchor_.right = &t1.anchor_;
    t1.anchor_.left = &t1.anchor_;
    t1.anchor_.parent = 0;
    *(uint8_t*)&t1.anchor_.color = 0;
    t1.size = 0;
    t2.anchor_.left = 0; t2.anchor_.parent = 0; t2.anchor_.color = 0;
    t2.anchor_.right = &t2.anchor_;
    t2.anchor_.left = &t2.anchor_;
    t2.anchor_.parent = 0;
    *(uint8_t*)&t2.anchor_.color = 0;
    t2.size = 0;
    s4.p = 0; s4.a = 0; s4.b = 0; s4.c = 0;
    total = 0;
}

// @ 0x009AB4A0
void Mgr::RemoveEntry(Iter* pit)
{
    NodeP* n = (NodeP*)pit->n;
    if (n->v.second.p) {
        n->v.second.p->Fn(0);
        if (g_vecP) g_vecP->push_back(&((NodeP*)pit->n)->v.second.p);
        n = (NodeP*)pit->n;
        RefC* c = n->v.second.p;
        if (c) { n->v.second.p = 0; c->Release(); }
    }
    n = (NodeP*)pit->n;
    if (n->v.second.q && n->v.second.q->z)
        total -= n->v.second.q->z->size;
    n = (NodeP*)pit->n;
    RefD* d = n->v.second.q;
    if (d) { n->v.second.q = 0; d->Release(); }
}

// @ 0x009AB540
int Mgr::RemoveAll(int key, int max)
{
    int n = 0;
    if (max == 0) return 0;
    if (s4.a == (uint32_t)key) {
        S4Ref tmp; tmp.p = 0; tmp.a = 0; tmp.b = 0; tmp.c = 0;
        s4 = tmp;
    }
    Iter it; it.n = t1.anchor_.left;
    if (it.n != &t1.anchor_) {
        do {
            if (((NodeP*)it.n)->v.first.a == (uint32_t)key) {
                Node* cur = it.n;
                RemoveEntry(&it);
                --t1.size;
                Node* next = eastl::RBTreeIncrement(cur);
                eastl::RBTreeErase(cur, &t1.anchor_);
                NodeP* np = (NodeP*)cur;
                if (np->v.second.q) np->v.second.q->Release();
                if (np->v.second.p) np->v.second.p->Release();
                if (np->v.first.p) np->v.first.p->Release();
                operator delete[](cur);
                ++n;
                it.n = next;
                if (n == max) return n;
            } else {
                it.n = eastl::RBTreeIncrement(it.n);
            }
        } while (it.n != &t1.anchor_);
    }
    return n;
}
