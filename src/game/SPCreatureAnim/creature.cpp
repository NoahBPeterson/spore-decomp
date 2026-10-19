// src/game/SPCreatureAnim/creature.cpp -- migrated from slice(s) s009c4a30, s009c32c0, s009c1f60, s009bfc20, s009bd340, s009bc580, s009bb910, s009ba4c0, s009b77a0, s009b6b10, s009b5ce0, s009b3180 by tools/migrate/rewrite.py
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
int  __fastcall FUN_009e5b40(int a, int dummy, void* b, int c);
int  __fastcall FUN_009e18c0(int a, int dummy, void* b, int c, int d);     // LoadGaitFile
int  __fastcall FUN_009dbe10(int a, int dummy, int b, int c);
int  __fastcall FUN_009e4350(int a, int dummy, int b);
int  __fastcall FUN_009e3790(int a, int dummy);
int  __fastcall FUN_009e4450(int a, int dummy, int b, int c, int d);
int  __fastcall FUN_009d24c0(int a, int dummy, int b, int c, int d, int e);
float __fastcall FUN_009dc7a0(int a, int dummy);
int  FUN_009d0c80(void);
int  FUN_009dfc40(void);
int  FUN_009d1050(void);
// ---- items of slice s009b77a0 end

// ---- items of slice s009ba4c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace checkerlib {
struct vector_3_s009b_a4c0 {
    float x, y, z;
    vector_3_s009b_a4c0& operator=(const vector_3_s009b_a4c0& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
}
namespace checkerlib {
struct vector_4_s009b_a4c0 { float x, y, z, w; };
}
namespace checkerlib {
vector_3_s009b_a4c0* QuaternionVectorTransform(vector_3_s009b_a4c0* out, const vector_4_s009b_a4c0* q, const vector_3_s009b_a4c0* v);  // 0x0099c1a0
}
namespace checkerlib {
__forceinline vector_4_s009b_a4c0 QuaternionProduct(const vector_4_s009b_a4c0& a, const vector_4_s009b_a4c0& b)
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
__forceinline vector_3_s009b_a4c0 QuaternionVectorTransformInverse(const vector_4_s009b_a4c0& q, const vector_3_s009b_a4c0& v)
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
    uint32_t pad_128[(0x1f8 - 0x128) / 4];
    unsigned long bidx;                  // +0x1f8 (body index in the creature)
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
void GoalStateInit(creature_instance_data_s009b_a4c0* c, goal_state* st, int flag);       // 0x009ba7d0 (cdecl)
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
static __forceinline void MarkBodyGoal(creature_body_instance_data_s009b_a4c0* body)
{
    unsigned long bit = body->static_data->bidx * 2;
    body->creature->body_goal_bits[bit >> 3] |= (uint8_t)(1 << (bit & 7));
}
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
struct vector_3_s009b_c580 {
    float x, y, z;
    vector_3_s009b_c580& operator=(const vector_3_s009b_c580& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
}
namespace checkerlib {
struct vector_4_s009b_c580 {
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
    uint32_t                     pad_03c[(0x280 - 0x3c) / 4];
    checkerlib::vector_3_s009b_c580                     blend_pos;     // +0x280
    checkerlib::vector_4_s009b_c580                     blend_rot;     // +0x28c
    uint32_t                     pad_29c[(0x2bc - 0x29c) / 4];
};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009b_c580 {
    uint32_t pad_000[0x70 / 4];
    float    requested_scale;             // +0x070
    uint32_t pad_074[(0x2e4 - 0x74) / 4];
    creature_body_instance_data_s009b_c580* mpBegin; // +0x2e4  (Bodies vector)
    creature_body_instance_data_s009b_c580* mpEnd;   // +0x2e8
};
}
// ---- items of slice s009bc580 end

// ---- items of slice s009bd340 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_IKFloorWeightRate;   // 0x01550d88 (20.0)
namespace checkerlib {
struct vector_3_s009b_d340 {
    float x, y, z;
    vector_3_s009b_d340& operator=(const vector_3_s009b_d340& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
}
namespace checkerlib {
struct vector_4_s009b_d340 {
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
    uint32_t      pad_154[(0x344 - 0x154) / 4];
    checkerlib::vector_3_s009b_d340      ik_joint_r__SCALABLE;         // +0x344 (name guessed)
    checkerlib::vector_3_s009b_d340      parent_local_joint_r__SCALABLE;  // +0x350 (name guessed)
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
    uint32_t                     pad_02c[(0x38 - 0x2c) / 4];
    bool                         floored;       // +0x038
    uint8_t                      pad_039[3];
    uint32_t                     pad_03c[(0x29c - 0x3c) / 4];
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
    uint32_t pad_004[(0x18 - 0x4) / 4];
    checkerlib::vector_3_s009b_d340 position;                          // +0x018
    uint32_t pad_024[(0x3c - 0x24) / 4];
    checkerlib::vector_4_s009b_d340 orientation;                       // +0x03c
    uint32_t pad_04c[(0x70 - 0x4c) / 4];
    float    requested_scale;                   // +0x070
    uint32_t pad_074[(0xe8 - 0x74) / 4];
    checkerlib::vector_3_s009b_d340 ground_pos;                        // +0x0e8
    checkerlib::vector_3_s009b_d340 ground_normal;                     // +0x0f4
    uint32_t pad_100[(0x2e4 - 0x100) / 4];
    eastl::vector_s009b_d340<creature_body_instance_data_s009b_d340, eastl::sp_vector_allocator_s009b_d340> Bodies;  // +0x2e4
    uint32_t pad_2f4[(0x168c - 0x2f4) / 4];
    uint8_t  pad_168c;
    bool     floor_enabled;                     // +0x168d
};
}
// ---- items of slice s009bd340 end

// ---- items of slice s009bfc20 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace checkerlib {
struct vector_3_s009b_fc20 {
    float x, y, z;
    vector_3_s009b_fc20() {}
    vector_3_s009b_fc20(const vector_3_s009b_fc20& o) : x(o.x), y(o.y), z(o.z) {}
    vector_3_s009b_fc20& operator=(const vector_3_s009b_fc20& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
}
namespace checkerlib {
struct vector_4_s009b_fc20 { float x, y, z, w; };
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
};
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

    float GetGroundHeight(const checkerlib::vector_3_s009b_fc20* pos, checkerlib::vector_3_s009b_fc20* normal);   // 0x009b6220
    checkerlib::vector_3_s009b_fc20* GetGroundUp(checkerlib::vector_3_s009b_fc20* out, const checkerlib::vector_3_s009b_fc20* pos);      // 0x009b62c0
};
}
namespace nSPCreatureAnim {
struct creature_body_instance_data_s009b_fc20 {
    creature_body_static_data_s009b_fc20* static_data;  // +0x000
    uint32_t pad_004[(0x7c - 0x4) / 4];
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
    int   pad_1c[7];                     // +0x1c .. 0x38
    uint8 flag;                          // +0x38
    uint8 pad_39[3];
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
struct bone_xform {                      // pair<matrix_3x3, vector_3>, size 0x30
    matrix_3x3_s009c_1f60 first;
    vector_3_s009c_1f60   second;
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
    vec3p<wiggle_static_data> mWiggles;  // +0x3b4
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
    uint8   pad_004;
    uint8   flag4;                       // +0x04
    uint8   flag5;                       // +0x05
    uint8   pad_006[2];
    vector_3_s009c_1f60 zero;                       // +0x08
    vector_3_s009c_1f60 pos;                        // +0x14
    vector_3_s009c_1f60 pos_copy;                   // +0x20
};
}
namespace nSPCreatureAnim {
struct wiggle_instance_vec : vec3p<wiggle_instance_data> {
    void resize(unsigned n);             // 0x009c25f0
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
    uint8      pad_1700[0x172c - 0x1700];
    wiggle_static_data desc_b;           // +0x172c
    uint8      pad_1768[8];

    void BuildBodyList();
    void InitWiggles();  // 0x009c2c20 (nSPCreatureAnim::creature_instance_data::InitWiggles)
};
}
namespace nSPCreatureAnim {
int  FUN_009d7d10(creature_instance_data_s009c_1f60* c, float* pos, float* rot);   // 0x009d7d10
}
namespace nSPCreatureAnim {
void* FUN_00a09f50();                                                   // 0x00a09f50
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
struct phasegroup_vec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32 mAllocator;
    void DoDestroyValues(void* first, void* last);          // 0x009c3240
};
}
namespace nSPCreatureAnim {
struct dynamics_walking_s009c_4a30 {
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
struct creature_instance_data_s009c_4a30 {
    uint8 blob[0x17b0];

    void Clear(bool flag);                                  // 0x009c4d40
    int  Release();                                         // 0x009c4cc0
    ~creature_instance_data_s009c_4a30();                              // 0x009c4bf0
    void InitWiggles();                                     // 0x009c2c20
    void BuildBodyList();                                   // 0x009c20e0
    void FUN_009c4d10();                                    // 0x009c4d10
    void FUN_009cb4f0();                                    // 0x009cb4f0
    void FUN_009b6360();                                    // 0x009b6360
};
}
// ---- items of slice s009c4a30 end

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
        local_1a4 = FUN_009e5b40(param_1 + 0x2f8, 0, local_1a0, param_4);
    } else {
        // ComposeGaitFileName(param_1, local_1a0, local_1a8, param_3)
        char cVar1 = FUN_009b3850(param_1, 0, local_1a0, local_1a8, param_3);
        if (cVar1 != 0) {
            int iVar5 = param_4;
            int uVar3 = FUN_009ce410(param_4);
            local_1a4 = FUN_009e18c0(param_1 + 0x2f8, 0, local_1a0, uVar3, iVar5);
            if (local_1a4 != 0) goto LAB_009b79ca;
        }
        cVar1 = FUN_009b3850(param_1, 0, local_1a0, local_1a8, 0);
        if (cVar1 == 0) return 0;
        int iVar5 = param_4;
        int uVar3 = FUN_009ce410(param_4);
        local_1a4 = FUN_009e18c0(param_1 + 0x2f8, 0, local_1a0, uVar3, iVar5);
    }
    if (local_1a4 == 0) return 0;
LAB_009b79ca:
    {
        int* base = (int*)(param_1);
        iVar4 = *(int*)((int)base + param_2 * 4 + 0x2fc);
        if (param_4 == iVar4) *(int*)((int)base + param_2 * 4 + 0x2fc) = iVar4 + 1;
        if (param_4 == 0) *(int*)((int)base + (param_4 + param_2 * 4) * 4 + 0x374) = 0x3f800000;
        else *(int*)((int)base + (param_4 + param_2 * 4) * 4 + 0x374) = 0;
        int iVar5 = param_4;
        int uVar3 = FUN_009ce410(param_4);
        iVar4 = FUN_009dbe10(local_1a4, 0, uVar3, iVar5);
        if (iVar4 != 0) {
            *(int*)(param_1 + 0x434) = param_2 + 1;
            uVar3 = FUN_009d0c80();
            uVar3 = FUN_009e4350(*piVar2, 0, uVar3);
            FUN_009e3790(uVar3, 0);
            FUN_009dfc40();
            float fVar5 = FUN_009dc7a0(param_1 + 0x264, 0);
            float fVar6 = 1.0f;
            if (1e-06f < *(float*)(param_1 + 0x70)) fVar6 = 1.0f / *(float*)(param_1 + 0x70);
            FUN_009e4450(param_1 + 0x2f8, 0, (int)(fVar6 * fVar5), param_4, 0);
            int a = *(int*)(param_1 + param_2 * 4 + 0x2fc);
            int b = param_1 + param_2 * 0x10 + 0x374;
            int c = param_1 + param_2 * 0x2d0 + 0x3d4;
            int d = (int)((char*)base + param_2 * 0x2d0 + 0x438);
            int e = param_1 + 0x434;
            FUN_009d24c0(a, 0, b, c, d, e);
            FUN_009d1050();
        }
    }
    return 1;
}

// @ 0x009b7b10
char __fastcall FUN_009b7b10(int param_1, int dummy, int param_2, int param_3)
{
    (void)dummy;
    int* piVar2 = GetPoliticalID(param_1 + 0x15b8);
    int iVar1 = (piVar2[1] - *piVar2) / 0x104;
    int iVar4 = 0;
    char uVar3 = 1;
    if (0 < iVar1) {
        do {
            uVar3 = FUN_009b78c0(param_1, 0, iVar4, param_2, param_3);
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
    float local_2c, local_28, local_24, local_20, local_1c, local_18, local_14, local_10, local_c, local_8, local_4;
    float local_2cbase[8];
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
        float* pfVar4 = (float*)FUN_0099c310(&local_20, (float*)(param_1 + 0x3c), pfVar3);
        *pfVar3 = *pfVar4;
        *(float*)(param_1 + 0x1664) = pfVar4[1];
        *(float*)(param_1 + 0x1668) = pfVar4[2];
        *(int*)(param_1 + 0x1668) = 0;
        *pfVar3 = *pfVar3 * fVar6;
        *(float*)(param_1 + 0x1664) = *(float*)(param_1 + 0x1664) * fVar6;
        float g0 = *(float*)(param_1 + 0x3c);
        float g1 = *(float*)(param_1 + 0x40);
        float g2 = *(float*)(param_1 + 0x44);
        float h0 = -*(float*)(param_1 + 0x1650);
        float h1 = -*(float*)(param_1 + 0x1654);
        float h2 = -*(float*)(param_1 + 0x1658);
        float g3 = *(float*)(param_1 + 0x48);
        local_20 = ((g0 * *(float*)(param_1 + 0x165c) + g3 * h0) - g2 * h1) + g1 * h2;
        local_1c = ((g1 * *(float*)(param_1 + 0x165c) + g3 * h1) + g2 * h0) - g0 * h2;
        local_18 = ((g2 * *(float*)(param_1 + 0x165c) - g1 * h0) + g0 * h1) + g3 * h2;
        local_14 = ((g3 * *(float*)(param_1 + 0x165c) - g0 * h0) - g1 * h1) - g2 * h2;
        local_2c = 0.0f;
        local_28 = 0.0f;
        local_24 = 0.0f;
        FUN_009b4ba0(&local_10, &local_20, &local_2c);
        local_4 = local_4 * param_2;
        float fVar10 = 1.0f, fVar5b = 0.0f, fVar6b = 0.0f;
        local_2c = local_10 * local_4;
        local_28 = local_c * local_4;
        local_24 = local_8 * local_4;
        local_1c = 0.0f;
        if ((*(char**)(param_1 + 0x1688) != 0) && (**(char**)(param_1 + 0x1688) != '\0')) {
            fVar5b = *(float*)(param_1 + 0x18);
            if ((fVar5b * fVar5b + *(float*)(param_1 + 0x1c) * *(float*)(param_1 + 0x1c)) +
                *(float*)(param_1 + 0x20) * *(float*)(param_1 + 0x20) <= 0.01f) {
                fVar5b = 0.0f;
            } else {
                float* pfVar3b = (float*)FUN_009a49d0(&local_20, (float*)(param_1 + 0x18), 0);
                fVar6b = *pfVar3b;
                fVar5b = pfVar3b[1];
                fVar10 = pfVar3b[2];
            }
        }
        fVar6 = (fVar10 * local_24 + fVar5b * local_28) + fVar6b * local_2c;
    } else {
        local_2c = *(float*)(param_1 + 0x264) * fVar6;
        local_28 = *(float*)(param_1 + 0x268) * fVar6;
        local_24 = 0.0f;
        int* puVar2 = (int*)FUN_0099c310(&local_20, (void*)(param_1 + 0x3c), &local_2c);
        *(int*)(param_1 + 0x1660) = *puVar2;
        float fVar10 = 1.0f, fVar6b = 0.0f, fVar5b = 0.0f;
        *(int*)(param_1 + 0x1664) = puVar2[1];
        *(int*)(param_1 + 0x1668) = puVar2[2];
        *(int*)(param_1 + 0x1668) = 0;
        float fVar1 = *(float*)(param_1 + 0x18);
        if (((*(char**)(param_1 + 0x1688) != 0) && (**(char**)(param_1 + 0x1688) != '\0')) &&
            (0.01f < (fVar1 * fVar1 + *(float*)(param_1 + 0x1c) * *(float*)(param_1 + 0x1c)) +
                      *(float*)(param_1 + 0x20) * *(float*)(param_1 + 0x20))) {
            float* pfVar3b = (float*)FUN_009a49d0(&local_20, (float*)(param_1 + 0x18), 0);
            fVar6b = *pfVar3b;
            fVar5b = pfVar3b[1];
            fVar10 = pfVar3b[2];
        }
        fVar6 = (fVar5b + fVar6b) * 0.0f + *(float*)(param_1 + 0x26c) * fVar10;
    }
    *(float*)(param_1 + 0x166c) = fVar6;
    float fVar5c = -6.2831855f;
    if ((fVar6 <= -6.2831855f) || (fVar5c = 6.2831855f, 6.2831855f < fVar6)) {
        fVar6 = fVar5c;
    }
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
        lrot = checkerlib::QuaternionProduct(parent->orientation, def->rot);
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
    checkerlib::vector_3_s009b_a4c0 g = checkerlib::QuaternionVectorTransformInverse(orientation, d);
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
    float size = sqrtf(ex * ex + ey * ey + ez * ez) * 1.3f;

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

// @ 0x009c4cc0
long nSPCreatureAnim::creature_instance_data::Release()
{
    char* b = (char*)this;
    int n = *(int*)(b + 0x14) - 1;
    if (n < 1)
        n = 0;
    *(int*)(b + 0x14) = n;
    if (n < 1) {
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
