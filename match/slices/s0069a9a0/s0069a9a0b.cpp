// slice s0069a9a0 (second TU) — SP::QuaternionFromFacingAndUp.
// Kept in its own translation unit: defining Matrix3FromFacingAndUp in the same TU changes
// the /O2 schedule of this wrapper (verified with chk.py).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

struct Vector3 {
  float x, y, z;
};
struct Matrix3 {
  float m[9];
};
struct Quaternion {
  float x, y, z, w;
};

Matrix3* Matrix3FromFacingAndUp(Matrix3* out, const Vector3* facing, const Vector3* up);  // 0x69b440
Quaternion* QuaternionFromMatrix33(Quaternion* out, const Matrix3* m, float w);            // 0x472b80

// @ 0x0069b600
Quaternion* QuaternionFromFacingAndUp(Quaternion* out, const Vector3* facing, const Vector3* up) {
  Matrix3 m;
  Quaternion q;
  Matrix3* pm = Matrix3FromFacingAndUp(&m, facing, up);
  Quaternion* p = QuaternionFromMatrix33(&q, pm, 0.0f);
  out->x = p->x;
  out->y = p->y;
  out->z = p->z;
  out->w = p->w;
  return out;
}
