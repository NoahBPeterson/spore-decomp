// src/game/SPGonzago/SPEatEgg.cpp -- migrated from slice(s) s00d70fe0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPEatEgg.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cTribe.h"

// unnamed retail callees and globals (address in the comment)
extern float   g_f01687a48;          // 0x01687a48
extern float   g_f0169e278;          // 0x0169e278
extern int     g_i0156c194;          // 0x0156c194
extern float   g_f01582e68;          // 0x01582e68

// ---- items of slice s00d70fe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
typedef unsigned char u8;
struct Vector3 {
    float x, y, z;
};
extern float   g_f01687a48;          // 0x01687a48
extern float   g_f0169e278;          // 0x0169e278
extern int     g_i0156c194;          // 0x0156c194
extern float   g_f01582e68;          // 0x01582e68
void  normalized_safe(Vector3* out, const Vector3* in);        // 0x00449c20
class cPlanetModel {
public:
    void ToSurface(Vector3* out, const Vector3* in);            // 0x00b81630
    void DirectionToSurfacePosition(Vector3* out, const Vector3* in);  // 0x00b815a0
};
cPlanetModel* PlanetModel();                                   // 0x00b3d350
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
class cLocomotiveObject {
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
    virtual void* v2c();                    // +0x2c  GetPosition
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
    virtual bool v58();                     // +0x58
    virtual void* v5c(Vector3* out);        // +0x5c
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual void v70();
    virtual float v74();                    // +0x74  facing angle
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
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8();
    virtual void vec();                     // +0xec
    virtual void vf0();

    bool IsNearGoal();                      // 0x00c42e20
};
class cTribe;
class cSPCreatureBase {
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
virtual bool v2c();
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
    virtual void v84(int a, int b, int c);               // +0x84
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
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8(int a);
virtual void vec();
virtual void vf0();

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
class cTribe {
public:
    void SetStimuli(int a, int b, float c, void* d);     // 0x00c8f470
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
virtual void v00();
virtual void v04();
virtual void v08();
    virtual cSPCreatureBase* Lookup(int id);             // +0x0c
};
class cStimulus {
public:
    char pad00[0x0c];
    int  mField0c;                                       // +0x0c
    char pad10[0x1c];
    cStimulusPayload* mpPayload;                         // +0x2c
};
cSPCreatureBase* GetAnimalFromStimulus(void* stim);      // 0x00d99980
int    FUN_00c0b8e0(cSPCreatureBase* animal);            // 0x00c0b8e0
int    RandomUint32Uniform(int range);                   // 0x00a68fb0
void   FUN_00f924e0(float f);                            // 0x00f924e0
void   EatFood(cSPCreatureBase* self, const char* name, int a, int b);  // 0x00d85ad0
void   FUN_00d85540(cSPCreatureBase* self);              // 0x00d85540
void   FUN_00d39360(int event, void* data);              // 0x00d39360
void   NotifyEvent(float f);                             // 0x00d2e8a0
// ---- items of slice s00d70fe0 end

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
