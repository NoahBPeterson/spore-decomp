// src/game/SPTerrain/_at_00fa0000.cpp -- migrated from slice(s) s00faf4e0, s00fae800, s00fadc20, s00fad550, s00fac5c0 by tools/migrate/rewrite.py
// Object file: SPTerrain/_at_00fa0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cTerrainSphereDecal.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
#include <math.h>
#include <xmmintrin.h>
#include "rw/graphics/IndexBuffer.h"
#include "rw/graphics/Mesh.h"
#include "rw/graphics/VertexBuffer.h"
#include "rw/graphics/VertexDescriptor.h"
#include <string.h>
#include <intrin.h>
#include <float.h>
#pragma intrinsic(_InterlockedExchangeAdd)

// ---- items of slice s00fac5c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct FaceQuad {
    void AddDecal(void* pOwner);                // 0x00fb4a50
    void RemoveDecal(void* pOwner);             // 0x00fb3660
};
struct QuadMesh {
    char pad[0x118];
    FaceQuad* mFaces[6];                        // +0x118
};
struct DecalHost {
    char pad0[0x78];                            // +0x0
    QuadMesh* mpMesh;                           // +0x78
    char pad1[0xb8 - 0x7c];                     // +0x7c
    uint32_t mFlags;                            // +0xb8

    void AttachDecal();                         // 0x00facfc0
    void DetachDecal();                         // 0x00fad000
};
struct BoxElem {
    uint32_t mKey;                              // +0x0
    float mVal[4];                              // +0x4
};
void CopyBoxElemsChecked(const BoxElem* pFirst, const BoxElem* pLast, BoxElem* pDst);
void CopyBoxElems(const BoxElem* pFirst, const BoxElem* pLast, BoxElem* pDst);
void CopyBoxElemsBackward(const BoxElem* pFirst, const BoxElem* pLast, BoxElem* pDstEnd);
// ---- items of slice s00fac5c0 end

// ---- items of slice s00fad550 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long _InterlockedDecrement(volatile long* p);
extern const float    kF_16ca628;                    // 0x16ca628
extern const float    kF_16ca62c;                    // 0x16ca62c
extern const float    kF_16ca630;                    // 0x16ca630
extern const float    kF_16ca5c4;                    // 0x16ca5c4
extern const float    kF_16ca5c8;                    // 0x16ca5c8
extern const float    kF_16ca5cc;                    // 0x16ca5cc
extern const float    kF_16ca5d0;                    // 0x16ca5d0
extern const float    kF_16ca5d4;                    // 0x16ca5d4
extern const float    kF_16ca5d8;                    // 0x16ca5d8
extern const float    kF_16ca5dc;                    // 0x16ca5dc
extern const float    kF_15b14f8;                    // 0x15b14f8
extern const float    kF_15b14fc;                    // 0x15b14fc
extern const float    kF_15b1500;                    // 0x15b1500
extern const float    kF_15b1504;                    // 0x15b1504
extern const float    kF_15b1508;                    // 0x15b1508
extern const float    kF_15b150c;                    // 0x15b150c
extern char           kVtbl_1491090;                 // 0x1491090
extern "C" void* FUN_00fad040(void* first, void* last, void* dst);
extern "C" void  FUN_00fad0f0(void* dst, void* first, void* last);
extern "C" void  FUN_00fad0a0(void* a, void* b, void* c);
typedef unsigned short u16;
typedef unsigned int   u32;
struct Vector4 {
    float x, y, z, w;
};
struct Matrix33 {
    float m[9];
    void  Assign(const Matrix33& src);
};
struct DecalEntry {
    int     m_index;    // +0x00
    Vector4 m_box;      // +0x04
};
struct DecalEntryVector {
    DecalEntry* mBegin;     // +0x00
    DecalEntry* mEnd;       // +0x04
    DecalEntry* mCapacity;  // +0x08

    void DoGrow(DecalEntry* pos, const DecalEntry* value);
    void push_back(const DecalEntry& value);
};
struct cTerrainSphereDecal;
struct cDecalHost {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int  GetTarget();                       // vtable slot +0xc
    void         MergeFaceBox(Vector4 box, int index);
};
extern const Matrix33 kMat_16ca604;                  // 0x16ca604
extern "C" void* EAAllocate(u32 size, const char* name, int flags, u32 align,
                            const char* file, int line);
void operator delete(void* p);
struct cTerrainSphereDecal {
    void*       m_vtbl;         // +0x000
    int         m_04;           // +0x004
    u16         m_08;           // +0x008
    u16         m_0a;           // +0x00a
    float       m_0c;           // +0x00c
    float       m_10;           // +0x010
    float       m_14;           // +0x014
    float       m_18;           // +0x018
    Matrix33    m_mat;          // +0x01c
    float       m_40[8];        // +0x040
    float       m_60;           // +0x060
    float       m_64;           // +0x064
    int         m_68;           // +0x068
    int         m_6c;           // +0x06c
    int         m_70;           // +0x070
    int         m_74;           // +0x074
    void*       m_78;           // +0x078
    void*       m_7c;           // +0x07c
    DecalEntry* m_80;           // +0x080
    DecalEntry* m_84;           // +0x084
    int         m_88;           // +0x088
    int         m_8c;           // +0x08c
    int         m_90;           // +0x090
    float       m_94;           // +0x094
    float       m_98;           // +0x098
    int         m_9c;           // +0x09c
    float       m_a0;           // +0x0a0
    float       m_a4;           // +0x0a4
    float       m_a8;           // +0x0a8
    float       m_ac;           // +0x0ac
    float       m_b0;           // +0x0b0
    int         m_b4;           // +0x0b4
    int         m_b8;           // +0x0b8
    int         m_bc[0xc];      // +0x0bc .. +0x0ec
    float       m_ec[7];        // +0x0ec .. +0x108
    float       m_108[3];       // +0x108 .. +0x114
    float       m_114;          // +0x114
    float       m_118[3];       // +0x118 .. +0x124
    float       m_124;          // +0x124
    void*       m_128;          // +0x128

    cTerrainSphereDecal* Construct();
    void  Uninit();
    bool  DispatchStaticDecal(int index, int param3);
    void  Reset();              // 00fad000
};
static void CopyEntry(DecalEntry* dst, const DecalEntry* src)
{
    dst->m_index = src->m_index;
    dst->m_box.x = src->m_box.x;
    dst->m_box.y = src->m_box.y;
    dst->m_box.z = src->m_box.z;
    dst->m_box.w = src->m_box.w;
}
// ---- items of slice s00fad550 end

// ---- items of slice s00fadc20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint8_t gCubeFaceAxes[3][4];   // 0x01491030: {u, v, w, pad}
struct Vector3
{
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}

    Vector3& operator*=(const float& s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }

    float Dot(const Vector3& v) const
    {
        // The original evaluates dot products in SSE (mulss/addss), not on x87.
        __m128 px = _mm_mul_ss(_mm_set_ss(x), _mm_set_ss(v.x));
        __m128 py = _mm_mul_ss(_mm_set_ss(y), _mm_set_ss(v.y));
        __m128 pz = _mm_mul_ss(_mm_set_ss(z), _mm_set_ss(v.z));
        return _mm_cvtss_f32(_mm_add_ss(_mm_add_ss(px, py), pz));
    }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    void Normalize()
    {
        // The original rounds 1/len to float before scaling (it spills it and multiplies in SSE); cl 15.00.30729
        // keeps it on the x87 stack instead, which differs for huge/denormal inputs. The volatile store
        // reproduces the rounding.
        volatile float inv = 1.0f / sqrtf(x * x + y * y + z * z);
        float s = inv;
        *this *= s;
    }
    Vector3 Normalized() const
    {
        Vector3 r(*this);
        r.Normalize();
        return r;
    }
};
static inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
static inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
static inline Vector3 EdgeSub(const Vector3& a, const Vector3& b)
{
    volatile float ax = a.x, ay = a.y, az = a.z;
    volatile float bx = b.x, by = b.y, bz = b.z;
    volatile float x = ax - bx, y = ay - by, z = az - bz;
    return Vector3(x, y, z);
}
static inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
static inline Vector3 operator/(const Vector3& a, float s)
{
    float inv = 1.0f / s;
    return Vector3(a.x * inv, a.y * inv, a.z * inv);
}
struct Plane
{
    Vector3 mNormal;
    float   mD;
    Plane() {}
    __forceinline Plane(const Vector3& normal, const Vector3& point)
    {
        mNormal = normal;
        mNormal.Normalize();
        mD = -mNormal.Dot(point);
    }
};
static inline void IntersectRayPlane(const Plane& plane, const Vector3& origin, const Vector3& dir, Vector3& point)
{
    float denom = dir.Dot(plane.mNormal);
    if (denom != 0.0f)
    {
        float t = -(plane.mNormal.Dot(origin) + plane.mD) / denom;
        if (t >= 0.0f)
            point = dir * t;
    }
}
struct RectF                    // EA::RectT<float>
{
    float mLeft, mTop, mRight, mBottom;
    RectF() {}
    RectF(float l, float t, float r, float b) : mLeft(l), mTop(t), mRight(r), mBottom(b) {}
    bool Intersect(const RectF& a, const RectF& b);     // 0x00634b60
};
template <typename T> inline const T& min_(const T& a, const T& b) { return (b < a) ? b : a; }
template <typename T> inline const T& max_(const T& a, const T& b) { return (a < b) ? b : a; }
struct cFaceCoord
{
    float u, v;
    int   face;
    cFaceCoord(float au, float av, int f) : u(au), v(av), face(f) {}
};
struct cFaceRect
{
    int   mFace;
    RectF mRect;
};
struct cFaceRectVector
{
    cFaceRect* mpBegin;
    cFaceRect* mpEnd;
    cFaceRect* mpCapacity;
    uint32_t   mAllocator;

    void push_back(const cFaceRect& value);             // 0x00fada70
    cFaceRect* erase(cFaceRect* first, cFaceRect* last);
    void clear() { erase(mpBegin, mpEnd); }
};
cFaceRect* copy(cFaceRect* first, cFaceRect* last, cFaceRect* dest);  // 0x00fad0a0 (eastl::copy)
inline cFaceRect* cFaceRectVector::erase(cFaceRect* first, cFaceRect* last)
{
    cFaceRect* const pNewEnd = copy(last, mpEnd, first);
    (void)pNewEnd;
    mpEnd -= (last - first);
    return first;
}
struct cViewRect
{
    uint32_t mUnknown0;
    Vector3  mPosition;     // +0x04: center of the rectangle
    float    mScale;        // +0x10
    Vector3  mRight;        // +0x14
    Vector3  mUp;           // +0x20
};
class cViewFaceCover
{
public:
    void Update(const cViewRect& view, float aspect);

    uint32_t        mPad0[0x20];
    cFaceRectVector mFaceRects;     // +0x80
    uint32_t        mPad90[0x17];
    Vector3         mOrigin;        // +0xec
    Plane           mPlane;         // +0xf8
    Vector3         mUAxis;         // +0x108
    float           mULength;       // +0x114
    Vector3         mVAxis;         // +0x118
    float           mVLength;       // +0x124
};
// ---- items of slice s00fadc20 end

// ---- items of slice s00fae800 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace graphics {
class VertexDescriptor_s00fa_e800 {
public:
    VertexDescriptor_s00fa_e800* m_nextParent;       // +0x00
    VertexDescriptor_s00fa_e800* m_nextSibling;      // +0x04
    void*             m_vertexDeclaration;// +0x08
    unsigned short    m_numElements;      // +0x0c
    unsigned char     m_lockFlags;        // +0x0e
    unsigned char     m_stride;           // +0x0f
    unsigned int      m_elementsUsed;     // +0x10
    unsigned int      m_elementHash;      // +0x14
};
}
}
namespace rw {
namespace graphics {
class VertexBuffer_s00fa_e800 {
public:
    VertexDescriptor_s00fa_e800* m_desc;             // +0x00
    void*             m_d3dVB;            // +0x04
    unsigned int      m_base;             // +0x08
    unsigned int      m_numVertices;      // +0x0c
    unsigned int      m_usage;            // +0x10
    unsigned char     m_stride;           // +0x14
    unsigned char     m_lockFlags;        // +0x15
    unsigned short    m_pad0;             // +0x16
    void*             m_disposableBuffer; // +0x18

    void* D3D9Lock(unsigned int usage, unsigned int size1, unsigned int size2); // 0x011f3620
    VertexBuffer_s00fa_e800* Unlock();                                                     // 0x011f36a0
};
}
}
namespace rw {
namespace graphics {
class IndexBuffer_s00fa_e800 {
public:
    struct Locked { void* mpData; unsigned int mField4; unsigned int mField8; };

    void*         m_d3dIB;            // +0x00
    unsigned int  m_base;             // +0x04
    unsigned int  m_numIndices;       // +0x08
    unsigned int  m_usage;            // +0x0c
    unsigned int  m_fmt;              // +0x10
    unsigned int  m_primType;         // +0x14
    void*         m_disposableBuffer; // +0x18

    IndexBuffer_s00fa_e800* Lock(unsigned int count, Locked& out);  // 0x011f4f20
    IndexBuffer_s00fa_e800* Unlock(Locked& out);                    // 0x011f4fd0
};
}
}
namespace rw {
namespace graphics {
class Mesh_s00fa_e800 {
public:
    unsigned int  m_instancedSize;    // +0x00
    unsigned int  m_primTypeCache;    // +0x04
    IndexBuffer_s00fa_e800*  m_indexBuffer;      // +0x08
    unsigned int  m_primCount;        // +0x0c
    unsigned int  m_numVertexBuffers; // +0x10
    unsigned int  m_start;            // +0x14
    unsigned int  m_numIndices;       // +0x18
    unsigned int  m_minVertex;        // +0x1c
    unsigned int  m_vertexRange;      // +0x20
    VertexBuffer_s00fa_e800* m_vertexBuffer[1];  // +0x24

    void SetVertexBuffer(unsigned int index, VertexBuffer_s00fa_e800* vb); // 0x011f9670
    void SetIndexBuffer(IndexBuffer_s00fa_e800* ib);                       // 0x011f96e0
    void SetNumIndices(unsigned int n);                         // 0x011f96b0
    void D3D9RecalculatePrimCount();                            // 0x011f9710
};
}
}
namespace EA {
template <class T>
struct RectT_s00fa_e800 {
    T x0;
    T y0;
    T x1;
    T y1;
};  // namespace EA
}
namespace SP {
using rw::graphics::IndexBuffer_s00fa_e800;
}
namespace SP {
using rw::graphics::Mesh_s00fa_e800;
}
namespace SP {
using rw::graphics::VertexBuffer_s00fa_e800;
}
namespace SP {
struct cSPVector2 { float x; float y; };
}
namespace SP {
struct cCubeMapCoord_s00fa_e800 {
    float mU;      // +0x0
    float mV;      // +0x4
    int   mFace;   // +0x8
};
}
namespace SP {
class cTerrainMapSet_s00fa_e800 {
public:
    unsigned char mPad00[0x34];
    float mRadius;      // +0x34
    float mMaxHeight;   // +0x38
    float mWaterHeight; // +0x3c
    float mWaterDelta;  // +0x40
    float mBeachHeight; // +0x44
};
}
namespace SP {
class cTerrainSphere_s00fa_e800 {
public:
    virtual void vtable00();
    virtual void vtable04();
    virtual void vtable08();
    virtual cTerrainMapSet_s00fa_e800* GetMapSet();   // +0x0c
    virtual void* GetInfo();               // +0x10

    void MergeFaceBox(unsigned int face, EA::RectT_s00fa_e800<float> box);  // 0x00f98620
};
}
namespace SP {
class cTerrainSphereQuad_s00fa_e800 {
public:
    cTerrainSphere_s00fa_e800*     mSphere;             // +0x00
    cTerrainSphereQuad_s00fa_e800* mParent;             // +0x04
    cTerrainSphereQuad_s00fa_e800* mChildren[4];        // +0x08
    int                 mChunkRes;           // +0x18
    int                 mFace;               // +0x1c
    cSPVector2          mFaceMin;            // +0x20
    cSPVector2          mFaceMax;            // +0x28
    float               mFaceScale;          // +0x30
    unsigned char       mPad34[0x24];
    float               mAtmoU0;             // +0x58
    float               mAtmoV0;             // +0x5c
    float               mAtmoStep;           // +0x60
    unsigned char       mPad64[0x08];
    bool                mAtmoSkip;           // +0x6c
    unsigned char       mPad6D[0x23];
    bool                mDirtyVertices;      // +0x90
    bool                mDirtyIndices;       // +0x91
    unsigned char       mPad92[0x02];
    VertexBuffer_s00fa_e800**      mAtmoVertexBuffer;   // +0x94
    unsigned char       mPad98[0xd8];
    unsigned int*       mAboveBelowMap;      // +0x170
    int                 mAboveBelowMapSize;  // +0x174
    int                 mAboveBelowMapStride;// +0x178

    void MarkVerticesDirty(int face, const float* box);    // 0x00faf140
    void MarkIndicesDirty(int face, const float* box);     // 0x00faf400
    bool BuildAtmosphereVertices();                        // 0x00faf220
    void ClearAboveBelowRange(int row, int col, int res);  // 0x00faf070
};
}
namespace SP {
struct TerrainMeshSlot {
    VertexBuffer_s00fa_e800*    mpVertexBuffer;  // +0x00
    IndexBuffer_s00fa_e800*     mpIndexBuffer;   // +0x04
    TerrainMeshSlot* mpPrev;          // +0x08
    TerrainMeshSlot* mpNext;          // +0x0c
};
}
namespace SP {
struct cTerrainMeshListHolder {
    TerrainMeshSlot* mpHeadA;  // +0x00  (&gTerrainMeshSlots[0])
    TerrainMeshSlot* mpHeadB;  // +0x04  (&gTerrainMeshSlots[0xBFF])
    int              mField8;  // +0x08
    int              mFieldC;  // +0x0c

    cTerrainMeshListHolder();            // 0x00faed90
    void Create(void* device, int res);  // 0x00faeda0
    void Destroy();                      // 0x00faeec0
};
}
namespace SP {
extern int  gIndexBufferDesc;                     // 0x015d07b0
}
namespace SP {
extern void* gTerrainDeviceA;                     // 0x016c9e74
}
namespace SP {
extern void* gTerrainDeviceB;                     // 0x016c9e6c
}
namespace SP {
extern void* gTerrainDeviceC;                     // 0x016c9e3c
}
namespace SP {
extern TerrainMeshSlot gTerrainMeshSlots[0xC00];  // 0x016ca640
}
namespace SP {
extern IndexBuffer_s00fa_e800*  gTerrainAtmosphereIB;        // 0x016d6640
}
namespace SP {
extern VertexBuffer_s00fa_e800* gTerrainAtmosphereVB;        // 0x016d6644
}
namespace SP {
extern Mesh_s00fa_e800*         gTerrainAtmosphereMesh;      // 0x016d6648
}
namespace SP {
Mesh_s00fa_e800* CreateMesh(int flags);                              // 0x00761840
}
namespace SP {
VertexBuffer_s00fa_e800* CreateVertexBuffer(void* device, unsigned int numVertices,
                                 unsigned int a, unsigned int b);  // 0x00762b70
}
namespace SP {
IndexBuffer_s00fa_e800* CreateIndexBuffer(void* desc, unsigned int numIndices,
                               unsigned int maxIndex, unsigned int a,
                               unsigned int b, unsigned int c);    // 0x00762c60
}
namespace SP {
void DestroyVertexBuffer(VertexBuffer_s00fa_e800* vb);                // 0x00762a00
}
namespace SP {
void DestroyIndexBuffer(IndexBuffer_s00fa_e800* ib);                  // 0x00762a30
}
namespace SP {
void MapCubeFaceUV(int* face, float* u, float* v, int a, int b, int c);
}
namespace SP {
void __stdcall SetupTerrainMesh(VertexBuffer_s00fa_e800* vb, IndexBuffer_s00fa_e800* ib,
                                unsigned int start, unsigned int numIndices);
}
namespace SP {
void InitTerrainAtmosphereMesh();
}
namespace SP {
void ShiftTerrainRecords(void* srcBegin, void* srcEnd, void* dstEnd);
}
// ---- items of slice s00fae800 end

// ---- items of slice s00faf4e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_lastFace;                          // 0x015b1538
extern int g_lastKey;                           // 0x015b153c
namespace rw {
namespace graphics {
class CompiledState_s00fa_f4e0
{
public:
    void Dispatch();                                    // 0x011ee580
};
}
}
namespace rw {
namespace graphics {
class RasterState
{
public:
    void Assign(CompiledState_s00fa_f4e0* state, int index, int value);   // 0x00fc27e0
    CompiledState_s00fa_f4e0* mpState;     // +0x00
    int            mIndex;      // +0x04
    int            mValue;      // +0x08
    int            mCached;     // +0x0c
};
}
}
using rw::graphics::CompiledState_s00fa_f4e0;
using rw::graphics::RasterState;
struct cSPVector2_s00fa_f4e0 { float x, y; };
struct cRibbonFaceVertex           // 0x14
{
    cSPVector2_s00fa_f4e0 mPos;               // +0x00
    cSPVector2_s00fa_f4e0 mTC;                // +0x08
    float      mAlpha;             // +0x10
};
struct cRibbonFacePoly
{
    cRibbonFaceVertex* mpBegin;     // +0x00
    cRibbonFaceVertex* mpEnd;       // +0x04
    uint32_t           mPad08[39];  // +0x08 .. +0xa3
    float              mTopV;       // +0xa4
    float              mLengthV;    // +0xa8
    int                mRibbonID;   // +0xac
    float              mMinX;       // +0xb0
    float              mMinY;       // +0xb4
    float              mMaxX;       // +0xb8
    float              mMaxY;       // +0xbc
    cRibbonFaceVertex  mPatch[4];   // +0xc0 .. +0x10f

    void FUN_00fafda0();            // 0x00fafda0
    void FUN_00faff10();            // 0x00faff10
};
template <class T> const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
template <class T> const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
class cTextureInstance
{
public:
    int  mFirst;                    // +0x00
    int  GetRaster();               // 0x0046f260
};
extern cTextureInstance* g_pTextureInstance;    // 0x016c9f58
class cTerrainSphere
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* GetMapSet();      // +0x0c
    virtual void* GetInfo();        // +0x10

    int GetQuadKeyA(int face);      // 0x00f98260
    int GetQuadKeyB(int face);      // 0x00f98270
    int GetQuadKeyC(int face);      // 0x00f98280
    int GetKeyD(int face);          // 0x00f96910
    int GetKeyE();                  // 0x00f96a00
};
class cTerrainSphereQuad
{
public:
    cTerrainSphere* mSphere;            // +0x00
    uint32_t        mPad04[5];          // +0x04 .. +0x17
    int             mChunkRes;          // +0x18
    int             mFace;              // +0x1c
    uint32_t        mPad20[84];         // +0x20 .. +0x16f
    void*           mAboveBelowMap;     // +0x170
    uint32_t        mAboveBelowCount;   // +0x174
    int             mAboveBelowStride;  // +0x178

    void FUN_00faf890();                                        // 0x00faf890
    void FUN_00faf4e0(int key, RasterState* states, int flag);  // 0x00faf4e0
};
void* operator new[](unsigned int size, const char* name, int a, int b, int c, int d);
unsigned int* Memset32(unsigned int* dst, unsigned int value, int count);
int* FUN_00f48a60();                                                    // 0x00f48a60
cRibbonFaceVertex InterpolateRibbonPoly(const cRibbonFacePoly& poly,
                                        const cSPVector2_s00fa_f4e0& facePos);      // 0x00fafb50
char FUN_00faf920(cRibbonFacePoly* poly, float* pOut1, float* pOut2,
                  float v);                                             // 0x00faf920
// ---- items of slice s00faf4e0 end

// @ 0x00fad000
void DecalHost::DetachDecal()
{
    FaceQuad** pFace = mpMesh->mFaces;
    FaceQuad** pFaceEnd = pFace + 6;
    do {
        if (*pFace != 0)
            (*pFace)->RemoveDecal(this);
        ++pFace;
    } while (pFace < pFaceEnd);
    mFlags &= ~0x10u;
}

// @ 0x00fad040
void CopyBoxElemsChecked(const BoxElem* pFirst, const BoxElem* pLast, BoxElem* pDst)
{
    while (pFirst != pLast) {
        if (pDst != 0) {
            pDst->mKey = pFirst->mKey;
            pDst->mVal[0] = pFirst->mVal[0];
            pDst->mVal[1] = pFirst->mVal[1];
            pDst->mVal[2] = pFirst->mVal[2];
            pDst->mVal[3] = pFirst->mVal[3];
        }
        ++pFirst;
        ++pDst;
    }
}

// @ 0x00fad0a0
void CopyBoxElems(const BoxElem* pFirst, const BoxElem* pLast, BoxElem* pDst)
{
    while (pFirst != pLast) {
        pDst->mKey = pFirst->mKey;
        pDst->mVal[0] = pFirst->mVal[0];
        pDst->mVal[1] = pFirst->mVal[1];
        pDst->mVal[2] = pFirst->mVal[2];
        pDst->mVal[3] = pFirst->mVal[3];
        ++pFirst;
        ++pDst;
    }
}

// @ 0x00fad0f0
void CopyBoxElemsBackward(const BoxElem* pFirst, const BoxElem* pLast, BoxElem* pDstEnd)
{
    while (pFirst != pLast) {
        --pFirst;
        --pDstEnd;
        pDstEnd->mKey = pFirst->mKey;
        pDstEnd->mVal[0] = pFirst->mVal[0];
        pDstEnd->mVal[1] = pFirst->mVal[1];
        pDstEnd->mVal[2] = pFirst->mVal[2];
        pDstEnd->mVal[3] = pFirst->mVal[3];
    }
}

// @ 0x00fad730
cTerrainSphereDecal* cTerrainSphereDecal::Construct()
{
    m_08 = 0;
    m_0a = 0;
    m_0c = kF_16ca628;
    m_10 = kF_16ca62c;
    m_14 = kF_16ca630;
    m_18 = 1.0f;
    m_mat.Assign(kMat_16ca604);
    m_40[0] = 1.0f;
    m_40[1] = 1.0f;
    m_40[2] = 1.0f;
    m_40[3] = 1.0f;
    m_40[4] = 1.0f;
    m_40[5] = 1.0f;
    m_40[6] = 1.0f;
    m_40[7] = 1.0f;
    m_60 = 0.0f;
    m_64 = 0.0f;
    m_68 = 0;
    m_6c = 0;
    m_04 = 0;
    m_78 = 0;
    m_7c = 0;
    m_vtbl = &kVtbl_1491090;
    m_74 = -1;
    m_80 = 0;
    m_84 = 0;
    m_88 = 0;
    m_9c = 0;
    m_94 = 0.0f;
    m_98 = 0.0f;
    m_b4 = 0;
    m_b8 = 0;
    m_a0 = 0.0f;
    m_a4 = 0.0f;
    m_a8 = 0.0f;
    m_ac = 0.0f;
    m_b0 = 1.0f;
    m_ec[0] = kF_16ca5c4;
    m_ec[1] = kF_16ca5c8;
    m_ec[2] = kF_16ca5cc;
    m_ec[3] = kF_16ca5d0;
    m_ec[4] = kF_16ca5d4;
    m_ec[5] = kF_16ca5d8;
    m_ec[6] = kF_16ca5dc;
    m_108[0] = kF_15b14f8;
    m_108[1] = kF_15b14fc;
    m_108[2] = kF_15b1500;
    m_114 = 1.0f;
    m_118[0] = kF_15b1504;
    m_118[1] = kF_15b1508;
    m_118[2] = kF_15b150c;
    m_124 = 1.0f;
    m_128 = 0;
    return this;
}

// @ 0x00fad930
void DecalEntryVector::DoGrow(DecalEntry* pos, const DecalEntry* value)
{
    if (mEnd != mCapacity) {
        const DecalEntry* src = value;
        if (src >= pos && src < mEnd)
            src = src + 1;
        if (mEnd)
            CopyEntry(mEnd, mEnd - 1);
        FUN_00fad0f0(pos, mEnd - 1, mEnd);
        CopyEntry(pos, src);
        ++mEnd;
    } else {
        int count = (int)((char*)mEnd - (char*)mBegin) / 0x14;
        int newCap;
        if (count != 0)
            newCap = count * 2;
        else
            newCap = 1;
        DecalEntry* newBuf;
        if (newCap)
            newBuf = (DecalEntry*)EAAllocate(newCap * 0x14, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        else
            newBuf = 0;
        DecalEntry* oldBegin = mBegin;
        DecalEntry* p = (DecalEntry*)FUN_00fad040(oldBegin, pos, newBuf);
        if (p)
            CopyEntry(p, value);
        const DecalEntry* oldEnd = mEnd;
        DecalEntry* newEnd = (DecalEntry*)FUN_00fad040(pos, (void*)oldEnd, p + 1);
        if (mBegin && ((int*)mBegin)[-1] != 0)
            operator delete(mBegin);
        mBegin = newBuf;
        mEnd = newEnd;
        mCapacity = newBuf + newCap;
    }
}

// @ 0x00fada70
void DecalEntryVector::push_back(const DecalEntry& value)
{
    DecalEntry* end = mEnd;
    if (end < mCapacity) {
        mEnd = end + 1;
        if (end)
            CopyEntry(end, &value);
    } else {
        DoGrow(end, &value);
    }
}

// @ 0x00fadac0
void cTerrainSphereDecal::Uninit()
{
    if ((m_b8 >> 3 & 1) == 0) {
        if ((m_b8 >> 4 & 1) != 0)
            Reset();
    } else {
        if ((u32)(((char*)m_84 - (char*)m_80) / 0x14) != 0) {
            u32 i = 0;
            do {
                cDecalHost* host = (cDecalHost*)m_78;
                if (host->GetTarget())
                    host->MergeFaceBox(m_80[i].m_box, m_80[i].m_index);
                host = (cDecalHost*)m_78;
                ++i;
            } while (i < (u32)(((char*)m_84 - (char*)m_80) / 0x14));
        }
    }
    FUN_00fad0a0(m_84, m_84, m_80);
    m_84 -= (int)((char*)m_84 - (char*)m_80) / 0x14;
    m_78 = 0;
    m_7c = 0;
    if (m_128) {
        volatile long* p = (volatile long*)((char*)m_128 + 8);
        m_128 = 0;
        _InterlockedDecrement(p);
        if (_InterlockedExchangeAdd(p, 0) >= 1)
            _InterlockedExchangeAdd(p, 0);
        else
            _InterlockedExchangeAdd(p, 1);
    }
    m_74 = -1;
}

// @ 0x00fadc20
void cViewFaceCover::Update(const cViewRect& view, float aspect)
{
    mFaceRects.clear();

    Vector3 pos = view.mPosition;
    float scale = view.mScale;
    Vector3 right = view.mRight * scale;
    Vector3 up = view.mUp * scale * aspect;

    Vector3 c0 = pos - right + up;
    Vector3 c1 = pos + right + up;
    Vector3 c2 = pos + right - up;
    Vector3 c3 = pos - right - up;

    Vector3 n0 = c0.Normalized();
    Vector3 n1 = c1.Normalized();
    Vector3 n2 = c2.Normalized();
    Vector3 n3 = c3.Normalized();

    mPlane = Plane(pos.Normalized(), pos);

    Vector3 origin(0.0f, 0.0f, 0.0f);
    IntersectRayPlane(mPlane, origin, n3, c3);
    IntersectRayPlane(mPlane, origin, n2, c2);
    IntersectRayPlane(mPlane, origin, n1, c1);

    Vector3 uEdge = EdgeSub(c2, c3);
    Vector3 vEdge = EdgeSub(c1, c2);

    mOrigin = c3;
    mULength = uEdge.Length();
    mUAxis = uEdge / mULength;
    mVLength = vEdge.Length();
    mVAxis = vEdge / mVLength;

    RectF unit(0.0f, 0.0f, 1.0f, 1.0f);

    for (int face = 0; face < 6; ++face)
    {
        cFaceCoord f0(0.0f, 0.0f, face);
        cFaceCoord f1(1.0f, 0.0f, face);
        cFaceCoord f2(1.0f, 1.0f, face);
        cFaceCoord f3(0.0f, 1.0f, face);

        const uint8_t* axes = gCubeFaceAxes[face >> 1];
        float sign = (face & 1) ? -1.0f : 1.0f;
        int u = axes[0];
        int v = axes[1];
        int w = axes[2];

        if (sign * n0[w] < 1e-6f || n1[w] * sign < 1e-6f || n3[w] * sign < 1e-6f || n2[w] * sign < 1e-6f)
            continue;

        float sign2 = sign * sign;
        float inv0 = 1.0f / n0[w];
        float inv1 = 1.0f / n1[w];
        float inv2 = 1.0f / n2[w];
        float inv3 = 1.0f / n3[w];

        f0.u = (n0[u] * inv0 * sign2 + 1.0f) * 0.5f;
        f1.u = (n1[u] * inv1 * sign2 + 1.0f) * 0.5f;
        f2.u = (n2[u] * inv2 * sign2 + 1.0f) * 0.5f;
        f3.u = (n3[u] * inv3 * sign2 + 1.0f) * 0.5f;
        f0.v = (n0[v] * sign * inv0 + 1.0f) * 0.5f;
        f1.v = (n1[v] * sign * inv1 + 1.0f) * 0.5f;
        f2.v = (n2[v] * sign * inv2 + 1.0f) * 0.5f;
        f3.v = (n3[v] * sign * inv3 + 1.0f) * 0.5f;

        RectF r(min_(f2.u, min_(f3.u, min_(f0.u, f1.u))),
                min_(f2.v, min_(f3.v, min_(f0.v, f1.v))),
                max_(f2.u, max_(f3.u, max_(f0.u, f1.u))),
                max_(f2.v, max_(f3.v, max_(f0.v, f1.v))));

        if (r.mLeft < 1.0f && r.mRight > 0.0f && r.mTop < 1.0f && r.mBottom > 0.0f)
        {
            r.Intersect(r, unit);
            cFaceRect fr;
            fr.mFace = face;
            fr.mRect = r;
            mFaceRects.push_back(fr);
        }
    }
}

// @ 0x00faed90
SP::cTerrainMeshListHolder::cTerrainMeshListHolder()
{
    mpHeadA = 0;
    mpHeadB = 0;
    mField8 = 0;
    mFieldC = 0;
}

// @ 0x00faeda0
void SP::cTerrainMeshListHolder::Create(void* device, int res)
{
    int numVertices = (res + 3) * (res + 3);
    int numIndices = (res + 2) * (res + 2) * 6;
    int numPrimitives = numIndices / 3;

    mpHeadA = &SP::gTerrainMeshSlots[0];
    SP::gTerrainMeshSlots[0].mpPrev = 0;
    SP::gTerrainMeshSlots[0].mpNext = &SP::gTerrainMeshSlots[1];
    SP::gTerrainMeshSlots[0].mpVertexBuffer =
        CreateVertexBuffer(device, numVertices, 0, 0);
    SP::gTerrainMeshSlots[0].mpIndexBuffer =
        CreateIndexBuffer(&SP::gIndexBufferDesc, numPrimitives, numIndices, 8, 4, 0);

    mpHeadB = &SP::gTerrainMeshSlots[0xBFF];
    SP::gTerrainMeshSlots[0xBFF].mpPrev = &SP::gTerrainMeshSlots[0xBFE];
    SP::gTerrainMeshSlots[0xBFF].mpNext = 0;
    SP::gTerrainMeshSlots[0xBFF].mpVertexBuffer =
        CreateVertexBuffer(device, numVertices, 0, 0);
    SP::gTerrainMeshSlots[0xBFF].mpIndexBuffer =
        CreateIndexBuffer(&SP::gIndexBufferDesc, numPrimitives, numIndices, 8, 4, 0);

    TerrainMeshSlot* slot = &SP::gTerrainMeshSlots[1];
    do {
        slot->mpVertexBuffer = CreateVertexBuffer(device, numVertices, 0, 0);
        slot->mpIndexBuffer =
            CreateIndexBuffer(&SP::gIndexBufferDesc, numPrimitives, numIndices, 8, 4, 0);
        slot->mpPrev = slot - 1;
        slot->mpNext = slot + 1;
        ++slot;
    } while (slot < &SP::gTerrainMeshSlots[0xBFF]);

    mField8 = 0;
    mFieldC = 0;
}

// @ 0x00faeec0
void SP::cTerrainMeshListHolder::Destroy()
{
    IndexBuffer_s00fa_e800** pp = &SP::gTerrainMeshSlots[0].mpIndexBuffer;
    do {
        if (pp[-1])
            DestroyVertexBuffer((VertexBuffer_s00fa_e800*)pp[-1]);
        pp[-1] = 0;
        if (*pp)
            DestroyIndexBuffer(*pp);
        *pp = 0;
        pp += 4;
    } while ((int)pp < (int)&SP::gTerrainMeshSlots[0xC00].mpIndexBuffer);

    mpHeadA = 0;
    mpHeadB = 0;
    mField8 = 0;
    mFieldC = 0;
}

// @ 0x00faef10
void __stdcall SP::SetupTerrainMesh(VertexBuffer_s00fa_e800* vb, IndexBuffer_s00fa_e800* ib, unsigned int start, unsigned int numIndices)
{
    SP::gTerrainAtmosphereMesh->SetIndexBuffer(ib);
    Mesh_s00fa_e800* mesh = SP::gTerrainAtmosphereMesh;
    unsigned int numVertices = vb->m_numVertices;
    mesh->m_minVertex = 0;
    mesh->m_vertexRange = numVertices;
    SP::gTerrainAtmosphereMesh->SetVertexBuffer(0, vb);
    SP::gTerrainAtmosphereMesh->SetVertexBuffer(1, (VertexBuffer_s00fa_e800*)SP::gTerrainDeviceC);
    SP::gTerrainAtmosphereMesh->SetNumIndices(numIndices);
    SP::gTerrainAtmosphereMesh->m_start = start;
    SP::gTerrainAtmosphereMesh->D3D9RecalculatePrimCount();
}

// @ 0x00faef90
void SP::InitTerrainAtmosphereMesh()
{
    if (SP::gTerrainAtmosphereMesh != 0)
        return;

    SP::gTerrainAtmosphereMesh = CreateMesh(2);

    VertexBuffer_s00fa_e800* secondVB = (VertexBuffer_s00fa_e800*)SP::gTerrainDeviceB;
    SP::gTerrainAtmosphereVB = CreateVertexBuffer(SP::gTerrainDeviceA, 3, 0, 0);
    SP::gTerrainAtmosphereIB = CreateIndexBuffer(&SP::gIndexBufferDesc, 1, 3, 8, 4, 0);

    IndexBuffer_s00fa_e800::Locked locked;
    SP::gTerrainAtmosphereIB->Lock(2, locked);
    unsigned short* indices = (unsigned short*)locked.mpData;
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    SP::gTerrainAtmosphereIB->Unlock(locked);

    Mesh_s00fa_e800* mesh = SP::gTerrainAtmosphereMesh;
    mesh->m_minVertex = 0;
    mesh->m_vertexRange = SP::gTerrainAtmosphereVB->m_numVertices;
    SP::gTerrainAtmosphereMesh->SetVertexBuffer(0, SP::gTerrainAtmosphereVB);
    SP::gTerrainAtmosphereMesh->SetVertexBuffer(1, secondVB);
    SP::gTerrainAtmosphereMesh->SetIndexBuffer(SP::gTerrainAtmosphereIB);
}

// @ 0x00faf070
void SP::cTerrainSphereQuad_s00fa_e800::ClearAboveBelowRange(int row, int col, int res)
{
    int i = col * res + 1;
    int end = i + res;
    if (i >= end)
        return;

    int rowShift = row * res + 1;
    unsigned int clearMask = ~(((1 << res) - 1) << (rowShift % 32));
    int shift = rowShift / 32;

    do {
        int index = mAboveBelowMapStride * i + shift;
        ++i;
        mAboveBelowMap[index] &=
            mAboveBelowMap[mAboveBelowMapSize / 2 + index] | clearMask;
    } while (i < end);
}

// @ 0x00faf100
void SP::ShiftTerrainRecords(void* srcBegin, void* srcEnd, void* dstEnd)
{
    while (srcEnd != srcBegin) {
        srcEnd = (char*)srcEnd - 200;
        dstEnd = (char*)dstEnd - 200;
        memcpy(dstEnd, srcEnd, 200);
    }
}

// @ 0x00faf140
void SP::cTerrainSphereQuad_s00fa_e800::MarkVerticesDirty(int face, const float* box)
{
    if (face != mFace)
        return;

    float cx = (mFaceMin.x + mFaceMax.x) * 0.5f;
    float cy = (mFaceMin.y + mFaceMax.y) * 0.5f;

    if (cx > box[0]) {
        if (cy > box[1] && mChildren[0])
            mChildren[0]->MarkVerticesDirty(face, box);
        if (box[3] >= cy && mChildren[2])
            mChildren[2]->MarkVerticesDirty(face, box);
    }
    if (box[2] >= cx) {
        if (cy > box[1] && mChildren[1])
            mChildren[1]->MarkVerticesDirty(face, box);
        if (box[3] >= cy && mChildren[3])
            mChildren[3]->MarkVerticesDirty(face, box);
    }
    mDirtyVertices = true;
}

// @ 0x00faf220
bool SP::cTerrainSphereQuad_s00fa_e800::BuildAtmosphereVertices()
{
    VertexBuffer_s00fa_e800* vb = *mAtmoVertexBuffer;
    unsigned char stride = vb->m_desc->m_stride;

    unsigned int* data = (unsigned int*)vb->D3D9Lock(
        10, (unsigned int)stride * vb->m_base,
        (unsigned int)stride * vb->m_numVertices);
    if (!data)
        return false;

    int n = mChunkRes + 3;
    unsigned char step2 = vb->m_desc->m_stride;

    mSphere->GetMapSet();
    mSphere->GetMapSet();
    mSphere->GetInfo();

    float step = 1.0f / (float)mChunkRes;
    float negStep = -step;
    float v = negStep;

    if (n > 0) {
        do {
            float u = negStep;
            int cols = n;
            do {
                cCubeMapCoord_s00fa_e800 coord;
                coord.mU = mAtmoStep * u + mAtmoU0;
                coord.mV = mAtmoStep * v + mAtmoV0;
                coord.mFace = mFace;
                if (coord.mU < 0.0f || coord.mV < 0.0f ||
                    coord.mU > 1.0f || coord.mV > 1.0f) {
                    MapCubeFaceUV(&coord.mFace, &coord.mU, &coord.mV, 0, 0, 0);
                }

                // both halves of the packed atmosphere vertex carry the same
                // biased fixed-point cube map coordinate
                unsigned short packed = (unsigned short)((int)coord.mU + 0x8000);
                *data = ((unsigned int)packed << 16) | (unsigned int)packed;

                data = (unsigned int*)((char*)data + step2);
                u += step;
            } while (--cols);
            v += step;
        } while (--n);
    }

    (*mAtmoVertexBuffer)->Unlock();
    return true;
}

// @ 0x00faf400
void SP::cTerrainSphereQuad_s00fa_e800::MarkIndicesDirty(int face, const float* box)
{
    if (face != mFace)
        return;
    if (mAtmoSkip != 0)
        return;

    float cx = (mFaceMin.x + mFaceMax.x) * 0.5f;
    float cy = (mFaceMin.y + mFaceMax.y) * 0.5f;

    if (cx > box[0]) {
        if (cy > box[1] && mChildren[0])
            mChildren[0]->MarkIndicesDirty(face, box);
        if (box[3] >= cy && mChildren[2])
            mChildren[2]->MarkIndicesDirty(face, box);
    }
    if (box[2] >= cx) {
        if (cy > box[1] && mChildren[1])
            mChildren[1]->MarkIndicesDirty(face, box);
        if (box[3] >= cy && mChildren[3])
            mChildren[3]->MarkIndicesDirty(face, box);
    }
    mDirtyIndices = true;
}

// @ 0x00faf4e0
void cTerrainSphereQuad::FUN_00faf4e0(int key, RasterState* states, int flag)
{
    if (g_lastFace == key && mFace == g_lastKey && flag == 0)
        return;

    g_lastFace = key;
    g_lastKey = mFace;

    int* table = FUN_00f48a60();
    int entry = *(int*)((char*)table + 0x5c + key * 4);
    if (entry == 0)
        return;
    CompiledState_s00fa_f4e0* pState = *(CompiledState_s00fa_f4e0**)(entry + 4);
    if (pState == 0)
        return;

    int** base = (int**)((char*)mSphere->GetInfo() + 0x2f4);

    switch (key)
    {
    case 0:
        states[0].Assign(pState, 0, mSphere->GetQuadKeyB(mFace));
        states[1].Assign(pState, 1, *base[3]);
        states[2].Assign(pState, 2, mSphere->GetKeyD(mFace));
        states[3].Assign(pState, 3, g_pTextureInstance->mFirst);
        break;
    case 1:
        states[0].Assign(pState, 0, mSphere->GetQuadKeyB(mFace));
        states[1].Assign(pState, 1, mSphere->GetQuadKeyA(mFace));
        states[2].Assign(pState, 2, mSphere->GetKeyD(mFace));
        break;
    case 2:
        states[0].Assign(pState, 0, mSphere->GetQuadKeyA(mFace));
        states[1].Assign(pState, 1, *base[1]);
        states[2].Assign(pState, 2, *base[0]);
        states[3].Assign(pState, 3, *base[2]);
        states[4].Assign(pState, 4, g_pTextureInstance->mFirst);
        states[5].Assign(pState, 5, mSphere->GetKeyE());
        break;
    case 3:
        states[0].Assign(pState, 0, mSphere->GetQuadKeyB(mFace));
        states[1].Assign(pState, 1, mSphere->GetQuadKeyA(mFace));
        states[2].Assign(pState, 2, *base[6]);
        states[3].Assign(pState, 3, *base[4]);
        states[4].Assign(pState, 4, *base[1]);
        states[5].Assign(pState, 5, *base[5]);
        states[6].Assign(pState, 6, *base[2]);
        states[7].Assign(pState, 7, g_pTextureInstance->mFirst);
        break;
    case 4:
        states[0].Assign(pState, 0, mSphere->GetQuadKeyB(mFace));
        states[1].Assign(pState, 1, mSphere->GetQuadKeyA(mFace));
        states[2].Assign(pState, 2, *base[4]);
        states[3].Assign(pState, 3, *base[7]);
        states[4].Assign(pState, 4, *base[9]);
        states[5].Assign(pState, 5, *base[8]);
        states[6].Assign(pState, 6, g_pTextureInstance->mFirst);
        break;
    case 5:
        states[0].Assign(pState, 0, g_pTextureInstance->mFirst);
        states[1].Assign(pState, 1, *base[12]);
        break;
    case 6:
    case 7:
    case 8:
    case 9:
        states[0].Assign(pState, 0, mSphere->GetQuadKeyB(mFace));
        states[1].Assign(pState, 1, flag);
        states[2].Assign(pState, 2, g_pTextureInstance->GetRaster());
        break;
    case 10:
        {
            int arr[5];
            arr[0] = 0;
            arr[1] = mSphere->GetQuadKeyA(mFace);
            arr[2] = mSphere->GetQuadKeyB(mFace);
            arr[3] = mSphere->GetQuadKeyC(mFace);
            arr[4] = mSphere->GetKeyD(mFace);
            int* t = FUN_00f48a60();
            states[0].Assign(pState, 0, arr[*(int*)((char*)t + 8)]);
        }
        break;
    default:
        break;
    }

    pState->Dispatch();
}

// @ 0x00faf890
void cTerrainSphereQuad::FUN_00faf890()
{
    if (mAboveBelowMap != 0)
    {
        operator delete(mAboveBelowMap);
        mAboveBelowMap = 0;
    }
    int raw = mChunkRes;
    _ReadWriteBarrier();
    int n = raw + 2;
    int q = n / 32 + 1;
    mAboveBelowStride = q;
    unsigned int count = q * n * 2;
    mAboveBelowCount = count;
    mAboveBelowMap = new("Terrain/SphereQuad/mAboveBelowMap", 0, 0, 0, 0) unsigned int[count];
    if (mAboveBelowMap != 0)
        Memset32((unsigned int*)mAboveBelowMap, 0, mAboveBelowCount);
}

// @ 0x00faf920
char FUN_00faf920(cRibbonFacePoly* poly, float* pOut1, float* pOut2, float v)
{
    cRibbonFaceVertex* begin = poly->mpBegin;
    cRibbonFaceVertex* end = poly->mpEnd;
    unsigned int count = (unsigned int)(end - begin);
    if (count < 3)
        return 0;

    bool bVar3 = true;
    bool bVar2 = true;
    for (cRibbonFaceVertex* p = begin; p != end; p++)
    {
        float y = p->mPos.y;
        if (v - 1.52587890625e-05f <= y)
        {
            if (v + 1.52587890625e-05f < y)
            {
                bVar3 = false;
                bVar2 = false;
            }
        }
        else
        {
            bVar3 = true;
            bVar2 = true;
        }
    }

    char cVar8 = 0;
    char local_19 = 0;
    cRibbonFaceVertex* prev = end - 1;
    for (cRibbonFaceVertex* cur = begin; cur != end; cur++)
    {
        float y = cur->mPos.y;
        bool hit;
        if (bVar2)
            hit = (v + 1.0e-08f < y);
        else
            hit = (y < v - 1.0e-08f);
        if (hit)
        {
            float f9 = (v - prev->mPos.y) / (y - prev->mPos.y);
            union { float f; unsigned int u; } fb;
            fb.f = f9;
            if ((fb.u & 0x7fffffffu) > 0x7f800000u)
                f9 = 0.5f;
            float f10 = 1.0f - f9;
            float f14 = y * f9 + prev->mPos.y * f10;
            float f11 = cur->mPos.x * f9 + f10 * prev->mPos.x;
            float f12 = cur->mTC.x * f9 + prev->mTC.x * f10;
            float f13 = cur->mTC.y * f9 + prev->mTC.y * f10;
            float f9b = prev->mAlpha * f10 + cur->mAlpha * f9;
            if (cVar8 == 0 || f11 < pOut1[0])
            {
                pOut1[0] = f11;
                pOut1[1] = f14;
                pOut1[2] = f12;
                pOut1[3] = f13;
                pOut1[4] = f9b;
                cVar8 = local_19;
            }
            if (cVar8 == 0 || (pOut2[0] <= f11 && f11 != pOut2[0]))
            {
                pOut2[0] = f11;
                pOut2[1] = f14;
                pOut2[2] = f12;
                pOut2[3] = f13;
                pOut2[4] = f9b;
            }
            bVar2 = !bVar3;
            cVar8 = 1;
            local_19 = 1;
            bVar3 = bVar2;
        }
        prev = cur;
    }
    return cVar8;
}

// @ 0x00fafb50
cRibbonFaceVertex InterpolateRibbonPoly(const cRibbonFacePoly& poly, const cSPVector2_s00fa_f4e0& facePos)
{
    float f13 = (facePos.x - poly.mPatch[0].mPos.x) /
                (poly.mPatch[1].mPos.x - poly.mPatch[0].mPos.x);
    float f17 = 1.0f - f13;
    float f19 = poly.mPatch[1].mPos.y * f13 + poly.mPatch[0].mPos.y * f17;

    float f15 = (facePos.x - poly.mPatch[2].mPos.x) /
                (poly.mPatch[3].mPos.x - poly.mPatch[2].mPos.x);
    float f18 = 1.0f - f15;
    float f16 = poly.mPatch[3].mPos.y * f15 + poly.mPatch[2].mPos.y * f18;

    float f14 = (facePos.y - f19) / (f16 - f19);
    float f20 = 1.0f - f14;

    cRibbonFaceVertex v;
    v.mPos.x = (poly.mPatch[3].mPos.x * f15 + poly.mPatch[2].mPos.x * f18) * f14 +
               f20 * (poly.mPatch[1].mPos.x * f13 + poly.mPatch[0].mPos.x * f17);
    v.mPos.y = f16 * f14 + f20 * f19;
    v.mTC.x = (poly.mPatch[3].mTC.x * f15 + poly.mPatch[2].mTC.x * f18) * f14 +
              f20 * (poly.mPatch[1].mTC.x * f13 + poly.mPatch[0].mTC.x * f17);
    v.mTC.y = (poly.mPatch[3].mTC.y * f15 + poly.mPatch[2].mTC.y * f18) * f14 +
              (poly.mPatch[1].mTC.y * f13 + poly.mPatch[0].mTC.y * f17) * f20;
    v.mAlpha = (poly.mPatch[2].mAlpha * f18 + poly.mPatch[3].mAlpha * f15) * f14 +
               f20 * (poly.mPatch[0].mAlpha * f17 + poly.mPatch[1].mAlpha * f13);
    return v;
}

// @ 0x00fafda0
void cRibbonFacePoly::FUN_00fafda0()
{
    float minX = FLT_MAX;
    float maxX = -FLT_MAX;
    float minY = FLT_MAX;
    float maxY = FLT_MAX;

    int n = (int)(mpEnd - mpBegin);
    const cRibbonFaceVertex* base = mpBegin;
    for (unsigned i = 0; i < (unsigned)n; i++)
    {
        float v = base[i].mPos.x;
        if (!(v > minX)) minX = v;
        if (!(maxX > v)) maxX = v;
        v = base[i].mPos.y;
        if (!(v > minY)) minY = v;
        if (!(maxY > v)) maxY = v;
    }

    mMinX = minX;
    mMinY = minY;
    mMaxX = maxX;
    mMaxY = maxY;
}

// @ 0x00faff10
void cRibbonFacePoly::FUN_00faff10()
{
    float local_c = FLT_MAX;
    float local_8 = -1.0f;
    int count = (int)(mpEnd - mpBegin);

    for (int i = 0; i < count; i++)
    {
        local_c = Min(local_c, mpBegin[i].mPos.y);
        local_8 = Max(local_8, mpBegin[i].mPos.y);
    }

    float range = local_8 - local_c;
    FUN_00faf920(this, &mPatch[0].mPos.x, &mPatch[1].mPos.x, range * 0.3f + local_c);
    FUN_00faf920(this, &mPatch[2].mPos.x, &mPatch[3].mPos.x, range * 0.6f + local_c);
}
