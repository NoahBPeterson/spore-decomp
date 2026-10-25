// src/game/SPGonzago/SPUFOBehaviorTrees.cpp -- migrated from slice(s) s00dc2720 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUFOBehaviorTrees.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cBehaviorTreeData.h"
#include "SP/cCombatant.h"
#include "SP/cCommunity.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cSpatialObject.h"

// unnamed retail callees and globals (address in the comment)
extern "C" double sqrt(double);
extern const float g_floatMax;                                // 0x0147c300 FLT_MAX
#pragma warning(disable: 4100)

// ---- items of slice s00dc2720 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double sqrt(double);
namespace SP {
struct Vec3 { float x, y, z; };
}
namespace SP {
class cSpatialObject_s00dc_2720;
}
namespace SP {
class cSpatialSub;
}
namespace SP {
class cCombatant_s00dc_2720;
}
namespace SP {
class cCommunity_s00dc_2720;
}
namespace SP {
class RefCounted {
public:
    virtual void AddRef();                                    // +0x00
    virtual void Release();                                   // +0x04
};
}
namespace SP {
class cCombatant_s00dc_2720 : public RefCounted {
public:
    virtual void v02();
    virtual cSpatialObject_s00dc_2720* GetOwnerNoun();                   // +0x0c
};
}
namespace SP {
class cLocomotion {
public:
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
    virtual const Vec3* GetPosition();                        // +0x2c  0x00c0d6b0
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
    virtual const Vec3* GetFacing(Vec3* out);                 // +0x5c
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
virtual void v2e();
virtual void v2f();
virtual void v30();
virtual void v31();
    virtual bool TestGround();                                // +0x48
virtual void v33();
virtual void v34();
virtual void v35();
    virtual bool IsFlying();                                  // +0x58
};
}
namespace SP {
struct cBehaviorTreeData_s00dc_2720 {
    uint32_t pad00[0x1d8 / 4];
    uint32_t mTreeId;                                         // +0x1d8  behaviour-tree fourcc
};
}
namespace SP {
class cSpatialSub {
public:
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
    virtual const Vec3* GetPosition();                        // +0x2c
};
}
namespace SP {
class cGroup {
public:
virtual void v00();
virtual void v01();
virtual void v02();
    virtual cSpatialObject_s00dc_2720* FindMember(uint32_t key);         // +0x0c
};
}
namespace SP {
class cSpatialObject_s00dc_2720 : public RefCounted {
public:
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual int  GetTypeHash();                               // +0x20  0x00c0...
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
    virtual int  GetRingKey();                                // +0x60
    virtual void v19();
    uint8_t  pad04[0xc0 - 0x04];
    cLocomotion mLoco;                                        // +0xc0 locomotion sub-object
    uint8_t  padc4[0x120 - 0xc4];
    cSpatialSub mSpatial120;                                  // +0x120 spatial sub-object
    uint8_t  pad124[0x135 - 0x124];
    bool     mbValid135;                                      // +0x135 the leader is usable
    uint8_t  pad136[0x5a8 - 0x136];
    cCombatant_s00dc_2720 mCombatant5a8;                                 // +0x5a8 combatant sub-object
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
    cBehaviorTreeData_s00dc_2720* mpGameData;                            // +0xb4c behaviour-tree data
    uint8_t  padb50[0xb5e - 0xb50];
    bool     mbDeadB5e;                                       // +0xb5e dead / despawned
    uint8_t  padb5f[4];
    // ---- predicates / lookups (plain members, direct calls in the original) ----
    bool          IsBaby();                                   // 0x00c0b770
    bool          IsEpic();                                   // 0x00c0c0e0
    cCombatant_s00dc_2720*   GetCombatantTarget();                       // 0x00c0ee60
    cGroup*       GetTargetGroup();                           // 0x00c38b00
    // ---- posse-member interface (0x00c3daa0 / 0x00c3be70) ----
    void SetTargetDistance(float distance);                   // 0x00c3daa0
    void SetTargetPosition(const Vec3& position);             // 0x00c3be70
};
}
namespace EA {
template <class T>
class AutoRefCount_s00dc_2720 {
public:
    T* mpObj;                                                 // +0x00
    AutoRefCount_s00dc_2720() : mpObj(0) {}
    explicit AutoRefCount_s00dc_2720(T* p) : mpObj(p) { if (mpObj) mpObj->AddRef(); }
    AutoRefCount_s00dc_2720(const AutoRefCount_s00dc_2720& o) : mpObj(o.mpObj) { if (mpObj) mpObj->AddRef(); }
    ~AutoRefCount_s00dc_2720() { if (mpObj) mpObj->Release(); }
    AutoRefCount_s00dc_2720& operator=(const AutoRefCount_s00dc_2720& o) {
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
};  // namespace EA
}
namespace eastl {
template <class T>
class vector_s00dc_2720 {
public:
    T* mpBegin;                                               // +0x00
    T* mpEnd;                                                 // +0x04
    T* mpCapacity;                                            // +0x08
    vector_s00dc_2720() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    vector_s00dc_2720(T* begin, T* end, T* capacity)
        : mpBegin(begin), mpEnd(end), mpCapacity(capacity) {}
    void push_back(const T& value) {
        if (mpEnd < mpCapacity) {
            *mpEnd = value;
            ++mpEnd;
        } else {
            DoInsertValue(mpEnd, value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
        }
    }
    void DoInsertValue(T* position, const T& value);          // 0x00aea5d0
    ~vector_s00dc_2720();                                                // 0x00ad92d0
};
}
namespace SP {
class cCommunity_s00dc_2720 {
public:
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
    virtual eastl::vector_s00dc_2720<EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720> >* GetMembers();   // +0x90
    cSpatialObject_s00dc_2720* GetLeader();                              // 0x00c00650
};  // namespace SP
}
using SP::Vec3;
using SP::cSpatialObject_s00dc_2720;
using SP::cSpatialSub;
using SP::cLocomotion;
using SP::cCombatant_s00dc_2720;
using SP::cGroup;
using SP::cCommunity_s00dc_2720;
extern const Vec3  g_originThread;                            // 0x0169f444 (x/y/z)
extern const float g_floatMax;                                // 0x0147c300 FLT_MAX
class cGameNounManager_s00dc_2720 {
public:
    cSpatialObject_s00dc_2720* GetAvatar();                              // 0x00b1fdb0
    cCommunity_s00dc_2720*     GetPlayerTribe();                         // 0x00bfc5f0
    void* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);   // 0x00b21340
};
cGameNounManager_s00dc_2720* NounManager();                              // 0x00b3d300
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
    virtual bool FindObjects(const Vec3* pos, float range,
                             eastl::vector_s00dc_2720<EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720> >* results, int zero,
                             void* callback, cSpatialObject_s00dc_2720* who);   // +0x48
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
cSpatialObject_s00dc_2720* CastCreature(void* noun);                     // 0x00ae66f0
cSpatialQuery*  GetSpatialQuery();                            // 0x00b3d240
class cPlanetModel_s00dc_2720 {
public:
    void Project(Vec3* out, const Vec3* in);                  // 0x00b81630
};
cPlanetModel_s00dc_2720* GetPlanetModel();                               // 0x00b3d350
namespace SP {
struct UFO_FOLLOW_AVATAR_memory_block {
    float mMovementTimer;                                     // +0x00
    bool  mbDone;                                             // +0x04
    uint32_t mState;                                          // +0x08
};  // namespace SP
}
using SP::UFO_FOLLOW_AVATAR_memory_block;
enum {
    kGameCreature = 0x1654c01,
    kGameTribe    = 0x1654c02,
};
enum {
    kCreatureAnimalNoun = 0x18eb45e,   // cCreatureAnimal::NOUN_ID
    kUFOFollowTree      = 0x3704748,   // behaviour-tree id already driving the candidate
    kGroupMemberKey     = 0xee9b2232,  // fourcc used by cGroup::FindMember
};
enum {
    kPropTargetDistance = 0x9b0ef346,
    kPropUnused         = 0xa58acb11,
    kPropWanderRadius   = 0x0005f8cc,
    kPropPlanTime       = 0x34e39082,
    kPropSpeed          = 0x829df2e1,
    kPropSearchRange    = 0x9650f75f,
};
// ---- items of slice s00dc2720 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern const Vec3  g_originThread;                            // 0x0169f444 (x/y/z)

// @ 0x00dc2720
namespace SP {
bool UFO_FOLLOW_AVATAR_Tick(cSpatialObject_s00dc_2720* self, cSpatialObject_s00dc_2720* avatar, void* a3, int a4, int a5, UFO_FOLLOW_AVATAR_memory_block* mem, int a6, float dt)
{
    // ---- pick the leader -------------------------------------------------
    cSpatialObject_s00dc_2720* leader;
    int mode = GetCurrentGameMode();
    if (mode == kGameCreature) {
        leader = NounManager()->GetAvatar();
    } else if (mode == kGameTribe) {
        cCommunity_s00dc_2720* tribe = NounManager()->GetPlayerTribe();
        leader = tribe->GetLeader();
        if (leader == 0 || leader->mbDeadB5e) {
            eastl::vector_s00dc_2720<EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720> >* members = tribe->GetMembers();
            for (EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720>* it = members->mpBegin; it != members->mpEnd; ++it) {
                cSpatialObject_s00dc_2720* candidate = it->Get();
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
        cCombatant_s00dc_2720* found = 0;
        if (!bLowState) {
            cCombatant_s00dc_2720* exclude = leader->GetCombatantTarget();
            const Vec3* pos = loco->GetPosition();
            EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720> buffer[32];
            eastl::vector_s00dc_2720<EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720> > hits(buffer, buffer, buffer + 32);
            float rangeSq = speed * speed;
            // 0x00d9a9c0: the per-noun filter callback handed to cSpatialQuery::FindObjects.
            if (GetSpatialQuery()->FindObjects(pos, searchRange, &hits, 0, (void*)0x00d9a9c0, leader)) {
                int count = (int)(hits.mpEnd - hits.mpBegin);
                for (int i = 0; i < count; ++i) {
                    cSpatialObject_s00dc_2720* candidate = CastCreature(hits.mpBegin[i].Get());
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
            hits.~vector_s00dc_2720();
            if (found != 0) {
                cSpatialObject_s00dc_2720* who = found->GetOwnerNoun();
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
