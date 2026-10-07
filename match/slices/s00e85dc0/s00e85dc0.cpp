// @ 0x00e85dc0  shape-matching goal positions (no symbol; free cdecl function)
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (scalar SSE math with reassociated sums).
//
// One step of meshless shape matching (Mueller et al. 2005) over n particles:
//   c   = mass-weighted centre of the current positions        (0x00e853c0)
//   Apq = sum_i m_i (x_i - c)(s * q_i)^T                         (q_i = rest offsets)
//   Apq is decomposed with Jacobi sweeps into R (eigenvectors) and D (0x00e851c0)
//   T   = beta * (Apq * Aqq) / s^2 + (1 - beta) * R              (written to *pT)
//   g_i = (s * q_i) * T + c                                      (goal positions)
// Matrices are row-major 3x3; points are row vectors multiplied on the left.
#include "types.h"
#include <string.h>

struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
  Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
  Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
  Vector3 operator*(float f) const { return Vector3(x * f, y * f, z * f); }
};

struct Matrix3 {
  Vector3 r[3];
  Matrix3() {}
  Matrix3(const Vector3& r0, const Vector3& r1, const Vector3& r2) { r[0] = r0; r[1] = r1; r[2] = r2; }
  Matrix3 operator+(const Matrix3& m) const { return Matrix3(r[0] + m.r[0], r[1] + m.r[1], r[2] + m.r[2]); }
  Matrix3 operator*(float f) const { return Matrix3(r[0] * f, r[1] * f, r[2] * f); }
  __forceinline Matrix3 operator*(const Matrix3& m) const {
    return Matrix3(m.r[0] * r[0].x + m.r[1] * r[0].y + m.r[2] * r[0].z,
                   m.r[0] * r[1].x + m.r[1] * r[1].y + m.r[2] * r[1].z,
                   m.r[0] * r[2].x + m.r[1] * r[2].y + m.r[2] * r[2].z);
  }
};

// a b^T
inline Matrix3 Outer(const Vector3& a, const Vector3& b) { return Matrix3(b * a.x, b * a.y, b * a.z); }
// row vector times matrix
inline Vector3 operator*(const Vector3& v, const Matrix3& m) {
  return Vector3(v.x * m.r[0].x + v.y * m.r[1].x + v.z * m.r[2].x,
                 v.x * m.r[0].y + v.y * m.r[1].y + v.z * m.r[2].y,
                 v.x * m.r[0].z + v.y * m.r[1].z + v.z * m.r[2].z);
}

extern const Vector3 kZeroVector;   // 0x016c4584

void ComputeCenterOfMass(int n, const Vector3* positions, const float* masses, Vector3* center);   // 0x00e853c0
void JacobiDecompose(const Matrix3& m, Matrix3& eigenvectors, Matrix3& diagonal);                 // 0x00e851c0

// @ 0x00e85dc0
void ComputeShapeMatchGoals(int n, const Vector3* restOffsets, const float* masses, const Matrix3& Aqq,
                            const Vector3* positions, float scale, float beta, Vector3* goals,
                            Matrix3& R, Matrix3& T)
{
  float invScale = 1.0f / scale;
  Vector3 center = kZeroVector;
  ComputeCenterOfMass(n, positions, masses, &center);

  Matrix3 Apq[3];   // the original clears 0x6c bytes; only the first matrix is used
  memset(Apq, 0, sizeof(Apq));
  for (int i = 0; i < n; i++) {
    Vector3 q = positions[i] - center;
    Vector3 p = restOffsets[i] * scale;
    Apq[0] = Apq[0] + Outer(q, p) * masses[i];
  }

  Matrix3 D;
  JacobiDecompose(Apq[0], R, D);
  Matrix3 M = Apq[0] * Aqq * invScale * invScale;
  T = M * beta + R * (1.0f - beta);

  for (int i = 0; i < n; i++)
    goals[i] = (restOffsets[i] * scale) * T + center;
}
