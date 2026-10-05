// w1g1 slice s0050d750 -- /Od EASTL vector machinery (element strides 8, 0xc, 0x14,
// 0x18 and 0x64) plus two 2-float helpers and an int unique.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE  (no C++ EH)
#include "types.h"

template <int N> inline void ScratchSlots() { unsigned int s[N]; }
template <int N> inline void ScratchPad() { unsigned int scratch[N]; }
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

void* EASTL_Allocate(void* alloc, unsigned int n, unsigned int align, unsigned int offset);  // 0x0042dee0
void EASTL_allocator_deallocate(void* p);                                                    // 0x00f47380
inline void DeleteElemConditional(void* p, int flags)
{
    if (flags & 1)
        EASTL_allocator_deallocate(p);
}

// ---------------------------------------------------------------------------
// eastl::copy (the range copies below carry the three selector bools)
// ---------------------------------------------------------------------------
template <class In, class Out>
inline Out CopyImpl(In first, In last, Out dest)
{
    for (; first != last; ++dest, ++first)
        *dest = *first;
    return dest;
}
template <class In, class Out>
inline Out Copy(In first, In last, Out result)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return CopyImpl(first, last, result);
}

template <class T>
inline void Destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}

// ---------------------------------------------------------------------------
// 2-float helpers
// ---------------------------------------------------------------------------
struct V2 { float x, y; V2() {} V2(float a, float b) : x(a), y(b) {} };

// @ 0x0050e190  out = { a.x * b.x, a.y * b.x }
V2* Mul2(V2* out, const V2* a, const V2* b)
{
    V2 r(a->x * b->x, a->y * b->x);
    out->x = r.x;
    out->y = r.y;
    return out;
}

// @ 0x0050e570  out += a
V2* AddTo2(V2* out, const V2* a)
{
    V2 r;
    r.x = out->x + a->x;
    r.y = out->y + a->y;
    out->x = r.x;
    out->y = r.y;
    return out;
}

// ---------------------------------------------------------------------------
// eastl::unique / adjacent_find over int
// ---------------------------------------------------------------------------
inline int* AdjacentFind(int* first, int* last)
{
    if (first != last) {
        int* i = first;
        for (++i; i != last; ++i) {
            if (*first == *i)
                return first;
            first = i;
        }
    }
    return last;
}

// @ 0x0050e4b0
int* Unique(int* first, int* last)
{
    first = AdjacentFind(first, last);
    if (first != last) {
        int* dest(first);
        for (++first; first != last; ++first) {
            if (!(*dest == *first))
                *++dest = *first;
        }
        return ++dest;
    }
    return last;
}

// ---------------------------------------------------------------------------
// vector<pair<int,int>>  (stride 8)
// ---------------------------------------------------------------------------
struct P2 { int first; int second; };

struct Vec8 {
    P2* mpBegin;      // 0x00
    P2* mpEnd;        // 0x04
    P2* mpCapacity;   // 0x08
    uint32_t mAlloc;  // 0x0c

    P2* AllocCopy(uint32_t n, const P2* first, const P2* last);   // 0x0056a0e0
    void DoInsertValues(P2* position, uint32_t n, const P2& value);  // 0x004cef00
    void insert(P2* position, uint32_t n, const P2& value) { ScratchPad<6>(); DoInsertValues(position, n, value); }
    void EraseRange(P2* first, P2* last);                            // 0x00530c80

    Vec8& operator=(const Vec8& x);
    P2* erase(P2* position);
    void resize(uint32_t n);
};

P2* __cdecl UninitCopy8(P2* first, P2* last, P2* dest);   // 0x004d0960

inline void DoFree8(P2* p)
{
    if (p && ((uint32_t*)p)[-1]) {
        void* q = p;
        EASTL_allocator_deallocate(q);
    }
}

// @ 0x0050d750
Vec8& Vec8::operator=(const Vec8& x)
{
    if (this != &x) {
        uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
        if ((uint32_t)(mpCapacity - mpBegin) < n) {
            P2* const pNewData = AllocCopy(n, x.mpBegin, x.mpEnd);
            for (P2* p = mpBegin; p < mpEnd; ++p) {}
            DoFree8(mpBegin);
            mpBegin = pNewData;
            mpCapacity = mpBegin + n;
        } else if ((uint32_t)(mpEnd - mpBegin) < n) {
            Copy(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            UninitCopy8(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
        } else {
            Copy(x.mpBegin, x.mpEnd, mpBegin);
            for (P2* p = mpBegin + n; p < mpEnd; ++p) {}
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x0050e200
P2* Vec8::erase(P2* position)
{
    if (position + 1 < mpEnd)
        Copy(position + 1, mpEnd, position);
    --mpEnd;
    return position;
}

// @ 0x0050da10
void Vec8::resize(uint32_t n)
{
    if (n > (uint32_t)(mpEnd - mpBegin)) {
        insert(mpEnd, n - (uint32_t)(mpEnd - mpBegin), P2());
    } else {
        EraseRange(mpBegin + n, mpEnd);
    }
}

// ---------------------------------------------------------------------------
// vector<T12>  (stride 0xc)
// ---------------------------------------------------------------------------
struct T12 { uint32_t a, b, c; };

struct Vec12 {
    T12* mpBegin;
    T12* mpEnd;
    T12* mpCapacity;
    uint32_t mAlloc;

    T12* AllocCopy(uint32_t n, const T12* first, const T12* last);   // 0x0056a140
    Vec12& operator=(const Vec12& x);
};

T12* __cdecl UninitCopy12(T12* first, T12* last, T12* dest);   // 0x0050eb40

inline void DoFree12(T12* p)
{
    if (p && ((uint32_t*)p)[-1]) {
        void* q = p;
        EASTL_allocator_deallocate(q);
    }
}

// @ 0x0050dea0
Vec12& Vec12::operator=(const Vec12& x)
{
    if (this != &x) {
        uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
        if ((uint32_t)(mpCapacity - mpBegin) < n) {
            T12* const pNewData = AllocCopy(n, x.mpBegin, x.mpEnd);
            for (T12* p = mpBegin; p < mpEnd; ++p) {}
            DoFree12(mpBegin);
            mpBegin = pNewData;
            mpCapacity = mpBegin + n;
        } else if ((uint32_t)(mpEnd - mpBegin) < n) {
            Copy(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            UninitCopy12(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
        } else {
            Copy(x.mpBegin, x.mpEnd, mpBegin);
            for (T12* p = mpBegin + n; p < mpEnd; ++p) {}
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// ---------------------------------------------------------------------------
// vector<T20>  (stride 0x14)
// ---------------------------------------------------------------------------
struct T20 { uint32_t a[5]; };

struct Vec20 {
    T20* mpBegin;
    T20* mpEnd;
    T20* mpCapacity;
    uint32_t mAlloc;

    T20* AllocCopy(uint32_t n, const T20* first, const T20* last);   // 0x0050eab0
    Vec20(const Vec20& x);
    Vec20& operator=(const Vec20& x);
};

void __cdecl UninitCopy20(void** out, T20* first, T20* last, T20* dest, uint8_t tag);  // 0x0050f7f0

inline void DoFree20(T20* p)
{
    if (p && ((uint32_t*)p)[-1]) {
        void* q = p;
        EASTL_allocator_deallocate(q);
    }
}

// @ 0x0050da90
Vec20::Vec20(const Vec20& x)
{
    uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
    mpBegin = n ? (T20*)EASTL_Allocate(&mAlloc, n * sizeof(T20), 4, 0) : 0;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
    void* pResult;
    UninitCopy20(&pResult, x.mpBegin, x.mpEnd, mpBegin, (uint8_t)0);
    mpEnd = (T20*)pResult;
}

// @ 0x0050db60
Vec20& Vec20::operator=(const Vec20& x)
{
    if (this != &x) {
        uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
        if ((uint32_t)(mpCapacity - mpBegin) < n) {
            T20* const pNewData = AllocCopy(n, x.mpBegin, x.mpEnd);
            for (T20* p = mpBegin; p < mpEnd; ++p) {}
            DoFree20(mpBegin);
            mpBegin = pNewData;
            mpCapacity = mpBegin + n;
        } else if ((uint32_t)(mpEnd - mpBegin) < n) {
            Copy(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            void* pResult;
            UninitCopy20(&pResult, x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd, (uint8_t)0);
        } else {
            Copy(x.mpBegin, x.mpEnd, mpBegin);
            for (T20* p = mpBegin + n; p < mpEnd; ++p) {}
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// ---------------------------------------------------------------------------
// vector<T24>  (stride 0x18)
// ---------------------------------------------------------------------------
struct T24 { uint32_t a[6]; };

struct Vec24 {
    T24* mpBegin;
    T24* mpEnd;
    T24* mpCapacity;
    uint32_t mAlloc;

    T24* erase(T24* first, T24* last);
};

// @ 0x0050e690
T24* Vec24::erase(T24* first, T24* last)
{
    T24* const position = Copy(last, mpEnd, first);
    Destruct(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// ---------------------------------------------------------------------------
// vector<Elem100>  (stride 0x64)
// ---------------------------------------------------------------------------
struct FixedVec {
    uint32_t* mpBegin;    // 0x00
    uint32_t* mpEnd;      // 0x04
    uint32_t* mpCapacity; // 0x08
    uint32_t mAlloc[3];   // 0x0c
    uint32_t mBuf[16];    // 0x18
    void Destroy();       // 0x004c0b80
    __forceinline ~FixedVec()
    {
        for (uint32_t* q = mpBegin; q < mpEnd; ++q) {}
        Destroy();
        DeleteElemConditional(this, 0);
    }
};

struct Base100 {
    FixedVec vec;         // 0x00
    Base100();            // 0x0041cfe0
    Base100(const Base100&);  // 0x0050e5f0
};

struct Elem100 : Base100 {
    float f58, f5c, f60;  // 0x58
    Elem100() : f58(0), f5c(0), f60(0) {}
    Elem100(const Elem100& x) : Base100(x), f58(x.f58), f5c(x.f5c), f60(x.f60) { ScratchSlots<6>(); }
    ~Elem100() { ScratchSlots<6>(); }
};

struct VecBase {
    Elem100* mpBegin;
    Elem100* mpEnd;
    Elem100* mpCapacity;
    uint32_t mAlloc;
    ~VecBase();           // 0x0050f070
};

struct Vec100 : VecBase {
    void DoInsertValues(Elem100* position, uint32_t n, const Elem100& value);  // 0x0050fc30
    void EraseRange(Elem100* first, Elem100* last);                            // 0x0050eca0
    void DoInsertValue(Elem100* position, const Elem100& value);               // 0x0050ed90

    ~Vec100();
    void resize(uint32_t n);
    void push_back(const Elem100& value);
};

// @ 0x0050e290
Vec100::~Vec100()
{
    ScratchSlots<6>();
    for (Elem100* p = mpBegin; p < mpEnd; ++p) {
        FixedVec& v = p->vec;
        for (uint32_t* q = v.mpBegin; q < v.mpEnd; ++q) {}
        v.Destroy();
        DeleteElemConditional(p, 0);
    }
}

// @ 0x0050e310
void Vec100::resize(uint32_t n)
{
    if (n > (uint32_t)(mpEnd - mpBegin)) {
        Elem100 value;
        DoInsertValues(mpEnd, n - (uint32_t)(mpEnd - mpBegin), value);
    } else {
        EraseRange(mpBegin + n, mpEnd);
    }
}

// @ 0x0050e410
void Vec100::push_back(const Elem100& value)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) Elem100(value);
    else
        DoInsertValue(mpEnd, value);
}
