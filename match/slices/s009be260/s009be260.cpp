// Slice s009be260
//
//   009be260  ResetBoneSlots(CreatureAnim*)       -- clear outputs, re-init every bone slot
//   009be750  uninitialized_copy<BodyVertex28>    -- (out, first, last, dst)
//   009be7d0  uninitialized_copy<Matrix30>        -- (out, first, last, dst)
//   009be850  Copy108c::operator=                 -- 0x10c body, tail block copied with rep movsd
//   009bea50  BodyInstance copy ctor              -- 0x2bc body
//   009bed40  copy<BodyVertex28>                  -- (first, last, dst)
//   009bee30  uninitialized_copy<WiggleInstance>  -- (out, first, last, dst)
//   009beec0  copy<WiggleInstance>                -- (first, last, src)
//   009bef30  fill_n<WiggleInstance>              -- (dst, n, src)
//   009befa0  Copy108::operator=                  -- 0x10c body, tail unrolled
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

struct V3 { float x, y, z; };
struct V4 { float x, y, z, w; };

// ---------------------------------------------------------------------------
// anim descriptor and bone slot layouts
// ---------------------------------------------------------------------------
struct AnimDesc {                       // *slot : creature animation descriptor
    uint32_t pad0[0x10c / 4];           // 0x00..0x10b
    float scaleX, scaleY, scaleZ;       // 0x10c..0x114
    V4 tint;                            // 0x118..0x127
};

struct BoneSlot {                       // 700 bytes
    AnimDesc* desc;                     // 0x00
    uint32_t pad04[3];                  // 0x04..0x0f
    V3 pos;                             // 0x10
    V4 tint;                            // 0x1c
    V3 zero;                            // 0x2c
    uint8_t flag38;                     // 0x38
    uint8_t pad39[3];
    V3 pos2;                            // 0x3c
    uint8_t pad48[0x2bc - 0x48];
};

struct CreatureAnim {
    uint32_t pad00[6];                  // 0x00..0x17
    V3 a18;                             // 0x18
    V3 b24;                             // 0x24
    V3 c30;                             // 0x30
    V4 d3c;                             // 0x3c
    V4 e4c;                             // 0x4c
    V4 f5c;                             // 0x5c
    float g6c;                          // 0x6c
    float h70;                          // 0x70
    V3 i74;                             // 0x74
    V3 j80;                             // 0x80
    V3 k8c;                             // 0x8c
    V3 l98;                             // 0x98
    V3 ma4;                             // 0xa4
    V3 nb0;                             // 0xb0
    V3 obc;                             // 0xbc
    V3 pc8;                             // 0xc8
    float qd4;                          // 0xd4
    uint8_t padD8[0x2e4 - 0xd8];
    uint8_t* slotsBegin;                // 0x2e4
    uint8_t* slotsEnd;                  // 0x2e8
};

static void InitSlot(BoneSlot* s, float t) {
    s->pos.x = s->desc->scaleX * t;
    s->pos.y = s->desc->scaleY * t;
    s->pos.z = s->desc->scaleZ * t;
    s->pos2.x = s->pos.x;
    s->pos2.y = s->pos.y;
    s->pos2.z = s->pos.z;
    s->tint.x = s->desc->tint.x;
    s->tint.y = s->desc->tint.y;
    s->tint.z = s->desc->tint.z;
    s->tint.w = s->desc->tint.w;
    s->zero.x = 0.0f;
    s->zero.y = 0.0f;
    s->zero.z = 0.0f;
    s->flag38 = 1;
}

// @ 0x009be260
void __cdecl FUN_009be260(CreatureAnim* c) {
    c->a18.x = 0.0f; c->a18.y = 0.0f; c->a18.z = 0.0f;
    c->d3c.x = 0.0f; c->d3c.y = 0.0f; c->d3c.z = 0.0f; c->d3c.w = 1.0f;
    c->i74.x = 0.0f; c->i74.y = 0.0f; c->i74.z = 0.0f;
    c->k8c.x = 0.0f; c->k8c.y = 0.0f; c->k8c.z = 0.0f;
    c->ma4.x = 0.0f; c->ma4.y = 0.0f; c->ma4.z = 0.0f;
    c->nb0.x = 0.0f; c->nb0.y = 0.0f; c->nb0.z = 0.0f;
    c->obc.x = 0.0f; c->obc.y = 0.0f; c->obc.z = 0.0f;
    c->pc8.x = 0.0f; c->pc8.y = 0.0f; c->pc8.z = 0.0f;
    c->qd4 = 1.0f;
    c->h70 = c->g6c;
    c->c30 = c->a18;
    c->b24 = c->c30;
    c->j80 = c->i74;
    c->f5c = c->d3c;
    c->e4c = c->f5c;

    int n = (int)((c->slotsEnd - c->slotsBegin) / 700);
    float t = c->h70;
    BoneSlot* slots = (BoneSlot*)c->slotsBegin;
    for (int i = 0; i < n; i++) InitSlot(&slots[i], t);
}

// ---------------------------------------------------------------------------
// 0x28 element: { int, int, float[8] }
// ---------------------------------------------------------------------------
struct BodyVertex28 { int a; int b; float f[8]; };

// @ 0x009be750
BodyVertex28** __cdecl FUN_009be750(BodyVertex28** out, const BodyVertex28* first,
                                    const BodyVertex28* last, BodyVertex28* dst) {
    *out = dst;
    if (first != last) {
        do {
            if (dst) {
                dst->a = first->a;
                dst->b = first->b;
                dst->f[0] = first->f[0]; dst->f[1] = first->f[1];
                dst->f[2] = first->f[2]; dst->f[3] = first->f[3];
                dst->f[4] = first->f[4]; dst->f[5] = first->f[5];
                dst->f[6] = first->f[6]; dst->f[7] = first->f[7];
            }
            first++; dst++;
        } while (first != last);
        *out = dst;
    }
    return out;
}

// @ 0x009bed40
BodyVertex28* __cdecl FUN_009bed40(const BodyVertex28* first, const BodyVertex28* last,
                                   BodyVertex28* dst) {
    if (first != last) {
        do {
            dst->a = first->a;
            dst->b = first->b;
            dst->f[0] = first->f[0]; dst->f[1] = first->f[1];
            dst->f[2] = first->f[2]; dst->f[3] = first->f[3];
            dst->f[4] = first->f[4]; dst->f[5] = first->f[5];
            dst->f[6] = first->f[6]; dst->f[7] = first->f[7];
            first++; dst++;
        } while (first != last);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// 0x30 element: twelve floats copied in the original's column order
// ---------------------------------------------------------------------------
struct Matrix30 { float f[12]; };

// @ 0x009be7d0
Matrix30** __cdecl FUN_009be7d0(Matrix30** out, const Matrix30* first,
                                const Matrix30* last, Matrix30* dst) {
    *out = dst;
    if (first != last) {
        do {
            if (dst) {
                dst->f[0]  = first->f[0];
                dst->f[3]  = first->f[3];
                dst->f[6]  = first->f[6];
                dst->f[1]  = first->f[1];
                dst->f[4]  = first->f[4];
                dst->f[7]  = first->f[7];
                dst->f[2]  = first->f[2];
                dst->f[5]  = first->f[5];
                dst->f[8]  = first->f[8];
                dst->f[9]  = first->f[9];
                dst->f[10] = first->f[10];
                dst->f[11] = first->f[11];
            }
            first++; dst++;
        } while (first != last);
        *out = dst;
    }
    return out;
}

// ---------------------------------------------------------------------------
// 0x2c element: nSPCreatureAnim::creature_body_wiggle_instance_data
// ---------------------------------------------------------------------------
struct WiggleInstance {
    const void* static_data;            // 0x00
    bool enabled;                       // 0x04
    bool force_override;                // 0x05
    V3 world_vel;                       // 0x08
    V3 world_pos;                       // 0x14
    V3 world_pos_old;                   // 0x20
};

// @ 0x009bee30
WiggleInstance** __cdecl FUN_009bee30(WiggleInstance** out, const WiggleInstance* first,
                                      const WiggleInstance* last, WiggleInstance* dst) {
    *out = dst;
    if (first != last) {
        do {
            if (dst) {
                dst->static_data = first->static_data;
                dst->enabled = first->enabled;
                dst->force_override = first->force_override;
                dst->world_vel = first->world_vel;
                dst->world_pos = first->world_pos;
                dst->world_pos_old = first->world_pos_old;
            }
            first++; dst++;
        } while (first != last);
        *out = dst;
    }
    return out;
}

// @ 0x009beec0
void __cdecl FUN_009beec0(WiggleInstance* first, WiggleInstance* last,
                          const WiggleInstance* src) {
    if (first != last) {
        do {
            first->static_data = src->static_data;
            first->enabled = src->enabled;
            first->force_override = src->force_override;
            first->world_vel = src->world_vel;
            first->world_pos = src->world_pos;
            first->world_pos_old = src->world_pos_old;
            first++;
        } while (first != last);
    }
}

// @ 0x009bef30
void __cdecl FUN_009bef30(WiggleInstance* dst, unsigned n, const WiggleInstance* src) {
    if (n == 0) return;
    do {
        if (dst) {
            dst->static_data = src->static_data;
            dst->enabled = src->enabled;
            dst->force_override = src->force_override;
            dst->world_vel = src->world_vel;
            dst->world_pos = src->world_pos;
            dst->world_pos_old = src->world_pos_old;
        }
        n--; dst++;
    } while (n != 0);
}

// ---------------------------------------------------------------------------
// 0x10c copy helpers (two flavours of the same 0x00..0xd4 prefix)
// ---------------------------------------------------------------------------
struct Blob12 { int d[12]; };

struct Copy108 {                        // 0x009befa0: tail unrolled
    int i[4];                           // 0x00..0x0c
    float a[28];                        // 0x10..0x7c
    float b[5];                         // 0x80..0x90
    int m;                              // 0x94
    float c[13];                        // 0x98..0xc8
    int j[3];                           // 0xcc..0xd4
    int k[12];                          // 0xd8..0x104
    int n;                              // 0x108
    Copy108& operator=(const Copy108& o);
};

// @ 0x009befa0
Copy108& Copy108::operator=(const Copy108& o) {
    i[0] = o.i[0]; i[1] = o.i[1]; i[2] = o.i[2]; i[3] = o.i[3];
    a[0] = o.a[0]; a[1] = o.a[1]; a[2] = o.a[2]; a[3] = o.a[3];
    a[4] = o.a[4]; a[5] = o.a[5]; a[6] = o.a[6]; a[7] = o.a[7];
    a[8] = o.a[8]; a[9] = o.a[9]; a[10] = o.a[10]; a[11] = o.a[11];
    a[12] = o.a[12]; a[13] = o.a[13]; a[14] = o.a[14]; a[15] = o.a[15];
    a[16] = o.a[16]; a[17] = o.a[17]; a[18] = o.a[18]; a[19] = o.a[19];
    a[20] = o.a[20]; a[21] = o.a[21]; a[22] = o.a[22]; a[23] = o.a[23];
    a[24] = o.a[24]; a[25] = o.a[25]; a[26] = o.a[26]; a[27] = o.a[27];
    b[0] = o.b[0]; b[1] = o.b[1]; b[2] = o.b[2]; b[3] = o.b[3]; b[4] = o.b[4];
    m = o.m;
    c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; c[3] = o.c[3];
    c[4] = o.c[4]; c[5] = o.c[5]; c[6] = o.c[6]; c[7] = o.c[7];
    c[8] = o.c[8]; c[9] = o.c[9]; c[10] = o.c[10]; c[11] = o.c[11];
    c[12] = o.c[12];
    j[0] = o.j[0]; j[1] = o.j[1]; j[2] = o.j[2];
    k[0] = o.k[0]; k[1] = o.k[1]; k[2] = o.k[2]; k[3] = o.k[3];
    k[4] = o.k[4]; k[5] = o.k[5]; k[6] = o.k[6]; k[7] = o.k[7];
    k[8] = o.k[8]; k[9] = o.k[9]; k[10] = o.k[10]; k[11] = o.k[11];
    n = o.n;
    return *this;
}

struct Copy108c {                       // 0x009be850: tail is one block (rep movsd)
    int i[4];                           // 0x00..0x0c
    float a[28];                        // 0x10..0x7c
    float b[5];                         // 0x80..0x90
    int m;                              // 0x94
    float c[13];                        // 0x98..0xc8
    int j[3];                           // 0xcc..0xd4
    Blob12 k;                           // 0xd8..0x104
    int n;                              // 0x108
    Copy108c& operator=(const Copy108c& o);
};

// @ 0x009be850
Copy108c& Copy108c::operator=(const Copy108c& o) {
    i[0] = o.i[0]; i[1] = o.i[1]; i[2] = o.i[2]; i[3] = o.i[3];
    a[0] = o.a[0]; a[1] = o.a[1]; a[2] = o.a[2]; a[3] = o.a[3];
    a[4] = o.a[4]; a[5] = o.a[5]; a[6] = o.a[6]; a[7] = o.a[7];
    a[8] = o.a[8]; a[9] = o.a[9]; a[10] = o.a[10]; a[11] = o.a[11];
    a[12] = o.a[12]; a[13] = o.a[13]; a[14] = o.a[14]; a[15] = o.a[15];
    a[16] = o.a[16]; a[17] = o.a[17]; a[18] = o.a[18]; a[19] = o.a[19];
    a[20] = o.a[20]; a[21] = o.a[21]; a[22] = o.a[22]; a[23] = o.a[23];
    a[24] = o.a[24]; a[25] = o.a[25]; a[26] = o.a[26]; a[27] = o.a[27];
    b[0] = o.b[0]; b[1] = o.b[1]; b[2] = o.b[2]; b[3] = o.b[3]; b[4] = o.b[4];
    m = o.m;
    c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; c[3] = o.c[3];
    c[4] = o.c[4]; c[5] = o.c[5]; c[6] = o.c[6]; c[7] = o.c[7];
    c[8] = o.c[8]; c[9] = o.c[9]; c[10] = o.c[10]; c[11] = o.c[11];
    c[12] = o.c[12];
    j[0] = o.j[0]; j[1] = o.j[1]; j[2] = o.j[2];
    k = o.k;
    n = o.n;
    return *this;
}

// ---------------------------------------------------------------------------
// @ 0x009bea50  0x2bc body-instance copy ctor
// ---------------------------------------------------------------------------
struct Sub18c {                         // 0x18c..0x27f (0xf4), copied by 0x009b45b0
    uint8_t d[0xf4];
    void Init(const Sub18c& o);
};

struct Blob41 { int d[41]; };           // 0xa0..0x143

struct Body2bc {
    int i00, i04, i08, i0c;             // 0x00..0x0c
    float f[10];                        // 0x10..0x34
    uint8_t b38;                        // 0x38
    uint8_t pad39[3];
    float g[3];                         // 0x3c..0x44
    int j[3];                           // 0x48..0x50
    uint8_t b54, b55;                   // 0x54,0x55
    uint8_t pad56[2];
    float h[18];                        // 0x58..0x9c
    Blob41 arr;                         // 0xa0..0x143
    int i144;                           // 0x144
    float p[17];                        // 0x148..0x188
    Sub18c sub;                         // 0x18c..0x27f
    float q[8];                         // 0x280..0x29c
    uint8_t b2a0;                       // 0x2a0
    uint8_t pad2a1[3];
    float r[6];                         // 0x2a4..0x2b8

    Body2bc(const Body2bc& o);
};

Body2bc::Body2bc(const Body2bc& o) {
    i00 = o.i00; i04 = o.i04; i08 = o.i08; i0c = o.i0c;
    f[0] = o.f[0]; f[1] = o.f[1]; f[2] = o.f[2]; f[3] = o.f[3]; f[4] = o.f[4];
    f[5] = o.f[5]; f[6] = o.f[6]; f[7] = o.f[7]; f[8] = o.f[8]; f[9] = o.f[9];
    b38 = o.b38;
    g[0] = o.g[0]; g[1] = o.g[1]; g[2] = o.g[2];
    j[0] = o.j[0]; j[1] = o.j[1]; j[2] = o.j[2];
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
