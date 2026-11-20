// Slice s00ce3560 -- SP planner step: spend tribe food on a tool whose cooldown has
// elapsed, place the spawned tool through the planner UI, then charge the plan
// context for the tool's cost.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>

// Retail image references, use relocatable symbols rather than numeric addresses.
extern "C" unsigned char g_014853bc[];

namespace SP {

// State block handed to the planner steps (tribe first, plan table second).
struct cPlannerContext {
    void*    mpTribe;                                        // +0x00
    void*    mpPlanner;                                      // +0x04
    uint32_t mPad08;                                         // +0x08
    uint32_t mPad0c;                                         // +0x0c
    uint32_t mPad10;                                         // +0x10
    int32_t  mValue14;                                       // +0x14
};

// SP::cTribePlanConfiguration (only the property holder is used here).
struct cPlanConfiguration {
    uint32_t mPad00[0x40 / 4];                               // +0x00 .. +0x3f
    void*    mpPropertyHolder;                               // +0x40
};

// Tool description table entry returned for a probe value.
struct cToolEntry {
    uint32_t mPad00[0x38 / 4];                               // +0x00 .. +0x37
    int32_t  mCost;                                          // +0x38
};

struct cVector3 {
    float mX;
    float mY;
    float mZ;
};

struct cColor {
    float mR;
    float mG;
    float mB;
    float mA;
};

// Opaque name/tag buffer the placed model fills in.
struct cTagName {
    uint32_t mPad00[3];
};

} // namespace SP

extern "C" unsigned  SP_GetAdultPopulation();                // 0x00c8f370 (thiscall)
extern "C" uint32_t __cdecl FindFirstEligiblePlanStep(SP::cPlannerContext*, uint32_t,
                                                     uint32_t); // 0x00ce2f00
extern "C" void      SP_GetProbeValue();                     // 0x00c904b0 (thiscall, int* out)
extern "C" void      SP_GetToolOfType();                     // 0x00c8f6e0 (thiscall, int)
extern "C" void      SP_GetToolState();                      // 0x008e7f80 (thiscall, no args)
extern "C" void      FindPlanEntry();                        // 0x00ce0e60 (thiscall: table, x, y)
extern "C" void      SP_GetPlanConfiguration();              // 0x00ce2ee0 (thiscall, no args)
extern "C" float __cdecl GetPropertyFloat(void*, uint32_t, float); // 0x004e1c70
extern "C" float     SP_GetTimeSinceLastUse();               // 0x00c9d1c0 (thiscall, no args)
extern "C" void* __cdecl GetToolEntry(int32_t);              // 0x00c9cec0
extern "C" uint32_t  SP_SpawnToolIcon();                     // 0x00c9cfd0 (thiscall, no args)
extern "C" void      SP_AdjustTribeValue();                  // 0x00c8f660 (thiscall, int)
extern "C" void      SP_ReserveToolSlots();                  // 0x00c998c0 (thiscall, bool)
extern "C" void*     GetPlannerUI();                         // 0x00b3d240

typedef unsigned      (__thiscall* AdultPopThunk)(void*);
typedef unsigned char (__thiscall* ProbeValueThunk)(void*, int*);
typedef void*         (__thiscall* ToolOfTypeThunk)(void*, int);
typedef int           (__thiscall* ToolStateThunk)(void*);
typedef void*         (__thiscall* FindEntryThunk)(void*, uint32_t, uint32_t);
typedef void*         (__thiscall* PlanConfigThunk)(void*);
typedef float         (__thiscall* ToolUseAgeThunk)(void*);
typedef uint32_t      (__thiscall* SpawnIconThunk)(void*);
typedef void          (__thiscall* AdjustValueThunk)(void*, int);
typedef void          (__thiscall* ReserveSlotsThunk)(void*, unsigned char);

// eastl::max spelling: selects by reference, so the constant operand becomes a
// stack temporary and the result is loaded from the chosen address.
static __forceinline const int& MaxRef(const int& a, const int& b) { return (a > b) ? a : b; }

// @ 0x00ce3560
double __cdecl FUN_00ce3560(SP::cPlannerContext* args)
{
    void* pTribe = args->mpTribe;

    if (((AdultPopThunk)SP_GetAdultPopulation)(pTribe) <= 0)
        return 0.0;

    // A tool-spending step (kind 8, no ignore flag) must be available.
    uint32_t uPlan = FindFirstEligiblePlanStep(args, 8, 0);
    if (uPlan != 0xffffffffu) {
        // The probe value selects which tool the step wants.
        int iProbe = 0;
        if (((ProbeValueThunk)SP_GetProbeValue)(pTribe, &iProbe)) {
            if (iProbe != 0) {
                void* pTool = ((ToolOfTypeThunk)SP_GetToolOfType)(pTribe, iProbe);
                if (pTool) {
                    if (((ToolStateThunk)SP_GetToolState)((char*)pTool + 0x120) == 2) {
                        // Cooldown of the tool: the configured delay must have elapsed.
                        SP::cPlanConfiguration* pConfig = (SP::cPlanConfiguration*)
                            ((PlanConfigThunk)SP_GetPlanConfiguration)(
                                ((FindEntryThunk)FindPlanEntry)(args->mpPlanner, 8, uPlan));
                        void* pHolder = pConfig->mpPropertyHolder;
                        float fCooldown = GetPropertyFloat(pHolder, 0xbff61edbu,
                                                          *(const float*)g_014853bc);
                        if (!(fCooldown > ((ToolUseAgeThunk)SP_GetTimeSinceLastUse)(pTool))) {
                            // Position and colour of the tool's model, kept for the copy.
                            void* pToolSub = (char*)pTool + 0x34;
                            SP::cVector3* pPos = (SP::cVector3*)((void* (__thiscall*)(void*))
                                ((void**) *(void**)pToolSub)[0x2c / 4])(pToolSub);
                            SP::cVector3 vPos;
                            vPos.mX = pPos->mX;
                            vPos.mY = pPos->mY;
                            vPos.mZ = pPos->mZ;
                            _ReadWriteBarrier();

                            SP::cTagName name;

                            SP::cColor* pColor = (SP::cColor*)((void* (__thiscall*)(void*))
                                ((void**) *(void**)pToolSub)[0x30 / 4])(pToolSub);
                            SP::cColor color;
                            color.mR = pColor->mR;
                            color.mG = pColor->mG;
                            color.mB = pColor->mB;
                            color.mA = pColor->mA;

                            // Pay for the tool: charge the shortfall, remove the tool
                            // from the shared slots, then credit the cost back.
                            SP::cToolEntry* pEntry = (SP::cToolEntry*)GetToolEntry(iProbe);
                            int iDelta = pEntry->mCost -
                                         (int)((SpawnIconThunk)SP_SpawnToolIcon)(pTool);
                            int iAmount = MaxRef(iDelta, 0);
                            ((AdjustValueThunk)SP_AdjustTribeValue)(pTribe, iAmount);
                            ((void (__thiscall*)(void*, void*))
                                ((void**) *(void**)pTribe)[0xb8 / 4])(pTribe, pTool);
                            ((AdjustValueThunk)SP_AdjustTribeValue)(pTribe, -pEntry->mCost);

                            // Give the tribe a new tool and place it where the old was.
                            void* pPlaced = ((void* (__thiscall*)(void*, int))
                                ((void**) *(void**)pTribe)[0xb4 / 4])(pTribe, iProbe);
                            ((void (__thiscall*)(void*, void*))
                                ((void**) *(void**)pPlaced)[0x64 / 4])(pPlaced, pTribe);

                            void* pPlacedSub = (char*)pPlaced + 0x34;
                            ((void (__thiscall*)(void*, SP::cVector3*))
                                ((void**) *(void**)pPlacedSub)[0x38 / 4])(pPlacedSub, &vPos);
                            ((void (__thiscall*)(void*, SP::cColor*))
                                ((void**) *(void**)pPlacedSub)[0x3c / 4])(pPlacedSub, &color);

                            ((ReserveSlotsThunk)SP_ReserveToolSlots)(pTribe, 0);

                            // Tell the planner UI about the placed model (tag
                            // 0x014fc194); the name/model calls are arguments,
                            // so they are evaluated before the notification.
                            void* pUI = GetPlannerUI();
                            void** ppNotify = &((void**) *(void**)pUI)[0x60 / 4];
                            ((void (__thiscall*)(void*, uint32_t, void*, void*)) *ppNotify)(
                                pUI, 0x014fc194u,
                                ((void* (__thiscall*)(void*))
                                    ((void**) *(void**)pPlacedSub)[0x2c / 4])(pPlacedSub),
                                ((void* (__thiscall*)(void*, void*))
                                    ((void**) *(void**)pPlacedSub)[0x5c / 4])(pPlacedSub,
                                                                              &name));

                            args->mValue14 -= pEntry->mCost;
                            return 0.0;
                        }
                        else
                            return 0.0;
                    }
                    else
                        return 0.0;
                }
                else
                    return 0.0;
            }
            else
                return 0.0;
        }
        else
            return 0.0;
    }
    else
        return 0.0;

    return 0.0;
}
