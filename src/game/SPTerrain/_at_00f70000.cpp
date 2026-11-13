// src/game/SPTerrain/_at_00f70000.cpp -- migrated from slice(s) s00f7caf0, s00f7b520, s00f7a710, s00f79bb0, s00f77940, s00f76000, s00f75c10, s00f74fe0, s00f717b0, s00f708d0, s00f6fc50 by tools/migrate/rewrite.py
// Object file: SPTerrain/_at_00f70000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include "EA/Allocator/FixedAllocatorBase.h"
#include <xmmintrin.h>
#include <string.h>
#include "EA/Swarm/cTransform.h"
#include <intrin.h>
#ifndef NULL
#define NULL 0
#endif

// unnamed retail callees and globals (address in the comment)
extern "C" double __cdecl fabs(double);
extern void* EffectsManager();   // 0x0067ddd0
#pragma intrinsic(fabs)

// ---- items of slice s00f6fc50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* EffectsManager();   // 0x0067ddd0
struct IEffect
{
	virtual void  vt00();
	virtual void  vt04();
	virtual void  vt08();
	virtual void  vt0c();
	virtual int   vt10();
	virtual void  vt14();
	virtual void  vt18();
	virtual void  vt1c();
	virtual float vt20(void* p);
};
typedef IEffect* (__thiscall *PFN_MgrLookup)(void* self, int key, int b);
struct CubeInner
{
	char   _pad00[8];
	void*  mp08;                     // +0x08  cTerrainMap<unsigned short>*
	void*  mp0c;                     // +0x0c  cTerrainMap<unsigned int>*
	void*  mp10;                     // +0x10  cCubeImage*
	void*  mp14;                     // +0x14  other sub-object
	char   _pad18[0x38 - 0x18];
	float  m38;                      // +0x38
	float  m3c;                      // +0x3c
	float  m40;                      // +0x40
	float  m44;                      // +0x44
	float  m48;                      // +0x48
};
struct CubeOwner
{
	char        _pad00[0xc];
	CubeInner*  mpInner;             // +0x0c
	void*       mp10;                // +0x10

	float Sample32(const float* p);          // 0x00F6FC50
	float Test32(const float* p);            // 0x00F6FE50
	float Slope16(const float* p);           // 0x00F70080
	float Test16(const float* p);            // 0x00F70250
	int   CountSubs();                       // 0x00F70440
	float SampleImage(const float* p);       // 0x00F70470
	float TestEffect(const float* p);        // 0x00F70660
	int   CountSubsEffect();                 // 0x00F70870
};
// ---- items of slice s00f6fc50 end

// ---- items of slice s00f708d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_01485720;    // 1.0f
extern float DAT_013ec4b8;    // 1e-08f
extern const float DAT_016c9a20;
struct V4 {
    float x, y, z, w;
};
void  Matrix33Assign(void* out, const void* src);         // 0x0041cb40
void  GetCameraLocationInfo(void* viewer, V4* out, int, int, int); // 0x007c3d30
void  GetCameraDirInfo(void* viewer, V4* out);            // 0x00fb8db0
struct IEff {
    void** mpVtbl;
};
inline void*  EffGet(void* mgr, unsigned int key, void* p) { return ((void*(*)(void*,unsigned int,void*))(((void**)mgr)[0x8c/4]))(mgr, key, p); }
inline void   EffAddRef(IEff* e)                           { ((void(*)(IEff*))(e->mpVtbl[0]))(e); }
inline void   EffRelease(IEff* e)                          { ((void(*)(IEff*))(e->mpVtbl[1]))(e); }
inline float  EffCall10(IEff* e)                           { return ((float(*)(IEff*))(e->mpVtbl[0x10/4]))(e); }
inline float  EffCall20(IEff* e, const V4* dir)            { return ((float(*)(IEff*,const V4*))(e->mpVtbl[0x20/4]))(e, dir); }
void EAFreeOp(void* p);       // 0x00f47380
float SqrtF(float f);         // 0x006be790 (linker-resolved CRT sqrt helper)
struct CCubeQuery {
    char pad0[0x0c];
    struct Ctx* mpCtx;        // +0x0c
    struct Terrain* mpTerrain; // +0x10
    struct Viewer* mpViewer;   // +0x14
    void* mpSlot;              // +0x18
    // member functions
    float QueryA(const V4* dir);       // 0x00f708d0
    float QueryB(const V4* dir);       // 0x00f70c30
    float QueryC(const V4* dir);       // 0x00f70fa0
    float QueryD(const V4* dir);       // 0x00f71220
    V4*   GetCubeUV();                 // 0x00f713c0
    V4*   DirToTerrainColor(V4* out, const V4* dir);  // 0x00f713e0
    V4*   GetColorA(V4* out);          // 0x00f715d0
    V4*   GetColorB(V4* out);          // 0x00f71610
    V4*   GetScaledColor(V4* out, const V4* unused);  // 0x00f716b0
};
struct Ctx {
    char pad0[8];
    void* mpMapA;             // +0x08
    void* mpMapB;             // +0x0c
    void* mpCube;             // +0x10
    void* mpUV;               // +0x14
    char pad1[0x38 - 0x18];
    float f38;                // +0x38
    float f3c;                // +0x3c
    float f40;                // +0x40
    float f44;                // +0x44
    float f48;                // +0x48
};
struct Terrain {
    char pad0[0x2f4];
    char body[0x2f4];         // +0x2f4 base
};
struct Viewer {
    char pad0[0x14];
    void* mpCubeImage;        // +0x14
};
// ---- items of slice s00f708d0 end

// ---- items of slice s00f717b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cTerrainProbe {
public:
    virtual bool query0();
    virtual bool query1();
    virtual bool query2();
    virtual bool query3();
    virtual bool castPoint(const float* pos, float* hit, int a, int b, int c, int d);  // +0x10
    float distance(const float* pos, int a, int b);                                      // 0x00f71f30
};
struct cSPTransformOps {
    char pad00[0x38];
    float mHeight;                      // +0x38
    cSPTransformOps* Assign(const void* src);
};
struct cTerrainHeightSource {
    char pad00[0x40];
    const float* mBegin;                // +0x40
    const float* mEnd;                  // +0x44
};
// ---- items of slice s00f717b0 end

// ---- items of slice s00f74fe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kFXMaxFloat;               // 0x015B0EDC (FLT_MAX, bounding-box sentinel)
extern float kFXRandThreshold;          // 0x015B0EE8 (0.5 random split)
extern float kFXHeightCutoff;           // 0x01471064 (height test for the emit map)
extern float kFXSampleEpsilon;          // 0x015B0EEC (radius epsilon of the sample jitter)
extern uint32_t kSurfacePinFlags;       // 0x015B0EE4 (surface record flag mask)
extern "C" double FUN_007d45d0(float lo, float hi);
namespace EA {
namespace Random {
class RandomLinearCongruential_s00f7_4fe0 { public: double RandomDoubleUniform(); };   // 0x009360d0
}
}
extern EA::Random::RandomLinearCongruential_s00f7_4fe0 sRandom_Swarm;                  // 0x016778dc
static __forceinline double RandRange(double lo, double hi)
{
    double r = sRandom_Swarm.RandomDoubleUniform();
    double v = r * (hi - lo) + lo;
    if (v >= hi) return hi;
    if (v < lo) return lo;
    return v;
}
struct Vector2 { float x, y; Vector2() {} Vector2(float _x, float _y) : x(_x), y(_y) {} };
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
};
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
struct Vector4 { float x, y, z, w; };
struct cBoundingBox { Vector3 mMin; Vector3 mMax; };
struct cTransform {                     // 0x38 bytes (== cSPTransform)
    enum { kHasScale = 1, kHasRotation = 2, kHasTranslation = 4 };

    uint16_t mFlags;                    // +0x00
    uint16_t mModCount;                 // +0x02
    Vector3  mTranslation;              // +0x04
    float    mScale;                    // +0x10
    float    mRotation[3][3];           // +0x14 (row vectors)

    // out of line in the original
    void Assign(const void* pSrc);      // 0x00537DC0 (cSPTransformOps::Assign)
    void Transform(Vector3& v) const;   // 0x007CDEE0
    void InverseTransformPoint(Vector3& v) const;   // 0x007CDA70

    // row 0 is written as two statements so /fp:fast keeps the original ((r10*y + r20*z) + x*r00)
    // summation order (the binary does); rows 1 and 2 are plain left-to-right sums.
    Vector3 Rotate(const Vector3& v) const
    {
        float rx = mRotation[1][0] * v.y + mRotation[2][0] * v.z;
        rx += v.x * mRotation[0][0];
        return Vector3(rx,
                       mRotation[0][1] * v.x + mRotation[1][1] * v.y + mRotation[2][1] * v.z,
                       mRotation[0][2] * v.x + mRotation[1][2] * v.y + mRotation[2][2] * v.z);
    }
    // transform a point: rotate (when flagged), scale, translate
    Vector3 TransformPoint(const Vector3& v) const
    {
        Vector3 r = (mFlags & kHasRotation) ? Rotate(v) : v;
        return Vector3(mTranslation.x + r.x * mScale,
                       mTranslation.y + r.y * mScale,
                       mTranslation.z + r.z * mScale);
    }
};
struct cSurfaceInfo {
    uint32_t mFlags;                    // +0x00
    uint32_t mPad[7];
    float    mPinOffset;                // +0x20
};
struct ISurface {
    virtual int  Release() = 0;
    virtual int  AddRef() = 0;
    virtual bool ApplySurface(float, const Vector3&, Vector3&, Vector3&, void*, void*) = 0;
    virtual float DistanceFromSurface(const Vector3& srcPoint, void*, void*) = 0;
    virtual bool FindClosestSurfacePoint(const Vector3& srcPoint, Vector3& dst, Vector3* normal,
                                         void* orientation, void* stateData, void* particleData) = 0;
};
struct cSurfaceRec {                    // 0x18
    ISurface*     mpSurface;            // +0x00
    cSurfaceInfo* mpInfo;               // +0x04
    int           mHasStateData;        // +0x08
    int           mStateDataOffset;     // +0x0c
    uint32_t      mPad[2];
};
struct IEffectMap {
    virtual int   AddRef() = 0;
    virtual int   Release() = 0;
    virtual void  Start() = 0;
    virtual void  Finish() = 0;
    virtual int   ModificationCount() = 0;
    virtual cBoundingBox GetBounds() = 0;
    virtual bool  PointInMap(const Vector3& position) = 0;         // +0x18
    virtual bool  InWorldSpace() = 0;
    virtual float Height(const Vector3& position) = 0;             // +0x20
    virtual Vector3 Normal(const Vector3& position) = 0;
    virtual Vector3 Velocity(const Vector3& position) = 0;
    virtual Vector4* ColorAlpha(Vector4* pOut, const Vector3& position) = 0;   // +0x2c
};
struct cParticleBase {                  // +0x08 in cParticle
    float   mAge;                       // +0x00
    float   mLife;                      // +0x04
    Vector3 mPosition;                  // +0x08
    Vector3 mVelocity;                  // +0x14
};
struct cParticle {                      // older layout (s00f79bb0)
    void*         mpNext;               // +0x00
    void*         mpPrev;               // +0x04
    cParticleBase mBase;                // +0x08
    float         mSize;                // +0x28
    float         mAspectRatio;         // +0x2c
    float         mRotation;            // +0x30
    float         mAlpha;               // +0x34
    Vector3       mColor;               // +0x38
    uint8_t       mFrame;               // +0x44
    uint8_t       mPad45[3];
    Vector3       mSurfaceNormal;       // +0x48
};
struct cParticlesDescription {          // older layout (s00f79bb0), retail offsets
    enum {
        kFlagEllipsoid = 1 << 4,        // ellipsoid emission volume
        kFlagPinToMap  = 1 << 5         // emit map height/colour modulation
    };

    uint32_t mPad0[2];                  // +0x00
    uint32_t mFlags;                    // +0x08 (low half of the flag bitset)
    uint32_t mFlagsHigh;                // +0x0c
    uint32_t mPad10[21];                // +0x10
    float    mTorusWidth;               // +0x64 (negative: box/ellipsoid instead)
    uint32_t mPad68[32];                // +0x68
    float    mColorVary[3];             // +0xe8
};
class cParticlesEffectOld {             // older layout (s00f79bb0)
public:
    char                   mPad00[0x17];            // +0x00
    uint8_t                mForcePin;               // +0x17 (always place on surface; name guessed)
    uint32_t               mPad18[3];               // +0x18
    cParticlesDescription* mDesc;                   // +0x24
    uint32_t               mPad28[2];               // +0x28
    void*                  mGlobalParams;           // +0x30
    uint32_t               mPad34[31];              // +0x34
    cTransform             mSourceTransform;        // +0xb0
    cTransform             mRigidTransform;         // +0xe8
    uint32_t               mPad120[30];             // +0x120
    IEffectMap*            mEmitMap;                // +0x198
    IEffectMap*            mEmitColorMap;           // +0x19c
    uint8_t                mPad1a0;                 // +0x1a0
    uint8_t                mEmitMapInWorldSpace;    // +0x1a1 (name guessed)
    uint8_t                mEmitColorMapInWorldSpace;   // +0x1a2
    uint8_t                mPad1a3[9];              // +0x1a3
    cBoundingBox           mEmissionVolume;         // +0x1ac
    uint32_t               mPad1c4[4];              // +0x1c4
    cSurfaceRec*           mSurfaceRecsBegin;       // +0x1d4
    cSurfaceRec*           mSurfaceRecsEnd;         // +0x1d8
    uint32_t               mPad1dc[4];              // +0x1dc
    uint8_t*               mSurfaceStateData;       // +0x1ec
    uint32_t               mPad1f0[4];              // +0x1f0
    uint8_t                mHaveSurfacePin;         // +0x200 (name guessed)
    uint8_t                mPad201[3];
};
extern "C" Vector3 FUN_007cdbe0(const cBoundingBox& box);                  // random point in a box
extern "C" Vector3 FUN_00a816d0(const cBoundingBox& box);                  // random point in an ellipsoid
extern "C" Vector3 FUN_00a817c0(const cBoundingBox& box, float width);     // random point on a torus
extern "C" double  FUN_007cdb90(const Vector2& range);                     // random float of a pair
extern "C" void    FUN_00705290(Vector3* dst, const Vector4* src);         // component-wise colour mul
class cDistributeEffectOld {
public:
    uint32_t      mPad00[32];           // +0x00
    Vector3       mBoundsMin;           // +0x80 (name guessed: world bounding box)
    Vector3       mBoundsMax;           // +0x8c
    uint32_t      mPad98;               // +0x98
    Vector3       mPosition;            // +0x9c
    cTransform    mSourceTransform;     // +0xa8
    cTransform    mRigidTransform;      // +0xe0
    uint32_t      mPad118[50];          // +0x118
    uint8_t       mTransformDirty;      // +0x1e0 (cleared here; name guessed)
    uint8_t       mPad1e1[0x9f];        // +0x1e1

    void SetTransforms(const void* pSource, const void* pRigid);
};
// ---- items of slice s00f74fe0 end

// ---- items of slice s00f75c10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 {
    float x;
    float y;
    float z;
};
struct Xform {
    uint32_t mFlags;                                        // +0x00
    Vec3     mPosition;                                     // +0x04
    float    mScale;                                        // +0x10
    float    mMatrix[9];                                    // +0x14
    void InverseTransformPoint(Vec3* point);                // 0x007cda70 (thiscall, ret 4)
};
struct AttachConfig {                                       // pointed to by owner+0x24
    char     pad00[8];
    uint32_t mFlags;                                        // +0x08
};
struct AttachTarget {                                       // pointed to by owner+0x198
virtual void t00();
virtual void t04();
virtual void t08();
virtual void t0c();
virtual void t10();
virtual void t14();
    virtual bool  Accept(Vec3* point);                      // +0x18
    virtual void  t1cdummy();
    virtual float GetRange(Vec3* point);                    // +0x20
};
struct RandomGlobal {
    double RandomDouble();                                  // 0x009360d0
};
extern RandomGlobal _sRandomGlobal;                         // 0x016778dc
namespace SP {
struct Vector2_s004d_f2d0 {
    float mData[2];
};
}
namespace SP {
float RandomInRange(const Vector2_s004d_f2d0& range);       // 0x004df2d0
}
struct AttachPoint {
    char pad00[0x10];
    Vec3 mPosition;                                         // +0x10
    char pad1c[0x48 - 0x1c];
    Vec3 mField48;                                          // +0x48
};
struct AttachPointUpdater {
    char          pad00[0x24];
    AttachConfig* mpConfig;                                 // +0x24
    char          pad28[0xb0 - 0x28];
    Xform         mXformA;                                  // +0xb0
    Xform         mXformB;                                  // +0xe8
    char          pad120[0x16c - 0x120];
    float         mMinRange;                                // +0x16c
    float         mMaxRange;                                // +0x170
    char          pad174[0x198 - 0x174];
    AttachTarget* mpTarget;                                 // +0x198
    char          pad19c[0x1a1 - 0x19c];
    bool          mEnabled;                                 // +0x1a1
    char          pad1a2[0x1b4 - 0x1a2];
    float         mField1b4;                                // +0x1b4
    char          pad1b8[0x1c0 - 0x1b8];
    float         mField1c0;                                // +0x1c0
    bool UpdateAttachPoint(AttachPoint* io);                // 0x00f75c10
};
struct PoolNode {
    PoolNode* mpNext;                                       // +0x00
    int       mField4;                                      // +0x04
};
struct PoolAllocator {
    uint32_t  mPad[4];
    PoolNode* mpFreeHead;                                   // +0x10 (0x016c9b68)
    bool AddCore(int a, int b);                             // 0x00926650
};
extern PoolAllocator sPool;                                 // 0x016c9b58
// ---- items of slice s00f75c10 end

// ---- items of slice s00f76000 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void __fastcall FUN_00a7d6b0(void* self, int, float* v);
static inline float InlineSqrt(float x) { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(x))); }
static float g_a0;   // DAT_016c9ba0
static float g_a4;   // DAT_016c9ba4
static float g_a8;   // DAT_016c9ba8
static float g_ac;   // DAT_016c9bac
static float g_b0;   // DAT_016c9bb0
static float g_b4;   // DAT_016c9bb4
static float g_b8;   // DAT_016c9bb8
static float g_bc;   // DAT_016c9bbc
static float g_c0;   // DAT_016c9bc0
struct DrawParams {
    float v0, v1, v2;
    float v3, v4, v5;
    float colorR, colorG, colorB, colorA;
    uint8_t flag28;
    uint8_t pad29[3];
    float invW, invH;
    int wMinus1, hMinus1;
    int log2W;
    uint8_t alpha40;
};
struct EffectObject {
    char pad0[0x2c];
    float x0, y0, z0;         // +0x2c
    float x1, y1, z1;         // +0x38
    char pad44[0x134 - 0x44];
    uint8_t mode;             // +0x134
};
// ---- items of slice s00f76000 end

// ---- items of slice s00f77940 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
namespace EA {
namespace Swarm {
struct Vector3_s00f7_7940 {
    float x, y, z;
};
}
}
namespace EA {
namespace Swarm {
struct Matrix33 {
    float m[3][3];
};
}
}
namespace EA {
namespace Swarm {
struct Matrix44 {
    float m[4][4];
};
}
}
namespace EA {
namespace Swarm {
template <typename T>
struct SPVector {
    T*  mpBegin;
    T*  mpEnd;
    T*  mpCapacity;
    u32 mAllocator[2];

    int  size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
};
}
}
namespace EA {
namespace Swarm {
struct cWiggle {                              // 0x1c
    float   mTimeRate;
    Vector3_s00f7_7940 mRateDir;
    Vector3_s00f7_7940 mWiggleDir;
};
}
}
namespace EA {
namespace Swarm {
struct cParticle_s00f7_7940 {                            // 0x48
    cParticle_s00f7_7940* mpNext;                        // +0x00 intrusive_list_node
    cParticle_s00f7_7940* mpPrev;                        // +0x04
    float      mAge;                          // +0x08 cParticleBase
    float      mLife;                         // +0x0c
    Vector3_s00f7_7940    mPosition;                     // +0x10
    Vector3_s00f7_7940    mVelocity;                     // +0x1c
    float      mOverallSize;                  // +0x28 cParticleProperties
    float      mOverallAspect;                // +0x2c
    float      mOverallRotation;              // +0x30
    float      mOverallAlpha;                 // +0x34
    Vector3_s00f7_7940    mOverallColor;                 // +0x38
    u8         mFrame;                        // +0x44
    u8         mUnused[3];
};
}
}
namespace EA {
namespace Swarm {
struct cTransform_s00f7_7940 {                           // 0x38
    u16      mFlags;                          // +0x00
    u16      mModificationCount;              // +0x02
    Vector3_s00f7_7940  mTranslation;                    // +0x04
    float    mScale;                          // +0x10
    Matrix33 mRotation;                       // +0x14
};
}
}
namespace EA {
namespace Swarm {
struct cGlobalParams_s00f7_7940 {
    float    mParticleDensity;                // +0x00
    float    mParticleScale;                  // +0x04
    int      mParticleMultThreshold;          // +0x08
    float    mMaxParticleSize;                // +0x0c
    int      mMaxParticles;                   // +0x10
    int      mMaxEffects;                     // +0x14
    int      mMaxDistributeSamples;           // +0x18
    Matrix44 mProjectionMatrix;               // +0x1c
};
}
}
namespace EA {
namespace Swarm {
struct cParticlesDescription_s00f7_7940 {
    void*                 vftable;            // +0x000
    u32                   pad004;
    u32                   mFlags;             // +0x008 (bitset)
    u32                   pad00c[(0x7c - 0x0c) / 4];
    float                 mRateCurveTime;     // +0x07c
    u32                   pad080[2];
    SPVector<float>       mSizeCurve;         // +0x088
    float                 mSizeVary;          // +0x09c
    SPVector<float>       mAspectCurve;       // +0x0a0
    float                 mAspectVary;        // +0x0b4
    SPVector<float>       mRotationCurve;     // +0x0b8
    float                 mRotationVary;      // +0x0cc
    float                 mRotationOffset;    // +0x0d0
    SPVector<Vector3_s00f7_7940>     mColorCurve;        // +0x0d4
    Vector3_s00f7_7940               mColorVary;         // +0x0e8
    SPVector<float>       mAlphaCurve;        // +0x0f4
    u32                   pad108[(0x164 - 0x108) / 4];
    float                 mVelocityStretch;   // +0x164
    float                 mScrewRate;         // +0x168
    SPVector<cWiggle>     mWiggles;           // +0x16c
    u8                    mScreenBloomAlphaRate;  // +0x180
    u8                    mScreenBloomAlphaBase;  // +0x181
    u8                    mScreenBloomSizeRate;   // +0x182
    u8                    mScreenBloomSizeBase;   // +0x183
    SPVector<Vector3_s00f7_7940>     mLoopBoxColorCurve; // +0x184
    SPVector<float>       mLoopBoxAlphaCurve; // +0x198

    enum { kFlagScrewCylindrical = 29, kFlagLoopBox = 30 };
    bool IsSet(int bit) const { return ((mFlags >> bit) & 1) != 0; }
};
}
}
namespace EA {
namespace Swarm {
class cITextureParticleRenderer_s00f7_7940 {
public:
    virtual int  GetBuffer(int count, u8** buffer, int* stride) = 0;   // slot 0
    virtual void GetVertexAndIndexBuffer() = 0;                        // slot 1
    virtual void ReleaseAndDrawBuffer() = 0;                           // slot 2
};
}
}
namespace EA {
namespace Swarm {
class cParticlesEffect { public:
    u32                    pad000[0x18 / 4];  // vtables + cComponentBase
    cParticle_s00f7_7940*             mParticlesFirst;   // +0x18 intrusive_list anchor.mpNext
    cParticle_s00f7_7940*             mParticlesLast;    // +0x1c
    int                    mParticleCount;    // +0x20
    cParticlesDescription_s00f7_7940* mDesc;             // +0x24
    u32                    pad028[(0x30 - 0x28) / 4];
    cGlobalParams_s00f7_7940*         mGlobalParams;     // +0x30
    u32                    pad034;
    double                 mOverallTime;      // +0x38
    u32                    pad040[(0xb0 - 0x40) / 4];
    cTransform_s00f7_7940             mSourceTransform;  // +0xb0
    cTransform_s00f7_7940             mRigidTransform;   // +0xe8
    u32                    pad120[(0x17c - 0x120) / 4];
    float                  mCurrentSizeScale;     // +0x17c
    float                  mCurrentAlphaScale;    // +0x180
    float                  mCurrentMapForceScale; // +0x184
    Vector3_s00f7_7940                mCurrentColorScale;    // +0x188
};
}
}
namespace EA {
namespace Swarm {
struct SinCosEntry { float s, c; };
}
}
namespace EA {
namespace Swarm {
extern SinCosEntry gSinCosTable[16];          // 0x01677840
}
}
namespace EA {
namespace Swarm {
extern float       gSinCosInvStep;            // 0x016c9b24
}
}
namespace EA {
namespace Swarm {
extern float       gSinCosStep;               // 0x016c9b20
}
}
namespace EA {
namespace Swarm {
extern float       gDegToRad;                 // 0x016c9b9c
}
}
namespace EA {
namespace Swarm {
void WigglePoint(float time, const SPVector<cWiggle>& wiggles, const Vector3_s00f7_7940& origin,
                 Vector3_s00f7_7940& point);             // 0x00a9aff0
}
}
namespace {

// Output of StreamerSetup: the camera-facing quad axes and the screen-bloom factors.
struct StreamerInfo {                         // 0x28 (+ pad)
    EA::Swarm::Vector3_s00f7_7940 mAxis0;                           // +0x00
    EA::Swarm::Vector3_s00f7_7940 mAxis1;                           // +0x0c
    float   mBloomAlphaBase;                  // +0x18
    float   mBloomAlphaRate;                  // +0x1c
    float   mBloomSizeBase;                   // +0x20
    float   mBloomSizeRate;                   // +0x24
};

void StreamerSetup(EA::Swarm::cParticlesEffect* effect, EA::Swarm::cParticlesDescription_s00f7_7940* desc, StreamerInfo* info);  // 0x00f76000
void ApplyLoopBox(EA::Swarm::cParticlesEffect* effect, EA::Swarm::cParticlesDescription_s00f7_7940* desc, EA::Swarm::Vector3_s00f7_7940* pos,
                  EA::Swarm::Vector3_s00f7_7940* color, float* alpha);  // 0x00f74b40

// ---- math helpers -------------------------------------------------------------------

static __forceinline float Min(float a, float b)
{
    return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

static __forceinline float Max(float a, float b)
{
    return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

static __forceinline float Clamp(float v, float lo, float hi)
{
    return Min(Max(lo, v), hi);
}

static __forceinline int FloatToInt(float v)          // cvtss2si (current rounding mode)
{
    return _mm_cvt_ss2si(_mm_set_ss(v));
}

static __forceinline int FloorToInt(float v)
{
    int i = FloatToInt(v);
    if (v < (float)i)
        i = i - 1;
    return i;
}

static __forceinline const float& MaxRef(const float& a, const float& b)
{
    return (a < b) ? b : a;
}

static __forceinline const float& MinRef(const float& a, const float& b)
{
    return (b < a) ? b : a;
}

// Table sin/cos: nearest table angle by the 1.5*2^23 rounding trick, then a 2nd-order
// Taylor correction around it.
static __forceinline void FastSinCos(float angle, float& s, float& c)
{
    float k = angle * EA::Swarm::gSinCosInvStep + 12582912.0f;
    u32 bits = *(u32*)&k;
    u32 idx = bits & 0xf;
    float r = angle - (float)(int)(bits - 0x4b400000) * EA::Swarm::gSinCosStep;
    float s0 = EA::Swarm::gSinCosTable[idx].s;
    float c0 = EA::Swarm::gSinCosTable[idx].c;
    s = (c0 - s0 * r * 0.5f) * r + s0;
    c = c0 - (c0 * r * 0.5f + s0) * r;
}

// Curve evaluation at t in [0,1]; last = number of keys - 1.
static __forceinline float SampleCurve(const float* curve, unsigned int last, float t)
{
    if (last == 0)
        return curve[0];
    float f = (float)last * t;
    int i = (int)f;
    float frac = f - (float)i;
    if (frac > 0.0f)
        return (curve[i + 1] - curve[i]) * frac + curve[i];
    return curve[i];
}

static __forceinline EA::Swarm::Vector3_s00f7_7940 SampleCurve(const EA::Swarm::Vector3_s00f7_7940* curve, unsigned int last, float t)
{
    EA::Swarm::Vector3_s00f7_7940 v;
    if (last == 0) {
        v = curve[0];
    } else {
        float f = (float)last * t;
        int i = (int)f;
        float frac = f - (float)i;
        const EA::Swarm::Vector3_s00f7_7940& a = curve[i];
        if (frac > 0.0f) {
            const EA::Swarm::Vector3_s00f7_7940& b = curve[i + 1];
            v.x = a.x + (b.x - a.x) * frac;
            v.y = a.y + (b.y - a.y) * frac;
            v.z = a.z + (b.z - a.z) * frac;
        } else {
            v = a;
        }
    }
    return v;
}

// Row-vector times a 3x3 rotation.
static __forceinline EA::Swarm::Vector3_s00f7_7940 Rotate(const EA::Swarm::Vector3_s00f7_7940& v, const EA::Swarm::Matrix33& m)
{
    EA::Swarm::Vector3_s00f7_7940 r;
    r.x = m.m[2][0] * v.z + m.m[1][0] * v.y + m.m[0][0] * v.x;
    r.y = m.m[2][1] * v.z + m.m[1][1] * v.y + m.m[0][1] * v.x;
    r.z = m.m[2][2] * v.z + m.m[1][2] * v.y + m.m[0][2] * v.x;
    return r;
}

static __forceinline u8 ColorToByte(float v)
{
    return (u8)FloatToInt(Min(Max(0.0f, v) * 255.0f, 255.0f));
}

// Curve key counts (minus one) of the description, hoisted out of the particle loop.
struct CurveLimits {
    unsigned int color;
    unsigned int alpha;
    unsigned int size;
    unsigned int aspect;
    unsigned int rotation;
};

// Everything a quad needs: centre + age fraction, the oriented half-axis, size and colour.
struct QuadParticle {
    EA::Swarm::Vector3_s00f7_7940 pos;
    float   t;
    EA::Swarm::Vector3_s00f7_7940 axis;
    float   size;
    u32     color;
};

static __forceinline void ComputeQuadParticle(EA::Swarm::cParticlesEffect* effect, EA::Swarm::cParticlesDescription_s00f7_7940* desc,
                                              const StreamerInfo& info, const CurveLimits& lim,
                                              const EA::Swarm::cParticle_s00f7_7940* particle, QuadParticle& q)
{
    const float t = particle->mAge / particle->mLife;

    float aspect = SampleCurve(desc->mAspectCurve.mpBegin, lim.aspect, t);   // unused by quads
    (void)aspect;

    float size = particle->mOverallSize * effect->mCurrentSizeScale
               * SampleCurve(desc->mSizeCurve.mpBegin, lim.size, t);
    float rotation = particle->mOverallRotation * SampleCurve(desc->mRotationCurve.mpBegin, lim.rotation, t)
                   + desc->mRotationOffset;

    EA::Swarm::Vector3_s00f7_7940 c = SampleCurve(desc->mColorCurve.mpBegin, lim.color, t);
    EA::Swarm::Vector3_s00f7_7940 color;
    color.x = effect->mCurrentColorScale.x * (c.x * particle->mOverallColor.x);
    color.y = effect->mCurrentColorScale.y * (particle->mOverallColor.y * c.y);
    color.z = effect->mCurrentColorScale.z * (particle->mOverallColor.z * c.z);

    float alpha = particle->mOverallAlpha * SampleCurve(desc->mAlphaCurve.mpBegin, lim.alpha, t)
                * effect->mCurrentAlphaScale;

    EA::Swarm::Vector3_s00f7_7940 pos = particle->mPosition;

    // Screw: spin the particle about the effect's vertical axis.
    const float screwRate = desc->mScrewRate;
    if (screwRate != 0.0f) {
        const EA::Swarm::Vector3_s00f7_7940& origin = effect->mSourceTransform.mTranslation;
        float dx = pos.x - origin.x;
        float dy = pos.y - origin.y;
        float dz = pos.z - origin.z;
        float s, cs;
        if (desc->IsSet(EA::Swarm::cParticlesDescription_s00f7_7940::kFlagScrewCylindrical)) {
            float angle = sqrtf(dx * dx + dy * dy) * screwRate;
            FastSinCos(angle, s, cs);
        } else {
            FastSinCos(screwRate * dz, s, cs);
        }
        pos.x = dx * cs - dy * s + origin.x;
        pos.y = dx * s + dy * cs + origin.y;
    }

    if (desc->mWiggles.mpBegin != desc->mWiggles.mpEnd)
        EA::Swarm::WigglePoint((float)(desc->mRateCurveTime * effect->mOverallTime), desc->mWiggles,
                    effect->mSourceTransform.mTranslation, pos);

    if (desc->IsSet(EA::Swarm::cParticlesDescription_s00f7_7940::kFlagLoopBox))
        ApplyLoopBox(effect, desc, &pos, &color, &alpha);

    // Rigid transform (rotation only when flagged, then scale + translation).
    const EA::Swarm::cTransform_s00f7_7940& rigid = effect->mRigidTransform;
    if (rigid.mFlags & 2)
        pos = Rotate(pos, rigid.mRotation);
    const float scale = rigid.mScale;
    pos.x = rigid.mTranslation.x + pos.x * scale;
    pos.y = rigid.mTranslation.y + pos.y * scale;
    pos.z = rigid.mTranslation.z + pos.z * scale;
    size = scale * size;

    // Screen bloom: fade/shrink particles toward the screen edges.
    if (desc->mScreenBloomAlphaRate || desc->mScreenBloomSizeRate) {
        const EA::Swarm::Matrix44& m = effect->mGlobalParams->mProjectionMatrix;
        float sx = m.m[2][0] * pos.z + m.m[1][0] * pos.y + m.m[0][0] * pos.x + m.m[3][0];
        float sy = m.m[2][1] * pos.z + m.m[1][1] * pos.y + m.m[0][1] * pos.x + m.m[3][1];
        float sw = m.m[2][3] * pos.z + m.m[1][3] * pos.y + m.m[0][3] * pos.x + m.m[3][3];
        float invW = 1.0f / sw;
        float ay = fabsf(invW * sy);
        float ax = fabsf(invW * sx);
        float d = 1.0f - MaxRef(ax, ay);
        float sizeFactor;
        if (d > 0.0f) {
            float one = 1.0f;
            float a = info.mBloomAlphaRate * d + info.mBloomAlphaBase;
            alpha = alpha * MinRef(a, one);
            float one2 = 1.0f;
            float b = info.mBloomSizeRate * d + info.mBloomSizeBase;
            sizeFactor = MinRef(b, one2);
        } else {
            alpha = info.mBloomAlphaBase * alpha;
            sizeFactor = info.mBloomSizeBase;
        }
        size = sizeFactor * size;
    }

    u8 r = ColorToByte(color.x);
    u8 g = ColorToByte(color.y);
    u8 b = ColorToByte(color.z);
    u8 a = ColorToByte(alpha);
    q.color = ((((u32)a << 8 | r) << 8 | g) << 8) | b;

    // Quad axes: camera-facing by default, aligned with the velocity when stretched.
    EA::Swarm::Vector3_s00f7_7940 axis0 = info.mAxis0;
    EA::Swarm::Vector3_s00f7_7940 axis1 = info.mAxis1;
    if (desc->mVelocityStretch != 0.0f) {
        EA::Swarm::Vector3_s00f7_7940 vel = particle->mVelocity;
        if (rigid.mFlags & 2)
            vel = Rotate(vel, rigid.mRotation);
        float v1 = vel.x * info.mAxis1.x + vel.z * info.mAxis1.z + vel.y * info.mAxis1.y;
        float v0 = vel.x * info.mAxis0.x + vel.z * info.mAxis0.z + vel.y * info.mAxis0.y;
        float len = sqrtf(v0 * v0 + v1 * v1);
        if (len > 1e-6f) {
            float inv = 1.0f / len;
            float cs = inv * v0;
            float sn = inv * v1;
            axis1.x = info.mAxis1.x * sn + info.mAxis0.x * cs;
            axis1.y = info.mAxis1.y * sn + info.mAxis0.y * cs;
            axis1.z = info.mAxis1.z * sn + info.mAxis0.z * cs;
            axis0.x = info.mAxis0.x * sn - info.mAxis1.x * cs;
            axis0.y = info.mAxis0.y * sn - info.mAxis1.y * cs;
            axis0.z = info.mAxis0.z * sn - info.mAxis1.z * cs;
            if (len > desc->mVelocityStretch) {
                float stretch = len / desc->mVelocityStretch;
                axis1.x = axis1.x * stretch;
                axis1.y = stretch * axis1.y;
                axis1.z = stretch * axis1.z;
            }
        }
    }

    // Particle spin.
    if (fabsf(rotation) > 1e-6f) {
        float s, cs;
        FastSinCos(EA::Swarm::gDegToRad * rotation, s, cs);
        axis1.x = axis1.x * cs - axis0.x * s;
        axis1.y = cs * axis1.y - s * axis0.y;
        axis1.z = cs * axis1.z - s * axis0.z;
    }

    q.pos = pos;
    q.t = t;
    q.axis = axis1;
    q.size = size;
}

static __forceinline void InitCurveLimits(const EA::Swarm::cParticlesDescription_s00f7_7940* desc, CurveLimits& lim)
{
    lim.color    = desc->mColorCurve.size() - 1;
    lim.alpha    = desc->mAlphaCurve.size() - 1;
    lim.aspect   = desc->mAspectCurve.size() - 1;
    lim.size     = desc->mSizeCurve.size() - 1;
    lim.rotation = desc->mRotationCurve.size() - 1;
}

struct V4F { float x, y, z, w; };

} // anonymous namespace
// ---- items of slice s00f77940 end

// ---- items of slice s00f79bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace math {
namespace fpu {
struct Vector2_s00f7_9bb0
{
    float x, y;
    Vector2_s00f7_9bb0() {}
    Vector2_s00f7_9bb0(float ax, float ay) : x(ax), y(ay) {}
    Vector2_s00f7_9bb0(const Vector2_s00f7_9bb0& v) : x(v.x), y(v.y) {}
};
}
}
}
namespace rw {
namespace math {
namespace fpu {
struct Vector3_s00f7_9bb0
{
    float x, y, z;
    Vector3_s00f7_9bb0() {}
    Vector3_s00f7_9bb0(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00f7_9bb0(const Vector3_s00f7_9bb0& v) : x(v.x), y(v.y), z(v.z) {}

    float SquaredLength() const { return x * x + y * y + z * z; }
    Vector3_s00f7_9bb0 operator-(const Vector3_s00f7_9bb0& v) const { return Vector3_s00f7_9bb0(x - v.x, y - v.y, z - v.z); }
    Vector3_s00f7_9bb0 operator*(float s) const { return Vector3_s00f7_9bb0(x * s, y * s, z * s); }
    Vector3_s00f7_9bb0& operator+=(const Vector3_s00f7_9bb0& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3_s00f7_9bb0& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
};
}
}
}
typedef rw::math::fpu::Vector2_s00f7_9bb0 Vector2_s00f7_9bb0;
typedef rw::math::fpu::Vector3_s00f7_9bb0 Vector3_s00f7_9bb0;
namespace EA {
namespace Random {
class RandomLinearCongruential_s00f7_9bb0
{ public:
    uint32_t mnSeed;
    double   RandomDoubleUniform();                 // 0x009360d0
    uint32_t RandomUint32Uniform(uint32_t nLimit);  // 0x00a68fb0
};  // namespace Random
}
}
namespace EA {
namespace SP {
 extern Random::RandomLinearCongruential_s00f7_9bb0 sMathRandom;   // 0x01601760
}
}
namespace EA {
namespace Swarm {
extern Random::RandomLinearCongruential_s00f7_9bb0 sRandom;    // 0x016778dc
}
}
namespace EA {
namespace Swarm {
extern uint64_t kSurfaceEmitFlags;                  // 0x016c9b94 (64-bit flag mask)  (name guessed)
}
}
namespace EA {
namespace Swarm {
extern uint32_t kSurfacePinFlags_s00f7_9bb0;                   // 0x015b0ee4  (name guessed)
}
}
namespace EA {
namespace Swarm {
struct ColorRGBA { float r, g, b, a; };
}
}
namespace EA {
namespace Swarm {
struct cBoundingBox_s00f7_9bb0 { Vector3_s00f7_9bb0 mMin, mMax; };
}
}
namespace EA {
namespace Swarm {
static __forceinline double RandomRangeM(double lo, double hi)
{
    double v = SP::sMathRandom.RandomDoubleUniform() * (hi - lo) + lo;
    if (v >= hi)
        return hi;
    if (lo > v)
        return lo;
    return v;
}
}
}
namespace EA {
namespace Swarm {
static __forceinline double RandomRangeS(double lo, double hi)
{
    double v = sRandom.RandomDoubleUniform() * (hi - lo) + lo;
    if (v >= hi)
        return hi;
    if (lo > v)
        return lo;
    return v;
}
}
}
namespace EA {
namespace Swarm {
static __forceinline double RandomRange(Vector2_s00f7_9bb0 range) { return RandomRangeM(range.x, range.y); }
}
}
namespace EA {
namespace Swarm {
static __forceinline double RandomVary(float vary) { return RandomRangeS(1.0f - vary, 1.0f + vary); }
}
}
namespace EA {
namespace Swarm {
static inline bool TestBit(uint32_t flags, int bit) { return ((flags >> bit) & 1) != 0; }
}
}
namespace EA {
namespace Swarm {
float   RandomInRange(const Vector2_s00f7_9bb0& range);                                    // 0x004df2d0
}
}
namespace EA {
namespace Swarm {
float   RandomSymmetric(float range);                                           // 0x00a78f80: random in [-range, range] from Swarm::sRandom (name guessed; 0x00572a60 is the sMathRandom twin)
}
}
namespace EA {
namespace Swarm {
Vector3_s00f7_9bb0 RandomPointInBox(const cBoundingBox_s00f7_9bb0& box);                              // 0x007cdbe0 (name guessed)
}
}
namespace EA {
namespace Swarm {
Vector3_s00f7_9bb0 RandomPointInEllipsoid(const cBoundingBox_s00f7_9bb0& box);                        // 0x00a816d0 (name guessed)
}
}
namespace EA {
namespace Swarm {
Vector3_s00f7_9bb0 RandomPointInTorus(const cBoundingBox_s00f7_9bb0& box, float width);               // 0x00a817c0 (name guessed)
}
}
namespace EA {
namespace Swarm {
struct cPathPoint;
}
}
namespace EA {
namespace Swarm {
struct cPathPoints { cPathPoint* mpBegin; cPathPoint* mpEnd; cPathPoint* mpCapacity; uint32_t mAllocator; };
}
}
namespace EA {
namespace Swarm {
struct cParticleBase_s00f7_9bb0                // +0x08 in cParticle
{
    float   mAge;
    float   mLife;
    Vector3_s00f7_9bb0 mPosition;
    Vector3_s00f7_9bb0 mVelocity;
};
}
}
namespace EA {
namespace Swarm {
bool PlaceParticleOnPath(cParticleBase_s00f7_9bb0* particle, const cPathPoints* path);    // 0x00a79660 (name guessed)
}
}
namespace EA {
namespace Swarm {
struct cParticle_s00f7_9bb0                    // older layout
{
    void*         mpNext;           // +0x00 intrusive_list_node
    void*         mpPrev;
    cParticleBase_s00f7_9bb0 mBase;            // +0x08
    float         mSize;            // +0x28
    float         mAspectRatio;     // +0x2c
    float         mRotation;        // +0x30
    float         mAlpha;           // +0x34
    Vector3_s00f7_9bb0       mColor;           // +0x38
    uint8_t       mFrame;           // +0x44
    uint8_t       mUnused[3];
    Vector3_s00f7_9bb0       mSurfaceNormal;   // +0x48 (name guessed)
};
}
}
namespace EA {
namespace Swarm {
struct cSurfaceInfo_s00f7_9bb0
{
    uint32_t mFlags;                // +0x00
    uint32_t mPad[7];
    float    mPinOffset;            // +0x20
};
}
}
namespace EA {
namespace Swarm {
struct ISurface_s00f7_9bb0
{
    virtual int  Release() = 0;
    virtual int  AddRef() = 0;
    virtual bool ApplySurface(float, const Vector3_s00f7_9bb0&, Vector3_s00f7_9bb0&, Vector3_s00f7_9bb0&, void*, void*) = 0;
    virtual float DistanceFromSurface(const Vector3_s00f7_9bb0& srcPoint, void*, void*) = 0;
    virtual bool FindClosestSurfacePoint(const Vector3_s00f7_9bb0& srcPoint, Vector3_s00f7_9bb0& dst, Vector3_s00f7_9bb0* normal,
                                         void* orientation, void* stateData, void* particleData) = 0;
};
}
}
namespace EA {
namespace Swarm {
struct cSurfaceRec_s00f7_9bb0                  // 0x18
{
    ISurface_s00f7_9bb0*     mpSurface;
    cSurfaceInfo_s00f7_9bb0* mpInfo;
    int           mHasStateData;    // (name guessed)
    int           mStateDataOffset; // (name guessed)
    uint32_t      mPad[2];
};
}
}
namespace EA {
namespace Swarm {
struct IEffectMap_s00f7_9bb0
{
    virtual int  AddRef() = 0;
    virtual int  Release() = 0;
    virtual void Start() = 0;
    virtual void Finish() = 0;
    virtual int  ModificationCount() = 0;
    virtual cBoundingBox_s00f7_9bb0 GetBounds() = 0;
    virtual bool PointInMap(const Vector3_s00f7_9bb0& position) = 0;
    virtual bool InWorldSpace() = 0;
    virtual float Height(const Vector3_s00f7_9bb0& position) = 0;
    virtual Vector3_s00f7_9bb0 Normal(const Vector3_s00f7_9bb0& position) = 0;
    virtual Vector3_s00f7_9bb0 Velocity(const Vector3_s00f7_9bb0& position) = 0;
    virtual ColorRGBA ColorAlpha(const Vector3_s00f7_9bb0& position) = 0;
};
}
}
namespace EA {
namespace Swarm {
struct cTransform_s00f7_9bb0                   // 0x38
{
    uint16_t mFlags;                // +0x00 (bit 1: has rotation)
    uint16_t mPad;
    Vector3_s00f7_9bb0  mTranslation;          // +0x04
    float    mScale;                // +0x10
    float    mRotation[3][3];       // +0x14 (row vectors)

    void Transform(Vector3_s00f7_9bb0& v) const;   // 0x007cdee0 (name guessed)

    Vector3_s00f7_9bb0 Rotate(const Vector3_s00f7_9bb0& v) const
    {
        float rx = mRotation[1][0] * v.y + mRotation[2][0] * v.z;
        rx += v.x * mRotation[0][0];
        float ry = mRotation[0][1] * v.x + mRotation[1][1] * v.y;
        ry += mRotation[2][1] * v.z;
        float rz = mRotation[0][2] * v.x + mRotation[1][2] * v.y;
        rz += mRotation[2][2] * v.z;
        return Vector3_s00f7_9bb0(rx, ry, rz);
    }
};
}
}
namespace EA {
namespace Swarm {
struct cGlobalParams_s00f7_9bb0
{
    uint32_t mPad[0x17];
    Vector3_s00f7_9bb0  mCameraRight;          // +0x5c (name guessed)
    uint32_t mPad2[3];
    Vector3_s00f7_9bb0  mCameraUp;             // +0x74 (name guessed)
};
}
}
namespace EA {
namespace Swarm {
struct cParticlesDescription_s00f7_9bb0        // older layout of the description (ModAPI ParticleEffect)
{
    uint32_t mPad0[2];
    uint64_t mFlags;                // +0x08 (bit 31: follow path; bit 4: ellipsoid; bit 3: stretch)
    Vector2_s00f7_9bb0  mLife;                 // +0x10
    uint32_t mPad18[5];
    cBoundingBox_s00f7_9bb0 mEmitDirection;    // +0x2c
    Vector2_s00f7_9bb0  mEmitSpeed;            // +0x44
    uint32_t mPad4c[6];
    float    mTorusWidth;           // +0x64
    uint32_t mPad68[8];
    float*   mSizeCurve;            // +0x88 eastl::vector<float>::mpBegin
    uint32_t mPad8c[4];
    float    mSizeVary;             // +0x9c
    uint32_t mPada0[5];
    float    mAspectRatioVary;      // +0xb4
    uint32_t mPadb8[5];
    float    mRotationVary;         // +0xcc
    uint32_t mPadd0[6];
    float    mColorVary[3];         // +0xe8
    uint32_t mPadf4[16];
    uint16_t mPad134;
    uint8_t  mFrameStride;          // +0x136 (name guessed)
    uint8_t  mFrameRandom;          // +0x137 (name guessed)
    uint32_t mPad138[6];
    float    mRadialForce;          // +0x150
    Vector3_s00f7_9bb0  mRadialForceLocation;  // +0x154
    float    mPad160;
    float    mStretchScale;         // +0x164 (name guessed)
    uint32_t mPad168[61];
    cPathPoints mPathPoints;        // +0x25c
};
}
}
namespace EA {
namespace Swarm {
class cParticlesEffectOld_s00f7_9bb0
{
public:
    uint32_t               mPad0[9];
    cParticlesDescription_s00f7_9bb0* mDesc;               // +0x24
    uint32_t               mPad28[2];
    cGlobalParams_s00f7_9bb0*         mGlobalParams;       // +0x30
    uint32_t               mPad34[31];
    cTransform_s00f7_9bb0             mSourceTransform;    // +0xb0
    cTransform_s00f7_9bb0             mRigidTransform;     // +0xe8
    uint32_t               mPad120[10];
    float                  mEmitVelocityScale;  // +0x148
    uint32_t               mPad14c[7];
    uint8_t                mFrameStart;         // +0x168
    uint8_t                mPad169[3];
    uint32_t               mPad16c[3];
    float                  mCurrentSizeScale;   // +0x178
    uint32_t               mPad17c[8];
    IEffectMap_s00f7_9bb0*            mEmitColorMap;       // +0x19c
    bool                   mPad1a0[2];
    bool                   mEmitColorMapInWorldSpace;   // +0x1a2
    bool                   mPad1a3;
    uint32_t               mPad1a4[2];
    cBoundingBox_s00f7_9bb0           mEmissionVolume;     // +0x1ac
    uint32_t               mPad1c4[4];
    cSurfaceRec_s00f7_9bb0*           mSurfaceRecsBegin;   // +0x1d4
    cSurfaceRec_s00f7_9bb0*           mSurfaceRecsEnd;     // +0x1d8
    uint32_t               mPad1dc[4];
    uint8_t*               mSurfaceStateData;   // +0x1ec
    uint32_t               mPad1f0[4];
    bool                   mHaveSurfacePin;     // +0x200
    uint8_t                mPad201[3];
    cPathPoints            mPathPoints;         // +0x204

    bool PlaceParticleOnSurface(cParticle_s00f7_9bb0* particle);   // 0x00f75c10 (name guessed)
    bool InitParticle(cParticle_s00f7_9bb0* particle);             // 0x00f79bf0 (name guessed)

    bool PlaceOnPath(cParticle_s00f7_9bb0* particle)
    {
        const cPathPoints* path = &mPathPoints;
        if (mPathPoints.mpBegin == mPathPoints.mpEnd)
            path = &mDesc->mPathPoints;
        return PlaceParticleOnPath(&particle->mBase, path);
    }
};
}
}
struct StreamGlobals {
    uint32_t mVtable0;                                  // +0x00
    uint32_t mPad4;                                     // +0x04
    uint32_t mFn8;                                      // +0x08
    uint32_t mFnC;                                      // +0x0c
    uint32_t mPad10[0x1c];                              // +0x10
};
StreamGlobals gStreamGlobals;                           // 0x016c9aa0
namespace EA {
namespace Swarm {
struct EffectSub {
    virtual void v0();
    virtual void v1();
    virtual void Set(int value);                        // +0x08
    virtual void Dispatch(int value);                   // +0x0c
    virtual bool Test();                                // +0x10
};
}
}
namespace EA {
namespace Swarm {
struct ParticleList {
    cParticle_s00f7_9bb0* mNext;                                   // +0x00 (sentinel)
    cParticle_s00f7_9bb0* mPrev;                                   // +0x04
    uint32_t mCount;                                    // +0x08
};
}
}
namespace EA {
namespace Swarm {
struct SwarmEmitterE {
    uint32_t mPad0[2];                                  // +0x00
    EffectSub mSub8;                                    // +0x08
    uint32_t mPadC[3];                                  // +0x0c
    ParticleList mList18;                               // +0x18
    cParticlesDescription_s00f7_9bb0* mDesc24;                     // +0x24
};
}
}
namespace EA {
namespace Swarm {
struct SwarmSystem {
    uint8_t mPad0[0x15];                                // +0x00
    uint8_t mField15;                                   // +0x15
    uint8_t mPad16[0xa];                                // +0x16
    uint32_t mField20;                                  // +0x20
    cParticlesDescription_s00f7_9bb0* mDesc24;                     // +0x24
    uint8_t mPad28[0x1f0];                              // +0x28
    SwarmEmitterE* mEffect218;                          // +0x218

    void InitParticle2(cParticle_s00f7_9bb0* particle);
    void Spawn(cParticle_s00f7_9bb0* particle);
};
}
}
namespace EA {
namespace Swarm {
cParticle_s00f7_9bb0* gFreeParticleList;                           // 0x016c9b68
}
}
// ---- items of slice s00f79bb0 end

// ---- items of slice s00f7a710 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_RadiansScale;      // 0x0167952c
extern double g1454410;                          // 0x01454410  (-1.0)
struct Vector3_s00f7_a710 {
    float x, y, z;
    Vector3_s00f7_a710() {}
    Vector3_s00f7_a710(const Vector3_s00f7_a710& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Matrix3 {
    Vector3_s00f7_a710 row[3];
    Matrix3() {}
    Matrix3(const Matrix3& o) { row[0] = o.row[0]; row[1] = o.row[1]; row[2] = o.row[2]; }
};
struct RawMatrix3 { float f[9]; };
struct OutRow { Vector3_s00f7_a710 v; float w; };
extern Matrix3 g_Identity3;       // 0x01679540
struct cTransform_s00f7_a710 {               // 0x38
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3_s00f7_a710 mTranslation;
    float mScale;
    Matrix3 mRotation;
    void RotateZ(float angle);                         // 0x007d1ac0
    void PostTransformBy(const cTransform_s00f7_a710& parent);    // 0x00a8a140
};
void __cdecl BuildBasisMode2(const Vector3_s00f7_a710* dir, Matrix3* out);   // 0x00a81a20
void __cdecl BuildBasisMode3(const Vector3_s00f7_a710* dir, Matrix3* out);   // 0x00a818f0
void __cdecl BuildBasisMode4(const Vector3_s00f7_a710* dir, Matrix3* out);   // 0x00a81b80
struct FloatVec { float* mpBegin; float* mpEnd; float* mpCap; };
struct Vec3Vec { Vector3_s00f7_a710* mpBegin; Vector3_s00f7_a710* mpEnd; Vector3_s00f7_a710* mpCap; };
struct Particle {
    Particle* mpNext;      // +0x00
    uint32_t pad04;
    float mAge;            // +0x08
    float mLifetime;       // +0x0c
    Vector3_s00f7_a710 mPos;          // +0x10
    Vector3_s00f7_a710 mDir;          // +0x1c
    float mSize;           // +0x28
    uint32_t pad2c;
    float mSpin;           // +0x30
    float mAlpha;          // +0x34
    float mColorMul[3];    // +0x38
};
struct EmitterInfo {
    uint32_t pad0[34];
    FloatVec mScaleCurve;      // +0x88
    uint32_t pad94[9];
    FloatVec mSpinCurve;       // +0xb8
    uint32_t padc4[3];
    float mSpinBase;           // +0xd0
    Vec3Vec mColorCurve;       // +0xd4
    uint32_t padE0[5];
    FloatVec mAlphaCurve;      // +0xf4
    uint32_t pad100[13];
    uint8_t mOrientMode;       // +0x134
};
struct IVertexStream {
    virtual int Acquire(int count, char** ppBuf, int* pStride);  // +0
    virtual void Commit();                                       // +4
};
inline float EvalCurve(const FloatVec& v, uint32_t n, float t)
{
    if (n == 0)
        return v.mpBegin[0];
    int i = (int)((float)n * t);
    float frac = (float)n * t - (float)i;
    if (frac > 0.0f) {
        float a = v.mpBegin[i];
        return (v.mpBegin[i + 1] - a) * frac + a;
    }
    return v.mpBegin[i];
}
inline Vector3_s00f7_a710 operator-(const Vector3_s00f7_a710& a, const Vector3_s00f7_a710& b)
{
    Vector3_s00f7_a710 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r;
}
inline Vector3_s00f7_a710 operator*(const Vector3_s00f7_a710& a, float s)
{
    Vector3_s00f7_a710 r; r.x = a.x * s; r.y = a.y * s; r.z = a.z * s; return r;
}
inline Vector3_s00f7_a710 operator+(const Vector3_s00f7_a710& a, const Vector3_s00f7_a710& b)
{
    Vector3_s00f7_a710 r; r.x = a.x + b.x; r.y = a.y + b.y; r.z = a.z + b.z; return r;
}
inline Vector3_s00f7_a710 EvalColorCurve(const Vec3Vec& v, uint32_t n, float t)
{
    if (n == 0)
        return v.mpBegin[0];
    int i = (int)((float)n * t);
    float frac = (float)n * t - (float)i;
    if (frac > 0.0f) {
        Vector3_s00f7_a710 d = v.mpBegin[i + 1] - v.mpBegin[i];
        return v.mpBegin[i] + d * frac;
    }
    return v.mpBegin[i];
}
struct cSwarmWriterA {
    uint32_t pad0[5];
    Particle* mpHead;          // +0x14
    uint32_t pad18;
    int mRemaining;            // +0x1c
    EmitterInfo* mpInfo;       // +0x20
    uint32_t pad24[48];
    cTransform_s00f7_a710 mWorld;         // +0xe4
    uint32_t pad11c[3];
    uint16_t mFrame;           // +0x128
    uint16_t pad12a;
    uint32_t pad12c[19];
    float mSizeMul;            // +0x178
    float mAlphaMul;           // +0x17c
    uint32_t pad180;
    float mColorMul[3];        // +0x184
    uint32_t pad190[37];
    uint8_t mColorOffset;      // +0x224 (matrix record offset)
    uint8_t mAlphaOffset;      // +0x225
    void Write(IVertexStream* pStream);
};
struct F1 { float f; };
extern F1 g16c9b28, g16c9b2c, g16c9b30;          // 0x016c9b28 / 2c / 30  (zero-initialised .data)
extern F1 g16c9b78, g16c9b7c;                    // 0x016c9b78 / 7c
extern F1 g16c9b80, g16c9b84, g16c9b88;          // 0x016c9b80 / 84 / 88
extern F1 g1485720;                              // 0x01485720  (1.0f)
extern F1 g1418f90;                              // 0x01418f90  (-10000.0f)
extern F1 g13f0620;                              // 0x013f0620  (+10000.0f)
void operator delete(void* p);                   // 0x00f47380
struct Matrix33Ctor {
    void Assign(const void* pSrc);                           // 0x0041cb40
};
struct IntrusiveListBase {
    void Destroy();                                          // 0x00620230
};
struct F218Object {
    uint32_t mPad0;            // +0x00
    uint32_t mPad4;            // +0x04
    void*    mpVtable;         // +0x08
};
struct HeapBlock {
    int32_t  mRefCount;        // allocation header immediately before the payload
};
struct RefVertex;
struct SpVectorRefVertex {     // EA::Swarm::SpVector<EA::Swarm::RefVertex>, size 0x14
    RefVertex* mpBegin;        // +0x00
    RefVertex* mpEnd;          // +0x04
    RefVertex* mpCapacity;     // +0x08
    void*      mpAllocName;    // +0x0c
    uint32_t   mAllocFlags;    // +0x10
    void Destroy();            // 0x00a8c440
};
struct cParticlesEffect_s00f7_a710 {       // size 0x238
    void*    mpVtbl0;                       // +0x000
    volatile void* mpVtbl1;                 // +0x004
    volatile void* mpVtbl2;                 // +0x008
    volatile void* mpVtbl3;                 // +0x00c
    int32_t  mF10;                          // +0x010
    bool     mStarted;                      // +0x014
    bool     mDelayedStopActive;            // +0x015
    bool     mIsVisible;                    // +0x016
    bool     mF17;                          // +0x017
    void*    mpParticlesHead;               // +0x018
    void*    mpParticlesAnchor;             // +0x01c
    int32_t  mParticleCount;                // +0x020
    void*    mpDesc;                        // +0x024
    uint32_t mCollectionIndex;              // +0x028
    void*    mpWorld;                       // +0x02c
    void*    mpGlobalParams;                // +0x030
    uint32_t mF34;                          // +0x034
    double   mOverallTime;                  // +0x038
    bool     mPreroll;                      // +0x040
    char     mPad41[7];                     // +0x041
    double   mParticleSystemTime;           // +0x048
    int32_t  mCurrentCycle;                 // +0x050
    uint32_t mF54;                          // +0x054
    double   mInverseRateCurveTime;         // +0x058
    float    mParticlesToGenerate;          // +0x060
    float    mDirectionalForcesSum[3];      // +0x064
    float    mRandomWalkNextTime;           // +0x070
    float    mRandomWalkStrengthV;          // +0x074
    float    mRandomWalkStrengthH;          // +0x078
    float    mRandomWalkTheta;              // +0x07c
    float    mF80;                          // +0x080
    float    mF84;                          // +0x084
    float    mAttractorForce;               // +0x088
    float    mAttractorLocation[3];         // +0x08c
    float    mAttractorIntensity;           // +0x098
    float    mRetriggerTime;                // +0x09c
    float    mF0a0;                         // +0x0a0
    float    mF0a4;                         // +0x0a4
    float    mF0a8;                         // +0x0a8
    float    mF0ac;                         // +0x0ac
    uint16_t mF0b0;                         // +0x0b0
    uint16_t mF0b2;                         // +0x0b2
    float    mF0b4;                         // +0x0b4
    float    mF0b8;                         // +0x0b8
    float    mF0bc;                         // +0x0bc
    float    mF0c0;                         // +0x0c0
    Matrix3  mMatrix0;                      // +0x0c4
    uint16_t mF0e8;                         // +0x0e8
    uint16_t mF0ea;                         // +0x0ea
    float    mF0ec;                         // +0x0ec
    float    mF0f0;                         // +0x0f0
    float    mF0f4;                         // +0x0f4
    float    mF0f8;                         // +0x0f8
    Matrix3  mMatrix1;                      // +0x0fc
    float    mF120;                         // +0x120
    float    mF124;                         // +0x124
    float    mF128;                         // +0x128
    uint16_t mF12c;                         // +0x12c
    uint16_t mF12e;                         // +0x12e
    float    mF130;                         // +0x130
    float    mF134;                         // +0x134
    float    mF138;                         // +0x138
    float    mF13c;                         // +0x13c
    float    mF140;                         // +0x140
    float    mF144;                         // +0x144
    float    mF148;                         // +0x148
    float    mF14c;                         // +0x14c
    float    mF150;                         // +0x150
    float    mF154;                         // +0x154
    float    mF158;                         // +0x158
    float    mF15c;                         // +0x15c
    float    mF160;                         // +0x160
    float    mF164;                         // +0x164
    uint32_t mF168;                         // +0x168
    float    mF16c;                         // +0x16c
    float    mF170;                         // +0x170
    float    mF174;                         // +0x174
    float    mF178;                         // +0x178
    float    mF17c;                         // +0x17c
    float    mF180;                         // +0x180
    float    mF184;                         // +0x184
    float    mF188;                         // +0x188
    float    mF18c;                         // +0x18c
    float    mF190;                         // +0x190
    void*    mpF194;                        // +0x194
    void*    mpF198;                        // +0x198
    void*    mpF19c;                        // +0x19c
    bool     mF1a0;                         // +0x1a0
    bool     mF1a1;                         // +0x1a1
    bool     mF1a2;                         // +0x1a2
    char     mPad1a3;                       // +0x1a3
    uint32_t mF1a4;                         // +0x1a4
    uint32_t mF1a8;                         // +0x1a8
    float    mF1ac;                         // +0x1ac
    float    mF1b0;                         // +0x1b0
    float    mF1b4;                         // +0x1b4
    float    mF1b8;                         // +0x1b8
    float    mF1bc;                         // +0x1bc
    float    mF1c0;                         // +0x1c0
    char     mPad1c4[4];                    // +0x1c4
    int32_t  mF1c8;                         // +0x1c8
    int32_t  mF1cc;                         // +0x1cc
    uint32_t mF1d0;                         // +0x1d0
    SpVectorRefVertex mRefVertices;         // +0x1d4
    bool     mF1e8;                         // +0x1e8
    char     mPad1e9[3];                    // +0x1e9
    void*    mpF1ec;                        // +0x1ec
    void*    mpF1f0;                        // +0x1f0
    void*    mpF1f4;                        // +0x1f4
    char     mPad1f8[8];                    // +0x1f8
    bool     mF200;                         // +0x200
    char     mPad201[3];                    // +0x201
    void*    mpF204;                        // +0x204
    void*    mpF208;                        // +0x208
    void*    mpF20c;                        // +0x20c
    char     mPad210[8];                    // +0x210
    F218Object* mpF218;                     // +0x218
    bool     mF21c;                         // +0x21c
    char     mPad21d[3];                    // +0x21d
    int32_t  mF220;                         // +0x220
    int32_t  mF224;                         // +0x224
    char     mPad228[6];                    // +0x228
    bool     mF22e;                         // +0x22e
    char     mPad22f[9];                    // +0x22f

    cParticlesEffect_s00f7_a710* Init(void* pDesc, uint32_t collectionIndex);
    void Destroy();
};
// ---- items of slice s00f7a710 end

// ---- items of slice s00f7b520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int*  g_16c9b68;                  // 0x016c9b68  free node list head
extern "C" char  g_16c9b58;                  // 0x016c9b58  FixedAllocatorBase
extern "C" int   g_15b0ebc[];               // 0x015b0ebc  per-type step callback table
extern "C" char* FUN_00f75fc0(void);                                  // 0x00f75fc0
extern "C" char  FUN_00f79bf0(char*);                                 // 0x00f79bf0
extern "C" void  FUN_00f58620(char*);                                 // 0x00f58620
extern "C" void  FUN_00f7a6a0(char*);                                 // 0x00f7a6a0
extern "C" void  FUN_00f7a5d0(char*);                                 // 0x00f7a5d0
extern "C" void  FUN_007cda70(float*);                                // 0x007cda70
extern "C" void  FUN_00a7ab40(int, void*, int, void*);                // 0x00a7ab40
extern "C" void* FUN_007d5590(void*, void*, void*, void*);            // 0x007d5590
extern "C" void* FUN_00aa8ea0(void*, void*);                          // 0x00aa8ea0
extern "C" char  EA_AddCore(void*, int, int);                         // 0x00bbc... FixedAllocatorBase::AddCore
typedef unsigned char uchar;
extern "C" void* FUN_00f473a0(u32, const char*, int, int, int, int);  // 0x00f473a0 EAAllocate
struct AllocObj { void* FUN_00f7afd0(void*, void*); };                // 0x00f7afd0 (thiscall)
int FUN_00f7be20(int, int);                                           // defined below
typedef int* (__thiscall *PFN_Get)(void*);
typedef int  (__thiscall *PFN_Slot)(void*, int, int, int, int, int);
struct Swarm_s00f7_b520 {
    int  FUN_00f7b520(int id, float* p, int n);
    void FUN_00f7ba80(float dt);
    void FUN_00f7bd70();
    void FUN_00f7bef0(int param_2);
};
// ---- items of slice s00f7b520 end

// ---- items of slice s00f7caf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
namespace EA {
namespace Swarm {
struct Vector3_s00f7_caf0
{
    float x, y, z;
    Vector3_s00f7_caf0() {}
    Vector3_s00f7_caf0(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3_s00f7_caf0(const Vector3_s00f7_caf0& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3_s00f7_caf0 operator*(float s) const { return Vector3_s00f7_caf0(x * s, y * s, z * s); }
    Vector3_s00f7_caf0 operator+(const Vector3_s00f7_caf0& v) const { return Vector3_s00f7_caf0(x + v.x, y + v.y, z + v.z); }
    Vector3_s00f7_caf0 operator-(const Vector3_s00f7_caf0& v) const { return Vector3_s00f7_caf0(x - v.x, y - v.y, z - v.z); }
    void Set(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }
    Vector3_s00f7_caf0& operator+=(const Vector3_s00f7_caf0& v) { Set(v.x + x, v.y + y, v.z + z); return *this; }
    Vector3_s00f7_caf0& operator*=(float s) { Set(x * s, y * s, z * s); return *this; }
    float SquaredLength() const { return y * y + z * z + x * x; }
    static Vector3_s00f7_caf0 Scaled(float s, const Vector3_s00f7_caf0& v) { return Vector3_s00f7_caf0(s * v.x, s * v.y, s * v.z); }
};
}
}
namespace EA {
namespace Swarm {
struct Vector2_s00f7_caf0
{
    float x, y;
    float Lerp(float t) const { return (y - x) * t + x; }
};
}
}
namespace EA {
namespace Swarm {
extern float kFXMaxFloat_s00f7_caf0;                    // 0x015B0EDC
}
}
namespace EA {
namespace Swarm {
struct cBoundingBox_s00f7_caf0
{
    Vector3_s00f7_caf0 mMin;
    Vector3_s00f7_caf0 mMax;
    void Reset()
    {
        float v = kFXMaxFloat_s00f7_caf0;
        mMin = Vector3_s00f7_caf0(v, v, v);
        mMax = Vector3_s00f7_caf0(-v, -v, -v);
    }
    void AddPoint(const Vector3_s00f7_caf0& p)
    {
        if (p.x < mMin.x) mMin.x = p.x;
        if (p.x > mMax.x) mMax.x = p.x;
        if (p.y < mMin.y) mMin.y = p.y;
        if (p.y > mMax.y) mMax.y = p.y;
        if (p.z < mMin.z) mMin.z = p.z;
        if (p.z > mMax.z) mMax.z = p.z;
    }
    void Transform(const struct cTransform_s00f7_caf0& xf);                 // 0x006E95A0
};
}
}
namespace EA {
namespace Swarm {
struct cTransform_s00f7_caf0
{
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3_s00f7_caf0 mTranslation;                                         // +0x04
    float mScale;                                                 // +0x10
    float mRotation[9];                                           // +0x14
    void TransformPoint(Vector3_s00f7_caf0& v) const;                        // 0x007CDEE0
    void InverseTransformPoint(Vector3_s00f7_caf0& v) const;                 // 0x007CDA70
    void BackTransformVector(Vector3_s00f7_caf0& v) const;                   // 0x00A78E90
};
}
}
namespace EA {
namespace Swarm {
template<int N> struct bitset
{
    uint32_t mWord[(N + 31) / 32];
    bool test(int i) const { return ((mWord[i >> 5] >> (i & 31)) & 1) != 0; }
};
}
}
namespace EA {
namespace Swarm {
template<class T> struct vector
{
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    T* begin() const { return mpBegin; }
    T* end() const { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
}
}
namespace EA {
namespace Swarm {
struct Color3 { float r, g, b; };
}
}
namespace EA {
namespace Swarm {
struct Color4 { float a; Color3 rgb; };
}
}
namespace EA {
namespace Swarm {
struct cEffectStateBlock
{
    uint32_t mField00;                                            // +0x00
    uint32_t mField04;                                            // +0x04
    uint8_t mStatus;                                              // +0x08
    uint8_t mType;                                                // +0x09
    uint8_t pad_0a[2];
    uint32_t mField0c;                                            // +0x0C
    uint32_t mField10;                                            // +0x10
    uint32_t mField14;                                            // +0x14
    uint32_t mField18;                                            // +0x18
    uint32_t mField1c;                                            // +0x1C
};
}
}
namespace EA {
namespace Swarm {
struct cSurfaceParam
{
    uint32_t mFlags;                                              // +0x00
    uint32_t pad_04;
    uint32_t mIdA;                                                // +0x08
    uint32_t mIdB;                                                // +0x0C
    uint32_t pad_10[18];
};
}
}
namespace EA {
namespace Swarm {
struct cEffectRef
{
    uint32_t mField00;
    uint32_t mField04;
    uint32_t mField08;
    uint32_t mField0c;
    uint32_t mField10;
    uint32_t mField14;
};
}
}
namespace EA {
namespace Swarm {
struct cEffectVector
{
    cEffectRef* mpBegin;
    cEffectRef* mpEnd;
    cEffectRef* mpCapacity;
    uint32_t mAllocator[2];
    cEffectRef* __thiscall erase(cEffectRef* first, cEffectRef* last);   // 0x00A8D020
};
}
}
namespace EA {
namespace Swarm {
struct cBoolVector
{
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCapacity;
    uint32_t mAllocator[2];

    void erase_range(uint8_t* first, uint8_t* last)
    {
        memcpy(first, last, (unsigned int)(mpEnd - last));
        mpEnd -= last - first;
    }
    void clear() { erase_range(mpBegin, mpEnd); }
    void DoInsertValues(uint8_t* position, uint32_t count, const bool& value);   // 0x004C10E0
    void resize(uint32_t n)
    {
        uint32_t cur = (uint32_t)(mpEnd - mpBegin);
        if (n > cur)
            DoInsertValues(mpEnd, n - cur, false);
        else
            erase_range(mpBegin + n, mpEnd);
    }
};
}
}
namespace EA {
namespace Swarm {
struct cIParam { virtual void AddRef(); virtual void Release(); virtual void v08(); virtual void v0c();
                 virtual uint32_t GetValue();                         // +0x10
virtual void v14();
virtual void v18();
virtual bool IsReady();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
                 virtual void v30(); };
}
}
namespace EA {
namespace Swarm {
struct cIParticleStream
{
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
    virtual void s10(uint8_t flags, uint8_t* out);                        // +0x10
    virtual void s14();
    virtual void s18(void* object, void* block, int* out);                // +0x18
    virtual void s1c();
    virtual void s20();
    virtual uint8_t s24(uint32_t a, uint32_t b, int c);                   // +0x24
    virtual void s28();
    virtual void s2c(void* base2, void* block, int* out);                 // +0x2C
};
}
}
namespace EA {
namespace Swarm {
struct cParamFactory
{
virtual void p00();
virtual void p04();
virtual void p08();
virtual void p0c();
    virtual void p10();
    virtual cIParticleStream* p14();                                      // +0x14
virtual void p18();
virtual void p1c();
virtual void p20();
virtual void p24();
virtual void p28();
virtual void p2c();
virtual void p30();
virtual void p34();
virtual void p38();
virtual void p3c();
virtual void p40();
virtual void p44();
virtual void p48();
virtual void p4c();
virtual void p50();
virtual void p54();
virtual void p58();
virtual void p5c();
virtual void p60();
virtual void p64();
virtual void p68();
virtual void p6c();
virtual void p70();
virtual void p74();
virtual void p78();
virtual void p7c();
virtual void p80();
virtual void p84();
    virtual void p88();
    virtual cIParam* CreateParam(uint32_t idA, uint32_t idB);             // +0x8C
};
}
}
namespace EA {
namespace Swarm {
enum
{
    kParticleFlagIgnoreLOD0 = 0,
    kParticleFlagIgnoreLOD1 = 1,
    kParticleFlagSizeScaleTransform = 11,
    kParticleFlagRandomWalk = 19,
    kParticleFlagModelStats = 21,
    kParticleFlagAttractor = 24,
    kParticleFlagScaleSizeOnly = 25,
    kParticleFlagSingleCycle = 28
};
}
}
namespace EA {
namespace Swarm {
struct cParticlesDescription_s00f7_caf0
{
    uint32_t pad_00[2];
    bitset<34> mFlags;                                            // +0x08
    Vector2_s00f7_caf0 mParticleLifetime;                                    // +0x10
    float mPrerollTime;                                           // +0x18
    uint32_t pad_1c[(0x4C - 0x1C) / 4];
    Vector3_s00f7_caf0 mColorParams1;                                        // +0x4C
    Vector3_s00f7_caf0 mColorParams2;                                        // +0x58
    uint32_t pad_64;
    vector<float> mRateCurve;                                     // +0x68
    float mRateCurveTime;                                         // +0x7C
    uint32_t pad_80[(0x88 - 0x80) / 4];
    vector<float> mSizeCurve;                                     // +0x88
    uint32_t pad_9c[(0x110 - 0x9C) / 4];
    cEffectStateBlock mStateBlock;                                // +0x110
    uint8_t mPhysicsType;                                         // +0x130
    uint8_t pad_131[0x135 - 0x131];
    uint8_t mPhysicsSubtype;                                      // +0x135
    uint8_t pad_136[0x13C - 0x136];
    Vector3_s00f7_caf0 mDirectionalForcesSum;                                // +0x13C
    float mWindStrength;                                          // +0x148
    float mGravityStrength;                                       // +0x14C
    float mRadialForce;                                           // +0x150
    Vector3_s00f7_caf0 mRadialForceLocation;                                 // +0x154
    float mDrag;                                                  // +0x160
    uint32_t pad_164[(0x1AC - 0x164) / 4];
    vector<cSurfaceParam> mSurfaceParams;                         // +0x1AC
    uint32_t pad_1c0[(0x1DC - 0x1C0) / 4];
    uint32_t mField1dc;                                           // +0x1DC
    uint32_t mField1e0;                                           // +0x1E0
    uint32_t pad_1e4;
    uint32_t mParamMask0A;                                        // +0x1E8
    uint32_t mParamMask0B;                                        // +0x1EC
    uint32_t mParamMask1A;                                        // +0x1F0
    uint32_t mParamMask1B;                                        // +0x1F4
    uint32_t mParamMask2A;                                        // +0x1F8
    uint32_t mParamMask2B;                                        // +0x1FC
    uint32_t pad_200[(0x234 - 0x200) / 4];
    Vector3_s00f7_caf0 mAttractorOrigin;                                     // +0x234
};
}
}
namespace EA {
namespace Swarm {
struct cGlobalParams_s00f7_caf0
{
    float mParticleDensity;                                       // +0x00
    float mParticleScale;                                         // +0x04
    int mParticleMultThreshold;                                   // +0x08
    uint32_t pad_0c[(0xBC - 0x0C) / 4];
    Vector3_s00f7_caf0 mWindDirection;                                       // +0xBC
    uint32_t pad_c8[(0xD8 - 0xC8) / 4];
    Vector3_s00f7_caf0 mGravityDirection;                                    // +0xD8
};
}
}
namespace EA {
namespace Swarm {
struct cParticle_s00f7_caf0
{
    cParticle_s00f7_caf0* mpNext;                                            // intrusive_list_node
    cParticle_s00f7_caf0* mpPrev;
    float mAge;                                                   // +0x08
    float mLifeTime;                                              // +0x0C
    Vector3_s00f7_caf0 mPosition;                                            // +0x10
    Vector3_s00f7_caf0 mVelocity;                                            // +0x1C
};
}
}
namespace EA {
namespace Swarm {
struct intrusive_list
{
    cParticle_s00f7_caf0* mpNext;
    cParticle_s00f7_caf0* mpPrev;
    cParticle_s00f7_caf0* begin() { return mpNext; }
    cParticle_s00f7_caf0* end() { return (cParticle_s00f7_caf0*)this; }
    cParticle_s00f7_caf0* erase(cParticle_s00f7_caf0* pNode)
    {
        cParticle_s00f7_caf0* const pPrev = pNode->mpPrev;
        cParticle_s00f7_caf0* const pNext = pNode->mpNext;
        pPrev->mpNext = pNext;
        pNext->mpPrev = pPrev;
        pNode->mpNext = 0;
        pNode->mpPrev = 0;
        return pNext;
    }
};
}
}
namespace EA {
namespace Swarm {
class cIRenderer_s00f7_caf0
{ public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void UpdateTextureParticles(int id, const cBoundingBox_s00f7_caf0& box, float maxSize);   // +0x20
    virtual void StopTextureParticles(int id, int arg);                                    // +0x24
virtual void v28();
virtual void v2c();
virtual void v30();
    virtual void UpdateModelParticles(int id, const cBoundingBox_s00f7_caf0& box, float maxSize);     // +0x34
    virtual void StopModelParticles(int id, int arg);                                      // +0x38
};
}
}
namespace EA {
namespace Swarm {
class cIEffectsWorld_s00f7_caf0
{ public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual cIRenderer_s00f7_caf0* GetRenderer();                                                     // +0x20
virtual void v24();
virtual void v28();
    virtual cGlobalParams_s00f7_caf0* GetGlobalParams();                                              // +0x2C
    virtual cParamFactory* GetParamFactory();                                              // +0x30
};
}
}
namespace EA {
namespace Swarm {
struct cSurfaceInfo;
}
}
namespace EA {
namespace Swarm {
struct cSurfaceRec_s00f7_caf0
{
    struct cISurface
    {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
        virtual void InitState(cSurfaceInfo* info, const cTransform_s00f7_caf0& src, const cTransform_s00f7_caf0& rigid, uint8_t* state); // +0x20
    };
    cISurface* mpSurface;                                         // +0x00
    cSurfaceInfo* mpInfo;                                         // +0x04
    uint32_t field_8;
    uint32_t mStateOffset;                                        // +0x0C
    uint32_t field_10;
    uint32_t field_14;
};
}
}
namespace EA {
namespace Swarm {
struct cStats
{
    uint32_t pad_00[4];
    int mTextureParticles;                                        // +0x10
    int mTextureParticlesRendered;                                // +0x14
    int mModelParticles;                                          // +0x18
    int mModelParticlesRendered;                                  // +0x1C
};
}
}
namespace EA {
namespace Swarm {
class cParticlesEffect_s00f7_caf0;
}
}
namespace EA {
namespace Swarm {
class cParticlesEffectCore;
}
}
namespace EA {
namespace Swarm {
typedef bool (*PhysicsUpdateFn)(cParticle_s00f7_caf0* p, float dt, cParticlesDescription_s00f7_caf0* desc, cParticlesEffect_s00f7_caf0* effect);
}
}
namespace EA {
namespace Swarm {
extern PhysicsUpdateFn sPhysicsUpdate[];                          // 0x015B0EBC
}
}
namespace EA {
namespace Swarm {
class cITextureParticleStreamer_s00f7_caf0 { public: virtual void StreamTextureParticles(); };
}
}
namespace EA {
namespace Swarm {
class cIModelParticleStreamer_s00f7_caf0 { public: virtual void StreamModelParticles(); };
}
}
namespace EA {
namespace Swarm {
class cIComponent_s00f7_caf0
{ public:
    virtual void c00();
    virtual void c04();
    virtual void c08();
    virtual bool Stop(bool hard);                                 // +0x0C
    virtual void ApplyEffect(float deltaTime, float lodFactor, cStats* stats);
};
}
}
namespace EA {
namespace Swarm {
class cComponentBase_s00f7_caf0 : public cIComponent_s00f7_caf0 { public: uint32_t mRefCountBase[2]; };
}
}
namespace EA {
namespace Swarm {
class cParticlesEffect_s00f7_caf0 : public cITextureParticleStreamer_s00f7_caf0, public cIModelParticleStreamer_s00f7_caf0, public cComponentBase_s00f7_caf0
{
public:
    bool mStarted;                                                // +0x14
    bool mDelayedStopActive;                                      // +0x15
    bool mIsVisible;                                              // +0x16
    bool mParamsChanged;                                          // +0x17
    intrusive_list mParticles;                                    // +0x18
    int mParticleCount;                                           // +0x20
    cParticlesDescription_s00f7_caf0* mDesc;                                 // +0x24
    uint32_t pad_28;
    cIEffectsWorld_s00f7_caf0* mWorld;                                       // +0x2C
    cGlobalParams_s00f7_caf0* mGlobalParams;                                 // +0x30
    uint32_t pad_34;
    double mOverallTime;                                          // +0x38
    bool mPreroll;                                                // +0x40
    double mParticleSystemTime;                                   // +0x48
    uint32_t pad_50[(0x64 - 0x50) / 4];
    Vector3_s00f7_caf0 mDirectionalForcesSum;                                // +0x64
    uint32_t pad_70;
    Vector3_s00f7_caf0 mAttractorLocation;                                   // +0x74
    float mAttractorIntensity;                                    // +0x80
    uint32_t pad_84;
    cBoundingBox_s00f7_caf0 mBoundingBox;                                    // +0x88
    float mMaxParticleSize;                                       // +0xA0
    uint32_t pad_a4[(0xB0 - 0xA4) / 4];
    cTransform_s00f7_caf0 mSourceTransform;                                  // +0xB0
    cTransform_s00f7_caf0 mRigidTransform;                                   // +0xE8
    Vector3_s00f7_caf0 mLastEmitLocation;                                    // +0x120
    uint16_t mRenderCount;                                        // +0x12C
    uint16_t mLastRenderCount;                                    // +0x12E
    Vector2_s00f7_caf0 mLODEmitScale;                                        // +0x130
    Vector2_s00f7_caf0 mLODSizeScale;                                        // +0x138
    Vector2_s00f7_caf0 mLODAlphaScale;                                       // +0x140
    uint32_t pad_148;
    float mEmitScale;                                             // +0x14C
    float mSizeScale;                                             // +0x150
    float mAlphaScale;                                            // +0x154
    Color4 mColorScale;                                           // +0x158
    uint32_t pad_168[3];
    float mCurrentEmitRateScale;                                  // +0x174
    float mCurrentEmitSizeScale;                                  // +0x178
    float mCurrentSizeScale;                                      // +0x17C
    float mCurrentAlphaScale;                                     // +0x180
    Color4 mCurrentColorScale;                                    // +0x184
    uint32_t pad_194;
    cIParam* mParamA;                                             // +0x198
    cIParam* mParamB;                                             // +0x19C
    uint32_t pad_1a0;
    uint32_t mCachedParamA;                                       // +0x1A4
    uint32_t mCachedParamB;                                       // +0x1A8
    uint32_t pad_1ac[(0x1D4 - 0x1AC) / 4];
    vector<cSurfaceRec_s00f7_caf0> mSurfaceRecs;                             // +0x1D4
    bool mSurfaceStateDataValid;                                  // +0x1E8
    vector<uint8_t> mSurfaceStateData;                            // +0x1EC
    uint32_t pad_200[(0x218 - 0x200) / 4];
    cParticlesEffect_s00f7_caf0* mChainSystem;                               // +0x218
    bool mSuppressEmission;                                       // +0x21C
    int mModelParticlesID;                                        // +0x220
    int mTextureParticlesID;                                      // +0x224

    void DestroyParticle(cParticle_s00f7_caf0* p);                           // 0x00AAF670
    void RemoveParticle(cParticle_s00f7_caf0* p)
    {
        --mParticleCount;
        DestroyParticle(p);
    }
    void GenerateNewParticles(float deltaTime);                   // 0x00AB1840
    virtual void ApplyEffect(float deltaTime, float lodFactor, cStats* stats);
};
}
}
namespace EA {
namespace Swarm {
struct cParticleBase0 { virtual void b00(); };
}
}
namespace EA {
namespace Swarm {
struct cParticleBase1 { virtual void b10(); };
}
}
namespace EA {
namespace Swarm {
class cParticlesEffectCore : public cParticleBase0, public cParticleBase1
{
public:
    uint32_t pad_08[(0x24 - 0x08) / 4];
    cParticlesDescription_s00f7_caf0* mDesc;                                 // +0x24
    uint32_t pad_28[(0x58 - 0x28) / 4];
    double mRateCurveTimeInv;                                     // +0x58
    uint32_t pad_60[(0x74 - 0x60) / 4];
    Vector3_s00f7_caf0 mAttractorLocation;                                   // +0x74
    float mAttractorIntensity;                                    // +0x80
    uint32_t pad_84[(0xA0 - 0x84) / 4];
    float mMaxParticleSize;                                       // +0xA0
    uint32_t pad_a4[(0xE8 - 0xA4) / 4];
    cTransform_s00f7_caf0 mRigidTransform;                                   // +0xE8
    uint32_t pad_120[(0x168 - 0x120) / 4];
    uint32_t mPhysicsType;                                        // +0x168
    uint32_t mPhysicsField16c;                                    // +0x16C
    uint32_t mPhysicsField170;                                    // +0x170
    uint32_t pad_174[(0x194 - 0x174) / 4];
    cIParam* mParam0;                                             // +0x194
    cIParam* mParamA;                                             // +0x198
    cIParam* mParamB;                                             // +0x19C
    bool mParam0Ready;                                            // +0x1A0
    bool mParamAReady;                                            // +0x1A1
    bool mParamBReady;                                            // +0x1A2
    uint8_t pad_1a3;
    uint32_t mCachedParamA;                                       // +0x1A4
    uint32_t mCachedParamB;                                       // +0x1A8
    Vector3_s00f7_caf0 mColorParams1;                                        // +0x1AC
    Vector3_s00f7_caf0 mColorParams2;                                        // +0x1B8
    uint32_t pad_1c4[(0x1D4 - 0x1C4) / 4];
    cEffectVector mSurfaceRecs;                                   // +0x1D4
    bool mSurfaceStateDataValid;                                  // +0x1E8
    uint8_t pad_1e9[3];
    cBoolVector mSurfaceStateData;                                // +0x1EC
    bool mStateDirty;                                             // +0x200

    void F7d3d0(cParamFactory* mgr);                              // 0x00F7D3D0
};
}
}
namespace EA {
namespace Swarm {
class cParticlesEffectView
{
public:
    virtual void v00();                                           // +0x00 component vftable
    uint32_t mRefCount[2];                                        // +0x04 (cComponentBase::mRefCountBase)
    uint32_t pad_0c[(0x1C - 0x0C) / 4];
    cParticlesDescription_s00f7_caf0* mDesc;                                 // +0x1C
    uint32_t pad_20;
    cIEffectsWorld_s00f7_caf0* mWorld;                                       // +0x24
    cGlobalParams_s00f7_caf0* mGlobalParams;                                 // +0x28
    uint32_t pad_2c[(0x80 - 0x2C) / 4];
    cBoundingBox_s00f7_caf0 mBoundingBox;                                    // +0x80
    uint32_t pad_98[(0x1C0 - 0x98) / 4];
    uint32_t mSurfaceParamMaskA;                                  // +0x1C0
    uint32_t mSurfaceParamMaskB;                                  // +0x1C4
    uint32_t pad_1c8[(0x218 - 0x1C8) / 4];
    int mModelParticlesID;                                        // +0x218
    int mTextureParticlesID;                                      // +0x21C
    uint8_t mStreamState[5];                                      // +0x220
    uint8_t pad_225;
    uint8_t mStreamFlag;                                          // +0x226

    cParticlesEffectCore* core() { return (cParticlesEffectCore*)((char*)this - 8); }
    void F7d7a0(cIEffectsWorld_s00f7_caf0* world, cParamFactory* mgr, void* unused);  // 0x00F7D7A0
    void F7d990(cParticlesDescription_s00f7_caf0* desc);                     // 0x00F7D990
};
}
}
namespace EA {
namespace Swarm {
extern Vector3_s00f7_caf0 gZeroVector;                                       // 0x016C9B28
}
}
namespace EA {
namespace Swarm {
void BuildSurfaceRecs(cParamFactory* mgr, vector<cSurfaceParam>* params, cEffectVector* recs,
                      int* size0, int* size1, bool* dirty);       // 0x00A7FC10
}
}
namespace EA {
namespace Swarm {
__forceinline bool UpdatePhysicsSimple(cParticle_s00f7_caf0* p, float dt, cParticlesDescription_s00f7_caf0* desc, cParticlesEffect_s00f7_caf0* effect)
{
    p->mAge += dt;
    if (p->mAge >= p->mLifeTime)
        return false;
    Vector3_s00f7_caf0 oldVelocity = p->mVelocity;
    p->mVelocity += effect->mDirectionalForcesSum * dt;
    p->mVelocity *= 1.0f - desc->mDrag * dt;
    p->mPosition += (p->mVelocity + oldVelocity) * (dt * 0.5f);
    return true;
}
}
}
// ---- items of slice s00f7caf0 end

// @ 0x00f70440
int CubeOwner::CountSubs()
{
	CubeInner* in = mpInner;
	void* p1 = in->mp08;
	void* p2 = in->mp14;
	int a;
	if (p1)
		a = *(int*)((char*)p1 + 0xc);
	else
		a = 0;
	int b;
	if (p2)
		b = *(int*)((char*)p2 + 0xc);
	else
		b = 0;
	return a + b;
}

// @ 0x00f70870
int CubeOwner::CountSubsEffect()
{
	CubeInner* in = mpInner;
	void* a = in->mp08;

	void* mgr = EffectsManager();
	IEffect* obj = ((PFN_MgrLookup)(*(void***)mgr)[0x8c / 4])(mgr, 0x107ae878, 0);
	if (obj != NULL)
		obj->vt00();

	int x;
	if (a)
		x = *(int*)((char*)a + 0xc);
	else
		x = 0;
	int y;
	if (obj)
		y = obj->vt10();
	else
		y = 0;
	x = x + y;
	if (obj)
		obj->vt04();
	return x;
}

// @ 0x00f71220
float CCubeQuery::QueryD(const V4* dir)
{
    float m[9];
    V4 camLoc;
    V4 camDir;

    Matrix33Assign(m, &DAT_016c9a20);
    GetCameraLocationInfo(mpViewer, &camLoc, 0, 0, 0);
    GetCameraDirInfo(mpViewer, &camDir);

    float dx = dir->x, dy = dir->y, dz = dir->z;
    float dscale = 1.0f / SqrtF((dx * dx + dy * dy + dz * dz) + DAT_013ec4b8);
    float cscale = 1.0f / SqrtF(camLoc.x * camLoc.x + camLoc.y * camLoc.y + camLoc.z * camLoc.z);

    camDir.x += cscale * camLoc.x;
    camDir.y += camLoc.y * cscale;
    camDir.z += camLoc.z * cscale;

    float nscale = 1.0f / SqrtF(camDir.x * camDir.x + camDir.y * camDir.y + camDir.z * camDir.z);
    float dot = (camDir.z * nscale) * (dz * dscale)
              + (camDir.y * nscale) * (dy * dscale)
              + (nscale * camDir.x) * (dscale * dx);

    float v = dot;
    if (v < 0.0f)
        v = 0.0f;
    if (v > 1.0f)
        v = 1.0f;
    float v2 = v * v;
    return v2 * v2;
}

// @ 0x00f713c0
V4* CCubeQuery::GetCubeUV()
{
    void* p = mpCtx->mpUV;
    if (p)
        return *(V4**)((char*)p + 0x0c);
    return 0;
}

// @ 0x00f715d0
V4* CCubeQuery::GetColorA(V4* out)
{
    const float* p = (const float*)((char*)mpTerrain + 0x42c);
    out->w = DAT_01485720;
    out->x = p[0];
    out->y = p[1];
    out->z = p[2];
    return out;
}

// @ 0x00f71610
V4* CCubeQuery::GetColorB(V4* out)
{
    const float* p = (const float*)((char*)mpTerrain + 0x59c);
    out->x = p[0];
    out->y = p[1];
    out->w = DAT_01485720;
    out->z = p[2];
    return out;
}

// @ 0x00f71660
int QueryScaleA()
{
    IEff* eff = (IEff*)EffGet(EffectsManager(), 0x107ae878, 0);
    if (!eff)
        return 0;
    EffAddRef(eff);
    int r = (int)EffCall10(eff);
    EffRelease(eff);
    return r;
}

// @ 0x00f716b0
V4* CCubeQuery::GetScaledColor(V4* out, const V4* unused)
{
    IEff* eff = (IEff*)EffGet(EffectsManager(), 0x107ae878, 0);
    if (eff)
        EffAddRef(eff);
    float s = 1.0f;
    if (eff) {
        s = EffCall20(eff, unused);
        if (eff)
            EffRelease(eff);
    }
    const float* p = (const float*)((char*)mpTerrain + 0x59c);
    out->x = p[0] * s;
    out->y = p[1] * s;
    out->z = p[2] * s;
    out->w = s;
    if (eff)
        EffRelease(eff);
    return out;
}

// @ 0x00f71760
void* RefCountedDtor(void* self, unsigned char flags)
{
    int* rc = *(int**)((char*)self + 0x0c);
    if (rc) {
        int n = rc[1] - 1;
        rc[1] = n;
        if (n == 0) {
            rc[1] = 1;
            (*(void(**)(int))(*rc))(1);
        }
    }
    *(void**)((char*)self + 4) = (void*)0x013ef094;
    if (flags & 1)
        EAFreeOp(self);
    return self;
}

// @ 0x00f71f30
float cTerrainProbe::distance(const float* pos, int a, int b)
{
    float hit[3];
    if (castPoint(pos, hit, 0, 0, a, b)) {
        float dx = pos[0] - hit[0];
        float dy = pos[1] - hit[1];
        float dz = pos[2] - hit[2];
        return sqrtf(dx * dx + dy * dy + dz * dz);
    }
    return 0.0f;
}

// @ 0x00f71f90
void __stdcall SetTransformHeight(cTerrainHeightSource* src, const void* unused, const void* blob, cSPTransformOps* xf)
{
    xf->Assign(blob);
    xf->mHeight = 0;
    const float* p = src->mBegin;
    if (p != src->mEnd)
        xf->mHeight = *p;
}

// @ 0x00f74fe0
bool UpdateParticle(cParticle* particle, float dt, const cParticlesDescription* desc, cParticlesEffectOld* effect)
{
    particle->mBase.mAge += dt;
    if (!(particle->mBase.mAge < particle->mBase.mLife))
        return false;

    // emission anchor and particle point, both taken through the rigid transform
    Vector3 emit = effect->mRigidTransform.TransformPoint(effect->mSourceTransform.mTranslation);
    Vector3 pos = effect->mRigidTransform.TransformPoint(particle->mBase.mPosition);

    float distSqEmit = emit.x * emit.x + emit.z * emit.z + emit.y * emit.y;
    float distSqPos = pos.x * pos.x + pos.z * pos.z + pos.y * pos.y;
    const float eps = kFXSampleEpsilon;
    float dot = pos.x * emit.x + pos.z * emit.z + pos.y * emit.y;
    float limit = (distSqEmit / (eps * eps + distSqEmit)) * distSqEmit * distSqPos;
    float dotSq = dot * dot;

    if (dotSq < limit) {
        if ((float)sRandom_Swarm.RandomDoubleUniform() >= kFXRandThreshold) {
            // pull the particle towards the emission axis by a random fraction
            float s = dot / distSqEmit;
            double r = sRandom_Swarm.RandomDoubleUniform();
            float t = (s / (float)sqrt((double)(distSqPos - s * dot))) * eps;
            float f = (float)(2.0 * (r + (1.0 - r) * (double)t));
            particle->mBase.mPosition = Vector3((emit.x * s - pos.x) * f + pos.x,
                                                (emit.y * s - pos.y) * f + pos.y,
                                                (emit.z * s - pos.z) * f + pos.z);
        } else if (desc->mTorusWidth < 0.0f) {
            // random point in the emission volume, then into effect space
            Vector3 p = ((desc->mFlags & cParticlesDescription::kFlagEllipsoid) != 0)
                            ? FUN_00a816d0(effect->mEmissionVolume)
                            : FUN_007cdbe0(effect->mEmissionVolume);
            particle->mBase.mPosition = p;
            effect->mSourceTransform.Transform(particle->mBase.mPosition);
        } else {
            Vector3 p = FUN_00a817c0(effect->mEmissionVolume, desc->mTorusWidth);
            particle->mBase.mPosition = p;
            effect->mSourceTransform.Transform(particle->mBase.mPosition);
        }

        particle->mAlpha = 1.0f;

        if ((desc->mFlags & cParticlesDescription::kFlagPinToMap) != 0 && effect->mEmitMap != 0) {
            Vector3 p = particle->mBase.mPosition;
            if (effect->mEmitMapInWorldSpace)
                effect->mRigidTransform.Transform(p);
            else
                effect->mSourceTransform.InverseTransformPoint(p);
            if (effect->mEmitMap->PointInMap(p)) {
                float height = effect->mEmitMap->Height(p);
                Vector2 range(effect->mEmissionVolume.mMin.z, effect->mEmissionVolume.mMax.z);
                height += (float)FUN_007cdb90(range);
                p.z = height;
                if (effect->mEmitMapInWorldSpace)
                    effect->mRigidTransform.InverseTransformPoint(p);
                else
                    effect->mSourceTransform.Transform(p);
                particle->mBase.mPosition = p;
            }
        }

        particle->mColor.x = (float)FUN_007d45d0(1.0f, desc->mColorVary[0]);
        particle->mColor.y = (float)FUN_007d45d0(1.0f, desc->mColorVary[1]);
        particle->mColor.z = (float)FUN_007d45d0(1.0f, desc->mColorVary[2]);

        if (effect->mEmitColorMap != 0) {
            Vector3 p = particle->mBase.mPosition;
            if (effect->mEmitColorMapInWorldSpace)
                effect->mRigidTransform.Transform(p);
            else
                effect->mSourceTransform.InverseTransformPoint(p);
            if (effect->mEmitColorMap->PointInMap(p)) {
                Vector4 color;
                effect->mEmitColorMap->ColorAlpha(&color, p);
                particle->mAlpha *= color.w;
                FUN_00705290(&particle->mColor, &color);
            }
        }

        if (effect->mEmitMap != 0) {
            Vector3 p = particle->mBase.mPosition;
            if (effect->mEmitMapInWorldSpace)
                effect->mRigidTransform.Transform(p);
            else
                effect->mSourceTransform.InverseTransformPoint(p);
            float height = effect->mEmitMap->Height(p);
            if (kFXHeightCutoff > height)
                particle->mAlpha = 0.0f;
        }
    }

    if (!effect->mForcePin && !(dotSq < limit))
        return true;
    if (!effect->mHaveSurfacePin)
        return true;

    uint8_t* stateData = effect->mSurfaceStateData;
    for (cSurfaceRec* rec = effect->mSurfaceRecsBegin; rec != effect->mSurfaceRecsEnd; ++rec) {
        if ((rec->mpInfo->mFlags & kSurfacePinFlags) == 0)
            continue;
        void* state = rec->mHasStateData ? stateData + rec->mStateDataOffset : 0;
        Vector3 normal;
        if (rec->mpSurface->FindClosestSurfacePoint(particle->mBase.mPosition,
                                                    particle->mBase.mPosition, &normal, 0, state, 0)) {
            float pinOffset = rec->mpInfo->mPinOffset;
            if (pinOffset != 0.0f) {
                particle->mBase.mPosition.x += pinOffset * normal.x;
                particle->mBase.mPosition.y += pinOffset * normal.y;
                particle->mBase.mPosition.z += pinOffset * normal.z;
            }
            particle->mSurfaceNormal = normal;
            break;
        }
    }

    particle->mColor.x = (float)RandRange(1.0 - desc->mColorVary[0], 1.0 + desc->mColorVary[0]);
    particle->mColor.y = (float)RandRange(1.0 - desc->mColorVary[1], 1.0 + desc->mColorVary[1]);
    particle->mColor.z = (float)RandRange(1.0 - desc->mColorVary[2], 1.0 + desc->mColorVary[2]);

    if (effect->mEmitColorMap != 0) {
        Vector3 p = particle->mBase.mPosition;
        if (effect->mEmitColorMapInWorldSpace)
            effect->mRigidTransform.Transform(p);
        else
            effect->mSourceTransform.InverseTransformPoint(p);
        if (effect->mEmitColorMap->PointInMap(p)) {
            Vector4 color;
            effect->mEmitColorMap->ColorAlpha(&color, p);
            particle->mAlpha *= color.w;
            particle->mColor.x *= color.x;
            particle->mColor.y *= color.y;
            particle->mColor.z *= color.z;
        }
    }
    return true;
}

// @ 0x00f75990
void cDistributeEffectOld::SetTransforms(const void* pSource, const void* pRigid)
{
    mSourceTransform.Assign(pSource);
    mRigidTransform.Assign(pRigid);

    const Vector3 oldPosition = mPosition;
    mPosition = mSourceTransform.mTranslation;
    mTransformDirty = 0;

    if (mRigidTransform.mFlags & cTransform::kHasRotation)
        mPosition = mRigidTransform.Rotate(mPosition);
    mPosition *= mRigidTransform.mScale;
    mPosition += mRigidTransform.mTranslation;

    if (mBoundsMin.x != kFXMaxFloat && mBoundsMin.x != -kFXMaxFloat) {
        Vector3 delta(mPosition.x - oldPosition.x, mPosition.y - oldPosition.y,
                      mPosition.z - oldPosition.z);
        mBoundsMin += delta;
        mBoundsMax += delta;
    }
}

// @ 0x00f75c10
bool AttachPointUpdater::UpdateAttachPoint(AttachPoint* io)
{
    Vec3 pos;
    pos.x = io->mPosition.x;
    pos.y = io->mPosition.y;
    pos.z = io->mPosition.z;
    if (mEnabled) {
        if (mXformA.mFlags & 2) {
            Vec3 transformed;
            transformed.x = (mXformA.mMatrix[3] * pos.y + mXformA.mMatrix[6] * pos.z)
                            + mXformA.mMatrix[0] * pos.x;
            transformed.y = (mXformA.mMatrix[4] * pos.y + mXformA.mMatrix[7] * pos.z)
                            + mXformA.mMatrix[1] * pos.x;
            transformed.z = (mXformA.mMatrix[5] * pos.y + mXformA.mMatrix[8] * pos.z)
                            + mXformA.mMatrix[2] * pos.x;
            pos = transformed;
        }
        pos.x = mXformA.mScale * pos.x + mXformA.mPosition.x;
        pos.y = mXformA.mPosition.y + mXformA.mScale * pos.y;
        pos.z = mXformA.mPosition.z + mXformA.mScale * pos.z;
        if (mXformB.mFlags & 2) {
            Vec3 transformed;
            transformed.x = (mXformB.mMatrix[3] * pos.y + mXformB.mMatrix[6] * pos.z)
                            + mXformB.mMatrix[0] * pos.x;
            transformed.y = (mXformB.mMatrix[4] * pos.y + mXformB.mMatrix[7] * pos.z)
                            + mXformB.mMatrix[1] * pos.x;
            transformed.z = (mXformB.mMatrix[5] * pos.y + mXformB.mMatrix[8] * pos.z)
                            + mXformB.mMatrix[2] * pos.x;
            pos = transformed;
        }
        pos.x = mXformB.mPosition.x + mXformB.mScale * pos.x;
        pos.y = mXformB.mPosition.y + mXformB.mScale * pos.y;
        pos.z = mXformB.mPosition.z + mXformB.mScale * pos.z;
    }
    AttachTarget* target = mpTarget;
    if (!target)
        return false;
    if (!target->Accept(&pos))
        return false;
    float range = mpTarget->GetRange(&pos);
    unsigned flags = mpConfig->mFlags;
    bool bRangeCheck = ((flags >> 6) & 1) != 0;
    bool bRandomCheck = ((flags >> 7) & 1) != 0;
    if (bRangeCheck) {
        if (range < mMinRange)
            return false;
        if (range > mMaxRange)
            return false;
    } else if (bRandomCheck) {
        if (!(_sRandomGlobal.RandomDouble() < range))
            return false;
    }
    unsigned flags2 = mpConfig->mFlags;
    bool bOffset = ((flags2 >> 5) & 1) != 0;
    if (bOffset) {
        pos.z = range;
        SP::Vector2_s004d_f2d0 offset;
        offset.mData[0] = mField1b4;
        offset.mData[1] = mField1c0;
        pos.z = pos.z + SP::RandomInRange(offset);
    }
    Vec3 zero;
    zero.x = 0.0f;
    zero.y = 0.0f;
    zero.z = 0.0f;
    io->mField48 = zero;
    if (mEnabled) {
        mXformB.InverseTransformPoint(&pos);
        mXformA.InverseTransformPoint(&pos);
    }
    io->mPosition = pos;
    return true;
}

// @ 0x00f75fc0
PoolNode* AllocPoolNode()
{
    PoolNode* p;
    do {
        p = sPool.mpFreeHead;
        if (p)
            break;
    } while (sPool.AddCore(0, 0));
    if (!p)
        return 0;
    sPool.mpFreeHead = p->mpNext;
    p->mField4 = 0;
    p->mpNext = 0;
    return p;
}

// @ 0x00f76000
extern "C" void BuildDrawParams2(int param_1, EffectObject* p, DrawParams* out)
{
    char* c = (char*)p;
    float* o = (float*)out;

    switch (p->mode) {
    case 1:
    case 5: {
        float cx = (p->x1 + p->x0) * 0.5f;
        float cy = (p->y1 + p->y0) * 0.5f;
        float cz = (p->z1 + p->z0) * 0.5f;
        if (p->mode == 1) {
            FUN_00a7d6b0((char*)param_1 + 0xb0, 0, &cx);
            FUN_00a7d6b0((char*)param_1 + 0xe8, 0, &cx);
        }
        float d = cy * g_a8 - cz * g_a4;
        float e = cz * g_a0 - cx * g_a8;
        float f = cx * g_a4 - cy * g_a0;
        float len = InlineSqrt(f * f + e * e + d * d);
        if (len <= 0.0001f) {
            out->v0 = g_ac; out->v1 = g_b0; out->v2 = g_b4;
            out->v3 = g_b8; out->v4 = g_bc;
            len = g_c0;
        } else {
            float inv = 1.0f / len;
            float nx = inv * d;
            float ny = e * inv;
            o[0] = nx;
            float nz = f * inv;
            o[1] = ny;
            o[2] = nz;
            float bx = o[2] * g_a4 - o[1] * g_a8;
            float by = o[0] * g_a8 - o[2] * g_a0;
            float bz = o[1] * g_a0 - o[0] * g_a4;
            o[3] = bx;
            o[4] = by;
            len = bz;
        }
        o[5] = len;
        if (p->mode == 5) {
            FUN_00a7d6b0((char*)param_1 + 0xb0, 0, o);
            FUN_00a7d6b0((char*)param_1 + 0xb0, 0, o + 3);
            FUN_00a7d6b0((char*)param_1 + 0xe8, 0, o);
            FUN_00a7d6b0((char*)param_1 + 0xe8, 0, o + 3);
        }
        break;
    }
    case 6: {
        float* b = o + 3;
        b[0] = g_a0; b[1] = g_a4; b[2] = g_a8;
        FUN_00a7d6b0((char*)param_1 + 0xb0, 0, b);
        FUN_00a7d6b0((char*)param_1 + 0xe8, 0, b);
        float* pa = *(float**)((char*)param_1 + 0x30);
        o[0] = pa[0x68 / 4]; o[1] = pa[0x6c / 4]; o[2] = pa[0x70 / 4];
        float fy = o[1], fx = o[0];
        o[0] = o[5] * fy - o[4] * o[2];
        o[1] = b[0] * o[2] - o[5] * fx;
        o[2] = o[4] * fx - b[0] * fy;
        float inv = 1.0f / (InlineSqrt(o[0] * o[0] + o[1] * o[1] + o[2] * o[2]) + 0.1f);
        o[0] *= inv; o[1] *= inv; o[2] *= inv;
        break;
    }
    case 7: {
        float* pd = *(float**)((char*)param_1 + 0x30);
        o[3] = pd[0xf4 / 4]; o[4] = pd[0xf8 / 4]; o[5] = pd[0xfc / 4];
        float* pa = *(float**)((char*)param_1 + 0x30);
        o[0] = pa[0x68 / 4]; o[1] = pa[0x6c / 4]; o[2] = pa[0x70 / 4];
        float fy = o[1], fx = o[0];
        o[0] = o[5] * fy - o[4] * o[2];
        o[1] = o[3] * o[2] - o[5] * fx;
        o[2] = o[4] * fx - o[3] * fy;
        float inv = 1.0f / (InlineSqrt(o[0] * o[0] + o[1] * o[1] + o[2] * o[2]) + 0.1f);
        o[0] *= inv; o[1] *= inv; o[2] *= inv;
        break;
    }
    default: {
        float* pf = *(float**)((char*)param_1 + 0x30);
        o[0] = pf[0x5c / 4]; o[1] = pf[0x60 / 4]; o[2] = pf[100 / 4];
        pf = *(float**)((char*)param_1 + 0x30);
        o[3] = pf[0x74 / 4]; o[4] = pf[0x78 / 4]; o[5] = pf[0x7c / 4];
        break;
    }
    }

    if (c[0x180] != 0 || c[0x182] != 0) {
        o[6] = (float)(uint8_t)c[0x181] * 0.003921569f;
        o[7] = (float)(uint8_t)c[0x180] * 0.0627451f;
        o[8] = (float)(uint8_t)c[0x183] * 0.003921569f;
        o[9] = (float)(uint8_t)c[0x182] * 0.0627451f;
    }

    uint8_t flag = ((uint8_t)c[0x132] < 2 && (uint8_t)c[0x133] < 2) ? 0 : 1;
    ((uint8_t*)o)[0x28] = flag;
    o[0x0b] = 1.0f / (float)(uint8_t)c[0x132];
    o[0x0c] = 1.0f / (float)(uint8_t)c[0x133];
    out->wMinus1 = (uint8_t)c[0x132] - 1;
    out->hMinus1 = (uint8_t)c[0x133] - 1;
    out->log2W = 0;

    uint32_t n = (uint8_t)c[0x132];
    if (n > 1) {
        int log2 = 0;
        do {
            n >>= 1;
            log2++;
        } while (n > 1);
        out->log2W = log2;
    }
}

// @ 0x00f77940
void Stream_Quad_V4F_N4F_C4B_T2F_Old(EA::Swarm::cParticlesEffect* effect, EA::Swarm::cITextureParticleRenderer_s00f7_7940* renderer, u8* offsets)
{
    EA::Swarm::cParticlesDescription_s00f7_7940* desc = effect->mDesc;
    StreamerInfo info;
    StreamerSetup(effect, desc, &info);

    EA::Swarm::cParticle_s00f7_7940* particle = effect->mParticlesFirst;
    CurveLimits lim;
    InitCurveLimits(desc, lim);

    int remaining = effect->mParticleCount;
    while (remaining > 0) {
        u8* buffer;
        int stride;
        int count = renderer->GetBuffer(remaining, &buffer, &stride);
        remaining -= count;

        for (; count > 0; count--) {
            QuadParticle q;
            ComputeQuadParticle(effect, desc, info, lim, particle, q);

            // T2F: unit square (0,0) (1,0) (1,1) (0,1).
            static const float kU[4] = { 0.0f, 1.0f, 1.0f, 0.0f };
            static const float kV[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

            u8* pPos   = buffer + offsets[0];
            u8* pAxis  = buffer + offsets[1];
            u8* pColor = buffer + offsets[2];
            u8* pTex   = buffer + offsets[3];
            for (int i = 0; i < 4; i++) {
                V4F& v = *(V4F*)pPos;
                v.x = q.pos.x;
                v.y = q.pos.y;
                v.z = q.pos.z;
                v.w = q.t;
                pPos += stride;

                V4F& n = *(V4F*)pAxis;
                n.x = q.axis.x * q.size;
                n.y = q.axis.y * q.size;
                n.z = q.axis.z * q.size;
                n.w = q.size;
                pAxis += stride;

                *(u32*)pColor = q.color;
                pColor += stride;

                ((float*)pTex)[0] = kU[i];
                ((float*)pTex)[1] = kV[i];
                pTex += stride;
            }

            buffer += stride * 4;
            particle = particle->mpNext;
        }
        renderer->ReleaseAndDrawBuffer();
    }
}

// @ 0x00f79bb0
void FUN_00f79bb0(char init)
{
    if (init != 0) {
        memset(&gStreamGlobals, 0, sizeof(gStreamGlobals));
        gStreamGlobals.mVtable0 = 0x00f765a0;
        gStreamGlobals.mFn8 = 0x00f77940;
        gStreamGlobals.mFnC = 0x00f78a60;
    }
}

// @ 0x00f79bf0
namespace EA { namespace Swarm {
bool cParticlesEffectOld_s00f7_9bb0::InitParticle(cParticle_s00f7_9bb0* particle)
{
    particle->mBase.mAge = 0.0f;
    particle->mBase.mLife = (float)RandomRange(mDesc->mLife);

    particle->mFrame = mFrameStart;
    if (mDesc->mFrameRandom > 0)
    {
        if (mDesc->mFrameStride > 0)
            particle->mFrame += (uint8_t)(sRandom.RandomUint32Uniform(mDesc->mFrameRandom) * mDesc->mFrameStride);
        else
            particle->mFrame += (uint8_t)sRandom.RandomUint32Uniform(mDesc->mFrameRandom);
    }

    const bool onPath = TestBit((uint32_t)mDesc->mFlags, 31) && PlaceOnPath(particle);
    bool placed = true;
    float speed;
    if (!onPath)
    {
        if (mDesc->mTorusWidth >= 0.0f)
            particle->mBase.mPosition = RandomPointInTorus(mEmissionVolume, mDesc->mTorusWidth);
        else if (TestBit((uint32_t)mDesc->mFlags, 4))
            particle->mBase.mPosition = RandomPointInEllipsoid(mEmissionVolume);
        else
            particle->mBase.mPosition = RandomPointInBox(mEmissionVolume);

        if ((mDesc->mFlags & kSurfaceEmitFlags) != 0)
            placed = PlaceParticleOnSurface(particle);

        particle->mBase.mVelocity = RandomPointInBox(mDesc->mEmitDirection);
        speed = RandomInRange(Vector2_s00f7_9bb0(mDesc->mEmitSpeed)) * mEmitVelocityScale;
        {
            float lengthSq = particle->mBase.mVelocity.SquaredLength();
            if (lengthSq > 0.0f)
                particle->mBase.mVelocity *= speed / sqrtf(lengthSq);
        }
        {
            float radial = mDesc->mRadialForce;
            if (radial != 0.0f)
            {
                Vector3_s00f7_9bb0 d = particle->mBase.mPosition - mDesc->mRadialForceLocation;
                float lengthSq = d.SquaredLength();
                if (lengthSq > 0.0f)
                    particle->mBase.mVelocity += d * (radial / sqrtf(lengthSq));
            }
        }
    }

    particle->mSize = (float)(RandomVary(mDesc->mSizeVary) * mCurrentSizeScale);
    particle->mAspectRatio = (float)RandomVary(mDesc->mAspectRatioVary);
    particle->mAlpha = placed ? 1.0f : 0.0f;
    particle->mColor.x = (float)RandomVary(mDesc->mColorVary[0]);
    particle->mColor.y = (float)RandomVary(mDesc->mColorVary[1]);
    particle->mColor.z = (float)RandomVary(mDesc->mColorVary[2]);

    if (mEmitColorMap)
    {
        Vector3_s00f7_9bb0 p = particle->mBase.mPosition;
        if (mEmitColorMapInWorldSpace)
        {
            mSourceTransform.Transform(p);
            mRigidTransform.Transform(p);
        }
        if (mEmitColorMap->PointInMap(p))
        {
            ColorRGBA c = mEmitColorMap->ColorAlpha(p);
            particle->mAlpha = particle->mAlpha * c.a;
            particle->mColor = Vector3_s00f7_9bb0(particle->mColor.x * c.r, particle->mColor.y * c.g,
                                       particle->mColor.z * c.b);
        }
    }

    {
        float rotationVary = mDesc->mRotationVary;
        if (rotationVary > 0.0f)
            particle->mRotation = RandomSymmetric(rotationVary);
        else
            particle->mRotation = 1.0f;
    }

    Vector3_s00f7_9bb0& pos = particle->mBase.mPosition;
    if (mSourceTransform.mFlags & 2)
        pos = mSourceTransform.Rotate(pos);
    {
        float s = mSourceTransform.mScale;
        pos.x = s * pos.x;
        pos.y = s * pos.y;
        pos.z = s * pos.z;
    }
    pos.x = mSourceTransform.mTranslation.x + pos.x;
    pos.y = mSourceTransform.mTranslation.y + pos.y;
    pos.z = mSourceTransform.mTranslation.z + pos.z;
    if (mSourceTransform.mFlags & 2)
        particle->mBase.mVelocity = mSourceTransform.Rotate(particle->mBase.mVelocity);

    if (!onPath && TestBit((uint32_t)mDesc->mFlags, 3))
    {
        const cGlobalParams_s00f7_9bb0* gp = mGlobalParams;
        const Vector3_s00f7_9bb0& v = particle->mBase.mVelocity;
        float up = v.x * gp->mCameraUp.x + v.z * gp->mCameraUp.z + v.y * gp->mCameraUp.y;
        float right = v.x * gp->mCameraRight.x + v.z * gp->mCameraRight.z + v.y * gp->mCameraRight.y;
        float invSpeed = 1.0f / speed;
        float screen = sqrtf(right * right + up * up) / mDesc->mStretchScale;
        float size0 = *mDesc->mSizeCurve;
        pos += v * 0.5f * screen * size0 * invSpeed;
    }

    if (mHaveSurfacePin)
    {
        uint8_t* stateData = mSurfaceStateData;
        for (cSurfaceRec_s00f7_9bb0* rec = mSurfaceRecsBegin; rec != mSurfaceRecsEnd; ++rec)
        {
            if ((rec->mpInfo->mFlags & kSurfacePinFlags_s00f7_9bb0) == 0)
                continue;
            void* state = rec->mHasStateData ? stateData + rec->mStateDataOffset : 0;
            Vector3_s00f7_9bb0 normal;
            if (rec->mpSurface->FindClosestSurfacePoint(pos, pos, &normal, 0, state, 0))
            {
                float offset = rec->mpInfo->mPinOffset;
                if (offset != 0.0f)
                {
                    pos.x = pos.x + normal.x * offset;
                    pos.y = normal.y * offset + pos.y;
                    pos.z = normal.z * offset + pos.z;
                }
                particle->mSurfaceNormal = normal;
                return true;
            }
        }
    }
    return true;
}
}}  // namespace EA::Swarm

// @ 0x00f7a5d0
namespace EA { namespace Swarm {
void SwarmSystem::InitParticle2(cParticle_s00f7_9bb0* particle)
{
    SwarmEmitterE* effect = mEffect218;
    cParticlesDescription_s00f7_9bb0* desc = effect->mDesc24;

    particle->mBase.mAge = 0.0f;
    particle->mBase.mLife = (float)RandomRangeM(desc->mLife.x, desc->mLife.y);

    EffectSub* sub = &effect->mSub8;
    if (!sub->Test())
        sub->Set(0);

    if (TestBit((uint32_t)desc->mFlags, 26))
        ((cParticlesEffectOld_s00f7_9bb0*)effect)->InitParticle(particle);

    ParticleList* list = &effect->mList18;
    particle->mpPrev = list->mPrev;
    particle->mpNext = (void*)&list->mNext;
    list->mPrev = particle;
    ((cParticle_s00f7_9bb0*)particle->mpPrev)->mpNext = particle;
    list->mCount++;
}
}}  // namespace EA::Swarm

// @ 0x00f7a6a0
namespace EA { namespace Swarm {
void SwarmSystem::Spawn(cParticle_s00f7_9bb0* particle)
{
    float age = particle->mBase.mAge;
    float life = particle->mBase.mLife;
    if (mEffect218 == 0 ||
        ((!(life <= age)) &&
         !TestBit((uint32_t)mDesc24->mFlags, 27))) {
        particle->mpNext = gFreeParticleList;
        gFreeParticleList = particle;
        return;
    }

    InitParticle2(particle);

    if (mEffect218 != 0 && mField20 == 0 && mField15 != 0) {
        EffectSub* sub = (EffectSub*)((char*)mEffect218 + 8);
        sub->Dispatch(0);
    }
}
}}  // namespace EA::Swarm

// @ 0x00f7a710
void cSwarmWriterA::Write(IVertexStream* pStream)
{
    EmitterInfo* info = mpInfo;
    Particle* p = mpHead;
    uint32_t nColor = (uint32_t)(info->mColorCurve.mpEnd - info->mColorCurve.mpBegin) - 1;
    uint32_t offColor = mAlphaOffset;
    uint32_t nScale = (uint32_t)(info->mScaleCurve.mpEnd - info->mScaleCurve.mpBegin) - 1;
    uint32_t offMatrix = mColorOffset;
    int remaining = mRemaining;
    uint32_t nAlpha = (uint32_t)(info->mAlphaCurve.mpEnd - info->mAlphaCurve.mpBegin) - 1;
    char* buf;
    int stride;
    while (remaining > 0) {
        int n = pStream->Acquire(remaining, &buf, &stride);
        remaining -= n;
        if (n > 0) {
            do {
                float t = p->mAge / p->mLifetime;
                cTransform_s00f7_a710 xf;
                xf.mTranslation = Vector3_s00f7_a710(p->mPos);
                Vector3_s00f7_a710 c = EvalColorCurve(mpInfo->mColorCurve, nColor, t);
                Vector3_s00f7_a710 col;
                col.x = mColorMul[0] * (p->mColorMul[0] * c.x);
                col.y = (p->mColorMul[1] * c.y) * mColorMul[1];
                col.z = (p->mColorMul[2] * c.z) * mColorMul[2];
                float alpha = (p->mAlpha * mAlphaMul) * EvalCurve(mpInfo->mAlphaCurve, nAlpha, t);
                float scale = EvalCurve(mpInfo->mScaleCurve, nScale, t);
                xf.mRotation.row[0] = Vector3_s00f7_a710(g_Identity3.row[0]);
                xf.mRotation.row[1] = Vector3_s00f7_a710(g_Identity3.row[1]);
                xf.mRotation.row[2] = Vector3_s00f7_a710(g_Identity3.row[2]);
                xf.mModificationCount = 2;
                xf.mFlags = 4;
                scale = (p->mSize * mSizeMul) * scale;
                xf.mScale = scale;
                uint8_t mode = mpInfo->mOrientMode;
                if (mode >= 2 && mode <= 4) {
                    Vector3_s00f7_a710 dir(p->mDir);
                    Matrix3 m;
                    m.row[0] = Vector3_s00f7_a710(g_Identity3.row[0]);
                    m.row[1] = Vector3_s00f7_a710(g_Identity3.row[1]);
                    m.row[2] = Vector3_s00f7_a710(g_Identity3.row[2]);
                    float len = (float)sqrt((dir.z * dir.z + dir.y * dir.y) + dir.x * dir.x);
                    if (0.0f < len) {
                        float inv = 1.0f / len;
                        dir.x = inv * dir.x;
                        dir.y = dir.y * inv;
                        dir.z = dir.z * inv;
                    }
                    switch (mpInfo->mOrientMode) {
                    case 2: BuildBasisMode2(&dir, &m); break;
                    case 3: BuildBasisMode3(&dir, &m); break;
                    case 4: BuildBasisMode4(&dir, &m); break;
                    }
                    *(RawMatrix3*)&xf.mRotation = *(RawMatrix3*)&m;
                    xf.mFlags = 6;
                    xf.mModificationCount = 3;
                }
                float rot = EvalCurve(mpInfo->mSpinCurve,
                                      (uint32_t)(mpInfo->mSpinCurve.mpEnd - mpInfo->mSpinCurve.mpBegin) - 1, t);
                xf.RotateZ((p->mSpin * rot + mpInfo->mSpinBase) * g_RadiansScale);
                xf.PostTransformBy(mWorld);
                float s = xf.mScale;
                OutRow* d = (OutRow*)(buf + offMatrix);
                d[0].v = xf.mRotation.row[0] * s;
                d[1].v = xf.mRotation.row[1] * s;
                d[2].v = xf.mRotation.row[2] * s;
                d[3].v = xf.mTranslation;
                OutRow* e = (OutRow*)(buf + offColor);
                e->v = col;
                e->w = alpha;
                buf += stride;
                p = p->mpNext;
            } while (--n != 0);
        }
        pStream->Commit();
    }
    ++mFrame;
}

// @ 0x00f7afd0
cParticlesEffect_s00f7_a710* cParticlesEffect_s00f7_a710::Init(void* pDesc, uint32_t collectionIndex)
{
    float zero = 0.0f;
    float one;
    void* anchor;

    mpVtbl1 = (void*)0x140b5a0;
    mpVtbl3 = (void*)0x13ef094;
    mF10 = 0;
    mpVtbl2 = (void*)0x13f21d4;
    mpVtbl3 = (void*)0x13f2194;
    mpVtbl0 = (void*)0x148ff18;
    mpVtbl1 = (void*)0x148ff14;
    mpVtbl2 = (void*)0x148fed8;
    mpVtbl3 = (void*)0x148fed4;
    mStarted = false;
    mDelayedStopActive = false;
    mIsVisible = true;
    mF17 = false;
    anchor = (void*)&mpParticlesHead;
    mpParticlesAnchor = anchor;
    mpParticlesHead = anchor;
    mOverallTime = 0.0;
    mParticleSystemTime = 0.0;
    mpDesc = pDesc;
    mCollectionIndex = collectionIndex;
    mInverseRateCurveTime = g1454410;
    mParticlesToGenerate = zero;
    mParticleCount = 0;
    mpWorld = 0;
    mpGlobalParams = 0;
    mPreroll = false;
    mCurrentCycle = 0;

    mDirectionalForcesSum[0] = g16c9b28.f;
    mDirectionalForcesSum[1] = g16c9b2c.f;
    mDirectionalForcesSum[2] = g16c9b30.f;
    mRandomWalkNextTime = zero;
    mRandomWalkStrengthV = g16c9b28.f;
    mRandomWalkStrengthH = g16c9b2c.f;
    mRandomWalkTheta = g16c9b30.f;
    mF80 = zero;
    mF84 = zero;
    mAttractorForce = zero;
    mAttractorLocation[0] = zero;
    mAttractorLocation[1] = zero;
    mAttractorLocation[2] = zero;
    mAttractorIntensity = zero;
    mRetriggerTime = zero;
    mF0a0 = zero;
    mF0a4 = g16c9b28.f;
    mF0a8 = g16c9b2c.f;
    mF0ac = g16c9b30.f;
    mF0b0 = 0;
    mF0b2 = 0;
    mF0b4 = g16c9b28.f;
    mF0b8 = g16c9b2c.f;
    mF0bc = g16c9b30.f;
    one = g1485720.f;
    mF0c0 = one;

    ((Matrix33Ctor*)&mMatrix0)->Assign((const void*)0x16c9b34);

    mF0e8 = 0;
    mF0ea = 0;
    mF0ec = g16c9b28.f;
    mF0f0 = g16c9b2c.f;
    mF0f4 = g16c9b30.f;
    one = g1485720.f;
    mF0f8 = one;

    ((Matrix33Ctor*)&mMatrix1)->Assign((const void*)0x16c9b34);

    mF120 = g16c9b28.f;
    mF124 = g16c9b2c.f;
    mF128 = g16c9b30.f;
    mF12c = 0;
    mF12e = 0;
    mF130 = g16c9b78.f;
    mF134 = g16c9b7c.f;
    mF138 = g16c9b78.f;
    mF13c = g16c9b7c.f;
    mF140 = g16c9b78.f;
    mF144 = g16c9b7c.f;
    one = g1485720.f;
    mF148 = one;
    mF14c = one;
    mF150 = one;
    mF154 = one;
    mF158 = one;
    mF15c = g16c9b80.f;
    mF160 = g16c9b84.f;
    mF164 = g16c9b88.f;
    mF168 = 0;
    mF16c = g1418f90.f;
    mF170 = g13f0620.f;
    mF174 = one;
    mF178 = one;
    mF17c = one;
    mF180 = one;
    mF184 = one;
    mF188 = g16c9b80.f;
    mF18c = g16c9b84.f;
    mF190 = g16c9b88.f;
    mpF194 = 0;
    mpF198 = 0;
    mpF19c = 0;
    mF1a0 = false;
    mF1a1 = false;
    mF1a2 = false;
    mF1a4 = 0;
    mF1a8 = 0;
    mF1ac = 0.0f;
    mF1b0 = 0.0f;
    mF1b4 = 0.0f;
    mF1b8 = 0.0f;
    mF1bc = 0.0f;
    mF1c0 = 0.0f;
    mF1c8 = -1;
    mF1cc = -1;
    mF1d0 = 0;
    mRefVertices.mpBegin = 0;
    mRefVertices.mpEnd = 0;
    mRefVertices.mpCapacity = 0;
    mF1e8 = false;
    mpF1ec = 0;
    mpF1f0 = 0;
    mpF1f4 = 0;
    mF200 = false;
    mpF204 = 0;
    mpF208 = 0;
    mpF20c = 0;
    mpF218 = 0;
    mF220 = -1;
    mF224 = -1;
    mF21c = false;
    mF22e = false;
    return this;
}

// @ 0x00f7b460
void cParticlesEffect_s00f7_a710::Destroy()
{
    mpVtbl0 = (void*)0x148ff18;
    mpVtbl1 = (void*)0x148ff14;
    mpVtbl2 = (void*)0x148fed8;
    mpVtbl3 = (void*)0x148fed4;
    _ReadWriteBarrier();
    if (mpF218) {
        void* obj = (void*)&mpF218->mpVtable;
        void** vt = *(void***)obj;
        ((void (__thiscall*)(void*))vt[0x38 / 4])(obj);
    }
    if (mpF204 && ((HeapBlock*)mpF204)[-1].mRefCount != 0)
        operator delete(mpF204);
    if (mpF1ec && ((HeapBlock*)mpF1ec)[-1].mRefCount != 0)
        operator delete(mpF1ec);
    mRefVertices.Destroy();
    if (mpF19c) {
        void** vt = *(void***)mpF19c;
        ((void (__thiscall*)(void*))vt[1])(mpF19c);
    }
    if (mpF198) {
        void** vt = *(void***)mpF198;
        ((void (__thiscall*)(void*))vt[1])(mpF198);
    }
    if (mpF194) {
        void** vt = *(void***)mpF194;
        ((void (__thiscall*)(void*))vt[1])(mpF194);
    }
    ((IntrusiveListBase*)&mpParticlesHead)->Destroy();
    mpVtbl2 = (void*)0x13f21d4;
    mpVtbl3 = (void*)0x13ef094;
}

// @ 0x00f7b520
int Swarm_s00f7_b520::FUN_00f7b520(int param_2, float* param_3, int param_4)
{
    char* s = (char*)this;
    float f2, f3, f4, f5, f6, f16;
    int   i9, i15;
    char* p14;
    char* p7; char* p8;
    void* u13;
    char  c11;

    if (param_2 < 0x102) {
        if (param_2 == 0x101) {
            *(float*)(s + 0x128) = param_3[0];
            *(float*)(s + 0x130) = param_3[1];
            *(float*)(s + 0x138) = param_3[2];
            *(float*)(s + 300)   = param_3[3];
            *(float*)(s + 0x134) = param_3[4];
            *(float*)(s + 0x13c) = param_3[5];
            return 1;
        }
        switch (param_2) {
        case 0:
            *(float*)(s + 0x140) = param_3[0];
            return 1;
        case 1:
            *(float*)(s + 0x148) = param_3[0];
            return 1;
        case 3:
            *(float*)(s + 0x144) = param_3[0];
            return 1;
        case 4:
            *(float*)(s + 0x14c) = param_3[0];
            return 1;
        case 5:
            f2 = param_3[1];
            f3 = param_3[2];
            *(float*)(s + 0x154) = param_3[0];
            *(float*)(s + 0x158) = f2;
            *(float*)(s + 0x15c) = f3;
            return 1;
        case 6:
            i15 = param_4 / 3;
            i9 = *(int*)(s + 0x18);
            while (i9 < i15) {
                char* node = (char*)FUN_00f75fc0();
                if (FUN_00f79bf0(node) != 0) {
                    *(char**)(node + 4) = *(char**)(s + 0x14);
                    *(char**)node       = s + 0x10;
                    *(char**)(s + 0x14) = node;
                    *(char**)*(char**)(node + 4) = node;
                    *(int*)(s + 0x18) = *(int*)(s + 0x18) + 1;
                }
                i9 = *(int*)(s + 0x18);
            }
            i9 = *(int*)(s + 0x18);
            p14 = *(char**)(s + 0x10);
            while (i15 < i9) {
                p7 = *(char**)(p14 + 4);
                p8 = *(char**)p14;
                *(char**)p7 = p8;
                *(char**)(p8 + 4) = p7;
                *(char**)p14 = 0;
                *(char**)(p14 + 4) = 0;
                *(int*)(s + 0x18) = *(int*)(s + 0x18) - 1;
                FUN_00f7a6a0(p14);
                p14 = p8;
                i9 = *(int*)(s + 0x18);
            }
            p14 = *(char**)(s + 0x10);
            if (0 < i15) {
                do {
                    *(float*)(p14 + 0x38) = param_3[0];
                    *(float*)(p14 + 0x3c) = param_3[1];
                    f16 = param_3[2];
                    param_3 += 3;
                    --i15;
                    *(float*)(p14 + 0x40) = f16;
                    p14 = *(char**)p14;
                } while (i15 != 0);
            }
            return 1;
        case 9:
            *(float*)(s + 0x6c) = param_3[0];
            *(float*)(s + 0x70) = param_3[1];
            *(float*)(s + 0x74) = param_3[2];
            return 1;
        case 10:
            *(float*)(s + 0x78) = param_3[0];
            return 1;
        case 0xb:
            f2 = param_3[5];
            f3 = param_3[3];
            f4 = param_3[4];
            f16 = (((*(float*)(s + 0xa4) - param_3[2]) * f2 +
                    (*(float*)(s + 0xa0) - param_3[1]) * f4) +
                   (*(float*)(s + 0x9c) - param_3[0]) * f3) /
                  ((f4 * f4 + f3 * f3) + f2 * f2);
            f2 = param_3[5];
            f5 = param_3[1];
            f6 = param_3[2];
            *(float*)(s + 0x6c) = param_3[0] + f3 * f16;
            *(float*)(s + 0x70) = f4 * f16 + f5;
            *(float*)(s + 0x74) = f2 * f16 + f6;
            *(float*)(s + 0x78) = (float)(0.0f <= f16);
            FUN_007cda70((float*)(s + 0x6c));
            return 1;
        case 0xd:
            i9 = *(int*)(s + 0x1c);
            i15 = param_4 / 3;
            if (*(int*)(i9 + 8) < 0) {
                char auStack_38[56];
                u13 = FUN_007d5590(auStack_38, s + 0xa8, s + 0xe0, s + 0x1fc);
                FUN_00a7ab40(i15, param_3, *(int*)(i9 + 0x44), u13);
                return 1;
            }
            i9 = *(int*)(s + 0x18);
            while (i9 < i15) {
                char* node = (char*)FUN_00f75fc0();
                if (FUN_00f79bf0(node) != 0)
                    FUN_00f58620(node);
                i9 = *(int*)(s + 0x18);
            }
            i9  = *(int*)(s + 0x18);
            u13 = *(void**)(s + 0x10);
            while (i15 < i9) {
                void* nx = *(void**)FUN_00aa8ea0(&param_2, u13);
                *(int*)(s + 0x18) = *(int*)(s + 0x18) - 1;
                FUN_00f7a6a0((char*)u13);
                u13 = nx;
                i9 = *(int*)(s + 0x18);
            }
            p14 = *(char**)(s + 0x10);
            if (0 < i15) {
                do {
                    *(float*)(p14 + 0x10) = param_3[0];
                    *(float*)(p14 + 0x14) = param_3[1];
                    f16 = param_3[2];
                    param_3 += 3;
                    --i15;
                    *(float*)(p14 + 0x18) = f16;
                    p14 = *(char**)p14;
                } while (i15 != 0);
            }
            return 1;
        case 0xe:
            if (-1 < *(int*)(s + 0x21c)) {
                void* obj = *(void**)(s + 0x24);
                int* v = (int*)((PFN_Get)*(void**)(*(int*)obj + 0x20))(obj);
                return ((PFN_Slot)*(void**)(*v + 0x74))(v, 0, *(int*)(s + 0x21c), 0, param_4, (int)param_3);
            }
            if (-1 < *(int*)(s + 0x218)) {
                void* obj = *(void**)(s + 0x24);
                int* v = (int*)((PFN_Get)*(void**)(*(int*)obj + 0x20))(obj);
                return ((PFN_Slot)*(void**)(*v + 0x74))(v, 1, *(int*)(s + 0x218), 0, param_4, (int)param_3);
            }
            break;
        case 0x10:
            if (param_4 == 2 ||
                (int)(param_3[2] < 0.0f ? param_3[2] - 0.5f : param_3[2] + 0.5f) ==
                    (int)*(uchar*)(*(int*)(s + 0x1c) + 0x131)) {
                *(float*)(s + 0x164) = param_3[0];
                *(float*)(s + 0x168) = param_3[1];
                return 1;
            }
            break;
        case 0x12:
            *(float*)(s + 0x150) = param_3[0];
            return 1;
        }
    }
    return 0;
}

// @ 0x00f7ba80
void Swarm_s00f7_b520::FUN_00f7ba80(float param_2)
{
    char* s = (char*)this;
    float f9, f2, f3, f4, f10, f11, f12;
    int   i5, i8;
    char* p6;
    char  c7;

    f9 = param_2 * (float)*(double*)(s + 0x58) + (float)*(double*)(s + 0x48);
    *(double*)(s + 0x48) = (double)f9;

    if ((float)*(int*)(s + 0x50) <= f9) {
        f9 = **(float**)(*(int*)(s + 0x24) + 0x68) * *(float*)(s + 0x174);
        i8 = (int)(f9 < 0.0f ? f9 - 0.5f : f9 + 0.5f);
        if ((float)i8 < f9)
            i8 = i8 + 1;

        for (i8 = i8 - *(int*)(s + 0x20); 0 < i8; i8 = i8 - 1) {
            for (;;) {
                p6 = (char*)g_16c9b68;
                if (g_16c9b68 != 0) {
                    g_16c9b68 = *(int**)g_16c9b68;
                    *(void**)(p6 + 4) = 0;
                    *(void**)p6 = 0;
                    break;
                }
                c7 = EA_AddCore(&g_16c9b58, 0, 0);
                if (c7 != 0)
                    break;
            }
            c7 = FUN_00f79bf0(p6);
            if (c7 == 0) {
            LAB_ret:
                if (*(int*)(s + 0x218) == 0 ||
                    (*(float*)(p6 + 8) < *(float*)(p6 + 0xc) &&
                     ((*(u32*)(*(int*)(s + 0x24) + 8) >> 0x1b & 1) == 0))) {
                    *(int**)p6 = g_16c9b68;
                    g_16c9b68 = (int*)p6;
                } else {
                    FUN_00f7a5d0(p6);
                    if (*(int*)(s + 0x218) != 0 && *(int*)(s + 0x20) == 0 &&
                        *(char*)(s + 0x15) != 0)
                        ((void(__thiscall*)(void*, int))*(void**)(*(int*)(*(int*)(s + 0x218) + 8) + 0xc))
                            (*(void**)(s + 0x218), 0);
                }
            } else {
                i5 = *(int*)(s + 0x24);
                int fncell = g_15b0ebc[(u32)*(uchar*)(i5 + 0x130)];
                if (fncell == 0) {
                    f9 = *(float*)(p6 + 8);
                    *(float*)(p6 + 8) = f9 + param_2;
                    if (f9 + param_2 < *(float*)(p6 + 0xc)) {
                        f9  = *(float*)(s + 100);
                        f2  = *(float*)(p6 + 0x24);
                        f10 = *(float*)(s + 0x68);
                        f3  = *(float*)(p6 + 0x1c);
                        f4  = *(float*)(p6 + 0x20);
                        f11 = *(float*)(s + 0x6c) * param_2 + *(float*)(p6 + 0x24);
                        *(float*)(p6 + 0x24) = f11;
                        f9  = f3 + f9 * param_2;
                        *(float*)(p6 + 0x1c) = f9;
                        f10 = f4 + f10 * param_2;
                        *(float*)(p6 + 0x20) = f10;
                        f12 = 1.0f - *(float*)(i5 + 0x160) * param_2;
                        f9  = f9 * f12;
                        *(float*)(p6 + 0x1c) = f9;
                        f11 = f11 * f12;
                        f10 = f10 * f12;
                        *(float*)(p6 + 0x20) = f10;
                        *(float*)(p6 + 0x24) = f11;
                        f12 = param_2 * 0.5f;
                        *(float*)(p6 + 0x14) = *(float*)(p6 + 0x14) + (f10 + f4) * f12;
                        *(float*)(p6 + 0x10) = *(float*)(p6 + 0x10) + (f9 + f3) * f12;
                        *(float*)(p6 + 0x18) = *(float*)(p6 + 0x18) + (f11 + f2) * f12;
                        c7 = 1;
                    } else {
                        c7 = 0;
                    }
                } else {
                    c7 = ((char(__thiscall*)(void*, float, int, char*))fncell)(p6, param_2, i5, s);
                }
                if (c7 == 0)
                    goto LAB_ret;

                *(char**)(p6 + 4) = *(char**)(s + 0x1c);
                *(char**)p6       = s + 0x18;
                *(char**)(s + 0x1c) = p6;
                *(char**)*(char**)(p6 + 4) = p6;
                *(int*)(s + 0x20) = *(int*)(s + 0x20) + 1;

                if (*(float*)(p6 + 0x10) < *(float*)(s + 0x88))
                    *(float*)(s + 0x88) = *(float*)(p6 + 0x10);
                f9 = *(float*)(p6 + 0x10);
                if (*(float*)(s + 0x94) <= f9 && f9 != *(float*)(s + 0x94))
                    *(float*)(s + 0x94) = f9;
                if (*(float*)(p6 + 0x14) < *(float*)(s + 0x8c))
                    *(float*)(s + 0x8c) = *(float*)(p6 + 0x14);
                f9 = *(float*)(p6 + 0x14);
                if (*(float*)(s + 0x98) <= f9 && f9 != *(float*)(s + 0x98))
                    *(float*)(s + 0x98) = f9;
                if (*(float*)(p6 + 0x18) < *(float*)(s + 0x90))
                    *(float*)(s + 0x90) = *(float*)(p6 + 0x18);
                f9 = *(float*)(p6 + 0x18);
                if (*(float*)(s + 0x9c) <= f9 && f9 != *(float*)(s + 0x9c))
                    *(float*)(s + 0x9c) = f9;
            }
        }
    }
}

// @ 0x00f7bd70
void Swarm_s00f7_b520::FUN_00f7bd70()
{
    char* s    = (char*)this;
    char* head = s + 0x18;
    char* n    = *(char**)(s + 0x18);

    while (n != head) {
        char* nx = *(char**)n;
        char* pv = *(char**)(n + 4);
        *(char**)pv       = nx;
        *(char**)(nx + 4) = pv;
        *(char**)n        = 0;
        *(char**)(n + 4)  = 0;
        *(int*)(s + 0x20) = *(int*)(s + 0x20) - 1;

        if (*(int*)(s + 0x218) == 0 ||
            (*(float*)(n + 8) < *(float*)(n + 0xc) &&
             ((*(u32*)(*(int*)(s + 0x24) + 8) >> 0x1b & 1) == 0))) {
            *(int**)n = g_16c9b68;
            g_16c9b68 = (int*)n;
        } else {
            FUN_00f7a5d0(n);
            if (*(int*)(s + 0x218) != 0 && *(int*)(s + 0x20) == 0 &&
                *(char*)(s + 0x15) != 0)
                ((void(__thiscall*)(void*, int))*(void**)(*(int*)(*(int*)(s + 0x218) + 8) + 0xc))
                    (*(void**)(s + 0x218), 0);
        }
        n = nx;
    }

    char* m = *(char**)(s + 0x18);
    while (m != head) {
        char* mx = *(char**)m;
        *(char**)(m + 4) = 0;
        *(char**)m       = 0;
        m = mx;
    }
    *(char**)head       = head;
    *(char**)(head + 4) = head;
}

// @ 0x00f7be20
int FUN_00f7be20(int param_1, int param_2)
{
    char* p = (char*)FUN_00f473a0(0x230, "Swarm", 0, 0, 0, 0);
    if (p != 0) {
        char* r = (char*)((AllocObj*)p)->FUN_00f7afd0((void*)param_1, (void*)param_2);
        if (r != 0)
            return (int)(r + 8);
    }
    return 0;
}

// @ 0x00f7bef0
void Swarm_s00f7_b520::FUN_00f7bef0(int param_2)
{
    char* s = (char*)this;
    if (*(char*)(s + 0xc) != 0) {
        if (*(int*)(s + 0x210) != 0 && *(int*)(s + 0x18) == 0) {
            void* obj = (char*)*(void**)(s + 0x210) + 8;
            ((void(__thiscall*)(void*, int))*(void**)(*(int*)obj + 0xc))(obj, param_2);
        }
        *(char*)(s + 0xd) = (param_2 == 0);

        if (*(char*)(s + 0xd) == 0) {
            *(char*)(s + 0xc) = *(char*)(s + 0xd);
            ((Swarm_s00f7_b520*)((char*)this - 8))->FUN_00f7bd70();   // lea ecx,[esi-8]: list owner is 8 bytes below

            if (*(int*)(s + 0x21c) >= 0) {
                void* obj = *(void**)(s + 0x24);
                int* v = (int*)((PFN_Get)*(void**)(*(int*)obj + 0x20))(obj);
                ((void(__thiscall*)(void*, int, int))*(void**)(*v + 0x24))(v, *(int*)(s + 0x21c), 0);
                return;
            }
            if (*(int*)(s + 0x218) >= 0) {
                void* obj = *(void**)(s + 0x24);
                int* v = (int*)((PFN_Get)*(void**)(*(int*)obj + 0x20))(obj);
                ((void(__thiscall*)(void*, int, int))*(void**)(*v + 0x38))(v, *(int*)(s + 0x218), 0);
            }
        }
    }
}

// @ 0x00f7caf0
namespace EA { namespace Swarm {
void cParticlesEffect_s00f7_caf0::ApplyEffect(float deltaTime, float lodFactor, cStats* stats)
{
    if (mPreroll) {
        if (mDesc->mFlags.test(kParticleFlagSingleCycle)) {
            mParticleSystemTime = 1.0;
            mPreroll = false;
        } else {
            deltaTime += mDesc->mPrerollTime;
            mPreroll = false;
        }
    } else if (mRenderCount > mLastRenderCount) {
        int n = (mRenderCount - mLastRenderCount) * mParticleCount;
        if (mDesc->mFlags.test(kParticleFlagModelStats))
            stats->mModelParticlesRendered += n;
        else
            stats->mTextureParticlesRendered += n;
        mLastRenderCount = mRenderCount;
    }

    if (deltaTime < 0.0f)
        return;

    if (mParamA) {
        uint32_t v = mParamA->GetValue();
        if (mCachedParamA != v) {
            mCachedParamA = v;
            mParamsChanged = true;
        }
    }
    if (mParamB) {
        uint32_t v = mParamB->GetValue();
        if (mCachedParamB != v) {
            mCachedParamB = v;
            mParamsChanged = true;
        }
    }

    if (mDesc->mFlags.test(kParticleFlagSingleCycle) && !mDelayedStopActive) {
        float timeLeft = (float)(1.0 - mParticleSystemTime) * mDesc->mRateCurveTime - 0.01f;
        if (timeLeft <= 0.0f)
            deltaTime = 0.0f;
        else if (deltaTime > timeLeft)
            deltaTime = timeLeft;
    }

    Vector3_s00f7_caf0 location = mSourceTransform.mTranslation;
    if ((location - mLastEmitLocation).SquaredLength() > 1.0f)
        mLastEmitLocation = location;

    mCurrentEmitRateScale = mLODEmitScale.Lerp(lodFactor) * mEmitScale;
    float sizeScale = mLODSizeScale.Lerp(lodFactor) * mSizeScale;
    mCurrentAlphaScale = mLODAlphaScale.Lerp(lodFactor) * mAlphaScale;
    mCurrentColorScale.a = mColorScale.a;
    mCurrentColorScale.rgb = mColorScale.rgb;
    if (mDesc->mFlags.test(kParticleFlagScaleSizeOnly)) {
        mCurrentEmitSizeScale = 1.0f;
        mCurrentSizeScale = sizeScale;
    } else {
        mCurrentEmitSizeScale = sizeScale;
        mCurrentSizeScale = 1.0f;
    }
    if (mDesc->mFlags.test(kParticleFlagSizeScaleTransform))
        mCurrentEmitSizeScale *= mSourceTransform.mScale;

    uint32_t lodFlags = mDesc->mFlags.mWord[0];
    if (!((lodFlags & 1) || ((lodFlags >> 1) & 1))) {
        mCurrentEmitSizeScale *= mGlobalParams->mParticleScale;
        mCurrentEmitRateScale *= mGlobalParams->mParticleDensity;
    }

    if (mDesc->mFlags.test(kParticleFlagAttractor)) {
        mAttractorLocation = mDesc->mAttractorOrigin;
        mSourceTransform.TransformPoint(mAttractorLocation);
        mAttractorIntensity = 1.0f;
    }

    mOverallTime += deltaTime;

    mDirectionalForcesSum = Vector3_s00f7_caf0::Scaled(mDesc->mGravityStrength, mGlobalParams->mGravityDirection);
    mDirectionalForcesSum += Vector3_s00f7_caf0::Scaled(mDesc->mWindStrength, mGlobalParams->mWindDirection);
    mRigidTransform.BackTransformVector(mDirectionalForcesSum);
    mDirectionalForcesSum += mDesc->mDirectionalForcesSum;

    if (!mSurfaceStateData.empty() && !mSurfaceStateDataValid) {
        for (cSurfaceRec_s00f7_caf0* rec = mSurfaceRecs.begin(); rec != mSurfaceRecs.end(); ++rec)
            rec->mpSurface->InitState(rec->mpInfo, mSourceTransform, mRigidTransform,
                                      &mSurfaceStateData[rec->mStateOffset]);
        mSurfaceStateDataValid = true;
    }

    cParticle_s00f7_caf0* it = mParticles.begin();
    mBoundingBox.Reset();

    if (sPhysicsUpdate[mDesc->mPhysicsType]) {
        while (it != mParticles.end()) {
            cParticle_s00f7_caf0* p = it;
            if (sPhysicsUpdate[mDesc->mPhysicsType](p, deltaTime, mDesc, this)) {
                mBoundingBox.AddPoint(p->mPosition);
                it = it->mpNext;
            } else {
                it = mParticles.erase(it);
                RemoveParticle(p);
            }
        }
    } else {
        while (it != mParticles.end()) {
            cParticle_s00f7_caf0* p = it;
            if (UpdatePhysicsSimple(p, deltaTime, mDesc, this)) {
                mBoundingBox.AddPoint(p->mPosition);
                it = it->mpNext;
            } else {
                it = mParticles.erase(it);
                RemoveParticle(p);
            }
        }
    }

    if (!mDelayedStopActive && !mSuppressEmission)
        GenerateNewParticles(deltaTime);

    float maxSize = mRigidTransform.mScale * mMaxParticleSize * mCurrentSizeScale * mCurrentEmitSizeScale;
    mBoundingBox.Transform(mRigidTransform);
    if (mTextureParticlesID >= 0)
        mWorld->GetRenderer()->UpdateTextureParticles(mTextureParticlesID, mBoundingBox, maxSize);
    else if (mModelParticlesID >= 0)
        mWorld->GetRenderer()->UpdateModelParticles(mModelParticlesID, mBoundingBox, maxSize);

    if (mParticleCount == 0 && mDelayedStopActive) {
        mStarted = false;
        if (mTextureParticlesID >= 0)
            mWorld->GetRenderer()->StopTextureParticles(mTextureParticlesID, 0);
        else if (mModelParticlesID >= 0)
            mWorld->GetRenderer()->StopModelParticles(mModelParticlesID, 0);
        if (mChainSystem)
            mChainSystem->Stop(false);
        return;
    }

    mLastEmitLocation = location;
    if (mDesc->mFlags.test(kParticleFlagModelStats))
        stats->mModelParticles += mParticleCount;
    else
        stats->mTextureParticles += mParticleCount;
    mParamsChanged = false;
}
}}  // namespace EA::Swarm

// @ 0x00f7d3d0
namespace EA { namespace Swarm {
void __thiscall cParticlesEffectCore::F7d3d0(cParamFactory* mgr)
{
    const float minRate = 1e-6f;
    const float& rate = mDesc->mRateCurveTime > minRate ? mDesc->mRateCurveTime : minRate;
    mRateCurveTimeInv = 1.0 / rate;

    mPhysicsField16c = mDesc->mField1dc;
    mPhysicsField170 = mDesc->mField1e0;
    mPhysicsType = mDesc->mPhysicsSubtype;

    if (mDesc->mFlags.test(kParticleFlagAttractor)) {
        mAttractorLocation = mDesc->mAttractorOrigin;
        mRigidTransform.InverseTransformPoint(mAttractorLocation);
        mAttractorIntensity = 1.0f;
    } else {
        mAttractorLocation = gZeroVector;
        mAttractorIntensity = 0.0f;
    }

    mColorParams2 = mDesc->mColorParams2;
    mColorParams1 = mDesc->mColorParams1;

    mMaxParticleSize = mDesc->mSizeCurve[0];
    for (uint32_t i = 1; i < mDesc->mSizeCurve.size(); ++i) {
        if (mMaxParticleSize < mDesc->mSizeCurve[i])
            mMaxParticleSize = mDesc->mSizeCurve[i];
    }

    if ((mDesc->mParamMask0A & mDesc->mParamMask0B) != 0xffffffff) {
        cIParam* p = mgr->CreateParam(mDesc->mParamMask0A, mDesc->mParamMask0B);
        cIParam* old = mParam0;
        if (p != old) {
            if (p) p->AddRef();
            mParam0 = p;
            if (old) old->Release();
        }
    }
    if ((mDesc->mParamMask1A & mDesc->mParamMask1B) != 0xffffffff) {
        cIParam* p = mgr->CreateParam(mDesc->mParamMask1A, mDesc->mParamMask1B);
        cIParam* old = mParamA;
        if (p != old) {
            if (p) p->AddRef();
            mParamA = p;
            if (old) old->Release();
        }
    }
    if ((mDesc->mParamMask2A & mDesc->mParamMask2B) != 0xffffffff) {
        cIParam* p = mgr->CreateParam(mDesc->mParamMask2A, mDesc->mParamMask2B);
        cIParam* old = mParamB;
        if (p != old) {
            if (p) p->AddRef();
            mParamB = p;
            if (old) old->Release();
        }
    }

    if (mParam0) {
        mParam0->v08();
        mParam0Ready = mParam0->IsReady();
    }
    if (mParamA) {
        mParamA->v08();
        mParamAReady = mParamA->IsReady();
        mCachedParamA = mParamA->GetValue();
    }
    if (mParamB) {
        mParamB->v08();
        mParamBReady = mParamB->IsReady();
        mCachedParamB = mParamB->GetValue();
    }

    mSurfaceRecs.erase(mSurfaceRecs.mpBegin, mSurfaceRecs.mpEnd);

    vector<cSurfaceParam>& params = mDesc->mSurfaceParams;
    if (!params.empty()) {
        int size0 = 0;
        int size1 = 0;
        BuildSurfaceRecs(mgr, &params, &mSurfaceRecs, &size0, &size1, &mStateDirty);
        mSurfaceStateDataValid = false;
        mSurfaceStateData.resize((uint32_t)size0);
    } else {
        mSurfaceStateData.clear();
        mStateDirty = false;
    }
}
}}  // namespace EA::Swarm

// @ 0x00f7d7a0
namespace EA { namespace Swarm {
void __thiscall cParticlesEffectView::F7d7a0(cIEffectsWorld_s00f7_caf0* world, cParamFactory* mgr, void* unused)
{
    mWorld = world;
    mGlobalParams = world->GetGlobalParams();
    mBoundingBox.Reset();
    core()->F7d3d0(mgr);

    cIParticleStream* p6 = mgr->p14();
    cIParticleStream* p7 = (cIParticleStream*)world->GetRenderer();
    if (!p7)
        return;

    cParticlesDescription_s00f7_caf0* desc = mDesc;
    cEffectStateBlock block = desc->mStateBlock;
    uint32_t maskA = mSurfaceParamMaskA;
    uint32_t maskB = mSurfaceParamMaskB;
    if ((maskB & maskA) != 0xffffffff) {
        block.mField00 = maskA;
        block.mField04 = maskB;
    }

    if (desc->mFlags.test(kParticleFlagModelStats)) {
        if (block.mType == 0x0f)
            block.mStatus = p6->s24(block.mField18, block.mField1c, 9);
        else
            block.mStatus = 9;
        p7->s2c(static_cast<cParticleBase1*>(core()), &block, &mModelParticlesID);
        p7->s10(block.mStatus, &mStreamState[0]);
    } else {
        if (block.mType == 0x0f) {
            block.mStatus = 0x10;
            mStreamState[0] = 0;
            mStreamState[1] = 0x10;
            mStreamState[2] = 0x20;
            mStreamState[3] = 0x24;
            mStreamState[4] = 0x28;
        } else {
            block.mStatus = 0;
            p7->s10(0, &mStreamState[0]);
        }
        p7->s18(core(), &block, &mTextureParticlesID);
    }
    mStreamFlag = block.mStatus;
}
}}  // namespace EA::Swarm

// @ 0x00f7d990
namespace EA { namespace Swarm {
void __thiscall cParticlesEffectView::F7d990(cParticlesDescription_s00f7_caf0* desc)
{
    mDesc = desc;
    cParamFactory* mgr = mWorld->GetParamFactory();
    core()->F7d3d0(mgr);
}
}}  // namespace EA::Swarm
