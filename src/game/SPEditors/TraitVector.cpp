// src/game/SPEditors/TraitVector.cpp -- migrated from slice(s) s005709b0 by tools/migrate/rewrite.py
// Object file: SPEditors/TraitVector.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Traits/cFeatureVector.h"
#include <new>
#include <string.h>
#include <math.h>

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
Key12* __cdecl lower_bound(Key12* first, Key12* last, const Key12& value, unsigned char comp);  // 0x571c40
// ---- items of slice s005709b0 end

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
