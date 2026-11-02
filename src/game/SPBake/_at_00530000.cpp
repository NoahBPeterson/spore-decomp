// src/game/SPBake/_at_00530000.cpp -- migrated from slice(s) s00532f80 by tools/migrate/rewrite.py
// Object file: SPBake/_at_00530000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00532f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int ptrdiff_t;
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
inline void* operator new(size_t, void* p) { return p; }
void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line); // 0xf473a0
inline void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, name, flags, debugFlags, file, line); }
void* EASTL_Allocate(void* pAllocator, size_t n, size_t alignment, size_t offset); // 0x42dee0
struct Vector3T {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v);                                // @ 0x4098a0 (out of line)
    const float& operator[](int i) const { return (&x)[i]; }
};
Vector3T operator-(const Vector3T& a, const Vector3T& b);      // @ 0x41db10
namespace eastl {
template<typename T1, typename T2> struct pair_s0053_2f80 {
    T1 first;
    T2 second;
    pair_s0053_2f80(const T1& x, const T2& y) : first(x), second(y) {}
};
}
namespace eastl {
template<typename T> struct less_s0053_2f80 {
    bool operator()(const T& a, const T& b) const { return a < b; }
};
}
namespace eastl {
class allocator_s0053_2f80 { public:
    uint32_t mFlags;
    void deallocate(void* p, size_t) { delete[] (char*)p; }
};
}
namespace eastl {
class fixed_vector_allocator { public:
    allocator_s0053_2f80 mOverflowAllocator;
    void* mpPoolBegin;
    void deallocate(void* p, size_t n) { if (p != mpPoolBegin) mOverflowAllocator.deallocate(p, n); }
};
}
namespace eastl {
template<typename T> class fixed_vector_s0053_2f80 { public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    fixed_vector_allocator mAllocator;
    uint32_t mBuffer[0x44 / 4];

    fixed_vector_s0053_2f80();                                             // @ 0x41cfe0
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T* insert(T* position, const T& value);
    void DoInsertValue(T* position, const T& value);
    size_t GetNewCapacity(size_t currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
    T* DoAllocate(size_t n) { return n ? (T*)EASTL_Allocate(&mAllocator, n * sizeof(T), 4, 0) : 0; }
    void DoFree(T* p, size_t n) { if (p) mAllocator.deallocate(p, n); }
};
}
namespace eastl {
template<typename T> T* uninitialized_copy_ptr(T* first, T* last, T* result);   // @ 0x4554f0
}
namespace eastl {
template<typename T>
inline T* copy_backward_impl(T* first, T* last, T* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
}
namespace eastl {
template<typename T>
inline T* copy_backward(T* first, T* last, T* resultEnd)
{
    const bool t38 = false, n12 = false, n21 = false;
    return copy_backward_impl(first, last, resultEnd);
}
}
namespace eastl {
template<typename T>
T* fixed_vector_s0053_2f80<T>::insert(T* position, const T& value)
{
    const ptrdiff_t n = position - mpBegin;
    if ((position != mpEnd) || (mpEnd == mpCapacity))
        DoInsertValue(position, value);
    else
        ::new(mpEnd++) T(value);
    return mpBegin + n;
}
}
namespace eastl {
template<typename T>
void fixed_vector_s0053_2f80<T>::DoInsertValue(T* position, const T& value)
{
    if (mpEnd != mpCapacity) {
        const T* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) T(*(mpEnd - 1));
        copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const size_t nPrevSize = size_t(mpEnd - mpBegin);
        const size_t nNewSize = GetNewCapacity(nPrevSize);
        T* const pNewData = DoAllocate(nNewSize);
        T* pNewEnd = uninitialized_copy_ptr(mpBegin, position, pNewData);
        ::new(pNewEnd) T(value);
        pNewEnd = uninitialized_copy_ptr(position, mpEnd, ++pNewEnd);
        ScratchSlots<16>();
        DoFree(mpBegin, (size_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
}
namespace eastl {
template<typename It, typename T, typename Compare>
It lower_bound(It first, It last, const T& value, Compare compare);              // @ 0x5701b0
}
namespace eastl {
template<typename Key, typename T, typename Compare = less_s0053_2f80<Key> >
class vector_map_s0053_2f80 : public fixed_vector_s0053_2f80<pair_s0053_2f80<Key, T> > { public:
    typedef fixed_vector_s0053_2f80<pair_s0053_2f80<Key, T> > base_type;
    typedef pair_s0053_2f80<Key, T> value_type;
    typedef value_type* iterator;
    struct value_compare {
        bool operator()(const value_type& a, const value_type& b) const { return a.first < b.first; }
        bool operator()(const Key& a, const value_type& b) const { return a < b.first; }
    };
    value_compare mValueCompare;    // +0x58

    vector_map_s0053_2f80() { ScratchSlots<4>(); }
    T& operator[](const Key& k);
    iterator insert(iterator position, const value_type& value);
};
}
namespace eastl {
template<typename Key, typename T, typename Compare>
T& vector_map_s0053_2f80<Key, T, Compare>::operator[](const Key& k)
{
    iterator itLB = lower_bound(this->begin(), this->end(), k, mValueCompare);
    uint32_t unused;
    if ((itLB == this->end()) || mValueCompare(k, *itLB)) {
        itLB = insert(itLB, value_type(k, T()));
    }
    return itLB->second;
}
}
namespace eastl {
template<typename Key, typename T, typename Compare>
typename vector_map_s0053_2f80<Key, T, Compare>::iterator
vector_map_s0053_2f80<Key, T, Compare>::insert(iterator position, const value_type& value)
{
    iterator itLB;
    if ((position != this->end()) && mValueCompare(value, *position))
        itLB = lower_bound(this->begin(), position, value, mValueCompare);
    else
        itLB = lower_bound(position, this->end(), value, mValueCompare);
    if ((itLB == this->end()) || mValueCompare(value, *itLB))
        itLB = base_type::insert(itLB, value);
    ScratchSlots<3>();
    return itLB;
}
}
typedef eastl::pair_s0053_2f80<uint32_t, float> WeightPair;
struct cIter {
    void* mp;
    cIter(void* p) : mp(p) {}
    cIter(const cIter& x) : mp(x.mp) {}
};
cIter FillImpl(void* first, void* last, void* value);         // @ 0x4c6ae0
struct ISwarmObject { virtual int AddRef(); virtual int Release(); };
struct cSwarmRefCounted {
    virtual int AddRef();
    int mnRefCount;
    cSwarmRefCounted() : mnRefCount(0) {}
};
struct cSwarmObjectBase : public ISwarmObject, public cSwarmRefCounted {
    cSwarmObjectBase() {}
    virtual int AddRef();
};
struct cSwarmObject : public cSwarmObjectBase {
    uint32_t mUnused;
    uint32_t mParam;
    cSwarmObject(uint32_t p) { mUnused = p; }
    virtual int AddRef();
};
struct cFlagHolder {
    char pad[0x10];
    bool mbFlag;
    void ClearFlag(int);
};
// ---- items of slice s00532f80 end

// @ 0x00533960
template void eastl::fixed_vector_s0053_2f80<WeightPair>::DoInsertValue(WeightPair*, const WeightPair&)
;

// @ 0x00533ba0
inline cIter FillWrap(void* first, void* last, void* value)
{ void* f = first; return FillImpl(f, last, value); }

// @ 0x00533ce0
cSwarmObject* CreateSwarmObject(uint32_t param)
{
    cSwarmObject* p = new("Swarm", 0, 0, 0, 0) cSwarmObject(param);
    return p;
}

// @ 0x00533d80
void cFlagHolder::ClearFlag(int)
{
    mbFlag = false;
}
