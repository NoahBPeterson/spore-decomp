// nSPCreatureAnim layout slice s009f9b40.
//
// Toolchain: the shipped module is cl 13.10 (VC .NET 2003) SSE code; this slice is built with
// /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast.
#include "s009f9b40.h"
#include <string.h>
#include <math.h>

// ---- runtime float/int constants (not present in the on-disk image) ----
extern "C" const float g_one_01485720;      // 0x01485720  1.0f
extern "C" const float g_01550a28;          // 0x01550a28
extern "C" const float g_014853e0;          // 0x014853e0
extern "C" const float g_01551638;          // 0x01551638
extern "C" const float g_0166c990;          // 0x0166c990
extern "C" const float g_0155163c;          // 0x0155163c
extern "C" const float g_01550b08;          // 0x01550b08
extern "C" const float g_01551678;          // 0x01551678
extern "C" const float g_0155167c;          // 0x0155167c
extern "C" const float g_01551680;          // 0x01551680
extern "C" const float g_01551684;          // 0x01551684
extern "C" const int g_015509fc;            // 0x015509fc
extern "C" const int g_0166c01c;            // 0x0166c01c
extern "C" const int g_01550b0c;            // 0x01550b0c
extern "C" const int g_01550b10;            // 0x01550b10
extern "C" const int g_01550b14;            // 0x01550b14
extern "C" const int g_0166c020;            // 0x0166c020

// ---- helpers outside this slice (declared with their VAs; the harness binds them) ----
extern "C" void fn_009eab60(AnimLayout* self, float* v);            // 0x009EAB60
extern "C" void fn_009f4660(AnimLayout* self, float* v);            // 0x009F4660
extern "C" void* fn_011e0744(void* dst, const void* src, unsigned n); // 0x011E0744 (memcpy)
extern "C" void fn_009f3390(AnimLayout* self, float* v);            // 0x009F3390
extern "C" void fn_009f3af0(AnimLayout* self, float* v);            // 0x009F3AF0
extern "C" void fn_009fa310(AnimLayout* owner, AnimLayout* self);   // 0x009FA310
extern "C" void fn_009f9e20(AnimLayout* owner, AnimLayout* self);   // 0x009F9E20
extern "C" void fn_009fa170(AnimLayout* self);                      // 0x009FA170
extern "C" float* fn_0099c1a0(float* out, const float* quat, const float* vec); // 0x0099C1A0
extern "C" float* fn_009ac7a0(float* a, float* b, float* c, int d);  // 0x009AC7A0

extern "C" const float g_01550b00;          // 0x01550b00
extern "C" const float g_013f11c8;          // 0x013f11c8
extern "C" const float g_01485378;          // 0x01485378
extern "C" const int g_01550afc;            // 0x01550afc

// reference-returning max (the original selects an operand pointer and then loads it)
static __inline const float& hkMaxRef(const float& a, const float& b)
{
    return a > b ? a : b;
}

// @ 0x009f9b40
void animLayoutUpdate(AnimLayout* self)
{
    int n = (int)(self->m_poolEnd - self->m_poolBegin) / 0x2bc;
    float v[4];
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = g_one_01485720;

    self->m_f1b4 = g_one_01485720;
    self->m_f1b0 = g_01550a28;

    unsigned len = ((unsigned)(n + n + 7)) >> 3;
    int same = 0;
    if (g_015509fc != 0)
        same = memcmp(self->m_cache, self->m_mirror, len) == 0;

    if (same && self->m_flag10 != 0)
    {
        fn_009eab60(self, v);
    }
    else
    {
        fn_009f4660(self, v);
        fn_011e0744(self->m_mirror, self->m_cache, len);
    }

    fn_009f3390(self, v);
    fn_009f3af0(self, v);
    self->m_counter++;
}

// @ 0x009f9c60
float animLayoutScale(AnimLayout* self)
{
    float d = self->m_f140 * self->m_f138;
    d = d * g_014853e0;
    d = d / g_01551638;
    float inv = 1.0f / sqrtf(d);
    float r;
    if (inv > g_0166c990)
        r = inv;
    else
        r = g_0166c990;
    if (r > g_0155163c)
        r = g_0155163c;
    if (self->m_flag371 != 0)
        r *= g_01550b08;
    return r;
}

// @ 0x009f9ce0
int animNameAllowed(AnimNameHolder* obj)
{
    if (g_0166c01c != 0 && obj->m_name.HasTag(0x00657965))    // "eye"
        return 0;
    if (g_01550b0c != 0 && obj->m_name.HasTag(0x74756f6d))    // "mout"
        return 0;
    if (g_01550b10 != 0 && obj->m_name.HasTag(0x65677263))    // "crge"
        return 0;
    if (g_01550b14 != 0 && obj->m_name.HasTag(0x676e6977))    // "wing"
        return 0;
    if (obj->m_name.HasTag(0x6c637077))                       // "wpcl"
        return 0;
    if (obj->m_name.HasTag(0x6c63746d))                       // "mtcl"
        return 0;
    if (g_0166c020 != 0)
    {
        int v = obj->m_name.GetValue();
        if (v != 0)
            return 1;
        if (obj->m_208 == v)
            return 0;
    }
    return 1;
}

// @ 0x009f9dc0
void animLayoutSyncMat(void* unused, AnimLayout* self)
{
    self->m_mat[0] = self->m_src[0];
    self->m_mat[1] = self->m_src[1];
    self->m_mat[2] = self->m_src[2];
    self->m_mat[3] = self->m_src[3];
    self->m_mat[4] = self->m_src[4];
    self->m_mat[5] = self->m_src[5];
    self->m_mat[6] = self->m_src[6];
}

// @ 0x009fa770
void animLayoutEvaluateAll(AnimLayout* owner, AnimLayout* self)
{
    fn_009fa310(owner, self);

    AnimHierarchy* h = self->m_hier;
    unsigned n = (unsigned)h->m_20c;
    int off = h->m_204 * 0x2bc;
    for (unsigned i = 0; i < n; i++)
    {
        fn_009fa310(owner, (AnimLayout*)((char*)owner->m_poolBegin + off));
        off += 0x2bc;
    }
}

// @ 0x009fa7d0
void animLayoutResetOne(AnimLayout* owner, AnimLayout* self)
{
    self->m_quat[0] = g_01551678;
    self->m_quat[1] = g_0155167c;
    self->m_quat[2] = g_01551680;
    self->m_quat[3] = g_01551684;

    self->m_v158[0] = 0.0f;
    self->m_v158[1] = 0.0f;
    self->m_v158[2] = 0.0f;
    self->m_v164[0] = 0.0f;
    self->m_v164[1] = 0.0f;
    self->m_v164[2] = 0.0f;

    fn_009f9e20(owner, self);
    animLayoutSyncMat(owner, self);
}

// @ 0x009fa870
void animLayoutResetAll(AnimLayout* owner, AnimLayout* self)
{
    animLayoutResetOne(owner, self);

    AnimHierarchy* h = self->m_hier;
    int idx = h->m_204;
    unsigned n = (unsigned)h->m_20c;
    int off = idx * 0x2bc;
    for (unsigned i = 0; i < n; i++)
    {
        AnimLayout* e = (AnimLayout*)((char*)owner->m_poolBegin + off);
        e->m_quat[0] = g_01551678;
        e->m_quat[1] = g_0155167c;
        e->m_quat[2] = g_01551680;
        e->m_quat[3] = g_01551684;
        e->m_v158[0] = 0.0f;
        e->m_v158[1] = 0.0f;
        e->m_v158[2] = 0.0f;
        e->m_v164[0] = 0.0f;
        e->m_v164[1] = 0.0f;
        e->m_v164[2] = 0.0f;
        fn_009f9e20(owner, e);
        e->m_mat[0] = e->m_src[0];
        e->m_mat[1] = e->m_src[1];
        e->m_mat[2] = e->m_src[2];
        e->m_mat[3] = e->m_src[3];
        e->m_mat[4] = e->m_src[4];
        e->m_mat[5] = e->m_src[5];
        e->m_mat[6] = e->m_src[6];
        off += 0x2bc;
    }
}

// @ 0x009f9e20
void fn_009f9e20(AnimLayout* owner, AnimLayout* self)
{
    AnimHierarchy* h = self->m_hier;
    AnimNodeBlock* nodes = self->m_nodes;

    float A = nodes->m_src[3];
    float F = nodes->m_src[4];
    float E = nodes->m_src[5];
    float Dw = nodes->m_src[6];
    float B = h->m_quat[0];
    float Z = h->m_quat[1];
    float C = h->m_quat[2];
    float W = h->m_quat[3];

    // the original's association: (((B*Dw + A*W) - Z*E) + C*F) and so on; the parentheses keep the
    // /fp:fast reassociator from regrouping the terms (a 1-ulp difference shows up in the equiv test)
    float r1 = ((B * Dw + A * W) - Z * E) + C * F;
    float r2 = ((E * B + Z * Dw) + F * W) - C * A;
    float r3 = ((E * W - F * B) + C * Dw) + Z * A;
    float r4 = ((Dw * W - B * A) - F * Z) - C * E;

    float q0 = self->m_quat[0];
    float q1 = self->m_quat[1];
    float q2 = self->m_quat[2];
    float q3 = self->m_quat[3];

    float o0 = ((q0 * r4 + q3 * r1) - q1 * r3) + q2 * r2;
    float o1 = ((q1 * r4 + q0 * r3) + q3 * r2) - q2 * r1;
    float o2 = (q3 * r3 - q0 * r2) + q2 * r4 + q1 * r1;
    float o3 = (q3 * r4 - q0 * r1) - q1 * r2 - q2 * r3;

    self->m_src[3] = o0;
    self->m_src[4] = o1;
    self->m_src[6] = o3;
    self->m_src[5] = o2;

    float f = owner->m_f70;

    float v1[3];
    v1[0] = h->m_v350[0] * f;
    v1[1] = h->m_v350[1] * f;
    v1[2] = h->m_v350[2] * f;

    float out1[3];
    fn_0099c1a0(out1, nodes->m_src + 3, v1);

    float px = nodes->m_src[0] + out1[0];
    float py = nodes->m_src[1] + out1[1];
    float pz = nodes->m_src[2] + out1[2];
    self->m_f1b4 = py;
    self->m_f1b0 = px;
    self->m_f1b8 = pz;

    float v2[3];
    v2[0] = h->m_v344[0] * f;
    v2[1] = h->m_v344[1] * f;
    v2[2] = h->m_v344[2] * f;

    float out2[3];
    fn_0099c1a0(out2, self->m_src + 3, v2);

    self->m_src[0] = self->m_f1b0 - out2[0];
    self->m_src[1] = self->m_f1b4 - out2[1];
    self->m_src[2] = self->m_f1b8 - out2[2];
    self->m_flag38 = 1;
}

// @ 0x009fa170
void fn_009fa170(AnimLayout* self)
{
    float w = fabsf(self->m_quat[3]);
    float d = w - g_01550b00;
    // The shipped guard compares the epsilon slot (0x13F11C8) against K - |w| (x87 FCOMIP st(2)),
    // i.e. it proceeds only while the real part sits at the target magnitude.
    if (!(d < g_013f11c8))
        return;

    float x = self->m_quat[0];
    float y = self->m_quat[1];
    float z = self->m_quat[2];
    // the original sums x*x, then z*z, then y*y (fld [esp+4] = x, fld [esp+0x14] = z, fld [esp] = y);
    // the numerator is the constant 1 - K*K (K stays on the x87 stack across the guard)
    float s = sqrtf((1.0f - g_01550b00 * g_01550b00) / (x * x + z * z + y * y));

    self->m_quat[0] = x * s;
    self->m_quat[1] = y * s;
    self->m_quat[2] = z * s;
    self->m_quat[3] = g_01550b00;

    // it accumulates (v1*y + v2*z) + v0*x; keep that order against /fp:fast reassociation
    float dot = (self->m_v158[1] * y + self->m_v158[2] * z) + self->m_v158[0] * x;
    if (!(dot > g_01485378))
        return;

    float len2 = (self->m_v158[0] * self->m_v158[0] + self->m_v158[1] * self->m_v158[1])
                 + self->m_v158[2] * self->m_v158[2];
    if (!(len2 > g_013f11c8))
        return;

    // the x87 chain recomputes the length in extended precision (no overflow) and divides *dot* twice:
    // first by the recomputed length, then by sqrt(len2) as stored
    float len = sqrtf(self->m_v158[0] * self->m_v158[0] + self->m_v158[1] * self->m_v158[1]
                      + self->m_v158[2] * self->m_v158[2]);
    float k = 1.0f - (dot / len) / sqrtf(len2);
    self->m_v158[0] = self->m_v158[0] * k;
    self->m_v158[1] = self->m_v158[1] * k;
    self->m_v158[2] = self->m_v158[2] * k;
}

// @ 0x009fa310
// Reconstructed from the disassembly. The helper at 0x009AC7A0 is called as (D, &m0, &m1, 0) and
// returns a pointer to four floats that are copied into self->m_quat; the roles of its arguments
// could not be resolved, so this body is listed as approximate in partial.txt.
void fn_009fa310(AnimLayout* owner, AnimLayout* self)
{
    AnimHierarchy* h = self->m_hier;

    if (h->m_flag370 != 0)
    {
        float f = owner->m_f70;
        AnimNodeBlock* nodes = self->m_nodes;

        float v[3];
        v[0] = h->m_v350[0] * f;
        v[1] = h->m_v350[1] * f;
        v[2] = h->m_v350[2] * f;

        float out1[3];
        fn_0099c1a0(out1, nodes->m_src + 3, v);

        float P[3];
        P[0] = nodes->m_src[0] + out1[0];
        P[1] = nodes->m_src[1] + out1[1];
        P[2] = nodes->m_src[2] + out1[2];

        float out2[3];
        fn_0099c1a0(out2, self->m_src + 3, out1);

        float D[3];
        D[0] = P[0] - (self->m_f1b0 - out2[0]);
        D[1] = P[1] - (self->m_f1b4 - out2[1]);
        D[2] = P[2] - (self->m_f1b8 - out2[2]);

        float A = nodes->m_src[3];
        float F = nodes->m_src[4];
        float E = nodes->m_src[5];
        float Dw = nodes->m_src[6];
        float B = h->m_quat[0];
        float Z = h->m_quat[1];
        float C = h->m_quat[2];
        float W = h->m_quat[3];

        float r1 = B * Dw + A * W - Z * E + C * F;
        float r2 = E * B + Z * Dw + F * W - C * A;
        float r3 = E * W - F * B + C * Dw + Z * A;
        float r4 = Dw * W - B * A - F * Z - C * E;

        float m0 = D[0] + 2.0f * ((r2 * r1 + r4 * r3) * D[1]
                                  + (r3 * r1 - r4 * r2) * D[2]
                                  - (r2 * r2 + r3 * r3) * D[0]);
        float m1 = D[1] + 2.0f * ((r3 * r2 + r4 * r1) * D[2]
                                  - (r1 * r1 + r3 * r3) * D[1]
                                  + (r2 * r1 - r4 * r3) * D[0]);
        float m2 = D[2] + 2.0f * (-(r1 * r1 + r2 * r2) * D[2]
                                  + (r3 * r2 - r4 * r1) * D[1]
                                  + (r3 * r1 + r4 * r2) * D[0]);

        float out3[2];
        out3[0] = m1;
        out3[1] = m2;

        float* q = fn_009ac7a0(D, &m0, out3, 0);
        self->m_quat[0] = q[0];
        self->m_quat[1] = q[1];
        self->m_quat[2] = q[2];
        self->m_quat[3] = q[3];

        if (g_01550afc != 0)
            fn_009fa170(self);
    }
    else
    {
        self->m_quat[0] = g_01551678;
        self->m_quat[1] = g_0155167c;
        self->m_quat[2] = g_01551680;
        self->m_quat[3] = g_01551684;
    }

    self->m_v158[0] = 0.0f;
    self->m_v158[1] = 0.0f;
    self->m_v158[2] = 0.0f;
    self->m_v164[0] = 0.0f;
    self->m_v164[1] = 0.0f;
    self->m_v164[2] = 0.0f;

    fn_009f9e20(owner, self);
    animLayoutSyncMat(owner, self);
}
