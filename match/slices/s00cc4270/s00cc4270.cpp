// Slice s00cc4270: SP::cDefaultBeamProjectileView::HandleSimulationUpdate (PDB candidate name).
//
// After the base view update: in civilization mode (game mode 0x1654c04 whose strategy reports a flag) the beam
// effects are hidden; the hidden state is cached in byte +0x39 and pushed to the five beam effects when it changes.
// Then, when the owner casts to a cDefaultBeamProjectile with a non-empty point list:
//   - the first 128 beam points are flattened into a fixed_vector<float, 384> and handed to the beam effect
//     (0x246350a) as float param 0xd, the effect is placed at the first point facing the last point (up = the
//     first point's direction), with vector param 9 = the last point and float param 10 = 1.0;
//   - effect 0x9138b729 is placed at the first point facing the second point;
//   - an end transform (at the last point, oriented by the beam's quaternion or facing the last segment) drives
//     effects 0x246350b / 0x246350c (started/stopped by the beam's +0x16c / +0x16d flags) and, oriented around
//     the last point, 0x47f791a (hitting the player) and 0x246350d (+0x1e0 set and not hitting the player);
//   - the flags are cached in the view's bytes +0x38/+0x3a..+0x3d.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the original has no EH frame around the fixed_vector).
#include "types.h"

#pragma warning(disable: 4100)

inline void* operator new(unsigned int, void* p) throw() { return p; }
inline void operator delete(void*, void*) throw() {}

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
void __cdecl operator delete[](void* p);   // 0x00f47380

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 Normalized() const
    {
        float inv = 1.0f / (float)sqrt(x * x + y * y + z * z);
        return Vector3(inv * x, inv * y, inv * z);
    }
    Vector3 SafeNormalized() const
    {
        float inv = 1.0f / (float)sqrt(x * x + y * y + z * z + 1e-08f);
        return Vector3(inv * x, inv * y, inv * z);
    }
    static const Vector3 ZERO;     // 0x0169b048
};
struct Quaternion { float x, y, z, w; };
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& o);     // 0x0041cb40 (rw::math::fpu::Matrix33Template copy ctor, out of line)
    static const Matrix3 IDENTITY; // 0x0169b024
};

Matrix3& Matrix3FromQuaternion(Matrix3& out, const Quaternion& q);                         // 0x0059c190
Matrix3& Matrix3FromFacingAndUp(Matrix3& out, const Vector3& facing, const Vector3& up);   // 0x0069b440

struct Transform {
    int16_t mnFlags;
    int16_t mnTransformCount;
    Vector3 mOffset;
    float mfScale;
    Matrix3 mRotation;
    __forceinline Transform() : mnFlags(0), mnTransformCount(0), mOffset(Vector3::ZERO), mfScale(1.0f),
                                mRotation(Matrix3::IDENTITY) {}
    // offset-only transform with an identity rotation assigned in the body
    __forceinline explicit Transform(const Vector3& offset) : mnFlags(4), mnTransformCount(1), mOffset(offset), mfScale(1.0f)
    {
        mRotation = Matrix3::IDENTITY;
    }
    Transform& SetOffset(const Vector3& v) { mOffset = v; mnFlags |= 4; mnTransformCount++; return *this; }
    Transform& SetRotation(const Matrix3& r) { mRotation = r; mnFlags |= 2; mnTransformCount++; return *this; }
};

namespace Swarm {
enum { kFloatParamBeamPoints = 0xd, kVectorParamBeamEnd = 9, kFloatParamBeamScale = 10 };
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
    virtual bool SetVectorParams(int param, const Vector3* data, int count) = 0;   // +0x40
    virtual bool SetFloatParams(int param, const float* data, int count) = 0;      // +0x44
};
}

// ---- eastl (minimal) --------------------------------------------------------------------------------------------
namespace eastl {
template <typename T> inline const T& min(const T& a, const T& b) { return (b < a) ? b : a; }

template <typename T>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](unsigned n) const { return mpBegin[n]; }
    T& front() const { return *mpBegin; }
    T& back() const { return *(mpEnd - 1); }
};

// fixed_vector<float, 384, true>: three pointers, the overflow allocator, the pool pointer, then the buffer.
template <typename T, int nodeCount>
struct fixed_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mOverflowAllocator;
    T* mpPoolBegin;
    uint32_t mPad;
    T mBuffer[nodeCount];

    fixed_vector()
    {
        mpPoolBegin = mBuffer;
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + nodeCount;
    }
    ~fixed_vector()
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

// ---- game classes -----------------------------------------------------------------------------------------------
namespace SP {
struct cGameMode;
extern cGameMode kCivGameMode;   // 0x01654c04
cGameMode* GetCurrentGameMode(); // 0x00b5b800

struct cCivModeTribe { bool f1540(); };                    // 0x00cf1540
struct cCivModeStrategy {
    static cCivModeStrategy* Get();                        // 0x00cf74c0
    cCivModeTribe* f74f0();                                // 0x00cf74f0
};

struct cDefaultBeamProjectile {
    uint32_t pad0[0x16c / 4];
    bool mb16c;                                            // +0x16c
    bool mb16d;                                            // +0x16d
    bool mbUseOrientation;                                 // +0x16e
    uint8_t pad16f[0x1b0 - 0x16f];
    Quaternion mOrientation;                               // +0x1b0
    uint32_t pad1c0[(0x1e0 - 0x1c0) / 4];
    void* mp1e0;                                           // +0x1e0
    eastl::vector<Vector3> mPoints;                        // +0x1e4

    const eastl::vector<Vector3>& GetPoints();             // 0x00cb3cf0
    bool UseOrientation();                                 // 0x00cb3d10
    bool Has1e0();                                         // 0x00cb5ba0
    bool IsHittingPlayer();                                // 0x00cb5b70
};

struct cSpatialObject {
    // vtable slot 0x2e (+0xb8): Cast
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v0a(); virtual void v0b(); virtual void v0c(); virtual void v0d(); virtual void v0e();
    virtual void v0f(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v1a(); virtual void v1b(); virtual void v1c(); virtual void v1d();
    virtual void v1e(); virtual void v1f(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b(); virtual void v2c();
    virtual void v2d();
    virtual void* Cast(uint32_t typeID);

    // effect list at +0xc0 (0x3c-byte entries: id at +0, running flag at +8, effect at +0x38)
    Swarm::IVisualEffect* GetEffect(uint32_t id);          // 0x00c888e0
    bool HasEffect(uint32_t id);                           // 0x00c88910
    bool IsEffectRunning(uint32_t id);                     // 0x00c88940
    void StartEffect(uint32_t id, int hard);               // 0x00c88980
    void StopEffect(uint32_t id, int hard);                // 0x00c889c0
};

struct cSpatialObjectView {
    uint32_t pad0[3];
    cSpatialObject* mpObject;                              // +0x0c
    uint32_t pad10[(0x34 - 0x10) / 4];
    int mnTime;                                            // +0x34

    void HandleSimulationUpdate(int unk, int deltaTime);   // 0x00e92ca0
};

struct cDefaultBeamProjectileView : cSpatialObjectView {
    bool mbAnyActive;                                      // +0x38
    bool mbHidden;                                         // +0x39
    bool mb16c;                                            // +0x3a
    bool mb16d;                                            // +0x3b
    bool mbHittingPlayer;                                  // +0x3c
    bool mbHas1e0;                                         // +0x3d

    void HandleSimulationUpdate(int unk, int deltaTime);
};

enum {
    kBeamEffect = 0x246350a,
    kBeamStartEffect = 0x9138b729,
    kBeamEndEffectB = 0x246350b,
    kBeamEndEffectC = 0x246350c,
    kBeamEndEffectD = 0x246350d,
    kBeamHitPlayerEffect = 0x47f791a,
    kTypeDefaultBeamProjectile = 0x24630ce,
};

static __forceinline void UpdateEffectRunning(cSpatialObject* obj, uint32_t id, bool want, bool was)
{
    if (want) {
        if (!was)
            obj->StartEffect(id, 0);
    } else if (was) {
        obj->StopEffect(id, 0);
    }
}

// @ 0x00cc4270
void cDefaultBeamProjectileView::HandleSimulationUpdate(int unk, int deltaTime)
{
    cSpatialObjectView::HandleSimulationUpdate(unk, deltaTime);

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
    cDefaultBeamProjectile* beam = (cDefaultBeamProjectile*)mpObject->Cast(kTypeDefaultBeamProjectile);
    if (!beam || beam->GetPoints().empty())
        return;

    const eastl::vector<Vector3>& points = beam->GetPoints();
    int n = (int)points.size();
    n = eastl::min(n, 0x80);
    eastl::fixed_vector<float, 384> vertices;
    for (int i = 0; i < n; i++) {
        vertices.push_back(points[i].x);
        vertices.push_back(points[i].y);
        vertices.push_back(points[i].z);
    }
    Vector3 start = points.front();
    Vector3 end = points.back();

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
    Vector3 dir;
    if (points.size() > 1)
        dir = points.back() - points[points.size() - 2];
    else
        dir = start - end;
    Vector3 endFacing = dir.SafeNormalized();
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
}
