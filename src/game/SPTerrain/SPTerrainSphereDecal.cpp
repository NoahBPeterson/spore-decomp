// src/game/SPTerrain/SPTerrainSphereDecal.cpp -- migrated from slice(s) s00fae800, s00fad550, s00fac5c0 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainSphereDecal.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cTerrainSphereDecal.h"

// unnamed retail callees and globals (address in the comment)
extern void FreeArr(void* p);                  // 0x00f47380, operator delete[] (cdecl)
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
#include <math.h>
#include "rw/graphics/IndexBuffer.h"
#include "rw/graphics/Mesh.h"
#include "rw/graphics/VertexBuffer.h"
#include "rw/graphics/VertexDescriptor.h"
#include <string.h>
#pragma intrinsic(_InterlockedExchangeAdd)

// ---- items of slice s00fac5c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void FreeArr(void* p);                  // 0x00f47380, operator delete[] (cdecl)
struct FaceElem {
    uint32_t mFace;                             // +0x0
    float mBox[4];                              // +0x4
};
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
struct Vec3 { float x, y, z; };
struct Matrix33 {
    union {
        float m[9];                             // +0x0
        struct { Vec3 xAxis, yAxis, zAxis; } row;
    };

    void Assign(const Matrix33* pSrc);          // 0x0041cb40
};
struct DecalNode {
    uint16_t mFlags;                            // +0x0
    uint16_t mStamp;                            // +0x2
    float mNormal[3];                           // +0x4
    uint32_t mPad;                              // +0x10
    Matrix33 mBasis;                            // +0x14
};
struct DecalOwner {
    void* mpVtbl;                               // +0x0
    char pad0[0x80 - 0x4];                      // +0x4
    void* mpBlock_80;                           // +0x80
    char pad1[0x128 - 0x84];                    // +0x84
    void* mpRef_128;                            // +0x128

    void Destroy();                             // 0x00fad4f0
};
namespace SP {
struct cTerrainSphereDecal_s00fa_c5c0 {
    char pad0[0x80];
    FaceElem* mpFaces;                          // +0x80
    FaceElem* mpFacesEnd;                       // +0x84

    bool GetBBoxForFace(uint32_t face, float* pOut);   // 0x00fad140
};  // namespace SP
}
static Vec3 CrossVec(Vec3 a, Vec3 b)
{
    Vec3 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}
static Vec3 NormVec(Vec3 v)
{
    float inv = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    Vec3 r;
    r.x = v.x * inv;
    r.y = v.y * inv;
    r.z = v.z * inv;
    return r;
}
// ---- items of slice s00fac5c0 end

// ---- items of slice s00fad550 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float sqrtf(float);
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
struct Vector4 {
    float x, y, z, w;
};
struct Matrix33_s00fa_d550 {
    float m[9];
    void  Assign(const Matrix33_s00fa_d550& src);
};
struct DecalEntry {
    int     m_index;    // +0x00
    Vector4 m_box;      // +0x04
};
struct cTerrainSphereDecal_s00fa_d550;
struct cDecalHost {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int  GetTarget();                       // vtable slot +0xc
    void         MergeFaceBox(Vector4 box, int index);
};
struct cTerrainMapSet_s00fa_d550 {
    float GetHeightAt(const float* pos);  // 0x00f927c0 (cTerrainMapSet::GetHeightAt)
};
struct cTerrainEditor {
    bool SynthesizeAboveTextureDecal(void* host, cTerrainSphereDecal_s00fa_d550* decal, const float* pair,
                                     int index, Vector4 box, int param3);
};
namespace SP {
    cTerrainEditor* TerrainEditor();
}
struct U32Pair { u32 a, b; };
extern const u8       kSwz_1491030[][4];             // 0x1491030
extern const U32Pair  kPairs_16ca3d4[];              // 0x16ca3d4
struct cTerrainSphereDecal_s00fa_d550 {
    void*       m_vtbl;         // +0x000
    int         m_04;           // +0x004
    u16         m_08;           // +0x008
    u16         m_0a;           // +0x00a
    float       m_0c;           // +0x00c
    float       m_10;           // +0x010
    float       m_14;           // +0x014
    float       m_18;           // +0x018
    Matrix33_s00fa_d550    m_mat;          // +0x01c
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

    cTerrainSphereDecal_s00fa_d550* Construct();  // 0x00fad730 (cTerrainSphereDecal::Construct)
    void  Uninit();  // 0x00fadac0 (cTerrainSphereDecal::Uninit)
    bool  DispatchStaticDecal(int index, int param3);
    void  Reset();              // 00fad000
};
// ---- items of slice s00fad550 end

// ---- items of slice s00fae800 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace math {
namespace fpu {
template <class T, int Align>
struct Matrix33Template_s00fa_e800 {
    T m[9];
    Matrix33Template_s00fa_e800(const Matrix33Template_s00fa_e800& other);  // 0x0041cb40
};
}  // namespace rw::math::fpu
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
struct cSPVector3 { float x; float y; float z; };
}
namespace SP {
typedef rw::math::fpu::Matrix33Template_s00fa_e800<float, 0> cSPMatrix3;
}
namespace SP {
struct cSPTransform {
    unsigned short mFlags;             // +0x00
    unsigned short mModificationCount; // +0x02
    cSPVector3     mTranslation;       // +0x04
    float          mScale;             // +0x10
    cSPMatrix3     mRotation;          // +0x14

    // 0x00537dc0 (cSPTransformOps::Assign): copies a transform, fixing up the
    // derived rotation/scale cache.
    cSPTransform& Assign(const void* src);
};
}
namespace SP {
struct cDecalFlags {
    unsigned int mBits;  // +0x00
    bool test(int i) const { return ((mBits >> i) & 1) != 0; }
    void set(int i, bool v) {
        if (v)
            mBits |= (1u << i);
        else
            mBits &= ~(1u << i);
    }
};
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
class cTextureInstance_s00fa_e800 {
public:
    void GetImageResource(unsigned int id);  // 0x00576650
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
struct tFaceInfo_s00fa_e800 {
    unsigned int       mFace;             // +0x00
    EA::RectT_s00fa_e800<float>   mBoundingBoxFace;  // +0x04
};
}
namespace SP {
class cTerrainSphereDecal_s00fa_e800 {
public:
    unsigned char mPad00[0x08];
    cSPTransform  mTransform;        // +0x08  (cDecal::mTransform)
    unsigned char mPad40[0x10];      // +0x40 .. cDecal::mColorAlpha region
    float         mTurns;            // +0x50  (cDecal::mTurns)
    float         mAspect;           // +0x54  (cDecal::mAspect)
    unsigned char mPad58[0x18];
    int           mType;             // +0x70  (cTerrainDecal::mType)
    unsigned int  mRefCount;         // +0x74
    cTerrainSphere_s00fa_e800* mpParentSphere;  // +0x78
    cTerrainMapSet_s00fa_e800* mpTerrainMapSet; // +0x7c
    tFaceInfo_s00fa_e800*    mFaceArrayBegin;   // +0x80
    tFaceInfo_s00fa_e800*    mFaceArrayEnd;     // +0x84
    unsigned char mPad88[0x0c];
    cCubeMapCoord_s00fa_e800 mPosition;         // +0x94
    float         mUSize;            // +0xa0
    float         mVSize;            // +0xa4
    float         mUSizeInput;       // +0xa8
    float         mVSizeInput;       // +0xac
    float         mDecalRadius;      // +0xb0
    unsigned char mPadB4[0x04];
    cDecalFlags   mFlags;            // +0xb8
    unsigned char mPadBC[0x10];
    float         mTexXform[8];      // +0xcc  (the decal's projective texture transform)
    unsigned char mPadEC[0x3c];
    cTextureInstance_s00fa_e800 mTexture;       // +0x128

    void UpdateDecalUV();                                             // 0x00fae800
    void SetupDecal(int id, unsigned int textureId, cTerrainSphere_s00fa_e800* sphere,
                    const cSPTransform* xf, float turns, bool flag);  // 0x00faec70
    void UpdateDecalShaderData(const cSPTransform* xf, float repeat); // 0x00fadc20
};
}
namespace SP {
extern float gDecalAngleScale;                    // 0x016ca638
}
namespace SP {
void FixupDecalTransform(cSPTransform* xf);
}
// ---- items of slice s00fae800 end

// @ 0x00fad140
namespace SP {
bool cTerrainSphereDecal_s00fa_c5c0::GetBBoxForFace(uint32_t face, float* pOut)
{
    uint32_t n = (uint32_t)(mpFacesEnd - mpFaces);
    if (n == 0)
        return false;
    uint32_t i = 0;
    do {
        if (mpFaces[i].mFace == face) {
            pOut[0] = mpFaces[i].mBox[0];
            pOut[1] = mpFaces[i].mBox[1];
            pOut[2] = mpFaces[i].mBox[2];
            pOut[3] = mpFaces[i].mBox[3];
            return true;
        }
        ++i;
    } while (i < (uint32_t)(mpFacesEnd - mpFaces));
    return false;
}
}  // namespace SP

// @ 0x00fad1d0
void DecalNode_UpdateBasis(DecalNode* pNode)
{
    Matrix33 m;
    m.Assign(&pNode->mBasis);

    Vec3 zAxis;
    zAxis.x = pNode->mNormal[0];
    float invZ = 1.0f / sqrtf(zAxis.x * zAxis.x +
                              pNode->mNormal[2] * pNode->mNormal[2] +
                              pNode->mNormal[1] * pNode->mNormal[1] + 1e-8f);
    zAxis.x = zAxis.x * invZ;
    zAxis.y = pNode->mNormal[1] * invZ;
    zAxis.z = pNode->mNormal[2] * invZ;
    m.row.zAxis = zAxis;

    Vec3 xAxis = m.row.xAxis;
    Vec3 yAxis = m.row.yAxis;

    float dotA = fabsf(xAxis.x * zAxis.x + xAxis.y * zAxis.y + xAxis.z * zAxis.z);
    float dotB = fabsf(yAxis.x * zAxis.x + yAxis.y * zAxis.y + yAxis.z * zAxis.z);

    if (dotB <= dotA) {
        // Rebuild the x row from y x z, then y from z x x.
        xAxis = NormVec(CrossVec(yAxis, zAxis));
        m.row.xAxis = xAxis;
        yAxis = CrossVec(zAxis, xAxis);
        m.row.yAxis = yAxis;
    } else {
        // Rebuild the y row from z x x, then x from y x z.
        yAxis = NormVec(CrossVec(zAxis, xAxis));
        m.row.yAxis = yAxis;
        xAxis = CrossVec(yAxis, zAxis);
        m.row.xAxis = xAxis;
    }

    pNode->mFlags |= 2;
    ++pNode->mStamp;
    pNode->mBasis = m;
}

// @ 0x00fad4f0
void DecalOwner::Destroy()
{
    mpVtbl = (void*)0x1491090;
    if (mpRef_128 != 0) {
        volatile long* pCount = (volatile long*)((char*)mpRef_128 + 8);
        _InterlockedExchangeAdd(pCount, -1);
        long n = _InterlockedExchangeAdd(pCount, 0);
        if (n < 1)
            _InterlockedExchangeAdd(pCount, 1);
        else
            _InterlockedExchangeAdd(pCount, 0);
    }
    if (mpBlock_80 != 0 && ((int*)mpBlock_80)[-1] != 0)
        FreeArr(mpBlock_80);
    mpVtbl = (void*)0x13ef094;
}

// @ 0x00fad550
bool cTerrainSphereDecal_s00fa_d550::DispatchStaticDecal(int index, int param3)
{
    float* pf = (float*)((cDecalHost*)m_78)->GetTarget();

    float t1 = m_94 * 2.0f - 1.0f;
    float h  = ((pf[0x10] + pf[0xf]) * pf[0xe]) + pf[0xd];
    float t2 = m_98 * 2.0f - 1.0f;
    float inv = 1.0f / sqrtf(t2 * t2 + t1 * t1 + 1.0f);
    float s = inv;
    if (m_9c & 1)
        s = -s;

    const u8* swz = kSwz_1491030[m_9c >> 1];
    float axis[3];
    axis[swz[0]] = s * t1;
    axis[swz[1]] = inv * t2;
    axis[swz[2]] = s;

    if (h > ((cTerrainMapSet_s00fa_d550*)m_7c)->GetHeightAt(axis))
        m_b8 |= 1;
    else
        m_b8 &= ~1;

    for (u32 i = 0; i < (u32)(((char*)m_84 - (char*)m_80) / 0x14); i++) {
        if (m_80[i].m_index == index) {
            U32Pair pair = kPairs_16ca3d4[m_80[i].m_index];
            return SP::TerrainEditor()->SynthesizeAboveTextureDecal(m_78, this, (const float*)&pair,
                       m_80[i].m_index, m_80[i].m_box, param3) != 0;
        }
    }
    return true;
}

// @ 0x00fae800
void SP::cTerrainSphereDecal_s00fa_e800::UpdateDecalUV()
{
    float angle = mTurns * SP::gDecalAngleScale;
    float fSin = sinf(angle);
    float fCos = cosf(angle);
    float fRepeat = (mType == 9) ? 1.0f : mAspect;

    cSPTransform xf = mTransform;
    rw::math::fpu::Matrix33Template_s00fa_e800<float, 0> rot(mTransform.mRotation);
    FixupDecalTransform(&xf);

    float fNegSin = -fSin;
    float fHalfScale = 0.5f / xf.mScale;
    float f12 = (rot.m[0] * fCos + rot.m[3] * fSin) * fHalfScale;
    float f13 = (rot.m[1] * fCos + rot.m[4] * fSin) * fHalfScale;
    float f7 = (rot.m[2] * fCos + rot.m[5] * fSin) * fHalfScale;
    float fNegHalf = -0.5f / (xf.mScale * fRepeat);
    float f10 = (rot.m[0] * fNegSin + rot.m[3] * fCos) * fNegHalf;
    float f14 = (rot.m[1] * fNegSin + rot.m[4] * fCos) * fNegHalf;
    float f8 = (rot.m[2] * fNegSin + rot.m[5] * fCos) * fNegHalf;

    float fAbsX = fabsf(xf.mTranslation.x);
    float fAbsY = fabsf(xf.mTranslation.y);
    float fAbsZ = fabsf(xf.mTranslation.z);

    mTexXform[3] = 0.5f - ((xf.mTranslation.x * f12 + xf.mTranslation.z * f7) +
                           xf.mTranslation.y * f13);
    mTexXform[0] = f12;
    mTexXform[1] = f13;
    mTexXform[2] = f7;
    mTexXform[4] = f10;
    mTexXform[5] = f14;
    mTexXform[7] = 0.5f - ((xf.mTranslation.x * f10 + xf.mTranslation.z * f8) +
                           xf.mTranslation.y * f14);
    mTexXform[6] = f8;

    float fU;
    float fV;
    int face;
    if (fAbsZ < fAbsX || fAbsZ < fAbsY) {
        if (fAbsY < fAbsX) {
            fU = (xf.mTranslation.y / xf.mTranslation.x + 1.0f) * 0.5f;
            fV = (xf.mTranslation.z / fAbsX + 1.0f) * 0.5f;
            face = (xf.mTranslation.x < 0.0f) ? 3 : 2;
        } else {
            fU = (xf.mTranslation.z / xf.mTranslation.y + 1.0f) * 0.5f;
            fV = (xf.mTranslation.x / fAbsY + 1.0f) * 0.5f;
            face = (xf.mTranslation.y < 0.0f) ? 5 : 4;
        }
    } else {
        fU = (xf.mTranslation.x / xf.mTranslation.z + 1.0f) * 0.5f;
        fV = (xf.mTranslation.y / fAbsZ + 1.0f) * 0.5f;
        face = (xf.mTranslation.z < 0.0f) ? 1 : 0;
    }

    float fUSize = xf.mScale /
                   ((mpParentSphere->GetMapSet()->mRadius * SP::gDecalAngleScale) * 0.25f);
    float fVSize = fUSize * fRepeat;

    if (mPosition.mU != fU || mPosition.mV != fV || mPosition.mFace != face ||
        mUSizeInput != fUSize || mVSizeInput != fVSize) {
        mPosition.mU = fU;
        mPosition.mV = fV;
        mUSizeInput = fUSize;
        mVSizeInput = fVSize;
        mUSize = fUSize;
        mVSize = fVSize;
        mPosition.mFace = face;
        mDecalRadius = (fVSize > fUSize) ? (fVSize * 0.55f) : (fUSize * 0.55f);
        UpdateDecalShaderData(&xf, fRepeat);
    }
}

// @ 0x00faec70
void SP::cTerrainSphereDecal_s00fa_e800::SetupDecal(int id, unsigned int textureId, cTerrainSphere_s00fa_e800* sphere, const cSPTransform* xf, float turns, bool flag)
{
    mRefCount = (unsigned int)id;
    mTexture.GetImageResource(textureId);
    mpParentSphere = sphere;
    mpTerrainMapSet = sphere->GetMapSet();
    mTransform.Assign(xf);
    mTurns = turns;

    mFlags.set(3, flag);
    mFlags.set(1, false);

    if (mFlags.test(3)) {
        UpdateDecalUV();
        for (int i = 0; i < (int)(mFaceArrayEnd - mFaceArrayBegin); ++i) {
            if (mpParentSphere->GetMapSet())
                mpParentSphere->MergeFaceBox(mFaceArrayBegin[i].mFace,
                                             mFaceArrayBegin[i].mBoundingBoxFace);
        }
    }
}
