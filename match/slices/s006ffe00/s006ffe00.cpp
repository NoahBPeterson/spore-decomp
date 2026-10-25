// Slice s006ffe00: frustum/spatial-cell helpers (bit-pack/unpack) and small vector/accessor
// routines. Region 0x6ffe00-0x700d80. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-.
#include "types.h"
#include <xmmintrin.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include <new>
#include <intrin.h>

// ---- external callees -------------------------------------------------------------------
void* __cdecl FUN_011e073e(void* p, int a, unsigned size);
void  __cdecl FUN_006ec4a0(void* pos, const void* v);
void  __cdecl FUN_00f47410(int a);
void  __cdecl FUN_00762a00(int a);
void  __cdecl FUN_00762a30(int a);
void  __cdecl FUN_00761130(int a);
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
void* __cdecl FUN_006ffdc0(void* dst, const void* src);          // 0x006ffdc0 4x4 transpose
void  __stdcall FUN_006ffc60(void* plane);                        // 0x006ffc60 plane bisector indices (ret 4)
void* __cdecl operator_new(unsigned size, int align, int flags, const char* name,
                           int a, int b, int c, int d);           // 0x00f473d0
void* __cdecl FUN_006df700(void* a, void* b, void* c);            // 0x006df700 CopyRefPtr
void  __stdcall FUN_0059c410(void* a, void* b);                   // 0x0059c410 ReleaseAutoRefRange

// ---- globals ----------------------------------------------------------------------------
extern unsigned short g_cellTable[];   // 0x15352a8, 32 ushort entries
extern int            g_planeOrder[6]; // 0x1534e4c, frustum plane evaluation order
extern unsigned char  g_frustumOff;    // 0x1628c38, frustum cull disabled

#define VFN(p, off) (*(void***)(p))[((off) >> 2)]

namespace SP {
// 0x28-byte clip plane: coefficients x,y,z,w then two 3-index corner selectors.
struct ClipPlane {
    float x, y, z, w;   // +0x00
    int   idx[6];       // +0x10
};
// Frustum built from a view matrix: six planes, no other members in this region.
struct FrustumBuilder {
    ClipPlane planes[6];
    void Build(const void* view);
};
struct cFrustumCull {
    ClipPlane mClipPlanes[6];
    unsigned int FrustumTestSphere(int* a, int* b, unsigned int flags);
    unsigned int AltTest(int* a, int* b);   // 0x006ffaf0
};
} // namespace SP

// @ 0x006ffe00
void SP::FrustumBuilder::Build(const void* view) {
    float tmp[16];
    float m[16];
    memcpy(m, FUN_006ffdc0(tmp, view), 64);

    planes[0].x = -(m[0] + m[12]);
    planes[0].y = -(m[1] + m[13]);
    planes[0].z = -(m[2] + m[14]);
    planes[0].w = -(m[3] + m[15]);
    planes[1].x = -(m[12] - m[0]);
    planes[1].y = -(m[13] - m[1]);
    planes[1].z = -(m[14] - m[2]);
    planes[1].w = -(m[15] - m[3]);
    planes[2].x = -(m[12] - m[4]);
    planes[2].y = -(m[13] - m[5]);
    planes[2].z = -(m[14] - m[6]);
    planes[2].w = -(m[15] - m[7]);
    planes[3].x = -(m[4] + m[12]);
    planes[3].y = -(m[5] + m[13]);
    planes[3].z = -(m[6] + m[14]);
    planes[3].w = -(m[7] + m[15]);
    planes[4].x = -m[8];
    planes[4].y = -m[9];
    planes[4].z = -m[10];
    planes[4].w = -m[11];
    planes[5].x = -(m[12] - m[8]);
    planes[5].y = -(m[13] - m[9]);
    planes[5].z = -(m[14] - m[10]);
    planes[5].w = -(m[15] - m[11]);

    const float kOne = 1.0f;
    for (int i = 0; i < 6; i++) {
        ClipPlane* p = &planes[i];
        float x = p->x, y = p->y, z = p->z;
        float len2 = x * x;
        len2 += y * y;
        len2 += z * z;
        float s = kOne / sqrtf(len2);
        p->x = x * s;
        p->y = y * s;
        p->z = z * s;
        p->w *= s;
        FUN_006ffc60(p);
    }
}

// @ 0x00700120
unsigned int SP::cFrustumCull::FrustumTestSphere(int* a, int* b, unsigned int flags) {
    if (flags & 0x200)
        return AltTest(a, b);
    if (g_frustumOff != 0)
        return 0x13f;

    int bits[6];
    bits[0] = a[0];
    bits[1] = a[1];
    bits[2] = a[2];
    bits[3] = b[0];
    bits[4] = b[1];
    bits[5] = b[2];
    float* pts = (float*)bits;
    flags &= ~0x100u;

    for (unsigned off = 0; off < 0x18; off += 4) {
        int pi = *(int*)((char*)g_planeOrder + off);
        unsigned int bit = 1u << pi;
        if ((flags & bit) != 0)
            continue;
        const ClipPlane* p = &mClipPlanes[pi];
        float f1 = p->x;
        float f2 = p->y;
        float f3 = p->z;
        float f4 = p->w;
        float d0 = f1 * pts[p->idx[0]] + f2 * pts[p->idx[2]] +
                   f3 * pts[p->idx[4]] + f4;
        if ((*(unsigned int*)&d0 & 0x80000000u) == 0) {
            flags |= 0x7f;
            break;
        }
        float d1 = f1 * pts[p->idx[1]] + f2 * pts[p->idx[3]] +
                   f3 * pts[p->idx[5]] + f4;
        if ((*(unsigned int*)&d1 & 0x80000000u) == 0)
            flags |= 0x100;
        else
            flags |= bit;
    }
    if ((flags & 0x140u) == 0)
        flags |= 0x80;
    return flags;
}

// cell record copy (a POD 0xa0-byte record memcpy)
struct SpCellRecord {
    int     m00[3];     // +0x00
    __m128  m10;        // +0x10  (16-byte aligned -> 4-byte hole at +0x0c)
    int     m20[6];     // +0x20
    uint8_t m38[4];     // +0x38
    int     m3c[3];     // +0x3c  (8-byte hole at +0x48)
    __m128  m50;        // +0x50
    __m128  m60;        // +0x60
    __m128  m70;        // +0x70
    __m128  m80;        // +0x80
    int     m90[3];     // +0x90  (4-byte tail pad to +0xa0)
    SpCellRecord(const SpCellRecord& o);
};
// @ 0x00700290
SpCellRecord::SpCellRecord(const SpCellRecord& o) {
    m00[0] = o.m00[0]; m00[1] = o.m00[1]; m00[2] = o.m00[2];
    m10 = o.m10;
    m20[0] = o.m20[0]; m20[1] = o.m20[1]; m20[2] = o.m20[2];
    m20[3] = o.m20[3]; m20[4] = o.m20[4]; m20[5] = o.m20[5];
    m38[0] = o.m38[0]; m38[1] = o.m38[1]; m38[2] = o.m38[2]; m38[3] = o.m38[3];
    m3c[0] = o.m3c[0]; m3c[1] = o.m3c[1]; m3c[2] = o.m3c[2];
    m50 = o.m50; m60 = o.m60; m70 = o.m70; m80 = o.m80;
    m90[0] = o.m90[0]; m90[1] = o.m90[1]; m90[2] = o.m90[2];
}

// @ 0x00700360
struct CellAccessor {
    char pad[8];
    int  f8;   // +0x08
    int  fc;   // +0x0c
    int Get(int* out);
};
int CellAccessor::Get(int* out) {
    if (out)
        *out = fc;
    return f8;
}

struct CellArray {
    void*         vt;      // +0x00
    int           f04;     // +0x04
    SpCellRecord* data;    // +0x08
    unsigned      count;   // +0x0c
    CellArray(const SpCellRecord* src, unsigned n);
    void* Destroy(unsigned flags);
};

// @ 0x007003a0
CellArray::CellArray(const SpCellRecord* src, unsigned n) {
    f04 = 0;
    vt = (void*)0x140c460;
    unsigned __int64 sz = (unsigned __int64)n * 0xa0u;
    unsigned size = (unsigned)sz | (unsigned)-(int)((sz >> 32) != 0);
    data = (SpCellRecord*)operator_new(size, 0x10, 0, "Graphics", 0, 0, 0, 0);
    count = n;
    FUN_011e073e(data, 0, n * 0xa0);
    for (unsigned i = 0; i < n; i++)
        new (&data[i]) SpCellRecord(src[i]);
}

// @ 0x00700450
void* CellArray::Destroy(unsigned flags) {
    vt = (void*)0x140c460;
    EASTL_allocator_deallocate(data);
    vt = (void*)0x13ef094;
    if (flags & 1)
        EASTL_allocator_deallocate(this);
    return this;
}

typedef void (__thiscall* ThiscallVoid)(void*);
typedef void (__thiscall* ThiscallInt)(void*, int);

// One 0x28-byte inline bool/int vector (eastl fixed_vector_allocator shape).
struct BoolVec {
    unsigned char* begin;   // +0x00
    unsigned char* end;     // +0x04
    unsigned char* cap;     // +0x08
    int            f0c;     // +0x0c
    int            f10;     // +0x10
    int            f14;     // +0x14
    unsigned char  buf[16]; // +0x18
};

// Plain three-pointer vector (element sizes differ per instance).
struct Vec3p {
    void* begin;   // +0x00
    void* end;     // +0x04
    void* cap;     // +0x08
};

struct Vec3f {
    float x, y, z;
};

// Small reference-counted object and owning-object interfaces used by the
// 0x7c-byte element type below.
class IObject {
public:
    virtual void f0();
    virtual void Release();       // vtable + 0x04
};

class RefObj {
public:
    virtual void OnZero(int n);   // vtable + 0x00
    volatile int mCount;          // +0x04
};

// AutoRefCount-style destructor: drop one reference, call OnZero(1) at zero.
class AutoRef {
public:
    RefObj* mp;
    AutoRef() {}
    AutoRef(RefObj* p) : mp(p) {}
    ~AutoRef() {
        if (mp != 0) {
            int n = mp->mCount - 1;
            mp->mCount = n;
            if (n == 0) {
                mp->mCount = 1;
                mp->OnZero(1);
            }
        }
    }
};

struct CellRec7c {
    unsigned char m00[0x74];  // +0x00
    IObject*      mpObj;      // +0x74
    RefObj*       mpRef;      // +0x78
    void Assign(const CellRec7c& o);
};

struct Elem8 { int a, b; };

// eastl vector erase(end(), end()) + size adjust: copy is zero bytes but the
// original still emits the call, then moves the end pointer back.
static void ErasePtrRange(BoolVec& v) {
    int* first = (int*)v.begin;
    int* last = (int*)v.end;
    memcpy(first, last, (char*)v.end - (char*)last);
    v.end = (unsigned char*)((int*)v.end - (last - first));
}
static void Erase8Range(Vec3p& v) {
    Elem8* first = (Elem8*)v.begin;
    Elem8* last = (Elem8*)v.end;
    Elem8* dst = first;
    Elem8* src = last;
    Elem8* stop = (Elem8*)v.end;
    while (src != stop) {
        *dst = *src;
        ++src;
        ++dst;
    }
    v.end = (char*)((Elem8*)v.end - (last - (Elem8*)v.begin));
}
static void EraseRecRange(Vec3p& v) {
    CellRec7c* first = (CellRec7c*)v.begin;
    CellRec7c* last = (CellRec7c*)v.end;
    CellRec7c* src = last;
    CellRec7c* stop = (CellRec7c*)v.end;
    while (src != stop) {
        first->Assign(*src);
        ++src;
        ++first;
    }
    v.end = (char*)((CellRec7c*)v.end - (last - (CellRec7c*)v.begin));
}
struct cCellList {
    void*          vt;        // 0x000
    volatile long  f004;      // 0x004
    int            f008;      // 0x008
    int            f00c;      // 0x00c
    int            f010;      // 0x010
    int            f014;      // 0x014
    BoolVec        v018;      // 0x018
    BoolVec        v040;      // 0x040
    BoolVec        v068;      // 0x068
    BoolVec        v090;      // 0x090
    BoolVec        v0b8;      // 0x0b8
    Vec3p          v0e0;      // 0x0e0  (8-byte elements)
    int            pad0ec[2]; // 0x0ec
    Vec3p          v0f4;      // 0x0f4
    int            pad100[2]; // 0x100
    Vec3p          v108;      // 0x108  (0x7c-byte elements)
    int            pad114[2]; // 0x114
    Vec3f          mMin;      // 0x11c
    Vec3f          mMax;      // 0x128
    float          f134;
    IObject*       f138;
    IObject*       f13c;
    cCellList* Construct();
    void Clear();
    ~cCellList();
};

// @ 0x007004d0
cCellList* cCellList::Construct() {
    vt = (void*)0x13ebcdc;
    _InterlockedExchange(&f004, 0);
    f008 = 0;
    f00c = 0;
    f010 = 0;
    f014 = 0;
    vt = (void*)0x140c464;

    v018.f14 = 0;
    v018.begin = v018.buf;
    v018.end = v018.begin;
    v018.cap = v018.begin + 16;

    v040.f14 = 0;
    v040.begin = v040.buf;
    v040.end = v040.begin;
    v040.cap = v040.begin + 16;

    v068.f14 = 0;
    v068.begin = v068.buf;
    v068.end = v068.begin;
    v068.cap = v068.begin + 16;

    v090.f14 = 0;
    v090.begin = v090.buf;
    v090.end = v090.begin;
    v090.cap = v090.begin + 16;

    v0b8.f14 = 0;
    v0b8.begin = v0b8.buf;
    v0b8.end = v0b8.begin;
    v0b8.cap = v0b8.begin + 16;

    v0e0.begin = 0;
    v0e0.end = 0;
    v0e0.cap = 0;
    v0f4.begin = 0;
    v0f4.end = 0;
    v0f4.cap = 0;
    v108.begin = 0;
    v108.end = 0;
    v108.cap = 0;

    Vec3f mn;
    mn.x = FLT_MAX;
    mn.y = FLT_MAX;
    mn.z = FLT_MAX;
    mMin = mn;
    Vec3f mx;
    mx.x = -FLT_MAX;
    mx.y = -FLT_MAX;
    mx.z = -FLT_MAX;
    mMax = mx;
    f134 = 1.0f;
    f138 = 0;
    f13c = 0;
    return this;
}

// @ 0x00700640
struct Vec4b {
    int* begin;   // +0x00
    int* end;     // +0x04
    int* cap;     // +0x08
    void PushBack(const int* v);
    void Grow(void* pos, const void* v);
};
void Vec4b::PushBack(const int* v) {
    int* old = end;
    if (old < cap) {
        end = old + 1;
        if (old)
            *old = *v;
    } else {
        Grow(old, v);
    }
}

// @ 0x007006d0
void cCellList::Clear() {
    int n = (int)((char*)v018.end - (char*)v018.begin) >> 2;
    for (int i = 0; i < n; i++)
        FUN_00f47410(*(int*)(v018.begin + i * 4));
    ErasePtrRange(v018);

    n = (int)((char*)v068.end - (char*)v068.begin) >> 2;
    for (int i = 0; i < n; i++)
        FUN_00762a00(*(int*)(v068.begin + i * 4));
    ErasePtrRange(v068);

    n = (int)((char*)v040.end - (char*)v040.begin) >> 2;
    for (int i = 0; i < n; i++)
        FUN_00762a30(*(int*)(v040.begin + i * 4));
    ErasePtrRange(v040);

    n = (int)((char*)v090.end - (char*)v090.begin) >> 2;
    for (int i = 0; i < n; i++)
        FUN_00761130(*(int*)(v090.begin + i * 4));
    ErasePtrRange(v090);

    ErasePtrRange(v0b8);
    Erase8Range(v0e0);

    {
        int* first = (int*)v0f4.begin;
        int* last  = (int*)v0f4.end;
        void* range = FUN_006df700(last, last, first);
        FUN_0059c410(range, v0f4.end);
        v0f4.end = (char*)((int*)v0f4.end - (last - first));
    }

    {
        CellRec7c* first = (CellRec7c*)v108.begin;
        CellRec7c* last  = (CellRec7c*)v108.end;
        CellRec7c* stop  = last;
        CellRec7c* src   = last;
        while (src != stop) {
            first->Assign(*src);
            ++src;
            ++first;
        }
        for (CellRec7c* p = (CellRec7c*)v108.begin; p < stop; ++p) {
            {
                AutoRef tmp(p->mpRef);
                (void)tmp;
            }
            if (p->mpObj != 0)
                p->mpObj->Release();
        }
        v108.end = (char*)(stop - (last - (CellRec7c*)v108.begin));
    }

    Vec3f mn;
    mn.x = FLT_MAX;
    mn.y = FLT_MAX;
    mn.z = FLT_MAX;
    Vec3f mx;
    mx.x = -FLT_MAX;
    mx.y = -FLT_MAX;
    mx.z = -FLT_MAX;
    mMax = mx;
    mMin = mn;
    f134 = 1.0f;

    if (f138 != 0) {
        IObject* q = f138;
        f138 = 0;
        q->Release();
    }
    if (f13c != 0) {
        IObject* q = f13c;
        f13c = 0;
        q->Release();
    }
    _ReadWriteBarrier();
}

// Free an inline-vector backing store: EASTL keeps the "own memory" flag at p-4.
static void FreeVecBuf(void* p) {
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        EASTL_allocator_deallocate(p);
}

// @ 0x00700a30
cCellList::~cCellList() {
    vt = (void*)0x140c464;
    Clear();
    if (f13c != 0) {
        IObject* q = f13c;
        q->Release();
    }
    if (f138 != 0) {
        IObject* q = f138;
        q->Release();
    }
    ((ThiscallVoid)0x41f270)((char*)this + 0x108);
    ((ThiscallVoid)0x41eb80)((char*)this + 0xf4);
    FreeVecBuf(v0e0.begin);
    FreeVecBuf(v0b8.begin);
    FreeVecBuf(v090.begin);
    FreeVecBuf(v068.begin);
    FreeVecBuf(v040.begin);
    FreeVecBuf(v018.begin);
    vt = (void*)0x13eb938;
}

namespace {

// @ 0x00700b70
void GetParentChildInfo(unsigned a, unsigned* p2, unsigned* p3) {
    *p3 = (((a >> 9) & 0x800) | (a & 0x400)) >> 9 | (a & 1);
    *p2 = (a >> 1) & 0x7ff7fdff;
}

// @ 0x00700bb0
void ChildCellIDs(unsigned a, int* p) {
    int v = (int)(a & 0xfff7fdff) * 2;
    p[0] = v;
    p[1] = v + 1;
    p[2] = v + 0x400;
    p[3] = v + 0x401;
    p[4] = v + 0x100000;
    p[5] = v + 0x100001;
    p[6] = v + 0x100400;
    p[7] = v + 0x100401;
}
} // namespace

// @ 0x00700c00
unsigned int __cdecl FUN_00700c00(unsigned int a) {
    unsigned int hi = a >> 20;
    unsigned int mid = a >> 10;
    return (((((g_cellTable[(hi >> 5) & 0x1f] * 2 | g_cellTable[(mid >> 5) & 0x1f]) * 2 |
               g_cellTable[(a >> 5) & 0x1f]) << 13 | g_cellTable[hi & 0x1f]) * 2 |
             g_cellTable[mid & 0x1f]) * 2) | g_cellTable[a & 0x1f];
}

// @ 0x00700c80
bool __cdecl FUN_00700c80(const float* a, const float* b, const float* c, float r, float* out) {
    float dx = b[0] - a[0];
    float dy = b[1] - a[1];
    float dz = b[2] - a[2];
    float ex = a[0] - c[0];
    float ey = a[1] - c[1];
    float ez = a[2] - c[2];
    float len2 = dx * dx + dy * dy + dz * dz;
    float dot  = dx * ex + dy * ey + dz * ez;
    float elen = ex * ex + ey * ey + ez * ez;
    float disc = dot * dot - (elen - r * r) * len2;
    if (0.0f > disc) return false;
    float root = sqrtf(disc);
    float t1 = -dot - root;
    if (0.0f > root - dot) return false;
    if (t1 > len2) return false;
    if (out != 0) {
        if (!(t1 <= 0.0f)) *out = t1 / len2;
        else               *out = 0.0f;
    }
    return true;
}
