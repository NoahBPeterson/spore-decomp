// EASTL container helpers (instantiated templates) built without optimization:
// allocator front end, uninitialized_copy / uninitialized_move / uninitialized_fill_n
// loops, copy_backward for intrusive pointers, a merge sort over 12-byte elements,
// and a few vector/string growth helpers.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE (no EH frames)

typedef unsigned int uint32_t;
typedef unsigned int size_t;

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedIncrement)
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, size_t);

inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

static const char kEastlAllocatorFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// --- externals ----------------------------------------------------------------
void* __cdecl EASTL_allocator_allocate(size_t n, const char* name, int flags, int a, const char* file, int line);        // 0x00F473A0
void* __cdecl EASTL_allocator_allocate_aligned(size_t n, size_t align, size_t off, const char* name, int flags, int a, const char* file, int line); // 0x00F473D0

struct Tag {};                        // is_pod style dispatch tag

struct Elem12 { uint32_t a, b, c; };

struct Elem48 {                       // 0x30 bytes, copy-constructed out of line (0x0042CBF0)
    Elem48(const Elem48& o);
    uint32_t d[12];
};
struct Elem16 {                       // 0x10 bytes; the copy body is out of line (0x00401B80)
    void Copy(const Elem16& o);
    Elem16(const Elem16& o) { Copy(o); }
    uint32_t d[4];
};
struct Elem56 {                       // 0x38 bytes (0x0040CE80)
    Elem56(const Elem56& o);
    uint32_t d[14];
};

struct Counted {                      // intrusive refcount at +0x40
    uint32_t pad[16];
    int refCount;
    void Release();                   // 0x0040F360
};
struct ThreadedObject {               // atomic refcount at +4
    uint32_t pad;
    volatile long refCount;
    void AddRef() { _InterlockedIncrement(&refCount); }
    void Release();                   // 0x00404F90
};

template<int N> inline void padfn() { uint32_t pad[N]; }

// Generic iterator wrapper (EASTL generic_iterator style).
template<class T> struct It {
    T* p;
    It(T* q) : p(q) {}
    T& operator*() const { return *p; }
    It& operator++() { ++p; return *this; }
};
template<class T> inline bool operator!=(It<T> a, It<T> b) { return a.p != b.p; }

// @ 0x0042DEE0
void* EASTL_Allocate(void* /*allocator*/, size_t n, size_t align, size_t offset)
{
    void* p;
    void* q;
    if (align <= 8) {
        p = EASTL_allocator_allocate(n, "Editor", 0, 0, kEastlAllocatorFile, 0xd1);
        return p;
    }
    q = EASTL_allocator_allocate_aligned(n, align, offset, "Editor", 0, 0, kEastlAllocatorFile, 0xe5);
    return q;
}

// --- uninitialized_copy ---------------------------------------------------------
// eastl::uninitialized_copy_impl over generic_iterator wrappers. The unused padfn<N>() block
// stands in for dead locals of the original's inline layers (see padfn above).
template<class T, int N> __forceinline It<T> uninitialized_copy_impl(It<T> first, It<T> last, It<T> dest)
{
    It<T> cur(dest);
    for (; first != last; ++first, ++cur)
        ::new((void*)&*cur) T(*first);
    padfn<N>();
    return cur;
}

// @ 0x0042DF50
Elem48* UninitializedCopy48(Elem48* first, Elem48* last, Elem48* dest)
{
    const It<Elem48> i(uninitialized_copy_impl<Elem48, 4>(It<Elem48>(first), It<Elem48>(last), It<Elem48>(dest)));
    Elem48* unused;
    return i.p;
}

// @ 0x0042E410
Elem16* UninitializedCopy16(Elem16* first, Elem16* last, Elem16* dest)
{
    const It<Elem16> i(uninitialized_copy_impl<Elem16, 1>(It<Elem16>(first), It<Elem16>(last), It<Elem16>(dest)));
    Elem16* unused;
    return i.p;
}

// @ 0x0042E510
Elem56* UninitializedCopy56(Elem56* first, Elem56* last, Elem56* dest)
{
    const It<Elem56> i(uninitialized_copy_impl<Elem56, 14>(It<Elem56>(first), It<Elem56>(last), It<Elem56>(dest)));
    Elem56* unused;
    return i.p;
}

// --- uninitialized_move (copy, then an empty destroy pass) ------------------------
// Two inline passes over the range. The byte locals are the original's empty is_pod
// dispatch flags; padfn stands for dead locals of its inline layers.
inline Elem48* uninitialized_copy_pass(Elem48* first, Elem48* last, Elem48* dest)
{
    padfn<4>();
    for (; first != last; ++first, ++dest)
        ::new((void*)&*dest) Elem48(*first);
    return dest;
}
inline void destroy_pass(Elem48* first, Elem48* last, Elem48* dest)
{
    for (; first != last; ++first, ++dest) {}
}
inline void destroy_pass_tagged(Elem48* first, Elem48* last, Elem48* dest)
{
    const bool b2 = false;
    destroy_pass(first, last, dest);
}

// @ 0x0042DFF0
Elem48* UninitializedMove48(Elem48* first, Elem48* last, Elem48* dest)
{
    Elem48* dst;
    const bool b = false;
    dst = uninitialized_copy_pass(first, last, dest);
    destroy_pass_tagged(first, last, dest);
    return dst;
}

// --- merge sort -------------------------------------------------------------------
void MergeRuns(Elem12* first1, Elem12* last1, Elem12* first2, Elem12* last2, Elem12* out, bool flag);   // 0x0042F160

// @ 0x0042E090
void MergeSortBuffer(Elem12* first, Elem12* last, Elem12* buffer, bool flag)
{
    int count = (int)(last - first);
    if (count > 1) {
        int half = count / 2;
        Elem12* mid = first + half;
        if (half > 1) {
            int quarter = half / 2;
            Elem12* q = first + quarter;
            MergeSortBuffer(first, q, buffer, flag);
            MergeSortBuffer(q, mid, buffer + quarter, flag);
            MergeRuns(first, q, q, mid, buffer, flag);
        } else {
            *buffer = *first;
        }
        if (count - half > 1) {
            int threeq = (half + count) / 2;
            Elem12* q = first + threeq;
            MergeSortBuffer(mid, q, buffer + half, flag);
            MergeSortBuffer(q, last, buffer + threeq, flag);
            MergeRuns(mid, q, q, last, buffer + half, flag);
        } else {
            buffer[half] = *mid;
        }
        MergeRuns(buffer, buffer + half, buffer + half, buffer + count, first, flag);
    }
}

// --- fill_n -------------------------------------------------------------------------
template<class T> inline T* fill_n_impl(T* first, size_t n, const T& value)
{
    const T tmp = value;
    for (; n-- > 0; ++first)
        *first = tmp;
    return first;
}

// @ 0x0042E240
uint32_t* FillN32(uint32_t* first, size_t n, const uint32_t* value)
{
    return fill_n_impl(first, n, *value);
}

// --- list node / vector helpers ------------------------------------------------------
struct NodeAlloc { char pad[0x18]; char allocator[1]; };

struct Elem12List {
    uint32_t pad[6];
    uint32_t allocator;               // +0x18
    struct Node { uint32_t links[4]; Elem12 value; };   // 0x1C bytes
    Node* AllocateNode(const Elem12& v);
};

// @ 0x0042E290
Elem12List::Node* Elem12List::AllocateNode(const Elem12& v)
{
    Node* node = (Node*)EASTL_Allocate(&allocator, 0x1c, 4, 0);
    ::new(&node->value) Elem12(v);
    return node;
}

struct WString {
    wchar_t* mBegin;
    wchar_t* mEnd;
    wchar_t* mCapEnd;
    wchar_t* erase(wchar_t* first, wchar_t* last);
    void reserve_internal(size_t n);  // 0x0042F360
    void reserve(size_t n);
};

// @ 0x0042E2F0
wchar_t* WString::erase(wchar_t* first, wchar_t* last)
{
    if (first != last) {
        memmove(first, last, (mEnd - last + 1) * sizeof(wchar_t));
        wchar_t* newEnd = mEnd - (last - first);
        mEnd = newEnd;
    }
    return first;
}

template<class T> inline const T& eastl_max(const T& a, const T& b)
{
    padfn<15>();
    return (a < b) ? b : a;
}

// @ 0x0042E610
void WString::reserve(size_t n)
{
    size_t size = mEnd - mBegin;
    n = eastl_max(n, size) + 1;
    if (n > (size_t)(mCapEnd - mBegin))
        reserve_internal(n);
}

// Containers with the allocator at +0xC
struct VecBase {
    uint32_t pad[3];
    uint32_t allocator;               // +0xC
};

uint32_t* CopyRange32(uint32_t* first, uint32_t* last, uint32_t* dest);   // 0x004D0B90
uint32_t* CopyRange32b(uint32_t* first, uint32_t* last, uint32_t* dest);  // 0x00511F70

struct Vec16Base : VecBase {
    Elem16* AllocCopy(size_t n, Elem16* first, Elem16* last);
};
struct Vec56Base : VecBase {
    Elem56* AllocCopy(size_t n, Elem56* first, Elem56* last);
};
struct Vec4Base : VecBase {
    uint32_t* AllocCopyA(size_t n, uint32_t* first, uint32_t* last);
    uint32_t* AllocCopyB(size_t n, uint32_t* first, uint32_t* last);
};
struct Vec2Base : VecBase {
    uint32_t* AllocCopy(size_t n, uint32_t* first, uint32_t* last);
};

// @ 0x0042E350
uint32_t* Vec2Base::AllocCopy(size_t n, uint32_t* first, uint32_t* last)
{
    uint32_t* p = n ? (uint32_t*)EASTL_Allocate(&allocator, n * 4, 2, 0) : 0;
    padfn<11>();
    CopyRange32(first, last, p);
    return p;
}

// @ 0x0042E3B0
Elem16* Vec16Base::AllocCopy(size_t n, Elem16* first, Elem16* last)
{
    Elem16* p = n ? (Elem16*)EASTL_Allocate(&allocator, n * 16, 4, 0) : 0;
    padfn<13>();
    UninitializedCopy16(first, last, p);
    return p;
}

// @ 0x0042E4B0
Elem56* Vec56Base::AllocCopy(size_t n, Elem56* first, Elem56* last)
{
    Elem56* p = n ? (Elem56*)EASTL_Allocate(&allocator, n * 56, 4, 0) : 0;
    padfn<25>();
    UninitializedCopy56(first, last, p);
    return p;
}

// @ 0x0042E5B0
uint32_t* Vec4Base::AllocCopyB(size_t n, uint32_t* first, uint32_t* last)
{
    uint32_t* p = n ? (uint32_t*)EASTL_Allocate(&allocator, n * 4, 4, 0) : 0;
    padfn<17>();
    CopyRange32b(first, last, p);
    return p;
}

// @ 0x0042E680
void UninitializedFillN56(It<Elem56> first, size_t n, const Elem56* value, Tag)
{
    It<Elem56> cur(first);
    for (; n > 0; --n, ++cur)
        ::new((void*)&*cur) Elem56(*value);
    padfn<14>();
}

// --- intrusive pointer copy_backward ----------------------------------------------------
struct CountedRef {
    Counted* p;
    CountedRef& operator=(Counted* x)
    {
        if (x != p) {
            Counted* old = p;
            if (x)
                x->refCount = x->refCount + 1;
            p = x;
            if (old)
                old->Release();
        }
        padfn<2>();
        return *this;
    }
};
struct ThreadedRef {
    ThreadedObject* p;
    ThreadedRef(const ThreadedRef& o) : p(o.p)
    {
        if (p)
            p->AddRef();
    }
    ThreadedRef& operator=(ThreadedObject* x)
    {
        if (x != p) {
            ThreadedObject* old = p;
            if (x)
                _InterlockedIncrement(&x->refCount);
            p = x;
            if (old)
                old->Release();
        }
        padfn<3>();
        return *this;
    }
};

template<class R> inline R* copy_backward_impl(R* first, R* last, R* dest)
{
    while (last != first) {
        --last;
        --dest;
        *dest = (*last).p;
    }
    return dest;
}

// @ 0x0042E6E0
CountedRef* CopyBackwardCounted(CountedRef* first, CountedRef* last, CountedRef* dest)
{
    const bool tag = false;
    return copy_backward_impl(first, last, dest);
}

// @ 0x0042E760
ThreadedRef* CopyBackwardThreaded(ThreadedRef* first, ThreadedRef* last, ThreadedRef* dest)
{
    const bool tag = false;
    return copy_backward_impl(first, last, dest);
}

// @ 0x0042E7E0
void UninitializedFillNThreaded(It<ThreadedRef> first, size_t n, const ThreadedRef* value, Tag)
{
    It<ThreadedRef> cur(first);
    for (; n > 0; --n, ++cur)
        ::new((void*)&*cur) ThreadedRef(*value);
}
