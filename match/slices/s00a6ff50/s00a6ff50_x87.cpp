// Slice s00a6ff50 (x87 unit, NO /arch:SSE): EA::Swarm cGlobalParams copy/clone
// and the SP parameter-delta apply helpers. Flags: /O2 /MD /Gy /EHsc /TP /GS- /fp:fast
#include "types.h"
#include <string.h>

extern "C" void  operator_delete__(void* p);                                   // 0xf47380
extern "C" void* EAAllocate(unsigned size, const char* file, int a, int b, int c, int d); // 0xf473a0
extern "C" void* __cdecl memmove_nd(void* dst, const void* src, unsigned n);    // 0x11e0744
extern "C" void  __stdcall ehvec_ctor(void* dst, void* src, unsigned size, int count, void* ctor); // 0x406540
extern "C" void* __stdcall arrElemCopy(void* dst, void* src);                   // 0xac8980

struct M33 {
    float m[9];
    void Assign(const void* src);      // 0x41cb40
    M33() {}                           // 00a70910 style ctor would be inline; see note
};
struct M44 {
    float m[16];
    void Ctor(const void* src);        // 0x45dca0
};
struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------------------
// EA::Swarm::cGlobalParams (0x120) - retail offsets match the PDB layout.
struct cGlobalParams {
    float  mParticleDensity;        // +0x00
    float  mParticleScale;          // +0x04
    int    mParticleMultThreshold;  // +0x08
    float  mMaxParticleSize;        // +0x0c
    int    mMaxParticles;           // +0x10
    int    mMaxEffects;             // +0x14
    int    mMaxDistributeSamples;   // +0x18
    M44    mProjectionMatrix;       // +0x1c
    M33    mCameraOrientation;      // +0x5c
    Vec3   mCameraTranslation;      // +0x80
    Vec3   mLODPosition;            // +0x8c
    Vec3   mCursorRayPoint;         // +0x98
    Vec3   mCursorRayDirection;     // +0xa4
    bool   mCursorRayAvailable;     // +0xb0
    unsigned int mButtonFlags;      // +0xb4
    unsigned int mButtonChangedFlags; // +0xb8
    Vec3   mWindDirection;          // +0xbc
    float  mWindPointStrength;      // +0xc8
    Vec3   mWindPoint;              // +0xcc
    Vec3   mGravityDirection;       // +0xd8
    float  mGravityPointStrength;   // +0xe4
    Vec3   mGravityPoint;           // +0xe8
    Vec3   mSunDirection;           // +0xf4
    float  mSunPointStrength;       // +0x100
    Vec3   mSunPoint;               // +0x104
    bool   mShowBoundingBoxes;      // +0x110
    bool   mShowSurfaces;           // +0x111
    bool   mShowEffects;            // +0x112
    float  mShowEffectsScale;       // +0x114
    bool   mDisableParticleAlpha;   // +0x118
    bool   mDrawParticles;          // +0x119
    bool   mDrawMeshes;             // +0x11a
    bool   mDrawModels;             // +0x11b
    bool   mDrawDecals;             // +0x11c
    cGlobalParams* Ctor(const cGlobalParams* src);   // 0x00a704b0
};

struct IntVec {
    int* mpBegin;
    int* mpEnd;
    int* mpCap;
    void CtorGrow(int count, const int* fill);      // 0x4aa350
    void DoInsertValue(int* pos, const int& v);     // 0x4558a0
};

struct IParamRef {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30();
    virtual void AddRefI();    // slot 13 (0x34)
    virtual void ReleaseI();   // slot 14 (0x38)
};

// SP parameter block, 0x5c bytes (see s00a6ff50.cpp)
struct ParamElem {
    unsigned short f00;    // +0x00
    unsigned short f02;    // +0x02
    float f04;             // +0x04
    float f08;             // +0x08
    float f0c;             // +0x0c
    float f10;             // +0x10
    M33   m14;             // +0x14
    IParamRef* mp38;       // +0x38
    int   f3c;             // +0x3c
    float f40;             // +0x40
    int   f44;             // +0x44
    IntVec vec;            // +0x48
    int   f54;             // +0x54
    int   f58;             // +0x58
    ParamElem* CopyCtor(const ParamElem* src);   // 0x00a70cc0
};

// The delta-apply object: flags at +0x10, source (cGlobalParams at +0xd0), dst.
struct ParamUpdate {
    char pad[0x10];
    unsigned int mFlags;               // +0x10
    const char* mpSrc;                 // +0x14 (cGlobalParams lives at +0xd0)
    cGlobalParams* mpDst;              // +0x18
    void Apply();                      // 0x00a6ff50
};

// EffectParams (0xd8): 0x00-0x64 raw, int-vector at 0x64, 0x78-0xa0 raw,
// int-vector at 0xa0, then an eh-array of 9 4-byte elements at 0xb4.
struct EffectParams {
    char   raw00[0x64];      // +0x00 .. +0x63
    IntVec v64;              // +0x64 (begin/end/cap), fill at +0x70
    int    fill70;           // +0x70
    int    pad74;            // +0x74
    char   raw78[0x28];      // +0x78 .. +0x9f
    IntVec va0;              // +0xa0 (begin/end/cap), fill at +0xac
    int    fillac;           // +0xac
    int    padb0;            // +0xb0
    int    arrb4[9];         // +0xb4 .. +0xd7
    EffectParams* Clone(const EffectParams* src);   // 0x00a70df0
};

// ---------------------------------------------------------------------------
// @ 0x00a6ff50
#define SRCG ((const cGlobalParams*)(mpSrc + 0xd0))
void ParamUpdate::Apply()
{
    if ((mFlags & 1) == 0) {
        mpDst->mParticleDensity = SRCG->mParticleDensity;
        mpDst->mParticleScale = SRCG->mParticleScale;
        mpDst->mParticleMultThreshold = SRCG->mParticleMultThreshold;
        mpDst->mMaxParticleSize = SRCG->mMaxParticleSize;
        mpDst->mMaxParticles = SRCG->mMaxParticles;
        mpDst->mMaxEffects = SRCG->mMaxEffects;
        mpDst->mMaxDistributeSamples = SRCG->mMaxDistributeSamples;
    }
    if ((mFlags & 2) == 0) {
        mpDst->mProjectionMatrix = SRCG->mProjectionMatrix;
        mpDst->mCameraOrientation = SRCG->mCameraOrientation;
        mpDst->mCameraTranslation = SRCG->mCameraTranslation;
        mpDst->mLODPosition = SRCG->mLODPosition;
    }
    if ((mFlags & 4) == 0) {
        mpDst->mCursorRayPoint = SRCG->mCursorRayPoint;
        mpDst->mCursorRayDirection = SRCG->mCursorRayDirection;
        mpDst->mCursorRayAvailable = SRCG->mCursorRayAvailable;
        mpDst->mButtonFlags = SRCG->mButtonFlags;
        mpDst->mButtonChangedFlags = SRCG->mButtonChangedFlags;
    }
    if ((mFlags & 8) == 0) {
        mpDst->mWindDirection = SRCG->mWindDirection;
        mpDst->mWindPointStrength = SRCG->mWindPointStrength;
        mpDst->mWindPoint = SRCG->mWindPoint;
        mpDst->mGravityDirection = SRCG->mGravityDirection;
        mpDst->mGravityPointStrength = SRCG->mGravityPointStrength;
        mpDst->mGravityPoint = SRCG->mGravityPoint;
        mpDst->mSunDirection = SRCG->mSunDirection;
        mpDst->mSunPointStrength = SRCG->mSunPointStrength;
        mpDst->mSunPoint = SRCG->mSunPoint;
    }
    if ((mFlags & 0x10) == 0) {
        mpDst->mShowBoundingBoxes = SRCG->mShowBoundingBoxes;
        mpDst->mShowSurfaces = SRCG->mShowSurfaces;
        mpDst->mShowEffects = SRCG->mShowEffects;
        mpDst->mShowEffectsScale = SRCG->mShowEffectsScale;
        mpDst->mDisableParticleAlpha = SRCG->mDisableParticleAlpha;
        mpDst->mDrawParticles = SRCG->mDrawParticles;
        mpDst->mDrawMeshes = SRCG->mDrawMeshes;
        mpDst->mDrawModels = SRCG->mDrawModels;
        mpDst->mDrawDecals = SRCG->mDrawDecals;
    }
}

// @ 0x00a704b0
cGlobalParams* cGlobalParams::Ctor(const cGlobalParams* src)
{
    mParticleDensity = src->mParticleDensity;
    mParticleScale = src->mParticleScale;
    mParticleMultThreshold = src->mParticleMultThreshold;
    mMaxParticleSize = src->mMaxParticleSize;
    mMaxParticles = src->mMaxParticles;
    mMaxEffects = src->mMaxEffects;
    mMaxDistributeSamples = src->mMaxDistributeSamples;
    mProjectionMatrix.Ctor(&src->mProjectionMatrix);
    mCameraOrientation.Assign(&src->mCameraOrientation);
    mCameraTranslation.x = src->mCameraTranslation.x;
    mCameraTranslation.y = src->mCameraTranslation.y;
    mCameraTranslation.z = src->mCameraTranslation.z;
    mLODPosition.x = src->mLODPosition.x;
    mLODPosition.y = src->mLODPosition.y;
    mLODPosition.z = src->mLODPosition.z;
    mCursorRayPoint.x = src->mCursorRayPoint.x;
    mCursorRayPoint.y = src->mCursorRayPoint.y;
    mCursorRayPoint.z = src->mCursorRayPoint.z;
    mCursorRayDirection.x = src->mCursorRayDirection.x;
    mCursorRayDirection.y = src->mCursorRayDirection.y;
    mCursorRayDirection.z = src->mCursorRayDirection.z;
    mCursorRayAvailable = src->mCursorRayAvailable;
    mButtonFlags = src->mButtonFlags;
    mButtonChangedFlags = src->mButtonChangedFlags;
    mWindDirection.x = src->mWindDirection.x;
    mWindDirection.y = src->mWindDirection.y;
    mWindDirection.z = src->mWindDirection.z;
    mWindPointStrength = src->mWindPointStrength;
    mWindPoint.x = src->mWindPoint.x;
    mWindPoint.y = src->mWindPoint.y;
    mWindPoint.z = src->mWindPoint.z;
    mGravityDirection.x = src->mGravityDirection.x;
    mGravityDirection.y = src->mGravityDirection.y;
    mGravityDirection.z = src->mGravityDirection.z;
    mGravityPointStrength = src->mGravityPointStrength;
    mGravityPoint.x = src->mGravityPoint.x;
    mGravityPoint.y = src->mGravityPoint.y;
    mGravityPoint.z = src->mGravityPoint.z;
    mSunDirection.x = src->mSunDirection.x;
    mSunDirection.y = src->mSunDirection.y;
    mSunDirection.z = src->mSunDirection.z;
    mSunPointStrength = src->mSunPointStrength;
    mSunPoint.x = src->mSunPoint.x;
    mSunPoint.y = src->mSunPoint.y;
    mSunPoint.z = src->mSunPoint.z;
    mShowBoundingBoxes = src->mShowBoundingBoxes;
    mShowSurfaces = src->mShowSurfaces;
    mShowEffects = src->mShowEffects;
    mShowEffectsScale = src->mShowEffectsScale;
    mDisableParticleAlpha = src->mDisableParticleAlpha;
    mDrawParticles = src->mDrawParticles;
    mDrawMeshes = src->mDrawMeshes;
    mDrawModels = src->mDrawModels;
    mDrawDecals = src->mDrawDecals;
    return this;
}

// @ 0x00a70cc0
ParamElem* ParamElem::CopyCtor(const ParamElem* src)
{
    f00 = src->f00;
    f02 = src->f02;
    f04 = src->f04;
    f08 = src->f08;
    f0c = src->f0c;
    f10 = src->f10;
    m14.Assign(&src->m14);
    mp38 = src->mp38;
    if (mp38 != 0)
        mp38->AddRefI();
    f3c = src->f3c;
    f40 = src->f40;
    f44 = src->f44;
    {
        int count = (int)(src->vec.mpEnd - src->vec.mpBegin);
        vec.CtorGrow(count, &src->f54);
        memmove_nd(vec.mpBegin, src->vec.mpBegin, (char*)src->vec.mpEnd - (char*)src->vec.mpBegin);
        vec.mpEnd = vec.mpBegin + count;
    }
    return this;
}

// @ 0x00a70df0
EffectParams* EffectParams::Clone(const EffectParams* src)
{
    memcpy((char*)this, (const char*)src, 0x64);
    {
        int count = (int)(src->v64.mpEnd - src->v64.mpBegin);
        v64.CtorGrow(count, &src->fill70);
        memmove_nd(v64.mpBegin, src->v64.mpBegin, (char*)src->v64.mpEnd - (char*)src->v64.mpBegin);
        v64.mpEnd = v64.mpBegin + count;
    }
    memcpy((char*)this + 0x78, (const char*)src + 0x78, 0x28);
    {
        int count = (int)(src->va0.mpEnd - src->va0.mpBegin);
        va0.CtorGrow(count, &src->fillac);
        memmove_nd(va0.mpBegin, src->va0.mpBegin, (char*)src->va0.mpEnd - (char*)src->va0.mpBegin);
        va0.mpEnd = va0.mpBegin + count;
    }
    ehvec_ctor((char*)this + 0xb4, (char*)src + 0xb4, 4, 9, (void*)&arrElemCopy);
    return this;
}
