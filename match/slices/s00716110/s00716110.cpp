// Slice s00716110: SP::cMeshBuilder member helpers (vector push/reserve/color-pack)
// and its EH copy constructors.  Built /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast.
// This region (SporeEP1_RL) is not in the 2008 dev PDB; the class layout was read
// from the constructor's member stores and the accessors below.
#include <stddef.h>
#include <string.h>
#include <new>
#include <xmmintrin.h>

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
    // The retail tail keeps everything in xmm0 (xorps/maxss/mulss/minss/cvtss2si) and
    // never writes another vector register.  Evaluate the clamp in x87 (double compares)
    // so no extra xmm register is materialised, then materialise only xmm0 for the final
    // round-to-nearest conversion the original uses (cvtss2si, not truncation).
    double d = (double)f * 255.0;
    if (d > 255.0 || !(d <= 255.0))
        d = 255.0;                            // NaN and +inf clamp high, like minss
    else if (d < 0.0)
        d = 0.0;
    float t = (float)d;
    return (u8)_mm_cvtss_si32(_mm_load_ss(&t));
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

// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct I {
    void DoInsertValue();   // 0x00715350 (equiv t2; aligned twin 0x004558a0)
};
struct M {
    void DoInsertValue();   // 0x00455660 (equiv t2)
    void reserve();   // 0x004e0880 (equiv t2)
};
struct UVec3 {
    void DoInsertValue();   // 0x004b5ad0 (equiv t2)
    void reserve();   // 0x00473890 (equiv t2)
};
}

namespace __equiv_ann2 {   // address annotations for the equivalence checker; never referenced
struct I {
    void reserve();   // 0x00714cd0 (equiv t2)
};
}

// ===========================================================================
// The two functions this slice still owes are compiler-generated copy
// constructors of the two element types of SP::cMeshBuilder's arrays:
//   0x00716110  cBuilderSection::cBuilderSection(const cBuilderSection&)   (0xd0-byte element)
//   0x007162b0  cMorphTarget::cMorphTarget(const cMorphTarget&)             (0x50-byte element)
// They are the functions the 0xd0- and 0x50-stride uninitialized_copy /
// fill helpers around 0x007163c0 call.  Both are plain member-wise copies:
// scalars, inlined eastl-vector copies for the int vectors, out-of-line
// eastl-vector copies for the cSPVector3 ones, and
// __eh_vector_copy_constructor_iterator_ runs for the section's two arrays.
//
// Residual (see nonmatching.txt): cl's register allocator colours two short-lived
// memcpy/address temps opposite to retail, so 0x007162b0 is 205 == 205 bytes with a
// 6-byte register swap and 0x00716110 is 402 vs 403 bytes.  The shape below (named
// destination local, count + byte-count locals) is the closest of ~25 source variants.
// ===========================================================================

struct cSPVector2 { float x, y; };
struct cSPVector3 { float x, y, z; };
struct tMDUByte4  { u32 mValue; };

// 8-byte allocator carried inside every vector of this region
// (eastl::sp_vector_allocator : eastl::allocator, whose mpName sits at +0x0)
struct spVectorAlloc { u32 mpName; u32 mExtra; };

// 0x14-byte eastl::vector<T, sp_vector_allocator>.  The original inlines the copy ctor of
// the int instantiation -- whose allocation helper stays an out-of-line call (0x004aa350) --
// but calls the cSPVector3 one out of line (0x00473460), so the two are modelled separately.
template<class T> struct spVecInl {
    T*            mpBegin;      // +0x00
    T*            mpEnd;        // +0x04
    T*            mpCapacity;   // +0x08
    spVectorAlloc mAlloc;       // +0x0c
    void DoAlloc(int n, const spVectorAlloc& a);   // 0x004aa350
    spVecInl() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~spVecInl();                                   // non-trivial: the buffer is freed
    spVecInl(const spVecInl& x) {
        int n = (int)(x.mpEnd - x.mpBegin);
        DoAlloc(n, x.mAlloc);
        int bytes = (int)((char*)x.mpEnd - (char*)x.mpBegin);
        T* d = mpBegin;
        mpEnd = (T*)memcpy(d, x.mpBegin, (size_t)bytes) + (bytes >> 2);
    }
};

template<class T> struct spVecExt {
    T*            mpBegin;      // +0x00
    T*            mpEnd;        // +0x04
    T*            mpCapacity;   // +0x08
    spVectorAlloc mAlloc;       // +0x0c
    spVecExt(const spVecExt& x);   // 0x00473460: out of line in the original
    ~spVecExt();
};

// element of SP::cMeshBuilder::mSections
struct cBuilderSection {
    u32                  mVertexFormat;      // +0x00
    int                  mNumVertices;       // +0x04
    spVecInl<int>        mPositionIndices;   // +0x08
    spVecInl<int>        mNormalIndices;     // +0x1c
    spVecExt<cSPVector2> mTexCoordIndices[4];// +0x30
    spVecExt<tMDUByte4>  mColorIndices[2];   // +0x80
    spVecInl<int>        mAttribIndices;     // +0xa8
    spVecInl<int>        mVertIndices;       // +0xbc
};

// element of SP::cMeshBuilder::mMorphTargets
struct cMorphTarget {
    spVecInl<int>        mPositionIndices;   // +0x00
    spVecExt<cSPVector3> mPositionDeltas;    // +0x14
    spVecInl<int>        mNormalIndices;     // +0x28
    spVecExt<cSPVector3> mNormalDeltas;      // +0x3c
};

// These exist only so the compiler emits the two implicit copy constructors under test.
// 0x00716110 cBuilderSection::cBuilderSection
__declspec(noinline) void* ForceCopySection(void* p, const cBuilderSection& x)
{
    return new (p) cBuilderSection(x);
}
// 0x007162b0 cMorphTarget::cMorphTarget
__declspec(noinline) void* ForceCopyMorph(void* p, const cMorphTarget& x)
{
    return new (p) cMorphTarget(x);
}
