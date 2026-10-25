// src/game/SPGonzago/SPMissionTerraform.cpp -- migrated from slice(s) s00c602b0 by tools/migrate/rewrite.py
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
// ---- items of slice s00c602b0 end

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
