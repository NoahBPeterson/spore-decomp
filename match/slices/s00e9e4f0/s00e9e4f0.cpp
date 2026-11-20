// Single-element insertion for a vector of 12-byte elements whose three
// pointers (begin / finish / end-of-storage) sit at +0 / +4 / +8.
//
// Inserting at `pos` moves the tail right by one element; when the vector is
// full a buffer of twice the current size is allocated and both halves are
// copied in around the new element.

#include <new>

struct Element12 {
    int a, b, c;
};

// eastl::copy_backward, inlined. Written `last != first` so the loop test
// compiles as cmp last, first, the way the original does.
template <typename T>
__forceinline T* copy_backward(T* first, T* last, T* result)
{
    while (last != first)
        *--result = *--last;
    return result;
}

struct Vector12 {
    Element12* mBegin;
    Element12* mFinish;
    Element12* mEnd;

    void insert(Element12* pos, const Element12& value);
};

Element12* __cdecl CopyInto(Element12* first, Element12* last, Element12* dest);
// Retail pushes the arguments in the order (size, "vector.cpp", 0, 0,
// "Vector12", 209), i.e. the source file is the second argument and the type
// name the second-to-last.
void* __cdecl AllocateDebug(unsigned size, const char* file, int a, int b,
                            const char* name, int line);
void __cdecl FreeDebug(void* p);

// eastl::vector::DoAllocate for a 12-byte element, inlined.
__forceinline Element12* DoAllocate(int n)
{
    return n ? (Element12*)AllocateDebug(n * sizeof(Element12), "vector.cpp", 0,
                                         0, "Vector12", 209)
             : 0;
}

// @ 0x00e9e4f0
void Vector12::insert(Element12* pos, const Element12& value)
{
    if (mFinish != mEnd) {
        // If the value already lives at or after the insertion point, the shift
        // below carries it one element further along.
        Element12* src = (Element12*)&value;
        if (!(src < pos) && src < mFinish)
            src += 1;

        if (mFinish)
            *mFinish = mFinish[-1];

        copy_backward(pos, mFinish - 1, mFinish);

        *pos = *src;
        mFinish += 1;
        return;
    }

    // No spare element: reallocate, copying both halves around the new value.
    // The two source pointers are read once into locals, so they stay put in
    // the old buffer while the finished vector is rewritten.
    const int count = (int)(mFinish - mBegin);
    const int newcap = count ? (2 * count) : 1;
    Element12* const newvec = DoAllocate(newcap);

    Element12* const oldbegin = mBegin;
    Element12* newend = CopyInto(oldbegin, pos, newvec);
    if (newend)
        ::new (newend) Element12(value);

    Element12* const oldfinish = mFinish;
    newend = CopyInto(pos, oldfinish, ++newend);

    if (mBegin != 0)
        FreeDebug(mBegin);

    mBegin = newvec;
    mFinish = newend;
    mEnd = newvec + newcap;
}
