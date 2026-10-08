// Slice s009ea370 -- 0x009ea370 nSPCreatureAnim::IKFinishRetargetGoals (name guessed; called by
// IKCreatureRetargetGoals 0x009eab60 on the root body after the per-body retarget loop).
// It re-sums the delegated goals of the root's children (IKSumDelegatedGoals 0x009e9af0), blends the averaged
// position / orientation into the root's own (kWeight toward the goals), then rigidly moves every child's
// particle and particle-goal by the position/rotation change and stores the new root pose in all the
// duplicated root slots (+0x190 / +0x1b0 / +0x1c8 / +0x1d4).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

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
vector_4 Normalize(const vector_4& q, float* pLength);   // 0x0099cae0
}  // namespace checkerlib
using namespace checkerlib;

extern float g_ikRetargetBlend;   // DAT 0x01550a60 (blend weight toward the summed goals)

namespace nSPCreatureAnim
{
struct creature_instance_data;

struct creature_body_static_data   // retail layout (partial)
{
    uint32_t      pad_000[0x208 / 4];
    unsigned long num_children;                    // +0x208
};

struct creature_body_instance_data   // size 0x2bc (retail)
{
    creature_body_static_data*   static_data;                  // +0x000
    uint32_t                     pad_004[2];
    creature_body_instance_data* first_child;                  // +0x00c
    uint32_t                     pad_010[(0x190 - 0x10) / 4];
    vector_3                     ik_pos;                       // +0x190 (name guessed)
    vector_4                     ik_goal_orientation;          // +0x19c
    uint32_t                     pad_1ac[1];
    vector_3                     ik_particle;                  // +0x1b0
    uint32_t                     pad_1bc[(0x1c8 - 0x1bc) / 4];
    vector_3                     ik_particle_goal;             // +0x1c8
    vector_3                     ik_particle_extra;            // +0x1d4
    uint32_t                     pad_1e0[(0x2bc - 0x1e0) / 4];
};
typedef char AssertBodySize[sizeof(creature_body_instance_data) == 0x2bc ? 1 : -1];

// 0x009e9af0
void IKSumDelegatedGoals(creature_instance_data* creature, creature_body_instance_data* body,
                         int* count, vector_3* sumPos, vector_4* sumRot);

// @ 0x009ea370
void IKFinishRetargetGoals(creature_instance_data* creature, creature_body_instance_data* body)
{
    int      count = 0;
    vector_3 sumPos;
    vector_4 sumRot;
    sumRot.x = 0.0f; sumRot.y = 0.0f; sumRot.z = 0.0f; sumRot.w = 0.0f;
    sumPos.x = 0.0f; sumPos.y = 0.0f; sumPos.z = 0.0f;

    IKSumDelegatedGoals(creature, body, &count, &sumPos, &sumRot);
    if (count == 0)
        return;

    float inv = 1.0f / (float)count;

    // normalize the summed orientation (exact zero test, x87 double length)
    float len = (float)sqrt((double)sumRot.x * sumRot.x +
                            ((double)sumRot.y * sumRot.y + ((double)sumRot.z * sumRot.z + (double)sumRot.w * sumRot.w)));
    if (len != 0.0f)
    {
        float il = 1.0f / len;
        sumRot.x = il * sumRot.x;
        sumRot.y = sumRot.y * il;
        sumRot.w = sumRot.w * il;
        sumRot.z = sumRot.z * il;
    }

    const float s = g_ikRetargetBlend;
    const float t = 1.0f - s;

    // blended position
    float newX = s * (inv * sumPos.x) + body->ik_pos.x * t;
    float newY = (inv * sumPos.y) * s + body->ik_pos.y * t;
    float newZ = (inv * sumPos.z) * s + body->ik_pos.z * t;

    // blended orientation, in the hemisphere of the old one
    float ow_x = body->ik_goal_orientation.x * t;
    float ow_y = body->ik_goal_orientation.y * t;
    float ow_z = body->ik_goal_orientation.z * t;
    float ow_w = body->ik_goal_orientation.w * t;
    float sx = s * sumRot.x, sy = sumRot.y * s, sz = sumRot.z * s, sw = sumRot.w * s;
    vector_4 b;
    if (0.0f <= ((sx * ow_x + sw * ow_w) + sz * ow_z) + sy * ow_y)
    {
        b.z = sz + ow_z;
        b.x = sx + ow_x;
        b.y = sy + ow_y;
        b.w = sw + ow_w;
    }
    else
    {
        b.z = sz - ow_z;
        b.x = sx - ow_x;
        b.y = sy - ow_y;
        b.w = sw - ow_w;
    }
    vector_4 n = Normalize(b, 0);

    // delta = n * conj(old orientation)
    const float bx = body->ik_goal_orientation.x;
    const float by = body->ik_goal_orientation.y;
    const float bz = body->ik_goal_orientation.z;
    const float bw = body->ik_goal_orientation.w;
    unsigned long numChildren = body->static_data->num_children;
    float qx = ((bw * n.x - bx * n.w) + by * n.z) - bz * n.y;
    float qy = ((bw * n.y - bx * n.z) - by * n.w) + bz * n.x;
    float qz = ((bx * n.y + bw * n.z) - by * n.x) - bz * n.w;
    float qw = ((bz * n.z + by * n.y) + bw * n.w) + bx * n.x;

    if (numChildren != 0)
    {
        float wx = qw * qx;
        float wy = qw * qy;
        float wz = qw * qz;
        float yx = qy * qx;
        float xx = -(qx * qx);
        float zx = qz * qx;
        float yy = -(qy * qy);
        float zy = qz * qy;
        float zz = -(qz * qz);
        unsigned long off = 0;
        do
        {
            creature_body_instance_data* c =
                (creature_body_instance_data*)((char*)body->first_child + off);
            float dy = c->ik_particle_goal.y - body->ik_pos.y;
            float dz = c->ik_particle_goal.z - body->ik_pos.z;
            float dx = c->ik_particle_goal.x - body->ik_pos.x;
            c->ik_particle_goal.x = ((((yx - wz) * dy + (zx + wy) * dz) + (zz + yy) * dx) * 2.0f + dx) + newX;
            c->ik_particle_goal.y = ((((zz + xx) * dy + (zy - wx) * dz) + (yx + wz) * dx) * 2.0f + dy) + newY;
            c->ik_particle_goal.z = ((((yy + xx) * dz + (zy + wx) * dy) + (zx - wy) * dx) * 2.0f + dz) + newZ;

            float py = c->ik_particle.y - body->ik_pos.y;
            float pz = c->ik_particle.z - body->ik_pos.z;
            float px = c->ik_particle.x - body->ik_pos.x;
            off += 0x2bc;
            --numChildren;
            c->ik_particle.x = (((pz * (zx + wy) + py * (yx - wz)) + px * (zz + yy)) * 2.0f + px) + newX;
            c->ik_particle.y = (((pz * (zy - wx) + py * (zz + xx)) + px * (yx + wz)) * 2.0f + py) + newY;
            c->ik_particle.z = (((py * (zy + wx) + pz * (yy + xx)) + px * (zx - wy)) * 2.0f + pz) + newZ;
        } while (numChildren != 0);
    }

    body->ik_goal_orientation = n;
    body->ik_pos.x = newX;
    body->ik_pos.y = newY;
    body->ik_pos.z = newZ;
    body->ik_particle.x = newX;
    body->ik_particle.y = newY;
    body->ik_particle.z = newZ;
    body->ik_particle_goal.x = newX;
    body->ik_particle_goal.y = newY;
    body->ik_particle_goal.z = newZ;
    body->ik_particle_extra.x = newX;
    body->ik_particle_extra.y = newY;
    body->ik_particle_extra.z = newZ;
}
}  // namespace nSPCreatureAnim
