// Slice s009f2970: 0x009f2a00 (2443 bytes). PARTIAL, not started beyond the signature.
// Signature from the asm: __thiscall, two stack pointer args (ebx = arg1, ebp = arg2), ret 8,
// returns a float* in eax (pfVar5 in the Ghidra decompile). Body starts with a loop over
// IKContext::Update (0x009f1990, thiscall, one pushed pointer) for [this+0x208] entries.
#include "types.h"

namespace SP {
struct cIKStub
{
    float* Solve(void* ctx, void* pose);     // 0x009f2a00, thiscall, ret 8
};
}

float* SP::cIKStub::Solve(void* ctx, void* pose)
{
    // TODO: whole body, see partial.txt.
    (void)ctx;
    (void)pose;
    return 0;
}
