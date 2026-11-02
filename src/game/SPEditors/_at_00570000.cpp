// src/game/SPEditors/_at_00570000.cpp -- migrated from slice(s) s005709b0, s0056fb90 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_00570000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Traits/cFeatureVector.h"
#include <new>
#include <string.h>
#include <math.h>

// ---- items of slice s0056fb90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Elem1cB {                        // 0x1c-byte element: 4-byte key + 0x18-byte payload
    uint32_t key;                       // +0
    struct Payload {
        char b[0x18];
        void DoDestroyValues();         // 0x00553fb0 (thiscall ret 0)
        void AssignFrom(const void* src);  // 0x0050d440 (thiscall ret 4)
    } body;                            // +4
    // An explicit p->~Elem1cB() makes cl /Od emit the destroy call plus the
    // guarded "scalar deleting destructor" tail (operator delete) seen in the original.
    ~Elem1cB() { body.DoDestroyValues(); }
};
Elem1cB* UninitCopyB(Elem1cB* first, Elem1cB* last, Elem1cB* dst);   // 0x00570400 (cdecl)
struct Sub { void Init(); };                                          // @ 0x00571640
struct Big {
    Sub a;                                  // +0
    char padA[0x1c - 1];                    // +1
    Sub b;                                  // +0x1c
    char padB[0x38 - 0x1c - 1];             // +0x1d
    float vx, vy, vz;                       // +0x38
    char padC[0x50 - 0x44];                 // +0x44
    bool flag;                              // +0x50
    char padD[3];                           // +0x51
    int value;                              // +0x54
    Big* Init();                            // @ 0x00570870
};
// ---- items of slice s0056fb90 end

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
// ---- items of slice s005709b0 end

// ---- items of slice s005709b0_g7 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Key12_s0057_09b0__g7 {
    uint32_t mA;    // +0x00
    uint32_t mB;    // +0x04
    float mC;       // +0x08
};
struct cFeatureVector_s0057_09b0__g7 {
    Key12_s0057_09b0__g7* mpBegin;     // +0x00
    Key12_s0057_09b0__g7* mpEnd;       // +0x04
    Key12_s0057_09b0__g7* mpCapacity;  // +0x08
};
// ---- items of slice s005709b0_g7 end

// @ 0x00570400
Elem1cB* UninitCopyB(Elem1cB* first, Elem1cB* last, Elem1cB* dst)
{
    bool v6 = false;                // bUnused: /Od still materialises the store
    Elem1cB* n26 = dst;             // out
    Elem1cB* n24 = first;           // src
    uint32_t t20[18];               // dead pad filling the original frame
    for (; n24 != last; n24 = n24 + 1) {
        Elem1cB* v22 = n26;         // pElem
        Elem1cB::Payload* n17 = &v22->body;   // pBody
        Elem1cB* p30;               // pCreated
        if (v22 != 0) {
            v22->key = n24->key;
            n17->AssignFrom(&n24->body);
            p30 = v22;
        } else {
            p30 = 0;
        }
        (void)p30;
        (void)t20;
        n26 = n26 + 1;
    }
    (void)v6;
    return n26;
}

// @ 0x00570870
Big* Big::Init()
{
    a.Init();
    b.Init();
    float* pVec = &vx;
    int tmp;
    ((int*)pVec)[0] = 0;
    ((int*)pVec)[1] = 0;
    ((int*)pVec)[2] = 0;
    flag = false;
    value = 0;
    return this;
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

// @ 0x00571530
bool IntersectWeights(const cFeatureVector_s0057_09b0__g7* a, const WeightVector* b)
{
    WeightPair* wtIt = b->mpBegin;
    WeightPair* wtEnd = b->mpEnd;
    Key12_s0057_09b0__g7* fit = a->mpBegin;
    Key12_s0057_09b0__g7* fitEnd = a->mpEnd;

    for (; fit != fitEnd; ++fit)
    {
        for (; wtIt != wtEnd && wtIt->mKey < fit->mA; ++wtIt)
            ;
        if (wtIt == wtEnd || wtIt->mKey != fit->mA)
            return false;
        fit->mC *= wtIt->mVal;
    }
    return true;
}

// @ 0x005715d0
bool Key12::operator<(const Key12& rhs) const
{
    if (mA < rhs.mA)
        return true;
    if (mA != rhs.mA)
        return false;
    return mB < rhs.mB;
}

// @ 0x00571610
bool Key12::operator==(const Key12& rhs) const
{
    if (mA != rhs.mA)
        return false;
    return mB == rhs.mB;
}

// @ 0x00571640
cFeatureVector::cFeatureVector()
{
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    mfLen = 0.0f;
}

// @ 0x00571680
void cFeatureVector::clear()
{
    erase(mpBegin, mpEnd);
    mfLen = 0.0f;
}

// @ 0x005716c0
Key12* cFeatureVector::begin()
{
    Key12* p = mpBegin;
    return p;
}

// @ 0x005716e0
Key12* cFeatureVector::end()
{
    Key12* p = mpEnd;
    return p;
}

// @ 0x00571700
void cFeatureVector::ResetResourceType()
{
    GetResourceTypeFromModelType();
}
