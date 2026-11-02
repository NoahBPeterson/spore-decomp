// src/game/SPTerrain/_at_00f60000.cpp -- migrated from slice(s) s00f6df40, s00f6c940, s00f66f80, s00f66050, s00f63a50 by tools/migrate/rewrite.py
// Object file: SPTerrain/_at_00f60000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cTerrainDistributeInfo.h"

// unnamed retail callees and globals (address in the comment)
extern const uint8_t g_swizzle[16];                    // 0x01491464
#include <math.h>
#include "EA/Swarm/cEffectParams.h"
#include "SP/cTerrainMapSet.h"
#include "SP/cTerrainSphere.h"
#include "EA/Swarm/cTransform.h"
#include <new>
#include <float.h>

// ---- items of slice s00f63a50 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
extern const float kFXMaxFloat;     // 0x015b0cb0
}
namespace SP {
struct cCellEffectInfo {            // 0x10
    int   mEffectIndex;             // +0x0
    float mMinHeight;               // +0x4
    float mMaxHeight;               // +0x8
    char  mDistributeType;          // +0xc
    char  mResourceType;            // +0xd
    unsigned char mOverrideSet;     // +0xe

    cCellEffectInfo()
        : mEffectIndex(-1), mMinHeight(0.0f), mMaxHeight(kFXMaxFloat),
          mDistributeType((char)0xff), mResourceType((char)0xff), mOverrideSet(0) {}
};
}
namespace SP {
extern "C" cCellEffectInfo* __cdecl eastl_copy(const cCellEffectInfo* first,
                                               const cCellEffectInfo* last,
                                               cCellEffectInfo* dst);
}
namespace SP {
struct EffectVector {
    cCellEffectInfo* mpBegin;       // +0x0
    cCellEffectInfo* mpEnd;         // +0x4
    cCellEffectInfo* mpCapacity;    // +0x8
    int mAllocator[2];              // +0xc

    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }

    EffectVector& operator=(const EffectVector& rhs);   // 0x00f63570
    void DoInsertValues(cCellEffectInfo* pos, unsigned n, const cCellEffectInfo& v); // 0x0088fe00
    void resize(unsigned n);                            // 0x00f63ab0

    cCellEffectInfo* erase(cCellEffectInfo* first, cCellEffectInfo* last)
    {
        eastl_copy(last, mpEnd, first);
        mpEnd -= (last - first);
        return first;
    }

    void resize_inline(unsigned n)
    {
        if (n > size())
            DoInsertValues(mpEnd, n - size(), cCellEffectInfo());
        else
            erase(mpBegin + n, mpEnd);
    }
};
}
namespace SP {
struct cLevelInfo {                 // 0x28 (retail; the 2008 PDB says 0x20)
    float mActiveDist;              // +0x0
    float mChildActiveDist;         // +0x4
    float mActiveFacing;            // +0x8
    float mChildActiveFacing;       // +0xc
    float mExtra;                   // +0x10
    EffectVector mEffectInfo;       // +0x14

    cLevelInfo& operator=(const cLevelInfo& rhs)
    {
        mActiveDist = rhs.mActiveDist;
        mChildActiveDist = rhs.mChildActiveDist;
        mActiveFacing = rhs.mActiveFacing;
        mChildActiveFacing = rhs.mChildActiveFacing;
        mExtra = rhs.mExtra;
        mEffectInfo = rhs.mEffectInfo;
        return *this;
    }
};
}
namespace SP {
struct cCell {                      // 0x18
    unsigned short mMinHeight;      // +0x0
    unsigned short mMaxHeight;      // +0x2
    unsigned short mTypeMask;       // +0x4
    short mActiveSlot;              // +0x6
    short mActiveChildren;          // +0x8
    float mDirX, mDirY, mDirZ;      // +0xc
};
}
namespace SP {
class cHeightRanges { public:
    int mFaceSize;                      // +0x00
    int mLevelOffsets[5];               // +0x04
    int* mCellData;                     // +0x18
};
}
namespace SP {
struct cTerrainDistributeInfo_s00f6_3a50 {
    int mFaceSize;                      // +0x00
    int mLevelOffsets[5];               // +0x04
    cCell* mCellData;                   // +0x18
};
}
namespace SP {
class cDistGrid { public:                      // 0x108+
    void* mWorld;                       // +0x00
    int   mCollectionIndex;             // +0x04
    int   mFaceSize;                    // +0x08
    cLevelInfo* mLevelInfo;             // +0x0c
    int   mLevelOffsets[5];             // +0x10
    cCell* mCellData;                   // +0x24
    void* mTerrainMapSet;               // +0x28
    float mHeightBase;                  // +0x2c
    float mHeightRange16;               // +0x30
    void* mActiveCellSlots[8];          // +0x34 (slot_deque, 0x24 bytes) ... +0x54
    void* mSlots[8];                    // +0x54
    float mDistInfo0;                   // +0x74
    float mDistInfo1;                   // +0x78
    cTerrainDistributeInfo_s00f6_3a50* mDistInfo;  // +0xa0
    uint32_t mPadA4;                    // +0xa4

    void Init(cLevelInfo* level, int collectionIndex);
    void SetTerrainMapSet(void* mapset);
    void ReleaseSlots();
    int* CellIndex(int level, int face, unsigned char a, unsigned char b);
};
}
extern const uint8_t g_swizzle[16];                    // 0x01491464
// ---- items of slice s00f63a50 end

// ---- items of slice s00f66050 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cFormatInfo {
    uint8_t  mPad00[0xf];                    // +0x00
    uint8_t  mIndexStride;                   // +0x0f
};
}
namespace SP {
class cMeshBuffer {                          // 0x10 (vertex/index buffer interface)
public:
    void* Lock(unsigned int type, unsigned int first, unsigned int count);  // 0x011F3620
    cFormatInfo* mpFormat;                   // +0x00
    uint32_t mPad04;                         // +0x04
    int mBaseIndex;                          // +0x08
    int mCapacity;                           // +0x0c
};
}
namespace SP {
class cDistCellMesh {                        // 0x34
public:
    void Init(const void* desc, int indexCount, int numCells);
    ~cDistCellMesh();
    bool LockItems(int* pOut, void* unused, int count, int param);

    uint32_t mPad00;                         // +0x00
    void*    mTexture;                       // +0x04
    cMeshBuffer* mBuffer;                    // +0x08
    void*    mDynamicBuffer;                 // +0x0c
    void*    mMesh;                          // +0x10
    int      mIndexCount;                    // +0x14 (capacity in entries)
    int      mBaseOffset;                    // +0x18 (next free entry)
    int      mNumCells;                      // +0x1c
    uint32_t mPad20;                         // +0x20
    int      mItemCount;                     // +0x24
    uint32_t mPad28;                         // +0x28
    int      mParam;                         // +0x2c
    int      mFlag;                          // +0x30
};
}
// ---- items of slice s00f66050 end

// ---- items of slice s00f66f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_c_1488874;                // 0x01488874 = 0.1f
extern float g_c_13fff7c;                // 0x013fff7c = 0.35f
extern float g_c_1485544;                // 0x01485544 = 0.75f
void* __cdecl RWVertexBufferUnlock(void* self);                                                   // 0x011f36a0
void  __cdecl RWCompiledStateDispatch(void* cs);                                                  // 0x011ee580
void  __cdecl RWGlobalStateD3D9Sync();                                                            // 0x011f21a0
int   __cdecl RWVertexDescriptorAreEqual(void* a, void* b);                                       // 0x011f2e70
void  __cdecl FUN_011f2bc0(void* vd);                                                             // 0x011f2bc0
struct VBi {
    void*    mpBuffer;    // +0x00  byte +0x0f is the stride
    int32_t  mPad04;      // +0x04
    int32_t  mOffset;     // +0x08
    int32_t  mCount;      // +0x0c
    unsigned Lock(unsigned pool, unsigned offset, unsigned size);  // 0x011f3620
};
struct IBuf {
    int LockIndex(IBuf* self, int offset, int count, int* out, unsigned flags);  // 0x2c slot
};
struct IBufWrap {
    IBuf*   mpObject;     // +0x00
    int32_t mBase;        // +0x04
};
struct TerrainDraw {
    void**  mpVtbl;      // +0x00
    void*   mpVb;        // +0x04
    void*   mpIb;        // +0x08
    void*   mpIb2;       // +0x0c
    void*   mpShader;    // +0x10
    int32_t mStart0;     // +0x14
    int32_t mCount0;     // +0x18
    int32_t mStart1;     // +0x1c
    int32_t mCount1;     // +0x20
    int32_t mBase0;      // +0x24
    int32_t mBase1;      // +0x28
    void*   mpParam;     // +0x2c
    int32_t mLockState;  // +0x30

    char BuildIndexed(unsigned* pa, void* unused, int vertCount, int* pd, int indexCount, void* param);  // 0x00f66f80
    int  Draw(void* compiledState, void* out);                                              // 0x00f67070
    void Advance();                                                                         // 0x00f67290
    void Init(void* a, void* b, void* c);                                                   // 0x00f66d20
    void Deinit();                                                                          // 0x00f66e70
};
struct TerrainFace {
    char raw[0x300];
    void SetDepth(float d);        // 0x00f67540
    void ClearDepth();             // 0x00f67560
    void SetLodByte(int slot, unsigned char v);  // 0x00f67580
    void Draw(int slot, void* a3); // 0x00f67810
    float GetDepth();              // 0x00f678d0
    void MergeRectA(int slot, float* r);  // 0x00f67900
    void MergeRectB(int slot, float* r);  // 0x00f679b0
    float ProjectDir(float dx, float dy, float dz);  // 0x00f67aa0
    void ClearSprites();           // 0x00f67da0
};
// ---- items of slice s00f66f80 end

// ---- items of slice s00f6c940 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double FUN_007d45d0(float lo, float hi);
typedef unsigned char u8;
typedef unsigned int  u32;
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    float& operator[](int i) { return (&x)[i]; }
};
static inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
static inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
static inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
static inline Vector3 operator-(const Vector3& a) { return Vector3(-a.x, -a.y, -a.z); }
static inline float Dot(const Vector3& a, const Vector3& b)
{
    float s = a.x * b.x;
    s += a.y * b.y;
    s += a.z * b.z;
    return s;
}
static inline Vector3 Cross(const Vector3& a, const Vector3& b)
{
    return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
static inline float Length(const Vector3& v) { return sqrtf(Dot(v, v)); }
static inline Vector3 Normalized(const Vector3& v) { return v * (1.0f / Length(v)); }
struct Quaternion { float x, y, z, w; };
struct Plane {
    Vector3 n;
    float   d;
    // Ray (origin, dir) / plane intersection; t >= 0 only.
    bool Intersect(const Vector3& origin, const Vector3& dir, float& t) const
    {
        float denom = Dot(n, dir);
        if (denom != 0.0f) {
            t = -((Dot(n, origin) + d) / denom);
            if (t >= 0.0f)
                return true;
        }
        return false;
    }
};
struct BoundingBox {
    Vector3 lo;
    Vector3 hi;
    BoundingBox() : lo(FLT_MAX, FLT_MAX, FLT_MAX),
                    hi(-FLT_MAX, -FLT_MAX, -FLT_MAX) {}
    explicit BoundingBox(const Vector3& p) : lo(p), hi(p) {}
    bool IsEmpty() const { return lo.x > hi.x; }
    void Extend(const Vector3& p);              // 0x0041bd50 (out of line)
    __forceinline void ExtendInline(const Vector3& p)       // same body, inlined in the clip loop
    {
        if (IsEmpty()) {
            lo = p;
            hi = p;
            return;
        }
        if (lo.x > p.x) lo.x = p.x;
        else if (hi.x < p.x) hi.x = p.x;
        if (lo.y > p.y) lo.y = p.y;
        else if (hi.y < p.y) hi.y = p.y;
        if (lo.z > p.z) lo.z = p.z;
        else if (hi.z < p.z) hi.z = p.z;
    }
};
struct ClipVertex {
    Vector3 pos;
    float   extra[4];
};
struct Decal {                      // param_4
    char    pad00[6];
    char    noRandomSpin;           // +0x06
    char    pad07[0x2c - 7];
    Plane   plane;                  // +0x2c
    char    pad3c[4];
    Vector3 origin;                 // +0x40
    Vector3 axisU;                  // +0x4c
    float   sizeU;                  // +0x58
    Vector3 axisV;                  // +0x5c
    float   sizeV;                  // +0x68
};
struct CubeTarget {                 // param_5
    char pad00[0x60];
    u32  width;                     // +0x60
    u32  height;                    // +0x64
    u32  depth;                     // +0x68
};
struct FaceRect { float minU, minV, maxU, maxV; };
extern "C" const Vector3    DAT_015b0df8;       // base axis U
extern "C" const Vector3    DAT_015b0e04;       // base axis V
extern "C" const Vector3    DAT_015b0e10;       // random-spin axis
extern "C" const Vector3    DAT_016d6fa8[6][4]; // side-plane normals per cube face
extern "C" const u8         DAT_0148f608[6 / 2][4]; // per-axis component permutation
Vector3 FUN_0059aed0(const Vector3& v, const Quaternion& q);    // 0x0059aed0 rotate v by q
void    FUN_00fc2c70(ClipVertex* poly, int* count, const Vector3* planeNormal); // 0x00fc2c70 clip
static __forceinline int CubeFaceUV(const Vector3& d, float& u, float& v)
{
    float ax = fabsf(d.x);
    float ay = fabsf(d.y);
    float az = fabsf(d.z);
    if (az < ax || az < ay) {
        if (ay < ax) {
            u = (d.y / d.x + 1.0f) * 0.5f;
            v = (d.z / ax + 1.0f) * 0.5f;
            return d.x < 0.0f ? 3 : 2;
        }
        u = (d.z / d.y + 1.0f) * 0.5f;
        v = (d.x / ay + 1.0f) * 0.5f;
        return d.y < 0.0f ? 5 : 4;
    }
    u = (d.x / d.z + 1.0f) * 0.5f;
    v = (d.y / az + 1.0f) * 0.5f;
    return d.z < 0.0f ? 1 : 0;
}
class DecalProjector {
public:
    void BuildDecal(const Vector3* pos, const Quaternion* orient, float size, Decal* decal,
                    CubeTarget* target, u32 arg6, u32 arg7, float spinRange, FaceRect* rects,
                    u32 arg10);
    // 0x00f6c600
    void EmitFace(CubeTarget* target, Vector3* pts, int count, int face, Decal* decal,
                  FaceRect* rect, u32 arg10, u32 arg6);
};
// ---- items of slice s00f6c940 end

// ---- items of slice s00f6df40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
#pragma intrinsic(memcpy, memset)
#pragma intrinsic(fabs)
struct cSPVector3_s00f6_df40 {
    float x, y, z;
    cSPVector3_s00f6_df40() {}
    cSPVector3_s00f6_df40(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3_s00f6_df40(const cSPVector3_s00f6_df40& o) : x(o.x), y(o.y), z(o.z) {}
};
struct AABox {   // min/max box, empty while min.x > max.x
    cSPVector3_s00f6_df40 mMin;
    cSPVector3_s00f6_df40 mMax;
    void Extend(const cSPVector3_s00f6_df40& p) {
        if (mMin.x > mMax.x) {
            mMin = p;
            mMax = p;
        } else {
            if (mMin.x > p.x) mMin.x = p.x;
            else if (p.x > mMax.x) mMax.x = p.x;
            if (mMin.y > p.y) mMin.y = p.y;
            else if (p.y > mMax.y) mMax.y = p.y;
            if (mMin.z > p.z) mMin.z = p.z;
            else if (p.z > mMax.z) mMax.z = p.z;
        }
    }
};
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
extern "C" void* __cdecl memset(void*, int, size_t);
// ---- items of slice s00f6df40 end

// @ 0x00f63da0
int* SP::cDistGrid::CellIndex(int level, int face, unsigned char a, unsigned char b)
{
    int t = g_swizzle[b >> 4] * 2 | g_swizzle[a >> 4];
    t = t << 7 | g_swizzle[b & 0xf];
    t = t << 1 | g_swizzle[a & 0xf];
    return ((SP::cHeightRanges*)this)->mCellData +
           (t + ((SP::cHeightRanges*)this)->mLevelOffsets[level] +
            ((SP::cHeightRanges*)this)->mFaceSize * face);
}

// @ 0x00f66ef0
bool SP::cDistCellMesh::LockItems(int* pOut, void* unused, int count, int param)
{
    int offset = mBaseOffset;
    int type = 10;
    if (count > mIndexCount - offset) {
        type = 6;
        offset = 0;
    }
    *pOut = 0;

    SP::cMeshBuffer* buffer = mBuffer;
    int num = count;
    if (!num)
        num = buffer->mCapacity;
    unsigned char stride = buffer->mpFormat->mIndexStride;
    void* p = buffer->Lock(type, (buffer->mBaseIndex + offset) * stride, stride * num);
    if (!p)
        return false;

    mBaseOffset = offset;
    mItemCount = count;
    mParam = param;
    mFlag = 1;
    *pOut = (int)p;
    return true;
}

// @ 0x00f66f80
char TerrainDraw::BuildIndexed(unsigned* pa, void* unused, int vertCount, int* pd, int indexCount, void* param)
{
    int base = mCount0;
    unsigned pool = 10;
    if (mStart0 - base < vertCount) {
        pool = 6;
        base = 0;
    }
    *pa = 0;
    *pd = 0;

    VBi* vb = (VBi*)mpIb;                       // +0x08
    int n = vertCount;
    if (vertCount == 0)
        n = vb->mCount;
    unsigned char stride = *(unsigned char*)((char*)vb->mpBuffer + 0xf);
    void* p = (void*)vb->Lock(pool, (vb->mOffset + base) * stride, stride * n);
    if (!p)
        return 0;

    int vbase = mCount1;
    unsigned pool2 = 0x1000;
    if (mStart1 - vbase < indexCount) {
        pool2 = 0;
        vbase = 0;
    }
    IBufWrap* wrap = (IBufWrap*)mpIb2;          // +0x0c
    IBuf* obj = wrap->mpObject;
    void** vt = *(void***)obj;
    int r = ((int(__thiscall*)(IBuf*, IBuf*, int, int, int*, unsigned))vt[0x2c / 4])(
        obj, obj, (wrap->mBase + vbase) * 2, indexCount, pd, pool2);
    if (r < 0)
        return 0;

    mpParam = param;
    mCount0 = base;
    mBase0 = vertCount;
    mLockState = 1;
    *pa = (unsigned)p;
    mCount1 = vbase;
    mBase1 = indexCount;
    return 1;
}

// @ 0x00f67070
int TerrainDraw::Draw(void* compiledState, void* out)
{
    if (mLockState == 1) {
        RWVertexBufferUnlock(mpVb);
        if (mpIb) {
            void* o = *(void**)mpIb;
            ((void(__thiscall*)(void*))((void**)o)[0x30 / 4])(o);
        }
    }
    mLockState = 2;
    RWCompiledStateDispatch(compiledState);
    RWGlobalStateD3D9Sync();

    void** dev = *(void***)0x016f89d0;
    void* vd = mpShader;
    if (*(void**)0x016f65a0 == 0 || !RWVertexDescriptorAreEqual(*(void**)0x016f65a0, vd))
        *(unsigned*)0x016f9110 |= 0x100000;
    *(void**)0x016f65a0 = vd;
    FUN_011f2bc0(vd);

    ((void(__thiscall*)(void*, void*))((void**)(*(void**)0x016f6568))[0x14 / 4])(*(void**)0x016f6568, mpShader);
    *(unsigned*)0x016f9110 = 0;

    {
        unsigned* vb = (unsigned*)mpVb;
        int iVar5 = vb[1];
        unsigned stride = *(unsigned char*)(*vb + 0xf);
        if (*(int*)0x016f9138 != iVar5 || *(int*)0x016f913c != 0 || *(unsigned*)0x016f9140 != stride) {
            ((void(__thiscall*)(void*, int, int, int, unsigned))((void**)*dev)[0x190 / 4])(dev, 0, iVar5, 0, stride);
            *(int*)0x016f9138 = iVar5;
            *(int*)0x016f913c = 0;
            *(unsigned*)0x016f9140 = stride;
        }
    }
    {
        int i = 1;
        int* p = (int*)0x016f9144;
        do {
            if (*p != 0) {
                ((void(__thiscall*)(void*, int, int, int, int))((void**)*dev)[0x190 / 4])(dev, i, 0, 0, 0);
                p[0] = 0;
                p[1] = 0;
                p[2] = 0;
            }
            p += 3;
            ++i;
        } while ((int)p < 0x16f9168);
    }

    int* ib = (int*)mpIb2;
    if (ib == 0 && mpIb != 0) {
        if (mpIb != (void*)1)
            ib = 0;
        else
            ib = *(int**)0x016c9698;
    } else if (ib == 0) {
        ib = *(int**)0x016c969c;
    }
    {
        int obj = *ib;
        if (*(int*)0x016f8afc != obj) {
            ((void(__thiscall*)(void*, int))((void**)*dev)[0x1a0 / 4])(dev, obj);
            *(int*)0x016f8afc = obj;
        }
    }

    if (mpParam == (void*)0) {
        int n = mBase0;
        if (n == 0)
            n = mBase1;
        n -= 2;
        int v = mCount1 + ib[1];
        int r = ((int(__thiscall*)(void*, int, int, int, int, int, int))((void**)*dev)[0x148 / 4])(
            dev, 5, mStart1, 0, mBase1, v, n);
        if (r < 0) {
            ((void(__thiscall*)(void*))((void**)*mpVtbl)[0x10 / 4])(this);
            return 0;
        }
    } else if (mpParam == (void*)1) {
        int n = mBase0;
        if (n == 0)
            n = mBase1;
        n /= 3;
        int v = mCount1 + ib[1];
        int r = ((int(__thiscall*)(void*, int, int, int, int, int, int))((void**)*dev)[0x148 / 4])(
            dev, 4, mStart1, 0, mBase1, v, n);
        if (r < 0) {
            ((void(__thiscall*)(void*))((void**)*mpVtbl)[0x10 / 4])(this);
            return 0;
        }
    }

    if (out) {
        *((int*)out + 8) += mBase1;
        if (mBase0 != 0) {
            *((int*)out + 9) += mBase0;
            *((int*)out + 10) += 1;
            return 1;
        }
        *((int*)out + 9) += mBase1;
        *((int*)out + 10) += 1;
    }
    return 1;
}

// @ 0x00f67290
void TerrainDraw::Advance()
{
    char* p = (char*)this;
    *(int*)(p + 0x18) += *(int*)(p + 0x24);
    *(int*)(p + 0x20) += *(int*)(p + 0x28);
    *(int*)(p + 0x30) = 0;
}

// @ 0x00f67540
void TerrainFace::SetDepth(float d)
{
    char* p = (char*)this;
    p[0x158] = 1;
    *(float*)(p + 0x15c) = d;
}

// @ 0x00f67560
void TerrainFace::ClearDepth()
{
    char* p = (char*)this;
    p[0x158] = 0;
    *(float*)(p + 0x15c) = 0.0f;
}

// @ 0x00f67580
void TerrainFace::SetLodByte(int slot, unsigned char v)
{
    char* p = (char*)this;
    if (slot < 0) {
        p[0x78] = (char)v;
        p[0x79] = (char)v;
        p[0x7a] = (char)v;
        p[0x7b] = (char)v;
        p[0x7c] = (char)v;
        p[0x7d] = (char)v;
        return;
    }
    p[0x78 + slot] = (char)v;
}

// @ 0x00f676f0
int __cdecl SelectLod(float* param_1)
{
    float a = param_1[2] - param_1[0];
    float b = param_1[3] - param_1[1];
    float* p = (a < b) ? &b : &a;
    float fVar1 = *p;
    if (fVar1 < g_c_1488874)
        return 0;
    if (fVar1 < g_c_13fff7c)
        return 1;
    if (fVar1 < g_c_1485544)
        return 2;
    return 3;
}

// @ 0x00f6c940
void DecalProjector::BuildDecal(const Vector3* pos, const Quaternion* orient, float size, Decal* decal, CubeTarget* target, u32 arg6, u32 arg7, float spinRange, FaceRect* rects, u32 arg10)
{
    target->width  = 0x200;
    target->height = 0x200;
    target->depth  = 0x200;

    // ---- 1. frame around pos ------------------------------------------------------------
    Vector3 n = Normalized(*pos);
    Vector3 up(0.0f, 0.0f, 1.0f);
    if (Dot(n, Vector3(0.0f, 0.0f, 1.0f)) >= 0.999f)
        up = Vector3(0.0f, 1.0f, 0.0f);
    Vector3 side = Cross(up, *pos);
    Vector3 up2  = -Cross(side, *pos);      // = pos x side; written negated, as the original emits it
    Vector3 fwd  = Normalized(Cross(side, up2));

    Vector3 axisU = DAT_015b0df8;
    Vector3 axisV = DAT_015b0e04;
    if (decal->noRandomSpin == 0 && spinRange != 0.0f) {
        float half = FUN_007d45d0(0.0f, spinRange) * 0.017453292f * 0.5f;
        float s = sinf(half);
        Quaternion spin;
        spin.x = s * DAT_015b0e10.x;
        spin.y = s * DAT_015b0e10.y;
        spin.z = s * DAT_015b0e10.z;
        spin.w = cosf(half);
        axisU = FUN_0059aed0(DAT_015b0df8, spin);
        axisV = FUN_0059aed0(DAT_015b0e04, spin);
    }
    axisU = FUN_0059aed0(axisU, *orient);
    axisV = FUN_0059aed0(axisV, *orient);
    if (Dot(Cross(axisU, axisV), fwd) < 0.95f) {
        axisU = Normalized(side);
        axisV = Normalized(up2);
    }

    // ---- 2. corners, plane and decal frame -------------------------------------------------
    Vector3 a = axisU * size;
    Vector3 b = axisV * size;
    Vector3 corner0 = *pos - a - b;
    Vector3 dir[4];
    dir[1] = Normalized(*pos - a + b);
    dir[2] = Normalized(*pos + a + b);
    dir[3] = Normalized(*pos + a - b);
    dir[0] = Normalized(corner0);

    Plane plane;
    plane.n = n;
    plane.d = -Dot(n, *pos);
    decal->plane = plane;
    float t;
    if (decal->plane.Intersect(Vector3(0.0f, 0.0f, 0.0f), dir[0], t))
        corner0 = dir[0] * t;
    decal->origin = corner0;

    float lenU = Length(a);
    decal->sizeU = lenU * 2.0f;
    decal->axisU = a * (1.0f / lenU);
    float lenV = Length(b);
    decal->sizeV = lenV * 2.0f;
    decal->axisV = b * (1.0f / lenV);

    // ---- 3. cube faces of the four corners ---------------------------------------------------
    float u[4], v[4];
    int face1 = CubeFaceUV(dir[1], u[1], v[1]);
    int face2 = CubeFaceUV(dir[2], u[2], v[2]);
    int face3 = CubeFaceUV(dir[3], u[3], v[3]);
    int face0 = CubeFaceUV(dir[0], u[0], v[0]);

    FaceRect localRects[6];
    if (rects == 0)
        rects = localRects;

    Vector3 quad[4];
    quad[0] = dir[1];
    quad[1] = dir[2];
    quad[2] = dir[3];
    quad[3] = dir[0];

    Vector3 pts[16];
    if (face1 == face2 && face1 == face3 && face1 == face0) {
        // whole decal on one face: a single quad
        float w = (float)target->width;
        float h = (float)target->height;
        for (int i = 0; i < 4; ++i)
            pts[i] = Vector3(u[i] * w, v[i] * h, 0.0f);
        BoundingBox box(Vector3(u[1], v[1], 0.0f));
        box.Extend(Vector3(u[0], v[0], 0.0f));
        box.Extend(Vector3(u[3], v[3], 0.0f));
        box.Extend(Vector3(u[2], v[2], 0.0f));
        FaceRect* r = &rects[face1];
        r->minU = box.lo.x;
        r->minV = box.lo.y;
        r->maxU = box.hi.x;
        r->maxV = box.hi.y;
        EmitFace(target, pts, 4, face1, decal, r, arg10, arg6);
        return;
    }

    // ---- spans several faces: clip against each face's frustum ------------------------------
    for (int face = 0; face < 6; ++face) {
        ClipVertex poly[16];
        for (int i = 0; i < 4; ++i)
            poly[i].pos = quad[i];
        int count = 4;
        for (int k = 0; k < 4; ++k) {
            if (count == 0)
                break;
            FUN_00fc2c70(poly, &count, &DAT_016d6fa8[face][k]);
        }
        if (count == 0)
            continue;

        BoundingBox box;
        float sign = (face & 1) ? -1.0f : 1.0f;
        const u8* perm = DAT_0148f608[face >> 1];
        float flip[3];
        flip[0] = sign;
        flip[1] = 1.0f;
        flip[2] = sign;
        Vector3 scale(flip[perm[0]], flip[perm[1]], flip[perm[2]]);

        float w = (float)target->width;
        float h = (float)target->height;
        for (int i = 0; i < count; ++i) {
            Vector3 f;
            f[perm[0]] = poly[i].pos.x * scale.x;
            f[perm[1]] = poly[i].pos.y * scale.y;
            f[perm[2]] = poly[i].pos.z * scale.z;
            float pu = (f.x * (1.0f / f.z) + 1.0f) * 0.5f;
            float pv = (f.y * (1.0f / f.z) + 1.0f) * 0.5f;
            pts[i] = Vector3(pu * w, pv * h, 0.0f);
            box.ExtendInline(Vector3(pu, pv, 0.0f));
        }
        FaceRect* r = &rects[face];
        r->minU = box.lo.x;
        r->minV = box.lo.y;
        r->maxU = box.hi.x;
        r->maxV = box.hi.y;
        EmitFace(target, pts, count, face, decal, r, arg10, arg6);
    }
    (void)arg7;
}

// @ 0x00f6eb40
void __stdcall FUN_00f6eb40(AABox* box)
{
    AABox tmp;
    tmp.mMin = cSPVector3_s00f6_df40(-1000.0f, -1000.0f, -1000.0f);
    tmp.mMax = cSPVector3_s00f6_df40(1000.0f, 1000.0f, 1000.0f);
    const AABox& r = tmp;
    box->mMax = r.mMax;
    box->mMin = r.mMin;
}
