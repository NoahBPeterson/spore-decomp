// slice s00698ca0 — SP orientation / intersection math (x87+SSE). Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct Vector3 {
  float x, y, z;
};

extern const float kPi;      // 0x0140837c
extern const float kTwoPi;   // 0x0152de2c
extern const float kTwoPi2;  // 0x016017a8
extern const float DAT_01601620;  // 0x01601620
extern const float DAT_01601624;  // 0x01601624
extern const float DAT_01601628;  // 0x01601628

template <typename T>
inline const T& min_ref(const T& a, const T& b) { return (a > b) ? b : a; }
template <typename T>
inline const T& max_ref(const T& a, const T& b) { return (a < b) ? b : a; }

// @ 0x00698ca0  classifies the projection of (a - b) onto (c - b) and returns the
// distance from a to the point that survives the test.  *outKind: 1 = behind b,
// 2 = past c, 0 = between (returns |a - proj|).
float SegmentTriangleIntersect(const Vector3* a, const Vector3* b, const Vector3* c,
                               int* outKind) {
  float lx = a->x - b->x;
  float ly = a->y - b->y;
  float lz = a->z - b->z;
  float cxb = c->x - b->x;
  float cyb = c->y - b->y;
  float czb = c->z - b->z;

  float sum = (lz * czb + ly * cyb) + lx * cxb;
  if (sum <= 0.0f) {
    *outKind = 1;
  } else {
    float len2 = (czb * czb + cyb * cyb) + cxb * cxb;
    if (sum >= len2) {
      *outKind = 2;
      double dx = (double)a->x - (double)c->x;
      double dy = (double)a->y - (double)c->y;
      double dz = (double)a->z - (double)c->z;
      return (float)sqrt(dx * dx + (dy * dy + dz * dz));
    }
    float t = sum / len2;
    lx = a->x - (b->x + cxb * t);
    ly = a->y - (cyb * t + b->y);
    lz = a->z - (b->z + czb * t);
    *outKind = 0;
  }
  return (float)sqrt((double)lx * lx + ((double)ly * ly + (double)lz * lz));
}

// @ 0x00698e00  projects p onto the segment [seg0, seg1] and returns the clamped point.
void DistancePointSegment(Vector3* out, const Vector3* p, const Vector3* seg0,
                          const Vector3* seg1) {
  float sx = seg0->x;
  float sy = seg0->y;
  float sz = seg0->z;
  float ex = seg1->x;
  float ey = seg1->y;
  float ez = seg1->z;
  float dx = ex - sx;
  float dy = ey - sy;
  float dz = ez - sz;
  float len = (float)sqrt((double)dx * dx + (double)dy * dy + (double)dz * dz);
  if (!(len <= 1e-06f)) {
    float inv = 1.0f / len;
    float t = ((p->z - sz) * (inv * dz) + (p->y - sy) * (inv * dy)) + (p->x - sx) * (inv * dx);
    if (t >= 0.0f) {
      if (t > len) {
        out->x = ex;
        out->y = ey;
        out->z = ez;
        return;
      }
      sx += (inv * dx) * t;
      sy += (inv * dy) * t;
      sz += (inv * dz) * t;
    }
  }
  out->x = sx;
  out->y = sy;
  out->z = sz;
}

// @ 0x00698fa0  closest points between two segments (p1 + s*d1, p2 + t*d2) inside a radius.
bool ClosestPointsOnSegments(const Vector3* p1, const Vector3* d1, const Vector3* p2,
                             const Vector3* d2, float radius, float len, float* outA,
                             float* outB) {
  float ux = p1->x - p2->x;
  float uy = p1->y - p2->y;
  float uz = p1->z - p2->z;
  float ax = d1->x;
  float bx = d2->x;
  float c3 = d2->z * d1->y - d2->y * d1->z;
  float c4 = bx * d1->z - ax * d2->z;
  float c10 = ax * d2->y - bx * d1->y;
  float n = (float)sqrt((double)c3 * c3 + ((double)c4 * c4 + (double)c10 * c10));

  if (!(1.5258789e-05f > n)) {
    float inv = 1.0f / n;
    float a3 = inv * c3;
    float a4 = c4 * inv;
    float a10 = c10 * inv;
    float dist = fabsf(a3 * ux + (a10 * uz + a4 * uy));
    if (!(dist > radius)) {
      float z2 = d2->z;
      float y2 = d2->y;
      float t = -(((uy * z2 - uz * y2) * a3 + (y2 * ux - uy * bx) * a10) +
                  (uz * bx - z2 * ux) * a4) *
                inv;
      float g6 = a4 * z2 - a10 * y2;
      float g11 = y2 * a3 - a4 * bx;
      float g14 = a10 * bx - z2 * a3;
      float inv2 = 1.0f / (float)sqrt((double)g14 * g14 + ((double)g11 * g11 + (double)g6 * g6));
      float f10 = (y2 * d1->y + z2 * d1->z) + ax * bx;
      float f8 = (uy * y2 + uz * z2) + bx * ux;
      float span = fabsf((float)sqrt((double)radius * radius - (double)dist * dist) /
                         ((inv2 * g6) * ax +
                          ((g11 * inv2) * d1->z + (g14 * inv2) * d1->y)));
      float lo = t - span;
      float hi = t + span;

      if (!(1.5258789e-05f > fabsf(f10))) {
        float inv10 = 1.0f / f10;
        float xa = (len - f8) * inv10;
        float xb = -(inv10 * f8);
        float v1, v2;
        if (f10 <= 0.0f) {
          v1 = (xa > lo) ? xa : lo;
          v2 = (hi > xb) ? xb : hi;
        } else {
          v1 = (xb > lo) ? xb : lo;
          v2 = (hi > xa) ? xa : hi;
        }
        if (v2 < v1) return false;
        if (!(v1 >= 0.0f) && !(v2 >= 0.0f)) return false;
        if (outA) *outA = v1;
        if (outB) *outB = v2;
        return true;
      }
      if (f8 < 0.0f || len < f8) return false;
      if (outA) *outA = lo;
      if (outB) *outB = hi;
      return true;
    }
    return false;
  }

  float s = (uy * d2->y + uz * d2->z) + bx * ux;
  float px = ux - bx * s;
  float py = uy - d2->y * s;
  float pz = uz - d2->z * s;
  if (!((float)sqrt((double)px * px + ((double)py * py + (double)pz * pz)) > radius)) {
    float v1, v2;
    if ((d1->z * d2->z + ax * bx) + d1->y * d2->y <= 0.0f) {
      v1 = s - len;
      v2 = s;
    } else {
      v1 = -s;
      v2 = len - s;
    }
    if (!(v1 >= 0.0f) && !(v2 >= 0.0f)) return false;
    if (outA) *outA = v1;
    if (outB) *outB = v2;
    return true;
  }
  return false;
}

// clamps an angle's cosine to the acos domain [-1, 1].
static inline float ClampUnit(float x) {
  if (x < -1.0f) x = -1.0f;
  if (x > 1.0f) x = 1.0f;
  return x;
}

// @ 0x006994a0
float SignedAngleBetween(const Vector3* a, const Vector3* b, const Vector3* axis)
{
  if (a->x == b->x && a->y == b->y && a->z == b->z) return 0.0f;
  float dot = (float)(a->z * (double)b->z + a->y * (double)b->y + a->x * (double)b->x);
  float vol = axis->z * (a->x * b->y - a->y * b->x)
            + axis->y * (a->z * b->x - a->x * b->z)
            + axis->x * (a->y * b->z - a->z * b->y);
  if (vol > 0.0f) return acosf(ClampUnit(dot));
  return kTwoPi2 - acosf(ClampUnit(dot));
}

// @ 0x00699600
void MoveToward(Vector3* out, const Vector3* from, const Vector3* to, float maxStep) {
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

// wraps an angle into (-pi, pi].
static __forceinline float WrapAngle(float x)
{
  x = (float)fmod((double)x, (double)kTwoPi);
  if (kPi <= x) x -= kTwoPi;
  return x;
}

// @ 0x00699730
float AngleDistance(float a, float b)
{
  float x = WrapAngle(a);
  float y = WrapAngle(b);
  const float& lo = min_ref(x, y);
  const float& hi = max_ref(x, y);
  float d = hi - lo;
  float e = (kTwoPi2 - hi) + lo;
  return min_ref(d, e);
}

// @ 0x00699800  point on the circle (center, radius) in the plane of "from" that is
// tangent toward "dir"; DAT_0160162x is the "no solution" result.
Vector3 CircleTangentPoint(const Vector3& center, float radius, const Vector3& from,
                           const Vector3& dir)
{
  Vector3 p;
  Vector3 d;
  d.x = from.x - center.x;
  d.y = from.y - center.y;
  d.z = from.z - center.z;
  float radiusSq = radius * radius;
  float lenSq = d.x * d.x + d.y * d.y + d.z * d.z;
  if (radiusSq < lenSq) {
    float inv = 1.0f / lenSq;
    float t = (dir.x * d.x + dir.y * d.y + dir.z * d.z) * inv;
    float k = radiusSq * inv;
    Vector3 a;
    a.x = d.x * k;
    a.y = d.y * k;
    a.z = d.z * k;
    Vector3 perp;
    perp.x = dir.x - d.x * t;
    perp.y = dir.y - d.y * t;
    perp.z = dir.z - d.z * t;
    float rem = radiusSq - (a.x * a.x + a.y * a.y + a.z * a.z);
    if (0.0f <= rem && 1e-06 <= perp.x * perp.x + perp.y * perp.y + perp.z * perp.z) {
      float s = (float)sqrt(rem / (perp.x * perp.x + perp.y * perp.y + perp.z * perp.z));
      p.x = center.x + (perp.x * s + a.x);
      p.y = center.y + (perp.y * s + a.y);
      p.z = center.z + (perp.z * s + a.z);
      return p;
    }
  }
  p.x = DAT_01601620;
  p.y = DAT_01601624;
  p.z = DAT_01601628;
  return p;
}
