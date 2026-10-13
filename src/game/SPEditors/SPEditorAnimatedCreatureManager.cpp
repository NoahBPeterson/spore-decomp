// src/game/SPEditors/SPEditorAnimatedCreatureManager.cpp -- migrated from slice(s) s0059c4c0, s0059b4b0, s0059acb0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorAnimatedCreatureManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cAnimatingCreature.h"

// unnamed retail callees and globals (address in the comment)
extern char gAnimVtblA[];   // 0x013f64b4
extern float gAnimVecX;     // 0x015e590c
extern float gAnimVecY;     // 0x015e5910
extern float gAnimVecZ;     // 0x015e5914
extern float gAnimScale;    // 0x015e5984
extern float gAnimHalf;     // 0x01471064
extern float gAnim2_5;      // 0x013f6488
#include <math.h>
#include <intrin.h>
#include "SP/cAnimInfo.h"
#include "EA/Swarm/cIVisualEffect.h"
#include "SP/cSPEditorAnimatedCreatureData.h"
#include "SP/cSPEditorAnimatedCreatureManager.h"
#include "SP/cSPEditorAnimatedEventInfo.h"
#include "SP/cSPEditorAnimationManager.h"
#include "cSPMatrix3.h"
#include "cSPQuaternion.h"
#include "cSPVector3.h"
#include "SP/cIModelWorld.h"
#include "EA/Sockets/Socket.h"
#include "EA/IO/FileStream.h"
#include "EA/AutoRefCount.h"

// ---- items of slice s0059acb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace Simulator {
class cAnimatingCreature {
public:
    char pad0[0x70];
    uint32_t mFlags;                // +0x70
    char pad74[0x150 - 0x74];
    uint8_t mByte150;               // +0x150
    void AddRef();                  // 0x00a02c30
    void Release();                 // 0x00a05270
    bool IsSomething(int a);        // 0x00a02b20
};
}
namespace Simulator {
class cAnimatedData {
public:
    virtual void slot0();           // vptr at +0
    int mField04;                   // +0x04
    cAnimatingCreature* mpCreature; // +0x08
    int mField0c;                   // +0x0c
    int mField10, mField14, mField18;   // +0x10..0x18
    int mField1c;                   // +0x1c
    float mVec0[3];                 // +0x20
    float mVec1[3];                 // +0x2c
    float mVec2[3];                 // +0x38
    float mField44, mField48;       // +0x44, +0x48
    float mField4c;                 // +0x4c
    float mField50;                 // +0x50
    bool mField54, mField55;        // +0x54, +0x55
    float mField58, mField5c, mField60;   // +0x58 target
    float mField64, mField68, mField6c;   // +0x64 copy
    bool mField70;                  // +0x70
    float mField74, mField78, mField7c;   // +0x74..0x7c
    float mField80;                 // +0x80
    bool mField84;                  // +0x84

    void FUN_0059ae20(cAnimatingCreature* p, int a);   // 0x0059ae20
    void FUN_0059ae60();                               // 0x0059ae60
    bool FUN_0059ae80();                               // 0x0059ae80
    void FUN_0059aea0(char b);                         // 0x0059aea0
    void* FUN_0059ace0();                              // 0x0059ace0
    void* FUN_0059b0b0(char flags);                    // 0x0059b0b0
    void FUN_0059b2f0(float angle, char update);       // 0x0059b2f0
    void FUN_0059b390();                               // 0x0059b390
    void FUN_0059b420(char b);                         // 0x0059b420
    void FUN_0059aed0(float* out, const float* q, const float* v);  // 0x0059aed0
    void SetTargetPosition(int a, float angle);        // 0x0059b0f0
};
}
extern char gAnimVtblA[];   // 0x013f64b4
extern float gAnimVecX;     // 0x015e590c
extern float gAnimVecY;     // 0x015e5910
extern float gAnimVecZ;     // 0x015e5914
extern float gAnimScale;    // 0x015e5984
extern float gAnimHalf;     // 0x01471064
extern float gAnim2_5;      // 0x013f6488
// ---- items of slice s0059acb0 end

// ---- items of slice s0059b4b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kPi59;      // 0x013f64d4
extern float kTwoPi59;   // 0x0150dff4
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
inline void* operator new(size_t, void* p) { return p; }
namespace EA {
template <typename T>
class RefCountTemplate_s0059_b4b0 {
public:
    RefCountTemplate_s0059_b4b0() : mnRefCount(0) {}
    virtual ~RefCountTemplate_s0059_b4b0() {}
    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) {
            mnRefCount = 1;
            delete this;
            return 0;
        }
        return mnRefCount;
    }
protected:
    T mnRefCount;   // +0x4
};
}
namespace EA {
template <typename T>
class AutoRefCount_s0059_b4b0 {
public:
    T* mpObject;
    AutoRefCount_s0059_b4b0() : mpObject(0) {}
    AutoRefCount_s0059_b4b0(const AutoRefCount_s0059_b4b0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s0059_b4b0() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s0059_b4b0& operator=(T* p)
    {
        T* const pOld = mpObject;
        if (p != pOld) {
            if (p) p->AddRef();
            mpObject = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    void Reset()
    {
        if (mpObject) { T* const pTemp = mpObject; mpObject = 0; pTemp->Release(); }
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
namespace SP {
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& o) : x(o.x), y(o.y), z(o.z) {}
    cSPVector3 operator-(const cSPVector3& o) const { return cSPVector3(x - o.x, y - o.y, z - o.z); }
    cSPVector3 operator+(const cSPVector3& o) const { return cSPVector3(x + o.x, y + o.y, z + o.z); }
    cSPVector3 operator*(float s) const { return cSPVector3(x * s, y * s, z * s); }
    cSPVector3 operator-() const { return cSPVector3(-x, -y, -z); }
    bool operator!=(const cSPVector3& o) const { return x != o.x || y != o.y || z != o.z; }
    float Length() const { return (float)sqrt(x * x + y * y + z * z); }
    __forceinline cSPVector3 Normalized() const
    {
        float inv = 1.0f / (float)sqrt(x * x + (y * y + z * z));
        return cSPVector3(x * inv, y * inv, z * inv);
    }
    __forceinline cSPVector3 Normalize() const
    {
        float ax = x, ay = y, az = z;
        float inv = 1.0f / (float)sqrt(ax * ax + ay * ay + az * az);
        return cSPVector3(ax * inv, ay * inv, az * inv);
    }
    cSPVector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
};
}
namespace SP {
struct cSPMatrix3 {
    cSPVector3 mRow[3];
};
}
namespace SP {
inline cSPVector3 operator*(const cSPVector3& v, const cSPMatrix3& m)
{
    return cSPVector3(m.mRow[0].x * v.x + m.mRow[1].x * v.y + m.mRow[2].x * v.z,
                      m.mRow[0].y * v.x + m.mRow[1].y * v.y + m.mRow[2].y * v.z,
                      m.mRow[0].z * v.x + m.mRow[1].z * v.y + m.mRow[2].z * v.z);
}
}
namespace SP {
struct FilterSettings {
    unsigned __int64 requiredGroupFlags;   // +0x00
    unsigned __int64 excludedGroupFlags;   // +0x08
    void* filterFunction;                  // +0x10
    uint8_t collisionMode;                 // +0x14
    uint8_t flags;                         // +0x15
    FilterSettings() : requiredGroupFlags(), excludedGroupFlags(), filterFunction(0), collisionMode(4), flags(0) {}
    void SetRequiredGroup(uint32_t group)
    {
        if (group < 64)
            ((uint32_t*)&requiredGroupFlags)[group >> 5] |= 1 << (group & 31);
    }
};
}
namespace SP {
class cIModelWorld_s0059_b4b0 {
public:
    virtual void AddRef();     // +0x0
    virtual void Release();    // +0x4
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08();
    virtual void* FindFirstModelAlongLine(const cSPVector3& p1, const cSPVector3& p2, float* factorDst,
                                          cSPVector3* dstPoint, cSPVector3* dstNormal,
                                          FilterSettings& settings, int* a, int* b);   // +0x24
};
}
namespace SP {
class cISPCreatureAnimWorld_s0059_b4b0 {
public:
    virtual void AddRef();     // +0x00
    virtual void Release();    // +0x04
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void SetWorld(cIModelWorld_s0059_b4b0* world, int a, int b, int c, int d);   // slot +0x1c
};
}
namespace SP {
class cSPEditorAnimationManager_s0059_b4b0 : public EA::RefCountTemplate_s0059_b4b0<int> {
public:
    cSPEditorAnimationManager_s0059_b4b0();   // 0x0059dac0 (out of line)
    void Init();                   // 0x0059db40
    char pad_8[0x20 - 0x8];
};
}
namespace SP {
class cSPEditorAnimatedCreatureManager_s0059_b4b0 : public EA::RefCountTemplate_s0059_b4b0<int> {
public:
    void Init(cIModelWorld_s0059_b4b0* pModelWorld, bool flag);  // 0x0059c060 (SP::cSPEditorAnimatedCreatureManager::Init)

    // rbtree members laid out from +0x8..+0x24, vector +0x24..+0x38
    char pad_08[0x38 - 0x8];
    EA::AutoRefCount_s0059_b4b0<cISPCreatureAnimWorld_s0059_b4b0>     mAnimWorld;     // +0x38
    EA::AutoRefCount_s0059_b4b0<cSPEditorAnimationManager_s0059_b4b0> mAnimManager;   // +0x3c
    EA::AutoRefCount_s0059_b4b0<cIModelWorld_s0059_b4b0>              mModelWorld;    // +0x40
    unsigned int                                mCurrentID;     // +0x44
};
}
void* FUN_0067cb20();   // 0x0067cb20
struct Vector3M { float x, y, z; Vector3M() {} Vector3M(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Matrix33T {
    Vector3M xAxis, yAxis, zAxis;                 // 9 floats
    Matrix33T() {}
    Matrix33T& operator=(const Matrix33T& o);     // out of line @ 0x0041cb40
};
struct Quaternion { float x, y, z, w; };
cSPVector3 Normalize(const cSPVector3& v);                                          // 0x00436ce0
// ---- items of slice s0059b4b0 end

// @ 0x0059ace0
void* Simulator::cAnimatedData::FUN_0059ace0()
{
    *(void**)this = (void*)gAnimVtblA;
    mField04 = 0;
    mpCreature = 0;
    mField0c = 0;
    mField10 = 0;
    mField14 = 0;
    mField18 = 0;
    mField1c = 0;
    mVec0[0] = gAnimVecX; mVec0[1] = gAnimVecY; mVec0[2] = gAnimVecZ;
    mVec1[0] = gAnimVecX; mVec1[1] = gAnimVecY; mVec1[2] = gAnimVecZ;
    mVec2[0] = gAnimVecX; mVec2[1] = gAnimVecY; mVec2[2] = gAnimVecZ;
    mField44 = 0.0f;
    mField48 = 0.0f;
    mField4c = gAnim2_5;
    mField50 = gAnimScale;
    mField54 = false;
    mField55 = false;
    mField58 = gAnimVecX; mField5c = gAnimVecY; mField60 = gAnimVecZ;
    mField64 = gAnimVecX; mField68 = gAnimVecY; mField6c = gAnimVecZ;
    mField74 = 0.0f;
    mField78 = 0.0f;
    mField7c = 0.0f;
    mField70 = true;
    mField80 = gAnimHalf;
    mField84 = false;
    return this;
}




// @ 0x0059ae60
void Simulator::cAnimatedData::FUN_0059ae60()
{
    mField0c = 0;
    _ReadWriteBarrier();
    if (mpCreature) {
        cAnimatingCreature* p = mpCreature;
        mpCreature = 0;
        p->Release();
    }
}



// @ 0x0059c030
float WrapAngleToPi(float angle)
{
    float r = fmodf(angle, kTwoPi59);
    if (r >= kPi59)
        return r - kTwoPi59;
    return r;
}


// @ 0x0059c060
void SP::cSPEditorAnimatedCreatureManager_s0059_b4b0::Init(cIModelWorld_s0059_b4b0* pModelWorld, bool flag)
{
    mModelWorld = pModelWorld;
    void* pProps = FUN_0067cb20();
    typedef void* (__thiscall* GetEditorFn)(void*, const wchar_t*);
    GetEditorFn getEditor = *(GetEditorFn*)(*(char**)pProps + 0x20);
    mAnimWorld = (cISPCreatureAnimWorld_s0059_b4b0*)getEditor(pProps, L"Editor");
    if (!mAnimWorld)
        return;
    if (*(int*)(*(int*)(*(int*)0x015fd918 + 0x3c) + 0x118) != 0) {
        void* p2 = FUN_0067cb20();
        typedef void (__thiscall* NotifyFn)(void*, unsigned int);
        NotifyFn notify = *(NotifyFn*)(*(char**)p2 + 0x3c);
        notify(p2, 0x4373c4f);
    }
    if (flag) {
        mAnimWorld->SetWorld(pModelWorld, 1, 1, 0, 1);
        cSPEditorAnimationManager_s0059_b4b0* pMgr =
            new ("Editor", 0, 0, 0, 0) cSPEditorAnimationManager_s0059_b4b0();
        mAnimManager = pMgr;
        if (mAnimManager)
            mAnimManager->Init();
    } else {
        mAnimWorld->SetWorld(pModelWorld, 1, 0, 0, 0);
    }
}


// @ 0x0059c190
Matrix33T& Matrix3FromQuaternion(Matrix33T& result, const Quaternion& q)
{
    float x = q.x, y = q.y, z = q.z, w = q.w;
    Matrix33T tmp;
    tmp.xAxis = Vector3M(1.0f - (z * z + y * y) * 2.0f, (w * z + y * x) * 2.0f, (z * x - w * y) * 2.0f);
    tmp.yAxis = Vector3M((y * x - w * z) * 2.0f, 1.0f - (z * z + x * x) * 2.0f, (w * x + z * y) * 2.0f);
    tmp.zAxis = Vector3M((w * y + z * x) * 2.0f, (z * y - w * x) * 2.0f, 1.0f - (y * y + x * x) * 2.0f);
    return result = tmp;
}

