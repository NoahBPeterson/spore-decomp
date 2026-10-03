#include "types.h"

// Slice s0041e730: EASTL-style vector internals and Property value getters (unoptimized module).
//   0x0041E730  Vec24::~Vec24            (vector of 24-byte records, destruct loop is empty, then base dtor)
//   0x0041E770  Vec24::reserve           (not byte-exact: dead-slot layout of the nested inlines)
//   0x0041E8B0  Vec24::push_back
//   0x0041E920  Property::GetBool, 0x0041E990 GetInt, 0x0041EA00 GetUInt, 0x0041EA70 GetFloat
//   0x0041EAE0  RefVector::RefVector(const RefVector&)   (vector of intrusive refs to ThreadedObject)
//   0x0041EB80  RefVector::~RefVector
//   0x0041EBE0  RefVector::operator=     (not byte-exact: dead-slot layout)
//   0x0041EE90  RefVector::resize
//   0x0041EF20  RefVector::push_back
// Flags: /Od /Ob1 /MD /Gy /TP.
//
// /Od notes:
//  - Locals of an inline function are allocated before its parameter temporaries; locals of an
//    inline function expanded *later* sit below earlier expansions. Unused `uN` ints and
//    parameterless pad helpers (tail(), InsertBack(), er()) reproduce dead slots at the right
//    depth. The unused ints are stand-ins for compiled-out debug locals, not recovered names.
//  - Property getters: `if (a) { return x; } else if (b) return this; return 0;` inside an
//    inline helper yields the dead `jmp` after the first branch.

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedIncrement)

void __cdecl EASTL_allocator_deallocate(void* p);                                  // 0x00f47380
inline void* operator new(unsigned int, void* p) { return p; }

struct Alloc { int unused; };
void* __cdecl AllocatorAllocate(Alloc* a, unsigned size, unsigned align, unsigned off);   // 0x0042dee0

// ---------------------------------------------------------------- vector of 24-byte records
struct Elem24 {
    unsigned d[6];
    Elem24(const Elem24& o);                                                       // 0x00511140
};
Elem24* __cdecl UninitMove24(Elem24* first, Elem24* last, Elem24* dest);           // 0x00512000

struct Vec24Base {
    Elem24* mpBegin; Elem24* mpEnd; Elem24* mpCap; Alloc alloc;
    ~Vec24Base();                                                                  // 0x004fd940
};
struct Vec24 : Vec24Base {
    ~Vec24();
    void DoInsertValue(Elem24* pos, const Elem24& v);                              // 0x00424010
    void InsertBack(const Elem24& v) { int u0, u1; DoInsertValue(mpEnd, v); }
    void reserve(unsigned n);
    void push_back(const Elem24& v);
};

// @ 0x0041e730
Vec24::~Vec24()
{
    Elem24* p = mpBegin; int a, b, c;
    for (; p < mpEnd; ++p) {}
}

inline void MoveAndDestroy(Elem24* first, Elem24* last, Elem24* dest)
{
    Elem24* r; bool b = false; int u0, u1, u2; bool b2 = false; Elem24* f; Elem24* d;
    r = UninitMove24(first, last, dest);
    d = dest; f = first; for (; f != last; ++f, ++d) {}
}
inline void dealloc24(Elem24* p, unsigned n)
{
    if (((int*)p)[-1]) { Elem24* q = p; EASTL_allocator_deallocate(q); }
}
inline void free24(Elem24* p, unsigned n) { if (p) dealloc24(p, n); }

// @ 0x0041e770  (nonmatching: slot layout)
void Vec24::reserve(unsigned n)
{
    if (n > (unsigned)(mpCap - mpBegin)) {
        Elem24* pNewData = n ? (Elem24*)AllocatorAllocate(&alloc, n * 0x18, 4, 0) : 0;
        MoveAndDestroy(mpBegin, mpEnd, pNewData);
        free24(mpBegin, mpCap - mpBegin);
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCap = mpBegin + n;
    }
}

// @ 0x0041e8b0
void Vec24::push_back(const Elem24& v)
{
    if (mpEnd < mpCap) {
        ::new((void*)mpEnd++) Elem24(v);
    } else InsertBack(v);
}

// ---------------------------------------------------------------- Property getters
extern bool g_defaultBool;       // 0x015d115d
extern int g_defaultInt;         // 0x015d1160
extern unsigned g_defaultUInt;   // 0x015d1164
extern float g_defaultFloat;     // 0x015d1168

struct Property {
    char* data; unsigned pad[3]; unsigned short flags; unsigned short type;   // flags 0x10, type 0x12
    void* GetStorage() { if (flags & 0x30) { return data; } else if (type) return this; return 0; }
    bool* GetBool();
    int* GetInt();
    unsigned* GetUInt();
    float* GetFloat();
};
// @ 0x0041e920
bool* Property::GetBool()
{
    if (type == 1 || type == 0x10) { return (bool*)GetStorage(); }
    return &g_defaultBool;
}
// @ 0x0041e990
int* Property::GetInt()
{
    if (type == 9 || type == 0x10) { return (int*)GetStorage(); }
    return &g_defaultInt;
}
// @ 0x0041ea00
unsigned* Property::GetUInt()
{
    if (type == 10 || type == 0x10) { return (unsigned*)GetStorage(); }
    return &g_defaultUInt;
}
// @ 0x0041ea70
float* Property::GetFloat()
{
    if (type == 13 || type == 0x10) { return (float*)GetStorage(); }
    return &g_defaultFloat;
}

// ---------------------------------------------------------------- vector of intrusive refs
struct ThreadedObject {
    void* vtable; volatile long mnRefCount;
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release();                                                                // 0x00404f90
};
struct Ref {
    ThreadedObject* p;
    Ref(const Ref& o) : p(o.p) { if (p) p->AddRef(); }
    ~Ref() { if (p) p->Release(); }
};
Ref* __cdecl CopyRefs(Ref* first, Ref* last, Ref* dest);          // 0x0042d4a0
Ref* __cdecl UninitCopyRefs(Ref* first, Ref* last, Ref* dest);    // 0x00423f50

struct RefVectorBase {
    Ref* mpBegin; Ref* mpEnd; Ref* mpCap; Alloc alloc;
    ~RefVectorBase();                                                              // 0x00425990
};
struct RefVector : RefVectorBase {
    Ref* DoAllocateAndCopy(unsigned n, Ref* first, Ref* last);                     // 0x00423ef0
    void DoInsertValue(Ref* pos, const Ref& v);                                    // 0x00424430
    void DoInsertN(Ref* pos, unsigned n, Ref* val);                                // 0x00429e00
    void DoErase(Ref* first, Ref* last);                                           // 0x00426280
    Ref* DoAllocate(unsigned n) {
        int u0, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11, u12;
        return n ? (Ref*)AllocatorAllocate(&alloc, n * 4, 4, 0) : 0;
    }
    void ins(Ref* pos, unsigned n, Ref* val) { DoInsertN(pos, n, val); }
    void er(unsigned n) {
        int u0, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11, u12, u13, u14, u15, u16, u17;
        DoErase(mpBegin + n, mpEnd);
    }
    void tail() { int x, y, z; }
    RefVector(const RefVector& o);
    ~RefVector();
    RefVector& operator=(const RefVector& x);
    void resize(unsigned n);
    void push_back(const Ref& v);
};

// @ 0x0041eae0
RefVector::RefVector(const RefVector& o)
{
    int n = o.mpEnd - o.mpBegin;
    mpBegin = DoAllocate(n);
    mpEnd = mpBegin;
    mpCap = mpBegin + n;
    mpEnd = UninitCopyRefs(o.mpBegin, o.mpEnd, mpBegin);
}

inline void destructRefs(Ref* first, Ref* last) { int a, b, c; for (; first < last; ++first) first->~Ref(); }

// @ 0x0041eb80
RefVector::~RefVector()
{
    destructRefs(mpBegin, mpEnd);
    tail();
}

inline void dealloc(Ref* p, unsigned n) { if (((int*)p)[-1]) { Ref* q = p; EASTL_allocator_deallocate(q); } }
inline void freeRefs(Ref* p, unsigned n) { if (p) dealloc(p, n); }
inline void pad9() { int u0, u1, u2, u3, u4, u5, u6, u7, u8; }
inline Ref* copyW(Ref* first, Ref* last, Ref* dest) { bool t1 = false; bool t2 = false; int w[4]; return CopyRefs(first, last, dest); }
inline Ref* copyW3(Ref* first, Ref* last, Ref* dest) { bool t1 = false; bool t2 = false; int w[8]; return CopyRefs(first, last, dest); }

// @ 0x0041ebe0  (nonmatching: slot layout)
RefVector& RefVector::operator=(const RefVector& x)
{
    if (&x != this) {
        const unsigned n = (unsigned)(x.mpEnd - x.mpBegin);
        if (n > (unsigned)(mpCap - mpBegin)) {
            Ref* pNewData = DoAllocateAndCopy(n, x.mpBegin, x.mpEnd);
            pad9();
            destructRefs(mpBegin, mpEnd);
            freeRefs(mpBegin, mpCap - mpBegin);
            mpBegin = pNewData;
            mpCap = mpBegin + n;
        } else if (n > (unsigned)(mpEnd - mpBegin)) {
            copyW(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            UninitCopyRefs(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
        } else {
            Ref* pNewEnd = copyW3(x.mpBegin, x.mpEnd, mpBegin);
            destructRefs(pNewEnd, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x0041ee90
void RefVector::resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin)) {
        ThreadedObject* val = 0;
        ins(mpEnd, n - (unsigned)(mpEnd - mpBegin), (Ref*)&val);
        if (val) val->Release();
    } else er(n);
}

// @ 0x0041ef20
void RefVector::push_back(const Ref& v)
{
    if (mpEnd < mpCap) {
        ::new((void*)mpEnd++) Ref(v);
    } else DoInsertValue(mpEnd, v);
}
