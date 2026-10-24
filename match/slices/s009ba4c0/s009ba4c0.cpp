// Slice s009ba4c0 -- nSPCreatureAnim goal spring: integrate one body goal and accumulate it into the
// body's goal_pos_rot (0x009ba990, 2509 bytes).
//
// A goal state (one per animated goal) holds a damped spring particle that follows a target
// point attached to a body: the target is the body's own normalised goal (if it has position
// and rotation weight), else the body's rest pose (root goals), else the parent body's pose
// composed with the goal's local offset/rotation. The particle is stepped nSteps times
// (stiffness g_GoalSpringK, damping g_GoalSpringDamp, gravity on z), clamped to maxDist of the
// target (removing the outward velocity component), then the result is brought into creature
// space and blended into body.goal with weight (t - body.goal_time) * rate (or reset to
// t * rate), marking the body's goal bit in the creature.
//
// Type and field names follow slice s009f4660 (creature_body_instance_data, goal_pos_rot,
// creature_instance_data); goal_def / goal_state and the helper names are Claude-coined.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

namespace checkerlib {
class vector_3 { public:
    float x, y, z;
    vector_3& operator=(const vector_3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
class vector_4 { public: float x, y, z, w; };

// Rotates v by q (out of line in the binary, sret).
vector_3* QuaternionVectorTransform(vector_3* out, const vector_4* q, const vector_3* v);  // 0x0099c1a0

// Hamilton product a*b, in the binary's term order.
__forceinline vector_4 QuaternionProduct(const vector_4& a, const vector_4& b)
{
    vector_4 r;
    r.x = ((a.w * b.x + b.w * a.x) - a.z * b.y) + a.y * b.z;
    r.y = ((a.w * b.y + a.z * b.x) + a.y * b.w) - b.z * a.x;
    r.z = ((a.z * b.w - a.y * b.x) + a.w * b.z) + b.y * a.x;
    r.w = ((a.w * b.w - b.x * a.x) - a.y * b.y) - a.z * b.z;
    return r;
}

// Rotates v by the inverse of the unit quaternion q (inlined).
__forceinline vector_3 QuaternionVectorTransformInverse(const vector_4& q, const vector_3& v)
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
}  // namespace checkerlib

using namespace checkerlib;

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
    uint32_t pad_128[(0x150 - 0x128) / 4];
    uint32_t flags_150;                  // +0x150 (alternate flag word)
    uint32_t flags_154;                  // +0x154
    uint32_t pad_158[(0x1f8 - 0x158) / 4];
    unsigned long bidx;                  // +0x1f8 (body index in the creature)
    int      parent_bidx;                // +0x1fc (parent body index, -1: root)
};

struct creature_instance_data;

struct creature_body_instance_data {     // size 0x2bc
    creature_body_static_data* static_data;  // +0x000
    creature_instance_data*    creature;     // +0x004
    uint32_t pad_008[2];
    vector_3 pos;                            // +0x010
    vector_4 orientation;                    // +0x01c
    uint32_t pad_02c[(0x48 - 0x2c) / 4];
    float    goal_time;                      // +0x048
    uint32_t pad_04c;
    float    goal_blend;                     // +0x050
    uint32_t pad_054;
    goal_pos_rot goal;                       // +0x058
    uint32_t pad_07c[(0x2bc - 0x7c) / 4];
};

struct body_vector {                     // eastl::vector<creature_body_instance_data>
    creature_body_instance_data* mpBegin;
    creature_body_instance_data* mpEnd;
    creature_body_instance_data* mpCapacity;
    uint32_t mAllocator;
    unsigned long size() const { return (unsigned long)(mpEnd - mpBegin); }
};

struct creature_instance_data {
    uint32_t pad_000[0x18 / 4];
    vector_3 position;                   // +0x018
    uint32_t pad_024[(0x3c - 0x24) / 4];
    vector_4 orientation;                // +0x03c
    uint32_t pad_04c[(0x70 - 0x4c) / 4];
    float    requested_scale;            // +0x070
    uint32_t pad_074[(0x1b8 - 0x74) / 4];
    uint8_t  body_goal_bits[1];          // +0x1b8 (two bits per body)
    uint8_t  pad_1b9[0x2e4 - 0x1b9];
    body_vector Bodies;                  // +0x2e4

    void UpdateGoalSpring(struct goal_state* st, int nSteps, float dt, float t, float rate);
};

struct goal_def {
    unsigned long bidx;                  // +0x00
    int      parent_bidx;                // +0x04 (-1: root goal)
    uint32_t pad_08[2];
    float    max_dist;                   // +0x10 (in units of the creature scale)
    uint32_t pad_14[2];
    vector_3 offset;                     // +0x1c (in the parent body's frame)
    vector_4 rot;                        // +0x28 (relative to the parent body)
};

struct goal_state {
    goal_def* def;                       // +0x00
    bool      initialized;               // +0x04
    bool      reset;                     // +0x05
    uint8_t   pad_06[2];
    vector_3  vel;                       // +0x08
    vector_3  pos;                       // +0x14
    vector_3  prev;                      // +0x20
};

bool GoalStateIsActive(creature_instance_data* c, goal_state* st, float t);  // 0x009ba8d0 (cdecl)
void GoalStateInit(creature_instance_data* c, goal_state* st, char flag);      // 0x009ba7d0 (cdecl)

extern float g_GoalSpringMaxDist;        // 0x01550ab8 (1.0)
extern float g_GoalSpringK;              // 0x01550abc (100.0)
extern float g_GoalSpringDamp;           // 0x01550ac0 (8.0)
extern float g_GoalGravity;              // 0x0166c010
extern int   g_GoalClampAboveGround;     // 0x0166c014
extern const float kGoalMaxDistScale;    // 0x013ec434 (0.4)
extern const float kOne;                 // 0x01485720
extern const float kZero;                // 0x01485378
extern const float kMinSpeed2;           // 0x013ebca0 (1e-4)
extern char  g_GoalUseAltFlags;          // 0x01550c2c (use flags_150 instead of flags_154)

static __forceinline void MarkBodyGoal(creature_body_instance_data* body)
{
    unsigned long bit = body->static_data->bidx * 2;
    body->creature->body_goal_bits[bit >> 3] |= (uint8_t)(1 << (bit & 7));
}

// ---------------------------------------------------------------------------
// Wiggle (secondary animation) support.  The animation object owns a vector of
// 0x468-byte per-body records whose rest pose sits at the same offsets as
// creature_body_static_data; a wiggle names two of those records and stores the
// relative transform that the runtime blends on top of the normal animation.
// ---------------------------------------------------------------------------
struct anim_body_data {                    // stride 0x468
    uint32_t pad_000[0x10c / 4];
    vector_3 rest_center__SCALABLE;        // +0x10c
    vector_4 rest_orientation_q;           // +0x118
    uint32_t pad_128[(0x468 - 0x128) / 4];
};

struct creature_anim {                     // nSPCreatureAnim data
    uint32_t        pad_000[0x384 / 4];
    anim_body_data* anim_bodies_begin;     // +0x384
    anim_body_data* anim_bodies_end;       // +0x388
};

struct wiggle_data {                       // size 0x39 (padded to 0x3c)
    int      body_a;                       // +0x00
    int      body_b;                       // +0x04
    int      body_c;                       // +0x08
    int      body_d;                       // +0x0c
    float    weight;                       // +0x10
    float    length;                       // +0x14
    float    angle;                        // +0x18
    vector_3 pos;                          // +0x1c
    vector_4 rot;                          // +0x28
    uint8_t  flag_038;                     // +0x38
    void CopyFrom(const wiggle_data* w);   // 0x009b3ab0 (0x39-byte copy)
};

bool CalcWiggle(creature_anim* anim, anim_body_data* body, wiggle_data* w,
                int a4, int a5, int a6, int a7, int a8, int a9);   // 0x009ba180

// @ 0x009ba4c0
bool CreateWiggle(creature_anim* anim, unsigned index, wiggle_data* out,
                  int a4, int a5, int a6, int a7, int a8, int a9)
{
    if (index < (unsigned)(anim->anim_bodies_end - anim->anim_bodies_begin)) {
        wiggle_data w;
        w.pos.x = w.pos.y = w.pos.z = 0.0f;
        w.rot.x = w.rot.y = w.rot.z = 0.0f;
        w.rot.w = 1.0f;
        anim_body_data* body = &anim->anim_bodies_begin[index];
        if (CalcWiggle(anim, body, &w, a4, a5, a6, a7, a8, a9)) {
            out->CopyFrom(&w);
            return true;
        }
        out->body_a = -1;
        out->body_b = -1;
        out->body_c = -1;
    }
    return false;
}

// @ 0x009ba590
void ComputeWiggle(creature_anim* anim, wiggle_data* w)
{
    if (w->body_a == -1 || w->body_b == -1)
        return;

    anim_body_data* a = &anim->anim_bodies_begin[w->body_a];
    anim_body_data* b = &anim->anim_bodies_begin[w->body_b];

    vector_3 delta;
    delta.x = a->rest_center__SCALABLE.x - b->rest_center__SCALABLE.x;
    delta.y = a->rest_center__SCALABLE.y - b->rest_center__SCALABLE.y;
    delta.z = a->rest_center__SCALABLE.z - b->rest_center__SCALABLE.z;

    vector_4 conj_b;
    conj_b.x = -b->rest_orientation_q.x;
    conj_b.y = -b->rest_orientation_q.y;
    conj_b.z = -b->rest_orientation_q.z;
    conj_b.w = b->rest_orientation_q.w;

    vector_4 rot_a = a->rest_orientation_q;

    vector_3 v;
    QuaternionVectorTransform(&v, &conj_b, &delta);
    w->pos = v;

    vector_4 q;
    q.x = ((conj_b.w * rot_a.x + rot_a.w * conj_b.x) - rot_a.y * conj_b.z)
        + rot_a.z * conj_b.y;
    q.y = ((conj_b.w * rot_a.y + conj_b.z * rot_a.x) + conj_b.y * rot_a.w)
        - rot_a.z * conj_b.x;
    q.z = ((conj_b.z * rot_a.w - conj_b.y * rot_a.x) + conj_b.w * rot_a.z)
        + rot_a.y * conj_b.x;
    q.w = ((conj_b.w * rot_a.w - rot_a.x * conj_b.x) - conj_b.y * rot_a.y)
        - conj_b.z * rot_a.z;
    w->rot = q;
}

// @ 0x009ba7d0
void GoalStateInit(creature_instance_data* c, goal_state* st, char flag)
{
    creature_body_instance_data* body = &c->Bodies.mpBegin[st->def->bidx];

    vector_3 local;
    const vector_3* src;
    if (flag != 0) {
        float s = c->requested_scale;
        const vector_3& rc = body->static_data->rest_center__SCALABLE;
        local.x = rc.x * s;
        local.y = rc.y * s;
        local.z = rc.z * s;
        src = &local;
    } else {
        src = &body->pos;
    }

    vector_3 v;
    v.x = src->x;
    v.y = src->y;
    v.z = src->z;

    st->vel.x = 0.0f;
    st->vel.y = 0.0f;
    st->vel.z = 0.0f;

    vector_3* r = QuaternionVectorTransform(&local, &c->orientation, &v);

    st->pos.x = r->x + c->position.x;
    st->pos.y = r->y + c->position.y;
    st->pos.z = r->z + c->position.z;
    st->prev = st->pos;
}

// @ 0x009ba8d0
bool GoalStateIsActive(creature_instance_data* c, goal_state* st, float t)
{
    goal_def* def = st->def;
    unsigned bidx = def->bidx;
    creature_body_instance_data* body = &c->Bodies.mpBegin[(int)bidx];

    if (!st->reset) {
        if (body->goal_time >= t)
            return false;
        if ((body->static_data->flags_154 >> 2) & 1)
            return false;
    }

    int parent = def->parent_bidx;
    if (parent == -1)
        return true;
    if ((int)bidx == -1)
        return true;
    if ((int)bidx == parent)
        return true;

    for (;;) {
        uint32_t flags = g_GoalUseAltFlags ? body->static_data->flags_150
                                           : body->static_data->flags_154;
        if ((flags >> 3) & 1)
            return true;
        if (body->goal_blend > 0.0f)
            return false;
        if (body->goal_time > 0.0f && !st->reset)
            return false;
        bidx = (unsigned)body->static_data->parent_bidx;
        body = &c->Bodies.mpBegin[(int)bidx];
        if ((int)bidx == -1)
            return true;
    }
}

// @ 0x009ba990
void creature_instance_data::UpdateGoalSpring(goal_state* st, int nSteps, float dt, float t, float rate)
{
    goal_def* def = st->def;
    if (def->bidx >= Bodies.size())
        return;
    creature_body_instance_data* bodies = Bodies.mpBegin;
    creature_body_instance_data* body = &bodies[def->bidx];
    if (!GoalStateIsActive(this, st, t)) {
        st->initialized = false;
        return;
    }

    vector_3 lpos;
    vector_4 lrot;
    if (body->goal.pos_weight > 0.0f && body->goal.rot_weight > 0.0f) {
        float inv = kOne / body->goal.pos_weight;
        float px = body->goal.pos.x * inv;
        float py = body->goal.pos.y * inv;
        float pz = body->goal.pos.z * inv;
        inv = kOne / body->goal.rot_weight;
        float rx = body->goal.rot.x * inv;
        float ry = body->goal.rot.y * inv;
        float rz = body->goal.rot.z * inv;
        float rw = body->goal.rot.w * inv;
        lpos.x = px; lpos.y = py; lpos.z = pz;
        lrot.x = rx; lrot.y = ry; lrot.z = rz; lrot.w = rw;
    } else if (def->parent_bidx == -1) {
        creature_body_static_data* sd = body->static_data;
        float s = requested_scale;
        float px = sd->rest_center__SCALABLE.x * s;
        float py = sd->rest_center__SCALABLE.y * s;
        float pz = sd->rest_center__SCALABLE.z * s;
        lrot = sd->rest_orientation_q;
        lpos.x = px; lpos.y = py; lpos.z = pz;
    } else {
        creature_body_instance_data* parent = &bodies[def->parent_bidx];
        vector_3 tmp;
        vector_3* r = QuaternionVectorTransform(&tmp, &parent->orientation, &def->offset);
        float s = requested_scale;
        lpos.x = parent->pos.x + r->x * s;
        lpos.y = parent->pos.y + r->y * s;
        lpos.z = parent->pos.z + r->z * s;
        lrot = QuaternionProduct(parent->orientation, def->rot);
    }

    vector_3 target;
    {
        vector_3 tmp;
        vector_3* r = QuaternionVectorTransform(&tmp, &orientation, &lpos);
        target.x = position.x + r->x;
        target.y = position.y + r->y;
        target.z = position.z + r->z;
    }

    if (!st->initialized) {
        GoalStateInit(this, st, 1);
        st->initialized = true;
    }

    float maxDist;
    if (st->def->parent_bidx == -1)
        maxDist = g_GoalSpringMaxDist;
    else
        maxDist = (st->def->max_dist * requested_scale) * kGoalMaxDistScale;

    vector_3 p;
    p.x = st->pos.x;
    p.y = st->pos.y;
    p.z = st->pos.z;
    if (nSteps > 0) {
        float maxDist2 = maxDist * maxDist;
        do {
            float ax = (target.x - st->pos.x) * g_GoalSpringK - st->vel.x * g_GoalSpringDamp;
            float az = ((target.z - st->pos.z) * g_GoalSpringK - st->vel.z * g_GoalSpringDamp) + g_GoalGravity;
            float ay = (target.y - st->pos.y) * g_GoalSpringK - st->vel.y * g_GoalSpringDamp;
            float vx = st->vel.x + ax * dt;
            float vz = st->vel.z + az * dt;
            st->vel.y = ay * dt + st->vel.y;
            st->vel.z = vz;
            st->vel.x = vx;
            p.x = st->vel.x * dt + st->pos.x;
            p.y = st->pos.y + st->vel.y * dt;
            p.z = st->pos.z + st->vel.z * dt;
            float dx = p.x - target.x;
            float dy = p.y - target.y;
            float dz = p.z - target.z;
            float l2 = (dx * dx + dy * dy) + dz * dz;
            if (l2 > maxDist2) {
                float inv = 1.0f / sqrtf(l2);
                float nz = dz * inv;
                float ny = dy * inv;
                float nx = inv * dx;
                p.z = nz * maxDist + target.z;
                p.x = nx * maxDist + target.x;
                p.y = ny * maxDist + target.y;
                float v2 = (st->vel.x * st->vel.x + st->vel.y * st->vel.y) + st->vel.z * st->vel.z;
                float dot = (st->vel.z * nz + st->vel.y * ny) + st->vel.x * nx;
                if (v2 > kMinSpeed2 && dot > kZero) {
                    float f = dot / sqrtf(v2);
                    float fx = f * st->vel.x;
                    float fy = st->vel.y * f;
                    float fz = st->vel.z * f;
                    st->vel.y = st->vel.y - fy;
                    st->vel.x = st->vel.x - fx;
                    st->vel.z = st->vel.z - fz;
                }
            }
            st->prev = st->pos;
            st->pos.x = p.x;
            st->pos.y = p.y;
            st->pos.z = p.z;
        } while (--nSteps);
    }

    vector_3 d;
    d.x = p.x - position.x;
    d.y = p.y - position.y;
    d.z = p.z - position.z;
    vector_3 g = QuaternionVectorTransformInverse(orientation, d);
    if (g_GoalClampAboveGround != 0 && 0.0f > g.z)
        g.z = 0.0f;

    if (!(t > body->goal_time) && !st->reset)
        return;
    if (st->reset) {
        body->goal_blend = t * rate;
        body->goal_time = 0.0f;
        if (body->goal_blend > 0.0f) {
            float w = body->goal_blend;
            body->goal.pos.x = w * g.x;
            body->goal.pos.y = w * g.y;
            body->goal.pos.z = w * g.z;
            body->goal.pos_weight = body->goal_blend;
            w = body->goal_blend;
            body->goal.rot.x = w * lrot.x;
            body->goal.rot.y = w * lrot.y;
            body->goal.rot.z = w * lrot.z;
            body->goal.rot.w = w * lrot.w;
            body->goal.rot_weight = body->goal_blend;
            MarkBodyGoal(body);
        }
        return;
    }
    float w = (t - body->goal_time) * rate + body->goal_blend;
    body->goal_blend = w;
    if (w > 0.0f) {
        if (t > body->goal.pos_weight) {
            body->goal.pos.x = w * g.x + body->goal.pos.x;
            body->goal.pos.z = w * g.z + body->goal.pos.z;
            body->goal.pos.y = body->goal.pos.y + w * g.y;
            body->goal.pos_weight = body->goal.pos_weight + body->goal_blend;
            MarkBodyGoal(body);
        }
        if (t > body->goal.rot_weight) {
            float b = body->goal_blend;
            body->goal.rot.x = body->goal.rot.x + b * lrot.x;
            body->goal.rot.y = b * lrot.y + body->goal.rot.y;
            body->goal.rot.z = b * lrot.z + body->goal.rot.z;
            body->goal.rot.w = b * lrot.w + body->goal.rot.w;
            body->goal.rot_weight = body->goal.rot_weight + body->goal_blend;
            MarkBodyGoal(body);
        }
    }
}

}  // namespace nSPCreatureAnim
