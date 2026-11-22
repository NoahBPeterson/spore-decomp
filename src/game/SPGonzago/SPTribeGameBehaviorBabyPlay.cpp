// src/game/SPGonzago/SPTribeGameBehaviorBabyPlay.cpp -- migrated from slice(s) s00d71f80 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeGameBehaviorBabyPlay.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cInteractionAgent.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cTribe.h"

// unnamed retail callees and globals (address in the comment)
extern const float kOneF;          // 0x01470f1c  1.0f
extern const float kSqEps;         // 0x013ec4b8  1e-8f
extern float kZeroA;               // 0x0157206c
extern float kZeroB;               // 0x01572070
extern const float kFearScaleF;    // 0x01581340
extern const float kSinHalfF;      // 0x01584190
extern const float kRotConstF;     // 0x01471064
#include <math.h>
#include <string.h>

// ---- items of slice s00d71f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char byte;
void operator delete(void* p) throw();        // 0x00f47380
void operator delete[](void* p) throw();      // 0x00f47380
namespace SP {
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) : x(v.x), y(v.y), z(v.z) {}
    float LengthSquared() const { return x * x + y * y + z * z; }
};
}
namespace SP {
struct cPlanetModel_s00d7_1f80 {
    float       GetWaterHeight();                                             // 0x00b7e390
    float       GetRadiusAt(const cSPVector3* pos);                           // 0x00b7ef70
    cSPVector3* DirectionToSurfacePosition(cSPVector3* out, cSPVector3* dir);  // 0x00b815a0
    cSPVector3* MakeRandomWorldPosition(cSPVector3* out, const cSPVector3* dir); // 0x00b81780
};
}
namespace SP {
cPlanetModel_s00d7_1f80* PlanetModel();                                                  // 0x00b3d350
}
namespace SP {
cSPVector3* normalized_safe(cSPVector3* out, const cSPVector3* in);          // 0x00449c20
}
namespace SP {
cSPVector3* SomeRotate(cSPVector3* out, const cSPVector3* a, const cSPVector3* b);   // 0x0059aed0
}
namespace SP {
struct cVt32 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual cSPVector3* AtAngle(float a, float b);   // +0x2c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual float GetFacingAngle();                  // +0x70
};
}
namespace SP {
class cLocomotiveObject_s00d7_1f80 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual cSPVector3* GetPosition();               // +0x2c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
    virtual void GetSteerParams(void* params);       // +0xdc

    char  mTail[0x3e0 - 4];                          // pad the class out to 0x3e0
    bool IsNearGoal();                               // 0x00c42e20
};
}
namespace SP {
class cTribe_s00d7_1f80;
}
namespace SP {
class cSPCreatureCitizen_s00d7_1f80;
}
namespace SP {
class cTribeMember {
public:
virtual void v00();
virtual void v04();
    cTribe_s00d7_1f80* GetTribe();                                                // 0x00c22f50
    void SetCurrentToolEffect(int tool, unsigned a);                   // 0x00c24f40
    void PlayAnimation(unsigned animID, int a, int b);                 // 0x00c12190
    void MoveToPointAndFacingAtSpeed(int speed, const cSPVector3* pt,
                                     const cSPVector3* facing, float f1, float f2); // 0x00c1c5c0
    void MoveToPointAtSpeed(int speed, const cSPVector3* pt, float f1, float f2);  // 0x00c1c1d0
    bool  QueryFlagB770();                                             // 0x00c0b770
    void  FuncC0CFF0(int a);                                           // 0x00c0cff0
    bool  FuncC0E0C0(int a);                                           // 0x00c0e0c0

    char pad00[0xc0];
    cLocomotiveObject_s00d7_1f80 mLoco;            // +0xc0
};
}
namespace SP {
class cTribe_s00d7_1f80 {
public:
    char  pad00[0x120];
    cLocomotiveObject_s00d7_1f80* mpLeader_120;    // +0x120  (GetPosition at vtable+0x2c)
    char  pad_124[0x260 - 0x124];
    void* mpLeader_260;                 // +0x260  (object whose +0x34 is a spatial base)
};
}
namespace SP {
void* AgentMapLookup(int a, void* fn, void** key);          // 0x00bc9b00
}
namespace SP {
void* AgentOrderFindNode(void* a, int b, int c);            // 0x00bca620
}
namespace SP {
class cSPCreatureCitizen_s00d7_1f80 : public cTribeMember {
public:
    char  pad_b4c[0xb4c - 0xc0 - 0x3e0];
    void* mpOrderManager;   // +0xb4c
};
}
namespace SP {
struct SteerParams {
    char  pad00[0x40];
    void* mpVec;            // +0x40  (a heap vector, released by the caller)
    char  pad44[0x24];
};
}
extern const float kOneF;          // 0x01470f1c  1.0f
extern const float kSqEps;         // 0x013ec4b8  1e-8f
extern float kZeroA;               // 0x0157206c
extern float kZeroB;               // 0x01572070
extern const float kFearScaleF;    // 0x01581340
extern const float kSinHalfF;      // 0x01584190
extern const float kRotConstF;     // 0x01471064
// ---- items of slice s00d71f80 end

// ---- items of slice s00d70fe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00d995c0();
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;

// ---------------------------------------------------------------------------
// shared math types
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
};

extern Vector3 g_v0169ee40;          // 0x0169ee40, unit Z
extern float   g_f01582e30;          // 0x01582e30
extern float   g_f01687a00;          // 0x01687a00
extern float   g_f01687a48;          // 0x01687a48
extern float   g_f0169e278;          // 0x0169e278
extern float   g_f0156c194f;         // 0x0156c194
extern int     g_i0156c194;          // 0x0156c194
extern float   g_f01582e68;          // 0x01582e68
extern float   g_f0148fddc;          // 0x0148fddc (1.5258789e-05)
extern float   g_f0148fde0;          // 0x0148fde0 (10.0)

bool  Vector3Equal(const Vector3* a, const Vector3* b);        // 0x004232c0
bool  Vector3_NotEqual(const Vector3* a, const Vector3* b);    // 0x0041dd30
void  normalized_safe(Vector3* out, const Vector3* in);        // 0x00449c20

class cPlanetModel {
public:
    void ToSurface(Vector3* out, const Vector3* in);            // 0x00b81630
    void DirectionToSurfacePosition(Vector3* out, const Vector3* in);  // 0x00b815a0
};
cPlanetModel* PlanetModel();                                   // 0x00b3d350

// ---------------------------------------------------------------------------
// stimuli and the behaviour-side object at creature+0xb4c
// ---------------------------------------------------------------------------
class Stimuli {
public:
    void ClearAll(int mask, int flags);    // 0x00bc98f0
    void* Play(int flags, int a);          // 0x00bc96a0
    void* Make(int a, int b, float c, int d);  // 0x00bc97f0
    void ClearStimulus(int a);             // 0x00bc9770
};

class cSim5a8 {
public:
    float NodeRatio();                     // 0x00bfc490
};

class cNotificationMgr {
public:
    void Send(int a, void* b, int c);      // 0x00ba48b0
};
cNotificationMgr* NotificationMgr();       // 0x00b3d4c0

// ---------------------------------------------------------------------------
// locomotion object, embedded at creature+0xc0
// ---------------------------------------------------------------------------
class cLocomotiveObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void* v2c();                    // +0x2c  GetPosition
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool v58();                     // +0x58
    virtual void* v5c(Vector3* out);        // +0x5c
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70();
    virtual float v74();                    // +0x74  facing angle
    virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8();
    virtual void vdc(); virtual void ve0(); virtual void ve4(); virtual void ve8();
    virtual void vec();                     // +0xec
    virtual void vf0();

    bool IsNearGoal();                      // 0x00c42e20
};

// ---------------------------------------------------------------------------
// tribe / citizen
// ---------------------------------------------------------------------------
class cTribe;

class cSPCreatureBase {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual bool v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80();
    virtual void v84(int a, int b, int c);               // +0x84
    virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
    virtual void vb8(); virtual void vbc(); virtual void vc0(); virtual void vc4();
    virtual void vc8(); virtual void vcc(); virtual void vd0(); virtual void vd4();
    virtual void vd8(); virtual void vdc(); virtual void ve0(); virtual void ve4();
    virtual void ve8(int a); virtual void vec(); virtual void vf0();

    void* GetTargetAsCreature();                         // 0x00c0ee70
    void  UpdateLocomotion(int a);                       // 0x00c14750
    bool  AnimationFinished(int anim);                   // 0x00c12400
    int   PlayAnimation(int id, int a, int b);           // 0x00c12190
    int   PlayAnimationWithTargetObj(int id, void* target, int a, int b);  // 0x00c14940
    void  Attack(cSPCreatureBase* target, int a);        // 0x00c1e460
    void  MoveToPointAndFacingAtSpeed(int speed, Vector3* pos, Vector3* facing, float a, float b);
                                                         // 0x00c1c5c0
    void  MoveToPointAtSpeed(int speed, Vector3* pos, float a, float b);   // 0x00c1c1d0
    void* GetFieldE7C();                                 // 0x00c0ee60
    bool  BehaviourFlag();                               // 0x00c0b780
    bool  AnimValid(int anim);                           // 0x00c0e070
    bool  SomeBool();                                    // 0x00c0b770
    float SomeRatio();                                   // 0x00c0b9c0
    float SomeValue();                                   // 0x00c0bb10
    void* SomeObj();                                     // 0x00c0bc00
    bool  CanSee(Vector3* pos, Vector3* out);            // 0x00a04d20
    void* PickAttackTarget(int, int, int, int, int, int, int);  // 0x00c12410

    char pad004[0x34 - 0x004];
    void* mpField34;         // +0x34
    char pad038[0x110 - 0x038];
    u32  mFlags110;          // +0x110
    char pad114[0x135 - 0x114];
    u8   mb135;              // +0x135
    char pad136[0x137 - 0x136];
    u8   mb137;              // +0x137
    char pad138[0x1e8 - 0x138];
    int  mField1e8;          // +0x1e8
    char pad1ec[0x1f4 - 0x1ec];
    void* mpField1f4;        // +0x1f4
    char pad1f8[0x5a8 - 0x1f8];
    cSim5a8 mObj5a8;         // +0x5a8
    char pad5a9[0x5e0 - 0x5a9];
    float mField5e0;         // +0x5e0
    char pad5e4[0xb20 - 0x5e4];
    void* mpFieldB20;        // +0xb20
    char pad_b24[0xb4c - 0xb24];
    void* mpStimuliMgr;      // +0xb4c
    cSPCreatureBase* mpTarget;  // +0xb50
    void* mpFieldB54;        // +0xb54
    u32  mFlagsB58;          // +0xb58
    char pad_b5c[0xb5e - 0xb5c];
    u8   mbB5e;              // +0xb5e
    u8   mbB5f;              // +0xb5f
    char pad_b60[0x1014 - 0xb60];
    cTribe* mpTribe;         // +0x1014
};

class cSPCreatureCitizen : public cSPCreatureBase {
public:
    cTribe* GetTribe();                                  // 0x00c22f50
};

class cTribeMember;

class cTribe {
public:
    void SetStimuli(int a, int b, float c, void* d);     // 0x00c8f470
};

class cAgentOrderNode {
public:
    int CurrentId();                                     // 0x00bc9b10
};

class cAgentOrderManager {
public:
    cAgentOrderNode* FindNode(int a, void* fn, void* ctx);  // 0x00bca620
};

cAgentOrderManager* AgentOrderManager();                 // 0x00bc9b00

class cSPUIEventLog {
public:
    void PostFeedbackEvent(int a, int b, int c, int d, int e, int f);  // 0x00dd8640
};
cSPUIEventLog* EventLog();                               // 0x00b3d3e0

// ---------------------------------------------------------------------------
// behaviour state objects (sixth stack argument of the behaviour callbacks)
// ---------------------------------------------------------------------------
struct AutoRef {
    cSPCreatureBase* mp;
    AutoRef& operator=(cSPCreatureBase* v);              // 0x00b5f950
};

struct CarcassCtx {
    int      mState;        // +0x00
    AutoRef  mTarget;       // +0x04
    u8       mbField08;     // +0x08
    u8       mbField09;     // +0x09
    u16      pad0a;
    int      mAnimId;       // +0x0c
    int      mAnimArgA;     // +0x10
    int      mAnimArgB;     // +0x14
};

struct EggCtx {
    int      mState;        // +0x00
    float    mTimer;        // +0x04
    cSPCreatureBase* mpFood; // +0x08
    int      mAnimId;       // +0x0c
};

struct AchievementCtx {
    cSPCreatureBase* mpSelf;
    cSPCreatureBase* mpTarget;
    int              mField08;
};

class cStimulusPayload {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cSPCreatureBase* Lookup(int id);             // +0x0c
};

class cStimulus {
public:
    char pad00[0x0c];
    int  mField0c;                                       // +0x0c
    char pad10[0x1c];
    cStimulusPayload* mpPayload;                         // +0x2c
};

// ---- external helpers used by the two large behaviour ticks -----------------
cSPCreatureBase* GetAnimalFromStimulus(void* stim);      // 0x00d99980
int    FUN_00c0b8e0(cSPCreatureBase* animal);            // 0x00c0b8e0
void   FUN_00ba48b0(int a, void* b, int c);              // 0x00ba48b0
int    RandomUint32Uniform(int range);                   // 0x00a68fb0
void   FUN_00f924e0(float f);                            // 0x00f924e0
void   EatFood(cSPCreatureBase* self, const char* name, int a, int b);  // 0x00d85ad0
void   FUN_00d85540(cSPCreatureBase* self);              // 0x00d85540
void   FUN_00d70b10(float dt, cSPCreatureBase* self, void* ctx);  // 0x00d70b10
void   FUN_00d39360(int event, void* data);              // 0x00d39360
void   NotifyEvent(float f);                             // 0x00d2e8a0
void   FUN_00d52e40(int a);                              // 0x00d52e40
void*  cPosseSimulatorInstance();                        // 0x00d539d0
int    FUN_00d998d0(void* a, int b);                     // 0x00d998d0
void*  Achievements();                                   // 0x00675250
void*  AchievementsAccessor(void* c);                    // 0x00675370
bool   AchievementsHas(void* c, int id);                 // 0x00675e80
void   AchievementsClear(void* c);                       // 0x00675770
void   AchievementsAutoTest(void* c, int id, int v);      // 0x00676e90
void*  AchievementsLookup(void* c, void* key, void* out); // 0x00675b60


// ---------------------------------------------------------------------------
// 00d70fe0 : SP::EAT_CARCASS_Deactivate
// ---------------------------------------------------------------------------
struct DeactivateCtx {
    char pad00[4];
    cSPCreatureBase* mpTarget;    // +0x04
};
// ---- items of slice s00d70fe0 end

bool FUN_00d71f80(SP::cTribeMember* citizen, int, int, int, int, unsigned* out)
{
    *out = 0;
    citizen->SetCurrentToolEffect(0, 0xffffffff);
    return true;
}

// @ 0x00d71fa0
bool SP_FOOD_CRY_Tick(SP::cSPCreatureCitizen_s00d7_1f80* citizen, int, int, int, int, uint32_t* state)
{
    if (*state == 0) {
        SP::cTribe_s00d7_1f80* tribe = citizen->GetTribe();
        void* leader = tribe->mpLeader_260;
        SP::cVt32* sp = (SP::cVt32*)((char*)leader + 0x34);
        float angle = sp->GetFacingAngle();
        SP::cSPVector3* dir = sp->AtAngle(0.0f, angle);
        SP::cSPVector3 buf;
        SP::PlanetModel()->MakeRandomWorldPosition(&buf, dir);
        SP::cSPVector3* pos = ((SP::cLocomotiveObject_s00d7_1f80*)((char*)citizen + 0xc0))->GetPosition();
        SP::cSPVector3 diff(buf.x - pos->x, buf.y - pos->y, buf.z - pos->z);
        float inv = 1.0f / sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + kSqEps);
        SP::cSPVector3 facing(inv * diff.x, inv * diff.y, inv * diff.z);
        citizen->MoveToPointAndFacingAtSpeed(2, &buf, &facing, kZeroA, kZeroB);
        *state = 1;
    } else if (*state == 1) {
        if (((SP::cLocomotiveObject_s00d7_1f80*)((char*)citizen + 0xc0))->IsNearGoal()) {
            *state = 2;
            citizen->PlayAnimation(0x2fc3666, 1, 0xffffffff);
            return true;
        }
    }
    return true;
}

// @ 0x00d72100
bool SP_FEAR_Tick(SP::cSPCreatureCitizen_s00d7_1f80* citizen, int, int, int, int, uint32_t*)
{
    if (citizen->QueryFlagB770())
        return false;

    void* p = 0;
    if (citizen != 0)
        p = (char*)citizen + 0x5a8;
    void* mgr = SP::AgentMapLookup(0x060995fc, (void*)0x00d995c0, &p);
    void* order = SP::AgentOrderFindNode(mgr, 0, 0);
    if (order != 0) {
        SP::SteerParams s;
        for (unsigned i = 0; i < sizeof(s); ++i)
            ((char*)&s)[i] = 0;
        ((SP::cLocomotiveObject_s00d7_1f80*)((char*)citizen + 0xc0))->GetSteerParams(&s);
        if (s.mpVec != 0 && *(int*)((char*)s.mpVec - 4) != 0)
            operator delete[](s.mpVec);
        citizen->FuncC0CFF0(0);
        if (!citizen->FuncC0E0C0(0x2fc3667))
            citizen->PlayAnimation(0x2fc3667, 1, 0xffffffff);
        return true;
    }

    if ((*(uint32_t*)((char*)citizen->mpOrderManager + 0x1cc) & 0x100) != 0) {
        SP::cLocomotiveObject_s00d7_1f80* loco = (SP::cLocomotiveObject_s00d7_1f80*)((char*)citizen + 0xc0);
        if (loco->IsNearGoal() || ((*(byte*)((char*)citizen + 0x330) & 1) != 0)) {
            SP::cTribe_s00d7_1f80* tribe = citizen->GetTribe();
            float scale = kFearScaleF;
            SP::cSPVector3* tpos = tribe->mpLeader_120->GetPosition();
            SP::cSPVector3* cpos = loco->GetPosition();
            SP::cSPVector3 diff(cpos->x - tpos->x, cpos->y - tpos->y, cpos->z - tpos->z);
            SP::cSPVector3 n1, n2;
            SP::normalized_safe(&n1, &diff);
            SP::normalized_safe(&n2, (SP::cSPVector3*)tpos);
            float sh = sinf(kSinHalfF * kRotConstF);
            float ch = cosf(kSinHalfF * kRotConstF);
            SP::cSPVector3 quat(n2.x * sh, n2.y * sh, n2.z * sh);
            (void)ch;
            SP::cSPVector3 rot;
            SP::SomeRotate(&rot, &n1, &quat);
            SP::cSPVector3* tpos2 = tribe->mpLeader_120->GetPosition();
            SP::cSPVector3 pt(rot.x * scale + tpos2->x,
                              rot.y * scale + tpos2->y,
                              rot.z * scale + tpos2->z);
            SP::cSPVector3 surf;
            SP::PlanetModel()->DirectionToSurfacePosition(&surf, &pt);
            ((SP::cTribeMember*)citizen)->MoveToPointAtSpeed(3, &surf, kOneF, kOneF);
        }
        if (!citizen->FuncC0E0C0(0x2c38d92))
            citizen->PlayAnimation(0x2c38d92, 1, 0xffffffff);
        return true;
    }
    return false;
}

// @ 0x00d70fe0
void FUN_00d70fe0(cSPCreatureBase* self, int, int, int, int, DeactivateCtx* ctx)
{
    cSPCreatureBase* target = ctx->mpTarget;
    if (target != 0)
    {
        if (target->mpTarget == self)
        {
            cSPCreatureBase* held = *(cSPCreatureBase* volatile*)&target->mpTarget;
            if (held != 0)
            {
                target->mpTarget = 0;
                held->v04();
            }
        }
    }
    cSPCreatureBase* target2 = ctx->mpTarget;
    if (target2 == (cSPCreatureBase*)self->GetTargetAsCreature())
        self->v84(0, 0, 0);
    Stimuli* stimuli = (Stimuli*)((char*)self->mpStimuliMgr + 8);
    stimuli->ClearAll(0x40000, 0);
    cSPCreatureBase* target3 = ctx->mpTarget;
    if (target3)
        target3->v04();
}

// @ 0x00d71f50
void FUN_00d71f50(cSPCreatureBase* self)
{
    Stimuli* stimuli = (Stimuli*)((char*)self->mpStimuliMgr + 8);
    stimuli->ClearAll(0, 0x100);
    self->UpdateLocomotion(0);
}

// @ 0x00d71eb0
bool TRIBE_BABY_FEAR_Activate(cSPCreatureCitizen* self)
{
    cLocomotiveObject* loco = (cLocomotiveObject*)((char*)self + 0xc0);
    if (loco->v58())
    {
        EventLog()->PostFeedbackEvent(0x9cb7ee45, 0x182cd6ce, (int)loco->v2c(), 0, 1, 0);
        return true;
    }
    cAgentOrderNode* node = AgentOrderManager()->FindNode(0x60995fc, (void*)FUN_00d995c0, self);
    if (node)
    {
        int id = node->CurrentId();
        if (id)
            self->GetTribe()->SetStimuli(0, 0x4000, 25.0f, (void*)id);
    }
    return true;
}

// ---------------------------------------------------------------------------
// 00d71060 : SP::EAT_CARCASS_Tick
// ---------------------------------------------------------------------------
// @ 0x00d71060
bool EAT_CARCASS_Tick(cSPCreatureBase* self, int, int, int, int, CarcassCtx* ctx, int, float dt)
{
    if (!ctx->mTarget.mp || !ctx->mTarget.mp->mbB5e || !ctx->mTarget.mp->mb135)
        return false;

    cSPCreatureBase* found = (cSPCreatureBase*)self->GetTargetAsCreature();
    if (found && found->mbB5e && found->mb135 && found != ctx->mTarget.mp)
    {
        ctx->mState = 0;
        cSPCreatureBase* old = ctx->mTarget.mp;
        if (old && old->mpTarget)
        {
            cSPCreatureBase* held = old->mpTarget;
            old->mpTarget = 0;
            held->v04();
        }
        ctx->mTarget = found;
    }

    if (ctx->mTarget.mp->mpTarget != self)
    {
        if (((self->mFlagsB58 >> 9) & 1) == 0 && ctx->mTarget.mp->mpTarget != 0)
            return false;
        ctx->mTarget = self;
    }

    cLocomotiveObject* loco = (cLocomotiveObject*)((char*)self + 0xc0);

    switch (ctx->mState)
    {
    case 0:
    {
        float startAngle;
        if ((ctx->mTarget.mp->mFlags110 & 0x1000) == 0)
            startAngle = loco->v74();
        else
            startAngle = *(float*)((char*)self->mpFieldB20 + 0x55c);

        cSPCreatureBase* target = ctx->mTarget.mp;
        if (target->mpFieldB54)
        {
            Vector3 spot;
            Vector3* p = (Vector3*)loco->v2c();
            if (!target->CanSee(p, &spot))
                spot = *(Vector3*)loco->v2c();

            Vector3 surface;
            PlanetModel()->ToSurface(&surface, &spot);

            Vector3 dir;
            Vector3* here = (Vector3*)loco->v2c();
            dir.x = surface.x - here->x;
            dir.y = surface.y - here->y;
            dir.z = surface.z - here->z;

            Vector3 dirN;
            normalized_safe(&dirN, &dir);

            Vector3 facing;
            if (Vector3Equal(&dirN, &g_v0169ee40))
            {
                Vector3 tmp;
                facing = *(Vector3*)loco->v5c(&tmp);
            }
            else
            {
                Vector3 surfN;
                normalized_safe(&surfN, &surface);
                float d = dirN.x * surfN.x + dirN.y * surfN.y + dirN.z * surfN.z;
                Vector3 perp;
                perp.x = dirN.x - surfN.x * d;
                perp.y = dirN.y - surfN.y * d;
                perp.z = dirN.z - surfN.z * d;
                if (Vector3_NotEqual(&perp, &g_v0169ee40))
                    facing = perp;
                else
                    facing = dirN;
            }

            float angle = loco->v74() + startAngle;
            self->MoveToPointAndFacingAtSpeed(2, &spot, &facing, angle, angle);
            ctx->mState = 1;
            return true;
        }

        float angle = loco->v74() + startAngle;
        cLocomotiveObject* tloco = (cLocomotiveObject*)((char*)target + 0xc0);
        Vector3* spot = (Vector3*)tloco->v2c();
        self->MoveToPointAtSpeed(2, spot, angle, angle);
        ctx->mState = 1;
        return true;
    }

    case 1:
        if (!loco->IsNearGoal())
            return true;

        loco->vec();
        ctx->mState = 2;
        FUN_00d85540(self);
        {
            void* animTarget = ctx->mTarget.mp ? (void*)((char*)ctx->mTarget.mp + 0xc0) : 0;
            ctx->mAnimId = self->PlayAnimationWithTargetObj(ctx->mAnimArgA, animTarget,
                                                            ctx->mAnimArgB, -1);
        }
        if (((self->mFlagsB58 >> 9) & 1) == 0)
            return true;
        if (ctx->mTarget.mp->mbB5f)
            return true;
        if (!self->BehaviourFlag())
            return true;
        ctx->mTarget.mp->mbB5f = 1;
        ctx->mbField08 = 1;
        NotifyEvent(g_f01582e30);
        {
            AchievementCtx ac;
            ac.mpSelf = self;
            ac.mpTarget = ctx->mTarget.mp;
            ac.mField08 = 0;
            FUN_00d39360(0xd335362d, &ac);

            void* ctrl = Achievements();
            void* acc = AchievementsAccessor(ctrl);
            if (AchievementsHas(acc, 0xe25acf0e))
            {
                AchievementsClear(acc);
                return true;
            }
            AchievementsAutoTest(ctrl, 0xe25acf0e, 1);
        }
        return true;

    case 2:
        if (self->BehaviourFlag() && self->AnimValid(ctx->mAnimId))
            FUN_00d70b10(dt, self, ctx);
        if (self->AnimationFinished(ctx->mAnimId))
            ctx->mState = 3;
        return true;

    case 3:
    {
        Stimuli* s = (Stimuli*)((char*)self->mpStimuliMgr + 8);
        void* stim = s->Play(0x400, 0);
        if (stim)
        {
            cStimulusPayload* payload = ((cStimulus*)stim)->mpPayload;
            if (payload)
            {
                cSPCreatureBase* animal = payload->Lookup(0xd0036e08);
                if (animal && animal->mb135)
                {
                    int anim = self->PlayAnimationWithTargetObj(0xb20c5df2,
                                                               (char*)animal + 0xc0, -1, -1);
                    ctx->mAnimId = anim;
                    ctx->mState = 5;
                    s->ClearAll(0, 1);
                }
            }
        }

        if (!self->BehaviourFlag())
        {
            void* s2 = s->Make(0, 0x20000000, 0x40a00000, 0);
            ((cStimulus*)s2)->mField0c = -1;
            ctx->mState = 4;
            return true;
        }

        if (ctx->mState != 5)
            FUN_00d70b10(dt, self, ctx);
        ctx->mbField08 = 0;

        float v = self->SomeRatio();
        bool ready = v >= g_f01687a00 &&
                     (ctx->mbField09 == 0 || self->mObj5a8.NodeRatio() >= 1.0f);
        if (ready)
        {
            if (((self->mFlagsB58 >> 9) & 1) != 0 && !self->SomeBool())
            {
                self->ve8(1);
                if (cPosseSimulatorInstance())
                    FUN_00d52e40(1);
            }
            ctx->mState = 4;
            return true;
        }

        float w = self->SomeValue();
        if (w < g_f0148fddc)
        {
            ctx->mState = 4;
            return true;
        }
        ctx->mState = 1;
        return true;
    }

    case 4:
        return false;

    case 5:
        if (self->AnimationFinished(ctx->mAnimId))
            ctx->mState = 3;
        return true;

    default:
        return true;
    }
}

// ---------------------------------------------------------------------------
// 00d71780 : SP::EAT_EGG_Tick
// ---------------------------------------------------------------------------
// @ 0x00d71780
bool EAT_EGG_Tick(cSPCreatureBase* self, int, int, int, int, EggCtx* ctx, int, float dt)
{
    cSPCreatureBase* food = ctx->mpFood;
    if (!food)
        return false;
    if (food->v2c())
        return false;

    ctx->mTimer = ctx->mTimer - dt;
    if (ctx->mTimer > 0.0f)
        return true;

    if (((self->mFlagsB58 >> 9) & 1) == 0)
    {
        Stimuli* s = (Stimuli*)((char*)self->mpStimuliMgr + 8);
        void* stim = s->Play(0x400, 0);
        if (stim && ((cStimulus*)stim)->mpPayload)
        {
            cSPCreatureBase* animal = GetAnimalFromStimulus(stim);
            if (animal && animal->mb135 && FUN_00c0b8e0(animal) >= g_i0156c194)
            {
                s->ClearAll(0x400, 0);
                ctx->mState = 3;

                cLocomotiveObject* foodLoco = (cLocomotiveObject*)food->mpField34;
                Vector3* foodPos = (Vector3*)foodLoco->v2c();
                Vector3* selfPos = (Vector3*)self->v2c();  // hmm, self's loco, not self+0xc0
                Vector3 dir;
                dir.x = selfPos->x - foodPos->x;
                dir.y = selfPos->y - foodPos->y;
                dir.z = selfPos->z - foodPos->z;
                Vector3 dirN;
                normalized_safe(&dirN, &dir);
                dirN.x = -dirN.x;
                dirN.y = -dirN.y;
                dirN.z = -dirN.z;
                Vector3 dest;
                dest.x = selfPos->x + dirN.x * 10.0f;
                dest.y = selfPos->y + dirN.y * 10.0f;
                dest.z = selfPos->z + dirN.z * 10.0f;
                Vector3 surf;
                PlanetModel()->DirectionToSurfacePosition(&surf, &dest);
                self->MoveToPointAndFacingAtSpeed(2, &surf, &dirN, 1.0f, 2.0f);
                ctx->mTimer = 0.0f;
            }
        }
    }

    cLocomotiveObject* loco = (cLocomotiveObject*)((char*)self + 0xc0);

    switch (ctx->mState)
    {
    case 0:
        if (food->mField1e8 == 4 || food->mField1e8 == 5 || food->mField1e8 == 3)
            return false;
        self->UpdateLocomotion(0);
        {
            Vector3* selfPos = (Vector3*)loco->v2c();
            cLocomotiveObject* foodLoco = (cLocomotiveObject*)food->mpField34;
            Vector3* foodPos = (Vector3*)foodLoco->v2c();
            Vector3 dir;
            dir.x = foodPos->x - selfPos->x;
            dir.y = foodPos->y - selfPos->y;
            dir.z = foodPos->z - selfPos->z;
            Vector3 dirN;
            normalized_safe(&dirN, &dir);
            float myAngle = loco->v74();
            float foodAngle = foodLoco->v74();
            Vector3 dest;
            dest.x = foodPos->x - dirN.x * myAngle;
            dest.y = foodPos->y - dirN.y * myAngle;
            dest.z = foodPos->z - dirN.z * myAngle;
            self->MoveToPointAndFacingAtSpeed(2, &dest, &dirN,
                                              foodAngle + myAngle, foodAngle + myAngle + 1.0f);
        }
        if (loco->IsNearGoal())
        {
            if (loco->v58())
                NotificationMgr()->Send(6, (char*)food->mpField1f4 + 0x98, 0);
            ctx->mTimer = 1.0f;
            ctx->mState = 1;
            return true;
        }
        break;

    case 1:
        if (food->mField1e8 == 5 || food->mField1e8 == 3)
            return false;
        if (self->mb137 != 0)
        {
            if (((self->mFlagsB58 >> 9) & 1) == 0)
            {
                int r = RandomUint32Uniform(3000);
                ctx->mTimer = (float)r * 0.001f + 4.0f;
                self->PlayAnimation(0xf14faa42, 1, -1);
            }
            else
            {
                void* target = self->PickAttackTarget(0, 0, 0, 0, 0, 0, 0);
                ctx->mTimer = 1.0f;
                self->Attack((cSPCreatureBase*)target, 0);
            }
        }
        FUN_00d85540(self);
        if (food->mField1e8 == 4)
        {
            ctx->mAnimId = self->PlayAnimation(0x282d205, 1, -1);
            ctx->mState = 2;
            ctx->mTimer = 0.0f;

            float base = self->mField5e0;
            float maxv = self->mObj5a8.NodeRatio();
            float v = maxv * g_f01582e68 + base;
            if (v <= 0.0f)
                v = 0.0f;
            if (maxv <= v)
                v = maxv;
            FUN_00f924e0(v);

            if (loco->v58())
                NotifyEvent(g_f0169e278);
            if (loco->v58())
                NotificationMgr()->Send(7, (char*)food->mpField1f4 + 0x98, 0);

            EatFood(self, (const char*)&g_f01687a48, 0x133b8599, 1);
            AchievementCtx ac;
            ac.mpSelf = self;
            ac.mpTarget = food;
            ac.mField08 = 0;
            FUN_00d39360(0xd335362e, &ac);
            return true;
        }
        break;

    case 2:
        if (self->AnimationFinished(ctx->mAnimId))
        {
            self->UpdateLocomotion(0);
            return false;
        }
        break;

    case 3:
        if (loco->IsNearGoal())
        {
            self->PlayAnimationWithTargetObj(0x320446ba, food->mpField34, -1, -1);
            int r = RandomUint32Uniform(3000);
            ctx->mTimer = (float)r * 0.001f + 2.0f;
            ctx->mState = 0;
        }
        break;
    }

    return true;
}
