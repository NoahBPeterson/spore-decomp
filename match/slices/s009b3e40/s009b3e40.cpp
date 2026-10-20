// nSPCreatureAnim body-structure copy/fill helpers (slice s009b3e40).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>
#include <math.h>
#include <intrin.h>

namespace nSPCreatureAnim {

struct vector_3 { float x, y, z; };

// 0x3c-byte wiggle descriptor (same layout as s009b3180 CopyBlock)
struct wiggle_static_data {
    int   a0, a1, a2, a3;              // +0x00
    float f[10];                       // +0x10
    uint8_t c;                         // +0x38
    uint8_t pad_39[3];
    wiggle_static_data& operator=(const wiggle_static_data& o)
    {
        a0 = o.a0; a1 = o.a1; a2 = o.a2; a3 = o.a3;
        f[0] = o.f[0]; f[1] = o.f[1]; f[2] = o.f[2]; f[3] = o.f[3]; f[4] = o.f[4];
        f[5] = o.f[5]; f[6] = o.f[6]; f[7] = o.f[7]; f[8] = o.f[8]; f[9] = o.f[9];
        c = o.c;
        return *this;
    }
};

// 0x2c-byte wiggle instance element
struct wiggle_instance_data {
    void*   wiggle;                    // +0x00
    uint8_t flag4;                     // +0x04
    uint8_t flag5;                     // +0x05
    uint8_t pad_06[2];
    float   f[9];                      // +0x08
    wiggle_instance_data& operator=(const wiggle_instance_data& o);   // 0x009b4230
};

// 0x30-byte transform: matrix (column-order copy) + vector
struct xform12 {
    float m[9];                        // +0x00
    float v[3];                        // +0x24
    xform12& operator=(const xform12& o);   // 0x009b41e0
};

// 0x30-byte sequential transform (int, int, float[10])
struct Transform30 {
    int   a;                           // +0x00
    int   b;                           // +0x04
    float f[10];                       // +0x08
    Transform30& operator=(const Transform30& o)
    {
        a = o.a; b = o.b;
        f[0] = o.f[0]; f[1] = o.f[1]; f[2] = o.f[2]; f[3] = o.f[3]; f[4] = o.f[4];
        f[5] = o.f[5]; f[6] = o.f[6]; f[7] = o.f[7]; f[8] = o.f[8]; f[9] = o.f[9];
        return *this;
    }
};

// 0x30-byte bone transform: matrix copied raw + vector
struct bone_xform {
    float m[9];                        // +0x00
    float v[3];                        // +0x24
    bone_xform& operator=(const bone_xform& o)
    {
        __movsd((unsigned long*)m, (unsigned long*)o.m, 9);
        float* d = v; const float* s = o.v;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2];
        return *this;
    }
};

// 0xf4-byte blob
struct blob_f4 {
    uint32_t u00;                      // +0x00
    float    f04[7];                   // +0x04
    uint32_t u20;                      // +0x20
    float    f24[19];                  // +0x24
    uint8_t  b70, b71;                 // +0x70
    float    f74[3];                   // +0x74
    float    f80[6];                   // +0x80
    uint32_t u98[4];                   // +0x98
    uint8_t  ba8, ba9;                 // +0xa8
    uint32_t uac;                      // +0xac
    float    fb0;                      // +0xb0
    uint32_t ub4, ub8;                 // +0xb4
    float    fbc[14];                  // +0xbc
    blob_f4& operator=(const blob_f4& o);   // 0x009b45b0
};

// creature body static data, 0x468 bytes
struct creature_body_static_data {
    char     name[0x104];              // +0x000
    uint32_t instance_id;              // +0x104
    uint32_t group_id;                 // +0x108
    float    f10c[17];                 // +0x10c
    uint32_t w150[0x2a];               // +0x150
    uint32_t w1f8[10];                 // +0x1f8
    uint32_t w220[0x41];               // +0x220
    float    f324[6];                  // +0x324
    uint32_t u33c;                     // +0x33c
    uint8_t  b340;                     // +0x340
    uint8_t  pad341[3];
    float    f344[11];                 // +0x344
    uint8_t  b370;                     // +0x370
    uint8_t  b371;                     // +0x371
    uint8_t  pad372[2];
    float    f374[3];                  // +0x374
    uint32_t w380[0x29];               // +0x380
    uint32_t u424;                     // +0x424
    uint32_t u428;                     // +0x428
    uint8_t  b42c;                     // +0x42c
    uint8_t  pad42d[3];
    uint32_t u430;                     // +0x430
    float    f434[3];                  // +0x434
    uint32_t u440;                     // +0x440
    uint32_t u444;                     // +0x444
    float    f448[7];                  // +0x448
    uint8_t  b464;                     // +0x464
    uint8_t  pad465[3];
    creature_body_static_data& operator=(const creature_body_static_data& o);   // 0x009b3e40
};

// creature static data (owner of the Bodies vector)
struct creature_static_data {
    uint8_t  pad_000[0x384];
    creature_body_static_data* Bodies;      // +0x384
    creature_body_static_data* BodiesEnd;   // +0x388
    uint8_t  pad_38c[0x440 - 0x38c];
    uint32_t u440;                          // +0x440
    void FUN_009b4ce0();
};

}  // namespace nSPCreatureAnim

using namespace nSPCreatureAnim;

void NormalizeVec3(float* out, const float* v, float* lenOut);   // 0x009a49d0

// ---- definitions -----------------------------------------------------------

// @ 0x009B3E40
creature_body_static_data& creature_body_static_data::operator=(const creature_body_static_data& o)
{
    memcpy(name, o.name, 0x104);
    instance_id = o.instance_id;
    group_id = o.group_id;
    f10c[0] = o.f10c[0]; f10c[1] = o.f10c[1]; f10c[2] = o.f10c[2]; f10c[3] = o.f10c[3];
    f10c[4] = o.f10c[4]; f10c[5] = o.f10c[5]; f10c[6] = o.f10c[6]; f10c[7] = o.f10c[7];
    f10c[8] = o.f10c[8]; f10c[9] = o.f10c[9]; f10c[10] = o.f10c[10]; f10c[11] = o.f10c[11];
    f10c[12] = o.f10c[12]; f10c[13] = o.f10c[13]; f10c[14] = o.f10c[14]; f10c[15] = o.f10c[15];
    f10c[16] = o.f10c[16];
    memcpy(w150, o.w150, 0x2a * 4);
    w1f8[0] = o.w1f8[0]; w1f8[1] = o.w1f8[1]; w1f8[2] = o.w1f8[2]; w1f8[3] = o.w1f8[3];
    w1f8[4] = o.w1f8[4]; w1f8[5] = o.w1f8[5]; w1f8[6] = o.w1f8[6]; w1f8[7] = o.w1f8[7];
    w1f8[8] = o.w1f8[8]; w1f8[9] = o.w1f8[9];
    memcpy(w220, o.w220, 0x41 * 4);
    f324[0] = o.f324[0]; f324[1] = o.f324[1]; f324[2] = o.f324[2];
    f324[3] = o.f324[3]; f324[4] = o.f324[4]; f324[5] = o.f324[5];
    u33c = o.u33c;
    b340 = o.b340;
    f344[0] = o.f344[0]; f344[1] = o.f344[1]; f344[2] = o.f344[2]; f344[3] = o.f344[3];
    f344[4] = o.f344[4]; f344[5] = o.f344[5]; f344[6] = o.f344[6]; f344[7] = o.f344[7];
    f344[8] = o.f344[8]; f344[9] = o.f344[9]; f344[10] = o.f344[10];
    b370 = o.b370;
    b371 = o.b371;
    f374[0] = o.f374[0]; f374[1] = o.f374[1]; f374[2] = o.f374[2];
    memcpy(w380, o.w380, 0x29 * 4);
    u424 = o.u424;
    u428 = o.u428;
    b42c = o.b42c;
    u430 = o.u430;
    f434[0] = o.f434[0]; f434[1] = o.f434[1]; f434[2] = o.f434[2];
    u440 = o.u440;
    u444 = o.u444;
    f448[0] = o.f448[0]; f448[1] = o.f448[1]; f448[2] = o.f448[2]; f448[3] = o.f448[3];
    f448[4] = o.f448[4]; f448[5] = o.f448[5]; f448[6] = o.f448[6];
    b464 = o.b464;
    return *this;
}

// @ 0x009B41E0
xform12& xform12::operator=(const xform12& o)
{
    m[0] = o.m[0]; m[3] = o.m[3]; m[6] = o.m[6];
    m[1] = o.m[1]; m[4] = o.m[4]; m[7] = o.m[7];
    m[2] = o.m[2]; m[5] = o.m[5]; m[8] = o.m[8];
    v[0] = o.v[0];
    v[1] = o.v[1];
    v[2] = o.v[2];
    return *this;
}

// @ 0x009B4230
wiggle_instance_data& wiggle_instance_data::operator=(const wiggle_instance_data& o)
{
    wiggle = o.wiggle;
    flag4 = o.flag4;
    flag5 = o.flag5;
    f[0] = o.f[0]; f[1] = o.f[1]; f[2] = o.f[2]; f[3] = o.f[3]; f[4] = o.f[4];
    f[5] = o.f[5]; f[6] = o.f[6]; f[7] = o.f[7]; f[8] = o.f[8];
    return *this;
}

// @ 0x009B4290
Transform30* CopyTransform30Guarded(Transform30* first, Transform30* last, Transform30* result)
{
    for (; first != last; ++first, ++result)
        if (result) {
            result->a = first->a;
            result->b = first->b;
            float* d = result->f; float* s = first->f;
            d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
            d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8]; d[9] = s[9];
        }
    return result;
}

// @ 0x009B4350
wiggle_static_data* CopyWigglesGuarded(wiggle_static_data* first, wiggle_static_data* last, wiggle_static_data* result)
{
    for (; first != last; ++first, ++result)
        if (result) {
            result->a0 = first->a0; result->a1 = first->a1;
            result->a2 = first->a2; result->a3 = first->a3;
            float* d = result->f; float* s = first->f;
            d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
            d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8]; d[9] = s[9];
            result->c = first->c;
        }
    return result;
}

// @ 0x009B43F0
wiggle_static_data* CopyWiggles(wiggle_static_data* first, wiggle_static_data* last, wiggle_static_data* result)
{
    for (; first != last; ++first, ++result) {
        result->a0 = first->a0; result->a1 = first->a1;
        result->a2 = first->a2; result->a3 = first->a3;
        float* d = result->f; float* s = first->f;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
        d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8]; d[9] = s[9];
        result->c = first->c;
    }
    return result;
}

// @ 0x009B4490
void FillBoneXforms(bone_xform* first, bone_xform* last, const bone_xform* value)
{
    for (; first != last; ++first)
        *first = *value;
}

// @ 0x009B44E0
void FillXform12(xform12* dest, uint32_t n, const xform12* value)
{
    for (; n != 0; --n, ++dest)
        if (dest) *dest = *value;
}

// @ 0x009B4550
bone_xform* CopyBoneXforms(bone_xform* first, bone_xform* last, bone_xform* result)
{
    for (; first != last; ++first, ++result)
        *result = *first;
    return result;
}

// @ 0x009B45B0
blob_f4& blob_f4::operator=(const blob_f4& o)
{
    u00 = o.u00;
    f04[0] = o.f04[0]; f04[1] = o.f04[1]; f04[2] = o.f04[2]; f04[3] = o.f04[3];
    f04[4] = o.f04[4]; f04[5] = o.f04[5]; f04[6] = o.f04[6];
    u20 = o.u20;
    f24[0] = o.f24[0]; f24[1] = o.f24[1]; f24[2] = o.f24[2]; f24[3] = o.f24[3];
    f24[4] = o.f24[4]; f24[5] = o.f24[5]; f24[6] = o.f24[6]; f24[7] = o.f24[7];
    f24[8] = o.f24[8]; f24[9] = o.f24[9]; f24[10] = o.f24[10]; f24[11] = o.f24[11];
    f24[12] = o.f24[12]; f24[13] = o.f24[13]; f24[14] = o.f24[14]; f24[15] = o.f24[15];
    f24[16] = o.f24[16]; f24[17] = o.f24[17]; f24[18] = o.f24[18];
    b70 = o.b70;
    b71 = o.b71;
    f74[0] = o.f74[0]; f74[1] = o.f74[1]; f74[2] = o.f74[2];
    f80[0] = o.f80[0]; f80[1] = o.f80[1]; f80[2] = o.f80[2];
    f80[3] = o.f80[3]; f80[4] = o.f80[4]; f80[5] = o.f80[5];
    u98[0] = o.u98[0]; u98[1] = o.u98[1]; u98[2] = o.u98[2]; u98[3] = o.u98[3];
    ba8 = o.ba8;
    ba9 = o.ba9;
    uac = o.uac;
    fb0 = o.fb0;
    ub4 = o.ub4;
    ub8 = o.ub8;
    fbc[0] = o.fbc[0]; fbc[1] = o.fbc[1]; fbc[2] = o.fbc[2]; fbc[3] = o.fbc[3];
    fbc[4] = o.fbc[4]; fbc[5] = o.fbc[5]; fbc[6] = o.fbc[6]; fbc[7] = o.fbc[7];
    fbc[8] = o.fbc[8]; fbc[9] = o.fbc[9]; fbc[10] = o.fbc[10]; fbc[11] = o.fbc[11];
    fbc[12] = o.fbc[12]; fbc[13] = o.fbc[13];
    return *this;
}

// @ 0x009B47F0
Transform30* CopyTransform30Backward(Transform30* first, Transform30* last, Transform30* result)
{
    while (last != first) {
        --last;
        --result;
        result->a = last->a;
        result->b = last->b;
        float* d = result->f; float* s = last->f;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
        d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8]; d[9] = s[9];
    }
    return result;
}

// @ 0x009B4870
wiggle_static_data* CopyWigglesBackward(wiggle_static_data* first, wiggle_static_data* last, wiggle_static_data* result)
{
    while (last != first) {
        --last;
        --result;
        result->a0 = last->a0; result->a1 = last->a1;
        result->a2 = last->a2; result->a3 = last->a3;
        float* d = result->f; float* s = last->f;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
        d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8]; d[9] = s[9];
        result->c = last->c;
    }
    return result;
}

// @ 0x009B4910
void CopyXform12Guarded(xform12* first, xform12* last, xform12* result)
{
    for (; first != last; ++first, ++result)
        if (result) *result = *first;
}

// @ 0x009B4990
wiggle_instance_data* CopyWiggleInstancesGuarded(wiggle_instance_data* first, wiggle_instance_data* last, wiggle_instance_data* result)
{
    for (; first != last; ++first, ++result)
        if (result) {
            result->wiggle = first->wiggle;
            result->flag4 = first->flag4;
            result->flag5 = first->flag5;
            float* d = result->f; float* s = first->f;
            d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
            d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8];
        }
    return result;
}

// @ 0x009B4A20
wiggle_instance_data* CopyWiggleInstances(wiggle_instance_data* first, wiggle_instance_data* last, wiggle_instance_data* result)
{
    for (; first != last; ++first, ++result) {
        result->wiggle = first->wiggle;
        result->flag4 = first->flag4;
        result->flag5 = first->flag5;
        float* d = result->f; float* s = first->f;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
        d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8];
    }
    return result;
}

// @ 0x009B4AB0
bone_xform* CopyBoneXformsBackward(bone_xform* first, bone_xform* last, bone_xform* result)
{
    while (last != first) {
        --last;
        --result;
        *result = *last;
    }
    return result;
}

// @ 0x009B4B10
wiggle_instance_data* CopyWiggleInstancesBackward(wiggle_instance_data* first, wiggle_instance_data* last, wiggle_instance_data* result)
{
    while (last != first) {
        --last;
        --result;
        result->wiggle = last->wiggle;
        result->flag4 = last->flag4;
        result->flag5 = last->flag5;
        float* d = result->f; float* s = last->f;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
        d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8];
    }
    return result;
}

// @ 0x009B4BA0
void FUN_009b4ba0(float* out, const float* v, const float* fallback)
{
    float nvec[3];
    float len;
    NormalizeVec3(nvec, v, &len);
    float angle;
    if (len < 1e-6f) {
        angle = 0.0f;
        if (fallback == 0) {
            float axis[3] = { 1.0f, 0.0f, 0.0f };
            fallback = axis;
        }
        nvec[0] = fallback[0];
        nvec[1] = fallback[1];
        nvec[2] = fallback[2];
    } else if (len < 0.01f) {
        if (v[3] >= 0.0f)
            angle = len * 2.0f;
        else
            angle = len * -2.0f;
    } else {
        float x = v[3];
        const float one = 1.0f;
        if (-1.0f < x) {
            if (one < x) x = one;
        } else {
            x = -1.0f;
        }
        angle = acosf(x) * 2.0f;
        if (angle > 3.1415927f)
            angle = angle - 6.2831855f;
    }
    out[0] = nvec[0];
    out[1] = nvec[1];
    out[2] = nvec[2];
    out[3] = angle;
}

// @ 0x009B4CE0
void creature_static_data::FUN_009b4ce0()
{
    int n = (int)(((int)((char*)BodiesEnd - (char*)Bodies)) / 0x468);
    for (int i = 0; i < n; ++i) {
        creature_body_static_data* b = Bodies + i;
        if (b != 0) {
            if ((b->w150[0] & 8) != 0) {
                b->u430 = b->w1f8[0];
            } else {
                uint32_t idx = b->w1f8[1];
                uint32_t cur;
                int cnt = 0;
                do {
                    cur = idx;
                    ++cnt;
                    if (cur == 0 || (Bodies[cur].w150[0] & 8) != 0) break;
                    idx = Bodies[cur].w1f8[1];
                } while (cnt < 0xff);
                b->u430 = cur;
            }
        }
    }
}

// @ 0x009B4D90  (retail uses a register ABI; written with ordinary parameters)
uint32_t FUN_009b4d90(creature_static_data* self, creature_body_static_data* b)
{
    creature_body_static_data* p = self->Bodies + self->u440;
    creature_body_static_data* parent = (creature_body_static_data*)p->w1f8[7];   // +0x214
    int n = 0;
    creature_body_static_data* c = parent;
    if (c != b) {
        do {
            c = (creature_body_static_data*)c->w1f8[7];
            ++n;
        } while (c != b);
        if (n == 0)
            return b->w1f8[0];
        if (n == 1)
            return p->w1f8[1];
        int k = n / 2 + 1;
        c = parent;
        for (;;) {
            if (c == b) return 0;
            --k;
            if (k == 0) break;
            c = (creature_body_static_data*)c->w1f8[7];
        }
        return c->w1f8[0];
    }
    return b->w1f8[0];
}
