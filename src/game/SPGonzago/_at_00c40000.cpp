// src/game/SPGonzago/_at_00c40000.cpp -- migrated from slice(s) s00c4dbf0, s00c4cb90, s00c4bc00, s00c4a850 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00c40000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameData.h"
#include "SP/cPlanet.h"
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cSPMission.h"
#include "SP/cStarManager.h"
#include "SP/cVarListSerializer.h"
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
struct cGameData {
    virtual void       AddRef();                            // +0x00
    virtual void       Release();                           // +0x04
    virtual void       v08();                               // +0x08
    virtual cGameData* Cast(uint32_t nType);                // +0x0c
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
struct cPlanetSearch {                                      // pick request built by cMissionBalance::Init
    uint32_t mKind;                                         // +0x00 (0x20 / 0x38)
    char     mPad004[0x40];                                 // +0x004

    cPlanetSearch();                                        // 0x00ba7bd0
    ~cPlanetSearch();                                       // 0x00ba8220
};
struct cSPMissionAdventureBase : cSPMission {
    void* PickAdventureAsset();                             // 0x00c4b220
    bool  RerollAdventureAsset();                           // 0x00c4b250
    void  InitAdventure();                                  // 0x00c4b2b0
};
struct cStarManager {
    bool PickRandomAsset();                                 // 0x00bb7940
    cGameData* GetBannerByID(uint32_t nID);                 // 0x00ba6d80
    void* GetEmpireByID();                                  // 0x00ba9370
};
cStarManager*          __stdcall StarManager(uint32_t nID);             // 0x00b3d2a0
cStarManager*          __stdcall StarManager(void* pObject);            // 0x00b3d2a0
cStarManager*          __stdcall StarManager(void* pOut, int32_t nKind);   // 0x00b3d2a0
cStarManager*          __stdcall StarManager(void* pA, void* pB);       // 0x00b3d2a0
void*  __stdcall FUN_01021300(void* pAsset);                            // 0x01021300
void   __fastcall FUN_00baf790(cStarManager* pThis);                    // 0x00baf790
void*  __stdcall FUN_00b3d360(void* pPlanet);                           // 0x00b3d360
void   __fastcall FUN_00b7d580(void* pThis);                            // 0x00b7d580
// ---- items of slice s00c4a850 end

// ---- items of slice s00c4bc00 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
class IProperty;
}
namespace SP {
bool __cdecl GetPropertyAsKey(IProperty* pProperty, uint32_t keyId, void* pOut); // 0x006a1250
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
class cSPMissionEradicate : public cSPMissionBase_s00c4_bc00 {
public:
    uint32_t GetDiseaseEffectID();
};
}
// ---- items of slice s00c4bc00 end

// ---- items of slice s00c4cb90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00b3d300();                   // SP::NounManager
extern "C" void* __cdecl FUN_00b3d3d0();
extern "C" void* __cdecl FUN_01002bd0();                   // SpaceGameGet
extern "C" void* __cdecl FUN_00675250();
extern "C" void  __cdecl FUN_006a12a0(void* prop, int key, void* out);   // SP::GetPropertyAsKeyInstance
extern "C" void  FUN_00fe5430(void* tribe, int a, int b);  // (reached through cTribe::FUN_00fe5430)
extern "C" void  __cdecl FUN_00676e90(void* a, int key, int n);
typedef unsigned int u32;
typedef unsigned char u8;
struct IEmpty {};
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};
struct Vec3 {
    float x, y, z;
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
class cSPMissionBiosphere : public cSPMission_s00c4_cb90 {
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
struct cMissionKeys {
    u8   pad000[0x200];
    int* mpKeys_200;                                         // +0x200
    int* mpKeysEnd_204;                                      // +0x204
    char ContainsKey(int key);                               // 0x00c4db00 (ret 4)
};
// ---- items of slice s00c4cb90 end

// ---- items of slice s00c4dbf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int   __cdecl FUN_00f47380(void* p);                     // operator delete
extern "C" void* __cdecl FUN_01021300();
extern "C" int   __cdecl FUN_01021240();
extern "C" void* __cdecl FUN_010212a0();
extern "C" int   __cdecl FUN_00b8de30(int a);
extern "C" void  __cdecl FUN_00ffbe50();
extern "C" float __cdecl FUN_00ffbfc0();
extern "C" void  __cdecl FUN_00ae6970(void* p);
extern "C" void  __cdecl FUN_00c344f0();
extern "C" void  __cdecl FUN_00c4dbe0(void* vec, void* val);        // eastl push_back
extern "C" void  __cdecl FUN_00c4db30(void* self, int a);
extern "C" void  __cdecl FUN_00c4e070(void* out, void* fmt, int val);   // WStr_Format
extern "C" int   __cdecl FUN_00c491c0(void* self, int tag, void* out);  // cSPMission::GetTagString
extern "C" int   __cdecl FUN_01021080();
extern "C" int   __cdecl FUN_00ce6950(int ctx);
extern "C" int   __cdecl FUN_00c4a6b0(void* self, int a, int b);
extern "C" void  __cdecl FUN_00c4b760(void* self);
extern "C" void  __cdecl FUN_00c46160(void* self);
extern "C" float __cdecl FUN_00c44d00(int a, int b);
extern "C" int   __cdecl FUN_00bb9ae0x(int p);
extern "C" int   __cdecl FUN_00801920(int p);
extern "C" int   __cdecl FUN_00b1fdb0(int p);
extern "C" int   __cdecl FUN_00b8dab0x(int p);
extern "C" char  __cdecl FUN_00fefe90x(int p);
extern "C" void  __cdecl FUN_00b3d430x(int p);
extern "C" char  __cdecl FUN_00bbe5c0x(int p);
extern "C" void  __cdecl FUN_00c47d80(void* self);
extern "C" int   __cdecl FUN_00c5c5e0x(int p);                        // cCivData::GetCities -> float[3]
extern "C" void  __cdecl FUN_00b3d2a0x(void* a, void* b, void* c);
extern "C" void  __cdecl FUN_00bb1080x(void* a, void* b, void* c);
extern "C" char  __cdecl FUN_00bb9af0x(int a);
extern "C" char  __cdecl FUN_00bb9c90x(void* p);
extern "C" void* __cdecl FUN_00bba790x(int p);
extern "C" void  __cdecl FUN_00bb4af0x(void* a, void* b);
extern "C" void  __cdecl FUN_00b3d2a0y(void* a, void* b);
extern "C" int   __cdecl FUN_00c478b0(void* self, int a, int b);
extern "C" void  __cdecl FUN_00c55500(void* self);
extern "C" void  __cdecl FUN_00c5ed90(void* self, int a);
extern "C" int   __cdecl FUN_00c70b20(int a, int b);
extern "C" int   __cdecl FUN_00c487d0(void* self, int key, void* out);
extern "C" void  __cdecl FUN_00c48d40(void* self, void* out);
extern "C" void  __cdecl FUN_0057cb60(void* a, void* b);
extern float gNegOneF;   // 0x013eb1bc  -1.0f
extern float gPosOneF;   // 0x01485720   1.0f
extern float gZeroF;     // 0x01485378   0.0f
extern float gHugeF;     // 0x0146dfa0   3.4028235e+38f
extern "C" u32   __cdecl FUN_00a68fb0(int n);                       // RandomUint32Uniform
extern "C" char  __cdecl FUN_00c4db00(void* self, u32 key);
extern "C" void  __cdecl FUN_00ba6310x(void* self, u32 a, int b);
namespace SP {
class ThisStubs
{
  public:
    void  A();               // 0x00c48e90 cGenericPressureEvent ctor
    void  B();               // 0x00c47680 cSPMission dtor
    bool  Init();            // 0x00c4ad50
    bool  IsActive();        // 0x00c44c80
    u32   ReadTargetType();  // 0x00c45b40
    void* GetPlanetRec(int); // 0x00c474b0
    float ReadMinRange();    // 0x00c45b80
    float ReadMaxRange();    // 0x00c45bd0
    int   ReadNumJumps();    // 0x00c45c20
    int   CalcDuration();    // 0x00c45a10
    void  BaseInitA();       // 0x00c44b80
    void  BaseInitB();       // 0x00c44bd0
    void  SetSerializer();   // 0x00c2e4e0
    void  GetText(int key, void* out);   // 0x00c487d0
    void  GetUITitle(void* out);         // 0x00c48d40
    void  TriggerUIUpdate();             // 0x00c47d80
    void* PickPlanet(void* a);           // 0x00c47e20
    void* GetTargetPlanet();             // 0x00970b30
    int   Update(int a);                 // 0x00c478b0
    void  SetText(void* a);              // 0x0057cb60 eastl wstring operator=
    void  vt14c(int a);                  // mission list register
    void  vt150(int a);                  // mission list register
    void  RemoveEvent();                 // 0x00dd6d10 cSPUIEventLog::RemoveEvent
    bool  RegisterCallback();            // 0x00dd6b20 cSPUIEventLog::RegisterCallback
    void  MoveNestInit(void* a, void* b);  // 0x00c4db90
    void  PostInit();                    // 0x00c4a0c0
};
}
namespace SP {
class cMission
{
  public:
    unsigned char pad000[0x44];
    u32    mField44;               // 0x44
    unsigned char pad048[0x78 - 0x48];
    u32    mField78;               // 0x78
    unsigned char pad07c[0x80 - 0x7c];
    int    mDuration80;            // 0x80
    unsigned char pad084[0x14c - 0x84];
    void*  mp14c;                  // 0x14c  eastl wstring (UI text)
    unsigned char pad150[0x180 - 0x150];
    void*  mp180;                  // 0x180  property list
    unsigned char pad184[0x1bc - 0x184];
    int    mField1bc;              // 0x1bc
    unsigned char pad1c0[0x1c4 - 0x1c0];
    int    mField1c4;              // 0x1c4
    int    mCounter1c8;            // 0x1c8
    unsigned char pad1cc[0x1f0 - 0x1cc];
    int    mField1f0;              // 0x1f0
    unsigned char pad1f4[0x1f8 - 0x1f4];
    int    mCount1f8;              // 0x1f8
    int    mCount1fc;              // 0x1fc
    unsigned char pad200[0x204 - 0x200];
    int    mNum204;                // 0x204
    int    mNum208;                // 0x208
    unsigned char pad20c[0x218 - 0x20c];
    int    mNum218;                // 0x218 (=-1 sentinel)
    int    mNum21c;                // 0x21c (=-1 sentinel)

    void* vtbl() { return *(void**)this; }
};
}
// ---- items of slice s00c4dbf0 end

// @ 0x00c4b220
void* cSPMissionAdventureBase::PickAdventureAsset()
{
    StarManager(&mpData1f4, 0)->PickRandomAsset();
    return mpData1f4;
}

// @ 0x00c4b250
bool cSPMissionAdventureBase::RerollAdventureAsset()
{
    void* pOld = mpData1f4;
    bool bResult = StarManager(&mpData1f4, 0)->PickRandomAsset();
    if (mpData1f4 != pOld) {
        cPlanet* pPlanet = GetTargetPlanet();
        void* pPlanetData = pPlanet->mpData13C;
        void* pAssetRef = FUN_01021300(mpData1f4);
        FUN_00baf790(StarManager(pPlanetData, pAssetRef));
        FUN_00b7d580(FUN_00b3d360(pPlanet));
    }
    return bResult;
}

// @ 0x00c4bda0
namespace SP {
void __fastcall FUN_00c4bda0(cSPMissionEradicate* this_, int unused, void* pOut)
{
    GetPropertyAsKey(this_->mpMissionKey, 0xff60c676, pOut);
}
}  // namespace SP

// @ 0x00c4bdc0
namespace SP {
void __fastcall FUN_00c4bdc0(cSPMissionBase_s00c4_bc00* this_, int unused, void* a, void* b, void* c)
{
    (void)this_; (void)a; (void)b; (void)c;
}
}  // namespace SP

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

// @ 0x00c4db00
char cMissionKeys::ContainsKey(int key)
{
    for (int i = 0; i < (int)(mpKeysEnd_204 - mpKeys_200); i++)
        if (mpKeys_200[i] == key)
            return true;
    return false;
}

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

// @ 0x00c4db90
void cSPMissionBiosphere::GetPropertyInstance(void* key, int* out)
{
    FUN_006a12a0(mpPropList_180, 0xf924ed01, key);
    cPropertyList_s00c4_cb90* prop = mpPropList_180;
    if (!prop)
        return;
    cProperty_s00c4_cb90* p;
    if (prop->GetProperty(0xf924ed02, &p))
        if (p->mType == 10)
            *out = *p->GetUInt();
}

// @ 0x00c4dbf0
void __fastcall FUN_00c4dbf0(void* ecx_this, void* edx)
{
    ((SP::ThisStubs*)ecx_this)->A();
    int zero = 0;
    *(int*)((char*)ecx_this + 0x1f0) = zero;
    *(int*)((char*)ecx_this + 0x1f4) = zero;
    *(int*)((char*)ecx_this + 0x1f8) = zero;
    *(int*)((char*)ecx_this + 0x1fc) = zero;
    *(void**)ecx_this = (void*)0x146dd58;
    *(void**)((char*)ecx_this + 4) = (void*)0x146dd44;
    *(void**)((char*)ecx_this + 0x34) = (void*)0x146dd34;
    *(int*)((char*)ecx_this + 0x200) = zero;
    *(int*)((char*)ecx_this + 0x204) = zero;
    *(int*)((char*)ecx_this + 0x208) = zero;
}

// @ 0x00c4dca0
void* __fastcall FUN_00c4dca0(void* ecx_this, void* edx, u8 flags)
{
    void* p = *(void**)((char*)ecx_this + 0x200);
    if (p && *(int*)((char*)p - 4) != 0)
        FUN_00f47380(p);
    ((SP::ThisStubs*)ecx_this)->B();
    if (flags & 1)
        FUN_00f47380(ecx_this);
    return ecx_this;
}

// @ 0x00c4dce0
char __fastcall FUN_00c4dce0(void* ecx_this, void* edx)
{
    if (!((SP::ThisStubs*)ecx_this)->Init())
        return 0;
    ((SP::ThisStubs*)ecx_this)->MoveNestInit((char*)ecx_this + 0x1f4, (char*)ecx_this + 0x1f8);
    ((SP::ThisStubs*)ecx_this)->PostInit();
    return 1;
}

// @ 0x00c4dd10
void __fastcall FUN_00c4dd10(void* ecx_this, void* edx, u32 msg, void* arg)
{
    SP::cMission* self = (SP::cMission*)ecx_this;
    if (msg < 0x4446534u) {
        if (msg != 0x4446533u && msg != 0x4445d43u) {
            FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
            return;
        }
    } else if (msg != 0xf46092c1u && msg != 0xf46092d4u && msg != 0xf46092d5u &&
               msg != 0xf46092d8u && msg != 0xf46092dau && msg != 0xf46092dbu) {
        FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
        return;
    }
    if (msg == 0xf46092d4u) {
        u32 key = *(u32*)((char*)arg + 8);
        if (FUN_00c4db00(ecx_this, key))
            return;  // fallthrough to HandleMessage
        FUN_00c4dbe0((char*)ecx_this + 0x1cc, &key);   // push_back
        goto LAB_INC;
    }
    if (msg == 0xf46092dau) {
        int v = *(int*)((char*)arg + 8);
        if (v < 1) {
            FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
            return;
        }
        self->mCounter1c8 += v;
        goto LAB_COMPARE;
    }
    if (msg == 0xf46092dbu) {
        if (FUN_01021080() != 0)
            goto LAB_CASE_DEFAULT;
        if (FUN_010212a0() == 0)
            goto LAB_CASE_DEFAULT;
        int ctx = (int)FUN_010212a0();
        u32 found = FUN_00ce6950(ctx);
        (void)found;
        if (FUN_00c4db00(ecx_this, found))
            goto LAB_CASE_DEFAULT;
        FUN_00c4dbe0((char*)ecx_this + 0x1cc, &found);
        goto LAB_INC;
    }
    if (msg == 0xf46092c1u) {
        int a0 = *(int*)((char*)arg + 0x20);
        int a1 = *(int*)((char*)arg + 0x28);
        if (*(int*)((char*)arg + 8) == 0) {
            int ctx = (int)FUN_01021300();
            int found = FUN_00ce6950(ctx);
            if (a1 != found)
                goto LAB_ADD_A0;
            goto LAB_INC;
        }
        int v = *(int*)((char*)arg + 0x10);
        if (v == (int)0xb978c47a || v == 0x7ecbe6f5)
            self->mCounter1c8 -= a0;
        goto LAB_CASE_DEFAULT;
    }
LAB_INC:
    FUN_00c4db30(ecx_this, 1);
    self->mCounter1c8 += 1;
LAB_COMPARE:
    if ((u32)self->mField1c4 > (u32)self->mCounter1c8) {
        FUN_00c47d80(ecx_this);          // TriggerUIUpdate
        FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
        return;
    }
    FUN_00c4b760(ecx_this);
    FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
    return;
LAB_ADD_A0:
    {
        int a0 = *(int*)((char*)arg + 0x20);
        self->mCounter1c8 += a0;
    }
    goto LAB_COMPARE;
LAB_CASE_DEFAULT:
    FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
}

// @ 0x00c4deb0
int __fastcall FUN_00c4deb0(void* ecx_this, void* edx, int tag, void* out)
{
    if ((u32)tag == 0x649ad9deu) {
        int diff = *(int*)((char*)ecx_this + 0x1f8) - *(int*)((char*)ecx_this + 0x1fc);
        FUN_00c4e070(out, (void*)0x13f01bc, diff);   // WStr_Format
        return 1;
    }
    return FUN_00c491c0(ecx_this, tag, out);         // cSPMission::GetTagString
}

// @ 0x00c4def0
void* __fastcall FUN_00c4def0(void* ecx_this, void* edx)
{
    ((SP::ThisStubs*)ecx_this)->A();
    int zero = 0;
    *(int*)((char*)ecx_this + 0x1f0) = zero;
    *(char*)((char*)ecx_this + 0x1f4) = 0;
    *(char*)((char*)ecx_this + 0x1f5) = 0;
    *(void**)ecx_this = (void*)0x146dfc8;
    *(void**)((char*)ecx_this + 4) = (void*)0x146dfb4;
    *(void**)((char*)ecx_this + 0x34) = (void*)0x146dfa4;
    return ecx_this;
}

// @ 0x00c4e0f0
void __fastcall FUN_00c4e0f0(void* ecx_this, void* edx, u32 msg, void* arg)
{
    SP::cMission* self = (SP::cMission*)ecx_this;
    bool runTail = false;
    if (msg < 0x248976bu) {
        if (msg == 0x248976au) {
            runTail = true;
        } else if (msg == 0x248975fu) {
            if (self->mField44 != 0x398aca5eu) { FUN_00c4a6b0(ecx_this, (int)msg, (int)arg); return; }
            if (self->mField1bc == 0)
                FUN_00c46160(ecx_this);
            runTail = true;
        } else if (msg == 0x2489766u) {
            runTail = true;
        } else {
            FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
            return;
        }
    } else if (msg == 0x490d429u) {
        runTail = true;
    } else {
        FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
        return;
    }
    if (runTail) {
        if (self->mField44 == 0x398aca5eu && self->mField1bc == 0)
            FUN_00c47d80(ecx_this);              // TriggerUIUpdate
    }
    FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
}

// @ 0x00c4e280
float __fastcall FUN_00c4e280(void* ecx_this, void* edx, int a2, int a3)
{
    float r = FUN_00c44d00(a2, a3);
    if (0.0f >= r)
        return r;
    int p = FUN_00b8de30(a2);
    if (FUN_00bb9ae0x(p) != 1 && FUN_00801920(p) != 0)
        return gNegOneF;
    if (FUN_00b1fdb0(p) != -1)
        return gNegOneF;
    if (FUN_00b8dab0x(a2) != 1)
        return gNegOneF;
    if (((*(u32*)((char*)ecx_this + 0x130) >> 3) & 1) != 0) {
        if (!FUN_00fefe90x(a2))
            return gNegOneF;
    }
    FUN_00b3d430x(a2);
    char c = FUN_00bbe5c0x(a2);
    if (*(char*)((char*)ecx_this + 0x1f4) != 0)
        return c ? gPosOneF : gNegOneF;
    return c ? gNegOneF : gPosOneF;
}

// @ 0x00c4e570
void* __fastcall FUN_00c4e570(void* ecx_this, void* edx, u32* a)
{
    SP::ThisStubs* self = (SP::ThisStubs*)ecx_this;
    u32* p = a;
    void* chosen = 0;
    if (*(u32*)((char*)ecx_this + 0x78) != 0x398aca5eu)
        goto LAB_PICK;

    float minR = self->ReadMinRange();
    float maxR = self->ReadMaxRange();
    int numJumps = self->ReadNumJumps();
    u32 r1 = p[1];

    // query block (0x1ff1 / r1 / 4 / -1,-1,-1 / jumps)
    int   q0 = 0x1ff1;
    u32   q1 = r1;
    int   q2 = 4;
    float qmin = gNegOneF, qmax = gNegOneF, qtravel = gNegOneF;
    int   qjumps = 0;
    (void)qjumps;
    if (0.0f <= minR)
        qmin = minR;
    if (maxR > gZeroF)
        qmax = maxR;
    FUN_00ffbe50();
    qtravel = (float)FUN_00ffbfc0();
    qjumps = numJumps;

    float hostPos[3];      // esp+0x30/34/38
    void* civ = (void*)self->GetPlanetRec(0);      // esp+0x54
    (void)civ;
    float* cp = (float*)FUN_00c5c5e0x((int)p);     // GetCities -> float[3]
    hostPos[0] = cp[0];
    hostPos[1] = cp[1];
    hostPos[2] = cp[2];

    // build the star-record vector
    struct Vec { void* b; void* e; void* c; };
    Vec planetVec;
    planetVec.b = 0; planetVec.e = 0; planetVec.c = 0;
    FUN_00b3d2a0x(hostPos, &q0, &planetVec);
    FUN_00bb1080x(hostPos, &q0, &planetVec);

    void** pv = (void**)planetVec.b;
    void** endv = (void**)planetVec.e;
    int n = (int)((char*)endv - (char*)pv) / 4;
    float bestTravel = gHugeF;
    float bestDist = gNegOneF;
    void* bestStar = 0;
    for (int i = 0; i < n; ++i) {
        void* star = pv[i];
        if (FUN_00bb9af0x(1))
            continue;
        int bit = FUN_00bb9ae0x((int)star) & 0x1f;
        if ((p[1] & (1u << bit)) == 0)
            continue;
        if (bestStar == star)
            continue;
        float* sp = (float*)FUN_00c5c5e0x((int)star);
        float dx = hostPos[0] - sp[0];
        float dy = hostPos[1] - sp[1];
        float dz = hostPos[2] - sp[2];
        float dist = dz * dz + dy * dy + dx * dx;
        if (!FUN_00bb9c90x(star)) {
            FUN_00b3d2a0y(star, p);
            FUN_00bb4af0x(star, p);
        }
        void** pl = (void**)FUN_00bba790x((int)star);
        int m = (int)((char*)pl[1] - (char*)pl[0]) / 4;
        for (int j = 0; j < m; ++j) {
            int planet = *(int*)((char*)pl[0] + j * 4);
            int pb = (*(int*)(planet + 0x28)) & 0x1f;
            if ((*p & (1u << pb)) == 0)
                continue;
            int pb2 = FUN_00b8dab0x(planet) & 0x1f;
            if ((p[2] & (1u << pb2)) == 0)
                continue;
            int t1 = 0, t2 = 0;
            float travel = (*(float(__thiscall**)(void*, int, void*))(*(char**)ecx_this + 0x184))(ecx_this, planet, &t1);
            (void)t2;
            if (travel <= 0.0f)
                continue;
            bool better;
            if (travel == bestDist)
                better = (dist < bestTravel);
            else
                better = (bestDist < travel);
            if (better) {
                bestTravel = dist;
                bestDist = travel;
                bestStar = star;
            }
        }
    }

    // tear down the vector
    for (void** it = pv; it < endv; ++it) {
        if (*it)
            (*(void(__thiscall**)(void*))(*(char**)*it + 4))(*it);
    }
    if (planetVec.b && *((int*)planetVec.b - 1) != 0)
        FUN_00f47380(planetVec.b);

    chosen = bestStar;
    if (chosen)
        goto LAB_TAIL;
LAB_PICK:
    chosen = self->PickPlanet(a);
LAB_TAIL:
    if (*(u32*)((char*)ecx_this + 0x78) == 0x398aca5eu && chosen) {
        u32 keys[13];
        keys[0] = 0xb4fe6c1d; keys[1] = 0xef9a0e5d; keys[2] = 0x6c836e17; keys[3] = 0x6fbf28c4;
        keys[4] = 0x09f1a11b; keys[5] = 0x7fb9baf3; keys[6] = 0xcb3c5ecb; keys[7] = 0x524a8dc4;
        keys[8] = 0xd84910a0; keys[9] = 0xdf5be6d5; keys[10] = 0x4c7c77a7; keys[11] = 0x618e762a;
        keys[12] = 0x1b917be2;
        u32 idx = FUN_00a68fb0(13);
        u32 key = keys[idx];
        FUN_00b3d2a0y(chosen, (void*)key);
        FUN_00ba6310x(chosen, key, 0xa6);
    }
    return chosen;
}

// @ 0x00c4e9a0
int __fastcall FUN_00c4e9a0(void* ecx_this, void* edx, int a)
{
    int r = (int)((int(__fastcall*)(void*, void*, int))FUN_00c478b0)(ecx_this, 0, a);
    if (r != 3)
        return r;
    void* owner = *(void**)((char*)ecx_this + 0x1f0);   // placeholder per decompile: param_1[1].mpOwnerEmpire
    (void)owner;
    if (owner == 0) {
        bool ok;
        if (*(u32*)((char*)ecx_this + 0x78) == 0x398aca5eu) {
            void* v[3];
            v[0] = 0; v[1] = 0; v[2] = 0;
            FUN_01021300();
            FUN_00c344f0();
            int cnt = (int)((char*)v[1] - (char*)v[0]) / 4;
            ok = cnt > 1;
            FUN_00ae6970(&v[0]);
        } else {
            FUN_01021300();
            ((SP::ThisStubs*)ecx_this)->GetTargetPlanet();
            ok = FUN_00c70b20(0, 0) != 0;
        }
        if (!ok)
            return 3;
        if (*(u8*)((char*)ecx_this + 0x1f5) != 0) {
            FUN_00c5ed90(ecx_this, 1);
            return 3;
        }
    } else if (owner != (void*)1) {
        return 3;
    } else {
        FUN_01021300();
        ((SP::ThisStubs*)ecx_this)->GetTargetPlanet();
        if (!FUN_00c70b20(0, 0))
            return 3;
    }
    FUN_00c55500(ecx_this);
    return 3;
}

// @ 0x00c4ea70
void __fastcall FUN_00c4ea70(void* ecx_this, void* edx, void* out)
{
    void* textPtr = (char*)ecx_this + 0x14c;
    if (*(void**)((char*)ecx_this + 0x14c) != *(void**)((char*)ecx_this + 0x150) ||
        *(int*)((char*)ecx_this + 0x1f0) != 0 ||
        *(u32*)((char*)ecx_this + 0x78) != 0x398aca5eu)
        goto LAB_DEFAULT;

    if (FUN_01021080() == 1) {
        void* rec = FUN_010212a0();
        if (rec) {
            void* tp = ((SP::ThisStubs*)ecx_this)->GetTargetPlanet();
            int tpv = tp ? *(int*)((char*)tp + 0x13c) : 0;
            if ((int)rec == tpv) {
                FUN_00c487d0(ecx_this, (int)0x791cfa76, out);
                FUN_0057cb60(textPtr, out);
                return;
            }
        }
        int isArchived = FUN_01021240();
        void* tp2 = ((SP::ThisStubs*)ecx_this)->GetTargetPlanet();
        int tpv2 = tp2 ? FUN_00b8de30(*(int*)((char*)tp2 + 0x13c)) : 0;
        if (isArchived != 0 && isArchived == tpv2) {
            FUN_00c487d0(ecx_this, (int)0x639f0b00, out);
            FUN_0057cb60(textPtr, out);
            return;
        }
    } else if (FUN_01021080() == 0) {
        void* rec = FUN_010212a0();
        if (rec) {
            void* tp = ((SP::ThisStubs*)ecx_this)->GetTargetPlanet();
            int tpv = tp ? *(int*)((char*)tp + 0x13c) : 0;
            if ((int)rec == tpv) {
                FUN_00c487d0(ecx_this, (int)0x6f9c8bf3, out);
                FUN_0057cb60(textPtr, out);
                return;
            }
        }
    }
LAB_DEFAULT:
    FUN_00c48d40(ecx_this, out);
}
