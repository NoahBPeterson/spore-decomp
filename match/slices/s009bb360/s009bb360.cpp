// Slice s009bb360 -- nSPCreatureAnim::creature_instance_data wiggle trio:
//   0x009bb360 UpdateHitWiggles(this, int nSteps, float dt, float t, float rate)
//   0x009bb4f0 UpdateWiggles(this, float dt, float t)
//   0x009bb680 HitBody(this, unsigned long bidx, const vector_3& dir, uint32_t a3, bool a4, float a5)
//
// UpdateWiggles runs a metronome on the wiggle timer (this+0x1690): accumulate dt, clamp,
// convert the overflow into whole ticks; each tick drives the hit and root wiggle goal
// springs (UpdateGoalSpring, 0x009ba990) through UpdateHitWiggles. HitBody starts a hit
// wiggle on body bidx (CreateWiggle), re-inits both goal states, snaps every wiggle goal
// state to its body's animated world pose, and feeds the impact direction into the hit
// spring's velocity and the decay timers.
//
// Offsets follow slice s009ba4c0's retail stub (position +0x18, orientation +0x3c,
// Bodies +0x2e4); the wiggle block at +0x1670 is read off these three functions.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" double sqrt(double);
extern "C" double fmod(double, double);
#pragma intrinsic(sqrt)
#pragma intrinsic(fmod)

namespace checkerlib {
class vector_3 { public:
    float x, y, z;
    vector_3() {}
    vector_3(const vector_3& o) : x(o.x), y(o.y), z(o.z) {}
    vector_3& operator=(const vector_3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
class vector_4 { public: float x, y, z, w; };
}  // namespace checkerlib

using checkerlib::vector_3;
using checkerlib::vector_4;

namespace nSPCreatureAnim {

struct creature_static_data {
    uint32_t pad000[0x3f4 / 4];
    uint8_t  dead;                        // +0x3f4 (disables the wiggle springs)
    uint8_t  pad3f5[3];
};

struct goal_def {                         // only +0x00 is read here
    unsigned long bidx;                   // +0x00
};

struct goal_state {                       // size 0x2c
    goal_def* def;                        // +0x00
    bool      initialized;                // +0x04
    bool      reset;                      // +0x05
    uint8_t   pad06[2];
    vector_3  vel;                        // +0x08
    vector_3  pos;                        // +0x14
    vector_3  prev;                       // +0x20
};

struct creature_body_instance_data {      // size 0x2bc; only ->pos (+0x10) is read here
    uint32_t pad000[0x10 / 4];
    vector_3 pos;                         // +0x010
    uint32_t pad01c[(0x2bc - 0x1c) / 4];
};

struct body_vector {                      // eastl::vector<creature_body_instance_data>
    creature_body_instance_data* mpBegin;     // +0x2e4
    creature_body_instance_data* mpEnd;
    creature_body_instance_data* mpCapacity;
    uint32_t mAllocator;
};

struct creature_instance_data {
    creature_static_data* static_data;    // +0x000
    uint32_t pad004[(0x18 - 0x4) / 4];
    vector_3 position;                    // +0x018
    uint32_t pad024[(0x3c - 0x24) / 4];
    vector_4 orientation;                 // +0x03c
    uint32_t pad04c[(0x2e4 - 0x4c) / 4];
    body_vector Bodies;                   // +0x2e4
    uint32_t pad2f4[(0x168c - 0x2f4) / 4];
    uint8_t  pad168c[2];
    uint8_t  wiggles_enabled;             // +0x168e
    uint8_t  pad68f[1];
    float    wiggle_timer;                // +0x1690
    goal_state* states_begin;             // +0x1694
    goal_state* states_end;               // +0x1698
    uint32_t states_capacity;             // +0x169c
    uint32_t pad6a0[(0x16a8 - 0x16a0) / 4];
    float    hit_time;                    // +0x16a8
    float    root_time;                   // +0x16ac
    float    hold_time;                   // +0x16b0
    vector_3 hit_dir;                     // +0x16b4
    float    hit_len;                     // +0x16c0
    uint32_t hit_wiggle[0x3c / 4];        // +0x16c4 (opaque instance, CreateWiggle)
    goal_state hit_goal;                  // +0x1700
    uint32_t pad172c[(0x1768 - 0x172c) / 4];
    goal_state root_goal;                 // +0x1768

    void UpdateGoalSpring(goal_state* st, int nSteps, float dt, float t, float rate); // 0x009ba990
    void UpdateHitWiggles(int nSteps, float dt, float t, float rate);
    void UpdateWiggles(float dt, float t);
    void HitBody(unsigned long bidx, const vector_3& dir, uint32_t a3, bool a4, float a5);
};

extern float g_01550ab4;   // 0x01550ab4 wiggle timer clamp
extern float g_01550c30;   // 0x01550c30 wiggle tick interval
extern float g_0166c018;   // 0x0166c018 hit-wiggle fade window
extern float g_01550ad0;   // 0x01550ad0
extern float g_01550ac8;   // 0x01550ac8
extern float g_01550acc;   // 0x01550acc
extern float g_013ec4b8;   // 0x013ec4b8 (1e-8f)

extern "C" bool __cdecl CreateWiggle(creature_static_data* sd, unsigned long bidx, void* wiggle,
                                     int a4, uint32_t a5, int a6, int a7, int a8, int a9);   // 0x009ba4c0
extern "C" void FUN_009ba590(creature_static_data* sd, void* wiggle);                        // 0x009ba590
extern "C" void GoalStateInit(creature_instance_data* c, goal_state* st, int flag);          // 0x009ba7d0
extern "C" vector_3* QuaternionVectorTransform(vector_3* out, const vector_4* q, const vector_3* v); // 0x0099c1a0

// @ 0x009bb360
void creature_instance_data::UpdateHitWiggles(int nSteps, float dt, float t, float rate)
{
    float step = (float)nSteps * dt;
    if (hit_time > 0.0f) {
        if (step > 0.0f) {
            creature_static_data* sd = static_data;
            hit_time -= step;
            if (!sd->dead) {
                if (root_time > 0.0f) {
                    root_time -= step;
                } else {
                    root_time = 0.0f;
                    if (hold_time > 0.0f) {
                        hold_time -= step;
                        float k = hit_len / g_01550ad0 * g_01550ac8 * step;
                        vector_3 dv;
                        dv.x = hit_dir.x * k;
                        dv.y = hit_dir.y * k;
                        dv.z = hit_dir.z * k;
                        root_goal.vel.x += dv.x;
                        root_goal.vel.y += dv.y;
                        root_goal.vel.z += dv.z;
                    } else {
                        hold_time = 0.0f;
                    }
                }
            }
        }
        UpdateGoalSpring(&hit_goal, nSteps, dt, t, rate);
        if (!static_data->dead)
            UpdateGoalSpring(&root_goal, nSteps, dt, t, rate);
    } else {
        hit_time = 0.0f;
        hit_goal.initialized = 0;
        root_goal.initialized = 0;
    }
}

// @ 0x009bb4f0
void creature_instance_data::UpdateWiggles(float dt, float t)
{
    if (!wiggles_enabled) return;
    if (t == 0.0f) return;
    wiggle_timer += dt;
    const float& m = wiggle_timer > g_01550ab4 ? g_01550ab4 : wiggle_timer;
    float clamped = m;
    wiggle_timer = clamped;
    int count;
    float step;
    if (0.0f < dt) {
        if (g_01550c30 <= clamped) {
            step = g_01550c30;
            count = (int)(clamped / g_01550c30);
            wiggle_timer = (float)fmod((double)clamped, (double)g_01550c30);
        } else {
            step = clamped;
            count = 1;
            wiggle_timer = 0.0f;
        }
    } else {
        step = 0.0f;
        count = 0;
    }
    float weight = 1.0f;
    if (0.0f < hit_time && hit_time < g_0166c018)
        weight = 1.0f - (g_0166c018 - hit_time) / g_0166c018;
    UpdateHitWiggles(count, step, t, weight);
    if (static_data->dead) return;
    if (hit_time <= 0.0f) return;
    int n = (int)((char*)states_end - (char*)states_begin) / 0x2c;
    if (n != 0) {
        int left = n;
        unsigned int off = 0;
        do {
            UpdateGoalSpring((goal_state*)((char*)states_begin + off), count, step, t, weight);
            off += 0x2c;
        } while (--left);
    }
}

// @ 0x009bb680
void creature_instance_data::HitBody(unsigned long bidx, const vector_3& dir, uint32_t a3,
                                     bool a4, float a5)
{
    unsigned long b = bidx;
    int count = (int)((char*)Bodies.mpEnd - (char*)Bodies.mpBegin) / 0x2bc;
    if (b >= (unsigned long)count) return;
    if (a4 && hit_goal.initialized) {
        if (hit_goal.def->bidx != b) return;
    }
    if (!hit_goal.initialized) {
        if (CreateWiggle(static_data, b, &hit_wiggle, 1, a3, 0, 1, 0, 0)) {
            FUN_009ba590(static_data, &hit_wiggle);
            GoalStateInit(this, &hit_goal, 0);
            GoalStateInit(this, &root_goal, 0);
            int n = (int)((char*)states_end - (char*)states_begin) / 0x2c;
            if (n > 0) {
                int left = n;
                unsigned int off = 0;
                do {
                    goal_state* gs = (goal_state*)((char*)states_begin + off);
                    creature_body_instance_data* body =
                        &Bodies.mpBegin[gs->def->bidx];
                    vector_3 bodyPos = body->pos;
                    gs->vel.x = 0.0f;
                    gs->vel.y = 0.0f;
                    gs->vel.z = 0.0f;
                    vector_3 out;
                    vector_3* pr = QuaternionVectorTransform(&out, &orientation, &bodyPos);
                    gs->pos.x = position.x + pr->x;
                    gs->pos.y = pr->y + position.y;
                    gs->pos.z = pr->z + position.z;
                    gs->prev.x = gs->pos.x;
                    gs->prev.y = gs->pos.y;
                    gs->prev.z = gs->pos.z;
                    off += 0x2c;
                } while (--left);
            }
        }
    }
    hit_len = (float)sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    float scale = 1.0f
        / ((float)sqrt(dir.x * dir.x + (dir.y * dir.y + dir.z * dir.z)) + 1e-08f);
    vector_3 d;
    d.x = dir.x * scale;
    d.y = scale * dir.y;
    d.z = dir.z * scale;
    hit_dir = d;
    hit_goal.vel.x += dir.x;
    hit_goal.vel.y += dir.y;
    hit_goal.vel.z += dir.z;
    hit_time = a5;
    hold_time = g_01550ad0;
    root_time = g_01550acc;
}

}  // namespace nSPCreatureAnim
