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

// @ 0x00d71f80
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
