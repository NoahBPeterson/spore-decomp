// slice s009d3950 -- nSPCreatureAnim gait-dynamics block (record heap helpers,
// bone-weight blending and the gait state machine).
//
// Every VA is unnamed in the dev PDB (the build post-dates it); the field offsets are the
// retail ones recovered from the disassembly.  The retail __thiscall functions take their
// object in ecx, so they are declared as members of the classes below (VC9 rejects
// __thiscall on free functions).
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include <math.h>

typedef unsigned char  uint8;
typedef unsigned int   uint32;
typedef unsigned short uint16;

typedef long double float10;

// ====================================================================== external code
// 0x009d3790 / 0x009d3840 / 0x009d3710 are __thiscall siblings living in other slices.

// ====================================================================== records
// 0x108-byte animation record (layout recovered in slices/s009cddf0/s009cddf0.cpp:
// FUN_009cddf0 fills it, FUN_009ce790 copies it, fac at +0xac is the sort key).
struct SA {
    float f00, f04, f08, f0c;                       // 0x00
    float f10, f14, f18, f1c;                       // 0x10
    float f20, f24, f28, f2c;                       // 0x20
    float f30, f34, f38, f3c;                       // 0x30
    float f40;                                      // 0x40
    int   i44, i48;                                 // 0x44
    float f4c;                                      // 0x4c
    int   i50;                                      // 0x50
    float f54;                                      // 0x54
    int   i58;                                      // 0x58
    uint8 b5c, b5d; uint8 pad5e[2];                 // 0x5c
    float f60;                                      // 0x60
    int   i64, i68;                                 // 0x64
    float f6c, f70, f74, f78, f7c, f80, f84, f88;   // 0x6c
    float f8c, f90, f94, f98, f9c, fa0, fa4, fa8;   // 0x8c
    float fac;                                      // 0xac
    int   iB0;                                      // 0xb0
    float fB4, fB8, fBC, fC0;                       // 0xb4
    int   iC4, iC8;                                 // 0xc4
    float fCC, fD0, fD4, fD8, fDC, fE0, fE4, fE8;   // 0xcc
    float fEC, fF0, fF4, fF8, fFC, f100, f104;      // 0xec

    SA(const SA& src);                              // 0x009ce790  member-wise copy
    SA& operator=(const SA& src);                   // 0x009ce790
};

// Heap ordering on SA::fac (record + 0xac): "a before b" == a.fac > b.fac.
// The operands are taken by value -- the retail code copy-constructs both of them into
// 0x108-byte stack records before comparing (see 0x009d40c0).
struct SAGreater {
    uint32 mUnused;
    bool operator()(SA a, SA b) const { return a.fac > b.fac; }
};

// 0x009ced30  eastl::promote_heap<SA*, int, SA, SAGreater>
void __cdecl promote_heap(SA* first, int topPosition, int position, SA value, SAGreater compare);

// 0x30-byte record copied by 0x009d41b0 (two ints then ten floats).  The copy walks the
// fields (mov for the ints, fld/fstp for the floats) rather than issuing a block move, so
// its assignment operator is written out.
struct R30 {
    int   i0, i4;                                   // 0x00
    float f8, fc;                                   // 0x08
    float f10[8];                                   // 0x10

    R30& operator=(const R30& o)
    {
        i0 = o.i0;
        i4 = o.i4;
        f8 = o.f8;
        fc = o.fc;
        f10[0] = o.f10[0];
        f10[1] = o.f10[1];
        f10[2] = o.f10[2];
        f10[3] = o.f10[3];
        f10[4] = o.f10[4];
        f10[5] = o.f10[5];
        f10[6] = o.f10[6];
        f10[7] = o.f10[7];
        return *this;
    }
};

// 0x104-byte weight record held by the AnimDyn vector at +0x10 (see 0x009d3b50).
struct Obj2;
struct Bone {                                       // the object the record points at (+0x48)
    uint8  _00[0x4c];
    float  f4c, f50, f54;                           // 0x4c
    uint8  _58[0x64 - 0x58];
    float  f64;                                     // 0x64
    uint8  _68[0x80 - 0x68];
    float  f80;                                     // 0x80
};

struct Rec {
    uint8  _00[0x48];
    void*  p48;                                     // 0x48  -> Bone
    uint8  _4c[0xa4 - 0x4c];
    float  fA4;                                     // 0xa4
    float  fA8, fAC, fB0, fB4;                      // 0xa8
    uint8  _b8[0xd0 - 0xb8];
    float  fD0;                                     // 0xd0
    uint8  _d4[0x104 - 0xd4];
};

// Gait state machine object (the "this" of 0x009d3f70).
struct GaitState {
    int    state;                                   // 0x00
    int    prev;                                    // 0x04
    float  f08;                                     // 0x08
    float  f0c;                                     // 0x0c
    uint8  _10[0x38 - 0x10];
    void*  p38;                                     // 0x38  begin of the 0x30-byte record vector
    void*  p3c;                                     // 0x3c  end

    void   FUN_009d3f70(Obj2* p);                   // 0x009d3f70
};

// ====================================================================== the "instances"
// Creature instance (the argument object of the gait helpers).
struct Obj2 {
    void*  p00;                                     // 0x00  -> [p00 + 0x3ec] float
    uint8  _04[0x70 - 0x04];
    float  f70;                                     // 0x70
    uint8  _74[0x84 - 0x74];
    float  f84;                                     // 0x84
    float  f88;                                     // 0x88
    uint8  _8c[0xa8 - 0x8c];
    float  fa8, fac, fb0, fb4;                      // 0xa8
    uint8  _b8[0xf8 - 0xb8];
    float  ff8;                                     // 0xf8
    uint8  _fc[0x2d5 - 0xfc];
    uint8  b2d5;                                    // 0x2d5
    uint8  _2d6[0x1684 - 0x2d6];
    int    i1684;                                   // 0x1684
};

// 3-float vector: the output buffer of 0x009cede0.
struct vector_3 { float x, y, z; };

// The object at pC8 + 0x15b8 (the receiver of 0x009d3530).
struct GaitBlk {
    double FUN_009d3530();                          // 0x009d3530
};

// The gait/IK solver object ("this" of the block below).
struct AnimDyn {
    float  f00, f04, f08;                           // 0x00
    uint8  _0c[0x10 - 0x0c];
    void*  p10;                                     // 0x10  begin of the 0x104-byte record vector
    void*  p14;                                     // 0x14  end
    float  f18, f1c, f20;                           // 0x18  outputs of 0x009d42b0
    uint8  _24[0x4c - 0x24];
    float  f4c, f50, f54;                           // 0x4c
    int    i58;                                     // 0x58
    uint8  _5c[0x64 - 0x5c];
    float  f64, f68;                                // 0x64
    uint8  _6c[0x78 - 0x6c];
    float  f78, f7c, f80, f84;                      // 0x78
    uint8  _88[0xc0 - 0x88];
    float  fC0;                                     // 0xc0
    uint8  _c4[0xc8 - 0xc4];
    void*  pC8;                                     // 0xc8
    uint8  _cc[0xd0 - 0xcc];
    float  fD0, fD4, fD8;                           // 0xd0
    float  fDC, fE0, fE4, fE8, fEC, fF0, fF4;       // 0xdc
    float  fF8, fFC;                                // 0xf8

    float  FUN_009d3790(float t);                   // 0x009d3790
    float  FUN_009d3840(int x);                     // 0x009d3840
    float  FUN_009d3710(Obj2* p, float a, float b); // 0x009d3710
    float  FUN_009d3950(Obj2* p, float dt, int x);  // 0x009d3950
    float  FUN_009d3a20(Obj2* p, float a, int x, float b);  // 0x009d3a20
    void   FUN_009d3b50(float t);                   // 0x009d3b50
    vector_3* SampleBlendPos(vector_3* out, float t);        // 0x009cede0
    float     CalcBendBlendFactor(Obj2* pRoot, float t);     // 0x009cf740
    void   FUN_009d42b0(Obj2* p);                   // 0x009d42b0
};

// ------------------------------------------------------------------ globals
extern float DAT_01551258;   // distance threshold
extern float DAT_01551500;   // sqrt domain constant
extern float DAT_01551504;   // gait time scale
extern float DAT_015515dc;   // gait blend toggle
extern char  DAT_01551256;   // gait bend toggle
extern float DAT_01551508;   // bend blend scale
extern float DAT_0155150c;   // hermite range
float  LengthSqVec3(const float* v);                             // 0x009a49b0
float  FUN_009cdbe0(float, float, float, float, float);          // 0x009cdbe0 cdecl

// 0x009cddc0 is a TU-local `static` helper (also reconstructed in s009ccfe0);
// cl gives TU-local statics a register convention (arg1 in xmm0, arg2 in xmm1,
// the float result in xmm0), which only reproduces with a same-TU definition,
// so 0x009d42b0 keeps a private copy of it here.  Only its signature and
// result matter for this slice.
static float FUN_009cddc0(float /*unused*/, float v)
{
    if (v < 1e-06f)
        return -1.0f;
    if (1e-06f < v)
        return 1.0f;
    return 0.0f;
}

// ======================================================================
// @ 0x009d3950
//   bone-weight scale: sqrt(|v|^2)/blend * bone-factor, or the 1.1f variant when the
//   instance is in "flattened" pose.
// ======================================================================
float AnimDyn::FUN_009d3950(Obj2* p, float dt, int x)
{
    float r = 0.0f;
    if (f4c * f4c + f50 * f50 + f54 * f54 > DAT_01551258) {
        float a = FUN_009d3790(dt);
        if (1e-06f < a) {
            float b = FUN_009d3840(x);
            if (p->b2d5 != 0)
                r = ((f08 / a) * b) * 1.1f;
            else
                return sqrtf(f4c * f4c + f50 * f50 + f54 * f54) / a * b;
        }
    }
    return r;
}

// ======================================================================
// @ 0x009d3a20
//   blend factor: (bone factor + pose term + 1/sqrt(k)) squared, inverted and clamped
//   against the two per-axis weight lookups.  The min/max helpers return their argument
//   by reference -- that is what makes the retail code materialise both candidates into
//   stack slots and select the slot address.
// ======================================================================
template <class T> inline const T& eastl_max(const T& a, const T& b) { return (a < b) ? b : a; }

// 0x166c69c / 0x166c6a0 are the function-local `static float sScale =
// 1.0f/sqrtf(DAT_01551500)` and its guard dword (bit 0).  Both are named by their retail
// addresses and the guard is written by hand so the cached value lands in the same .data
// slot as the original's -- a C++ function-local static would get a fresh slot.
extern float  DAT_0166c69c;                             // sScale
extern uint32 DAT_0166c6a0;                             // its guard dword

float AnimDyn::FUN_009d3a20(Obj2* p, float a, int x, float b)
{
    float sScale = (DAT_0166c6a0 & 1) ? DAT_0166c69c
                                      : (DAT_0166c6a0 |= 1, DAT_0166c69c = 1.0f / sqrtf(DAT_01551500));

    // lo = per-axis extent, hi = pose term; the two branches differ only in the lo term
    // (sqrt(f70)*sqrt(|v|^2) vs sqrt(f70)*f08) and the retail keeps both on the x87 stack.
    float sum = (p->b2d5 != 0)
        ? sqrtf(p->f70) * f08 + fabsf(f64 * 0.31830987f)
        : sqrtf(p->f70) * sqrtf(f4c * f4c + f50 * f50 + f54 * f54) + fabsf(f64 * 0.31830987f);

    float q = sum + sScale;
    float d = 1.0f / (q * q);

    float r1 = FUN_009d3950(p, a, x);
    float r2 = FUN_009d3710(p, a, b);
    float m = eastl_max(r1, r2);
    float n = eastl_max(m, d);
    float v = f80 * n;
    return eastl_max(v, 0.1f);
}

// ======================================================================
// @ 0x009d3b50
//   advance the bone-weight table: rescale every 0x104-byte record by the new time.
// ======================================================================
void AnimDyn::FUN_009d3b50(float t)
{
    f7c = f78;
    f78 = t;

    int    count = (int)((char*)p14 - (char*)p10) / 0x104;
    Rec*   base  = (Rec*)p10;
    for (int i = 0; i < count; ++i) {
        Rec* rec = base + i;
        float f  = rec->fD0 * f78;
        rec->fA4 = f;
        if (f < 0.001f) {
            rec->fA8 = 0.0f;
            rec->fAC = 0.0f;
            rec->fB0 = 0.0f;
            rec->fB4 = 0.0f;
        }
        else {
            Bone* b   = (Bone*)rec->p48;
            float inv = 1.0f / f;
            rec->fA8  = (b->f4c * inv) * b->f80;
            rec->fAC  = (b->f50 * inv) * b->f80;
            rec->fB0  = (b->f54 * inv) * b->f80;
            rec->fB4  = (b->f64 / rec->fA4) * b->f80;
        }
    }
}

// ======================================================================
// @ 0x009d3f70
//   gait state machine: 0 idle, 1 start, 2 stride, 3 stop.
// ======================================================================
void GaitState::FUN_009d3f70(Obj2* p)
{
    float v = *(float*)((char*)p->p00 + 0x3ec);

    prev  = state;
    int n = (int)((char*)p3c - (char*)p38) / 0x30;
    float h = (1.0f - DAT_01551504) * 0.2f;
    if (n != 0) {
        state = 3;
        return;
    }

    // DAT_01551504 is the gait time scale; the retail reloads it per use instead of
    // keeping it in a named local (which would take a stack home and a frame slot).
    bool b3 = (f08 * p->f70 <= DAT_01551504 * v) && (fabsf(f0c) <= DAT_01551504 * 0.2f);
    bool b5 = ((1.0f - DAT_01551504) * v < f08 * p->f70) || (h < fabsf(f0c));
    bool b4 = (p->i1684 == 0) && (fabsf(f0c) <= h);

    switch (state) {
    case 0:
        if (!b3 && !b4) {
            state = 1;
            return;
        }
        break;
    case 1:
        if (!b3) {
            if (!b5) return;
            if (b4) return;
            state = 3;
            return;
        }
        goto setState2;
    case 2:
        if (b3 || b4) {
            state = 0;
            return;
        }
        if (b5) {
            state = 1;
            return;
        }
        break;
    case 3:
        if (b5 && !b4)
            return;
    setState2:
        state = 2;
    }
}

// ======================================================================
// @ 0x009d40c0
//   eastl::adjust_heap<SA*, int, SA, SAGreater>
// ======================================================================
void adjust_heap(SA* first, int topPosition, int heapSize, int position, SA value, SAGreater compare)
{
    int childPosition = (2 * position) + 2;
    while (childPosition < heapSize) {
        if (compare(first[childPosition], first[childPosition - 1]))
            --childPosition;
        first[position] = first[childPosition];
        position = childPosition;
        childPosition = (2 * position) + 2;
    }
    if (childPosition == heapSize) {
        first[position] = first[childPosition - 1];
        position = childPosition - 1;
    }
    promote_heap(first, topPosition, position, value, compare);
}

// ======================================================================
// @ 0x009d41b0
//   eastl::copy over the 0x30-byte records; returns one past the last written record.
// ======================================================================
R30* copy30(R30* first, R30* last, R30* result)
{
    for (; first != last; ++first, ++result)
        *result = *first;
    return result;
}

// ======================================================================
// @ 0x009d4230
//   eastl::pop_heap<SA*, SAGreater>
// ======================================================================
void pop_heap(SA* first, SA* last, SAGreater compare)
{
    const SA tempBottom(*(last - 1));
    *(last - 1) = *first;
    adjust_heap(first, 0, (int)(last - first - 1), 0, tempBottom, compare);
}

// ======================================================================
// @ 0x009d42b0
//   per-frame foot placement: rebuild the local rotation (0xdc/0xe0/0xe4/
//   0xec/0xfc) and the three output positions at +0x18.  The original leaves
//   EAX undefined at both exits (it computes no return value).
// ======================================================================
void AnimDyn::FUN_009d42b0(Obj2* p)
{
    if (DAT_015515dc == 0 || f64 == 0.0f || f68 == 0.0f)
        fF8 = cosf((1.0f - p->f88) * 1.5707964f);
    else
        fF8 = 0.0f;

    float half = fF8 * -0.5f;
    float t    = f78;
    fE4 = t * (p->fb0 * half);
    fDC = t * (p->fa8 * half);
    fE0 = t * (p->fac * half);
    fFC = 1.0f;
    fEC = (p->fb4 * t) * -0.5f;

    if (DAT_015515dc == 0 || f64 == 0.0f || f68 == 0.0f) {
        f18 = 0.0f;
        f1c = 0.0f;
        f20 = 0.0f;
        return;
    }

    float    l20  = f80;
    float    f84u = f84;
    vector_3 out;
    SampleBlendPos(&out, 0.0f);                                     // 0x009cede0

    float d = (float)((GaitBlk*)((char*)pC8 + 0x15b8))->FUN_009d3530();  // 0x009d3530
    float e = CalcBendBlendFactor(p, d);                            // 0x009cf740
    fF4  = e;
    f84u = e * out.z + f84u;

    float f15 = p->ff8;
    float s   = 1.0f;
    if (DAT_01551256 != 0) {
        // the first argument is the pose length, not f7c (the retail reloads it from
        // that local's slot, which still holds the 0x009d3530 result here)
        float r = FUN_009cdbe0(d, 0.0f, DAT_0155150c, 0.0f, 1.0f);  // 0x009cdbe0
        s = 1.0f - r * fC0;
    }

    // f7c is read only now: the calls above may write it, so the retail reloads it here
    float x  = f7c;
    float sg = (x < 1e-06f) ? -1.0f : ((x > 1e-06f) ? 1.0f : 0.0f);
    float xa = ((x - f15) * p->f84) * s + f15;
    xa = (sg * e * out.x) + xa;

    int* vec = (int*)((char*)pC8 + 0x15dc);
    if (vec != 0 && (vec[1] - vec[0]) / 0x108 == 2) {
        float* tbl = (float*)(*(int*)pC8 + 0x384 + i58 * 0x468);
        float  B   = tbl[0x4f];                                 // +0x13c
        float  A   = tbl[0x4e];                                 // +0x138
        float  fv2 = fabsf(f7c) - A;
        if (fv2 > 1e-06f && B / fv2 <= 1.0f) {
            float r = LengthSqVec3(&fD0);                           // 0x009a49b0
            if (DAT_01551258 < r) {
                float sg2 = FUN_009cddc0(fv2, f7c);                 // 0x009cddc0
                float bf  = fD0;
                if (fv2 > 1e-06f)
                    bf = (bf / fv2) * sg2;
                if (bf <= -1.0f)
                    bf = -1.0f;
                else if (bf > 1.0f)
                    bf = 1.0f;
                l20 = l20 - ((bf * DAT_01551508) * (fabsf(fD0) / sqrtf(r))) * B;
            }
        }
    }

    float X  = fD0 * out.y + xa;
    float Y  = fD4 * out.y + l20;
    float Z  = fD8 * out.y + f84u;
    float sn = sinf(fEC);
    float cs = cosf(fEC);
    f18 = f00 - (cs * X - sn * Y);
    f1c = f04 - (cs * Y + sn * X);
    f20 = f08 - Z;
}
