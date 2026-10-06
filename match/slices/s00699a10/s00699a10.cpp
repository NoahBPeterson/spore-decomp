// slice s00699a10 — SP animated-event curve helpers (float arrays). Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"
#include <math.h>

// =============================================================================================
// @ 0x0069a4c0 (attempt): slope array = (in[i+1]-in[i-1]) / (x[i+1]-x[i-1])
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

// @ 0x0069a4c0
void CurveSlopes::ComputeSlopes() {
  int n = (int)(mpEnd - mpBegin);
  for (int i = 1; i < n - 1; ++i) {
    mpOut[i] = (mpIn[i + 1] - mpIn[i - 1]) / (mpBegin[i + 1] - mpBegin[i - 1]);
  }
}

// =============================================================================================
struct Vec3 {
  float x, y, z;
};

// Hermite keyframe track: times at +0/+4, values at +0x14/+0x18, tangents at +0x28.
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

// @ 0x00699a10  2D convex hull (monotone chain) of points with stride 3 floats; returns hull point count
int ConvexHull2D(const float* pts, int n, float* out) {
  float x0 = pts[0];
  int first = 1;
  while (first < n && pts[first * 3] == x0) ++first;
  int lo = first - 1;
  int hi = n - 1;
  if (lo == hi) {
    out[0] = pts[0]; out[1] = pts[1]; out[2] = pts[2];
    const float* q = pts + lo * 3;
    unsigned k = (q[1] != pts[1]);
    if (k) { out[3] = q[0]; out[4] = q[1]; out[5] = q[2]; }
    float* o = out + (k + 1) * 3;
    o[0] = pts[0]; o[1] = pts[1]; o[2] = pts[2];
    return (int)k + 2;
  }
  int last = n - 2;
  float xl = pts[n * 3 - 3];
  while (last >= 0 && pts[last * 3] == xl) --last;
  int split = last + 1;
  out[0] = pts[0]; out[1] = pts[1]; out[2] = pts[2];
  int k = 0;
  for (int i = first; i <= split; ++i) {
    const float* p = pts + i * 3;
    float c = (p[1] - pts[1]) * (pts[split * 3] - pts[0]) - (pts[split * 3 + 1] - pts[1]) * (p[0] - pts[0]);
    if (c < 0.0f || split <= i) {
      while (k > 0) {
        const float* a = out + (k - 1) * 3;
        const float* b = out + k * 3;
        if (0.0f < (b[0] - a[0]) * (p[1] - a[1]) - (b[1] - a[1]) * (p[0] - a[0])) break;
        --k;
      }
      ++k;
      out[k * 3] = p[0]; out[k * 3 + 1] = p[1]; out[k * 3 + 2] = p[2];
    }
  }
  if (hi != split) {
    ++k;
    const float* p = pts + hi * 3;
    out[k * 3] = p[0]; out[k * 3 + 1] = p[1]; out[k * 3 + 2] = p[2];
  }
  int m = k;
  for (int i = last; i >= lo; --i) {
    const float* p = pts + i * 3;
    float hx = pts[hi * 3], hy = pts[hi * 3 + 1];
    float c = (pts[lo * 3] - hx) * (p[1] - hy) - (pts[lo * 3 + 1] - hy) * (p[0] - hx);
    if (c < 0.0f || i <= lo) {
      while (m > k) {
        const float* a = out + (m - 1) * 3;
        const float* b = out + m * 3;
        if (0.0f < (b[0] - a[0]) * (p[1] - a[1]) - (b[1] - a[1]) * (p[0] - a[0])) break;
        --m;
      }
      ++m;
      out[m * 3] = p[0]; out[m * 3 + 1] = p[1]; out[m * 3 + 2] = p[2];
    }
  }
  if (lo != 0) {
    ++m;
    out[m * 3] = pts[0]; out[m * 3 + 1] = pts[1]; out[m * 3 + 2] = pts[2];
  }
  return m + 1;
}

// @ 0x0069a050  even-odd point-in-polygon (xy) over points with stride 3 floats
bool PointInPolygon2D(const float* pts, int n, const float* pt) {
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

// @ 0x0069a240  clip segment p0->p1 against polygon edges; returns whether anything was produced
bool ClipSegmentToPolygon(const Vec3* p0, const Vec3* p1, const float* pts, int n, Vec3* out0, Vec3* out1) {
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

// @ 0x0069a5f0  cubic Hermite evaluation at t
float HermiteTrack::Evaluate(float t) {
  if (t <= mpTimes[0]) return mpValues[0];
  if (mpTimesEnd[-1] <= t) return mpValuesEnd[-1];
  int n = (int)(mpTimesEnd - mpTimes);
  int seg = 0;
  for (int i = 1; i < n; ++i) {
    if (t <= mpTimes[i]) break;
    seg = i;
  }
  float h = mpTimes[seg + 1] - mpTimes[seg];
  float s = (t - mpTimes[seg]) / h;
  float s2 = s * s;
  float m0 = mpTangents[seg] * h;
  float m1 = mpTangents[seg + 1] * h;
  return ((s - 1.0f) * s2) * m1 + (((s - 2.0f) * s + 1.0f) * s) * m0 +
         ((3.0f - s * 2.0f) * s2) * mpValues[seg + 1] + ((s * 2.0f - 3.0f) * s2 + 1.0f) * mpValues[seg];
}

// @ 0x0069a750  finite-difference tangents for the interior keys
void HermiteTrack3::ComputeTangents() {
  int n = (int)(mpTimesEnd - mpTimes) - 1;
  for (int i = 1; i < n; ++i) {
    float inv = 1.0f / (mpTimes[i + 1] - mpTimes[i - 1]);
    mpTangents[i].x = (mpValues[i + 1].x - mpValues[i - 1].x) * inv;
    mpTangents[i].y = inv * (mpValues[i + 1].y - mpValues[i - 1].y);
    mpTangents[i].z = inv * (mpValues[i + 1].z - mpValues[i - 1].z);
  }
}
