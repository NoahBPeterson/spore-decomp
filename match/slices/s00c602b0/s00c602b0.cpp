// Slice s00c602b0 -- the SP terraforming mission (SP::cSPMissionTerraform), its
// message handler for the story-201 variant, and the Simulator pressure-event
// mission constructor.
//
//  00c602b0  cSPMissionStory201::HandleMessage            (ruin scan / stage change dispatch)
//  00c606e0  Simulator::cMissionTerraform ctor           (pressure-event mission)
//  00c60850  cSPMissionTerraform::OnTerraformSphereChange (first terraform step feedback)
//  00c608d0  cSPMissionTerraform::RegisterMessages
//  00c60930  cSPMissionTerraform::UnregisterMessages
//  00c609d0  cSPMissionTerraform::HasAnyRequiredTool    (tool list + player inventory)
//  00c60a70  cSPMissionTerraform::GetTargetPlanetScore  (property 0xd7a6baad, -1 default)
//  00c60ab0  cSPMissionTerraform::GetTargetTerraformScore (property 0xe51c23d2, 3 default)
//  00c60af0  cSPMissionTerraform::IsStageOneComplete
//  00c60cc0  cSPMissionTerraform::IsStageTwoComplete
//  00c60e90  cSPMissionTerraform::Init
//  00c60fa0  cSPMissionTerraform::ScoreTerraformStep
//  00c61070  cSPMissionTerraform::GetUITitle
//  00c61300  cSPMissionTerraform::GetTagString
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: no unwind frames).
#include "types.h"
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16
#define PV64 PV32 PV32

// ---------------------------------------------------------------------------------------------
// Forward declarations of the shared engine types.
class cSPMission;
class cSPMissionTerraform;
struct cPlanet;
struct cGameNoun;
struct cProperty;
struct cPropertyList;

// An eastl::basic_string<wchar_t> as used for the mission UI text: only the
// begin/end pair is observable from this slice.
struct wstring {
    wchar_t* mpBegin;               // +0x00
    wchar_t* mpEnd;                 // +0x04
    bool IsEmpty() const { return mpBegin == mpEnd; }
    wstring& operator=(const wstring& rhs);     // 0x0057cb60
};

// A resource key (12 bytes) as returned by the terraforming queries.
struct ResourceKey {
    uint32_t mGroup;                // +0x00
    uint32_t mType;                 // +0x04
    uint32_t mInstance;             // +0x08
};
inline bool operator!=(const ResourceKey& a, const ResourceKey& b)
{
    return a.mGroup != b.mGroup || a.mType != b.mType || a.mInstance != b.mInstance;
}

// A property of a property list: only the int case is read here.
struct cProperty {
    uint16_t pad00[9];              // +0x00
    uint16_t mwType;                // +0x12 (property type tag; 9 == int)
    int* GetInt();                  // 0x0041e990
};

// A named property list (the mission's "planet/mission variable" store).
struct cPropertyList {
    PV8 PV
    virtual bool Find(uint32_t id, cProperty** ppOut);     // +0x24
};

// The virtual interface a mission object is seen through for the calls made by
// this slice (the vptr sits at +0x00 of cSPMission).
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

// The planet model exposes the current planet object list through its +0x24 member.
struct cPlanetModelInner {
    PV32 PV8 PV4                                            // +0x000 .. +0x0ac
    virtual int GetPlanetList(void** ppList);               // +0x0b0
};
struct cPlanetModel {
    uint8_t pad00[0x24];
    cPlanetModelInner* mp24;                                // +0x24
};

// A planet object: only the flags/key/position and its type tag are used.
struct cPlanetType {
    uint32_t pad00[2];
    uint32_t mHash;                 // +0x08
};
struct cPlanet {
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

// A noun's property list (embedded in the noun at +0x70) and its two setters.
struct cNounPropertyList {
    PV8 PV4 PV2                                             // +0x000 .. +0x034
    virtual void SetKey(const void* pKey);                  // +0x38
    virtual void SetValue(const float* pValue);             // +0x3c
};

// The noun's "spawned" flag block (embedded at +0x148).
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

// The noun manager / space game accessors this slice uses.
struct cTerrainSphere {
    bool FUN_00c772c0(uint32_t id);     // 0x00c772c0
    void FUN_00c77bf0(uint32_t id);     // 0x00c77bf0
};
struct cGameNounManager {
    cGameNoun* CreateNoun(uint32_t type);   // 0x00b20c60
    cTerrainSphere* GetCurrentTerrainSphere();   // 0x00f67d90
};

// A per-layer simulator subsystem (only the two message thunks are used).
struct cSimulatorSubsystem {
    void FUN_0106ab20(uint32_t id);     // 0x0106ab20
    void FUN_0106dcd0(uint32_t id);     // 0x0106dcd0
};

// Tool IDs, inventory entries and tools.
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
// A game-data interface embedded in an inventory entry, at +0xc.
struct cGameDataInterface {
    PV2 PV
    virtual void* Find(uint32_t id);        // +0x0c
};
struct cInventoryEntry {
    uint8_t pad00[0x0c];
    cGameDataInterface mInterface;          // +0x0c
};

// The player inventory view used by the terraform mission.
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

// The space game / UFO simulator objects (the inventory and avatar live behind them).
struct cSPSimulatorSpaceGame {
    uint8_t pad00[0x40];
    cPlayerInventory* mpPlayerInventory;    // +0x40
    uint8_t pad44[0x54 - 0x44];
    void* mpAvatar;                         // +0x54
    cPlayerInventory* GetPlayerInventory(); // 0x00a1ad60
    void* GetAvatar();                      // 0x00b1fdb0
};

// Terraforming manager and its terraform-value query results.
struct cTerraformingManager {
    ResourceKey* QueryLevelValues(ResourceKey* pOut, int score, uint32_t id, cPlanet* pPlanet);  // 0x00bbc870
    ResourceKey* QueryFaceValues(ResourceKey* pOut, int score, uint32_t id, cPlanet* pPlanet);   // 0x00bbc950
    ResourceKey* QueryValue(ResourceKey* pOut, int score, uint32_t id);                          // 0x00bbca30
    int GetTerraformLevel(cPlanet* pPlanet);                                                     // 0x00bbc670
};

// The action target the trigger manager fills in.
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

// The audio system (only its +0x20 thunk is used).
struct cAudioSystem {
    PV8
    virtual void* GetVoiceHandle();     // +0x20
};

// The comm manager and the star record it is fed from.
struct cCommManager {
    void FUN_00aeb720(int param, void* pContext, void* pHandle, uint32_t id, void* pMission, int flags);  // 0x00aeb720
};
struct cStarRecordRef {
    uint8_t pad000[0x184];
    void* mpCommContext;            // +0x184
    void* GetCommContext();         // 0x00ce6950
};

// The mission manager.
struct cMissionManager {
    void FUN_00febf20(cSPMission* pMission);    // 0x00febf20
};

// A message delivered to the handlers: the trigger id and the planet at +0x10.
struct cMessage {
    uint32_t pad00[2];
    uint32_t mParam8;               // +0x08
    uint32_t pad0C;
    cPlanet* mpPlanet;              // +0x10
};

// The planet selection request used by Init.
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

// ---------------------------------------------------------------------------------------------
// cSPMission: the mission base (members are only the ones this slice touches).
class cSPMission {
public:
    // The message handler subobject sits 0x34 bytes into a mission object.
    static const uint32_t kHandlerOffset = 0x34;

    uint8_t pad000[0x78];
    uint32_t mMissionTypeKey;       // +0x78 (0xd85005e9 for the terraform missions)
    uint8_t pad07c[0x14c - 0x7c];
    wstring mUITitle;               // +0x14c
    uint8_t pad154[0x180 - 0x154];  // +0x154 .. +0x180 (the base ends where the subclasses' members begin)

    bool Init();                                        // 0x00c4ad50
    bool IsActive();                                    // 0x00c44c80
    uint32_t ReadTargetPlanetType();                    // 0x00c45b40
    void* GetPlanetRecordFromTargetType(uint32_t type); // 0x00c474b0
    void FUN_00c47180(void* pRecord);                   // 0x00c47180
    cPlanet* GetTargetPlanet();                         // 0x00970b30
    cPlanet* PickPlanet(const cPlanetPickParams* pParams);   // 0x00c47e20
    void FUN_00c4a0c0();                                // 0x00c4a0c0
    void TriggerUIUpdate();                             // 0x00c47d80
    void GetText(uint32_t id, wstring* pOut);           // 0x00c487d0
    void GetUITitle(wstring* pOut);                     // 0x00c48d40
    bool GetTagString(uint32_t tag, wstring* pOut);     // 0x00c491c0
    float FUN_00c44d00(cPlanet* pPlanet, void* arg);    // 0x00c44d00
    void FUN_00c44b80();                                // 0x00c44b80
    void FUN_00c44bd0();                                // 0x00c44bd0
    cMissionVtbl* Vtbl() { return (cMissionVtbl*)this; }
};

// ---------------------------------------------------------------------------------------------
// cSPMissionTerraform: the terraforming mission.
class cSPMissionTerraform : public cSPMission {
public:
    cPropertyList* mpPropertyList;  // +0x180
    uint8_t pad184[0x194 - 0x184];
    cToolID* mpToolIDsBegin;        // +0x194
    cToolID* mpToolIDsEnd;          // +0x198
    uint8_t pad19c[0x1e8 - 0x19c];
    cPlanet* mpTargetPlanet;        // +0x1e8
    uint8_t pad1ec[0x1f0 - 0x1ec];
    uint32_t mTerraformState;       // +0x1f0
    bool mFlag1F4;                  // +0x1f4
    bool mFlag1F5;                  // +0x1f5

    void OnTerraformSphereChange(int param);            // 0x00c60850
    void RegisterMessages();                            // 0x00c608d0
    void UnregisterMessages();                          // 0x00c60930
    bool HasAnyRequiredTool();                          // 0x00c609d0
    int GetTargetPlanetScore();                         // 0x00c60a70
    int GetTargetTerraformScore();                      // 0x00c60ab0
    bool IsStageOneComplete();                          // 0x00c60af0
    bool IsStageTwoComplete();                          // 0x00c60cc0
    bool Init();                                        // 0x00c60e90
    float ScoreTerraformStep(cPlanet* pPlanet, void* arg);  // 0x00c60fa0
    void GetUITitle(wstring* pOut);                     // 0x00c61070
    bool GetTagString(uint32_t tag, wstring* pOut);     // 0x00c61300
};

// The story-201 mission object (a mission whose handler is cSPMissionStory201).
class cSPMissionStory201Mission : public cSPMission {
public:
    uint8_t pad180[0x1f0 - 0x180];
    uint32_t mStoryState;           // +0x1f0
    cPlanet* mpScannedPlanet;       // +0x1f4
    void OnArtifactScanned(void* pArtifact);   // 0x00c60120
};

// The story-201 mission, seen through its message-handler subobject (the
// IHandlerRC base sits at mission + 0x34, so the members below are the mission's
// +0x1f0 / +0x1f4 seen from the handler).
class cMissionMessageHandler {
public:
    virtual bool HandleMessage(uint32_t msg, void* arg);    // 0x00c4a6b0
};

class cSPMissionStory201 : public cMissionMessageHandler {
public:
    uint8_t pad004[0x1bc - 0x04];
    uint32_t mStoryState;           // +0x1bc (mission +0x1f0)
    cPlanet* mpScannedPlanet;       // +0x1c0 (mission +0x1f4)
    virtual bool HandleMessage(uint32_t msg, void* arg);    // 0x00c602b0
    // The mission object this handler subobject belongs to.
    cSPMissionStory201Mission* Mission()
    {
        return (cSPMissionStory201Mission*)((char*)this - cSPMission::kHandlerOffset);
    }
};

// The base class of the Simulator pressure-event mission (its ctor is at 0xc48e90).
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

// Simulator::cMissionTerraform: the pressure-event mission (only its ctor here).
namespace Simulator {
class cMissionTerraform : public cGenericPressureEvent {
public:
    cMissionTerraform();            // 0x00c606e0
};
}  // namespace Simulator

// ---------------------------------------------------------------------------------------------
// Free helpers / singletons.
void* __cdecl SpaceGameGet();                           // 0x01002bd0
void* __cdecl PlanetModel();                            // 0x00b3d350
cGameNounManager* __cdecl NounManager();                // 0x00b3d300
cTerraformingManager* __cdecl TerraformingManager();    // 0x00b3d430
cTriggerManager* __cdecl GetTriggerMgr();               // 0x00b3d4d0
void* __cdecl CommManager();                            // 0x00b3d4a0
cAudioSystem* __cdecl EA_GetSystemAT();                 // 0x00a206f0
cMissionManager* __cdecl GetMissionManager();           // 0x00feb9f0
void* __cdecl GetUFOSimulator();                        // 0x00ffbe50
int  __cdecl GetUniverseContext();                      // 0x01021080
void* __cdecl GetActivePlanetRecord();                  // 0x010212a0
int  __cdecl IsArchivedMission();                       // 0x01021240
void* __cdecl GetActivePlanet();                        // 0x01021260
cSimulatorSubsystem* __cdecl FUN_010666a0();            // 0x010666a0
void* __cdecl FUN_00b8de30(void* pRecord);              // 0x00b8de30
float* __cdecl FUN_0046d660(float** ppOut, const float* pValue);  // 0x0046d660
void __cdecl WStr_Format(wstring* pOut, const wchar_t* pFormat, int value);  // 0x0041e050
void __cdecl SP_KillSetiEffects(uint32_t id, void* pHandle);    // 0x00435ed0

extern const char kScannedRuinTrigger[];                // 0x01470088 "SPG_Story201ScannedRuin"
extern const wchar_t kIntFormat[];                      // 0x013f01bc
extern const ResourceKey kNoPlanetKey;                  // 0x01693170
extern const float kEps;                                // 0x013ec4b8 (1e-8f)
extern const float kOffsetScale;                        // 0x013eecd8 (20.0f)

// The message ids the terraform mission reacts to.
enum {
    kMsgTerraformStep        = 0x248975f,
    kMsgTerraformSubStepA    = 0x2489766,
    kMsgTerraformSubStepB    = 0x248976a,
    kMsgStoryRuinScanned     = 0x44f1189,
    kMsgTerraformArtifact    = 0xf46093da,
    kMsgTerraformAction      = 0x6441936,
};

// =============================================================================================
// @ 0x00c602b0
// =============================================================================================
bool cSPMissionStory201::HandleMessage(uint32_t msg, void* arg)
{
    switch (msg) {
    case kMsgTerraformStep: {
        cPlanet* pMessagePlanet = ((cMessage*)arg)->mpPlanet;
        if (mpScannedPlanet == pMessagePlanet) {
            if (((cSPSimulatorSpaceGame*)SpaceGameGet())->GetAvatar()) {
                void* pList = 0;
                int count = ((cPlanetModel*)PlanetModel())->mp24->GetPlanetList(&pList);
                cPlanet** ppPlanets = (cPlanet**)pList;
                for (int i = 0; i < count; i++) {
                    cPlanet* pPlanet = ppPlanets[i];
                    if (pPlanet->mpType->mHash == 0x9597ce64) {
                        pPlanet->mFlags &= ~1u;
                        cGameNoun* pNoun = NounManager()->CreateNoun(0x018c88e4);
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
            if (((cSPSimulatorSpaceGame*)SpaceGameGet())->GetAvatar()) {
                void* pList = 0;
                int count = ((cPlanetModel*)PlanetModel())->mp24->GetPlanetList(&pList);
                cPlanet** ppPlanets = (cPlanet**)pList;
                for (int i = 0; i < count; i++) {
                    cPlanet* pPlanet = ppPlanets[i];
                    uint32_t hash = pPlanet->mpType->mHash;
                    if (hash == 0xba6596d0 || hash == 0xba6596d3) {
                        pPlanet->mFlags &= ~1u;
                        cGameNoun* pNoun = NounManager()->CreateNoun(0x018c88e4);
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
        cPlanet* pPlanet = pMission->GetTargetPlanet();
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
            ((cSPSimulatorSpaceGame*)GetUFOSimulator())->GetPlayerInventory();
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

// =============================================================================================
// @ 0x00c606e0
// =============================================================================================
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

// =============================================================================================
// @ 0x00c60850
// =============================================================================================
void cSPMissionTerraform::OnTerraformSphereChange(int param)
{
    switch (param) {
    case 1: {
        if (!IsActive())
            return;
        if (GetTargetPlanet() != GetActivePlanet())
            return;
        cTerrainSphere* pSphere = NounManager()->GetCurrentTerrainSphere();
        if (pSphere == 0)
            return;
        if (pSphere->FUN_00c772c0(0x6626789))
            return;
        FUN_010666a0()->FUN_0106ab20(3);
        pSphere->FUN_00c77bf0(0x6626789);
        FUN_010666a0()->FUN_0106dcd0(0x3a90f931);
        break;
    }
    }
}

// =============================================================================================
// @ 0x00c608d0
// =============================================================================================
void cSPMissionTerraform::RegisterMessages()
{
    FUN_00c44b80();
    Vtbl()->AddMessageHandler(kMsgTerraformStep);
    Vtbl()->AddMessageHandler(kMsgTerraformSubStepA);
    Vtbl()->AddMessageHandler(kMsgTerraformSubStepB);
    Vtbl()->AddMessageHandler(0x43f2583);
    Vtbl()->AddMessageHandler(0x490d429);
}

// =============================================================================================
// @ 0x00c60930
// =============================================================================================
void cSPMissionTerraform::UnregisterMessages()
{
    FUN_00c44bd0();
    Vtbl()->RemoveMessageHandler(kMsgTerraformStep);
    Vtbl()->RemoveMessageHandler(kMsgTerraformSubStepA);
    Vtbl()->RemoveMessageHandler(kMsgTerraformSubStepB);
    Vtbl()->RemoveMessageHandler(0x43f2583);
    Vtbl()->RemoveMessageHandler(0x490d429);
}

// =============================================================================================
// @ 0x00c609d0
// =============================================================================================
bool cSPMissionTerraform::HasAnyRequiredTool()
{
    cPlayerInventory* pInventory =
        ((cSPSimulatorSpaceGame*)SpaceGameGet())->GetPlayerInventory();
    if (pInventory == 0)
        return false;
    int count = (int)(mpToolIDsEnd - mpToolIDsBegin);
    bool found = false;
    for (int i = 0; i < count; i++) {
        const cToolID* pID = &mpToolIDsBegin[i];
        if (pInventory->HasToolID(pID)) {
            cTool* pTool = pInventory->GetToolFromToolID(pID);
            if (pTool != 0 && pTool->GetStackCount() > 0)
                found = true;
        }
    }
    return found;
}

// =============================================================================================
// @ 0x00c60a70
// =============================================================================================
int cSPMissionTerraform::GetTargetPlanetScore()
{
    int score = -1;
    cPropertyList* pList = mpPropertyList;
    if (pList != 0) {
        cProperty* pProperty;
        if (pList->Find(0xd7a6baad, &pProperty) && pProperty->mwType == 9)
            score = *pProperty->GetInt();
    }
    return score;
}

// =============================================================================================
// @ 0x00c60ab0
// =============================================================================================
int cSPMissionTerraform::GetTargetTerraformScore()
{
    int score = -1;
    cPropertyList* pList = mpPropertyList;
    if (pList != 0) {
        cProperty* pProperty;
        if (pList->Find(0xe51c23d2, &pProperty) && pProperty->mwType == 9)
            score = *pProperty->GetInt();
    }
    return score == -1 ? 3 : score;
}

// =============================================================================================
// @ 0x00c60af0
// =============================================================================================
bool cSPMissionTerraform::IsStageOneComplete()
{
    if (mTerraformState != 1)
        return false;
    int score = GetTargetTerraformScore();
    ResourceKey value;
    bool bLevelA = *TerraformingManager()->QueryLevelValues(&value, score, 0x6d60a1cc, 0) !=
                   kNoPlanetKey;
    bool bLevelB = *TerraformingManager()->QueryLevelValues(&value, score, 0x29c388a, 0) !=
                   kNoPlanetKey;
    bool bLevelC = *TerraformingManager()->QueryLevelValues(&value, score, 0x3a8be428, 0) !=
                   kNoPlanetKey;
    bool bToolA = false;
    bool bToolB = false;
    bool bToolC = false;
    cPlayerInventory* pInventory =
        ((cSPSimulatorSpaceGame*)SpaceGameGet())->GetPlayerInventory();
    int count = pInventory->GetToolCount();
    for (int i = 0; i < count; i++) {
        cInventoryEntry* pEntry = (cInventoryEntry*)pInventory->GetToolEntry(i);
        if (pEntry == 0)
            continue;
        cTool* pTool = (cTool*)pEntry->mInterface.Find(0x70a2863c);
        if (pTool == 0)
            continue;
        uint32_t toolKey = pTool->FUN_00b8f860();
        switch (toolKey) {
        case 0x29c388a:
            bToolB = true;
            break;
        case 0x3a8be428:
            bToolC = true;
            break;
        case 0x6d60a1cc:
            bToolA = true;
            break;
        }
    }
    if (!(bLevelA || bToolA))
        return true;
    if (!(bLevelB || bToolB))
        return true;
    if (!(bLevelC || bToolC))
        return true;
    return false;
}

// =============================================================================================
// @ 0x00c60cc0
// =============================================================================================
bool cSPMissionTerraform::IsStageTwoComplete()
{
    if (mTerraformState != 2)
        return false;
    ResourceKey faceKey;
    ResourceKey valueKey;
    int score = GetTargetTerraformScore();
    bool bFaceA = *TerraformingManager()->QueryFaceValues(&faceKey, score, 0, 0) != kNoPlanetKey;
    bool bFaceB = *TerraformingManager()->QueryFaceValues(&valueKey, score, 1, 0) != kNoPlanetKey;
    bool bValue = *TerraformingManager()->QueryValue(&valueKey, score, 0) != kNoPlanetKey;
    int faces = (bFaceB ? 1 : 0) + (bFaceA ? 1 : 0);
    int values = bValue ? 1 : 0;
    int countA = 0;
    int countB = 0;
    cPlayerInventory* pInventory =
        ((cSPSimulatorSpaceGame*)SpaceGameGet())->GetPlayerInventory();
    int count = pInventory->GetToolCount();
    for (int i = 0; i < count; i++) {
        cInventoryEntry* pEntry = (cInventoryEntry*)pInventory->GetToolEntry(i);
        if (pEntry == 0)
            continue;
        cTool* pTool = (cTool*)pEntry->mInterface.Find(0x30fc270b);
        if (pTool == 0)
            continue;
        if (pTool->FUN_00ac0c30())
            countA++;
        if (pTool->FUN_00ac0c50())
            countB++;
    }
    if (countA + faces >= 2 && countB + values >= 1)
        return false;
    return true;
}

// =============================================================================================
// @ 0x00c60e90
// =============================================================================================
bool cSPMissionTerraform::Init()
{
    if (!cSPMission::Init())
        return false;
    uint32_t type = ReadTargetPlanetType();
    if (type != 0x2ca33bdb) {
        void* pRecord = GetPlanetRecordFromTargetType(type);
        if (pRecord != 0)
            FUN_00c47180(pRecord);
        if (GetTargetPlanet() == 0) {
            int score = GetTargetPlanetScore();
            cPlanetPickParams params;
            switch (score) {
            case 0:
                params.mPlanetType = 4;
                break;
            case 1:
                params.mPlanetType = 8;
                break;
            case 2:
                params.mPlanetType = 0x10;
                break;
            default:
                params.mPlanetType = 0x1c;
                break;
            }
            params.mPickMode = 2;
            cPlanet* pPlanet = PickPlanet(&params);
            if (pPlanet == 0)
                return false;
            FUN_00c47180(pPlanet);
        }
    }
    if (!Vtbl()->IsReady())
        return false;
    FUN_00c4a0c0();
    Vtbl()->RefreshProgress();
    return true;
}

// =============================================================================================
// @ 0x00c60fa0
// =============================================================================================
float cSPMissionTerraform::ScoreTerraformStep(cPlanet* pPlanet, void* arg)
{
    float value = FUN_00c44d00(pPlanet, arg);
    if (0.0f < value) {
        int score = GetTargetPlanetScore();
        int level = TerraformingManager()->GetTerraformLevel(pPlanet);
        if (score == -1) {
            if (level == 3)
                return 1.0f;
            return -1.0f;
        }
        if (level == score)
            return 1.0f;
        return -1.0f;
    }
    return value;
}

// =============================================================================================
// @ 0x00c61070
// =============================================================================================
void cSPMissionTerraform::GetUITitle(wstring* pOut)
{
    if (mUITitle.IsEmpty() && mMissionTypeKey == 0xd85005e9) {
        switch (mTerraformState) {
        case 0:
            if (mFlag1F4) {
                GetText(0x2fd4e76a, pOut);
                mUITitle = *pOut;
                return;
            }
            if (GetUniverseContext() == 1) {
                if (GetActivePlanetRecord() != 0) {
                    void* pRecord = GetTargetPlanet() != 0 ?
                                    GetTargetPlanet()->mpStarRecord : 0;
                    if (GetActivePlanetRecord() == pRecord) {
                        GetText(0x791cfa76, pOut);
                        mUITitle = *pOut;
                        return;
                    }
                }
                int archived = IsArchivedMission();
                void* pRecord = GetTargetPlanet() != 0 ?
                                FUN_00b8de30(GetTargetPlanet()->mpStarRecord) : 0;
                if (archived != 0 && archived == (int)(size_t)pRecord) {
                    GetText(0x639f0b00, pOut);
                    mUITitle = *pOut;
                    return;
                }
            } else if (GetUniverseContext() == 0) {
                if (GetActivePlanetRecord() != 0) {
                    void* pRecord = GetTargetPlanet() != 0 ?
                                    GetTargetPlanet()->mpStarRecord : 0;
                    if (GetActivePlanetRecord() == pRecord) {
                        GetText(0xdf81d02e, pOut);
                        mUITitle = *pOut;
                        return;
                    }
                }
            }
            break;
        case 1:
            if (GetUniverseContext() == 0) {
                if (GetActivePlanetRecord() != 0) {
                    void* pRecord = GetTargetPlanet() != 0 ?
                                    GetTargetPlanet()->mpStarRecord : 0;
                    if (GetActivePlanetRecord() == pRecord) {
                        GetText(0x14dae625, pOut);
                        mUITitle = *pOut;
                        return;
                    }
                }
            }
            break;
        case 2:
            if (GetUniverseContext() == 0) {
                if (GetActivePlanetRecord() != 0) {
                    void* pRecord = GetTargetPlanet() != 0 ?
                                    GetTargetPlanet()->mpStarRecord : 0;
                    if (GetActivePlanetRecord() == pRecord) {
                        GetText(0xe050be3a, pOut);
                        mUITitle = *pOut;
                        return;
                    }
                }
            }
            break;
        case 3:
            if (mFlag1F5) {
                GetText(0x8c5de162, pOut);
                mUITitle = *pOut;
                return;
            }
            GetText(0xc1f54b2f, pOut);
            mUITitle = *pOut;
            return;
        }
    }
    cSPMission::GetUITitle(pOut);
}

// =============================================================================================
// @ 0x00c61300
// =============================================================================================
bool cSPMissionTerraform::GetTagString(uint32_t tag, wstring* pOut)
{
    if (tag == 0xd1ebc6a6) {
        int score = GetTargetPlanetScore();
        WStr_Format(pOut, kIntFormat, score);
        return true;
    }
    if (tag == 0x6b6f15e7) {
        int score = GetTargetTerraformScore();
        WStr_Format(pOut, kIntFormat, score);
        return true;
    }
    return cSPMission::GetTagString(tag, pOut);
}
