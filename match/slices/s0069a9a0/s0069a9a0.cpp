// slice s0069a9a0 -- animated-event keyframe tracks (Hermite) and orientation math. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fmod(double, double);
#pragma intrinsic(sqrt)

struct Vector3 {
  float x, y, z;
};
struct Matrix3 {
  float m[9];
};
struct Matrix3Rows {
  Vector3 row[3];
};

extern const float kPi;      // 0x0140837c
extern const float kTwoPi;   // 0x0152de2c
extern const float kTwoPi2;  // 0x016017a8

// EASTL-style vector header (begin, end, capacity, allocator)
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
struct HermiteTrack {
  EVec<float> mTimes;     // +0x00
  EVec<V> mValues;        // +0x14
  EVec<V> mTangents;      // +0x28
  void Evaluate(V* out, float t);
  void BuildTangents();
};

// Segment search: last index j (1 <= j < n) with t > times[j], else 0 (4x unrolled; expanded in place).
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

// @ 0x0069a9a0 (Vec3 track evaluate)
template <class V>
void HermiteTrack<V>::Evaluate(V* out, float t)
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
      return;
    }
    src = &mValues.mpEnd[-1];
  } else {
    src = &mValues.mpBegin[0];
  }
  *out = *src;
}

// @ 0x0069aee0
template <>
void HermiteTrack<Vec4k>::Evaluate(Vec4k* out, float t)
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
      return;
    }
    src = &mValues.mpEnd[-1];
  } else {
    src = &mValues.mpBegin[0];
  }
  *out = *src;
}

// Catmull-Rom style tangents for the interior keys of a Vec4 track.
// @ 0x0069ac00
template <>
void HermiteTrack<Vec4k>::BuildTangents()
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

// Explicit instantiations: 0x0069a9a0 (Vec3 evaluate), 0x0069ac00 (Vec4 tangents), 0x0069aee0 (Vec4 evaluate)
template void HermiteTrack<Vec3k>::Evaluate(Vec3k*, float);

// =============================================================================================
Vector3* OrthogonalVector(Vector3* out, const Vector3* v);   // 0x006985b0 (SP::OrthogonalVector)

static inline Vector3 Normalized(const Vector3& v)
{
  float inv = 1.0f / (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  Vector3 r;
  r.x = v.x * inv;
  r.y = v.y * inv;
  r.z = v.z * inv;
  return r;
}

static inline Vector3 Cross(const Vector3& a, const Vector3& b)
{
  Vector3 r;
  r.x = a.y * b.z - a.z * b.y;
  r.y = a.z * b.x - a.x * b.z;
  r.z = a.x * b.y - a.y * b.x;
  return r;
}

// @ 0x0069b1c0  rotation matrix taking unit vector a onto b (axis-angle from cross/dot)
void MatrixFromTwoVectors(Matrix3* out, const Vector3* a, const Vector3* b)
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
    Vector3 tmp;
    Vector3 o = *OrthogonalVector(&tmp, a);
    Vector3 n = Normalized(o);
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

// @ 0x0069b440  SP::Matrix3FromFacingAndUp
Matrix3Rows* Matrix3FromFacingAndUp(Matrix3Rows* out, const Vector3* facing, const Vector3* up)
{
  Vector3 f = Normalized(*facing);
  Vector3 r = Normalized(Cross(f, *up));
  Vector3 u = Normalized(Cross(r, f));
  out->row[0] = r;
  out->row[1] = f;
  out->row[2] = u;
  return out;
}

struct Vec2f {
  float x, y;
  Vec2f() {}
  Vec2f(float ax, float ay) : x(ax), y(ay) {}
  float Length() const { return (float)sqrt(x * x + y * y); }
};

static __forceinline Vec2f operator-(const Vec2f& a, const Vec2f& b) { return Vec2f(a.x - b.x, a.y - b.y); }
static __forceinline Vec2f operator*(const Vec2f& a, float k) { return Vec2f(a.x * k, a.y * k); }
static __forceinline float Dot(const Vec2f& a, const Vec2f& b) { return a.y * b.y + a.x * b.x; }

// @ 0x0069b650  closest point on segment [a,b] to point p (2D), written to out
void SegmentClosestPoint2D(Vec2f* out, const Vec2f* p, const Vec2f* a, const Vec2f* b)
{
  Vec2f d = *b - *a;
  float len = d.Length();
  Vec2f r = *a;
  if (len > 1e-6f) {
    Vec2f n = d * (1.0f / len);
    float proj = Dot(*p - *a, n);
    if (0.0f <= proj) {
      if (len < proj) {
        *out = *b;
        return;
      }
      r = Vec2f(a->x + n.x * proj, a->y + n.y * proj);
    }
  }
  *out = r;
}

float SignedAngleBetween(const Vector3* a, const Vector3* b, const Vector3* axis);   // 0x006994a0

// @ 0x0069b760  angle between two (normalized copies of) vectors about an axis
static inline void NormalizeTo(Vector3* o, const Vector3* v)
{
  float inv = 1.0f / (float)sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
  o->x = v->x * inv;
  o->y = v->y * inv;
  o->z = v->z * inv;
}

float SignedAngleNormalized(const Vector3* a, const Vector3* b, const Vector3* axis)
{
  Vector3 nb, na;
  NormalizeTo(&nb, b);
  NormalizeTo(&na, a);
  return SignedAngleBetween(&na, &nb, axis);
}

float AngleDistance(float a, float b);   // 0x00699730

static __forceinline float WrapAngle(float x)
{
  x = (float)fmod((double)x, (double)kTwoPi);
  if (kPi <= x) x -= kTwoPi;
  return x;
}

// @ 0x0069b840  step angle a toward b by at most c, wrapped to [-pi, pi)
float AngleStepToward(float a, float b, float c)
{
  if (AngleDistance(a, b) <= c) return b;
  float up = a + c;
  float down = a - c;
  float du = AngleDistance(up, b);
  float dd = AngleDistance(down, b);
  return WrapAngle((du < dd) ? up : down);
}
