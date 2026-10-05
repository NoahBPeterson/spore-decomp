// Slice s00448fa0: cSPEditorBlock / bounding-box /Od /Ob1 helpers plus
// SP::normalized_safe (byte-exact).
// Flags: /Od /Ob1 /Oi /MD /EHsc /TP /arch:SSE /fp:fast /Gy
#include "types.h"
#include <math.h>

float* sub_453880(float* tmp, const float* v, float* s);

// @ 0x00449c20  SP::normalized_safe  (byte-exact)
float* normalized_safe(float* out, const float* v)
{
    float v1 = v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + 1e-8f;
    float p15 = sqrtf(v1);
    float n20[3];
    float* owner = sub_453880(n20, v, &p15);
    out[0] = owner[0];
    out[1] = owner[1];
    out[2] = owner[2];
    return out;
}

// ---------------------------------------------------------------------------
// Remaining functions are 1-2 KB /Od methods; skeletons only (partial.txt).
// ---------------------------------------------------------------------------
struct Blk {
    void A48fa0();
    void A49420(int a, char b);
    void A494b0();
    void A49ce0();
    void A49d40(int a);
};

// @ 0x00448fa0
void Blk::A48fa0()
{
}

// @ 0x00449420
void Blk::A49420(int, char)
{
}

// @ 0x004494b0
void Blk::A494b0()
{
}

// @ 0x00449ce0
void Blk::A49ce0()
{
}

// @ 0x00449d40
void Blk::A49d40(int)
{
}
