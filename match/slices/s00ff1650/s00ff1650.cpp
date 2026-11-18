// Slice s00ff1650: eastl::vector<TElement>::insert(position, value) for a 56-byte element
// (0x38). 0x00ff11c0 is TElement's out-of-line copy constructor and 0x00ff1290 the
// uninitialized-copy loop over the same element.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The grow path follows eastl::vector::DoInsertValue + VectorBase::GetNewCapacity as the game's
// header writes them: the three-pointer vector, `nPrevSize`/`nNewSize` locals (which is what gives
// retail's extra 4-byte `push ecx` frame slot for nNewSize) and DoAllocate's `n ? ... : 0` guard.
// The old begin is read into a local (`pFirst`, like eastl's `uninitialized_copy_ptr(mpBegin, ...)`
// call spelled out); naming it is what makes cl 15 hand eax to that argument and keep `position`
// in ebp, i.e. it fixes the whole grow-path tail's scratch-register rotation (edx/eax/ecx/edx/eax
// with a bare `mpBegin`).
#include <new>
#include "types.h"

typedef unsigned int uint;

void* __cdecl EAAllocate(uint size, const char* name, int a, int b, int file, int line); // 0x00f473a0
void  __cdecl EASTL_allocator_deallocate(void* p);                                        // 0x00f47380

// 56-byte element; its copy constructor is the out-of-line 0x00ff11c0 (eight floats, an int,
// two flag bytes and four trailing words).
struct TElement {
    float mf00, mf04, mf08, mf0c;   // +0x00
    float mf10, mf14, mf18, mf1c;   // +0x10
    int   mn20;                     // +0x20
    char  mb24;                     // +0x24
    char  mb25;                     // +0x25
    short mn26;                     // +0x26
    int   mn28, mn2c, mn30, mn34;   // +0x28
    TElement(const TElement& other);            // 0x00ff11c0
};

TElement* __cdecl CopyRange(const TElement* first, const TElement* last, TElement* dest); // 0x00ff1290

// eastl::vector<TElement> (three pointers, no allocator member)
struct ElemVec {
    TElement* mpBegin;      // +0x00
    TElement* mpEnd;        // +0x04
    TElement* mpCapacity;   // +0x08

    uint GetNewCapacity(uint currentCapacity)
    {
        return (currentCapacity > 0) ? (2 * currentCapacity) : 1;
    }
    TElement* DoAllocate(uint n)
    {
        return n ? (TElement*)EAAllocate(n * 0x38, "EASTL", 0, 0, 0x13ebb38, 0xd1) : 0;
    }
    void DoFree(TElement* p)
    {
        if (p && ((int*)p)[-1])
            EASTL_allocator_deallocate(p);
    }
    void insert(TElement* position, const TElement& value);
};

// @ 0x00ff1650
void ElemVec::insert(TElement* position, const TElement& value)
{
    if (mpEnd != mpCapacity)
    {
        // The value may live inside the range that is about to shift up by one element.
        const TElement* pValue = &value;
        if (pValue >= position && pValue < mpEnd)
            pValue = pValue + 1;

        if (mpEnd)
            ::new ((void*)mpEnd) TElement(mpEnd[-1]);

        TElement* pDst = mpEnd;
        TElement* pSrc = mpEnd - 1;
        while (pSrc != position)
        {
            --pSrc;
            --pDst;
            *pDst = *pSrc;
        }
        *position = *pValue;
        ++mpEnd;
        return;
    }

    // Grow: double the element count (one for an empty vector) and rebuild the sequence.
    const uint nPrevSize = (uint)(mpEnd - mpBegin);
    const uint nNewSize = GetNewCapacity(nPrevSize);
    TElement* const pNewData = DoAllocate(nNewSize);

    const TElement* pFirst = mpBegin;
    TElement* pNewEnd = CopyRange(pFirst, position, pNewData);
    ::new ((void*)pNewEnd) TElement(value);
    pNewEnd = CopyRange(position, mpEnd, pNewEnd + 1);

    DoFree(mpBegin);
    mpBegin = pNewData;
    mpEnd = pNewEnd;
    mpCapacity = pNewData + nNewSize;
}
