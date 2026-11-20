// @ 0x00672f00
// eastl::uninitialized_copy_impl<0, random_access_iterator_tag>::do_copy<cAction*, cAction*>:
// copy-constructs [first, last) into the uninitialized storage at *result and walks the
// caller's output iterator (the retail build takes the two source iterators by value as
// one-member iterator objects and hands the result back through the caller's pointer).
#include "game/types.h"
#include <intrin.h>

inline void* operator new(unsigned int, void* storage) { return storage; }

namespace eastl {
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
}

namespace {
class cBuildXHTMLDetokenizer {
public:
    class cVar {
    public:
        struct cAction {
            eastl::fixed_string<wchar_t, 32, true> mString;
            int mX;

            __forceinline cAction(const cAction& source)
                : mString(source.mString), mX(source.mX) {}
        };
    };
};
}

typedef cBuildXHTMLDetokenizer::cVar::cAction DetokenizerAction;

// The source range iterator: a single pointer, passed by value (its address is what the
// retail code keeps in the argument slots and reloads across the assign call).
struct DetokenizerActionIterator {
    DetokenizerAction* mIterator;

    DetokenizerActionIterator(DetokenizerAction* position) : mIterator(position) {}

    bool operator!=(const DetokenizerActionIterator& other) const
    {
        return mIterator != other.mIterator;
    }

    DetokenizerActionIterator& operator++()
    {
        ++mIterator;
        return *this;
    }
};

// Copy-construct the source range into the uninitialized destination range.
// @ 0x00672f00
DetokenizerAction** CopyUninitializedDetokenizerActions(
    DetokenizerAction** result, DetokenizerActionIterator first,
    DetokenizerActionIterator last, DetokenizerAction* destination)
{
    *result = destination;
    for (; first != last; ++first, ++*result)
        new (static_cast<void*>(*result)) DetokenizerAction(*first.mIterator);
    return result;
}
