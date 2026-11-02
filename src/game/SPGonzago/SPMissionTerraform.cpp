// src/game/SPGonzago/SPMissionTerraform.cpp -- migrated from slice(s) s00c61390, s00c602b0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionTerraform.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "SP/cSPMission.h"
#include "SP/cPlanet.h"
#include "SP/cPlanetModel.h"
#include "SP/cITerrainSphere.h"
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cTerrainSphere.h"

// unnamed retail callees and globals (address in the comment)
extern const wchar_t kIntFormat[];                      // 0x013f01bc
#include <math.h>

// ---- items of slice s00c602b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16
class cSPMission;
class cSPMissionTerraform;
struct cPlanet;
struct cProperty;
struct cPropertyList;
struct wstring {
    wchar_t* mpBegin;               // +0x00
    wchar_t* mpEnd;                 // +0x04
    bool IsEmpty() const { return mpBegin == mpEnd; }
    wstring& operator=(const wstring& rhs);     // 0x0057cb60
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
struct cProperty {
    uint16_t pad00[9];              // +0x00
    uint16_t mwType;                // +0x12 (property type tag; 9 == int)
    int* GetInt();                  // 0x0041e990
};
struct cPropertyList {
    PV8 PV
    virtual bool Find(uint32_t id, cProperty** ppOut);     // +0x24
};
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
struct cGameDataInterface {
    PV2 PV
    virtual void* Find(uint32_t id);        // +0x0c
};
struct cInventoryEntry {
    uint8_t pad00[0x0c];
    cGameDataInterface mInterface;          // +0x0c
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
struct cSPSimulatorSpaceGame {
    uint8_t pad00[0x40];
    cPlayerInventory* mpPlayerInventory;    // +0x40
    uint8_t pad44[0x54 - 0x44];
    void* mpAvatar;                         // +0x54
    cPlayerInventory* GetPlayerInventory(); // 0x00a1ad60
    void* GetAvatar();                      // 0x00b1fdb0
};
struct cTerraformingManager {
    ResourceKey* QueryLevelValues(ResourceKey* pOut, int score, uint32_t id, cPlanet* pPlanet);  // 0x00bbc870
    ResourceKey* QueryFaceValues(ResourceKey* pOut, int score, uint32_t id, cPlanet* pPlanet);   // 0x00bbc950
    ResourceKey* QueryValue(ResourceKey* pOut, int score, uint32_t id);                          // 0x00bbca30
    int GetTerraformLevel(cPlanet* pPlanet);                                                     // 0x00bbc670
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
void* __cdecl SpaceGameGet();                           // 0x01002bd0
cTerraformingManager* __cdecl TerraformingManager();    // 0x00b3d430
void __cdecl WStr_Format(wstring* pOut, const wchar_t* pFormat, int value);  // 0x0041e050
extern const wchar_t kIntFormat[];                      // 0x013f01bc
extern const ResourceKey kNoPlanetKey;                  // 0x01693170
// ---- items of slice s00c602b0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern const ResourceKey kNoPlanetKey;                  // 0x01693170

// ---- items of slice s00c61390 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  uint8;
struct Mission {
    // Functions defined by this slice.
    void  FUN_00c61390(int arg);
    void  FUN_00c61450(int msg, int arg);
    void  FUN_00c61550();
    void  FUN_00c61570();
    int   FUN_00c615c0(int param);
    void* FUN_00c61bb0();
    char  FUN_00c61d70();
    int   FUN_00c61dd0(int param);
    void  FUN_00c61e20(int msg, int arg);
    char  FUN_00c61e80(int msg, int out);
    void* FUN_00c61f20();
    int   FUN_00c620c0(int tag);
    void  FUN_00c62100();
    void  FUN_00c62180(int* a, int* b);
    char  FUN_00c62200();
    void  FUN_00c62250(int msg, int arg);
    void* FUN_00c62370();
    char  FUN_00c624c0();
    int   FUN_00c62540(int param);
    void  FUN_00c62590(int msg, int arg);
    int   FUN_00c62710();
    void  FUN_00c62750(int msg, int arg);

    // __thiscall helpers from the rest of the game.
    void* FUN_0970b30();
    void* FUN_00b21340(int a, int b, int c, int d, int e);
    void  FUN_00ba95a0(void* src);
    void  FUN_00bdc4a0(int arg);
    void* FUN_00bbc870(void* out, int score, int id, int zero);
    void* FUN_00bbc950(void* out, int score, int id, int zero);
    void* FUN_00bbca30(void* out, int score, int id);
    int   FUN_00c478b0(int arg);
    void  FUN_00c4a6b0(int msg, int arg);
    void  FUN_00c47d80();
    void  FUN_00c46160();
    void  FUN_00c461d0();
    void  FUN_00c46250();
    void  FUN_00c471c0();
    void  FUN_00c472e0();
    void  FUN_00c46590();
    char  FUN_00c4ad50();
    void  FUN_00c4a0c0();
    void  FUN_00c4b760();
    char  FUN_00c491c0(int msg, int out);
    void* FUN_00bfc5f0();
    int   FUN_00fe6770(int id);
    int   FUN_00fe66f0(int id);
    char  FUN_00fe4180(int id);
    void* FUN_00c451e0();
    int   FUN_00ff0420();
    int   FUN_00ff0870();
    void  FUN_00ff0760();
    char  FUN_00c308e0(int arg);
    void  FUN_00c48e90();
    int   FUN_00c70fb0();
    int   FUN_00c60ab0();
    char  FUN_00c60af0();
    char  FUN_00c60cc0();
    char  FUN_00c609d0();
    void* FUN_005c65e0();
    char  FUN_00ae9390();
    void  FUN_00dd8640(int a, int b, int c, int d, int e, int f);
    void* FUN_008414c0();
    void* FUN_00ba6dc0(int arg);
    void* FUN_00b8de30();
    void* FUN_00b1fdb0();
};
void* FUN_01021260();
void* FUN_01021080();
void* FUN_01021300();
void* FUN_00b3d430();
char  FUN_005f78f0(const void* a, const void* b);
char  FUN_00c70150(void* civs, void* owner, int flag);
typedef char (__thiscall* VTCFn)(void*);
#define VTC(o,off) (((VTCFn)(*(void***)(o))[(off)/4])((void*)(o)))
// ---- items of slice s00c61390 end

// @ 0x00c609d0
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

// @ 0x00c60a70
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

// @ 0x00c60ab0
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

// @ 0x00c60af0
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

// @ 0x00c60cc0
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

// @ 0x00c60e90
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

// @ 0x00c60fa0
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

// @ 0x00c61300
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

// @ 0x00c615c0
int Mission::FUN_00c615c0(int param)
{
    int rc = this->FUN_00c478b0(param);
    int st;

    if (rc != 3)
        return rc;

    if (VTC(this, 0xf8) == 0) {
        void* planet = this->FUN_0970b30();
        if (FUN_01021260() == planet) {
            int f = ((Mission*)this->FUN_0970b30())->FUN_00c70fb0();
            int score = this->FUN_00c60ab0();
            st = *(int*)((char*)this + 0x1f0);
            if (st != 0 && score > f) {
                if (*(int*)((char*)this + 0x78) == (int)0xd85005e9)
                    this->FUN_00c61390(0);
                *(int*)((char*)this + 0x1f0) = 0;
                this->FUN_00c47d80();
            } else if (st != 1 && this->FUN_00c60af0()) {
                if (*(int*)((char*)this + 0x1f0) != 1) {
                    if (*(int*)((char*)this + 0x78) == (int)0xd85005e9)
                        this->FUN_00c61390(0);
                    *(int*)((char*)this + 0x1f0) = 1;
                    this->FUN_00c47d80();
                }
                this->FUN_00c461d0();
            } else if (*(int*)((char*)this + 0x78) == (int)0xd85005e9 &&
                       st != 2 && this->FUN_00c60cc0()) {
                if (*(int*)((char*)this + 0x1f0) != 2) {
                    if (*(int*)((char*)this + 0x78) == (int)0xd85005e9)
                        this->FUN_00c61390(0);
                    *(int*)((char*)this + 0x1f0) = 2;
                    this->FUN_00c47d80();
                }
                this->FUN_00c46250();
            }
        }
    }

    switch (*(int*)((char*)this + 0x1f0)) {
    case 0: {
        void* planet = this->FUN_0970b30();
        if (FUN_01021260() != planet)
            goto lab_17ca;
        if (FUN_01021080() != 0)
            goto lab_17ca;
        {
            int f = ((Mission*)this->FUN_0970b30())->FUN_00c70fb0();
            int score = this->FUN_00c60ab0();
            if (score > f) {
                if (*(int*)((char*)this + 0x78) != (int)0xd85005e9)
                    goto lab_17ca;
                if (*(uint8*)((char*)this + 0x1f4) != 0)
                    goto lab_17d7;
                if (!this->FUN_00c609d0()) {
                    void* body = ((Mission*)this->FUN_0970b30())->FUN_008414c0();
                    if (body != 0 &&
                        *(float*)0x013f9428 >= *(float*)((char*)body + 0x1fd4) &&
                        *(float*)0x013f9428 >= *(float*)((char*)body + 0x1fd8)) {
                        *(uint8*)((char*)this + 0x1f4) = 1;
                        this->FUN_00c47d80();
                    }
                }
                goto lab_17ca;
            }
            if (*(int*)((char*)this + 0x1f0) != 1) {
                if (*(int*)((char*)this + 0x78) == (int)0xd85005e9)
                    this->FUN_00c61390(0);
                *(int*)((char*)this + 0x1f0) = 1;
                this->FUN_00c47d80();
            }
            this->FUN_00c461d0();
        }
lab_17ca:
        if (*(uint8*)((char*)this + 0x1f4) == 0)
            goto lab_1b74;
lab_17d7:
        if (!this->FUN_00c609d0())
            goto lab_1b74;
        *(uint8*)((char*)this + 0x1f4) = 0;
        this->FUN_00c47d80();
        break;
    }
    case 1: {
        void* planet = this->FUN_0970b30();
        if (FUN_01021260() != planet)
            goto lab_1b74;
        int score = this->FUN_00c60ab0();
        int k1[3], k2[3], k3[3];
        if (!FUN_005f78f0(
                ((Mission*)FUN_00b3d430())->FUN_00bbc870(k1, score, 0x6d60a1cc, 0),
                (void*)0x01693170))
            goto lab_1b74;
        if (!FUN_005f78f0(
                ((Mission*)FUN_00b3d430())->FUN_00bbc870(k2, score, 0x029c388a, 0),
                (void*)0x01693170))
            goto lab_1b74;
        if (!FUN_005f78f0(
                ((Mission*)FUN_00b3d430())->FUN_00bbc870(k3, score, 0x3a8be428, 0),
                (void*)0x01693170))
            goto lab_1b74;

        if (*(int*)((char*)this + 0x78) != (int)0xd85005e9)
            goto lab_1b31;
        if (*(int*)((char*)this + 0x1f0) != 2) {
            this->FUN_00c61390(0);
            *(int*)((char*)this + 0x1f0) = 2;
            this->FUN_00c47d80();
        }
        this->FUN_00c46250();
        break;
    }
    case 2: {
        void* planet = this->FUN_0970b30();
        if (FUN_01021260() != planet)
            goto lab_1b74;
        int score = this->FUN_00c60ab0();
        int k1[3], k2[3], k3[3];
        if (!FUN_005f78f0(
                ((Mission*)FUN_00b3d430())->FUN_00bbc950(k1, score, 0, 0),
                (void*)0x01693170))
            goto lab_1b74;
        if (!FUN_005f78f0(
                ((Mission*)FUN_00b3d430())->FUN_00bbc950(k2, score, 1, 0),
                (void*)0x01693170))
            goto lab_1b74;
        if (!FUN_005f78f0(
                ((Mission*)FUN_00b3d430())->FUN_00bbca30(k3, score, 0),
                (void*)0x01693170))
            goto lab_1b74;

        if (*(int*)((char*)this + 0x78) == (int)0xd85005e9) {
            void* p = this->FUN_0970b30();
            int civs = *(int*)((char*)p + 0x13c);
            if (((Mission*)FUN_01021300())->FUN_00c308e0(civs)) {
                if (*(int*)((char*)this + 0x1f0) == 3)
                    break;
                if (*(int*)((char*)this + 0x78) == (int)0xd85005e9)
                    this->FUN_00c61390(1);
                *(int*)((char*)this + 0x1f0) = 3;
                this->FUN_00c47d80();
                break;
            }
        }
        goto lab_1b31;
    }
    case 3: {
        void* planet = this->FUN_0970b30();
        if (FUN_01021260() != planet)
            goto lab_1b74;
        void* tp = this->FUN_0970b30();
        if (*(uint8*)((char*)this + 0x1f5) == 0) {
            void* civs = (void*)*(int*)((char*)tp + 0x13c);
            void* owner = this->FUN_00c451e0();
            if (FUN_00c70150(civs, owner, 0) != 0) {
                *(uint8*)((char*)this + 0x1f5) = 1;
                this->FUN_00c47d80();
            }
            break;
        }
        {
            char* civVec = (char*)*(int*)((char*)tp + 0x13c);
            void* owner = this->FUN_00c451e0();
            if (FUN_00c70150(civVec, owner, 0) == 0) {
                *(uint8*)((char*)this + 0x1f5) = 0;
                this->FUN_00c47d80();
                break;
            }
            int n = (*(int*)(civVec + 0x160) - *(int*)(civVec + 0x15c)) >> 2;
            char found = 0;
            for (int i = 0; i < n; i++) {
                Mission* civ = *(Mission**)(*(int*)(civVec + 0x15c) + i * 4);
                void* owner2 = this->FUN_00c451e0();
                int eid = *(int*)((char*)owner2 + 0x84);
                if (civ->FUN_00ff0420() == eid) {
                    int* cities = (int*)civ->FUN_005c65e0();
                    int nc = (cities[1] - cities[0]) >> 2;
                    for (int j = 0; j < nc; j++) {
                        Mission* city = *(Mission**)(cities[0] + j * 4);
                        int nb = city->FUN_00ff0870();
                        char* link = *(char**)((char*)city + 0x7c) + 0x34;
                        for (int k = 0; k < nb; k++) {
                            if (*(int*)link == 0x018ea2cc)
                                found = 1;
                            link += 0x38;
                        }
                        city->FUN_00ff0760();
                    }
                }
            }
            if (found)
                goto lab_1b31;
        }
        break;
    }
    }

lab_1b74:
    return rc;
lab_1b31:
    this->FUN_00c61570();
    return rc;
}
