// src/game/SPEditors/TraitVector.cpp -- migrated from slice(s) s005718f0, s0056fb90, s005709b0 by tools/migrate/rewrite.py
// Object file: SPEditors/TraitVector.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Traits/cFeatureVector.h"
#include <new>
#include <string.h>
#include <math.h>
#include <intrin.h>

// ---- items of slice s005709b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Allocator { const char* mpName; };
struct Key12 {
    uint32_t mA;
    uint32_t mB;
    float mC;
    bool operator<(const Key12& rhs) const;      // 0x5715d0
    bool operator==(const Key12& rhs) const;     // 0x571610
};
struct KeyVector {
    Key12* mpBegin;
    Key12* mpEnd;
    Key12* mpCapacity;
    Allocator mAllocator;

    ~KeyVector();                                                            // 0x5719a0 (frees the buffer)
    void erase(Key12* first, Key12* last);                                   // 0x50f740
    Key12* insert(Key12* position, const Key12& value);                      // 0x5718f0
};
struct InsertResult {
    Key12* position;      // +0x0
    bool inserted;        // +0x4
    InsertResult(Key12* p, bool b) { position = p; inserted = b; }
};
struct cFeatureVector : KeyVector {
    char pad10[4];                 // +0x10 .. +0x13
    unsigned char mSorted;         // +0x14 (compare/flag byte passed to lower_bound)
    char pad15[3];                 // +0x15 .. +0x17
    float mfLen;                   // +0x18

    cFeatureVector();                                        // 0x571640
    // destruction: run over the elements, then let the base release the buffer.
    ~cFeatureVector()                                        // out of line copy: 0x564470
    {
        for (Key12* p = mpBegin; p < mpEnd; ++p)
            ;
    }
    void clear();                                            // 0x571680
    Key12* begin();                                          // 0x5716c0
    Key12* end();                                            // 0x5716e0
    void ResetResourceType();                                // 0x571700
    void assign(const cFeatureVector& other);                // 0x571720
    float add(const Key12& key, float value);                // 0x571790
    InsertResult insertValue(const Key12& value);            // 0x571840

    // out-of-line callee (0x526430), named from the PDB
    void GetResourceTypeFromModelType();
};
Key12* __cdecl lower_bound(Key12* first, Key12* last, const Key12& value, unsigned char comp);  // 0x571c40
struct WeightPair {
    uint32_t mKey;      // +0x00
    float mVal;         // +0x04
};
struct WeightVector {
    WeightPair* mpBegin;    // +0x00
    WeightPair* mpEnd;      // +0x04
};
struct cTraitQuery {
    char mUnk00[0x1c];              // +0x00
    cFeatureVector mFeatures;       // +0x1c  the query's own feature vector
    WeightVector mWeights;          // +0x38
    char mUnk40[0x10];              // +0x40
    unsigned char mWeighted;        // +0x50  non-zero: weight both inputs first
    char mUnk51[3];                 // +0x51 .. +0x53
    uint32_t mMode;                 // +0x54  similarity operator index

    float Compute(cFeatureVector* a, cFeatureVector* b);   // 0x5709b0
    float Op1(cFeatureVector* a, cFeatureVector* b);       // 0x570c40
    float Op2(cFeatureVector* a, cFeatureVector* b);       // 0x570e50
    float Op3(cFeatureVector* a, cFeatureVector* b);       // 0x571100
};
static const float kfSimilarityError = 4294967296.0f;       // 0x13f4fd0
struct TraitData_s0057_09b0 {
    unsigned char mFlag;                                      // +0x00
    TraitData_s0057_09b0() { mFlag = 0; }
    float Intersect(cFeatureVector* a, cFeatureVector* b);   // 0x005704c0 (ignores this)
};
// ---- items of slice s005709b0 end

// ---- items of slice s0056fb90 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots() { uint32_t s[N]; }
struct SetPair { void* first; void* second; };
struct VectorSetU32 {
    void*    mpBegin;                   // +0
    void*    mpEnd;                     // +4  (0x015e4a20)
    void*    mpCapacity;                // +8
    uint32_t mAllocator;                // +0xc
    void  insert(void* position, const void* value);      // 0x00554020
    void  eraseKey(const void* value);                    // 0x005540d0
    void  equal_range(SetPair* out, const void* value);   // 0x00555980
};
VectorSetU32 g_rigBlockSet;             // 0x015e4a1c
struct Key1c {
    uint32_t a; uint32_t b;
    bool operator<(const Key1c& k) const;    // @ 0x005715d0
    bool operator==(const Key1c& k) const;   // @ 0x00571610
};
struct FeatureVector {
    void*    mpBegin;                   // +0
    void*    mpEnd;                     // +4
    void*    mpCapacity;                // +8
    uint32_t mAllocator;                // +0xc
    void* begin();                      // 0x005716c0
    void* end();                        // 0x005716e0
    void  clear();                      // 0x00571680
    float add(const void* key, float weight);   // 0x00571790 (thiscall ret 8)
};
struct Elem12 {                         // entry of a cFeatureVector: 8-byte key + float
    Key1c key;                          // +0
    float f;                            // +8
};
struct TraitData {                      // object holding two cFeatureVector members
    FeatureVector mBase;                // +0
    char          pad[0x1c - 0x10];     // +0x10
    FeatureVector mExtra;               // +0x1c
    float Intersect(FeatureVector* lhs, FeatureVector* rhs);   // 0x005704c0 (ret 8)
    void  Blend(bool positive, FeatureVector* src, uint32_t amount);   // 0x005708d0 (ret 0xc)
};
// ---- items of slice s0056fb90 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
bool __cdecl IntersectWeights(const cFeatureVector* a, const WeightVector* b);  // 0x00571530 (stays in the slice: not this object's)

// ---- items of slice s005718f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl AllocatorAllocate(Allocator* alloc, uint32_t size, uint32_t align, uint32_t offset);  // 0x42dee0
void  __cdecl AllocatorDeallocate(void* block);                                                    // EASTL_allocator_deallocate
struct Key12_s0057_18f0 {
    uint32_t mA;
    uint32_t mB;
    uint32_t mC;
    bool operator<(const Key12_s0057_18f0& rhs) const;      // 0x5715d0
};
Key12_s0057_18f0* __cdecl UninitializedCopyKey12(Key12_s0057_18f0* first, Key12_s0057_18f0* last, Key12_s0057_18f0* dest);   // 0x50f8b0
inline Key12_s0057_18f0* copy_backward_impl(Key12_s0057_18f0* first, Key12_s0057_18f0* last, Key12_s0057_18f0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
inline Key12_s0057_18f0* copy_backward(Key12_s0057_18f0* first, Key12_s0057_18f0* last, Key12_s0057_18f0* resultEnd)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_backward_impl(first, last, resultEnd);
}
struct KeyVector_s0057_18f0 {
    Key12_s0057_18f0* mpBegin;
    Key12_s0057_18f0* mpEnd;
    Key12_s0057_18f0* mpCapacity;
    Allocator mAllocator;

    inline Key12_s0057_18f0* DoAllocate(uint32_t n) {
        uint32_t reserved[16];   // unused slots of the inlined allocator layers
        return n ? (Key12_s0057_18f0*)AllocatorAllocate(&mAllocator, n * sizeof(Key12_s0057_18f0), 4, 0) : 0;
    }
    inline void deallocate(void* p, uint32_t n) {
        void* q = p;
        AllocatorDeallocate(q);
    }
    inline void DoFree(Key12_s0057_18f0* p, uint32_t n) {
        if (p)
            deallocate(p, n * sizeof(Key12_s0057_18f0));
    }
    ~KeyVector_s0057_18f0();
    Key12_s0057_18f0* insert(Key12_s0057_18f0* position, const Key12_s0057_18f0& value);
    void DoInsertValue(Key12_s0057_18f0* position, const Key12_s0057_18f0& value);
};
struct less_key {
    inline bool operator()(const Key12_s0057_18f0& a, const Key12_s0057_18f0& b) const { return a < b; }
};
inline void advance(Key12_s0057_18f0*& i, int n) { i += n; }
// ---- items of slice s005718f0 end

// @ 0x005704c0
float TraitData::Intersect(FeatureVector* lhs, FeatureVector* rhs)
{
    // Declaration order chosen to reproduce the original /Od slot order.
    ScratchSlots<17>();
    Elem12* itA = (Elem12*)lhs->begin();
    Elem12* endA;
    Elem12* endB;
    Elem12* itB = (Elem12*)rhs->begin();
    endA = (Elem12*)lhs->end();
    endB = (Elem12*)rhs->end();
    float sum = 0.0f;
    while (itA != endA && itB != endB) {
        while (itA != endA && itB != endB && itA->key < itB->key) {
            Elem12* saved1 = itA;
            SetPair pair1;
            g_rigBlockSet.equal_range(&pair1, saved1);
            Elem12* found1 = (pair1.first == pair1.second) ? (Elem12*)g_rigBlockSet.mpEnd : (Elem12*)pair1.first;
            if (found1 != (Elem12*)g_rigBlockSet.mpEnd) {
                sum += saved1->f;
            }
            itA += 1;
        }
        while (itA != endA && itB != endB && itB->key < itA->key) {
            Elem12* saved2 = itB;
            SetPair pair2;
            g_rigBlockSet.equal_range(&pair2, saved2);
            Elem12* found2 = (pair2.first == pair2.second) ? (Elem12*)g_rigBlockSet.mpEnd : (Elem12*)pair2.first;
            if (found2 != (Elem12*)g_rigBlockSet.mpEnd) {
                sum += saved2->f;
            }
            itB += 1;
        }
        while (itA->key == itB->key && itA != endA && itB != endB) {
            Elem12* saved3 = itA;
            float w3 = itB->f;
            SetPair pair3;
            g_rigBlockSet.equal_range(&pair3, saved3);
            Elem12* found3 = (pair3.first == pair3.second) ? (Elem12*)g_rigBlockSet.mpEnd : (Elem12*)pair3.first;
            if (found3 != (Elem12*)g_rigBlockSet.mpEnd) {
                if (w3 > saved3->f) {
                    sum += w3 - saved3->f;
                } else {
                    sum += saved3->f - w3;
                }
            }
            itA += 1;
            itB += 1;
        }
    }
    while (itA != endA && itB == endB) {
        Elem12* saved4 = itA;
        SetPair pair4;
        g_rigBlockSet.equal_range(&pair4, saved4);
        Elem12* found4 = (pair4.first == pair4.second) ? (Elem12*)g_rigBlockSet.mpEnd : (Elem12*)pair4.first;
        if (found4 != (Elem12*)g_rigBlockSet.mpEnd) {
            sum += saved4->f;
        }
        itA += 1;
    }
    for (; itA == endA && itB != endB; itB += 1) {
        Elem12* saved5 = itB;
        SetPair pair5;
        g_rigBlockSet.equal_range(&pair5, saved5);
        Elem12* found5 = (pair5.first == pair5.second) ? (Elem12*)g_rigBlockSet.mpEnd : (Elem12*)pair5.first;
        if (found5 != (Elem12*)g_rigBlockSet.mpEnd) {
            sum += saved5->f;
        }
    }
    return sum;
}

// @ 0x005708d0
void TraitData::Blend(bool positive, FeatureVector* vec, uint32_t amount)
{
    float n30 = 1.0f;
    if (!positive) {
        n30 = -n30;
    }
    Elem12* p30 = (Elem12*)vec->begin();
    Elem12* v = (Elem12*)vec->end();
    for (; p30 != v; p30 += 1) {
        mBase.add(p30, n30);
    }
    mExtra.clear();
    Elem12* t32 = (Elem12*)mBase.begin();
    Elem12* t21 = (Elem12*)mBase.end();
    for (; t32 != t21; t32 += 1) {
        Elem12* b = t32;
        mExtra.add(b, amount / b->f);
    }
}

// @ 0x005709b0
float cTraitQuery::Compute(cFeatureVector* a, cFeatureVector* b)
{
    if (mWeighted == 0)
    {
        switch (mMode)
        {
        case 0:
        {
            TraitData_s0057_09b0 data;
            return data.Intersect(a, b);
        }
        case 1:
            return Op1(a, b);
        case 2:
            return Op2(a, b);
        case 3:
            return Op3(a, b);
        }
        return kfSimilarityError;
    }

    cFeatureVector fa;
    cFeatureVector fb;
    fa.assign(*a);
    fb.assign(*b);
    IntersectWeights(&fa, &mWeights);
    IntersectWeights(&fb, &mWeights);

    switch (mMode)
    {
    case 0:
    {
        TraitData_s0057_09b0 data;
        return data.Intersect(&fa, &fb);
    }
    case 1:
        return Op1(&fa, &fb);
    case 2:
        return Op2(&fa, &fb);
    case 3:
        return Op3(&fa, &fb);
    }
    return kfSimilarityError;
}

// @ 0x00571720
void cFeatureVector::assign(const cFeatureVector& other)
{
    erase(mpBegin, mpEnd);
    for (const Key12* p = other.mpBegin; p != other.mpEnd; ++p)
        insertValue(*p);
    mfLen = other.mfLen;
}

// @ 0x00571790
float cFeatureVector::add(const Key12& key, float value)
{
    float a = fabsf(value);
    if (a <= 1.52587890625e-05f)
        return 0.0f;

    Key12 v;
    v.mA = key.mA;
    v.mB = key.mB;
    v.mC = value;

    InsertResult r = insertValue(v);
    float* pf = (float*)((char*)r.position + 8);
    if (!r.inserted)
        *pf += value;
    mfLen += value;
    return *pf;
}

// @ 0x00571840
InsertResult cFeatureVector::insertValue(const Key12& value)
{
    Key12* pBegin = mpBegin;
    Key12* pEnd = mpEnd;
    Key12* pos = lower_bound(pBegin, pEnd, value, mSorted);
    if (pos != mpEnd && !(value < *pos))
        return InsertResult(pos, false);
    return InsertResult(insert(pos, value), true);
}

// @ 0x005718f0
Key12_s0057_18f0* KeyVector_s0057_18f0::insert(Key12_s0057_18f0* position, const Key12_s0057_18f0& value)
{
    const int n = position - mpBegin;
    if ((position != mpEnd) || (mpEnd == mpCapacity))
        DoInsertValue(position, value);
    else
        ::new(mpEnd++) Key12_s0057_18f0(value);
    return mpBegin + n;
}

// @ 0x005719a0
KeyVector_s0057_18f0::~KeyVector_s0057_18f0()
{
    if (mpBegin)
        deallocate(mpBegin, (uint32_t)(mpCapacity - mpBegin) * sizeof(Key12_s0057_18f0));
}

// @ 0x005719f0
void KeyVector_s0057_18f0::DoInsertValue(Key12_s0057_18f0* position, const Key12_s0057_18f0& value)
{
    if (mpEnd != mpCapacity) {
        const Key12_s0057_18f0* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) Key12_s0057_18f0(*(mpEnd - 1));
        copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        Key12_s0057_18f0* const pNewData = DoAllocate(nNewSize);
        Key12_s0057_18f0* pNewEnd = UninitializedCopyKey12(mpBegin, position, pNewData);
        ::new(pNewEnd) Key12_s0057_18f0(value);
        ++pNewEnd;
        pNewEnd = UninitializedCopyKey12(position, mpEnd, pNewEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00571c40
Key12_s0057_18f0* __cdecl lower_bound(Key12_s0057_18f0* first, Key12_s0057_18f0* last, const Key12_s0057_18f0& value)
{
    int d = last - first;
    while (d > 0) {
        Key12_s0057_18f0* i = first;
        int d2 = d >> 1;
        advance(i, d2);
        less_key compare;
        if (compare(*i, value)) {
            first = ++i;
            d -= d2 + 1;
        } else
            d = d2;
    }
    return first;
}
