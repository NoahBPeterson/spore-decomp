// Slice s00ce33b0 -- SP plan deactivation thunks (partial).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

struct PlanArgs {
    void* mpPlan;                                            // +0x00
    void* mpContext;                                         // +0x04
    uint32_t mPad08;                                         // +0x08
    void* mpAudioValue;                                      // +0x0c
};

struct AudioSystem {
    void* mpVtable;                                          // +0x00
};

struct cSubInterface {
    void* mpVtable;                                          // +0x00
};

struct cPlannerHost {
    void* mpVtable;                                          // +0x00
    uint32_t mPad04[12];                                     // +0x04 .. +0x33
    cSubInterface mSub;                                      // +0x34
};

struct cPlannerUnit {
    uint32_t mPad00[48];                                     // +0x00 .. +0xbf
    cSubInterface mSub;                                      // +0xc0
};

struct cPlanConfig {
    uint32_t mPad00[16];                                     // +0x00 .. +0x3f
    uint32_t mValue40;                                       // +0x40
};

struct cPlanTableEntry {
    uint32_t      mPlanId;                                   // +0x00
    uint32_t      mPad04[20];                                // +0x04 .. +0x53
    cPlanConfig*  mpConfig;                                  // +0x54
};

struct cCheatArgs {
    cPlannerHost* mpObject;                                  // +0x00
    void*         mpPlanTable;                               // +0x04
};

struct cPlannerArgs {
    uint32_t mPad00[6];                                      // +0x00 .. +0x17
    uint32_t mValue18;                                       // +0x18
    uint32_t mValue1c;                                       // +0x1c
};

struct cCombatant {
    void* mpVtable;                                          // +0x00
};

struct cCombatantHost {
    uint32_t    mPad00[0x120 / 4];                           // +0x00 .. +0x11f
    cCombatant  mCombatant;                                  // +0x120
};

struct cTribe {
    void*    mpVtable;                                       // +0x00
    uint8_t  mPad04[0xb5a];                                  // +0x04 .. +0xb5d
    uint8_t  mFlagB5e;                                       // +0xb5e
};

struct cStimuli {
    uint32_t mPad00[6];                                      // +0x00 .. +0x17
    int32_t  mValue18;                                       // +0x18
    void*    mpValue1c;                                      // +0x1c
};

} // namespace SP

extern "C" void SP_GetDamageState();                        // 0x008e7f80 (thiscall)
extern "C" void SP_TribeIsReady();                          // 0x00c8f3a0 (thiscall int)
extern "C" void SP_GetChieftain();                          // 0x00c8fd30 (thiscall pointer)
extern "C" void* __cdecl FindFirstEligiblePlanStep(void* plan, int a, int b); // 0x00ce2f00
extern "C" void SP_GetAny();                                // 0x00d997e0 (thiscall)

// @ 0x00ce3440
double __cdecl TryStartPlanStep(void* planRef, int a, int b, int c, SP::cStimuli* stimuli,
                                uint8_t* outFlag)
{
    SP::cTribe* tribe = (SP::cTribe*)*(void**)planRef;
    SP::cCombatantHost* host = (SP::cCombatantHost*)(
        (void* (__thiscall*)(SP::cTribe*))((void**)tribe->mpVtable)[0xac / 4])(tribe);
    int state = ((int (__thiscall*)(void*))SP_GetDamageState)(&host->mCombatant);
    if (state == 2)
        return 0.0;
    int ready = ((int (__thiscall*)(SP::cTribe*))SP_TribeIsReady)(tribe);
    if (ready == 1) {
        SP::cTribe* chief = (SP::cTribe*)((void* (__thiscall*)(SP::cTribe*))SP_GetChieftain)(tribe);
        if (!chief)
            return 0.0;
        chief = (SP::cTribe*)((void* (__thiscall*)(SP::cTribe*))SP_GetChieftain)(tribe);
        if (chief->mFlagB5e == 0)
            return 0.0;
    } else if (ready != 0) {
        return 0.0;
    }
    void* plan = FindFirstEligiblePlanStep(planRef, 7, 1);
    if (plan == (void*)-1)
        return 0.0;
    if (stimuli)
        ((void (__thiscall*)(SP::cStimuli*))SP_GetAny)(stimuli);
    stimuli->mpValue1c = plan;
    stimuli->mValue18 = 7;
    *outFlag = 1;
    return 1.0;
}

extern "C" void __cdecl DeactivatePlan(void* plan, void* a, void* b, int flag); // 0x00ce3020

// @ 0x00ce3b40
void __cdecl DeactivatePlanThunk1(void* plan, int a, int b, int c, int d, SP::PlanArgs* ctx)
{
    DeactivatePlan(plan, ctx->mpPlan, ctx->mpContext, 1);
}

// @ 0x00ce3e90
void __cdecl DeactivatePlanThunk0(void* plan, int a, int b, int c, int d, SP::PlanArgs* ctx)
{
    DeactivatePlan(plan, ctx->mpPlan, ctx->mpContext, 0);
}

extern "C" void* __cdecl GetSystemAT();                     // 0x00a206f0

// @ 0x00ce3e20
void __cdecl RaidingDeactivate(void* plan, int a, int b, int c, int d, SP::PlanArgs* ctx)
{
    void* audioValue = ctx->mpAudioValue;
    SP::AudioSystem* audio = (SP::AudioSystem*)GetSystemAT();
    if (audio) {
        ((void (__thiscall*)(void*, uint32_t))((void**)audio->mpVtable)[0x38 / 4])(audio, 0x0347536b);
        ((void (__thiscall*)(void*, uint32_t, void*))((void**)audio->mpVtable)[0x40 / 4])(audio, 0x03475385, audioValue);
        ((void (__thiscall*)(void*, uint32_t, int))((void**)audio->mpVtable)[0x40 / 4])(audio, 0x034753a0, 0);
        ((void (__thiscall*)(void*))((void**)audio->mpVtable)[0x58 / 4])(audio);
    }
    DeactivatePlan(plan, ctx->mpPlan, ctx->mpContext, 1);
}

extern "C" void FindPlanEntry();                            // 0x00ce0e60 (thiscall: table, a, b)
extern "C" SP::cPlanConfig* __cdecl GetTribePlanConfiguration(uint32_t planId);    // 0x00ce2d20
extern "C" uint32_t __cdecl CountPlanObjects(void* configValue, uint32_t id, int flag); // 0x00ac8fa0

// @ 0x00ce3a80
bool __cdecl CheatMembersActivate(SP::cCheatArgs* args, int a, int b, int c, int d, int e,
                                  SP::cPlannerArgs* ctx)
{
    SP::cPlannerHost* host = args->mpObject;
    SP::cPlanTableEntry* entry = ((SP::cPlanTableEntry* (__thiscall*)(void*, uint32_t, uint32_t))
        FindPlanEntry)(args->mpPlanTable, ctx->mValue18, ctx->mValue1c);
    if (!entry)
        return false;
    if (!entry->mpConfig)
        entry->mpConfig = GetTribePlanConfiguration(entry->mPlanId);
    uint32_t count = CountPlanObjects((void*)entry->mpConfig->mValue40, 0x80033b48, 1);
    SP::cPlannerHost* sub;
    sub = (SP::cPlannerHost*)(
        (void* (__thiscall*)(SP::cPlannerHost*))((void**)host->mpVtable)[0xac / 4])(host);
    uint32_t valueA = ((uint32_t (__thiscall*)(void*))
        ((void**)sub->mSub.mpVtable)[0x2c / 4])(&sub->mSub);
    sub = (SP::cPlannerHost*)(
        (void* (__thiscall*)(SP::cPlannerHost*))((void**)host->mpVtable)[0xac / 4])(host);
    uint32_t valueB = ((uint32_t (__thiscall*)(void*))
        ((void**)sub->mSub.mpVtable)[0x30 / 4])(&sub->mSub);
    while (count > 0) {
        SP::cPlannerUnit* unit = (SP::cPlannerUnit*)(
            (void* (__thiscall*)(SP::cPlannerHost*, int))
            ((void**)host->mpVtable)[0x98 / 4])(host, 1);
        ((void (__thiscall*)(void*, uint32_t, uint32_t))
            ((void**)unit->mSub.mpVtable)[0x44 / 4])(&unit->mSub, valueA, valueB);
        --count;
    }
    return false;
}
