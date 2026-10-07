// Slice s00dbab60 — one function, @ 0x00dbab60 (13,792 bytes).
//
// SP tribe creature "tick" behaviour-tree action.  PDB candidate
// SP::TRIBE_NPC_GIFT_Tick (decompile header; xmatch also scores
// SP::TRIBE_GATHER_MEAT_Tick from callers) — the name is uncertain, so keep
// it as a candidate.  `param_1` is the acting cSPCreatureBase; extra
// behaviour arguments live on the caller's stack (Ghidra lost them).  The
// body validates the actor/target, then switches on the behaviour opcode
// (*blackboard) and drives the creature through the animation / locomotion /
// tribe APIs (PlayAnimation, InterruptAnimation, MoveToPointAtSpeed,
// MoveToPointAndFacingAtSpeed, SetSprinting, Attack, GetTribe, ...),
// with a score-based selection and random jitter.
//
// PARTIAL (call-shape skeleton): oversized (>13 KB); captures the guards,
// the opcode switch and every out-of-line call, but the per-case bodies are
// summarised.  Not asm transcription.
#include "types.h"

namespace SP { struct cSPCreatureBase; }

extern uint8_t  DAT_01581374;

extern uint32_t FUN_00da6270(void* a, int b);                        // anim helper
extern uint32_t FUN_00d998d0(void* a, uint32_t id);
extern int      FUN_00d00780(float v);
extern void     FUN_00b3d2c0(float v);
extern float    SP_normalized_safe(float* a, float* b, float lo, float hi);
extern void*    SP_TribeModeStrategy_Instance();
extern uint32_t FUN_00bc2240(uint32_t id, void* a, void* b, void* c);
extern void     FUN_00bc23d0(void* p, void* a, void* b, void* c);

// creature methods (thiscall, declared as free helpers for the skeleton)
extern void cSPCreatureBase_PlayAnimation(void* self, uint32_t clip);
extern void cSPCreatureBase_InterruptAnimation(void* self, uint32_t clip);
extern void cSPCreatureBase_MoveToPointAtSpeed(void* self, void* dst, float speed);
extern void cSPCreatureBase_MoveToPointAndFacingAtSpeed(void* self, int mode, void* dst, float speed, int a, int b);
extern void cSPCreatureBase_SetSprinting(void* self, int on);
extern void cSPCreatureBase_Attack(void* self, void* target);
extern void cSPCreatureBase_PlayIdleAnimation(void* self);

// @ 0x00dbab60
uint32_t FUN_00dbab60(void* param_1, void* arg0, void* arg1, void* arg2,
                      void* arg3, void* arg4, int arg5, int arg6, void* arg7)
{
    (void)arg1; (void)arg2; (void)arg3; (void)arg4; (void)arg5; (void)arg6; (void)arg7;

    if (arg0 == 0)
        return FUN_00da6270(param_1, 0xf);

    // actor validation: a specific "tribe" component id (0x4f396a66)
    if (arg0 != 0 && FUN_00d998d0(arg0, 0x4f396a66) != 0)
        goto active;

    if (*(int*)arg1 < 4 || DAT_01581374 != 0) {
        FUN_00b3d2c0(0.0f);
        int n = (int)FUN_00d00780(0.0f);
        if (n > 1)
            goto active;
    }
    // distance/score test against the blackboard target (squared distance
    // compared with 1.0f) -> return 0 when out of range
    {
        float dx = 0.0f;
        if (1.0f < dx * dx)
            return 0;
    }

active:
    // score-based selection: best target gives the animation/route
    if (arg0 != 0) {
        // if ((cVar3 != 0) && (param_1 == pcVar9)) { cTribeModeStrategy::Instance();
        //     FUN_00bc2240/FUN_00bc23d0 ... }
    }

    switch (*(int*)arg1) {
    case 0:  goto out;
    case 1:  SP_normalized_safe(0, 0, 1.0f, 2.0f);
             cSPCreatureBase_MoveToPointAndFacingAtSpeed(param_1, 2, 0, 0.0f, 0, 0);
             return 1;
    case 2:  // walk to the current goal
             cSPCreatureBase_MoveToPointAtSpeed(param_1, 0, 0.0f);
             return 1;
    case 3:  cSPCreatureBase_SetSprinting(param_1, 1);
             return 1;
    case 4:  cSPCreatureBase_PlayAnimation(param_1, 0);
             return 1;
    case 5:  cSPCreatureBase_InterruptAnimation(param_1, 0);
             cSPCreatureBase_PlayIdleAnimation(param_1);
             return 1;
    case 6:  cSPCreatureBase_Attack(param_1, 0);
             return 1;
    default: break;
    }
out:
    return 1;
}
