// Slice s00cd6800 -- SP::cTribeModeStrategy stage/state transition helper.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

// ---------------------------------------------------------------------------------------------
// Support types
// ---------------------------------------------------------------------------------------------
struct cSPTimer {
    void Restart();                         // 0x00bc3130
};

struct cGameTimeManager {
    void DecPauseGate(u32 id);              // 0x00b32250
};

struct cGameInputManager {
    u8  mPad000[0x110];
    int mField110;                          // 0x110
};

struct cCameraCtl {
    u8   mPad000[0x390];
    bool mFlag390;                          // 0x390
};

struct cConfigManager {
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08();
    virtual void v09(); virtual void v10();
    virtual void SetConfigU32(u32 id, char value);  // +0x2c
    virtual u32  GetConfigU32(u32 id);              // +0x30
};

struct cUIHints {
    void UpdateHints(u32 id);               // 0x0067c830
};

struct cUIWindow {
    void FUN_00e2f270();                    // 0x00e2f270
};

struct cModeObject {
    u8       mPad000[4];                    // 0x00 vtable
    void F_cd6390(unsigned char enable);    // 0x00cd6390
    u8       mPad004[0x1a8 - 4];
    cSPTimer mTimer;                        // 0x1a8
};

extern "C" cGameTimeManager*   GameTimeManager();          // 0x00b3d380
extern "C" cGameInputManager*  GameInputManager();         // 0x00b3d250
extern "C" cCameraCtl*         GetCameraCtl();             // 0x00b3d280
extern "C" cConfigManager*     ConfigManager();            // 0x0067dd30
extern "C" cUIHints*           FUN_0067cac0();             // 0x0067cac0
extern "C" cUIWindow* __stdcall FUN_00b3d4f0(int flag);    // 0x00b3d4f0
extern "C" cModeObject*        DAT_0169b2c8;               // 0x0169b2c8

// ---------------------------------------------------------------------------------------------
// SP::cTribeModeStrategy
// ---------------------------------------------------------------------------------------------
struct cTribeModeStrategy {
    u8       mPad000[4];                    // 0x00 vtable
    int      mState4;                       // 0x04

    void FUN_00cd6800();
};

// @ 0x00cd6800
void cTribeModeStrategy::FUN_00cd6800()
{
    cGameTimeManager* time = GameTimeManager();
    time->DecPauseGate(0x4bf38a7u);

    switch (mState4) {
    case 1:
        if (ConfigManager()->GetConfigU32(0x4ea96cbu) != 0) {
            if (ConfigManager()->GetConfigU32(0x5b5bb5eu) != 0) {
                DAT_0169b2c8->F_cd6390(1);
                FUN_00b3d4f0(1)->FUN_00e2f270();
                cGameInputManager* input = GameInputManager();
                input->mField110++;
                if (GetCameraCtl() != 0)
                    GetCameraCtl()->mFlag390 = true;
                DAT_0169b2c8->mTimer.Restart();
            }
        }
        break;
    case 2:
        if (ConfigManager()->GetConfigU32(0x5b5bb5eu) != 0)
            FUN_0067cac0()->UpdateHints(0x508fccb5u);
        break;
    }
}
