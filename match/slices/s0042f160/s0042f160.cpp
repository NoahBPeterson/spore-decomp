// Template-instantiation module 0x0042F160..0x0042F9C8: EASTL algorithms (merge, copy,
// copy_backward over deque iterators / intrusive_ptr arrays), vector and string helpers.
// Built unoptimized: /Od /Ob1 /MD /Gy /TP /arch:SSE
#include <string.h>
#include "types.h"

// ---------------------------------------------------------------------------
// Common helpers
// ---------------------------------------------------------------------------
struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
};

struct Alloc {
    uint32_t pad;
    const char* mpName;
    Alloc& operator=(const Alloc& x)
    {
        mpName = x.mpName;
        return *this;
    }
};

struct MergeElem {
    uint32_t key, a, b;
};

inline bool LessThan(const uint32_t& a, const uint32_t& b) { return a < b; }

inline MergeElem* CopyLoop(const MergeElem* first, const MergeElem* last, MergeElem* result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}

inline MergeElem* CopyElems(const MergeElem* first, const MergeElem* last, MergeElem* result)
{
    char b = 0, a = 0, c = 0;
    return CopyLoop(first, last, result);
}

// @ 0x0042f160
MergeElem* MergeRanges(const MergeElem* first1, const MergeElem* last1, const MergeElem* first2,
                       const MergeElem* last2, MergeElem* result)
{
    while (first1 != last1 && first2 != last2) {
        if (LessThan(first2->key, first1->key)) {
            *result = *first2;
            ++first2;
        } else {
            *result = *first1;
            ++first1;
        }
        ++result;
    }
    return CopyElems(first2, last2, CopyElems(first1, last1, result));
}

// ---------------------------------------------------------------------------
// vector<uint32_t>
// ---------------------------------------------------------------------------
void* AllocatorAllocate(Alloc* a, uint32_t size, uint32_t align, uint32_t offset);  // 0x0042dee0
uint32_t* UninitializedCopy(uint32_t* first, uint32_t* last, uint32_t* dest);       // 0x00511f70

struct UIntVectorBase {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    Alloc mAllocator;

    UIntVectorBase(uint32_t n, const Alloc& a);
};

// @ 0x0042f2e0
UIntVectorBase::UIntVectorBase(uint32_t n, const Alloc& a)
{
    mAllocator = a;
    mpBegin = n ? (uint32_t*)AllocatorAllocate(&mAllocator, n * 4, 4, 0) : 0;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
}

struct UIntVector : UIntVectorBase {
    UIntVector(const UIntVector& x);
};

// @ 0x0042f280
UIntVector::UIntVector(const UIntVector& x) : UIntVectorBase((uint32_t)(x.mpEnd - x.mpBegin), x.mAllocator)
{
    uint32_t dead[18];
    mpEnd = UninitializedCopy(x.mpBegin, x.mpEnd, mpBegin);
}

// ---------------------------------------------------------------------------
// wide string
// ---------------------------------------------------------------------------
struct WString {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    Alloc mAllocator;

    WString(const WString& x);
    void AllocateSelf(const uint16_t* b, const uint16_t* e);  // 0x00423820
    void FreeBuffer();                                         // 0x004237d0
    void Resize(uint32_t n);                                   // 0x00429520
    void Swap(WString& x);                                     // 0x0042f620
    void SetCapacity(uint32_t n);                              // 0x0042f360
    WString& AssignRange(const uint16_t* b, const uint16_t* e);    // 0x0042f920
    void Assign(const uint16_t* b, const uint16_t* e);         // 0x00423650
    void EraseRange(uint16_t* b, uint16_t* e);                 // 0x0042e2f0
    void AppendRange(const uint16_t* b, const uint16_t* e);    // 0x0042f9d0
};

void* EastlAllocate(uint32_t size, const char* name, uint32_t flags, uint32_t align,
                    const char* file, int line);  // 0x00f473a0

// @ 0x0042f7e0
WString::WString(const WString& x)
{
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    mAllocator = x.mAllocator;
    AllocateSelf(x.mpBegin, x.mpEnd);
}

inline void DeadHelper()
{
    uint32_t dead[3];
}

template <class T> inline void Swap3(T& a, T& b)
{
    T t = a;
    a = b;
    b = t;
}

// @ 0x0042f620
void WString::Swap(WString& x)
{
    uint32_t dead0;
    if (true) {
        Swap3(mpBegin, x.mpBegin);
        Swap3(mpEnd, x.mpEnd);
        Swap3(mpCapacity, x.mpCapacity);
        DeadHelper();
    } else {
        struct { uint16_t* b; uint16_t* e; uint16_t* c; } tmp = {0, 0, 0};
        ((WString*)&tmp)->AllocateSelf(mpBegin, mpEnd);
        if (&x != this)
            Assign(x.mpBegin, x.mpEnd);
        if ((WString*)&tmp != &x)
            x.Assign(tmp.b, tmp.e);
        ((WString*)&tmp)->FreeBuffer();
    }
}

inline uint16_t* DoAllocate(uint32_t n)
{
    uint16_t* p = (uint16_t*)EastlAllocate(
        n * 2, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    return p;
}

inline uint16_t* UninitializedCopy16(const uint16_t* first, const uint16_t* last, uint16_t* dest)
{
    memcpy(dest, first, (last - first) * 2);
    return dest + (last - first);
}

// @ 0x0042f360
void WString::SetCapacity(uint32_t n)
{
    uint32_t dead0;
    if (n == (uint32_t)-1 || n <= (uint32_t)(mpEnd - mpBegin)) {
        if (n < (uint32_t)(mpEnd - mpBegin))
            Resize(n);
        struct { uint16_t* b; uint16_t* e; uint16_t* c; } tmp = {0, 0, 0};
        ((WString*)&tmp)->AllocateSelf(mpBegin, mpEnd);
        Swap(*(WString*)&tmp);
        ((WString*)&tmp)->FreeBuffer();
    } else {
        uint16_t* pNew;
        uint16_t* pEnd;
        {
            uint32_t dead1[3];
            pNew = DoAllocate(n);
            pEnd = pNew;
            pEnd = UninitializedCopy16(mpBegin, mpEnd, pNew);
            *pEnd = 0;
            FreeBuffer();
            mpBegin = pNew;
            mpEnd = pEnd;
            mpCapacity = pNew + n;
            DeadHelper();
        }
    }
}

// @ 0x0042f920
WString& WString::AssignRange(const uint16_t* b, const uint16_t* e)
{
    uint32_t n = (uint32_t)(e - b);
    if (n <= (uint32_t)(mpEnd - mpBegin)) {
        memcpy(mpBegin, b, n * 2);
        EraseRange(mpBegin + n, mpEnd);
    } else {
        memcpy(mpBegin, b, (mpEnd - mpBegin) * 2);
        AppendRange(b + (mpEnd - mpBegin), e);
    }
    return *this;
}

// ---------------------------------------------------------------------------
// intrusive_ptr range assignment
// ---------------------------------------------------------------------------
inline void AssignRef(IRefCounted*& dst, IRefCounted* p)
{
    if (p != dst) {
        IRefCounted* old = dst;
        if (p)
            p->AddRef();
        dst = p;
        if (old)
            old->Release();
    }
}

// @ 0x0042f530
IRefCounted** CopyPtrs(IRefCounted** first, IRefCounted** last, IRefCounted** result)
{
    for (; first != last; ++result, ++first)
        AssignRef(*result, *first);
    return result;
}

// @ 0x0042f5b0
IRefCounted** CopyPtrsBackward(IRefCounted** first, IRefCounted** last, IRefCounted** result)
{
    while (last != first) {
        --last;
        --result;
        AssignRef(*result, *last);
    }
    return result;
}

// ---------------------------------------------------------------------------
// deque iterator copy
// ---------------------------------------------------------------------------
struct DequeElem {
    uint32_t data[12];
    DequeElem& operator=(const DequeElem& x);  // 0x00405440
};

struct DequeIter {
    DequeElem* mpCurrent;
    DequeElem* mpBegin;
    DequeElem* mpEnd;
    DequeElem** mpCurrentArrayPtr;

    DequeIter(const DequeIter& x);   // 0x00420050
    DequeElem& operator*() const;    // 0x005658b0
    DequeIter& operator++();         // 0x004253c0
    DequeIter& operator--();         // 0x0042f840
};

inline bool operator!=(const DequeIter& a, const DequeIter& b) { return a.mpCurrent != b.mpCurrent; }

// @ 0x0042f840
DequeIter& DequeIter::operator--()
{
    if (mpCurrent == mpBegin) {
        --mpCurrentArrayPtr;
        mpBegin = *mpCurrentArrayPtr;
        mpEnd = mpBegin + 4;
        mpCurrent = mpEnd;
    }
    --mpCurrent;
    return *this;
}

// @ 0x0042f720
DequeIter DequeCopyImpl(DequeIter first, DequeIter last, DequeIter result)
{
    uint32_t dead[20];
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}

// @ 0x0042f780
DequeIter DequeCopyBackwardImpl(DequeIter first, DequeIter last, DequeIter result)
{
    uint32_t dead[20];
    while (last != first)
        *--result = *--last;
    return result;
}

// @ 0x0042f490
DequeIter DequeCopy(DequeIter first, DequeIter last, DequeIter result)
{
    char tag = 0;
    uint32_t dead[10];
    uint32_t dead2[10];
    return DequeCopyImpl(first, last, result);
}

// @ 0x0042f4e0
DequeIter DequeCopyBackward(DequeIter first, DequeIter last, DequeIter result)
{
    char tag = 0;
    uint32_t dead[10];
    uint32_t dead2[10];
    return DequeCopyBackwardImpl(first, last, result);
}

// ---------------------------------------------------------------------------
// threaded-object holder assignment
// ---------------------------------------------------------------------------
struct ThreadedObject {
    uint32_t pad;
    volatile long mnRefCount;
    void Release();  // 0x00404f90
};

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedIncrement)

struct ThreadedPtr {
    ThreadedObject* mpObject;
    ThreadedPtr& operator=(const ThreadedPtr& x)
    {
        return operator=(x.mpObject);
    }
    ThreadedPtr& operator=(ThreadedObject* p)
    {
        ThreadedObject* old;
        uint32_t dead[3];
        if (p != mpObject) {
            old = mpObject;
            if (p)
                _InterlockedIncrement(&p->mnRefCount);
            mpObject = p;
            if (old)
                old->Release();
        }
        return *this;
    }
};

struct ThreadedHolder {
    uint32_t mID;
    ThreadedPtr mPtr;
    ThreadedHolder& operator=(const ThreadedHolder& x);
};

// @ 0x0042f8b0
ThreadedHolder& ThreadedHolder::operator=(const ThreadedHolder& x)
{
    mID = x.mID;
    mPtr = x.mPtr;
    return *this;
}
