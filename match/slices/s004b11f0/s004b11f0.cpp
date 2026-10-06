// Slice s004b11f0 — vector element (de)allocation helpers.
#include "types.h"
#pragma pack(push, 4)

struct AutoRef {
    void* mpObject;   // +0x0
    AutoRef* Set(void* v);
};

// @ 0x004b22b0
void FillAutoRef(AutoRef* first, AutoRef* last, void** value)
{
    void* old;
    for (; first != last; ++first) {
        void* v = *value;
        if (v != first->mpObject) {
            old = first->mpObject;
            if (v != 0) {
                (*(void(__thiscall*)(void*))(*(void**)((char*)*(void**)v + 4)))(v);
            }
            first->mpObject = v;
            if (old != 0) {
                (*(void(__thiscall*)(void*))(*(void**)((char*)*(void**)old + 8)))(old);
            }
        }
    }
}

// @ 0x004b2220
void** UninitCopyAutoRef(void** out, void** first, void** last, void** dest)
{
    for (; first != last; ++first) {
        if (dest != 0) {
            *dest = *first;
            if (*dest != 0) {
                (*(void(__thiscall*)(void*))(*(void**)((char*)*(void**)*dest + 4)))(*dest);
            }
        }
        ++dest;
    }
    *out = dest;
    return out;
}


// ---------------------------------------------------------------------------
// eastl::vector<T> instances (editor /Od region): DoInsertValues for a 0x1d8-byte and a 0x18-byte element,
// DoAssignFromIterator for the 0x18-byte element, DoAssignValues for 4-byte elements.
// ---------------------------------------------------------------------------
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

void EASTLFree(void* p);                                                         // 0x00F47380 operator delete[]
void* EASTLAlloc(void* allocator, uint32_t n, uint32_t align, uint32_t offset);  // 0x0042DEE0

namespace eastl {

struct false_type {};
struct EASTLAllocator { const char* mpName; EASTLAllocator() {} };
struct random_access_iterator_tag { random_access_iterator_tag() {} };

struct Big {                                   // 0x1d8-byte element, out-of-line copy ctor (0x004721E0)
    uint32_t d[0x76];
    Big(const Big& o);
};

struct Vector3 {
    uint32_t x, y, z;                          // copied as integers
    Vector3(const Vector3& v);                 // 0x004098A0 (out of line)
};

struct S24 {                                   // two Vector3, assigned second-half first
    Vector3 a;
    Vector3 b;
    S24& operator=(const S24& o) { b = o.b; a = o.a; return *this; }
};

template <class T> struct generic_iterator {
    T mIterator;
    explicit generic_iterator(const T& x) : mIterator(x) {}
    const T& base() const { return mIterator; }
};
template <class T> struct value_of;
template <class T> struct value_of<T*> { typedef T type; };
template <class T> struct value_of<const T*> { typedef T type; };
template <class T> struct has_trivial_relocate : public false_type {};

template <class T> T* uninitialized_move(T* first, T* last, T* dest);              // out of line
template <class T> T* uninitialized_copy_ool(T* first, T* last, T* dest);          // out of line
template <class In, class Out>
generic_iterator<Out> uninitialized_copy_impl(generic_iterator<In> first, generic_iterator<In> last,
                                              generic_iterator<Out> dest, false_type);
template <class It, class T>
void uninitialized_fill_n_impl(generic_iterator<It> first, uint32_t n, const T& value, false_type);

template <class First, class Last, class Result>
inline Result uninitialized_copy_ptr(First first, Last last, Result result)
{
    const generic_iterator<Result> i(uninitialized_copy_impl(generic_iterator<First>(first),
                                                             generic_iterator<Last>(last),
                                                             generic_iterator<Result>(result),
                                                             has_trivial_relocate<typename value_of<Result>::type>()));
    return i.base();
}

template <class T>
inline void uninitialized_fill_n_ptr(T* first, uint32_t n, const T& value)
{
    uninitialized_fill_n_impl(generic_iterator<T*>(first), n, value, has_trivial_relocate<T>());
}

template <class Bi1, class Bi2>
__forceinline Bi2 copy_backward_impl(Bi1 first, Bi1 last, Bi2 resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}

template <class T>
__forceinline T* copy_backward_loop(T* first, T* last, T* resultEnd)
{
    const bool bIsMove = false;
    const bool bCanMemmove = false;
    const bool bIsPod = false;
    return copy_backward_impl(first, last, resultEnd);
}

template <class T>
inline void fill(T* first, T* last, const T& value)
{
    for (; first != last; ++first)
        *first = value;
}

template <class T>
inline T* copy_loop(const T* first, const T* last, T* result)
{
    const bool bIsMove = false;
    const bool bCanMemmove = false;
    const bool bIsPod = false;
    for (; first != last; ++first, ++result)
        *result = *first;
    return result;
}

template <class T>
inline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        ;
}

template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    EASTLAllocator mAllocator;

    inline uint32_t GetNewCapacity(uint32_t currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
    inline T* DoAllocate(uint32_t n) { return n ? (T*)EASTLAlloc(&mAllocator, n * sizeof(T), 4, 0) : 0; }
    inline void DoFree(T* p, uint32_t n) { if (p) deallocate(p, n * sizeof(T)); }
    static void deallocate(void* p, uint32_t) { if (*((uint32_t*)p - 1)) FreeBlock(p); }
    static void FreeBlock(void* p) { void* pBlock = p; EASTLFree(pBlock); }
    void DoInsertValues(T* position, uint32_t n, const T& value);
    T* DoRealloc(uint32_t n, const T* first, const T* last);                      // 0x0050E750 (S24)
    void DoAssignFromIterator(const T* first, const T* last, random_access_iterator_tag);
    void DoAssignValues(uint32_t n, const T& value);
    vector() {}
    vector(uint32_t n, const EASTLAllocator& a);                                  // 0x004AA350
    ~vector();                                                                    // 0x004E1BF0
    void swap(vector& o);                                                         // 0x0052C730
    void erase_ool(T* first, T* last);                                            // 0x004769B0
};
void FillN32(uint32_t* first, uint32_t n, const uint32_t* value);                 // 0x0042E240
generic_iterator<uint32_t*> uninitialized_fill_n_raw(generic_iterator<uint32_t*> first, uint32_t n, const uint32_t& value);  // 0x004AB450
inline uint32_t* uninitialized_fill_n_it(uint32_t* first, uint32_t n, const uint32_t& value)
{
    const generic_iterator<uint32_t*> r(uninitialized_fill_n_raw(generic_iterator<uint32_t*>(first), n, value));
    return r.base();
}
inline void uninitialized_fill_n_outer(generic_iterator<uint32_t*> first, uint32_t n, const uint32_t& value)
{
    uninitialized_fill_n_it(first.base(), n, value);
}

// @ 0x004b11f0
template <> void vector<Big>::DoInsertValues(Big* position, uint32_t n, const Big& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const Big temp(value);
            ScratchSlots<1>();
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            Big* const pEnd = mpEnd;
            if (n < nExtra) {
                uninitialized_copy_ptr(mpEnd - n, mpEnd, mpEnd);
                mpEnd += n;
                copy_backward_loop(position, pEnd - n, pEnd);
                fill(position, position + n, temp);
            } else {
                uninitialized_fill_n_ptr(mpEnd, n - nExtra, temp);
                mpEnd += n - nExtra;
                uninitialized_copy_ptr(position, pEnd, mpEnd);
                mpEnd += nExtra;
                fill(position, pEnd, temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = GetNewCapacity(nPrevSize);
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        Big* const pNewData = DoAllocate(nNewSize);
        Big* pNewEnd = uninitialized_move(mpBegin, position, pNewData);
        ScratchSlots<8>();
        uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd = uninitialized_move(position, mpEnd, pNewEnd + n);
        ScratchSlots<8>();
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x004b1800
template <> void vector<S24>::DoInsertValues(S24* position, uint32_t n, const S24& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const S24 temp(value);
            ScratchSlots<1>();
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            S24* const pEnd = mpEnd;
            if (n < nExtra) {
                uninitialized_copy_ptr(mpEnd - n, mpEnd, mpEnd);
                mpEnd += n;
                copy_backward_loop(position, pEnd - n, pEnd);
                fill(position, position + n, temp);
            } else {
                uninitialized_fill_n_ptr(mpEnd, n - nExtra, temp);
                mpEnd += n - nExtra;
                uninitialized_copy_ool(position, pEnd, mpEnd);
                mpEnd += nExtra;
                fill(position, pEnd, temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = GetNewCapacity(nPrevSize);
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        S24* const pNewData = DoAllocate(nNewSize);
        S24* pNewEnd = uninitialized_move(mpBegin, position, pNewData);
        uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd = uninitialized_copy_ool(position, mpEnd, pNewEnd + n);
        destruct(position, mpEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x004b1cc0
template <> void vector<S24>::DoAssignFromIterator(const S24* first, const S24* last, random_access_iterator_tag)
{
    const uint32_t n = (uint32_t)(last - first);
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        S24* const pNewData = DoRealloc(n, first, last);
        ScratchSlots<11>();
        destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = mpBegin + n;
        mpCapacity = mpEnd;
    } else if (n <= (uint32_t)(mpEnd - mpBegin)) {
        S24* const position = copy_loop(first, last, mpBegin);
        destruct(position, mpEnd);
        mpEnd = position;
    } else {
        const S24* position = first + (mpEnd - mpBegin);
        copy_loop(first, position, mpBegin);
        mpEnd = uninitialized_copy_ool(const_cast<S24*>(position), const_cast<S24*>(last), mpEnd);
    }
}

// @ 0x004b2030
template <> void vector<uint32_t>::DoAssignValues(uint32_t n, const uint32_t& value)
{
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        vector<uint32_t> tmp(n, mAllocator);
        uninitialized_fill_n_outer(generic_iterator<uint32_t*>(tmp.mpBegin), n, value);
        tmp.mpEnd = tmp.mpBegin + n;
        swap(tmp);
    } else if (n > (uint32_t)(mpEnd - mpBegin)) {
        uint32_t* const pEnd = mpEnd;
        const uint32_t v = value;
        for (uint32_t* p = mpBegin; p != pEnd; ++p)
            *p = v;
        uninitialized_fill_n_it(mpEnd, n - (uint32_t)(mpEnd - mpBegin), value);
        mpEnd = mpEnd + (n - (uint32_t)(mpEnd - mpBegin));
    } else {
        FillN32(mpBegin, n, &value);
        erase_ool(mpBegin + n, mpEnd);
    }
}

} // namespace eastl
