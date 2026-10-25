// Slice s00dc18e0: cSpace::UpdateTarget (VA 0x00dc18e0) and cSpace::Update (VA 0x00dc1d70),
// __cdecl members of SP::cSpace (this is the first stack argument, plain ret, bool in al).
// Translated from the retail disassembly; retail member names are unconfirmed, so cSpace's fields
// are declared with neutral names and the layout is documented inline.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-.  Both functions are booked nonmatching: the retail
// build mixes x87 float returns (virtual getters deliver their result in st(0)) with SSE local
// math, which a single /arch:SSE translation unit cannot reproduce.
// Known approximation: unaff_EBP (kEbp) has no visible origin in the outline, so it is taken as 0.
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
void   Fun_dc00a0(float* out, int arg, void* self);            // 0x00dc00a0: cdecl, 3 args
float  Fun_c37120();                                           // 0x00c37120: cdecl, no args

// Vtable access. Slot offsets are byte offsets into the vtable.
typedef void  (__thiscall* FnV0)(void*);
typedef void* (__thiscall* FnP0)(void*);
typedef void* (__thiscall* FnPP)(void*, void*);
typedef void* (__thiscall* FnPStr)(void*, unsigned int);
typedef int   (__thiscall* FnIArg)(void*, unsigned int);
typedef float (__thiscall* FnF0)(void*);
typedef void  (__thiscall* FnV1)(void*, int);

inline void** VT(void* o) { return *reinterpret_cast<void***>(o); }

// Embedded object at +0x508: its first dword is a vtable pointer.
struct Sub508 { void* vtbl; };

// The noun held by cSpace (cSpace::heldObject); +0x34 is an embedded helper object,
// +0x718/+0x71c/+0x720 its world position, +0x724 a radius triple, +0x730 its orientation.
struct HeldBody {
  char    pad0[0x34];
  struct { void* vtbl; } sub34;               // +0x34
  char    pad38[0x718 - 0x38];
  float   pos[3];                             // +0x718
  float   r724[3];                            // +0x724
  float   orient[4];                          // +0x730
};

class cSpace {
 public:
  bool __cdecl Update(int p2, unsigned int p3, int p4, int p5, float* p6, float p7, float p8);
  bool __cdecl UpdateTarget(int p2, unsigned int p3, int p4, int p5, float* p6, float p7, float p8);

  void* Fun_c38b00();                                          // 0x00c38b00: thiscall, returns [this+0x7a8]
  void* Fun_c38b80();                                          // 0x00c38b80: thiscall, returns [this+0x7ac]
  void  Fun_c3dae0(const void* arg);                           // 0x00c3dae0: thiscall, ret 4
  void  Fun_c3daa0(float arg);                                 // 0x00c3daa0: thiscall float, ret 4
  void  Fun_c3be70(const void* arg);                           // 0x00c3be70: thiscall, ret 4

  char        pad0[0x34];                     // +0x00
  void*       subObj34;                       // +0x34  helper object pointer
  char        pad38[0x508 - 0x38];            // +0x38
  Sub508      sub508;                         // +0x508
  char        pad50c[0x624 - 0x50c];          // +0x50c
  unsigned char flag624;                      // +0x624
  char        pad625[0x68c - 0x625];          // +0x625
  void*       heldObject;                     // +0x68c
  char        pad690[0x691 - 0x690];          // +0x690
  unsigned char flag691;                      // +0x691
  char        pad692[0x694 - 0x692];          // +0x692
  float       heldOffset[3];                  // +0x694
  char        pad6a0[0x6b0 - 0x6a0];          // +0x6a0
  unsigned int idx6b0;                        // +0x6b0
  char        pad6b4[0x714 - 0x6b4];          // +0x6b4
  int         i714;                           // +0x714
  float       pos[3];                         // +0x718
  char        pad724[0x730 - 0x724];          // +0x724
  float       orient[4];                      // +0x730
};

// @ 0x00dc18e0
bool __cdecl cSpace::UpdateTarget(int p2, unsigned int p3, int p4, int p5,
                                  float* p6, float p7, float p8) {
  (void)p2; (void)p3; (void)p5; (void)p7;

  void* held = heldObject;
  if (held == 0)
    return false;

  float local[3];
  Fun_dc00a0(local, p4, this);

  HeldBody* body = static_cast<HeldBody*>(held);
  void* heldSub = &body->sub34;
  void** heldVt = *reinterpret_cast<void***>(heldSub);
  const float kPositionScale = *reinterpret_cast<const float*>(0x014007f4);
  float scalar = reinterpret_cast<FnF0>(heldVt[0x34 / 4])(heldSub);

  local[0] = (local[0] + heldOffset[0] * kPositionScale) * scalar;
  local[1] = (local[1] + heldOffset[1] * kPositionScale) * scalar;
  local[2] = (local[2] + heldOffset[2] * kPositionScale) * scalar;

  void* basis = reinterpret_cast<FnP0>(heldVt[0x30 / 4])(heldSub);
  float rotated[3];
  Fun_59aed0(rotated, local, basis);

  float candidate[3];
  candidate[0] = pos[0] + rotated[0];
  candidate[1] = pos[1] + rotated[1];
  candidate[2] = pos[2] + rotated[2];

  const float kUnsetX = *reinterpret_cast<const float*>(0x0169f444);
  const float kUnsetY = *reinterpret_cast<const float*>(0x0169f448);
  const float kUnsetZ = *reinterpret_cast<const float*>(0x0169f44c);
  const float kOne = *reinterpret_cast<const float*>(0x01485720);
  const bool targetUnset = p6[0] == kUnsetX && p6[1] == kUnsetY && p6[2] == kUnsetZ;

  if (targetUnset) {
    const float dx = candidate[0] - pos[0];
    const float dy = candidate[1] - pos[1];
    const float dz = candidate[2] - pos[2];
    const float distance = (float)sqrt((double)(dz * dz + dy * dy) + (double)(dx * dx));

    if (distance > *reinterpret_cast<const float*>(0x01486110)) {
      const float blend = Fun_c37120();
      Fun_c3be70(candidate);
      Fun_c3daa0(blend);
      flag624 = 1;
      return true;
    }

    flag691 = 1;
    p6[0] = candidate[0];
    p6[1] = candidate[1];
    p6[2] = candidate[2];
  } else {
    flag691 = 1;

    float rate = (p6[3] + *reinterpret_cast<const float*>(0x0159d5f0)) * p8;
    if (rate > kOne)
      rate = kOne;

    const float dirLength = (float)sqrt((double)(candidate[2] * candidate[2] +
                                                candidate[1] * candidate[1]) +
                                        (double)(candidate[0] * candidate[0]));
    float dir[3];
    dir[0] = candidate[0] / dirLength;
    dir[1] = candidate[1] / dirLength;
    dir[2] = candidate[2] / dirLength;

    const float targetLength = (float)sqrt((double)(p6[2] * p6[2] +
                                                    p6[1] * p6[1]) +
                                           (double)(p6[0] * p6[0]));
    const float invTargetLength = kOne / targetLength;
    float normal[3];
    normal[0] = p6[0] * invTargetLength;
    normal[1] = p6[1] * invTargetLength;
    normal[2] = p6[2] * invTargetLength;

    float steer[3];
    Fun_b0fd00(steer, normal, dir, rate);
    p6[0] = steer[0] * targetLength;
    p6[1] = steer[1] * targetLength;
    p6[2] = steer[2] * targetLength;
  }

  void* finalHeld = heldObject;
  HeldBody* finalBody = static_cast<HeldBody*>(finalHeld);
  void* finalSub = &finalBody->sub34;
  void** finalVt = *reinterpret_cast<void***>(finalSub);
  void* extra = reinterpret_cast<FnP0>(finalVt[0x2c / 4])(finalSub);
  const float* extraVec = static_cast<const float*>(extra);
  float combined[3];
  combined[0] = extraVec[0] + p6[0];
  combined[1] = extraVec[1] + p6[1];
  combined[2] = extraVec[2] + p6[2];

  float facing[3];
  Fun_b0fd00(facing, pos, combined, *reinterpret_cast<const float*>(0x013ec4b4));
  Fun_c3dae0(facing);

  float orientRate = (p6[3] + *reinterpret_cast<const float*>(0x0159d5f4)) * p8;
  if (orientRate > kOne)
    orientRate = kOne;

  float slerpResult[4];
  float* quat = Fun_5b2500(slerpResult, orient, finalBody->orient, orientRate);
  orient[0] = quat[0];
  orient[1] = quat[1];
  orient[2] = quat[2];
  orient[3] = quat[3];
  return true;
}

// @ 0x00dc1d70
bool __cdecl cSpace::Update(int p2, unsigned int p3, int p4, int p5, float* p6, float p7, float p8) {
  (void)p2; (void)p4; (void)p5;
  const float kEbp = 0.0f;  // unaff_EBP: no visible origin in the Ghidra output.
  const float S0 = *reinterpret_cast<const float*>(0x0169f444);
  const float S1 = *reinterpret_cast<const float*>(0x0169f448);
  const float S2 = *reinterpret_cast<const float*>(0x0169f44c);

  // Early out when no held object.
  if (heldObject == 0) {
    return false;
  }
  if (p6[4] != -1.0f) {
    p6[4] = p6[4] - p8;
    if (p6[4] <= 0.0f) {
      void* c = heldObject;
      if (c != 0) {
        heldObject = 0;
        reinterpret_cast<FnV0>(VT(c)[1])(c);
      }
      void* sub = &sub508;
      reinterpret_cast<FnV0>(VT(sub)[0x38 / 4])(sub);
      return false;
    }
  }

  // Retarget test: if the target is farther than the threshold, drop it.
  if (heldObject != Fun_c38b00()) {
    void* u = Fun_c38b00();
    if (u != 0) {
      void* o = reinterpret_cast<FnPStr>(VT(u)[0xc / 4])(u, 0x01186577);
      if (o != 0) {
        float* pa = static_cast<float*>(reinterpret_cast<FnP0>(VT(o)[0x2c / 4])(o));
        void* m34 = subObj34;
        float* pb = static_cast<float*>(reinterpret_cast<FnP0>(VT(m34)[0x2c / 4])(m34));
        double dd = (double)(pb[1] - pa[1]) * (pb[1] - pa[1]) +
                    ((double)(pb[2] - pa[2]) * (pb[2] - pa[2]) + (double)(pb[0] - pa[0]) * (pb[0] - pa[0]));
        if (*reinterpret_cast<const float*>(0x0159d5c4) < (float)sqrt(dd)) {
          void* c = heldObject;
          if (c != 0) {
            heldObject = 0;
            reinterpret_cast<FnV0>(VT(c)[1])(c);
          }
          void* sub = &sub508;
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
  bool bEq = (heldObject == Fun_c38b00());
  fStack_84 = 1.0f;
  if (bEq) {
    uStack_80 = *reinterpret_cast<const float*>(0x0159d5cc);
    fStack_84 = *reinterpret_cast<const float*>(0x0159d5c8);
  } else {
    uStack_80 = 1.0f;
  }
  unsigned int idx = idx6b0 % 5;
  const float* row = reinterpret_cast<const float*>(0x016dba24) + idx * 3;
  double ang = (double)(*reinterpret_cast<const float*>(0x0169fa04) * fStack_84 * p8) * 0.5;
  float sn = (float)sin(ang);
  float cs = (float)cos(ang);
  float rv[3] = {row[0] * sn, row[1] * sn, row[2] * sn};
  float buf24[4];
  float* pv = Fun_59aed0(buf24, heldOffset, rv);
  heldOffset[0] = pv[0];
  heldOffset[1] = pv[1];
  heldOffset[2] = pv[2];

  // Length of the held object's position vector, minus planet radius and 1.0.
  HeldBody* hb = static_cast<HeldBody*>(heldObject);
  fStack_88 = (float)sqrt((double)(hb->pos[0] * hb->pos[0] + hb->pos[1] * hb->pos[1]) +
                          (double)(hb->pos[2] * hb->pos[2]));
  cPlanetModel* pl = PlanetModel();
  float rad = pl->GetRadiusAt(hb->pos);
  fStack_84 = (float)((double)fStack_88 - rad - 1.0);
  void* O = hb->sub34.vtbl;
  float t34 = reinterpret_cast<FnF0>(VT(O)[0x34 / 4])(O);
  float cand = t34 * *reinterpret_cast<const float*>(0x0159d5bc) * uStack_80;
  fStack_88 = cand;
  if (!(cand <= fStack_84)) {
    fStack_88 = fStack_84;
  }

  float V1[3] = {heldOffset[0] * fStack_88, heldOffset[1] * fStack_88, heldOffset[2] * fStack_88};
  void* O2 = hb->sub34.vtbl;
  void* u30 = reinterpret_cast<FnP0>(VT(O2)[0x30 / 4])(O2);
  float* v2 = Fun_59aed0(buf24, V1, u30);
  W[1] = v2[0];
  W[2] = v2[1];

  void* O3 = hb->sub34.vtbl;
  float buf18[6];
  float* v6c = static_cast<float*>(reinterpret_cast<FnPP>(VT(O3)[0x6c / 4])(O3, buf18));
  float V3x = (v6c[0] + v6c[3]) * 0.5f;
  float V3y = (v6c[4] + v6c[1]) * 0.5f;
  float V3z = (v6c[5] + v6c[2]) * 0.5f;

  // Steering test: take the main branch if the target changed, or if the held object is within range.
  float dx = hb->pos[0] - pos[0];
  float dy = hb->pos[1] - pos[1];
  float dz = hb->pos[2] - pos[2];
  float dist = (float)sqrt((double)(dz * dz + dy * dy) + (double)(dx * dx));
  bool take = (p6[0] != S0) || (p6[1] != S1) || (p6[2] != S2) || (dist <= kEbp + 3.0f);

  if (take) {
    flag691 = 1;
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
    Fun_b0fd00(buf28, pos, N2, rate2);
    Fun_c3dae0(buf28);

    float k3 = (p6[3] + *reinterpret_cast<const float*>(0x0159d5f4)) * p7;
    float rate3 = (k3 <= 1.0f) ? k3 : 1.0f;
    void* O4 = hb->sub34.vtbl;
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
    float* pq = Fun_5b2500(N3, orient, Q, rate3);
    float q0 = pq[0], q1 = pq[1], q2 = pq[2], q3 = pq[3];
    orient[0] = q0;
    orient[1] = q1;
    orient[2] = q2;
    orient[3] = q3;
    const float* vv = hb->r724;
    if (*reinterpret_cast<const float*>(0x0159fe24) <
        (float)sqrt((double)(vv[0] * vv[0] + vv[1] * vv[1]) + (double)(vv[2] * vv[2]))) {
      flag691 = 0;
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
    flag624 = 1;
  }

  // Target selection and final dispatch.
  int target = GetBestUFOTarget(this, (p3 >> 12) & 1u, 0);
  if (i714 == 2 && target == 0) {
    target = Fun_102c460(this);
  }
  unsigned char* u80b = reinterpret_cast<unsigned char*>(&uStack_80);
  if (u80b[3] != 0 && target == 0) {
    void* p = reinterpret_cast<cSpace*>(heldObject)->Fun_c38b80();
    if (p != 0) {
      int r = reinterpret_cast<FnIArg>(VT(p)[0xc / 4])(p, 0xee9b2232u);
      if (r != 0) {
        target = Fun_cc15b0(r, 0);
      }
    }
  }
  void* sub = &sub508;
  reinterpret_cast<FnV1>(VT(sub)[0x50 / 4])(sub, target);
  return true;
}

}  // namespace SP
