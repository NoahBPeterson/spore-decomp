// Slice s0040ccb0: modifier-transform accumulation helpers, a float property
// lookup, an environment colour key ctor, and two creature-ability style classes
// (base with vtable 0x013ef094) with their constructors / destructors.
//
// Built WITHOUT optimization: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"
#include <string.h>
#include <intrin.h>
inline void* operator new(unsigned int, void* p) { return p; }

// ---------------------------------------------------------------------------
// Math
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    void Transform(const struct Matrix3& m);
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

struct Matrix3 {
    struct Data { float f[9]; } d;
    Matrix3& operator=(const Matrix3& o) { d = o.d; return *this; }
    Matrix3() {}
    Matrix3(const Matrix3& o);   // 0x0041cb40 (out of line copy ctor)
};

Vector3 operator*(const Vector3& v, const float& s);           // 0x0041dca0
Vector3 operator*(const Vector3& v, const Matrix3& m);         // 0x0041daf0
Matrix3 operator*(const Matrix3& a, const Matrix3& b);         // 0x0041de20
Vector3& operator+=(Vector3& a, const Vector3& b);             // 0x0041ddb0
Vector3& operator*=(Vector3& a, const float& s);               // 0x0041dba0
inline void Vector3::Transform(const Matrix3& m) { *this = *this * m; }

// A scale/rotation/translation modifier that accumulates onto another one.
struct Modifier {
    uint16_t flags;     // +0x00
    uint16_t count;     // +0x02
    Vector3 pos;        // +0x04
    float scale;        // +0x10
    Matrix3 rot;        // +0x14

    void Accumulate(const Modifier& o);
    void AccumulateScaled(const Modifier& o);
    Modifier(const Modifier& o);
};

// @ 0x0040ccb0
void Modifier::Accumulate(const Modifier& o)
{
    pos += (o.pos * scale) * rot;
    rot = o.rot * rot;
    scale *= o.scale;
    flags |= o.flags;
    count++;
}

// @ 0x0040cd80
void Modifier::AccumulateScaled(const Modifier& o)
{
    pos *= o.scale;
    pos.Transform(o.rot);
    pos += o.pos;
    rot = rot * o.rot;
    scale *= o.scale;
    flags |= o.flags;
    count++;
}

// @ 0x0040ce80
Modifier::Modifier(const Modifier& o)
    : flags(o.flags), count(o.count), pos(o.pos), scale(o.scale), rot(o.rot)
{
}

// ---------------------------------------------------------------------------
// Property lookup: float property from a property list
// ---------------------------------------------------------------------------
class Property {
public:
    float* GetValueFloat();          // 0x0041ea70
    uint16_t pad[9];
    uint16_t mnType;                 // +0x12  (0xd = float)
};

class PropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);  // +0x24
};

// @ 0x0040cf10
bool GetFloatProperty(PropertyList* list, uint32_t propertyID, float& result)
{
    Property* pProp;
    float* pValue;   // unused; keeps the original frame layout
    if (list && list->GetProperty(propertyID, pProp) && pProp->mnType == 0xd) {
        result = *pProp->GetValueFloat();
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// Default colour key
// ---------------------------------------------------------------------------
extern const float kZero;   // 0x01485378
extern const float kOne;    // 0x01485720

struct ColorKey {
    uint8_t type;       // +0
    uint8_t r, g, b;    // +1..+3
    float a;            // +4
    float b2;           // +8
    float c;            // +0xc
    float d;            // +0x10
    ColorKey();
};

// @ 0x0040cf60
ColorKey::ColorKey()
{
    type = 2;
    a = kZero;
    b2 = kZero;
    c = kOne;
    d = kZero;
    r = 0x5c;
    g = 0x44;
    b = 0x26;
}

// ---------------------------------------------------------------------------
// Creature ability classes
// ---------------------------------------------------------------------------
void EASTL_allocator_deallocate(void* p);   // 0x00f47380

struct AtomicRefCounted { void Release(); };   // 0x00402420

struct RefPtr {
    AtomicRefCounted* mpObject;
    RefPtr() : mpObject(0) {}
    ~RefPtr() { if (mpObject) mpObject->Release(); }
};

struct RefSlot {
    int key;
    RefPtr mpRef;
    int value[2];
};

struct SlotTable {
    int count;
    RefSlot slots[6];
    SlotTable() : count(0) {}
};

class CreatureAbility {
public:
    CreatureAbility(uint16_t a, uint16_t b, void* c)
        : mId(a), mValue(b), mpData(c) {}
    virtual ~CreatureAbility() {}
    uint16_t mId;       // +4
    uint16_t mValue;    // +6
    void* mpData;       // +8
};

// @ 0x0040cfd0
// The constructor is an in-class (inline) definition. This helper (not in the
// original) keeps one out-of-line copy of it alive so it is emitted as a symbol.
#pragma inline_depth(0)
void* KeepCreatureAbilityCtor(void* mem, uint16_t a, uint16_t b, void* c)
{
    return new (mem) CreatureAbility(a, b, c);
}
#pragma inline_depth()

class SlotAbility : public CreatureAbility {
public:
    SlotAbility();
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
    SlotTable mSlots;   // +0x0c
};

// @ 0x0040d0c0 (scalar deleting dtor) and 0x0040d100 (SlotTable::~SlotTable) are compiler generated.

// @ 0x0040d010
SlotAbility::SlotAbility() : CreatureAbility(0x20d, 100, &mSlots)
{
    memset(&mSlots, 0, sizeof(mSlots));
}

// ---------------------------------------------------------------------------
// Ability holding four vectors
// ---------------------------------------------------------------------------
struct Allocator { const char* mpName; uint32_t mFlags; Allocator() {} };

template <class T>
struct VectorBase {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    Allocator mAllocator;
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase();    // 0x0050ea50 frees the storage
};

struct OpaqueVector {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    Allocator mAllocator;
    OpaqueVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~OpaqueVector();
};
struct OpaqueVectorA : OpaqueVector { ~OpaqueVectorA(); };   // 0x0041f760
struct OpaqueVectorB : OpaqueVector { ~OpaqueVectorB(); };   // 0x0041f8e0
struct OpaqueVectorC : OpaqueVector { ~OpaqueVectorC(); };   // 0x004b5440

struct Entry20 { uint32_t data[5]; };

template <class T>
struct vector : VectorBase<T> {
    vector() {}
    ~vector() {
        for (T* p = this->mpBegin; p < this->mpEnd; ++p)
            p->~T();
    }
};

// Base with an atomic reference count at +4 (same vtable 0x013ef094 as CreatureAbility).
struct AtomicInt {
    volatile long mValue;
    AtomicInt(long v) {
        long unused;   // reproduces an extra frame slot of the original
        Set(v);
    }
    void Set(long v) { _InterlockedExchange(&mValue, v); }
};

class RefCountedAbility {
public:
    RefCountedAbility() : mRefCount(0) {}
    virtual ~RefCountedAbility() {}
    AtomicInt mRefCount;   // +4
};

class ListAbility : public RefCountedAbility {
public:
    ListAbility();
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
    OpaqueVectorA mA;          // +0x08
    OpaqueVectorB mB;          // +0x1C
    vector<Entry20> mEntries;  // +0x30
    OpaqueVectorC mC;          // +0x44
};

// @ 0x0040d160
ListAbility::ListAbility()
{
}

// @ 0x0040d230
// @ 0x0040d260
// ~ListAbility (0x0040d260) and its scalar deleting destructor (0x0040d230) are
// compiler generated from the member list above; no source is written for them.
// (Not byte-exact: the original frames reserve 0x5c / 0x50 bytes of dead inline slots.)
