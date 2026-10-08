// slice s009b5ce0 -- FUN_009b6450: ray cast against the oriented boxes of a creature's parts.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <float.h>

namespace RC {

struct BoxShape {
  char pad[0x138];
  float mHalfExtent[3];   // +0x138
};

// One part record (700 bytes).
struct Part {
  BoxShape* mpShape;      // +0x00
  char pad04[0xc];
  float mCenter[3];       // +0x10
  float mQuat[4];         // +0x1c: x y z w
  char pad2c[700 - 0x2c];
};

struct Owner {
  char pad00[0x18];
  float mPos[3];          // +0x18
  char pad24[0x3c - 0x24];
  float mQuat[4];         // +0x3c: x y z w
  char pad4c[0x70 - 0x4c];
  float mScale;           // +0x70
  char pad74[0x2e4 - 0x74];
  Part* mpPartsBegin;     // +0x2e4
  Part* mpPartsEnd;       // +0x2e8
};

}  // namespace RC

// Ray vs one oriented box; fills tOut and the box-local normal.
bool BoxRayTest(const float* org, const float* dir, const float* center, const float* rot3x3,
                float ex, float ey, float ez, float* tOut, float* normalOut);  // 0x00a02530
// Rotates a vector by a quaternion; returns out.
float* QuaternionVectorTransform(float* out, const float* quat, const float* v);  // 0x0099c1a0

using namespace RC;

// @ 0x009b6450
bool RayCastParts(const float* org, const float* dir, Owner* obj, unsigned* pIndex, float* pT, float* pHit,
                  float* pNormal)
{
  float bestT = FLT_MAX;
  float bestN[3] = {0.0f, 0.0f, 0.0f};
  float dx = org[0] - obj->mPos[0];
  float qd = obj->mQuat[3];
  float qc = obj->mQuat[2];
  float qb = obj->mQuat[1];
  float dy = org[1] - obj->mPos[1];
  float dz = org[2] - obj->mPos[2];
  float qa = obj->mQuat[0];
  float lo[3];
  float ld[3];
  unsigned bestIdx = 0xffffffff;

  lo[0] = (((qc * qa + -(qb * qd)) * dz + (qb * qa - -(qc * qd)) * dy) + (-(qc * qc) + -(qb * qb)) * dx) * 2.0f + dx;
  lo[1] = (((qc * qb - -(qa * qd)) * dz + (-(qc * qc) + -(qa * qa)) * dy) + (qb * qa + -(qc * qd)) * dx) * 2.0f + dy;
  lo[2] = (((-(qb * qb) + -(qa * qa)) * dz + (qc * qb + -(qa * qd)) * dy) + (qc * qa - -(qb * qd)) * dx) * 2.0f + dz;

  float e0 = dir[0], e1 = dir[1], e2 = dir[2];
  qb = obj->mQuat[1];
  qd = obj->mQuat[3];
  qa = obj->mQuat[0];
  qc = obj->mQuat[2];
  ld[0] = (((-(qc * qc) + -(qb * qb)) * e0 + (qc * qa + -(qb * qd)) * e2) + (qb * qa - -(qc * qd)) * e1) * 2.0f + e0;
  ld[1] = (((-(qc * qc) + -(qa * qa)) * e1 + (qb * qa + -(qc * qd)) * e0) + (qc * qb - -(qa * qd)) * e2) * 2.0f + e1;
  ld[2] = (((qc * qa - -(qb * qd)) * e0 + (-(qb * qb) + -(qa * qa)) * e2) + (qc * qb + -(qa * qd)) * e1) * 2.0f + e2;

  unsigned i = 0;
  if ((obj->mpPartsEnd - obj->mpPartsBegin) != 0) {
    do {
      Part* part = &obj->mpPartsBegin[i];
      float t = FLT_MAX;
      float n[3] = {0.0f, 0.0f, 0.0f};
      BoxShape* shape = part->mpShape;
      float qz = part->mQuat[2];
      float qy = part->mQuat[1];
      float qx = part->mQuat[0];
      float s2 = obj->mScale * 2.0f;
      float ex = s2 * shape->mHalfExtent[0];
      float ey = shape->mHalfExtent[1] * s2;
      float qyz = qz * qy;
      float ez = shape->mHalfExtent[2] * s2;
      float qw = part->mQuat[3];
      float qwy = qw * qy;
      float m[9];
      m[0] = 1.0f - (qz * qz + qy * qy) * 2.0f;
      m[1] = (qy * qx - qw * qz) * 2.0f;
      m[2] = (qwy + qz * qx) * 2.0f;
      m[3] = (qw * qz + qy * qx) * 2.0f;
      m[4] = 1.0f - (qz * qz + qx * qx) * 2.0f;
      m[5] = (qyz - qw * qx) * 2.0f;
      m[6] = (qz * qx - qwy) * 2.0f;
      m[7] = (qw * qx + qyz) * 2.0f;
      m[8] = 1.0f - (qy * qy + qx * qx) * 2.0f;
      if (BoxRayTest(lo, ld, part->mCenter, m, ex, ey, ez, &t, n) && t < bestT && 0.0f <= t) {
        bestT = t;
        bestIdx = i;
        float tmp[3];
        float* r = QuaternionVectorTransform(tmp, obj->mQuat, n);
        bestN[0] = r[0];
        bestN[1] = r[1];
        bestN[2] = r[2];
      }
      ++i;
    } while (i < (unsigned)(obj->mpPartsEnd - obj->mpPartsBegin));
    if (bestIdx != 0xffffffff) {
      if (pT) *pT = bestT;
      if (pNormal) {
        pNormal[0] = bestN[0];
        pNormal[1] = bestN[1];
        pNormal[2] = bestN[2];
      }
      if (pHit) {
        float h1 = dir[1];
        float h2 = dir[2];
        float o1 = org[1];
        float o2 = org[2];
        pHit[0] = dir[0] * bestT + org[0];
        pHit[1] = h1 * bestT + o1;
        pHit[2] = h2 * bestT + o2;
      }
      if (pIndex) *pIndex = bestIdx;
      return true;
    }
  }
  return false;
}
