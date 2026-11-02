// src/game/SPBake/_at_004b0000.cpp -- migrated from slice(s) s004b2320, s004b11f0, s004b0490 by tools/migrate/rewrite.py
// Object file: SPBake/_at_004b0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>

// ---- items of slice s004b0490 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct V3 { float x, y, z; };
struct B24 { V3 a; V3 b; };
struct Vec24 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;

    void Wrapper(void* a, void* b);       // 0x4b0560
    B24* Erase24(B24* dst, B24* end);     // 0x4b0490
    void Other(void* a, void** b);        // 0x4b2030
};
struct sp_vector_allocator { };
void* AllocatorAllocate(const void* allocator, unsigned size, unsigned align, unsigned flags); // 0x42dee0
void AllocatorDeallocate(void* p);                                                             // 0xf47380
struct AutoRef {
    void* mpObject;   // +0x0
    AutoRef* Set(void* v);
    void AddRef() { (*(void(__thiscall*)(void*))(*(void**)((char*)mpObject + 4)))(mpObject); }
    void Release() { (*(void(__thiscall*)(void*))(*(void**)((char*)*(void**)mpObject + 8)))(mpObject); }
    AutoRef() : mpObject(0) { }
    AutoRef(const AutoRef& other) : mpObject(other.mpObject) { if (mpObject != 0) AddRef(); }
    ~AutoRef() { if (mpObject != 0) Release(); }
};
void ConstructArray(AutoRef* dst, unsigned n, const AutoRef* value, bool tag);        // 0x4b2320
void UninitializedCopyRef(AutoRef** result, AutoRef* first, AutoRef* last, AutoRef* dst); // 0x4b2220
void FillRef(AutoRef* first, AutoRef* last, const AutoRef* value);                    // 0x4b22b0
void CopyRef(AutoRef* first, AutoRef* last, AutoRef* dst);                            // 0x4551e0
struct AutoRefVector {
    AutoRef* mpBegin;
    AutoRef* mpEnd;
    AutoRef* mpCapacity;
    sp_vector_allocator mAllocator;

    void DoInsertValues(AutoRef* position, unsigned n, const AutoRef* value);         // 0x4b0590
};
void UninitializedFillFloat(float** result, float* dst, unsigned n, const float* value);   // 0x42efc0
void UninitializedCopyFloat(float** result, const float* first, const float* last, float* dst); // 0x4d1240
struct FloatVector {
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    sp_vector_allocator mAllocator;

    void DoInsertValues(float* position, unsigned n, const float* value);             // 0x4b0a10
};
struct Elem1d8 { unsigned int mData[0x76]; };
void UninitializedCopy24(const Elem1d8* first, const Elem1d8* last, Elem1d8* dst);       // 0x4b1760
struct Record1d8Vector {
    Elem1d8* mpBegin;
    Elem1d8* mpEnd;
    Elem1d8* mpCapacity;

    Elem1d8* DoAllocateAndCopy(int n, const Elem1d8* first, const Elem1d8* last);        // 0x4b1f50
    Record1d8Vector& Assign(const Record1d8Vector& other);                               // 0x4b0ef0
};
// ---- items of slice s004b0490 end

// ---- items of slice s004b11f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 4)
struct AutoRef_s004b_11f0 {
    void* mpObject;   // +0x0
    AutoRef_s004b_11f0* Set(void* v);  // 0x004b09b0 (AutoRef::Set)
};
template <int N> inline void ScratchSlots() { uint32_t s[N]; }
void EASTLFree(void* p);                                                         // 0x00F47380 operator delete[]
void* EASTLAlloc(void* allocator, uint32_t n, uint32_t align, uint32_t offset);  // 0x0042DEE0
namespace eastl {
struct false_type {};
}
namespace eastl {
struct EASTLAllocator { const char* mpName; EASTLAllocator() {} };
}
namespace eastl {
struct random_access_iterator_tag { random_access_iterator_tag() {} };
}
namespace eastl {
struct Vector3 {
    uint32_t x, y, z;                          // copied as integers
    Vector3(const Vector3& v);                 // 0x004098A0 (out of line)
};
}
namespace eastl {
struct S24 {                                   // two Vector3, assigned second-half first
    Vector3 a;
    Vector3 b;
    S24& operator=(const S24& o) { b = o.b; a = o.a; return *this; }
};
}
namespace eastl {
template <class T> class generic_iterator { public:
    T mIterator;
    explicit generic_iterator(const T& x) : mIterator(x) {}
    const T& base() const { return mIterator; }
};
}
namespace eastl {
template <class T> struct value_of;
}
namespace eastl {
template <class T> struct value_of<T*> { typedef T type; };
}
namespace eastl {
template <class T> struct value_of<const T*> { typedef T type; };
}
namespace eastl {
template <class T> struct has_trivial_relocate : public false_type {};
}
namespace eastl {
template <class T> T* uninitialized_move(T* first, T* last, T* dest);              // out of line
}
namespace eastl {
template <class T> T* uninitialized_copy_ool(T* first, T* last, T* dest);          // out of line
}
namespace eastl {
template <class T> T* uninitialized_move_start(T* first, T* last, T* dest);        // out of line (S24: 0x00512000)
}
namespace eastl {
template <class In, class Out>
generic_iterator<Out> uninitialized_copy_impl(generic_iterator<In> first, generic_iterator<In> last,
                                              generic_iterator<Out> dest, false_type);
}
namespace eastl {
template <class It, class T>
void uninitialized_fill_n_impl(generic_iterator<It> first, uint32_t n, const T& value, false_type);
}
namespace eastl {
template <class First, class Last, class Result>
inline Result uninitialized_copy_ptr(First first, Last last, Result result)
{
    const generic_iterator<Result> i(uninitialized_copy_impl(generic_iterator<First>(first),
                                                             generic_iterator<Last>(last),
                                                             generic_iterator<Result>(result),
                                                             has_trivial_relocate<typename value_of<Result>::type>()));
    return i.base();
}
}
namespace eastl {
template <class T>
inline void uninitialized_fill_n_ptr(T* first, uint32_t n, const T& value)
{
    uninitialized_fill_n_impl(generic_iterator<T*>(first), n, value, has_trivial_relocate<T>());
}
}
namespace eastl {
template <class Bi1, class Bi2>
__forceinline Bi2 copy_backward_impl(Bi1 first, Bi1 last, Bi2 resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
}
namespace eastl {
template <class T>
__forceinline T* copy_backward_loop(T* first, T* last, T* resultEnd)
{
    const bool bIsMove = false;
    const bool bCanMemmove = false;
    const bool bIsPod = false;
    return copy_backward_impl(first, last, resultEnd);
}
}
namespace eastl {
template <class T>
inline void fill(T* first, T* last, const T& value)
{
    for (; first != last; ++first)
        *first = value;
}
}
namespace eastl {
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
}
namespace eastl {
template <class T>
inline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        ;
}
}
namespace eastl {
template <class T>
class vector_s004b_11f0 { public:
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
    vector_s004b_11f0() {}
    vector_s004b_11f0(uint32_t n, const EASTLAllocator& a);                                  // 0x004AA350
    ~vector_s004b_11f0();                                                                    // 0x004E1BF0
    void swap(vector_s004b_11f0& o);                                                         // 0x0052C730
    void erase_ool(T* first, T* last);                                            // 0x004769B0
};
}
namespace eastl {
void FillN32(uint32_t* first, uint32_t n, const uint32_t* value);                 // 0x0042E240
}
namespace eastl {
generic_iterator<uint32_t*> uninitialized_fill_n_raw(generic_iterator<uint32_t*> first, uint32_t n, const uint32_t& value);  // 0x004AB450
}
namespace eastl {
inline uint32_t* uninitialized_fill_n_it(uint32_t* first, uint32_t n, const uint32_t& value)
{
    const generic_iterator<uint32_t*> r(uninitialized_fill_n_raw(generic_iterator<uint32_t*>(first), n, value));
    return r.base();
}
}
namespace eastl {
inline void uninitialized_fill_n_outer(generic_iterator<uint32_t*> first, uint32_t n, const uint32_t& value)
{
    uninitialized_fill_n_it(first.base(), n, value);
}
}
// ---- items of slice s004b11f0 end

// ---- items of slice s004b2320 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RefCounted { virtual void V0(); virtual void V1(); };
// ---- items of slice s004b2320 end

// @ 0x004b0490
B24* Vec24::Erase24(B24* param_2, B24* param_3)
{
    B24* out = (B24*)mpEnd;
    B24* local_14 = param_2;
    for (B24* local_10 = param_3; local_10 != out;
         local_10 = (B24*)((char*)local_10 + 0x18)) {
        local_14->b = local_10->b;
        local_14->a = local_10->a;
        local_14 = (B24*)((char*)local_14 + 0x18);
    }
    for (B24* local_1c = local_14; local_1c < (B24*)mpEnd;
         local_1c = (B24*)((char*)local_1c + 0x18)) {
    }
    mpEnd = mpEnd + ((char*)param_3 - (char*)param_2) / 0x18 * -0x18;
    return param_2;
}

// @ 0x004b0560
void Vec24::Wrapper(void* a, void* b)
{
    void* local[2];
    local[0] = b;
    Other(a, local);
}

// @ 0x004b0590
void AutoRefVector::DoInsertValues(AutoRef* position, unsigned n, const AutoRef* value)
{
    if ((unsigned)(mpCapacity - mpEnd) < n) {
        unsigned nOldSize = (unsigned)(mpEnd - mpBegin);
        unsigned nGrow = nOldSize ? nOldSize * 2 : 1;
        unsigned nNewSize = nGrow > nOldSize + n ? nGrow : nOldSize + n;
        AutoRef* pNewData = nNewSize
            ? (AutoRef*)AllocatorAllocate(&mAllocator, nNewSize * sizeof(AutoRef), 4, 0) : 0;
        AutoRef* pNewPos = (AutoRef*)memcpy(pNewData, mpBegin,
            (unsigned)((char*)position - (char*)mpBegin)) + (position - mpBegin);
        ConstructArray(pNewPos, n, value, false);
        AutoRef* pNewEnd = (AutoRef*)memcpy(pNewPos + n, position,
            (unsigned)((char*)mpEnd - (char*)position)) + (mpEnd - position);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            AllocatorDeallocate(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    } else if (n > 0) {
        AutoRef temp(*value);
        unsigned nExtra = (unsigned)(mpEnd - position);
        AutoRef* pOldEnd = mpEnd;
        if (n < nExtra) {
            AutoRef* result;
            UninitializedCopyRef(&result, mpEnd - n, mpEnd, mpEnd);
            mpEnd = pOldEnd + n;
            AutoRef* src = pOldEnd - n;
            AutoRef* dst = pOldEnd;
            while (src != position) {
                --src;
                --dst;
                dst->Set(src->mpObject);
            }
            FillRef(position, position + n, &temp);
        } else {
            ConstructArray(mpEnd, n - nExtra, &temp, false);
            mpEnd = pOldEnd + (n - nExtra);
            CopyRef(position, pOldEnd, mpEnd);
            mpEnd = mpEnd + nExtra;
            FillRef(position, pOldEnd, &temp);
        }
    }
}

// @ 0x004b09b0
AutoRef* AutoRef::Set(void* v)
{
    if (v != mpObject) {
        void* old = mpObject;
        if (v != 0) {
            (*(void(__thiscall*)(void*))(*(void**)((char*)*(void**)v + 4)))(v);
        }
        mpObject = v;
        if (old != 0) {
            (*(void(__thiscall*)(void*))(*(void**)((char*)*(void**)old + 8)))(old);
        }
    }
    return this;
}

// @ 0x004b0a10
void FloatVector::DoInsertValues(float* position, unsigned n, const float* value)
{
    if ((unsigned)(mpCapacity - mpEnd) < n) {
        unsigned nOldSize = (unsigned)(mpEnd - mpBegin);
        unsigned nGrow = nOldSize ? nOldSize * 2 : 1;
        unsigned nNewSize = nGrow > nOldSize + n ? nGrow : nOldSize + n;
        float* pNewData = nNewSize
            ? (float*)AllocatorAllocate(&mAllocator, nNewSize * sizeof(float), 4, 0) : 0;
        float* pNewPos = (float*)memcpy(pNewData, mpBegin,
            (unsigned)((char*)position - (char*)mpBegin)) + (position - mpBegin);
        {
            float* result;
            UninitializedFillFloat(&result, pNewPos, n, value);
        }
        float* pNewEnd = (float*)memcpy(pNewPos + n, position,
            (unsigned)((char*)mpEnd - (char*)position)) + (mpEnd - position);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            AllocatorDeallocate(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    } else if (n > 0) {
        float temp = *value;
        unsigned nExtra = (unsigned)(mpEnd - position);
        float* pOldEnd = mpEnd;
        if (n < nExtra) {
            float* result;
            UninitializedCopyFloat(&result, mpEnd - n, mpEnd, mpEnd);
            mpEnd = pOldEnd + n;
            memmove(position + n, position, (unsigned)((char*)(pOldEnd - n) - (char*)position));
            for (float* p = position; p != position + n; ++p)
                *p = temp;
        } else {
            float* result;
            UninitializedFillFloat(&result, mpEnd, n - nExtra, &temp);
            mpEnd = pOldEnd + (n - nExtra);
            float* result2;
            UninitializedCopyFloat(&result2, position, pOldEnd, mpEnd);
            mpEnd = mpEnd + nExtra;
            for (float* p = position; p != pOldEnd; ++p)
                *p = temp;
        }
    }
}

// @ 0x004b0ef0
Record1d8Vector& Record1d8Vector::Assign(const Record1d8Vector& other)
{
    if (this != &other) {
        int n = (int)((other.mpEnd - other.mpBegin) / (int)sizeof(Elem1d8));
        if ((unsigned)((mpCapacity - mpBegin) / (int)sizeof(Elem1d8)) < (unsigned)n) {
            Elem1d8* pNewData = DoAllocateAndCopy(n, other.mpBegin, other.mpEnd);
            for (Elem1d8* p = mpBegin; p < mpEnd; ++p) {
            }
            if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
                AllocatorDeallocate(mpBegin);
            mpBegin = pNewData;
            mpCapacity = mpBegin + n;
        } else if ((unsigned)((mpEnd - mpBegin) / (int)sizeof(Elem1d8)) < (unsigned)n) {
            Elem1d8* dst = mpBegin;
            const Elem1d8* src = other.mpBegin;
            const Elem1d8* srcEnd = other.mpBegin + (mpEnd - mpBegin) / (int)sizeof(Elem1d8);
            while (src != srcEnd) {
                *dst = *src;
                ++dst;
                ++src;
            }
            UninitializedCopy24(srcEnd, other.mpEnd, mpEnd);
        } else {
            Elem1d8* dst = mpBegin;
            for (const Elem1d8* src = other.mpBegin; src != other.mpEnd; ++src) {
                *dst = *src;
                ++dst;
            }
            for (Elem1d8* p = dst; p < mpEnd; ++p) {
            }
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x004b1800
namespace eastl {
template <> void vector_s004b_11f0<S24>::DoInsertValues(S24* position, uint32_t n, const S24& value)
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
        pNewEnd = uninitialized_move_start(position, mpEnd, pNewEnd + n);
        destruct(position, mpEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
}  // namespace eastl

// @ 0x004b1cc0
namespace eastl {
template <> void vector_s004b_11f0<S24>::DoAssignFromIterator(const S24* first, const S24* last, random_access_iterator_tag)
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
}  // namespace eastl

// @ 0x004b2030
namespace eastl {
template <> void vector_s004b_11f0<uint32_t>::DoAssignValues(uint32_t n, const uint32_t& value)
{
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        vector_s004b_11f0<uint32_t> tmp(n, mAllocator);
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
}  // namespace eastl

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

// @ 0x004b22b0
void FillAutoRef(AutoRef_s004b_11f0* first, AutoRef_s004b_11f0* last, void** value)
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

// @ 0x004b2320
void ConstructArray(RefCounted** p, unsigned int n, RefCounted** src)
{
    while (n != 0) {
        if (p != 0) {
            *p = *src;
            if (*p != 0)
                (*p)->V1();
        }
        --n;
        ++p;
    }
}
