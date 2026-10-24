// Slice s00a06600: creature pose refresh (0x00a06600, 1863 bytes).
//
// pose_bone_set::Refresh(float elapsed, int mode)  (thiscall, ret 8)
//
// If the set holds any bones: notify the owner through vtable slot +0x28, then for every enabled
// bone rotate its cached axis (creature +0x160) by the bone orientation and add the result to the
// bone position, post-multiply the bone orientation by the creature quaternion (+0x170), normalise
// it when the creature's flags (+0x10 & 0x1f) are clear, publish the bone position / orientation
// into the creature (+0x30, +0x5c), rotate the creature vector (+0x118) by the bone orientation
// and add it to the bone position to get the creature position, build the creature orientation
// (+0x3c) from the bone orientation and the creature quaternion (+0x128), and finally move the
// creature position along the ground normal by the ground height delta measured since the start of
// the update. vtable slot +0x2c is notified last.
//
// Layouts: retail offsets; names follow the creature_instance_data view of s009bfc20 (position
// +0x18, orientation +0x3c, ground_up +0x100, rest_orientation_q +0x118) extended with the fields
// this function touches. pose_bone / pose_bone_set are invented.
//
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

namespace checkerlib {
class vector_3 { public: float x, y, z; };
class vector_4 { public: float x, y, z, w; };
}  // namespace checkerlib

using namespace checkerlib;

namespace nSPCreatureAnim {

struct creature_instance_data;

// One bone of an animated pose: world position, orientation, the parent basis it was refreshed
// against, and the creature instance that owns the pose.
struct pose_bone {
    uint32_t pad_000;                    // +0x000
    vector_3 position;                   // +0x004
    vector_4 orientation;                // +0x010 (x, y, z, w)
    vector_3 cached_axis;                // +0x020 (creature +0x160)
    vector_4 cached_orientation;         // +0x02c (creature +0x170)
    uint8_t  pad_03c[0x64 - 0x3c];       // +0x03c
    uint8_t  enabled;                    // +0x064
    uint8_t  pad_065[0x17c - 0x065];     // +0x065
    creature_instance_data* creature;    // +0x17c
};

// Creature instance data, limited to what the pose refresh reads and writes.
struct creature_instance_data {
    uint32_t pad_000[0x10 / 4];          // +0x000
    uint8_t  flags_010;                  // +0x010 (low 5 bits: orientation already unit)
    uint8_t  pad_011[0x18 - 0x11];       // +0x011
    vector_3 position;                   // +0x018
    uint32_t pad_024[(0x030 - 0x24) / 4];// +0x024
    float    f_030;                      // +0x030
    float    f_034;                      // +0x034
    float    f_038;                      // +0x038
    vector_4 orientation;                // +0x03c (x, y, z, w)
    uint32_t pad_04c[(0x05c - 0x4c) / 4];// +0x04c
    vector_4 q_05c;                      // +0x05c (x, y, z, w)
    uint32_t pad_06c[(0x118 - 0x6c) / 4];// +0x06c
    vector_3 v_118;                      // +0x118 (rotation axis * angle, unscaled)
    uint32_t pad_124;                    // +0x124
    float    f_128;                      // +0x128
    float    f_12c;                      // +0x12c
    float    f_130;                      // +0x130
    float    f_134;                      // +0x134
    uint32_t pad_138[(0x160 - 0x138) / 4];// +0x138 (extent lives here, see s009bfc20)
    vector_3 v_160;                      // +0x160 (rotation axis * angle, scaled)
    uint32_t pad_16c;                    // +0x16c
    vector_4 q_170;                      // +0x170 (x, y, z, w)

    float GetGroundHeight(const vector_3* pos, vector_3* normal);   // 0x009b6220
    vector_3* GetGroundUp(vector_3* out, const vector_3* pos);      // 0x009b62c0
};

// The set of bones refreshed together; only the vtable notification slots and the bone vector are
// visible here.
struct pose_bone_set {
    void**   vtable;                     // +0x000
    uint32_t pad_004[(0x24 - 0x04) / 4]; // +0x004
    pose_bone** bone_begin;              // +0x024
    pose_bone** bone_end;                // +0x028

    void Refresh(float elapsed, int mode);
};

typedef void (__thiscall* pose_set_notify)(pose_bone_set* set, float elapsed, int mode);

}  // namespace nSPCreatureAnim

using namespace nSPCreatureAnim;

// Rotates v by the inverse of the unit quaternion q, in the binary's term order (same helper as
// s009bfc20; the negation is a sign flip, so /fp:fast keeps the xorps form).
static __forceinline vector_3 InvRotate(const vector_4& q, const vector_3& v,
                                        const vector_3& add)
{
    vector_3 r;
    r.x = ((-(q.z * q.z) + -(q.y * q.y)) * v.x + (q.z * q.x + q.y * q.w) * v.z +
           (q.y * q.x - q.z * q.w) * v.y) * 2.0f + v.x + add.x;
    r.y = ((-(q.z * q.z) + -(q.x * q.x)) * v.y + (q.z * q.y - q.x * q.w) * v.z +
           (q.y * q.x + q.z * q.w) * v.x) * 2.0f + v.y + add.y;
    r.z = ((-(q.y * q.y) + -(q.x * q.x)) * v.z + (q.z * q.x - q.y * q.w) * v.x +
           (q.z * q.y + q.x * q.w) * v.y) * 2.0f + v.z + add.z;
    return r;
}

// @ 0x00a06600
void pose_bone_set::Refresh(float elapsed, int mode)
{
    if (this->bone_begin == this->bone_end)
        return;

    ((pose_set_notify)this->vtable[10])(this, elapsed, mode);

    uint32_t count = (uint32_t)(this->bone_end - this->bone_begin);
    for (uint32_t i = 0; i < count; i++) {
        pose_bone* bone = this->bone_begin[i];
        if (!bone->enabled)
            continue;

        creature_instance_data* c = bone->creature;
        float base_height = c->GetGroundHeight(&c->position, 0);

        bone->cached_axis.x = c->v_160.x;
        bone->cached_axis.y = c->v_160.y;
        bone->cached_axis.z = c->v_160.z;
        bone->cached_orientation.x = c->q_170.x;
        bone->cached_orientation.y = c->q_170.y;
        bone->cached_orientation.z = c->q_170.z;
        bone->cached_orientation.w = c->q_170.w;

        vector_3 offset = InvRotate(bone->orientation, c->v_160, bone->position);
        bone->position.x = offset.x;
        bone->position.y = offset.y;
        bone->position.z = offset.z;

        float qx = bone->orientation.x;
        float qy = bone->orientation.y;
        float qz = bone->orientation.z;
        float qw = bone->orientation.w;
        float ax = c->q_170.x;
        float ay = c->q_170.y;
        float az = c->q_170.z;
        float aw = c->q_170.w;
        bone->orientation.x = ((qx * aw + ax * qw) - ay * qz) + az * qy;
        bone->orientation.y = ((qy * aw + ax * qz) + ay * qw) - az * qx;
        bone->orientation.z = ((qz * aw - qy * ax) + ay * qx) + az * qw;
        bone->orientation.w = ((qw * aw - qx * ax) - qy * ay) - qz * az;

        if ((c->flags_010 & 0x1f) == 0) {
            float inv = 1.0f / sqrtf(bone->orientation.x * bone->orientation.x +
                                     bone->orientation.y * bone->orientation.y +
                                     bone->orientation.z * bone->orientation.z +
                                     bone->orientation.w * bone->orientation.w);
            bone->orientation.x *= inv;
            bone->orientation.y *= inv;
            bone->orientation.z *= inv;
            bone->orientation.w *= inv;
        }

        c->f_030 = bone->position.x;
        c->f_034 = bone->position.y;
        c->f_038 = bone->position.z;
        c->q_05c.x = bone->orientation.x;
        c->q_05c.y = bone->orientation.y;
        c->q_05c.z = bone->orientation.z;
        c->q_05c.w = bone->orientation.w;

        vector_3 spin = InvRotate(bone->orientation, c->v_118, bone->position);
        c->position.x = spin.x;
        c->position.y = spin.y;
        c->position.z = spin.z;

        qx = bone->orientation.x;
        qy = bone->orientation.y;
        qz = bone->orientation.z;
        qw = bone->orientation.w;
        float rw = c->f_128;
        float rx = c->f_134;
        float ry = c->f_130;
        float rz = c->f_12c;
        c->orientation.x = ((rw * qw + qx * rx) - rz * qz) + ry * qy;
        c->orientation.y = ((qz * rw + rz * qw) + qy * rx) - ry * qx;
        c->orientation.z = ((qz * rx - qy * rw) + ry * qw) + rz * qx;
        c->orientation.w = ((qw * rx - rw * qx) - qy * rz) - ry * qz;

        float height = c->GetGroundHeight(&c->position, 0);
        float lift = height - base_height;
        vector_3 up;
        c->GetGroundUp(&up, &c->position);
        c->position.x = up.x * lift + c->position.x;
        c->position.y = c->position.y + up.y * lift;
        c->position.z = c->position.z + up.z * lift;
    }

    ((pose_set_notify)this->vtable[11])(this, elapsed, mode);
}
