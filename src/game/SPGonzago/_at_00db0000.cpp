// src/game/SPGonzago/_at_00db0000.cpp -- migrated from slice(s) s00dbf0c0, s00dbe140 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00db0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"

// unnamed retail callees and globals (address in the comment)
extern "C" double __cdecl sqrt(double);
extern const float kOne;                      // 0x01485720 = 1.0f
extern const float kEps;                      // 0x0147c304
extern const float kUfoAltitudeA;             // 0x0159d5a0
extern const float kUfoScaleA;                // 0x0159d5a4
extern const float kUfoScaleB;                // 0x0159d5a8
extern const float kUfoScaleC;                // 0x0159d5d0
extern const float kUfoScaleD;                // 0x0159d5d4
extern const float kThree;                    // 0x013eb95c = 3.0f

// ---- items of slice s00dbe140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
struct UfoComponent {
virtual void u00();
virtual void u04();
virtual void u08();
virtual void u0c();
    virtual int  u10();                       // +0x10
virtual void u14();
virtual void u18();
virtual void u1c();
virtual void u20();
virtual void u24();
virtual void u28();
virtual void u2c();
virtual void u30();
virtual void u34();
    virtual void u38();                       // +0x38
virtual void u3c();
virtual void u40();
virtual void u44();
virtual void u48();
    virtual void u4c();
    virtual void u50(int arg);                // +0x50
    int  GetFileCount();                      // 0x008e7f80
    char mPad[0x38 - 0x04];
};
struct UfoBehaviour {
    char pad000[0x508];
    UfoComponent mSelf;                       // +0x508
    float mField540;                          // +0x540
    int mField544;                            // +0x544
    char pad548[0x624 - 0x548];
    uint8_t mField624;                        // +0x624
    char pad625[0x6b4 - 0x625];
    float mField6b4;                          // +0x6b4
    float mField6b8;                          // +0x6b8
    char pad6bc[0x718 - 0x6bc];
    float mPos[3];                            // +0x718
    void SetOrigin(const float* p);           // 0x00c3be70 (ret 4)
    void SetAltitude(float v);                // 0x00c3daa0 (ret 4)
    bool FUN_00c372b0();                      // 0x00c372b0
    uint32_t FUN_00c37260();                  // 0x00c37260
    void FUN_00c37270();                      // 0x00c37270
    void* FUN_00c38b80();                     // 0x00c38b80
    void  FUN_00c38b90();                     // 0x00c38b90
};
struct UfoInventory {
    char pad000[0x508];
    UfoComponent mSelf;                       // +0x508
    bool IsInvalid(int a);                    // 0x00c38990
};
struct UfoSim {
    UfoInventory* GetPlayerInventory();       // 0x00a1ad60
};
struct EmpireRef {
virtual void r00();
virtual void r04();
virtual void r08();
virtual void r0c();
virtual void r10();
virtual void r14();
virtual void r18();
virtual void r1c();
virtual void r20();
virtual void r24();
virtual void r28();
virtual void r2c();
virtual void r30();
virtual void r34();
virtual void r38();
virtual void r3c();
virtual void r40();
virtual void r44();
virtual void r48();
    virtual int  GetEmpireID();               // +0x4c
};
struct Empire {
    bool IsAtWarWithPlayer();                 // 0x00c31640
};
struct RelMgr {
    bool IsAllied(int a, int b);              // 0x00d01fb0 (ret 8)
};
struct TriggerMgr {
    char    pad00[0x28];
    uint8_t mField28;                         // +0x28
    char    pad29[0x2c - 0x29];
    int     mField2c;                         // +0x2c
};
struct PlanetModelObj {
    float GetRadiusAt(const float* pos);      // 0x00b7ef70 (ret 4)
    float GetWaterHeight2();                  // 0x00b7e4d0
};
struct PlanetRecord {
    int GetKind();                            // 0x00b8dab0
};
struct MissionRecord {
    void* GetAvatar();                        // 0x00b1fdb0
};
struct StarMgrObj {
    Empire* GetEmpireByID(int id);            // 0x00ba9370 (ret 4)
};
void*  __cdecl GetCurrentGameMode();          // 0x00b5b800
int    __cdecl GetPlayerEmpireID();           // 0x01021090
RelMgr* __cdecl RelationshipMgr();            // 0x00b3d2c0
TriggerMgr* __cdecl GetTriggerMgr();          // 0x00b3d4d0
UfoSim* __cdecl GetUFOSimulator();            // 0x00ffbe50
PlanetModelObj* __cdecl PlanetModel();        // 0x00b3d350
StarMgrObj* __cdecl StarManager();            // 0x00b3d2a0
PlanetRecord* __cdecl GetActivePlanetRecord();// 0x010212a0
MissionRecord* __cdecl GetMissionRecord();    // 0x01021240
extern const float kOne;                      // 0x01485720 = 1.0f
extern const float kEps;                      // 0x0147c304
extern const float kUfoAltitudeA;             // 0x0159d5a0
extern const float kUfoScaleA;                // 0x0159d5a4
extern const float kUfoScaleB;                // 0x0159d5a8
extern const float kUfoScaleC;                // 0x0159d5d0
extern const float kUfoScaleD;                // 0x0159d5d4
extern const float kThree;                    // 0x013eb95c = 3.0f
// ---- items of slice s00dbe140 end

// ---- items of slice s00dbf0c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_169f754;                                 // 0x0169f754 k_placeembassy_0169f754
typedef unsigned int uint32;
float MathSqrt(float v);                              // = sqrtf
float MathSin(float v);                               // = sinf
float MathCos(float v);                               // = cosf
struct Behaviour;
struct Spatial {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
    virtual const float* Slot2c();                    // +0x2c  position
};
struct Handle120 {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
    virtual const float* Pose(int a, int b);          // +0x2c
};
struct CombatObj {
    char pad000[0x220];
    float mHull;                                      // +0x220
    bool DamageTest(int a);                           // 0x00c004c0
};
struct TargetObj {
    bool Active(int a);                               // 0x00c38990
};
struct SimObj {
    void SetTracked(void* e);                         // 0x01001700
};
struct Component {
    virtual void slot00();                            // +0x00  AddRef
    virtual void slot04();                            // +0x04  Release
    virtual void slot08();                            // +0x08
    virtual void* Cast(uint32 typeId);                // +0x0c
virtual void s10b();
virtual void s14b();
virtual void s18b();
virtual void s1cb();
    virtual void* Slot20();                           // +0x20
virtual void s24b();
virtual void s28b();
    virtual bool IsReady();                           // +0x2c
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
    virtual void* Slot4c();                           // +0x4c
    virtual void  Slot50(void* p);                    // +0x50
    virtual void* Slot54();                           // +0x54
virtual void  s58();
virtual void s5c();

    // 0x00bfc600 -- bounds/validity check on this component (thiscall)
    bool CheckAlive();
    // 0x00bfc490 -- scalar metric of this component (thiscall)
    float Metric();
};
struct EntityRoot {
virtual void e00();
virtual void e04();
virtual void e08();
virtual void e0c();
virtual void e10();
virtual void e14();
virtual void e18();
virtual void e1c();
virtual void e20();
virtual void e24();
virtual void e28();
virtual void e2c();
virtual void e30();
virtual void e34();
virtual void e38();
virtual void e3c();
virtual void e40();
virtual void e44();
virtual void e48();
    virtual void* Slot4c(void* a);                    // +0x4c
    virtual void  Slot50(void* p);                    // +0x50
    virtual void* Slot54();                           // +0x54
};
struct Behaviour : EntityRoot {
    char pad004[0x34 - 0x04];
    Spatial mSpatial;                                 // +0x34  (vtable at +0x34)
    char pad038[0x508 - 0x38];
    Component mSelf;                                  // +0x508 (vtable at +0x508)
    char pad50c[0x624 - 0x50c];
    uint8_t flag624;                                  // +0x624
    char pad625[0x68c - 0x625];
    void* mpTarget;                                   // +0x68c
    uint8_t b690;                                     // +0x690
    uint8_t b691;                                     // +0x691
    char pad692[0x6b4 - 0x692];
    float f6b4;                                       // +0x6b4
    float f6b8;                                       // +0x6b8
    char pad6bc[0x710 - 0x6bc];
    void* mpCommTarget;                               // +0x710
    uint32 kind;                                      // +0x714
    float pos[3];                                     // +0x718
    char pad724[0x748 - 0x724];
    float f748;                                       // +0x748
    int i74c;                                         // +0x74c
    char pad750[0x800 - 0x750];

    // helpers implemented outside the slice (thiscall, hence members)
    Component* GetTargetComponent();                  // 0x00c38b00
    void       ReleaseTargetComponent();              // 0x00c38b10
    Component* GetService();                          // 0x00c38b80
    void       SetOrigin(const float* p);             // 0x00c3be70
    void       SetTarget(void* t);                    // 0x00c3b700
    void       SetAltitude(float v);                  // 0x00c3daa0
};
struct BehaviourState {
    float f00;                                        // +0x00  angle accumulator
    float f04;                                        // +0x04  radius scale
    float f08;                                        // +0x08  vertical scale
    int   state;                                      // +0x0c  0 = idle, 3 = running
    float timer;                                      // +0x10
};
#define FLAG_BIT12 0x1000u
bool   __cdecl f_00c37890(Behaviour* o, void* t, int a); // 0x00c37890
void*  __cdecl f_00c389c0(Behaviour* o, int a, int b); // 0x00c389c0
void   __cdecl f_00c3a930(Behaviour* o, void* t, int a); // 0x00c3a930
void*  __cdecl f_00cc26a0(float x, float y, float z); // 0x00cc26a0
void*  __cdecl f_00d997e0(void* stimuli);             // 0x00d997e0 behaviour_stimuli::GetAny
void*  __cdecl f_0102c340(Behaviour* o, int a);       // 0x0102c340
bool   __cdecl f_0102aa50(void* t, Behaviour* o, bool f); // 0x0102aa50 cSPSpaceCommCanTarget
void*  __cdecl f_0102bc90(Behaviour* o, int a, int b);   // 0x0102bc90 SP::GetBestUFOTarget
void*  __cdecl f_01029940(int kind);                  // 0x01029940 GetSpaceCombatTuning
double __cdecl f_0102a8f0(void* tuning);              // 0x0102a8f0 GetLootMoneyChance2
bool   __cdecl f_01029a10(void* planet, void* record);   // 0x01029a10 IsValidSpaceCommTarget
void*  __cdecl f_01021090();                          // 0x01021090 GetPlayerEmpireID
void*  __cdecl f_010212a0();                          // 0x010212a0 GetActivePlanetRecord
void*  __cdecl f_01021300();                          // 0x01021300 GetPlayerEmpire
void*  __cdecl f_00bddd10(void* sim);                 // 0x00bddd10
void*  __cdecl f_00b3d2a0(uint32 empireId);           // 0x00b3d2a0 SP::StarManager
void*  __cdecl f_00ba9370(void* mgr, uint32 empireId);// 0x00ba9370 cStarManager::GetEmpireByID
void*  __cdecl f_00a206f0();                          // 0x00a206f0 EA::Audio::GetSystemAT
void*  __cdecl f_00435ed0(uint32 setId, void* system); // 0x00435ed0 cSPUISpace::KillSetiEffects
void*  __stdcall f_00b3d350(float* p);                // 0x00b3d350 SP::PlanetModel (callee pops)
namespace SP {
 struct cPlanetModel_s00db_f0c0 { float GetRadiusAt(); };   // 0x00b7ef70
}
void   __cdecl f_00436ce0(const float* src, float* dst);      // 0x00436ce0 Vector3_Normalize
void*  __cdecl f_006985b0(const float* src, float* dst);      // 0x006985b0 SP::OrthogonalVector
void*  __cdecl f_00449c20(const float* src, float* dst);      // 0x00449c20 SP::normalized_safe
void*  __cdecl f_00cc15b0(char* entity, void* calc);  // 0x00cc15b0
void*  __cdecl f_00ffbe50();                          // 0x00ffbe50 SP::GetUFOSimulator
void*  __cdecl f_00ffc320(void* sim);                 // 0x00ffc320
struct Rng { double Uniform(); };
extern Rng g_1601760;                                 // 0x01601760
struct HandleLess {
    char pad[0x120];
};
struct Comparator {
    bool Less(const HandleLess* a, const HandleLess* b);   // 0x00ac0730
};
static inline const HandleLess* prio(const void* p) {
    return p ? (const HandleLess*)((const char*)p + 0x120) : 0;
}
static inline float MathSqrt(float v) { return v < 0.0f ? 0.0f : v; }
static const uint32 kSetiByType[9] = {
    0xef2fc9e8u, 0x94a77229u, 0xe4129110u, 0x6139d767u, 0x6263b501u,
    0x367a1940u, 0x62d3be51u, 0x0199e701u, 0x7aa79140u,
};
// ---- items of slice s00dbf0c0 end

// @ 0x00dbec30
float __cdecl FUN_00dbec30()
{
    float r;
    if (GetCurrentGameMode() == (void*)0x1654c05) r = kOne;
    else r = 0.0f;
    return r;
}

// @ 0x00dbec60
float __cdecl FUN_00dbec60()
{
    float r;
    if (GetCurrentGameMode() == (void*)0x1654c01
        || GetCurrentGameMode() == (void*)0x1654c02) r = kOne;
    else r = 0.0f;
    return r;
}

// @ 0x00dbeca0
float __cdecl FUN_00dbeca0(UfoBehaviour* self)
{
    float r;
    if (self->mField540 <= kEps) r = kOne;
    else r = 0.0f;
    return r;
}

// @ 0x00dbece0
float __cdecl FUN_00dbece0()
{
    TriggerMgr* tm = GetTriggerMgr();
    float r;
    if (tm->mField2c == 2 && tm->mField28 == 0) r = kOne;
    else r = 0.0f;
    return r;
}

// @ 0x00dbed20
float __cdecl FUN_00dbed20(UfoBehaviour* self)
{
    if (self->FUN_00c372b0() && self->FUN_00c37260() > 30000) return 1.0f;
    return 0.0f;
}

// @ 0x00dbed50
float __cdecl FUN_00dbed50(UfoBehaviour* self)
{
    if (self->FUN_00c372b0()) return 1.0f;
    return 0.0f;
}

// @ 0x00dbed70
float __cdecl FUN_00dbed70(EmpireRef* obj)
{
    int const id = obj->GetEmpireID();
    if (id != GetPlayerEmpireID()) {
        if (!RelationshipMgr()->IsAllied(obj->GetEmpireID(), GetPlayerEmpireID())) return 1.0f;
    }
    return 0.0f;
}

// @ 0x00dbedc0
float __cdecl FUN_00dbedc0(UfoBehaviour* self, int a2, int a3, uint32_t flags)
{
    (void)a2; (void)a3;
    uint32_t const t = flags >> 0xd;
    if (!(t & 1)) {
        int const id = self->mField544;
        UfoInventory* inv = GetUFOSimulator()->GetPlayerInventory();
        if (!inv->IsInvalid(1)) {
            if (id == inv->mSelf.u10()) return 1.0f;
        }
        return 0.0f;
    }
    self->mSelf.u38();
    return 0.0f;
}

// @ 0x00dbee30
float __cdecl FUN_00dbee30()
{
    float r;
    if (GetActivePlanetRecord()->GetKind() != 5) r = kOne;
    else r = 0.0f;
    return r;
}

// @ 0x00dbee70
float __cdecl FUN_00dbee70(EmpireRef* obj)
{
    void* avatar = GetMissionRecord()->GetAvatar();
    Empire* a = StarManager()->GetEmpireByID((int)avatar);
    int const id = obj->GetEmpireID();
    Empire* b = StarManager()->GetEmpireByID(id);
    if (a && a != b) return 1.0f;
    float r;
    if (b && !b->IsAtWarWithPlayer()) r = kOne;
    else r = 0.0f;
    return r;
}

// @ 0x00dbeef0
float __cdecl FUN_00dbeef0(UfoBehaviour* self)
{
    if (self->FUN_00c38b80()) return 1.0f;
    return 0.0f;
}

// @ 0x00dbef10
char __cdecl FUN_00dbef10(UfoBehaviour* self)
{
    return self->mSelf.GetFileCount() == 2;
}

// @ 0x00dbef30
void __cdecl FUN_00dbef30(UfoBehaviour* self)
{
    if (self->FUN_00c38b80()) self->FUN_00c38b90();
    self->mSelf.u50(0);
}

// @ 0x00dbef60
bool __cdecl FUN_00dbef60(UfoBehaviour* self)
{
    self->SetOrigin(&self->mPos[0]);
    self->mField624 = 1;
    float const r = PlanetModel()->GetRadiusAt(&self->mPos[0]) + kUfoAltitudeA;
    self->SetAltitude(r);
    self->mField6b4 = kUfoScaleA;
    self->mField6b8 = kUfoScaleB;
    return true;
}

// @ 0x00dbefc0
void __cdecl FUN_00dbefc0(UfoBehaviour* self)
{
    self->mField6b4 = 1.0f;
    self->mField6b8 = 1.0f;
}

// @ 0x00dbefe0
bool __cdecl FUN_00dbefe0(UfoBehaviour* self)
{
    if (!self->FUN_00c372b0()) self->FUN_00c37270();
    return true;
}

// @ 0x00dbf000
bool __cdecl FUN_00dbf000(UfoBehaviour* self, int a2, int a3, int a4, int a5, float* out)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
    float* const pos = &self->mPos[0];
    self->SetOrigin(pos);
    float const r = (float)sqrt((double)pos[0] * pos[0]
                                + (double)pos[1] * pos[1]
                                + (double)pos[2] * pos[2]);
    self->SetAltitude(r);
    out[1] = kOne;
    out[0] = kThree;
    return true;
}

// @ 0x00dbf060
bool __cdecl FUN_00dbf060(UfoBehaviour* self)
{
    self->SetOrigin(&self->mPos[0]);
    self->mField624 = 1;
    float const r = PlanetModel()->GetWaterHeight2() + kUfoAltitudeA;
    self->SetAltitude(r);
    self->mField6b4 = kUfoScaleC;
    self->mField6b8 = kUfoScaleD;
    return true;
}

// @ 0x00dbf0c0
void f_00dbf0c0(Behaviour* self)
{
    Component* c = self->GetTargetComponent();
    if (c != 0) {
        if (!c->IsReady())
            self->ReleaseTargetComponent();
    }
    self->f6b4 = 1.0f;
    self->f6b8 = 1.0f;
}

// @ 0x00dbf100
bool f_00dbf100(Behaviour* self)
{
    self->ReleaseTargetComponent();
    return false;
}

// @ 0x00dbf110
bool f_00dbf110(Behaviour* self)
{
    if (!self->mSelf.CheckAlive())
        return false;
    self->SetOrigin(&self->pos[0]);
    return true;
}

// @ 0x00dbf140
bool f_00dbf140(Behaviour* self, int a1, int a2, int a3, int a4, int a5, int a6)
{
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5;
    if (a6 != 0)
        self->SetTarget(*(void**)(a6 + 8));
    return false;
}

// @ 0x00dbf160
void f_00dbf160(Behaviour* self)
{
    self->f6b4 = 1.0f;
    self->f6b8 = 1.0f;
    self->b690 = 0;
    self->b691 = 0;
    self->SetOrigin(&self->pos[0]);
    self->SetTarget(0);
    self->mSelf.Slot50(0);
}

// @ 0x00dbf1c0
bool f_00dbf1c0(Behaviour* self)
{
    if (self->kind == 3) {
        void* e = self->Slot4c(0);
        ((SimObj*)f_00ffbe50())->SetTracked(e);
    }
    return true;
}

// @ 0x00dbf1f0
bool f_00dbf1f0(Behaviour* self)
{
    f_0102c340(self, 0);
    return true;
}

// @ 0x00dbf210
bool f_00dbf210(Behaviour* self, int a1, int a2, int a3, int a4, BehaviourState* out)
{
    (void)self; (void)a1; (void)a2; (void)a3; (void)a4;
    out->f00 = 2.5f;
    *(unsigned char*)&out->f04 = 0;
    *(uint32*)&out->f08 = 0;
    return true;
}

// @ 0x00dbf230
void* f_00dbf230(const void* a1, const void* a2, const void* a3, Comparator cmp)
{
    if (cmp.Less(prio(a1), prio(a2))) {
        if (!cmp.Less(prio(a2), prio(a3)))
            return cmp.Less(prio(a1), prio(a3)) ? (void*)a3 : (void*)a1;
        return (void*)a2;
    }
    if (cmp.Less(prio(a1), prio(a3)))
        return (void*)a1;
    if (cmp.Less(prio(a2), prio(a3)))
        return (void*)a3;
    return (void*)a2;
}

// @ 0x00dbf340
float f_00dbf340(Behaviour* self)
{
    Component* c = self->GetTargetComponent();
    if (c != 0) {
        Component* t = (Component*)c->Cast(0xb033b403);
        if (t != 0) {
            if (t->IsReady()) {
                self->ReleaseTargetComponent();
                return 0.0f;
            }
            if (t->IsReady())
                return 0.0f;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00dbf3c0
float f_00dbf3c0(Behaviour* self, int a2, int a3, uint32 flags, void* stimuli, uint8_t* out)
{
    (void)a2; (void)a3;
    Component* c = self->GetTargetComponent();
    if (c == 0)
        return 0.0f;
    void* obj = c->Cast(0xee9b2232);
    if (obj == 0)
        return 0.0f;

    Handle120* h = (Handle120*)((char*)obj + 0x120);
    const float* mine = h->Pose((flags >> 12) & 1, (flags >> 14) & 1);
    void* target = f_00cc26a0(mine[0], mine[1], mine[2]);
    if (target == 0)
        return 0.0f;

    const float* theirs = ((Spatial*)((char*)target + 0x34))->Slot2c();
    float dx = theirs[0] - mine[0];
    float dy = theirs[1] - mine[1];
    float dz = theirs[2] - mine[2];
    if (MathSqrt(dx * dx + dy * dy + dz * dz) < 1000.0f) {
        if (stimuli != 0)
            f_00d997e0(stimuli);
        *(void**)((char*)stimuli + 4) = (char*)target + 0x508;
        *out = 1;
        return 1.0f;
    }
    return 0.0f;
}

// @ 0x00dbf4b0
float f_00dbf4b0(Behaviour* self, int a2, int a3, uint32 flags, void* stimuli, uint8_t* out)
{
    (void)a2; (void)a3;
    int bit = (flags & FLAG_BIT12) != 0;
    void* target = (void*)f_0102bc90(self, bit, 0);   /* returns the chosen object */

    float range = 1000.0f;
    if (self->kind == 5)
        range = 230.0f;

    if (target != 0) {
        const float* tpos = ((Spatial*)((char*)target + 8))->Slot2c();
        const float* mpos = self->mSpatial.Slot2c();
        float dx = tpos[0] - mpos[0];
        float dy = tpos[1] - mpos[1];
        float dz = tpos[2] - mpos[2];
        if (MathSqrt(dx * dx + dy * dy + dz * dz) < range) {
            if (stimuli != 0)
                f_00d997e0(stimuli);
            *(void**)((char*)stimuli + 4) = target;
            *out = 1;
            return 1.0f;
        }
    }

    if (self->mpCommTarget != 0) {
        if (f_0102aa50(self->mpCommTarget, self, bit)) {
            if (stimuli != 0)
                f_00d997e0(stimuli);
            void* t = self->mpCommTarget;
            *(void**)((char*)stimuli + 4) = t ? (char*)t + 0x508 : 0;
            *out = 1;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00dbf5e0
float f_00dbf5e0(Behaviour* self, int a2, int a3, uint32 flags, void* stimuli, uint8_t* out)
{
    (void)a2; (void)a3;
    if (self->mpTarget == 0 || ((Behaviour*)self->mpTarget)->kind != 4)
        return 0.0f;

    int bit = (flags & FLAG_BIT12) != 0;
    void* target = (void*)f_0102bc90(self, bit, 0);

    if (target != 0) {
        Behaviour* owner = (Behaviour*)self->mpTarget;
        const float* tpos = ((Spatial*)((char*)target + 8))->Slot2c();
        const float* mpos = owner->mSpatial.Slot2c();
        float dx = tpos[0] - mpos[0];
        float dy = tpos[1] - mpos[1];
        float dz = tpos[2] - mpos[2];
        if (MathSqrt(dx * dx + dy * dy + dz * dz) < 230.0f) {
            if (stimuli != 0)
                f_00d997e0(stimuli);
            *(void**)((char*)stimuli + 4) = target;
            *out = 1;
            return 1.0f;
        }
    }

    void* comm = ((Behaviour*)self->mpTarget)->mpCommTarget;
    if (comm != 0) {
        if (f_0102aa50(comm, self, bit)) {
            if (stimuli != 0)
                f_00d997e0(stimuli);
            void* t = ((Behaviour*)self->mpTarget)->mpCommTarget;
            *(void**)((char*)stimuli + 4) = t ? (char*)t + 0x508 : 0;
            *out = 1;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00dbf710
float f_00dbf710(Behaviour* self)
{
    Component* c = self->GetTargetComponent();
    if (c != 0) {
        CombatObj* o = (CombatObj*)c->Cast(0xee9b2232);
        if (o != 0) {
            if (o->DamageTest(0) || o->mHull > 0.0f)
                return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00dbf760
float f_00dbf760(Behaviour* self)
{
    Component* c = self->GetTargetComponent();
    if (c != 0) {
        CombatObj* o = (CombatObj*)c->Cast(0xee9b2232);
        if (o != 0) {
            if (o->DamageTest(0) || 0.0f < o->mHull)
                return 0.0f;
        }
    }
    return 1.0f;
}

// @ 0x00dbf7b0
float f_00dbf7b0(Behaviour* self)
{
    if (self->kind != 4) {
        if (self->mSelf.Metric() <= 0.2f) {
            if (g_1601760.Uniform() < 0.85f)
                return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00dbf810
float f_00dbf810(Behaviour* self)
{
    return self->mpTarget == 0 ? 1.0f : 0.0f;
}

// @ 0x00dbf840
float f_00dbf840(Behaviour* self)
{
    if (self->mpTarget != 0) {
        if (((TargetObj*)self->mpTarget)->Active(1))
            return 0.0f;
    }
    if (self->mpTarget != 0)
        return 1.0f;
    return 0.0f;
}

// @ 0x00dbf890
float f_00dbf890(Behaviour* self)
{
    void* t = self->mpTarget;
    if (t != 0) {
        if (((Behaviour*)t)->kind == 4)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00dbf8b0
float f_00dbf8b0(Behaviour* self)
{
    Component* c = self->GetService();
    if (c != 0) {
        void* o = c->Cast(0x4e3faaf);
        if (o != 0 && *(int*)((char*)o + 0x64c) == g_169f754)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00dbf8f0
float f_00dbf8f0(Behaviour* self, int a2, int a3, uint32 flags)
{
    (void)a2; (void)a3;
    void* t = self->mpTarget;
    if (t != 0) {
        if (f_0102aa50(t, self, (flags & FLAG_BIT12) != 0))
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00dbf9a0
float f_00dbf9a0(Behaviour* self)
{
    void* t = self->mpTarget;
    if (t != 0) {
        if (((Behaviour*)t)->kind == 0)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00dbf9c0
bool f_00dbf9c0(Behaviour* self, int a2, int a3, int a4, int a5, BehaviourState* out)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
    out->f00 = 0.0f;
    out->state = 0;
    out->timer = 0.0f;

    const float* centre;
    Component* c = self->GetService();
    if (c != 0) {
        void* o = c->Cast(0x1186577);
        if (o != 0)
            centre = ((Spatial*)o)->Slot2c();
        else
            centre = &self->pos[0];
    } else {
        centre = &self->pos[0];
    }

    float p[3];
    p[0] = centre[0];
    p[1] = centre[1];
    p[2] = centre[2];

    void* pm = f_00b3d350(p);
    float r = ((SP::cPlanetModel_s00db_f0c0*)pm)->GetRadiusAt();
    self->SetAltitude(r + 55.0f);

    switch (self->kind) {
    case 3:
        out->f04 = 4.0f;
        out->f08 = 50.0f;
        break;
    case 4:
        out->f04 = 12.0f;
        out->f08 = 90.0f;
        break;
    case 6:
        out->f04 = 6.0f;
        out->f08 = 70.0f;
        break;
    }
    return true;
}

// @ 0x00dbfad0
bool f_00dbfad0(Behaviour* self, int a2, int a3, uint32 flags, BehaviourState* s, int a6, int a7, float dTimer, float dAngle, int a10)
{
    (void)a2; (void)a3; (void)a6; (void)a7; (void)a10;

    if (self->kind == 4) {
        void* best = (void*)f_0102bc90(self, (flags & FLAG_BIT12) != 0, 0);

        if (s->state == 0) {
            if (f_00c37890(self, best, 3)) {
                s->timer = 0.0f;
                s->state = 3;
                f_00c389c0(self, 8, 1);
            }
        }

        if (s->state == 3) {
            s->timer = s->timer + dTimer;
            void* tuning = f_01029940(self->kind);
            double chance = f_0102a8f0(tuning);
            if (s->timer >= (float)chance) {
                f_00c3a930(self, best, 3);
                s->timer = 0.0f;
                s->state = 0;
                return true;
            }
            self->mSelf.Slot50(0);
            return true;
        }
    }

    /* ---- keep-updating phase ---- */
    int empireId = 0;
    (void)empireId;

    if (self->kind == 3)
        empireId = (int)f_01021090();
    else
        empireId = (int)((Component*)self)->Slot4c();

    Component* svc = self->GetService();
    if (svc == 0)
        return false;

    void* planet = svc->Cast(0x1186577);
    void* place = svc->Cast(0x4e3faaf);
    void* ship = svc->Cast(0xee9b2232);
    if (svc->IsReady())
        return false;

    if (self->kind == 3) {
        if (ship == 0)
            return false;
        void* sim = f_00ffbe50();
        if (ship != f_00ffc320(sim))
            return false;
    }

    if (ship != 0) {
        void* record = f_010212a0();
        if (f_01029a10(planet, record) && ((Behaviour*)ship)->i74c == empireId
            && ((Behaviour*)ship)->f748 >= 100.0f)
            return false;
    }

    s->f00 = s->f00 + dAngle;

    const float* planetPos = ((Spatial*)planet)->Slot2c();

    float dir[3];
    f_00436ce0(planetPos, dir);

    float phase = -((s->f00 * 1.0f) / (s->f04 * 2.2f));

    float orth[3];
    f_006985b0(dir, orth);
    f_00436ce0(orth, orth);

    /* cross = orth x dir, then normalized */
    float cr[3];
    cr[0] = orth[1] * dir[2] - orth[2] * dir[1];
    cr[1] = orth[2] * dir[0] - orth[0] * dir[2];
    cr[2] = orth[0] * dir[1] - orth[1] * dir[0];

    float side[3];
    f_00449c20(cr, side);

    float sn = MathSin(phase * 2.2f) * s->f08;
    float cs = MathCos(phase);

    float off[3];
    off[0] = dir[0] * sn + orth[0] * cs;
    off[1] = dir[1] * sn + orth[1] * cs;
    off[2] = dir[2] * sn + orth[2] * cs;

    const float* here = self->mSpatial.Slot2c();
    float p[3];
    p[0] = here[0] + off[0];
    p[1] = here[1] + off[1];
    p[2] = here[2] + off[2];
    self->SetOrigin(p);

    self->flag624 = 1;

    void* handle;
    if (ship != 0) {
        handle = (void*)f_00cc15b0((char*)ship, self->mSelf.Slot54());
    } else {
        handle = place != 0 ? (char*)place + 0x508 : 0;
    }
    self->mSelf.Slot50(handle);
    return true;
}

// @ 0x00dbfe80
bool f_00dbfe80(Behaviour* self)
{
    void* sim = f_00ffbe50();
    void* ufo = f_00bddd10(sim);
    void* best;
    if (ufo == 0)
        best = 0;
    else
        best = ((Component*)ufo)->Cast(0xb033b403);

    sim = f_00ffbe50();
    void* player = f_00ffc320(sim);

    Component* svc = self->GetService();
    uint32 empireId = (uint32)((Component*)self)->Slot4c();

    void* mgr = f_00b3d2a0(empireId);
    void* empire = f_00ba9370(mgr, empireId);
    if (empire != 0) {
        int t = *(int*)((char*)empire + 0x58);
        uint32 setId;
        if ((unsigned)t <= 8)
            setId = kSetiByType[t];
        else
            setId = (void*)empire == f_01021300() ? 0xea351526u : 0u;

        void* aud = f_00a206f0();
        void* audSys = 0;
        if (aud != 0)
            audSys = ((Component*)aud)->Slot20();
        f_00435ed0(setId, audSys);
    }

    if (best != 0) {
        void* old = self->mpTarget;
        if (best != old) {
            ((Component*)best)->slot00();
            self->mpTarget = best;
            if (old != 0)
                ((Component*)old)->slot04();
        }
        return true;
    }
    if (player != 0) {
        self->SetTarget(player);
        return true;
    }
    (void)svc;
    return false;
}
