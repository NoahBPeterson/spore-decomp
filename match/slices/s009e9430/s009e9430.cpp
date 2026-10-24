// Slice s009e9430 -- 0x009e9af0 nSPCreatureAnim::IKSumDelegatedGoals (name guessed; the IK goal solver, same
// translation unit as s009e7bb0 / s009eab60):
//   for every child body of `body` whose ik_goal_mode is 1 (blended goal in ik_delegate_pos/rot) or 2 (anchored
//   goal in ik_particle_goal / ik_goal_orientation), count it, accumulate the goal orientation (relative to the
//   child's joint orientation; sign-flipped to stay in the hemisphere of the running sum) into sumRot and the
//   goal position (rotated child-joint offset + goal position) into sumPos.  The caller averages / normalizes.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <stddef.h>
#include <math.h>

namespace checkerlib
{
class vector_3
{ public:
    float x, y, z;
};
class vector_4
{ public:
    float x, y, z, w;
    void __thiscall assign(const vector_4* src);   // 0x00572600
};

vector_4* __cdecl QuatNormalize(vector_4* out, const vector_4* in, float* lenOut);  // 0x0099cae0
vector_3* __cdecl QuaternionVectorTransform(vector_3* out, const vector_4* q,
                                            const vector_3* v);                    // 0x0099c1a0
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
    uint32_t                     pad_010[(0x58 - 0x10) / 4];
    vector_3                     ik_center_local;              // +0x58
    float                        ik_center_weight;             // +0x64
    vector_4                     ik_orientation_local;         // +0x68
    float                        ik_orientation_weight;        // +0x78
    vector_3                     ik_parent_r_local;            // +0x7c
    float                        ik_parent_r_weight;           // +0x88
    vector_4                     ik_parent_q_local;            // +0x8c
    float                        ik_parent_q_weight;           // +0x9c
    uint32_t                     pad_0a0[(0x19c - 0xa0) / 4];
    vector_4                     ik_goal_orientation;          // +0x19c
    uint32_t                     pad_1ac[(0x1c8 - 0x1ac) / 4];
    vector_3                     ik_particle_goal;             // +0x1c8
    vector_3                     ik_particle_extra;            // +0x1d4
    vector_3                     ik_delegate_pos;              // +0x1e0
    vector_4                     ik_delegate_rot;              // +0x1ec
    uint32_t                     pad_1fc[(0x200 - 0x1fc) / 4];
    vector_4                     ik_rest_orientation;          // +0x200
    uint32_t                     pad_210[(0x238 - 0x210) / 4];
    int                          ik_goal_mode;                 // +0x238
    uint32_t                     pad_23c[(0x2bc - 0x23c) / 4];
};

typedef char AssertBodySize[sizeof(creature_body_instance_data) == 0x2bc ? 1 : -1];
typedef char AssertBodyDelegate[offsetof(creature_body_instance_data, ik_delegate_rot) == 0x1ec ? 1 : -1];
typedef char AssertBodyMode[offsetof(creature_body_instance_data, ik_goal_mode) == 0x238 ? 1 : -1];
typedef char AssertStaticJoint[offsetof(creature_body_static_data, parent_local_joint_r__SCALABLE) == 0x350 ? 1 : -1];
typedef char AssertBodyCenter[offsetof(creature_body_instance_data, ik_center_local) == 0x58 ? 1 : -1];
typedef char AssertBodyRest[offsetof(creature_body_instance_data, ik_rest_orientation) == 0x200 ? 1 : -1];

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
// Goal transform for a body in blended-goal mode (mode 1).  Normalises the four
// optional joint contributions first, then resolves the goal orientation and
// position from whichever of them are enabled.  p2 is the body-space offset of
// the child joint, p3 the fallback world-space goal position.
// @ 0x009e9430
void FUN_009e9430(creature_body_instance_data* self, const vector_3* p2,
                  const vector_3* p3, bool f4, bool f5, bool f6, bool f7)
{
    const float one = 1.0f;
    vector_4 tmp;

    if (f4)
    {
        float inv = one / self->ik_center_weight;
        float x = inv * self->ik_center_local.x;
        float y = inv * self->ik_center_local.y;
        float z = inv * self->ik_center_local.z;
        self->ik_center_local.x = x;
        self->ik_center_local.y = y;
        self->ik_center_local.z = z;
        self->ik_center_weight = one;
    }
    if (f5)
    {
        vector_4* q = QuatNormalize(&tmp, &self->ik_orientation_local, 0);
        self->ik_orientation_local.x = q->x;
        self->ik_orientation_local.y = q->y;
        self->ik_orientation_local.z = q->z;
        self->ik_orientation_local.w = q->w;
        self->ik_orientation_weight = one;
    }
    if (f6)
    {
        float inv = one / self->ik_parent_r_weight;
        float x = inv * self->ik_parent_r_local.x;
        float y = inv * self->ik_parent_r_local.y;
        float z = inv * self->ik_parent_r_local.z;
        self->ik_parent_r_local.x = x;
        self->ik_parent_r_local.y = y;
        self->ik_parent_r_local.z = z;
        self->ik_parent_r_weight = one;
    }
    if (f7)
    {
        vector_4* q = QuatNormalize(&tmp, &self->ik_parent_q_local, 0);
        self->ik_parent_q_local.x = q->x;
        self->ik_parent_q_local.y = q->y;
        self->ik_parent_q_local.z = q->z;
        self->ik_parent_q_local.w = q->w;
        self->ik_parent_q_weight = one;
    }

    if (f4)
    {
        if (f5)
        {
            self->ik_delegate_rot.x = self->ik_orientation_local.x;
            self->ik_delegate_rot.y = self->ik_orientation_local.y;
            self->ik_delegate_rot.z = self->ik_orientation_local.z;
            self->ik_delegate_rot.w = self->ik_orientation_local.w;
            {
                vector_3* r = QuaternionVectorTransform((vector_3*)&tmp, &self->ik_orientation_local, p2);
                self->ik_delegate_pos.x = self->ik_center_local.x + r->x;
                self->ik_delegate_pos.y = self->ik_center_local.y + r->y;
                self->ik_delegate_pos.z = self->ik_center_local.z + r->z;
            }

            if (!f6)
            {
                if (!f7)
                    return;
                self->ik_goal_orientation.assign(&self->ik_parent_q_local);
                self->ik_particle_goal.x = self->ik_delegate_pos.x;
                self->ik_particle_goal.y = self->ik_delegate_pos.y;
                self->ik_particle_goal.z = self->ik_delegate_pos.z;
                return;
            }

            if (f7)
            {
                self->ik_goal_orientation.assign(&self->ik_parent_q_local);
                vector_3* r = QuaternionVectorTransform((vector_3*)&tmp, &self->ik_parent_q_local, p2);
                self->ik_particle_goal.x = r->x + self->ik_parent_r_local.x;
                self->ik_particle_goal.y = r->y + self->ik_parent_r_local.y;
                self->ik_particle_goal.z = r->z + self->ik_parent_r_local.z;
            }
            else
            {
                self->ik_goal_orientation.assign(&self->ik_orientation_local);
                vector_3* r = QuaternionVectorTransform((vector_3*)&tmp, &self->ik_orientation_local, p2);
                self->ik_particle_goal.x = r->x + self->ik_parent_r_local.x;
                self->ik_particle_goal.y = r->y + self->ik_parent_r_local.y;
                self->ik_particle_goal.z = r->z + self->ik_parent_r_local.z;
            }
            return;
        }

        self->ik_delegate_rot.x = self->ik_rest_orientation.x;
        self->ik_delegate_rot.y = self->ik_rest_orientation.y;
        self->ik_delegate_rot.z = self->ik_rest_orientation.z;
        self->ik_delegate_rot.w = self->ik_rest_orientation.w;

        if (!f6)
        {
            if (!f7)
                goto update_delegate_from_goal;

            self->ik_goal_orientation.assign(&self->ik_parent_q_local);
            {
                vector_3* r = QuaternionVectorTransform((vector_3*)&tmp, &self->ik_goal_orientation, p2);
                float x = p3->x;
                float y = r->y + p3->y;
                float z = r->z + p3->z;
                x = x + r->x;
                self->ik_particle_goal.x = x;
                self->ik_particle_goal.y = y;
                self->ik_particle_goal.z = z;
            }
        }
        else if (f7)
        {
            self->ik_goal_orientation.assign(&self->ik_parent_q_local);
            vector_3* r = QuaternionVectorTransform((vector_3*)&tmp, &self->ik_parent_q_local, p2);
            float x = self->ik_parent_r_local.x;
            float y = self->ik_parent_r_local.y + r->y;
            float z = self->ik_parent_r_local.z + r->z;
            x = x + r->x;
            self->ik_particle_goal.x = x;
            self->ik_particle_goal.y = y;
            self->ik_particle_goal.z = z;
        }
        else
        {
            self->ik_goal_orientation.assign(&self->ik_rest_orientation);
            vector_3* r = QuaternionVectorTransform((vector_3*)&tmp, &self->ik_rest_orientation, p2);
            self->ik_particle_goal.x = r->x + self->ik_parent_r_local.x;
            self->ik_particle_goal.y = self->ik_parent_r_local.y + r->y;
            self->ik_particle_goal.z = self->ik_parent_r_local.z + r->z;
        }

    update_delegate_from_goal:
        {
            vector_3* r = QuaternionVectorTransform((vector_3*)&tmp, &self->ik_goal_orientation, p2);
            self->ik_delegate_pos.x = r->x + self->ik_center_local.x;
            self->ik_delegate_pos.y = self->ik_center_local.y + r->y;
            self->ik_delegate_pos.z = self->ik_center_local.z + r->z;
        }
        return;
    }

    if (!f5)
        return;

    self->ik_delegate_rot.x = self->ik_orientation_local.x;
    self->ik_delegate_rot.y = self->ik_orientation_local.y;
    self->ik_delegate_rot.z = self->ik_orientation_local.z;
    self->ik_delegate_rot.w = self->ik_orientation_local.w;

    if (!f6)
    {
        if (!f7)
            goto store_goal_to_delegate;

        self->ik_goal_orientation.assign(&self->ik_parent_q_local);
        {
            vector_3* r = QuaternionVectorTransform((vector_3*)&tmp, &self->ik_goal_orientation, p2);
            float x = p3->x;
            float y = r->y + p3->y;
            float z = r->z + p3->z;
            x = x + r->x;
            self->ik_particle_goal.x = x;
            self->ik_particle_goal.y = y;
            self->ik_particle_goal.z = z;
        }
    }
    else if (f7)
    {
        self->ik_goal_orientation.assign(&self->ik_parent_q_local);
        vector_3* r = QuaternionVectorTransform((vector_3*)&tmp, &self->ik_parent_q_local, p2);
        self->ik_particle_goal.x = r->x + self->ik_parent_r_local.x;
        self->ik_particle_goal.y = r->y + self->ik_parent_r_local.y;
        self->ik_particle_goal.z = r->z + self->ik_parent_r_local.z;
    }
    else
    {
        self->ik_goal_orientation.assign(&self->ik_orientation_local);
        vector_3* r = QuaternionVectorTransform((vector_3*)&tmp, &self->ik_orientation_local, p2);
        float x = self->ik_parent_r_local.x;
        float y = self->ik_parent_r_local.y + r->y;
        float z = self->ik_parent_r_local.z + r->z;
        x = x + r->x;
        self->ik_particle_goal.x = x;
        self->ik_particle_goal.y = y;
        self->ik_particle_goal.z = z;
    }

store_goal_to_delegate:
    self->ik_delegate_pos.x = self->ik_particle_goal.x;
    self->ik_delegate_pos.y = self->ik_particle_goal.y;
    self->ik_delegate_pos.z = self->ik_particle_goal.z;
}

// Spline normal for the rest orientation of a body joint.  Builds the rotation
// matrix from ik_rest_orientation, crosses the supplied spline direction with
// it twice and normalises the result.
// @ 0x009e99a0
void ComputeSplineNormal(creature_body_instance_data* self, vector_3* out, const vector_3* dir)
{
    const float qx = self->ik_rest_orientation.x;
    const float qy = self->ik_rest_orientation.y;
    const float qz = self->ik_rest_orientation.z;
    const float qw = self->ik_rest_orientation.w;

    const float m00 = 1.0f - (qy * qy + qz * qz) * 2.0f;
    const float m01 = (qz * qx - qw * qy) * 2.0f;
    const float m02 = (qw * qz + qy * qx) * 2.0f;

    const float a = dir->y * m01 - dir->z * m02;
    const float b = dir->z * m00 - dir->x * m01;
    const float c = dir->x * m02 - dir->y * m00;

    const float n0 = dir->z * b - dir->y * c;
    const float n1 = dir->x * c - dir->z * a;
    const float n2 = dir->y * a - dir->x * b;

    const float len = sqrtf(n0 * n0 + (n2 * n2 + n1 * n1));
    const float inv = 1.0f / (len + 1e-8f);

    out->x = n0 * inv;
    out->y = inv * n1;
    out->z = n2 * inv;
}
}  // namespace nSPCreatureAnim
