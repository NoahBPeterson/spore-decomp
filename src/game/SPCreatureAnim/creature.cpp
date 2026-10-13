// src/game/SPCreatureAnim/creature.cpp -- migrated from slice(s) s009c4a30, s009c1f60, s009b77a0, s009b6b10, s009b3180 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/creature.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPCreatureAnim/creature_instance_data.h"
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

// ---- items of slice s009c4a30 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace nSPCreatureAnim {
struct creature_instance_data_s009c_4a30;
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







// @ 0x009b3bc0
namespace nSPCreatureAnim {
void __cdecl FUN_009b3bc0(int obj)
{
  float* p = (float*)(obj + 0x118);
  for (int i = 0; i < 9; i++)
    p[i] = 0.0f;
}
}  // namespace nSPCreatureAnim







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
