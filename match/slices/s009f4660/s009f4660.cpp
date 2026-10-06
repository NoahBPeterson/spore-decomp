// Slice s009f4660 -- nSPCreatureAnim::IKCreatureToGoals (0x009f4660, 21728 bytes).
//
// The retail IK goal solver for one creature (ik_solver.cpp). It runs in four passes:
//   A. bodies, leaf to root: clear the IK state, merge the goal summaries of the children,
//      compute the rest particle and the goal particle/orientation of every body;
//   B. bodies, root to leaf: rebuild creature.ik_constraints (parent links, spine chains,
//      goal and rest constraints, cross constraints);
//   C. constraints: link the multi-branch lists and the spine begin/end pointers;
//   D. spine constraints: fit a quintic Hermite spine curve through the rest joints (or
//      slerp a frame along the chord for short spines) and store every spine body's
//      position/orientation relative to that curve.
//
// The retail build is newer than the 2008 dev PDB (quaternions instead of matrices,
// a second root-orientation argument, bigger structs), so the layouts below come from
// the disassembly; member names follow the dev PDB where the order lines up, and the
// ones marked "(name guessed)" are not confirmed.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <stdio.h>
#include <new>

namespace eastl
{
struct sp_vector_allocator { int mFlags; };

// Minimal EASTL vector: just the members this function uses.
template <typename T, typename Allocator = sp_vector_allocator>
class vector
{
public:
    typedef unsigned int size_type;

    T*        mpBegin;
    T*        mpEnd;
    T*        mpCapacity;
    Allocator mAllocator;

    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    T& operator[](size_type n) { return *(mpBegin + n); }
    T& back() { return *(mpEnd - 1); }

    void resize(size_type n);                            // 0x009c2ef0 (ik_constraint)

    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }

protected:
    void DoInsertValue(T* position, const T& value);     // 0x009f3e20 (ik_constraint)
};
} // namespace eastl

namespace checkerlib
{
class vector_3
{
public:
    float x, y, z;
};

class vector_4
{
public:
    float x, y, z, w;
};

class matrix_3x3
{
public:
    float el[9];

    void InitIdentity()
    {
        el[1] = 0.0f; el[2] = 0.0f; el[3] = 0.0f;
        el[5] = 0.0f; el[6] = 0.0f; el[7] = 0.0f;
        el[8] = 1.0f; el[4] = 1.0f; el[0] = 1.0f;
    }
    void ConcatenateYRotation(float radians);            // 0x009e5f50
};

class matrix_4x4
{
public:
    float el[16];

    float& operator()(int r, int c) { return el[r * 4 + c]; }
    void InitZero()
    {
        for (int i = 0; i < 16; ++i)
            el[i] = 0.0f;
    }
};

inline vector_3 make_v3(float x, float y, float z)
{
    vector_3 r;
    r.x = x; r.y = y; r.z = z;
    return r;
}
inline vector_3 operator+(const vector_3& a, const vector_3& b) { return make_v3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline vector_3 operator-(const vector_3& a, const vector_3& b) { return make_v3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline vector_3 operator*(const vector_3& a, float s) { return make_v3(a.x * s, a.y * s, a.z * s); }
inline vector_3 operator*(float s, const vector_3& a) { return make_v3(s * a.x, s * a.y, s * a.z); }

inline float DotProduct(const vector_3& a, const vector_3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline float Length2(const vector_3& a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
inline float Length(const vector_3& a) { return (float)sqrt((double)a.x * a.x + (double)a.y * a.y + (double)a.z * a.z); }
inline vector_3 CrossProduct(const vector_3& a, const vector_3& b)
{
    return make_v3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

// Normalize with an exact zero test (zero vectors stay zero).
inline vector_3 Normalize(const vector_3& v)
{
    vector_3 r = v;
    float len = Length(v);
    if (len != 0.0f)
    {
        float inv = 1.0f / len;
        r.x = inv * v.x;
        r.y = inv * v.y;
        r.z = inv * v.z;
    }
    return r;
}

// Normalize with a 1e-8 bias in the length (never divides by zero).
inline vector_3 NormalizeSafe(const vector_3& v)
{
    float inv = (float)(1.0 / (sqrt((double)v.x * v.x + (double)v.y * v.y + (double)v.z * v.z) + 1e-8f));
    return make_v3(v.x * inv, v.y * inv, v.z * inv);
}

inline float DotProduct(const vector_4& a, const vector_4& b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

inline vector_4 Normalize(const vector_4& q, float* pLength)    // 0x0099cae0
{
    float x = q.x, y = q.y, z = q.z, w = q.w;
    float len = (float)sqrt((double)w * w + (double)x * x + (double)y * y + (double)z * z);
    if (pLength)
        *pLength = len;
    if (len != 0.0f)
    {
        float inv = 1.0f / len;
        x = inv * x;
        y = inv * y;
        z = inv * z;
        w = w * inv;
    }
    vector_4 r;
    r.x = x; r.y = y; r.z = z; r.w = w;
    return r;
}

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

// Rotates v by the unit quaternion q.                          (out of line: 0x0099c1a0)
inline vector_3 QuaternionVectorTransform(const vector_4& q, const vector_3& v)
{
    vector_3 r;
    r.x = (((-(q.z * q.z) + -(q.y * q.y)) * v.x + (q.z * q.x + q.y * q.w) * v.z) + (q.y * q.x - q.z * q.w) * v.y) * 2.0f + v.x;
    r.y = (((q.y * q.x + q.z * q.w) * v.x + (q.z * q.y - q.x * q.w) * v.z) + (-(q.z * q.z) + -(q.x * q.x)) * v.y) * 2.0f + v.y;
    r.z = (((q.z * q.x - q.y * q.w) * v.x + (-(q.y * q.y) + -(q.x * q.x)) * v.z) + (q.z * q.y + q.x * q.w) * v.y) * 2.0f + v.z;
    return r;
}

// Rotates v by the inverse of the unit quaternion q.           (out of line: 0x0099c310)
inline vector_3 QuaternionVectorTransformInverse(const vector_4& q, const vector_3& v)
{
    return QuaternionVectorTransform(QuaternionConjugate(q), v);
}

vector_4   matrix_to_quaternion(const matrix_3x3& m);                                  // 0x009a4f10
matrix_3x3 RotationAtoB(const vector_3& a, const vector_3& b, float* pCos,
                        const matrix_3x3* pFallback);                                  // 0x009edb70
bool       LinearSolveInPlace(matrix_4x4& a, vector_4* b, int numRhs);                  // 0x009e6040

// Orthonormal frame with the given column vectors: [n | t | n x t].
inline matrix_3x3 FrameFromNormalTangent(const vector_3& n, const vector_3& t)
{
    matrix_3x3 m;
    m.el[0] = n.x; m.el[1] = t.x; m.el[2] = n.y * t.z - n.z * t.y;
    m.el[3] = n.y; m.el[4] = t.y; m.el[5] = n.z * t.x - t.z * n.x;
    m.el[6] = n.z; m.el[7] = t.z; m.el[8] = t.y * n.x - n.y * t.x;
    return m;
}
} // namespace checkerlib

using namespace checkerlib;

namespace nSPCreatureAnim
{
struct creature_instance_data;
struct creature_body_instance_data;

struct goal_pos_rot                                   // size 0x24
{
    vector_3 pos;          // +0x00
    float    pos_weight;   // +0x0c
    vector_4 rot;          // +0x10
    float    rot_weight;   // +0x20
};

// Goal summary of a body subtree: bits 0-2 = type (4 = no goals), bit 4 = own goal.
struct ik_goals_data                                  // size 0x4
{
    unsigned char TypeAndFlags;  // +0x0
    unsigned char Reserved;      // +0x1
    unsigned char ChildIdx;      // +0x2
    unsigned char NumBIdx;       // +0x3

    ik_goals_data() : TypeAndFlags(4), Reserved(0), ChildIdx(0xff), NumBIdx(0xff) {}

    void MergeThisBIdx(unsigned char bidx)            // 0x009e6750
    {
        unsigned char f = TypeAndFlags;
        switch (f & 7)
        {
        case 1:
            ++NumBIdx;
            TypeAndFlags = f | 0x10;
            break;
        case 2:
            TypeAndFlags = (f & 0xf9) | 0x11;
            NumBIdx = 2;
            ChildIdx = 0xff;
            break;
        case 3:
            ++NumBIdx;
            TypeAndFlags = (f & 0xf9) | 0x11;
            ChildIdx = 0xff;
            break;
        case 4:
            TypeAndFlags = 0x10;
            NumBIdx = bidx;
            ChildIdx = 0xff;
            break;
        }
    }
    void MergeChild(ik_goals_data child, unsigned long childIdx);  // 0x009e67c0
};

struct creature_body_static_data                      // retail layout (partial)
{
    uint32_t      pad_000[0x10c / 4];
    vector_3      rest_center__SCALABLE;           // +0x10c
    vector_4      rest_orientation_q;              // +0x118
    uint32_t      pad_128[(0x144 - 0x128) / 4];
    vector_3      local_joint_r__SCALABLE;         // +0x144 (name guessed)
    unsigned long caps_flags;                      // +0x150 (2 = ?, 8 = spine root / anchor)
    uint32_t      pad_154[(0x204 - 0x154) / 4];
    unsigned long first_child_bidx;                // +0x204
    unsigned long num_children;                    // +0x208
    uint32_t      pad_20c[(0x344 - 0x20c) / 4];
    vector_3      ik_joint_r__SCALABLE;            // +0x344 (name guessed)
    vector_3      parent_local_joint_r__SCALABLE;  // +0x350 (name guessed)
};

struct ik_constraint;

struct creature_body_instance_data                    // size 0x2bc (retail)
{
    creature_body_static_data*   static_data;                  // +0x000
    creature_instance_data*      creature;                     // +0x004
    creature_body_instance_data* parent;                       // +0x008
    creature_body_instance_data* first_child;                  // +0x00c
    uint32_t                     pad_010[(0x58 - 0x10) / 4];
    goal_pos_rot                 goal;                         // +0x058
    goal_pos_rot                 goal_extra;                   // +0x07c (name guessed)
    uint32_t                     pad_0a0[(0x18c - 0xa0) / 4];
    int                          ik_state;                     // +0x18c (name guessed)
    uint32_t                     pad_190[(0x19c - 0x190) / 4];
    vector_4                     ik_goal_orientation;          // +0x19c (name guessed)
    ik_goals_data                ik_goals;                     // +0x1ac
    vector_3                     ik_particle;                  // +0x1b0
    vector_3                     ik_particle_rest;             // +0x1bc
    vector_3                     ik_particle_goal;             // +0x1c8
    uint32_t                     pad_1d4[(0x1fc - 0x1d4) / 4];
    bool                         ik_limb_aimed;                // +0x1fc
    bool                         ik_limb_straight;             // +0x1fd (name guessed)
    unsigned char                pad_1fe[2];
    vector_4                     ik_orientation_rest;          // +0x200
    float                        ik_invmass;                   // +0x210
    float                        ik_parent_length;             // +0x214
    vector_3                     ik_parent_r_rest;             // +0x218
    unsigned long                ik_num_active_children;       // +0x224
    unsigned long                ik_goal_to_spine_num;         // +0x228
    unsigned long                ik_constraint_idx;            // +0x22c
    unsigned long                ik_constraint_num;            // +0x230
    bool                         ik_in_constraint;             // +0x234
    bool                         ik_in_spine;                  // +0x235
    unsigned char                pad_236[2];
    int                          ik_goal_mode;                 // +0x238 (name guessed)
    float                        ik_inherit_goals;             // +0x23c
    ik_constraint*               ik_own_spine_constraint;      // +0x240
    ik_constraint*               ik_end_spine_constraint;      // +0x244
    vector_3                     ik_spine_spline_secant_tangent_rest; // +0x248
    float                        ik_spine_t;                   // +0x254
    vector_3                     ik_spine_local_pos;           // +0x258
    vector_3                     ik_spine_pos;                 // +0x264
    vector_4                     ik_spine_local_rot;           // +0x270
    uint32_t                     pad_280[(0x2bc - 0x280) / 4];
};

struct ik_spine_spline_end                            // size 0x30 (name guessed)
{
    vector_3 coef0;     // +0x00  hermite coefficient (first derivative), body-local
    vector_3 coef1;     // +0x0c  hermite coefficient (second derivative), body-local
    vector_3 tangent;   // +0x18  body-local
    vector_3 normal;    // +0x24  body-local
};

struct ik_constraint                                  // size 0x10c (retail)
{
    creature_body_instance_data* b_i;               // +0x00
    creature_body_instance_data* b_j;               // +0x04
    vector_3*                    p_i;               // +0x08
    vector_3*                    p_j;               // +0x0c
    float                        rest_length;       // +0x10
    float                        invmass_i;         // +0x14
    float                        invmass_j;         // +0x18
    ik_spine_spline_end          spine_spline_i;    // +0x1c
    ik_spine_spline_end          spine_spline_j;    // +0x4c
    vector_3                     chord;             // +0x7c
    float                        inv_chord_length;  // +0x88
    float                        rest_invmass_i;    // +0x8c (name guessed)
    float                        rest_invmass_j;    // +0x90 (name guessed)
    unsigned long                Flags;             // +0x94
    float                        soft[12];          // +0x98
    float                        spine_chord_rest_length; // +0xc8
    int                          spine_count;       // +0xcc
    ik_constraint*               multi_branch_base_start; // +0xd0
    ik_constraint*               multi_branch_child_next; // +0xd4
    uint32_t                     altitude[12];      // +0xd8
    int                          num_altitudes;     // +0x108

    ik_constraint(creature_body_instance_data* bi, creature_body_instance_data* bj,
                  float restLength, unsigned long flags);                       // 0x009e68f0
    ik_constraint(creature_body_instance_data* bi, vector_3* pi, float invmassI,
                  creature_body_instance_data* bj, vector_3* pj, float invmassJ,
                  float restLength, unsigned long flags);                       // 0x009e6a20
    ik_constraint(const ik_constraint& other);                                  // 0x009be850
    void SetSoft(float sMin, float sMax, float deltaMin, float deltaMax);       // 0x009e6b40
};

struct creature_instance_data                         // retail layout (partial)
{
    uint32_t pad_000[0x70 / 4];
    float    requested_scale;                                        // +0x070
    uint32_t pad_074[(0x1b0 - 0x74) / 4];
    float    ik_spine_rest_alpha;                                    // +0x1b0
    uint32_t pad_1b4[(0x238 - 0x1b4) / 4];
    vector_4 ik_root_orientation;                                    // +0x238 (name guessed)
    float    ik_root_scale;                                          // +0x248 (name guessed)
    eastl::vector<ik_constraint, eastl::sp_vector_allocator> ik_constraints; // +0x24c
    uint32_t pad_25c[(0x2e4 - 0x25c) / 4];
    eastl::vector<creature_body_instance_data, eastl::sp_vector_allocator> Bodies; // +0x2e4
};

// --- tunables / debug switches (.data) ---
extern float                   g_IKSpineCollinearTolerance;  // 0x01550a0c (0.01)
extern float                   g_IKSpineSoftDeltaMin;        // 0x01550a10 (0.2)
extern float                   g_IKSpineGoalInvMass;         // 0x01550a18 (0.1)
extern int                     g_IKMinSplineSpineCount;      // 0x01550a3c (3)
extern float                   g_IKInheritGoalsExponent;     // 0x01550a5c (0.5)
extern int                     g_IKDebugSplines;             // 0x0166bff8
extern creature_instance_data* g_IKDebugCreature;            // 0x0166c948

// --- same-TU helpers (`IKCreatureToGoals'::ik_utils / nest) and other ik_solver functions ---
void ik_utils_Clear(creature_body_instance_data& body);                                 // 0x009e6c60
void ik_utils_DelegateGoals(creature_instance_data* creature, creature_body_instance_data* body,
                            int* numDelegated, int* numPos, int* numRot, vector_3* sumPos,
                            vector_4* sumRot, ik_goals_data* goals);                    // 0x009e7bb0
void IKComputeRootGoal(creature_instance_data* creature, creature_body_instance_data* root,
                       const vector_4* rootOrientation, vector_3* rootPos);             // 0x009e8210
void IKFinishGoals(creature_instance_data* creature, creature_body_instance_data* root); // 0x009e8860
void IKBodyGoal(creature_body_instance_data* body, const vector_3* restPos, const vector_3* jointR,
                vector_3* outPos, vector_4* outRot);                                    // 0x009e90a0
void IKBodyGoalAnchored(creature_body_instance_data* body, const vector_3* restPos,
                        const vector_3* jointR, vector_3* outPos, vector_4* outRot);    // 0x009e92f0
void IKBodyGoalAnchoredBlend(creature_body_instance_data* body, const vector_3* jointR,
                             const vector_3* center, bool hasPos, bool hasRot,
                             bool hasPosExtra, bool hasRotExtra);                       // 0x009e9430
bool AddSerialSpineConstraints(eastl::vector<ik_constraint, eastl::sp_vector_allocator>* constraints,
                               creature_body_instance_data* body);                     // 0x009f4100
unsigned long AddCrossConstraints(creature_instance_data* creature, creature_body_instance_data* body,
                                  unsigned long flags);                                 // 0x009f41b0

// `IKCreatureToGoals'::nest::ComputeSplineNormal (0x009e99a0, register-arg static helper):
// the body's rest x axis made perpendicular to the tangent.
static inline vector_3 ComputeSplineNormal(const creature_body_instance_data& body, const vector_3& t)
{
    const vector_4& q = body.ik_orientation_rest;
    vector_3 axis;
    axis.x = 1.0f - (q.y * q.y + q.z * q.z) * 2.0f;
    axis.y = (q.w * q.z + q.y * q.x) * 2.0f;
    axis.z = (q.z * q.x - q.w * q.y) * 2.0f;
    vector_3 a = CrossProduct(t, axis);
    return NormalizeSafe(CrossProduct(a, t));
}

// Rest position of a body's joint relative to its own rest center frame.
static inline vector_3 JointRestPos(const creature_body_static_data* sd, const vector_3& jointR,
                                    const vector_3& center)
{
    return QuaternionVectorTransform(sd->rest_orientation_q, jointR) + center;
}

// Rest vector from body b's joint to its parent's joint, rotated into the creature frame.
static inline vector_3 SpineLinkVector(const creature_instance_data& c, const vector_4& rootRot,
                                       const creature_body_instance_data* b)
{
    const float scale = c.requested_scale;
    const creature_body_static_data* bs = b->static_data;
    const creature_body_static_data* ps = b->parent->static_data;
    vector_3 r;
    r.x = scale * ps->local_joint_r__SCALABLE.x - scale * bs->parent_local_joint_r__SCALABLE.x;
    r.y = ps->local_joint_r__SCALABLE.y * scale - bs->parent_local_joint_r__SCALABLE.y * scale;
    r.z = ps->local_joint_r__SCALABLE.z * scale - bs->parent_local_joint_r__SCALABLE.z * scale;
    return QuaternionVectorTransform(QuaternionProduct(rootRot, ps->rest_orientation_q), r);
}

// Quintic Hermite basis: positions h0/h1, first-derivative weights ha/hb, second-derivative
// weights hc/hd (p0/p1 are the end points).
struct hermite5
{
    float h0, h1, ha, hb, hc, hd;

    hermite5(float t)
    {
        float t2 = t * t;
        float t3 = t2 * t;
        float t4 = t3 * t;
        float t5 = t4 * t;
        h1 = (t3 * 10.0f - t4 * 15.0f) + t5 * 6.0f;
        h0 = ((1.0f - t3 * 10.0f) + t4 * 15.0f) - t5 * 6.0f;
        ha = ((t - t3 * 6.0f) + t4 * 8.0f) - t5 * 3.0f;
        hb = (t4 * 7.0f - t3 * 4.0f) - t5 * 3.0f;
        hc = (((t2 - t3 * 3.0f) + t4 * 3.0f) - t5) * 0.5f;
        hd = ((t3 - t4 * 2.0f) + t5) * 0.5f;
    }
};

// Derivative of hermite5 with respect to t.
struct hermite5_d
{
    float h0, h1, ha, hb, hc, hd;

    hermite5_d(float t)
    {
        float t2 = t * t;
        float t3 = t2 * t;
        float t4 = t3 * t;
        h1 = (t2 * 30.0f - t3 * 60.0f) + t4 * 30.0f;
        h0 = (t3 * 60.0f - t2 * 30.0f) - t4 * 30.0f;
        ha = ((1.0f - t2 * 18.0f) + t3 * 32.0f) - t4 * 15.0f;
        hb = (t3 * 28.0f - t2 * 12.0f) - t4 * 15.0f;
        hc = (((t * 2.0f - t2 * 9.0f) + t3 * 12.0f) - t4 * 5.0f) * 0.5f;
        hd = ((t2 * 3.0f - t3 * 8.0f) + t4 * 5.0f) * 0.5f;
    }
};

typedef eastl::vector<ik_constraint, eastl::sp_vector_allocator> ik_constraint_vector;

// @ 0x009f4660
void IKCreatureToGoals(creature_instance_data& c, const vector_4& rootRot)
{
    creature_body_instance_data* root = c.Bodies.mpBegin;
    const int numBodies = (int)(c.Bodies.mpEnd - c.Bodies.mpBegin);

    vector_3 rootPos;
    IKComputeRootGoal(&c, root, &rootRot, &rootPos);
    c.ik_root_orientation = rootRot;
    c.ik_root_scale = c.requested_scale;
    ik_utils_Clear(*root);

    // ---------------------------------------------------------------- A: goals, leaf to root
    for (int i = numBodies - 1; i >= 0; --i)
    {
        creature_body_instance_data& body = c.Bodies.mpBegin[i];
        ik_utils_Clear(body);

        ik_goals_data goals;
        bool hasPos      = body.goal.pos_weight > 0.0f;
        bool hasRot      = body.goal.rot_weight > 0.0f;
        bool hasPosExtra = body.goal_extra.pos_weight > 0.0f;
        bool hasRotExtra = body.goal_extra.rot_weight > 0.0f;
        if (hasPos || hasRot || hasPosExtra || hasRotExtra)
            goals.MergeThisBIdx((unsigned char)i);

        const creature_body_static_data* sd = body.static_data;
        for (unsigned long k = 0; k < sd->num_children; ++k)
            goals.MergeChild(c.Bodies.mpBegin[sd->first_child_bidx + k].ik_goals, k);
        body.ik_goals = goals;

        if (i == 0)
            continue;

        body.ik_orientation_rest = QuaternionProduct(rootRot, sd->rest_orientation_q);

        const float scale = c.requested_scale;
        creature_body_instance_data* parent = body.parent;
        vector_3 center = make_v3(sd->rest_center__SCALABLE.x * scale, sd->rest_center__SCALABLE.y * scale,
                                  sd->rest_center__SCALABLE.z * scale);
        vector_3 jointR = make_v3(sd->ik_joint_r__SCALABLE.x * scale, sd->ik_joint_r__SCALABLE.y * scale,
                                  sd->ik_joint_r__SCALABLE.z * scale);

        vector_3 rel = JointRestPos(sd, jointR, center) - rootPos;
        vector_3 restPos = QuaternionVectorTransform(rootRot, rel) + root->ik_particle_rest;

        unsigned char type = body.ik_goals.TypeAndFlags & 7;
        if (type == 0)
        {
            // Own goals only.
            if ((sd->caps_flags & 0xa) == 0 && (parent->static_data->caps_flags & 0xa) != 0
                && (hasPos || hasRot))
            {
                if (!hasPosExtra && !hasRotExtra)
                {
                    body.ik_goal_mode = 2;
                    IKBodyGoalAnchored(&body, &restPos, &jointR, &body.ik_particle_goal, &body.ik_goal_orientation);
                }
                else
                {
                    body.ik_goal_mode = 1;
                    IKBodyGoalAnchoredBlend(&body, &jointR, &center, hasPos, hasRot, hasPosExtra, hasRotExtra);
                }
            }
            else
            {
                body.ik_goal_mode = 0;
                IKBodyGoal(&body, &restPos, &jointR, &body.ik_particle_goal, &body.ik_goal_orientation);
            }
            body.ik_particle_rest = restPos;
            body.ik_particle = body.ik_particle_goal;
            body.ik_state = 1;
            body.ik_invmass = 0.0f;
        }
        else if (type == 4)
        {
            // No goals anywhere in this subtree.
            body.ik_invmass = -1.0f;
        }
        else
        {
            // Goals delegated from the subtree.
            body.ik_particle_rest = restPos;

            int numDelegated = 0;
            int numPos = 0;
            int numRot = 0;
            vector_3 sumPos = make_v3(0.0f, 0.0f, 0.0f);
            vector_4 sumRot;
            sumRot.x = 0.0f; sumRot.y = 0.0f; sumRot.z = 0.0f; sumRot.w = 0.0f;
            ik_goals_data delegated;
            ik_utils_DelegateGoals(&c, &body, &numDelegated, &numPos, &numRot, &sumPos, &sumRot, &delegated);

            if (numPos == 0 && (body.ik_goals.TypeAndFlags & 0x10) == 0)
            {
                body.ik_invmass = 1.0f;
                body.ik_particle_goal = body.ik_particle_rest;
                body.ik_state = 5;
            }
            else
            {
                delegated.MergeThisBIdx((unsigned char)i);
                int posCount = numPos;
                int rotCount = numRot;
                if (body.ik_goals.TypeAndFlags & 0x10)
                {
                    vector_3 ownPos;
                    vector_4 ownRot;
                    IKBodyGoal(&body, &restPos, &jointR, &ownPos, &ownRot);
                    if (DotProduct(ownRot, sumRot) < 0.0f)
                    {
                        sumRot.x = sumRot.x - ownRot.x;
                        sumRot.y = sumRot.y - ownRot.y;
                        sumRot.z = sumRot.z - ownRot.z;
                        sumRot.w = sumRot.w - ownRot.w;
                    }
                    else
                    {
                        sumRot.x = ownRot.x + sumRot.x;
                        sumRot.y = ownRot.y + sumRot.y;
                        sumRot.z = ownRot.z + sumRot.z;
                        sumRot.w = ownRot.w + sumRot.w;
                    }
                    rotCount = numRot + 1;
                    body.ik_state = (numPos > 0) ? 3 : 4;
                    posCount = numPos + 1;
                    sumPos = ownPos + sumPos;
                }
                else
                {
                    body.ik_state = 2;
                }

                float fPosCount = (float)posCount;
                float inv = 1.0f / fPosCount;
                body.ik_particle_goal.y = sumPos.y * inv;
                body.ik_particle_goal.z = sumPos.z * inv;
                body.ik_particle_goal.x = inv * sumPos.x;
                body.ik_goal_orientation = Normalize(sumRot, 0);
                body.ik_goals = delegated;
                body.ik_invmass = (float)(numRot != numDelegated);
                body.ik_inherit_goals = (float)pow((double)fPosCount / rotCount, (double)g_IKInheritGoalsExponent);
            }

            body.ik_particle = body.ik_particle_goal;

            unsigned long flags = body.static_data->caps_flags;
            if (flags & 8)
            {
                if (body.parent == root)
                {
                    body.ik_invmass = 0.0f;
                    body.ik_particle_goal = body.ik_particle_rest;
                }
            }
            else if (body.parent == root)
                body.ik_invmass = 0.0f;
            else if (parent->static_data->caps_flags & 8)
                body.ik_invmass = (flags & 2) ? 0.0f : g_IKSpineGoalInvMass;
            else
                body.ik_invmass = 1.0f;
        }

        // Rest vector from this joint to the parent's joint.
        vector_3 joint = JointRestPos(body.static_data, jointR, center);
        const creature_body_static_data* ps = parent->static_data;
        const float pscale = c.requested_scale;
        vector_3 pJointR = make_v3(ps->ik_joint_r__SCALABLE.x * pscale, ps->ik_joint_r__SCALABLE.y * pscale,
                                   ps->ik_joint_r__SCALABLE.z * pscale);
        vector_3 pCenter = make_v3(pscale * ps->rest_center__SCALABLE.x, ps->rest_center__SCALABLE.y * pscale,
                                   ps->rest_center__SCALABLE.z * pscale);
        vector_3 d = (pCenter + QuaternionVectorTransform(ps->rest_orientation_q, pJointR)) - joint;
        body.ik_parent_r_rest = QuaternionVectorTransform(rootRot, d);
        body.ik_parent_length = Length(body.ik_parent_r_rest);
    }

    IKFinishGoals(&c, root);
    ik_constraint_vector& constraints = c.ik_constraints;
    constraints.resize(0);

    // ---------------------------------------------------------------- B: constraints
    for (int i = 1; i < numBodies; ++i)
    {
        creature_body_instance_data& body = c.Bodies.mpBegin[i];
        if ((body.ik_goals.TypeAndFlags & 7) == 4)
            continue;

        const unsigned long before = constraints.size();

        if (body.static_data->caps_flags & 8)
        {
            switch (body.ik_goals.TypeAndFlags & 7)
            {
            case 0:
                AddSerialSpineConstraints(&constraints, &body);
                break;
            case 1:
                if (!AddSerialSpineConstraints(&constraints, &body))
                    constraints.push_back(ik_constraint(&body, &body.ik_particle, 0.0f,
                                                        &body, &body.ik_particle, 0.0f, 0.0f, 0x80));
                body.ik_num_active_children = 1;
                break;
            case 2:
            case 3:
            {
                creature_body_instance_data& child =
                    c.Bodies.mpBegin[body.static_data->first_child_bidx + body.ik_goals.ChildIdx];
                if ((child.static_data->caps_flags & 8) == 0)
                    AddSerialSpineConstraints(&constraints, &body);
                break;
            }
            }

            if (body.ik_goals.TypeAndFlags & 0x10)
                constraints.push_back(ik_constraint(&body, &body.ik_particle_goal, 0.0f, &body, &body.ik_particle,
                                                    1.0f - c.ik_spine_rest_alpha, 0.0f, 0x10));
            if (body.ik_in_constraint)
                constraints.push_back(ik_constraint(&body, &body.ik_particle_rest, 0.0f, &body, &body.ik_particle,
                                                    c.ik_spine_rest_alpha, 0.0f, 8));
        }
        else
        {
            creature_body_instance_data* parent = body.parent;
            if (parent->parent == 0 || (parent->static_data->caps_flags & 8) != 0)
            {
                if ((body.ik_goals.TypeAndFlags & 7) == 1)
                {
                    constraints.push_back(ik_constraint(&body, &body, 0.0f, 0x280));
                    constraints.back().Flags |= 2;
                }
            }
            else
            {
                constraints.push_back(ik_constraint(parent, &body, body.ik_parent_length, 0x240));
                ik_constraint& k = constraints.back();
                if ((body.ik_goals.TypeAndFlags & 7) == 1)
                    k.Flags |= 2;
                if ((body.parent->ik_goals.TypeAndFlags & 7) == 1)
                    k.Flags |= 4;
            }

            body.ik_num_active_children = AddCrossConstraints(&c, &body, 0x200);

            if (body.ik_goals.TypeAndFlags & 0x10)
            {
                // Walk up to the spine (or the root), summing the link lengths.
                creature_body_instance_data* p = body.parent;
                float length = body.ik_parent_length;
                creature_body_instance_data* spineEnd = 0;
                creature_body_instance_data* last = 0;
                if (p)
                {
                    do
                    {
                        if (p->static_data->caps_flags & 8)
                            break;
                        if ((p->ik_goals.TypeAndFlags & 7) == 2)
                            spineEnd = p;
                        last = p;
                        length = p->ik_parent_length + length;
                        p = p->parent;
                    } while (p);

                    if (spineEnd && last)
                    {
                        // Is the limb chain (body .. spineEnd) straight?
                        vector_3 d = body.ik_particle_rest - last->ik_particle_rest;
                        float tolerance = Length2(d) * g_IKSpineCollinearTolerance;
                        creature_body_instance_data* end = spineEnd->parent;
                        bool straight = true;
                        for (creature_body_instance_data* q = body.parent; q != end; q = q->parent)
                        {
                            vector_3 r = q->ik_particle_rest - last->ik_particle_rest;
                            if (Length2(CrossProduct(d, r)) > Length2(r) * tolerance)
                                straight = false;
                        }
                        if (straight)
                            for (creature_body_instance_data* q = body.parent; q != end; q = q->parent)
                                q->ik_limb_straight = true;
                    }
                }

                if (p->parent != 0)
                {
                    constraints.push_back(ik_constraint(p, &body, length, 0));
                    ++body.ik_goal_to_spine_num;
                    ik_constraint& k = constraints.back();
                    k.invmass_i = g_IKSpineGoalInvMass;
                    k.Flags |= 0x540;
                    k.rest_invmass_i = g_IKSpineGoalInvMass;
                    k.SetSoft(1.0f, 10.0f, g_IKSpineSoftDeltaMin, 0.0f);
                }
            }
        }

        unsigned long added = constraints.size() - before;
        body.ik_constraint_num = added;
        if (added)
            body.ik_constraint_idx = before;
    }

    // ---------------------------------------------------------------- C: link constraints
    const int numConstraints = (int)constraints.size();
    for (int n = 0; n < numConstraints; ++n)
    {
        ik_constraint& k = constraints.mpBegin[n];
        if (k.Flags & 2)
        {
            creature_body_instance_data* bj = k.b_j;
            const creature_body_static_data* sd = bj->static_data;
            ik_constraint** link = &k.multi_branch_base_start;
            for (unsigned long m = 0; m < sd->num_children; ++m)
            {
                creature_body_instance_data& child = c.Bodies.mpBegin[sd->first_child_bidx + m];
                if (child.ik_constraint_num != 0)
                {
                    ik_constraint* ck = &c.ik_constraints.mpBegin[child.ik_constraint_idx];
                    *link = ck;
                    link = &ck->multi_branch_child_next;
                }
            }
            for (unsigned long m = bj->ik_constraint_idx + 1; m != bj->ik_constraint_idx + bj->ik_constraint_num; ++m)
            {
                ik_constraint* ck = &c.ik_constraints.mpBegin[m];
                if (ck->Flags & 0x200)
                {
                    *link = ck;
                    link = &ck->multi_branch_child_next;
                }
            }
        }
        if (k.Flags & 1)
        {
            k.b_i->ik_end_spine_constraint = &k;
            k.b_j->ik_own_spine_constraint = &k;
        }
    }

    // ---------------------------------------------------------------- D: spine splines
    for (int n = 0; n < numConstraints; ++n)
    {
        ik_constraint& k = constraints.mpBegin[n];
        if ((k.Flags & 1) == 0)
            continue;

        const float restLength = k.rest_length;
        const float invRestLength = 1.0f / restLength;
        float stretch = restLength / k.spine_chord_rest_length;
        k.Flags |= (stretch >= 1.3f) ? 0x800 : 0;

        vector_3 p0 = k.b_j->ik_particle_rest;
        vector_3 p1 = k.b_i->ik_particle_rest;
        if (g_IKDebugSplines && &c == g_IKDebugCreature)
            fprintf(stderr, "%f\n", (double)stretch);

        // First spine joint after b_j and its curve parameter.
        creature_body_instance_data* bj = k.b_j;
        const float t0Accum = bj->ik_parent_length * invRestLength;
        vector_3 link0 = SpineLinkVector(c, rootRot, bj);
        vector_3 joint0 = bj->ik_particle_rest + link0;
        const float t0 = DotProduct(bj->ik_parent_r_rest, link0) / (bj->ik_parent_length * restLength);

        // Hermite coefficients (body frame) of the fitted curve.
        vector_3 ta, tb, tc, td;
        if (k.spine_count >= g_IKMinSplineSpineCount)
        {
            // Least squares: the curve through p0/p1 that passes closest to the joints.
            matrix_4x4 A;
            matrix_4x4 B;
            A.InitZero();
            B.InitZero();

            float accum = t0Accum;
            float t = t0;
            vector_3 joint = joint0;
            for (creature_body_instance_data* b = bj->parent; b != k.b_i->parent; )
            {
                hermite5 h(t);
                b->ik_spine_t = t;
                vector_3 res = (h.h0 * p0 + h.h1 * p1) - joint;

                float basis[4] = { h.ha, h.hb, h.hc, h.hd };
                for (int r = 0; r < 4; ++r)
                {
                    for (int s = 0; s < 4; ++s)
                        A(r, s) = A(r, s) + basis[r] * basis[s];
                    B(r, 0) = B(r, 0) - basis[r] * res.x;
                    B(r, 1) = B(r, 1) - res.y * basis[r];
                    B(r, 2) = B(r, 2) - res.z * basis[r];
                }

                creature_body_instance_data* next = b->parent;
                vector_3 link = SpineLinkVector(c, rootRot, b);
                joint = b->ik_particle_rest + link;
                float nextAccum = b->ik_parent_length * invRestLength + accum;
                t = DotProduct(b->ik_parent_r_rest, link) / (b->ik_parent_length * restLength) + accum;
                accum = nextAccum;
                b = next;
            }

            // One right-hand side per coordinate.
            matrix_4x4 Bt;
            for (int r = 0; r < 4; ++r)
                for (int s = 0; s < 4; ++s)
                    Bt(r, s) = B(s, r);
            B = Bt;
            LinearSolveInPlace(A, (vector_4*)B.el, 3);

            ta = make_v3(B(0, 0), B(1, 0), B(2, 0));
            tc = make_v3(B(0, 2), B(1, 2), B(2, 2));
            tb = make_v3(B(0, 1), B(1, 1), B(2, 1));
            td = make_v3(B(0, 3), B(1, 3), B(2, 3));
        }

        // b_j end: secant tangent, tangent, normal.
        bj = k.b_j;
        if (bj->ik_end_spine_constraint == 0)
            bj->ik_spine_spline_secant_tangent_rest = make_v3(0.0f, 0.0f, 0.0f);
        else
            bj->ik_spine_spline_secant_tangent_rest =
                Normalize(k.b_i->ik_particle_rest - bj->ik_end_spine_constraint->b_j->ik_particle_rest);

        vector_3 tangentJ;
        vector_3 normalJ;
        if (k.spine_count < g_IKMinSplineSpineCount)
        {
            bj = k.b_j;
            if (bj->ik_end_spine_constraint == 0)
                tangentJ = Normalize(bj->parent->ik_particle_rest - bj->ik_particle_rest);
            else
                tangentJ = bj->ik_spine_spline_secant_tangent_rest;
            normalJ = ComputeSplineNormal(*bj, tangentJ);
            k.spine_spline_j.tangent = QuaternionVectorTransformInverse(bj->ik_orientation_rest, tangentJ);
        }
        else
        {
            bj = k.b_j;
            k.spine_spline_j.coef0 = QuaternionVectorTransformInverse(bj->ik_orientation_rest, ta);
            k.spine_spline_j.coef1 = QuaternionVectorTransformInverse(bj->ik_orientation_rest, tc);
            tangentJ = NormalizeSafe(ta);
            normalJ = ComputeSplineNormal(*bj, tangentJ);
            k.spine_spline_j.tangent = QuaternionVectorTransformInverse(bj->ik_orientation_rest, tangentJ);
        }
        k.spine_spline_j.normal = QuaternionVectorTransformInverse(k.b_j->ik_orientation_rest, normalJ);

        // b_i end.
        creature_body_instance_data* bi = k.b_i;
        if (bi->ik_own_spine_constraint == 0)
            bi->ik_spine_spline_secant_tangent_rest = make_v3(0.0f, 0.0f, 0.0f);
        else
            bi->ik_spine_spline_secant_tangent_rest =
                Normalize(bi->ik_own_spine_constraint->b_i->ik_particle_rest - k.b_j->ik_particle_rest);

        vector_3 tangentI;
        vector_3 normalI;
        if (k.spine_count < g_IKMinSplineSpineCount)
        {
            bi = k.b_i;
            if (bi->ik_own_spine_constraint == 0)
                tangentI = Normalize(bi->ik_particle_rest - bi->first_child->ik_particle_rest);
            else
                tangentI = bi->ik_spine_spline_secant_tangent_rest;
            normalI = ComputeSplineNormal(*bi, tangentI);
            k.spine_spline_i.tangent = QuaternionVectorTransformInverse(bi->ik_orientation_rest, tangentI);
        }
        else
        {
            bi = k.b_i;
            k.spine_spline_i.coef0 = QuaternionVectorTransformInverse(bi->ik_orientation_rest, tb);
            k.spine_spline_i.coef1 = QuaternionVectorTransformInverse(bi->ik_orientation_rest, td);
            tangentI = NormalizeSafe(tb);
            normalI = ComputeSplineNormal(*bi, tangentI);
            k.spine_spline_i.tangent = QuaternionVectorTransformInverse(k.b_i->ik_orientation_rest, tangentI);
        }
        k.spine_spline_i.normal = QuaternionVectorTransformInverse(k.b_i->ik_orientation_rest, normalI);

        if (k.spine_count < g_IKMinSplineSpineCount)
        {
            // Short spine: straight chord, orientation slerped (nlerp) between the end frames.
            float t = t0;
            float accum = t0Accum;
            vector_3 joint = joint0;

            vector_4 qj = matrix_to_quaternion(FrameFromNormalTangent(normalJ, tangentJ));
            vector_4 qi = matrix_to_quaternion(FrameFromNormalTangent(normalI, tangentI));
            if (DotProduct(qi, qj) < 0.0f)
            {
                qi.x = -qi.x;
                qi.y = -qi.y;
                qi.z = -qi.z;
                qi.w = -qi.w;
            }

            for (creature_body_instance_data* b = k.b_j->parent; b != k.b_i->parent; )
            {
                float u = 1.0f - t;
                vector_3 pos;
                pos.z = u * p0.z + t * p1.z;
                pos.x = u * p0.x + t * p1.x;
                pos.y = u * p0.y + t * p1.y;
                b->ik_spine_t = t;
                vector_4 q;
                q.x = u * qj.x + qi.x * t;
                q.y = u * qj.y + qi.y * t;
                q.z = u * qj.z + qi.z * t;
                q.w = u * qj.w + qi.w * t;
                vector_4 qn = Normalize(q, 0);

                vector_3 offset = joint - pos;
                b->ik_in_spine = true;
                b->ik_spine_pos = pos;
                b->ik_spine_local_pos = QuaternionVectorTransformInverse(qn, offset);
                b->ik_spine_local_rot = QuaternionProduct(QuaternionConjugate(qn), b->ik_orientation_rest);

                vector_3 link = SpineLinkVector(c, rootRot, b);
                joint = b->ik_particle_rest + link;
                t = DotProduct(b->ik_parent_r_rest, link) / (b->ik_parent_length * restLength) + accum;
                accum = b->ik_parent_length * invRestLength + accum;
                b = b->parent;
            }
        }
        else
        {
            // Long spine: evaluate the fitted curve and propagate the frame along it.
            if (g_IKDebugSplines && &c == g_IKDebugCreature)
                fprintf(stderr, "points = {\n");

            vector_3 prevTangent = tangentJ;
            vector_3 prevNormal = normalJ;
            for (creature_body_instance_data* b = k.b_j->parent; b != k.b_i->parent; b = b->parent)
            {
                float t = b->ik_spine_t;
                hermite5 h(t);
                vector_3 pos = ((((h.h0 * p0 + h.h1 * p1) + h.ha * ta) + h.hb * tb) + h.hc * tc) + h.hd * td;
                hermite5_d dh(t);
                vector_3 dpos = ((((dh.h0 * p0 + dh.h1 * p1) + dh.ha * ta) + dh.hb * tb) + dh.hc * tc) + dh.hd * td;
                vector_3 tangent = NormalizeSafe(dpos);

                matrix_3x3 turn = RotationAtoB(prevTangent, tangent, 0, 0);
                vector_3 normal;
                normal.x = (turn.el[0] * prevNormal.x + turn.el[2] * prevNormal.z) + turn.el[1] * prevNormal.y;
                normal.y = (turn.el[3] * prevNormal.x + turn.el[5] * prevNormal.z) + turn.el[4] * prevNormal.y;
                normal.z = (turn.el[6] * prevNormal.x + turn.el[8] * prevNormal.z) + turn.el[7] * prevNormal.y;
                prevTangent = tangent;
                prevNormal = normal;

                matrix_3x3 frame = FrameFromNormalTangent(normal, tangent);
                vector_4 frameQ = matrix_to_quaternion(frame);

                // The body's rest goal position in the creature frame.
                const creature_body_static_data* bs = b->static_data;
                const float scale = c.requested_scale;
                vector_3 jr = make_v3(bs->local_joint_r__SCALABLE.x * scale, bs->local_joint_r__SCALABLE.y * scale,
                                      bs->local_joint_r__SCALABLE.z * scale);
                vector_3 cc = make_v3(bs->rest_center__SCALABLE.x * scale, bs->rest_center__SCALABLE.y * scale,
                                      bs->rest_center__SCALABLE.z * scale);
                vector_3 rel = (cc + QuaternionVectorTransform(bs->rest_orientation_q, jr)) - rootPos;
                vector_3 goal = root->ik_particle_rest + QuaternionVectorTransform(rootRot, rel);

                b->ik_in_spine = true;
                b->ik_spine_pos = pos;
                vector_3 offset = goal - pos;
                b->ik_spine_local_pos.x = (offset.x * frame.el[0] + offset.z * frame.el[6]) + offset.y * frame.el[3];
                b->ik_spine_local_pos.y = (offset.x * frame.el[1] + offset.z * frame.el[7]) + offset.y * frame.el[4];
                b->ik_spine_local_pos.z = (offset.x * frame.el[2] + offset.z * frame.el[8]) + offset.y * frame.el[5];
                b->ik_spine_local_rot = QuaternionProduct(QuaternionConjugate(frameQ), b->ik_orientation_rest);

                if (g_IKDebugSplines && &c == g_IKDebugCreature)
                    fprintf(stderr, "{%f, {%f,%f,%f}, {%f,%f,%f}}%s\n", (double)t,
                            (double)pos.x, (double)pos.y, (double)pos.z,
                            (double)goal.x, (double)goal.y, (double)goal.z,
                            (b->parent != k.b_i->parent) ? "," : "");
            }

            if (g_IKDebugSplines && &c == g_IKDebugCreature)
            {
                fprintf(stderr, "};\n");
                fprintf(stderr, "p0 = {%f,%f,%f};\n", (double)p0.x, (double)p0.y, (double)p0.z);
                fprintf(stderr, "p1 = {%f,%f,%f};\n", (double)p1.x, (double)p1.y, (double)p1.z);
                vector_3 n0 = NormalizeSafe(k.b_j->parent->ik_particle_rest - k.b_j->ik_particle_rest) * restLength;
                vector_3 n1 = NormalizeSafe(k.b_i->ik_particle_rest - k.b_i->first_child->ik_particle_rest) * restLength;
                fprintf(stderr, "n0 = {%f,%f,%f};\n", (double)n0.x, (double)n0.y, (double)n0.z);
                fprintf(stderr, "n1 = {%f,%f,%f};\n", (double)n1.x, (double)n1.y, (double)n1.z);
            }

            // Spread the twist between the propagated frame and b_i's frame over the spine.
            vector_3 axis = CrossProduct(prevNormal, normalI);
            if ((double)axis.x * axis.x + (double)axis.y * axis.y + (double)axis.z * axis.z > 1e-6)
            {
                matrix_3x3 twist;
                twist.InitIdentity();
                double angle = atan2((double)DotProduct(axis, tangentI), (double)DotProduct(normalI, prevNormal));
                twist.ConcatenateYRotation((float)(angle / k.spine_count));
                vector_4 step = matrix_to_quaternion(twist);
                vector_4 acc = step;
                for (creature_body_instance_data* b = k.b_j->parent; b != k.b_i->parent; b = b->parent)
                {
                    b->ik_spine_local_pos = QuaternionVectorTransformInverse(acc, b->ik_spine_local_pos);
                    b->ik_spine_local_rot = QuaternionProduct(QuaternionConjugate(acc), b->ik_spine_local_rot);
                    acc = QuaternionProduct(acc, step);
                }
            }
        }
    }
}
} // namespace nSPCreatureAnim
