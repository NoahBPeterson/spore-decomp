// src/game/SPCreatureAnim/creature.cpp -- migrated from slice(s) s009c56c0, s009c2ef0, s009c0f60, s009bf210, s009be260, s009bb360, s009b95d0, s009b8720, s009b4e00, s009b3e40, s009c4a30, s009c32c0, s009c1f60, s009bfc20, s009bd340, s009bc580, s009bb910, s009ba4c0, s009b77a0, s009b6b10, s009b5ce0, s009b3180 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/creature.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <float.h>
#include "nSPCreatureAnim/creature_instance_data.h"
#include <math.h>
#include "nSPCreatureAnim/creature_static_data.h"
#include "nSPCreatureAnim/creature_body_instance_data.h"
#include "nSPCreatureAnim/creature_body_static_data.h"
#include "checkerlib/vector_3.h"
#include "checkerlib/vector_4.h"
#include "nSPCreatureAnim/dynamics_walking.h"
#include <string.h>
#include <intrin.h>
#include <stddef.h>
#include "checkerlib/matrix_3x3.h"
#include <xmmintrin.h>

// ---- items of slice s009b3180 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace nSPCreatureAnim {
struct TargetFrame {
  char pad_000[0x1644];
  float posA[3];  // +0x1644
  float posB[4];  // +0x1650
  void Set(const float* a, const float* b);
};
}
namespace nSPCreatureAnim {
struct Transform30 {
  int a;         // +0x00
  int b;         // +0x04
  float f[10];   // +0x08
  Transform30& operator=(const Transform30& src);
};
}
namespace nSPCreatureAnim {
struct CopyBlock {
  int a[4];       // +0x00
  float f[10];    // +0x10
  char c;         // +0x38
  CopyBlock& operator=(const CopyBlock& src);
};
}
// ---- items of slice s009b3180 end

// ---- items of slice s009b5ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace RC {
struct BoxShape {
  char pad[0x138];
  float mHalfExtent[3];   // +0x138
};
}
namespace RC {
struct Part {
  BoxShape* mpShape;      // +0x00
  char pad04[0xc];
  float mCenter[3];       // +0x10
  float mQuat[4];         // +0x1c: x y z w
  char pad2c[700 - 0x2c];
};
}
namespace RC {
struct Owner {
  char pad00[0x18];
  float mPos[3];          // +0x18
  char pad24[0x3c - 0x24];
  float mQuat[4];         // +0x3c: x y z w
  char pad4c[0x70 - 0x4c];
  float mScale;           // +0x70
  char pad74[0x2e4 - 0x74];
  Part* mpPartsBegin;     // +0x2e4
  Part* mpPartsEnd;       // +0x2e8
};
}
bool BoxRayTest(const float* org, const float* dir, const float* center, const float* rot3x3,
                float ex, float ey, float ez, float* tOut, float* normalOut);  // 0x00a02530
float* QuaternionVectorTransform(float* out, const float* quat, const float* v);  // 0x0099c1a0
namespace CA {
typedef unsigned int  u32;
}
namespace CA {
typedef unsigned char u8;
}
namespace CA {
struct Vec3 { float x, y, z; };
}
namespace CA {
struct PartCaps {
  u32 NameFOURCCs[32];          // +0x00
  u8  Values[32];               // +0x80
};
}
namespace CA {
struct BoneMesh {
  void* mpShape;                // +0x00
  char  pad04[0x0c];
  Vec3  mCenter;                // +0x10
  float mQuat[4];               // +0x1c
  char  pad2c[0x2bc - 0x2c];
};
}
namespace CA {
struct CreaturePart {
  char  pad000[0x10c];
  Vec3  mA;                     // +0x10c local offset
  Vec3  mB;                     // +0x118 local offset
  char  pad124[0x150 - 0x124];
  u32   m150;                   // +0x150 capability flags of this part
  u32   m154;                   // +0x154 capability flags inherited from children
  PartCaps mCaps;               // +0x158
  void* m1f8;                   // +0x1f8 own spine constraint
  u32   m1fc;                   // +0x1fc next part index (0 == root)
  u32   m200;                   // +0x200
  u32   m204;                   // +0x204 first child index
  u32   m208;                   // +0x208 child count
  u32   m20c;                   // +0x20c
  u32   m210;                   // +0x210 traversal state
  CreaturePart* m214;           // +0x214 next part in the state chain
  CreaturePart* m218;           // +0x218 child array (stride 0x468)
  char  pad21c[0x464 - 0x21c];
  u8    m464;                   // +0x464
};
}
namespace CA {
struct PartRef {
  CreaturePart* mPart;          // +0x00
  u32           mExtra;         // +0x04
};
}
namespace CA {
class WorkspaceSource {
public:
  u8    mUseOrigin;             // +0x00
  char  pad01[3];
  void* mCallback;              // +0x04
  void* mContext;               // +0x08
  Vec3* rotateInto(Vec3* out, const Vec3* v, int zero);   // 0x009a49d0
};
}
namespace CA {
struct BoneRecord {
  char pad00[0x58];
  u32  mIndex;                  // +0x58
  char pad5c[0x108 - 0x5c];
  void finish();                // 0x009cf3c0
};
}
namespace CA {
struct BonePool {
  u32          addPart(void* owner, const Vec3* local, const Vec3* world);  // 0x009d7d10
  BoneRecord** storage();                                                   // 0x00a09f50
  char pad00[0x88];
};
}
namespace CA {
extern float kWorkspaceDirEps;   // 0x014471fc  1e-6f
}
namespace CA {
extern float kWorkspaceMinSq;    // 0x013eb960  0.01f
}
namespace CA {
extern float kWorkspaceOne;      // 0x01485720  1.0f
}
namespace CA {
extern int gExtraBoneCount;      // 0x01550d58
}
namespace CA {
u32  FUN_009b3460(CreaturePart* part);                       // 0x009b3460
}
namespace CA {
struct Creature {
  char  pad00[0x04];
  void* m04;                    // +0x04
  char  pad08[0x18 - 0x08];
  Vec3  m18;                    // +0x18
  char  pad24[0x70 - 0x24];
  float m70;                    // +0x70
  char  pad74[0x2e4 - 0x74];
  BoneMesh* mpBonesBegin;       // +0x2e4
  BoneMesh* mpBonesEnd;         // +0x2e8
  char  pad2ec[0x384 - 0x2ec];
  CreaturePart* mpPartsBegin;   // +0x384
  CreaturePart* mpPartsEnd;     // +0x388
  char  pad38c[0x3ac - 0x38c];
  u32   m3ac;                   // +0x3ac
  u32   m3b0;                   // +0x3b0
  char  pad3b4[0x3cc - 0x3b4];
  PartRef* mpRefsBegin;         // +0x3cc
  PartRef* mpRefsEnd;           // +0x3d0
  char  pad3d4[0x15b8 - 0x3d4];
  BonePool mPool;               // +0x15b8
  u32   m1640;                  // +0x1640
  char  pad1644[0x1688 - 0x1644];
  WorkspaceSource* mpSource;    // +0x1688

  Vec3* get_workspace_origin(Vec3* out, u32 unused);        // 0x009b61f0
  float set_workspace_dir(const Vec3* dir, Vec3* out);      // 0x009b6220
  Vec3* workspace_origin_for(Vec3* out, const Vec3* v);     // 0x009b62c0
  void  update_part_states();                               // 0x009b6360
};
}
namespace CA {
void FUN_009b5ce0(Creature* c);                             // 0x009b5ce0
}
namespace CA {
void FUN_009b5f90(u32 index, Creature* c);                  // 0x009b5f90
}
// ---- items of slice s009b5ce0 end

// ---- items of slice s009b6b10 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 8)
#pragma pack(pop)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
};
struct Quaternion {
    float x, y, z, w;

    // v' = v + 2 * (rotation-matrix-minus-identity * v)
    Vector3 Rotate(const Vector3& v) const
    {
        float xw = x * w;
        float yw = y * w;
        float zw = z * w;
        float xx = -(x * x);
        float yx = y * x;
        float yy = -(y * y);
        float zx = z * x;
        float zy = z * y;
        float zz = -(z * z);
        return Vector3(((zz + yy) * v.x + (yx - zw) * v.y + (zx + yw) * v.z) * 2.0f + v.x,
                       ((zz + xx) * v.y + (yx + zw) * v.x + (zy - xw) * v.z) * 2.0f + v.y,
                       ((zx - yw) * v.x + (yy + xx) * v.z + (zy + xw) * v.y) * 2.0f + v.z);
    }
};
inline Vector3 Min(const Vector3& a, const Vector3& b)
{
    return Vector3(a.x > b.x ? b.x : a.x, a.y > b.y ? b.y : a.y, a.z > b.z ? b.z : a.z);
}
inline Vector3 Max(const Vector3& a, const Vector3& b)
{
    return Vector3(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z);
}
inline void ExpandBounds(Vector3& vMin, Vector3& vMax, const Vector3& pt)
{
    vMin = Min(pt, vMin);
    vMax = Max(vMax, pt);
}
struct cOrientedPart {                  // 0x468 bytes
    uint32_t pad000[0x10c / 4];
    Vector3 mPosition;                  // +0x10c
    Quaternion mOrientation;            // +0x118
    uint32_t pad128[(0x138 - 0x128) / 4];
    Vector3 mHalfExtents;               // +0x138
    uint32_t pad144[(0x468 - 0x144) / 4];
};
template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    const T& operator[](uint32_t i) const { return mpBegin[i]; }
};
struct cPartOwner {
    uint32_t pad000[0x384 / 4];
    vector<cOrientedPart> mParts;       // +0x384
};
static const float kMaxFloat = 3.402823466e+38F;
// ---- items of slice s009b6b10 end

// ---- items of slice s009b77a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int DAT_01550b1c;      // 0x01550b1c  (float)
extern "C" double sqrt(double);
extern "C" void* FUN_0099c310(void* out, void* a, void* b);      // 0x0099c310
extern "C" void  FUN_009b4ba0(void* out, void* q, void* v);      // 0x009b4ba0
extern "C" void* FUN_009a49d0(void* out, void* v, int f);        // 0x009a49d0
extern "C" void  Sprintf8(void* buf, const char* fmt);           // 0x00938470
int* __fastcall GetPoliticalID(int this_);                       // 0x0097e850
int* __fastcall FUN_00a09f50(int this_);                         // 0x00a09f50
int* __fastcall FUN_00ff3ba0(int this_);                         // 0x00ff3ba0
int  __fastcall FUN_009ce410(int this_);                         // 0x009ce410
char __fastcall FUN_009b78c0(int this_, int dummy, int param_2, int param_3, int param_4);
char __fastcall FUN_009b3850(int a, int dummy, void* b, void* c, int d);   // ComposeGaitFileName
int  __fastcall FUN_009e5b40(int a, int dummy, void* b, int c, int d);
int  __fastcall FUN_009e18c0(int a, int dummy, void* b, int c, int d);     // LoadGaitFile
int  __fastcall FUN_009dbe10(int a, int dummy, int b, int c, int d);
int  __fastcall FUN_009e4350(int a, int dummy, int b, int c);
int  __fastcall FUN_009e3790(int a, int dummy, void* b);
int  __fastcall FUN_009e4450(int a, int dummy, float f, int b, int c, int d);
int  __fastcall FUN_009d24c0(int a, int dummy, int b, int c, int d, int e, int f);
float __fastcall FUN_009dc7a0(int a, int dummy, void* b);
int  __fastcall FUN_009d0c80(int a);
int  __fastcall FUN_009dfc40(int a);
int  __fastcall FUN_009d1050(int a);
// ---- items of slice s009b77a0 end

// ---- items of slice s009ba4c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace checkerlib {
class vector_3_s009b_a4c0 { public:
    float x, y, z;
    vector_3_s009b_a4c0& operator=(const vector_3_s009b_a4c0& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
}
namespace checkerlib {
class vector_4_s009b_a4c0 { public: float x, y, z, w; };
}
namespace checkerlib {
vector_3_s009b_a4c0* QuaternionVectorTransform(vector_3_s009b_a4c0* out, const vector_4_s009b_a4c0* q, const vector_3_s009b_a4c0* v);  // 0x0099c1a0
}
namespace checkerlib {
__forceinline vector_4_s009b_a4c0 QuaternionProduct_s009b_a4c0(const vector_4_s009b_a4c0& a, const vector_4_s009b_a4c0& b)
{
    vector_4_s009b_a4c0 r;
    r.x = ((a.w * b.x + b.w * a.x) - a.z * b.y) + a.y * b.z;
    r.y = ((a.w * b.y + a.z * b.x) + a.y * b.w) - b.z * a.x;
    r.z = ((a.z * b.w - a.y * b.x) + a.w * b.z) + b.y * a.x;
    r.w = ((a.w * b.w - b.x * a.x) - a.y * b.y) - a.z * b.z;
    return r;
}
}
namespace checkerlib {
__forceinline vector_3_s009b_a4c0 QuaternionVectorTransformInverse_s009b_a4c0(const vector_4_s009b_a4c0& q, const vector_3_s009b_a4c0& v)
{
    float nxw = -(q.x * q.w);
    float nzw = -(q.z * q.w);
    float nxx = -(q.x * q.x);
    float nyw = -(q.y * q.w);
    float zx = q.z * q.x;
    float yx = q.y * q.x;
    float nyy = -(q.y * q.y);
    float zy = q.z * q.y;
    float nzz = -(q.z * q.z);
    vector_3_s009b_a4c0 r;
    r.x = (((yx - nzw) * v.y + (zx + nyw) * v.z) + (nzz + nyy) * v.x) * 2.0f + v.x;
    r.y = (((nzz + nxx) * v.y + (zy - nxw) * v.z) + (yx + nzw) * v.x) * 2.0f + v.y;
    r.z = (((nyy + nxx) * v.z + (zy + nxw) * v.y) + (zx - nyw) * v.x) * 2.0f + v.z;
    return r;
}
}
namespace nSPCreatureAnim {
struct goal_pos_rot_s009b_a4c0 {                    // size 0x24
    checkerlib::vector_3_s009b_a4c0 pos;          // +0x00
    float    pos_weight;   // +0x0c
    checkerlib::vector_4_s009b_a4c0 rot;          // +0x10
    float    rot_weight;   // +0x20
};
}
namespace nSPCreatureAnim {
struct creature_body_static_data_s009b_a4c0 {
    uint32_t pad_000[0x10c / 4];
    checkerlib::vector_3_s009b_a4c0 rest_center__SCALABLE;      // +0x10c
    checkerlib::vector_4_s009b_a4c0 rest_orientation_q;         // +0x118
    uint32_t pad_128[(0x150 - 0x128) / 4];
    uint32_t flags_150;                  // +0x150 (alternate flag word)
    uint32_t flags_154;                  // +0x154
    uint32_t pad_158[(0x1f8 - 0x158) / 4];
    unsigned long bidx;                  // +0x1f8 (body index in the creature)
    int      parent_bidx;                // +0x1fc (parent body index, -1: root)
};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009b_a4c0;
}
namespace nSPCreatureAnim {
struct creature_body_instance_data_s009b_a4c0 {     // size 0x2bc
    creature_body_static_data_s009b_a4c0* static_data;  // +0x000
    creature_instance_data_s009b_a4c0*    creature;     // +0x004
    uint32_t pad_008[2];
    checkerlib::vector_3_s009b_a4c0 pos;                            // +0x010
    checkerlib::vector_4_s009b_a4c0 orientation;                    // +0x01c
    uint32_t pad_02c[(0x48 - 0x2c) / 4];
    float    goal_time;                      // +0x048
    uint32_t pad_04c;
    float    goal_blend;                     // +0x050
    uint32_t pad_054;
    goal_pos_rot_s009b_a4c0 goal;                       // +0x058
    uint32_t pad_07c[(0x2bc - 0x7c) / 4];
};
}
namespace nSPCreatureAnim {
struct body_vector {                     // eastl::vector<creature_body_instance_data>
    creature_body_instance_data_s009b_a4c0* mpBegin;
    creature_body_instance_data_s009b_a4c0* mpEnd;
    creature_body_instance_data_s009b_a4c0* mpCapacity;
    uint32_t mAllocator;
    unsigned long size() const { return (unsigned long)(mpEnd - mpBegin); }
};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009b_a4c0 {
    uint32_t pad_000[0x18 / 4];
    checkerlib::vector_3_s009b_a4c0 position;                   // +0x018
    uint32_t pad_024[(0x3c - 0x24) / 4];
    checkerlib::vector_4_s009b_a4c0 orientation;                // +0x03c
    uint32_t pad_04c[(0x70 - 0x4c) / 4];
    float    requested_scale;            // +0x070
    uint32_t pad_074[(0x1b8 - 0x74) / 4];
    uint8_t  body_goal_bits[1];          // +0x1b8 (two bits per body)
    uint8_t  pad_1b9[0x2e4 - 0x1b9];
    body_vector Bodies;                  // +0x2e4

    void UpdateGoalSpring(struct goal_state* st, int nSteps, float dt, float t, float rate);
};
}
namespace nSPCreatureAnim {
struct goal_def {
    unsigned long bidx;                  // +0x00
    int      parent_bidx;                // +0x04 (-1: root goal)
    uint32_t pad_08[2];
    float    max_dist;                   // +0x10 (in units of the creature scale)
    uint32_t pad_14[2];
    checkerlib::vector_3_s009b_a4c0 offset;                     // +0x1c (in the parent body's frame)
    checkerlib::vector_4_s009b_a4c0 rot;                        // +0x28 (relative to the parent body)
};
}
namespace nSPCreatureAnim {
struct goal_state {
    goal_def* def;                       // +0x00
    bool      initialized;               // +0x04
    bool      reset;                     // +0x05
    uint8_t   pad_06[2];
    checkerlib::vector_3_s009b_a4c0  vel;                       // +0x08
    checkerlib::vector_3_s009b_a4c0  pos;                       // +0x14
    checkerlib::vector_3_s009b_a4c0  prev;                      // +0x20
};
}
namespace nSPCreatureAnim {
bool GoalStateIsActive(creature_instance_data_s009b_a4c0* c, goal_state* st, float t);  // 0x009ba8d0 (cdecl)
}
namespace nSPCreatureAnim {
void GoalStateInit(creature_instance_data_s009b_a4c0* c, goal_state* st, char flag);      // 0x009ba7d0 (cdecl)
}
namespace nSPCreatureAnim {
extern float g_GoalSpringMaxDist;        // 0x01550ab8 (1.0)
}
namespace nSPCreatureAnim {
extern float g_GoalSpringK;              // 0x01550abc (100.0)
}
namespace nSPCreatureAnim {
extern float g_GoalSpringDamp;           // 0x01550ac0 (8.0)
}
namespace nSPCreatureAnim {
extern float g_GoalGravity;              // 0x0166c010
}
namespace nSPCreatureAnim {
extern int   g_GoalClampAboveGround;     // 0x0166c014
}
namespace nSPCreatureAnim {
extern const float kGoalMaxDistScale;    // 0x013ec434 (0.4)
}
namespace nSPCreatureAnim {
extern const float kOne;                 // 0x01485720
}
namespace nSPCreatureAnim {
extern const float kZero;                // 0x01485378
}
namespace nSPCreatureAnim {
extern const float kMinSpeed2;           // 0x013ebca0 (1e-4)
}
namespace nSPCreatureAnim {
extern char  g_GoalUseAltFlags;          // 0x01550c2c (use flags_150 instead of flags_154)
}
namespace nSPCreatureAnim {
static __forceinline void MarkBodyGoal(creature_body_instance_data_s009b_a4c0* body)
{
    unsigned long bit = body->static_data->bidx * 2;
    body->creature->body_goal_bits[bit >> 3] |= (uint8_t)(1 << (bit & 7));
}
}
namespace nSPCreatureAnim {
struct anim_body_data {                    // stride 0x468
    uint32_t pad_000[0x10c / 4];
    checkerlib::vector_3_s009b_a4c0 rest_center__SCALABLE;        // +0x10c
    checkerlib::vector_4_s009b_a4c0 rest_orientation_q;           // +0x118
    uint32_t pad_128[(0x468 - 0x128) / 4];
};
}
namespace nSPCreatureAnim {
struct creature_anim {                     // nSPCreatureAnim data
    uint32_t        pad_000[0x384 / 4];
    anim_body_data* anim_bodies_begin;     // +0x384
    anim_body_data* anim_bodies_end;       // +0x388
};
}
namespace nSPCreatureAnim {
struct wiggle_data {                       // size 0x39 (padded to 0x3c)
    int      body_a;                       // +0x00
    int      body_b;                       // +0x04
    int      body_c;                       // +0x08
    int      body_d;                       // +0x0c
    float    weight;                       // +0x10
    float    length;                       // +0x14
    float    angle;                        // +0x18
    checkerlib::vector_3_s009b_a4c0 pos;                          // +0x1c
    checkerlib::vector_4_s009b_a4c0 rot;                          // +0x28
    uint8_t  flag_038;                     // +0x38
    void CopyFrom(const wiggle_data* w);   // 0x009b3ab0 (0x39-byte copy)
};
}
namespace nSPCreatureAnim {
bool CalcWiggle(creature_anim* anim, anim_body_data* body, wiggle_data* w,
                int a4, int a5, int a6, int a7, int a8, int a9);   // 0x009ba180
}
// ---- items of slice s009ba4c0 end

// ---- items of slice s009bb910 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace checkerlib {
struct vector_3_s009b_b910 {
    float x, y, z;
    vector_3_s009b_b910& operator=(const vector_3_s009b_b910& o) { x = o.x; y = o.y; z = o.z; return *this; }
    vector_3_s009b_b910& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    vector_3_s009b_b910& operator+=(const vector_3_s009b_b910& o) { x += o.x; y += o.y; z += o.z; return *this; }
};
}
namespace checkerlib {
struct vector_4_s009b_b910 {
    float x, y, z, w;
    vector_4_s009b_b910& operator=(const vector_4_s009b_b910& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
    vector_4_s009b_b910& operator+=(const vector_4_s009b_b910& o) { x += o.x; y += o.y; z += o.z; w += o.w; return *this; }
    vector_4_s009b_b910& operator-=(const vector_4_s009b_b910& o) { x -= o.x; y -= o.y; z -= o.z; w -= o.w; return *this; }
};
}
namespace checkerlib {
vector_4_s009b_b910 Normalize(const vector_4_s009b_b910& q, float* pLength);    // 0x0099cae0 (out of line here)
}
namespace checkerlib {
inline vector_3_s009b_b910 make_v3(float x, float y, float z)
{
    vector_3_s009b_b910 r;
    r.x = x; r.y = y; r.z = z;
    return r;
}
}
namespace checkerlib {
inline vector_3_s009b_b910 operator-(const vector_3_s009b_b910& a, const vector_3_s009b_b910& b) { return make_v3(a.x - b.x, a.y - b.y, a.z - b.z); }
}
namespace checkerlib {
inline vector_3_s009b_b910 operator*(const vector_3_s009b_b910& a, float s) { return make_v3(a.x * s, a.y * s, a.z * s); }
}
namespace checkerlib {
inline vector_3_s009b_b910 operator*(float s, const vector_3_s009b_b910& a) { return make_v3(s * a.x, s * a.y, s * a.z); }
}
namespace checkerlib {
inline vector_4_s009b_b910 make_v4(float x, float y, float z, float w)
{
    vector_4_s009b_b910 r;
    r.x = x; r.y = y; r.z = z; r.w = w;
    return r;
}
}
namespace checkerlib {
inline vector_4_s009b_b910 operator*(const vector_4_s009b_b910& a, float s) { return make_v4(a.x * s, a.y * s, a.z * s, a.w * s); }
}
namespace checkerlib {
inline vector_4_s009b_b910 operator+(const vector_4_s009b_b910& a, const vector_4_s009b_b910& b) { return make_v4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
}
namespace checkerlib {
inline vector_4_s009b_b910 operator-(const vector_4_s009b_b910& a, const vector_4_s009b_b910& b) { return make_v4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
}
namespace checkerlib {
inline float DotProduct(const vector_4_s009b_b910& a, const vector_4_s009b_b910& b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
}
namespace checkerlib {
inline vector_4_s009b_b910 QuaternionProductConjugate(const vector_4_s009b_b910& a, const vector_4_s009b_b910& b)
{
    vector_4_s009b_b910 r;
    r.x = ((a.x * b.w - b.x * a.w) + a.z * b.y) - a.y * b.z;
    r.y = ((a.y * b.w - a.z * b.x) - b.y * a.w) + b.z * a.x;
    r.z = ((a.y * b.x + a.z * b.w) - b.y * a.x) - b.z * a.w;
    r.w = ((b.z * a.z + a.y * b.y) + b.x * a.x) + a.w * b.w;
    return r;
}
}
namespace checkerlib {
inline vector_4_s009b_b910 QuaternionProduct_s009b_b910(const vector_4_s009b_b910& a, const vector_4_s009b_b910& b)
{
    vector_4_s009b_b910 r;
    r.x = ((a.w * b.x + b.w * a.x) - a.z * b.y) + a.y * b.z;
    r.y = ((a.w * b.y + a.z * b.x) + a.y * b.w) - b.z * a.x;
    r.z = ((a.z * b.w - a.y * b.x) + a.w * b.z) + b.y * a.x;
    r.w = ((a.w * b.w - b.x * a.x) - a.y * b.y) - a.z * b.z;
    return r;
}
}
namespace nSPCreatureAnim {
struct goal_pos_rot_s009b_b910 {                    // size 0x24
    checkerlib::vector_3_s009b_b910 pos;          // +0x00
    float    pos_weight;   // +0x0c
    checkerlib::vector_4_s009b_b910 rot;          // +0x10
    float    rot_weight;   // +0x20

    // Divides an over-weighted accumulated position by its weight.
    __forceinline void NormalizePos()
    {
        float w = pos_weight;
        if (w > 0.0f && w > 1.0f)
        {
            pos = (1.0f / w) * pos;
        }
    }

    // Renormalises the accumulated rotation; a weight below 1 is filled up with the identity.
    __forceinline void NormalizeWeightedRot()
    {
        float w = rot.w, z = rot.z, y = rot.y, x = rot.x;
        float len = (float)sqrt((double)x * x + (double)y * y + (double)z * z + (double)w * w);
        if (len != 0.0f)
        {
            float inv = 1.0f / len;
            rot.x = x * inv;
            rot.y = y * inv;
            rot.z = z * inv;
            rot.w = w * inv;
        }
        if (1.0f > rot_weight)
        {
            float t = 1.0f - rot_weight;
            checkerlib::vector_4_s009b_b910 a = rot * rot_weight;
            checkerlib::vector_4_s009b_b910 b = checkerlib::make_v4(0.0f, 0.0f, 0.0f, 1.0f) * t;
            if (0.0f > checkerlib::DotProduct(a, b))
                a = a - b;
            else
                a = a + b;
            rot = checkerlib::Normalize(a, 0);
        }
    }

    __forceinline void SetRotIdentity()
    {
        rot.x = 0.0f;
        rot.y = 0.0f;
        rot.z = 0.0f;
        rot.w = 1.0f;
    }

    __forceinline void NormalizeRot()
    {
        if (rot_weight > 0.0f)
            NormalizeWeightedRot();
        else
            SetRotIdentity();
    }
};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009b_b910 {
    uint32_t     pad_000[0x18 / 4];
    checkerlib::vector_3_s009b_b910     requested_pos;           // +0x018
    uint32_t     pad_024[(0x30 - 0x24) / 4];
    checkerlib::vector_3_s009b_b910     previous_requested_pos;  // +0x030
    checkerlib::vector_4_s009b_b910     requested_rot;           // +0x03c
    uint32_t     pad_04c[(0x5c - 0x4c) / 4];
    checkerlib::vector_4_s009b_b910     previous_requested_rot;  // +0x05c
    uint32_t     pad_06c[(0x118 - 0x6c) / 4];
    goal_pos_rot_s009b_b910 goal_0x118;              // +0x118
    goal_pos_rot_s009b_b910 goal_0x13c;              // +0x13c
    goal_pos_rot_s009b_b910 goal_0x160;              // +0x160
    goal_pos_rot_s009b_b910 walk_goal_delta;         // +0x184
};
}
// ---- items of slice s009bb910 end

// ---- items of slice s009bc580 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace checkerlib {
class vector_3_s009b_c580 { public:
    float x, y, z;
    vector_3_s009b_c580& operator=(const vector_3_s009b_c580& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
}
namespace checkerlib {
class vector_4_s009b_c580 { public:
    float x, y, z, w;
    vector_4_s009b_c580& operator=(const vector_4_s009b_c580& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
};
}
namespace checkerlib {
inline vector_3_s009b_c580 operator+(const vector_3_s009b_c580& a, const vector_3_s009b_c580& b) { vector_3_s009b_c580 r; r.x = a.x + b.x; r.y = a.y + b.y; r.z = a.z + b.z; return r; }
}
namespace checkerlib {
inline vector_3_s009b_c580 operator-(const vector_3_s009b_c580& a, const vector_3_s009b_c580& b) { vector_3_s009b_c580 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r; }
}
namespace checkerlib {
inline vector_3_s009b_c580 operator*(const vector_3_s009b_c580& a, float s) { vector_3_s009b_c580 r; r.x = a.x * s; r.y = a.y * s; r.z = a.z * s; return r; }
}
namespace checkerlib {
inline vector_4_s009b_c580 QuaternionProduct_s009b_c580(const vector_4_s009b_c580& a, const vector_4_s009b_c580& b)
{
    vector_4_s009b_c580 r;
    r.x = ((a.x * b.w + b.x * a.w) - a.z * b.y) + a.y * b.z;
    r.y = ((a.y * b.w + a.z * b.x) + b.y * a.w) - b.z * a.x;
    r.z = ((a.z * b.w - a.y * b.x) + b.z * a.w) + b.y * a.x;
    r.w = ((b.w * a.w - a.x * b.x) - a.y * b.y) - b.z * a.z;
    return r;
}
}
namespace checkerlib {
__forceinline vector_3_s009b_c580 QuaternionVectorTransform_s009b_c580(const vector_4_s009b_c580& q, const vector_3_s009b_c580& v)
{
    vector_3_s009b_c580 r;
    r.x = (((-(q.z * q.z) + -(q.y * q.y)) * v.x + (q.z * q.x + q.y * q.w) * v.z) + (q.y * q.x - q.z * q.w) * v.y) * 2.0f + v.x;
    r.y = (((q.y * q.x + q.z * q.w) * v.x + (q.z * q.y - q.x * q.w) * v.z) + (-(q.z * q.z) + -(q.x * q.x)) * v.y) * 2.0f + v.y;
    r.z = (((q.z * q.x - q.y * q.w) * v.x + (-(q.y * q.y) + -(q.x * q.x)) * v.z) + (q.z * q.y + q.x * q.w) * v.y) * 2.0f + v.z;
    return r;
}
}
namespace nSPCreatureAnim {
struct creature_body_static_data_s009b_c580 {
    uint32_t pad_000[0x10c / 4];
    checkerlib::vector_3_s009b_c580 center;                      // +0x10c
    checkerlib::vector_4_s009b_c580 orientation;                 // +0x118
    checkerlib::vector_4_s009b_c580 joint_rotation;              // +0x128 (rotation relative to the parent body)
    uint32_t pad_138[(0x344 - 0x138) / 4];
    checkerlib::vector_3_s009b_c580 local_r;                     // +0x344
    checkerlib::vector_3_s009b_c580 parent_r;                    // +0x350
};
}
namespace nSPCreatureAnim {
struct creature_body_instance_data_s009b_c580 {      // size 0x2bc (retail)
    creature_body_static_data_s009b_c580*   static_data;   // +0x000
    void*                        creature;      // +0x004
    creature_body_instance_data_s009b_c580* parent;        // +0x008
    uint32_t                     pad_00c;
    checkerlib::vector_3_s009b_c580                     center;        // +0x010
    checkerlib::vector_4_s009b_c580                     orientation;   // +0x01c
    checkerlib::vector_3_s009b_c580                     velocity;      // +0x02c
    bool                         blend_active;  // +0x038
    uint8_t                      pad_039[3];
    uint32_t                     pad_03c[(0x190 - 0x3c) / 4];
    checkerlib::vector_3_s009b_c580                     target_center; // +0x190
    checkerlib::vector_4_s009b_c580                     target_rotation; // +0x19c
    uint32_t                     pad_1ac[(0x280 - 0x1ac) / 4];
    checkerlib::vector_3_s009b_c580                     blend_pos;     // +0x280
    checkerlib::vector_4_s009b_c580                     blend_rot;     // +0x28c
    uint32_t                     pad_29c[(0x2bc - 0x29c) / 4];
};
}
namespace nSPCreatureAnim {
class cGameData {
public:
    uint32_t mData[0x8c / 4];
    int  GetPoliticalID();                // 0x0097e850
    void F_9d33a0(int* p);                // 0x009d33a0
};
}
namespace nSPCreatureAnim {
class anim_state_x {
public:
    void F_9e3f70(int a, int b);          // 0x009e3f70
};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009b_c580 {
    uint32_t pad_000[0x18 / 4];
    checkerlib::vector_3_s009b_c580 center;                      // +0x018
    checkerlib::vector_3_s009b_c580 prev_center;                 // +0x024
    uint32_t pad_030[(0x3c - 0x30) / 4];
    checkerlib::vector_4_s009b_c580 orientation;                 // +0x03c
    checkerlib::vector_4_s009b_c580 orientation_b;               // +0x04c
    uint32_t pad_05c[(0x6c - 0x5c) / 4];
    float    field_06c;                   // +0x06c
    float    requested_scale;             // +0x070
    checkerlib::vector_3_s009b_c580 velocity;                    // +0x074
    checkerlib::vector_3_s009b_c580 prev_velocity;               // +0x080
    checkerlib::vector_3_s009b_c580 smooth_velocity;             // +0x08c
    checkerlib::vector_3_s009b_c580 smooth_velocity_prev;        // +0x098
    checkerlib::vector_3_s009b_c580 rot_velocity;                // +0x0a4
    checkerlib::vector_3_s009b_c580 velocity2;                   // +0x0b0
    checkerlib::vector_3_s009b_c580 rot_velocity2;               // +0x0bc
    checkerlib::vector_4_s009b_c580 rel_rotation;                // +0x0c8
    uint32_t pad_0d8[(0xe8 - 0xd8) / 4];
    checkerlib::vector_3_s009b_c580 new_center;                  // +0x0e8
    checkerlib::vector_3_s009b_c580 field_f4;                    // +0x0f4
    checkerlib::vector_3_s009b_c580 direction;                   // +0x100
    float    field_10c;                   // +0x10c
    float    anim_speed;                  // +0x110
    float    field_114;                   // +0x114
    uint32_t pad_118[(0x2e4 - 0x118) / 4];
    creature_body_instance_data_s009b_c580* mpBegin; // +0x2e4  (Bodies vector)
    creature_body_instance_data_s009b_c580* mpEnd;   // +0x2e8
    uint32_t pad_2ec[(0x2f8 - 0x2ec) / 4];
    void*    mpAnimState;                 // +0x2f8
    uint32_t pad_2fc[(0x15b8 - 0x2fc) / 4];
    cGameData gameData;                   // +0x15b8
    float    saved_center[3];             // +0x1644
    float    saved_orientation[4];        // +0x1650

    float     F_9b6220(checkerlib::vector_3_s009b_c580* a, checkerlib::vector_3_s009b_c580* b);       // 0x009b6220
    checkerlib::vector_3_s009b_c580* F_9b62c0(checkerlib::vector_3_s009b_c580* out, checkerlib::vector_3_s009b_c580* v);     // 0x009b62c0
    void      F_9b7b10(int a, int b);                   // 0x009b7b10
};
}
namespace nSPCreatureAnim {
checkerlib::vector_3_s009b_c580 FUN_0099c310(const checkerlib::vector_4_s009b_c580* q, const checkerlib::vector_3_s009b_c580* v);   // 0x0099c310
}
// ---- items of slice s009bc580 end

// ---- items of slice s009bd340 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_IKFloorWeightRate;   // 0x01550d88 (20.0)
extern "C" void* memset(void* dst, int value, unsigned int size);
namespace checkerlib {
class vector_3_s009b_d340 { public:
    float x, y, z;
    vector_3_s009b_d340& operator=(const vector_3_s009b_d340& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
}
namespace checkerlib {
class vector_4_s009b_d340 { public:
    float x, y, z, w;
    vector_4_s009b_d340& operator=(const vector_4_s009b_d340& o);   // 0x00572600 (EA::RectT<float>::operator= by COMDAT folding)
};
}
namespace checkerlib {
vector_3_s009b_d340* QuaternionVectorTransform(vector_3_s009b_d340* out, const vector_4_s009b_d340* q, const vector_3_s009b_d340* v);         // 0x0099c1a0
}
namespace checkerlib {
vector_3_s009b_d340* QuaternionVectorTransformInverse(vector_3_s009b_d340* out, const vector_4_s009b_d340* q, const vector_3_s009b_d340* v);  // 0x0099c310
}
namespace checkerlib {
vector_4_s009b_d340* QuaternionProduct(vector_4_s009b_d340* out, const vector_4_s009b_d340* a, const vector_4_s009b_d340* b);                // 0x0099c0b0
}
namespace checkerlib {
vector_4_s009b_d340 Normalize(const vector_4_s009b_d340& q, float* pLength);                                            // 0x0099cae0
}
checkerlib::vector_4_s009b_d340* QuaternionFromTwoVectors(checkerlib::vector_4_s009b_d340* out, const checkerlib::vector_3_s009b_d340* a, const checkerlib::vector_3_s009b_d340* b, int flag);  // 0x009ac7a0
namespace eastl {
template <typename T>
inline const T& min(const T& a, const T& b) { return (b < a) ? b : a; }
}
namespace eastl {
struct sp_vector_allocator_s009b_d340 { int mFlags; };
}
namespace eastl {
template <typename T, typename Allocator = sp_vector_allocator_s009b_d340>
class vector_s009b_d340 {
public:
    typedef unsigned int size_type;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    T& operator[](size_type n) { return *(mpBegin + n); }
};
}
namespace nSPCreatureAnim {
struct creature_static_data_s009b_d340 {
    uint32_t pad_000[0x3f4 / 4];
    bool     floor_check_caps;                  // +0x3f4
};
}
namespace nSPCreatureAnim {
struct creature_body_static_data_s009b_d340 {
    uint32_t      pad_000[0x114 / 4];
    float         floor_height;                 // +0x114
    uint32_t      pad_118[(0x150 - 0x118) / 4];
    unsigned long caps_flags;                   // +0x150

    bool HasCap(unsigned int bit) const { return ((caps_flags >> bit) & 1) != 0; }
    uint8_t       field_154;                    // +0x154
    uint8_t       pad_155[3];
    uint32_t      pad_158[(0x344 - 0x158) / 4];
    checkerlib::vector_3_s009b_d340      ik_joint_r__SCALABLE;         // +0x344 (name guessed)
    checkerlib::vector_3_s009b_d340      parent_local_joint_r__SCALABLE;  // +0x350 (name guessed)
};
}
namespace nSPCreatureAnim {
struct creature_deform {                        // 0x14 bytes
    int32_t key;                                // +0x00
    int32_t flags;                              // +0x04
    float   value8;                             // +0x08
    int32_t field_0c;                           // +0x0c
    float   value10;                            // +0x10
};
}
namespace nSPCreatureAnim {
struct creature_body_instance_data_s009b_d340 {            // size 0x2bc (retail)
    creature_body_static_data_s009b_d340*   static_data;   // +0x000
    void*                        creature;      // +0x004
    creature_body_instance_data_s009b_d340* parent;        // +0x008
    creature_body_instance_data_s009b_d340* first_child;   // +0x00c
    checkerlib::vector_3_s009b_d340                     center;        // +0x010
    checkerlib::vector_4_s009b_d340                     orientation;   // +0x01c
    checkerlib::vector_3_s009b_d340                     velocity;      // +0x02c
    bool                         floored;       // +0x038
    uint8_t                      pad_039[3];
    checkerlib::vector_3_s009b_d340                     blended_center; // +0x03c
    int32_t                      field_048;     // +0x048
    int32_t                      field_04c;     // +0x04c
    int32_t                      field_050;     // +0x050
    uint8_t                      field_054;     // +0x054
    uint8_t                      field_055;     // +0x055
    uint8_t                      pad_056[2];
    float                        reset_floats[18]; // +0x058..+0x09f
    uint32_t                     field_0a0;     // +0x0a0
    creature_deform              deforms[11];  // +0x0a4..+0x17f
    uint32_t                     pad_180[4];   // +0x180..+0x18f
    checkerlib::vector_3_s009b_d340                     saved_center; // +0x190
    checkerlib::vector_4_s009b_d340                     saved_orientation; // +0x19c
    uint32_t                     pad_1ac[(0x29c - 0x1ac) / 4];
    float                        floored_weight;     // +0x29c
    bool                         known_ground_pos;   // +0x2a0
    uint8_t                      pad_2a1[3];
    checkerlib::vector_3_s009b_d340                     ground_pos;         // +0x2a4
    checkerlib::vector_3_s009b_d340                     ground_normal;      // +0x2b0
};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009b_d340 {
    creature_static_data_s009b_d340* static_data;          // +0x000
    uint32_t pad_004[3];                        // +0x004
    int32_t  reset_counter;                     // +0x010
    uint32_t pad_014;                           // +0x014
    checkerlib::vector_3_s009b_d340 position;                          // +0x018
    uint32_t pad_024[(0x3c - 0x24) / 4];
    checkerlib::vector_4_s009b_d340 orientation;                       // +0x03c
    uint32_t pad_04c[(0x70 - 0x4c) / 4];
    float    requested_scale;                   // +0x070
    uint32_t pad_074[(0xe8 - 0x74) / 4];
    checkerlib::vector_3_s009b_d340 ground_pos;                        // +0x0e8
    checkerlib::vector_3_s009b_d340 ground_normal;                     // +0x0f4
    uint32_t pad_100[4];                        // +0x100
    float    reset_110;                         // +0x110
    float    reset_114;                         // +0x114
    uint32_t pad_118[(0x13c - 0x118) / 4];
    float    reset_floats[27];                  // +0x13c..+0x1a7
    uint8_t  reset_1a8;                         // +0x1a8
    uint8_t  reset_1a9;                         // +0x1a9
    uint8_t  pad_1aa[0x1b8 - 0x1aa];
    uint8_t  reset_mask;                        // +0x1b8
    uint8_t  pad_1b9[0x262 - 0x1b9];
    uint8_t  reset_262;                         // +0x262
    uint8_t  pad_263[0x2e4 - 0x263];
    eastl::vector_s009b_d340<creature_body_instance_data_s009b_d340, eastl::sp_vector_allocator_s009b_d340> Bodies;  // +0x2e4
    uint32_t pad_2f4[(0x168c - 0x2f4) / 4];
    uint8_t  pad_168c;
    bool     floor_enabled;                     // +0x168d
};
}
// ---- items of slice s009bd340 end

// ---- items of slice s009bfc20 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace checkerlib {
class vector_3_s009b_fc20 { public:
    float x, y, z;
    vector_3_s009b_fc20() {}
    vector_3_s009b_fc20(const vector_3_s009b_fc20& o) : x(o.x), y(o.y), z(o.z) {}
    vector_3_s009b_fc20& operator=(const vector_3_s009b_fc20& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
}
namespace checkerlib {
class vector_4_s009b_fc20 { public: float x, y, z, w; };
}
namespace checkerlib {
vector_3_s009b_fc20* QuaternionVectorTransform(vector_3_s009b_fc20* out, const vector_4_s009b_fc20* q, const vector_3_s009b_fc20* v);         // 0x0099c1a0
}
namespace checkerlib {
vector_3_s009b_fc20* QuaternionVectorTransformInverse(vector_3_s009b_fc20* out, const vector_4_s009b_fc20* q, const vector_3_s009b_fc20* v);  // 0x0099c310
}
namespace checkerlib {
vector_4_s009b_fc20* Normalize(vector_4_s009b_fc20* out, const vector_4_s009b_fc20* q, float* pLength);                            // 0x0099cae0
}
checkerlib::vector_4_s009b_fc20* QuaternionFromTwoVectors(checkerlib::vector_4_s009b_fc20* out, const checkerlib::vector_3_s009b_fc20* a, const checkerlib::vector_3_s009b_fc20* b, int flag);  // 0x009ac7a0
float __cdecl SmoothStep(float lo, float hi, float x);                                             // 0x009b01e0
static __forceinline checkerlib::vector_4_s009b_fc20 QuatMul(const checkerlib::vector_4_s009b_fc20& a, const checkerlib::vector_4_s009b_fc20& b)
{
    checkerlib::vector_4_s009b_fc20 r;
    r.x = ((b.w * a.x + b.x * a.w) - b.y * a.z) + b.z * a.y;
    r.y = ((b.w * a.y + b.y * a.w) + b.x * a.z) - b.z * a.x;
    r.z = ((b.w * a.z - b.x * a.y) + b.y * a.x) + b.z * a.w;
    r.w = ((b.w * a.w - b.x * a.x) - b.y * a.y) - b.z * a.z;
    return r;
}
static __forceinline checkerlib::vector_4_s009b_fc20 QuatConjMul(const checkerlib::vector_4_s009b_fc20& a, const checkerlib::vector_4_s009b_fc20& b)
{
    checkerlib::vector_4_s009b_fc20 r;
    r.x = ((a.w * b.x - a.x * b.w) + a.z * b.y) - a.y * b.z;
    r.y = ((a.w * b.y - a.y * b.w) - a.z * b.x) + a.x * b.z;
    r.z = ((a.y * b.x - a.z * b.w) - a.x * b.y) + a.w * b.z;
    r.w = ((a.x * b.x + a.y * b.y) + a.z * b.z) + a.w * b.w;
    return r;
}
static __forceinline checkerlib::vector_3_s009b_fc20 InvRotate(const checkerlib::vector_4_s009b_fc20& q, const checkerlib::vector_3_s009b_fc20& v)
{
    float nxw = -(q.x * q.w);
    float nzw = -(q.z * q.w);
    float nxx = -(q.x * q.x);
    float nyw = -(q.y * q.w);
    float zx = q.z * q.x;
    float yx = q.y * q.x;
    float nyy = -(q.y * q.y);
    float zy = q.z * q.y;
    float nzz = -(q.z * q.z);
    checkerlib::vector_3_s009b_fc20 r;
    r.x = (((yx - nzw) * v.y + (zx + nyw) * v.z) + (nzz + nyy) * v.x) * 2.0f + v.x;
    r.y = (((nzz + nxx) * v.y + (zy - nxw) * v.z) + (yx + nzw) * v.x) * 2.0f + v.y;
    r.z = (((nyy + nxx) * v.z + (zy + nxw) * v.y) + (zx - nyw) * v.x) * 2.0f + v.z;
    return r;
}
namespace nSPCreatureAnim {
struct goal_pos_rot_s009b_fc20 {                    // size 0x24
    checkerlib::vector_3_s009b_fc20 pos;          // +0x00
    float    pos_weight;   // +0x0c
    checkerlib::vector_4_s009b_fc20 rot;          // +0x10
    float    rot_weight;   // +0x20
};
}
namespace nSPCreatureAnim {
struct creature_body_static_data_s009b_fc20 {
    uint32_t pad_000[0x10c / 4];
    checkerlib::vector_3_s009b_fc20 rest_center__SCALABLE;      // +0x10c
    checkerlib::vector_4_s009b_fc20 rest_orientation_q;         // +0x118
    uint32_t pad_128[(0x138 - 0x128) / 4];
    checkerlib::vector_3_s009b_fc20 extent;                     // +0x138 (half size, unscaled)
    uint32_t pad_144[(0x150 - 0x144) / 4];
    uint32_t ground_flags;               // +0x150 (bit 2: store placement, bit 4: alternate)
    uint32_t pad_154[(0x468 - 0x154) / 4];

    void SetFromBuilt(uint32_t value);   // 0x009b3e40
    uint32_t Build();                    // 0x009b3cd0
};
}
namespace nSPCreatureAnim {
struct creature_body_instance_data_s009b_fc20;
}
namespace nSPCreatureAnim {
struct creature_body_ref;
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009b_fc20 {
    uint32_t pad_000[0x18 / 4];
    checkerlib::vector_3_s009b_fc20 position;                   // +0x018
    uint32_t pad_024[(0x3c - 0x24) / 4];
    checkerlib::vector_4_s009b_fc20 orientation;                // +0x03c
    uint32_t pad_04c[(0x70 - 0x4c) / 4];
    float    requested_scale;            // +0x070
    uint32_t pad_074[(0x100 - 0x74) / 4];
    checkerlib::vector_3_s009b_fc20 ground_up;                  // +0x100
    uint32_t pad_10c[(0x260 - 0x10c) / 4];
    bool     ground_placement_valid;     // +0x260
    uint8_t  pad_261[0x2e4 - 0x261];
    creature_body_instance_data_s009b_fc20* body_begin;      // +0x2e4
    creature_body_instance_data_s009b_fc20* body_end;        // +0x2e8
    creature_body_instance_data_s009b_fc20* body_capacity;   // +0x2ec

    float GetGroundHeight(const checkerlib::vector_3_s009b_fc20* pos, checkerlib::vector_3_s009b_fc20* normal);   // 0x009b6220
    checkerlib::vector_3_s009b_fc20* GetGroundUp(checkerlib::vector_3_s009b_fc20* out, const checkerlib::vector_3_s009b_fc20* pos);      // 0x009b62c0
    void FUN_009b8fd0(float* pBase, float* pRate);                  // 0x009b8fd0
    void UpdateGoalGrounds();                                       // 0x009c0680
    void UpdateGoalGround(creature_body_ref* pRef);                 // 0x009c0860
};
}
namespace nSPCreatureAnim {
struct creature_body_instance_data_s009b_fc20 {
    creature_body_static_data_s009b_fc20* static_data;  // +0x000
    uint32_t pad_004[(0x58 - 0x4) / 4];
    goal_pos_rot_s009b_fc20 goal_a;                     // +0x058
    goal_pos_rot_s009b_fc20 goal_b;                     // +0x07c
    uint32_t pad_0a0[(0x2a0 - 0xa0) / 4];
    bool     known_ground_pos;               // +0x2a0
    uint8_t  pad_2a1[3];
    checkerlib::vector_3_s009b_fc20 ground_pos;                     // +0x2a4
    checkerlib::vector_3_s009b_fc20 ground_normal;                  // +0x2b0

    void GroundGoal(checkerlib::vector_3_s009b_fc20* outPos, checkerlib::vector_4_s009b_fc20* outRot, creature_instance_data_s009b_fc20* c,
                    float baseHeight, float rate, bool storeGround);
};
}
namespace nSPCreatureAnim {
struct creature_body_ref {
    uint32_t pad_000;                        // +0x000
    creature_body_instance_data_s009b_fc20* body;       // +0x004
};
}
// ---- items of slice s009bfc20 end

// ---- items of slice s009c1f60 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char uint8;
typedef unsigned int  uint32;
namespace checkerlib {
struct vector_3_s009c_1f60 { float x, y, z; };
}
namespace checkerlib {
struct vector_4_s009c_1f60 { float x, y, z, w; };
}
namespace checkerlib {
struct matrix_3x3_s009c_1f60 { float m[3][3]; };
}
using checkerlib::vector_3_s009c_1f60;
using checkerlib::vector_4_s009c_1f60;
using checkerlib::matrix_3x3_s009c_1f60;
void operator delete[](void* p);   // 0x00f47380
namespace nSPCreatureAnim {
struct creature_body_static_data_s009c_1f60;
}
namespace nSPCreatureAnim {
struct creature_body_instance_data_s009c_1f60;
}
namespace nSPCreatureAnim {
struct wiggle_static_data {              // body wiggle descriptor, size 0x3c
    int   body;                          // +0x00
    int   cap_a;                         // +0x04
    int   cap_b;                         // +0x08
    int   channel;                       // +0x0c
    float vx, vy, vz;                    // +0x10
    vector_3_s009c_1f60 v1c;                        // +0x1c
    vector_3_s009c_1f60 v28;                        // +0x28
    float s34;                           // +0x34
    uint8 flag;                          // +0x38
    uint8 pad_39[3];
    wiggle_static_data()
    {
        v1c.z = 0.0f; v1c.y = 0.0f; v1c.x = 0.0f;
        v28.z = 0.0f; v28.y = 0.0f; v28.x = 0.0f;
        s34 = 1.0f;
    }
    wiggle_static_data& operator=(const wiggle_static_data& o);   // 0x009b3ab0 (retail CopyBlock::operator=)
};
}
namespace nSPCreatureAnim {
struct unk_pair {                        // element of the 0x3cc vector, stride 8
    creature_body_static_data_s009c_1f60* body;     // +0x00
    uint32 pad;
};
}
namespace nSPCreatureAnim {
template <typename T>
struct vec3p {
    T*     mpBegin;
    T*     mpEnd;
    T*     mpCapacity;
    uint32 mAllocator;
};
}
namespace nSPCreatureAnim {
wiggle_static_data* CopyWiggles(wiggle_static_data* first, wiggle_static_data* last, wiggle_static_data* result);   // 0x009b43f0 cdecl
}
namespace nSPCreatureAnim {
struct wiggle_vec : vec3p<wiggle_static_data> {
    void DoInsert(wiggle_static_data* pos, const wiggle_static_data& v);   // 0x009c10c0 ret 8
    void erase(wiggle_static_data* first, wiggle_static_data* last)
    {
        CopyWiggles(last, mpEnd, first);
        mpEnd -= (last - first);
    }
    void erase(wiggle_static_data* position)
    {
        if ((position + 1) < mpEnd)
            CopyWiggles(position + 1, mpEnd, position);
        --mpEnd;
    }
};
}
namespace nSPCreatureAnim {
struct bone_xform {                      // pair<matrix_3x3, vector_3>, size 0x30
    matrix_3x3_s009c_1f60 first;
    vector_3_s009c_1f60   second;
    bone_xform()
    {
        first.m[0][1] = 0.0f; first.m[0][2] = 0.0f;
        first.m[1][0] = 0.0f; first.m[1][2] = 0.0f;
        first.m[2][0] = 0.0f; first.m[2][1] = 0.0f;
        first.m[2][2] = 1.0f; first.m[1][1] = 1.0f; first.m[0][0] = 1.0f;
        second.z = 0.0f; second.y = 0.0f; second.x = 0.0f;
    }
};
}
namespace nSPCreatureAnim {
bone_xform* CopyBoneXforms(bone_xform* first, bone_xform* last, bone_xform* result);   // 0x009b4550 cdecl
}
namespace nSPCreatureAnim {
struct bone_xform_vec : vec3p<bone_xform> {
    void resize(unsigned n);             // 0x009c2520
    void DoInsertValues(bone_xform* pos, unsigned n, const bone_xform& v);   // 0x009c11e0 ret 0xc
};
}
namespace nSPCreatureAnim {
struct body_entry {                      // element of the built body list, size 0x30
    void*                        static_pair;   // +0x00
    creature_body_instance_data_s009c_1f60* body;          // +0x04
    float                        m[6];          // +0x08
    float                        w0;             // +0x20
    float                        w1;             // +0x24
    float                        w2;             // +0x28
    float                        w3;             // +0x2c
};
}
namespace nSPCreatureAnim {
struct body_entry_list {
    body_entry* mpBegin;
    body_entry* mpEnd;
    body_entry* mpCapacity;
    void* Resize(int n);                                       // 0x009c0b00
    void  Append(body_entry* at, const body_entry& v);         // 0x009c0f60
};
}
namespace nSPCreatureAnim {
struct cBuilding {
    body_entry_list* func8Ch();          // 0x00ad2800
};
}
namespace nSPCreatureAnim {
struct creature_body_static_data_s009c_1f60 {       // retail size 0x468
    uint8      pad_000[0x10c];
    vector_3_s009c_1f60   rest_center;              // +0x10c
    vector_4_s009c_1f60   rest_orientation_q;       // +0x118
    uint8      pad_128[0x18];            // +0x128 .. 0x140
    float      unk_140;                  // +0x140
    uint8      pad_144[0xc];             // +0x144 .. 0x150
    uint32     cap_flags;                // +0x150
    uint8      pad_154[0xa4];            // +0x154 .. 0x1f8
    uint32     bidx;                     // +0x1f8
    int        parent_bidx;              // +0x1fc
    uint8      pad_200[0x268];           // +0x200 .. 0x468
};
}
namespace nSPCreatureAnim {
struct creature_body_instance_data_s009c_1f60 {     // retail size 0x2bc
    creature_body_static_data_s009c_1f60* static_data;   // +0x00
    uint8      pad_004[0x2bc - 4];
};
}
namespace nSPCreatureAnim {
struct creature_static_data_s009c_1f60 {            // retail size >= 0x408
    uint8          pad_000[0x324];
    vector_3_s009c_1f60       skin_colors[3];       // +0x324
    int            RefCount;             // +0x348
    uint8          pad_34c[0xc];         // +0x34c .. 0x358
    vector_3_s009c_1f60       local_aabb_origin;    // +0x358
    vector_3_s009c_1f60       local_aabb_extent;    // +0x364
    uint8          pad_370[0x14];        // +0x370 .. 0x384
    vec3p<creature_body_static_data_s009c_1f60> Bodies;      // +0x384
    uint8          pad_394[4];           // +0x394 .. 0x398
    vec3p<creature_body_static_data_s009c_1f60> mUnk398;     // +0x398
    uint8          pad_3a8[4];           // +0x3a8 .. 0x3ac
    uint32         spine_start_bidx;     // +0x3ac
    uint32         spine_end_bidx;       // +0x3b0
    wiggle_vec     mWiggles;             // +0x3b4
    uint8          pad_3c4[8];           // +0x3c4 .. 0x3cc
    vec3p<unk_pair> mUnk3cc;             // +0x3cc
    uint8          pad_3dc[0x18];        // +0x3dc .. 0x3f4
    bool           mIsLegless;           // +0x3f4
    bool           mIgnoreGait;          // +0x3f5
    uint8          pad_3f6[2];           // +0x3f6 .. 0x3f8
    vec3p<bone_xform> inv_bone_rest_xforms;       // +0x3f8

    creature_static_data_s009c_1f60();
    ~creature_static_data_s009c_1f60();
    int  Release();
    bool FilterAndAddWiggle(wiggle_static_data* w, bool keep, bool sym);  // 0x009c2300 (nSPCreatureAnim::creature_static_data::FilterAndAddWiggle)
    void InitWiggles();
    void Clear(int flag);                // 0x009c1dc0
};
}
namespace nSPCreatureAnim {
struct wiggle_instance_data {            // element of instance mWiggles, size 0x2c
    wiggle_static_data* wiggle;          // +0x00
    uint8   flag4;                       // +0x04
    uint8   flag5;                       // +0x05
    uint8   pad_006a;
    uint8   pad_006b;
    vector_3_s009c_1f60 zero;                       // +0x08
    vector_3_s009c_1f60 pos;                        // +0x14
    vector_3_s009c_1f60 pos_copy;                   // +0x20
    wiggle_instance_data()
    {
        zero.z = 0.0f; zero.y = 0.0f; zero.x = 0.0f;
        pos.z = 0.0f; pos.y = 0.0f; pos.x = 0.0f;
        pos_copy.z = 0.0f; pos_copy.y = 0.0f; pos_copy.x = 0.0f;
    }
};
}
namespace nSPCreatureAnim {
void DestroyWiggleInstances(void* first, void* last, void* result);   // 0x009b4a20 cdecl
}
namespace nSPCreatureAnim {
struct wiggle_instance_vec : vec3p<wiggle_instance_data> {
    void resize(unsigned n);             // 0x009c25f0
    void DoInsertValues(wiggle_instance_data* pos, unsigned n, const wiggle_instance_data& v);   // 0x009c13a0 ret 0xc
};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009c_1f60 {
    creature_static_data_s009c_1f60* static_data;   // +0x000
    uint8      pad_004[0x18 - 0x4];
    vector_3_s009c_1f60   position;                 // +0x018
    uint8      pad_024[0x3c - 0x24];
    vector_4_s009c_1f60   orientation;              // +0x03c
    uint8      pad_04c[0x70 - 0x4c];
    float      requested_scale;          // +0x070
    uint8      pad_074[0x2e4 - 0x74];
    vec3p<creature_body_instance_data_s009c_1f60> Bodies;    // +0x2e4
    uint8      pad_2f4[0x15b8 - 0x2f4];
    cBuilding  building;                 // +0x15b8 (size 1)
    uint8      pad_15b9[0x1640 - 0x15b9];
    int        last_joint_index;         // +0x1640
    uint8      pad_1644[0x168e - 0x1644];
    uint8      flag_168e;                // +0x168e
    uint8      pad_168f;
    float      f_1690;                   // +0x1690
    wiggle_instance_vec mWiggles;        // +0x1694
    uint8      pad_16a4[0x16a8 - 0x16a4];
    float      f_16a8;                   // +0x16a8
    uint8      pad_16ac[0x16c4 - 0x16ac];
    wiggle_static_data desc_a;           // +0x16c4
    wiggle_instance_data inst_a;         // +0x1700
    wiggle_static_data desc_b;           // +0x172c
    wiggle_instance_data inst_b;         // +0x1768

    void BuildBodyList();
    void InitWiggles();  // 0x009c2c20 (nSPCreatureAnim::creature_instance_data::InitWiggles)
};
}
namespace nSPCreatureAnim {
struct FixedNodePool {                   // eastl::fixed_node_pool<20,...>, size 0x14
    void*    mpHead;                     // +0x00
    uint32   pad04;
    void*    mpNext;                     // +0x08
    void*    mpCapacity;                 // +0x0c
    uint32   mnNodeSize;                 // +0x10
    void init(void* mem, unsigned memSize, unsigned nodeSize, unsigned align, unsigned alignOffset);   // 0x00921260 (eastl::fixed_pool_base::init) ret 0x14
};
}
namespace nSPCreatureAnim {
struct RBNodeU32 {                       // rbtree node: right, left, parent, color, then the value
    RBNodeU32* mpNodeRight;
    RBNodeU32* mpNodeLeft;
    RBNodeU32* mpNodeParent;
    uint32     mColor;
    uint32     mKey;                     // +0x10
    void*      mValue;                   // +0x14
};
}
namespace nSPCreatureAnim {
RBNodeU32* RBTreeIncrementU32(RBNodeU32* node);                         // 0x00921580 cdecl
}
namespace nSPCreatureAnim {
struct KVPair { uint32 first; void* second; };
}
namespace nSPCreatureAnim {
struct RbInsertResult { RBNodeU32* mpNode; int mbInserted; };
}
namespace nSPCreatureAnim {
struct RbTrueType {};
}
namespace nSPCreatureAnim {
struct FixedMapU32 {                     // eastl::fixed_map<unsigned, void*, 255>, size 0x2c
    uint32      mCompare;                // +0x00 (empty class slot)
    RBNodeU32*  mpNodeRight;             // +0x04  (anchor)
    RBNodeU32*  mpNodeLeft;              // +0x08
    RBNodeU32*  mpNodeParent;            // +0x0c
    uint32      mColor;                  // +0x10
    uint32      mnSize;                  // +0x14
    FixedNodePool mAllocator;            // +0x18

    RBNodeU32* anchor() { return (RBNodeU32*)&mpNodeRight; }
    RbInsertResult insert(const KVPair& v, RbTrueType t);               // 0x009c1700 (sret, ret 0xc)
    void DoNukeSubtree(RBNodeU32* pNode);                               // 0x00d3b370 ret 4
};
}
namespace nSPCreatureAnim {
struct FixedVecU32 {                     // eastl::fixed_vector<unsigned, 255, true>
    uint32* mpBegin;                     // +0x00
    uint32* mpEnd;                       // +0x04
    uint32* mpCapacity;                  // +0x08
    uint32  mAllocPad;                   // +0x0c
    uint32* mpBuffer;                    // +0x10
    uint32  mPad14;                      // +0x14
    uint32  mBuffer[255];                // +0x18
    void DoInsertValue(uint32* pos, const uint32& v);                   // 0x00899480 ret 8
    void push_back(const uint32& v)
    {
        if (mpEnd < mpCapacity) {
            uint32* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};
}
namespace nSPCreatureAnim {
bool CreateWiggle(creature_static_data_s009c_1f60* c, int index, wiggle_static_data* desc,
                  int a, int b, int c2, int d, int e, int f);           // 0x009ba4c0
}
namespace nSPCreatureAnim {
void AddWiggle(creature_static_data_s009c_1f60* c, wiggle_static_data* w);         // 0x009ba590
}
namespace nSPCreatureAnim {
bool FUN_009b3150(const void* a, const void* b);                        // 0x009b3150
}
namespace nSPCreatureAnim {
int  FUN_009d7d10(creature_instance_data_s009c_1f60* c, float* pos, float* rot);   // 0x009d7d10
}
namespace nSPCreatureAnim {
void* FUN_00a09f50();                                                   // 0x00a09f50
}
namespace nSPCreatureAnim {
extern int   g_gait_channel;               // 0x0166c130
}
namespace nSPCreatureAnim {
extern uint8 g_wiggle_symmetry;            // 0x01550c2d
}
namespace nSPCreatureAnim {
static inline float PickGait(const wiggle_static_data* w, int g)
{
    float v;
    switch (g) {
    case 0:  v = w->vx; break;
    case 1:  v = w->vy; break;
    case 2:  v = w->vz; break;
    default: v = 0.0f;  break;
    }
    return v;
}
}
// ---- items of slice s009c1f60 end

// ---- items of slice s009c32c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memcpy(void* dst, const void* src, unsigned int n);   // 0x011e0744 thunk
#pragma intrinsic(sqrt)
typedef unsigned int   uint32_s009c_32c0;
namespace checkerlib {
struct vector_3_s009c_32c0 { float x, y, z; };
}
namespace checkerlib {
struct vector_4_s009c_32c0 { float x, y, z, w; };
}
namespace checkerlib {
struct matrix_3x3_s009c_32c0 { float m[3][3]; };
}
using checkerlib::vector_3_s009c_32c0;
using checkerlib::vector_4_s009c_32c0;
using checkerlib::matrix_3x3_s009c_32c0;
namespace eastl {
template <typename T> inline const T& max(const T& a, const T& b) { return (a < b) ? b : a; }
}
namespace eastl {
template <typename T> inline void swap(T& a, T& b) { T temp(a); a = b; b = temp; }
}
namespace eastl {
struct sp_vector_allocator_s009c_32c0 {
    sp_vector_allocator_s009c_32c0() {}
    void deallocate(void* p) { if (((int*)p)[-1] != 0) operator delete[](p); }
};
}
namespace eastl {
template <typename T, int nodeCount>
struct fixed_vector_s009c_32c0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_s009c_32c0 mOverflowAllocator;
    T* mpPoolBegin;
    uint32_s009c_32c0 mPad;
    T mBuffer[nodeCount];

    fixed_vector_s009c_32c0() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + nodeCount)
    {
        mpPoolBegin = mBuffer;
    }
    fixed_vector_s009c_32c0(unsigned n, const T& value);                    // 0x009c3210
    ~fixed_vector_s009c_32c0()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }

    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](unsigned i) { return mpBegin[i]; }

    void DoInsertValue(T* position, const T& value);             // 0x00899480
    void DoInsertValues(T* position, unsigned n, const T& value);  // 0x0089a8e0

    void push_back(const T& value)                               // out of line: 0x00886db0
    {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            if (p)
                *p = value;
        } else
            DoInsertValue(mpEnd, value);
    }
    T* erase(T* first, T* last)
    {
        memcpy(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void resize(unsigned n)                                      // out of line: 0x0089cb60
    {
        T value = T();
        unsigned s = size();
        if (n > s)
            DoInsertValues(mpEnd, n - s, value);
        else
            erase(mpBegin + n, mpEnd);
    }
};
}
namespace nSPCreatureAnim {
enum {
    kCapNameRoot    = 0x746f6f72,   // "root"
    kCapNameFoot    = 0x746f6f66,   // "foot"
    kCapNameMouth   = 0x74756f6d,   // "mout"
    kCapNameLimb    = 0x626d696c,   // "limb"
    kCapNameSpine   = 0x6e697073,   // "spin"
    kCapNameGrasper = 0x70737267,   // "grsp"
    kCapNamePsft    = 0x74667370,   // "psft"
    kCapNameNstr    = 0x7274736e,   // "nstr"
};
}
namespace nSPCreatureAnim {
enum {
    kCapRoot    = 0x01,
    kCapLimb    = 0x02,
    kCapFoot    = 0x04,
    kCapSpine   = 0x08,
    kCapPsft    = 0x10,
    kCapMouth   = 0x20,
    kCapGrasper = 0x40,
    kCapNstr    = 0x80,
};
}
namespace nSPCreatureAnim {
struct creature_body_static_data_s009c_32c0 {                // retail size 0x468
    char name[260];                                // 0x000
    uint32_s009c_32c0 instance_id;                            // 0x104
    uint32_s009c_32c0 group_id;                               // 0x108
    vector_3_s009c_32c0 rest_center;                          // 0x10c
    vector_4_s009c_32c0 rest_orientation_q;                   // 0x118
    vector_4_s009c_32c0 rest_parent_rel_orientation_q;        // 0x128
    uint32_s009c_32c0 pad138[3];
    vector_3_s009c_32c0 rest_joint_offset;                    // 0x144
    uint32_s009c_32c0 cap_flags;                              // 0x150  every cap present
    uint32_s009c_32c0 owned_cap_flags;                        // 0x154  caps with a non-zero value
    uint32_s009c_32c0 NameFOURCCs[32];                        // 0x158
    uint8 Values[32];                              // 0x1d8
    uint32_s009c_32c0 bidx;                                   // 0x1f8
    int parent_bidx;                               // 0x1fc
    int symmetric_bidx;                            // 0x200  -2 = not computed yet
    int first_child_bidx;                          // 0x204
    uint32_s009c_32c0 num_children;                           // 0x208
    uint32_s009c_32c0 pad20c[2];
    creature_body_static_data_s009c_32c0* parent;             // 0x214
    creature_body_static_data_s009c_32c0* first_child;        // 0x218
    uint32_s009c_32c0 bone_idx;                               // 0x21c
    uint32_s009c_32c0 pad220[73];
    vector_3_s009c_32c0 local_joint_r;                        // 0x344
    vector_3_s009c_32c0 parent_local_joint_r;                 // 0x350
    vector_3_s009c_32c0 joint_r;                              // 0x35c
    float joint_r_len;                             // 0x368
    float workspace_radius;                        // 0x36c
    uint32_s009c_32c0 pad370[61];
    bool in_leg_chain;                             // 0x464
    uint8 pad465[3];

    void CopyFrom(const creature_body_static_data_s009c_32c0& other);   // 0x009b3490
};
}
namespace nSPCreatureAnim {
struct body_vector_s009c_32c0 {                               // eastl::vector<creature_body_static_data, sp_vector_allocator>
    creature_body_static_data_s009c_32c0* mpBegin;
    creature_body_static_data_s009c_32c0* mpEnd;
    creature_body_static_data_s009c_32c0* mpCapacity;
    eastl::sp_vector_allocator_s009c_32c0 mAllocator;

    body_vector_s009c_32c0(unsigned n, const eastl::sp_vector_allocator_s009c_32c0& allocator);   // 0x009c0bb0
    ~body_vector_s009c_32c0()
    {
        if (mpBegin)
            mAllocator.deallocate(mpBegin);
    }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    creature_body_static_data_s009c_32c0& operator[](unsigned i) { return mpBegin[i]; }
    void swap(body_vector_s009c_32c0& other);                 // 0x009c0ed0
};
}
namespace nSPCreatureAnim {
struct bone_xform_s009c_32c0 {                                // eastl::pair<matrix_3x3, vector_3>
    matrix_3x3_s009c_32c0 first;
    vector_3_s009c_32c0 second;
};
}
namespace nSPCreatureAnim {
struct bone_xform_vector {
    bone_xform_s009c_32c0* mpBegin;
    bone_xform_s009c_32c0* mpEnd;
    bone_xform_s009c_32c0* mpCapacity;
    uint32_s009c_32c0 mAllocator;
    void resize(unsigned n);                       // 0x009c2520
};
}
namespace nSPCreatureAnim {
struct creature_static_data_s009c_32c0 {
    uint8 pad0[0x37c];
    uint32_s009c_32c0 num_bones;                              // 0x37c
    uint32_s009c_32c0 pad380;
    body_vector_s009c_32c0 Bodies;                            // 0x384
    uint32_s009c_32c0 pad394[6];
    uint32_s009c_32c0 spine_start_bidx;                       // 0x3ac
    uint32_s009c_32c0 spine_end_bidx;                         // 0x3b0
    uint32_s009c_32c0 pad3b4[16];
    bool mIsLegless;                               // 0x3f4
    uint8 pad3f5[3];
    bone_xform_vector inv_bone_rest_xforms;        // 0x3f8
};
}
namespace nSPCreatureAnim {
typedef eastl::fixed_vector_s009c_32c0<uint32_s009c_32c0, 255> index_vector;
}
namespace nSPCreatureAnim {
extern int g_bRootAtClosestSpine;      // 0x0166c004
}
namespace nSPCreatureAnim {
extern int g_bRootAtMidSpine;          // 0x01550a84
}
namespace nSPCreatureAnim {
extern float g_WorkspaceRadiusPad;     // 0x01550a10
}
namespace nSPCreatureAnim {
extern float g_WorkspaceRadiusScale;   // 0x01550a78
}
namespace nSPCreatureAnim {
void AddExtraBonesAsNecessary(creature_static_data_s009c_32c0* c, uint32_s009c_32c0 bidx);   // 0x009b5f90 (bidx in eax)
}
namespace nSPCreatureAnim {
void ComputeBodyStatics(creature_static_data_s009c_32c0* c);                      // 0x009b5c50
}
namespace nSPCreatureAnim {
void BuildHierarchyOrder(creature_static_data_s009c_32c0* c, index_vector* order,
                         index_vector* children, uint32_s009c_32c0 root);          // 0x009c3150
}
namespace nSPCreatureAnim {
inline uint32_s009c_32c0 CapFlagFromName(uint32_s009c_32c0 name)
{
    switch (name) {
    case kCapNameSpine:   return kCapSpine;
    case kCapNameLimb:    return kCapLimb;
    case kCapNameGrasper: return kCapGrasper;
    case kCapNameNstr:    return kCapNstr;
    case kCapNamePsft:    return kCapPsft;
    case kCapNameFoot:    return kCapFoot;
    case kCapNameRoot:    return kCapRoot;
    case kCapNameMouth:   return kCapMouth;
    default:              return 0;
    }
}
}
namespace nSPCreatureAnim {
__forceinline void ComputeInverseRestXform(const creature_body_static_data_s009c_32c0& b, bone_xform_s009c_32c0& out)
{
    const vector_4_s009c_32c0& q = b.rest_orientation_q;
    const vector_3_s009c_32c0& p = b.rest_center;

    float nxw = -(q.x * q.w);
    float nzw = -(q.z * q.w);
    float zx = q.z * q.x;
    float nxx = -(q.x * q.x);
    float yx = q.y * q.x;
    float zy = q.z * q.y;
    float nyw = -(q.y * q.w);
    float nyy = -(q.y * q.y);
    float nzz = -(q.z * q.z);
    vector_3_s009c_32c0 t;
    t.x = -((((nzz + nyy) * p.x + (zx + nyw) * p.z) + (yx - nzw) * p.y) * 2.0f + p.x);
    t.y = -((((yx + nzw) * p.x + (zy - nxw) * p.z) + (nzz + nxx) * p.y) * 2.0f + p.y);
    t.z = -((((zx - nyw) * p.x + (nyy + nxx) * p.z) + (zy + nxw) * p.y) * 2.0f + p.z);

    float cx = -q.x, cy = -q.y, cz = -q.z, w = q.w;
    float xx = cx * cx, xy = cx * cy, yy = cy * cy, xz = cx * cz, yz = cy * cz;
    float xw = cx * w, zz = cz * cz, wy = w * cy, wz = w * cz;
    matrix_3x3_s009c_32c0 r;
    r.m[0][0] = 1.0f - (zz + yy) * 2.0f;
    r.m[0][1] = (xy - wz) * 2.0f;
    r.m[0][2] = (wy + xz) * 2.0f;
    r.m[1][0] = (wz + xy) * 2.0f;
    r.m[1][1] = 1.0f - (zz + xx) * 2.0f;
    r.m[1][2] = (yz - xw) * 2.0f;
    r.m[2][0] = (xz - wy) * 2.0f;
    r.m[2][1] = (xw + yz) * 2.0f;
    r.m[2][2] = 1.0f - (yy + xx) * 2.0f;

    matrix_3x3_s009c_32c0 rot;
    for (int i = 0; i < 3; ++i) {
        rot.m[0][i] = r.m[0][i];
        rot.m[1][i] = r.m[1][i];
        rot.m[2][i] = r.m[2][i];
    }
    out.first = rot;
    out.second = t;
}
}
// ---- items of slice s009c32c0 end

// ---- items of slice s009c4a30 begin (TODO(rewrite): local stubs, replace by canonical classes)
float sqrtf(float);
namespace nSPCreatureAnim {
struct creature_static_data_s009c_4a30;
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009c_4a30;
}
namespace nSPCreatureAnim {
struct creature_static_data_s009c_4a30 {
    uint8 blob[0x410];

    int   Release();                       // 0x009c26a0
    void  InitWiggles();                   // 0x009c26f0
    void  FUN_009c1d30();                  // 0x009c1d30
    void  FUN_009b54a0();                  // 0x009b54a0
    void  FUN_009b5580();                  // 0x009b5580
    void  FUN_009b5930();                  // 0x009b5930
    void  FUN_009bfa20();                  // 0x009bfa20
    float FUN_009b5360();                  // 0x009b5360
};
}
namespace nSPCreatureAnim {
bool ComputeHierarchy(creature_static_data_s009c_4a30* c, int flag);   // 0x009c32c0
}
namespace nSPCreatureAnim {
void FUN_009b6b10(float* mn, float* mx, creature_static_data_s009c_4a30* c);   // 0x009b6b10
}
namespace nSPCreatureAnim {
void FUN_009b5ce0(creature_static_data_s009c_4a30* c);                 // 0x009b5ce0
}
namespace nSPCreatureAnim {
void FUN_009bf5c0(void* first, void* last, void* out);      // 0x009bf5c0
}
namespace nSPCreatureAnim {
void FUN_009b4a20(void* first, void* last, void* out);      // 0x009b4a20
}
namespace nSPCreatureAnim {
struct M3 { float f[9]; void FUN_0099ce40(); };             // 0x0099ce40
}
namespace nSPCreatureAnim {
void FUN_009e3f70(void* self, int a, int b);                // 0x009e3f70
}
namespace nSPCreatureAnim {
void FUN_009bd340(creature_instance_data_s009c_4a30* c);               // 0x009bd340
}
namespace nSPCreatureAnim {
void* FUN_011e073e(void* p, int a, int b);                  // 0x011e073e
}
namespace nSPCreatureAnim {
void  FUN_009db1d0(void* self);                             // 0x009db1d0
}
namespace nSPCreatureAnim {
void  FUN_009db270(void* self);                             // 0x009db270
}
namespace nSPCreatureAnim {
void  FUN_009db4d0(void* self, float v);                    // 0x009db4d0
}
namespace nSPCreatureAnim {
void  FUN_009db6d0(void* self, float v, creature_instance_data_s009c_4a30* c);  // 0x009db6d0
}
namespace nSPCreatureAnim {
void  FUN_009d34a0(void* self);                             // 0x009d34a0
}
namespace nSPCreatureAnim {
void  FUN_009da640(void* self, creature_instance_data_s009c_4a30* c);  // 0x009da640
}
namespace nSPCreatureAnim {
void  FUN_009d3170(void* self);                             // 0x009d3170
}
namespace nSPCreatureAnim {
struct phasegroup_vec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32 mAllocator;
    void DoDestroyValues(void* first, void* last);          // 0x009c3240
};
}
namespace nSPCreatureAnim {
class dynamics_walking_s009c_4a30 { public:
    uint8           pad00[0x10];
    phasegroup_vec  groups;                                 // 0x10
    uint8           pad20[0x24 - 0x20];
    void*           feet;                                   // 0x24
    uint8           pad28[0x38 - 0x28];
    void*           vert;                                   // 0x38
    ~dynamics_walking_s009c_4a30();
};
}
namespace nSPCreatureAnim {
struct body_vec {                                           // object at instance+0x2e4
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32 mAllocator;
    void FUN_009c3040(int n);                               // 0x009c3040
};
}
namespace nSPCreatureAnim {
struct sub_2f8 {                                            // object at instance+0x2f8
    uint8 pad[0x10];
    void FUN_009e3f70(int a, int b);                        // 0x009e3f70
    void FUN_009b59c0();                                    // 0x009b59c0
};
}
namespace nSPCreatureAnim {
struct ik_vec {                                             // object at instance+0x24c
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32 mAllocator;
    void resize(int n);                                     // 0x009c2ef0
};
}
namespace nSPCreatureAnim {
struct instance_hashtable {                                 // object at instance+0x17a0
    uint32 mAllocator0;                                     // +0x00
    void*  mpBucketArray;                                   // +0x04
    uint32 mnBucketCount;                                   // +0x08
    uint32 mnElementCount;                                  // +0x0c
    uint32 pad10[3];                                        // +0x10
    void*  mpFreeList;                                      // +0x1c  (fixed allocator free list)
    uint32 pad20;                                           // +0x20
    void*  mpPoolBegin;                                     // +0x24
    void*  mpPoolEnd;                                       // +0x28
    uint32 pad2c;
    void*  mpFixedBuffer;                                   // +0x30
    void DoFreeNodes(void* a, void* b);                     // 0x00a1b6c0
};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009c_4a30 {
    uint8 blob[0x17b0];

    void Clear(bool flag);                                  // 0x009c4d40
    __declspec(noinline) int Release();                     // 0x009c4cc0
    ~creature_instance_data_s009c_4a30();                              // 0x009c4bf0
    void InitWiggles();                                     // 0x009c2c20
    void BuildBodyList();                                   // 0x009c20e0
    void FUN_009c4d10();                                    // 0x009c4d10
    void FUN_009cb4f0();                                    // 0x009cb4f0
    void FUN_009b6360();                                    // 0x009b6360
};
}
namespace nSPCreatureAnim {
#define F(o) (*(float*)(b + (o)))
}
namespace nSPCreatureAnim {
struct V2 { float x, y; V2& operator=(const V2& o) { x = o.x; y = o.y; return *this; } };
}
namespace nSPCreatureAnim {
struct V3 { float x, y, z; V3& operator=(const V3& o) { x = o.x; y = o.y; z = o.z; return *this; } };
}
namespace nSPCreatureAnim {
#define V2AT(o) (*(V2*)(b + (o)))
}
namespace nSPCreatureAnim {
#define V3AT(o) (*(V3*)(b + (o)))
}
namespace nSPCreatureAnim {
struct Elem2bc { uint8 d[0x2bc]; };
}
namespace nSPCreatureAnim {
struct Elem2c  { uint8 d[0x2c]; };
}
namespace nSPCreatureAnim {
struct vec2bc { Elem2bc* mpBegin; Elem2bc* mpEnd; };
}
namespace nSPCreatureAnim {
struct vec2c  { Elem2c*  mpBegin; Elem2c*  mpEnd; };
}
// ---- items of slice s009c4a30 end

// ---- items of slice s009b3e40 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace nSPCreatureAnim {
struct wiggle_static_data_s009b_3e40 {
    int   a0, a1, a2, a3;              // +0x00
    float f[10];                       // +0x10
    uint8_t c;                         // +0x38
    uint8_t pad_39[3];
    wiggle_static_data_s009b_3e40& operator=(const wiggle_static_data_s009b_3e40& o)
    {
        a0 = o.a0; a1 = o.a1; a2 = o.a2; a3 = o.a3;
        f[0] = o.f[0]; f[1] = o.f[1]; f[2] = o.f[2]; f[3] = o.f[3]; f[4] = o.f[4];
        f[5] = o.f[5]; f[6] = o.f[6]; f[7] = o.f[7]; f[8] = o.f[8]; f[9] = o.f[9];
        c = o.c;
        return *this;
    }
};
}
namespace nSPCreatureAnim {
struct wiggle_instance_data_s009b_3e40 {
    void*   wiggle;                    // +0x00
    uint8_t flag4;                     // +0x04
    uint8_t flag5;                     // +0x05
    uint8_t pad_06[2];
    float   f[9];                      // +0x08
    wiggle_instance_data_s009b_3e40& operator=(const wiggle_instance_data_s009b_3e40& o);   // 0x009b4230
};
}
namespace nSPCreatureAnim {
struct xform12 {
    float m[9];                        // +0x00
    float v[3];                        // +0x24
    xform12& operator=(const xform12& o);   // 0x009b41e0
};
}
namespace nSPCreatureAnim {
struct Transform30_s009b_3e40 {
    int   a;                           // +0x00
    int   b;                           // +0x04
    float f[10];                       // +0x08
    Transform30_s009b_3e40& operator=(const Transform30_s009b_3e40& o)
    {
        a = o.a; b = o.b;
        f[0] = o.f[0]; f[1] = o.f[1]; f[2] = o.f[2]; f[3] = o.f[3]; f[4] = o.f[4];
        f[5] = o.f[5]; f[6] = o.f[6]; f[7] = o.f[7]; f[8] = o.f[8]; f[9] = o.f[9];
        return *this;
    }
};
}
namespace nSPCreatureAnim {
struct bone_xform_s009b_3e40 {
    float m[9];                        // +0x00
    float v[3];                        // +0x24
    bone_xform_s009b_3e40& operator=(const bone_xform_s009b_3e40& o)
    {
        memcpy(m, o.m, sizeof(m));
        float* d = v; const float* s = o.v;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2];
        return *this;
    }
};
}
namespace nSPCreatureAnim {
struct blob_f4 {
    uint32_t u00;                      // +0x00
    float    f04[7];                   // +0x04
    uint32_t u20;                      // +0x20
    float    f24[19];                  // +0x24
    uint8_t  b70, b71;                 // +0x70
    float    f74[3];                   // +0x74
    float    f80[6];                   // +0x80
    uint32_t u98[4];                   // +0x98
    uint8_t  ba8, ba9;                 // +0xa8
    uint32_t uac;                      // +0xac
    float    fb0;                      // +0xb0
    uint32_t ub4, ub8;                 // +0xb4
    float    fbc[14];                  // +0xbc
    blob_f4& operator=(const blob_f4& o);   // 0x009b45b0
};
}
namespace nSPCreatureAnim {
struct creature_body_static_data_s009b_3e40 {
    char     name[0x104];              // +0x000
    uint32_t instance_id;              // +0x104
    uint32_t group_id;                 // +0x108
    float    f10c[17];                 // +0x10c
    uint32_t w150[0x2a];               // +0x150
    uint32_t w1f8[10];                 // +0x1f8
    uint32_t w220[0x41];               // +0x220
    float    f324[6];                  // +0x324
    uint32_t u33c;                     // +0x33c
    uint8_t  b340;                     // +0x340
    uint8_t  pad341[3];
    float    f344[11];                 // +0x344
    uint8_t  b370;                     // +0x370
    uint8_t  b371;                     // +0x371
    uint8_t  pad372[2];
    float    f374[3];                  // +0x374
    uint32_t w380[0x29];               // +0x380
    uint32_t u424;                     // +0x424
    uint32_t u428;                     // +0x428
    uint8_t  b42c;                     // +0x42c
    uint8_t  pad42d[3];
    uint32_t u430;                     // +0x430
    float    f434[3];                  // +0x434
    uint32_t u440;                     // +0x440
    uint32_t u444;                     // +0x444
    float    f448[7];                  // +0x448
    uint8_t  b464;                     // +0x464
    uint8_t  pad465[3];
    creature_body_static_data_s009b_3e40& operator=(const creature_body_static_data_s009b_3e40& o);   // 0x009b3e40
};
}
namespace nSPCreatureAnim {
struct creature_static_data_s009b_3e40 {
    uint8_t  pad_000[0x384];
    creature_body_static_data_s009b_3e40* Bodies;      // +0x384
    creature_body_static_data_s009b_3e40* BodiesEnd;   // +0x388
    uint8_t  pad_38c[0x440 - 0x38c];
    uint32_t u440;                          // +0x440
    void FUN_009b4ce0();
};
}
void NormalizeVec3(float* out, const float* v, float* lenOut);   // 0x009a49d0
// ---- items of slice s009b3e40 end

// ---- items of slice s009b4e00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_14471fc;  // 0.0f (or small)  0x014471fc
extern const float g_1550b04;  // int  0x01550b04 (global gate)
extern const float g_1550d3c;  // float 0x01550d3c
extern const float g_1550d40;  // float 0x01550d40
extern const float g_1550d44;  // float 0x01550d44
extern const float g_1550d48;  // float 0x01550d48
#pragma intrinsic(fabs)
void* __cdecl FUN_0099c1a0(void* out, void* quat, void* pos);   // 0x0099c1a0 QuaternionVectorTransform
int  __cdecl FUN_009b4d90();                                     // 0x009b4d90
void __cdecl FUN_009b3090(unsigned int tag, int n);              // 0x009b3090
void __cdecl FUN_009dfc40(int* p);                               // 0x009dfc40 AnimA dtor
void __cdecl FUN_009dfd30(int* p);                               // 0x009dfd30 AnimC dtor
double __cdecl FUN_009f9c60(void* p);                            // 0x009f9c60
bool __cdecl nSPCreatureAnim_ShouldJiggle(void* p);              // ShouldJiggle
namespace nSPCreatureAnim {
struct Bone {                       // stride 0x468; only the used fields are modelled
    unsigned char pad0[0x10c];
    float mOffsetX;                 // +0x10c
    float mOffsetY;                 // +0x110
    float mOffsetZ;                 // +0x114
    unsigned char pad1[0x2c];       // +0x118 .. 0x144
    float mParentOffX;              // +0x144
    float mParentOffY;              // +0x148
    float mParentOffZ;              // +0x14c
    unsigned char mFlags150;        // +0x150
    unsigned char pad2[0x3];        // +0x151 .. 0x154
    unsigned char mFlags154;        // +0x154
    unsigned char pad3[0x1b8 - 0x155];
    unsigned char mBitset[0x1f8 - 0x1b8];
    int mPrevIndex;                 // +0x1f8
    int mNextIndex;                 // +0x1fc
    int mChildFirst;                // +0x204
    int mChildCount;                // +0x208
    unsigned char pad4[0x348 - 0x20c];
    float mPosX;                    // +0x344
    float mPosY;                    // +0x348
    float mPosZ;                    // +0x34c
    float mAttX;                    // +0x350
    float mAttY;                    // +0x354
    float mAttZ;                    // +0x358
    unsigned char pad6[0x368 - 0x35c];
    float mLen;                     // +0x368
    float mScale;                   // +0x36c
    unsigned char mJiggle;          // +0x370
    unsigned char pad7[0x3];
    float mAvgSegLen;               // +0x374
};
}
namespace nSPCreatureAnim {
struct Solver {
    unsigned char pad0[0x10c];
    float mOffsetX;                 // +0x10c
    float mOffsetY;                 // +0x110
    float mOffsetZ;                 // +0x114
    unsigned char pad1[0x2c];       // +0x118 .. 0x144
    float mParentOffX;              // +0x144
    float mParentOffY;              // +0x148
    float mParentOffZ;              // +0x14c
    unsigned char mFlags150;        // +0x150
    unsigned char pad2[0x3];
    unsigned char mFlags154;        // +0x154
    unsigned char pad3[0x1f8 - 0x155];
    int mPrevIndex;                 // +0x1f8
    int mNextIndex;                 // +0x1fc
    unsigned char pad4[0x344 - 0x200];
    float mPosX;                    // +0x344
    float mPosY;                    // +0x348
    float mPosZ;                    // +0x34c
    float mAttX;                    // +0x350
    float mAttY;                    // +0x354
    float mAttZ;                    // +0x358
    float mVX;                      // +0x358?  (see ForceAdd)
    unsigned char pad5[0x368 - 0x360];
    float mSizeA;                   // +0x368
    float mSizeB;                   // +0x36c
    unsigned char mJiggle;          // +0x370
    unsigned char pad6[0x3];
    float mAvgSegLen;               // +0x374
    unsigned char pad7[0x384 - 0x378];
    Bone* mBones;                   // +0x384
    Bone* mBonesEnd;                // +0x388
    unsigned char pad8[0x3ac - 0x38c];
    int mRootIndex;                 // +0x3ac
    unsigned char pad9[0x3c8 - 0x3b0];
    int mUseDirect;                 // +0x3c8
    int* mOrderPairs;               // +0x3cc (pairs of {Bone*, int})
    int* mOrderPairsEnd;            // +0x3d0
    unsigned char pad10[0x3e0 - 0x3d4];
    int mFlaggedCount;              // +0x3e0

    float DistX(int i0, int i1, float k);
    float DistY(int i0, int i1, float k);
    float SqX(float k, int i0, int i1);
    float SqY(float k, int i0, int i1);
    float SegmentLengthSum(Bone* b);
    float AverageSegment();
    void  MarkDeepBones();
    int   IsDeeperRatio(Bone** a, Bone** b);
    int   FindMinIndex(int* from, int* to);
    void  SortRange(int* a, int* b);
    void  SortFlaggedRuns();
    void  ShutdownAnims();
    void  UpdateAvgSegLen();
    void  BuildOrderPairs();
    float SegmentLengthSum2(Bone* b);
};
}
using nSPCreatureAnim::Solver;
using nSPCreatureAnim::Bone;
static inline float fsq(float v) { return v * v; }
// ---- items of slice s009b4e00 end

// ---- items of slice s009b8720 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int DAT_014470a0;      // 0x014470a0  (double 1e-08)
extern "C" int DAT_01485720;      // 0x01485720  (_HK_REAL_ONE = 1.0f)
extern "C" int DAT_014853e0;      // 0x014853e0  (float 2.0f)
extern "C" int DAT_015509f8;      // 0x015509f8  (float)
extern "C" int DAT_01550b18;      // 0x01550b18  (float eps)
extern "C" int DAT_01550d64;      // 0x01550d64  (float)
extern "C" int DAT_01448874;      // 0x01448874  (float 1e-06f)
extern "C" int DAT_013eb960;      // 0x013eb960  (float 0.01f)
extern "C" int DAT_01485544;      // 0x01485544  (0.75f)
extern "C" int DAT_014471fc;      // 0x014471fc  (0.0f)
extern "C" int DAT_01550d6c;      // 0x01550d6c  (float)
extern "C" int DAT_01550d68;      // 0x01550d68  (float)
extern "C" int DAT_01550d70;      // 0x01550d70  (float)
extern "C" int DAT_01550d74;      // 0x01550d74  (float)
extern "C" int DAT_01550d78;      // 0x01550d78  (float)
extern "C" int DAT_01550d08;      // 0x01550d08  (float)
extern "C" int DAT_01550d0c;      // 0x01550d0c  (float)
extern "C" int DAT_01550d10;      // 0x01550d10  (float)
extern "C" int DAT_01550d14;      // 0x01550d14  (float)
extern "C" int DAT_01550d18;      // 0x01550d18  (float)
extern "C" int DAT_01550d1c;      // 0x01550d1c  (float)
extern "C" int DAT_01550d20;      // 0x01550d20  (float)
extern "C" int DAT_01550d24;      // 0x01550d24  (float)
extern "C" int DAT_01550d28;      // 0x01550d28  (float)
extern "C" int DAT_015509e0;      // 0x015509e0
extern "C" int DAT_015509ec;      // 0x015509ec
void  __fastcall FUN_0099c4a0(int this_, int dummy, int a, int b, float c, float d); // 0x0099c4a0
void  __fastcall Bone_IntegrateVelocity(int this_, int dummy, float f, float* a, float* b); // 0x009b5ab0
int   __fastcall FUN_00c37030(int this_);                          // 0x00c37030  (GetFootprintRadius)
int   __fastcall FUN_009d3530(int this_);                          // 0x009d3530
float __fastcall FUN_009ce700(float x);                            // 0x009ce700
void  __fastcall FUN_009d00a0(int this_, int dummy, void* out, void* param); // 0x009d00a0
void  __fastcall FUN_009b3970(void* p);                            // 0x009b3970
namespace nSPCreatureAnim {
struct vector_3 { float x, y, z; };
}
namespace nSPCreatureAnim {
struct SpatialObject {
    uint32_t _00[0x1c/4];                               // 0x000
    float    orient_w;                                  // 0x01c orientation.w
    float    extent_lower_z;                            // 0x020 original-local lower.z
    uint32_t _24;                                       // 0x024
    float    extent_lower_x;                            // 0x028 original-local lower.x
    float    extent_upper_x;                            // 0x02c original-local upper.x
};
}
namespace nSPCreatureAnim {
struct Obj2;                                            // the creature instance (this slice)
}
namespace nSPCreatureAnim {
struct AniDyn;                                          // 0x15b8
}
namespace nSPCreatureAnim {
struct GaitGroup;
}
namespace nSPCreatureAnim {
struct BoneGoal;
}
namespace nSPCreatureAnim {
struct Vector30 { void* begin; void* end; };            // elements are 0x30 bytes
}
namespace nSPCreatureAnim {
struct Vector104 { void* begin; void* end; };           // elements are 0x104 bytes
}
namespace nSPCreatureAnim {
struct Vector108 { void* begin; void* end; };           // elements are 0x108 bytes
}
namespace nSPCreatureAnim {
struct GaitGroup {                                      // stride 0x108
    float    vx, vy, vz;                                // 0x000 desired velocity
    uint32_t _0c[6];                                    // 0x00c
    uint32_t f24_0[9];                                  // 0x024 integration scratch (float[9])
    uint32_t i44;                                       // 0x044
    uint32_t i48;                                       // 0x048
    float    f4c;                                       // 0x04c
    float    f50;                                       // 0x050
    float    f54;                                       // 0x054
    int      i58;                                       // 0x058 bone index
    uint32_t pad_05c[0x108/4 - 0x5c/4];                 // 0x05c..0x108
};
}
namespace nSPCreatureAnim {
struct BoneGoal {                                       // stride 0x104
    uint32_t f00_0[0x100/4];                            // 0x000
    float    f100;                                      // 0x100
    void     FUN_009d63e0(float t);                     // 0x009d63e0
};
}
namespace nSPCreatureAnim {
struct GoalBone {                                       // stride 0x2bc
    uint32_t _00[0x38/4];                               // 0x000
    bool     flag_38;                                   // 0x038
    uint8_t  pad_039[0x0f];                             // 0x039..0x048
    float    f48;                                       // 0x048
    uint32_t _4c[0x30/4];                               // 0x04c..0x07c
    float    cur_x;                                     // 0x07c current pose
    float    cur_y;                                     // 0x080
    float    cur_z;                                     // 0x084
    uint32_t pad_088[0x108/4];                          // 0x088..0x190
    float    goal_x;                                    // 0x190 goal pose
    float    goal_y;                                    // 0x194
    float    goal_z;                                    // 0x198
    uint32_t tail[0x124/4];                             // 0x19c..0x2bc
};
}
namespace nSPCreatureAnim {
struct BoneHandle {
    uint32_t _00[0x1c/4];                               // 0x000
    void     FUN_0099c4a0(int a, int b, float c, float d); // 0x0099c4a0
};
}
namespace nSPCreatureAnim {
struct BoneInst {                                       // stride 0x2bc
    uint32_t   _00[0x4c/4];                             // 0x000
    float      f4c;                                     // 0x04c
    uint32_t   _50[0x50/4];                             // 0x050
    BoneHandle hA0;                                     // 0x0a0
    uint32_t   tail[0x200/4];                           // 0x0bc..0x2bc
    void       Bone_IntegrateVelocity(float f, float* a, float* b); // 0x009b5ab0
};
}
namespace nSPCreatureAnim {
struct GaitState {                                      // 0x2f8
    int    state;                                       // 0x000
    int    prev;                                        // 0x004
    float  f08;                                         // 0x008
    float  f0c;                                         // 0x00c
    uint32_t _10[10];                                   // 0x010
    void*  p38;                                         // 0x038
    void*  p3c;                                         // 0x03c
    float  FUN_009dbd50();                              // 0x009dbd50
};
}
namespace nSPCreatureAnim {
struct AniDyn {                                         // receiver of the 0x9d3xxx helpers
    uint32_t _00[0xa8/4];                               // 0x000..0x0a8

    int*   FUN_009d3200(void* p, float f);              // 0x009d3200
    void   FUN_009d32d0();                              // 0x009d32d0
    void   FUN_009d3f70(Obj2* p);                       // 0x009d3f70
    float  FUN_009d3a20(Obj2* p, float a, int x, float b); // 0x009d3a20
    void   FUN_009d3b50(float t);                       // 0x009d3b50
    void   FUN_009d6700(float t);                       // 0x009d6700
    Vector108* FUN_00a09f50();                          // 0x00a09f50 gait-group vector
    Vector30*  FUN_00ad2800();                          // 0x00ad2800
    Vector104* GetPoliticalID();                        // 0x0097e850
    float  FUN_009d3530();                              // 0x009d3530
    float  FUN_009ce700(float x);                       // 0x009ce700
    void   FUN_009d00a0(float* out, void* phase);       // 0x009d00a0
    float* FUN_009b9340(float* out, int** a, SpatialObject* s, float dt); // 0x009b9340
};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009b_8720 {
    // 0x000..0x058 : requested rot + scale + actual rot block
    uint32_t pad_000[6];                         // 0x000
    float    f_18;                               // 0x018
    float    f_1c;                               // 0x01c
    float    f_20;                               // 0x020
    uint32_t pad_024[6];                         // 0x024
    float    f_3c;                               // 0x03c
    float    f_40;                               // 0x040
    float    f_44;                               // 0x044
    float    f_48;                               // 0x048
    float    f_4c;                               // 0x04c
    float    f_50;                               // 0x050
    float    f_54;                               // 0x054
    float    f_58;                               // 0x058
    uint32_t pad_05c[5];                         // 0x05c
    float    requested_scale;                    // 0x070
    uint32_t pad_074[6];                         // 0x074
    float    f_8c;                              // 0x08c
    float    f_90;                              // 0x090
    float    f_94;                              // 0x094
    uint32_t pad_098[26];                        // 0x098
    float    f_100;                              // 0x100
    float    f_104;                              // 0x104
    float    f_108;                              // 0x108
    float    f_10c;                              // 0x10c
    uint32_t pad_110[11];                        // 0x110
    float    f_13c;                              // 0x13c
    float    f_140;                              // 0x140
    float    f_144;                              // 0x144
    uint32_t pad_148;                            // 0x148
    float    f_14c;                              // 0x14c
    float    f_150;                              // 0x150
    float    f_154;                              // 0x154
    float    f_158;                              // 0x158
    uint32_t pad_15c;
    float    f_160;                              // 0x160
    uint32_t pad_164[7];
    float    f_180;                              // 0x180
    float    f_184;                              // 0x184
    float    f_188;                              // 0x188
    float    f_18c;                              // 0x18c
    float    f_190;                              // 0x190
    float    f_194;                              // 0x194
    float    f_198;                              // 0x198
    float    f_19c;                              // 0x19c
    float    f_1a0;                              // 0x1a0
    uint32_t pad_1a4[47];                        // 0x1a4
    bool     flag_260;                           // 0x260
    char     flag_261;                           // 0x261
    uint16_t pad_262;                            // 0x262
    float    walk_linear_x;                      // 0x264
    float    walk_linear_y;                      // 0x268
    float    walk_angular;                       // 0x26c
    uint32_t pad_270[0x74/4];                    // 0x270..0x2e4
    int*     mpBone_2e4;                         // 0x2e4
    uint32_t pad_2e8[0x10/4];                    // 0x2e8..0x2f8
    GaitState gait_2f8;                          // 0x2f8
    uint32_t pad_338[0x1280/4];                  // 0x338..0x15b8
    AniDyn   anim_15b8;                          // 0x15b8
    uint32_t pad_1600[0x60/4];                   // 0x1600..0x1660
    float    accum_1660;                         // 0x1660 root motion delta
    float    accum_1664;
    float    accum_1668;
    float    accum_166c;
    vector_3 root_1670;                          // 0x1670
    float    root_167c;
    bool     flag_1680;                          // 0x1680

    void FUN_009b8250(float param_2);            // 0x009b8250
    void FUN_009b83b0(float param_2);            // 0x009b83b0
    void FUN_009b8650(float param_2);            // 0x009b8650
    void FUN_009b7da0(float param_2);            // 0x009b7da0
    void FUN_009b7c00(float param_2, float* param_3, float param_4); // 0x009b7c00

    // this slice
    void FUN_009b8720(float param_2);            // 0x009b8720
    void FUN_009b8760(float param_2);            // 0x009b8760
    void FUN_009b8d50(float param_2);            // 0x009b8d50
    void FUN_009b8e40(float param_2);            // 0x009b8e40
    void FUN_009b8f40(float param_2);            // 0x009b8f40
    void FUN_009b8fd0(float* out_a, float* out_b); // 0x009b8fd0
    void FUN_009b9090();                         // 0x009b9090
    float* FUN_009b9250(float* out, float* p);   // 0x009b9250
};
}
using nSPCreatureAnim::creature_instance_data_s009b_8720;
using nSPCreatureAnim::AniDyn;
using nSPCreatureAnim::SpatialObject;
// ---- items of slice s009b8720 end

// ---- items of slice s009b95d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_1485720;  // 1.0f               0x01485720
extern const float g_1550d2c;  // quat w             0x01550d2c
extern const float g_1550d30;  // quat x             0x01550d30
extern const float g_1550d34;  // quat y             0x01550d34
extern const float g_1550d38;  // angle scale        0x01550d38
extern const float g_1550d14;  // axis x             0x01550d14
extern const float g_1550d18;  // axis y             0x01550d18
extern const float g_1550d1c;  // axis z             0x01550d1c
extern const float g_1550d04;  // clamp high         0x01550d04
extern const float g_1550d7c;  // scale x            0x01550d7c
extern const float g_1550d80;  // scale y            0x01550d80
extern const float g_1550d84;  // scale z            0x01550d84
extern int g_15509e4;          // root-update enable 0x015509e4
extern int g_15509e8;          // extra-update enable 0x015509e8
void* __cdecl FUN_009b9250(void* q);                                     // 0x009b9250
void* __cdecl FUN_009b9340(void* out, int inst, int b, float scale);     // 0x009b9340
float __cdecl FUN_009b3110(void* p);                                     // 0x009b3110
void  __cdecl FUN_009b39e0(float v);                                     // 0x009b39e0
void  __cdecl FUN_0099cae0(void* out, void* in, int mode);               // 0x0099cae0 quat normalize
int   __cdecl FUN_009d0460(void* out, float a);                          // 0x009d0460
double __cdecl FUN_009d3530(void* g);                                    // 0x009d3530
double __cdecl FUN_009ce700(void* g);                                    // 0x009ce700
void  __cdecl FUN_009d0a40(void* out, void* obj);                        // 0x009d0a40
int   __cdecl FUN_00ff3ba0(void* h);                                     // 0x00ff3ba0
int   __cdecl GetPoliticalID(void* g);                                   // 0x0097e850
float __cdecl GetFootprintRadius(void* o);                               // 0x00c37030
void __cdecl FUN_009b95d0(void* a, int b, int c, float d);
void __cdecl FUN_009b9ac0(void* a, int b, int c);
struct Body {
    unsigned char pad0[0x7c];
    float mVelX;                    // +0x7c
    float mVelY;                    // +0x80
    float mVelZ;                    // +0x84
    float mVelW;                    // +0x88
    float mRadX;                    // +0x8c
    float mRadY;                    // +0x90
    float mRadZ;                    // +0x94
    float mRadW;                    // +0x98
    float mBlend;                   // +0x9c
    float mScaleX;                  // +0xa0
    float mScaleY;                  // +0xa4
    float mScaleZ;                  // +0xa8
};
struct Quat { float x, y, z, w; };
static inline Quat qmul(const Quat& a, const Quat& b)
{
    Quat r;
    r.x = ((a.x * b.w + a.w * b.x) - a.y * b.z) + a.z * b.y;
    r.y = ((a.y * b.w + a.w * b.y) + a.z * b.x) - a.x * b.z;
    r.z = ((a.z * b.w - a.y * b.x) + a.x * b.y) + a.w * b.z;
    r.w = ((a.w * b.w - a.x * b.x) - a.y * b.y) - a.z * b.z;
    return r;
}
// ---- items of slice s009b95d0 end

// ---- items of slice s009bb360 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double fmod(double, double);
#pragma intrinsic(fmod)
namespace checkerlib {
class vector_3_s009b_b360 { public:
    float x, y, z;
    vector_3_s009b_b360() {}
    vector_3_s009b_b360(const vector_3_s009b_b360& o) : x(o.x), y(o.y), z(o.z) {}
    vector_3_s009b_b360& operator=(const vector_3_s009b_b360& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
}
namespace checkerlib {
class vector_4_s009b_b360 { public: float x, y, z, w; };
}
using checkerlib::vector_3_s009b_b360;
using checkerlib::vector_4_s009b_b360;
namespace nSPCreatureAnim {
struct creature_static_data_s009b_b360 {
    uint32_t pad000[0x3f4 / 4];
    uint8_t  dead;                        // +0x3f4 (disables the wiggle springs)
    uint8_t  pad3f5[3];
};
}
namespace nSPCreatureAnim {
struct goal_def_s009b_b360 {                         // only +0x00 is read here
    unsigned long bidx;                   // +0x00
};
}
namespace nSPCreatureAnim {
struct goal_state_s009b_b360 {                       // size 0x2c
    goal_def_s009b_b360* def;                        // +0x00
    bool      initialized;                // +0x04
    bool      reset;                      // +0x05
    uint8_t   pad06[2];
    vector_3_s009b_b360  vel;                        // +0x08
    vector_3_s009b_b360  pos;                        // +0x14
    vector_3_s009b_b360  prev;                       // +0x20
};
}
namespace nSPCreatureAnim {
struct creature_body_instance_data_s009b_b360 {      // size 0x2bc; only ->pos (+0x10) is read here
    uint32_t pad000[0x10 / 4];
    vector_3_s009b_b360 pos;                         // +0x010
    uint32_t pad01c[(0x2bc - 0x1c) / 4];
};
}
namespace nSPCreatureAnim {
struct body_vector_s009b_b360 {                      // eastl::vector<creature_body_instance_data>
    creature_body_instance_data_s009b_b360* mpBegin;     // +0x2e4
    creature_body_instance_data_s009b_b360* mpEnd;
    creature_body_instance_data_s009b_b360* mpCapacity;
    uint32_t mAllocator;
};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009b_b360 {
    creature_static_data_s009b_b360* static_data;    // +0x000
    uint32_t pad004[(0x18 - 0x4) / 4];
    vector_3_s009b_b360 position;                    // +0x018
    uint32_t pad024[(0x3c - 0x24) / 4];
    vector_4_s009b_b360 orientation;                 // +0x03c
    uint32_t pad04c[(0x2e4 - 0x4c) / 4];
    body_vector_s009b_b360 Bodies;                   // +0x2e4
    uint32_t pad2f4[(0x168c - 0x2f4) / 4];
    uint8_t  pad168c[2];
    uint8_t  wiggles_enabled;             // +0x168e
    uint8_t  pad68f[1];
    float    wiggle_timer;                // +0x1690
    goal_state_s009b_b360* states_begin;             // +0x1694
    goal_state_s009b_b360* states_end;               // +0x1698
    uint32_t states_capacity;             // +0x169c
    uint32_t pad6a0[(0x16a8 - 0x16a0) / 4];
    float    hit_time;                    // +0x16a8
    float    root_time;                   // +0x16ac
    float    hold_time;                   // +0x16b0
    vector_3_s009b_b360 hit_dir;                     // +0x16b4
    float    hit_len;                     // +0x16c0
    uint32_t hit_wiggle[0x3c / 4];        // +0x16c4 (opaque instance, CreateWiggle)
    goal_state_s009b_b360 hit_goal;                  // +0x1700
    uint32_t pad172c[(0x1768 - 0x172c) / 4];
    goal_state_s009b_b360 root_goal;                 // +0x1768

    void UpdateGoalSpring(goal_state_s009b_b360* st, int nSteps, float dt, float t, float rate); // 0x009ba990
    void UpdateHitWiggles(int nSteps, float dt, float t, float rate);
    void UpdateWiggles(float dt, float t);  // 0x009bb4f0 (nSPCreatureAnim::creature_instance_data::UpdateWiggles)
    void HitBody(unsigned long bidx, const vector_3_s009b_b360& dir, uint32_t a3, bool a4, float a5);  // 0x009bb680 (nSPCreatureAnim::creature_instance_data::HitBody)
};
}
namespace nSPCreatureAnim {
extern float g_01550ab4;   // 0x01550ab4 wiggle timer clamp
}
namespace nSPCreatureAnim {
extern float g_01550c30;   // 0x01550c30 wiggle tick interval
}
namespace nSPCreatureAnim {
extern float g_0166c018;   // 0x0166c018 hit-wiggle fade window
}
// ---- items of slice s009bb360 end

// ---- items of slice s009be260 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct V3_s009b_e260 { float x, y, z; };
struct V4 { float x, y, z, w; };
struct AnimDesc {                       // *slot : creature animation descriptor
    uint32_t pad0[0x10c / 4];           // 0x00..0x10b
    float scaleX, scaleY, scaleZ;       // 0x10c..0x114
    V4 tint;                            // 0x118..0x127
};
struct BoneSlot {                       // 700 bytes
    AnimDesc* desc;                     // 0x00
    uint32_t pad04[3];                  // 0x04..0x0f
    V3_s009b_e260 pos;                             // 0x10
    V4 tint;                            // 0x1c
    V3_s009b_e260 zero;                            // 0x2c
    uint8_t flag38;                     // 0x38
    uint8_t pad39[3];
    V3_s009b_e260 pos2;                            // 0x3c
    uint8_t pad48[0x2bc - 0x48];
};
struct CreatureAnim {
    uint32_t pad00[6];                  // 0x00..0x17
    V3_s009b_e260 a18;                             // 0x18
    V3_s009b_e260 b24;                             // 0x24
    V3_s009b_e260 c30;                             // 0x30
    V4 d3c;                             // 0x3c
    V4 e4c;                             // 0x4c
    V4 f5c;                             // 0x5c
    float g6c;                          // 0x6c
    float h70;                          // 0x70
    V3_s009b_e260 i74;                             // 0x74
    V3_s009b_e260 j80;                             // 0x80
    V3_s009b_e260 k8c;                             // 0x8c
    V3_s009b_e260 l98;                             // 0x98
    V3_s009b_e260 ma4;                             // 0xa4
    V3_s009b_e260 nb0;                             // 0xb0
    V3_s009b_e260 obc;                             // 0xbc
    V3_s009b_e260 pc8;                             // 0xc8
    float qd4;                          // 0xd4
    uint8_t padD8[0x2e4 - 0xd8];
    uint8_t* slotsBegin;                // 0x2e4
    uint8_t* slotsEnd;                  // 0x2e8
};
static void InitSlot(BoneSlot* s, float t) {
    s->pos.x = s->desc->scaleX * t;
    s->pos.y = s->desc->scaleY * t;
    s->pos.z = s->desc->scaleZ * t;
    s->pos2.x = s->pos.x;
    s->pos2.y = s->pos.y;
    s->pos2.z = s->pos.z;
    s->tint.x = s->desc->tint.x;
    s->tint.y = s->desc->tint.y;
    s->tint.z = s->desc->tint.z;
    s->tint.w = s->desc->tint.w;
    s->zero.x = 0.0f;
    s->zero.y = 0.0f;
    s->zero.z = 0.0f;
    s->flag38 = 1;
}
struct BodyVertex28 { int a; int b; float f[8]; };
struct Matrix30 { float f[12]; };
struct WiggleInstance {
    const void* static_data;            // 0x00
    bool enabled;                       // 0x04
    bool force_override;                // 0x05
    V3_s009b_e260 world_vel;                       // 0x08
    V3_s009b_e260 world_pos;                       // 0x14
    V3_s009b_e260 world_pos_old;                   // 0x20
};
struct Blob12 { int d[12]; };
struct Copy108 {                        // 0x009befa0: tail unrolled
    int i[4];                           // 0x00..0x0c
    float a[28];                        // 0x10..0x7c
    float b[5];                         // 0x80..0x90
    int m;                              // 0x94
    float c[13];                        // 0x98..0xc8
    int j[3];                           // 0xcc..0xd4
    int k[12];                          // 0xd8..0x104
    int n;                              // 0x108
    Copy108& operator=(const Copy108& o);
};
struct Copy108c {                       // 0x009be850: tail is one block (rep movsd)
    int i[4];                           // 0x00..0x0c
    float a[28];                        // 0x10..0x7c
    float b[5];                         // 0x80..0x90
    int m;                              // 0x94
    float c[13];                        // 0x98..0xc8
    int j[3];                           // 0xcc..0xd4
    Blob12 k;                           // 0xd8..0x104
    int n;                              // 0x108
    Copy108c& operator=(const Copy108c& o);
};
struct Sub18c {                         // 0x18c..0x27f (0xf4), copied by 0x009b45b0
    uint8_t d[0xf4];
    void Init(const Sub18c& o);
};
struct Blob41 { int d[41]; };           // 0xa0..0x143
struct Body2bc {
    int i00, i04, i08, i0c;             // 0x00..0x0c
    float f[10];                        // 0x10..0x34
    uint8_t b38;                        // 0x38
    uint8_t pad39[3];
    float g[3];                         // 0x3c..0x44
    int j[3];                           // 0x48..0x50
    uint8_t b54, b55;                   // 0x54,0x55
    uint8_t pad56[2];
    float h[18];                        // 0x58..0x9c
    Blob41 arr;                         // 0xa0..0x143
    int i144;                           // 0x144
    float p[17];                        // 0x148..0x188
    Sub18c sub;                         // 0x18c..0x27f
    float q[8];                         // 0x280..0x29c
    uint8_t b2a0;                       // 0x2a0
    uint8_t pad2a1[3];
    float r[6];                         // 0x2a4..0x2b8

    Body2bc(const Body2bc& o);
};
// ---- items of slice s009be260 end

// ---- items of slice s009bf210 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct V3_s009b_f210 { float x, y, z; };
struct Sub18cF {                        // same layout, different copy routine
    uint8_t d[0xf4];
    void Init(const Sub18cF& o);        // -> 0x009b45d0 (009bf210 flavour)
    void Reset();                       // -> 0x009b2e50 (009bf680)
};
struct Body2bcF {
    int i00, i04, i08, i0c;             // 0x00..0x0c
    float f[10];                        // 0x10..0x34
    uint8_t b38;                        // 0x38
    uint8_t pad39[3];
    float g[3];                         // 0x3c..0x44
    float j3[3];                        // 0x48..0x50   (floats in this flavour)
    uint8_t b54, b55;                   // 0x54,0x55
    uint8_t pad56[2];
    float h[18];                        // 0x58..0x9c
    Blob41 arr;                         // 0xa0..0x143
    int i144;                           // 0x144
    float p[17];                        // 0x148..0x188
    Sub18cF sub;                        // 0x18c..0x27f
    float q[8];                         // 0x280..0x29c
    uint8_t b2a0;                       // 0x2a0
    uint8_t pad2a1[3];
    float r[6];                         // 0x2a4..0x2b8

    Body2bcF(const Body2bcF& o);
};
struct BodyAnimC {
    uint8_t pad00[0x10];
    V3_s009b_f210 a;                               // 0x10
    V3_s009b_f210 b;                               // 0x1c
    float c;                            // 0x28
    V3_s009b_f210 d;                               // 0x2c
    int unk38;                          // 0x38 (untouched)
    V3_s009b_f210 e;                               // 0x3c
    uint8_t pad48[0x10];                // 0x48..0x57 (untouched)
    float f[18];                        // 0x58..0x9c
    int g;                              // 0xa0
    uint8_t padA4[0x148 - 0xa4];
    V3_s009b_f210 h;                               // 0x148
    float i;                            // 0x154
    V3_s009b_f210 j;                               // 0x158
    V3_s009b_f210 k;                               // 0x164
    V3_s009b_f210 l;                               // 0x170
    V3_s009b_f210 m;                               // 0x17c
    float n;                            // 0x188
    Sub18cF sub;                        // 0x18c..0x27f
    V3_s009b_f210 o;                               // 0x280
    V3_s009b_f210 p;                               // 0x28c
    float q;                            // 0x298
    uint8_t pad29c[8];                  // 0x29c..0x2a3
    V3_s009b_f210 r;                               // 0x2a4
    V3_s009b_f210 s;                               // 0x2b0
    void Finalize();                    // -> 0x009b5a00

    BodyAnimC();
};
struct WiggleElem {
    uint8_t pad000[0x10c];
    V3_s009b_f210 pos;                             // 0x10c
    uint8_t pad118[0x150 - 0x118];
    unsigned flags;                     // 0x150
    uint8_t pad154[0x1f8 - 0x154];
    int link1;                          // 0x1f8
    uint8_t pad1fc[0x204 - 0x1fc];
    int first;                          // 0x204  first dependent node
    int count;                          // 0x208  number of dependents
    uint8_t pad20c[0x430 - 0x20c];
    int link2;                          // 0x430
    float dist;                         // 0x434
    float span;                         // 0x438
    float gap;                          // 0x43c
    int root;                           // 0x440  -1 none, -2 merged, -3 orphan
    int other;                          // 0x444
};
struct WiggleAnim {
    uint8_t pad000[0x384];
    WiggleElem* beg;                    // 0x384
    WiggleElem* end;                    // 0x388
    uint8_t pad38c[0x3e4 - 0x38c];
    float maxDist;                      // 0x3e4
    float maxDist2;                     // 0x3e8

    void Prep();                        // -> 0x009b4ce0
    void Recompute();                   // -> 0x009bf860
    float Weight(WiggleElem* e);        // -> 0x009b5200
    void Walk();                        // -> 0x009bfa20
};
float g_eps = 1e-6f;                    // -> 0x014471fc
void FUN_009b4ef0(void* p);             // -> 0x009b4ef0, cdecl pointer arg
// ---- items of slice s009bf210 end

// ---- items of slice s009c0f60 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8_s009c_0f60;
typedef unsigned int u32_s009c_0f60;
typedef unsigned short u16;
void* operator_new(size_t n, const char* name, int flags, int align,
                   const char* file, int line);
void operator_delete__(void* p);
#define EASTL_NEW(n) operator_new((n), "EASTL", 0, 0, \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
#define EASTL_FREE(p) do { \
    if ((p) != 0 && *(int*)((u8_s009c_0f60*)(p) - 4) != 0) operator_delete__(p); \
} while (0)
void  FUN_009b3c80(void* p);                       // destroy / move slot (0x30)
void  FUN_009b47f0(void* dst, void* first, void* last);
void* FUN_009b4290(void* first, void* last, void* dst);
void  FUN_009b3ab0(void* p);                       // destroy / copy slot (0x3c)
void  FUN_009b4870(void* dst, void* first, void* last);
void* FUN_009b4350(void* first, void* last, void* dst);
void  FUN_009b41e0(const void* value);             // copy to a temporary slot
void* FUN_009b4910(void* first, void* last, void* dst);
void  FUN_009b44e0(void* dst, unsigned n, const void* value, void* at);
void  FUN_009b4ab0(void* dst, void* first, void* last);
void  FUN_009b4490(void* first, void* end, const void* temp);
void  FUN_009b4230(const void* value);
void* FUN_009b4990(void* first, void* last, void* dst);
void  FUN_009b4b10(void* dst, void* first, void* last);
void  FUN_009bef30(void* dst, unsigned n, const void* value, void* at);
void  FUN_009beec0(void* first, void* last, const void* src);
void  FUN_009be850(const void* value);             // 0x10c copy ctor / assign
void  FUN_009bedb0(void* out, void* first, void* last, void* dst);
void  FUN_009bf600(void* dst, void* first, void* last);
void  FUN_009c0d40(void* first, void* end, const void* temp);
void  FUN_009bea50(const void* value);             // 700-byte copy ctor / assign
void  FUN_009bedf0(void* out, void* first, void* last, void* dst);
void  FUN_009bf640(void* dst, void* first, void* last);
void  FUN_009c0d70(void* first, void* end, const void* temp);
void* FUN_009bf500(void* first, void* last, void* dst);
void* FUN_009bf580(void* first, void* last, void* dst);
void  FUN_009c0aa0(void* dst, unsigned n, const void* value);
void  FUN_009c0ad0(void* dst, unsigned n, const void* value);
void  FUN_009b4310(void* dst, void* first, void* last);
void  FUN_009b43f0(void* dst, void* first, void* last);
void  RBTreeInsert(void* node, void* key, void* root, u32_s009c_0f60 reuse);
void  FUN_00a22220(u32_s009c_0f60 n);                         // hash_table::Rehash
static unsigned grow_count(unsigned have) {
    return have == 0 ? 1 : have * 2;
}
struct Vec30 {
    u8_s009c_0f60* begin;
    u8_s009c_0f60* end;
    u8_s009c_0f60* cap;

    void Insert(u8_s009c_0f60* pos, u8_s009c_0f60* value);                            // 009c0f60
    void InsertFill(u8_s009c_0f60* pos, unsigned n, const void* value);    // 009c11e0
};
struct Vec3c {
    u8_s009c_0f60* begin;
    u8_s009c_0f60* end;
    u8_s009c_0f60* cap;

    void Insert(u8_s009c_0f60* pos, u8_s009c_0f60* value);                            // 009c10c0
};
struct Vec44 {
    u8_s009c_0f60* begin;
    u8_s009c_0f60* end;
    u8_s009c_0f60* cap;

    void InsertFill(u8_s009c_0f60* pos, unsigned n, const void* value);    // 009c13a0
};
struct Vec10c {
    u8_s009c_0f60* begin;
    u8_s009c_0f60* end;
    u8_s009c_0f60* cap;

    void InsertFill(u8_s009c_0f60* pos, unsigned n, const void* value);    // 009c1790
};
struct Vec700 {
    u8_s009c_0f60* begin;
    u8_s009c_0f60* end;
    u8_s009c_0f60* cap;

    void InsertFill(u8_s009c_0f60* pos, unsigned n, const void* value);    // 009c1980
};
struct HTable {
    u32_s009c_0f60 bucketCount;                    // 0x00
    void* buckets;                      // 0x04
    u32_s009c_0f60 pad08;                          // 0x08
    u32_s009c_0f60 elementCount;                   // 0x0c
    float loadFactor;                   // 0x10
    float growthFactor;                 // 0x14
    void* freeList;                     // 0x18

    void DoInsertValue(void** out, void* key, u32_s009c_0f60* value, char reuse);   // 009c1560
};
extern "C" void fixed_pool_base_init(void* pool, void* begin, u32_s009c_0f60 size,
                                     u32_s009c_0f60 nodeSize, u32_s009c_0f60 alignment, u32_s009c_0f60 flags);
void* FUN_00921340(u32_s009c_0f60 n);
u32_s009c_0f60   FUN_009213c0(u32_s009c_0f60 n);
void* FUN_009c09c0(void* node, void* a, void* b, void* c, void* d, void* e,
                   void* pool);
struct BoolVec {
    u8_s009c_0f60* begin;                          // 0x00
    u8_s009c_0f60* end;                            // 0x04
    u8_s009c_0f60* cap;                            // 0x08
    u8_s009c_0f60* storage;                        // 0x0c  inline buffer
    u8_s009c_0f60* storageEnd;                     // 0x10

    void Insert(u8_s009c_0f60* pos, u8_s009c_0f60* first, u8_s009c_0f60* last);                  // 009c1b70
};
void* bool_insert_dispatch(void* at, void* first, long bytes);
struct AnimNode {                       // 0x468 bytes
    u8_s009c_0f60 pad000[0x150];
    u32_s009c_0f60 flags;                          // 0x150
    u8_s009c_0f60 pad154[0x440 - 0x154];
    int root;                           // 0x440
};
struct PendingRec {                     // 8-byte queue element
    AnimNode* node;
    char flag;
};
struct PendingQueue {                   // vector<{AnimNode*, char}> at +0x3cc
    PendingRec* begin;                  // 0x3cc
    PendingRec* end;                    // 0x3d0
    PendingRec* cap;                    // 0x3d4

    void Push(const PendingRec& value) {
        PendingRec* e = end;
        if (e < cap) {
            end = e + 1;
            if (e != 0) *e = value;
        } else {
            Grow(e, &value);
        }
    }
    void Grow(PendingRec* at, const PendingRec* value);   // -> 0x009a0c50
};
struct XformRec {                       // one inv_bone_rest_xforms entry
    u8_s009c_0f60 d[0x3c];
};
struct BodyVec {                        // vector<creature_body_static_data>, 0x468
    AnimNode* begin;
    AnimNode* end;
    AnimNode* cap;
};
struct XformVec {                       // vector<0x3c-byte record>
    XformRec* begin;
    XformRec* end;
    XformRec* cap;
};
struct Rgb3 {                           // one skin-colour triple
    float x1, x2, x3;
};
struct CreatureStaticData {
    u16   name[0x104];                          // 0x000
    char  filename[0x108];                      // 0x208
    u32_s009c_0f60   uid[2];                               // 0x310
    u32_s009c_0f60   type_id;                              // 0x318
    u32_s009c_0f60   group_id;                             // 0x31c
    u32_s009c_0f60   instance_id;                          // 0x320
    Rgb3  skin_colors[3];                       // 0x324
    u8_s009c_0f60    pad348[0x34c - 0x348];
    u8_s009c_0f60    BranchPredicates;                     // 0x34c
    u8_s009c_0f60    pad34d[0x350 - 0x34d];
    u32_s009c_0f60   f350;                                 // 0x350
    u32_s009c_0f60   f354;                                 // 0x354
    u8_s009c_0f60    pad358[0x374 - 0x358];
    float f374;                                 // 0x374
    int   num_bones_with_mesh_parts;            // 0x378
    u8_s009c_0f60    pad37c[0x380 - 0x37c];
    u8_s009c_0f60    f380;                                 // 0x380
    u8_s009c_0f60    pad381[0x384 - 0x381];
    BodyVec Bodies;                             // 0x384  vector<creature_body_static_data>
    u8_s009c_0f60    pad390[0x3ac - 0x390];
    int   mMaxStraightLegLength_Scalable;       // 0x3ac  stored as 0xffffffff
    int   mGear;                                // 0x3b0
    XformVec inv_bone_rest_xforms;              // 0x3b4  vector<0x3c-byte records>
    u8_s009c_0f60    pad3c0[0x3c8 - 0x3c0];
    u32_s009c_0f60   f3c8;                                 // 0x3c8
    PendingQueue pending;                       // 0x3cc  vector<{AnimNode*, char}>
    u8_s009c_0f60    pad3d8[0x3e0 - 0x3d8];
    u32_s009c_0f60   f3e0;                                 // 0x3e0
    u8_s009c_0f60    pad3e4[0x3ec - 0x3e4];
    float f3ec;                                 // 0x3ec  defaults to 4.0f
    u32_s009c_0f60   f3f0;                                 // 0x3f0
    u8_s009c_0f60    pad3f4[0x3f5 - 0x3f4];
    u8_s009c_0f60    f3f5;                                 // 0x3f5

    void CollectFlagged();                                          // 009c1d30
    void Clear(int unused);                                         // 009c1dc0
};
// ---- items of slice s009c0f60 end

// ---- items of slice s009c2ef0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8_s009c_2ef0;
typedef unsigned int u32_s009c_2ef0;
void FUN_009bf540(void* newEnd, void* first, void* last);      // 0x10c range destroy
void FUN_009bf5c0(void* newEnd, void* first, void* last);      // 700-byte range destroy
struct V3_s009c_2ef0 {                             // a checkerlib vector_3
    float x1, x2, x3;
};
struct PadFirst {                       // 0x1c bytes
    float a, b, c, d, e, f, g;
};
struct PadLast {                        // 0x84 bytes
    float a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w,
          x, y, z, aa, ab, ac, ad, ae, af, ag;
};
struct IkConstraint {                   // 0x10c bytes
    PadFirst p0;
    V3_s009c_2ef0 v0, v1, v2, v3, v4, v5, v6, v7, v8;   // 0x1c .. 0x88 -- reset to zero
    PadLast p1;
};
struct IKVec {                          // vector<ik_constraint>
    IkConstraint* begin;                // 0x00
    IkConstraint* end;                  // 0x04
    IkConstraint* cap;                  // 0x08

    void InsertFill(IkConstraint* pos, unsigned n, const IkConstraint* value);  // 0x009c1790
    void Resize(unsigned n);            // 009c2ef0
};
struct F25 { float a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v, w, x, y; };   // 100 bytes
struct BodyAnimC_s009c_2ef0 {                      // 0x2bc = 700 bytes; ctor 0x009bf680
    F25 p0, p1, p2, p3, p4, p5, p6;

    BodyAnimC_s009c_2ef0* Ctor();                  // 0x009bf680 -- returns this
};
struct WiggleVec {
    BodyAnimC_s009c_2ef0* begin;                   // 0x00
    BodyAnimC_s009c_2ef0* end;                     // 0x04
    BodyAnimC_s009c_2ef0* cap;                     // 0x08

    void InsertFill(BodyAnimC_s009c_2ef0* pos, unsigned n, const BodyAnimC_s009c_2ef0* value);  // 0x009c1980
    void Resize(unsigned n);            // 009c3040
};
struct BodyNode {                       // 0x468-byte creature_body_static_data
    u8_s009c_2ef0 pad000[0x204];
    unsigned prevCount;                 // 0x204
    unsigned count;                     // 0x208
    int      total;                     // 0x20c
    u8_s009c_2ef0 pad210[0x468 - 0x210];
};
struct AnimOwner {
    u8_s009c_2ef0 pad000[0x384];
    BodyNode* bodies;                   // 0x384
};
struct WordVec {                        // the dword-backed bit vector
    u32_s009c_2ef0* begin;                         // 0x00
    u32_s009c_2ef0* end;                           // 0x04
    u32_s009c_2ef0* cap;                           // 0x08

    void Insert(u32_s009c_2ef0* pos, u32_s009c_2ef0* first, u32_s009c_2ef0* last, void* owner);  // 0x009c1b70
};
int FUN_009c3150(AnimOwner* a, WordVec* v, u32_s009c_2ef0** base, unsigned idx);
struct FixedVec {
    void*     begin;                    // 0x00
    void*     end;                      // 0x04
    void*     cap;                      // 0x08
    void*     pad0c;                    // 0x0c
    u8_s009c_2ef0*       buf;                      // 0x10
    void*     pad14;                    // 0x14
    u8_s009c_2ef0        storage[0x3fc];           // 0x18

    FixedVec* Init(void* a, void* b);   // 009c3210 -- __thiscall, ret 8
    void      Setup(void* a, void* b);  // 0x009c30f0
};
struct PhaseGroup {                     // 0x104 bytes
    u8_s009c_2ef0 pad00[0x4c];
    void* subBegin;                     // 0x4c
    void* subEnd;                       // 0x50
    u8_s009c_2ef0 pad54[0xbc - 0x54];
    void* block;                        // 0xbc
    u8_s009c_2ef0 padc0[0x104 - 0xc0];
};
struct PhaseGroupVec {
    void* begin;                        // 0x00
    void* end;                          // 0x04
    void* cap;                          // 0x08

    void DestroyValues(PhaseGroup* first, PhaseGroup* last);   // 009c3240
};
// ---- items of slice s009c2ef0 end

// ---- items of slice s009c56c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct XBodySub { void Construct(); };                        // 0x009e3ec0
struct XGaitSub { void Construct(void* a, void* b); };        // 0x009c1630
struct creature_instance_data {
    char pad00[0x14];
    int  flags14;                       // +0x14
    char pad18[0x17b0 - 0x18];
    void Clear(bool);                   // 0x009c4d40
    creature_instance_data();
};
// ---- items of slice s009c56c0 end

// @ 0x009b3180
void __fastcall FUN_009b3180(void* self)
{ (void)self; }

// @ 0x009b3460
namespace nSPCreatureAnim {
int __cdecl FUN_009b3460(int obj)
{
  int i = *(int*)(*(int*)(obj + 0x214) + 0x210);
  if (i == 0) {
    i = FUN_009b3460(*(int*)(obj + 0x214));
    *(int*)(obj + 0x210) = i;
    return i;
  }
  *(int*)(obj + 0x210) = i;
  return i;
}
}  // namespace nSPCreatureAnim

// @ 0x009b3850
void __fastcall FUN_009b3850(void* self)
{ (void)self; }

// @ 0x009b3920
namespace nSPCreatureAnim {
void TargetFrame::Set(const float* a, const float* b)
{
  posA[0] = a[0];
  posA[1] = a[1];
  posA[2] = a[2];
  posB[0] = b[0];
  posB[1] = b[1];
  posB[2] = b[2];
  posB[3] = b[3];
}
}  // namespace nSPCreatureAnim

// @ 0x009b3970
void __fastcall FUN_009b3970(void* self)
{ (void)self; }

// @ 0x009b39e0
void __fastcall FUN_009b39e0(void* self)
{ (void)self; }

// @ 0x009b3ab0
namespace nSPCreatureAnim {
CopyBlock& CopyBlock::operator=(const CopyBlock& src)
{
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

// @ 0x009b3b20
void __fastcall FUN_009b3b20(void* self)
{ (void)self; }

// @ 0x009b3bc0
namespace nSPCreatureAnim {
void __cdecl FUN_009b3bc0(int obj)
{
  float* p = (float*)(obj + 0x118);
  for (int i = 0; i < 9; i++)
    p[i] = 0.0f;
}
}  // namespace nSPCreatureAnim

// @ 0x009b3c10
void __fastcall FUN_009b3c10(void* self)
{ (void)self; }

// @ 0x009b3c80
namespace nSPCreatureAnim {
Transform30& Transform30::operator=(const Transform30& src)
{
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
}  // namespace nSPCreatureAnim

// @ 0x009b3cd0
void __fastcall FUN_009b3cd0(void* self)
{ (void)self; }

// @ 0x009b3e40
nSPCreatureAnim::creature_body_static_data_s009b_3e40& nSPCreatureAnim::creature_body_static_data_s009b_3e40::operator=(const nSPCreatureAnim::creature_body_static_data_s009b_3e40& o)
{
    memcpy(name, o.name, 0x104);
    instance_id = o.instance_id;
    group_id = o.group_id;
    f10c[0] = o.f10c[0]; f10c[1] = o.f10c[1]; f10c[2] = o.f10c[2]; f10c[3] = o.f10c[3];
    f10c[4] = o.f10c[4]; f10c[5] = o.f10c[5]; f10c[6] = o.f10c[6]; f10c[7] = o.f10c[7];
    f10c[8] = o.f10c[8]; f10c[9] = o.f10c[9]; f10c[10] = o.f10c[10]; f10c[11] = o.f10c[11];
    f10c[12] = o.f10c[12]; f10c[13] = o.f10c[13]; f10c[14] = o.f10c[14]; f10c[15] = o.f10c[15];
    f10c[16] = o.f10c[16];
    memcpy(w150, o.w150, 0x2a * 4);
    w1f8[0] = o.w1f8[0]; w1f8[1] = o.w1f8[1]; w1f8[2] = o.w1f8[2]; w1f8[3] = o.w1f8[3];
    w1f8[4] = o.w1f8[4]; w1f8[5] = o.w1f8[5]; w1f8[6] = o.w1f8[6]; w1f8[7] = o.w1f8[7];
    w1f8[8] = o.w1f8[8]; w1f8[9] = o.w1f8[9];
    memcpy(w220, o.w220, 0x41 * 4);
    f324[0] = o.f324[0]; f324[1] = o.f324[1]; f324[2] = o.f324[2];
    f324[3] = o.f324[3]; f324[4] = o.f324[4]; f324[5] = o.f324[5];
    u33c = o.u33c;
    b340 = o.b340;
    f344[0] = o.f344[0]; f344[1] = o.f344[1]; f344[2] = o.f344[2]; f344[3] = o.f344[3];
    f344[4] = o.f344[4]; f344[5] = o.f344[5]; f344[6] = o.f344[6]; f344[7] = o.f344[7];
    f344[8] = o.f344[8]; f344[9] = o.f344[9]; f344[10] = o.f344[10];
    b370 = o.b370;
    b371 = o.b371;
    f374[0] = o.f374[0]; f374[1] = o.f374[1]; f374[2] = o.f374[2];
    memcpy(w380, o.w380, 0x29 * 4);
    u424 = o.u424;
    u428 = o.u428;
    b42c = o.b42c;
    u430 = o.u430;
    f434[0] = o.f434[0]; f434[1] = o.f434[1]; f434[2] = o.f434[2];
    u440 = o.u440;
    u444 = o.u444;
    f448[0] = o.f448[0]; f448[1] = o.f448[1]; f448[2] = o.f448[2]; f448[3] = o.f448[3];
    f448[4] = o.f448[4]; f448[5] = o.f448[5]; f448[6] = o.f448[6];
    b464 = o.b464;
    return *this;
}

// @ 0x009b41e0
nSPCreatureAnim::xform12& nSPCreatureAnim::xform12::operator=(const nSPCreatureAnim::xform12& o)
{
    m[0] = o.m[0]; m[3] = o.m[3]; m[6] = o.m[6];
    m[1] = o.m[1]; m[4] = o.m[4]; m[7] = o.m[7];
    m[2] = o.m[2]; m[5] = o.m[5]; m[8] = o.m[8];
    v[0] = o.v[0];
    v[1] = o.v[1];
    v[2] = o.v[2];
    return *this;
}

// @ 0x009b4230
nSPCreatureAnim::wiggle_instance_data_s009b_3e40& nSPCreatureAnim::wiggle_instance_data_s009b_3e40::operator=(const nSPCreatureAnim::wiggle_instance_data_s009b_3e40& o)
{
    wiggle = o.wiggle;
    flag4 = o.flag4;
    flag5 = o.flag5;
    f[0] = o.f[0]; f[1] = o.f[1]; f[2] = o.f[2]; f[3] = o.f[3]; f[4] = o.f[4];
    f[5] = o.f[5]; f[6] = o.f[6]; f[7] = o.f[7]; f[8] = o.f[8];
    return *this;
}

// @ 0x009b4290
nSPCreatureAnim::Transform30_s009b_3e40* CopyTransform30Guarded(nSPCreatureAnim::Transform30_s009b_3e40* first, nSPCreatureAnim::Transform30_s009b_3e40* last, nSPCreatureAnim::Transform30_s009b_3e40* result)
{
    for (; first != last; ++first, ++result)
        if (result) {
            result->a = first->a;
            result->b = first->b;
            float* d = result->f; float* s = first->f;
            d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
            d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8]; d[9] = s[9];
        }
    return result;
}

// @ 0x009b4350
nSPCreatureAnim::wiggle_static_data_s009b_3e40* CopyWigglesGuarded(nSPCreatureAnim::wiggle_static_data_s009b_3e40* first, nSPCreatureAnim::wiggle_static_data_s009b_3e40* last, nSPCreatureAnim::wiggle_static_data_s009b_3e40* result)
{
    for (; first != last; ++first, ++result)
        if (result) {
            result->a0 = first->a0; result->a1 = first->a1;
            result->a2 = first->a2; result->a3 = first->a3;
            float* d = result->f; float* s = first->f;
            d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
            d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8]; d[9] = s[9];
            result->c = first->c;
        }
    return result;
}

// @ 0x009b43f0
nSPCreatureAnim::wiggle_static_data_s009b_3e40* CopyWiggles(nSPCreatureAnim::wiggle_static_data_s009b_3e40* first, nSPCreatureAnim::wiggle_static_data_s009b_3e40* last, nSPCreatureAnim::wiggle_static_data_s009b_3e40* result)
{
    for (; first != last; ++first, ++result) {
        result->a0 = first->a0; result->a1 = first->a1;
        result->a2 = first->a2; result->a3 = first->a3;
        float* d = result->f; float* s = first->f;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
        d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8]; d[9] = s[9];
        result->c = first->c;
    }
    return result;
}

// @ 0x009b4490
void FillBoneXforms(nSPCreatureAnim::bone_xform_s009b_3e40* first, nSPCreatureAnim::bone_xform_s009b_3e40* last, const nSPCreatureAnim::bone_xform_s009b_3e40* value)
{
    for (; first != last; ++first)
        *first = *value;
}

// @ 0x009b44e0
void FillXform12(nSPCreatureAnim::xform12* dest, uint32_t n, const nSPCreatureAnim::xform12* value)
{
    for (; n != 0; --n, ++dest)
        if (dest) *dest = *value;
}

// @ 0x009b4550
nSPCreatureAnim::bone_xform_s009b_3e40* CopyBoneXforms(nSPCreatureAnim::bone_xform_s009b_3e40* first, nSPCreatureAnim::bone_xform_s009b_3e40* last, nSPCreatureAnim::bone_xform_s009b_3e40* result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}

// @ 0x009b45b0
nSPCreatureAnim::blob_f4& nSPCreatureAnim::blob_f4::operator=(const nSPCreatureAnim::blob_f4& o)
{
    u00 = o.u00;
    f04[0] = o.f04[0]; f04[1] = o.f04[1]; f04[2] = o.f04[2]; f04[3] = o.f04[3];
    f04[4] = o.f04[4]; f04[5] = o.f04[5]; f04[6] = o.f04[6];
    u20 = o.u20;
    f24[0] = o.f24[0]; f24[1] = o.f24[1]; f24[2] = o.f24[2]; f24[3] = o.f24[3];
    f24[4] = o.f24[4]; f24[5] = o.f24[5]; f24[6] = o.f24[6]; f24[7] = o.f24[7];
    f24[8] = o.f24[8]; f24[9] = o.f24[9]; f24[10] = o.f24[10]; f24[11] = o.f24[11];
    f24[12] = o.f24[12]; f24[13] = o.f24[13]; f24[14] = o.f24[14]; f24[15] = o.f24[15];
    f24[16] = o.f24[16]; f24[17] = o.f24[17]; f24[18] = o.f24[18];
    b70 = o.b70;
    b71 = o.b71;
    f74[0] = o.f74[0]; f74[1] = o.f74[1]; f74[2] = o.f74[2];
    f80[0] = o.f80[0]; f80[1] = o.f80[1]; f80[2] = o.f80[2];
    f80[3] = o.f80[3]; f80[4] = o.f80[4]; f80[5] = o.f80[5];
    u98[0] = o.u98[0]; u98[1] = o.u98[1]; u98[2] = o.u98[2]; u98[3] = o.u98[3];
    ba8 = o.ba8;
    ba9 = o.ba9;
    uac = o.uac;
    fb0 = o.fb0;
    ub4 = o.ub4;
    ub8 = o.ub8;
    fbc[0] = o.fbc[0]; fbc[1] = o.fbc[1]; fbc[2] = o.fbc[2]; fbc[3] = o.fbc[3];
    fbc[4] = o.fbc[4]; fbc[5] = o.fbc[5]; fbc[6] = o.fbc[6]; fbc[7] = o.fbc[7];
    fbc[8] = o.fbc[8]; fbc[9] = o.fbc[9]; fbc[10] = o.fbc[10]; fbc[11] = o.fbc[11];
    fbc[12] = o.fbc[12]; fbc[13] = o.fbc[13];
    return *this;
}

// @ 0x009b47f0
nSPCreatureAnim::Transform30_s009b_3e40* CopyTransform30Backward(nSPCreatureAnim::Transform30_s009b_3e40* first, nSPCreatureAnim::Transform30_s009b_3e40* last, nSPCreatureAnim::Transform30_s009b_3e40* result)
{
    while (last != first) {
        --last;
        --result;
        result->a = last->a;
        result->b = last->b;
        float* d = result->f; float* s = last->f;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
        d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8]; d[9] = s[9];
    }
    return result;
}

// @ 0x009b4870
nSPCreatureAnim::wiggle_static_data_s009b_3e40* CopyWigglesBackward(nSPCreatureAnim::wiggle_static_data_s009b_3e40* first, nSPCreatureAnim::wiggle_static_data_s009b_3e40* last, nSPCreatureAnim::wiggle_static_data_s009b_3e40* result)
{
    while (last != first) {
        --last;
        --result;
        result->a0 = last->a0; result->a1 = last->a1;
        result->a2 = last->a2; result->a3 = last->a3;
        float* d = result->f; float* s = last->f;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
        d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8]; d[9] = s[9];
        result->c = last->c;
    }
    return result;
}

// @ 0x009b4910
void CopyXform12Guarded(nSPCreatureAnim::xform12* first, nSPCreatureAnim::xform12* last, nSPCreatureAnim::xform12* result)
{
    for (; first != last; ++first, ++result)
        if (result) *result = *first;
}

// @ 0x009b4990
nSPCreatureAnim::wiggle_instance_data_s009b_3e40* CopyWiggleInstancesGuarded(nSPCreatureAnim::wiggle_instance_data_s009b_3e40* first, nSPCreatureAnim::wiggle_instance_data_s009b_3e40* last, nSPCreatureAnim::wiggle_instance_data_s009b_3e40* result)
{
    for (; first != last; ++first, ++result)
        if (result) {
            result->wiggle = first->wiggle;
            result->flag4 = first->flag4;
            result->flag5 = first->flag5;
            float* d = result->f; float* s = first->f;
            d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
            d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8];
        }
    return result;
}

// @ 0x009b4a20
nSPCreatureAnim::wiggle_instance_data_s009b_3e40* CopyWiggleInstances(nSPCreatureAnim::wiggle_instance_data_s009b_3e40* first, nSPCreatureAnim::wiggle_instance_data_s009b_3e40* last, nSPCreatureAnim::wiggle_instance_data_s009b_3e40* result)
{
    for (; first != last; ++first, ++result) {
        result->wiggle = first->wiggle;
        result->flag4 = first->flag4;
        result->flag5 = first->flag5;
        float* d = result->f; float* s = first->f;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
        d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8];
    }
    return result;
}

// @ 0x009b4ab0
nSPCreatureAnim::bone_xform_s009b_3e40* CopyBoneXformsBackward(nSPCreatureAnim::bone_xform_s009b_3e40* first, nSPCreatureAnim::bone_xform_s009b_3e40* last, nSPCreatureAnim::bone_xform_s009b_3e40* result)
{
    while (last != first) {
        --last;
        --result;
        *result = *last;
    }
    return result;
}

// @ 0x009b4b10
nSPCreatureAnim::wiggle_instance_data_s009b_3e40* CopyWiggleInstancesBackward(nSPCreatureAnim::wiggle_instance_data_s009b_3e40* first, nSPCreatureAnim::wiggle_instance_data_s009b_3e40* last, nSPCreatureAnim::wiggle_instance_data_s009b_3e40* result)
{
    while (last != first) {
        --last;
        --result;
        result->wiggle = last->wiggle;
        result->flag4 = last->flag4;
        result->flag5 = last->flag5;
        float* d = result->f; float* s = last->f;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
        d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; d[8] = s[8];
    }
    return result;
}

// @ 0x009b4ba0
void FUN_009b4ba0(float* out, const float* v, const float* fallback)
{
    float nvec[3];
    float len;
    NormalizeVec3(nvec, v, &len);
    float angle;
    if (len < 1e-6f) {
        angle = 0.0f;
        if (fallback == 0) {
            float axis[3] = { 1.0f, 0.0f, 0.0f };
            fallback = axis;
        }
        nvec[0] = fallback[0];
        nvec[1] = fallback[1];
        nvec[2] = fallback[2];
    } else if (len < 0.01f) {
        if (v[3] >= 0.0f)
            angle = len * 2.0f;
        else
            angle = len * -2.0f;
    } else {
        float x = v[3];
        const float one = 1.0f;
        if (-1.0f < x) {
            if (one < x) x = one;
        } else {
            x = -1.0f;
        }
        angle = acosf(x) * 2.0f;
        if (angle > 3.1415927f)
            angle = angle - 6.2831855f;
    }
    out[0] = nvec[0];
    out[1] = nvec[1];
    out[2] = nvec[2];
    out[3] = angle;
}

// @ 0x009b4ce0
void nSPCreatureAnim::creature_static_data_s009b_3e40::FUN_009b4ce0()
{
    int n = (int)(((int)((char*)BodiesEnd - (char*)Bodies)) / 0x468);
    for (int i = 0; i < n; ++i) {
        nSPCreatureAnim::creature_body_static_data_s009b_3e40* b = Bodies + i;
        if (b != 0) {
            if ((b->w150[0] & 8) != 0) {
                b->u430 = b->w1f8[0];
            } else {
                uint32_t idx = b->w1f8[1];
                uint32_t cur;
                int cnt = 0;
                do {
                    cur = idx;
                    ++cnt;
                    if (cur == 0 || (Bodies[cur].w150[0] & 8) != 0) break;
                    idx = Bodies[cur].w1f8[1];
                } while (cnt < 0xff);
                b->u430 = cur;
            }
        }
    }
}

// @ 0x009b4d90
uint32_t FUN_009b4d90(nSPCreatureAnim::creature_static_data_s009b_3e40* self, nSPCreatureAnim::creature_body_static_data_s009b_3e40* b)
{
    nSPCreatureAnim::creature_body_static_data_s009b_3e40* p = self->Bodies + self->u440;
    nSPCreatureAnim::creature_body_static_data_s009b_3e40* parent = (nSPCreatureAnim::creature_body_static_data_s009b_3e40*)p->w1f8[7];   // +0x214
    int n = 0;
    nSPCreatureAnim::creature_body_static_data_s009b_3e40* c = parent;
    if (c != b) {
        do {
            c = (nSPCreatureAnim::creature_body_static_data_s009b_3e40*)c->w1f8[7];
            ++n;
        } while (c != b);
        if (n == 0)
            return b->w1f8[0];
        if (n == 1)
            return p->w1f8[1];
        int k = n / 2 + 1;
        c = parent;
        for (;;) {
            if (c == b) return 0;
            --k;
            if (k == 0) break;
            c = (nSPCreatureAnim::creature_body_static_data_s009b_3e40*)c->w1f8[7];
        }
        return c->w1f8[0];
    }
    return b->w1f8[0];
}

// @ 0x009b4e00
void Bone_ComputeSegment(Solver* self, Solver* other)
{
    float* a = (float*)FUN_0099c1a0((void*)0, (char*)self + 0x118, (char*)self + 0x344);
    float ax = a[0] + self->mOffsetX;
    float ay = a[1] + self->mOffsetY;
    float az = a[2] + self->mOffsetZ;
    float* b = (float*)FUN_0099c1a0((void*)0, (char*)other + 0x118, (char*)other + 0x344);
    float bx = b[0] + other->mOffsetX;
    float by = b[1] + other->mOffsetY;
    float bz = b[2] + other->mOffsetZ;
    self->mPosX = bx - ax;
    self->mPosY = by - ay;
    self->mPosZ = bz - az;
}

// @ 0x009b4ef0
void Solver_UpdateSegment(Solver* self, void* unk, Solver* a)
{
    int n = FUN_009b4d90();
    int i = (int)(char*)a->mBones + 0x444;
    (void)i;
}

// @ 0x009b5080
float nSPCreatureAnim::Solver::DistX(int i0, int i1, float k)
{
    Solver* self = this;
    Bone* a = (Bone*)((char*)self->mBones + i0 * 0x468);
    Bone* b = (Bone*)((char*)self->mBones + i1 * 0x468);
    float d = a->mOffsetZ - b->mOffsetZ;
    float dx = a->mOffsetX - b->mOffsetX;
    return k * (dx * dx * k);
}

// @ 0x009b5100
float nSPCreatureAnim::Solver::DistY(int i0, int i1, float k)
{
    Solver* self = this;
    Bone* a = (Bone*)((char*)self->mBones + i0 * 0x468);
    Bone* b = (Bone*)((char*)self->mBones + i1 * 0x468);
    float d = a->mOffsetZ - b->mOffsetZ;
    float dy = a->mOffsetY - b->mOffsetY;
    return k * (dy * dy * k);
}

// @ 0x009b5180
float nSPCreatureAnim::Solver::SqX(float k, int i0, int i1)
{
    Solver* self = this;
    Bone* a = (Bone*)((char*)self->mBones + i0 * 0x468);
    Bone* b = (Bone*)((char*)self->mBones + i1 * 0x468);
    float d = a->mOffsetX - b->mOffsetX;
    return k * (d * d * k);
}

// @ 0x009b51c0
float nSPCreatureAnim::Solver::SqY(float k, int i0, int i1)
{
    Solver* self = this;
    Bone* a = (Bone*)((char*)self->mBones + i0 * 0x468);
    Bone* b = (Bone*)((char*)self->mBones + i1 * 0x468);
    float d = a->mOffsetY - b->mOffsetY;
    return k * (d * d * k);
}

// @ 0x009b5200
float nSPCreatureAnim::Solver::SegmentLengthSum(Bone* bone)
{
    Solver* self = this;
    float accum = 0.0f;
    float best = 0.01f;
    if (bone->mPrevIndex != bone->mChildFirst) {
        float* b0 = (float*)((char*)self->mBones + bone->mPrevIndex * 0x468 + 0x344);
        accum = sqrtf(fsq(b0[0]) + fsq(b0[1]) + fsq(b0[2]));
        int prev = bone->mPrevIndex;
        int cur = bone->mNextIndex;
        while (cur != bone->mChildFirst) {
            float* p0 = (float*)((char*)self->mBones + cur * 0x468 + 0x344);
            float* p1 = (float*)((char*)self->mBones + prev * 0x468 + 0x350);
            float dx = p0[0] - p1[0];
            float dy = p0[1] - p1[1];
            float dz = p0[2] - p1[2];
            accum = sqrtf(fsq(dx) + fsq(dy) + fsq(dz)) + accum;
            prev = cur;
            cur = *(int*)((char*)self->mBones + cur * 0x468 + 0x1fc);
        }
        float* p1 = (float*)((char*)self->mBones + prev * 0x468 + 0x350);
        accum = sqrtf(fsq(p1[0]) + fsq(p1[1]) + fsq(p1[2])) + accum;
        if (0.01f < accum)
            return accum;
    }
    (void)best;
    return best;
}

// @ 0x009b5360
float nSPCreatureAnim::Solver::AverageSegment()
{
    Solver* self = this;
    int count = (int)((self->mBonesEnd - self->mBones) / 0x468);
    float accum = 0.0f;
    int used = 0;
    if (count != 0) {
        Bone* b = self->mBones;
        do {
            if ((b->mFlags154 & 4) != 0) {
                accum = SegmentLengthSum2(b) + accum;
                ++used;
            }
            b = (Bone*)((char*)b + 0x468);
        } while (--count != 0);
        if (used != 0)
            accum = accum / (float)used;
    }
    return accum;
}

// @ 0x009b53f0
void Bone_AddScaledVectors(float* out, Bone* b, float k)
{
    float f4 = b->mPosX * k;
    if ((b->mFlags150 & 8) != 0) {
        float f1 = b->mParentOffX;
        float f2 = b->mParentOffY;
        float f3 = b->mParentOffZ;
        float f5 = b->mPosY;
        out[0] = f4 - f1 * k;
        float f6 = b->mPosZ;
        out[1] = f5 * k - f2 * k;
        out[2] = f6 * k - f3 * k;
        return;
    }
    out[0] = f4;
    out[1] = b->mPosY * k;
    out[2] = b->mPosZ * k;
}

// @ 0x009b54a0
void nSPCreatureAnim::Solver::BuildOrderPairs()
{
    Solver* self = this;
    Bone* b = (Bone*)((char*)self->mBones + self->mRootIndex * 0x468);
    int idx = 0;
    while (b->mPrevIndex != 0) {
        Bone* cur = b;
        *(Bone**)((char*)self->mOrderPairs + idx * 8) = cur;
        *(int*)((char*)self->mOrderPairs + idx * 8 + 4) = 0;
        b = (Bone*)((char*)self->mBones + cur->mNextIndex * 0x468);
        ++idx;
    }
    idx = idx * 4;
    for (;;) {
        *(Bone**)((char*)self->mOrderPairs + idx * 2) = b;
        unsigned int n = (unsigned int)b->mChildCount;
        Bone* c = (Bone*)((char*)self->mBones + b->mChildFirst * 0x468);
        int found = 0;
        if (n != 0) {
            do {
                if ((c->mFlags150 & 8) != 0 && c != b)
                    break;
                ++found;
                c = (Bone*)((char*)c + 0x468);
            } while ((unsigned int)found < n);
        }
        if ((unsigned int)found == n || c == 0)
            return;
        b = c;
        idx += 4;
    }
}

// @ 0x009b5580
void nSPCreatureAnim::Solver::MarkDeepBones()
{
    Solver* self = this;
    float f = (self->mSizeA / self->mSizeB - 1.0f) * g_1550d48 + g_1550d44;
    if (f <= g_1550d40)
        f = g_1550d40;
    if (g_1550d3c < f)
        f = g_1550d3c;
    float limit = f * self->mSizeB;
    unsigned int count = (unsigned int)((int)((char*)self->mOrderPairsEnd - (char*)self->mOrderPairs) >> 3);
    unsigned int i = 0;
    if (3 < (int)count) {
        int* p = self->mOrderPairs;
        do {
            Bone* b0 = *(Bone**)((char*)p + 0);
            if (b0->mOffsetZ - b0->mParentOffZ < limit) {
                *(unsigned char*)((char*)p + 4) = 1;
                self->mFlaggedCount = self->mFlaggedCount + 1;
            }
            Bone* b1 = *(Bone**)((char*)p + 8);
            if (b1->mOffsetZ - b1->mParentOffZ < limit) {
                *(unsigned char*)((char*)p + 12) = 1;
                self->mFlaggedCount = self->mFlaggedCount + 1;
            }
            Bone* b2 = *(Bone**)((char*)p + 16);
            if (b2->mOffsetZ - b2->mParentOffZ < limit) {
                *(unsigned char*)((char*)p + 20) = 1;
                self->mFlaggedCount = self->mFlaggedCount + 1;
            }
            Bone* b3 = *(Bone**)((char*)p + 24);
            if (b3->mOffsetZ - b3->mParentOffZ < limit) {
                *(unsigned char*)((char*)p + 28) = 1;
                self->mFlaggedCount = self->mFlaggedCount + 1;
            }
            p = (int*)((char*)p + 32);
            i = i + 4;
        } while (i < count - 3);
    }
    for (; i < count; ++i) {
        Bone* b0 = *(Bone**)((char*)self->mOrderPairs + i * 8);
        if (b0->mOffsetZ - b0->mParentOffZ < limit) {
            *(unsigned char*)((char*)self->mOrderPairs + i * 8 + 4) = 1;
            self->mFlaggedCount = self->mFlaggedCount + 1;
        }
    }
}

// @ 0x009b5700
int nSPCreatureAnim::Solver::IsDeeperRatio(Bone** a, Bone** b)
{
    Solver* self = this;
    /* Both epsilons are the global 0x014471fc (1e-06f); when the measured value
       is at least the epsilon the address of the local is used instead. */
    float denom = self->mSizeA;
    float* pDenom = (float*)&g_14471fc;
    if (!(denom < *pDenom))
        pDenom = &denom;
    int result = 1;
    if (a != b) {
        Bone* ba = *a;
        Bone* bb = *b;
        float dx = ba->mOffsetX - bb->mOffsetX;
        float dy = ba->mOffsetY - bb->mOffsetY;
        float absdz = fabsf(ba->mOffsetZ - bb->mOffsetZ);
        float len = sqrtf(fsq(dy) + fsq(dx));
        float* pLen = (float*)&g_14471fc;
        if (!(len < *pLen))
            pLen = &len;
        if (self->mSizeB / *pDenom < absdz / *pLen)
            return 1;
        result = 0;
    }
    return result;
}

// @ 0x009b57b0
int nSPCreatureAnim::Solver::FindMinIndex(int* from, int* to)
{
    Solver* self = this;
    int* base = self->mOrderPairs;
    unsigned int n = (unsigned int)(to - base) >> 3;
    unsigned int i = (unsigned int)((from - base) >> 3) + 1;
    if (i <= n) {
        unsigned int rem = (n - i) + 1;
        if (3 < rem) {
            while (rem > 3) {
                int* p = (int*)(base + i * 8);
                if (*(float*)(*(int*)(p - 4) + 0x114) <= *(float*)(*from + 0x114) &&
                    *(float*)(*from + 0x114) != *(float*)(*(int*)(p - 4) + 0x114))
                    from = p - 4;
                if (*(float*)(*(int*)(p - 2) + 0x114) <= *(float*)(*from + 0x114) &&
                    *(float*)(*from + 0x114) != *(float*)(*(int*)(p - 2) + 0x114))
                    from = p - 2;
                if (*(float*)(*(int*)(p + 0) + 0x114) <= *(float*)(*from + 0x114) &&
                    *(float*)(*from + 0x114) != *(float*)(*(int*)(p + 0) + 0x114))
                    from = p;
                if (*(float*)(*(int*)(p + 2) + 0x114) <= *(float*)(*from + 0x114) &&
                    *(float*)(*from + 0x114) != *(float*)(*(int*)(p + 2) + 0x114))
                    from = p + 2;
                p = p + 8;
                i += 4;
                rem -= 4;
            }
        }
        while (i <= n) {
            int* p = (int*)((char*)base + i * 8);
            if (*(float*)(*(int*)(p + 0) + 0x114) <= *(float*)(*from + 0x114) &&
                *(float*)(*from + 0x114) != *(float*)(*(int*)(p + 0) + 0x114))
                from = p;
            i += 1;
        }
    }
    return (int)((from - base) >> 3);
}

// @ 0x009b58b0
void nSPCreatureAnim::Solver::SortRange(int* a, int* b)
{
    Solver* self = this;
    (void)self;
    if (3 < ((int)b - (int)a >> 3) + 1) {
        int ok = self->IsDeeperRatio((Bone**)a, (Bone**)b);
        if (ok == 0) {
            FUN_009b3090(0x74667370, 1);
            FUN_009b3090(0x74667370, 1);
            return;
        }
    }
    self->FindMinIndex(a, b);
    FUN_009b3090(0x74667370, 1);
}

// @ 0x009b5930
void nSPCreatureAnim::Solver::SortFlaggedRuns()
{
    unsigned int n = (unsigned int)((int)((char*)mOrderPairsEnd - (char*)mOrderPairs) >> 3);
    int* first = 0;
    int* last = 0;
    if (mFlaggedCount != 0) {
        for (unsigned int i = 0; i < n; ++i) {
            char flag = *(char*)((char*)mOrderPairs + 4 + i * 8);
            int* cur = (int*)((char*)mOrderPairs + i * 8);
            if (flag != 0) {
                if (first == 0)
                    first = cur;
                last = cur;
            }
            if (first != 0 && last != 0 && (flag == 0 || i == n - 1)) {
                SortRange(first, last);
                last = 0;
                first = 0;
            }
        }
    } else {
        SortRange(mOrderPairs, (int*)((char*)mOrderPairs - 8 + n * 8));
    }
}

// @ 0x009b59c0
void nSPCreatureAnim::Solver::ShutdownAnims()
{
    Solver* self = this;
    int* p = (int*)((char*)self + 0x1220);
    FUN_009dfc40(p);
    p = (int*)((char*)self + 0x1220);
    int i = 0x17;
    do {
        p = (int*)((char*)p - 0xb4);
        FUN_009dfd30(p);
        --i;
    } while (-1 < i);
}

// 0x009b5a00 (byte-exact lifted version: match/slices/s009b5a00/s009b5a00.cpp)
void Bone_ResetState(unsigned int* p)
{
    p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 0;
    p[0x16] = 0; p[0x17] = 0; p[0x18] = 0; p[0x19] = 0; p[0x1a] = 0; p[0x1b] = 0;
    p[0x1c] = 0; p[0x1d] = 0; p[0x1e] = 0; p[0x1f] = 0; p[0x20] = 0; p[0x21] = 0;
    p[0x22] = 0; p[0x23] = 0; p[0x24] = 0; p[0x25] = 0; p[0x26] = 0; p[0x27] = 0;
    p[0x28] = 0; p[0x12] = 0; p[0x13] = 0; p[0x14] = 0;
    *(unsigned char*)((char*)p + 0x54) = 0;
    *(unsigned char*)((char*)p + 0x55) = 0;
    *(unsigned char*)((char*)p + 0x2a0) = 0;
    *(unsigned char*)((char*)p + 0x38) = 0;
    p[0x51] = 0;
}

// @ 0x009b5ab0
void Bone_IntegrateVelocity(unsigned int* p, float dt, float* accel, float* quat)
{
    if (!(0.0f < dt))
        return;
    float qx = accel[0];
    float qz = accel[2];
    float vy = accel[1];
    p[0x20] = (unsigned int)(vy * dt + (float)p[0x20]);
    p[0x21] = (unsigned int)((float)p[0x21] + qz * dt);
    p[0x1f] = (unsigned int)((float)p[0x1f] + qx * dt);
    p[0x22] = (unsigned int)(dt + (float)p[0x22]);
    float ax = (float)p[0x23];
    float ay = (float)p[0x24];
    float az = (float)p[0x25];
    float aw = (float)p[0x26];
    float bx = quat[0] * dt;
    float by = quat[1] * dt;
    float bz = quat[2] * dt;
    float bw = quat[3] * dt;
    if (0.0f <= (aw * bw + ax * bx) + ay * by + az * bz) {
        ax += bx; ay += by; az += bz; aw += bw;
    } else {
        ax -= bx; ay -= by; az -= bz; aw -= bw;
    }
    p[0x23] = *(unsigned int*)&ax;
    p[0x24] = *(unsigned int*)&ay;
    p[0x25] = *(unsigned int*)&az;
    p[0x26] = *(unsigned int*)&aw;
    p[0x27] = (unsigned int)(dt + (float)p[0x27]);
    unsigned int idx = *(unsigned int*)(((Bone*)p)->pad0 + 0x1f8) & 0x7fffffff;
    unsigned char* flag = (unsigned char*)(p[1] + 0x1b8 + (idx >> 2));
    *flag |= (unsigned char)(2 << ((idx * 2) & 7));
}

// @ 0x009b5c50
void nSPCreatureAnim::Solver::UpdateAvgSegLen()
{
    Solver* self = this;
    int n = (int)((char*)self->mBonesEnd - (char*)self->mBones) / 0x468;
    if (0 < n) {
        int off = 0;
        do {
            Solver* b = (Solver*)((char*)self->mBones + off);
            b->mAvgSegLen = (float)FUN_009f9c60(b);
            if (*(int*)&g_1550b04 == 0)
                b->mJiggle = nSPCreatureAnim_ShouldJiggle(b) ? 1 : 0;
            if (b->mSizeA <= 0.001f && b->mSizeA != 0.001f)
                b->mJiggle = 0;
            off += 0x468;
            --n;
        } while (n != 0);
    }
}

// @ 0x009b5ce0
void CA::FUN_009b5ce0(CA::Creature* c)
{
  CA::u32 numParts = (CA::u32)(c->mpPartsEnd - c->mpPartsBegin);
  CA::u32 numRefs  = (CA::u32)(c->mpRefsEnd - c->mpRefsBegin);
  int firstIdx = -1;
  int lastIdx  = -1;
  int bestIdx  = -1;
  bool viaRefs = true;

  if (numRefs != 0) {
    CA::u32 i = 0;
    do {
      CA::CreaturePart* part = c->mpRefsBegin[i].mPart;
      if (part->m1f8 == 0)
        bestIdx = (int)i;
      CA::u32 n = part->m208;
      if (n > 0) {
        CA::CreaturePart* child = part->m218;
        CA::u32 k = 0;
        do {
          CA::u32 flags = child->m150;
          if ((flags & 2) && !(flags & 8)) {
            if (firstIdx == -1)
              firstIdx = (int)i;
            lastIdx = (int)i;
          }
          child += 1;
          ++k;
        } while (k < n);
      }
      ++i;
    } while (i < numRefs);

    if (firstIdx != -1) {
      if (firstIdx > bestIdx)
        firstIdx = bestIdx;
      else if (lastIdx < bestIdx)
        lastIdx = bestIdx;
    }
    if (firstIdx == lastIdx)
      viaRefs = false;
  }

  if (viaRefs) {
    if (lastIdx > firstIdx) {
      /* nothing to mark */
    } else {
      int i = firstIdx;
      do {
        c->mpRefsBegin[i].mPart->m210 = 0x200;
        ++i;
      } while (i <= lastIdx);
    }
  } else {
    CA::u32 n = (CA::u32)CA::gExtraBoneCount;
    c->mpPartsBegin->m210 = 0x200;
    if (n != 0) {
      int off = 0;
      CA::u32 k = 0;
      do {
        int fwd = bestIdx + off;
        if ((CA::u32)fwd < numRefs)
          ((CA::PartRef*)((char*)c->mpRefsBegin + off * 8))->mPart->m210 = 0x200;
        int bwd = bestIdx - off;
        if ((CA::u32)bwd < numRefs)
          ((CA::PartRef*)((char*)c->mpRefsBegin - off * 8))->mPart->m210 = 0x200;
        ++off;
        ++k;
      } while (k < n);
    }
  }

  if (numParts > 0) {
    CA::u32 off = 0;
    CA::u32 i = 0;
    do {
      CA::CreaturePart* p = (CA::CreaturePart*)((char*)c->mpPartsBegin + off);
      if (p->m150 & 0x20) {
        CA::CreaturePart* q = p;
        for (;;) {
          CA::CreaturePart* nxt = q->m214;
          q->m210 = 0x200000;
          if (nxt->m210 != 0x200)
            break;
          q = nxt;
        }
      }
      off += 0x468;
      ++i;
    } while (i < numParts);
  }

  if (numRefs > 0) {
    CA::u32 i = 0;
    do {
      CA::CreaturePart* p = c->mpRefsBegin[i].mPart;
      if (p->m210 == 0)
        p->m210 = 0x10000;
      ++i;
    } while (i < numRefs);
  }

  if (numParts > 0) {
    CA::u32 off = 0;
    CA::u32 i = 0;
    do {
      CA::CreaturePart* p = (CA::CreaturePart*)((char*)c->mpPartsBegin + off);
      if (p->m210 == 0 && (p->m150 & 2))
        p->m210 = p->m464 ? 0x400000 : 0x100;
      off += 0x468;
      ++i;
    } while (i < numParts);
  }

  if (numParts > 1) {
    CA::u32 off = 0x468;
    CA::u32 i = 1;
    do {
      CA::CreaturePart* p = (CA::CreaturePart*)((char*)c->mpPartsBegin + off);
      if (p->m210 == 0) {
        CA::CreaturePart* nxt = p->m214;
        CA::u32 v = nxt->m210;
        p->m210 = v ? v : CA::FUN_009b3460(nxt);
      }
      off += 0x468;
      ++i;
    } while (i < numParts);
  }
}

// @ 0x009b5f90
void CA::FUN_009b5f90(CA::u32 index, CA::Creature* c)
{
  for (;;) {
    if (index == 0)
      return;
    CA::CreaturePart* part = c->mpPartsBegin + index;

    if (part->m208 > 0) {
      CA::CreaturePart* parent = c->mpPartsBegin + part->m204;
      CA::u32 n = part->m208;
      CA::u32 hits = 0;
      do {
        if (*(CA::u8*)&parent->m154 & 2)
          ++hits;
        parent += 1;
        --n;
      } while (n != 0);
      if (hits > 1)
        return;
    }

    CA::PartCaps* caps = &part->mCaps;
    CA::u32* names = caps->NameFOURCCs;
    CA::u32 ci = 0;
    for (;;) {
      CA::u32 v = names[ci];
      if (v == 0x626d696c) {          // 'limb'
        caps->Values[ci] = 1;
        break;
      }
      if (v == 0) {
        names[ci] = 0x626d696c;
        caps->Values[ci] = 1;
        break;
      }
      if (++ci >= 32)
        break;
    }

    part->m154 = 0;
    part->m150 = 0;
    CA::u32* nm = caps->NameFOURCCs;
    for (CA::u32 k = 0; k < 32; ++k) {
      CA::u32 v = nm[k];
      if (v == 0)
        break;
      CA::u32 f;
      switch (v) {
        case 0x626d696c: f = 2;    break;   // 'limb'
        case 0x6e697073: f = 8;    break;   // 'spin'
        case 0x70737267: f = 0x40; break;   // 'grsp'
        case 0x7274736e: f = 0x80; break;   // 'nstr'
        case 0x74667370: f = 0x10; break;   // 'psft'
        case 0x746f6f66: f = 4;    break;   // 'foot'
        case 0x746f6f72: f = 1;    break;   // 'root'
        case 0x74756f6d: f = 0x20; break;   // 'mout'
        default:         f = 0;    break;
      }
      part->m150 |= f;
      if (caps->Values[k] != 0)
        part->m154 |= f;
    }

    CA::u32 si = 0;
    for (;;) {
      CA::u32 v = names[si];
      if (v == 0x6e697073) {          // 'spin'
        caps->Values[si] = 0;
        break;
      }
      if (v == 0) {
        names[si] = 0x6e697073;
        caps->Values[si] = 0;
        break;
      }
      if (++si >= 32)
        break;
    }

    part->m154 = 0;
    part->m150 = 0;
    CA::u32* nm2 = caps->NameFOURCCs;
    for (CA::u32 k = 0; k < 32; ++k) {
      CA::u32 v = nm2[k];
      if (v == 0)
        break;
      CA::u32 f;
      switch (v) {
        case 0x626d696c: f = 2;    break;   // 'limb'
        case 0x6e697073: f = 8;    break;   // 'spin'
        case 0x70737267: f = 0x40; break;   // 'grsp'
        case 0x7274736e: f = 0x80; break;   // 'nstr'
        case 0x74667370: f = 0x10; break;   // 'psft'
        case 0x746f6f66: f = 4;    break;   // 'foot'
        case 0x746f6f72: f = 1;    break;   // 'root'
        case 0x74756f6d: f = 0x20; break;   // 'mout'
        default:         f = 0;    break;
      }
      part->m150 |= f;
      if (caps->Values[k] != 0)
        part->m154 |= f;
    }

    index = part->m1fc;
  }
}

// @ 0x009b61f0
CA::Vec3* CA::Creature::get_workspace_origin(CA::Vec3* out, CA::u32 unused)
{
  float* o = &out->x;
  const CA::Vec3* c = &mpBonesBegin->mCenter;
  o[0] = c->x;
  o[1] = c->y;
  o[2] = c->z;
  return out;
}

// @ 0x009b6220
float CA::Creature::set_workspace_dir(const CA::Vec3* dir, CA::Vec3* out)
{
  float result = 0.0f;
  CA::WorkspaceSource* src = mpSource;
  if (src && src->mCallback) {
    if (src->mUseOrigin ||
        dir->x * dir->x + dir->y * dir->y + dir->z * dir->z > CA::kWorkspaceDirEps) {
      result = ((float (__cdecl*)(void*, void*, const CA::Vec3*, CA::Vec3*, int, int))
                src->mCallback)(src->mContext, m04, dir, out, 0, 0);
      return result;
    }
  }
  if (out) {
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = CA::kWorkspaceOne;
  }
  return result;
}

// @ 0x009b62c0
CA::Vec3* CA::Creature::workspace_origin_for(CA::Vec3* out, const CA::Vec3* v)
{
  out->x = 0.0f;
  out->y = 0.0f;
  out->z = CA::kWorkspaceOne;
  if (!v)
    v = &m18;
  CA::WorkspaceSource* src = mpSource;
  if (src && src->mUseOrigin) {
    if (v->x * v->x + v->y * v->y + v->z * v->z > CA::kWorkspaceMinSq) {
      CA::Vec3 tmp;
      *out = *src->rotateInto(&tmp, v, 0);
    }
  }
  return out;
}

// @ 0x009b6360
void CA::Creature::update_part_states()
{
  CA::u32 count = (CA::u32)(mpBonesEnd - mpBonesBegin);
  if (count == 0)
    return;

  CA::u32 off = 0;
  for (CA::u32 i = 0; i < count; ++i) {
    CA::BoneMesh* bm = (CA::BoneMesh*)((char*)mpBonesBegin + off);
    CA::CreaturePart* part = (CA::CreaturePart*)bm->mpShape;
    if (part->m150 & 4) {
      CA::Vec3 local;
      local.x = part->mA.x * m70;
      local.y = part->mA.y * m70;
      local.z = part->mA.z * m70;
      CA::u32 id = mPool.addPart(this, &local, &part->mB);
      m1640 = id + 1;
      CA::BoneRecord* rec = (CA::BoneRecord*)((char*)*mPool.storage() + id * 0x108);
      rec->mIndex = i;
      rec->finish();
    }
    off += 0x2bc;
  }
}

// @ 0x009b6450
bool RayCastParts(const float* org, const float* dir, RC::Owner* obj, unsigned* pIndex, float* pT, float* pHit, float* pNormal)
{
  float bestT = FLT_MAX;
  float bestN[3] = {0.0f, 0.0f, 0.0f};
  float dx = org[0] - obj->mPos[0];
  float qd = obj->mQuat[3];
  float qc = obj->mQuat[2];
  float qb = obj->mQuat[1];
  float dy = org[1] - obj->mPos[1];
  float dz = org[2] - obj->mPos[2];
  float qa = obj->mQuat[0];
  float lo[3];
  float ld[3];
  unsigned bestIdx = 0xffffffff;

  lo[0] = (((qc * qa + -(qb * qd)) * dz + (qb * qa - -(qc * qd)) * dy) + (-(qc * qc) + -(qb * qb)) * dx) * 2.0f + dx;
  lo[1] = (((qc * qb - -(qa * qd)) * dz + (-(qc * qc) + -(qa * qa)) * dy) + (qb * qa + -(qc * qd)) * dx) * 2.0f + dy;
  lo[2] = (((-(qb * qb) + -(qa * qa)) * dz + (qc * qb + -(qa * qd)) * dy) + (qc * qa - -(qb * qd)) * dx) * 2.0f + dz;

  float e0 = dir[0], e1 = dir[1], e2 = dir[2];
  qb = obj->mQuat[1];
  qd = obj->mQuat[3];
  qa = obj->mQuat[0];
  qc = obj->mQuat[2];
  ld[0] = (((-(qc * qc) + -(qb * qb)) * e0 + (qc * qa + -(qb * qd)) * e2) + (qb * qa - -(qc * qd)) * e1) * 2.0f + e0;
  ld[1] = (((-(qc * qc) + -(qa * qa)) * e1 + (qb * qa + -(qc * qd)) * e0) + (qc * qb - -(qa * qd)) * e2) * 2.0f + e1;
  ld[2] = (((qc * qa - -(qb * qd)) * e0 + (-(qb * qb) + -(qa * qa)) * e2) + (qc * qb + -(qa * qd)) * e1) * 2.0f + e2;

  unsigned i = 0;
  if ((obj->mpPartsEnd - obj->mpPartsBegin) != 0) {
    do {
      RC::Part* part = &obj->mpPartsBegin[i];
      float t = FLT_MAX;
      float n[3] = {0.0f, 0.0f, 0.0f};
      RC::BoxShape* shape = part->mpShape;
      float qz = part->mQuat[2];
      float qy = part->mQuat[1];
      float qx = part->mQuat[0];
      float s2 = obj->mScale * 2.0f;
      float ex = s2 * shape->mHalfExtent[0];
      float ey = shape->mHalfExtent[1] * s2;
      float qyz = qz * qy;
      float ez = shape->mHalfExtent[2] * s2;
      float qw = part->mQuat[3];
      float qwy = qw * qy;
      float m[9];
      m[0] = 1.0f - (qz * qz + qy * qy) * 2.0f;
      m[1] = (qy * qx - qw * qz) * 2.0f;
      m[2] = (qwy + qz * qx) * 2.0f;
      m[3] = (qw * qz + qy * qx) * 2.0f;
      m[4] = 1.0f - (qz * qz + qx * qx) * 2.0f;
      m[5] = (qyz - qw * qx) * 2.0f;
      m[6] = (qz * qx - qwy) * 2.0f;
      m[7] = (qw * qx + qyz) * 2.0f;
      m[8] = 1.0f - (qy * qy + qx * qx) * 2.0f;
      if (BoxRayTest(lo, ld, part->mCenter, m, ex, ey, ez, &t, n) && t < bestT && 0.0f <= t) {
        bestT = t;
        bestIdx = i;
        float tmp[3];
        float* r = QuaternionVectorTransform(tmp, obj->mQuat, n);
        bestN[0] = r[0];
        bestN[1] = r[1];
        bestN[2] = r[2];
      }
      ++i;
    } while (i < (unsigned)(obj->mpPartsEnd - obj->mpPartsBegin));
    if (bestIdx != 0xffffffff) {
      if (pT) *pT = bestT;
      if (pNormal) {
        pNormal[0] = bestN[0];
        pNormal[1] = bestN[1];
        pNormal[2] = bestN[2];
      }
      if (pHit) {
        float h1 = dir[1];
        float h2 = dir[2];
        float o1 = org[1];
        float o2 = org[2];
        pHit[0] = dir[0] * bestT + org[0];
        pHit[1] = h1 * bestT + o1;
        pHit[2] = h2 * bestT + o2;
      }
      if (pIndex) *pIndex = bestIdx;
      return true;
    }
  }
  return false;
}

// @ 0x009b6b10
void FUN_009b6b10(Vector3* pMin, Vector3* pMax, const cPartOwner* pOwner)
{
    *pMin = Vector3(kMaxFloat, kMaxFloat, kMaxFloat);
    *pMax = Vector3(-kMaxFloat, -kMaxFloat, -kMaxFloat);

    for (uint32_t i = 0; i < pOwner->mParts.size(); i++) {
        const cOrientedPart& part = pOwner->mParts[i];
        const Vector3& center = part.mPosition;
        Vector3 extents = part.mHalfExtents;

        Vector3 r = part.mOrientation.Rotate(Vector3(extents.x, extents.y, extents.z));
        ExpandBounds(*pMin, *pMax, center - r);
        ExpandBounds(*pMin, *pMax, center + r);

        r = part.mOrientation.Rotate(Vector3(-extents.x, extents.y, extents.z));
        ExpandBounds(*pMin, *pMax, center - r);
        ExpandBounds(*pMin, *pMax, center + r);

        r = part.mOrientation.Rotate(Vector3(-extents.x, extents.y, -extents.z));
        ExpandBounds(*pMin, *pMax, center - r);
        ExpandBounds(*pMin, *pMax, center + r);

        r = part.mOrientation.Rotate(Vector3(extents.x, extents.y, -extents.z));
        ExpandBounds(*pMin, *pMax, center - r);
        ExpandBounds(*pMin, *pMax, center + r);
    }
}

// @ 0x009b77a0
void FUN_009b77a0(float* param_1, int param_2, int param_3, float* param_4, char* param_5)
{
    int iVar4 = *(int*)(param_2 + 0x2e4);
    float fVar1 = *(float*)(iVar4 + 0x18);
    float fVar2 = *(float*)(iVar4 + 0x10);
    float fVar3 = *(float*)(iVar4 + 0x14);
    float fVar5 = *(float*)(*(int*)(param_3 * 700 + iVar4) + 0x36c) * *(float*)(param_2 + 0x70);
    float fVar7 = param_4[2] - fVar1;
    float fVar9 = *param_4 - fVar2;
    float fVar6 = param_4[1] - fVar3;
    float fVar8 = (fVar9 * fVar9 + fVar7 * fVar7) + fVar6 * fVar6;
    if (fVar5 * fVar5 < fVar8) {
        fVar8 = (float)(1.0 / sqrt((double)fVar8));
        if (param_5 != 0) *param_5 = 1;
        *param_1 = (fVar8 * fVar9) * fVar5 + fVar2;
        param_1[1] = (fVar6 * fVar8) * fVar5 + fVar3;
        param_1[2] = (fVar8 * fVar7) * fVar5 + fVar1;
        return;
    }
    if (param_5 != 0) *param_5 = 0;
    *param_1 = *param_4;
    param_1[1] = param_4[1];
    param_1[2] = param_4[2];
}

// @ 0x009b78c0
char __fastcall FUN_009b78c0(int param_1, int dummy, int param_2, int param_3, int param_4)
{
    (void)dummy;
    int* piVar2 = GetPoliticalID(param_1 + 0x15b8);
    piVar2 = (int*)(param_2 * 0x104 + *piVar2);
    int iVar4 = *piVar2;
    char* local_1a8;
    if ((iVar4 < 0) || (7 < iVar4)) local_1a8 = 0;
    else local_1a8 = (char*)*(int*)(0x01550c0c + iVar4 * 4);
    char local_1a0[416];
    int local_1a4;
    if (iVar4 == 7) {
        Sprintf8(local_1a0, "default");
        local_1a4 = FUN_009e5b40(param_1 + 0x2f8, 0, local_1a0, (int)piVar2, param_4);
    } else {
        char cVar1 = FUN_009b3850(param_1, 0, local_1a0, local_1a8, param_3);
        if (cVar1 != 0) {
            int uVar3 = FUN_009ce410((int)piVar2);
            local_1a4 = FUN_009e18c0(param_1 + 0x2f8, 0, local_1a0, uVar3, param_4);
            if (local_1a4 != 0) goto LAB_009b79ca;
        }
        cVar1 = FUN_009b3850(param_1, 0, local_1a0, local_1a8, 0);
        if (cVar1 == 0) return 0;
        int uVar3 = FUN_009ce410((int)piVar2);
        local_1a4 = FUN_009e18c0(param_1 + 0x2f8, 0, local_1a0, uVar3, param_4);
    }
    if (local_1a4 == 0) return 0;
LAB_009b79ca:
    {
        int iVar5 = *(int*)(param_1 + param_2 * 4 + 0x2fc);
        if (param_4 == iVar5) *(int*)(param_1 + param_2 * 4 + 0x2fc) = iVar5 + 1;
        if (param_4 == 0) *(int*)(param_1 + (param_4 + param_2 * 4) * 4 + 0x374) = 0x3f800000;
        else *(int*)(param_1 + (param_4 + param_2 * 4) * 4 + 0x374) = 0;
        int uVar3 = FUN_009ce410((int)piVar2);
        iVar5 = FUN_009dbe10(param_1 + 0x2f8, 0, local_1a4, uVar3, param_4);
        if (iVar5 != 0) {
            *(int*)(param_1 + 0x434) = param_2 + 1;
            int uVar4 = FUN_009d0c80((int)piVar2);
            int inner[45];
            FUN_009e4350((int)inner, 0, *piVar2, uVar4);
            int index = param_4 + param_2 * 4;
            int dest = param_1 + 0x440 + index * 0xb4;
            FUN_009e3790(dest, 0, inner);
            FUN_009dfc40((int)inner);
            float fVar5 = FUN_009dc7a0(param_1 + 0x2f8, 0, (void*)(param_1 + 0x264));
            float fVar6 = 1.0f;
            if (1e-06f < *(float*)(param_1 + 0x70)) fVar6 = 1.0f / *(float*)(param_1 + 0x70);
            FUN_009e4450(param_1 + 0x2f8, 0, fVar6 * fVar5, param_4, 0, 0);
            int a = *(int*)(param_1 + param_2 * 4 + 0x2fc);
            int b = param_1 + param_2 * 0x10 + 0x374;
            int c = param_1 + param_2 * 0x10 + 0x3d4;
            int d = param_1 + param_2 * 0x2d0 + 0x438;
            int e = param_1 + 0x434;
            FUN_009d24c0((int)piVar2, 0, a, b, c, d, e);
            FUN_009d1050((int)piVar2);
        }
    }
    return 1;
}

// LoadGaitRecord (0x009b78c0) is a __thiscall member in retail (ecx = instance, no edx).
struct GaitLoader_s009b_7b10 { char FUN_009b78c0(int group, int a, int b); };
// @ 0x009b7b10
char __fastcall FUN_009b7b10(int param_1, int dummy, int param_2, int param_3)
{
    (void)dummy;
    char uVar3 = 1;
    int* piVar2 = GetPoliticalID(param_1 + 0x15b8);
    int iVar1 = (piVar2[1] - *piVar2) / 0x104;
    int iVar4 = 0;
    if (0 < iVar1) {
        do {
            uVar3 = ((GaitLoader_s009b_7b10*)param_1)->FUN_009b78c0(iVar4, param_2, param_3);
            iVar4 = iVar4 + 1;
        } while (iVar4 < iVar1);
    }
    return uVar3;
}

// @ 0x009b7b70
void nSPCreatureAnim::creature_instance_data::SetStyleWeightForAllGroups(char const * param_2, int param_3, float param_4)
{
    int param_2_v = (int)param_2;
    int iVar4 = 0;
    if (0 < *(int*)((char*)this + 0x2f8)) {
        float* local_4 = (float*)((char*)this + 0x3d4);
        int* pcVar6 = (int*)((char*)this + 0x2fc);
        float* pcVar5 = (float*)((char*)this + param_3 * 4 + 0x374);
        do {
            if (*(int*)((char*)pcVar5 - 0x60) == 0) {
                FUN_009b78c0((int)this, 0, iVar4, param_2_v, param_3);
            }
            int iVar3 = 0;
            float* pcVar2 = local_4;
            if (0 < *pcVar6) {
                do {
                    iVar3 = iVar3 + 1;
                    *pcVar2 = *(float*)((char*)pcVar2 - 0x60);
                    pcVar2 = pcVar2 + 1;
                } while (iVar3 < *pcVar6);
            }
            local_4 = local_4 + 4;
            *(int*)((char*)this + 0x434) = 5;
            *pcVar5 = param_4;
            iVar4 = iVar4 + 1;
            pcVar5 = pcVar5 + 4;
            pcVar6 = pcVar6 + 1;
        } while (iVar4 < *(int*)((char*)this + 0x2f8));
    }
}

// @ 0x009b7da0
void __fastcall FUN_009b7da0(int param_1, int dummy, float param_2)
{
    (void)dummy;
    float fVar6 = 1.0f / *(float*)(param_1 + 0x70);
    float out[3];
    float vec[3];
    float quat[4];
    float zero[3];
    float rot[4];
    float scaled[3];
    float dir[3];
    if (*(char*)(param_1 + 0x263) == '\0') {
        if (param_2 <= 1e-06f) param_2 = 0.0f;
        else param_2 = 1.0f / param_2;
        float* pfVar3 = (float*)(param_1 + 0x1660);
        *pfVar3 = (*(float*)(param_1 + 0x18) - *(float*)(param_1 + 0x1644)) * param_2;
        *(float*)(param_1 + 0x1664) = (*(float*)(param_1 + 0x1c) - *(float*)(param_1 + 0x1648)) * param_2;
        *(float*)(param_1 + 0x1668) = (*(float*)(param_1 + 0x20) - *(float*)(param_1 + 0x164c)) * param_2;
        float fVar5 = *(float*)(param_1 + 0xd8);
        if (0.0f < fVar5) {
            *pfVar3 = *pfVar3 - (fVar5 * *(float*)(param_1 + 0xdc)) * param_2;
            *(float*)(param_1 + 0x1664) = *(float*)(param_1 + 0x1664) - (*(float*)(param_1 + 0xe0) * fVar5) * param_2;
            *(float*)(param_1 + 0x1668) = *(float*)(param_1 + 0x1668) - (*(float*)(param_1 + 0xe4) * fVar5) * param_2;
        }
        float* pfVar4 = (float*)FUN_0099c310(out, (float*)(param_1 + 0x3c), pfVar3);
        *pfVar3 = pfVar4[0];
        *(float*)(param_1 + 0x1664) = pfVar4[1];
        *(float*)(param_1 + 0x1668) = pfVar4[2];
        *(float*)(param_1 + 0x1668) = 0.0f;
        *pfVar3 = *pfVar3 * fVar6;
        *(float*)(param_1 + 0x1664) = *(float*)(param_1 + 0x1664) * fVar6;
        float g0 = *(float*)(param_1 + 0x3c);
        float g1 = *(float*)(param_1 + 0x40);
        float g2 = *(float*)(param_1 + 0x44);
        float h0 = -*(float*)(param_1 + 0x1650);
        float h1 = -*(float*)(param_1 + 0x1654);
        float h2 = -*(float*)(param_1 + 0x1658);
        float g3 = *(float*)(param_1 + 0x48);
        quat[0] = ((g0 * *(float*)(param_1 + 0x165c) + g3 * h0) - g2 * h1) + g1 * h2;
        quat[1] = ((g1 * *(float*)(param_1 + 0x165c) + g3 * h1) + g2 * h0) - g0 * h2;
        quat[2] = ((g2 * *(float*)(param_1 + 0x165c) - g1 * h0) + g0 * h1) + g3 * h2;
        quat[3] = ((g3 * *(float*)(param_1 + 0x165c) - g0 * h0) - g1 * h1) - g2 * h2;
        zero[0] = 0.0f;
        zero[1] = 0.0f;
        zero[2] = 0.0f;
        FUN_009b4ba0(rot, quat, zero);
        rot[3] = rot[3] * param_2;
        scaled[0] = rot[0] * rot[3];
        scaled[1] = rot[1] * rot[3];
        scaled[2] = rot[2] * rot[3];
        dir[1] = 0.0f;
        float fVar10 = 1.0f, fVar5b = 0.0f, fVar6b = 0.0f;
        if ((*(char**)(param_1 + 0x1688) != 0) && (**(char**)(param_1 + 0x1688) != '\0')) {
            fVar5b = *(float*)(param_1 + 0x18);
            if ((fVar5b * fVar5b + *(float*)(param_1 + 0x1c) * *(float*)(param_1 + 0x1c)) +
                *(float*)(param_1 + 0x20) * *(float*)(param_1 + 0x20) <= 0.01f) {
                fVar5b = 0.0f;
            } else {
                float* pfVar3b = (float*)FUN_009a49d0(dir, (float*)(param_1 + 0x18), 0);
                fVar6b = pfVar3b[0];
                fVar5b = pfVar3b[1];
                fVar10 = pfVar3b[2];
            }
        }
        fVar6 = (fVar10 * scaled[2] + fVar5b * scaled[1]) + fVar6b * scaled[0];
    } else {
        vec[0] = *(float*)(param_1 + 0x264) * fVar6;
        vec[1] = *(float*)(param_1 + 0x268) * fVar6;
        vec[2] = 0.0f;
        float* puVar2 = (float*)FUN_0099c310(out, (void*)(param_1 + 0x3c), vec);
        *(float*)(param_1 + 0x1660) = puVar2[0];
        *(float*)(param_1 + 0x1664) = puVar2[1];
        *(float*)(param_1 + 0x1668) = puVar2[2];
        *(float*)(param_1 + 0x1668) = 0.0f;
        float fVar1 = *(float*)(param_1 + 0x18);
        float fVar10 = 1.0f, fVar6b = 0.0f, fVar5b = 0.0f;
        if (((*(char**)(param_1 + 0x1688) != 0) && (**(char**)(param_1 + 0x1688) != '\0')) &&
            (0.01f < (fVar1 * fVar1 + *(float*)(param_1 + 0x1c) * *(float*)(param_1 + 0x1c)) +
                      *(float*)(param_1 + 0x20) * *(float*)(param_1 + 0x20))) {
            float* pfVar3b = (float*)FUN_009a49d0(dir, (float*)(param_1 + 0x18), 0);
            fVar6b = pfVar3b[0];
            fVar5b = pfVar3b[1];
            fVar10 = pfVar3b[2];
        }
        fVar6 = (fVar5b + fVar6b) * 0.0f + *(float*)(param_1 + 0x26c) * fVar10;
    }
    *(float*)(param_1 + 0x166c) = fVar6;
    if (!(fVar6 > -6.2831855f)) fVar6 = -6.2831855f;
    else if (!(fVar6 <= 6.2831855f)) fVar6 = 6.2831855f;
    *(float*)(param_1 + 0x166c) = fVar6;
}

// @ 0x009b8250
void __fastcall FUN_009b8250(int param_1, int dummy, float param_2)
{
    (void)dummy;
    int* piVar3 = FUN_00a09f50(param_1 + 0x15b8);
    unsigned n = (unsigned)((piVar3[1] - *piVar3) / 0x108);
    for (unsigned i = 0; i < n; i++) {
        int eax = *(int*)(*piVar3 + 0x58 + i * 0x108) * 700 + *(int*)(param_1 + 0x2e4);
        float fVar1 = *(float*)(eax + 0x48);
        if (fVar1 < param_2) *(float*)(eax + 0x4c) = param_2 - fVar1;
    }
}

// @ 0x009b83b0
void __fastcall FUN_009b83b0(int param_1, int dummy, float param_2)
{
    (void)dummy;
    int iVar2;
    int* piVar4;
    int* piVar5;
    float fVar9;
    float fVar10;
    float fVar11;
    piVar4 = FUN_00a09f50(param_1 + 0x15b8);
    int iVar8 = *piVar4;
    fVar10 = 0.0f;
    fVar11 = 0.0f;
    unsigned uVar3 = (piVar4[1] - iVar8) / 0x108;
    unsigned uVar6 = 0;
    if (1 < (int)uVar3) {
        int iVar7 = (uVar3 - 2 >> 1) + 1;
        uVar6 = iVar7 * 2;
        piVar4 = (int*)(iVar8 + 0x160);
        do {
            iVar2 = *piVar4;
            fVar10 = *(float*)(*(int*)(param_1 + 0x2e4) + 0x4c + piVar4[-0x42] * 700) + fVar10;
            piVar4 = piVar4 + 0x84;
            iVar7 = iVar7 + -1;
            fVar11 = *(float*)(*(int*)(param_1 + 0x2e4) + 0x4c + iVar2 * 700) + fVar11;
        } while (iVar7 != 0);
    }
    if (uVar6 < uVar3) {
        fVar9 = *(float*)(*(int*)(uVar6 * 0x108 + 0x58 + iVar8) * 700 + 0x4c + *(int*)(param_1 + 0x2e4));
    } else {
        fVar9 = 0.0f;
    }
    fVar9 = (fVar10 + fVar11) + fVar9;
    if (uVar3 != 0) {
        fVar10 = (float)(int)uVar3;
        if ((int)uVar3 < 0) fVar10 = fVar10 + 4.2949673e+09f;
        fVar9 = fVar9 / fVar10;
    }
    if (1e-06f < fVar9) {
        iVar8 = *(int*)(param_1 + 0x2e4);
        if (param_2 <= 1e-06f) fVar10 = 0.0f;
        else fVar10 = fVar9 / param_2;
        fVar10 = (1.0f - fVar10) * *(float*)&DAT_01550b1c + (1.0f - *(float*)&DAT_01550b1c);
        fVar11 = *(float*)(iVar8 + 0x48) * fVar10;
        *(float*)(iVar8 + 0x48) = fVar11;
        *(float*)(iVar8 + 0x4c) = param_2 - fVar11;
        *(float*)(iVar8 + 0x88) = *(float*)(iVar8 + 0x88) * fVar10;
        *(float*)(iVar8 + 0x9c) = *(float*)(iVar8 + 0x9c) * fVar10;
        piVar4 = FUN_00a09f50(param_1 + 0x15b8);
        piVar5 = GetPoliticalID(param_1 + 0x15b8);
        iVar8 = (piVar5[1] - *piVar5) / 0x104;
        if (iVar8 != 0) {
            int iVar7 = 0;
            do {
                piVar5 = GetPoliticalID(param_1 + 0x15b8);
                iVar2 = *piVar5;
                uVar6 = (unsigned)(*(int*)(iVar2 + 8 + iVar7) + *(int*)(iVar2 + 4 + iVar7)) >> 1;
                if (uVar6 != *(unsigned*)(iVar2 + iVar7 + 0xc)) {
                    iVar2 = *(int*)(uVar6 * 0x30 + 4 + *piVar4);
                    if (param_2 <= 1e-06f) fVar10 = 0.0f;
                    else fVar10 = fVar9 / param_2;
                    fVar10 = (1.0f - fVar10) * *(float*)&DAT_01550b1c + (1.0f - *(float*)&DAT_01550b1c);
                    fVar11 = *(float*)(iVar2 + 0x48) * fVar10;
                    *(float*)(iVar2 + 0x48) = fVar11;
                    *(float*)(iVar2 + 0x4c) = param_2 - fVar11;
                    *(float*)(iVar2 + 0x88) = *(float*)(iVar2 + 0x88) * fVar10;
                    *(float*)(iVar2 + 0x9c) = *(float*)(iVar2 + 0x9c) * fVar10;
                }
                iVar7 = iVar7 + 0x104;
                iVar8 = iVar8 + -1;
            } while (iVar8 != 0);
        }
    }
}

// @ 0x009b8650
void __fastcall FUN_009b8650(int param_1, int dummy, float param_2)
{
    (void)dummy;
    param_2 = param_2 - *(float*)(*(int*)(param_1 + 0x2e4) + 0x48);
    if (1e-06f < param_2) {
        *(float*)(*(int*)(param_1 + 0x2e4) + 0x4c) = param_2;
        int* piVar2 = GetPoliticalID(param_1 + 0x15b8);
        int iVar1 = (piVar2[1] - *piVar2) / 0x104;
        int ebp = 0;
        while (iVar1 != 0) {
            int esi = *GetPoliticalID(param_1 + 0x15b8) + ebp;
            int* piVar2b = FUN_00ff3ba0(esi);
            int iVar3 = (piVar2b[1] - *piVar2b) / 0x38;
            if (iVar3 != 0) {
                int iVar4 = 0;
                do {
                    piVar2b = FUN_00ff3ba0(esi);
                    int* p = (int*)(iVar4 + *piVar2b);
                    iVar4 = iVar4 + 0x38;
                    iVar3 = iVar3 + -1;
                    *(float*)(*p + 0x4c) = param_2;
                } while (iVar3 != 0);
            }
            ebp = ebp + 0x104;
            iVar1 = iVar1 + -1;
        }
    }
}

// @ 0x009b8720
void nSPCreatureAnim::creature_instance_data_s009b_8720::FUN_009b8720(float param_2)
{
    FUN_009b8250(param_2);
    if (*(char*)(*(int*)this + 0x3f4) != 0) {
        FUN_009b83b0(param_2);
    } else {
        FUN_009b8650(param_2);
    }
}

// @ 0x009b8760
void nSPCreatureAnim::creature_instance_data_s009b_8720::FUN_009b8760(float param_2)
{
    float fVar1 = f_194;
    float fVar9 = (float)(1.0 / ((double)param_2 + *(double*)&DAT_014470a0));
    float fVar2 = f_154;
    float fVar3 = f_198;
    float fVar4 = f_158;
    // first quaternion (input) and its rectifying-output vector
    float q1_20 = ((fVar1 * fVar4 + f_14c * f_1a0) - f_150 * f_19c) + fVar2 * fVar3;
    float q1_1c = ((fVar3 * fVar4 + f_19c * f_14c) + f_150 * f_1a0) - fVar2 * fVar1;
    float q1_14 = ((fVar4 * f_1a0 - fVar1 * f_14c) - fVar3 * f_150) - fVar2 * f_19c;
    float q1_18 = ((f_19c * fVar4 - fVar3 * f_14c) + f_150 * fVar1) + fVar2 * f_1a0;
    // scaled increments (computed before the call; the call may reuse their slots)
    float s_x = (f_184 + f_13c) * fVar9;
    float s_y = (f_188 + f_140) * fVar9;
    float s_z = (f_18c + f_144) * fVar9;
    float m1[4];                       // first call output (x,y,z,w)
    FUN_009b4ba0(m1, &q1_20, 0);
    float fA = f_40;
    float fB = f_3c;
    float fC = f_48;
    float fD = f_44;
    float fVar10 = f_58;
    float fVar13 = m1[2] * (1.0f - (fB * fB + fA * fA) * 2.0f);
    float fVar11 = m1[1] * ((fD * fA - fB * fC) * 2.0f);
    float fVar5 = f_54;
    float fVar6 = f_50;
    float fVar7 = f_90;
    float fVar12 = f_4c * fVar6;
    float fVar8 = f_4c;
    walk_linear_x =
        (((-(fVar6 * fVar10) + f_4c * fVar5) * f_94 +
          (-(fVar6 * fVar6) + -(fVar5 * fVar5)) * f_8c) +
         (fVar12 - -(fVar5 * fVar10)) * fVar7) * 2.0f + f_8c;
    walk_linear_y =
        (((fVar6 * fVar5 - -(fVar8 * fVar10)) * f_94 +
          (-(fVar8 * fVar8) + -(fVar5 * fVar5)) * fVar7) +
         (fVar12 + -(fVar5 * fVar10)) * f_8c) * 2.0f + fVar7;
    float fVar10b = f_4c;
    float fVar5b = f_58;
    float fVar6b = f_48;
    float fVar7b = f_54;
    float fVar8b = f_40;
    float q2_20 = ((f_3c * fVar5b - fVar10b * fVar6b) + f_50 * f_44) - fVar7b * fVar8b;
    float fVar12b = f_3c;
    float q2_1c = ((fVar8b * fVar5b - f_44 * fVar10b) - f_50 * fVar6b) + fVar7b * fVar12b;
    float q2_18 = ((fVar8b * fVar10b + f_44 * fVar5b) - f_50 * fVar12b) - fVar7b * fVar6b;
    float q2_14 = ((fVar8b * f_50 + fVar7b * f_44) + fVar10b * fVar12b) + fVar6b * fVar5b;
    float m2[4];                       // second call output (x,y,z,w)
    FUN_009b4ba0(m2, &q2_20, 0);
    float fVar10c = f_40;
    float fVar5c = f_3c;
    walk_angular =
        (m2[3] * fVar9) *
        (m2[1] * ((f_44 * fVar10c - fVar5c * f_48) * 2.0f) +
         (m2[2] * (1.0f - (fVar5c * fVar5c + fVar10c * fVar10c) * 2.0f) +
          ((fVar5c * f_44 + fVar10c * f_48) * 2.0f) * m2[0]));
    float fVar10d = (f_108 * s_z + f_104 * s_y) + f_100 * s_x;
    float d_z = s_z - f_108 * fVar10d;
    float d_x = s_x - f_100 * fVar10d;
    float d_y = s_y - f_104 * fVar10d;
    int result;
    if ((d_x * d_x + d_y * d_y) + d_z * d_z > *(float*)&DAT_01550b18) {
        result = 1;
    } else if ((float)fabs(((((fB * fD + fA * fC) * 2.0f) * m1[0] + fVar13) + fVar11) *
                         (m1[2] * fVar9)) > *(float*)&DAT_01550b18) {
        result = 1;
    } else {
        result = 0;
    }
    flag_261 = result;
}

// @ 0x009b8d50
void nSPCreatureAnim::creature_instance_data_s009b_8720::FUN_009b8d50(float param_2)
{
    if (1e-06f < param_2) {
        float local_c = accum_1660;
        float uVar1 = accum_166c;
        float local_8 = accum_1664;
        float local_4 = accum_1668;
        FUN_009b7da0(param_2);
        anim_15b8.FUN_009d3200(&accum_1660, accum_166c);
        FUN_009b7c00(param_2, &local_c, uVar1);
    }
    anim_15b8.FUN_009d3f70((Obj2*)this);
    anim_15b8.FUN_009d32d0();
    float f = gait_2f8.FUN_009dbd50();
    f = anim_15b8.FUN_009d3a20((Obj2*)this, f, (int)&root_1670, root_167c);
    anim_15b8.FUN_009d3b50(f);
    anim_15b8.FUN_009d6700(param_2);
}

// @ 0x009b8e40
void nSPCreatureAnim::creature_instance_data_s009b_8720::FUN_009b8e40(float param_2)
{
    (void)param_2;
    Vector108* v = anim_15b8.FUN_00a09f50();
    unsigned n = (unsigned)(((char*)v->end - (char*)v->begin) / 0x108);
    if (n == 0) return;
    char* base = (char*)v->begin;
    for (unsigned i = 0; i != n; ++i) {
        GaitGroup* p = (GaitGroup*)(base + i * 0x108);
        BoneInst* bone = &((BoneInst*)mpBone_2e4)[p->i58];
        float fVar1 = bone->f4c;
        if (fVar1 > 0.0f) {
            float local_c = p->vx * requested_scale;
            float local_8 = p->vy * requested_scale;
            float local_4 = p->vz * requested_scale;
            bone->Bone_IntegrateVelocity(fVar1, &local_c, (float*)p->f24_0);
            if (DAT_015509e0 != 0) {
                bone->hA0.FUN_0099c4a0(
                    (int)p->i44, (int)p->i48, p->f4c, p->f54);
            }
        }
    }
}

// @ 0x009b8f40
void nSPCreatureAnim::creature_instance_data_s009b_8720::FUN_009b8f40(float param_2)
{
    if (DAT_015509ec != 0 && *(char*)(*(int*)this + 0x3f5) == 0) {
        Vector30* v = anim_15b8.FUN_00ad2800();
        if (v != 0 && 3u <= (unsigned)(((char*)v->end - (char*)v->begin) / 0x30)) {
            Vector104* g = anim_15b8.GetPoliticalID();
            unsigned n = (unsigned)(((char*)g->end - (char*)g->begin) / 0x104);
            for (unsigned i = 0; i < n; ++i)
                ((BoneGoal*)((char*)g->begin + i * 0x104))->FUN_009d63e0(param_2);
        }
    }
}

// @ 0x009b8fd0
void nSPCreatureAnim::creature_instance_data_s009b_8720::FUN_009b8fd0(float* param_2, float* param_3)
{
    float fVar2 = ((f_20 * f_108 + f_1c * f_104) + f_18 * f_100);    if (fVar2 <= f_10c) {
        *param_2 = fVar2;
        *param_3 = *(float*)&DAT_01485720;
        return;
    }
    *param_2 = f_10c;
    float t = 1.0f - ((fVar2 - f_10c) /
                      (*(float*)(*(int*)this + 0x36c) * requested_scale)) *
                         *(float*)&DAT_01550d64;
    float lo = 0.0f;
    float* p = (t > lo) ? &t : &lo;
    *param_3 = *p;
}

// @ 0x009b9090
void nSPCreatureAnim::creature_instance_data_s009b_8720::FUN_009b9090()
{
    Vector108* v = anim_15b8.FUN_00a09f50();
    if (v == 0) return;
    int n = (int)(((char*)v->end - (char*)v->begin) / 0x108);
    if (n <= 0) return;
    int off = 0;
    int cnt = n;
    do {
        char* b = (char*)v->begin;
        int bi = *(int*)(off + b + 0x58);
        if (bi != -1) {
            GoalBone* bone = (GoalBone*)((char*)mpBone_2e4 + bi * 0x2bc);
            if (bone->f48 <= 0.0f) {
                float ddz = bone->goal_z - bone->cur_z;
                float ddx = bone->goal_x - bone->cur_x;
                float ddy = bone->goal_y - bone->cur_y;
                float d2 = ddy * ddy + ddz * ddz + ddx * ddx;
                float l2 = *(float*)&DAT_015509f8 * *(float*)&DAT_015509f8;
                if (d2 <= l2 * *(float*)&DAT_014853e0) {
                    if (l2 >= d2) {
                        bone->goal_x = bone->cur_x;
                        bone->goal_y = bone->cur_y;
                        bone->goal_z = bone->cur_z;
                    } else {
                        float t = (float)sqrt(d2) - *(float*)&DAT_015509f8;
                        t = t / *(float*)&DAT_015509f8;
                        float u = *(float*)&DAT_01485720 - t;
                        bone->goal_x = bone->cur_x * u + bone->goal_x * t;
                        bone->goal_y = bone->cur_y * u + bone->goal_y * t;
                        bone->goal_z = bone->cur_z * u + bone->goal_z * t;
                    }
                    bone->flag_38 = true;
                }
            }
        }
        off += 0x108;
    } while (--cnt != 0);
}

// @ 0x009b9250
float* nSPCreatureAnim::creature_instance_data_s009b_8720::FUN_009b9250(float* param_2, float* param_3)
{
    float py = param_3[1];
    float px = param_3[0];
    param_2[2] = 0.0f;
    param_2[1] = 0.0f;
    param_2[0] = 0.0f;
    float len = (float)sqrt(px * px + py * py);
    if (len <= *(float*)&DAT_014471fc) {
        param_2[0] = 0.0f;
        param_2[1] = 0.0f;
        param_2[2] = 0.0f;
        return param_2;
    }
    FUN_009b3970(&len);
    float s = (float)sin(len);
    float c = (float)cos(len);
    float k = *(float*)&DAT_01550d68;
    if (param_3[1] < 0.0f)
        k = *(float*)&DAT_01485720;
    float f1 = *(float*)&DAT_01485720;
    float inv = f1 / len;
    param_2[0] = (inv * param_3[0]) * *(float*)&DAT_01550d68 * s;
    param_2[1] = (inv * param_3[1] * k) * s;
    param_2[2] = (c - f1) * inv;
    return param_2;
}

// @ 0x009b9340
float* nSPCreatureAnim::AniDyn::FUN_009b9340(float* param_1, int** param_2, SpatialObject* param_3, float param_4)
{
    param_1[2] = 0.0f;
    param_1[1] = 0.0f;
    param_1[0] = 0.0f;
    float minimum = *(float*)&DAT_01448874;
    float orient_w = param_3->orient_w;
    float ext_lz = param_3->extent_lower_z;
    int* v = *param_2;
    int* core = (int*)v[0];
    float ext_lx = param_3->extent_lower_x;
    float ext_ux = param_3->extent_upper_x;
    float scale = *(float*)(v[1] + 0x70);
    float lc = *(float*)(core + 0x10c) * scale;
    float l8 = *(float*)(core + 0x110) * scale;
    float l4 = *(float*)(core + 0x114) * scale;

    float lo = minimum;
    float* p = (l4 > minimum) ? &l4 : &lo;
    float sel = *p;
    float sel2 = sel * *(float*)&DAT_01485544;
    float hi = *(float*)&DAT_013eb960;
    float* p2 = (sel2 > hi) ? &sel2 : &hi;
    float chosen = *p2;
    float fpr = FUN_00c37030((int)param_3) * scale;
    float* p3 = (fpr <= chosen) ? &chosen : &fpr;
    float ratio = *p3 / chosen;
    float one = *(float*)&DAT_01485720;
    float* p4 = (one > ratio) ? &ratio : &one;
    float factor = FUN_009d3530();
    factor = FUN_009ce700(factor) * *p4;

    FUN_009d00a0(&lc, param_3);
    float dt = factor * param_4;

    float a = ((lc * *(float*)&DAT_01550d74) * l4) * ext_lx;
    float b = ((l8 * *(float*)&DAT_01550d70) * sel) * ext_ux;
    float c = ((ext_lz * *(float*)&DAT_01550d78 + l4 * orient_w) * *(float*)&DAT_01550d6c) * sel;

    param_1[0] = ((*(float*)&DAT_01550d08 * c + *(float*)&DAT_01550d14 * l8 * ext_lx) +
                  *(float*)&DAT_01550d20 * a) * dt;
    param_1[1] = ((*(float*)&DAT_01550d0c * c + *(float*)&DAT_01550d18 * b +
                   *(float*)&DAT_01550d24 * a)) * dt;
    param_1[2] = ((*(float*)&DAT_01550d10 * c + *(float*)&DAT_01550d1c * b +
                   *(float*)&DAT_01550d28 * a)) * dt;
    return param_1;
}

// @ 0x009b95d0
void __fastcall UpdateRootPosition(int* inst, int* unused, float dt, int* owner, float scale)
{
    Body* body = *(Body**)((char*)inst + 0);
    float vx, vy, vz;
    if (*(char*)((char*)inst + 0x24) == 0) {
        float* a = (float*)FUN_009b9250((char*)body + 0x10);
        float* b = (float*)FUN_009b9340((void*)0, (int)inst, (int)owner, scale);
        vx = b[0] + a[0];
        vy = b[1] + a[1];
        vz = b[2] + a[2];
    } else {
        double f = FUN_009d3530((char*)owner + 0x15b8);
        float* q = (float*)FUN_009d0460((void*)0, (float)f);
        vx = q[0];
        vy = q[1];
        vz = q[2];
    }
    int* b0 = *(int**)((char*)body + 0);
    if (body->mVelW <= 1e-06f) {
        float s = *(float*)((char*)body + 4);
        body->mVelX = (*(float*)((char*)b0 + 0x10c) * s + vx) * dt;
        body->mVelY = (*(float*)((char*)b0 + 0x110) * s + vy) * dt;
        body->mVelZ = (*(float*)((char*)b0 + 0x114) * s + vz) * dt;
        body->mVelW = dt;
    } else {
        float inv = 1.0f / body->mVelW;
        body->mVelX = body->mVelX + (inv * body->mVelX + vx) * dt;
        body->mVelY = body->mVelY + (inv * body->mVelY + vy) * dt;
        body->mVelZ = body->mVelZ + (inv * body->mVelZ + vz) * dt;
        body->mVelW = body->mVelW + dt;
    }
    if (0.0f < dt) {
        unsigned int idx = *(unsigned int*)(b0 + 0x1f8);
        unsigned char* p = (unsigned char*)(*(int*)((char*)body + 4) + 0x1b8 + ((idx & 0x7fffffff) >> 2));
        *p = *p | (unsigned char)(2 << ((idx * 2) & 7));
    }
}

// @ 0x009b97c0
int* BuildOrientation(int* out, int* inst, char* so, void* self, float scale)
{
    Quat ext;
    ext.x = *(float*)(so + 0x3c);
    ext.y = *(float*)(so + 0x40);
    ext.z = *(float*)(so + 0x44);
    int* b = *(int**)((char*)inst + 0);
    float s = *(float*)(*(int*)((char*)((char*)b + 0)) + 0x70);
    Quat ax;
    ax.x = (float)b[0x10c / 4] * s;
    ax.y = (float)b[0x110 / 4] * s;
    ax.z = (float)b[0x114 / 4] * s;
    float lim = (ext.z <= 0.1f) ? 0.1f : ext.z;
    float r = lim * 0.75f;
    if (r <= 0.01f)
        r = 0.01f;
    float dia = GetFootprintRadius(so) * 2.0f;
    if (r <= dia)
        r = 0;
    if (r != 0) { /* keep r */ }
    float ratio = (r != 0 ? r : dia) / r;
    if (ratio > 1.0f)
        ratio = 1.0f;
    double t = FUN_009d3530((char*)self + 0x15b8);
    double st = FUN_009ce700((char*)self + 0x15b8);
    (void)t; (void)st;
    float k = ratio;
    float px, py, pz;
    FUN_009d0a40((void*)&px, so);
    (void)py;
    ext.x = ((ext.x * g_1550d80) * k) * ext.x;
    ext.y = ((ext.y * g_1550d84) * k) * ext.y;
    ext.z = ((ext.z * g_1550d7c) * k) * ext.z;
    float lo = -g_1550d04;
    if (ext.x < lo) ext.x = lo;
    if (g_1550d04 < ext.x) ext.x = g_1550d04;
    if (ext.y < lo) ext.y = lo;
    if (g_1550d04 < ext.y) ext.y = g_1550d04;
    if (ext.z < lo) ext.z = lo;
    if (g_1550d04 < ext.z) ext.z = g_1550d04;
    out[0] = (int)0;
    out[0] = 0;
    return out;
}

// @ 0x009b9a00
float* QuatFromAxisAngle(float angle, float out[4], float unused)
{
    out[0] = g_1550d2c;
    out[1] = g_1550d30;
    out[2] = g_1550d34;
    out[3] = g_1550d38;
    if (fabsf(angle) > 1e-06f) {
        FUN_009b39e0(angle);
        float s = g_1550d38 * 0.5f;
        float sn = (float)sin((double)s);
        float cs = (float)cos((double)s);
        out[0] = g_1550d14 * sn;
        out[1] = g_1550d18 * sn;
        out[2] = g_1550d1c * sn;
        out[3] = cs;
    }
    return out;
}

// @ 0x009b9ac0
void __fastcall FUN_009b9ac0(int* self, int* inst, int h, int prim, float dt)
{
    Body* body = *(Body**)((char*)inst + 0);
    Quat a;
    BuildOrientation((int*)&a, inst, (char*)prim, self, dt);
    Quat b;
    QuatFromAxisAngle(*(float*)((char*)self + 0x15c4), (float*)&b, 0.0f);
    Quat q = qmul(b, a);
    if (body->mBlend <= 1e-06f) {
        Quat w = qmul(a, *(Quat*)((char*)body + 0));
        Quat n;
        FUN_0099cae0((void*)&n, (void*)&w, 0);
        body->mVelX = n.x * dt;
        body->mVelY = n.y * dt;
        body->mVelZ = n.z * dt;
        body->mVelW = n.w * dt;
        body->mBlend = dt;
    } else {
        float len = sqrtf(((body->mVelX * body->mVelX + body->mVelY * body->mVelY) +
                           body->mVelZ * body->mVelZ) + body->mVelW * body->mVelW);
        if (len != 0.0f) {
            float inv = g_1485720 / len;
            body->mVelX = body->mVelX * inv;
            body->mVelY = body->mVelY * inv;
            body->mVelZ = body->mVelZ * inv;
            body->mVelW = body->mVelW * inv;
        }
        Quat cur = *(Quat*)((char*)body + 0x0);
        Quat n;
        FUN_0099cae0((void*)&n, (void*)&cur, 0);
        n.x = n.x * dt;
        n.y = n.y * dt;
        n.z = n.z * dt;
        n.w = n.w * dt;
        if (0.0f <= ((body->mVelX * n.x + body->mVelY * n.y) + body->mVelZ * n.z) + body->mVelW * n.w) {
            body->mVelX = body->mVelX + n.x;
            body->mVelY = body->mVelY + n.y;
            body->mVelZ = body->mVelZ + n.z;
            body->mVelW = body->mVelW + n.w;
        } else {
            body->mVelX = body->mVelX - n.x;
            body->mVelY = body->mVelY - n.y;
            body->mVelZ = body->mVelZ - n.z;
            body->mVelW = body->mVelW - n.w;
        }
        body->mBlend = body->mBlend + dt;
    }
    if (0.0f < dt) {
        unsigned int idx = *(unsigned int*)((char*)body + 4 - 4);
        (void)idx;
        unsigned int link = *(unsigned int*)(*(int*)((char*)body + 0) + 0x1f8);
        unsigned char* p = (unsigned char*)(*(int*)((char*)body + 4) + 0x1b8 + ((link & 0x7fffffff) >> 2));
        *p = *p | (unsigned char)(2 << ((link * 2) & 7));
    }
}

// @ 0x009ba040
void __fastcall UpdateRoots(char* self, void* unused, float param)
{
    if (!(g_14471fc < param) || *(char*)(self + 0x262) == 0)
        return;
    {
        int* p = (int*)GetPoliticalID(self + 0x15b8);
        int n = (p[1] - p[0]) / 0x104;
        if (n <= 0)
            return;
        {
            int stride = 0;
            do {
                p = (int*)GetPoliticalID(self + 0x15b8);
                int base = p[0];
                p = (int*)FUN_00ff3ba0(self + 0x15b8);
                int cnt = (p[1] - p[0]) / 0x38;
                if (0 < cnt) {
                    int off = 0;
                    do {
                        p = (int*)FUN_00ff3ba0(self + 0x15b8);
                        int node = *(int*)(p[0] + off);
                        int ptr = p[0] + off;
                        if (0.0f < *(float*)(node + 0x4c) &&
                            ((*(unsigned int*)(*(int*)(node + 0)) >> 4 & 1) == 0)) {
                            if (g_15509e4 != 0)
                                FUN_009b95d0((void*)ptr, base + stride, 0, 1.0f);
                            if (g_15509e8 != 0)
                                FUN_009b9ac0((void*)ptr, base + stride, 0);
                        }
                        off += 0x38;
                        --cnt;
                    } while (cnt != 0);
                }
                stride += 0x104;
                --n;
            } while (n != 0);
        }
    }
}

// @ 0x009ba180
int __fastcall FindRootChain(int* self, int* out, int a, int b, int node, char dbg, char hasParent, char checkKids, char a9, char a10, char a11)
{
    if (a10 == 0 && (*(unsigned char*)(node + 0x154) & 4) != 0)
        return 0;
    if (a11 == 0) {
        for (int n = *(int*)(node + 0x214); n != 0; n = *(int*)(n + 0x214)) {
            if ((*(unsigned char*)(n + 0x154) & 4) != 0)
                return 0;
        }
    }
    if (checkKids != 0) {
        unsigned int cnt = *(unsigned int*)(node + 0x208);
        unsigned int i = 0;
        if (cnt != 0) {
            int k = *(int*)(node + 0x204) * 0x468 + 0x150 + *(int*)((char*)self + 900);
            do {
                if (*(int*)(k + 0xb8) > 0)
                    return 0;
                if (FUN_009b3110((void*)k) != 0)
                    return 0;
                ++i;
                k += 0x468;
            } while (i < cnt);
        }
    }
    unsigned int nflags = 0;
    int* walk = (int*)(node + 0x158);
    while (nflags < 0x20) {
        if (*walk == 0)
            break;
        ++nflags;
        ++walk;
    }
    if (checkKids == 0 && 0 < nflags)
        return 0;
    if (dbg != 0) {
        out[0] = *(int*)(node + 0x1f8);
        out[1] = -1;
        return 1;
    }
    return 0;
}

// @ 0x009ba4c0
namespace nSPCreatureAnim {
bool CreateWiggle(creature_anim* anim, unsigned index, wiggle_data* out, int a4, int a5, int a6, int a7, int a8, int a9)
{
    if (index < (unsigned)(anim->anim_bodies_end - anim->anim_bodies_begin)) {
        wiggle_data w;
        w.pos.x = w.pos.y = w.pos.z = 0.0f;
        w.rot.x = w.rot.y = w.rot.z = 0.0f;
        w.rot.w = 1.0f;
        anim_body_data* body = &anim->anim_bodies_begin[index];
        if (CalcWiggle(anim, body, &w, a4, a5, a6, a7, a8, a9)) {
            out->CopyFrom(&w);
            return true;
        }
        out->body_a = -1;
        out->body_b = -1;
        out->body_c = -1;
    }
    return false;
}
}  // namespace nSPCreatureAnim

// @ 0x009ba590
namespace nSPCreatureAnim {
void ComputeWiggle(creature_anim* anim, wiggle_data* w)
{
    if (w->body_a == -1 || w->body_b == -1)
        return;

    anim_body_data* a = &anim->anim_bodies_begin[w->body_a];
    anim_body_data* b = &anim->anim_bodies_begin[w->body_b];

    checkerlib::vector_3_s009b_a4c0 delta;
    delta.x = a->rest_center__SCALABLE.x - b->rest_center__SCALABLE.x;
    delta.y = a->rest_center__SCALABLE.y - b->rest_center__SCALABLE.y;
    delta.z = a->rest_center__SCALABLE.z - b->rest_center__SCALABLE.z;

    checkerlib::vector_4_s009b_a4c0 conj_b;
    conj_b.x = -b->rest_orientation_q.x;
    conj_b.y = -b->rest_orientation_q.y;
    conj_b.z = -b->rest_orientation_q.z;
    conj_b.w = b->rest_orientation_q.w;

    checkerlib::vector_4_s009b_a4c0 rot_a = a->rest_orientation_q;

    checkerlib::vector_3_s009b_a4c0 v;
    checkerlib::QuaternionVectorTransform(&v, &conj_b, &delta);
    w->pos = v;

    checkerlib::vector_4_s009b_a4c0 q;
    q.x = ((conj_b.w * rot_a.x + rot_a.w * conj_b.x) - rot_a.y * conj_b.z)
        + rot_a.z * conj_b.y;
    q.y = ((conj_b.w * rot_a.y + conj_b.z * rot_a.x) + conj_b.y * rot_a.w)
        - rot_a.z * conj_b.x;
    q.z = ((conj_b.z * rot_a.w - conj_b.y * rot_a.x) + conj_b.w * rot_a.z)
        + rot_a.y * conj_b.x;
    q.w = ((conj_b.w * rot_a.w - rot_a.x * conj_b.x) - conj_b.y * rot_a.y)
        - conj_b.z * rot_a.z;
    w->rot = q;
}
}  // namespace nSPCreatureAnim

// @ 0x009ba7d0
namespace nSPCreatureAnim {
void GoalStateInit(creature_instance_data_s009b_a4c0* c, goal_state* st, char flag)
{
    creature_body_instance_data_s009b_a4c0* body = &c->Bodies.mpBegin[st->def->bidx];

    checkerlib::vector_3_s009b_a4c0 local;
    const checkerlib::vector_3_s009b_a4c0* src;
    if (flag != 0) {
        float s = c->requested_scale;
        const checkerlib::vector_3_s009b_a4c0& rc = body->static_data->rest_center__SCALABLE;
        local.x = rc.x * s;
        local.y = rc.y * s;
        local.z = rc.z * s;
        src = &local;
    } else {
        src = &body->pos;
    }

    checkerlib::vector_3_s009b_a4c0 v;
    v.x = src->x;
    v.y = src->y;
    v.z = src->z;

    st->vel.x = 0.0f;
    st->vel.y = 0.0f;
    st->vel.z = 0.0f;

    checkerlib::vector_3_s009b_a4c0* r = checkerlib::QuaternionVectorTransform(&local, &c->orientation, &v);

    st->pos.x = r->x + c->position.x;
    st->pos.y = r->y + c->position.y;
    st->pos.z = r->z + c->position.z;
    st->prev = st->pos;
}
}  // namespace nSPCreatureAnim

// @ 0x009ba8d0
namespace nSPCreatureAnim {
bool GoalStateIsActive(creature_instance_data_s009b_a4c0* c, goal_state* st, float t)
{
    goal_def* def = st->def;
    unsigned bidx = def->bidx;
    creature_body_instance_data_s009b_a4c0* body = &c->Bodies.mpBegin[(int)bidx];

    if (!st->reset) {
        if (body->goal_time >= t)
            return false;
        if ((body->static_data->flags_154 >> 2) & 1)
            return false;
    }

    int parent = def->parent_bidx;
    if (parent == -1)
        return true;
    if ((int)bidx == -1)
        return true;
    if ((int)bidx == parent)
        return true;

    for (;;) {
        uint32_t flags = g_GoalUseAltFlags ? body->static_data->flags_150
                                           : body->static_data->flags_154;
        if ((flags >> 3) & 1)
            return true;
        if (body->goal_blend > 0.0f)
            return false;
        if (body->goal_time > 0.0f && !st->reset)
            return false;
        bidx = (unsigned)body->static_data->parent_bidx;
        body = &c->Bodies.mpBegin[(int)bidx];
        if ((int)bidx == -1)
            return true;
    }
}
}  // namespace nSPCreatureAnim

// @ 0x009ba990
namespace nSPCreatureAnim {
void creature_instance_data_s009b_a4c0::UpdateGoalSpring(goal_state* st, int nSteps, float dt, float t, float rate)
{
    goal_def* def = st->def;
    if (def->bidx >= Bodies.size())
        return;
    creature_body_instance_data_s009b_a4c0* bodies = Bodies.mpBegin;
    creature_body_instance_data_s009b_a4c0* body = &bodies[def->bidx];
    if (!GoalStateIsActive(this, st, t)) {
        st->initialized = false;
        return;
    }

    checkerlib::vector_3_s009b_a4c0 lpos;
    checkerlib::vector_4_s009b_a4c0 lrot;
    if (body->goal.pos_weight > 0.0f && body->goal.rot_weight > 0.0f) {
        float inv = kOne / body->goal.pos_weight;
        float px = body->goal.pos.x * inv;
        float py = body->goal.pos.y * inv;
        float pz = body->goal.pos.z * inv;
        inv = kOne / body->goal.rot_weight;
        float rx = body->goal.rot.x * inv;
        float ry = body->goal.rot.y * inv;
        float rz = body->goal.rot.z * inv;
        float rw = body->goal.rot.w * inv;
        lpos.x = px; lpos.y = py; lpos.z = pz;
        lrot.x = rx; lrot.y = ry; lrot.z = rz; lrot.w = rw;
    } else if (def->parent_bidx == -1) {
        creature_body_static_data_s009b_a4c0* sd = body->static_data;
        float s = requested_scale;
        float px = sd->rest_center__SCALABLE.x * s;
        float py = sd->rest_center__SCALABLE.y * s;
        float pz = sd->rest_center__SCALABLE.z * s;
        lrot = sd->rest_orientation_q;
        lpos.x = px; lpos.y = py; lpos.z = pz;
    } else {
        creature_body_instance_data_s009b_a4c0* parent = &bodies[def->parent_bidx];
        checkerlib::vector_3_s009b_a4c0 tmp;
        checkerlib::vector_3_s009b_a4c0* r = checkerlib::QuaternionVectorTransform(&tmp, &parent->orientation, &def->offset);
        float s = requested_scale;
        lpos.x = parent->pos.x + r->x * s;
        lpos.y = parent->pos.y + r->y * s;
        lpos.z = parent->pos.z + r->z * s;
        lrot = checkerlib::QuaternionProduct_s009b_a4c0(parent->orientation, def->rot);
    }

    checkerlib::vector_3_s009b_a4c0 target;
    {
        checkerlib::vector_3_s009b_a4c0 tmp;
        checkerlib::vector_3_s009b_a4c0* r = checkerlib::QuaternionVectorTransform(&tmp, &orientation, &lpos);
        target.x = position.x + r->x;
        target.y = position.y + r->y;
        target.z = position.z + r->z;
    }

    if (!st->initialized) {
        GoalStateInit(this, st, 1);
        st->initialized = true;
    }

    float maxDist;
    if (st->def->parent_bidx == -1)
        maxDist = g_GoalSpringMaxDist;
    else
        maxDist = (st->def->max_dist * requested_scale) * kGoalMaxDistScale;

    checkerlib::vector_3_s009b_a4c0 p;
    p.x = st->pos.x;
    p.y = st->pos.y;
    p.z = st->pos.z;
    if (nSteps > 0) {
        float maxDist2 = maxDist * maxDist;
        do {
            float ax = (target.x - st->pos.x) * g_GoalSpringK - st->vel.x * g_GoalSpringDamp;
            float az = ((target.z - st->pos.z) * g_GoalSpringK - st->vel.z * g_GoalSpringDamp) + g_GoalGravity;
            float ay = (target.y - st->pos.y) * g_GoalSpringK - st->vel.y * g_GoalSpringDamp;
            float vx = st->vel.x + ax * dt;
            float vz = st->vel.z + az * dt;
            st->vel.y = ay * dt + st->vel.y;
            st->vel.z = vz;
            st->vel.x = vx;
            p.x = st->vel.x * dt + st->pos.x;
            p.y = st->pos.y + st->vel.y * dt;
            p.z = st->pos.z + st->vel.z * dt;
            float dx = p.x - target.x;
            float dy = p.y - target.y;
            float dz = p.z - target.z;
            float l2 = (dx * dx + dy * dy) + dz * dz;
            if (l2 > maxDist2) {
                float inv = 1.0f / sqrtf(l2);
                float nz = dz * inv;
                float ny = dy * inv;
                float nx = inv * dx;
                p.z = nz * maxDist + target.z;
                p.x = nx * maxDist + target.x;
                p.y = ny * maxDist + target.y;
                float v2 = (st->vel.x * st->vel.x + st->vel.y * st->vel.y) + st->vel.z * st->vel.z;
                float dot = (st->vel.z * nz + st->vel.y * ny) + st->vel.x * nx;
                if (v2 > kMinSpeed2 && dot > kZero) {
                    float f = dot / sqrtf(v2);
                    float fx = f * st->vel.x;
                    float fy = st->vel.y * f;
                    float fz = st->vel.z * f;
                    st->vel.y = st->vel.y - fy;
                    st->vel.x = st->vel.x - fx;
                    st->vel.z = st->vel.z - fz;
                }
            }
            st->prev = st->pos;
            st->pos.x = p.x;
            st->pos.y = p.y;
            st->pos.z = p.z;
        } while (--nSteps);
    }

    checkerlib::vector_3_s009b_a4c0 d;
    d.x = p.x - position.x;
    d.y = p.y - position.y;
    d.z = p.z - position.z;
    checkerlib::vector_3_s009b_a4c0 g = checkerlib::QuaternionVectorTransformInverse_s009b_a4c0(orientation, d);
    if (g_GoalClampAboveGround != 0 && 0.0f > g.z)
        g.z = 0.0f;

    if (!(t > body->goal_time) && !st->reset)
        return;
    if (st->reset) {
        body->goal_blend = t * rate;
        body->goal_time = 0.0f;
        if (body->goal_blend > 0.0f) {
            float w = body->goal_blend;
            body->goal.pos.x = w * g.x;
            body->goal.pos.y = w * g.y;
            body->goal.pos.z = w * g.z;
            body->goal.pos_weight = body->goal_blend;
            w = body->goal_blend;
            body->goal.rot.x = w * lrot.x;
            body->goal.rot.y = w * lrot.y;
            body->goal.rot.z = w * lrot.z;
            body->goal.rot.w = w * lrot.w;
            body->goal.rot_weight = body->goal_blend;
            MarkBodyGoal(body);
        }
        return;
    }
    float w = (t - body->goal_time) * rate + body->goal_blend;
    body->goal_blend = w;
    if (w > 0.0f) {
        if (t > body->goal.pos_weight) {
            body->goal.pos.x = w * g.x + body->goal.pos.x;
            body->goal.pos.z = w * g.z + body->goal.pos.z;
            body->goal.pos.y = body->goal.pos.y + w * g.y;
            body->goal.pos_weight = body->goal.pos_weight + body->goal_blend;
            MarkBodyGoal(body);
        }
        if (t > body->goal.rot_weight) {
            float b = body->goal_blend;
            body->goal.rot.x = body->goal.rot.x + b * lrot.x;
            body->goal.rot.y = b * lrot.y + body->goal.rot.y;
            body->goal.rot.z = b * lrot.z + body->goal.rot.z;
            body->goal.rot.w = b * lrot.w + body->goal.rot.w;
            body->goal.rot_weight = body->goal.rot_weight + body->goal_blend;
            MarkBodyGoal(body);
        }
    }
}
}  // namespace nSPCreatureAnim

// @ 0x009bb4f0
namespace nSPCreatureAnim {
void creature_instance_data_s009b_b360::UpdateWiggles(float dt, float t)
{
    if (!wiggles_enabled) return;
    if (t == 0.0f) return;
    wiggle_timer += dt;
    const float& m = wiggle_timer > g_01550ab4 ? g_01550ab4 : wiggle_timer;
    float clamped = m;
    wiggle_timer = clamped;
    int count;
    float step;
    if (0.0f < dt) {
        if (g_01550c30 <= clamped) {
            step = g_01550c30;
            count = (int)(clamped / g_01550c30);
            wiggle_timer = (float)fmod((double)clamped, (double)g_01550c30);
        } else {
            step = clamped;
            count = 1;
            wiggle_timer = 0.0f;
        }
    } else {
        step = 0.0f;
        count = 0;
    }
    float weight = 1.0f;
    if (0.0f < hit_time && hit_time < g_0166c018)
        weight = 1.0f - (g_0166c018 - hit_time) / g_0166c018;
    UpdateHitWiggles(count, step, t, weight);
    if (static_data->dead) return;
    if (hit_time <= 0.0f) return;
    int n = (int)((char*)states_end - (char*)states_begin) / 0x2c;
    if (n != 0) {
        int left = n;
        unsigned int off = 0;
        do {
            UpdateGoalSpring((goal_state_s009b_b360*)((char*)states_begin + off), count, step, t, weight);
            off += 0x2c;
        } while (--left);
    }
}
}  // namespace nSPCreatureAnim

// @ 0x009bb910
namespace nSPCreatureAnim {
void __cdecl FinalizeCreatureGoals(creature_instance_data_s009b_b910* c)
{
    goal_pos_rot_s009b_b910& g160 = c->goal_0x160;
    if (g160.pos_weight > 0.0f)
    {
        g160.NormalizePos();
        g160.pos_weight = 1.0f;
    }

    goal_pos_rot_s009b_b910& d = c->walk_goal_delta;
    d.NormalizePos();
    d.pos += c->requested_pos - c->previous_requested_pos;
    d.pos_weight = 1.0f;

    goal_pos_rot_s009b_b910& g13c = c->goal_0x13c;
    g13c.NormalizePos();
    g13c.pos_weight = 1.0f;

    if (g160.rot_weight > 0.0f)
    {
        g160.NormalizeWeightedRot();
        g160.rot_weight = 1.0f;
    }
    else
    {
        g160.SetRotIdentity();
    }

    d.NormalizeRot();
    d.rot = checkerlib::QuaternionProduct_s009b_b910(checkerlib::QuaternionProductConjugate(c->requested_rot, c->previous_requested_rot), d.rot);
    d.rot_weight = 1.0f;

    g13c.NormalizeRot();
    g13c.rot_weight = 1.0f;

    goal_pos_rot_s009b_b910& g118 = c->goal_0x118;
    g118.NormalizePos();
    g118.pos_weight = 1.0f;
    g118.NormalizeRot();
    g118.rot_weight = 1.0f;
}
}  // namespace nSPCreatureAnim

// @ 0x009bc580
namespace nSPCreatureAnim {
void __cdecl FUN_009bc580(creature_instance_data_s009b_c580* c, float dt)
{
    if (c->field_114 <= 0.0f)
        c->anim_speed = 1.0f;
    else
        c->anim_speed = c->anim_speed / c->field_114;
    c->field_114 = 1.0f;

    const float speed = c->field_06c * c->anim_speed;
    c->requested_scale = (speed > 0.001f) ? speed : 0.001f;
    c->field_10c = c->F_9b6220(&c->center, &c->field_f4);

    checkerlib::vector_3_s009b_c580 dir;
    c->F_9b62c0(&dir, &c->center);
    c->direction = dir;

    const float dot = -((c->center.z * dir.z + c->center.y * dir.y) + c->center.x * dir.x);
    const float len = c->field_10c;
    c->new_center.x = c->center.x + (dir.x * dot + len * dir.x);
    c->new_center.y = c->center.y + (dir.y * dot + dir.y * len);
    c->new_center.z = c->center.z + (dir.z * dot + dir.z * len);

    if (1e-06f < dt) {
        const float inv = 1.0f / dt;
        const float vx = (c->center.x - c->prev_center.x) * inv;
        const float vy = (c->center.y - c->prev_center.y) * inv;
        const float vz = (c->center.z - c->prev_center.z) * inv;
        c->velocity.x = vx;
        c->velocity.y = vy;
        c->velocity.z = vz;

        const float sz = c->smooth_velocity.z * 0.8f + vz * 0.19999999f;
        const float sy = c->smooth_velocity.y * 0.8f + vy * 0.19999999f;
        c->smooth_velocity.x = c->smooth_velocity.x * 0.8f + vx * 0.19999999f;
        c->smooth_velocity.y = sy;
        c->smooth_velocity.z = sz;
        if ((c->smooth_velocity.x * c->smooth_velocity.x + c->smooth_velocity.y * c->smooth_velocity.y) +
            c->smooth_velocity.z * c->smooth_velocity.z < 1e-06f) {
            c->smooth_velocity.x = 0.0f;
            c->smooth_velocity.y = 0.0f;
            c->smooth_velocity.z = 0.0f;
        }

        c->rot_velocity = FUN_0099c310(&c->orientation, &c->smooth_velocity);

        const float t2z = c->velocity2.z * 0.8f +
                          ((c->smooth_velocity.z - c->smooth_velocity_prev.z) * inv) * 0.19999999f;
        const float t2y = c->velocity2.y * 0.8f +
                          ((c->smooth_velocity.y - c->smooth_velocity_prev.y) * inv) * 0.19999999f;
        c->velocity2.x = c->velocity2.x * 0.8f +
                         ((c->smooth_velocity.x - c->smooth_velocity_prev.x) * inv) * 0.19999999f;
        c->velocity2.y = t2y;
        c->velocity2.z = t2z;
        if ((c->velocity2.x * c->velocity2.x + c->velocity2.y * c->velocity2.y) +
            c->velocity2.z * c->velocity2.z < 1e-06f) {
            c->velocity2.x = 0.0f;
            c->velocity2.y = 0.0f;
            c->velocity2.z = 0.0f;
        }

        c->rot_velocity2 = FUN_0099c310(&c->orientation, &c->velocity2);

        const float a0 = c->orientation.x, a1 = c->orientation.y;
        const float a2 = c->orientation.z, a3 = c->orientation.w;
        const float b0 = c->orientation_b.x, b1 = c->orientation_b.y;
        const float b2 = c->orientation_b.z, b3 = c->orientation_b.w;
        c->rel_rotation.x = ((a0 * b3 - b0 * a3) + a1 * b2) - a2 * b1;
        c->rel_rotation.y = ((a1 * b3 - b1 * a3) - b2 * a0) + a2 * b0;
        c->rel_rotation.z = ((b1 * a0 - b2 * a3) - a1 * b0) + a2 * b3;
        c->rel_rotation.w = ((b1 * a1 + a2 * b2) + b0 * a0) + a3 * b3;

        c->prev_center = c->center;
        c->prev_velocity = c->velocity;
        c->smooth_velocity_prev = c->smooth_velocity;
        c->orientation_b = c->orientation;
    }
}
}  // namespace nSPCreatureAnim

// @ 0x009bcab0
namespace nSPCreatureAnim {
float* __cdecl FUN_009bcab0(creature_instance_data_s009b_c580* c, float w1, float w2)
{
    const int byteDiff = (int)((char*)c->mpEnd - (char*)c->mpBegin);
    const int count = byteDiff / 700;
    if (count == 0)
        return (float*)(int)(0x5d9f7391u * (uint32_t)byteDiff);

    float* p = (float*)((char*)c->mpBegin + 0x18);
    int left = count;
    do {
        creature_body_instance_data_s009b_c580* b = (creature_body_instance_data_s009b_c580*)((char*)p - 0x18);
        b->blend_pos.x = b->target_center.x * w1 + b->center.x * w2;
        b->blend_pos.z = b->target_center.z * w1 + b->center.z * w2;
        b->blend_pos.y = b->target_center.y * w1 + b->center.y * w2;

        const float ax = b->target_rotation.x * w1;
        const float ay = b->target_rotation.y * w1;
        const float az = b->target_rotation.z * w1;
        const float aw = b->target_rotation.w * w1;
        const float bx = b->orientation.x * w2;
        const float by = b->orientation.y * w2;
        const float bz = b->orientation.z * w2;
        const float bw = b->orientation.w * w2;
        const float dot = ((aw * bw + az * bz) + ay * by) + ax * bx;
        if (!(dot < 0.0f)) {
            b->blend_rot.x = ax + bx;
            b->blend_rot.y = ay + by;
            b->blend_rot.z = az + bz;
            b->blend_rot.w = aw + bw;
        } else {
            b->blend_rot.x = ax - bx;
            b->blend_rot.y = ay - by;
            b->blend_rot.z = az - bz;
            b->blend_rot.w = aw - bw;
        }
        p = (float*)((char*)p + 0x2bc);
        --left;
    } while (left != 0);
    return p;
}
}  // namespace nSPCreatureAnim

// @ 0x009bcc70
namespace nSPCreatureAnim {
void __cdecl UpdateBodyTransforms(creature_instance_data_s009b_c580* c, float dt)
{
    int n = (int)(c->mpEnd - c->mpBegin);
    for (int i = 0; i != n; ++i) {
        creature_body_instance_data_s009b_c580* b = &c->mpBegin[i];
        if (b->blend_active) {
            checkerlib::vector_3_s009b_c580 moved, zero;
            const checkerlib::vector_3_s009b_c580* v;
            if (dt > 1e-06f) {
                moved = (b->blend_pos - b->center) * (1.0f / dt);
                v = &moved;
            } else {
                zero.x = 0.0f; zero.y = 0.0f; zero.z = 0.0f;
                v = &zero;
            }
            b->velocity = *v;
            b->center = b->blend_pos;
            b->orientation = b->blend_rot;
        } else {
            b->velocity.x = 0.0f; b->velocity.y = 0.0f; b->velocity.z = 0.0f;
            creature_body_instance_data_s009b_c580* p = b->parent;
            if (!p) {
                b->orientation = b->static_data->orientation;
                b->center = b->static_data->center * c->requested_scale;
            } else {
                creature_body_static_data_s009b_c580* sd = b->static_data;
                b->orientation = checkerlib::QuaternionProduct_s009b_c580(p->orientation, sd->joint_rotation);
                checkerlib::vector_3_s009b_c580 a = sd->local_r * c->requested_scale;
                checkerlib::vector_3_s009b_c580 pr = sd->parent_r * c->requested_scale;
                checkerlib::vector_3_s009b_c580 ra = checkerlib::QuaternionVectorTransform_s009b_c580(b->orientation, a);
                checkerlib::vector_3_s009b_c580 rp = checkerlib::QuaternionVectorTransform_s009b_c580(b->parent->orientation, pr);
                b->center = (b->parent->center + rp) - ra;
            }
        }
    }
}
}  // namespace nSPCreatureAnim

// @ 0x009bd2b0
namespace nSPCreatureAnim {
void __cdecl FUN_009bd2b0(creature_instance_data_s009b_c580* c)
{
    c->saved_center[0] = c->center.x;
    c->saved_center[1] = c->center.y;
    c->saved_center[2] = c->center.z;
    c->saved_orientation[0] = c->orientation.x;
    c->saved_orientation[1] = c->orientation.y;
    c->saved_orientation[2] = c->orientation.z;
    c->saved_orientation[3] = c->orientation.w;
    int* p = (int*)&c->mpAnimState;
    if (*p == 0) {
        ((anim_state_x*)p)->F_9e3f70(6, 4);
        c->F_9b7b10(0, 0);
    }
    if (c->gameData.GetPoliticalID() != 0)
        c->gameData.F_9d33a0(p);
}
}  // namespace nSPCreatureAnim

// @ 0x009bd340
namespace nSPCreatureAnim {
void ResetBodies(creature_instance_data_s009b_d340* c)
{
    int count = (int)(c->Bodies.mpEnd - c->Bodies.mpBegin);
    if (count != 0) {
        int offset = 0;
        int remaining = count;
        do {
            creature_body_instance_data_s009b_d340* b =
                (creature_body_instance_data_s009b_d340*)((char*)c->Bodies.mpBegin + offset);
            b->reset_floats[0] = 0.0f;
            b->reset_floats[1] = 0.0f;
            b->reset_floats[2] = 0.0f;
            b->reset_floats[3] = 0.0f;
            b->reset_floats[4] = 0.0f;
            b->reset_floats[5] = 0.0f;
            b->reset_floats[6] = 0.0f;
            b->reset_floats[7] = 0.0f;
            b->reset_floats[8] = 0.0f;
            b->reset_floats[9] = 0.0f;
            b->reset_floats[10] = 0.0f;
            b->reset_floats[11] = 0.0f;
            b->reset_floats[12] = 0.0f;
            b->reset_floats[13] = 0.0f;
            b->reset_floats[14] = 0.0f;
            b->reset_floats[15] = 0.0f;
            b->reset_floats[16] = 0.0f;
            b->reset_floats[17] = 0.0f;
            b->field_0a0 = 0;
            b->field_048 = 0;
            b->field_04c = 0;
            b->field_050 = 0;
            _ReadWriteBarrier();
            offset += (int)sizeof(creature_body_instance_data_s009b_d340);
            remaining--;
            b->field_054 = 0;
            b->field_055 = 0;
            b->known_ground_pos = 0;
            b->floored = 0;
        } while (remaining != 0);
    }

    c->reset_114 = 0.0f;
    c->reset_110 = 0.0f;
    c->reset_floats[0] = 0.0f;
    c->reset_floats[1] = 0.0f;
    c->reset_floats[2] = 0.0f;
    c->reset_floats[3] = 0.0f;
    c->reset_floats[4] = 0.0f;
    c->reset_floats[5] = 0.0f;
    c->reset_floats[6] = 0.0f;
    c->reset_floats[7] = 0.0f;
    c->reset_floats[8] = 0.0f;
    c->reset_floats[9] = 0.0f;
    c->reset_floats[10] = 0.0f;
    c->reset_floats[11] = 0.0f;
    c->reset_floats[12] = 0.0f;
    c->reset_floats[13] = 0.0f;
    c->reset_floats[14] = 0.0f;
    c->reset_floats[15] = 0.0f;
    c->reset_floats[16] = 0.0f;
    c->reset_floats[17] = 0.0f;
    c->reset_floats[18] = 0.0f;
    c->reset_floats[19] = 0.0f;
    c->reset_floats[20] = 0.0f;
    c->reset_floats[21] = 0.0f;
    c->reset_floats[22] = 0.0f;
    c->reset_floats[23] = 0.0f;
    c->reset_floats[24] = 0.0f;
    c->reset_floats[25] = 0.0f;
    const unsigned int maskSize = ((unsigned int)(count * 2 + 7)) >> 3;
    _ReadWriteBarrier();
    c->reset_floats[26] = 0.0f;
    _ReadWriteBarrier();
    memset((c->reset_1a8 = 0, c->reset_1a9 = 0, c->reset_262 = 1, &c->reset_mask),
           0, maskSize);
    c->reset_counter++;
}
}  // namespace nSPCreatureAnim

// @ 0x009bd550
namespace nSPCreatureAnim {
void BlendBodyPoses(float dt, float blend, creature_instance_data_s009b_d340* c, bool keep_pose)
{
    int count = (int)(c->Bodies.mpEnd - c->Bodies.mpBegin);
    if (count == 0)
        return;

    float invBlend = 1.0f - blend;
    int offset = 0;
    int remaining = count;
    do {
        creature_body_instance_data_s009b_d340* b =
            (creature_body_instance_data_s009b_d340*)((char*)c->Bodies.mpBegin + offset);

        if (!keep_pose) {
            checkerlib::vector_3_s009b_d340 velocity;
            if (dt <= 1e-06f) {
                velocity.x = 0.0f;
                velocity.y = 0.0f;
                velocity.z = 0.0f;
            } else {
                float invDt = 1.0f / dt;
                velocity.x = (b->saved_center.x - b->center.x) * invDt;
                velocity.y = (b->saved_center.y - b->center.y) * invDt;
                velocity.z = (b->saved_center.z - b->center.z) * invDt;
            }
            b->velocity = velocity;
            b->center = b->saved_center;
            b->orientation.x = b->saved_orientation.x;
            b->orientation.y = b->saved_orientation.y;
            b->orientation.z = b->saved_orientation.z;
            b->orientation.w = b->saved_orientation.w;
            b->floored = 1;
        }

        b->blended_center.x = b->center.x * invBlend + b->blended_center.x * blend;
        b->blended_center.y = b->center.y * invBlend + b->blended_center.y * blend;
        b->blended_center.z = b->center.z * invBlend + b->blended_center.z * blend;

        offset += (int)sizeof(creature_body_instance_data_s009b_d340);
        remaining--;
    } while (remaining != 0);
}
}  // namespace nSPCreatureAnim

// @ 0x009bd6f0
namespace nSPCreatureAnim {
void FloorBodies(creature_instance_data_s009b_d340* c)
{
    if (!c->floor_enabled)
        return;

    // creature ground plane in creature space
    checkerlib::vector_3_s009b_d340 normal;
    checkerlib::QuaternionVectorTransformInverse(&normal, &c->orientation, &c->ground_normal);
    checkerlib::vector_3_s009b_d340 rel;
    rel.x = c->ground_pos.x - c->position.x;
    rel.y = c->ground_pos.y - c->position.y;
    rel.z = c->ground_pos.z - c->position.z;
    checkerlib::vector_3_s009b_d340 lground;
    checkerlib::QuaternionVectorTransformInverse(&lground, &c->orientation, &rel);

    const float scale = c->requested_scale;
    const unsigned int count = c->Bodies.size();
    const float planeDist = (lground.z * normal.z + normal.y * lground.y) + normal.x * lground.x;

    for (unsigned int i = 0; i < count; ++i) {
        creature_body_instance_data_s009b_d340& b = c->Bodies[i];
        creature_body_static_data_s009b_d340* sd = b.static_data;
        b.floored_weight = 0.0f;
        if (sd->floor_height < 0.0f)
            continue;

        const bool raised = sd->HasCap(2);
        if (c->static_data->floor_check_caps) {
            if (sd->HasCap(4))
                continue;
            if (sd->HasCap(3))
                continue;
        }

        checkerlib::vector_3_s009b_d340 dir;
        float plane;
        if (b.known_ground_pos) {
            dir = b.ground_normal;
            plane = (b.ground_pos.z * dir.z + b.ground_pos.y * dir.y) + b.ground_pos.x * dir.x;
        } else {
            dir = normal;
            plane = planeDist;
            if (raised)
                plane = sd->floor_height * scale + planeDist;
        }

        float depth = (b.center.z * dir.z + b.center.y * dir.y) + b.center.x * dir.x;
        if (!(plane > depth))
            continue;

        float one = 1.0f;
        float w = (plane - depth) * g_IKFloorWeightRate;
        const float weight = eastl::min(w, one);
        b.floored_weight = weight;

        creature_body_instance_data_s009b_d340* parent = b.parent;
        if (parent != 0 && b.first_child == 0 && !raised && !sd->HasCap(5)) {
            // keep the joint on the parent's joint, put the center on the plane
            checkerlib::vector_3_s009b_d340 v, r;
            v.x = sd->parent_local_joint_r__SCALABLE.x * scale;
            v.y = sd->parent_local_joint_r__SCALABLE.y * scale;
            v.z = sd->parent_local_joint_r__SCALABLE.z * scale;
            const checkerlib::vector_3_s009b_d340* pr = checkerlib::QuaternionVectorTransform(&r, &parent->orientation, &v);
            checkerlib::vector_3_s009b_d340 joint;
            joint.x = pr->x + parent->center.x;
            joint.y = pr->y + parent->center.y;
            joint.z = pr->z + parent->center.z;

            if (parent->floored_weight > 0.0f) {
                checkerlib::vector_3_s009b_d340 v2, r2;
                v2.x = sd->ik_joint_r__SCALABLE.x * scale;
                v2.y = sd->ik_joint_r__SCALABLE.y * scale;
                v2.z = sd->ik_joint_r__SCALABLE.z * scale;
                const checkerlib::vector_3_s009b_d340* pr2 = checkerlib::QuaternionVectorTransform(&r2, &b.orientation, &v2);
                const float inv = 1.0f - weight;
                joint.x = (b.center.x + pr2->x) * inv + joint.x * weight;
                joint.y = (b.center.y + pr2->y) * inv + joint.y * weight;
                joint.z = (b.center.z + pr2->z) * inv + joint.z * weight;
            }

            checkerlib::vector_3_s009b_d340 v3, r3;
            v3.x = sd->ik_joint_r__SCALABLE.x * scale;
            v3.y = sd->ik_joint_r__SCALABLE.y * scale;
            v3.z = sd->ik_joint_r__SCALABLE.z * scale;
            const checkerlib::vector_3_s009b_d340* pr3 = checkerlib::QuaternionVectorTransform(&r3, &b.orientation, &v3);
            checkerlib::vector_3_s009b_d340 arm;   // joint -> center
            arm.x = -pr3->x;
            arm.y = -pr3->y;
            arm.z = -pr3->z;
            const float armLen2 = (arm.y * arm.y + arm.z * arm.z) + arm.x * arm.x;
            if (armLen2 > 0.0f) {
                const float k = ((arm.z + joint.z) * dir.z + (arm.y + joint.y) * dir.y) + (arm.x + joint.x) * dir.x;
                checkerlib::vector_3_s009b_d340 proj;
                proj.x = dir.x * k;
                proj.y = dir.y * k;
                proj.z = dir.z * k;
                checkerlib::vector_3_s009b_d340 a;
                a.x = (dir.x * plane + arm.x) - proj.x;
                float ay = dir.y * plane + arm.y;
                a.y = ay - proj.y;
                a.z = (dir.z * plane + arm.z) - proj.z;
                const float m = (arm.z * dir.z + arm.y * dir.y) + arm.x * dir.x;
                checkerlib::vector_3_s009b_d340 bv;
                bv.x = arm.x - dir.x * m;
                bv.y = arm.y - dir.y * m;
                bv.z = arm.z - dir.z * m;
                const float bb = (bv.x * bv.x + bv.y * bv.y) + bv.z * bv.z;
                const float ab = (bv.z * a.z + bv.y * a.y) + bv.x * a.x;
                const float aa = (a.y * a.y + a.z * a.z) + a.x * a.x;
                const float disc = ab * ab - (aa - armLen2) * bb;
                float root;
                if (disc > 0.0f)
                    root = sqrtf(disc);
                else
                    root = 0.0f;
                const float t = (float)(((double)root - ab) / (bb + 1e-08));
                checkerlib::vector_3_s009b_d340 newArm;
                newArm.x = bv.x * t + a.x;
                newArm.y = bv.y * t + a.y;
                newArm.z = bv.z * t + a.z;
                b.center.x = newArm.x + joint.x;
                b.center.y = newArm.y + joint.y;
                b.center.z = newArm.z + joint.z;
                checkerlib::vector_4_s009b_d340 q, qr;
                b.orientation = *checkerlib::QuaternionProduct(&qr, QuaternionFromTwoVectors(&q, &arm, &newArm, 0),
                                                   &b.orientation);
            }
        } else {
            // tilt the body's up axis towards the plane normal, then put it on the plane
            const checkerlib::vector_4_s009b_d340& o = b.orientation;
            checkerlib::vector_3_s009b_d340 up;
            up.x = (o.x * o.z + o.y * o.w) * 2.0f;
            up.y = (o.z * o.y - o.x * o.w) * 2.0f;
            up.z = 1.0f - (o.x * o.x + o.y * o.y) * 2.0f;
            if ((up.x * dir.x + up.z * dir.z) + up.y * dir.y < 0.0f) {
                up.x = -up.x;
                up.y = -up.y;
                up.z = -up.z;
            }
            checkerlib::vector_4_s009b_d340 arc;
            const checkerlib::vector_4_s009b_d340* pa = QuaternionFromTwoVectors(&arc, &up, &dir, 0);
            checkerlib::vector_4_s009b_d340 s;
            s.x = pa->x * weight;
            s.y = pa->y * weight;
            s.z = pa->z * weight;
            const float sw = pa->w * weight;
            s.w = (sw < 0.0f ? weight - 1.0f : 1.0f - weight) + sw;
            const checkerlib::vector_4_s009b_d340 r = checkerlib::Normalize(s, 0);

            const float qx = b.orientation.x, qy = b.orientation.y;
            const float qz = b.orientation.z, qw = b.orientation.w;
            const float nx = ((qx * r.w + r.x * qw) - qy * r.z) + qz * r.y;
            const float ny = ((r.z * qx + qy * r.w) + r.y * qw) - qz * r.x;
            const float nz = ((r.z * qw - r.y * qx) + qz * r.w) + qy * r.x;
            const float nw = ((r.w * qw - qx * r.x) - r.y * qy) - qz * r.z;
            b.orientation.w = nw;
            b.orientation.x = nx;
            b.orientation.y = ny;
            b.orientation.z = nz;

            const float d = depth - plane;
            b.center.x = b.center.x - dir.x * d;
            b.center.y = b.center.y - dir.y * d;
            b.center.z = b.center.z - dir.z * d;
        }
        b.floored = true;
    }
}
}  // namespace nSPCreatureAnim

// @ 0x009be150
namespace nSPCreatureAnim {
void UpdateDeforms(creature_instance_data_s009b_d340* c)
{
    int count = (int)(c->Bodies.mpEnd - c->Bodies.mpBegin);
    if (count == 0)
        return;

    int offset = 0;
    int remaining = count;
    do {
        creature_body_instance_data_s009b_d340* b =
            (creature_body_instance_data_s009b_d340*)((char*)c->Bodies.mpBegin + offset);

        if ((b->static_data->field_154 & 0x20) != 0) {
            uint32_t n = b->field_0a0;
            uint32_t first = 0;
            if (n != 0) {
                creature_deform* p = &b->deforms[0];
                do {
                    if (p->key == 0x4d5bf589)
                        goto found_first;
                    first++;
                    p++;
                } while (first < n);
            }
            first = 0xffffffffu;
        found_first:
            if (first < n) {
                creature_deform* src = &b->deforms[first];
                uint32_t second = 0;
                if (n != 0) {
                    creature_deform* p = &b->deforms[0];
                    do {
                        if (p->key == 0x89e06a31)
                            goto found_second;
                        second++;
                        p++;
                    } while (second < n);
                }
                second = 0xffffffffu;
            found_second:
                if (second < n) {
                    creature_deform* dst = &b->deforms[second];
                    dst->value8 = src->value8 + dst->value8;
                    dst->value10 = src->value10 + dst->value10;
                } else {
                    src->flags &= ~1;
                    src->key = 0x89e06a31;
                }
            }
        }

        offset += (int)sizeof(creature_body_instance_data_s009b_d340);
        remaining--;
    } while (remaining != 0);
}
}  // namespace nSPCreatureAnim

// @ 0x009be260
void __cdecl FUN_009be260(CreatureAnim* c)
{
    c->a18.x = 0.0f; c->a18.y = 0.0f; c->a18.z = 0.0f;
    c->d3c.x = 0.0f; c->d3c.y = 0.0f; c->d3c.z = 0.0f; c->d3c.w = 1.0f;
    c->i74.x = 0.0f; c->i74.y = 0.0f; c->i74.z = 0.0f;
    c->k8c.x = 0.0f; c->k8c.y = 0.0f; c->k8c.z = 0.0f;
    c->ma4.x = 0.0f; c->ma4.y = 0.0f; c->ma4.z = 0.0f;
    c->nb0.x = 0.0f; c->nb0.y = 0.0f; c->nb0.z = 0.0f;
    c->obc.x = 0.0f; c->obc.y = 0.0f; c->obc.z = 0.0f;
    c->pc8.x = 0.0f; c->pc8.y = 0.0f; c->pc8.z = 0.0f;
    c->qd4 = 1.0f;
    c->h70 = c->g6c;
    c->c30 = c->a18;
    c->b24 = c->c30;
    c->j80 = c->i74;
    c->f5c = c->d3c;
    c->e4c = c->f5c;

    int n = (int)((c->slotsEnd - c->slotsBegin) / 700);
    float t = c->h70;
    BoneSlot* slots = (BoneSlot*)c->slotsBegin;
    for (int i = 0; i < n; i++) InitSlot(&slots[i], t);
}

// @ 0x009be750
BodyVertex28** __cdecl FUN_009be750(BodyVertex28** out, const BodyVertex28* first, const BodyVertex28* last, BodyVertex28* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst) {
                dst->a = first->a;
                dst->b = first->b;
                dst->f[0] = first->f[0]; dst->f[1] = first->f[1];
                dst->f[2] = first->f[2]; dst->f[3] = first->f[3];
                dst->f[4] = first->f[4]; dst->f[5] = first->f[5];
                dst->f[6] = first->f[6]; dst->f[7] = first->f[7];
            }
            first++; dst++;
        } while (first != last);
        *out = dst;
    }
    return out;
}

// @ 0x009be7d0
Matrix30** __cdecl FUN_009be7d0(Matrix30** out, const Matrix30* first, const Matrix30* last, Matrix30* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst) {
                dst->f[0]  = first->f[0];
                dst->f[3]  = first->f[3];
                dst->f[6]  = first->f[6];
                dst->f[1]  = first->f[1];
                dst->f[4]  = first->f[4];
                dst->f[7]  = first->f[7];
                dst->f[2]  = first->f[2];
                dst->f[5]  = first->f[5];
                dst->f[8]  = first->f[8];
                dst->f[9]  = first->f[9];
                dst->f[10] = first->f[10];
                dst->f[11] = first->f[11];
            }
            first++; dst++;
        } while (first != last);
        *out = dst;
    }
    return out;
}

// @ 0x009be850
Copy108c& Copy108c::operator=(const Copy108c& o)
{
    i[0] = o.i[0]; i[1] = o.i[1]; i[2] = o.i[2]; i[3] = o.i[3];
    a[0] = o.a[0]; a[1] = o.a[1]; a[2] = o.a[2]; a[3] = o.a[3];
    a[4] = o.a[4]; a[5] = o.a[5]; a[6] = o.a[6]; a[7] = o.a[7];
    a[8] = o.a[8]; a[9] = o.a[9]; a[10] = o.a[10]; a[11] = o.a[11];
    a[12] = o.a[12]; a[13] = o.a[13]; a[14] = o.a[14]; a[15] = o.a[15];
    a[16] = o.a[16]; a[17] = o.a[17]; a[18] = o.a[18]; a[19] = o.a[19];
    a[20] = o.a[20]; a[21] = o.a[21]; a[22] = o.a[22]; a[23] = o.a[23];
    a[24] = o.a[24]; a[25] = o.a[25]; a[26] = o.a[26]; a[27] = o.a[27];
    b[0] = o.b[0]; b[1] = o.b[1]; b[2] = o.b[2]; b[3] = o.b[3]; b[4] = o.b[4];
    m = o.m;
    c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; c[3] = o.c[3];
    c[4] = o.c[4]; c[5] = o.c[5]; c[6] = o.c[6]; c[7] = o.c[7];
    c[8] = o.c[8]; c[9] = o.c[9]; c[10] = o.c[10]; c[11] = o.c[11];
    c[12] = o.c[12];
    j[0] = o.j[0]; j[1] = o.j[1]; j[2] = o.j[2];
    k = o.k;
    n = o.n;
    return *this;
}

// @ 0x009bea50
Body2bc::Body2bc(const Body2bc& o)
{
    i00 = o.i00; i04 = o.i04; i08 = o.i08; i0c = o.i0c;
    f[0] = o.f[0]; f[1] = o.f[1]; f[2] = o.f[2]; f[3] = o.f[3]; f[4] = o.f[4];
    f[5] = o.f[5]; f[6] = o.f[6]; f[7] = o.f[7]; f[8] = o.f[8]; f[9] = o.f[9];
    b38 = o.b38;
    g[0] = o.g[0]; g[1] = o.g[1]; g[2] = o.g[2];
    j[0] = o.j[0]; j[1] = o.j[1]; j[2] = o.j[2];
    b54 = o.b54; b55 = o.b55;
    h[0] = o.h[0]; h[1] = o.h[1]; h[2] = o.h[2]; h[3] = o.h[3];
    h[4] = o.h[4]; h[5] = o.h[5]; h[6] = o.h[6]; h[7] = o.h[7];
    h[8] = o.h[8]; h[9] = o.h[9]; h[10] = o.h[10]; h[11] = o.h[11];
    h[12] = o.h[12]; h[13] = o.h[13]; h[14] = o.h[14]; h[15] = o.h[15];
    h[16] = o.h[16]; h[17] = o.h[17];
    arr = o.arr;
    i144 = o.i144;
    p[0] = o.p[0]; p[1] = o.p[1]; p[2] = o.p[2]; p[3] = o.p[3];
    p[4] = o.p[4]; p[5] = o.p[5]; p[6] = o.p[6]; p[7] = o.p[7];
    p[8] = o.p[8]; p[9] = o.p[9]; p[10] = o.p[10]; p[11] = o.p[11];
    p[12] = o.p[12]; p[13] = o.p[13]; p[14] = o.p[14]; p[15] = o.p[15];
    p[16] = o.p[16];
    sub.Init(o.sub);
    q[0] = o.q[0]; q[1] = o.q[1]; q[2] = o.q[2]; q[3] = o.q[3];
    q[4] = o.q[4]; q[5] = o.q[5]; q[6] = o.q[6]; q[7] = o.q[7];
    b2a0 = o.b2a0;
    r[0] = o.r[0]; r[1] = o.r[1]; r[2] = o.r[2];
    r[3] = o.r[3]; r[4] = o.r[4]; r[5] = o.r[5];
}

// @ 0x009bed40
BodyVertex28* __cdecl FUN_009bed40(const BodyVertex28* first, const BodyVertex28* last, BodyVertex28* dst)
{
    if (first != last) {
        do {
            dst->a = first->a;
            dst->b = first->b;
            dst->f[0] = first->f[0]; dst->f[1] = first->f[1];
            dst->f[2] = first->f[2]; dst->f[3] = first->f[3];
            dst->f[4] = first->f[4]; dst->f[5] = first->f[5];
            dst->f[6] = first->f[6]; dst->f[7] = first->f[7];
            first++; dst++;
        } while (first != last);
    }
    return dst;
}

// @ 0x009bee30
WiggleInstance** __cdecl FUN_009bee30(WiggleInstance** out, const WiggleInstance* first, const WiggleInstance* last, WiggleInstance* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst) {
                dst->static_data = first->static_data;
                dst->enabled = first->enabled;
                dst->force_override = first->force_override;
                dst->world_vel = first->world_vel;
                dst->world_pos = first->world_pos;
                dst->world_pos_old = first->world_pos_old;
            }
            first++; dst++;
        } while (first != last);
        *out = dst;
    }
    return out;
}

// @ 0x009beec0
void __cdecl FUN_009beec0(WiggleInstance* first, WiggleInstance* last, const WiggleInstance* src)
{
    if (first != last) {
        do {
            first->static_data = src->static_data;
            first->enabled = src->enabled;
            first->force_override = src->force_override;
            first->world_vel = src->world_vel;
            first->world_pos = src->world_pos;
            first->world_pos_old = src->world_pos_old;
            first++;
        } while (first != last);
    }
}

// @ 0x009bef30
void __cdecl FUN_009bef30(WiggleInstance* dst, unsigned n, const WiggleInstance* src)
{
    if (n == 0) return;
    do {
        if (dst) {
            dst->static_data = src->static_data;
            dst->enabled = src->enabled;
            dst->force_override = src->force_override;
            dst->world_vel = src->world_vel;
            dst->world_pos = src->world_pos;
            dst->world_pos_old = src->world_pos_old;
        }
        n--; dst++;
    } while (n != 0);
}

// @ 0x009befa0
Copy108& Copy108::operator=(const Copy108& o)
{
    i[0] = o.i[0]; i[1] = o.i[1]; i[2] = o.i[2]; i[3] = o.i[3];
    a[0] = o.a[0]; a[1] = o.a[1]; a[2] = o.a[2]; a[3] = o.a[3];
    a[4] = o.a[4]; a[5] = o.a[5]; a[6] = o.a[6]; a[7] = o.a[7];
    a[8] = o.a[8]; a[9] = o.a[9]; a[10] = o.a[10]; a[11] = o.a[11];
    a[12] = o.a[12]; a[13] = o.a[13]; a[14] = o.a[14]; a[15] = o.a[15];
    a[16] = o.a[16]; a[17] = o.a[17]; a[18] = o.a[18]; a[19] = o.a[19];
    a[20] = o.a[20]; a[21] = o.a[21]; a[22] = o.a[22]; a[23] = o.a[23];
    a[24] = o.a[24]; a[25] = o.a[25]; a[26] = o.a[26]; a[27] = o.a[27];
    b[0] = o.b[0]; b[1] = o.b[1]; b[2] = o.b[2]; b[3] = o.b[3]; b[4] = o.b[4];
    m = o.m;
    c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; c[3] = o.c[3];
    c[4] = o.c[4]; c[5] = o.c[5]; c[6] = o.c[6]; c[7] = o.c[7];
    c[8] = o.c[8]; c[9] = o.c[9]; c[10] = o.c[10]; c[11] = o.c[11];
    c[12] = o.c[12];
    j[0] = o.j[0]; j[1] = o.j[1]; j[2] = o.j[2];
    k[0] = o.k[0]; k[1] = o.k[1]; k[2] = o.k[2]; k[3] = o.k[3];
    k[4] = o.k[4]; k[5] = o.k[5]; k[6] = o.k[6]; k[7] = o.k[7];
    k[8] = o.k[8]; k[9] = o.k[9]; k[10] = o.k[10]; k[11] = o.k[11];
    n = o.n;
    return *this;
}

// @ 0x009bf210
Body2bcF::Body2bcF(const Body2bcF& o)
{
    i00 = o.i00; i04 = o.i04; i08 = o.i08; i0c = o.i0c;
    f[0] = o.f[0]; f[1] = o.f[1]; f[2] = o.f[2]; f[3] = o.f[3]; f[4] = o.f[4];
    f[5] = o.f[5]; f[6] = o.f[6]; f[7] = o.f[7]; f[8] = o.f[8]; f[9] = o.f[9];
    b38 = o.b38;
    g[0] = o.g[0]; g[1] = o.g[1]; g[2] = o.g[2];
    j3[0] = o.j3[0]; j3[1] = o.j3[1]; j3[2] = o.j3[2];
    b54 = o.b54; b55 = o.b55;
    h[0] = o.h[0]; h[1] = o.h[1]; h[2] = o.h[2]; h[3] = o.h[3];
    h[4] = o.h[4]; h[5] = o.h[5]; h[6] = o.h[6]; h[7] = o.h[7];
    h[8] = o.h[8]; h[9] = o.h[9]; h[10] = o.h[10]; h[11] = o.h[11];
    h[12] = o.h[12]; h[13] = o.h[13]; h[14] = o.h[14]; h[15] = o.h[15];
    h[16] = o.h[16]; h[17] = o.h[17];
    arr = o.arr;
    i144 = o.i144;
    p[0] = o.p[0]; p[1] = o.p[1]; p[2] = o.p[2]; p[3] = o.p[3];
    p[4] = o.p[4]; p[5] = o.p[5]; p[6] = o.p[6]; p[7] = o.p[7];
    p[8] = o.p[8]; p[9] = o.p[9]; p[10] = o.p[10]; p[11] = o.p[11];
    p[12] = o.p[12]; p[13] = o.p[13]; p[14] = o.p[14]; p[15] = o.p[15];
    p[16] = o.p[16];
    sub.Init(o.sub);
    q[0] = o.q[0]; q[1] = o.q[1]; q[2] = o.q[2]; q[3] = o.q[3];
    q[4] = o.q[4]; q[5] = o.q[5]; q[6] = o.q[6]; q[7] = o.q[7];
    b2a0 = o.b2a0;
    r[0] = o.r[0]; r[1] = o.r[1]; r[2] = o.r[2];
    r[3] = o.r[3]; r[4] = o.r[4]; r[5] = o.r[5];
}

// @ 0x009bf680
BodyAnimC::BodyAnimC()
{
    a.z = 0.0f; a.y = 0.0f; a.x = 0.0f;
    b.z = 0.0f; b.y = 0.0f; b.x = 0.0f;
    c = 1.0f;
    d.z = 0.0f; d.y = 0.0f; d.x = 0.0f;
    e.z = 0.0f; e.y = 0.0f; e.x = 0.0f;
    f[0] = 0.0f;  f[1] = 0.0f;  f[2] = 0.0f;  f[3] = 0.0f;  f[4] = 0.0f;
    f[5] = 0.0f;  f[6] = 0.0f;  f[7] = 0.0f;  f[8] = 0.0f;  f[9] = 0.0f;
    f[10] = 0.0f; f[11] = 0.0f; f[12] = 0.0f; f[13] = 0.0f; f[14] = 0.0f;
    f[15] = 0.0f; f[16] = 0.0f; f[17] = 0.0f;
    g = 0;
    h.z = 0.0f; h.y = 0.0f; h.x = 0.0f;
    i = 1.0f;
    j.z = 0.0f; j.y = 0.0f; j.x = 0.0f;
    k.z = 0.0f; k.y = 0.0f; k.x = 0.0f;
    l.z = 0.0f; l.y = 0.0f; l.x = 0.0f;
    m.z = 0.0f; m.y = 0.0f; m.x = 0.0f;
    n = 1.0f;
    sub.Reset();
    o.z = 0.0f; o.y = 0.0f; o.x = 0.0f;
    p.z = 0.0f; p.y = 0.0f; p.x = 0.0f;
    q = 1.0f;
    r.z = 0.0f; r.y = 0.0f; r.x = 0.0f;
    s.z = 0.0f; s.y = 0.0f; s.x = 0.0f;
    Finalize();
}

// @ 0x009bf860
void WiggleAnim::Recompute()
{
    maxDist = 0.0f;
    maxDist2 = 0.0f;
    int n = (int)((int)((char*)end - (char*)beg) / 0x468);
    if (n <= 0) return;

    for (int i = 0; i < n; i++) {
        WiggleElem* node = (WiggleElem*)((char*)beg + i * 0x468);
        WiggleElem* a = (WiggleElem*)((char*)beg + node->link1 * 0x468);
        WiggleElem* b = (WiggleElem*)((char*)beg + node->link2 * 0x468);

        float dx = a->pos.x - b->pos.x;
        float dy = a->pos.y - b->pos.y;
        float dz = a->pos.z - b->pos.z;

        float local[3];
        local[1] = 0.01f;
        local[0] = (float)sqrt(dx * dx + dy * dy + dz * dz);
        float* p = local;
        if (local[0] <= local[1]) p = local + 1;
        node->span = *p;

        float w = Weight(node);
        node->dist = w;
        if (maxDist < w) maxDist = w;
        if ((node->flags & 4) && (node->dist > maxDist2)) maxDist2 = node->dist;

        local[2] = b->pos.z - node->pos.z;
        float* q = local + 2;
        if (local[2] <= g_eps) q = &g_eps;
        node->gap = *q;
    }
}

// @ 0x009bfa20
void WiggleAnim::Walk()
{
    Prep();
    Recompute();

    unsigned count = (unsigned)((int)((char*)end - (char*)beg) / 0x468);
    int i = (int)count - 1;
    if (i < 0) return;

    do {
        WiggleElem* node = (WiggleElem*)((char*)beg + i * 0x468);
        unsigned nflags = node->flags;
        unsigned d = (unsigned)node->first;
        unsigned dend = (unsigned)node->count + d;
        node->root = -1;
        node->other = -1;
        unsigned kept = 0xffffffff;
        int seen = 0;

        if (d < dend) {
            unsigned j = d;
            do {
                WiggleElem* dep = (WiggleElem*)((char*)beg + j * 0x468);
                if ((dep->flags & 8) == 0) {
                    if ((dep->flags & 4) == 0) {
                        if (dep->root != -1) {
                            if (((nflags >> 3 & 1) == 0) && seen == 0) {
                                node->root = dep->root;
                                kept = 0xffffffff;
                                if (dep->root != -2) kept = j;
                                seen = 1;
                            } else {
                                if (kept != 0xffffffff && seen == 1) {
                                    FUN_009b4ef0((char*)beg + kept * 0x468);
                                    node->root = -2;
                                }
                                if (dep->root != -2) FUN_009b4ef0(dep);
                                seen++;
                            }
                        }
                    } else {
                        node->root = (int)j;
                        dep->root = (int)j;
                    }
                }
                j++;
            } while (j < dend);
        }

        if (node->root < (int)count) {
            unsigned k1 = (unsigned)node->first;
            unsigned kend = (unsigned)node->count + k1;
            if (k1 < kend) {
                unsigned k = k1;
                do {
                    WiggleElem* dep = (WiggleElem*)((char*)beg + k * 0x468);
                    if (dep->root == -1) dep->root = -3;
                    k++;
                } while (k < kend);
            }
        }

        i--;
    } while (i >= 0);
}

// @ 0x009bfc20
namespace nSPCreatureAnim {
void creature_body_instance_data_s009b_fc20::GroundGoal(checkerlib::vector_3_s009b_fc20* outPos, checkerlib::vector_4_s009b_fc20* outRot, creature_instance_data_s009b_fc20* c, float baseHeight, float rate, bool storeGround)
{
    // goal position in creature space
    checkerlib::vector_3_s009b_fc20 lpos;
    float s;
    if (goal_b.pos_weight > 0.0f) {
        s = 1.0f / goal_b.pos_weight;
        lpos.x = goal_b.pos.x * s;
        lpos.y = goal_b.pos.y * s;
        lpos.z = goal_b.pos.z * s;
    } else {
        const checkerlib::vector_3_s009b_fc20& rc = static_data->rest_center__SCALABLE;
        s = c->requested_scale;
        lpos.x = rc.x * s;
        lpos.y = rc.y * s;
        lpos.z = rc.z * s;
    }
    checkerlib::vector_3_s009b_fc20 local;
    local = lpos;

    // world position
    checkerlib::vector_3_s009b_fc20 wpos;
    {
        checkerlib::vector_3_s009b_fc20 tmp;
        checkerlib::vector_3_s009b_fc20* r = checkerlib::QuaternionVectorTransform(&tmp, &c->orientation, &local);
        wpos.x = c->position.x + r->x;
        wpos.y = r->y + c->position.y;
        wpos.z = r->z + c->position.z;
    }

    // world rotation
    checkerlib::vector_4_s009b_fc20 tmpA, tmpB;
    const checkerlib::vector_4_s009b_fc20* nrot;
    if (goal_b.rot_weight > 0.0f)
        nrot = checkerlib::Normalize(&tmpA, &goal_b.rot, 0);
    else
        nrot = checkerlib::Normalize(&tmpB, &static_data->rest_orientation_q, 0);
    checkerlib::vector_4_s009b_fc20 wrot = QuatMul(c->orientation, *nrot);

    checkerlib::vector_3_s009b_fc20 normal;
    normal.x = 0.0f;
    normal.y = 0.0f;
    normal.z = 0.0f;
    float height = c->GetGroundHeight(&wpos, &normal);
    float d = (height - baseHeight) * rate;

    checkerlib::vector_3_s009b_fc20 gpos;
    gpos.x = c->ground_up.x * d + wpos.x;
    gpos.y = c->ground_up.y * d + wpos.y;
    gpos.z = c->ground_up.z * d + wpos.z;

    const checkerlib::vector_3_s009b_fc20& ext = static_data->extent;
    float ex = ext.x * c->requested_scale;
    float ey = ext.y * c->requested_scale;
    float ez = ext.z * c->requested_scale;
    double sum = (double)ex * (double)ex;
    sum = sum + (double)ey * (double)ey;
    sum = sum + (double)ez * (double)ez;
    float size = (float)((float)sqrt(sum) * 1.3f);

    checkerlib::vector_4_s009b_fc20 grot;
    if (size > local.z) {
        float f = 1.0f - SmoothStep(0.0f, size, local.z);
        checkerlib::vector_4_s009b_fc20 tilt;
        QuaternionFromTwoVectors(&tilt, &c->ground_up, &normal, 0);
        if (f < 1.0f) {
            tilt.x *= f;
            tilt.y *= f;
            tilt.z *= f;
            tilt.w *= f;
            float g = 1.0f - f;
            if (tilt.w > 0.0f)
                tilt.w = g + tilt.w;
            else
                tilt.w = tilt.w - g;
            checkerlib::vector_4_s009b_fc20 tmp;
            grot = QuatMul(*checkerlib::Normalize(&tmp, &tilt, 0), wrot);
        } else {
            grot = QuatMul(tilt, wrot);
        }
    } else {
        grot = wrot;
    }

    if (storeGround) {
        checkerlib::vector_3_s009b_fc20 up;
        c->GetGroundUp(&up, &wpos);
        float dot = (up.x * wpos.x + up.z * wpos.z) + up.y * wpos.y;
        float r = static_data->rest_center__SCALABLE.z * c->requested_scale;
        checkerlib::vector_3_s009b_fc20 gp;
        gp.x = (((wpos.x - up.x * dot) + up.x * height) + normal.x * r) - c->position.x;
        gp.y = (((wpos.y - up.y * dot) + up.y * height) + normal.y * r) - c->position.y;
        gp.z = (((wpos.z - up.z * dot) + up.z * height) + normal.z * r) - c->position.z;
        checkerlib::vector_3_s009b_fc20 tmp;
        ground_pos = *checkerlib::QuaternionVectorTransformInverse(&tmp, &c->orientation, &gp);
        ground_normal = *checkerlib::QuaternionVectorTransformInverse(&tmp, &c->orientation, &normal);
        known_ground_pos = true;
    }

    checkerlib::vector_3_s009b_fc20 delta;
    delta.x = gpos.x - c->position.x;
    delta.y = gpos.y - c->position.y;
    delta.z = gpos.z - c->position.z;
    *outPos = InvRotate(c->orientation, delta);
    *outRot = QuatConjMul(c->orientation, grot);
}
}  // namespace nSPCreatureAnim

// @ 0x009c0680
namespace nSPCreatureAnim {
void creature_instance_data_s009b_fc20::UpdateGoalGrounds()
{
    checkerlib::vector_4_s009b_fc20 rot;
    checkerlib::vector_3_s009b_fc20 pos;
    float baseHeight;
    bool storeGround;
    float rate;

    FUN_009b8fd0(&baseHeight, &rate);
    if (!(rate > 1.0e-6f))
        return;
    int32_t count = (int32_t)(body_end - body_begin);
    if (count <= 0)
        return;
    for (int32_t i = 0; i < count; ++i) {
        creature_body_instance_data_s009b_fc20* pBody = &body_begin[i];
        if (pBody->goal_b.pos_weight != 0.0f || pBody->goal_b.rot_weight != 0.0f ||
            pBody->goal_a.pos_weight != 0.0f || pBody->goal_a.rot_weight != 0.0f) {
            uint32_t flags = pBody->static_data->ground_flags;
            uint32_t alt = flags >> 4;
            storeGround = ((flags >> 2) & 1) != 0;
            if (ground_placement_valid && (storeGround || (alt & 1) != 0)) {
                pos.z = 0.0f;
                pos.y = 0.0f;
                pos.x = 0.0f;
                rot.z = 0.0f;
                rot.y = 0.0f;
                rot.x = 0.0f;
                rot.w = 1.0f;
                pBody->GroundGoal(&pos, &rot, this, baseHeight, rate, storeGround);
                float w = pBody->goal_b.pos_weight;
                if (w > 0.0f) {
                    float x = w * pos.x;
                    float y = w * pos.y;
                    float z = w * pos.z;
                    pBody->goal_b.pos.x = x;
                    pBody->goal_b.pos.y = y;
                    pBody->goal_b.pos.z = z;
                }
                w = pBody->goal_b.rot_weight;
                if (w > 0.0f) {
                    float x = w * rot.x;
                    float y = w * rot.y;
                    float z = w * rot.z;
                    float qw = w * rot.w;
                    pBody->goal_b.rot.x = x;
                    pBody->goal_b.rot.y = y;
                    pBody->goal_b.rot.z = z;
                    pBody->goal_b.rot.w = qw;
                }
            }
        }
    }
}
}  // namespace nSPCreatureAnim

// @ 0x009c0860
namespace nSPCreatureAnim {
void creature_instance_data_s009b_fc20::UpdateGoalGround(creature_body_ref* pRef)
{
    checkerlib::vector_4_s009b_fc20 rot;
    checkerlib::vector_3_s009b_fc20 pos;
    float baseHeight;
    float rate;

    FUN_009b8fd0(&baseHeight, &rate);
    if (!(rate > 1.0e-6f))
        return;
    creature_body_instance_data_s009b_fc20* pBody = pRef->body;
    if (pBody->goal_b.pos_weight == 0.0f && pBody->goal_b.rot_weight == 0.0f)
        return;
    if (!ground_placement_valid)
        return;
    pos.z = 0.0f;
    pos.y = 0.0f;
    pos.x = 0.0f;
    rot.z = 0.0f;
    rot.y = 0.0f;
    rot.x = 0.0f;
    rot.w = 1.0f;
    pBody->GroundGoal(&pos, &rot, this, baseHeight, rate, false);
    float w = pBody->goal_b.pos_weight;
    if (w > 0.0f) {
        float x = w * pos.x;
        float y = w * pos.y;
        float z = w * pos.z;
        pBody->goal_b.pos.x = x;
        pBody->goal_b.pos.y = y;
        pBody->goal_b.pos.z = z;
    }
    w = pBody->goal_b.rot_weight;
    if (w > 0.0f) {
        float x = w * rot.x;
        float y = w * rot.y;
        float z = w * rot.z;
        float qw = w * rot.w;
        pBody->goal_b.rot.x = x;
        pBody->goal_b.rot.y = y;
        pBody->goal_b.rot.z = z;
        pBody->goal_b.rot.w = qw;
    }
}
}  // namespace nSPCreatureAnim

// @ 0x009c0f60
void Vec30::Insert(u8_s009c_0f60* pos, u8_s009c_0f60* value)
{
    if (end != cap) {
        // the value may live inside the range we are about to shift
        if (pos <= value && value < end) value += 0x30;
        if (end != 0) FUN_009b3c80(end - 0x30);
        FUN_009b47f0(pos, end - 0x30, end);
        for (int i = 0; i < 12; i++) ((u32_s009c_0f60*)pos)[i] = ((u32_s009c_0f60*)value)[i];
        end += 0x30;
        return;
    }

    unsigned n = grow_count((unsigned)((end - begin) / 0x30));
    u8_s009c_0f60* mem = (u8_s009c_0f60*)EASTL_NEW(n * 0x30);
    u8_s009c_0f60* mid = (u8_s009c_0f60*)FUN_009b4290(begin, pos, mem);
    if (mem != 0) FUN_009b3c80(value);
    u8_s009c_0f60* newEnd = (u8_s009c_0f60*)FUN_009b4290(pos, end, mem + 0x30);
    EASTL_FREE(begin);
    begin = mem;
    end = newEnd;
    cap = mem + n * 0x30;
    (void)mid;
}

// @ 0x009c10c0
void Vec3c::Insert(u8_s009c_0f60* pos, u8_s009c_0f60* value)
{
    if (end != cap) {
        if (pos <= value && value < end) value += 0x3c;
        if (end != 0) FUN_009b3ab0(end - 0x3c);
        FUN_009b4870(pos, end - 0x3c, end);
        FUN_009b3ab0(value);
        end += 0x3c;
        return;
    }

    unsigned n = grow_count((unsigned)((end - begin) / 0x3c));
    u8_s009c_0f60* mem = (u8_s009c_0f60*)EASTL_NEW(n * 0x3c);
    FUN_009b4350(begin, pos, mem);
    FUN_009b3ab0(value);
    u8_s009c_0f60* newEnd = (u8_s009c_0f60*)FUN_009b4350(pos, end, mem + 0x3c);
    EASTL_FREE(begin);
    begin = mem;
    end = newEnd;
    cap = mem + n * 0x3c;
}

// @ 0x009c11e0
void Vec30::InsertFill(u8_s009c_0f60* pos, unsigned n, const void* value)
{
    if ((unsigned)((cap - end) / 0x30) < n) {
        unsigned have = (unsigned)((end - begin) / 0x30);
        unsigned need = have + n;
        unsigned want = grow_count(have);
        if (need < want) need = want;
        u8_s009c_0f60* mem = (u8_s009c_0f60*)EASTL_NEW(need * 0x30);
        u8_s009c_0f60* p = (u8_s009c_0f60*)FUN_009b4910(begin, pos, mem);
        FUN_009b44e0(p, n, value, pos);
        u8_s009c_0f60* newEnd = (u8_s009c_0f60*)FUN_009b4910(pos, end, p + n * 0x30);
        EASTL_FREE(begin);
        begin = mem;
        end = newEnd;
        cap = mem + need * 0x30;
        return;
    }
    if (n == 0) return;

    FUN_009b41e0(value);                       // copy the value into a local slot
    u8_s009c_0f60 tmp[0x30];
    memcpy(tmp, value, 0x30);
    u8_s009c_0f60* e = end;
    unsigned tail = (unsigned)((e - pos) / 0x30);

    if (tail < n) {
        // not enough room after pos: fill the gap, then shift the tail
        FUN_009b44e0(e, n - tail, tmp, pos);
        end = e + (n - tail) * 0x30;
        FUN_009b4ab0(pos, e, end);
        end += tail * 0x30;
        FUN_009b4490(pos, pos + n * 0x30, tmp);
    } else {
        // enough room: move the last n elements out, then shift in the fill
        u8_s009c_0f60* at = e - n * 0x30;
        FUN_009b4ab0(at, e, e);
        end = e + n * 0x30;
        FUN_009b4490(pos, at + n * 0x30, tmp);
    }
}

// @ 0x009c13a0
void Vec44::InsertFill(u8_s009c_0f60* pos, unsigned n, const void* value)
{
    if ((unsigned)((cap - end) / 0x2c) < n) {
        unsigned have = (unsigned)((end - begin) / 0x2c);
        unsigned need = have + n;
        unsigned want = grow_count(have);
        if (need < want) need = want;
        u8_s009c_0f60* mem = (u8_s009c_0f60*)EASTL_NEW(need * 0x2c);
        u8_s009c_0f60* p = (u8_s009c_0f60*)FUN_009b4990(begin, pos, mem);
        FUN_009bef30(p, n, value, pos);
        u8_s009c_0f60* newEnd = (u8_s009c_0f60*)FUN_009b4990(pos, end, p + n * 0x2c);
        EASTL_FREE(begin);
        begin = mem;
        end = newEnd;
        cap = mem + need * 0x2c;
        return;
    }
    if (n == 0) return;

    FUN_009b4230(value);
    u8_s009c_0f60 tmp[0x2c];
    memcpy(tmp, value, 0x2c);
    u8_s009c_0f60* e = end;
    unsigned tail = (unsigned)((e - pos) / 0x2c);

    if (tail < n) {
        FUN_009bef30(e, n - tail, tmp, pos);
        end = e + (n - tail) * 0x2c;
        FUN_009b4b10(pos, e, end);
        end += tail * 0x2c;
        FUN_009beec0(pos, pos + n * 0x2c, tmp);
    } else {
        u8_s009c_0f60* at = e - n * 0x2c;
        FUN_009b4b10(at, e, e);
        end = e + n * 0x2c;
        FUN_009beec0(pos, at + n * 0x2c, tmp);
    }
}

// @ 0x009c1560
void HTable::DoInsertValue(void** out, void* key, u32_s009c_0f60* value, char reuse)
{
    // a key that is already stored and sorts before the incoming value keeps
    // its node; everything else links a fresh one
    u32_s009c_0f60 keep = 0;
    if (reuse == 0 && key != (void*)((u8_s009c_0f60*)this + 4) &&
        *(u32_s009c_0f60*)((u8_s009c_0f60*)key + 0x10) <= *value)
        keep = 1;

    void** node = (void**)*(void**)((u8_s009c_0f60*)this + 0x18);
    if (node == 0)
        node = (void**)EASTL_NEW(*(u32_s009c_0f60*)((u8_s009c_0f60*)this + 0x28));
    else
        *(void**)((u8_s009c_0f60*)this + 0x18) = *node;

    if (node != 0) node[4] = (void*)*value;

    RBTreeInsert(node, key, (u8_s009c_0f60*)this + 4, keep);
    ((u32_s009c_0f60*)((u8_s009c_0f60*)this + 0x14))[0]++;
    *out = node;
}

// @ 0x009c1630
HTable* HTableCtor(HTable* self, u32_s009c_0f60 bucketCount, void* allocator)
{
    void* pool[0x18 / 4];
    ((void**)pool)[0] = 0;                                  // mpHead
    fixed_pool_base_init(pool, (u8_s009c_0f60*)self + 0x7c, 0xc0, 0xc, 4, 0);

    void* node = FUN_00921340(0x11);
    FUN_009c09c0(node, (void*)bucketCount, &allocator, &allocator, allocator,
                 &allocator, pool);

    (*(float*)((u8_s009c_0f60*)self + 0x10)) = 1.0f;                   // 0x461c4000
    (*(float*)((u8_s009c_0f60*)self + 0x14)) = 2.0f;                   // 0x40000000
    *(void**)((u8_s009c_0f60*)self + 0x18) = 0;

    u32_s009c_0f60 need = FUN_009213c0(*(u32_s009c_0f60*)((u8_s009c_0f60*)self + 0x0c));
    if (*(u32_s009c_0f60*)((u8_s009c_0f60*)self + 0x08) < need)
        FUN_00a22220(need);                                 // Rehash
    return self;
}

// @ 0x009c1790
void Vec10c::InsertFill(u8_s009c_0f60* pos, unsigned n, const void* value)
{
    if ((unsigned)((cap - end) / 0x10c) < n) {
        unsigned have = (unsigned)((end - begin) / 0x10c);
        unsigned need = have + n;
        unsigned want = grow_count(have);
        if (need < want) need = want;
        u8_s009c_0f60* mem = (u8_s009c_0f60*)EASTL_NEW(need * 0x10c);
        u8_s009c_0f60* p = (u8_s009c_0f60*)FUN_009bf500(begin, pos, mem);
        FUN_009c0aa0(p, n, value);
        u8_s009c_0f60* newEnd = (u8_s009c_0f60*)FUN_009bf500(pos, end, p + n * 0x10c);
        EASTL_FREE(begin);
        begin = mem;
        end = newEnd;
        cap = mem + need * 0x10c;
        return;
    }
    if (n == 0) return;

    FUN_009be850(value);
    u8_s009c_0f60 tmp[0x10c];
    memcpy(tmp, value, 0x10c);
    u8_s009c_0f60* e = end;
    unsigned tail = (unsigned)((e - pos) / 0x10c);

    if (tail <= n) {
        FUN_009c0aa0(e, n - tail, tmp);
        end = e + (n - tail) * 0x10c;
        FUN_009bedb0(&n, pos, e, end);
        end += tail * 0x10c;
        FUN_009c0d40(pos, e, tmp);
    } else {
        u8_s009c_0f60* at = e - n * 0x10c;
        FUN_009bedb0(&n, at, e, e);
        end += n * 0x10c;
        FUN_009bf600(pos, at, e);
        FUN_009c0d40(pos, pos + n * 0x10c, tmp);
    }
}

// @ 0x009c1980
void Vec700::InsertFill(u8_s009c_0f60* pos, unsigned n, const void* value)
{
    if ((unsigned)((cap - end) / 700) < n) {
        unsigned have = (unsigned)((end - begin) / 700);
        unsigned need = have + n;
        unsigned want = grow_count(have);
        if (need < want) need = want;
        u8_s009c_0f60* mem = (u8_s009c_0f60*)EASTL_NEW(need * 700);
        u8_s009c_0f60* p = (u8_s009c_0f60*)FUN_009bf580(begin, pos, mem);
        FUN_009c0ad0(p, n, value);
        u8_s009c_0f60* newEnd = (u8_s009c_0f60*)FUN_009bf580(pos, end, p + n * 700);
        EASTL_FREE(begin);
        begin = mem;
        end = newEnd;
        cap = mem + need * 700;
        return;
    }
    if (n == 0) return;

    FUN_009bea50(value);
    u8_s009c_0f60 tmp[700];
    memcpy(tmp, value, 700);
    u8_s009c_0f60* e = end;
    unsigned tail = (unsigned)((e - pos) / 700);

    if (tail <= n) {
        FUN_009c0ad0(e, n - tail, tmp);
        end = e + (n - tail) * 700;
        FUN_009bedf0(&n, pos, e, end);
        end += tail * 700;
        FUN_009c0d70(pos, e, tmp);
    } else {
        u8_s009c_0f60* at = e - n * 700;
        FUN_009bedf0(&n, at, e, e);
        end += n * 700;
        FUN_009bf640(pos, at, e);
        FUN_009c0d70(pos, pos + n * 700, tmp);
    }
}

// @ 0x009c1b70
void BoolVec::Insert(u8_s009c_0f60* pos, u8_s009c_0f60* first, u8_s009c_0f60* last)
{
    if (first == last) return;

    u8_s009c_0f60* e = end;
    long bytes = last - first;
    unsigned words = (unsigned)(bytes >> 2);

    if (words <= (unsigned)((cap - e) >> 2)) {
        u8_s009c_0f60* at = e;
        unsigned have = (unsigned)((e - pos) >> 2);
        if (have <= words) {
            // build the new tail first, then insert the remainder in place
            u8_s009c_0f60* tail = first + have * 4;
            bool_insert_dispatch(at, tail, last - tail);
            end += (words - have) * 4;
            bool_insert_dispatch(end, pos, at - pos);
            end += have * 4;
            memmove(pos + (have - (unsigned)((tail - first) >> 2)) * 4,
                    first, tail - first);
            return;
        }
        u8_s009c_0f60* split = at - words * 4;
        bool_insert_dispatch(at, split, at - split);
        end += words * 4;
        memmove(split + words * 4, split, (size_t)(at - split));
        u8_s009c_0f60* head = split;
        bool_insert_dispatch(pos, first, bytes);
        (void)head;
        return;
    }

    unsigned have = (unsigned)((e - begin) >> 2);
    unsigned need = have + words;
    unsigned want = grow_count(have);
    if (need < want) need = want;

    u8_s009c_0f60* mem = (u8_s009c_0f60*)EASTL_NEW(need * 4);
    u8_s009c_0f60* head = pos;
    u8_s009c_0f60* p = (u8_s009c_0f60*)bool_insert_dispatch(mem, begin, head - begin);
    p += words * 4;
    p = (u8_s009c_0f60*)bool_insert_dispatch(p, first, bytes);
    p += (e - pos);
    bool_insert_dispatch(p, pos, e - pos);

    if (begin != 0 && begin != storage) EASTL_FREE(begin);
    end = p;
    begin = mem;
    cap = mem + need * 4;
}

// @ 0x009c1d30
void CreatureStaticData::CollectFlagged()
{
    int n = (int)(Bodies.end - Bodies.begin);
    if (n == 0) return;

    for (int off = 0; n != 0; off += 0x468, n--) {
        AnimNode* node = (AnimNode*)((char*)Bodies.begin + off);
        if ((node->flags & 8) != 0) {
            PendingRec rec;
            rec.node = node;
            rec.flag = 0;
            pending.Push(rec);
        }
    }
}

// @ 0x009c1dc0
void CreatureStaticData::Clear(int)
{
    name[0] = 0;
    filename[0] = 0;
    uid[0] = 0;
    uid[1] = 0;
    instance_id = 0;
    group_id = 0;
    type_id = 0;
    BranchPredicates = 1;

    // Bodies: run the range destructor, then rewind mpEnd by the whole-element
    // count.  The original spells this `mpEnd -= (mpEnd - mpBegin)` in element
    // units, so any partial trailing element (impossible for a well formed
    // vector) would survive the rewind.
    FUN_009b4310(Bodies.end, Bodies.end, Bodies.begin);
    Bodies.end -= Bodies.end - Bodies.begin;

    mMaxStraightLegLength_Scalable = -1;
    mGear = -1;
    num_bones_with_mesh_parts = -1;

    skin_colors[0].x1 = 1.0f;
    skin_colors[1].x1 = 1.0f;
    skin_colors[0].x2 = 1.0f;
    skin_colors[0].x3 = 1.0f;
    skin_colors[1].x2 = 1.0f;
    skin_colors[1].x3 = 1.0f;
    skin_colors[2].x1 = 1.0f;
    skin_colors[2].x2 = 1.0f;
    skin_colors[2].x3 = 1.0f;

    // inv_bone_rest_xforms: same destroy + whole-element rewind
    FUN_009b43f0(inv_bone_rest_xforms.end, inv_bone_rest_xforms.end,
                 inv_bone_rest_xforms.begin);
    inv_bone_rest_xforms.end -= inv_bone_rest_xforms.end -
                                inv_bone_rest_xforms.begin;

    f3c8 = 0;

    // pending: the original copies the 8-byte records backwards over themselves
    // and then rewinds mpEnd onto mpBegin by the same (dead) element count
    pending.end -= pending.end - pending.begin;

    f374 = 0.0f;
    f350 = 0;
    f354 = 0;
    f3f0 = 0;
    f3f5 = 0;
    f380 = 0;
    f3e0 = 0;
    f3ec = 4.0f;
}

// @ 0x009c1f60
namespace nSPCreatureAnim {
creature_static_data_s009c_1f60::creature_static_data_s009c_1f60()
{
    Bodies.mpBegin = 0;
    Bodies.mpEnd = 0;
    Bodies.mpCapacity = 0;
    mUnk398.mpBegin = 0;
    mUnk398.mpEnd = 0;
    mUnk398.mpCapacity = 0;
    skin_colors[0].x = skin_colors[0].y = skin_colors[0].z = 0.0f;
    skin_colors[1].x = skin_colors[1].y = skin_colors[1].z = 0.0f;
    skin_colors[2].x = skin_colors[2].y = skin_colors[2].z = 0.0f;
    mWiggles.mpBegin = 0;
    mWiggles.mpEnd = 0;
    mWiggles.mpCapacity = 0;
    local_aabb_origin.x = local_aabb_origin.y = local_aabb_origin.z = 0.0f;
    mUnk3cc.mpBegin = 0;
    mUnk3cc.mpEnd = 0;
    mUnk3cc.mpCapacity = 0;
    local_aabb_extent.x = local_aabb_extent.y = local_aabb_extent.z = 0.0f;
    inv_bone_rest_xforms.mpBegin = 0;
    inv_bone_rest_xforms.mpEnd = 0;
    inv_bone_rest_xforms.mpCapacity = 0;
    RefCount = 0;
    Clear(1);
}
}  // namespace nSPCreatureAnim

// @ 0x009c2050
namespace nSPCreatureAnim {
creature_static_data_s009c_1f60::~creature_static_data_s009c_1f60()
{
    Clear(0);
    if (inv_bone_rest_xforms.mpBegin && ((int*)inv_bone_rest_xforms.mpBegin)[-1] != 0)
        operator delete[](inv_bone_rest_xforms.mpBegin);
    if (mUnk3cc.mpBegin && ((int*)mUnk3cc.mpBegin)[-1] != 0)
        operator delete[](mUnk3cc.mpBegin);
    if (mWiggles.mpBegin && ((int*)mWiggles.mpBegin)[-1] != 0)
        operator delete[](mWiggles.mpBegin);
    if (mUnk398.mpBegin && ((int*)mUnk398.mpBegin)[-1] != 0)
        operator delete[](mUnk398.mpBegin);
    if (Bodies.mpBegin && ((int*)Bodies.mpBegin)[-1] != 0)
        operator delete[](Bodies.mpBegin);
}
}  // namespace nSPCreatureAnim

// @ 0x009c20e0
namespace nSPCreatureAnim {
void creature_instance_data_s009c_1f60::BuildBodyList()
{
    body_entry_list* list = building.func8Ch();
    unsigned count = (unsigned)(static_data->mUnk3cc.mpEnd - static_data->mUnk3cc.mpBegin);
    list->Resize((int)count);
    if (count == 0)
        return;

    unsigned k = 0;
    do {
        creature_body_static_data_s009c_1f60* sd0 = static_data->mUnk3cc.mpBegin[k].body;
        uint32 bidx = sd0->bidx;
        creature_body_instance_data_s009c_1f60* body = &Bodies.mpBegin[bidx];

        body_entry tmp;
        tmp.static_pair = &static_data->mUnk3cc.mpBegin[k];
        tmp.body = body;
        tmp.m[0] = tmp.m[1] = tmp.m[2] = tmp.m[3] = tmp.m[4] = tmp.m[5] = 0.0f;
        tmp.w0 = 1.0f;
        tmp.w1 = 0.0f;
        tmp.w2 = 0.0f;
        tmp.w3 = 1.0f;

        if (list->mpEnd < list->mpCapacity) {
            body_entry* p = list->mpEnd++;
            if (p)
                *p = tmp;
        } else {
            list->Append(list->mpEnd, tmp);
        }

        body_entry* e = &list->mpBegin[k];
        const creature_body_static_data_s009c_1f60* sd = e->body->static_data;
        float scale = requested_scale;
        e->m[0] = sd->rest_center.x * scale;
        e->m[1] = sd->rest_center.y * scale;
        e->m[2] = sd->rest_center.z * scale;
        if (!static_data->mIgnoreGait)
            e->m[2] = sd->unk_140 * scale;
        e->m[3] = sd->rest_orientation_q.x;
        e->m[4] = sd->rest_orientation_q.y;
        e->m[5] = sd->rest_orientation_q.z;
        e->w0 = sd->rest_orientation_q.w;

        if (body->static_data->cap_flags & 0x10) {
            int joint = FUN_009d7d10(this, &e->m[0], &e->m[3]);
            last_joint_index = joint + 1;
            void* table = *(void**)FUN_00a09f50();
            *(int*)((char*)table + joint * 0x108 + 0x58) = (int)bidx;
        }
        ++k;
    } while (k < count);
}
}  // namespace nSPCreatureAnim

// @ 0x009c2300
namespace nSPCreatureAnim {
bool creature_static_data_s009c_1f60::FilterAndAddWiggle(wiggle_static_data* w, bool keep, bool sym)
{
    unsigned count = (unsigned)(mWiggles.mpEnd - mWiggles.mpBegin);
    int found = -1;
    unsigned i = 0;
    if (count != 0) {
        do {
            wiggle_static_data* o = &mWiggles.mpBegin[i];
            if (w->cap_a == o->cap_a && w->cap_b == o->cap_b) {
                creature_body_static_data_s009c_1f60* bodies = Bodies.mpBegin;
                bool sameParent = bodies[w->body].parent_bidx == bodies[o->body].parent_bidx;
                int g = g_gait_channel;
                float oVal = PickGait(o, g);
                float wVal = PickGait(w, g);

                if (keep && o->channel == w->channel && fabs((double)oVal - (double)wVal) < 0.01f &&
                    FUN_009b3150(&bodies[o->body].cap_flags, &bodies[w->body].cap_flags)) {
                    w->flag = 1;
                    o->flag = 1;
                }
                if ((!sym || !sameParent) && (!keep || w->flag == 0)) {
                    if ((unsigned)o->channel < (unsigned)w->channel || wVal > oVal)
                        found = (int)i;
                    else
                        return false;
                }
            }
            ++i;
        } while (i < count);
    }

    AddWiggle(this, w);
    if (found != -1) {
        mWiggles.mpBegin[found] = *w;
        return true;
    }
    if (mWiggles.mpEnd < mWiggles.mpCapacity) {
        wiggle_static_data* p = mWiggles.mpEnd++;
        if (p)
            *p = *w;
        return true;
    }
    mWiggles.DoInsert(mWiggles.mpEnd, *w);
    return true;
}
}  // namespace nSPCreatureAnim

// @ 0x009c2520
namespace nSPCreatureAnim {
void bone_xform_vec::resize(unsigned n)
{
    unsigned s = (unsigned)(mpEnd - mpBegin);
    if (n > s) {
        bone_xform value;
        DoInsertValues(mpEnd, n - s, value);
    } else {
        bone_xform* first = mpBegin + n;
        bone_xform* last = mpEnd;
        CopyBoneXforms(last, mpEnd, first);
        mpEnd -= (last - first);
    }
}
}  // namespace nSPCreatureAnim

// @ 0x009c25f0
namespace nSPCreatureAnim {
void wiggle_instance_vec::resize(unsigned n)
{
    unsigned s = (unsigned)(mpEnd - mpBegin);
    if (n > s) {
        wiggle_instance_data value;
        DoInsertValues(mpEnd, n - s, value);
    } else {
        wiggle_instance_data* first = mpBegin + n;
        wiggle_instance_data* last = mpEnd;
        DestroyWiggleInstances(last, mpEnd, first);
        mpEnd -= (last - first);
    }
}
}  // namespace nSPCreatureAnim

// @ 0x009c26a0
namespace nSPCreatureAnim {
int creature_static_data_s009c_1f60::Release()
{
    int n = RefCount - 1;
    if (n < 1)
        n = 0;
    RefCount = n;
    if (n < 1) {
        RefCount = 1;
        this->~creature_static_data_s009c_1f60();
        operator delete[](this);
        return 0;
    }
    return n;
}
}  // namespace nSPCreatureAnim

// @ 0x009c26f0
namespace nSPCreatureAnim {
void creature_static_data_s009c_1f60::InitWiggles()
{
    const bool legless = mIsLegless != 0;
    const bool keep = !legless;

    {
        wiggle_static_data* first = mWiggles.mpBegin;
        wiggle_static_data* last = mWiggles.mpEnd;
        mWiggles.erase(first, last);
    }

    unsigned n = (unsigned)(Bodies.mpEnd - Bodies.mpBegin);
    for (unsigned i = 0; i < n; ++i) {
        wiggle_static_data w;
        if (CreateWiggle(this, (int)i, &w, 0, 1, 1, legless, 0, 0))
            FilterAndAddWiggle(&w, keep, true);
    }

    // temporary pool + fixed_map<unsigned, void*, 255> (parents of the dropped symmetric pairs)
    uint32 poolBuf[0x13ec / 4];
    FixedNodePool pool;
    pool.mpHead = 0;
    pool.init(poolBuf, 0x13ec, 0x14, 4, 0);
    pool.mpNext = poolBuf;
    pool.mpCapacity = (char*)poolBuf + 0x13ec;
    pool.mnNodeSize = 0x14;

    FixedMapU32 map;
    map.mpNodeRight = 0;
    map.mpNodeLeft = 0;
    map.mpNodeParent = 0;
    map.mColor = 0;
    map.mnSize = 0;
    map.mAllocator.mpHead = 0;
    map.mAllocator.init(pool.mpHead, 0x13ec, 0x14, 4, 0);
    map.mAllocator.mpNext = pool.mpHead;
    map.mAllocator.mpCapacity = (char*)pool.mpHead + 0x13ec;
    map.mpNodeRight = map.anchor();
    map.mpNodeLeft = map.anchor();
    map.mpNodeParent = 0;
    map.mColor = 0;
    map.mnSize = 0;
    map.mAllocator.mnNodeSize = 0x14;

    FixedVecU32 list;
    list.mpBegin = list.mBuffer;
    list.mpEnd = list.mBuffer;
    list.mpCapacity = list.mBuffer + 255;
    list.mpBuffer = list.mBuffer;

    unsigned wcount = (unsigned)(mWiggles.mpEnd - mWiggles.mpBegin);
    for (unsigned a = 0; a < wcount; ++a) {
        wiggle_static_data* wa = &mWiggles.mpBegin[a];
        creature_body_static_data_s009c_1f60* bodies = Bodies.mpBegin;
        creature_body_static_data_s009c_1f60* bodyA = &bodies[wa->body];
        int waParent = bodyA->parent_bidx;
        float waVal = PickGait(wa, g_gait_channel);

        wiggle_static_data* wb = mWiggles.mpBegin;
        for (unsigned b = 0; b < wcount; ++b, ++wb) {
            if (a == b)
                continue;
            if (waParent != bodies[wb->body].parent_bidx)
                continue;
            float wbVal = PickGait(wb, g_gait_channel);
            if (!keep || wa->flag == 0) {
                if (wb->flag == 0 && ((unsigned)wa->channel < (unsigned)wb->channel || waVal < wbVal)) {
                    list.push_back(a);
                    break;
                }
            } else if (!((bodyA->cap_flags >> 2) & 1)) {
                KVPair kv;
                kv.first = (uint32)waParent;
                kv.second = 0;
                map.insert(kv, RbTrueType());
                list.push_back(a);
                break;
            }
        }
    }

    // Erase the marked wiggles, highest index first.
    for (int idx = (int)(list.mpEnd - list.mpBegin) - 1; idx >= 0; --idx)
        mWiggles.erase(mWiggles.mpBegin + list.mpBegin[idx]);

    // Symmetry pass over the collected parents.
    if (g_wiggle_symmetry != 0) {
        RBNodeU32* node = map.mpNodeLeft;
        if (node != map.anchor()) {
            do {
                wiggle_static_data w;
                if (CreateWiggle(this, (int)node->mKey, &w, 0, 0, 1, legless, 0, 0))
                    FilterAndAddWiggle(&w, false, false);
                node = RBTreeIncrementU32(node);
            } while (node != map.anchor());
        }
    }

    if (list.mpBegin && list.mpBegin != list.mpBuffer)
        operator delete[](list.mpBegin);
    map.DoNukeSubtree(map.mpNodeParent);
}
}  // namespace nSPCreatureAnim

// @ 0x009c2c20
namespace nSPCreatureAnim {
void creature_instance_data_s009c_1f60::InitWiggles()
{
    unsigned n = (unsigned)(static_data->mWiggles.mpEnd - static_data->mWiggles.mpBegin);
    mWiggles.resize(n);

    unsigned count = (unsigned)(mWiggles.mpEnd - mWiggles.mpBegin);
    for (unsigned i = 0; i < count; ++i) {
        wiggle_instance_data* e = &mWiggles.mpBegin[i];
        wiggle_static_data* sw = &static_data->mWiggles.mpBegin[i];
        e->flag4 = 0;
        e->flag5 = 0;
        e->wiggle = sw;

        creature_body_static_data_s009c_1f60* bsd = Bodies.mpBegin[sw->body].static_data;
        float scale = requested_scale;
        float Y = bsd->rest_center.y * scale;
        float X = scale * bsd->rest_center.x;
        float Z = bsd->rest_center.z * scale;
        e->zero.x = e->zero.y = e->zero.z = 0.0f;

        float q0 = orientation.x, q1 = orientation.y, q2 = orientation.z, q3 = orientation.w;
        float q1q3 = q1 * q3;
        float q0q3 = q0 * q3;
        float q2q3 = q2 * q3;
        float nq0q0 = -(q0 * q0);
        float q1q0 = q1 * q0;
        float q2q0 = q2 * q0;
        float nq1q1 = -(q1 * q1);
        float q2q1 = q2 * q1;
        float nq2q2 = -(q2 * q2);

        float A = nq2q2 + nq0q0;
        float B = nq2q2 + nq1q1;
        float C = q2q0 + q1q3;
        float D = q1q0 - q2q3;
        float E = q1q0 + q2q3;
        float F = q2q1 - q0q3;
        float G = q2q0 - q1q3;
        float H = nq1q1 + nq0q0;
        float J = q2q1 + q0q3;

        float T1 = ((B * X + C * Z) + D * Y) * 2.0f + X;
        float T2 = ((E * X + A * Y) + F * Z) * 2.0f + Y;
        float T3 = ((G * X + H * Z) + J * Y) * 2.0f + Z;

        e->pos.x = position.x + T1;
        e->pos.y = position.y + T2;
        e->pos.z = position.z + T3;
        e->pos_copy = e->pos;
    }

    f_16a8 = 0.0f;
    inst_a.flag4 = 0;
    inst_a.flag5 = 1;
    inst_a.wiggle = &desc_a;
    CreateWiggle(static_data, 0, &desc_b, 1, 0, 0, 0, 0, 0);
    inst_b.wiggle = &desc_b;
    inst_b.flag4 = 0;
    inst_b.flag5 = 1;
    flag_168e = 1;
    f_1690 = 0.0f;
}
}  // namespace nSPCreatureAnim

// @ 0x009c2ef0
void IKVec::Resize(unsigned n)
{
    IkConstraint* e = end;
    IkConstraint* b = begin;
    unsigned have = (unsigned)(e - b);

    if (n > have) {
        IkConstraint t;
        t.v0.x1 = t.v0.x2 = t.v0.x3 = 0.0f;
        t.v1.x1 = t.v1.x2 = t.v1.x3 = 0.0f;
        t.v2.x1 = t.v2.x2 = t.v2.x3 = 0.0f;
        t.v3.x1 = t.v3.x2 = t.v3.x3 = 0.0f;
        t.v4.x1 = t.v4.x2 = t.v4.x3 = 0.0f;
        t.v5.x1 = t.v5.x2 = t.v5.x3 = 0.0f;
        t.v6.x1 = t.v6.x2 = t.v6.x3 = 0.0f;
        t.v7.x1 = t.v7.x2 = t.v7.x3 = 0.0f;
        t.v8.x1 = t.v8.x2 = t.v8.x3 = 0.0f;
        InsertFill(e, n - have, &t);
    } else {
        IkConstraint* newEnd = b + n;
        FUN_009bf540(e, e, newEnd);
        end -= e - newEnd;
    }
}

// @ 0x009c3040
void WiggleVec::Resize(unsigned n)
{
    BodyAnimC_s009c_2ef0* e = end;
    BodyAnimC_s009c_2ef0* b = begin;
    unsigned have = (unsigned)(e - b);

    if (n > have) {
        BodyAnimC_s009c_2ef0 t;
        BodyAnimC_s009c_2ef0* src = t.Ctor();
        InsertFill(end, n - (unsigned)(end - begin), src);
    } else {
        BodyAnimC_s009c_2ef0* newEnd = b + n;
        FUN_009bf5c0(e, e, newEnd);
        end -= e - newEnd;
    }
}

// @ 0x009c3150
int FUN_009c3150(AnimOwner* a, WordVec* v, u32_s009c_2ef0** base, unsigned idx)
{
    BodyNode* node = &a->bodies[idx];

    unsigned prev = node->prevCount;
    node->prevCount = (unsigned)(((char*)v->end - (char*)v->begin) >> 2);
    unsigned n = node->count;
    node->total = (int)n;
    if (n == 0) return 0;

    unsigned off = prev * 4;
    v->Insert(v->end, (u32_s009c_2ef0*)((char*)*base + off),
              (u32_s009c_2ef0*)((char*)*base + off + n * 4), a);

    for (unsigned i = 0; i < node->count; i++) {
        node->total += FUN_009c3150(a, v, base, *(u32_s009c_2ef0*)((char*)*base + off));
        off += 4;
    }
    return node->total;
}

// @ 0x009c3210
FixedVec* FixedVec::Init(void* a, void* b)
{
    u8_s009c_2ef0* s = storage;
    buf = s;
    end = s;
    begin = s;
    cap = s + 0x3fc;
    Setup(a, b);
    return this;
}

// @ 0x009c3240
void PhaseGroupVec::DestroyValues(PhaseGroup* p, PhaseGroup* e)
{
    for (; p < e; ++p) {
        void* b = p->block;
        if (b != 0 && *(int*)((char*)b - 4) != 0)
            operator delete(b);

        char* qe = (char*)p->subEnd;
        for (char* q = (char*)p->subBegin; q < qe; q += 0x38) {
            void* sub = *(void**)(q + 4);
            if (sub != 0 && *(int*)((char*)sub - 4) != 0)
                operator delete(sub);
        }

        void* r = p->subBegin;
        if (r != 0 && *(int*)((char*)r - 4) != 0)
            operator delete(r);
    }
}

// @ 0x009c32c0
namespace nSPCreatureAnim {
bool ComputeHierarchy(creature_static_data_s009c_32c0* c, uint32_s009c_32c0 target)
{
    if (c->Bodies.mpBegin == c->Bodies.mpEnd)
        return false;
    if (target >= c->Bodies.size())
        return false;
    if (!(c->Bodies[target].owned_cap_flags & kCapSpine))
        return false;
    if (c->Bodies[target].parent_bidx != -1)
        return false;

    // Trailing bodies without a bone don't count as bones.
    c->num_bones = c->Bodies.size();
    while (c->num_bones != 0 && c->Bodies[c->num_bones - 1].bone_idx == (uint32_s009c_32c0)-1)
        c->num_bones--;

    // Spines carrying the most feet (counted at the nearest spine ancestor of each foot).
    index_vector bestSpines;
    uint32_s009c_32c0 zero = 0;
    index_vector footCounts(c->Bodies.size(), zero);
    int rootCapBody = -1;
    {
        uint32_s009c_32c0 maxFeet = 0;
        unsigned n = c->Bodies.size();
        for (unsigned i = 0; i < n; ++i) {
            creature_body_static_data_s009c_32c0& b = c->Bodies[i];
            if (b.cap_flags & kCapRoot) {
                rootCapBody = i;
                break;
            }
            if (b.owned_cap_flags & kCapFoot) {
                uint32_s009c_32c0 spine = b.parent_bidx;
                while (spine != (uint32_s009c_32c0)-1 && !(c->Bodies[spine].owned_cap_flags & kCapSpine))
                    spine = c->Bodies[spine].parent_bidx;
                footCounts[spine]++;
                uint32_s009c_32c0 feet = footCounts[spine];
                if (feet > maxFeet) {
                    bestSpines.resize(0);
                    maxFeet = feet;
                    bestSpines.push_back(spine);
                } else if (feet == maxFeet) {
                    bestSpines.push_back(spine);
                }
            }
        }
    }

    // Inverse bone rest transforms, last spine index and symmetry links.
    c->spine_end_bidx = 0;
    c->spine_start_bidx = 0;
    c->inv_bone_rest_xforms.resize(c->num_bones);
    {
        unsigned n = c->Bodies.size();
        for (unsigned i = 0; i < n; ++i) {
            creature_body_static_data_s009c_32c0& b = c->Bodies[i];
            uint32_s009c_32c0 bone = b.bone_idx;
            if (bone < c->num_bones)
                ComputeInverseRestXform(b, c->inv_bone_rest_xforms.mpBegin[bone]);

            if (b.owned_cap_flags & kCapSpine)
                c->spine_end_bidx = eastl::max(c->spine_end_bidx, (uint32_s009c_32c0)i);

            if (b.symmetric_bidx == -2) {
                vector_3_s009c_32c0 mirrored;
                mirrored.x = -b.rest_center.x;
                mirrored.y = b.rest_center.y;
                mirrored.z = b.rest_center.z;
                unsigned j;
                for (j = 0; j < n; ++j) {
                    if (i == j)
                        continue;
                    creature_body_static_data_s009c_32c0& o = c->Bodies[j];
                    double dx = (double)o.rest_center.x - mirrored.x;
                    double dy = (double)o.rest_center.y - mirrored.y;
                    double dz = (double)o.rest_center.z - mirrored.z;
                    if (!((dz * dz + dy * dy) + dx * dx < 1e-05))
                        continue;
                    unsigned k;
                    for (k = 0; k < 32; ++k) {
                        if (b.NameFOURCCs[k] == 0)
                            break;
                        if (b.NameFOURCCs[k] != o.NameFOURCCs[k])
                            break;
                    }
                    if (k < 32 && b.NameFOURCCs[k] != 0)
                        continue;   // caps differ
                    b.symmetric_bidx = j;
                    break;
                }
                if (j == n)
                    b.symmetric_bidx = -1;
            }
        }
    }

    // Choose the root.
    int root = -1;
    if (g_bRootAtClosestSpine) {
        float best = 3.402823466e+38f;
        int n = (int)c->Bodies.size();
        for (int i = 0; i < n; ++i) {
            creature_body_static_data_s009c_32c0& b = c->Bodies[i];
            if (b.owned_cap_flags & kCapSpine) {
                const vector_3_s009c_32c0& p = b.rest_center;
                float d = (p.x * p.x + p.y * p.y) + p.z * p.z;
                if (d < best) {
                    best = d;
                    root = i;
                }
            }
        }
    }
    if (root == -1)
        root = rootCapBody;

    bool legless = bestSpines.empty();
    c->mIsLegless = legless;
    if (root == -1) {
        if (!legless) {
            // The highest spine among those carrying the most feet.
            float bestY = -3.402823466e+38f;
            unsigned count = bestSpines.size();
            for (unsigned k = 0; k < count; ++k) {
                uint32_s009c_32c0 idx = bestSpines[k];
                float y = c->Bodies[idx].rest_center.y;
                if (y > bestY) {
                    bestY = y;
                    root = idx;
                }
            }
        } else {
            root = 0;
            if (g_bRootAtMidSpine) {
                index_vector spines;
                unsigned n = c->Bodies.size();
                for (uint32_s009c_32c0 i = 0; i < n; ++i)
                    if (c->Bodies[i].owned_cap_flags & kCapSpine)
                        spines.push_back(i);
                unsigned numSpines = spines.size();
                if (numSpines > 2) {
                    // Child-spine counts; walk up half the spine count from a spine end.
                    index_vector childSpines;
                    childSpines.resize(n);
                    for (unsigned i = 0; i < n; ++i) {
                        creature_body_static_data_s009c_32c0& b = c->Bodies[i];
                        int p = b.parent_bidx;
                        if (p != -1 && (b.owned_cap_flags & kCapSpine))
                            childSpines[p]++;
                    }
                    for (unsigned k = 0; k < numSpines; ++k) {
                        uint32_s009c_32c0 idx = spines[k];
                        if (childSpines[idx] == 0) {
                            if (idx != (uint32_s009c_32c0)-1) {
                                for (unsigned steps = 0; steps < (numSpines >> 1); ++steps) {
                                    idx = c->Bodies[idx].parent_bidx;
                                    if (idx == (uint32_s009c_32c0)-1)
                                        break;
                                }
                                if (idx != (uint32_s009c_32c0)-1)
                                    root = idx;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    creature_body_static_data_s009c_32c0& rb = c->Bodies[root];
    if (!(rb.owned_cap_flags & kCapSpine))
        return false;

    // Give the root a "root" cap and recompute its cap flags.
    for (unsigned k = 0; k < 32; ++k) {
        if (rb.NameFOURCCs[k] == kCapNameRoot) {
            rb.Values[k] = 1;
            break;
        }
        if (rb.NameFOURCCs[k] == 0) {
            rb.NameFOURCCs[k] = kCapNameRoot;
            rb.Values[k] = 1;
            break;
        }
    }
    rb.owned_cap_flags = 0;
    rb.cap_flags = 0;
    for (unsigned k = 0; k < 32; ++k) {
        uint32_s009c_32c0 capName = rb.NameFOURCCs[k];
        if (capName == 0)
            break;
        uint32_s009c_32c0 flag = CapFlagFromName(capName);
        rb.cap_flags |= flag;
        if (rb.Values[k])
            rb.owned_cap_flags |= flag;
    }

    // Re-root: reverse the parent chain from the new root, moving the joint vectors along.
    if ((uint32_s009c_32c0)root != target) {
        vector_3_s009c_32c0 carriedLocal = rb.parent_local_joint_r;
        vector_3_s009c_32c0 carriedParent = rb.local_joint_r;
        int prev = -1;
        for (int idx = root; idx != -1;) {
            creature_body_static_data_s009c_32c0& b = c->Bodies[idx];
            int next = b.parent_bidx;
            b.parent_bidx = prev;
            vector_3_s009c_32c0 oldLocal = b.local_joint_r;
            vector_3_s009c_32c0 oldParent = b.parent_local_joint_r;
            b.local_joint_r = carriedLocal;
            b.parent_local_joint_r = carriedParent;
            if (b.cap_flags & kCapSpine) {
                b.joint_r.x = b.local_joint_r.x - b.rest_joint_offset.x;
                b.joint_r.y = b.local_joint_r.y - b.rest_joint_offset.y;
                b.joint_r.z = b.local_joint_r.z - b.rest_joint_offset.z;
            } else {
                b.joint_r = b.local_joint_r;
            }
            b.joint_r_len = (float)sqrt(((double)b.joint_r.x * b.joint_r.x +
                                         (double)b.joint_r.y * b.joint_r.y) +
                                        (double)b.joint_r.z * b.joint_r.z);
            carriedLocal = oldParent;
            carriedParent = oldLocal;
            prev = idx;
            idx = next;
        }
        c->Bodies[target].num_children--;
        rb.num_children++;
        target = root;
    }
    rb.parent_local_joint_r.x = 0.0f;
    rb.parent_local_joint_r.y = 0.0f;
    rb.parent_local_joint_r.z = 0.0f;
    rb.local_joint_r.x = 0.0f;
    rb.local_joint_r.y = 0.0f;
    rb.local_joint_r.z = 0.0f;
    rb.joint_r.x = 0.0f;
    rb.joint_r.y = 0.0f;
    rb.joint_r.z = 0.0f;
    rb.joint_r_len = 0.0f;

    // Hierarchy order: order[0] = root; footCounts is reused as the child-slot table.
    index_vector order;
    order.resize(c->Bodies.size());
    order.resize(1);
    order[0] = target;
    index_vector& children = footCounts;
    children.resize(c->Bodies.size());

    {
        unsigned n = c->Bodies.size();
        int nextSlot = 1;
        for (unsigned i = 0; i < n; ++i) {
            creature_body_static_data_s009c_32c0& b = c->Bodies[i];
            b.first_child_bidx = nextSlot;
            nextSlot += b.num_children;
            b.num_children = 0;
        }
    }
    {
        unsigned n = c->Bodies.size();
        for (unsigned i = 0; i < n; ++i) {
            int p = c->Bodies[i].parent_bidx;
            if (p == -1)
                continue;
            creature_body_static_data_s009c_32c0& parent = c->Bodies[p];
            uint32_s009c_32c0 slot = parent.num_children + parent.first_child_bidx;
            children[slot] = i;
            uint32_s009c_32c0 numChildren = parent.num_children;
            if (numChildren && (c->Bodies[i].cap_flags & kCapSpine)) {
                // Keep a spine child first (for the root, second if a spine is already first).
                if (parent.parent_bidx == -1) {
                    uint32_s009c_32c0& first = children[parent.first_child_bidx];
                    if (!(c->Bodies[first].cap_flags & kCapSpine))
                        eastl::swap(children[slot], first);
                    else if (numChildren > 1)
                        eastl::swap((&first)[1], children[slot]);
                } else {
                    eastl::swap(children[slot], children[parent.first_child_bidx]);
                }
            }
            parent.num_children++;
        }
    }

    BuildHierarchyOrder(c, &order, &children, target);

    // Copy the bodies into hierarchy order, remapping indices and rebuilding relative rotations.
    body_vector_s009c_32c0 sorted(c->Bodies.size(), eastl::sp_vector_allocator_s009c_32c0());
    {
        unsigned n = c->Bodies.size();
        bool startRemapped = false;
        bool endRemapped = false;
        for (unsigned k = 0; k < n; ++k) {
            uint32_s009c_32c0 src = order[k];
            creature_body_static_data_s009c_32c0& old = c->Bodies[src];
            creature_body_static_data_s009c_32c0& nb = sorted[k];
            nb.CopyFrom(old);
            nb.bidx = k;
            old.parent_bidx = k;   // old index -> new index, used for the remaps below
            if (nb.parent_bidx != -1) {
                nb.parent_bidx = c->Bodies[nb.parent_bidx].parent_bidx;
                const vector_4_s009c_32c0& pq = sorted[nb.parent_bidx].rest_orientation_q;
                const vector_4_s009c_32c0& q = nb.rest_orientation_q;
                vector_4_s009c_32c0& r = nb.rest_parent_rel_orientation_q;
                r.x = ((q.x * pq.w - q.w * pq.x) + q.y * pq.z) - q.z * pq.y;
                r.y = ((q.y * pq.w - q.w * pq.y) - q.x * pq.z) + q.z * pq.x;
                r.z = ((q.x * pq.y - q.w * pq.z) - q.y * pq.x) + q.z * pq.w;
                r.w = ((q.y * pq.y + q.x * pq.x) + q.w * pq.w) + q.z * pq.z;
            }
            if (!startRemapped && c->spine_start_bidx == src) {
                c->spine_start_bidx = k;
                startRemapped = true;
            }
            if (!endRemapped && c->spine_end_bidx == src) {
                c->spine_end_bidx = k;
                endRemapped = true;
            }
        }
    }
    {
        unsigned n = c->Bodies.size();
        for (unsigned i = 0; i < n; ++i) {
            creature_body_static_data_s009c_32c0& nb = sorted[i];
            if ((uint32_s009c_32c0)nb.symmetric_bidx < n)
                nb.symmetric_bidx = c->Bodies[nb.symmetric_bidx].parent_bidx;
        }
    }
    c->Bodies.swap(sorted);

    if (!c->mIsLegless) {
        AddExtraBonesAsNecessary(c, c->spine_start_bidx);
        AddExtraBonesAsNecessary(c, c->spine_end_bidx);
    }

    // Parent / first-child pointers.
    {
        unsigned n = c->Bodies.size();
        for (unsigned i = 0; i < n; ++i) {
            creature_body_static_data_s009c_32c0& b = c->Bodies[i];
            b.parent = i ? &c->Bodies[b.parent_bidx] : 0;
            b.first_child = b.num_children ? &c->Bodies[b.first_child_bidx] : 0;
            b.in_leg_chain = false;
        }
    }
    // Workspace radius: parent's radius plus the padded distance to the parent.
    {
        unsigned n = c->Bodies.size();
        for (unsigned i = 0; i < n; ++i) {
            creature_body_static_data_s009c_32c0& b = c->Bodies[i];
            if (i == 0) {
                b.workspace_radius = 3.0f;
                continue;
            }
            float base = (b.parent_bidx == 0) ? 0.0f : b.parent->workspace_radius;
            const vector_3_s009c_32c0& pc = b.parent->rest_center;
            double dx = (double)pc.x - b.rest_center.x;
            float dy = pc.y - b.rest_center.y;
            float dz = pc.z - b.rest_center.z;
            double len = sqrt(((double)dy * dy + (double)dz * dz) + dx * dx);
            b.workspace_radius =
                (float)(((g_WorkspaceRadiusPad + 1.0) * len) * g_WorkspaceRadiusScale + base);
        }
    }
    // Leg chains: a body with a foot below it (or a foot itself) marks its parent.
    for (int i = (int)c->Bodies.size() - 1; i >= 0; --i) {
        creature_body_static_data_s009c_32c0& b = c->Bodies[i];
        if (b.in_leg_chain || (b.cap_flags & kCapFoot)) {
            b.in_leg_chain = true;
            if (b.parent)
                b.parent->in_leg_chain = true;
        } else {
            b.in_leg_chain = false;
        }
    }

    ComputeBodyStatics(c);
    return true;
}
}  // namespace nSPCreatureAnim

// @ 0x009c4a30
namespace nSPCreatureAnim {
uint32 FinalizeCreature(creature_static_data_s009c_4a30* c)
{
    if (!ComputeHierarchy(c, 0))
        return 0;

    float l18 = 0.0f, l14 = 0.0f, l10 = 0.0f;
    float lc = 0.0f, l8 = 0.0f, l4 = 0.0f;
    FUN_009b6b10(&l18, &lc, c);

    *(float*)((char*)c + 0x358) = l18;
    lc = lc - l18;
    *(float*)((char*)c + 0x35c) = l14;
    float f3 = l8 - l14;
    float f4 = l4 - l10;
    *(float*)((char*)c + 0x360) = l10;
    *(float*)((char*)c + 0x364) = lc;
    *(float*)((char*)c + 0x368) = f3;
    *(float*)((char*)c + 0x36c) = f4;
    *(float*)((char*)c + 0x370) = sqrtf(lc * lc + (f4 * f4 + f3 * f3));

    c->FUN_009c1d30();
    c->FUN_009b54a0();
    if (*(int*)((char*)c + 0x3c8) == 0) {
        c->FUN_009b5580();
        c->FUN_009b5930();
    }
    c->FUN_009bfa20();
    c->InitWiggles();
    *(float*)((char*)c + 0x374) = c->FUN_009b5360();
    FUN_009b5ce0(c);

    int n = (int)((*(char**)((char*)c + 0x388) - *(char**)((char*)c + 0x384)) / 0x468);
    return (uint32)(n < 0x100);
}
}  // namespace nSPCreatureAnim

// @ 0x009c4b90
namespace nSPCreatureAnim {
dynamics_walking_s009c_4a30::~dynamics_walking_s009c_4a30()
{
    if (vert && ((int*)vert)[-1] != 0)
        operator delete[](vert);
    if (feet && ((int*)feet)[-1] != 0)
        operator delete[](feet);
    groups.DoDestroyValues(groups.mpBegin, groups.mpEnd);
    if (groups.mpBegin && ((int*)groups.mpBegin)[-1] != 0)
        operator delete[](groups.mpBegin);
}
}  // namespace nSPCreatureAnim

// @ 0x009c4bf0
namespace nSPCreatureAnim {
creature_instance_data_s009c_4a30::~creature_instance_data_s009c_4a30()
{
    char* b = (char*)this;
    instance_hashtable* ht = (instance_hashtable*)(b + 0x17a0);
    ht->DoFreeNodes(ht->mpBucketArray, (void*)ht->mnBucketCount);
    {
        void* e = ht->mpBucketArray;
        ht->mnElementCount = 0;
        if (ht->mnBucketCount > 1 && e != ht->mpFixedBuffer) {
            if (e < ht->mpPoolBegin || e >= ht->mpPoolEnd)
                operator delete[](e);
            else {
                *(void**)e = ht->mpFreeList;
                ht->mpFreeList = e;
            }
        }
    }
    if (*(void**)(b + 0x1694) && ((int*)*(void**)(b + 0x1694))[-1] != 0)
        operator delete[](*(void**)(b + 0x1694));
    ((dynamics_walking_s009c_4a30*)(b + 0x15b8))->~dynamics_walking_s009c_4a30();
    ((sub_2f8*)(b + 0x2f8))->FUN_009b59c0();
    if (*(void**)(b + 0x2e4) && ((int*)*(void**)(b + 0x2e4))[-1] != 0)
        operator delete[](*(void**)(b + 0x2e4));
    if (*(void**)(b + 0x294))
        ((creature_instance_data_s009c_4a30*)*(void**)(b + 0x294))->Release();
    if (*(void**)(b + 0x24c) && ((int*)*(void**)(b + 0x24c))[-1] != 0)
        operator delete[](*(void**)(b + 0x24c));
    creature_static_data_s009c_4a30* sd = *(creature_static_data_s009c_4a30**)b;
    if (sd)
        sd->Release();
}
}  // namespace nSPCreatureAnim

// @ 0x009c4cc0
long nSPCreatureAnim::creature_instance_data::Release()
{
    char* b = (char*)this;
    int n = *(int*)(b + 0x14) - 1;
    int zero = 0;
    const int& r = (zero < n) ? n : zero;
    n = r;
    *(int*)(b + 0x14) = n;
    if (n <= 0) {
        *(int*)(b + 0x14) = 1;
        this->~creature_instance_data();
        operator delete[](this);
        return 0;
    }
    return n;
}

// @ 0x009c4d10
namespace nSPCreatureAnim {
void creature_instance_data_s009c_4a30::FUN_009c4d10()
{
    char* b = (char*)this;
    if (*(int*)(b + 0x294) != 0) {
        void* p = *(void**)(b + 0x294);
        *(uint32*)(b + 0x294) = 0;
        ((creature_instance_data_s009c_4a30*)p)->Release();
    }
    FUN_009cb4f0();
    *(uint8*)(b + 0xc) = 0;
}
}  // namespace nSPCreatureAnim

// @ 0x009c4d40
namespace nSPCreatureAnim {
void creature_instance_data_s009c_4a30::Clear(bool flag)
{
    char* b = (char*)this;
    creature_static_data_s009c_4a30* sd;

    if (flag) {
        sd = *(creature_static_data_s009c_4a30**)b;
        *(uint32*)(b + 0x2c0) = 0;
        if (sd) { *(void**)b = 0; sd->Release(); }
        *(uint8*)(b + 0xc) = 0;
    }

    sd = *(creature_static_data_s009c_4a30**)b;
    *(uint32*)(b + 0x2c0) = 0;
    if (sd) { *(void**)b = 0; sd->Release(); }
    *(uint32*)(b + 4) = 0;
    *(uint32*)(b + 8) = 0;

    // Bodies.clear()
    {
        vec2bc* v = (vec2bc*)(b + 0x2e4);
        Elem2bc* be = v->mpBegin;
        Elem2bc* en = v->mpEnd;
        FUN_009bf5c0(en, en, be);
        v->mpEnd += (en - be);
    }
    *(uint32*)(b + 0x10) = (uint32)this >> 4;
    *(uint8*)(b + 0xc) = 0;
    FUN_009cb4f0();

    F(0x34) = 0.0f;  F(0x38) = 0.0f;  F(0x30) = 0.0f;  F(0x18) = 0.0f;
    V2AT(0x1c) = V2AT(0x34);
    F(0x24) = 0.0f;
    V2AT(0x28) = V2AT(0x1c);
    F(0x60) = 0.0f;  F(0x64) = 0.0f;  F(0x68) = 1.0f;  F(0x5c) = 0.0f;  F(0x3c) = 0.0f;
    V3AT(0x40) = V3AT(0x60);
    F(0x4c) = 0.0f;
    V3AT(0x50) = V3AT(0x40);
    F(0x6c) = 1.0f;  F(0x70) = 1.0f;
    F(0xb4) = 0.0f;  F(0xb8) = 0.0f;  F(0xb0) = 0.0f;  F(0x98) = 0.0f;
    V2AT(0x9c) = V2AT(0xb4);
    F(0x8c) = 0.0f;
    V2AT(0x90) = V2AT(0x9c);
    F(0x80) = 0.0f;
    V2AT(0x84) = V2AT(0x90);
    F(0x74) = 0.0f;
    V2AT(0x78) = V2AT(0x84);
    F(0xc8) = 0.0f;  F(0xcc) = 0.0f;  F(0xd0) = 0.0f;  F(0xd4) = 1.0f;
    F(0xa4) = 0.0f;  F(0xa8) = 0.0f;  F(0xac) = 0.0f;
    F(0xbc) = 0.0f;  F(0xc0) = 0.0f;  F(0xc4) = 0.0f;
    F(0xd8) = 0.0f;  F(0xdc) = 0.0f;  F(0xe0) = 0.0f;  F(0xe4) = 0.0f;
    F(0x110) = 0.0f; F(0x114) = 0.0f;
    {
        M3* mm = (M3*)(b + 0x118);
        float* m = mm->f;
        m[0] = 0.0f;
        m[1] = 0.0f;
        m[2] = 0.0f;
        m[3] = 0.0f;
        m[4] = 0.0f;
        m[5] = 0.0f;
        m[6] = 0.0f;
        m[7] = 0.0f;
        m[8] = 0.0f;
        mm->FUN_0099ce40();
    }

    F(0x13c) = 0.0f;
    F(0x140) = 0.0f;
    F(0x144) = 0.0f;
    F(0x148) = 0.0f;
    F(0x14c) = 0.0f;
    F(0x150) = 0.0f;
    F(0x154) = 0.0f;
    F(0x158) = 0.0f;
    F(0x15c) = 0.0f;
    F(0x160) = 0.0f;
    F(0x164) = 0.0f;
    F(0x168) = 0.0f;
    F(0x16c) = 0.0f;
    F(0x170) = 0.0f;
    F(0x174) = 0.0f;
    F(0x178) = 0.0f;
    F(0x17c) = 0.0f;
    F(0x180) = 0.0f;
    F(0x184) = 0.0f;
    F(0x188) = 0.0f;
    F(0x18c) = 0.0f;
    F(0x190) = 0.0f;
    F(0x194) = 0.0f;
    F(0x198) = 0.0f;
    F(0x19c) = 0.0f;
    F(0x1a0) = 0.0f;
    F(0x1a4) = 0.0f;

    *(uint32*)(b + 0x274) = 0;
    F(0x27c) = -10.0f;
    F(0x280) = 2.0f;
    F(0x278) = 0.0f;
    F(0x284) = 0.0f;  F(0x288) = 0.0f;  F(0x28c) = 0.0f;  F(0x290) = 1.0f;

    if (*(void**)(b + 0x294)) {
        void* p = *(void**)(b + 0x294);
        *(uint32*)(b + 0x294) = 0;
        ((creature_instance_data_s009c_4a30*)p)->Release();
    }

    *(uint32*)(b + 0x2b0) = 0;
    *(uint32*)(b + 0x2b8) = 0;
    *(uint32*)(b + 0x2bc) = 0;
    *(uint32*)(b + 0x2b4) = 0xc;
    *(uint32*)(b + 0x2a8) = 0;
    *(uint32*)(b + 0x2ac) = 0xffffffffu;
    *(uint8*)(b + 0x260) = 1;  *(uint8*)(b + 0x261) = 0;
    *(uint8*)(b + 0x262) = 1;  *(uint8*)(b + 0x263) = 0;
    F(0x26c) = 0.0f;  F(0x264) = 0.0f;  F(0x268) = 0.0f;
    ((sub_2f8*)(b + 0x2f8))->FUN_009e3f70(6, 4);

    *(uint32*)(b + 0x1640) = 0;
    F(0x1650) = 0.0f; F(0x1654) = 0.0f; F(0x1658) = 0.0f; F(0x165c) = 1.0f;
    *(uint8*)(b + 0x168c) = 1;  *(uint8*)(b + 0x168d) = 1;
    *(uint8*)(b + 0x168e) = 1;  F(0x1690) = 0.0f;

    // mWiggles.clear()
    {
        vec2c* v = (vec2c*)(b + 0x1694);
        Elem2c* be = v->mpBegin;
        Elem2c* en = v->mpEnd;
        FUN_009b4a20(en, en, be);
        v->mpEnd += (en - be);
    }
    *(uint8*)(b + 0x1704) = 0;  *(uint8*)(b + 0x176c) = 0;
    *(uint8*)(b + 0x1794) = 1;  F(0x1798) = 0.0f;
    *(uint8*)(b + 0x179c) = 0;  *(uint8*)(b + 0x1680) = 1;
    *(uint32*)(b + 0x1684) = 0;
    *(uint32*)(b + 0x2d0) = 0xffffffffu;
    *(uint8*)(b + 0x2d4) = 1;  *(uint8*)(b + 0x2d5) = 0;
    *(uint32*)(b + 0x2dc) = 0;  *(uint32*)(b + 0x2d8) = 0;
    *(uint8*)(b + 0x2e0) = 1;
    *(uint32*)(b + 0x1ac) = 0;
    ((ik_vec*)(b + 0x24c))->resize(0);

    F(0x238) = 0.0f; F(0x23c) = 0.0f;
    F(0x240) = 0.0f; F(0x244) = 1.0f;
    F(0x248) = 1.0f;
    FUN_011e073e(b + 0x1f8, 0xaa, 0x40);
    FUN_011e073e(b + 0x1b8, 0, 0x40);
}
}  // namespace nSPCreatureAnim

// @ 0x009c52a0
namespace nSPCreatureAnim {
bool InitCreatureInstance(creature_static_data_s009c_4a30* c, creature_instance_data_s009c_4a30* inst, float a, float fb, float p5, float p6, float p7, float p8, float p9, int arg10)
{
    char* b = (char*)inst;
    unsigned count = (unsigned)((*(char**)((char*)c + 0x388) - *(char**)((char*)c + 0x384)) / 0x468);
    if (count == 0)
        return false;

    inst->Clear(false);

    creature_static_data_s009c_4a30* old = *(creature_static_data_s009c_4a30**)b;
    if (c != old) {
        if (c)
            ++*(int*)((char*)c + 0x348);
        *(creature_static_data_s009c_4a30**)b = c;
        if (old)
            old->Release();
    }
    *(uint8*)(b + 0xc) = 1;
    *(uint8*)((char*)c + 0x34c) = 0;

    *(float*)(b + 0x30) = a;
    *(float*)(b + 0x34) = fb;
    *(float*)(b + 0x38) = p5;
    *(float*)(b + 0x18) = a;
    *(float*)(b + 0x1c) = fb;
    *(float*)(b + 0x20) = p5;
    *(float*)(b + 0x24) = a;
    *(float*)(b + 0x28) = fb;
    *(float*)(b + 0x2c) = p5;
    *(float*)(b + 0x60) = p7;
    *(float*)(b + 0x64) = p8;
    *(float*)(b + 0x68) = p9;
    *(float*)(b + 0x5c) = p6;
    *(float*)(b + 0x3c) = p6;
    *(float*)(b + 0x40) = p7;
    *(float*)(b + 0x44) = p8;
    *(float*)(b + 0x48) = p9;
    *(float*)(b + 0x4c) = p6;
    *(float*)(b + 0x50) = p7;
    *(float*)(b + 0x54) = p8;
    *(float*)(b + 0x58) = p9;
    *(float*)(b + 0x1644) = a;
    *(float*)(b + 0x1648) = fb;
    *(float*)(b + 0x164c) = p5;
    *(float*)(b + 0x1650) = p6;
    *(float*)(b + 0x1654) = p7;
    *(float*)(b + 0x1658) = p8;
    *(float*)(b + 0x165c) = p9;
    *(float*)(b + 0x6c) = 1.0f;
    *(float*)(b + 0x70) = 1.0f;

    ((body_vec*)(b + 0x2e4))->FUN_009c3040((int)count);
    *(uint32*)(b + 8) = *(uint32*)(b + 0x2e4);
    *(float*)(b + 0x1660) = 0.0f; *(float*)(b + 0x1664) = 0.0f;
    *(float*)(b + 0x1668) = 0.0f; *(float*)(b + 0x166c) = 0.0f;
    *(float*)(b + 0x1670) = 0.0f; *(float*)(b + 0x1674) = 0.0f;
    *(float*)(b + 0x1678) = 0.0f; *(float*)(b + 0x167c) = 0.0f;
    FUN_009db1d0(b + 0x15b8);
    *(uint8*)(b + 0x270) = 1;

    // Per-body instance initialisation.
    for (unsigned i = 0; i < count; ++i) {
        char* e = *(char**)(b + 0x2e4) + i * 0x2bc;      // body instance record
        char* bs = *(char**)((char*)c + 0x384) + i * 0x468;
        *(uint32*)(e + 8) = 0;
        *(uint32*)(e + 0xc) = 0;
        for (int k = 0; k < 20; ++k)
            *(float*)(e + 0x58 + k * 4) = 0.0f;
        *(uint32*)(e + 0xa0) = 0;
        *(uint32*)(e + 0x48) = 0; *(uint32*)(e + 0x4c) = 0;
        *(uint32*)(e + 0x50) = 0;
        *(uint8*)(e + 0x54) = 0; *(uint8*)(e + 0x55) = 0;
        *(uint8*)(e + 0x2a0) = 0; *(uint8*)(e + 0x38) = 0;
        *(uint32*)(e + 0x144) = 0;
        *(void**)(e + 0) = bs;
        *(void**)(e + 4) = inst;
        *(uint32*)(e + 8) = 0;
        *(uint32*)(e + 0xc) = 0;
        *(float*)(e + 0x1c) = *(float*)(bs + 0x118);
        *(float*)(e + 0x20) = *(float*)(bs + 0x11c);
        *(float*)(e + 0x24) = *(float*)(bs + 0x120);
        *(float*)(e + 0x28) = *(float*)(bs + 0x124);
        float sc = *(float*)(b + 0x70);
        *(float*)(e + 0x10) = *(float*)(bs + 0x10c) * sc;
        *(float*)(e + 0x14) = *(float*)(bs + 0x110) * sc;
        *(float*)(e + 0x18) = *(float*)(bs + 0x114) * sc;
        *(uint8*)(e + 0x38) = 0;
        *(float*)(e + 0x3c) = *(float*)(e + 0x10);
        *(float*)(e + 0x40) = *(float*)(e + 0x14);
        *(float*)(e + 0x44) = *(float*)(e + 0x18);
        *(uint32*)(e + 0x144) = 0;
        *(float*)(e + 0x148) = 0.0f; *(float*)(e + 0x14c) = 0.0f;
        *(float*)(e + 0x150) = 0.0f; *(float*)(e + 0x154) = 1.0f;
        *(float*)(e + 0x158) = 0.0f; *(float*)(e + 0x15c) = 0.0f;
        *(float*)(e + 0x160) = 0.0f;
    }

    FUN_009bd340(inst);
    *(uint32*)(b + 0x1688) = arg10;
    *(uint8*)(b + 0x263) = 0;
    *(uint32*)(b + 0x1640) = 0;
    FUN_009db270(b + 0x15b8);

    if (*(int*)(*(char**)((char*)c + 0x3c8)) == 0)
        inst->BuildBodyList();
    else
        inst->FUN_009b6360();

    if (*(uint32*)(b + 0x1640) > 0) {
        void* gt = (void*)(b + 0x15b8);
        if (*(int*)(*(char**)((char*)c + 0x3c8)) == 0)
            FUN_009db6d0(gt, 2.0f, inst);
        else
            FUN_009db4d0(gt, 2.0f);
        FUN_009d34a0(gt);
        FUN_009da640(gt, inst);
        FUN_009d3170(gt);
    }

    inst->InitWiggles();
    return true;
}
}  // namespace nSPCreatureAnim

// @ 0x009c56c0
creature_instance_data::creature_instance_data()
{
    char tmp;
    *(int*)this = 0;
    *(float*)((char*)this + 0x20) = 0.0f;
    *(float*)((char*)this + 0x1c) = 0.0f;
    *(float*)((char*)this + 0x18) = 0.0f;
    *(float*)((char*)this + 0x2c) = 0.0f;
    *(float*)((char*)this + 0x28) = 0.0f;
    *(float*)((char*)this + 0x24) = 0.0f;
    *(float*)((char*)this + 0x38) = 0.0f;
    *(float*)((char*)this + 0x34) = 0.0f;
    *(float*)((char*)this + 0x30) = 0.0f;
    *(float*)((char*)this + 0x44) = 0.0f;
    *(float*)((char*)this + 0x40) = 0.0f;
    *(float*)((char*)this + 0x3c) = 0.0f;
    *(float*)((char*)this + 0x48) = 1.0f;
    *(float*)((char*)this + 0x54) = 0.0f;
    *(float*)((char*)this + 0x50) = 0.0f;
    *(float*)((char*)this + 0x4c) = 0.0f;
    *(float*)((char*)this + 0x58) = 1.0f;
    *(float*)((char*)this + 0x64) = 0.0f;
    *(float*)((char*)this + 0x60) = 0.0f;
    *(float*)((char*)this + 0x5c) = 0.0f;
    *(float*)((char*)this + 0x68) = 1.0f;
    *(float*)((char*)this + 0x6c) = 1.0f;
    *(float*)((char*)this + 0x70) = 1.0f;
    *(float*)((char*)this + 0x7c) = 0.0f;
    *(float*)((char*)this + 0x78) = 0.0f;
    *(float*)((char*)this + 0x74) = 0.0f;
    *(float*)((char*)this + 0x88) = 0.0f;
    *(float*)((char*)this + 0x84) = 0.0f;
    *(float*)((char*)this + 0x80) = 0.0f;
    *(float*)((char*)this + 0x94) = 0.0f;
    *(float*)((char*)this + 0x90) = 0.0f;
    *(float*)((char*)this + 0x8c) = 0.0f;
    *(float*)((char*)this + 0xa0) = 0.0f;
    *(float*)((char*)this + 0x9c) = 0.0f;
    *(float*)((char*)this + 0x98) = 0.0f;
    *(float*)((char*)this + 0xac) = 0.0f;
    *(float*)((char*)this + 0xa8) = 0.0f;
    *(float*)((char*)this + 0xa4) = 0.0f;
    *(float*)((char*)this + 0xb8) = 0.0f;
    *(float*)((char*)this + 0xb4) = 0.0f;
    *(float*)((char*)this + 0xb0) = 0.0f;
    *(float*)((char*)this + 0xc4) = 0.0f;
    *(float*)((char*)this + 0xc0) = 0.0f;
    *(float*)((char*)this + 0xbc) = 0.0f;
    *(float*)((char*)this + 0xd0) = 0.0f;
    *(float*)((char*)this + 0xcc) = 0.0f;
    *(float*)((char*)this + 0xc8) = 0.0f;
    *(float*)((char*)this + 0xd4) = 1.0f;
    *(float*)((char*)this + 0xe4) = 0.0f;
    *(float*)((char*)this + 0xe0) = 0.0f;
    *(float*)((char*)this + 0xdc) = 0.0f;
    *(float*)((char*)this + 0xf0) = 0.0f;
    *(float*)((char*)this + 0xec) = 0.0f;
    *(float*)((char*)this + 0xe8) = 0.0f;
    *(float*)((char*)this + 0xfc) = 0.0f;
    *(float*)((char*)this + 0xf8) = 0.0f;
    *(float*)((char*)this + 0xf4) = 0.0f;
    *(float*)((char*)this + 0x108) = 0.0f;
    *(float*)((char*)this + 0x104) = 0.0f;
    *(float*)((char*)this + 0x100) = 0.0f;
    *(float*)((char*)this + 0x118) = 0.0f;
    *(float*)((char*)this + 0x11c) = 0.0f;
    *(float*)((char*)this + 0x120) = 0.0f;
    *(float*)((char*)this + 0x124) = 0.0f;
    *(float*)((char*)this + 0x128) = 0.0f;
    *(float*)((char*)this + 0x12c) = 0.0f;
    *(float*)((char*)this + 0x130) = 0.0f;
    *(float*)((char*)this + 0x134) = 0.0f;
    *(float*)((char*)this + 0x138) = 0.0f;
    *(float*)((char*)this + 0x13c) = 0.0f;
    *(float*)((char*)this + 0x140) = 0.0f;
    *(float*)((char*)this + 0x144) = 0.0f;
    *(float*)((char*)this + 0x148) = 0.0f;
    *(float*)((char*)this + 0x14c) = 0.0f;
    *(float*)((char*)this + 0x150) = 0.0f;
    *(float*)((char*)this + 0x154) = 0.0f;
    *(float*)((char*)this + 0x158) = 0.0f;
    *(float*)((char*)this + 0x15c) = 0.0f;
    *(float*)((char*)this + 0x160) = 0.0f;
    *(float*)((char*)this + 0x164) = 0.0f;
    *(float*)((char*)this + 0x168) = 0.0f;
    *(float*)((char*)this + 0x16c) = 0.0f;
    *(float*)((char*)this + 0x170) = 0.0f;
    *(float*)((char*)this + 0x174) = 0.0f;
    *(float*)((char*)this + 0x178) = 0.0f;
    *(float*)((char*)this + 0x17c) = 0.0f;
    *(float*)((char*)this + 0x180) = 0.0f;
    *(float*)((char*)this + 0x184) = 0.0f;
    *(float*)((char*)this + 0x188) = 0.0f;
    *(float*)((char*)this + 0x18c) = 0.0f;
    *(float*)((char*)this + 0x190) = 0.0f;
    *(float*)((char*)this + 0x194) = 0.0f;
    *(float*)((char*)this + 0x198) = 0.0f;
    *(float*)((char*)this + 0x19c) = 0.0f;
    *(float*)((char*)this + 0x1a0) = 0.0f;
    *(float*)((char*)this + 0x1a4) = 0.0f;
    *(float*)((char*)this + 0x240) = 0.0f;
    *(float*)((char*)this + 0x23c) = 0.0f;
    *(float*)((char*)this + 0x238) = 0.0f;
    *(float*)((char*)this + 0x244) = 1.0f;
    *(float*)((char*)this + 0x268) = 0.0f;
    *(float*)((char*)this + 0x264) = 0.0f;
    *(float*)((char*)this + 0x280) = 0.0f;
    *(float*)((char*)this + 0x27c) = 0.0f;
    *(float*)((char*)this + 0x278) = 0.0f;
    *(int*)((char*)this + 0x24c) = 0;
    *(int*)((char*)this + 0x250) = 0;
    *(int*)((char*)this + 0x254) = 0;
    *(float*)((char*)this + 0x28c) = 0.0f;
    *(float*)((char*)this + 0x288) = 0.0f;
    *(float*)((char*)this + 0x284) = 0.0f;
    *(float*)((char*)this + 0x290) = 1.0f;
    *(int*)((char*)this + 0x294) = 0;
    *(int*)((char*)this + 0x298) = 0;
    *(int*)((char*)this + 0x29c) = 0;
    *(int*)((char*)this + 0x2a0) = 0;
    *(int*)((char*)this + 0x2a4) = 0;
    *(float*)((char*)this + 0x2cc) = 0.0f;
    *(float*)((char*)this + 0x2c8) = 0.0f;
    *(float*)((char*)this + 0x2c4) = 0.0f;
    *(int*)((char*)this + 0x2e4) = 0;
    *(int*)((char*)this + 0x2e8) = 0;
    *(int*)((char*)this + 0x2ec) = 0;
    ((XBodySub*)((char*)this + 0x2f8))->Construct();
    *(float*)((char*)this + 0x160c) = 0.0f;
    *(float*)((char*)this + 0x1608) = 0.0f;
    *(float*)((char*)this + 0x1604) = 0.0f;
    *(float*)((char*)this + 0x1618) = 0.0f;
    *(float*)((char*)this + 0x1614) = 0.0f;
    *(float*)((char*)this + 0x1610) = 0.0f;
    *(float*)((char*)this + 0x164c) = 0.0f;
    *(float*)((char*)this + 0x1648) = 0.0f;
    *(float*)((char*)this + 0x1644) = 0.0f;
    *(int*)((char*)this + 0x15c8) = 0;
    *(int*)((char*)this + 0x15cc) = 0;
    *(int*)((char*)this + 0x15d0) = 0;
    *(float*)((char*)this + 0x1658) = 0.0f;
    *(float*)((char*)this + 0x1654) = 0.0f;
    *(float*)((char*)this + 0x1650) = 0.0f;
    *(float*)((char*)this + 0x165c) = 1.0f;
    *(int*)((char*)this + 0x15dc) = 0;
    *(int*)((char*)this + 0x15e0) = 0;
    *(int*)((char*)this + 0x15e4) = 0;
    *(float*)((char*)this + 0x1668) = 0.0f;
    *(float*)((char*)this + 0x1664) = 0.0f;
    *(float*)((char*)this + 0x1660) = 0.0f;
    *(int*)((char*)this + 0x15f0) = 0;
    *(int*)((char*)this + 0x15f4) = 0;
    *(int*)((char*)this + 0x15f8) = 0;
    *(float*)((char*)this + 0x1678) = 0.0f;
    *(float*)((char*)this + 0x1674) = 0.0f;
    *(float*)((char*)this + 0x1670) = 0.0f;
    *(float*)((char*)this + 0x16bc) = 0.0f;
    *(float*)((char*)this + 0x16b8) = 0.0f;
    *(float*)((char*)this + 0x16b4) = 0.0f;
    *(float*)((char*)this + 0x16e8) = 0.0f;
    *(float*)((char*)this + 0x16e4) = 0.0f;
    *(float*)((char*)this + 0x16e0) = 0.0f;
    *(float*)((char*)this + 0x16f4) = 0.0f;
    *(float*)((char*)this + 0x16f0) = 0.0f;
    *(float*)((char*)this + 0x16ec) = 0.0f;
    *(float*)((char*)this + 0x16f8) = 1.0f;
    *(float*)((char*)this + 0x1710) = 0.0f;
    *(float*)((char*)this + 0x170c) = 0.0f;
    *(float*)((char*)this + 0x1708) = 0.0f;
    *(float*)((char*)this + 0x171c) = 0.0f;
    *(float*)((char*)this + 0x1718) = 0.0f;
    *(float*)((char*)this + 0x1714) = 0.0f;
    *(float*)((char*)this + 0x1728) = 0.0f;
    *(float*)((char*)this + 0x1724) = 0.0f;
    *(float*)((char*)this + 0x1720) = 0.0f;
    *(float*)((char*)this + 0x1750) = 0.0f;
    *(float*)((char*)this + 0x174c) = 0.0f;
    *(float*)((char*)this + 0x1748) = 0.0f;
    *(float*)((char*)this + 0x175c) = 0.0f;
    *(float*)((char*)this + 0x1758) = 0.0f;
    *(float*)((char*)this + 0x1754) = 0.0f;
    *(float*)((char*)this + 0x1760) = 1.0f;
    *(float*)((char*)this + 0x1778) = 0.0f;
    *(float*)((char*)this + 0x1774) = 0.0f;
    *(float*)((char*)this + 0x1770) = 0.0f;
    *(float*)((char*)this + 0x1784) = 0.0f;
    *(float*)((char*)this + 0x1780) = 0.0f;
    *(float*)((char*)this + 0x177c) = 0.0f;
    *(int*)((char*)this + 0x1694) = 0;
    *(int*)((char*)this + 0x1698) = 0;
    *(int*)((char*)this + 0x169c) = 0;
    *(float*)((char*)this + 0x1790) = 0.0f;
    *(float*)((char*)this + 0x178c) = 0.0f;
    *(float*)((char*)this + 0x1788) = 0.0f;
    ((XGaitSub*)((char*)this + 0x17a0))->Construct(&tmp, &tmp);
    flags14 = 0;
    Clear(true);
}
