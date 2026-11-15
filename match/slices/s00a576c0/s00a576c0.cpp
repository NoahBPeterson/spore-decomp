// slice s00a576c0 -- SPAudio EAPd "collread"/"collwrite" externals + coll hash table helpers.
// Object file: SPAudio/eapdinstance.obj.  Compile: /O2 /MD /Gy /EHsc /TP /arch:SSE
//
// All offsets below are the retail (whole-program) layouts; the message handlers registered
// with class_addmethod take the symbol by value (two stack slots), so their argc/argv live in
// the 4th/5th argument slots.
#include "types.h"
#include <string.h>

namespace EA {
namespace Audio {
namespace Eapd {

struct t_symbol { uint32_t mHash; const char* mpName; };   // 8 bytes

// Hash-table node: five key dwords, then the payload (count + item pointer) and the chain link.
struct CollNode {
    uint32_t  k0;          // +0x00
    uint32_t  k1;          // +0x04
    uint32_t  type;        // +0x08
    uint32_t  value;       // +0x0c
    uint32_t  sym;         // +0x10
    int32_t   count;       // +0x14
    uint32_t* items;       // +0x18
    CollNode* next;        // +0x1c
};

struct Pair { CollNode* node; CollNode** bucket; };
struct InsResult { CollNode* node; CollNode** bucket; bool ok; };

// Doubly linked ring used by the object's ordered list (next +0, prev +4).
struct RingNode {
    RingNode* next;        // +0x00
    RingNode* prev;        // +0x04
};
struct ListItem : RingNode {
    uint32_t type;         // +0x08
    uint32_t value;        // +0x0c
    uint32_t sym;          // +0x10
};

// Outlet list object: head link lives at +8; each node is { next, target }.
struct OutletNode { OutletNode* next; void* target; };
struct OutletList { uint8_t pad[8]; OutletNode* head; };

struct RehashResult { uint8_t grow; uint8_t pad[3]; uint32_t count; };

// Hash-table growth policy sub-object, embedded at table+0x10.
class HashPolicy {
public:
    uint8_t pad[0x18];
    void Rehash(RehashResult* out, unsigned buckets, unsigned elems, int flag);  // 0x921440
};

// ---- external EAPd helpers (real names from the dev PDB) ----------------
void*  pd_new(void* cls);                                        // 0xa49390
void*  outlet_new(void* x, uint32_t s1, uint32_t s2);            // 0xa49d30
void   outlet_list(void* x, uint32_t s1, uint32_t s2, int argc, void* argv);  // 0xa49e40
void   outlet_float(void* x, float f);                           // 0xa49570
void   outlet_symbol(void* x, uint32_t a, uint32_t b);           // 0xa49df0
void*  pd_findbyclass(unsigned a, unsigned b, unsigned c);       // 0xa671f0
int    atom_getint(void* a, void* out);                          // 0xa46770
t_symbol* gensym(t_symbol* out, const char* s);                  // 0xa675f0
void*  class_new(uint32_t h, uint32_t n, void* fn, int a, int b, int c, int d, int e);  // 0xa48ea0
bool   class_addmethod(void* c, void* fn, uint32_t h, uint32_t n, int a1, int a2);   // 0xa48a80
bool   class_doaddfloat(void* c, void* fn);                      // 0xa47f30
bool   class_addsymbol(void* c, void* fn);                       // 0xa47f50
unsigned Fn921340(unsigned n);                                   // 0x921340

extern t_symbol  gListSymbol;        // 0x16758ac
extern t_symbol  gListSender;        // 0x16758b0
extern int       gOutletCount;       // 0x167545c
extern uint32_t  gCollReadClass;     // 0x1675610
extern uint32_t  gCollWriteClass;    // 0x167561c
extern uint32_t  gCollClass;         // 0x16755f4

// ---- fixed-pool allocator ----------------------------------------------
class CollIAlloc {
public:
    virtual void  v0();
    virtual void  v1();
    virtual void* Alloc(unsigned size);     // vtable +0x08
    virtual void  Free(void* p);            // vtable +0x0c
};

class FixedPool {
public:
    bool Init(unsigned size, int count, void* a, void* b);   // 0xa53210, thiscall, ret 0x10
};

class CollPool : public CollIAlloc {
public:
    uint8_t  pad04[0x2c];
    unsigned mSize;                        // +0x30
    void*    mBuf;                         // +0x34
    bool Init(int count, void* a, void* b);                     // 0xa57750
};

class CollTable {
public:
    uint32_t   pad0;                       // +0x00
    CollNode** mBuckets;                   // +0x04
    uint32_t   mBucketCount;               // +0x08
    uint32_t   mElems;                     // +0x0c
    HashPolicy mPolicy;                    // +0x10
    CollIAlloc mAlloc;                     // +0x28
    uint8_t    pad2c[8];                   // +0x2c
    uint32_t   mElemSize;                  // +0x34
    CollNode*  mBegin;                     // +0x38
    CollNode*  mEnd;                       // +0x3c
    CollNode*  mFree;                      // +0x40
    uint32_t   mCount;                     // +0x44
    uint32_t   mHigh;                      // +0x48
    uint32_t   mSpecialDwords;             // +0x4c
    CollNode*  mSpecial;                   // +0x50

    __forceinline unsigned HashOf(CollNode* n)
    {
        switch (n->type) {
        case 1:  return n->value & 0x7fffffff;
        case 2:  return n->value;
        default: return 0;
        }
    }
    void      FreeChains(unsigned count);                       // 0xa57900
    CollNode** NewBuckets(unsigned count);                      // 0xa57880
    CollNode* Find(CollNode* head, CollNode* key, unsigned h);  // 0xa579d0
    Pair*     Lookup(Pair* out, CollNode* key);                 // 0xa57a20
    CollNode* AllocNode(CollNode* src);                         // 0xa57aa0
    void      FreeList(CollNode** v, unsigned n);               // 0xa57af0
    Pair*     EraseNode(Pair* out, CollNode* key, CollNode** bucket);  // 0xa583e0
    InsResult* InsertIns(InsResult* out, CollNode* key, unsigned unused);  // 0xa58480
};

// The coll object: its table starts at object+0x180 (receiver `this` at object+0x30, so the
// table is at receiver+0x150); the ordered ring is at object+0x1d4 (receiver+0x1a4) and the
// two outlet chains at object+0x1e8 / +0x1ec (receiver+0x1b8 / +0x1bc).
struct CollRecv {
    uint8_t    pad0[0x150];
    CollTable  mTable;                     // +0x150
    RingNode   mSentinel;                  // +0x1a4
    uint8_t    pad2[0x1b8 - 0x1a4 - sizeof(RingNode)];
    OutletList* mOutlets;                  // +0x1b8
    void*      mOutlets2;                  // +0x1bc

    bool LookupKey(uint32_t a0, uint32_t a1, uint32_t a2, int* outA, int* outB);      // 0xa57b60
    bool LookupIndex(uint32_t a0, uint32_t a1, uint32_t a2, int idx, void* out);      // 0xa57be0
};

struct CollObject {
    uint8_t   pad0[0x28];
    uint32_t  mKeyA;                       // +0x28
    uint32_t  mKeyB;                       // +0x2c
};

struct CollLess {
    CollRecv* recv;                        // +0
    int       index;                       // +4
    int       swap;                        // +8
    bool Less(CollNode* a, CollNode* b);   // 0xa58570
};

// @ 0x00a576c0
CollObject* CollReadNew(unsigned a, unsigned b)
{
    CollObject* x = (CollObject*)pd_new((void*)gCollReadClass);
    if (x) {
        x->mKeyA = a;
        x->mKeyB = b;
        outlet_new(x, gListSymbol.mHash, gListSender.mHash);
    }
    return x;
}

// @ 0x00a57700
void CollWriteNew(unsigned a, unsigned b)
{
    CollObject* x = (CollObject*)pd_new((void*)gCollWriteClass);
    if (x) {
        x->mKeyA = a;
        x->mKeyB = b;
    }
}

// @ 0x00a57730
void CollSetKey(CollObject* x, unsigned a, unsigned b)
{
    x->mKeyA = a;
    x->mKeyB = b;
}

// @ 0x00a57750
bool CollPool::Init(int count, void* a, void* b)
{
    if (mBuf) {
        Free(mBuf);
        mBuf = 0;
    }
    unsigned n = (unsigned)((float)count * 1.3333334f);
    if (n < 3)
        mSize = 3;
    else
        mSize = Fn921340(n) + 1;
    if (mSize * 4 == 0x20)
        return ((FixedPool*)this)->Init(0x20, count + 1, a, b);
    if (!((FixedPool*)this)->Init(0x20, count, a, b))
        return false;
    mBuf = Alloc(mSize * 4);
    return mBuf != 0;
}

// @ 0x00a57840
void __stdcall SpliceNodes(RingNode* a, RingNode* b, RingNode* c, RingNode* d)
{
    (void)b;
    if (c != d) {
        RingNode* A = d->prev;
        RingNode* B = A->next;
        RingNode* C = c->prev;
        B->prev = C;
        C->next = B;
        RingNode* E = a->prev;
        E->next = c;
        c->prev = E;
        A->next = a;
        a->prev = A;
    }
}

// @ 0x00a57880
CollNode** CollTable::NewBuckets(unsigned count)
{
    unsigned bytes = count * 4;
    CollNode** p = 0;
    if (bytes + 4 == 0x20) {
        p = (CollNode**)mFree;
        if (p) {
            mFree = *p;
        } else {
            p = (CollNode**)mAlloc.Alloc(mElemSize);
        }
        if (p) {
            ++mCount;
            if (mCount > mHigh)
                mHigh = mCount;
        }
    } else if (bytes + 4 == mSpecialDwords * 4) {
        p = (CollNode**)mSpecial;
    }
    memset(p, 0, bytes);
    ((uint32_t*)p)[count] = 0xffffffff;
    return p;
}

// @ 0x00a57900
void CollTable::FreeChains(unsigned count)
{
    CollNode** tmp = NewBuckets(count);
    for (unsigned i = 0; i < mBucketCount; ++i) {
        while (mBuckets[i]) {
            CollNode* node = mBuckets[i];
            mBuckets[i] = node->next;
            unsigned h = HashOf(node);
            node->next = tmp[h % count];
            tmp[h % count] = node;
        }
    }
    CollNode** old = mBuckets;
    if (mBucketCount > 1 && old != (CollNode**)mSpecial) {
        --mCount;
        if (old >= (CollNode**)mBegin && old < (CollNode**)mEnd) {
            *(CollNode**)old = mFree;
            mFree = (CollNode*)old;
        } else {
            mAlloc.Free(old);
        }
    }
    mBuckets = tmp;
    mBucketCount = count;
}

// @ 0x00a579d0
CollNode* CollTable::Find(CollNode* head, CollNode* key, unsigned h)
{
    (void)h;
    if (head) {
        do {
            if (key->type == head->type) {
                if (key->type == 1) {
                    if (*(float*)&key->value == *(float*)&head->value)
                        return head;
                } else if (key->type == 2 && key->value == head->value) {
                    return head;
                }
            }
            head = head->next;
        } while (head);
    }
    return 0;
}

// @ 0x00a57a20
Pair* CollTable::Lookup(Pair* out, CollNode* key)
{
    unsigned h = HashOf(key);
    unsigned b = h % mBucketCount;
    CollNode** bp = mBuckets + b;
    CollNode* n = Find(*bp, key, h);
    if (n) {
        out->node = n;
        out->bucket = bp;
    } else {
        out->node = mBuckets[mBucketCount];
        out->bucket = mBuckets + mBucketCount;
    }
    return out;
}

// @ 0x00a57aa0
CollNode* CollTable::AllocNode(CollNode* src)
{
    CollNode* p = mFree;
    if (p)
        mFree = *(CollNode**)p;
    else
        p = (CollNode*)mAlloc.Alloc(mElemSize);
    if (p) {
        ++mCount;
        if (mCount > mHigh)
            mHigh = mCount;
        p->k0 = src->k0;
        p->k1 = src->k1;
        p->type = src->type;
        p->value = src->value;
        p->sym = src->sym;
        p->count = src->count;
        p->items = src->items;
    }
    p->next = 0;
    return p;
}

// @ 0x00a57af0
void CollTable::FreeList(CollNode** v, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        CollNode* node = v[i];
        while (node) {
            CollNode* cur = node;
            node = cur->next;
            if (cur != mSpecial) {
                --mCount;
                if (cur < mBegin || cur >= mEnd) {
                    mAlloc.Free(cur);
                } else {
                    *(CollNode**)cur = mFree;
                    mFree = cur;
                }
            }
        }
        v[i] = 0;
    }
}

// @ 0x00a57b60
bool CollRecv::LookupKey(uint32_t a0, uint32_t a1, uint32_t a2, int* outA, int* outB)
{
    CollNode key;
    key.k0 = 0;
    key.k1 = 0;
    key.type = a0;
    key.value = a1;
    key.sym = a2;
    Pair p;
    mTable.Lookup(&p, &key);
    if (mTable.mBuckets[mTable.mBucketCount] != p.node) {
        *outA = p.node->count;
        *outB = (int)p.node->items;
        return true;
    }
    return false;
}

// @ 0x00a57be0
bool CollRecv::LookupIndex(uint32_t a0, uint32_t a1, uint32_t a2, int idx, void* out)
{
    int count;
    int items;
    if (!LookupKey(a0, a1, a2, &count, &items))
        return false;
    if (idx <= 0)
        return false;
    if (idx > count)
        return false;
    uint32_t* src = (uint32_t*)items + (idx - 1) * 3;
    ((uint32_t*)out)[0] = src[0];
    ((uint32_t*)out)[1] = src[1];
    ((uint32_t*)out)[2] = src[2];
    return true;
}

// @ 0x00a57c60
void Float_(void* x, float f, uint32_t b)
{
    CollRecv* r = (CollRecv*)((char*)x + 0x30);
    uint32_t fbits = *(uint32_t*)&f;
    uint32_t unused;
    uint32_t u = *(volatile uint32_t*)&unused;
    int outA, outB;
    if (r->LookupKey(1, fbits, u, &outA, &outB)) {
        if (++gOutletCount < 1000) {
            for (OutletNode* n = r->mOutlets->head; n; n = n->next)
                outlet_float(n->target, f);
        }
        --gOutletCount;
        outlet_list(r->mOutlets2, gListSymbol.mHash, gListSender.mHash, outA, (void*)outB);
    }
}

// @ 0x00a57d20
void Symbol_(void* x, uint32_t a, uint32_t b)
{
    CollRecv* r = (CollRecv*)((char*)x + 0x30);
    int outA, outB;
    if (r->LookupKey(2, a, b, &outA, &outB)) {
        outlet_symbol(r->mOutlets, a, b);
        outlet_list(r->mOutlets2, gListSymbol.mHash, gListSender.mHash, outA, (void*)outB);
    }
}

// @ 0x00a57da0
void List_(void* x, t_symbol s, int argc, void* atoms)
{
    (void)s;
    CollRecv* r = (CollRecv*)((char*)x + 0x30);
    if (argc == 0) {
        ++gOutletCount;
        if (gOutletCount < 1000) {
            OutletNode* n = ((OutletList*)r->mOutlets2)->head;
            if (n) {
                float v = (float)(int)r->mTable.mElems;
                do {
                    outlet_float(n->target, v);
                    n = n->next;
                } while (n);
            }
        }
        --gOutletCount;
        return;
    }
    if (argc != 1)
        return;
    int local;
    uint32_t* a = (uint32_t*)atoms;
    if (r->LookupKey(a[0], a[1], a[2], &argc, &local)) {
        float v = (float)argc;
        ++gOutletCount;
        if (gOutletCount < 1000) {
            OutletNode* n = ((OutletList*)r->mOutlets2)->head;
            if (n) {
                do {
                    outlet_float(n->target, v);
                    n = n->next;
                } while (n);
            }
        }
        --gOutletCount;
    }
}

// @ 0x00a57ea0
void DoInt(void* x, t_symbol s, int argc, void* atoms)
{
    (void)s;
    if (argc != 2)
        return;
    CollRecv* r = (CollRecv*)((char*)x + 0x30);
    uint32_t* a = (uint32_t*)atoms;
    uint32_t buf[3];
    int idx = atom_getint((char*)atoms + 0xc, buf);
    if (r->LookupIndex(a[0], a[1], a[2], idx, buf))
        outlet_list(r->mOutlets2, gListSymbol.mHash, gListSender.mHash, 1, buf);
}

// @ 0x00a57f20
void Output(void* x)
{
    CollRecv* r = (CollRecv*)((char*)x + 0x30);
    RingNode* sentinel = &r->mSentinel;
    ListItem* n = (ListItem*)sentinel->next;
    while (n != (ListItem*)sentinel) {
        if (n->type == 2) {
            outlet_symbol(r->mOutlets, n->value, n->sym);
        } else {
            float v = *(float*)&n->value;
            ++gOutletCount;
            if (gOutletCount < 1000) {
                for (OutletNode* o = r->mOutlets->head; o; o = o->next)
                    outlet_float(o->target, v);
            }
            --gOutletCount;
        }
        CollNode key;
        key.k0 = 0;
        key.k1 = 0;
        key.type = n->type;
        key.value = n->value;
        key.sym = n->sym;
        int outA = 0, outB = 0;
        r->LookupKey(n->type, n->value, n->sym, &outA, &outB);
        outlet_list(r->mOutlets2, gListSymbol.mHash, gListSender.mHash, outA, (void*)outB);
        n = (ListItem*)n->next;
    }
}

// @ 0x00a58040
void PdFloat_(void* x, float f)
{
    void* o = pd_findbyclass(*(uint32_t*)((char*)x + 0x28),
                             *(uint32_t*)((char*)x + 0x2c), gCollClass);
    if (o) {
        CollRecv* r = (CollRecv*)((char*)o + 0x30);
        uint32_t fbits = *(uint32_t*)&f;
        uint32_t unused;
        uint32_t u = *(volatile uint32_t*)&unused;
        int outA = 0, outB = 0;
        if (r->LookupKey(1, fbits, u, &outA, &outB))
            outlet_list(*(void**)((char*)x + 0xc), gListSymbol.mHash,
                        gListSender.mHash, outA, (void*)outB);
    }
}

// @ 0x00a580d0
void PdSymbol_(void* x, uint32_t a, uint32_t b)
{
    void* o = pd_findbyclass(*(uint32_t*)((char*)x + 0x28),
                             *(uint32_t*)((char*)x + 0x2c), gCollClass);
    if (o) {
        CollRecv* r = (CollRecv*)((char*)o + 0x30);
        int outA = 0, outB = 0;
        if (r->LookupKey(2, a, b, &outA, &outB))
            outlet_list(*(void**)((char*)x + 0xc), gListSymbol.mHash,
                        gListSender.mHash, outA, (void*)outB);
    }
}

// @ 0x00a58150
void PdLength(void* x, t_symbol s, int argc, void* atoms)
{
    (void)s;
    void* o = pd_findbyclass(*(uint32_t*)((char*)x + 0x28),
                             *(uint32_t*)((char*)x + 0x2c), gCollClass);
    if (!o)
        return;
    OutletList* ol = *(OutletList**)((char*)x + 0xc);
    if (argc == 0) {
        ++gOutletCount;
        if (gOutletCount < 1000 && ol) {
            float v = (float)*(int*)((char*)o + 0x18c);
            for (OutletNode* n = ol->head; n; n = n->next)
                outlet_float(n->target, v);
        }
        --gOutletCount;
        return;
    }
    if (argc != 1)
        return;
    CollRecv* r = (CollRecv*)((char*)o + 0x30);
    uint32_t* a = (uint32_t*)atoms;
    int count = 0, items = 0;
    if (r->LookupKey(a[0], a[1], a[2], &count, &items)) {
        ++gOutletCount;
        if (gOutletCount < 1000 && ol) {
            float v = (float)count;
            for (OutletNode* n = ol->head; n; n = n->next)
                outlet_float(n->target, v);
        }
        --gOutletCount;
    }
}

// @ 0x00a58260
void PdNth(void* x, t_symbol s, int argc, void* atoms)
{
    (void)s;
    if (argc != 2)
        return;
    void* o = pd_findbyclass(*(uint32_t*)((char*)x + 0x28),
                             *(uint32_t*)((char*)x + 0x2c), gCollClass);
    if (!o)
        return;
    CollRecv* r = (CollRecv*)((char*)o + 0x30);
    uint32_t* a = (uint32_t*)atoms;
    uint32_t buf[3];
    int idx = atom_getint((char*)atoms + 0xc, buf);
    if (r->LookupIndex(a[0], a[1], a[2], idx, buf))
        outlet_list(*(void**)((char*)x + 0xc), gListSymbol.mHash,
                    gListSender.mHash, 1, buf);
}

// @ 0x00a582f0
bool CollReadClassNew()
{
    t_symbol s;
    t_symbol* p = gensym(&s, "collread");
    uint32_t cls = (uint32_t)class_new(p->mHash, (uint32_t)p->mpName,
                                       (void*)0xa576c0, 0, 0x30, 0, 6, 0);
    gCollReadClass = cls;
    bool ok = cls != 0;
    ok &= class_doaddfloat((void*)gCollReadClass, (void*)0xa58040);
    ok &= class_addsymbol((void*)gCollReadClass, (void*)0xa580d0);
    p = gensym(&s, "length");
    ok &= class_addmethod((void*)gCollReadClass, (void*)0xa58150,
                          p->mHash, (uint32_t)p->mpName, 9, 0);
    p = gensym(&s, "nth");
    ok &= class_addmethod((void*)gCollReadClass, (void*)0xa58260,
                          p->mHash, (uint32_t)p->mpName, 9, 0);
    p = gensym(&s, "set");
    ok &= class_addmethod((void*)gCollReadClass, (void*)0xa57730,
                          p->mHash, (uint32_t)p->mpName, 2, 0);
    return ok;
}

// @ 0x00a583e0
Pair* CollTable::EraseNode(Pair* out, CollNode* key, CollNode** bucket)
{
    CollNode* n = key->next;
    out->bucket = bucket;
    out->node = n;
    while (!n) {
        ++bucket;
        n = *bucket;
        out->node = n;
    }
    CollNode* head = *bucket;
    if (head == key) {
        *bucket = head->next;
    } else {
        CollNode* prev = head;
        CollNode* cur = head->next;
        while (cur != key) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = cur->next;
    }
    if (key != mSpecial) {
        --mCount;
        if (key >= mBegin && key < mEnd) {
            *(CollNode**)key = mFree;
            mFree = key;
            --mElems;
            return out;
        }
        mAlloc.Free(key);
    }
    --mElems;
    return out;
}

// @ 0x00a58480
InsResult* CollTable::InsertIns(InsResult* out, CollNode* key, unsigned unused)
{
    (void)unused;
    unsigned h = HashOf(key);
    unsigned b = h % mBucketCount;
    CollNode** bp = mBuckets + b;
    CollNode* found = Find(*bp, key, h);
    if (found) {
        out->node = found;
        out->bucket = bp;
        out->ok = false;
        return out;
    }
    RehashResult rr;
    mPolicy.Rehash(&rr, mBucketCount, mElems, 1);
    CollNode* node = AllocNode(key);
    if (rr.grow) {
        b = h % rr.count;
        FreeChains(rr.count);
    }
    node->next = mBuckets[b];
    mBuckets[b] = node;
    ++mElems;
    out->node = node;
    out->bucket = mBuckets + b;
    out->ok = true;
    return out;
}

// @ 0x00a58570
bool CollLess::Less(CollNode* a, CollNode* b)
{
    CollNode* x = b;
    CollNode* y = a;
    if (swap != 0) {
        x = a;
        y = b;
    }
    int keyType, keyA, keyB;
    int keyType2, keyA2, keyB2;
    if (index < 1) {
        keyType  = y->type;
        keyA     = y->value;
        keyB     = y->sym;
        keyType2 = x->type;
        keyA2    = x->value;
        keyB2    = x->sym;
    } else {
        keyType = 0; keyA = 0; keyB = 0;
        recv->LookupIndex(y->type, y->value, y->sym, index, &keyType);
        keyType2 = 0; keyA2 = 0; keyB2 = 0;
        recv->LookupIndex(x->type, x->value, x->sym, index, &keyType2);
    }
    if (keyType != keyType2 || keyType == 0)
        return keyType2 < keyType;
    if (keyType == 1)
        return *(float*)&keyA < *(float*)&keyA2;
    if (keyType != 2)
        return false;
    const char* s = (const char*)keyB;
    const char* t = (const char*)keyB2;
    for (;;) {
        unsigned char c1 = (unsigned char)*s;
        unsigned char c2 = (unsigned char)*t;
        if (c1 != c2)
            return c1 < c2;
        if (c1 == 0)
            return false;
        ++s; ++t;
    }
}

} // namespace Eapd
} // namespace Audio
} // namespace EA
