// slice s00a576c0 -- SPAudio EAPd "collread"/"collwrite" externals + coll hash table helpers.
// Object file: SPAudio/eapdinstance.obj.  Compile: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

namespace EA {
namespace Audio {
namespace Eapd {

struct t_symbol { uint32_t mHash; const char* mpName; };   // 8 bytes

struct CollHead { uint32_t w[7]; };          // 28 bytes
struct CollNode {
    CollHead  head;                         // +0x00 .. +0x1b
    CollNode* mNext;                        // +0x1c
};

struct Pair { CollNode* node; CollNode** bucket; };
struct InsResult { CollNode* node; CollNode** bucket; bool ok; };

// ---- external EAPd helpers (real names from the dev PDB) ----------------
void* pd_new(void* cls);                                        // 0xa49390 cdecl
void* outlet_new(void* x, uint32_t s1, uint32_t s2);            // 0xa49d30 cdecl (ret: 3 dwords)
void  outlet_list(void* x, uint32_t s1, uint32_t s2, int argc, void* argv);  // 0xa49e40 cdecl
void  outlet_float(void* x, float f);                           // 0xa49570 cdecl
void  outlet_symbol(void* x, uint32_t a, uint32_t b);           // 0xa49df0 cdecl
void* pd_findbyclass(unsigned a, unsigned b, unsigned c);       // 0xa671f0 cdecl
void  atom_getint(void* a, void* out);                          // 0xa46770 cdecl
t_symbol* gensym(t_symbol* out, const char* s);                 // 0xa675f0 cdecl
void* class_new(uint32_t s1, uint32_t s2, void* fn, int a, int b, int c, int d, int e);  // 0xa48ea0 cdecl
bool  class_addmethod(void* c, void* fn, uint32_t s1, uint32_t s2, int a1, int a2);   // 0xa48a80 cdecl
bool  class_doaddfloat(void* c, void* fn);                      // 0xa47f30 cdecl
bool  class_addsymbol(void* c, void* fn);                       // 0xa47f50 cdecl
int   Fn921340(unsigned n);                                     // 0x921340 cdecl
void  Fn921440(void* out, unsigned a, unsigned b, int c);       // 0x921440 cdecl
void* FnA57880(unsigned count);                                 // 0xa57880 cdecl
bool  FixedPoolInit(void* self, unsigned size, unsigned count, void* a, void* b);  // 0xa53210 thiscall ret 0x10

extern t_symbol gListSymbol;         // 0x16758ac
extern t_symbol gListSender;         // 0x16758b0
extern int      gOutletCount;        // 0x167545c
extern uint32_t gCollReadClass;      // 0x1675610
extern uint32_t gCollWriteClass;     // 0x167561c
extern uint32_t gCollClass;          // 0x16755f4

// ---- coll hash table / fixed pool --------------------------------------
class CollIAlloc {
public:
    virtual void  v0();
    virtual void  v1();
    virtual void* Alloc(unsigned size);     // +0x08
    virtual void  Free(void* p);            // +0x0c
};
class CollPool {
public:
    CollIAlloc  mAlloc;                     // +0x00
    char        pad04[0x30 - 4];
    unsigned    mSize;                      // +0x30
    void*       mBuf;                       // +0x34
    bool Init(int count, void* a, void* b); // va 0xa57750 (ret 0xc)
};
class CollTable {
public:
    unsigned    pad0;
    CollNode**  mBuckets;                   // +0x04
    unsigned    mBucketCount;               // +0x08
    unsigned    mElems;                     // +0x0c
    char        pad10[0x28 - 0x10];
    CollIAlloc  mAlloc;                     // +0x28
    char        pad2c[0x34 - 0x2c];
    unsigned    mElemSize;                  // +0x34
    CollNode*   mBegin;                     // +0x38
    CollNode*   mEnd;                       // +0x3c
    CollNode*   mFree;                      // +0x40
    unsigned    mCount;                     // +0x44
    unsigned    mHigh;                      // +0x48
    char        pad4c[4];
    CollNode*   mSpecial;                   // +0x50

    unsigned HashOf(CollNode* n)
    {
        uint32_t t = *(uint32_t*)((char*)n + 8);
        if (t == 1) return *(uint32_t*)((char*)n + 0xc) & 0x7fffffff;
        if (t == 2) return *(uint32_t*)((char*)n + 0xc);
        return 0;
    }
    void     FreeChains(unsigned count);    // va 0xa57900
    CollNode* Find(CollNode* head, CollNode* key, unsigned h);  // va 0xa579d0
    Pair*     Lookup(Pair* out, CollNode* key);                 // va 0xa57a20
    CollNode* AllocNode(CollNode* src);                         // va 0xa57aa0
    void     FreeList(CollNode** v, unsigned n);                // va 0xa57af0
    Pair*     EraseNode(Pair* out, CollNode* key, CollNode** bucket);   // va 0xa583e0
    InsResult* InsertIns(InsResult* out, CollNode* key);        // va 0xa58480
};

struct CollObject {
    char     pad0[0x28];
    uint32_t mKeyA;                         // +0x28
    uint32_t mKeyB;                         // +0x2c
    char     pad30[0x1d4 - 0x30];
    CollNode* mSentinel;                    // +0x1d4 (cring list)
};
struct GColl {
    char pad0[0x30];
    CollTable mTable;                       // +0x30
};

} // namespace Eapd
} // namespace Audio
} // namespace EA

namespace EA { namespace Audio { namespace Eapd {

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
        mAlloc.Free(mBuf);
        mBuf = 0;
    }
    unsigned n = (unsigned)((float)(unsigned)count * 1.3333334f);
    if (n < 3) {
        mSize = 3;
    } else {
        mSize = Fn921340(n) + 1;
    }
    if (mSize * 4 == 0x20)
        return FixedPoolInit(this, 0x20, count + 1, a, b);
    if (!FixedPoolInit(this, 0x20, count, a, b))
        return false;
    mBuf = mAlloc.Alloc(mSize * 4);
    return mBuf != 0;
}

// @ 0x00a57840
void SpliceNodes(CollNode* a, CollNode* b, CollNode* c, CollNode* d)
{
    (void)b;
    if (c != d) {
        CollNode* p = d->mNext;
        p->mNext->mNext = c->mNext;
        c->mNext->mNext = p->mNext;
        CollNode* q = a->mNext;
        q->mNext = c;
        c->mNext = q;
        p->mNext = a;
        a->mNext = p;
    }
}

// @ 0x00a57900
void CollTable::FreeChains(unsigned count)
{
    CollNode** tmp = (CollNode**)FnA57880(count);
    unsigned i = 0;
    if (mBucketCount) {
        do {
            CollNode* node = mBuckets[i];
            while (node) {
                unsigned h = HashOf(node);
                node = node->mNext;
                node->mNext = tmp[h % count];
                tmp[h % count] = node;
                node = mBuckets[i];
            }
            ++i;
        } while (i < mBucketCount);
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
        unsigned t = *(unsigned*)((char*)key + 8);
        do {
            if (t == *(unsigned*)((char*)head + 8)) {
                if (t == 1) {
                    if (*(float*)((char*)key + 0xc) == *(float*)((char*)head + 0xc))
                        return head;
                } else if (t == 2 && *(unsigned*)((char*)key + 0xc) == *(unsigned*)((char*)head + 0xc)) {
                    return head;
                }
            }
            head = head->mNext;
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
        mFree = p->mNext;
    else
        p = (CollNode*)mAlloc.Alloc(mElemSize);
    if (p) {
        ++mCount;
        if (mCount > mHigh)
            mHigh = mCount;
        p->head = src->head;
    }
    p->mNext = 0;
    return p;
}

// @ 0x00a57af0
void CollTable::FreeList(CollNode** v, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        CollNode* node = v[i];
        while (node) {
            CollNode* cur = node;
            node = node->mNext;
            if (cur != mSpecial) {
                --mCount;
                if (cur < mBegin || cur >= mEnd) {
                    mAlloc.Free(cur);
                } else {
                    cur->mNext = mFree;
                    mFree = cur;
                }
            }
        }
        v[i] = 0;
    }
}

// ---- coll object method receiver (this = outer object + 0x30) ----------
// Outer object (+0x28/+0x2c pd key, +0x180 table, +0x1d4 sentinel list,
//                +0x18c count, +0x1e8/+0x1ec outlet targets)
struct CollRecv {
    char       pad0[0x150];
    CollTable  mTable;                      // +0x150 (outer +0x180)
    CollNode*  mSentinel;                   // +0x1a4 (outer +0x1d4)
    char       pad2[0x1b8 - 0x1a4 - 4];
    void*      mOutlets;                    // +0x1b8 (outer +0x1e8)
    void*      mOutlets2;                   // +0x1bc (outer +0x1ec)

    bool  LookupKey(unsigned a0, unsigned a1, unsigned a2, int* outA, int* outB);  // va 0xa57b60
    bool  LookupIndex(unsigned a0, unsigned a1, unsigned a2, int idx, void* out);  // va 0xa57be0
};

struct CollLess {
    CollRecv* recv;                         // +0
    int       index;                        // +4
    int       swap;                         // +8
    bool Less(CollNode* a, CollNode* b);    // va 0xa58570
};

// @ 0x00a57b60
bool CollRecv::LookupKey(unsigned a0, unsigned a1, unsigned a2, int* outA, int* outB)
{
    CollTable* t = &mTable;
    CollNode key;
    *(uint32_t*)((char*)&key + 0) = 0;
    *(uint32_t*)((char*)&key + 4) = 0;
    *(uint32_t*)((char*)&key + 8) = a0;
    *(uint32_t*)((char*)&key + 0xc) = a1;
    *(uint32_t*)((char*)&key + 0x10) = a2;
    Pair local;
    t->Lookup(&local, &key);
    if (t->mBuckets[t->mBucketCount] != local.node) {
        *outA = *(int*)((char*)local.node + 0x14);
        *outB = *(int*)((char*)local.node + 0x18);
        return true;
    }
    return false;
}

// @ 0x00a57be0
bool CollRecv::LookupIndex(unsigned a0, unsigned a1, unsigned a2, int idx, void* out)
{
    CollNode* node;
    CollNode** bucket;
    if (!LookupKey(a0, a1, a2, (int*)&node, (int*)&bucket))
        return false;
    if (idx <= 0)
        return false;
    if (*(int*)&node < idx)
        return false;
    int i = (idx - 1) * 3;
    uint32_t* src = (uint32_t*)((char*)bucket + i * 4);
    *(uint32_t*)((char*)out + 0) = src[0];
    *(uint32_t*)((char*)out + 4) = src[1];
    *(uint32_t*)((char*)out + 8) = src[2];
    return true;
}

// outlet-chain walker: gOutletCount guards recursion; walk a linked list of
// outlet targets and emit a float to each.
struct OutletNode { OutletNode* next; void* target; };   // +0, +4
struct OutletList { char pad[8]; OutletNode* head; };    // +8

static void EmitFloats(OutletList* lst, float f)
{
    if (++gOutletCount < 1000) {
        for (OutletNode* n = lst->head; n; n = n->next)
            outlet_float(n->target, f);
    }
    --gOutletCount;
}

// @ 0x00a57c60
void Float_(void* x, float f, unsigned b)
{
    CollRecv* r = (CollRecv*)((char*)x + 0x30);
    unsigned fbits = *(unsigned*)&f;
    if (r->LookupKey(1, fbits, b, (int*)&fbits, (int*)&b)) {
        EmitFloats((OutletList*)r->mOutlets, *(float*)&fbits);
        outlet_list(r->mOutlets2, gListSymbol.mHash, gListSender.mHash, (int)fbits, (void*)b);
    }
}

// @ 0x00a57d20
void Symbol_(void* x, unsigned a, unsigned b)
{
    CollRecv* r = (CollRecv*)((char*)x + 0x30);
    int outA = 0, outB = 0;
    if (r->LookupKey(2, a, b, &outA, &outB)) {
        outlet_symbol(r->mOutlets, a, b);
        outlet_list(r->mOutlets2, gListSymbol.mHash, gListSender.mHash, outA, (void*)outB);
    }
}

// @ 0x00a57da0
void List_(void* x, unsigned argc, void* atoms)
{
    CollRecv* r = (CollRecv*)((char*)x + 0x30);
    if (argc == 0) {
        EmitFloats((OutletList*)r->mOutlets2, (float)*(int*)((char*)x + 0x18c));
        return;
    }
    if (argc != 1)
        return;
    int outA = 0, outB = 0;
    if (r->LookupKey(*(unsigned*)atoms, *(unsigned*)((char*)atoms + 4),
                     *(unsigned*)((char*)atoms + 8), &outA, &outB))
        EmitFloats((OutletList*)r->mOutlets2, (float)outA);
}

// @ 0x00a57ea0
void DoInt(void* x, int argc, void* atoms)
{
    if (argc != 2)
        return;
    CollRecv* r = (CollRecv*)((char*)x + 0x30);
    char buf[12];
    atom_getint((char*)atoms + 0xc, buf);
    if (r->LookupIndex(*(unsigned*)atoms, *(unsigned*)((char*)atoms + 4),
                       *(unsigned*)((char*)atoms + 8), *(int*)buf, buf))
        outlet_list(r->mOutlets2, gListSymbol.mHash, gListSender.mHash, 1, buf);
}

// @ 0x00a57f20
void Output(void* x)
{
    CollRecv* r = (CollRecv*)((char*)x + 0x30);
    CollNode* ring = (CollNode*)((char*)x + 0x1d4);
    CollNode* n = ring->mNext;
    while (n != ring) {
        unsigned t = *(unsigned*)((char*)n + 8);
        if (t == 2) {
            outlet_symbol(r->mOutlets, *(unsigned*)((char*)n + 0xc),
                          *(unsigned*)((char*)n + 0x10));
        } else {
            EmitFloats((OutletList*)r->mOutlets, *(float*)((char*)n + 0xc));
        }
        int outA = 0, outB = 0;
        r->LookupKey(t, *(unsigned*)((char*)n + 0xc),
                     *(unsigned*)((char*)n + 0x10), &outA, &outB);
        outlet_list(r->mOutlets2, gListSymbol.mHash, gListSender.mHash, outA, (void*)outB);
        n = n->mNext;
    }
}

}}}  // namespace EA::Audio::Eapd

namespace EA { namespace Audio { namespace Eapd {

// @ 0x00a582f0
bool CollReadClassNew()
{
    t_symbol s;
    t_symbol* p = gensym(&s, "collread");
    uint32_t cls = (uint32_t)class_new(
        p->mHash, (uint32_t)p->mpName, (void*)0xa576c0, 0, 0x30, 0, 6, 0);
    gCollReadClass = cls;
    bool ok = cls != 0;
    ok &= class_doaddfloat((void*)gCollReadClass, (void*)0xa58040);
    ok &= class_addsymbol((void*)gCollReadClass, (void*)0xa580d0);
    t_symbol l;  p = gensym(&l, "length");
    ok &= class_addmethod((void*)gCollReadClass, (void*)0xa58150, p->mHash, (uint32_t)p->mpName, 9, 0);
    t_symbol n;  p = gensym(&n, "nth");
    ok &= class_addmethod((void*)gCollReadClass, (void*)0xa58260, p->mHash, (uint32_t)p->mpName, 9, 0);
    t_symbol st; p = gensym(&st, "set");
    ok &= class_addmethod((void*)gCollReadClass, (void*)0xa57730, p->mHash, (uint32_t)p->mpName, 2, 0);
    return ok;
}

// @ 0x00a583e0
Pair* CollTable::EraseNode(Pair* out, CollNode* key, CollNode** bucket)
{
    CollNode* n = key->mNext;
    out->bucket = bucket;
    out->node = n;
    while (!n) {
        ++bucket;
        n = *bucket;
        out->node = n;
    }
    CollNode* head = *bucket;
    if (head == key) {
        *bucket = head->mNext;
    } else {
        CollNode* prev = head;
        CollNode* cur = head->mNext;
        while (cur != key) {
            prev = cur;
            cur = cur->mNext;
        }
        prev->mNext = cur->mNext;
    }
    if (key != mSpecial) {
        --mCount;
        if (key >= mBegin && key < mEnd) {
            key->mNext = mFree;
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
InsResult* CollTable::InsertIns(InsResult* out, CollNode* key)
{
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
    struct RehashResult { unsigned char grow; unsigned count; } rr;
    Fn921440(&rr, mBucketCount, mElems, 1);
    CollNode* node = AllocNode(key);
    if (rr.grow) {
        b = h % rr.count;
        FreeChains(rr.count);
    }
    node->mNext = mBuckets[b];
    mBuckets[b] = node;
    ++mElems;
    out->node = node;
    out->bucket = mBuckets + b;
    out->ok = true;
    return out;
}

}}}  // namespace EA::Audio::Eapd

namespace EA { namespace Audio { namespace Eapd {

// ---- pd external callbacks (x = the collread/collwrite instance) ----
struct PdColl {
    char      pad0[0x0c];
    void*     mOutlet;                      // +0x0c
    char      pad10[0x28 - 0x10];
    unsigned  mKeyA;                        // +0x28
    unsigned  mKeyB;                        // +0x2c
};

// @ 0x00a58040
void PdFloat_(void* x, float f)
{
    void* o = pd_findbyclass(*(unsigned*)((char*)x + 0x28), *(unsigned*)((char*)x + 0x2c), gCollClass);
    if (o) {
        CollRecv* c = (CollRecv*)((char*)o + 0x30);
        unsigned fb = *(unsigned*)&f;
        int outA = 0, outB = 0;
        if (c->LookupKey(1, fb, fb, &outA, &outB))
            outlet_list(*(void**)((char*)x + 0xc), gListSymbol.mHash, gListSender.mHash, outA, (void*)outB);
    }
}

// @ 0x00a580d0
void PdSymbol_(void* x, unsigned a, unsigned b)
{
    void* o = pd_findbyclass(*(unsigned*)((char*)x + 0x28), *(unsigned*)((char*)x + 0x2c), gCollClass);
    if (o) {
        CollRecv* c = (CollRecv*)((char*)o + 0x30);
        int outA = 0, outB = 0;
        if (c->LookupKey(2, a, b, &outA, &outB))
            outlet_list(*(void**)((char*)x + 0xc), gListSymbol.mHash, gListSender.mHash, outA, (void*)outB);
    }
}

// @ 0x00a58150
void PdLength(void* x, unsigned argc, void* atoms)
{
    void* o = pd_findbyclass(*(unsigned*)((char*)x + 0x28), *(unsigned*)((char*)x + 0x2c), gCollClass);
    if (!o)
        return;
    CollRecv* c = (CollRecv*)((char*)o + 0x30);
    void* outlet2 = c->mOutlets2;
    if (argc == 0) {
        EmitFloats((OutletList*)outlet2, (float)*(int*)((char*)o + 0x18c));
        return;
    }
    if (argc != 1)
        return;
    int outA = 0, outB = 0;
    if (c->LookupKey(*(unsigned*)atoms, *(unsigned*)((char*)atoms + 4),
                     *(unsigned*)((char*)atoms + 8), &outA, &outB))
        EmitFloats((OutletList*)outlet2, (float)outA);
}

// @ 0x00a58260
void PdNth(void* x, int argc, void* atoms)
{
    if (argc != 2)
        return;
    void* o = pd_findbyclass(*(unsigned*)((char*)x + 0x28), *(unsigned*)((char*)x + 0x2c), gCollClass);
    if (!o)
        return;
    CollRecv* c = (CollRecv*)((char*)o + 0x30);
    char buf[12];
    atom_getint((char*)atoms + 0xc, buf);
    if (c->LookupIndex(*(unsigned*)atoms, *(unsigned*)((char*)atoms + 4),
                       *(unsigned*)((char*)atoms + 8), *(int*)buf, buf))
        outlet_list(*(void**)((char*)x + 0xc), gListSymbol.mHash, gListSender.mHash, 1, buf);
}

// @ 0x00a58570
bool CollLess::Less(CollNode* a, CollNode* b)
{
    CollNode* x = b;
    CollNode* y = a;
    if (*(int*)((char*)this + 8) != 0) {
        x = a;
        y = b;
    }
    int keyType, keyA, keyB;
    int keyType2, keyA2, keyB2;
    if (*(int*)((char*)this + 4) < 1) {
        keyType  = *(int*)((char*)y + 8);
        keyA     = *(int*)((char*)y + 0xc);
        keyB     = *(int*)((char*)y + 0x10);
        keyType2 = *(int*)((char*)x + 8);
        keyA2    = *(int*)((char*)x + 0xc);
        keyB2    = *(int*)((char*)x + 0x10);
    } else {
        keyType = 0; keyA = 0; keyB = 0;
        recv->LookupIndex(*(unsigned*)((char*)y + 8), *(unsigned*)((char*)y + 0xc),
                          *(unsigned*)((char*)y + 0x10), *(int*)((char*)this + 4), &keyType);
        keyType2 = 0; keyA2 = 0; keyB2 = 0;
        recv->LookupIndex(*(unsigned*)((char*)x + 8), *(unsigned*)((char*)x + 0xc),
                          *(unsigned*)((char*)x + 0x10), *(int*)((char*)this + 4), &keyType2);
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

}}}  // namespace EA::Audio::Eapd