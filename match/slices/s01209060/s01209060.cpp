// Slice s01209060 -- Havok SDK core objects interleaved inside the RenderWare 4
// address range (equivalence-only region): hkUnionFind, hkSemaphore,
// hkStringMapBase, hkSweptTransformUtil plus one hkAabb-style SSE routine and
// one block of static Havok class data.
// Toolchain: Havok was linked in from VC .NET 2003 libraries, so the scalar
// float code is x87; the hkVector4 paths use explicit SSE intrinsics.
#include <xmmintrin.h>
#include <math.h>
#include "types.h"

#pragma intrinsic(sqrt)

// The Win32 kernel imports this slice uses.  Declared by hand so the source also
// builds with the VC .NET 2003 compiler, which cannot parse the newer SDK
// <windows.h>; the calls still go through the image import table.
typedef void* HANDLE;
typedef int   BOOL;
typedef unsigned long DWORD;
typedef long  LONG;

extern "C" {
__declspec(dllimport) HANDLE __stdcall CreateSemaphoreA(void* attrs, LONG initial, LONG maxCount, const char* name);
__declspec(dllimport) BOOL   __stdcall CloseHandle(HANDLE h);
__declspec(dllimport) DWORD  __stdcall WaitForSingleObject(HANDLE h, DWORD ms);
__declspec(dllimport) BOOL   __stdcall ReleaseSemaphore(HANDLE h, LONG count, LONG* previous);
}

// ---------------------------------------------------------------------------
// Out-of-slice helpers (cdecl, resolved by the address annotation).
// ---------------------------------------------------------------------------
void  hkString_memSet(void* dst, int c, int n);            // 0x0107f470 hkString::memSet
int   hkString_strCmp(const char* a, const char* b);       // 0x0107f3d0 hkString::strCmp
void  hkArrayUtil_reserveMore(void* arr, int elemSize);    // 0x0107f530 hkArrayUtil::_reserveMore
void  hkArrayUtil_reserveExactly(void* arr, int size, int elemSize); // 0x0107f4a0

// ---------------------------------------------------------------------------
// hkMemory: only the vtable slots that this slice calls are modelled.
// ---------------------------------------------------------------------------
class hkMemory {
public:
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c();
    virtual void* alloc(int size, int align);              // vtable +0x10
    virtual void  dealloc(void* p, int size, int align);   // vtable +0x14

    static hkMemory* s_instance;                           // 0x016e4178
};

// ---------------------------------------------------------------------------
// hkArray<T>
// ---------------------------------------------------------------------------
template<class T>
class hkArray {
public:
    T*  m_data;                // +0x00
    int m_size;                // +0x04
    int m_capacityAndFlags;    // +0x08
};

typedef hkArray<int> hkArrayInt;

// ---------------------------------------------------------------------------
// hkVector4 / hkQuaternion / hkRotation / hkTransform / hkSweptTransform
// ---------------------------------------------------------------------------
struct hkRotation;

struct __declspec(align(16)) hkVector4 {
    float x, y, z, w;

    void setRotatedDir(const hkRotation& rot, const hkVector4& dir);  // 0x010814a0
};

struct __declspec(align(16)) hkQuaternion {
    float x, y, z, w;
};

struct __declspec(align(16)) hkRotation {
    float m[12];

    void set(const hkQuaternion& q);                                  // 0x010824a0
};

struct __declspec(align(16)) hkTransform {
    hkRotation rotation;       // +0x00
    hkVector4  translation;    // +0x30
};

// 4x4 transform followed by the box radii at +0x44..+0x50.
struct __declspec(align(16)) hkAabbShape {
    float m[0x18];
};

struct __declspec(align(16)) hkSweptTransform {
    hkVector4    m_centreOfRotation0;   // +0x00  (.w = time0)
    hkVector4    m_centreOfRotation1;   // +0x10  (.w = 1/deltaTime)
    hkQuaternion m_rotation0;           // +0x20
    hkQuaternion m_rotation1;           // +0x30
    hkVector4    m_translation0;        // +0x40
};

class hkMotionState { public:
    float m[0x24];             // 0x00..0x8f
};

// ---------------------------------------------------------------------------
// hkUnionFind
// ---------------------------------------------------------------------------
class hkUnionFind {
public:
    hkUnionFind(hkArrayInt& arr, int numElems);
    void addEdge(int a, int b);
    void assignGroups(hkArrayInt& out);

private:
    void collapseTree();

    hkArrayInt* m_array;       // +0x00
};

// ---------------------------------------------------------------------------
// hkSemaphore
// ---------------------------------------------------------------------------
class hkSemaphore {
public:
    hkSemaphore(int initial, int maxCount);
    ~hkSemaphore();
    void acquire();
    void release(int count);

private:
    HANDLE m_handle;           // +0x00
};

// ---------------------------------------------------------------------------
// hkStringMapBase -- open-addressed hash table, values at [i + 2*mask + 2].
// ---------------------------------------------------------------------------
class hkStringMapBase {
public:
    hkStringMapBase();
    ~hkStringMapBase();

    int         getIterator() const;
    int         getNext(int i) const;
    unsigned    getValue(int i) const;
    const char* getName(int i) const;
    void        isValid(bool* out, int i) const;

    void        insert(const char* key, unsigned value);
    int         findKey(const char* key) const;
    unsigned    getWithDefault(const char* key, unsigned def) const;

protected:
    void        resizeTable(int slots);

private:
    int* m_table;              // +0x00
    int  m_numEntries;         // +0x04
    int  m_mask;               // +0x08
};

// ---------------------------------------------------------------------------
// hkSweptTransformUtil
// ---------------------------------------------------------------------------
class hkSweptTransformUtil {
public:
    static void setTimeInformation(float time0, float time1, hkMotionState& ms);
    static void setCentreOfRotationLocal(const hkVector4& v, hkMotionState& ms);
    static void lerp2(const hkSweptTransform& st, float t, hkTransform& out);
};

// ---------------------------------------------------------------------------
// hkAabbUtil -- the bounding-box builder is a thiscall member (ecx = the
// transform, three stack arguments), so it is modelled as a real class.
// ---------------------------------------------------------------------------
class hkAabbUtil {
public:
    int calcAabb(const hkAabbShape* b, int unused, hkVector4* out);
};

// ===========================================================================
// code
// ===========================================================================

// @ 0x01209060
// Axis-aligned box from a transform: rotates the four rows by "b" (identity when
// b is null) and expands by the radii at +0x44/+0x48/+0x4c plus the padding at
// +0x50.  Writes the min corner at out[0] and the max corner at out[0x10].
int hkAabbUtil::calcAabb(const hkAabbShape* b, int unused, hkVector4* out)
{
    (void)unused;
    __m128 m0 = _mm_load_ps(((const hkAabbShape*)this)->m);
    __m128 r0, r1, r2, r3;

    if (b != 0) {
        __m128 b0 = _mm_load_ps(b->m);
        __m128 b1 = _mm_load_ps(b->m + 4);
        __m128 b2 = _mm_load_ps(b->m + 8);

        r0 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(b0, _mm_shuffle_ps(m0, m0, 0x00)),
                                   _mm_mul_ps(b1, _mm_shuffle_ps(m0, m0, 0x55))),
                        _mm_mul_ps(b2, _mm_shuffle_ps(m0, m0, 0xaa)));

        __m128 m1 = _mm_load_ps(((const hkAabbShape*)this)->m + 4);
        r1 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(b0, _mm_shuffle_ps(m1, m1, 0x00)),
                                   _mm_mul_ps(b1, _mm_shuffle_ps(m1, m1, 0x55))),
                        _mm_mul_ps(b2, _mm_shuffle_ps(m1, m1, 0xaa)));

        __m128 m2 = _mm_load_ps(((const hkAabbShape*)this)->m + 8);
        r2 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(b0, _mm_shuffle_ps(m2, m2, 0x00)),
                                   _mm_mul_ps(b1, _mm_shuffle_ps(m2, m2, 0x55))),
                        _mm_mul_ps(b2, _mm_shuffle_ps(m2, m2, 0xaa)));

        __m128 m3 = _mm_load_ps(((const hkAabbShape*)this)->m + 12);
        __m128 b3 = _mm_load_ps(b->m + 12);
        r3 = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(b0, _mm_shuffle_ps(m3, m3, 0x00)),
                                              _mm_mul_ps(b1, _mm_shuffle_ps(m3, m3, 0x55))),
                                   _mm_mul_ps(b2, _mm_shuffle_ps(m3, m3, 0xaa))),
                        _mm_mul_ps(b3, _mm_set1_ps(1.0f)));
    } else {
        r0 = m0;
        r1 = _mm_load_ps(((const hkAabbShape*)this)->m + 4);
        r2 = _mm_load_ps(((const hkAabbShape*)this)->m + 8);
        r3 = _mm_load_ps(((const hkAabbShape*)this)->m + 12);
    }

    __m128 neg = _mm_set1_ps(-1.0f);
    __m128 ext = _mm_add_ps(
        _mm_add_ps(
            _mm_add_ps(
                _mm_mul_ps(_mm_max_ps(_mm_mul_ps(neg, r0), r0), _mm_set1_ps(((const hkAabbShape*)this)->m[0x11])),
                _mm_mul_ps(_mm_max_ps(_mm_mul_ps(neg, r1), r1), _mm_set1_ps(((const hkAabbShape*)this)->m[0x12]))),
            _mm_mul_ps(_mm_max_ps(_mm_mul_ps(neg, r2), r2), _mm_set1_ps(((const hkAabbShape*)this)->m[0x13]))),
        _mm_set1_ps(((const hkAabbShape*)this)->m[0x14]));

    _mm_store_ps(&out->x, _mm_sub_ps(r3, ext));
    _mm_store_ps(&out[1].x, _mm_add_ps(r3, ext));
    return 1;
}

// @ 0x01209220
// NOT CODE: static Havok class-descriptor data (records of vtable pointer +
// flags).  There is no function here and no source is emitted; see
// nonmatching.txt for the bookkeeping note.

// @ 0x01209540
// hkUnionFind::addEdge -- path-compressing union of the two elements.
void hkUnionFind::addEdge(int a, int b)
{
    int lo = a;
    int hi = b;
    if (hi < lo) {
        int t = lo;
        lo = hi;
        hi = t;
    }

    int i = lo;
    while (m_array->m_data[i] >= 0)
        i = m_array->m_data[i];
    int rootA = i;

    i = lo;
    while (m_array->m_data[i] >= 0) {
        int next = m_array->m_data[i];
        m_array->m_data[i] = rootA;
        i = next;
    }

    i = hi;
    while (m_array->m_data[i] >= 0)
        i = m_array->m_data[i];
    int rootB = i;

    i = hi;
    while (m_array->m_data[i] >= 0) {
        int next = m_array->m_data[i];
        m_array->m_data[i] = rootB;
        i = next;
    }

    if (rootA != rootB) {
        if (rootA < rootB) {
            m_array->m_data[rootA] = m_array->m_data[rootA] + m_array->m_data[rootB];
            m_array->m_data[rootB] = rootA;
        } else {
            m_array->m_data[rootB] = m_array->m_data[rootB] + m_array->m_data[rootA];
            m_array->m_data[rootA] = rootB;
        }
    }
}

// @ 0x01209620
// hkUnionFind::collapseTree -- flatten every element onto its group root.
void hkUnionFind::collapseTree()
{
    int* data = m_array->m_data;
    int* end = data + m_array->m_size;

    for (int* p = data; p != end; ++p) {
        int v = *p;
        if (v >= 0 && m_array->m_data[v] >= 0) {
            do {
                *p = m_array->m_data[*p];
            } while (m_array->m_data[*p] >= 0);
        }
    }
}

// @ 0x01209660
// hkUnionFind::hkUnionFind -- size the backing array and mark every slot empty.
hkUnionFind::hkUnionFind(hkArrayInt& arr, int numElems)
{
    m_array = &arr;

    unsigned cap = (unsigned)arr.m_capacityAndFlags & 0x3fffffff;
    if ((int)cap < numElems) {
        int want = (int)cap * 2;
        if (numElems >= want)
            want = numElems;
        hkArrayUtil_reserveExactly(&arr, want, 4);
    }

    arr.m_size = numElems;
    for (int i = 0; i < numElems; ++i)
        m_array->m_data[i] = -1;
}

// @ 0x012096c0
// hkUnionFind::assignGroups -- number the groups and record their sizes.
void hkUnionFind::assignGroups(hkArrayInt& out)
{
    collapseTree();

    int next = 0;
    for (int i = 0; i < m_array->m_size; ++i) {
        int v = m_array->m_data[i];
        if (v < 0) {
            if (out.m_size == ((unsigned)out.m_capacityAndFlags & 0x3fffffff))
                hkArrayUtil_reserveMore(&out, 4);
            out.m_data[out.m_size] = -v;
            out.m_size = out.m_size + 1;
            m_array->m_data[i] = next;
            ++next;
        } else {
            m_array->m_data[i] = m_array->m_data[v];
        }
    }
}

// @ 0x01209750
// Small (0x1c byte) Havok object built from hkMemory; the vtable pointer is a
// fixed image address, not something this translation unit can name.
void* hkCreateSmallObject()
{
    void* p = hkMemory::s_instance->alloc(0x1c, 0x15);

    *(unsigned short*)((char*)p + 4) = 0x1c;
    *(unsigned short*)((char*)p + 6) = 1;
    *(unsigned*)p = 0x014f8f54u;
    *(int*)((char*)p + 0x10) = 0;
    *(int*)((char*)p + 0x14) = 0;
    *(int*)((char*)p + 0x18) = 0x80000000;
    *(int*)((char*)p + 0x08) = 0;
    *(int*)((char*)p + 0x0c) = 0;
    return p;
}

// @ 0x01209800
// hkSemaphore::hkSemaphore
hkSemaphore::hkSemaphore(int initial, int maxCount)
{
    m_handle = CreateSemaphoreA(0, initial, maxCount, 0);
}

// @ 0x01209820
// hkSemaphore::~hkSemaphore
hkSemaphore::~hkSemaphore()
{
    CloseHandle(m_handle);
}

// @ 0x01209830
// hkSemaphore::acquire
void hkSemaphore::acquire()
{
    WaitForSingleObject(m_handle, 0xffffffff);
}

// @ 0x01209840
// hkSemaphore::release
void hkSemaphore::release(int count)
{
    ReleaseSemaphore(m_handle, count, 0);
}

// @ 0x01209860
// hkStringMapBase::getIterator -- index of the first occupied slot.
int hkStringMapBase::getIterator() const
{
    int i = 0;
    if (m_mask >= 0) {
        do {
            if (m_table[i] != -1)
                return i;
            ++i;
        } while (i <= m_mask);
    }
    return i;
}

// @ 0x01209880
// Slot name (raw key pointer) for slot i.
const char* hkStringMapBase::getName(int i) const
{
    return (const char*)m_table[m_mask + i + 1];
}

// @ 0x012098a0
// hkStringMapBase::getValue
unsigned hkStringMapBase::getValue(int i) const
{
    return (unsigned)m_table[i + m_mask * 2 + 2];
}

// @ 0x012098c0
// hkStringMapBase::getNext -- index of the next occupied slot after i.
int hkStringMapBase::getNext(int i) const
{
    ++i;
    if (i <= m_mask) {
        do {
            if (m_table[i] != -1)
                return i;
            ++i;
        } while (i <= m_mask);
    }
    return i;
}

// @ 0x012098f0
// Reports whether slot index i is inside the table (used by iterators).
void hkStringMapBase::isValid(bool* out, int i) const
{
    *out = (i <= m_mask);
}

// @ 0x01209910
// hkStringMapBase::insert
void hkStringMapBase::insert(const char* key, unsigned value)
{
    unsigned h = 0;
    const char* p = key;
    char c = *p;
    while (c != 0) {
        h = h * 0x1f + (unsigned)c;
        ++p;
        c = *p;
    }
    h &= 0x7fffffff;

    if (m_numEntries * 2 > m_mask)
        resizeTable(m_mask * 2 + 2);

    unsigned i = (unsigned)m_mask & h;
    while (m_table[i] != -1) {
        if ((unsigned)m_table[i] == h &&
            hkString_strCmp(key, (const char*)m_table[m_mask + i + 1]) == 0)
            break;
        i = (i + 1) & (unsigned)m_mask;
    }

    if (m_table[i] == -1)
        ++m_numEntries;
    m_table[i] = (int)h;
    m_table[m_mask + i + 1] = (int)key;
    m_table[i + m_mask * 2 + 2] = (int)value;
}

// @ 0x012099c0
// hkStringMapBase::findKey -- slot holding key, or m_mask+1 when absent.
int hkStringMapBase::findKey(const char* key) const
{
    unsigned h = 0;
    const char* p = key;
    char c = *p;
    while (c != 0) {
        h = h * 0x1f + (unsigned)c;
        ++p;
        c = *p;
    }
    h &= 0x7fffffff;

    unsigned i = (unsigned)m_mask & h;
    while (m_table[i] != -1) {
        if ((unsigned)m_table[i] == h &&
            hkString_strCmp(key, (const char*)m_table[m_mask + i + 1]) == 0)
            return (int)i;
        i = (i + 1) & (unsigned)m_mask;
    }
    return m_mask + 1;
}

// @ 0x01209a40
// hkStringMapBase::getWithDefault
unsigned hkStringMapBase::getWithDefault(const char* key, unsigned def) const
{
    int i = findKey(key);
    if (i > m_mask)
        return def;
    return (unsigned)m_table[i + m_mask * 2 + 2];
}

// @ 0x01209a70
// hkStringMapBase::hkStringMapBase -- 16 slots, all keys empty.
hkStringMapBase::hkStringMapBase()
{
    m_table = (int*)hkMemory::s_instance->alloc(0xc0, 0x14);
    hkString_memSet(m_table, 0xff, 0x40);
    m_numEntries = 0;
    m_mask = 0xf;
}

// @ 0x01209ab0
// hkStringMapBase::~hkStringMapBase
hkStringMapBase::~hkStringMapBase()
{
    hkMemory::s_instance->dealloc(m_table, (m_mask + 1) * 0xc, 0x14);
}

// @ 0x01209ad0
// hkStringMapBase::resizeTable -- reallocate with "slots" entries and rehash.
void hkStringMapBase::resizeTable(int slots)
{
    int oldSize = m_mask + 1;
    int* old = m_table;

    m_table = (int*)hkMemory::s_instance->alloc(slots * 0xc, 0x14);
    hkString_memSet(m_table, 0xff, slots * 4);
    m_mask = slots - 1;
    m_numEntries = 0;

    int i = 0;
    if (0 < oldSize) {
        do {
            if (old[i] != -1)
                insert((const char*)old[oldSize + i], (unsigned)old[i + oldSize * 2]);
            ++i;
        } while (i < oldSize);
    }

    hkMemory::s_instance->dealloc(old, oldSize * 0xc, 0x14);
}

// @ 0x01209b70
// hkSweptTransformUtil::setTimeInformation
void hkSweptTransformUtil::setTimeInformation(float time0, float time1, hkMotionState& ms)
{
    ms.m[0x4c / 4] = time0;
    ms.m[0x5c / 4] = time1;
}

// @ 0x01209b90
// hkSweptTransformUtil::setCentreOfRotationLocal
void hkSweptTransformUtil::setCentreOfRotationLocal(const hkVector4& v, hkMotionState& ms)
{
    hkVector4 delta;
    delta.x = v.x - ms.m[0x80 / 4];
    delta.y = v.y - ms.m[0x84 / 4];
    delta.z = v.z - ms.m[0x88 / 4];
    delta.w = v.w - ms.m[0x8c / 4];

    ms.m[0x80 / 4] = v.x;
    ms.m[0x84 / 4] = v.y;
    ms.m[0x88 / 4] = v.z;
    ms.m[0x8c / 4] = v.w;

    hkVector4 r;
    r.setRotatedDir(*(const hkRotation*)&ms.m[0], delta);

    ms.m[0x40 / 4] = r.x + ms.m[0x40 / 4];
    ms.m[0x44 / 4] = r.y + ms.m[0x44 / 4];
    ms.m[0x48 / 4] = r.z + ms.m[0x48 / 4];
    ms.m[0x50 / 4] = r.x + ms.m[0x50 / 4];
    ms.m[0x54 / 4] = r.y + ms.m[0x54 / 4];
    ms.m[0x58 / 4] = r.z + ms.m[0x58 / 4];
}

// @ 0x01209c50
// hkSweptTransformUtil::lerp2 -- interpolate a swept transform at time t and
// write out a full hkTransform (fast slerp + centre-of-rotation adjustment).
void hkSweptTransformUtil::lerp2(const hkSweptTransform& st, float t, hkTransform& out)
{
    const float* p = (const float*)&st;
    float* o = (float*)&out;

    float dt = (t - p[3]) * p[7];

    float q0x = p[8], q0y = p[9], q0z = p[0xa], q0w = p[0xb];
    float q1x = p[0xc], q1y = p[0xd], q1z = p[0xe], q1w = p[0xf];

    float sx = q1x + q0x;
    float sy = q0y + q1y;
    float sz = q1z + q0z;
    float sw = q1w + q0w;

    float len2 = ((sw * sw + sz * sz) + sx * sx) + sy * sy;
    float a = 0.75f - len2 * 0.125f;
    float nrm = (1.5f - ((a * a) * len2) * 0.5f) * a;

    float px = sx * nrm;
    float py = sy * nrm;
    float pz = sz * nrm;
    float pw = sw * nrm;

    float d2 = dt + dt;
    float rx, ry, rz, rw;
    if (dt < 0.5f) {
        float c1 = d2 - 1.0f;
        float c0 = 1.0f - c1;
        rx = c0 * px + c1 * q1x;
        ry = c1 * q1y + c0 * py;
        rz = c0 * pz + c1 * q1z;
        rw = c0 * pw + c1 * q1w;
    } else {
        float c0 = 1.0f - d2;
        rx = d2 * px + c0 * q0x;
        ry = c0 * q0y + d2 * py;
        rz = c0 * q0z + d2 * pz;
        rw = c0 * q0w + d2 * pw;
    }

    float qlen2 = ((rw * rw + rz * rz) + rx * rx) + ry * ry;
    float inv = (qlen2 == 0.0f) ? 0.0f : (float)(1.0 / sqrt((double)qlen2));

    hkQuaternion q;
    q.x = inv * rx;
    q.y = ry * inv;
    q.z = rz * inv;
    q.w = inv * rw;

    out.rotation.set(q);

    float w = 1.0f - dt;
    o[0xc] = w * p[0] + dt * p[4];
    o[0xd] = dt * p[5] + w * p[1];
    o[0xe] = dt * p[6] + w * p[2];
    o[0xf] = w * p[3] + dt * p[7];

    float t0x = p[0x10], t0y = p[0x11], t0z = p[0x12];
    float cx = (t0z * o[0x8] + t0y * o[0x4]) + t0x * o[0x0];
    float cy = (t0z * o[0x9] + t0y * o[0x5]) + t0x * o[0x1];
    float cz = (t0z * o[0xa] + t0y * o[0x6]) + t0x * o[0x2];

    o[0xc] = o[0xc] - cx;
    o[0xd] = o[0xd] - cy;
    o[0xe] = o[0xe] - cz;
}
