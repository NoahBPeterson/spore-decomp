// Slice s009bb910 -- nSPCreatureAnim: finalize the creature's accumulated goals (0x009bb910, 3170 bytes).
//
// Goals are accumulated as weighted sums (goal_pos_rot: position + weight, rotation + weight).
// This function turns each of the four creature-level accumulators into a plain goal:
//   * a position whose weight exceeds 1 is divided by that weight;
//   * a rotation is renormalised and, if its weight is below 1, blended (nlerp, shortest arc)
//     with the identity by the missing weight; with no weight it becomes the identity;
//   * the walk delta goal additionally picks up this frame's requested motion: the position
//     change (requested - previous) and the rotation change (requested * conj(previous)),
//     composed in front of the accumulated rotation;
//   * the weights are reset to 1 (the 0x160 goal keeps a zero weight when it had none).
//
// Layout of the retail creature_instance_data (newer than the 2008 PDB: quaternions instead
// of matrices) comes from the disassembly and slice s009ba4c0; the names of the four
// accumulators (goal_0x118 ...) except walk_goal_delta are Claude-coined.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

namespace checkerlib {
struct vector_3 {
    float x, y, z;
    vector_3& operator=(const vector_3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    vector_3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    vector_3& operator+=(const vector_3& o) { x += o.x; y += o.y; z += o.z; return *this; }
};
struct vector_4 {
    float x, y, z, w;
    vector_4& operator=(const vector_4& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
    vector_4& operator+=(const vector_4& o) { x += o.x; y += o.y; z += o.z; w += o.w; return *this; }
    vector_4& operator-=(const vector_4& o) { x -= o.x; y -= o.y; z -= o.z; w -= o.w; return *this; }
};

vector_4 Normalize(const vector_4& q, float* pLength);    // 0x0099cae0 (out of line here)

inline vector_3 make_v3(float x, float y, float z)
{
    vector_3 r;
    r.x = x; r.y = y; r.z = z;
    return r;
}
inline vector_3 operator-(const vector_3& a, const vector_3& b) { return make_v3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline vector_3 operator*(const vector_3& a, float s) { return make_v3(a.x * s, a.y * s, a.z * s); }
inline vector_3 operator*(float s, const vector_3& a) { return make_v3(s * a.x, s * a.y, s * a.z); }

inline vector_4 make_v4(float x, float y, float z, float w)
{
    vector_4 r;
    r.x = x; r.y = y; r.z = z; r.w = w;
    return r;
}
inline vector_4 operator*(const vector_4& a, float s) { return make_v4(a.x * s, a.y * s, a.z * s, a.w * s); }
inline vector_4 operator+(const vector_4& a, const vector_4& b) { return make_v4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
inline vector_4 operator-(const vector_4& a, const vector_4& b) { return make_v4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
inline float DotProduct(const vector_4& a, const vector_4& b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

// a * conj(b): the rotation from b to a.
inline vector_4 QuaternionProductConjugate(const vector_4& a, const vector_4& b)
{
    vector_4 r;
    r.x = ((a.x * b.w - b.x * a.w) + a.z * b.y) - a.y * b.z;
    r.y = ((a.y * b.w - a.z * b.x) - b.y * a.w) + b.z * a.x;
    r.z = ((a.y * b.x + a.z * b.w) - b.y * a.x) - b.z * a.w;
    r.w = ((b.z * a.z + a.y * b.y) + b.x * a.x) + a.w * b.w;
    return r;
}

// Hamilton product a*b (rotation b, then a).
inline vector_4 QuaternionProduct(const vector_4& a, const vector_4& b)
{
    vector_4 r;
    r.x = ((a.w * b.x + b.w * a.x) - a.z * b.y) + a.y * b.z;
    r.y = ((a.w * b.y + a.z * b.x) + a.y * b.w) - b.z * a.x;
    r.z = ((a.z * b.w - a.y * b.x) + a.w * b.z) + b.y * a.x;
    r.w = ((a.w * b.w - b.x * a.x) - a.y * b.y) - a.z * b.z;
    return r;
}
}  // namespace checkerlib

using namespace checkerlib;

namespace nSPCreatureAnim {

struct goal_pos_rot {                    // size 0x24
    vector_3 pos;          // +0x00
    float    pos_weight;   // +0x0c
    vector_4 rot;          // +0x10
    float    rot_weight;   // +0x20

    // Divides an over-weighted accumulated position by its weight.
    __forceinline void NormalizePos()
    {
        float w = pos_weight;
        if (w > 0.0f && w > 1.0f)
        {
            pos = (1.0f / w) * pos;
        }
    }

    // Renormalises the accumulated rotation; a weight below 1 is filled up with the identity.
    __forceinline void NormalizeWeightedRot()
    {
        float w = rot.w, z = rot.z, y = rot.y, x = rot.x;
        float len = (float)sqrt((double)x * x + (double)y * y + (double)z * z + (double)w * w);
        if (len != 0.0f)
        {
            float inv = 1.0f / len;
            rot.x = x * inv;
            rot.y = y * inv;
            rot.z = z * inv;
            rot.w = w * inv;
        }
        if (1.0f > rot_weight)
        {
            float t = 1.0f - rot_weight;
            vector_4 a = rot * rot_weight;
            vector_4 b = make_v4(0.0f, 0.0f, 0.0f, 1.0f) * t;
            if (0.0f > DotProduct(a, b))
                a = a - b;
            else
                a = a + b;
            rot = Normalize(a, 0);
        }
    }

    __forceinline void SetRotIdentity()
    {
        rot.x = 0.0f;
        rot.y = 0.0f;
        rot.z = 0.0f;
        rot.w = 1.0f;
    }

    __forceinline void NormalizeRot()
    {
        if (rot_weight > 0.0f)
            NormalizeWeightedRot();
        else
            SetRotIdentity();
    }
};

struct creature_instance_data {
    uint32_t     pad_000[0x18 / 4];
    vector_3     requested_pos;           // +0x018
    uint32_t     pad_024[(0x30 - 0x24) / 4];
    vector_3     previous_requested_pos;  // +0x030
    vector_4     requested_rot;           // +0x03c
    uint32_t     pad_04c[(0x5c - 0x4c) / 4];
    vector_4     previous_requested_rot;  // +0x05c
    uint32_t     pad_06c[(0x118 - 0x6c) / 4];
    goal_pos_rot goal_0x118;              // +0x118
    goal_pos_rot goal_0x13c;              // +0x13c
    goal_pos_rot goal_0x160;              // +0x160
    goal_pos_rot walk_goal_delta;         // +0x184
};

// @ 0x009BB910
void __cdecl FinalizeCreatureGoals(creature_instance_data* c)
{
    goal_pos_rot& g160 = c->goal_0x160;
    if (g160.pos_weight > 0.0f)
    {
        g160.NormalizePos();
        g160.pos_weight = 1.0f;
    }

    goal_pos_rot& d = c->walk_goal_delta;
    d.NormalizePos();
    d.pos += c->requested_pos - c->previous_requested_pos;
    d.pos_weight = 1.0f;

    goal_pos_rot& g13c = c->goal_0x13c;
    g13c.NormalizePos();
    g13c.pos_weight = 1.0f;

    if (g160.rot_weight > 0.0f)
    {
        g160.NormalizeWeightedRot();
        g160.rot_weight = 1.0f;
    }
    else
    {
        g160.SetRotIdentity();
    }

    d.NormalizeRot();
    d.rot = QuaternionProduct(QuaternionProductConjugate(c->requested_rot, c->previous_requested_rot), d.rot);
    d.rot_weight = 1.0f;

    g13c.NormalizeRot();
    g13c.rot_weight = 1.0f;

    goal_pos_rot& g118 = c->goal_0x118;
    g118.NormalizePos();
    g118.pos_weight = 1.0f;
    g118.NormalizeRot();
    g118.rot_weight = 1.0f;
}

}  // namespace nSPCreatureAnim
