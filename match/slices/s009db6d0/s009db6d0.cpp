// Spore 0x009db6d0 slice -- animation gait/layout blend helpers (anonymous game code).
//
// Reconstructed from the retail disassembly. Struct sizes and the float/integer split of
// the members below are what drive the code generation, so keep them in sync with the
// offsets noted per member.

#include <math.h>
#include <string.h>

typedef unsigned int uint32;

// 0x015515dc: set when scalar channels are shared (skips the x component on copy).
extern int g_skipScalars;

// ---------------------------------------------------------------------------
// shared record types
// ---------------------------------------------------------------------------

struct SegObj {
    char pad[4];
    char active;            // +0x04
};

struct Seg {                // 0x30
    SegObj* obj;            // +0x00
    char pad[0x2c];
};

struct Part {               // 0x104
    char pad0[0xbc];
    int* ids_begin;         // +0xbc
    int* ids_end;           // +0xc0
    char pad1[0x40];        // +0xc4
    float Time();           // 0x009d0db0
};

struct Particle {           // 0x108
    char pad0[0xa8];
    float v0;               // +0xa8
    float v1;               // +0xac
    char pad1[0x14];
    int index;              // +0xc4
    char pad2[0x40];
};

struct World {
    char pad[0x3e0];
    int f3e0;               // +0x3e0
};

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------

float __cdecl sub_9DB0B0(void* begin, void* end, int flags);      // 0x009db0b0
void __cdecl sub_9DB140(void* begin, void* end, int flags);       // 0x009db140
float* __cdecl sub_99CC70(float* out, const float* a, const float* b, float t);  // 0x0099cc70
float __cdecl sub_9B3C10(float a, float b);                       // 0x009b3c10

struct Layout {
    char pad0[0x10];
    Part* parts_begin;      // +0x10
    Part* parts_end;        // +0x14
    char pad1[0x0c];
    char* particles;        // +0x24
    char pad2[0x10];
    Seg* seg_begin;         // +0x38
    Seg* seg_end;           // +0x3c

    int Call630(World** ctx, Seg* start, Seg* end, int total);    // 0x009db630
    void Build(float ratio, World** ctx);
};

// @ 0x009db6d0
void Layout::Build(float ratio, World** ctx)
{
    uint32 count = (uint32)(seg_end - seg_begin);
    Seg* start = 0;
    Seg* last = 0;
    int total = 0;

    if ((*ctx)->f3e0 == 0) {
        Call630(ctx, seg_begin, seg_begin + count - 1, 0);
    } else {
        for (uint32 i = 0; i < count; ++i) {
            Seg* seg = seg_begin + i;
            char active = seg->obj->active;
            if (active) {
                if (start == 0)
                    start = seg;
                last = seg;
            }
            if (start != 0 && last != 0 && (!active || i == count - 1)) {
                total += Call630(ctx, start, last, total);
                last = 0;
                start = 0;
            }
        }
    }

    sub_9DB0B0(parts_begin, parts_end, 0);

    uint32 parts = (uint32)(parts_end - parts_begin);
    if (parts > 1) {
        float first = parts_begin[0].Time();
        uint32 split = 1;
        while (split < parts) {
            if (parts_begin[split].Time() / first > ratio)
                break;
            ++split;
        }
        if (split > 1) {
            float lastTime = parts_begin[split - 1].Time();
            uint32 n = split - 1;
            if (n != 0) {
                Part* part = parts_begin;
                do {
                    float scale = part->Time() / lastTime;
                    int* ids = part->ids_begin;
                    uint32 used = (uint32)(part->ids_end - part->ids_begin);
                    for (uint32 k = 0; k < used; ++k) {
                        Particle* p = (Particle*)(particles + ids[k] * sizeof(Particle));
                        p->v0 = p->v0 * scale;
                        p->v1 = scale * p->v1;
                    }
                    ++part;
                } while (--n != 0);
            }
        }
    }

    sub_9DB140(parts_begin, parts_end, 0);

    for (uint32 i = 0; i < parts; ++i) {
        Part* part = parts_begin + i;
        int* ids = part->ids_begin;
        uint32 used = (uint32)(part->ids_end - part->ids_begin);
        for (uint32 k = 0; k < used; ++k) {
            Particle* p = (Particle*)(particles + ids[k] * sizeof(Particle));
            p->index = (int)i;
        }
    }
}

// ---------------------------------------------------------------------------
// value types copied by hand all over this code
// ---------------------------------------------------------------------------

struct ValPath;

struct Val3 {               // 0x0c -- one interpolated sample
    float x;                // +0x00
    float y;                // +0x04
    int z;                  // +0x08
};
// The original takes the destination Val3 explicitly (first stack argument); ecx is unused.
void __stdcall SampleAt(Val3* out, uint32 index, const ValPath* a, float t, const ValPath* b);

struct Val3b {              // 0x0c -- an (x, y, flag) triple
    float x;                // +0x00
    float y;                // +0x04
    char flag;              // +0x08
};

struct ValPath {            // 3-float value list
    char pad0[0x0c];
    Val3* begin;            // +0x0c
    Val3* end;              // +0x10
};

// in-place blend: this = a*(1-t) + b*t
struct Blend9 {
    char pad0[8];
    float v[3];             // +0x08
    float r[3][4];          // +0x14, only the first two floats of every row blend
    void Pos(const Blend9* a, float t, const Blend9* b);
    void All(const Blend9* a, float t, const Blend9* b);
};

struct BlendQ {
    char pad0[8];
    float q[4];             // +0x08
    float r[4][4];          // +0x18, only the first two floats of every row blend
    void All(const BlendQ* a, float t, const BlendQ* b);
};

// Polymorphic inner record shared by the layout and animation tracks.
struct Inner {
    int f00;                // +0x00
    float f04;              // +0x04
    int f08;                // +0x08
    char skip[0x28];        // +0x0c .. +0x33 (not part of either copy)
    int f34;                // +0x34
    int f38;
    int f3c;
    int f40;
    int f44;
    int f48;
    int f4c;
    int f50;
    int f54;
    int f58;
    int f5c;
    int f60;
    int f64;
    int f68;
    int f6c;
    int f70;
    int f74;
    int f78;
    int f7c;
    int f80;
    int f84;
    int f88;
    int f8c;
    int f90;
    int f94;
    int f98;
    char pad1[3];
    char f9c;               // +0x9c
    void Assign(const Inner* src);
    void CopyMasked(const Inner* src, uint32 mask);
};

// Weighted sum of a track: one weight per sample plus the stride-separated channel data.
struct Track {
    void* vtbl;             // +0x00
    int count;              // +0x04
    char pad0[0x74];        // +0x08 .. +0x7b
    float w[1];             // +0x7c
    float Channel(int i) const
    {
        return *(const float*)((const char*)this + 0x140 + i * 0xb4);
    }
    float Total();
};

// @ 0x009dba20
void Blend9::Pos(const Blend9* a, float t, const Blend9* b)
{
    float inv = 1.0f - t;
    v[0] = a->v[0] * inv + b->v[0] * t;
    v[1] = a->v[1] * inv + b->v[1] * t;
    v[2] = a->v[2] * inv + b->v[2] * t;
}

// @ 0x009dba90
void Inner::CopyMasked(const Inner* src, uint32 mask)
{
    f00 = src->f00;
    if (g_skipScalars == 0 && (mask & 1) == 0)
        f04 = src->f04;
    f08 = src->f08;
    if ((mask & 4) == 0)
        f34 = src->f34;
    if ((mask & 8) == 0)
        f38 = src->f38;
    if ((mask & 0x10) == 0)
        f3c = src->f3c;
    if ((mask & 0x20) == 0)
        f40 = src->f40;
    if ((mask & 0x40) == 0)
        f44 = src->f44;
    if ((mask & 0x80) == 0)
        f48 = src->f48;
    if ((mask & 0x100) == 0)
        f4c = src->f4c;
    if ((mask & 0x200) == 0)
        f50 = src->f50;
    if ((mask & 0x400) == 0)
        f54 = src->f54;
    if ((mask & 0x800) == 0)
        f58 = src->f58;
    if ((mask & 0x1000) == 0)
        f5c = src->f5c;
    if ((mask & 0x2000000) == 0)
        f60 = src->f60;
    if ((mask & 0x2000) == 0)
        f64 = src->f64;
    if ((mask & 0x4000) == 0)
        f68 = src->f68;
    if ((mask & 0x8000) == 0)
        f6c = src->f6c;
    if ((mask & 0x10000) == 0)
        f70 = src->f70;
    if ((mask & 0x8000000) == 0)
        f74 = src->f74;
    if ((mask & 0x10000000) == 0)
        f78 = src->f78;
    if ((mask & 0x20000) == 0)
        f7c = src->f7c;
    if ((mask & 0x40000) == 0)
        f80 = src->f80;
    if ((mask & 0x80000) == 0)
        f84 = src->f84;
    if ((mask & 0x100000) == 0)
        f88 = src->f88;
    if ((mask & 0x200000) == 0)
        f8c = src->f8c;
    if ((mask & 0x400000) == 0)
        f90 = src->f90;
    if ((mask & 0x800000) == 0)
        f94 = src->f94;
    if ((mask & 0x1000000) == 0)
        f98 = src->f98;
    f9c = src->f9c;
}

// @ 0x009dbc60
void Inner::Assign(const Inner* src)
{
    f00 = src->f00;
    f04 = src->f04;
    f08 = src->f08;
    f34 = src->f34;
    f38 = src->f38;
    f3c = src->f3c;
    f40 = src->f40;
    f44 = src->f44;
    f48 = src->f48;
    f4c = src->f4c;
    f50 = src->f50;
    f54 = src->f54;
    f58 = src->f58;
    f5c = src->f5c;
    f60 = src->f60;
    f64 = src->f64;
    f68 = src->f68;
    f6c = src->f6c;
    f70 = src->f70;
    f74 = src->f74;
    f78 = src->f78;
    f7c = src->f7c;
    f80 = src->f80;
    f84 = src->f84;
    f88 = src->f88;
    f8c = src->f8c;
    f90 = src->f90;
    f94 = src->f94;
    f98 = src->f98;
    f9c = src->f9c;
}

// @ 0x009dbd50
float Track::Total()
{
    float acc[3] = { 0.0f, 0.0f, 0.0f };
    int n = count;
    int j = 0;
    if (n >= 2) {
        int pairs = ((unsigned)(n - 2) >> 1) + 1;
        const float* c = (const float*)((const char*)this + 0x140 + 0xb4);
        const float* wv = (const float*)((const char*)this + 0x7c) + 1;
        j = pairs * 2;
        do {
            acc[1] = c[-0x2d] * wv[-1] + acc[1];
            acc[2] = wv[0] * c[0] + acc[2];
            wv += 2;
            c += 0x5a;
        } while (--pairs);
    }
    if (j < n)
        acc[2] = w[j] * Channel(j);
    return acc[0] + acc[1] + acc[2];
}

// ---------------------------------------------------------------------------
// 4x4 blob with an integer row selector
// ---------------------------------------------------------------------------

struct Grid {
    char pad[0x1c];
    void* m[4][4];          // +0x1c
    void Set(void* value, int row, int col);
};

// @ 0x009dbe10
void Grid::Set(void* value, int row, int col)
{
    m[row][col] = value;
}

// ---------------------------------------------------------------------------
// records copied by hand
// ---------------------------------------------------------------------------

struct Rec44 {              // 0x44
    void* vtbl;             // +0x00
    int ref;                // +0x04
    float x, y, z;          // +0x08
    int d[12];              // +0x14
    Rec44* Ctor(const Rec44* src);
    Rec44* Assign(const Rec44* src);
};

struct Rec58 {              // 0x58
    void* vtbl;             // +0x00
    int ref;                // +0x04
    float x, y, z, w;       // +0x08 .. +0x14
    int d[16];              // +0x18
    Rec58* Ctor(const Rec58* src);
    Rec58* Assign(const Rec58* src);
};

struct Rec1C {              // 0x1c
    void* vtbl;             // +0x00
    int ref;                // +0x04
    int d[5];               // +0x08
    Rec1C* Ctor(const Rec1C* src);
};

struct GaitC {              // 0x1c, copied without its vtable slot
    void* vtbl;             // +0x00
    int ref;                // +0x04
    float t;                // +0x08
    int d[4];               // +0x0c
};

// @ 0x009dbe30
Rec44* Rec44::Ctor(const Rec44* src)
{
    const int* r = src ? (const int*)src + 1 : 0;
    ref = *r;
    vtbl = (void*)0x1447cc0;
    x = src->x;
    y = src->y;
    z = src->z;
    memcpy(d, src->d, sizeof d);
    return this;
}

// @ 0x009dbe80
Rec58* Rec58::Ctor(const Rec58* src)
{
    const int* r = src ? (const int*)src + 1 : 0;
    ref = *r;
    vtbl = (void*)0x1447cc4;
    x = src->x;
    y = src->y;
    z = src->z;
    w = src->w;
    memcpy(d, src->d, sizeof d);
    return this;
}

// @ 0x009dbed0
Rec1C* Rec1C::Ctor(const Rec1C* src)
{
    const int* r = src ? (const int*)src + 1 : 0;
    ref = *r;
    vtbl = (void*)0x1447cc8;
    d[0] = src->d[0];
    memcpy(&d[1], &src->d[1], 4 * sizeof(int));
    return this;
}

// 3-float keyframe
struct Sample {             // 0x0c
    float t;                // +0x00
    float v;                // +0x04
    float d;                // +0x08
};

struct CurveOut {
    float v;                // +0x00
    float d;                // +0x04
    bool exact;             // +0x08
};

struct Curve {
    int count;              // +0x00
    Sample* samples;        // +0x04
    void Eval(float t, CurveOut* out);
};

// @ 0x009dbf10
void Curve::Eval(float t, CurveOut* out)
{
    int n = count;
    int idx = 0;
    int i = 0;
    if (n != 0) {
        for (; i != n; ++i) {
            if (t < samples[i].t)
                break;
            idx = i;
        }
        if (i != 0 && i != n) {
            const Sample& a = samples[idx];
            const Sample& b = samples[i];
            out->v = (t - a.t) / (b.t - a.t) * (b.v - a.v) + a.v;
            out->exact = (t == a.t);
            return;
        }
    }
    out->v = samples[idx].v;
    out->d = samples[idx].d;
    out->exact = (t == samples[idx].t);
}

// @ 0x009dbfd0
Rec44* Rec44::Assign(const Rec44* src)
{
    const int* r = src ? (const int*)src + 1 : 0;
    ref = *r;
    x = src->x;
    y = src->y;
    z = src->z;
    d[0] = src->d[0];
    d[1] = src->d[1];
    d[2] = src->d[2];
    d[3] = src->d[3];
    d[4] = src->d[4];
    d[5] = src->d[5];
    d[6] = src->d[6];
    d[7] = src->d[7];
    d[8] = src->d[8];
    d[9] = src->d[9];
    d[10] = src->d[10];
    d[11] = src->d[11];
    return this;
}

// @ 0x009dc050
Rec58* Rec58::Assign(const Rec58* src)
{
    const int* r = src ? (const int*)src + 1 : 0;
    ref = *r;
    x = src->x;
    y = src->y;
    z = src->z;
    w = src->w;
    d[0] = src->d[0];
    d[1] = src->d[1];
    d[2] = src->d[2];
    d[3] = src->d[3];
    d[4] = src->d[4];
    d[5] = src->d[5];
    d[6] = src->d[6];
    d[7] = src->d[7];
    d[8] = src->d[8];
    d[9] = src->d[9];
    d[10] = src->d[10];
    d[11] = src->d[11];
    d[12] = src->d[12];
    d[13] = src->d[13];
    d[14] = src->d[14];
    d[15] = src->d[15];
    return this;
}

// @ 0x009dc0f0
Rec44* Copy44(const Rec44* first, const Rec44* last, Rec44* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst != 0) {
            const int* ref = first ? (const int*)first + 1 : 0;
            dst->ref = *ref;
            dst->vtbl = (void*)0x1447cc0;
            dst->x = first->x;
            dst->y = first->y;
            dst->z = first->z;
            memcpy(dst->d, first->d, sizeof dst->d);
        }
    }
    return dst;
}

// @ 0x009dc160
Rec58* Copy58(const Rec58* first, const Rec58* last, Rec58* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst != 0) {
            const int* ref = first ? (const int*)first + 1 : 0;
            dst->ref = *ref;
            dst->vtbl = (void*)0x1447cc4;
            dst->x = first->x;
            dst->y = first->y;
            dst->z = first->z;
            dst->w = first->w;
            memcpy(dst->d, first->d, sizeof dst->d);
        }
    }
    return dst;
}

// @ 0x009dc1d0
Rec1C* Copy1C(const Rec1C* first, const Rec1C* last, Rec1C* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst != 0) {
            const int* ref = first ? (const int*)first + 1 : 0;
            dst->ref = *ref;
            dst->vtbl = (void*)0x1447cc8;
            dst->d[0] = first->d[0];
            dst->d[1] = first->d[1];
            dst->d[2] = first->d[2];
            dst->d[3] = first->d[3];
            dst->d[4] = first->d[4];
        }
    }
    return dst;
}

// @ 0x009dc2b0
GaitC* vcopyGaitC(const GaitC* first, const GaitC* last, GaitC* dst)
{
    for (; first != last; ++first, ++dst) {
        const int* ref = first ? (const int*)first + 1 : 0;
        dst->ref = *ref;
        dst->t = first->t;
        dst->d[0] = first->d[0];
        dst->d[1] = first->d[1];
        dst->d[2] = first->d[2];
        dst->d[3] = first->d[3];
    }
    return dst;
}

// @ 0x009dc300
Val3b* CopyVal3b(const Val3b* first, const Val3b* last, Val3b* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst != 0) {
            dst->x = first->x;
            dst->y = first->y;
            dst->flag = first->flag;
        }
    }
    return dst;
}

// @ 0x009dc3c0
GaitC* vcopyGaitCBack(const GaitC* first, const GaitC* last, GaitC* dst)
{
    while (last != first) {
        --last;
        --dst;
        const int* ref = last ? (const int*)last + 1 : 0;
        dst->ref = *ref;
        dst->t = last->t;
        dst->d[0] = last->d[0];
        dst->d[1] = last->d[1];
        dst->d[2] = last->d[2];
        dst->d[3] = last->d[3];
    }
    return dst;
}

// @ 0x009dc410
void Blend9::All(const Blend9* a, float t, const Blend9* b)
{
    float inv = 1.0f - t;
    v[0] = a->v[0] * inv + b->v[0] * t;
    v[1] = a->v[1] * inv + b->v[1] * t;
    v[2] = a->v[2] * inv + b->v[2] * t;
    float* d = &r[0][0];
    const float* pa = &a->r[0][0];
    const float* pb = &b->r[0][0];
    for (int i = 3; i != 0; --i) {
        d[0] = pa[0] * inv + pb[0] * t;
        d[1] = pa[1] * inv + pb[1] * t;
        d += 4;
        pa += 4;
        pb += 4;
    }
}

// @ 0x009dc4f0
void BlendQ::All(const BlendQ* a, float t, const BlendQ* b)
{
    float buf[4];
    float* res = sub_99CC70(buf, a->q, b->q, t);
    q[0] = res[0];
    q[1] = res[1];
    q[2] = res[2];
    q[3] = res[3];
    float inv = 1.0f - t;
    for (int i = 0; i < 4; ++i) {
        r[i][0] = a->r[i][0] * inv + b->r[i][0] * t;
        r[i][1] = a->r[i][1] * inv + b->r[i][1] * t;
    }
}

// @ 0x009dc5b0
void __stdcall SampleAt(Val3* out, uint32 index, const ValPath* a, float t, const ValPath* b)
{
    uint32 na = (uint32)(a->end - a->begin);
    uint32 nb = (uint32)(b->end - b->begin);
    if (index < na) {
        if (index < nb) {
            float base = a->begin[index].x;
            float v = sub_9B3C10(b->begin[index].x - base, 1.0f) * t + base;
            out->x = v - (float)floor((double)v);
            out->y = (b->begin[index].y - a->begin[index].y) * t + a->begin[index].y;
            out->z = a->begin[index].z;
            return;
        }
        *out = a->begin[index];
        return;
    }
    if (index < nb)
        *out = b->begin[index];
}

// path descriptor
struct Path104 {            // 0xa4
    char pad0[0x10];
    Val3* begin;            // +0x10
    Val3* end;              // +0x14
    char pad1[0x8c];
};

struct Track2 {
    char pad0[0x18];
    int count;              // +0x18
    Path104* paths;         // +0x1c
    int TotalItems();
};

// @ 0x009dc6a0
int Track2::TotalItems()
{
    int n = count;
    int sumA = 0;
    int sumB = 0;
    int tail = 0;
    unsigned i = 0;
    if (n > 1) {
        const Path104* p = paths;
        unsigned pairs = ((unsigned)(n - 2) >> 1) + 1;
        i = pairs * 2;
        do {
            sumA += (int)(p[0].end - p[0].begin) * 8;
            sumB += (int)(p[1].end - p[1].begin) * 8;
            p += 2;
        } while (--pairs != 0);
    }
    if (i < (unsigned)n)
        tail = (int)(paths[i].end - paths[i].begin) * 8;
    return sumA + sumB + tail;
}
