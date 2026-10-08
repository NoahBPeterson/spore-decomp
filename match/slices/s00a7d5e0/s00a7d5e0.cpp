// slice s00a7d5e0 (function 0x00a7d8a0): Swarm quad collider setup. Takes a quad described by a
// corner and two edge vectors, builds its four corner points (corner, +u, +u+v, +v) and its unit
// plane normal, assigns the source transform, then moves the points and the normal through the
// world transform (rotation if flag 2, uniform scale, translation), recomputes the plane offset
// and records the dominant normal axis (0, 1 or 2) at +0x78. Class and member names are coined.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
  Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

static inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
static inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
static inline float Dot(const Vector3& a, const Vector3& b) { return a.z * b.z + a.y * b.y + a.x * b.x; }

struct Matrix3 { Vector3 row[3]; };

// PDB cSPTransform: flags, modification count, translation, scale, rotation (size 0x38)
struct cSPTransform {
  uint16_t mFlags;
  uint16_t mModificationCount;
  Vector3 mTranslation;
  float mScale;
  Matrix3 mRotation;
  void operator=(const cSPTransform& o);    // 0x00537dc0
};

static inline Vector3 Rotate(const Matrix3& m, const Vector3& v) {
  return Vector3(m.row[0].x * v.x + m.row[1].x * v.y + m.row[2].x * v.z,
                 m.row[0].y * v.x + m.row[1].y * v.y + m.row[2].y * v.z,
                 m.row[0].z * v.x + m.row[1].z * v.y + m.row[2].z * v.z);
}

// Quad (corner, edge u, edge v) referenced from the owner at +0x40.
struct QuadSource {
  Vector3 corner, u, v;
};
struct QuadOwner {
  uint8_t pad[0x40];
  QuadSource* mpQuad;
};

struct QuadPlane {
  Vector3 normal;          // +0x00
  float d;                 // +0x0c
  Vector3 pt[4];           // +0x10
  cSPTransform transform;  // +0x40
  int axis;                // +0x78 dominant normal axis
};

static __forceinline void TransformPoint(const cSPTransform* t, Vector3& p) {
  if (t->mFlags & 2)
    p = Rotate(t->mRotation, p);
  p = p * t->mScale;
  p = t->mTranslation + p;
}

// @ 0x00a7d8a0
void __stdcall BuildQuadPlane(QuadOwner* owner, cSPTransform* xf, const cSPTransform* src, QuadPlane* out) {
  const QuadSource* q = owner->mpQuad;
  Vector3 v = q->v;
  Vector3 u = q->u;
  out->pt[0] = q->corner;
  out->pt[1] = out->pt[0] + u;
  out->pt[2] = out->pt[1] + v;
  out->pt[3] = out->pt[0] + v;
  float nz = v.y * u.x - u.y * v.x;
  float ny = u.z * v.x - v.z * u.x;
  float nx = v.z * u.y - v.y * u.z;
  float inv = (float)(1.0 / sqrt(nz * nz + ny * ny + nx * nx + 1e-8f));
  out->normal = Vector3(inv * nx, ny * inv, nz * inv);
  out->transform = *src;
  TransformPoint(xf, out->pt[0]);
  TransformPoint(xf, out->pt[1]);
  TransformPoint(xf, out->pt[2]);
  TransformPoint(xf, out->pt[3]);
  if (xf->mFlags & 2)
    out->normal = Rotate(xf->mRotation, out->normal);
  out->d = -Dot(out->normal, out->pt[0]);
  float ax = fabsf(out->normal.x), ay = fabsf(out->normal.y), az = fabsf(out->normal.z);
  int axis;
  if (ax <= ay) {
    if (ay > az)
      axis = 1;
    else
      axis = 2;
  } else {
    if (ax > az)
      axis = 0;
    else
      axis = 2;
  }
  out->axis = axis;
}
