// eastl::vector<Vector3>::DoInsertValue for the 12-byte three-float element:
// with spare capacity the elements from `position` up are shifted one slot and
// the value is copy-assigned at `position`; without capacity a buffer of twice
// the size is allocated, both halves are copied into it around a copy of the
// value and the old buffer is released.
#include "types.h"
#include <new.h>

struct Vector3
{
    float x;    // +0x00
    float y;    // +0x04
    float z;    // +0x08

    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

struct Vector3Array
{
    Vector3* mpBegin;       // +0x00  first element
    Vector3* mpEnd;         // +0x04  one past the last element
    Vector3* mpCapacity;    // +0x08  one past the allocated storage
    uint32_t mAllocator;    // +0x0c  debug name of the sp_vector_allocator

    void insert(Vector3* position, const Vector3& value);   // 0x00e9e620
};

// Runtime helpers, called at their retail addresses.
extern char g_eastlAllocator;                                   // 0x013ebb38
void*    operator new(unsigned int size, const char* name, int flags, int align,
                      const char* file, int line);                // 0x00f473a0
void     FUN_00f47380(void* block);                               // 0x00f47380 free
Vector3* FUN_007ec550(Vector3* first, Vector3* last, Vector3* dest);  // 0x007ec550 copy-construct [first, last) at dest

// @ 0x00e9e620
void Vector3Array::insert(Vector3* position, const Vector3& value)
{
    if (mpEnd != mpCapacity)
    {   // spare slot: shift the tail up by one element and write the value
        // The value may be one of the elements being shifted up, in which case
        // the reference has to move with it.
        const Vector3* pValue = &value;
        if (pValue >= position && pValue < mpEnd)
            pValue = pValue + 1;

        // Duplicate of the last element in the spare slot.
        ::new (mpEnd) Vector3(*(mpEnd - 1));

        // Shift [position, mpEnd - 1) up by one slot.
        Vector3* pDst = mpEnd;
        Vector3* pSrc = mpEnd - 1;
        while (pSrc != position)
        {
            --pSrc;
            --pDst;
            *pDst = *pSrc;
        }

        *position = *pValue;

        mpEnd = mpEnd + 1;
        return;
    }

    // No spare element: reallocate, copy both halves around the new one.
    const int nPrevSize = (int)(mpEnd - mpBegin);
    const int nNewSize = nPrevSize ? (2 * nPrevSize) : 1;
    Vector3* const pNewData = nNewSize
        ? (Vector3*)operator new(nNewSize * sizeof(Vector3), "Simulator", 0, 0,
                                 &g_eastlAllocator, 0xd1)
        : 0;

    Vector3* const pBegin = mpBegin;
    Vector3* pNewEnd = FUN_007ec550(pBegin, position, pNewData);
    ::new (pNewEnd) Vector3(value);
    Vector3* const pEnd = mpEnd;
    pNewEnd = FUN_007ec550(position, pEnd, ++pNewEnd);

    if (mpBegin != 0)
        FUN_00f47380(mpBegin);

    mpBegin = pNewData;
    mpEnd = pNewEnd;
    mpCapacity = pNewData + nNewSize;
}
