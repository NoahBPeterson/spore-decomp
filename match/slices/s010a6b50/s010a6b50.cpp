// Flags: /O2 /MD /Gy /TP /vc71
#include "../s010eb310/hk31_math.h"
#include <math.h>
#include <stddef.h>

#pragma intrinsic(fabs, sqrt)

struct hkSimpleConstraintUtilCollideParams;
class hkSimpleContactConstraintData;

class hkRigidAccumulator
{
public:
    char m_header[0x0c];
    bool m_angularVelocityInWorld;
    char m_padding[3];
    hkVector4 m_linearVelocity;
    hkVector4 m_angularVelocity;
    hkVector4 m_invMasses;
    hkVector4 m_centerOfMass;
    hkRotation m_coreFromWorld;
};

class hkMotion
{
public:
    char m_state[0xd0];
    hkVector4 m_linearVelocity;
    hkVector4 m_angularVelocity;
};

class hkRigidBody
{
public:
    char m_entityHeader[0x58];
    hkMotion* m_motion;
};

struct hkBodyVelocity
{
    hkVector4 m_linear;
    hkVector4 m_angular;
};

struct __declspec(align(16)) hkSimpleConstraintInfoInitInput
{
    hkVector4 m_massRelPos;
    hkRotation m_invInertia;
    hkReal m_invMass;
};

struct hkSimpleConstraintBodyInfo
{
    hkMatrix3 m_rxR;
    hkMatrix3 m_IinvRxR;
    hkReal m_invMass;
    hkReal m_invMassReg;
    hkReal m_padding[2];
};

struct __declspec(align(16)) hkSimpleConstraintInfo
{
    hkSimpleConstraintBodyInfo m_body[2];
    hkMatrix3 m_directions;
    hkMatrix3 m_mC;
    hkMatrix3 m_mCinv;
};

extern "C" void hkSimpleConstraintUtil_InitInfo(const hkSimpleConstraintInfoInitInput& a,
    const hkSimpleConstraintInfoInitInput& b, const hkMatrix3& directions, hkSimpleConstraintInfo& info);
extern "C" hkReal hkSimpleConstraintUtil_Collide(const hkSimpleConstraintInfo& info,
    const hkSimpleConstraintUtilCollideParams& params, hkBodyVelocity& a, hkBodyVelocity& b);

class hkSimpleCollisionResponse
{
public:
    struct SolveSingleOutput2 { hkReal m_impulse; };
    static void solveSingleContact2(const hkContactPoint& contact, const hkSimpleConstraintUtilCollideParams& params,
        hkRigidBody* bodyA, hkRigidBody* bodyB, hkRigidAccumulator* accA, hkRigidAccumulator* accB,
        hkSimpleContactConstraintData& data, SolveSingleOutput2& out);
};

typedef char InitInputStride[(sizeof(hkSimpleConstraintInfoInitInput) == 0x50) ? 1 : -1];
typedef char ConstraintInfoSize[(sizeof(hkSimpleConstraintInfo) == 0x170) ? 1 : -1];
typedef char AccumulatorRotationOffset[(offsetof(hkRigidAccumulator, m_coreFromWorld) == 0x50) ? 1 : -1];

// hkVector4::setZero4 on one column of an hkMatrix3 (m_el[col*4 .. col*4+3]).
static __forceinline void setZero4(float* v)
{
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
}

// hkMatrix3::setZero: column by column (the order fixes which address the loop's input pointer is based on).
static __forceinline void zeroInertia(hkMatrix3& matrix)
{
    setZero4(matrix.m_el + 0);
    setZero4(matrix.m_el + 4);
    setZero4(matrix.m_el + 8);
}

static __forceinline void _setRotatedInverseDir(hkVector4& out, const hkRotation& r, const hkVector4& v)
{
    const float* m = r.m_el;
    float vx = v.x, vy = v.y, vz = v.z;
    out.x = (vz * m[2] + vy * m[1]) + vx * m[0];
    out.y = (vz * m[6] + vy * m[5]) + vx * m[4];
    out.z = (vz * m[10] + vy * m[9]) + vx * m[8];
    float& w = out.w;
    w = 0.0f;
}

static __forceinline void copyVelocity(hkVector4& dest, const hkVector4& src)
{
    dest.x = src.x;
    dest.y = src.y;
    dest.z = src.z;
    dest.w = src.w;
}

static __forceinline void writeVelocity(hkRigidBody* body, hkRigidAccumulator* acc, const hkBodyVelocity& velocity)
{
    copyVelocity(acc->m_linearVelocity, velocity.m_linear);
    copyVelocity(body->m_motion->m_linearVelocity, velocity.m_linear);
    copyVelocity(body->m_motion->m_angularVelocity, velocity.m_angular);
}

// The two writebacks group the dot products differently in the x87 build.
template <bool secondBody>
static __forceinline void writeAngularVelocity(hkRigidAccumulator& acc, const hkBodyVelocity& vel)
{
    if (acc.m_angularVelocityInWorld)
        copyVelocity(acc.m_angularVelocity, vel.m_angular);
    else
    {
        const float* r = acc.m_coreFromWorld.m_el;
        float* av = &acc.m_angularVelocity.x;
        const float vy = vel.m_angular.y;
        const float vz = vel.m_angular.z;
        const float vx = vel.m_angular.x;
        av[0] = (vz * r[8] + vy * r[4]) + vx * r[0];
        if (secondBody)
        {
            av[1] = (vz * r[9] + vy * r[5]) + vx * r[1];
            av[2] = (vz * r[10] + vy * r[6]) + vx * r[2];
        }
        else
        {
            av[1] = (vx * r[1] + vz * r[9]) + vy * r[5];
            av[2] = (vx * r[2] + vz * r[10]) + vy * r[6];
        }
        acc.m_angularVelocity.w = 0.0f;
    }
}

// Perpendicular of `in` in its two largest components (unnormalised): the least-magnitude component is dropped.
static __forceinline void calculatePerpendicular(const hkVector4& in, float* tangent)
{
    // Drop the least-magnitude component to build a stable perpendicular.
    int least = 0;
    int first = 1;
    int second = 2;
    float minAbs = fabsf(in.x);
    const float absY = fabsf(in.y);
    const float absZ = fabsf(in.z);
    if (absY < minAbs)
    {
        first = 0;
        least = 1;
        minAbs = absY;
    }
    if (absZ < minAbs)
    {
        second = least;
        least = 2;
    }

    tangent[least] = 0.0f;
    tangent[3] = 0.0f;
    const float* normalComponents = &in.x;
    tangent[first] = normalComponents[second];
    tangent[second] = -normalComponents[first];
}

// @ 0x010a6b50
void hkSimpleCollisionResponse::solveSingleContact2(const hkContactPoint& contact,
    const hkSimpleConstraintUtilCollideParams& params, hkRigidBody* bodyA, hkRigidBody* bodyB,
    hkRigidAccumulator* accA, hkRigidAccumulator* accB, hkSimpleContactConstraintData&, SolveSingleOutput2& out)
{
    __declspec(align(16)) hkBodyVelocity velocities[2];
    hkSimpleConstraintInfoInitInput inputs[2];
    __declspec(align(16)) hkMatrix3 scaledRotation;
    __declspec(align(16)) hkMatrix3 directions;
    hkSimpleConstraintInfo info;

    const hkRigidAccumulator* acc = accA;
    hkBodyVelocity* velocity = velocities;
    hkSimpleConstraintInfoInitInput* input = inputs;
    int remaining = 2;
    do
    {
        input->m_invMass = acc->m_invMasses.w;
        input->m_massRelPos.x = contact.m_position.x - acc->m_centerOfMass.x;
        input->m_massRelPos.y = contact.m_position.y - acc->m_centerOfMass.y;
        input->m_massRelPos.z = contact.m_position.z - acc->m_centerOfMass.z;
        input->m_massRelPos.w = contact.m_position.w - acc->m_centerOfMass.w;
        copyVelocity(velocity->m_linear, acc->m_linearVelocity);

        if (acc->m_angularVelocityInWorld)
        {
            copyVelocity(velocity->m_angular, acc->m_angularVelocity);
            zeroInertia(input->m_invInertia);
            input->m_invInertia.m_el[0] = acc->m_invMasses.x;
            input->m_invInertia.m_el[5] = acc->m_invMasses.y;
            input->m_invInertia.m_el[10] = acc->m_invMasses.z;
        }
        else
        {
            _setRotatedInverseDir(velocity->m_angular, acc->m_coreFromWorld, acc->m_angularVelocity);
            const float* r = acc->m_coreFromWorld.m_el;

            // Scale the rotation columns by the principal inverse inertias.
            const float ix = acc->m_invMasses.x;
            const float iy = acc->m_invMasses.y;
            const float iz = acc->m_invMasses.z;
            int i;
            for (i = 0; i < 4; ++i)
                scaledRotation.m_el[i] = ix * r[i];
            for (i = 4; i < 8; ++i)
                scaledRotation.m_el[i] = iy * r[i];
            for (i = 8; i < 12; ++i)
                scaledRotation.m_el[i] = iz * r[i];
            input->m_invInertia.setMulInverse(scaledRotation, acc->m_coreFromWorld);
            input->m_invInertia.transpose();
        }
        acc = accB;
        ++input;
        ++velocity;
    } while (--remaining);

    const hkVector4& normal = contact.m_separatingNormal;
    directions.m_el[0] = normal.x;
    directions.m_el[1] = normal.y;
    directions.m_el[2] = normal.z;
    directions.m_el[3] = normal.w;

    float* tangent = directions.m_el + 4;
    calculatePerpendicular(contact.m_separatingNormal, tangent);
    const float lengthSquared = tangent[0] * tangent[0] +
        tangent[1] * tangent[1] + tangent[2] * tangent[2];
    const float invLength = lengthSquared != 0.0f ? 1.0f / (float)sqrt(lengthSquared) : 0.0f;
    tangent[0] *= invLength;
    tangent[1] *= invLength;
    tangent[2] *= invLength;
    tangent[3] *= invLength;

    directions.m_el[11] = 0.0f;
    const float bitangentY = tangent[0] * normal.z - tangent[2] * normal.x;
    const float bitangentZ = tangent[1] * normal.x - tangent[0] * normal.y;
    const float bitangentX = tangent[2] * normal.y - tangent[1] * normal.z;
    directions.m_el[8] = bitangentX;
    directions.m_el[9] = bitangentY;
    directions.m_el[10] = bitangentZ;

    hkSimpleConstraintUtil_InitInfo(inputs[0], inputs[1], directions, info);
    out.m_impulse = hkSimpleConstraintUtil_Collide(info, params, velocities[0], velocities[1]);

    writeVelocity(bodyA, accA, velocities[0]);
    writeVelocity(bodyB, accB, velocities[1]);
    writeAngularVelocity<false>(*accA, velocities[0]);
    writeAngularVelocity<true>(*accB, velocities[1]);
}
