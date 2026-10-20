// Slice s009bf210
//
//   009bf210  Body2bcF copy ctor            -- same 0x2bc body as 009bea50, but 0x48..0x50 are floats
//   009bf680  creature-body-anim reset ctor -- SSE zero/one init + two member calls
//   009bf860  wiggle static-data recompute  -- per-element sqrt/length update
//   009bfa20  anim teardown/rebuild         -- calls 009b4ce0 + 009bf860 then walks the array
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

struct V3 { float x, y, z; };

// ---------------------------------------------------------------------------
// sub-object at +0x18c of the 0x2bc body (0xf4 bytes), own copy/reset routines
// ---------------------------------------------------------------------------
struct Sub18c {                         // 0x18c..0x27f
    uint8_t d[0xf4];
    void Init(const Sub18c& o);         // -> 0x009b45b0 (009bea50 flavour)
};
struct Sub18cF {                        // same layout, different copy routine
    uint8_t d[0xf4];
    void Init(const Sub18cF& o);        // -> 0x009b45d0 (009bf210 flavour)
    void Reset();                       // -> 0x009b2e50 (009bf680)
};

struct Blob41 { int d[41]; };           // 0xa0..0x143

// ---------------------------------------------------------------------------
// @ 0x009bf210  copy ctor of the 0x2bc body (float variant of 009bea50)
// ---------------------------------------------------------------------------
struct Body2bcF {
    int i00, i04, i08, i0c;             // 0x00..0x0c
    float f[10];                        // 0x10..0x34
    uint8_t b38;                        // 0x38
    uint8_t pad39[3];
    float g[3];                         // 0x3c..0x44
    float j3[3];                        // 0x48..0x50   (floats in this flavour)
    uint8_t b54, b55;                   // 0x54,0x55
    uint8_t pad56[2];
    float h[18];                        // 0x58..0x9c
    Blob41 arr;                         // 0xa0..0x143
    int i144;                           // 0x144
    float p[17];                        // 0x148..0x188
    Sub18cF sub;                        // 0x18c..0x27f
    float q[8];                         // 0x280..0x29c
    uint8_t b2a0;                       // 0x2a0
    uint8_t pad2a1[3];
    float r[6];                         // 0x2a4..0x2b8

    Body2bcF(const Body2bcF& o);
};

Body2bcF::Body2bcF(const Body2bcF& o) {
    i00 = o.i00; i04 = o.i04; i08 = o.i08; i0c = o.i0c;
    f[0] = o.f[0]; f[1] = o.f[1]; f[2] = o.f[2]; f[3] = o.f[3]; f[4] = o.f[4];
    f[5] = o.f[5]; f[6] = o.f[6]; f[7] = o.f[7]; f[8] = o.f[8]; f[9] = o.f[9];
    b38 = o.b38;
    g[0] = o.g[0]; g[1] = o.g[1]; g[2] = o.g[2];
    j3[0] = o.j3[0]; j3[1] = o.j3[1]; j3[2] = o.j3[2];
    b54 = o.b54; b55 = o.b55;
    h[0] = o.h[0]; h[1] = o.h[1]; h[2] = o.h[2]; h[3] = o.h[3];
    h[4] = o.h[4]; h[5] = o.h[5]; h[6] = o.h[6]; h[7] = o.h[7];
    h[8] = o.h[8]; h[9] = o.h[9]; h[10] = o.h[10]; h[11] = o.h[11];
    h[12] = o.h[12]; h[13] = o.h[13]; h[14] = o.h[14]; h[15] = o.h[15];
    h[16] = o.h[16]; h[17] = o.h[17];
    arr = o.arr;
    i144 = o.i144;
    p[0] = o.p[0]; p[1] = o.p[1]; p[2] = o.p[2]; p[3] = o.p[3];
    p[4] = o.p[4]; p[5] = o.p[5]; p[6] = o.p[6]; p[7] = o.p[7];
    p[8] = o.p[8]; p[9] = o.p[9]; p[10] = o.p[10]; p[11] = o.p[11];
    p[12] = o.p[12]; p[13] = o.p[13]; p[14] = o.p[14]; p[15] = o.p[15];
    p[16] = o.p[16];
    sub.Init(o.sub);
    q[0] = o.q[0]; q[1] = o.q[1]; q[2] = o.q[2]; q[3] = o.q[3];
    q[4] = o.q[4]; q[5] = o.q[5]; q[6] = o.q[6]; q[7] = o.q[7];
    b2a0 = o.b2a0;
    r[0] = o.r[0]; r[1] = o.r[1]; r[2] = o.r[2];
    r[3] = o.r[3]; r[4] = o.r[4]; r[5] = o.r[5];
}

// ---------------------------------------------------------------------------
// @ 0x009bf680  the creature-body animation object reset ctor
// ---------------------------------------------------------------------------
struct BodyAnimC {
    uint8_t pad00[0x10];
    V3 a;                               // 0x10
    V3 b;                               // 0x1c
    float c;                            // 0x28
    V3 d;                               // 0x2c
    int unk38;                          // 0x38 (untouched)
    V3 e;                               // 0x3c
    uint8_t pad48[0x10];                // 0x48..0x57 (untouched)
    float f[18];                        // 0x58..0x9c
    int g;                              // 0xa0
    uint8_t padA4[0x148 - 0xa4];
    V3 h;                               // 0x148
    float i;                            // 0x154
    V3 j;                               // 0x158
    V3 k;                               // 0x164
    V3 l;                               // 0x170
    V3 m;                               // 0x17c
    float n;                            // 0x188
    Sub18cF sub;                        // 0x18c..0x27f
    V3 o;                               // 0x280
    V3 p;                               // 0x28c
    float q;                            // 0x298
    uint8_t pad29c[8];                  // 0x29c..0x2a3
    V3 r;                               // 0x2a4
    V3 s;                               // 0x2b0
    void Finalize();                    // -> 0x009b5a00

    BodyAnimC();
};

BodyAnimC::BodyAnimC() {
    a.z = 0.0f; a.y = 0.0f; a.x = 0.0f;
    b.z = 0.0f; b.y = 0.0f; b.x = 0.0f;
    c = 1.0f;
    d.z = 0.0f; d.y = 0.0f; d.x = 0.0f;
    e.z = 0.0f; e.y = 0.0f; e.x = 0.0f;
    f[0] = 0.0f;  f[1] = 0.0f;  f[2] = 0.0f;  f[3] = 0.0f;  f[4] = 0.0f;
    f[5] = 0.0f;  f[6] = 0.0f;  f[7] = 0.0f;  f[8] = 0.0f;  f[9] = 0.0f;
    f[10] = 0.0f; f[11] = 0.0f; f[12] = 0.0f; f[13] = 0.0f; f[14] = 0.0f;
    f[15] = 0.0f; f[16] = 0.0f; f[17] = 0.0f;
    g = 0;
    h.z = 0.0f; h.y = 0.0f; h.x = 0.0f;
    i = 1.0f;
    j.z = 0.0f; j.y = 0.0f; j.x = 0.0f;
    k.z = 0.0f; k.y = 0.0f; k.x = 0.0f;
    l.z = 0.0f; l.y = 0.0f; l.x = 0.0f;
    m.z = 0.0f; m.y = 0.0f; m.x = 0.0f;
    n = 1.0f;
    sub.Reset();
    o.z = 0.0f; o.y = 0.0f; o.x = 0.0f;
    p.z = 0.0f; p.y = 0.0f; p.x = 0.0f;
    q = 1.0f;
    r.z = 0.0f; r.y = 0.0f; r.x = 0.0f;
    s.z = 0.0f; s.y = 0.0f; s.x = 0.0f;
    Finalize();
}

// ---------------------------------------------------------------------------
// the animation graph the two functions below walk: an array of 0x468-byte
// node records hung off the container at +0x384/+0x388
// ---------------------------------------------------------------------------
struct WiggleElem {
    uint8_t pad000[0x10c];
    V3 pos;                             // 0x10c
    uint8_t pad118[0x150 - 0x118];
    unsigned flags;                     // 0x150
    uint8_t pad154[0x1f8 - 0x154];
    int link1;                          // 0x1f8
    uint8_t pad1fc[0x204 - 0x1fc];
    int first;                          // 0x204  first dependent node
    int count;                          // 0x208  number of dependents
    uint8_t pad20c[0x430 - 0x20c];
    int link2;                          // 0x430
    float dist;                         // 0x434
    float span;                         // 0x438
    float gap;                          // 0x43c
    int root;                           // 0x440  -1 none, -2 merged, -3 orphan
    int other;                          // 0x444
};

struct WiggleAnim {
    uint8_t pad000[0x384];
    WiggleElem* beg;                    // 0x384
    WiggleElem* end;                    // 0x388
    uint8_t pad38c[0x3e4 - 0x38c];
    float maxDist;                      // 0x3e4
    float maxDist2;                     // 0x3e8

    void Prep();                        // -> 0x009b4ce0
    void Recompute();                   // -> 0x009bf860
    float Weight(WiggleElem* e);        // -> 0x009b5200
    void Walk();                        // -> 0x009bfa20
};

float g_eps = 1e-6f;                    // -> 0x014471fc

void FUN_009b4ef0(void* p);             // -> 0x009b4ef0, cdecl pointer arg

// ---------------------------------------------------------------------------
// @ 0x009bf860  recompute per-node span/dist/gap and the two running maxima
// ---------------------------------------------------------------------------
void WiggleAnim::Recompute() {
    maxDist = 0.0f;
    maxDist2 = 0.0f;
    int n = (int)((int)((char*)end - (char*)beg) / 0x468);
    if (n <= 0) return;

    for (int i = 0; i < n; i++) {
        WiggleElem* node = (WiggleElem*)((char*)beg + i * 0x468);
        WiggleElem* a = (WiggleElem*)((char*)beg + node->link1 * 0x468);
        WiggleElem* b = (WiggleElem*)((char*)beg + node->link2 * 0x468);

        float dx = a->pos.x - b->pos.x;
        float dy = a->pos.y - b->pos.y;
        float dz = a->pos.z - b->pos.z;

        float local[3];
        local[1] = 0.01f;
        local[0] = (float)sqrt(dx * dx + dy * dy + dz * dz);
        float* p = local;
        if (local[0] <= local[1]) p = local + 1;
        node->span = *p;

        float w = Weight(node);
        node->dist = w;
        if (maxDist < w) maxDist = w;
        if ((node->flags & 4) && (node->dist > maxDist2)) maxDist2 = node->dist;

        local[2] = b->pos.z - node->pos.z;
        float* q = local + 2;
        if (local[2] <= g_eps) q = &g_eps;
        node->gap = *q;
    }
}

// ---------------------------------------------------------------------------
// @ 0x009bfa20  resolve the parent (-1) markers over the dependent ranges
// ---------------------------------------------------------------------------
void WiggleAnim::Walk() {
    Prep();
    Recompute();

    unsigned count = (unsigned)((int)((char*)end - (char*)beg) / 0x468);
    int i = (int)count - 1;
    if (i < 0) return;

    do {
        WiggleElem* node = (WiggleElem*)((char*)beg + i * 0x468);
        unsigned nflags = node->flags;
        unsigned d = (unsigned)node->first;
        unsigned dend = (unsigned)node->count + d;
        node->root = -1;
        node->other = -1;
        unsigned kept = 0xffffffff;
        int seen = 0;

        if (d < dend) {
            unsigned j = d;
            do {
                WiggleElem* dep = (WiggleElem*)((char*)beg + j * 0x468);
                if ((dep->flags & 8) == 0) {
                    if ((dep->flags & 4) == 0) {
                        if (dep->root != -1) {
                            if (((nflags >> 3 & 1) == 0) && seen == 0) {
                                node->root = dep->root;
                                kept = 0xffffffff;
                                if (dep->root != -2) kept = j;
                                seen = 1;
                            } else {
                                if (kept != 0xffffffff && seen == 1) {
                                    FUN_009b4ef0((char*)beg + kept * 0x468);
                                    node->root = -2;
                                }
                                if (dep->root != -2) FUN_009b4ef0(dep);
                                seen++;
                            }
                        }
                    } else {
                        node->root = (int)j;
                        dep->root = (int)j;
                    }
                }
                j++;
            } while (j < dend);
        }

        if (node->root < (int)count) {
            unsigned k1 = (unsigned)node->first;
            unsigned kend = (unsigned)node->count + k1;
            if (k1 < kend) {
                unsigned k = k1;
                do {
                    WiggleElem* dep = (WiggleElem*)((char*)beg + k * 0x468);
                    if (dep->root == -1) dep->root = -3;
                    k++;
                } while (k < kend);
            }
        }

        i--;
    } while (i >= 0);
}
