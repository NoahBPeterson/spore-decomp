// src/game/SPGonzago/SPSpaceCommActions.cpp -- migrated from slice(s) s0102cd90, s0102df20, s0102be20 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceCommActions.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>

// ---- items of slice s0102be20 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int intptr_t;
#define nullptr 0
struct cMissionKey;
struct cMissionData {
    uint8_t mPad000[0x13c];                     // 0x000
    cMissionKey* mpMissionKey;                  // 0x13c
};
struct cSpaceGameSub;
struct cSpaceGame {
    uint8_t mPad00[0x18];                       // 0x00
    cSpaceGameSub* mpSubObject;                 // 0x18
};
struct cMissionKey {
    void* GetRewardTable();
};
struct cMission {
    void* Call(int nSlot) {
        return ((void* (*)(void*))((void**)*(void**)this)[nSlot >> 2])(this);
    }
};
struct cMissionStep {
    void CompleteStep(void* pPlanet, void* pLookup, uint32_t nKeyA, uint32_t nKeyB,
                      void* pMission, int nFlags);
};
struct cMissionManager {
    void* CreateMissionFromID(void* pParam3, cMissionKey* pKey, int nCount, int nFlags);
    void* FindMission(int nCount, cMissionKey* pKey);
};
struct cSpaceGamePart {
    void* ResolvePlanetPart(void* pPlanet);
};
struct cTradeRoute {
    int RemoveTradeRoute(void* pRoute);
};
struct cTradeRouteManager : cTradeRoute {
};
struct cNounManager {
    cTradeRouteManager* GetTradeRouteManager();
};
struct cTribe {
    int RemoveTradeRouteReward(uint32_t nId, int nValue);
};
struct cPlayer {
    cTribe* GetTribe();
};
struct cSpiceManager {
    void AutoAddSpiceToCargo(void* pData);
};
struct cCommScreen {
    void SetSpeakerText();
    void SetResponseCount();
};
struct cRewardReceiver {
    void Apply();
};
struct cSpaceGameSub {
    void StopStory();
    void PauseStory();
};
void* NounManager();
void* SpaceGameGet();
void* SpaceGameGet(uint32_t nA, int nB);
void* ResolveNoun(void* pNoun);
void* GetMissionManager(void* pA);
void* GetPlayerHomePlanet();
void* GetActivePlanet();
void* GetPlayerEmpire();
void* GetSpaceRelationshipTuning();
void* __stdcall GetLayout(uint32_t nId);
void* MissionResultLookup(void* pA, void* pB);
char CheckMissionAllowed(void* pOwner, void* pMission);
char TestAchievement(uint32_t nId, int nA);
int RemoveTradeRoute(void* pManager, void* pRoute);
int GetLanguageOwner(int nLanguage);
int GetRelationshipValue(void* pCreature, void* pMission);
void RemoveTradeRouteReward(void* pA, int nValue);
void AutoAddSpiceToCargo(void* pUFO, void* pData);
void CompleteMissionStep(void* pA, void* pB, uint32_t nId, uint32_t nValue);
void AutoTestAchievement(void* pController, uint32_t nId, int nValue);
void AddAchievementScore(int nValue);
void ApplyRelationshipChange(void* pA, uint32_t nId, uint32_t nValue);
void* CreateWantedMission(void* pPlanet, void* pKey);
void* SetMissionResult(void* pA, void* pB);
void* GetSpiceManager();
void* __stdcall GetRewardReceiver(uint32_t nId);
void* GetMissionStepHandler();
void* GetMissionManager();
void SetSpeakerText(void* pText);
void SetResponseCount(uint32_t nCount);
void StopStory(void* pSub);
void PauseStory(void* pSub);
// ---- items of slice s0102be20 end

// ---- items of slice s0102df20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_key_016de7e4[];
extern int g_TargetPlanetIndex;             // 0x15b751c
extern const char k_Military_Planet[];      // 0x0149963c "SPG_SystemSurrender_Military_Planet"
typedef unsigned int uint;
struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct Obj;
struct PtrVec { Obj** b; Obj** e; Obj** c; };
struct Obj {
    // event log / UI (b3d4a0, b3d4d0 return one of these)
    void m_aea210();
    void m_aeb720(int arg, int stringKey, int category, int text, int a, int b);
    void m_aeb3e0(int a, int b, int c, int d, int e, int f, int g, int h);
    void m_ae0930(const char* s, int a, int b, int c, int d, int e);
    void m_ae09b0(int id, void* data, int z);
    // empire / planet
    int m_ce6950();                       // empire id style getter ([this+0x184])
    Obj* m_b8de30();
    Vec3* m_5c65e0();                     // cCivData::GetCities
    Obj* m_c31730();                      // cEmpire::GetHomePlanet
    int m_c30c60();
    void m_c30bb0();
    void m_c31a00(int amount);
    int m_c313d0(Vec3 v);
    // managers
    Obj* m_ba9370(int id);                // cStarManager::GetEmpireByID
    Obj* m_ba6490();
    Obj* m_ba6dc0(Obj* p);
    float m_d06240(int a, int b, int key, float f);   // cRelationshipManager::RecordEvent
    int m_d00a70(int a, int b, int c);
    void m_d05830(int a, int b);
    void m_d038e0(Obj* a, Obj* b);        // StartPeace
    void m_d06920(Obj* a, Obj* b);        // StartAlliance
    Obj* m_ad49b0();
    Obj* m_f67d90();                      // cTerrainEditor::GetCurrentTerrainSphere
    void m_c77bf0(int key);
    void m_c7be30(Obj* e);
    // tuning
    int m_102fa30(int type);              // GetTradeCaptureOfferPrice
    int m_1030930(int type, Obj* emp);    // GetPeaceOfferPrice
    int m_1030390();                      // GetTradeRouteMaxNumber
    int m_1030650(int x);                 // CalcAttackRequestCost
    int m_10407d0(Obj* emp);
    // trade
    int m_1037f20();                      // GetNumberOfPlayerTradeRoutes
    void m_10393a0(Obj* sort, int arg, int key, uint pid);   // AddTradeRoute
    Obj* m_bfc5f0(int a, int b);
    void m_fe5430();
    // sim
    Obj* m_a1ad60();                      // GetPlayerInventory
    void m_ff45e0(void* key);
    void m_106ac90(int x);
    void m_10027b0(int a, int b);         // AddPosseMember
    void m_10019a0();
    void m_1046fc0();
    // missions
    void m_c46e20(int x);                 // GiveOnAcceptItems
    void m_c485b0();                      // Accept
    void m_c485c0();
    void m_c485d0();
    void m_c485e0();
    void m_c485f0();
    void m_c59eb0();                      // AcceptCurrentStep
    void m_c59f00();
    void m_c59f60();
    Obj* m_c59d90();                      // GetCurrSubMission
    void m_c52070();                      // ValidateProgressEvent
    int m_c57ef0(int arg, void* planet);  // cSPMissionMultiDelivery::OnDelivery
    Obj* m_b1fdb0();                      // GetAvatar
    Obj* m_bba790();
    int m_b8dab0();
    Obj* m_c8b770();                      // cStar::GetSolarSystem
    void m_676e90(uint id, int x);        // Achievements::Controller::AutoTest
};
struct Planet { uint pad[79]; Obj* emp; };           // +0x13c
struct Emp { uint pad[33]; uint f84; };              // +0x84
struct Tuning90 : Obj { uint pad[36]; int f90; };          // +0x90
inline uint& nounField(Obj* n, int off) { return *(uint*)((char*)n + off); }
struct VecCopy {                              // eastl::vector<Obj*> copy (50d440 ctor / 4e1bf0 dtor)
    Obj** b; Obj** e; Obj** c;
    VecCopy(const PtrVec& src);   // 0x0050d440
    ~VecCopy();                   // 0x004e1bf0
};
struct SpaceGameObj { uint pad[5]; Obj* f14; };
struct Flag44 { char pad[0x44]; char flag; };
struct EvtData {
    char pad[0x1c];
    float f1c;
    float f20;
    EvtData(const Vec3* p, const Quat* q);   // 0x00ad79d0
    ~EvtData();                              // 0x00ad7ad0 cActionTarget::~cActionTarget
};
struct Z3 { int a, b, c; Z3() : a(0), b(0), c(0) {} };
Planet* GetActivePlanet_s0102_df20();                 // 0x01021260 SP::cSPLivingUniverse::GetActivePlanet
Obj* GetSystemAT();                        // 0x00a206f0 EA::Audio::GetSystemAT
uint GetPlayerEmpireID();                  // SP::cSPLivingUniverse::GetPlayerEmpireID
Obj* GetPlayerEmpire_s0102_df20();                    // SP::cSPLivingUniverse::GetPlayerEmpire
int GetUniverseContext();                  // 0x01021080
Obj* Fn_01021240();
Obj* Fn_01021230();
Obj* StarManager();
Obj* RelationshipManager();
Obj* NounManager_s0102_df20();
Obj* SpaceGameGet_s0102_df20();
Obj* GetUFOSimulator();
Obj* MessageServer();                      // 0x0067dcc0
Obj* Fn_0102f810();                        // SP::GetSpaceEconomyTuning
Tuning90* GetSpaceRelationshipTuning_s0102_df20();
Obj* Fn_00b3d4a0();
Obj* Fn_00b3d4d0();
Obj* Fn_00675250();                        // Achievements::Controller::Get
void Fn_01044640();
void Fn_0102caa0(int arg, Planet* p);
void Fn_0102c980(Obj* x);
void Fn_0102cd30();
void Fn_0102cd40();
void Fn_0102c9e0(int arg, Planet* p, int x);
void Fn_0102cc30(int arg, Planet* p);
void Fn_0102d7e0();
void Fn_0102d820();
void Fn_0102daa0(Obj* x);
void Fn_0102d0b0(int arg, Obj* x);
int Fn_0102b690(Obj* avatar, uint pid, int count);
void Fn_00c8c9d0(Obj* x);
void Fn_00c8d000(Obj* x, uint pid);
char Fn_00c8b920(int empId, uint pid);
Obj* Fn_00aed3f0(Obj* mission);
Obj* icast_Delivery(Obj* m);               // EA::COM::interface_cast<cSPMissionMultiDelivery*>
Obj* icast_Fetch(Obj* m);                  // interface_cast<cSPMissionFetch*>
Obj* icast_Flight101(Obj* m);              // interface_cast<cSPMissionFlight101*>
void GiveGift(int arg, int kind);          // 0x0102cae0
void TryBreakAlliance(int arg);            // 0x0102cd90
void TryCreateAlliance(int arg);           // 0x0102ce30
void TryPeaceOffer(int arg, int price);    // 0x0102cf10
void TryPurchaseOffer(int arg, Obj* sort, int price);   // 0x0102d1b0
int GetAttackRequestResponse(int arg);     // 0x0102d150
void Fn_00e39ab0(int key, Obj* emp, Z3* d, Z3* c, int v, int zero, Z3* b, Z3* a);
extern PtrVec g_AttackRequestPlanets;       // 0x16decac
template <class R> inline R vc0(void* o, int off) {
    typedef R(__thiscall * F)(void*);
    return ((F)(*(void***)o)[off / 4])(o);
}
template <class R, class A> inline R vc1(void* o, int off, A a) {
    typedef R(__thiscall * F)(void*, A);
    return ((F)(*(void***)o)[off / 4])(o, a);
}
template <class R, class A, class B> inline R vc2(void* o, int off, A a, B b) {
    typedef R(__thiscall * F)(void*, A, B);
    return ((F)(*(void***)o)[off / 4])(o, a, b);
}
template <class R, class A, class B, class C> inline R vc3(void* o, int off, A a, B b, C c) {
    typedef R(__thiscall * F)(void*, A, B, C);
    return ((F)(*(void***)o)[off / 4])(o, a, b, c);
}
static inline void LogTail(int arg, Planet* p, int text) {
    Fn_00b3d4a0()->m_aeb720(arg, p->emp->m_ce6950(), (int)0xc8fbf7d7, text, 0, 0);
}
// ---- items of slice s0102df20 end

// ---- items of slice s0102cd90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_15da7c4, g_15da7c8, g_15da7cc, g_15da7d0;   // 0x015da7c4
extern int    g_targetPlanetIndex;             // 0x015b751c
extern void* vtbl_UIMessageBase[];   // 0x013eb90c
extern void* vtbl_UIMessage[];       // 0x013eb844
struct Vec3_s0102_cd90 {
    float x, y, z;
    Vec3_s0102_cd90() {}
    Vec3_s0102_cd90(const Vec3_s0102_cd90& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Quat_s0102_cd90 {
    float x, y, z, w;
    Quat_s0102_cd90() {}
    Quat_s0102_cd90(const Quat_s0102_cd90& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};
struct Obj_s0102_cd90;
struct PtrVec_s0102_cd90 { Obj_s0102_cd90** b; Obj_s0102_cd90** e; Obj_s0102_cd90** c; };
struct Tuning {
    int m_102fa30(int type);          // GetTradeCaptureOfferPrice
    int m_102ffc0();                  // GetTradeCaptureGoodOfferDelta
    int m_102ff40();                  // GetTradeCaptureBadOfferDelta
    int m_102ff80();                  // GetTradeCaptureVeryBadOfferDelta
    float m_1030600();                // GetTradeCaptureRemainingBuildingRatio
    float m_10305b0();                // GetTradeCaptureRemainingCityRatio
    float m_1030560();                // GetTradeCaptureRemainingPlanetRatio
    int m_1030930(int type, Obj_s0102_cd90* empire);  // GetPeaceOfferPrice
    int m_1030aa0(Obj_s0102_cd90* empire);        // GetPeaceGoodOfferDelta
    int m_10309c0(Obj_s0102_cd90* empire);        // GetPeaceBadOfferDelta
    int m_1030a30(Obj_s0102_cd90* empire);        // GetPeaceVeryBadOfferDelta
};
struct TradeMgr {
    void m_10383a0(Obj_s0102_cd90* sys);                         // RemoveAllTradeRoutesFromSystem
    int m_1037e40(int sysId, int empId);              // GetPlayerProgressOnTradeRoute
};
struct StarMgr {
    Obj_s0102_cd90* m_ba9370(int id);                            // cStarManager::GetEmpireByID
    TradeMgr* m_ba6490();                             // trade route manager
    void m_bb59b0(Obj_s0102_cd90* p, Obj_s0102_cd90** outPlanet);           // GetOrActivatePlanet
    Obj_s0102_cd90* m_ba6dc0(Obj_s0102_cd90* planet);                       // banner / planet lookup
};
struct Obj_s0102_cd90 {
    int m_bba990();
    Obj_s0102_cd90* m_bbaa60(int i);
    int m_b8dab0();
    int m_c70c00();                   // planet: sim active?
    void m_c71e70();                  // cPlanet::PlanetSimActivate
    int m_c70e00();
    Obj_s0102_cd90* m_c8b770();                  // cStar::GetSolarSystem
    Obj_s0102_cd90* m_a1ad60();                  // GetPlayerInventory
    Obj_s0102_cd90* m_bfc5f0();                  // GetPlayerTribe
    void m_fe5430(int a, int b);
    void m_c31a00(int amount);
    void m_ae9140(int id);
    void m_aea230(void* strVec);
    void m_aeb720(int arg, int empId, int category, int text, int a, int b);
    void m_ae09b0(int id, void* data, int z);
    int m_ce6950();
    float m_d06240(int a, int b, int key, float f);   // cRelationshipManager::RecordEvent
    void m_676e90(uint id, int x);    // Achievements::Controller::AutoTest
    int  m_d01e30(Obj_s0102_cd90* empire, Obj_s0102_cd90* player);           // cRelationshipManager::EndAlliance
    float m_d00a10(int empireId, int playerId, int zero);  // cRelationshipManager::ClampRelationship
    void m_d06920(Obj_s0102_cd90* empire, Obj_s0102_cd90* player);           // cRelationshipManager::StartAlliance
    void m_d05830(int empireId, int playerId);
    void m_d038e0(Obj_s0102_cd90* empire, Obj_s0102_cd90* player);           // cRelationshipManager::StartPeace
    void m_aea210();                                   // cCommManager::CloseCommEvent
    Obj_s0102_cd90* m_b8de30();                                   // cBioElemSort::SortBanners
    Obj_s0102_cd90* m_b1fdb0();                                   // cGameNounManager::GetAvatar
    int  m_c30c80();
    void m_60d860(uint id, int v);                     // cPollinator::UpdateProperty
    void m_c5b370(Obj_s0102_cd90* target);                        // cPlanetMission::SetTarget
    void m_c47180(int param);
    int  m_c5b530();                                   // cSPRaidEvent::GenerateBomberCount
    void m_c5b390(int n);
    void m_c485b0();                                   // cSPMission::Accept
    void m_c322f0(int v);
    char m_1075500();
    void m_1075ef0();
    Vec3_s0102_cd90* m_4df400();
};
struct PlayerObj {
    uint32_t pad_000[0x84 / 4];
    int      empire_id;                                // +0x84
};
struct TerrainPlayer {
    uint32_t pad_000[0x10fc / 4];
    uint32_t t10fc, t1100, t1104, t1108, t110c;        // +0x10fc
    int  m_c76800(Obj_s0102_cd90* empire);                        // cPlayer::GetPeacePriceForPlayer
    void m_c7bc20(int empireId, int flag);             // cPlayer::SetWarFlag20
};
struct NounMgr {
    TerrainPlayer* m_f67d90();                         // cTerrainEditor::GetCurrentTerrainSphere
};
struct U32Vec {
    uint32_t* b; uint32_t* e; uint32_t* c;
    void push_back(uint32_t v);
    void m_4558a0(uint32_t* pos, const uint32_t* val); // eastl slow path (0x004558a0)
};
struct SpaceGame {
    uint32_t pad_000[6];
    Obj_s0102_cd90*     trading;                                  // +0x18
};
struct LaunchData {
    void*    vptr;                                     // +0x00
    uint32_t pad_004[2];
    uint32_t f00c;                                     // +0x0c
    uint32_t f010, f014, f018;                         // +0x10
    uint32_t pad_01c[2];
    uint32_t f024, f028, f02c, f030;                   // +0x24
    unsigned char f034, f035, f036, f037, f038, f039;  // +0x34
    unsigned char pad_03a[2];
    unsigned char f03c, f03d;                          // +0x3c
    unsigned char pad_03e[2];
    void*    str_b;                                    // +0x40
    void*    str_e;                                    // +0x44
    uint32_t str_c;                                    // +0x48
    unsigned char pad_04c[0x64 - 0x4c];
    unsigned char f064;                                // +0x64
    unsigned char pad_065[0x6d - 0x65];
    unsigned char f06d;                                // +0x6d
    unsigned char pad_06e[2];
    U32Vec   vec;                                      // +0x70
    unsigned char pad_07c[0x90 - 0x7c];
    uint32_t f090;                                     // +0x90
    Obj_s0102_cd90*     p094;                                     // +0x94
    void m_5a9080();                                   // cEditorLaunchData::cEditorLaunchData
};
struct MissionMgr {
    Obj_s0102_cd90* m_fec590(uint id, int param, Obj_s0102_cd90* empire, int zero);  // CreateMissionFromID
    char m_fee590(Obj_s0102_cd90* planet, int* out);                      // IsPlanetARaidTarget
};
struct RelTuning {
    float m_1040820(float rel);
};
struct RandomGlobal {
    double RandomDouble();
};
struct Planet_s0102_cd90 { uint pad[79]; Obj_s0102_cd90* emp; };           // +0x13c
inline uint& nounField_s0102_cd90(Obj_s0102_cd90* n, int off) { return *(uint*)((char*)n + off); }
struct EvtData_s0102_cd90 {
    char pad[0x1c];
    float f1c;
    float f20;
    EvtData_s0102_cd90(const Vec3_s0102_cd90* p, const Quat_s0102_cd90* q);   // 0x00ad79d0
    ~EvtData_s0102_cd90();                              // 0x00ad7ad0 cActionTarget::~cActionTarget
};
struct Z3_s0102_cd90 { int a, b, c, d; Z3_s0102_cd90() : a(0), b(0), c(0) {} };
Planet_s0102_cd90* GetActivePlanet_s0102_cd90();                 // 0x01021260
Obj_s0102_cd90* GetPlayerEmpire_s0102_cd90();                    // 0x01021300
Obj_s0102_cd90* Fn_01021230_s0102_cd90();
StarMgr* StarManager_s0102_cd90();                    // 0x00b3d2a0
Obj_s0102_cd90* RelationshipManager_s0102_cd90();                // 0x00b3d2c0
Obj_s0102_cd90* SpaceGameGet_s0102_cd90();                       // 0x01002bd0
Obj_s0102_cd90* GetUFOSimulator_s0102_cd90();                    // 0x00ffbe50
Obj_s0102_cd90* MessageServer_s0102_cd90();                      // 0x0067dcc0
Tuning* Fn_0102f810_s0102_cd90();                     // SP::GetSpaceEconomyTuning
Obj_s0102_cd90* Fn_00b3d4a0_s0102_cd90();                        // CommManager
Obj_s0102_cd90* Fn_00b3d4d0_s0102_cd90();                        // GetTriggerMgr
Obj_s0102_cd90* Fn_00675250_s0102_cd90();                        // Achievements::Controller::Get
void Fn_00c705c0(Obj_s0102_cd90* p, int v);
void Fn_00c8ce40(Obj_s0102_cd90* sort, float r3, int one1, float r2, int one2, float r1, int zero);
void Fn_00e39ab0(int key, Obj_s0102_cd90* emp, Z3_s0102_cd90* d, Z3_s0102_cd90* c, int v, int zero, Z3_s0102_cd90* b, Z3_s0102_cd90* a);
void* __cdecl operator_new6(uint, const char*, int, int, const char*, int);   // 0x00f473a0
void  __cdecl operator_delete__(void*);                                        // 0x00f47380
void  __cdecl StrCopy(void* dst, const void* src, uint n);                     // 0x011e0744 (memcpy)
NounMgr*      NounManager_s0102_cd90();                   // 0x00b3d300
MissionMgr*   GetMissionManager_s0102_cd90();             // 0x00feb9f0
RelTuning*    Fn_010407c0();                   // 0x010407c0 GetSpaceRelationshipTuning
Obj_s0102_cd90*          Fn_0067cb30();                   // 0x0067cb30 manager getter
char          IsWorldLayoutFlagSet(int flag);  // 0x00685520
Obj_s0102_cd90*          Fn_00401090();                   // 0x00401090
Obj_s0102_cd90*          Fn_00b3d320(Obj_s0102_cd90* o);             // 0x00b3d320
void          Fn_00b1dee0(Obj_s0102_cd90* o);             // 0x00b1dee0
void          Fn_00e5c780(void* self, int* key, void* out);  // 0x00e5c780 rbtree find
extern Obj_s0102_cd90**  g_attackRequestPlanets;          // 0x016decac (vector begin)
extern Obj_s0102_cd90**  g_attackRequestPlanetsEnd;       // 0x016decb0 (vector end)
inline RandomGlobal* randomGlobal() { return (RandomGlobal*)0x01601760; }
template <class R, class A, class B, class C, class D> inline R vc4(void* o, int off, A a, B b, C c, D d) {
    typedef R(__thiscall * F)(void*, A, B, C, D);
    return ((F)(*(void***)o)[off / 4])(o, a, b, c, d);
}
struct StrVec {
    char* b; char* e; char* c;
};
static __forceinline void PostCommString(const char* s, uint n) {
    StrVec v;
    v.b = 0; v.e = 0; v.c = 0;
    char* p = (char*)operator_new6(n + 1, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    v.c = p + n + 1;
    v.b = p;
    StrCopy(p, s, n);
    v.e = p + n;
    *v.e = 0;
    Fn_00b3d4a0_s0102_cd90()->m_aea230(&v);
    if ((v.c - v.b) > 1 && v.b) operator_delete__(v.b);
}
struct IRel { virtual void v0(); virtual void Release(); };
struct UIMessage {
    void** vptr; volatile long rc; int d0; uint pad[11]; uint id; uint pad34; uint flags;
    UIMessage(uint id_, int data) {
        id = id_;
        vptr = vtbl_UIMessageBase;
        _InterlockedExchange(&rc, 0);
        vptr = vtbl_UIMessage;
        flags = 0;
        d0 = data;
    }
    ~UIMessage() {
        vptr = vtbl_UIMessage;
        uint bit = 1;
        for (int i = 0; i < 32; i++) {
            if ((flags & bit) && ((IRel**)((char*)this + 8))[i * 2]) ((IRel**)((char*)this + 8))[i * 2]->Release();
            bit = _rotl(bit, 1);
        }
    }
};
struct MsgServer {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
    virtual void Post(unsigned type, UIMessage* m, int flag);   // +0x14
};
void U32Vec::push_back(uint32_t v) {
    uint32_t* p = e;
    if (p < c) {
        e = p + 1;
        if (p) *p = v;
    } else {
        m_4558a0(p, &v);
    }
}
// ---- items of slice s0102cd90 end

// @ 0x0102c980
void ClearTradeRoute(void* pRoute)
{
    int nDelta = ((cNounManager*)NounManager())->GetTradeRouteManager()->RemoveTradeRoute(pRoute);
    if (nDelta > 0) {
        ((cPlayer*)SpaceGameGet())->GetTribe()->RemoveTradeRouteReward(0x19, -nDelta);
    }
}

// @ 0x0102c9e0
void StartMission(void* pPlanet, cMissionData* pMissionData, void* pParam3)
{
    void* pCount = ((cSpaceGamePart*)NounManager())->ResolvePlanetPart(pPlanet);

    cMissionKey* pKey = pMissionData->mpMissionKey;
    cMission* pMission;
    if (pCount != nullptr && pParam3 != nullptr) {
        pMission = (cMission*)((cMissionManager*)GetMissionManager())
                       ->CreateMissionFromID(pParam3, pKey, (int)(intptr_t)pCount, 0);
    } else {
        pMission = (cMission*)((cMissionManager*)GetMissionManager())
                       ->FindMission((int)(intptr_t)pCount, pKey);
    }

    uint32_t nKeyA;
    uint32_t nKeyB;
    if (pMission != nullptr) {
        nKeyA = (uint32_t)(intptr_t)pMission->Call(0xa4);
        nKeyB = 0x8b756f4b;
    } else {
        nKeyA = 0xc8fbf7d7;
        nKeyB = (pKey != GetPlayerHomePlanet()) ? 0x8053662e : 0x303878af;
    }

    void* pLookup = pKey->GetRewardTable();
    ((cMissionStep*)GetMissionStepHandler())
        ->CompleteStep(pPlanet, pLookup, nKeyA, nKeyB, pMission, 0);
}

// @ 0x0102caa0
void CollectSpice(void* pPlanet, cMissionData* pData)
{
    cSpiceManager* pManager = (cSpiceManager*)GetSpiceManager();
    pManager->AutoAddSpiceToCargo(pData);
    ((cMissionStep*)GetMissionStepHandler())
        ->CompleteStep(pPlanet, pData->mpMissionKey->GetRewardTable(), 0xc8fbf7d7,
                       0x2ea8fb98, 0, 0);
}

// @ 0x0102cae0
void GiveGift(void* pPlanet, uint32_t nGiftType)
{
    int nCost;
    uint32_t nReward;
    if (nGiftType == 0) {
        void* pTuning = GetSpaceRelationshipTuning();
        nCost = *(int*)((uint8_t*)pTuning + 0x78);
        pTuning = GetSpaceRelationshipTuning();
        nReward = *(uint32_t*)((uint8_t*)pTuning + 0x84);
    } else if (nGiftType == 1) {
        void* pTuning = GetSpaceRelationshipTuning();
        nCost = *(int*)((uint8_t*)pTuning + 0x7c);
        pTuning = GetSpaceRelationshipTuning();
        nReward = *(uint32_t*)((uint8_t*)pTuning + 0x88);
    } else {
        if (nGiftType != 2)
            return;
        void* pTuning = GetSpaceRelationshipTuning();
        nCost = *(int*)((uint8_t*)pTuning + 0x80);
        pTuning = GetSpaceRelationshipTuning();
        nReward = *(uint32_t*)((uint8_t*)pTuning + 0x8c);
    }

    void* pEmpire = GetPlayerEmpire();
    if (pEmpire == nullptr)
        return;
    if (GetLanguageOwner(0) < nCost)
        return;

    (void)TestAchievement(0x77893b39, 1);
    AutoTestAchievement(nullptr, 0x77893b39, 1);
    AddAchievementScore(-nCost);
    CheckMissionAllowed(nullptr, nullptr);

    int nBefore = GetRelationshipValue(pPlanet, *(void**)((uint8_t*)pEmpire + 0x84));
    ApplyRelationshipChange(pPlanet, *(uint32_t*)((uint8_t*)pEmpire + 0x84), 0x526e51f);
    (void)nReward;
    int nAfter = GetRelationshipValue(pPlanet, *(void**)((uint8_t*)pEmpire + 0x84));
    uint32_t nResult;
    if ((float)nBefore == (float)nAfter) {
        GetActivePlanet();
        nResult = 0x661d5b89;
    } else {
        GetActivePlanet();
        nResult = 0x8efa19dc;
    }

    void* pLookup = MissionResultLookup((void*)0xc8fbf7d7, (void*)(intptr_t)nResult);
    SetMissionResult(pPlanet, pLookup);
    CompleteMissionStep(pPlanet, pLookup, 0xc8fbf7d7, nResult);
}

// @ 0x0102cc30
void CreateNewRaid(void* pPlanet, cMissionData* pMission)
{
    ResolveNoun(pPlanet);
    void* pLanguage = (void*)GetLanguageOwner(0);
    uint32_t nMission = 0xffffffff;
    switch (*(uint32_t*)((uint8_t*)pLanguage + 0x58)) {
    case 0:
    case 9:
    case 0x12:
        nMission = 0x5d182075;
        break;
    case 1:
    case 10:
        nMission = 0x2b795e0d;
        break;
    case 2:
    case 0xb:
        nMission = 0x4b708009;
        break;
    case 3:
    case 0xc:
        nMission = 0xc052cccf;
        break;
    case 4:
    case 0xd:
        nMission = 0x29e235c0;
        break;
    case 5:
    case 0xe:
        nMission = 0xf46a1fc4;
        break;
    case 6:
    case 0xf:
    case 0x11:
        nMission = 0x34ca76bf;
        break;
    case 7:
    case 0x10:
        nMission = 0xb9656f6;
        break;
    default:
        break;
    }

    void* pResult = nullptr;
    if (nMission != 0) {
        void* pMissionKey = pMission->mpMissionKey;
        GetMissionManager((void*)(intptr_t)nMission);
        pResult = CreateWantedMission((void*)(intptr_t)nMission, pMissionKey);
        if (pResult != nullptr)
            ((void* (*)(void*))((void**)*(void**)pResult)[0xa4 >> 2])(pResult);
    }

    void* pLookup = MissionResultLookup(pResult == nullptr ? (void*)0xc8fbf7d7
                                                          : (void*)0xc8fbf7d7,
                                        pResult == nullptr ? (void*)0x8053662e
                                                           : (void*)0x8b756f4b);
    SetMissionResult(pPlanet, pLookup);
    CompleteMissionStep(pPlanet, pLookup, 0xc8fbf7d7,
                        pResult == nullptr ? 0x8053662e : 0x8b756f4b);
}

// @ 0x0102cd30
void ResumeSpaceGame()
{
    cSpaceGame* pGame = (cSpaceGame*)SpaceGameGet();
    cSpaceGameSub** ppSub = &pGame->mpSubObject;
    (*ppSub)->StopStory();
}

// @ 0x0102cd40
void CloseCommScreenToSpace()
{
    ((cCommScreen*)GetLayout(0x13fa1d4))->SetSpeakerText();
    ((cCommScreen*)GetLayout(0))->SetResponseCount();
    ((cRewardReceiver*)GetRewardReceiver(0x2710))->Apply();

    cSpaceGame* pGame = (cSpaceGame*)SpaceGameGet();
    cSpaceGameSub** ppSub = &pGame->mpSubObject;
    (*ppSub)->StopStory();
    pGame = (cSpaceGame*)SpaceGameGet();
    ppSub = &pGame->mpSubObject;
    (*ppSub)->PauseStory();
}

// @ 0x0102cd90
void TryBreakAlliance(int empireId)
{
    Obj_s0102_cd90* empire = StarManager_s0102_cd90()->m_ba9370(empireId);
    Obj_s0102_cd90* player = GetPlayerEmpire_s0102_cd90();
    RelationshipManager_s0102_cd90()->m_d01e30(empire, player);
    int pid = ((PlayerObj*)player)->empire_id;
    RelationshipManager_s0102_cd90()->m_d06240(empireId, pid, 0x526e521, 1.0f);
    vc4<void>(MessageServer_s0102_cd90(), 0x18, 0x43f2585, 0, 0, 0);
    Planet_s0102_cd90* pl = GetActivePlanet_s0102_cd90();
    Obj_s0102_cd90* emp = pl->emp;
    Fn_00b3d4a0_s0102_cd90()->m_aeb720(empireId, emp->m_ce6950(), (int)0xc8fbf7d7,
                            (int)0x20534e67, 0, 0);
}

// @ 0x0102ce30
void TryCreateAlliance(int empireId)
{
    Obj_s0102_cd90* empire = StarManager_s0102_cd90()->m_ba9370(empireId);
    SpaceGameGet_s0102_cd90();
    Obj_s0102_cd90* player = GetPlayerEmpire_s0102_cd90();
    float rel = RelationshipManager_s0102_cd90()->m_d00a10(empireId, ((PlayerObj*)player)->empire_id, 0);
    float threshold = Fn_010407c0()->m_1040820(rel);
    double r = randomGlobal()->RandomDouble();
    uint key;
    Planet_s0102_cd90* pl;
    if (threshold < (float)r) {
        key = 0xb1519e40;
        pl = GetActivePlanet_s0102_cd90();
    } else {
        RelationshipManager_s0102_cd90()->m_d06920(empire, player);
        int v = empire->m_c30c80() + 0x504;
        uint id = 0x5ba499af;
        Fn_0067cb30()->m_60d860(id, v);
        key = 0x12510968;
        pl = GetActivePlanet_s0102_cd90();
    }
    Fn_00b3d4a0_s0102_cd90()->m_aeb720(empireId, pl->emp->m_ce6950(), (int)0xc8fbf7d7,
                            (int)key, 0, 0);
}

// @ 0x0102cf10
void TryPeaceOffer(int empireId, int price)
{
    Obj_s0102_cd90* empire = StarManager_s0102_cd90()->m_ba9370(empireId);
    int basePrice = NounManager_s0102_cd90()->m_f67d90()->m_c76800(empire);
    int commKey = 0x1273c3f6;
    uint eventKey = 0x5661a77;
    bool good = (price == Fn_0102f810_s0102_cd90()->m_1030930(4, empire));
    if (good)
        commKey = 0x6c5f070e;
    int delta = price - basePrice;
    if (delta > Fn_0102f810_s0102_cd90()->m_1030aa0(empire)) {
        commKey = 0x38c512e1;
        good = true;
    } else if (delta > Fn_0102f810_s0102_cd90()->m_10309c0(empire)) {
        commKey = 0x6c5f070e;
        good = true;
    } else if (!good) {
        int v = Fn_0102f810_s0102_cd90()->m_1030a30(empire);
        commKey = ((delta <= v) - 1 & 0xa612289f) + 0x1273c3f6;
    }
    Obj_s0102_cd90* player = GetPlayerEmpire_s0102_cd90();
    Fn_00675250_s0102_cd90()->m_676e90(0x77893b39, 1);
    player->m_c31a00(-price);
    if (good) {
        RelationshipManager_s0102_cd90()->m_d05830(empireId, ((PlayerObj*)player)->empire_id);
        NounManager_s0102_cd90()->m_f67d90()->m_c7bc20(empireId, 0);
        empire->m_c322f0(1);
        RelationshipManager_s0102_cd90()->m_d038e0(empire, player);
        if (commKey == 0x38c512e1)
            eventKey = 0x5661a7c;
    }
    RelationshipManager_s0102_cd90()->m_d06240(empireId, ((PlayerObj*)player)->empire_id, eventKey, 1.0f);
    Planet_s0102_cd90* pl = GetActivePlanet_s0102_cd90();
    Fn_00b3d4a0_s0102_cd90()->m_aeb720(empireId, pl->emp->m_ce6950(), (int)0xc8fbf7d7,
                            (int)commKey, 0, 0);
}

// @ 0x0102d0b0
void AttackPlanet(int param1, int param2)
{
    if (!param2)
        return;
    Obj_s0102_cd90* empire = StarManager_s0102_cd90()->m_ba9370(param1);
    Obj_s0102_cd90* avatar = ((Obj_s0102_cd90*)param2)->m_b8de30()->m_b1fdb0();
    Obj_s0102_cd90* empire2 = StarManager_s0102_cd90()->m_ba9370((int)avatar);
    Obj_s0102_cd90* mission = GetMissionManager_s0102_cd90()->m_fec590(0xbbae6b99, param2, empire2, 0);
    if (!mission)
        return;
    Obj_s0102_cd90* raid = vc1<Obj_s0102_cd90*>(mission, 0xc, 0x3960c0a);
    if (!raid)
        return;
    raid->m_c5b370(empire);
    raid->m_c47180(param2);
    int n = raid->m_c5b530();
    raid->m_c5b390(n);
    raid->m_c485b0();
}

// @ 0x0102d150
int GetAttackRequestResponse(int param)
{
    int fail = 0xec3ae04;
    Obj_s0102_cd90* planet = g_attackRequestPlanets[g_targetPlanetIndex];
    Obj_s0102_cd90* banners = StarManager_s0102_cd90()->m_ba6dc0(planet);
    int local;
    if (GetMissionManager_s0102_cd90()->m_fee590(banners, &local))
        return (local - param) != 0 ? 0xa6cc89f3 : 0x6f3064cc;
    return fail;
}

// @ 0x0102d1b0
void TryPurchaseOffer(int arg, Obj_s0102_cd90* sort, int price)
{
    int basePrice = sort->m_bba990();
    uint key = 0x92a95b57;
    bool exact = false;
    if (price == Fn_0102f810_s0102_cd90()->m_102fa30(4)) {
        key = 0x57c98667;
        exact = true;
    }
    int delta = price - basePrice;
    bool capture = true;
    if (delta > Fn_0102f810_s0102_cd90()->m_102ffc0()) {
        RelationshipManager_s0102_cd90()->m_d06240(arg, GetPlayerEmpireID(), 0x55901b3, 1.0f);
        key = 0xe8a568ec;
    } else if (delta > Fn_0102f810_s0102_cd90()->m_102ff40()) {
        key = 0x57c98667;
    } else if (!exact) {
        if (delta > Fn_0102f810_s0102_cd90()->m_102ff80()) {
            key = 0x81034ee0;
        } else {
            RelationshipManager_s0102_cd90()->m_d06240(arg, GetPlayerEmpireID(), 0x5590199, 1.0f);
            key = 0x92a95b57;
        }
        capture = false;
        StarManager_s0102_cd90()->m_ba6490()->m_1037e40(nounField_s0102_cd90(sort, 0x70), arg);
    }
    if (capture) {
        Obj_s0102_cd90* emp = StarManager_s0102_cd90()->m_ba9370(arg);
        Z3_s0102_cd90 a, b, c, d;
        Fn_00e39ab0(0xfdd30461, emp, &d, &c, (int)nounField_s0102_cd90(sort, 0x70), 0, &b, &a);
        Fn_00c8ce40(sort, Fn_0102f810_s0102_cd90()->m_1030560(), 1, Fn_0102f810_s0102_cd90()->m_10305b0(), 1,
                    Fn_0102f810_s0102_cd90()->m_1030600(), 0);
        StarManager_s0102_cd90()->m_ba6490()->m_10383a0(sort);
        int count = *(unsigned char*)((char*)sort + 0xac);
        for (int i = 0; i < count; i++) {
            Obj_s0102_cd90* p = sort->m_bbaa60(i);
            if (p->m_b8dab0() == 5) {
                Obj_s0102_cd90* planet;
                StarManager_s0102_cd90()->m_bb59b0(p, &planet);
                if (!planet->m_c70c00()) planet->m_c71e70();
                Fn_00c705c0(p, 0x7fffffff);
            }
        }
        Fn_00b3d4a0_s0102_cd90()->m_ae9140((int)nounField_s0102_cd90(sort, 0x70));
        int ctx = GetUniverseContext();
        switch (ctx) {
        case 0:
            Fn_01044640();
            vc3<void>(MessageServer_s0102_cd90(), 0x14, 0x678a3ef, 0, 0);
            PostCommString("SPG_SystemSurrender_Diplomatic_Planet", 0x25);
            break;
        case 1: {
            Obj_s0102_cd90* sys = Fn_01021230_s0102_cd90()->m_c8b770();
            PtrVec_s0102_cd90* list = (PtrVec_s0102_cd90*)((char*)sys + 0x10);
            Obj_s0102_cd90* best = 0;
            Obj_s0102_cd90* inv = GetUFOSimulator_s0102_cd90()->m_a1ad60();
            Vec3_s0102_cd90* pp = vc0<Vec3_s0102_cd90*>((char*)inv + 0x34, 0x2c);
            Vec3_s0102_cd90 P = *pp;
            int n = list->e - list->b;
            for (int i = 0; i < n; i++) {
                Obj_s0102_cd90* it = list->b[i];
                if (it->m_c70e00() == 5) {
                    Vec3_s0102_cd90* q = vc0<Vec3_s0102_cd90*>(list->b[i], 0x2c);
                    float dx = P.x - q->x, dy = P.y - q->y, dz = P.z - q->z;
                    if (dx * dx + dz * dz + dy * dy < 3.40282346e+38f) best = list->b[i];
                }
            }
            if (best) {
                Vec3_s0102_cd90* q = vc0<Vec3_s0102_cd90*>(best, 0x2c);
                Vec3_s0102_cd90 pos = *q;
                Quat_s0102_cd90* o = vc0<Quat_s0102_cd90*>(best, 0x30);
                Quat_s0102_cd90 Q = *o;
                EvtData_s0102_cd90 ev(&pos, &Q);
                ev.f20 = vc0<float>(best, 0x70);
                ev.f1c = vc0<float>(best, 0x74);
                Fn_00b3d4d0_s0102_cd90()->m_ae09b0(0x5f848353, &ev, 0);
                PostCommString("SPG_SystemSurrender_Diplomatic_Solar", 0x24);
            }
            break;
        }
        }
        Fn_00675250_s0102_cd90()->m_676e90(0xd3f14a26, 1);
        SpaceGameGet_s0102_cd90()->m_bfc5f0()->m_fe5430(0x1a, 1);
        GetPlayerEmpire_s0102_cd90()->m_c31a00(-price);
        UIMessage m(0xf46092d2, (int)nounField_s0102_cd90(sort, 0x70));
        ((MsgServer*)MessageServer_s0102_cd90())->Post(0xf46092d2, &m, 0);
    }
    Planet_s0102_cd90* pl = GetActivePlanet_s0102_cd90();
    Fn_00b3d4a0_s0102_cd90()->m_aeb720(arg, pl->emp->m_ce6950(), (int)0xc8fbf7d7, (int)key, 0, 0);
}

// @ 0x0102d7e0
void ClearAttackRequest(void)
{
    Obj_s0102_cd90** begin = g_attackRequestPlanets;
    Obj_s0102_cd90** end = g_attackRequestPlanetsEnd;
    StrCopy(begin, end, 0);
    Obj_s0102_cd90** q = end - (g_attackRequestPlanetsEnd - begin);
    g_attackRequestPlanetsEnd = q;
    g_targetPlanetIndex = -1;
}

// @ 0x0102d820
void Shutdown(void)
{
    SpaceGame* sg = (SpaceGame*)SpaceGameGet_s0102_cd90();
    if (sg->trading->m_1075500())
        ((SpaceGame*)SpaceGameGet_s0102_cd90())->trading->m_1075ef0();
    Fn_00b3d4a0_s0102_cd90()->m_aea210();
    if (!IsWorldLayoutFlagSet(2))
        return;

    LaunchData* obj = (LaunchData*)operator_new6(0x9c, "App", 0, 0, 0, 0);
    if (obj) {
        obj->m_5a9080();
        if (obj) vc0<void>(obj, 4);
    }
    Obj_s0102_cd90* a = Fn_00401090();
    Vec3_s0102_cd90* p = a->m_4df400();
    obj->f010 = *(uint32_t*)&p->x;
    obj->f014 = *(uint32_t*)&p->y;
    obj->f018 = *(uint32_t*)&p->z;
    obj->f00c = 0xa56567f7;
    if (obj->p094) {
        obj->p094 = 0;
        vc0<void>(obj->p094, 4);
    }
    obj->f024 = g_15da7c4;
    obj->f028 = g_15da7c8;
    obj->f02c = g_15da7cc;
    obj->f030 = g_15da7d0;
    obj->f035 = 1;
    obj->f034 = 0;
    obj->f036 = 0;
    obj->f038 = 0;
    obj->f037 = 0;
    obj->f039 = 0;
    obj->f03c = 1;
    obj->f06d = 1;

    TerrainPlayer* tp = NounManager_s0102_cd90()->m_f67d90();
    if (tp) {
        obj->vec.push_back(tp->t10fc);
        obj->vec.push_back(tp->t1100);
        obj->vec.push_back(tp->t1104);
        obj->vec.push_back(tp->t1108);
        obj->vec.push_back(tp->t110c);
    }
    obj->f090 = 0x66787bc;

    Obj_s0102_cd90* player = GetPlayerEmpire_s0102_cd90();
    PlayerObj* pj = (PlayerObj*)player;
    int key = 0x11;
    // (rbtree lookup of the player's feedback string, then basic_string<wchar_t>::assign)
    Fn_00e5c780((char*)pj + 0x14, &key, (void*)((char*)obj + 0x40));

    obj->f03d = 1;
    obj->f064 = 1;
    Fn_00b1dee0(Fn_00b3d320((Obj_s0102_cd90*)obj));
    vc0<void>(obj, 8);
}

// @ 0x0102df20
void DoSpaceCommAction(int* msg, int arg, Obj* mission)
{
    Planet* planet = GetActivePlanet_s0102_df20();

    Obj* at = GetSystemAT();
    int v = at ? vc0<int>(at, 0x20) : 0;
    at = GetSystemAT();
    if (at) {
        vc1<void>(at, 0x38, 0x3475365);
        vc2<void>(at, 0x40, 0x3475381, (int)0x7cd49637);
        vc2<void>(at, 0x40, 0x3475385, v);
        vc0<void>(at, 0x58);
    }

    switch (msg[0]) {
    case (int)0x8a820a27:
        Fn_0102caa0(arg, planet);
        return;
    case (int)0x8a43c6d9:
        Fn_0102c980(planet->emp->m_b8de30());
        LogTail(arg, planet, (int)0x80e15bcf);
        return;
    case (int)0x86eb5442:
        Fn_0102cd30();
        return;
    case (int)0x9320dbba:
        TryPeaceOffer(arg, Fn_0102f810()->m_1030930(3, StarManager()->m_ba9370(arg)));
        return;
    case (int)0x9320dbbb:
        TryPeaceOffer(arg, Fn_0102f810()->m_1030930(4, StarManager()->m_ba9370(arg)));
        return;
    case (int)0x9320dbbc:
        TryPeaceOffer(arg, Fn_0102f810()->m_1030930(1, StarManager()->m_ba9370(arg)));
        return;
    case (int)0x9320dbbd:
        TryPeaceOffer(arg, Fn_0102f810()->m_1030930(2, StarManager()->m_ba9370(arg)));
        return;
    case (int)0x9320dbbf:
        TryPeaceOffer(arg, Fn_0102f810()->m_1030930(0, StarManager()->m_ba9370(arg)));
        return;
    case (int)0x9b18a2fa:
        if (mission) mission->m_c46e20(0);
        return;
    case (int)0xab909e37: {
        Fn_00c8c9d0(Fn_01021240());
        ((Flag44*)Fn_01021230())->flag = 0;
        Fn_00b3d4a0()->m_aea210();
        return;
    }
    case (int)0xa624e3fa: {
        if (!mission) return;
        Obj* m = Fn_00aed3f0(mission);
        if (!m) return;
        if (vc0<int>(m, 0x60) == 0) m->m_c485b0();
        else m->m_c59eb0();
        return;
    }
    case (int)0xacc50317:
        if (mission) mission->m_c485f0();
        return;
    case (int)0xaccf645c:
        SpaceGameGet_s0102_df20()->m_a1ad60()->m_ff45e0(g_key_016de7e4);
        return;
    case (int)0xae44b32e:
    case 0x577614c6:
        RelationshipManager()->m_d06240(arg, GetPlayerEmpireID(), 0x5b6cf09, 1.0f);
        NounManager_s0102_df20()->m_f67d90()->m_c77bf0(0x5f1f0ca);
        LogTail(arg, planet, 0x2ea8fb98);
        return;
    case (int)0xc0816f3b:
        if (mission) mission->m_c485d0();
        return;
    case (int)0xc9cb7680:
        GetUFOSimulator()->m_10019a0();
        return;
    case (int)0xca667561:
        GetUFOSimulator()->m_10027b0(arg, 1);
        LogTail(arg, planet, (int)0xe9146e3c);
        return;
    case (int)0xd13e4ca2:
        GiveGift(arg, 1);
        return;
    case (int)0xd95019bd:
        TryBreakAlliance(arg); // 0x0102cd90
        return;
    case (int)0xd91dba31: {
        if (!mission) return;
        Obj* m = Fn_00aed3f0(mission);
        if (!m) return;
        m->m_c59f60();
        int r = vc0<int>(mission, 0xa4);
        Fn_00b3d4a0()->m_aeb720(arg, planet->emp->m_ce6950(), r, (int)0x8b756f4b, (int)mission, 0);
        return;
    }
    case (int)0xdac9a912:
        GiveGift(arg, 0);
        return;
    case (int)0xeab9e2c9: {
        Obj* emp = StarManager()->m_ba9370(arg);
        Z3 a, b, c, d;
        Fn_00e39ab0(0x16f8fdb4, emp, &d, &c, (int)nounField(Fn_01021240(), 0x70), 0, &b, &a);
        int ctx = GetUniverseContext();
        if (ctx == 0) {
            Fn_01044640();
            vc3<void>(MessageServer(), 0x14, 0x678a3ef, 0, 0);
            Fn_00b3d4d0()->m_ae0930(k_Military_Planet, 1, 0, 0, 0, 0);
        } else if (ctx == 1) {
            Obj* sys = Fn_01021230()->m_c8b770();
            PtrVec* list = (PtrVec*)((char*)sys + 0x10);
            Obj* best = 0;
            Obj* inv = GetUFOSimulator()->m_a1ad60();
            Vec3* pp = vc0<Vec3*>((char*)inv + 0x34, 0x2c);
            Vec3 P = *pp;
            int n = list->e - list->b;
            for (int i = 0; i < n; i++) {
                Obj* it = list->b[i];
                if (Fn_00c8b920((int)nounField(it, 0x13c), GetPlayerEmpireID())) {
                    Vec3* q = vc0<Vec3*>(it, 0x2c);
                    float dx = P.x - q->x, dy = P.y - q->y, dz = P.z - q->z;
                    if (dz * dz + dy * dy + dx * dx < 3.40282346e+38f) best = it;
                }
            }
            if (best) {
                Vec3* q = vc0<Vec3*>(best, 0x2c);
                P = *q;
                Quat* o = vc0<Quat*>(best, 0x30);
                Quat Q = *o;
                EvtData ev(&P, &Q);
                ev.f20 = vc0<float>(best, 0x70);
                ev.f1c = vc0<float>(best, 0x74);
                Fn_00b3d4d0()->m_ae09b0(0x5f848353, &ev, 0);
                Fn_00b3d4d0()->m_ae0930("SPG_SystemSurrender_Military_Solar", 1, 0, 0, 0, 0);
            }
        }
        Obj* avatar = Fn_01021240()->m_b1fdb0();
        Fn_00c8d000(Fn_01021240(), GetPlayerEmpireID());
        int count = 0;
        PtrVec* lst = (PtrVec*)Fn_01021240()->m_bba790();
        int n = lst->e - lst->b;
        for (int i = 0; i < n; i++)
            if (lst->b[i]->m_b8dab0() == 5) count++;
        char ok = (char)Fn_0102b690(avatar, GetPlayerEmpireID(), count);
        Fn_00675250()->m_676e90(0xd3f14a26, 1);
        if (ok) return;
        Fn_00b3d4a0()->m_aea210();
        return;
    }
    case (int)0xe3b5dbdf: {
        if (!mission) return;
        Obj* d = icast_Delivery(mission);
        if (!d) return;
        int got = d->m_c57ef0(arg, planet);
        int r = vc0<int>(mission, 0xa4);
        Fn_00b3d4a0()->m_aeb720(arg, planet->emp->m_ce6950(), r, got, (int)mission, 0);
        return;
    }
    case (int)0xdaff3ce0: {
        Fn_0102daa0(Fn_01021240());
        VecCopy local(g_AttackRequestPlanets);
        LogTail(arg, planet, local.b == local.e ? 0x174890ac : (int)0xac4e8b42);
        return;
    }
    case (int)0xfaa8c815: {
        if (!mission) return;
        Obj* f = icast_Fetch(mission);
        if (!f) {
            Obj* fl = icast_Flight101(mission);
            if (!fl) return;
            f = icast_Fetch(fl->m_c59d90());
            if (!f) return;
        }
        f->m_c52070();
        return;
    }
    case 0x7d5647d: {
        if (!mission) return;
        Obj* m = Fn_00aed3f0(mission);
        if (!m) return;
        m->m_c59f00();
        return;
    }
    case 0xc5d2701:
        Fn_0102cc30(arg, planet);
        return;
    case 0x12293370:
        TryPurchaseOffer(arg, planet->emp->m_b8de30(), Fn_0102f810()->m_102fa30(4));
        return;
    case 0x12293371:
        TryPurchaseOffer(arg, planet->emp->m_b8de30(), Fn_0102f810()->m_102fa30(3));
        return;
    case 0x12293374:
        TryPurchaseOffer(arg, planet->emp->m_b8de30(), Fn_0102f810()->m_102fa30(0));
        return;
    case 0x12293376:
        TryPurchaseOffer(arg, planet->emp->m_b8de30(), Fn_0102f810()->m_102fa30(2));
        return;
    case 0x12293377:
        TryPurchaseOffer(arg, planet->emp->m_b8de30(), Fn_0102f810()->m_102fa30(1));
        return;
    case 0x12d9113a:
        GiveGift(arg, 2);
        return;
    case 0x135594f5: {
        Obj* sort = planet->emp->m_b8de30();
        int key = GetPlayerEmpire_s0102_df20()->m_c313d0(*sort->m_5c65e0());
        int status = (int)0x917bee91;
        Obj* tm = StarManager()->m_ba6490();
        int max = Fn_0102f810()->m_1030390();
        if (max > 0 && tm->m_1037f20() >= max) status = (int)0xdc68eaa0;
        int rel = RelationshipManager()->m_d00a70(arg, GetPlayerEmpireID(), 1);
        if (rel < 3) {
            status = 0x4584b3cd;
        } else if (status == (int)0x917bee91) {
            StarManager()->m_ba6490()->m_10393a0(sort, arg, key, GetPlayerEmpireID());
            SpaceGameGet_s0102_df20()->m_bfc5f0(0x19, 1)->m_fe5430();
        }
        LogTail(arg, planet, status);
        return;
    }
    case 0x1a771205: {
        RelationshipManager()->m_d06240(arg, GetPlayerEmpireID(), 0x594afff, 1.0f);
        Obj* e = StarManager()->m_ba9370(arg);
        e->m_c30bb0();
        Fn_00b3d4a0()->m_aea210();
        ((SpaceGameObj*)SpaceGameGet_s0102_df20())->f14->m_106ac90(e->m_c30c60());
        return;
    }
    case 0x1febc3ea:
        if (mission) mission->m_c485c0();
        return;
    case 0x2027bc64:
        Fn_0102d7e0();
        LogTail(arg, planet, 0x2ea8fb98);
        return;
    case 0x2125a82a:
        RelationshipManager()->m_d06240(arg, GetPlayerEmpireID(), 0x5f62736, 1.0f);
        Fn_00b3d4a0()->m_aea210();
        return;
    case 0x2e42264b:
        NounManager_s0102_df20()->m_f67d90()->m_c7be30(StarManager()->m_ba9370(arg));
        Fn_00b3d4a0()->m_aea210();
        return;
    case 0x307071c8:
        g_TargetPlanetIndex = 0;
        LogTail(arg, planet, GetAttackRequestResponse(arg));
        return;
    case 0x307071cb:
        g_TargetPlanetIndex = 1;
        LogTail(arg, planet, GetAttackRequestResponse(arg));
        return;
    case 0x307071ca:
        g_TargetPlanetIndex = 2;
        LogTail(arg, planet, GetAttackRequestResponse(arg));
        return;
    case 0x307071cd:
        g_TargetPlanetIndex = 3;
        LogTail(arg, planet, GetAttackRequestResponse(arg));
        return;
    case 0x31484f2c:
        TryCreateAlliance(arg);
        return;
    case 0x39a2e1bc:
        Fn_00b3d4a0()->m_aea210();
        return;
    case 0x3de7cb69: {
        uint pid = GetPlayerEmpireID();
        RelationshipManager()->m_d05830(arg, pid);
        Obj* e = StarManager()->m_ba9370(arg);
        RelationshipManager()->m_d038e0(e, GetPlayerEmpire_s0102_df20());
        RelationshipManager()->m_d06240(arg, pid, 0x57e4fe3, 1.0f);
        PtrVec* lst = (PtrVec*)NounManager_s0102_df20()->m_ad49b0();
        int n = lst->e - lst->b;
        for (int i = 0; i < n; i++) {
            Obj* nn = lst->b[i];
            if (nn && (nounField(nn, 0x714) == 8 || nounField(nn, 0x714) == 6)) {
                vc0<void>((char*)nn + 0x508, 0x38);
                Obj* h = (Obj*)nounField(nn, 0x68c);
                if (h) {
                    nounField(nn, 0x68c) = 0;
                    vc0<void>(h, 4);
                }
            }
        }
        Fn_00b3d4a0()->m_aea210();
        return;
    }
    case 0x4c113574: {
        int idx = (int)g_AttackRequestPlanets.b[g_TargetPlanetIndex];
        Obj* t = StarManager()->m_ba6dc0((Obj*)idx);
        Fn_0102d0b0(arg, t);
        GetPlayerEmpire_s0102_df20()->m_c31a00(-Fn_0102f810()->m_1030650((int)t));
        Fn_0102d7e0();
        Fn_00b3d4a0()->m_aea210();
        return;
    }
    case 0x4c182387: {
        Fn_00b3d4a0()->m_aea210();
        Obj* e = StarManager()->m_ba9370(arg);
        Fn_00b3d4a0()->m_aeb3e0(((Emp*)e)->f84, e->m_c30c60(), e->m_c31730()->m_ce6950(),
                                (int)0x95bbbbfc, 0x7fc02fbc, 2, 0, 0);
        return;
    }
    case 0x52b8a79f:
        GetPlayerEmpire_s0102_df20()->m_c31a00(GetSpaceRelationshipTuning_s0102_df20()->f90);
        RelationshipManager()->m_d06240(arg, GetPlayerEmpireID(), 0x594b017, 1.0f);
        Fn_00b3d4a0()->m_aea210();
        return;
    case 0x5c2efcb0: {
        Obj* e = StarManager()->m_ba9370(arg);
        GetPlayerEmpire_s0102_df20()->m_c31a00(-GetSpaceRelationshipTuning_s0102_df20()->m_10407d0(e));
        e->m_c30bb0();
        Fn_00b3d4a0()->m_aea210();
        return;
    }
    case 0x5d79f0cb: {
        if (!mission) return;
        mission->m_c485b0();
        uint pid = GetPlayerEmpireID();
        if (arg != (int)pid) RelationshipManager()->m_d06240(arg, pid, 0x5b6ce81, 1.0f);
        return;
    }
    case 0x6c70b992: {
        Obj* e = StarManager()->m_ba9370(arg);
        RelationshipManager()->m_d06920(e, GetPlayerEmpire_s0102_df20());
        Fn_00b3d4a0()->m_aea210();
        return;
    }
    case 0x75ad98bb:
        Fn_0102cd40();
        return;
    case 0x7b1f7d82:
        Fn_0102c9e0(arg, planet, msg[1]);
        return;
    case 0x7d8aa8be:
        if (mission) mission->m_c485e0();
        return;
    case 0x7e9ccaab:
        Fn_0102d820();
        return;
    }
}
