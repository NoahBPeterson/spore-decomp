// src/game/SPEngine/SPMathUtilities.cpp -- migrated from slice(s) s0069a9a0, s00699a10, s00698ca0, s00697c40 by tools/migrate/rewrite.py
// Object file: SPEngine/SPMathUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// ---- items of slice s00697c40 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vector3 {
  float x, y, z;
};
}
namespace SP {
struct Quaternion {
  float x, y, z, w;
};
}
namespace SP {
struct Matrix3 {
  float m[9];
};
}
// ---- items of slice s00697c40 end

// ---- items of slice s00698ca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s0069_8ca0 {
  float x, y, z;
};
// ---- items of slice s00698ca0 end

// ---- items of slice s00699a10 begin (TODO(rewrite): local stubs, replace by canonical classes)
class CurveSlopes {
 public:
  float* mpBegin;     // +0
  float* mpEnd;       // +4
  char pad8[0x14 - 8];
  float* mpIn;        // +0x14
  char pad18[0x28 - 0x18];
  float* mpOut;       // +0x28

  void ComputeSlopes();
};
struct Vec3 {
  float x, y, z;
};
class HermiteTrack {
 public:
  float* mpTimes;      // +0
  float* mpTimesEnd;   // +4
  char pad8[0x14 - 8];
  float* mpValues;     // +0x14
  float* mpValuesEnd;  // +0x18
  char pad1c[0x28 - 0x1c];
  float* mpTangents;   // +0x28

  float Evaluate(float t);
};
class HermiteTrack3 {
 public:
  float* mpTimes;      // +0
  float* mpTimesEnd;   // +4
  char pad8[0x14 - 8];
  Vec3* mpValues;      // +0x14
  char pad18[0x28 - 0x18];
  Vec3* mpTangents;    // +0x28

  void ComputeTangents();
};
// ---- items of slice s00699a10 end

// ---- items of slice s0069a9a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
struct Vector3_s0069_a9a0 {
  float x, y, z;
};
struct Matrix3_s0069_a9a0 {
  float m[9];
};
struct Matrix3Rows {
  Vector3_s0069_a9a0 row[3];
};
template <class T>
struct EVec {
  T* mpBegin;
  T* mpEnd;
  T* mpCap;
  int mAlloc[2];
};
struct Vec3k {
  float x, y, z;
  Vec3k& operator=(const Vec3k& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Vec4k {
  float x, y, z, w;
  Vec4k& operator=(const Vec4k& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
};
template <class V>
struct HermiteTrack_s0069_a9a0 {
  EVec<float> mTimes;     // +0x00
  EVec<V> mValues;        // +0x14
  EVec<V> mTangents;      // +0x28
  void Evaluate(V* out, float t);  // 0x0069a5f0 (HermiteTrack::Evaluate)
  void BuildTangents();
};
#define FIND_SEGMENT(times, n, t, idx) \
  int idx = 0; \
  { \
    int j = 1; \
    if (j < (n)) { \
      if ((n) - 1 >= 4) { \
        const float* p = (times) + 3; \
        do { \
          if (!((t) > p[-2])) goto seg_done; \
          idx = j; \
          if (!((t) > p[-1])) goto seg_done; \
          idx = j + 1; \
          if (!((t) > p[0])) goto seg_done; \
          idx = j + 2; \
          if (!((t) > p[1])) goto seg_done; \
          idx = j + 3; \
          j += 4; \
          p += 4; \
        } while (j < (n) - 3); \
      } \
      if (j < (n)) { \
        const float* p = (times) + j; \
        int k; \
        do { \
          k = j; \
          if (!((t) > *p)) break; \
          ++p; \
          j = k + 1; \
          idx = k; \
        } while (k + 1 < (n)); \
      } \
    } \
  } \
  seg_done:
template void HermiteTrack_s0069_a9a0<Vec3k>::Evaluate(Vec3k*, float);
Vector3_s0069_a9a0* OrthogonalVector(Vector3_s0069_a9a0* out, const Vector3_s0069_a9a0* v);   // 0x006985b0 (SP::OrthogonalVector)
static inline Vector3_s0069_a9a0 Normalized(const Vector3_s0069_a9a0& v)
{
  float inv = 1.0f / (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  Vector3_s0069_a9a0 r;
  r.x = v.x * inv;
  r.y = v.y * inv;
  r.z = v.z * inv;
  return r;
}
static inline Vector3_s0069_a9a0 Cross(const Vector3_s0069_a9a0& a, const Vector3_s0069_a9a0& b)
{
  Vector3_s0069_a9a0 r;
  r.x = a.y * b.z - a.z * b.y;
  r.y = a.z * b.x - a.x * b.z;
  r.z = a.x * b.y - a.y * b.x;
  return r;
}
struct Vec2f {
  float x, y;
  Vec2f() {}
  Vec2f(float ax, float ay) : x(ax), y(ay) {}
  float Length() const { return (float)sqrt(x * x + y * y); }
};
static __forceinline Vec2f operator-(const Vec2f& a, const Vec2f& b) { return Vec2f(a.x - b.x, a.y - b.y); }
static __forceinline Vec2f operator*(const Vec2f& a, float k) { return Vec2f(a.x * k, a.y * k); }
// ---- items of slice s0069a9a0 end

// ---- items of slice s0069a9a0b begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s0069_a9a0_b {
  float x, y, z;
};
struct Matrix3_s0069_a9a0_b {
  float m[9];
};
struct Quaternion_s0069_a9a0_b {
  float x, y, z, w;
};
Matrix3_s0069_a9a0_b* Matrix3FromFacingAndUp(Matrix3_s0069_a9a0_b* out, const Vector3_s0069_a9a0_b* facing, const Vector3_s0069_a9a0_b* up);  // 0x69b440
Quaternion_s0069_a9a0_b* QuaternionFromMatrix33(Quaternion_s0069_a9a0_b* out, const Matrix3_s0069_a9a0_b* m, float w);            // 0x472b80
// ---- items of slice s0069a9a0b end

// @ 0x00698180
namespace SP {
void QuaternionFromDirections(Quaternion* out, const Vector3* a, const Vector3* b)
{
  float a0 = a->x;
  float a1 = a->y;
  float a2 = a->z;
  volatile double inv = 1.0 / sqrt(((double)a0 * a0 + (double)a1 * a1) + (double)a2 * a2);
  volatile float invf = (float)inv;
  volatile float p = a0 * invf;
  volatile double lx = (double)a1 * inv;
  volatile double nx = (double)a2 * inv;
  float l = (float)lx;
  float n = (float)nx;
  float binv = 1.0f / sqrtf(b->x * b->x + b->y * b->y + b->z * b->z);
  float q = b->x * binv + p;
  float m = b->y * binv + l;
  float o = b->z * binv + n;
  volatile float dot = (q * q + o * o) + m * m;
  if (dot > 1e-4f) {
    volatile float s = 1.0f / sqrtf(dot);
    float ms = m * s;
    float os = o * s;
    float qs = q * s;
    out->x = os * l - ms * n;
    out->y = n * qs - os * p;
    out->z = ms * p - l * qs;
    out->w = (ms * l + os * n) + qs * p;
    return out;
  }
  if (fabsf(p) > 0.0f) {
    volatile float s = (float)(1.0 / sqrt((double)p * (double)p + nx * nx));
    out->y = 0.0f;
    out->x = -(n * s);
    out->z = p * s;
    out->w = 0.0f;
    return out;
  }
  volatile float s = (float)(1.0 / sqrt(lx * lx + nx * nx));
  out->x = 0.0f;
  out->y = -(n * s);
  out->z = l * s;
  out->w = 0.0f;
  return out;
}
}  // namespace SP

// @ 0x006983a0
namespace SP {
void MatrixFromDirection(Matrix3* out, const Vector3* dir)
{
  float s = 1.0f / sqrtf(dir->x * dir->x + dir->y * dir->y + dir->z * dir->z + 1e-8f);
  float x = dir->x * s;
  float y = dir->y * s;
  float z = dir->z * s;
  out->m[6] = x;
  out->m[7] = y;
  out->m[8] = z;
  float v0, v1, v2, v3, v4, v5;
  if (!(fabsf(z) < 0.999)) {
    float k = 1.0f / sqrtf(x * x + z * z + 1e-8f);
    v0 = k * z;
    v1 = k * -0.0f;
    v2 = -x * k;
    v3 = v2 * y - v1 * z;
    v4 = v0 * z - v2 * x;
    v5 = v1 * x - v0 * y;
  } else {
    float k = 1.0f / sqrtf(x * x + y * y + 1e-8f);
    v0 = -y * k;
    v1 = x * k;
    v2 = k * -0.0f;
    v3 = v2 * y - v1 * z;
    v4 = v0 * z - v2 * x;
    v5 = v1 * x - v0 * y;
  }
  out->m[0] = v0;
  out->m[1] = v1;
  out->m[2] = v2;
  out->m[3] = v3;
  out->m[4] = v4;
  out->m[5] = v5;
  (void)*(volatile unsigned int*)&out->m[5];
}
}  // namespace SP

// @ 0x006985b0
namespace SP {
void OrthogonalVector(Vector3* out, const Vector3* v)
{
  if (fabsf(v->y) <= fabsf(v->x)) {
    if (fabsf(v->y) < fabsf(v->z)) {
      out->x = -v->z;
      out->y = 0.0f;
      out->z = v->x;
      return;
    }
  } else if (fabsf(v->x) < fabsf(v->z)) {
    out->x = 0.0f;
    out->y = v->z;
    out->z = -v->y;
    return;
  }
  out->x = v->y;
  out->y = -v->x;
  out->z = 0.0f;
}
}  // namespace SP

// @ 0x00698650
namespace SP {
void MatrixFromQuaternion(Matrix3* m, const Quaternion* q)
{
  (void)q;
  double inv = 1.0 / (sqrt((double)m->m[3] * m->m[3] + (double)m->m[4] * m->m[4] + (double)m->m[5] * m->m[5]) + 1e-8);
  volatile float t3 = (float)((double)m->m[3] * inv);
  volatile float t4 = (float)((double)m->m[4] * inv);
  volatile float t5 = (float)((double)m->m[5] * inv);
  m->m[3] = t3;
  m->m[4] = t4;
  m->m[5] = t5;
  volatile float p1 = m->m[5] * m->m[8];
  volatile float p2 = m->m[4] * m->m[7];
  volatile float p3 = m->m[3] * m->m[6];
  volatile float s12 = p1 + p2;
  volatile float d = s12 + p3;
  volatile float q3 = m->m[3] * d;
  volatile float q4 = m->m[4] * d;
  volatile float q5 = m->m[5] * d;
  m->m[6] = m->m[6] - q3;
  m->m[7] = m->m[7] - q4;
  m->m[8] = m->m[8] - q5;
  double inv2 = 1.0 / (sqrt((double)m->m[6] * m->m[6] + (double)m->m[7] * m->m[7] + (double)m->m[8] * m->m[8]) + 1e-8);
  m->m[6] = (float)((double)m->m[6] * inv2);
  m->m[7] = (float)((double)m->m[7] * inv2);
  m->m[8] = (float)((double)m->m[8] * inv2);
  volatile float u0 = m->m[8] * m->m[4];
  volatile float v0 = m->m[7] * m->m[5];
  m->m[0] = u0 - v0;
  volatile float u1 = m->m[6] * m->m[5];
  volatile float v1 = m->m[3] * m->m[8];
  m->m[1] = u1 - v1;
  volatile float u2 = m->m[3] * m->m[7];
  volatile float v2 = m->m[6] * m->m[4];
  m->m[2] = u2 - v2;
  volatile float s0 = m->m[0] * m->m[0];
  volatile float s1 = m->m[1] * m->m[1];
  volatile float s2 = m->m[2] * m->m[2];
  volatile float t01 = s0 + s1;
  volatile float len = t01 + s2;
  if (len < 0.95f) {
    Vector3 tmp;
    typedef Vector3* (*OrthoPtr)(Vector3*, const Vector3*);
    Vector3* r = ((OrthoPtr)OrthogonalVector)(&tmp, (const Vector3*)&m->m[3]);
    m->m[6] = r->x;
    m->m[7] = r->y;
    m->m[8] = r->z;
    volatile float w0 = m->m[8] * m->m[4];
    volatile float w1 = m->m[7] * m->m[5];
    m->m[0] = w0 - w1;
    volatile float w2 = m->m[6] * m->m[5];
    volatile float w3 = m->m[3] * m->m[8];
    m->m[1] = w2 - w3;
    volatile float w4 = m->m[3] * m->m[7];
    volatile float w5 = m->m[6] * m->m[4];
    m->m[2] = w4 - w5;
  }
}
}  // namespace SP

// @ 0x00698880
namespace SP {
bool RayBoxIntersect(const float* origin, const float* dir, const float* box, float* outT)
{
  float invX = 1.0f / dir[0];
  float invY = 1.0f / dir[1];
  unsigned int nx = (dir[0] < 0.0f);
  unsigned int ny = (dir[1] < 0.0f);
  float t1 = (box[nx * 3 + 0] - origin[0]) * invX;
  float t2 = (box[3 - nx * 3] - origin[0]) * invX;
  float t3 = (box[4 - ny * 3] - origin[1]) * invY;
  float t4 = (box[ny * 3 + 1] - origin[1]) * invY;
  if (t1 <= t3 && t4 <= t2) {
    if (t1 < t4) t1 = t4;
    if (t3 < t2) t2 = t3;
    unsigned int nz = (dir[2] < 0.0f);
    float invZ = 1.0f / dir[2];
    float t5 = (box[5 - nz * 3] - origin[2]) * invZ;
    float t6 = (box[nz * 3 + 2] - origin[2]) * invZ;
    if (t1 <= t5 && t6 <= t2) {
      if (t1 < t6) t1 = t6;
      if (t5 < t2) t2 = t5;
      if (0.0f <= t2) {
        if (outT) *outT = (0.0f <= t1) ? t1 : 0.0f;
        return true;
      }
    }
  }
  return false;
}
}  // namespace SP

// @ 0x006989d0
namespace SP {
bool SegmentBoxIntersect(const float* p1, const float* p2, const float* box, float* outT)
{
  float dx = p2[0] - p1[0];
  float dy = p2[1] - p1[1];
  float dz = p2[2] - p1[2];
  float invX = 1.0f / dx;
  float invY = 1.0f / dy;
  float invZ = 1.0f / dz;
  unsigned int nx = (dx < 0.0f);
  unsigned int ny = (dy < 0.0f);
  unsigned int nz = (dz < 0.0f);
  float t1 = (box[nx * 3 + 0] - p1[0]) * invX;
  float t2 = (box[3 - nx * 3] - p1[0]) * invX;
  float t3 = (box[4 - ny * 3] - p1[1]) * invY;
  float t4 = (box[ny * 3 + 1] - p1[1]) * invY;
  if (t1 <= t3 && t4 <= t2) {
    if (t1 < t4) t1 = t4;
    if (t3 < t2) t2 = t3;
    float t5 = (box[5 - nz * 3] - p1[2]) * invZ;
    float t6 = (box[nz * 3 + 2] - p1[2]) * invZ;
    if (t1 <= t5 && t6 <= t2) {
      if (t1 < t6) t1 = t6;
      if (t5 < t2) t2 = t5;
      if (0.0f <= t2 && t1 < 1.0f) {
        if (outT) *outT = (0.0f <= t1) ? t1 : 0.0f;
        return true;
      }
    }
  }
  return false;
}
}  // namespace SP

// @ 0x00698b30
namespace SP {
void QuaternionSlerp(Quaternion* out, const Quaternion* a, const Quaternion* b, float t)
{
  (void)out;
  (void)a;
  (void)b;
  (void)t;
}
}  // namespace SP

// @ 0x00698ca0
int SegmentTriangleIntersect(const Vector3_s0069_8ca0* a, const Vector3_s0069_8ca0* b, const Vector3_s0069_8ca0* c, Vector3_s0069_8ca0* p, Vector3_s0069_8ca0* q, int* outKind)
{
  (void)a; (void)b; (void)c; (void)p; (void)q; (void)outKind;
  return 0;
}

// @ 0x00698e00
float DistancePointSegment(const Vector3_s0069_8ca0* a, const Vector3_s0069_8ca0* b, const Vector3_s0069_8ca0* p, float t)
{
  (void)a; (void)b; (void)p; (void)t;
  return 0.0f;
}

// @ 0x00698fa0
void ClosestPointsOnSegments(const Vector3_s0069_8ca0* a, const Vector3_s0069_8ca0* b, const Vector3_s0069_8ca0* c, const Vector3_s0069_8ca0* d, Vector3_s0069_8ca0* outA, Vector3_s0069_8ca0* outB)
{
  (void)a; (void)b; (void)c; (void)d; (void)outA; (void)outB;
}

// @ 0x006994a0
void RaySphereIntersect(const Vector3_s0069_8ca0* origin, const Vector3_s0069_8ca0* dir, float r, Vector3_s0069_8ca0* out, int* hits)
{
  (void)origin; (void)dir; (void)r; (void)out; (void)hits;
}

// @ 0x00699600
void MoveToward(Vector3_s0069_8ca0* out, const Vector3_s0069_8ca0* from, const Vector3_s0069_8ca0* to, float maxStep)
{
  float dx = to->x - from->x;
  float dy = to->y - from->y;
  float dz = to->z - from->z;
  if (dx * dx + dy * dy + dz * dz <= maxStep * maxStep) {
    out->x = to->x;
    out->y = to->y;
    out->z = to->z;
    return;
  }
  float inv = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz));
  out->x = from->x + (inv * dx) * maxStep;
  out->y = from->y + (dy * inv) * maxStep;
  out->z = from->z + (dz * inv) * maxStep;
}

// @ 0x00699730
float WrapAngle(float a, float b)
{
  (void)a; (void)b;
  return 0.0f;
}

// @ 0x00699800
void SegmentPhysics(const Vector3_s0069_8ca0* a, const Vector3_s0069_8ca0* b, float r, const Vector3_s0069_8ca0* c, Vector3_s0069_8ca0* out)
{
  (void)a; (void)b; (void)r; (void)c; (void)out;
}

// @ 0x00699a10
int ConvexHull2D(const float* pts, int n, float* out)
{
  const Vec3* P = (const Vec3*)pts;
  Vec3* O = (Vec3*)out;
  float x0 = P[0].x;
  int first = 1;
  while (first < n && P[first].x == x0) ++first;
  int lo = first - 1;
  int hi = n - 1;
  if (lo == hi) {
    O[0] = P[0];
    unsigned k = (P[lo].y != P[0].y);
    if (k) O[1] = P[lo];
    O[k + 1] = P[0];
    return (int)k + 2;
  }
  int last = n - 2;
  float xl = P[n - 1].x;
  while (last >= 0 && P[last].x == xl) --last;
  int split = last + 1;
  O[0] = P[0];
  int k = 0;
  for (int i = first; i <= split; ++i) {
    const Vec3* p = &P[i];
    float c = (p->y - P[0].y) * (P[split].x - P[0].x) - (P[split].y - P[0].y) * (p->x - P[0].x);
    if (c >= 0.0f && i < split) continue;
    while (k > 0) {
      const Vec3* a = &O[k - 1];
      const Vec3* b = &O[k];
      if ((b->x - a->x) * (p->y - a->y) - (b->y - a->y) * (p->x - a->x) > 0.0f) break;
      --k;
    }
    ++k;
    O[k] = *p;
  }
  if (hi != split) {
    ++k;
    O[k] = P[hi];
  }
  int m = k;
  for (int i = last; i >= lo; --i) {
    const Vec3* p = &P[i];
    float c = (P[lo].x - P[hi].x) * (p->y - P[hi].y) - (P[lo].y - P[hi].y) * (p->x - P[hi].x);
    if (c >= 0.0f && i > lo) continue;
    while (m > k) {
      const Vec3* a = &O[m - 1];
      const Vec3* b = &O[m];
      if ((b->x - a->x) * (p->y - a->y) - (b->y - a->y) * (p->x - a->x) > 0.0f) break;
      --m;
    }
    ++m;
    O[m] = *p;
  }
  if (lo != 0) {
    ++m;
    O[m] = P[0];
  }
  return m + 1;
}

// @ 0x0069a050
bool PointInPolygon2D(const float* pts, int n, const float* pt)
{
  float px = pt[0], py = pt[1];
  bool inside = false;
  int prev = n - 1;
  for (int i = 0; i < n; ++i) {
    float ax = pts[i * 3], ay = pts[i * 3 + 1];
    float bx = pts[prev * 3], by = pts[prev * 3 + 1];
    if (((ay <= py && py < by) || (by <= py && py < ay)) &&
        px < (bx - ax) * (py - ay) / (by - ay) + ax)
      inside = !inside;
    prev = i;
  }
  return inside;
}

// @ 0x0069a240
bool ClipSegmentToPolygon(const Vec3* p0, const Vec3* p1, const float* pts, int n, Vec3* out0, Vec3* out1)
{
  if (p0->x == p1->x && p0->y == p1->y && p0->z == p1->z) {
    *out0 = *p0;
    *out1 = *p0;
    return PointInPolygon2D(pts, n, (const float*)p0);
  }
  float dx = p1->x - p0->x;
  float dy = p1->y - p0->y;
  float dz = p1->z - p0->z;
  int edges = n - 1;
  float tmin = 0.0f, tmax = 1.0f;
  for (int i = 0; i < edges; ++i) {
    const float* a = pts + i * 3;
    float ex = a[3] - a[0];
    float ey = a[4] - a[1];
    float ez = a[5] - a[2];
    if (ex * ex + ey * ey + ez * ez < 1.5258789e-05f) continue;
    float num = (p0->y - a[1]) * ex - ey * (p0->x - a[0]);
    float den = -(dy * ex - ey * dx);
    if (1.5258789e-05f <= fabsf(den)) {
      float t = num / den;
      if (0.0f <= den) {
        if (!(t < tmax)) continue;
        tmax = t;
        if (tmin > t) return false;
      } else {
        if (!(tmin < t)) continue;
        tmin = t;
        if (t > tmax) return false;
      }
    } else {
      if (0.0f > num) return false;
    }
  }
  out0->x = p0->x + dx * tmin;
  out0->y = p0->y + dy * tmin;
  out0->z = p0->z + dz * tmin;
  out1->x = p0->x + dx * tmax;
  out1->y = p0->y + dy * tmax;
  out1->z = p0->z + dz * tmax;
  return edges > 0;
}

// @ 0x0069a4c0
void CurveSlopes::ComputeSlopes()
{
  int n = (int)(mpEnd - mpBegin);
  for (int i = 1; i < n - 1; ++i) {
    mpOut[i] = (mpIn[i + 1] - mpIn[i - 1]) / (mpBegin[i + 1] - mpBegin[i - 1]);
  }
}

// @ 0x0069a5f0
float HermiteTrack::Evaluate(float t)
{
  if (t <= mpTimes[0]) return mpValues[0];
  if (mpTimesEnd[-1] <= t) return mpValuesEnd[-1];
  int n = (int)(mpTimesEnd - mpTimes);
  int seg = 0;
  for (int i = 1; i < n; ++i) {
    if (!(t > mpTimes[i])) break;
    seg = i;
  }
  float h = mpTimes[seg + 1] - mpTimes[seg];
  float s = (t - mpTimes[seg]) / h;
  // tangents scaled into a small array: forces float-rounded SSE products, as in the original
  float m[2];
  m[0] = mpTangents[seg] * h;
  m[1] = mpTangents[seg + 1] * h;
  float s2 = s * s;
  return ((s * 2.0f - 3.0f) * s2 + 1.0f) * mpValues[seg] + ((3.0f - s * 2.0f) * s2) * mpValues[seg + 1] +
         (((s - 2.0f) * s + 1.0f) * s) * m[0] + ((s - 1.0f) * s2) * m[1];
}

// @ 0x0069a750
void HermiteTrack3::ComputeTangents()
{
  int n = (int)(mpTimesEnd - mpTimes) - 1;
  for (int i = 1; i < n; ++i) {
    float inv = 1.0f / (mpTimes[i + 1] - mpTimes[i - 1]);
    mpTangents[i].x = (mpValues[i + 1].x - mpValues[i - 1].x) * inv;
    mpTangents[i].y = inv * (mpValues[i + 1].y - mpValues[i - 1].y);
    mpTangents[i].z = inv * (mpValues[i + 1].z - mpValues[i - 1].z);
  }
}

// @ 0x0069a9a0
template <class V> void HermiteTrack_s0069_a9a0<V>::Evaluate(V* out, float t)
{
  float* times = mTimes.mpBegin;
  const V* src;
  if (times[0] < t) {
    if (t < mTimes.mpEnd[-1]) {
      int n = (int)(mTimes.mpEnd - times);
      FIND_SEGMENT(times, n, t, idx)
      V* values = mValues.mpBegin;
      V* tangents = mTangents.mpBegin;
      float dt = times[idx + 1] - times[idx];
      float s = (t - times[idx]) / dt;
      const V& p0 = values[idx];
      const V& p1 = values[idx + 1];
      const V& m0 = tangents[idx];
      const V& m1 = tangents[idx + 1];
      float m0z = m0.z, m0y = m0.y;
      float m1y = m1.y, m1z = m1.z;
      float s2 = s * s;
      float h10 = ((s - 2.0f) * s + 1.0f) * s;
      float h11 = (s - 1.0f) * s2;
      float h00 = (s * 2.0f - 3.0f) * s2 + 1.0f;
      float h01 = (3.0f - s * 2.0f) * s2;
      float p1y = p1.y, p1z = p1.z, p0y = p0.y, p0z = p0.z;
      out->x = ((p0.x * h00 + (m0.x * dt) * h10) + p1.x * h01) + (m1.x * dt) * h11;
      out->y = ((p0y * h00 + (m0y * dt) * h10) + p1y * h01) + (m1y * dt) * h11;
      out->z = ((p0z * h00 + (m0z * dt) * h10) + p1z * h01) + (m1z * dt) * h11;
      __asm { mov eax, dword ptr [out] }   // the hidden return buffer is the out pointer
      return;
    }
    src = &mValues.mpEnd[-1];
  } else {
    src = &mValues.mpBegin[0];
  }
  *out = *src;
  __asm { mov eax, dword ptr [out] }
}

// @ 0x0069ac00
template <> void HermiteTrack_s0069_a9a0<Vec4k>::BuildTangents()
{
  int n = (int)(mTimes.mpEnd - mTimes.mpBegin) - 1;
  for (int i = 1; i < n; ++i) {
    float inv = 1.0f / (mTimes.mpBegin[i + 1] - mTimes.mpBegin[i - 1]);
    const Vec4k& a = mValues.mpBegin[i + 1];
    const Vec4k& b = mValues.mpBegin[i - 1];
    Vec4k* m = &mTangents.mpBegin[i];
    m->x = (a.x - b.x) * inv;
    m->y = inv * (a.y - b.y);
    m->z = inv * (a.z - b.z);
    m->w = (a.w - b.w) * inv;
  }
}

// @ 0x0069aee0
template <> void HermiteTrack_s0069_a9a0<Vec4k>::Evaluate(Vec4k* out, float t)
{
  float* times = mTimes.mpBegin;
  const Vec4k* src;
  if (times[0] < t) {
    if (t < mTimes.mpEnd[-1]) {
      int n = (int)(mTimes.mpEnd - times);
      FIND_SEGMENT(times, n, t, idx)
      Vec4k* values = mValues.mpBegin;
      Vec4k* tangents = mTangents.mpBegin;
      float dt = times[idx + 1] - times[idx];
      const Vec4k& m0 = tangents[idx];
      float m0z = m0.z, m0y = m0.y, m0w = m0.w;
      const Vec4k& m1 = tangents[idx + 1];
      float s = (t - times[idx]) / dt;
      const Vec4k& p0 = values[idx];
      const Vec4k& p1 = values[idx + 1];
      float m1y = m1.y, m1z = m1.z, m1w = m1.w;
      float s2 = s * s;
      float h10 = ((s - 2.0f) * s + 1.0f) * s;
      float h11 = (s - 1.0f) * s2;
      float h01 = (3.0f - s * 2.0f) * s2;
      float h00 = (s * 2.0f - 3.0f) * s2 + 1.0f;
      float p1y = p1.y, p1z = p1.z, p1w = p1.w, p0z = p0.z, p0w = p0.w, p0y = p0.y;
      out->x = ((p0.x * h00 + (m0.x * dt) * h10) + p1.x * h01) + (m1.x * dt) * h11;
      out->y = ((p0y * h00 + (m0y * dt) * h10) + p1y * h01) + (m1y * dt) * h11;
      out->z = ((p0z * h00 + (m0z * dt) * h10) + p1z * h01) + (m1z * dt) * h11;
      out->w = ((p0w * h00 + (m0w * dt) * h10) + p1w * h01) + (m1w * dt) * h11;
      __asm { mov eax, dword ptr [out] }   // the hidden return buffer is the out pointer
      return;
    }
    src = &mValues.mpEnd[-1];
  } else {
    src = &mValues.mpBegin[0];
  }
  *out = *src;
  __asm { mov eax, dword ptr [out] }
}

// @ 0x0069b1c0
void MatrixFromTwoVectors(Matrix3_s0069_a9a0* out, const Vector3_s0069_a9a0* a, const Vector3_s0069_a9a0* b)
{
  float cx = b->z * a->y - b->y * a->z;
  float cy = b->x * a->z - a->x * b->z;
  float cz = a->x * b->y - b->x * a->y;
  float c = (a->x * b->x + a->y * b->y) + a->z * b->z;
  float s = (float)sqrt(cx * cx + (cy * cy + cz * cz));
  float ax, ay, az;
  if (s >= 1e-6f) {
    float inv = 1.0f / s;
    ax = inv * cx;
    ay = cy * inv;
    az = cz * inv;
  } else {
    Vector3_s0069_a9a0 tmp;
    Vector3_s0069_a9a0 o = *OrthogonalVector(&tmp, a);
    Vector3_s0069_a9a0 n = Normalized(o);
    ax = n.x;
    ay = n.y;
    az = n.z;
  }
  float oneMinusC = 1.0f - c;
  float tx = ax * oneMinusC;
  float ty = ay * oneMinusC;
  float tz = az * oneMinusC;
  out->m[0] = ax * tx + c;
  out->m[1] = ay * tx + az * s;
  out->m[2] = az * tx - ay * s;
  out->m[3] = ax * ty - az * s;
  out->m[4] = ay * ty + c;
  out->m[5] = az * ty + ax * s;
  out->m[6] = ax * tz + ay * s;
  out->m[7] = ay * tz - ax * s;
  out->m[8] = az * tz + c;
}

// @ 0x0069b440
Matrix3Rows* Matrix3FromFacingAndUp(Matrix3Rows* out, const Vector3_s0069_a9a0* facing, const Vector3_s0069_a9a0* up)
{
  Vector3_s0069_a9a0 f = Normalized(*facing);
  Vector3_s0069_a9a0 r = Normalized(Cross(f, *up));
  Vector3_s0069_a9a0 u = Normalized(Cross(r, f));
  out->row[0] = r;
  out->row[1] = f;
  out->row[2] = u;
  return out;
}

// @ 0x0069b600
Quaternion_s0069_a9a0_b* QuaternionFromFacingAndUp(Quaternion_s0069_a9a0_b* out, const Vector3_s0069_a9a0_b* facing, const Vector3_s0069_a9a0_b* up)
{
  Matrix3_s0069_a9a0_b m;
  Quaternion_s0069_a9a0_b q;
  Matrix3_s0069_a9a0_b* pm = Matrix3FromFacingAndUp(&m, facing, up);
  Quaternion_s0069_a9a0_b* p = QuaternionFromMatrix33(&q, pm, 0.0f);
  out->x = p->x;
  out->y = p->y;
  out->z = p->z;
  out->w = p->w;
  return out;
}
