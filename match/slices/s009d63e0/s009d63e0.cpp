// s009d63e0 -- nSPCreatureAnim "Anim/gait/untagged" record container and the EASTL sort / heap /
// partial_sort machinery instantiated for its 0x108-byte gait record (SA), plus three animation
// step helpers of the owning class.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-   (VC9 / VS2008 SP1, the game's main toolset)
//
// Elements:
//   SA      0x108-byte gait/anim record (field layout as recovered in slice s009cddf0).
//   0x38    vector element with an owned counted buffer at +4.
//   0x104   "phase/group" record of the owning class.
// Every helper that lives outside this slice is a relocation (referenced by address only), so its
// exact name does not matter; the by-value SA copies all run through the out-of-line member-wise
// copy SA::FUN_009ce790 (0x009ce790), reproducing the retail `call 0x009ce790` sites.

typedef unsigned int u32;

#include <string.h>
#include <math.h>

// ---------------------------------------------------------------- allocator / memcpy helpers
#define EASTL_FILE                                                            \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define GAIT_NAME "Anim/gait/untagged"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                          // 0x00f473a0
void  __cdecl EastlFree(void* p);                                        // 0x00f47380
void* __cdecl FUN_011e0744(void* dst, const void* src, unsigned n);      // 0x011e0744 (game memcpy)

#define GAIT_ALLOC(n) operator new((n), GAIT_NAME, 0, 0, EASTL_FILE, 0xd1)

// ---------------------------------------------------------------- the 0x108-byte gait record
struct SA {
    float f00, f04, f08;    // +0x00, +0x04, +0x08
    char  pad0c[0x18];
    float f24, f28, f2c, f30;   // +0x24 .. +0x30
    char  pad34[0x24];
    int   i58;          // +0x58
    char  pad5c[0x1c];
    float f78;          // +0x78
    float f7c;          // +0x7c
    float f80;          // +0x80
    char  pad84[0x28];
    float fac;          // +0xac
    char  padB0[0x14];
    int   iC4;          // +0xc4
    int   iC8;          // +0xc8  (phase/group object pointer)
    char  padCc[0x10];
    float fdc;          // +0xdc
    char  padE0[0x20];
    float f100;         // +0x100
    float f104;         // +0x104

    SA(const SA& o) { FUN_009ce790((SA*)&o); }
    SA& operator=(const SA& o) { FUN_009ce790((SA*)&o); return *this; }
    void FUN_009ce790(SA* src);
};

// 4-byte comparator object; both operands are taken by value (0x108 bytes each).  Its call
// operator is inline so the comparison folds to `comiss [..+0xac]` like the retail instantiations.
struct LessFac {
    void* mp;
    bool operator()(SA a, SA b) { return a.fac > b.fac; }
};

// Free by-value comparison used inside the partition (retail inlines it there and takes both
// records by value, so each side is copied by FUN_009ce790).
inline bool FacLess(SA a, SA b) { return a.fac > b.fac; }

// Swap through an inline helper: this keeps a single reused 0x210-byte temporary like retail.
inline void swp(SA& a, SA& b) { SA tmp = a; a = b; b = tmp; }

// ---------------------------------------------------------------- containers
struct Vec38 {
    char* b;
    char* e;
    char* c;
    Vec38* DoAllocate(unsigned n, void* a);      // 0x009d6a10
};

struct VecU32 {
    u32* b;
    u32* e;
    u32* c;
    void DoInsertValue(u32* pos, const u32& v);  // 0x009d6ef0
};

struct VecSA {
    SA* b;
    SA* e;
    SA* c;
    void DoInsertValue(SA* pos, const SA& v);    // 0x009d7000
};

// ---------------------------------------------------------------- off-slice helpers
SA*  __cdecl FUN_009ceb50(SA* a, SA* b, SA* c, LessFac c1, LessFac c2);   // 0x009ceb50 median
SA*  __cdecl FUN_009cec70(SA* first, SA* last, SA* dst);                  // 0x009cec70
SA*  __cdecl FUN_009cecf0(SA* first, SA* last, SA* dstEnd);               // 0x009cecf0
int  __cdecl FUN_009d40c0(SA* first, int hole, int len, int top, SA value, LessFac cmp); // 0x009d40c0
void __cdecl FUN_009d6b50(SA* first, SA* last, LessFac cmp);              // 0x009d6b50 sort_heap

// ---------------------------------------------------------------- owning animation object
struct Elem104;   // 0x104-byte phase/group record

struct Anim {
    char  pad04[4];
    char* b4;           // +0x04
    char* e8;           // +0x08
    int   i0c;          // +0x0c
    char* p10;          // +0x10  (0x104-byte element array)
    char* p14;          // +0x14
    char  pad18[0xc];
    char* p24;          // +0x24  (0x108-byte SA array)
    char* p28;          // +0x28
    char  pad2c[0xc];
    char* p38;          // +0x38
    char  pad3c[0xc];
    void* ctx48;        // +0x48
    float f4c, f50, f54;    // +0x4c
    char  pad58[0xc];
    float f64;          // +0x64
    int   i68;          // +0x68
    float f6c;          // +0x6c
    float f70;          // +0x70
    float f74;          // +0x74
    char  pad78[0x2c];
    float fa4;          // +0xa4
    char  padA8[0x14];
    u32*  pbc;          // +0xbc  (indices into the SA table)

    void  FUN_009d2f50(void* out1, void* out2);   // 0x009d2f50
    float FUN_009d62a0(float x);                  // 0x009d62a0 (Ent::DistRadius)

    void  m63e0(void* param2);                    // 0x009d63e0
    float m65f0(float dt, void* e);               // 0x009d65f0
    void  m6700(float dt);                        // 0x009d6700
};

// 0x104-byte phase/group record (fields used by the step helpers).
struct Elem104 {
    char  pad00[0x8c];
    float f8c;          // +0x8c
    float f90;          // +0x90
    float f94;          // +0x94
    char  pad98[4];
    float f9c;          // +0x9c
    float fa0;          // +0xa0
    float fa4;          // +0xa4
    char  padA8[0x2c];
    float fd4;          // +0xd4
    float fd8;          // +0xd8
    float fdc;          // +0xdc
    char  padE0[0x24];
};

// ---------------------------------------------------------------- constants
extern const float g_14479b0;    // 1e-6f
extern const float g_1485720;    // 1.0f
extern const float g_15514e0;    // 1.0f
extern const float g_1471064;    // 0.5f
extern const float g_1447a38;    // 1.6651092f
extern const float g_1447a08;    // pi/2
extern const float g_166c7d4;    // exp clamp threshold
extern int         g_15509f0;

// ---------------------------------------------------------------- off-slice step helpers
void  __cdecl FUN_009cfb00(void* a, void* b, void* c, void* d, float e, void* f, void* g);
void  __cdecl FUN_009cfd40(void* a, void* b, void* c);
void  __cdecl FUN_009c0860(void* a);
void  __cdecl FUN_009cf240(void* sa, float f);
void  __cdecl FUN_009d5f10(void* e, float f, float x, float y, float z);

// =============================================================================================
// 0x009d6a10 -- allocate an n-element (0x38-byte) vector into the slot in ecx.
// =============================================================================================
// @ 0x009d6a10
Vec38* Vec38::DoAllocate(unsigned n, void* a)
{
    char* data;
    if (n != 0)
        data = (char*)GAIT_ALLOC(n * 0x38);
    else
        data = 0;
    b = data;
    e = data;
    c = data + n * 0x38;
    return this;
}

// =============================================================================================
// 0x009d6a70 -- destroy the ranged 0x38-byte elements, releasing each owned +4 buffer.
// =============================================================================================
// @ 0x009d6a70
void __cdecl FUN_009d6a70(char* first, char* last)
{
    for (; first != last; first += 0x38) {
        void* q = *(void**)(first + 4);
        if (q != 0 && *(int*)((char*)q - 4) != 0)
            EastlFree(q);
    }
}

// =============================================================================================
// 0x009d6ae0 -- eastl::make_heap over the SA range using the LessFac comparator.
// =============================================================================================
// @ 0x009d6ae0
void __cdecl FUN_009d6ae0(SA* first, SA* last, LessFac cmp)
{
    int n = (int)(last - first);
    if (n >= 2) {
        int i = ((n - 2) >> 1) + 1;
        SA* p = first + i;
        do {
            --i;
            --p;
            FUN_009d40c0(first, i, n, i, *p, cmp);
        } while (i != 0);
    }
}

// =============================================================================================
// 0x009d6bb0 -- merge two sorted SA* runs on record+0x7c; returns the end of the output.
// =============================================================================================
// @ 0x009d6bb0
SA** __cdecl FUN_009d6bb0(SA** f1, SA** l1, SA** f2, SA** l2, SA** out)
{
    while (f1 != l1 && f2 != l2) {
        SA* b = *f2;
        SA* a = *f1;
        if (b->f7c > a->f7c) {
            *out = b;
            ++f2;
        } else {
            *out = a;
            ++f1;
        }
        ++out;
    }
    int n1 = (int)((char*)l1 - (char*)f1);
    out = (SA**)((char*)FUN_011e0744(out, f1, (unsigned)n1) + (n1 >> 2) * 4);
    int n2 = (int)((char*)l2 - (char*)f2);
    out = (SA**)((char*)FUN_011e0744(out, f2, (unsigned)n2) + (n2 >> 2) * 4);
    return out;
}

// =============================================================================================
// 0x009d6c20 -- merge two sorted SA* runs on record+0x80; returns the end of the output.
// =============================================================================================
// @ 0x009d6c20
SA** __cdecl FUN_009d6c20(SA** f1, SA** l1, SA** f2, SA** l2, SA** out)
{
    while (f1 != l1 && f2 != l2) {
        SA* b = *f2;
        SA* a = *f1;
        if (b->f80 > a->f80) {
            *out = b;
            ++f2;
        } else {
            *out = a;
            ++f1;
        }
        ++out;
    }
    int n1 = (int)((char*)l1 - (char*)f1);
    out = (SA**)((char*)FUN_011e0744(out, f1, (unsigned)n1) + (n1 >> 2) * 4);
    int n2 = (int)((char*)l2 - (char*)f2);
    out = (SA**)((char*)FUN_011e0744(out, f2, (unsigned)n2) + (n2 >> 2) * 4);
    return out;
}

// =============================================================================================
// 0x009d6ca0 -- merge two sorted SA* runs, key (record+0x80, then +0x7c); returns the output end.
// =============================================================================================
// @ 0x009d6ca0
SA** __cdecl FUN_009d6ca0(SA** f1, SA** l1, SA** f2, SA** l2, SA** out)
{
    for (;;) {
        if (f1 == l1)
            break;
        if (f2 == l2)
            break;
        SA* a = *f1;
        SA* b = *f2;
        bool takeB;
        if (b->f80 == a->f80)
            takeB = b->f7c > a->f7c;
        else
            takeB = b->f80 > a->f80;
        if (takeB) {
            *out = b;
            ++f2;
        } else {
            *out = a;
            ++f1;
        }
        ++out;
    }
    int n1 = (int)((char*)l1 - (char*)f1);
    out = (SA**)((char*)FUN_011e0744(out, f1, (unsigned)n1) + (n1 >> 2) * 4);
    int n2 = (int)((char*)l2 - (char*)f2);
    out = (SA**)((char*)FUN_011e0744(out, f2, (unsigned)n2) + (n2 >> 2) * 4);
    return out;
}

// =============================================================================================
// 0x009d6d30 -- Hoare partition of [first,last) about `pivot` by record+0xac (descending);
//              returns the cut pointer.
// =============================================================================================
// @ 0x009d6d30
SA* __cdecl FUN_009d6d30(SA* first, SA* last, SA pivot)
{
    for (;;) {
        while (FacLess(*first, pivot))
            ++first;
        do {
            --last;
        } while (FacLess(*last, pivot));
        if (first >= last)
            return first;
        swp(*first, *last);
        ++first;
    }
}

// =============================================================================================
// 0x009d6e00 -- eastl::partial_sort over [first,last) keeping the smallest `middle-first`.
// =============================================================================================
// @ 0x009d6e00
void __cdecl FUN_009d6e00(SA* first, SA* middle, SA* last, LessFac cmp)
{
    FUN_009d6ae0(first, middle, cmp);
    for (SA* i = middle; i < last; ++i) {
        if (cmp(*i, *first)) {
            SA temp(*i);
            *i = *first;
            FUN_009d40c0(first, 0, (int)(middle - first), 0, temp, cmp);
        }
    }
    FUN_009d6b50(first, middle, cmp);
}

// =============================================================================================
// 0x009d6ef0 -- eastl vector<u32>::DoInsertValue(pos, const u32&) with the in-place shift and
//               the 2x-grow relocation path (EASTL allocator).
// =============================================================================================
// @ 0x009d6ef0
void VecU32::DoInsertValue(u32* pos, const u32& v)
{
    if (e != c) {
        const u32* pv = &v;
        if (pv >= pos && pv < e)
            ++pv;
        if (e)
            *e = *(e - 1);
        u32* last = e - 1;
        memmove(e - (last - pos), pos, (char*)last - (char*)pos);
        *pos = *pv;
        ++e;
    } else {
        u32 cnt = (u32)(e - b);
        u32 n = cnt > 0 ? 2 * cnt : 1;
        u32* nb = n ? (u32*)GAIT_ALLOC(n * 4) : 0;
        int n1 = (int)((char*)pos - (char*)b);
        u32* np = (u32*)FUN_011e0744(nb, b, (unsigned)n1);
        np += n1 >> 2;
        if (np)
            *np = v;
        ++np;
        int n2 = (int)((char*)e - (char*)pos);
        np = (u32*)FUN_011e0744(np, pos, (unsigned)n2);
        np += n2 >> 2;
        if (b && ((int*)b)[-1])
            EastlFree(b);
        b = nb;
        e = np;
        c = nb + n;
    }
}

// =============================================================================================
// 0x009d7000 -- eastl vector<SA>::DoInsertValue(pos, const SA&): in-place shift or 2x-grow with
//               the member-wise record copies.
// =============================================================================================
// @ 0x009d7000
void VecSA::DoInsertValue(SA* pos, const SA& v)
{
    if (e != c) {
        const SA* pv = &v;
        if (pv >= pos && pv < e)
            ++pv;
        if (e)
            e->FUN_009ce790(e - 1);
        FUN_009cecf0(pos, e - 1, e);
        pos->FUN_009ce790((SA*)pv);
        ++e;
    } else {
        int cnt = (int)(e - b);
        int n = cnt != 0 ? 2 * cnt : 1;
        SA* nb;
        if (n != 0)
            nb = (SA*)GAIT_ALLOC(n * 0x108);
        else
            nb = 0;
        SA* r = FUN_009cec70(b, pos, nb);
        if (r)
            r->FUN_009ce790((SA*)&v);
        r = FUN_009cec70(pos, e, r + 1);
        if (b && ((int*)b)[-1])
            EastlFree(b);
        b = nb;
        e = r;
        c = nb + n;
    }
}

// =============================================================================================
// 0x009d7480 -- eastl::introsort_loop over [first,last): median-of-three, partition, recurse on
//               the right part and iterate on the left; final partial_sort when depth runs out.
// =============================================================================================
// @ 0x009d7480
void __cdecl FUN_009d7480(SA* first, SA* last, int depth, LessFac cmp)
{
    while ((int)(last - first) > 0x1c && depth > 0) {
        SA* mid = first + (last - first) / 2;
        SA* med = FUN_009ceb50(first, mid, last - 1, cmp, cmp);
        SA* cut = FUN_009d6d30(first, last, *med);
        --depth;
        FUN_009d7480(cut, last, depth, cmp);
        last = cut;
    }
    if (depth == 0)
        FUN_009d6e00(first, last, last, cmp);
}

// =============================================================================================
// 0x009d63e0 -- step the two indexed phase records into the output vectors (reconstruction).
// =============================================================================================
// @ 0x009d63e0
void Anim::m63e0(void* param2)
{
    if (!(fa4 >= g_14479b0))
        return;
    if ((unsigned)(e8 - b4) < 2)
        return;

    u32 i0 = pbc[0];
    u32 i1 = pbc[1];
    char* arr = *(char**)((char*)ctx48 + 0x24);
    char* a0 = arr + i0 * 0x108;
    char* a1 = arr + i1 * 0x108;
    char* obj = *(char**)(a0 + 0xc8);
    unsigned mid = (unsigned)((char*)e8) + (unsigned)((char*)b4);

    void* out34 = 0;
    float f0 = 0.0f, f1 = 0.0f, f2 = 0.0f, one = 0.0f;
    FUN_009d2f50(&f0, &obj);
    float dist = FUN_009d62a0(*(float*)&f0);
    mid >>= 1;

    if (obj[0x260] != 0) {
        one = 1.0f;
        if (b4 < (char*)i0c && (char*)i0c < e8) {
            FUN_009cfb00(&f1, &f2, a0, a1, dist, &f0, &out34);
            FUN_009cfd40(&f1, &f2, param2);
        }
        if (mid != (unsigned)i0c) {
            FUN_009cfb00(&f1, &f2, a0, a1, dist, &f0, &out34);
            FUN_009cfd40(&f1, &f2, param2);
        }
    }
    if (g_15509f0 != 0 && obj[0x168c] != 0) {
        char* t = (char*)i0c;
        if (b4 < t && t < e8)
            FUN_009c0860(p38 + (unsigned)t * 0x30);
        if (mid != (unsigned)i0c) {
            FUN_009c0860(p38 + mid * 0x30);
            return;
        }
    }
}

// =============================================================================================
// 0x009d65f0 -- per-record speed blend: pow(0.1, dt/f70) blends the [0xdc] scale against the
//               speed magnitude; returns the eased value in ST(0).
// =============================================================================================
// @ 0x009d65f0
float Anim::m65f0(float dt, void* e)
{
    if (!(dt > g_14479b0))
        return *(float*)((char*)e + 0xdc);
    float p = (float)pow(0.1, (double)(dt / f70));
    float a = (float)fabs((double)f64) * g_15514e0;
    float r = (float)sqrt((double)(f4c * f4c + f50 * f50 + f54 * f54));
    float m = (a > r) ? a : r;
    f6c = (1.0f - p) * m + f6c * p;
    float x = f6c * g_1447a38;
    x = x * x;
    if (x > -g_166c7d4)
        return g_1485720;
    return 1.0f - (float)exp((double)-x);
}

// =============================================================================================
// 0x009d6700 -- advance every record of the animation by `dt`: phase/speed update, the SA blend
//               pass (Advance or the direct field copy) and the fractional-phase wrap.
// =============================================================================================
// @ 0x009d6700
void Anim::m6700(float dt)
{
    int n = (int)((p14 - p10) / 0x104);
    if (n != 0) {
        char* p = p10;
        for (int i = 0; i < n; ++i, p += 0x104) {
            Elem104* e = (Elem104*)p;
            e->fdc = m65f0(dt, e);
            e->fa0 = e->fa4 * dt;
            float q = (float)pow(0.1, (double)(dt / f74));
            e->f8c = (float)sin((double)e->f8c * g_1447a08);
            e->f90 = e->fd4 * (1.0f - q) + e->f90 * q;
            e->f94 = e->fd8 * (1.0f - q) + e->f94 * q;
        }
    }

    int m = (int)((p28 - p24) / 0x108);
    if (m != 0) {
        char* s = p24;
        for (int i = 0; i < m; ++i, s += 0x108) {
            SA* sa = (SA*)s;
            char* e = p10 + sa->iC4 * 0x104;
            float f = (*(float*)(e + 0x8c) * sa->f78) * g_1471064;
            sa->f100 = f;
            sa->f104 = g_1485720 - f;
            FUN_009cf240(s, *(float*)(e + 0x9c));
            char* obj = *(char**)(sa->iC8);
            char* g = *(char**)(obj + 0x2e4) + sa->i58 * 0x2bc;
            if (*(float*)(g + 0x4c) > 0.0f) {
                FUN_009d5f10(e, f64, f4c, f50, f54);
            } else {
                float d = *(float*)(obj + 0x70);
                if (!(d > g_14479b0))
                    d = g_14479b0;
                float inv = g_1485720 / d;
                sa->f00 = inv * *(float*)(g + 0x7c);
                sa->f04 = *(float*)(g + 0x80) * inv;
                sa->f08 = *(float*)(g + 0x84) * inv;
                sa->f24 = *(float*)(g + 0x8c);
                sa->f28 = *(float*)(g + 0x90);
                sa->f2c = *(float*)(g + 0x94);
                sa->f30 = *(float*)(g + 0x98);
            }
        }
    }

    if (n != 0) {
        char* p = p10;
        for (int i = 0; i < n; ++i, p += 0x104) {
            Elem104* e = (Elem104*)p;
            float v = e->fa0 + e->f9c;
            e->f9c = v - (float)floor((double)v);
        }
    }
}
