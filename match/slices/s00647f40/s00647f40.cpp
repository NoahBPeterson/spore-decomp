// Slice s00647f40 -- cSPUIAssetGrid sorting / grid-entry vector + map helpers.
// Module flags: /O2 /MD /Gy /TP (EASTL template instances).
#include "types.h"

// Refcounted object whose Release sits on a secondary base at +0x10.
struct Primary {
    virtual void p0();
    uint8_t pad[0xc];
};
struct IRef2 {
    virtual void AddRef();
    virtual void Release();
};
struct RefObj : Primary, IRef2 {};

struct AutoRefObj {
    RefObj* p;
    AutoRefObj() : p(0) {}
    ~AutoRefObj() { if (p) p->Release(); }
};
struct AutoRef {
    IRef2* p;
    ~AutoRef() { if (p) p->Release(); }
};
// 0x14-byte vector element with two refcounted handles.
struct Entry14 {
    uint32_t f00, f04, f08;
    AutoRef  h0c;   // +0xc  (primary base)
    AutoRefObj h10; // +0x10 (secondary base)
    void Construct(const Entry14& v);      // 0x645390: copy whole element
    void AssignHandles(const Entry14& v);  // 0x645db0: assign the two handles (this=&h0c)
};

// Sort key of a grid entry: (f00, then f08, then f04).
inline bool EntryLess(const Entry14& a, const Entry14& b)
{
    if (a.f00 == b.f00) {
        if (a.f08 == b.f08)
            return a.f04 < b.f04;
        return a.f08 < b.f08;
    }
    return a.f00 < b.f00;
}
struct Key12 { uint32_t a, b, c; };

struct GridVec {
    Entry14* mpBegin;
    Entry14* mpEnd;
    Entry14* mpCapacity;
    uint32_t mFieldC;    // +0xc
    uint32_t mField10;   // +0x10
    uint8_t  mField14;   // +0x14

    Entry14* EraseAt(Entry14* pos);   // 0x648af0
    Entry14* Insert(Entry14* pos, const Entry14& v); // 0x648b40
    void InsertAt(Entry14* pos, const Entry14& v);   // 0x6485e0 (declared)
    Entry14* InsertSorted(Entry14* pos, const Entry14& v); // 0x648c60 (declared)
    Entry14* FindOrInsert(const Key12& k);           // 0x648ce0
    void GrowTo(unsigned int n);                     // 0x648bb0
    void ClearAssetViews();                          // 0x648aa0
    void DoInsertValuesEnd(Entry14* pos, unsigned int n, const Entry14& v); // 0x6483d0
};

extern "C" Entry14* __cdecl f646140(Entry14* a, Entry14* b, Entry14* c);   // move range
extern "C" Entry14* __cdecl f646030(Entry14* first, Entry14* last, const Key12* key, uint8_t flag);

// @ 0x00648af0
Entry14* GridVec::EraseAt(Entry14* pos) {
    if (pos + 1 < mpEnd)
        f646140(pos + 1, mpEnd, pos);
    --mpEnd;
    Entry14* const e = mpEnd;
    RefObj* const p10 = e->h10.p;
    if (p10)
        p10->Release();
    IRef2* const pC = e->h0c.p;
    if (pC)
        pC->Release();
    return pos;
}

// @ 0x00648b40
Entry14* GridVec::Insert(Entry14* pos, const Entry14& v) {
    const uint32_t idx = (uint32_t)(pos - mpBegin);
    Entry14* const end = mpEnd;
    if ((pos == end) && (end != mpCapacity)) {
        mpEnd = end + 1;
        if (end)
            end->Construct(v);
    } else {
        InsertAt(pos, v);
    }
    return mpBegin + idx;
}

// @ 0x00648ce0
Entry14* GridVec::FindOrInsert(const Key12& k) {
    Entry14* const end = mpEnd;
    Entry14* p = f646030(mpBegin, end, &k, mField14);
    if (p != end) {
        bool less;
        if (k.a == p->f00) {
            if (k.c == p->f08)
                less = k.b < p->f04;
            else
                less = k.c < p->f08;
        } else {
            less = k.a < p->f00;
        }
        if (!less)
            return (Entry14*)((char*)p + 0xc);
    }
    Entry14 value;
    value.f00 = k.a;
    value.f04 = k.b;
    value.f08 = k.c;
    value.h0c.p = 0;
    value.h10.p = 0;
    Entry14* r = InsertSorted(p, value);
    return (Entry14*)((char*)r + 0xc);
}

// ---------------------------------------------------------------------------
// Grid-vector algorithm helpers (EASTL instances and the vector's own
// insert/fill machinery).  Each is reconstructed from its own body.
// ---------------------------------------------------------------------------
extern "C" void* operator_new(unsigned int n, const char* tag, int a, int b, const char* file, int line); // 0xf473a0
extern "C" void  operator_delete(void* p);                                                                // 0xf47380

// Raw element helpers of the 0x14-byte grid entry.  Copy/AssignHandles carry
// their destination in ECX (stub classes make that `this` explicit); the range
// helpers are plain cdecl.
struct EntryOps {
    Entry14* Copy(const Entry14* src);                 // 0x645390 (this = dst)
    void     AssignHandles(const void* src);           // 0x645db0 (this = &dst->h0c)
};
struct GridOps {
    void DestroyRange(Entry14* first, Entry14* last);  // 0x645ff0 (this = GridVec)
    void Sift(Entry14* first, Entry14* last);          // 0x648380 (this = GridVec)
};
extern "C" void     f6453e0(void* out, Entry14* first, Entry14* last, Entry14* dest);    // write dest to *out, copy range
extern "C" Entry14* f645450(Entry14* first, Entry14* last, Entry14* dst);                // UninitCopy
extern "C" void     f6454c0(Entry14* first, Entry14* last, Entry14* dst);                // DestroyRange
extern "C" void     f645510(Entry14* dst, unsigned int n, const Entry14* v);             // UninitFillN
extern "C" Entry14* f6461d0(Entry14* dstEnd, Entry14* first, Entry14* last);             // move backward
extern "C" void     f6460b0(Entry14* first, Entry14* last, const Entry14* v);            // assign v over range

// @ 0x00648bb0
void GridVec::GrowTo(unsigned int n)
{
    if (n > (unsigned int)(mpEnd - mpBegin)) {
        Entry14 value;
        value.f00 = 0;
        value.f04 = 0;
        value.f08 = 0;
        value.h0c.p = 0;
        value.h10.p = 0;
        DoInsertValuesEnd(mpEnd, n - (unsigned int)(mpEnd - mpBegin), value);
    } else {
        reinterpret_cast<GridOps*>(this)->Sift(mpBegin + n, mpEnd);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00648aa0  drop every asset view: shift nothing, destroy the whole range
// ---------------------------------------------------------------------------
// @ 0x00648aa0
void GridVec::ClearAssetViews()
{
    Entry14* first = mpBegin;
    Entry14* last = mpEnd;
    Entry14* moved = f646140(last, last, first);
    reinterpret_cast<GridOps*>(this)->DestroyRange(moved, mpEnd);
    mpEnd -= last - first;
}

// @ 0x00648c60  insert v at pos keeping order (GridVec::InsertSorted)
Entry14* GridVec::InsertSorted(Entry14* pos, const Entry14& v)
{
    Entry14* const end = mpEnd;
    bool less = false;
    if (pos != end)
        less = EntryLess(v, *pos);
    Entry14* where = less
        ? f646030(mpBegin, pos, (const Key12*)&v, mField14)
        : f646030(pos, end, (const Key12*)&v, mField14);
    if (where != end) {
        if (!EntryLess(v, *where))
            return where;
    }
    return Insert(where, v);
}

// ---------------------------------------------------------------------------
// @ 0x006485e0  insert v before pos, growing the buffer if it is full
// ---------------------------------------------------------------------------
void GridVec::InsertAt(Entry14* pos, const Entry14& v)
{
    if (mpEnd != mpCapacity) {
        const Entry14* value = &v;
        if (!(value < pos) && value < mpEnd)
            value = value + 1;
        if (mpEnd)
            reinterpret_cast<EntryOps*>(mpEnd)->Copy(mpEnd - 1);
        f6461d0(pos, mpEnd - 1, mpEnd);
        pos->f00 = value->f00;
        pos->f04 = value->f04;
        pos->f08 = value->f08;
        reinterpret_cast<EntryOps*>(&pos->h0c)->AssignHandles(&value->h0c);
        mpEnd += 1;
        return;
    }
    const unsigned int oldSize = (unsigned int)(mpEnd - mpBegin);
    unsigned int newCapacity = oldSize ? oldSize * 2 : 1;
    Entry14* pNew;
    if (newCapacity)
        pNew = (Entry14*)operator_new(newCapacity * 0x14, "Editor", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    else
        pNew = 0;
    Entry14* pNewEnd = f645450(mpBegin, pos, pNew);
    f6454c0(mpBegin, pos, pNew);
    if (pNewEnd)
        reinterpret_cast<EntryOps*>(pNewEnd)->Copy(&v);
    Entry14* const oldEnd = mpEnd;
    Entry14* pNewEnd2 = f645450(pos, oldEnd, pNewEnd + 1);
    f6454c0(pos, oldEnd, pNewEnd + 1);
    if (mpBegin)
        operator_delete(mpBegin);
    mpEnd = pNewEnd2;
    mpBegin = pNew;
    mpCapacity = pNew + newCapacity;
}

// ---------------------------------------------------------------------------
// @ 0x006483d0  fill-insert n copies of v at pos (DoInsertValuesEnd / resize)
// ---------------------------------------------------------------------------
void GridVec::DoInsertValuesEnd(Entry14* pos, unsigned int n, const Entry14& v)
{
    if ((unsigned int)(mpCapacity - mpEnd) < n) {
        const unsigned int oldSize = (unsigned int)(mpEnd - mpBegin);
        unsigned int newCapacity = oldSize ? oldSize * 2 : 1;
        unsigned int want = oldSize + n;
        if (want < newCapacity)
            want = newCapacity;
        Entry14* pNew;
        if (want)
            pNew = (Entry14*)operator_new(want * 0x14, "Editor", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        else
            pNew = 0;
        Entry14* pNewEnd = f645450(mpBegin, pos, pNew);
        f6454c0(mpBegin, pos, pNew);
        f645510(pNewEnd, n, &v);
        Entry14* pFillEnd = pNewEnd + n;
        Entry14* const oldEnd = mpEnd;
        Entry14* pNewEnd2 = f645450(pos, oldEnd, pFillEnd);
        f6454c0(pos, oldEnd, pFillEnd);
        if (mpBegin)
            operator_delete(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd2;
        mpCapacity = pNew + want;
    } else if (n != 0) {
        Entry14 local;
        reinterpret_cast<EntryOps*>(&local)->Copy(&v);
        const unsigned int elemsAfter = (unsigned int)(mpEnd - pos);
        if (n < elemsAfter) {
            Entry14* const oldEnd = mpEnd;
            Entry14* const pSplit = oldEnd - n;
            Entry14* pOut;
            f6453e0(&pOut, pSplit, oldEnd, oldEnd);
            mpEnd += n;
            f6461d0(pOut, pSplit, oldEnd);
            f6460b0(pOut, pOut + n, &local);
        } else {
            f645510(mpEnd, n - elemsAfter, &local);
            const unsigned int added = n - elemsAfter;
            Entry14* const oldEnd = mpEnd;
            Entry14* pOut2;
            mpEnd += added;
            f6453e0(&pOut2, pos, oldEnd, mpEnd);
            mpEnd += elemsAfter;
            f6460b0(pos, oldEnd, &local);
        }
        if (local.h10.p)
            local.h10.p->Release();
        if (local.h0c.p)
            local.h0c.p->Release();
    }
}

// ===========================================================================
// cSPUIAssetGrid itself: the destructor and constructor walk a large class
// whose members are all reached at their real offsets.  `this` is the object;
// AT(T, off) names each field at its byte offset.
// ===========================================================================
#define AT(T, off) (*(T*)((char*)this + (off)))
#define VSLOT(o, byteoff) ((*(void***)(o))[(byteoff) / 4])
typedef void (__thiscall *Fn_v0)(void*);

extern "C" void EA_RemoveHandler(void* h, void* a, void* b, void* c, void* d);   // 0x571db0
extern "C" void DoFreeNodes34(void* buckets, unsigned int n);                    // 0x961d60
extern "C" void DoFreeBucketsVoidP(void* buckets, unsigned int n);               // 0x693230
extern "C" void FUN_0093a560();        // EA::Stopwatch::Stopwatch(this, units, running)  @ 0x93a560
extern "C" void FUN_0066a5e0();        // FlagKey::FlagKey(this, fill, value)              @ 0x66a5e0
extern uint32_t g_140042c;             // 0x0140042c: value word written into a fresh FlagKey
extern void* gEmptyBucketArray;                                                  // 0x154df28 (empty hashtable sentinel)

struct cSPUIAssetGrid {
    void Dtor();       // @ 0x00647f40
    void* Ctor();      // @ 0x00648730
};

// ---------------------------------------------------------------------------
// @ 0x00647f40  cSPUIAssetGrid::~cSPUIAssetGrid
// ---------------------------------------------------------------------------
void cSPUIAssetGrid::Dtor()
{
    AT(void*, 0) = (void*)0x13ff844;
    AT(void*, 4) = (void*)0x13ff838;
    AT(void*, 8) = (void*)0x13ff81c;
    AT(void*, 0xc) = (void*)0x13ff80c;
    for (;;) {
        void* p;
        p = AT(void*, 0x228); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x224); if (p) { ((Fn_v0)VSLOT(p, 8))(p); }
        p = AT(void*, 0x220); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x21c); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x218); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x1bc); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x1b4); if (p) { ((Fn_v0)VSLOT(p, 8))(p); }
        p = AT(void*, 0x1b0); if (p) { ((Fn_v0)VSLOT(p, 8))(p); }
        p = AT(void*, 0x194); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        if (AT(void*, 0x180)) {
            EA_RemoveHandler(AT(void*, 0x180), AT(void*, 0x184), AT(void*, 0x188),
                             AT(void*, 0x18c), AT(void*, 0x190));
            AT(void*, 0x180) = 0;
        }
        p = AT(void*, 0x17c); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        break;
    }
    DoFreeNodes34(AT(void*, 0x160), AT(unsigned int, 0x164));
    AT(unsigned int, 0x168) = 0;
    if (AT(unsigned int, 0x164) > 1)
        operator_delete(AT(void*, 0x160));
    if (AT(void*, 0x158)) ((Fn_v0)VSLOT(AT(void*, 0x158), 4))(AT(void*, 0x158));
    DoFreeNodes34(AT(void*, 0x13c), AT(unsigned int, 0x140));
    AT(unsigned int, 0x144) = 0;
    if (AT(unsigned int, 0x140) > 1)
        operator_delete(AT(void*, 0x13c));
    DoFreeBucketsVoidP(AT(void*, 0x11c), AT(unsigned int, 0x120));
    AT(unsigned int, 0x124) = 0;
    if (AT(unsigned int, 0x120) > 1)
        operator_delete(AT(void*, 0x11c));
    DoFreeBucketsVoidP(AT(void*, 0xfc), AT(unsigned int, 0x100));
    AT(unsigned int, 0x104) = 0;
    if (AT(unsigned int, 0x100) > 1)
        operator_delete(AT(void*, 0xfc));
    if (AT(void*, 0xe4) && *(uint32_t*)((char*)AT(void*, 0xe4) - 4))
        operator_delete(AT(void*, 0xe4));
    reinterpret_cast<GridOps*>(this)->DestroyRange(AT(Entry14*, 0xcc), AT(Entry14*, 0xd0));
    if (AT(void*, 0xcc))
        operator_delete(AT(void*, 0xcc));
    for (;;) {
        void* p;
        p = AT(void*, 0xc8); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xc4); if (p) { ((Fn_v0)VSLOT(p, 8))(p); }
        p = AT(void*, 0xc0); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xbc); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xb8); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xb4); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xb0); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xac); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xa8); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xa4); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xa0); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x9c); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x98); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x94); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x90); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x8c); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x88); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x84); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x80); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x7c); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x78); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x74); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x70); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x6c); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x68); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x64); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x60); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x5c); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x58); if (p) { ((Fn_v0)VSLOT(p, 8))(p); }
        p = AT(void*, 0x18); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        break;
    }
    AT(void*, 0xc) = (void*)0x13ec458;
    AT(void*, 8) = (void*)0x13eb938;
    AT(void*, 0) = (void*)0x13eb394;
}

// ---------------------------------------------------------------------------
// @ 0x00648730  cSPUIAssetGrid::cSPUIAssetGrid
// ---------------------------------------------------------------------------
void* cSPUIAssetGrid::Ctor()
{
    AT(void*, 8) = (void*)0x14426a0;
    AT(void*, 0xc) = (void*)0x13ec458;
    AT(void*, 0x10) = 0;
    AT(void*, 0) = (void*)0x13ff844;
    AT(void*, 4) = (void*)0x13ff838;
    AT(void*, 8) = (void*)0x13ff81c;
    AT(void*, 0xc) = (void*)0x13ff80c;
    AT(void*, 0x14) = 0;
    AT(void*, 0x18) = 0;
    AT(uint8_t, 0x1c) = 0;
    AT(uint8_t, 0x1d) = 0;
    AT(uint8_t, 0x1e) = 0;
    AT(uint8_t, 0x1f) = 0;
    AT(uint32_t, 0x20) = 1;
    AT(uint8_t, 0x24) = 0;
    AT(uint8_t, 0x25) = 0;
    AT(uint8_t, 0x26) = 0;
    AT(uint8_t, 0x27) = 0;
    AT(uint8_t, 0x28) = 0;
    AT(uint8_t, 0x29) = 0;
    AT(uint8_t, 0x2a) = 1;
    AT(float, 0x3c) = 0.0f;
    ((void(__thiscall*)(void*, int, int))FUN_0093a560)((char*)this + 0x40, 4, 0);    AT(void*, 0x58) = 0;
    AT(void*, 0x5c) = 0;
    AT(void*, 0x60) = 0;
    AT(void*, 0x64) = 0;
    AT(void*, 0x68) = 0;
    AT(void*, 0x6c) = 0;
    AT(void*, 0x70) = 0;
    AT(void*, 0x74) = 0;
    AT(void*, 0x78) = 0;
    AT(void*, 0x7c) = 0;
    AT(void*, 0x80) = 0;
    AT(void*, 0x84) = 0;
    AT(void*, 0x88) = 0;
    AT(void*, 0x8c) = 0;
    AT(void*, 0x90) = 0;
    AT(void*, 0x94) = 0;
    AT(void*, 0x98) = 0;
    AT(void*, 0x9c) = 0;
    AT(void*, 0xa0) = 0;
    AT(void*, 0xa4) = 0;
    AT(void*, 0xa8) = 0;
    AT(void*, 0xac) = 0;
    AT(void*, 0xb0) = 0;
    AT(void*, 0xb4) = 0;
    AT(void*, 0xb8) = 0;
    AT(void*, 0xbc) = 0;
    AT(void*, 0xc0) = 0;
    AT(void*, 0xc4) = 0;
    AT(void*, 0xc8) = 0;
    AT(void*, 0xcc) = 0;
    AT(void*, 0xd0) = 0;
    AT(void*, 0xd4) = 0;
    AT(void*, 0xe4) = 0;
    AT(void*, 0xe8) = 0;
    AT(void*, 0xec) = 0;
    AT(float, 0x108) = 1.0f;
    AT(float, 0x10c) = 2.0f;
    AT(uint32_t, 0x100) = 1;
    AT(void*, 0xfc) = &gEmptyBucketArray;
    AT(uint32_t, 0x104) = 0;
    AT(void*, 0x110) = 0;
    AT(float, 0x128) = 1.0f;
    AT(float, 0x12c) = 2.0f;
    AT(uint32_t, 0x120) = 1;
    AT(void*, 0x11c) = &gEmptyBucketArray;
    AT(uint32_t, 0x124) = 0;
    AT(void*, 0x130) = 0;
    AT(float, 0x148) = 1.0f;
    AT(float, 0x14c) = 2.0f;
    AT(uint32_t, 0x140) = 1;
    AT(void*, 0x13c) = &gEmptyBucketArray;
    AT(uint32_t, 0x144) = 0;
    AT(void*, 0x150) = 0;
    AT(void*, 0x158) = 0;
    AT(float, 0x16c) = 1.0f;
    AT(float, 0x170) = 2.0f;
    AT(uint32_t, 0x164) = 1;
    AT(void*, 0x160) = &gEmptyBucketArray;
    AT(uint32_t, 0x168) = 0;
    AT(void*, 0x174) = 0;
    AT(void*, 0x17c) = 0;
    AT(void*, 0x180) = 0;
    AT(void*, 0x184) = 0;
    AT(void*, 0x188) = 0;
    AT(void*, 0x18c) = 0;
    AT(void*, 0x190) = 0;
    AT(void*, 0x194) = 0;
    AT(void*, 0x198) = 0;
    AT(void*, 0x1a0) = 0;
    AT(void*, 0x1a4) = 0;
    AT(void*, 0x1a8) = 0;
    AT(uint8_t, 0x1ac) = 0;
    AT(void*, 0x1b0) = 0;
    AT(void*, 0x1b4) = 0;
    AT(void*, 0x1b8) = 0;
    AT(void*, 0x1bc) = 0;
    AT(void*, 0x1c0) = 0;
    AT(uint8_t, 0x1c4) = 0;
    AT(uint8_t, 0x1c5) = 0;
    AT(uint8_t, 0x1c6) = 0;
    AT(uint8_t, 0x1c7) = 0;
    AT(uint8_t, 0x1c8) = 0;
    AT(void*, 0x1cc) = 0;
    AT(void*, 0x1d0) = 0;
    AT(void*, 0x1d4) = 0;
    AT(void*, 0x1d8) = 0;
    AT(void*, 0x1dc) = 0;
    AT(void*, 0x1e0) = 0;
    AT(void*, 0x1e4) = 0;
    AT(void*, 0x1e8) = 0;
    AT(uint8_t, 0x1ec) = 0;
    AT(uint8_t, 0x1ed) = 0;
    ((void(__thiscall*)(void*, int, uint32_t))FUN_0066a5e0)((char*)this + 0x1f0, 1, g_140042c);
    AT(void*, 0x210) = 0;
    AT(float, 0x214) = 24.0f;
    AT(void*, 0x218) = 0;
    AT(void*, 0x21c) = 0;
    AT(void*, 0x220) = 0;
    AT(void*, 0x224) = 0;
    AT(void*, 0x228) = 0;
    AT(uint32_t, 0x22c) = 1;
    AT(void*, 0x230) = 0;
    AT(uint8_t, 0x234) = 0;
    AT(uint8_t, 0x235) = 0;
    AT(uint8_t, 0x236) = 0;
    AT(void*, 0x238) = 0;
    AT(uint8_t, 0x23c) = 0;
    AT(uint8_t, 0x23d) = 0;
    AT(void*, 0x240) = 0;
    AT(void*, 0x244) = 0;
    AT(void*, 0x248) = 0;
    AT(uint8_t, 0x24c) = 0;
    AT(uint8_t, 0x24d) = 0;
    AT(uint8_t, 0x24e) = 0;
    AT(uint8_t, 0x24f) = 0;
    return this;
}
