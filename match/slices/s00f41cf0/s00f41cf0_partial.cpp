// Slice s00f41cf0 -- partial skeletons for the three large action-evaluator state machines.
// These are NOT in manifest.txt: they are incomplete (control flow not reconstructed) and are
// kept in a separate translation unit so they cannot perturb the byte-exact functions in
// s00f41cf0.cpp (0x00f42a00 must call Eval427c0 out of line, which a same-TU definition breaks).
#include "types.h"

struct Action {
    int32_t mType, mParam1, mParam2, mParam3;
    char    pad10[0x188 - 0x10];
};

struct ScenarioObjSkeleton {
    char pad00[0x10];
    void* mpManager;      // +0x10
    char pad14[0x8c - 0x14];
    void* mpField8c;      // +0x8c

    // @ 0x00f427c0
    void Eval427c0();
    // @ 0x00f41dc0
    char f_41dc0(Action* a, int idx, void* p);
    // @ 0x00f420d0
    char f_420d0(int idx, Action* a, int n, int* out, void* p);
};

// @ 0x00f427c0
// Drives per-tutorial action evaluation: for each tutorial, for each action, calls the
// 0x00f41dc0 state evaluator and reports whether any action became active.  Not reconstructed.
void ScenarioObjSkeleton::Eval427c0()
{
    // skeleton
}

// @ 0x00f41dc0
// Per-action state evaluator: a jump table on Action::mType (cases 1..11) drives a comparison
// against the owning tutorial's slot state and updates Action::mState (offsets +0x184).  Not
// reconstructed.
char ScenarioObjSkeleton::f_41dc0(Action* a, int idx, void* p)
{
    (void)a; (void)idx; (void)p;
    return 0;
}

// @ 0x00f420d0
// Two-pass cost evaluator over an action list, using two eastl::lower_bound lookups per action
// and updating per-action costs.  Not reconstructed.
char ScenarioObjSkeleton::f_420d0(int idx, Action* a, int n, int* out, void* p)
{
    (void)idx; (void)a; (void)n; (void)out; (void)p;
    return 0;
}
