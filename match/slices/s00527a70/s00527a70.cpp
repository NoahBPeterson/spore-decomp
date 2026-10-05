// nSPSkinner skin-mesh EASTL vector support, part 2 (/Od /Ob1 /MD /Gy /TP /arch:SSE).
// 0x1c / 0x18 / 0x40-byte element vectors plus the fixed_vector<8-byte> assign path.
#include "types.h"

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}

extern "C" void* __cdecl memcpy(void*, const void*, uint32_t);
#pragma intrinsic(memcpy)

inline void* operator new(unsigned int, void* p) { return p; }

struct sp_vector_allocator { const char* mpName; uint32_t mFlags; };
void* EA_Allocate(void* allocator, uint32_t n, uint32_t align, uint32_t offset);  // 0x0042dee0
void  EA_Free(void* p);                                                            // 0x00f47380

// ---------------------------------------------------------------- small math types
struct Vec3f {
    float x, y, z;
    Vec3f() {}
    Vec3f(const Vec3f& o) { x = o.x; y = o.y; z = o.z; }
};
struct Matrix33 {                                  // 0x24 bytes
    float m[9];
    Matrix33() {}
    Matrix33(const Matrix33& o) { Assign(o); }
    void Assign(const Matrix33& o);                // 0x0041cb40
};
struct B4 {
    uint8_t a, b, c, d;
    B4() {}
    B4(const B4& o) { a = o.a; b = o.b; c = o.c; d = o.d; }
};

// ---------------------------------------------------------------- 0x40-byte element
struct Elem40 {
    B4 m00;                     // +0x00
    Vec3f v04;                  // +0x04
    Matrix33 mat;               // +0x10
    float v34, v38, v3c;        // +0x34
    Elem40() {}
    Elem40(const Elem40& x);    // 0x00528610
};

// @ 0x00528610
Elem40::Elem40(const Elem40& x)
    : m00(x.m00), v04(x.v04), mat(x.mat), v34(x.v34), v38(x.v38), v3c(x.v3c)
{
    ScratchSlots<11>();
}

// ---------------------------------------------------------------- generic_iterator
template <typename T> struct gi {
    T* it;
    explicit gi(T* x) : it(x) {}
    gi& operator++() { ++it; return *this; }
    T& operator*() const { return *it; }
    T* base() const { return it; }
};
template <typename T> inline bool operator!=(const gi<T>& a, const gi<T>& b) { return a.it != b.it; }

// ---------------------------------------------------------------- trivial elements
struct Elem1c { uint32_t d[7]; };   // 0x1c
struct Elem18 { uint32_t d[6]; };   // 0x18

// @ 0x00527a70  eastl::uninitialized_copy<Elem1c*>
void* UninitCopy1c(void* first, void* last, void* dest)
{
    const gi<Elem1c> i((Elem1c*)((char*)dest + (((char*)last - (char*)first) / 0x1c) * 0x1c));
    memcpy(dest, first, (uint32_t)((char*)last - (char*)first));
    (void)i;
    return (void*)((char*)dest + (((char*)last - (char*)first) / 0x1c) * 0x1c);
}

// @ 0x00527b70  eastl::uninitialized_copy<Elem18*>
void* UninitCopy18(void* first, void* last, void* dest)
{
    const gi<Elem18> i((Elem18*)((char*)dest + (((char*)last - (char*)first) / 0x18) * 0x18));
    memcpy(dest, first, (uint32_t)((char*)last - (char*)first));
    (void)i;
    return (void*)((char*)dest + (((char*)last - (char*)first) / 0x18) * 0x18);
}

// ---------------------------------------------------------------- vector base
template <typename T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    uint32_t capacity() const { return (uint32_t)(mpCapacity - mpBegin); }
    void DoFree(T* p, uint32_t) { if (p && ((uint32_t*)p)[-1]) { void* q = p; EA_Free(q); } }
};
template <typename T> inline void destruct(T* first, T* last) { for (; first < last; ++first) first->~T(); }

Elem40* UninitCopy40(Elem40* first, Elem40* last, Elem40* dest);   // 0x00528330
Elem40* AllocAndCopy40(uint32_t n, Elem40* first, Elem40* last);   // 0x005286c0
Elem40* UninitCopy40b(Elem40* first, Elem40* last, Elem40* dest);  // 0x005273a0
void    FillN40(Elem40* dest, uint32_t n, const Elem40& value);    // 0x00528880

struct VectorElem40 : VectorBase<Elem40> {
    typedef Elem40 value_type;
    typedef uint32_t size_type;
    VectorElem40() {}
    VectorElem40(const VectorElem40& x);
    VectorElem40& operator=(const VectorElem40& x);                       // 0x00527c70
    void DoInsertValues(Elem40* position, size_type n, const Elem40& value);  // 0x00527f30
    void insert(Elem40* position, size_type n, const Elem40& value) { DoInsertValues(position, n, value); }
};

// @ 0x00527c70
VectorElem40& VectorElem40::operator=(const VectorElem40& x)
{
    if (this != &x) {
        uint32_t n = x.size();
        if (n > capacity()) {
            Elem40* pNewData = AllocAndCopy40(n, x.mpBegin, x.mpEnd);
            destruct(mpBegin, mpEnd);
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
            mpBegin = pNewData;
            mpCapacity = pNewData + n;
        } else if (n > size()) {
            Elem40* p = mpBegin;
            for (Elem40* s = x.mpBegin; s != x.mpBegin + size(); ++s, ++p)
                *p = *s;
            UninitCopy40(x.mpBegin + size(), x.mpEnd, mpEnd);
        } else {
            Elem40* p = mpBegin;
            for (Elem40* s = x.mpBegin; s != x.mpEnd; ++s, ++p)
                *p = *s;
            destruct(p, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x00527f30
void VectorElem40::DoInsertValues(Elem40* position, size_type n, const Elem40& value)
{
    if (n == 0)
        return;
    Elem40 valueSaved(value);
    size_type nAfter = (size_type)(mpEnd - position);
    if ((size_type)(mpCapacity - mpEnd) >= n) {
        if (nAfter > n) {
            for (size_type i = 0; i < n; ++i)
                ::new (mpEnd + i) Elem40(mpEnd[nAfter - n + i]);
            for (Elem40* p = mpEnd - n - 1; p >= position; --p)
                p[n] = *p;
            for (size_type i = 0; i < n; ++i)
                position[i] = valueSaved;
            mpEnd += n;
        } else {
            for (size_type i = 0; i < n - nAfter; ++i)
                ::new (mpEnd + i) Elem40(valueSaved);
            for (Elem40* p = mpEnd - 1; p >= position; --p)
                p[n] = *p;
            for (size_type i = 0; i < nAfter; ++i)
                position[i] = valueSaved;
            mpEnd += n;
        }
    } else {
        size_type nOldSize = (size_type)(mpEnd - mpBegin);
        size_type nNewSize = nOldSize + n;
        if (nOldSize > 0 && nNewSize < 2 * nOldSize)
            nNewSize = 2 * nOldSize;
        Elem40* pNewData = nNewSize ? (Elem40*)EA_Allocate(&mAllocator, nNewSize << 6, 4, 0) : 0;
        Elem40* pNewEnd = UninitCopy40(mpBegin, position, pNewData);
        for (size_type i = 0; i < n; ++i)
            ::new (pNewEnd + i) Elem40(valueSaved);
        pNewEnd += n;
        pNewEnd = UninitCopy40(position, mpEnd, pNewEnd);
        destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------- fixed_vector<8-byte>
struct Alloc4 { uint32_t mFlags; };
void* FixedAlloc8(uint32_t n, void* first, void* last);      // 0x0056a0e0
void* FixedUninit8(void* first, void* last, void* dest);     // 0x004d0960

struct FixedVec8 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    Alloc4 mAllocator;
    void* mpInlineBuffer;    // +0x10
    void assign(void* first, void* last);   // 0x005283d0
};

// @ 0x005283d0
void FixedVec8::assign(void* first, void* last)
{
    uint32_t n = (uint32_t)(((char*)last - (char*)first) >> 3);
    if ((uint32_t)(((char*)mpCapacity - (char*)mpBegin) >> 3) < n) {
        void* pNew = FixedAlloc8(n, first, last);
        for (void* p = mpBegin; p < mpEnd; p = (char*)p + 8) { }
        void* old = mpBegin;
        if (old && old != mpInlineBuffer) {
            void* q = old;
            EA_Free(q);
        }
        mpBegin = pNew;
        mpEnd = (char*)mpBegin + n * 8;
        mpCapacity = mpEnd;
    } else if ((uint32_t)(((char*)mpEnd - (char*)mpBegin) >> 3) < n) {
        void* dst = mpBegin;
        uint32_t cur = (uint32_t)(((char*)mpEnd - (char*)mpBegin) >> 3);
        void* s = first;
        while (s != (char*)first + cur * 8) {
            *(uint32_t*)dst = *(uint32_t*)s;
            *((uint32_t*)dst + 1) = *((uint32_t*)s + 1);
            dst = (char*)dst + 8;
            s = (char*)s + 8;
        }
        void* newEnd = FixedUninit8((char*)first + cur * 8, last, mpEnd);
        mpEnd = newEnd;
    } else {
        void* dst = mpBegin;
        for (void* s = first; s != last; s = (char*)s + 8) {
            *(uint32_t*)dst = *(uint32_t*)s;
            *((uint32_t*)dst + 1) = *((uint32_t*)s + 1);
            dst = (char*)dst + 8;
        }
        for (void* p = dst; p < mpEnd; p = (char*)p + 8) { }
        mpEnd = dst;
    }
}
