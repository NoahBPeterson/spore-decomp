// Slice s00c41dc0: 0x00c41dc0, pick which pair of three consecutive 12-byte records
// (`v[0]`, `v[1]`, `v[2]`) to blend: it measures the 0x00698b30 distance from the point
// `p` to the segments [v0,v1], [v1,v2] and [v2,v0], keeps the winning index, and copies
// that pair out to the two out-parameters.
//
// Arg 2 is NOT a pointer and there are only four parameters: the argument area holds
// `v` at [esp+4], one 12-byte point passed by value at [esp+8] (>[esp+0x10]), and the
// two out pointers at [esp+0x14] / [esp+0x18]. Every distance call gets the address of
// that in-place point (`lea eax,[esp+0x20]`); cl also spills `d0` into the dead `v`
// argument slot at [esp+4] (retail) and keeps `d1` in the `push ecx` local at [esp-4].
//
// `index` must be declared (and initialised) before the two distance calls: that is what
// makes cl hoist `xor ebp,ebp` to just before the first call, keeping ebp as the switch
// selector. Declared after the calls it lands in a stack slot and shifts every later
// call/displacement by three bytes.
//
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

struct Vec3 { float x, y, z; };

// 0x00698b30 (cdecl, float in st0): distance from p to the segment [a, b].
float SegmentDistance(const Vec3* p, const Vec3* a, const Vec3* b);

// @ 0x00c41dc0
void ChoosePair(const Vec3* v, Vec3 p, Vec3* out0, Vec3* out1)
{
    int index = 0;
    float d0 = SegmentDistance(&p, &v[0], &v[1]);
    float d1 = SegmentDistance(&p, &v[1], &v[2]);
    if (d0 > d1) {
        index = 1;
        d0 = d1;
    }
    if (d0 > SegmentDistance(&p, &v[2], &v[0]))
        index = 2;

    switch (index) {
    case 0:
        *out0 = v[0];
        *out1 = v[1];
        break;
    case 1:
        *out0 = v[1];
        *out1 = v[2];
        break;
    default:
        *out0 = v[2];
        *out1 = v[0];
        break;
    }
}
