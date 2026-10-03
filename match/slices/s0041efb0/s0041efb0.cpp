// Slice 0x0041EFB0..0x0041F8E0: unoptimized (/Od /Ob1, no EH) EASTL-style vector<T> helpers.
//
// Everything here is a member of one class template, Vec<T> (begin/end/capacity pointers plus a
// 4-byte allocator at +0xC), instantiated for five element types:
//   Elem16 (trivially copyable, 16 bytes), Elem20 (32 bytes, holds a COM-like ref at +0x1C),
//   Elem7c (124 bytes, two refs at +0x74/+0x78), Elem8c (140 bytes) and RcPtr (4 bytes).
//
// The "PadN" / "uint32_t s[N]" locals are deliberate: at /Od every local of an inlined EASTL
// helper keeps a stack slot, and the original frames have those unused slots. Reproducing them
// is what makes the frame offsets (and therefore the bytes) identical.
#include "types.h"

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }

struct IRefCounted { virtual void AddRef(); virtual void Release(); };
struct DefaultRefCounted { void Release(); };  // @ 0x00453540

// Intrusive smart pointer: releases the object in its destructor.
template <class T> struct ptr {
    T* p;
    ptr() : p(0) {}
    ~ptr() { if (p) p->Release(); }
};

void AllocDeallocate(void* p);  // EASTL allocator deallocate (0x00F47380)
void* AllocAllocate(void* alloc, size_t n, size_t align, size_t off);  // 0x0042DEE0

template <int N> inline void PadN() { uint32_t s[N]; }

// ---- element types ---------------------------------------------------------------------

struct Elem16 { uint32_t pad[4]; };

struct Elem20 {
    uint32_t pad[7];
    ptr<IRefCounted> a;                  // +0x1C, released through vtable slot 1
    Elem20(const Elem20&);               // 0x00423080
};

struct Elem7c {
    char pad[0x74];
    ptr<IRefCounted> a;                  // +0x74
    ptr<DefaultRefCounted> b;            // +0x78
    Elem7c(const Elem7c&);               // 0x00422FD0
    Elem7c& operator=(const Elem7c&);    // 0x00429370
    ~Elem7c();
};

struct Elem8c {
    uint32_t pad[35];
    Elem8c(const Elem8c&);
    ~Elem8c();                           // 0x0041F940
};

typedef ptr<DefaultRefCounted> RcPtr;

// ---- helper stubs used by the operator= specializations --------------------------------

struct Tag {};
struct Ret16 { uint32_t a, b, c, d; };
struct TagA { char c; TagA() : c(0) {} };
struct TagB { char c; TagB() : c(0) {} };
struct TagC { char c; TagC() : c(0) {} };
void UninitCopyImpl(Ret16* out, Elem16* first, Elem16* last, Elem16* dest, Tag t);  // 0x0047A500
Elem16* CopyElems16(Elem16* first, Elem16* last, Elem16* dest);                      // 0x00424770
Elem7c* UninitCopy7c(Elem7c* first, Elem7c* last, Elem7c* dest);                     // 0x00424C00
template <class T> T* UninitCopy(T* first, T* last, T* dest);  // 0x00425010 / 0x00425110

// @ 0x0041F2D0
Elem7c::~Elem7c() { uint32_t s[3]; }

template <class T> struct Vec {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t alloc;

    void Destroy(T* first, T* last) {
        for (; first < last; ++first) first->~T();
    }
    void DoFreeImpl();
    void DoFree() { uint32_t s[3]; DoFreeImpl(); }
    ~Vec();
    void push_back(const T& v);
    void DoInsertValue(T* pos, const T& v);
    Vec(const Vec& o);
    Vec& operator=(const Vec& x);
    T* DoAllocateAndCopy(size_t n, T* first, T* last);
    T* DoAllocate(size_t n) { return n ? (T*)AllocAllocate(&alloc, n * sizeof(T), 4, 0) : 0; }

    // free a block obtained from the allocator (EASTL frees only blocks with a nonzero header word)
    void FreeImpl(void* p) { AllocDeallocate(p); }
    void DoFreeRange(T* p, size_t n) {
        if (p) {
            if (((int*)p)[-1]) { void* q = p; FreeImpl(q); }
        }
    }
    // Elem16 only: uninitialized_copy through three nested helpers (the stack layout shows all three)
    void UninitCopy16(T* first, T* last, T* dest) {
        Ret16 ret16; Tag t;
        volatile char tag;   // an unused 1-byte local occupies the slot just under the tag
        UninitCopy16M(&ret16, &t, dest, last, first);
    }
    void UninitCopy16M(Ret16* o, Tag* t, T* p0, T* p1, T* p2) {
        T* pDest = p0; T* last = p1; T* pFirst = p2;
        UninitCopy16O(o, t, pFirst, last, pDest);
    }
    void UninitCopy16O(Ret16* o, Tag* t, T* first, T* last, T* dest) {
        uint32_t pad[4];
        UninitCopyImpl(o, first, last, dest, *t);
    }
    void Destruct(T* first) { for (; first < mpEnd; ++first) {} }

    // Elem7c only: element-wise copy assignment
    static T* Copy(T* first, T* last, T* dest) {
        TagA ta = TagA(); TagB tag2 = TagB(); TagC c = TagC();
        return CopyImpl(first, last, dest);
    }
    static T* Copy2(T* first, T* last, T* dest) {
        TagA ta = TagA(); TagB tag2 = TagB(); TagC c = TagC(); PadN<2>();
        return CopyImpl(first, last, dest);
    }
    static T* CopyImpl(T* first, T* last, T* dest) {
        for (; first != last; ++dest, ++first) *dest = *first;
        return dest;
    }
};

// @ 0x0041F270
template <> Vec<Elem7c>::~Vec() { uint32_t s1[5]; Destroy(mpBegin, mpEnd); DoFree(); }

// @ 0x0041F650
template <> void Vec<Elem7c>::push_back(const Elem7c& v) {
    if (mpEnd < mpCapacity) { new (mpEnd++) Elem7c(v); PadN<18>(); }
    else DoInsertValue(mpEnd, v);
}

// @ 0x0041F760
template <> Vec<Elem20>::~Vec() { Destroy(mpBegin, mpEnd); DoFree(); }

// @ 0x0041F7D0
template <> void Vec<Elem20>::push_back(const Elem20& v) {
    if (mpEnd < mpCapacity) { new (mpEnd++) Elem20(v); PadN<1>(); }
    else DoInsertValue(mpEnd, v);
}

// @ 0x0041F6C0
template <> Vec<Elem20>::Vec(const Vec& o) {
    size_t n = o.mpEnd - o.mpBegin;
    uint32_t s[13];
    mpBegin = DoAllocate(n);
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
    mpEnd = UninitCopy(o.mpBegin, o.mpEnd, mpBegin);
}

// @ 0x0041F840
template <> Vec<Elem8c>::Vec(const Vec& o) {
    size_t n = o.mpEnd - o.mpBegin;
    uint32_t s[14]; uint32_t s14, s15;
    mpBegin = DoAllocate(n);
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
    mpEnd = UninitCopy(o.mpBegin, o.mpEnd, mpBegin);
}

// @ 0x0041F8E0
template <> Vec<Elem8c>::~Vec() { uint32_t s1[9]; Destroy(mpBegin, mpEnd); DoFree(); }

// @ 0x0041F1E0  vector<RcPtr>::resize(n)
struct VecP {
    RcPtr* mpBegin; RcPtr* mpEnd; RcPtr* mpCapacity; uint32_t alloc;
    void DoInsertValues(RcPtr* pos, size_t n, const RcPtr& v);   // 0x0042A220
    void Erase(RcPtr* first, RcPtr* last);                       // 0x004247F0
    void Insert(RcPtr* pos, size_t n, const RcPtr& v) { DoInsertValues(pos, n, v); }
    void resize(size_t n);
};
void VecP::resize(size_t n) {
    if (n > (size_t)(mpEnd - mpBegin)) {
        RcPtr val;
        Insert(mpEnd, n - (mpEnd - mpBegin), val);
    } else {
        Erase(mpBegin + n, mpEnd);
    }
    PadN<18>();
}

// @ 0x0041EFB0  Vec<Elem16>::operator=
template <> Vec<Elem16>& Vec<Elem16>::operator=(const Vec& x) {
    if (&x != this) {
        size_t n = x.mpEnd - x.mpBegin;
        if (n > (size_t)(mpCapacity - mpBegin)) {
            Elem16* pNew = DoAllocateAndCopy(n, x.mpBegin, x.mpEnd);
            PadN<9>(); Destruct(mpBegin);
            DoFreeRange(mpBegin, mpCapacity - mpBegin);
            mpBegin = pNew;
            mpCapacity = mpBegin + n;
        } else if (n > (size_t)(mpEnd - mpBegin)) {
            CopyElems16(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            UninitCopy16(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
        } else {
            Elem16* pos = CopyElems16(x.mpBegin, x.mpEnd, mpBegin);
            PadN<3>(); Destruct(pos);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x0041F320  Vec<Elem7c>::operator=
template <> Vec<Elem7c>& Vec<Elem7c>::operator=(const Vec& x) {
    if (&x != this) {
        size_t n = x.mpEnd - x.mpBegin;
        if (n > (size_t)(mpCapacity - mpBegin)) {
            Elem7c* pNew = DoAllocateAndCopy(n, x.mpBegin, x.mpEnd);
            PadN<11>();
            Destroy(mpBegin, mpEnd);
            DoFreeRange(mpBegin, mpCapacity - mpBegin);
            mpBegin = pNew;
            mpCapacity = mpBegin + n;
        } else if (n > (size_t)(mpEnd - mpBegin)) {
            Copy2(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            PadN<10>();
            UninitCopy7c(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
        } else {
            Elem7c* pos;
            PadN<2>();
            pos = Copy(x.mpBegin, x.mpEnd, mpBegin);
            PadN<5>();
            Destroy(pos, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}
