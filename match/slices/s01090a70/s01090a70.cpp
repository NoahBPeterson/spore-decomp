// Havok 3.1.0 slice s01090a70 (0x01090A70..0x01091A36): the hkSphereMotion motion virtuals
// (applyPointImpulse, applyAngularImpulse, a scaled angular-impulse helper, applyForcesAndStep,
// applyForcesAndBuildAccumulator, applyAccumulator, clone), the hkSpatialRigidBodyDeactivator
// constructor and its two deactivation predicates, and hkQuaternion::setMulInverse.
//
// Toolchain: the shipped module was built by cl 13.10 (VC .NET 2003); the slice compiles with
// /vc71 /O2 /MD /Gy /TP. All floating point is scalar x87 with 0x1485378/0x1485720 (0.0f/1.0f)
// and the polynomial constants below read straight out of the read-only pool.
#include "s01090a70.h"
#include <math.h>
#include <new>

// ---------------------------------------------------------------------------------------------------------
// constant pool referenced by the x87 math (extern "C" keeps the relocation, the VA comment is what the
// difftest resolver binds it to).
// ---------------------------------------------------------------------------------------------------------
extern "C" const float g_hkZero_01485378;      // 0x01485378
extern "C" const float g_hkOne_01485720;       // 0x01485720
extern "C" const float g_hkHalf_01471064;      // 0x01471064
extern "C" const float g_hkSinScale_0149e068;  // 0x0149e068
extern "C" const float g_hkQuatC1_0149e064;    // 0x0149e064
extern "C" const float g_hkQuatC2_0149e060;    // 0x0149e060
extern "C" const float g_hkQuatC3_0149e05c;    // 0x0149e05c
extern "C" const float g_hkPi_014a1a20;        // 0x014a1a20
extern "C" const float g_hkMaxAngle_013ec4b4;  // 0x013ec4b4

// identity transform used while cloning motions (position 0x016E42D0, rotation 0x015B9B50).
extern "C" const float g_identityPos_016e42d0[4];    // 0x016e42d0
extern "C" const float g_identityQuat_015b9b50[4];   // 0x015b9b50

// hkMemory::s_instance lives at 0x016E4178 (the shared b005 header only declares it).
hkMemory* hkMemory::s_instance;                      // 0x016e4178

// Floor-to-zero clamp the original keeps on the x87 stack (fsubr 1.0 / fcomp 0.0 / keep >= 0.0).
static inline float hkFloorZero(float v) { return g_hkZero_01485378 > v ? g_hkZero_01485378 : v; }

// =========================================================================================================
// hkSphereMotion virtuals
// =========================================================================================================

// @ 0x01090a70
void hkSphereMotionEx::applyPointImpulse(const hkVector4& impulse, const hkVector4& pos)
{
    float mInv = m_massInv;
    hkVector4& lv = m_linearVelocity;
    lv.x = mInv * impulse.x + lv.x;
    lv.y = mInv * impulse.y + lv.y;
    lv.z = mInv * impulse.z + lv.z;
    lv.w = mInv * impulse.w + lv.w;

    // torque arm about the centre of mass, then the cross product with the impulse
    const hkMotionState::hkSweptTransform& swept = m_motionState.m_sweptTransform;
    hkVector4 relPos;
    relPos.x = pos.x - swept.m_centerOfMass1.x;
    relPos.y = pos.y - swept.m_centerOfMass1.y;
    relPos.z = pos.z - swept.m_centerOfMass1.z;

    hkVector4 cross;
    cross.x = relPos.y * impulse.z - relPos.z * impulse.y;
    cross.y = relPos.z * impulse.x - relPos.x * impulse.z;
    cross.z = relPos.x * impulse.y - relPos.y * impulse.x;
    cross.w = 0.0f;

    hkVector4& av = m_angularVelocity;
    float inertia = m_particleMinInertiaDiagInv;
    av.x = inertia * cross.x + av.x;
    av.y = inertia * cross.y + av.y;
    av.z = inertia * cross.z + av.z;
    av.w = inertia * cross.w + av.w;
}

// @ 0x01090b50
void hkSphereMotionEx::applyAngularImpulse(const hkVector4& impulse)
{
    hkVector4& v = m_angularVelocity;
    float inertia = m_particleMinInertiaDiagInv;
    v.x = inertia * impulse.x + v.x;
    v.y = inertia * impulse.y + v.y;
    v.z = inertia * impulse.z + v.z;
    v.w = inertia * impulse.w + v.w;
}

// @ 0x01090ba0
void hkSphereMotionEx::applyAngularImpulseScaled(float scale, const hkVector4& impulse)
{
    hkVector4 scaled;
    scaled.x = scale * impulse.x;
    scaled.y = scale * impulse.y;
    scaled.z = scale * impulse.z;
    scaled.w = scale * impulse.w;
    applyAngularImpulse(scaled);
}

// @ 0x01090bf0
void* hkSphereMotionEx::applyForcesAndBuildAccumulator(const hkStepInfo& stepInfo, hkVelocityAccumulator* acc)
{
    float dt = stepInfo.m_deltaTime;
    float linScale = hkFloorZero(g_hkOne_01485720 - dt * m_linearDamping);
    m_linearVelocity.x = linScale * m_linearVelocity.x;
    m_linearVelocity.y = linScale * m_linearVelocity.y;
    m_linearVelocity.z = linScale * m_linearVelocity.z;
    m_linearVelocity.w = linScale * m_linearVelocity.w;
    float angScale = hkFloorZero(g_hkOne_01485720 - dt * m_angularDamping);
    m_angularVelocity.x = angScale * m_angularVelocity.x;
    m_angularVelocity.y = angScale * m_angularVelocity.y;
    m_angularVelocity.z = angScale * m_angularVelocity.z;
    m_angularVelocity.w = angScale * m_angularVelocity.w;

    acc->m_islandIndex = 0;
    float invI = m_particleMinInertiaDiagInv;
    acc->m_invMass.x = invI;
    acc->m_invMass.y = invI;
    acc->m_invMass.z = invI;
    acc->m_invMass.w = m_massInv;

    // interpolate the swept centre of mass between the two stored samples
    const hkMotionState::hkSweptTransform& swept = m_motionState.m_sweptTransform;
    const hkVector4& com0 = swept.m_centerOfMass0;
    const hkVector4& com1 = swept.m_centerOfMass1;
    float t = (stepInfo.m_startTime - com0.w) * com1.w;
    float g = g_hkOne_01485720 - t;
    acc->m_sweptCenterOfMass.x = g * com0.x + t * com1.x;
    acc->m_sweptCenterOfMass.y = g * com0.y + t * com1.y;
    acc->m_sweptCenterOfMass.z = g * com0.z + t * com1.z;
    acc->m_sweptCenterOfMass.w = g * com0.w + t * com1.w;

    acc->m_angularVelocity.x = m_angularVelocity.x;
    acc->m_angularVelocity.y = m_angularVelocity.y;
    acc->m_angularVelocity.z = m_angularVelocity.z;
    acc->m_angularVelocity.w = m_angularVelocity.w;
    acc->m_linearVelocity.x = m_linearVelocity.x;
    acc->m_linearVelocity.y = m_linearVelocity.y;
    acc->m_linearVelocity.z = m_linearVelocity.z;
    acc->m_linearVelocity.w = m_linearVelocity.w;

    acc->m_rotation.m_col0.x = 0.0f;
    acc->m_rotation.m_col0.y = 0.0f;
    acc->m_rotation.m_col0.z = 0.0f;
    acc->m_rotation.m_col0.w = 0.0f;
    acc->m_rotation.m_col1.x = 0.0f;
    acc->m_rotation.m_col1.y = 0.0f;
    acc->m_rotation.m_col1.z = 0.0f;
    acc->m_rotation.m_col1.w = 0.0f;
    acc->m_rotation.m_col2.x = 0.0f;
    acc->m_rotation.m_col2.y = 0.0f;
    acc->m_rotation.m_col2.z = 0.0f;
    acc->m_rotation.m_col2.w = 0.0f;
    acc->m_rotation.m_col0.x = 1.0f;
    acc->m_rotation.m_col1.y = 1.0f;
    acc->m_rotation.m_col2.z = 1.0f;

    acc->m_isValid = 1;
    acc->m_deactivationClass = (uint32_t)m_motionState.m_deactivationClass;
    acc->m_deactivationCounter = (uint32_t)m_motionState.m_deactivationCounter;
    return (char*)acc + 0x80;
}

// @ 0x01090dc0
hkMotion* hkSphereMotionEx::clone() const
{
    hkSphereMotionEx* p = (hkSphereMotionEx*)hkMemory::s_instance->allocateChunk(0xf0, 0x2b);
    p->m_memSizeAndFlags = (hkInt16)0xf0;
    new (p) hkRigidMotion(*(const hkVector4*)&g_identityPos_016e42d0,
                          *(const hkQuaternion*)&g_identityQuat_015b9b50);
    *(const void**)p = (const void*)0x0149df10;
    hkString::memCpy((char*)p + 8, (const char*)this + 8, 0xe8);
    return p;
}

// @ 0x01090e30
void hkSphereMotionEx::applyForcesAndStep(const hkStepInfo& stepInfo, const hkVector4& force)
{
    // velocity damping (the force is folded in first, then the whole vector is scaled)
    m_linearVelocity.x = m_linearVelocity.x + force.x;
    m_linearVelocity.y = force.y + m_linearVelocity.y;
    m_linearVelocity.z = force.z + m_linearVelocity.z;
    m_linearVelocity.w = force.w + m_linearVelocity.w;
    float dt = stepInfo.m_deltaTime;
    float linScale = hkFloorZero(g_hkOne_01485720 - dt * m_linearDamping);
    m_linearVelocity.x = linScale * m_linearVelocity.x;
    m_linearVelocity.y = linScale * m_linearVelocity.y;
    m_linearVelocity.z = linScale * m_linearVelocity.z;
    m_linearVelocity.w = linScale * m_linearVelocity.w;
    float angScale = hkFloorZero(g_hkOne_01485720 - dt * m_angularDamping);
    m_angularVelocity.x = angScale * m_angularVelocity.x;
    m_angularVelocity.y = angScale * m_angularVelocity.y;
    m_angularVelocity.z = angScale * m_angularVelocity.z;
    m_angularVelocity.w = angScale * m_angularVelocity.w;

    hkMotionState& ms = m_motionState;
    hkMotionState::hkSweptTransform& swept = ms.m_sweptTransform;

    // previous position <- current position, then the half-step time stamp
    swept.m_centerOfMass0.x = swept.m_centerOfMass1.x;
    swept.m_centerOfMass0.y = swept.m_centerOfMass1.y;
    swept.m_centerOfMass0.z = swept.m_centerOfMass1.z;
    swept.m_centerOfMass0.w = swept.m_centerOfMass1.w;
    swept.m_centerOfMass0.w = stepInfo.m_startTime;

    // clamp the linear speed
    float lv2 = m_linearVelocity.x * m_linearVelocity.x +
                (m_linearVelocity.y * m_linearVelocity.y + m_linearVelocity.z * m_linearVelocity.z);
    float maxLin = ms.m_maxLinearVelocity;
    if (lv2 > maxLin * maxLin)
    {
        float s = maxLin / sqrtf(lv2);
        m_linearVelocity.x = s * m_linearVelocity.x;
        m_linearVelocity.y = s * m_linearVelocity.y;
        m_linearVelocity.z = s * m_linearVelocity.z;
        m_linearVelocity.w = s * m_linearVelocity.w;
    }

    // integrate the centre of mass
    swept.m_centerOfMass1.x = dt * m_linearVelocity.x + swept.m_centerOfMass1.x;
    swept.m_centerOfMass1.y = dt * m_linearVelocity.y + swept.m_centerOfMass1.y;
    swept.m_centerOfMass1.z = dt * m_linearVelocity.z + swept.m_centerOfMass1.z;
    swept.m_centerOfMass1.w = dt * m_linearVelocity.w + swept.m_centerOfMass1.w;
    swept.m_centerOfMass1.w = stepInfo.m_invDeltaTime;

    // rotation0 <- rotation1, and the half-angle delta quaternion from the angular velocity
    hkQuaternion rotation = swept.m_rotation1;
    swept.m_rotation0 = rotation;

    float halfDelta = dt * g_hkHalf_01471064;
    hkQuaternion deltaQ;
    deltaQ.x = halfDelta * m_angularVelocity.x;
    deltaQ.y = halfDelta * m_angularVelocity.y;
    deltaQ.z = halfDelta * m_angularVelocity.z;

    float angleSq = (deltaQ.z * deltaQ.z + deltaQ.y * deltaQ.y + deltaQ.x * deltaQ.x) * g_hkSinScale_0149e068;
    float maxAngle = ms.m_maxAngularVelocity * dt;
    if (maxAngle > g_hkMaxAngle_013ec4b4)
        maxAngle = g_hkMaxAngle_013ec4b4;
    float maxAngleSq = maxAngle * maxAngle;
    if (angleSq > maxAngleSq)
    {
        float s = maxAngle / sqrtf(angleSq);
        m_angularVelocity.x = s * m_angularVelocity.x;
        m_angularVelocity.y = s * m_angularVelocity.y;
        m_angularVelocity.z = s * m_angularVelocity.z;
        m_angularVelocity.w = s * m_angularVelocity.w;
        deltaQ.x = deltaQ.x * s;
        deltaQ.y = deltaQ.y * s;
        deltaQ.z = deltaQ.z * s;
        angleSq = maxAngleSq;
    }
    deltaQ.w = ((g_hkOne_01485720 - angleSq * g_hkQuatC1_0149e064) - (angleSq * angleSq) * g_hkQuatC2_0149e060)
             - ((angleSq * angleSq) * angleSq) * g_hkQuatC3_0149e05c;

    ((hkQuaternionOps*)&rotation)->setMul(deltaQ, rotation);
    ((hkQuaternionOps*)&rotation)->normalize();

    ms.m_deltaAngle.x = deltaQ.x + deltaQ.x;
    ms.m_deltaAngle.y = deltaQ.y + deltaQ.y;
    ms.m_deltaAngle.z = deltaQ.z + deltaQ.z;
    ms.m_deltaAngle.w = deltaQ.w + deltaQ.w;
    ms.m_deltaAngle.w = sqrtf(angleSq) * g_hkPi_014a1a20;

    swept.m_rotation1 = rotation;
    ((hkRotationOps*)&ms.m_transform)->set(swept.m_rotation1);

    // rebuild the transform translation from the swept centre of mass and the local com offset
    float lx = swept.m_centerOfMassLocal.x;
    float ly = swept.m_centerOfMassLocal.y;
    float lz = swept.m_centerOfMassLocal.z;
    float cx = swept.m_centerOfMass1.x;
    float cy = swept.m_centerOfMass1.y;
    float cz = swept.m_centerOfMass1.z;
    ms.m_transform.m_trans.x = cx - (lx * ms.m_transform.m_rot[0].x + (ly * ms.m_transform.m_rot[1].x + lz * ms.m_transform.m_rot[2].x));
    ms.m_transform.m_trans.y = cy - (lx * ms.m_transform.m_rot[0].y + (ly * ms.m_transform.m_rot[1].y + lz * ms.m_transform.m_rot[2].y));
    ms.m_transform.m_trans.z = cz - (lx * ms.m_transform.m_rot[0].z + (ly * ms.m_transform.m_rot[1].z + lz * ms.m_transform.m_rot[2].z));
    ms.m_transform.m_trans.w = swept.m_centerOfMass1.w;
}

// @ 0x01091270
const hkVelocityAccumulator* hkSphereMotionEx::applyAccumulator(const hkStepInfo& stepInfo, const hkVelocityAccumulator* acc)
{
    m_linearVelocity.x = acc->m_linearVelocity.x + acc->m_sweptCenterOfMass.x;
    m_linearVelocity.y = acc->m_linearVelocity.y + acc->m_sweptCenterOfMass.y;
    m_linearVelocity.z = acc->m_linearVelocity.z + acc->m_sweptCenterOfMass.z;
    m_linearVelocity.w = acc->m_linearVelocity.w + acc->m_sweptCenterOfMass.w;
    m_angularVelocity.x = acc->m_angularVelocity.x + acc->m_sweptCenterOfMass.x;
    m_angularVelocity.y = acc->m_angularVelocity.y + acc->m_sweptCenterOfMass.y;
    m_angularVelocity.z = acc->m_angularVelocity.z + acc->m_sweptCenterOfMass.z;
    m_angularVelocity.w = acc->m_angularVelocity.w + acc->m_sweptCenterOfMass.w;
    m_motionState.m_deactivationCounter = (uint16_t)acc->m_deactivationCounter;

    hkMotionState& ms = m_motionState;
    hkMotionState::hkSweptTransform& swept = ms.m_sweptTransform;

    swept.m_centerOfMass0.x = swept.m_centerOfMass1.x;
    swept.m_centerOfMass0.y = swept.m_centerOfMass1.y;
    swept.m_centerOfMass0.z = swept.m_centerOfMass1.z;
    swept.m_centerOfMass0.w = swept.m_centerOfMass1.w;
    swept.m_centerOfMass0.w = stepInfo.m_startTime;

    float lv2 = m_linearVelocity.x * m_linearVelocity.x +
                (m_linearVelocity.y * m_linearVelocity.y + m_linearVelocity.z * m_linearVelocity.z);
    float maxLin = ms.m_maxLinearVelocity;
    if (lv2 > maxLin * maxLin)
    {
        float s = maxLin / sqrtf(lv2);
        m_linearVelocity.x = s * m_linearVelocity.x;
        m_linearVelocity.y = s * m_linearVelocity.y;
        m_linearVelocity.z = s * m_linearVelocity.z;
        m_linearVelocity.w = s * m_linearVelocity.w;
    }

    float dt = stepInfo.m_deltaTime;
    swept.m_centerOfMass1.x = dt * m_linearVelocity.x + swept.m_centerOfMass1.x;
    swept.m_centerOfMass1.y = dt * m_linearVelocity.y + swept.m_centerOfMass1.y;
    swept.m_centerOfMass1.z = dt * m_linearVelocity.z + swept.m_centerOfMass1.z;
    swept.m_centerOfMass1.w = dt * m_linearVelocity.w + swept.m_centerOfMass1.w;
    swept.m_centerOfMass1.w = stepInfo.m_invDeltaTime;

    hkQuaternion rotation = swept.m_rotation1;
    swept.m_rotation0 = rotation;

    float halfDelta = dt * g_hkHalf_01471064;
    hkQuaternion deltaQ;
    deltaQ.x = halfDelta * m_angularVelocity.x;
    deltaQ.y = halfDelta * m_angularVelocity.y;
    deltaQ.z = halfDelta * m_angularVelocity.z;

    float angleSq = (deltaQ.z * deltaQ.z + deltaQ.y * deltaQ.y + deltaQ.x * deltaQ.x) * g_hkSinScale_0149e068;
    float maxAngle = ms.m_maxAngularVelocity * dt;
    if (maxAngle > g_hkMaxAngle_013ec4b4)
        maxAngle = g_hkMaxAngle_013ec4b4;
    float maxAngleSq = maxAngle * maxAngle;
    if (angleSq > maxAngleSq)
    {
        float s = maxAngle / sqrtf(angleSq);
        m_angularVelocity.x = s * m_angularVelocity.x;
        m_angularVelocity.y = s * m_angularVelocity.y;
        m_angularVelocity.z = s * m_angularVelocity.z;
        m_angularVelocity.w = s * m_angularVelocity.w;
        deltaQ.x = deltaQ.x * s;
        deltaQ.y = deltaQ.y * s;
        deltaQ.z = deltaQ.z * s;
        angleSq = maxAngleSq;
    }
    deltaQ.w = ((g_hkOne_01485720 - angleSq * g_hkQuatC1_0149e064) - (angleSq * angleSq) * g_hkQuatC2_0149e060)
             - ((angleSq * angleSq) * angleSq) * g_hkQuatC3_0149e05c;

    ((hkQuaternionOps*)&rotation)->setMul(deltaQ, rotation);
    ((hkQuaternionOps*)&rotation)->normalize();

    ms.m_deltaAngle.x = deltaQ.x + deltaQ.x;
    ms.m_deltaAngle.y = deltaQ.y + deltaQ.y;
    ms.m_deltaAngle.z = deltaQ.z + deltaQ.z;
    ms.m_deltaAngle.w = deltaQ.w + deltaQ.w;
    ms.m_deltaAngle.w = sqrtf(angleSq) * g_hkPi_014a1a20;

    swept.m_rotation1 = rotation;
    ((hkRotationOps*)&ms.m_transform)->set(swept.m_rotation1);

    float lx = swept.m_centerOfMassLocal.x;
    float ly = swept.m_centerOfMassLocal.y;
    float lz = swept.m_centerOfMassLocal.z;
    float cx = swept.m_centerOfMass1.x;
    float cy = swept.m_centerOfMass1.y;
    float cz = swept.m_centerOfMass1.z;
    ms.m_transform.m_trans.x = cx - (lx * ms.m_transform.m_rot[0].x + (ly * ms.m_transform.m_rot[1].x + lz * ms.m_transform.m_rot[2].x));
    ms.m_transform.m_trans.y = cy - (lx * ms.m_transform.m_rot[0].y + (ly * ms.m_transform.m_rot[1].y + lz * ms.m_transform.m_rot[2].y));
    ms.m_transform.m_trans.z = cz - (lx * ms.m_transform.m_rot[0].z + (ly * ms.m_transform.m_rot[1].z + lz * ms.m_transform.m_rot[2].z));
    ms.m_transform.m_trans.w = swept.m_centerOfMass1.w;

    m_linearVelocity = acc->m_linearVelocity;
    m_angularVelocity = acc->m_angularVelocity;
    return (const hkVelocityAccumulator*)((const char*)acc + 0x80);
}

// =========================================================================================================
// hkSpatialRigidBodyDeactivator
// =========================================================================================================

// @ 0x01091670
hkSpatialRigidBodyDeactivator::hkSpatialRigidBodyDeactivator()
{
    uint32_t* words = (uint32_t*)this;
    words[0x50 / 4] = 0xbf800000;   // -1.0f
    words[0x54 / 4] = 0x3c23d70a;   // 0.01f
    words[0x58 / 4] = 0x3ba3d70a;   // 0.005f
    words[0x5c / 4] = 0x3dcccccd;   // 0.1f
    words[0x60 / 4] = 0x3e4ccccd;   // 0.2f
    uint32_t big = 0x7f7fffee;
    uint32_t zero = 0;
    uint32_t one = 0x3f800000;
    words[0x10 / 4] = big;
    words[0x14 / 4] = big;
    words[0x18 / 4] = big;
    words[0x1c / 4] = big;
    words[0x30 / 4] = big;
    words[0x34 / 4] = big;
    words[0x38 / 4] = big;
    words[0x3c / 4] = big;
    words[0x20 / 4] = zero;
    words[0x24 / 4] = zero;
    words[0x28 / 4] = zero;
    words[0x2c / 4] = one;
    words[0x40 / 4] = zero;
    words[0x44 / 4] = zero;
    words[0x48 / 4] = zero;
    words[0x4c / 4] = one;
}

// @ 0x010916e0
hkBool hkSpatialRigidBodyDeactivator::shouldDeactivateHighFrequency(const hkEntity* entity) const
{
    const hkSpatialRigidBodyDeactivatorData* self = (const hkSpatialRigidBodyDeactivatorData*)this;
    const hkMotionState& ms = ((const hkRigidMotion*)entity->m_motion)->m_motionState;
    float radius = ms.m_objectRadius;

    hkVector4 dp;
    dp.x = self->m_highFreqPosition.x - ms.m_sweptTransform.m_centerOfMass1.x;
    dp.y = self->m_highFreqPosition.y - ms.m_sweptTransform.m_centerOfMass1.y;
    dp.z = self->m_highFreqPosition.z - ms.m_sweptTransform.m_centerOfMass1.z;

    hkVector4 dr;
    dr.x = self->m_highFreqRotation.x - ms.m_sweptTransform.m_rotation1.x;
    dr.y = self->m_highFreqRotation.y - ms.m_sweptTransform.m_rotation1.y;
    dr.z = self->m_highFreqRotation.z - ms.m_sweptTransform.m_rotation1.z;
    dr.w = self->m_highFreqRotation.w - ms.m_sweptTransform.m_rotation1.w;

    if (dp.x * dp.x + dp.y * dp.y + dp.z * dp.z <
            self->m_highFreqLinearThreshold * self->m_highFreqLinearThreshold &&
        (dr.x * dr.x + dr.y * dr.y + dr.z * dr.z + dr.w * dr.w) * radius * radius <
            self->m_highFreqAngularThreshold * self->m_highFreqAngularThreshold)
    {
        return hkBool(true);
    }

    hkSpatialRigidBodyDeactivatorData* s = (hkSpatialRigidBodyDeactivatorData*)(void*)this;
    s->m_highFreqPosition.x = ms.m_sweptTransform.m_centerOfMass1.x;
    s->m_highFreqPosition.y = ms.m_sweptTransform.m_centerOfMass1.y;
    s->m_highFreqPosition.z = ms.m_sweptTransform.m_centerOfMass1.z;
    s->m_highFreqPosition.w = ms.m_sweptTransform.m_centerOfMass1.w;
    s->m_highFreqRotation.x = ms.m_sweptTransform.m_rotation1.x;
    s->m_highFreqRotation.y = ms.m_sweptTransform.m_rotation1.y;
    s->m_highFreqRotation.z = ms.m_sweptTransform.m_rotation1.z;
    s->m_highFreqRotation.w = ms.m_sweptTransform.m_rotation1.w;
    return hkBool(false);
}

// @ 0x010917e0
hkBool hkSpatialRigidBodyDeactivator::shouldDeactivateLowFrequency(const hkEntity* entity) const
{
    const hkSpatialRigidBodyDeactivatorData* self = (const hkSpatialRigidBodyDeactivatorData*)this;
    const hkMotionState& ms = ((const hkRigidMotion*)entity->m_motion)->m_motionState;
    float radius = ms.m_objectRadius;

    hkVector4 dp;
    dp.x = self->m_lowFreqPosition.x - ms.m_sweptTransform.m_centerOfMass1.x;
    dp.y = self->m_lowFreqPosition.y - ms.m_sweptTransform.m_centerOfMass1.y;
    dp.z = self->m_lowFreqPosition.z - ms.m_sweptTransform.m_centerOfMass1.z;

    hkVector4 dr;
    dr.x = self->m_lowFreqRotation.x - ms.m_sweptTransform.m_rotation1.x;
    dr.y = self->m_lowFreqRotation.y - ms.m_sweptTransform.m_rotation1.y;
    dr.z = self->m_lowFreqRotation.z - ms.m_sweptTransform.m_rotation1.z;
    dr.w = self->m_lowFreqRotation.w - ms.m_sweptTransform.m_rotation1.w;

    if (dp.x * dp.x + dp.y * dp.y + dp.z * dp.z <
            self->m_lowFreqLinearThreshold * self->m_lowFreqLinearThreshold &&
        (dr.x * dr.x + dr.y * dr.y + dr.z * dr.z + dr.w * dr.w) * radius * radius <
            self->m_lowFreqAngularThreshold * self->m_lowFreqAngularThreshold)
    {
        return hkBool(true);
    }

    hkSpatialRigidBodyDeactivatorData* s = (hkSpatialRigidBodyDeactivatorData*)(void*)this;
    s->m_lowFreqPosition.x = ms.m_sweptTransform.m_centerOfMass1.x;
    s->m_lowFreqPosition.y = ms.m_sweptTransform.m_centerOfMass1.y;
    s->m_lowFreqPosition.z = ms.m_sweptTransform.m_centerOfMass1.z;
    s->m_lowFreqPosition.w = ms.m_sweptTransform.m_centerOfMass1.w;
    s->m_lowFreqRotation.x = ms.m_sweptTransform.m_rotation1.x;
    s->m_lowFreqRotation.y = ms.m_sweptTransform.m_rotation1.y;
    s->m_lowFreqRotation.z = ms.m_sweptTransform.m_rotation1.z;
    s->m_lowFreqRotation.w = ms.m_sweptTransform.m_rotation1.w;
    return hkBool(false);
}

// =========================================================================================================
// hkQuaternion::setMulInverse (0x01091970)
// =========================================================================================================

// @ 0x01091970
void hkQuaternionOps::setMulInverse(const hkQuaternion& q0, const hkQuaternion& q1)
{
    hkQuaternion& out = *(hkQuaternion*)this;
    out.x = q0.z * q1.y - q0.y * q1.z - q0.w * q1.x + q1.w * q0.x;
    out.y = q0.x * q1.z - q0.z * q1.x - q0.w * q1.y + q1.w * q0.y;
    out.z = q0.y * q1.x - q0.x * q1.y - q0.w * q1.z + q1.w * q0.z;
    out.w = q0.x * q1.x + q0.y * q1.y + q0.w * q1.w + q0.z * q1.z;
}
