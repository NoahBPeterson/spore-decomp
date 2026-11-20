// @ 0x00672c30
#include "game/types.h"
#include <intrin.h>

inline void* operator new(unsigned int, void* storage) { return storage; }

namespace eastl {

// fixed_string<wchar_t, 32, true> as the detokenizer instantiates it:
// three pointers followed by the inline allocator (header + 32-character buffer).
template <class T, int N, bool Overflow> class fixed_string {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    struct Allocator {
        int mPadding;
        T* mpBegin;
        T mBuffer[N];
    } mAllocator;

    void assign(const T* first, const T* last); // 0x00672750

    __forceinline fixed_string(const fixed_string& source)
    {
        T* buffer = mAllocator.mBuffer;
        mAllocator.mpBegin = buffer;
        _ReadWriteBarrier();
        mpCapacity = buffer + N;
        mpEnd = buffer;
        mpBegin = buffer;
        *buffer = 0;
        assign(source.mpBegin, source.mpEnd);
    }
};

template <class T> struct iterator_traits;
template <class T> struct iterator_traits<T*> {
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
};

// EASTL's wrapper that gives a raw pointer a value_type.
template <class Iterator, class = void> class generic_iterator {
public:
    Iterator mIterator;

    generic_iterator(const Iterator& x) : mIterator(x) {}
    generic_iterator(const generic_iterator& x) : mIterator(x.mIterator) {}

    Iterator base() const { return mIterator; }
    typename iterator_traits<Iterator>::reference operator*() const { return *mIterator; }
    generic_iterator& operator++() { ++mIterator; return *this; }
    bool operator==(const generic_iterator& x) const { return mIterator == x.mIterator; }
    bool operator!=(const generic_iterator& x) const { return mIterator != x.mIterator; }
};

template <class I, class V> struct iterator_traits<generic_iterator<I, V> > {
    typedef typename iterator_traits<I>::value_type value_type;
};

}

typedef eastl::fixed_string<wchar_t, 32, true> DetokenizerString;
typedef eastl::generic_iterator<DetokenizerString*> DetokenizerStringIterator;

// eastl::uninitialized_copy_impl's non-trivial path (EASTL memory.h): copy-construct
// each value into the uninitialized range and report the end of the destination range.
// 0x00672c30 is the out-of-line instantiation of this loop.
// @ 0x00672c30
DetokenizerStringIterator CopyUninitializedDetokenizerStrings(
    DetokenizerStringIterator first, DetokenizerStringIterator last,
    DetokenizerStringIterator destination)
{
    typedef eastl::iterator_traits<DetokenizerStringIterator>::value_type value_type;
    DetokenizerStringIterator currentDest(destination);
    for (; first != last; ++first, ++currentDest)
        ::new ((void*)&*currentDest) value_type(*first);
    return currentDest;
}
