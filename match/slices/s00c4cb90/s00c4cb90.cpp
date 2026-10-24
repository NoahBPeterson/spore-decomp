// Slice s00c4cb90 -- SPGonzago/SPMission.obj (SP::cSPMissionBiosphere state machine and
// message handler: closest-diseased-animal query, phase failure, planet deactivate, the
// biosphere message dispatcher, the herbivore-bonus event-id switchers and small helpers).
//
// The shared src/game/include headers carry the 2008 dev-PDB layout; the retail layout of
// cSPMissionBiosphere is shifted, so the members below are declared at their retail offsets with
// named fields and padN gaps, and vtable slots are reached through stub interfaces that declare
// the slot at its index.
//
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

#pragma warning(disable : 4100)

typedef unsigned int u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------------------------
// vtable / container helpers
// ---------------------------------------------------------------------------------------------
struct IEmpty {};
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};

struct Vec3 {
    float x, y, z;
};

struct tAllocHeader {                // element count stored in front of every sp_vector block
    u32 mCount;
};

// ---------------------------------------------------------------------------------------------
// retail callees without a natural receiver (plain __cdecl, ret 0)
// ---------------------------------------------------------------------------------------------
extern "C" {
void* __cdecl FUN_01021260();                   // the active planet
void* __cdecl FUN_01021080();                   // living-universe context
void* __cdecl FUN_00b3d300();                   // SP::NounManager
void* __cdecl FUN_00b3d480();                   // the global cargo manager
void* __cdecl FUN_00b3d430();                   // SP::TerraformingManager
void* __cdecl FUN_00b3d3d0();
void  __cdecl FUN_00b8e040(void* key);          // (reached through cPlanetEco::SetBiostabilizer)
void* __cdecl FUN_0067dcc0();                   // SP::MessageServer
void* __cdecl FUN_01002bd0();                   // SpaceGameGet
void* __cdecl FUN_00675250();
int   __cdecl FUN_00c03180(void* p);            // (reached through cCreatureBase::GetEmpireID)
int   __cdecl FUN_00c4b8f0(void* eco);
float __cdecl FUN_00c4bea0(void* prop, void* eco);
float __cdecl FUN_00c4bf10(void* prop, void* eco);
void* __cdecl FUN_00c4bdc0(void* tmp, void* vec, void* arg);
int   __cdecl FUN_00c17350(void* creature, int eff, int one);
void  __cdecl FUN_00aca360(void* p);            // (reached through cCargoManager::FUN_00aca360)
void  __cdecl FUN_00f47380(void* p);            // operator delete
void  __cdecl FUN_006a1250(void* prop, int key, void* out);   // SP::GetPropertyAsKey
void  __cdecl FUN_006a12a0(void* prop, int key, void* out);   // SP::GetPropertyAsKeyInstance
void* __cdecl FUN_00ae33b0(void* p);            // OnAbduction helper
void  __cdecl FUN_00feff80(void* species, int n, int a, int b, int c, int eff, void* herds);
void  __cdecl FUN_00fefbb0(void* species, void* herd, int one, int political, int eff);
void  FUN_00fe5430(void* tribe, int a, int b);  // (reached through cTribe::FUN_00fe5430)
void* __cdecl FUN_00bbcb10(void* a, void* planet);  // (reached through cTerraformingManager)
void* __cdecl FUN_00bbf2b0(void* planet);
void* __cdecl FUN_00bbe740(void* planet);
void* __cdecl FUN_00bbc540(void* a, void* b);
void  __cdecl FUN_00676e90(void* a, int key, int n);
float __cdecl FUN_00572a60(float f);            // RandomSigned(float)
double __cdecl fabs(double);
}

// ---------------------------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------------------------
extern "C" void* g_168f8f8;        // 0x0168f8f8  key
extern "C" int   g_168f5e4;        // 0x0168f5e4  accumulated herbivore time
extern "C" int   g_157507c;        // 0x0157507c  herbivore time threshold
extern "C" float g_1471064;        // 0x01471064
extern "C" float g_146da50;        // 0x0146da50
extern "C" float g_13ef580;        // 0x013ef580
extern "C" float g_13f9428;        // 0x013f9428  (0.001f)

// ---------------------------------------------------------------------------------------------
// cSPMission interfaces (only the slots this slice calls are named)
// ---------------------------------------------------------------------------------------------
struct cProperty;
struct cPropertyList : VPad<9, IEmpty> {
    virtual bool GetProperty(u32 key, cProperty** out);          // 0x24
};

struct cProperty {
    u8    pad00[0x12];
    short mType;                                                 // +0x12
    int*  GetUInt();                                             // 0x0041ea00
};

struct IMission0 : VPad<27, IEmpty> {
    virtual void StartCompletedFeedbackTimer();                  // 0x06c
};
struct IMission1 : VPad<46, IMission0> {
    virtual bool SetupTargetPlanet();                            // 0x128
};
struct IMission2 : VPad<8, IMission1> {
    virtual void AddMessageHandler(u32 message);                 // 0x14c
};
struct IMission3 : IMission2 {
    virtual void RemoveMessageHandler(u32 message);              // 0x150
};
struct IMission4 : VPad<6, IMission3> {
    virtual void PreInit();                                      // 0x16c
};
struct IMissionVtbl : IMission4 {
    virtual void DataExportOnInit();                             // 0x170
};
struct IMission6 : VPad<6, IMissionVtbl> {
    virtual bool IsPhaseComplete();                              // 0x18c
};

struct IMessageServer : VPad<5, IEmpty> {
    virtual void SendEvent(int id, int a, int b);                // 0x14
};

struct IPlantSpecies : VPad<6, IEmpty> {
    virtual void* FUN_v18();                                     // 0x18
};

// ---------------------------------------------------------------------------------------------
// support classes
// ---------------------------------------------------------------------------------------------
struct cSPTimer {                                            // 0x30 bytes
    u8        pad00[0x30];
    void      Restart();                                     // 0x00bc3130
    long long GetElapsedTime();                              // 0x00bc3190
};

struct cHerd;
struct cHerdPtrVector {
    cHerd** mpBegin;                                         // +0x00
    cHerd** mpEnd;                                           // +0x04
    cHerd** mpCapacity;                                      // +0x08
    void    Erase(cHerd** first, cHerd** last);              // 0x00e25bd0
};

struct cLocomotive : VPad<11, IEmpty> {
    virtual const Vec3* GetPosition();                       // 0x2c
};

class cCreatureBase {
  public:
    u8          pad000[0xc0];
    cLocomotive mLoco_c0;                                    // +0xc0 (vfptr only)
    u8          pad_c4[0x135 - 0xc4];
    bool        mbFlag_135;                                  // +0x135
    u8          pad136[0xb5e - 0x136];
    bool        mbFlag_b5e;                                  // +0xb5e
    u8          padb5f[0xb62 - 0xb5f];
    bool        mbFlag_b62;                                  // +0xb62

    int   GetEmpireID();                                     // 0x00c03180
    void* GetSpeciesProfile();                               // 0x00c0bbd0
    int   GetDamageState();                                  // 0x008e7f80
    void* GetHerd();                                         // 0x00c04590
};

struct cHerd {
    u8              pad00[0x40];
    cCreatureBase** mpMembers_40;                            // +0x40
    cCreatureBase** mpMembersEnd_44;                         // +0x44
};

struct Vec3Vector {
    Vec3* mpBegin;                                           // +0x00
    Vec3* mpEnd;                                             // +0x04
    Vec3* mpCapacity;                                        // +0x08
    void  DoInsertValue(Vec3* insertPos, const Vec3* value);  // 0x004b5ad0
};

struct cSpeciesProfile {                                     // the descriptor stored at mission+0x16c
    u8 pad000[0x504];
    u8 mData_504;                                            // +0x504
};

struct cTerraformingManager {
    cTerraformingManager* FUN_00bbcb10(void* a, void* planet);   // 0x00bbcb10
    cTerraformingManager* FUN_00bbf2b0(void* planet);            // 0x00bbf2b0
    cTerraformingManager* FUN_00bbe740(void* planet);            // 0x00bbe740
    cTerraformingManager* FUN_00bbc540(void* a, void* b);        // 0x00bbc540
};

struct cCargoManager {
    void FUN_00aca360(void* creature);                       // 0x00aca360
};

struct cVoidPtrVector {
    void** mpBegin;                                          // +0x00
    void** mpEnd;                                            // +0x04
};

class cNounManager {
  public:
    void*           FUN_00f67d90();                          // 0x00f67d90
    cVoidPtrVector* FUN_00ace2f0();                          // 0x00ace2f0
};

struct cTribe {
    void FUN_00fe5430(int a, int b);                         // 0x00fe5430
};

struct cSpaceGame {
    cTribe* GetPlayerTribe();                                // 0x00bfc5f0
    void    FUN_01005d80(int a, int b);                      // 0x01005d80
};

struct cNounObj {                                            // object returned by NounManager::FUN_00f67d90
    void FUN_00c75cc0(int key, u32 ev);                      // 0x00c75cc0 (ret 8)
};

struct c6_75250Obj {                                       // object returned by FUN_00675250
    void FUN_00676e90(int a, int b);                       // 0x00676e90 (ret 8)
};

struct cB3d3d0Obj {                                          // object returned by FUN_00b3d3d0
    void FUN_0103dcc0();                                     // 0x0103dcc0
};

struct cPlanetEco {                                          // object stored at planet+0x13c
    u8     pad000[0xbc];
    Vec3*  mpVecA_bc;                                        // +0xbc
    Vec3*  mpVecAEnd_c0;                                     // +0xc0
    u8     padC4[0xd0 - 0xc4];
    Vec3*  mpVecB_d0;                                        // +0xd0
    Vec3*  mpVecBEnd_d4;                                     // +0xd4
    void   SetBiostabilizer(void* key);                      // 0x00b8e040
};

class cSimPlanetLowLOD {
  public:
    void FUN_00c830f0(int dt);                               // 0x00c830f0
    void FUN_00c7e2f0(int a);                                // 0x00c7e2f0
};

class cPlanet {
  public:
    u8                pad000[0x13c];
    cPlanetEco*       mpEco_13c;                             // +0x13c
    cSimPlanetLowLOD* GetSim();                              // 0x008414c0
    bool              HasAnimalSpecies(void* species);       // 0x00c70d10
    int               FUN_00c70fb0();                        // 0x00c70fb0
    void*             GetRandomPlantSpecies();               // 0x00c70c90
    float             FUN_00c709d0();                        // 0x00c709d0
    float             FUN_00c70a20();                        // 0x00c70a20
    void              FUN_00c70a00(float f);                 // 0x00c70a00
    void              FUN_00c70a50(float f);                 // 0x00c70a50
};

// ---------------------------------------------------------------------------------------------
// SP::cSPMission -- shared base of the biosphere mission
// ---------------------------------------------------------------------------------------------
class cSPMission : public IMission6 {
  public:
    u8             pad004[0x20];                             // +0x04
    u32            mPoliticalID_24;                          // +0x24
    u8             pad028[0x16c - 0x28];                     // +0x28 (handler sub-object at +0x34)
    void*          mpTargetSpecies_16c;                      // +0x16c
    u32            mUnk170_170;                              // +0x170
    u8             pad174[0x180 - 0x174];                    // +0x174
    cPropertyList* mpPropList_180;                           // +0x180

    cPlanet* GetTargetPlanet();                              // 0x00970b30
    int      Update(int delta);                              // 0x00c478b0
    void     UpdateEventLog(int a, int b);                   // 0x00c4c4b0
    void     ValidateProgressEvent();                        // 0x00c44f20
    void     TriggerUIUpdate();                              // 0x00c47d80
    void     UnkC690(void* p);                               // 0x00c4c690
    void     UnkC790(void* p);                               // 0x00c4c790
    void     UnkC610(int v);                                 // 0x00c4c610
    void     UnkC2e4e0();                                    // 0x00c2e4e0
    void     UnkC471c0();                                    // 0x00c471c0
    void     UnkC472e0();                                    // 0x00c472e0
    void     UnkC46b80();                                    // 0x00c46b80
    void     UnkC44b80();                                    // 0x00c44b80
    void     UnkC44bd0();                                    // 0x00c44bd0
    int      GetDiseaseEffectID();                           // 0x00c4bd60
};

// ---------------------------------------------------------------------------------------------
// SP::cSPMissionBiosphere -- the state machine of the biosphere mission
// ---------------------------------------------------------------------------------------------
class cSPMissionBiosphere : public cSPMission {
  public:
    u8             pad184[0x1f0 - 0x184];                    // +0x184
    int            mState_1f0;                               // +0x1f0
    u32            mEventID_1f4;                             // +0x1f4
    int            mThreshold_1f8;                           // +0x1f8
    int            mThreshold_1fc;                           // +0x1fc
    int            mCount_200;                               // +0x200
    int            mCount_204;                               // +0x204
    int            mCount_208;                               // +0x208
    int            mCount_20c;                               // +0x20c
    int            mCount_210;                               // +0x210
    u8             pad214[0x218 - 0x214];                    // +0x214
    cSPTimer       mTimer_218;                               // +0x218
    cHerdPtrVector mHerds_248;                               // +0x248

    char FindClosestDiseasedAnimal(void* outHerd, Vec3* outPos);   // 0x00c4cb90 (ret 8)
    int  FailCurrentPhase();                                       // 0x00c4ccd0
    void OnPlanetDeactivate();                                     // 0x00c4d050
    int  UpdateStateMachine(int delta);                            // 0x00c4d150 (ret 4)
    void ReportEventLate();                                        // 0x00c4d830
    void ReportEventEarly();                                       // 0x00c4d920
    void TriggerHerbivoreBonus();                                  // 0x00c4da10
    void BeginHerbivorePhase();                                    // 0x00c4db40
    void GetPropertyInstance(void* key, int* out);                 // 0x00c4db90 (ret 8)
};

// the message-handler sub-object embedded at mission+0x34
struct cBiosphereHandler {
    void HandleMessage(u32 message, void* data);             // 0x00c4a6b0
    void DispatchMessage(u32 message, void* data);           // 0x00c4d590 (ret 8)
};

// the class whose list 0x00c4db00 searches (its this has a pointer vector at +0x200)
struct cMissionKeys {
    u8   pad000[0x200];
    int* mpKeys_200;                                         // +0x200
    int* mpKeysEnd_204;                                      // +0x204
    char ContainsKey(int key);                               // 0x00c4db00 (ret 4)
};

// =============================================================================================
// 0x00c4cb90 -- cSPMissionBiosphere::FindClosestDiseasedAnimal (ret 8)
// =============================================================================================
// @ 0x00c4cb90
char cSPMissionBiosphere::FindClosestDiseasedAnimal(void* outHerd, Vec3* outPos)
{
    int count = mHerds_248.mpEnd - mHerds_248.mpBegin;
    Vec3Vector out;
    out.mpBegin = 0;
    out.mpEnd = 0;
    out.mpCapacity = 0;
    Vec3 tmp;
    for (int i = 0; i < count; i++) {
        cHerd* herd = mHerds_248.mpBegin[i];
        int n = herd->mpMembersEnd_44 - herd->mpMembers_40;
        for (int j = 0; j < n; j++) {
            cCreatureBase* a = herd->mpMembers_40[j];
            if (a->mbFlag_b62 && !a->mbFlag_b5e) {
                const Vec3* pos = a->mLoco_c0.GetPosition();
                if (out.mpEnd != out.mpCapacity) {
                    Vec3* slot = out.mpEnd;
                    out.mpEnd++;
                    if (slot)
                        *slot = *pos;
                } else {
                    out.DoInsertValue(out.mpEnd, pos);
                }
            }
        }
    }
    char found = (out.mpBegin != out.mpEnd);
    if (found) {
        Vec3* r = (Vec3*)FUN_00c4bdc0(&tmp, &out, outHerd);
        *outPos = *r;
    }
    if (out.mpBegin && ((tAllocHeader*)out.mpBegin - 1)->mCount != 0)
        FUN_00f47380(out.mpBegin);
    return found;
}

// =============================================================================================
// 0x00c4ccd0 -- cSPMissionBiosphere::FailCurrentPhase
// =============================================================================================
// @ 0x00c4ccd0
int cSPMissionBiosphere::FailCurrentPhase()
{
    if (mState_1f0 != 0)
        return 3;
    if (mpTargetSpecies_16c == 0)
        return 6;

    bool onActive = false;
    if (GetTargetPlanet() == FUN_01021260()) {
        onActive = true;
        if (FUN_01021080() != 0)
            onActive = false;
    }
    ValidateProgressEvent();
    UpdateEventLog(0, (-(int)onActive & 0xff79c673) + 0x357ae5b4);

    cHerd** it = mHerds_248.mpBegin;
    cHerd** end = mHerds_248.mpEnd;
    while (it != end) {
        cHerd* herd = *it;
        int n = herd->mpMembersEnd_44 - herd->mpMembers_40;
        for (int j = 0; j < n; j++) {
            cCreatureBase* a = herd->mpMembers_40[j];
            if (a && a->GetEmpireID() == (int)mPoliticalID_24) {
                int key[3];
                int eff;
                if (!mpPropList_180) {
                    eff = -1;
                } else {
                    key[0] = 0;
                    key[1] = 0;
                    key[2] = 0;
                    FUN_006a1250(mpPropList_180, 0x7a2db2dd, key);
                    eff = key[0];
                }
                FUN_00c17350(a, eff, 1);
                ((cCargoManager*)FUN_00b3d480())->FUN_00aca360(a);
            }
        }
        it++;
    }
    mHerds_248.Erase(mHerds_248.mpBegin, mHerds_248.mpEnd);

    FUN_00bbcb10(&((cSpeciesProfile*)mpTargetSpecies_16c)->mData_504, GetTargetPlanet());
    FUN_00bbf2b0(GetTargetPlanet());
    FUN_00bbe740(GetTargetPlanet());

    mpTargetSpecies_16c = 0;
    mTimer_218.Restart();

    if (FUN_00c4b8f0(GetTargetPlanet()->mpEco_13c) >= mCount_200) {
        if (!IsPhaseComplete())
            return 6;
        mCount_210 = 0;
        mCount_208 = 0;
        if (onActive)
            FUN_00feff80(mpTargetSpecies_16c, mCount_204, 1, 2, mPoliticalID_24,
                         GetDiseaseEffectID(), &mHerds_248);
        UpdateEventLog(2, (-(GetTargetPlanet() != FUN_01021260()) & 0x92568317) + 0xf8142a0e);
        return 3;
    }

    if (mState_1f0 != 1) {
        mState_1f0 = 1;
        TriggerUIUpdate();
    }
    GetTargetPlanet()->GetSim()->FUN_00c7e2f0(1);
    float a = GetTargetPlanet()->FUN_00c709d0();
    if (fabs(a - g_1471064) < g_146da50) {
        float b = GetTargetPlanet()->FUN_00c70a20();
        if (fabs(b - g_1471064) < g_146da50) {
            GetTargetPlanet()->FUN_00c70a00(FUN_00572a60(g_13ef580) + a);
            GetTargetPlanet()->FUN_00c70a50(FUN_00572a60(g_13ef580) + b);
        }
    }
    UpdateEventLog(2, (-(GetTargetPlanet() != FUN_01021260()) & 0xd7de1a37) + 0x4fd65556);
    return 3;
}

// =============================================================================================
// 0x00c4d050 -- cSPMissionBiosphere::OnPlanetDeactivate
// =============================================================================================
// @ 0x00c4d050
void cSPMissionBiosphere::OnPlanetDeactivate()
{
    int key[3];
    int eff;
    FUN_00b3d300();
    if (!mpPropList_180) {
        eff = -1;
    } else {
        key[0] = 0;
        key[1] = 0;
        key[2] = 0;
        FUN_006a1250(mpPropList_180, 0x7a2db2dd, key);
        eff = key[0];
    }
    cHerd** it = mHerds_248.mpBegin;
    cHerd** end = mHerds_248.mpEnd;
    while (it != end) {
        cHerd* herd = *it;
        int n = herd->mpMembersEnd_44 - herd->mpMembers_40;
        for (int j = 0; j < n; j++) {
            cCreatureBase* a = herd->mpMembers_40[j];
            if (a) {
                int pid = mPoliticalID_24;
                if (a->GetEmpireID() == pid) {
                    FUN_00c17350(a, eff, 1);
                    ((cCargoManager*)FUN_00b3d480())->FUN_00aca360(a);
                }
            }
        }
        it++;
    }
    mHerds_248.Erase(mHerds_248.mpBegin, mHerds_248.mpEnd);
    TriggerUIUpdate();
}

// =============================================================================================
// 0x00c4d150 -- cSPMissionBiosphere::UpdateStateMachine (ret 4)
// =============================================================================================
// @ 0x00c4d150
int cSPMissionBiosphere::UpdateStateMachine(int delta)
{
    int state = cSPMission::Update(delta);
    cPlanetEco* eco = GetTargetPlanet()->mpEco_13c;
    eco->SetBiostabilizer(g_168f8f8);
    if (state != 3)
        return state;

    if (GetTargetPlanet()->FUN_00c70fb0() < (int)mEventID_1f4) {
        UpdateEventLog(1, (-(GetTargetPlanet() != FUN_01021260()) & 0x866a22cd) + 0x274a455f);
        return state + 3;
    }

    switch (mState_1f0) {
    case 2:
        UpdateEventLog(3, 0x90b73292);
        {
            cTribe* tribe = ((cSpaceGame*)FUN_01002bd0())->GetPlayerTribe();
            if (tribe)
                tribe->FUN_00fe5430(9, 1);
        }
        ((IMessageServer*)FUN_0067dcc0())->SendEvent(0xf46092d9, 0, 0);
        return 5;

    case 0:
        if (GetTargetPlanet()->HasAnimalSpecies(&mUnk170_170)) {
            if (mCount_20c - mCount_210 > 0) {
                long long elapsed = mTimer_218.GetElapsedTime();
                float limit = FUN_00c4bea0(mpPropList_180, eco);
                if ((float)elapsed * g_13f9428 > limit) {
                    if (FUN_01021080() != 0)
                        break;
                    if (GetTargetPlanet() != FUN_01021260())
                        break;
                    g_168f5e4 += delta;
                    if (g_168f5e4 <= g_157507c)
                        break;
                    g_168f5e4 = 0;
                    int count = 0;
                    cVoidPtrVector* v = ((cNounManager*)FUN_00b3d300())->FUN_00ace2f0();
                    for (void** p = v->mpBegin; p != v->mpEnd; p++) {
                        cCreatureBase* c = (cCreatureBase*)*p;
                        if (c->GetSpeciesProfile() == mpTargetSpecies_16c && c->mbFlag_b62 &&
                            c->mbFlag_135 && !c->mbFlag_b5e)
                            count++;
                    }
                    if (count >= mCount_204 - mCount_208)
                        break;
                    FUN_00feff80(mpTargetSpecies_16c, (mCount_204 - mCount_208) - count, 1, 2,
                                 mPoliticalID_24, GetDiseaseEffectID(), &mHerds_248);
                    break;
                }
                return FailCurrentPhase();
            }
            UpdateEventLog(0, 0xc4deccc8);
        }
        return FailCurrentPhase();

    case 1:
        if (GetTargetPlanet() != FUN_01021260())
            GetTargetPlanet()->GetSim()->FUN_00c830f0(delta);
        {
            long long elapsed = mTimer_218.GetElapsedTime();
            float limit = FUN_00c4bf10(mpPropList_180, eco);
            if (limit < (float)elapsed * g_13f9428) {
                mTimer_218.Restart();
                IPlantSpecies* plant = (IPlantSpecies*)GetTargetPlanet()->GetRandomPlantSpecies();
                if (plant) {
                    void* a = plant->FUN_v18();
                    cTerraformingManager* tm = (cTerraformingManager*)FUN_00b3d430();
                    tm->FUN_00bbc540(a, GetTargetPlanet());
                    tm->FUN_00bbf2b0(GetTargetPlanet());
                    tm->FUN_00bbe740(GetTargetPlanet());
                    UpdateEventLog(0,
                        (-(GetTargetPlanet() != FUN_01021260()) & 0xc1226e27) + 0x60c074f0);
                }
            }
        }
        {
            cPlanetEco* e = GetTargetPlanet()->mpEco_13c;
            if (e->mpVecBEnd_d4 - e->mpVecB_d0 < mThreshold_1fc)
                break;
            if (e->mpVecAEnd_c0 - e->mpVecA_bc < mThreshold_1f8)
                break;
            if (GetTargetPlanet()->FUN_00c70fb0() < (int)mEventID_1f4)
                break;
            UpdateEventLog(3, 0x90b73292);
            cTribe* tribe = ((cSpaceGame*)FUN_01002bd0())->GetPlayerTribe();
            if (tribe)
                tribe->FUN_00fe5430(9, 1);
            ((IMessageServer*)FUN_0067dcc0())->SendEvent(0xf46092d9, 0, 0);
            return 5;
        }
    }
    return state;
}

// =============================================================================================
// 0x00c4d590 -- cBiosphereHandler::DispatchMessage (ret 8)
// =============================================================================================
// @ 0x00c4d590
void cBiosphereHandler::DispatchMessage(u32 msg, void* arg)
{
    // the handler sub-object is embedded in its owner at +0x34; recover the mission
    cSPMissionBiosphere* self = (cSPMissionBiosphere*)((char*)this - 0x34);
    if (msg <= 0x3029f11u) {
        if (msg == 0x3029f11u) {
            if (self->GetTargetPlanet() == FUN_01021260()) {
                void* p = *(void**)((char*)arg + 8);
                if (!p)
                    self->UnkC790(0);
                else
                    self->UnkC790((*(void* (__thiscall**)(void*, u32))((char*)*(void**)p + 8))(p, 0xce9f6639u));
            }
        } else if (msg == 0x1622184u) {
            if (self->GetTargetPlanet() == FUN_01021260()) {
                cCreatureBase* a1 = (cCreatureBase*)*(void**)((char*)arg + 8);
                void* a2 = *(void**)((char*)arg + 0x10);
                if (a1->GetDamageState() == 2) {
                    if (!a2 || !(*(char (__thiscall**)(void*, u32))((char*)*(void**)a2 + 0x5c))(a2, 0xd0036e08u))
                        self->UnkC690(a1);
                    else {
                        cCreatureBase* ani = (cCreatureBase*)FUN_00ae33b0(a1);
                        if (ani && ani->mbFlag_b62 && ani->GetEmpireID() == (int)self->mPoliticalID_24) {
                            void* herd = ani->GetHerd();
                            if (herd)
                                FUN_00fefbb0(self->mpTargetSpecies_16c, herd, 1,
                                             self->mPoliticalID_24, self->GetDiseaseEffectID());
                        }
                    }
                }
            }
        } else if (msg == 0x2489760u) {
            if (*(void**)((char*)arg + 8) == (void*)self->GetTargetPlanet())
                self->OnPlanetDeactivate();
        }
    } else if (msg == 0x5e37a53u) {
        void* active = FUN_01021260();
        if (active == (void*)self->GetTargetPlanet())
            self->UnkC610(1);
    }
    HandleMessage(msg, arg);
}

// =============================================================================================
// 0x00c4d830 -- cSPMissionBiosphere::ReportEventLate
// =============================================================================================
// @ 0x00c4d830
void cSPMissionBiosphere::ReportEventLate()
{
    UnkC44b80();
    switch (mEventID_1f4) {
    case 0x24baa909u: AddMessageHandler(0xf46092da); break;
    case 0x4bf9b404u: AddMessageHandler(0xf46092d4); break;
    case 0x519c1e5du: AddMessageHandler(0xf46092d8); break;
    case 0x60678523u: AddMessageHandler(0x04445d43); break;
    case 0x89f8a63au: AddMessageHandler(0xf46092d5); break;
    case 0xd91d5c7bu: AddMessageHandler(0xf46092db); break;
    case 0xda05d5c1u: AddMessageHandler(0xf46092c1); break;
    case 0xf9f35d90u: AddMessageHandler(0x04446533); break;
    }
}

// =============================================================================================
// 0x00c4d920 -- cSPMissionBiosphere::ReportEventEarly
// =============================================================================================
// @ 0x00c4d920
void cSPMissionBiosphere::ReportEventEarly()
{
    UnkC44bd0();
    switch (mEventID_1f4) {
    case 0x24baa909u: RemoveMessageHandler(0xf46092da); break;
    case 0x4bf9b404u: RemoveMessageHandler(0xf46092d4); break;
    case 0x519c1e5du: RemoveMessageHandler(0xf46092d8); break;
    case 0x60678523u: RemoveMessageHandler(0x04445d43); break;
    case 0x89f8a63au: RemoveMessageHandler(0xf46092d5); break;
    case 0xd91d5c7bu: RemoveMessageHandler(0xf46092db); break;
    case 0xda05d5c1u: RemoveMessageHandler(0xf46092c1); break;
    case 0xf9f35d90u: RemoveMessageHandler(0x04446533); break;
    }
}

// =============================================================================================
// 0x00c4da10 -- cSPMissionBiosphere::TriggerHerbivoreBonus
// =============================================================================================
// @ 0x00c4da10
void cSPMissionBiosphere::TriggerHerbivoreBonus()
{
    UnkC46b80();
    u32 ev = 0xa5656e84;
    switch (mEventID_1f4) {
    case 0x24baa909u: ev = 0xd9c806e4; break;
    case 0x4bf9b404u: ev = 0x50fee6bf; break;
    case 0x519c1e5du: ev = 0x9ce4639c; break;
    case 0x60678523u: ev = 0xb436c0bc; break;
    case 0x89f8a63au: ev = 0xb40d2187; break;
    case 0xd91d5c7bu: ev = 0xcf6c2ab4; break;
    case 0xda05d5c1u: ev = 0xb7cb9f7a; break;
    case 0xf9f35d90u: ev = 0x2b35f523; break;
    }
    ((cNounObj*)((cNounManager*)FUN_00b3d300())->FUN_00f67d90())->FUN_00c75cc0(0x2db6dad3, ev);
    ((cSpaceGame*)FUN_01002bd0())->GetPlayerTribe()->FUN_00fe5430(0x1e, 1);
    ((c6_75250Obj*)FUN_00675250())->FUN_00676e90(0x4a559e78, 1);
    ((cSpaceGame*)FUN_01002bd0())->FUN_01005d80(0, 1);
    ((cB3d3d0Obj*)FUN_00b3d3d0())->FUN_0103dcc0();
}

// =============================================================================================
// 0x00c4db00 -- cMissionKeys::ContainsKey (ret 4)
// =============================================================================================
// @ 0x00c4db00
char cMissionKeys::ContainsKey(int key)
{
    for (int i = 0; i < (int)(mpKeysEnd_204 - mpKeys_200); i++)
        if (mpKeys_200[i] == key)
            return true;
    return false;
}

// =============================================================================================
// 0x00c4db40 -- cSPMissionBiosphere::BeginHerbivorePhase
// =============================================================================================
// @ 0x00c4db40
void cSPMissionBiosphere::BeginHerbivorePhase()
{
    UnkC2e4e0();
    if (mState_1f0 == 1)
        return;
    StartCompletedFeedbackTimer();
    if (mState_1f0 != 1) {
        mState_1f0 = 1;
        TriggerUIUpdate();
    }
    UnkC472e0();
    UnkC471c0();
}

// =============================================================================================
// 0x00c4db90 -- cSPMissionBiosphere::GetPropertyInstance (ret 8)
// =============================================================================================
// @ 0x00c4db90
void cSPMissionBiosphere::GetPropertyInstance(void* key, int* out)
{
    FUN_006a12a0(mpPropList_180, 0xf924ed01, key);
    cPropertyList* prop = mpPropList_180;
    if (!prop)
        return;
    cProperty* p;
    if (prop->GetProperty(0xf924ed02, &p))
        if (p->mType == 10)
            *out = *p->GetUInt();
}