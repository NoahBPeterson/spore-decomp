// Slice s009f16a0 -- recursive body-hierarchy traversal for the nSPCreatureAnim IK
// rig.  Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (ik_solver.obj, /GL-linked).
//
//   0x009f16a0  IKCtx::FollowBodyRig        thiscall (ECX = IKCtx*), con, ret 4
//   0x009f1730  IKCtx::ComputeBodyParticles thiscall (ECX = IKCtx*), con, ret 4
//
// Both walk the creature's Body hierarchy: a Body's static_data (+0x000) holds the
// child range (+0x204 first_child_bidx, +0x208 num_children) and a local translation
// (+0x350 local_pos); the Body itself carries a local position (+0x190) and rotation
// quaternion (+0x19c), the goal_mode at +0x1ac and the particle / particle_rest /
// particle_goal vectors at +0x1b0 / +0x1bc / +0x1c8.
typedef unsigned int   uint32;
typedef unsigned char  uint8;

struct Vec3 { float x, y, z; };

struct BodyStatic {
    uint8  pad000[0x150];
    uint32 flags;                 // +0x150
    uint8  pad154[0x204 - 0x154];
    uint32 first_child_bidx;      // +0x204
    uint32 num_children;          // +0x208
    uint8  pad20c[0x350 - 0x20c];
    Vec3   local_pos;             // +0x350
};

struct Body {                     // 700 bytes
    BodyStatic* static_data;      // +0x000
    uint8  pad004[0x190 - 4];
    Vec3   pos;                   // +0x190
    float  qx, qy, qz, qw;        // +0x19c
    uint8  goal_mode;             // +0x1ac (low 3 bits)
    uint8  pad1ad[0x1b0 - 0x1ad];
    Vec3   particle;              // +0x1b0
    Vec3   particle_rest;         // +0x1bc
    Vec3   particle_goal;         // +0x1c8
    uint8  pad1d4[700 - 0x1d4];
};

struct Creature {
    uint8  pad000[0x70];
    float  scale;                 // +0x070
    uint8  pad074[0x2e4 - 0x74];
    Body*  bodies;                // +0x2e4
};

struct IKCtx {
    Creature* creature;           // +0x000
    void ComputeBodyParticles(Body* node);   // 0x009f1730
    void FollowBodyRig(Body* node);          // 0x009f16a0
};

void __stdcall IKRigidFollow(IKCtx* ctx, Body* body);   // 0x009f09a0

// For each child body of `node`: unless it is a mode-4 terminator, run the rigid-follow
// solver when `node` is mode-1 and recurse into bodies flagged as having a sub-rig.
// @ 0x009f16a0
void IKCtx::FollowBodyRig(Body* node)
{
    uint32 count = node->static_data->num_children;
    if (count == 0)
        return;
    uint32 start = node->static_data->first_child_bidx;
    Body* bodies = creature->bodies;
    for (uint32 i = 0; i < count; ++i) {
        Body* body = &bodies[start + i];
        if ((body->goal_mode & 7) == 4)
            continue;
        if ((node->goal_mode & 7) == 1)
            IKRigidFollow(this, body);
        if (body->goal_mode & 1)
            FollowBodyRig(body);
    }
}

// For each child body of `node`: if it is a sub-rig (static flags bit 3) recurse; else
// compose the body's world particle position from the parent's local position/rotation
// and the body's scaled local offset, store it as both particle and particle_goal, then
// rigid-follow and descend.
// @ 0x009f1730
void IKCtx::ComputeBodyParticles(Body* node)
{
    uint32 count = node->static_data->num_children;
    if (count == 0)
        return;
    uint32 start = node->static_data->first_child_bidx;
    Body* bodies = creature->bodies;
    float scale = creature->scale;
    for (uint32 i = 0; i < count; ++i) {
        Body* body = &bodies[start + i];
        if ((body->goal_mode & 7) == 4)
            continue;
        BodyStatic* sd = body->static_data;
        if (sd->flags & 8) {
            ComputeBodyParticles(body);
            continue;
        }

        float qx = node->qx, qy = node->qy, qz = node->qz, qw = node->qw;
        float axs = sd->local_pos.x * scale;
        float ays = sd->local_pos.y * scale;
        float azs = sd->local_pos.z * scale;

        float nBx2 = -(qx * qx);
        float nBy2 = -(qy * qy);
        float nBz2 = -(qz * qz);

        // v' = C + 2*(qw*(qv x v) + qv x (qv x v)) + v,  v = local_pos*scale
        float rx = ((qz * qx + qy * qw) * azs + (qy * qx - qz * qw) * ays) +
                   (nBz2 + nBy2) * axs;
        float ry = ((nBz2 + nBx2) * ays + (qz * qy - qx * qw) * azs) +
                   (qy * qx + qz * qw) * axs;
        float rz = ((nBy2 + nBx2) * azs + (qz * qy + qx * qw) * ays) +
                   (qz * qx - qy * qw) * axs;

        float px = (2.0f * rx + axs) + node->pos.x;
        float py = node->pos.y + (2.0f * ry + ays);
        float pz = node->pos.z + (2.0f * rz + azs);

        body->particle_goal.x = px;
        body->particle_goal.y = py;
        body->particle_goal.z = pz;
        body->particle.x = px;
        body->particle.y = py;
        body->particle.z = pz;

        IKRigidFollow(this, body);
        FollowBodyRig(body);
    }
}
