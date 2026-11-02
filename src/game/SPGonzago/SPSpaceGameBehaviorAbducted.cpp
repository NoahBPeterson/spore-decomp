// src/game/SPGonzago/SPSpaceGameBehaviorAbducted.cpp -- migrated from slice(s) s010327b0, s01030b10 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceGameBehaviorAbducted.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureCitizen.h"

// unnamed retail callees and globals (address in the comment)
extern char DAT_016ded38[];
extern const float _HK_REAL_ONE;                            // 0x01485720 (1.0f)
extern const float _HK_REAL_ONE_HALF;                       // 0x01485548 (1.5f)
extern const float _HK_REAL_TWO;                            // 0x01470f1c (2.0f)
extern const float _HK_REAL_NEG_ONE;                        // 0x013eb1bc (-1.0f)
#include <math.h>
#include "SP/cInteraction.h"
#include "SP/cPlanetModel.h"

// ---- items of slice s01030b10 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef unsigned char uchar;
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Species;                                              // opaque species handle
struct Tuning {
    float GetLavaThreshold();                                // 0x01049bf0 (x87 return)
    float GetIceThreshold();                                 // 0x01049c40
};
Tuning* GetTuning();                                         // 0x01049a10
struct Terrain {
    bool IsInside(Species* s, const Vec3* pos);              // 0x00c7f430 ret 8
    bool IsNear(void* a, Vec3 pos);                          // 0x00c7f300 ret 0x10
};
struct Planet {
    Terrain* GetTerrain();                                   // 0x008414c0
    float    GetValueA();                                    // 0x00c70a20 (x87 return)
    float    GetValueB();                                    // 0x00c709d0
};
Planet* GetActivePlanet();                                   // 0x01021260
struct PlanetRecord { char pad[0x2c]; uint mFlags; };        // +0x2c: bit 0x800
PlanetRecord* GetActivePlanetRecord();                       // 0x010212a0
struct Body {                                                // id 0x116dd1b
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void v10();
    virtual uint GetModelKey();                              // 0x2c
virtual void v12();
virtual void v13();
    virtual void GetPosition(Vec3* out);                     // 0x38
};
struct Centered {
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
virtual void c5();
virtual void c6();
virtual void c7();
virtual void c8();
virtual void c9();
    virtual void c10();
    virtual const Vec3* GetCenter();                         // 0x2c
};
struct HitStats { char pad[0x25c]; float mRadius; };
struct Hit {
virtual void h0();
virtual void h1();
virtual void h2();
virtual void h3();
virtual void h4();
virtual void h5();
virtual void h6();
virtual void h7();
virtual void h8();
virtual void h9();
virtual void h10();
virtual void h11();
virtual void h12();
virtual void h13();
virtual void h14();
virtual void h15();
virtual void h16();
virtual void h17();
virtual void h18();
virtual void h19();
virtual void h20();
virtual void h21();
virtual void h22();
virtual void h23();
virtual void h24();
virtual void h25();
virtual void h26();
    virtual HitStats* GetStats();                            // 0x6c
    char     pad[0x120 - 4];
    Centered mCenter;                                        // +0x120
};
struct PlanetModelT {
    void  GetPos(Vec3* out, uint key);                       // 0x00b81630 ret 8
    float GetHeight(Vec3* pos, int mode);                    // 0x00b7e430 ret 8 (x87 return)
    Hit*  FindHit(Vec3* pos);                                // 0x00b894a0 ret 4
};
PlanetModelT* PlanetModel();                                 // 0x00b3d350
struct SlowDeath { void SetDeathType(int t); };              // 0x01034260 ret 4
struct Slow {
virtual void a0();
virtual void a1();
virtual void a2();
    virtual SlowDeath* Find(uint id);                        // 0x0c
};
struct SubObj {
virtual void s0();
virtual void s1();
virtual void s2();
    virtual void Notify(uint a, int b, int c);               // 0x0c
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
    virtual Slow* GetHandler();                              // 0x20
};
struct Blob { void Flush(); };                               // 0x00bcb3d0
struct FlagBlock { char pad[0x192]; uchar mFlag; };
struct Controller {                                          // id 0xd0036e08
    Species*   GetSpecies();                                 // 0x00c0bc00
    FlagBlock* GetFlags();                                   // 0x00c04590
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
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
    virtual void v20();
    virtual void Refresh();                                  // 0x54
};
struct Creature {                                            // id 0xce9f6639
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
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
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
    virtual void Stop(int a);                                // 0x9c
    char    pad0[0x58 - 4];
    SubObj  mSub;                                            // +0x58
    char    pad1[0xb4c - 0x58 - 4];
    Blob*   mBlob;                                           // +0xb4c
    bool    IsFlagged();                                     // 0x00c0b780
    void    SetPending(int v);                               // 0x00c14750 ret 4
};
void FUN_00c0d3a0(Creature* c);                              // cdecl
struct Trigger { bool IsSet(); };                            // id 0x4f176642: 0x00c232c0
struct Sense   { void* GetObject(Vec3* out); };              // id 0xaeb336b4: 0x00c3e1e0 ret 4
struct Agent {
virtual void a0();
virtual void a1();
    virtual void* GetInterface(uint id);                     // 0x08
};
struct Profile { char pad[0x608]; uint mA; uint mB; };       // +0x608 / +0x60c
struct SettingsMgr { Profile* GetProfile(Species* s); };     // 0x004df550 ret 4
SettingsMgr* Settings();                                     // 0x00401090
struct TerraMgr {
    int  GetScore(int planet);                               // 0x00bbc670 ret 4
    bool CheckA(Species* s, bool a, bool b, int c, bool* out);   // 0x00bbee30 ret 0x14
    bool CheckB(void* a, void* b, int c, bool* out);             // 0x00bbecc0 ret 0x10
};
TerraMgr* TerraformingManager();                             // 0x00b3d430
struct Spec {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
    virtual void s5();
    virtual void* GetKey();                                  // 0x18
    void* GetClass();                                        // 0x00b8f860
};
struct SpeciesMgr { Spec* GetSpeciesFromID(void* id); };     // 0x00b90410 ret 4
SpeciesMgr* FUN_00b3d420();
struct Mgr60 {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
virtual void m10();
virtual void m11();
virtual void m12();
virtual void m13();
virtual void m14();
virtual void m15();
virtual void m16();
virtual void m17();
virtual void m18();
virtual void m19();
virtual void m20();
virtual void m21();
virtual void m22();
virtual void m23();
    virtual void Fire(uint id, Vec3* pos, void* extra);      // 0x60
};
Mgr60* FUN_00b3d240();
struct Mgr2 { void Done(Creature* c); };                     // 0x00aca360 ret 4
Mgr2*  FUN_00b3d480();
struct EventLogT { void PostFeedbackEvent(uint id, uint a, int b, int c, int d, int e); };  // ret 0x18
EventLogT* EventLog();                                       // 0x00b3d3e0
int    GetCurrentGameMode();                                 // 0x00b5b800
struct Inventory;
struct Sim { Inventory* GetPlayerInventory(); };             // 0x00a1ad60
Sim*   GetUFOSimulator();                                    // 0x00ffbe50
extern uint DAT_016df328;
extern char DAT_016ded38[];
struct Abducted {
    char  pad0[0x74];
    bool  mField74;                                          // +0x74
    char  pad75[3];
    int   mField78;                                          // +0x78
    int   mField7c;                                          // +0x7c
    char  pad80[0x1c];
    void* mInventory;                                        // +0x9c
    bool  OnAgentHitsGround(Agent* agent, bool beam, bool flag);
    Agent* GetAgent();                                       // 0x00abf0b0
    void  SetState(int state);                               // 0x01030dd0
    int   CanJoin(int a, int b);                             // 0x01030df0
    void  AdjustRelationship();                              // 0x01030ef0
};
namespace __equiv_ann1 {
struct Blob {
    void Flush();   // 0x00c0b780 (equiv t3)
};
}
namespace __equiv_ann1 {
struct Mgr2 {
    void Done();   // 0x00aca360 (equiv t3)
};
}
namespace __equiv_ann1 {
struct SlowDeath {
    void SetDeathType();   // 0x01034260 (equiv t2)
};
}
extern const float _HK_REAL_ONE;                            // 0x01485720 (1.0f)
extern const float _HK_REAL_ONE_HALF;                       // 0x01485548 (1.5f)
extern const float _HK_REAL_TWO;                            // 0x01470f1c (2.0f)
extern const float _HK_REAL_NEG_ONE;                        // 0x013eb1bc (-1.0f)
struct PropertyObject;
struct InvSub {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
    virtual float GetValue();                              // +0x58
};
struct Inventory {
    char pad00[0x508];
    InvSub mSub;                                            // +0x508
    char pad50c[0x540 - 0x50c];
    float mField540;                                        // +0x540
};
struct SpaceObject {
    char pad00[0x508];
    InvSub mSub;                                            // +0x508
    char pad50c[0x540 - 0x50c];
    float mField540;                                        // +0x540
    char pad544[0x714 - 0x544];
    int mType714;                                           // +0x714
};
struct NounVector {
    void* mpUnused;                                         // +0x00
    SpaceObject** mpBegin;                                  // +0x04
    SpaceObject** mpEnd;                                    // +0x08
};
typedef bool (*NounFilter)(PropertyObject*);
struct TerrainSphere {
    bool Check();                                           // 0x00c75650
};
struct GameNounManager {
    NounVector* GetGameDataVector(NounFilter f1, NounFilter f2, NounFilter f3,
                                  NounFilter f4, unsigned id);     // 0x00b21340
    TerrainSphere* GetCurrentTerrainSphere();               // 0x00f67d90
};
GameNounManager* NounManager();                              // 0x00b3d300
namespace Simulator {
struct IRefCounted {
    virtual void AddRef();                                  // +0x00
};
}
namespace Simulator {
class cBeamLocomotionBase {
public:
    virtual void b00();
    int mField04;                                           // +0x04
};
}
namespace Simulator {
class cContentValidationSummarizer {
public:
    cContentValidationSummarizer() : mField4(0) {}
    virtual void c00();
    int mField4;                                            // +0x0c
};
}
namespace Simulator {
class cAbductionBeamLocomotion : public cBeamLocomotionBase,
                                 public cContentValidationSummarizer {
public:
    cAbductionBeamLocomotion(IRefCounted* target, bool flag);    // 0x01030e80
    IRefCounted* mpTarget;                                  // +0x10
    float mScale;                                           // +0x14
    bool  mFlag;                                            // +0x18
    float mRate;                                            // +0x1c
    bool  mEnabled;                                         // +0x20
};
}
struct City {
virtual void c00();
virtual void c01();
virtual void c02();
virtual void c03();
virtual void c04();
virtual void c05();
virtual void c06();
virtual void c07();
virtual void c08();
virtual void c09();
virtual void c10();
virtual void c11();
virtual void c12();
virtual void c13();
virtual void c14();
virtual void c15();
virtual void c16();
virtual void c17();
virtual void c18();
    virtual unsigned GetEmpireID();                         // +0x4c
    char pad04[0x120 - 0x04];
    Centered mCenter;                                       // +0x120
};
struct Citizen {
    City* GetCity();                                        // 0x00c23e40
};
struct RelationshipMgr {
    float RecordEvent(unsigned empire, unsigned eventID, float amount);   // 0x00d06240
};
RelationshipMgr* __stdcall RelationshipManager(unsigned empire);          // 0x00b3d2c0
unsigned GetPlayerEmpireID();                               // 0x01021090
void DoCommunityReaction(City* city, float amount, const Vec3* center);   // 0x00ff5270
// ---- items of slice s01030b10 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern uint DAT_016df328;

// ---- items of slice s010327b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_016ded38;              // 0x016ded38  default event origin, x
extern float g_016ded3c;              // 0x016ded3c  default event origin, y
extern float g_016ded40;              // 0x016ded40  default event origin, z
extern const float g_01470f1c;        // 0x01470f1c  2.0f
extern const float g_013ec4b4;        // 0x013ec4b4  0.9f
extern const float g_01485720;        // 0x01485720  1.0f
extern const float g_014996fc;        // 0x014996fc  FLT_MAX
extern const float g_013eb1bc;        // 0x013eb1bc  -1.0f
extern "C" void FUN_00f47380(void* p);       // 0x00f47380  operator delete[] (array form)
typedef void* Vp;
struct cVec3 {
    float x;
    float y;
    float z;
};
extern "C" Vp   FUN_00b3d260();              // 0x00b3d260  BehaviorManager accessor
extern "C" Vp   FUN_00b3d350();              // 0x00b3d350  PlanetModel accessor
struct cBehaviorHost {
    void F421B0(int flag);                   // 0x00c421b0
    void F41D60(void* value);                // 0x00c41d60
};
struct cPlanetModel {
    cVec3* DirectionToSurfacePosition(cVec3* out, void* value);   // 0x00b815a0
    cVec3* F81630(cVec3* out, void* value);                       // 0x00b81630
    float  F7E430(void* value, char flag);                        // 0x00b7e430
};
struct cAgentTargetA {
    unsigned char mPad00[0x34];               // +0x00
    cBehaviorHost mHost;                      // +0x34
    unsigned char mHostTail1[0x224 - 0x35];   // +0x35
    int  mField224;                           // +0x224  raycast result code
    unsigned char mHostTail2[0x528 - 0x228];  // +0x228
    unsigned char mbField528;                 // +0x528  cleared when the pass completes
    unsigned char mHostTail3[0x5e8 - 0x529];  // +0x529
    unsigned char mField5E8;                  // +0x5e8  attention sub-object
};
struct cAgentTargetB {
    unsigned char mPad00[0x34];               // +0x00
    cBehaviorHost mHost;                      // +0x34
    unsigned char mHostTail1[0x224 - 0x35];   // +0x35
    int  mField224;                           // +0x224  raycast result code
    unsigned char mHostTail2[0x5d0 - 0x228];  // +0x228
    unsigned char mField5D0;                  // +0x5d0  attention sub-object
};
struct cAgentExtra {
    unsigned char mPad00[0x660];              // +0x00
    float mf660;                              // +0x660
};
struct cAgentEvent {
    void* mpObject;              // +0x00  released through the array-delete path
    void* mpField04;             // +0x04  cleared
    void* mpField08;             // +0x08  cleared
    void* mpField0C;             // +0x0c
    void* mpField10;             // +0x10
    cVec3 mOrigin;               // +0x14
    float mf20;                  // +0x20
    void* mpField24;             // +0x24  cleared
    unsigned mField28;           // +0x28
    unsigned mField2C;           // +0x2c
    unsigned mField30;           // +0x30
    unsigned mField34;           // +0x34
    unsigned mField38;           // +0x38
    unsigned mField3C;           // +0x3c
    unsigned mField40;           // +0x40
    unsigned mField44;           // +0x44
    unsigned mField48;           // +0x48
    unsigned char mb4C;          // +0x4c  cleared
    unsigned char mb4D;          // +0x4d
    unsigned char mb4E;          // +0x4e
    unsigned char mb4F;          // +0x4f
    float mf50;                  // +0x50  cleared
    float mf54;                  // +0x54  cleared
    float mf58;                  // +0x58  cleared
    void* mpField5C;             // +0x5c  cleared
    float mf60;                  // +0x60
    float mf64;                  // +0x64
    float mf68;                  // +0x68
    float mf6C;                  // +0x6c  cleared
    void* mpField70;             // +0x70  cleared
};
struct cInteractionOwner {
    cVec3* F0FEE0(void** source);            // 0x00d0fee0
};
struct cAgentFilterRange {
    void* mpNoun;            // +0x00  noun owning the bit-pool agent table
    unsigned mId;            // +0x04  agent id: block = id >> 7, entry = id & 0x7f
    unsigned mField08;       // +0x08  forwarded unchanged
    unsigned mField0C;       // +0x0c  forwarded unchanged
    unsigned mField10;       // +0x10  forwarded unchanged
    unsigned mField14;       // +0x14  forwarded unchanged
};
struct cInteraction {
    unsigned char mPad00[0x80];              // +0x00
    cInteractionOwner mOwner;                // +0x80

    void RemoveAgent(cAgentFilterRange range);     // 0x00abedb0
    void TeardownAgent(cAgentFilterRange range);
};
static inline Vp VC0(void* p, int offset)
{
    return ((Vp(__thiscall*)(void*))(*(Vp**)p)[offset / 4])(p);
}
static inline Vp VC1P(void* p, int offset, void* arg)
{
    return ((Vp(__thiscall*)(void*, void*))(*(Vp**)p)[offset / 4])(p, arg);
}
static inline Vp VC1U(void* p, int offset, unsigned arg)
{
    return ((Vp(__thiscall*)(void*, unsigned))(*(Vp**)p)[offset / 4])(p, arg);
}
static inline void InitAgentEvent(cAgentEvent& ev)
{
    ev.mOrigin.x = g_016ded38;
    ev.mOrigin.y = g_016ded3c;
    ev.mOrigin.z = g_016ded40;
    ev.mf20 = g_01485720;
    ev.mf60 = g_01470f1c;
    ev.mf64 = g_013ec4b4;
    ev.mf68 = g_014996fc;
    ev.mpObject = 0;
    ev.mpField04 = 0;
    ev.mpField08 = 0;
    ev.mpField24 = 0;
    ev.mb4C = 0;
    ev.mf50 = 0.0f;
    ev.mf54 = 0.0f;
    ev.mf58 = 0.0f;
    ev.mpField5C = 0;
    ev.mf6C = 0.0f;
    ev.mpField70 = 0;
}
static inline void ReleaseAgentEvent(cAgentEvent& ev)
{
    void* p = ev.mpObject;
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        FUN_00f47380(p);
}
// ---- items of slice s010327b0 end

// @ 0x01030d50
float GetAbductionScale(unsigned id)
{
    float scale = _HK_REAL_ONE;
    if (id != 0x29c388a) {
        if (id == 0x3a8be428)
            scale = _HK_REAL_TWO;
    } else {
        scale = _HK_REAL_ONE_HALF;
    }
    return scale;
}

// @ 0x01030dd0
void Abducted::SetState(int state)
{
    mField7c = state;
    switch (state) {
    case 0:
        mField74 = true;
        break;
    case 1:
        mField74 = false;
        break;
    }
}

// @ 0x01030df0
int Abducted::CanJoin(int, int)
{
    return mField78 != 2 && mField7c != 2;
}

// @ 0x01030e80
namespace Simulator {
cAbductionBeamLocomotion::cAbductionBeamLocomotion(IRefCounted* target, bool flag)
{
    mpTarget = target;
    if (target)
        target->AddRef();
    mScale = _HK_REAL_NEG_ONE;
    mRate = _HK_REAL_ONE;
    mFlag = flag;
    mEnabled = true;
}
}  // namespace Simulator

// @ 0x01030ef0
void Abducted::AdjustRelationship()
{
    Agent* agent = GetAgent();
    if (!agent)
        return;
    Citizen* citizen = (Citizen*)agent->GetInterface(0x4f176642);
    if (!citizen)
        return;
    if (NounManager()->GetCurrentTerrainSphere()->Check())
        return;
    City* city = citizen->GetCity();
    if (!city)
        return;
    if (city->GetEmpireID() == GetPlayerEmpireID())
        return;
    float amount = RelationshipManager(city->GetEmpireID())->RecordEvent(
        GetPlayerEmpireID(), 0x526e5d4, 1.0f);
    DoCommunityReaction(city, amount, city->mCenter.GetCenter());
    EventLog()->PostFeedbackEvent(0x9ad9306e, 0x131a9f54, 0, 0, 1, 0);
}

// @ 0x01030fd0
bool Abducted::OnAgentHitsGround(Agent* agent, bool beam, bool flag)
{
    (void)beam;
    if (!agent) return true;
    Body* body = (Body*)agent->GetInterface(0x116dd1b);
    if (!body) return true;
    Creature*   creature = (Creature*)agent->GetInterface(0xce9f6639);
    Controller* ctl      = (Controller*)agent->GetInterface(0xd0036e08);
    Trigger*    trigger  = (Trigger*)agent->GetInterface(0x4f176642);
    Sense*      sense    = (Sense*)agent->GetInterface(0xaeb336b4);
    if (!sense && !creature) return true;

    Planet*  planet  = GetActivePlanet();
    Terrain* terrain = planet->GetTerrain();
    if (ctl) ctl->Refresh();

    Vec3 pos;
    PlanetModel()->GetPos(&pos, body->GetModelKey());
    body->GetPosition(&pos);

    int  score = TerraformingManager()->GetScore(0);
    bool noScore = (score == 0);
    bool out13 = noScore;
    bool scored = !noScore;

    float height = PlanetModel()->GetHeight(&pos, 1);
    bool lava;
    if (height > 0.0f && planet->GetValueA() > GetTuning()->GetLavaThreshold())
        lava = true;
    else
        lava = false;
    bool ice;
    if (height > 0.0f && planet->GetValueA() < GetTuning()->GetIceThreshold())
        ice = true;
    else
        ice = false;
    bool hasHeight = (height != 0.0f);

    bool near;
    Hit* hit = PlanetModel()->FindHit(&pos);
    if (hit) {
        const Vec3* c = hit->mCenter.GetCenter();
        Vec3 d;
        d.x = pos.x - c->x;
        d.y = pos.y - c->y;
        d.z = pos.z - c->z;
        near = hit->GetStats()->mRadius > sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
    } else {
        near = false;
    }

    bool hitTarget;
    if (!noScore) {
        if (ctl) {
            Species* sp = ctl->GetSpecies();
            Profile* prof = Settings()->GetProfile(sp);
            if (prof) {
                if (hasHeight && TerraformingManager()->CheckA(sp, prof->mB > 0, prof->mA > 0, 0, &out13))
                    scored = true;
                else
                    scored = false;
            }
        } else {
            if (!sense) goto no_hit;
            {
                Vec3 tmp;
                Spec* sp = FUN_00b3d420()->GetSpeciesFromID(sense->GetObject(&tmp));
                scored = TerraformingManager()->CheckB(sp->GetKey(), sp->GetClass(), 0, &out13);
            }
            goto try_sense;
        }
    }
    if (ctl) {
        if (terrain->IsInside(ctl->GetSpecies(), &pos)) goto hit_yes;
    }
try_sense:
    if (sense) {
        Vec3 tmp;
        if (terrain->IsNear(sense->GetObject(&tmp), pos)) goto hit_yes;
    }
no_hit:
    hitTarget = false;
    goto after_hit;
hit_yes:
    hitTarget = true;
after_hit:

    if (ctl && ctl->GetFlags())
        ctl->GetFlags()->mFlag = !scored;

    if (!hitTarget && !noScore && scored && !lava && hasHeight) {
        if (!flag) return true;
        if (!creature) return true;
    }

    uint evA = 0, evB = 0;
    if (lava) {
        if (creature) evB = 0x6addd9bc;
        else if (!sense) return hitTarget;
        else { evA = 0xe4141994; evB = 0xf8b7cb07; }
    } else if (!hasHeight && !ice) {
        if (creature) evB = 0xd4495c37;
        else if (!sense) return hitTarget;
        else { evA = 0x534a52c0; evB = 0x6843ead6; }
    } else if (flag && creature) {
        evB = 0xf804e08c;
    } else if (scored) {
        if (hitTarget) evB = 0x27d13994;
    } else {
        if (sense) {
            evA = 0x33ce359;
            if (noScore) {
                float da = (float)fabs(planet->GetValueA() - 0.5f);
                float db = (float)fabs(planet->GetValueB() - 0.5f);
                if (da >= db)
                    evA = (0.5f > planet->GetValueA()) ? 0x4fd21bbc : 0xd3520187;
                else
                    evA = (0.5f > planet->GetValueB()) ? 0xf7129557 : 0xed8c1210;
            }
        }
        if (!trigger) {
            if (!out13) {
                if (creature) {
                    if (GetActivePlanetRecord()->mFlags & 0x800)
                        evB = 0xcd46959;
                    else
                        evB = (creature->IsFlagged() ? 0x9d6d92a3 : 0) + 0xca1ad72a;
                } else if (sense) {
                    evB = 0x7e1fde15;
                }
            } else {
                evB = ((uint)(score >= 3) - 1 & 0x45acd817) + 0x99f93d3d;
            }
        }
    }

    if (evA) {
        Mgr60* mgr = FUN_00b3d240();
        float len2 = pos.x * pos.x + pos.z * pos.z + pos.y * pos.y;
        float inv = (float)(1.0 / sqrt(len2 + 1e-8f));
        Vec3 dir;
        dir.x = inv * pos.x;
        dir.y = pos.y * inv;
        dir.z = pos.z * inv;
        mgr->Fire(evA, &pos, &dir);
    }
    if (evB) {
        if (GetCurrentGameMode() == 0x1654c05) {
            void* inv = this->mInventory;
            if (inv == GetUFOSimulator()->GetPlayerInventory())
                EventLog()->PostFeedbackEvent(evB, 0x131a9f54, 0, 0, 1, 0);
        }
    }

    if (!creature) return hitTarget;
    creature->Stop(0);
    if (trigger) {
        if (trigger->IsSet()) {
            FUN_00c0d3a0(creature);
            if (creature->mBlob) creature->mBlob->Flush();
        }
        if (hasHeight && near && !flag) return true;
    }

    int code = 0;
    if (lava) {
        code = 8;
    } else if (!hasHeight && !ice) {
        code = 7;
    } else if (flag) {
        code = 1;
    } else if (noScore) {
        float da = (float)fabs(planet->GetValueA() - 0.5f);
        float db = (float)fabs(planet->GetValueB() - 0.5f);
        if (da >= db)
            code = (0.5f > planet->GetValueA()) ? 2 : 3;
        else
            code = (0.5f > planet->GetValueB()) ? 4 : 5;
    } else if ((!trigger && !scored) || out13) {
        code = 6;
    }

    if (hasHeight && near && !flag) {
        creature->SetPending(1);
        body->GetPosition(&pos);
        FUN_00b3d240()->Fire(0x2818ee0, &pos, DAT_016ded38);
        FUN_00b3d480()->Done(creature);
        return true;
    }
    if (code) {
        SubObj* sub = &creature->mSub;
        sub->Notify(DAT_016df328, 0, 0);
        Slow* h = sub->GetHandler();
        if (h) {
            SlowDeath* sd = h->Find(0x3cdbbe9);
            if (sd) sd->SetDeathType(code);
        }
        return false;
    }
    if (trigger) return true;
    return hitTarget;
}

// @ 0x010327b0
void cInteraction::TeardownAgent(cAgentFilterRange range)
{
    // The noun owns a table of bit-pool blocks; block[id >> 7] holds 0x80 eight-byte agent
    // entries and the handle lives in the second dword of entry[id & 0x7f].
    void** pools = *(void***)range.mpNoun;
    void** block = (void**)pools[range.mId >> 7];
    void* agent = block[(range.mId & 0x7f) * 2 + 1];

    RemoveAgent(range);

    if (agent == 0)
        return;

    cVec3 surfaceDir;

    // ---- first hash: 0xce9f6639 -------------------------------------------------------------
    Vp obj1 = VC1U(agent, 0x08, 0xce9f6639u);
    if (obj1 != 0) {
        VC0(obj1, 0x00);            // AddRef
        VC1U(obj1, 0x9c, 0);        // clear one flag
        VC0(obj1, 0x54);            // refresh
    }

    // ---- second hash: 0xaeb336b4 ------------------------------------------------------------
    Vp obj2 = VC1U(agent, 0x08, 0xaeb336b4u);
    if (obj2 != 0) {
        cAgentTargetA* target = (cAgentTargetA*)obj2;

        VC0(obj2, 0x00);            // AddRef

        Vp mgr = FUN_00b3d260();    // BehaviorManager
        VC1P(mgr, 0x3c, &target->mField5E8);

        target->mHost.F421B0(0);

        Vp value = VC0(&target->mHost, 0x2c);
        cPlanetModel* planet = (cPlanetModel*)FUN_00b3d350();
        cVec3* dir = planet->DirectionToSurfacePosition(&surfaceDir, value);
        VC1P(&target->mHost, 0x38, dir);

        target->mField224 = 0;

        cAgentEvent event;
        InitAgentEvent(event);
        VC1P(&target->mHost, 0xdc, &event);
        ReleaseAgentEvent(event);

        target->mHost.F41D60(&g_016ded38);

        Vp source = VC0(&target->mHost, 0x2c);
        cVec3* slot = mOwner.F0FEE0(&obj2);
        *slot = *(const cVec3*)source;

        target->mbField528 = 0;
    }

    // ---- third hash: 0x283d961 --------------------------------------------------------------
    Vp obj3 = VC1U(agent, 0x08, 0x283d961u);
    if (obj3 != 0) {
        cAgentTargetB* target = (cAgentTargetB*)obj3;

        VC0(obj3, 0x00);            // AddRef

        Vp mgr = FUN_00b3d260();    // BehaviorManager
        VC1P(mgr, 0x3c, &target->mField5D0);

        target->mHost.F421B0(0);

        Vp value = VC0(&target->mHost, 0x2c);
        cPlanetModel* planet = (cPlanetModel*)FUN_00b3d350();
        cVec3* dir = planet->F81630(&surfaceDir, value);
        VC1P(&target->mHost, 0x38, dir);

        Vp probe = VC0(&target->mHost, 0x2c);
        float distance = ((cPlanetModel*)FUN_00b3d350())->F7E430(probe, 1);
        target->mField224 = (distance > 0.0f) ? 6 : 0;

        cAgentEvent event;
        InitAgentEvent(event);
        VC1P(&target->mHost, 0xdc, &event);
        ReleaseAgentEvent(event);

        target->mHost.F41D60(&g_016ded38);

        Vp extra = VC1U(obj3, 0x0c, 0x2dd8c33u);
        if (extra != 0)
            ((cAgentExtra*)extra)->mf660 = g_013eb1bc;

        VC0(obj3, 0x04);            // Release
    }

    if (obj2 != 0)
        VC0(obj2, 0x04);            // Release
    if (obj1 != 0)
        VC0(obj1, 0x04);            // Release
}
