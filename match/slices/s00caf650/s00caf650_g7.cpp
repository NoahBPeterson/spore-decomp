// Slice s00caf650 (gold7): bone-state storage helpers (bucket release, bone-set copy,
// node-core copy) plus the flying-locomotion steering update that feeds ApplyFacing.
// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

typedef unsigned int u32;

// ---------------------------------------------------------------- smart pointer
struct RefCounted {
    virtual void AddRef();                    // vtable +0x00
    virtual void Release();                   // vtable +0x04
};

struct SmartPtr {
    RefCounted* mPtr;                         // +0x00

    SmartPtr() : mPtr(0) {}
    SmartPtr(const SmartPtr& o) : mPtr(o.mPtr) { if (mPtr) mPtr->AddRef(); }
    SmartPtr& operator=(const SmartPtr& o) { return operator=(o.mPtr); }
    SmartPtr& operator=(RefCounted* p)
    {
        RefCounted* old = mPtr;
        if (p != old) {
            if (p) p->AddRef();
            mPtr = p;
            if (old) old->Release();
        }
        return *this;
    }
    ~SmartPtr() { if (mPtr) mPtr->Release(); }
};

struct Vector3 {
    float x, y, z;

    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
};

// ------------------------------------------------------------------ bone state
struct cOrientation {
    u32 mFlags;                               // +0x000
    char mPad04[0x1c];
    RefCounted* mTarget;                      // +0x020 (raw pointer, refcounted separately)
    char mPad24[0xcc];
    float mAngle;                             // +0x0f0
    Vector3 mAxis;                            // +0x0f4

    cOrientation& operator=(const cOrientation& o);   // 0x00af1910
    ~cOrientation();                                  // 0x00c2e4e0
};

struct BoneSet {
    cOrientation mOrients[8];                 // +0x000 (0x100 bytes each)
    SmartPtr mPtrs[8];                        // +0x800
};

struct NodeCore {
    u32 mField0;                              // +0x000
    cOrientation mOrients[8];                 // +0x004
    SmartPtr mPtrs[8];                        // +0x804

    NodeCore* CopyConstruct(const NodeCore& src);   // 0x00cb02a0
};

struct Node : NodeCore {
    Node* mNext;                              // +0x824
};

// --------------------------------------------------------------- vector helpers
struct Quaternion { float x, y, z, w; };

// ----------------------------------------------------------------------- externs
extern "C" void __stdcall CopyCtorIterator(void* dst, const void* src, unsigned int size, int count, void* ctor);
extern "C" void OrientationCopyCtor();        // 0x00c29ab0
extern "C" void SmartPtrCopyCtor();           // 0x00ac8980

// -------------------------------------------------------------------- classes
struct cPlanetModel {
    void BuildSurfaceOrientation(Quaternion* out, const Vector3& pos, const Vector3& facing);  // 0x00b7f250
};
extern "C" cPlanetModel* PlanetModel();       // 0x00b3d350
extern Vector3 RotateByQuat(const Vector3& v, const Quaternion& q);                              // 0x0059aed0
extern Vector3 RotateTowardsRate(const Vector3& from, const Vector3& to, float rate, float dt);  // 0x00cadf50
extern Vector3 kBoneAxis;                     // 0x0169a3fc

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct cLocomotiveObject {
    PV8 PV2 PV
    virtual const Vector3* GetPosition();                 // +0x2c
    virtual const Quaternion* GetOrientation();           // +0x30
    PV2
    virtual void SetOrientation(const Quaternion& q);     // +0x3c
    PV4 PV2 PV
    virtual Vector3 GetFacing();                          // +0x5c
};

struct cCreatureFlyer {
    u32 pad00[0x34 / 4];
    cLocomotiveObject mLocomotion;                        // +0x34
    u32 pad38[(0xF0 - 0x38) / 4];
    int mField_F0;                                        // +0x0f0
    u32 padF4[(0x21C - 0xF4) / 4];
    float mTurnRate;                                      // +0x21c

    float GetSpeed();                                     // 0x00c9f380
};

struct cFlyingLocomotion {
    void* vtable;
    u32 pad04[3];
    float mBank;                                          // +0x10

    void ApplyFacing(cCreatureFlyer* pFlyer, const Vector3& dir, float dt);   // 0x00caf650
    void UpdateSteering(cCreatureFlyer* flyer, const Vector3* target, struct SteeringState* state);  // 0x00cafe90
};

struct SteeringState {
    Vector3 mDir;                             // +0x000
    u32 mPad0C;                               // +0x00c
    float mTime;                              // +0x010
};

// @ 0x00cb0130
void __stdcall ReleaseBuckets(Node** buckets, unsigned int count)
{
    for (unsigned int i = 0; i < count; ++i) {
        Node* p = buckets[i];
        while (p) {
            Node* cur = p;
            p = p->mNext;
            delete cur;
        }
        buckets[i] = 0;
    }
}

// @ 0x00cb01e0
void CopyBoneSet(const cOrientation* src, BoneSet* dst)
{
    for (int i = 0; i < 8; ++i) {
        dst->mOrients[i] = src[i];
        dst->mOrients[i].mAngle = src[i].mAngle;
        dst->mOrients[i].mAxis = src[i].mAxis;
        if (src[i].mFlags)
            dst->mPtrs[i] = src[i].mTarget;
        else
            dst->mPtrs[i] = 0;
    }
}

// @ 0x00cb02a0
NodeCore* NodeCore::CopyConstruct(const NodeCore& src)
{
    mField0 = src.mField0;
    const cOrientation* s = src.mOrients;
    cOrientation* d = mOrients;
    CopyCtorIterator(d, s, 0x100, 8, (void*)&OrientationCopyCtor);
    CopyCtorIterator(d + 8, s + 8, 4, 8, (void*)&SmartPtrCopyCtor);
    return this;
}

// @ 0x00cafe90
void cFlyingLocomotion::UpdateSteering(cCreatureFlyer* flyer, const Vector3* target, SteeringState* state)
{
    cLocomotiveObject* loco = &flyer->mLocomotion;
    Vector3 facing = loco->GetFacing();
    Quaternion q;
    PlanetModel()->BuildSurfaceOrientation(&q, *loco->GetPosition(), facing);
    Vector3 up;
    up = RotateByQuat(kBoneAxis, q);
    up = RotateTowardsRate(facing, up, flyer->mTurnRate, state->mTime);
    ApplyFacing(flyer, up, state->mTime);

    const Vector3* now = loco->GetPosition();
    Vector3 delta(target->x - now->x, target->y - now->y, target->z - now->z);
    float len = sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
    if (len < 1.0f) {
        state->mDir *= 0.25f;
    } else {
        state->mDir += (delta - state->mDir) * 0.5f;
        float speed = flyer->GetSpeed();
        float d2 = state->mDir.x * state->mDir.x + state->mDir.y * state->mDir.y + state->mDir.z * state->mDir.z;
        float s = sqrtf(d2);
        if (s > speed) {
            float inv = 1.0f / sqrtf(s + 1e-8f);
            state->mDir = state->mDir * inv * speed;
        }
    }
}
