// Slice s00af8b50 (batch op2_big) — 0x00af8b50, 3910 bytes.
//
// SP::SPDynamicsParticle::StepDeltaTime(float dt, SPSurfaceConstraints* pConstraints)
//   (retail layout; __thiscall, ret 8)
//
// Identification: the only callers (0x00af026d, 0x00af030e) pass `this` = proxy + 0x80,
// where the proxy is the 0x150-byte "Simulator" SP::SPCreatureProxy that
// SP::Havok::CreateHavokEntityForObject (0x00b56090) creates; that function fills
// particle fields +0x40 (gravity, from cPlanetModel), +0x44 (max speed), +0x98 (step
// height), +0xa8 (radius).  The body integrates gravity, slides on steep support
// normals, clamps speed, carries the particle along with a supporting rigid body,
// runs hkSimplexSolverSolve over the given surface constraints (at most 10
// iterations) and then probes the ground (0x00b669b0) to update the support state —
// the shape of the dev build's SP::SPDynamicsParticle::StepDeltaTime (2130 B) grown
// in retail.  Callees without a recovered name keep their FUN_ address names.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (SSE scalar math, x87 only for sqrt and
// the fld/fstp hkVector4 operator= copies).

#include "types.h"
#include <math.h>

#pragma pack(push, 8)

typedef float hkReal;

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
    void operator=(const hkVector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    void setZero4() { x = y = z = w = 0.0f; }
    void set(hkReal a, hkReal b, hkReal c, hkReal d = 0.0f) { x = a; y = b; z = c; w = d; }
    void setAll(hkReal a) { x = a; y = a; z = a; w = a; }
    void setAll3(hkReal a) { x = a; y = a; z = a; w = a; }
    void setTransformedPos(const class hkTransform& t, const hkVector4& v);   // 0x01081360
};

class hkTransform {
public:
    hkVector4 m_col0, m_col1, m_col2, m_translation;
};

struct hkMotion {
    uint32_t pad00[4];
    hkTransform m_transform;                    // +0x10
};

class hkRigidBody {
public:
    uint32_t pad00[0x58 / 4];
    hkMotion* m_motion;                         // +0x58
    uint32_t pad5c[(0x98 - 0x5c) / 4];
    char pad98;
    bool m_isFixedOrKeyframed;                  // +0x99
};

class hkWorld;

struct hkSurfaceConstraintInfo;
struct hkSurfaceConstraintInteraction;

struct hkSimplexSolverInput {
    hkVector4 m_position;                       // +0x0
    hkVector4 m_velocity;                       // +0x10
    hkVector4 m_maxSurfaceVelocity;             // +0x20
    hkVector4 m_upVector;                       // +0x30
    hkReal m_deltaTime;                         // +0x40
    hkReal m_minDeltaTime;                      // +0x44
    hkSurfaceConstraintInfo* m_constraints;     // +0x48
    int m_numConstraints;                       // +0x4c
    hkSimplexSolverInput()
    {
        m_upVector.set(0.0f, 1.0f, 0.0f);
        m_maxSurfaceVelocity.setAll3(1.1920929e-07f);
        m_position.setZero4();
    }
};

struct hkSimplexSolverOutput {
    hkVector4 m_position;                       // +0x0
    hkVector4 m_velocity;                       // +0x10
    hkReal m_deltaTime;                         // +0x20
    hkSurfaceConstraintInteraction* m_planeInteractions;  // +0x24
};

void hkSimplexSolverSolve(const hkSimplexSolverInput& input, hkSimplexSolverOutput& output);  // 0x010A9D30

extern hkVector4 g_hkZeroVector;                                     // 0x016E42D0

namespace SP {

class cPlanetModel {
public:
    float GetWaterHeight();                                          // 0x00B7E390
};

struct SPSurfaceConstraintArray {
    hkSurfaceConstraintInfo* m_data;
    int m_size;
};

struct SPSurfaceConstraints {
    SPSurfaceConstraintArray* m_constraints;
    hkSurfaceConstraintInteraction** m_interactions;
};

// Ground probe used by the particle (0x00b669b0).
struct SPGroundProbe {
    hkVector4 m_position;                       // +0x0
    float m_radius;                             // +0x10
    float m_depth;                              // +0x14
};

struct SPGroundProbeResult {
    int m_type;                                 // +0x0  0 = none
    uint32_t pad04[3];
    hkVector4 m_position;                       // +0x10
    hkVector4* m_normal;                        // +0x20
    float* m_distance;                          // +0x24
    int m_28;                                   // +0x28
    int m_2c;                                   // +0x2c
};

void ProbeGround(const SPGroundProbe* probe, cPlanetModel* planet, hkWorld* world, void* filter,
                 int a, SPGroundProbeResult* result, int b);                           // 0x00B669B0
hkVector4 GetUpVector(const hkVector4& position);                                     // 0x00B65710
void GetSlideVector(const hkVector4& normal, const hkVector4& gravity, hkVector4& out);  // 0x00AF8600
void ResolvePenetration(const hkVector4* probe, const hkVector4* position, hkWorld* world,
                        hkVector4* out);                                               // 0x00AF86C0

extern float g_kParticleMinSpeedSq;                                  // 0x0156733C
extern float g_kParticleSlideAccel;                                  // 0x01567340
extern float g_kParticleMaxSlideCos;                                 // 0x01567334
extern float g_kParticleSupportDistance;                             // 0x01567348

class SPDynamicsParticle {
public:
    uint32_t pad00[4];                          // +0x0 (vtable and header, unused here)
    hkVector4 m_pos;                            // +0x10
    hkVector4 m_vel;                            // +0x20
    float m_mass;                               // +0x30
    float m_friction;                           // +0x34
    float m_38;                                 // +0x38
    bool m_applyGravity;                        // +0x3c
    float m_gravity;                            // +0x40
    float m_maxSpeed;                           // +0x44
    bool m_48;                                  // +0x48
    bool m_49;                                  // +0x49
    bool m_onSteepSlope;                        // +0x4a
    int m_supportState;                         // +0x4c
    hkVector4 m_supportNormal;                  // +0x50
    uint32_t pad60[2];
    hkRigidBody* m_supportBody;                 // +0x68
    uint32_t pad6c;
    hkVector4 m_supportLocalPos;                // +0x70
    hkVector4 m_supportVelocity;                // +0x80
    uint32_t pad90;
    float m_cosMaxClimbableSlope;               // +0x94
    float m_stepHeight;                         // +0x98
    uint32_t m_probeFilter[3];                  // +0x9c
    float m_radius;                             // +0xa8
    float m_probeDepth;                         // +0xac
    hkWorld* m_world;                           // +0xb0
    cPlanetModel* m_planet;                     // +0xb4

    void FUN_00af8840(int a, int b, int c);                          // 0x00AF8840
    void FUN_00af8920(SPGroundProbeResult* result);                  // 0x00AF8920
    void StepDeltaTime(float dt, SPSurfaceConstraints* pConstraints);
};

}  // namespace SP

#pragma pack(pop)

static inline hkReal LengthSquared3(const hkVector4& v) { return v.x * v.x + v.y * v.y + v.z * v.z; }
static inline hkReal Dot3(const hkVector4& a, const hkVector4& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
static __forceinline hkReal SqrtInverse(hkReal r) { return (r == 0.0f) ? 0.0f : (hkReal)(1.0f / sqrt(r)); }

using namespace SP;

void SPDynamicsParticle::StepDeltaTime(float dt, SPSurfaceConstraints* pConstraints)
{
    if (dt <= 0.0f)
        return;

    if (LengthSquared3(m_vel) < g_kParticleMinSpeedSq)
        m_vel.setZero4();

    hkVector4 up = GetUpVector(m_pos);
    hkVector4 gravity;
    {
        hkVector4 g = GetUpVector(m_pos);
        gravity.x = g.x * m_gravity;
        gravity.y = g.y * m_gravity;
        gravity.z = g.z * m_gravity;
        gravity.w = g.w * m_gravity;
    }
    m_onSteepSlope = false;

    hkVector4 vel;
    vel.x = m_vel.x; vel.y = m_vel.y; vel.z = m_vel.z; vel.w = m_vel.w;

    if (m_supportState != 0)
    {
        const hkVector4& n = m_supportNormal;
        if (Dot3(n, up) < m_cosMaxClimbableSlope)
        {
            if (m_applyGravity)
            {
                hkVector4 slide;
                GetSlideVector(n, gravity, slide);
                float k = g_kParticleSlideAccel * dt;
                vel.x += slide.x * k;
                vel.y += slide.y * k;
                vel.z += slide.z * k;
                vel.w += slide.w * k;
            }
            m_onSteepSlope = true;
        }
        float p = -Dot3(n, vel);
        vel.x += n.x * p;
        vel.y += n.y * p;
        vel.z += n.z * p;
        vel.w += n.w * p;
    }
    else if (m_applyGravity)
    {
        vel.x += gravity.x * dt;
        vel.y += gravity.y * dt;
        vel.z += gravity.z * dt;
        vel.w += gravity.w * dt;
    }

    float speedSq = LengthSquared3(vel);
    float maxSpeed = m_maxSpeed;
    if (speedSq > maxSpeed * maxSpeed)
    {
        float k = (float)(maxSpeed / sqrt(speedSq));
        vel.x *= k;
        vel.y *= k;
        vel.z *= k;
        vel.w *= k;
    }

    hkVector4 moveVel;
    moveVel.x = vel.x; moveVel.y = vel.y; moveVel.z = vel.z; moveVel.w = vel.w;

    bool bOnBody;
    if (!m_onSteepSlope && m_supportBody && !m_supportBody->m_isFixedOrKeyframed)
        bOnBody = true;
    else
        bOnBody = false;

    hkVector4 bodyVel;
    bodyVel.setZero4();
    if (bOnBody)
    {
        hkVector4 worldPos;
        worldPos.setTransformedPos(m_supportBody->m_motion->m_transform, m_supportLocalPos);
        float invDt = 1.0f / dt;
        bodyVel.x = invDt * (worldPos.x - m_pos.x);
        bodyVel.y = (worldPos.y - m_pos.y) * invDt;
        bodyVel.z = (worldPos.z - m_pos.z) * invDt;
        bodyVel.w = (worldPos.w - m_pos.w) * invDt;
        moveVel.x = bodyVel.x + vel.x;
        moveVel.y = bodyVel.y + vel.y;
        moveVel.z = bodyVel.z + vel.z;
        moveVel.w = bodyVel.w + vel.w;
    }

    hkVector4 newPos;
    if (pConstraints && pConstraints->m_constraints->m_size > 0)
    {
        hkVector4 pos;
        pos.x = m_pos.x; pos.y = m_pos.y; pos.z = m_pos.z; pos.w = m_pos.w;
        float remaining = dt;
        hkSimplexSolverOutput output;
        for (int iter = 0; remaining > 1.1920929e-07f && iter < 10; iter++)
        {
            hkSimplexSolverInput input;
            input.m_constraints = pConstraints->m_constraints->m_data;
            input.m_numConstraints = pConstraints->m_constraints->m_size;
            input.m_minDeltaTime = 0.0f;
            input.m_position.setZero4();
            input.m_upVector.x = up.x; input.m_upVector.y = up.y; input.m_upVector.z = up.z; input.m_upVector.w = up.w;
            input.m_velocity.x = moveVel.x; input.m_velocity.y = moveVel.y;
            input.m_velocity.z = moveVel.z; input.m_velocity.w = moveVel.w;
            input.m_deltaTime = remaining;
            input.m_maxSurfaceVelocity.setAll(m_maxSpeed);
            output.m_planeInteractions = *pConstraints->m_interactions;
            hkSimplexSolverSolve(input, output);
            pos.x += output.m_position.x;
            pos.y += output.m_position.y;
            pos.z += output.m_position.z;
            pos.w += output.m_position.w;
            remaining -= output.m_deltaTime;
        }
        vel.x = output.m_velocity.x; vel.y = output.m_velocity.y;
        vel.z = output.m_velocity.z; vel.w = output.m_velocity.w;
        if (bOnBody)
        {
            vel.x -= bodyVel.x;
            vel.y -= bodyVel.y;
            vel.z -= bodyVel.z;
            vel.w -= bodyVel.w;
        }
        newPos.x = pos.x; newPos.y = pos.y; newPos.z = pos.z; newPos.w = pos.w;
    }
    else
    {
        newPos.x = moveVel.x * dt + m_pos.x;
        newPos.y = moveVel.y * dt + m_pos.y;
        newPos.z = moveVel.z * dt + m_pos.z;
        newPos.w = moveVel.w * dt + m_pos.w;
    }

    if (pConstraints && m_supportState == 0)
    {
        hkVector4 probe;
        probe.x = up.x * 0.05f + m_pos.x;
        probe.y = up.y * 0.05f + m_pos.y;
        probe.z = up.z * 0.05f + m_pos.z;
        probe.w = up.w * 0.05f + m_pos.w;
        ResolvePenetration(&probe, &newPos, m_world, &newPos);
    }

    SPGroundProbe probe;
    probe.m_position.x = newPos.x; probe.m_position.y = newPos.y;
    probe.m_position.z = newPos.z; probe.m_position.w = newPos.w;
    probe.m_radius = m_radius;
    probe.m_depth = m_probeDepth;
    hkVector4 hitNormal;
    float hitDistance;
    SPGroundProbeResult result;
    result.m_normal = &hitNormal;
    result.m_distance = &hitDistance;
    result.m_28 = 0;
    result.m_2c = 0;
    ProbeGround(&probe, m_planet, m_world, m_probeFilter, 0, &result, 0);

    int contact = 0;
    if (m_supportState != 0)
    {
        if (result.m_type != 0)
        {
            float dx = result.m_position.x - m_pos.x;
            float dy = result.m_position.y - m_pos.y;
            float dz = result.m_position.z - m_pos.z;
            float height = m_supportNormal.z * dz + m_supportNormal.y * dy + dx * m_supportNormal.x;
            contact = 1;
            float step = m_stepHeight;
            if (step > 0.0f)
            {
                if (height > step)
                    contact = 3;
                else if (-step > height)
                    contact = 2;
            }
            if (result.m_type != 3)
            {
                float vSq = LengthSquared3(vel);
                if (vSq > 1e-06f && contact == 1)
                {
                    float d = dx * vel.x + dz * vel.z + dy * vel.y;
                    float invV = SqrtInverse(vSq);
                    float invD = SqrtInverse(dy * dy + dz * dz + dx * dx);
                    if (invD * invV * d < g_kParticleMaxSlideCos &&
                        Dot3(m_supportNormal, up) > Dot3(*result.m_normal, up) &&
                        !(height > 0.0f))
                        contact = 2;
                }
            }
        }
        else
            contact = 0;
    }

    if (m_supportState != 0)
    {
        if (contact == 2)
        {
            m_supportState = 0;
            goto done;
        }
        if (contact == 3)
            goto stop;
    }
    else if (m_48 && m_49)
    {
        float distSq = result.m_position.z * result.m_position.z + result.m_position.y * result.m_position.y +
                       result.m_position.x * result.m_position.x;
        if (result.m_type != 0)
        {
            float dist = (float)sqrt(distSq);
            if (dist > m_planet->GetWaterHeight() - 3.0f)
            {
                float p = -Dot3(m_vel, up);
                float tx = up.x * p + m_vel.x;
                float ty = up.y * p + m_vel.y;
                float tz = up.z * p + m_vel.z;
                const hkVector4& hn = *result.m_normal;
                if (hn.z * tz + hn.y * ty + tx * hn.x <= 0.0f)
                {
                    if (result.m_type == 2 || result.m_type == 3)
                        goto stop;
                }
            }
        }
    }
    else if (result.m_type != 0 && *result.m_distance < 0.01f)
    {
        m_supportState = result.m_type;
    }

done:
    {
        hkVector4 newVel;
        if (m_supportState != 0)
        {
            FUN_00af8920(&result);
            m_supportVelocity.x = bodyVel.x; m_supportVelocity.y = bodyVel.y;
            m_supportVelocity.z = bodyVel.z; m_supportVelocity.w = bodyVel.w;
            m_supportNormal = *result.m_normal;
            float speedSq2 = LengthSquared3(m_vel);
            if (speedSq2 < g_kParticleMinSpeedSq)
            {
                newVel.setZero4();
            }
            else if (m_applyGravity)
            {
                float gn = -Dot3(m_supportNormal, gravity);
                hkVector4 f;
                if (gn > 0.0f)
                {
                    float k = -(m_friction * gn);
                    f.x = k * m_vel.x;
                    f.y = m_vel.y * k;
                    f.z = m_vel.z * k;
                    f.w = m_vel.w * k;
                }
                else
                    f.setZero4();
                f.x *= dt;
                f.y *= dt;
                f.z *= dt;
                f.w *= dt;
                if (LengthSquared3(f) > speedSq2)
                {
                    newVel.x = g_hkZeroVector.x; newVel.y = g_hkZeroVector.y;
                    newVel.z = g_hkZeroVector.z; newVel.w = g_hkZeroVector.w;
                }
                else
                {
                    newVel.x = f.x + vel.x;
                    newVel.y = f.y + vel.y;
                    newVel.z = f.z + vel.z;
                    newVel.w = f.w + vel.w;
                }
            }
            else
            {
                newVel.x = vel.x; newVel.y = vel.y; newVel.z = vel.z; newVel.w = vel.w;
            }
        }
        else
        {
            m_pos.x = newPos.x; m_pos.y = newPos.y; m_pos.z = newPos.z; m_pos.w = newPos.w;
            FUN_00af8840(0, 0, 0);
            if (*result.m_distance < g_kParticleSupportDistance)
                m_supportNormal = *result.m_normal;
            else
                m_supportNormal = GetUpVector(m_pos);
            newVel.x = vel.x; newVel.y = vel.y; newVel.z = vel.z; newVel.w = vel.w;
        }

        m_vel.x = newVel.x;
        m_vel.y = newVel.y;
        m_vel.z = newVel.z;
        m_vel.w = newVel.w;
        if (LengthSquared3(m_vel) < g_kParticleMinSpeedSq)
            m_vel.setZero4();
        return;
    }

stop:
    m_vel.setZero4();
}
