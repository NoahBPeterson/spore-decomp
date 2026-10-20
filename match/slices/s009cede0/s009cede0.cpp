// slice s009cede0 -- nSPCreatureAnim gait_dynamics (retail /O2 build of the dev module
// SPCreatureAnim/gait_dynamics.obj).  Members of nSPCreatureAnim::dynamics_foot.
//
//   @ 0x009cede0  dynamics_foot::SampleBlendPos          (curve lerp, sret)
//   @ 0x009ceec0  dynamics_foot::SampleBlendRot          (quaternion blend, sret)
//   @ 0x009cf080  dynamics_foot::SetBendAngle
//   @ 0x009cf240  dynamics_foot::AdvancePhase
//   @ 0x009cf3c0  dynamics_foot::UpdateStance
//   @ 0x009cf740  dynamics_foot::CalcBendBlendFactor
//   @ 0x009cf7d0  dynamics_foot::GetDeltaCoordinate
//   @ 0x009cfa90  dynamics_foot::CalcDeltaRootPosition
//   @ 0x009cfb00  foot_pair::BlendFeet
//
// Field offsets are the retail ones read from the disassembly (the dev PDB predates this build).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned char uint8;
typedef unsigned int  uint32;

namespace checkerlib {
struct vector_3 { float x, y, z, w; };   // 16 bytes in this build: passed by value as four dwords
struct vector_4 { float x, y, z, w; };
}
using checkerlib::vector_3;
using checkerlib::vector_4;

namespace nSPCreatureAnim {

struct creature_body_static_data;
struct creature_body_instance_data;
struct creature_instance_data;

// ------------------------------------------------------------------ external code (resolved by
// tools/difftest/resolve.py from the hex in the name / the '// 0x...' annotation)

struct dynamics_foot;

struct curve_sample_a {                       // the object the [0x64]/[0x68] fields hold
    void* Sample(void* out, float t);         // 0x009dcc50  ret 8   (called at +4)
};
struct curve_sample_b {
    void* Sample(void* out, float t);         // 0x009dd0c0  ret 8   (called at +0x18)
};

// output block of a curve Sample(): the 3-vector lives at +8
struct curve_out { float w; float u; vector_3 v; };

void  FUN_0099cc70(float* out, const float* a, const float* b, float w);   // 0x0099cc70 cdecl
void  FUN_009cda70(float* out, const float* m);                            // 0x009cda70 cdecl
float nSPCreatureAnim_biasedSigmoid(float, float, float, float, float, float);  // 0x009cdce0 cdecl

// ------------------------------------------------------------------ data structures

struct creature_body_static_data {            // retail size 0x468
    char  pad_000[0x10c];
    float rest_cx, rest_cy, rest_cz;          // 0x10c
    float q_118, q_11c, q_120, q_124;         // 0x118 (quaternion, component order per the retail formulas)
    char  pad_128[0x154 - 0x128];
    uint8 flags_154;                          // 0x154
    char  pad_155[0x1f8 - 0x155];
    int   bidx;                               // 0x1f8
    char  pad_1fc[0x430 - 0x1fc];
    int   anim_group;                         // 0x430
    float f_434;                              // 0x434
    float f_438;                              // 0x438
    float f_43c;                              // 0x43c
    char  pad_440[0x468 - 0x440];
};

struct creature_body_instance_data {          // retail size 0x2bc
    char  pad_000[0x7c];
    float rest_x, rest_y, rest_z;             // 0x7c
    char  pad_088[0x2bc - 0x88];
};

struct creature_static_data {                 // partial; only the pieces this slice touches
    char  pad_000[0x384];
    creature_body_static_data* bodies_begin;  // 0x384
    float leg_len_a(float w, int bidx, int grp);   // 0x009b5080 ret 0xc
    float leg_len_b(float w, int bidx, int grp);   // 0x009b51c0 ret 0xc
    float leg_len_c(float w, int bidx, int grp);   // 0x009b5100 ret 0xc
    float leg_len_d(float w, int bidx, int grp);   // 0x009b5180 ret 0xc
};

struct creature_instance_data {
    creature_static_data* static_data;        // 0x000
    char  pad_004[0x2e4 - 4];
    creature_body_instance_data* bodies;      // 0x2e4
    char  pad_2e8[0x15b8 - 0x2e8];
    int   f_15b8;                             // 0x15b8
    int   f_15bc;                             // 0x15bc
};

// the struct pointer passed to SetBendAngle
struct gait_src {
    char  pad_000[0x68];
    float f_68;                               // 0x68
    float f_6c;                               // 0x6c
    float f_70;                               // 0x70
    float f_74;                               // 0x74
    float f_78;                               // 0x78
    char  pad_07c[0xdc - 0x7c];
    float f_dc;                               // 0xdc
};

struct dynamics_foot {
    float pos[3];                             // 0x000
    float prev_pos[3];                        // 0x00c
    float unk_18[3];                          // 0x018
    float orient[4];                          // 0x024
    float prev_orient[4];                     // 0x034
    float f_44;                               // 0x044
    float f_48;                               // 0x048
    float f_4c;                               // 0x04c
    float f_50;                               // 0x050
    float f_54;                               // 0x054
    int   index;                              // 0x058
    char  pad_05c;
    uint8 flag_5d;                            // 0x05d
    char  pad_05e[2];
    float ratio;                              // 0x060
    curve_sample_a* curve_64;                 // 0x064
    curve_sample_b* curve_68;                 // 0x068
    float f_6c;                               // 0x06c
    float f_70;                               // 0x070
    float f_74;                               // 0x074
    float phase;                              // 0x078
    float rest_angle[3];                      // 0x07c
    float orient2[4];                         // 0x088
    float phase_offset;                       // 0x098
    char  pad_09c[0x0c];
    float f_a8;                               // 0x0a8
    float f_ac;                               // 0x0ac
    int   motion;                             // 0x0b0
    char  pad_0b4[0x0c];
    float f_c0;                               // 0x0c0
    int   f_c4;                               // 0x0c4
    creature_instance_data* creature;         // 0x0c8
    char  pad_0cc[8];
    float turn;                               // 0x0d4
    char  pad_0d8[0x28];
    float phl;                                // 0x100
    float phu;                                // 0x104

    vector_3* SampleBlendPos(vector_3* out, float t);
    vector_3* SampleBlendRot(vector_3* out, float t);
    void      SetBendAngle(gait_src* p, float a, float b);
    void      AdvancePhase(float dt);
    void      UpdateStance();
    float     CalcBendBlendFactor(void* creature, float t);
    float     GetDeltaCoordinate(int idx, void* pRoot, vector_3 v);
    vector_3* CalcDeltaRootPosition(vector_3* out, void* pRoot, vector_3 v);
    float     FUN_009cdfb0(float x);          // 0x009cdfb0  ret 4  (ecx = this)
    float     FUN_009ce100(bool b);           // 0x009ce100  ret 4  (ecx = this)
};

// the object 0x009cfb00 is a method of
struct body_ref { creature_body_static_data* body; };
struct foot_pair {
    char        pad_00[4];
    body_ref*   ref;                          // 0x004
    char        pad_08[0x24 - 8];
    float       f_24;                         // 0x024
    float       f_28;                         // 0x028
    float       f_2c;                         // 0x02c
    void BlendFeet(float* outPos, float* outQuat, dynamics_foot* footA, dynamics_foot* footB,
                   float w, float w2, float* inQuat);
};

float GetAnimationBlend(void* body);          // 0x009b33f0 cdecl (1 arg)

extern float DAT_01447a18;                    // 0x01447a18  (1/PI)
extern float DAT_0155125c;                    // 0x0155125c
extern int   DAT_015515dc;                    // 0x015515dc
extern float DAT_0155147c;                    // 0x0155147c
extern float DAT_01551478;                    // 0x01551478
extern float DAT_01551470;                    // 0x01551470
extern float DAT_01551480;                    // 0x01551480
extern float DAT_01551484;                    // 0x01551484
extern float DAT_01551488;                    // 0x01551488
extern float DAT_0155148c;                    // 0x0155148c
extern float DAT_01551490;                    // 0x01551490
extern float DAT_01551494;                    // 0x01551494
extern float DAT_01551498;                    // 0x01551498
extern float DAT_0155149c;                    // 0x0155149c
extern float DAT_01550a10;                    // 0x01550a10
extern float DAT_0166c67c;                    // 0x0166c67c
extern float DAT_0166c7d0;                    // 0x0166c7d0
extern uint8 DAT_01551254;                    // 0x01551254
extern uint8 DAT_01551255;                    // 0x01551255
extern uint8 DAT_01551256;                    // 0x01551256

static inline float clampf(float v, float lo, float hi)
{
    return v < lo ? lo : (v > hi ? hi : v);
}

// ------------------------------------------------------------------ @ 0x009cede0

// @ 0x009cede0
vector_3* dynamics_foot::SampleBlendPos(vector_3* out, float t)
{
    float f = ratio;
    float g = 1.0f - f;

    float a[0x11];
    float b[0x11];
    ((curve_sample_a*)((char*)curve_68 + 4))->Sample(a, t);
    float ax = a[2] * f, ay = a[3] * f, az = a[4] * f;
    ((curve_sample_a*)((char*)curve_64 + 4))->Sample(b, t);

    out->x = b[2] * g + ax;
    out->y = b[3] * g + ay;
    out->z = b[4] * g + az;
    return out;
}

// ------------------------------------------------------------------ @ 0x009ceec0

// @ 0x009ceec0
vector_3* dynamics_foot::SampleBlendRot(vector_3* out, float t)
{
    float f = ratio;

    float a[0x16];
    float b[0x16];
    curve_sample_b* ca = (curve_sample_b*)((char*)curve_68 + 0x18);
    curve_sample_b* cb = (curve_sample_b*)((char*)curve_64 + 0x18);
    ca->Sample(a, t);
    cb->Sample(b, t);

    float q[9];
    FUN_0099cc70(q, b + 2, a + 2, f);

    float e4 = q[0], e0 = q[1], dc = q[2], d8 = q[3];
    float m[9];
    m[0] = 1.0f - (dc * dc + e0 * e0) * 2.0f;
    m[1] = (e4 * e0 - d8 * dc) * 2.0f;
    m[2] = (d8 * e0 + dc * e4) * 2.0f;
    m[3] = (d8 * dc + e4 * e0) * 2.0f;
    m[4] = 1.0f - (dc * dc + e4 * e4) * 2.0f;
    m[5] = (dc * e0 - d8 * e4) * 2.0f;
    m[6] = (dc * e4 - d8 * e0) * 2.0f;
    m[7] = (d8 * e4 + dc * e0) * 2.0f;
    m[8] = 1.0f - (e0 * e0 + e4 * e4) * 2.0f;

    FUN_009cda70((float*)out, m);
    return out;
}

// ------------------------------------------------------------------ @ 0x009cf080

// @ 0x009cf080
void dynamics_foot::SetBendAngle(gait_src* p, float a, float b)
{
    float v;

    if (DAT_015515dc != 0 && curve_64 != 0 && curve_68 != 0) {
        double tv = (double)(phase_offset - phase * 0.5f);
        float frac = (float)(tv - floor(tv));
        float r = FUN_009cdfb0(frac * DAT_0155125c);
        v = r * p->f_dc + (1.0f - p->f_dc) * 0.5f;
    } else {
        float f4 = 0.5f - (p->f_dc * p->f_70) * p->f_68;
        f4 = clampf(f4, 0.0f, 1.0f);

        float f1 = p->f_6c;
        float f5 = p->f_74 * f1;
        float f3 = (1.0f - f1) * p->f_78 + f1;
        float f6 = 0.0f;
        if (f5 < a && a < f3) {
            float t = 0.0f;
            if (f1 <= a) {
                if (1e-6f < f3 - f1)
                    t = (f3 - a) / (f3 - f1);
            } else {
                if (1e-6f < f1 - f5)
                    t = (a - f5) / (f1 - f5);
            }
            float s = (float)sin((double)(t * (float)1.5707964));
            f6 = s * s;
        }
        float h = fabsf(b) * 0.31830987f + 0.5f;
        v = (1.0f - f6) * h + f6 * f4;
    }

    if (fabsf(v) < 1e-6f)
        v = 0.0f;
    f_44 = 123239.71875f;                     // bits 0x47f0b3dc: stored as an immediate by the original
    f_48 = 0.0f;
    f_4c = v;
    f_54 = 1.0f;
}

// ------------------------------------------------------------------ @ 0x009cf240

// @ 0x009cf240
void dynamics_foot::AdvancePhase(float dt)
{
    double tv = (double)(f_6c + dt);
    float frac = (float)((f_6c + dt) - floor(tv));

    bool bUp = phl > frac;
    bool bDown = frac >= phu;
    bool wrap = bUp || bDown;

    if (wrap) {
        int st = creature->f_15b8;
        if (st == 0 || st == 2)
            return;
        motion = 3;
        return;
    }

    if (creature == 0)
        return;

    if (creature->f_15bc != creature->f_15b8 && creature->f_15bc == 0) {
        float r = FUN_009ce100(false);
        float v = (frac - phl) / r;
        float c = clampf(v, 0.0f, 1.0f);
        motion = (c > DAT_0155147c) ? 0 : 3;
    }

    int st = creature->f_15b8;
    if (st != 0 && st != 2)
        return;

    float dx = pos[0] - rest_angle[0];
    float dy = pos[1] - rest_angle[1];
    float dxy = (float)sqrt((double)(dx * dx + dy * dy));
    if (dxy < f_ac * DAT_01551478 && fabsf(pos[2] - rest_angle[2]) < 1e-6f) {
        motion = 0;
        return;
    }
    motion = 3;
}

// ------------------------------------------------------------------ @ 0x009cf3c0

// @ 0x009cf3c0
void dynamics_foot::UpdateStance()
{
    creature_body_static_data* body =
        *(creature_body_static_data**)((char*)creature->bodies + index * 0x2bc);

    float ca = 1.0f;
    if (DAT_01551254 != 0 && body->f_434 > 1e-6f) {
        ca = (body->f_43c / body->f_434) * (DAT_0155148c - DAT_01551488) + DAT_01551488;
        ca = clampf(ca, 0.0f, 1.5f);
    }

    float cb = 1.0f;
    if (DAT_01551255 != 0 && body->f_434 > 1e-6f) {
        float r = body->f_438 / body->f_434;
        if (r > DAT_01551484)
            cb = ((r - DAT_01551484) / (1.0f - DAT_01551484)) * DAT_01550a10 + 1.0f;
    }

    if (DAT_01551256 != 0 && body->f_434 > 1e-6f) {
        float inv = 1.0f / body->f_434;
        float p8 = body->f_43c * inv;
        float p10 = (body->f_438 * inv - 0.75f) * 4.0f;
        p10 = clampf(p10, 0.0f, 1.0f);
        float pw = (float)pow((double)(1.0f - p8), *(double*)&DAT_0166c7d0);
        p8 = clampf(pw, 0.0f, 1.0f);
        f_c0 = (p10 <= p8) ? p10 : p8;
    }

    creature_static_data* sd = creature->static_data;

    float t1 = sd->leg_len_a(1.0f - f_c0, body->bidx, body->anim_group);
    float t2 = sd->leg_len_b(1.0f - f_c0, body->bidx, body->anim_group);

    float d = body->f_434 * body->f_434 - t1;
    float half2 = (float)(0.25 * sqrt((double)t2));
    float val = ((float)sqrt((double)(d > 0.0f ? d : 0.0f)) - (float)sqrt((double)t2)) * cb * ca;
    val = val + val;
    f_ac = (val <= half2) ? half2 : val;

    float p10b = f_c0 * DAT_01551480 + 1.0f;
    float u1 = sd->leg_len_c(1.0f - f_c0, body->bidx, body->anim_group);
    float u2 = sd->leg_len_d(1.0f - f_c0, body->bidx, body->anim_group);

    float half4 = (float)(sqrt((double)u2) * 0.25);
    float d2 = body->f_434 * body->f_434 - u1;
    float val2 = ((float)sqrt((double)d2) - (float)sqrt((double)u2)) * p10b * cb * ca;
    val2 = val2 + val2;
    f_a8 = (val2 <= half4) ? half4 : val2;
}

// ------------------------------------------------------------------ @ 0x009cf740

// @ 0x009cf740
float dynamics_foot::CalcBendBlendFactor(void* pRoot, float t)
{
    creature_static_data* sd = creature->static_data;
    creature_body_static_data* bd =
        (creature_body_static_data*)((char*)sd->bodies_begin + index * 0x468);

    float blend = GetAnimationBlend(bd);

    float fv;
    if ((bd->flags_154 & 8) != 0)
        fv = rest_angle[2];
    else
        fv = ((creature_body_static_data*)((char*)sd->bodies_begin +
                                           bd->anim_group * 0x468))->rest_cz;

    float ratio = (t * 0.2f) / (0.7f + t * 0.2f);
    return ((ratio * (fv + blend)) * *(float*)((char*)pRoot + 0x60)) * 0.5f;
}

// ------------------------------------------------------------------ @ 0x009cf7d0

// @ 0x009cf7d0
float dynamics_foot::GetDeltaCoordinate(int idx, void* pRoot, vector_3 v)
{
    float f = (&v.x)[idx] + phase_offset;
    float frac = f - (float)floor((double)f);

    bool bUp = phl > frac;
    bool bDown = frac >= phu;
    bool wrap = bUp || bDown;

    float num, den;
    if (bUp) {
        num = (1.0f - phu) + frac;
        den = (1.0f - phu) + phl;
    } else if (bDown) {
        num = frac - phu;
        den = (1.0f - phu) + phl;
    } else {
        num = frac - phl;
        den = phu - phl;
    }

    float r = clampf(num / den, 0.0f, 1.0f);

    if (idx == 0) {
        float s = (float)sin((double)(r * 3.1415927f)) * rest_angle[0];
        return wrap ? -s : s;
    }
    if (idx == 1) {
        if (!wrap)
            return (float)cos((double)(r * 3.1415927f)) * turn;
        return ((r - 0.5f) * turn) * 2.0f;
    }
    if (idx == 2) {
        float u = (1.0f - phase) * 0.63661975f;
        float c1 = -(DAT_0155149c * u);
        float c2 = (1.0f - u) * DAT_0155149c;
        float pp = (frac >= 0.5f) ? (1.0f - frac) : frac;
        if (DAT_015515dc != 0 && curve_64 != 0 && curve_68 != 0)
            return nSPCreatureAnim_biasedSigmoid(pp, DAT_0166c67c, DAT_01551494, c1, c2,
                                                 1.0f - DAT_01551498 * v.w);
        float l2 = (float)(log((double)(phase * 0.5f)) / 0.6931471805599453);
        float b = nSPCreatureAnim_biasedSigmoid(
            pp, DAT_0166c67c, DAT_01551494, c1, c2,
            (float)((double)DAT_0166c7d0 / (0.6931471805599453 * (double)l2)));
        double x = (double)b * DAT_01551470;
        double y = log(sqrt(x * x + 1.0) + x);
        return (float)((y / (double)DAT_01551470) * (double)DAT_01551490);
    }
    return 0.0f;
}

// ------------------------------------------------------------------ @ 0x009cfa90

// @ 0x009cfa90
vector_3* dynamics_foot::CalcDeltaRootPosition(vector_3* out, void* pRoot, vector_3 v)
{
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = 0.0f;
    for (int i = 0; i < 3; ++i)
        (&out->x)[i] += GetDeltaCoordinate(i, pRoot, v);
    return out;
}

// ------------------------------------------------------------------ @ 0x009cfb00

// @ 0x009cfb00
void foot_pair::BlendFeet(float* outPos, float* outQuat, dynamics_foot* footA, dynamics_foot* footB,
                          float w, float w2, float* inQuat)
{
    creature_body_instance_data* ba =
        (creature_body_instance_data*)((char*)footA->creature->bodies + footA->index * 0x2bc);
    float f2 = f_24;
    float f3 = ba->rest_y;
    float f10 = 1.0f - f_24;
    creature_body_instance_data* bb =
        (creature_body_instance_data*)((char*)footB->creature->bodies + footB->index * 0x2bc);
    float f4 = bb->rest_y;
    float f5 = bb->rest_z;
    float f12 = ba->rest_z;

    outPos[0] = ba->rest_x * f10 + bb->rest_x * f2;
    outPos[1] = f3 * f10 + f4 * f2;
    outPos[2] = f12 * f10 + f5 * f2;

    creature_body_static_data* bd = ref->body;
    outPos[2] = (f_28 * f_28) * w + bd->rest_cz;

    float qx = bd->q_118;
    float qy = bd->q_11c;
    float qw = bd->q_120;
    float qz = bd->q_124;

    float ang = (float)atan2(((f_2c / w2) * f_28 * w) * 6.2831855f, 1.0f);
    float s = (float)sin((double)(ang * 0.5f));
    float c = (float)cos((double)(ang * 0.5f));

    float i0 = inQuat[0] * s;
    float i1 = inQuat[1] * s;
    float i2 = inQuat[2] * s;

    outQuat[0] = ((qx * c + qz * i0) - qy * i2) + qw * i1;
    outQuat[1] = ((qy * c + qx * i2) + qz * i1) - qw * i0;
    outQuat[2] = ((qz * i2 - qx * i1) + qw * c) + qy * i0;
    outQuat[3] = ((qz * c - qx * i0) - qy * i1) - qw * i2;
}

}  // namespace nSPCreatureAnim
