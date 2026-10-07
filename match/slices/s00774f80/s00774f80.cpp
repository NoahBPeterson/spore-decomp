// slice s00774f80: SP::cRuntimeModelBuilder comparison / copy helpers with EH
// frames and inlined EASTL vectors.  Not reconstructed byte-for-byte; kept as
// signature-only skeletons so the slice compiles (partial).
#include "types.h"

// @ 0x00774f80  compare a model builder's mesh arrays and sort/compare elements
int FUN_00774f80(int param_1, int param_2) {
    (void)param_1;
    (void)param_2;
    return 0;
}

// @ 0x00775230
void FUN_00775230(int param_1, int* param_2) {
    (void)param_1;
    (void)param_2;
}

// @ 0x007754d0  __alloca_probe frame, builds an index table
int FUN_007754d0(int param_1, int param_2) {
    (void)param_1;
    (void)param_2;
    return 0;
}

// @ 0x007756b0  push_back of a 0x20-byte element into a vector (EH frame)
void FUN_007756b0(int param_1, void* param_2) {
    (void)param_1;
    (void)param_2;
}
