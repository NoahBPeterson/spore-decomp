// Slice s01009c60 -- eastl::vector<T, eastl::sp_vector_allocator>::DoInsertValue for the
// 0x14-byte element (insert-at-position), the sibling of
// s01009af0/s01009af0.cpp (the same template for a 0x1c-byte element).
//
// Flags: /O2 /MD /Gy /TP
//
// Two paths, as in eastl::vector::DoInsertValue: with spare capacity the last element is
// constructed in the hole, the tail is copied backwards over the insert position and the
// value is assigned in; when the vector is full it grows to twice its size, builds the
// elements before the position, constructs the value, builds the elements after it and
// destroys the old storage.
//
// The element type is only seen through the helpers this function calls, so it is spelled
// by the offsets and the vftable constants the disassembly writes.

#include "types.h"

// Retail image references, use relocatable symbols rather than numeric addresses.
extern "C" unsigned char g_013ec458[];
extern "C" unsigned char g_01495400[];
extern "C" unsigned char g_0149bad8[];

inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

typedef unsigned int u32;

// ---------------------------------------------------------------------------
// external helpers (addresses are relocation bytes masked by the checker)
// ---------------------------------------------------------------------------
void* EAAlloc(u32 size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  operator_delete_array(void* p);                                                // 0x00f47380

// ---------------------------------------------------------------------------
// element: 0x14 bytes, a class with a base sub-object vftable at +0x04 and the
// complete-object vftables 0x01495400 / 0x0149bad8, a zeroed dword at +0x08 and the
// two copied payload dwords at +0x0c / +0x10.
// ---------------------------------------------------------------------------
struct Element {
    u32 mVftable0;  // +0x00
    u32 mVftable4;  // +0x04
    u32 m08;        // +0x08
    u32 m0C;        // +0x0c
    u32 m10;        // +0x10

    // Inlined copy construction (the class' own constructor is not visible here): the base
    // sub-object vftable, the zeroed dword and the two complete-object vftables, then the
    // copied payload.  Written through character pointers, as the original inlined code is;
    // the base vftable write is volatile so it is not merged into the complete-object one.
    Element(const Element& src)
    {
        char* d = (char*)this;
        const char* s = (const char*)&src;

        *(u32 volatile*)(d + 0x04) = (u32)g_013ec458;
        *(u32*)(d + 0x08) = 0;
        *(u32*)(d + 0x00) = (u32)g_01495400;
        *(u32*)(d + 0x04) = (u32)g_0149bad8;
        *(u32*)(d + 0x0c) = *(const u32*)(s + 0x0c);
        *(u32*)(d + 0x10) = *(const u32*)(s + 0x10);
    }

    Element& operator=(const Element& src)
    {
        m0C = src.m0C;
        m10 = src.m10;
        return *this;
    }
};

Element* uninitialized_copy(Element* first, Element* last, Element* dest);   // 0x010062d0
void     uninitialized_relocate_commit(Element* first, Element* last, Element* dest); // 0x01002ea0
void     copy_backward(Element* first, Element* last, Element* destEnd);       // 0x010088e0

// eastl::uninitialized_relocate_ptr: copy the range to dest, then destroy the source range.
// Both helpers take the destination, so the same three arguments are passed twice.
template <class T>
inline T* uninitialized_relocate_ptr(T* first, T* last, T* dest)
{
    T* result = uninitialized_copy(first, last, dest);
    uninitialized_relocate_commit(first, last, dest);
    return result;
}

// ---------------------------------------------------------------------------
// eastl::vector<Element, sp_vector_allocator>
// ---------------------------------------------------------------------------
struct ElementVector {
    Element* mpBegin;       // +0x00
    Element* mpEnd;         // +0x04
    Element* mpCapacity;    // +0x08
    u32      mAllocator;    // +0x0c  eastl::sp_vector_allocator (stateless)

    static u32 GetNewCapacity(u32 currentCapacity)
    {
        return currentCapacity ? (2 * currentCapacity) : 1;
    }

    Element* DoAllocate(u32 n)
    {
        return n ? (Element*)EAAlloc(n * sizeof(Element), "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
                 : 0;
    }

    void DoFree(Element* p)
    {
        if (p && ((int*)p)[-1] != 0)
            operator_delete_array(p);
    }

    void DoInsertValue(Element* position, const Element& value);
};

// @ 0x01009c60 ElementVector::DoInsertValue
void ElementVector::DoInsertValue(Element* position, const Element& value)
{
    if (mpEnd != mpCapacity) {
        // Room for one more: the value may itself come from the range about to move.
        const Element* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        if (mpEnd)
            ::new ((void*)mpEnd) Element(mpEnd[-1]);
        copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const u32 nPrevSize = (u32)(mpEnd - mpBegin);
        const u32 nNewSize  = GetNewCapacity(nPrevSize);
        Element* const pNewData = DoAllocate(nNewSize);

        Element* pNewEnd = uninitialized_relocate_ptr(mpBegin, position, pNewData);
        if (pNewEnd)
            ::new ((void*)pNewEnd) Element(value);
        pNewEnd = uninitialized_relocate_ptr(position, mpEnd, ++pNewEnd);

        DoFree(mpBegin);

        mpBegin    = pNewData;
        mpEnd      = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
