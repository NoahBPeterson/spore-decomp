// Slice s004cf770: eastl vector<T>::DoInsertValues / DoAssignFromIterator instances, a hashtable bucket
// free and a fixed-pool allocate helper, from the creature-editor skin code.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"
#pragma pack(push, 4)

template <int N> inline void ScratchSlots() { uint32_t s[N]; }
inline void* operator new(unsigned int, void* p) { return p; }

void EASTLFree(void* p);                                                         // 0x00F47380 operator delete[]
void* EASTLAlloc(void* allocator, uint32_t n, uint32_t align, uint32_t offset);  // 0x0042DEE0
extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned int n);

namespace eastl {

struct false_type {};
struct is_integral_false : public false_type { is_integral_false() {} };
struct random_access_iterator_tag { random_access_iterator_tag() {} };
template <class T> struct has_trivial_relocate : public false_type {};

struct Vec4 {                                   // movss copy ctor / assignment (SSE module)
    float x, y, z, w;
    Vec4(const Vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    Vec4& operator=(const Vec4& v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
};

struct X87Vec4 {                                // out-of-line copy ctor (x87), 0x00501290
    float x, y, z, w;
    X87Vec4(const X87Vec4& v);                  // 0x00501290
};

struct Rec14 {                                  // 0x14: key + X87Vec4
    uint32_t mKey;
    X87Vec4 mValue;
    Rec14(const Rec14& x) : mKey(x.mKey), mValue(x.mValue) {}
};

struct Word32 { uint32_t mValue; };

struct EASTLAllocator { const char* mpName; EASTLAllocator() {} };

template <class T> struct generic_iterator {
    T mIterator;
    explicit generic_iterator(const T& x) : mIterator(x) {}
    const T& base() const { return mIterator; }
};

template <class T> struct value_of;
template <class T> struct value_of<T*> { typedef T type; };
template <class T> struct value_of<const T*> { typedef T type; };

// out-of-line template instances (defined in slice s004d06e0 / unnamed neighbours)
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

template <class T> T* uninitialized_move(T* first, T* last, T* dest);        // out of line
template <class T> T* uninitialized_move_start(T* first, T* last, T* dest);  // out of line
template <class T> T* copy_backward(T* first, T* last, T* resultEnd);         // out of line (Vec4)
template <class T> T* uninitialized_copy_ool2(T* first, T* last, T* dest);    // out of line (0x00477200 for Word32)
template <class T> T* uninitialized_copy_ool(T* first, T* last, T* dest);     // out of line (0x004D0A80 for Rec14)

template <class T> struct move_impl;

template <class T>
inline T* uninitialized_move_commit5(T* first, T* last, T* dest)
{
    const bool bHasTrivialMove = false;
    uint32_t unusedFrame[5];
    return move_impl<T>::do_move_commit(first, last, dest);
}

template <class T>
inline T* uninitialized_move_inl(T* first, T* last, T* dest)
{
    T* result = uninitialized_move_start(first, last, dest);
    uninitialized_move_commit5(first, last, dest);
    return result;
}

template <class T> struct move_impl {
    static T* do_move_start(T* first, T* last, T* dest);        // out of line
    static T* do_move_commit(T* first, T* last, T* dest)
    {
        for (; first != last; ++first, ++dest)
            first->~T();
        return dest;
    }
};

template <class T>
inline T* uninitialized_move_start_w(T* first, T* last, T* dest)
{
    const bool bHasTrivialMove = false;
    return move_impl<T>::do_move_start(first, last, dest);
}

template <class T>
inline T* uninitialized_move_commit_w(T* first, T* last, T* dest)
{
    const bool bHasTrivialMove = false;
    uint32_t unusedFrame;
    return move_impl<T>::do_move_commit(first, last, dest);
}

template <class T>
inline T* uninitialized_move_inl0(T* first, T* last, T* dest)
{
    T* result = uninitialized_move_start_w(first, last, dest);
    uninitialized_move_commit_w(first, last, dest);
    return result;
}

template <class Bi1, class Bi2>
inline Bi2 copy_backward_impl(Bi1 first, Bi1 last, Bi2 resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}

template <class T>
inline T* copy_backward_inl(T* first, T* last, T* resultEnd)
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
    T* DoRealloc(uint32_t n, const T* first, const T* last);                 // 0x0042E5B0
    template <class II> void DoAssignFromIterator(II first, II last, random_access_iterator_tag);
};

Word32* uninitialized_copy_ext(const Word32* first, const Word32* last, Word32* result);   // 0x00511F70

template <class T> __forceinline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        ;
}

__forceinline Word32* copy(const Word32* first, const Word32* last, Word32* result)
{
    const bool bIsMove = false;
    const bool bCanMemmove = false;
    const bool bIsPod = true;
    return (Word32*)memmove(result, first, (unsigned int)((uint32_t)last - (uint32_t)first)) + (last - first);
}

// @ 0x004CF770
template <> void vector<Rec14>::DoInsertValues(Rec14* position, uint32_t n, const Rec14& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const Rec14 temp(value);
            ScratchSlots<1>();
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            Rec14* const pEnd = mpEnd;
            if (n < nExtra) {
                uninitialized_copy_ptr(mpEnd - n, mpEnd, mpEnd);
                mpEnd += n;
                copy_backward_inl(position, pEnd - n, pEnd);
                fill(position, position + n, temp);
            } else {
                uninitialized_fill_n_ptr(mpEnd, n - nExtra, temp);
                mpEnd += n - nExtra;
                uninitialized_copy_ool(position, pEnd, mpEnd);
                ScratchSlots<12>();
                mpEnd += nExtra;
                fill(position, pEnd, temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = GetNewCapacity(nPrevSize);
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        Rec14* const pNewData = DoAllocate(nNewSize);
        Rec14* pNewEnd = uninitialized_move(mpBegin, position, pNewData);
        ScratchSlots<8>();
        uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd = uninitialized_move_inl(position, mpEnd, pNewEnd + n);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

struct fixed_word_vector {                       // vector<Word32, fixed_vector_allocator>
    Word32* mpBegin;
    Word32* mpEnd;
    Word32* mpCapacity;
    EASTLAllocator mAllocator;
    void* mpPoolBegin;

    inline uint32_t GetNewCapacity(uint32_t currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
    inline Word32* DoAllocate(uint32_t n) { return n ? (Word32*)EASTLAlloc(&mAllocator, n * sizeof(Word32), 2, 0) : 0; }
    inline void DoFree(Word32* p, uint32_t n) { if (p) deallocate(p, n * sizeof(Word32)); }
    inline void deallocate(void* p, uint32_t) { if (p != mpPoolBegin) FreeBlock(p); }
    static void FreeBlock(void* p) { void* pBlock = p; EASTLFree(pBlock); }
    void DoInsertValues(Word32* position, uint32_t n, const Word32& value);
};

// @ 0x004D0080
void fixed_word_vector::DoInsertValues(Word32* position, uint32_t n, const Word32& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const Word32 temp(value);
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            Word32* const pEnd = mpEnd;
            if (n < nExtra) {
                uninitialized_copy_ptr(mpEnd - n, mpEnd, mpEnd);
                mpEnd += n;
                copy_backward_inl(position, pEnd - n, pEnd);
                fill(position, position + n, temp);
            } else {
                uninitialized_fill_n_ptr(mpEnd, n - nExtra, temp);
                mpEnd += n - nExtra;
                uninitialized_copy_ool(position, pEnd, mpEnd);
                ScratchSlots<11>();
                mpEnd += nExtra;
                fill(position, pEnd, temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = GetNewCapacity(nPrevSize);
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        Word32* const pNewData = DoAllocate(nNewSize);
        Word32* pNewEnd = uninitialized_copy_ool2(mpBegin, position, pNewData);
        ScratchSlots<8>();
        uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd = uninitialized_copy_ool2(position, mpEnd, pNewEnd + n);
        ScratchSlots<8>();
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// definitions after their first use: cl keeps them out of line
template <class In, class Out>
generic_iterator<Out> uninitialized_copy_impl(generic_iterator<In> first, generic_iterator<In> last,
                                              generic_iterator<Out> dest, false_type)
{
    typedef typename value_of<Out>::type value_type;
    generic_iterator<Out> currentDest(dest);
    for (; first.mIterator != last.mIterator; ++first.mIterator, ++currentDest.mIterator)
        ::new (currentDest.mIterator) value_type(*first.mIterator);
    return currentDest;
}
template <class It, class T>
void uninitialized_fill_n_impl(generic_iterator<It> first, uint32_t n, const T& value, false_type)
{
    generic_iterator<It> currentDest(first);
    for (; n > 0; --n, ++currentDest.mIterator)
        ::new (currentDest.mIterator) T(value);
}
template <class T> T* uninitialized_move(T* first, T* last, T* dest)
{
    T* result = uninitialized_move_start(first, last, dest);
    uninitialized_move_commit5(first, last, dest);
    return result;
}
template <class T> T* uninitialized_move_start(T* first, T* last, T* dest)
{
    const bool bHasTrivialMove = false;
    for (; first != last; ++first, ++dest)
        ::new (dest) T(*first);
    return dest;
}
template <class T> T* uninitialized_copy_ool(T* first, T* last, T* dest)
{
    for (; first != last; ++first, ++dest)
        ::new (dest) T(*first);
    return dest;
}
template Rec14* uninitialized_copy_ool(Rec14*, Rec14*, Rec14*);
template Rec14* uninitialized_move(Rec14*, Rec14*, Rec14*);
template Rec14* uninitialized_move_start(Rec14*, Rec14*, Rec14*);
template generic_iterator<Rec14*> uninitialized_copy_impl(generic_iterator<const Rec14*>, generic_iterator<const Rec14*>, generic_iterator<Rec14*>, false_type);
template void uninitialized_fill_n_impl(generic_iterator<Rec14*>, uint32_t, const Rec14&, false_type);

// @ 0x004CFC00
template <> void vector<Vec4>::DoInsertValues(Vec4* position, uint32_t n, const Vec4& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const Vec4 temp(value);
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            Vec4* const pEnd = mpEnd;
            if (n < nExtra) {
                uninitialized_copy_ptr(mpEnd - n, mpEnd, mpEnd);
                mpEnd += n;
                copy_backward(position, pEnd - n, pEnd);
                ScratchSlots<3>();
                fill(position, position + n, temp);
            } else {
                uninitialized_fill_n_ptr(mpEnd, n - nExtra, temp);
                mpEnd += n - nExtra;
                uninitialized_copy_ool(position, pEnd, mpEnd);
                ScratchSlots<12>();
                mpEnd += nExtra;
                fill(position, pEnd, temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = GetNewCapacity(nPrevSize);
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        Vec4* const pNewData = DoAllocate(nNewSize);
        Vec4* pNewEnd = uninitialized_move(mpBegin, position, pNewData);
        ScratchSlots<8>();
        uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd = uninitialized_move_inl0(position, mpEnd, pNewEnd + n);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x004D04F0
template <> template <>
void vector<Word32>::DoAssignFromIterator<const Word32*>(const Word32* first, const Word32* last, random_access_iterator_tag)
{
    const uint32_t n = (uint32_t)(last - first);
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        Word32* const pNewData = DoRealloc(n, first, last);
        ScratchSlots<14>();
        eastl::destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = mpBegin + n;
        mpCapacity = mpEnd;
    } else if (n <= (uint32_t)(mpEnd - mpBegin)) {
        Word32* const position = eastl::copy(first, last, mpBegin);
        eastl::destruct(position, mpEnd);
        mpEnd = position;
    } else {
        const Word32* position = first + (mpEnd - mpBegin);
        eastl::copy(first, position, mpBegin);
        mpEnd = eastl::uninitialized_copy_ext(position, last, mpEnd);
        ScratchSlots<17>();
    }
}

// ---------------------------------------------------------------------------
// hashtable (fixed node pool): DoFreeNodes, and the fixed-pool allocate_memory helper
// ---------------------------------------------------------------------------
struct HashNode {
    uint32_t mValue[3];
    HashNode* mpNext;                                // 0x0C
};

struct FixedPool {
    void* mpHead;
    void* mpNext;
    void* mpPoolBegin;
    void* mpCapacity;
    uint32_t mnNodeSize;
    void* allocate();                                // 0x004CE850
};

struct FixedHashtableAllocator {
    FixedPool mPool;
    void* mpBucketBuffer;                            // 0x14
    inline void* allocate(uint32_t n, int flags = 0)
    {
        uint32_t unused[3];
        if (n == sizeof(HashNode))
            return mPool.allocate();
        return mpBucketBuffer;
    }
};

class hashtable {
public:
    uint32_t mFunctors;                              // 0x00
    HashNode** mpBucketArray;                        // 0x04
    uint32_t mnBucketCount;                          // 0x08
    uint32_t mnElementCount;                         // 0x0C
    uint32_t mRehashPolicy[3];                       // 0x10
    FixedHashtableAllocator mAllocator;              // 0x1C
    void DoFreeNode(HashNode* pNode);                // 0x004D0C20
    void DoFreeNodes(HashNode** pNodeArray, uint32_t n);
};

// @ 0x004D0430
void hashtable::DoFreeNodes(HashNode** pNodeArray, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        HashNode* pNode = pNodeArray[i];
        while (pNode) {
            HashNode* const pTempNode = pNode;
            pNode = pNode->mpNext;
            DoFreeNode(pTempNode);
            ScratchSlots<3>();
        }
        pNodeArray[i] = 0;
    }
}

// @ 0x004D04A0
void* allocate_memory(FixedHashtableAllocator& a, uint32_t n, uint32_t alignment, uint32_t alignmentOffset)
{
    if (alignment <= 8)
        return a.allocate(n);
    return a.allocate(n);
}

} // namespace eastl

#pragma pack(pop)
