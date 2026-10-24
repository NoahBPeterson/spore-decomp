// Slice s00dc2720 -- four entries of the SP behaviour / game-data block:
//
//   0x00dc2720  SP::UFO_FOLLOW_AVATAR_Tick -- the UFO tool's follow-avatar behaviour: picks and
//                                              validates the leader, then runs a 4-state sub-machine
//                                              that steers the UFO toward a target point.
//   0x00dc2e40  unnamed                    -- std::partition-style step over a range of pointers,
//                                              ordered with the spatial distance predicate.
//   0x00dc2ee0  unnamed                    -- "pull the head element forward" step for the same
//                                              range, used while the spatial sort is running.
//   0x00dc32d0  unnamed                    -- lays out a ring of game-data entries: a tuning-state
//                                              switch, a gather of the matching entries and their
//                                              ring-direction vectors.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same SP behaviour module as s00dc0b00 / s00dacd40).
#include "types.h"

#pragma warning(disable: 4100)

extern "C" double sqrt(double);
extern "C" double sin(double);
extern "C" double cos(double);

namespace SP {

struct Vec3 { float x, y, z; };

class cSpatialObject;
class cSpatialSub;
class cCombatant;
class cCommunity;

// A refcounted game object: AddRef is vtable slot 0, Release slot 1.
class RefCounted {
public:
    virtual void AddRef();                                    // +0x00
    virtual void Release();                                   // +0x04
};

// The +0x5a8 cCombatant sub-object of a creature.
class cCombatant : public RefCounted {
public:
    virtual void v02();
    virtual cSpatialObject* GetOwnerNoun();                   // +0x0c
};

// The +0xc0 locomotion sub-object (own vtable).
class cLocomotion {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual const Vec3* GetPosition();                        // +0x2c  0x00c0d6b0
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16();
    virtual const Vec3* GetFacing(Vec3* out);                 // +0x5c
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
    virtual void v30(); virtual void v31();
    virtual bool TestGround();                                // +0x48
    virtual void v33(); virtual void v34(); virtual void v35();
    virtual bool IsFlying();                                  // +0x58
};

// Per-object behaviour-tree record reached through +0xb4c.
struct cBehaviorTreeData {
    uint32_t pad00[0x1d8 / 4];
    uint32_t mTreeId;                                         // +0x1d8  behaviour-tree fourcc
};

// The spatial sub-object embedded at +0x120 of every noun: its own vtable, slot 0x2c yields the
// object's world position (the key the distance predicate sorts on).
class cSpatialSub {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual const Vec3* GetPosition();                        // +0x2c
};

// A noun group (0x00c38b00); slot 3 resolves a member by its fourcc key.
class cGroup {
public:
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual cSpatialObject* FindMember(uint32_t key);         // +0x0c
};

// The spatial object the behaviour and the ring code both work on (creature / UFO / game data
// entry).  Only the fields this slice reads or writes are named; the gaps keep the retail offsets.
class cSpatialObject : public RefCounted {
public:
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07();
    virtual int  GetTypeHash();                               // +0x20  0x00c0...
    virtual void v09(); virtual void v0a(); virtual void v0b(); virtual void v0c();
    virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual int  GetRingKey();                                // +0x60
    virtual void v19();
    uint8_t  pad04[0xc0 - 0x04];
    cLocomotion mLoco;                                        // +0xc0 locomotion sub-object
    uint8_t  padc4[0x120 - 0xc4];
    cSpatialSub mSpatial120;                                  // +0x120 spatial sub-object
    uint8_t  pad124[0x135 - 0x124];
    bool     mbValid135;                                      // +0x135 the leader is usable
    uint8_t  pad136[0x5a8 - 0x136];
    cCombatant mCombatant5a8;                                 // +0x5a8 combatant sub-object
    uint8_t  pad5ac[0x624 - 0x5ac];
    bool     mbDirty624;                                      // +0x624 behaviour state changed
    uint8_t  pad625[0x68c - 0x625];
    int      mFamily68c;                                      // +0x68c family / house id
    bool     mbFlag690;                                       // +0x690
    uint8_t  pad691[0x694 - 0x691];
    Vec3     mBasis694;                                       // +0x694 ring direction
    uint8_t  pad6a0[0x6b0 - 0x6a0];
    int      mRingIndex6b0;                                   // +0x6b0 index within the ring
    float    mField6b4;                                       // +0x6b4
    float    mField6b8;                                       // +0x6b8
    uint8_t  pad6bc[0x6c8 - 0x6bc];
    void*    mpEnv;                                           // +0x6c8 behaviour environment / tree
    uint8_t  pad6cc[0x714 - 0x6cc];
    int      mState714;                                       // +0x714 tuning / model state
    uint8_t  pad718[0x74c - 0x718];
    bool     mbEnabled74c;                                    // +0x74c behaviour switched on
    uint8_t  pad74d[0xb20 - 0x74d];
    void*    mpSpecies;                                       // +0xb20 species profile
    uint8_t  padb24[0xb34 - 0xb24];
    int      mRankB34;                                        // +0xb34 (== 1 for a follower)
    uint8_t  padb38[0xb4c - 0xb38];
    cBehaviorTreeData* mpGameData;                            // +0xb4c behaviour-tree data
    uint8_t  padb50[0xb5e - 0xb50];
    bool     mbDeadB5e;                                       // +0xb5e dead / despawned
    uint8_t  padb5f[4];
    // ---- predicates / lookups (plain members, direct calls in the original) ----
    bool          IsBaby();                                   // 0x00c0b770
    bool          IsEpic();                                   // 0x00c0c0e0
    cCombatant*   GetCombatantTarget();                       // 0x00c0ee60
    cGroup*       GetTargetGroup();                           // 0x00c38b00
    // ---- posse-member interface (0x00c3daa0 / 0x00c3be70) ----
    void SetTargetDistance(float distance);                   // 0x00c3daa0
    void SetTargetPosition(const Vec3& position);             // 0x00c3be70
};

}  // namespace SP

namespace EA {
template <class T>
class AutoRefCount {
public:
    T* mpObj;                                                 // +0x00
    AutoRefCount() : mpObj(0) {}
    explicit AutoRefCount(T* p) : mpObj(p) { if (mpObj) mpObj->AddRef(); }
    AutoRefCount(const AutoRefCount& o) : mpObj(o.mpObj) { if (mpObj) mpObj->AddRef(); }
    ~AutoRefCount() { if (mpObj) mpObj->Release(); }
    AutoRefCount& operator=(const AutoRefCount& o) {
        if (mpObj != o.mpObj) {
            T* p = o.mpObj;
            if (p) p->AddRef();
            T* old = mpObj;
            mpObj = p;
            if (old) old->Release();
        }
        return *this;
    }
    T* Get() const { return mpObj; }
};
}  // namespace EA

namespace eastl {

// Functor whose only state is the query origin; the comparison body is unnamed in the binary, so
// the member keeps its address as its name (calls arrive in ECX with the two objects pushed).
struct AgentDistanceCompare {
    SP::Vec3 mOrigin;
    bool FUN_00ac0730(const SP::cSpatialSub* a, const SP::cSpatialSub* b) const;
};

template <class T>
class vector {
public:
    T* mpBegin;                                               // +0x00
    T* mpEnd;                                                 // +0x04
    T* mpCapacity;                                            // +0x08
    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    vector(T* begin, T* end, T* capacity)
        : mpBegin(begin), mpEnd(end), mpCapacity(capacity) {}
    void push_back(const T& value) {
        if (mpEnd < mpCapacity) {
            *mpEnd = value;
            ++mpEnd;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
    void DoInsertValue(T* position, const T& value);          // 0x00aea5d0
    ~vector();                                                // 0x00ad92d0
};

}  // namespace eastl

namespace SP {

class cCommunity {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual eastl::vector<EA::AutoRefCount<cSpatialObject> >* GetMembers();   // +0x90
    cSpatialObject* GetLeader();                              // 0x00c00650
};

}  // namespace SP

using SP::Vec3;
using SP::cSpatialObject;
using SP::cSpatialSub;
using SP::cLocomotion;
using SP::cCombatant;
using SP::cGroup;
using SP::cCommunity;
using eastl::AgentDistanceCompare;

// ---- globals -------------------------------------------------------------------
extern const Vec3  g_originThread;                            // 0x0169f444 (x/y/z)
extern const float g_floatMax;                                // 0x0147c300 FLT_MAX
extern const float g_ringBasis[7];                            // 0x0169fa08 .. 0x0169fa20

// Per-state ring radii and weights (values all 20.0 / 25.0 / -1.0).
extern const float kRingRadiusNear;                           // 0x0159d59c 20.0
extern const float kRingRadiusB;                              // 0x0159d594 25.0
extern const float kRingRadiusC;                              // 0x0159d598 25.0
extern const float kRingRadiusD;                              // 0x0159d590 25.0
extern const float kRingRadiusE;                              // 0x0159d5e0 25.0
extern const float kRingWeightA;                              // 0x013eb1bc -1.0
extern const float kRingWeightB;                              // 0x0159d5ec -1.0
extern const float kRingWeightC;                              // 0x0159d5e4 -1.0
extern const float kRingField6b4;                             // 0x0159d618 3.5
extern const float kRingField6b8;                             // 0x0159d61c 2.5

// ---- callees -------------------------------------------------------------------
class cGameNounManager {
public:
    cSpatialObject* GetAvatar();                              // 0x00b1fdb0
    cCommunity*     GetPlayerTribe();                         // 0x00bfc5f0
    void* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);   // 0x00b21340
};
cGameNounManager* NounManager();                              // 0x00b3d300
int  GetCurrentGameMode();                                    // 0x00b5b800

class cBehaviorStimuli {
public:
    void ClearAll(int zero, int flags);                       // 0x00bc98f0
    void PostEvent(uint32_t id, uint32_t zero, float range, void* who);   // 0x00bc97f0
};
class cBehaviorEnv {
public:
    uint32_t pad00[2];
    cBehaviorStimuli mStimuli;                                // +0x08
};
class cSpatialQuery {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11();
    virtual bool FindObjects(const Vec3* pos, float range,
                             eastl::vector<EA::AutoRefCount<cSpatialObject> >* results, int zero,
                             void* callback, cSpatialObject* who);   // +0x48
};
class cSPDramaManager {
public:
    int   GetState();                                         // 0x00d516a0
    void* GetActiveEventTuning(int which);                    // 0x00d4cb50
};
cSPDramaManager* GetDramaManager();                           // 0x00d51660

float GetPropertyT(void* obj, uint32_t key, float def);       // 0x004e1c70
Vec3* RandomDirection3(Vec3* out);                            // 0x00b7e560
bool  Vector3_NotEqual(const Vec3* a, const Vec3* b);         // 0x0041dd30
cSpatialObject* CastCreature(void* noun);                     // 0x00ae66f0
cSpatialQuery*  GetSpatialQuery();                            // 0x00b3d240
class cPlanetModel {
public:
    void Project(Vec3* out, const Vec3* in);                  // 0x00b81630
};
cPlanetModel* GetPlanetModel();                               // 0x00b3d350

// Sorting helpers of the spatial range sort; unnamed in the binary, so named by address.
void FUN_00b2af00(cSpatialObject** a, cSpatialObject** b);                     // swap the two slots
void FUN_00aca890(cSpatialObject** begin, cSpatialObject** first, AgentDistanceCompare pred);
void FUN_00aca900(cSpatialObject** begin, cSpatialObject** first, AgentDistanceCompare pred);
void FUN_00aca0c0(cSpatialObject** begin, int zero, int count, int start,
                  EA::AutoRefCount<cSpatialObject> value, AgentDistanceCompare pred);
void operator_delete_array(void* p);                          // 0x00f47380

namespace SP {

// SP::UFO_FOLLOW_AVATAR_memory_block (PDB): the behaviour's per-instance state.
struct UFO_FOLLOW_AVATAR_memory_block {
    float mMovementTimer;                                     // +0x00
    bool  mbDone;                                             // +0x04
    uint32_t mState;                                          // +0x08
};

}  // namespace SP
using SP::UFO_FOLLOW_AVATAR_memory_block;

// Game-mode ids compared by GetCurrentGameMode().
enum {
    kGameCreature = 0x1654c01,
    kGameTribe    = 0x1654c02,
};
enum {
    kCreatureAnimalNoun = 0x18eb45e,   // cCreatureAnimal::NOUN_ID
    kUFOFollowTree      = 0x3704748,   // behaviour-tree id already driving the candidate
    kGroupMemberKey     = 0xee9b2232,  // fourcc used by cGroup::FindMember
};

// Property keys read from the active drama-event tuning block.
enum {
    kPropTargetDistance = 0x9b0ef346,
    kPropUnused         = 0xa58acb11,
    kPropWanderRadius   = 0x0005f8cc,
    kPropPlanTime       = 0x34e39082,
    kPropSpeed          = 0x829df2e1,
    kPropSearchRange    = 0x9650f75f,
};

// The spatial sub-object that carries the position the distance predicate sorts on, with the
// original's null check on the owning object.
static __forceinline cSpatialSub* ObjectSpatial(cSpatialObject* o)
{
    return o ? &o->mSpatial120 : 0;
}

// ===========================================================================
// @ 0x00dc2e40
// ===========================================================================
// One partition step of the spatial range sort: walks `first` forward and `last` back while the
// distance predicate orders the two ends, swapping what is out of place.  The cursor object the
// comparisons run against is consumed (released) by the step.
cSpatialObject** FUN_00dc2e40(cSpatialObject** first, cSpatialObject** last, cSpatialObject* cursor,
                               AgentDistanceCompare pred)
{
    for (;;) {
        while (pred.FUN_00ac0730(ObjectSpatial(*first), ObjectSpatial(cursor)))
            ++first;
        do {
            --last;
        } while (pred.FUN_00ac0730(ObjectSpatial(cursor), ObjectSpatial(*last)));

        if (first >= last)
            break;
        FUN_00b2af00(first, last);
        ++first;
    }
    if (cursor)
        cursor->Release();
    return first;
}

// ===========================================================================
// @ 0x00dc2ee0
// ===========================================================================
// Pulls the head element of [begin, first) forward: every element of [first, last) that the
// predicate rates ahead of the head is swapped with it, and the [begin, first) heap is repaired
// around the element that was displaced.
void FUN_00dc2ee0(cSpatialObject** begin, cSpatialObject** first, cSpatialObject** last,
                  AgentDistanceCompare pred)
{
    FUN_00aca890(begin, first, pred);
    for (cSpatialObject** it = first; it < last; ++it) {
        cSpatialObject* elem = *it;
        if (!pred.FUN_00ac0730(ObjectSpatial(elem), ObjectSpatial(*begin)))
            continue;

        if (elem)
            elem->AddRef();

        cSpatialObject* head = *begin;
        if (head != elem) {
            if (head)
                head->AddRef();
            *it = head;
            if (elem)
                elem->Release();
        }

        FUN_00aca0c0(begin, 0, (int)(first - begin), 0, EA::AutoRefCount<cSpatialObject>(elem), pred);
        if (elem)
            elem->Release();
    }
    FUN_00aca900(begin, first, pred);
}

// ===========================================================================
// @ 0x00dc2720
// ===========================================================================
namespace SP {

bool UFO_FOLLOW_AVATAR_Tick(cSpatialObject* self, cSpatialObject* avatar, void* a3, int a4, int a5,
                            UFO_FOLLOW_AVATAR_memory_block* mem, int a6, float dt)
{
    // ---- pick the leader -------------------------------------------------
    cSpatialObject* leader;
    int mode = GetCurrentGameMode();
    if (mode == kGameCreature) {
        leader = NounManager()->GetAvatar();
    } else if (mode == kGameTribe) {
        cCommunity* tribe = NounManager()->GetPlayerTribe();
        leader = tribe->GetLeader();
        if (leader == 0 || leader->mbDeadB5e) {
            eastl::vector<EA::AutoRefCount<cSpatialObject> >* members = tribe->GetMembers();
            for (EA::AutoRefCount<cSpatialObject>* it = members->mpBegin; it != members->mpEnd; ++it) {
                cSpatialObject* candidate = it->Get();
                if (!candidate->IsBaby())
                    continue;
                if (candidate == leader)
                    continue;
                if (candidate->mbDeadB5e)
                    continue;
                leader = candidate;
                break;
            }
        }
    } else {
        return false;
    }

    if (leader == 0 || !leader->mbValid135)
        return false;

    cLocomotion* loco = &leader->mLoco;
    const Vec3* leaderPos = loco->GetPosition();
    if (leaderPos->x == g_originThread.x && leaderPos->y == g_originThread.y &&
        leaderPos->z == g_originThread.z)
        return false;

    if (!self->mbEnabled74c)
        return true;

    cBehaviorEnv* env = (cBehaviorEnv*)self->mpEnv;
    if (mem->mbDone) {
        env->mStimuli.ClearAll(2, 0);
        return false;
    }

    mem->mMovementTimer -= dt;
    if (mem->mMovementTimer >= 0.0f)
        return true;

    // ---- read the tuning block ------------------------------------------
    cSPDramaManager* drama = GetDramaManager();
    bool bLowState = drama->GetState() <= 0;
    void* tuning = drama->GetActiveEventTuning(2);

    float targetDistance = GetPropertyT(tuning, kPropTargetDistance, 5.0f);
    GetPropertyT(tuning, kPropUnused, 20.0f);
    float wanderRadius = GetPropertyT(tuning, kPropWanderRadius, 75.0f);
    float planTime = GetPropertyT(tuning, kPropPlanTime, 7.5f);
    float speed = GetPropertyT(tuning, kPropSpeed, 5.0f);
    float searchRange = GetPropertyT(tuning, kPropSearchRange, 50.0f);

    mem->mMovementTimer = planTime;

    Vec3 target = g_originThread;

    switch (mem->mState) {
    case 0: {
        target = *loco->GetPosition();
        mem->mState = 1;
        break;
    }
    case 1: {
        Vec3 facing;
        loco->GetFacing(&facing);
        Vec3 offset;
        offset.x = facing.x * speed;
        offset.y = facing.y * speed;
        offset.z = facing.z * speed;
        const Vec3* pos = loco->GetPosition();
        target.x = offset.x + pos->x;
        target.y = offset.y + pos->y;
        target.z = offset.z + pos->z;
        mem->mState = 2;
        break;
    }
    case 2: {
        Vec3 dir;
        RandomDirection3(&dir);
        Vec3 offset;
        offset.x = dir.x * wanderRadius;
        offset.y = dir.y * wanderRadius;
        offset.z = dir.z * wanderRadius;
        const Vec3* pos = loco->GetPosition();
        target.x = offset.x + pos->x;
        target.y = offset.y + pos->y;
        target.z = offset.z + pos->z;
        mem->mState = 3;
        break;
    }
    case 3: {
        cCombatant* found = 0;
        if (!bLowState) {
            cCombatant* exclude = leader->GetCombatantTarget();
            const Vec3* pos = loco->GetPosition();
            EA::AutoRefCount<cSpatialObject> buffer[32];
            eastl::vector<EA::AutoRefCount<cSpatialObject> > hits(buffer, buffer, buffer + 32);
            float rangeSq = speed * speed;
            // 0x00d9a9c0: the per-noun filter callback handed to cSpatialQuery::FindObjects.
            if (GetSpatialQuery()->FindObjects(pos, searchRange, &hits, 0, (void*)0x00d9a9c0, leader)) {
                int count = (int)(hits.mpEnd - hits.mpBegin);
                for (int i = 0; i < count; ++i) {
                    cSpatialObject* candidate = CastCreature(hits.mpBegin[i].Get());
                    if (candidate == 0)
                        continue;
                    if (candidate->mbDeadB5e)
                        continue;
                    cLocomotion* candidateLoco = &candidate->mLoco;
                    if (!candidateLoco->TestGround())
                        continue;
                    if (candidateLoco->IsFlying())
                        continue;
                    if (candidate->IsEpic())
                        continue;
                    if (&candidate->mCombatant5a8 == exclude)
                        continue;
                    if (leader->mpSpecies == candidate->mpSpecies)
                        continue;
                    if (candidate->GetTypeHash() != kCreatureAnimalNoun)
                        continue;
                    if (candidate->mpGameData->mTreeId == kUFOFollowTree)
                        continue;
                    const Vec3* candidatePos = candidateLoco->GetPosition();
                    float dx = candidatePos->x - pos->x;
                    float dy = candidatePos->y - pos->y;
                    float dz = candidatePos->z - pos->z;
                    if (dx * dx + dz * dz + dy * dy >= rangeSq)
                        found = &candidate->mCombatant5a8;
                }
            }
            hits.~vector();
            if (found != 0) {
                cSpatialObject* who = found->GetOwnerNoun();
                env->mStimuli.PostEvent(1, 0, g_floatMax, who);
                return false;
            }
        }
        Vec3 dir;
        RandomDirection3(&dir);
        const Vec3* pos = loco->GetPosition();
        target.x = dir.x * wanderRadius + pos->x;
        target.y = dir.y * wanderRadius + pos->y;
        target.z = dir.z * wanderRadius + pos->z;
        break;
    }
    }

    if (!Vector3_NotEqual(&target, &g_originThread))
        return true;

    // ---- steer ----------------------------------------------------------
    Vec3 projected;
    GetPlanetModel()->Project(&projected, &target);
    float distSq = projected.x * projected.x + projected.z * projected.z + projected.y * projected.y;
    float distance = (float)sqrt((double)distSq);

    if (!bLowState) {
        self->SetTargetDistance(targetDistance * 10.0f + distance);
        mem->mMovementTimer = planTime * 3.0f;
        mem->mbDone = true;
    } else {
        self->SetTargetDistance(distance + targetDistance);
    }
    self->SetTargetPosition(projected);
    self->mbDirty624 = 1;
    return true;
}

}  // namespace SP

// ===========================================================================
// @ 0x00dc32d0
// ===========================================================================
// The layout record written by the ring code (argument 6 of the original).
struct RingStateOut {
    float mWeight;                                            // +0x00
    float mRadius;                                            // +0x04
    float mSpacing;                                           // +0x08
    int   mField0C;                                           // +0x0c
    bool  mbFlag10;                                           // +0x10
    Vec3  mOrigin;                                            // +0x14
};

// SP::cGameNounManager::tGameDataVectorT<T>: the noun manager's per-tag entry vector.
struct GameDataVector {
    uint32_t mPad;                                            // +0x00
    EA::AutoRefCount<cSpatialObject>* mpBegin;                // +0x04
    EA::AutoRefCount<cSpatialObject>* mpEnd;                  // +0x08
};

bool FUN_00dc32d0(cSpatialObject* self, void* a2, void* a3, void* a4, void* a5, RingStateOut* out)
{
    out->mRadius = 0.0f;
    out->mWeight = kRingWeightA;
    out->mField0C = 0;
    out->mbFlag10 = false;
    out->mOrigin = g_originThread;

    switch (self->mState714) {
    case 1:
        out->mRadius = kRingRadiusNear;
        out->mWeight = kRingWeightA;
        break;
    case 2:
    case 11:
        out->mRadius = kRingRadiusB;
        out->mWeight = kRingWeightA;
        break;
    case 3:
        out->mRadius = kRingRadiusE;
        out->mWeight = kRingWeightC;
        break;
    case 6: {
        cGroup* group = self->GetTargetGroup();
        out->mWeight = (group != 0 && group->FindMember(kGroupMemberKey) != 0)
                     ? kRingWeightA : kRingWeightB;
        out->mRadius = kRingRadiusD;
        break;
    }
    case 8:
        out->mRadius = kRingRadiusC;
        out->mWeight = kRingWeightA;
        break;
    default:
        break;
    }

    // ---- gather the entries of the same family and state -----------------
    eastl::vector<EA::AutoRefCount<cSpatialObject> > entries;
    GameDataVector* gameData = (GameDataVector*)NounManager()->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00ad48b0, (void*)0x00b1e500,
        (void*)0x018ebadc);
    for (EA::AutoRefCount<cSpatialObject>* it = gameData->mpBegin; it != gameData->mpEnd; ++it) {
        cSpatialObject* entry = it->Get();
        if (entry->mFamily68c != self->mFamily68c)
            continue;
        if (entry->mState714 != self->mState714)
            continue;
        entries.push_back(EA::AutoRefCount<cSpatialObject>(entry));
    }

    // ---- spread them over the ring --------------------------------------
    if (entries.mpBegin != entries.mpEnd) {
        int count = (int)(entries.mpEnd - entries.mpBegin);
        float step = 1.0f / (float)count;
        int index = 0;
        for (EA::AutoRefCount<cSpatialObject>* it = entries.mpBegin; it != entries.mpEnd; ++it, ++index) {
            cSpatialObject* entry = it->Get();
            entry->mRingIndex6b0 = index;

            float angle = ((float)entry->mRingIndex6b0 * step) * g_ringBasis[0];
            angle *= 0.5f;
            float sn = (float)sin((double)angle);
            float cs = (float)cos((double)angle);

            float u = sn * g_ringBasis[1];                    // 0x0169fa0c
            float v = sn * g_ringBasis[2];                    // 0x0169fa10
            float w = sn * g_ringBasis[3];                    // 0x0169fa14
            float kA = g_ringBasis[4];                        // 0x0169fa18
            float kB = g_ringBasis[5];                        // 0x0169fa1c
            float kC = g_ringBasis[6];                        // 0x0169fa20

            entry->mBasis694.x = 2.0f * ((v * u - cs * w) * kB + (cs * v + w * u) * kC)
                               + (1.0f - 2.0f * (v * v + w * w)) * kA;
            entry->mBasis694.y = 2.0f * ((w * v - cs * u) * kC + (cs * w + v * u) * kA)
                               + (1.0f - 2.0f * (u * u + w * w)) * kB;
            entry->mBasis694.z = 2.0f * ((cs * u + w * v) * kB + (w * u - cs * v) * kA)
                               + (1.0f - 2.0f * (u * u + v * v)) * kC;
        }
    }

    out->mSpacing = 0.0f;
    self->mField6b4 = kRingField6b4;
    self->mbDirty624 = 1;
    self->mbFlag690 = 1;
    self->mField6b8 = kRingField6b8;

    for (EA::AutoRefCount<cSpatialObject>* it = entries.mpBegin; it != entries.mpEnd; ++it) {
        if (it->Get() != 0)
            it->Get()->Release();
    }
    if (entries.mpBegin != 0) {
        if (*((int*)entries.mpBegin - 1) != 0)
            operator_delete_array(entries.mpBegin);
    }
    return true;
}
