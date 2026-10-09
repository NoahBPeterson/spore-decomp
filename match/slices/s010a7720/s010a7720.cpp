// @ 0x010A7720
//
// Havok 3.1 contact-constraint Jacobian builder: called from
// hkSimpleContactConstraintData::buildJacobian (0x010a3ed0, call at 0x010a4277).
// Same role as Havok 6's extern "C" hkSimpleContactConstraintDataBuildJacobian, but
// with the 3.1 argument list (contact points, count, properties, info, in, out).
// cdecl, six stack args, aligned frame (`and esp,-16`), no calls.
//
// Output: one schema header (0x180101), then per contact point a 1D contact
// jacobian (schema 0x40504, or 0x80805 "pair" when CONTACT_USES_SOLVER_PATH2 couples
// it with the previous point). If the summed friction impulse is positive, a 2D
// friction jacobian pair (0x180809) along two tangents of the averaged normal, and
// for more than one point an optional rolling/angular friction jacobian that turns
// the friction schema into 0x1c090a.
#include "types.h"
#include <math.h>

// Engine-side tuning globals (0x015ba0d0, 0x015ba0d4); names from Havok 6's
// hkpSimpleContactConstraintInfo.h, which declares the same pair.
extern float HK_CONTACT_LINEAR_ERROR_RECOVERY_VELOCITY;
extern float HK_CONTACT_EXPONENTIAL_ERROR_RECOVERY_VELOCITY;
// 0x015b9b20: three unit axes (rows of the identity), 16-byte stride.
extern const float hkIdentityAxes[3][4];

struct hkVelocityAccumulator {
  uint32_t pad00[3];
  uint8_t m_type;            // +0x0c: nonzero = angular part is used unrotated
  uint8_t pad0d[3];
  uint32_t pad10[8];
  float m_invMasses[4];      // +0x30: inverse inertia diagonal xyz, inverse mass w
  float m_centerOfMass[4];   // +0x40
  float m_rotation[3][4];    // +0x50: columns, world -> core frame
};

struct hkConstraintQueryIn {
  float m_substepDeltaTime;      // +0x00
  float m_substepInvDeltaTime;   // +0x04
  float m_frameDeltaTime;        // +0x08
  float m_frameInvDeltaTime;     // +0x0c
  float m_invNumSteps;           // +0x10
  float m_rhsFactor;             // +0x14
  float m_virtMassFactor;        // +0x18
  float m_frictionRhsFactor;     // +0x1c
  char* m_accumulatorBufferRoot; // +0x20
  char* m_jacobianBufferRoot;    // +0x24
  hkVelocityAccumulator* m_bodyA; // +0x28
  hkVelocityAccumulator* m_bodyB; // +0x2c
};

struct hkConstraintQueryOut {
  float* m_jacobians;           // +0
  uint32_t* m_jacobianSchemas;  // +4
};

struct hkContactPoint {
  float m_position[4];
  float m_separatingNormal[4];  // w = distance
};

struct hkContactPointProperties {
  float m_impulseApplied;      // +0x00
  float m_internalSolverData;  // +0x04
  uint32_t m_userData;         // +0x08
  uint16_t m_friction;         // +0x0c (8.8 fixed point)
  uint8_t m_restitution;       // +0x0e
  uint8_t m_flags;             // +0x0f
  float m_internalDataA;       // +0x10
};

struct hkSimpleContactConstraintDataInfo {
  enum { HK_FLAG_OK = 0, HK_FLAG_POINT_REMOVED = 1, HK_FLAG_AREA_CHANGED = 4 };
  uint8_t m_flags;    // +0
  uint8_t pad1;
  uint16_t m_index;   // +2: friction reference axis (0..2)
  float m_data[7];    // +4: solver data; [1] [3] friction rhs, [5] rolling rhs, [6] contact radius
};

enum {
  CONTACT_USES_SOLVER_PATH2 = 2,
  SCHEMA_HEADER = 0x180101,
  SCHEMA_SINGLE_CONTACT = 0x40504,
  SCHEMA_PAIR_CONTACT = 0x80805,
  SCHEMA_2D_FRICTION = 0x180809,
  SCHEMA_2D_ROLLING_FRICTION = 0x1c090a
};

static __forceinline void SchemaFloat(uint32_t* s, float f) { *(float*)s = f; }

// Angular jacobian of one body: the direction rotated into the body's core frame,
// or copied unchanged (w included) when the accumulator says it needs no rotation.
static __forceinline void SetAngular(float* out, const hkVelocityAccumulator* acc, float x, float y,
                              float z) {
  if (acc->m_type == 0) {
    out[0] = x * acc->m_rotation[0][0] + (y * acc->m_rotation[1][0] + z * acc->m_rotation[2][0]);
    out[1] = x * acc->m_rotation[0][1] + (y * acc->m_rotation[1][1] + z * acc->m_rotation[2][1]);
    out[2] = x * acc->m_rotation[0][2] + (y * acc->m_rotation[1][2] + z * acc->m_rotation[2][2]);
  } else {
    out[0] = x;
    out[1] = y;
    out[2] = z;
  }
  out[3] = 0.0f;
}

// Effective-mass diagonal of a linear+angular jacobian (jac[4..6] body A, jac[8..10] body B).
static __forceinline float Diag(const float* jac, const hkVelocityAccumulator* a,
                         const hkVelocityAccumulator* b) {
  return ((b->m_invMasses[3] + a->m_invMasses[3]) + 1.1920929e-07f) +
         ((((jac[10] * jac[10]) * b->m_invMasses[2] + (jac[6] * jac[6]) * a->m_invMasses[2]) +
           ((jac[9] * jac[9]) * b->m_invMasses[1] + (jac[5] * jac[5]) * a->m_invMasses[1])) +
          ((jac[8] * jac[8]) * b->m_invMasses[0] + (jac[4] * jac[4]) * a->m_invMasses[0]));
}

// Coupling term J0 M^-1 J1^T of two linear+angular jacobians.
static __forceinline float Coupling(const float* j0, const float* j1, const hkVelocityAccumulator* a,
                             const hkVelocityAccumulator* b) {
  float mB = b->m_invMasses[3];
  float mA = a->m_invMasses[3];
  return ((((j0[2] * j1[2]) * mB + (j0[2] * j1[2]) * mA) +
           ((j0[10] * j1[10]) * b->m_invMasses[2] + (j0[6] * j1[6]) * a->m_invMasses[2])) +
          (((j0[1] * j1[1]) * mB + (j0[1] * j1[1]) * mA) +
           ((j0[9] * j1[9]) * b->m_invMasses[1] + (j0[5] * j1[5]) * a->m_invMasses[1]))) +
         ((mB * (j0[0] * j1[0]) + mA * (j0[0] * j1[0])) +
          ((j0[8] * j1[8]) * b->m_invMasses[0] + (j0[4] * j1[4]) * a->m_invMasses[0]));
}

// Linear jacobian `dir` at `pos` for the friction directions: angular parts are
// (pos - comA) x dir for A and dir x (pos - comB) for B.
static __forceinline void BuildLinear(float* jac, const float* pos, float dx, float dy, float dz,
                               const hkVelocityAccumulator* a, const hkVelocityAccumulator* b) {
  float ax = pos[0] - a->m_centerOfMass[0];
  float ay = pos[1] - a->m_centerOfMass[1];
  float az = pos[2] - a->m_centerOfMass[2];
  float bx = pos[0] - b->m_centerOfMass[0];
  float by = pos[1] - b->m_centerOfMass[1];
  float bz = pos[2] - b->m_centerOfMass[2];
  SetAngular(jac + 4, a, ay * dz - az * dy, az * dx - ax * dz, ax * dy - ay * dx);
  SetAngular(jac + 8, b, bz * dy - by * dz, bx * dz - bz * dx, by * dx - bx * dy);
}

extern "C" void hkSimpleContactConstraintDataBuildJacobian(
    const hkContactPoint* cp, int numPoints, hkContactPointProperties* props,
    hkSimpleContactConstraintDataInfo* info, const hkConstraintQueryIn* in,
    hkConstraintQueryOut* out) {
  hkVelocityAccumulator* bodyA = in->m_bodyA;
  hkVelocityAccumulator* bodyB = in->m_bodyB;
  float invNumPoints = 1.0f / (float)numPoints;

  uint32_t* header = out->m_jacobianSchemas;
  header[1] = (uint32_t)((char*)out->m_jacobians - in->m_jacobianBufferRoot);
  header[2] = (uint32_t)((char*)bodyA - in->m_accumulatorBufferRoot);
  header[3] = (uint32_t)((char*)bodyB - in->m_accumulatorBufferRoot);
  header[0] = SCHEMA_HEADER;
  header[5] = (uint32_t)props;
  header[4] = sizeof(hkContactPointProperties);
  uint32_t* schema = header + 6;
  float* jac = out->m_jacobians;

  float center[3] = {0.0f, 0.0f, 0.0f};
  float normal[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  int frictionSum = 0;
  float impulseSum = 0.0f;

  {
    const hkContactPoint* p = cp;
    hkContactPointProperties* pp = props;
    for (int i = numPoints; i != 0; i--, p++, pp++) {
      const float* n = p->m_separatingNormal;
      float virtMassFactor = in->m_virtMassFactor;
      jac[0] = n[0];
      jac[1] = n[1];
      jac[2] = n[2];
      jac[3] = n[3];
      {
        float ax = p->m_position[0] - bodyA->m_centerOfMass[0];
        float ay = p->m_position[1] - bodyA->m_centerOfMass[1];
        float az = p->m_position[2] - bodyA->m_centerOfMass[2];
        float bx = p->m_position[0] - bodyB->m_centerOfMass[0];
        float by = p->m_position[1] - bodyB->m_centerOfMass[1];
        float bz = p->m_position[2] - bodyB->m_centerOfMass[2];
        SetAngular(jac + 4, bodyA, ay * n[2] - az * n[1], az * n[0] - ax * n[2],
                   ax * n[1] - ay * n[0]);
        SetAngular(jac + 8, bodyB, bz * n[1] - by * n[2], bx * n[2] - bz * n[0],
                   by * n[0] - bx * n[1]);
      }
      float diag = Diag(jac, bodyA, bodyB);
      jac[11] = diag;
      jac[7] = virtMassFactor / diag;

      // Penetration recovery: limit the per-step correction, remember it in
      // m_internalDataA (clamped to <= 0) and set the rhs.
      frictionSum += pp->m_friction;
      impulseSum += pp->m_impulseApplied;
      float prevA = pp->m_internalDataA;
      float dist = n[3] - prevA;
      float solverDist = -pp->m_internalSolverData - dist;
      float maxLinear = HK_CONTACT_LINEAR_ERROR_RECOVERY_VELOCITY * in->m_frameDeltaTime;
      float expo = -HK_CONTACT_EXPONENTIAL_ERROR_RECOVERY_VELOCITY * prevA;
      float recover = (expo < maxLinear) ? expo : maxLinear;
      float newA = recover + prevA;
      float rhsDist = dist - recover;
      if ((recover + recover) + maxLinear < solverDist) {
        newA = newA - solverDist;
        rhsDist = rhsDist + solverDist;
      }
      if (fabsf(rhsDist) < 1e-10f) rhsDist = 0.0f;
      pp->m_internalDataA = (newA < 0.0f) ? newA : 0.0f;
      jac[3] = -rhsDist * in->m_rhsFactor;

      center[0] += p->m_position[0];
      center[1] += p->m_position[1];
      center[2] += p->m_position[2];
      normal[0] += n[0];
      normal[1] += n[1];
      normal[2] += n[2];
      normal[3] += n[3];

      if ((pp->m_flags & CONTACT_USES_SOLVER_PATH2) == 0) {
        schema[0] = SCHEMA_SINGLE_CONTACT;
      } else {
        // Couple with the previous point into a 2x2 block (inverted here).
        float* prev = jac - 12;
        float c = Coupling(jac, prev, bodyA, bodyB) * 0.99f;
        float prevDiag = prev[11];
        float inv = in->m_virtMassFactor / (jac[11] * prevDiag - c * c);
        prev[11] = jac[11] * inv;
        jac[11] = prevDiag * inv;
        schema[-1] = SCHEMA_PAIR_CONTACT;
        SchemaFloat(&schema[0], -(inv * c));
      }
      jac += 12;
      schema += 1;
    }
  }
  out->m_jacobians = jac;

  float frictionImpulse = (((float)frictionSum * 0.00390625f) * invNumPoints) * impulseSum;
  if (!(frictionImpulse > 0.0f)) {
    out->m_jacobianSchemas = schema;
    return;
  }

  // Friction normal: averaged normal, or the first point's when they agree or
  // cancel out, or +Y as last resort (then no friction impulse).
  float len2 = (normal[1] * normal[1] + normal[2] * normal[2]) + normal[0] * normal[0];
  if ((invNumPoints * invNumPoints) * len2 > 0.9999f) {
    normal[0] = cp->m_separatingNormal[0];
    normal[1] = cp->m_separatingNormal[1];
    normal[2] = cp->m_separatingNormal[2];
    normal[3] = cp->m_separatingNormal[3];
  } else if (len2 > 0.1f) {
    float inv = (len2 == 0.0f) ? 0.0f : 1.0f / sqrtf(len2);
    normal[0] = inv * normal[0];
    normal[1] = inv * normal[1];
    normal[2] = inv * normal[2];
    normal[3] = inv * normal[3];
  } else {
    normal[0] = cp->m_separatingNormal[0];
    normal[1] = cp->m_separatingNormal[1];
    normal[2] = cp->m_separatingNormal[2];
    normal[3] = cp->m_separatingNormal[3];
    if ((normal[1] * normal[1] + normal[2] * normal[2]) + normal[0] * normal[0] < 0.9f) {
      frictionImpulse = 0.0f;
      normal[3] = 0.0f;
      normal[0] = 0.0f;
      normal[2] = 0.0f;
      normal[1] = 1.0f;
    }
  }

  for (;;) {
    const float* axis = hkIdentityAxes[info->m_index];
    float tx = axis[1] * normal[2] - axis[2] * normal[1];
    float ty = axis[2] * normal[0] - normal[2] * axis[0];
    float tz = normal[1] * axis[0] - axis[1] * normal[0];
    float t2 = (tz * tz + ty * ty) + tx * tx;
    if (t2 > 0.1f) {
      float inv = (t2 == 0.0f) ? 0.0f : 1.0f / sqrtf(t2);
      tx = tx * inv;
      ty = ty * inv;
      tz = inv * tz;
      jac = out->m_jacobians;
      // Second tangent = normal x first tangent.
      float sx = tz * normal[1] - ty * normal[2];
      float sy = tx * normal[2] - tz * normal[0];
      float sz = ty * normal[0] - tx * normal[1];
      center[0] = center[0] * invNumPoints;
      center[1] = center[1] * invNumPoints;
      center[2] = center[2] * invNumPoints;

      float virtMassFactor = in->m_virtMassFactor;
      jac[0] = sx;
      jac[1] = sy;
      jac[2] = sz;
      jac[3] = 0.0f;
      BuildLinear(jac, center, sx, sy, sz, bodyA, bodyB);
      float d0 = Diag(jac, bodyA, bodyB);
      jac[11] = d0;
      jac[7] = virtMassFactor / d0;
      jac[3] = info->m_data[1] * in->m_frictionRhsFactor;

      float* j1 = jac + 12;
      virtMassFactor = in->m_virtMassFactor;
      j1[3] = inv * 0.0f;
      j1[0] = tx;
      j1[1] = ty;
      j1[2] = tz;
      BuildLinear(j1, center, tx, ty, tz, bodyA, bodyB);
      float d1 = Diag(j1, bodyA, bodyB);
      j1[11] = d1;
      j1[7] = virtMassFactor / d1;
      j1[3] = info->m_data[3] * in->m_frictionRhsFactor;

      float c = Coupling(jac, j1, bodyA, bodyB);
      float diag0 = jac[11];
      float k = in->m_virtMassFactor / (j1[11] * diag0 - c * c);
      jac[11] = k * j1[11];
      j1[11] = k * diag0;

      float invNumSteps = in->m_invNumSteps;
      schema[1] = (uint32_t)&info->m_data[0];
      schema[0] = SCHEMA_2D_FRICTION;
      SchemaFloat(&schema[4], 1.0f);
      schema[5] = 8;
      SchemaFloat(&schema[2], -(c * k));
      SchemaFloat(&schema[3], frictionImpulse * invNumSteps);
      float* j2 = jac + 24;

      if (numPoints > 1) {
        // Rolling friction needs the contact radius; recompute it when the area changed.
        while (info->m_flags & hkSimpleContactConstraintDataInfo::HK_FLAG_AREA_CHANGED) {
          info->m_data[6] = 0.0f;
          const hkContactPoint* p = cp;
          for (int i = numPoints; i != 0; i--, p++) {
            float dx = p->m_position[0] - center[0];
            float dy = p->m_position[1] - center[1];
            float dz = p->m_position[2] - center[2];
            info->m_data[6] = sqrtf((dy * dy) + ((dz * dz) + (dx * dx))) + info->m_data[6];
          }
          float radius = invNumPoints * info->m_data[6];
          info->m_data[6] = radius;
          if (radius < 1e-06f) {
            out->m_jacobians = j2;
            out->m_jacobianSchemas = schema + 6;
            return;
          }
          info->m_flags &= ~hkSimpleContactConstraintDataInfo::HK_FLAG_AREA_CHANGED;
        }

        // Angular jacobian about the normal: +n for A, -n for B.
        float vmf = in->m_virtMassFactor;
        if (bodyA->m_type == 0) {
          SetAngular(j2, bodyA, normal[0], normal[1], normal[2]);
        } else {
          j2[0] = normal[0];
          j2[1] = normal[1];
          j2[2] = normal[2];
          j2[3] = normal[3];
        }
        if (bodyB->m_type == 0) {
          SetAngular(j2 + 4, bodyB, -normal[0], -normal[1], -normal[2]);
        } else {
          j2[4] = -normal[0];
          j2[5] = -normal[1];
          j2[6] = -normal[2];
          j2[7] = -normal[3];
        }
        j2[3] = vmf / (((((j2[6] * j2[6]) * bodyB->m_invMasses[2] +
                          (j2[2] * j2[2]) * bodyA->m_invMasses[2]) +
                         ((j2[5] * j2[5]) * bodyB->m_invMasses[1] +
                          (j2[1] * j2[1]) * bodyA->m_invMasses[1])) +
                        ((j2[4] * j2[4]) * bodyB->m_invMasses[0] +
                         (j2[0] * j2[0]) * bodyA->m_invMasses[0])) +
                       1.1920929e-07f);
        float invRadius = 1.0f / info->m_data[6];
        SchemaFloat(&schema[6], info->m_data[6]);
        schema[0] = SCHEMA_2D_ROLLING_FRICTION;
        j2[7] = info->m_data[5] * in->m_frictionRhsFactor;
        j2[3] = invRadius * j2[3];
        out->m_jacobians = j2 + 8;
        out->m_jacobianSchemas = schema + 7;
        return;
      }
      out->m_jacobians = j2;
      out->m_jacobianSchemas = schema + 6;
      return;
    }

    // Reference axis too close to the normal: pick another one and reset the
    // stored friction state.
    float ax = fabsf(normal[0]);
    float ay = fabsf(normal[1]);
    float az = fabsf(normal[2]);
    if (ax >= ay) {
      info->m_index = (ay >= az) ? 2 : 1;
    } else {
      info->m_index = (ax >= az) ? 2 : 0;
    }
    info->m_data[1] = 0.0f;
    info->m_data[3] = 0.0f;
  }
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
