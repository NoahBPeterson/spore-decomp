// Slice s0100a080: expiry of the space-game UFO status effects.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned __int64 u64;

// A simulator timer embedded in a game noun; its own state lives in mBytes.
struct cSimEffectTimer {
    u8   mBytes[0x20];
    bool IsValid();                    // 0x00feba90
    u64  Elapsed();                    // 0x00bc3190
    void Reset();                      // 0x00bc3110
};

// The small state block at +0x508 of a space-game noun.
struct cSpaceEffectState {
    u8   mBytes[0x1c8];
    bool Get();                        // 0x00bfc480
    void Set(int value);               // 0x00bfc470
};

// A noun of the space-game object list: two status-effect timers plus the
// on/off state the simulator queries for it.
struct cSpaceNoun {
    u8                 mPad0000[0x508];
    cSpaceEffectState  mState508;      // 0x508
    cSimEffectTimer    mTimer6d0;      // 0x6d0
    cSimEffectTimer    mTimer6f0;      // 0x6f0

    bool FUN_00c38990(int enabled);            // 0x00c38990
    void FUN_00c389c0(int enabled, int arg);   // 0x00c389c0
};

// The noun-pointer vector the noun-manager data query fills in.
struct cSpaceNounVector {
    cSpaceNoun** mpBegin;              // 0x00
    cSpaceNoun** mpEnd;                // 0x04
};

// The record the query returns: a type word followed by the vector.
struct cGameDataVectorOut {
    u32               mType;           // 0x00
    cSpaceNounVector  mVec;            // 0x04
};

struct cSpaceNounManager {
    cGameDataVectorOut* GetGameDataVector(void* a, void* b, void* c, void* d, int e);  // 0x00b21340
};

cSpaceNounManager* __cdecl NounManager();   // 0x00b3d300

// @ 0x0100a080
// Walks every noun of the space-game object list and, for the ones that are
// switched on, retires a status effect that has been running past its lifetime
// (90 s for the +0x6f0 effect, 60 s for the +0x6d0 one with the +0x508 state).
void UpdateUFOStatusEffects()
{
    cSpaceNounManager* manager = NounManager();
    cGameDataVectorOut* out = manager->GetGameDataVector(
        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xad48b0, (void*)0xb1e500, 0x18ebadc);

    cSpaceNounVector& nouns = out->mVec;
    cSpaceNoun** it = nouns.mpBegin;
    cSpaceNoun** end = nouns.mpEnd;

    for (; it != end; ++it) {
        cSpaceNoun* noun = *it;

        if (noun->FUN_00c38990(1)) {
            if (noun->mTimer6f0.IsValid() && noun->mTimer6f0.Elapsed() > 0x15f90) {
                noun->FUN_00c389c0(1, 0);
                noun->mTimer6f0.Reset();
            }
        }

        if (noun->mState508.Get()) {
            if (noun->mTimer6d0.IsValid() && noun->mTimer6d0.Elapsed() > 0xea60) {
                noun->mState508.Set(0);
                noun->mTimer6d0.Reset();
            }
        }
    }
}
