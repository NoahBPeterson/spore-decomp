// Slice s009e8860 -- nSPCreatureAnim IK: IKFinishGoals (0x009e8860, 2099 bytes).
//
// Called by IKCreatureToGoals right after IKComputeRootGoal. It collects the goals that the
// children of the root body delegate up to it (ik_utils::DelegateGoals), averages the summed
// goal position, renormalises the summed goal rotation, blends both with the body's current
// pose (weight g_IKGoalBlend), then rotates every child's two particle positions
// (ik_particle_goal at +0x1c8 and ik_particle at +0x1b0) by the change of the body's rotation
// about the body's old position and moves them to the new one. Finally the body's pose and its
// three particle copies are overwritten with the blended result.
//
// Layouts come from the retail disassembly; names marked "(name guessed)" are not confirmed.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

namespace checkerlib
{
class vector_3 { public: float x, y, z; };
class vector_4 { public: float x, y, z, w; };
vector_4 Normalize(const vector_4& q, float* pLength);    // 0x0099cae0 (out of line, sret)
}
using namespace checkerlib;

namespace nSPCreatureAnim
{
struct creature_instance_data;

struct ik_goals_data                                  // size 0x4
{
    unsigned char TypeAndFlags;  // +0x0
    unsigned char Reserved;      // +0x1
    unsigned char ChildIdx;      // +0x2
    unsigned char NumBIdx;       // +0x3
    ik_goals_data() : TypeAndFlags(4), Reserved(0), ChildIdx(0xff), NumBIdx(0xff) {}
};

struct creature_body_static_data                      // retail layout (partial)
{
    uint32_t      pad_000[0x208 / 4];
    unsigned long num_children;                    // +0x208
};

struct creature_body_instance_data                    // size 0x2bc (retail)
{
    creature_body_static_data*   static_data;                  // +0x000
    creature_instance_data*      creature;                     // +0x004
    creature_body_instance_data* parent;                       // +0x008
    creature_body_instance_data* first_child;                  // +0x00c
    uint32_t                     pad_010[(0x190 - 0x10) / 4];
    vector_3                     ik_goal_pos;                  // +0x190 (name guessed)
    vector_4                     ik_goal_orientation;          // +0x19c (name guessed)
    ik_goals_data                ik_goals;                     // +0x1ac
    vector_3                     ik_particle;                  // +0x1b0
    vector_3                     ik_particle_rest;             // +0x1bc
    vector_3                     ik_particle_goal;             // +0x1c8
    vector_3                     ik_particle_goal_prev;        // +0x1d4 (name guessed)
    uint32_t                     pad_1e0[(0x2bc - 0x1e0) / 4];
};

extern float g_IKGoalBlend;                           // 0x01550a60

void ik_utils_DelegateGoals(creature_instance_data* creature, creature_body_instance_data* body,
                            int* numDelegated, int* numPos, int* numRot, vector_3* sumPos,
                            vector_4* sumRot, ik_goals_data* goals);                    // 0x009e7bb0

// @ 0x009e8860
void IKFinishGoals(creature_instance_data* creature, creature_body_instance_data* body)
{
    int numDelegated = 0, numPos = 0, numRot = 0;
    vector_3 sumPos = { 0.0f, 0.0f, 0.0f };
    vector_4 sumRot = { 0.0f, 0.0f, 0.0f, 0.0f };
    ik_goals_data goals;
    ik_utils_DelegateGoals(creature, body, &numDelegated, &numPos, &numRot, &sumPos, &sumRot, &goals);
    if (numPos == 0)
        return;

    // Average position; renormalised rotation.
    float invN = 1.0f / (float)numPos;
    float len = (float)sqrt((double)sumRot.x * sumRot.x + (double)sumRot.w * sumRot.w
                            + (double)sumRot.z * sumRot.z + (double)sumRot.y * sumRot.y);
    if (len != 0.0f)
    {
        float s = 1.0f / len;
        sumRot.x = s * sumRot.x;
        sumRot.y = sumRot.y * s;
        sumRot.w = sumRot.w * s;
        sumRot.z = sumRot.z * s;
    }

    // Blend with the body's current pose.
    const float a = g_IKGoalBlend;
    const float b = 1.0f - a;
    float px = a * (invN * sumPos.x) + body->ik_goal_pos.x * b;
    float py = (invN * sumPos.y) * a + body->ik_goal_pos.y * b;
    float pz = (invN * sumPos.z) * a + body->ik_goal_pos.z * b;
    float bx = b * body->ik_goal_orientation.x;
    float by = body->ik_goal_orientation.y * b;
    float bz = body->ik_goal_orientation.z * b;
    float bw = body->ik_goal_orientation.w * b;
    float rx = sumRot.x * a;
    float ry = sumRot.y * a;
    float rz = sumRot.z * a;
    float rw = sumRot.w * a;

    vector_4 q;
    if (0.0f <= ((rx * bx + rw * bw) + rz * bz) + ry * by)
    {
        q.x = rx + bx;
        q.y = ry + by;
        q.z = rz + bz;
        q.w = rw + bw;
    }
    else
    {
        q.x = rx - bx;
        q.y = ry - by;
        q.z = rz - bz;
        q.w = rw - bw;
    }
    vector_4 r = Normalize(q, 0);

    // Rotation change r * conj(old orientation).
    float ox = body->ik_goal_orientation.x;
    float oy = body->ik_goal_orientation.y;
    float oz = body->ik_goal_orientation.z;
    float ow = body->ik_goal_orientation.w;
    float dx = ((ow * r.x - ox * r.w) + oy * r.z) - oz * r.y;
    float dy = ((ow * r.y - ox * r.z) - oy * r.w) + oz * r.x;
    float dz = ((ox * r.y + ow * r.z) - oy * r.x) - oz * r.w;
    float dw = ((oz * r.z + oy * r.y) + ow * r.w) + ox * r.x;

    unsigned long n = body->static_data->num_children;
    if (n != 0)
    {
        float wx = dw * dx, wy = dw * dy, wz = dw * dz;
        float xy = dy * dx;
        float nxx = -(dx * dx);
        float xz = dz * dx;
        float nyy = -(dy * dy);
        float yz = dz * dy;
        float nzz = -(dz * dz);
        unsigned int off = 0;
        for (; n; --n, off += sizeof(creature_body_instance_data))
        {
            creature_body_instance_data* c = (creature_body_instance_data*)((char*)body->first_child + off);

            float vy = c->ik_particle_goal.y - body->ik_goal_pos.y;
            float vz = c->ik_particle_goal.z - body->ik_goal_pos.z;
            float vx = c->ik_particle_goal.x - body->ik_goal_pos.x;
            c->ik_particle_goal.x = ((((xy - wz) * vy + (xz + wy) * vz) + (nzz + nyy) * vx) * 2.0f + vx) + px;
            c->ik_particle_goal.y = ((((nzz + nxx) * vy + (yz - wx) * vz) + (xy + wz) * vx) * 2.0f + vy) + py;
            c->ik_particle_goal.z = ((((nyy + nxx) * vz + (yz + wx) * vy) + (xz - wy) * vx) * 2.0f + vz) + pz;

            float uy = c->ik_particle.y - body->ik_goal_pos.y;
            float uz = c->ik_particle.z - body->ik_goal_pos.z;
            float ux = c->ik_particle.x - body->ik_goal_pos.x;
            c->ik_particle.x = (((uz * (xz + wy) + uy * (xy - wz)) + ux * (nzz + nyy)) * 2.0f + ux) + px;
            c->ik_particle.y = (((uz * (yz - wx) + uy * (nzz + nxx)) + ux * (xy + wz)) * 2.0f + uy) + py;
            c->ik_particle.z = (((uy * (yz + wx) + uz * (nyy + nxx)) + ux * (xz - wy)) * 2.0f + uz) + pz;
        }
    }

    body->ik_goal_orientation = r;
    body->ik_goal_pos.x = px;
    body->ik_goal_pos.y = py;
    body->ik_goal_pos.z = pz;
    body->ik_particle.x = px;
    body->ik_particle.y = py;
    body->ik_particle.z = pz;
    body->ik_particle_goal.x = px;
    body->ik_particle_goal.y = py;
    body->ik_particle_goal.z = pz;
    body->ik_particle_goal_prev.x = px;
    body->ik_particle_goal_prev.y = py;
    body->ik_particle_goal_prev.z = pz;
}
} // namespace nSPCreatureAnim
