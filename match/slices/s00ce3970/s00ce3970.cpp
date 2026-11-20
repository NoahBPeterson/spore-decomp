// Slice s00ce3970 -- SP planner step: find plan entry, count down a local
// timer, then let the host play its "baby born" vocal.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include "sse_helpers.h"

// Retail image references, use relocatable symbols rather than numeric addresses.
extern "C" unsigned char g_0147792c[];
extern "C" unsigned char g_0158133c[];

namespace SP {

struct cSubInterface {
    void* mpVtable;                                          // +0x00
};

struct cPlanTableEntry {
    uint32_t mPlanId;                                        // +0x00
    uint32_t mPad04[20];                                     // +0x04 .. +0x53
    void*    mpConfig;                                       // +0x54
};

// First 0x20c bytes of the planner host; the host object itself additionally
// carries a voice sub-interface as a second base at +0x20c.
struct cHostHead {
    void*          mpHostVtbl;                               // +0x00
    uint32_t       mPad04[12];                               // +0x04 .. +0x33
    cSubInterface  mSub;                                     // +0x34
    uint32_t       mPad38[117];                              // +0x38 .. +0x20b
};

struct cPlannerHost : cHostHead, cSubInterface {
};

struct cPlannerUnit {
    uint32_t       mPad00[48];                               // +0x00 .. +0xbf
    cSubInterface  mSub;                                     // +0xc0
};

// Argument block at +0x00 of the step function's first parameter.
struct cPlanArgs {
    cPlannerHost* mpObject;                                  // +0x00
    void*         mpPlanTable;                               // +0x04
};

// State block passed as the step function's sixth parameter.
struct cStepState {
    uint32_t mX;                                             // +0x00
    uint32_t mY;                                             // +0x04
    float    mTimeLeft;                                      // +0x08
};

} // namespace SP

extern "C" void  FindPlanEntry();                            // 0x00ce0e60 (thiscall: table, x, y)
extern "C" void* __cdecl GetTribePlanConfiguration(uint32_t planId);  // 0x00ce2d20
extern "C" void* __cdecl GetGlobalValue();                   // 0x00b3d2b0
extern "C" float SP_PlayVocalData();                         // 0x00ac7d10 (thiscall, 3 args)
extern "C" unsigned SP_TriggerVocalOnUnit();                 // 0x00c1d640

// @ 0x00ce3970
bool __cdecl FUN_00ce3970(SP::cPlanArgs* args, int a2, int a3, int a4, int a5,
                          SP::cStepState* state, int a7, float dt)
{
    SP::cPlannerHost* host = args->mpObject;
    SP::cPlanTableEntry* entry = ((SP::cPlanTableEntry* (__thiscall*)(void*, uint32_t, uint32_t))
        FindPlanEntry)(args->mpPlanTable, state->mX, state->mY);
    if (!entry)
        return false;
    if (!entry->mpConfig)
        entry->mpConfig = GetTribePlanConfiguration(entry->mPlanId);
    // Retail reads the timer-reset value (2.0f) from the global at 0x01470f1c and
    // compares against the zero float at 0x01485378.
    if ((state->mTimeLeft = state->mTimeLeft - dt) > 0.0f) {
        state->mTimeLeft = 2.0f;
        return true;
    }
    float limitf = (*(float*)g_0158133c);
    int limit = SseTruncToInt(limitf);
    if (((int (__thiscall*)(void*))((void**)host->mpHostVtbl)[0xa4 / 4])(host) < limit)
        return false;
    // Retail compares against the tiny epsilon float at 0x0147792c (2^-16).
    if (limitf > (*(const float*)g_0147792c)) {
        ((float (__thiscall*)(void*, float, void*, unsigned))SP_PlayVocalData)(
            GetGlobalValue(), limitf, (void*)(SP::cSubInterface*)host, 0u);
    }
    SP::cPlannerUnit* unit = (SP::cPlannerUnit*)(
        (void* (__thiscall*)(SP::cPlannerHost*, int))((void**)host->mpHostVtbl)[0x98 / 4])(host, 0);
    if (!unit)
        return false;
    SP::cPlannerHost* sub = (SP::cPlannerHost*)(
        (void* (__thiscall*)(SP::cPlannerHost*))((void**)host->mpHostVtbl)[0xac / 4])(host);
    SP::cSubInterface* unitIface = &unit->mSub;
    void** unitVtable = (void**)unitIface->mpVtable;
    uint32_t value = ((uint32_t (__thiscall*)(void*))
        ((void**)sub->mSub.mpVtable)[0x2c / 4])(&sub->mSub);
    ((void (__thiscall*)(void*, uint32_t))unitVtable[0x38 / 4])(unitIface, value);
    ((unsigned (__thiscall*)(void*, const char*, int, unsigned))
        SP_TriggerVocalOnUnit)(unit, "vcode_baby_born_cry", 2, 0);
    return false;
}
