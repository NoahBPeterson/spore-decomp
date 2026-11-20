// Slice s00cd16a0 -- cScenarioEditModeInputStrategy: destructor and UI state machine setup.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_14771e0[];

#include "types.h"

namespace Simulator {

// Intrusive-list sentinel stored inside both sub-objects below.
struct cListRoot {
    void* mpNext;                                            // +0x00
    void* mpPrev;                                            // +0x04
};

struct cNested1c {
    uint32_t  mTag00;                                        // +0x00
    cListRoot mRoot;                                         // +0x04  self-referential sentinel
    void*     mpValue0c;                                     // +0x0c
    uint8_t   mFlag10;                                       // +0x10
    uint32_t  mPad14;                                        // +0x14
    uint32_t  mPad18;                                        // +0x18

    void Release(void* value);                               // 0x00e4b990
    void Reset(void);                                        // inlined by the caller
};

struct cSub04 {
    uint32_t  mTag00;                                        // +0x00
    cListRoot mRoot;                                         // +0x04  self-referential sentinel
    void*     mpValue0c;                                     // +0x0c
    uint8_t   mFlag10;                                       // +0x10
    uint32_t  mPad14;                                        // +0x14
    uint32_t  mPad18;                                        // +0x18
    cNested1c mNested1c;                                     // +0x1c

    void Release(void* value);                               // 0x00b1b830
    void Reset(void);                                        // inlined by the caller
};

struct cScenarioEditModeInputStrategy {
    void*    mpVtable;                                       // +0x00
    cSub04   mSub;                                           // +0x04

    void* Destroy(uint8_t flags);
    void  InitUIStateMachines(int mode);
};

// UI state machine host built as a temporary while declaring the strategy's
// layout state machines.  0x14 bytes: pad + owning pointer at +0x10.
struct cStateMachineHost {
    uint32_t mPad00[4];                                      // +0x00 .. +0x0f
    void*    mpOwner;                                        // +0x10

    cStateMachineHost(void* owner);                          // 0x00b198d0
    void DeclareState(int state, const char* name);          // 0x00b1c080
    void LoadStateMachine(const char* name);                 // 0x00b1b410
    void Finish();                                           // 0x00b19b60
    ~cStateMachineHost();                                    // 0x0083c750
};

// Empties the container: release the owned value, then re-point the sentinel at
// itself and clear the value/flag fields.
inline void cNested1c::Reset(void)
{
    Release(mpValue0c);
    mRoot.mpNext = &mRoot;
    mRoot.mpPrev = &mRoot;
    mpValue0c = 0;
    mFlag10 = 0;
    mPad14 = 0;
}

inline void cSub04::Reset(void)
{
    Release(mpValue0c);
    mRoot.mpNext = &mRoot;
    mRoot.mpPrev = &mRoot;
    mpValue0c = 0;
    mFlag10 = 0;
    mPad14 = 0;
}

} // namespace Simulator

extern "C" void operator_delete(void* p);                    // 0x00f47380

// @ 0x00cd1750
void* Simulator::cScenarioEditModeInputStrategy::Destroy(uint8_t flags)
{
    cSub04& sub = mSub;
    cNested1c& nested = sub.mNested1c;
    mpVtable = (void*)g_14771e0;
    nested.Release(nested.mpValue0c);
    sub.Release(sub.mpValue0c);
    if (flags & 1)
        operator_delete(this);
    return this;
}

// @ 0x00cd16a0
// Resets both intrusive containers of the strategy, then rebuilds the tribe UI
// state machine: "CISNeutral" is the neutral creature-input state and the
// per-layout machine is loaded on top of "UIMachineTribe".
void Simulator::cScenarioEditModeInputStrategy::InitUIStateMachines(int mode)
{
    mSub.Reset();
    mSub.mNested1c.Reset();

    cStateMachineHost host(&mSub);
    host.DeclareState(0, "CISNeutral");
    switch (mode)
    {
    case 0:
        host.LoadStateMachine("UIMachineLeftRightTranslate");
        break;
    case 1:
        host.LoadStateMachine("UIMachineTribeRotate");
        break;
    default:
        host.LoadStateMachine("UIMachineLeftRightTranslate");
        break;
    }
    host.LoadStateMachine("UIMachineTribe");
    host.Finish();
}
