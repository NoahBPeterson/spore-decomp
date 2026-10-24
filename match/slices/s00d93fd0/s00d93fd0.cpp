// Slice s00d93fd0 -- SP::CitizenTree behaviour-tree callbacks (cdecl, citizen-creature first).
//
// Subject is the retail citizen/creature object.  Its locomotion sub-object (cLocomotiveObject) sits
// at +0xc0, its combatant sub-object at +0x120, its behaviour-tree object at +0xb4c, its owner record
// at +0xfb8 and its owning city at +0x1010.  The behaviour tree invokes each callback with the
// creature first and a stimulus list plus an out-flag (plus a context record where used) as the
// trailing cdecl arguments.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same module as the s00d964a0 CitizenTree callbacks).
#include <math.h>
#include <float.h>
#include "types.h"

#define PV(n) virtual void pv##n();

struct Vec3 { float x, y, z; };

// --------------------------------------------------------------------- services / helpers
struct PlanetModel {                      // cPlanetModel singleton
    Vec3* MakeRandomWorldPosition(Vec3* out, const Vec3* center, float minDist, float maxDist); // 0x00b81780
};
PlanetModel* GetPlanetModel();            // 0x00b3d350

Vec3*  GetNearestLaneNode(Vec3* out, void* citizen);      // 0x00d917f0
Vec3*  normalized_safe(Vec3* out, const Vec3* in);         // 0x00449c20

// behaviour-tree stimulus services (cdecl where an explicit this is not the receiver)
int*   StimuliLookup(void* table, void* key);              // 0x00d99420
void*  StimuliResolve(void* v);                            // 0x00d99500

struct Viewer;
class AppObject {                         // returned by App() (0x0067dd10)
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
    PV(15) PV(16) PV(17) PV(18) PV(19)
    virtual void* Slot50();                                // +0x50 (slot 20)
};
class ViewerHolder {                      // returned by AppObject::Slot50()
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
    virtual Viewer* GetViewer_1c();                        // +0x1c (slot 7)
};
class Viewer {
 public:
    void GetCameraLocationInfo(Vec3* out, void* a, void* b, void* c) const;  // 0x007c3d30
};
AppObject* App();                         // 0x0067dd10

// behaviour-tree stimuli objects
class BehaviorStimuli {                   // at creature + 0xb4c + 8
 public:
    void ClearAll(int a, int b);                           // 0x00bc98f0
    void* GetAny();                                        // 0x00d997e0
};
class StimuliTable {                      // at creature + 0xb4c + 0x1d0
 public:
    int* Lookup(void* key);                                // 0x00d99420
};
class StimuliZone {                        // returned by ProfGetZone()
 public:
    bool Find(uint32_t key, int* out, int n);              // 0x00c0dee0
    void SetPos(const Vec3* p);                            // 0x00c15270
};
class StimulusObj {                        // object reached via StimuliLookup()
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    virtual void* Slot5c(uint32_t id);                 // +0x5c (slot 23)
};
void* StimuliCreateEffect(BehaviorStimuli* self, uint32_t a, uint32_t b, float c, int d); // 0x00bc97f0

class Spatial {                           // sub-object vtable at object + 0x34
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();         // +0x2c (slot 11)
};
struct ObjView { uint8_t pad00[0x34]; Spatial mSpatial_34; };

// action-circle / route helpers
class ActionSlot {                         // cActionCircle::tSlot (sizeof 0x18)
 public:
    uint8_t mOccupied;                    // +0x00
    uint8_t mPad01[0x17];                 // +0x01 .. 0x18
    void Clear();                         // 0x00afa0a0
    void Reserve(void* gameData);         // 0x00afa030
};
class ActionCircle {
 public:
    uint8_t  mPad00[0x14];                // +0x00 .. 0x14
    Vec3     mPos_14;                     // +0x14
    uint8_t  mPad20[0x30];                // +0x20 .. 0x50
    ActionSlot* mpBegin_50;               // +0x50
    ActionSlot* mpEnd_54;                 // +0x54
    ActionSlot* SlotAt(uint32_t idx);     // 0x00af9ff0
};
ActionSlot* ActionCircleFindSlot(ActionCircle* circle, const Vec3* p); // 0x00afad70
void  ArtifactSlotClear(void* slot);                       // 0x00dc4c60
struct CityWalls {
    uint8_t  mPad00[0x25c];
    float    mRadius_25c;                                  // +0x25c
    bool     PointInsideInnerWall(const Vec3* p);          // 0x00bec140
};

// --------------------------------------------------------------------- random
namespace EA { namespace Random {
class RandomLinearCongruential { public:
    uint32_t RandomUint32Uniform(uint32_t limit);   // 0x00a68fb0
    double   RandomDoubleUniform();                 // 0x009360d0
};
}}
extern EA::Random::RandomLinearCongruential sMathRandom;   // 0x01601760

namespace SP {

class Citizen;

// --------------------------------------------------------------------- global constants (read from the image)
extern const float kFlTwo;          // 0x01470f1c = 2.0f
extern const float kFlHalf;         // 0x01471064 = 0.5f
extern const float kFlFifteen;      // 0x014007f4 = 15.0f
extern const float kFlSafeEps;      // 0x013ec4b8 = 1e-8f
extern float       gFleeChance;     // 0x01593334 = 0.7f
extern const float kFlOne;          // 0x01485720 = 1.0f
extern const float kFlSix;          // 0x0147b9f0 = 6.0f
extern float       gForcedDeathDistSq;  // 0x0169f204
extern uint32_t    gForcedDeathInit;    // 0x0169f208
extern const float kFlForcedDeathDistSq;// 0x0147c11c = 22500.0f
extern const float kFlThree;        // 0x013eb95c = 3.0f
extern const float kFlThirty;       // 0x014853bc = 30.0f
extern const float kFlFour;         // 0x014853e0 = 4.0f
extern void*       gAnimEventCond;  // 0x01590c54

// --------------------------------------------------------------------- object layouts
class Locomotion {                        // cLocomotiveObject sub-object at creature + 0xc0
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                 // +0x2c (slot 11)
    PV(12) PV(13)
    virtual void SetPosition(const Vec3* p);           // +0x38 (slot 14)
    PV(15) PV(16) PV(17)
    virtual bool Slot48();                             // +0x48 (slot 18)
    PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
    virtual float GetTurnRate();                       // +0x74 (slot 29)

    struct NeighborList { void** mpBegin; void** mpEnd; };   // at +0x278
    NeighborList* GetNeighbors();                      // 0x00c420d0 (returns this + 0x278)
    bool IsNearGoal();                                 // 0x00c42e20
};

class Combatant {                         // cCombatant sub-object at creature + 0x120
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual float GetSize_58();                        // +0x58 (slot 22)
    uint8_t  pad04[0x30];                              // +0x04 .. 0x34
    int      mDamageState_34;                          // +0x34
    float    mHealth_38;                               // +0x38
    uint8_t  pad3c[0x24];                              // +0x3c .. 0x60
    int GetDamageState();                              // 0x008e7f80 (reads [this + 0x34])
};

class City {                              // owning city (creature + 0x1010)
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
    virtual CityWalls* GetWalls();                     // +0x6c (slot 27)
    uint8_t  pad70[0x11c];                             // +0x04 .. 0x120
    Locomotion mCityLoco_120;                          // +0x120
    ActionCircle* GetActions();                        // 0x00bd7f50 (returns this + 0x450)
    ActionCircle* GetRoute3ec();                       // 0x00bd7f40 (returns this + 0x3ec)
    void RouteVec(Vec3* a, Vec3* b);                   // 0x00bd7f70
};

struct Owner {                            // owner record at creature + 0xfb8
    uint8_t  pad00[0x220];
    uint8_t* mpActionPool_220;                         // +0x220 : cActionCircle pool base (stride 0x64)
    uint8_t  pad224[0xa51 - 0x224];
    uint8_t  mbArtifactNotHeld_0a51;                   // +0xa51
    uint8_t  padA52[0x02];
    void*    mpArtifact_0a54;                          // +0xa54 : held artifact (ref-counted)
    uint8_t  padA58[0xaf0 - 0xa58];
    uint8_t* mpZoneData_af0;                           // +0xaf0

    void         EnterZone(Citizen* c);                // 0x00d5c580 (thiscall)
    void         SetFlag(Citizen* c, bool f);          // 0x00d5c470 (thiscall)
    StimuliZone* GetZone(Citizen* c);                  // 0x00d59170 (thiscall)
};

struct BehaviorTree {                      // behaviour-tree object at creature + 0xb4c
    uint8_t  pad00[0x1c8];
    uint32_t mFlags_1c8;                               // +0x1c8
    uint32_t mField_1cc;                               // +0x1cc
};

class Object {                             // ref-counted object
 public:
    PV(0)
    virtual void Release();                            // +0x04 (slot 1)
};

// The creature; sparse retail layout with explicit named gaps.
class Citizen {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
    PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
    PV(43) PV(44) PV(45)
    virtual void* AsInterface_b8(uint32_t id);             // +0xb8 (slot 46)
    uint8_t  pad04[0xc0 - 4];                              // +0x04 .. 0xc0
    Locomotion mLoco;                                  // +0xc0 (vptr only)
    uint8_t  pad12[0x120 - 0xc4];                      // +0xc4 .. 0x120
    Combatant  mCombatant;                             // +0x120 (size 0x60)
    uint8_t  pad18[0x5a8 - 0x180];                     // +0x180 .. 0x5a8
    uint32_t mStimulusPayload_5a8;                     // +0x5a8
    uint8_t  pad5ac[0xb20 - 0x5ac];                    // +0x5ac .. 0xb20
    uint32_t mObjectId_0b20;                           // +0xb20
    uint8_t  pad0b24[0xb4c - 0xb24];                   // +0xb24 .. 0xb4c
    BehaviorTree* mpBehaviorTree_0b4c;                 // +0xb4c
    uint8_t  pad0b50[0xfb8 - 0xb50];                   // +0xb50 .. 0xfb8
    Owner*   mpOwner_0fb8;                             // +0xfb8
    uint8_t  pad0fbc[0xfc4 - 0xfbc];                   // +0xfbc .. 0xfc4
    uint32_t mToolEffectId_fc4;                        // +0xfc4
    void*    mpObject_0x34_hint;                       // (unused; keeps Object view anchored)
    uint8_t  pad0fcc[0x1010 - 0xfcc];                  // +0xfcc .. 0x1010
    City*    mpCity_1010;                              // +0x1010

    City* GetCity();                                   // 0x00c23e40 (returns [this + 0x1010])
    bool  IsValidTarget_c232c0();                      // 0x00c232c0
    void PlayAnimation(uint32_t anim, int a, int b);                           // 0x00c12190
    bool WaitForAnimEventOrEnd(void* cond, int* outId, int a, int b, int c);   // 0x00c14ef0
    void SetCurrentToolEffect(int tool, unsigned int id);                      // 0x00c24f40
    void SetSprinting(bool on);                                               // 0x00c1ad10
    void InterruptAnimation(uint32_t anim, int a, int b);                      // 0x00c12310
    void MoveToPointAndFacingAtSpeed(int mode, const Vec3* pos, const Vec3* facing, float speed, float turn); // 0x00c1c5c0
    void MoveToPointAtSpeed(int mode, const Vec3* pos, float a, float b);      // 0x00c1c1d0
    int  SetToolEffectId(int id) { mToolEffectId_fc4 = id; return mToolEffectId_fc4; }  // 0x00c22830
};

// Argument records
struct RepairState {                       // RepairBuilding_Tick trailing record (arg6)
    uint8_t  mbFlag_0;                     // +0x00
    uint8_t  pad1[0x03];
    int      mSlotA_4;                     // +0x04
    int      mSlotB_8;                     // +0x08
    Citizen* mpTarget_c;                   // +0x0c : target creature
};
#pragma pack(push, 1)
struct FleeContext {                       // FleeNearbyCreature / AttackNearbyCreature arg8
    uint8_t  pad00[0x2d];
    int      mValue_2d;                    // +0x2d (unaligned)
};
#pragma pack(pop)
struct ArtifactState {                     // ArtifactMover_Tick trailing record (arg6)
    Object*  mpArtifact_0;                 // +0x00 : must match owner->mpArtifact_0a54
    int      mPhase_4;                     // +0x04
    Vec3     mRoute_8;                     // +0x08
};

// ----------------------------------------------------------------------------------------------------
namespace CitizenTree {

// @ 0x00d93fd0
bool RepairBuilding_Tick(Citizen* c, int a2, int a3, int a4, int a5, RepairState* st, int a7, int a8)
{
    Citizen* tgt = st->mpTarget_c;
    Combatant* comb = tgt ? &tgt->mCombatant : 0;
    if (comb->GetDamageState() == 2)
        return false;
    if (comb->GetSize_58() == comb->mHealth_38)
        return false;
    if (c->mLoco.IsNearGoal())
    {
        if (st->mbFlag_0)
        {
            st->mbFlag_0 = 0;
            if (sMathRandom.RandomUint32Uniform(10) < 5)
                c->PlayAnimation(0x50f3406, 1, -1);
            else
                c->PlayAnimation(0x50f3407, 1, -1);
            return true;
        }
        int outId;
        if (c->WaitForAnimEventOrEnd(gAnimEventCond, &outId, -1, 0, 0))
        {
            if (outId != -1)
            {
                c->SetCurrentToolEffect(0x13, (unsigned int)c->SetToolEffectId(outId));
                return true;
            }
            ActionCircle* circle = (ActionCircle*)(c->mpOwner_0fb8->mpActionPool_220 + st->mSlotA_4 * 100);
            int count = (int)(circle->mpEnd_54 - circle->mpBegin_50);
            int cur = st->mSlotB_8;
            int next;
            if (sMathRandom.RandomUint32Uniform(10) < 5)
                next = (cur == count - 1) ? 0 : cur + 1;
            else
                next = (cur == 0) ? count - 1 : cur - 1;

            ActionSlot* slot = circle->SlotAt((uint32_t)next);
            if (!slot->mOccupied)
            {
                circle->SlotAt((uint32_t)cur)->Clear();
                slot->Reserve(c);
                st->mSlotB_8 = next;
            }
            const Vec3* here = c->mLoco.GetPosition();
            Vec3 facing;
            facing.x = circle->mPos_14.x - here->x;
            facing.y = circle->mPos_14.y - here->y;
            facing.z = circle->mPos_14.z - here->z;
            c->MoveToPointAndFacingAtSpeed(2, c->mLoco.GetPosition(), &facing, kFlHalf, kFlTwo);
            c->SetCurrentToolEffect(0, 0xffffffff);
            st->mbFlag_0 = 1;
        }
    }
    return true;
}

// @ 0x00d941e0
float OutsideCity_Decide(Citizen* c)
{
    City* city = c->GetCity();
    if (city)
    {
        float wallR = city->GetWalls()->mRadius_25c;
        const Vec3* cp = city->mCityLoco_120.GetPosition();
        const Vec3* mp = c->mLoco.GetPosition();
        float dx = mp->x - cp->x;
        float dy = mp->y - cp->y;
        float dz = mp->z - cp->z;
        float dist = sqrtf((dx * dx + dz * dz) + dy * dy);
        if (dist > wallR)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00d94260
bool HostileAlien_Activate(Citizen* c, int a2, int a3, int a4, int a5, uint8_t* out)
{
    City* city = c->GetCity();
    Vec3 start = *c->mLoco.GetPosition();
    if (city->GetWalls()->PointInsideInnerWall(&start))
        GetNearestLaneNode(&start, c);
    const Vec3* cp = city->mCityLoco_120.GetPosition();
    Vec3 d;
    d.x = cp->x - start.x;
    d.y = cp->y - start.y;
    d.z = cp->z - start.z;
    Vec3 facing;
    normalized_safe(&facing, &d);
    c->MoveToPointAndFacingAtSpeed(2, &start, &facing, kFlOne, kFlTwo);
    *out = 1;
    return true;
}

// @ 0x00d943b0
float AttackNearbyTribe_Decide(Citizen* c, int a2, int a3, int a4, void* stimuli, uint8_t* out)
{
    Locomotion::NeighborList* list = c->mLoco.GetNeighbors();
    void** it = list->mpBegin;
    void** end = list->mpEnd;
    if (it == end)
        return 0.0f;
    do
    {
        Citizen* candidate = (Citizen*)*it;
        if (candidate)
        {
            Citizen* obj = (Citizen*)candidate->AsInterface_b8(0x4f176642);
            if (obj && obj->IsValidTarget_c232c0() && c->mObjectId_0b20 != obj->mObjectId_0b20)
            {
                if (stimuli)
                    ((BehaviorStimuli*)stimuli)->GetAny();
                void* payload = &obj->mStimulusPayload_5a8;
                *(void**)((char*)stimuli + 4) = payload;
                *out = 1;
                return 1.0f;
            }
        }
        ++it;
    } while (it != end);
    return 0.0f;
}

// @ 0x00d94440
float DetectNearbyCreature_Decide(Citizen* c, int a2, int a3, int a4, void* stimuli, uint8_t* out)
{
    Locomotion::NeighborList* list = c->mLoco.GetNeighbors();
    void** it = list->mpBegin;
    void** end = list->mpEnd;
    if (it == end)
        return 0.0f;
    do
    {
        Citizen* candidate = (Citizen*)*it;
        if (candidate)
        {
            Citizen* obj = (Citizen*)candidate->AsInterface_b8(0xd0036e08);
            if (obj && c->mObjectId_0b20 != obj->mObjectId_0b20)
            {
                if (stimuli)
                    ((BehaviorStimuli*)stimuli)->GetAny();
                void* payload = &obj->mStimulusPayload_5a8;
                *(void**)((char*)stimuli + 4) = payload;
                *out = 1;
                return 1.0f;
            }
        }
        ++it;
    } while (it != end);
    return 0.0f;
}

// @ 0x00d944c0  SP::CitizenTree::FleeNearbyCreature_Decide
float FleeNearbyCreature_Decide(Citizen* c, int a2, int a3, int a4, int a5, int a6, int a7, FleeContext* ctx)
{
    BehaviorTree* tree = c->mpBehaviorTree_0b4c;
    int* slot = StimuliLookup((char*)tree + 0x1d0, (void*)ctx->mValue_2d);
    StimulusObj* so = slot ? (StimulusObj*)slot[0] : 0;
    void* obj = so ? so->Slot5c(0xce9f6639) : 0;
    Citizen* found = (Citizen*)StimuliResolve(obj);
    if (found)
    {
        if (sMathRandom.RandomDoubleUniform() < gFleeChance)
        {
            void* e = StimuliCreateEffect((BehaviorStimuli*)((char*)tree + 8), 4, 0, kFlThirty, 0);
            if (e)
            {
                const Vec3* p = found->mLoco.GetPosition();
                *(float*)((char*)e + 0xc) = p->x;
                *(float*)((char*)e + 0x10) = p->y;
                *(float*)((char*)e + 0x14) = p->z;
                *(float*)((char*)e + 0x18) = kFlThirty;
                *(int*)((char*)e + 0x1c) = -1;
                return 1.0f;
            }
        }
    }
    return 0.0f;
}

// @ 0x00d94590
float AttackNearbyCreature_Decide(Citizen* c, int a2, int a3, int a4, void* stimuli, uint8_t* out, int a7, FleeContext* ctx)
{
    BehaviorTree* tree = c->mpBehaviorTree_0b4c;
    int* slot = StimuliLookup((char*)tree + 0x1d0, (void*)ctx->mValue_2d);
    StimulusObj* so = slot ? (StimulusObj*)slot[0] : 0;
    void* obj = so ? so->Slot5c(0xce9f6639) : 0;
    Citizen* found = (Citizen*)StimuliResolve(obj);
    if (found)
    {
        if (stimuli)
            ((BehaviorStimuli*)stimuli)->GetAny();
        void* payload = &found->mStimulusPayload_5a8;
        *out = 1;
        *(void**)((char*)stimuli + 4) = payload;
        return 1.0f;
    }
    return 0.0f;
}

// @ 0x00d94610
float ForcedDeath_Decide(Citizen* c)
{
    if (c->mLoco.Slot48())
        return 0.0f;
    AppObject* app = App();
    ViewerHolder* vh = (ViewerHolder*)app->Slot50();
    Viewer* viewer = vh->GetViewer_1c();
    Vec3 cam;
    viewer->GetCameraLocationInfo(&cam, 0, 0, 0);
    if (!(gForcedDeathInit & 1))
    {
        gForcedDeathInit |= 1;
        gForcedDeathDistSq = kFlForcedDeathDistSq;
    }
    const Vec3* mp = c->mLoco.GetPosition();
    float dx = cam.x - mp->x;
    float dy = cam.y - mp->y;
    float dz = cam.z - mp->z;
    float d2 = (dz * dz + dy * dy) + dx * dx;
    if (d2 > gForcedDeathDistSq)
        return 1.0f;
    return 0.0f;
}

// @ 0x00d946e0
float ArtifactHeld_Decide(Citizen* c)
{
    Owner* o = c->mpOwner_0fb8;
    if (o && !o->mbArtifactNotHeld_0a51 && o->mpArtifact_0a54)
        return 1.0f;
    return 0.0f;
}

// @ 0x00d94710
bool ArtifactMover_Tick(Citizen* c, int a2, int a3, int a4, int a5, ArtifactState* st, int a7, int a8)
{
    Owner* owner = c->mpOwner_0fb8;
    if (st->mpArtifact_0 != (Object*)owner->mpArtifact_0a54)
        return false;

    if (st->mPhase_4 == 1)
    {
        if (c->mLoco.IsNearGoal())
        {
            ActionSlot* slot = ActionCircleFindSlot(c->GetCity()->GetActions(), &st->mRoute_8);
            if (slot)
            {
                Object* art = st->mpArtifact_0;
                (*(void(**)(void*, const Vec3*))(*(uint32_t*)((char*)art + 0x34) + 0x38))((char*)art + 0x34, &st->mRoute_8);
                slot->Reserve(art);
            }
            Object* old = st->mpArtifact_0;
            st->mpArtifact_0 = 0;
            if (old)
                old->Release();
            Object* old2 = (Object*)c->mpOwner_0fb8->mpArtifact_0a54;
            c->mpOwner_0fb8->mpArtifact_0a54 = 0;
            if (old2)
                old2->Release();
            return false;
        }
        const Vec3* p1 = c->mLoco.GetPosition();
        Vec3 base = *p1;
        Object* art = st->mpArtifact_0;
        const Vec3* p2 = (*(const Vec3*(**)(void*))(*(uint32_t*)((char*)art + 0x34) + 0x2c))((char*)art + 0x34);
        Vec3 d;
        d.x = p2->x - base.x;
        d.y = p2->y - base.y;
        d.z = p2->z - base.z;
        float turn = (*(float(**)(void*))(*(uint32_t*)((char*)art + 0x34) + 0x74))((char*)art + 0x34);
        float scale = turn + kFlOne;
        Vec3 n;
        normalized_safe(&n, &d);
        Vec3 target;
        target.x = n.x * scale + base.x;
        target.y = n.y * scale + base.y;
        target.z = n.z * scale + base.z;
        (*(void(**)(void*, const Vec3*))(*(uint32_t*)((char*)art + 0x34) + 0x38))((char*)art + 0x34, &target);
        return true;
    }
    if (st->mPhase_4 == 0)
    {
        if (!c->mLoco.IsNearGoal())
            return true;
        c->GetCity()->GetWalls();
        const Vec3* mp = c->mLoco.GetPosition();
        Vec3 pos = *mp;
        ActionSlot* slot = ActionCircleFindSlot(c->GetCity()->GetActions(), &pos);
        if (!slot)
        {
            ArtifactSlotClear(&c->mpOwner_0fb8->mpArtifact_0a54);
            return false;
        }
        st->mRoute_8 = *(Vec3*)((char*)slot + 0xc);
        c->SetSprinting(false);
        c->MoveToPointAtSpeed(2, &st->mRoute_8, kFlOne, kFlTwo);
        st->mPhase_4 = 1;
    }
    return true;
}

// @ 0x00d949a0
bool ArtifactSeek_Activate(Citizen* c, int a2, int a3, int a4, int a5, uint8_t* out)
{
    if (out)
        *out = 0;
    Vec3 lane;
    GetNearestLaneNode(&lane, c);
    const Vec3* mp = c->mLoco.GetPosition();
    if (lane.x == mp->x && lane.y == mp->y && lane.z == mp->z)
        GetPlanetModel()->MakeRandomWorldPosition(&lane, c->mLoco.GetPosition(), kFlTwo, kFlFour);
    Vec3 rnd;
    GetPlanetModel()->MakeRandomWorldPosition(&rnd, &lane, 0.0f, kFlFifteen);
    lane = rnd;
    c->InterruptAnimation(0x2481db0, -1, 0);
    City* city = c->GetCity();
    const Vec3* cp = city->mCityLoco_120.GetPosition();
    Vec3 facing;
    facing.x = cp->x - lane.x;
    facing.y = cp->y - lane.y;
    facing.z = cp->z - lane.z;
    Vec3 d;
    normalized_safe(&d, &facing);
    c->MoveToPointAndFacingAtSpeed(2, &lane, &d, kFlOne, kFlSix);
    return true;
}

// @ 0x00d94b60
bool WanderFlee_Activate(Citizen* c, int a2, int a3, int a4, int a5, uint8_t* out)
{
    if (out)
    {
        *out = 0;
        *(float*)(out + 4) = 0.0f;
    }
    City* city = c->GetCity();
    Vec3 routeB, routeA;
    city->RouteVec(&routeB, &routeA);
    ActionCircle* circle = city->GetRoute3ec();
    const Vec3* mp = c->mLoco.GetPosition();
    ActionSlot* slot = ActionCircleFindSlot(circle, mp);
    Vec3 pt;
    if (slot)
        pt = *(Vec3*)((char*)slot + 0xc);
    else
        pt = routeA;
    float maxD = routeB.z - c->mLoco.GetTurnRate();
    Vec3 rnd;
    GetPlanetModel()->MakeRandomWorldPosition(&rnd, &pt, 0.0f, maxD);
    c->MoveToPointAtSpeed(2, &rnd, kFlOne, kFlThree);
    return true;
}

// ----------------------------------------------------------------------------------------------------
// Shared helper: nearest object of a list matching a predicate (kept file-local).
// @ 0x00d94c60
void* FindNearestObj(void** vec, const Vec3* p, bool (*pred)(void*))
{
    void** begin = (void**)vec[0];
    void** end = (void**)vec[1];
    void* best = 0;
    float bestD = FLT_MAX;
    if (begin == end)
        return 0;
    do
    {
        void* o = *begin;
        if (pred(o))
        {
            const Vec3* op = ((ObjView*)o)->mSpatial_34.GetPosition();
            float dx = op->x - p->x;
            float dy = op->y - p->y;
            float dz = op->z - p->z;
            float d = (dx * dx + dz * dz) + dy * dy;
            if (d < bestD)
            {
                bestD = d;
                best = o;
            }
        }
        ++begin;
    } while (begin != end);
    return best;
}

// @ 0x00d94d10
void* FindNearestObjCitizen(void** vec, const Vec3* p, bool (*pred)(void*))
{
    void** begin = (void**)vec[0];
    void** end = (void**)vec[1];
    void* best = 0;
    float bestD = FLT_MAX;
    if (begin == end)
        return 0;
    do
    {
        Citizen* o = (Citizen*)*begin;
        if (pred(o ? &o->mCombatant : 0))
        {
            const Vec3* op = ((ObjView*)o)->mSpatial_34.GetPosition();
            float dx = op->x - p->x;
            float dy = op->y - p->y;
            float dz = op->z - p->z;
            float d = (dx * dx + dz * dz) + dy * dy;
            if (d < bestD)
            {
                bestD = d;
                best = o;
            }
        }
        ++begin;
    } while (begin != end);
    return best;
}

// @ 0x00d94dd0
bool ProfZone_Tick(Citizen* c, int a2, int a3, uint32_t flags)
{
    BehaviorTree* tree = c->mpBehaviorTree_0b4c;
    if (tree->mFlags_1c8 & 0x8000)
    {
        ((BehaviorStimuli*)((char*)c->mpBehaviorTree_0b4c + 8))->ClearAll(0x8000, 0);
        ((BehaviorStimuli*)((char*)c->mpBehaviorTree_0b4c + 8))->ClearAll(0x800, 0);
        c->mpOwner_0fb8->EnterZone(c);
        c->mpOwner_0fb8->SetFlag(c, (flags & 0x801) != 0);
        return true;
    }
    if (tree->mFlags_1c8 & 0x800)
        return false;
    StimuliZone* zone = c->mpOwner_0fb8->GetZone(c);
    if (zone)
    {
        int id = -1;
        if (zone->Find(0x6d30dd42, &id, 1))
        {
            uint8_t* zd = c->mpOwner_0fb8->mpZoneData_af0;
            Vec3 v = *(Vec3*)(zd + 0x7d8);
            zone->SetPos(&v);
        }
        if (zone->Find(0x6d30dd41, &id, 1))
        {
            uint8_t* zd = c->mpOwner_0fb8->mpZoneData_af0;
            Vec3 v = *(Vec3*)(zd + 0x7e4);
            zone->SetPos(&v);
        }
    }
    return true;
}

}  // namespace CitizenTree
}  // namespace SP