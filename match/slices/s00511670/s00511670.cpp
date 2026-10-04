// s00511670: EASTL algorithm instantiations (heap sort with an extent comparator,
// uninitialized copy/fill/relocate for a 100-byte element), a triangle-normal helper
// and a container owner (two vectors + a map).
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
// ScratchSlots<N>() reproduces unused stack slots left by inlined helpers.
#include "types.h"

extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);   // 0x011e0744 (static thunk)
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}
void operator delete(void* p);   // 0x00f47380

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}

namespace eastl {

template <typename T, T v> struct integral_constant { static const T value = v; };
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;
template <typename T> struct has_trivial_relocate : false_type {};
template <> struct has_trivial_relocate<uint32_t> : true_type {};
template <typename T> struct has_trivial_assign : false_type {};

struct allocator { allocator() {} };

template <typename Iterator> struct generic_iterator {
    Iterator mIterator;
    generic_iterator(const Iterator& x) : mIterator(x) {}
    Iterator base() const { return mIterator; }
};
template <typename T> struct generic_iterator<T*> {
    T* mIterator;
    generic_iterator(T* x) : mIterator(x) {}
    T* base() const { return mIterator; }
    T& operator*() const { return *mIterator; }
    generic_iterator& operator++() { ++mIterator; return *this; }
};
template <typename I>
inline bool operator!=(const generic_iterator<I>& a, const generic_iterator<I>& b) { return a.mIterator != b.mIterator; }
template <typename T> struct is_generic_iterator : false_type {};
template <typename I> struct is_generic_iterator<generic_iterator<I> > : true_type {};

// eastl::fixed_vector<uint32_t, 16, true>
struct VectorBaseU32 {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator[3];
    ~VectorBaseU32();                                  // 0x004c0b80
};
struct fixed_vector_u32_16 : VectorBaseU32 {
    uint32_t mBuffer[16];
    fixed_vector_u32_16(const fixed_vector_u32_16& x);  // 0x0050e5f0
    ~fixed_vector_u32_16()
    {
        for (uint32_t* p = mpBegin; p < mpEnd; ++p)
            ;
    }
};

} // namespace eastl

// 100-byte element: a fixed list plus three floats
struct Elem {
    eastl::fixed_vector_u32_16 mList;   // +0x00
    float mA;                           // +0x58
    float mB;                           // +0x5c
    float mC;                           // +0x60
    Elem& operator=(const Elem& x);     // 0x0050f210
};

struct Vec3i { uint32_t x, y, z; };

// sorted object: extent along one axis is mMax - mMin
struct Obj {
    char pad[0x60];
    float mMin;   // +0x60
    float mMax;   // +0x64
};

struct ExtentCompare {
    bool mbAscending;
    __forceinline bool operator()(const Obj* a, const Obj* b) const
    {
        float extentA = a->mMax - a->mMin;
        float extentB = b->mMax - b->mMin;
        if (mbAscending)
            return extentA < extentB;
        else
            return extentA > extentB;
    }
};

namespace eastl {

// ---------------------------------------------------------------- heap (with compare)
// @ 0x005120D0  eastl::promote_heap<const Obj**, int, const Obj*, ExtentCompare>
template <typename RandomAccessIterator, typename Distance, typename T, typename Compare>
void promote_heap(RandomAccessIterator first, Distance topPosition, Distance position, T value, Compare compare)
{
    for (Distance parentPosition = (position - 1) >> 1;
         (position > topPosition) && compare(*(first + parentPosition), value);
         parentPosition = (position - 1) >> 1) {
        *(first + position) = *(first + parentPosition);
        position = parentPosition;
    }
    *(first + position) = value;
}

// @ 0x00511A50  eastl::adjust_heap<const Obj**, int, const Obj*, ExtentCompare>
template <typename RandomAccessIterator, typename Distance, typename T, typename Compare>
void adjust_heap(RandomAccessIterator first, Distance topPosition, Distance heapSize, Distance position, T value, Compare compare)
{
    Distance childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(*(first + childPosition), *(first + (childPosition - 1))))
            --childPosition;
        *(first + position) = *(first + childPosition);
        position = childPosition;
    }
    if (childPosition == heapSize) {
        *(first + position) = *(first + (childPosition - 1));
        position = childPosition - 1;
    }
    ScratchSlots<5>();
    eastl::promote_heap<RandomAccessIterator, Distance, T, Compare>(first, topPosition, position, value, compare);
}

// @ 0x005119F0  eastl::make_heap<const Obj**, ExtentCompare>
template <typename RandomAccessIterator, typename Compare>
void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    const int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            eastl::adjust_heap<RandomAccessIterator, int, const Obj*, Compare>(first, parentPosition, heapSize, parentPosition, *(first + parentPosition), compare);
        } while (parentPosition != 0);
    }
}

// @ 0x00511B80  eastl::sort_heap<const Obj**, ExtentCompare>
template <typename RandomAccessIterator, typename Compare>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    for (; (last - first) > 1; --last) {
        const Obj* tempBottom(*(last - 1));
        *(last - 1) = *first;
        eastl::adjust_heap<RandomAccessIterator, int, const Obj*, Compare>(first, 0, (int)(last - first - 1), 0, tempBottom, compare);
    }
}

// @ 0x00511670  eastl::partial_sort<const Obj**, ExtentCompare>
template <typename RandomAccessIterator, typename Compare>
void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, Compare compare)
{
    eastl::make_heap<RandomAccessIterator, Compare>(first, middle, compare);
    for (RandomAccessIterator i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            ScratchSlots<1>();
            const Obj* temp(*i);
            *i = *first;
            eastl::adjust_heap<RandomAccessIterator, int, const Obj*, Compare>(first, int(0), int(middle - first), int(0), temp, compare);
        }
    }
    eastl::sort_heap<RandomAccessIterator, Compare>(first, middle, compare);
}

template void partial_sort<const Obj**, ExtentCompare>(const Obj**, const Obj**, const Obj**, ExtentCompare);

// ---------------------------------------------------------------- heap (uint32_t, operator<)
template <typename RandomAccessIterator, typename Distance, typename T>
inline void promote_heap(RandomAccessIterator first, Distance topPosition, Distance position, T value)
{
    for (Distance parentPosition = (position - 1) >> 1;
         (position > topPosition) && (*(first + parentPosition) < value);
         parentPosition = (position - 1) >> 1) {
        *(first + position) = *(first + parentPosition);
        position = parentPosition;
    }
    *(first + position) = value;
}

// @ 0x00511E30  eastl::adjust_heap<uint32_t*, int, uint32_t>
template <typename RandomAccessIterator, typename Distance, typename T>
void adjust_heap(RandomAccessIterator first, Distance topPosition, Distance heapSize, Distance position, T value)
{
    Distance childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (*(first + childPosition) < *(first + (childPosition - 1)))
            --childPosition;
        *(first + position) = *(first + childPosition);
        position = childPosition;
    }
    if (childPosition == heapSize) {
        *(first + position) = *(first + (childPosition - 1));
        position = childPosition - 1;
    }
    eastl::promote_heap<RandomAccessIterator, Distance, T>(first, topPosition, position, value);
}

// @ 0x00511DD0  eastl::make_heap<uint32_t*>
template <typename RandomAccessIterator>
void make_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    const int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            eastl::adjust_heap<RandomAccessIterator, int, uint32_t>(first, parentPosition, heapSize, parentPosition, *(first + parentPosition));
        } while (parentPosition != 0);
    }
}

// @ 0x00511F10  eastl::sort_heap<uint32_t*>
template <typename RandomAccessIterator>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    for (; (last - first) > 1; --last) {
        const uint32_t tempBottom(*(last - 1));
        *(last - 1) = *first;
        eastl::adjust_heap<RandomAccessIterator, int, uint32_t>(first, 0, (int)(last - first - 1), 0, tempBottom);
    }
}

// @ 0x00511900  eastl::partial_sort<uint32_t*>
template <typename RandomAccessIterator>
void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last)
{
    eastl::make_heap<RandomAccessIterator>(first, middle);
    for (RandomAccessIterator i = middle; i < last; ++i) {
        if (*i < *first) {
            ScratchSlots<1>();
            const uint32_t temp(*i);
            *i = *first;
            eastl::adjust_heap<RandomAccessIterator, int, uint32_t>(first, int(0), int(middle - first), int(0), temp);
        }
    }
    eastl::sort_heap<RandomAccessIterator>(first, middle);
}

template void partial_sort<uint32_t*>(uint32_t*, uint32_t*, uint32_t*);

// ---------------------------------------------------------------- fill / copy / relocate
template <typename ForwardIterator, typename T>
inline void fill_impl(ForwardIterator first, ForwardIterator last, const T& value)
{
    for (; first != last; ++first)
        *first = value;
}
// @ 0x005117D0  eastl::fill<Elem*, Elem>
template <typename ForwardIterator, typename T>
void fill(ForwardIterator first, ForwardIterator last, const T& value)
{
    ScratchSlots<7>();
    fill_impl(first, last, value);
}
template void fill<Elem*, Elem>(Elem*, Elem*, const Elem&);

template <typename T>
inline T* uninitialized_relocate_commit_impl(T* first, T* last, T* dest, const false_type&)
{
    for (; first != last; ++first, ++dest) {
        first->~T();
        ScratchSlots<3>();
    }
    return dest;
}
// @ 0x00511880  eastl::uninitialized_relocate_commit<Elem*, Elem*>
template <typename T>
T* uninitialized_relocate_commit(T* first, T* last, T* dest)
{
    const bool bHasTrivialRelocate = has_trivial_relocate<T>::value;
    return uninitialized_relocate_commit_impl(first, last, dest, has_trivial_relocate<T>());
}
template Elem* uninitialized_relocate_commit<Elem>(Elem*, Elem*, Elem*);

// @ 0x00511BE0  eastl::uninitialized_copy_impl<generic_iterator<const Elem*>, generic_iterator<Elem*> >
template <typename T>
generic_iterator<T*> uninitialized_copy_impl(generic_iterator<const T*> first, generic_iterator<const T*> last, generic_iterator<T*> dest, const false_type&)
{
    generic_iterator<T*> currentDest(dest);
    for (; first != last; ++first, ++currentDest) {
        ::new (&*currentDest) T(*first);
        ScratchSlots<6>();
    }
    return currentDest;
}
template generic_iterator<Elem*> uninitialized_copy_impl<Elem>(generic_iterator<const Elem*>, generic_iterator<const Elem*>, generic_iterator<Elem*>, const false_type&);

// @ 0x00512050  eastl::uninitialized_copy_impl<generic_iterator<const Vec3i*>, generic_iterator<Vec3i*> >
template <typename T>
generic_iterator<T*> uninitialized_copy_impl_v(generic_iterator<const T*> first, generic_iterator<const T*> last, generic_iterator<T*> dest, const false_type&)
{
    generic_iterator<T*> currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        ::new (&*currentDest) T(*first);
    return currentDest;
}
template generic_iterator<Vec3i*> uninitialized_copy_impl_v<Vec3i>(generic_iterator<const Vec3i*>, generic_iterator<const Vec3i*>, generic_iterator<Vec3i*>, const false_type&);

// @ 0x00511C80  eastl::uninitialized_fill_n_impl<generic_iterator<Elem*>, unsigned int, Elem>
template <typename ForwardIterator, typename Count, typename T>
void uninitialized_fill_n_impl(ForwardIterator first, Count n, const T& value, const false_type&)
{
    ForwardIterator currentDest(first);
    for (; n > 0; --n, ++currentDest) {
        ::new (&*currentDest) T(value);
        ScratchSlots<6>();
    }
}
template void uninitialized_fill_n_impl<generic_iterator<Elem*>, unsigned int, Elem>(generic_iterator<Elem*>, unsigned int, const Elem&, const false_type&);

template <typename BidirectionalIterator1, typename BidirectionalIterator2>
inline BidirectionalIterator2 copy_backward_impl(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 resultEnd, const false_type&)
{
    while (last != first) {
        *--resultEnd = *--last;
        ScratchSlots<7>();
    }
    return resultEnd;
}
// @ 0x00511D00  eastl::copy_backward<Elem*, Elem*>
template <typename BidirectionalIterator1, typename BidirectionalIterator2>
BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 resultEnd)
{
    const bool bHasTrivialAssign = has_trivial_assign<Elem>::value;
    return copy_backward_impl(first, last, resultEnd, has_trivial_assign<Elem>());
}
template Elem* copy_backward<Elem*, Elem*>(Elem*, Elem*, Elem*);

// @ 0x00511D50  eastl::uninitialized_relocate_start<Elem*, Elem*>
template <typename InputIterator, typename ForwardIterator>
ForwardIterator uninitialized_relocate_start(InputIterator first, InputIterator last, ForwardIterator dest, const false_type&)
{
    for (; first != last; ++first, ++dest) {
        ScratchSlots<6>();
        ::new (&*dest) Elem(*first);
    }
    return dest;
}
template Elem* uninitialized_relocate_start<Elem*, Elem*>(Elem*, Elem*, Elem*, const false_type&);

// ---- uninitialized_copy_ptr for trivially relocatable uint32_t (memcpy path)
template <bool bHasTrivialCopy> struct copy_impl_chooser;
template <> struct copy_impl_chooser<true> {
    template <typename T>
    static T* do_copy(const T* first, const T* last, T* result)
    {
        return (T*)memcpy(result, first, (unsigned int)((uint32_t)last - (uint32_t)first)) + (last - first);
    }
};
template <typename InputIterator, typename OutputIterator>
inline OutputIterator copy_impl(InputIterator first, InputIterator last, OutputIterator result)
{
    const bool canBeMemmoved = true;
    return copy_impl_chooser<canBeMemmoved>::do_copy(first, last, result);
}
template <bool bInputIsGenericIterator, bool bOutputIsGenericIterator> struct copy_generic_iterator;
template <> struct copy_generic_iterator<true, true> {
    template <typename InputIterator, typename OutputIterator>
    static OutputIterator do_copy(InputIterator first, InputIterator last, OutputIterator result)
    {
        return OutputIterator(eastl::copy_impl(first.base(), last.base(), result.base()));
    }
};
template <typename InputIterator, typename OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
    const bool bInputIsGenericIterator = is_generic_iterator<InputIterator>::value;
    const bool bOutputIsGenericIterator = is_generic_iterator<OutputIterator>::value;
    return copy_generic_iterator<bInputIsGenericIterator, bOutputIsGenericIterator>::do_copy(first, last, result);
}
template <typename InputIterator, typename ForwardIterator>
inline ForwardIterator uninitialized_copy_impl(InputIterator first, InputIterator last, ForwardIterator dest, true_type)
{
    return eastl::copy(first, last, dest);
}
// @ 0x00511F70  eastl::uninitialized_copy_ptr<uint32_t*, uint32_t*, uint32_t*>
template <typename First, typename Last, typename Result>
Result uninitialized_copy_ptr(First first, Last last, Result result)
{
    const generic_iterator<Result> i(uninitialized_copy_impl(generic_iterator<First>(first),
                                                             generic_iterator<Last>(last),
                                                             generic_iterator<Result>(result),
                                                             has_trivial_relocate<uint32_t>()));
    return i.base();
}
template uint32_t* uninitialized_copy_ptr<uint32_t*, uint32_t*, uint32_t*>(uint32_t*, uint32_t*, uint32_t*);

} // namespace eastl

// ---------------------------------------------------------------- triangle mesh
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Vector3Diff : Vector3 {};
Vector3Diff operator-(const Vector3& a, const Vector3& b);   // 0x0041db10
Vector3 Cross(const Vector3& a, const Vector3& b);           // 0x0044e460
Vector3 Normalize(const Vector3& v);                         // 0x00436ce0

struct TriMesh {
    char pad0[8];
    Vector3* mpVertices;       // +0x08
    char pad1[0x58 - 0x0c];
    int* mpTriangles;          // +0x58 (3 vertex indices per triangle)
    Vector3 GetTriangleNormal(int i);
};

// @ 0x005121C0
Vector3 TriMesh::GetTriangleNormal(int i)
{
    Vector3* verts = mpVertices;
    int* tris = mpTriangles;
    Vector3 edge2 = verts[tris[i * 3 + 2]] - verts[tris[i * 3]];
    Vector3 edge1 = verts[tris[i * 3 + 1]] - verts[tris[i * 3]];
    return Normalize(Cross(edge1, edge2));
}

// ---------------------------------------------------------------- owner of two vectors and a map
struct Elem1C { uint32_t d[7]; };
struct Elem18 { uint32_t d[6]; };

struct VecBase1C {
    Elem1C* mpBegin; Elem1C* mpEnd; Elem1C* mpCapacity; uint32_t mAllocator[2];
    VecBase1C(const eastl::allocator&) { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~VecBase1C();                                     // 0x005141b0
};
struct Vec1C : VecBase1C {
    Vec1C(const eastl::allocator& a = eastl::allocator()) : VecBase1C(a) {}
    ~Vec1C() { for (Elem1C* p = mpBegin; p < mpEnd; ++p) ; ScratchSlots<3>(); }
    Elem1C* erase(Elem1C* first, Elem1C* last);        // 0x00514110
    void clear() { erase(mpBegin, mpEnd); }
};
struct VecBase18 {
    Elem18* mpBegin; Elem18* mpEnd; Elem18* mpCapacity; uint32_t mAllocator[2];
    VecBase18(const eastl::allocator&) { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~VecBase18();                                     // 0x004fd940
};
struct Vec18 : VecBase18 {
    Vec18(const eastl::allocator& a = eastl::allocator()) : VecBase18(a) {}
    ~Vec18() { for (Elem18* p = mpBegin; p < mpEnd; ++p) ; ScratchSlots<3>(); }
    Elem18* erase(Elem18* first, Elem18* last);        // 0x00514210
    void clear() { erase(mpBegin, mpEnd); }
};
struct Less { Less() {} };
struct Map28 {
    uint32_t d[6];
    Map28(const Less& c = Less());                    // 0x00513e20
    ~Map28();                                         // 0x00513e40
    void clear();                                     // 0x00513f20
};

struct Owner {
    Vec1C mA;     // +0x00
    Vec18 mB;     // +0x14
    Map28 mC;     // +0x28
    Owner();
    ~Owner();
    void Clear();
};

// @ 0x005122C0
Owner::Owner() : mA(), mB(), mC(Less()) {}

// @ 0x00512330
Owner::~Owner()
{
    Clear();
}

// @ 0x005123B0
void Owner::Clear()
{
    ScratchSlots<8>();
    mA.clear();
    mB.clear();
    mC.clear();
}
