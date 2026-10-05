// Slice s00716110: SP::cMeshBuilder member helpers (vector push/reserve/color-pack)
// and its EH copy constructors.  Built /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast.
// This region (SporeEP1_RL) is not in the 2008 dev PDB; the class layout was read
// from the constructor's member stores and the accessors below.
#include <stddef.h>

typedef unsigned int   u32;
typedef unsigned char  u8;

// ---------------------------------------------------------------------------
// element types (float structs get a user operator= so copies use x87 fld/fstp)
// ---------------------------------------------------------------------------
struct Vec2 { float x, y;     Vec2& operator=(const Vec2& o) { x = o.x; y = o.y; return *this; } };
struct Vec3 { float x, y, z;  Vec3& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; } };
struct Vec4 { float x, y, z, w; };

struct Vec8 { int a, b; };

// minimal eastl::vector-alike (only the three pointers are touched by this slice)
template<class T> struct EAVec {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    void reserve(int n);                       // masked (eastl::vector::reserve)
    void DoInsertValue(T* pos, const T& v);   // masked (eastl::vector::DoInsertValue)
    void push_back(const T& v) {
        T* p = mpEnd;
        if (p < mpCapacity) {
            mpEnd = p + 1;
            if (p)
                *p = v;
        } else {
            DoInsertValue(p, v);
        }
    }
};
template<class T> struct VecSlot { EAVec<T> v; char pad[8]; };  // 0x14 bytes

// 0x28-byte element at [this+0x120] + i*0x28
struct Elem120 { EAVec<u32> u; char p0[8]; EAVec<float> f; char p1[8]; };
// 0x50-byte element at [this+0x134] + i*0x50
struct Elem134 {
    EAVec<u32> u0;  char p0[8];
    EAVec<Vec3> v14; char p1[8];
    EAVec<u32> u28;  char p2[8];
    EAVec<Vec3> v3c; char p3[8];
};

struct MeshBuilder {
    char pad0[8];                    // +0x00
    VecSlot<Vec3> v8;                // +0x08
    VecSlot<Vec3> v1c;               // +0x1c
    VecSlot<Vec2> v30[4];            // +0x30
    VecSlot<u32>  v80[2];            // +0x80
    VecSlot<u32>  vA8;               // +0xa8
    VecSlot<u32>  vBC;               // +0xbc
    char padD0[0xf8 - 0xd0];         // +0xd0
    EAVec<Vec8>   vF8;               // +0xf8
    char pad104[0x120 - 0x104];      // +0x104
    Elem120*      p120;              // +0x120
    char pad124[0x134 - 0x124];      // +0x124
    Elem134*      p134;              // +0x134
    char pad138[0x148 - 0x138];      // +0x138
    void*         p148;              // +0x148
    int           n14c;              // +0x14c
    u8            b150;              // +0x150
    char pad151[0x158 - 0x151];      // +0x151
    int           n158;              // +0x158
    char pad15c[0x168 - 0x15c];      // +0x15c
    int           n168;              // +0x168
    int           n16c;              // +0x16c
    char pad170[0x188 - 0x170];      // +0x170
    VecSlot<u32>  v188[8];           // +0x188 .. +0x228

    // copy ctors (EH, partial bodies)
    void copyFrom410(const MeshBuilder& src);
    void copyFrom2b0(const MeshBuilder& src);

    // accessors / helpers in this slice
    void pushV8(const Vec3& v);                 // 0x716700
    void pushV1c(const Vec3& v);                // 0x716740
    void pushV30(const Vec2& v, int index);     // 0x716780
    void resizeV8(int n, const Vec3& v);        // 0x7168c0
    void resizeV1c(int n, const Vec3& v);       // 0x716930
    void addPair120(int elemIdx, float value, int delta);        // 0x716e40
    void addBulk120(int elemIdx, int n, const int* idx, const float* vals); // 0x716ed0
    void pushV188_2(u32 v, int index);   // 0x716bf0
    void pushV188_6(u32 v, int index);   // 0x716c30
    void addMasked(u8 mask, u32 value);         // 0x716c70
    void uniqueAdd(int key);                    // 0x716ad0
    void pushColor(const Vec4& c, int index);   // 0x7167c0
    void addColors(int index, int n, const Vec4* c); // 0x7169a0
    void addDiff120(int elemIdx);               // (unused)
    void addDiff134_lo(int slot, int n, const Vec3* pts); // 0x716fc0
    void addDiff134_hi(int slot, int n, const Vec3* pts); // 0x7170e0
    void addDiff134_lo1(int slot, int index, const Vec3* pt); // 0x717200
    void addDiff134_hi1(int slot, int index, const Vec3* pt); // 0x7172f0
};

// ---------------------------------------------------------------------------
// simple push_back accessors
// ---------------------------------------------------------------------------

// @ 0x00716700
void MeshBuilder::pushV8(const Vec3& v) { v8.v.push_back(v); }

// @ 0x00716740
void MeshBuilder::pushV1c(const Vec3& v) { v1c.v.push_back(v); }

// @ 0x00716780
void MeshBuilder::pushV30(const Vec2& v, int index) { v30[index].v.push_back(v); }

// @ 0x007168c0
void MeshBuilder::resizeV8(int n, const Vec3& v)
{
    v8.v.reserve((int)(v8.v.mpEnd - v8.v.mpBegin) + n);
    for (int i = n; i > 0; --i)
        v8.v.push_back(v);
}

// @ 0x00716930
void MeshBuilder::resizeV1c(int n, const Vec3& v)
{
    v1c.v.reserve((int)(v1c.v.mpEnd - v1c.v.mpBegin) + n);
    for (int i = n; i > 0; --i)
        v1c.v.push_back(v);
}

// @ 0x00716bf0
void MeshBuilder::pushV188_2(u32 v, int index) { v188[2 + index].v.push_back(v); }

// @ 0x00716c30
void MeshBuilder::pushV188_6(u32 v, int index) { v188[6 + index].v.push_back(v); }

// @ 0x00716c70
void MeshBuilder::addMasked(u8 mask, u32 value)
{
    if (mask & 1)
        v188[0].v.push_back(value);
    if (mask & 2)
        v188[1].v.push_back(value);
    if (mask & 4)
        v188[2].v.push_back(value);
    if (mask & 0xf8) {
        if (mask & 8)
            v188[3].v.push_back(value);
        if (mask & 0x10)
            v188[4].v.push_back(value);
        if (mask & 0x20)
            v188[5].v.push_back(value);
        if (mask & 0x40)
            v188[6].v.push_back(value);
        if (mask & 0x80)
            v188[7].v.push_back(value);
    }
}

// @ 0x00716ad0  find key in the 8-byte-element vector or append (key, n14c)
void MeshBuilder::uniqueAdd(int key)
{
    n158 = -1;
    int n = (int)(vF8.mpEnd - vF8.mpBegin);
    int idx = 0;
    if (n > 0) {
        int* p = (int*)vF8.mpBegin;
        do {
            if (*p == key) {
                n158 = idx;
                break;
            }
            ++idx;
            p += 2;
        } while (idx < n);
    }
    if (n158 < 0) {
        n158 = (int)(vF8.mpEnd - vF8.mpBegin);
        Vec8 e;
        e.a = key;
        e.b = n14c;
        vF8.push_back(e);
    }
}

// @ 0x00716e40  append (n168+delta) to u and value to f of element elemIdx
void MeshBuilder::addPair120(int elemIdx, float value, int delta)
{
    Elem120& e = p120[elemIdx];
    u32 index = (u32)(n168 + delta);
    e.u.push_back(index);
    e.f.push_back(value);
}

// @ 0x00716ed0  bulk append indices/values to element elemIdx
void MeshBuilder::addBulk120(int elemIdx, int n, const int* idx, const float* vals)
{
    Elem120& e = p120[elemIdx];
    e.u.reserve((int)(e.u.mpEnd - e.u.mpBegin) + n);
    e.f.reserve((int)(e.f.mpEnd - e.f.mpBegin) + n);
    for (int i = 0; i < n; ++i) {
        u32 index = (u32)(n168 + idx[i]);
        e.u.push_back(index);
        e.f.push_back(vals[i]);
    }
}

// ---------------------------------------------------------------------------
// color packing (float RGBA -> packed 32-bit)
// ---------------------------------------------------------------------------
struct BGRA { u8 b, g, r, a; };

static __forceinline u8 PackComp(float f)
{
    if (f < 0.0f)
        f = 0.0f;
    f = f * 255.0f;
    if (f > 255.0f)
        f = 255.0f;
    return (u8)(int)f;
}

static __forceinline u32 PackColor(const Vec4& c)
{
    BGRA col;
    col.b = PackComp(c.z);
    col.g = PackComp(c.y);
    col.r = PackComp(c.x);
    col.a = PackComp(c.w);
    return *(u32*)&col;
}

// @ 0x007167c0
void MeshBuilder::pushColor(const Vec4& c, int index)
{
    u32 packed = PackColor(c);
    v80[index].v.push_back(packed);
}

// @ 0x007169a0
void MeshBuilder::addColors(int index, int n, const Vec4* c)
{
    EAVec<u32>& v = v80[index].v;
    v.reserve((int)(v.mpEnd - v.mpBegin) + n);
    for (int i = 0; i < n; ++i) {
        u32 packed = PackColor(c[i]);
        v.push_back(packed);
    }
}

// ---------------------------------------------------------------------------
// differences against existing vertices, appended to the 0x50-byte elements
// ---------------------------------------------------------------------------

// @ 0x00716fc0
void MeshBuilder::addDiff134_lo(int slot, int n, const Vec3* pts)
{
    for (int i = 0; i < n; ++i) {
        int index = n168 + i;
        const Vec3& base = *(const Vec3*)((char*)v8.v.mpBegin + index * 0xc);
        float dx = pts[i].x - base.x;
        float dy = pts[i].y - base.y;
        float dz = pts[i].z - base.z;
        Elem134& e = p134[slot];
        e.u0.push_back((u32)index);
        Vec3 d; d.x = dx; d.y = dy; d.z = dz;
        e.v14.push_back(d);
    }
}

// @ 0x007170e0
void MeshBuilder::addDiff134_hi(int slot, int n, const Vec3* pts)
{
    for (int i = 0; i < n; ++i) {
        int index = n16c + i;
        const Vec3& base = *(const Vec3*)((char*)v1c.v.mpBegin + index * 0xc);
        float dx = pts[i].x - base.x;
        float dy = pts[i].y - base.y;
        float dz = pts[i].z - base.z;
        Elem134& e = p134[slot];
        e.u28.push_back((u32)index);
        Vec3 d; d.x = dx; d.y = dy; d.z = dz;
        e.v3c.push_back(d);
    }
}

// @ 0x00717200
void MeshBuilder::addDiff134_lo1(int slot, int index, const Vec3* pt)
{
    int idx = n168 + index;
    const Vec3& base = *(const Vec3*)((char*)v8.v.mpBegin + idx * 0xc);
    Vec3 d;
    d.x = pt->x - base.x;
    d.y = pt->y - base.y;
    d.z = pt->z - base.z;
    Elem134& e = p134[slot];
    e.u0.push_back((u32)idx);
    e.v14.push_back(d);
}

// @ 0x007172f0
void MeshBuilder::addDiff134_hi1(int slot, int index, const Vec3* pt)
{
    int idx = n16c + index;
    const Vec3& base = *(const Vec3*)((char*)v1c.v.mpBegin + idx * 0xc);
    Vec3 d;
    d.x = pt->x - base.x;
    d.y = pt->y - base.y;
    d.z = pt->z - base.z;
    Elem134& e = p134[slot];
    e.u28.push_back((u32)idx);
    e.v3c.push_back(d);
}

// ---------------------------------------------------------------------------
// EH copy constructors (partial reconstructions)
// ---------------------------------------------------------------------------

// @ 0x00716110
void MeshBuilder::copyFrom410(const MeshBuilder& src)
{
    // Approximate: the original copies each vector with EH vector-copy-constructor
    // iterators.  See partial.txt.
    *(u32*)&pad0[0] = *(u32*)&src.pad0[0];
    v8.v.mpBegin = 0;
    v8.v.mpEnd = 0;
    v8.v.mpCapacity = 0;
    v1c.v.mpBegin = 0;
    v1c.v.mpEnd = 0;
    v1c.v.mpCapacity = 0;
}

// @ 0x007162b0
void MeshBuilder::copyFrom2b0(const MeshBuilder& src)
{
    v8.v.mpBegin = 0;
    v8.v.mpEnd = 0;
    v8.v.mpCapacity = 0;
    v1c.v.mpBegin = 0;
    v1c.v.mpEnd = 0;
    v1c.v.mpCapacity = 0;
}
