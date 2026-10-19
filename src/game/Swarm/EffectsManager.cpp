// src/game/Swarm/EffectsManager.cpp -- migrated from slice(s) s00a6c190 by tools/migrate/rewrite.py
// Object file: Swarm/EffectsManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Swarm/cGlobalParams.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  operator_delete__(void* p);
extern "C" bool  FUN_00a72f70(int x);
extern float gEC;     // 0x016768ec
extern float gF0;     // 0x016768f0
extern float gF4;     // 0x016768f4
extern float gC4;     // 0x016768c4
extern float gC8;     // 0x016768c8
extern float gCC;     // 0x016768cc
extern const char kFXIdentity4[];   // 0x01676930
extern const char kCameraInstr[];   // 0x01676998
extern const float kMilli;          // 0x013f9428 = 0.001f
#include <string.h>
#include <intrin.h>

// ---- items of slice s00a6c190 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  operator_delete__(void* p);
extern "C" bool  FUN_00a72f70(int x);
extern float gEC;     // 0x016768ec
extern float gF0;     // 0x016768f0
extern float gF4;     // 0x016768f4
extern float gC4;     // 0x016768c4
extern float gC8;     // 0x016768c8
extern float gCC;     // 0x016768cc
extern const char kFXIdentity4[];   // 0x01676930
extern const char kCameraInstr[];   // 0x01676998
extern const float kMilli;          // 0x013f9428 = 0.001f
struct ICollBase {
    virtual void r00();
    virtual void r04();
    virtual ICollBase* r08();
    virtual void r0c();
};
struct IComp {
    virtual void q00();
    virtual void q04();
    virtual void q08(int a, int b, int c);
    virtual void q0c();
    virtual void q10();
    virtual void q14(float f, int i);
    virtual void q18(); virtual void q1c(); virtual void q20(); virtual void q24();
    virtual void q28(); virtual void q2c(); virtual void q30(); virtual void q34();
    virtual void q38(); virtual void q3c();
    virtual void q40();
};
struct IColl7 {
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s10(int a, int b, int c, int d);
    virtual void s14(int a, int b, int c);
    virtual void s18();
    virtual long long s1c(int t);
};
struct IDecal {
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09();
    virtual void d28(int a, int b);
    virtual void d2c(int a, int b);
    virtual void d30(int a, int b, int c);
    virtual void d34(int a, int b, int c);
};
struct Matrix44 { char m[0x40]; void Ctor(const void* src); };
struct Matrix33 { char m[0x24]; void Assign(const void* src); };
struct FXParams {
    float f0;
    float f4;
    float f8;
    float fc;
    float f10;
    char  b14;
    char  pad15[3];
    float f18;
    int   i1c;
};
struct cEffectsManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(float a, float b);          // 0x40
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual IColl7* v21(int t);                  // 0x54

    char _pad04[0x44 - 0x04];
    ICollBase* m44;                              // 0x44
    ICollBase* m48;                              // 0x48
    int   m4c;                                   // 0x4c
    float m50;                                   // 0x50
    int   m54;                                   // 0x54
    float m58;                                   // 0x58
    float m5c;                                   // 0x5c
    float m60;                                   // 0x60
    float m64;                                   // 0x64
    unsigned m68;                                // 0x68
    char _pad6c[0xd0 - 0x6c];
    float md0;                                   // 0xd0
    float md4;                                   // 0xd4
    char _padD8[0x1f0 - 0xd8];
    void* m1f0;                                  // 0x1f0
    ICollBase* m1f4[20];                         // 0x1f4
    IComp* m244;                                 // 0x244

    void  DoUpdate(unsigned a, unsigned b);      // 0x00a6c8f0
    void  SetFlag(int index, char value);        // 0x00a6c940
    bool  GetFlag(int index);                    // 0x00a6c970
    void  SetParams(const FXParams* p);          // 0x00a6c9b0
    void  SetResources(ICollBase* p);            // 0x00a6ca10
    void  SetComponent(ICollBase* p, int type); // 0x00a6ca90
    void* GetComponent(int type);                // 0x00a6cb10
    void  Comp8(int a, int b, int c);            // 0x00a6cb30
    void  Comp14(float f, int i);                // 0x00a6cb70
    void  ResetState();                          // 0x00a6cba0
    void  SetComponent244(IComp* p);             // 0x00a6cbc0
    void* LookupA(int a, int idx, int type);     // 0x00a6cc20
    void* LookupB(int a, int idx, int type);     // 0x00a6cc50
    void  Decal30(int a, int b, int c);          // 0x00a6cc80
    void  Decal28(int a, int b);                 // 0x00a6cca0
    void  Coll10(int a, int b, int c, int d);    // 0x00a6ccc0
    void  Decal34(int a, int b, int c);          // 0x00a6cd10
    void  Decal2c(int a, int b);                 // 0x00a6cd30
    void  Coll14(int a, int b, int c);           // 0x00a6cd50
    long long GetS1c(int t);                     // 0x00a6cd70
};
struct cGlobalParams {
    float mParticleDensity;          // 0x00
    float mParticleScale;            // 0x04
    int   mParticleMultThreshold;    // 0x08
    float mMaxParticleSize;          // 0x0c
    int   mMaxParticles;             // 0x10
    int   mMaxEffects;               // 0x14
    int   mMaxDistributeSamples;     // 0x18
    Matrix44 mProjectionMatrix;      // 0x1c
    Matrix33 mCameraOrientation;     // 0x5c
    float mCameraTranslation[3];     // 0x80
    float mLODPosition[3];           // 0x8c
    float mCursorRayPoint[3];        // 0x98
    float mCursorRayDirection[3];    // 0xa4
    char  mCursorRayAvailable;       // 0xb0
    char  _padB1[3];
    int   mButtonFlags;              // 0xb4
    int   mButtonChangedFlags;       // 0xb8
    float mWindDirection[3];         // 0xbc
    float mWindPointStrength;        // 0xc8
    float mWindPoint[3];             // 0xcc
    float mGravityDirection[3];      // 0xd8
    float mGravityPointStrength;     // 0xe4
    float mGravityPoint[3];          // 0xe8
    float mSunDirection[3];          // 0xf4
    float mSunPointStrength;         // 0x100
    float mSunPoint[3];              // 0x104
    char  mShowBoundingBoxes;        // 0x110
    char  mShowSurfaces;             // 0x111
    char  mShowEffects;              // 0x112
    char  _pad113;
    float mShowEffectsScale;         // 0x114
    char  mDisableParticleAlpha;     // 0x118
    char  mDrawParticles;            // 0x119
    char  mDrawMeshes;               // 0x11a
    char  mDrawModels;               // 0x11b
    char  mDrawDecals;               // 0x11c

    cGlobalParams();
};
struct GmeRefCount {
    int ScalarDeletingDestructor(unsigned flags);
};
// ---- items of slice s00a6c190 end

// @ 0x00a6c8f0
void cEffectsManager::DoUpdate(unsigned a, unsigned b)
{
    v16((float)a * kMilli, (float)b * kMilli);
}

// @ 0x00a6c940
void cEffectsManager::SetFlag(int index, char value)
{
    if (index < 0x20) {
        unsigned mask = 1u << index;
        if (value)
            m68 |= mask;
        else
            m68 &= ~mask;
    }
}

// @ 0x00a6c970
bool cEffectsManager::GetFlag(int index)
{
    if (index < 0x20)
        return (m68 & (1u << index)) != 0;
    return false;
}

// @ 0x00a6c9b0
void cEffectsManager::SetParams(const FXParams* p)
{
    m58 = p->f0;
    m5c = p->f8;
    md4 = p->f4;
    m60 = p->fc;
    m64 = p->f10;
    m4c = (p->b14 == 0);
    m50 = p->f18;
    m54 = p->i1c;
}

// @ 0x00a6ca10
void cEffectsManager::SetResources(ICollBase* p)
{
    ICollBase* c6 = m44;
    if (p != c6) {
        if (p)
            p->r00();
        m44 = p;
        if (c6)
            c6->r04();
    }
    if (p != 0) {
        ICollBase* q = p->r08();
        ICollBase* c7 = m48;
        if (q != c7) {
            if (q)
                q->r00();
            m48 = q;
            if (c7)
                c7->r04();
        }
    }
    else {
        ICollBase* c7 = m48;
        if (c7) {
            m48 = 0;
            c7->r04();
        }
    }
}

// @ 0x00a6ca90
void cEffectsManager::SetComponent(ICollBase* p, int type)
{
    if (type >= 0) {
        ICollBase* old = m1f4[type];
        if (p != old) {
            if (p)
                p->r08();
            m1f4[type] = p;
            if (old)
                old->r0c();
        }
    }
    else {
        ICollBase* old = (ICollBase*)m1f0;
        if (p != old) {
            if (p)
                p->r08();
            m1f0 = p;
            if (old)
                old->r0c();
        }
    }
}

// @ 0x00a6cb10
void* cEffectsManager::GetComponent(int type)
{
    if (type >= 0) {
        void* r = m1f4[type];
        if (r)
            return r;
    }
    return m1f0;
}

// @ 0x00a6cb30
void cEffectsManager::Comp8(int a, int b, int c)
{
    m244->q08(a, b, c);
    _ReadWriteBarrier();
}

// @ 0x00a6cb70
void cEffectsManager::Comp14(float f, int i)
{
    m244->q14(f, i);
}

// @ 0x00a6cba0
void cEffectsManager::ResetState()
{
    md0 = m58;
    m244->q40();
}

// @ 0x00a6cbc0
void cEffectsManager::SetComponent244(IComp* p)
{
    IComp* old;
    if (p != 0) {
        old = m244;
        if (p == old)
            return;
    }
    else {
        p = (IComp*)v21(0);
        old = m244;
        if (p == old)
            return;
        if (p == 0)
            goto done;
    }
    p->q00();
done:
    m244 = p;
    if (old)
        old->q04();
}

// @ 0x00a6cc20
void* cEffectsManager::LookupA(int a, int idx, int type)
{
    int* table = *(int**)((char*)this + 0x2c);
    int  obj = *(int*)((char*)table + type * 4);
    int  arr = *(int*)((char*)obj + 0xc);
    int* e = (int*)(arr + a * 0x14);
    if (e[0] == e[1])
        return 0;
    return *(void**)(e[0] + idx * 4);
}

// @ 0x00a6cc50
void* cEffectsManager::LookupB(int a, int idx, int type)
{
    int* table = *(int**)((char*)this + 0x2c);
    int  obj = *(int*)((char*)table + type * 4);
    int  arr = *(int*)((char*)obj + 0x20);
    int* e = (int*)(arr + a * 0x14);
    if (e[0] == e[1])
        return 0;
    return *(void**)(e[0] + idx * 4);
}

// @ 0x00a6cc80
void cEffectsManager::Decal30(int a, int b, int c)
{
    ((IDecal*)m44)->d30(a, b, c);
    _ReadWriteBarrier();
}

// @ 0x00a6cca0
void cEffectsManager::Decal28(int a, int b)
{
    ((IDecal*)m44)->d28(a, b);
    _ReadWriteBarrier();
}

// @ 0x00a6ccc0
void cEffectsManager::Coll10(int a, int b, int c, int d)
{
    IColl7* p = (IColl7*)m48;
    if (p) {
        p->s10(a, b, c, d);
        _ReadWriteBarrier();
    }
}

// @ 0x00a6cd10
void cEffectsManager::Decal34(int a, int b, int c)
{
    ((IDecal*)m44)->d34(a, b, c);
    _ReadWriteBarrier();
}

// @ 0x00a6cd30
void cEffectsManager::Decal2c(int a, int b)
{
    ((IDecal*)m44)->d2c(a, b);
    _ReadWriteBarrier();
}

// @ 0x00a6cd50
void cEffectsManager::Coll14(int a, int b, int c)
{
    IColl7* p = (IColl7*)m48;
    if (p) {
        p->s14(a, b, c);
        _ReadWriteBarrier();
    }
}

// @ 0x00a6cd70
long long cEffectsManager::GetS1c(int t)
{
    IColl7* p = (IColl7*)m48;
    if (p)
        return p->s1c(t);
    return 0xFFFFFFFFFFFFFFFFull;
}

// @ 0x00a6cd90
bool __stdcall RangeNotEmpty(void* p)
{
    int a = *(int*)((char*)p + 0x10);
    if (a != *(int*)((char*)p + 0x14))
        return FUN_00a72f70(a);
    return false;
}

// @ 0x00a6cdb0
cGlobalParams::cGlobalParams()
{
    mParticleDensity = 1.0f;
    mParticleScale = 1.0f;
    mParticleMultThreshold = 0x14;
    mMaxParticleSize = 1000.0f;
    mMaxParticles = 0;
    mMaxEffects = 0;
    mMaxDistributeSamples = 0;
    mProjectionMatrix.Ctor(&kFXIdentity4);
    mCameraOrientation.Assign(&kCameraInstr);
    mCameraTranslation[0] = 0.0f;
    mCameraTranslation[1] = 0.0f;
    mCameraTranslation[2] = 0.0f;
    mLODPosition[0] = 0.0f;
    mLODPosition[1] = 0.0f;
    mLODPosition[2] = 0.0f;
    mCursorRayPoint[0] = 0.0f;
    mCursorRayPoint[1] = 0.0f;
    mCursorRayPoint[2] = 0.0f;
    mCursorRayDirection[0] = 0.0f;
    mCursorRayDirection[1] = 0.0f;
    mCursorRayDirection[2] = 1.0f;
    mCursorRayAvailable = 0;
    mButtonFlags = 0;
    mButtonChangedFlags = 0;
    mWindDirection[0] = gEC;
    mWindDirection[1] = gF0;
    mWindDirection[2] = gF4;
    mWindPointStrength = 0.0f;
    mWindPoint[0] = gEC;
    mWindPoint[1] = gF0;
    mWindPoint[2] = gF4;
    mGravityDirection[0] = 0.0f;
    mGravityDirection[1] = 0.0f;
    mGravityDirection[2] = -1.0f;
    mGravityPointStrength = 0.0f;
    mGravityPoint[0] = gEC;
    mGravityPoint[1] = gF0;
    mGravityPoint[2] = gF4;
    mSunDirection[0] = gC4;
    mSunDirection[1] = gC8;
    mSunDirection[2] = gCC;
    mSunPointStrength = 0.0f;
    mSunPoint[0] = gC4;
    mSunPoint[1] = gC8;
    mSunPoint[2] = gCC;
    mShowBoundingBoxes = 0;
    mShowSurfaces = 0;
    mShowEffects = 0;
    mShowEffectsScale = 0.1f;
    mDisableParticleAlpha = 0;
    mDrawParticles = 1;
    mDrawMeshes = 1;
    mDrawModels = 1;
    mDrawDecals = 1;
}

// @ 0x00a6d000
int GmeRefCount::ScalarDeletingDestructor(unsigned flags)
{
    *(void**)((char*)this + 4) = (void*)0x013ef094;
    if (flags & 1)
        operator_delete__(this);
    return (int)this;
}
