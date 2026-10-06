// @ 0x00d35190  SP::cCreatureModeInputStrategy::HandleMessage   (real name, PDB anchor)
//
// PARTIAL.  The retail function (5422 B) is a large message dispatcher: it tests
// `msg` against ~22 hashed message ids and, for each, runs a handler (some via
// the GameInputManager vtable, some via cCreatureModeStrategy::Instance(), some
// via cUIBanningContent, etc.).  The class layout is the dev-PDB layout.
//
// The dispatcher shape and the branches that were decoded are reproduced; the
// remaining branch bodies are marked TODO.

#include "types.h"

namespace SP {
struct cMWModel;
struct cGonzagoTimer;
struct cSpatialObject;
struct cGameData;
}
namespace EA { template<class T> struct AutoRefCount { void* mpObject; }; }

namespace SP {
class cCreatureModeInputStrategy {
public:
    char pad0[0x54];
    bool mbEnabled;                 // +0x54
    bool mbAutoRun;                 // +0x55
    bool mbLastAutoRun;             // +0x56
    char pad1[0x2];
    char mCreatureHitBoxes[0x10];   // +0x58
    char mClickTimerMap[0x1c];      // +0x68
    char mAutoHandler[0x14];        // +0x84
    char mMouseDownTime[0x20];      // +0x98
    bool mbUpdateAvatarGoals;       // +0xb8
    bool mbAllowWASDGoals;          // +0xb9
    char pad2[0x2];
    EA::AutoRefCount<cSpatialObject> mpHeldObject;   // +0xbc
    char mHeldObjectLastPosition[0xc];               // +0xc0
    char mHeldObjectMouseVelocity[0xc];              // +0xcc
    EA::AutoRefCount<int> mpMovementGoalEffect;      // +0xd8
    char mAvatarGoal[0xc];                           // +0xdc
    EA::AutoRefCount<int> mpRolloverEffect;          // +0xe8
    EA::AutoRefCount<cGameData> mpLastRolledOverData;// +0xec
    unsigned mLastCursor;                            // +0xf0
    float mRolloverUpdateTimer;                      // +0xf4
public:
    unsigned __thiscall HandleMessage(unsigned msg, int* data);
};
} // namespace SP

extern "C" {
    void* GameInputManager();
    void  cCreatureModeStrategy_Instance();
    void  cUIBanningContent_EndBanMode();
    void  FUN_00d2eb70();
    void  FUN_00b3d4d0();
    void  FUN_00ad7dc0();
    void  FUN_00d2c200();
    void  FUN_00b3d410();
    void  FUN_00e3e350();
    void  FUN_00b3d320();
    void  FUN_00b1e410();
    void  FUN_00bc3170();
    unsigned FUN_00bd6a60(...);
    void  FUN_00d539d0(...);
}

unsigned __thiscall SP::cCreatureModeInputStrategy::HandleMessage(unsigned param_2, int* param_3)
{
    if (param_2 == 0x477f66c) {
        FUN_00b3d4d0();
        FUN_00ad7dc0();
        cCreatureModeStrategy_Instance();
        FUN_00d2c200();
        FUN_00b3d410();
        FUN_00e3e350();
        if (*(char*)&mpHeldObject.mpObject != 0) {
            *((char*)&mpHeldObject.mpObject + 1) = 1;
            return 1;
        }
        FUN_00b3d320();
        FUN_00b1e410();
        return 1;
    }
    if (param_2 == 0xd33b6aa2) {
        FUN_00bc3170();
        return 1;
    }
    if (param_2 == 0x44eaa93) {
        FUN_00d2eb70();
        return 1;
    }
    {
        int* pInput = (int*)GameInputManager();
        int mode = (*(int(__thiscall**)(void*))(*pInput + 0x34))(pInput);
        if (mode == 2) {
            if (param_2 == 0x452e0ca) {
                cUIBanningContent_EndBanMode();
                int* p2 = (int*)GameInputManager();
                (*(void(__thiscall**)(void*))(*p2 + 0x38))(p2);
                return 1;
            }
            if (param_2 == 0xb332763d) {
                int* p2 = (int*)(*(int(__thiscall**)(int*))(*param_3 + 0x10))(param_3);
                int v = (*(int(__thiscall**)(void*))(*p2 + 0x1c))(p2);
                if (v == 0) return 1;
                FUN_00bd6a60();
            }
        }
    }
    // Remaining decoded message ids (bodies not transcribed):
    //   0x13cdf6fa 0x19d5174 0x19edcf3 0x1c0e6e7 0x1c38e3b 0x1c6d8ad 0x248d179
    //   0x2c4bfda 0x2c4bfde 0x4fe41c0 0x50e6232d 0x620222b 0x620271c 0x62663dc
    //   0x716b83ff 0xb0ee272f 0xd02dcc68
    (void)param_3;
    return 1;
}
