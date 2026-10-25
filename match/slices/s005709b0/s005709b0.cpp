// slice s005709b0
// SP::Traits feature-vector helpers. The module is built /Od /Ob1 (spilled `this`,
// every local in memory), like the neighbouring slice s005718f0.
#include <new>
#include <string.h>
#include <math.h>
#include "types.h"

// The retail Op3 tail contains the x87 CRT square-root and arc-cosine: `fld arg; call
// _CIsqrt` / `call _CIacos` with the argument and result on the x87 stack (retail 0x5714d4:
// fld [ebp-0x14]; call 0x11e0738 ... call 0x11e08c8).  Under /arch:SSE (no SSE2) cl lowers
// sqrt(double)/acos(double) to those x87 intrinsics, whereas sqrtf/acosf become cdecl SSE
// libm calls -- so the tail below uses the double forms with a float(result) narrowing, the
// same shape as retail (`fstp tmp; fld tmp`).

// ---------------------------------------------------------------------------
// 12-byte key: {cID (2 x uint32), float}
// ---------------------------------------------------------------------------
struct Allocator { const char* mpName; };

void* __cdecl AllocatorAllocate(Allocator* a, uint32_t size, uint32_t align, uint32_t offset);
void  __cdecl AllocatorDeallocate(void* p);

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

// lower_bound(first, last, value, comp): the 4th arg is an empty comparator
// (cl passes the byte stored in the map and never reads it in the /Od body).
Key12* __cdecl lower_bound(Key12* first, Key12* last, const Key12& value, unsigned char comp);  // 0x571c40

// ---------------------------------------------------------------------------
// @ 0x005715d0
bool Key12::operator<(const Key12& rhs) const
{
    if (mA < rhs.mA)
        return true;
    if (mA != rhs.mA)
        return false;
    return mB < rhs.mB;
}

// ---------------------------------------------------------------------------
// @ 0x00571610
bool Key12::operator==(const Key12& rhs) const
{
    if (mA != rhs.mA)
        return false;
    return mB == rhs.mB;
}

// ---------------------------------------------------------------------------
// @ 0x00571640
cFeatureVector::cFeatureVector()
{
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    mfLen = 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00571680
void cFeatureVector::clear()
{
    erase(mpBegin, mpEnd);
    mfLen = 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x005716c0
Key12* cFeatureVector::begin()
{
    Key12* p = mpBegin;
    return p;
}

// ---------------------------------------------------------------------------
// @ 0x005716e0
Key12* cFeatureVector::end()
{
    Key12* p = mpEnd;
    return p;
}

// ---------------------------------------------------------------------------
// @ 0x00571700
void cFeatureVector::ResetResourceType()
{
    GetResourceTypeFromModelType();
}

// ---------------------------------------------------------------------------
// @ 0x00571720
void cFeatureVector::assign(const cFeatureVector& other)
{
    erase(mpBegin, mpEnd);
    for (const Key12* p = other.mpBegin; p != other.mpEnd; ++p)
        insertValue(*p);
    mfLen = other.mfLen;
}

// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Large /Od dispatch / similarity functions.
// ---------------------------------------------------------------------------
// 8-byte {key, weight} entry of the weight vector (same type as s005709b0_g7.cpp).
struct WeightPair {
    uint32_t mKey;      // +0x00
    float mVal;         // +0x04
};

struct WeightVector {
    WeightPair* mpBegin;    // +0x00
    WeightPair* mpEnd;      // +0x04
};

// @ 0x00571530
// scales every feature of `a` by its lookup weight; false when a key is unknown.
bool __cdecl IntersectWeights(const cFeatureVector* a, const WeightVector* b)
{
    WeightPair* wtIt = b->mpBegin;
    WeightPair* wtEnd = b->mpEnd;
    Key12* it = a->mpBegin;
    Key12* end = a->mpEnd;
    for (; it != end; ++it)
    {
        for (; wtIt != wtEnd && wtIt->mKey < it->mA; ++wtIt)
            ;
        if (wtIt == wtEnd || wtIt->mKey != it->mA)
            return false;
        it->mC = it->mC * wtIt->mVal;
    }
    return true;
}

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

// result reported when the operator index is out of range: (float)0xFFFFFFFF
static const float kfSimilarityError = 4294967296.0f;       // 0x13f4fd0

// 0x555980 returns [position, position+1) when the key is present, else
// [position, position); the callers keep the result in an 8-byte local.
struct Range { Key12* first; Key12* second; };

struct cTraitSet : cFeatureVector {
    Range FUN_00555980(const Key12& key);    // 0x00555980  equal_range
};
extern cTraitSet g_traitSet_15e4a1c;          // 0x15e4a1c  global trait-frequency set

struct TraitData {
    unsigned char mFlag;                                      // +0x00
    TraitData() { mFlag = 0; }
    float Intersect(cFeatureVector* a, cFeatureVector* b);   // 0x005704c0 (ignores this)
};

// @ 0x005709b0
float cTraitQuery::Compute(cFeatureVector* a, cFeatureVector* b)
{
    if (mWeighted == 0)
    {
        switch (mMode)
        {
        case 0:
        {
            TraitData data;
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
        TraitData data;
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

// @ 0x00570c40
float cTraitQuery::Op1(cFeatureVector* a, cFeatureVector* b)
{
    Key12* itA = a->begin();
    Key12* itB = b->begin();
    Key12* endA = a->end();
    Key12* endB = b->end();
    float acc = 0.0f;
    Key12* it = mFeatures.begin();
    Key12* end = mFeatures.end();

    for (; it != end; ++it)
    {
        Key12* cur = it;
        float wA = 0.0f;
        float wB = 0.0f;

        if (itA != endA && *itA < *cur)
            ++itA;
        if (itB != endB && *itB < *cur)
            ++itB;

        Range r = g_traitSet_15e4a1c.FUN_00555980(*cur);
        Key12* found = r.first != r.second ? r.first : g_traitSet_15e4a1c.mpEnd;
        if (found == g_traitSet_15e4a1c.mpEnd)
            continue;

        if (itA != endA && *itA == *cur)
        {
            wA = itA->mC;
            if (itB != endB && *itB == *cur)
            {
                wB = itB->mC;
                acc = fabsf(wA - wB) * cur->mC + acc;
            }
            else
            {
                acc = wA * cur->mC + acc;
            }
        }
        else if (itB != endB && *itB == *cur)
        {
            wB = itB->mC;
            acc = wB * cur->mC + acc;
        }
    }
    return acc;
}

// @ 0x00570e50
float cTraitQuery::Op2(cFeatureVector* a, cFeatureVector* b)
{
    Key12* itA = a->begin();
    Key12* itB = b->begin();
    Key12* endA = a->end();
    Key12* endB = b->end();
    float fA = 0.0f;
    float fB = 0.0f;
    float fC = 0.0f;

    while (itA != endA && itB != endB) {
        while (itA != endA && itB != endB && *itA < *itB) {
            Range rA = g_traitSet_15e4a1c.FUN_00555980(*itA);
            Key12* pA = rA.first != rA.second ? rA.first : g_traitSet_15e4a1c.mpEnd;
            if (pA != g_traitSet_15e4a1c.mpEnd)
                fA += 1.0f;
            ++itA;
        }
        while (itA != endA && itB != endB && *itB < *itA) {
            Range rB = g_traitSet_15e4a1c.FUN_00555980(*itB);
            Key12* pB = rB.first != rB.second ? rB.first : g_traitSet_15e4a1c.mpEnd;
            if (pB != g_traitSet_15e4a1c.mpEnd)
                fB += 1.0f;
            ++itB;
        }
        while (*itA == *itB && itA != endA && itB != endB) {
            Range rC = g_traitSet_15e4a1c.FUN_00555980(*itA);
            Key12* pC = rC.first != rC.second ? rC.first : g_traitSet_15e4a1c.mpEnd;
            if (pC != g_traitSet_15e4a1c.mpEnd) {
                fC += 1.0f;
                fA += 1.0f;
                fB += 1.0f;
            }
            ++itA;
            ++itB;
        }
    }

    char ignore = 0;
    return (fA + fB) * ((TraitData*)&ignore)->Intersect(a, b) / (2.0f * fC);
}

// @ 0x00571100
float cTraitQuery::Op3(cFeatureVector* a, cFeatureVector* b)
{
    Key12* itA = a->begin();
    Key12* itB = b->begin();
    Key12* endA = a->end();
    Key12* endB = b->end();
    float fA = 0.0f;
    float fB = 0.0f;
    float fC = 0.0f;

    while (itA != endA && itB != endB) {
        while (itA != endA && itB != endB && *itA < *itB) {
            Key12* pA = itA;
            Range rA = g_traitSet_15e4a1c.FUN_00555980(*pA);
            Key12* found = rA.first != rA.second ? rA.first : g_traitSet_15e4a1c.mpEnd;
            if (found != g_traitSet_15e4a1c.mpEnd)
                fB += pA->mC * pA->mC;
            ++itA;
        }
        while (itA != endA && itB != endB && *itB < *itA) {
            Key12* pB = itB;
            Range rB = g_traitSet_15e4a1c.FUN_00555980(*pB);
            Key12* found = rB.first != rB.second ? rB.first : g_traitSet_15e4a1c.mpEnd;
            if (found != g_traitSet_15e4a1c.mpEnd)
                fC += pB->mC * pB->mC;
            ++itB;
        }
        while (*itA == *itB && itA != endA && itB != endB) {
            Key12* pA = itA;
            float mB = itB->mC;
            Range rC = g_traitSet_15e4a1c.FUN_00555980(*pA);
            Key12* found = rC.first != rC.second ? rC.first : g_traitSet_15e4a1c.mpEnd;
            if (found != g_traitSet_15e4a1c.mpEnd) {
                fA += pA->mC * mB;
                fB += pA->mC * pA->mC;
                fC += mB * mB;
            }
            ++itA;
            ++itB;
        }
    }
    while (itA != endA && itB == endB) {
        Key12* pA = itA;
        Range rA = g_traitSet_15e4a1c.FUN_00555980(*pA);
        Key12* found = rA.first != rA.second ? rA.first : g_traitSet_15e4a1c.mpEnd;
        if (found != g_traitSet_15e4a1c.mpEnd)
            fB += pA->mC * pA->mC;
        ++itA;
    }
    while (itA == endA && itB != endB) {
        Key12* pB = itB;
        Range rB = g_traitSet_15e4a1c.FUN_00555980(*pB);
        Key12* found = rB.first != rB.second ? rB.first : g_traitSet_15e4a1c.mpEnd;
        if (found != g_traitSet_15e4a1c.mpEnd)
            fC += pB->mC * pB->mC;
        ++itB;
    }

    float nA = (float)sqrt((double)fB);
    float nB = (float)sqrt((double)fC);
    return (float)acos((double)(fA / (nA * nB)));
}
