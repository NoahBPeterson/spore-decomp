// EASTL-style vector support (unoptimized module: /Od /Ob1, frame pointers, every local in memory).
//   - Vec124 : vector of 0x7c-byte elements (DoInsertValue, DoAllocateAndCopy, free, uninitialized_copy)
//   - Vec32  : vector of 0x20-byte elements (same set) + element assignment operators
//   - Vec140 : vector of 0x8c-byte elements (free, uninitialized_copy)
//   - SmallVec16 : fixed-buffer vector of 16-byte elements (free)
// Layout of every container: { T* mBegin; T* mEnd; T* mCapacity; Allocator mAllocator; }.

#include "types.h"

extern "C" void* __cdecl memcpy(void*, const void*, uint32_t);
#pragma intrinsic(memcpy)

inline void* operator new(unsigned int, void* p) { return p; }

struct Allocator { const char* mpName; };

// At /Od every local of an inlined EASTL helper keeps a stack slot; unused slots are reproduced with this.
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
template<> inline void ScratchSlots<0>() {}

// Thin iterator wrapper (EASTL generic_iterator): by-value arguments get their own stack temporaries.
template <typename T> struct gi
{
    T* it;
    explicit gi(T* x) : it(x) {}
    gi& operator++() { ++it; return *this; }
    T& operator*() const { return *it; }
    T* base() const { return it; }
};
template <typename T> inline bool operator!=(const gi<T>& a, const gi<T>& b) { return a.it != b.it; }

// uninitialized_copy_impl: placement-copy [first,last) into dest.  N = number of unused inlined-helper slots.
template <typename T, int N>
inline gi<T> UninitCopyImpl(gi<const T> first, gi<const T> last, gi<T> dest)
{
    gi<T> cur(dest);
    for (; first != last; ++first, ++cur)
        ::new (&*cur) T(*first);
    ScratchSlots<N>();
    return cur;
}

// Three empty-ish tag objects EASTL passes down copy_backward (each is a byte local at /Od).
struct TagA { char c; TagA() : c(0) {} };
struct TagB { char c; TagB() : c(0) {} };
struct TagC { char c; TagC() : c(0) {} };

// copy_backward(first, last, destEnd) via assignment; returns the new dest begin.
template <typename T>
struct CopyBackwardAlgo
{
    static T* CopyBackward(T* first, T* last, T* destEnd)
    {
        TagB tb = TagB(); TagA ta = TagA(); TagC tc = TagC();
        return CopyBackwardImpl(first, last, destEnd);
    }
    static T* CopyBackwardImpl(T* first, T* last, T* dest)
    {
        while (last != first)
        {
            --last;
            --dest;
            *dest = *last;
        }
        return dest;
    }
};

void* __cdecl AllocatorAllocate(Allocator* alloc, uint32_t size, uint32_t align, uint32_t offset);  // FUN_0042dee0
void  __cdecl AllocatorDeallocate(void* block);                                                    // EASTL_allocator_deallocate

// ---------------------------------------------------------------------------------------------
// Vec124
// ---------------------------------------------------------------------------------------------
struct Elem124
{
    uint32_t data[31];
    Elem124(const Elem124& src);                  // FUN_00422fd0
    Elem124& operator=(const Elem124& src);       // FUN_00429370
};
Elem124* __cdecl UninitializedCopy124(Elem124* first, Elem124* last, Elem124* dest);  // FUN_00424c00 (in slice)
Elem124* __cdecl MoveRange124(Elem124* first, Elem124* last, Elem124* destEnd);    // FUN_0042a680

struct Vec124
{
    Elem124* mBegin;
    Elem124* mEnd;
    Elem124* mCapacity;
    Allocator mAllocator;

    void DoFreeRange(Elem124* p, uint32_t /*n*/)
    {
        if (p)
        {
            if (((uint32_t*)p)[-1])
            {
                void* q = p;
                AllocatorDeallocate(q);
            }
        }
    }
    void DoInsertValue(Elem124* pos, const Elem124* value);
    Elem124* DoAllocateAndCopy(uint32_t n, Elem124* first, Elem124* last);
    void Free();
};

// @ 0x004248c0
void Vec124::DoInsertValue(Elem124* pos, const Elem124* value)
{
    if (mEnd != mCapacity)
    {
        const Elem124* v = value;
        if (v >= pos && v < mEnd)
            ++v;

        new (mEnd) Elem124(*(mEnd - 1));
        CopyBackwardAlgo<Elem124>::CopyBackward(pos, mEnd - 1, mEnd);
        *pos = *v;
        ++mEnd;
    }
    else
    {
        ScratchSlots<24>();
        uint32_t prevCount = mEnd - mBegin;                 // current size
        uint32_t newCount = prevCount > 0 ? prevCount * 2 : 1;
        Elem124* result = newCount ? (Elem124*)AllocatorAllocate(&mAllocator, newCount * sizeof(Elem124), 4, 0) : 0;  // new buffer
        Elem124* nCount = MoveRange124(mBegin, pos, result);   // running end of the new buffer
        new (nCount) Elem124(*value);
        nCount = nCount + 1;
        nCount = MoveRange124(pos, mEnd, nCount);
        DoFreeRange(mBegin, mCapacity - mBegin);
        mBegin = result;
        mEnd = nCount;
        mCapacity = result + newCount;
    }
}

// @ 0x00424b40
void Vec124::Free()
{
    void* q;
    if (mBegin)
    {
        int bytes = (int)(mCapacity - mBegin) * sizeof(Elem124);
        Elem124* p = mBegin;
        (void)bytes;
        if (((uint32_t*)p)[-1])
        {
            q = p;
            AllocatorDeallocate(q);
        }
    }
}

// @ 0x00424ba0
Elem124* Vec124::DoAllocateAndCopy(uint32_t n, Elem124* first, Elem124* last)
{
    Elem124* result = n ? (Elem124*)AllocatorAllocate(&mAllocator, n * sizeof(Elem124), 4, 0) : 0;
    ScratchSlots<17>();
    UninitializedCopy124(first, last, result);
    return result;
}

// @ 0x00424c00
Elem124* __cdecl UninitializedCopy124(Elem124* first, Elem124* last, Elem124* dest)
{
    uint32_t pad[1];
    const gi<Elem124> i(UninitCopyImpl<Elem124, 5>(gi<const Elem124>(first), gi<const Elem124>(last), gi<Elem124>(dest)));
    return i.base();
}

// ---------------------------------------------------------------------------------------------
// SmallVec16: fixed-buffer vector (inline buffer pointer stored at +0x10)
// ---------------------------------------------------------------------------------------------
struct SmallVec16
{
    char* mBegin;
    char* mEnd;
    char* mCapacity;
    Allocator mAllocator;
    char* mInlineBuffer;

    void Free();
};

// @ 0x00424ca0
void SmallVec16::Free()
{
    void* q;
    if (mBegin)
    {
        int bytes = ((int)(mCapacity - mBegin) >> 4) << 4;
        char* p = mBegin;
        (void)bytes;
        if (p != mInlineBuffer)
        {
            q = p;
            AllocatorDeallocate(q);
        }
    }
}

// ---------------------------------------------------------------------------------------------
// Vec32
// ---------------------------------------------------------------------------------------------
struct RefObject
{
    virtual void AddRef();
    virtual void Release();
};

struct Handle   // 0x10 bytes: two words, two shorts, intrusive ref pointer at +0xc
{
    uint32_t a;
    uint32_t b;
    uint16_t c;
    uint16_t d;
    RefObject* mpRef;

    Handle* Assign(const Handle* src);   // FUN_00424f70
};

struct Elem32
{
    uint32_t w0, w1, w2, w3;
    Handle handle;

    Elem32(const Elem32& src);                  // FUN_00423080
    Elem32& operator=(const Elem32& src);       // FUN_00424f10
};
Elem32* __cdecl UninitializedCopy32(Elem32* first, Elem32* last, Elem32* dest);  // FUN_00425010 (in slice)
Elem32* __cdecl MoveRange32(Elem32* first, Elem32* last, Elem32* destEnd);    // FUN_0042a730

struct Vec32
{
    Elem32* mBegin;
    Elem32* mEnd;
    Elem32* mCapacity;
    Allocator mAllocator;

    void DoFreeRange(Elem32* p, uint32_t /*n*/)
    {
        if (p)
        {
            if (((uint32_t*)p)[-1])
            {
                void* q = p;
                AllocatorDeallocate(q);
            }
        }
    }
    void DoInsertValue(Elem32* pos, const Elem32* value);
};

// @ 0x00424cf0
void Vec32::DoInsertValue(Elem32* pos, const Elem32* value)
{
    if (mEnd != mCapacity)
    {
        const Elem32* v = value;
        if (v >= pos && v < mEnd)
            ++v;

        new (mEnd) Elem32(*(mEnd - 1));
        CopyBackwardAlgo<Elem32>::CopyBackward(pos, mEnd - 1, mEnd);
        *pos = *v;
        ++mEnd;
    }
    else
    {
        ScratchSlots<15>();
        uint32_t prevCount = mEnd - mBegin;                 // current size
        uint32_t newCount = prevCount > 0 ? prevCount * 2 : 1;
        Elem32* result = newCount ? (Elem32*)AllocatorAllocate(&mAllocator, newCount * sizeof(Elem32), 4, 0) : 0;  // new buffer
        Elem32* nCount = MoveRange32(mBegin, pos, result);   // running end of the new buffer
        new (nCount) Elem32(*value);
        nCount = nCount + 1;
        nCount = MoveRange32(pos, mEnd, nCount);
        DoFreeRange(mBegin, mCapacity - mBegin);
        mBegin = result;
        mEnd = nCount;
        mCapacity = result + newCount;
    }
}

// @ 0x00424f10
Elem32& Elem32::operator=(const Elem32& src)
{
    ScratchSlots<3>();
    w0 = src.w0;
    w1 = src.w1;
    w2 = src.w2;
    w3 = src.w3;
    handle.Assign(&src.handle);
    return *this;
}

// @ 0x00424f70
Handle* Handle::Assign(const Handle* src)
{
    RefObject* old;
    a = src->a;
    b = src->b;
    c = src->c;
    d = src->d;
    RefObject** slot = &mpRef;
    RefObject* incoming = src->mpRef;
    if (incoming != *slot)
    {
        old = *slot;
        if (incoming)
            incoming->AddRef();
        *slot = incoming;
        if (old)
            old->Release();
    }
    return this;
}

// @ 0x00425010
Elem32* __cdecl UninitializedCopy32(Elem32* first, Elem32* last, Elem32* dest)
{
    uint32_t pad[1];
    const gi<Elem32> i(UninitCopyImpl<Elem32, 1>(gi<const Elem32>(first), gi<const Elem32>(last), gi<Elem32>(dest)));
    return i.base();
}

// ---------------------------------------------------------------------------------------------
// Vec140
// ---------------------------------------------------------------------------------------------
struct Elem140
{
    uint32_t data[35];
    Elem140(const Elem140& src);                  // FUN_0042cba0
};

struct Vec140
{
    Elem140* mBegin;
    Elem140* mEnd;
    Elem140* mCapacity;
    Allocator mAllocator;

    void Free();
};

// @ 0x004250b0
void Vec140::Free()
{
    void* q;
    if (mBegin)
    {
        int bytes = (int)(mCapacity - mBegin) * sizeof(Elem140);
        Elem140* p = mBegin;
        (void)bytes;
        if (((uint32_t*)p)[-1])
        {
            q = p;
            AllocatorDeallocate(q);
        }
    }
}

// @ 0x00425110
Elem140* __cdecl UninitializedCopy140(Elem140* first, Elem140* last, Elem140* dest)
{
    uint32_t pad[1];
    const gi<Elem140> i(UninitCopyImpl<Elem140, 4>(gi<const Elem140>(first), gi<const Elem140>(last), gi<Elem140>(dest)));
    return i.base();
}

// ---------------------------------------------------------------------------------------------
// List node allocation (node = 0x18 bytes: two-word key, intrusive ref pointer at +8, link at +0x10)
// ---------------------------------------------------------------------------------------------
struct RefNode
{
    uint32_t key[2];
    RefObject* mpRef;
    uint32_t pad;
    RefNode* mpNext;
    uint32_t pad2;

    RefNode(const RefNode& src)
    {
        memcpy(key, src.key, 8);
        RefObject** slot = &mpRef;
        *slot = src.mpRef;
        if (*slot)
            (*slot)->AddRef();
    }
};

struct RefNodeList
{
    char pad[0x1c];
    Allocator mAllocator;

    RefNode* DoCreateNode(const RefNode* src);
};

// @ 0x004251b0
RefNode* RefNodeList::DoCreateNode(const RefNode* src)
{
    RefNode* node = (RefNode*)AllocatorAllocate(&mAllocator, sizeof(RefNode), 8, 0);
    new (node) RefNode(*src);
    node->mpNext = 0;
    return node;
}
