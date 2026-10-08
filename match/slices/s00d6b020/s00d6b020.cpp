// Slice s00d6b020 -- SP::FLEE_Tick (0x00d6b020, 6703 bytes, /O2 /arch:SSE /fp:fast, __cdecl, returns bool).
//
// Per-tick behaviour of a creature in the "flee" behaviour-tree node.  The arguments are
// (creature, ?, ?, flags, flags2, FleeState*, ?, dt): flags bit 0x100000 = "may run to a hiding
// spot", 0x2000000 / flags2 bit 0 pick the flee-distance tuning property, flags bit 25 is passed to
// FreakOut.  The state block *st drives a small state machine (st->mState):
//   0 waiting for the pre-flee animation, 1 running away, 2 waiting for the interrupt animation,
//   3 fleeing (pick a direction away from the threat), 4 jump-start, 5 landed, 6 cornered/hover,
//   7 running to a hiding spot.
// The threat is the "owner" of the creature's target object; the flee direction is built from
// tuning properties (GetPropertyT<float>) and neighbours.  After the switch the tick publishes
// speed-modifier 2 (st->mTimer2 > 0) and returns true; the early exits return false.
//
// Every callee's convention was taken from its call site, and the stack arguments were re-derived
// from the asm (not from the decompile): pushes made long before a call can belong to a later
// cdecl call (the push 1 / float / vector pushes before the two GetFootprintRadius virtual calls
// feed FUN_00d99a60, the pushes before FUN_00c42de0 feed TryJumpToTarget, the two stack slots
// after FUN_00d99e20 are reused as MoveToPointAtSpeed's float arguments).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
//
// @ 0x00d6b020
#include "types.h"
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

namespace SP {

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

class cSPCreatureBase;

// ---- objects reached through virtual calls --------------------------------------------------------
struct Avatar;

struct ThreatOwner {                                   // the "owner" of the target object
    PV PV PV PV PV PV PV PV PV PV PV                   // 0x00 .. 0x28
    virtual Vec3* GetPosition();                       // +0x2c
    PV8 PV2                                            // 0x30 .. 0x54
    virtual bool IsPlayerOwned();                      // +0x58
    PV4 PV2                                            // 0x5c .. 0x70
    virtual float GetFootprintRadius();                // +0x74
    PV8 PV8                                            // 0x78 .. 0xb4
    virtual void* Cast(uint32_t type);                 // +0xb8
};

struct TargetRef {                                     // result of cSPCreatureBase::GetTargetObj
    PV PV
    virtual ThreatOwner* GetOwner();                   // +0x08
};

struct LocoState {
    uint32_t pad[0x14 / 4];
    Vec3 mV14;                                         // +0x14
    uint32_t pad20[(0x5c - 0x20) / 4];
    int mHasPath;                                      // +0x5c
};

struct Loco {                                          // sub-object at creature+0xc0 (own vtable)
    PV8 PV2 PV                                         // 0x00 .. 0x28
    virtual Vec3* GetPosition();                       // +0x2c
    virtual Quat* GetOrientation();                    // +0x30
    PV4 PV                                             // 0x34 .. 0x44
    virtual bool IsOnView();                           // +0x48
    PV4                                                // 0x4c .. 0x58
    virtual Vec3* GetDirection(Vec3* out);             // +0x5c
    PV4 PV                                             // 0x60 .. 0x70
    virtual float GetFootprintRadius();                // +0x74
    bool IsNearGoal();                                 // 0x00c42e20
    Vec3* FUN_00c42de0();                              // 0x00c42de0
    LocoState* GetState();                             // 0x00c41ec0
};

struct Avatar {                                        // GetAvatar() result
    uint32_t pad[0xc0 / 4];
    Loco mLoco;                                        // +0xc0
};

struct cGameNounManager {
    Avatar* GetAvatar();                               // 0x00b1fdb0
};

struct cSPDramaManager {
    bool IsDramaEventActive(int type);                 // 0x00d4cb30
};

struct cViewer {
    void GetCameraLocationInfo(Vec3* pos, Vec3* dir, Vec3* a, Vec3* b);   // 0x007c3d30
};
struct cApp {
    PV8 PV8 PV4 PV2                                    // 0x00 .. 0x54
    virtual cViewer* GetViewer();                      // +0x58
};

struct RandomLCG {                                     // EA::Random::RandomLinearCongruential
    uint32_t RandomUint32Uniform(uint32_t limit);      // 0x00a68fb0
    double RandomDoubleUniform();                      // 0x009360d0
};

// ---- tuning / strategy ----------------------------------------------------------------------------
struct CreatureModeStrategy {
    uint32_t pad[0xb4 / 4];
    void* mProperties;                                 // +0xb4
};

// ---- creature internals ---------------------------------------------------------------------------
struct BehStim {                                       // creature->mBehav + 8
    void FUN_00bc97f0(uint32_t lo, uint32_t hi, float f, cSPCreatureBase* ref);   // ret 0x10
};
struct Behav {
    uint32_t pad0[2];
    uint32_t pad1[(0x1d8 - 8) / 4];
    uint32_t m1d8;                                     // +0x1d8
};

struct Holder {                                        // element of the creature lists
    uint32_t pad0[2];
    cSPCreatureBase* mCreature;                        // +0x08
};
struct NearEntry {                                     // element of the list at creature+0x1124 (via filter)
    float mDistance;                                   // +0x00
    uint32_t pad04;
    cSPCreatureBase* mCreature;                        // +0x08
};
struct HomeObj {
    Vec3* FUN_00c6acc0();                              // 0x00c6acc0
};
struct SpotObj {
    uint32_t pad[0x5c / 4];
    Vec3 mPos;                                         // +0x5c
    float FUN_00aff550();                              // 0x00aff550
};
struct SpotEntry {
    uint32_t pad[3];
    SpotObj* mObj;                                     // +0x0c
};

struct Pred {                                          // stateless filter functor (0x00c02600)
    bool Test(NearEntry* e);                           // 0x00c02600 (thiscall ret 4)
};
struct FilterRange {                                   // 0x00b41a40 / 0x00b3d850
    NearEntry** mpCur;
    NearEntry** mpEnd;
    Pred mPred;
    FilterRange* FUN_00b41a40(void* container, bool* unused);   // ret 8
    void Advance();                                    // 0x00b3d850
};

struct ObjInfo {
    uint32_t pad[0x7c / 4];
    int m7c;                                           // +0x7c
};

struct GroupObj {
    uint32_t pad[0x58c / 4];
    float mF58c;                                       // +0x58c
};

struct OwnerCastObj {                                  // owner->Cast(0xb033b403) result
    uint32_t pad[0x714 / 4];
    int m714;                                          // +0x714
};

class cSPCreatureBase {
public:
    PV PV PV
    virtual cSPCreatureBase* Cast(uint32_t type);      // +0x0c
    PV8 PV8 PV8 PV4 PV                                 // 0x10 .. 0x80
    virtual void SetTarget(void* obj, int a, int b);   // +0x84
    PV8 PV2 PV                                         // 0x88 .. 0xb0
    virtual ObjInfo* GetObjectById(int id);            // +0xb4
    PV PV                                              // 0xb8 0xbc
    virtual bool CanReach(cSPCreatureBase* o, float a, float b);   // +0xc0

    uint32_t padc4[(0xc0 - 4) / 4];
    Loco mLoco;                                        // +0xc0
    uint32_t padc4b[(0xb20 - 0xc4) / 4];
    GroupObj* mGroup;                                  // +0xb20
    uint32_t padb24[(0xb4c - 0xb24) / 4];
    Behav* mBehav;                                     // +0xb4c
    uint32_t padb50[(0xb58 - 0xb50) / 4];
    uint32_t mFlags;                                   // +0xb58
    uint8_t mScared;                                   // +0xb5c
    uint8_t padb5d;
    uint8_t mDead;                                     // +0xb5e
    uint8_t padb5f[(0xe7c - 0xb5f)];
    uint32_t padE7c;                                   // +0xe7c (target ref)
    uint8_t pade80[(0xf90 - 0xe80)];
    uint8_t mF90;                                      // +0xf90
    uint8_t padf91[(0x108c - 0xf91)];
    SpotEntry** mSpotsBegin;                           // +0x108c
    SpotEntry** mSpotsEnd;                             // +0x1090
    uint8_t pad1094[(0x1124 - 0x1094)];
    NearEntry** mNearBegin;                            // +0x1124
    NearEntry** mNearEnd;                              // +0x1128

    TargetRef* GetTargetObj();                         // 0x00c0ee60
    cSPCreatureBase* GetTargetAsCreature();            // 0x00c0ee70
    bool FUN_00c0c130();
    bool FUN_00c0c0e0();                               // "cCreatureBase" (+0xe84 flag test)
    uint32_t FUN_00c0cdb0();
    int FUN_00c0b750();
    void* FUN_00c04750();
    int FUN_00c0f570();
    int FUN_00c0c140();
    bool FUN_00c11480(const Vec3* p, float a, float b);          // ret 12
    bool FUN_00c0d560(cSPCreatureBase* t, float a, float b);     // ret 12
    int FUN_00c12410(uint32_t* mask, float range, int a, int b, int c, int d, int e);   // ret 28
    void InterruptAnimation(int id, int a, int b);               // 0x00c12310 (ret 12)
    int PlayAnimation(int id, int a, int b);                     // 0x00c12190 (ret 12)
    bool FUN_00c0e0c0(int id);                                   // ret 4
    bool AnimationFinished(int id);                              // 0x00c12400
    bool AnimationFinished2(int id);                             // 0x00c123f0
    bool WaitForAnimEventOrEnd(int id, float* out, int a, int b, int c);   // 0x00c14ef0 (ret 20)
    void SetStealthed(int a, int b);                             // 0x00c1aed0 (ret 8)
    bool Hover(int on);                                          // 0x00c13a30 (ret 4)
    void FUN_00c19940(int a);                                    // ret 4
    void FUN_00c0cff0(int a);                                    // ret 4
    void FUN_00c0d0c0(uint32_t idx, bool on);                    // ret 8
    void MoveToPointAndFacingAtSpeed(int a, const Vec3* p, const Vec3* facing, float s0, float s1);   // 0x00c1c5c0 (ret 20)
    void MoveToPointAtSpeed(int a, const Vec3* p, float s0, float s1);                              // 0x00c1c1d0 (ret 16)
    void TryJumpToTarget(int a, const Vec3* p, const Vec3* q, float f, int b);                     // 0x00c190e0 (ret 20)
    HomeObj* FUN_00c04590();                                     // helper object (ptr at +0x1674)
};

struct FleeState {
    int mState;        // +0x00
    float mTimer1;     // +0x04
    float mTimer2;     // +0x08
    float mTimer3;     // +0x0c
    float mTimer4;     // +0x10
    bool mB14;         // +0x14
    bool mB15;         // +0x15
    uint16_t pad16;
    int mFreakOut;     // +0x18
    float mTimer5;     // +0x1c
    Vec3 mVec;         // +0x20
    float mF2c;        // +0x2c
    int mAnim;         // +0x30
};

class cPlanetModel {
public:
    void FUN_00b81630(Vec3* out, const Vec3* in);                // ret 8 (position -> direction)
    void DirectionToSurfacePosition(Vec3* out, const Vec3* in);  // 0x00b815a0, ret 8
};

bool FLEE_Tick(cSPCreatureBase* self, int, int, unsigned flags4, unsigned flags5, FleeState* st, int, float dt);

// ---- free functions (all cdecl, arguments checked at the call sites) -------------------------------
cSPCreatureBase* FUN_00d99470(cSPCreatureBase* c);
cSPDramaManager* FUN_00d51660();                                // drama manager singleton
cGameNounManager* NounManager();                                // 0x00b3d300
float GetPropertyT_float(void* props, uint32_t hash, float def);   // 0x004e1c70
float FUN_00d38a30(int which, cSPCreatureBase* c);
cPlanetModel* PlanetModel();                                    // 0x00b3d350
float FUN_00d99a60(Vec3* a, float ra, Vec3* b, float rb, bool clamp);
void* GetCurrentGameMode();                                     // 0x00b5b800
void PlayScaredAnimation(cSPCreatureBase* c, ThreatOwner* owner, int* slot);   // 0x00d6ab00
int FreakOut(cSPCreatureBase* c, int flag);                     // 0x00d6aa30
Vec3* Vector3_Normalize(Vec3* out, const Vec3* in);             // 0x00436ce0
Vec3* normalized_safe(Vec3* out, const Vec3* in);               // 0x00449c20
char Vector3Equal(const Vec3* a, const Vec3* b);                // 0x004232c0
void FUN_00d99e20(Vec3* pos, Vec3* inout);
Vec3* FUN_0059aed0(Vec3* out, const Vec3* v, const Quat* q);
float FUN_00572a60(float a);
void FUN_00576b00(float* mat9, const Vec3* axis, float angle);
cApp* App();                                                    // 0x0067dd10
cSPCreatureBase* interface_cast_animal(cSPCreatureBase* c);     // 0x00ac8960

}  // namespace SP

extern SP::CreatureModeStrategy* gCreatureModeStrategy;        // 0x0169e294
extern SP::RandomLCG sMathRandom;                              // 0x01601760
extern char DAT_01654c10;                                      // game-mode object
extern SP::Vec3 DAT_0169ed0c;
extern SP::Vec3 DAT_0169ed58;
extern float DAT_01582e18;
extern float DAT_01582e08;
extern float DAT_01583f98;

namespace {
inline const float& MinRef(const float& a, const float& b) { return (a > b) ? b : a; }
inline const float& MaxRef(const float& a, const float& b) { return (a > b) ? a : b; }

// DirectionToSurfacePosition + FUN_00d99e20 + MoveToPointAtSpeed(2, p, 1.0, 2.0)
__forceinline void RunTo(SP::cSPCreatureBase* self, SP::Vec3* myPos, const SP::Vec3& dirPoint)
{
    SP::Vec3 surf;
    SP::PlanetModel()->DirectionToSurfacePosition(&surf, &dirPoint);
    SP::FUN_00d99e20(myPos, &surf);
    self->MoveToPointAtSpeed(2, &surf, 1.0f, 2.0f);
}
}

using namespace SP;

// @ 0x00d6b020
bool SP::FLEE_Tick(cSPCreatureBase* self, int, int, unsigned flags4, unsigned flags5, FleeState* st,
                   int, float dt)
{
    TargetRef* tgtObj = self->GetTargetObj();
    cSPCreatureBase* tgt = self->GetTargetAsCreature();
    if (!tgtObj)
        return false;
    if (tgt) {
        if (!FUN_00d99470(tgt))
            return false;
        if (tgt->FUN_00c0c130()) {
            ((BehStim*)((char*)self->mBehav + 8))->FUN_00bc97f0(0x1000000, 0, 10.0f, tgt);
            return false;
        }
    }

    unsigned dramaFlag = flags5 & 1;
    if (dramaFlag) {
        if (!FUN_00d51660()->IsDramaEventActive(3))
            return false;
    }

    if ((self->mFlags >> 8) & 1) {
        Avatar* avatar = NounManager()->GetAvatar();
        if (avatar) {
            Vec3* p = self->mLoco.GetPosition();
            Vec3* q = avatar->mLoco.GetPosition();
            float dx = q->x - p->x;
            float dy = q->y - p->y;
            float dz = q->z - p->z;
            float lim = DAT_01582e18 + DAT_01582e08;
            if (!(lim * lim > ((dx * dx + dy * dy) + dz * dz)))
                return false;
        }
    }

    cSPCreatureBase* animal = tgt ? tgt->Cast(0xd0036e08) : 0;
    ThreatOwner* owner = tgtObj->GetOwner();
    OwnerCastObj* ownerCast = owner ? (OwnerCastObj*)owner->Cast(0xb033b403) : 0;
    bool scaredOrCaster = owner->IsPlayerOwned() || ownerCast != 0;

    void* props = gCreatureModeStrategy->mProperties;
    uint32_t fleeHash;
    if (flags4 & 0x2000000)
        fleeHash = 0x1eb2ca6d;
    else if (dramaFlag)
        fleeHash = 0xd6379aa9;
    else
        fleeHash = 0x679d56bb;
    float fleeDist = GetPropertyT_float(props, fleeHash, 50.0f);
    float restTime = GetPropertyT_float(props, 0x6a3e31f9, 5.0f);
    float margin = GetPropertyT_float(props, 0x322d5dd6, 0.25f);
    float scaredTime = GetPropertyT_float(props, 0x45ee098c, 3.0f);
    GetPropertyT_float(props, 0x35cd8f0c, 30.0f);
    float hideTime = GetPropertyT_float(props, 0x3d3e2988, 10.0f);
    float hideTime2 = GetPropertyT_float(props, 0x2eba30a8, 10.0f);
    float timerLimit = GetPropertyT_float(props, 0x3757372c, 10.0f);
    float timerReset = GetPropertyT_float(props, 0x9c2ad71b, 5.0f);
    float jumpTime = GetPropertyT_float(props, 0x82fb1acc, 5.0f);
    float randDist = FUN_00d38a30(5, self);
    float speedScale = FUN_00d38a30(3, self);
    float stopDist = MinRef(speedScale, fleeDist);
    float neighbourWeight = GetPropertyT_float(props, 0xbd82fae8, 0.5f);
    float dirScale = GetPropertyT_float(props, 0x8836316c, 1.0f);
    float viewWeight = GetPropertyT_float(props, 0x82e52579, 1.0f);
    float friendWeight = GetPropertyT_float(props, 0x5be9d5f9, 1.0f);

    Loco* loco = &self->mLoco;
    Vec3* myPos = loco->GetPosition();
    Vec3* ownerPos = owner->GetPosition();
    Vec3 ownerDir;
    PlanetModel()->FUN_00b81630(&ownerDir, ownerPos);
    float ownerRadius = owner->GetFootprintRadius();
    float dist = FUN_00d99a60(myPos, loco->GetFootprintRadius(), &ownerDir, ownerRadius, true);
    float scale1 = FUN_00d38a30(1, self);
    float scale2 = FUN_00d38a30(2, self);

    bool nearEnough;
    if (!tgt) {
        nearEnough = self->FUN_00c11480(&ownerDir, dist, scale2);
    } else {
        nearEnough = self->FUN_00c0d560(tgt, scale1, dist) || self->CanReach(tgt, scale2, dist);
    }

    uint32_t selfCount = self->FUN_00c0cdb0();
    if (tgt) {
        uint32_t tgtCount = tgt->FUN_00c0cdb0();
        if (st->mState != 1 && !(tgtCount < selfCount) && dist < fleeDist && self->FUN_00c0b750() > 1) {
            if (timerLimit <= st->mTimer3) {
                st->mTimer2 = timerReset;
                st->mTimer3 = 0.0f;
            }
            st->mTimer3 = st->mTimer3 + dt;
        }
    }
    st->mTimer1 = st->mTimer1 - dt;
    st->mTimer2 = st->mTimer2 - dt;

    if (GetCurrentGameMode() == &DAT_01654c10 && self->FUN_00c04750() != 0 &&
        *(int*)((char*)self->FUN_00c04750() + 0x4b8) == 1) {
        PlayScaredAnimation(self, owner, &st->mFreakOut);
        if (0.0f < st->mTimer1)
            return true;
        if (self->FUN_00c0f570() < 1)
            return false;
        self->InterruptAnimation(0x3a74a08, -1, 0);
        st->mState = 2;
        return false;
    }

    bool hasTimer = st->mTimer2 > 0.0f;
    st->mB15 = hasTimer;
    bool waitOk = !hasTimer || selfCount != 0;
    unsigned freakFlag = (flags4 >> 25) & 1;

    if (st->mAnim == 0 && (flags4 & 0x100000) && scaredOrCaster && nearEnough && !hasTimer && animal &&
        !dramaFlag && st->mState != 5 && st->mState != 1 && st->mState != 7) {
        uint32_t mask[3];
        mask[0] = 0; mask[1] = 0; mask[2] = 0;
        uint32_t i = 0;
        do {
            mask[i] = ~mask[i];
            i = i + 1;
        } while (i < 3);
        mask[2] &= 0xffffff;
        if (animal->FUN_00c0c0e0())
            mask[0] &= 0x7fffffff;
        int id = self->FUN_00c12410(mask, dist + margin, 0, 0, 0, 0, 0);
        if (id != -1 && animal->GetObjectById(id)->m7c != 1) {
            st->mTimer1 = scaredTime;
            st->mState = 4;
            if (st->mB14)
                st->mFreakOut = FreakOut(self, freakFlag);
        }
    }

    // ---- keep-fleeing decision ----
    bool scaredOn;
    if (!(dist >= fleeDist)) {
        scaredOn = (st->mState == 6 || st->mState == 1);
    } else if (st->mState == 6) {
        scaredOn = true;
    } else {
        if (st->mState != 1 && st->mState != 7) {
            bool goOn = true;
            if (dramaFlag) {
                FilterRange range;
                range.FUN_00b41a40(&self->mNearBegin, &waitOk);
                if (range.mpCur != range.mpEnd) {
                    do {
                        NearEntry* e = *range.mpCur;
                        if (e->mDistance < fleeDist) {
                            cSPCreatureBase* c = e->mCreature;
                            if (c != self->GetTargetAsCreature() && !c->mDead) {
                                self->SetTarget(c ? (void*)((char*)c + 0x5a8) : 0, 0, 0);
                                st->mState = 0;
                                goOn = false;
                            }
                        }
                        range.Advance();
                    } while (range.mpCur != range.mpEnd);
                }
            }
            if (goOn) {
                st->mTimer1 = hideTime;
                st->mState = 6;
                Vec3 myDir;
                PlanetModel()->FUN_00b81630(&myDir, myPos);
                Vec3 diff;
                diff.x = ownerDir.x - myDir.x;
                diff.y = ownerDir.y - myDir.y;
                diff.z = ownerDir.z - myDir.z;
                Vec3 facing;
                self->MoveToPointAndFacingAtSpeed(2, &myDir, Vector3_Normalize(&facing, &diff), 1.0f, 2.0f);
            }
        }
        scaredOn = (st->mState == 6 || st->mState == 1);
    }
    self->mScared = scaredOn;

    switch (st->mState) {
    case 0:
        if (self->AnimationFinished(st->mAnim)) {
            st->mAnim = 0;
            st->mB14 = true;
            st->mFreakOut = FreakOut(self, freakFlag);
            self->SetStealthed(0, 0);
            self->Hover(1);
            st->mState = 3;
        }
        break;

    case 1: {
        float t = st->mTimer4 + dt;
        st->mTimer4 = t;
        if (t > 1.0f) {
            Vec3 d;
            d.x = myPos->x - ownerDir.x;
            d.y = myPos->y - ownerDir.y;
            d.z = myPos->z - ownerDir.z;
            Vec3 u;
            normalized_safe(&u, &d);
            const float& pick = MaxRef(stopDist, dist);
            float ownerR = owner->GetFootprintRadius();
            float s = (loco->GetFootprintRadius() + ownerR) + pick;
            Vec3 tp;
            tp.x = ownerDir.x + u.x * s;
            tp.y = ownerDir.y + u.y * s;
            tp.z = ownerDir.z + u.z * s;
            RunTo(self, myPos, tp);
            st->mTimer4 = 0.0f;
        }
        PlayScaredAnimation(self, owner, &st->mFreakOut);
        if (flags4 & 0x100000) {
            if (0.0f < st->mTimer1)
                break;
            if (!(stopDist > dist)) {
                if (!loco->IsNearGoal())
                    break;
            }
        }
        if (self->FUN_00c0f570() > 0) {
            self->InterruptAnimation(0x3a74a08, -1, 0);
            st->mState = 2;
            break;
        }
        if ((flags4 & 0x100000) && self->FUN_00c0c140() != -1 && self->mSpotsBegin != self->mSpotsEnd) {
            SpotObj* o = (*self->mSpotsBegin)->mObj;
            st->mVec = o->mPos;
            st->mF2c = o->FUN_00aff550();
            st->mTimer1 = hideTime2;
            st->mState = 7;
            Vec3 d;
            d.x = st->mVec.x - ownerDir.x;
            d.y = st->mVec.y - ownerDir.y;
            d.z = st->mVec.z - ownerDir.z;
            Vec3 u;
            normalized_safe(&u, &d);
            float s = loco->GetFootprintRadius() + st->mF2c;
            Vec3 tp;
            tp.x = st->mVec.x + s * u.x;
            tp.y = st->mVec.y + u.y * s;
            tp.z = st->mVec.z + u.z * s;
            RunTo(self, myPos, tp);
            break;
        }
        goto settle;
    }

    case 2:
        if (!self->WaitForAnimEventOrEnd(0x81d12704, &jumpTime, -1, 0, 1) && !self->AnimationFinished2(0))
            break;
        self->FUN_00c19940(0);
    settle:
        st->mB14 = true;
        st->mFreakOut = FreakOut(self, freakFlag);
        st->mState = 3;
        self->Hover(1);
        break;

    case 3:
        st->mTimer5 = st->mTimer5 - dt;
        self->FUN_00c19940(0);
        if (waitOk) {
            if (loco->IsNearGoal() || !(0.0f < st->mTimer1)) {
                unsigned hideFlag = flags4 & 0x100000;
                if (hideFlag && self->FUN_00c0c140() != -1 && self->mSpotsBegin != self->mSpotsEnd &&
                    !(dist < stopDist * 0.5f)) {
                    SpotObj* o = (*self->mSpotsBegin)->mObj;
                    st->mVec = o->mPos;
                    st->mF2c = o->FUN_00aff550();
                    st->mState = 7;
                    Vec3 d;
                    d.x = st->mVec.x - ownerDir.x;
                    d.y = st->mVec.y - ownerDir.y;
                    d.z = st->mVec.z - ownerDir.z;
                    Vec3 u;
                    normalized_safe(&u, &d);
                    float s = loco->GetFootprintRadius() + st->mF2c;
                    Vec3 tp;
                    tp.x = st->mVec.x + s * u.x;
                    tp.y = st->mVec.y + u.y * s;
                    tp.z = st->mVec.z + u.z * s;
                    RunTo(self, myPos, tp);
                    break;
                }

                Vec3* dirp;
                Vec3 dbuf;
                if (nearEnough) {
                    Vec3 d;
                    d.x = myPos->x - ownerDir.x;
                    d.y = myPos->y - ownerDir.y;
                    d.z = myPos->z - ownerDir.z;
                    dirp = normalized_safe(&dbuf, &d);
                } else {
                    dirp = loco->GetDirection(&dbuf);
                }
                Vec3 w;
                w.x = dirp->x * dirScale;
                w.y = dirp->y * dirScale;
                w.z = dirp->z * dirScale;
                HomeObj* home = self->FUN_00c04590();
                if (!scaredOrCaster || (randDist < dist && (int)sMathRandom.RandomUint32Uniform(100) < 0x32)) {
                    Vec3* q = home->FUN_00c6acc0();
                    Vec3 d;
                    d.x = q->x - myPos->x;
                    d.y = q->y - myPos->y;
                    d.z = q->z - myPos->z;
                    Vec3 n;
                    normalized_safe(&n, &d);
                    w.x = n.x * neighbourWeight + w.x;
                    w.y = n.y * neighbourWeight + w.y;
                    w.z = n.z * neighbourWeight + w.z;
                }
                if (scaredOrCaster && (self->mF90 || hideFlag)) {
                    NearEntry** cur = self->mNearEnd;
                    NearEntry** begin = self->mNearBegin;
                    if (cur != begin) {
                        do {
                            NearEntry* h = cur[-1];
                            cSPCreatureBase* a = interface_cast_animal(h->mCreature);
                            Pred pred;
                            if (pred.Test(h) && a && a->mGroup == self->mGroup && a->GetTargetObj() == tgtObj &&
                                a->mBehav->m1d8 == 0x2d852e0) {
                                LocoState* ls = a->mLoco.GetState();
                                if (ls->mHasPath != 0) {
                                    Vec3 d;
                                    d.x = ls->mV14.x - myPos->x;
                                    d.y = ls->mV14.y - myPos->y;
                                    d.z = ls->mV14.z - myPos->z;
                                    Vec3 n;
                                    Vec3* np = Vector3_Normalize(&n, &d);
                                    w.x = friendWeight * np->x + w.x;
                                    w.y = np->y * friendWeight + w.y;
                                    w.z = np->z * friendWeight + w.z;
                                    break;
                                }
                            }
                            cur = cur - 1;
                        } while (cur != begin);
                    }
                }
                if (loco->IsOnView() &&
                    ((animal && ((animal->mFlags >> 9) & 1)) || (ownerCast && ownerCast->m714 == 0))) {
                    cViewer* viewer = App()->GetViewer();
                    Vec3 camPos, camDir;
                    viewer->GetCameraLocationInfo(&camPos, &camDir, 0, 0);
                    Vec3 n;
                    Vector3_Normalize(&n, myPos);
                    float dp = (n.x * camDir.x + camDir.y * n.y) + camDir.z * n.z;
                    n.x = camDir.x - dp * n.x;
                    n.y = camDir.y - dp * n.y;
                    n.z = camDir.z - dp * n.z;
                    Vec3 n2buf;
                    Vec3* n2 = Vector3_Normalize(&n2buf, &n);
                    w.x = viewWeight * n2->x + w.x;
                    w.y = n2->y * viewWeight + w.y;
                    w.z = n2->z * viewWeight + w.z;
                }
                Vec3 wbuf;
                Vec3* wn = normalized_safe(&wbuf, &w);
                w = *wn;
                Vec3 tp;
                tp.x = w.x * fleeDist + myPos->x;
                tp.y = myPos->y + w.y * fleeDist;
                tp.z = myPos->z + w.z * fleeDist;
                RunTo(self, myPos, tp);
                loco->GetState()->mHasPath = 2;
                st->mTimer1 = restTime;
                break;
            }
        }
        if (!loco->IsNearGoal() && !self->FUN_00c0c0e0()) {
            if (!(0.0f < st->mTimer5)) {
                st->mTimer5 = jumpTime;
                self->TryJumpToTarget(0, loco->FUN_00c42de0(), &DAT_0169ed0c, 0.0f, 0);
            }
            self->FUN_00c0cff0(2);
        }
        break;

    case 4: {
        Vec3 d;
        d.x = myPos->x - ownerDir.x;
        d.y = myPos->y - ownerDir.y;
        d.z = myPos->z - ownerDir.z;
        Vec3 w;
        normalized_safe(&w, &d);
        if (Vector3Equal(&w, &DAT_0169ed0c)) {
            Vec3 tmp;
            w = *FUN_0059aed0(&tmp, &DAT_0169ed58, loco->GetOrientation());
        }
        float angle = FUN_00572a60(DAT_01583f98);
        Vec3 axis;
        float m[9];
        FUN_00576b00(m, Vector3_Normalize(&axis, loco->GetPosition()), angle);
        Vec3 r;
        r.x = (m[0] * w.x + m[6] * w.z) + m[3] * w.y;
        r.y = (m[7] * w.z + m[4] * w.y) + m[1] * w.x;
        r.z = (m[8] * w.z + m[5] * w.y) + m[2] * w.x;
        Vec3 wbuf;
        w = *Vector3_Normalize(&wbuf, &r);
        Vec3 tp;
        tp.x = w.x * fleeDist + myPos->x;
        tp.y = w.y * fleeDist + myPos->y;
        tp.z = w.z * fleeDist + myPos->z;
        Vec3 surf;
        PlanetModel()->DirectionToSurfacePosition(&surf, &tp);
        FUN_00d99e20(myPos, &surf);
        self->MoveToPointAtSpeed(2, &surf, 1.0f, 2.0f);
        loco->GetState()->mHasPath = 2;
        if (!self->Hover(1) && self->mGroup->mF58c > 1.52587890625e-05f) {
            float p = GetPropertyT_float(gCreatureModeStrategy->mProperties, 0x04f7cf2c, 0.25f);
            if (sMathRandom.RandomDoubleUniform() < (double)p)
                self->TryJumpToTarget(0, &surf, &DAT_0169ed0c, 0.0f, 0);
        }
        st->mState = 5;
        break;
    }

    case 5:
        if (!(0.0f >= st->mTimer1) && !loco->IsNearGoal()) {
            self->FUN_00c0cff0(2);
            break;
        }
        st->mState = 3;
        break;

    case 6:
        self->Hover(0);
        PlayScaredAnimation(self, owner, &st->mFreakOut);
        if (!(0.0f < st->mTimer1) && loco->IsNearGoal())
            return false;
        if (nearEnough && stopDist > dist) {
            if (st->mB14)
                st->mFreakOut = FreakOut(self, freakFlag);
            st->mState = 3;
            self->Hover(1);
            st->mTimer1 = 0.0f;
        }
        break;

    case 7:
        if (stopDist * 0.5f > dist) {
            st->mB14 = true;
            st->mFreakOut = FreakOut(self, freakFlag);
            st->mState = 3;
            break;
        }
        if (!(0.0f > st->mTimer1)) {
            Vec3 d1;
            d1.x = myPos->x - st->mVec.x;
            d1.y = myPos->y - st->mVec.y;
            d1.z = myPos->z - st->mVec.z;
            Vec3 u;
            normalized_safe(&u, &d1);
            Vec3 d2;
            d2.x = ownerDir.x - st->mVec.x;
            d2.y = ownerDir.y - st->mVec.y;
            d2.z = ownerDir.z - st->mVec.z;
            Vec3 v;
            normalized_safe(&v, &d2);
            if (!((u.y * v.y + u.z * v.z) + v.x * u.x >= 0.0f)) {
                if (loco->IsNearGoal() && !self->FUN_00c0e0c0(0x52b0e04))
                    self->PlayAnimation(0x52b0e04, 1, -1);
            } else {
                Vec3 d3;
                d3.x = st->mVec.x - ownerDir.x;
                d3.y = st->mVec.y - ownerDir.y;
                d3.z = st->mVec.z - ownerDir.z;
                Vec3 u2;
                normalized_safe(&u2, &d3);
                float s = loco->GetFootprintRadius() + st->mF2c;
                Vec3 tp;
                tp.x = s * u2.x + st->mVec.x;
                tp.y = st->mVec.y + s * u2.y;
                tp.z = st->mVec.z + s * u2.z;
                RunTo(self, myPos, tp);
            }
        } else {
            st->mTimer1 = hideTime;
            st->mState = 6;
        }
        break;
    }

    self->FUN_00c0d0c0(2, hasTimer);
    return true;
}
