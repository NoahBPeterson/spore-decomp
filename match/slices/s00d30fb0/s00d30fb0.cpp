// 0x00d30fb0 -- SP::cCreatureModeInputStrategy::SpawnMovementGoalEffect
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// Places (or re-places) the creature movement-goal cursor effect at the
// requested goal position.  This is the retail 500-byte body; the class
// members used here are mpMovementGoalEffect (+0xe0) and mAvatarGoal (+0xe4).
//
// The transform handed to the effect is a 0x38-byte XformMsg:
//   +0x00 u16 flags, +0x02 i16 count, +0x04 Vector3 pos,
//   +0x10 float 1.0f, +0x14 Matrix3 rotation.
//
// Flags: 2 = matrix valid, 4 = position valid; every change bumps count.

#include "types.h"

typedef unsigned int u32;
typedef unsigned short u16;
typedef short i16;

// ---- math -----------------------------------------------------------------
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};

struct Quat {
    float x, y, z, w;
};

struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& o);          // 0x0041cb40 (out-of-line copy ctor)
};

// Scratch results for the two orientation paths.  `up` is 0x0c bytes, so
// the union starts at +0x0c and the retail frame reuses that slot for the
// quaternion, the orthogonal vector and the projected position.
struct GoalTemps {
    Vec3 up;                            // +0x00
    union {
        float q[4];                     // +0x0c (Quat)
        float ortho[3];                 // +0x0c
        float projected[3];             // +0x0c
    };
};

extern Vec3    gZeroVector3_0169e214;   // 0x0169e214 (constant vector)
extern Matrix3 gIdentityMatrix3_0169e1f0; // 0x0169e1f0 (identity matrix)
extern float   g_147a5f4;               // 0x0147a5f4 (height threshold)

void Matrix3FromQuaternion(Matrix3* out, const Quat* q);          // 0x0059c190
void Matrix3FromFacingAndUp(Matrix3* out, const Vec3* facing,
                            const Vec3* up);                      // 0x0069b440
void OrthogonalVector(Vec3* out, const Vec3* in);                 // 0x006985b0

// ---- planet model ---------------------------------------------------------
struct cPlanetModel {
    float GetWaterDepth(const Vec3&, bool) const;       // 0x00b7e430
    Quat* BuildSurfaceOrientation(Quat* out, const Vec3&) const; // 0x00b7f190
    Vec3* ProjectToSurface(Vec3* out, const Vec3&) const; // 0x00b81630
    Vec3* GetUp(Vec3* out, const Vec3&) const;          // 0x00b7e3b0
};
cPlanetModel* PlanetModel();                            // 0x00b3d350

// ---- effects --------------------------------------------------------------
struct XformMsg {
    u16     flags;      // +0x00
    i16     count;      // +0x02
    Vec3    pos;        // +0x04
    float   f10;        // +0x10
    Matrix3 mat;        // +0x14

    XformMsg()
        : flags(0), count(0), pos(gZeroVector3_0169e214),
          f10(1.0f), mat(gIdentityMatrix3_0169e1f0) {}

    void SetPos(const Vec3& p)
    {
        pos = p;
        flags |= 4;
        ++count;
    }
};

struct cIVisualEffect {
    virtual int  AddRef();                                  // +0x00
    virtual int  Release();                                 // +0x04
    virtual void Start(int transition);                     // +0x08
    virtual void Stop(int transition);                      // +0x0c
    virtual bool IsRunning() const;                         // +0x10
    virtual void SetRigidTransform(const XformMsg&);        // +0x14
    virtual void SetSourceTransform(const XformMsg&);       // +0x18
};

struct cEffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void v24(); virtual void v28();
    virtual bool CreateVisualEffect(u32 id, int unused,
                                    cIVisualEffect** out);  // +0x2c
};
cEffectsManager* EffectsManager();                          // 0x0067ddd0

// intrusive ref-count handle (release clears the pointer first)
template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* old = mpObject;
            mpObject = p;
            if (old)
                old->Release();
        }
        return *this;
    }
    operator bool() const { return mpObject != 0; }
    T* operator->() const { return mpObject; }
    // Out-parameter accessor used by the effects-manager create calls: the
    // existing effect is stopped/released before its slot is handed out.
    T** AsPPTypeParam()
    {
        T* old = mpObject;
        if (old) {
            mpObject = 0;
            old->Release();
        }
        return &mpObject;
    }
};

// ---- strategy -------------------------------------------------------------
struct cCreatureModeInputStrategy {
    char pad0[0xe0];
    AutoRefCount<cIVisualEffect> mpMovementGoalEffect;  // +0xe0
    Vec3 mAvatarGoal;                                   // +0xe4

    void SpawnMovementGoalEffect(const Vec3* goal);
};

// @ 0x00d30fb0
void cCreatureModeInputStrategy::SpawnMovementGoalEffect(const Vec3* goal)
{
    mAvatarGoal = *goal;

    if (mpMovementGoalEffect) {
        mpMovementGoalEffect->Stop(1);
        mpMovementGoalEffect = 0;
    }

    if (EffectsManager()->CreateVisualEffect(0x384e54a4, 0,
                                             mpMovementGoalEffect.AsPPTypeParam())) {
        cPlanetModel* planet = PlanetModel();
        XformMsg xform;
        xform.SetPos(*goal);

        if (planet->GetWaterDepth(*goal, true) > g_147a5f4) {
            GoalTemps tmp;
            Matrix3 m;
            Matrix3FromQuaternion(&m, planet->BuildSurfaceOrientation((Quat*)tmp.q, *goal));
            xform.mat = m;
            xform.flags |= 2;
            ++xform.count;
            xform.SetPos(*planet->ProjectToSurface((Vec3*)tmp.projected, *goal));
        } else {
            GoalTemps tmp;
            planet->GetUp(&tmp.up, *goal);
            OrthogonalVector((Vec3*)tmp.ortho, &tmp.up);
            Matrix3 m;
            Matrix3FromFacingAndUp(&m, (Vec3*)tmp.ortho, &tmp.up);
            xform.mat = m;
            xform.flags |= 2;
            ++xform.count;
        }

        mpMovementGoalEffect->SetSourceTransform(xform);
        mpMovementGoalEffect->Start(0);
    }
}
