// s00513930: fast acos, mesh-topology helpers, and EASTL vector/deque instantiations.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
// ScratchSlots<N>() reproduces unused stack slots left by inlined helpers.
#include "types.h"

extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);           // 0x011e0744 (static thunk)
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}
void operator delete[](void* p);                                            // 0x00f47380
void* EASTL_Allocate(uint32_t* allocator, unsigned int n, unsigned int alignment, unsigned int offset);  // 0x0042dee0

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}

// ---------------------------------------------------------------- math
extern const float kPI;        // 0x015dd4bc
extern const float kHalfPI;    // 0x015dd6e0
// the volatile store reproduces the original's forced float rounding of the root
inline float Sqrt(float x) { volatile float r = (float)sqrt(x); return r; }

// @ 0x00513930  polynomial acos approximation
float FastAcos(float x)
{
    if (x >= 1.0f)
        return 0.0f;
    if (-1.0f >= x)
        return kPI;
    if (x >= 0.0f) {
        float s = Sqrt(1.0f - x);
        return (((x * -0.02164095f + 0.07798048f) * x + -0.21330099f) * x + kHalfPI) * s;
    } else {
        float s = Sqrt(1.0f + x);
        return kPI - (kHalfPI - (-0.21330099f - (0.07798048f - x * -0.02164095f) * x) * x) * s;
    }
}

struct Vector2 {
    float x, y;
    Vector2(float x_, float y_) : x(x_), y(y_) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
    float Dot(const Vector2& v) const { return x * v.x + y * v.y; }
};

// @ 0x00513BA0  edge test with a top-left style bias
bool EdgeTest(const Vector2& a, const Vector2& b)
{
    // local names chosen for /Od slot order
    Vector2 t19(b[1] - a[1], a[0] - b[0]);   // edge normal
    float num = a.Dot(t19);
    if (t19[0] < 0.0f)
        num -= t19[0];
    if (t19[1] < 0.0f)
        num -= t19[1];
    return num > 0.0f;
}

// ---------------------------------------------------------------- mesh topology
template <typename T> struct SimpleVector {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator[2];
    T* data() const { return mpBegin; }
};

struct MeshData {
    uint32_t pad0[2];
    SimpleVector<float> mPositions;    // +0x08
    SimpleVector<float> mNormals;      // +0x1c
    SimpleVector<float> mUVs;          // +0x30
    SimpleVector<float> mColors;       // +0x44
    SimpleVector<int> mPositionIndices; // +0x58
    SimpleVector<int> mNormalIndices;  // +0x6c
    SimpleVector<int> mUVIndices;      // +0x80
    SimpleVector<int> mOpposite;       // +0x94
};

static const signed char kNextInTri[3] = { 1, 1, -2 };
static const signed char kPrevInTri[3] = { 2, -1, -1 };

struct EdgeQuery {
    uint32_t edge;
    bool isSeamless;
    EdgeQuery(uint32_t e, bool b) : edge(e), isSeamless(b) {}
};

struct MeshView {
    float* mpPositions;     // +0x00
    float* mpNormals;       // +0x04
    float* mpUVs;           // +0x08
    int* mpPositionIndices; // +0x0c
    int* mpNormalIndices;   // +0x10
    int* mpUVIndices;       // +0x14
    uint32_t* mpOpposite;   // +0x18
    MeshView(const MeshData& m);
    EdgeQuery GetOppositePrev(uint32_t e);
};

// @ 0x005139F0
MeshView::MeshView(const MeshData& m)
{
    mpPositions = m.mPositions.data();
    mpNormals = m.mNormals.data();
    mpUVs = m.mUVs.data();
    mpPositionIndices = m.mPositionIndices.data();
    mpNormalIndices = m.mNormalIndices.data();
    mpUVIndices = m.mUVIndices.data();
    mpOpposite = (uint32_t*)m.mOpposite.data();
}

// @ 0x00513A90
EdgeQuery MeshView::GetOppositePrev(uint32_t e)
{
    // local names chosen for /Od slot order:
    // x = uv indices, first = normal indices, from = twin edge, m = twin's corner,
    // v34 = twin's next, t23 = twin's prev, ptr = e's next, w = result flag
    int* x = mpUVIndices;
    int* first = mpNormalIndices;
    uint32_t from = mpOpposite[e];
    uint32_t m = from - (from / 3) * 3;
    uint32_t v34 = kNextInTri[m] + from;
    uint32_t t23 = kPrevInTri[m] + from;
    uint32_t ptr = kNextInTri[e - (e / 3) * 3] + e;
    bool w = x[ptr] == x[from] && x[v34] == x[e] &&
             first[v34] == first[e] && first[ptr] == first[from];
    return EdgeQuery(t23, w);
}

// ---------------------------------------------------------------- EASTL
namespace eastl {

template <typename T, T v> struct integral_constant { static const T value = v; };
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

struct allocator { allocator() {} };

// ---- copy / copy_backward for trivially copyable pointers (memcpy / memmove paths)
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
template <> struct copy_generic_iterator<false, false> {
    template <typename InputIterator, typename OutputIterator>
    static OutputIterator do_copy(InputIterator first, InputIterator last, OutputIterator result)
    {
        return eastl::copy_impl(first, last, result);
    }
};
template <typename InputIterator, typename OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
    const bool bInputIsGenericIterator = false;
    const bool bOutputIsGenericIterator = false;
    return copy_generic_iterator<bInputIsGenericIterator, bOutputIsGenericIterator>::do_copy(first, last, result);
}

template <typename T>
inline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}

template <bool bHasTrivialCopy> struct copy_backward_impl_chooser;
template <> struct copy_backward_impl_chooser<true> {
    template <typename T>
    static T* do_copy(const T* first, const T* last, T* resultEnd)
    {
        return (T*)memmove(resultEnd - (last - first), first, (unsigned int)((uint32_t)last - (uint32_t)first));
    }
};
template <typename BidirectionalIterator1, typename BidirectionalIterator2>
inline BidirectionalIterator2 copy_backward_impl(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 resultEnd)
{
    const bool canBeMemmoved = true;
    return copy_backward_impl_chooser<canBeMemmoved>::do_copy(first, last, resultEnd);
}
template <typename BidirectionalIterator1, typename BidirectionalIterator2>
inline BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 resultEnd)
{
    const bool bInputIsGenericIterator = false;
    const bool bOutputIsGenericIterator = false;
    return copy_backward_impl(first, last, resultEnd);
}

template <typename T>
inline T* uninitialized_copy_ptr(T* first, T* last, T* result)
{
    const bool bCanMemcpy = true;
    T* const pEnd = copy_impl_chooser<bCanMemcpy>::do_copy(first, last, result);
    const bool bIsPtr = true;
    return pEnd;
}

struct Elem1C { uint32_t d[7]; };
struct Elem18 { uint32_t d[6]; Elem18() {} };
struct Elem0C { uint32_t d[3]; Elem0C() {} };

template <typename T>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];   // +0x0c

    T* erase(T* first, T* last);
    void push_back();
    void push_back(const T& value);
    void resize(unsigned int n, const T& value);
    void DoInsertValue(T* position, const T& value);
    void DoInsertValues(T* position, unsigned int n, const T& value);
    void insert(T* position, unsigned int n, const T& value) { DoInsertValues(position, n, value); }
    unsigned int GetNewCapacity(unsigned int currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
    T* DoAllocate(unsigned int n) { return n ? (T*)EASTL_Allocate(mAllocator, n * sizeof(T), 4, 0) : 0; }
    void Free(void* p) { void* q = p; operator delete[](q); }
    void DoFree(T* p, unsigned int n) { if (p && ((uint32_t*)p)[-1] != 0) Free(p); }
};

// @ 0x005142B0  eastl::vector<Elem18>::DoInsertValue(position, value)
template <typename T>
void vector<T>::DoInsertValue(T* position, const T& value)
{
    if (mpEnd != mpCapacity) {
        const T* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) T(*(mpEnd - 1));
        eastl::copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const unsigned int nPrevSize = (unsigned int)(mpEnd - mpBegin);
        const unsigned int nNewSize = GetNewCapacity(nPrevSize);
        T* const pNewData = DoAllocate(nNewSize);
        T* pNewEnd = eastl::uninitialized_copy_ptr(mpBegin, position, pNewData);
        ::new (pNewEnd) T(value);
        pNewEnd = eastl::uninitialized_copy_ptr(position, mpEnd, ++pNewEnd);
        DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
template void vector<Elem18>::DoInsertValue(Elem18*, const Elem18&);

// @ 0x00514110  eastl::vector<Elem1C>::erase(first, last)
// @ 0x00514210  eastl::vector<Elem18>::erase(first, last)
// @ 0x00514750  eastl::vector<uint8_t>::erase(first, last)
template <typename T>
T* vector<T>::erase(T* first, T* last)
{
    T* const position = eastl::copy(last, mpEnd, first);
    eastl::destruct(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}
template Elem1C* vector<Elem1C>::erase(Elem1C*, Elem1C*);
template Elem18* vector<Elem18>::erase(Elem18*, Elem18*);
template uint8_t* vector<uint8_t>::erase(uint8_t*, uint8_t*);

// @ 0x00513D20  eastl::vector<Elem18>::push_back()
// @ 0x005140A0  eastl::vector<Elem0C>::push_back()
template <typename T>
void vector<T>::push_back()
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) T();
    else
        DoInsertValue(mpEnd, T());
}
template void vector<Elem18>::push_back();
template void vector<Elem0C>::push_back();

// @ 0x00513D90  eastl::vector<Elem18>::push_back(const value_type&)
template <typename T>
void vector<T>::push_back(const T& value)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) T(value);
    else
        DoInsertValue(mpEnd, value);
}
template void vector<Elem18>::push_back(const Elem18&);

// @ 0x00514030  eastl::vector<uint8_t>::resize(n, value)
template <typename T>
void vector<T>::resize(unsigned int n, const T& value)
{
    if (n > (unsigned int)(mpEnd - mpBegin))
        insert(mpEnd, n - (mpEnd - mpBegin), value);
    else
        erase(mpBegin + n, mpEnd);
    ScratchSlots<4>();
}
template void vector<uint8_t>::resize(unsigned int, const uint8_t&);

// ---- deque<Elem48, allocator, 4>
struct Vector3 { float x, y, z; Vector3() {} Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {} };
struct Vector2f { float x, y; Vector2f() {} Vector2f(const Vector2f& v) : x(v.x), y(v.y) {} };
struct Tri3 { uint32_t a, b, c; };
struct Bytes3 { uint8_t a, b, c; };
struct Elem48 {
    uint32_t mId;       // +0x00
    Vector3 mA;         // +0x04
    Vector3 mB;         // +0x10
    Vector3 mC;         // +0x1c
    Vector2f mUV;       // +0x28
    Tri3 mTri;          // +0x30
    uint32_t m3c;       // +0x3c
    uint32_t m40;       // +0x40
    Bytes3 m44;         // +0x44
    uint8_t m47;        // +0x47
    Elem48() {}
    Elem48(const Elem48& x);
};
// @ 0x005147D0  Elem48 copy constructor (memberwise)
Elem48::Elem48(const Elem48& x)
    : mId(x.mId), mA(x.mA), mB(x.mB), mC(x.mC), mUV(x.mUV), mTri(x.mTri), m3c(x.m3c), m40(x.m40), m44(x.m44), m47(x.m47)
{
}

enum { kSubarraySize = 4 };

template <typename T>
struct DequeIterator {
    T* mpCurrent;
    T* mpBegin;
    T* mpEnd;
    T** mpCurrentArrayPtr;
    struct Increment {};
    struct Decrement {};
    DequeIterator(const DequeIterator& x);                  // 0x00420050
    DequeIterator(const DequeIterator& x, Decrement);       // 0x00514690
    DequeIterator& operator++();
    T& operator*() const;                                   // 0x005658b0
    void SetSubarray(T** pCurrentArrayPtr);                 // 0x00515170
};
template <typename T>
inline bool operator!=(const DequeIterator<T>& a, const DequeIterator<T>& b) { return a.mpCurrent != b.mpCurrent; }

// @ 0x005146E0  eastl::DequeIterator<Elem48>::operator++
template <typename T>
DequeIterator<T>& DequeIterator<T>::operator++()
{
    if (++mpCurrent == mpEnd) {
        mpBegin = *++mpCurrentArrayPtr;
        mpEnd = mpBegin + kSubarraySize;
        mpCurrent = mpBegin;
    }
    return *this;
}
template DequeIterator<Elem48>& DequeIterator<Elem48>::operator++();

template <typename T>
struct DequeBase {
    T** mpPtrArray;
    int mnPtrArraySize;
    DequeIterator<T> mItBegin;   // +0x08
    DequeIterator<T> mItEnd;     // +0x18
    DequeBase(unsigned int n, const allocator& a);          // 0x00514640
    ~DequeBase();                                           // 0x00501ef0
    T* DoAllocateSubarray();                                // 0x00514e10
    void DoFreeSubarray(T* p);                              // 0x00569260
    void DoReallocPtrArray(unsigned int nAdditionalCapacity, int side);  // 0x00514e40
};

template <typename T>
struct deque : DequeBase<T> {
    deque(const allocator& a);
    ~deque();
    T& back();
    void push_back();
    void clear();
    void DoPushBack(const T& value);
};

// (not in this slice) 0x00513E20  eastl::deque<Elem48>::deque(const allocator&)
template <typename T>
deque<T>::deque(const allocator& a) : DequeBase<T>(0, a) {}

// @ 0x00513E40  eastl::deque<Elem48>::~deque
template <typename T>
deque<T>::~deque()
{
    for (DequeIterator<T> itCurrent(this->mItBegin); itCurrent != this->mItEnd; ++itCurrent)
        itCurrent.mpCurrent->~T();
}

// @ 0x00513E90  eastl::deque<Elem48>::back
template <typename T>
T& deque<T>::back()
{
    return *DequeIterator<T>(this->mItEnd, typename DequeIterator<T>::Decrement());
}

// @ 0x00513EC0  eastl::deque<Elem48>::push_back()
template <typename T>
void deque<T>::push_back()
{
    if ((this->mItEnd.mpCurrent + 1) != this->mItEnd.mpEnd)
        ::new (this->mItEnd.mpCurrent++) T();
    else
        DoPushBack(T());
}

// @ 0x00513F20  eastl::deque<Elem48>::clear
template <typename T>
void deque<T>::clear()
{
    if (this->mItBegin.mpCurrentArrayPtr != this->mItEnd.mpCurrentArrayPtr) {
        for (T* p1 = this->mItBegin.mpCurrent; p1 < this->mItBegin.mpEnd; ++p1)
            p1->~T();
        for (T* p2 = this->mItEnd.mpBegin; p2 < this->mItEnd.mpCurrent; ++p2)
            p2->~T();
        this->DoFreeSubarray(this->mItEnd.mpBegin);
    } else {
        for (T* p = this->mItBegin.mpCurrent; p < this->mItEnd.mpCurrent; ++p)
            p->~T();
    }
    for (T** pPtrArray = this->mItBegin.mpCurrentArrayPtr + 1; pPtrArray < this->mItEnd.mpCurrentArrayPtr; ++pPtrArray) {
        for (T *p = *pPtrArray, *pEnd = *pPtrArray + kSubarraySize; p < pEnd; ++p)
            p->~T();
        this->DoFreeSubarray(*pPtrArray);
    }
    this->mItEnd = this->mItBegin;
}

// @ 0x00514570  eastl::deque<Elem48>::DoPushBack
template <typename T>
void deque<T>::DoPushBack(const T& value)
{
    ScratchSlots<15>();
    T valueSaved(value);
    if (((this->mItEnd.mpCurrentArrayPtr - this->mpPtrArray) + 1) >= this->mnPtrArraySize)
        this->DoReallocPtrArray(1, 1);
    this->mItEnd.mpCurrentArrayPtr[1] = this->DoAllocateSubarray();
    ::new (this->mItEnd.mpCurrent) T(valueSaved);
    this->mItEnd.SetSubarray(this->mItEnd.mpCurrentArrayPtr + 1);
    this->mItEnd.mpCurrent = this->mItEnd.mpBegin;
}

template struct deque<Elem48>;

} // namespace eastl
