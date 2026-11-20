// @ 0x0106c930
// s0106c930 - SP::cSPUISpace: resolve the local cursor id (badge / star-record key)
// and make the cursor manager select it when it differs from the current cursor.
#include "types.h"

// ---------------------------------------------------------------------------
// generic vtable access (engine virtual slots 0x24 / 0x38 / 0x3c)
// ---------------------------------------------------------------------------
struct Vtbl { void* mSlots[0x120 / 4]; };

typedef void  (__thiscall *VFn_vp)(void*, void*);
typedef char  (__thiscall *VFn_cpp)(void*, void*, void*, int);
typedef int*  (__thiscall *VFn_pvp)(void*, void*);

// out buffer of the tool virtual slots (0x3c, 0x24, 0x38); the original frame
// holds two of these 12-byte key records, the first one shared by 0x3c / 0x24
struct ToolKeyOut { uint32_t mHash; uint32_t mPad0; uint32_t mPad1; };

#define VSLOT(o, n) (((Vtbl*)*(void**)(o))->mSlots[(n) / 4])

// ---------------------------------------------------------------------------
// engine entry points
// ---------------------------------------------------------------------------
struct InputMgr {
    char IsActiveMode();                 // 0x00fd9d00  input manager mode test
};
InputMgr* FUN_00fd9c60();                // 0x00fd9c60  InputManager::Get

struct EffectsMgr {
    char FUN_00b5ca60();                 // 0x00b5ca60
};
EffectsMgr* FUN_00b3d230();              // 0x00b3d230  SP::EffectsManager

int  FUN_01021080();                     // 0x01021080  SP::cSPLivingUniverse::GetUniverseContext

struct SimCheck {
    char FUN_00d09660();                 // 0x00d09660
};
struct SpaceGame {
    uint8_t   mPad00[0x20];
    SimCheck* mSimCheck;                 // +0x20
};
SpaceGame* FUN_01002bd0();               // 0x01002bd0  SP::SpaceGameGet

// the object stored at cSPUISpace+0x238 keeps the shown and the "other" tool
struct cSpaceTool;
struct cSpaceToolView {
    cSpaceTool* GetShownTool();          // 0x00ff3f00  currently shown item
    cSpaceTool* GetOtherTool();          // 0x00ff3f10
};

struct cToolStrategy;                    // virtual slots 0x24 / 0x3c

struct cSpaceTool {
    cToolStrategy* GetStrategy();        // 0x0104f930  dispatch the tool strategy
    char FUN_0104ff10();                 // 0x0104ff10
    char FUN_0104bd50();                 // 0x0104bd50
};

// star-record path: the simulator player object and the record under the mouse
struct cStar;
struct cSPSimulatorPlayerUFO {
    cStar* GetStarRecordUnderMouse();    // 0x00fff8e0
};
cSPSimulatorPlayerUFO* FUN_00ffbe50();   // 0x00ffbe50  SP::GetUFOSimulator

struct cEmpire {
    uint8_t  mPad00[0x84];
    uint32_t mEmpireKey;                 // +0x84
};
struct cStarManager {
    cEmpire* GetEmpireByID(uint32_t avatarID);   // 0x00ba9370 (ret 4)
};
cStarManager* FUN_00b3d2a0();            // 0x00b3d2a0  SP::StarManager

struct cStar {
    uint8_t  mPad00[0x70];
    uint32_t mKey;                       // +0x70
    int  GetState();                     // 0x00bb9ae0
    uint32_t GetAvatar();                // 0x00b1fdb0
};

struct cCommMgr {
    char Has();                           // 0x00ae9c10
};
cCommMgr* __stdcall FUN_00b3d4a0(uint32_t empireKey, uint32_t starKey); // 0x00b3d4a0 SP::CommManager

// cursor manager
struct CurMgr {
    uint32_t GetCursor();                // 0x008013c0
    char     FindLocal(uint32_t id);     // 0x00801bb0
};
CurMgr* FUN_0067cab0();                  // 0x0067cab0  GetCurMgr

// ---------------------------------------------------------------------------
// the UI space object
// ---------------------------------------------------------------------------
struct cSPUISpace {
    uint8_t          mPad000[0x238];
    cSpaceToolView*  mToolView;          // +0x238

    int  FUN_0106b9b0(int key, int index);   // 0x0106b9b0 badge-table lookup
    void FUN_0106c930();                     // 0x0106c930
};

// @ 0x0106c930
void cSPUISpace::FUN_0106c930()
{
    if (FUN_00fd9c60()->IsActiveMode())
        return;

    int id = 0x1002;

    if (!FUN_00b3d230()->FUN_00b5ca60()) {
        cSpaceTool* tool = this->mToolView->GetShownTool();

        if (tool != 0 && FUN_01021080() == 0) {
            // the engine looks the sim-check slot up by reference, so the
            // original keeps the address of the +0x20 member as well as its value
            SimCheck*& simCheck = FUN_01002bd0()->mSimCheck;

            if (!simCheck->FUN_00d09660()) {
            ToolKeyOut scratch;
            ToolKeyOut keyOut;

            cToolStrategy* strategy = tool->GetStrategy();

            ((VFn_vp)VSLOT(strategy, 0x3c))(strategy, &scratch);

            cSpaceTool* other = this->mToolView->GetOtherTool();

            if (tool->FUN_0104ff10()) {
                id = 3;
            } else if (tool->FUN_0104bd50()) {
                id = 2;
            } else {
                id = !((VFn_cpp)VSLOT(strategy, 0x24))(strategy, tool, &scratch, 0);
            }

            int* key;
            if (other != 0)
                key = ((VFn_pvp)VSLOT(other, 0x38))(other, &keyOut);
            else
                key = ((VFn_pvp)VSLOT(tool, 0x38))(tool, &keyOut);

            id = this->FUN_0106b9b0(*key, id);
            }
        }

        if (FUN_01021080() == 2) {
            cStar* star = FUN_00ffbe50()->GetStarRecordUnderMouse();
            if (star != 0 && star->GetState() == 5) {
                uint32_t avatar = star->GetAvatar();
                cEmpire* empire = FUN_00b3d2a0()->GetEmpireByID(avatar);
                uint32_t starKey = star->mKey;
                uint32_t empireKey = empire->mEmpireKey;
                if (FUN_00b3d4a0(empireKey, starKey)->Has())
                    id = 0x057f997d;
            }
        }
    }

    CurMgr* mgr = FUN_0067cab0();
    if (mgr->GetCursor() != (uint32_t)id)
        mgr->FindLocal((uint32_t)id);
}
