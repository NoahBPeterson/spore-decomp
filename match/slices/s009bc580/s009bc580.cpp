// Slice s009bc580: nSPCreatureAnim body transform update (0x009bcc70, 1598 bytes).
//
// UpdateBodyTransforms(creature_instance_data* c, float dt)   (cdecl; name Claude-coined)
//
// For every body of the creature (0x2bc bytes each):
//  * a body with a pending blend (blend_active, +0x38): velocity = (blend_pos - center) / dt
//    (zero when dt <= 1e-6), then center / orientation are snapped to blend_pos / blend_rot;
//  * otherwise velocity is cleared and the body is placed from its static data:
//      - root body: orientation = static orientation, center = static center * scale;
//      - child body: orientation = parent orientation * static joint rotation (quaternion
//        product), center = parent center + parentOrientation.Rotate(scale * static.parent_r)
//        - orientation.Rotate(scale * static.local_r).
//
// Layouts: retail offsets from the disassembly (the 2008 PDB bodies are 0xc bytes smaller);
// field names are Claude-coined unless they match the PDB.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace checkerlib {
class vector_3 { public:
    float x, y, z;
    vector_3& operator=(const vector_3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
class vector_4 { public:
    float x, y, z, w;
    vector_4& operator=(const vector_4& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
};

inline vector_3 operator+(const vector_3& a, const vector_3& b) { vector_3 r; r.x = a.x + b.x; r.y = a.y + b.y; r.z = a.z + b.z; return r; }
inline vector_3 operator-(const vector_3& a, const vector_3& b) { vector_3 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r; }
inline vector_3 operator*(const vector_3& a, float s) { vector_3 r; r.x = a.x * s; r.y = a.y * s; r.z = a.z * s; return r; }

// Hamilton product a*b (rotation b, then a).
inline vector_4 QuaternionProduct(const vector_4& a, const vector_4& b)
{
    vector_4 r;
    r.x = ((a.x * b.w + b.x * a.w) - a.z * b.y) + a.y * b.z;
    r.y = ((a.y * b.w + a.z * b.x) + b.y * a.w) - b.z * a.x;
    r.z = ((a.z * b.w - a.y * b.x) + b.z * a.w) + b.y * a.x;
    r.w = ((b.w * a.w - a.x * b.x) - a.y * b.y) - b.z * a.z;
    return r;
}

// Rotates v by the unit quaternion q.                          (out of line: 0x0099c1a0)
__forceinline vector_3 QuaternionVectorTransform(const vector_4& q, const vector_3& v)
{
    vector_3 r;
    r.x = (((-(q.z * q.z) + -(q.y * q.y)) * v.x + (q.z * q.x + q.y * q.w) * v.z) + (q.y * q.x - q.z * q.w) * v.y) * 2.0f + v.x;
    r.y = (((q.y * q.x + q.z * q.w) * v.x + (q.z * q.y - q.x * q.w) * v.z) + (-(q.z * q.z) + -(q.x * q.x)) * v.y) * 2.0f + v.y;
    r.z = (((q.z * q.x - q.y * q.w) * v.x + (-(q.y * q.y) + -(q.x * q.x)) * v.z) + (q.z * q.y + q.x * q.w) * v.y) * 2.0f + v.z;
    return r;
}
}  // namespace checkerlib

using namespace checkerlib;

namespace nSPCreatureAnim {

struct creature_body_static_data {
    uint32_t pad_000[0x10c / 4];
    vector_3 center;                      // +0x10c
    vector_4 orientation;                 // +0x118
    vector_4 joint_rotation;              // +0x128 (rotation relative to the parent body)
    uint32_t pad_138[(0x344 - 0x138) / 4];
    vector_3 local_r;                     // +0x344
    vector_3 parent_r;                    // +0x350
};

struct creature_body_instance_data {      // size 0x2bc (retail)
    creature_body_static_data*   static_data;   // +0x000
    void*                        creature;      // +0x004
    creature_body_instance_data* parent;        // +0x008
    uint32_t                     pad_00c;
    vector_3                     center;        // +0x010
    vector_4                     orientation;   // +0x01c
    vector_3                     velocity;      // +0x02c
    bool                         blend_active;  // +0x038
    uint8_t                      pad_039[3];
    uint32_t                     pad_03c[(0x190 - 0x3c) / 4];
    vector_3                     target_center; // +0x190
    vector_4                     target_rotation; // +0x19c
    uint32_t                     pad_1ac[(0x280 - 0x1ac) / 4];
    vector_3                     blend_pos;     // +0x280
    vector_4                     blend_rot;     // +0x28c
    uint32_t                     pad_29c[(0x2bc - 0x29c) / 4];
};

class cGameData {
public:
    uint32_t mData[0x8c / 4];
    int  GetPoliticalID();                // 0x0097e850
    void F_9d33a0(int* p);                // 0x009d33a0
};

class anim_state_x {
public:
    void F_9e3f70(int a, int b);          // 0x009e3f70
};

struct creature_instance_data {
    uint32_t pad_000[0x18 / 4];
    vector_3 center;                      // +0x018
    vector_3 prev_center;                 // +0x024
    uint32_t pad_030[(0x3c - 0x30) / 4];
    vector_4 orientation;                 // +0x03c
    vector_4 orientation_b;               // +0x04c
    uint32_t pad_05c[(0x6c - 0x5c) / 4];
    float    field_06c;                   // +0x06c
    float    requested_scale;             // +0x070
    vector_3 velocity;                    // +0x074
    vector_3 prev_velocity;               // +0x080
    vector_3 smooth_velocity;             // +0x08c
    vector_3 smooth_velocity_prev;        // +0x098
    vector_3 rot_velocity;                // +0x0a4
    vector_3 velocity2;                   // +0x0b0
    vector_3 rot_velocity2;               // +0x0bc
    vector_4 rel_rotation;                // +0x0c8
    uint32_t pad_0d8[(0xe8 - 0xd8) / 4];
    vector_3 new_center;                  // +0x0e8
    vector_3 field_f4;                    // +0x0f4
    vector_3 direction;                   // +0x100
    float    field_10c;                   // +0x10c
    float    anim_speed;                  // +0x110
    float    field_114;                   // +0x114
    uint32_t pad_118[(0x2e4 - 0x118) / 4];
    creature_body_instance_data* mpBegin; // +0x2e4  (Bodies vector)
    creature_body_instance_data* mpEnd;   // +0x2e8
    uint32_t pad_2ec[(0x2f8 - 0x2ec) / 4];
    void*    mpAnimState;                 // +0x2f8
    uint32_t pad_2fc[(0x15b8 - 0x2fc) / 4];
    cGameData gameData;                   // +0x15b8
    float    saved_center[3];             // +0x1644
    float    saved_orientation[4];        // +0x1650

    float     F_9b6220(vector_3* a, vector_3* b);       // 0x009b6220
    vector_3* F_9b62c0(vector_3* out, vector_3* v);     // 0x009b62c0
    void      F_9b7b10(int a, int b);                   // 0x009b7b10
};

vector_3 FUN_0099c310(const vector_4* q, const vector_3* v);   // 0x0099c310

// @ 0x009bcc70
void __cdecl UpdateBodyTransforms(creature_instance_data* c, float dt)
{
    int n = (int)(c->mpEnd - c->mpBegin);
    for (int i = 0; i != n; ++i) {
        creature_body_instance_data* b = &c->mpBegin[i];
        if (b->blend_active) {
            vector_3 moved, zero;
            const vector_3* v;
            if (dt > 1e-06f) {
                moved = (b->blend_pos - b->center) * (1.0f / dt);
                v = &moved;
            } else {
                zero.x = 0.0f; zero.y = 0.0f; zero.z = 0.0f;
                v = &zero;
            }
            b->velocity = *v;
            b->center = b->blend_pos;
            b->orientation = b->blend_rot;
        } else {
            b->velocity.x = 0.0f; b->velocity.y = 0.0f; b->velocity.z = 0.0f;
            creature_body_instance_data* p = b->parent;
            if (!p) {
                b->orientation = b->static_data->orientation;
                b->center = b->static_data->center * c->requested_scale;
            } else {
                creature_body_static_data* sd = b->static_data;
                b->orientation = QuaternionProduct(p->orientation, sd->joint_rotation);
                vector_3 a = sd->local_r * c->requested_scale;
                vector_3 pr = sd->parent_r * c->requested_scale;
                vector_3 ra = QuaternionVectorTransform(b->orientation, a);
                vector_3 rp = QuaternionVectorTransform(b->parent->orientation, pr);
                b->center = (b->parent->center + rp) - ra;
            }
        }
    }
}

// @ 0x009bc580
void __cdecl FUN_009bc580(creature_instance_data* c, float dt)
{
    if (c->field_114 <= 0.0f)
        c->anim_speed = 1.0f;
    else
        c->anim_speed = c->anim_speed / c->field_114;
    c->field_114 = 1.0f;

    const float speed = c->field_06c * c->anim_speed;
    c->requested_scale = (speed > 0.001f) ? speed : 0.001f;
    c->field_10c = c->F_9b6220(&c->center, &c->field_f4);

    vector_3 dir;
    c->F_9b62c0(&dir, &c->center);
    c->direction = dir;

    const float dot = -((c->center.z * dir.z + c->center.y * dir.y) + c->center.x * dir.x);
    const float len = c->field_10c;
    c->new_center.x = c->center.x + (dir.x * dot + len * dir.x);
    c->new_center.y = c->center.y + (dir.y * dot + dir.y * len);
    c->new_center.z = c->center.z + (dir.z * dot + dir.z * len);

    if (1e-06f < dt) {
        const float inv = 1.0f / dt;
        const float vx = (c->center.x - c->prev_center.x) * inv;
        const float vy = (c->center.y - c->prev_center.y) * inv;
        const float vz = (c->center.z - c->prev_center.z) * inv;
        c->velocity.x = vx;
        c->velocity.y = vy;
        c->velocity.z = vz;

        const float sz = c->smooth_velocity.z * 0.8f + vz * 0.19999999f;
        const float sy = c->smooth_velocity.y * 0.8f + vy * 0.19999999f;
        c->smooth_velocity.x = c->smooth_velocity.x * 0.8f + vx * 0.19999999f;
        c->smooth_velocity.y = sy;
        c->smooth_velocity.z = sz;
        if ((c->smooth_velocity.x * c->smooth_velocity.x + c->smooth_velocity.y * c->smooth_velocity.y) +
            c->smooth_velocity.z * c->smooth_velocity.z < 1e-06f) {
            c->smooth_velocity.x = 0.0f;
            c->smooth_velocity.y = 0.0f;
            c->smooth_velocity.z = 0.0f;
        }

        c->rot_velocity = FUN_0099c310(&c->orientation, &c->smooth_velocity);

        const float t2z = c->velocity2.z * 0.8f +
                          ((c->smooth_velocity.z - c->smooth_velocity_prev.z) * inv) * 0.19999999f;
        const float t2y = c->velocity2.y * 0.8f +
                          ((c->smooth_velocity.y - c->smooth_velocity_prev.y) * inv) * 0.19999999f;
        c->velocity2.x = c->velocity2.x * 0.8f +
                         ((c->smooth_velocity.x - c->smooth_velocity_prev.x) * inv) * 0.19999999f;
        c->velocity2.y = t2y;
        c->velocity2.z = t2z;
        if ((c->velocity2.x * c->velocity2.x + c->velocity2.y * c->velocity2.y) +
            c->velocity2.z * c->velocity2.z < 1e-06f) {
            c->velocity2.x = 0.0f;
            c->velocity2.y = 0.0f;
            c->velocity2.z = 0.0f;
        }

        c->rot_velocity2 = FUN_0099c310(&c->orientation, &c->velocity2);

        const float a0 = c->orientation.x, a1 = c->orientation.y;
        const float a2 = c->orientation.z, a3 = c->orientation.w;
        const float b0 = c->orientation_b.x, b1 = c->orientation_b.y;
        const float b2 = c->orientation_b.z, b3 = c->orientation_b.w;
        c->rel_rotation.x = ((a0 * b3 - b0 * a3) + a1 * b2) - a2 * b1;
        c->rel_rotation.y = ((a1 * b3 - b1 * a3) - b2 * a0) + a2 * b0;
        c->rel_rotation.z = ((b1 * a0 - b2 * a3) - a1 * b0) + a2 * b3;
        c->rel_rotation.w = ((b1 * a1 + a2 * b2) + b0 * a0) + a3 * b3;

        c->prev_center = c->center;
        c->prev_velocity = c->velocity;
        c->smooth_velocity_prev = c->smooth_velocity;
        c->orientation_b = c->orientation;
    }
}

// @ 0x009bcab0
float* __cdecl FUN_009bcab0(creature_instance_data* c, float w1, float w2)
{
    const int byteDiff = (int)((char*)c->mpEnd - (char*)c->mpBegin);
    const int count = byteDiff / 700;
    if (count == 0)
        return (float*)(int)(0x5d9f7391u * (uint32_t)byteDiff);

    float* p = (float*)((char*)c->mpBegin + 0x18);
    int left = count;
    do {
        creature_body_instance_data* b = (creature_body_instance_data*)((char*)p - 0x18);
        b->blend_pos.x = b->target_center.x * w1 + b->center.x * w2;
        b->blend_pos.z = b->target_center.z * w1 + b->center.z * w2;
        b->blend_pos.y = b->target_center.y * w1 + b->center.y * w2;

        const float ax = b->target_rotation.x * w1;
        const float ay = b->target_rotation.y * w1;
        const float az = b->target_rotation.z * w1;
        const float aw = b->target_rotation.w * w1;
        const float bx = b->orientation.x * w2;
        const float by = b->orientation.y * w2;
        const float bz = b->orientation.z * w2;
        const float bw = b->orientation.w * w2;
        const float dot = ((aw * bw + az * bz) + ay * by) + ax * bx;
        if (!(dot < 0.0f)) {
            b->blend_rot.x = ax + bx;
            b->blend_rot.y = ay + by;
            b->blend_rot.z = az + bz;
            b->blend_rot.w = aw + bw;
        } else {
            b->blend_rot.x = ax - bx;
            b->blend_rot.y = ay - by;
            b->blend_rot.z = az - bz;
            b->blend_rot.w = aw - bw;
        }
        p = (float*)((char*)p + 0x2bc);
        --left;
    } while (left != 0);
    return p;
}

// @ 0x009bd2b0
void __cdecl FUN_009bd2b0(creature_instance_data* c)
{
    c->saved_center[0] = c->center.x;
    c->saved_center[1] = c->center.y;
    c->saved_center[2] = c->center.z;
    c->saved_orientation[0] = c->orientation.x;
    c->saved_orientation[1] = c->orientation.y;
    c->saved_orientation[2] = c->orientation.z;
    c->saved_orientation[3] = c->orientation.w;
    if (c->mpAnimState == 0) {
        ((anim_state_x*)&c->mpAnimState)->F_9e3f70(6, 4);
        c->F_9b7b10(0, 0);
    }
    if (c->gameData.GetPoliticalID() != 0)
        c->gameData.F_9d33a0((int*)&c->mpAnimState);
}

}  // namespace nSPCreatureAnim
