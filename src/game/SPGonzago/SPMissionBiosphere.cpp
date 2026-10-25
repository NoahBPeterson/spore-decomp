// src/game/SPGonzago/SPMissionBiosphere.cpp -- migrated from slice(s) s00c4cb90, s00c4bc00, s00c4a850 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionBiosphere.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameData.h"
#include "SP/cPlanet.h"
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cSPMission.h"
#include "SP/cStarManager.h"
#include "SP/cVarListSerializer.h"
#include "SP/cSPMissionBase.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cHerd.h"
#include "SP/cSPTimer.h"
#include "SP/cSimPlanetLowLOD.h"
#include "SP/cGameNounManager.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cTribe.h"

// ---- items of slice s00c4a850 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ResourceKey {
    uint32_t mInstanceID;                                   // +0x00
    uint32_t mGroupID;                                      // +0x04
    uint32_t mTypeID;                                       // +0x08
};
template <class T>
struct cVec {
    T*       mpBegin;                                       // +0x00
    T*       mpEnd;                                         // +0x04
    T*       mpCapacity;                                    // +0x08
    void*    mpAllocator;                                   // +0x0c
    uint32_t mPad10;                                        // +0x10

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T&       operator[](uint32_t nIndex) const { return mpBegin[nIndex]; }

    void     push_back(const T& rValue)
    {
        if (mpEnd != mpCapacity) {
            T* pSlot = mpEnd;
            ++mpEnd;
            if (pSlot)
                *pSlot = rValue;
            return;
        }
        DoInsertValue(mpEnd, rValue);
    }

    void     DoInsertValue(T* pPos, const T& rValue);       // 0x00aea5d0
};
struct cPlanet {
    char     mPad000[0x13c];                                // +0x000
    void*    mpData13C;                                     // +0x13c
    char     mPad140[0x2c];                                 // +0x140
};
struct cPlanetRecord;
struct cProperty {
    void*     mpValue;                                      // +0x00
    uint32_t  mPad04;                                       // +0x04
    uint32_t  mCount;                                       // +0x08
    uint32_t  mPad0c;                                       // +0x0c
    uint16_t  mFlags;                                       // +0x10
    uint16_t  mType;                                        // +0x12

    bool*     GetBool();                                    // 0x0041e920
    int32_t*  GetInt();                                     // 0x0041e990
};
struct cPropertyList {
    virtual void        v00();                              // +0x00
    virtual void        v04();                              // +0x04
    virtual void        v08();                              // +0x08
    virtual void        v0c();                              // +0x0c
    virtual void        v10();                              // +0x10
    virtual void        v14();                              // +0x14
    virtual void        v18();                              // +0x18
    virtual void        v1c();                              // +0x1c
    virtual void        v20();                              // +0x20
    virtual bool        Find(uint32_t nKey, cProperty** ppOut);   // +0x24
    virtual cProperty*  Get(uint32_t nKey);                 // +0x28
};
struct cSPMission;
struct cSPMissionMultiDelivery;
struct cPlanetSearch;
struct cSPMission {
    // vtable +0x00 (slots used by this slice: +0x6c, +0x128, +0x16c, +0x170, +0x188)
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
    virtual void Abort();                                   // +0x06c
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual void v090();
virtual void v094();
virtual void v098();
virtual void v09c();
virtual void v0a0();
virtual void v0a4();
virtual void v0a8();
virtual void v0ac();
virtual void v0b0();
virtual void v0b4();
virtual void v0b8();
virtual void v0bc();
virtual void v0c0();
virtual void v0c4();
virtual void v0c8();
virtual void v0cc();
virtual void v0d0();
virtual void v0d4();
virtual void v0d8();
virtual void v0dc();
virtual void v0e0();
virtual void v0e4();
virtual void v0e8();
virtual void v0ec();
virtual void v0f0();
virtual void v0f4();
virtual void v0f8();
virtual void v0fc();
virtual void v100();
virtual void v104();
virtual void v108();
virtual void v10c();
virtual void v110();
virtual void v114();
virtual void v118();
virtual void v11c();
virtual void v120();
virtual void v124();
    virtual bool CheckTargetValid();                        // +0x128
virtual void v12c();
virtual void v130();
virtual void v134();
virtual void v138();
virtual void v13c();
virtual void v140();
virtual void v144();
virtual void v148();
virtual void v14c();
virtual void v150();
virtual void v154();
virtual void v158();
virtual void v15c();
virtual void v160();
virtual void v164();
virtual void v168();
    virtual void OnMissionStarted();                        // +0x16c
    virtual void OnMissionSucceeded();                      // +0x170
virtual void v174();
virtual void v178();
virtual void v17c();
virtual void v180();
    virtual void v184();
    virtual void OnPropertiesLoaded();                      // +0x188

    char           mPad004[0x12c];                          // +0x004 .. +0x12f
    uint32_t       mFlags;                                  // +0x130
    char           mPad134[0x4c];                           // +0x134 .. +0x17f
    cPropertyList* mpPropertyList;                          // +0x180
    int32_t        mField184;                               // +0x184
    int32_t        mField188;                               // +0x188
    char           mPad18c[4];                              // +0x18c
    int32_t        mField190;                               // +0x190
    cVec<ResourceKey> mKeys194;                             // +0x194
    cVec<ResourceKey> mKeys1a8;                             // +0x1a8
    cVec<ResourceKey> mKeys1bc;                             // +0x1bc
    char           mPad1d0[0x20];                           // +0x1d0 .. +0x1ef
    int32_t        mStatus;                                 // +0x1f0
    void*          mpData1f4;                               // +0x1f4
    char           mPad1f8[0xc];                            // +0x1f8 .. +0x203
    int32_t        mField204;                               // +0x204
    int32_t        mField208;                               // +0x208

    char           Init();                                  // 0x00c4ad50
    void           PickGiveOnAcceptItems();                 // 0x00c4a980
    cPlanet*       GetTargetPlanet();                       // 0x00970b30
    void           SetTargetPlanet(void* pPlanet);          // 0x00c47180
    void           SetInitialized();                        // 0x00c4a0c0
    void           TriggerUIUpdate();                       // 0x00c47d80
    int32_t        Update(void* pArg);                      // 0x00c478b0
    void*          PickPlanet(cPlanetSearch* pSearch);      // 0x00c47e20
    uint32_t       ReadTargetPlanetType();                  // 0x00c45b40
    cPlanetRecord* GetPlanetRecordFromTargetType(uint32_t nType);   // 0x00c474b0
};
struct cSPMissionMultiDelivery : cSPMission {
    void    ReturnForRewards();                             // 0x00c4b760
    int32_t Update(void* pArg);                             // 0x00c4b7a0
    bool    IsAtDeliveryTarget(void* pPlanet, ResourceKey* pKey);   // 0x00c4bb60
    bool    InitWrapper();                                  // 0x00c4baa0
    int32_t GetCountA();                                    // 0x00c4bba0
    int32_t GetCountB();                                    // 0x00c4bbc0
};
struct cPlanetSearch {                                      // pick request built by cMissionBalance::Init
    uint32_t mKind;                                         // +0x00 (0x20 / 0x38)
    char     mPad004[0x40];                                 // +0x004

    cPlanetSearch();                                        // 0x00ba7bd0
    ~cPlanetSearch();                                       // 0x00ba8220
};
extern ResourceKey kDeliveryTargetKey;                      // 0x0168f784
// ---- items of slice s00c4a850 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern ResourceKey kDeliveryTargetKey;                      // 0x0168f784

// ---- items of slice s00c4bc00 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
class IProperty;
}
namespace SP {
struct tUShortVector {
    uint16_t* mpBegin;                                  // +0x00
    uint16_t* mpEnd;                                    // +0x04
    uint16_t* mpCapacity;                               // +0x08
};
}
namespace SP {
class cSPMissionBase_s00c4_bc00 {
public:
    void SetSerializer();                               // 0x00c2e4e0
    void TriggerUIUpdate();                             // 0x00c47d80
    void FUN_00c48db0(tUShortVector* pVector);          // 0x00c48db0

    uint8_t      pad000[0x180];                         // +0x000 .. +0x17f
    IProperty*   mpMissionKey;                          // +0x180
    uint8_t      pad184[0x6c];                          // +0x184 .. +0x1ef
    int32_t      mState;                                // +0x1f0
};
}
namespace SP {
class cSPMissionBiosphere : public cSPMissionBase_s00c4_bc00 {
public:
    int GetPlanetCount();
    void UpdateEventLog();
};
}
// ---- items of slice s00c4bc00 end

// ---- items of slice s00c4cb90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_01021260();                   // the active planet
extern "C" void* __cdecl FUN_01021080();                   // living-universe context
extern "C" void* __cdecl FUN_00b3d300();                   // SP::NounManager
extern "C" void* __cdecl FUN_00b3d480();                   // the global cargo manager
extern "C" void* __cdecl FUN_00b3d430();                   // SP::TerraformingManager
extern "C" void* __cdecl FUN_0067dcc0();                   // SP::MessageServer
extern "C" void* __cdecl FUN_01002bd0();                   // SpaceGameGet
extern "C" int   __cdecl FUN_00c4b8f0(void* eco);
extern "C" float __cdecl FUN_00c4bea0(void* prop, void* eco);
extern "C" float __cdecl FUN_00c4bf10(void* prop, void* eco);
extern "C" void* __cdecl FUN_00c4bdc0(void* tmp, void* vec, void* arg);
extern "C" int   __cdecl FUN_00c17350(void* creature, int eff, int one);
extern "C" void  __cdecl FUN_00aca360(void* p);            // (reached through cCargoManager::FUN_00aca360)
extern "C" void  __cdecl FUN_00f47380(void* p);            // operator delete
extern "C" void  __cdecl FUN_006a1250(void* prop, int key, void* out);   // SP::GetPropertyAsKey
extern "C" void  __cdecl FUN_00feff80(void* species, int n, int a, int b, int c, int eff, void* herds);
extern "C" void  FUN_00fe5430(void* tribe, int a, int b);  // (reached through cTribe::FUN_00fe5430)
extern "C" void* __cdecl FUN_00bbcb10(void* a, void* planet);  // (reached through cTerraformingManager)
extern "C" void* __cdecl FUN_00bbf2b0(void* planet);
extern "C" void* __cdecl FUN_00bbe740(void* planet);
extern "C" void* __cdecl FUN_00bbc540(void* a, void* b);
extern "C" float __cdecl FUN_00572a60(float f);            // RandomSigned(float)
extern "C" double __cdecl fabs(double);
extern "C" void* g_168f8f8;        // 0x0168f8f8  key
extern "C" int   g_168f5e4;        // 0x0168f5e4  accumulated herbivore time
extern "C" int   g_157507c;        // 0x0157507c  herbivore time threshold
extern "C" float g_1471064;        // 0x01471064
extern "C" float g_146da50;        // 0x0146da50
extern "C" float g_13ef580;        // 0x013ef580
extern "C" float g_13f9428;        // 0x013f9428  (0.001f)
typedef unsigned int u32;
typedef unsigned char u8;
struct IEmpty {};
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};
struct Vec3 {
    float x, y, z;
};
struct tAllocHeader {                // element count stored in front of every sp_vector block
    u32 mCount;
};
struct cProperty_s00c4_cb90;
struct cPropertyList_s00c4_cb90 : VPad<9, IEmpty> {
    virtual bool GetProperty(u32 key, cProperty_s00c4_cb90** out);          // 0x24
};
struct cProperty_s00c4_cb90 {
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
class cPlanet_s00c4_cb90 {
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
class cSPMission_s00c4_cb90 : public IMission6 {
  public:
    u8             pad004[0x20];                             // +0x04
    u32            mPoliticalID_24;                          // +0x24
    u8             pad028[0x16c - 0x28];                     // +0x28 (handler sub-object at +0x34)
    void*          mpTargetSpecies_16c;                      // +0x16c
    u32            mUnk170_170;                              // +0x170
    u8             pad174[0x180 - 0x174];                    // +0x174
    cPropertyList_s00c4_cb90* mpPropList_180;                           // +0x180

    cPlanet_s00c4_cb90* GetTargetPlanet();                              // 0x00970b30
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
class cSPMissionBiosphere_s00c4_cb90 : public cSPMission_s00c4_cb90 {
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
// ---- items of slice s00c4cb90 end

// @ 0x00c4baa0
bool cSPMissionMultiDelivery::InitWrapper()
{
    return cSPMission::Init();
}

// @ 0x00c4bb60
bool cSPMissionMultiDelivery::IsAtDeliveryTarget(void* pPlanet, ResourceKey* pKey)
{
    if (pPlanet == GetTargetPlanet() &&
        pKey->mInstanceID == kDeliveryTargetKey.mInstanceID &&
        pKey->mGroupID == kDeliveryTargetKey.mGroupID &&
        pKey->mTypeID == kDeliveryTargetKey.mTypeID)
        return true;
    return false;
}

// @ 0x00c4bba0
int32_t cSPMissionMultiDelivery::GetCountA()
{
    if (mStatus == 0)
        return mField208;
    return 0;
}

// @ 0x00c4bbc0
int32_t cSPMissionMultiDelivery::GetCountB()
{
    if (mStatus == 0)
        return mField204;
    return 0;
}

// @ 0x00c4bca0
namespace SP {
float __fastcall FUN_00c4bca0(cSPMissionBase_s00c4_bc00* this_, int unused, void* pParam)
{
    (void)this_;
    (void)pParam;
    return 0.0f;
}
}  // namespace SP

// @ 0x00c4bd00
namespace SP {
void __fastcall FUN_00c4bd00(cSPMissionBase_s00c4_bc00* this_, int unused)
{
    this_->SetSerializer();
    if (this_->mState != 2) {
        this_->mState = 2;
        this_->TriggerUIUpdate();
    }
}
}  // namespace SP

// @ 0x00c4bd30
namespace SP {
void __fastcall FUN_00c4bd30(cSPMissionBase_s00c4_bc00* this_, int unused, tUShortVector* pVector)
{
    if (this_->mState == 1) {
        if (pVector->mpBegin != pVector->mpEnd) {
            *pVector->mpBegin = 0;
            pVector->mpEnd = pVector->mpBegin;
        }
        return;
    }
    this_->FUN_00c48db0(pVector);
}
}  // namespace SP

// @ 0x00c4bf80
namespace SP {
int __thiscall cSPMissionBiosphere::GetPlanetCount()
{
    return 0;
}
}  // namespace SP

// @ 0x00c4c090
namespace SP {
void __fastcall FUN_00c4c090(cSPMissionBase_s00c4_bc00* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00c4c130
namespace SP {
void __fastcall FUN_00c4c130(cSPMissionBase_s00c4_bc00* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00c4c2f0
namespace SP {
void __fastcall cMissionBiosphere_ctor(void* this_, int unused)
{
    (void)this_; (void)unused;
}
}  // namespace SP

// @ 0x00c4c3f0
namespace SP {
void __fastcall FUN_00c4c3f0(cSPMissionBase_s00c4_bc00* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00c4c450
namespace SP {
void __fastcall FUN_00c4c450(cSPMissionBase_s00c4_bc00* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00c4c4b0
namespace SP {
void __thiscall cSPMissionBiosphere::UpdateEventLog()
{
}
}  // namespace SP

// @ 0x00c4c610
namespace SP {
void __fastcall FUN_00c4c610(cSPMissionBase_s00c4_bc00* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00c4c690
namespace SP {
void __fastcall FUN_00c4c690(cSPMissionBase_s00c4_bc00* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00c4c790
namespace SP {
void __fastcall FUN_00c4c790(cSPMissionBase_s00c4_bc00* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00c4c850
namespace SP {
void __fastcall FUN_00c4c850(cSPMissionBase_s00c4_bc00* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00c4c910
namespace SP {
void __fastcall FUN_00c4c910(cSPMissionBase_s00c4_bc00* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00c4cb90
char cSPMissionBiosphere_s00c4_cb90::FindClosestDiseasedAnimal(void* outHerd, Vec3* outPos)
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

// @ 0x00c4ccd0
int cSPMissionBiosphere_s00c4_cb90::FailCurrentPhase()
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

// @ 0x00c4d050
void cSPMissionBiosphere_s00c4_cb90::OnPlanetDeactivate()
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

// @ 0x00c4d150
int cSPMissionBiosphere_s00c4_cb90::UpdateStateMachine(int delta)
{
    int state = cSPMission_s00c4_cb90::Update(delta);
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
