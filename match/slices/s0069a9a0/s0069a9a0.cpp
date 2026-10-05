// slice s0069a9a0 — SP animated-event helpers and orientation math. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
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

// =============================================================================================
// @ 0x0069a9a0 (partial: skeleton)
void EventInterpolate(float t, const void* keys, void* out) { (void)t; (void)keys; (void)out; }

// @ 0x0069ac00 (partial: skeleton)
void EventInsert(int index, const void* value, void* keys) { (void)index; (void)value; (void)keys; }

// @ 0x0069aee0 (partial: skeleton)
void EventErase(float t, void* keys) { (void)t; (void)keys; }

// @ 0x0069b1c0 (partial: skeleton)
void SegmentClosest(const Vector3* a, const Vector3* b, const Vector3* p, Vector3* out) {
  (void)a; (void)b; (void)p; (void)out;
}

// @ 0x0069b440 (partial: skeleton)
__declspec(noinline) Matrix3* Matrix3FromFacingAndUp(Matrix3* out, const Vector3* facing,
                                                     const Vector3* up) {
  (void)facing; (void)up;
  return out;
}

// @ 0x0069b650 (partial: skeleton)
void SegmentPointDistance(const Vector3* a, const Vector3* b, const Vector3* c,
                          const Vector3* d, Vector3* out) {
  (void)a; (void)b; (void)c; (void)d; (void)out;
}

// @ 0x0069b760 (partial: skeleton)
void OrthoBasis(const Vector3* a, const Vector3* b, void* out) { (void)a; (void)b; (void)out; }

// @ 0x0069b840 (partial: skeleton)
float AngleClamp(float a, float b, float c) { (void)a; (void)b; (void)c; return 0.0f; }
