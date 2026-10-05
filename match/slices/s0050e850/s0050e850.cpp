// w1g1 slice s0050e850 -- /Od EASTL internals for the same TU as s0050d750:
// a 3-byte FNV-style word hash, an open-addressed 12-byte-entry slot finder,
// vector<T20>/<T12>/<Elem100> allocate+copy/erase/resize helpers, Elem100
// assignment, VectorBase dtor, and sort/quick-sort drivers.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

template <int N> inline void ScratchSlots() { unsigned int s[N]; }
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

void* EASTL_Allocate(void* alloc, unsigned int n, unsigned int align, unsigned int offset);  // 0x0042dee0
void EASTL_allocator_deallocate(void* p);                                                    // 0x00f47380

// ---------------------------------------------------------------------------
// hashing
// ---------------------------------------------------------------------------
// @ 0x0050ea00
uint32_t HashWord(uint32_t x)
{
    uint32_t h = 0x811c9dc5u * 0x1000193u ^ ((const uint8_t*)&x)[2];
    h = h * 0x1000193u ^ ((const uint8_t*)&x)[1];
    h = h * 0x1000193u ^ ((const uint8_t*)&x)[0];
    return h;
}

struct HashEntry { uint32_t mInstance; uint32_t mType; uint32_t mMeta; };

struct HashTable {
    HashEntry* mp;   // +0x00
    uint32_t FindSlot(uint32_t a, uint32_t b);
};

// @ 0x0050e850
uint32_t HashTable::FindSlot(uint32_t a, uint32_t b)
{
    uint32_t h = HashWord(a) * 0x1000193u ^ b;
    uint32_t n = h & 0x7fff;
    if (((uint8_t*)&mp[n])[3] != 0xff) {
        if (!(mp[n].mInstance == a && mp[n].mType == b)) {
            const uint32_t step = (h >> 16 & 0x7fff) | 1;
            uint32_t count = 1;
            do {
                n = (n + step) & 0x7fff;
                ++count;
                if (mp[n].mInstance == a && mp[n].mType == b)
                    return n;
                if (((uint8_t*)&mp[n])[3] == 0xff)
                    return n;
            } while (count < 0x8001);
            n = 0xffffffff;
        }
    }
    return n;
}

// ---------------------------------------------------------------------------
// element types
// ---------------------------------------------------------------------------
struct T12 { uint32_t a, b, c; };
struct T20 { uint32_t a[5]; };

void __cdecl UninitCopy20(void** out, T20* first, T20* last, T20* dest, uint8_t tag);  // 0x0050f7f0

struct Vec20 {
    T20* mpBegin;
    T20* mpEnd;
    T20* mpCapacity;
    uint32_t mAlloc;

    T20* AllocCopy(uint32_t n, const T20* first, const T20* last);
};

// @ 0x0050eab0  (allocate n and uninitialized-copy [first,last))
T20* Vec20::AllocCopy(uint32_t n, const T20* first, const T20* last)
{
    T20* p = n ? (T20*)EASTL_Allocate(&mAlloc, n * sizeof(T20), 4, 0) : 0;
    uint8_t tag;
    UninitCopy20((void**)&p, (T20*)first, (T20*)last, p, tag);
    return p;
}

// @ 0x0050eb40
T12* UninitCopy12(T12* first, T12* last, T12* result)
{
    T12* d = result;
    for (T12* p = first; p != last; ++p) {
        if (d) {
            d->a = p->a;
            d->b = p->b;
            d->c = p->c;
        }
        ++d;
    }
    return d;
}

// ---------------------------------------------------------------------------
// eastl::copy (three selector bools; assignments may call operator=)
// ---------------------------------------------------------------------------
template <class In, class Out>
inline Out CopyImpl(In first, In last, Out dest)
{
    for (; first != last; ++dest, ++first)
        *dest = *first;
    return dest;
}
template <class In, class Out>
inline Out Copy(In first, In last, Out dest)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return CopyImpl(first, last, dest);
}

template <class T>
inline void Destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}// ---------------------------------------------------------------------------
// Vector3 copy ctor (used by 0x18-byte element machinery)
// ---------------------------------------------------------------------------
struct Vector3 { float x, y, z; Vector3() {} Vector3(const Vector3&); };  // 0x004098a0
struct T24 { Vector3 v[2]; };

// ---------------------------------------------------------------------------
// Elem100 / fixed_vector<uint32_t,16> machinery (shared with s0050d750)
// ---------------------------------------------------------------------------
void DwordVector_assign(uint32_t* first, uint32_t* last, uint8_t tag);  // 0x0042c750
void FixedVec_erase(uint32_t* first, uint32_t* last);                   // 0x004769b0

struct FixedVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAlloc[3];
    uint32_t mBuf[16];
    void Destroy();   // 0x004c0b80
    FixedVec& operator=(const FixedVec& o)
    {
        if (this != &o) {
            FixedVec_erase(mpBegin, mpEnd);
            uint8_t tag;
            DwordVector_assign(o.mpBegin, o.mpEnd, tag);
        }
        return *this;
    }
};

struct Base100 {
    FixedVec vec;
    Base100();
    Base100(const Base100&);
};

struct Elem100 : Base100 {
    float f58, f5c, f60;
    Elem100() : f58(0), f5c(0), f60(0) {}
    Elem100& operator=(const Elem100& x);   // 0x0050f210
};

// @ 0x0050f210
Elem100& Elem100::operator=(const Elem100& x)
{
    vec = x.vec;
    f58 = x.f58;
    f5c = x.f5c;
    f60 = x.f60;
    return *this;
}

inline void DeleteElemConditional(void* p, int flags)
{
    if (flags & 1)
        EASTL_allocator_deallocate(p);
}

// @ 0x0050f070
struct VecBase {
    Elem100* mpBegin;
    Elem100* mpEnd;
    Elem100* mpCapacity;
    uint32_t mAlloc;
    Elem100* mFixed;   // +0x10
    ~VecBase();
};

// @ 0x0050f070
VecBase::~VecBase()
{
    if (mpBegin) {
        int q = (int)((char*)mpCapacity - (char*)mpBegin) / (int)sizeof(Elem100) * (int)sizeof(Elem100);
        (void)q;
        Elem100* n = mpBegin;
        if (n != mFixed) {
            void* p = n;
            EASTL_allocator_deallocate(p);
        }
    }
}

void EraseHelper(Elem100* first, Elem100* last);   // 0x0050f210 alias (operator=)
void CopyBackward100(Elem100* first, Elem100* last, Elem100* resultEnd);  // 0x00511d00
Elem100* UninitRelocate100(Elem100* first, Elem100* last, Elem100* dest);  // 0x00511880

struct Vec100 : VecBase {
    Elem100* EraseRange(Elem100* first, Elem100* last);   // 0x0050eca0
    void DoInsertValue(Elem100* position, const Elem100& value);  // 0x0050ed90
    Elem100* DoAllocate(uint32_t n);
};

// @ 0x0050eca0
Elem100* Vec100::EraseRange(Elem100* first, Elem100* last)
{
    Elem100* position = first;
    for (Elem100* i = last; i != mpEnd; ++i, ++position)
        *position = *i;
    Elem100* p = position;
    for (; p < mpEnd; ++p) {
        FixedVec& v = p->vec;
        for (uint32_t* q = v.mpBegin; q < v.mpEnd; ++q) {}
        v.Destroy();
        DeleteElemConditional(p, 0);
    }
    mpEnd -= (last - first);
    return first;
}

// @ 0x0050ed90
void Vec100::DoInsertValue(Elem100* position, const Elem100& value)
{
    if (mpEnd != mpCapacity) {
        const Elem100* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) Elem100(*(mpEnd - 1));
        CopyBackward100(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        Elem100* const pNewData = (Elem100*)EASTL_Allocate(&mAlloc, nNewSize * sizeof(Elem100), 4, 0);
        Elem100* pNewEnd = UninitRelocate100(mpBegin, position, pNewData);
        ::new (pNewEnd) Elem100(value);
        pNewEnd = UninitRelocate100(position, mpEnd, ++pNewEnd);
        if (mpBegin && mpBegin != mFixed) {
            void* q = mpBegin;
            EASTL_allocator_deallocate(q);
        }
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------------------
// vector<T12>::erase
// ---------------------------------------------------------------------------
struct Vec12 {
    T12* mpBegin;
    T12* mpEnd;
    T12* mpCapacity;
    uint32_t mAlloc;

    T12* erase(T12* first, T12* last);
};

// @ 0x0050f740
T12* Vec12::erase(T12* first, T12* last)
{
    T12* const position = Copy(last, mpEnd, first);
    Destruct(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// ---------------------------------------------------------------------------
// @ 0x0050f7f0  uninitialized_copy (result via out-param) for T20
// ---------------------------------------------------------------------------
void __cdecl UninitCopy20(void** out, T20* first, T20* last, T20* dest, uint8_t tag)
{
    (void)tag;
    T20* d = dest;
    for (T20* p = first; p != last; ++p, ++d) {
        if (d) {
            for (int i = 0; i < 5; ++i)
                ((uint32_t*)d)[i] = ((uint32_t*)p)[i];
        }
    }
    *out = d;
}

// ---------------------------------------------------------------------------
// sort drivers
// ---------------------------------------------------------------------------
void QuickSort0E(int* first, int* last, int n, uint8_t cmp);   // 0x0050f950
void QuickSort1E(int* first, int* last, int n, uint8_t cmp);   // 0x005100c0
void InsertionSortA(int* first, int* last, uint8_t cmp);       // 0x0050fa10
void InsertionSortB(int* first, int* last, uint8_t cmp);       // 0x0050fb30
void InsertionSortC(int* first, int* last);                    // 0x00510240
void InsertionSortD(int* first, int* last);                    // 0x005102d0

// @ 0x0050ebe0  eastl::sort with compare functor (1-byte, passed by value)
void SortCmp(int* first, int* last, uint8_t cmp)
{
    if (first != last) {
        int i = 0;
        for (int n = (int)((last - first) >> 2); n != 0; n >>= 1)
            ++i;
        QuickSort0E(first, last, i * 2 - 2, cmp);
        if ((int)((last - first) >> 2) < 0x1d) {
            InsertionSortA(first, last, cmp);
        } else {
            InsertionSortA(first, first + 0x1c, cmp);
            InsertionSortB(first + 0x1c, last, cmp);
        }
    }
}

// @ 0x0050f0d0  eastl::sort with default less
void SortDefault(int* first, int* last)
{
    if (first != last) {
        int i = 0;
        for (int n = (int)((last - first) >> 2); n != 0; n >>= 1)
            ++i;
        QuickSort1E(first, last, i * 2 - 2, 0);
        if ((int)((last - first) >> 2) < 0x1d) {
            InsertionSortC(first, last);
        } else {
            InsertionSortC(first, first + 0x1c);
            InsertionSortD(first + 0x1c, last);
        }
    }
}

// ---------------------------------------------------------------------------
// vector<T24>::DoInsertValues  (0x18-byte elements with Vector3 members)
// ---------------------------------------------------------------------------
// @ 0x0050f290
struct Vec24Full {
    T24* mpBegin;
    T24* mpEnd;
    T24* mpCapacity;
    uint32_t mAlloc;

    void DoInsertValues(T24* position, uint32_t n, const T24& value);
};

T24* UninitCopy24(T24* first, T24* last, T24* dest)
{
    T24* d = dest;
    for (; first != last; ++first, ++d)
        ::new (d) T24(*first);
    return d;
}

void UninitFillN24(T24* first, uint32_t n, const T24& value)
{
    for (; n > 0; --n, ++first)
        ::new (first) T24(value);
}

void CopyBackward24(T24* first, T24* last, T24* resultEnd)
{
    while (last != first) {
        --last;
        --resultEnd;
        *resultEnd = *last;
    }
}

void Fill24(T24* first, T24* last, const T24& value)
{
    for (; first != last; ++first)
        *first = value;
}

void Vec24Full::DoInsertValues(T24* position, uint32_t n, const T24& value)
{
    if ((uint32_t)(mpCapacity - mpEnd) < n) {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const uint32_t nNewSize = (nPrevSize + n < nGrowSize) ? nGrowSize : (nPrevSize + n);
        T24* const pNewData = nNewSize ? (T24*)EASTL_Allocate(&mAlloc, nNewSize * sizeof(T24), 4, 0) : 0;
        T24* pNewEnd = UninitCopy24(mpBegin, position, pNewData);
        UninitFillN24(pNewEnd, n, value);
        pNewEnd = UninitCopy24(position, mpEnd, pNewEnd + n);
        for (T24* p = mpBegin; p < mpEnd; ++p) {}
        if (mpBegin && ((uint32_t*)mpBegin)[-1]) {
            void* q = mpBegin;
            EASTL_allocator_deallocate(q);
        }
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    } else if (n != 0) {
        const T24 valueSaved(value);
        const uint32_t nExtra = (uint32_t)(mpEnd - position);
        if (n < nExtra) {
            UninitCopy24(mpEnd - n, mpEnd, mpEnd);
            T24* const pEnd = mpEnd;
            mpEnd += n;
            CopyBackward24(position, pEnd - n, pEnd);
            Fill24(position, position + n, valueSaved);
        } else {
            UninitFillN24(mpEnd, n - nExtra, valueSaved);
            T24* const pEnd = mpEnd;
            mpEnd += n - nExtra;
            UninitCopy24(position, pEnd, mpEnd);
            mpEnd += nExtra;
            Fill24(position, pEnd, valueSaved);
        }
    }
}
