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
struct vector_3 {
    float x, y, z;
    vector_3& operator=(const vector_3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct vector_4 {
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
    uint32_t                     pad_03c[(0x280 - 0x3c) / 4];
    vector_3                     blend_pos;     // +0x280
    vector_4                     blend_rot;     // +0x28c
    uint32_t                     pad_29c[(0x2bc - 0x29c) / 4];
};

struct creature_instance_data {
    uint32_t pad_000[0x70 / 4];
    float    requested_scale;             // +0x070
    uint32_t pad_074[(0x2e4 - 0x74) / 4];
    creature_body_instance_data* mpBegin; // +0x2e4  (Bodies vector)
    creature_body_instance_data* mpEnd;   // +0x2e8
};

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

}  // namespace nSPCreatureAnim
