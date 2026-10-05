// slice s00708100: SP::cLightingWorld / cLightingManager continuation and the
// EASTL container algorithms used by the lighting config.  /O2 + SSE region.
#include <new>
#include <string.h>
#include "types.h"

void __cdecl EastlFree(void* p);                      // 0x00F47380

// ===========================================================================
// eastl::vector<cCellInfo, fixed_vector_allocator<8,16,4,0,1>>::assign
// ===========================================================================
struct CellInfo { int x, y; };

struct VecCell {
    CellInfo* mpBegin;      // +0x00
    CellInfo* mpEnd;        // +0x04
    CellInfo* mpCapacity;   // +0x08
    char pad_c[4];
    CellInfo* mpInline;     // +0x10
    CellInfo* DoRealloc(uint32_t n, const CellInfo* first, const CellInfo* last);  // 0x754f80
    void assign(const CellInfo* first, const CellInfo* last);
};

void* MoveRange5(void** out, const CellInfo* first, const CellInfo* last, CellInfo* dst,
                 const CellInfo* end);               // 0x76ffd0

// @ 0x00708340
void VecCell::assign(const CellInfo* first, const CellInfo* last)
{
    const uint32_t n = (uint32_t)(last - first);
    CellInfo* p = mpBegin;
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        CellInfo* pNew = DoRealloc(n, first, last);
        if (mpBegin && mpBegin != mpInline)
            EastlFree(mpBegin);
        mpBegin = pNew;
        mpCapacity = pNew + n;
        mpEnd = pNew + n;
        return;
    }
    if (n <= (uint32_t)(mpEnd - p)) {
        for (; first != last; ++first, ++p)
            *p = *first;
        mpEnd = p;
        return;
    }
    const CellInfo* mid = first + (mpEnd - mpBegin);
    for (; first != mid; ++first, ++p)
        *p = *first;
    CellInfo* newEnd;
    MoveRange5((void**)&newEnd, mid, last, mpEnd, last);
    mpEnd = newEnd;
}

// ===========================================================================
// 8-byte element vector
// ===========================================================================
struct Vec8b {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    void resize(uint32_t n);
    void DoInsertValues(char* position, uint32_t n, const void* value);  // 0x707d10
    void Erase(char* first, char* last);                                 // 0xd018d0
};

// @ 0x00708d90
void Vec8b::resize(uint32_t n)
{
    const uint32_t size = (uint32_t)((mpEnd - mpBegin) >> 3);
    if (size < n) {
        uint64_t z = 0;
        DoInsertValues(mpEnd, n - size, &z);
    } else {
        Erase(mpBegin + n, mpEnd);
    }
}

// ===========================================================================
// 16-byte element vector
// ===========================================================================
struct Vec16 {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    void resize(uint32_t n);
    void DoInsertValues16(char* position, uint32_t n, const void* value);  // 0x77d510
};

void Copy16(char* first, char* last, char* result);    // 0x705250

// @ 0x00708e60
void Vec16::resize(uint32_t n)
{
    const uint32_t size = (uint32_t)((mpEnd - mpBegin) >> 4);
    if (size < n) {
        char buf[16];
        DoInsertValues16(mpEnd, n - size, buf);
        return;
    }
    char* mid = mpBegin + n * 0x10;
    Copy16(mpEnd, mpEnd, mid);
    mpEnd = (char*)(mpEnd - (mpEnd - mid));
}

// ===========================================================================
// vector-like clear (destroys each element then drops the range)
// ===========================================================================
void ReleaseElem(void* p);                              // 0x7610f0

struct ClearVec {
    char pad0[0x4c];
    void** mpBegin;     // +0x4c
    void** mpEnd;       // +0x50
    char pad54[0xc];
    void* mpExtra;      // +0x60
    void clear();
};

// @ 0x007087a0
void ClearVec::clear()
{
    int n = (int)((mpEnd - mpBegin) >> 2);
    for (int i = 0; i < n; ++i)
        ReleaseElem(mpBegin[i]);
    memcpy(mpBegin, mpEnd, 0);
    mpEnd -= mpEnd - mpBegin;
    if (mpExtra) {
        ReleaseElem(mpExtra);
        mpExtra = 0;
    }
}
