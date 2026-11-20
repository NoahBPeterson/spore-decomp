// Slice s01009af0 -- eastl::vector<SP::cXHTMLControlAppearance::cControlDrawable,
// eastl::sp_vector_allocator>::DoInsertValue, the 0x1c-byte element's insert-at-position.
//
// Flags: /O2 /MD /Gy /TP
//
// Two paths, as in eastl::vector::DoInsertValue: with spare capacity the last element is
// constructed in the hole, the tail is copied backwards over the insert position and the
// value is assigned in; when the vector is full it grows to twice its size, builds the
// elements before the position, constructs the value, builds the elements after it and
// destroys the old storage.
//
// The element type (0x1c bytes) and its member functions are seen only through the calls
// this function makes, so they are spelled by the offsets the disassembly uses.

#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

typedef unsigned int u32;

// ---------------------------------------------------------------------------
// external helpers (addresses are relocation bytes masked by the checker)
// ---------------------------------------------------------------------------
void* EAAlloc(u32 size, const char* name, int a, int b, const char* file, int line);   // 0x00f473a0
void  operator_delete_array(void* p);                                                  // 0x00f47380

// ---------------------------------------------------------------------------
// element: SP::cXHTMLControlAppearance::cControlDrawable (0x1c bytes)
// ---------------------------------------------------------------------------
struct EStringX {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    int   mAllocator;   // +0x0c
    void assign(const char* first, const char* last);   // 0x00454cb0

    EStringX& operator=(const EStringX& src)
    {
        if (&src != this)
            assign(src.mpBegin, src.mpEnd);
        return *this;
    }
};

struct cControlDrawable {
    EStringX mName;     // +0x00
    int      m10;       // +0x10
    float    m14;       // +0x14
    int      m18;       // +0x18

    cControlDrawable(const cControlDrawable& src);                    // 0x01006630
    cControlDrawable& operator=(const cControlDrawable& src);
};

cControlDrawable& cControlDrawable::operator=(const cControlDrawable& src)
{
    mName = src.mName;
    m10   = src.m10;
    m14   = src.m14;
    m18   = src.m18;
    return *this;
}

cControlDrawable* uninitialized_copy_ptr(const cControlDrawable* first, const cControlDrawable* last,
                                        cControlDrawable* dest);   // 0x010066a0
cControlDrawable* uninitialized_relocate_commit(cControlDrawable* first, cControlDrawable* last,
                                                cControlDrawable* dest);  // 0x006fa9e0

// eastl::uninitialized_relocate_ptr: copy the range to dest, then destroy the source range.
template <class T>
inline T* uninitialized_relocate_ptr(T* first, T* last, T* dest)
{
    T* result = uninitialized_copy_ptr(first, last, dest);
    uninitialized_relocate_commit(first, last, dest);
    return result;
}
cControlDrawable* copy_backward(cControlDrawable* first, cControlDrawable* last,
                               cControlDrawable* destEnd);          // 0x01006320

// ---------------------------------------------------------------------------
// eastl::vector<cControlDrawable>
// ---------------------------------------------------------------------------
struct ControlDrawableVector {
    cControlDrawable* mpBegin;      // +0x00
    cControlDrawable* mpEnd;        // +0x04
    cControlDrawable* mpCapacity;   // +0x08
    u32               mAllocator;   // +0x0c  eastl::sp_vector_allocator (stateless)

    static u32 GetNewCapacity(u32 currentCapacity)
    {
        return currentCapacity ? (2 * currentCapacity) : 1;
    }

    cControlDrawable* DoAllocate(u32 n)
    {
        return n ? (cControlDrawable*)EAAlloc(n * sizeof(cControlDrawable), "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
                 : 0;
    }

    void DoFree(cControlDrawable* p)
    {
        if (p && ((int*)p)[-1] != 0)
            operator_delete_array(p);
    }

    void DoInsertValue(cControlDrawable* position, const cControlDrawable& value);
};

// @ 0x01009af0 ControlDrawableVector::DoInsertValue
void ControlDrawableVector::DoInsertValue(cControlDrawable* position, const cControlDrawable& value)
{
    if (mpEnd != mpCapacity) {
        // Room for one more: value may itself come from the range that is about to move.
        const cControlDrawable* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        if (mpEnd)
            ::new(mpEnd) cControlDrawable(*(mpEnd - 1));
        copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const u32 nPrevSize = (u32)(mpEnd - mpBegin);
        const u32 nNewSize  = GetNewCapacity(nPrevSize);
        cControlDrawable* const pNewData = nNewSize
            ? (cControlDrawable*)EAAlloc(nNewSize * sizeof(cControlDrawable), "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
            : 0;
        cControlDrawable* pNewEnd = uninitialized_relocate_ptr(mpBegin, position, pNewData);
        if (pNewEnd)
            ::new(pNewEnd) cControlDrawable(value);
        pNewEnd = uninitialized_relocate_ptr(position, mpEnd, ++pNewEnd);

        DoFree(mpBegin);

        mpBegin    = pNewData;
        mpEnd      = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
