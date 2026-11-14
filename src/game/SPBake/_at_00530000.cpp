#include "game/types.h"

// Reserve N words of stack space (the original /Od frames keep these slots).
template<int N> inline void ScratchSlots() { uint32_t s[N]; }

inline void* operator new(size_t, void* p) { return p; }
void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line); // 0xf473a0
inline void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, name, flags, debugFlags, file, line); }
void* EASTL_Allocate(void* pAllocator, size_t n, size_t alignment, size_t offset); // 0x42dee0

namespace eastl {

template<typename T1, typename T2> struct pair_s0053_2f80 {
    T1 first;
    T2 second;
    pair_s0053_2f80(const T1& x, const T2& y) : first(x), second(y) {}
};

class allocator_s0053_2f80 { public:
    uint32_t mFlags;
    void deallocate(void* p, size_t) { delete[] (char*)p; }
};

class fixed_vector_allocator { public:
    allocator_s0053_2f80 mOverflowAllocator;
    void* mpPoolBegin;
    void deallocate(void* p, size_t n) { if (p != mpPoolBegin) mOverflowAllocator.deallocate(p, n); }
};

template<typename T> class fixed_vector_s0053_2f80 { public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    fixed_vector_allocator mAllocator;
    uint32_t mBuffer[0x44 / 4];

    fixed_vector_s0053_2f80();                                             // @ 0x41cfe0
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
void fixed_vector_s0053_2f80<T>::DoInsertValue(T* position, const T& value)
{
    if (mpEnd != mpCapacity) {
        // If the value lives inside the vector, it moves when the tail shifts.
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

} // namespace eastl

typedef eastl::pair_s0053_2f80<uint32_t, float> WeightPair;

// Two-base interface object: one vptr per base, plus the refcount at +0x8.
struct ISwarmObject { virtual int AddRef(); virtual int Release(); };
struct cSwarmRefCounted {
    virtual int AddRef();
    int mnRefCount;         // +0x08
    cSwarmRefCounted() : mnRefCount(0) {}
};
struct cSwarmObjectBase : public ISwarmObject, public cSwarmRefCounted {
    cSwarmObjectBase() {}
    virtual int AddRef();
};
struct cSwarmObject : public cSwarmObjectBase {
    uint32_t mValue;        // +0x0c, the constructor argument
    uint32_t mPad10;        // +0x10, never touched; makes the object 0x14 bytes
    cSwarmObject(uint32_t p) { mValue = p; }
    virtual int AddRef();
};

struct cFlagHolder {
    char pad[0x10];
    bool mbFlag;            // +0x10
    void ClearFlag(int);
};

// @ 0x00533960
template void eastl::fixed_vector_s0053_2f80<WeightPair>::DoInsertValue(WeightPair*, const WeightPair&)
;

// @ 0x00533ce0
cSwarmObject* CreateSwarmObject(uint32_t param)
{
    // EA operator new tag "Swarm"; the trailing zeros are flags/debugFlags/file/line.
    cSwarmObject* p = new("Swarm", 0, 0, 0, 0) cSwarmObject(param);
    return p;
}

// @ 0x00533d80
void cFlagHolder::ClearFlag(int)
{
    mbFlag = false;
}
