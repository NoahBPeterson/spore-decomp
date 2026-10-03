// Misc startup-module helpers: a message ctor, Matrix3/Vector3 math, and EASTL wide-string
// (basic_string<wchar_t>) internals. Built /Od /Ob1 /arch:SSE.
#include <intrin.h>
#include <stdarg.h>
#include "types.h"

struct Vector3 {
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
};

struct Matrix3 {
    union { float m[3][3]; Vector3 rows[3]; };
    Vector3& operator[](int i) { return rows[i]; }
    Matrix3& Assign(const Matrix3& m);   // @ 0x0041CB40 (other slice)
};

// ---- message ctor ---------------------------------------------------------------------------
struct BehaviorMessage {
    virtual void Dummy0();
    int mRefCount;      // +4
    int pad[6];         // +8..+0x20
    int pad2[3];        // +0x20..0x2C
    int mArg;           // +0x28 (overlaps; see ctor)
};

struct MessageBase {
    virtual void Dummy0();
    long mRefCount;     // +4
    int mUnk8[8];       // +8..+0x28
    int mUserData;      // +0x28
};

// @ 0x00423110
struct LocaleMessage : MessageBase {
    LocaleMessage(int userData);
    virtual void Dummy1();
};

LocaleMessage::LocaleMessage(int userData)
{
    mUserData = userData;
    _InterlockedExchange(&mRefCount, 0);
}

// ---- vector / matrix math ---------------------------------------------------------------------
// @ 0x00423160  out = v * m (row vector times 3x3 matrix)
Vector3* TransformVector3(Vector3* out, const Vector3* v, const float* m)
{
    Vector3 tmp;
    tmp.x = m[6] * v->z + (m[3] * v->y + m[0] * v->x);
    tmp.y = m[7] * v->z + (m[4] * v->y + m[1] * v->x);
    tmp.z = m[8] * v->z + (m[5] * v->y + m[2] * v->x);
    out->x = tmp.x;
    out->y = tmp.y;
    out->z = tmp.z;
    return out;
}

// @ 0x004232c0
uint8_t Vector3Equal(const Vector3* a, const Vector3* b)
{
    int eq;
    if (a->x == b->x && a->y == b->y && a->z == b->z)
        eq = true;
    else
        eq = false;
    return eq;
}

// @ 0x00423250
uint8_t Matrix3Equal(const Matrix3* a, const Matrix3* b)
{
    int eq;
    if (Vector3Equal((const Vector3*)a->m[0], (const Vector3*)b->m[0]) && Vector3Equal((const Vector3*)a->m[1], (const Vector3*)b->m[1]) &&
        Vector3Equal((const Vector3*)a->m[2], (const Vector3*)b->m[2]))
        eq = true;
    else
        eq = false;
    return eq;
}

// @ 0x00423320
Matrix3* Matrix3Multiply(Matrix3* out, const Matrix3* a, const Matrix3* b)
{
    Matrix3 vx;
    for (int i = 0; i < 3; ++i) {
        float fX = a->m[i][2] * b->m[2][0] + (a->m[i][1] * b->m[1][0] + a->m[i][0] * b->m[0][0]);
        Vector3& rowZ = vx[i];
        rowZ[0] = fX;
        float fY = a->m[i][2] * b->m[2][1] + (a->m[i][1] * b->m[1][1] + a->m[i][0] * b->m[0][1]);
        Vector3& s1 = vx[i];
        s1[1] = fY;
        float fZ = a->m[i][2] * b->m[2][2] + (a->m[i][1] * b->m[1][2] + a->m[i][0] * b->m[0][2]);
        Vector3& e1 = vx[i];
        e1[2] = fZ;
    }
    out->Assign(vx);
    return out;
}

// ---- wide string ----------------------------------------------------------------------------
extern wchar_t gEmptyWString[];   // 0x01667BAC
int __cdecl VsnprintfW(wchar_t* dst, unsigned n, const wchar_t* fmt, va_list args);       // 0x00939950
wchar_t* __cdecl SearchW(wchar_t* b1, wchar_t* e1, const wchar_t* b2, const wchar_t* e2); // 0x004297f0
void __cdecl DeallocateRaw(void* p);                                                      // EASTL allocator

template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
template <class T> inline const T& Min(const T& a, const T& b) { return (a < b) ? a : b; }

struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;

    wchar_t* begin() { return mpBegin; }
    wchar_t* end() { return mpEnd; }
    wchar_t* at(int i) { return mpBegin + i; }
    unsigned size() { return (unsigned)(mpEnd - mpBegin); }
    unsigned capacity() { return (unsigned)(mpCapacity - mpBegin); }
    unsigned remaining() { return (unsigned)(mpCapacity - mpEnd); }

    WString& AppendSprintfVa(const wchar_t* fmt, va_list args);   // 0x004234b0
    WString& Assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
    unsigned Find(const wchar_t* s, unsigned pos, unsigned n);    // 0x00423700
    void FreeBuffer();                                            // 0x004237d0
    void AllocateSelf(const wchar_t* first, const wchar_t* last); // 0x00423820

    void reserve(unsigned n);                                      // 0x00429520
    void AllocateBuf(unsigned n);                                  // 0x00429760
    void Append(const wchar_t* first, const wchar_t* last);        // 0x00429580
    void Erase(wchar_t* first, wchar_t* last);                     // 0x0042e2f0
};

// @ 0x004234b0
WString& WString::AppendSprintfVa(const wchar_t* fmt, va_list args)
{
    const int nInitialSize = (int)size();
    int nReturnValue;

    if (mpBegin == gEmptyWString) {
        nReturnValue = VsnprintfW(end(), 0, fmt, args);
    } else {
        nReturnValue = VsnprintfW(end(), (int)remaining(), fmt, args);
    }

    if (nReturnValue >= (int)remaining()) {
        reserve(nInitialSize + nReturnValue);
        nReturnValue = VsnprintfW(at(nInitialSize), nReturnValue + 1, fmt, args);
    } else if (nReturnValue < 0) {
        unsigned nLocalBufferSize = Max<unsigned>(7, size() << 1);
        for (; nReturnValue < 0 && nLocalBufferSize < 1000000; nLocalBufferSize <<= 1) {
            reserve(nLocalBufferSize);
            nReturnValue = VsnprintfW(at(nInitialSize), nLocalBufferSize + 1 - nInitialSize, fmt, args);
        }
    }

    if (nReturnValue >= 0)
        mpEnd = mpBegin + nInitialSize + nReturnValue;
    return *this;
}

// @ 0x00423650
WString& WString::Assign(const wchar_t* first, const wchar_t* last)
{
    const unsigned n = (unsigned)(last - first);
    if (n <= (unsigned)(mpEnd - mpBegin)) {
        memcpy(mpBegin, first, n * 2);
        Erase(mpBegin + n, mpEnd);
    } else {
        memcpy(mpBegin, first, (mpEnd - mpBegin) * 2);
        Append(first + (mpEnd - mpBegin), last);
    }
    return *this;
}

// @ 0x00423700
unsigned WString::Find(const wchar_t* s, unsigned pos, unsigned n)
{
    const unsigned nLength = (unsigned)(mpEnd - mpBegin);
    if (n <= nLength) {
        if (n != 0) {
            wchar_t* const pEnd = mpBegin + Min(pos, nLength - n) + n;
            wchar_t* const pResult = SearchW(mpBegin, pEnd, s, s + n);
            if (pResult != pEnd)
                return (unsigned)(pResult - mpBegin);
        } else {
            return Min(pos, nLength);
        }
    }
    return (unsigned)-1;
}

// @ 0x004237d0
void WString::FreeBuffer()
{
    int n;
    wchar_t* pData;
    wchar_t* pMem;
    if ((mpCapacity - mpBegin) > 1) {
        n = (int)(mpCapacity - mpBegin);
        pData = mpBegin;
        if (pData) {
            pMem = pData;
            DeallocateRaw(pMem);
        }
    }
}

// @ 0x00423820
void WString::AllocateSelf(const wchar_t* first, const wchar_t* last)
{
    const unsigned n = (unsigned)(last - first);
    AllocateBuf(n + 1);
    wchar_t* pNew = mpBegin;
    memcpy(pNew, first, (last - first) * 2);
    mpEnd = pNew + (last - first);
    *mpEnd = 0;
}

// @ 0x00423890  find last occurrence of c in [lo, hi), scanning backwards
wchar_t* __cdecl RFindChar(wchar_t* hi, wchar_t* lo, wchar_t c)
{
    while (hi > lo) {
        if (hi[-1] == c)
            return hi;
        hi -= 1;
    }
    return lo;
}

// ---- 0x38-byte element vector range erase -------------------------------------------------------
struct Elem38 {
    int data[14];
    void Assign(const Elem38* other);   // 0x00537dc0
};

// EASTL-style copy used by vector::erase (element-wise assignment).
inline Elem38* CopyElems(Elem38* first, Elem38* last, Elem38* result)
{
    const bool b0 = false;
    const bool b1 = false;
    const bool b2 = false;
    for (; first != last; ++first, ++result)
        result->Assign(first);
    return result;
}

struct Elem38Vector {
    Elem38* mpBegin;
    Elem38* mpEnd;
    Elem38* erase(Elem38* first, Elem38* last);   // 0x004238c0
};

// @ 0x004238c0
Elem38* Elem38Vector::erase(Elem38* first, Elem38* last)
{
    Elem38* position = CopyElems(last, mpEnd, first);
    for (Elem38* p = position; p < mpEnd; ++p) {
    }
    mpEnd -= (last - first);
    return first;
}
