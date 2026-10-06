// slice s00577e10
// SP::cAppModeEditorBase::UpdateBabyCreatures  @ 0x00577e10 (5788 bytes, /arch:SSE module).
//
// Places up to three baby creatures on a ring around the creature being edited and drives
// their idle / walk / sit / social-call behaviour each frame.
//   1. Ring placement: for each baby, an angle i/n*2pi around kRingAxis (pushed off by 0.26 rad
//      from earlier angles), position = (kRingForward*radius) rotated + main creature position.
//      Positions further than 4.0 from the origin are searched for by stepping +/-0.26 rad
//      (at most 12 steps) and de-duplicated against earlier slots (min distance 0.5).
//   2. Assignment: every ring slot is given to the closest unassigned baby whose straight
//      path to it does not cross the main creature's bounding box.
//   3. Per-baby update: sit / social-call timers, look-at and facing, walking to the slot,
//      or random idle animations.
#include "types.h"

#include <math.h>
#include <float.h>

// ---------------------------------------------------------------------------------------
// math helpers
struct Vector3
{
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    float SquaredLength() const { return x * x + y * y + z * z; }
    float Length() const { return (float)sqrt(SquaredLength()); }
};

// 0x0041dd30: component-wise float inequality (cdecl, out of line).
bool operator!=(const Vector3& a, const Vector3& b);
// 0x00436ce0: v / |v| (cdecl, returns its out param).
Vector3* Vector3_Normalize(Vector3* out, const Vector3* v);
// 0x0069b760: signed angle from a to b around axis.
float Math_SignedAngle(const Vector3* a, const Vector3* b, const Vector3* axis);
// 0x006989d0: segment [p0,p1] against an axis-aligned box; true on intersection, *t = hit param.
bool SegmentIntersectsBox(const Vector3* p0, const Vector3* p1, const struct BoundingBox* box, float* t);
// 0x00572a10: uniform float in [lo, hi) from the shared math RNG.
float RandomFloatRange(float lo, float hi);

struct BoundingBox
{
    Vector3 lower;
    Vector3 upper;
    BoundingBox() : lower(FLT_MAX, FLT_MAX, FLT_MAX),
                    upper(-FLT_MAX, -FLT_MAX, -FLT_MAX) {}
};

// Row-major 3x3 rotation about an arbitrary unit axis (row vector convention: v * M).
struct Matrix3
{
    float m[3][3];
    void SetAxisAngle(const Vector3& axis, float angle)
    {
        float s = (float)sin(angle);
        float c = (float)cos(angle);
        float t = 1.0f - c;
        m[0][0] = t * axis.x * axis.x + c;
        m[0][1] = t * axis.x * axis.y + s * axis.z;
        m[0][2] = t * axis.x * axis.z - s * axis.y;
        m[1][0] = t * axis.y * axis.x - s * axis.z;
        m[1][1] = t * axis.y * axis.y + c;
        m[1][2] = t * axis.y * axis.z + s * axis.x;
        m[2][0] = t * axis.z * axis.x + s * axis.y;
        m[2][1] = t * axis.z * axis.y - s * axis.x;
        m[2][2] = t * axis.z * axis.z + c;
    }
};

inline Vector3 operator*(const Vector3& v, const Matrix3& r)
{
    return Vector3(v.x * r.m[0][0] + v.y * r.m[1][0] + v.z * r.m[2][0],
                   v.x * r.m[0][1] + v.y * r.m[1][1] + v.z * r.m[2][1],
                   v.x * r.m[0][2] + v.y * r.m[1][2] + v.z * r.m[2][2]);
}

extern Vector3 kRingAxis;      // 0x015e5024 (rotation axis of the ring)
extern float   kTwoPi;         // 0x015e50a0
extern Vector3 kRingForward;   // 0x015e50a4 (ring start direction; also the creatures' forward)

namespace EA { namespace Random {
class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t limit);   // 0x00a68fb0
};
} }
extern EA::Random::RandomLinearCongruential sMathRandom;   // 0x01601760

// ---------------------------------------------------------------------------------------
// game objects
struct cCreatureModel
{
    char  pad0[0x6c];
    float mScale;           // +0x6c
    BoundingBox mBoundingBox;   // +0x70
};

struct cCreatureObject
{
    char pad0[0x180];
    cCreatureModel* mpModel;    // +0x180
};

class cAnimatedCreature
{
public:
    virtual void v00();
    virtual void v01();
    virtual uint32_t CreateAnimation(uint32_t animID, int flags);          // +0x08
    virtual void SetAnimationLoop(uint32_t handle, int loop);              // +0x0c
    virtual void v04();
    virtual void v05();
    virtual void StartAnimation(uint32_t handle);                          // +0x18
    virtual void v07();
    virtual void SetAnimationActive(uint32_t handle, int active);          // +0x20
    virtual void SetAnimationDuration(uint32_t handle, float duration);    // +0x24
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void SetAnimationBlendTime(uint32_t handle, float time);       // +0x38
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void GetCurrentAnimation(uint32_t* animID, float* time, float* duration, int index); // +0x58
};

class cCreatureStructure
{
public:
    char pad0[8];
    cAnimatedCreature* mpAnimatedCreature;   // +0x08
    char pad0c[0x48 - 0x0c];
    float mOrientation;                      // +0x48
    void RefreshTargetPosition();            // 0x0059b390
    void SetUseTargetAngle(bool use);        // 0x0059b420
};

namespace SP {

class cSPEditorAnimatedCreatureManager
{
public:
    cCreatureObject*    GetCreature(uint32_t id);                                   // 0x0059ca70
    cCreatureStructure* GetCreatureStructure(uint32_t id);                          // 0x0059cac0
    void PlayAnimation(uint32_t id, uint32_t animID);                               // 0x0059cb10
    bool IsPlayingAnimation(uint32_t id);                                           // 0x0059cd20
    void SetCreatureTargetAngle(uint32_t id, float angle, int immediate);           // 0x0059cea0
    void SetCreatureLookAtTarget(uint32_t id, Vector3 target, int immediate);       // 0x0059cfb0
    bool GetCreaturePosition(uint32_t id, Vector3& pos);                            // 0x0059d110
};

class cSPPlayMode
{
public:
    bool  IsDancingAnim(uint32_t animID, bool includeIdle);                         // 0x00628600
    bool  IsWalkTypeAnim(uint32_t animID);                                          // 0x00628610
    bool  IsDancingBaby(uint32_t id);                                               // 0x00628750
    void  SetAllOtherBabiesToIdle(uint32_t id, uint32_t animID, float blend);       // 0x006292b0
    void  SetBabySocialCallState(uint32_t id, uint32_t animID, float blend);        // 0x006293d0
    void  SetBabyPath(uint32_t id, Vector3 target);                                 // 0x0062a230
    bool  HasActivePath(uint32_t id);                                               // 0x0062a360
    void  BabyStartSocialCallEffect(int index, uint32_t id);                        // 0x0062a990
    void  SetBabySitState(int index);                                               // 0x0062aa90
    float GetCreatureHalfExtent(cCreatureObject* creature, int isBaby);             // 0x0062ace0
};

template <class T>
struct vector
{
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
};

class cAppModeEditorBase
{
public:
    struct cAnimatedBaby
    {
        uint32_t mID;                 // +0x00
        float    mIdleTimer;          // +0x04
        float    mNextTime;           // +0x08
        Vector3  mPositionOffset;     // +0x0c
        bool     mIsWalking;          // +0x18
        bool     mJustSpawned;        // +0x19
        bool     mInButtonEvent;      // +0x1a
        char     mSittingMode;        // +0x1b
        char     mCallingMode;        // +0x1c
        float    mEventStartTime;     // +0x20
        float    mAnimChangeTime;     // +0x24
        float    mCallEffectStartTime;// +0x28
        uint32_t mSocialCallEffectID; // +0x2c
    };

    char pad0[0x7c];
    cSPPlayMode* mpPlayMode;                                    // +0x7c
    char pad80[0x360 - 0x80];
    cSPEditorAnimatedCreatureManager* mAnimCreatureManager;     // +0x360
    uint32_t mAnimatingCreatureID;                              // +0x364
    uint32_t mAnimatingThumbnailID;                             // +0x368
    vector<cAnimatedBaby> mAnimatedBabies;                      // +0x36c

    void UpdateBabyCreatures(uint32_t deltaTime);   // 0x577e10
};

}  // namespace SP

enum { kMaxRingBabies = 3 };

// @ 0x00577e10
void SP::cAppModeEditorBase::UpdateBabyCreatures(uint32_t deltaTime)
{
    float dt = (float)deltaTime * 0.001f;
    uint32_t numBabies = mAnimatedBabies.size();
    float radius = 1.15f;

    float   ringAngles[kMaxRingBabies];
    int     ringOwner[kMaxRingBabies];       // baby index -> ring slot (or -1)
    Vector3 ringPositions[kMaxRingBabies];

    if (numBabies != 0)
    {
        BoundingBox box;

        cCreatureObject* mainCreature = mAnimCreatureManager->GetCreature(mAnimatingCreatureID);
        float scale = mainCreature->mpModel->mScale;
        if (scale > radius)
        {
            radius = scale * 1.5f;
            if (radius > 3.75f)
                radius = 3.75f;
        }
        float mainExtent = mpPlayMode->GetCreatureHalfExtent(mainCreature, 0);
        float babyExtent = mpPlayMode->GetCreatureHalfExtent(
            mAnimCreatureManager->GetCreature(mAnimatedBabies[0].mID), 1);
        if (babyExtent + mainExtent > radius)
            radius = babyExtent + mainExtent;

        box = mainCreature->mpModel->mBoundingBox;

        Vector3 mainPos;
        mAnimCreatureManager->GetCreaturePosition(mAnimatingCreatureID, mainPos);
        box.lower.x = (mainPos.x + box.lower.x) - 0.075f;
        box.lower.y = (box.lower.y + mainPos.y) - 0.075f;
        box.lower.z = (box.lower.z + mainPos.z) - 0.075f;
        box.upper.x = (mainPos.x + box.upper.x) + 0.075f;
        box.upper.y = (box.upper.y + mainPos.y) + 0.075f;
        box.upper.z = (box.upper.z + mainPos.z) + 0.075f;

        if (numBabies != 0)
        {
            Vector3 offset = kRingForward * radius;
            Matrix3 rot;

            for (uint32_t k = 0; k < numBabies; ++k)
                ringOwner[k] = -1;

            for (uint32_t i = 0; i < numBabies; ++i)
            {
                float angle = ((float)i / (float)numBabies) * kTwoPi;
                for (uint32_t j = 0; j < i; ++j)
                {
                    if (fabs(ringAngles[j] - angle) < 0.26f)
                        angle += 0.26f;
                }

                rot.SetAxisAngle(kRingAxis, angle);
                ringPositions[i] = offset * rot + mainPos;

                if (ringPositions[i].Length() > 4.0f)
                {
                    // Too far out: search both directions for a slot within reach.
                    float up = angle + 0.26f;
                    float down = angle - 0.26f;
                    float found = 0.0f;
                    uint8_t tries = 0;
                    Vector3 p;

                    for (;;)
                    {
                        if (tries >= 12)
                            goto next_slot;     // give up: keep the far position, no angle

                        while (found == 0.0f && tries < 12)
                        {
                            rot.SetAxisAngle(kRingAxis, up);
                            p = offset * rot + mainPos;
                            found = up;
                            if (p.Length() > 4.0f)
                            {
                                rot.SetAxisAngle(kRingAxis, down);
                                p = offset * rot + mainPos;
                                found = down;
                                if (p.Length() > 4.0f)
                                {
                                    found = 0.0f;
                                    up += 0.26f;
                                    down -= 0.26f;
                                    ++tries;
                                    if (up > kTwoPi)
                                        up -= kTwoPi;
                                    if (down < 0.0f)
                                        down += kTwoPi;
                                }
                            }
                        }

                        bool retry = false;
                        for (uint32_t j = 0; j < i; ++j)
                        {
                            Vector3 d = ringPositions[j] - p;
                            if (d.Length() < 0.5f)
                            {
                                if (tries < 12)
                                {
                                    up += 0.26f;
                                    down -= 0.26f;
                                    found = 0.0f;
                                    retry = true;
                                    break;
                                }
                                p = (p + ringPositions[j]) * 0.5f - d;
                                found = kTwoPi;
                            }
                        }
                        if (retry)
                            continue;
                        if (found != 0.0f)
                            break;
                    }

                    ringPositions[i] = p;
                    ringAngles[i] = found;
                }
                else
                {
                    ringAngles[i] = angle;
                }
            next_slot:;
            }
        }

        // Give each ring slot to the closest free baby with a clear path to it.
        for (uint32_t i = 0; i < numBabies; ++i)
        {
            float bestDist = FLT_MAX;
            Vector3 slot = ringPositions[i];
            int best = -1;
            for (uint32_t j = 0; j < numBabies; ++j)
            {
                if (ringOwner[j] == -1)
                {
                    Vector3 babyPos;
                    mAnimCreatureManager->GetCreaturePosition(mAnimatedBabies[j].mID, babyPos);
                    float dist = (slot - babyPos).Length();
                    float t;
                    if (dist < bestDist && !SegmentIntersectsBox(&babyPos, &slot, &box, &t))
                    {
                        bestDist = dist;
                        best = (int)j;
                    }
                }
            }
            if (best != -1)
                ringOwner[best] = (int)i;
        }
    }

    int count = (int)mAnimatedBabies.size();
    for (int i = 0; i < count; ++i)
    {
        if (mAnimCreatureManager == 0 || mAnimatingCreatureID == 0 || mAnimatedBabies[i].mID == 0)
            continue;

        uint32_t animID;
        float animTime, animDuration;
        mAnimCreatureManager->GetCreatureStructure(mAnimatedBabies[i].mID)
            ->mpAnimatedCreature->GetCurrentAnimation(&animID, &animTime, &animDuration, 0);

        char sitting = mAnimatedBabies[i].mSittingMode;
        if (sitting == 2 || sitting == 3)
        {
            mAnimatedBabies[i].mAnimChangeTime -= (float)deltaTime * 0.001f;
            if (mAnimatedBabies[i].mAnimChangeTime > 0.0f)
            {
                mAnimatedBabies[i].mSittingMode = 3;
            }
            else
            {
                cAnimatedCreature* anim =
                    mAnimCreatureManager->GetCreatureStructure(mAnimatedBabies[i].mID)->mpAnimatedCreature;
                uint32_t handle = anim->CreateAnimation(0x4079851, 0);
                anim->SetAnimationLoop(handle, 1);
                anim->StartAnimation(handle);
                anim->SetAnimationActive(handle, 1);
                anim->SetAnimationDuration(handle, -1.0f);
                anim->SetAnimationBlendTime(handle, 0.667f);
                mAnimatedBabies[i].mAnimChangeTime = 0.0f;
                mAnimatedBabies[i].mSittingMode = 4;
            }
            continue;
        }
        if (sitting == 4)
            continue;

        char calling = mAnimatedBabies[i].mCallingMode;
        if (calling == 2)
        {
            mAnimatedBabies[i].mCallEffectStartTime -= (float)deltaTime * 0.001f;
            if (mAnimatedBabies[i].mCallEffectStartTime <= 0.0f)
            {
                mpPlayMode->BabyStartSocialCallEffect(i, mAnimatedBabies[i].mID);
                mAnimatedBabies[i].mCallingMode = 3;
            }
            continue;
        }
        if (calling == 3)
        {
            mAnimatedBabies[i].mAnimChangeTime -= (float)deltaTime * 0.001f;
            if (mAnimatedBabies[i].mAnimChangeTime <= 0.0f)
                mpPlayMode->SetBabySitState(i);
            continue;
        }

        if (mpPlayMode->IsDancingAnim(animID, true))
            continue;

        Vector3 mainPos;
        if (!mAnimCreatureManager->GetCreaturePosition(mAnimatingCreatureID, mainPos))
            continue;
        Vector3 babyPos;
        if (!mAnimCreatureManager->GetCreaturePosition(mAnimatedBabies[i].mID, babyPos))
            continue;

        cCreatureStructure* structure = mAnimCreatureManager->GetCreatureStructure(mAnimatedBabies[i].mID);

        if ((mAnimatedBabies[i].mSittingMode == 1 || mAnimatedBabies[i].mCallingMode == 1) &&
            mAnimatedBabies[i].mAnimChangeTime > 0.0f)
        {
            mAnimatedBabies[i].mAnimChangeTime -= (float)deltaTime * 0.001f;
            if (mAnimatedBabies[i].mAnimChangeTime <= 0.0f)
            {
                if (mAnimatedBabies[i].mSittingMode == 1)
                    mpPlayMode->SetAllOtherBabiesToIdle(mAnimatedBabies[i].mID, 0x4079846, 0.667f);
                else
                    mpPlayMode->SetBabySocialCallState(mAnimatedBabies[i].mID, 0x42dd0f4, 0.667f);
            }
        }

        float scale = mAnimCreatureManager->GetCreature(mAnimatingCreatureID)->mpModel->mScale;
        if (scale > radius)
        {
            radius = scale * 1.5f;
            if (radius > 3.75f)
                radius = 3.75f;
        }

        // Ring slot (or the baby's own spot) projected onto the ground plane.
        int slot = ringOwner[i];
        mainPos.z = 0.0f;
        babyPos.z = 0.0f;
        Vector3 target;
        if (slot != -1)
            target = ringPositions[slot];
        else
            target = babyPos;

        if (mpPlayMode != 0 && mpPlayMode->IsDancingBaby(mAnimatedBabies[i].mID))
        {
            float orientation =
                mAnimCreatureManager->GetCreatureStructure(mAnimatingCreatureID)->mOrientation;
            mAnimCreatureManager->SetCreatureTargetAngle(mAnimatedBabies[i].mID, orientation, 0);
            structure->RefreshTargetPosition();
            structure->SetUseTargetAngle(false);
        }
        else
        {
            mAnimCreatureManager->SetCreatureLookAtTarget(
                mAnimatedBabies[i].mID, Vector3(mainPos.x, mainPos.y, mainPos.z + 0.8f), 0);
            Vector3 back = -kRingForward;
            Vector3 toMain = mainPos - babyPos;
            float facing = Math_SignedAngle(&toMain, &back, &kRingAxis);
            mAnimCreatureManager->SetCreatureTargetAngle(mAnimatedBabies[i].mID, -facing, 0);
            structure->SetUseTargetAngle(true);
        }

        if (sqrt(target.x * target.x + target.y * target.y + target.z * target.z) > 4.0)
        {
            Vector3 n;
            Vector3* dir = Vector3_Normalize(&n, &target);
            target.x = dir->x * 4.0f;
            target.y = dir->y * 4.0f;
            target.z = dir->z * 4.0f;
        }

        // Planar offset to the target (the target's height is ignored).
        Vector3 toTarget(babyPos.x - target.x, babyPos.y - target.y, babyPos.z);
        if (toTarget.SquaredLength() > 0.02f &&
            (!mAnimCreatureManager->IsPlayingAnimation(mAnimatedBabies[i].mID) ||
             mpPlayMode->IsWalkTypeAnim(animID)))
        {
            if (!mpPlayMode->HasActivePath(mAnimatedBabies[i].mID))
            {
                if (target != babyPos && !mAnimatedBabies[i].mJustSpawned &&
                    !mAnimatedBabies[i].mInButtonEvent)
                {
                    mpPlayMode->SetBabyPath(mAnimatedBabies[i].mID, target);
                    mAnimatedBabies[i].mIsWalking = true;
                }
                uint32_t curAnim;
                float curTime, curDuration;
                mAnimCreatureManager->GetCreatureStructure(mAnimatedBabies[i].mID)
                    ->mpAnimatedCreature->GetCurrentAnimation(&curAnim, &curTime, &curDuration, 0);
            }
            continue;
        }

        // Idle: every 3.7-5.5 s pick a random idle animation.
        if (mAnimatedBabies[i].mIdleTimer > mAnimatedBabies[i].mNextTime)
        {
            mAnimatedBabies[i].mNextTime = RandomFloatRange(3.7f, 5.5f);
            mAnimatedBabies[i].mIdleTimer = 0.0f;

            uint32_t idleAnim;
            float idleTime, idleDuration;
            mAnimCreatureManager->GetCreatureStructure(mAnimatedBabies[i].mID)
                ->mpAnimatedCreature->GetCurrentAnimation(&idleAnim, &idleTime, &idleDuration, 0);
            if (mAnimCreatureManager->IsPlayingAnimation(mAnimatedBabies[i].mID))
                continue;
            if (mpPlayMode->IsDancingAnim(idleAnim, true))
                continue;

            uint32_t choice;
            if ((int)sMathRandom.RandomUint32Uniform(100) < 10)
                choice = 4;
            else
                choice = sMathRandom.RandomUint32Uniform(4);

            switch (choice)
            {
            case 0: mAnimCreatureManager->PlayAnimation(mAnimatedBabies[i].mID, 0x43736bf); break;
            case 1: mAnimCreatureManager->PlayAnimation(mAnimatedBabies[i].mID, 0x437369a); break;
            case 2: mAnimCreatureManager->PlayAnimation(mAnimatedBabies[i].mID, 0x43736a0); break;
            case 3: mAnimCreatureManager->PlayAnimation(mAnimatedBabies[i].mID, 0x43736ae); break;
            case 4: mAnimCreatureManager->PlayAnimation(mAnimatedBabies[i].mID, 0x43736b9); break;
            }
        }
        else
        {
            mAnimatedBabies[i].mIdleTimer += dt;
        }
    }
}
