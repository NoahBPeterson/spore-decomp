// Slice s009f41b0 -- nSPCreatureAnim::AddCrossConstraints (0x009f41b0, 1188 bytes).
//
// Builds the "cross" IK constraints of one body: it walks the body's children and
// keeps only the goal-bearing ones (ik_goals type != 4).  The first such child is the
// common anchor; the second forms a single distance constraint, and every further
// child is tied to both the first and the second one (two distance constraints) plus
// an altitude constraint over (body, first, second, child).  When exactly two
// goal-bearing children exist, the single constraint between them is completed with
// the three point/line altitudes instead.  Returns the number of goal-bearing
// children processed.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
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

namespace nSPCreatureAnim
{
struct vector_3
{
    float x, y, z;
};

struct vector_4
{
    float x, y, z, w;
};

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
};

struct creature_body_static_data                      // retail layout (partial)
{
    uint32_t      pad_000[0x10c / 4];
    vector_3      rest_center__SCALABLE;           // +0x10c
    vector_4      rest_orientation_q;              // +0x118
    uint32_t      pad_128[(0x144 - 0x128) / 4];
    vector_3      local_joint_r__SCALABLE;         // +0x144 (name guessed)
    unsigned long caps_flags;                      // +0x150
    uint32_t      pad_154[(0x204 - 0x154) / 4];
    unsigned long first_child_bidx;                // +0x204
    unsigned long num_children;                    // +0x208
};

struct ik_constraint;
struct creature_instance_data;

struct creature_body_instance_data                    // size 0x2bc (retail)
{
    creature_body_static_data*   static_data;                  // +0x000
    creature_instance_data*      creature;                     // +0x004
    creature_body_instance_data* parent;                       // +0x008
    creature_body_instance_data* first_child;                  // +0x00c
    uint32_t                     pad_010[(0x58 - 0x10) / 4];
    goal_pos_rot                 goal;                         // +0x058
    goal_pos_rot                 goal_extra;                   // +0x07c (name guessed)
    uint32_t                     pad_0a0[(0x1ac - 0xa0) / 4];
    ik_goals_data                ik_goals;                     // +0x1ac
    vector_3                     ik_particle;                  // +0x1b0
    vector_3                     ik_particle_rest;             // +0x1bc
    uint32_t                     pad_1c8[(0x2bc - 0x1c8) / 4];
};

struct ik_spine_spline_end                            // size 0x30 (name guessed)
{
    vector_3 coef0;     // +0x00
    vector_3 coef1;     // +0x0c
    vector_3 tangent;   // +0x18
    vector_3 normal;    // +0x24
};

// one altitude entry: the moving body, its target altitude and an enable flag (stride 0xc)
struct ik_altitude
{
    creature_body_instance_data* body;      // +0x00
    float                        altitude;  // +0x04
    unsigned char                enabled;   // +0x08
    unsigned char                pad[3];    // +0x09
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
    ik_constraint*               multi_branch_base_start;   // +0xd0
    ik_constraint*               multi_branch_child_next;   // +0xd4
    ik_altitude                  altitudes[4];      // +0xd8
    int                          num_altitudes;     // +0x108

    ik_constraint(creature_body_instance_data* bi, creature_body_instance_data* bj,
                  float restLength, unsigned long flags);                       // 0x009e68f0
    ik_constraint(const ik_constraint& other);                                  // 0x009be850
};

struct creature_instance_data                         // retail layout (partial)
{
    uint32_t pad_000[0x24c / 4];
    eastl::vector<ik_constraint, eastl::sp_vector_allocator> ik_constraints; // +0x24c
    uint32_t pad_25c[(0x2e4 - 0x25c) / 4];
    eastl::vector<creature_body_instance_data, eastl::sp_vector_allocator> Bodies; // +0x2e4
};

typedef eastl::vector<ik_constraint, eastl::sp_vector_allocator> ik_constraint_vector;

// The original computes each squared distance in x87 double precision: the x component
// is kept unrounded in the FPU, the y/z components are rounded to float first.  The
// three call sites sum the squares in three different orders (a /fp:fast scheduling
// artefact), so the pairings are reproduced literally.
static inline float DistXY_Z(const vector_3& a, const vector_3& b)   // (dx^2 + dy^2) + dz^2
{
    float  dy = a.y - b.y;
    float  dz = a.z - b.z;
    double dx = (double)a.x - (double)b.x;
    return (float)sqrt((dx * dx + (double)dy * dy) + (double)dz * dz);
}

static inline float DistYZ_X(const vector_3& a, const vector_3& b)   // (dy^2 + dz^2) + dx^2
{
    float  dy = a.y - b.y;
    float  dz = a.z - b.z;
    double dx = (double)a.x - (double)b.x;
    return (float)sqrt(((double)dy * dy + (double)dz * dz) + dx * dx);
}

static inline float DistYX_Z(const vector_3& a, const vector_3& b)   // (dy^2 + dx^2) + dz^2
{
    float  dy = a.y - b.y;
    float  dz = a.z - b.z;
    double dx = (double)a.x - (double)b.x;
    return (float)sqrt(((double)dy * dy + dx * dx) + (double)dz * dz);
}

void SetConstraintAltitudes(creature_body_instance_data* a, creature_body_instance_data* b,
                            creature_body_instance_data* c, creature_body_instance_data* d,
                            ik_constraint* con);                                 // 0x009e7a60
bool ComputeAltitudeLine(const vector_3& a, const vector_3& b, const vector_3& c,
                         float* outDist, vector_3* outNormal);                   // 0x009e6e10

// @ 0x009f41b0
unsigned long AddCrossConstraints(creature_instance_data* creature,
                                  creature_body_instance_data* body, unsigned long flags)
{
    ik_constraint_vector& constraints = creature->ik_constraints;
    const int existing = (int)(constraints.mpEnd - constraints.mpBegin);
    const unsigned long conFlags = flags | 0x24;
    unsigned long freeCount = 0;
    creature_body_instance_data* first = 0;
    creature_body_instance_data* second = 0;

    if (body->static_data->num_children == 0)
        return 0;

    unsigned long idx = 0;
    do
    {
        creature_body_instance_data* child =
            &creature->Bodies.mpBegin[body->static_data->first_child_bidx + idx];

        if ((child->ik_goals.TypeAndFlags & 7) != 4)
        {
            ++freeCount;

            if (freeCount == 1)
            {
                first = child;
            }
            else if (freeCount == 2)
            {
                float dist = DistXY_Z(first->ik_particle_rest, child->ik_particle_rest);
                constraints.push_back(ik_constraint(first, child, dist, conFlags));
                second = child;
            }
            else if (freeCount == 3)
            {
                float d1 = DistYZ_X(first->ik_particle_rest, child->ik_particle_rest);
                constraints.push_back(ik_constraint(first, child, d1, conFlags));
                float d2 = DistYZ_X(second->ik_particle_rest, child->ik_particle_rest);
                constraints.push_back(ik_constraint(second, child, d2, conFlags));
                SetConstraintAltitudes(body, first, second, child, &constraints.mpBegin[existing]);
            }
            else
            {
                float d1 = DistYZ_X(first->ik_particle_rest, child->ik_particle_rest);
                constraints.push_back(ik_constraint(first, child, d1, conFlags));
                float d2 = DistYX_Z(second->ik_particle_rest, child->ik_particle_rest);
                constraints.push_back(ik_constraint(second, child, d2, conFlags));
                SetConstraintAltitudes(body, first, second, child,
                                       &constraints.mpBegin[existing + 2 * freeCount - 5]);
            }
        }

        ++idx;
    } while (idx < body->static_data->num_children);

    if (freeCount != 2)
        return freeCount;

    // Exactly two goal-bearing children: complete the single constraint with the three
    // point/line altitudes over (body, first, second).
    ik_constraint* con = &constraints.mpBegin[existing];
    con->altitudes[0].enabled = ComputeAltitudeLine(body->ik_particle_rest, first->ik_particle_rest,
                                                    second->ik_particle_rest,
                                                    &con->altitudes[0].altitude, 0);
    con->altitudes[1].enabled = ComputeAltitudeLine(first->ik_particle_rest, second->ik_particle_rest,
                                                    body->ik_particle_rest,
                                                    &con->altitudes[1].altitude, 0);
    con->altitudes[2].enabled = ComputeAltitudeLine(second->ik_particle_rest, body->ik_particle_rest,
                                                    first->ik_particle_rest,
                                                    &con->altitudes[2].altitude, 0);
    con->altitudes[0].body = body;
    con->altitudes[1].body = first;
    con->altitudes[2].body = second;
    con->num_altitudes = 3;
    return freeCount;
}
} // namespace nSPCreatureAnim
