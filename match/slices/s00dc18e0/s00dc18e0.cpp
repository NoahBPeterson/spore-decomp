// Slice s00dc18e0: FUN_00dc1d70 (VA 0x00dc1d70, 2474 bytes), a thiscall member of the space object.
// Translated from the Ghidra outline in work/match/scratch_s00dc18e0_card.txt.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-.
// Retail member names are unconfirmed, so fields are accessed by offset.
// Calling convention: __cdecl member (this is the first stack argument, plain ret), confirmed by the epilogue.
// Known gaps: unaff_EBP (kEbp) is set to 0. W[0] (uStack_7c) starts at 0 where the original holds
// bit-merged junk. The junk stack pointer in one branch is replaced by 1.0f.
#include "types.h"
#include <math.h>

namespace SP {

class cPlanetModel {
 public:
  float GetRadiusAt(const void* pos);                          // 0x00b7ef70: thiscall, ret 4
};
cPlanetModel* PlanetModel();                                   // 0x00b3d350: cdecl, no args

// Cdecl helpers (caller pops). Conventions read from call sites and callee epilogues.
int    GetBestUFOTarget(void* self, unsigned int flag, int zero);  // 0x0102bc90: cdecl, 3 args
int    Fun_102c460(void* self);                                // 0x0102c460: cdecl, 1 arg
int    Fun_cc15b0(int a, int b);                               // 0x00cc15b0: cdecl, 2 args
int    Fun_b67740(void* a);                                    // 0x00b67740: cdecl, 1 arg
float* Fun_59aed0(void* out, const void* a, const void* b);    // 0x0059aed0: cdecl, 3 args
float* Fun_b0fd00(void* out, const void* a, const void* b, float t);  // 0x00b0fd00 RotateTowards: cdecl, 4 args
void   QuaternionFromFacingAndUp(void* out, const void* facing, const void* up);  // 0x0069b600: cdecl
float* Fun_5b2500(const void* a, const void* b, const void* c, float t);          // 0x005b2500 Slerp: cdecl

// Vtable access. Slot offsets are byte offsets into the vtable.
typedef void  (__thiscall* FnV0)(void*);
typedef void* (__thiscall* FnP0)(void*);
typedef void* (__thiscall* FnPP)(void*, void*);
typedef void* (__thiscall* FnPStr)(void*, unsigned int);
typedef int   (__thiscall* FnIArg)(void*, unsigned int);
typedef float (__thiscall* FnF0)(void*);
typedef void  (__thiscall* FnV1)(void*, int);

inline void** VT(void* o) { return *reinterpret_cast<void***>(o); }

class cSpace {
 public:
  bool __cdecl Update(int p2, unsigned int p3, int p4, int p5, float* p6, float p7, float p8);

  void* Fun_c38b00();                                          // 0x00c38b00: thiscall, returns [this+0x7a8]
  void* Fun_c38b80();                                          // 0x00c38b80: thiscall, returns [this+0x7ac]
  void  Fun_c3dae0(const void* arg);                           // 0x00c3dae0: thiscall, ret 4
  void  Fun_c3daa0(float arg);                                 // 0x00c3daa0: thiscall float, ret 4
  void  Fun_c3be70(const void* arg);                           // 0x00c3be70: thiscall, ret 4

 private:
  template <typename T> T& At(unsigned int off) {
    return *reinterpret_cast<T*>(reinterpret_cast<char*>(this) + off);
  }
};

// @ 0x00dc1d70
bool __cdecl cSpace::Update(int p2, unsigned int p3, int p4, int p5, float* p6, float p7, float p8) {
  (void)p2; (void)p4; (void)p5;
  const float kEbp = 0.0f;  // unaff_EBP: no visible origin in the Ghidra output.
  const float S0 = *reinterpret_cast<const float*>(0x0169f444);
  const float S1 = *reinterpret_cast<const float*>(0x0169f448);
  const float S2 = *reinterpret_cast<const float*>(0x0169f44c);

  // Early out when no held object.
  if (At<void*>(0x68c) == 0) {
    return false;
  }
  if (p6[4] != -1.0f) {
    p6[4] = p6[4] - p8;
    if (p6[4] <= 0.0f) {
      void* c = At<void*>(0x68c);
      if (c != 0) {
        At<void*>(0x68c) = 0;
        reinterpret_cast<FnV0>(VT(c)[1])(c);
      }
      void* sub = reinterpret_cast<char*>(this) + 0x508;
      reinterpret_cast<FnV0>(VT(sub)[0x38 / 4])(sub);
      return false;
    }
  }

  // Retarget test: if the target is farther than the threshold, drop it.
  if (At<void*>(0x68c) != Fun_c38b00()) {
    void* u = Fun_c38b00();
    if (u != 0) {
      void* o = reinterpret_cast<FnPStr>(VT(u)[0xc / 4])(u, 0x01186577);
      if (o != 0) {
        float* pa = static_cast<float*>(reinterpret_cast<FnP0>(VT(o)[0x2c / 4])(o));
        void* m34 = At<void*>(0x34);
        float* pb = static_cast<float*>(reinterpret_cast<FnP0>(VT(m34)[0x2c / 4])(m34));
        double dd = (double)(pb[1] - pa[1]) * (pb[1] - pa[1]) +
                    ((double)(pb[2] - pa[2]) * (pb[2] - pa[2]) + (double)(pb[0] - pa[0]) * (pb[0] - pa[0]));
        if (*reinterpret_cast<const float*>(0x0159d5c4) < (float)sqrt(dd)) {
          void* c = At<void*>(0x68c);
          if (c != 0) {
            At<void*>(0x68c) = 0;
            reinterpret_cast<FnV0>(VT(c)[1])(c);
          }
          void* sub = reinterpret_cast<char*>(this) + 0x508;
          reinterpret_cast<FnV0>(VT(sub)[0x38 / 4])(sub);
          int t = Fun_b67740(Fun_c38b00());
          if (t != 0) {
            void* sub2 = reinterpret_cast<char*>(t) + 0x508;
            reinterpret_cast<FnV0>(VT(sub2)[0x38 / 4])(sub2);
          }
          return false;
        }
      }
    }
  }

  // Blend toward the target.
  float W[3] = {0.0f, 0.0f, 0.0f};  // W[0] is uStack_7c; W[1] and W[2] are filled from the stage-2 result.
  float fStack_84, fStack_88, uStack_80, fStack_64, fStack_60, fStack_5c;
  bool bEq = (At<void*>(0x68c) == Fun_c38b00());
  fStack_84 = 1.0f;
  if (bEq) {
    uStack_80 = *reinterpret_cast<const float*>(0x0159d5cc);
    fStack_84 = *reinterpret_cast<const float*>(0x0159d5c8);
  } else {
    uStack_80 = 1.0f;
  }
  unsigned int idx = At<unsigned int>(0x6b0) % 5;
  const float* row = reinterpret_cast<const float*>(0x016dba24) + idx * 3;
  double ang = (double)(*reinterpret_cast<const float*>(0x0169fa04) * fStack_84 * p8) * 0.5;
  float sn = (float)sin(ang);
  float cs = (float)cos(ang);
  float rv[3] = {row[0] * sn, row[1] * sn, row[2] * sn};
  float buf24[4];
  float* pos694 = reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x694);
  float* pv = Fun_59aed0(buf24, pos694, rv);
  pos694[0] = pv[0];
  At<float>(0x698) = pv[1];
  At<float>(0x69c) = pv[2];

  // Length of the held object's +0x718 vector, minus planet radius and 1.0.
  void* h = At<void*>(0x68c);
  float* hp = reinterpret_cast<float*>(reinterpret_cast<char*>(h) + 0x718);
  fStack_88 = (float)sqrt((double)(hp[0] * hp[0] + hp[1] * hp[1]) + (double)(hp[2] * hp[2]));
  cPlanetModel* pl = PlanetModel();
  float rad = pl->GetRadiusAt(hp);
  fStack_84 = (float)((double)fStack_88 - rad - 1.0);
  void* O = *reinterpret_cast<void**>(reinterpret_cast<char*>(At<void*>(0x68c)) + 0x34);
  float t34 = reinterpret_cast<FnF0>(VT(O)[0x34 / 4])(O);
  float cand = t34 * *reinterpret_cast<const float*>(0x0159d5bc) * uStack_80;
  fStack_88 = cand;
  if (!(cand <= fStack_84)) {
    fStack_88 = fStack_84;
  }

  float V1[3] = {pos694[0] * fStack_88, At<float>(0x698) * fStack_88, At<float>(0x69c) * fStack_88};
  void* O2 = *reinterpret_cast<void**>(reinterpret_cast<char*>(At<void*>(0x68c)) + 0x34);
  void* u30 = reinterpret_cast<FnP0>(VT(O2)[0x30 / 4])(O2);
  float* v2 = Fun_59aed0(buf24, V1, u30);
  W[1] = v2[0];
  W[2] = v2[1];

  void* O3 = *reinterpret_cast<void**>(reinterpret_cast<char*>(At<void*>(0x68c)) + 0x34);
  float buf18[6];
  float* v6c = static_cast<float*>(reinterpret_cast<FnPP>(VT(O3)[0x6c / 4])(O3, buf18));
  float V3x = (v6c[0] + v6c[3]) * 0.5f;
  float V3y = (v6c[4] + v6c[1]) * 0.5f;
  float V3z = (v6c[5] + v6c[2]) * 0.5f;

  // Steering test: take the main branch if the target changed, or if the held object is within range.
  void* A = At<void*>(0x68c);
  float dx = *reinterpret_cast<const float*>(reinterpret_cast<const char*>(A) + 0x718) - At<float>(0x718);
  float dy = *reinterpret_cast<const float*>(reinterpret_cast<const char*>(A) + 0x71c) - At<float>(0x71c);
  float dz = *reinterpret_cast<const float*>(reinterpret_cast<const char*>(A) + 0x720) - At<float>(0x720);
  float dist = (float)sqrt((double)(dz * dz + dy * dy) + (double)(dx * dx));
  bool take = (p6[0] != S0) || (p6[1] != S1) || (p6[2] != S2) || (dist <= kEbp + 3.0f);

  if (take) {
    At<unsigned char>(0x691) = 1;
    if (p6[0] == S0 && p6[1] == S1 && p6[2] == S2) {
      p6[0] = W[0];
      p6[1] = W[1];
      p6[2] = W[2];
    } else {
      float f60 = (p6[3] + *reinterpret_cast<const float*>(0x0159d5f0)) * p7;
      float rate1 = (f60 <= 1.0f) ? f60 : 1.0f;
      fStack_64 = (float)sqrt((double)(W[0] * W[0] + (W[1] * W[1] + W[2] * W[2])));
      float inv = 1.0f / fStack_64;
      float f84 = p6[2];
      W[0] = inv * W[0];
      float f88 = p6[1];
      W[1] = W[1] * inv;
      W[2] = W[2] * inv;
      float f58 = p6[0];
      fStack_5c = 1.0f / (float)sqrt((double)(f58 * f58 + (f88 * f88 + f84 * f84)));
      float N[3] = {f58 * fStack_5c, f88 * fStack_5c, f84 * fStack_5c};
      float buf54[4];
      float* r = Fun_b0fd00(buf54, N, W, rate1);
      float len = fStack_64;
      p6[0] = len * r[0];
      p6[1] = len * r[1];
      p6[2] = len * r[2];
    }

    float k2 = *reinterpret_cast<const float*>(0x0159fe28) * p7;
    float rate2 = (k2 <= 1.0f) ? k2 : 1.0f;
    float N2[3] = {V3x + p6[0], V3y + p6[1], V3z + p6[2]};
    float buf28[4];
    Fun_b0fd00(buf28, reinterpret_cast<char*>(this) + 0x718, N2, rate2);
    Fun_c3dae0(buf28);

    float k3 = (p6[3] + *reinterpret_cast<const float*>(0x0159d5f4)) * p7;
    float rate3 = (k3 <= 1.0f) ? k3 : 1.0f;
    void* O4 = *reinterpret_cast<void**>(reinterpret_cast<char*>(At<void*>(0x68c)) + 0x34);
    void* u2 = reinterpret_cast<FnP0>(VT(O4)[0x30 / 4])(O4);
    float buf54b[4];
    float* b = Fun_59aed0(buf54b, row, u2);

    float f58b = p6[0];
    float f88b = p6[1];
    float f84b = p6[2];
    float c0 = (f88b * -1.0f) * b[2] - (f84b * -1.0f) * b[1];
    float c1 = b[1] * (f58b * -1.0f) - (f88b * -1.0f) * b[0];
    float c2 = (f84b * -1.0f) * b[0] - b[2] * (f58b * -1.0f);
    float f34 = 1.0f / (float)sqrt((double)(c0 * c0 + (c2 * c2 + c1 * c1)) + 1e-08);
    float F[3] = {f34 * c0, c2 * f34, c1 * f34};
    float fa = 1.0f / (float)sqrt((double)(f58b * f58b + (f88b * f88b + f84b * f84b)) + 1e-08);
    float N3[3] = {fa * f58b, fa * f88b, fa * f84b};
    float Q[4];
    QuaternionFromFacingAndUp(Q, F, N3);
    float* pq = Fun_5b2500(N3, reinterpret_cast<char*>(this) + 0x730, Q, rate3);
    float q0 = pq[0], q1 = pq[1], q2 = pq[2], q3 = pq[3];
    At<float>(0x730) = q0;
    At<float>(0x734) = q1;
    At<float>(0x738) = q2;
    At<float>(0x73c) = q3;
    void* A2 = At<void*>(0x68c);
    const float* vv = reinterpret_cast<const float*>(reinterpret_cast<const char*>(A2) + 0x724);
    if (*reinterpret_cast<const float*>(0x0159fe24) <
        (float)sqrt((double)(vv[0] * vv[0] + vv[1] * vv[1]) + (double)(vv[2] * vv[2]))) {
      At<unsigned char>(0x691) = 0;
      p6[0] = S0;
      p6[1] = S1;
      p6[2] = S2;
    }
  } else {
    W[2] = V3z + W[2];
    W[1] = V3y + W[1];
    W[0] = V3x + W[0];
    Fun_c3daa0((float)sqrt((double)(W[0] * W[0] + (W[1] * W[1] + W[2] * W[2]))));
    Fun_c3be70(W);
    At<unsigned char>(0x624) = 1;
  }

  // Target selection and final dispatch.
  int target = GetBestUFOTarget(this, (p3 >> 12) & 1u, 0);
  if (At<int>(0x714) == 2 && target == 0) {
    target = Fun_102c460(this);
  }
  unsigned char* u80b = reinterpret_cast<unsigned char*>(&uStack_80);
  if (u80b[3] != 0 && target == 0) {
    void* p = reinterpret_cast<cSpace*>(At<void*>(0x68c))->Fun_c38b80();
    if (p != 0) {
      int r = reinterpret_cast<FnIArg>(VT(p)[0xc / 4])(p, 0xee9b2232u);
      if (r != 0) {
        target = Fun_cc15b0(r, 0);
      }
    }
  }
  void* sub = reinterpret_cast<char*>(this) + 0x508;
  reinterpret_cast<FnV1>(VT(sub)[0x50 / 4])(sub, target);
  return true;
}

}  // namespace SP
