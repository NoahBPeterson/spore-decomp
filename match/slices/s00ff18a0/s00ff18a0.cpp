// Slice s00ff18a0: eastl::vector<TElement>::insert(position, value) for a 52-byte element
// (0x34): eight floats followed by five 32-bit words. 0x00ff1230 is TElement's out-of-line
// copy constructor and 0x00ff1330 the uninitialized-copy loop over the same element.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <new>
#include "types.h"

// Retail image references, use relocatable symbols rather than numeric addresses.
extern "C" unsigned char g_013ebb38[];

typedef unsigned int uint;

void* __cdecl EAAllocate(uint size, const char* name, int a, int b, int file, int line); // 0x00f473a0
void  __cdecl EASTL_allocator_deallocate(void* p);                                        // 0x00f47380

// 52-byte element; its copy constructor is the out-of-line 0x00ff1230 (eight floats and
// five trailing words, copied member by member).
struct TElement {
    float mf00, mf04, mf08, mf0c;   // +0x00
    float mf10, mf14, mf18, mf1c;   // +0x10
    uint  mu20, mu24, mu28, mu2c;   // +0x20
    uint  mu30;                     // +0x30

    TElement(const TElement& other);            // 0x00ff1230
};

TElement* __cdecl CopyRange(const TElement* first, const TElement* last, TElement* dest); // 0x00ff1330

// eastl::vector<TElement> (three pointers, no allocator member)
struct OrnamentVec {
    TElement* mpBegin;      // +0x00
    TElement* mpEnd;        // +0x04
    TElement* mpCapacity;   // +0x08

    TElement* end() const { return mpEnd; }
    uint GetNewCapacity(uint currentCapacity)
    {
        return (currentCapacity > 0) ? (2 * currentCapacity) : 1;
    }
    TElement* DoAllocate(uint n)
    {
        return n ? (TElement*)EAAllocate(n * 0x34, "EASTL", 0, 0, (int)g_013ebb38, 0xd1) : 0;
    }
    void DoFree(TElement* p)
    {
        if (p && ((int*)p)[-1])
            EASTL_allocator_deallocate(p);
    }
    void insert(TElement* position, const TElement& value);
};

// @ 0x00ff18a0
void OrnamentVec::insert(TElement* position, const TElement& value)
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
    if (pNewEnd)
        ::new ((void*)pNewEnd) TElement(value);

    pNewEnd = CopyRange(position, end(), pNewEnd + 1);
    DoFree(mpBegin);
    mpCapacity = pNewData + nNewSize;
    mpEnd = pNewEnd;
    mpBegin = pNewData;
}
