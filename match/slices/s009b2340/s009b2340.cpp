// nSPCreatureAnim::EvaluateContextTargetQuery (slice s009b2340).
// Dev PDB: ?EvaluateContextTargetQuery@nSPCreatureAnim@@YAKPAKKABUcreature_static_data@1@ABUcontext_target@1@K_N@Z
// (context.obj).  Retail layouts differ from the 2008 PDB: offsets below are the retail ones read off the asm.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast  (aligned frame; FloorToInt is the module asm helper)
#include "types.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

namespace nSPCreatureAnim {

// checkerlib::vector_3 (user ctors/assignment, as in the dev PDB).
struct vector_3 {
  float x, y, z;
  vector_3() {}
  vector_3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
  vector_3(const vector_3& v) : x(v.x), y(v.y), z(v.z) {}
  vector_3& operator=(const vector_3& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

// checkerlib::rmin / rmax / vmin / vmax
inline float rmin(float a, float b) { return (a < b) ? a : b; }
inline float rmax(float a, float b) { return (a > b) ? a : b; }
inline vector_3 vmin(const vector_3& a, const vector_3& b) {
  vector_3 r;
  r.x = rmin(a.x, b.x);
  r.y = rmin(a.y, b.y);
  r.z = rmin(a.z, b.z);
  return r;
}
inline vector_3 vmax(const vector_3& a, const vector_3& b) {
  vector_3 r;
  r.x = rmax(a.x, b.x);
  r.y = rmax(a.y, b.y);
  r.z = rmax(a.z, b.z);
  return r;
}

// creature_part_caps lives at +8 of this holder; GetCap looks a FOURCC up in NameFOURCCs[32]
// (0-terminated) and returns Values[i], or the default if absent.  Retail 0x009b3050 (thiscall).
struct creature_part_caps_holder {
  unsigned long mFlags;                        // +0x00: OR of flags for all listed caps
  unsigned long mFlagsOn;                      // +0x04: OR of flags for enabled caps
  unsigned long mNames[32];                    // +0x08: FOURCC list (0-terminated)
  bool mValues[32];                            // +0x88: per-slot enabled byte

  bool GetCap(unsigned long fourcc, bool bDefault) const;  // 0x009b3050
  bool HasCap(unsigned long fourcc) const;                 // 0x009b30e0
  void SetCap(unsigned long fourcc, bool bValue);          // 0x009b3090
  unsigned long GetFreeSlot() const;                       // 0x009b3110
  __declspec(noinline) void Recompute();                   // 0x009b3010
};

unsigned long CapFlag(unsigned long fourcc);               // 0x009b2f90
bool SameCaps(const creature_part_caps_holder* a,
              const creature_part_caps_holder* b);         // 0x009b3150

struct creature_body_static_data {            // retail size 0x468
  char pad_000[0x10c];
  vector_3 rest_center__SCALABLE;              // +0x10c
  char pad_118[0x138 - 0x118];
  vector_3 local_half_extents__SCALABLE;       // +0x138
  char pad_144[0x150 - 0x144];
  creature_part_caps_holder caps;              // +0x150 (size 0xa8)
  char pad_1f8[0x210 - 0x1f8];
  unsigned long context_flags;                 // +0x210 (retail-only; masked with 0x610300)
  char pad_214[0x468 - 0x214];
};

struct creature_body_vector {
  creature_body_static_data* mpBegin;          // +0x384
  creature_body_static_data* mpEnd;            // +0x388
  creature_body_static_data* mpCapacity;
  unsigned long size() const { return (unsigned long)(mpEnd - mpBegin); }
  const creature_body_static_data& operator[](unsigned long i) const { return mpBegin[i]; }
};

struct creature_static_data {
  char pad_000[0x360];
  float local_aabb_origin_z;                   // +0x360
  char pad_364[0x36c - 0x364];
  float local_aabb_extent_z;                   // +0x36c
  char pad_370[0x384 - 0x370];
  creature_body_vector Bodies;                 // +0x384
};

struct context_target {
  unsigned long TypeAndFlags;  // +0x0
  unsigned long Query;         // +0x4
  unsigned __int64 Reserved;   // +0x8
};

void MirrorSagittalContextTarget(const context_target& in, context_target& out);  // 0x009b0280

// 0x009b1d80 (cdecl, 5 args; not yet identified): called for each accepted body unless bNoRecurse.
void FUN_009b1d80(unsigned long* pResult, unsigned long& nResult, const creature_static_data& data,
                               const creature_body_static_data& body, const context_target& target);

// float -> int round-down: the module's asm helper (cvtss2si + cmovb), result in eax.
__forceinline int FloorToInt(float f) {
  __asm {
    movss    xmm0, f
    cvtss2si eax, xmm0
    cvtsi2ss xmm1, eax
    mov      ecx, eax
    sub      ecx, 1
    ucomiss  xmm0, xmm1
    cmovb    eax, ecx
  }
}

inline int FixedUpmult(float f) { return FloorToInt(f * 100.0f); }

template <typename T> inline const T& min_(const T& a, const T& b) { return (b < a) ? b : a; }
template <typename T> inline const T& max_(const T& a, const T& b) { return (a < b) ? b : a; }

// Small state object reset by creature_anim_state::Init (retail 0x009b2e50).
struct anim_vec3 {
  float x, y, z;
  anim_vec3() {}
  anim_vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};

// The 4-byte packed colour at +0x20: Init writes bytes 04 00 FF FF (0xffff0004).
struct anim_color {
  unsigned char r, g, b, a;
  void Init();                                        // 0x009e6740
};

struct creature_anim_state {                          // retail size 0xf4
  char        pad_000[4];                             // +0x000 (not written here)
  anim_vec3   m004;                                   // +0x004
  anim_vec3   m010;                                   // +0x010
  float       m01c;                                   // +0x01c
  anim_color  m020;                                   // +0x020
  anim_vec3   m024;                                   // +0x024
  anim_vec3   m030;                                   // +0x030
  anim_vec3   m03c;                                   // +0x03c
  anim_vec3   m048;                                   // +0x048
  anim_vec3   m054;                                   // +0x054
  anim_vec3   m060;                                   // +0x060
  float       m06c;                                   // +0x06c
  float       m070;                                   // +0x070 (not written here)
  anim_vec3   m074;                                   // +0x074
  float       m080;                                   // +0x080
  char        pad_084[0x08c - 0x084];                 // +0x084
  anim_vec3   m08c;                                   // +0x08c
  char        pad_098[0x0bc - 0x098];                 // +0x098
  anim_vec3   m0bc;                                   // +0x0bc
  float       m0c8;                                   // +0x0c8 (not written here)
  anim_vec3   m0cc;                                   // +0x0cc
  anim_vec3   m0d8;                                   // +0x0d8
  anim_vec3   m0e4;                                   // +0x0e4
  float       m0f0;                                   // +0x0f0

  creature_anim_state* Init();                        // 0x009b2e50
};

// @ 0x009b2340
unsigned long EvaluateContextTargetQuery(unsigned long* pResult, unsigned long nMaxResults,
                                         const creature_static_data& data, const context_target& target_in,
                                         unsigned long bMirror, bool bNoRecurse) {
  unsigned long result[256];
  const unsigned long numBodies = data.Bodies.size();
  context_target target = target_in;
  if (bMirror)
    MirrorSagittalContextTarget(target_in, target);

  const unsigned long type = target.TypeAndFlags & 0x100003;
  unsigned long nResult = 0;
  switch (type) {
  case 1:
  case 0x100000:
  case 0x100001:
    result[0] = 0;
    nResult = 1;
    break;
  case 0:
  case 3:
  case 0x100002: {
    vector_3 bbMin(FLT_MAX, FLT_MAX, FLT_MAX);
    vector_3 bbMax(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    bool bNeedBounds = false;
    const unsigned long xMode = target.TypeAndFlags & 0x2000c;
    switch (xMode) {
    case 0x20000:
    case 0x20004:
    case 0x20008:
      bNeedBounds = true;
    }
    const unsigned long yMode = target.TypeAndFlags & 0x40030;
    switch (yMode) {
    case 0x40000:
    case 0x40010:
    case 0x40020:
      bNeedBounds = true;
    }
    const unsigned long zMode = target.TypeAndFlags & 0x800c0;
    switch (zMode) {
    case 0x80000:
    case 0x80040:
    case 0x80080:
      bNeedBounds = true;
    }
    if (bNeedBounds) {
      for (unsigned long i = 0; i < numBodies; ++i) {
        const creature_body_static_data& body = data.Bodies[i];
        if (type == 0x100002 || body.caps.GetCap(target.Query, false)) {
          bbMin = vmin(bbMin, body.rest_center__SCALABLE);
          bbMax = vmax(bbMax, body.rest_center__SCALABLE);
        }
      }
    }

    for (unsigned long i = 0; i < numBodies; ++i) {
      const creature_body_static_data& body = data.Bodies[i];
      if (!(type == 0x100002 || body.caps.GetCap(target.Query, false) || (type == 3 && i == target.Query)))
        continue;

      const vector_3& c = body.rest_center__SCALABLE;
      const vector_3& h = body.local_half_extents__SCALABLE;
      const float radius = (h.z + h.y + h.x) * 0.15f;
      bool bReject = false;

      switch (xMode) {
      case 0:
        bReject = bReject;  // no constraint on this axis
        break;
      case 0xc:
        if (!(fabs(c.x) - radius <= 0.0)) bReject = true;
        break;
      case 4:
        if (!(c.x >= -radius)) bReject = true;
        break;
      case 8:
        if (!(c.x <= radius)) bReject = true;
        break;
      case 0x20000:
        if (FixedUpmult(c.x) < FixedUpmult(bbMax.x - (bbMax.x - bbMin.x) * 0.525f)) bReject = true;
        break;
      case 0x20004:
        if (FixedUpmult(c.x) > FixedUpmult((bbMax.x - bbMin.x) * 0.525f + bbMin.x)) bReject = true;
        break;
      case 0x20008:
        if (abs(FixedUpmult(c.x - ((bbMax.x - bbMin.x) * 0.5f + bbMin.x))) > 10) bReject = true;
        break;
      }

      switch (yMode) {
      case 0:
        bReject = bReject;  // no constraint on this axis
        break;
      case 0x30:
        if (!(fabs(c.y) - radius <= 0.0)) bReject = true;
        break;
      case 0x10:
        if (!(c.y <= 0.0f)) bReject = true;
        break;
      case 0x20:
        if (!(c.y >= 0.0f)) bReject = true;
        break;
      case 0x40000:
        if (FixedUpmult(c.y) > FixedUpmult((bbMax.y - bbMin.y) * 0.525f + bbMin.y)) bReject = true;
        break;
      case 0x40010:
        if (FixedUpmult(c.y) < FixedUpmult(bbMax.y - (bbMax.y - bbMin.y) * 0.525f)) bReject = true;
        break;
      case 0x40020:
        if (abs(FixedUpmult(c.y - ((bbMax.y - bbMin.y) * 0.5f + bbMin.y))) > 10) bReject = true;
        break;
      }

      const float midZ = data.local_aabb_extent_z * 0.5f + data.local_aabb_origin_z;
      switch (zMode) {
      case 0:
        bReject = bReject;  // no constraint on this axis
        break;
      case 0xc0:
        if (!(fabs(c.z - midZ) <= radius)) bReject = true;
        break;
      case 0x40:
        if (!(c.z >= midZ)) bReject = true;
        break;
      case 0x80:
        if (!(c.z <= midZ)) bReject = true;
        break;
      case 0x80000:
        if (FixedUpmult(c.z) < FixedUpmult(bbMax.z - (bbMax.z - bbMin.z) * 0.525f)) bReject = true;
        break;
      case 0x80040:
        if (FixedUpmult(c.z) > FixedUpmult((bbMax.z - bbMin.z) * 0.525f + bbMin.z)) bReject = true;
        break;
      case 0x80080:
        if (abs(FixedUpmult(c.z - ((bbMax.z - bbMin.z) * 0.5f + bbMin.z))) > 10) bReject = true;
        break;
      }

      const unsigned long flags = target.TypeAndFlags;
      if ((flags & 0x610300) != 0 && (body.context_flags & flags & 0x610300) != body.context_flags)
        continue;
      if (bReject)
        continue;

      if (nResult == 0) {
        result[0] = i;
        nResult = 1;
      } else {
        switch (flags & 0xe000) {
        case 0:
          result[nResult++] = i;
          break;
        case 0x2000:
          if (c.x > data.Bodies[result[0]].rest_center__SCALABLE.x) result[nResult - 1] = i;
          break;
        case 0x4000:
          if (data.Bodies[result[0]].rest_center__SCALABLE.x > c.x) result[nResult - 1] = i;
          break;
        case 0x6000:
          if (data.Bodies[result[0]].rest_center__SCALABLE.y > c.y) result[nResult - 1] = i;
          break;
        case 0x8000:
          if (c.y > data.Bodies[result[0]].rest_center__SCALABLE.y) result[nResult - 1] = i;
          break;
        case 0xa000:
          if (c.z > data.Bodies[result[0]].rest_center__SCALABLE.z) result[nResult - 1] = i;
          break;
        case 0xc000:
          if (data.Bodies[result[0]].rest_center__SCALABLE.z > c.z) result[nResult - 1] = i;
          break;
        }
      }
      if (!bNoRecurse)
        FUN_009b1d80(result, nResult, data, body, target);
    }
    break;
  }
  }

  const unsigned long n = min_(nMaxResults, nResult);
  if (n != 0 && pResult != 0)
    memcpy(pResult, result, n * sizeof(unsigned long));
  return n;
}

// @ 0x009b2e50
creature_anim_state* creature_anim_state::Init() {
  m004.x = m004.y = m004.z = 0.0f;
  m010.x = m010.y = m010.z = 0.0f;
  m01c = 1.0f;
  m020.Init();
  m024.x = m024.y = m024.z = 0.0f;
  m030.x = m030.y = m030.z = 0.0f;
  m03c.x = m03c.y = m03c.z = 0.0f;
  m048.x = m048.y = m048.z = 0.0f;
  m054.x = m054.y = m054.z = 0.0f;
  m060.x = m060.y = m060.z = 0.0f;
  m06c = 1.0f;
  m074.x = m074.y = m074.z = 0.0f;
  m080 = 1.0f;
  m08c.x = m08c.y = m08c.z = 0.0f;
  m0bc.x = m0bc.y = m0bc.z = 0.0f;
  m0cc.x = m0cc.y = m0cc.z = 0.0f;
  m0d8.x = m0d8.y = m0d8.z = 0.0f;
  m0e4.x = m0e4.y = m0e4.z = 0.0f;
  m0f0 = 1.0f;
  return this;
}

// @ 0x009b2f90
unsigned long CapFlag(unsigned long fourcc) {
  switch (fourcc) {
  case 0x74667370: return 0x10;
  case 0x70737267: return 0x40;
  case 0x626d696c: return 2;
  case 0x6e697073: return 8;
  case 0x7274736e: return 0x80;
  case 0x746f6f66: return 4;
  case 0x746f6f72: return 1;
  case 0x74756f6d: return 0x20;
  default:         return 0;
  }
}

// @ 0x009b3050
bool creature_part_caps_holder::GetCap(unsigned long fourcc, bool bDefault) const {
  for (unsigned long i = 0; i < 32; ++i) {
    unsigned long name = mNames[i];
    if (name == 0)
      break;
    if (fourcc == name)
      return mValues[i];
  }
  return bDefault;
}

// @ 0x009b3090
void creature_part_caps_holder::SetCap(unsigned long fourcc, bool bValue) {
  for (unsigned long i = 0; i < 32; ++i) {
    unsigned long name = mNames[i];
    if (fourcc == name) {
      mValues[i] = bValue;
      Recompute();
      return;
    }
    if (name == 0) {
      mNames[i] = fourcc;
      mValues[i] = bValue;
      Recompute();
      return;
    }
  }
  Recompute();
}

// @ 0x009b3010
void creature_part_caps_holder::Recompute() {
  mFlagsOn = 0;
  mFlags = 0;
  unsigned long i = 0;
  const unsigned long* p = mNames;
  for (; i < 32; ++i, ++p) {
    unsigned long fourcc = *p;
    if (fourcc == 0)
      return;
    unsigned long flag = CapFlag(fourcc);
    mFlags |= flag;
    if (mValues[i])
      mFlagsOn |= flag;
  }
}

// @ 0x009b30e0
bool creature_part_caps_holder::HasCap(unsigned long fourcc) const {
  for (unsigned long i = 0; i < 32; ++i) {
    unsigned long name = mNames[i];
    if (name == 0)
      break;
    if (fourcc == name)
      return true;
  }
  return false;
}

// @ 0x009b3110
unsigned long creature_part_caps_holder::GetFreeSlot() const {
  unsigned long i = 0;
  for (; i < 32; i += 4) {
    if (mNames[i + 0] == 0) return i + 0;
    if (mNames[i + 1] == 0) return i + 1;
    if (mNames[i + 2] == 0) return i + 2;
    if (mNames[i + 3] == 0) return i + 3;
  }
  return i;
}

// @ 0x009b3150
bool SameCaps(const creature_part_caps_holder* a, const creature_part_caps_holder* b) {
  for (unsigned long i = 0; i < 32; ++i) {
    if (a->mNames[i] == 0)
      return true;
    if (a->mNames[i] != b->mNames[i])
      return false;
  }
  return true;
}

}  // namespace nSPCreatureAnim
