// Slice s00d6f1c0 -- party/posse behaviour packets and the small actor helpers that clear
// behaviour stimuli and push the "go to avatar" action.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

// behaviour stimuli set embedded in a behaviour tree (offset +8).
struct cBehaviorStimuli {
    uint8_t pad000[8];                                  // +0x00 .. +0x07

    void ClearAll(uint32_t mask, uint32_t flags);        // 0x00bc98f0
};

struct cBehaviorTree {
    uint8_t        pad000[8];                           // +0x00 .. +0x07
    cBehaviorStimuli mStimuli;                          // +0x08
};

// Avatar noun carrying the behaviour payload at +0x5a8.
class cAvatar {
public:
    uint8_t  pad000[0x5a8];                             // +0x000 .. +0x5a7
    uint32_t mTargetHandle;                             // +0x5a8
};

class cGameNounManager {
public:
    cAvatar* GetAvatar();                               // 0x00b1fdb0
};

cGameNounManager* __cdecl NounManager();                 // 0x00b3d300

// Actor that drives a behaviour tree; only the slots used here are named.
class cBehaviorActor {
public:
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c();
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void v080();
    virtual void PushTargetAction(void* pTarget, int mode, int flags); // +0x84

    uint8_t        pad004[0xb48];                       // +0x004 .. +0xb4b
    cBehaviorTree* mpBehavior;                          // +0xb4c
};

// --- behaviour packets -----------------------------------------------------

struct cActionStatus {
    int32_t mResult;                                    // +0x00
    int32_t mDetail;                                    // +0x04
};

bool __cdecl PATROL_TOOFAR_Decide(cBehaviorActor* pActor, int param, int32_t* pResult); // 0x00d6f430
void __cdecl CRY_TO_AVATAR_Tick(cBehaviorActor* pActor, cActionStatus* pStatus);        // 0x00d6f800
void __cdecl AVATAR_PARTY_Tick(cBehaviorActor* pActor, cActionStatus* pStatus);         // 0x00d6f910
void __cdecl POSSE_PARTY_Tick(cBehaviorActor* pActor, cActionStatus* pStatus);          // 0x00d6fa60

} // namespace SP

using namespace SP;

namespace SP {

// @ 0xd6f1c0 FUN_00d6f1c0
void __fastcall FUN_00d6f1c0(cBehaviorActor* this_, int unused)
{
    (void)this_;
}

// @ 0xd6f430 PATROL_TOOFAR_Decide
bool __cdecl PATROL_TOOFAR_Decide(cBehaviorActor* pActor, int param, int32_t* pResult)
{
    (void)pActor;
    (void)param;
    if (pResult)
        *pResult = 0;
    return true;
}

// @ 0xd6f590 FUN_00d6f590
void __fastcall FUN_00d6f590(cBehaviorActor* this_, int unused)
{
    (void)this_;
}

// @ 0xd6f760 FUN_00d6f760
void __cdecl FUN_00d6f760(cBehaviorActor* pActor)
{
    pActor->PushTargetAction(0, 0, 0);
    pActor->mpBehavior->mStimuli.ClearAll(0, 0x80);
}

// @ 0xd6f790 FUN_00d6f790
bool __cdecl FUN_00d6f790(cBehaviorActor* pActor, int p1, int p2, int p3, int p4,
                          int32_t* pOut)
{
    (void)p1;
    (void)p2;
    (void)p3;
    (void)p4;
    cAvatar* pAvatar = NounManager()->GetAvatar();
    uint32_t* pTarget = pAvatar ? &pAvatar->mTargetHandle : 0;
    pActor->PushTargetAction(pTarget, 1, 0);
    pOut[0] = 0;
    pOut[1] = 0;
    return true;
}

// @ 0xd6f800 CRY_TO_AVATAR_Tick
void __cdecl CRY_TO_AVATAR_Tick(cBehaviorActor* pActor, cActionStatus* pStatus)
{
    (void)pActor;
    (void)pStatus;
}

// @ 0xd6f910 AVATAR_PARTY_Tick
void __cdecl AVATAR_PARTY_Tick(cBehaviorActor* pActor, cActionStatus* pStatus)
{
    (void)pActor;
    (void)pStatus;
}

// @ 0xd6fa60 POSSE_PARTY_Tick
void __cdecl POSSE_PARTY_Tick(cBehaviorActor* pActor, cActionStatus* pStatus)
{
    (void)pActor;
    (void)pStatus;
}

// @ 0xd6fd70 FUN_00d6fd70
void __fastcall FUN_00d6fd70(cBehaviorActor* this_, int unused)
{
    (void)this_;
}

// @ 0xd6fef0 FUN_00d6fef0
void __fastcall FUN_00d6fef0(cBehaviorActor* this_, int unused)
{
    (void)this_;
}

} // namespace SP
