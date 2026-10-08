// w1g1 slice s004e6c60 -- a small /O2 colour-scale helper plus two large /Od
// body builders (skeletons).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE for the float helper.

typedef unsigned int uint32_t;

// math.h with a plain (non-dllimport) floor(): calls go through the local CRT thunk 0x011e0906.
#define _CRTIMP
#include <math.h>

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
// Normalises three non-negative amounts to integer percentages that sum to exactly 100.
// pct = v / max(total, 20) * 100; then (unless the total was clamped up to 20) the floors are
// summed and the 0..3 missing points go to the entries with the largest fractional remainders.
struct PctItem {
    char  pad[0x18];
    float amount;     // +0x18
    float pad2;
    float pct;        // +0x20
};

// NB: the odd local names (n5, v33, ...) are chosen so the /Od hash-ordered frame slots match.
// Roles: n5=amountA, v33=amountB, obj=amountC, nSize=minTotal(20), begin=total, p19=clamped,
//        n22=floor sum, p22/left/t38 = fractional remainders of a/b/c.
void NormalizePercents(PctItem* a, PctItem* b, PctItem* c)
{
    float n5 = a->amount;
    float v33 = b->amount;
    float obj = c->amount;
    float nSize = 20.0f;
    float begin = n5 + v33 + obj;
    bool p19 = false;
    if (nSize > begin) {
        begin = nSize;
        p19 = true;
    }
    a->pct = n5 / begin * 100.0f;
    b->pct = v33 / begin * 100.0f;
    c->pct = obj / begin * 100.0f;
    if (!p19) {
    float n22 = floor(a->pct) + floor(b->pct) + floor(c->pct);
    float p22 = a->pct - floor(a->pct);
    float left = b->pct - floor(b->pct);
    float t38 = c->pct - floor(c->pct);

    if (n22 == 100.0f) {
        a->pct = floor(a->pct);
        b->pct = floor(b->pct);
        c->pct = floor(c->pct);
    } else if (n22 == 99.0f) {
        if (p22 >= left && p22 >= t38) {
            a->pct = 1.0f + floor(a->pct);
            b->pct = floor(b->pct);
            c->pct = floor(c->pct);
        } else if (left >= p22 && left >= t38) {
            b->pct = 1.0f + floor(b->pct);
            a->pct = floor(a->pct);
            c->pct = floor(c->pct);
        } else {
            c->pct = 1.0f + floor(c->pct);
            b->pct = floor(b->pct);
            a->pct = floor(a->pct);
        }
    } else if (n22 == 98.0f) {
        if (left >= t38 && p22 >= t38) {
            a->pct = 1.0f + floor(a->pct);
            b->pct = 1.0f + floor(b->pct);
            c->pct = floor(c->pct);
        } else if (p22 >= left && t38 >= left) {
            b->pct = floor(b->pct);
            a->pct = 1.0f + floor(a->pct);
            c->pct = 1.0f + floor(c->pct);
        } else {
            c->pct = 1.0f + floor(c->pct);
            b->pct = 1.0f + floor(b->pct);
            a->pct = floor(a->pct);
        }
    } else {
        c->pct = 1.0f + floor(c->pct);
        b->pct = 1.0f + floor(b->pct);
        a->pct = 1.0f + floor(a->pct);
    }
    }
}

// @ 0x004e7610
// 887-byte /Od verb-icon data builder.  Skeleton.
void BuildVerbIconData(void* list, void* out, void* owner)
{
    (void)list; (void)out; (void)owner;
}
