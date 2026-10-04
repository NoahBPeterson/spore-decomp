// Slice s00532f80: Swarm barycentric helper, EASTL vector_map<uint32_t,float> (fixed_vector
// backed) members and eastl::sort pieces ordered by descending .second.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef unsigned int size_t;
typedef int ptrdiff_t;
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
inline void* operator new(size_t, void* p) { return p; }
void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line); // 0xf473a0
inline void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, name, flags, debugFlags, file, line); }
void EASTL_Free(char* p);                                                         // 0xf47380
void* EASTL_Allocate(void* pAllocator, size_t n, size_t alignment, size_t offset); // 0x42dee0

// ---------------------------------------------------------------- math
struct Vector3T {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v);                                // @ 0x4098a0 (out of line)
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    float Dot(const Vector3T& v) const { return x * v.x + y * v.y + z * v.z; }
};
struct Vector2T {
    float x, y;
    Vector2T(float x_, float y_);                               // @ 0x508780
    Vector2T(const Vector2T& v);                                // @ 0x51fb60
    static const Vector2T ZERO;                                 // @ 0x15e1394
};
struct cSPVector3Copy : Vector3T {
    cSPVector3Copy(const Vector3T& v) : Vector3T(v) {}
};
struct cSPVector2 : Vector2T {
    cSPVector2(const Vector2T& v) : Vector2T(v) {}
};
Vector3T operator-(const Vector3T& a, const Vector3T& b);      // @ 0x41db10
Vector3T Cross(const Vector3T& a, const Vector3T& b);          // @ 0x44e460
float Dot(const Vector3T& a, const Vector3T& b);               // @ 0x455cc0

// @ 0x00532f80
float LengthSquared(const Vector3T& v)
{
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

// @ 0x00532fe0
cSPVector2 BarycentricCoords(cSPVector3 a, cSPVector3 b, cSPVector3 c, cSPVector3 normal, cSPVector3 point)
{
    float areaC, areaA, areaB, sum;
    areaA = normal.Dot(Cross(cSPVector3(b - point), cSPVector3(c - point)));
    areaB = normal.Dot(Cross(cSPVector3(c - point), cSPVector3(a - point)));
    areaC = Dot(normal, Cross(cSPVector3Copy(a - point), cSPVector3(b - point)));
    sum = areaA + areaB + areaC;
    return (sum != 0.0f) ? Vector2T(areaB / sum, areaC / sum) : Vector2T::ZERO;
}

// ---------------------------------------------------------------- table lookup
struct cElement8C { uint32_t pad[0x8c / 4]; };
struct cElementTable { char pad[0x98]; cElement8C* mpElements; };
struct cElementOwner {
    char pad0[8];
    cElementTable* mpTable;         // +0x08
    char pad1[0x14];
    uint8_t* mpIndexRemap;          // +0x20
};

// @ 0x005332f0
cElement8C* GetElement(cElementOwner* owner, uint32_t index)
{
    if (index & 0x80000000) {
        uint8_t* pRemap = (index & 0x7fffffff) + owner->mpIndexRemap;
        cElementTable* table = owner->mpTable;
        return &table->mpElements[*pRemap];
    } else {
        cElementTable* table = owner->mpTable;
        return &table->mpElements[index];
    }
}

// ---------------------------------------------------------------- EASTL
namespace eastl {

template<typename T1, typename T2> struct pair {
    T1 first;
    T2 second;
    pair(const T1& x, const T2& y) : first(x), second(y) {}
};

template<typename T> struct less {
    bool operator()(const T& a, const T& b) const { return a < b; }
};

template<typename Pair> struct greater_second {
    bool operator()(const Pair& a, const Pair& b) const { return a.second > b.second; }
};

struct allocator {
    uint32_t mFlags;
    void deallocate(void* p, size_t) { delete[] (char*)p; }
};
struct fixed_vector_allocator {
    allocator mOverflowAllocator;
    void* mpPoolBegin;
    void deallocate(void* p, size_t n) { if (p != mpPoolBegin) mOverflowAllocator.deallocate(p, n); }
};

template<typename T> struct fixed_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    fixed_vector_allocator mAllocator;
    uint32_t mBuffer[0x44 / 4];

    fixed_vector();                                             // @ 0x41cfe0
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T* insert(T* position, const T& value);
    void DoInsertValue(T* position, const T& value);
    size_t GetNewCapacity(size_t currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
    T* DoAllocate(size_t n) { return n ? (T*)EASTL_Allocate(&mAllocator, n * sizeof(T), 4, 0) : 0; }
    void DoFree(T* p, size_t n) { if (p) mAllocator.deallocate(p, n); }
};

template<typename T> T* uninitialized_copy_ptr(T* first, T* last, T* result);   // @ 0x4554f0

template<typename T>
inline T* copy_backward_impl(T* first, T* last, T* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
template<typename T>
inline T* copy_backward(T* first, T* last, T* resultEnd)
{
    const bool t38 = false, n12 = false, n21 = false;
    return copy_backward_impl(first, last, resultEnd);
}

template<typename T>
T* fixed_vector<T>::insert(T* position, const T& value)
{
    const ptrdiff_t n = position - mpBegin;
    if ((position != mpEnd) || (mpEnd == mpCapacity))
        DoInsertValue(position, value);
    else
        ::new(mpEnd++) T(value);
    return mpBegin + n;
}

template<typename T>
void fixed_vector<T>::DoInsertValue(T* position, const T& value)
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

template<typename It, typename T, typename Compare>
It lower_bound(It first, It last, const T& value, Compare compare);              // @ 0x5701b0

template<typename Key, typename T, typename Compare = less<Key> >
struct vector_map : public fixed_vector<pair<Key, T> > {
    typedef fixed_vector<pair<Key, T> > base_type;
    typedef pair<Key, T> value_type;
    typedef value_type* iterator;
    struct value_compare {
        bool operator()(const value_type& a, const value_type& b) const { return a.first < b.first; }
        bool operator()(const Key& a, const value_type& b) const { return a < b.first; }
    };
    value_compare mValueCompare;    // +0x58

    vector_map() { ScratchSlots<4>(); }
    T& operator[](const Key& k);
    iterator insert(iterator position, const value_type& value);
};

template<typename Key, typename T, typename Compare>
T& vector_map<Key, T, Compare>::operator[](const Key& k)
{
    iterator itLB = lower_bound(this->begin(), this->end(), k, mValueCompare);
    uint32_t unused;
    if ((itLB == this->end()) || mValueCompare(k, *itLB)) {
        itLB = insert(itLB, value_type(k, T()));
    }
    return itLB->second;
}

template<typename Key, typename T, typename Compare>
typename vector_map<Key, T, Compare>::iterator
vector_map<Key, T, Compare>::insert(iterator position, const value_type& value)
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

template<typename Size> inline Size Log2(Size n)
{
    int i;
    for (i = 0; n; ++i)
        n >>= 1;
    return i;
}
template<typename It, typename Size, typename Compare>
void quick_sort_impl(It first, It last, Size kRecursionCount, Compare compare);  // @ 0x52c950

template<typename It, typename Compare>
inline void insertion_sort(It first, It last, Compare compare)
{
    if (first != last) {
        It iCurrent, iNext, iSorted = first;
        for (++iSorted; iSorted != last; ++iSorted) {
            const pair<uint32_t, float> temp(*iSorted);
            iNext = iCurrent = iSorted;
            for (--iCurrent; (iNext != first) && compare(temp, *iCurrent); --iNext, --iCurrent)
                *iNext = *iCurrent;
            *iNext = temp;
        }
    }
}

template<typename It, typename Compare>
inline void insertion_sort_simple(It first, It last, Compare compare)
{
    for (It current = first; current != last; ++current) {
        It end(current), prev(current);
        const pair<uint32_t, float> value(*current);
        for (--prev; compare(value, *prev); --end, --prev)
            *end = *prev;
        *end = value;
    }
}

template<typename It, typename Compare>
inline void sort(It first, It last, Compare compare)
{
    if (first != last) {
        quick_sort_impl(first, last, 2 * Log2(last - first) - 2, compare);
        if ((last - first) > 28) {
            insertion_sort(first, first + 28, compare);
            insertion_sort_simple(first + 28, last, compare);
        } else
            insertion_sort(first, last, compare);
    }
}

template<typename T, typename Compare>
inline const T& median(const T& a, const T& b, const T& c, Compare compare)
{
    if (compare(a, b)) {
        if (compare(b, c))
            return b;
        else if (compare(a, c))
            return c;
        else
            return a;
    } else if (compare(a, c))
        return a;
    else if (compare(b, c))
        return c;
    return b;
}

} // namespace eastl

typedef eastl::pair<uint32_t, float> WeightPair;
typedef eastl::greater_second<WeightPair> WeightCompare;
typedef eastl::vector_map<uint32_t, float> WeightMap;

// @ 0x00533410
template WeightMap::vector_map();
// @ 0x00533430
template float& WeightMap::operator[](const uint32_t&);
// @ 0x005335b0
template WeightMap::iterator WeightMap::insert(iterator, const value_type&);
// @ 0x00533740
template WeightPair* eastl::fixed_vector<WeightPair>::insert(WeightPair*, const WeightPair&);
// @ 0x00533960
template void eastl::fixed_vector<WeightPair>::DoInsertValue(WeightPair*, const WeightPair&);
// @ 0x00533680
template void eastl::sort(WeightPair*, WeightPair*, WeightCompare);
// @ 0x005337e0
template void eastl::insertion_sort(WeightPair*, WeightPair*, WeightCompare);
// @ 0x005338b0
template void eastl::insertion_sort_simple(WeightPair*, WeightPair*, WeightCompare);
// @ 0x00533ba0
template const WeightPair& eastl::median(const WeightPair&, const WeightPair&, const WeightPair&, WeightCompare);

// ---------------------------------------------------------------- misc
struct cIter {
    void* mp;
    cIter(void* p) : mp(p) {}
    cIter(const cIter& x) : mp(x.mp) {}
};
cIter FillImpl(void* first, void* last, void* value);         // @ 0x4c6ae0
inline cIter FillWrap(void* first, void* last, void* value) { void* f = first; return FillImpl(f, last, value); }

// @ 0x005334d0
void Fill(void* first, void* last, void* value)
{
    uint32_t mem;
    void* block = first;
    FillWrap(block, last, value);
}

struct cIVisualEffect { virtual void AddRef(); virtual void Release(); };
template<class T> struct AutoRefCount {
    T* mpObject;
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};
typedef AutoRefCount<cIVisualEffect> EffectRef;
EffectRef* CopyEffects(EffectRef* first, EffectRef* last, EffectRef* result);     // @ 0x42f530

struct cEffectVector {
    EffectRef* mpBegin;
    EffectRef* mpEnd;
    EffectRef* erase(EffectRef* first, EffectRef* last);
};

inline void DoDestroyValues(EffectRef* first, EffectRef* last)
{
    for (; first < last; ++first)
        first->~EffectRef();
}
inline EffectRef* copy(EffectRef* first, EffectRef* last, EffectRef* result)
{
    const bool t38 = false, n12 = false, n21 = false;
    ScratchSlots<2>();
    return CopyEffects(first, last, result);
}

// @ 0x00533500
EffectRef* cEffectVector::erase(EffectRef* first, EffectRef* last)
{
    EffectRef* position = copy(last, mpEnd, first);
    DoDestroyValues(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// ---------------------------------------------------------------- Swarm object factory
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

// @ 0x00533ce0
cSwarmObject* CreateSwarmObject(uint32_t param)
{
    cSwarmObject* p = new("Swarm", 0, 0, 0, 0) cSwarmObject(param);
    return p;
}

struct cFlagHolder {
    char pad[0x10];
    bool mbFlag;
    void ClearFlag(int);
};

// @ 0x00533d80
void cFlagHolder::ClearFlag(int)
{
    mbFlag = false;
}
