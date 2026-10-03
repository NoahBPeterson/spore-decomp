// Small math helpers and EASTL-style vector internals (unoptimized module: /Od /Ob1 /arch:SSE).
#include "types.h"
#include <stdarg.h>

inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

// ---- external functions ----
bool __cdecl PtrEqual(const void* a, const void* b);                     // FUN_00423250
void __cdecl CopyRange(void* a, void* b, void* c);                       // FUN_00423320
void __cdecl FreeBlock(void* p);                                         // EASTL_allocator_deallocate
void* __cdecl AllocBlock(void* allocator, uint32_t size, uint32_t align, uint32_t offset); // FUN_0042dee0
void __cdecl CopyFloats3(void* first, void* last, void* dest);           // FUN_0050f8b0

struct Matrix3 {
    float m[3][3];
    float* operator[](int i) { return m[i]; }
};
struct Mat3Target { void Set(const float* m); };                         // FUN_0041cb40


// @ 0x0041dd90
bool __cdecl NotEqual(const void* a, const void* b)
{
    return !PtrEqual(a, b);
}

// @ 0x0041ddb0
Vector3* __cdecl Vector3_Add(Vector3* a, const Vector3* b)
{
    Vector3 t;
    t.x = a->x + b->x;
    t.y = a->y + b->y;
    t.z = a->z + b->z;
    *a = t;
    return a;
}

// @ 0x0041de20
void* __cdecl CopyRangeRet(void* dst, void* a, void* b)
{
    CopyRange(dst, a, b);
    return dst;
}

// @ 0x0041de40
Vector3* __cdecl Vector3_Scale(Vector3* out, const float* s, const Vector3* v)
{
    *out = Vector3(v->x * *s, v->y * *s, v->z * *s);
    return out;
}

// @ 0x0041ded0
Mat3Target* __cdecl Matrix3_Transposed(Mat3Target* out, const Matrix3* src)
{
    Matrix3 m;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            float* row;
            float t;
            t = src->m[j][i];
            row = m.m[i];
            row[j] = t;
        }
    { uint32_t unused[11]; }
    out->Set(m.m[0]);
    return out;
}

struct WStr {
    const wchar_t* mBegin;
    const wchar_t* mEnd;
    uint32_t mCap;
    WStr(const wchar_t* s, int unused);
    void Assign(const wchar_t* b, const wchar_t* e);        // 0x00423820
    int rfind(wchar_t c, uint32_t pos);
    void AppendVPrintf(const wchar_t* fmt, va_list args);   // 0x004234b0
};
const wchar_t* __cdecl FindLast(const wchar_t* end, const wchar_t* begin, wchar_t c);     // 0x00423890

// @ 0x0041df50
WStr::WStr(const wchar_t* s, int unused)
{
    mBegin = 0;
    mEnd = 0;
    mCap = 0;
    const wchar_t* p = s;
    while (*p) ++p;
    Assign(s, s + (p - s));
}

template <class T> inline const T& Min(const T& a, const T& b) { return a < b ? a : b; }

// @ 0x0041dfc0
int WStr::rfind(wchar_t c, uint32_t pos)
{
    uint32_t n = mEnd - mBegin;
    if (n) {
        uint32_t last = n - 1;
        const uint32_t* m = (pos < last) ? &pos : &last;
        const wchar_t* p = mBegin + (*m + 1);
        const wchar_t* res = FindLast(p, mBegin, c);
        if (res != mBegin)
            return (res - 1) - mBegin;
    }
    return -1;
}

// @ 0x0041e050
WStr* __cdecl WStr_Format(WStr* s, const wchar_t* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    s->mEnd = s->mBegin;
    s->AppendVPrintf(fmt, args);
    va_end(args);
    return s;
}

// Stack-frame filler. The original frames reserve slots for locals of inlined helpers whose
// code was optimized away even at /Od; an unused local in an inlined helper reproduces them.
template <int N> inline void ScratchSlots() { uint32_t slots[N]; }

// ---- vector internals ----
struct Counted { void Release(); };                                      // 0x0040f360

// Transform: 0x38-byte element
struct Transform {
    uint32_t f[14];
    Transform();                                // 0x00409930
    Transform(const Transform&) throw();        // 0x0040ce80
    Transform& operator=(const Transform&);     // 0x00537dc0
};

Transform* __cdecl UninitCopy(const Transform* first, const Transform* last, Transform* dest);   // 0x0042e510

struct TransformVec {
    Transform* mBegin;
    Transform* mEnd;
    Transform* mCap;
    Transform* DoAllocateAndCopy(uint32_t n, const Transform* first, const Transform* last);   // 0x0042e4b0
    void DoInsertValue(Transform* pos, const Transform& v);      // 0x00423960
    void DoInsertFill(Transform* pos, uint32_t n, const Transform& v);   // 0x004298f0
    void erase(Transform* first, Transform* last);               // 0x004238c0
    void Free();                                                 // 0x00427440

    static void DoFree(Transform* p, uint32_t n)
    {
        if (p) {
            if (((int*)p)[-1]) {
                void* q = p;
                FreeBlock(q);
            }
        }
    }
    static Transform* DoCopy(const Transform* first, const Transform* last, Transform* dest)
    {
        bool b0 = false, b1 = false, b2 = false;
        Transform* d = dest;
        const Transform* f = first;
        for (; f != last; ++f, ++d)
            *d = *f;
        return d;
    }

    void clearDtors();
    TransformVec& assign(const TransformVec& x);
    void resize(uint32_t n);
    void insertN(Transform* pos, uint32_t n, const Transform& v) { DoInsertFill(pos, n, v); }
    void push_back(const Transform& v);
};

// @ 0x0041e090
void TransformVec::clearDtors()
{
    for (Transform* p = mBegin; p < mEnd; ++p) { }
    { uint32_t u[3]; }
    Free();
}

// @ 0x0041e0d0
TransformVec& TransformVec::assign(const TransformVec& x)
{
    if (&x != this) {
        uint32_t n = x.mEnd - x.mBegin;
        if (n > (uint32_t)(mCap - mBegin)) {
            Transform* pNew = DoAllocateAndCopy(n, x.mBegin, x.mEnd);
            ScratchSlots<9>();
            for (Transform* p = mBegin; p < mEnd; ++p) { }
            DoFree(mBegin, mCap - mBegin);
            mBegin = pNew;
            mCap = mBegin + n;
        } else if (n > (uint32_t)(mEnd - mBegin)) {
            DoCopy(x.mBegin, x.mBegin + (mEnd - mBegin), mBegin);
            UninitCopy(x.mBegin + (mEnd - mBegin), x.mEnd, mEnd);
            ScratchSlots<11>();
        } else {
            Transform* res = DoCopy(x.mBegin, x.mEnd, mBegin);
            for (Transform* q = res; q < mEnd; ++q) { }
        }
        mEnd = mBegin + n;
    }
    return *this;
}

// @ 0x0041e3b0
void TransformVec::resize(uint32_t n)
{
    if (n > (uint32_t)(mEnd - mBegin)) {
        ScratchSlots<11>();
        insertN(mEnd, n - (mEnd - mBegin), Transform());
        ScratchSlots<6>();
    } else
        erase(mBegin + n, mEnd);
}

// @ 0x0041e460
void TransformVec::push_back(const Transform& v)
{
    if (mEnd < mCap) {
        ::new(mEnd++) Transform(v);
        ScratchSlots<14>();
    } else {
        DoInsertValue(mEnd, v);
    }
}

// Reserve for a vector of 12-byte elements (allocator at +0xc).
struct Vec3Vec {
    Vector3* mBegin;
    Vector3* mEnd;
    Vector3* mCap;
    uint32_t mAlloc;

    Vector3* DoAllocate(uint32_t n)
    {
        return n ? (Vector3*)AllocBlock(&mAlloc, n * sizeof(Vector3), 4, 0) : 0;
    }
    static void DoFree(Vector3* p, uint32_t n)
    {
        if (p) {
            if (((int*)p)[-1]) {
                void* q = p;
                FreeBlock(q);
            }
        }
    }
    void reserve(uint32_t n);
};

// @ 0x0041e4d0
void Vec3Vec::reserve(uint32_t n)
{
    if (n > (uint32_t)(mCap - mBegin)) {
        Vector3* newBegin = DoAllocate(n);
        CopyFloats3(mBegin, mEnd, newBegin);
        { uint32_t pad[8]; }
        DoFree(mBegin, mCap - mBegin);
        uint32_t prevSize = mEnd - mBegin;
        mBegin = newBegin;
        mEnd = newBegin + prevSize;
        mCap = mBegin + n;
    }
}

// Vector of bytes: destructor.
struct ByteVec {
    uint8_t* mBegin;
    uint8_t* mEnd;
    uint8_t* mCap;
    static void DoFree(uint8_t* p, uint32_t n)
    {
        if (((int*)p)[-1]) {
            void* q = p;
            FreeBlock(q);
        }
    }
    ~ByteVec();
};

// @ 0x0041e5d0
ByteVec::~ByteVec()
{
    for (uint8_t* p = mBegin; p < mEnd; ++p) { }
    if (mBegin)
        DoFree(mBegin, mCap - mBegin);
}

// Vector of intrusive pointers to refcounted objects.
struct IPtr {
    Counted* p;
    IPtr() : p(0) {}
    ~IPtr() { if (p) p->Release(); }
};

struct IPtrVec {
    IPtr* mBegin;
    IPtr* mEnd;
    IPtr* mCap;
    void Free();                                    // 0x00425990
    static void DestroyRange(IPtr* first, IPtr* last) { for (; first < last; ++first) first->~IPtr(); }
    void DoInsertValue(IPtr* pos, const IPtr& v) throw();   // 0x00423c40
    ~IPtrVec();
    void push_back();
};

// @ 0x0041e640
IPtrVec::~IPtrVec()
{
    ScratchSlots<2>();
    DestroyRange(mBegin, mEnd);
    ScratchSlots<3>();
    Free();
}

// @ 0x0041e6a0
void IPtrVec::push_back()
{
    ScratchSlots<2>();
    if (mEnd < mCap) {
        IPtr* p = mEnd;
        mEnd += 1;
        ::new((void*)p) Counted*(0);
    } else {
        IPtr tmp;
        DoInsertValue(mEnd, tmp);
    }
}
