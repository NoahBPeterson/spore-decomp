// Slice s00453250: Havok / EASTL / rw::math helpers used by the editor module. Unoptimized module.
// Flags: /Od /Ob1 /Oi /MD /TP /arch:SSE /fp:fast /Gy   (no /EHsc: temporaries with dtors get no EH frame)
#include "types.h"
#include <math.h>
#include <string.h>
#include <new>
#include <xmmintrin.h>

template<int N> inline void ScratchSlots() { uint32_t s[N]; }   // stands in for unused inline temps

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
void EASTL_allocator_deallocate(void* p);                       // 0xf47380
extern unsigned long g_threadMemoryTls;                         // hkThreadMemory TLS slot 0x16e4174

// ---------------------------------------------------------------- Havok
struct hkThreadMemory {
    void deallocateChunk(void* p, int nbytes, int cls);         // 0x107db10
    static hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_threadMemoryTls); }
};
template<class T> struct hkArray {
    T* m_data; int m_size; int m_capacityAndFlags;
    hkArray() : m_data(0), m_size(0), m_capacityAndFlags(0x80000000) {}
    __forceinline ~hkArray() {
        if ((m_capacityAndFlags & 0x80000000) == 0) {
            int cap = getCapacity();
            hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_threadMemoryTls);
            mem->deallocateChunk(m_data, cap * sizeof(T), 0x14);
        }
    }
    int getCapacity() const { return m_capacityAndFlags & 0x3fffffff; }
    void releaseMemory() {
        if ((m_capacityAndFlags & 0x80000000) == 0) {
            int cap = getCapacity();
            hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_threadMemoryTls);
            mem->deallocateChunk(m_data, cap * sizeof(T), 0x14);
        }
    }
};
struct hkVector4 {
    union { __m128 m_quad; struct { float x, y, z, w; }; };
    void setZero4() { w = 0.0f; z = 0.0f; y = 0.0f; x = 0.0f; }
    hkVector4& operator=(const hkVector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
};
extern const float kZero;    // 0x1485378
extern const float kOne;     // 0x1485720
struct hkRotation {
    hkVector4 m_col[3];
    hkVector4& getColumn(int i) { return *(hkVector4*)((char*)m_col + (i << 4)); }
    void setAll(float x, float y, float z, float w) {
        hkVector4 v; v.x = x; v.y = y; v.z = z; v.w = w;
    }
};
struct HavokTransform { float a, b; uint32_t pad[2]; hkVector4 m_translation; hkRotation m_rotation; };
struct Pair16_12 { hkArray<hkVector4> mA; hkArray<float[3]> mB; Pair16_12(); ~Pair16_12(); };

namespace SP { namespace EditorUtils {
// @ 0x00453250
HavokTransform* __fastcall GetHavokTransformFromMatrix(HavokTransform* t)
{
    t->a = kZero;
    t->b = kZero;
    hkVector4& tr = t->m_translation;
    tr.w = kZero; tr.z = kZero; tr.y = kZero; tr.x = kZero;
    hkRotation& r = t->m_rotation;
    hkVector4 zero;
    zero.w = kZero; zero.z = kZero; zero.y = kZero; zero.x = kZero;
    r.getColumn(0) = zero;
    r.getColumn(1) = zero;
    r.getColumn(2) = zero;
    return t;
}
}}

// @ 0x00453400
Pair16_12::Pair16_12() {}

// @ 0x00453460
Pair16_12::~Pair16_12() {}

// ---------------------------------------------------------------- refcounting
struct DefaultRefCounted {
    virtual ~DefaultRefCounted();
    int mnRefCount;
    int Release();
};
// @ 0x00453540
int DefaultRefCounted::Release()
{
    int rc = mnRefCount - 1;
    mnRefCount = mnRefCount - 1;
    if (rc != 0) return rc;
    mnRefCount = 1;
    delete this;
    return 0;
}

struct IRefCounted { virtual int AddRef(); virtual int Release(); };
template<class T> struct AutoRefCountI {
    T* mpObject;
    AutoRefCountI& operator=(T* p) {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
template struct AutoRefCountI<IRefCounted>;
// @ 0x004535d0 sym=??4?$AutoRefCountI@UIRefCounted@@@@QAEAAU0@PAUIRefCounted@@@Z

// ---------------------------------------------------------------- strings
struct FixedAllocTag { uint32_t mName; FixedAllocTag() {} };
struct string32 {
    char* mpBegin; char* mpEnd; char* mpCapacity; uint32_t mAlloc[2];
    char mBuffer[0x20];
    void InitAllocator(FixedAllocTag* t);                       // 0x422cf0
    void assign(const char* first, const char* last);           // 0x45f430
    string32();
    string32& operator=(const char* p);
};
// @ 0x00453630
string32::string32()
{
    char* p = mBuffer;
    FixedAllocTag a;
    InitAllocator(&a);
    mpEnd = mBuffer;
    mpBegin = mpEnd;
    mpCapacity = mpBegin + 0x20;
    *mpBegin = 0;
}

inline size_t CharStrlen(const char* p)
{
    const char* pCurrent = p;
    const char* pStart = p + 1;
    while (*pCurrent++)
        ;
    return (size_t)(pCurrent - pStart);
}
// @ 0x00453690 sym=??4string32@@QAEAAU0@PBD@Z
string32& string32::operator=(const char* p)
{
    if (mpBegin != p) {
        if (mpBegin != mpEnd) { *mpBegin = 0; mpEnd = mpBegin; }
        assign(p, p + strlen(p));
    }
    return *this;
}

// ---------------------------------------------------------------- math
// std::_Pow_int<float> (an out-of-line instance)
// @ 0x004537f0
float Pow_int(float _X, int _Y)
{
    unsigned int _N;
    if (_Y >= 0) _N = (unsigned int)_Y;
    else _N = (unsigned int)(-_Y);
    for (float _Z = 1.0f; ; _X *= _X) {
        if ((_N & 1) != 0) _Z *= _X;
        if ((_N >>= 1) == 0) return (_Y < 0 ? 1.0f / _Z : _Z);
    }
}

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    void Set(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};
// @ 0x00453880 sym=??K@YA?AUVector3@@ABU0@ABM@Z
Vector3 operator/(const Vector3& v, const float& s)
{
    float inv = 1.0f / s;
    Vector3 r(v.x * inv, v.y * inv, v.z * inv);
    return r;
}

struct Matrix33 {
    Vector3 xAxis, yAxis, zAxis;
    Matrix33(float a, float b, float c, float d, float e, float f, float g, float h, float i)
    { xAxis.Set(a, b, c); yAxis.Set(d, e, f); zAxis.Set(g, h, i); }
};
namespace rw { namespace math { namespace fpu {
// @ 0x00453920
Matrix33 Matrix33FromEulerXYZ(const Vector3& e)
{
    // Local names chosen for the /Od slot order (od_names fit 14; y/z still swap, see nonmatching.txt); roles in the comments.
    float v8 = e.x;                       // x
    float t2 = sinf(v8), elem = cosf(v8);   // sx, cx
    float n6 = e.y;                       // y
    float s = sinf(n6), mid = cosf(n6);   // sy, cy
    float t33 = e.z;                       // z
    float n5 = sinf(t33), p1 = cosf(t33);   // sz, cz
    float n17 = elem * p1;              // cx*cz
    float p9 = elem * n5;              // cx*sz
    float owner = t2 * p1;              // sx*cz
    float t23 = t2 * n5;              // sx*sz
    float p40[9];                          // the nine elements
    p40[0] = mid * p1; p40[1] = mid * n5; p40[2] = -s;
    p40[3] = s * owner - p9; p40[4] = s * t23 + n17; p40[5] = mid * t2;
    p40[6] = s * n17 + t23; p40[7] = s * p9 - owner; p40[8] = mid * elem;
    return Matrix33(p40[0], p40[1], p40[2], p40[3], p40[4], p40[5], p40[6], p40[7], p40[8]);
}
}}}
// @ 0x00453b20
Matrix33 Matrix33FromAxisAngle(const Vector3& a, float angle)
{
    float s = sinf(angle), c = cosf(angle);
    float t = 1.0f - c;
    float tx = t * a.x, ty = t * a.y, tz = t * a.z;
    float sx = s * a.x, sy = s * a.y, sz = s * a.z;
    return Matrix33(tx * a.x + c, tx * a.y + sz, tx * a.z - sy,
                    ty * a.x - sz, ty * a.y + c, ty * a.z + sx,
                    tz * a.x + sy, tz * a.y - sx, tz * a.z + c);
}

// ---------------------------------------------------------------- EASTL
namespace eastl {
template<class T> inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
struct wstring {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator;
    wstring(const wchar_t* first, const wchar_t* last) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(first, last); }
    void RangeInitialize(const wchar_t* first, const wchar_t* last);   // WString_AllocateSelf 0x423820
    wstring substr(uint32_t position, uint32_t n) const;
};
// @ 0x00453d20
wstring wstring::substr(uint32_t position, uint32_t n) const
{
    return wstring(mpBegin + position, mpBegin + position + min_alt(n, (uint32_t)(mpEnd - mpBegin) - position));
}

template<class T> inline void destruct(T* first, T* last) { for (; first < last; ++first) first->~T(); }

struct Bounds {                                     // 32-byte element
    uint32_t data[8];
    Bounds();                                       // Bounds::Bounds 0x433960
    ~Bounds();                                      // 0x4ae250
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
struct VectorBase32 { Bounds* mpBegin; Bounds* mpEnd; Bounds* mpCapacity; uint32_t mAllocator; ~VectorBase32(); };  // DestroyVector32 0x4273f0
struct BoundsVector : VectorBase32 {
    ~BoundsVector();
    void resize(uint32_t n);
    void DoInsertValues(Bounds* position, uint32_t n, const Bounds& value);   // 0x455fa0
    Bounds* erase(Bounds* first, Bounds* last);                               // 0x454dc0
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
// @ 0x00453dc0
BoundsVector::~BoundsVector() { destruct(mpBegin, mpEnd); ScratchSlots<3>(); }
// @ 0x00453e20
void BoundsVector::resize(uint32_t n)
{
    if (n > size()) DoInsertValues(mpEnd, n - size(), Bounds());
    else erase(mpBegin + n, mpEnd);
}
}

namespace SP { struct cSPEditorBlock { virtual void v0(); virtual int AddRef(); virtual int Release(); }; }
namespace EA {
template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
}
namespace eastl {
typedef EA::AutoRefCount<SP::cSPEditorBlock> BlockRef;
BlockRef* copy_impl(BlockRef* first, BlockRef* last, BlockRef* result);              // 0x4571d0
BlockRef* uninitialized_copy_impl(BlockRef* first, BlockRef* last, BlockRef* dest);  // 0x4551e0
inline BlockRef* copy(BlockRef* first, BlockRef* last, BlockRef* result)
{
    const bool b = false, a = false, c = false;
    ScratchSlots<2>();
    return copy_impl(first, last, result);
}
struct sp_vector_allocator {
    void deallocate(void* p, uint32_t) { if (((int*)p)[-1]) { void* q = p; EASTL_allocator_deallocate(q); } }
};
struct BlockVectorBase { BlockRef* mpBegin; BlockRef* mpEnd; BlockRef* mpCapacity; sp_vector_allocator mAllocator; ~BlockVectorBase(); };  // 0x425990
struct BlockVector : BlockVectorBase {
    ~BlockVector();
    BlockVector& operator=(const BlockVector& x);
    void push_back(const BlockRef& value);
    BlockRef* erase(BlockRef* first, BlockRef* last);
    BlockRef* DoRealloc(uint32_t n, BlockRef* first, BlockRef* last);   // 0x455180
    void DoInsertValue(BlockRef* position, const BlockRef& value);     // 0x454ee0
    void DoFree(BlockRef* p, uint32_t n) { if (p) mAllocator.deallocate(p, n); }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    uint32_t capacity() const { return (uint32_t)(mpCapacity - mpBegin); }
};
// @ 0x00453eb0
BlockVector::~BlockVector() { destruct(mpBegin, mpEnd); ScratchSlots<3>(); }
// @ 0x00453f20 sym=??4BlockVector@eastl@@QAEAAU01@ABU01@@Z
BlockVector& BlockVector::operator=(const BlockVector& x)
{
    if (&x != this) {
        const uint32_t n = x.size();
        if (n > capacity()) {
            BlockRef* const pNewData = DoRealloc(n, x.mpBegin, x.mpEnd);
            destruct(mpBegin, mpEnd);
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
            mpBegin = pNewData;
            mpCapacity = mpBegin + n;
        } else if (n > size()) {
            copy(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            uninitialized_copy_impl(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
        } else {
            BlockRef* const position = copy(x.mpBegin, x.mpEnd, mpBegin);
            destruct(position, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}
// @ 0x004541f0
void BlockVector::push_back(const BlockRef& value)
{
    if (mpEnd < mpCapacity) ::new(mpEnd++) BlockRef(value);
    else DoInsertValue(mpEnd, value);
}
// @ 0x00454280
BlockRef* BlockVector::erase(BlockRef* first, BlockRef* last)
{
    BlockRef* const position = copy(last, mpEnd, first);
    destruct(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}
}
