// Slice s009e9430 -- 0x009e9af0 nSPCreatureAnim::IKSumDelegatedGoals (name guessed; the IK goal solver, same
// translation unit as s009e7bb0 / s009eab60):
//   for every child body of `body` whose ik_goal_mode is 1 (blended goal in ik_delegate_pos/rot) or 2 (anchored
//   goal in ik_particle_goal / ik_goal_orientation), count it, accumulate the goal orientation (relative to the
//   child's joint orientation; sign-flipped to stay in the hemisphere of the running sum) into sumRot and the
//   goal position (rotated child-joint offset + goal position) into sumPos.  The caller averages / normalizes.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <stddef.h>

namespace checkerlib
{
struct vector_3
{
    float x, y, z;
};
struct vector_4
{
    float x, y, z, w;
};
}  // namespace checkerlib
using namespace checkerlib;

namespace nSPCreatureAnim
{
struct creature_instance_data
{
    uint32_t pad_000[0x70 / 4];
    float    requested_scale;   // +0x070
};

struct creature_body_static_data   // retail layout (partial)
{
    uint32_t      pad_000[0x128 / 4];
    vector_4      joint_orientation_q;             // +0x128 (name guessed)
    uint32_t      pad_138[(0x208 - 0x138) / 4];
    unsigned long num_children;                    // +0x208
    uint32_t      pad_20c[(0x344 - 0x20c) / 4];
    vector_3      ik_joint_r__SCALABLE;            // +0x344
    vector_3      parent_local_joint_r__SCALABLE;  // +0x350
};

struct creature_body_instance_data   // size 0x2bc (retail)
{
    creature_body_static_data*   static_data;                  // +0x000
    uint32_t                     pad_004[2];
    creature_body_instance_data* first_child;                  // +0x00c
    uint32_t                     pad_010[(0x19c - 0x10) / 4];
    vector_4                     ik_goal_orientation;          // +0x19c
    uint32_t                     pad_1ac[(0x1c8 - 0x1ac) / 4];
    vector_3                     ik_particle_goal;             // +0x1c8
    vector_3                     ik_particle_extra;            // +0x1d4
    vector_3                     ik_delegate_pos;              // +0x1e0
    vector_4                     ik_delegate_rot;              // +0x1ec
    uint32_t                     pad_1fc[(0x238 - 0x1fc) / 4];
    int                          ik_goal_mode;                 // +0x238
    uint32_t                     pad_23c[(0x2bc - 0x23c) / 4];
};

typedef char AssertBodySize[sizeof(creature_body_instance_data) == 0x2bc ? 1 : -1];
typedef char AssertBodyDelegate[offsetof(creature_body_instance_data, ik_delegate_rot) == 0x1ec ? 1 : -1];
typedef char AssertBodyMode[offsetof(creature_body_instance_data, ik_goal_mode) == 0x238 ? 1 : -1];
typedef char AssertStaticJoint[offsetof(creature_body_static_data, parent_local_joint_r__SCALABLE) == 0x350 ? 1 : -1];

// a * conjugate(b) written the way the original orders each product (see the two uses below).
inline void RelativeA(vector_4& r, const vector_4& q, const vector_4& j)
{
    r.x = ((q.x * j.w - j.x * q.w) + j.y * q.z) - j.z * q.y;
    r.y = ((q.y * j.w - q.z * j.x) - j.y * q.w) + j.z * q.x;
    r.z = ((q.y * j.x + q.z * j.w) - j.y * q.x) - j.z * q.w;
    r.w = ((q.y * j.y + j.z * q.z) + j.x * q.x) + q.w * j.w;
}

// Blended-goal quaternion transform (mode 1).
inline void XformA(vector_3& r, const vector_4& q, const vector_3& v)
{
    r.x = (((-(q.z * q.z) + -(q.y * q.y)) * v.x + (q.z * q.x + q.w * q.y) * v.z) + (q.y * q.x - q.w * q.z) * v.y) * 2.0f + v.x;
    r.y = (((q.y * q.x + q.w * q.z) * v.x + (-(q.z * q.z) + -(q.x * q.x)) * v.y) + (q.y * q.z - q.w * q.x) * v.z) * 2.0f + v.y;
    r.z = (((q.z * q.x - q.w * q.y) * v.x + (-(q.y * q.y) + -(q.x * q.x)) * v.z) + (q.y * q.z + q.w * q.x) * v.y) * 2.0f + v.z;
}

// Anchored-goal quaternion transform (mode 2).
inline void XformB(vector_3& r, const vector_4& q, const vector_3& v)
{
    r.x = (((q.z * q.x + q.w * q.y) * v.z + (q.y * q.x - q.w * q.z) * v.y) + (-(q.z * q.z) + -(q.y * q.y)) * v.x) * 2.0f + v.x;
    r.y = (((-(q.z * q.z) + -(q.x * q.x)) * v.y + (q.z * q.y - q.w * q.x) * v.z) + (q.y * q.x + q.w * q.z) * v.x) * 2.0f + v.y;
    r.z = (((q.z * q.y + q.w * q.x) * v.y + (-(q.y * q.y) + -(q.x * q.x)) * v.z) + (q.z * q.x - q.w * q.y) * v.x) * 2.0f + v.z;
}

// @ 0x009e9af0
void IKSumDelegatedGoals(creature_instance_data* creature, creature_body_instance_data* body,
                         int* count, vector_3* sumPos, vector_4* sumRot)
{
    unsigned long numChildren = body->static_data->num_children;
    for (unsigned long i = 0; i < numChildren; ++i)
    {
        creature_body_instance_data* child = &body->first_child[i];
        switch (child->ik_goal_mode)
        {
        case 1:
        {
            ++*count;
            vector_4 q;
            RelativeA(q, child->ik_delegate_rot, child->static_data->joint_orientation_q);
            if (0.0f <= ((sumRot->x * q.x + sumRot->w * q.w) + sumRot->y * q.y) + sumRot->z * q.z)
            {
                sumRot->y = sumRot->y + q.y;
                sumRot->x = sumRot->x + q.x;
                sumRot->z = sumRot->z + q.z;
                sumRot->w = sumRot->w + q.w;
            }
            else
            {
                sumRot->y = sumRot->y - q.y;
                sumRot->x = sumRot->x - q.x;
                sumRot->z = sumRot->z - q.z;
                sumRot->w = sumRot->w - q.w;
            }
            const float scale = creature->requested_scale;
            creature_body_static_data* cs = child->static_data;
            creature_body_static_data* bs = body->static_data;
            vector_3 d;
            d.x = bs->ik_joint_r__SCALABLE.x * scale - cs->parent_local_joint_r__SCALABLE.x * scale;
            d.y = bs->ik_joint_r__SCALABLE.y * scale - cs->parent_local_joint_r__SCALABLE.y * scale;
            d.z = bs->ik_joint_r__SCALABLE.z * scale - cs->parent_local_joint_r__SCALABLE.z * scale;
            vector_3 t;
            XformA(t, q, d);
            sumPos->x = sumPos->x + (child->ik_delegate_pos.x + t.x);
            sumPos->y = sumPos->y + (child->ik_delegate_pos.y + t.y);
            sumPos->z = (child->ik_delegate_pos.z + t.z) + sumPos->z;
            break;
        }
        case 2:
        {
            ++*count;
            vector_4 q;
            RelativeA(q, child->ik_goal_orientation, child->static_data->joint_orientation_q);
            if (0.0f <= ((sumRot->y * q.y + sumRot->z * q.z) + sumRot->w * q.w) + sumRot->x * q.x)
            {
                sumRot->y = sumRot->y + q.y;
                sumRot->x = sumRot->x + q.x;
                sumRot->z = sumRot->z + q.z;
                sumRot->w = sumRot->w + q.w;
            }
            else
            {
                sumRot->y = sumRot->y - q.y;
                sumRot->x = sumRot->x - q.x;
                sumRot->z = sumRot->z - q.z;
                sumRot->w = sumRot->w - q.w;
            }
            const float scale = creature->requested_scale;
            creature_body_static_data* cs = child->static_data;
            creature_body_static_data* bs = body->static_data;
            vector_3 d;
            d.x = bs->ik_joint_r__SCALABLE.x * scale - cs->parent_local_joint_r__SCALABLE.x * scale;
            d.y = bs->ik_joint_r__SCALABLE.y * scale - cs->parent_local_joint_r__SCALABLE.y * scale;
            d.z = bs->ik_joint_r__SCALABLE.z * scale - cs->parent_local_joint_r__SCALABLE.z * scale;
            vector_3 t;
            XformB(t, q, d);
            sumPos->x = (child->ik_particle_goal.x + t.x) + sumPos->x;
            sumPos->y = sumPos->y + (child->ik_particle_goal.y + t.y);
            sumPos->z = (child->ik_particle_goal.z + t.z) + sumPos->z;
            break;
        }
        }
    }
}
}  // namespace nSPCreatureAnim
