// Slice s00efa1b0 -- Simulator::cScenarioTutorials::Update (0x00efa1b0, 4904 bytes).
// Region flags: /O2 /MD /Gy /TP.
//
// The Galactic Adventures scenario tutorial step machine: switch on the current tutorial
// category (this+0x30, 0..0xb); within a category the first step that is not yet complete
// (IsStepComplete, 0x00ef8820) gets its hint shown (ShowStepHint, 0x00ef8390), its category
// message sent (HandleCategoryMessage, 0x00efa110) or its category state set (SetCategoryState,
// 0x00efa0b0).  Case bodies are written in the original's body layout order.
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};

// --- external objects ----------------------------------------------------------------------
struct cTutorialTarget {                       // object at +0x1c of an inventory item / creature
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
    virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
    virtual int  GetHighlightID(uint32_t effectID, int flag);   // slot 60 (+0xf0)
};

struct cTargetOwner {                          // returned by the tutorial target accessors
    uint32_t pad[7];
    cTutorialTarget* mpTarget;                 // +0x1c
};

struct cInventoryItem {
    cInventoryItem* GetItem(int index);        // 0x005cae30
    cInventoryItem* GetChild(int index);       // 0x005c2e50
    uint32_t pad[7];
    cTutorialTarget* mpTarget;                 // +0x1c
};

struct cSPPlayerInventoryOwner {
    cInventoryItem* GetPlayerInventory();      // 0x00a1ad60 SP::cSPSimulatorSpaceGame::GetPlayerInventory
};

struct cToolPanel {
    void SetSelected(uint32_t id);             // 0x00edcc70
    void SetVisible(int);                      // 0x00edcc90
    void SetMode(int);                         // 0x00edde30
};

struct cCategoryEntry { void Activate(); };    // 0x00ef7a00

struct cSimSubsystem {
    cCategoryEntry* GetEntry(int index);       // 0x00ed4b50
    cToolPanel* GetPanel();                    // 0x006c0200
    uint32_t pad[5];
    cSPPlayerInventoryOwner* mpSpaceGame;      // +0x14
};

struct cGameModeInfo { uint32_t pad[0x24]; int mMode; };  // +0x90

struct cSimulatorRoot {
    uint32_t pad0[5];
    cSimSubsystem* mpSub;                      // +0x14
    uint32_t pad1[0x18];
    cGameModeInfo* mpModeInfo;                 // +0x78
};

struct cPlayerState { bool IsActive(); };      // 0x00ac80f0
cPlayerState* GetPlayerState();                // 0x00b3d4d0

struct cAnimatedCreature {
    void SetEffect(uint32_t id, int flag);     // 0x00ecf910
    uint32_t pad[0x1e];
    char pad1;
    bool mbHighlighted;                        // +0x79
};
cAnimatedCreature* GetAnimatedCreature(cTargetOwner* p);  // 0x00ef73a0 (cdecl)

namespace SP {
    struct cGameTimeManager { void IncPauseGate(uint32_t id); };  // 0x00b32220
    cGameTimeManager* GameTimeManager();                           // 0x00b3d380
}

struct cHintData { void* mpVtbl; int mValue; };
struct cHintManager {
    void ShowHint(Vector3 pos, cHintData* data, int a, float offsetX, float offsetY, float offsetZ, int b, int c);  // 0x0067aaf0
};
cHintManager* GetHintManager();                // 0x0067caf0

extern cSimulatorRoot* g_pSimulatorRoot;      // 0x016c7aa4
extern bool g_bScenarioTutorialFlag;          // 0x016c7b50
extern cHintData g_TutorialHintData;          // 0x015ad260

extern Vector3 kPos_15acfc4, kPos_15acfd0, kPos_15acfdc, kPos_15acfe8, kPos_15acff4;
extern Vector3 kPos_15ad000, kPos_15ad00c, kPos_15ad018, kPos_15ad024, kPos_15ad030;
extern Vector3 kPos_15ad03c, kPos_15ad048, kPos_15ad054, kPos_15ad060, kPos_15ad06c;
extern Vector3 kPos_15ad078, kPos_15ad084, kPos_15ad090, kPos_15ad09c, kPos_15ad0a8;
extern Vector3 kPos_15ad0b4, kPos_15ad0c0, kPos_15ad0cc, kPos_15ad0d8, kPos_15ad0e4;
extern Vector3 kPos_15ad0f0, kPos_15ad0fc, kPos_15ad108, kPos_15ad120, kPos_15ad12c;
extern Vector3 kPos_15ad138, kPos_15ad144, kPos_15ad150, kPos_15ad15c, kPos_15ad168;
extern Vector3 kPos_15ad174, kPos_15ad180, kPos_15ad18c;

namespace Simulator {

class cScenarioTutorials {
public:
    void Update();                                                  // 0x00efa1b0
    void HandleCategoryMessage(int step, uint32_t messageID);       // 0x00efa110
    void SetCategoryState(int step, bool state);                    // 0x00efa0b0
    bool IsStepComplete(int step);                                  // 0x00ef8820
    void ShowStepHint(Vector3 pos, int step, cTutorialTarget* target, int highlightID);  // 0x00ef8390
    cTargetOwner* GetSelectedCreature();                            // 0x00ef7740
    cTargetOwner* GetCurrentVehicle();                              // 0x00ef7780
    cTargetOwner* GetCurrentCaptain();                              // 0x00ef77d0
    void SelectCategory(bool b);                                    // 0x00ef7810
    int  CountEntries();                                            // 0x00ef78c0
    bool IsInVehicle();                                             // 0x00ef84b0
    void Finish();                                                  // 0x00ef8860

    uint32_t pad0[12];
    int  mCategory;        // +0x30
    uint32_t pad1;
    bool mb38;             // +0x38
    bool mb39;             // +0x39
    bool mb3a;             // +0x3a
    char pad3b[3];
    bool mb3e;             // +0x3e
};

void cScenarioTutorials::Update()
{
    switch (mCategory) {
    case 0:
        if (!IsStepComplete(1)) {
            if (g_bScenarioTutorialFlag)
                ShowStepHint(kPos_15acff4, 1, 0, 0);
            else
                mb3e = true;
        } else if (!IsStepComplete(2)) {
            cSimSubsystem* sub = g_pSimulatorRoot->mpSub;
            if (sub)
                sub->GetEntry(0)->Activate();
            ShowStepHint(kPos_15ad000, 2, 0, 0);
        }
        break;
    case 1:
        if (!IsStepComplete(3)) {
            ShowStepHint(kPos_15ad00c, 3, 0, 0);
        } else if (!IsStepComplete(5)) {
            HandleCategoryMessage(4, 0xa9a5c32d);
        } else if (!IsStepComplete(7)) {
            HandleCategoryMessage(6, 0xe760e7ce);
        } else if (!IsStepComplete(8)) {
            ShowStepHint(kPos_15acfd0, 8, 0, 0);
        } else if (!IsStepComplete(10)) {
            SetCategoryState(9, false);
            mb39 = true;
        } else if (!IsStepComplete(0xb)) {
            ShowStepHint(kPos_15ad018, 0xb, 0, 0);
            mb38 = true;
            mb3a = true;
        } else if (!IsStepComplete(0xc)) {
            if (g_pSimulatorRoot->mpModeInfo->mMode == 3 && !GetPlayerState()->IsActive()) {
                ShowStepHint(kPos_15acfdc, 0xc, 0, 0);
            } else {
                mb3e = true;
                mb38 = true;
                mb3a = true;
            }
        } else if (!IsStepComplete(0xe)) {
            SetCategoryState(0xd, false);
            mb38 = true;
            mb3a = true;
        }
        break;
    case 3:
        if (!IsStepComplete(0x15)) {
            ShowStepHint(kPos_15ad024, 0x15, 0, 0);
        } else if (!IsStepComplete(0x17)) {
            SetCategoryState(0x16, false);
        } else if (!IsStepComplete(0x18)) {
            ShowStepHint(kPos_15ad030, 0x18, 0, 0);
        }
        break;
    case 2:
        if (!IsStepComplete(0x10)) {
            HandleCategoryMessage(0xf, 0x8cd7a9b1);
        } else if (!IsStepComplete(0x12)) {
            HandleCategoryMessage(0x11, 0xb3966da4);
        } else if (!IsStepComplete(0x14)) {
            HandleCategoryMessage(0x13, 0x1bfd23d0);
        }
        break;
    case 4:
        if (!IsStepComplete(0x19)) {
            ShowStepHint(kPos_15acfc4, 0x19, 0, 0);
        } else if (!IsStepComplete(0x1b)) {
            SetCategoryState(0x1a, false);
        } else if (!IsStepComplete(0x1c)) {
            cTutorialTarget* target = GetSelectedCreature()->mpTarget;
            ShowStepHint(kPos_15ad03c, 0x1c, target, target->GetHighlightID(0x73d54a0, 1));
        } else if (!IsStepComplete(0x1e)) {
            SetCategoryState(0x1d, false);
        } else if (!IsStepComplete(0x20)) {
            HandleCategoryMessage(0x1f, 0x45d1254d);
        } else if (!IsStepComplete(0x22)) {
            HandleCategoryMessage(0x21, 0x97c2f934);
        } else if (!IsStepComplete(0x24)) {
            HandleCategoryMessage(0x23, 0xb9a5b6f5);
        } else if (!IsStepComplete(0x25)) {
            ShowStepHint(kPos_15acfd0, 0x25, 0, 0);
        } else if (!IsStepComplete(0x27)) {
            SetCategoryState(0x26, false);
            mb39 = true;
        } else if (!IsStepComplete(0x28)) {
            if (g_pSimulatorRoot->mpModeInfo->mMode == 3 && !GetPlayerState()->IsActive()) {
                ShowStepHint(kPos_15acfdc, 0x28, 0, 0);
            } else {
                mb3e = true;
                mb38 = true;
                mb3a = true;
            }
        } else if (!IsStepComplete(0x2a)) {
            SetCategoryState(0x29, false);
            mb38 = true;
            mb3a = true;
        }
        break;
    case 5:
        if (!IsStepComplete(0x2b)) {
            ShowStepHint(kPos_15ad048, 0x2b, 0, 0);
        } else if (!IsStepComplete(0x2d)) {
            SetCategoryState(0x2c, false);
        } else if (!IsStepComplete(0x2e)) {
            cTutorialTarget* target = g_pSimulatorRoot->mpSub->mpSpaceGame->GetPlayerInventory()
                                          ->GetItem(2)->GetChild(0)->GetItem(0)->mpTarget;
            ShowStepHint(kPos_15ad054, 0x2e, target, target->GetHighlightID(0x73d54a0, 1));
        } else if (!IsStepComplete(0x30)) {
            SetCategoryState(0x2f, false);
        }
        break;
    case 9:
        if (!IsStepComplete(0x66)) {
            if (CountEntries() >= 3) {
                g_TutorialHintData.mValue = 0;
                GetHintManager()->ShowHint(kPos_15acfe8, &g_TutorialHintData, 0,
                                           -1.0f, -1.0f, 0.0f, 0, 0);
                Finish();
            } else {
                ShowStepHint(kPos_15ad0fc, 0x66, 0, 0);
            }
        } else if (!IsStepComplete(0x67)) {
            ShowStepHint(kPos_15ad108, 0x67, 0, 0);
        } else if (!IsStepComplete(0x69)) {
            cToolPanel* panel = g_pSimulatorRoot->mpSub->GetPanel();
            panel->SetSelected(0xe34e8a60);
            panel->SetVisible(1);
            g_pSimulatorRoot->mpSub->GetPanel()->SetMode(2);
            HandleCategoryMessage(0x68, 0xeca34363);
        } else if (!IsStepComplete(0x6b)) {
            g_pSimulatorRoot->mpSub->GetPanel()->SetMode(2);
            HandleCategoryMessage(0x6a, 0x7e3df1a7);
        } else if (!IsStepComplete(0x6d)) {
            SetCategoryState(0x6c, false);
        } else if (!IsStepComplete(0x6e)) {
            ShowStepHint(kPos_15acfd0, 0x6e, 0, 0);
        } else if (!IsStepComplete(0x70)) {
            SetCategoryState(0x6f, false);
            mb39 = true;
        } else if (!IsStepComplete(0x71)) {
            { SP::cGameTimeManager* gtm = SP::GameTimeManager(); gtm->IncPauseGate(0x4bf38a7); }
            ShowStepHint(kPos_15ad120, 0x71, 0, 0);
        } else if (!IsStepComplete(0x72)) {
            { SP::cGameTimeManager* gtm = SP::GameTimeManager(); gtm->IncPauseGate(0x4bf38a7); }
            ShowStepHint(kPos_15ad12c, 0x72, 0, 0);
        } else if (!IsStepComplete(0x73)) {
            { SP::cGameTimeManager* gtm = SP::GameTimeManager(); gtm->IncPauseGate(0x4bf38a7); }
            ShowStepHint(kPos_15ad138, 0x73, 0, 0);
        } else if (!IsStepComplete(0x74)) {
            { SP::cGameTimeManager* gtm = SP::GameTimeManager(); gtm->IncPauseGate(0x4bf38a7); }
            ShowStepHint(kPos_15ad144, 0x74, 0, 0);
            mb38 = true;
            mb3a = true;
        } else if (!IsStepComplete(0x75)) {
            if (g_pSimulatorRoot->mpModeInfo->mMode == 3 && !GetPlayerState()->IsActive()) {
                ShowStepHint(kPos_15acfdc, 0x75, 0, 0);
            } else {
                mb3e = true;
                mb38 = true;
                mb3a = true;
            }
        } else if (!IsStepComplete(0x77)) {
            SetCategoryState(0x76, false);
            mb38 = true;
            mb3a = true;
        }
        break;
    case 10:
        if (!IsStepComplete(0x78)) {
            if (CountEntries() >= 3) {
                g_TutorialHintData.mValue = 0;
                GetHintManager()->ShowHint(kPos_15acfe8, &g_TutorialHintData, 0,
                                           -1.0f, -1.0f, 0.0f, 0, 0);
                Finish();
            } else {
                ShowStepHint(kPos_15ad150, 0x78, 0, 0);
            }
        } else if (!IsStepComplete(0x7a)) {
            g_pSimulatorRoot->mpSub->GetPanel()->SetVisible(1);
            HandleCategoryMessage(0x79, 0x2792b320);
        } else if (!IsStepComplete(0x7c)) {
            g_pSimulatorRoot->mpSub->GetPanel()->SetMode(6);
            HandleCategoryMessage(0x7b, 0x240bb42d);
        } else if (!IsStepComplete(0x7d)) {
            ShowStepHint(kPos_15ad15c, 0x7d, 0, 0);
        } else if (!IsStepComplete(0x7f)) {
            HandleCategoryMessage(0x7e, 0x65f5aa45);
        }
        break;
    case 7:
        if (!IsStepComplete(0x3e)) {
            ShowStepHint(kPos_15ad078, 0x3e, 0, 0);
        } else if (!IsStepComplete(0x3f)) {
            ShowStepHint(kPos_15acfc4, 0x3f, 0, 0);
        } else if (!IsStepComplete(0x41)) {
            SetCategoryState(0x40, false);
        } else if (!IsStepComplete(0x42)) {
            SelectCategory(true);
            cTutorialTarget* target = GetCurrentVehicle()->mpTarget;
            ShowStepHint(kPos_15ad084, 0x42, target, target->GetHighlightID(0x73d54a0, 1));
        } else if (!IsStepComplete(0x44)) {
            SetCategoryState(0x43, false);
        } else if (!IsStepComplete(0x45)) {
            if (IsInVehicle())
                SelectCategory(false);
            cAnimatedCreature* creature = GetAnimatedCreature(GetCurrentVehicle());
            creature->SetEffect(0x7464588, 1);
            creature->mbHighlighted = true;
            ShowStepHint(kPos_15ad090, 0x45, 0, 0);
        } else if (!IsStepComplete(0x47)) {
            SetCategoryState(0x46, false);
        } else if (!IsStepComplete(0x48)) {
            ShowStepHint(kPos_15ad09c, 0x48, 0, 0);
        } else if (!IsStepComplete(0x4a)) {
            HandleCategoryMessage(0x49, 0xca6b8824);
        } else if (!IsStepComplete(0x4b)) {
            ShowStepHint(kPos_15ad0a8, 0x4b, 0, 0);
        } else if (!IsStepComplete(0x4d)) {
            HandleCategoryMessage(0x4c, 0x712afe6e);
        } else if (!IsStepComplete(0x4e)) {
            ShowStepHint(kPos_15ad0b4, 0x4e, 0, 0);
        } else if (!IsStepComplete(0x50)) {
            HandleCategoryMessage(0x4f, 0xa7d93ee1);
        } else if (!IsStepComplete(0x51)) {
            ShowStepHint(kPos_15ad0c0, 0x51, 0, 0);
        } else if (!IsStepComplete(0x53)) {
            HandleCategoryMessage(0x52, 0x4a7282dc);
        } else if (!IsStepComplete(0x54)) {
            HandleCategoryMessage(0x54, 0xf9e6bb2f);
        }
        break;
    case 11:
        if (!IsStepComplete(0x80)) {
            ShowStepHint(kPos_15ad168, 0x80, 0, 0);
        } else if (!IsStepComplete(0x82)) {
            SetCategoryState(0x81, false);
            ShowStepHint(kPos_15ad174, 0, 0, 0);
        } else if (!IsStepComplete(0x84)) {
            SetCategoryState(0x83, false);
            ShowStepHint(kPos_15ad180, 0, 0, 0);
        } else if (!IsStepComplete(0x86)) {
            SetCategoryState(0x85, false);
            ShowStepHint(kPos_15ad18c, 0x86, 0, 0);
        }
        break;
    case 6:
        if (!IsStepComplete(0x31)) {
            ShowStepHint(kPos_15ad060, 0x31, 0, 0);
        } else if (!IsStepComplete(0x33)) {
            SetCategoryState(0x32, false);
        } else if (!IsStepComplete(0x34)) {
            cTutorialTarget* target = g_pSimulatorRoot->mpSub->mpSpaceGame->GetPlayerInventory()
                                          ->GetItem(5)->GetChild(0)->GetItem(0)->mpTarget;
            ShowStepHint(kPos_15ad06c, 0x34, target, target->GetHighlightID(0x73d54a0, 1));
        } else if (!IsStepComplete(0x36)) {
            SetCategoryState(0x35, false);
        } else if (!IsStepComplete(0x38)) {
            HandleCategoryMessage(0x37, 0x486ee24d);
        } else if (!IsStepComplete(0x3a)) {
            HandleCategoryMessage(0x39, 0x87d79e47);
        } else if (!IsStepComplete(0x3c)) {
            HandleCategoryMessage(0x3b, 0x53dab6ed);
        } else if (!IsStepComplete(0x3d)) {
            SetCategoryState(0x3d, false);
        }
        break;
    case 8:
        if (!IsStepComplete(0x55)) {
            ShowStepHint(kPos_15ad0cc, 0x55, 0, 0);
        } else if (!IsStepComplete(0x57)) {
            SetCategoryState(0x56, false);
        } else if (!IsStepComplete(0x58)) {
            cTutorialTarget* target = g_pSimulatorRoot->mpSub->mpSpaceGame->GetPlayerInventory()
                                          ->GetItem(1)->GetChild(0)->GetItem(0)->mpTarget;
            ShowStepHint(kPos_15ad0d8, 0x58, target, target->GetHighlightID(0x73d54a0, 1));
        } else if (!IsStepComplete(0x5a)) {
            SetCategoryState(0x59, false);
        } else if (!IsStepComplete(0x5b)) {
            cAnimatedCreature* creature = GetAnimatedCreature(GetCurrentCaptain());
            creature->SetEffect(0x7464588, 1);
            creature->mbHighlighted = true;
            ShowStepHint(kPos_15ad0e4, 0x5b, 0, 0);
        } else if (!IsStepComplete(0x5d)) {
            HandleCategoryMessage(0x5c, 0x2863b952);
        } else if (!IsStepComplete(0x5e)) {
            ShowStepHint(kPos_15ad0f0, 0x5e, 0, 0);
        } else if (!IsStepComplete(0x60)) {
            SetCategoryState(0x5f, false);
        } else if (!IsStepComplete(0x62)) {
            HandleCategoryMessage(0x61, 0xe3b1f1d1);
        } else if (!IsStepComplete(0x64)) {
            HandleCategoryMessage(0x63, 0x53106d77);
        } else if (!IsStepComplete(0x65)) {
            HandleCategoryMessage(0x65, 0xb3b61e49);
        }
        break;
    }
}

}  // namespace Simulator
