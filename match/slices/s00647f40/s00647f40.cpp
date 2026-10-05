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
    void Construct(const Entry14& v);
};
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
// Functions whose helper contract could not be recovered within budget;
// reconstructed only in outline and listed in partial.txt.
// ---------------------------------------------------------------------------
// @ 0x00647f40
void __cdecl sub_647f40() {}
// @ 0x006483d0
void __cdecl sub_6483d0() {}
// @ 0x006485e0
void __cdecl sub_6485e0() {}
// @ 0x00648730
void __cdecl sub_648730() {}
// @ 0x00648aa0
void __cdecl sub_648aa0() {}
// @ 0x00648b40
void __cdecl sub_648b40() {}
// @ 0x00648bb0
void __cdecl sub_648bb0() {}
// @ 0x00648c60
void __cdecl sub_648c60() {}
// @ 0x00648ce0
void __cdecl sub_648ce0() {}
