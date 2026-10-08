// Slice s009e7bb0 -- two helpers of the IK goal solver (nSPCreatureAnim::IKCreatureToGoals, 0x009f4660):
//   0x009e7bb0  `IKCreatureToGoals'::ik_utils::DelegateGoals: for every child body of `body` that carries
//               goals, merge its goal summary and accumulate the weighted goal position / orientation that
//               the child delegates upwards.
//   0x009e8210  IKComputeRootGoal: fold the extra goal of the root body into its goal, derive the root
//               goal position / orientation and reset the root's IK particle state.
// Layouts come from the sibling slice s009f4660 (same translation unit in the original).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <stddef.h>

namespace checkerlib
{
struct vector_3
{
    float x, y, z;
    vector_3() {}
    vector_3(const vector_3& o) : x(o.x), y(o.y), z(o.z) {}
    vector_3& operator=(const vector_3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct vector_4
{
    float x, y, z, w;
    vector_4() {}
    vector_4(const vector_4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
    vector_4& operator=(const vector_4& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
};

inline vector_3 make_v3(float x, float y, float z)
{
    vector_3 r;
    r.x = x; r.y = y; r.z = z;
    return r;
}
inline vector_3 operator+(const vector_3& a, const vector_3& b) { return make_v3(a.x + b.x, a.y + b.y, a.z + b.z); }

inline vector_4 QuaternionConjugate(const vector_4& q)
{
    vector_4 r;
    r.x = -q.x; r.y = -q.y; r.z = -q.z; r.w = q.w;
    return r;
}

// Hamilton product a*b (rotation b, then a).
inline vector_4 QuaternionProduct(const vector_4& a, const vector_4& b)
{
    vector_4 r;
    r.x = ((b.x * a.w + b.w * a.x) - a.z * b.y) + a.y * b.z;
    r.y = ((a.y * b.w + a.z * b.x) + b.y * a.w) - b.z * a.x;
    r.z = ((a.z * b.w - a.y * b.x) + b.z * a.w) + b.y * a.x;
    r.w = ((b.w * a.w - b.x * a.x) - a.y * b.y) - b.z * a.z;
    return r;
}

// a * conjugate(b): the rotation that takes b's orientation to a's.
inline void QuaternionRelative(vector_4& r, const vector_4& a0, const vector_4& b0)
{
    vector_4 a = a0;
    vector_4 b = b0;
    r.x = ((a.x * b.w - b.x * a.w) + b.y * a.z) - b.z * a.y;
    r.y = ((a.y * b.w - a.z * b.x) - b.y * a.w) + b.z * a.x;
    r.z = ((a.y * b.x + a.z * b.w) - b.y * a.x) - b.z * a.w;
    r.w = ((a.y * b.y + a.z * b.z) + a.x * b.x) + a.w * b.w;
}

vector_3 QuaternionVectorTransform(const vector_4& q, const vector_3& v);   // 0x0099c1a0 (rotate v by q)
vector_4 Normalize(const vector_4& q, float* pLength);                       // 0x0099cae0
}  // namespace checkerlib
using namespace checkerlib;

namespace nSPCreatureAnim
{
struct creature_instance_data;

// Goal summary of a body subtree: bits 0-2 = type (4 = no goals), bit 4 = own goal.
struct ik_goals_data
{
    unsigned char TypeAndFlags;  // +0x0
    unsigned char Reserved;      // +0x1
    unsigned char ChildIdx;      // +0x2
    unsigned char NumBIdx;       // +0x3

    ik_goals_data() : TypeAndFlags(4), Reserved(0), ChildIdx(0xff), NumBIdx(0xff) {}
    void MergeChild(ik_goals_data child, unsigned long childIdx);  // 0x009e67c0
};

struct goal_pos_rot                                   // size 0x24
{
    vector_3 pos;          // +0x00
    float    pos_weight;   // +0x0c
    vector_4 rot;          // +0x10
    float    rot_weight;   // +0x20
};

struct creature_body_static_data                      // retail layout (partial)
{
    uint32_t      pad_000[0x10c / 4];
    vector_3      rest_center__SCALABLE;           // +0x10c
    vector_4      rest_orientation_q;              // +0x118
    vector_4      joint_orientation_q;             // +0x128 (name guessed)
    uint32_t      pad_138[(0x208 - 0x138) / 4];
    unsigned long num_children;                    // +0x208
    uint32_t      pad_20c[(0x344 - 0x20c) / 4];
    vector_3      ik_joint_r__SCALABLE;            // +0x344 (name guessed)
    vector_3      parent_local_joint_r__SCALABLE;  // +0x350 (name guessed)
};

struct creature_body_instance_data                    // size 0x2bc (retail)
{
    creature_body_static_data*   static_data;                  // +0x000
    creature_instance_data*      creature;                     // +0x004
    creature_body_instance_data* parent;                       // +0x008
    creature_body_instance_data* first_child;                  // +0x00c
    uint32_t                     pad_010[(0x38 - 0x10) / 4];
    unsigned char                ik_goal_ready;                // +0x038 (name guessed)
    unsigned char                pad_039[0x58 - 0x39];
    goal_pos_rot                 goal;                         // +0x058
    goal_pos_rot                 goal_extra;                   // +0x07c (name guessed)
    uint32_t                     pad_0a0[(0x190 - 0xa0) / 4];
    vector_3                     ik_root_pos;                  // +0x190 (name guessed)
    vector_4                     ik_goal_orientation;          // +0x19c (name guessed)
    ik_goals_data                ik_goals;                     // +0x1ac
    vector_3                     ik_particle;                  // +0x1b0
    vector_3                     ik_particle_rest;             // +0x1bc
    vector_3                     ik_particle_goal;             // +0x1c8
    vector_3                     ik_particle_extra;            // +0x1d4 (name guessed)
    vector_3                     ik_delegate_pos;              // +0x1e0 (name guessed)
    vector_4                     ik_delegate_rot;              // +0x1ec (name guessed)
    uint32_t                     pad_1fc;
    vector_4                     ik_orientation_rest;          // +0x200
    float                        ik_invmass;                   // +0x210
    float                        ik_parent_length;             // +0x214
    uint32_t                     pad_218[(0x238 - 0x218) / 4];
    int                          ik_goal_mode;                 // +0x238 (name guessed)
    uint32_t                     pad_23c[(0x2bc - 0x23c) / 4];
};

struct creature_instance_data
{
    uint32_t pad_000[0x70 / 4];
    float    requested_scale;                                        // +0x070
};

typedef char AssertBodySize[sizeof(creature_body_instance_data) == 0x2bc ? 1 : -1];
typedef char AssertBodyGoalExtra[offsetof(creature_body_instance_data, goal_extra) == 0x7c ? 1 : -1];
typedef char AssertBodyFlag[offsetof(creature_body_instance_data, ik_goal_ready) == 0x38 ? 1 : -1];
typedef char AssertBodyRoot[offsetof(creature_body_instance_data, ik_root_pos) == 0x190 ? 1 : -1];
typedef char AssertBodyOrient[offsetof(creature_body_instance_data, ik_goal_orientation) == 0x19c ? 1 : -1];
typedef char AssertBodyDelegate[offsetof(creature_body_instance_data, ik_delegate_rot) == 0x1ec ? 1 : -1];
typedef char AssertBodyRest[offsetof(creature_body_instance_data, ik_orientation_rest) == 0x200 ? 1 : -1];
typedef char AssertBodyMode[offsetof(creature_body_instance_data, ik_goal_mode) == 0x238 ? 1 : -1];
typedef char AssertStaticQ2[offsetof(creature_body_static_data, joint_orientation_q) == 0x128 ? 1 : -1];
typedef char AssertStaticJoint[offsetof(creature_body_static_data, parent_local_joint_r__SCALABLE) == 0x350 ? 1 : -1];

// `IKCreatureToGoals'::ik_utils::DelegateGoals
// Child goal modes (ik_goal_mode): 0 = child keeps its own goal (only the summary is merged),
// 1 = blended goal (second goal in ik_delegate_pos/rot), 2 = anchored goal (ik_particle_goal/orientation),
// delegated up to this body.
// @ 0x009e7bb0
void ik_utils_DelegateGoals(creature_instance_data* creature, creature_body_instance_data* body,
                            int* numDelegated, int* numPos, int* numRot, vector_3* sumPos,
                            vector_4* sumRot, ik_goals_data* goals)
{
    unsigned long numChildren = body->static_data->num_children;
    for (unsigned long i = 0; i < numChildren; ++i)
    {
        creature_body_instance_data& child = body->first_child[i];
        if ((child.ik_goals.TypeAndFlags & 7) == 4)
            continue;

        ++*numRot;
        switch (child.ik_goal_mode)
        {
        case 0:
            goals->MergeChild(child.ik_goals, i);
            break;
        case 1:
        {
            ++*numPos;
            goals->MergeChild(child.ik_goals, i);
            vector_4 rot;
            QuaternionRelative(rot, child.ik_delegate_rot, child.static_data->joint_orientation_q);
            if (((sumRot->w * rot.w + sumRot->y * rot.y) + sumRot->z * rot.z) + sumRot->x * rot.x < 0.0f)
            {
                sumRot->x = sumRot->x - rot.x;
                sumRot->y = sumRot->y - rot.y;
                sumRot->z = sumRot->z - rot.z;
                sumRot->w = sumRot->w - rot.w;
            }
            else
            {
                sumRot->x = sumRot->x + rot.x;
                sumRot->y = sumRot->y + rot.y;
                sumRot->z = sumRot->z + rot.z;
                sumRot->w = sumRot->w + rot.w;
            }
            const float scale = creature->requested_scale;
            const creature_body_static_data* bs = body->static_data;
            const creature_body_static_data* cs = child.static_data;
            vector_3 link;
            link.x = scale * bs->ik_joint_r__SCALABLE.x - cs->parent_local_joint_r__SCALABLE.x * scale;
            link.y = bs->ik_joint_r__SCALABLE.y * scale - cs->parent_local_joint_r__SCALABLE.y * scale;
            link.z = bs->ik_joint_r__SCALABLE.z * scale - cs->parent_local_joint_r__SCALABLE.z * scale;
            const vector_3& t = QuaternionVectorTransform(rot, link);
            sumPos->x = sumPos->x + (t.x + child.ik_delegate_pos.x);
            sumPos->y = sumPos->y + (child.ik_delegate_pos.y + t.y);
            sumPos->z = (child.ik_delegate_pos.z + t.z) + sumPos->z;
            break;
        }
        case 2:
        {
            ++*numPos;
            ++*numDelegated;
            child.ik_goals.TypeAndFlags = 4;
            child.ik_goals.Reserved = 0;
            child.ik_goals.ChildIdx = 0xff;
            child.ik_goals.NumBIdx = 0xff;
            child.ik_invmass = -1.0f;
            vector_4 rot;
            QuaternionRelative(rot, child.ik_goal_orientation, child.static_data->joint_orientation_q);
            if (((sumRot->y * rot.y + sumRot->z * rot.z) + sumRot->w * rot.w) + sumRot->x * rot.x < 0.0f)
            {
                sumRot->x = sumRot->x - rot.x;
                sumRot->y = sumRot->y - rot.y;
                sumRot->z = sumRot->z - rot.z;
                sumRot->w = sumRot->w - rot.w;
            }
            else
            {
                sumRot->x = sumRot->x + rot.x;
                sumRot->y = sumRot->y + rot.y;
                sumRot->z = sumRot->z + rot.z;
                sumRot->w = sumRot->w + rot.w;
            }
            const float scale = creature->requested_scale;
            const creature_body_static_data* bs = body->static_data;
            const creature_body_static_data* cs = child.static_data;
            vector_3 link;
            link.x = scale * bs->ik_joint_r__SCALABLE.x - cs->parent_local_joint_r__SCALABLE.x * scale;
            link.y = bs->ik_joint_r__SCALABLE.y * scale - cs->parent_local_joint_r__SCALABLE.y * scale;
            link.z = bs->ik_joint_r__SCALABLE.z * scale - cs->parent_local_joint_r__SCALABLE.z * scale;
            const vector_3& t = QuaternionVectorTransform(rot, link);
            sumPos->x = sumPos->x + (child.ik_particle_goal.x + t.x);
            sumPos->y = sumPos->y + (child.ik_particle_goal.y + t.y);
            sumPos->z = (child.ik_particle_goal.z + t.z) + sumPos->z;
            break;
        }
        }
    }
}

// Smaller of two values, returned by reference (std::min semantics).
template <typename T> inline const T& min_ref(const T& a, const T& b) { return (b < a) ? b : a; }

// Folds the extra goal of the root body into its goal and derives the root goal position / orientation;
// rootRot receives the root orientation relative to the rest pose, rootPos the scaled rest centre.
// @ 0x009e8210
void IKComputeRootGoal(creature_instance_data* creature, creature_body_instance_data* root,
                       vector_4* rootRot, vector_3* rootPos)
{
    const float scale = creature->requested_scale;
    rootPos->x = root->static_data->rest_center__SCALABLE.x * scale;
    rootPos->y = root->static_data->rest_center__SCALABLE.y * scale;
    rootPos->z = root->static_data->rest_center__SCALABLE.z * scale;

    // goal += goal_extra (position + weight)
    root->goal.pos.x = root->goal.pos.x + root->goal_extra.pos.x;
    root->goal.pos.y = root->goal_extra.pos.y + root->goal.pos.y;
    root->goal.pos.z = root->goal_extra.pos.z + root->goal.pos.z;
    root->goal.pos_weight = root->goal_extra.pos_weight + root->goal.pos_weight;

    // goal.rot += +-goal_extra.rot (hemisphere aligned), weights add
    float dot = ((root->goal.rot.x * root->goal_extra.rot.x + root->goal.rot.y * root->goal_extra.rot.y)
                 + root->goal.rot.z * root->goal_extra.rot.z) + root->goal.rot.w * root->goal_extra.rot.w;
    if (dot < 0.0f)
    {
        root->goal.rot.x = root->goal.rot.x - root->goal_extra.rot.x;
        root->goal.rot.y = root->goal.rot.y - root->goal_extra.rot.y;
        root->goal.rot.z = root->goal.rot.z - root->goal_extra.rot.z;
        root->goal.rot.w = root->goal.rot.w - root->goal_extra.rot.w;
    }
    else
    {
        root->goal.rot.x = root->goal.rot.x + root->goal_extra.rot.x;
        root->goal.rot.y = root->goal.rot.y + root->goal_extra.rot.y;
        root->goal.rot.z = root->goal.rot.z + root->goal_extra.rot.z;
        root->goal.rot.w = root->goal.rot.w + root->goal_extra.rot.w;
    }
    root->goal.rot_weight = root->goal_extra.rot_weight + root->goal.rot_weight;

    // position: weighted average, blended with the rest centre while the weight is below 1
    if (root->goal.pos_weight > 0.0f)
    {
        float inv = 1.0f / root->goal.pos_weight;
        root->goal.pos.x = inv * root->goal.pos.x;
        root->goal.pos.y = inv * root->goal.pos.y;
        root->goal.pos.z = inv * root->goal.pos.z;
        float t = min_ref(root->goal.pos_weight, 1.0f);
        float s = 1.0f - t;
        root->ik_root_pos.x = root->goal.pos.x * t + rootPos->x * s;
        root->ik_root_pos.y = root->goal.pos.y * t + rootPos->y * s;
        root->ik_root_pos.z = root->goal.pos.z * t + rootPos->z * s;
        root->goal.pos_weight = 1.0f;
    }
    else
    {
        root->ik_root_pos = *rootPos;
    }

    // orientation: normalized goal, blended with the rest orientation while the weight is below 1
    if (root->goal.rot_weight > 0.0f)
    {
        root->goal.rot = Normalize(root->goal.rot, 0);
        if (root->goal.rot_weight >= 1.0f)
        {
            root->ik_goal_orientation = root->goal.rot;
            root->goal.rot_weight = 1.0f;
        }
        else
        {
            float t = min_ref(root->goal.rot_weight, 1.0f);
            float s = 1.0f - t;
            const vector_4& rest = root->static_data->rest_orientation_q;
            vector_4 a;
            a.x = root->goal.rot.x * t;
            a.y = root->goal.rot.y * t;
            a.z = root->goal.rot.z * t;
            a.w = root->goal.rot.w * t;
            vector_4 b;
            b.x = rest.x * s;
            b.y = rest.y * s;
            b.z = rest.z * s;
            b.w = rest.w * s;
            if (((a.x * b.x + a.y * b.y) + a.z * b.z) + a.w * b.w < 0.0f)
            {
                a.x = a.x - b.x; a.y = a.y - b.y; a.z = a.z - b.z; a.w = a.w - b.w;
            }
            else
            {
                a.x = a.x + b.x; a.y = a.y + b.y; a.z = a.z + b.z; a.w = a.w + b.w;
            }
            root->ik_goal_orientation = Normalize(a, 0);
            root->goal.rot_weight = 1.0f;
        }
    }
    else
    {
        root->ik_goal_orientation = root->static_data->rest_orientation_q;
    }

    root->ik_goal_ready = 1;
    QuaternionRelative(*rootRot, root->ik_goal_orientation, root->static_data->rest_orientation_q);
    root->ik_orientation_rest = root->ik_goal_orientation;
    root->ik_particle = root->ik_root_pos;
    root->ik_particle_rest = root->ik_root_pos;
    root->ik_particle_goal = root->ik_root_pos;
    root->ik_particle_extra = root->ik_root_pos;
    root->ik_invmass = 0.0f;
    root->ik_parent_length = 0.0f;
}

} // namespace nSPCreatureAnim
