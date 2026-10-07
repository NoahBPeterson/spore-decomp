// Slice s00d56c30: SP::cBehaviorSpaceTurret::Action (0x00d56c30).
// /O2 /MD /Gy /TP /arch:SSE /fp:fast.
//
// Retail layout (from the disassembly; the 2008 PDB layout is shifted):
//   +0x0c mTargetList (slot_deque), +0x2c mAgentList (slot_deque), +0x74 mStateMap,
//   +0x90 mLifeTimer, +0xb0 mNextFiringTime, +0xbc mCityCenter, +0xc8 mAaShotsPerTurret,
//   +0xd0 mSdrBeamLifetime, +0xd8 mbWasHostile.
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3 operator-(const Vector3& o) const { return Vector3(x - o.x, y - o.y, z - o.z); }
};
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

struct Matrix3 { float m[9]; };

// Transform (0x38 bytes): flags, change count, offset, scale, rotation
struct Transform {
    uint16_t mFlags;
    uint16_t mChangeCount;
    Vector3  mOffset;
    float    mScale;
    Matrix3  mRotation;
    Transform();                                  // 0x00434040
    void SetOffset(const Vector3& v);             // 0x00571d40
    void SetRotation(const Matrix3& m) { mRotation = m; mFlags |= 2; mChangeCount++; }
};

// ---- generic engine interface (only the used slots are named) ----
struct IObj {
    virtual void v00();
    virtual IObj* Cast4(uint32_t id);             // 0x04
    virtual IObj* Cast8(uint32_t id);             // 0x08
    virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();         // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual void Activate();                      // 0x4c
};

struct IVisualEffect {
    virtual void v00();
    virtual void Release();                       // 0x04
    virtual void Start(int flags);                // 0x08
    virtual void Stop(int flags);                 // 0x0c
    virtual bool IsRunning();                     // 0x10
    virtual void v14();
    virtual void SetTransform(const Transform& t);  // 0x18
};
struct EffectRef {   // EA::AutoRefCount<EA::Swarm::cIVisualEffect>
    IVisualEffect* mpObject;
    IVisualEffect** AsPPTypeParam();              // 0x00a16f40
    __forceinline void reset() {
        if (mpObject) { IVisualEffect* p = mpObject; mpObject = 0; p->Release(); }
    }
};

struct IEffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool CreateVisualEffect(uint32_t id, int group, IVisualEffect** out);  // 0x2c
};

struct cTool {
    int   GetRefireMs();         // 0x0104bde0
    float GetMinRange();         // 0x0104be20
    float GetMaxRange();         // 0x0104be30
    float GetDamage();           // 0x00e21850
};

struct cCombatantView {   // cCombatant subobject of a turret (+0x588)
    virtual void v00(); virtual void v04();
    virtual IObj* GetSpatial();                   // 0x08
    virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void SetTarget(void* target);         // 0x50
    int  GetDamageState();                        // 0x008e7f80
    bool IsDestroyed();                           // 0x00bfc600
};

struct cTargetObj {   // result of FindTarget (0x00cc26a0)
    uint32_t pad[0x34 / 4];
    IObj mSpatial;                                // 0x34
    bool IsInvalid(int flags);                    // 0x00c38990
};

struct cTurret {
    uint32_t pad0[0x34 / 4];
    IObj mSpatial;                                // 0x34
    uint32_t pad1[(0x588 - 0x38) / 4];
    cCombatantView mCombatant;                    // 0x588
    uint32_t pad2[(0x680 - 0x58c) / 4];
    EffectRef mpEffect;                           // 0x680
    cTool* GetPrimaryTool();                      // 0x00bce3d0
    cTool* GetTool();                             // 0x00bce3e0
    cTool* GetSecondaryTool();                    // 0x00bce3f0
    void   FaceAtTarget(void* target);            // 0x00bce480
};

struct cCity {   // cast of the front target (0xee9b2232)
    uint32_t pad0[0x120 / 4];
    IObj mSpatial;                                // 0x120
    uint32_t pad1[(0x748 - 0x124) / 4];
    float mThreat;                                // 0x748
};

struct cToolManager {
    void UseToolStart(cTool* tool, IObj* source, Vector3* target, int a, int b, IObj* targetObj, int c);  // 0x01050070
    void UseToolStop(cTool* tool);                // 0x0104fa90
};
struct cPlanet { int GetPlanetType(); };          // 0x00c70e00
struct cGameNounManager { void* GetPlayerCivilization(); };  // 0x00b25fb0

struct VectorV3 {   // eastl::vector<Vector3>
    Vector3* mpBegin; Vector3* mpEnd; Vector3* mpCapacity;
    VectorV3() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorV3();                                  // 0x00540520
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct cSpaceTurretStateInfo {
    uint32_t pad[2];
    uint64_t mNextFireTime;                       // 0x08
    uint64_t mNextBeamToggle;                     // 0x10
    uint64_t mBeamEndTime;                        // 0x18
    int      mBeamOn;                             // 0x20
};
struct StateMap { cSpaceTurretStateInfo& operator[](IObj* const& agent); };  // 0x00d56510

// spstl::slot_deque<AutoRefCount<T>, allocator, 128>
struct SlotEntry { uint32_t mNext; IObj* mpObject; };
struct SlotDeque {
    SlotEntry** mpBlocksBegin;
    SlotEntry** mpBlocksEnd;
    SlotEntry** mpBlocksCapacity;
    uint32_t pad0c;
    uint32_t pad10;
    int      mEndOffset;                          // 0x14
    uint32_t mFirst;                              // 0x18

    struct iterator {
        SlotDeque* mpDeque;
        uint32_t   mIndex;
        iterator& operator++();                   // 0x00abe9b0
        SlotEntry& entry() const { return mpDeque->mpBlocksBegin[mIndex >> 7][mIndex & 0x7f]; }
        uint32_t key() const { return (uint32_t)mpDeque + mIndex; }
        bool operator==(const iterator& o) const { return key() == o.key(); }
        bool operator!=(const iterator& o) const { return key() != o.key(); }
    };
    iterator begin();                             // 0x00abeaf0
    iterator end() {
        iterator it;
        it.mpDeque = this;
        it.mIndex = (mpBlocksEnd - mpBlocksBegin) * 128 - 127 + mEndOffset;
        return it;
    }
    int size();                                   // 0x00abefd0
    IObj*& front() { return mpBlocksBegin[mFirst >> 7][mFirst & 0x7f].mpObject; }
};

// ---- callees ----
uint32_t GetCurrentGameMode();                                      // 0x00b5b800
cPlanet* GetActivePlanet();                                         // 0x01021260
cGameNounManager* NounManager();                                    // 0x00b3d300
cToolManager* ToolManager();                                        // 0x00b3d390
IEffectsManager* EffectsManager();                                  // 0x0067ddd0
void ClearAllTargets(SlotDeque* agents);                            // 0x00d54c10
bool IsCityUnderAttack(cCity* city);                                // 0x01029950
bool IsPlanetContested(cPlanet* planet);                            // 0x0102ae60
bool IsRaidActive();                                                // 0x01041cf0
bool UpdateAirRaidSiren(void* civ, cCity* city);                    // 0x00d54940
void StopAirRaidSiren();                                            // 0x00d54760
cTurret* AgentToTurret(IObj** agent);                               // 0x00d54710
cTurret* AgentPtrToTurret(IObj* agent);                             // 0x00d546f0
cTargetObj* FindTarget(Vector3 pos, bool hostile, bool contested);  // 0x00cc26a0
Vector3 Vector3_Normalize(const Vector3& v);                        // 0x00436ce0
float Dot3(const Vector3& a, const Vector3& b);                     // 0x00455cc0
Vector3 OrthogonalVector(const Vector3& v);                         // 0x006985b0
Matrix3 Matrix3FromFacingAndUp(const Vector3& facing, const Vector3& up);  // 0x0069b440
void UpdateFirePattern(VectorV3* out, int shots, cTargetObj* target);      // 0x00d56070

struct cBehaviorSpaceTurret {
    uint32_t pad0[0xc / 4];
    SlotDeque mTargetList;                        // 0x0c
    uint32_t pad28;
    SlotDeque mAgentList;                         // 0x2c
    uint32_t pad48[(0x74 - 0x48) / 4];
    StateMap mStateMap;                           // 0x74
    uint32_t pad75[(0x90 - 0x78) / 4];
    struct Timer { uint32_t d[8]; uint64_t GetElapsedTime(); } mLifeTimer;  // 0x90 (0x00bc3190)
    uint64_t mNextFiringTime;                     // 0xb0
    uint32_t padb8;
    Vector3  mCityCenter;                         // 0xbc
    int      mAaShotsPerTurret;                   // 0xc8
    uint32_t padcc;
    uint64_t mSdrBeamLifetime;                    // 0xd0
    bool     mbWasHostile;                        // 0xd8

    int  GetActiveTurretCount();                  // 0x00d54ce0
    void UpdateWeaponData();                      // 0x00d547e0
    void StartDefense();                          // 0x00d56630
    void StopDefense();                           // 0x00d56870
    int  GetBusyTurretCount();                    // 0x00d54d90
    int  Action();
};

template <class T> inline T* object_cast4(IObj* p, uint32_t id) { return p ? (T*)p->Cast4(id) : 0; }

// @ 0x00d56c30
int cBehaviorSpaceTurret::Action()
{
    if (GetCurrentGameMode() == 0x1654c05 && GetActivePlanet()->GetPlanetType() == 4)
        return 1;

    if (mAgentList.mFirst == 0x3fffffff) {
        ClearAllTargets(&mAgentList);
        return 0;
    }
    if (GetActiveTurretCount() == 0) {
        ClearAllTargets(&mAgentList);
        return 0;
    }
    if (mTargetList.size() == 0) {
        ClearAllTargets(&mAgentList);
        return 0;
    }

    void* civ = NounManager()->GetPlayerCivilization();
    cCity* city = object_cast4<cCity>(mTargetList.front(), 0xee9b2232);
    if (city)
        ((IObj*)city)->Activate();

    bool hostile = false;
    if (IsCityUnderAttack(city))
        hostile = true;
    bool contested = false;
    if (IsPlanetContested(GetActivePlanet()))
        contested = true;
    if (city->mThreat >= 100.0f)
        contested = false;
    hostile = hostile || IsRaidActive();

    if (!mbWasHostile && hostile)
        hostile = UpdateAirRaidSiren(civ, city);
    else if (!hostile)
        StopAirRaidSiren();

    bool active = hostile || contested || IsRaidActive();
    if (!mbWasHostile && active)
        StartDefense();
    mbWasHostile = active;

    if (!active) {
        StopDefense();
        for (SlotDeque::iterator it = mAgentList.begin(); it != mAgentList.end(); ++it) {
            IObj* agent = it.entry().mpObject;
            if (agent) {
                cTurret* turret = (cTurret*)agent->Cast8(0x436f315);
                if (turret && turret->mpEffect.mpObject)
                    turret->mpEffect.mpObject->Stop(0);
            }
        }
        return 1;
    }

    UpdateWeaponData();
    uint64_t now = mLifeTimer.GetElapsedTime();

    if (now > mNextFiringTime) {
        cTool* tool = AgentToTurret(&mAgentList.begin().entry().mpObject)->GetTool();
        mNextFiringTime = now + tool->GetRefireMs();
        cTargetObj* target = FindTarget(city->mSpatial.GetPosition(), hostile, contested);
        if (target && !target->IsInvalid(1)) {
            IObj* targetSpatial = &target->mSpatial;
            Vector3 toTarget = targetSpatial->GetPosition() - mCityCenter;
            tool->GetDamage();
            tool->GetMaxRange();
            if (Dot3(Vector3_Normalize(toTarget), Vector3_Normalize(mCityCenter)) > 0.0f) {
                int busy = GetBusyTurretCount();
                int shots = (GetActiveTurretCount() - busy) * mAaShotsPerTurret;
                VectorV3 pattern;
                UpdateFirePattern(&pattern, shots, target);
                int n = pattern.size();
                SlotDeque::iterator it = mAgentList.begin();
                if (n > 0) {
                    float* p = &pattern.mpBegin[n].x - 1;
                    do {
                        cTurret* turret = AgentPtrToTurret(it.entry().mpObject);
                        if (turret->mCombatant.GetDamageState() != 2 && !turret->mCombatant.IsDestroyed()) {
                            Vector3 aim(p[-2], p[-1], p[0]);
                            cTool* t = turret->GetTool();
                            ToolManager()->UseToolStart(t, turret ? &turret->mSpatial : 0, &aim, -1, 0,
                                                        targetSpatial, 1);
                            ToolManager()->UseToolStop(t);
                            n--;
                            p -= 3;
                        }
                        if (mAgentList.end() == ++it)
                            it = mAgentList.begin();
                    } while (n > 0);
                }
            }
        }
    }

    for (SlotDeque::iterator it = mAgentList.begin(); it != mAgentList.end(); ++it) {
        IObj* agent = it.entry().mpObject;
        cTurret* turret = agent ? (cTurret*)agent->Cast8(0x436f315) : 0;
        cSpaceTurretStateInfo& st = mStateMap[agent];
        cCombatantView* combatant = &turret->mCombatant;

        if (combatant->GetDamageState() == 2 || combatant->IsDestroyed()) {
            combatant->SetTarget(0);
            continue;
        }

        cTool* primary = turret->GetPrimaryTool();
        cTool* secondary = turret->GetSecondaryTool();
        bool fire = false;
        if (now > st.mNextFireTime) {
            st.mNextFireTime += primary->GetRefireMs();
            fire = true;
        }
        if (st.mBeamEndTime == 0) {
            st.mBeamEndTime = now + mSdrBeamLifetime;
            st.mNextBeamToggle = now + secondary->GetRefireMs();
        }

        if (st.mNextBeamToggle < 1000 || now <= st.mNextBeamToggle - 1000) {
            if (now > st.mBeamEndTime) {
                if (turret->mpEffect.mpObject && turret->mpEffect.mpObject->IsRunning())
                    turret->mpEffect.mpObject->Stop(0);
                turret->mpEffect.reset();
            }
        } else {
            if (st.mBeamOn == 1 && turret->mpEffect.mpObject == 0) {
                IEffectsManager* em = EffectsManager();
                if (em->CreateVisualEffect(0xc19e6439, 0, turret->mpEffect.AsPPTypeParam())) {
                    IObj* spatial = &turret->mSpatial;
                    Vector3 up = Vector3_Normalize(spatial->GetPosition());
                    Vector3 facing = Vector3_Normalize(OrthogonalVector(up));
                    Transform xf;
                    xf.SetRotation(Matrix3FromFacingAndUp(facing, up));
                    xf.SetOffset(spatial->GetPosition());
                    turret->mpEffect.mpObject->SetTransform(xf);
                    turret->mpEffect.mpObject->Start(0);
                }
            }
        }

        if (now > st.mNextBeamToggle) {
            st.mBeamEndTime = now + mSdrBeamLifetime;
            st.mNextBeamToggle = now + secondary->GetRefireMs();
            st.mBeamOn = st.mBeamOn == 0;
        }

        cTargetObj* target = FindTarget(city->mSpatial.GetPosition(), hostile, contested);
        if (!target || target->IsInvalid(1)) {
            combatant->SetTarget(0);
            continue;
        }

        Vector3 targetPos(target->mSpatial.GetPosition());
        Vector3 toTarget = targetPos - mCityCenter;
        bool inArc = Dot3(Vector3_Normalize(toTarget), Vector3_Normalize(mCityCenter)) > 0.0f;
        void* aimTarget = (char*)target + 0x508;
        turret->FaceAtTarget(aimTarget);

        const Vector3& cp = combatant->GetSpatial()->GetPosition();
        float dx = targetPos.x - cp.x;
        float dy = targetPos.y - cp.y;
        float dz = targetPos.z - cp.z;
        float dist = (float)sqrt(dz * dz + dy * dy + dx * dx);

        if (dist > primary->GetMinRange() && dist < primary->GetMaxRange()) {
            if (fire && inArc) {
                combatant->SetTarget(aimTarget);
                continue;
            }
        } else if (dist < secondary->GetMaxRange() && now < st.mBeamEndTime && inArc && st.mBeamOn == 0) {
            combatant->SetTarget(aimTarget);
            continue;
        }
        combatant->SetTarget(0);
    }
    return 1;
}
