// Fixed-capacity vector helpers: eastl::vector<T>::assign(first, last) for four element types
// (Vector3, Transform, a POD dword, an intrusive ThreadedObject pointer) plus the copy
// constructor of a property entry that owns two fixed_vectors.
//
// Built without optimization: /Od /Ob1 /MD /Gy /EHsc /TP /arch:SSE  (frame pointer, every
// local in memory, small helpers still inlined).
//
// /Od frame-layout notes (see also docs/matching.md):
//  - The inlined copy helper has three flag locals; the order they are declared in decides
//    which byte slots they get, so the declaration order below is deliberate.
//  - The original frames reserve slots for locals of inlined helpers that were compiled out;
//    ScratchSlots<N>() stands in for them so the frame size and offsets match.
#include "types.h"
#include <string.h>
#pragma intrinsic(memcpy)

typedef unsigned int size_t_;

void __cdecl EASTL_Free(void* p);      // 0x00F47380 EASTL_allocator_deallocate

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }

// ---------------------------------------------------------------------------
// Element types
// ---------------------------------------------------------------------------
struct Vector3 { float x, y, z; };

struct Transform {                                   // 0x38 bytes
    uint32_t f[14];
    Transform& operator=(const Transform&);          // 0x00537DC0
};

namespace Resource { struct ThreadedObject { void Release(); }; }   // 0x00404F90

// ---------------------------------------------------------------------------
// Vector of 12-byte / 56-byte elements (element assignment is inline or a call)
// Layout: begin, end, capacity, allocator, pointer to the fixed buffer (or 0).
// ---------------------------------------------------------------------------
template <class T, int kTailSlots = 11>
struct Vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    T* mpFixedBuffer;

    T* DoAllocateAndCopy(size_t_ n, const T* first, const T* last);
    static T* __cdecl UninitializedCopy(const T* first, const T* last, T* dest);

    static T* CopyImpl(const T* first, const T* last, T* dest, bool, bool, bool)
    {
        for (; first != last; ++dest, ++first)
            *dest = *first;
        return dest;
    }
    static T* DoCopy(const T* first, const T* last, T* dest)
    {
        bool b2 = false, b0 = false, b1 = false;
        return CopyImpl(first, last, dest, b0, b1, b2);
    }
    static void Destruct(T* first, T* last) { for (; first < last; ++first) {} }
    static void Dealloc(void* p) { EASTL_Free(p); }
    void DoFree(T* p, size_t_ n)
    {
        if (p && p != mpFixedBuffer) {
            void* q = p;
            Dealloc(q);
        }
    }

    void assign(const T* first, const T* last, int);
};

template <class T, int kTailSlots>
void Vector<T, kTailSlots>::assign(const T* first, const T* last, int)
{
    const size_t_ n = (size_t_)(last - first);
    if (n > (size_t_)(mpCapacity - mpBegin)) {
        T* newBegin = DoAllocateAndCopy(n, first, last);
        ScratchSlots<10>();
        Destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (size_t_)(mpCapacity - mpBegin));
        mpBegin = newBegin;
        mpEnd = mpBegin + n;
        mpCapacity = mpEnd;
    } else if (n <= (size_t_)(mpEnd - mpBegin)) {
        T* newEnd = DoCopy(first, last, mpBegin);
        Destruct(newEnd, mpEnd);
        mpEnd = newEnd;
    } else {
        const T* mid = first + (mpEnd - mpBegin);
        DoCopy(first, mid, mpBegin);
        mpEnd = UninitializedCopy(mid, last, mpEnd);
        ScratchSlots<kTailSlots>();
    }
}

// @ 0x0042C2A0
template void Vector<Vector3>::assign(const Vector3*, const Vector3*, int);

// @ 0x0042C500
template void Vector<Transform, 14>::assign(const Transform*, const Transform*, int);

// ---------------------------------------------------------------------------
// Vector of 4-byte POD elements: copying is a memcpy
// ---------------------------------------------------------------------------
struct DwordVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator;
    uint32_t* mpFixedBuffer;

    uint32_t* DoAllocateAndCopy(size_t_ n, const uint32_t* first, const uint32_t* last);   // 0x0042E5B0
    static uint32_t* __cdecl UninitializedCopy(const uint32_t* first, const uint32_t* last, uint32_t* dest);   // 0x00511F70

    static uint32_t* CopyImpl(const uint32_t* first, const uint32_t* last, uint32_t* dest, bool, bool, bool)
    {
        return (uint32_t*)memcpy(dest, first, (const char*)last - (const char*)first) + (last - first);
    }
    static uint32_t* DoCopy(const uint32_t* first, const uint32_t* last, uint32_t* dest)
    {
        bool b2 = false, b0 = false, b1 = true;
        return CopyImpl(first, last, dest, b0, b1, b2);
    }
    static void Destruct(uint32_t* first, uint32_t* last) { for (; first < last; ++first) {} }
    static void Dealloc(void* p) { EASTL_Free(p); }
    void DoFree(uint32_t* p, size_t_ n)
    {
        if (p && p != mpFixedBuffer) {
            void* q = p;
            Dealloc(q);
        }
    }

    void assign(const uint32_t* first, const uint32_t* last, int);
};

// @ 0x0042C750
void DwordVector::assign(const uint32_t* first, const uint32_t* last, int)
{
    const size_t_ n = (size_t_)(last - first);
    if (n > (size_t_)(mpCapacity - mpBegin)) {
        uint32_t* newBegin = DoAllocateAndCopy(n, first, last);
        ScratchSlots<14>();
        Destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (size_t_)(mpCapacity - mpBegin));
        mpBegin = newBegin;
        mpEnd = mpBegin + n;
        mpCapacity = mpEnd;
    } else if (n <= (size_t_)(mpEnd - mpBegin)) {
        uint32_t* newEnd = DoCopy(first, last, mpBegin);
        Destruct(newEnd, mpEnd);
        mpEnd = newEnd;
    } else {
        const uint32_t* mid = first + (mpEnd - mpBegin);
        DoCopy(first, mid, mpBegin);
        mpEnd = UninitializedCopy(mid, last, mpEnd);
        ScratchSlots<17>();
    }
}

// ---------------------------------------------------------------------------
// Vector of intrusive ThreadedObject pointers (destroying an element releases it)
// ---------------------------------------------------------------------------
typedef Resource::ThreadedObject* ObjPtr;

struct ObjPtrVector {
    ObjPtr* mpBegin;
    ObjPtr* mpEnd;
    ObjPtr* mpCapacity;
    uint32_t mAllocator;
    ObjPtr* mpFixedBuffer;

    ObjPtr* DoAllocateAndCopy(size_t_ n, const ObjPtr* first, const ObjPtr* last);   // 0x00423EF0
    static ObjPtr* __cdecl UninitializedCopy(const ObjPtr* first, const ObjPtr* last, ObjPtr* dest);   // 0x00423F50
    static ObjPtr* __cdecl CopyRange(const ObjPtr* first, const ObjPtr* last, ObjPtr* dest);   // 0x0042D4A0

    template <int kDead>
    static ObjPtr* DoCopy(const ObjPtr* first, const ObjPtr* last, ObjPtr* dest)
    {
        bool b2 = false, b0 = false;
        ScratchSlots<kDead>();
        return CopyRange(first, last, dest);
    }
    static void Destruct(ObjPtr* first, ObjPtr* last)
    {
        for (; first < last; ++first) {
            if (*first)
                (*first)->Release();
            if (OwnsStorage() & 1)
                Dealloc(first);
        }
    }
    static void Dealloc(void* p) { EASTL_Free(p); }
    static bool OwnsStorage() { return false; }
    void DoFree(ObjPtr* p, size_t_ n)
    {
        if (p && p != mpFixedBuffer) {
            void* q = p;
            Dealloc(q);
        }
    }

    void assign(const ObjPtr* first, const ObjPtr* last, int);
};

// @ 0x0042C950
void ObjPtrVector::assign(const ObjPtr* first, const ObjPtr* last, int)
{
    const size_t_ n = (size_t_)(last - first);
    if (n > (size_t_)(mpCapacity - mpBegin)) {
        ObjPtr* newBegin = DoAllocateAndCopy(n, first, last);
        ScratchSlots<13>();
        Destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (size_t_)(mpCapacity - mpBegin));
        mpBegin = newBegin;
        mpEnd = mpBegin + n;
        mpCapacity = mpEnd;
    } else if (n <= (size_t_)(mpEnd - mpBegin)) {
        ObjPtr* newEnd = DoCopy<4>(first, last, mpBegin);
        ScratchSlots<3>();
        Destruct(newEnd, mpEnd);
        mpEnd = newEnd;
    } else {
        const ObjPtr* mid = first + (mpEnd - mpBegin);
        DoCopy<7>(first, mid, mpBegin);
        mpEnd = UninitializedCopy(mid, last, mpEnd);
        ScratchSlots<13>();
    }
}

// ---------------------------------------------------------------------------
// Property entry: a 16-byte record, a dword, and two 6-slot fixed_vectors
// ---------------------------------------------------------------------------
struct PropertyRecord {                       // 16 bytes, see slice s00401b80
    uint32_t mID;
    uint32_t mValue;
    uint16_t mType;
    uint16_t mFlags;
    void* mpObject;
    PropertyRecord(const PropertyRecord& other);      // 0x00401B80
};

struct FixedVectorA {                         // 0x30 bytes: begin/end/cap/alloc/buffer + 6 slots
    uint32_t mData[12];
    FixedVectorA(const FixedVectorA& other);           // 0x0042CCB0
};

struct FixedVectorB {                         // 0x30 bytes
    uint32_t mData[12];
    FixedVectorB(const FixedVectorB& other);           // 0x0042CF80
};

struct PropertyEntry {
    PropertyRecord mRecord;                   // +0x00
    uint32_t mField10;                        // +0x10
    FixedVectorA mValuesA;                    // +0x14
    FixedVectorB mValuesB;                    // +0x44

    PropertyEntry(const PropertyEntry& other);
};

// @ 0x0042CBA0
PropertyEntry::PropertyEntry(const PropertyEntry& other)
    : mRecord(other.mRecord), mField10(other.mField10), mValuesA(other.mValuesA), mValuesB(other.mValuesB)
{
    uint32_t dead[13];
}
