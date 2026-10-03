// EASTL-style algorithms instantiated for small POD element types.
// Module built unoptimized: /Od /Ob1 /MD /Gy /TP /arch:SSE
#include "types.h"

struct Entry12 {            // 12-byte element sorted by its first field
    uint32_t key, a, b;
};

struct Entry48 {            // 48-byte element stored in a vector
    uint32_t d[12];
    Entry48(const Entry48& src);   // FUN_0042cbf0 (out of line)
};

struct EmptyTag {};

inline bool Less12(const uint32_t& a, const uint32_t& b) { return a < b; }

// @ 0x0042b4e0
// insertion_sort over 12-byte elements, ordered by first field (less<>)
// (iterators declared at function scope: that fixes the /Od frame slot order)
void __cdecl InsertionSort12(Entry12* first, Entry12* last)
{
    Entry12* pNext;
    Entry12* prev;
    if (first != last) {
        Entry12* cur = first;
        ++cur;
        for (; cur != last; ++cur) {
            Entry12 val = *cur;
            prev = cur;
            pNext = prev;
            --prev;
            for (; pNext != first && Less12(val.key, prev->key); --pNext, --prev)
                *pNext = *prev;
            *pNext = val;
        }
    }
}

// @ 0x0042b5b0
// fill_n for 32-bit floats
float* __cdecl FillN(float* first, uint32_t n, const float* pValue)
{
    uint32_t n_ = n;
    float* f = first;
    float v = *pValue;
    for (; n_-- > 0; ++f)
        *f = v;
    return f;
}

// ---- vector<Entry48>::insert(pos, n, value) ----
struct Allocator48 {
    void* pad;
    void* fixedBuffer;      // +0x10 in the vector
};

Entry48* __cdecl Entry48_Move(EmptyTag* pTag, Entry48* first, Entry48* last, Entry48* dest, EmptyTag); // FUN_0042f020
Entry48* __cdecl Entry48_FillN(Entry48* dest, uint32_t n, const Entry48* value, EmptyTag); // FUN_0042f0a0
Entry48* __cdecl Entry48_MoveBackward(Entry48* first, Entry48* last, Entry48* destEnd); // FUN_0042df50
Entry48* __cdecl Entry48_Uninit(Entry48* first, Entry48* last, Entry48* dest); // FUN_0042dff0
void* __cdecl AllocateRaw(void* alloc, uint32_t size, uint32_t align, uint32_t offset); // FUN_0042dee0
void  __cdecl EASTL_allocator_deallocate(void* p);

struct Entry48Vector {
    Entry48* mpBegin;
    Entry48* mpEnd;
    Entry48* mpCapacity;
    void*    mAlloc;        // +0xc
    void*    mFixedBuffer;  // +0x10

    void insert_n(Entry48* position, uint32_t n, const Entry48& value);
};

// @ 0x0042b600
void Entry48Vector::insert_n(Entry48* position, uint32_t n, const Entry48& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            Entry48 tmp(value);
            uint32_t elementsAfter = (uint32_t)(mpEnd - position);
            Entry48* oldEnd = mpEnd;
            if (n < elementsAfter) {
                EmptyTag t;
                Entry48_Move(&t, mpEnd - n, mpEnd, mpEnd, t);
                mpEnd += n;
                Entry48* src = oldEnd;
                Entry48* dst = oldEnd - n;
                while (dst != position) {
                    --dst;
                    --src;
                    *src = *dst;
                }
                for (Entry48* p = position; p != position + n; ++p)
                    *p = tmp;
            } else {
                EmptyTag t;
                Entry48_FillN(mpEnd, n - elementsAfter, &tmp, t);
                mpEnd += n - elementsAfter;
                Entry48_MoveBackward(position, oldEnd, mpEnd);
                mpEnd += elementsAfter;
                for (Entry48* p = position; p != oldEnd; ++p)
                    *p = tmp;
            }
        }
    } else {
        uint32_t prevSize = (uint32_t)(mpEnd - mpBegin);
        uint32_t growSize = prevSize ? prevSize * 2 : 1;
        uint32_t newSize = (growSize > prevSize + n) ? growSize : prevSize + n;
        Entry48* newData = newSize ? (Entry48*)AllocateRaw(&mAlloc, newSize * 0x30, 4, 0) : 0;
        Entry48* newEnd = Entry48_Uninit(mpBegin, position, newData);
        EmptyTag t1;
        Entry48_FillN(newEnd, n, &value, t1);
        newEnd = Entry48_Uninit(position, mpEnd, newEnd + n);
        if (mpBegin && mpBegin != mFixedBuffer)
            EASTL_allocator_deallocate(mpBegin);
        mpBegin = newData;
        mpEnd = newEnd;
        mpCapacity = newData + newSize;
    }
}
