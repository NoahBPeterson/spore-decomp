// slice s00a586d0 -- SPAudio EAPd "collwrite" collection object implementation.
// Object file: SPAudio/eapdinstance.obj.  Compile: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#define NOINLINE __declspec(noinline)

namespace EA {
namespace Audio {
namespace Eapd {

struct t_symbol { uint32_t hash; const char* name; };   // 8 bytes
struct Atom { uint32_t a, b, c; };                      // 12 bytes

struct CollNode;
struct CollIAlloc {
    virtual void  v0();
    virtual void  v1();
    virtual void* Alloc(unsigned size);     // +0x08
    virtual void  Free(void* p);            // +0x0c
};

struct CollNode {
    CollNode* prev;      // +0x00  all-entries list
    CollNode* next;      // +0x04
    uint32_t  keyType;   // +0x08
    uint32_t  keyA;      // +0x0c
    uint32_t  keyB;      // +0x10
    uint32_t  count;     // +0x14
    void*     data;      // +0x18
    CollNode* chain;     // +0x1c
};

struct Pair { CollNode* node; CollNode** bucket; };

struct CollPool {
    bool Init(int count, void* a, void* b);     // 0xa57750 thiscall ret 0xc
};

struct CollTable {
    char        pad0[4];        // +0x00
    CollNode**  mBuckets;       // +0x04
    unsigned    mBucketCount;   // +0x08
    unsigned    mElems;         // +0x0c
    unsigned    f10;            // +0x10
    unsigned    f14;            // +0x14
    unsigned    f18;            // +0x18
    char        pad1c[0xc];     // +0x1c .. +0x27
    CollIAlloc  mAlloc;         // +0x28
    char        pad2c[0xc];     // +0x2c .. +0x37
    CollNode*   mBegin;         // +0x38
    CollNode*   mEnd;           // +0x3c
    CollNode*   mFree;          // +0x40
    unsigned    mCount;         // +0x44
    unsigned    mHigh;          // +0x48
    unsigned    mSize;          // +0x4c
    CollNode*   mSpecial;       // +0x50

    CollPool*     pool()        { return (CollPool*)((char*)this + 0x1c); }
    bool          Init(int count, void* a, void* b);             // 0xa58950
    void          Destroy();                                     // 0xa589e0
    Pair*         Lookup(Pair* out, CollNode* key);              // 0xa57a20
    CollNode*     AllocNode(CollNode* src);                      // 0xa57aa0
    void          FreeList(CollNode** v, unsigned n);            // 0xa57af0
    Pair*         EraseNode(CollNode* key, CollNode** bucket, Pair* out); // 0xa583e0
    void*         InsertIns(CollNode* key, void* a, void* b);    // 0xa58480
    void          FreeChains(unsigned count);                    // 0xa57900
};

struct FixedPool {
    char        pad0[0xc];      // +0x00
    CollIAlloc  mAlloc;         // +0x0c
    char        pad10[0xc];     // +0x10 .. +0x1b
    void*       mBegin;         // +0x1c
    void*       mEnd;           // +0x20
    void*       mFree;          // +0x24
    unsigned    mCount;         // +0x28

    bool Init(unsigned size, int count, void* a, void* b);  // 0xa53210 thiscall ret 0x10
    void Destroy();                                         // 0xa531b0
    void* Alloc();                                          // 0xa532b0
};

struct CollList {
    CollList* next;             // +0x00
    CollList* prev;             // +0x04
    void Destroy();             // 0x620230
    void FUN_00a58a70(CollList* other, Atom key);
    void FUN_00a58fa0(Atom key);
};

struct CollRecv {
    char        pad0[0x10];     // +0x00 (two fixed vectors)
    CollList    listA;          // +0x10
    char        pad18[0x78];    // +0x18 .. +0x8f
    CollList    listB;          // +0x90
    char        pad98[0x88];    // +0x98 .. +0x11f
    FixedPool   mPool;          // +0x120
    CollTable   mTable;         // +0x150
    CollList    mList;          // +0x1a4
    char        pad1ac[4];      // +0x1ac
    unsigned    mMaxA;          // +0x1ac
    unsigned    mMaxB;          // +0x1b0
    unsigned    mInitMax;       // +0x1b4

    void  FUN_00a586d0(Atom key);                                // erase one key
    void  FUN_00a587a0();                                        // clear
    bool  FUN_00a58950(int count, void* a, void* b);             // table init
    void  FUN_00a589e0();                                        // table destroy
    bool  FUN_00a58b00(unsigned a, unsigned b, void* alloc);
    void  FUN_00a58ba0(Atom key, unsigned count, void* data);
    void  FUN_00a59150();                                        // destructor
    CollRecv* FUN_00a592f0(void* arg);                           // constructor
};

// ---- external EAPd helpers ------------------------------------------------
void* pd_new(void* cls);                                        // 0xa49390 cdecl
void* outlet_new(void* x, uint32_t s1, uint32_t s2);            // 0xa49d30 cdecl
void* pd_findbyclass(unsigned a, unsigned b, unsigned c);       // 0xa671f0 cdecl
bool  pd_bind(void* x, unsigned a, unsigned b);                 // 0xa67620 cdecl
void  sys_vgui(unsigned a, unsigned b, unsigned c);             // 0xa671b0 cdecl
t_symbol* gensym(t_symbol* out, const char* s);                 // 0xa675f0 cdecl
void* class_new(uint32_t s1, uint32_t s2, void* fn, int a, int b, int c, int d, int e); // 0xa48ea0
bool  class_addmethod(void* c, void* fn, uint32_t s1, uint32_t s2, int a1, int a2);     // 0xa48a80
bool  class_addmethod3(void* c, void* fn, uint32_t s1, uint32_t s2, int a1);            // 0xa48a30
bool  class_addlist(void* c, void* fn);                         // 0xa47f70
void* FixedPoolInit(void* self, unsigned size, int count, void* a, void* b); // 0xa53210
void  atom_string(void* a, void* b, int c);                     // 0xa469b0
unsigned Fn921340(unsigned n);                                  // 0x921340
void  Fn921440(void* out, unsigned a, unsigned b, int c);       // 0x921440
void  FnA57840(void* a, void* b, void* c, void* d);             // 0xa57840
void  FnA57700(void* a, void* b);                               // 0xa57700
void  FnA57730(void* a, void* b, void* c);                      // 0xa57730
void  FnA57c60(void* x, float f);                              // 0xa57c60
void  FnA57d20(void* x, unsigned a, unsigned b);                // 0xa57d20
bool  FnA58570(void* a, void* b);                               // 0xa58570
void  FnA58e70(void* x, unsigned a, unsigned b, int argc, void* argv); // 0xa58e70
void  FnA588d0(void* x, unsigned a, unsigned b, int argc, void* argv); // 0xa588d0
void  FnA58920(void* x, unsigned a, unsigned b);                // 0xa58920
void  FnA59250(void* self, const char* name);                   // 0xa59250
void  FnA67d30(void* self);                                     // 0xa67d30

extern t_symbol gListSymbol;       // 0x16758ac
extern t_symbol gListSender;       // 0x16758b0
extern t_symbol gEmptySymbol;      // 0x167589c
extern uint32_t gCollClass;        // 0x16755f4
extern uint32_t gCollWriteClass;   // 0x167561c
extern uint32_t gFloatSymbol;      // 0x1675614
extern uint32_t gAtomSymbol;       // 0x1675600
extern uint32_t gListSymbol2;      // 0x16758a0
extern uint32_t gCollWriteClass2;  // 0x1675608
extern uint32_t gBindSymbolA;      // 0x16755f8
extern uint32_t gBindSymbolB;      // 0x16755fc
extern void* gVguiA;               // 0x15543b0

static const char* kAtomPoolName = "EAPd/CollectionAtomPool";
static const char* kMapName = "EAPd/CollectionMap";

}}}  // namespace EA::Audio::Eapd

namespace EA { namespace Audio { namespace Eapd {

// @ 0x00a586d0
NOINLINE void CollRecv::FUN_00a586d0(Atom key)
{
    CollTable* t = &mTable;
    CollNode k2;
    k2.prev = 0;
    k2.next = 0;
    k2.keyType = key.a;
    k2.keyA = key.b;
    k2.keyB = key.c;
    Pair p;
    t->Lookup(&p, &k2);
    if (p.node != t->mBuckets[t->mBucketCount]) {
        CollNode* n = p.node;
        n->prev->next = n->next;
        n->next->prev = n->prev;
        n->prev = 0;
        n->next = 0;
        void* data = n->data;
        --mPool.mCount;
        if (data >= mPool.mBegin && data < mPool.mEnd) {
            *(void**)data = mPool.mFree;
            mPool.mFree = data;
        } else {
            mPool.mAlloc.Free(data);
        }
        t->EraseNode(n, p.bucket, &p);
    }
}

// @ 0x00a587a0
NOINLINE void CollRecv::FUN_00a587a0()
{
    CollTable* t = &mTable;
    CollNode** bp = t->mBuckets;
    CollNode* n = *bp;
    if (!n) {
        ++bp;
        while (!*bp)
            ++bp;
        n = *bp;
    }
    CollNode* sentinel = t->mBuckets[t->mBucketCount];
    if (n != sentinel) {
        do {
            void* data = n->data;
            --mPool.mCount;
            if (data >= mPool.mBegin && data < mPool.mEnd) {
                *(void**)data = mPool.mFree;
                mPool.mFree = data;
            } else {
                mPool.mAlloc.Free(data);
            }
            n = n->chain;
            while (!n) {
                ++bp;
                n = *bp;
            }
        } while (n != sentinel);
    }
    CollList* head = &mList;
    CollList* p = head->next;
    while (p != head) {
        CollList* nx = p->next;
        p->next = 0;
        p->prev = 0;
        p = nx;
    }
    head->prev = head;
    head->next = head;
    t->FreeList(t->mBuckets, t->mBucketCount);
    mTable.f18 = 0;
}

// @ 0x00a58890
NOINLINE void FUN_00a58890(void* x, uint32_t, const char*, int argc, Atom* argv)
{
    if (argc == 1) {
        Atom a = *argv;
        ((CollRecv*)((char*)x + 0x30))->FUN_00a586d0(a);
    }
}

// @ 0x00a588c0
NOINLINE void FUN_00a588c0(void* x)
{
    ((CollRecv*)((char*)x + 0x30))->FUN_00a587a0();
}

// @ 0x00a588d0
NOINLINE void FUN_00a588d0(void* x, uint32_t, const char*, int argc, Atom* argv)
{
    if (argc == 1) {
        void* o = pd_findbyclass(*(uint32_t*)((char*)x + 0x28),
                                 *(uint32_t*)((char*)x + 0x2c), gCollClass);
        if (o) {
            Atom a = *argv;
            ((CollRecv*)((char*)o + 0x30))->FUN_00a586d0(a);
        }
    }
}

// @ 0x00a58920
NOINLINE void FUN_00a58920(void* x)
{
    void* o = pd_findbyclass(*(uint32_t*)((char*)x + 0x28),
                             *(uint32_t*)((char*)x + 0x2c), gCollClass);
    if (o)
        ((CollRecv*)((char*)o + 0x30))->FUN_00a587a0();
}

// @ 0x00a58950
NOINLINE bool CollRecv::FUN_00a58950(int count, void* a, void* b)
{
    if (!mTable.pool()->Init(count, a, b))
        return false;
    mTable.FreeChains((int)mTable.mSize - 1);
    mTable.f10 = 0x461c4000;    // 10000.0f
    mTable.f14 = 0x40000000;    // 2.0f
    mTable.f18 = 0;
    unsigned n = Fn921340(mTable.mElems);
    if (n > mTable.mBucketCount)
        mTable.FreeChains(n);
    return true;
}

// @ 0x00a589e0
NOINLINE void CollRecv::FUN_00a589e0()
{
    CollTable* t = &mTable;
    t->FreeList(t->mBuckets, t->mBucketCount);
    t->mElems = 0;
    if (t->mBucketCount > 1 && t->mBuckets != (CollNode**)t->mSpecial) {
        --t->mCount;
        if (t->mBuckets >= (CollNode**)t->mBegin && t->mBuckets < (CollNode**)t->mEnd) {
            *(CollNode**)t->mBuckets = t->mFree;
            t->mFree = (CollNode*)t->mBuckets;
        } else {
            t->mAlloc.Free(t->mBuckets);
        }
    }
    FnA67d30((char*)t + 0x1c);
}

// @ 0x00a58a70
NOINLINE void CollList::FUN_00a58a70(CollList* other, Atom key)
{
    if (this == other)
        return;
    CollList* a = this;
    CollList* b = other;
    CollList* i = a->next;
    CollList* j = b->next;
    if (i == a)
        goto tail;
    if (j == b)
        return;
    for (;;) {
        if (FnA58570(j, i)) {
            CollList* jn = j->next;
            if (j != jn) {
                jn->prev = j->prev;
                j->prev->next = jn;
                CollList* ip = i->prev;
                ip->next = j;
                j->prev = ip;
                jn->prev = i;
                i->prev = jn;
            }
            j = jn;
        } else {
            i = i->next;
        }
        if (i == a)
            break;
        if (j == b)
            return;
    }
tail:
    if (j != b)
        FnA57840(a, b, j, b);
}

// @ 0x00a58b00
NOINLINE bool CollRecv::FUN_00a58b00(unsigned a, unsigned b, void* alloc)
{
    mMaxA = a;
    mMaxB = b;
    struct AllocVt { void* p; unsigned f; void* s; } v;
    v.p = (void*)0x1454fac;
    v.f = 0;
    v.s = gVguiA;
    bool ok = FixedPoolInit(&mPool, b * 12, a, alloc, &v) != 0;
    bool ok2 = FUN_00a58950(a, alloc, &v);
    return ok2 & ok & 1;
}

// @ 0x00a58ba0
NOINLINE void CollRecv::FUN_00a58ba0(Atom key, unsigned count, void* data)
{
    if (count <= mMaxB) {
        Pair p;
        mTable.Lookup(&p, (CollNode*)&key);
        if (p.node != mTable.mBuckets[mTable.mBucketCount]) {
            CollNode* n = p.node;
            n->count = count;
            FnA57840(n->data, data, (void*)(count * 12), 0);
            return;
        }
        if (mTable.mElems != mMaxA) {
            CollNode* n = (CollNode*)mPool.Alloc();
            FnA57840(n, data, (void*)(count * 12), 0);
            mTable.InsertIns((CollNode*)&key, &key, 0);
            CollList* head = &mList;
            n->prev = (CollNode*)head->prev;
            n->next = (CollNode*)head;
            head->prev->next = (CollList*)n;
            head->prev = (CollList*)n;
            return;
        }
    }
    Atom out;
    atom_string(&key, &out, 0x1e);
}

// @ 0x00a58cf0
NOINLINE void FUN_00a58cf0(void* x, int arg2, int arg3, int count, Atom* atoms)
{
    int iVar1 = -1;
    int iVar5 = 1;
    Atom* p = atoms;
    int n = count;
    if (n > 0) {
        do {
            if (p->a == 2 && p->b == gAtomSymbol) {
                ++iVar5;
                if (arg3 <= iVar1)
                    arg3 = iVar1;
                iVar1 = -1;
            } else {
                ++iVar1;
            }
            p++;
        } while (--n);
    }
    if (arg3 <= iVar1)
        arg3 = iVar1;
    if (arg2 <= iVar5)
        arg2 = iVar5;
    void* alloc = (void*)gListSymbol2;
    ((CollRecv*)((char*)x + 0x30))->FUN_00a58b00(arg2, arg3, (void*)0);
    (void)alloc;

    Atom* base = atoms;
    Atom* cur = atoms;
    p = atoms;
    n = count;
    if (n > 0) {
        do {
            Atom* next = p + 1;
            if (p->a == 2 && p->b == gAtomSymbol && (next - base) >= 3) {
                int cnt = (int)(next - base) - 2;
                ((CollRecv*)((char*)x + 0x30))->FUN_00a58ba0(*p, cnt, p + 1);
                cur = next;
            }
            --n;
            p = next;
        } while (n);
    }
    int cnt = (int)(p - cur);
    if (cnt > 1)
        ((CollRecv*)((char*)x + 0x30))->FUN_00a58ba0(*cur, cnt - 1, cur + 1);
}

// @ 0x00a58e00
NOINLINE void FUN_00a58e00(void* x, uint32_t, const char*, int argc, Atom* argv)
{
    if (argc == 1) {
        if (argv->a == 1) {
            FnA57c60(x, *(float*)&argv->b);
        } else {
            FnA57d20(x, argv->b, argv->c);
        }
        return;
    }
    if (argc > 1)
        ((CollRecv*)((char*)x + 0x30))->FUN_00a58ba0(*argv, argc - 1, argv + 1);
}

// @ 0x00a58e70
NOINLINE void FUN_00a58e70(void* x, uint32_t, const char*, int argc, Atom* argv)
{
    void* o = pd_findbyclass(*(uint32_t*)((char*)x + 0x28),
                             *(uint32_t*)((char*)x + 0x2c), gCollClass);
    if (o)
        ((CollRecv*)((char*)o + 0x30))->FUN_00a58ba0(*argv, argc - 1, argv + 1);
}

// @ 0x00a58ec0
NOINLINE bool FUN_00a58ec0()
{
    t_symbol s;
    t_symbol* p = gensym(&s, "collwrite");
    gCollWriteClass = (uint32_t)class_new(p->hash, (uint32_t)p->name, (void*)FnA57700,
                                         0, 0x30, 0, 6, 0);
    bool ok = gCollWriteClass != 0;
    ok &= class_addlist((void*)gCollWriteClass, (void*)FnA58e70);
    p = gensym(&s, "delete");
    ok &= class_addmethod((void*)gCollWriteClass, (void*)FnA588d0, p->hash, (uint32_t)p->name, 9, 0);
    p = gensym(&s, "clear");
    ok &= class_addmethod3((void*)gCollWriteClass, (void*)FnA58920, p->hash, (uint32_t)p->name, 0);
    p = gensym(&s, "set");
    ok &= class_addmethod((void*)gCollWriteClass, (void*)FnA57730, p->hash, (uint32_t)p->name, 2, 0);
    return ok;
}

// @ 0x00a58fa0
NOINLINE void CollList::FUN_00a58fa0(Atom key)
{
    CollList* head = this;
    if (head->next == head || head->next == head->prev)
        return;
    CollList a, b;
    a.next = a.prev = &a;
    b.next = b.prev = &b;
    CollList* i = head->next;
    CollList* j = head;
    while (i != j) {
        j = j->prev;
        if (i == j)
            break;
        CollList* n = i->next;
        CollList* p = j->prev;
        p->next = n;
        n->prev = p;
        i->next = &b;
        b.prev = i;
        j->next = &a;
        a.prev = j;
        i = n;
    }
    CollList* rest = head->next;
    if (rest != head) {
        CollList* p = a.prev;
        p->next = rest;
        rest->prev = p;
        head->prev->next = &a;
        a.prev = head->prev;
        head->next = head;
        head->prev = head;
    }
    FUN_00a58fa0(key);
    FUN_00a58fa0(key);
}

// @ 0x00a59150
NOINLINE void CollRecv::FUN_00a59150()
{
    FUN_00a587a0();
    mList.Destroy();
    FUN_00a589e0();
    mPool.Destroy();
}

// @ 0x00a591c0
NOINLINE void FUN_00a591c0(void* x, uint32_t sym, uint32_t, float f)
{
    CollRecv* r = (CollRecv*)((char*)x + 0x30);
    Atom key;
    if (sym == gFloatSymbol) {
        key.a = (uint32_t)(unsigned)r;
        key.b = (uint32_t)(int)f;
        key.c = 1;
        ((CollList*)((char*)r + 0x1a4))->FUN_00a58fa0(key);
    } else {
        key.a = (uint32_t)(unsigned)r;
        key.b = (uint32_t)(int)f;
        key.c = 0;
        ((CollList*)((char*)r + 0x1a4))->FUN_00a58fa0(key);
    }
}

// @ 0x00a592f0
NOINLINE CollRecv* CollRecv::FUN_00a592f0(void* arg)
{
    listA.next = (CollList*)((char*)this + 0x10);
    listA.prev = (CollList*)((char*)this + 0x10);
    *(void**)((char*)this + 0x08) = (char*)this + 0x90;
    *(uint8_t*)((char*)this + 0x10) = 0;
    listB.next = (CollList*)((char*)this + 0xa0);
    listB.prev = (CollList*)((char*)this + 0xa0);
    *(void**)((char*)this + 0x98) = (char*)this + 0x120;
    *(uint8_t*)((char*)this + 0xa0) = 0;

    *(void**)((char*)this + 0x120) = (void*)0x1454fac;
    *(unsigned*)((char*)this + 0x124) = 0;
    *(const char**)((char*)this + 0x128) = kAtomPoolName;
    *(void**)((char*)this + 0x12c) = (void*)0x1454fac;
    *(unsigned*)((char*)this + 0x130) = 0;
    *(const char**)((char*)this + 0x134) = kAtomPoolName;
    *(unsigned*)((char*)this + 0x138) = 0;
    *(unsigned*)((char*)this + 0x13c) = 0;
    *(unsigned*)((char*)this + 0x140) = 0;
    *(unsigned*)((char*)this + 0x144) = 0;
    *(unsigned*)((char*)this + 0x148) = 0;
    *(unsigned*)((char*)this + 0x14c) = 0;

    FnA59250((char*)this + 0x150, kMapName);

    mList.next = &mList;
    mList.prev = &mList;
    mInitMax = (unsigned)arg;
    mMaxA = 0;
    mMaxB = 0;
    return this;
}

// @ 0x00a593e0
NOINLINE void* FUN_00a593e0(void* arg1, int arg2, int count, Atom* atoms)
{
    (void)arg1;
    t_symbol sym = gEmptySymbol;
    uint32_t symB = gListSymbol2;
    int iVar10 = 0;
    unsigned uVar8 = 0xffffffff;
    unsigned local24 = 0xffffffff;
    bool old = false;
    CollRecv* r;
    t_symbol* p = (t_symbol*)&sym;

    if (count > 0) {
        Atom* a = atoms;
        do {
            if (a->a == 2) {
                if (a->b == gCollWriteClass2) {
                    ++iVar10;
                    old = true;
                    break;
                }
                if (gEmptySymbol.hash == p->hash) {
                    sym.hash = a->b;
                    sym.name = (const char*)a->c;
                }
            } else {
                int v = (int)*(float*)&a->b;
                if (uVar8 == 0xffffffff) {
                    uVar8 = v < 0 ? 0 : (unsigned)v;
                } else if (local24 == 0xffffffff) {
                    local24 = 1;
                    if (v >= 1)
                        local24 = (unsigned)v;
                }
            }
            ++iVar10;
            a++;
        } while (iVar10 < count);
    }
    if (p->hash != gEmptySymbol.hash &&
        pd_findbyclass(p->hash, (unsigned)(unsigned)p->name, gCollClass))
        return 0;
    if (uVar8 == 0xffffffff) uVar8 = 0;
    if (local24 == 0xffffffff) local24 = 1;

    void* o = pd_new((void*)gCollClass);
    r = (CollRecv*)((char*)o + 0x30);
    r->FUN_00a592f0(o);
    *(uint32_t*)((char*)o + 0x28) = sym.hash;
    *(uint32_t*)((char*)o + 0x2c) = (uint32_t)(unsigned)sym.name;

    void* out1 = outlet_new(o, gListSymbol.hash, (uint32_t)(unsigned)gListSender.name);
    *(void**)((char*)o + 0x1ec) = out1;
    t_symbol fs;
    t_symbol* fp = gensym(&fs, "float or symbol");
    void* out2 = outlet_new(o, fp->hash, (uint32_t)(unsigned)fp->name);
    *(void**)((char*)o + 0x1e8) = out2;

    if (old) {
        FUN_00a58cf0(o, uVar8, local24, count - iVar10, atoms + iVar10);
    } else {
        r->FUN_00a58b00(uVar8, local24, (void*)0);
    }
    if (*(uint32_t*)((char*)o + 0x28) != gEmptySymbol.hash)
        pd_bind(o, *(uint32_t*)((char*)o + 0x28), *(uint32_t*)((char*)o + 0x2c));
    void* v = pd_findbyclass(gBindSymbolA, gBindSymbolB, gCollClass);
    if (v)
        sys_vgui((unsigned)(unsigned)v, gBindSymbolA, gBindSymbolB);
    pd_bind(o, gBindSymbolA, gBindSymbolB);
    (void)arg2;
    return o;
}

// @ 0x00a59630
NOINLINE void FUN_00a59630(void* x)
{
    if (*(uint32_t*)((char*)x + 0x28) != gEmptySymbol.hash)
        sys_vgui((unsigned)(unsigned)x, *(uint32_t*)((char*)x + 0x28),
                 *(uint32_t*)((char*)x + 0x2c));
    void* v = pd_findbyclass(gBindSymbolA, gBindSymbolB, gCollClass);
    if (v == x)
        sys_vgui((unsigned)(unsigned)x, gBindSymbolA, gBindSymbolB);
    ((CollRecv*)((char*)x + 0x30))->FUN_00a59150();
}

}}}  // namespace EA::Audio::Eapd
