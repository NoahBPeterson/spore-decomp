// src/game/SPGonzago/SPWeaponsView.cpp -- migrated from slice(s) s00cc4160, s00cc4270, s00cc3220, s00cc22c0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPWeaponsView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// Hand guard (kept by merge_preamble on re-apply): the generated tm.h defines `struct tm` unguarded, so it
// collides with <wchar.h>'s own `struct tm` (C2011) as soon as a slice of this module needs <wchar.h>
// (s00cc3220 does).  Defining the CRT guard first makes <wchar.h> skip its copy; tm.h (via SP/cStarRecord.h)
// still supplies `struct tm` for cStarRecord::savedGameTimeStamp (same 9-int layout).
#define _TM_DEFINED

#include "game/types.h"
#include "SP/cDefaultAoEArea.h"
#include "SP/cEffectInfo.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cModelInstance.h"
#include "SP/cSPSpaceToolData.h"
#include "SP/cSpatialObject.h"
#include <wchar.h>
#include <string.h>

// ---- items of slice s00cc22c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int intptr_t;
#define nullptr 0
class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};
class cDefaultAoEArea : public IRefCounted {
public:
    virtual void v14();
    virtual uint32_t GetNoteEffectID();
    virtual void v1c();
    virtual void v20();
    uint8_t mPad18[0x1c];
};
class cEffectInfo : public IRefCounted {
public:
    uint8_t mPad14[0x10];
};
class cSpatialObjectView : public IRefCounted {
public:
    cSpatialObjectView();
    ~cSpatialObjectView();
    void SetObject(void* pObject);                  // 0x24
    int UpdateState();
    void HandleSimulationUpdate(int a, int b);
    void CreateEffect(uint32_t id, int a);          // wrapper over the effect list

    uint8_t mPad04[0x10];           // 0x04
    void* mpObject;                 // 0x14
    uint8_t mPad18[0x1c];           // 0x18
    cEffectInfo* mpEffectInfo;      // 0x34
    uint8_t mFlag38;                // 0x38
    uint8_t mFlag39;                // 0x39
    uint8_t mFlag3a;                // 0x3a
    uint8_t mFlag3b;                // 0x3b
    uint8_t mFlag3c;                // 0x3c
    uint8_t mFlag3d;                // 0x3d
    uint8_t mPad3e[0x02];           // 0x3e
    int mViewState;                 // 0x40
};
class cDefaultBeamProjectileView : public cSpatialObjectView {
public:
    cDefaultBeamProjectileView();
    bool mbLoadingModel;            // 0x44
    bool mbAnimationsStarted;       // 0x45
};
class cSpaceDefenseMissileView : public cSpatialObjectView {
public:
    cSpaceDefenseMissileView();
    ~cSpaceDefenseMissileView();
    void HandleSimulationUpdate(int a, int b);
};
class cCulturalProjectileView : public cSpatialObjectView {
public:
    static cSpatialObjectView* MakeView(void* pObject);   // 0x00cc3140
};
class cSpaceProjectile : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual uint32_t GetEffectId();                 // 0x1c
    virtual void v20();
    uint8_t mPad18[0x1c];
};
class cGameNounManager {
public:
    void* GetGameDataVector(void* pA, void* pB, void* pC, void* pD, const void* pType);
};
void* operator_new(size_t nSize, const char* pName, int a, int b, int c, int d);
void* operator_new(size_t nSize, const char* pName, int a);
void* operator_new(size_t nSize, const char* pName, int a, int b);
cGameNounManager* NounManager();
void* NounManager(uint32_t id);
uint32_t GetHitEffectIdA();
uint32_t GetHitEffectIdB();
uint32_t GetHitEffectIdC();
uint32_t GetBeamEffectId();
uint32_t GetMuzzleEffectId();
uint32_t GetChargeEffectId();
uint32_t GetTrailEffectId();
uint32_t GetProjectileType();
void* FindEffect(uint32_t id);
void CreateEffectRef(uint32_t id, int a, uint32_t group);
void SetEffectScale(uint32_t id, uint32_t fScaleBits);
bool IsEmpireObjectValid(void* pObject);
bool IsAoEPreviewActive();
uint32_t GetAoEPreviewEffectId();
void* FindNounFromId(uint32_t id);
void UpdateMissileEffect(void* pView, void* pEffect, int a);
void UpdateBeamEffect(void* pView, void* pEffect, int a);
// ---- items of slice s00cc22c0 end

// ---- items of slice s00cc3220 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
void __cdecl EAFree(void* p);                        // 0x00f47380  operator delete[]
void* __cdecl EANew(int size, const char* name, int, int, int, int);  // 0x00f473a0
void* __cdecl GetCurrentGameMode_s00cc_3220();                                   // 0x00b5b800
void  __cdecl FUN_00cf74c0();                                         // 0x00cf74c0
void  __cdecl FUN_00cf74f0();                                         // 0x00cf74f0
u8    __cdecl FUN_00cf1540();                                         // 0x00cf1540
u8    __cdecl FUN_00c8e7c0();                                         // 0x00c8e7c0
void  __cdecl FUN_00c8b130(u32 kind, int a, int b);                   // 0x00c8b130
void  __cdecl FUN_00c88a00(u32 a, float b);                           // 0x00c88a00
void  __cdecl FUN_00c8ad30(int a, int b);                             // 0x00c8ad30
int   __cdecl FUN_00b25f40(u32 a);                                    // 0x00b25f40
void  __cdecl NounManager_s00cc_3220(u32 a);                                     // 0x00b3d300
u32   __cdecl FUN_00c9c2b0();                                         // 0x00c9c2b0
int   __cdecl FUN_00cb37c0();                                         // 0x00cb37c0
void  __cdecl FUN_00434040();                                         // 0x00434040
void* __cdecl GonzagoModelWorld();                                    // 0x00b3d520
void  __cdecl FUN_00cb5d80(void* a, void* b);                         // 0x00cb5d80
void  __cdecl FUN_00cb5450(void* a, void* b);                         // 0x00cb5450
float __cdecl FUN_0104bdb0();                                         // 0x0104bdb0
void* __cdecl SP_Matrix3FromFacingAndUp(void* out, void* a, void* b); // 0x0041cb40
float* __cdecl SP_Matrix3FromQuaternion(void* out, const void* q);    // 0x0059c190
void* __cdecl FUN_00b894a0(float* v);                                 // 0x00b894a0
static inline void* VT_B8_1(void* p, int a) {
    return ((void* (__thiscall*)(void*, int))*((void***)*(void**)p + 0xb8 / 4))(p, a);
}
static inline void VT_44_3(void* p, int a, float* b, int c) {
    ((void (__thiscall*)(void*, int, float*, int))*((void***)*(void**)p + 0x44 / 4))(p, a, b, c);
}
static inline void VT_30_1(void* p, int a) {
    ((void (__thiscall*)(void*, int))*((void***)*(void**)p + 0x30 / 4))(p, a);
}
static inline void VT_18_1(void* p, void* a) {
    ((void (__thiscall*)(void*, void*))*((void***)*(void**)p + 0x18 / 4))(p, a);
}
static inline void VT_20_1(void* p, void* a) {
    ((void (__thiscall*)(void*, void*))*((void***)*(void**)p + 0x20 / 4))(p, a);
}
static inline void VT_24_1(void* p, void* a) {
    ((void (__thiscall*)(void*, void*))*((void***)*(void**)p + 0x24 / 4))(p, a);
}
static inline int VT_0C_1(void* p, int a) {
    return ((int (__thiscall*)(void*, int))*((void***)*(void**)p + 0x0c / 4))(p, a);
}
static inline void* VT_0C_0(void* p) {
    return ((void* (__thiscall*)(void*))*((void***)*(void**)p + 0x0c / 4))(p);
}
static inline void* VT_0C_3(void* p, int a, int b, int c) {
    return ((void* (__thiscall*)(void*, int, int, int))*((void***)*(void**)p + 0x0c / 4))(p, a, b, c);
}
static inline void* VT_18_0(void* p) {
    return ((void* (__thiscall*)(void*))*((void***)*(void**)p + 0x18 / 4))(p);
}
static inline void* VT_5C_1(void* p, int a) {
    return ((void* (__thiscall*)(void*, int))*((void***)*(void**)p + 0x5c / 4))(p, a);
}
static inline void VT_A8_2(void* p, void* a, void* b) {
    ((void (__thiscall*)(void*, void*, void*))*((void***)*(void**)p + 0xa8 / 4))(p, a, b);
}
static inline int VT_AC_0(void* p) {
    return ((int (__thiscall*)(void*))*((void***)*(void**)p + 0xac / 4))(p);
}
static inline int VT_4C_0(void* p) {
    return ((int (__thiscall*)(void*))*((void***)*(void**)p + 0x4c / 4))(p);
}
static inline float VT_34_F(void* p) {
    return ((float (__thiscall*)(void*))*((void***)*(void**)p + 0x34 / 4))(p);
}
static inline void* VT_E0_0(void* p) {
    return ((void* (__thiscall*)(void*))*((void***)*(void**)p + 0xe0 / 4))(p);
}
static inline void* VT_6C_0(void* p) {
    return ((void* (__thiscall*)(void*))*((void***)*(void**)p + 0x6c / 4))(p);
}
static inline void* PM_DirToSurface(float* out, const float* dir) {
    return ((void* (__thiscall*)(float*, const float*))0x00b815a0)(out, dir);
}
static inline void* PM_BuildSurfaceOrientation(float* a, float* b) {
    return ((void* (__thiscall*)(float*, float*))0x00b7f190)(a, b);
}
static inline void PM_Construct(void* pm, float* out, float* dir) {
    ((void (__thiscall*)(void*, float*, float*))0x00b3d350)(pm, out, dir);
}
struct Vector3 { float x, y, z; };
struct Matrix33 {
    float m[9];
    void Ctor(const void* init);                     // 0x0041cb40
};
struct EffectUpdate {
    Vector3  mPosition;                              // 0x00
    u32      mFlags;                                 // 0x0c  bit0 pos, bit1 orient, bit2 scale
    u8       mCount;                                 // 0x10
    char     pad11[3];
    Matrix33 mOrientation;                           // 0x14
    float    mScale;                                 // 0x38
};
struct cSPSpaceToolData {
    u8 IsInContext();                                // 0x0104cb70
};
struct cSpatialObject {
    void* mpVtbl;                                    // 0x000
    char  pad004[0x134 - 0x004];
    void* mpSpaceToolData;                           // 0x134  space-tool bound to this object
    void  DestroyAllEffects(int a);                  // 0x00c8b0a0
    u8    GetEffect(int key);                        // 0x00c88910
    void* GetEffectObject(int key);                  // 0x00c888e0
    u64   FUN_00cb41b0();                            // 0x00cb41b0
    u64   FUN_00cb4340();                            // 0x00cb4340
    void* FUN_00c888e0(int a);                       // 0x00c888e0
};
struct cSubObject {
    char  pad000[0x034];
    void* mpOwner;                                   // 0x034  receiver used by the owner's slot 0xa8/0xac
    char  pad038[0x504 - 0x038];
    void* mpTool;                                    // 0x504  current tool instance
};
struct cToolInstance {
    char    pad000[0x544];
    int     mState;                                  // 0x544  1 = on ground, 2 = in air
    char    pad548[0x58c - 0x548];
    Vector3 mPosition;                               // 0x58c  world position
};
struct cTerrainObject {
    char  pad000[0x25c];
    float mHeight;                                   // 0x25c  surface height for the effect
};
struct cNounObject {
    char  pad000[0x0cc];
    u32   mEffectParam;                              // 0x0cc
};
struct cModelInstance {
    void* mpVtbl;                                    // 0x000
    u32   mFlags;                                    // 0x004
    char  pad008[0x040 - 0x008];
    int   mRefCount;                                 // 0x040  model reference counter
};
struct cSpatialObjectView_s00cc_3220 {
    void* mpVtbl;                                    // 0x000
    char  pad004[0x0c - 0x04];
    void* mpObject;                                  // 0x00c
    char  pad010[0x34 - 0x10];
    u8    mInGameMode;                               // 0x034  applied game-mode flag
    u8    mModeVariant;                              // 0x035  secondary mode flag

    void  ctor();                                    // 0x00e92af0
    void  BaseDtor();                                // 0x00e92660
    void  HandleSimulationUpdate(u32 fbits, u32 p);  // 0x00e92ca0

    void* FUN_00cc36d0(u8 flag);                     // 0x00cc36d0
    void  FUN_00cc3490(u32 fbits, u32 p);            // 0x00cc3490
    void  FUN_00cc3220(u32 fbits, u32 f2);           // 0x00cc3220
    void  FUN_00cc3950(u32 fbits, u32 f2);           // 0x00cc3950
    void  FUN_00cc3c30(u32 fbits, u32 f2);           // 0x00cc3c30
    void  FUN_00cc3f40(u32 fbits, u32 f2);           // 0x00cc3f40
};
struct cResourceProjectileView : cSpatialObjectView_s00cc_3220 {
    static void* MakeView(cSpatialObject* p);        // 0x00cc3380
};
struct cSpaceDefenseMissileView_s00cc_3220 : cSpatialObjectView_s00cc_3220 {
    static void* MakeView(cSpatialObject* p);        // 0x00cc3570
};
struct cArtilleryProjectileView : cSpatialObjectView_s00cc_3220 {
    static void* MakeView(cSpatialObject* p);        // 0x00cc3730
};
// ---- items of slice s00cc3220 end

// ---- items of slice s00cc4270 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
#pragma warning(disable: 4100)
#pragma intrinsic(sqrt)
inline void* operator new(unsigned int, void* p) throw() { return p; }
inline void operator delete(void*, void*) throw() {}
void __cdecl operator delete[](void* p);   // 0x00f47380
struct Vector3_s00cc_4270 {
    float x, y, z;
    Vector3_s00cc_4270() {}
    Vector3_s00cc_4270(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00cc_4270(const Vector3_s00cc_4270& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3_s00cc_4270 operator-(const Vector3_s00cc_4270& b) const { return Vector3_s00cc_4270(x - b.x, y - b.y, z - b.z); }
    Vector3_s00cc_4270 Normalized() const
    {
        float inv = 1.0f / (float)sqrt(x * x + y * y + z * z);
        return Vector3_s00cc_4270(inv * x, inv * y, inv * z);
    }
    Vector3_s00cc_4270 SafeNormalized() const
    {
        float inv = 1.0f / (float)sqrt(x * x + y * y + z * z + 1e-08f);
        return Vector3_s00cc_4270(inv * x, inv * y, inv * z);
    }
    static const Vector3_s00cc_4270 ZERO;     // 0x0169b048
};
struct Quaternion { float x, y, z, w; };
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& o);     // 0x0041cb40 (rw::math::fpu::Matrix33Template copy ctor, out of line)
    static const Matrix3 IDENTITY; // 0x0169b024
};
Matrix3& Matrix3FromQuaternion(Matrix3& out, const Quaternion& q);                         // 0x0059c190
Matrix3& Matrix3FromFacingAndUp(Matrix3& out, const Vector3_s00cc_4270& facing, const Vector3_s00cc_4270& up);   // 0x0069b440
struct Transform {
    int16_t mnFlags;
    int16_t mnTransformCount;
    Vector3_s00cc_4270 mOffset;
    float mfScale;
    Matrix3 mRotation;
    __forceinline Transform() : mnFlags(0), mnTransformCount(0), mOffset(Vector3_s00cc_4270::ZERO), mfScale(1.0f),
                                mRotation(Matrix3::IDENTITY) {}
    // offset-only transform with an identity rotation assigned in the body
    __forceinline explicit Transform(const Vector3_s00cc_4270& offset) : mnFlags(4), mnTransformCount(1), mOffset(offset), mfScale(1.0f)
    {
        mRotation = Matrix3::IDENTITY;
    }
    Transform& SetOffset(const Vector3_s00cc_4270& v) { mOffset = v; mnFlags |= 4; mnTransformCount++; return *this; }
    Transform& SetRotation(const Matrix3& r) { mRotation = r; mnFlags |= 2; mnTransformCount++; return *this; }
};
namespace Swarm {
enum { kFloatParamBeamPoints = 0xd, kVectorParamBeamEnd = 9, kFloatParamBeamScale = 10 };
}
namespace Swarm {
struct IVisualEffect {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual void Start(int hardStart) = 0;
    virtual int Stop(int hardStop) = 0;
    virtual int IsRunning() = 0;
    virtual void SetRigidTransform(const Transform& t) = 0;
    virtual void SetSourceTransform(const Transform& t) = 0;      // +0x18
    virtual void GetRigidTransform() = 0;
    virtual void GetSourceTransform() = 0;
    virtual void SetBone(void* pBone, int boneType) = 0;
    virtual void* GetBone(int boneType) = 0;
    virtual void SetIsPaused(bool paused) = 0;
    virtual void SetIsHidden(bool hidden) = 0;                    // +0x30
    virtual bool GetIsPaused() = 0;
    virtual bool GetIsHidden() = 0;
    virtual void SetSeed(int seed) = 0;
    virtual bool SetVectorParams(int param, const Vector3_s00cc_4270* data, int count) = 0;   // +0x40
    virtual bool SetFloatParams(int param, const float* data, int count) = 0;      // +0x44
};
}
namespace eastl {
template <typename T> inline const T& min(const T& a, const T& b) { return (b < a) ? b : a; }
}
namespace eastl {
template <typename T>
class vector_s00cc_4270 { public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](unsigned n) const { return mpBegin[n]; }
    T& front() const { return *mpBegin; }
    T& back() const { return *(mpEnd - 1); }
};
}
namespace eastl {
template <typename T, int nodeCount>
class fixed_vector_s00cc_4270 { public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mOverflowAllocator;
    T* mpPoolBegin;
    uint32_t mPad;
    T mBuffer[nodeCount];

    fixed_vector_s00cc_4270()
    {
        mpPoolBegin = mBuffer;
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + nodeCount;
    }
    ~fixed_vector_s00cc_4270()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
    T* data() { return mpBegin; }
    void DoInsertValue(T* position, const T& value);   // 0x00cc4160 (vector<float, fixed_vector_allocator>)
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
}
namespace SP {
struct cGameMode;
}
namespace SP {
extern cGameMode kCivGameMode;   // 0x01654c04
}
namespace SP {
cGameMode* GetCurrentGameMode(); // 0x00b5b800
}
namespace SP {
struct cCivModeTribe { bool f1540(); };                    // 0x00cf1540
}
namespace SP {
class cCivModeStrategy { public:
    static cCivModeStrategy* Get();                        // 0x00cf74c0
    cCivModeTribe* f74f0();                                // 0x00cf74f0
};
}
namespace SP {
class cDefaultBeamProjectile_s00cc_4270 { public:
    uint32_t pad0[0x16c / 4];
    bool mb16c;                                            // +0x16c
    bool mb16d;                                            // +0x16d
    bool mbUseOrientation;                                 // +0x16e
    uint8_t pad16f[0x1b0 - 0x16f];
    Quaternion mOrientation;                               // +0x1b0
    uint32_t pad1c0[(0x1e0 - 0x1c0) / 4];
    void* mp1e0;                                           // +0x1e0
    eastl::vector_s00cc_4270<Vector3_s00cc_4270> mPoints;                        // +0x1e4

    const eastl::vector_s00cc_4270<Vector3_s00cc_4270>& GetPoints();             // 0x00cb3cf0
    bool UseOrientation();                                 // 0x00cb3d10
    bool Has1e0();                                         // 0x00cb5ba0
    bool IsHittingPlayer();                                // 0x00cb5b70
};
}
namespace SP {
class cSpatialObject_s00cc_4270 { public:
    // vtable slot 0x2e (+0xb8): Cast
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v2a();
virtual void v2b();
virtual void v2c();
    virtual void v2d();
    virtual void* Cast(uint32_t typeID);

    // effect list at +0xc0 (0x3c-byte entries: id at +0, running flag at +8, effect at +0x38)
    Swarm::IVisualEffect* GetEffect(uint32_t id);          // 0x00c888e0
    bool HasEffect(uint32_t id);                           // 0x00c88910
    bool IsEffectRunning(uint32_t id);                     // 0x00c88940
    void StartEffect(uint32_t id, int hard);               // 0x00c88980
    void StopEffect(uint32_t id, int hard);                // 0x00c889c0
};
}
namespace SP {
class cSpatialObjectView_s00cc_4270 { public:
    uint32_t pad0[3];
    cSpatialObject_s00cc_4270* mpObject;                              // +0x0c
    uint32_t pad10[(0x34 - 0x10) / 4];
    int mnTime;                                            // +0x34

    void HandleSimulationUpdate(int unk, int deltaTime);   // 0x00e92ca0
};
}
namespace SP {
class cDefaultBeamProjectileView_s00cc_4270 : public cSpatialObjectView_s00cc_4270 { public:
    bool mbAnyActive;                                      // +0x38
    bool mbHidden;                                         // +0x39
    bool mb16c;                                            // +0x3a
    bool mb16d;                                            // +0x3b
    bool mbHittingPlayer;                                  // +0x3c
    bool mbHas1e0;                                         // +0x3d

    void HandleSimulationUpdate(int unk, int deltaTime);
};
}
namespace SP {
enum {
    kBeamEffect = 0x246350a,
    kBeamStartEffect = 0x9138b729,
    kBeamEndEffectB = 0x246350b,
    kBeamEndEffectC = 0x246350c,
    kBeamEndEffectD = 0x246350d,
    kBeamHitPlayerEffect = 0x47f791a,
    kTypeDefaultBeamProjectile = 0x24630ce,
};
}
namespace SP {
static __forceinline void UpdateEffectRunning(cSpatialObject_s00cc_4270* obj, uint32_t id, bool want, bool was)
{
    if (want) {
        if (!was)
            obj->StartEffect(id, 0);
    } else if (was) {
        obj->StopEffect(id, 0);
    }
}
}
// ---- items of slice s00cc4270 end

// ---- items of slice s00cc4160 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);
extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned int n);
void* EAAllocate(unsigned int size, const char* name, int a, int b, void* alloc, int line);
void eaFree(void* p);
struct cc4160_vec {
    float* m_begin;
    float* m_end;
    float* m_cap;
    float* m_alloc;
    void insert(float* pos, const float* value);
};
// ---- items of slice s00cc4160 end

// @ 0x00cc2980
cSpatialObjectView* MakeDefaultToolProjectileView(void* pObject)
{
    cSpatialObjectView* pView =
        (cSpatialObjectView*)operator_new(0x38, "Simulator/cDefaultToolProjectileView", 0);
    if (pView == nullptr)
        pView = nullptr;
    else
        pView->SetObject(nullptr);

    if (pObject == nullptr)
        return pView;

    void* pData = ((IRefCounted*)pObject)->Query((const void*)0x24270c4);
    if (pData == nullptr)
        return pView;

    pView->SetObject(pObject);
    pView->mFlag38 = 0;

    uint32_t nEffectId = GetMuzzleEffectId();
    if (nEffectId != 0) {
        uint32_t nKind = GetTrailEffectId();
        CreateEffectRef(nKind, 0, 0x500f162u);
        uint32_t fScale = (nKind == 0x203c5a15u || nKind == 0x992387aeu) ? 0x45000000u : 0x44800000u;
        SetEffectScale(0x500f162u, fScale);
    }

    if (GetChargeEffectId() != 0) {
        pView->mFlag39 = 0;
        uint32_t nCharge = GetChargeEffectId();
        CreateEffectRef(nCharge, 0, 0x6565ae1u);
        SetEffectScale(0x6565ae1u, 0x44800000u);
        uint32_t nChargeKind = GetTrailEffectId();
        if (nChargeKind == 0x79c7d671u || nChargeKind == 0x992387aeu || nChargeKind == 0xe8d95fb4u)
            pView->mFlag39 = 1;
    }

    float fScale = ((cSpaceProjectile*)*(void**)((uint8_t*)pData + 0x504))->GetEffectId();
    void* pEffect = FindEffect(0x500f162u);
    if (pEffect != nullptr) {
        UpdateBeamEffect(pEffect, &fScale, 1);
        if (GetProjectileType() == 0xe810d505u) {
            void* pTarget = (void*)(intptr_t)((cSpaceProjectile*)*(void**)((uint8_t*)pData + 0x504))->GetEffectId();
            if (pTarget != nullptr) {
                uint32_t nColor = ((cSpaceProjectile*)*(void**)((uint8_t*)pData + 0x504))->GetEffectId();
                if (IsEmpireObjectValid((void*)(intptr_t)nColor))
                    UpdateBeamEffect(pEffect, &nColor, 5);
            }
        }
    }
    return pView;
}

// @ 0x00cc2b60
cSpatialObjectView* MakeDeepSpaceProjectileView(void* pObject)
{
    cSpatialObjectView* pView =
        (cSpatialObjectView*)operator_new(0x34, "Simulator/cDeepSpaceProjectileView", 0, 0, 0, 0);
    if (pView == nullptr)
        pView = nullptr;
    else
        pView->SetObject(nullptr);

    if (pObject == nullptr)
        return pView;

    void* pData = ((IRefCounted*)pObject)->Query((const void*)0x24270c6);
    if (pData == nullptr)
        return pView;

    pView->SetObject(pObject);
    uint32_t nEffect0 = GetTrailEffectId();
    CreateEffectRef(nEffect0, 0, 0);
    uint32_t nEffect1 = GetBeamEffectId();
    CreateEffectRef(nEffect1, 0, 1);
    uint32_t nEffect2 = GetMuzzleEffectId();
    CreateEffectRef(nEffect2, 0, 2);
    uint32_t nEffect3 = GetChargeEffectId();
    CreateEffectRef(nEffect3, 0, 3);
    SetEffectScale(0, 0x45000000u);
    SetEffectScale(1, 0x45000000u);
    SetEffectScale(2, 0x45000000u);
    SetEffectScale(3, 0x45000000u);
    return pView;
}

// @ 0x00cc2c90
cSpaceDefenseMissileView::cSpaceDefenseMissileView()
{
    mpEffectInfo = nullptr;
    mFlag38 = 0;
    mFlag39 = 0;
    mFlag3a = 0;
    mFlag3b = 0;
}

// @ 0x00cc2cb0
cSpaceDefenseMissileView::~cSpaceDefenseMissileView()
{
    if (mpEffectInfo != nullptr) {
        mpEffectInfo->Query(nullptr);
        cEffectInfo* pOld = mpEffectInfo;
        if (pOld != nullptr) {
            mpEffectInfo = nullptr;
            pOld->Release();
        }
    }

    if (mpObject != nullptr) {
        ((IRefCounted*)mpObject)->Query(nullptr);
        if (mpObject != nullptr) {
            void* pOld = mpObject;
            mpObject = nullptr;
            ((IRefCounted*)pOld)->Release();
        }
    }

    if (mpObject != nullptr)
        ((IRefCounted*)mpObject)->Release();
    if (mpEffectInfo != nullptr)
        mpEffectInfo->Release();
}

// @ 0x00cc2d30
void cSpaceDefenseMissileView::HandleSimulationUpdate(int a, int b)
{
    cSpatialObjectView::HandleSimulationUpdate(a, b);
    UpdateMissileEffect(mpObject, mpEffectInfo, 0);
    UpdateBeamEffect(mpObject, &mpEffectInfo, 0);
}

// @ 0x00cc2d70
cSpatialObjectView* MakeDefaultBeamProjectileView(void* pObject)
{
    cDefaultBeamProjectileView* pView =
        (cDefaultBeamProjectileView*)operator_new(0x40, "Simulator/cDefaultBeamProjectileView", 0, 0);
    if (pView == nullptr) {
        pView = nullptr;
    } else {
        pView->mpEffectInfo = nullptr;
        pView->mFlag38 = 0;
        pView->mFlag39 = 0;
        pView->mFlag3a = 0;
        pView->mFlag3b = 0;
        pView->mbLoadingModel = false;
        pView->mbAnimationsStarted = false;
    }

    void* pData = nullptr;
    if (pObject != nullptr)
        pData = ((IRefCounted*)pObject)->Query((const void*)0x24630ce);

    pView->SetObject(pObject);
    pView->mFlag39 = 0;

    uint32_t nEffect0 = GetBeamEffectId();
    CreateEffectRef(nEffect0, 0, 0x246350au);
    uint32_t nEffect1 = GetMuzzleEffectId();
    CreateEffectRef(nEffect1, 0, 0x9138b729u);
    uint32_t nEffect2 = GetHitEffectIdA();
    pView->CreateEffect(nEffect2, 0);
    uint32_t nEffect3 = GetHitEffectIdB();
    pView->CreateEffect(nEffect3, 0);
    uint32_t nEffect4 = GetHitEffectIdC();
    pView->CreateEffect(nEffect4, 0);
    SetEffectScale(0x246350au, 0x45000000u);
    SetEffectScale(0x9138b729u, 0x45000000u);
    SetEffectScale(0x246350bu, 0x45000000u);
    SetEffectScale(0x246350cu, 0x45000000u);
    SetEffectScale(0x246350du, 0x45000000u);

    if (GetTrailEffectId() != 0) {
        uint32_t nTrail = GetTrailEffectId();
        pView->CreateEffect(nTrail, 0);
        SetEffectScale(0x47f791au, 0x44800000u);
    }

    pView->mpEffectInfo = nullptr;
    pView->mFlag38 = 0;

    float fScale = ((cSpaceProjectile*)*(void**)((uint8_t*)pData + 0x108))->GetEffectId();
    void* pEffect = FindEffect(0x246350au);
    if (pEffect != nullptr) {
        UpdateBeamEffect(pEffect, &fScale, 1);
        if (GetProjectileType() == 0xe810d505u) {
            uint32_t nTarget = ((cSpaceProjectile*)*(void**)((uint8_t*)pData + 0x108))->GetEffectId();
            if (nTarget != 0) {
                uint32_t nColor = ((cSpaceProjectile*)*(void**)((uint8_t*)pData + 0x108))->GetEffectId();
                if (IsEmpireObjectValid((void*)(intptr_t)nColor)) {
                    UpdateBeamEffect(pEffect, &nColor, 5);
                    void* pSecond = FindEffect(0x9138b729u);
                    if (pSecond != nullptr)
                        UpdateBeamEffect(pSecond, &nColor, 5);
                }
            }
        }
    }
    return pView;
}

// @ 0x00cc3000
cSpatialObjectView* MakeDefaultAoEAreaView(void* pObject)
{
    cSpatialObjectView* pView =
        (cSpatialObjectView*)operator_new(0x34, "Simulator/cDefaultAoEAreaView", 0, 0, 0, 0);
    if (pView == nullptr)
        pView = nullptr;
    else
        pView->SetObject(nullptr);

    cDefaultAoEArea* pArea = nullptr;
    if (pObject != nullptr)
        pArea = (cDefaultAoEArea*)((IRefCounted*)pObject)->Query((const void*)0x4167194);

    pView->SetObject(pObject);

    if (IsAoEPreviewActive()) {
        uint32_t nPreviewEffect = GetAoEPreviewEffectId();
        CreateEffectRef(nPreviewEffect, 0, 0x4178e6eu);
    }

    uint32_t nNoteEffect = pArea->GetNoteEffectID();
    CreateEffectRef(nNoteEffect, 0, 0x4178e6fu);

    uint32_t nNounId = ((cSpaceProjectile*)pArea)->GetEffectId();
    if (nNounId != 0xffffffffu) {
        uint32_t nId = ((cSpaceProjectile*)pArea)->GetEffectId();
        NounManager(nId);
        if (FindNounFromId(nId) != nullptr) {
            void* pEffect = FindEffect(0x4178e6eu);
            if (pEffect != nullptr)
                UpdateBeamEffect(pEffect, &nId, 5);
            pEffect = FindEffect(0x4178e6fu);
            if (pEffect != nullptr)
                UpdateBeamEffect(pEffect, &nId, 5);
        }
    }
    return pView;
}

// @ 0x00cc3140
cSpatialObjectView* cCulturalProjectileView::MakeView(void* pObject)
{
    cSpatialObjectView* pView =
        (cSpatialObjectView*)operator_new(0x38, "Simulator/cCulturalProjectileView", 0, 0, 0, 0);
    if (pView == nullptr)
        pView = nullptr;
    else
        pView->SetObject(nullptr);

    pView->SetObject(pObject);
    pView->mFlag38 = 0;

    CreateEffectRef(0x4cc9a429u, 0, 0);
    SetEffectScale(0, 0x44800000u);

    void* pEffect = FindEffect(0);
    if (pEffect != nullptr) {
        uint32_t nColor = ((cSpaceProjectile*)pObject)->GetEffectId();
        NounManager(nColor);
        if (FindNounFromId(nColor) != nullptr)
            UpdateBeamEffect(pEffect, &nColor, 5);
    }
    return pView;
}

// @ 0x00cc3220
void cSpatialObjectView_s00cc_3220::FUN_00cc3220(u32 fbits, u32 f2)
{
    HandleSimulationUpdate(fbits, f2);

    void* r = 0;
    if (mpObject)
        r = VT_B8_1(mpObject, 0x4f76f08);

    u8 inGame = 0;
    if (GetCurrentGameMode_s00cc_3220() == (void*)0x1654c04) {
        FUN_00cf74c0();
        FUN_00cf74f0();
        if (FUN_00cf1540())
            inGame = 1;
    }
    if (inGame != mInGameMode) {
        mInGameMode = inGame;
        cSpatialObject* o = (cSpatialObject*)mpObject;
        if (o->GetEffect(0))
            VT_30_1(o->GetEffectObject(0), (int)inGame);
    }

    if (r && ((cSpatialObject*)r)->FUN_00cb41b0() != 0) {
        void* e = ((cSpatialObject*)mpObject)->GetEffectObject(0);
        if (e) {
            u64 v = ((cSpatialObject*)r)->FUN_00cb41b0();
            float f = 1.0f - (float)v * *(float*)0x13f999c;
            if (f < 0.0f)
                f = 0.0f;
            if (f > 1.0f)
                f = 1.0f;
            VT_44_3(e, 4, &f, 1);
        }
    }
}

// @ 0x00cc3380
void* cResourceProjectileView::MakeView(cSpatialObject* p)
{
    cResourceProjectileView* v = (cResourceProjectileView*)
        EANew(0x34, "Simulator/cResourceProjectileView", 0, 0, 0, 0);
    if (v) {
        v->ctor();
        v->mpVtbl = (void*)0x14607a8;
    }
    VT_24_1(v, p);

    u32 kind = 0x4aad8baf;
    if (p) {
        void* hit = (void*)VT_0C_1(p, 0x5776a28);
        if (hit && FUN_00c8e7c0())
            kind = 0xf95108a3;
    }
    FUN_00c8b130(kind, 0, 0);
    FUN_00c88a00(0, 1024.0f);
    void* e = ((cSpatialObject*)v)->GetEffectObject(0);
    if (e) {
        int id = VT_4C_0(p);
        NounManager_s00cc_3220(id);
        if (FUN_00b25f40(id)) {
            EffectUpdate blk;
            blk.mFlags = 0;
            blk.mCount = 0;
            VT_44_3(e, 5, (float*)&blk, 3);
        }
    }
    return v;
}

// @ 0x00cc3490
void cSpatialObjectView_s00cc_3220::FUN_00cc3490(u32 fbits, u32 p)
{
    HandleSimulationUpdate(fbits, p);
    if (!mpObject)
        return;
    void* r = VT_B8_1(mpObject, 0x5776a28);
    if (!r)
        return;
    u64 v1 = ((cSpatialObject*)r)->FUN_00cb4340();
    if (!(v1 > 0))
        return;
    void* h = ((cSpatialObject*)mpObject)->FUN_00c888e0(0);
    if (!h)
        return;
    u64 v = ((cSpatialObject*)r)->FUN_00cb4340();
    float fr = 1.0f - (float)v * *(float*)0x13f999c;
    VT_44_3(h, 4, &fr, 1);
}

// @ 0x00cc3570
void* cSpaceDefenseMissileView_s00cc_3220::MakeView(cSpatialObject* p)
{
    cSpaceDefenseMissileView_s00cc_3220* v = (cSpaceDefenseMissileView_s00cc_3220*)
        EANew(0x3c, "Simulator/cSpaceDefenseMissileView", 0, 0, 0, 0);
    if (v) {
        v->ctor();
        v->mpVtbl = (void*)0x1476804;
    }
    VT_24_1(v, p);

    cSubObject* sub = p ? (cSubObject*)VT_0C_1(p, 0x244d3c0) : 0;
    u32 kind = FUN_00c9c2b0();
    FUN_00c8b130(kind, 0, 0x56bb11a);
    FUN_00c88a00(0x56bb11a, 1024.0f);

    if (VT_AC_0(sub->mpOwner) != 0) {
        VT_24_1(v, p);
        return v;
    }
    void* world = GonzagoModelWorld();
    cModelInstance* model = (cModelInstance*)VT_0C_3(world, 0x2e81370, *(int*)0x0169aab0, 0);
    if (model) {
        // the model is refcounted; the counter is bumped while held
        model->mRefCount = model->mRefCount + 1;
    }
    // NOTE: the view's own slot-0x28 call with (world, model + 0x8, scratch + 0x18)
    // is not reconstructed (its argument layout could not be recovered).
    VT_A8_2(sub->mpOwner, model, world);
    if (model->mRefCount > 1) {
        model->mRefCount = model->mRefCount - 1;
        return v;
    }
    ((void (__thiscall*)(void*, u32))((void***)model->mpVtbl)[0x170 / 4])(model, model->mFlags >> 31);
    return v;
}

// @ 0x00cc36d0
void* cSpatialObjectView_s00cc_3220::FUN_00cc36d0(u8 flag)
{
    mpVtbl = (void*)0x14767d0;
    if (mpObject) {
        void* r = VT_B8_1(mpObject, 0x24630ce);
        if (r) {
            void* t = ((cSpatialObject*)r)->mpSpaceToolData;
            if (t) {
                if (((cSPSpaceToolData*)t)->IsInContext())
                    ((cSpatialObject*)mpObject)->DestroyAllEffects(0);
            }
        }
    }
    BaseDtor();
    if (flag & 1)
        EAFree(this);
    return this;
}

// @ 0x00cc3730
void* cArtilleryProjectileView::MakeView(cSpatialObject* p)
{
    cArtilleryProjectileView* v = (cArtilleryProjectileView*)
        EANew(0x34, "Simulator/cArtilleryProjectileView", 0, 0, 0, 0);
    if (v) {
        v->ctor();
        v->mpVtbl = (void*)0x1460608;
    }
    VT_24_1(v, p);

    if (!p)
        return v;
    cSubObject* sub = (cSubObject*)VT_0C_1(p, 0x1428a48);
    if (!sub)
        return v;

    int mode = FUN_00cb37c0();
    if (mode == 2) {
        FUN_00c8b130(0x5cd27dc5, 0, 0x46e9287);
        void* e = ((cSpatialObject*)v)->GetEffectObject(0x46e9287);
        if (e) {
            void* q = VT_18_0(sub->mpTool);
            if (q) {
                void* m = VT_5C_1(q, 0xce9f6639);
                if (m) {
                    FUN_00434040();
                    EffectUpdate blk;
                    blk.mFlags = 0;
                    blk.mCount = 0;
                    VT_20_1(e, &blk);
                    blk.mScale = VT_34_F(sub->mpOwner);
                    VT_18_1(e, &blk);
                    VT_44_3(e, 5, (float*)VT_E0_0(m), 3);
                }
            }
        }
        return v;
    }
    if ((u32)(mode - 3) > 1) {
        FUN_00c8b130(0x364ea7b9, 0, 0);
        return v;
    }
    u32 kind = (FUN_00cb37c0() == 3) ? 0x91a80211 : 0x6211b885;
    FUN_00c8b130(kind, 0, 0);
    if (VT_4C_0(sub) != -1) {
        u32 id = VT_4C_0(sub);
        NounManager_s00cc_3220(id);
        cNounObject* obj = (cNounObject*)FUN_00b25f40(id);
        if (obj) {
            EffectUpdate blk;
            blk.mFlags = obj->mEffectParam;
            blk.mCount = 0;
            void* e = ((cSpatialObject*)v)->GetEffectObject(0);
            if (e)
                VT_44_3(e, 5, (float*)&blk, 3);
        }
    }
    return v;
}

// @ 0x00cc3950
void cSpatialObjectView_s00cc_3220::FUN_00cc3950(u32 fbits, u32 f2)
{
    HandleSimulationUpdate(fbits, f2);

    u8 inGame = 0;
    if (GetCurrentGameMode_s00cc_3220() == (void*)0x1654c04) {
        FUN_00cf74c0();
        FUN_00cf74f0();
        if (FUN_00cf1540())
            inGame = 1;
    }
    if (inGame != mInGameMode) {
        mInGameMode = inGame;
        cSpatialObject* o = (cSpatialObject*)mpObject;
        if (o->GetEffect(0x500f162))
            VT_30_1(o->GetEffectObject(0x500f162), (int)inGame);
        if (o->GetEffect(0x6565ae1))
            VT_30_1(o->GetEffectObject(0x6565ae1), (int)inGame);
    }

    if (((cSpatialObject*)mpObject)->GetEffect(0x6565ae1)) {
        void* sub = VT_0C_0(this);
        if (sub) {
            cToolInstance* tool = (cToolInstance*)VT_0C_1(sub, 0x24270c4);
            if (tool) {
                float tmp[3];
                tmp[0] = tool->mPosition.x;
                tmp[1] = tool->mPosition.y;
                tmp[2] = tool->mPosition.z;

                EffectUpdate blk;
                blk.mFlags = 0;
                blk.mCount = 0;
                blk.mOrientation.Ctor((void*)0x0169b024);
                float out[4];
                PM_Construct(out, out, tmp);
                float* surf = (float*)PM_DirToSurface(out, tmp);
                blk.mPosition.x = surf[0];
                blk.mPosition.y = surf[1];
                blk.mPosition.z = surf[2];
                blk.mFlags |= 4;
                blk.mCount = (u8)(blk.mCount + 1);
                float* orient = (float*)PM_BuildSurfaceOrientation(tmp, out);
                SP_Matrix3FromQuaternion(out, orient);
                blk.mFlags |= 2;
                blk.mCount = (u8)(blk.mCount + 1);
                blk.mScale = FUN_0104bdb0();
                blk.mCount = (u8)(blk.mCount + 1);
                if (mModeVariant) {
                    float v[3];
                    v[0] = tool->mPosition.x;
                    v[1] = tool->mPosition.y;
                    v[2] = tool->mPosition.z;
                    cTerrainObject* terrain = (cTerrainObject*)FUN_00b894a0(v);
                    if (terrain) {
                        void* m = VT_6C_0(terrain);
                        blk.mScale = ((cTerrainObject*)m)->mHeight;
                        blk.mCount = (u8)(blk.mCount + 1);
                    }
                }
                void* e = ((cSpatialObject*)mpObject)->GetEffectObject(0x6565ae1);
                VT_18_1(e, &blk);
            }
        }
    }

    if (mpObject) {
        cToolInstance* tool = (cToolInstance*)VT_B8_1(mpObject, 0x24270c4);
        if (tool && tool->mState == 1) {
            FUN_00c8ad30(0x500f162, 0);
            FUN_00c8ad30(0x6565ae1, 1);
        }
    }
}

// @ 0x00cc3c30
void cSpatialObjectView_s00cc_3220::FUN_00cc3c30(u32 fbits, u32 f2)
{
    HandleSimulationUpdate(fbits, f2);

    if (mpObject) {
        cToolInstance* tool = (cToolInstance*)VT_B8_1(mpObject, 0x24270c4);
        if (tool && tool->mState == 2)
            FUN_00c8ad30(0, 0);
    }
    if (mpObject)
        VT_B8_1(mpObject, 0x24270c6);

    float pos[3];
    float dir[3];
    FUN_00cb5450(pos, dir);

    void* e1 = ((cSpatialObject*)mpObject)->GetEffectObject(1);
    if (e1) {
        EffectUpdate blk;
        blk.mFlags = 0;
        blk.mCount = 0;
        blk.mPosition.x = pos[0];
        blk.mPosition.y = pos[1];
        blk.mPosition.z = pos[2];
        blk.mOrientation.m[0] = dir[0];
        blk.mOrientation.m[1] = dir[1];
        blk.mOrientation.m[2] = dir[2];
        VT_44_3(e1, 0xd, (float*)&blk, 6);
    }

    void* e2 = ((cSpatialObject*)mpObject)->GetEffectObject(2);
    if (e2) {
        float off[3];
        off[0] = dir[0] - pos[0];
        off[1] = dir[1] - pos[1];
        off[2] = dir[2] - pos[2];
        EffectUpdate blk;
        blk.mFlags = 0;
        blk.mCount = 0;
        blk.mPosition.x = pos[0];
        blk.mPosition.y = pos[1];
        blk.mPosition.z = pos[2];
        blk.mOrientation.Ctor((void*)0x0169b024);
        SP_Matrix3FromFacingAndUp(blk.mOrientation.m, off, pos);
        blk.mFlags |= 2;
        blk.mCount = (u8)(blk.mCount + 1);
        VT_18_1(e2, &blk);
    }

    void* e3 = ((cSpatialObject*)mpObject)->GetEffectObject(3);
    if (e3) {
        float surf[3];
        surf[0] = *(float*)0x0169b048;
        surf[1] = *(float*)0x0169b04c;
        surf[2] = *(float*)0x0169b050;
        EffectUpdate blk;
        blk.mFlags = 0;
        blk.mCount = 0;
        blk.mOrientation.Ctor((void*)0x0169b024);
        float out[4];
        PM_Construct(out, out, surf);
        float* p = (float*)PM_DirToSurface(out, surf);
        blk.mPosition.x = p[0];
        blk.mPosition.y = p[1];
        blk.mPosition.z = p[2];
        blk.mFlags |= 4;
        blk.mCount = (u8)(blk.mCount + 1);
        float* orient = (float*)PM_BuildSurfaceOrientation(dir, out);
        SP_Matrix3FromQuaternion(out, orient);
        blk.mFlags |= 2;
        blk.mCount = (u8)(blk.mCount + 1);
        VT_18_1(e3, &blk);
    }
}

// @ 0x00cc3f40
void cSpatialObjectView_s00cc_3220::FUN_00cc3f40(u32 fbits, u32 f2)
{
    HandleSimulationUpdate(fbits, f2);
    if (!mpObject)
        return;
    void* area = (void*)VT_B8_1(mpObject, 0x4167194);
    if (!area)
        return;
    void* e = ((cSpatialObject*)mpObject)->GetEffectObject(0x4178e6e);
    if (!e)
        return;

    float scratch[4];
    FUN_00cb5d80(scratch, scratch + 2);

    EffectUpdate blk;
    blk.mFlags = 0;
    blk.mCount = 0;
    blk.mPosition.x = scratch[0];
    blk.mPosition.y = scratch[1];
    blk.mPosition.z = scratch[2];
    blk.mOrientation.Ctor((void*)0x0169b024);
    float* q = (float*)SP_Matrix3FromQuaternion(blk.mOrientation.m, scratch + 1);
    for (int i = 0; i < 9; ++i)
        blk.mOrientation.m[i] = q[i];
    // NOTE: the final scale component comes from the AoE area object (offset not
    // reconstructed).
    blk.mFlags |= 4;
    blk.mCount = (u8)(blk.mCount + 1);
    VT_18_1(e, &blk);
}

// @ 0x00cc4160
void cc4160_vec::insert(float* pos, const float* value)
{
    float* end = m_end;
    if (end != m_cap) {
        if (pos <= value && value < end)
            ++value;
        if (end)
            *end = end[-1];
        int n = (int)((char*)(m_end - 1) - (char*)pos);
        memmove((char*)m_end - ((n >> 2) << 2), pos, (unsigned int)n);
        *pos = *value;
        m_end = m_end + 1;
        return;
    }
    int count = (int)(m_end - m_begin);
    int newCap = count == 0 ? 1 : count * 2;
    float* dst = 0;
    if (newCap != 0)
        dst = (float*)EAAllocate((unsigned int)(newCap * 4), "Simulator", 0, 0, (void*)0x13ebb38, 0xd1);
    memcpy(dst, m_begin, (unsigned int)((char*)pos - (char*)m_begin));
    float* p = dst + (pos - m_begin);
    if (p)
        *p = *value;
    float* q = (float*)memcpy(p + 1, pos, (unsigned int)((char*)m_end - (char*)pos));
    float* newEnd = q + (m_end - pos);
    if (m_begin != 0 && m_begin != m_alloc)
        eaFree(m_begin);
    m_begin = dst;
    m_end = newEnd;
    m_cap = dst + newCap;
}

// @ 0x00cc4270
namespace SP {
void cDefaultBeamProjectileView_s00cc_4270::HandleSimulationUpdate(int unk, int deltaTime)
{
    cSpatialObjectView_s00cc_4270::HandleSimulationUpdate(unk, deltaTime);

    {
        bool hidden;
        if (GetCurrentGameMode() == &kCivGameMode && cCivModeStrategy::Get()->f74f0()->f1540())
            hidden = true;
        else
            hidden = false;
        if (hidden != mbHidden) {
            mbHidden = hidden;
            if (mpObject->HasEffect(kBeamEffect))
                mpObject->GetEffect(kBeamEffect)->SetIsHidden(hidden);
            if (mpObject->HasEffect(kBeamStartEffect))
                mpObject->GetEffect(kBeamStartEffect)->SetIsHidden(hidden);
            if (mpObject->IsEffectRunning(kBeamEndEffectB))
                mpObject->GetEffect(kBeamEndEffectB)->SetIsHidden(hidden);
            if (mpObject->IsEffectRunning(kBeamEndEffectC))
                mpObject->GetEffect(kBeamEndEffectC)->SetIsHidden(hidden);
            if (mpObject->IsEffectRunning(kBeamEndEffectD))
                mpObject->GetEffect(kBeamEndEffectD)->SetIsHidden(hidden);
        }
    }
    mnTime += deltaTime;

    if (!mpObject)
        return;
    cDefaultBeamProjectile_s00cc_4270* beam = (cDefaultBeamProjectile_s00cc_4270*)mpObject->Cast(kTypeDefaultBeamProjectile);
    if (!beam || beam->GetPoints().empty())
        return;

    const eastl::vector_s00cc_4270<Vector3_s00cc_4270>& points = beam->GetPoints();
    int n = (int)points.size();
    n = eastl::min(n, 0x80);
    eastl::fixed_vector_s00cc_4270<float, 384> vertices;
    for (int i = 0; i < n; i++) {
        vertices.push_back(points[i].x);
        vertices.push_back(points[i].y);
        vertices.push_back(points[i].z);
    }
    Vector3_s00cc_4270 start = points.front();
    Vector3_s00cc_4270 end = points.back();

    Matrix3 rot;
    Swarm::IVisualEffect* beamEffect = mpObject->GetEffect(kBeamEffect);
    if (beamEffect) {
        beamEffect->SetFloatParams(Swarm::kFloatParamBeamPoints, vertices.data(), n * 3);
        Transform t;
        t.SetOffset(start);
        t.SetRotation(Matrix3FromFacingAndUp(rot, (end - start).Normalized(), start.Normalized()));
        beamEffect->SetSourceTransform(t);
        float scale = 1.0f;
        beamEffect->SetVectorParams(Swarm::kVectorParamBeamEnd, &end, 1);
        beamEffect->SetFloatParams(Swarm::kFloatParamBeamScale, &scale, 1);
    }

    bool b16c = beam->mb16c;
    bool b16d = beam->mb16d;
    bool has1e0 = beam->Has1e0();
    bool hittingPlayer = beam->IsHittingPlayer();
    bool anyActive = b16c || b16d || has1e0 || hittingPlayer;

    Swarm::IVisualEffect* startEffect = mpObject->GetEffect(kBeamStartEffect);
    if (startEffect) {
        Transform t;
        t.SetOffset(start);
        t.SetRotation(Matrix3FromFacingAndUp(rot, (points[1] - points[0]).Normalized(), start.Normalized()));
        startEffect->SetSourceTransform(t);
    }

    // transform at the beam's end
    Transform endTransform(end);
    Vector3_s00cc_4270 dir;
    if (points.size() > 1)
        dir = points.back() - points[points.size() - 2];
    else
        dir = start - end;
    Vector3_s00cc_4270 endFacing = dir.SafeNormalized();
    if (beam->UseOrientation())
        Matrix3FromQuaternion(rot, beam->mOrientation);
    else
        Matrix3FromFacingAndUp(rot, endFacing, start.Normalized());
    endTransform.SetRotation(rot);

    Swarm::IVisualEffect* effectB = mpObject->GetEffect(kBeamEndEffectB);
    Swarm::IVisualEffect* effectC = mpObject->GetEffect(kBeamEndEffectC);
    Swarm::IVisualEffect* hitEffect = mpObject->GetEffect(kBeamHitPlayerEffect);
    Swarm::IVisualEffect* effectD = mpObject->GetEffect(kBeamEndEffectD);

    if (effectB) {
        UpdateEffectRunning(mpObject, kBeamEndEffectB, b16c, mb16c);
        if (mpObject->IsEffectRunning(kBeamEndEffectB))
            effectB->SetSourceTransform(endTransform);
    }
    if (effectC) {
        UpdateEffectRunning(mpObject, kBeamEndEffectC, b16d, mb16d);
        if (mpObject->IsEffectRunning(kBeamEndEffectC))
            effectC->SetSourceTransform(endTransform);
    }
    if (hitEffect) {
        UpdateEffectRunning(mpObject, kBeamHitPlayerEffect, hittingPlayer, mbHittingPlayer);
        if (mpObject->IsEffectRunning(kBeamHitPlayerEffect)) {
            Transform t;
            t.SetOffset(end);
            t.SetRotation(Matrix3FromFacingAndUp(rot, endFacing, end.Normalized()));
            hitEffect->SetSourceTransform(t);
        }
    }
    if (effectD) {
        UpdateEffectRunning(mpObject, kBeamEndEffectD, has1e0 && !hittingPlayer, mbHas1e0);
        if (mpObject->IsEffectRunning(kBeamEndEffectD)) {
            Transform t;
            t.SetOffset(end);
            t.SetRotation(Matrix3FromFacingAndUp(rot, endFacing, end.Normalized()));
            effectD->SetSourceTransform(t);
        }
    }

    mbAnyActive = anyActive;
    mb16c = b16c;
    mbHas1e0 = has1e0;
    mb16d = b16d;
    mbHittingPlayer = hittingPlayer;
}
}  // namespace SP
