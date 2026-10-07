// Slice s009f09a0 -- 0x009f09a0 (3324 bytes): IK "rigid follow" of a body's descendants
// (nSPCreatureAnim ik_solver.cpp module; name guessed).
//
// For a body instance (700-byte creature body record) whose ik_goals mode is 1..3:
//   1. accumulate, over the reference bodies (mode 2: the body ik_goals.bidx; modes 1/3: the
//      first `ik_goals.count` descendants whose mode is 0), the weighted unit offsets of the
//      goal positions (sumGoal) and of the current/rest positions (sumCur), the weighted
//      length ratio |goal offset| / |current offset| and the total weight
//      (register-arg helper at VA 009ed370, re-written below as a static helper);
//   2. build R = rotation taking sumCur onto sumGoal (axis = sumCur x sumGoal, cos = dot,
//      sin = |axis|; identity if parallel, half-turn about a perpendicular if opposite) and a
//      stretch matrix  C = t*I + (ratio - t) * sumGoal (x) sumGoal,  M = C * R;
//   3. move every descendant (num_all_children from first_child_bidx): mode-0 descendants of
//      a mode-2 body snap to their goal; others are re-posed around this body's goal by M
//      (or by R plus a stretch along sumGoal when they lie behind), optionally pushed out
//      sideways to their radius by a smoothstep of (1 - ratio); and marked valid.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#pragma intrinsic(sqrt)

struct Vec3 {
    float x, y, z;
    Vec3& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

// checkerlib::matrix_3x3 (row-major, m[row*3 + col])
struct Mat3 {
    float m[9];
    // rotation about a unit axis from (cos, sin); thiscall, ret 0xc
    void SetAxisCosSin(const Vec3& axis, float c, float s);   // 0x009e6cf0
};

extern "C" {
    void  __cdecl PerpPair(const Vec3* dir, Vec3* o1, Vec3* o2);          // 0x009a4a70
    float __cdecl FUN_009b01e0(float lo, float hi, float x);              // 0x009b01e0 smoothstep
}

extern int   g_ikUseRatioScale;   // 0x0166bffc
extern float g_ikRatioScale;      // 0x01550a58
extern float g_ikPushRange;       // 0x01550a08
extern float g_ikHeavyWeight;     // 0x01550a04

struct BodyStatic {
    uint32_t pad000[0x150 / 4];
    uint32_t flags;               // +0x150
    uint32_t pad154[(0x204 - 0x154) / 4];
    uint32_t first_child_bidx;    // +0x204
    uint32_t num_children;        // +0x208
    uint32_t num_all_children;    // +0x20c
};

struct Body {                     // 700 bytes
    BodyStatic* static_data;      // +0x000
    uint8_t  pad004[0x1ac - 4];
    uint8_t  goal_mode;           // +0x1ac (low 3 bits)
    uint8_t  pad1ad[2];
    uint8_t  goal_count;          // +0x1af (bidx for mode 2, count for modes 1/3)
    Vec3     particle;            // +0x1b0
    Vec3     particle_rest;       // +0x1bc
    Vec3     particle_goal;       // +0x1c8
    uint8_t  pad1d4[0x1fc - 0x1d4];
    uint8_t  particle_valid;      // +0x1fc
    uint8_t  push_out;            // +0x1fd
    uint8_t  pad1fe[0x214 - 0x1fe];
    float    radius;              // +0x214
    uint8_t  pad218[700 - 0x218];
};

struct Creature {
    uint8_t  pad000[0x2e4];
    Body*    bodies;              // +0x2e4
};

struct IKCtx {
    Creature* creature;           // +0x00
};

// Original at VA 009ed370 (static helper with a register ABI: eax=other, esi=sumGoal,
// edx=sumCur, edi=weight; stack: self, ratio).
static __declspec(noinline) void AccumulateReference(Body* other, Body* self, float* ratio,
                                                     Vec3* sumGoal, Vec3* sumCur, float* weight)
{
    Vec3 g;
    g.x = other->particle_goal.x - self->particle_goal.x;
    g.y = other->particle_goal.y - self->particle_goal.y;
    g.z = other->particle_goal.z - self->particle_goal.z;
    Vec3 c;
    if (other->particle_valid == 0) {
        c.x = other->particle_rest.x - self->particle_rest.x;
        c.y = other->particle_rest.y - self->particle_rest.y;
        c.z = other->particle_rest.z - self->particle_rest.z;
    } else {
        c.x = other->particle.x - self->particle.x;
        c.y = other->particle.y - self->particle.y;
        c.z = other->particle.z - self->particle.z;
    }
    float invC = 1.0f / (float)(sqrt(c.x * c.x + (c.y * c.y + c.z * c.z)) + 1e-08);
    float lenG = sqrtf(g.x * g.x + (g.z * g.z + g.y * g.y));
    float invG = 1.0f / (float)(lenG + 1e-08);
    float w = (other->static_data->flags & 4) ? g_ikHeavyWeight : 1.0f;
    float k = w * invG;
    sumGoal->x += g.x * k;
    sumGoal->y += g.y * k;
    sumGoal->z += g.z * k;
    k = w * invC;
    sumCur->z = c.z * k + sumCur->z;
    sumCur->x += c.x * k;
    sumCur->y += c.y * k;
    *ratio = (w * lenG) * invC + *ratio;
    *weight += w;
}

// @ 0x009f09a0
void __stdcall IKRigidFollow(IKCtx* ctx, Body* self)
{
    Vec3  sumGoal;                // a
    float weight;
    float ratio;
    Vec3  sumCur;                 // b
    sumGoal.x = 0.0f; sumGoal.y = 0.0f; sumGoal.z = 0.0f;
    sumCur.x = 0.0f;  sumCur.y = 0.0f;  sumCur.z = 0.0f;
    ratio = 0.0f;
    weight = 0.0f;

    switch (self->goal_mode & 7) {
    case 0:
        return;
    case 1:
    case 3: {
        uint32_t n = self->static_data->num_all_children;
        uint32_t start = self->static_data->first_child_bidx;
        uint32_t found = 0;
        for (uint32_t i = 0; i < n; ++i) {
            if (found >= self->goal_count)
                break;
            Body* other = &ctx->creature->bodies[start + i];
            if ((other->goal_mode & 7) == 0) {
                ++found;
                AccumulateReference(other, self, &ratio, &sumGoal, &sumCur, &weight);
            }
        }
        break;
    }
    case 2:
        AccumulateReference(&ctx->creature->bodies[self->goal_count], self, &ratio,
                            &sumGoal, &sumCur, &weight);
        break;
    }

    if (weight != 1.0f) {
        ratio = ratio / weight;
        float inv = 1.0f / (sqrtf(sumGoal.x * sumGoal.x + sumGoal.y * sumGoal.y +
                                  sumGoal.z * sumGoal.z) + 1e-08f);
        sumGoal.x = inv * sumGoal.x;
        sumGoal.y = sumGoal.y * inv;
        sumGoal.z = sumGoal.z * inv;
        inv = 1.0f / (sqrtf(sumCur.x * sumCur.x + sumCur.y * sumCur.y +
                            sumCur.z * sumCur.z) + 1e-08f);
        sumCur.x = inv * sumCur.x;
        sumCur.y = sumCur.y * inv;
        sumCur.z = sumCur.z * inv;
    }

    // R: rotation taking sumCur onto sumGoal
    float c = (sumCur.x * sumGoal.x + sumCur.z * sumGoal.z) + sumCur.y * sumGoal.y;
    Vec3 axis;
    axis.x = sumCur.y * sumGoal.z - sumCur.z * sumGoal.y;
    axis.y = sumCur.z * sumGoal.x - sumGoal.z * sumCur.x;
    axis.z = sumGoal.y * sumCur.x - sumCur.y * sumGoal.x;
    float s = sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
    if (s != 0.0f) {
        float inv = 1.0f / s;
        axis.x = inv * axis.x;
        axis.y = inv * axis.y;
        axis.z = inv * axis.z;
    }
    Mat3 R;
    if (s > 0.0f) {
        float x = axis.x, y = axis.y, z = axis.z;
        float yy = y * y;
        float zz = z * z;
        float xx = x * x;
        R.m[0] = (1.0f - xx) * c + xx;
        float t = 1.0f - c;
        float txy = (t * y) * x;
        float zs = z * s;
        float tz = t * z;
        R.m[1] = txy - zs;
        R.m[3] = zs + txy;
        float tyz = y * tz;
        float ys = y * s;
        float tzx = tz * x;
        R.m[2] = ys + tzx;
        R.m[6] = tzx - ys;
        R.m[4] = (1.0f - yy) * c + yy;
        float xs = s * x;
        R.m[5] = tyz - xs;
        R.m[7] = xs + tyz;
        R.m[8] = (1.0f - zz) * c + zz;
    } else if (c > 0.0f) {
        R.m[0] = 1.0f; R.m[1] = 0.0f; R.m[2] = 0.0f;
        R.m[3] = 0.0f; R.m[4] = 1.0f; R.m[5] = 0.0f;
        R.m[6] = 0.0f; R.m[7] = 0.0f; R.m[8] = 1.0f;
    } else {
        Vec3 perp, other;
        perp.x = 0.0f; perp.y = 0.0f; perp.z = 0.0f;
        PerpPair(&sumCur, &perp, &other);
        R.SetAxisCosSin(perp, -1.0f, 0.0f);
    }

    // stretch: C = t*I + (ratio - t) * a (x) a ;  M = C * R
    float t = g_ikUseRatioScale ? g_ikRatioScale / ratio : 1.0f;
    float k = ratio - t;
    float v[3];
    v[0] = sumGoal.x * k;
    v[1] = sumGoal.y * k;
    v[2] = sumGoal.z * k;
    Mat3 O;
    for (uint32_t i = 0; i < 3; ++i) {
        float vi = v[i];
        O.m[i * 3 + 0] = vi * sumGoal.x;
        O.m[i * 3 + 1] = vi * sumGoal.y;
        O.m[i * 3 + 2] = vi * sumGoal.z;
    }
    Mat3 S;
    {
        float* r = S.m;
        int n = 3;
        do {
            r[0] = 0.0f; r[1] = 0.0f; r[2] = 0.0f;
            r += 3;
        } while (--n != 0);
    }
    S.m[0] = t; S.m[4] = t; S.m[8] = t;
    Mat3 C;
    for (int i = 0; i < 3; ++i) {
        C.m[i]     = S.m[i] + O.m[i];
        C.m[3 + i] = O.m[3 + i] + S.m[3 + i];
        C.m[6 + i] = O.m[6 + i] + S.m[6 + i];
    }
    Mat3 M;
    M.m[0] = (C.m[2] * R.m[6] + C.m[1] * R.m[3]) + C.m[0] * R.m[0];
    M.m[1] = (R.m[1] * C.m[0] + C.m[2] * R.m[7]) + C.m[1] * R.m[4];
    M.m[2] = (R.m[2] * C.m[0] + C.m[2] * R.m[8]) + C.m[1] * R.m[5];
    M.m[3] = (C.m[3] * R.m[0] + C.m[5] * R.m[6]) + C.m[4] * R.m[3];
    M.m[4] = (C.m[5] * R.m[7] + C.m[4] * R.m[4]) + C.m[3] * R.m[1];
    M.m[5] = (C.m[5] * R.m[8] + C.m[4] * R.m[5]) + C.m[3] * R.m[2];
    M.m[6] = (C.m[6] * R.m[0] + C.m[7] * R.m[3]) + C.m[8] * R.m[6];
    M.m[7] = (C.m[7] * R.m[4] + C.m[8] * R.m[7]) + C.m[6] * R.m[1];
    M.m[8] = (C.m[7] * R.m[5] + C.m[8] * R.m[8]) + C.m[6] * R.m[2];

    uint32_t n = self->static_data->num_all_children;
    uint32_t start = self->static_data->first_child_bidx;
    for (uint32_t i = 0; i < n; ++i) {
        Body* o = &ctx->creature->bodies[start + i];
        uint32_t mode = o->goal_mode & 7;
        if (mode == 0) {
            if ((uint8_t)(self->goal_mode & 7) == 2) {
                o->particle = o->particle_goal;
                o->particle_valid = 1;
                continue;
            }
        } else if (!(mode > 0 && mode <= 3)) {
            continue;
        }

        Vec3 d;
        if (o->particle_valid == 0) {
            d.x = o->particle_rest.x - self->particle_rest.x;
            d.y = o->particle_rest.y - self->particle_rest.y;
            d.z = o->particle_rest.z - self->particle_rest.z;
        } else {
            d.x = o->particle.x - self->particle.x;
            d.y = o->particle.y - self->particle.y;
            d.z = o->particle.z - self->particle.z;
        }

        float px, py, pz;
        if ((d.x * sumCur.x + d.z * sumCur.z) + d.y * sumCur.y < 0.0f) {
            float rx = (d.z * R.m[2] + d.y * R.m[1]) + d.x * R.m[0];
            float ry = (R.m[3] * d.x + d.z * R.m[5]) + d.y * R.m[4];
            float rz = (R.m[6] * d.x + d.z * R.m[8]) + d.y * R.m[7];
            if (ratio <= 1.0f) {
                o->particle.x = rx + self->particle_goal.x;
                o->particle.y = self->particle_goal.y + ry;
                o->particle.z = self->particle_goal.z + rz;
                o->particle_valid = 1;
                continue;
            }
            float f = (ratio > 2.0f) ? 1.0f : ratio - 1.0f;
            float proj = ((rx * sumGoal.x + rz * sumGoal.z) + ry * sumGoal.y) * f;
            px = (self->particle_goal.x + rx) - sumGoal.x * proj;
            py = (self->particle_goal.y + ry) - sumGoal.y * proj;
            pz = (self->particle_goal.z + rz) - sumGoal.z * proj;
        } else {
            float rx = (d.x * M.m[0] + d.z * M.m[2]) + d.y * M.m[1];
            float ry = (M.m[3] * d.x + d.z * M.m[5]) + d.y * M.m[4];
            float rz = (M.m[6] * d.x + d.z * M.m[8]) + d.y * M.m[7];
            o->particle.x = rx + self->particle_goal.x;
            o->particle.y = self->particle_goal.y + ry;
            o->particle.z = self->particle_goal.z + rz;
            if (o->push_out == 0 || !(ratio < 1.0f)) {
                o->particle_valid = 1;
                continue;
            }
            float proj = (rx * sumGoal.x + rz * sumGoal.z) + ry * sumGoal.y;
            rx = rx - sumGoal.x * proj;
            ry = ry - sumGoal.y * proj;
            rz = rz - sumGoal.z * proj;
            float inv = 1.0f / (sqrtf(rx * rx + ry * ry + rz * rz) + 1e-08f);
            float rad = o->radius;
            Vec3 push;
            push.x = (rx * inv) * rad;
            push.y = (ry * inv) * rad;
            push.z = (rz * inv) * rad;
            float w = FUN_009b01e0(0.0f, g_ikPushRange, 1.0f - ratio);
            px = push.x * w + o->particle.x;
            py = push.y * w + o->particle.y;
            pz = push.z * w + o->particle.z;
        }
        o->particle.z = pz;
        o->particle.y = py;
        o->particle.x = px;
        o->particle_valid = 1;
    }
}
