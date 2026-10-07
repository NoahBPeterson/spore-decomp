// Slice s009bfc20 -- nSPCreatureAnim: ground a body's goal (0x009bfc20, 2652 bytes).
//
// creature_body_instance_data::GroundGoal(vector_3* outPos, vector_4* outRot,
//                                         creature_instance_data* c, float baseHeight,
//                                         float rate, bool storeGround)        (thiscall, ret 0x18)
//
// Takes the body's second accumulated goal (goal_b: the weighted position, else the rest
// center scaled by the creature scale; the normalised weighted rotation, else the rest
// orientation), brings it into world space, asks the creature for the ground height and
// normal under it, and moves the position along the creature's up vector by
// (height - baseHeight) * rate. When the body sits lower than 1.3x its extent, the rotation is
// tilted towards the ground normal (shortest-arc rotation up -> normal), faded out by a
// smoothstep of the height over [0, 1.3*extent] (nlerp with the identity, shortest arc).
// With storeGround the ground point under the body (offset along the normal by the body's
// rest height) and the ground normal are stored in creature space in the body
// (ground_pos / ground_normal, known_ground_pos = true). The result is returned in
// creature space (inverse-rotated by the creature orientation).
//
// Layouts: retail offsets from the disassembly; names follow s009ba4c0 / the dev PDB
// (ground_pos, ground_normal, known_ground_pos are PDB names shifted to retail offsets).
// goal_b, extent, ground_up and the function name GroundGoal are Claude-coined.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

namespace checkerlib {
struct vector_3 {
    float x, y, z;
    vector_3() {}
    vector_3(const vector_3& o) : x(o.x), y(o.y), z(o.z) {}
    vector_3& operator=(const vector_3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct vector_4 { float x, y, z, w; };

vector_3* QuaternionVectorTransform(vector_3* out, const vector_4* q, const vector_3* v);         // 0x0099c1a0
vector_3* QuaternionVectorTransformInverse(vector_3* out, const vector_4* q, const vector_3* v);  // 0x0099c310
vector_4* Normalize(vector_4* out, const vector_4* q, float* pLength);                            // 0x0099cae0
}  // namespace checkerlib

using namespace checkerlib;

vector_4* QuaternionFromTwoVectors(vector_4* out, const vector_3* a, const vector_3* b, int flag);  // 0x009ac7a0
float __cdecl SmoothStep(float lo, float hi, float x);                                             // 0x009b01e0


// a * b (Hamilton), in the binary's term order.
static __forceinline vector_4 QuatMul(const vector_4& a, const vector_4& b)
{
    vector_4 r;
    r.x = ((b.w * a.x + b.x * a.w) - b.y * a.z) + b.z * a.y;
    r.y = ((b.w * a.y + b.y * a.w) + b.x * a.z) - b.z * a.x;
    r.z = ((b.w * a.z - b.x * a.y) + b.y * a.x) + b.z * a.w;
    r.w = ((b.w * a.w - b.x * a.x) - b.y * a.y) - b.z * a.z;
    return r;
}

// conj(a) * b
static __forceinline vector_4 QuatConjMul(const vector_4& a, const vector_4& b)
{
    vector_4 r;
    r.x = ((a.w * b.x - a.x * b.w) + a.z * b.y) - a.y * b.z;
    r.y = ((a.w * b.y - a.y * b.w) - a.z * b.x) + a.x * b.z;
    r.z = ((a.y * b.x - a.z * b.w) - a.x * b.y) + a.w * b.z;
    r.w = ((a.x * b.x + a.y * b.y) + a.z * b.z) + a.w * b.w;
    return r;
}

// Rotates v by the inverse of the unit quaternion q (inlined).
static __forceinline vector_3 InvRotate(const vector_4& q, const vector_3& v)
{
    float nxw = -(q.x * q.w);
    float nzw = -(q.z * q.w);
    float nxx = -(q.x * q.x);
    float nyw = -(q.y * q.w);
    float zx = q.z * q.x;
    float yx = q.y * q.x;
    float nyy = -(q.y * q.y);
    float zy = q.z * q.y;
    float nzz = -(q.z * q.z);
    vector_3 r;
    r.x = (((yx - nzw) * v.y + (zx + nyw) * v.z) + (nzz + nyy) * v.x) * 2.0f + v.x;
    r.y = (((nzz + nxx) * v.y + (zy - nxw) * v.z) + (yx + nzw) * v.x) * 2.0f + v.y;
    r.z = (((nyy + nxx) * v.z + (zy + nxw) * v.y) + (zx - nyw) * v.x) * 2.0f + v.z;
    return r;
}

namespace nSPCreatureAnim {

struct goal_pos_rot {                    // size 0x24
    vector_3 pos;          // +0x00
    float    pos_weight;   // +0x0c
    vector_4 rot;          // +0x10
    float    rot_weight;   // +0x20
};

struct creature_body_static_data {
    uint32_t pad_000[0x10c / 4];
    vector_3 rest_center__SCALABLE;      // +0x10c
    vector_4 rest_orientation_q;         // +0x118
    uint32_t pad_128[(0x138 - 0x128) / 4];
    vector_3 extent;                     // +0x138 (half size, unscaled)
};

struct creature_instance_data {
    uint32_t pad_000[0x18 / 4];
    vector_3 position;                   // +0x018
    uint32_t pad_024[(0x3c - 0x24) / 4];
    vector_4 orientation;                // +0x03c
    uint32_t pad_04c[(0x70 - 0x4c) / 4];
    float    requested_scale;            // +0x070
    uint32_t pad_074[(0x100 - 0x74) / 4];
    vector_3 ground_up;                  // +0x100

    float GetGroundHeight(const vector_3* pos, vector_3* normal);   // 0x009b6220
    vector_3* GetGroundUp(vector_3* out, const vector_3* pos);      // 0x009b62c0
};

struct creature_body_instance_data {
    creature_body_static_data* static_data;  // +0x000
    uint32_t pad_004[(0x7c - 0x4) / 4];
    goal_pos_rot goal_b;                     // +0x07c
    uint32_t pad_0a0[(0x2a0 - 0xa0) / 4];
    bool     known_ground_pos;               // +0x2a0
    uint8_t  pad_2a1[3];
    vector_3 ground_pos;                     // +0x2a4
    vector_3 ground_normal;                  // +0x2b0

    void GroundGoal(vector_3* outPos, vector_4* outRot, creature_instance_data* c,
                    float baseHeight, float rate, bool storeGround);
};

// @ 0x009bfc20
void creature_body_instance_data::GroundGoal(vector_3* outPos, vector_4* outRot,
                                             creature_instance_data* c, float baseHeight,
                                             float rate, bool storeGround)
{
    // goal position in creature space
    vector_3 lpos;
    float s;
    if (goal_b.pos_weight > 0.0f) {
        s = 1.0f / goal_b.pos_weight;
        lpos.x = goal_b.pos.x * s;
        lpos.y = goal_b.pos.y * s;
        lpos.z = goal_b.pos.z * s;
    } else {
        const vector_3& rc = static_data->rest_center__SCALABLE;
        s = c->requested_scale;
        lpos.x = rc.x * s;
        lpos.y = rc.y * s;
        lpos.z = rc.z * s;
    }
    vector_3 local;
    local = lpos;

    // world position
    vector_3 wpos;
    {
        vector_3 tmp;
        vector_3* r = QuaternionVectorTransform(&tmp, &c->orientation, &local);
        wpos.x = c->position.x + r->x;
        wpos.y = r->y + c->position.y;
        wpos.z = r->z + c->position.z;
    }

    // world rotation
    vector_4 tmpA, tmpB;
    const vector_4* nrot;
    if (goal_b.rot_weight > 0.0f)
        nrot = Normalize(&tmpA, &goal_b.rot, 0);
    else
        nrot = Normalize(&tmpB, &static_data->rest_orientation_q, 0);
    vector_4 wrot = QuatMul(c->orientation, *nrot);

    vector_3 normal;
    normal.x = 0.0f;
    normal.y = 0.0f;
    normal.z = 0.0f;
    float height = c->GetGroundHeight(&wpos, &normal);
    float d = (height - baseHeight) * rate;

    vector_3 gpos;
    gpos.x = c->ground_up.x * d + wpos.x;
    gpos.y = c->ground_up.y * d + wpos.y;
    gpos.z = c->ground_up.z * d + wpos.z;

    const vector_3& ext = static_data->extent;
    float ex = ext.x * c->requested_scale;
    float ey = ext.y * c->requested_scale;
    float ez = ext.z * c->requested_scale;
    float size = sqrtf(ex * ex + ey * ey + ez * ez) * 1.3f;

    vector_4 grot;
    if (size > local.z) {
        float f = 1.0f - SmoothStep(0.0f, size, local.z);
        vector_4 tilt;
        QuaternionFromTwoVectors(&tilt, &c->ground_up, &normal, 0);
        if (f < 1.0f) {
            tilt.x *= f;
            tilt.y *= f;
            tilt.z *= f;
            tilt.w *= f;
            float g = 1.0f - f;
            if (tilt.w > 0.0f)
                tilt.w = g + tilt.w;
            else
                tilt.w = tilt.w - g;
            vector_4 tmp;
            grot = QuatMul(*Normalize(&tmp, &tilt, 0), wrot);
        } else {
            grot = QuatMul(tilt, wrot);
        }
    } else {
        grot = wrot;
    }

    if (storeGround) {
        vector_3 up;
        c->GetGroundUp(&up, &wpos);
        float dot = (up.x * wpos.x + up.z * wpos.z) + up.y * wpos.y;
        float r = static_data->rest_center__SCALABLE.z * c->requested_scale;
        vector_3 gp;
        gp.x = (((wpos.x - up.x * dot) + up.x * height) + normal.x * r) - c->position.x;
        gp.y = (((wpos.y - up.y * dot) + up.y * height) + normal.y * r) - c->position.y;
        gp.z = (((wpos.z - up.z * dot) + up.z * height) + normal.z * r) - c->position.z;
        vector_3 tmp;
        ground_pos = *QuaternionVectorTransformInverse(&tmp, &c->orientation, &gp);
        ground_normal = *QuaternionVectorTransformInverse(&tmp, &c->orientation, &normal);
        known_ground_pos = true;
    }

    vector_3 delta;
    delta.x = gpos.x - c->position.x;
    delta.y = gpos.y - c->position.y;
    delta.z = gpos.z - c->position.z;
    *outPos = InvRotate(c->orientation, delta);
    *outRot = QuatConjMul(c->orientation, grot);
}

}  // namespace nSPCreatureAnim
