// slice s005709b0
// SP::Traits feature-vector helpers. The module is built /Od /Ob1 (spilled `this`,
// every local in memory), like the neighbouring slice s005718f0.
#include <new>
#include <string.h>
#include <math.h>
#include "types.h"

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

    void erase(Key12* first, Key12* last);                                   // 0x50f740
    Key12* insert(Key12* position, const Key12& value);                      // 0x5718f0
};

struct InsertResult {
    Key12* position;      // +0x0
    bool inserted;        // +0x4
};

struct cFeatureVector : KeyVector {
    char pad10[4];                 // +0x10 .. +0x13
    unsigned char mSorted;         // +0x14 (compare/flag byte passed to lower_bound)
    char pad15[3];                 // +0x15 .. +0x17
    float mfLen;                   // +0x18

    cFeatureVector();                                        // 0x571640
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
    if (pos != mpEnd && !(value < *pos)) {
        InsertResult r;
        r.position = pos;
        r.inserted = false;
        return r;
    }
    InsertResult r;
    r.position = insert(pos, value);
    r.inserted = true;
    return r;
}

// ---------------------------------------------------------------------------
// Large /Od dispatch / similarity functions. These are behaviourally summarised
// below; see partial.txt. They are kept as compiling placeholders until the
// full translation is verified.
// ---------------------------------------------------------------------------
struct cTraitQuery {
    char pad[0x100];
    float Compute(cFeatureVector* a, cFeatureVector* b);   // 0x5709b0
    float Op1(cFeatureVector* a, cFeatureVector* b);       // 0x570c40
    float Op2(cFeatureVector* a, cFeatureVector* b);       // 0x570e50
    float Op3(cFeatureVector* a, cFeatureVector* b);       // 0x571100
};

// @ 0x005709b0
float cTraitQuery::Compute(cFeatureVector* a, cFeatureVector* b)
{
    (void)a; (void)b;
    return 0.0f;
}

// @ 0x00570c40
float cTraitQuery::Op1(cFeatureVector* a, cFeatureVector* b)
{
    (void)a; (void)b;
    return 0.0f;
}

// @ 0x00570e50
float cTraitQuery::Op2(cFeatureVector* a, cFeatureVector* b)
{
    (void)a; (void)b;
    return 0.0f;
}

// @ 0x00571100
float cTraitQuery::Op3(cFeatureVector* a, cFeatureVector* b)
{
    (void)a; (void)b;
    return 0.0f;
}
