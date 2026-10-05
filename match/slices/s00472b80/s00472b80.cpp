// Slice s00472b80: rw math QuaternionFromMatrix33, EASTL basic_string sprintf ctors,
// and eastl::vector<T,sp_vector_allocator> instantiations (copy-ctor/resize/dtor/operator=/size/reserve).
// Built /Od /Ob1 /MD /Gy /TP (no /EHsc); vector template copied from the proven s00473e40 spelling.
#include "types.h"
#include <stdarg.h>
#include <math.h>

void* EASTL_Allocate(void* alloc, uint32_t n, uint32_t align, uint32_t flags); // @ 0x0042dee0
void  EASTL_allocator_deallocate(void* p);                                      // @ 0x00f47380
extern "C" unsigned int __cdecl strlen(const char* p);                          // inlined (intrinsic)
#pragma intrinsic(strlen)

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct sp_vector_allocator {
    uint32_t mDummy;
    void deallocate(void* p, uint32_t) { void* q = p; EASTL_allocator_deallocate(q); }
};

// ---- element types ---------------------------------------------------------------------------
struct Counted { void Release(); };                                  // 0x40f360
struct AutoRefCount {
    Counted* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
struct Pod12 { float x, y, z; };                                     // 12-byte POD
struct Pair8 { int first; float second; Pair8() {} };                 // 8-byte, empty default ctor
struct Elem29c {
    char pad[0x158];
    uint32_t a[64];      // +0x158
    uint32_t b[16];      // +0x258
    Counted* m298;       // +0x298
    Elem29c();                                            // out of line @ 0x475880
    ~Elem29c() {
        Counted** p = &m298;
        if (*p) (*p)->Release();
    }
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

// ---- vector<T, A> ----------------------------------------------------------------------------
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

// ---- vector<char,1>::vector(const vector&) ---------------------------------------------------
char* UninitCopyChar(char* first, char* last, char* dest);      // @ 0x00475bd0
inline char* uninitialized_copy(char* first, char* last, char* dest)
{
    ScratchSlots<14>();
    return UninitCopyChar(first, last, dest);
}
struct CharVec {
    char* mpBegin; char* mpEnd; char* mpCapacity; void* mAllocator;
    CharVec(const CharVec& x);
};
CharVec::CharVec(const CharVec& x)
{
    const uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
    mpBegin = n ? (char*)EASTL_Allocate(&mAllocator, n, 1, 0) : 0;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
    mpEnd = uninitialized_copy(x.mpBegin, x.mpEnd, mpBegin);
}

// ---- vector<Struct29c,4> dtor / resize -------------------------------------------------------
struct Vec29 {
    Elem29c* mpBegin; Elem29c* mpEnd; Elem29c* mpCapacity; void* mAllocator;
    void DoInsertValues(Elem29c* pos, uint32_t n, const Elem29c& v);   // @ 0x00478e00
    void erase(Elem29c* first, Elem29c* last);                         // @ 0x00475da0
    void DoFreeSelf();                                                 // @ 0x00475e90
    ~Vec29();
    void resize(uint32_t n);
};
Vec29::~Vec29()
{
    ScratchSlots<5>();
    Elem29c* const end = mpEnd;
    for (Elem29c* it = mpBegin; it < end; ++it)
        it->~Elem29c();
    DoFreeSelf();
}
void Vec29::resize(uint32_t n)
{
    if (n > (uint32_t)(mpEnd - mpBegin)) {
        Elem29c v;
        DoInsertValues(mpEnd, n - (uint32_t)(mpEnd - mpBegin), v);
    } else
        erase(mpBegin + n, mpEnd);
}

// ---- rw::math::fpu::QuaternionFromMatrix33<float,0> -------------------------------------------
struct Matrix33 { float m[12]; };
struct Quaternion { float x, y, z, w; };
Quaternion* QuaternionFromMatrix33(Quaternion* out, const Matrix33* mat, float epsilon)
{
    const float trace = mat->m[0] + mat->m[4] + mat->m[8];
    if (trace > epsilon) {
        const float s = sqrt(trace + 1.0f);
        const float inv = 0.5f / s;
        out->x = (mat->m[5] - mat->m[7]) * inv;
        out->y = (mat->m[6] - mat->m[2]) * inv;
        out->z = (mat->m[1] - mat->m[3]) * inv;
        out->w = 0.5f * s;
    } else if (mat->m[0] > mat->m[4] && mat->m[0] > mat->m[8]) {
        const float s = sqrt((mat->m[0] - (mat->m[4] + mat->m[8])) + 1.0f);
        const float inv = 0.5f / s;
        out->x = 0.5f * s;
        out->y = (mat->m[1] + mat->m[3]) * inv;
        out->z = (mat->m[2] + mat->m[6]) * inv;
        out->w = (mat->m[5] - mat->m[7]) * inv;
    } else if (mat->m[4] > mat->m[8]) {
        const float s = sqrt((mat->m[4] - (mat->m[8] + mat->m[0])) + 1.0f);
        const float inv = 0.5f / s;
        out->x = (mat->m[1] + mat->m[3]) * inv;
        out->y = 0.5f * s;
        out->z = (mat->m[5] + mat->m[7]) * inv;
        out->w = (mat->m[6] - mat->m[2]) * inv;
    } else {
        const float s = sqrt((mat->m[8] - (mat->m[0] + mat->m[4])) + 1.0f);
        const float inv = 0.5f / s;
        out->x = (mat->m[2] + mat->m[6]) * inv;
        out->y = (mat->m[5] + mat->m[7]) * inv;
        out->z = 0.5f * s;
        out->w = (mat->m[1] - mat->m[3]) * inv;
    }
    return out;
}

// ---- eastl::basic_string sprintf constructors ------------------------------------------------
struct Str8 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void RangeInitialize(uint32_t n);                             // @ 0x00475ab0
    void append_sprintf_va_list(const char* fmt, void* args);     // @ 0x00475930
    Str8(int unused, const char* p, ...);
};
Str8::Str8(int unused, const char* p, ...)
{
    mpBegin = 0; mpEnd = 0; mpCapacity = 0;
    const uint32_t n = (uint32_t)strlen(p) + 1;
    RangeInitialize(n);
    va_list args; va_start(args, p);
    append_sprintf_va_list(p, args);
    va_end(args);
}

struct StrW {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity;
    void AllocateSelf(uint32_t n);                               // @ 0x00475ab0
    void append_sprintf_va_list(const wchar_t* fmt, void* args); // @ 0x004234b0
    StrW(int unused, const wchar_t* p, ...);
};
StrW::StrW(int unused, const wchar_t* p, ...)
{
    mpBegin = 0; mpEnd = 0; mpCapacity = 0;
    const wchar_t* q = p;
    while (*q) ++q;
    const uint32_t n = (uint32_t)(q - p) + 1;
    AllocateSelf(n);
    va_list args; va_start(args, p);
    append_sprintf_va_list(p, args);
    va_end(args);
}

// ============================== explicit instantiations ========================================
// @ 0x00473140
// (CharVec copy ctor above)
// @ 0x00473270
template void vector<AutoRefCount, 4>::resize(uint32_t);
// @ 0x00473500
template vector<Pod12, 4>& vector<Pod12, 4>::operator=(const vector<Pod12, 4>&);
// @ 0x004737f0
template uint32_t vector<Pod12, 4>::size() const;
// @ 0x00473890
template void vector<Pod12, 4>::reserve(uint32_t);
// @ 0x00473b00
template vector<Pair8, 4>& vector<Pair8, 4>::operator=(const vector<Pair8, 4>&);
// @ 0x00473dc0
template void vector<Pair8, 4>::resize(uint32_t);
