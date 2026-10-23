// SporeApp gold5 slice s009d1b40 -- text layout / line alignment helpers.
//
// The owning object (Layout, EA::Text::Typesetter-ish) keeps a flat array of
// per-glyph entries (0x108 bytes each) referenced through Group records
// (0x38 bytes: head pointer, array of entry pointers, end pointer).
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// Compiled with VS2008 (cl 15): float copies go through the x87 stack, scalar
// arithmetic through SSE, int->float conversions through fild, and floor() is
// an import call.
#include "types.h"
#include <math.h>

extern int32_t  g_1550b6c;   // 0x01550b6c  layout mode (5 -> derive from game data)
extern uint32_t g_15515dc;   // 0x015515dc  enable per-entry atlas offsets
extern uint8_t  g_1551256;   // 0x01551256  enable per-entry shear correction
extern float    g_166c680;   // 0x0166c680  lazily initialised: pi/2
extern float    g_166c684;   // 0x0166c684  lazily initialised: 75deg / 30deg
extern uint32_t g_166c688;   // 0x0166c688  lazy-init bit flags
extern float    g_eps;       // 0x014479b0  smallest useful 1e-6
extern float    g_big;       // 0x014479b4  largest useful 1e6
extern float    g_tiny;      // 0x01551258  1e-12

// ---------------------------------------------------------------------------
// data model
// ---------------------------------------------------------------------------
struct Group                                        // 0x38 bytes
{
    void*       head;                               // +0x00  object whose +0x110 is a float
    uint8_t**   items;                              // +0x04  entry pointer array
    uint8_t**   end;                                // +0x08
    uint8_t     pad0c[0x2c];
};

struct Src                                          // layout description handed in
{
    uint8_t     pad00[0x10];
    int32_t     mode;                               // +0x10  -1 = no per-entry pass
    uint8_t*    first;                              // +0x14  0xc-byte records
    uint8_t*    last;                               // +0x18
    uint8_t     pad1c[0x20];
    float       f3c, f40, f44, f48;                 // +0x3c
    float       f4c, f50, f54, f58;                 // +0x4c
    float       f5c, f60, f64, f68;                 // +0x5c
    float       seq[14];                            // +0x6c .. +0xa3
    uint8_t     pad_a4[4];
    float       fa8;                                // +0xa8
    void*       pac;                                // +0xac
    void*       pb0;                                // +0xb0

    bool        WantsOffsets();                     // 0x009de630
};

struct Vec3
{
    float x, y, z;
};

struct Atlas                                        // object reached through Layout::f48
{
    uint8_t     pad00[0x24];
    uint8_t*    base;                               // +0x24  entry array base
};

struct Layout
{
    uint8_t     pad00[0x10];
    float       f10, f14, f18, f1c;                 // +0x10
    float       f20, f24, f28, f2c;                 // +0x20
    float       f30, f34, f38, f3c;                 // +0x30
    float       f40, f44;                           // +0x40
    Atlas*      f48;                                // +0x48
    Group*      gb;                                 // +0x4c  group array
    Group*      ge;                                 // +0x50
    uint8_t     pad54[0x0c];
    float       f60;                                // +0x60
    float       f64;                                // +0x64  accumulated advance
    float       f68, f6c, f70, f74;                 // +0x68
    float       f78, f7c, f80;                      // +0x78
    float       f84;                                // +0x84
    float       f88;                                // +0x88
    uint8_t     pad8c[0x0c];
    float       f98;                                // +0x98
    uint8_t     pad9c[0x20];
    int32_t*    ib;                                 // +0xbc
    int32_t*    ie;                                 // +0xc0
    uint8_t     padc4[0x10];
    float       fd4, fd8;                           // +0xd4
    uint8_t     paddc[0x1c];
    float       ff8;                                // +0xf8

    void        Apply(Src* s);                      // 0x009d1b40
    void        AlignLines();                       // 0x009d1c90
    void        SetupFrom(Src* s);                  // 0x009d2160
    void        BuildStops(int n, void* a2, void* a3, void* a4, int32_t* a5);  // 0x009d24c0
    float       MinThickness(Vec3 v);                // 0x009d25b0
    float       AngleScale(float angle);            // 0x009d2700

    void        GetExtents(void* extents, void* centres);   // 0x009d12c0
    void        BeginGradient(void* p);             // 0x009d13a0
    void        AddStop(float v, void* p);          // 0x009d15e0
    void        EndGradient(void* p);               // 0x009d19b0
};

void FUN_009ce430(float* out, int32_t n);           // 0x009ce430
void FUN_009ce560(float* vec, int32_t n);           // 0x009ce560

struct Box                                          // six contiguous floats
{
    float ex, ey, ez;                               // extents
    float cx, cy, cz;                               // centres
};

static inline uint8_t* EntryOf(Atlas* a, int32_t i)
{
    return a->base + i * 0x108;
}

// ---------------------------------------------------------------------------
// 0x009d1b40 -- apply per-record atlas offsets to the first "limit" entries
// ---------------------------------------------------------------------------
// @ 0x009d1b40
void Layout::Apply(Src* s)
{
    uint32_t n    = (uint32_t)((int)(s->last - s->first) / 0xc);
    uint32_t cap  = (uint32_t)(ie - ib);
    const uint32_t& limit = (cap < n) ? cap : n;
    if (limit == 0)
        return;

    int groups = (int)(ge - gb);
    if (groups <= 0)
        return;

    int      off = 0;
    uint32_t idx = 0;
    do
    {
        Group* g   = (Group*)((uint8_t*)gb + off);
        int    cnt = (int)(g->end - g->items);
        if (cnt > 0)
        {
            int srcOff = 0;
            int i      = 0;
            do
            {
                if ((int)limit <= (int)idx)
                    break;
                uint8_t* e = g->items[i];
                if (g_15515dc == 0 || s->WantsOffsets() == false)
                {
                    *(float*)(e + 0x60) = 0.0f;
                    *(void**)(e + 0x64) = 0;
                    *(void**)(e + 0x68) = 0;
                }
                else
                {
                    *(float*)(e + 0x60) = s->fa8;
                    int off2 = *(int*)(s->first + srcOff + 8) * 0x40;
                    *(uint8_t**)(e + 0x64) = *(uint8_t**)((uint8_t*)s->pac + 0x20) + off2;
                    *(uint8_t**)(e + 0x68) = *(uint8_t**)((uint8_t*)s->pb0 + 0x20) + off2;
                }
                srcOff += 0xc;
                ++idx;
                ++i;
            } while (i < cnt);
        }
        off += 0x38;
    } while (--groups != 0);
}

// ---------------------------------------------------------------------------
// 0x009d1c90 -- distribute the entries along their line (five spacing modes)
// ---------------------------------------------------------------------------
// @ 0x009d1c90
void Layout::AlignLines()
{
    Box b;
    GetExtents(&b.ex, &b.cx);

    int   count = (int)(ie - ib);
    float fn    = (float)count;
    if (count < 0)
        fn += 4294967296.0f;

    float lineH = ((fn + 2.0f) / fn) * b.ey;

    uint32_t mode = (uint32_t)g_1550b6c;
    if (g_1550b6c == 5)
    {
        uint8_t* a  = *(uint8_t**)((uint8_t*)f48 + 0x24);
        uint8_t* c8 = *(uint8_t**)(a + 0xc8);
        uint8_t* arr = *(uint8_t**)(c8 + 0x2e4);
        uint8_t* rec = *(uint8_t**)(arr + *(int*)(a + 0x58) * 700 + 4);
        int cnt = (*(int*)(rec + 0x2e8) - *(int*)(rec + 0x2e4)) / 700;
        mode = (uint32_t)(cnt % 5);
    }

    int groups = (int)(ge - gb);

    switch (mode)
    {
    case 1:
    {
        if (groups <= 0)
            return;
        int off = 0;
        int gc  = groups;
        do
        {
            Group* g   = (Group*)((uint8_t*)gb + off);
            int    cnt = (int)(g->end - g->items);
            if (cnt > 0)
            {
                uint8_t** it = g->items;
                int       k  = cnt;
                do
                {
                    uint8_t* e    = *it;
                    float    flag = (*(float*)(e + 0x7c) <= b.cx) ? 0.5f : 0.0f;
                    float    x;
                    if (b.ey > 0.0f)
                        x = (*(float*)(e + 0x80) - (b.cy - b.ey * 0.5f)) / lineH;
                    else
                        x = 0.0f;
                    float sum = x + flag;
                    *(float*)(e + 0x6c) = sum - (float)floor((double)sum);
                    ++it;
                } while (--k);
            }
            off += 0x38;
        } while (--gc);
        return;
    }
    case 2:
    {
        int base = 0;
        if (groups <= 0)
            return;
        int off = 0;
        do
        {
            Group* g   = (Group*)((uint8_t*)gb + off);
            int    cnt = (int)(g->end - g->items);
            if (cnt > 0)
            {
                uint8_t** it = g->items;
                int       i  = 0;
                do
                {
                    float v = (float)(i + base) * 0.5f;
                    *(float*)(*it + 0x6c) = v - (float)floor((double)v);
                    ++i;
                    ++it;
                } while (i < cnt);
            }
            off += 0x38;
            ++base;
        } while (base < groups);
        return;
    }
    case 3:
    {
        if (groups <= 0)
            return;
        int off = 0;
        int gc  = groups;
        do
        {
            Group* g   = (Group*)((uint8_t*)gb + off);
            int    cnt = (int)(g->end - g->items);
            if (cnt > 0)
            {
                uint8_t** it = g->items;
                int       k  = cnt;
                do
                {
                    uint8_t* e = *it;
                    float    x;
                    if (b.ey > 0.0f)
                        x = (*(float*)(e + 0x80) - (b.cy - b.ey * 0.5f)) / lineH;
                    else
                        x = 0.0f;
                    *(float*)(e + 0x6c) = x - (float)floor((double)x);
                    ++it;
                } while (--k);
            }
            off += 0x38;
        } while (--gc);
        return;
    }
    case 4:
    {
        if (groups <= 0)
            return;
        int off = 0;
        int gc  = groups;
        do
        {
            Group*   g   = (Group*)((uint8_t*)gb + off);
            float    top = *(float*)((uint8_t*)g->head + 0x110);
            int      cnt = (int)(g->end - g->items);
            if (cnt > 0)
            {
                uint8_t** it = g->items;
                int       k  = cnt;
                do
                {
                    uint8_t* e = *it;
                    float    x;
                    if (b.ey > 0.0f)
                        x = (top - (b.cy - b.ey * 0.5f)) / lineH;
                    else
                        x = 0.0f;
                    *(float*)(e + 0x6c) = x - (float)floor((double)x);
                    ++it;
                } while (--k);
            }
            off += 0x38;
        } while (--gc);
        return;
    }
    default:
    {
        if (groups <= 0)
            return;
        int off = 0;
        int gc  = groups;
        do
        {
            Group* g   = (Group*)((uint8_t*)gb + off);
            int    cnt = (int)(g->end - g->items);
            if (cnt > 0)
            {
                float  d   = b.ex * 0.1f;
                float  lo  = b.cx - d;
                float  hi  = d + b.cx;
                uint8_t** it = g->items;
                int       k  = cnt;
                do
                {
                    uint8_t* e = *it;
                    float    add = 0.0f;
                    if (lo <= *(float*)(e + 0x7c))
                        add = (*(float*)(e + 0x7c) <= hi) ? 0.25f : 0.5f;
                    float sum = *(float*)(e + 0x6c) + add;
                    *(float*)(e + 0x6c) = sum - (float)floor((double)sum);
                    ++it;
                } while (--k);
            }
            off += 0x38;
        } while (--gc);
    }
    }
}

// ---------------------------------------------------------------------------
// 0x009d2160 -- copy a layout description and lay out its entries
// ---------------------------------------------------------------------------
// @ 0x009d2160
void Layout::SetupFrom(Src* s)
{
    f60 = *(float*)((uint8_t*)s + 0x0c);
    f68 = s->f4c;
    f6c = s->f50;
    f70 = s->f54;
    f74 = s->f58;
    f78 = s->f5c;
    f7c = s->f60;
    f80 = s->f64;
    f84 = 1.0f - *(float*)((uint8_t*)s + 0x68) * 0.01f;
    f88 = s->f3c;
    fd4 = s->f40;
    fd8 = s->f44;
    f98 = s->f48;

    if (s->mode != -1)
    {
        uint32_t n   = (uint32_t)((int)(s->last - s->first) / 0xc);
        uint32_t cap = (uint32_t)(ie - ib);
        const uint32_t& limit = (cap < n) ? cap : n;
        if (limit != 0)
        {
            f64 = 0.0f;
            int groups = (int)(ge - gb);
            if (groups > 0)
            {
                int      off = 0;
                uint32_t idx = 0;
                int      gc  = groups;
                do
                {
                    Group* g   = (Group*)((uint8_t*)gb + off);
                    int    cnt = (int)(g->end - g->items);
                    if (cnt > 0)
                    {
                        uint8_t** it = g->items;
                        int       i  = 0;
                        do
                        {
                            if ((int)limit <= (int)idx)
                                break;
                            uint8_t* e = it[i];
                            *(float*)(e + 0x6c) = *(float*)(s->first + (size_t)idx * 0xc);
                            float v = *(float*)(s->first + (size_t)idx * 0xc + 4);
                            *(float*)(e + 0x78) = v;
                            f64 = v + f64;
                            ++idx;
                            ++i;
                        } while (i < cnt);
                    }
                    off += 0x38;
                } while (--gc);
            }
            f64 = f64 / (float)limit;
        }
        Apply(s);
    }

    if (s->mode == 7)
        AlignLines();

    f10 = s->seq[0];  f14 = s->seq[1];  f18 = s->seq[2];  f1c = s->seq[3];
    f20 = s->seq[4];  f24 = s->seq[5];  f28 = s->seq[6];  f2c = s->seq[7];
    f30 = s->seq[8];  f34 = s->seq[9];  f38 = s->seq[10]; f3c = s->seq[11];
    f40 = s->seq[12]; f44 = s->seq[13];
}

// ---------------------------------------------------------------------------
// 0x009d24c0 -- build gradient stops from a weight vector
// ---------------------------------------------------------------------------
// @ 0x009d24c0
void Layout::BuildStops(int n, void* a2, void* a3, void* a4, int32_t* a5)
{
    if (n > 1)
    {
        float w[4];
        float t = (float)(5 - *a5) * 0.2f;
        if (*a5 != 0)
            *a5 = *a5 - 1;
        FUN_009ce430(w, n);
        FUN_009ce560(w, n);
        uint8_t* base = (uint8_t*)a4 + 8;
        BeginGradient(base);
        for (int i = 0; i < n; ++i)
        {
            float v = w[i];
            if (1e-6f <= fabsf(v))
                AddStop(v, base + i * 0xb4);
        }
        EndGradient(base);
    }
    else
    {
        SetupFrom((Src*)a4);
    }
}

// ---------------------------------------------------------------------------
// 0x009d25b0 -- smallest normalised thickness over all entries
// ---------------------------------------------------------------------------
// @ 0x009d25b0
float Layout::MinThickness(Vec3 v)
{
    float best = g_big;
    float dx   = v.x;
    float dy   = v.y;
    float len  = sqrtf(dy * dy + dx * dx);
    if (len != 0.0f)
    {
        float inv = 1.0f / len;
        dy = inv * dy;
        dx = inv * dx;
    }

    int n = (int)(ie - ib);
    if (n > 0)
    {
        Atlas*   a    = f48;
        int32_t* p    = ib;
        int      cnt  = n;
        float    lens = dy * dy + dx * dx;
        do
        {
            uint8_t* e = EntryOf(a, *p);
            float    r;
            if (lens <= g_tiny)
                r = g_eps;
            else
            {
                float ac = *(float*)(e + 0xac);
                float u  = ac * dx;
                float a8 = *(float*)(e + 0xa8);
                float w  = a8 * dy;
                r = (a8 / sqrtf(w * w + u * u)) * ac;
            }
            if (r < best)
                best = r;
            ++p;
        } while (--cnt != 0);
    }
    return (g_eps > best) ? g_eps : best;
}

// ---------------------------------------------------------------------------
// 0x009d2700 -- angular scale factor of the thickest fitting entry
// ---------------------------------------------------------------------------
// @ 0x009d2700
float Layout::AngleScale(float angle)
{
    int n = (int)(ie - ib);

    if ((g_166c688 & 1) == 0)
    {
        g_166c688 |= 1;
        g_166c684 = (n < 7) ? 1.30899692f : 0.52359879f;
    }

    float best = g_166c684;
    if (n > 0)
    {
        float    base = f84;
        float    f98v = ff8;
        Atlas*   a    = f48;
        int32_t* p    = ib;
        int      cnt  = n;
        do
        {
            uint8_t* e     = EntryOf(a, *p);
            float    scale = base;
            if (g_1551256 != 0)
            {
                if ((g_166c688 & 2) == 0)
                {
                    g_166c688 |= 2;
                    g_166c680 = 1.57079637f;
                }
                float t = fabsf(angle) / g_166c680;
                if (t > 1.0f)
                    t = 1.0f;
                scale = base - ((*(float*)(e + 0xc0) * t) * t) * t;
            }
            float h  = *(float*)(e + 0x80);
            float th = fabsf(*(float*)(e + 0x7c)) +
                       ((scale - 1.0f) * fabsf(*(float*)(e + 0x7c) - f98v)) * 2.5f;
            float r = best;
            if (1e-12f < h * h + th * th)
            {
                float norm = sqrtf(h * h + th * th);
                float nx = h, ny = th;
                if (norm != 0.0f)
                {
                    nx = (1.0f / norm) * h;
                    ny = (1.0f / norm) * th;
                }
                float cur;
                if (ny * ny + nx * nx <= 1e-12f)
                    cur = 1e-6f;
                else
                {
                    float ac = *(float*)(e + 0xac);
                    float a8 = *(float*)(e + 0xa8);
                    float u  = ac * nx;
                    float v  = a8 * ny;
                    cur = (a8 / sqrtf(u * u + v * v)) * ac;
                }
                r = (1.75f - *(float*)(e + 0xc0) * 1.5f) * (cur / norm);
            }
            if (r < best)
                best = r;
            ++p;
        } while (--cnt != 0);
    }
    return (1e-6f > best) ? 1e-6f : best;
}
