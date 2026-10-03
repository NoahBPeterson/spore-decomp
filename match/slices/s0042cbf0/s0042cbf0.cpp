// Slice 0x0042cbf0..0x0042d520: a 3x4 float matrix copy, EASTL fixed_vector assign
// instantiations (fixed_vector<IdHandle,6> and fixed_vector<HandleEntry,3>), a
// basic_string<char16_t>::append(n, c), and a few intrusive-pointer range helpers
// (fill / copy / uninitialized_copy wrapper).
// Built without optimization: /Od /Ob1 /MD /Gy /EHsc /TP (see manifest flags).
// The original EASTL helper layering (copy -> copy_impl, DoFree, DestructRange,
// FillN -> FillImpl, ...) is reproduced with small inline functions so the frame
// layout comes out the same.

#include "types.h"
#include <intrin.h>

typedef unsigned int size_t;
typedef unsigned short char16;

// ---------------------------------------------------------------------------
// Common bits
// ---------------------------------------------------------------------------
struct fwd_tag {};
struct tagq {};

extern void __cdecl EASTL_allocator_deallocate(void* p);   // 0x00f47380
inline void dealloc_wrap(void* p) { EASTL_allocator_deallocate(p); }

// Unused inline-expansion frame space left by the original's dead helper layers.
inline void padfn11() { uint32_t pad[11]; }
inline void padfn3() { uint32_t pad[3]; }
inline void padfn13() { uint32_t pad[13]; }

// Fixed-buffer allocator state living inside a fixed_vector.
struct FixedAlloc {
    int mName;
    void* mpPool;
    inline FixedAlloc(void* buf) { mpPool = buf; }
    inline FixedAlloc(const FixedAlloc& o) { mpPool = o.mpPool; }
    inline void deallocate(void* p) { void* q = p; dealloc_wrap(q); }
};

template<class T>
struct VectorBase {
    T *mpBegin, *mpEnd, *mpCapacity;
    FixedAlloc mAlloc;
    inline VectorBase(const FixedAlloc& a) : mpBegin(0), mpEnd(0), mpCapacity(0), mAlloc(a) {}
};

// ---------------------------------------------------------------------------
// 0x0042cbf0: 3x4 float matrix assignment (48 bytes, three float4 rows)
// ---------------------------------------------------------------------------
struct Matrix34 {
    struct Row {
        float x, y, z, w;
        Row& operator=(const Row& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
    };
    Row a, b, c;
    Matrix34& operator=(const Matrix34& o);
};

// @ 0x0042cbf0
Matrix34& Matrix34::operator=(const Matrix34& o) {
    a.x = o.a.x; a.y = o.a.y; a.z = o.a.z; a.w = o.a.w;
    b = o.b;
    c = o.c;
    return *this;
}

// ---------------------------------------------------------------------------
// fixed_vector<IdHandle, 6>  (IdHandle = 4-byte id struct)
// ---------------------------------------------------------------------------
struct IdHandle { uint32_t v; };

inline IdHandle* id_copy_impl(const IdHandle* first, const IdHandle* last, IdHandle* result) {
    for (; first != last; ++result, ++first) *result = *first;
    return result;
}
inline IdHandle* id_copy(const IdHandle* first, const IdHandle* last, IdHandle* result) {
    bool x, y, z; x = false; y = false; z = false;
    return id_copy_impl(first, last, result);
}
extern IdHandle* __cdecl id_uninitialized_copy(const IdHandle* f, const IdHandle* l, IdHandle* d);  // 0x004d0b90

struct IdRange { const IdHandle* first; const IdHandle* last; };

struct FixedIdVector6 : VectorBase<IdHandle> {
    int mPad;
    IdHandle mBuffer[6];

    FixedIdVector6(const IdRange& r);
    inline void AssignRange(const IdHandle* first, const IdHandle* last) { fwd_tag t; DoAssign(first, last, t); }
    IdHandle* DoAllocateAndCopy(size_t n, const IdHandle* f, const IdHandle* l);   // 0x0042e350
    inline void DoFree(IdHandle* p, size_t n) { if (p && p != mAlloc.mpPool) mAlloc.deallocate(p); }
    inline void DestructRange(IdHandle* f, IdHandle* l) { for (; f < l; ++f) {} }
    void DoAssign(const IdHandle* first, const IdHandle* last, fwd_tag);
};

// @ 0x0042ccb0
FixedIdVector6::FixedIdVector6(const IdRange& r) : VectorBase<IdHandle>(FixedAlloc(mBuffer)) {
    mpEnd = mBuffer; mpBegin = mpEnd; mpCapacity = mpBegin + 6;
    AssignRange(r.first, r.last);
}

// @ 0x0042cd50
void FixedIdVector6::DoAssign(const IdHandle* first, const IdHandle* last, fwd_tag) {
    const size_t n = (size_t)(last - first);
    if (n > size_t(mpCapacity - mpBegin)) {
        IdHandle* const pNew = DoAllocateAndCopy(n, first, last);
        DestructRange(mpBegin, mpEnd);
        DoFree(mpBegin, size_t(mpCapacity - mpBegin));
        mpBegin = pNew; mpEnd = mpBegin + n; mpCapacity = mpEnd;
    } else if (n <= size_t(mpEnd - mpBegin)) {
        IdHandle* const pEnd = id_copy(first, last, mpBegin);
        DestructRange(pEnd, mpEnd);
        mpEnd = pEnd;
    } else {
        const IdHandle* const pMid = first + (mpEnd - mpBegin);
        IdHandle gap[10];
        id_copy(first, pMid, mpBegin);
        mpEnd = id_uninitialized_copy(pMid, last, mpEnd);
        padfn11();
    }
}

// ---------------------------------------------------------------------------
// fixed_vector<HandleEntry, 3>  (16-byte entries with a ref-counted pointer at +0xc)
// ---------------------------------------------------------------------------
struct IRefCounted {
    virtual void AddRef();
    virtual void Release();
};
struct SmartPtr {
    IRefCounted* mp;
    ~SmartPtr() { if (mp) mp->Release(); }
};
struct HandleEntry {
    uint32_t id0, id1;
    uint16_t w0, w1;
    SmartPtr ref;
    HandleEntry& operator=(const HandleEntry& o);    // 0x00424f70
};

inline HandleEntry* entry_copy_impl(const HandleEntry* first, const HandleEntry* last, HandleEntry* result) {
    for (; first != last; ++result, ++first) *result = *first;
    return result;
}
inline HandleEntry* entry_copy(const HandleEntry* first, const HandleEntry* last, HandleEntry* result) {
    bool x, y, z; x = false; y = false; z = false;
    return entry_copy_impl(first, last, result);
}
// Same as entry_copy; the extra pad reproduces unused frame space of the original's
// partial-copy (pMid) path.
inline HandleEntry* entry_copy_mid(const HandleEntry* first, const HandleEntry* last, HandleEntry* result) {
    bool x, y, z; x = false; y = false; z = false;
    padfn3();
    return entry_copy_impl(first, last, result);
}
extern HandleEntry* __cdecl entry_uninitialized_copy(const HandleEntry* f, const HandleEntry* l, HandleEntry* d);  // 0x0042e410

struct EntryRange { const HandleEntry* first; const HandleEntry* last; };

struct FixedEntryVector3 : VectorBase<HandleEntry> {
    int mPad;
    uint32_t mBuffer[12];

    FixedEntryVector3(const EntryRange& r);
    inline void AssignRange(const HandleEntry* first, const HandleEntry* last) { fwd_tag t; DoAssign(first, last, t); }
    HandleEntry* DoAllocateAndCopy(size_t n, const HandleEntry* f, const HandleEntry* l);   // 0x0042e3b0
    inline void DoFree(HandleEntry* p, size_t n) { if (p && p != mAlloc.mpPool) mAlloc.deallocate(p); }
    inline void DestructRange(HandleEntry* f, HandleEntry* l) { for (; f < l; ++f) f->~HandleEntry(); }
    void DoAssign(const HandleEntry* first, const HandleEntry* last, fwd_tag);
};

// @ 0x0042cf80
FixedEntryVector3::FixedEntryVector3(const EntryRange& r) : VectorBase<HandleEntry>(FixedAlloc(mBuffer)) {
    mpEnd = (HandleEntry*)mBuffer; mpBegin = mpEnd; mpCapacity = mpBegin + 3;
    AssignRange(r.first, r.last);
}

// @ 0x0042d020
void FixedEntryVector3::DoAssign(const HandleEntry* first, const HandleEntry* last, fwd_tag) {
    const size_t n = (size_t)(last - first);
    if (n > size_t(mpCapacity - mpBegin)) {
        HandleEntry* const pNew = DoAllocateAndCopy(n, first, last);
        DestructRange(mpBegin, mpEnd);
        DoFree(mpBegin, size_t(mpCapacity - mpBegin));
        mpBegin = pNew; mpEnd = mpBegin + n; mpCapacity = mpEnd;
    } else if (n <= size_t(mpEnd - mpBegin)) {
        HandleEntry* const pEnd = entry_copy(first, last, mpBegin);
        DestructRange(pEnd, mpEnd);
        mpEnd = pEnd;
    } else {
        const HandleEntry* const pMid = first + (mpEnd - mpBegin);
        uint32_t gap[10];
        entry_copy_mid(first, pMid, mpBegin);
        mpEnd = entry_uninitialized_copy(pMid, last, mpEnd);
        padfn13();
    }
}

// ---------------------------------------------------------------------------
// basic_string<char16_t>
// ---------------------------------------------------------------------------
struct WString {
    char16 *mpBegin, *mpEnd, *mpCapacity;
    void reserve(size_t n);       // 0x0042e610
    WString& append(size_t n, char16 c);
    static inline size_t GetNewCapacity(size_t cap) { return (cap > 8) ? (cap * 2) : 8; }
};
template<class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

inline void FillImpl(char16* dest, const size_t& n, char16 c) {
    char16* p = dest;
    char16* const pEnd = dest + n;
    while (p < pEnd) { *p = c; ++p; }
}
inline void FillN(char16* dest, size_t n, char16 c) { FillImpl(dest, n, c); }

// @ 0x0042d2e0
WString& WString::append(size_t n, char16 c) {
    const size_t nSize = size_t(mpEnd - mpBegin);
    const size_t nCap = size_t(mpCapacity - mpBegin) - 1;
    if (nSize + n > nCap) {
        const size_t nNeed = nSize + n;
        reserve(Max(GetNewCapacity(nCap), nNeed));
    }
    if (n > 0) {
        FillN(mpEnd + 1, n - 1, c);
        *mpEnd = c;
        mpEnd += n;
        *mpEnd = 0;
    }
    return *this;
}

// @ 0x0042d3f0
// Reverse search: scans [first, last) backwards, returns `last` when not found.
const char16* RFindChar(const char16* first, const char16* last, char16 c) {
    const char16* p = last;
    while (--p >= first) {
        if (*p == c) return p;
    }
    return last;
}

// ---------------------------------------------------------------------------
// Intrusive-pointer range helpers
// ---------------------------------------------------------------------------
struct RefObj {
    int vtbl;
    int refCount;
    void Release();     // Resource::ThreadedObject::Release, 0x00404f90
    inline void AddRef() { int pad[3]; _InterlockedIncrement((long*)&refCount); }
};
struct IntrusivePtr {
    RefObj* mp;
    inline IntrusivePtr& operator=(const IntrusivePtr& x) { return Assign(x.mp); }
    inline IntrusivePtr& Assign(RefObj* p) {
        if (p != mp) {
            RefObj* const pTemp = mp;
            if (p) p->AddRef();
            mp = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};

inline void fill_impl(IntrusivePtr* first, IntrusivePtr* last, const IntrusivePtr& v) {
    for (; first != last; ++first) *first = v;
}
// @ 0x0042d430
void FillIntrusivePtrs(IntrusivePtr* first, IntrusivePtr* last, const IntrusivePtr& v) {
    fill_impl(first, last, v);
}

inline IntrusivePtr* copy_ptrs_impl(const IntrusivePtr* first, const IntrusivePtr* last, IntrusivePtr* result) {
    for (; first != last; ++result, ++first) *result = *first;
    return result;
}
// @ 0x0042d4a0
IntrusivePtr* CopyIntrusivePtrs(const IntrusivePtr* first, const IntrusivePtr* last, IntrusivePtr* result) {
    bool b = false;
    return copy_ptrs_impl(first, last, result);
}

struct PtrIter { const IntrusivePtr* p; inline PtrIter(const IntrusivePtr* q) : p(q) {} };
extern void __cdecl UninitCopyIntrusivePtrs(IntrusivePtr** out, PtrIter f, PtrIter l, PtrIter d, tagq);  // 0x0042e860

// @ 0x0042d520
IntrusivePtr* UninitializedCopyIntrusivePtrs(const IntrusivePtr* f, const IntrusivePtr* l, IntrusivePtr* d) {
    IntrusivePtr* r;
    tagq t;
    UninitCopyIntrusivePtrs(&r, PtrIter(f), PtrIter(l), PtrIter(d), t);
    return r;
}
