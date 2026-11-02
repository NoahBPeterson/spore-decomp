// src/game/SPAudio/eapdcoll.cpp -- migrated from slice(s) s00a59690, s00a586d0, s00a576c0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdcoll.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>

// ---- items of slice s00a576c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol { uint32_t mHash; const char* mpName; };   // 8 bytes
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
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
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct Pair { CollNode* node; CollNode** bucket; };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct InsResult { CollNode* node; CollNode** bucket; bool ok; };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct RingNode {
    RingNode* next;        // +0x00
    RingNode* prev;        // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct OutletNode { OutletNode* next; void* target; };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct OutletList { uint8_t pad[8]; OutletNode* head; };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct RehashResult { uint8_t grow; uint8_t pad[3]; uint32_t count; };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class HashPolicy {
public:
    uint8_t pad[0x18];
    void Rehash(RehashResult* out, unsigned buckets, unsigned elems, int flag);  // 0x921440
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void   outlet_list(void* x, uint32_t s1, uint32_t s2, int argc, void* argv);  // 0xa49e40
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void   outlet_float(void* x, float f);                           // 0xa49570
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void   outlet_symbol(void* x, uint32_t a, uint32_t b);           // 0xa49df0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol* gensym(t_symbol* out, const char* s);                  // 0xa675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*  class_new(uint32_t h, uint32_t n, void* fn, int a, int b, int c, int d, int e);  // 0xa48ea0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool   class_addmethod(void* c, void* fn, uint32_t h, uint32_t n, int a1, int a2);   // 0xa48a80
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool   class_doaddfloat(void* c, void* fn);                      // 0xa47f30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool   class_addsymbol(void* c, void* fn);                       // 0xa47f50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
unsigned Fn921340(unsigned n);                                   // 0x921340
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol  gListSymbol;        // 0x16758ac
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol  gListSender;        // 0x16758b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern int       gOutletCount;       // 0x167545c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t  gCollReadClass;     // 0x1675610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class CollIAlloc {
public:
    virtual void  v0();
    virtual void  v1();
    virtual void* Alloc(unsigned size);     // vtable +0x08
    virtual void  Free(void* p);            // vtable +0x0c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class FixedPool {
public:
    bool Init(unsigned size, int count, void* a, void* b);   // 0xa53210, thiscall, ret 0x10
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class CollPool : public CollIAlloc {
public:
    uint8_t  pad04[0x2c];
    unsigned mSize;                        // +0x30
    void*    mBuf;                         // +0x34
    bool Init(int count, void* a, void* b);                     // 0xa57750
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
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
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
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
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollLess {
    CollRecv* recv;                        // +0
    int       index;                       // +4
    int       swap;                        // +8
    bool Less(CollNode* a, CollNode* b);   // 0xa58570
};
}
}
}
// ---- items of slice s00a576c0 end

// ---- items of slice s00a586d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
 class t_coll; 
}
}
}
#define NOINLINE __declspec(noinline)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a5_86d0 { uint32_t hash; const char* name; };   // 8 bytes
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct Atom { uint32_t a, b, c; };                      // 12 bytes
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollNode_s00a5_86d0;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollIAlloc_s00a5_86d0 {
    virtual void  v0();
    virtual void  v1();
    virtual void* Alloc(unsigned size);     // +0x08
    virtual void  Free(void* p);            // +0x0c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollNode_s00a5_86d0 {
    CollNode_s00a5_86d0* prev;      // +0x00  all-entries list
    CollNode_s00a5_86d0* next;      // +0x04
    uint32_t  keyType;   // +0x08
    uint32_t  keyA;      // +0x0c
    uint32_t  keyB;      // +0x10
    uint32_t  count;     // +0x14
    void*     data;      // +0x18
    CollNode_s00a5_86d0* chain;     // +0x1c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct Pair_s00a5_86d0 { CollNode_s00a5_86d0* node; CollNode_s00a5_86d0** bucket; };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollPool_s00a5_86d0 {
    bool Init(int count, void* a, void* b);     // 0xa57750 thiscall ret 0xc
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollTable_s00a5_86d0 {
    char        pad0[4];        // +0x00
    CollNode_s00a5_86d0**  mBuckets;       // +0x04
    unsigned    mBucketCount;   // +0x08
    unsigned    mElems;         // +0x0c
    unsigned    f10;            // +0x10
    unsigned    f14;            // +0x14
    unsigned    f18;            // +0x18
    char        pad1c[0xc];     // +0x1c .. +0x27
    CollIAlloc_s00a5_86d0  mAlloc;         // +0x28
    char        pad2c[0xc];     // +0x2c .. +0x37
    CollNode_s00a5_86d0*   mBegin;         // +0x38
    CollNode_s00a5_86d0*   mEnd;           // +0x3c
    CollNode_s00a5_86d0*   mFree;          // +0x40
    unsigned    mCount;         // +0x44
    unsigned    mHigh;          // +0x48
    unsigned    mSize;          // +0x4c
    CollNode_s00a5_86d0*   mSpecial;       // +0x50

    CollPool_s00a5_86d0*     pool()        { return (CollPool_s00a5_86d0*)((char*)this + 0x1c); }
    bool          Init(int count, void* a, void* b);             // 0xa58950
    void          Destroy();                                     // 0xa589e0
    Pair_s00a5_86d0*         Lookup(Pair_s00a5_86d0* out, CollNode_s00a5_86d0* key);              // 0xa57a20
    CollNode_s00a5_86d0*     AllocNode(CollNode_s00a5_86d0* src);                      // 0xa57aa0
    void          FreeList(CollNode_s00a5_86d0** v, unsigned n);            // 0xa57af0
    Pair_s00a5_86d0*         EraseNode(CollNode_s00a5_86d0* key, CollNode_s00a5_86d0** bucket, Pair_s00a5_86d0* out); // 0xa583e0
    void*         InsertIns(CollNode_s00a5_86d0* key, void* a, void* b);    // 0xa58480
    void          FreeChains(unsigned count);                    // 0xa57900
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct FixedPool_s00a5_86d0 {
    char        pad0[0xc];      // +0x00
    CollIAlloc_s00a5_86d0  mAlloc;         // +0x0c
    char        pad10[0xc];     // +0x10 .. +0x1b
    void*       mBegin;         // +0x1c
    void*       mEnd;           // +0x20
    void*       mFree;          // +0x24
    unsigned    mCount;         // +0x28

    bool Init(unsigned size, int count, void* a, void* b);  // 0xa53210 thiscall ret 0x10
    void Destroy();                                         // 0xa531b0
    void* Alloc();                                          // 0xa532b0
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollList {
    CollList* next;             // +0x00
    CollList* prev;             // +0x04
    void Destroy();             // 0x620230
    void FUN_00a58a70(CollList* other, Atom key);
    void FUN_00a58fa0(Atom key);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollRecv_s00a5_86d0 {
    char        pad0[0x10];     // +0x00 (two fixed vectors)
    CollList    listA;          // +0x10
    char        pad18[0x78];    // +0x18 .. +0x8f
    CollList    listB;          // +0x90
    char        pad98[0x88];    // +0x98 .. +0x11f
    FixedPool_s00a5_86d0   mPool;          // +0x120
    CollTable_s00a5_86d0   mTable;         // +0x150
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
    CollRecv_s00a5_86d0* FUN_00a592f0(void* arg);                           // constructor
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* pd_new(void* cls);                                        // 0xa49390 cdecl
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* outlet_new(void* x, uint32_t s1, uint32_t s2);            // 0xa49d30 cdecl
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* pd_findbyclass(unsigned a, unsigned b, unsigned c);       // 0xa671f0 cdecl
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  pd_bind(void* x, unsigned a, unsigned b);                 // 0xa67620 cdecl
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  sys_vgui(unsigned a, unsigned b, unsigned c);             // 0xa671b0 cdecl
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol_s00a5_86d0* gensym_s00a5_86d0(t_symbol_s00a5_86d0* out, const char* s);                 // 0xa675f0 cdecl
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  class_addmethod3(void* c, void* fn, uint32_t s1, uint32_t s2, int a1);            // 0xa48a30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  class_addlist(void* c, void* fn);                         // 0xa47f70
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* FixedPoolInit(void* self, unsigned size, int count, void* a, void* b); // 0xa53210
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  atom_string(void* a, void* b, int c);                     // 0xa469b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  FnA57840(void* a, void* b, void* c, void* d);             // 0xa57840
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  FnA57700(void* a, void* b);                               // 0xa57700
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  FnA57730(void* a, void* b, void* c);                      // 0xa57730
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  FnA57c60(void* x, float f);                              // 0xa57c60
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  FnA57d20(void* x, unsigned a, unsigned b);                // 0xa57d20
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  FnA58570(void* a, void* b);                               // 0xa58570
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  FnA58e70(void* x, unsigned a, unsigned b, int argc, void* argv); // 0xa58e70
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  FnA588d0(void* x, unsigned a, unsigned b, int argc, void* argv); // 0xa588d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  FnA58920(void* x, unsigned a, unsigned b);                // 0xa58920
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  FnA59250(void* self, const char* name);                   // 0xa59250
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  FnA67d30(void* self);                                     // 0xa67d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_86d0 gListSymbol_s00a5_86d0;       // 0x16758ac
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_86d0 gListSender_s00a5_86d0;       // 0x16758b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_86d0 gEmptySymbol;      // 0x167589c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t gCollClass;        // 0x16755f4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t gCollWriteClass;   // 0x167561c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t gFloatSymbol;      // 0x1675614
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t gAtomSymbol;       // 0x1675600
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t gListSymbol2;      // 0x16758a0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t gCollWriteClass2;  // 0x1675608
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t gBindSymbolA;      // 0x16755f8
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t gBindSymbolB;      // 0x16755fc
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern void* gVguiA;               // 0x15543b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
static const char* kAtomPoolName = "EAPd/CollectionAtomPool";
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
static const char* kMapName = "EAPd/CollectionMap";
}
}
}
// ---- items of slice s00a586d0 end

// ---- items of slice s00a59690 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uintptr_t;
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a5_9690 { void* s_name; void* s_name2; };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol_s00a5_9690* gensym_s00a5_9690(t_symbol_s00a5_9690* buf, const char* name);                                  // 0x00a675f0
}
}
}
using EA::Audio::Eapd::t_symbol_s00a5_9690;
#define g_spCollClass     (*(void**)0x016755f4u)
bool x_coll_setup();
uint8_t FUN_00a598d0();
// ---- items of slice s00a59690 end

// @ 0x00a57750
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a57840
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a57a20
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a57c60
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a57d20
namespace EA { namespace Audio { namespace Eapd {
void Symbol_(void* x, uint32_t a, uint32_t b)
{
    CollRecv* r = (CollRecv*)((char*)x + 0x30);
    int outA, outB;
    if (r->LookupKey(2, a, b, &outA, &outB)) {
        outlet_symbol(r->mOutlets, a, b);
        outlet_list(r->mOutlets2, gListSymbol.mHash, gListSender.mHash, outA, (void*)outB);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a582f0
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58480
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58570
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a587a0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void CollRecv_s00a5_86d0::FUN_00a587a0()
{
    CollTable_s00a5_86d0* t = &mTable;
    CollNode_s00a5_86d0** bp = t->mBuckets;
    CollNode_s00a5_86d0* n = *bp;
    if (!n) {
        ++bp;
        while (!*bp)
            ++bp;
        n = *bp;
    }
    CollNode_s00a5_86d0* sentinel = t->mBuckets[t->mBucketCount];
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58950
namespace EA { namespace Audio { namespace Eapd {
NOINLINE bool CollRecv_s00a5_86d0::FUN_00a58950(int count, void* a, void* b)
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a589e0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void CollRecv_s00a5_86d0::FUN_00a589e0()
{
    CollTable_s00a5_86d0* t = &mTable;
    t->FreeList(t->mBuckets, t->mBucketCount);
    t->mElems = 0;
    if (t->mBucketCount > 1 && t->mBuckets != (CollNode_s00a5_86d0**)t->mSpecial) {
        --t->mCount;
        if (t->mBuckets >= (CollNode_s00a5_86d0**)t->mBegin && t->mBuckets < (CollNode_s00a5_86d0**)t->mEnd) {
            *(CollNode_s00a5_86d0**)t->mBuckets = t->mFree;
            t->mFree = (CollNode_s00a5_86d0*)t->mBuckets;
        } else {
            t->mAlloc.Free(t->mBuckets);
        }
    }
    FnA67d30((char*)t + 0x1c);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58a70
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58b00
namespace EA { namespace Audio { namespace Eapd {
NOINLINE bool CollRecv_s00a5_86d0::FUN_00a58b00(unsigned a, unsigned b, void* alloc)
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58ba0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void CollRecv_s00a5_86d0::FUN_00a58ba0(Atom key, unsigned count, void* data)
{
    if (count <= mMaxB) {
        Pair_s00a5_86d0 p;
        mTable.Lookup(&p, (CollNode_s00a5_86d0*)&key);
        if (p.node != mTable.mBuckets[mTable.mBucketCount]) {
            CollNode_s00a5_86d0* n = p.node;
            n->count = count;
            FnA57840(n->data, data, (void*)(count * 12), 0);
            return;
        }
        if (mTable.mElems != mMaxA) {
            CollNode_s00a5_86d0* n = (CollNode_s00a5_86d0*)mPool.Alloc();
            FnA57840(n, data, (void*)(count * 12), 0);
            mTable.InsertIns((CollNode_s00a5_86d0*)&key, &key, 0);
            CollList* head = &mList;
            n->prev = (CollNode_s00a5_86d0*)head->prev;
            n->next = (CollNode_s00a5_86d0*)head;
            head->prev->next = (CollList*)n;
            head->prev = (CollList*)n;
            return;
        }
    }
    Atom out;
    atom_string(&key, &out, 0x1e);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58cf0
namespace EA { namespace Audio { namespace Eapd {
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
    ((CollRecv_s00a5_86d0*)((char*)x + 0x30))->FUN_00a58b00(arg2, arg3, (void*)0);
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
                ((CollRecv_s00a5_86d0*)((char*)x + 0x30))->FUN_00a58ba0(*p, cnt, p + 1);
                cur = next;
            }
            --n;
            p = next;
        } while (n);
    }
    int cnt = (int)(p - cur);
    if (cnt > 1)
        ((CollRecv_s00a5_86d0*)((char*)x + 0x30))->FUN_00a58ba0(*cur, cnt - 1, cur + 1);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58e00
namespace EA { namespace Audio { namespace Eapd {
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
        ((CollRecv_s00a5_86d0*)((char*)x + 0x30))->FUN_00a58ba0(*argv, argc - 1, argv + 1);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58e70
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void FUN_00a58e70(void* x, uint32_t, const char*, int argc, Atom* argv)
{
    void* o = pd_findbyclass(*(uint32_t*)((char*)x + 0x28),
                             *(uint32_t*)((char*)x + 0x2c), gCollClass);
    if (o)
        ((CollRecv_s00a5_86d0*)((char*)o + 0x30))->FUN_00a58ba0(*argv, argc - 1, argv + 1);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58ec0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE bool FUN_00a58ec0()
{
    t_symbol_s00a5_86d0 s;
    t_symbol_s00a5_86d0* p = gensym_s00a5_86d0(&s, "collwrite");
    gCollWriteClass = (uint32_t)class_new(p->hash, (uint32_t)p->name, (void*)FnA57700,
                                         0, 0x30, 0, 6, 0);
    bool ok = gCollWriteClass != 0;
    ok &= class_addlist((void*)gCollWriteClass, (void*)FnA58e70);
    p = gensym_s00a5_86d0(&s, "delete");
    ok &= class_addmethod((void*)gCollWriteClass, (void*)FnA588d0, p->hash, (uint32_t)p->name, 9, 0);
    p = gensym_s00a5_86d0(&s, "clear");
    ok &= class_addmethod3((void*)gCollWriteClass, (void*)FnA58920, p->hash, (uint32_t)p->name, 0);
    p = gensym_s00a5_86d0(&s, "set");
    ok &= class_addmethod((void*)gCollWriteClass, (void*)FnA57730, p->hash, (uint32_t)p->name, 2, 0);
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58fa0
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a59150
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void CollRecv_s00a5_86d0::FUN_00a59150()
{
    FUN_00a587a0();
    mList.Destroy();
    FUN_00a589e0();
    mPool.Destroy();
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a591c0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void FUN_00a591c0(void* x, uint32_t sym, uint32_t, float f)
{
    CollRecv_s00a5_86d0* r = (CollRecv_s00a5_86d0*)((char*)x + 0x30);
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a592f0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE CollRecv_s00a5_86d0* CollRecv_s00a5_86d0::FUN_00a592f0(void* arg)
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a593e0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void* FUN_00a593e0(void* arg1, int arg2, int count, Atom* atoms)
{
    (void)arg1;
    t_symbol_s00a5_86d0 sym = gEmptySymbol;
    uint32_t symB = gListSymbol2;
    int iVar10 = 0;
    unsigned uVar8 = 0xffffffff;
    unsigned local24 = 0xffffffff;
    bool old = false;
    CollRecv_s00a5_86d0* r;
    t_symbol_s00a5_86d0* p = (t_symbol_s00a5_86d0*)&sym;

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
    r = (CollRecv_s00a5_86d0*)((char*)o + 0x30);
    r->FUN_00a592f0(o);
    *(uint32_t*)((char*)o + 0x28) = sym.hash;
    *(uint32_t*)((char*)o + 0x2c) = (uint32_t)(unsigned)sym.name;

    void* out1 = outlet_new(o, gListSymbol_s00a5_86d0.hash, (uint32_t)(unsigned)gListSender_s00a5_86d0.name);
    *(void**)((char*)o + 0x1ec) = out1;
    t_symbol_s00a5_86d0 fs;
    t_symbol_s00a5_86d0* fp = gensym_s00a5_86d0(&fs, "float or symbol");
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a59630
namespace EA {
namespace Audio {
namespace Eapd {
void coll_free(t_coll * x)
{
    if (*(uint32_t*)((char*)x + 0x28) != gEmptySymbol.hash)
        sys_vgui((unsigned)(unsigned)x, *(uint32_t*)((char*)x + 0x28),
                 *(uint32_t*)((char*)x + 0x2c));
    void* v = pd_findbyclass(gBindSymbolA, gBindSymbolB, gCollClass);
    if (v == x)
        sys_vgui((unsigned)(unsigned)x, gBindSymbolA, gBindSymbolB);
    ((CollRecv_s00a5_86d0*)((char*)x + 0x30))->FUN_00a59150();
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a59690
bool x_coll_setup()
{
    t_symbol_s00a5_9690 sym;
    bool ok = true;

    EA::Audio::Eapd::gensym_s00a5_9690(&sym, "coll");
    g_spCollClass = (void*)((uintptr_t(*)(t_symbol_s00a5_9690*, void*, void*, int, int, int,
                                          int, int, int, int, int))0x00a48f00)(
        &sym, sym.s_name2, (void*)0x00a58e00, 0, 0x1f0, 0, 0, 9, 0, 0x016755f4, 0);
    (void)ok;
    return ok;
}

// @ 0x00a598d0
uint8_t FUN_00a598d0()
{
    uint8_t a = (uint8_t)x_coll_setup();
    uint8_t b = (uint8_t)((uint8_t(*)(void))0x00a582f0)();
    uint8_t c = (uint8_t)((uint8_t(*)(void))0x00a58ec0)();
    return (uint8_t)(a & 1 & b & c);
}
