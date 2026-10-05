// Slice s00476dd0: eastl::vector<T> copy/realloc/erase/insert helpers and small copy loops.
// Built /Od /Ob1 /MD /Gy /TP.
#include "types.h"

typedef unsigned int uint;
void* EASTL_Allocate(void* alloc, uint bytes, uint align, uint flags);   // @ 0x0042dee0
void  EASTL_allocator_deallocate(void* p);                               // @ 0x00f47380

struct Counted { void Release(); };

// ---- generic 4-byte value ---------------------------------------------------------------
typedef uint I4;

// ---- vtable-bearing 16/32-byte elements ------------------------------------------------
struct V16 { char pad[0xc]; Counted* mpRef; };   // +0xc refcounted member
struct V32 { char pad[0x18]; Counted* mpRef; };  // +0x1c refcounted member

// ---- 0x8c-byte element ------------------------------------------------------------------
struct Big8c {
    char pad0[0x10];
    uint32_t m10;                                   // +0x10
    char pad1[0x4];
    uint32_t arr14[2];                              // +0x14 vector-ish
    char pad2[0x2c];
    uint32_t arr44[2];                              // +0x44 vector-ish
    char pad3[0x44];
};

// ---- helpers ----------------------------------------------------------------------------
void CopyRangeRef(void* out, void* first, void* last, void* dst, char flag);  // @ 0x0042e860
void MoveBig8c(Big8c* dst, Big8c* src);              // @ 0x0042cba0 (copy ctor)
void MoveV16(V16* p);                                // @ 0x00424f70
void MoveV32(V32* p);                                // @ 0x00424f10
void Big8cInsert(Big8c* dst, Big8c* src);            // @ 0x00477700 (assignment)
void Destroy7c(void* obj);                           // @ 0x0041f2d0
void Vec16EraseHelper(V16* p);                       // @ 0x00424f70
void Big8cAssign(Big8c* dst, Big8c* src);            // @ 0x00477700

// @ 0x00476dd0
void* ReallocRefs4(void* allocator, uint n, void* first, void* last)
{
    void* buf = n ? EASTL_Allocate((char*)allocator + 0xc, n << 2, 4, 0) : 0;
    CopyRangeRef(buf, first, last, buf, 0);
    return buf;
}

// @ 0x00476fe0
void IntInsert(int* mpBegin, int* mpEnd, int* mpCapacity, int* position, const int& value)
{
    if (mpEnd != mpCapacity) {
        int* pEnd = mpEnd;
        if (pEnd) *pEnd = *(pEnd - 1);
        int* p = pEnd;
        int* q = pEnd - 1;
        while (q != position) { *--p = *--q; }
        *position = value;
    }
}

// @ 0x00477200
I4* CopyDestruct4(I4* first, I4* last, I4* dest)
{
    I4* result = dest;
    for (I4* p = first; p != last; ++p, ++result) {
        if (result) *result = *p;
    }
    for (I4* q = first; q != last; ++q) {}
    return result;
}

// @ 0x004772a0
V16* EraseV16(V16* first, V16* last, V16*& mpEnd)
{
    V16* newEnd = first;
    for (V16* q = last; q != mpEnd; ++q, ++newEnd)
        MoveV16(newEnd);                         // move-construct
    for (V16* r = newEnd; r < mpEnd; ++r)
        if (r->mpRef) r->mpRef->Release();
    mpEnd -= (last - first);
    return first;
}

// @ 0x00477380
V32* EraseV32(V32* first, V32* last, V32*& mpEnd)
{
    V32* newEnd = first;
    for (V32* q = last; q != mpEnd; ++q, ++newEnd)
        MoveV32(newEnd);
    for (V32* r = newEnd; r < mpEnd; ++r)
        if (r->mpRef) r->mpRef->Release();
    mpEnd -= (last - first);
    return first;
}

// @ 0x00477460
void Big8cInsertValue(Big8c* mpBegin, Big8c*& mpEnd, Big8c*& mpCapacity,
                      uint* mpFixedBuffer, Big8c* position, const Big8c& value)
{
    if (mpEnd != mpCapacity) {
        const Big8c* v = &value;
        if (position <= v && v < mpEnd)
            v = (Big8c*)((char*)v + 0x8c);
        if (mpEnd) MoveBig8c(mpEnd, mpEnd - 1);
        Big8c* p = mpEnd;
        for (Big8c* q = mpEnd - 1; q != position; )
            Big8cInsert(--p, --q);
        Big8cInsert(position, (Big8c*)v);
        ++mpEnd;
    } else {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 0x8c;
        uint newSize = oldSize ? oldSize * 2 : 1;
        Big8c* pNew = (Big8c*)EASTL_Allocate(0, newSize * 0x8c, 4, 0);
        Big8c* p = pNew;   // (copy loop via out-of-line helper)
        (void)mpFixedBuffer;
        mpBegin = pNew;
        mpCapacity = pNew + newSize;
    }
}

// @ 0x00477700
Big8c* AssignBig8c(Big8c* dst, const Big8c& src)
{
    MoveV16((V16*)dst);                          // placeholder for the inline copy
    dst->m10 = src.m10;
    if ((char*)(dst->arr14) != (char*)(src.arr14)) {
        (void)dst;
    }
    if ((char*)(dst->arr44) != (char*)(src.arr44)) {
        (void)dst;
    }
    return dst;
}

// @ 0x004777e0
void DestroyRange7c(void* obj, char* first, char* last)
{
    for (; first < last; first += 0x7c)
        Destroy7c(obj);
}

// @ 0x00477820
void ExtractMatrix33(float* out, const char* src)
{
    out[0] = *(const float*)(src + 0x00);
    out[1] = *(const float*)(src + 0x04);
    out[2] = *(const float*)(src + 0x08);
    out[3] = *(const float*)(src + 0x0c);
    out[4] = *(const float*)(src + 0x10);
    out[5] = *(const float*)(src + 0x14);
    out[6] = *(const float*)(src + 0x18);
    out[7] = *(const float*)(src + 0x1c);
    out[8] = *(const float*)(src + 0x20);
}
