// Slice s00898090: sample a layout pair at an index and return the first float.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct LayoutView {
    // 0x00897f90: interpolate a pair into out[0..1].
    void GetPair(int index, int firstOnly, float* out, int extra);
};

struct Wrapper {
    float Sample(int index, int firstOnly, int extra);   // 0x00898090
};

// @ 0x00898090
float Wrapper::Sample(int index, int firstOnly, int extra)
{
    float local[2] = { 0.0f, 0.0f };
    ((LayoutView*)this)->GetPair(index, firstOnly, local, extra);
    return local[0];
}