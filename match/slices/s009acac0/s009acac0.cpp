// nSPCreatureAnim::baked_animation::Evaluate (0x009ACAC0, 4193 bytes).
//
// Samples a baked animation at a time, blending the two surrounding key frames, and
// accumulates the sampled root/secondary transforms into two blend accumulators:
//   * `pose`  (arg 1): weighted sums of scale, transform positions/rotations and the
//                      per-frame deltas (walk delta position / rotation),
//   * `prev`  (arg 2): optional accumulation of the raw transforms (+0x2c / +0x50) and the
//                      previous-frame transforms used to compute the deltas (+0x74..+0xa8).
//
// Retail frame layout (differs from the 2008 PDB): the frame array starts at data+0x38, each
// frame is a 0x54-byte header followed by NumBodies 8-byte body states.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (same module as s009ac530).

#include "types.h"

extern uint32_t g_bakedAnimIdCounter;  // 0x0166c0c8

namespace nSPCreatureAnim {

struct Quat {
  float x, y, z, w;
};

struct Vec3 {
  float x, y, z;
};

// Sign-aligned quaternion accumulation: a +/- b depending on the hemisphere of b.
// Out of line at 0x0099cba0 (cdecl, result by hidden pointer).
Quat QuatAccumulate(const Quat& a, const Quat& b);
// Rotates v by the unit quaternion q.  0x0099c310 (cdecl, result by hidden pointer).
Vec3 QuatRotate(const Quat& q, const Vec3& v);

// Inlined form of QuatAccumulate.
inline void AccumQuat(Quat& out, const Quat& a, const Quat& b) {
  if (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w < 0.0f) {
    out.x = a.x - b.x;
    out.y = a.y - b.y;
    out.z = a.z - b.z;
    out.w = a.w - b.w;
  } else {
    out.x = a.x + b.x;
    out.y = a.y + b.y;
    out.z = a.z + b.z;
    out.w = a.w + b.w;
  }
}

inline void ScaleQuat(Quat& out, const Quat& q, float s) {
  out.x = q.x * s;
  out.y = q.y * s;
  out.z = q.z * s;
  out.w = q.w * s;
}

// a * conjugate(b)
inline void MulConj(Quat& out, const Quat& a, const Quat& b) {
  float bx = -b.x;
  float by = -b.y;
  float bz = -b.z;
  float bw = b.w;
  out.x = a.x * bw + a.w * bx - a.z * by + a.y * bz;
  out.y = a.y * bw + a.w * by + a.z * bx - a.x * bz;
  out.z = a.z * bw - a.y * bx + a.w * bz + a.x * by;
  out.w = a.w * bw - a.x * bx - a.y * by - a.z * bz;
}

// A weighted transform: homogeneous position, quaternion and the quaternion's weight.
struct BlendTransform {
  float pos[4];   // +0x00 (pos[3] = accumulated position weight)
  Quat rot;       // +0x10
  float weight;   // +0x20

  // 0x0099ce40: divides the position by its weight and normalises the rotation.
  void Normalize();

  void Set(const BlendTransform& o) {
    pos[0] = o.pos[0];
    pos[1] = o.pos[1];
    pos[2] = o.pos[2];
    pos[3] = o.pos[3];
    rot.x = o.rot.x;
    rot.y = o.rot.y;
    rot.z = o.rot.z;
    rot.w = o.rot.w;
    weight = o.weight;
  }

  void Accumulate(const BlendTransform& src, float w) {
    pos[0] += src.pos[0] * w;
    pos[1] += src.pos[1] * w;
    pos[2] += src.pos[2] * w;
    pos[3] += src.pos[3] * w;
    Quat q;
    ScaleQuat(q, src.rot, w);
    AccumQuat(rot, rot, q);
    weight += src.weight * w;
  }
};

struct baked_animation_frame {
  uint32_t Flags;          // +0x00
  float Time;              // +0x04
  float Scale;             // +0x08
  BlendTransform root;     // +0x0c
  BlendTransform second;   // +0x30
  // +0x54: NumBodies 8-byte body states
};

struct baked_animation_data {
  uint32_t MagicBANI;  // +0x00
  uint32_t SizeBytes;  // +0x04
  uint32_t Version;    // +0x08
  uint32_t NumBodies;  // +0x0c
  uint32_t NumFrames;  // +0x10
  float Duration;      // +0x14
  uint32_t pad_18[8];  // +0x18
  // +0x38: frames

  baked_animation_frame* GetFrame(uint32_t i) {
    return (baked_animation_frame*)((char*)this + 0x38 + (NumBodies * 8 + 0x54) * i);
  }
};

// Weighted pose accumulator (arg 1).
struct anim_pose_accum {
  uint32_t pad_00[0x110 / 4];
  float scaleSum;          // +0x110
  float weightSum;         // +0x114
  float rootPos[4];        // +0x118
  Quat rootRot;            // +0x128
  float rootRotWeight;     // +0x138
  float rootDeltaPos[3];   // +0x13c
  float rootDeltaPosW;     // +0x148
  Quat rootDeltaRot;       // +0x14c
  float rootDeltaRotW;     // +0x15c
  float walkDeltaPos[3];   // +0x160
  float walkDeltaPosW;     // +0x16c
  Quat walkDeltaRot;       // +0x170
  float walkDeltaRotW;     // +0x180
  float moveDeltaPos[3];   // +0x184
  float moveDeltaPosW;     // +0x190
  Quat moveDeltaRot;       // +0x194
  float moveDeltaRotW;     // +0x1a4
};

// Raw transform accumulator / previous-frame state (arg 2).
struct anim_prev_state {
  uint32_t pad_00[0x2c / 4];
  BlendTransform root;     // +0x2c
  BlendTransform second;   // +0x50
  float prevRootPos[3];    // +0x74
  Quat prevRootRot;        // +0x80
  float prevSecondPos[3];  // +0x90
  Quat prevSecondRot;      // +0x9c
};

struct baked_animation {
  baked_animation_data* data;  // +0x00
  uint32_t CurrentNumFrames;   // +0x04
  uint32_t LRUSequence;        // +0x08
  char Filename[260];          // +0x0c
  int RefCount;                // +0x110

  void GetFrameRange(float t, uint32_t* outStart, uint32_t* outEnd);  // 0x009ac690
  void Evaluate(float time, anim_pose_accum* pose, anim_prev_state* prev, float w,
                bool accumulateDeltas, bool accumulateRaw, bool skipDeltas);
};

// @ 0x009ACAC0
void baked_animation::Evaluate(float time, anim_pose_accum* pose, anim_prev_state* prev,
                               float w, bool accumulateDeltas, bool accumulateRaw,
                               bool skipDeltas) {
  LRUSequence = g_bakedAnimIdCounter;
  g_bakedAnimIdCounter++;

  float duration = data ? data->Duration : 0.0f;
  float t = time > 0.0f ? time : 0.0f;
  time = t > duration ? duration : t;

  uint32_t start, end;
  GetFrameRange(time, &start, &end);

  baked_animation_data* d = data;
  uint32_t stride = d->NumBodies * 8 + 0x54;
  baked_animation_frame* fa = (baked_animation_frame*)((char*)d + stride * start + 0x38);
  uint32_t flags = fa->Flags;
  bool keyedFoot = (flags >> 1) & 1;
  bool overrideGait = (flags >> 2) & 1;

  float scale;
  BlendTransform root;
  BlendTransform second;
  if (start == end) {
    scale = fa->Scale;
    root.Set(fa->root);
    second.Set(fa->second);
  } else {
    baked_animation_frame* fb = (baked_animation_frame*)((char*)d + stride * end + 0x38);
    float u = (time - fa->Time) / (fb->Time - fa->Time);
    float v = 1.0f - u;
    Quat qa, qb;

    scale = fa->Scale * v + fb->Scale * u;
    root.pos[0] = fa->root.pos[0] * v + fb->root.pos[0] * u;
    root.pos[1] = fa->root.pos[1] * v + fb->root.pos[1] * u;
    root.pos[2] = fa->root.pos[2] * v + fb->root.pos[2] * u;
    root.pos[3] = fa->root.pos[3] * v + fb->root.pos[3] * u;
    ScaleQuat(qa, fa->root.rot, v);
    ScaleQuat(qb, fb->root.rot, u);
    AccumQuat(root.rot, qa, qb);
    root.weight = fa->root.weight * v + fb->root.weight * u;

    second.pos[0] = fa->second.pos[0] * v + fb->second.pos[0] * u;
    second.pos[1] = fa->second.pos[1] * v + fb->second.pos[1] * u;
    second.pos[2] = fa->second.pos[2] * v + fb->second.pos[2] * u;
    second.pos[3] = fa->second.pos[3] * v + fb->second.pos[3] * u;
    ScaleQuat(qa, fa->second.rot, v);
    ScaleQuat(qb, fb->second.rot, u);
    AccumQuat(second.rot, qa, qb);
    second.weight = fa->second.weight * v + fb->second.weight * u;
  }

  pose->scaleSum += scale * w;
  pose->weightSum += w;

  if (accumulateRaw) {
    prev->root.Accumulate(root, w);
    prev->second.Accumulate(second, w);
  }

  if (!accumulateDeltas)
    return;

  root.Normalize();
  second.Normalize();

  pose->rootPos[0] += root.pos[0] * w;
  pose->rootPos[1] += root.pos[1] * w;
  pose->rootPos[2] += root.pos[2] * w;
  pose->rootPos[3] += root.pos[3] * w;

  if (!skipDeltas) {
    if (!keyedFoot) {
      pose->rootDeltaPos[0] += (root.pos[0] - prev->prevRootPos[0]) * w;
      pose->rootDeltaPos[1] += (root.pos[1] - prev->prevRootPos[1]) * w;
      pose->rootDeltaPos[2] += (root.pos[2] - prev->prevRootPos[2]) * w;
      pose->rootDeltaPosW += w;
    }
    Vec3 d;
    d.x = (second.pos[0] - prev->prevSecondPos[0]) * w;
    d.y = (second.pos[1] - prev->prevSecondPos[1]) * w;
    d.z = (second.pos[2] - prev->prevSecondPos[2]) * w;
    Vec3 r = QuatRotate(prev->prevSecondRot, d);
    pose->walkDeltaPos[0] += r.x;
    pose->walkDeltaPos[1] += r.y;
    pose->walkDeltaPos[2] += r.z;
    pose->walkDeltaPosW += w;
    if (!overrideGait) {
      pose->moveDeltaPos[0] += r.x;
      pose->moveDeltaPos[1] += r.y;
      pose->moveDeltaPos[2] += r.z;
      pose->moveDeltaPosW += w;
    }
  }

  prev->prevRootPos[0] = root.pos[0];
  prev->prevRootPos[1] = root.pos[1];
  prev->prevRootPos[2] = root.pos[2];
  prev->prevSecondPos[0] = second.pos[0];
  prev->prevSecondPos[1] = second.pos[1];
  prev->prevSecondPos[2] = second.pos[2];

  Quat rq;
  ScaleQuat(rq, root.rot, w);
  AccumQuat(pose->rootRot, pose->rootRot, rq);
  pose->rootRotWeight += root.weight * w;

  if (!skipDeltas) {
    if (!keyedFoot) {
      Quat d;
      MulConj(d, rq, prev->prevRootRot);
      pose->rootDeltaRot = QuatAccumulate(pose->rootDeltaRot, d);
      pose->rootDeltaRotW += w;
    }
    Quat sq, d2;
    ScaleQuat(sq, second.rot, w);
    MulConj(d2, sq, prev->prevSecondRot);
    AccumQuat(pose->walkDeltaRot, pose->walkDeltaRot, d2);
    pose->walkDeltaRotW += w;
    if (!overrideGait) {
      pose->moveDeltaRot = QuatAccumulate(pose->moveDeltaRot, d2);
      pose->moveDeltaRotW += w;
    }
  }

  prev->prevRootRot = root.rot;
  prev->prevSecondRot = second.rot;
}

}  // namespace nSPCreatureAnim
