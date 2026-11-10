// slice s00898e60 - basic_string<wchar_t, EASTLCoreAllocator>::swap.
//
//   0x00898e60  WString::swap(WString& other)
//
// The pre-1.11 EASTL string keeps {begin, end, capacity, allocator, flags}.
// When both strings share the allocator and the flags, swap only exchanges the
// three pointers; otherwise it falls back to the copy/assign dance:
//
//     WString temp(*this);
//     *this = other;
//     other = temp;
//
// Flags: /O2 /MD /Gy /GS- /GR- /TP /arch:SSE
#include "types.h"
#include <string.h>

// ---------------------------------------------------------------------------
// ICoreAllocator: the first four vtable slots (Alloc at +0x08, Free at +0x0c).
// ---------------------------------------------------------------------------
struct ICoreAllocator {
    virtual void  Slot0();
    virtual void  Slot4();
    virtual void* Alloc(unsigned int size, unsigned int alignment, unsigned int flags);
    virtual void  Free(void* p, unsigned int size);
};

struct WString {
    wchar_t*        mpBegin;      // +0x00
    wchar_t*        mpEnd;        // +0x04
    wchar_t*        mpCapacity;   // +0x08
    ICoreAllocator* mpAllocator;  // +0x0c
    unsigned int    mFlags;       // +0x10

    WString(const WString& x);
    ~WString();

    void RangeInitialize(const wchar_t* first, const wchar_t* last);  // 0x008885b0
    void assign(const wchar_t* first, const wchar_t* last);          // 0x008888b0
    void swap(WString& other);                                       // 0x00898e60

    WString& operator=(const WString& x)
    {
        if (this != &x)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }

    void DeallocateSelf()
    {
        int n = (int)(mpCapacity - mpBegin);
        if ((n > 1) && mpBegin)
            mpAllocator->Free(mpBegin, n * sizeof(wchar_t));
    }
};

inline WString::WString(const WString& x)
    : mpBegin(0), mpEnd(0), mpCapacity(0), mpAllocator(x.mpAllocator), mFlags(x.mFlags)
{
    RangeInitialize(x.mpBegin, x.mpEnd);
}

inline WString::~WString()
{
    DeallocateSelf();
}

template <typename T>
inline void Swap(T& a, T& b)
{
    const T tmp(a);
    a = b;
    b = tmp;
}

// @ 0x00898e60
void WString::swap(WString& other)
{
    if (mpAllocator == other.mpAllocator && mFlags == other.mFlags) {
        Swap(mpBegin, other.mpBegin);
        Swap(mpEnd, other.mpEnd);
        Swap(mpCapacity, other.mpCapacity);
    } else {
        WString temp(*this);
        *this = other;
        other = temp;
    }
}
