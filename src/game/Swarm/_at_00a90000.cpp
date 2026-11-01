// src/game/Swarm/_at_00a90000.cpp -- migrated from slice(s) s00a9ef80, s00a9ddd0, s00a9dc00, s00a9ce00, s00a9bf20, s00a9a630, s00a99640, s00a987c0, s00a978d0, s00a95d30, s00a954b0, s00a94b90, s00a93cf0, s00a92d90 by tools/migrate/rewrite.py
// Object file: Swarm/_at_00a90000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Swarm/cIEffectsWorld.h"
#include "EA/Swarm/cIVisualEffect.h"
#include <math.h>
#include <xmmintrin.h>
#include <stdlib.h>
#include <intrin.h>
#include "EA/ArgScript/cArguments.h"
#include <string.h>
#include "EA/Swarm/cTransform.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  __cdecl operator_delete(void* p);                                       // 0x00f47380
extern float g16786dc, g16786e0, g16786e4;         // 0x016786dc/e0/e4 colour bases

// ---- items of slice s00a92d90 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint32_t u32;
typedef uint8_t  u8;
typedef uint16_t u16;
struct Vector3 { float x, y, z; };
struct FloatVec  { float*    mpBegin; float*    mpEnd; float*    mpCapacity; u32 mAlloc[2]; };
struct Vec3Vec   { Vector3*  mpBegin; Vector3*  mpEnd; Vector3*  mpCapacity; u32 mAlloc[2]; };
extern "C" void  __cdecl operator_delete(void* p);                                       // 0x00f47380
extern float g16786dc, g16786e0, g16786e4;         // 0x016786dc/e0/e4 colour bases
struct FloatVecGrow : FloatVec {
    void Grow(float* at, const float& value);        // 0x00455660
};
struct Vec3VecGrow  : Vec3Vec  {
    void Grow(Vector3* at, const Vector3& value);    // 0x007ed1b0
};
static inline void PushBackFloat(FloatVec& v, float value) {
    float* at = v.mpEnd;
    if (at < v.mpCapacity) {
        v.mpEnd = at + 1;
        if (at)
            *at = value;
    } else {
        ((FloatVecGrow*)&v)->Grow(at, value);
    }
}
static inline void PushBackVec3(Vec3Vec& v, const Vector3& value) {
    Vector3* at = v.mpEnd;
    if (at < v.mpCapacity) {
        v.mpEnd = at + 1;
        if (at)
            *at = value;
    } else {
        ((Vec3VecGrow*)&v)->Grow(at, value);
    }
}
struct AllocHeader { int mOwnsBlock; };
static inline void FreeVecBuffer(void* p) {
    if (p && ((AllocHeader*)p)[-1].mOwnsBlock != 0)
        operator_delete(p);
}
struct MeshStreamerTable {
    void* mpRegister;                                 // +0x00
    void* mpPad04;                                    // +0x04
    void* mpCreate;                                   // +0x08
    void* mpField0c;                                  // +0x0c
    void* mpPad10;                                    // +0x10
    void* mpField14;                                  // +0x14
    int   mField18;                                   // +0x18
    int   mField1c;                                   // +0x1c
};
extern MeshStreamerTable gMeshStreamerTable;          // 0x01676050
struct cMetaParticlesEffect {
    void*   mpVtbl;                                   // +0x00
    int     mField04;                                 // +0x04
    int     mField08;                                 // +0x08
    float   mField0c;                                 // +0x0c
    float   mField10;                                 // +0x10
    float   mField14;                                 // +0x14
    float   mScales18[4];                             // +0x18
    float   mField28;                                 // +0x28
    float   mField2c;                                 // +0x2c
    float   mField30;                                 // +0x30
    float   mField34;                                 // +0x34
    float   mField38;                                 // +0x38
    float   mField3c;                                 // +0x3c
    float   mField40;                                 // +0x40
    float   mField44;                                 // +0x44
    float   mField48;                                 // +0x48
    float   mField4c;                                 // +0x4c
    float   mField50;                                 // +0x50
    float   mField54;                                 // +0x54
    float   mField58;                                 // +0x58
    float   mField5c;                                 // +0x5c
    FloatVec mVec60;                                  // +0x60
    float   mField74;                                 // +0x74
    u16     mField78;                                 // +0x78
    u16     mPad7a;
    float   mField7c;                                 // +0x7c
    FloatVec mVec80;                                  // +0x80
    Vec3Vec mVec94;                                   // +0x94
    FloatVec mVecA8;                                  // +0xa8
    int     mPadBc;                                   // +0xbc
    int     mFieldC0;                                 // +0xc0
    int     mFieldC4;                                 // +0xc4
    u8      mFieldC8;                                 // +0xc8
    u8      mFieldC9;                                 // +0xc9
    u8      mFieldCa;                                 // +0xca
    u8      mFieldCb;                                 // +0xcb
    u16     mFieldCc;                                 // +0xcc
    u16     mPadCe;
    float   mFieldD0;                                 // +0xd0
    int     mFieldD4;                                 // +0xd4
    int     mFieldD8;                                 // +0xd8
    int     mFieldDc;                                 // +0xdc
    u8      mFieldE0;                                 // +0xe0
    u8      mPadE1[3];
    float   mFieldE4;                                 // +0xe4
    float   mFieldE8;                                 // +0xe8
    float   mFieldEc;                                 // +0xec
    float   mFieldF0;                                 // +0xf0
    float   mFieldF4;                                 // +0xf4
    float   mFieldF8;                                 // +0xf8
    float   mFieldFc;                                 // +0xfc
    float   mField100;                                // +0x100
    float   mField104;                                // +0x104
    float   mField108;                                // +0x108

    ~cMetaParticlesEffect();
    cMetaParticlesEffect();
};
struct cSampleRange {
    Vector3 mMin;                                     // +0x00
    Vector3 mMax;                                     // +0x0c

    void Erase(const Vector3& v);
};
float gFltMax = 3.4028234663852886e+38f;              // "unset" sample-range sentinel (.rdata)
// ---- items of slice s00a92d90 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern MeshStreamerTable gMeshStreamerTable;          // 0x01676050

// ---- items of slice s00a93cf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_167889c;
extern float g_16788a0;
extern float g_16788a4;
extern float g_1678860;
extern float g_1678864;
extern float g_1485720;
extern float g_1565198;                                        // 3.4e38 marker
extern float g_13f11c8;                                        // tiny epsilon
#pragma pack(push, 4)
#pragma pack(pop)
typedef unsigned char u8_s00a9_3cf0;
typedef unsigned short u16_s00a9_3cf0;
typedef unsigned int   u32_s00a9_3cf0;
typedef signed   int   i32;
typedef unsigned long long u64;
struct CAbil;
struct IoObj;
void __cdecl FUN_0093a780(void* io, void* dst, int a, int b);   // 0x0093a780 ret-c
void __cdecl FUN_0093a700(void* io, void* dst, int a, int b);   // 0x0093a700 ret-c
void __cdecl FUN_0093a6c0(void* io, void* dst, int a);          // 0x0093a6c0 ret-c
void __cdecl FUN_007d27d0(void* io, void* dst);                 // 0x007d27d0 ret-c
void __cdecl FUN_007ed920(void* io, void* dst);                 // 0x007ed920 ret-c
void __cdecl FUN_00a85b00(void* io, void* dst);                 // 0x00a85b00 ret-c
void __cdecl FUN_00a6c7a0(void* a, int b, void* c, void* d, void* e); // 0x00a6c7a0 ret-c
float __cdecl FUN_007cdb90(void* a);                            // 0x007cdb90 float10 ret-c
void  __cdecl FUN_00f47380(void* p);                            // 0x00f47380 operator delete
struct IntrusiveList {
    void FUN_00620230();                                        // 0x00620230
};
struct MatCtor { void FUN_0041cb40(void* src); };
struct TransformOps { void* FUN_00537dc0(void* src); };
struct IoObj {
    void FUN_0041cb00();                                        // vtable +0x00 placeholder
    void FUN_0041cb00b();                                       // vtable +0x04 placeholder
    void FUN_0041cb00c();                                       // vtable +0x08 placeholder
    void FUN_0041cb00d();                                       // vtable +0x0c placeholder
    void FUN_0041cb00e();                                       // vtable +0x10 placeholder
    void FUN_0041cb00f();                                       // vtable +0x14 placeholder
    void FUN_0041cb00g();                                       // vtable +0x18 placeholder
    void FUN_0041cb00h();                                       // vtable +0x1c placeholder
    void FUN_0041cb00i();                                       // vtable +0x20 placeholder
    void FUN_0041cb00j();                                       // vtable +0x24 placeholder
    void FUN_0041cb00k();                                       // vtable +0x28 placeholder
    void FUN_0041cb00l();                                       // vtable +0x2c placeholder
    void FUN_00a93d30(void* dst, int size);                     // vtable +0x30 read raw (ret 8)
};
typedef void (__cdecl* AbilityHook)(void* self, void* arg, void* out);
#define VS(obj, off) (*(void**)(*(char**)(obj) + (off)))
extern u32_s00a9_3cf0   g_1678948;
extern u32_s00a9_3cf0   g_1454410[2];                                     // -1.0 double
extern AbilityHook g_16787b0[8];                               // per-state hook table
struct CAbil {
    void*  vt0;                                                // +0x00
    void*  vt1;                                                // +0x04
    void*  vt2;                                                // +0x08
    u8_s00a9_3cf0     m0c;                                                // +0x0c
    u8_s00a9_3cf0     m0d;                                                // +0x0d
    u8_s00a9_3cf0     m0e;                                                // +0x0e
    char   pad0f[0x10 - 0x0f];
    u8_s00a9_3cf0     m10;                                                // +0x10
    u8_s00a9_3cf0     m11;                                                // +0x11
    u8_s00a9_3cf0     m12;                                                // +0x12
    char   pad13[0x14 - 0x13];
    void*  m14;                                                // +0x14 (intrusive list head)
    void*  m18;                                                // +0x18
    void*  m1c;                                                // +0x1c ability descriptor
    void*  m20;                                                // +0x20 owner component
    void*  m24;                                                // +0x24
    void*  m28;                                                // +0x28
    float  m2c;                                                // +0x2c  (pair-zeroed with m30)
    float  m30;                                                // +0x30
    u8_s00a9_3cf0     m34;                                                // +0x34
    char   pad35[0x38 - 0x35];
    u8_s00a9_3cf0     m38;                                                // +0x38
    char   pad39[0x3c - 0x39];
    float  m3c;                                                // +0x3c  (pair-zeroed with m40)
    float  m40;                                                // +0x40
    void*  m44;                                                // +0x44
    void*  m48;                                                // +0x48
    u32_s00a9_3cf0    m4c;                                                // +0x4c
    double m50;                                                // +0x50 (a float at +0x54 aliases its high half)
    float  m58;                                                // +0x58
    float  m5c;                                                // +0x5c
    float  m60;                                                // +0x60
    float  m64;                                                // +0x64
    float  m68;                                                // +0x68
    float  m6c;                                                // +0x6c
    float  m70;                                                // +0x70
    float  m74;                                                // +0x74
    float  m78;                                                // +0x78
    float  m7c;                                                // +0x7c
    float  m80;                                                // +0x80
    float  m84;                                                // +0x84
    float  m88;                                                // +0x88
    float  m8c;                                                // +0x8c
    // cSPTransform at +0x90 (0x38 bytes): vector @+0x90..9c, matrix @+0xa8.
    u8_s00a9_3cf0     m90_0;                                              // +0x90 flags
    char   pad91[0x94 - 0x91];
    float  m94;                                                // +0x94
    float  m98;                                                // +0x98
    float  m9c;                                                // +0x9c
    float  ma0;                                                // +0xa0
    float  ma4;                                                // +0xa4
    u64    ma8;                                                // +0xa8 matrix (0x30)
    u64    mb0;
    u64    mb8;
    u64    mc0;
    // cSPTransform at +0xc8 (0x38 bytes)
    u8_s00a9_3cf0     mc8_0;                                              // +0xc8 flags
    char   padc9[0xcc - 0xc9];
    float  mcc;                                                // +0xcc
    float  md0;                                                // +0xd0
    float  md4;                                                // +0xd4
    float  md8;                                                // +0xd8
    float  mdc;                                                // +0xdc
    u64    me0;                                                // +0xe0 matrix (0x30)
    u64    me8;
    u64    mf0;
    u64    mf8;
    float  m100;                                               // +0x100
    float  m104;                                               // +0x104
    float  m108;                                               // +0x108
    float  m10c;                                               // +0x10c
    u16_s00a9_3cf0    m110;                                               // +0x110
    u16_s00a9_3cf0    m112;                                               // +0x112
    float  m114;                                               // +0x114
    float  m118;                                               // +0x118
    float  m11c;                                               // +0x11c
    float  m120;                                               // +0x120
    float  m124;                                               // +0x124
    float  m128;                                               // +0x128
    float  m12c;                                               // +0x12c
    float  m130;                                               // +0x130
    float  m134;                                               // +0x134
    float  m138;                                               // +0x138
    float  m13c;                                               // +0x13c
    float  m140;                                               // +0x140
    float  m144;                                               // +0x144
    float  m148;                                               // +0x148
    float  m14c;                                               // +0x14c
    float  m150;                                               // +0x150
    float  m154;                                               // +0x154
    float  m158;                                               // +0x158
    float  m15c;                                               // +0x15c
    float  m160;                                               // +0x160
    float  m164;                                               // +0x164
    float  m168;                                               // +0x168
    float  m16c;                                               // +0x16c
    float  m170;                                               // +0x170
    float  m174;                                               // +0x174
    float  m178;                                               // +0x178
    i32    m17c;                                               // +0x17c lo word of the 64-bit key
    i32    m180;                                               // +0x180 hi word of the 64-bit key
    i32    m184;                                               // +0x184 handle; -1 == none
    u8_s00a9_3cf0     m188;                                               // +0x188
    char   pad189[0x18c - 0x189];
    u8_s00a9_3cf0     m18c;                                               // +0x18c
    char   pad18d[0x190 - 0x18d];
    u8_s00a9_3cf0     m190;                                               // +0x190

    // ---- members -------------------------------------------------------
    void  FUN_00a93cf0(IoObj* io, void* mgr, CAbil* obj);      // 0x00a93cf0
    void  FUN_00a93ea0();                                      // 0x00a93ea0
    int   FUN_00a93ee0(int id, int* a, int count);             // 0x00a93ee0
    void  FUN_00a94030(char v);                                // 0x00a94030
    void  FUN_00a940a0(void* p);                               // 0x00a940a0
    void  FUN_00a94130(int p);                                 // 0x00a94130
    int   FUN_00a94220(int id, int* src, int n);               // 0x00a94220
    int   __declspec(noinline) FUN_00a943a0();                 // 0x00a943a0
    CAbil* FUN_00a94470(void* owner);                          // 0x00a94470
    CAbil* FUN_00a947b0(u8_s00a9_3cf0 freeIt);                            // 0x00a947b0
    void  FUN_00a94800(void* owner, void* mgr);                // 0x00a94800
    void  FUN_00a94940(void* t0, void* t1);                    // 0x00a94940
    void  FUN_00a94b70(void* desc);                            // 0x00a94b70
};
struct GmeRefCount   { virtual void r0(); };
struct GmeIComponent { virtual void c0(); virtual void c1(); };
// ---- items of slice s00a93cf0 end

// ---- items of slice s00a94b90 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8_s00a9_4b90;
typedef unsigned short u16_s00a9_4b90;
typedef unsigned int u32_s00a9_4b90;
struct Matrix33 {
    float m[3][3];
};
template <class T>
struct sp_vector {
    T* mpBegin;      // +0x00
    T* mpEnd;        // +0x04
    T* mpCapacity;   // +0x08
    int mAllocator;  // +0x0c
    int mPad;        // +0x10
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct cParticle {
    cParticle* mpNext;     // +0x00
    cParticle* mpPrev;     // +0x04
    float mAge;            // +0x08
    float mLife;           // +0x0c
    Vector3 mPosition;     // +0x10
    Vector3 mVelocity;     // +0x1c
    u16_s00a9_4b90 mStreamIndex;      // +0x28
    u16_s00a9_4b90 mFlags;            // +0x2a
};
struct cSPTransform_s00a9_4b90 {          // 0x38 bytes
    u8_s00a9_4b90 mFlags;                 // +0x00
    u8_s00a9_4b90 mFlagsHi;               // +0x01
    u16_s00a9_4b90 mModCount;             // +0x02
    Vector3 mTranslation;      // +0x04
    float mScale;              // +0x10
    Matrix33 mRotation;        // +0x14
};
struct cCurves {               // the descriptor part both writers sample
    char pad00[0x80];
    sp_vector<float> mSizeCurve;      // +0x80
    sp_vector<Vector3> mColorCurve;   // +0x94
    sp_vector<float> mAlphaCurve;     // +0xa8
};
struct cVectorRange {
    Vector3 mMin;   // +0x00
    Vector3 mMax;   // +0x0c
};
struct cRandomGlobal {
    double RandomDouble();                   // 0x009360d0
};
extern cRandomGlobal gRandomGlobal;          // 0x016778dc
Vector3 RandomVector3(const cVectorRange* range);   // 0x007cdbe0 (struct return by value)
static __forceinline Vector3 Rotate(const Vector3& v, const Matrix33& m);
struct cEffectSpawner;
struct cSpawnerDesc {
    char pad00[0x0c];
    float mLifeMin;          // +0x0c
    float mLifeMax;          // +0x10
    char pad14[0x14];
    cVectorRange mVelocityRange;   // +0x28
    float mSpeedMin;         // +0x40
    float mSpeedMax;         // +0x44
    char pad48[0xb0];
    float mAttractRadius;    // +0xf8
    Vector3 mAttractCenter;  // +0xfc
};
struct cEffectSpawner {
    char pad00[0x14];
    cParticle* mpParticlesFirst;   // +0x14
    char pad18[0x04];
    int mParticleCount;            // +0x1c
    cSpawnerDesc* mpDesc;          // +0x20
    char pad24[0x70];
    cSPTransform_s00a9_4b90 mTransform;       // +0x94
    char padCC[0x60];
    float mSpeedScale;             // +0x12c
    char pad130[0x04];
    float mLifeScale;              // +0x134
    char pad138[0x2c];
    cVectorRange mSpawnRange;      // +0x164
    u16_s00a9_4b90 mStreamCounter;            // +0x17c

    void ResetParticle(cParticle* particle);
};
struct cITextureParticleRenderer {
    virtual int GetBuffer(int want, char** base, int* stride) = 0;   // slot 0
    virtual void GetVertexAndIndexBuffer() = 0;                      // slot 1
    virtual void ReleaseAndDrawBuffer() = 0;                         // slot 2
};
struct cParticlesEffect {
    char pad00[0x14];
    cParticle* mpParticlesFirst;   // +0x14
    cParticle* mpParticlesLast;    // +0x18
    int mParticleCount;            // +0x1c
    cCurves* mpDesc;               // +0x20
    char pad24[0xcc - 0x24];
    cSPTransform_s00a9_4b90 mTransform;       // +0xcc
    char pad104[0x150 - 0x104];
    float mSizeScale;              // +0x150
    float mAlphaScale;             // +0x154
    Vector3 mColorScale;           // +0x158
};
static __forceinline Vector3 Rotate(const Vector3& v, const Matrix33& m)
{
    Vector3 r;
    r.x = m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[0][0] * v.x;
    r.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z;
    r.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z;
    return r;
}
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
static __forceinline Vector3 SampleCurve(const Vector3* curve, unsigned int last, float t)
{
    if (last == 0)
        return curve[0];
    float f = (float)last * t;
    int i = (int)f;
    float frac = f - (float)i;
    const Vector3& a = curve[i];
    if (frac > 0.0f) {
        const Vector3& b = curve[i + 1];
        Vector3 r;
        r.x = a.x + (b.x - a.x) * frac;
        r.y = a.y + (b.y - a.y) * frac;
        r.z = a.z + (b.z - a.z) * frac;
        return r;
    }
    return a;
}
static const float k255 = 255.0f;
static __forceinline u32_s00a9_4b90 ToByte(float x)
{
    __m128 v = _mm_max_ss(_mm_setzero_ps(), _mm_load_ss(&x));
    v = _mm_mul_ss(v, _mm_load_ss(&k255));
    v = _mm_min_ss(v, _mm_load_ss(&k255));
    return (u8_s00a9_4b90)_mm_cvtss_si32(v);
}
// ---- items of slice s00a94b90 end

// ---- items of slice s00a954b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8_s00a9_54b0;
typedef unsigned short u16_s00a9_54b0;
typedef unsigned int   u32_s00a9_54b0;
struct Vector2 { float x, y; };
struct Vector4 { float x, y, z, w; };
template <typename T>
struct SPVector {
    T*  mpBegin;
    T*  mpEnd;
    T*  mpCapacity;
    u32_s00a9_54b0 mAllocator[2];
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct cParticle_s00a9_54b0 {
    cParticle_s00a9_54b0* mpNext;      // +0x00
    cParticle_s00a9_54b0* mpPrev;      // +0x04
    float      mAge;        // +0x08
    float      mLife;       // +0x0c
    Vector3    mPosition;   // +0x10
    Vector3    mVelocity;   // +0x1c
};
struct cParticlesDescription {
    char              pad[0x80];
    SPVector<float>   mSizeCurve;     // +0x80
    SPVector<Vector3> mColorCurve;    // +0x94
    SPVector<float>   mAlphaCurve;    // +0xa8
};
struct cTransform {                   // at effect + 0xcc
    u8_s00a9_54b0        mFlags;                 // +0x00
    u8_s00a9_54b0        mFlagsHi;               // +0x01
    u16_s00a9_54b0       mModificationCount;     // +0x02
    Vector3   mTranslation;           // +0x04
    float     mScale;                 // +0x10
    Matrix33  mRotation;              // +0x14
};
struct cParticlesEffect_s00a9_54b0 {
    char                   pad0[0x14];
    cParticle_s00a9_54b0*             mParticlesFirst;    // +0x14
    cParticle_s00a9_54b0*             mParticlesLast;     // +0x18
    int                    mParticleCount;     // +0x1c
    cParticlesDescription* mDesc;              // +0x20
    char                   pad1[0xcc - 0x24];
    cTransform             mTransform;         // +0xcc
    char                   pad2[0x150 - 0x104];
    float                  mSizeScale;         // +0x150
    float                  mAlphaScale;        // +0x154
    Vector3                mColorScale;        // +0x158
};
class cITextureParticleRenderer_s00a9_54b0 {
public:
    virtual int  GetBuffer(int count, u8_s00a9_54b0** buffer, int* stride) = 0;   // slot 0
    virtual void GetVertexAndIndexBuffer() = 0;                        // slot 1
    virtual void ReleaseAndDrawBuffer() = 0;                           // slot 2
};
static __forceinline u8_s00a9_54b0 ColorToByte(float v)
{
    __m128 m = _mm_max_ss(_mm_setzero_ps(), _mm_load_ss(&v));
    m = _mm_mul_ss(m, _mm_set_ss(255.0f));
    m = _mm_min_ss(m, _mm_set_ss(255.0f));
    return (u8_s00a9_54b0)_mm_cvt_ss2si(m);
}
static __forceinline float SampleCurve_s00a9_54b0(const float* curve, unsigned int last, float t)
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
static __forceinline void SampleCurve_s00a9_54b0(const Vector3* curve, unsigned int last, float t,
                                      float& ox, float& oy, float& oz)
{
    if (last == 0) {
        ox = curve[0].x;
        oy = curve[0].y;
        oz = curve[0].z;
    } else {
        float f = (float)last * t;
        int i = (int)f;
        float frac = f - (float)i;
        const Vector3& a = curve[i];
        if (frac > 0.0f) {
            const Vector3& b = curve[i + 1];
            ox = a.x + (b.x - a.x) * frac;
            oy = a.y + (b.y - a.y) * frac;
            oz = a.z + (b.z - a.z) * frac;
        } else {
            ox = a.x;
            oy = a.y;
            oz = a.z;
        }
    }
}
static __forceinline Vector3 Rotate_s00a9_54b0(const Vector3& v, const Matrix33& m)
{
    Vector3 r;
    r.x = m.m[2][0] * v.z + m.m[1][0] * v.y + m.m[0][0] * v.x;
    r.y = m.m[2][1] * v.z + m.m[1][1] * v.y + m.m[0][1] * v.x;
    r.z = m.m[2][2] * v.z + m.m[1][2] * v.y + m.m[0][2] * v.x;
    return r;
}
// ---- items of slice s00a954b0 end

// ---- items of slice s00a95d30 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_rotr)
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};
struct Vec4 { float x, y, z, w; };
struct FloatCurve {          // eastl::vector<float> (20 bytes in this build)
    float* mpBegin;
    float* mpEnd;
    float* mpCap;
    int mAlloc;
    int pad;
};
struct Vec3Curve {           // eastl::vector<Vec3>
    Vec3* mpBegin;
    Vec3* mpEnd;
    Vec3* mpCap;
    int mAlloc;
    int pad;
};
struct EffectDesc {
    uint32_t pad00[0x20];
    FloatCurve size;         // +0x80
    Vec3Curve color;         // +0x94
    FloatCurve alpha;        // +0xa8
};
struct Particle {
    Particle* next;          // +0x00
    int pad04;
    float age;               // +0x08
    float life;              // +0x0c
    Vec3 a;                  // +0x10
    Vec3 b;                  // +0x1c
    uint16_t uv;             // +0x28
};
struct Mat3 {
    float m[9];
    Vec3 Mul(const Vec3& v) const
    {
        return Vec3((m[6] * v.z + m[3] * v.y) + m[0] * v.x,
                    (m[7] * v.z + m[4] * v.y) + m[1] * v.x,
                    (m[8] * v.z + m[5] * v.y) + m[2] * v.x);
    }
};
struct Effect {
    uint32_t pad00[5];
    Particle* mpParticles;   // +0x14
    uint32_t pad18;
    int mCount;              // +0x1c
    EffectDesc* mpDesc;      // +0x20
    uint32_t pad24[0x2a];
    uint32_t mFlags;         // +0xcc
    float origin[3];         // +0xd0
    float scale;             // +0xdc
    Mat3 mat;                // +0xe0
    uint32_t pad104[0x13];
    float sizeScale;         // +0x150
    float alphaScale;        // +0x154
    float colorScale[3];     // +0x158
};
struct VertexSink {
    virtual int Fetch(int want, char** base, int* stride);   // slot 0
    virtual void pv_1();
    virtual void Flush();                                    // slot 2
};
__forceinline float SampleFloat(const FloatCurve& c, unsigned n, float t)
{
    if (n == 0)
        return c.mpBegin[0];
    float f = (float)n * t;
    int i = (int)f;
    float frac = f - (float)i;
    if (frac > 0.0f) {
        float a = c.mpBegin[i];
        return (c.mpBegin[i + 1] - a) * frac + a;
    }
    return c.mpBegin[i];
}
__forceinline Vec3 SampleVec3(const Vec3Curve& c, unsigned n, float t)
{
    if (n == 0)
        return c.mpBegin[0];
    float f = (float)n * t;
    int i = (int)f;
    float frac = f - (float)i;
    const Vec3* p = c.mpBegin + i;
    if (frac > 0.0f) {
        Vec3 r;
        r.x = p[0].x + (p[1].x - p[0].x) * frac;
        r.y = p[0].y + (p[1].y - p[0].y) * frac;
        r.z = p[0].z + (p[1].z - p[0].z) * frac;
        return r;
    }
    return *p;
}
inline uint32_t ToByte_s00a9_5d30(float x)
{
    __m128 v = _mm_max_ss(_mm_setzero_ps(), _mm_load_ss(&x));
    v = _mm_mul_ss(v, _mm_load_ss(&k255));
    v = _mm_min_ss(v, _mm_load_ss(&k255));
    return (uint8_t)_mm_cvtss_si32(v);
}
inline void WriteVertex(char* v, const uint8_t* off, const Vec4& p, const Vec4& q, uint32_t color, uint32_t uvw)
{
    *(Vec4*)(v + off[0]) = p;
    *(Vec4*)(v + off[1]) = q;
    *(uint32_t*)(v + off[2]) = color;
    *(uint32_t*)(v + off[3]) = uvw;
}
inline void WriteVertexUV(char* v, const uint8_t* off, const Vec3& p, uint32_t color, const float* uv)
{
    *(Vec3*)(v + off[0]) = p;
    *(uint32_t*)(v + off[1]) = color;
    *(uint32_t*)(v + off[2]) = ((const uint32_t*)uv)[0];
    *(uint32_t*)(v + off[2] + 4) = ((const uint32_t*)uv)[1];
}
void* __cdecl AllocMem(unsigned n, const char* name, int a, int b, int c, int d);  // 0xf473a0
void* __cdecl MemZero(void* p, int v, unsigned n);                                 // 0x011e073e
struct SwarmNode {
    SwarmNode* mpNext;       // +0x00
    SwarmNode* mpPrev;       // +0x04
};
struct SwarmEffectBase {
    char pad00[0x14];
    SwarmNode mHead;         // +0x14
    int mnCount;             // +0x1c
    void ClearParticles();
};
struct SwarmEffect {
    char pad00[0x0c];
    uint8_t mbActive;        // +0x0c
    uint8_t mbPaused;        // +0x0d
    char pad0e[0x12];
    void* mpOwner;           // +0x20
    char pad24[0x160];
    int mnOwnerIndex;        // +0x184
    void Release(int bRelease);
};
struct SwarmAlloc {
    int Init(int arg);       // 0x00a94470
};
SwarmNode* gpFreeParticles;  // 0x0167888c
void* gpSwarmVtbl[0x20];     // 0x016787b0
// ---- items of slice s00a95d30 end

// ---- items of slice s00a978d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* EA_IO_ReadInt32(void* stream, void* out, int, int);          // (0x93a780)
extern void* EA_IO_ReadString16(void* stream, void* out);                 // (0x5302b0)
extern void FUN_00a97830();                                               // (0xa97830)
extern void FUN_00a78e90();                                               // (0xa78e90)
extern void FUN_006e95a0();                                               // (0x6e95a0)
extern void  FUN_00a983d0();                                              // (0xa983d0)
extern void* FUN_00a98480(void* stream, int version);                     // (0xa98480)
extern float   g_fBoundsInit;         // (0x1565198) bound-initialisation magnitude
extern float   g_fTeleportThreshold;  // (0x15651a8) squared-distance teleport threshold
extern char vtable_SwarmDesc[];       // (0x1458750)
extern char vtable_IEvent[];          // (0x13ef094) SP::Audio::IEventModifier
extern void* g_1676018;
extern void* g_167601c;
extern int   g_1676028;
extern int   g_167602c;
typedef unsigned int   uint;
typedef unsigned short u16_s00a9_78d0;
typedef unsigned char  u8_s00a9_78d0;
typedef unsigned int   u32_s00a9_78d0;
struct Vector3_t { float x, y, z; };   // 0xc
extern void* operator_new(uint size, const char* name, uint, uint, uint, uint); // (0xf473a0)
extern u16_s00a9_78d0     gEmptyString16[];      // (0x1667bac) eastl empty 16-bit string sentinel
extern u16_s00a9_78d0     gEmptyString16Cap[];   // (0x1667bad)
struct Str16                          // eastl::string16-ish (0xc bytes)
{
	const void* mpBegin;               // +0x00
	const void* mpEnd;                 // +0x04
	u32_s00a9_78d0         mCapacity;             // +0x08
};
struct SwarmNode_s00a9_78d0
{
	SwarmNode_s00a9_78d0* mpNext;                 // +0x00
	SwarmNode_s00a9_78d0* mpPrev;                 // +0x04
	float mf08;                        // +0x08
	float mf0c;                        // +0x0c
	float mf10;                        // +0x10
	float mf14;                        // +0x14
	float mf18;                        // +0x18
	float mf1c;                        // +0x1c
	float mf20;                        // +0x20
	float mf24;                        // +0x24
	float mf28;                        // +0x28
};
extern SwarmNode_s00a9_78d0* g_pNodeFreeList;     // (0x167888c)
struct Desc1c                          // *(this+0x1c): the effect description side
{
	char  pad00[8];                    // +0x00
	u32_s00a9_78d0   mFlags;                      // +0x08
	char  pad0c[8];                    // +0x0c
	float mf14;                        // +0x14
	char  pad18[0x48];                 // +0x18
	float* mp60;                       // +0x60
	char  pad64[0x10];                 // +0x64
	float mf74;                        // +0x74
	char  pad78[0x44];                 // +0x78
	float mfBC;                        // +0xbc
	float mfC0;                        // +0xc0
	float mfC4;                        // +0xc4
	char  padC8[0x1c];                 // +0xc8
	float mfE4;                        // +0xe4
	float mfE8;                        // +0xe8
	float mfEC;                        // +0xec
	float mfF0;                        // +0xf0
	float mfF4;                        // +0xf4
	char  padF8[0x10];                 // +0xf8
	float mf108;                       // +0x108
};
struct Desc24                          // *(this+0x24): the "player"/avatar side
{
	float mf00;                        // +0x00
	char  pad04[4];                    // +0x04
	float mf08;                        // +0x08
	char  pad0c[0xb0];                 // +0x0c
	float mfBC;                        // +0xbc
	float mfC0;                        // +0xc0
	float mfC4;                        // +0xc4
	char  padC8[0x10];                 // +0xc8
	float mfD8;                        // +0xd8
	float mfDC;                        // +0xdc
	float mfE0;                        // +0xe0
};
struct Xform38                         // *(this+0xc8): a transform used by the drawer dispatch
{
	char  pad00[0x10];                 // +0x00
	float mf10;                        // +0x10  (read as *(this+0xd8))
	char  pad14[0x24];                 // +0x14
};
struct UpdateCtx                       // the caller's per-frame stats block (third parameter)
{
	char pad00[0x10];                  // +0x00
	int  mn10;                         // +0x10
	int  mn14;                         // +0x14
};
struct SwarmCtrl
{
	char       pad00[0x0c];            // +0x00
	u8_s00a9_78d0         mb0c;                   // +0x0c
	u8_s00a9_78d0         mb0d;                   // +0x0d
	char       pad0e[2];               // +0x0e
	SwarmNode_s00a9_78d0* mpNext;                 // +0x10  (list sentinel embedded here)
	SwarmNode_s00a9_78d0* mpPrev;                 // +0x14
	int        mn18;                   // +0x18
	Desc1c*    mp1c;                   // +0x1c
	void*      mp20;                   // +0x20
	Desc24*    mp24;                   // +0x24
	char       pad28[4];               // +0x28
	double     mTimeD;                 // +0x2c
	u8_s00a9_78d0         mb34;                   // +0x34
	char       pad35[0x23];            // +0x35
	Vector3_t  mPos;                   // +0x58
	Vector3_t  mBoundsMin;             // +0x68
	Vector3_t  mBoundsMax;             // +0x74
	float      mf80;                   // +0x80
	char       pad84[0x10];            // +0x84
	Vector3_t  mWorld;                 // +0x94
	char       padA0[0x28];            // +0xa0
	Xform38    mXform;                 // +0xc8
	Vector3_t  mLastTeleport;          // +0x100
	u16_s00a9_78d0        mw10c;                  // +0x10c
	u16_s00a9_78d0        mw10e;                  // +0x10e
	float      mf110;                  // +0x110
	float      mf114;                  // +0x114
	float      mf118;                  // +0x118
	float      mf11c;                  // +0x11c
	float      mf120;                  // +0x120
	float      mf124;                  // +0x124
	float      mf12c;                  // +0x12c
	char       pad130[4];              // +0x130
	float      mf134;                  // +0x134
	float      mf138;                  // +0x138
	u32_s00a9_78d0        mn13c;                  // +0x13c
	u32_s00a9_78d0        mn140;                  // +0x140
	u32_s00a9_78d0        mn144;                  // +0x144
	float      mf148;                  // +0x148
	float      mf14c;                  // +0x14c
	float      mf150;                  // +0x150
	u32_s00a9_78d0        mn154;                  // +0x154
	u32_s00a9_78d0        mn158;                  // +0x158
	u32_s00a9_78d0        mn15c;                  // +0x15c
	char       pad160[0x24];           // +0x160
	int        mn184;                  // +0x184

	void Update(float dt, float param3, UpdateCtx* ctx);
};
struct EffectObjA
{
	void* mpVtbl;                      // +0x00
	char  pad04[0x1c];                 // +0x04
	int   mnBegin;                     // +0x20  (managed buffer address)
	char  pad24[4];                    // +0x24
	int   mnEnd;                       // +0x28

	void* Destroy(char freeSelf);
};
struct SwarmDesc                       // the 0x34-byte object built by (0x00a98480)
{
	void*  mpVtbl;                     // +0x00
	u32_s00a9_78d0    mn04;                       // +0x04
	u32_s00a9_78d0    mn08;                       // +0x08
	u32_s00a9_78d0    mn0c;                       // +0x0c
	u32_s00a9_78d0    mn10;                       // +0x10
	u32_s00a9_78d0    mn14;                       // +0x14
	u32_s00a9_78d0    mn18;                       // +0x18
	u32_s00a9_78d0    mn1c;                       // +0x1c
	Str16  mStr;                       // +0x20
	u32_s00a9_78d0    mn2c;                       // +0x2c
	float  mf30;                       // +0x30
};
// ---- items of slice s00a978d0 end

// ---- items of slice s00a987c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char g_str_Swarm[];             // 0x013f1fdc
extern "C" void* EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d);  // 0xf473a0
extern void* g_vtbl_LightEffectSub;  // 0x01458848
extern void Sub_ReadInt32(void* stream, void* out, int a, int b);  // 0x93a780
extern void Sub_ReadInt8(void* stream, void* out, int n);          // 0x93a6c0
extern void Sub_ReadByte(void* stream, void* out, int n, int a);   // 0x93a700
extern void Sub_ReadVec0C(void* stream, void* dst);                // 0x7ed920
extern void Sub_ReadFVec(void* stream, void* dst);                 // 0x7d27d0
extern void __stdcall Elem1C_Write1(void* stream, void* elem);   // 0xa79710
extern void __stdcall Elem1C_Write2(void* stream, void* elem);   // 0xa797a0
extern void __stdcall Elem1C_Dtor(void* first, void* last, void* cap); // 0x6fd250
int  __stdcall EA_IO_WriteUint32(void* stream, const unsigned int* p, unsigned int n, int a); // 0x93aa70
struct Elem1C {
    float w[7];
};
struct Elem1CVec {
    Elem1C* mpBegin;
    Elem1C* mpEnd;
    Elem1C* mpCapacity;
    const char* mpName;
    int mpExtra;
};
struct FVec5 {                       // 5-word eastl::vector<float>
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    const char* mpName;
    int   mpExtra;
    void assign(const FVec5& src);                       // 0x50d4e0
    void reserve(int n, const char* name);               // 0x4aa350
    float* insert_end(float* first, unsigned int n);     // 0x11e0744
};
struct LightEffectSub {
    void* v00;                       // +0x00
    int   n04;                       // +0x04
    int   n08;                       // +0x08
    unsigned char n0c;               // +0x0c
    float f10;                       // +0x10
    short s14;                       // +0x14
    void* v18a;                      // +0x18 (3-float element storage)
    void* v18b;
    void* v18c;
    float f24;                       // +0x24
    float f28;                       // +0x28
    FVec5 v2c;                       // +0x2c
    FVec5 v40;                       // +0x40
    float f54;                       // +0x54

    LightEffectSub() {}
    LightEffectSub& operator=(const LightEffectSub& src);
    LightEffectSub& copy_construct(const LightEffectSub& src);
    void Read(void* stream, int n);
    void Install(char flag);
};
Elem1C* Elem1C_copy_range(Elem1C* dst, Elem1C* first, Elem1C* last);
Elem1C* Elem1C_fill(Elem1C* dst, unsigned int n, const Elem1C* v);
Elem1C* Elem1C_fill_off14(Elem1C* dst, unsigned int n, const Elem1C* v);
void* Elem1C_write_vector(void* stream, Elem1CVec* vec);
void* Elem1C_write_vector2(void* stream, Elem1CVec* vec);
void Elem1C_insert(Elem1CVec* vec, Elem1C* pos, unsigned int n, const Elem1C* v);
extern void __stdcall Elem1C_DtorAndFill(void* dst, void* end, const Elem1C* v); // 0x6fd140
// ---- items of slice s00a987c0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
Elem1C* Elem1C_ctor_range(Elem1C** out, Elem1C* first, Elem1C* last, Elem1C* dst);  // 0x00a99350 (stays in the slice: not this object's)

// ---- items of slice s00a99640 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl eastl_alloc_counted(size_t n);                      // 0x00f473a0
extern "C" void  __cdecl operator_delete_arr(void* p);                       // 0x00f47380 operator delete[]
extern "C" void  __cdecl ClearElements(void* begin, void* end);              // 0x00a87300
inline void* operator new(size_t, void* p) { return p; }
struct Vec3f {
    float x, y, z;
    Vec3f() {}
    Vec3f(const Vec3f& o) { x = o.x; y = o.y; z = o.z; }
};
extern Vec3f g_vec3_01678e1c;     // 0x01678e1c (runtime-initialised constant, copied per word)
extern Vec3f g_vec3_01678dd0;     // 0x01678dd0
struct FloatVec_s00a9_9640 {
    float* mpBegin; float* mpEnd; float* mpCapacity; const char* mpName; int mpExtra;
    void Init() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    void DoInsertValue(float* pos, const float& v);     // 0x00455660 (ret 8)
    void push_back(const float& v)
    {
        if (mpEnd < mpCapacity) { float* p = mpEnd; mpEnd = p + 1; if (p) *p = v; }
        else DoInsertValue(mpEnd, v);
    }
};
struct Vec3Vec_s00a9_9640 {
    Vec3f* mpBegin; Vec3f* mpEnd; Vec3f* mpCapacity; const char* mpName; int mpExtra;
    void Init() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    void DoInsertValue(Vec3f* pos, const Vec3f& v);     // 0x007ed1b0 (ret 8)
    void push_back(const Vec3f& v)
    {
        if (mpEnd < mpCapacity) { Vec3f* p = mpEnd; mpEnd = p + 1; if (p) new (p) Vec3f(v); }
        else DoInsertValue(mpEnd, v);
    }
};
struct SimpleVec {
    void* mpBegin; void* mpEnd; void* mpCap;
    void Init() { mpBegin = 0; mpEnd = 0; mpCap = 0; }
};
struct ClearVec {
    void* mpBegin; void* mpEnd; void* mpCap;
    void Init() { mpBegin = 0; mpEnd = 0; mpCap = 0; }
    void Clear();                                       // 0x00a87300
};
struct cRefBase {
    int   mRefCount;                    // +0x04
    cRefBase() : mRefCount(0) {}
    void SetVtbl(void* v) { *(void**)this = v; }   // set the implicit vptr
};
struct cEffectParams : cRefBase {
    virtual ~cEffectParams();
    int   i08, i0c;
    float f10, f14, f18, f1c, f20, f24, f28, f2c, f30, f34, f38, f3c, f40;
    float f44, f48, f4c, f50, f54, f58, f5c, f60, f64;
    FloatVec_s00a9_9640 v68;                       // +0x68
    float f7c;
    int   i80;
    FloatVec_s00a9_9640 v84;                       // +0x84
    float f98;
    FloatVec_s00a9_9640 v9c;                       // +0x9c
    FloatVec_s00a9_9640 vb0;                       // +0xb0
    FloatVec_s00a9_9640 vc4;                       // +0xc4
    float fd8, fdc, fe0, fe4, fe8, fec;
    Vec3Vec_s00a9_9640 vf0;                        // +0xf0
    Vec3f v104;                         // +0x104
    FloatVec_s00a9_9640 v110;                      // +0x110
    float f124;
    int   i128, i12c, i130;
    char  b134;
    char  pad135[3];
    Vec3f v138, v144;
    float f150, f154, f158;
    Vec3f v15c;
    float f168, f16c;
    SimpleVec v170;                     // +0x170
    char  pad17c[8];
    char  b184, b185, b186, b187;
    SimpleVec v188;                     // +0x188
    char  pad194[8];
    SimpleVec v19c;                     // +0x19c
    char  pad1a8[8];
    ClearVec  v1b0;                     // +0x1b0
    char  pad1bc[8];    float f1c4, f1c8, f1cc, f1d0, f1d4, f1d8, f1dc, f1e0, f1e4;
    int   i1e8, i1ec, i1f0, i1f4, i1f8, i1fc;
    float f200, f204, f208, f20c, f210, f214, f218;
    SimpleVec v21c;                     // +0x21c
    char  pad228[8];
    char  b230;
    char  pad231[3];
    float f234, f238, f23c, f240, f244, f248, f24c;
    SimpleVec v250;                     // +0x250
    char  pad25c[8];
    char  b264;
    char  pad265[3];
    Vec3f v268;
    float f274, f278, f27c;
    Vec3f v280;
    SimpleVec v28c;                     // +0x28c
    char  pad298[8];
    float f2a0, f2a4;
    SimpleVec v2a8;                     // +0x2a8
    char  pad2b4[8];
    float f2bc;

    cEffectParams();
};
struct Rec7 {
    uint32_t w0, w1, w2, w3, w4, w5, w6;    // 0x00..0x18
};
extern "C" Rec7* __cdecl CopyRec7(Rec7* first, Rec7* last, Rec7* out);       // 0x00a78e30
extern "C" void  __cdecl Rec7_ShiftBack(Rec7* first, Rec7* last, Rec7* out); // 0x006fd250
extern "C" void  __cdecl DestroyRangeRec7(Rec7* first, Rec7* last);          // 0x00d73090
extern "C" void  __cdecl FillRec7(Rec7* first, Rec7* last, const Rec7* v);   // 0x006fd140
extern "C" Rec7  __cdecl RotateCopy2(const Rec7* first, const Rec7* last, Rec7* dst); // 0x00a993b0
extern "C" Rec7* __cdecl AllocCopy(Rec7* dst, uint32_t n, const Rec7* v, Rec7* pos); // 0x00a99240
struct RecVec {
    Rec7* mpBegin;      // 0x00
    Rec7* mpEnd;        // 0x04
    Rec7* mpCap;        // 0x08

    uint32_t size() const { return (uint32_t)((char*)mpEnd - (char*)mpBegin) / 0x1c; }
    uint32_t capacity() const { return (uint32_t)((char*)mpCap - (char*)mpBegin) / 0x1c; }

    void    reserve(uint32_t n, const void* tag);            // 0x00a05830
    void    UninitialisedFill(Rec7* out, uint32_t n, const Rec7* v); // 0x00a99410
    Rec7*   AllocCopyN(uint32_t n, const Rec7* first, const Rec7* last); // 0x00a9a250
    Rec7*   AllocMoveN(uint32_t n, const Rec7* first, const Rec7* last); // 0x00a9a2b0

    void    insert(Rec7* pos, uint32_t n, const Rec7& v);   // @ 0x00a99640
    void    resize(uint32_t n);                             // @ 0x00a99a10
    void    resizeZero(uint32_t n);                         // @ 0x00a99a90
    RecVec* reserveFill(const RecVec* src);                 // @ 0x00a9a310
    RecVec* reserveFill2(const RecVec* src);                // @ 0x00a9a370
    RecVec* assign(const RecVec& src);                      // @ 0x00a9a3d0
    RecVec* assignMove(const RecVec& src);                  // @ 0x00a9a500
};
static inline void FreeCounted(void* p) {
    if (p) {
        if (((int*)p)[-1] != 0)
            operator_delete_arr(p);
    }
}
void ClearVec::Clear()
{
    ClearElements(mpBegin, mpEnd);
}
// ---- items of slice s00a99640 end

// ---- items of slice s00a9a630 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl FUN_007cdbe0(void* out, const void* in);             // 0x7cdbe0
extern "C" float DAT_01565424;      // angle scale constant
extern "C" float DAT_01678ffc;      // angle divisor constant
extern "C" float DAT_01678f38;      // wiggle frequency
extern "C" float DAT_01678fe8;      // wiggle wrap scale
extern "C" float DAT_01677840[];    // wiggle table (interleaved pairs)
#pragma intrinsic(sqrt)
#pragma intrinsic(fabs)
typedef unsigned char byte;
struct Vec3_s00a9_a630 {
    float x, y, z;
};
struct cElem {
    float w;        // +0x00
    float m[3];     // +0x04
    float v[3];     // +0x10
};
struct cStream;
extern "C" void __cdecl ReadInt32(cStream* s, void* out, int n, int a4);     // 0x93a780
extern "C" void __cdecl FUN_0093a800(cStream* s, void* out, int n, int a4);  // 0x93a800
extern "C" void __cdecl FUN_00a87f50(cStream* s, void* out);                 // 0xa87f50
extern "C" void __cdecl FUN_00a7b9a0(cStream* s, void* out);                 // 0xa7b9a0
extern "C" void __cdecl FUN_00a7ba10(cStream* s, void* out);                 // 0xa7ba10
extern "C" void __cdecl FUN_00a9a870(cStream* s, void* out);                 // 0xa9a870
extern "C" void __cdecl FUN_00a9a8d0(cStream* s, void* out);                 // 0xa9a8d0
struct cRWState {
    void Update(void* p);       // 0xa790a0
};
extern "C" void __cdecl FUN_00a79430(void* state, const void* key,
                                     const Vec3_s00a9_a630* v, bool flag);              // 0xa79430
namespace EA {
namespace Random {
struct RandomLinearCongruential_s00a9_a630 {
    double RandomDoubleUniform();  // 0x009360d0 (EA::Random::RandomLinearCongruential::RandomDoubleUniform)
};
}
}
extern EA::Random::RandomLinearCongruential_s00a9_a630 g_Random;
struct cTimedState {
    void Advance(float dt);
};
struct cField {
    void*           m_vtbl;         // 0x000
    char            m_pad04[0x0c - 0x04];
    void*           m_0c;           // 0x0c
    char            m_pad10[0x14 - 0x10];
    int             m_14;           // 0x14
    char            m_pad18[0x20 - 0x18];
    byte            m_20;           // 0x20
    byte            m_21;           // 0x21
    char            m_pad22[0xa0 - 0x22];
    double          m_a0;           // 0xa0
    byte            m_a8;           // 0xa8
    char            m_padA9[0xb0 - 0xa9];
    double          m_b0;           // 0xb0
    int             m_b8;           // 0xb8
    char            m_padBC[0xc8 - 0xbc];
    float           m_c8;           // 0xc8
    int             m_cc;           // 0xcc
    int             m_d0;           // 0xd0
    int             m_d4;           // 0xd4
    char            m_d8[0x124 - 0xd8];
    int             m_124;          // 0x124
    int             m_128;          // 0x128
    float           m_12c;          // 0x12c
    char            m_pad130[0x194 - 0x130];
    void*           m_194;          // 0x194
    void*           m_198;          // 0x198
    void*           m_19c;          // 0x19c
    char            m_pad1a0[0x248 - 0x1a0];
    void*           m_248;          // 0x248
    byte            m_24c;          // 0x24c

    void Destroy();
    void Reset(int arg);
    void SetObject(cField* obj);
};
// ---- items of slice s00a9a630 end

// ---- items of slice s00a9bf20 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3_s00a9_bf20 {
    float x, y, z;
    Vec3_s00a9_bf20() {}
    Vec3_s00a9_bf20(const Vec3_s00a9_bf20& v) : x(v.x), y(v.y), z(v.z) {}
};
static inline bool Bit(uint32_t v, int n) { return (v >> n) & 1; }
namespace EA {
namespace Random {
struct RandomLinearCongruential_s00a9_bf20 { double RandomDoubleUniform(); };   // 0x009360d0
}
}
extern EA::Random::RandomLinearCongruential_s00a9_bf20 g_Random_s00a9_bf20;                // 0x016778dc (sRandom_Swarm)
struct Xform {
    uint32_t flags;      // +0x00
    Vec3_s00a9_bf20 t;              // +0x04
    float scale;         // +0x10
    float m[9];          // +0x14
    void Transform(Vec3_s00a9_bf20* v);       // 0x007cdee0
    void InvTransform(Vec3_s00a9_bf20* v);    // 0x007cda70
    void InvDir(Vec3_s00a9_bf20* v);          // 0x00a78e90
    void Dir(Vec3_s00a9_bf20* v);             // 0x00a7ca50
};
struct Sampler {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
    virtual bool Contains(Vec3_s00a9_bf20* p);               // 0x18
    virtual void s7();
    virtual float Height(Vec3_s00a9_bf20* p);                // 0x20
    virtual void Normal(Vec3_s00a9_bf20* out, Vec3_s00a9_bf20* p);      // 0x24
    virtual void Field(Vec3_s00a9_bf20* out, Vec3_s00a9_bf20* p);       // 0x28
};
struct Particle_s00a9_bf20 {
    uint32_t node[2];
    float age;               // +0x08
    float life;              // +0x0c
    Vec3_s00a9_bf20 pos;                // +0x10
    Vec3_s00a9_bf20 vel;                // +0x1c
    uint32_t pad28[(0x50 - 0x28) / 4];
    float spinA;             // +0x50
    float spinB;             // +0x54
    float angle1;            // +0x58
    float angle2;            // +0x5c
};
float FUN_0053c480(const float* a, const float* b);        // 0x0053c480 (dot product)
float FUN_007cdb90(float* range);                          // 0x007cdb90 (random in [range[0],range[1]])
void* FUN_007d5590(void* out, void* a, const void* b);     // 0x007d5590 (copy matrix + update)
void FUN_00a7ab40(int count, const float* data, float scale, void* params, void* extra);  // 0x00a7ab40
struct SwarmDesc_s00a9_bf20 {
    uint32_t pad0[2];
    uint32_t flags;                          // +0x08
    uint32_t pad0c[(0x44 - 0x0c) / 4];
    float m_44;                              // +0x44
};
struct SwarmChild {
    SwarmChild* m_next;                      // +0x00
    uint32_t m_pad04[0x1f - 1];              // +0x04 .. +0x7b
    void* m_processor;                       // +0x7c
};
struct SwarmProcessor {
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
    virtual bool Command(int command, float* data, int count);   // +0x1c
};
struct SwarmParamArray {
    uint32_t m_begin;                        // +0x00
    uint32_t m_end;                          // +0x04
    uint32_t m_capacityAndFlags;             // +0x08
};
static inline void TransformPoint(const Xform& xf, Vec3_s00a9_bf20& v)
{
    if (xf.flags & 2) {
        Vec3_s00a9_bf20 r;
        r.x = (xf.m[3] * v.y + xf.m[6] * v.z) + xf.m[0] * v.x;
        r.y = (xf.m[4] * v.y + xf.m[7] * v.z) + xf.m[1] * v.x;
        r.z = (xf.m[5] * v.y + xf.m[8] * v.z) + xf.m[2] * v.x;
        v = r;
    }
    v.x = xf.scale * v.x + xf.t.x;
    v.y = xf.t.y + xf.scale * v.y;
    v.z = xf.t.z + xf.scale * v.z;
}
class SwarmEmitter {
public:
    uint32_t m_pad00[3];                     // +0x00
    SwarmDesc_s00a9_bf20* m_desc;                       // +0x0c
    uint32_t m_pad10[5];                     // +0x10 .. +0x23
    SwarmChild* m_children;                  // +0x24 (head sentinel's next pointer)
    uint32_t m_pad28[2];                     // +0x28 .. +0x2f
    Xform m_xfA;                             // +0x30
    Xform m_xfB;                             // +0x68
    uint32_t m_padA0[(0x114 - 0xa0) / 4];    // +0xa0 .. +0x113
    Vec3_s00a9_bf20 m_surfacePoint;                     // +0x114
    float m_surfaceSign;                     // +0x120
    uint32_t m_pad124[(0x130 - 0x124) / 4];  // +0x124 .. +0x12f
    Vec3_s00a9_bf20 m_planePoint;                       // +0x130
    float m_param13c;                        // +0x13c
    float m_param140;                        // +0x140
    float m_param144;                        // +0x144
    float m_param148;                        // +0x148
    float m_param14c;                        // +0x14c
    Vec3_s00a9_bf20 m_param150;                         // +0x150
    float m_minHeight;                       // +0x15c
    float m_maxHeight;                       // +0x160
    float m_basis0;                          // +0x164
    float m_basis1;                          // +0x168
    float m_basis2;                          // +0x16c
    float m_basis3;                          // +0x170
    float m_basis4;                          // +0x174
    float m_basis5;                          // +0x178
    uint32_t m_pad17c[(0x198 - 0x17c) / 4];  // +0x17c .. +0x197
    Sampler* m_sampler;                      // +0x198
    uint32_t m_pad19c;                       // +0x19c
    bool m_localA;                           // +0x1a0
    bool m_local;                            // +0x1a1
    uint8_t m_pad1a2[2];                     // +0x1a2 .. +0x1a3
    Vec3_s00a9_bf20 m_bboxMin;                          // +0x1a4
    Vec3_s00a9_bf20 m_bboxMax;                          // +0x1b0
    uint32_t m_pad1bc[(0x218 - 0x1bc) / 4];  // +0x1bc .. +0x217
    SwarmParamArray m_params;                // +0x218

    bool ConstrainLocal(Particle_s00a9_bf20* p);                       // 0x00a9c710
    bool SetParameter(int command, float* data, int count); // 0x00a9ca50
    void UpdateBasis(float* data);                          // 0x00a9b480
};
// ---- items of slice s00a9bf20 end

// ---- items of slice s00a9ce00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kDegToRad;                           // 0x01678ffc
extern const float kMaxStep;                            // 0x01458c2c
extern const float kTwo;                                // 0x01470f1c
extern const float kOne;                                // 0x01485720
struct Vector3_s00a9_ce00 {
  float x, y, z;
  Vector3_s00a9_ce00() {}
  Vector3_s00a9_ce00(const Vector3_s00a9_ce00& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Matrix33_s00a9_ce00 {
  float m[3][3];
  Matrix33_s00a9_ce00() {}
  Matrix33_s00a9_ce00(const Matrix33_s00a9_ce00& o);                          // @ 0x41cb40
};
struct Quat {
  float x, y, z, w;
};
template <typename T>
struct CurveVector {
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  uint32_t mAllocator[2];
  size_t size() const { return (size_t)(mpEnd - mpBegin); }
  bool empty() const { return mpBegin == mpEnd; }
};
struct Wiggle {
  float f[7];
};
struct FxSub {
  uint32_t mWords[13];
};
struct FxState {
  float mTimer;                                       // +0x00
  uint32_t mWords[5];                                 // +0x04
  void FUN_00a790a0(struct FxSub* sub);               // 0x00a790a0
  void FUN_00a79300(Vector3_s00a9_ce00* out);                    // 0x00a79300
};
struct Xform_s00a9_ce00 {
  uint32_t mFlags;                                    // +0x00
  Vector3_s00a9_ce00 mOffset;                                    // +0x04
  float mScale;                                       // +0x10
  float mRotation[9];                                 // +0x14
};
struct PathView {
  void* mpBegin;                                      // +0x00
  void* mpEnd;                                        // +0x04
};
struct SwarmPath {
  PathView mMain;                                     // +0x00
  uint32_t mUnknown08[5];                             // +0x08
  PathView mAlt;                                      // +0x1c
  uint32_t mUnknown24[3];                             // +0x24
};
extern const Vector3_s00a9_ce00 kTransformZero;                    // 0x01678f44
extern const Matrix33_s00a9_ce00 kTransformIdentity;               // 0x01679010
struct cTransform_s00a9_ce00 {
  uint16_t mFlags;                                      // +0x00
  uint16_t mModCount;                                   // +0x02
  Vector3_s00a9_ce00 mOffset;                                      // +0x04
  float mScale;                                         // +0x10
  Matrix33_s00a9_ce00 mRotation;                                   // +0x14
  cTransform_s00a9_ce00()
      : mFlags(0), mModCount(0), mOffset(kTransformZero), mScale(1.0f),
        mRotation(kTransformIdentity) {}
  void RotateZ(float angle);                            // @ 0x007d1ac0
  void PreRotateX(float angle);                         // @ 0x005a2d90
  void RotateY(float angle);                            // @ 0x006b9050 (mixes rows 0 and 2)
};
struct cSPTransform_s00a9_ce00 {
  void operator=(const cTransform_s00a9_ce00& t);                  // @ 0x00537dc0
};
struct cParticlesDescription_s00a9_ce00 {
  uint32_t mFlags00;                                    // +0x000
  uint32_t mFlags04;                                    // +0x004
  uint32_t mFlags08;                                    // +0x008 bits 25 (path), 23 (attractor), 20 (sub-curves), 12 (collision)
  uint32_t mFlags;                                      // +0x00c bit 2: particle carries an orientation quaternion
  uint32_t pad10[(0x7c - 0x10) / 4];
  float mRateCurveTime;                                 // +0x07c
  uint32_t pad80[(0x9c - 0x80) / 4];
  CurveVector<float> mRotXCurve;                        // +0x09c (PreRotateX)
  CurveVector<float> mRotYCurve;                        // +0x0b0 (RotateY)
  CurveVector<float> mRotZCurve;                        // +0x0c4 (RotateZ)
  uint32_t padD8[(0xe4 - 0xd8) / 4];
  float mRotXOffset;                                    // +0x0e4
  float mRotYOffset;                                    // +0x0e8
  float mRotZOffset;                                    // +0x0ec
  uint32_t padF0[(0x134 - 0xf0) / 4];
  uint8_t mAlignMode;                                   // +0x134 (2..4 = align an axis to the velocity)
  uint8_t pad135[3];
  uint32_t pad138[(0x144 - 0x138) / 4];
  Vector3_s00a9_ce00 mOffset144;                                   // +0x144 acceleration offset
  uint32_t pad150[(0x168 - 0x150) / 4];
  float mDrag168;                                       // +0x168 velocity damping
  uint32_t pad16c[(0x170 - 0x16c) / 4];
  CurveVector<Wiggle> mWiggles;                         // +0x170
  uint32_t pad184[(0x200 - 0x184) / 4];
  FxSub mSubs[2];                                       // +0x200, +0x234 curve/sub-state blocks
  uint32_t pad268[(0x274 - 0x268) / 4];
  float mAlignLag;                                      // +0x274 (>0: smooth the spin angle)
  float mAlignSpin;                                     // +0x278
  float mSpinDamping;                                   // +0x27c
  uint32_t pad280[(0x28c - 0x280) / 4];
  SwarmPath mPath28c;                                   // +0x28c
  float mPathSpeed;                                     // +0x2bc
};
struct cParticle_s00a9_ce00 {
  uint32_t mNodeNext;                                   // +0x00
  uint32_t mNodePrev;                                   // +0x04
  float mAge;                                           // +0x08
  float mLife;                                          // +0x0c
  Vector3_s00a9_ce00 mPosition;                                    // +0x10
  Vector3_s00a9_ce00 mVelocity;                                    // +0x1c
  uint32_t pad28[(0x44 - 0x28) / 4];
  float mSpin;                                          // +0x44
  float mRotation;                                      // +0x48 (-999 = unset)
  FxState mState4c;                                     // +0x4c
  FxState mState64;                                     // +0x64
  uint32_t pad7c;                                       // +0x7c
  Quat mOrientation;                                    // +0x80
  uint32_t pad90[1];
  float mRotZVary;                                      // +0x94
  float mRotXVary;                                      // +0x98
  float mRotYVary;                                      // +0x9c
};
Vector3_s00a9_ce00* __cdecl RotateByQuat(Vector3_s00a9_ce00* out, const Vector3_s00a9_ce00* v, const Quat* q);   // @ 0x0059aed0
void __cdecl QuatToMatrix(Matrix33_s00a9_ce00* out, const Quat* q);                        // @ 0x004a9b40
void __cdecl AlignAxisX(const Vector3_s00a9_ce00* dir, Matrix33_s00a9_ce00* out);                     // @ 0x00a81a20
void __cdecl AlignAxisY(const Vector3_s00a9_ce00* dir, Matrix33_s00a9_ce00* out);                     // @ 0x00a818f0
void __cdecl AlignAxisZ(const Vector3_s00a9_ce00* dir, Matrix33_s00a9_ce00* out);                     // @ 0x00a81b80
float __cdecl MatrixAngle(const Matrix33_s00a9_ce00* m);                                   // @ 0x00a9af40
void __cdecl WigglePoint(float time, const CurveVector<Wiggle>* wiggles, const Vector3_s00a9_ce00* center,
                         Vector3_s00a9_ce00* pos);                                         // @ 0x00a9aff0
__forceinline float EvalCurve(const CurveVector<float>& v, float t) {
  size_t n = v.size() - 1;
  if (n == 0)
    return v.mpBegin[0];
  float f = (float)n * t;
  int i = (int)f;
  float frac = f - (float)i;
  if (frac > 0.0f)
    return (v.mpBegin[i + 1] - v.mpBegin[i]) * frac + v.mpBegin[i];
  return v.mpBegin[i];
}
struct cParticlesEffect_s00a9_ce00 {
  uint32_t pad00[3];
  cParticlesDescription_s00a9_ce00* mDesc;                         // +0x00c
  uint32_t pad10[(0x34 - 0x10) / 4];
  Vector3_s00a9_ce00 mCenter;                                      // +0x034
  uint32_t pad40[(0xa0 - 0x40) / 4];
  double mOverallTime;                                  // +0x0a0

  void BuildParticleTransform(cParticle_s00a9_ce00* p, float t, float size, Vector3_s00a9_ce00* pos,
                              cSPTransform_s00a9_ce00* out);       // @ 0x00a9ce00
};
struct ParticleEmitter {
  uint32_t pad00[3];
  cParticlesDescription_s00a9_ce00* mDesc;                         // +0x00c
  uint32_t pad10;
  void* mpFactory;                                      // +0x014
  uint32_t pad18;
  uint32_t u1c;                                         // +0x01c
  uint8_t pad20[2];
  uint8_t b22;                                          // +0x022
  uint8_t pad23[0x0d];
  Xform_s00a9_ce00 mXform30;                                       // +0x030
  Xform_s00a9_ce00 mXform68;                                       // +0x068
  uint32_t padA0[(0xcc - 0xa0) / 4];
  Vector3_s00a9_ce00 mAccel;                                       // +0x0cc
  uint32_t padD8[(0x114 - 0xd8) / 4];
  Vector3_s00a9_ce00 mAttractor;                                   // +0x114
  float mAttractorStrength;                             // +0x120
  uint32_t pad124[(0x194 - 0x124) / 4];
  void* mpCollisionObj;                                 // +0x194
  uint32_t pad198[(0x218 - 0x198) / 4];
  PathView mPath;                                       // +0x218

  bool FUN_00a9b8d0(cParticle_s00a9_ce00* p, Vector3_s00a9_ce00* pos);        // 0x00a9b8d0
  bool FUN_00a9bf20(cParticle_s00a9_ce00* p, float dt);            // 0x00a9bf20
  bool FUN_00a9d640(cParticle_s00a9_ce00* p, float dt);            // 0x00a9d640
};
void __cdecl FUN_00a798d0(float* pos, float dt, PathView* path, float speed, Xform_s00a9_ce00* xf);
bool __cdecl FUN_00a79500(SwarmPath* path, const Vector3_s00a9_ce00* pos, float radius, Vector3_s00a9_ce00* out);
// ---- items of slice s00a9ce00 end

// ---- items of slice s00a9dc00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" bool FUN_00a79f60(void* a1, float dt, void* a3, const float* a4, const float* a5, void* a6); // 0x00a79f60
typedef unsigned int uint32;
struct cMetaParticle;
struct cMetaParticlesEffect_s00a9_dc00;
extern uint32 g_1679034;   // 0x01679034  timestep flag mask A
extern uint32 g_1679038;   // 0x01679038  timestep flag mask B
struct cMetaParticle {
    char pad[0x28];
};
struct cMetaParticlesEffect_s00a9_dc00 {
    bool UpdateParticle(cMetaParticle* p, float dt);        // 0x00a9dc00
    bool UpdateParticleCheap(cMetaParticle* p, float dt);   // 0x00a9b780
    bool UpdateParticleFull(cMetaParticle* p, float dt);    // 0x00a9d640
};
// ---- items of slice s00a9dc00 end

// ---- items of slice s00a9ddd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_Mask[2];     // 0x01678f3c (bitset mask)
extern const float kZero;      // 0x01485378
extern uint32_t g_Mask5430;    // 0x01565430
extern float g_HalfPi;         // 0x01565424
extern float g_Inv;            // 0x01678ffc
extern float g_Mat9[9];        // 0x01679010
struct Vec3_s00a9_ddd0 { float x, y, z; };
struct RandomLinearCongruential { double RandomDoubleUniform(); };
extern RandomLinearCongruential g_Random_s00a9_ddd0;   // 0x016778dc (sRandom_Swarm)
static inline double RandRange(double lo, double hi)
{
    double r = g_Random_s00a9_ddd0.RandomDoubleUniform();
    double v = r * (hi - lo) + lo;
    if (v < hi) {
        if (v < lo) return lo;
        return v;
    }
    return hi;
}
struct Xform_s00a9_ddd0 {
    uint32_t flags;      // +0x00 (this+0x30)
    Vec3_s00a9_ddd0 t;              // +0x04
    float scale;         // +0x10
    float m[9];          // +0x14 (this+0x44)
    void Transform(Vec3_s00a9_ddd0* v);   // FUN_007cdee0 (thiscall)
};
struct FxObj {
    virtual void v0();
    virtual void v1();
    virtual void v2(int a);                                  // +0x08
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6(void* s, Xform_s00a9_ddd0* x);                      // +0x18
    virtual void v7();
    virtual void v8(int idx, uint32_t* p, int n);            // +0x20
    virtual void v9(int a, uint32_t b);                      // +0x24
    virtual void v10(int a);                                 // +0x28
    virtual void v11();
    virtual void v12();
    virtual void AddRef();                                   // +0x34
    virtual void Release();                                  // +0x38
};
struct FxFactory {
    FxObj* Create(uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // FUN_00a714f0
};
struct FxSub_s00a9_ddd0 { uint32_t w[13]; };                // 0x34 bytes (desc+0x200 array)
struct FxState_s00a9_ddd0 { uint32_t w[6]; };               // 0x18 bytes (particle+0x4c array)
void FxStateInit(FxState_s00a9_ddd0* st, FxSub_s00a9_ddd0* sub, Vec3_s00a9_ddd0* dir, int flag);   // FUN_00a79430 (thiscall, see below)
struct Desc {
    uint32_t pad0[2];
    uint32_t flags[2];       // +0x08 (64-bit bitset: low word, high word)
    float lifeMin;           // +0x10
    float lifeMax;           // +0x14
    uint32_t pad18[5];
    uint32_t emitDir[6];     // +0x2c
    uint32_t emitSpeed[8];   // +0x44
    float f64;               // +0x64
    uint32_t pad68[7];
    float* p84;              // +0x84
    uint32_t pad88[4];
    float sizeVary;          // +0x98
    uint32_t pad9c[15];
    float fd8, fdc, fe0;     // +0xd8
    uint32_t pade4[8];
    float vary104, vary108, vary10c;   // +0x104
    uint32_t pad110[5];
    float vary124;           // +0x124
    uint32_t key128;         // +0x128
    uint32_t key12c;         // +0x12c
    uint32_t pad130;
    uint8_t mode134;         // +0x134
    uint8_t pad135[3];
    uint32_t pad138[8];
    float attract;           // +0x158
    Vec3_s00a9_ddd0 attractPos;         // +0x15c
    uint32_t pad168[38];
    FxSub_s00a9_ddd0 subs[2];           // +0x200
    uint32_t pad268[16];
    uint32_t obj2a8[1];      // +0x2a8
};
struct Particle_s00a9_ddd0 {
    uint32_t node[2];
    float age;               // +0x08
    float life;              // +0x0c
    Vec3_s00a9_ddd0 pos;                // +0x10
    Vec3_s00a9_ddd0 vel;                // +0x1c
    float size;              // +0x28
    float aspect;            // +0x2c
    float rotation;          // +0x30
    float alpha;             // +0x34
    Vec3_s00a9_ddd0 color;              // +0x38
    uint32_t pad44;
    float f48;               // +0x48
    FxState_s00a9_ddd0 st[2];           // +0x4c
    FxObj* fx;               // +0x7c
    float quat[4];           // +0x80
    int index;               // +0x90
    float f94, f98, f9c;     // +0x94
};
struct Sampler_s00a9_ddd0 {             // vtable object at this+0x19c
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
    virtual bool Contains(Vec3_s00a9_ddd0* p);                 // +0x18
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
    virtual Vec4* Sample(Vec4* out, Vec3_s00a9_ddd0* p);       // +0x2c
};
struct HitObj {              // SpawnRec::a
virtual void h0();
virtual void h1();
virtual void h2();
virtual void h3();
    virtual bool Collide(Vec3_s00a9_ddd0* a, Vec3_s00a9_ddd0* b, Vec3_s00a9_ddd0* out, float* quat, int pa, int pb);   // +0x10
virtual void h5();
virtual void h6();
virtual void h7();
virtual void h8();
virtual void h9();
    virtual void h10();
    virtual void Apply(uint32_t* spec, int dst, void* arg);                           // +0x2c
};
struct SpawnRec {
    HitObj* a;               // +0x00
    uint32_t* b;             // +0x04
    int has8;                // +0x08
    int c;                   // +0x0c
    int has10;               // +0x10
    int c14;                 // +0x14
};
bool FUN_00a79660(void* base, void* v);                   // cdecl
Vec3_s00a9_ddd0* FUN_00a817c0(Vec3_s00a9_ddd0* out, Vec3_s00a9_ddd0* in, float f);         // cdecl
Vec3_s00a9_ddd0* FUN_00a81580(Vec3_s00a9_ddd0* out, Vec3_s00a9_ddd0* in);                  // cdecl
Vec3_s00a9_ddd0* FUN_007cdbe0_s00a9_ddd0(Vec3_s00a9_ddd0* out, void* in);                  // cdecl
float FUN_00a78f80(float f);                              // cdecl
float* QuatFromMatrix33(float* out, float* m, float z);   // 0x472b80 cdecl
struct SpawnArgs {
    short kind, one;
    Vec3_s00a9_ddd0 pos;
    float s;
    float m[9];
};
struct ParticleEmitter_s00a9_ddd0 {
    uint32_t pad0[3];
    Desc* desc;                  // +0x0c
    uint32_t u10;                // +0x10
    FxFactory* factory;          // +0x14
    uint32_t pad18;
    uint32_t u1c;                // +0x1c
    uint8_t pad20[2];
    uint8_t b22;                 // +0x22
    uint8_t pad23[0xd];
    Xform_s00a9_ddd0 xf30;                  // +0x30
    Xform_s00a9_ddd0 xf68;                  // +0x68
    uint32_t pada0[(0x13c - 0xa0) / 4];
    float f13c;                  // +0x13c
    uint32_t pad140;
    float f144;                  // +0x144
    uint32_t pad148[(0x19c - 0x148) / 4];
    Sampler_s00a9_ddd0* sampler;            // +0x19c
    uint8_t pad1a0[2];
    uint8_t b1a2;                // +0x1a2
    uint8_t pad1a3;
    Vec3_s00a9_ddd0 v1a4;                   // +0x1a4
    uint32_t pad1b0[3];
    SpawnRec* recBegin;          // +0x1bc
    SpawnRec* recEnd;            // +0x1c0
    uint32_t pad1c4[4];
    int i1d4;                    // +0x1d4
    uint32_t pad1d8[4];
    int i1e8;                    // +0x1e8
    uint32_t pad1ec[4];
    int i1fc;                    // +0x1fc
    uint32_t pad200[5];
    uint8_t b214;                // +0x214
    uint8_t pad215[3];
    uint32_t p218, p21c;         // +0x218
    uint32_t pad220[3];
    uint8_t b22c;                // +0x22c
    uint8_t pad22d[3];
    uint32_t u230;               // +0x230
    int i234;                    // +0x234
    uint32_t u238, u23c;         // +0x238
    uint32_t u240, u244;         // +0x240

    bool CheckSpawn(Particle_s00a9_ddd0* p);          // FUN_00a9c710
    bool InitParticle(Particle_s00a9_ddd0* p);        // @ 0x00a9ddd0
};
static inline Vec3_s00a9_ddd0 V3Mul(float x, float y, float z, float s) { Vec3_s00a9_ddd0 r; r.x = x * s; r.y = y * s; r.z = z * s; return r; }
static inline void V3AddTo(Vec3_s00a9_ddd0& v, const Vec3_s00a9_ddd0& a) { v.x += a.x; v.y += a.y; v.z += a.z; }
static inline float AtanApprox(float y, float x)
{
    float ay = fabsf(y) + 1e-10f;
    float ax = fabsf(x);
    float r = (ay - ax) / (ax + ay);
    r = (0.9817f - (r * r) * 0.1963f) * r;
    if (x < 0.0f) r = g_HalfPi * 3.0f - r;
    else r = r + g_HalfPi;
    if (y < 0.0f) r = -r;
    return r;
}
// ---- items of slice s00a9ddd0 end

// ---- items of slice s00a9ef80 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3_s00a9_ef80 { float x, y, z; };
extern RandomLinearCongruential g_Random_s00a9_ef80;                 // 0x016778dc (sRandom_Swarm)
static inline double RandRange_s00a9_ef80(double lo, double hi)
{
    double r = g_Random_s00a9_ef80.RandomDoubleUniform();
    double v = r * (hi - lo) + lo;
    if (v >= hi) return hi;
    if (v < lo) return lo;
    return v;
}
struct Matrix3 { float m[9]; Matrix3(); };
struct XformMsg {
    uint16_t flags;
    uint16_t count;
    Vec3_s00a9_ef80     pos;
    float    scale;
    Matrix3  rot;
    XformMsg();
};
struct Desc_s00a9_ef80 {
    uint8_t  pad00[8];
    uint32_t flags[2];         // +0x08 (64-bit bitset)
    float    lifeMin;          // +0x10
    float    lifeMax;          // +0x14
    uint8_t  pad18[0x128 - 0x18];
    uint32_t key128;           // +0x128
    uint32_t key12c;           // +0x12c
};
struct FxObj_s00a9_ef80 {
    virtual void v0();
    virtual void v1();
    virtual void v2(uint32_t a);                          // +0x08
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6(void* src, void* xform);              // +0x18
    virtual void v7();
    virtual void v8();
    virtual void v9(uint32_t a, uint32_t b);              // +0x24
    virtual void v10(uint8_t a);                          // +0x28
    virtual void v11();
    virtual void v12();
    virtual void AddRef();                                // +0x34
    virtual void Release();                               // +0x38
};
struct FxBase {
    virtual void b0();
    virtual void b1();
    virtual void b2();
    virtual void b3(uint32_t key);                        // +0x0c
    virtual void b4();
    virtual void b5();
    virtual void b6();
    virtual void b7(void* msg);                           // +0x1c
    virtual void b8(void* msg);                           // +0x20
};
struct FxFactory_s00a9_ef80 {
    FxObj_s00a9_ef80* Create(uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // FUN_00a714f0
};
struct Particle_s00a9_ef80;
struct FxPtr {
    FxObj_s00a9_ef80* p;                                             // +0x00
    void Assign(FxObj_s00a9_ef80* o);                                // FUN_007d4590 (out of line)
    void Reset() { FxObj_s00a9_ef80* old = p; if (old) { p = 0; old->Release(); } }
};
struct Particle_s00a9_ef80 {
    void*   node[2];                                      // +0x00 / +0x04 intrusive links
    float   age;                                          // +0x08
    float   life;                                         // +0x0c
    uint8_t pad10[0x7c - 0x10];
    FxPtr   fx;                                           // +0x7c
};
struct Emitter {
    virtual void v0();                                    // vtable at +0x00
    virtual void v1();
    virtual void v2(int a);                               // +0x08
    virtual void v3();
    virtual bool v4();                                    // +0x10
    uint32_t   u04;
    uint32_t   u08;
    Desc_s00a9_ef80*      desc;                                      // +0x0c
    uint32_t   u10;                                       // +0x10
    FxFactory_s00a9_ef80* factory;                                   // +0x14
    uint32_t   u18;                                       // +0x18
    uint32_t   u1c;                                       // +0x1c
    uint16_t   u20;                                       // +0x20
    uint8_t    b22;                                       // +0x22
    uint8_t    pad23;
    void*      head;                                      // +0x24 active-list head
    uint32_t   u28;                                       // +0x28
    uint32_t   count;                                     // +0x2c
    uint8_t    pad30[0x124 - 0x30];
    uint32_t   u124;                                      // +0x124
    int32_t    i128;                                      // +0x128
    uint8_t    pad12c[0x144 - 0x12c];
    float      f144;                                      // +0x144
    uint8_t    pad148[0x22c - 0x148];
    uint8_t    b22c;                                      // +0x22c
    uint8_t    pad22d[3];
    uint32_t   u230;                                      // +0x230
    uint8_t    pad234[0x248 - 0x234];
    Emitter*   pool;                                      // +0x248 owned child emitter

    bool InitParticle(Particle_s00a9_ef80* p);                       // FUN_00a9ddd0
    void FUN_00a9ef80(Particle_s00a9_ef80* p);                       // @ 0x00a9ef80
};
// ---- items of slice s00a9ef80 end

// @ 0x00a938d0
void RegisterMeshStreamers2(bool)
{
    gMeshStreamerTable.mpRegister = (void*)0x00a8bf10;
    gMeshStreamerTable.mpCreate   = (void*)0x00a8cc00;
    gMeshStreamerTable.mpField0c  = (void*)0x00a93880;
    gMeshStreamerTable.mpField14  = (void*)0x00a89680;
    gMeshStreamerTable.mField18   = 3;
    gMeshStreamerTable.mField1c   = 4;
}

// @ 0x00a93910
cMetaParticlesEffect::~cMetaParticlesEffect()
{
    FreeVecBuffer(mVecA8.mpBegin);
    FreeVecBuffer(mVec94.mpBegin);
    FreeVecBuffer(mVec80.mpBegin);
    FreeVecBuffer(mVec60.mpBegin);
    mpVtbl = (void*)0x013ef094;
}

// @ 0x00a93980
cMetaParticlesEffect::cMetaParticlesEffect()
{
    mField04 = 0;
    mpVtbl = (void*)0x01458474;
    mField08 = 0;
    mField0c = 2.0f;
    mField10 = 2.0f;
    mField14 = 0.0f;
    mScales18[0] = -1.0f;
    mScales18[1] = -1.0f;
    mScales18[2] = -1.0f;
    mScales18[3] = -1.0f;
    mField28 = 0.0f;
    mField2c = 0.0f;
    mField30 = 1.0f;
    mField34 = 0.0f;
    mField38 = 0.0f;
    mField3c = 1.0f;
    mField40 = 0.0f;
    mField44 = 0.0f;
    mField48 = 0.0f;
    mField4c = 0.0f;
    mField50 = 0.0f;
    mVec60.mpBegin = 0;
    mVec60.mpEnd = 0;
    mVec60.mpCapacity = 0;
    mField54 = 0.0f;
    mField58 = 0.0f;
    mField5c = 0.0f;
    mField74 = 1.0f;
    mField7c = 0.0f;
    mField78 = 0;
    mVec80.mpBegin = 0;
    mVec80.mpEnd = 0;
    mVec80.mpCapacity = 0;
    mVec94.mpBegin = 0;
    mVec94.mpEnd = 0;
    mVec94.mpCapacity = 0;
    mVecA8.mpBegin = 0;
    mVecA8.mpEnd = 0;
    mVecA8.mpCapacity = 0;
    mFieldC8 = 0;
    mFieldC9 = 0;
    mFieldCa = 0;
    mFieldCb = 0;
    mFieldD0 = 0.0f;
    mFieldC0 = -1;
    mFieldC4 = -1;
    mFieldD8 = -1;
    mFieldDc = -1;
    mFieldCc = 0;
    mFieldE0 = 0;
    mFieldE4 = g16786dc;
    mFieldE8 = g16786e0;
    mFieldEc = g16786e4;
    mFieldF0 = 0.0f;
    mFieldF4 = 0.0f;
    mFieldF8 = 0.0f;
    mFieldFc = g16786dc;
    mField100 = g16786e0;
    mField104 = g16786e4;
    mField108 = 0.0f;

    PushBackFloat(mVec60, 30.0f);
    Vector3 one = { 1.0f, 1.0f, 1.0f };
    PushBackVec3(mVec94, one);
    PushBackFloat(mVecA8, 1.0f);
    PushBackFloat(mVec80, 1.0f);
}

// @ 0x00a93c60
void cSampleRange::Erase(const Vector3& v)
{
    float x0 = mMin.x;
    if (x0 != gFltMax && x0 != -gFltMax) {
        mMin.y = mMin.y - v.y;
        mMin.z = mMin.z - v.z;
        mMin.x = mMin.x - v.x;
        mMax.z = mMax.z + v.z;
        mMax.x = mMax.x + v.x;
        mMax.y = mMax.y + v.y;
    }
}

// @ 0x00a93cf0
void CAbil::FUN_00a93cf0(IoObj* io, void* mgr, CAbil* obj)
{
    char* o = (char*)obj;
    int tmp;
    FUN_0093a780(io, &tmp, 1, 0);
    *(i32*)(o + 0x184) = tmp & 0x7ff;

    io->FUN_00a93d30(o + 0xc, 8);
    FUN_0093a780(io, o + 0x14, 1, 0);
    io->FUN_00a93d30(o + 0x18, 8);
    io->FUN_00a93d30(o + 0x20, 8);
    io->FUN_00a93d30(o + 0x28, 0xc);
    io->FUN_00a93d30(o + 0x34, 0xc);
    io->FUN_00a93d30(o + 0x40, 8);
    io->FUN_00a93d30(o + 0x48, 0xc);
    io->FUN_00a93d30(o + 0x54, 0xc);
    FUN_007d27d0(io, o + 0x60);
    FUN_0093a780(io, o + 0x74, 1, 0);
    FUN_0093a700(io, o + 0x78, 1, 0);
    FUN_0093a780(io, o + 0x7c, 1, 0);
    FUN_007d27d0(io, o + 0x80);
    FUN_007ed920(io, o + 0x94);
    FUN_007d27d0(io, o + 0xa8);
    FUN_00a85b00(io, o + 0xc0);
    FUN_0093a6c0(io, o + 0xe0, 1);
    io->FUN_00a93d30(o + 0xe4, 0xc);
    FUN_0093a780(io, o + 0xf0, 1, 0);
    FUN_0093a780(io, o + 0xf4, 1, 0);
    FUN_0093a780(io, o + 0xf8, 1, 0);
    io->FUN_00a93d30(o + 0xfc, 0xc);
    FUN_0093a780(io, o + 0x108, 1, 0);
    (void)mgr;
}

// @ 0x00a93ea0
void CAbil::FUN_00a93ea0()
{
    if (m0c != 0) {
        ((void (__thiscall*)(void*, int))*(void**)((char*)vt0 + 0xc))(this, 1);
    }
    if (m184 >= 0) {
        void* p = ((void* (__thiscall*)(void*))VS(m20, 0x20))(m20);
        ((void (__thiscall*)(void*, int))VS(p, 0x1c))(p, m184);
    }
    m1c = 0;
    m20 = 0;
}

// @ 0x00a93ee0
int CAbil::FUN_00a93ee0(int id, int* a, int count)
{
    if (id != 1) {
        return 0;
    }
    if (count >= 2 && a[1] != *(unsigned char*)((char*)m1c + 0xe0)) {
        return 1;
    }

    int v = *a;
    if (m17c != v || m180 != (v >> 31)) {
        m17c = v;
        m180 = v >> 31;
        if (m184 >= 0) {
            void* pL = ((void* (__thiscall*)(void*))VS(m20, 0x20))(m20);
            ((void (__thiscall*)(void*, int))VS(pL, 0x1c))(pL, m184);

            unsigned key = (unsigned)m17c;
            unsigned hi  = (unsigned)m180;
            struct Words { unsigned w[8]; };
            Words words;
            words = *(const Words*)((char*)m1c + 0xc0);
            if ((key & hi) != 0xffffffffu) {
                words.w[0] = key;
                words.w[1] = hi;
            }
            ((char*)&words)[8] = 0;
            if (((char*)&words)[9] == 0x0f) {
                void* q = ((void* (__thiscall*)(void*))VS(m20, 0x30))(m20);
                void* r = ((void* (__thiscall*)(void*))VS(q, 0x14))(q);
                ((char*)&words)[8] = ((char  (__thiscall*)(void*, char, unsigned, unsigned))
                        VS(r, 0x24))(r, ((char*)&words)[8], words.w[0], words.w[1]);
            }
            char ok = ((char (__thiscall*)(void*, void*, void*, int*))
                       VS(pL, 0x18))(pL, (char*)this - 4, &words, &m184);
            if (!ok) {
                ((void (__thiscall*)(void*, char, void*))
                 VS(pL, 0x10))(pL, ((char*)&words)[8], &m188);
                m18c = ((char*)&words)[8];
                m184 = -1;
            }
        }
    }
    return 1;
}

// @ 0x00a94030
void CAbil::FUN_00a94030(char v)
{
    m0e = v;
    if (v != 0) {
        *(i32*)((char*)this + 0x100) = *(i32*)((char*)this + 0x94);
        *(i32*)((char*)this + 0x104) = *(i32*)((char*)this + 0x98);
        *(i32*)((char*)this + 0x108) = *(i32*)((char*)this + 0x9c);
    }
    if (m0c != 0 && m184 >= 0) {
        void* p = ((void* (__thiscall*)(void*))VS(m20, 0x20))(m20);
        ((void (__thiscall*)(void*, int, char))VS(p, 0x24))(p, m184, m0e);
    }
}

// @ 0x00a940a0
void CAbil::FUN_00a940a0(void* p)
{
    AbilityHook h = g_16787b0[m190];
    if (h != 0) {
        h(this, p, &m18c);
    }
    m110 = (u16_s00a9_3cf0)(m110 + 1);
}

// @ 0x00a940e0
int __cdecl FUN_00a940e0(void* a, void* b, void* c, void* d)
{
    int out = 0;
    FUN_00a6c7a0((char*)b + 0xc0, 0, &out, &c, &d);
    return out;
}

// @ 0x00a94130
void CAbil::FUN_00a94130(int p)
{
    double zero = 0.0;
    unsigned f;
    if (p == 0
        || *(u16_s00a9_3cf0*)((char*)m1c + 0x78) == 0
        || ((f = *(u32_s00a9_3cf0*)((char*)m1c + 8)), (f >> 2) & 1)
        || ((f >> 10) & 1)) {

        if (m0c == 0 || m0d != 0) {
            m0d = 0;
            m0c = 1;
        }
        *(double*)((char*)this + 0x3c) = zero;
        *(double*)((char*)this + 0x2c) = zero;
        *(i32*)((char*)this + 0x100) = *(i32*)((char*)this + 0x94);
        *(i32*)((char*)this + 0x104) = *(i32*)((char*)this + 0x98);
        *(i32*)((char*)this + 0x108) = *(i32*)((char*)this + 0x9c);
        m44 = 0;
        *(float*)((char*)this + 0x54) = 0.0f;

        float neg = *(float*)((char*)m1c + 0x18);
        if (neg >= 0.0f) {
            m64 = FUN_007cdb90((char*)m1c + 0x18);
        } else {
            float n2 = *(float*)((char*)m1c + 0x20);
            if (n2 >= 0.0f) {
                m64 = FUN_007cdb90((char*)m1c + 0x20);
            } else {
                m64 = 0.0f;
            }
        }
        m34 = (p != 0);
        if (m184 >= 0) {
            void* q = ((void* (__thiscall*)(void*))VS(m20, 0x20))(m20);
            ((void (__thiscall*)(void*, int, char))VS(q, 0x24))(q, m184, m0e);
        }
    }
}

// @ 0x00a94220
int CAbil::FUN_00a94220(int id, int* src, int n)
{
    if (id < 0xf) {
        switch (id) {
        case 0:  m128 = *(float*)src; return 1;
        case 1:  m134 = *(float*)src; return 1;
        case 2:  m130 = *(float*)src; return 1;
        case 3:  m12c = *(float*)src; return 1;
        case 4:  m138 = *(float*)src; return 1;
        case 5:
            m13c = *(float*)&src[0];
            m140 = *(float*)&src[1];
            m144 = *(float*)&src[2];
            return 1;
        case 0xe:
            if (m184 >= 0) {
                void* p = ((void* (__thiscall*)(void*))VS(m20, 0x20))(m20);
                return ((int (__thiscall*)(void*, int, int, int, int, int*))
                        VS(p, 0x74))(p, 0, m184, 0, n, src);
            }
            break;
        default:
            break;
        }
    } else if (id == 0x101) {
        m110 = (u16_s00a9_3cf0)src[0];
        m118 = *(float*)&src[1];
        m120 = *(float*)&src[2];
        m114 = *(float*)&src[3];
        m11c = *(float*)&src[4];
        m124 = *(float*)&src[5];
        return 1;
    }
    return 0;
}

// @ 0x00a943a0
int CAbil::FUN_00a943a0()
{
    void* o = m20;
    float* pf = (float*)((char*)o + 0x74);
    float eps = g_13f11c8;
    float local = eps;
    if (!(*(float*)((char*)o + 0x74) > eps)) {
        pf = &local;
    }
    m50 = 1.0 / (double)*pf;

    *(i32*)((char*)this + 0x170) = *(i32*)((char*)o + 0x54);
    *(i32*)((char*)this + 0x174) = *(i32*)((char*)o + 0x58);
    *(i32*)((char*)this + 0x178) = *(i32*)((char*)o + 0x5c);
    *(i32*)((char*)this + 0x164) = *(i32*)((char*)o + 0x48);
    *(i32*)((char*)this + 0x168) = *(i32*)((char*)o + 0x4c);
    *(i32*)((char*)this + 0x16c) = *(i32*)((char*)o + 0x50);

    void* s = m20;
    m84 = **(float**)((char*)s + 0x80);
    unsigned cnt = (unsigned)((*(int*)((char*)s + 0x84) - *(int*)((char*)s + 0x80)) >> 2);
    unsigned i = 1;
    if (cnt > i) {
        do {
            float v = (*(float**)((char*)s + 0x80))[i];
            if (v > m84) {
                m84 = v;
            }
            i++;
        } while (i < (unsigned)((*(int*)((char*)s + 0x84) - *(int*)((char*)s + 0x80)) >> 2));
    }
    return cnt;
}

// @ 0x00a94470
CAbil* CAbil::FUN_00a94470(void* owner)
{
    double zero = 0.0;
    GmeRefCount*   rc = (GmeRefCount*)(void*)this;
    GmeIComponent* cp = (GmeIComponent*)(void*)this;
    void** vp = (void**)this;

    vp[2] = (void*)0x13ef094;
    vp[3] = 0;
    vp[1] = (void*)0x13f21d4;
    vp[2] = (void*)0x13f2194;
    vp[0] = (void*)0x1458714;
    vp[1] = (void*)0x14586d8;
    vp[2] = (void*)0x14586d4;
    (void)rc; (void)cp;

    *(u8_s00a9_3cf0*)((char*)this + 0x10) = 0;
    *(u8_s00a9_3cf0*)((char*)this + 0x11) = 0;
    *(&m12) = 1;

    void* self = (char*)this + 0x14;
    *(void**)((char*)self + 4) = self;
    *(void**)(char*)self = self;

    *(double*)((char*)this + 0x30) = zero;
    *(double*)((char*)this + 0x40) = zero;
    m50 = *(double*)g_1454410;
    m58 = 0.0f;
    m1c = 0;
    m20 = owner;
    m24 = 0;
    m28 = 0;
    m38 = 0;
    m48 = 0;

    m5c = g_167889c;
    m60 = g_16788a0;
    m64 = g_16788a4;

    m68 = 0.0f;
    m6c = 0.0f;
    m70 = 0.0f;
    m74 = 0.0f;
    m78 = 0.0f;
    m7c = 0.0f;
    m80 = 0.0f;
    m84 = 0.0f;

    m88 = g_167889c;
    m8c = g_16788a0;
    m90_0 = 0;                            // +0x90 low byte
    *(float*)((char*)this + 0x94) = g_16788a4;
    m98 = g_167889c;
    m9c = g_16788a0;
    ma0 = g_16788a4;
    ma4 = g_1485720;

    ((MatCtor*)((char*)this + 0xa8))->FUN_0041cb40(&g_1678948);

    *(u16_s00a9_3cf0*)((char*)this + 0xcc) = 0;
    *(u16_s00a9_3cf0*)((char*)this + 0xce) = 0;
    *(float*)((char*)this + 0xd0) = g_167889c;
    *(float*)((char*)this + 0xd4) = g_16788a0;
    *(float*)((char*)this + 0xd8) = g_16788a4;
    *(float*)((char*)this + 0xdc) = g_1485720;

    ((MatCtor*)((char*)this + 0xe0))->FUN_0041cb40(&g_1678948);

    *(float*)((char*)this + 0x104) = g_167889c;
    *(float*)((char*)this + 0x108) = g_16788a0;
    *(float*)((char*)this + 0x10c) = g_16788a4;

    *(u16_s00a9_3cf0*)((char*)this + 0x110) = 0;
    *(u16_s00a9_3cf0*)((char*)this + 0x112) = 0;

    *(float*)((char*)this + 0x114) = g_1678860;
    *(float*)((char*)this + 0x118) = g_1678864;
    *(float*)((char*)this + 0x11c) = g_1678860;
    *(float*)((char*)this + 0x120) = g_1678864;
    *(float*)((char*)this + 0x124) = g_1678860;
    *(float*)((char*)this + 0x128) = g_1678864;

    float cv = g_1485720;
    *(float*)((char*)this + 0x12c) = cv;
    *(float*)((char*)this + 0x130) = cv;
    *(float*)((char*)this + 0x134) = cv;
    *(float*)((char*)this + 0x138) = cv;
    *(float*)((char*)this + 0x13c) = cv;
    *(float*)((char*)this + 0x140) = cv;
    *(float*)((char*)this + 0x144) = cv;
    *(float*)((char*)this + 0x148) = cv;
    *(float*)((char*)this + 0x14c) = cv;
    *(float*)((char*)this + 0x150) = cv;
    *(float*)((char*)this + 0x154) = cv;
    *(float*)((char*)this + 0x158) = cv;
    *(float*)((char*)this + 0x15c) = cv;
    *(float*)((char*)this + 0x160) = cv;

    *(float*)((char*)this + 0x164) = 0.0f;
    *(float*)((char*)this + 0x168) = 0.0f;
    *(float*)((char*)this + 0x16c) = 0.0f;
    *(float*)((char*)this + 0x170) = 0.0f;
    *(float*)((char*)this + 0x174) = 0.0f;
    *(float*)((char*)this + 0x178) = 0.0f;

    m180 = -1;
    m184 = -1;
    *(i32*)((char*)this + 0x188) = -1;
    *(u16_s00a9_3cf0*)((char*)this + 0x17c) = 0;
    m190 = 0;
    return this;
}

// @ 0x00a947b0
CAbil* CAbil::FUN_00a947b0(u8_s00a9_3cf0 freeIt)
{
    vt0 = (void*)0x1458714;
    vt1 = (void*)0x14586d8;
    vt2 = (void*)0x14586d4;
    ((IntrusiveList*)(void*)((char*)this + 0x14))->FUN_00620230();
    vt1 = (void*)0x13f21d4;
    vt2 = (void*)0x13ef094;
    if (freeIt & 1) {
        FUN_00f47380(this);
    }
    return this;
}

// @ 0x00a94800
void CAbil::FUN_00a94800(void* owner, void* mgr)
{
    m20 = owner;
    m24 = ((void* (__thiscall*)(void*))VS(owner, 0x2c))(owner);

    float big = g_1565198;
    float nbig = -big;
    m68 = big;
    m6c = big;
    m70 = big;
    m74 = nbig;
    m78 = nbig;
    m7c = nbig;

    ((CAbil*)((char*)this - 4))->FUN_00a943a0();

    void* p = ((void* (__thiscall*)(void*))VS(owner, 0x20))(owner);
    if (p != 0) {
        unsigned key = (unsigned)m17c;
        unsigned hi  = (unsigned)m180;
        unsigned words[8];
        unsigned* src = (unsigned*)((char*)m1c + 0xc0);
        for (int i = 0; i < 8; i++) {
            words[i] = src[i];
        }
        if ((key & hi) != 0xffffffffu) {
            words[0] = key;
            words[1] = hi;
        }
        char flag = 0;
        if (((char*)words)[9] == 0x0f) {
            void* q = ((void* (__thiscall*)(void*))VS(mgr, 0x14))(mgr);
            flag = ((char  (__thiscall*)(void*, unsigned, unsigned, char))
                    VS(q, 0x24))(q, words[0], words[1], 0);
        }
        ((void (__thiscall*)(void*, void*, unsigned*, int*))
         VS(p, 0x18))(p, (char*)this - 4, words, &m184);
        ((void (__thiscall*)(void*, char, void*))
         VS(p, 0x10))(p, flag, &m188);
        m18c = flag;
    }
}

// @ 0x00a94940
void CAbil::FUN_00a94940(void* t0, void* t1)
{
    ((TransformOps*)(void*)((char*)this + 0x90))->FUN_00537dc0(t0);
    void* dst = (char*)this + 0xc8;
    ((TransformOps*)dst)->FUN_00537dc0(t1);

    float py0 = m84, py1 = m88, py2 = m8c;   // saved previous position (xmm3/4/5)

    float x = *(float*)((char*)this + 0x94);
    float y = *(float*)((char*)this + 0x98);
    float z = *(float*)((char*)this + 0x9c);
    m84 = x; m88 = y; m8c = z;

    void* mc8p = (char*)this + 0xc8;
    if ((*(u8_s00a9_3cf0*)mc8p & 2) != 0) {
        // rotate the local vector by the 3x3 matrix at mc8+0x14
        float* M = (float*)((char*)mc8p + 0x14);
        float ox = m84, oy = m88, oz = m8c;
        float nx = M[3] * oy + M[6] * oz + ox * M[0];
        float ny = M[1] * ox + M[4] * oy + M[7] * oz;
        float nz = M[2] * ox + M[5] * oy + M[8] * oz;
        m84 = nx; m88 = ny; m8c = nz;
    }

    float s = *(float*)((char*)mc8p + 0x10);
    m84 = m84 * s;
    m88 = m88 * s;
    m8c = m8c * s;

    float tx = *(float*)((char*)mc8p + 4);
    float ty = *(float*)((char*)mc8p + 8);
    float tz = *(float*)((char*)mc8p + 0xc);
    m84 = tx + m84;
    m88 = ty + m88;
    m8c = tz + m8c;

    float dx = m84 - py0;
    float dy = m88 - py1;
    float dz = m8c - py2;

    float chk = m68;
    if (chk != g_1565198 && chk != -g_1565198) {
        m68 = chk + dx;
        m6c = m6c + dy;
        m70 = m70 + dz;
        m74 = m74 + dx;
        m78 = m78 + dy;
        m7c = m7c + dz;
    }
}

// @ 0x00a94b70
void CAbil::FUN_00a94b70(void* desc)
{
    m1c = desc;
    ((CAbil*)((char*)this - 4))->FUN_00a943a0();
}

// @ 0x00a94b90
void cEffectSpawner::ResetParticle(cParticle* particle)
{
    particle->mAge = 0.0f;

    cSpawnerDesc* desc = mpDesc;
    double lo = desc->mLifeMin;
    double hi = desc->mLifeMax;
    double r = gRandomGlobal.RandomDouble();
    double v = r * (hi - lo) + lo;
    if (v < hi) {
        if (v < lo)
            v = lo;
    } else {
        v = hi;
    }
    particle->mLife = v * mLifeScale;

    particle->mPosition = RandomVector3(&mSpawnRange);
    particle->mVelocity = RandomVector3(&desc->mVelocityRange);

    double slo = desc->mSpeedMin;
    double shi = desc->mSpeedMax;
    r = gRandomGlobal.RandomDouble();
    double speed = r * (shi - slo) + slo;
    if (speed < shi) {
        if (speed < slo)
            speed = slo;
    } else {
        speed = shi;
    }

    Vector3 dir = particle->mVelocity;
    float len2 = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
    if (len2 > 0.0f) {
        double k = speed * mSpeedScale / sqrt((double)len2);
        particle->mVelocity.x = (float)(dir.x * k);
        particle->mVelocity.y = (float)(dir.y * k);
        particle->mVelocity.z = (float)(dir.z * k);
    }

    cSpawnerDesc* attract = mpDesc;
    if (attract->mAttractRadius != 0.0f) {
        Vector3 delta;
        delta.x = particle->mPosition.x - attract->mAttractCenter.x;
        delta.y = particle->mPosition.y - attract->mAttractCenter.y;
        delta.z = particle->mPosition.z - attract->mAttractCenter.z;
        float dist2 = delta.z * delta.z + delta.y * delta.y + delta.x * delta.x;
        if (dist2 > 0.0f) {
            float k = (float)(attract->mAttractRadius / sqrt((double)dist2));
            Vector3 kick;
            kick.x = delta.x * k;
            kick.y = delta.y * k;
            kick.z = delta.z * k;
            particle->mVelocity.x = particle->mVelocity.x + kick.x;
            particle->mVelocity.y = particle->mVelocity.y + kick.y;
            particle->mVelocity.z = particle->mVelocity.z + kick.z;
        }
    }

    if (mTransform.mFlags & 2)
        particle->mPosition = Rotate(particle->mPosition, mTransform.mRotation);

    const float scale = mTransform.mScale;
    particle->mPosition.x = particle->mPosition.x * scale + mTransform.mTranslation.x;
    particle->mPosition.y = particle->mPosition.y * scale + mTransform.mTranslation.y;
    particle->mPosition.z = particle->mPosition.z * scale + mTransform.mTranslation.z;

    if (mTransform.mFlags & 2)
        particle->mVelocity = Rotate(particle->mVelocity, mTransform.mRotation);

    particle->mStreamIndex = mStreamCounter++;
    particle->mFlags = 0;
}

// @ 0x00a94fb0
void __cdecl StreamTrail(cParticlesEffect* effect, cITextureParticleRenderer* renderer, const u8_s00a9_4b90* offsets)
{
    cCurves* desc = effect->mpDesc;
    cParticle* particle = effect->mpParticlesFirst;
    int remaining = effect->mParticleCount;
    unsigned int lastColor = desc->mColorCurve.size() - 1;
    unsigned int lastAlpha = desc->mAlphaCurve.size() - 1;
    unsigned int lastSize = desc->mSizeCurve.size() - 1;

    while (remaining > 0) {
        char* buffer;
        int stride;
        int count = renderer->GetBuffer(remaining, &buffer, &stride);
        if (count == 0)
            return;
        remaining -= count;
        if (count > 0) {
            do {
                float t = particle->mAge / particle->mLife;
                float width = effect->mSizeScale * SampleCurve(desc->mSizeCurve.mpBegin, lastSize, t);
                Vector3 colour = SampleCurve(desc->mColorCurve.mpBegin, lastColor, t);
                Vector3 c;
                c.x = effect->mColorScale.x * colour.x;
                c.y = colour.y * effect->mColorScale.y;
                c.z = colour.z * effect->mColorScale.z;
                float alpha = effect->mAlphaScale * SampleCurve(desc->mAlphaCurve.mpBegin, lastAlpha, t);

                Vector3 pos = particle->mPosition;
                if (effect->mTransform.mFlags & 2)
                    pos = Rotate(pos, effect->mTransform.mRotation);
                const float scale = effect->mTransform.mScale;
                pos.x = effect->mTransform.mTranslation.x + pos.x * scale;
                pos.y = effect->mTransform.mTranslation.y + pos.y * scale;
                pos.z = effect->mTransform.mTranslation.z + pos.z * scale;

                u32_s00a9_4b90 r = ToByte(c.x);
                u32_s00a9_4b90 g = ToByte(c.y);
                u32_s00a9_4b90 b = ToByte(c.z);
                u32_s00a9_4b90 a = ToByte(alpha);
                u32_s00a9_4b90 packed = (((a << 8) | r) << 8 | g) << 8 | b;

                *(Vector3*)(buffer + offsets[0]) = pos;
                *(u32_s00a9_4b90*)(buffer + offsets[1]) = packed;
                *(float*)(buffer + offsets[2]) = effect->mTransform.mScale * width;

                buffer += stride;
                particle = particle->mpNext;
            } while (--count);
        }
        renderer->ReleaseAndDrawBuffer();
    }
}

// @ 0x00a954b0
void Stream_Quad(cParticlesEffect_s00a9_54b0* effect, cITextureParticleRenderer_s00a9_54b0* renderer, u8_s00a9_54b0* offsets)
{
    cParticlesDescription* desc = effect->mDesc;
    cParticle_s00a9_54b0* particle = effect->mParticlesFirst;
    int remaining = effect->mParticleCount;
    unsigned int lastColor = desc->mColorCurve.size() - 1;
    unsigned int lastAlpha = desc->mAlphaCurve.size() - 1;
    unsigned int lastSize = desc->mSizeCurve.size() - 1;

    u8_s00a9_54b0* buffer;
    int stride;
    while (remaining > 0) {
        int count = renderer->GetBuffer(remaining, &buffer, &stride);
        if (count == 0)
            return;
        remaining -= count;
        if (count > 0) {
            const Vector2 uv0 = { 0.0f, 0.0f };
            const Vector2 uv1 = { 1.0f, 0.0f };
            const Vector2 uv2 = { 1.0f, 1.0f };
            const Vector2 uv3 = { 0.0f, 1.0f };
            do {
                const float t = particle->mAge / particle->mLife;
                float size = effect->mSizeScale * SampleCurve_s00a9_54b0(desc->mSizeCurve.mpBegin, lastSize, t);
                float cx, cy, cz;
                SampleCurve_s00a9_54b0(desc->mColorCurve.mpBegin, lastColor, t, cx, cy, cz);
                Vector3 c;
                c.x = effect->mColorScale.x * cx;
                c.y = cy * effect->mColorScale.y;
                c.z = cz * effect->mColorScale.z;
                float alpha = effect->mAlphaScale * SampleCurve_s00a9_54b0(desc->mAlphaCurve.mpBegin, lastAlpha, t);

                Vector3 pos = particle->mPosition;
                if (effect->mTransform.mFlags & 2)
                    pos = Rotate_s00a9_54b0(pos, effect->mTransform.mRotation);
                const float scale = effect->mTransform.mScale;
                Vector4 v;
                v.x = effect->mTransform.mTranslation.x + pos.x * scale;
                v.y = effect->mTransform.mTranslation.y + pos.y * scale;
                v.z = effect->mTransform.mTranslation.z + pos.z * scale;
                v.w = t;

                Vector3 vel = particle->mVelocity;
                if (effect->mTransform.mFlags & 2)
                    vel = Rotate_s00a9_54b0(vel, effect->mTransform.mRotation);
                Vector4 n;
                n.x = vel.x * scale;
                n.y = vel.y * scale;
                n.z = vel.z * scale;
                n.w = effect->mTransform.mScale * size;

                u8_s00a9_54b0 r = ColorToByte(c.x);
                u8_s00a9_54b0 g = ColorToByte(c.y);
                u8_s00a9_54b0 b = ColorToByte(c.z);
                u8_s00a9_54b0 a = ColorToByte(alpha);
                u32_s00a9_54b0 color = ((((u32_s00a9_54b0)a << 8 | r) << 8 | g) << 8) | b;

                *(Vector4*)(buffer + offsets[0]) = v;
                *(Vector4*)(buffer + offsets[1]) = n;
                *(u32_s00a9_54b0*)(buffer + offsets[2]) = color;
                *(Vector2*)(buffer + offsets[3]) = uv0;
                buffer += stride;
                *(Vector4*)(buffer + offsets[0]) = v;
                *(Vector4*)(buffer + offsets[1]) = n;
                *(u32_s00a9_54b0*)(buffer + offsets[2]) = color;
                *(Vector2*)(buffer + offsets[3]) = uv1;
                buffer += stride;
                *(Vector4*)(buffer + offsets[0]) = v;
                *(Vector4*)(buffer + offsets[1]) = n;
                *(u32_s00a9_54b0*)(buffer + offsets[2]) = color;
                *(Vector2*)(buffer + offsets[3]) = uv2;
                buffer += stride;
                *(Vector4*)(buffer + offsets[0]) = v;
                *(Vector4*)(buffer + offsets[1]) = n;
                *(u32_s00a9_54b0*)(buffer + offsets[2]) = color;
                *(Vector2*)(buffer + offsets[3]) = uv3;
                buffer += stride;
                particle = particle->mpNext;
            } while (--count);
        }
        renderer->ReleaseAndDrawBuffer();
    }
}

// @ 0x00a95d30
void __cdecl WriteParticleQuads(Effect* fx, VertexSink* sink, const uint8_t* off)
{
    EffectDesc* d = fx->mpDesc;
    Particle* node = fx->mpParticles;
    int remaining = fx->mCount;
    unsigned nColor = (unsigned)(d->color.mpEnd - d->color.mpBegin) - 1;
    unsigned nAlpha = (unsigned)(d->alpha.mpEnd - d->alpha.mpBegin) - 1;
    unsigned nSize = (unsigned)(d->size.mpEnd - d->size.mpBegin) - 1;

    while (remaining > 0) {
        char* base;
        int stride;
        int n = sink->Fetch(remaining, &base, &stride);
        if (n == 0)
            return;
        remaining -= n;
        for (int k = n; k > 0; --k) {
            float t = node->age / node->life;

            float sz = fx->sizeScale * SampleFloat(d->size, nSize, t);

            Vec3 col = SampleVec3(d->color, nColor, t);
            float cr = fx->colorScale[0] * col.x;
            float cg = col.y * fx->colorScale[1];
            float cb = col.z * fx->colorScale[2];

            float al = fx->alphaScale * SampleFloat(d->alpha, nAlpha, t);

            Vec3 a = node->a;
            Vec3 b = node->b;
            if (fx->mFlags & 2)
                a = fx->mat.Mul(a);
            float s = fx->scale;
            Vec4 pos = { fx->origin[0] + a.x * s, fx->origin[1] + a.y * s, fx->origin[2] + a.z * s, t };

            if (fx->mFlags & 2)
                b = fx->mat.Mul(b);
            Vec4 att = { b.x * fx->scale, b.y * fx->scale, b.z * fx->scale, fx->scale * sz };

            uint32_t r = ToByte_s00a9_5d30(cr);
            uint32_t g = ToByte_s00a9_5d30(cg);
            uint32_t bl = ToByte_s00a9_5d30(cb);
            uint32_t aa = ToByte_s00a9_5d30(al);
            uint32_t color = (((aa << 8 | r) << 8 | g) << 8) | bl;
            uint32_t uvw = _rotr(node->uv, 8);

            WriteVertex(base, off, pos, att, color, uvw);
            base += stride;
            WriteVertex(base, off, pos, att, color, uvw | 0xff0000);
            base += stride;
            WriteVertex(base, off, pos, att, color, uvw | 0xffff00);
            base += stride;
            WriteVertex(base, off, pos, att, color, uvw | 0xff00);
            base += stride;
            node = node->next;
        }
        sink->Flush();
    }
}

// @ 0x00a96520
void __cdecl WriteParticleQuadsUV(Effect* fx, VertexSink* sink, const uint8_t* off)
{
    EffectDesc* d = fx->mpDesc;
    Particle* node = fx->mpParticles;
    int remaining = fx->mCount;
    unsigned nColor = (unsigned)(d->color.mpEnd - d->color.mpBegin) - 1;
    unsigned nAlpha = (unsigned)(d->alpha.mpEnd - d->alpha.mpBegin) - 1;
    unsigned nSize = (unsigned)(d->size.mpEnd - d->size.mpBegin) - 1;

    (void)nSize;

    // Four corners of the billboard in the order (0,0) (1,0) (1,1) (0,1). This variant's vertex
    // format is position (3 floats), packed ARGB and a float2 texture coordinate -- there is no
    // attribute vector, so the particle's second vector (and the size curve) are not consumed.
    float uv[4][2] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

    while (remaining > 0) {
        char* base;
        int stride;
        int n = sink->Fetch(remaining, &base, &stride);
        if (n == 0)
            return;
        remaining -= n;
        for (int k = n; k > 0; --k) {
            float t = node->age / node->life;

            Vec3 col = SampleVec3(d->color, nColor, t);
            float cr = col.x * fx->colorScale[0];
            float cg = col.y * fx->colorScale[1];
            float cb = col.z * fx->colorScale[2];

            float al = fx->alphaScale * SampleFloat(d->alpha, nAlpha, t);

            Vec3 a = node->a;
            if (fx->mFlags & 2)
                a = fx->mat.Mul(a);
            Vec3 pos(fx->origin[0] + a.x * fx->scale,
                     fx->origin[1] + a.y * fx->scale,
                     fx->origin[2] + a.z * fx->scale);

            uint32_t r = ToByte_s00a9_5d30(cr);
            uint32_t g = ToByte_s00a9_5d30(cg);
            uint32_t b = ToByte_s00a9_5d30(cb);
            uint32_t aa = ToByte_s00a9_5d30(al);
            uint32_t color = (((aa << 8 | r) << 8 | g) << 8) | b;

            WriteVertexUV(base, off, pos, color, uv[0]);
            base += stride;
            WriteVertexUV(base, off, Vec3(pos.x + 1.0f, pos.y, pos.z), color, uv[1]);
            base += stride;
            WriteVertexUV(base, off, Vec3(pos.x + 1.0f, pos.y, pos.z + 1.0f), color, uv[2]);
            base += stride;
            WriteVertexUV(base, off, Vec3(pos.x, pos.y, pos.z + 1.0f), color, uv[3]);
            base += stride;
            node = node->next;
        }
        sink->Flush();
    }
}

// @ 0x00a96b70
int __cdecl CreateSwarmEffect(int arg)
{
    void* p = AllocMem(0x198, "Swarm", 0, 0, 0, 0);
    if (p) {
        int r = ((SwarmAlloc*)p)->Init(arg);
        if (r)
            return r + 4;
    }
    return 0;
}

// @ 0x00a96bb0
void __cdecl RegisterSwarmVtables(char enable)
{
    if (enable) {
        MemZero(gpSwarmVtbl, 0, 0x80);
        gpSwarmVtbl[0] = (void*)0x00a96520;
        gpSwarmVtbl[1] = (void*)0x00a94fb0;
        gpSwarmVtbl[2] = (void*)0x00a954b0;
        gpSwarmVtbl[3] = (void*)0x00a95d30;
    }
}

// @ 0x00a96c00
void SwarmEffectBase::ClearParticles()
{
    SwarmNode* node = mHead.mpNext;
    while (node != &mHead) {
        SwarmNode* prev = node->mpPrev;
        SwarmNode* next = node->mpNext;
        prev->mpNext = next;
        next->mpPrev = prev;
        node->mpNext = 0;
        node->mpPrev = 0;
        --mnCount;
        SwarmNode* dead = node;
        node = next;
        dead->mpNext = gpFreeParticles;
        gpFreeParticles = dead;
    }
    for (node = mHead.mpNext; node != &mHead; ) {
        SwarmNode* next = node->mpNext;
        node->mpPrev = 0;
        node->mpNext = 0;
        node = next;
    }
    mHead.mpNext = &mHead;
    mHead.mpPrev = &mHead;
}

// @ 0x00a96c60
void SwarmEffect::Release(int bRelease)
{
    if (mbActive) {
        bool pause = (bRelease == 0);
        mbPaused = pause;
        if (!pause) {
            mbActive = pause;
            ((SwarmEffectBase*)((char*)this - 4))->ClearParticles();
            if (mnOwnerIndex >= 0) {
                void* owner = mpOwner;
                void* obj = ((void* (__thiscall*)(void*))((void**)*(void**)owner)[8])(owner);
                ((void (__thiscall*)(void*, int, int))((void**)*(void**)obj)[9])(obj, mnOwnerIndex, 0);
            }
        }
    }
}

// @ 0x00a978d0
void SwarmCtrl::Update(float dt, float param3, UpdateCtx* ctx)
{
	Desc1c* d;

	if (mb34 == 0) {
		if (mw10e < mw10c) {
			ctx->mn14 += (int)(mw10c - mw10e) * mn18;
			mw10e = mw10c;
		}
	} else {
		dt = mp1c->mf14 + dt;
		mb34 = 0;
	}

	if (dt < 0.0f)
		return;

	d = mp1c;
	if (((d->mFlags >> 10) & 1) != 0 && mb0d == 0) {
		float f = (float)((1.0 - mTimeD) * d->mf74 - 0.01);
		float keep = 0.0f;
		if (f <= 0.0f || (keep = f, f < dt))
			dt = keep;
	}

	float fz = mWorld.z;
	float fy = mWorld.y;
	float fx = mWorld.x;
	float dz = fz - mLastTeleport.z;
	float dy = fy - mLastTeleport.y;
	float dx = fx - mLastTeleport.x;
	if (g_fTeleportThreshold < (dz * dz + dy * dy) + dx * dx) {
		mLastTeleport.x = fx;
		mLastTeleport.y = fy;
		mLastTeleport.z = fz;
	}

	mf148 = ((mf114 - mf110) * param3 + mf110) * mf12c;
	mn154 = mn13c;
	mn158 = mn140;
	mf150 = ((mf124 - mf120) * param3 + mf120) * mf138;
	mn15c = mn144;
	mf14c = ((mf11c - mf118) * param3 + mf118) * mf134;

	Desc24* av;
	if ((d->mFlags & 1) == 0 && ((d->mFlags >> 1) & 1) == 0) {
		av = mp24;
	} else {
		av = mp24;
		if (*d->mp60 <= (float)(int)av->mf08)
			goto LAB_ae9;
	}
	mf148 = mf148 * av->mf00;

LAB_ae9:
	{
		Desc1c* p = mp1c;
		mTimeD = (double)(dt + (float)mTimeD);

		float vF4 = p->mfF4;
		float tD8 = av->mfD8;
		float tDC = av->mfDC;
		float tE0 = av->mfE0;
		mPos.x = tD8 * vF4;
		mPos.y = tDC * vF4;
		mPos.z = tE0 * vF4;

		float vF0 = p->mfF0;
		float tBC = av->mfBC;
		float tC0 = av->mfC0;
		float tC4 = av->mfC4;
		mPos.x = tBC * vF0 + mPos.x;
		mPos.y = tC0 * vF0 + mPos.y;
		mPos.z = tC4 * vF0 + mPos.z;

		((void(__thiscall*)(void*, void*))FUN_00a78e90)(&mXform, &mPos);

		p = mp1c;
		mPos.y = p->mfE8 + mPos.y;
		mPos.x = p->mfE4 + mPos.x;
		mPos.z = p->mfEC + mPos.z;

		mBoundsMin.x = g_fBoundsInit;
		mBoundsMin.y = g_fBoundsInit;
		mBoundsMin.z = g_fBoundsInit;
		float neg = -g_fBoundsInit;
		mBoundsMax.x = neg;
		mBoundsMax.y = neg;
		mBoundsMax.z = neg;

		SwarmNode_s00a9_78d0* end = (SwarmNode_s00a9_78d0*)((char*)this + 0x10);
		SwarmNode_s00a9_78d0* node = mpNext;
		while (node != end) {
			float cur = node->mf08;
			node->mf08 = cur + dt;
			if (node->mf0c <= cur + dt) {
				SwarmNode_s00a9_78d0* prev = node->mpPrev;
				SwarmNode_s00a9_78d0* next = node->mpNext;
				prev->mpNext = next;
				next->mpPrev = prev;
				node->mpNext = 0;
				node->mpPrev = 0;
				--mn18;
				node->mpNext = g_pNodeFreeList;
				g_pNodeFreeList = node;
				node = next;
			} else {
				float m20 = node->mf20;
				float px = mPos.x;
				float pz = mPos.z;
				float m1c = node->mf1c;
				Desc1c* p2 = mp1c;
				float m24 = node->mf24;
				float n20 = mPos.y * dt + node->mf20;
				node->mf20 = n20;
				float n24 = node->mf24 + pz * dt;
				node->mf24 = n24;
				float n1c = m1c + px * dt;
				node->mf1c = n1c;
				float damp = 1.0f - p2->mf108 * dt;
				float d1c = damp * n1c;
				node->mf1c = d1c;
				float d24 = damp * n24;
				node->mf24 = d24;
				float d20 = damp * n20;
				node->mf20 = d20;
				float half = dt * 0.5f;
				float v10 = node->mf10 + (d1c + m1c) * half;
				node->mf18 = (d24 + m24) * half + node->mf18;
				node->mf10 = v10;
				node->mf14 = (d20 + m20) * half + node->mf14;
				if (v10 < mBoundsMin.x)
					mBoundsMin.x = v10;
				float q = node->mf10;
				if (mBoundsMax.x <= q && q != mBoundsMax.x)
					mBoundsMax.x = q;
				if (node->mf14 < mBoundsMin.y)
					mBoundsMin.y = node->mf14;
				q = node->mf14;
				if (mBoundsMax.y <= q && q != mBoundsMax.y)
					mBoundsMax.y = q;
				if (node->mf18 < mBoundsMin.z)
					mBoundsMin.z = node->mf18;
				q = node->mf18;
				if (mBoundsMax.z <= q && q != mBoundsMax.z)
					mBoundsMax.z = q;
				node = node->mpNext;
			}
		}
	}

	if (mb0d == 0)
		((void(__thiscall*)(void*, float))FUN_00a97830)((void*)((char*)this - 4), dt);

	((void(__thiscall*)(void*, void*))FUN_006e95a0)(&mBoundsMin, &mXform);

	if (mn184 >= 0) {
		float fv = mXform.mf10;
		float f80 = mf80;
		float f14c = mf14c;
		void* mgr = mp20;
		void* q = (*(void*(__thiscall**)(void*))(*(char**)mgr + 0x20))(mgr);
		(*(void(__thiscall**)(void*, int, void*, float))(*(char**)q + 0x20))(q, mn184, &mBoundsMin, (fv * f80) * f14c);
	}

	if (mn18 == 0 && mb0d != 0) {
		mb0c = 0;
		if (mn184 >= 0) {
			void* mgr = mp20;
			void* q = (*(void*(__thiscall**)(void*))(*(char**)mgr + 0x20))(mgr);
			(*(void(__thiscall**)(void*, int, int))(*(char**)q + 0x24))(q, mn184, 0);
			return;
		}
	} else {
		mLastTeleport.x = fx;
		mLastTeleport.y = fy;
		mLastTeleport.z = fz;
		ctx->mn10 += mn18;
	}
}

// @ 0x00a97f50
void* EffectObjA::Destroy(char freeSelf)
{
	int begin = mnBegin;
	if (mnEnd - begin > 1 && begin != 0)
		operator_delete((void*)begin);

	mpVtbl = (void*)vtable_IEvent;

	if ((freeSelf & 1) != 0)
		operator_delete(this);
	return this;
}

// @ 0x00a97f90
void FUN_00a97f90(void* stream, int unusedVersion, SwarmDesc* desc)
{
	u32_s00a9_78d0 tmp;

	EA_IO_ReadInt32(stream, &tmp, 1, 0);
	desc->mn08 = tmp & 0x3ff;

	EA_IO_ReadInt32(stream, &desc->mn0c, 1, 0);
	EA_IO_ReadInt32(stream, &desc->mn10, 1, 0);
	EA_IO_ReadInt32(stream, &desc->mn14, 1, 0);

	EA_IO_ReadInt32(stream, &desc->mn18, 1, 0);
	EA_IO_ReadInt32(stream, &desc->mn1c, 1, 0);
	EA_IO_ReadString16(stream, &desc->mStr);
	EA_IO_ReadInt32(stream, &desc->mf30, 1, 0);
}

// @ 0x00a98480
void* FUN_00a98480(void* stream, int version)
{
	SwarmDesc* obj = 0;
	SwarmDesc* p = (SwarmDesc*)operator_new(0x34, "Swarm", 0, 0, 0, 0);
	if (p != 0) {
		p->mn04 = 0;
		p->mpVtbl = (void*)vtable_SwarmDesc;
		p->mn08 = 0;
		p->mn0c = 0;
		p->mn10 = 0;
		p->mn14 = 0;
		p->mn18 = 0;
		p->mn1c = 0;
		p->mStr.mpBegin = gEmptyString16;
		p->mStr.mpEnd = gEmptyString16;
		p->mStr.mCapacity = (u32_s00a9_78d0)gEmptyString16Cap;
		p->mf30 = 0.0f;
		obj = p;
	}
	FUN_00a97f90(stream, version, obj);
	return obj;
}

// @ 0x00a984f0
void FUN_00a984f0()
{
	g_1676018 = (void*)FUN_00a983d0;
	g_167601c = (void*)FUN_00a98480;
	g_1676028 = 1;
	g_167602c = 1;
}

// @ 0x00a99040
void LightEffectSub_Read(void* stream, int n, LightEffectSub* self)
{
    unsigned char* s = (unsigned char*)self;
    unsigned int tmp;
    Sub_ReadInt32(stream, &tmp, 1, 0);
    *(int*)(s + 0x08) = (int)(tmp & 0xf);
    Sub_ReadInt8(stream, s + 0x0c, 1);
    if (n > 1) {
        Sub_ReadInt32(stream, s + 0x10, 1, 0);
        Sub_ReadByte(stream, s + 0x14, 1, 0);
    }
    Sub_ReadVec0C(stream, s + 0x18);
    Sub_ReadFVec(stream, s + 0x2c);
    Sub_ReadFVec(stream, s + 0x40);
    Sub_ReadInt32(stream, s + 0x54, 1, 0);
}

// @ 0x00a990d0
LightEffectSub* LightEffectSub_CreateAndRead(void* stream, int n)
{
    unsigned char* p = (unsigned char*)EAAllocate(0x58, g_str_Swarm, 0, 0, 0, 0);
    unsigned char* sub = 0;
    if (p) {
        *(int*)(p + 0x04)   = 0;
        *(void**)p          = (void*)&g_vtbl_LightEffectSub;
        *(int*)(p + 0x08)   = 0;
        *(float*)(p + 0x10) = 1.0f;
        *(p + 0x0c)         = 1;
        *(short*)(p + 0x14) = 0;
        *(int*)(p + 0x18)   = 0;
        *(int*)(p + 0x1c)   = 0;
        *(int*)(p + 0x20)   = 0;
        *(int*)(p + 0x2c)   = 0;
        *(int*)(p + 0x30)   = 0;
        *(int*)(p + 0x34)   = 0;
        *(int*)(p + 0x40)   = 0;
        *(int*)(p + 0x44)   = 0;
        *(int*)(p + 0x48)   = 0;
        *(float*)(p + 0x54) = 0.0f;
        sub = p;
    }
    LightEffectSub_Read(stream, n, (LightEffectSub*)sub);
    return (LightEffectSub*)sub;
}

// @ 0x00a99190
Elem1C* Elem1C_copy_range(Elem1C* dst, Elem1C* first, Elem1C* last)
{
    Elem1C* s = first;
    if (s != last) {
        Elem1C* d = dst;
        do {
            if (d) {
                d->w[0]=s->w[0]; d->w[1]=s->w[1]; d->w[2]=s->w[2];
                d->w[3]=s->w[3]; d->w[4]=s->w[4]; d->w[5]=s->w[5]; d->w[6]=s->w[6];
            }
            ++s; ++d;
        } while (s != last);
    }
    return dst;
}

// @ 0x00a991f0
Elem1C* Elem1C_fill(Elem1C* dst, unsigned int n, const Elem1C* v)
{
    if (n && dst) {
        Elem1C* d = dst;
        do {
            d->w[0]=v->w[0]; d->w[1]=v->w[1]; d->w[2]=v->w[2];
            d->w[3]=v->w[3]; d->w[4]=v->w[4]; d->w[5]=v->w[5]; d->w[6]=v->w[6];
            --n; ++d;
        } while (n);
    }
    return dst;
}

// @ 0x00a99240
Elem1C* Elem1C_fill_off14(Elem1C* dst, unsigned int n, const Elem1C* v)
{
    if (n && dst) {
        float* src = (float*)v;
        Elem1C* d = dst;
        do {
            d->w[0]=src[0]; d->w[1]=src[1]; d->w[2]=src[2];
            d->w[3]=src[3]; d->w[4]=src[4]; d->w[5]=src[5]; d->w[6]=src[6];
            --n; ++d;
        } while (n);
    }
    return dst;
}

// @ 0x00a99290
void* Elem1C_write_vector(void* stream, Elem1CVec* vec)
{
    int n = (int)(((char*)vec->mpEnd - (char*)vec->mpBegin) / 0x1c);
    EA_IO_WriteUint32(stream, (const unsigned int*)&n, 1, 0);
    if (n) {
        int off = 0;
        int c = n;
        do {
            Elem1C_Write1(stream, (char*)vec->mpBegin + off);
            off += 0x1c;
            --c;
        } while (c);
    }
    return stream;
}

// @ 0x00a992f0
void* Elem1C_write_vector2(void* stream, Elem1CVec* vec)
{
    int n = (int)(((char*)vec->mpEnd - (char*)vec->mpBegin) / 0x1c);
    EA_IO_WriteUint32(stream, (const unsigned int*)&n, 1, 0);
    if (n) {
        int off = 0;
        int c = n;
        do {
            Elem1C_Write2(stream, (char*)vec->mpBegin + off);
            off += 0x1c;
            --c;
        } while (c);
    }
    return stream;
}

// @ 0x00a99410
void Elem1C_insert(Elem1CVec* vec, Elem1C* pos, unsigned int n, const Elem1C* v)
{
    unsigned int cap = (unsigned int)(((char*)vec->mpCapacity - (char*)vec->mpBegin) / 0x1c);
    if (cap < n) {
        // grow
        unsigned int oldN = (unsigned int)(((char*)vec->mpEnd - (char*)vec->mpBegin) / 0x1c);
        unsigned int newCap = oldN * 2;
        if (oldN == 0) newCap = 1;
        unsigned int want = oldN + n;
        if (want > newCap) newCap = want;
        char* p = (char*)EAAllocate(newCap * 0x1c, "EASTL", 0, 0, 0, 0xd1);
        Elem1C* q = Elem1C_copy_range((Elem1C*)p, vec->mpBegin, pos);
        Elem1C_fill(q, n, v);
        Elem1C* r = Elem1C_copy_range(q + n, pos, vec->mpEnd);
        if (vec->mpBegin && *(int*)((char*)vec->mpBegin - 4) != 0)
            operator_delete(vec->mpBegin);
        vec->mpBegin = (Elem1C*)p;
        vec->mpEnd = r;
        vec->mpCapacity = (Elem1C*)(p + newCap * 0x1c);
        return;
    }

    if (n == 0) return;

    unsigned int rem = (unsigned int)(((char*)vec->mpEnd - (char*)pos) / 0x1c);
    unsigned int nn = n;
    Elem1C tmp = *v;

    if (nn < rem) {
        char* dstBase = (char*)vec->mpEnd - nn * 0x1c;
        Elem1C* r = Elem1C_ctor_range(0, (Elem1C*)dstBase, vec->mpEnd, vec->mpEnd);
        (void)r;
        unsigned int off = nn * 0x1c;
        vec->mpEnd = (Elem1C*)((char*)vec->mpEnd + off);
        Elem1C_Dtor((char*)pos, dstBase, vec->mpEnd);
        unsigned int n2 = n * 0x1c;
        Elem1C_DtorAndFill(pos, (char*)pos + n2, &tmp);
        return;
    }

    // nn >= rem
    unsigned int extra = nn - rem;
    Elem1C_fill(vec->mpEnd, extra, &tmp);
    vec->mpEnd = (Elem1C*)((char*)vec->mpEnd + extra * 0x1c);
    {
        Elem1C* dst = vec->mpEnd;
        Elem1C* o = pos;
        unsigned int m = rem;
        do {
            if (dst) *dst = *o;
            ++dst; ++o;
        } while (--m);
        vec->mpEnd = (Elem1C*)((char*)vec->mpEnd + rem * 0x1c);
    }
    Elem1C_DtorAndFill(pos, (char*)pos + rem * 0x1c, &tmp);
}

// @ 0x00a99640
void RecVec::insert(Rec7* pos, uint32_t n, const Rec7& v)
{
    uint32_t freeSlots = capacity() - size();
    if (n > freeSlots) {
        uint32_t old = size();
        uint32_t cap = old * 2;
        if (old == 0)
            cap = 1;
        uint32_t need = old + n;
        if (need > cap)
            cap = need;
        Rec7* nw = cap ? (Rec7*)eastl_alloc_counted(cap * 0x1c) : 0;
        Rec7* mid = CopyRec7(mpBegin, pos, nw);
        AllocCopy(mid, n, &v, pos);
        Rec7* tail = CopyRec7(pos, mpEnd, mid + n);
        FreeCounted(mpBegin);
        mpBegin = nw;
        mpEnd = tail;
        mpCap = nw + cap;
    } else if (n) {
        Rec7 tmp = v;
        uint32_t room = (uint32_t)((char*)mpEnd - (char*)pos) / 0x1c;
        if (n < room) {
            Rec7* split = mpEnd - n;
            RotateCopy2(split, mpEnd, mpEnd);
            Rec7* e = mpEnd;
            mpEnd += n;
            Rec7_ShiftBack(pos, split, e);
            FillRec7(pos, (Rec7*)((char*)pos + n * 0x1c), &tmp);
        } else {
            uint32_t extra = n - room;
            AllocCopy(mpEnd, extra, &tmp, pos);
            Rec7* e = mpEnd;
            mpEnd += extra;
            RotateCopy2(pos, e, mpEnd);
            mpEnd += room;
            FillRec7(pos, e, &tmp);
        }
    }
}

// @ 0x00a99870
cEffectParams::~cEffectParams()
{
    FreeCounted(v2a8.mpBegin);
    FreeCounted(v28c.mpBegin);
    FreeCounted(v250.mpBegin);
    FreeCounted(v21c.mpBegin);
    v1b0.Clear();
    FreeCounted(v1b0.mpBegin);
    FreeCounted(v19c.mpBegin);
    FreeCounted(v188.mpBegin);
    FreeCounted(v170.mpBegin);
    FreeCounted(v110.mpBegin);
    FreeCounted(vf0.mpBegin);
    FreeCounted(vc4.mpBegin);
    FreeCounted(vb0.mpBegin);
    FreeCounted(v9c.mpBegin);
    FreeCounted(v84.mpBegin);
    FreeCounted(v68.mpBegin);
    SetVtbl((void*)0x13ef094);
}

// @ 0x00a99a10
void RecVec::resize(uint32_t n)
{
    if (size() < n) {
        uint32_t extra = n - size();
        Rec7 tmp;
        UninitialisedFill(mpEnd, extra, &tmp);   // member helper bumps mpEnd internally
    } else {
        DestroyRangeRec7(mpBegin + n, mpEnd);
        mpEnd = mpBegin + n;
    }
}

// @ 0x00a99a90
void RecVec::resizeZero(uint32_t n)
{
    if (size() < n) {
        Rec7 tmp;
        tmp.w0=0; tmp.w1=0; tmp.w2=0; tmp.w3=0; tmp.w4=0; tmp.w5=0; tmp.w6=0;
        insert(mpEnd, n - size(), tmp);
    } else {
        DestroyRangeRec7(mpBegin + n, mpEnd);
        mpEnd = mpBegin + n;
    }
}

// @ 0x00a99b20
cEffectParams::cEffectParams()
{
    i08 = 0; i0c = 0;
    f10 = 2.0f; f14 = 2.0f; f18 = 0.0f;
    f1c = -1.0f; f20 = -1.0f; f24 = -1.0f; f28 = -1.0f;
    f2c = 0.0f; f30 = 0.0f; f34 = 1.0f; f38 = 0.0f; f3c = 0.0f; f40 = 1.0f;
    f44 = 0.0f; f48 = 0.0f; f4c = 0.0f; f50 = 0.0f; f54 = 0.0f; f58 = 0.0f; f5c = 0.0f; f60 = 0.0f;
    f64 = -1.0f;
    v68.Init();
    f7c = 1.0f;
    i80 = 0;
    v84.Init();
    f98 = 0.0f;
    v9c.Init(); vb0.Init(); vc4.Init();
    fd8 = 0.0f; fdc = 0.0f; fe0 = 0.0f; fe4 = 0.0f; fe8 = 0.0f; fec = 0.0f;
    vf0.Init();
    v104.x = g_vec3_01678e1c.x; v104.y = g_vec3_01678e1c.y; v104.z = g_vec3_01678e1c.z;
    v110.Init();
    f124 = 0.0f;
    i128 = -1; i12c = 0; i130 = -1;
    b134 = 0;
    v138.x = g_vec3_01678e1c.x; v138.y = g_vec3_01678e1c.y; v138.z = g_vec3_01678e1c.z;
    v144.x = g_vec3_01678e1c.x; v144.y = g_vec3_01678e1c.y; v144.z = g_vec3_01678e1c.z;
    f150 = 0.0f; f154 = 0.0f; f158 = 0.0f;
    v15c.x = g_vec3_01678e1c.x; v15c.y = g_vec3_01678e1c.y; v15c.z = g_vec3_01678e1c.z;
    f168 = 0.0f; f16c = 0.0f;
    v170.mpBegin = 0; v170.mpEnd = 0; v170.mpCap = 0;
    b184 = 0; b185 = (char)0xff; b186 = 0; b187 = (char)0xff;
    v188.mpBegin = 0; v188.mpEnd = 0; v188.mpCap = 0;
    v19c.mpBegin = 0; v19c.mpEnd = 0; v19c.mpCap = 0;
    v1b0.mpBegin = 0; v1b0.mpEnd = 0; v1b0.mpCap = 0;
    f1d8 = -1000000000.0f;
    f1c4 = 1.0f; f1c8 = 0.0f; f1cc = 0.0f; f1d0 = 0.0f; f1d4 = 0.0f;
    f1dc = 0.0f; f1e0 = -10000.0f; f1e4 = 10000.0f;
    i1e8 = -1; i1ec = -1; i1f0 = -1; i1f4 = -1; i1f8 = -1; i1fc = -1;
    f200 = 5.0f; f204 = 5.0f; f208 = 0.0f; f20c = 0.0f; f210 = 0.25f; f214 = 0.0f; f218 = 0.0f;
    v21c.mpBegin = 0; v21c.mpEnd = 0; v21c.mpCap = 0;
    f234 = 5.0f; f238 = 5.0f;
    b230 = 2;
    f23c = 0.0f; f240 = 0.0f; f244 = 0.25f; f248 = 0.0f; f24c = 0.0f;
    v250.mpBegin = 0; v250.mpEnd = 0; v250.mpCap = 0;
    b264 = 2;
    v268.x = g_vec3_01678e1c.x; v268.y = g_vec3_01678e1c.y; v268.z = g_vec3_01678e1c.z;
    f274 = 0.0f; f278 = 0.0f; f27c = 0.0f;
    v280.x = g_vec3_01678e1c.x; v280.y = g_vec3_01678e1c.y; v280.z = g_vec3_01678e1c.z;
    v28c.mpBegin = 0; v28c.mpEnd = 0; v28c.mpCap = 0;
    f2a0 = 1.0f; f2a4 = 0.0f;
    v2a8.mpBegin = 0; v2a8.mpEnd = 0; v2a8.mpCap = 0;
    f2bc = 0.0f;

    v68.push_back(30.0f);
    Vec3f d = g_vec3_01678dd0;
    vf0.push_back(d);
    v110.push_back(1.0f);
    v84.push_back(1.0f);
    v9c.push_back(0.0f);
    vb0.push_back(0.0f);
    vc4.push_back(0.0f);
}

// @ 0x00a9a930
void __cdecl FUN_00a9a930(cStream* s, int version, void* obj)
{
    char* o = (char*)obj;
    int   tmp;

    ReadInt32(s, &tmp, 1, 0);
    *(int*)(o + 0x8) = 0;
    *(unsigned int*)(o + 0xc) = tmp & 0xff;
    ReadInt32(s, &tmp, 1, 0);
    *(unsigned int*)(o + 0x8) |= tmp;

    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x10, 8);
    ReadInt32(s, o + 0x18, 1, 0);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x1c, 8);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x24, 8);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x2c, 0xc);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x38, 0xc);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x44, 8);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x4c, 0xc);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x58, 0xc);
    ReadInt32(s, o + 0x64, 1, 0);
    FUN_007d27d0(s, o + 0x68);
    ReadInt32(s, o + 0x7c, 1, 0);
    ReadInt32(s, o + 0x80, 1, 0);
    FUN_007d27d0(s, o + 0x84);
    ReadInt32(s, o + 0x98, 1, 0);
    FUN_007d27d0(s, o + 0x9c);
    FUN_007d27d0(s, o + 0xb0);
    FUN_007d27d0(s, o + 0xc4);
    ReadInt32(s, o + 0xd8, 1, 0);
    ReadInt32(s, o + 0xdc, 1, 0);
    ReadInt32(s, o + 0xe0, 1, 0);
    ReadInt32(s, o + 0xe4, 1, 0);
    ReadInt32(s, o + 0xe8, 1, 0);
    ReadInt32(s, o + 0xec, 1, 0);
    FUN_007ed920(s, o + 0xf0);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x104, 0xc);
    FUN_007d27d0(s, o + 0x110);
    ReadInt32(s, o + 0x124, 1, 0);
    ReadInt32(s, o + 0x128, 1, 0);
    if (version > 1)
        ReadInt32(s, o + 0x12c, 1, 0);
    ReadInt32(s, o + 0x130, 1, 0);
    FUN_0093a6c0(s, o + 0x134, 1);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x138, 0xc);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x144, 0xc);
    ReadInt32(s, o + 0x150, 1, 0);
    ReadInt32(s, o + 0x154, 1, 0);
    ReadInt32(s, o + 0x158, 1, 0);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x15c, 0xc);
    ReadInt32(s, o + 0x168, 1, 0);
    ReadInt32(s, o + 0x16c, 1, 0);
    FUN_00a9a870(s, o + 0x170);
    FUN_0093a6c0(s, o + 0x184, 1);
    FUN_0093a6c0(s, o + 0x185, 1);
    FUN_0093a6c0(s, o + 0x186, 1);
    FUN_0093a6c0(s, o + 0x187, 1);
    FUN_007ed920(s, o + 0x188);
    FUN_007d27d0(s, o + 0x19c);
    FUN_00a87f50(s, o + 0x1b0);
    ReadInt32(s, o + 0x1c4, 1, 0);
    ReadInt32(s, o + 0x1c8, 1, 0);
    ReadInt32(s, o + 0x1cc, 1, 0);
    ReadInt32(s, o + 0x1d0, 1, 0);
    ReadInt32(s, o + 0x1d4, 1, 0);
    ReadInt32(s, o + 0x1d8, 1, 0);
    ReadInt32(s, o + 0x1dc, 1, 0);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x1e0, 8);
    FUN_0093a800(s, o + 0x1e8, 1, 0);
    FUN_0093a800(s, o + 0x1f0, 1, 0);
    FUN_0093a800(s, o + 0x1f8, 1, 0);
    char* p = o + 0x200;
    for (int i = 2; i != 0; i--) {
        FUN_00a7b9a0(s, p);
        p += 0x34;
    }
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x268, 0xc);
    ReadInt32(s, o + 0x274, 1, 0);
    ReadInt32(s, o + 0x278, 1, 0);
    ReadInt32(s, o + 0x27c, 1, 0);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x280, 0xc);
    FUN_00a7ba10(s, o + 0x28c);
    FUN_00a9a8d0(s, o + 0x2a8);
    ReadInt32(s, o + 0x2bc, 1, 0);
}

// @ 0x00a9ae00
void cTimedState::Advance(float dt)
{
    char*  s = (char*)this;
    float* p;
    int    i = 0;
    p = (float*)(s + 0xd8);

    do {
        *p = *p - dt;
        while (*p < 0.0f)
            ((cRWState*)p)->Update((char*)(*(int*)(s + 0xc) + 0x200 + i));
        i += 0x34;
        p += 6;
    } while (i < 0x68);
}

// @ 0x00a9ae50
void __cdecl FUN_00a9ae50(const float* m, float* v)
{
    float x = v[0];
    float y = v[1];
    float z = v[2];

    float w = 1.0f / (((m[3] * x + m[7] * y) + m[11] * z) + m[15]);

    v[0] = w * (((m[4] * y + m[8] * z) + m[0] * x) + m[12]);
    v[1] = w * (((m[1] * x + m[5] * y) + m[9] * z) + m[13]);
    v[2] = w * (((m[2] * x + m[6] * y) + m[10] * z) + m[14]);
}

// @ 0x00a9af40
double __cdecl FUN_00a9af40(const float* p)
{
    float b = (float)(fabs((double)p[1]) + 1.0e-10);
    float a = (float)fabs((double)p[0]);
    float r = (b - a) / (a + b);
    float angle = (0.9817f - (r * r) * 0.1963f) * r;

    if (p[0] < 0.0f)
        angle = DAT_01565424 * 3.0f - angle;
    else
        angle = DAT_01565424 + angle;
    if (p[1] < 0.0f)
        angle = -angle;

    return (1.0 / DAT_01678ffc) * angle;
}

// @ 0x00a9aff0
void __cdecl FUN_00a9aff0(float t, const void* list, const float* a, float* b)
{
    float dx = b[0] - a[0];
    float dy = b[1] - a[1];
    float dz = b[2] - a[2];

    const cElem* begin = *(const cElem**)list;
    const cElem* end = *(const cElem**)((const char*)list + 4);

    for (const cElem* e = begin; e != end; e++) {
        float f = ((e->m[1] * dx + e->v[2] * dz) + e->m[2] * dy) + e->w * t;

        float g = DAT_01678f38 * f + 12582912.0f;
        int   bits = *(int*)&g;
        unsigned idx = (unsigned)bits & 0xf;

        float frac = f - (float)(bits + (int)0xb4c00000) * DAT_01678fe8;
        float s0 = DAT_01677840[idx * 2];
        float s1 = DAT_01677840[idx * 2 + 1];
        float s = (s1 - (s0 * frac) * 0.5f) * frac + s0;

        b[1] = b[1] + e->v[0] * s;
        b[0] = b[0] + e->m[0] * s;
        b[2] = e->v[1] * s + b[2];
    }
}

// @ 0x00a9b120
void __cdecl FUN_00a9b120(const void* a1, const float* a2, const float* a3, float a4, void* a5)
{
    float vx = a2[0];
    float vy = a2[1];
    float vz = a2[2];

    float num = a3[1] * vx - a3[0] * vy;
    float len = (float)sqrt((double)(vy * vy + (vx * vx + vz * vz)));
    if (len > 0.0f)
        num = num / len;

    char* o = (char*)a5;
    float f = *(float*)(o + 0x44) -
              (*(float*)((char*)a1 + 0x27c) * *(float*)(o + 0x44)) * a4;
    *(float*)(o + 0x44) = f;
    *(float*)(o + 0x44) = f - (*(float*)((char*)a1 + 0x278) * num) * a4;
}

// @ 0x00a9b1d0
void cField::Destroy()
{
    if (m_20 != 0) {
        void* v = *(void**)this;
        (*(void (__thiscall**)(void*, int))((char*)v + 0x0c))(this, 1);
    }
    if (m_194 != 0) {
        void* v = *(void**)m_194;
        (*(void (__thiscall**)(void*))((char*)v + 0x0c))(m_194);
        if (m_194 != 0) {
            void* o = m_194;
            m_194 = 0;
            void* ov = *(void**)o;
            (*(void (__thiscall**)(void*))((char*)ov + 0x04))(o);
        }
    }
    if (m_198 != 0) {
        void* v = *(void**)m_198;
        (*(void (__thiscall**)(void*))((char*)v + 0x0c))(m_198);
        if (m_198 != 0) {
            void* o = m_198;
            m_198 = 0;
            void* ov = *(void**)o;
            (*(void (__thiscall**)(void*))((char*)ov + 0x04))(o);
        }
    }
    if (m_19c != 0) {
        void* v = *(void**)m_19c;
        (*(void (__thiscall**)(void*))((char*)v + 0x0c))(m_19c);
        if (m_19c != 0) {
            void* o = m_19c;
            m_19c = 0;
            void* ov = *(void**)o;
            (*(void (__thiscall**)(void*))((char*)ov + 0x04))(o);
        }
    }
    m_0c = 0;
    m_14 = 0;
}

// @ 0x00a9b270
void cField::Reset(int arg)
{
    char* info = *(char**)((char*)this + 0xc);

    if (arg == 0)
        goto reset;
    if (*(int*)(info + 0x80) == 0)
        goto reset;
    if ((*(unsigned int*)(info + 8) >> 2) & 1)
        goto reset;
    if ((int)*(unsigned int*)(info + 8) < 0)
        goto reset;
    return;

reset:
    if (*(int*)(info + 0x128) >= 0) {
        m_b0 = 0.0;
        m_21 = 0;
        m_a0 = 0.0;
        m_20 = 1;
        m_b8 = 0;
        m_c8 = 0.0f;
        m_cc = *(int*)(info + 0x138);
        m_d0 = *(int*)(info + 0x13c);
        m_d4 = *(int*)(info + 0x140);

        if ((*(unsigned int*)(info + 8) >> 0x13) & 1) {
            Vec3_s00a9_a630 v;
            bool flag = (bool)((*(unsigned int*)(info + 8) >> 0x15) & 1);
            FUN_007cdbe0(&v, info + 0x2c);
            int i = 0;
            char* st = m_d8;
            do {
                char* base = *(char**)((char*)this + 0xc);
                FUN_00a79430(base + 0x200 + i, &v, (const Vec3_s00a9_a630*)st, flag);
                i += 0x34;
                st += 0x18;
            } while (i < 0x68);
        }

        info = *(char**)((char*)this + 0xc);
        if (*(float*)(info + 0x1c) < 0.0f) {
            if (*(float*)(info + 0x24) < 0.0f) {
                m_12c = 0.0f;
            }
            else {
                m_12c = (float)FUN_007cdb90(info + 0x24);
            }
        }
        else {
            double lo = (double)*(float*)(info + 0x1c);
            double hi = (double)*(float*)(info + 0x20);
            double r = g_Random.RandomDoubleUniform();
            double v = r * (hi - lo) + lo;
            if (hi <= v)
                m_12c = (float)hi;
            else if (v < lo)
                m_12c = (float)lo;
            else
                m_12c = (float)v;
        }

        m_124 = arg;
        m_128 = 0;
        m_a8 = (arg != 0) ? 1 : 0;
    }
}

// @ 0x00a9b410
void cField::SetObject(cField* n)
{
    cField* old = (cField*)m_248;

    if (n != old) {
        if (n != 0) {
            void* vt = *(void**)n;
            (*(void (__thiscall**)(void*))((char*)vt + 0x34))(n);
        }
        m_248 = n;
        if (old != 0) {
            void* vt = *(void**)old;
            (*(void (__thiscall**)(void*))((char*)vt + 0x38))(old);
            *(byte*)((char*)m_248 + 0x24c) = 1;
            return;
        }
        *(byte*)((char*)n + 0x24c) = 1;
        return;
    }
    *(byte*)((char*)old + 0x24c) = 1;
}

// @ 0x00a9c710
bool SwarmEmitter::ConstrainLocal(Particle_s00a9_bf20* p)
{
    Vec3_s00a9_bf20 pos = p->pos;
    if (m_local) {
        TransformPoint(m_xfA, pos);
        TransformPoint(m_xfB, pos);
    }

    if (m_sampler == 0 || !m_sampler->Contains(&pos))
        return false;

    float h = m_sampler->Height(&pos);
    uint32_t flags = m_desc->flags;
    if (Bit(flags, 6)) {
        if (m_minHeight > h) return false;
        if (h > m_maxHeight) return false;
    } else if (Bit(flags, 7)) {
        if (!(h > g_Random_s00a9_bf20.RandomDoubleUniform()))
            return false;
    }

    if (Bit(flags, 5)) {
        float range[2];
        range[0] = m_bboxMin.z;
        range[1] = m_bboxMax.z;
        pos.z = h + FUN_007cdb90(range);
    }

    if (m_local) {
        m_xfB.InvTransform(&pos);
        m_xfA.InvTransform(&pos);
    }

    p->pos = pos;
    return true;
}

// @ 0x00a9ca50
bool SwarmEmitter::SetParameter(int command, float* data, int count)
{
    switch (command) {
    case 0:
        m_param13c = data[0];
        return true;
    case 1:
        m_param148 = data[0];
        return true;
    case 2:
        m_param144 = data[0];
        return true;
    case 3:
        m_param140 = data[0];
        return true;
    case 4:
        m_param14c = data[0];
        return true;
    case 5:
        m_param150.x = data[0];
        m_param150.y = data[1];
        m_param150.z = data[2];
        return true;
    case 7:
        UpdateBasis(data);
        return true;
    case 9:
        m_surfacePoint.x = data[0];
        m_surfacePoint.y = data[1];
        m_surfacePoint.z = data[2];
        m_xfB.InvTransform(&m_surfacePoint);
        return true;
    case 0xa:
        m_surfaceSign = data[0];
        return true;
    case 0xb: {
        float numer = (m_planePoint.x - data[0]) * data[3];
        numer = numer + (m_planePoint.y - data[1]) * data[4];
        numer = numer + (m_planePoint.z - data[2]) * data[5];
        float len2 = FUN_0053c480(data + 3, data + 3);
        float t = numer / len2;
        m_surfacePoint.x = data[0] + data[3] * t;
        m_surfacePoint.y = data[1] + data[4] * t;
        m_surfacePoint.z = data[2] + data[5] * t;
        m_surfaceSign = (t >= 0.0f) ? 1.0f : 0.0f;
        m_xfB.InvTransform(&m_surfacePoint);
        return true;
    }
    case 0xd: {
        uint32_t buf[14];
        void* out = FUN_007d5590(buf, &m_xfA, &m_xfB);
        FUN_00a7ab40(count / 3, data, m_desc->m_44, out, &m_params);
        return true;
    }
    case 0x10:
        m_minHeight = data[0];
        m_maxHeight = data[1];
        return true;
    case 0x101:
        m_basis0 = data[0];
        m_basis2 = data[1];
        m_basis4 = data[2];
        m_basis1 = data[3];
        m_basis3 = data[4];
        m_basis5 = data[5];
        return true;
    default:
        break;
    }

    SwarmChild* head = (SwarmChild*)&m_children;
    bool result = false;
    for (SwarmChild* n = head->m_next; n != head; n = n->m_next) {
        SwarmProcessor* proc = (SwarmProcessor*)n->m_processor;
        if (proc != 0) {
            bool r = proc->Command(command, data, count);
            if (r || result)
                result = true;
        }
    }
    return result;
}

// @ 0x00a9ce00
void cParticlesEffect_s00a9_ce00::BuildParticleTransform(cParticle_s00a9_ce00* p, float t, float size, Vector3_s00a9_ce00* pos, cSPTransform_s00a9_ce00* out)
{
  cTransform_s00a9_ce00 tr;
  ++tr.mModCount;
  tr.mScale = size;
  cParticlesDescription_s00a9_ce00* d = mDesc;
  uint8_t mode = d->mAlignMode;
  if (mode < 2 || mode > 4) {
    tr.RotateZ(p->mRotation * kDegToRad);
  } else {
    Matrix33_s00a9_ce00 m(kTransformIdentity);
    Vector3_s00a9_ce00 v = p->mVelocity;
    float len = (float)sqrt((v.z * v.z + v.y * v.y) + v.x * v.x);
    if (len > 0.0001f) {
      float inv = 1.0f / len;
      v.x = inv * v.x;
      v.y = v.y * inv;
      v.z = v.z * inv;
    } else {
      v.x = v.x * 10000.0f;
      v.y = v.y * 10000.0f;
      v.z = v.z * 10000.0f;
      (&v.x)[mode - 2] = (1.0f - len * 10000.0f) + (&v.x)[mode - 2];
    }
    d = mDesc;
    if ((d->mFlags >> 2) & 1) {
      Quat q;
      q.x = -p->mOrientation.x;
      q.y = -p->mOrientation.y;
      q.z = -p->mOrientation.z;
      q.w = p->mOrientation.w;
      Vector3_s00a9_ce00 tmp;
      v = *RotateByQuat(&tmp, &v, &q);
    }
    switch (d->mAlignMode) {
    case 2: AlignAxisX(&v, &m); break;
    case 3: AlignAxisY(&v, &m); break;
    case 4: AlignAxisZ(&v, &m); break;
    }
    tr.mRotation = m;
    tr.mFlags |= 2;
    ++tr.mModCount;
    float lag = mDesc->mAlignLag;
    if (lag > 0.0f) {
      float cur = MatrixAngle(&m);
      float old = p->mRotation;
      float target;
      if (old == -999.0f) {
        target = cur;
      } else {
        if (old - 0.5f > cur)
          old = old - 1.0f;
        else if (cur > old + 0.5f)
          old = old + 1.0f;
        target = ((cur - old) / lag) * 0.06666667f + old;
      }
      tr.RotateZ((target - cur) * kDegToRad);
      p->mRotation = target;
    }
    d = mDesc;
    if (d->mAlignSpin != 0.0f) {
      switch (d->mAlignMode) {
      case 2: tr.PreRotateX(p->mSpin); break;
      case 3: tr.RotateY(p->mSpin); break;
      case 4: tr.RotateZ(p->mSpin); break;
      }
    }
  }
  if ((d->mFlags >> 2) & 1) {
    Matrix33_s00a9_ce00 q;
    QuatToMatrix(&q, &p->mOrientation);
    Matrix33_s00a9_ce00 r;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        r.m[i][j] = (tr.mRotation.m[i][0] * q.m[0][j] + tr.mRotation.m[i][1] * q.m[1][j]) +
                    tr.mRotation.m[i][2] * q.m[2][j];
    tr.mRotation = r;
    tr.mFlags |= 2;
    ++tr.mModCount;
  }
  d = mDesc;
  tr.RotateY((p->mRotYVary * EvalCurve(d->mRotYCurve, t) + d->mRotYOffset) * kDegToRad);
  d = mDesc;
  tr.PreRotateX((p->mRotXVary * EvalCurve(d->mRotXCurve, t) + d->mRotXOffset) * kDegToRad);
  d = mDesc;
  tr.RotateZ((p->mRotZVary * EvalCurve(d->mRotZCurve, t) + d->mRotZOffset) * kDegToRad);
  if (!d->mWiggles.empty())
    WigglePoint((float)(d->mRateCurveTime * mOverallTime), &d->mWiggles, &mCenter,
                pos);
  tr.mOffset.x = pos->x;
  tr.mOffset.y = pos->y;
  tr.mOffset.z = pos->z;
  tr.mFlags |= 4;
  ++tr.mModCount;
  *out = tr;
}

// @ 0x00a9d640
bool ParticleEmitter::FUN_00a9d640(cParticle_s00a9_ce00* p, float dt)
{
  p->mAge = p->mAge + dt;
  if (p->mLife <= p->mAge)
    return false;

  for (;;) {
    const float* stepPtr = &kMaxStep;
    if (!(dt > kMaxStep))
      stepPtr = &dt;
    float step = *stepPtr;

    Vector3_s00a9_ce00 pos = p->mPosition;
    Vector3_s00a9_ce00 vel = p->mVelocity;
    cParticlesDescription_s00a9_ce00* d = this->mDesc;
    unsigned char pathFlag = (unsigned char)(d->mFlags08 >> 25);

    if (pathFlag & 1) {
      PathView* path;
      if (this->mPath.mpBegin != this->mPath.mpEnd)
        path = &this->mPath;
      else
        path = &d->mPath28c.mAlt;
      FUN_00a798d0(&p->mAge, step, path, d->mPathSpeed, &this->mXform30);
    } else {
      p->mPosition.x = pos.x + vel.x * step;
      p->mPosition.y = pos.y + vel.y * step;
      p->mPosition.z = pos.z + vel.z * step;
    }

    Vector3_s00a9_ce00 accel = this->mAccel;
    unsigned char timerFlag = (unsigned char)(this->mDesc->mFlags08 >> 20);
    if (timerFlag & 1) {
      float t0 = p->mState4c.mTimer - step;
      p->mState4c.mTimer = t0;
      float t1 = p->mState64.mTimer - step;
      p->mState64.mTimer = t1;
      bool reset0 = t0 < 0.0f;
      bool reset1 = t1 < 0.0f;
      if (reset0)
        p->mState4c.FUN_00a790a0(&this->mDesc->mSubs[0]);
      p->mState4c.FUN_00a79300(&accel);
      if (reset1)
        p->mState64.FUN_00a790a0(&this->mDesc->mSubs[1]);
      p->mState64.FUN_00a79300(&accel);
    }

    d = this->mDesc;
    unsigned char quatFlag = (unsigned char)(d->mFlags >> 2);
    if (quatFlag & 1) {
      float f7 = p->mOrientation.z;
      float f8 = p->mOrientation.x;
      float f10 = p->mOrientation.y;
      float f11 = p->mOrientation.w;
      float f6 = (f7 * f8 - f11 * f10) * accel.x;
      float f9 = (f11 * f7 + f10 * f8) * accel.x;
      accel.x = ((f10 * f8 - f11 * f7) * accel.y +
                 (f11 * f10 + f7 * f8) * accel.z) * kTwo +
                (kOne - (f7 * f7 + f10 * f10) * kTwo) * accel.x;
      float local20 = (f9 + (f7 * f10 - f11 * f8) * accel.z) * kTwo +
                      (kOne - (f7 * f7 + f8 * f8) * kTwo) * accel.y;
      accel.z = (f6 + (f11 * f8 + f7 * f10) * accel.y) * kTwo +
                (kOne - (f10 * f10 + f8 * f8) * kTwo) * accel.z;
      accel.y = local20;
    }

    accel.y = d->mOffset144.y + accel.y;
    accel.z = d->mOffset144.z + accel.z;
    accel.x = d->mOffset144.x + accel.x;

    unsigned char attractorFlag = (unsigned char)(d->mFlags08 >> 23);
    if (attractorFlag & 1) {
      Vector3_s00a9_ce00 attractor;
      attractor.x = this->mAttractor.x - p->mPosition.x;
      attractor.y = this->mAttractor.y - p->mPosition.y;
      attractor.z = this->mAttractor.z - p->mPosition.z;
      if (!FUN_00a79500(&d->mPath28c, &attractor, this->mAttractorStrength, &accel))
        break;
    }

    float vy = p->mVelocity.y + accel.y * step;
    p->mVelocity.y = vy;
    float vx = p->mVelocity.x + accel.x * step;
    p->mVelocity.x = vx;
    float vz = p->mVelocity.z + accel.z * step;
    p->mVelocity.z = vz;
    float drag = kOne - this->mDesc->mDrag168 * step;
    p->mVelocity.x = vx * drag;
    p->mVelocity.y = vy * drag;
    p->mVelocity.z = vz * drag;

    unsigned char collFlag = (unsigned char)(this->mDesc->mFlags08 >> 12);
    if (((collFlag & 1) != 0 && !FUN_00a9b8d0(p, &pos)) ||
        (this->mpCollisionObj != 0 && !FUN_00a9bf20(p, step)))
      break;

    d = this->mDesc;
    float spin = d->mAlignSpin;
    if (spin != 0.0f) {
      float cross = p->mVelocity.y * vel.x - p->mVelocity.x * vel.y;
      float len = (float)sqrt(vel.x * vel.x + (vel.y * vel.y + vel.z * vel.z));
      if (0.0f < len)
        cross = cross / len;
      float s = p->mSpin - (d->mSpinDamping * p->mSpin) * step;
      p->mSpin = s;
      p->mSpin = s - (d->mAlignSpin * cross) * step;
    }

    dt -= step;
    if (dt <= 0.0f)
      return true;
  }
  return false;
}

// @ 0x00a9dc00
bool cMetaParticlesEffect_s00a9_dc00::UpdateParticle(cMetaParticle* p, float dt)
{
    char* self = (char*)this;
    char* desc = *(char**)(self + 0xc);
    if ((*(uint32*)(desc + 8) >> 26) & 1) {
        // save the particle's current position (used by the spin correction)
        float pos[3];
        pos[0] = *(float*)((char*)p + 0x1c);
        pos[1] = *(float*)((char*)p + 0x20);
        pos[2] = *(float*)((char*)p + 0x24);

        // path target: the effect's current path when active, else the description's default
        char* target = desc + 0x2a8;
        if (*(void**)(self + 0x218) != *(void**)(self + 0x21c))
            target = self + 0x218;

        void* path = p ? (char*)p + 8 : 0;

        char* d = *(char**)(self + 0xc);
        float w = *(float*)(d + 0x44);
        float size[3];
        size[0] = w * ((*(float*)(d + 0x2c) + *(float*)(d + 0x38)) * 0.5f);
        size[1] = w * ((*(float*)(d + 0x3c) + *(float*)(d + 0x30)) * 0.5f);
        size[2] = w * ((*(float*)(d + 0x40) + *(float*)(d + 0x34)) * 0.5f);
        float box[3];
        box[0] = (*(float*)(d + 0x58) + *(float*)(d + 0x4c)) * 0.5f;
        box[1] = (*(float*)(d + 0x5c) + *(float*)(d + 0x50)) * 0.5f;
        box[2] = (*(float*)(d + 0x60) + *(float*)(d + 0x54)) * 0.5f;

        if (!FUN_00a79f60(path, dt, target, box, size, self + 0x30))
            return false;

        char* d2 = *(char**)(self + 0xc);
        if (*(float*)(d2 + 0x278) != 0.0f)
            FUN_00a9b120(d2, pos, (float*)((char*)p + 0x1c), dt, p);
        return true;
    }

    // Cheap integrator while the description has no active timestep flags and the step is short.
    if ((*(uint32*)(desc + 0xc) & g_1679038) == 0 &&
        (*(uint32*)(desc + 8) & g_1679034) == 0 &&
        !(*(float*)(desc + 0x168) * dt > 0.05f))
        return UpdateParticleCheap(p, dt);
    return UpdateParticleFull(p, dt);
}

// @ 0x00a9ddd0
bool ParticleEmitter_s00a9_ddd0::InitParticle(Particle_s00a9_ddd0* p)
{
    bool fromVolume;
    bool hasQuat;
    Vec3_s00a9_ddd0 tmp;
    Vec3_s00a9_ddd0 dir;
    float spd;
    float nx, ny, nz;
    Vec4 col;
    Vec3_s00a9_ddd0 hit;

    p->age = 0.0f;
    p->life = (float)(RandRange(desc->lifeMin, desc->lifeMax) * f144);

    if (Bit(desc->flags[0], 0x1a)) {
        uint32_t* r = &p218;
        if (p218 == p21c) r = (uint32_t*)((char*)desc + 0x2a8);
        if (FUN_00a79660(&p->age, r)) {
            fromVolume = true;
            goto after_pos;
        }
    }
    fromVolume = false;
    {
        Desc* d = desc;
        Vec3_s00a9_ddd0* v;
        if (d->f64 >= kZero) {
            p->pos = *FUN_00a817c0(&tmp, &v1a4, d->f64);
        } else {
            if (Bit(d->flags[0], 4))
                v = FUN_00a81580(&tmp, &v1a4);
            else
                v = FUN_007cdbe0_s00a9_ddd0(&tmp, &v1a4);
            p->pos = *v;
        }
    }

    if ((desc->flags[0] & g_Mask[0]) | (desc->flags[1] & g_Mask[1])) {
        if (!CheckSpawn(p))
            return false;
    }

    {
        Vec3_s00a9_ddd0* v = FUN_007cdbe0_s00a9_ddd0(&tmp, desc->emitDir);
        dir = *v;
        spd = FUN_007cdb90(desc->emitSpeed) * f13c;
        p->vel = dir;
        float l2 = (p->vel.x * p->vel.x + p->vel.y * p->vel.y) + p->vel.z * p->vel.z;
        if (l2 > 0.0f) {
            float s = spd / sqrtf(l2);
            p->vel.x = p->vel.x * s;
            p->vel.y = p->vel.y * s;
            p->vel.z = s * p->vel.z;
        }
        Desc* d = desc;
        float k = d->attract;
        if (k != 0.0f) {
            float dy = p->pos.y - d->attractPos.y;
            float dz = p->pos.z - d->attractPos.z;
            float dx = p->pos.x - d->attractPos.x;
            float m2 = (dz * dz + dy * dy) + dx * dx;
            if (m2 > 1e-6f) {
                float s = k / sqrtf(m2);
                Vec3_s00a9_ddd0 a = V3Mul(dx, dy, dz, s);
                V3AddTo(p->vel, a);
            }
        }
    }

after_pos:
    {
        float v;
        v = desc->sizeVary;
        p->size = (float)RandRange(1.0 - v, v + 1.0);
        v = desc->vary124;
        p->alpha = (float)RandRange(1.0 - v, v + 1.0);
        v = desc->vary104;
        p->color.x = (float)RandRange(1.0 - v, v + 1.0);
        v = desc->vary108;
        p->color.y = (float)RandRange(1.0 - v, v + 1.0);
        v = desc->vary10c;
        p->color.z = (float)RandRange(1.0 - v, v + 1.0);
    }

    if (sampler) {
        tmp = p->pos;
        if (b1a2) {
            xf30.Transform(&tmp);
            xf68.Transform(&tmp);
        }
        if (sampler->Contains(&tmp)) {
            sampler->Sample(&col, &p->pos);
            p->alpha = col.w * p->alpha;
            p->color.x = p->color.x * col.x;
            p->color.y = p->color.y * col.y;
            p->color.z = p->color.z * col.z;
        }
    }

    {
        float v = desc->fd8;
        p->f98 = (v > kZero) ? FUN_00a78f80(v) : kOne;
        v = desc->fdc;
        p->f9c = (v > kZero) ? FUN_00a78f80(v) : kOne;
        v = desc->fe0;
        p->f94 = (v > kZero) ? FUN_00a78f80(v) : kOne;
    }

    if (Bit(desc->flags[0], 0xb))
        p->size = xf30.scale * p->size;

    Vec3_s00a9_ddd0* pv = &p->pos;
    if (xf30.flags & 2) {
        float y = pv->y, z = pv->z, x = pv->x;
        nx = (xf30.m[3] * y + xf30.m[6] * z) + xf30.m[0] * x;
        ny = (xf30.m[1] * x + xf30.m[4] * y) + xf30.m[7] * z;
        nz = (xf30.m[2] * x + xf30.m[5] * y) + xf30.m[8] * z;
        pv->x = nx; pv->y = ny; pv->z = nz;
    }
    {
        float s = xf30.scale;
        float x = pv->x;
        pv->z = pv->z * s;
        pv->y = s * pv->y;
        pv->x = x * s;
        pv->x = pv->x + xf30.t.x;
        pv->y = xf30.t.y + pv->y;
        pv->z = xf30.t.z + pv->z;
    }

    {
        FxObj* n = factory->Create(desc->key12c, desc->key128, u10, u1c);
        FxObj* old = p->fx;
        if (n != old) {
            if (n) n->AddRef();
            p->fx = n;
            if (old) old->Release();
        }
    }

    if (i1fc != 0) {
        void* arg = 0;
        if (desc->key12c == 0) {
            if (p->fx) arg = (char*)p->fx - 4;
        }
        int off = p->index * i1fc + i1e8;
        for (SpawnRec* r = recBegin; r != recEnd; r++) {
            if (r->has10)
                r->a->Apply(r->b, r->c14 + off, arg);
        }
    }

    p->quat[3] = kOne;
    hasQuat = false;
    if (b214) {
        int baseA = i1d4;
        int baseB = p->index * i1fc + i1e8;
        for (SpawnRec* r = recBegin; r != recEnd; r++) {
            if ((*r->b & g_Mask5430) == 0)
                continue;
            int pa = r->has8 ? r->c + baseA : 0;
            int pb = r->has10 ? r->c14 + baseB : 0;
            if (Bit(desc->flags[1], 2) == 0) {
                if (r->a->Collide(pv, pv, &hit, 0, pa, pb)) {
                    float sc = ((float*)r->b)[8];
                    if (sc != 0.0f) {
                        pv->x = pv->x + hit.x * sc;
                        pv->y = hit.y * sc + pv->y;
                        pv->z = hit.z * sc + pv->z;
                    }
                    break;
                }
            } else {
                if (r->a->Collide(pv, pv, &hit, p->quat, pa, pb)) {
                    float sc = ((float*)r->b)[8];
                    if (sc != 0.0f) {
                        pv->x = hit.x * sc + pv->x;
                        pv->y = hit.y * sc + pv->y;
                        pv->z = hit.z * sc + pv->z;
                    }
                    if (Bit(desc->flags[1], 3)) {
                        float* q = QuatFromMatrix33((float*)&col, xf30.m, 0.0f);
                        p->quat[0] = q[0];
                        p->quat[1] = q[1];
                        p->quat[2] = q[2];
                        p->quat[3] = q[3];
                    }
                    float qx = p->quat[0], qy = p->quat[1], qz = p->quat[2], qw = p->quat[3];
                    float zy = qz * qy;
                    float yx = qy * qx;
                    float wy = qw * qy;
                    float vx = p->vel.x;
                    nx = ((wy + qz * qx) * p->vel.z + (yx - qw * qz) * p->vel.y) * 2.0f
                         + (1.0f - (qz * qz + qy * qy) * 2.0f) * vx;
                    ny = ((qw * qz + yx) * vx + (zy - qw * qx) * p->vel.z) * 2.0f
                         + (1.0f - (qz * qz + qx * qx) * 2.0f) * p->vel.y;
                    nz = ((qz * qx - wy) * vx + (qw * qx + zy) * p->vel.y) * 2.0f
                         + (1.0f - (qy * qy + qx * qx) * 2.0f) * p->vel.z;
                    hasQuat = true;
                    goto store_vel;
                }
            }
        }
    }
    if (xf30.flags & 2) {
        float y = p->vel.y, z = p->vel.z, x = p->vel.x;
        nx = (xf30.m[3] * y + xf30.m[6] * z) + x * xf30.m[0];
        ny = (xf30.m[1] * x + xf30.m[4] * y) + xf30.m[7] * z;
        nz = (xf30.m[2] * x + xf30.m[5] * y) + xf30.m[8] * z;
store_vel:
        p->vel.x = nx;
        p->vel.y = ny;
        p->vel.z = nz;
    }

    if (!fromVolume && Bit(desc->flags[0], 3)) {
        float g = **(float**)&desc->p84;
        float inv = 1.0f / spd;
        pv->x = ((p->vel.x * 0.5f) * g) * inv + pv->x;
        pv->y = ((p->vel.y * 0.5f) * g) * inv + pv->y;
        pv->z = ((p->vel.z * 0.5f) * g) * inv + pv->z;
    }

    if (!hasQuat && desc->mode134 == 1) {
        float inv = 1.0f / g_Inv;
        p->f9c = inv * AtanApprox(xf30.m[1], xf30.m[0]) + p->f9c;
        p->f98 = inv * AtanApprox(xf30.m[1], xf30.m[0]) + p->f98;
        p->f94 = inv * AtanApprox(xf30.m[1], xf30.m[0]) + p->f94;
    }

    {
        uint8_t m = desc->mode134;
        if (m < 2 || m > 4) {
            if (!hasQuat)
                p->f48 = (1.0f / g_Inv) * AtanApprox(xf30.m[1], xf30.m[0]);
        } else {
            *(uint32_t*)&p->f48 = 0xc479c000;
        }
    }

    if (p->fx) {
        if (b22c)
            p->fx->v9(0, u230);
        if ((u238 & u23c) != 0xffffffff)
            p->fx->v8(0, &u238, 1);
        if ((u240 & u244) != 0xffffffff)
            p->fx->v8(1, &u240, 1);
        if (i234 >= 0)
            p->fx->v8(2, (uint32_t*)&i234, 1);
        SpawnArgs a;
        a.kind = 4;
        a.one = 1;
        a.pos = *pv;
        a.s = 1.0f;
        for (int i = 0; i < 9; i++) a.m[i] = g_Mat9[i];
        p->fx->v6(&a, &xf68);
        if (!b22)
            p->fx->v10(0);
        p->fx->v2(0);
    }

    if (!fromVolume && Bit(desc->flags[0], 0x14)) {
        int f = (desc->flags[0] >> 0x15) & 1;
        for (int i = 0; i < 2; i++)
            FxStateInit(&p->st[i], &desc->subs[i], &dir, f);
    }
    return true;
}

// @ 0x00a9ef80
void Emitter::FUN_00a9ef80(Particle_s00a9_ef80* p)
{
    Desc_s00a9_ef80* d = pool->desc;

    p->age = 0.0f;
    p->life = (float)(RandRange_s00a9_ef80(d->lifeMin, d->lifeMax) * f144);

    if ((int32_t)d->key128 >= 0 && d->key128 != desc->key128 && d->key12c == 0) {
        FxBase* fx = p->fx.p ? (FxBase*)((char*)p->fx.p - 4) : 0;
        XformMsg a;
        XformMsg b;
        if (p->fx.p) {
            fx->b7(&a);
            fx->b8(&b);
            fx->b3((uint32_t)i128);
            p->fx.Reset();
        }
        p->fx.Assign(factory->Create(d->key12c, d->key128, u10, (uint32_t)u1c));
        if (p->fx.p) {
            p->fx.p->v6(&b, &a);
            if (b22c) p->fx.p->v9(0, u230);
            p->fx.p->v10(b22);
            p->fx.p->v2(u124);
        }
    }

    if (!pool->v4())
        pool->v2(0);

    if (Bit(d->flags[0], 0x1d))
        pool->InitParticle(p);

    Emitter* em = pool;
    Particle_s00a9_ef80* first = (Particle_s00a9_ef80*)em->head;
    p->node[0] = first;
    p->node[1] = (void*)&em->head;
    em->head = p;
    ((Particle_s00a9_ef80*)p->node[0])->node[1] = p;
    em->count++;
}
