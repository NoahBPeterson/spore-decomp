// slice s009e0d90 -- gait record editor helpers used by the retail nSPCreatureAnim /
// gait subsystem of SporeApp.exe (32-bit, MSVC 2008 SP1 /O2).
//
//   @ 0x009e0d90  Outer::AddGait(void*)            dispatch on Record::kind, evaluate the
//                                                 key floats and append the A/B/C gait
//   @ 0x009e0f80  Outer::AddItem(void*)           evaluate one float into Record::item.b and
//                                                 append the 12-byte item
//   @ 0x009e0ff0  Outer::PushFlag(bool)           if !flag push the holder value into v1
//   @ 0x009e1030  Gait::Gait()                    default ctor (id = 50, three empty lists)
//   @ 0x009e1100  Gait::Gait(const Gait&)         copy ctor
//   @ 0x009e1160  Inner::AssignItemsN(const Inner*, uint32)
//   @ 0x009e1260  Inner::AssignItemsF(const Inner*, uint32 flags)
//   @ 0x009e1370  Inner::AssignItems(const Inner*)
//   @ 0x009e1470  Inner::Combine(const Inner*, float, const Inner*)
//   @ 0x009e1610  ItemArr::Add(const GaitItem*)   sorted insert-or-overwrite by .a
//   @ 0x009e1690  UninitCopyGait(first,last,result)
//   @ 0x009e1710  RecBlob::~RecBlob()
//   @ 0x009e1760  ItemArr::Build(const Src2*)
//   @ 0x009e17d0  RBTree::find_or_insert(const int*)
//   @ 0x009e1850  FindOrCreate(const char*, uint32)
//   @ 0x009e18c0  LoadGaitFile(const char*, int, int)
//   @ 0x009e1990  Vec<Gait>::realloc_insert(Gait*, const Gait&)
//   @ 0x009e1b40  Outer::Select(void*)            pick A/B/C by remaining capacity, push the
//                                                 gait when full, then store the evaluated id
//   @ 0x009e1cd0  Outer::PushGait(bool)           if !flag move the gait into the gaits list
//
// Build: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (no /EHsc)
#include "types.h"

typedef unsigned char uint8;
typedef unsigned int  uint32;

// ------------------------------------------------------------------ external code

inline void* operator new(unsigned, void* p) { return p; }
void  operator delete[](void* p);                                     // 0x00f47380
void* operator_new(unsigned size, const char* name, int flags, int align,
                   const char* file, int line);                       // 0x00f473a0

extern const char g_alloc_name_anim_gait[];                           // 0x014479f4 "Anim/gait/untagged"
extern const char g_alloc_file_eastl[];                               // 0x013ebb38 ".../EASTL/allocator.h"
extern const float g_gait_default_id;                                 // 0x013f1cac 50.0f
extern void* g_name_map;                                              // 0x0166c06c global name->object map

void*  CreateByName(const uint32 key);                                // 0x00a08a20
uint32 HashName(const char* s, uint32 basis, int one);                // 0x00932e80 FNV-1a

struct CArgs { void** MainArguments(int n); };                        // 0x00838320 __thiscall ret 4
struct Combiner { void Combine5(void* dst, unsigned i, const void* a,
                               float f, const void* b); };            // 0x009dc5b0 __thiscall

// element copy-constructors (out of line in the original)
struct GaitA; struct GaitB; struct GaitC;
GaitA* CopyGaitA(GaitA* dst, const GaitA* src);                       // 0x009dbe30
GaitB* CopyGaitB(GaitB* dst, const GaitB* src);                       // 0x009dbe80
GaitC* CopyGaitC(GaitC* dst, const GaitC* src);                       // 0x009dbed0

void  CopyA(GaitA* first, GaitA* last, GaitA* result);                // 0x009dc230 eastl::copy (cdecl)
void  CopyB(GaitB* first, GaitB* last, GaitB* result);                // 0x009dc270 eastl::copy (cdecl)
void  CopyC(GaitC* first, GaitC* last, GaitC* result);                // 0x009dc2b0 eastl::copy (cdecl)

void GaitRangeHelper(void* a, void* b, void* c);                      // 0x009de7d0
struct RBNode;
// 0x009e0c00: thiscall(ecx=tree), 4 stack dwords: [esp+4]=outNode [esp+8]=parent [esp+0xc]=key [esp+0x10]=flag
struct RBTree0 { void Insert(RBNode** outNode, RBNode* parent, const uint32* key, int flag); };

// ------------------------------------------------------------------ element types

struct Slot {                                                          // 16 bytes
    float a, b;
    bool  c, d;
    short e;
    int   pad;
};

struct GaitA {                                                         // 0x44, vtable 0x01447cc0
    virtual void f0();
    int   id;                                                          // +0x04
    float x, y, z;                                                     // +0x08
    Slot  s[3];                                                        // +0x14
    GaitA(const GaitA& o);                                             // 0x009dbe30
};

struct GaitB {                                                         // 0x58, vtable 0x01447cc4
    virtual void f0();
    int   id;                                                          // +0x04
    float a, b, c, d;                                                  // +0x08
    Slot  s[4];                                                        // +0x18
    GaitB(const GaitB& o);                                             // 0x009dbe80
};

struct GaitC {                                                         // 0x1c, vtable 0x01447cc8
    virtual void f0();
    int   id;                                                          // +0x04
    int   pad8;                                                        // +0x08
    float x, y, z;                                                     // +0x0c
    int   pad18;                                                       // +0x18
    GaitC(const GaitC& o);                                             // 0x009dbed0
};

struct Item { float a, b; int c; };                                    // 0x0c (record item)
struct GaitItem { float a, b; int c; };                                // 0x0c (ItemArr element)

// ------------------------------------------------------------------ vectors

template <class T>
struct Vec {                                                           // 0x14: begin/end/cap + 8-byte alloc
    T* b;
    T* e;
    T* cap;
    int alloc[2];
    Vec() : b(0), e(0), cap(0) {}
    ~Vec() { if (b && ((int*)b)[-1]) operator delete[](b); }
    Vec& operator=(const Vec& o);                                      // 0x9dfda0 / 0x9dfec0 / 0x9dffe0 / 0x9df630
    void reserve(int n);                                               // 0x9df400 / 0x9df4c0 / 0x9df570 / 0x9df630 / 0x9df800
    void clear();                                                      // 0x9e0940 / 0x9e0980 / 0x9e09c0
    void realloc_insert(T* pos, const T& v);                           // 0x9e0110 / 0x9e0230 / 0x9e0330 / 0x9e04e0 / 0x9e1990
    void insert(T* pos, const T& v);                                   // 0x9e0b20
    void push_back(const T& v) {
        if (e < cap) {
            T* p = e++;
            if (p) ::new((void*)p) T(v);
        } else {
            realloc_insert(e, v);
        }
    }
};

struct Gait {                                                          // 0x40
    int          id;                                                   // +0x00
    Vec<GaitA>   a;                                                    // +0x04
    Vec<GaitB>   b;                                                    // +0x18
    Vec<GaitC>   c;                                                    // +0x2c
    Gait();                                                            // 0x009e1030
    Gait(const Gait& o);                                               // 0x009e1100
};

// ------------------------------------------------------------------ record / holders / owner

struct Inner {                                                         // owner's per-entry data
    int        f0;                                                     // +0x00
    float      f4;                                                     // +0x04
    int        f8;                                                     // +0x08
    Vec<Item>  items;                                                  // +0x0c
    Vec<Gait>  gaits;                                                  // +0x20

    void AssignItemsN(const Inner* o, uint32 n);                       // 0x009e1160
    void AssignItemsF(const Inner* o, uint32 flags);                   // 0x009e1260
    void AssignItems(const Inner* o);                                  // 0x009e1370
    void Combine(const Inner* a, float f, const Inner* b);             // 0x009e1470
};

struct Record {                                                        // 0x150
    GaitC       gaitC;                                                 // +0x000
    GaitB       gaitB;                                                 // +0x01c
    GaitA       gaitA;                                                 // +0x074
    int         maxC;                                                  // +0x0b8
    int         maxB;                                                  // +0x0bc
    int         maxA;                                                  // +0x0c0
    int         kind;                                                  // +0x0c4
    int         flag;                                                  // +0x0c8
    int         pad0cc;                                                // +0x0cc
    Gait        gait;                                                  // +0x0d0
    Item        item;                                                  // +0x110
    int         pad11c[3];                                             // +0x11c
    Vec<Item>   items;                                                 // +0x128
    Vec<Gait>   gaits;                                                 // +0x13c
};

struct Holder {                                                        // +0x04 = Record*
    int          f00;                                                  // +0x00
    void*        val;                                                  // +0x04
    Vec<void*>   v1;                                                   // +0x08
    Vec<void*>   v2;                                                   // +0x1c
};

struct Outer {                                                         // this
    int      pad00;                                                    // +0x00
    void*    eval;                                                     // +0x04
    int      pad08;                                                    // +0x08
    Holder*  hC;                                                       // +0x0c
    int      pad10[8];                                                 // +0x10
    Holder*  h30;                                                      // +0x30

    void AddGait(void* arg);                                           // 0x009e0d90
    void AddItem(void* arg);                                           // 0x009e0f80
    void PushFlag(bool flag);                                          // 0x009e0ff0
    void Select(void* arg);                                            // 0x009e1b40
    void PushGait(bool flag);                                          // 0x009e1cd0
};

// ---- ItemArr / Src ---------------------------------------------------------

struct ItemArr {                                                       // 0x18
    uint32           count;                                            // +0x00
    Vec<GaitItem>    v;                                                // +0x04
    void Add(const GaitItem* value);                                   // 0x009e1610
    void Build(const void* src);                                       // 0x009e1760
};

struct RPair { float a, b; };

// ---- RB tree --------------------------------------------------------------

struct RBNode {
    RBNode* c0;                                                        // +0x00
    RBNode* c4;                                                        // +0x04
    RBNode* par;                                                       // +0x08
    int     color;                                                     // +0x0c
    uint32  key;                                                       // +0x10
    void*   value;                                                     // +0x14
};

struct RBTree {
    int      f00;                                                      // +0x00
    RBNode*  sentinel;                                                 // +0x04 (its address is the sentinel)
    int      f08;                                                      // +0x08
    RBNode*  root;                                                     // +0x0c

    // A parameter is copied only when it is (potentially) modified; referencing it through a
    // pointer forces the copy the original performs.  The 3rd argument of RBTree0::Insert is
    // the node *payload* pointer (0x009e0c00 writes the key through it); the original stores
    // `&params` there, i.e. the address of its saved-parameters area.
    void** find_or_insert(volatile const uint32* key);                 // 0x009e17d0
    void   FindNode(RBNode** keyOut, const uint32* key);               // 0x00e5c780 (this=p2, edx=p3)
};

// ------------------------------------------------------------------ @ 0x009e0d90

// @ 0x009e0d90
void Outer::AddGait(void* arg)
{
    Record* rec = (Record*)hC->val;
    switch (rec->kind) {
    case 0: {
        void** a = ((CArgs*)arg)->MainArguments(6);
        for (int off = 0x88; off < 0xb8; off += 0x10)
            for (int j = 0; j < 2; j++)
                *(float*)((char*)hC->val + off + 4 * j) =
                    ((float (__thiscall*)(void*, void*))(*(void***)eval)[0x98 / 4])(eval, *(a++));
        rec->gait.a.push_back(rec->gaitA);
        break;
    }
    case 1: {
        void** a = ((CArgs*)arg)->MainArguments(8);
        for (int off = 0x34; off < 0x74; off += 0x10)
            for (int j = 0; j < 2; j++)
                *(float*)((char*)hC->val + off + 4 * j) =
                    ((float (__thiscall*)(void*, void*))(*(void***)eval)[0x98 / 4])(eval, *(a++));
        rec->gait.b.push_back(rec->gaitB);
        break;
    }
    case 2: {
        void** a = ((CArgs*)arg)->MainArguments(2);
        for (int off = 0xc; off < 0x14; off += 4)
            *(float*)((char*)hC->val + off) =
                ((float (__thiscall*)(void*, void*))(*(void***)eval)[0x98 / 4])(eval, *(void**)((char*)a + off - 0xc));
        rec->gait.c.push_back(rec->gaitC);
        break;
    }
    }
}

// ------------------------------------------------------------------ @ 0x009e0f80

// @ 0x009e0f80
void Outer::AddItem(void* arg)
{
    void** a = ((CArgs*)arg)->MainArguments(1);
    Record* rec = (Record*)hC->val;
    rec->item.b = ((float (__thiscall*)(void*, void*))(*(void***)eval)[0x98 / 4])(eval, a[0]);
    rec->items.push_back(rec->item);
}

// ------------------------------------------------------------------ @ 0x009e0ff0

// @ 0x009e0ff0
void Outer::PushFlag(bool flag)
{
    if (!flag)
        h30->v1.push_back(h30->val);
}

// ------------------------------------------------------------------ @ 0x009e1030

// @ 0x009e1030
Gait::Gait()
{
    float f = g_gait_default_id;
    id = (int)f;
    CopyA(a.e, a.e, a.b);
    a.e += a.e - a.b;
    CopyB(b.e, b.e, b.b);
    b.e += b.e - b.b;
    CopyC(c.e, c.e, c.b);
    c.e += c.e - c.b;
}

// ------------------------------------------------------------------ @ 0x009e1100

// @ 0x009e1100
Gait::Gait(const Gait& o)
{
    id = o.id;
    a = o.a;
    b = o.b;
    c = o.c;
}

// ------------------------------------------------------------------ @ 0x009e1160

// @ 0x009e1160
void Inner::AssignItemsN(const Inner* o, uint32 n)
{
    uint32 myCount = (uint32)(items.e - items.b);
    uint32 oCount  = (uint32)(o->items.e - o->items.b);
    uint32 cp = myCount < oCount ? myCount : oCount;
    for (uint32 i = 0; i < cp; i++)
        items.b[i] = o->items.b[i];
    uint32 m = oCount < n ? oCount : n;
    items.reserve((int)m);
    for (uint32 i = cp; i < m; i++)
        items.push_back(o->items.b[i]);
}

// ------------------------------------------------------------------ @ 0x009e1260

// @ 0x009e1260
void Inner::AssignItemsF(const Inner* o, uint32 flags)
{
    uint32 myCount = (uint32)(items.e - items.b);
    uint32 oCount  = (uint32)(o->items.e - o->items.b);
    uint32 cp = myCount < oCount ? myCount : oCount;
    if (oCount < myCount) {
        for (uint32 i = oCount; i < myCount; i++)
            --items.e;
    }
    if (!(flags & 2)) {
        for (uint32 i = 0; i < cp; i++)
            items.b[i] = o->items.b[i];
    }
    items.reserve((int)oCount);
    for (uint32 i = cp; i < oCount; i++)
        items.push_back(o->items.b[i]);
}

// ------------------------------------------------------------------ @ 0x009e1370

// @ 0x009e1370
void Inner::AssignItems(const Inner* o)
{
    uint32 myCount = (uint32)(items.e - items.b);
    uint32 oCount  = (uint32)(o->items.e - o->items.b);
    uint32 cp = myCount < oCount ? myCount : oCount;
    if (oCount < myCount) {
        for (uint32 i = oCount; i < myCount; i++)
            --items.e;
    }
    for (uint32 i = 0; i < cp; i++)
        items.b[i] = o->items.b[i];
    items.reserve((int)oCount);
    for (uint32 i = cp; i < oCount; i++)
        items.push_back(o->items.b[i]);
}

// ------------------------------------------------------------------ @ 0x009e1470

// @ 0x009e1470
void Inner::Combine(const Inner* a, float f, const Inner* b)
{
    f8 = a->f8 < b->f8 ? b->f8 : a->f8;

    uint32 myCount = (uint32)(items.e - items.b);
    uint32 aCount  = (uint32)(a->items.e - a->items.b);
    uint32 bCount  = (uint32)(b->items.e - b->items.b);
    uint32 m = aCount < bCount ? aCount : bCount;
    uint32 n = m < myCount ? m : myCount;

    if (m < myCount) {
        for (uint32 i = m; i < myCount; i++)
            --items.e;
    }
    if (!(f0 & 2)) {
        for (uint32 i = 0; i < n; i++)
            ((Combiner*)this)->Combine5(&items.b[i], i, a, f, b);
    }
    items.reserve((int)m);
    for (uint32 i = myCount; i < m; i++) {
        Item it;
        it.a = 0.0f;
        it.b = 0.5f;
        it.c = 0;
        ((Combiner*)this)->Combine5(&it, i, a, f, b);
        items.push_back(it);
    }
}

// ------------------------------------------------------------------ @ 0x009e1610

// @ 0x009e1610
void ItemArr::Add(const GaitItem* value)
{
    uint32 count = this->count;
    uint32 i = 0;
    for (; i < count; i++) {
        if (!(v.b[i].a < value->a))
            break;
    }
    if (i < count && v.b[i].a == value->a) {
        v.b[i] = *value;
    } else {
        v.insert(v.b + i, *value);
        this->count++;
    }
}

// ------------------------------------------------------------------ @ 0x009e1690

// @ 0x009e1690
Gait* UninitCopyGait(const Gait* first, const Gait* last, Gait* result)
{
    while (first != last) {
        result->a.b = result->a.e = result->a.cap = 0;
        result->b.b = result->b.e = result->b.cap = 0;
        result->c.b = result->c.e = result->c.cap = 0;
        result->id = first->id;
        result->a = first->a;
        result->b = first->b;
        result->c = first->c;
        ++first;
        ++result;
    }
    return result;
}

// ------------------------------------------------------------------ @ 0x009e1710

struct ElemA4;
struct VRange { void DestroyRangeA4n(ElemA4* first, ElemA4* last); };  // 0x009e0b90 member

struct RecBlob {                                                        // 0x30
    int      f00;                                                       // +0x00
    void*    p04;                                                       // +0x04
    int      pad08[5];                                                  // +0x08
    ElemA4*  vb;                                                        // +0x1c
    ElemA4*  ve;                                                        // +0x20
    ElemA4*  vcap;                                                      // +0x24
    int      alloc[2];                                                  // +0x28
    ~RecBlob();
};

// @ 0x009e1710
RecBlob::~RecBlob()
{
    ((VRange*)&vb)->DestroyRangeA4n(vb, ve);
    if (vb && ((int*)vb)[-1] != 0)
        operator delete[](vb);
    if (p04 && ((int*)p04)[-1] != 0)
        operator delete[](p04);
}

// ------------------------------------------------------------------ @ 0x009e1760

// @ 0x009e1760
void ItemArr::Build(const void* src)
{
    const uint32 n = *(const uint32*)((const char*)src + 0x10);
    const RPair* pairs = (const RPair*)((const char*)src + 0x18);
    v.reserve((int)n);
    for (uint32 i = 0; i < n; i++) {
        GaitItem it;
        it.a = pairs[i].a;
        it.b = pairs[i].b;
        Add(&it);
    }
}

// ------------------------------------------------------------------ @ 0x009e17d0

// @ 0x009e17d0
void** RBTree::find_or_insert(volatile const uint32* key)
{
    RBNode* sentinel = (RBNode*)((char*)this + 4);
    RBNode* x = root;
    RBNode* y = sentinel;
    uint32 k = *key;
    while (x) {
        if (x->key >= k) {
            y = x;
            x = x->c4;
        } else {
            x = x->c0;
        }
    }
    if (y != sentinel && y->key <= k)
        return &y->value;

    RBNode* n = y;
    RBNode* saved = y;
    uint32 kc[2] = { k, 0 };
    const volatile uint32* kp = key;
    ((RBTree0*)this)->Insert(&n, saved, kc, (int)(size_t)kp);
    return &n->value;
}

// ------------------------------------------------------------------ @ 0x009e1850

// @ 0x009e1850
void* __stdcall FindOrCreate(const char* name, uint32 hash)
{
    RBTree* map = (RBTree*)g_name_map;
    RBNode* out = (RBNode*)((char*)map + 4);
    RBNode** pout = &out;
    const char* nm = name;
    map->FindNode(pout, (const uint32*)&hash);
    if (out != (RBNode*)((char*)map + 4)) {
        void* v = out->value;
        if (v)
            return v;
    }
    void* obj = CreateByName(hash);
    if (obj) {
        void** slot = map->find_or_insert(&hash);
        *slot = obj;
        return obj;
    }
    return 0;
}

// ------------------------------------------------------------------ @ 0x009e18c0

struct GaitLoader { void* LoadGaitFile(const char* name, int, int); };

// @ 0x009e18c0
void* GaitLoader::LoadGaitFile(const char* name, int, int)
{
    uint32 h = HashName(name, 0x811c9dc5u, 1);
    return FindOrCreate(name, h);
}

// ------------------------------------------------------------------ @ 0x009e1990

// @ 0x009e1990
void Vec<Gait>::realloc_insert(Gait* pos, const Gait& value)
{
    if (e != cap) {
        Gait* pv = (Gait*)&value;
        if (pv >= pos && pv < e)
            ++pv;
        if (e)
            ::new((void*)e) Gait(*(e - 1));
        GaitRangeHelper(pos, e - 1, e);
        if (pos != pv)
            *pos = *pv;
        ++e;
        return;
    }

    uint32 n = (uint32)(e - b);
    n = (n == 0) ? 1 : n * 2;
    Gait* p = n ? (Gait*)operator_new(n * 0x40, g_alloc_name_anim_gait, 0, 0,
                                     g_alloc_file_eastl, 0xd1) : (Gait*)0;
    Gait* i = UninitCopyGait(b, pos, p);
    if (i)
        ::new((void*)i) Gait(value);
    Gait* j = UninitCopyGait(pos, e, i + 1);
    if (b && ((int*)b)[-1] != 0)
        operator delete[](b);
    b = p;
    e = j;
    cap = p + n;
}

// ------------------------------------------------------------------ @ 0x009e1b40

// @ 0x009e1b40
void Outer::Select(void* arg)
{
    Record* rec = (Record*)hC->val;
    int aCount = (int)(rec->gait.a.e - rec->gait.a.b);
    int bCount = (int)(rec->gait.b.e - rec->gait.b.b);
    int cCount = (int)(rec->gait.c.e - rec->gait.c.b);
    if (aCount < rec->maxA) {
        rec->kind = 0;
    } else if (bCount < rec->maxB) {
        rec->kind = 1;
    } else if (cCount < rec->maxC) {
        rec->kind = 2;
    } else {
        rec->gaits.push_back(rec->gait);
        rec->gait.a.clear();
        rec->gait.b.clear();
        rec->gait.c.clear();
        rec->kind = 0;
    }

    void** a = ((CArgs*)arg)->MainArguments(1);
    float fv = ((float (__thiscall*)(void*, void*))(*(void***)eval)[0x98 / 4])(eval, a[0]);
    int id = (int)fv;

    int k = rec->kind;
    if (k == 0)
        rec->gaitA.id = id;
    else if (k == 1)
        rec->gaitB.id = id;
    else
        rec->gaitC.id = id;
}

// ------------------------------------------------------------------ @ 0x009e1cd0

// @ 0x009e1cd0
void Outer::PushGait(bool flag)
{
    if (flag)
        return;
    Record* rec = (Record*)h30->val;
    if (rec->flag == 0) {
        h30->v2.push_back(h30->val);
        return;
    }
    rec->gaits.push_back(rec->gait);
    h30->v2.push_back(h30->val);
    rec->gait.a.clear();
    rec->gait.b.clear();
    rec->gait.c.clear();
}
