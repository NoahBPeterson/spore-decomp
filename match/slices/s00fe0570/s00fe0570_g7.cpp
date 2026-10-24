// Slice s00fe0570 (gold7): cAppModeSpace transitions (solar->planet complete, and the
// unnamed planet->solar-ish teardown at 0x00fe0e10).
// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

void operator delete[](void* p);                              // 0x00f47380

namespace eastl {
struct ListNodeBase {
    ListNodeBase* mpNext;
    ListNodeBase* mpPrev;
};
template <typename T>
struct ListNode : public ListNodeBase {
    T mValue;
};
template <typename T>
class list { public:
    typedef ListNode<T> node_type;
    ListNodeBase mNode;
    uint32_t mAllocator;

    void clear()
    {
        node_type* pNode = (node_type*)mNode.mpNext;
        while (pNode != (node_type*)&mNode) {
            node_type* pCur = pNode;
            pNode = (node_type*)pNode->mpNext;
            operator delete[](pCur);
        }
        mNode.mpNext = &mNode;
        mNode.mpPrev = &mNode;
    }
};
}  // namespace eastl

// ---------------------------------------------------------------- message plumbing
extern void* g_slotMsgVtbl0;                                  // 0x013eb90c
extern void* g_slotMsgVtbl1;                                  // 0x013eb844
struct SlotMessage {
    void* vptr;           // +0x00
    long mRef;            // +0x04
    uint32_t pad08[2];
    uint32_t mTarget;     // +0x10
    uint32_t pad14[7];
    uint32_t mData30;     // +0x30
    uint32_t pad34;
    uint32_t mData38;     // +0x38
    uint32_t pad3c;

    SlotMessage()
    {
        mData30 = 0;
        vptr = &g_slotMsgVtbl0;
        _InterlockedExchange(&mRef, 0);
        vptr = &g_slotMsgVtbl1;
        mData38 = 0;
    }
    void Destruct();                                          // 0x00421cf0
    ~SlotMessage() { Destruct(); }
};
struct IMessageServer {
    PV4 PV
    virtual void Post(uint32_t id, SlotMessage* msg, int flag);  // +0x14
    virtual void PostEx(uint32_t id, int a, int b, int c);       // +0x18
};
IMessageServer* MessageServer();                              // 0x0067dcc0

// ---------------------------------------------------------------- singletons / helpers
struct cGameTimeManager {
    void DecPauseGate(uint32_t id);                           // 0x00b32250
};
cGameTimeManager* GameTimeManager();                          // 0x00b3d380

struct cSolarView {
    void Hide();                                              // 0x00801380
};
cSolarView* FUN_0067cab0();                                   // 0x0067cab0

struct cGameInputManager {
    uint32_t pad00[0x110 / 4];
    int mField110;                                            // +0x110
};
cGameInputManager* GameInputManager();                        // 0x00b3d250

struct IInputManager {
    PV8 PV8 PV4 PV2 PV
    virtual void IsControlActive(int control, int flag);      // +0x5c
};
IInputManager* InputManager();                                // 0x0067dd50

struct cPropertyList {
    int GetIntProperty(uint32_t id);                          // 0x006a2660
    bool GetDescription(uint32_t id);                         // 0x006a25a0
};
extern cPropertyList* sAppProperties;                         // 0x015fd918

struct cSPUISpace {
    void ShowBakeTimeSplash();                                // 0x01065af0
};

struct cStar;
cStar* FUN_01021230();                                        // 0x01021230

struct cSPSimulatorSpaceGame {
    uint32_t pad00[0x14 / 4];
    cSPUISpace* mpUI;                                         // +0x14
    uint32_t pad18[(0x40 - 0x18) / 4];
    void* mpField40;                                          // +0x40
    uint32_t pad44[(0x50 - 0x44) / 4];
    uint32_t mFlags;                                          // +0x50

    void DestroyNPC_UFOs(char a, char b, int c);              // 0x01009470
    void FUN_010039c0(cStar* star);                           // 0x010039c0
    void StepC();                                             // 0x01003690
    void ChaseFromSolarToPlanet();                            // 0x01007bf0
};

struct cSPSimulatorPlayerUFO {
    void InitForPlanet();                                     // 0x00ffd390
};
cSPSimulatorPlayerUFO* GetUFOSimulator();                     // 0x00ffbe50

struct cPlanet;
cPlanet* GetActivePlanet();                                   // 0x01021260

struct cTerrainSphere {
    void FUN_00c77bf0(uint32_t flag);                         // 0x00c77bf0
};
struct cGameNounManager {
    cTerrainSphere* GetCurrentTerrainSphere();                // [this+0x74]
    void ProcessPending();                                    // 0x00b22960
};
cGameNounManager* NounManager();                              // 0x00b3d300

void FUN_010213b0(int a);                                     // 0x010213b0

struct cPlanetModel {
    uint32_t pad00[0x24 / 4];
    uint32_t mField24;                                        // +0x24
    void FUN_00b8d750(int value);                             // 0x00b8d750
    int GetPlanetKey();                                       // 0x00b7e380
    void Refresh();                                           // 0x00b88420
};
cPlanetModel* PlanetModel();                                  // 0x00b3d350

struct cPlanet {
    int FUN_00c713e0(int flag);                               // 0x00c713e0
    void FUN_00c713c0(int key);                               // 0x00c713c0
};

struct cThingB3D360 {
    void FUN_00b7dec0();                                      // 0x00b7dec0
};
cThingB3D360* FUN_00b3d360();                                 // 0x00b3d360

struct cThingB3D310 {
    void FUN_00b515e0();                                      // 0x00b515e0
};
cThingB3D310* FUN_00b3d310();                                 // 0x00b3d310

// ---------------------------------------------------------------------- app mode
class cAppModeSpace {
public:
    uint32_t pad000[0x15c / 4];
    cSPSimulatorSpaceGame* mpSimulatorSpaceGame;              // +0x15c
    uint32_t pad160;
    uint32_t mElapsedBakeTimeForTransitionMS;                 // +0x164
    uint8_t pad168;
    bool mbBakeStarted;                                       // +0x169
    bool mBakingForPlanetEntryEnded;                          // +0x16a
    uint8_t pad16b;
    uint32_t mCommContext;                                    // +0x16c
    uint8_t pad170[0x17c - 0x170];
    eastl::list<bool> mInputFlags;                            // +0x17c

    void SetPlanetTimeOnFirstEntry();                         // 0x00fda530
    void FUN_00fdf9f0();                                      // 0x00fdf9f0

    void CompleteTransitionFromSolarToPlanet();
    void FUN_00fe0e10();
};

// @ 0x00fe0c60
void cAppModeSpace::CompleteTransitionFromSolarToPlanet()
{
    cGameTimeManager* timeMgr = GameTimeManager();
    timeMgr->DecPauseGate(0x4bf38a7);
    FUN_0067cab0()->Hide();
    cGameInputManager* input = GameInputManager();
    input->mField110--;

    if (mbBakeStarted) {
        eastl::list<bool>::node_type* it = (eastl::list<bool>::node_type*)mInputFlags.mNode.mpNext;
        for (int i = 0; i <= 0x1b; ++i) {
            if (it->mValue)
                InputManager()->IsControlActive(i, 1);
            it = (eastl::list<bool>::node_type*)it->mpNext;
        }
        mInputFlags.clear();
        mbBakeStarted = false;
    }

    if (sAppProperties->GetDescription(0x7ae23adf)) {
        if (mpSimulatorSpaceGame->mpUI)
            mpSimulatorSpaceGame->mpUI->ShowBakeTimeSplash();
    }

    mpSimulatorSpaceGame->DestroyNPC_UFOs(1, 1, 0);
    cSPSimulatorSpaceGame* sim = mpSimulatorSpaceGame;
    sim->FUN_010039c0(FUN_01021230());
    mpSimulatorSpaceGame->StepC();
    GetUFOSimulator()->InitForPlanet();
    SetPlanetTimeOnFirstEntry();
    FUN_00fdf9f0();
    mpSimulatorSpaceGame->ChaseFromSolarToPlanet();
    if (cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere())
        sphere->FUN_00c77bf0(0x574ac67);
    mpSimulatorSpaceGame->mFlags &= ~2u;

    SlotMessage msg;
    msg.mTarget = (uint32_t)GetActivePlanet();
    NounManager()->ProcessPending();
    MessageServer()->Post(0x248975f, &msg, 0);
    MessageServer()->PostEx(0x5e37a53, 0, 0, 0);
}

// @ 0x00fe0e10
void cAppModeSpace::FUN_00fe0e10()
{
    FUN_00b3d360()->FUN_00b7dec0();
    cPlanet* planet = GetActivePlanet();
    FUN_01021230();
    cPlanetModel* model = PlanetModel();
    if (model->mField24 == 0)
        model->FUN_00b8d750(planet->FUN_00c713e0(1));
    else
        planet->FUN_00c713c0(model->GetPlanetKey());
    FUN_00b3d310()->FUN_00b515e0();
    model->Refresh();
    GetUFOSimulator()->InitForPlanet();
    MessageServer()->Post(0x279a5da, 0, 0);
    mpSimulatorSpaceGame->StepC();

    SlotMessage msg;
    msg.mTarget = (uint32_t)GetActivePlanet();
    FUN_00fdf9f0();
    FUN_010213b0(-1);
    NounManager()->ProcessPending();
    MessageServer()->Post(0x248975f, &msg, 0);
    MessageServer()->PostEx(0x5e37a53, 0, 0, 0);
}
