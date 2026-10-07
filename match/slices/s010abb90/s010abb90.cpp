// slice s010abb90: FUN_010abb90 (0x010abb90, 2496 bytes). Matrix-chain update over param_3 segments
// (3x3 per-segment accumulate with the 0x90-byte stride and 0x24-float output stride).
// PARTIAL: loop structure from the Ghidra decompile only; the asm was not checked against it, the
// calling convention is doubtful (plain ret, so the stack args are caller-cleaned), and FUN_01081c30 /
// FUN_01081da0 are not identified. See partial.txt.
#include "types.h"

void Mat4MulAccumulate(float* out, const float* a, const float* b);   // FUN_01081c30 (unverified)
void Mat4Normalize(float* m);                                         // FUN_01081da0 (unverified)

void SegmentChainUpdate(int* seg, int base, int count, float weight, int srcOff, int dstOff)
{
    float local[13] = {0};
    int idx = 0;
    if (count > 0) {
        int* cur = seg;
        int  acc = 0;
        float prev = 0.0f;
        do {
            // per-segment 3x3 accumulate: 3 rows of 4 dot products (the full body is unported)
            for (int row = 0; row < 3; ++row) {
                (void)row;
            }
            (void)cur; (void)acc; (void)prev; (void)weight; (void)srcOff; (void)dstOff; (void)local;
            ++idx;
            acc += 0x90;
            cur = cur + 1;
        } while (idx < count);
    }
}
