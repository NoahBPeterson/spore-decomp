// SP::cCreatureModeStrategy::ContinueLoading  @ 0x00d43e30
//
// PARTIAL reconstruction. ~5880-byte __thiscall state machine (/O2 /MD /Gy /EHsc /TP).
// The loading-state switch (0..0xb) and its guard structure are reproduced as an
// outline; the per-state bodies (in particular case 0, ~770 decompiled lines of
// terrain/creature/mission loading) are summarised, not byte-faithful.
//
//   void __thiscall ContinueLoading(cCreatureModeStrategy* this, IHandlerRC* handler)

#pragma once

namespace SP { struct cCreatureModeStrategy; }
struct IHandlerRC;

// --- generic game objects touched by the loader (masked/opaque here) ---
struct cSPCreatureBase;
struct cGameNounManager;
struct cCreatureModeInputStrategy;
struct cSPCreatureMissionManager;
struct cPlanetModel;
struct cTerrainEditor;
struct Controller;
struct cPropertyList;
struct cCreatureModeScenario;
struct EditorResultData;

template <class T> struct AutoRefCount { T* mpObject; };

// Loading state: disassembly shows mState at +0xa4 and mPreviousMode at +0xa0.
struct ModeLoadingState
{
    unsigned char pad_000[0xa0];
    unsigned char mPreviousMode;   // +0xa0
    unsigned char pad_0a1[3];
    int           mState;          // +0xa4
};

namespace SP
{
struct cCreatureModeStrategy
{
    unsigned char  pad_000[0xa0];
    ModeLoadingState mLoadingState;   // +0xa0
    unsigned char  pad_0a8[0x200];
    void ContinueLoading(::IHandlerRC* handler);
};
}

// --- callees (masked relocations; cdecl unless noted) ---
extern "C" int  SP_GetCurrentGameMode();
extern "C" cTerrainEditor* SP_NounManager(int id);
extern "C" void* SP_PropertyManager();
extern "C" void* SP_SporeGuide();
extern "C" int  FUN_00d43e30_get();       // helper used by the initial guard
extern "C" void FUN_00d45000(void*);      // placeholder for the state body calls

// @ 0x00d43e30
void SP::cCreatureModeStrategy::ContinueLoading(IHandlerRC* handler)
{
    int      prevMode = this->mLoadingState.mPreviousMode;
    int      state    = this->mLoadingState.mState;
    (void)handler;
    (void)prevMode;

    switch (state)
    {
    case 0:
        // Bulk of the function: waits for the currently loading resource group
        // (terrain sphere, creature assets, mission data) and advances
        // mLoadingState.mState through the loading steps.  Reads this->+0xa0/+0xa4,
        // calls the game-noun / property managers, spins up a
        // cCreatureModeInputStrategy, and on completion hands off to the
        // creature-mission manager.  (Not reproduced.)
        FUN_00d45000(this);
        break;

    case 1:  // validate / finalise creature asset
    case 2:  // build input strategy
    case 3:  // load scenario / properties
    case 4:
    case 5:  // mission manager wiring
    case 6:  // terrain / planet model hooks
    case 7:
    case 8:  // editor result data handoff
    case 9:
    case 10:
    case 0xb: // done
        FUN_00d45000(this);
        break;

    default:
        break;
    }
}
