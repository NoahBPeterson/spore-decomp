// nSPCreatureAnim::creature_static_data / creature_instance_data helpers (slice s009b3180).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2
#include "types.h"
#include <xmmintrin.h>
#include <math.h>

extern const float DAT_013fe14c;  // 0.375f
extern const float DAT_0141b034;  // 0.625f

extern const float DAT_01550d50;  // 10.0f
extern const float DAT_01550d4c;  // 2.3f
extern const float DAT_01550d54;  // 2.3f
extern const float DAT_0144725c;  // 0.1745f
extern const float DAT_014471f8;  // pi
extern const float DAT_01447260;  // 0.2269f
extern const float DAT_01485378;  // 0.0f
extern const float DAT_01471064;  // 0.5f
extern const float DAT_01485720;  // 1.0f
extern float DAT_0166c270;
extern uint32_t DAT_0166c274;
extern float DAT_0166c27c;
extern float DAT_0166c278;
extern uint32_t DAT_0166c280;
extern const __m128 DAT_013eb8b0;  // all-lane sign mask

#include <string.h>

int Sprintf8(char* dst, const char* fmt, ...);  // 0x00938470

namespace nSPCreatureAnim {

struct creature_instance_data;

// @ 0x009B33F0
float __cdecl GetAnimationBlend(int obj) {
  float* p = (float*)obj;
  return ((float*)((char*)p + 0x438))[0] * 0.375f +
         ((float*)((char*)p + 0x434))[0] * 0.625f;
}

// @ 0x009B3430
char __stdcall FUN_009b3430(int a, int b) {
  return ((b - a) >> 3) + 1 >= 4;
}

// @ 0x009B3460
int __cdecl FUN_009b3460(int obj) {
  int i = *(int*)(*(int*)(obj + 0x214) + 0x210);
  if (i == 0) {
    i = FUN_009b3460(*(int*)(obj + 0x214));
    *(int*)(obj + 0x210) = i;
    return i;
  }
  *(int*)(obj + 0x210) = i;
  return i;
}

// @ 0x009B3920
struct TargetFrame {
  char pad_000[0x1644];
  float posA[3];  // +0x1644
  float posB[4];  // +0x1650
  void Set(const float* a, const float* b);
};

void TargetFrame::Set(const float* a, const float* b) {
  posA[0] = a[0];
  posA[1] = a[1];
  posA[2] = a[2];
  posB[0] = b[0];
  posB[1] = b[1];
  posB[2] = b[2];
  posB[3] = b[3];
}

// @ 0x009B3BC0
void __cdecl FUN_009b3bc0(int obj) {
  float* p = (float*)(obj + 0x118);
  for (int i = 0; i < 9; i++)
    p[i] = 0.0f;
}

// @ 0x009B3C80
struct Transform30 {
  int a;         // +0x00
  int b;         // +0x04
  float f[10];   // +0x08
  Transform30& operator=(const Transform30& src);
};

Transform30& Transform30::operator=(const Transform30& src) {
  a = src.a;
  b = src.b;
  f[0] = src.f[0];
  f[1] = src.f[1];
  f[2] = src.f[2];
  f[3] = src.f[3];
  f[4] = src.f[4];
  f[5] = src.f[5];
  f[6] = src.f[6];
  f[7] = src.f[7];
  f[8] = src.f[8];
  f[9] = src.f[9];
  return *this;
}

// @ 0x009B3AB0
struct CopyBlock {
  int a[4];       // +0x00
  float f[10];    // +0x10
  char c;         // +0x38
  CopyBlock& operator=(const CopyBlock& src);
};

CopyBlock& CopyBlock::operator=(const CopyBlock& src) {
  a[0] = src.a[0];
  a[1] = src.a[1];
  a[2] = src.a[2];
  a[3] = src.a[3];
  f[0] = src.f[0];
  f[1] = src.f[1];
  f[2] = src.f[2];
  f[3] = src.f[3];
  f[4] = src.f[4];
  f[5] = src.f[5];
  f[6] = src.f[6];
  f[7] = src.f[7];
  f[8] = src.f[8];
  f[9] = src.f[9];
  c = src.c;
  return *this;
}

}  // namespace nSPCreatureAnim

// --- larger functions in the slice (partial; see partial.txt) ---

// Small vector/quaternion value types used by the transform-shuffle helper (0x009b3b20).
struct anim_vec3 {
  float x, y, z;
};

struct anim_vec4 {
  float x, y, z, w;
};

// View of the instance prefix that the transform-shuffle helper reads/writes (+0x18 .. +0x6c).
struct anim_transform_view {
  char        mPad000[0x18];
  anim_vec3   mPos;       // +0x18
  anim_vec3   mPrevPos;   // +0x24
  anim_vec3   mTmpPos;    // +0x30
  anim_vec4   mRot;       // +0x3c
  anim_vec4   mPrevRot;   // +0x4c
  anim_vec4   mTmpRot;    // +0x5c
  float       mScale;     // +0x6c
  void Shuffle(const anim_vec3* pos, const anim_vec4* rot, const float* scale);
};

// @ 0x009B3B20
void anim_transform_view::Shuffle(const anim_vec3* pos, const anim_vec4* rot, const float* scale) {
  if (pos) {
    mPrevPos.x = mPos.x;
    mPrevPos.y = mPos.y;
    mPrevPos.z = mPos.z;
    mTmpPos.x = pos->x;
    mTmpPos.y = pos->y;
    mTmpPos.z = pos->z;
    mPos.x = mTmpPos.x;
    mPos.y = mTmpPos.y;
    mPos.z = mTmpPos.z;
  }
  if (rot) {
    mPrevRot.x = mRot.x;
    mPrevRot.y = mRot.y;
    mPrevRot.z = mRot.z;
    mPrevRot.w = mRot.w;
    mTmpRot.x = rot->x;
    mTmpRot.y = rot->y;
    mTmpRot.z = rot->z;
    mTmpRot.w = rot->w;
    mRot.x = mTmpRot.x;
    mRot.y = mTmpRot.y;
    mRot.z = mTmpRot.z;
    mRot.w = mTmpRot.w;
  }
  if (scale)
    mScale = *scale;
}

// View of the instance prefix holding the "epic gait" flag (+0x2d5).
struct anim_gait_name_view {
  char mPad000[0x2d5];
  char mEpicGait;   // +0x2d5
  bool ComposeGaitFileName(char* out, const char* name, const char* suffix);
};

// @ 0x009B3850
bool anim_gait_name_view::ComposeGaitFileName(char* out, const char* name, const char* suffix) {
  if (!out)
    return false;
  if (!name) {
    Sprintf8(out, "default");
    return true;
  }
  if (suffix && strlen(suffix) == 0)
    suffix = 0;

  char buffer[256];
  Sprintf8(buffer, mEpicGait ? "gait_epic" : "gait");
  if (suffix) {
    Sprintf8(out, "%s%s_%s", buffer, name, suffix);
    return true;
  }
  Sprintf8(out, "%s%s", buffer, name);
  return true;
}

// View of the instance prefix that the identity-fill helper (0x009b3cd0) initialises.
struct anim_identity_view {
  char        mPad000[0x10c];
  anim_vec3   mVec10c;    // +0x10c
  anim_vec4   mQuat118;   // +0x118
  anim_vec4   mQuat128;   // +0x128
  anim_vec3   mVec138;    // +0x138
  anim_vec3   mVec144;    // +0x144
  char        mBlock150[0xa8];            // +0x150
  char        mPad1f8[0x324 - 0x1f8];
  anim_vec3   mVec324;    // +0x324
  anim_vec3   mVec330;    // +0x330
  char        mPad33c[0x344 - 0x33c];
  anim_vec3   mVec344;    // +0x344
  anim_vec3   mVec350;    // +0x350
  anim_vec3   mVec35c;    // +0x35c
  char        mPad368[0x380 - 0x368];
  int         mInt380;    // +0x380
  char        mPad384[0x448 - 0x384];
  anim_vec3   mVec448;    // +0x448
  char        mPad454[0x458 - 0x454];
  anim_vec3   mVec458;    // +0x458
  anim_identity_view* Init();
};

// @ 0x009B3CD0
anim_identity_view* anim_identity_view::Init() {
  const float one = DAT_01485720;
  mVec10c.x = mVec10c.y = mVec10c.z = 0.0f;
  mQuat118.x = mQuat118.y = mQuat118.z = 0.0f;
  mQuat118.w = one;
  mQuat128.x = mQuat128.y = mQuat128.z = 0.0f;
  mQuat128.w = one;
  mVec138.x = mVec138.y = mVec138.z = 0.0f;
  mVec144.x = mVec144.y = mVec144.z = 0.0f;
  memset(mBlock150, 0, sizeof(mBlock150));
  mVec324.x = mVec324.y = mVec324.z = 0.0f;
  mVec330.x = mVec330.y = mVec330.z = 0.0f;
  mVec344.x = mVec344.y = mVec344.z = 0.0f;
  mVec350.x = mVec350.y = mVec350.z = 0.0f;
  mVec35c.x = mVec35c.y = mVec35c.z = 0.0f;
  mInt380 = 0;
  mVec448.x = mVec448.y = mVec448.z = 0.0f;
  mVec458.x = mVec458.y = mVec458.z = 0.0f;
  return this;
}

// --- retail in-memory view of creature_body_static_data (0x465 bytes) -------------------------
// The migrated header layout does not line up with retail (retail stores two quaternions directly
// at +0x118/+0x128 and has an 0xa8-byte caps block at +0x150), so model the retail layout here.

struct cbs_vec3 {
  float x, y, z;
  cbs_vec3& operator=(const cbs_vec3& src) {
    x = src.x;
    y = src.y;
    z = src.z;
    return *this;
  }
};

struct cbs_vec4 {
  float x, y, z, w;
  cbs_vec4& operator=(const cbs_vec4& src) {
    x = src.x;
    y = src.y;
    z = src.z;
    w = src.w;
    return *this;
  }
};

struct cbs_caps {
  int data[42];
};

#pragma pack(push, 4)
struct creature_body_static_view {
  char        name[260];                      // +0x000
  uint32_t    instance_id;                    // +0x104
  uint32_t    group_id;                       // +0x108
  cbs_vec3    rest_center;                    // +0x10c
  cbs_vec4    rest_orientation_q;             // +0x118
  cbs_vec4    rest_parent_rel_orientation_q;  // +0x128
  cbs_vec3    local_half_extents;             // +0x138
  cbs_vec3    local_original_r;               // +0x144
  cbs_caps    caps_block;                     // +0x150 (0xa8)
  int         bidx;                           // +0x1f8
  int         parent_bidx;                    // +0x1fc
  int         symmetric_bidx;                 // +0x200
  int         first_child_bidx;               // +0x204
  int         num_children;                   // +0x208
  int         num_all_children;               // +0x20c
  int         parent;                         // +0x210
  int         first_child;                    // +0x214
  int         bone_idx;                       // +0x218
  int         field_21c;                      // +0x21c
  char        submesh_bone_name[260];         // +0x220
  cbs_vec3    submesh_origin;                 // +0x324
  cbs_vec3    field_330;                      // +0x330
  int         field_33c;                      // +0x33c
  char        left_handed;                    // +0x340
  char        pad_341[3];
  cbs_vec3    local_joint_r;                  // +0x344
  cbs_vec3    parent_local_joint_r;           // +0x350
  float       field_35c;                      // +0x35c
  float       field_360;                      // +0x360
  float       field_364;                      // +0x364
  float       field_368;                      // +0x368
  float       field_36c;                      // +0x36c
  char        field_370;                      // +0x370
  char        field_371;                      // +0x371
  char        pad_372[2];
  cbs_vec3    field_374;                      // +0x374
  int         block_380[41];                  // +0x380 (0xa4)
  int         field_424;                      // +0x424
  int         field_428;                      // +0x428
  char        field_42c;                      // +0x42c
  char        pad_42d[3];
  int         field_430;                      // +0x430
  cbs_vec3    field_434;                      // +0x434
  int         field_440;                      // +0x440
  int         field_444;                      // +0x444
  float       field_448;                      // +0x448
  float       field_44c;                      // +0x44c
  float       field_450;                      // +0x450
  float       field_454;                      // +0x454
  float       field_458;                      // +0x458
  float       field_45c;                      // +0x45c
  float       field_460;                      // +0x460
  char        field_464;                      // +0x464
  void Clear();
  creature_body_static_view& operator=(const creature_body_static_view& src);
};
#pragma pack(pop)

// @ 0x009B3180
void creature_body_static_view::Clear() {
  const float one = DAT_01485720;
  name[0] = '\0';
  group_id = 0;
  instance_id = 0;
  rest_center.x = 0.0f;
  rest_center.y = 0.0f;
  rest_center.z = 0.0f;
  rest_parent_rel_orientation_q.y = 0.0f;
  rest_parent_rel_orientation_q.z = 0.0f;
  rest_parent_rel_orientation_q.w = one;
  rest_parent_rel_orientation_q.x = 0.0f;
  rest_orientation_q.x = 0.0f;
  rest_orientation_q.y = *(volatile const float*)&rest_parent_rel_orientation_q.y;
  rest_orientation_q.z = *(volatile const float*)&rest_parent_rel_orientation_q.z;
  rest_orientation_q.w = *(volatile const float*)&rest_parent_rel_orientation_q.w;
  local_half_extents.x = 0.0f;
  local_half_extents.y = 0.0f;
  local_half_extents.z = 0.0f;
  local_original_r.x = 0.0f;
  local_original_r.y = 0.0f;
  local_original_r.z = 0.0f;
  cbs_caps empty_caps;
  memset(empty_caps.data, 0, sizeof(empty_caps));
  num_all_children = num_children = 0;
  parent = 0;
  bone_idx = 0;
  first_child = 0;
  submesh_bone_name[0] = '\0';
  bidx = parent_bidx = symmetric_bidx = first_child_bidx = -1;
  field_21c = -1;
  caps_block = empty_caps;
  submesh_origin.x = 0.0f;
  submesh_origin.y = 0.0f;
  submesh_origin.z = 0.0f;
  field_330.x = 0.0f;
  field_330.y = 0.0f;
  field_330.z = 0.0f;
  field_33c = -1;
  left_handed = '\0';
  local_joint_r.x = 0.0f;
  local_joint_r.y = 0.0f;
  local_joint_r.z = 0.0f;
  parent_local_joint_r.x = 0.0f;
  parent_local_joint_r.y = 0.0f;
  parent_local_joint_r.z = 0.0f;
  field_35c = 0.0f;
  field_360 = 0.0f;
  field_364 = 0.0f;
  field_368 = 0.0f;
  field_36c = 0.0f;
  field_370 = '\0';
  field_371 = '\0';
  field_374.x = 0.0f;
  field_374.y = 0.0f;
  field_374.z = 0.0f;
  block_380[0] = 0;
  field_428 = -1;
  field_42c = '\0';
  field_424 = -1;
  field_430 = -1;
  field_434.x = 0.0f;
  field_434.y = 0.0f;
  field_434.z = 0.0f;
  field_440 = field_444 = -1;
  field_448 = 0.0f;
  field_44c = 0.0f;
  field_450 = 0.0f;
  field_454 = 0.0f;
  field_458 = 0.0f;
  field_45c = 0.0f;
  field_460 = 0.0f;
}

// @ 0x009B3490
creature_body_static_view& creature_body_static_view::operator=(
    const creature_body_static_view& src) {
  for (int i = 0; i < 260; i++)
    name[i] = src.name[i];
  instance_id = src.instance_id;
  group_id = src.group_id;
  rest_center.x = src.rest_center.x;
  rest_center.y = src.rest_center.y;
  rest_center.z = src.rest_center.z;
  rest_orientation_q.x = src.rest_orientation_q.x;
  rest_orientation_q.y = src.rest_orientation_q.y;
  rest_orientation_q.z = src.rest_orientation_q.z;
  rest_orientation_q.w = src.rest_orientation_q.w;
  rest_parent_rel_orientation_q.x = src.rest_parent_rel_orientation_q.x;
  rest_parent_rel_orientation_q.y = src.rest_parent_rel_orientation_q.y;
  rest_parent_rel_orientation_q.z = src.rest_parent_rel_orientation_q.z;
  rest_parent_rel_orientation_q.w = src.rest_parent_rel_orientation_q.w;
  local_half_extents.x = src.local_half_extents.x;
  local_half_extents.y = src.local_half_extents.y;
  local_half_extents.z = src.local_half_extents.z;
  local_original_r.x = src.local_original_r.x;
  local_original_r.y = src.local_original_r.y;
  local_original_r.z = src.local_original_r.z;
  memcpy(caps_block.data, src.caps_block.data, sizeof(caps_block));
  bidx = src.bidx;
  parent_bidx = src.parent_bidx;
  symmetric_bidx = src.symmetric_bidx;
  first_child_bidx = src.first_child_bidx;
  num_children = src.num_children;
  num_all_children = src.num_all_children;
  parent = src.parent;
  first_child = src.first_child;
  bone_idx = src.bone_idx;
  field_21c = src.field_21c;
  for (int i = 0; i < 260; i++)
    submesh_bone_name[i] = src.submesh_bone_name[i];
  submesh_origin.x = src.submesh_origin.x;
  submesh_origin.y = src.submesh_origin.y;
  submesh_origin.z = src.submesh_origin.z;
  field_330.x = src.field_330.x;
  field_330.y = src.field_330.y;
  field_330.z = src.field_330.z;
  field_33c = src.field_33c;
  left_handed = src.left_handed;
  local_joint_r.x = src.local_joint_r.x;
  local_joint_r.y = src.local_joint_r.y;
  local_joint_r.z = src.local_joint_r.z;
  parent_local_joint_r.x = src.parent_local_joint_r.x;
  parent_local_joint_r.y = src.parent_local_joint_r.y;
  parent_local_joint_r.z = src.parent_local_joint_r.z;
  field_35c = src.field_35c;
  field_360 = src.field_360;
  field_364 = src.field_364;
  field_368 = src.field_368;
  field_36c = src.field_36c;
  field_370 = src.field_370;
  field_371 = src.field_371;
  field_374.x = src.field_374.x;
  field_374.y = src.field_374.y;
  field_374.z = src.field_374.z;
  memcpy(block_380, src.block_380, sizeof(block_380));
  field_424 = src.field_424;
  field_428 = src.field_428;
  field_42c = src.field_42c;
  field_430 = src.field_430;
  field_434.x = src.field_434.x;
  field_434.y = src.field_434.y;
  field_434.z = src.field_434.z;
  field_440 = src.field_440;
  field_444 = src.field_444;
  field_448 = src.field_448;
  field_44c = src.field_44c;
  field_450 = src.field_450;
  field_454 = src.field_454;
  field_458 = src.field_458;
  field_45c = src.field_45c;
  field_460 = src.field_460;
  field_464 = src.field_464;
  return *this;
}

// @ 0x009B3970
float FUN_009b3970(__m128 v)
{
  float t = _mm_cvtss_f32(v) / DAT_01550d50;
  float L;
  if (t > DAT_01485720)
    L = DAT_01485720;
  else if (t > 0.0f)
    L = t;
  else
    L = 0.0f;
  if (!(DAT_0166c274 & 1)) {
    DAT_0166c270 = DAT_0144725c;
    DAT_0166c274 |= 1;
  }
  return (1.0 - pow(1.0f - L, DAT_01550d4c)) * DAT_0166c270;
}

// @ 0x009B39E0
__m128 FUN_009b39e0(float x)
{
  if (!(DAT_0166c280 & 1)) {
    DAT_0166c27c = DAT_014471f8;
    DAT_0166c280 |= 1;
  }
  float t = _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(fabsf(x)), _mm_set_ss(DAT_0166c27c)));
  float L;
  if (t > DAT_01485720)
    L = DAT_01485720;
  else if (t > 0.0f)
    L = t;
  else
    L = 0.0f;
  if (!(DAT_0166c280 & 2)) {
    DAT_0166c278 = DAT_01447260;
    DAT_0166c280 |= 2;
  }
  volatile float Lv = L;   // the retail reloads the clamp result with an x87 fld
  float r = (float)((1.0 - pow(1.0f - Lv, DAT_01550d54)) * DAT_0166c278);
  __m128 out = _mm_set_ss(r);
  if (x > DAT_01485378)
    out = _mm_xor_ps(out, DAT_013eb8b0);
  // The retail body leaves the static-init flag word in eax (it is the last value written to
  // eax before the pow call and the pow helper preserves it); C cannot express that state.
  __asm { mov eax, dword ptr [DAT_0166c280] }
  return out;
}

// @ 0x009B3C10
float FUN_009b3c10(float b, float c)
{
  float w = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(c), _mm_set_ss(DAT_01471064)));
  if (b > w) {
    int n = _mm_cvtt_ss2si(_mm_div_ss(_mm_add_ss(_mm_set_ss(w), _mm_set_ss(b)), _mm_set_ss(c)));
    return b - (float)n * c;
  }
  if (b > -w)
    return b;
  int n = _mm_cvtt_ss2si(_mm_div_ss(_mm_sub_ss(_mm_set_ss(b), _mm_set_ss(w)), _mm_set_ss(c)));
  return b - (float)n * c;
}

