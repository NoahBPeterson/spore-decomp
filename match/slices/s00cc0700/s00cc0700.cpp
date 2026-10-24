// Slice s00cc0700: SP::cDefaultBeamProjectile::Update (0x00cc0b40).
// /O2 /MD /Gy /TP /arch:SSE /fp:fast.
//
// Layout follows the Spore ModAPI cDefaultBeamProjectile (retail): the method runs on the
// secondary base at +0x108 (cBehaviorList side), so every member below is at
// (ModAPI offset - 0x108) and the cSpatialObject subobject is at this-0xd4.
#include "types.h"
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

// rw::math::fpu::Vector3Template<float,0> (plain value type)
struct cSPVector3;
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3 operator-(const Vector3& o) const { return Vector3(x - o.x, y - o.y, z - o.z); }
    Vector3 operator+(const Vector3& o) const { return Vector3(x + o.x, y + o.y, z + o.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    float SquaredLength() const { return x * x + y * y + z * z; }
    float Length() const { return (float)sqrt(SquaredLength()); }
    inline cSPVector3 Normalized() const;
};

// cSPVector3 : Vector3Template (Spore's member/argument type)
struct cSPVector3 : Vector3 {
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) { x = ax; y = ay; z = az; }
    cSPVector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
    cSPVector3(const cSPVector3& o) { x = o.x; y = o.y; z = o.z; }
    cSPVector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

inline cSPVector3 Vector3::Normalized() const
{
    float len = Length();
    float inv = 1.0f / len;
    return cSPVector3(x * inv, y * inv, z * inv);
}

struct Quaternion { float x, y, z, w; };

extern char g_013f94d4;   // type-id object passed to the Cast virtuals

// --- engine interfaces (only the vtable slots this function uses) ---
struct IObj {
    virtual void v00();
    virtual void Release();                         // 0x04
    virtual void v08();
    virtual IObj* CastC(void* id);                  // 0x0c
    virtual int GetPoliticalID();                   // 0x10
    virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual cSPVector3 GetAimPoint(int part);          // 0x28
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual bool IsDestroyed();                     // 0x3c
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4();
    virtual IObj* Cast(void* id);                   // 0xb8
};

template <class T> inline IObj* object_cast(T* p) { return p ? p->Cast(&g_013f94d4) : 0; }

struct cSpatialView {   // cSpatialObject subobject
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const cSPVector3& GetPosition();           // 0x2c
    virtual void v30(); virtual void v34();
    virtual void SetPosition(const Vector3& p);     // 0x38
};

struct cCombatantView {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual cSPVector3 GetPosition();               // 0x30
};

struct cSpaceToolData;
struct IToolStrategy {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void OnHit(cSpaceToolData* tool, Vector3* pos, int hitType, int arg);  // 0x30
};

struct cSpaceToolData {
    uint32_t pad0[0x114 / 4];
    IObj* mpOwner;        // 0x114
    IObj* mpTarget;       // 0x118 (intrusive_ptr<cSpatialObject>)
    int   mTargetPart;    // 0x11c
    bool  HasTargetAim();          // 0x0104cd30
    bool  IsHitScan();             // 0x0104cd60
    bool  DamageFlag();            // 0x0104cd70
    bool  IsReady();               // 0x0104bd50
    IToolStrategy* GetStrategy();  // 0x0104f930
};

struct cUFOView { uint32_t pad[0x508 / 4]; };
struct cCombatantData { bool IsStealthed(); };  // 0x00bfc480 (this = UFO+0x508)
struct cSPGameDataUFO {
    uint32_t pad[0x508 / 4];
    cCombatantData mCombatant;   // 0x508
    uint32_t pad2[(0x714 - 0x50c) / 4];
    int field_714;               // 0x714
};

// EA::AutoRefCount<T>
struct AutoRefCount {
    IObj* mpObject;
    AutoRefCount& operator=(IObj* p);   // 0x00b5f950
    void reset() {
        if (mpObject) { IObj* p = mpObject; mpObject = 0; p->Release(); }
    }
};

struct cSPTimer { uint32_t data[8]; uint64_t GetElapsedTime(); };   // 0x00bc3190

struct VectorV3 { cSPVector3* mpBegin; cSPVector3* mpEnd; cSPVector3* mpCapacity;
    cSPVector3& back() { return *(mpEnd - 1); } };

struct cCollisionMgr {
    bool LineHits(IObj* target, const Vector3& from, const Vector3& to, Vector3* hit);  // 0x00b35bf0
};
struct cPlanetModel {
    cSPVector3 GetNormal(const cSPVector3& pos);   // 0x00b7e3b0
};

struct cDefaultBeamProjectile;   // full object (this - 0x108)
struct cDefaultBeamProjectileFull { void ClearTargetedCombatant(); };  // 0x00cb5bb0

// --- callees ---
cCollisionMgr* CollisionManager();                                     // 0x00b3d240
cPlanetModel* PlanetModel();                                           // 0x00b3d350
IObj* CombatantCast(IObj** pp);                                        // 0x00ad2670
IObj* GameDataCast(AutoRefCount* pp);                                         // 0x00ad7360
cSPGameDataUFO* UFOCast(IObj** pp);                                    // 0x00c9f040
int  PathPrefsForTool(cSpaceToolData* tool);                           // 0x00cb36e0
int  CombatLineTest(const Vector3* from, const Vector3* dir, float len, AutoRefCount* hitObj,
                    Vector3* hit, cCombatantView* source, int flags);  // 0x00cb69e0
int  TerrainLineTest(const Vector3* from, const Vector3* dir, float len, Vector3* hit);  // 0x00cb6a50
void FindCombatantAt(Vector3* pos, float radius, AutoRefCount* out, cCombatantView* source);  // 0x00cb6500
void BuildStraightPath(cSPVector3 from, cSPVector3 to, VectorV3* path);      // 0x00cbcc40
void FindProjectilePath(IObj* owner, IObj* target, VectorV3* path, cSPVector3 to, int prefs, float spread);  // 0x00cbf120
// 0x00cba560: the original passes `pos` in EAX (same-TU static register convention).
void DoAreaDamage(Vector3* pos, float radius, float damage, float damage2, int one,
                  int politicalID, IObj* owner, IObj* target, bool flag);
cSPVector3 OrthogonalVector(const Vector3& v);                            // 0x006985b0
Quaternion QuaternionFromFacingAndUp(const Vector3& facing, const Vector3& up);  // 0x0069b600

struct cBeamUpdate {   // cDefaultBeamProjectile seen from its +0x108 base
    void* vtbl;
    uint32_t pad04[(0x2c - 0x04) / 4];
    cSpaceToolData* mpTool;            // 0x2c (0x134)
    cCombatantView* mpSource;          // 0x30 (0x138)
    cSPVector3 mTargetPosition;           // 0x34 (0x13c)
    cSPVector3 mHitPosition;              // 0x40 (0x148)
    bool  field_154;                   // 0x4c
    bool  mbStopBeam;                  // 0x4d
    uint16_t pad4e;
    float mMaxBeamLength;              // 0x50
    float field_15C;                   // 0x54
    cSPVector3 mBeamDirection;            // 0x58
    bool mbHittingGround;              // 0x64
    bool mbHittingWater;               // 0x65
    bool mbOrientsToTerrain;           // 0x66
    bool mbPassesThroughToTerrain;     // 0x67
    float mDamageRadius;               // 0x68
    float mBeamTurnRate;               // 0x6c
    uint64_t mMsPerDamagePoint;        // 0x70
    uint64_t mAccumulatedTime;         // 0x78
    uint64_t mLastUpdate;              // 0x80
    uint64_t mNextAimTime;             // 0x88
    Vector3 mTargetAimOffset;          // 0x90
    Vector3 mCurrentOffset;            // 0x9c
    Quaternion mGroundHitOrientation;  // 0xa8
    cSPTimer mLifeTimer;               // 0xb8
    AutoRefCount mpTargetedCombatant;  // 0xd8 (0x1e0)
    VectorV3 mPath;                    // 0xdc (0x1e4)

    cSpatialView* Spatial() { return (cSpatialView*)((char*)this - 0xd4); }
    cDefaultBeamProjectileFull* Full() { return (cDefaultBeamProjectileFull*)((char*)this - 0x108); }

    bool Update();
};

// @ 0x00cc0b40
bool cBeamUpdate::Update()
{
    if (mbStopBeam)
        return false;

    if (mpSource)
        Spatial()->SetPosition(mpSource->GetPosition());

    mbHittingGround = false;
    mbHittingWater = false;

    cSPVector3 start(Spatial()->GetPosition());
    cSPVector3 end(mTargetPosition);
    uint64_t now = mLifeTimer.GetElapsedTime();
    int hitType;
    float len;

    if (mpTool->mpTarget && mpTool->HasTargetAim()) {
        cSPVector3 p = object_cast(mpTool->mpTarget)->GetAimPoint(mpTool->mTargetPart);
        Vector3 aim = p - mTargetPosition;
        mBeamDirection = p - start;
        end = aim;
        len = mBeamDirection.Length();
        if (len == 0.0f)
            return false;
        mBeamDirection = mBeamDirection * (1.0f / len);

        if (mpTool->IsHitScan()) {
            if (mMaxBeamLength >= len) {
                hitType = 0;
                mpTargetedCombatant = CombatantCast(&mpTool->mpTarget);
                cSPVector3 farPoint = start + mBeamDirection * mMaxBeamLength;
                if (!CollisionManager()->LineHits(mpTool->mpTarget, start, farPoint, &mHitPosition))
                    mHitPosition = start + mBeamDirection * len;
            } else {
                hitType = 3;
                mHitPosition = start + mBeamDirection * mMaxBeamLength;
            }
        } else {
            hitType = CombatLineTest(&start, &mBeamDirection, mMaxBeamLength, &mpTargetedCombatant,
                                     &mHitPosition, mpSource, 4);
            if (hitType == 1) {
                Full()->ClearTargetedCombatant();
                BuildStraightPath(start, mHitPosition, &mPath);
                goto hit_done;
            }
        }

        {
            cSPGameDataUFO* ufo = UFOCast(&mpTool->mpTarget);
            if (ufo && ufo->field_714 == 0 && ufo->mCombatant.IsStealthed())
                end = aim - mBeamDirection * 10.0f;
        }

        if (hitType != 0 && mpTool->mpTarget && len < mMaxBeamLength) {
            mpTargetedCombatant = CombatantCast(&mpTool->mpTarget);
            hitType = 0;
            if ((start - mHitPosition).Length() > len)
                mHitPosition = start + mBeamDirection * len;
        }

        if (PathPrefsForTool(mpTool) == 2)
            BuildStraightPath(start, mHitPosition, &mPath);
        else
            FindProjectilePath(mpTool->mpOwner, GameDataCast(&mpTargetedCombatant), &mPath, end,
                               PathPrefsForTool(mpTool), 0.0f);
        mHitPosition = mPath.back();
    } else {
        mBeamDirection = (end - start).Normalized();
        mpTargetedCombatant.reset();
        float dist = (end - start).Length();
        if (dist > mMaxBeamLength)
            dist = mMaxBeamLength;

        if (mbPassesThroughToTerrain) {
            hitType = TerrainLineTest(&start, &mBeamDirection, dist, &mHitPosition);
            FindCombatantAt(&mHitPosition, mDamageRadius, &mpTargetedCombatant, mpSource);
            if (mpTargetedCombatant.mpObject)
                hitType = 0;
            else if (hitType == 3)
                hitType = TerrainLineTest(&start, &mBeamDirection, dist + 1.0f, &mHitPosition);
        } else {
            mHitPosition = end;
            FindCombatantAt(&mHitPosition, mDamageRadius, &mpTargetedCombatant, mpSource);
            if (mpTargetedCombatant.mpObject)
                hitType = 0;
            else
                hitType = TerrainLineTest(&start, &mBeamDirection, dist + 1.0f, &mHitPosition);
        }
        BuildStraightPath(start, mHitPosition, &mPath);
    }

hit_done:
    switch (hitType) {
    case 1: {
        mbHittingGround = true;
        end = PlanetModel()->GetNormal(mHitPosition);
        Vector3 ortho = OrthogonalVector(end);
        mGroundHitOrientation = QuaternionFromFacingAndUp(ortho, end);
        break;
    }
    case 2:
        mbHittingWater = true;
        mGroundHitOrientation = QuaternionFromFacingAndUp(OrthogonalVector(mHitPosition), mHitPosition);
        break;
    }

    if (mbHittingWater || mbHittingGround || mpTargetedCombatant.mpObject) {
        mAccumulatedTime += now - mLastUpdate;
        if (mMsPerDamagePoint != 0) {
            uint64_t acc = mAccumulatedTime;
            uint64_t points = acc / mMsPerDamagePoint;
            mAccumulatedTime = acc - points * mMsPerDamagePoint;
            if (points != 0) {
                float damage = (float)points;
                IObj* target = 0;
                IObj* owner = object_cast(mpTool->mpOwner);
                int politicalID;
                if (owner) {
                    politicalID = owner->GetPoliticalID();
                    if (owner->IsDestroyed())
                        politicalID = -1;
                } else {
                    politicalID = -1;
                }
                if (mpTargetedCombatant.mpObject)
                    target = mpTargetedCombatant.mpObject->CastC(&g_013f94d4);
                DoAreaDamage(&mHitPosition, mDamageRadius, damage, damage, 1, politicalID, owner, target,
                             mpTool->DamageFlag());
            }
        }

        if (field_154 && mpTool && mpTool->IsReady()) {
            IToolStrategy* s = mpTool->GetStrategy();
            if (s)
                s->OnHit(mpTool, &mHitPosition, hitType, 0);
            field_154 = false;
        }
    }

    mLastUpdate = now;
    return true;
}

// ---------------------------------------------------------------------------
// SP::FirePeaceBomb (0x00cc0700) and SP::cDefaultToolProjectile::SetupPathFollowing
// (0x00cc0870), the other two functions of the space-tool projectile TU. Both run on
// the full cDefaultToolProjectile object: this+0x34 is the cLocomotiveObject
// subobject, this+0x518 the owning cSpaceToolData.
// ---------------------------------------------------------------------------
#define K_DIST_EPS   (*(const float*)0x013EC4B8)   // 1e-8f, ray/sphere epsilon
#define K_FLOAT_ZERO (*(const float*)0x01485378)   // _HK_REAL_ZERO

// --- 0x00cc0700: Sim-side views ---
struct ISimSpatial {                                // sim's spatial data view
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const cSPVector3& GetPosition();        // 0x2c
};

struct ISimOwner {                                  // sim's empire data view
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual int GetEmpireID();                      // 0x4c
};

struct cSimGameData {
    uint32_t mPad000[0x714 / 4];                    // +0x000
    int mSpeciesKind;                               // +0x714
};

struct ISim {
    virtual void v00();                             // 0x00
    virtual void v04();                             // 0x04
    virtual ISimSpatial* GetSpatial();              // 0x08
    virtual ISimOwner* GetOwner();                  // 0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual cSimGameData* GetGameData(const void* typeId);      // 0x5c
    bool TimedExpired();                            // 0x00bfc600
    void TimedAdd(uint32_t ms);                     // 0x00bfc640
};

struct cSimPtrVector {
    ISim** mpBegin;                                 // +0x00
    ISim** mpEnd;                                   // +0x04
    ISim** mpCapacity;                              // +0x08
};

struct cGameDataList {                              // vector returned by GetGameDataVector
    uint32_t mField000;                             // +0x00
    cSimPtrVector mVec;                             // +0x04
};

struct cGameNounManager {
    cGameDataList* GetGameDataVector(void* collect, void* clear, void* collectSub,
                                     void* filter, const void* typeId);      // 0x00b21340
};
cGameNounManager* NounManager();                    // 0x00b3d300
int GetPlayerEmpireID();                            // 0x01021090

// Gives every non-player sim that sits in front of (pos, dir) a two-minute lifetime
// extension, so the peace bomb's wave front does not cull them mid-animation.
// @ 0x00CC0700
void FirePeaceBomb(cSPVector3 pos, cSPVector3 dir)
{
    cGameNounManager* pMgr = NounManager();
    cGameDataList* pList = pMgr->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00ae7230, (void*)0x00ae7250, (void*)0x00b1e520,
        (const void*)0x013f94d4);
    cSimPtrVector& vec = pList->mVec;
    int count = (int)(vec.mpEnd - vec.mpBegin);
    for (int i = 0; i < count; ++i) {
        ISim* sim = vec.mpBegin[i];
        if (sim->GetOwner()->GetEmpireID() == GetPlayerEmpireID())
            continue;
        if (sim->TimedExpired())
            continue;
        Vector3 delta = sim->GetSpatial()->GetPosition() - pos;
        double sq = (double)delta.z * delta.z + (double)delta.y * delta.y
                  + (double)delta.x * delta.x + K_DIST_EPS;
        float inv = (float)(1.0 / sqrt(sq));
        float dot = dir.z * (delta.z * inv) + dir.y * (delta.y * inv)
                  + dir.x * (delta.x * inv);
        if (dot > K_FLOAT_ZERO) {
            cSimGameData* pData = sim->GetGameData((const void*)0x00b033b403);
            if (pData == 0 || pData->mSpeciesKind != 3)
                sim->TimedAdd(120000);
        }
    }
}

// --- 0x00cc0870: projectile locomotion set-up ---
struct ILocomotion {                                // SmartPtr-managed behaviour (slots 0/4)
    virtual void AddRef();                          // 0x00
    virtual void Release();                         // 0x04
};

struct cLocomotiveView {                            // cLocomotiveObject at this+0x34
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const cSPVector3& GetPosition();        // 0x2c
    virtual void v30(); virtual void v34();
    virtual void SetPosition(const Vector3& pos);   // 0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void v5c(); virtual void v60(); virtual void v64(); virtual void v68();
    virtual void v6c(); virtual void v70(); virtual void v74(); virtual void v78();
    virtual void v7c(); virtual void v80(); virtual void v84(); virtual void v88();
    virtual void v8c(); virtual void v90(); virtual void v94(); virtual void v98();
    virtual void v9c(); virtual void va0(); virtual void va4(); virtual void va8();
    virtual void vac(); virtual void vb0(); virtual void vb4(); virtual void vb8();
    virtual void AddRef();                          // 0xbc
    virtual void Release();                         // 0xc0
    virtual void Advance(float deltaTime, int flags);   // 0xc4
    void SetLocomotion(ILocomotion* p);             // 0x00c421b0
};

struct cTargetObj {                                 // the projectile's target object
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual cSPVector3 GetAimPoint(int part);       // 0x28 (hidden return pointer)
    virtual const cSPVector3& GetPosition();        // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4();
    virtual cTargetObj* Cast(const void* typeId);   // 0xb8
    virtual void AddRef();                          // 0xbc
    virtual void Release();                         // 0xc0
};

struct cPathFollowingLocomotion : ILocomotion {
    cPathFollowingLocomotion(VectorV3& path, void* motion);     // 0x00cbaf00
};

inline void* operator new(size_t size, const char* tag, int a, int b, int c, int d);
void HeapDelete(void* p);                           // 0x00f47380: operator delete(void*)

struct cToolData {                                  // cSpaceToolData, members used here
    uint32_t mPad000[0x114 / 4];                    // +0x000
    IObj*    mpOwner;                               // +0x114
    IObj*    mpTarget;                              // +0x118
    int      mTargetPart;                           // +0x11c
    float GetSpread();                              // 0x0104bda0
    void* GetProjectileMotion();                    // 0x0104bd90
};

struct cPhaseTimer { uint32_t mData[8]; void Restart(); };      // 0x00bc3130

struct cDefaultToolProjectile {
    uint32_t mvftable;                              // +0x000
    uint32_t mPad004[0x30 / 4];                     // +0x004
    cLocomotiveView mLocomotive;                    // +0x034
    uint32_t mPad038[(0x224 - 0x038) / 4];          // +0x038
    int      mProjectileState;                      // +0x224
    uint32_t mPad228[(0x518 - 0x228) / 4];          // +0x228
    cToolData* mpTool;                              // +0x518
    ILocomotion* mpLocomotion;                      // +0x51c
    cSPVector3 mLastPosition;                       // +0x520
    uint32_t mPad52c[(0x544 - 0x52c) / 4];          // +0x52c
    int      mBombPhase;                            // +0x544
    cPhaseTimer mPhaseTimer;                        // +0x548
    uint32_t mPad568[(0x58c - 0x568) / 4];          // +0x568
    cSPVector3 mPathEndPoint;                       // +0x58c
    int      mTargetPart;                           // +0x598
    cSPVector3 mStartPosition;                      // +0x59c
    uint32_t mPad5a8[(0x5d8 - 0x5a8) / 4];          // +0x5a8
    cTargetObj* mpTarget;                           // +0x5d8
    uint32_t mPad5dc[(0x5f0 - 0x5dc) / 4];          // +0x5dc

    void SetupPathFollowing(float deltaTime, cTargetObj* pTarget, cSPVector3* pPos);   // 0x00cc0870
};

template <class T> struct ScopedRef {               // AddRef on entry, Release on exit
    T* mpObject;
    explicit ScopedRef(T* p) : mpObject(p) { if (p) p->AddRef(); }
    ~ScopedRef() { if (mpObject) mpObject->Release(); }
};

// Builds the flight path towards pTarget (or along pPos when there is no target), gives
// it to the locomotive and spawns the cPathFollowingLocomotion that walks it.
// @ 0x00CC0870
void cDefaultToolProjectile::SetupPathFollowing(float deltaTime, cTargetObj* pTarget,
                                               cSPVector3* pPos)
{
    mProjectileState = 5;
    cSPVector3 aim;

    if (pTarget) {
        mTargetPart = mpTool->mTargetPart;
        cTargetObj* pOldTarget = mpTarget;
        if (pTarget != pOldTarget) {
            pTarget->AddRef();
            mpTarget = pTarget;
            if (pOldTarget)
                pOldTarget->Release();
        }
        cTargetObj* pAim = pTarget->Cast(&g_013f94d4);
        const cSPVector3& targetPos = pTarget->GetPosition();
        aim = pAim->GetAimPoint(mTargetPart) - targetPos;
    } else {
        mStartPosition = *pPos;
        aim = *pPos;
    }

    VectorV3 path;
    path.mpBegin = 0;
    path.mpEnd = 0;
    path.mpCapacity = 0;

    IObj* pOwner;
    if (mpTool->mpOwner) {
        pOwner = mpTool->mpOwner;
    } else {
        ScopedRef<cLocomotiveView> held(&mLocomotive);
        pOwner = (IObj*)&mLocomotive;
    }

    FindProjectilePath(pOwner, (IObj*)pTarget, &path, aim, PathPrefsForTool((cSpaceToolData*)mpTool),
                       mpTool->GetSpread());

    mLocomotive.SetPosition(*path.mpBegin);

    cPathFollowingLocomotion* pLoco = new ("Simulator/cPathFollowingLocomotion", 0, 0, 0, 0)
        cPathFollowingLocomotion(path, mpTool->GetProjectileMotion());
    if (pLoco != mpLocomotion) {
        if (pLoco)
            pLoco->AddRef();
        ILocomotion* pOldLoco = mpLocomotion;
        mpLocomotion = pLoco;
        if (pOldLoco)
            pOldLoco->Release();
    }
    mLocomotive.SetLocomotion(mpLocomotion);

    mPathEndPoint = path.back();
    mLocomotive.Advance(deltaTime, 0);
    mBombPhase = 0;
    mPhaseTimer.Restart();
    mLastPosition = mLocomotive.GetPosition();

    if (path.mpBegin)
        HeapDelete(path.mpBegin);
}
