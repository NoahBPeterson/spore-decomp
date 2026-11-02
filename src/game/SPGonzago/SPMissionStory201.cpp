// src/game/SPGonzago/SPMissionStory201.cpp -- migrated from slice(s) s00c602b0, s00c5f530, s00c5e260 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionStory201.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanet.h"
#include "SP/cSPMission.h"
#include "SP/cSolarSystem.h"
#include "SP/cStar.h"
#include "SP/cStarManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cITerrainSphere.h"
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cTerrainSphere.h"
#include <math.h>

// ---- items of slice s00c5e260 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vtbl { void* p[64]; };
typedef int   (__thiscall* FnI0)(void*);
typedef void* (__thiscall* FnP1)(void*, int);
typedef void  (__thiscall* FnV1)(void*, int);
typedef void  (__thiscall* FnV2)(void*, void*, int);
typedef void  (__thiscall* FnV3)(void*, void*, int, int);
typedef void  (__thiscall* FnVoid)(void*);
struct Planet {
  uint8_t mPad000[0x13c];
  int     mField13c;      // +0x13c
};
struct Item {
  int mField0;            // +0x00
  int mField4;            // +0x04
  int mField8;            // +0x08
};
struct Inventory {
  void FUN_00ff45e0(Item* item);  // 0x00ff45e0
};
struct cSPSimulatorSpaceGame {
  Inventory* GetPlayerInventory(); // 0x00a1ad60
};
struct cGameNounManager_s00c5_e260 {
  void* GetPlayerTribe();          // 0x00bfc5f0
};
struct TribeObj {
  void FUN_00fe5430();             // 0x00fe5430
};
struct SomeVec {
  void*    mpField0;      // +0x00
  int      mPad04;        // +0x04
  int      mField8;       // +0x08
  int      mPad0C;        // +0x0c
  uint16_t mField10;      // +0x10
  uint16_t mField12;      // +0x12
};
struct Mission {
  Vtbl*   mpVtable;       // +0x000
  void*   mpField04;      // +0x004
  uint8_t mPad008[0x2c];  // +0x008 .. +0x033
  void*   mpField34;      // +0x034
  uint8_t mPad038[0x40];  // +0x038 .. +0x077
  int     mField078;      // +0x078
  uint8_t mPad07C[0xb4];  // +0x07c .. +0x12f
  uint32_t mField130;     // +0x130
  uint8_t mPad134[0x3c];  // +0x134 .. +0x16f
  uint8_t mField170[0x10];// +0x170 .. +0x17f
  void*   mpField180;     // +0x180
  uint8_t mPad184[0x6c];  // +0x184 .. +0x1ef
  int     mField1f0;      // +0x1f0
  void*   mpField1f4;     // +0x1f4
  int     mField1f8;      // +0x1f8
  int     mField1fc;      // +0x1fc

  // base helpers (addresses from the shipped binary)
  void  TriggerUIUpdate();        // 0x00c47d80
  void* GetTargetPlanet();        // 0x00970b30
  void  FUN_00c44b80();           // 0x00c44b80
  void  FUN_00c44bd0();           // 0x00c44bd0
  void  FUN_00c49f90();           // 0x00c49f90
  void  FUN_00c472e0();           // 0x00c472e0
  void  FUN_00c471c0();           // 0x00c471c0
  int   FUN_00c44cb0();           // 0x00c44cb0
  bool  IsActive();               // 0x00c44c80
  void  GetText(int id, int arg); // 0x00c487d0
  void  SetSerializer();          // 0x00c2e4e0
  bool  Init();                   // 0x00c4ad50
  int   ReadTargetPlanetType();   // 0x00c45b40
  void* GetPlanetRecordFromTargetType(int t); // 0x00c474b0
  void  FUN_00c47180(void* p);    // 0x00c47180
  int   ReadTargetAnimalSpeciesType(void* p); // 0x00c45b60
  void* GetAnimalSpeciesFromType(int t);      // 0x00c47610
  void* GetTargetPlanet(void* p, int a, int b); // 0x00970b30 (3-arg)
  void* PickPlanet(void* filter); // 0x00c47e20
  int   FUN_00c45b40();           // 0x00c45b40 (alias: ReadTargetPlanetType)
  void  FUN_00c4a0c0();           // 0x00c4a0c0
  char  FUN_00c5ea60();           // 0x00c5ea60 (see body)

  void  FUN_00c5ed90(int v);      // 0x00c5ed90
  void  FUN_00c5edb0();           // 0x00c5edb0
  void  FUN_00c5ee40();           // 0x00c5ee40
  void  FUN_00c5eed0(int arg);    // 0x00c5eed0
  void  FUN_00c5efb0(int arg);    // 0x00c5efb0
  int   FUN_00c5f090();           // 0x00c5f090
  int   FUN_00c5f0f0(int a, int b);// 0x00c5f0f0
  int   FUN_00c5f150();           // 0x00c5f150
  void  FUN_00c5f250();           // 0x00c5f250
  void  FUN_00c5f280();           // 0x00c5f280
  void  FUN_00c5f2c0();           // 0x00c5f2c0
  void  FUN_00c5f360();           // 0x00c5f360
  int   FUN_00c5f3d0();           // 0x00c5f3d0
  int   FUN_00c5f4e0(int id);     // 0x00c5f4e0
};
struct MissionStory201 : Mission {
  MissionStory201();              // 0x00c5f1b0
};
namespace SP {
  void* __stdcall SpaceGameGet(int a, int b); // 0x01002bd0
}
namespace SP {
  void* __stdcall SpaceGameGet();             // 0x01002bd0 (no-arg overload)
}
void* MessageServer();              // 0x0067dcc0
void  FUN_00c47a10();               // 0x00c47a10
void* FUN_01021370();               // 0x01021370
int   FUN_01021240();               // 0x01021240
int   FUN_01021080();               // 0x01021080
struct HomePlanetObj {
  int FUN_00b8de30();               // 0x00b8de30
};
void __fastcall MissionBaseCtor(void* self);
// ---- items of slice s00c5e260 end

// ---- items of slice s00c5f530 begin (TODO(rewrite): local stubs, replace by canonical classes)
class wstring {
public:
    unsigned short* mpBegin;      // +0x00
    unsigned short* mpEnd;        // +0x04
    unsigned short* mpCapacity;   // +0x08
    void assign(const unsigned short* first, const unsigned short* last);  // 0x00423650
};
struct cPlanet {
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
virtual void v06c();
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
    virtual void v0c0();   // +0xc0

    char    pad_04[0x13c - 0x04];
    void*   m13c;          // +0x13c

    wstring* GetName();        // 0x00c707e0
    int      FUN_00c70fb0();   // 0x00c70fb0
};
struct cSolarSystem {
    char      pad_00[0x10];
    cPlanet** m10;   // +0x10  begin
    cPlanet** m14;   // +0x14  end
};
struct cStar {
    cSolarSystem* GetSolarSystem();   // 0x00c8b770
};
struct cBioElemSort {
    cBioElemSort* SortBanners();      // 0x00b8de30
    void FUN_00bb9b00(int a, int b);  // 0x00bb9b00
    void FUN_00bb9c30();              // 0x00bb9c30
};
struct cStarManager {
    void GetOrActivatePlanet(void* id, cPlanet** out);   // 0x00bb59b0
};
struct cMissionMgr {
    void FUN_00feba80();   // 0x00feba80
};
struct cSub { int _; };
struct cNoun {
    char  pad_00[0x70];
    cSub  m070;                    // +0x70
    char  pad_74[0x228 - 0x74];
    int   m228;                    // +0x228
};
struct tVecData {
    int       m00;        // +0x00
    cNoun**   mItems[2];  // +0x04 begin, +0x08 end
};
struct cGameNounManager {
    tVecData* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);  // 0x00b21340
};
void  FUN_00c46b80();      // 0x00c46b80
void* FUN_01021260();      // 0x01021260  (cSPLivingUniverse::GetActivePlanet)
void* FUN_01021230();      // 0x01021230
void* StarManager();       // 0x00b3d2a0
void* NounManager();       // 0x00b3d300
void* GetCurrentGameMode();// 0x00b5b800
void* GetUniverseContext();// 0x01021080
cMissionMgr* __stdcall GetMissionManager(int id);   // 0x00feb9f0
void  TryGetUIntProperty(void* obj, unsigned id, unsigned* out);  // 0x00410370
struct cSPMission {
    char pad_00[0x180];

    void     FUN_00c46b80();                            // 0x00c46b80
    bool     Init();                                    // 0x00c4ad50
    cPlanet* GetTargetPlanet();                         // 0x00970b30
    bool     GetTagString(unsigned tag, wstring* out);  // 0x00c491c0
    void     FUN_00c4a0c0();                            // 0x00c4a0c0
};
struct cSPMissionStory201 : cSPMission {
    void*    m180;   // +0x180
    char     pad_184[0x1f4 - 0x184];
    cPlanet* m1f4;   // +0x1f4
    unsigned m1f8;   // +0x1f8
    unsigned m1fc;   // +0x1fc

    bool PickUFOWreckPlanet();                          // 0x00c5f530
    void FUN_00c5f5f0();                                // 0x00c5f5f0
    bool GetTagString(unsigned tag, wstring* out);      // 0x00c5f640
    void GetUIShortDescription();                       // 0x00c5f690
    bool FUN_00c5f770();                                // 0x00c5f770
    bool FUN_00c5fcf0();                                // 0x00c5fcf0
    void FUN_00c5fe00();                                // 0x00c5fe00
    void FUN_00c5ff50();                                // 0x00c5ff50
    void OnArtifactScanned();                           // 0x00c60120
};
static bool TagNameHelper(cPlanet* planet, wstring* out)
{
    wstring* name = planet->GetName();
    if (name != out)
        out->assign(name->mpBegin, name->mpEnd);
    return true;
}
// ---- items of slice s00c5f530 end

// ---- items of slice s00c602b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char kScannedRuinTrigger[];                // 0x01470088 "SPG_Story201ScannedRuin"
extern const float kEps;                                // 0x013ec4b8 (1e-8f)
extern const float kOffsetScale;                        // 0x013eecd8 (20.0f)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16
class cSPMission_s00c6_02b0;
struct cPlanet_s00c6_02b0;
struct cGameNoun;
struct wstring_s00c6_02b0 {
    wchar_t* mpBegin;               // +0x00
    wchar_t* mpEnd;                 // +0x04
    bool IsEmpty() const { return mpBegin == mpEnd; }
    wstring_s00c6_02b0& operator=(const wstring_s00c6_02b0& rhs);     // 0x0057cb60
};
struct ResourceKey {
    uint32_t mGroup;                // +0x00
    uint32_t mType;                 // +0x04
    uint32_t mInstance;             // +0x08
};
inline bool operator!=(const ResourceKey& a, const ResourceKey& b)
{
    return a.mGroup != b.mGroup || a.mType != b.mType || a.mInstance != b.mInstance;
}
struct cMissionVtbl {
    PV32 PV8 PV                                             // +0x000 .. +0x0a0
    virtual void* FindMissionRecord(uint32_t id, void* pMission, int flags);   // +0x0a4
    PV32                                                    // +0x0a8 .. +0x124
    virtual char IsReady();                                 // +0x128
    PV8                                                     // +0x12c .. +0x148
    virtual void AddMessageHandler(uint32_t id);            // +0x14c
    virtual void RemoveMessageHandler(uint32_t id);         // +0x150
    PV4 PV2 PV                                              // +0x154 .. +0x16c
    virtual void RefreshProgress();                         // +0x170
};
struct cPlanetModelInner {
    PV32 PV8 PV4                                            // +0x000 .. +0x0ac
    virtual int GetPlanetList(void** ppList);               // +0x0b0
};
struct cPlanetModel {
    uint8_t pad00[0x24];
    cPlanetModelInner* mp24;                                // +0x24
};
struct cPlanetType {
    uint32_t pad00[2];
    uint32_t mHash;                 // +0x08
};
struct cPlanet_s00c6_02b0 {
    void* mpVftable;                // +0x00
    uint32_t mFlags;                // +0x04
    uint32_t pad08[2];              // +0x08
    uint32_t mKey[3];               // +0x0c (EA::ResourceMan::Key)
    float mBounds[3];               // +0x1c
    uint8_t pad28[0x90 - 0x28];
    cPlanetType* mpType;            // +0x90
    uint8_t pad94[0x13c - 0x94];
    void* mpStarRecord;             // +0x13c
};
struct cNounPropertyList {
    PV8 PV4 PV2                                             // +0x000 .. +0x034
    virtual void SetKey(const void* pKey);                  // +0x38
    virtual void SetValue(const float* pValue);             // +0x3c
};
struct cNounFlagBlock {
    uint8_t pad00[0x80];
    uint8_t mb80;                   // +0x80
    void Set(bool value);           // 0x00bfc470
};
struct cGameNoun {
    uint8_t pad00[0x70];
    cNounPropertyList mPropList;    // +0x70
    uint8_t padA4[0x148 - 0xa4];
    cNounFlagBlock mFlagBlock;      // +0x148
    void FUN_00c6f770(uint32_t type, int32_t arg2, int32_t arg3);  // 0x00c6f770
};
struct cTerrainSphere {
    bool FUN_00c772c0(uint32_t id);     // 0x00c772c0
    void FUN_00c77bf0(uint32_t id);     // 0x00c77bf0
};
struct cGameNounManager_s00c6_02b0 {
    cGameNoun* CreateNoun(uint32_t type);   // 0x00b20c60
    cTerrainSphere* GetCurrentTerrainSphere();   // 0x00f67d90
};
struct cToolID {
    uint32_t mGroup;                // +0x00
    uint32_t mType;                 // +0x04
    uint32_t mInstance;             // +0x08
};
struct cTool {
    uint32_t pad00[0x7c / 4];
    int GetStackCount();            // 0x00a02d30
    uint32_t FUN_00b8f860();        // 0x00b8f860 (the tool's key/id)
    bool FUN_00ac0c30();            // 0x00ac0c30
    bool FUN_00ac0c50();            // 0x00ac0c50
};
struct cPlayerInventory {
    PV16 PV4 PV2 PV                         // +0x000 .. +0x058
    virtual int GetToolCount();             // +0x5c
    virtual void* GetToolEntry(int index);  // +0x60
    PV4                                     // +0x64 .. +0x070
    virtual bool HasToolID(const cToolID* pID);     // +0x74
    cTool* GetToolFromToolID(const cToolID* pID);   // 0x00ff3d40
    void SetNormal(const float* pNormal);           // 0x00c3be70
    void SetDistance(float distance);               // 0x00c3daa0
};
struct cSPSimulatorSpaceGame_s00c6_02b0 {
    uint8_t pad00[0x40];
    cPlayerInventory* mpPlayerInventory;    // +0x40
    uint8_t pad44[0x54 - 0x44];
    void* mpAvatar;                         // +0x54
    cPlayerInventory* GetPlayerInventory(); // 0x00a1ad60
    void* GetAvatar();                      // 0x00b1fdb0
};
struct cActionTarget {
    uint8_t mOpaque[0x20];          // +0x00
    cActionTarget();                // 0x00ad7940
    ~cActionTarget();               // 0x00ad7ad0
    float* GetLocation();           // 0x00ad7b50
};
struct cTriggerManager {
    int FindTrigger(const char* pName);                     // 0x00ad7db0
    uint32_t AddTrigger(uint32_t id, cActionTarget* pTarget);  // 0x00adb2a0
};
struct cAudioSystem {
    PV8
    virtual void* GetVoiceHandle();     // +0x20
};
struct cCommManager {
    void FUN_00aeb720(int param, void* pContext, void* pHandle, uint32_t id, void* pMission, int flags);  // 0x00aeb720
};
struct cStarRecordRef {
    uint8_t pad000[0x184];
    void* mpCommContext;            // +0x184
    void* GetCommContext();         // 0x00ce6950
};
struct cMissionManager {
    void FUN_00febf20(cSPMission_s00c6_02b0* pMission);    // 0x00febf20
};
struct cMessage {
    uint32_t pad00[2];
    uint32_t mParam8;               // +0x08
    uint32_t pad0C;
    cPlanet_s00c6_02b0* mpPlanet;              // +0x10
};
struct cPlanetPickParams {
    uint32_t mPlanetType;           // +0x00
    uint32_t mPickMode;             // +0x04
    uint32_t mPad08;                // +0x08
    uint32_t mPad0C;                // +0x0c
    uint32_t mPad10;                // +0x10
    uint32_t mPad14;                // +0x14
    uint32_t mPad18;                // +0x18
    uint32_t mPad1C;                // +0x1c
    uint32_t mPad20;                // +0x20
    uint32_t mPad24;                // +0x24
    uint32_t mPad28;                // +0x28
    uint32_t mPad2C;                // +0x2c
    uint32_t mPad30;                // +0x30
    uint32_t mPad34;                // +0x34
    uint32_t mPad38;                // +0x38
    uint32_t mPad3C;                // +0x3c
    uint32_t mPad40;                // +0x40
    uint32_t mPad44;                // +0x44
    cPlanetPickParams();            // 0x00ba7bd0
    ~cPlanetPickParams();           // 0x00ba8220
};
class cSPMission_s00c6_02b0 {
public:
    // The message handler subobject sits 0x34 bytes into a mission object.
    static const uint32_t kHandlerOffset = 0x34;

    uint8_t pad000[0x78];
    uint32_t mMissionTypeKey;       // +0x78 (0xd85005e9 for the terraform missions)
    uint8_t pad07c[0x14c - 0x7c];
    wstring_s00c6_02b0 mUITitle;               // +0x14c
    uint8_t pad154[0x180 - 0x154];  // +0x154 .. +0x180 (the base ends where the subclasses' members begin)

    bool Init();                                        // 0x00c4ad50
    bool IsActive();                                    // 0x00c44c80
    uint32_t ReadTargetPlanetType();                    // 0x00c45b40
    void* GetPlanetRecordFromTargetType(uint32_t type); // 0x00c474b0
    void FUN_00c47180(void* pRecord);                   // 0x00c47180
    cPlanet_s00c6_02b0* GetTargetPlanet();                         // 0x00970b30
    cPlanet_s00c6_02b0* PickPlanet(const cPlanetPickParams* pParams);   // 0x00c47e20
    void FUN_00c4a0c0();                                // 0x00c4a0c0
    void TriggerUIUpdate();                             // 0x00c47d80
    void GetText(uint32_t id, wstring_s00c6_02b0* pOut);           // 0x00c487d0
    void GetUITitle(wstring_s00c6_02b0* pOut);                     // 0x00c48d40
    bool GetTagString(uint32_t tag, wstring_s00c6_02b0* pOut);     // 0x00c491c0
    float FUN_00c44d00(cPlanet_s00c6_02b0* pPlanet, void* arg);    // 0x00c44d00
    void FUN_00c44b80();                                // 0x00c44b80
    void FUN_00c44bd0();                                // 0x00c44bd0
    cMissionVtbl* Vtbl() { return (cMissionVtbl*)this; }
};
class cSPMissionStory201Mission : public cSPMission_s00c6_02b0 {
public:
    uint8_t pad180[0x1f0 - 0x180];
    uint32_t mStoryState;           // +0x1f0
    cPlanet_s00c6_02b0* mpScannedPlanet;       // +0x1f4
    void OnArtifactScanned(void* pArtifact);   // 0x00c60120
};
class cMissionMessageHandler {
public:
    virtual bool HandleMessage(uint32_t msg, void* arg);    // 0x00c4a6b0
};
class cSPMissionStory201_s00c6_02b0 : public cMissionMessageHandler {
public:
    uint8_t pad004[0x1bc - 0x04];
    uint32_t mStoryState;           // +0x1bc (mission +0x1f0)
    cPlanet_s00c6_02b0* mpScannedPlanet;       // +0x1c0 (mission +0x1f4)
    virtual bool HandleMessage(uint32_t msg, void* arg);    // 0x00c602b0
    // The mission object this handler subobject belongs to.
    cSPMissionStory201Mission* Mission()
    {
        return (cSPMissionStory201Mission*)((char*)this - cSPMission_s00c6_02b0::kHandlerOffset);
    }
};
struct cGenericPressureEvent {
    void* mpVftable;                // +0x00
    void* mpVftable04;              // +0x04
    uint8_t pad08[0x34 - 0x08];
    void* mpVftable34;              // +0x34
    uint8_t pad38[0x1f0 - 0x38];
    uint32_t mEventStage;           // +0x1f0
    bool mFlag1F4;                  // +0x1f4
    bool mFlag1F5;                  // +0x1f5
    void BaseCtor();                // 0x00c48e90
};
namespace Simulator {
class cMissionTerraform : public cGenericPressureEvent {
public:
    cMissionTerraform();            // 0x00c606e0
};  // namespace Simulator
}
void* __cdecl SpaceGameGet();                           // 0x01002bd0
void* __cdecl PlanetModel();                            // 0x00b3d350
cGameNounManager_s00c6_02b0* __cdecl NounManager_s00c6_02b0();                // 0x00b3d300
cTriggerManager* __cdecl GetTriggerMgr();               // 0x00b3d4d0
void* __cdecl CommManager();                            // 0x00b3d4a0
cAudioSystem* __cdecl EA_GetSystemAT();                 // 0x00a206f0
cMissionManager* __cdecl GetMissionManager();           // 0x00feb9f0
void* __cdecl GetUFOSimulator();                        // 0x00ffbe50
float* __cdecl FUN_0046d660(float** ppOut, const float* pValue);  // 0x0046d660
void __cdecl SP_KillSetiEffects(uint32_t id, void* pHandle);    // 0x00435ed0
enum {
    kMsgTerraformStep        = 0x248975f,
    kMsgTerraformSubStepA    = 0x2489766,
    kMsgTerraformSubStepB    = 0x248976a,
    kMsgStoryRuinScanned     = 0x44f1189,
    kMsgTerraformArtifact    = 0xf46093da,
    kMsgTerraformAction      = 0x6441936,
};
// ---- items of slice s00c602b0 end

// @ 0x00c5ed90
void Mission::FUN_00c5ed90(int v)
{
  if (mField1f0 != v) {
    mField1f0 = v;
    TriggerUIUpdate();
  }
}

// @ 0x00c5edb0
void Mission::FUN_00c5edb0()
{
  FUN_00c44b80();
  ((FnV1)mpVtable->p[0x14c / 4])(this, 0x248975f);
  ((FnV1)mpVtable->p[0x14c / 4])(this, 0x2489766);
  ((FnV1)mpVtable->p[0x14c / 4])(this, 0x248976a);
  ((FnV1)mpVtable->p[0x14c / 4])(this, 0x44f1189);
  ((FnV1)mpVtable->p[0x14c / 4])(this, 0xf46093da);
  ((FnV1)mpVtable->p[0x14c / 4])(this, 0x6441936);

  void* dst = (void*)&mpField34;
  void* ms = MessageServer();
  ((FnV2)(*(Vtbl**)ms)->p[0x20 / 4])(ms, dst, 0x2489760);
}

// @ 0x00c5ee40
void Mission::FUN_00c5ee40()
{
  FUN_00c44bd0();
  ((FnV1)mpVtable->p[0x150 / 4])(this, 0x248975f);
  ((FnV1)mpVtable->p[0x150 / 4])(this, 0x2489766);
  ((FnV1)mpVtable->p[0x150 / 4])(this, 0x248976a);
  ((FnV1)mpVtable->p[0x150 / 4])(this, 0x44f1189);
  ((FnV1)mpVtable->p[0x150 / 4])(this, 0xf46093da);
  ((FnV1)mpVtable->p[0x150 / 4])(this, 0x6441936);

  void* dst = (void*)&mpField34;
  void* ms = MessageServer();
  ((FnV3)(*(Vtbl**)ms)->p[0x2c / 4])(ms, dst, 0x2489760, 0xffffd8f1);
}

// @ 0x00c5eed0
void Mission::FUN_00c5eed0(int arg)
{
  if (!IsActive())
    return;

  switch (mField1f0) {
  case 0:
    GetText(0xb98c20c5, arg);
    return;
  case 1:
    GetText(0x2f8f74df, arg);
    return;
  case 2: {
    void* p = FUN_01021370();
    int a = ((HomePlanetObj*)p)->FUN_00b8de30();
    int b = FUN_01021240();
    if (a == b && FUN_01021080() != 2)
      GetText(0xed4b67a7, arg);
    else
      GetText(0xd0fbdf85, arg);
    return;
  }
  case 3:
    GetText(0xa29d2048, arg);
    return;
  case 4:
    GetText(0x81128ae1, arg);
    return;
  }
}

// @ 0x00c5efb0
void Mission::FUN_00c5efb0(int arg)
{
  if (!IsActive())
    return;

  switch (mField1f0) {
  case 0:
    GetText(0xda9e8dc6, arg);
    return;
  case 1:
    GetText(0xc28f4e24, arg);
    return;
  case 2: {
    void* p = FUN_01021370();
    int a = ((HomePlanetObj*)p)->FUN_00b8de30();
    int b = FUN_01021240();
    if (a == b && FUN_01021080() != 2)
      GetText(0xc404af28, arg);
    else
      GetText(0x48cc6b76, arg);
    return;
  }
  case 3:
    GetText(0x2dc5caa7, arg);
    return;
  case 4:
    GetText(0xba93258e, arg);
    return;
  }
}

// @ 0x00c5f090
int Mission::FUN_00c5f090()
{
  if (((FnI0)mpVtable->p[0x60 / 4])(this) == 3) {
    switch (mField1f0) {
    case 0: return 0x2864b01f;
    case 1: return 0x0501dd96;
    case 2: return 0x1d3ce6e6;
    case 3: return 0x7b0daf98;
    case 4: return 0x11965a4d;
    }
  }
  return FUN_00c44cb0();
}

// @ 0x00c5f0f0
int Mission::FUN_00c5f0f0(int a, int b)
{
  if (((FnI0)mpVtable->p[0x60 / 4])(this) == 3) {
    switch (mField1f0) {
    case 0: return 0xcb268f51;
    case 1: return 0x1e1135ac;
    case 2: return 0xc04fa4e8;
    case 3: return 0x2d28ce76;
    }
  }
  return -1;
}

// @ 0x00c5f150
int Mission::FUN_00c5f150()
{
  if (mField1f0 != 0 && mField1f0 != 1)
    return 0;
  return 1;
}

// @ 0x00c5f190
void FUN_00c5f190()
{
  FUN_00c47a10();
  cGameNounManager_s00c5_e260* m = (cGameNounManager_s00c5_e260*)SP::SpaceGameGet(0x11, 1);
  TribeObj* t = (TribeObj*)m->GetPlayerTribe();
  t->FUN_00fe5430();
}

// @ 0x00c5f1b0
MissionStory201::MissionStory201()
{
  MissionBaseCtor(this);
  int zero = 0;
  *(volatile int*)&mField1f0 = zero;
  *(volatile int*)&mpVtable  = (int)0x146fe60;
  *(volatile int*)&mpField04 = (int)0x146fe4c;
  *(volatile int*)&mpField34 = (int)0x146fe3c;
  *(volatile int*)&mpField1f4 = zero;
  *(volatile int*)&mField1f8 = zero;
  *(volatile int*)&mField1fc = zero;
}

// @ 0x00c5f250
void Mission::FUN_00c5f250()
{
  void* p = mpField1f4;
  if (p != 0) {
    mpField1f4 = 0;
    ((FnVoid)(*(Vtbl**)p)->p[0xc0 / 4])(p);
  }
  FUN_00c49f90();
}

// @ 0x00c5f280
void Mission::FUN_00c5f280()
{
  if (mField1f0 != 4) {
    ((FnVoid)mpVtable->p[0x6c / 4])(this);
    if (mField1f0 != 4) {
      mField1f0 = 4;
      TriggerUIUpdate();
    }
    FUN_00c472e0();
    FUN_00c471c0();
  }
}

// @ 0x00c5f2c0
void Mission::FUN_00c5f2c0()
{
  void* obj = mpField180;
  SomeVec* v = (SomeVec*)((FnP1)(*(Vtbl**)obj)->p[0x28 / 4])(obj, 0xedcaee05);

  uint16_t mask = (uint16_t)(v->mField10 & 0x30);
  int count;
  int* items;

  if (mask != 0) {
    count = v->mField8;
    if (count <= 0)
      return;
  } else {
    if (v->mField12 == 0)
      return;
    count = 1;
  }

  if (mask != 0)
    items = (int*)v->mpField0;
  else {
    uint16_t f12 = *(volatile uint16_t*)&v->mField12;
    items = (f12 != 0) ? (int*)v : 0;
  }

  Inventory* inv = ((cSPSimulatorSpaceGame*)SP::SpaceGameGet())->GetPlayerInventory();
  if (inv == 0 || count <= 0)
    return;

  do {
    Item item;
    item.mField0 = items[0];
    item.mField4 = 0;
    item.mField8 = 0;
    inv->FUN_00ff45e0(&item);
    items += 3;
  } while (--count != 0);
}

// @ 0x00c5f360
void Mission::FUN_00c5f360()
{
  SetSerializer();
  FUN_00c5f2c0();
  if (mField1f0 != 4) {
    ((FnVoid)mpVtable->p[0x6c / 4])(this);
    if (mField1f0 != 4) {
      mField1f0 = 4;
      TriggerUIUpdate();
    }
    FUN_00c472e0();
    FUN_00c471c0();
  }
}

// @ 0x00c5f3d0
int Mission::FUN_00c5f3d0()
{
  if (GetTargetPlanet() != 0) {
    Planet* p = (Planet*)GetTargetPlanet();
    return p->mField13c;
  }
  return 0;
}

// @ 0x00c5f4e0
int Mission::FUN_00c5f4e0(int id)
{
  int v0 = (mpField1f4 != 0) ? ((Planet*)mpField1f4)->mField13c : 0;

  if (v0 != id) {
    int v1 = (GetTargetPlanet() != 0)
               ? ((Planet*)GetTargetPlanet())->mField13c
               : 0;
    if (v1 != id)
      return 0;
  }
  return 1;
}

// @ 0x00c5f530
bool cSPMissionStory201::PickUFOWreckPlanet()
{
    FUN_01021260();
    cStar* star = (cStar*)FUN_01021230();
    if (star == 0)
        return false;

    cSolarSystem* ss = star->GetSolarSystem();
    if (ss != 0) {
        int count = ss->m14 - ss->m10;
        for (int i = 0; i < count; i++) {
            cPlanet* p = ss->m10[i];
            if (p != 0) {
                void* a = p->m13c;
                if (a != FUN_01021370()) {
                    if (p->FUN_00c70fb0() > 0) {
                        cPlanet* old = m1f4;
                        if (old != 0) {
                            m1f4 = 0;
                            old->v0c0();
                        }
                        ((cStarManager*)StarManager())->GetOrActivatePlanet(p->m13c, &m1f4);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// @ 0x00c5f5f0
void cSPMissionStory201::FUN_00c5f5f0()
{
    FUN_00c46b80();
    cBioElemSort* s;
    if (GetTargetPlanet())
        s = ((cBioElemSort*)GetTargetPlanet()->m13c)->SortBanners();
    else
        s = ((cBioElemSort*)0)->SortBanners();
    s->FUN_00bb9b00(0x40000, 0);
    s->FUN_00bb9c30();
    GetMissionManager(1)->FUN_00feba80();
}

// @ 0x00c5f640
bool cSPMissionStory201::GetTagString(unsigned tag, wstring* out)
{
    if (tag == 0x7a216096)
        return TagNameHelper(m1f4, out);
    if (tag == 0xe3d3c424)
        return TagNameHelper(GetTargetPlanet(), out);
    return cSPMission::GetTagString(tag, out);
}

// @ 0x00c5f690
void cSPMissionStory201::GetUIShortDescription()
{}

// @ 0x00c5f770
__declspec(noinline) bool cSPMissionStory201::FUN_00c5f770()
{ return GetUniverseContext() != 0; }

// @ 0x00c5fcf0
bool cSPMissionStory201::FUN_00c5fcf0()
{
    if (!Init())
        return false;
    if (!PickUFOWreckPlanet())
        return false;
    if (!FUN_00c5f770())
        return false;
    FUN_00c4a0c0();
    if (m180 != 0) {
        TryGetUIntProperty(m180, 0x637cf275, &m1f8);
        TryGetUIntProperty(m180, 0x637cf276, &m1fc);
    }
    return true;
}

// @ 0x00c5fd90
void* FUN_00c5fd90()
{
    if (GetCurrentGameMode() == (void*)0x01654c05) {
        if (GetUniverseContext() == 0) {
            cGameNounManager* nm = (cGameNounManager*)NounManager();
            tVecData* v = nm->GetGameDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                                                (void*)0x00c5fc70, (void*)0x00b1e500,
                                                (void*)0x018c88e4);
            cNoun*** items = &v->mItems[0];
            cNoun** begin = items[0];
            cNoun** end = items[1];
            int n = end - begin;
            int i = 0;
            for (cNoun** q = begin; i < n; i++, q++) {
                cNoun* p = *q;
                if (p->m228 == 0x611a05f)
                    return &p->m070;
            }
        }
    }
    return 0;
}

// @ 0x00c5fe00
void cSPMissionStory201::FUN_00c5fe00()
{}

// @ 0x00c5ff50
void cSPMissionStory201::FUN_00c5ff50()
{}

// @ 0x00c60120
void cSPMissionStory201::OnArtifactScanned()
{}

// @ 0x00c602b0
bool cSPMissionStory201_s00c6_02b0::HandleMessage(uint32_t msg, void* arg)
{
    switch (msg) {
    case kMsgTerraformStep: {
        cPlanet_s00c6_02b0* pMessagePlanet = ((cMessage*)arg)->mpPlanet;
        if (mpScannedPlanet == pMessagePlanet) {
            if (((cSPSimulatorSpaceGame_s00c6_02b0*)SpaceGameGet())->GetAvatar()) {
                void* pList = 0;
                int count = ((cPlanetModel*)PlanetModel())->mp24->GetPlanetList(&pList);
                cPlanet_s00c6_02b0** ppPlanets = (cPlanet_s00c6_02b0**)pList;
                for (int i = 0; i < count; i++) {
                    cPlanet_s00c6_02b0* pPlanet = ppPlanets[i];
                    if (pPlanet->mpType->mHash == 0x9597ce64) {
                        pPlanet->mFlags &= ~1u;
                        cGameNoun* pNoun = NounManager_s00c6_02b0()->CreateNoun(0x018c88e4);
                        if (pNoun) {
                            pNoun->FUN_00c6f770(0x0611a05f, -1, 0);
                            pNoun->mPropList.SetKey(pPlanet->mKey);
                            float* pValue;
                            pNoun->mPropList.SetValue(
                                FUN_0046d660(&pValue, pPlanet->mBounds));
                            pNoun->mFlagBlock.Set(true);
                        }
                    }
                }
            }
            GetMissionManager()->FUN_00febf20(Mission());
        } else if (Mission()->GetTargetPlanet() == pMessagePlanet) {
            if (((cSPSimulatorSpaceGame_s00c6_02b0*)SpaceGameGet())->GetAvatar()) {
                void* pList = 0;
                int count = ((cPlanetModel*)PlanetModel())->mp24->GetPlanetList(&pList);
                cPlanet_s00c6_02b0** ppPlanets = (cPlanet_s00c6_02b0**)pList;
                for (int i = 0; i < count; i++) {
                    cPlanet_s00c6_02b0* pPlanet = ppPlanets[i];
                    uint32_t hash = pPlanet->mpType->mHash;
                    if (hash == 0xba6596d0 || hash == 0xba6596d3) {
                        pPlanet->mFlags &= ~1u;
                        cGameNoun* pNoun = NounManager_s00c6_02b0()->CreateNoun(0x018c88e4);
                        if (pNoun) {
                            pNoun->FUN_00c6f770(0x0611a05e, -1, 0);
                            pNoun->mPropList.SetKey(pPlanet->mKey);
                            float* pValue;
                            pNoun->mPropList.SetValue(
                                FUN_0046d660(&pValue, pPlanet->mBounds));
                        }
                    }
                }
            }
        }
        break;
    }
    case kMsgTerraformSubStepA:
    case kMsgTerraformSubStepB:
        if (mStoryState == 2)
            Mission()->TriggerUIUpdate();
        break;
    case kMsgStoryRuinScanned: {
        if (((cMessage*)arg)->mParam8 !=
            (uint32_t)GetTriggerMgr()->FindTrigger(kScannedRuinTrigger))
            break;
        cSPMissionStory201Mission* pMission = Mission();
        cPlanet_s00c6_02b0* pPlanet = pMission->GetTargetPlanet();
        cStarRecordRef* pStarRecord = (cStarRecordRef*)pPlanet->mpStarRecord;
        void* pHandle = pMission->Vtbl()->FindMissionRecord(0xdd0f716a, pMission, 0);
        void* pContext = pStarRecord->GetCommContext();
        ((cCommManager*)CommManager())->FUN_00aeb720(-1, pContext, pHandle,
                                                     0xdd0f716a, pMission, 0);
        cAudioSystem* pAudio = EA_GetSystemAT();
        if (pAudio)
            SP_KillSetiEffects(0x0ea16562, pAudio->GetVoiceHandle());
        else
            SP_KillSetiEffects(0x0ea16562, 0);
        break;
    }
    case kMsgTerraformAction: {
        cActionTarget target;
        GetTriggerMgr()->AddTrigger(0x1838a3f5, &target);
        cPlayerInventory* pInventory =
            ((cSPSimulatorSpaceGame_s00c6_02b0*)GetUFOSimulator())->GetPlayerInventory();
        float* pForward = target.GetLocation();
        float x = pForward[0];
        float y = pForward[1];
        float z = pForward[2];
        float scale = 1.0f / sqrtf(z * z + y * y + x * x + kEps);
        float normal[3];
        normal[0] = x + (x * scale) * kOffsetScale;
        normal[1] = y + (y * scale) * kOffsetScale;
        normal[2] = z + (z * scale) * kOffsetScale;
        pInventory->SetNormal(pForward);
        pInventory->SetDistance(sqrtf(normal[2] * normal[2] + normal[1] * normal[1] +
                                      normal[0] * normal[0]));
        break;
    }
    case kMsgTerraformArtifact:
        if (((cMessage*)arg)->mParam8)
            Mission()->OnArtifactScanned((void*)((cMessage*)arg)->mParam8);
        break;
    }
    return cMissionMessageHandler::HandleMessage(msg, arg);
}

// @ 0x00c606e0
Simulator::cMissionTerraform::cMissionTerraform()
{
    BaseCtor();
    mEventStage = 0;
    mFlag1F4 = false;
    mFlag1F5 = false;
    mpVftable = (void*)0x1470128;
    mpVftable04 = (void*)0x146dfb4;
    mpVftable34 = (void*)0x1470118;
}
