// Slice s00bafae0: layout pass that places a row of items (0x00BAFAE0, 4542 bytes).
// Flags region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
// Reads the item count (byte +0xAC) from the container, gives every item that is not a
// "continuation" (flag bit 2) a width (by kind) and a random start position snapped to a
// 20 unit grid, then relaxes overlaps between all pairs for up to 100 passes (moving
// positions inside each item's allowed [lo,hi] range, sometimes randomly), sorts the
// resulting intervals, clamps neighbours against each other and finally positions every
// item through the two placement helpers.
#include "types.h"
#include <math.h>

#pragma pack(push, 4)

template<class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

inline float ClampF(float v, float lo, float hi)
{
    // maxss / minss
    v = (v > lo) ? v : lo;
    v = (v < hi) ? v : hi;
    return v;
}

// Rounding float->int (cvtss2si, current MXCSR rounding).
inline int RoundToInt(float f)
{
    int r;
    __asm {
        cvtss2si eax, f
        mov r, eax
    }
    return r;
}

struct RandomLinearCongruential {
    int    RandomUint32Uniform(uint32_t n);     // 0x00A68FB0
    double RandomDoubleUniform();               // 0x009360D0
};
extern RandomLinearCongruential sMathRandom;    // 0x01601760

struct Interval {       // 12 bytes
    float lo, hi;
    int   index;
};

// Minimal EASTL-style vectors (begin, end, capacity) with out-of-line grow/reserve.
struct FloatVec {
    float* mpBegin; float* mpEnd; float* mpCap;
    void reserve(int n);                                // 0x004E0880
    void push_back_slow(float* pEnd, const float* v);   // 0x00455660
};
struct IntVec {
    int* mpBegin; int* mpEnd; int* mpCap;
    void reserve(int n);                                // 0x00D01790
    void push_back_slow(int* pEnd, const int* v);       // 0x00B96600
};
struct IntervalVec {
    Interval* mpBegin; Interval* mpEnd; Interval* mpCap;
    void reserve(int n);                                // 0x00BAA200
    void push_back_slow(Interval* pEnd, const Interval* v);   // 0x00BAA530
};

struct LayoutItem {
    char pad[0x28];
    int  kind;          // +0x28: 0, 1, 2
    uint32_t flags;     // +0x2c: bit 2 = continuation of the previous item
    char sub[1];        // +0x30
};

struct LayoutContainer {
    char pad[0xAC];
    uint8_t count;                  // +0xAC
    int         GetMode();          // 0x00801920
    LayoutItem* GetItem(int i);     // 0x00BBAA60
};

extern float gParam0;       // 0x0156C490
extern float gParam1;       // 0x0156C494
extern float gParam2;       // 0x0156C498
extern float gTailExtra;    // 0x0156C49C
extern float gSubLo;        // 0x0156C4A0
extern float gSubHi;        // 0x0156C4A4
extern float gKindWidth[4]; // 0x01465E94

float  GetModeParam(int mode, int which);                       // 0x00C84C60 cdecl
float* GetKindRange(float* out, int mode, int type, float w);   // 0x00BA68F0 cdecl
float  PickInRange(float* range);                               // 0x004DF2D0 cdecl
bool   IntervalLess(const Interval& a, const Interval& b);      // 0x00B72560
void operator delete[](void* p);                                 // 0x00F47380
typedef bool (*IntervalCmp)(const Interval&, const Interval&);
void   IntroLoop(Interval* first, Interval* last, int depth, IntervalCmp cmp);   // 0x00BABD30
void   InsertionSort(Interval* first, Interval* last, IntervalCmp cmp);          // 0x00BA77E0
void   UnguardedInsertion(Interval* first, Interval* last, IntervalCmp cmp);    // 0x00BA7880

struct LayoutPass {
    void PlaceItem(LayoutContainer* c, void* sub, float a, float b, LayoutItem* prev);                // 0x00BA8C40
    void PlaceExtra(LayoutItem* item, LayoutContainer* c, LayoutItem* prev, int a, int b);            // 0x00BADAE0
    void Run(LayoutContainer* c);                                                                     // 0x00BAFAE0
};

// Random value between base and target (target has priority, then base).
static inline float RandLerpClamp(float base, float target)
{
    double b = (double)base;
    double t = (double)target;
    double r = sMathRandom.RandomDoubleUniform();
    double v = r * (t - b) + b;
    if (v < t) {
        if (v < b) return (float)b;
        return (float)v;
    }
    return (float)t;
}

static inline float Snap(float v)   // round to the 20 unit grid
{
    return (float)RoundToInt(v * 0.05f) * 20.0f;
}

static inline int KindToSlot(int kind)
{
    int s = 2;
    if (kind == 0) s = 0;
    else if (kind == 1) s = 3;
    else if (kind == 2) s = 1;
    return s;
}

static inline float PushAmount(bool isZero, float overlap)
{
    if (isZero) return 20.0f;
    return Max(overlap * 0.25f, 1.0f);
}

// @ 0x00BAFAE0
void LayoutPass::Run(LayoutContainer* c)
{
    int mode = c->GetMode();
    gParam0 = GetModeParam(mode, 0);
    gParam1 = GetModeParam(mode, 1);
    gParam2 = GetModeParam(mode, 2);
    gTailExtra = Max(gParam2 + 100.0f, 400.0f);

    int count = c->count;
    FloatVec widths = { 0, 0, 0 };
    widths.reserve(count);
    FloatVec positions = { 0, 0, 0 };
    positions.reserve(count);
    IntVec types = { 0, 0, 0 };
    types.reserve(count);

    for (int i = 0; i < count; ++i) {
        LayoutItem* item = c->GetItem(i);
        int slot = KindToSlot(item->kind);
        float width = gKindWidth[slot];
        float pos = 0.0f;
        if (item->flags >> 2 & 1) {
            float w = widths.mpEnd[-1] + gKindWidth[0];
            widths.mpEnd[-1] = w;
            float tmp[2];
            float* r = GetKindRange(tmp, mode, types.mpEnd[-1], w);
            double lo = (double)r[0];
            double hi = (double)r[1];
            double rnd = sMathRandom.RandomDoubleUniform();
            double v = rnd * (hi - lo) + lo;
            float out;
            if (v < hi) {
                if (lo <= v) out = (float)v; else out = (float)lo;
            } else {
                out = (float)hi;
            }
            positions.mpEnd[-1] = out;
            continue;
        }
        if (slot == 0) {
            int rn = sMathRandom.RandomUint32Uniform(12);
            pos = (float)rn * 20.0f + 60.0f;
            float range[2];
            if (mode == 6) {
                range[0] = Max(60.0f, (float)RoundToInt(gParam2 * 0.05f) * 20.0f);
                range[1] = 280.0f;
            } else {
                range[0] = Max(60.0f, (float)RoundToInt((gParam0 + 19.0f) * 0.05f) * 20.0f);
                range[1] = 280.0f;
            }
            for (; pos < range[0]; pos += 20.0f) {}
            for (; range[1] < pos; pos -= 20.0f) {}
        } else if (slot > 0 && slot < 4) {
            float tmp[2];
            pos = PickInRange(GetKindRange(tmp, mode, slot, width));
        }
        if (types.mpEnd < types.mpCap) {
            int* p = types.mpEnd;
            types.mpEnd = p + 1;
            if (p) *p = slot;
        } else {
            types.push_back_slow(types.mpEnd, &slot);
        }
        if (widths.mpEnd < widths.mpCap) {
            float* p = widths.mpEnd;
            widths.mpEnd = p + 1;
            if (p) *p = width;
        } else {
            widths.push_back_slow(widths.mpEnd, &width);
        }
        if (positions.mpEnd < positions.mpCap) {
            float* p = positions.mpEnd;
            positions.mpEnd = p + 1;
            if (p) *p = pos;
        } else {
            positions.push_back_slow(positions.mpEnd, &pos);
        }
    }

    float* A = widths.mpBegin;
    float* B = positions.mpBegin;
    int*   C = types.mpBegin;
    int m = (int)(positions.mpEnd - positions.mpBegin);
    bool converged = false;
    int iter = 0;
    do {
        if (++iter > 100) break;
        bool changed = false;
        int i = 0;
        while (i < m) {
            float wi = A[i];
            int ti = C[i];
            bool zi = (ti == 0);
            float ri[2];
            GetKindRange(ri, mode, ti, wi);
            float loI = ri[0], hiI = ri[1];
            int next = i + 1;
            for (int j = i + 1; j < m; ++j) {
                float ov = (wi + A[j]) - fabsf(B[j] - B[i]);
                if (!(0.0f < ov)) continue;
                int tj = C[j];
                bool zj = (tj == 0);
                changed = true;
                float rj[2];
                GetKindRange(rj, mode, tj, A[j]);
                float loJ = rj[0], hiJ = rj[1];
                float pi = B[i];
                float pj = B[j];
                bool jAfter = pj > pi;
                bool jBefore = pj <= pi;
                bool doA = false;   // resolve with i on the left of j
                bool doB = false;   // resolve with j on the left of i
                if (loI == loJ && hiI == hiJ) {
                    doA = jAfter;
                    doB = jBefore;
                } else if (loI < loJ) {
                    if (hiJ < hiI) {
                        if (pi > loJ && pi < hiJ) {
                            if (sMathRandom.RandomUint32Uniform(2) == 0)
                                B[i] = RandLerpClamp(hiJ, hiI);
                            else
                                B[i] = RandLerpClamp(loI, loJ);
                            if (zi) B[i] = Snap(B[i]);
                        }
                        doA = jAfter;
                        doB = jBefore;
                    } else {
                        doA = true;
                        doB = false;
                    }
                } else if (hiJ >= hiI) {
                    if (pj > loI && pj < hiI) {
                        if (sMathRandom.RandomUint32Uniform(2) == 0)
                            B[j] = RandLerpClamp(hiI, hiJ);
                        else
                            B[j] = RandLerpClamp(loJ, loI);
                        if (zj) B[j] = Snap(B[j]);
                    }
                    doA = jAfter;
                    doB = jBefore;
                } else {
                    doA = false;
                    doB = true;
                }
                if (doA) {
                    pi = B[i];
                    pj = B[j];
                    if (pi > loI) {
                        B[i] = ClampF(pi - PushAmount(zi, ov), loI, hiI);
                        if (pj < hiJ)
                            B[j] = ClampF(B[j] + PushAmount(zj, ov), loJ, hiJ);
                    } else if (pj < hiJ) {
                        B[j] = ClampF(pj + PushAmount(zj, ov), loJ, hiJ);
                    } else {
                        B[i] = ClampF(pj, loI, hiI);
                        B[j] = ClampF(pi, loJ, hiJ);
                        if (zi) B[i] = Snap(B[i]);
                        if (zj) B[j] = Snap(B[j]);
                    }
                }
                if (doB) {
                    pi = B[i];
                    pj = B[j];
                    if (pi < hiI) {
                        B[i] = ClampF(pi + PushAmount(zi, ov), loI, hiI);
                        if (pj > loJ)
                            B[j] = ClampF(B[j] - PushAmount(zj, ov), loJ, hiJ);
                    } else if (pj > loJ) {
                        B[j] = ClampF(pj - PushAmount(zj, ov), loJ, hiJ);
                    } else {
                        B[i] = ClampF(pj, loI, hiI);
                        B[j] = ClampF(pi, loJ, hiJ);
                        if (zi) B[i] = Snap(B[i]);
                        if (zj) B[j] = Snap(B[j]);
                    }
                }
            }
            i = next;
        }
        converged = !changed;
    } while (!converged);

    IntervalVec ivs = { 0, 0, 0 };
    ivs.reserve(m);
    for (int k = 0; k < m; ++k) {
        float w = A[k];
        float pos = B[k];
        float tmp[2];
        GetKindRange(tmp, mode, C[k], w);
        Interval iv;
        iv.lo = pos - w;
        iv.hi = w + pos;
        iv.index = k;
        if (ivs.mpEnd < ivs.mpCap) {
            Interval* p = ivs.mpEnd;
            ivs.mpEnd = p + 1;
            if (p) *p = iv;
        } else {
            ivs.push_back_slow(ivs.mpEnd, &iv);
        }
    }

    if (converged) {
        Interval* first = ivs.mpBegin;
        Interval* last = ivs.mpEnd;
        if (first != last) {
            int n = (int)(last - first);
            int lg = 0;
            for (int t = n; t != 0; t >>= 1) ++lg;
            IntroLoop(first, last, lg * 2 - 2, IntervalLess);
            if (n < 0x1d) {
                InsertionSort(first, last, IntervalLess);
            } else {
                InsertionSort(first, first + 0x1c, IntervalLess);
                UnguardedInsertion(first + 0x1c, last, IntervalLess);
            }
        }
        float lastEnd = -1.0f;
        if (first != last) {
            Interval* p = first;
            bool zero;
            float w;
            float extHi;
            for (;;) {
                int k = p->index;
                int tk = C[k];
                w = A[k];
                zero = (tk == 0);
                float rr[2];
                GetKindRange(rr, mode, tk, w);
                float extLo = rr[0] - w;
                extHi = rr[1] + w;
                if (lastEnd < 0.0f) lastEnd = extLo;
                if (!zero && lastEnd < p->lo)
                    p->lo = (lastEnd > extLo) ? lastEnd : extLo;
                Interval* nx = p + 1;
                if (nx == last) break;
                if (zero) {
                    lastEnd = p->hi;
                } else if (C[nx->index] == 0) {
                    p->hi = (extHi > nx->lo) ? nx->lo : extHi;
                    lastEnd = p->hi;
                } else {
                    float mid = (p->hi + nx->lo) * 0.5f;
                    p->hi = (extHi > mid) ? mid : extHi;
                    lastEnd = p->hi;
                }
                p = nx;
            }
            if (!zero) {
                float t = w + gTailExtra;
                if (p->hi < t)
                    p->hi = (extHi > t) ? t : extHi;
            }
        }
    }

    int cursor = 0;
    LayoutItem* prev = 0;
    for (int i = 0; i < count; ++i) {
        LayoutItem* item = c->GetItem(i);
        if (item->flags >> 2 & 1) {
            PlaceItem(c, item->sub, gSubLo, gSubHi, prev);
            PlaceExtra(item, c, prev, 0, 0);
        } else {
            int slot = KindToSlot(item->kind);
            float w = gKindWidth[slot];
            gSubLo = w + 6.0f;
            gSubHi = gSubLo + 3.0f;
            for (Interval* q = ivs.mpBegin; q != ivs.mpEnd; ++q) {
                if (q->index == cursor) {
                    PlaceItem(c, item->sub, w + q->lo, q->hi - w, 0);
                    break;
                }
            }
            if (item->kind == 2)
                PlaceExtra(item, c, 0, 0, 0);
            ++cursor;
        }
        prev = item;
    }

    if (ivs.mpBegin && ((int*)ivs.mpBegin)[-1]) operator delete[](ivs.mpBegin);
    if (types.mpBegin && types.mpBegin[-1]) operator delete[](types.mpBegin);
    if (positions.mpBegin && ((int*)positions.mpBegin)[-1]) operator delete[](positions.mpBegin);
    if (widths.mpBegin && ((int*)widths.mpBegin)[-1]) operator delete[](widths.mpBegin);
}

#pragma pack(pop)
