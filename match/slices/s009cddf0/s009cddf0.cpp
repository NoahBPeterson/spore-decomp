// slice s009cddf0 -- nSPCreatureAnim creature-animation block/transform helpers.
//
// All 17 VAs are unnamed in the dev PDB (the build post-dates it); field offsets are the
// retail ones recovered from the disassembly, exposed as the `SA` record below (size 0x108).
// The retail __thiscall functions take the record in ecx, so they are declared as SA members
// (VC9 rejects __thiscall on free functions).
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include <math.h>

typedef unsigned char uint8;

// -------------------------------------------------------------------- external code
float __cdecl FUN_009b3c10(float x, float y);                       // 0x009b3c10
// 0x009dd440 is __thiscall(self, float* out, float t) returning `out`.
struct CurveOut { float v0, v1, v2, v3, v4, v5, v6; };            // 28-byte key-eval result
struct cCurveKey { void* __thiscall eval(void* out, float t); };

// -------------------------------------------------------------------- constants
extern float DAT_01485720;   // 1.0f
extern float DAT_01471064;   // 0.5f
extern float DAT_013ec480;   // 0.2f
extern float DAT_01485ac0;   // 0.7f
extern float DAT_01551474;   // 0.15f
extern float DAT_013eb8a0;   // 0.25f
extern float DAT_01485544;   // 0.75f
extern float DAT_014479a4;   // pi
extern float DAT_01470f1c;   // 2.0f
extern float DAT_0155145c;   // 2*pi

// -------------------------------------------------------------------- record
// 0x108-byte animation-record.  Layout recovered from FUN_009ce790 (a member-wise copy).
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

    void   FUN_009cddf0(int p1, float p2, float p3, float p4,
                        float p5, float p6, float p7, float p8);
    float  FUN_009cdfb0(float t);
    float  FUN_009ce100(char flag);
    float  FUN_009ce150(int idx, int* ptr, float a, float b, float c);
    float* FUN_009ce370(float* out, void* ptr, float a, float b, float c);
    void   FUN_009ce5e0();
    void   FUN_009ce720(int* a, int* b);
    void   FUN_009ce740(float x);
    void   FUN_009ce790(SA* src);
};

// =====================================================================
// @ 0x009cddf0
//   big record constructor: this + int + 7 floats (ret 0x20).
// =====================================================================
void SA::FUN_009cddf0(int p1, float p2, float p3, float p4,
                      float p5, float p6, float p7, float p8)
{
    f04 = p3;
    f00 = p2;
    f08 = p4;
    f0c = p2;
    f10 = f04;
    f14 = f08;
    f18 = 0.0f;
    f1c = 0.0f;
    f20 = 0.0f;
    f24 = p5;
    f28 = p6;
    f2c = p7;
    f30 = p8;
    f34 = f24;
    f38 = f28;
    f3c = f2c;
    f40 = f30;
    f4c = 0.5f;
    i48 = 0;
    i44 = 0x47f0b3dc;
    f54 = 1.0f;
    f60 = 0.0f;
    b5d = 0;
    i68 = 0;
    i64 = 0;
    f7c = f00;
    f80 = f04;
    f84 = f08;
    f88 = f24;
    f8c = f28;
    f90 = f2c;
    f94 = f30;
    fa8 = 1.0f;
    fac = 1.0f;
    iB0 = 0;
    fB4 = 0.0f;
    fB8 = 0.0f;
    fBC = 0.0f;
    iC4 = 0;
    fC0 = 0.0f;
    iC8 = p1;
    fD0 = 0.0f;
    fD4 = 0.0f;
    fD8 = 0.0f;
    fDC = 0.0f;
    fE0 = 0.0f;
    fE4 = 0.0f;
    fE8 = 0.0f;
    fEC = 0.0f;
    fF0 = 0.0f;
    fF4 = 0.0f;
    f100 = 0.25f;
    fF8 = 1.0f;
    fFC = 1.0f;
    f104 = 0.75f;
}

// =====================================================================
// @ 0x009cdfb0
//   blend two keyed sub-curve lookups: (1-f60)*a[2] + f60*b[2].
// =====================================================================
float SA::FUN_009cdfb0(float t)
{
    CurveOut loc0;
    CurveOut loc1;
    void* ra = ((cCurveKey*)((char*)i64 + 0x2c))->eval(&loc0, t);
    float a = (1.0f - f60) * *(float*)((char*)ra + 8);
    void* rb = ((cCurveKey*)((char*)i68 + 0x2c))->eval(&loc1, t);
    return *(float*)((char*)rb + 8) * f60 + a;
}

// =====================================================================
// @ 0x009ce010
//   rotate quaternion `q` (object in EAX, retail LTCG register form) by `angle`/2 about Z.
// =====================================================================
void __cdecl FUN_009ce010(SA* q, float angle)
{
    float* qv = (float*)q;
    float s = sinf(angle * 0.5f);
    float c = cosf(angle * 0.5f);
    float x = qv[0], y = qv[1], z = qv[2], w = qv[3];
    qv[0] = x * c + w * 0.0f - z * 0.0f + y * s;
    qv[1] = y * c + z * 0.0f + w * 0.0f - x * s;
    qv[2] = z * c - y * 0.0f + w * s + x * 0.0f;
    qv[3] = w * c - x * 0.0f - y * 0.0f - z * s;
}

// =====================================================================
// @ 0x009ce100
//   wrap-aware span: (1-f104)+f100 when flag, else f104-f100.
// =====================================================================
float SA::FUN_009ce100(char flag)
{
    float r;
    if (flag)
        r = (DAT_01485720 - f104) + f100;
    else
        r = f104 - f100;
    return r;
}

// =====================================================================
// @ 0x009ce150
//   per-axis curve evaluation: normalises one coordinate through the [f100,f104]
//   wrap window, then maps it through the axis-specific atan2 shape.
// =====================================================================
float SA::FUN_009ce150(int idx, int* ptr, float a, float b, float c)
{
    float v = ((float*)&a)[idx] + f98;
    v = v - (float)floor((double)v);

    float lo = f100;
    float hi = f104;
    bool hiEdge = (lo > v);
    bool loEdge = (v >= hi);
    bool wrapped;
    float t;
    if (hiEdge || loEdge) {
        wrapped = true;
        if (hiEdge)
            t = ((1.0f - hi) + v) / ((1.0f - hi) + lo);
        else
            t = (v - hi) / ((1.0f - hi) + lo);
    } else {
        wrapped = false;
        t = (v - lo) / (hi - lo);
    }
    if (t > 0.0f) {
        if (t > 1.0f) t = 1.0f;
    } else {
        t = 0.0f;
    }

    if (idx == 0) {
        if (wrapped)
            return atan2f(((t - 0.5f) * fD4) * 2.0f + f80, f7c);
        return atan2f(cosf(t * DAT_014479a4) * fD4 + f80, f7c);
    }
    if (idx == 1) {
        float axis = *(float*)((char*)*ptr + 0x18);
        if (wrapped)
            return atan2f(axis, ((t - 0.5f) * fD4) * 2.0f + f80);
        return atan2f(axis, cosf(t * DAT_014479a4) * fD4 + f80);
    }
    if (idx == 2) {
        if (wrapped)
            return atan2f(f84, f7c);
        return atan2f(sinf(t * DAT_014479a4) * fF4 + f84, f7c);
    }
    return 0.0f;
}

// =====================================================================
// @ 0x009ce370
//   evaluate all three axes into `out` (ret 0x14).
// =====================================================================
float* SA::FUN_009ce370(float* out, void* ptr, float a, float b, float c)
{
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    float* pf = &f9c;
    for (int i = 0; i < 3; ++i) {
        float f = pf[i];
        out[i] = FUN_009b3c10(FUN_009ce150(i, (int*)ptr, a, b, c) - f,
                              DAT_0155145c);
    }
    return out;
}

// =====================================================================
// @ 0x009ce430
//   in-place 4-wide lerp dst[i] = a[i]*(1-t) + b[i]*t for i in [1,n).
//   (retail passes dst in arg1, n in ecx, a in eax, b in edi, t in xmm0)
// =====================================================================
void __cdecl FUN_009ce430(float* dst, int n, const float* a, const float* b, float t)
{
    for (int i = 1; i < n; ++i)
        dst[i] = a[i] * (1.0f - t) + b[i] * t;
}

// =====================================================================
// @ 0x009ce560
//   accumulate the negated tail into element 0: e[0] = 1 - sum(e[1..n-1]).
// =====================================================================
void __cdecl FUN_009ce560(float* e, int n)
{
    float s = 1.0f;
    if (n > 1) {
        for (int i = 1; i < n; ++i)
            s = s - e[i];
    }
    e[0] = s;
}

// =====================================================================
// @ 0x009ce5e0
//   reset the record's rotation/scale scratch fields.
// =====================================================================
void SA::FUN_009ce5e0()
{
    f08 = 0.0f; f04 = 0.0f; f00 = 0.0f;
    f14 = 0.0f; f10 = 0.0f; f0c = 0.0f;
    f20 = 0.0f; f1c = 0.0f; f18 = 0.0f;
    f2c = 0.0f; f28 = 0.0f; f24 = 0.0f;
    f30 = 1.0f;
    f3c = 0.0f; f38 = 0.0f; f34 = 0.0f;
    f40 = 1.0f;
    f74 = 0.0f; f70 = 0.0f;
    f84 = 0.0f; f80 = 0.0f; f7c = 0.0f;
    f90 = 0.0f; f8c = 0.0f; f88 = 0.0f;
    f94 = 1.0f;
    fa4 = 0.0f; fa0 = 0.0f; f9c = 0.0f;
    fac = 0.0f; fa8 = 0.0f;
    fBC = 0.0f; fB8 = 0.0f; fB4 = 0.0f;
    fD8 = 0.0f; fD4 = 0.0f; fD0 = 0.0f;
    fE4 = 0.0f; fE0 = 0.0f; fDC = 0.0f;
}

// =====================================================================
// @ 0x009ce700
//   saturating blend curve x*0.2 / (0.7 + x*0.2).
// =====================================================================
float __stdcall FUN_009ce700(float x)
{
    return (x * 0.2f) / (0.7f + x * 0.2f);
}

// =====================================================================
// @ 0x009ce720
//   split the first two dwords of the record into two outputs (ret 8).
// =====================================================================
void SA::FUN_009ce720(int* a, int* b)
{
    *a = *(int*)&f00;
    *b = *(int*)&f04;
}

// =====================================================================
// @ 0x009ce740
//   store clamp(1 - x*x, 0.15, 1.0) into f80.
// =====================================================================
void SA::FUN_009ce740(float x)
{
    float v = DAT_01485720 - x * x;
    if (v > DAT_01551474) { }
    else v = DAT_01551474;
    if (v > DAT_01485720)
        v = DAT_01485720;
    f80 = v;
}

// =====================================================================
// @ 0x009ce790
//   member-wise copy of the whole 0x108-byte record (dst = this, src = arg).
// =====================================================================
void SA::FUN_009ce790(SA* src)
{
    f00 = src->f00; f04 = src->f04; f08 = src->f08; f0c = src->f0c;
    f10 = src->f10; f14 = src->f14; f18 = src->f18; f1c = src->f1c;
    f20 = src->f20; f24 = src->f24; f28 = src->f28; f2c = src->f2c;
    f30 = src->f30; f34 = src->f34; f38 = src->f38; f3c = src->f3c;
    f40 = src->f40;
    i44 = src->i44; i48 = src->i48; f4c = src->f4c;
    i50 = src->i50; f54 = src->f54; i58 = src->i58;
    b5c = src->b5c; b5d = src->b5d;
    f60 = src->f60;
    i64 = src->i64; i68 = src->i68;
    f6c = src->f6c; f70 = src->f70; f74 = src->f74; f78 = src->f78;
    f7c = src->f7c; f80 = src->f80; f84 = src->f84; f88 = src->f88;
    f8c = src->f8c; f90 = src->f90; f94 = src->f94; f98 = src->f98;
    f9c = src->f9c; fa0 = src->fa0; fa4 = src->fa4; fa8 = src->fa8;
    fac = src->fac;
    iB0 = src->iB0;
    fB4 = src->fB4; fB8 = src->fB8; fBC = src->fBC; fC0 = src->fC0;
    iC4 = src->iC4; iC8 = src->iC8;
    fCC = src->fCC; fD0 = src->fD0; fD4 = src->fD4; fD8 = src->fD8;
    fDC = src->fDC; fE0 = src->fE0; fE4 = src->fE4; fE8 = src->fE8;
    fEC = src->fEC; fF0 = src->fF0; fF4 = src->fF4; fF8 = src->fF8;
    fFC = src->fFC; f100 = src->f100; f104 = src->f104;
}

// =====================================================================
// @ 0x009cea00
//   insertion sort by fac over [begin,end).
// =====================================================================
void __cdecl FUN_009cea00(SA* begin, SA* end)
{
    if (begin == end)
        return;
    for (SA* p = begin + 1; p != end; ) {
        char key[0x108];
        p->FUN_009ce790((SA*)key);
        SA* j = p;
        if (p != begin) {
            do {
                SA* q = j - 1;
                char pv[0x108];
                char kc[0x108];
                q->FUN_009ce790((SA*)pv);
                ((SA*)key)->FUN_009ce790((SA*)kc);
                if (*(float*)(kc + 0xac) <= *(float*)(pv + 0xac))
                    break;
                j->FUN_009ce790(q);
                j = q;
            } while (j != begin);
        }
        j->FUN_009ce790((SA*)key);
        p = p + 1;
    }
}

// =====================================================================
// @ 0x009ceab0
//   insertion sort by fac over a tail range (no low bound; caller supplies the hole).
// =====================================================================
void __cdecl FUN_009ceab0(SA* begin, SA* end)
{
    for (SA* p = begin; p != end; p = p + 1) {
        char key[0x108];
        p->FUN_009ce790((SA*)key);
        SA* j = p;
        for (;;) {
            SA* q = j - 1;
            char pv[0x108];
            char kc[0x108];
            q->FUN_009ce790((SA*)pv);
            ((SA*)key)->FUN_009ce790((SA*)kc);
            if (*(float*)(kc + 0xac) <= *(float*)(pv + 0xac))
                break;
            j->FUN_009ce790(q);
            j = q;
        }
        j->FUN_009ce790((SA*)key);
    }
}

// =====================================================================
// @ 0x009ceb50
//   median-of-three by fac; returns the pointer to the median record.
// =====================================================================
SA* __cdecl FUN_009ceb50(SA* a, SA* b, SA* c)
{
    if (a->fac <= b->fac) {
        if (a->fac > c->fac)
            return a;
        if (b->fac > c->fac)
            return c;
        return b;
    } else {
        if (b->fac > c->fac)
            return b;
        if (a->fac <= c->fac)
            return a;
        return c;
    }
}

// =====================================================================
// @ 0x009ced30
//   sift-up (heap insert): move `value` up from `index` while it is greater than
//   its parent, stopping at `low`.
// =====================================================================
void __cdecl FUN_009ced30(SA* base, int low, int index, SA value)
{
    char key[0x108];
    int parent = (index - 1) >> 1;
    while (index > low) {
        char pv[0x108];
        (&value)->FUN_009ce790((SA*)key);
        base[parent].FUN_009ce790((SA*)pv);
        if (*(float*)(pv + 0xac) <= *(float*)(key + 0xac))
            break;
        base[index].FUN_009ce790(&base[parent]);
        index = parent;
        parent = (index - 1) >> 1;
    }
    base[index].FUN_009ce790(&value);
}
