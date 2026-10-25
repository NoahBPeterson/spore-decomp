// Slice s00d45530 (0x00d45530..0x00d456f3, 451 bytes) -- the strategy slot handler run when the
// creature game mode is entered or left.
//
//   void __thiscall cModeStrategy::PostGameModeTransition(cGameMode* from, cGameMode* to)  (ret 8)
//
// `this` is the polymorphic sub-object of SP::cCreatureModeStrategy (its vtable lives at +0x00, the
// owning cCreatureModeStrategy begins 8 bytes below it, which is what ContinueLoading() is called
// on). The two cGameMode* arguments are the game-mode objects being left and entered; they are only
// ever compared by identity against the static mode objects (0x01654c00 normal mode,
// 0x01654c01 creature mode) and against the bare mode ids posted by the app (0x00dbdba1 planet,
// 0x02ccd1d2 space, -1 = none).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (no /EHsc)

#include "types.h"
#include <stddef.h>

// --- external helpers ------------------------------------------------------------------------
void* __cdecl operator new(unsigned size, const char* name, int flags, unsigned debugFlags,
                           const char* file, int line);   // 0x00f473a0
void* __cdecl SP_EffectsManager();                        // 0x0067ddd0
void* __cdecl MessageServer();                            // 0x0067dcc0
void  __cdecl FUN_00b976f0();                             // 0x00b976f0
float __cdecl FUN_00d2e350();                             // 0x00d2e350 (the app tick period, in st0)

struct cGameMode;
struct cGameObject;   // placeholder: only its address is used

struct cGameNounManager {                                 // 0x00b3d300
    cGameObject* GetAvatar();                             // 0x00b1fdb0
};
cGameNounManager* __cdecl NounManager();                  // 0x00b3d300

struct cGameTimeManager {                                 // 0x00b3d380
    void IncPauseGate(int key);                           // 0x00b32220
};
cGameTimeManager* __cdecl GameTimeManager();              // 0x00b3d380

// The two static game-mode objects this handler keys off. Only their addresses matter.
extern char gGameModeNormal;   // 0x01654c00 (normal / tribal game mode)
extern char gGameModeCreature; // 0x01654c01 (creature game mode)

// --- misc types ------------------------------------------------------------------------------
struct cGameMode;

// The app-level game modes this handler distinguishes. Entering or leaving any of them is a
// separate case; 0 is "no mode / unknown".
enum GameModeId {
    kModeNone      = 0,
    kModePlanet    = 0x00dbdba1,
    kModeSpace     = 0x02ccd1d2,
    kModeUnloading = 0xffffffff
};

struct cGameObject { char pad00[0x04]; };   // placeholder: only its address is used

// --- the polymorphic sub-object `this` lives on ----------------------------------------------
// The strategy's own vtable slots this handler uses: fetch the mode we are in, store the mode we
// are entering, then run the shared post-transition book-keeping.
struct cModeStrategyVtbl {
    void*  m00;                                                              // +0x00
    void*  m04;                                                              // +0x04
    void*  m08;                                                              // +0x08
    void*  m0c;                                                              // +0x0c
    void*  m10;                                                              // +0x10
    void*  m14;                                                              // +0x14
    void*  m18;                                                              // +0x18
    void*  m1c;                                                              // +0x1c
    cGameMode* (__thiscall* GetGameMode)(void* self);                        // +0x20
    void*  m24;                                                              // +0x24
    void*  m28;                                                              // +0x28
    void*  m2c;                                                              // +0x2c
    void*  m30;                                                              // +0x30
    void*  m34;                                                              // +0x34
    void*  m38;                                                              // +0x38
    void*  m3c;                                                              // +0x3c
    void*  m40;                                                              // +0x40
    void   (__thiscall* SetGameMode)(void* self, cGameMode* mode);           // +0x44
    void*  m48;                                                              // +0x48
    void   (__thiscall* OnTransitionEnd)(void* self);                        // +0x4c
};

struct cModeStrategy {
    cModeStrategyVtbl* mpVtbl; // +0x00
    char pad04[0x3d];          // +0x04..0x40
    unsigned char m41;         // +0x41  "creature mode entered" flag
    char pad42[0x56];          // +0x42..0x97
    int  m98;                  // +0x98  mode-entry tick (cleared here)
    int  m9c;                  // +0x9c  previous game-mode id (the `from` object)
    int  ma0;                  // +0xa0  new game-mode id (the `to` object)
    int  ma4;                  // +0xa4  mode-entry sub-tick (cleared here)
    char padA8[0x2c];          // +0xa8..0xd3
    unsigned char md4;         // +0xd4  pending-transition flag A
    char padD5[0x01];          // +0xd5
    unsigned char md6;         // +0xd6  pending-transition flag B

    void PostGameModeTransition(cGameMode* from, cGameMode* to);   // 0x00d45530
};

// --- the owning strategy (ContinueLoading() is a method of it) --------------------------------
struct cCreatureModeStrategy {
    char          pad00[0x08];            // +0x00..0x07
    cModeStrategy mStrategy;              // +0x08
    void          ContinueLoading(int start);   // 0x00d43e30
};

// --- the 0x40-byte message object posted to the message server -------------------------------
struct cSlotMessage {
    char pad00[0x08];          // +0x00..0x07
    int  m08;                  // +0x08  tick count (floor of the app tick period)
    char pad0c[0x04];          // +0x0c..0x0f
    int  m10;                  // +0x10  the avatar's current action id
    char pad14[0x04];          // +0x14..0x17
    int  m18;                  // +0x18  1 = "post as an app message"
    char pad1c[0x14];          // +0x1c..0x2f
    int  m30;                  // +0x30  message id
    char pad34[0x0c];          // +0x34..0x3f

    cSlotMessage* Construct(int flags);   // 0x00421c80
};

struct cSlotMessageVtbl {
    void* m00;                            // +0x00
    void  (__thiscall* Init)(void* self); // +0x04
    void  (__thiscall* Release)(void* self);  // +0x08
};
static cSlotMessageVtbl* SlotMessageVtbl(cSlotMessage* msg) {
    return *(cSlotMessageVtbl**)msg;
}

struct cMessageServerVtbl {
    void* m00;  // +0x00
    void* m04;  // +0x04
    void* m08;  // +0x08
    void* m0c;  // +0x0c
    void* m10;  // +0x10
    void (__thiscall* PostMessage)(void* self, int id, cSlotMessage* msg, int flags);  // +0x14
};
static cMessageServerVtbl* MessageServerVtbl(void* ms) {
    return *(cMessageServerVtbl**)ms;
}

struct cAvatarVtbl {
    char pad00[0xd8];                                   // +0x00..0xd7
    int (__thiscall* GetActionId)(void* self);          // +0xd8
};
static cAvatarVtbl* AvatarVtbl(void* avatar) {
    return *(cAvatarVtbl**)avatar;
}

struct cEffectsManagerVtbl {
    char pad00[0x98];                                                // +0x00..0x97
    void (__thiscall* SetCreatureMode)(void* self, int a, int b);    // +0x98
};
static cEffectsManagerVtbl* EffectsManagerVtbl(void* eff) {
    return *(cEffectsManagerVtbl**)eff;
}

#pragma warning(disable:4035)
// EA math FloorToInt: the app's inline SSE helper (round, then step down when the rounded value
// ended up above the input). Same helper as used by the SP editor / purchases code.
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

// @ 0x00d45530
void cModeStrategy::PostGameModeTransition(cGameMode* from, cGameMode* to) {
    if (mpVtbl->GetGameMode(this) == to)
        return;

    // record the mode we are entering before anything else
    mpVtbl->SetGameMode(this, to);

    if (from != (cGameMode*)&gGameModeCreature) {
        if (to != (cGameMode*)&gGameModeCreature) {
            mpVtbl->OnTransitionEnd(this);
            return;
        }
    } else {
        // leaving the creature game mode
        if (to != (cGameMode*)&gGameModeCreature) {
            if ((int)to == kModePlanet) {
                void* ms = MessageServer();
                if (ms != 0) {
                    cGameObject* avatar = NounManager()->GetAvatar();
                    cSlotMessage* obj = (cSlotMessage*)operator new(0x40, "App", 0, 0, 0, 0);
                    if (obj != 0) {
                        obj = obj->Construct(0);
                        if (obj != 0)
                            SlotMessageVtbl(obj)->Init(obj);
                    }
                    obj->m30 = 0x90a03fdf;
                    obj->m08 = FloorToInt(FUN_00d2e350());
                    obj->m10 = AvatarVtbl(avatar)->GetActionId(avatar);
                    const int id = obj->m30;
                    obj->m18 = 1;
                    MessageServerVtbl(ms)->PostMessage(ms, id, obj, 0);
                    SlotMessageVtbl(obj)->Release(obj);
                    mpVtbl->OnTransitionEnd(this);
                    return;
                }
            } else {
                if ((int)to == kModeSpace || (int)to == kModeUnloading)
                    FUN_00b976f0();
                md6 = 0;
                md4 = 0;
            }
            mpVtbl->OnTransitionEnd(this);
            return;
        }
    }

    // entering the creature game mode (from either side) -- or leaving it towards creature mode
    void* eff = SP_EffectsManager();
    EffectsManagerVtbl(eff)->SetCreatureMode(eff, 8, 1);

    m41 |= (from == (cGameMode*)&gGameModeNormal);
    m98 = 0;
    m9c = (int)from;
    ma0 = (int)to;
    ma4 = 0;

    GameTimeManager()->IncPauseGate(0x4bf38a7);
    ((cCreatureModeStrategy*)((char*)this - offsetof(cCreatureModeStrategy, mStrategy)))
        ->ContinueLoading(0);

    mpVtbl->OnTransitionEnd(this);
}
