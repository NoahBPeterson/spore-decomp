// slice s00699a10 — SP animated-event curve helpers (float arrays). Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

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
struct Vector4 {
  float x, y, z, w;
};

// @ 0x00699a10 (partial: skeleton)
void EventEvaluate(float t, float* out, const void* keys) { (void)t; (void)out; (void)keys; }

// @ 0x0069a050 (partial: skeleton)
void EventSort(float* a, float* b, int n) { (void)a; (void)b; (void)n; }

// @ 0x0069a240 (partial: skeleton)
float VecDistance(const Vector4* a, const Vector4* b) { (void)a; (void)b; return 0.0f; }

// @ 0x0069a5f0 (partial: skeleton)
void CurveAdd(float t, void* keys) { (void)t; (void)keys; }

// @ 0x0069a750 (partial: skeleton)
void CurveRemove(int index, void* keys) { (void)index; (void)keys; }
