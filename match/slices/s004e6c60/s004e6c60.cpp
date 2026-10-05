// w1g1 slice s004e6c60 -- a small /O2 colour-scale helper plus two large /Od
// body builders (skeletons).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE for the float helper.

typedef unsigned int uint32_t;

// @ 0x004e7460
// Scales an RGB triple for a colour-variation "kind" (0/1/2).  Each output is
// initialised to 1.0 and then combined with the input channels using per-kind
// multipliers.
void ScaleColorForKind(int kind, float r, float g, float b,
                       float* pR, float* pG, float* pB)
{
    *pR = 1.0f;
    *pG = 1.0f;
    *pB = 1.0f;

    if (kind == 0) {
        *pR = *pR * 10.0f + r * 20.0f;
        *pG = *pG * 150.0f + g * 300.0f;
        *pB = *pB * 5.0f + b * 20.0f;
    }
    if (kind == 1) {
        *pR = *pR * 15.0f + r * 30.0f;
        *pG = *pG * 200.0f + g * 400.0f;
        *pB = *pB * 5.0f + b * 20.0f;
    }
    if (kind == 2) {
        *pR = *pR * 10.0f + r * 20.0f;
        *pG = *pG * 150.0f + g * 300.0f;
        *pB = *pB * 10.0f + b * 40.0f;
    }
}

// @ 0x004e6c60
// 2045-byte /Od editor verb-icon builder.  Skeleton.
void BuildVerbIcons(void* self, void* out)
{
    (void)self; (void)out;
}

// @ 0x004e7610
// 887-byte /Od verb-icon data builder.  Skeleton.
void BuildVerbIconData(void* list, void* out, void* owner)
{
    (void)list; (void)out; (void)owner;
}
