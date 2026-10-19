// src/game/SPEditors/SPSubModeDance.cpp -- migrated from slice(s) s0063aa90 by tools/migrate/rewrite.py
// Object file: SPEditors/SPSubModeDance.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPlayModeSubModeDance.h"
#include "EA/Stopwatch.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cSPPlayMode.h"
#include "SP/cSPPlayModeSubModeAction.h"
#include "SP/cSPPlayModeSubModeBase.h"
#include "SP/cSPPlayModeSubModeMovie.h"
#include "SP/cSPPlayModeUI.h"
#include "cSPUILayout.h"
#include "SP/cString.h"

// ---- items of slice s0063aa90 begin (TODO(rewrite): local stubs, replace by canonical classes)
void KillSetiEffects(uint32_t id, int v);                               // 0x00435ED0 (cdecl)
struct cAudioSys { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual int GetState(); };    // +0x20
cAudioSys* GetSystemAT();                                               // 0x00A206F0
class cEditorMode2 {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual char* GetSaveInfo();   // +0x40
    void SaveModel(char* p, bool b);                                    // 0x0057F6C0
    void FUN_00574110(uint32_t id, int a, float b, float c);            // 0x00574110
    void OnLayout(int a, int b);                                        // 0x00B267F0
};
class cPlayModeUI2 { public: void SetEnabled(uint32_t id, bool b); };   // 0x00634EF0
class cSPPlayMode {
public:
    void WakeupCreature();                                              // 0x0062A760
    void FUN_00628810();                                                // 0x00628810
    void SetAllBabySitUp();                                             // 0x00629220
    char pad0[0xc]; cPlayModeUI2* mpUI;                                 // +0xc
    char pad1[0x1d - 0x10]; uint8_t mB1d, mB1e;                         // +0x1d, +0x1e
    char pad2[0x28 - 0x1f]; float mF28, mF2c, mF30;                     // +0x28..
};
class cSPPlayModeAnimation2 {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual float PlayAnimation(uint32_t creatureID, uint32_t animID, int a, int b, void* c);  // +0xc
};
class cSPPlayModeSubModeBase {
public:
    virtual void v0();
    void Init(void* params);                                            // 0x0063B270 (called out of line from other TUs; body below as InitCopy)
    void InitCopy(void* params);
    cEditorMode2* mEditorBaseMode;                                      // +0x4
    cSPPlayModeAnimation2* mAnim;                                       // +0x8
    void* mSubModeParams;                                               // +0xc
    cSPPlayMode* mPlayMode;                                             // +0x10
};
#define KILL_SETI_AT() { cAudioSys* at = GetSystemAT(); KillSetiEffects(0xa03e74b2, at ? at->GetState() : 0); }
class cSPPlayModeSubModeDance : public cSPPlayModeSubModeBase {
public:
    cSPPlayModeSubModeDance();
    void Init(void* params);
    bool IsDancingAnim(uint32_t animID, bool baby);
    bool HandleButton(uint32_t id);

    char pad14[0x28 - 0x14];
    uint32_t mField28;                                                  // +0x28
    uint32_t mDanceMovesGUID[6];                                        // +0x2c
    uint32_t mBabyDanceMovesGUID[6];                                    // +0x44
    uint8_t mField5c;                                                   // +0x5c (inside event array slot)
    char pad5d[3];
    uint32_t mDanceEventIDs[6];                                         // +0x60
};
#define DANCE_CASE(ID, N) \
    case ID: KILL_SETI_AT(); guid = mDanceMovesGUID[N]; evt = mDanceEventIDs[N]; idx = N; break;
// ---- items of slice s0063aa90 end

// @ 0x0063b290
void cSPPlayModeSubModeDance::Init(void* params)
{
    cSPPlayModeSubModeBase::Init(params);
    mDanceMovesGUID[0] = 0x3fbce75;
    mDanceMovesGUID[1] = 0x3fbce97;
    mDanceMovesGUID[2] = 0x3fbcea4;
    mDanceMovesGUID[3] = 0x3fbceb5;
    mDanceMovesGUID[4] = 0x4114b22;
    mDanceMovesGUID[5] = 0x4114b5e;
    mBabyDanceMovesGUID[0] = 0x44f475b;
    mBabyDanceMovesGUID[1] = 0x44f4767;
    mBabyDanceMovesGUID[2] = 0x44f476c;
    mBabyDanceMovesGUID[3] = 0x44f4771;
    mBabyDanceMovesGUID[4] = 0x44f4776;
    mBabyDanceMovesGUID[5] = 0x44f477a;
    mDanceEventIDs[0] = 0xe5025cd9;
    mDanceEventIDs[1] = 0xed65cbf6;
    mDanceEventIDs[2] = 0xe12a2ae7;
    mDanceEventIDs[3] = 0xbd989484;
    mDanceEventIDs[4] = 0x6df196fd;
    mDanceEventIDs[5] = 0x3088ceca;
    mField28 = 0;
    mAnim = *(cSPPlayModeAnimation2**)((char*)params + 0x20);
    mField5c = 0;
}

// @ 0x0063b330
bool cSPPlayModeSubModeDance::HandleButton(uint32_t id)
{
    uint32_t guid, evt;
    int idx;
    switch (id) {
    DANCE_CASE(0x3e830f4, 0)
    DANCE_CASE(0x3e830fc, 1)
    DANCE_CASE(0x3e83104, 2)
    DANCE_CASE(0x3e8313c, 3)
    DANCE_CASE(0x3e83154, 4)
    DANCE_CASE(0x3e83170, 5)
    default:
        return true;
    }
    mEditorBaseMode->OnLayout(1, idx);
    if (guid != (uint32_t)-1) {
        mPlayMode->WakeupCreature();
        mPlayMode->FUN_00628810();
        mAnim->PlayAnimation(*(uint32_t*)((char*)mEditorBaseMode + 0x364), guid, 1, 1, 0);
        if (evt != (uint32_t)-1)
            mEditorBaseMode->FUN_00574110(evt, -1, 1.0f, 0.0f);
    }
    return true;
}

// @ 0x0063b570
bool cSPPlayModeSubModeDance::IsDancingAnim(uint32_t animID, bool baby)
{
    const uint32_t* arr;
    if (baby) arr = mBabyDanceMovesGUID;
    else arr = mDanceMovesGUID;
    uint32_t i = 0;
    do {
        if (animID == arr[i]) return true;
        i++;
    } while (i < 6);
    return false;
}
