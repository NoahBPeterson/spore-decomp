// nSPCreatureAnim context/pose helpers (slice s009afda0).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2
#include "types.h"

extern const float DAT_01550bec;  // 0x01550bec

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

struct animation_frame_40 {
  char pad_00[0x18];
  float pos[3];      // +0x18
  char pad_24[0x18];
  float rot[3];      // +0x3c
};

void MirrorSagittalContextTarget(uint32_t* src, uint32_t* dst);

}  // namespace nSPCreatureAnim

// @ 0x009B00C0
bool __cdecl FUN_009b00c0(nSPCreatureAnim::creature_instance_data* c, uint32_t mask) {
  int count = (int)((char*)c->bodies_end - (char*)c->bodies_begin) / 0x468;
  if (count != 0) {
    nSPCreatureAnim::creature_body_instance_data* body = c->bodies_begin;
    int i = 0;
    do {
      if ((body->flags154 & mask) != 0)
        return true;
      i++;
      body = (nSPCreatureAnim::creature_body_instance_data*)((char*)body + 0x468);
    } while (i < count);
  }
  return false;
}

// @ 0x009B0120
bool __cdecl FUN_009b0120(nSPCreatureAnim::creature_instance_data* c) {
  float* q = (float*)((char*)c->bodies_begin + 0x118);  // a,b,c,d
  float a = q[0], b = q[1], c2 = q[2], d = q[3];
  float r = (0.0f - (1.0f - (a * a + c2 * c2) * 2.0f)) * 0.0f +
            (0.0f - ((b * a - c2 * d) * 2.0f)) +
            (0.0f - ((c2 * b + d * a) * 2.0f));
  return r > DAT_01550bec;
}

// @ 0x009B01E0  cubic smoothstep / blend
float __cdecl FUN_009b01e0(float a, float b, float t) {
  if (1.1754944e-38f <= (b - a >= 0.0f ? (b - a) : (a - b))) {
    if (t <= a)
      t = a;
    if (b < t)
      t = b;
    float u = (t - a) / (b - a);
    return 3.0f * (u * u) - ((u * u) * u + (u * u) * u);
  }
  if (t <= a)
    return 0.0f;
  if (b <= t)
    return 1.0f;
  return 0.5f;
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
static void AddUnique(int* array, uint32_t* count, int value) {
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

// @ 0x009B05B0  PARTIAL: context event location update.
void __fastcall FUN_009b05b0(void* self) { (void)self; }

// @ 0x009B07D0  PARTIAL: large context/IK update routine.
void __fastcall FUN_009b07d0(void* self) { (void)self; }
