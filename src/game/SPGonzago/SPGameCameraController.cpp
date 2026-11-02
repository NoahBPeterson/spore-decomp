// src/game/SPGonzago/SPGameCameraController.cpp -- migrated from slice(s) s00472b80 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameCameraController.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" unsigned int __cdecl strlen(const char* p);                          // inlined (intrinsic)
#include <stdarg.h>
#include <math.h>
#pragma intrinsic(strlen)

// ---- items of slice s00472b80 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* EASTL_Allocate(void* alloc, uint32_t n, uint32_t align, uint32_t flags); // @ 0x0042dee0
void  EASTL_allocator_deallocate(void* p);                                      // @ 0x00f47380
extern "C" unsigned int __cdecl strlen(const char* p);                          // inlined (intrinsic)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct sp_vector_allocator {
    uint32_t mDummy;
    void deallocate(void* p, uint32_t) { void* q = p; EASTL_allocator_deallocate(q); }
};
struct Counted { void Release(); };                                  // 0x40f360
struct AutoRefCount {
    Counted* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
template<class T> struct ResizeHoles { enum { N = 6 }; };
template<> struct ResizeHoles<AutoRefCount> { enum { N = 15 }; };
template<class T> T* uninitialized_copy_ptr(T* first, T* last, T* dest);   // out of line
template<class T> inline void destruct(T* first, T* last)
{ for (; first < last; ++first) first->~T(); }
template<class T> inline T* CopyRef(T* first, T* last, T* dest)
{
    const bool from = false, left = false, pos = false;
    { uint32_t unused[2]; }
    T* pSource = first;
    T* pDest = dest;
    for (; pSource != last; ++pSource, ++pDest) *pDest = *pSource;
    return pDest;
}
template<class T, int A>
struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; sp_vector_allocator mAllocator;

    T* DoAllocate(uint32_t n) { return n ? (T*)EASTL_Allocate(&mAllocator, n * sizeof(T), A, 0) : 0; }
    void DoFree(T* p, uint32_t n) { if (p && ((int*)p)[-1]) mAllocator.deallocate(p, n); }

    void DoInsertValues(T* pos, uint32_t n, const T& v);   // out of line
    void erase(T* first, T* last);                         // out of line
    void insert(T* pos, uint32_t n, const T& v) { DoInsertValues(pos, n, v); }

    vector& operator=(const vector& x);
    T* DoRealloc(uint32_t n, T* first, T* last);           // out of line
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void reserve(uint32_t n);
    void resize(uint32_t n);
};
template<class T, int A>
vector<T,A>& vector<T,A>::operator=(const vector& x)
{
    if (&x != this) {
        const uint32_t n = x.size();
        if (n > (uint32_t)(mpCapacity - mpBegin)) {
            T* const pNewData = DoRealloc(n, x.mpBegin, x.mpEnd);
            ScratchSlots<9>();
            destruct(mpBegin, mpEnd);
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
            mpBegin = pNewData;
            mpCapacity = mpBegin + n;
        } else if (n > size()) {
            CopyRef(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            uninitialized_copy_ptr(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
            ScratchSlots<8>();
        } else {
            T* const position = CopyRef(x.mpBegin, x.mpEnd, mpBegin);
            destruct(position, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}
template<class T, int A>
void vector<T,A>::reserve(uint32_t n)
{
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        T* const pNewData = DoAllocate(n);
        uninitialized_copy_ptr(mpBegin, mpEnd, pNewData);
        destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        const int nPrevSize = mpEnd - mpBegin;
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = mpBegin + n;
    }
}
template<class T, int A>
void vector<T,A>::resize(uint32_t n)
{
    if (n > size()) {
        insert(mpEnd, n - size(), T());
        ScratchSlots<ResizeHoles<T>::N>();
    } else
        erase(mpBegin + n, mpEnd);
}
struct Str8 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void RangeInitialize(uint32_t n);                             // @ 0x00475ab0
    void append_sprintf_va_list(const char* fmt, void* args);     // @ 0x00475930
    Str8(int unused, const char* p, ...);
};
// ---- items of slice s00472b80 end

// @ 0x00472f50
Str8::Str8(int unused, const char* p, ...)
{
    mpBegin = 0; mpEnd = 0; mpCapacity = 0;
    const uint32_t n = (uint32_t)strlen(p) + 1;
    RangeInitialize(n);
    va_list args; va_start(args, p);
    append_sprintf_va_list(p, args);
    va_end(args);
}
