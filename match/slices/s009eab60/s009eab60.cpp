// Slice s009eab60 -- nSPCreatureAnim IK goal retarget pass (0x009eab60, 6140 bytes).
//
// Retail-only ik_solver function (no dev-PDB counterpart; name guessed). It re-targets the
// IK goals of an already set-up creature to a new root orientation and scale without
// rebuilding the constraint set (IKCreatureToGoals, 0x009f4660, does the full build):
//   1. root goal (IKComputeRootGoal), delta rotation old root orientation -> rootRot,
//      scale ratio requested_scale / ik_root_scale;
//   2. bodies, leaf to root (index n-1 .. 1): rest orientation, rest particle, and the goal
//      particle/orientation per ik_state; rotate the cached spine tangent and parent link by
//      the delta rotation and rescale the cached lengths;
//   3. IKFinishRetargetGoals on the root (0x009ea370);
//   4. constraints: reset the rest inverse masses and rescale the rest lengths and spine
//      spline coefficients.
//
// Types are shared with s009f4660 (copied, since slices are self-contained).
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

    vector_3& operator=(const vector_3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

class vector_4
{
public:
    float x, y, z, w;

    vector_4& operator=(const vector_4& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
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

void IKComputeRootGoal(creature_instance_data* creature, creature_body_instance_data* root,
                       const vector_4* rootOrientation, vector_3* rootPos);             // 0x009e8210
void IKBodyGoal(creature_body_instance_data* body, const vector_3* restPos, const vector_3* jointR,
                vector_3* outPos, vector_4* outRot);                                    // 0x009e90a0
void IKBodyGoalAnchored(creature_body_instance_data* body, const vector_3* restPos,
                        const vector_3* jointR, vector_3* outPos, vector_4* outRot);    // 0x009e92f0
void IKBodyGoalAnchoredBlend(creature_body_instance_data* body, const vector_3* jointR,
                             const vector_3* center, bool hasPos, bool hasRot,
                             bool hasPosExtra, bool hasRotExtra);                       // 0x009e9430
// Sums the goal positions/orientations delegated to this body by its subtree (name guessed).
void IKSumDelegatedGoals(creature_instance_data* creature, creature_body_instance_data* body,
                         int* count, vector_3* sumPos, vector_4* sumRot);               // 0x009e9af0
// Root pass after the per-body retarget (name guessed).
void IKFinishRetargetGoals(creature_instance_data* creature, creature_body_instance_data* root); // 0x009ea370

// a * conjugate(b): the rotation that takes b to a.
inline vector_4 QuaternionProductConjugate(const vector_4& a, const vector_4& b)
{
    vector_4 r;
    r.x = ((a.x * b.w - b.x * a.w) + a.z * b.y) - a.y * b.z;
    r.y = ((a.y * b.w - a.z * b.x) - b.y * a.w) + b.z * a.x;
    r.z = ((a.y * b.x + a.z * b.w) - b.y * a.x) - b.z * a.w;
    r.w = ((b.z * a.z + a.y * b.y) + b.x * a.x) + a.w * b.w;
    return r;
}

// QuaternionVectorTransform, always inlined (the original hoists the q products out of the body loop).
__forceinline vector_3 QuaternionVectorTransformInl(const vector_4& q, const vector_3& v)
{
    vector_3 r;
    r.x = (((-(q.z * q.z) + -(q.y * q.y)) * v.x + (q.z * q.x + q.y * q.w) * v.z) + (q.y * q.x - q.z * q.w) * v.y) * 2.0f + v.x;
    r.y = (((q.y * q.x + q.z * q.w) * v.x + (q.z * q.y - q.x * q.w) * v.z) + (-(q.z * q.z) + -(q.x * q.x)) * v.y) * 2.0f + v.y;
    r.z = (((q.z * q.x - q.y * q.w) * v.x + (-(q.y * q.y) + -(q.x * q.x)) * v.z) + (q.z * q.y + q.x * q.w) * v.y) * 2.0f + v.z;
    return r;
}

inline void SetZero(vector_3& v) { v.x = 0.0f; v.y = 0.0f; v.z = 0.0f; }
inline void SetZero(vector_4& v) { v.x = 0.0f; v.y = 0.0f; v.z = 0.0f; v.w = 0.0f; }
inline void Scale(vector_3& v, float s) { v.x = v.x * s; v.y = v.y * s; v.z = v.z * s; }

// @ 0x009eab60
void IKCreatureRetargetGoals(creature_instance_data& c, const vector_4& rootRot)
{
    creature_body_instance_data* root = &c.Bodies[0];
    vector_3 rootPos;
    IKComputeRootGoal(&c, root, &rootRot, &rootPos);
    root->ik_limb_aimed = false;
    SetZero(root->ik_particle_goal);
    SetZero(root->ik_spine_pos);

    const vector_4 dq = QuaternionProductConjugate(rootRot, c.ik_root_orientation);
    c.ik_root_orientation = rootRot;

    float scaleRatio = 1.0f;
    const float scale = c.requested_scale;
    if (scale != c.ik_root_scale)
    {
        scaleRatio = scale / c.ik_root_scale;
        c.ik_root_scale = scale;
    }

    for (int i = (int)c.Bodies.size() - 1; i >= 1; --i)
    {
        creature_body_instance_data& b = c.Bodies[i];
        b.ik_limb_aimed = false;
        SetZero(b.ik_particle_goal);
        SetZero(b.ik_spine_pos);
        b.ik_orientation_rest = QuaternionProduct(rootRot, b.static_data->rest_orientation_q);

        const creature_body_static_data* sd = b.static_data;
        const float s = c.requested_scale;
        const vector_3 center = sd->rest_center__SCALABLE * s;
        const vector_3 jointR = sd->ik_joint_r__SCALABLE * s;
        const vector_3 local = (QuaternionVectorTransform(sd->rest_orientation_q, jointR) + center) - rootPos;
        vector_3 restPos = QuaternionVectorTransform(rootRot, local) + root->ik_particle_rest;
        const bool anchored = ((sd->caps_flags >> 3) & 1) != 0;

        switch (b.ik_state)
        {
        case 1:
            switch (b.ik_goal_mode)
            {
            case 0:
                IKBodyGoal(&b, &restPos, &jointR, &b.ik_particle_goal, &b.ik_goal_orientation);
                break;
            case 1:
                IKBodyGoalAnchoredBlend(&b, &jointR, &center,
                                        b.goal.pos_weight > 0.0f, b.goal.rot_weight > 0.0f,
                                        b.goal_extra.pos_weight > 0.0f, b.goal_extra.rot_weight > 0.0f);
                break;
            case 2:
                IKBodyGoalAnchored(&b, &restPos, &jointR, &b.ik_particle_goal, &b.ik_goal_orientation);
                break;
            }
            b.ik_particle_rest = restPos;
            b.ik_particle = b.ik_particle_goal;
            break;

        case 2:
        {
            b.ik_particle_rest = restPos;
            int count = 0;
            vector_4 sumRot;
            SetZero(sumRot);
            vector_3 sumPos;
            SetZero(sumPos);
            IKSumDelegatedGoals(&c, &b, &count, &sumPos, &sumRot);
            const float inv = 1.0f / (float)count;
            b.ik_particle_goal.x = inv * sumPos.x;
            b.ik_particle_goal.y = sumPos.y * inv;
            b.ik_particle_goal.z = sumPos.z * inv;
            b.ik_goal_orientation = Normalize(sumRot, 0);
            b.ik_particle = b.ik_particle_goal;
            if (anchored && b.parent == root)
                b.ik_particle_goal = b.ik_particle_rest;
            break;
        }

        case 3:
        {
            b.ik_particle_rest = restPos;
            int count = 0;
            vector_4 sumRot;
            SetZero(sumRot);
            vector_3 sumPos;
            SetZero(sumPos);
            IKSumDelegatedGoals(&c, &b, &count, &sumPos, &sumRot);
            vector_3 goalPos;
            vector_4 goalRot;
            IKBodyGoal(&b, &restPos, &jointR, &goalPos, &goalRot);
            // Add the body's own goal orientation in the same hemisphere as the sum.
            if (DotProduct(goalRot, sumRot) < 0.0f)
            {
                sumRot.x = sumRot.x - goalRot.x;
                sumRot.y = sumRot.y - goalRot.y;
                sumRot.z = sumRot.z - goalRot.z;
                sumRot.w = sumRot.w - goalRot.w;
            }
            else
            {
                sumRot.x = goalRot.x + sumRot.x;
                sumRot.y = goalRot.y + sumRot.y;
                sumRot.z = goalRot.z + sumRot.z;
                sumRot.w = goalRot.w + sumRot.w;
            }
            const float inv = 1.0f / (float)(count + 1);
            b.ik_particle_goal.x = inv * (goalPos.x + sumPos.x);
            b.ik_particle_goal.y = (goalPos.y + sumPos.y) * inv;
            b.ik_particle_goal.z = (goalPos.z + sumPos.z) * inv;
            b.ik_goal_orientation = Normalize(sumRot, 0);
            b.ik_particle = b.ik_particle_goal;
            if (anchored && b.parent == root)
                b.ik_particle_goal = b.ik_particle_rest;
            break;
        }

        case 4:
            b.ik_particle_rest = restPos;
            IKBodyGoal(&b, &restPos, &jointR, &b.ik_particle_goal, &b.ik_goal_orientation);
            b.ik_particle = b.ik_particle_goal;
            if (anchored && b.parent == root)
                b.ik_particle_goal = b.ik_particle_rest;
            break;

        case 5:
            b.ik_particle_rest = restPos;
            b.ik_particle_goal = b.ik_particle_rest;
            b.ik_particle = b.ik_particle_goal;
            if (anchored && b.parent == root)
                b.ik_particle_goal = b.ik_particle_rest;
            break;
        }

        // Cached rest vectors follow the root rotation.
        if (b.ik_own_spine_constraint != 0 &&
            (b.ik_end_spine_constraint != 0 || b.ik_own_spine_constraint->b_i->ik_own_spine_constraint != 0))
        {
            b.ik_spine_spline_secant_tangent_rest =
                QuaternionVectorTransformInl(dq, b.ik_spine_spline_secant_tangent_rest);
        }
        b.ik_parent_r_rest = QuaternionVectorTransformInl(dq, b.ik_parent_r_rest);

        if (scaleRatio != 1.0f)
        {
            b.ik_parent_length = b.ik_parent_length * scaleRatio;
            Scale(b.ik_parent_r_rest, scaleRatio);
            if (b.ik_in_spine)
                Scale(b.ik_spine_local_pos, scaleRatio);
        }
    }

    IKFinishRetargetGoals(&c, root);

    const unsigned int numConstraints = c.ik_constraints.size();
    for (unsigned int i = 0; i < numConstraints; ++i)
    {
        ik_constraint& k = c.ik_constraints[i];
        k.rest_invmass_i = k.invmass_i;
        k.rest_invmass_j = k.invmass_j;
        if (scaleRatio != 1.0f)
        {
            k.rest_length = k.rest_length * scaleRatio;
            if (k.Flags & 1)
            {
                k.spine_chord_rest_length = k.spine_chord_rest_length * scaleRatio;
                if (k.spine_count >= g_IKMinSplineSpineCount)
                {
                    Scale(k.spine_spline_i.coef0, scaleRatio);
                    Scale(k.spine_spline_i.coef1, scaleRatio);
                    Scale(k.spine_spline_j.coef0, scaleRatio);
                    Scale(k.spine_spline_j.coef1, scaleRatio);
                }
            }
        }
    }
}

} // namespace nSPCreatureAnim
