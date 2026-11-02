// src/game/SPTerrain/_at_00f40000.cpp -- migrated from slice(s) s00f4baa0, s00f4aaf0 by tools/migrate/rewrite.py
// Object file: SPTerrain/_at_00f40000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/Swarm/cTransform.h"

// unnamed retail callees and globals (address in the comment)
extern float DAT_016c8ff0;
extern float DAT_016c8ff4;
extern float DAT_016c8ff8;
extern const float k9999;                            // 0x0148e61c (9999.0f)
#include <math.h>
#include <string.h>
#include <intrin.h>

// ---- items of slice s00f4aaf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef unsigned __int64 uint64;
struct Vector3 { float x, y, z; };
struct Vector2 { float x, y; };
struct Matrix3 { float m[9]; Matrix3* Assign(const Matrix3* src); };   // 0x0041cb40
struct cTransform {                       // EA::Swarm::cTransform, 0x38
    uint16 mFlags;
    uint16 mModificationCount;
    Vector3 mTranslation;
    float mScale;
    Matrix3 mRotation;
    void PreTransformBy(const cTransform* x);            // 0x00537f40
    cTransform& operator=(const cTransform& o);          // 0x00537dc0
};
struct FloatVector {                       // eastl::vector<float, sp_vector_allocator> 0x14
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    uint32 mAlloc[2];
    uint32 size() const { return (uint32)(mpEnd - mpBegin); }
};
struct cBrushVertex {                      // SP::cBrushVertex, 0x1c
    Vector3 mPosition;
    Vector2 mUV;
    float mIntensity;
    float mSize;
};
struct BrushVertexVector {                 // eastl::vector<cBrushVertex, sp_vector_allocator>
    cBrushVertex* mpBegin;                 // +0x00
    cBrushVertex* mpEnd;                   // +0x04
    cBrushVertex* mpCapacity;              // +0x08
    uint32 mAlloc[2];                      // +0x0c
    uint32 size() const;                   // 0x00f4b160
    cBrushVertex* back();                  // 0x00f4b180
};
struct cTerrainBrushDescription {          // SP::cTerrainBrushDescription (retail layout)
    uint32 mDescriptionBase[2];            // +0x00
    float  mLocation[3];                   // +0x08
    uint32 pad14;                          // +0x14
    uint32 mTexture[2];                    // +0x18
    uint8  mDrawMode;                      // +0x20
    bool   mDoGaussian;                    // +0x21
    char   pad22[2];
    float  mGaussianSlope;                 // +0x24
    float  mLifetime;                      // +0x28
    FloatVector mSizeCurve;                // +0x2c
    FloatVector mIntensityCurve;           // +0x40
    bool   mWaterLevelIsZero;              // +0x54
    char   pad55[3];
    float  mIntensityVary;                 // +0x58
    float  mSizeVary;                      // +0x5c
    float  mRotationVary;                  // +0x60
    float  mTextureOffset[2];              // +0x64
    float  mLevelValue;                    // +0x6c
    float  mLevelVary;                     // +0x70
    float  mLevelRangeValue1;              // +0x74
    float  mLevelRangeValue2;              // +0x78
    float  mImprintsPerSecond;             // +0x7c
    bool   mDoFiltering;                   // +0x80
    bool   mFilterGlobal;                  // +0x81
    uint8  mKernelType;                    // +0x82
    uint8  mKernelOp;                      // +0x83
    float  mDeltaAmount;                   // +0x84
    FloatVector mSpacingCurve;             // +0x88
    float  mSpacingVary;                   // +0x9c
    uint8  mCondOp;                        // +0xa0
    char   padA1[3];
    float  mCondN1;                        // +0xa4
    float  mCondN2;                        // +0xa8
    uint8  mFallOffOp;                     // +0xac
    char   padAd[3];
    float  mFallOffN1;                     // +0xb0
    float  mFallOffN2;                     // +0xb4
    uint8  mGradientCondOp;                // +0xb8
    char   padB9[3];
    float  mGradientCondN1;                // +0xbc
    float  mGradientCondN2;                // +0xc0
    uint8  mGradientFallOffOp;             // +0xc4
    char   padC5[3];
    float  mGradientFallOffN1;             // +0xc8
    float  mGradientFallOffN2;             // +0xcc
    bool   mDoCubeMap;                     // +0xd0
    char   padD1[3];
    Vector3 mRot;                          // +0xd4
    Vector3 mRotVary;                      // +0xe0
    bool   mRibbonBrush;                   // +0xec
    char   padEd[0x108 - 0xed];            // tail (ribbon params)

    cTerrainBrushDescription();                                  // 0x00f49040
    cTerrainBrushDescription& operator=(const cTerrainBrushDescription&);  // 0x00f4a5d0
    ~cTerrainBrushDescription();                                 // 0x00f48b00
    cTerrainBrushDescription* Construct(const cTerrainBrushDescription& src);  // 0x00f4a810
};
struct SWARM_TerrainBrushCreate {
    void* vtbl;                            // +0x00
    void* vtbl2;                           // +0x04
    int   mRefTarget;                      // +0x08
    void* mParam;                          // +0x0c
    uint8 mFlag10;                         // +0x10
    char  pad11[3];                        // +0x11
    uint16 w14;                            // +0x14
    uint16 w16;                            // +0x16
    Vector3 mPos;                          // +0x18
    float mSize;                           // +0x24
    Matrix3 mRot;                          // +0x28
    float mF4c;                            // +0x4c
    uint16 w50;                            // +0x50
    uint16 w52;                            // +0x52
    Vector3 mPos2;                         // +0x54
    float mSize2;                          // +0x60
    Matrix3 mRot2;                         // +0x64
    float mF88;                            // +0x88
    uint8 mFlag8c;                         // +0x8c
    float mF90;                            // +0x90
    float mF94;                            // +0x94
    float mF98;                            // +0x98
    float mF9c;                            // +0x9c
    float mFa0;                            // +0xa0
    float mFa4;                            // +0xa4
    uint8 mFa8;                            // +0xa8
    uint8 mFa9;                            // +0xa9
    float mFac;                            // +0xac
    float mFb0;                            // +0xb0
    float mFb4;                            // +0xb4
    float mFb8;                            // +0xb8
    float mFbc;                            // +0xbc
    void* mPc0;                            // +0xc0
    void* mPc4;                            // +0xc4
    uint32 mCc8;                           // +0xc8
    uint32 mCcc;                           // +0xcc
    SWARM_TerrainBrushCreate(void* p);     // 0x00f4b220
    ~SWARM_TerrainBrushCreate();           // 0x00f4b3a0
};
struct cComponentStats;
struct cDecalFront {                       // brush/level descriptor
    uint8  mUseNoise;                      // +0x00  (no texture, or gaussian draw)
    uint8  mFilterGlobal;                  // +0x01
    uint8  mDoCubeMap;                     // +0x02
    uint8  pad03;
    float  mGaussianSlope;                 // +0x04
    uint32 mDrawMode;                      // +0x08
    float  mLevel;                         // +0x0c
    float  mLevelRange1;                   // +0x10
    float  mLevelRange2;                   // +0x14
    float  mRotationVary;                  // +0x18
};
struct cDecalBoxParams {                   // filter / gradient descriptor
    uint8  mDoFiltering;                   // +0x00
    uint8  mRibbonKernel;                  // +0x01  (mKernelType == 0x12)
    char   pad02[2];
    uint32 mKernel[17];                    // +0x04  kernel weights (0x44 bytes)
    uint32 mGradientCondOp;                // +0x48
    float  mGradientCondN1;                // +0x4c
    float  mGradientCondN2;                // +0x50
    uint32 mGradientFallOffOp;             // +0x54
    float  mGradientFallOffN1;             // +0x58
    float  mGradientFallOffN2;             // +0x5c
};
struct cTerrainEditor {
    float GetWaterLevel();                                // 0x00f678d0
    float GetHeightAt(Vector3 p);                         // 0x00f67aa0
    void  BuildDecalBox(int a2, int a3, int a4, void** outRef,
                        const cDecalFront* front, const cDecalBoxParams* params,
                        int zero, float offset, float rotVary, int zero2, int one);
    // 0x00f6c940
};
cTerrainEditor* TerrainEditor();                          // 0x00f48a70
class cTerrainBrushEffect {
public:
    virtual void Initialize(void*, void*, void*);
    virtual void Dispose();
    virtual void Start(int hardStart);
    virtual int  Stop(int hardStop);
    virtual int  IsRunning();
    virtual void ApplyEffect(float dt, float, cComponentStats*);

    void ApplyGlobal(float intensity, const Matrix3& kernel);   // 0x00f4bcb0
    bool SetParam(int id, float* value, int);                   // 0x00f4b110
    void Imprint(const Vector3& pos, int, int, int, const void* kernel);  // 0x00f4b870
    void SetTransform(void* a, const cTransform* t);            // 0x00f4b6e0

    int mRefCount;                           // +0x04
    int mRefCountPad;                        // +0x08
    cTerrainBrushDescription* mDesc;         // +0x0c
    bool mActive;                            // +0x10
    cTransform mTransform;                   // +0x14
    float mSize;                             // +0x4c
    cTransform mPreviousTransform;           // +0x50
    float mPreviousSize;                     // +0x88
    bool mPreviousValuesInitialized;         // +0x8c
    float mAccumulatedTime;                  // +0x90
    float mLODSizeScale;                     // +0x94
    float mIntensityScale;                   // +0x98
    float mOverallTime;                      // +0x9c
    float mInvLifetime;                      // +0xa0
    float mLifeTime;                         // +0xa4
    bool mDoSpacing;                         // +0xa8
    bool mDoSpacingVary;                     // +0xa9
    float mSpacingVaryVal;                   // +0xac
    float mDistTraveled;                     // +0xb0
    float mUserLevelParm;                    // +0xb4
    float mUserSizeParm;                     // +0xb8
    float mLevelValue;                       // +0xbc
    void* mpTexture;                         // +0xc0
    BrushVertexVector mRibbonBrushList;      // +0xc4
};
void  EAAllocatorDeallocate(void* p);                                       // 0x00f47380
__forceinline void ReleaseNoRef(void* p)
{
    long* c = (long*)((char*)p + 8);
    _InterlockedExchangeAdd(c, -1);
    long old = _InterlockedExchangeAdd(c, 0);
    if (old < 1)
        _InterlockedExchangeAdd(c, 1);
    else
        _InterlockedExchangeAdd(c, 0);
}
struct TextureRef { void* p; void Assign(void* src); };      // 0x00576650 (this = destination)
void* Singleton67dd60();                             // 0x0067dd60
extern float DAT_016c8ff0;
extern float DAT_016c8ff4;
extern float DAT_016c8ff8;
extern Matrix3 DAT_016c9020;
extern const float k9999;                            // 0x0148e61c (9999.0f)
struct VtblObj { void* slot[16]; };
extern VtblObj kGmeRefCountVtbl;                     // 0x013ef094
extern VtblObj kGmeIComponentVtbl;                   // 0x013f21d4
extern VtblObj kBrushCreateVtbl;                     // 0x0148e714
extern VtblObj kBrushCreateVtbl2;                    // 0x0148e710
struct F7 { float a, b, c, d, e, f, g; };
// ---- items of slice s00f4aaf0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern Matrix3 DAT_016c9020;
extern VtblObj kGmeRefCountVtbl;                     // 0x013ef094
extern VtblObj kGmeIComponentVtbl;                   // 0x013f21d4
extern VtblObj kBrushCreateVtbl;                     // 0x0148e714
extern VtblObj kBrushCreateVtbl2;                    // 0x0148e710

// ---- items of slice s00f4baa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __stdcall VectorCopyCtorIterator(void* dst, const void* src, int elemSize,
                                                 int count, void* ctor);   // 0x00406540
extern "C" void BrushVertexCopyCtor(void* dst, const void* src);           // 0x00705c00
extern const char gSimulatorName[];   // 0x013f09b4
extern const char gAllocatorPath[];   // 0x013ebb38
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)
struct cSPVector3_s00f4_baa0 {                   // 0x0c
    float x, y, z;
};
struct cSPVector2_s00f4_baa0 {                   // 0x08
    float x, y;
};
struct cTextureInstance_s00f4_baa0 {
    void*          vftable;           // +0x00
    unsigned int   mField04;          // +0x04
    volatile long  mnRefCount;        // +0x08

    int Release() {
        _InterlockedDecrement(&mnRefCount);
        if (_InterlockedExchangeAdd(&mnRefCount, 0) < 1) {
            _InterlockedIncrement(&mnRefCount);
            return 1;
        }
        return _InterlockedExchangeAdd(&mnRefCount, 0);
    }
};
float RandomRange(float lo, float hi);                    // 0x007d45d0
struct TexRef {                       // EA::AutoRefCount<cTextureInstance>
    cTextureInstance_s00f4_baa0* mpObject;       // +0x00

    TexRef& operator=(cTextureInstance_s00f4_baa0* p);               // 0x00576650
    ~TexRef() {
        if (mpObject)
            mpObject->Release();
    }
};
namespace SP {
struct cBrushVertex_s00f4_baa0 {                 // 0x1c
    cSPVector3_s00f4_baa0 mPosition;             // +0x00
    cSPVector2_s00f4_baa0 mUV;                   // +0x0c
    float      mIntensity;            // +0x14
    float      mSize;                 // +0x18

    cBrushVertex_s00f4_baa0() {}
    cBrushVertex_s00f4_baa0(const cBrushVertex_s00f4_baa0& o) {
        mPosition.x = o.mPosition.x;
        mPosition.y = o.mPosition.y;
        mPosition.z = o.mPosition.z;
        mUV.x = o.mUV.x;
        mUV.y = o.mUV.y;
        mIntensity = o.mIntensity;
        mSize = o.mSize;
    }
};
}
namespace SP {
struct cRibbonBrushPoly {             // 0x1c4
    int          mNumVertices;        // +0x000
    cBrushVertex_s00f4_baa0 mVertices[16];       // +0x004

    cRibbonBrushPoly() {}
    cRibbonBrushPoly(const cRibbonBrushPoly& o) {
        mNumVertices = o.mNumVertices;
        VectorCopyCtorIterator(mVertices, o.mVertices, sizeof(cBrushVertex_s00f4_baa0), 16,
                               (void*)BrushVertexCopyCtor);
    }
};
}
namespace SP {
struct cRibbonFalloffParams {         // 0x44
    int   mField00[11];               // +0x00
    int   mFallOffOp;                 // +0x2c
    float mFallOffN1;                 // +0x30
    float mFallOffN2;                 // +0x34
    int   mGradientCondOp;            // +0x38
    float mGradientCondN1;            // +0x3c
    float mGradientCondN2;            // +0x40
};
}
namespace SP {
struct cBrushTextureInfo {            // 0x78
    TexRef mTexture;                  // +0x00
    char   mField04;                  // +0x04
    char   mFilterGlobal;             // +0x05
    char   mDoCubeMap;                // +0x06
    char   pad07;                     // +0x07
    float  mGaussianSlope;            // +0x08
    int    mDrawMode;                 // +0x0c
    float  mVary;                     // +0x10
    float  mLevelRangeValue1;         // +0x14
    float  mLevelRangeValue2;         // +0x18
    float  mIntensity;                // +0x1c
    float  mRotationX;                // +0x20
    float  mRotationY;                // +0x24
    float  mRotationZ;                // +0x28
    char   pad2c[0x10];               // +0x2c
    int    mReserved;                 // +0x3c
    char   pad40[0x38];               // +0x40
};
}
namespace SP {
struct cBrushHeightInfo {             // 0x7c
    char  mDoFiltering;               // +0x00
    char  mRibbonKernel;              // +0x01
    char  pad02[2];                   // +0x02
    cRibbonFalloffParams mFalloff;    // +0x04
    int   mGradientCondOp;            // +0x48
    float mGradientCondN1;            // +0x4c
    float mGradientCondN2;            // +0x50
    int   mGradientFallOffOp;         // +0x54
    float mGradientFallOffN1;         // +0x58
    float mGradientFallOffN2;         // +0x5c
    char  pad60[0x1c];                // +0x60
};
}
struct FloatVector_s00f4_baa0 {                  // eastl::vector<float, sp_vector_allocator>, 0x14
    void*    mpBegin;                 // +0x00
    void*    mpEnd;                   // +0x04
    void*    mpCapacity;              // +0x08
    unsigned mAlloc[2];               // +0x0c
};
struct cTerrainBrushDescription_s00f4_baa0 {     // 0x108
    int    mDescriptionBase[2];       // +0x00
    float  mLocation[3];              // +0x08
    int    pad14;                     // +0x14
    int    mTexture[2];               // +0x18
    unsigned char mDrawMode;          // +0x20
    bool   mDoGaussian;               // +0x21
    char   pad22[2];                  // +0x22
    float  mGaussianSlope;            // +0x24
    float  mLifetime;                 // +0x28
    FloatVector_s00f4_baa0 mSizeCurve;           // +0x2c
    FloatVector_s00f4_baa0 mIntensityCurve;      // +0x40
    bool   mWaterLevelIsZero;         // +0x54
    char   pad55[3];                  // +0x55
    float  mIntensityVary;            // +0x58
    float  mSizeVary;                 // +0x5c
    float  mRotationVary;             // +0x60
    float  mTextureOffset[2];         // +0x64
    float  mLevelValue;               // +0x6c
    float  mLevelVary;                // +0x70
    float  mLevelRangeValue1;         // +0x74
    float  mLevelRangeValue2;         // +0x78
    float  mImprintsPerSecond;        // +0x7c
    bool   mDoFiltering;              // +0x80
    bool   mFilterGlobal;             // +0x81
    unsigned char mKernelType;        // +0x82
    unsigned char mKernelOp;          // +0x83
    float  mDeltaAmount;              // +0x84
    FloatVector_s00f4_baa0 mSpacingCurve;        // +0x88
    float  mSpacingVary;              // +0x9c
    unsigned char mCondOp;            // +0xa0
    char   padA1[3];                  // +0xa1
    float  mCondN1;                   // +0xa4
    float  mCondN2;                   // +0xa8
    unsigned char mFallOffOp;         // +0xac
    char   padAd[3];                  // +0xad
    float  mFallOffN1;                // +0xb0
    float  mFallOffN2;                // +0xb4
    unsigned char mGradientCondOp;    // +0xb8
    char   padB9[3];                  // +0xb9
    float  mGradientCondN1;           // +0xbc
    float  mGradientCondN2;           // +0xc0
    unsigned char mGradientFallOffOp; // +0xc4
    char   padC5[3];                  // +0xc5
    float  mGradientFallOffN1;        // +0xc8
    float  mGradientFallOffN2;        // +0xcc
    bool   mDoCubeMap;                // +0xd0
    char   padD1[3];                  // +0xd1
    float  mRot[3];                   // +0xd4
    float  mRotVary[3];               // +0xe0
    bool   mRibbonBrush;              // +0xec
    char   padEd[0x108 - 0xed];       // +0xed
};
void* EAAllocate(size_t size, const char* name, unsigned a, unsigned b, const char* file,
                 int line);           // 0x00f473a0
void  operator delete[](void* p);     // 0x00f47380
namespace eastl {
struct sp_vector_allocator_s00f4_baa0 {
    int mFlags;
    int mUnused;

    bool operator==(const sp_vector_allocator_s00f4_baa0&) const { return true; }
    void deallocate(void* p, size_t) {
        if (p != 0 && ((int*)p)[-1] != 0)
            ::operator delete[](p);
    }
};
}
namespace eastl {
template <class T, class Allocator> class vector_s00f4_baa0 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;

    void DoInsertValue(T* position, const T& value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
    void push_back();
    void erase(T* first, T* last);    // 0x00d73090
};
}
typedef eastl::vector_s00f4_baa0<SP::cBrushVertex_s00f4_baa0, eastl::sp_vector_allocator_s00f4_baa0> BrushVertexVector_s00f4_baa0;
SP::cBrushVertex_s00f4_baa0*  CopyVerticesForward(SP::cBrushVertex_s00f4_baa0* first, SP::cBrushVertex_s00f4_baa0* last, SP::cBrushVertex_s00f4_baa0* dest);          // 0x00f4b1d0
inline void* operator new(size_t, void* p) { return p; }
template <class T>
inline T* CopyBackward(T* first, T* last, T* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
class cTerrainEditor_s00f4_baa0 {
public:
    float GetRandom01();                                                              // 0x00f678d0
    void  ApplyBrush(SP::cBrushTextureInfo* texInfo, SP::cBrushHeightInfo* heightInfo, int count,
                     SP::cRibbonBrushPoly* polys, int flags);                             // 0x00f6e120
    void  ApplyGlobalBrush(SP::cBrushTextureInfo* texInfo, SP::cBrushHeightInfo* heightInfo,
                           int flags, float vary);                                    // 0x00f6df40
};
cTerrainEditor_s00f4_baa0* TerrainEditor_s00f4_baa0();                                                      // 0x00f48a70
class cTerrainBrushEffect_s00f4_baa0 {
public:
    void*                     vftable;                    // +0x00
    char                      pad04[0x0c - 0x04];         // +0x04
    cTerrainBrushDescription_s00f4_baa0* mDesc;                      // +0x0c
    bool                      mIsActive;                  // +0x10
    char                      pad11[0x9c - 0x11];         // +0x11
    float                     mOverallTime;               // +0x9c
    char                      padA0[0xbc - 0xa0];         // +0xa0
    float                     mVary;                      // +0xbc
    cTextureInstance_s00f4_baa0*         mpTexture;                  // +0xc0
    BrushVertexVector_s00f4_baa0         mRibbonBrushList;           // +0xc4

    void ApplyBrush(float intensity, int count, SP::cRibbonBrushPoly* polys,
                    const SP::cRibbonFalloffParams* params);                              // 0x00f4baa0
    void ApplyGlobalBrush(float vary, const SP::cRibbonFalloffParams* params);             // 0x00f4bcb0
    void Start(int a);                                                                // 0x00f4c2c0
    void Imprint(float intensity, int count, SP::cRibbonBrushPoly* polys,
                 const SP::cRibbonFalloffParams* params);                                 // 0x00f4b870
};
float gRealOne;               // _HK_REAL_ONE, 0x01485720
// ---- items of slice s00f4baa0 end

// @ 0x00f4b110
bool cTerrainBrushEffect::SetParam(int id, float* value, int)
{
    switch (id) {
    case 4:
        mIntensityScale = *value;
        return true;
    case 0x15:
        mUserLevelParm = *value;
        return true;
    case 0x16:
        mUserSizeParm = *value;
        return true;
    }
    return false;
}

// @ 0x00f4b1d0
F7* CopyF7(F7* first, F7* last, F7* dst)
{
    for (; first != last; ++first) {
        if (dst) {
            dst->a = first->a;
            dst->b = first->b;
            dst->c = first->c;
            dst->d = first->d;
            dst->e = first->e;
            dst->f = first->f;
            dst->g = first->g;
        }
        ++dst;
    }
    return dst;
}

// @ 0x00f4b220
SWARM_TerrainBrushCreate::SWARM_TerrainBrushCreate(void* p)
{
    vtbl2 = (void*)&kGmeRefCountVtbl;
    mRefTarget = 0;
    vtbl = (void*)&kBrushCreateVtbl;
    vtbl2 = (void*)&kBrushCreateVtbl2;
    mParam = p;
    mFlag10 = 0;
    w14 = 0;
    w16 = 0;
    mPos.x = DAT_016c8ff0;
    mPos.y = DAT_016c8ff4;
    mPos.z = DAT_016c8ff8;
    mSize = 1.0f;
    mRot.Assign(&DAT_016c9020);
    mF4c = 1.0f;
    w52 = 0;
    w50 = 0;
    mPos2.x = DAT_016c8ff0;
    mPos2.y = DAT_016c8ff4;
    mPos2.z = DAT_016c8ff8;
    mSize2 = 1.0f;
    mRot2.Assign(&DAT_016c9020);
    mF88 = 1.0f;
    mF94 = 1.0f;
    mF98 = 1.0f;
    mFa0 = 1.0f;
    mFa4 = 1.0f;
    mFac = 1.0f;
    mFlag8c = 0;
    mFa8 = 0;
    mF90 = 0.0f;
    mF9c = 0.0f;
    mFa9 = 1;
    mFb0 = 0.0f;
    mFb4 = k9999;
    mFb8 = k9999;
    mFbc = 0.0f;
    mPc0 = 0;
    mPc4 = 0;
    mCc8 = 0;
    mCcc = 0;
}

// @ 0x00f4b3a0
SWARM_TerrainBrushCreate::~SWARM_TerrainBrushCreate()
{
    vtbl = (void*)&kBrushCreateVtbl;
    vtbl2 = (void*)&kBrushCreateVtbl2;
    if (mPc4 != 0 && *(int*)((char*)mPc4 - 4) != 0)
        EAAllocatorDeallocate(mPc4);
    if (mPc0 != 0)
        ReleaseNoRef(mPc0);
    vtbl = (void*)&kGmeIComponentVtbl;
    vtbl2 = (void*)&kGmeRefCountVtbl;
}

// @ 0x00f4b420
void cTerrainBrushEffect::Initialize(void*, void*, void*)
{
    float epsilon = 0.0001f;                    // xmm0, loaded before the deref
    cTerrainBrushDescription* d = mDesc;
    mLifeTime = d->mLifetime;
    float* denom = &d->mLifetime;
    if (!(d->mLifetime > epsilon))              // movss xmm1,[ecx]; comiss; ja
        denom = &epsilon;
    mInvLifetime = 1.0f / *denom;
    mDoSpacing = (d->mSpacingCurve.mpBegin != d->mSpacingCurve.mpEnd);
    uint32 texLo = d->mTexture[0];              // mov ecx, [eax+0x18]
    if ((texLo & d->mTexture[1]) != 0xffffffff) {
        void* mgr = Singleton67dd60();
        cTerrainBrushDescription* d2 = mDesc;
        uint64 tex = *(uint64*)&d2->mTexture[0];
        uint32 hi = (uint32)(tex >> 32);
        void** vtbl = *(void***)mgr;
        void* res = ((void* (__thiscall*)(void*, uint32, uint32, uint32))vtbl[0x20 / 4])(mgr, d2->mTexture[0], hi, 0);
        ((TextureRef*)&mpTexture)->Assign(res);
    }
}

// @ 0x00f4b870
void cTerrainBrushEffect::Imprint(const Vector3& pos, int a2, int a3, int a4, const void* kernel)
{
    float offset = 0.0f;
    if (mDesc->mWaterLevelIsZero) {
        float w = TerrainEditor()->GetWaterLevel();
        offset = (w + w) - 1.0f;
    }

    void* outRef = 0;
    ((TextureRef*)&outRef)->Assign(mpTexture);

    cTerrainBrushDescription* d = mDesc;

    cDecalFront front;
    front.mUseNoise      = (mpTexture == 0 || d->mDoGaussian) ? 1 : 0;
    front.mFilterGlobal  = d->mFilterGlobal ? 1 : 0;
    front.mDoCubeMap     = d->mDoCubeMap ? 1 : 0;
    front.mGaussianSlope = d->mGaussianSlope;
    front.mDrawMode      = d->mDrawMode;
    front.mLevel         = mLevelValue + offset;
    front.mLevelRange1   = d->mLevelRangeValue1;
    front.mLevelRange2   = d->mLevelRangeValue2;
    front.mRotationVary  = d->mRotVary.x;
    if (d->mDrawMode != 5 && d->mDrawMode != 6) {
        front.mLevelRange1 += offset;
        front.mLevelRange2 += offset;
    }

    cDecalBoxParams params;
    params.mDoFiltering  = d->mDoFiltering ? 1 : 0;
    params.mRibbonKernel = (d->mDoFiltering && d->mKernelType == 0x12) ? 1 : 0;
    for (int i = 0; i < 17; ++i)
        params.mKernel[i] = ((const uint32*)kernel)[i];
    params.mGradientCondOp    = d->mGradientCondOp;
    params.mGradientCondN1    = d->mGradientCondN1;
    params.mGradientCondN2    = d->mGradientCondN2;
    params.mGradientFallOffOp = d->mGradientFallOffOp;
    params.mGradientFallOffN1 = d->mGradientFallOffN1;
    params.mGradientFallOffN2 = d->mGradientFallOffN2;

    (void)pos;
    TerrainEditor()->BuildDecalBox(a2, a3, a4, &outRef, &front, &params, 0, offset,
                                   d->mRotVary.x, 0, 1);

    if (outRef != 0)
        ReleaseNoRef(outRef);
}

// @ 0x00f4baa0
void cTerrainBrushEffect_s00f4_baa0::ApplyBrush(float intensity, int count, SP::cRibbonBrushPoly* polys, const SP::cRibbonFalloffParams* params)
{
    float vary = 0.0f;
    if (mDesc->mWaterLevelIsZero) {
        float r = TerrainEditor_s00f4_baa0()->GetRandom01();
        vary = r + r - gRealOne;
    }

    SP::cBrushTextureInfo texInfo;
    texInfo.mTexture.mpObject = 0;
    texInfo.mTexture = mpTexture;
    if (mpTexture == 0 || mDesc->mDoGaussian)
        texInfo.mField04 = 1;
    else
        texInfo.mField04 = 0;

    cTerrainBrushDescription_s00f4_baa0* desc = mDesc;
    texInfo.mGaussianSlope = desc->mGaussianSlope;
    texInfo.mIntensity = intensity;
    texInfo.mFilterGlobal = (char)desc->mFilterGlobal;
    texInfo.mDoCubeMap = (char)desc->mDoCubeMap;
    texInfo.mDrawMode = desc->mDrawMode;
    texInfo.mVary = mVary + vary;
    texInfo.mLevelRangeValue1 = desc->mLevelRangeValue1;
    texInfo.mLevelRangeValue2 = desc->mLevelRangeValue2;
    if (texInfo.mDrawMode != 5 && texInfo.mDrawMode != 6) {
        texInfo.mLevelRangeValue1 = texInfo.mLevelRangeValue1 + vary;
        texInfo.mLevelRangeValue2 = texInfo.mLevelRangeValue2 + vary;
    }

    SP::cBrushHeightInfo heightInfo;
    texInfo.mReserved = 0;
    heightInfo.mDoFiltering = desc->mDoFiltering;
    heightInfo.mFalloff = *params;
    heightInfo.mRibbonKernel = 0;
    heightInfo.mGradientCondOp = desc->mGradientCondOp;
    heightInfo.mGradientCondN1 = desc->mGradientCondN1;
    heightInfo.mGradientCondN2 = desc->mGradientCondN2;
    heightInfo.mGradientFallOffOp = desc->mGradientFallOffOp;
    heightInfo.mGradientFallOffN1 = desc->mGradientFallOffN1;
    heightInfo.mGradientFallOffN2 = desc->mGradientFallOffN2;
    if (desc->mDoFiltering && desc->mKernelType == 0x12)
        heightInfo.mRibbonKernel = 1;

    TerrainEditor_s00f4_baa0()->ApplyBrush(&texInfo, &heightInfo, count, polys, 0);
}

// @ 0x00f4bcb0
void cTerrainBrushEffect_s00f4_baa0::ApplyGlobalBrush(float vary, const SP::cRibbonFalloffParams* params)
{
    float localVary = 0.0f;
    float rx, ry, rz;
    if (mDesc->mWaterLevelIsZero) {
        float r = TerrainEditor_s00f4_baa0()->GetRandom01();
        localVary = r + r - gRealOne;
    }

    SP::cBrushTextureInfo texInfo;
    texInfo.mTexture.mpObject = 0;
    if (mpTexture == 0 || mDesc->mDoGaussian)
        texInfo.mField04 = 1;
    else
        texInfo.mField04 = 0;

    cTerrainBrushDescription_s00f4_baa0* desc = mDesc;
    texInfo.mGaussianSlope = desc->mGaussianSlope;
    texInfo.mIntensity = vary;
    texInfo.mFilterGlobal = (char)desc->mFilterGlobal;
    rx = RandomRange(desc->mRot[0], desc->mRotVary[0]);
    ry = RandomRange(desc->mRot[1], desc->mRotVary[1]);
    rz = RandomRange(desc->mRot[2], desc->mRotVary[2]);
    texInfo.mVary = mVary + localVary;
    texInfo.mRotationX = rx;
    texInfo.mRotationY = ry;
    texInfo.mRotationZ = rz;
    texInfo.mDrawMode = desc->mDrawMode;
    texInfo.mLevelRangeValue1 = desc->mLevelRangeValue1;
    texInfo.mLevelRangeValue2 = desc->mLevelRangeValue2;
    if (texInfo.mDrawMode != 5 && texInfo.mDrawMode != 6) {
        texInfo.mLevelRangeValue1 = texInfo.mLevelRangeValue1 + localVary;
        texInfo.mLevelRangeValue2 = texInfo.mLevelRangeValue2 + localVary;
    }
    texInfo.mReserved = 0;
    texInfo.mTexture = mpTexture;

    SP::cBrushHeightInfo heightInfo;
    heightInfo.mDoFiltering = desc->mDoFiltering;
    heightInfo.mFalloff = *params;
    heightInfo.mRibbonKernel = 0;
    heightInfo.mGradientCondOp = desc->mGradientCondOp;
    heightInfo.mGradientCondN1 = desc->mGradientCondN1;
    heightInfo.mGradientCondN2 = desc->mGradientCondN2;
    heightInfo.mGradientFallOffOp = desc->mGradientFallOffOp;
    heightInfo.mGradientFallOffN1 = desc->mGradientFallOffN1;
    heightInfo.mGradientFallOffN2 = desc->mGradientFallOffN2;
    if (desc->mDoFiltering && desc->mKernelType == 0x12)
        heightInfo.mRibbonKernel = 1;

    TerrainEditor_s00f4_baa0()->ApplyGlobalBrush(&texInfo, &heightInfo, 0, localVary);
}

// @ 0x00f4bf30
void BrushVertexVector_s00f4_baa0::DoInsertValue(SP::cBrushVertex_s00f4_baa0* position, const SP::cBrushVertex_s00f4_baa0& value)
{
    if (this->mpEnd != this->mpCapacity) {
        const SP::cBrushVertex_s00f4_baa0* pValue = &value;
        if (pValue >= position && pValue < this->mpEnd)
            ++pValue;
        ::new ((void*)this->mpEnd) SP::cBrushVertex_s00f4_baa0(*(this->mpEnd - 1));
        CopyBackward(position, this->mpEnd - 1, this->mpEnd);
        *position = *pValue;
        ++this->mpEnd;
        return;
    }

    unsigned int nPrevSize = (unsigned int)(this->mpEnd - this->mpBegin);
    unsigned int nNewSize = nPrevSize ? (2 * nPrevSize) : 1;
    SP::cBrushVertex_s00f4_baa0* pNewData = nNewSize
        ? (SP::cBrushVertex_s00f4_baa0*)EAAllocate(nNewSize * sizeof(SP::cBrushVertex_s00f4_baa0), gSimulatorName, 0, 0,
                                    gAllocatorPath, 0xd1)
        : 0;
    SP::cBrushVertex_s00f4_baa0* pNewEnd = CopyVerticesForward(this->mpBegin, position, pNewData);
    ::new ((void*)pNewEnd) SP::cBrushVertex_s00f4_baa0(value);
    pNewEnd = CopyVerticesForward(position, this->mpEnd, ++pNewEnd);
    if (this->mpBegin != 0 && ((int*)this->mpBegin)[-1] != 0)
        ::operator delete[](this->mpBegin);
    this->mpEnd = pNewEnd;
    this->mpBegin = pNewData;
    this->mpCapacity = pNewData + nNewSize;
}

// @ 0x00f4c150
void BrushVertexVector_s00f4_baa0::push_back()
{
    if (this->mpEnd < this->mpCapacity) {
        ++this->mpEnd;
        return;
    }
    DoInsertValue(this->mpEnd, SP::cBrushVertex_s00f4_baa0());
}
