// Slice s009e6e10 -- ik_solver.cpp altitude + soft-distance constraint solvers
// (nSPCreatureAnim).  Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

namespace nSPCreatureAnim
{

struct vector_3 { float x, y, z; };
struct vector_4 { float x, y, z, w; };

struct creature_body_instance_data;

// one altitude entry: the moving body, its target altitude and an enable flag (stride 0xc)
struct ik_altitude
{
    creature_body_instance_data* body;   // +0x00
    float                        altitude; // +0x04
    unsigned char                enabled;  // +0x08
    unsigned char                pad[3];   // +0x09
};

struct ik_constraint
{
    uint32_t      pad_000[2];             // +0x00
    vector_3*     p_i;                    // +0x08
    vector_3*     p_j;                    // +0x0c
    float         rest_length;            // +0x10
    uint32_t      pad_014[(0x7c - 0x14) / 4];
    vector_3      chord;                  // +0x7c
    float         inv_chord_length;       // +0x88
    float         invmass_i;              // +0x8c
    float         invmass_j;              // +0x90
    unsigned long Flags;                  // +0x94
    float         soft[12];               // +0x98
    uint32_t      pad_c8[4];              // +0xc8
    ik_altitude   altitudes[4];           // +0xd8
    int           num_altitudes;          // +0x108
};

struct creature_body_instance_data
{
    uint32_t  pad_000[0x1b0 / 4];
    vector_3  ik_particle;                // +0x1b0
    vector_3  ik_particle_rest;           // +0x1bc
    uint32_t  pad_1c8[(0x210 - 0x1c8) / 4];
    float     ik_invmass;                 // +0x210
};

// debug switches / tunables (.data)
extern int g_IKAltitudeNormalize;      // 0x01550a4c (1)
extern int g_IKPermuteAltitudesNum;    // 0x01550a48 (1)

// fast inverse square root (integer bit hack, as in the original)
static inline float rsqrt_fast(float x)
{
    union { float f; int i; } u;
    u.f = x;
    u.i = 0x5f375a86 - (u.i >> 1);
    float y = u.f;
    return y * (1.5f - ((x * 0.5f) * y) * y);
}

// Distance from point C to line AB: returns the perpendicular distance and the
// unit direction from the line towards C.  false when the triangle degenerates.
// @ 0x009e6e10
bool ComputeAltitudeLine(const vector_3& a, const vector_3& b, const vector_3& c,
                                float* outDist, vector_3* outNormal)
{
    vector_3 u;
    u.x = c.x - a.x; u.y = c.y - a.y; u.z = c.z - a.z;
    vector_3 v;
    v.x = b.x - a.x; v.y = b.y - a.y; v.z = b.z - a.z;
    vector_3 n;
    n.x = v.y * u.z - v.z * u.y;
    n.y = v.z * u.x - v.x * u.z;
    n.z = v.x * u.y - v.y * u.x;
    if (1e-5 < ((double)n.x * n.x + (double)n.y * n.y) + (double)n.z * n.z)
    {
        vector_3 m;
        m.x = n.y * v.z - n.z * v.y;
        m.y = n.z * v.x - n.x * v.z;
        m.z = n.x * v.y - n.y * v.x;
        float inv = (float)(1.0 / (sqrt(((double)m.x * m.x + (double)m.y * m.y) + (double)m.z * m.z) + 1e-08f));
        m.x *= inv; m.y *= inv; m.z *= inv;
        *outDist = (m.z * u.z + m.y * u.y) + m.x * u.x;
        if (outNormal)
        {
            outNormal->x = m.x;
            outNormal->y = m.y;
            outNormal->z = m.z;
        }
        return true;
    }
    return false;
}

// Signed distance of point D from the plane through A, B, C; normal is the
// normalized (B-A)x(C-A).  false when the triangle degenerates.
// @ 0x009e6fa0
bool ComputeAltitudePlane(const vector_3& a, const vector_3& b, const vector_3& c,
                                 const vector_3& d, float* outDist, vector_3* outNormal)
{
    vector_3 u;
    u.x = c.x - a.x; u.y = c.y - a.y; u.z = c.z - a.z;
    vector_3 v;
    v.x = b.x - a.x; v.y = b.y - a.y; v.z = b.z - a.z;
    vector_3 n;
    n.x = v.y * u.z - v.z * u.y;
    n.y = v.z * u.x - v.x * u.z;
    n.z = v.x * u.y - v.y * u.x;
    float n2 = (n.x * n.x + n.y * n.y) + n.z * n.z;
    if (1e-5 < n2)
    {
        float inv = (float)(1.0 / (sqrt((double)n2) + 1e-08f));
        n.x *= inv; n.y *= inv; n.z *= inv;
        *outDist = (n.z * (d.z - a.z) + n.y * (d.y - a.y)) + n.x * (d.x - a.x);
        if (outNormal)
        {
            outNormal->x = n.x;
            outNormal->y = n.y;
            outNormal->z = n.z;
        }
        return true;
    }
    return false;
}

// @ 0x009e7100
void SolveAltitudeLine(creature_body_instance_data* b0, creature_body_instance_data* b1,
                              creature_body_instance_data* b2, float dist, float weight)
{
    if (g_IKAltitudeNormalize == 0 || 0.0f < b2->ik_invmass ||
        (0.0f < b0->ik_invmass && 0.0f < b1->ik_invmass))
    {
        float cur;
        vector_3 normal = { 0.0f, 0.0f, 0.0f };
        ComputeAltitudeLine(b0->ik_particle, b1->ik_particle, b2->ik_particle, &cur, &normal);
        float err = dist - cur;
        float f = (b0->ik_invmass * err) * weight * 0.5f;
        b0->ik_particle.x -= normal.x * f;
        b0->ik_particle.y -= normal.y * f;
        b0->ik_particle.z -= normal.z * f;
        f = (b1->ik_invmass * err) * weight * 0.5f;
        b1->ik_particle.x -= normal.x * f;
        b1->ik_particle.y -= normal.y * f;
        b1->ik_particle.z -= normal.z * f;
        f = (b2->ik_invmass * err) * weight * 0.5f;
        b2->ik_particle.x += normal.x * f;
        b2->ik_particle.y += normal.y * f;
        b2->ik_particle.z += normal.z * f;
    }
}

// @ 0x009e72b0
void SolveAltitudePlane(creature_body_instance_data* b0, creature_body_instance_data* b1,
                               creature_body_instance_data* b2, creature_body_instance_data* b3,
                               float dist, float weight)
{
    if (g_IKAltitudeNormalize == 0 || 0.0f < b3->ik_invmass ||
        (0.0f < b0->ik_invmass && 0.0f < b1->ik_invmass && 0.0f < b2->ik_invmass))
    {
        float cur;
        vector_3 normal = { 0.0f, 0.0f, 0.0f };
        ComputeAltitudePlane(b0->ik_particle, b1->ik_particle, b2->ik_particle, b3->ik_particle,
                             &cur, &normal);
        float err = dist - cur;
        float f = (b0->ik_invmass * err) * weight * 0.5f;
        b0->ik_particle.x -= normal.x * f;
        b0->ik_particle.y -= normal.y * f;
        b0->ik_particle.z -= normal.z * f;
        f = (b1->ik_invmass * err) * weight * 0.5f;
        b1->ik_particle.x -= normal.x * f;
        b1->ik_particle.y -= normal.y * f;
        b1->ik_particle.z -= normal.z * f;
        f = (b2->ik_invmass * err) * weight * 0.5f;
        b2->ik_particle.x -= normal.x * f;
        b2->ik_particle.y -= normal.y * f;
        b2->ik_particle.z -= normal.z * f;
        f = (b3->ik_invmass * err) * weight * 0.5f;
        b3->ik_particle.x += normal.x * f;
        b3->ik_particle.y += normal.y * f;
        b3->ik_particle.z += normal.z * f;
    }
}

// @ 0x009e7510
void EnforceAltitudes(ik_constraint* con, int seed)
{
    int n = con->num_altitudes;
    if (n == 3)
    {
        if (con->altitudes[0].enabled)
            SolveAltitudeLine(con->altitudes[0].body, con->altitudes[1].body,
                              con->altitudes[2].body, con->altitudes[0].altitude, 1.0f);
        if (con->altitudes[1].enabled)
            SolveAltitudeLine(con->altitudes[1].body, con->altitudes[2].body,
                              con->altitudes[0].body, con->altitudes[1].altitude, 1.0f);
        if (con->altitudes[2].enabled)
            SolveAltitudeLine(con->altitudes[2].body, con->altitudes[0].body,
                              con->altitudes[1].body, con->altitudes[2].altitude, 1.0f);
    }
    else if (n == 4 && (con->altitudes[0].enabled || con->altitudes[1].enabled))
    {
        int numIter = g_IKPermuteAltitudesNum + 1;
        for (int i = 0; i < numIter; ++i)
        {
            int order[4] = { 2, 3, 1, 0 };
            if (i != 0)
            {
                int p = (g_IKPermuteAltitudesNum * seed + i - 1) % 24;
                for (int j = 3; j >= 0; --j)
                {
                    int r = p % (j + 1);
                    p /= (j + 1);
                    int t = order[j];
                    order[j] = order[r];
                    order[r] = t;
                }
            }
            float w = 1.0f / (float)(numIter - i);
            for (int k = 0; k < 4; ++k)
            {
                switch (order[k])
                {
                case 0:
                    if (con->altitudes[0].enabled)
                        SolveAltitudePlane(con->altitudes[0].body, con->altitudes[1].body,
                                           con->altitudes[2].body, con->altitudes[3].body,
                                           con->altitudes[0].altitude, w);
                    break;
                case 1:
                    if (con->altitudes[1].enabled)
                        SolveAltitudePlane(con->altitudes[0].body, con->altitudes[3].body,
                                           con->altitudes[1].body, con->altitudes[2].body,
                                           con->altitudes[1].altitude, w);
                    break;
                case 2:
                    if (con->altitudes[2].enabled)
                        SolveAltitudePlane(con->altitudes[0].body, con->altitudes[2].body,
                                           con->altitudes[3].body, con->altitudes[1].body,
                                           con->altitudes[2].altitude, w);
                    break;
                case 3:
                    if (con->altitudes[3].enabled)
                        SolveAltitudePlane(con->altitudes[1].body, con->altitudes[3].body,
                                           con->altitudes[2].body, con->altitudes[0].body,
                                           con->altitudes[3].altitude, w);
                    break;
                }
            }
        }
    }
}

// @ 0x009e7840
void SolveSoftDistance(ik_constraint* con, int seed, float weight)
{
    if (con->Flags & 0x80)
        return;
    vector_3 chord;
    chord.x = con->p_j->x - con->p_i->x;
    chord.y = con->p_j->y - con->p_i->y;
    chord.z = con->p_j->z - con->p_i->z;
    con->chord = chord;
    float lenSq = chord.x * chord.x + chord.y * chord.y + chord.z * chord.z + 1e-08f;
    float inv = rsqrt_fast(lenSq);
    con->inv_chord_length = inv;
    float t = inv * con->rest_length;
    if (con->Flags & 0x400)
    {
        if (con->soft[0] < t)
        {
            if (t < con->soft[2])
            {
                t = (con->soft[3] * t + con->soft[4]) * t + con->soft[5];
            }
            else if (t <= con->soft[6])
            {
                return;
            }
            else if (t < con->soft[10])
            {
                t = (con->soft[7] * t + con->soft[8]) * t + con->soft[9];
            }
            else
            {
                t = con->soft[11] * t;
            }
        }
        else
        {
            t = con->soft[1] * t;
        }
    }
    float f = (1.0f - t) * weight * 0.5f;
    float fi = con->invmass_i * f;
    con->p_i->x += chord.x * fi;
    con->p_i->y += chord.y * fi;
    con->p_i->z += chord.z * fi;
    float fj = con->invmass_j * f;
    con->p_j->x -= chord.x * fj;
    con->p_j->y -= chord.y * fj;
    con->p_j->z -= chord.z * fj;
}

// @ 0x009e7a60
void SetConstraintAltitudes(creature_body_instance_data* a, creature_body_instance_data* b,
                                   creature_body_instance_data* c, creature_body_instance_data* d,
                                   ik_constraint* con)
{
    if (d == 0)
    {
        con->altitudes[0].enabled =
            ComputeAltitudeLine(a->ik_particle_rest, b->ik_particle_rest, c->ik_particle_rest,
                                &con->altitudes[0].altitude, 0);
        con->altitudes[1].enabled =
            ComputeAltitudeLine(b->ik_particle_rest, c->ik_particle_rest, a->ik_particle_rest,
                                &con->altitudes[1].altitude, 0);
        con->altitudes[2].enabled =
            ComputeAltitudeLine(c->ik_particle_rest, a->ik_particle_rest, b->ik_particle_rest,
                                &con->altitudes[2].altitude, 0);
        con->altitudes[0].body = a;
        con->altitudes[1].body = b;
        con->altitudes[2].body = c;
        con->num_altitudes = 3;
    }
    else
    {
        con->altitudes[0].enabled =
            ComputeAltitudePlane(a->ik_particle_rest, b->ik_particle_rest, c->ik_particle_rest,
                                 d->ik_particle_rest, &con->altitudes[0].altitude, 0);
        con->altitudes[1].enabled =
            ComputeAltitudePlane(a->ik_particle_rest, d->ik_particle_rest, b->ik_particle_rest,
                                 c->ik_particle_rest, &con->altitudes[1].altitude, 0);
        con->altitudes[2].enabled =
            ComputeAltitudePlane(a->ik_particle_rest, c->ik_particle_rest, d->ik_particle_rest,
                                 b->ik_particle_rest, &con->altitudes[2].altitude, 0);
        con->altitudes[3].enabled =
            ComputeAltitudePlane(b->ik_particle_rest, d->ik_particle_rest, c->ik_particle_rest,
                                 a->ik_particle_rest, &con->altitudes[3].altitude, 0);
        con->altitudes[0].body = a;
        con->altitudes[1].body = b;
        con->altitudes[2].body = c;
        con->altitudes[3].body = d;
        con->num_altitudes = 4;
    }
}

} // namespace nSPCreatureAnim
