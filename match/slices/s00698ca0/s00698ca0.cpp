// slice s00698ca0 — SP orientation / intersection math (x87+SSE). Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"
#include <math.h>

struct Vector3 {
  float x, y, z;
};

// @ 0x00698ca0 (partial: skeleton)
int SegmentTriangleIntersect(const Vector3* a, const Vector3* b, const Vector3* c,
                             Vector3* p, Vector3* q, int* outKind) {
  (void)a; (void)b; (void)c; (void)p; (void)q; (void)outKind;
  return 0;
}

// @ 0x00698e00 (partial: skeleton)
float DistancePointSegment(const Vector3* a, const Vector3* b, const Vector3* p, float t) {
  (void)a; (void)b; (void)p; (void)t;
  return 0.0f;
}

// @ 0x00698fa0 (partial: skeleton)
void ClosestPointsOnSegments(const Vector3* a, const Vector3* b, const Vector3* c,
                             const Vector3* d, Vector3* outA, Vector3* outB) {
  (void)a; (void)b; (void)c; (void)d; (void)outA; (void)outB;
}

// @ 0x006994a0 (partial: skeleton)
void RaySphereIntersect(const Vector3* origin, const Vector3* dir, float r,
                        Vector3* out, int* hits) {
  (void)origin; (void)dir; (void)r; (void)out; (void)hits;
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

// @ 0x00699730 (partial: skeleton)
float WrapAngle(float a, float b) {
  (void)a; (void)b;
  return 0.0f;
}

// @ 0x00699800 (partial: skeleton)
void SegmentPhysics(const Vector3* a, const Vector3* b, float r, const Vector3* c,
                    Vector3* out) {
  (void)a; (void)b; (void)r; (void)c; (void)out;
}
