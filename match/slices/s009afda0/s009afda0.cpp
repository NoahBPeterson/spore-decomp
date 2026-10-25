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
extern "C" void FUN_0099c310(void* out, void* rot, void* delta);
extern "C" void FUN_009ae7e0(void* p, unsigned a, unsigned b);            // 0x009ae7e0
extern "C" char FUN_009ae450(void* out1, void* out2, void* ctx);          // 0x009ae450
extern "C" void FUN_009add80(void* self, unsigned p3);                     // 0x009add80
extern "C" void FUN_009adfd0(void* self);                                 // 0x009adfd0
extern "C" void* FUN_009b62c0(void* out, void* in);                       // 0x009b62c0
extern "C" void FUN_009ac690(float t, int* frame, int* nextFrame);        // 0x009ac690
extern "C" void FUN_009adb30(void* a, void* b);                           // 0x009adb30
extern "C" float* FUN_009a49d0(float* out, const float* v, void* unk);    // 0x009a49d0
extern "C" void FUN_009a4a70(float* a, float* b, float* c);               // 0x009a4a70
extern "C" float* FUN_0099c1a0(float* out, void* q, float* v);            // 0x0099c1a0
extern int DAT_0166c0c8;   // 0x0166c0c8
extern int DAT_01550aa0;   // 0x01550aa0
extern int DAT_01550a6c;   // 0x01550a6c

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

// @ 0x009AFDA0  context-target evaluation entry point (thiscall, 3 stack args)
void __fastcall FUN_009afda0(void* selfPtr, int, unsigned p2, void* p3, void* p4)
{
    int* self = (int*)selfPtr;
    unsigned char local1c[12];
    unsigned char local10[16];

    int root = *self;
    int* node = (int*)(p2 * 700 + *(int*)(root + 0x2e4));
    if (*(unsigned*)(*node + 0x444) <
        (unsigned)((*(int*)(root + 0x2e8) - *(int*)(root + 0x2e4)) / 700)) {
        FUN_009ae7e0(node, (unsigned)p3, (unsigned)p4);
        return;
    }
    char ok = FUN_009ae450(local1c, local10, node);
    if (ok == 0) {
        if (*(char*)(*node + 0x464) == 0)
            goto scan;
        FUN_009add80(self, (unsigned)p3);
    }
    FUN_009adfd0(self);

scan:
    unsigned first = *(unsigned*)(*node + 0x204);
    unsigned last = *(int*)(*node + 0x208) + first;
    for (unsigned i = first; i < last; ++i)
        FUN_009afda0(self, 0, i, local1c, local10);
}

// @ 0x009AFE90  build the interpolation record and run the context-target pass.
struct pose_root {
    char pad[0x2e4];
    int nodesBegin;   // +0x2e4
    int nodesEnd;     // +0x2e8
};
struct context_anim {
    char pad0[0xc];
    int frameCount;   // +0x0c
    char pad10[4];
    float duration;   // +0x14
    char pad18[0x20];
    char frames[];    // +0x38
};
struct blend_pose {
    void*    mpRoot;    // +0x00
    int*     mpSelf;    // +0x04
    void*    mpFrame;   // +0x08
    float    mBlend;    // +0x0c
    unsigned mArg5;     // +0x10
    unsigned mArg6;     // +0x14
    unsigned char mArg4;// +0x18
    char     pad19[3];
    float    mQx;       // +0x1c
    float    mQy;       // +0x20
    float    mQz;       // +0x24
    unsigned mFlags;    // +0x28
    unsigned mZero;     // +0x2c
};

void __fastcall FUN_009afe90(void* selfPtr, int, float p2, void* animRoot,
                             int p4, unsigned p5, unsigned p6)
{
    int* self = (int*)selfPtr;
    context_anim* anim = (context_anim*)*self;
    blend_pose frame;
    float pos[3];
    float quat[4];
    int frameIndex;
    int nextFrame;

    self[2] = DAT_0166c0c8++;
    int iVar2 = (((pose_root*)animRoot)->nodesEnd - ((pose_root*)animRoot)->nodesBegin) / 700;

    if (*self == 0)
        return;

    float maxTime = anim->duration;
    if (p2 <= 0.0f)
        p2 = 0.0f;
    if (maxTime < p2)
        p2 = maxTime;

    void* qsrc = FUN_009b62c0(quat, (char*)animRoot + 0x18);
    FUN_0099c310(pos, (char*)animRoot + 0x3c, qsrc);

    unsigned flags = *(unsigned*)((char*)animRoot + 0x10c);
    FUN_009ac690(p2, &frameIndex, &nextFrame);

    int* owner = (int*)*self;
    int stride = owner[3] * 8 + 0x54;
    char* f = (char*)owner + 0x38 + stride * frameIndex;
    char* next = f;
    float blend = 0.0f;
    if (frameIndex != nextFrame) {
        char* n = (char*)owner + 0x38 + stride * nextFrame;
        blend = (p2 - *(float*)(f + 4)) / (*(float*)(n + 0x3c) - *(float*)(f + 4));
        next = n;
    }

    frame.mpRoot = (void*)animRoot;
    frame.mpSelf = self;
    frame.mpFrame = next;
    frame.mBlend = blend;
    frame.mArg5 = p5;
    frame.mArg6 = p6;
    frame.mArg4 = (unsigned char)p4;
    frame.mQx = pos[0];
    frame.mQy = pos[1];
    frame.mQz = pos[2];
    frame.mFlags = flags;
    frame.mZero = 0;

    if (DAT_01550aa0 != 0) {
        quat[3] = 1.0f;
        pos[0] = pos[1] = pos[2] = 0.0f;
        quat[0] = quat[1] = quat[2] = 0.0f;
        FUN_009afda0(&frame, 0, 0, pos, quat);
        return;
    }
    for (int i = 0; i < iVar2; ++i) {
        FUN_009adb30(0, quat);
        FUN_009adfd0(&frame);
    }
}

// @ 0x009B0340  build one basis row + the two remaining rows of a 3x3 matrix.
int __cdecl FUN_009b0340(int out, float* p2, float* p3, unsigned* p4, int p5,
                         unsigned p6, float p7, float p8, float p9)
{
    float local_c[3];
    float local_30, local_2c, local_28;
    float local_24, local_20, local_1c;
    float local_18, local_14, local_10;

    local_24 = p3[0] - p2[0];
    local_20 = p3[1] - p2[1];
    local_1c = p3[2] - p2[2];
    local_18 = local_14 = local_10 = 0.0f;

    float* pfVar1 = FUN_009a49d0(local_c, &local_24, &p3);
    local_30 = pfVar1[0];
    local_2c = pfVar1[1];
    local_28 = pfVar1[2];
    if (p4 != 0)
        *p4 = (unsigned)p3;

    // Retail's first degenerate test compares the (pointer) argument bits; a live
    // direction pointer always takes the general path.
    if (p3 == 0) {
        local_18 = 0.0f;
        local_20 = 1.0f;
        local_30 = 1.0f;
        local_2c = 0.0f;
        local_28 = 0.0f;
        local_24 = 0.0f;
        local_1c = 0.0f;
        local_14 = 0.0f;
        local_10 = 1.0f;
    } else {
        local_24 = p8 * local_28 - p9 * local_2c;
        local_20 = p9 * local_30 - local_28 * p7;
        local_1c = local_2c * p7 - p8 * local_30;
        pfVar1 = FUN_009a49d0(local_c, &local_24, &p3);
        local_24 = pfVar1[0];
        local_20 = pfVar1[1];
        local_1c = pfVar1[2];
        if (pfVar1[0] * pfVar1[0] + pfVar1[1] * pfVar1[1] + pfVar1[2] * pfVar1[2] <= 1e-6f) {
            FUN_009a4a70(&local_30, &local_24, &local_18);
        } else {
            local_18 = local_2c * local_1c - local_20 * local_28;
            local_14 = local_28 * local_24 - local_1c * local_30;
            local_10 = local_20 * local_30 - local_2c * local_24;
        }
    }

    unsigned uVar2 = (p5 + 1u) % 3u;
    *(float*)(out + p5 * 4) = local_30;
    *(float*)(out + 0xc + p5 * 4) = local_2c;
    *(float*)(out + 0x18 + p5 * 4) = local_28;
    *(float*)(out + p6 * 4) = local_18;
    *(float*)(out + 0xc + p6 * 4) = local_14;
    *(float*)(out + 0x18 + p6 * 4) = local_10;
    if (uVar2 == p6) {
        local_24 = -local_24;
        local_20 = -local_20;
        local_1c = -local_1c;
        uVar2 = (p5 + 2u) % 3u;
    }
    *(float*)(out + 0x18 + uVar2 * 4) = local_1c;
    *(float*)(out + 0xc + uVar2 * 4) = local_20;
    *(float*)(out + uVar2 * 4) = local_24;
    return out;
}

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

// @ 0x009B07D0  build the orientation basis used by the context/IK update.
void __cdecl FUN_009b07d0(void* unused, float* quat, void* transform,
                           float* dirA, float* dirB, void* out)
{
    (void)unused;
    float rot[3];
    float rot2[3];
    float dir[3];
    float tmp[3];
    float basis[3];
    float matrix[9];

    float qx = quat[0], qz = quat[2];
    float qv[3];
    qv[0] = -((quat[1] * qx - qz * quat[3]) * 2.0f);
    qv[1] = -(1.0f - (qz * qz + qx * qx) * 2.0f);
    qv[2] = -((qz * quat[1] + quat[3] * qx) * 2.0f);
    FUN_0099c1a0(rot, transform, qv);

    float dx = dirA[0] - dirB[0];
    float dy = dirA[1] - dirB[1];
    float dz = dirA[2] - dirB[2];
    float len = sqrtf(dx * dx + dy * dy + dz * dz);
    if (len != 0.0f) {
        float inv = 1.0f / len;
        dx *= inv;
        dy *= inv;
        dz *= inv;
    }
    dir[0] = dx;
    dir[1] = dy;
    dir[2] = dz;

    float dot = rot[0] * dir[0] + rot[1] * dir[1] + rot[2] * dir[2];
    if (dot < 0.7f) {
        if (dot < -0.3f) {
            if (dot < -0.5f) {
                float t = FUN_009b01e0(-1.0f, -0.5f, dot);
                t = (1.0f - t * 0.8f) - dot;
                tmp[0] = rot[0] * t + dir[0];
                tmp[1] = rot[1] * t + dir[1];
                tmp[2] = rot[2] * t + dir[2];
                float* r = FUN_009a49d0(rot, tmp, 0);
                dir[0] = r[0];
                dir[1] = r[1];
                dir[2] = r[2];
            } else {
                float k = 0.2f - dot;
                tmp[0] = rot[0] * k + dir[0];
                tmp[1] = rot[1] * k + dir[1];
                tmp[2] = rot[2] * k + dir[2];
                float* r = FUN_009a49d0(tmp, tmp, 0);
                dir[0] = r[0];
                dir[1] = r[1];
                dir[2] = r[2];
            }
        } else {
            float t = FUN_009b01e0(-0.3f, 0.7f, dot);
            float k = (t * 0.5f + 0.2f) - dot;
            tmp[0] = rot[0] * k + dir[0];
            tmp[1] = rot[1] * k + dir[1];
            tmp[2] = rot[2] * k + dir[2];
            float l = sqrtf(tmp[0] * tmp[0] + tmp[1] * tmp[1] + tmp[2] * tmp[2]);
            if (l != 0.0f) {
                float inv = 1.0f / l;
                tmp[0] *= inv;
                tmp[1] *= inv;
                tmp[2] *= inv;
            }
            dir[0] = tmp[0];
            dir[1] = tmp[1];
            dir[2] = tmp[2];
        }
    }

    if (DAT_01550a6c != 0) {
        tmp[0] = dirB[0] + dir[0];
        tmp[1] = dirB[1] + dir[1];
        tmp[2] = dirB[2] + dir[2];
        dirA = tmp;
    }
    rot2[0] = dirA[0];
    rot2[1] = dirA[1];
    rot2[2] = dirA[2];

    float* pf = basis;
    if (DAT_01550a6c == 0) {
        basis[0] = 0.0f;
        basis[1] = 0.0f;
        basis[2] = 1.0f;
    } else {
        float qy = quat[1];
        basis[0] = (qx * qz + qy * quat[3]) * 2.0f;
        basis[1] = (qz * qy - qx * quat[3]) * 2.0f;
        basis[2] = 1.0f - (qx * qx + qy * qy) * 2.0f;
        pf = FUN_0099c1a0(qv, transform, basis);
    }

    float* m = (float*)FUN_009b0340((int)matrix, rot2, dirB, 0, 1, 2,
                                    pf[0], pf[1], pf[2]);
    for (int i = 0; i < 9; ++i)
        ((float*)out)[i] = m[i];
}
