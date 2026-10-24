// Slice s009f3390 -- nSPCreatureAnim IK solver iteration helpers (ik_solver.cpp).
//
//   009f3390  nSPCreatureAnim::IKSolveSpineAlphas   (register-arg: creature in eax)
//   009f3af0  nSPCreatureAnim::IKSolveDistances     (creature at [esp+4])
//   009f3e20  eastl::vector<ik_constraint>::DoInsertValue   (this = vector, args on stack, ret 8)
//   009f3f40  nSPCreatureAnim::AddSerialSpineConstraint      (this = vector, args on stack)
//   009f4100  nSPCreatureAnim::AddSerialSpineConstraints     (creature at [esp+8], this = vector)
//
// The retail build is newer than the 2008 dev PDB (quaternions instead of matrices, bigger
// structs), so the layouts below come from the disassembly; member names follow the dev PDB
// where the order lines up, and the ones marked "(name guessed)" are not confirmed.
//
// 009f3390 and 009f4100 read one of their arguments from a register (eax / edx) instead of the
// stack, so the prototypes on those two are illustrative only; only 009f3af0, 009f3e20 and
// 009f3f40 have a stack ABI that the compilers here reproduce.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <new>

// The retail eastl allocator's allocate() is an out-of-line 6-argument operator new at
// 0x00f473a0: ??2@YAPAXIPBDHI0H@Z (size, name, flags, debugFlags, file, line).
void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);

namespace eastl
{
struct sp_vector_allocator { int mFlags; };

// Minimal EASTL vector: just the members these functions use.
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

inline vector_3 make_v3(float x, float y, float z)
{
    vector_3 r;
    r.x = x; r.y = y; r.z = z;
    return r;
}
} // namespace checkerlib

using namespace checkerlib;

namespace nSPCreatureAnim
{
struct creature_instance_data;
struct creature_body_instance_data;

struct ik_goals_data                                  // size 0x4
{
    unsigned char TypeAndFlags;  // +0x0 (bit 1 = chain continues, bit 2 = no own constraint)
    unsigned char Reserved;      // +0x1
    unsigned char ChildIdx;      // +0x2
    unsigned char NumBIdx;       // +0x3
};

struct creature_body_instance_data;
struct creature_body_static_data                      // retail layout (partial)
{
    uint32_t      pad_000[2];
    creature_body_instance_data* owner;            // +0x008 (body instance this static data belongs to)
    uint32_t      pad_00c[(0x150 - 0xc) / 4];
    unsigned long body_flags;                      // +0x150 (2 = ?, 8 = spine root / anchor)
    uint32_t      pad_154[(0x1ac - 0x154) / 4];
    ik_goals_data ik_goals;                        // +0x1ac
};

struct ik_constraint;

struct creature_body_instance_data                    // size 0x2bc (retail)
{
    creature_body_static_data*   static_data;                  // +0x000
    creature_instance_data*      creature;                     // +0x004
    creature_body_instance_data* parent;                       // +0x008
    creature_body_instance_data* first_child;                  // +0x00c
    uint32_t                     pad_010[(0x94 - 0x10) / 4];
    unsigned long                Flags;                        // +0x094
    uint32_t                     pad_098[(0x150 - 0x98) / 4];
    unsigned long                body_flags;                   // +0x150 (name guessed; 8 = spine anchor)
    uint32_t                     pad_154[(0x19c - 0x154) / 4];
    vector_4                     ik_goal_orientation;          // +0x19c (name guessed)
    ik_goals_data                ik_goals;                     // +0x1ac
    vector_3                     ik_particle;                  // +0x1b0
    vector_3                     ik_particle_rest;             // +0x1bc
    vector_3                     ik_particle_goal;             // +0x1c8
    uint32_t                     pad_1d4[(0x200 - 0x1d4) / 4];
    vector_4                     ik_orientation_rest;          // +0x200 (name guessed)
    float                        ik_invmass;                   // +0x210
    float                        ik_parent_length;             // +0x214
    uint32_t                     pad_218[(0x23c - 0x218) / 4];
    float                        ik_inherit_goals;             // +0x23c
    ik_constraint*               ik_own_spine_constraint;      // +0x240
    ik_constraint*               ik_end_spine_constraint;      // +0x244
    uint32_t                     pad_248[(0x2bc - 0x248) / 4];
};

struct ik_spine_spline_end                            // size 0x30 (name guessed)
{
    vector_3 coef0;     // +0x00
    vector_3 coef1;     // +0x0c
    vector_3 tangent;   // +0x18
    vector_3 normal;    // +0x24
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
    float                        soft_s_min;        // +0x8c
    float                        soft_s_max;        // +0x90
    unsigned long                Flags;             // +0x94
    float                        soft_delta_min;    // +0x98
    float                        soft_delta_max;    // +0x9c
    uint32_t                     pad_0a0[(0xc8 - 0xa0) / 4];
    float                        spine_chord_rest_length; // +0xc8
    int                          spine_count;       // +0xcc
    ik_constraint*               multi_branch_base_start; // +0xd0
    ik_constraint*               multi_branch_child_next; // +0xd4
    uint32_t                     pad_0d8[(0x10c - 0xd8) / 4];

    ik_constraint(creature_body_instance_data* bi, creature_body_instance_data* bj,
                  float restLength, unsigned long flags);                       // 0x009e68f0
    ik_constraint(const ik_constraint& other);                                  // 0x009be850
    void SetSoft(float sMin, float sMax, float deltaMin, float deltaMax);       // 0x009e6b40
};

struct creature_instance_data                         // retail layout (partial)
{
    uint32_t pad_000[0x70 / 4];
    float    requested_scale;                                        // +0x070
    uint32_t pad_074[(0x1b0 - 0x74) / 4];
    float    ik_spine_rest_alpha;                                    // +0x1b0
    float    ik_inherit_goals_blend;                                 // +0x1b4 (name guessed)
    uint32_t pad_1b8[(0x24c - 0x1b8) / 4];
    eastl::vector<ik_constraint, eastl::sp_vector_allocator> ik_constraints; // +0x24c
    uint32_t pad_25c[(0x2e4 - 0x25c) / 4];
    eastl::vector<creature_body_instance_data, eastl::sp_vector_allocator> Bodies; // +0x2e4
};

// --- tunables / debug switches (.data) ---
extern int    g_IKSpineIterations;                 // 0x01550a1c (5)
extern int    g_IKParticleIterations;              // 0x01550a20 (5)
extern int    g_IKEnforceAltitudes;                // 0x01550a24 (1)
extern float  g_IKInheritGoalsMin;                 // 0x01550a2c (0.48)
extern float  g_IKInheritGoalsRate;                // 0x01550a30 (0.3)
extern float  g_IKInheritGoalsBias;                // 0x01550a34 (0.4)
extern int    g_IKRelaxSpineAlphas;                // 0x01550a38 (1)
extern int    g_IKDebugConstraintLimit;            // 0x01550a40 (-1)
extern int    g_IKSpineSoftMode;                   // 0x01550a44 (1)
extern int    g_IKMaxSerialConstraintCount;        // 0x01550a50 (256)
extern float  g_IKSpineSoftAlphaScale;             // 0x01550a54 (0.2)
extern bool   g_IKOrderConstraintsBackward;        // 0x01551630 (1): constraints relaxed backward
extern bool   g_IKOrderLeavesFirst;                // 0x01551631 (1): 009f3af0 body order (leaf first)
extern int    g_IKDebugSplines;                    // 0x0166bff8
extern creature_instance_data* g_IKDebugCreature;  // 0x0166c948

// --- other ik_solver functions (each read their creature/handle from a register) ---
void IKSolveSoftDistance(ik_constraint* c, int iteration, float weight);   // 0x009e7840
void IKEnforceAltitudesClash(ik_constraint* c, int iteration);             // 0x009e7510 (unused)
void IKComputeBodyParticles(creature_instance_data* c, int zero);          // 0x009f1730
void IKWriteParticles(void* handle, creature_instance_data* c);            // 0x009f2970
void* IKGetParticleContext(int unused);                                    // 0x009ed560
void IKSolveParticles(void* ctx, void* particles);                         // 0x009f2a00

// Enforce the altitude limits of one spine-tip body; like IKSolveSpineAlphas its creature
// argument travels in a register, so this is modeled as a plain single-body helper.
void IKEnforceAltitudesBody(creature_body_instance_data* b, int iteration);  // 0x009e7510

// The body whose spine sits above b, one chain level up (0 when b is the chain end).
inline creature_body_instance_data* IKSpineParent(creature_body_instance_data* b)
{
    return b->parent;
}

// Soft constraint of the spine chain that ends at b.
inline ik_constraint* IKEndSpineConstraint(creature_body_instance_data* b)
{
    return b->ik_end_spine_constraint;
}

// ---------------------------------------------------------------------------
// Spine alpha relaxation + distance/inherit solve. `creature` arrives in eax.
// ---------------------------------------------------------------------------
// @ 0x009f3390
void IKSolveSpineAlphas(creature_instance_data* creature, int unused)
{
    const int numBodies    = (int)((creature->Bodies.mpEnd - creature->Bodies.mpBegin)
                                   / (int)sizeof(creature_body_instance_data));
    const int numConstraints = (int)((creature->ik_constraints.mpEnd
                                      - creature->ik_constraints.mpBegin)
                                     / (int)sizeof(ik_constraint));
    creature_body_instance_data* const bodies = creature->Bodies.mpBegin;
    ik_constraint* const constraints = creature->ik_constraints.mpBegin;
    int debugCount = 0;

    for (int iteration = 0; iteration < g_IKSpineIterations; ++iteration)
    {
        if (g_IKDebugSplines != 0 && creature == g_IKDebugCreature)
            fprintf((FILE*)((char*)__iob_func() + 0x40), "%.2f(%.2f) ",
                    (double)creature->ik_spine_rest_alpha, (double)creature->ik_inherit_goals_blend);

        if (g_IKRelaxSpineAlphas != 0)
        {
            // Scale the soft bounds / rest masses of every constraint by the spine alpha.
            for (int i = 0; i < numConstraints; ++i)
            {
                ik_constraint* c = &constraints[i];
                if ((c->Flags & 0x100) != 0)
                {
                    if (c->soft_s_min != 0.0f)
                        c->soft_s_min = (1.0f - creature->ik_spine_rest_alpha) * g_IKSpineSoftAlphaScale;
                }
                else if ((c->Flags & 8) != 0)
                    c->soft_s_max = creature->ik_spine_rest_alpha;
                else if ((c->Flags & 0x10) != 0)
                    c->soft_s_max = 1.0f - creature->ik_spine_rest_alpha;
            }
        }

        // Bodies, root/leaf first (g_IKOrderConstraintsBackward): solve every chain constraint
        // that does not lie on a spine.
        if (g_IKOrderConstraintsBackward)
        {
            for (int i = numBodies - 1; i >= 0; --i)
            {
                if ((bodies[i].Flags & 0x200) != 0)
                    continue;
                if (g_IKDebugConstraintLimit >= 0 && debugCount >= g_IKDebugConstraintLimit)
                    goto done;
                ++debugCount;
                IKSolveSoftDistance(0, iteration, 1.0f);
            }
        }
        else
        {
            for (int i = 0; i < numBodies; ++i)
            {
                if ((bodies[i].Flags & 0x200) != 0)
                    continue;
                if (g_IKDebugConstraintLimit >= 0 && debugCount >= g_IKDebugConstraintLimit)
                    goto done;
                ++debugCount;
                IKSolveSoftDistance(0, iteration, 1.0f);
            }
        }

        float blend = 1.0f;
        if ((int)((creature->Bodies.mpEnd - creature->Bodies.mpBegin)
                  / (int)sizeof(creature_body_instance_data)) > 0)
        {
            // How much of the spine blend each body may inherit from its end constraint.
            for (int i = 0; i < numBodies; ++i)
            {
                creature_body_instance_data* b = &bodies[i];
                ik_constraint* c = b->ik_own_spine_constraint;
                if (c == 0 || (c->Flags & 0x800) != 0)
                    continue;

                ik_constraint* e = b->ik_end_spine_constraint;
                float inv = blend;
                if (e == 0)
                {
                    creature_body_instance_data* p = IKSpineParent(b);
                    if (p == 0 || p->parent != 0)
                        continue;
                    float qx = p->ik_goal_orientation.x;
                    float qy = p->ik_goal_orientation.y;
                    float qz = p->ik_goal_orientation.z;
                    float qw = p->ik_goal_orientation.w;
                    float v = c->invmass_i * qx * qy + c->invmass_j * (qx * qz - qy * qw)
                              + c->invmass_j * (qz * qy - qx * qw);
                    float t0 = (qz * qw + qy * qx) * c->invmass_i;
                    float t1 = (-(qz * qz) + -(qx * qx)) * c->invmass_i;
                    float t2 = c->invmass_j * qx * qz - c->invmass_j * qy * qw
                               + c->invmass_j * qz * qy + c->invmass_j * qx * qw;
                    float inner = (((v * 2.0f + c->invmass_i) * c->spine_spline_j.normal.x
                                    + (t1 * qy + t0 * qz) * 2.0f + c->invmass_i)
                                   * c->spine_spline_i.normal.x)
                                  + ((t2 * 2.0f + c->invmass_j) * c->spine_spline_i.normal.z);
                    inv = -inner * c->inv_chord_length;
                }
                else if ((e->Flags & 0x800) == 0)
                {
                    const ik_constraint* base = b->ik_own_spine_constraint;
                    float chord = e->soft_delta_min;
                    float invLen = base->inv_chord_length;
                    float soft = ((chord * base->spine_spline_i.normal.x
                                   + invLen * base->spine_spline_i.normal.y)
                                  + base->chord.x * base->spine_spline_i.normal.z) * invLen;
                    inv = soft;
                }
                blend = inv;
            }
        }
        creature->ik_inherit_goals_blend = blend;

        if (g_IKRelaxSpineAlphas != 0)
        {
            float a = (1.0f - (blend - g_IKInheritGoalsBias) * g_IKInheritGoalsRate)
                      * creature->ik_spine_rest_alpha;
            if (a <= g_IKInheritGoalsMin)
                a = g_IKInheritGoalsMin;
            if (a > 1.0f)
                a = 1.0f;
            creature->ik_spine_rest_alpha = a;
        }
    }

done:
    if (g_IKDebugSplines != 0 && creature == g_IKDebugCreature)
        fprintf((FILE*)((char*)__iob_func() + 0x40), "\n");

    IKWriteParticles(0, creature);
}

// ---------------------------------------------------------------------------
// Particle distance solve: per iteration, relax the soft chains, then enforce
// the altitude limits from the spine tip down. `creature` is at [esp+4].
// ---------------------------------------------------------------------------
// @ 0x009f3af0
void IKSolveDistances(creature_instance_data* creature, int unused)
{
    const int numBodies = (int)((creature->Bodies.mpEnd - creature->Bodies.mpBegin)
                                / (int)sizeof(creature_body_instance_data));
    creature_body_instance_data* const bodies = creature->Bodies.mpBegin;
    int debugCount = 0;

    IKComputeBodyParticles(creature, (int)(intptr_t)creature->Bodies.mpBegin);

    if (g_IKParticleIterations <= 0)
        goto done;

    for (int iteration = 0; iteration < g_IKParticleIterations; ++iteration)
    {
        int first, step, last;
        if (g_IKOrderLeavesFirst)
        {
            step  = -1;
            first = numBodies - 1;
            last  = -1;
        }
        else
        {
            step  = 1;
            first = 0;
            last  = numBodies;
        }

        for (int i = first; i != last; i += step)
        {
            creature_body_instance_data* b = &bodies[i];
            if ((b->Flags & 0x200) == 0)
                continue;

            if ((b->static_data->owner->static_data->body_flags & 8) != 0)
                b->ik_end_spine_constraint = 0;

            if ((b->Flags & 2) == 0)
            {
                if ((b->Flags & 4) != 0)
                    continue;
                if (g_IKDebugConstraintLimit >= 0 && debugCount >= g_IKDebugConstraintLimit)
                    goto done;
                ++debugCount;
                IKSolveSoftDistance(0, iteration, 1.0f);
                continue;
            }

            const int levels = g_IKSpineSoftMode + 1;
            int level = 0;
            while (level < levels)
            {
                ik_constraint* chain[12];
                int numChain = 0;
                int capacity = 1;
                for (ik_constraint* c = b->ik_own_spine_constraint; c != 0;
                     c = c->multi_branch_child_next)
                {
                    chain[numChain++] = c;
                    ++capacity;
                    capacity *= numChain;
                }
                if (numChain > 12)
                    capacity = 0x7fffffff;

                if (level != 0)
                {
                    int idx = (g_IKSpineSoftMode * i + level - 1) % capacity;
                    for (int k = numChain; k > 0; --k)
                    {
                        int q = idx / k;
                        idx = idx % k;
                        ik_constraint* tmp = chain[k - 1];
                        chain[k - 1] = chain[idx];
                        idx = q;
                        chain[idx] = tmp;
                    }
                }

                for (int k = 0; k < numChain; ++k)
                {
                    if (g_IKDebugConstraintLimit >= 0 && debugCount >= g_IKDebugConstraintLimit)
                        goto done;
                    ++debugCount;
                    IKSolveSoftDistance(chain[k], iteration,
                                        1.0f / (float)(levels - level));
                }
                ++level;
            }

            if (g_IKDebugConstraintLimit >= 0 && debugCount >= g_IKDebugConstraintLimit)
                goto done;
            ++debugCount;
            if ((b->Flags & 4) == 0)
                IKSolveSoftDistance(0, iteration, 1.0f);
        }

        if (g_IKEnforceAltitudes != 0)
        {
            for (int i = numBodies - 1; i >= 0; --i)
            {
                if ((bodies[i].Flags & 0x200) != 0)
                    IKEnforceAltitudesBody(&bodies[i], iteration);
                if (g_IKDebugConstraintLimit >= 0 && debugCount >= g_IKDebugConstraintLimit)
                    goto done;
                ++debugCount;
            }
        }
    }

done:
    IKSolveParticles(IKGetParticleContext((int)(intptr_t)creature->Bodies.mpBegin),
                     creature->Bodies.mpBegin);
}

// ---------------------------------------------------------------------------
// Build one ik_constraint spanning the < maximum> bodies from `start` up to
// `end`, and append it to the vector. Returns the body where the walk stopped.
// ---------------------------------------------------------------------------
// @ 0x009f3f40
creature_body_instance_data* AddSerialSpineConstraint(
    eastl::vector<ik_constraint, eastl::sp_vector_allocator>* constraints,
    creature_body_instance_data* start, creature_body_instance_data* end,
    int maximum)
{
    float parentLength = 0.0f;
    int count = 0;
    creature_body_instance_data* b = start;
    while (b != 0 && b != end && count < maximum)
    {
        parentLength += b->ik_parent_length;
        b = b->parent;
        ++count;
    }

    ik_constraint made(b, start, parentLength, 0x401);
    if (constraints->mpEnd < constraints->mpCapacity)
        ::new (constraints->mpEnd++) ik_constraint(made);
    else
        constraints->push_back(made);

    ik_constraint* c = constraints->mpEnd - 1;
    c->spine_count = count;
    const float dx = start->ik_particle_rest.x - b->ik_particle_rest.x;
    const float dy = start->ik_particle_rest.y - b->ik_particle_rest.y;
    const float dz = start->ik_particle_rest.z - b->ik_particle_rest.z;
    const float restLength = (float)sqrt((double)dz * dz + (double)dy * dy
                                         + (double)dx * dx);
    c->spine_chord_rest_length = restLength;

    const float ratio = (1.0f / restLength) * parentLength;
    const float hi = ratio + 0.7f;
    const float lo = ratio - 0.5f;
    const float maxSoft = (hi <= 5.0f) ? 5.0f : hi;
    const float minSoft = (0.8f <= lo) ? 0.8f : lo;
    c->SetSoft(minSoft - 0.01f, maxSoft + 0.01f, 0.5f, 0.7f);

    return b;
}

// ---------------------------------------------------------------------------
// Split the spine chain that starts at `body` into arcs of at most
// g_IKMaxSerialConstraintCount bodies and build a constraint for each.
// `creature` arrives in edx / on the stack, `constraints` (this) in ecx.
// ---------------------------------------------------------------------------
// @ 0x009f4100
bool AddSerialSpineConstraints(eastl::vector<ik_constraint, eastl::sp_vector_allocator>* constraints,
                               creature_body_instance_data* body)
{
    int count = 0;
    creature_body_instance_data* last = body;
    creature_body_instance_data* next = body->parent;
    while ((body->static_data->ik_goals.TypeAndFlags & 2) != 0 && next != 0)
    {
        last = next;
        next = next->parent;
        ++count;
    }
    if (last->parent != 0)
    {
        last = last->parent;
        ++count;
    }

    if (body == last)
        return false;

    int segments = (int)((float)count / (float)g_IKMaxSerialConstraintCount);
    if ((float)segments < (float)count / (float)g_IKMaxSerialConstraintCount)
        ++segments;

    creature_body_instance_data* walk = body;
    for (int i = 0; i < segments; ++i)
        walk = AddSerialSpineConstraint(constraints, walk, last, g_IKMaxSerialConstraintCount);

    return true;
}

} // namespace nSPCreatureAnim

namespace nSPCreatureAnim {}

// ---------------------------------------------------------------------------
// eastl vector<ik_constraint> grow-and-insert slow path.
// ---------------------------------------------------------------------------
// @ 0x009f3e20
void eastl::vector<nSPCreatureAnim::ik_constraint, eastl::sp_vector_allocator>::DoInsertValue(
    nSPCreatureAnim::ik_constraint* position, const nSPCreatureAnim::ik_constraint& value)
{
    if (mpEnd == mpCapacity)
    {
        unsigned int oldSize = (unsigned int)(mpEnd - mpBegin) / 0x10c;
        unsigned int newSize = (oldSize == 0) ? 1u : oldSize * 2u;
        nSPCreatureAnim::ik_constraint* pNew = 0;
        if (newSize != 0)
        {
            pNew = (nSPCreatureAnim::ik_constraint*)operator new(
                newSize * 0x10c, "EASTL", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\"
                "EASTL\\include\\EASTL/allocator.h", 0xd1);
        }

        nSPCreatureAnim::ik_constraint* pMid =
            (nSPCreatureAnim::ik_constraint*)memmove(pNew, mpBegin, (char*)position - (char*)mpBegin);
        if (pMid != 0)
            ::new (pMid) nSPCreatureAnim::ik_constraint(value);
        nSPCreatureAnim::ik_constraint* pAfter =
            (nSPCreatureAnim::ik_constraint*)memmove(pMid + 1, position,
                                                     (char*)mpEnd - (char*)position);

        if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0)
            operator delete(mpBegin);

        mpBegin    = pNew;
        mpEnd      = pAfter;
        mpCapacity = pNew + newSize;
        return;
    }

    nSPCreatureAnim::ik_constraint* pInsert = position;
    if (position >= mpBegin && position < mpEnd)
        ++pInsert;

    ::new (mpEnd) nSPCreatureAnim::ik_constraint(value);
    memmove(pInsert + 1, pInsert, (char*)mpEnd - (char*)pInsert);
    *pInsert = value;
    ++mpEnd;
}
