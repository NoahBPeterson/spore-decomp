// nSPCreatureAnim context/pose helpers (slice s009afda0).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2
#include "types.h"
#include <math.h>

extern const float DAT_01550bec;  // 0x01550bec  (0.7f)
extern const float DAT_01485378;  // 0x01485378  (0.0f: retail multiplies the folded term by it)
extern const float DAT_013eb1bc;  // 0x013eb1bc  (-1.0f: initial best score)
extern const float DAT_013ec4b8;  // 0x013ec4b8  (1e-8f: length bias)
extern const float DAT_01485720;  // 0x01485720  (1.0f: vertical weight)

// --- out-of-line helpers (masked) ---
extern "C" void FUN_009cd580(int obj, float* out, int a, int flags);
extern "C" void FUN_0099c310(void* out, void* rot, const float* delta);

namespace nSPCreatureAnim {

struct vector_3 { float x, y, z; };

struct creature_body_instance_data {
  char pad_000[0x154];
  uint32_t flags154;  // +0x154
  char pad_158[0x468 - 0x158];
};

struct creature_instance_data {
  char pad_000[0x384];
  creature_body_instance_data* bodies_begin;  // +0x384
  creature_body_instance_data* bodies_end;    // +0x388
};

struct context_target {
  uint32_t mFlags;   // +0x00
  char pad_04[0x10];
  int ctx14;         // +0x14
};

// 0x468-byte node of the bone/context tree walked by FUN_009b05b0.
struct creature_bone_node {
  char pad_000[0x150];
  uint8_t flags;                             // +0x150
  char pad_151[0x1f8 - 0x151];
  uint32_t id1f8;                            // +0x1f8
  char pad_1fc[0x208 - 0x1fc];
  uint32_t child_count;                      // +0x208
  char pad_20c[0x218 - 0x20c];
  creature_bone_node* children;              // +0x218
  char pad_21c[0x350 - 0x21c];
  float x350;                                // +0x350
  float y354;                                // +0x354
  float z358;                                // +0x358
};

struct animation_frame_40 {
  char pad_00[0x18];
  float pos[3];      // +0x18
  char pad_24[0x18];
  float rot[3];      // +0x3c
};

void MirrorSagittalContextTarget(uint32_t* src, uint32_t* dst);

}  // namespace nSPCreatureAnim

// @ 0x009B00C0
// The body count is a SIGNED quotient (imul/sar by the 0x468 magic) but the walk compares the
// index against it UNSIGNED (`cmp ecx,eax; jb`), so a negative quotient scans on past the array
// instead of stopping at once. The return value is that quotient in eax with only al replaced by
// the 0/1 flag, which is why this is a u32 rather than a bool.
uint32_t __cdecl FUN_009b00c0(nSPCreatureAnim::creature_instance_data* c, uint32_t mask) {
  int count = (int)((char*)c->bodies_end - (char*)c->bodies_begin) / 0x468;
  uint32_t found = 0;
  if (count != 0) {
    nSPCreatureAnim::creature_body_instance_data* body = c->bodies_begin;
    for (uint32_t i = 0; i < (uint32_t)count; i++) {
      if ((body->flags154 & mask) != 0) {
        found = 1;
        break;
      }
      body = (nSPCreatureAnim::creature_body_instance_data*)((char*)body + 0x468);
    }
  }
  return ((uint32_t)count & ~0xffu) | found;
}

// @ 0x009B0120
// The 1 - (a*a + c*c)*2 term of the retail expression is computed and then multiplied by 0.0f,
// so it only survives as a NaN/zero; the value actually compared is -2*(c*b + d*a).
bool __cdecl FUN_009b0120(nSPCreatureAnim::creature_instance_data* c) {
  float* q = (float*)((char*)c->bodies_begin + 0x118);  // a,b,c,d
  float a = q[0], b = q[1], c2 = q[2], d = q[3];
  // Both of the first two terms sit inside the multiply by 0.0f (so an infinite term turns the
  // whole result into NaN); only the (c*b + d*a) term survives.
  float folded = (0.0f - (1.0f - (a * a + c2 * c2) * 2.0f)) - (b * a - c2 * d) * 2.0f;
  float r = folded * DAT_01485378 + (0.0f - (c2 * b + d * a) * 2.0f);
  return r > DAT_01550bec;
}

// @ 0x009B01E0  cubic smoothstep / blend
float __cdecl FUN_009b01e0(float a, float b, float t) {
  // Retail keeps the UNROUNDED b - a on the x87 stack (`fld b; fsub a; fst [esp]; fabs`), so the
  // FLT_MIN threshold test runs on the exact difference; only the sum is rounded into the stack
  // slot that the division by (b - a) reads. The blend itself is SSE single precision: the clamp
  // (`t <= a -> a`, `t > b -> b`) then u = (t - a)/d, u2 = u*u rounded to float, and the
  // 3u^2 - 2u^3 polynomial evaluated in x87 from the two rounded floats.
  volatile double de = (double)b - (double)a;   // spills, so no xmm is held across the branch
  float d = (float)de;                          // retail's spilled float copy
  if (de < 1.1754944e-38 && de > -1.1754944e-38) {
    if (!(a < t))     // NaN falls into the "t <= a" arm, like retail's `comiss a,t; jb`
      return 0.0f;
    if (!(t < b))
      return 1.0f;
    return 0.5f;
  }
  if (!(a < t))
    t = a;
  if (b < t)
    t = b;
  float u = (t - a) / d;
  float u2 = u * u;
  return 3.0f * u2 - (u2 * u + u2 * u);
}

// @ 0x009B0280
void __cdecl nSPCreatureAnim::MirrorSagittalContextTarget(uint32_t* src, uint32_t* dst) {
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
  dst[3] = src[3];

  uint32_t f = src[0] & 0x2000c;
  if (f > 0x20000) {
    if (f == 0x20004)
      f = 0x20000;
  } else {
    if (f == 0x20000)
      f = 0x20004;
    else if (f == 4)
      f = 8;
    else if (f == 8)
      f = 4;
  }
  uint32_t v = (dst[0] & 0xfffdfff3) | f;

  uint32_t g = src[0] & 0xe000;
  if (g == 0x2000)
    g = 0x4000;
  else if (g == 0x4000)
    g = 0x2000;

  dst[0] = (v & 0xffff1fff) | g;
}

// @ 0x009B0320  (static helper: append `value` to array[0..*count) if not already present)
void AddUnique(int* array, uint32_t* count, int value) {
  uint32_t n = *count;
  for (uint32_t i = 0; i < n; i++) {
    if (array[i] == value)
      return;
  }
  array[n] = value;
  *count = n + 1;
}

// @ 0x009B0720
void* __cdecl FUN_009b0720(void* out, int obj, nSPCreatureAnim::context_target* ctx,
                           void* src) {
  if ((ctx->ctx14 & 0x100003) == 2) {
    nSPCreatureAnim::animation_frame_40* f = (nSPCreatureAnim::animation_frame_40*)obj;
    float v[3];
    v[0] = v[1] = v[2] = 0.0f;
    FUN_009cd580(obj, v, 0, ctx->mFlags & 0x20);
    float d[3];
    d[0] = v[0] - f->pos[0];
    d[1] = v[1] - f->pos[1];
    d[2] = v[2] - f->pos[2];
    FUN_0099c310(out, (char*)obj + 0x3c, d);
    return out;
  }
  float* s = (float*)src;
  float* o = (float*)out;
  o[0] = s[0];
  o[1] = s[1];
  o[2] = s[2];
  return out;
}

// --- larger functions in the slice (partial; see partial.txt) ---

// @ 0x009AFDA0  PARTIAL: context-target evaluation entry point.
void __fastcall FUN_009afda0(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }

// @ 0x009AFE90  PARTIAL: context-target blending.
void __fastcall FUN_009afe90(void* self, void* a) { (void)self; (void)a; }

// @ 0x009B0340  PARTIAL: pose/context resolution helper.
void __fastcall FUN_009b0340(void* self) { (void)self; }

// @ 0x009B05B0  collect the ids of the flagged nodes below `node` into an id set.
void __cdecl FUN_009b05b0(nSPCreatureAnim::creature_bone_node* node, uint32_t* out,
                           uint32_t* count) {
  bool any = false;
  volatile uint32_t remaining = node->child_count;   // retail keeps this counter in a stack slot
  if (remaining != 0) {
    nSPCreatureAnim::creature_bone_node* child = node->children;
    for (; remaining != 0; remaining--) {
      if ((child->flags & 0xa) != 0) {
        any = true;
        FUN_009b05b0(child, out, count);
      }
      child = (nSPCreatureAnim::creature_bone_node*)((char*)child + 0x468);
    }
    if (any)
      return;
  }
  uint32_t id;
  if ((node->flags & 0xa) != 0) {
    // No flagged child won, so pick the nearest own child: 1 / (|p| + 1e-8) scaled by the
    // (deliberately zeroed) horizontal term and the vertical one, i.e. the most negative y.
    nSPCreatureAnim::creature_bone_node* best = 0;
    float bestScore = DAT_013eb1bc;
    nSPCreatureAnim::creature_bone_node* child = node->children;
    for (uint32_t n = node->child_count; n != 0; n--) {
      double len2 = (double)child->x350 * child->x350;
      len2 += (double)child->y354 * child->y354;
      len2 += (double)child->z358 * child->z358;
      float t = (float)(1.0 / (sqrt(len2) + DAT_013ec4b8));
      float x = child->x350, y = child->y354, z = child->z358;
      float sum = (float)((double)(z * t) + (double)(x * t));
      float score = sum * DAT_01485378 - y * t * DAT_01485720;
      if (score > bestScore) {
        bestScore = score;
        best = child;
      }
      child = (nSPCreatureAnim::creature_bone_node*)((char*)child + 0x468);
    }
    id = (best != 0 ? best : node)->id1f8;
  } else {
    id = node->id1f8;
  }
  uint32_t n = *count;
  for (uint32_t i = 0; i < n; i++) {
    if (out[i] == id)
      return;
  }
  out[n] = id;
  *count = n + 1;
}

// @ 0x009B07D0  PARTIAL: large context/IK update routine.
void __fastcall FUN_009b07d0(void* self) { (void)self; }
