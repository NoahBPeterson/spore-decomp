// src/game/SPGonzago/_at_00af0000.cpp -- migrated from slice(s) s00afef10, s00afdfe0, s00afd1c0, s00afbaf0, s00afab70, s00af9aa0, s00af7c60, s00af6bf0, s00af6400, s00af5b40, s00af4da0, s00af3e00, s00af1a90, s00af1910, s00af08e0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00af0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void __cdecl FreeMem(void* p);                                                   // 0xf47380
extern "C" void* __cdecl Instance();                                                        // 0xbc30b0
extern "C" void* __cdecl PropertyManager();                                                 // 0x67de30
extern "C" extern const float g_zero;           // 0x01485378
extern "C" extern const float g_one;            // 0x01485720
extern "C" extern const float g_two;            // 0x01470f1c
extern "C" extern const float g_secPerDay;      // 0x0145c194 (86400.0f)
extern "C" extern const float g_invDay;         // 0x0145c198 (1.1574074e-05f)
extern "C" extern const float g_msPerSec;       // 0x013ec5b4 (1000.0f)
extern "C" extern const float g_minScale;       // 0x013ebc4c (60.0f)
extern "C" extern const float g_minScale2;      // 0x0145c19c (60000.0f)
extern "C" extern const float g_eps;            // 0x0145c190 (1.5258789e-05f)
extern "C" extern const char g_allocFile[];     // 0x013ebb38 (EASTL/allocator.h)
extern "C" extern const char g_allocName[];     // 0x013f09b4 ("Simulator")
#include <math.h>
#include <string.h>
#include <intrin.h>
#include "cSPTransform.h"
#include "SP/cITerrainSphere.h"
#include "SP/cPlanetModel.h"
#include "cSPMatrix3.h"
#include "cSPVector3.h"
#include <float.h>
#include "SP/cGameNounManager.h"
#include "SP/cSpatialObject.h"
#include "SP/cActionCircle.h"
#include "cSPQuaternion.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cGameData.h"
#include "SP/cInteractionAgent.h"
#include <xmmintrin.h>
#include "SP/cFruit.h"
#include "SP/cSPEditorAnimatedCreatureData.h"
#include "SP/cTreeData.h"
#include "SP/cVarListSerializer.h"
#pragma intrinsic(sqrt)

// ---- items of slice s00af08e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned long long u64;
struct Node;
struct Node
{
    Node* left;    // +0x00
    Node* right;   // +0x04
    Node* parent;  // +0x08
    u8 color;      // +0x0c
    u8 pad[3];
    int key;       // +0x10
    int t0;        // +0x14
    int t1;        // +0x18
    u32 v;         // +0x1c (float value, copied verbatim)
};
struct HashNode
{
    u32 key;        // +0x00
    u32 unk04;      // +0x04
    u32 unk08;      // +0x08
    u32 unk0c;      // +0x0c
    Node* tree;     // +0x10
    u32 unk14;      // +0x14
    u32 unk18;      // +0x18
    u32 unk1c;      // +0x1c
    HashNode* next; // +0x20
};
struct HIter
{
    void* a;
    void* b;
};
struct InnerNode
{
    void* val;       // +0x00
    InnerNode* next; // +0x04
};
struct RBTree
{
    u32 unk00;      // +0x00
    void* base;     // +0x04 (self)
    void* end;      // +0x08 (self)
    Node* root;     // +0x0c
    u8 flag;        // +0x10
    u8 pad[3];
    u32 size;       // +0x14
    u32 unk18;      // +0x18

    void FindBounds(HIter* out, const int* key);
    Node* Clone(Node* src, void* parent);
};
struct HashTable
{
    u32 unk00;           // +0x00
    HashNode** buckets;  // +0x04
    u32 bucketCount;     // +0x08
    u32 size;            // +0x0c
    float f10;           // +0x10
    float f14;           // +0x14
    u32 unk18;           // +0x18
    u32 pad1c;           // +0x1c (padding: object is 0x20 bytes)

    void __thiscall FreeChains(HashNode** buckets, u32 count);
    void* __thiscall GetOrCreate(const u32* key);
};
struct Block { u32 q[8]; };
struct Vec3 { float x, y, z; };
struct World
{
    RBTree tree;         // +0x00 .. +0x1b
    u32 gap1c;           // +0x1c
    u32 f20;             // +0x20
    u32 f24;             // +0x24
    Vec3 p;              // +0x28
    u32 d34, d38, d3c;   // +0x34
    u8 flag40;           // +0x40
    u8 pad41[7];
    Vec3 q;              // +0x48
    float f54;           // +0x54
    u32 pad58[0x1d];     // +0x58 .. +0xcb
    Vec3 r6;             // +0xcc
    Vec3 r5;             // +0xd8
    Vec3 r7;             // +0xe4
};
struct Pair { u32 key; World w; };
struct LayoutMgr
{
    HashTable t1;   // +0x00
    HashTable t2;   // +0x20
    u8 mbInit;      // +0x40

    void ClearBucketChains();
    void BuildTables();
    bool LookupA(void* entity, int key, float* out);
    bool LookupB(void* entity, int key, float* out);
    bool LookupC(void* entity, int key, float* out);
};
struct ListNode { ListNode* next; ListNode* prev; u8 str[0x10]; };  // 0x18
struct ListHead { ListNode* next; ListNode* prev; };               // 0x08
struct TimerOwner
{
    u32 vtable;      // +0x00 = 0x0145c1bc
    u32 pad04;
    ListHead head;   // +0x08
    u32 pad10;
    u32 pad14;
    u8 timer[0x28];  // +0x18 SP::cGonzagoTimer

    void Dtor();
    void Add(const void* wstr);
    TimerOwner* Ctor();
    TimerOwner* Delete(u32 flags);
};
struct XComp
{
    u32 __thiscall Get();           // 0xc04590
    u32 __thiscall GetPosition();   // 0xc6acc0
    u32 __thiscall GetAlt();        // 0xc23290
};
struct XTimeOfDay
{
    float __thiscall GetSeconds(u32 pos);   // 0xbc2b30
};
struct XSpeciesMgr
{
    void* __thiscall GetArchetype();        // 0x4e0050
};
struct XGonzago
{
    void __thiscall Dtor();
    void __thiscall Ctor();
};
struct XSPTimer
{
    void __thiscall Restart();
    void __thiscall Start();
};
struct XStopwatch
{
    u32 lo;              // +0x00
    u32 hi;              // +0x04
    u32 pad08;           // +0x08
    u32 pad0c;           // +0x0c
    u32 units;           // +0x10
    void __thiscall SetUnits(int units);
};
struct XList
{
    void __thiscall DoClear();
};
struct XWString
{
    void __thiscall Ctor(const void* src);
};
struct XClear
{
    void __thiscall ClearValue(void* p);    // 0x9a9600
};
struct XHash
{
    void __thiscall HashFind(HIter* out, const u32* key);              // 0xafb0d0
    void __thiscall HashInsert(HIter* result, const void* value, u8 unique);
};
struct XTreeCopy
{
    void __thiscall CopyFrom(const void* src);              // 0xaf0d40
};
struct XTreeNuke
{
    void __thiscall Nuke(void* root);                       // 0x9a9600
};
struct XHashIns
{
    void __thiscall InsertVal(HIter* out, const void* val, u8 unique);  // 0xaf0e40
};
extern "C" void* __cdecl EAAllocate(u32 size, const char* name, int a, int b, const char* file, int line);  // 0xf473a0
extern "C" void __cdecl FreeMem(void* p);                                                   // 0xf47380
extern "C" Node* __cdecl RBTreeInc(Node* node);                                             // 0x921580
extern "C" void __cdecl RBTreeInsert(Node* node, void* parent, void* base, int side);       // 0x9216a0
extern "C" void* __cdecl Instance();                                                        // 0xbc30b0
extern "C" u32 __stdcall GetSetting9(u32 a, u32 b);                                         // 0x401090
extern "C" void* __cdecl PropertyManager();                                                 // 0x67de30
extern "C" bool __cdecl FindProperty(void* rec, u32 key, int* count, int* data);            // 0x6a0990
extern "C" extern u32 g_singleton_167ad74;      // 0x0167ad74
extern "C" extern XStopwatch g_stopwatch;       // 0x0167adf0
extern "C" extern u32 g_default34;              // 0x0167ae24
extern "C" extern u32 g_default38;              // 0x0167ae28
extern "C" extern u32 g_default3c;              // 0x0167ae2c
extern "C" extern const float g_zero;           // 0x01485378
extern "C" extern const float g_one;            // 0x01485720
extern "C" extern const float g_two;            // 0x01470f1c
extern "C" extern const float g_secPerDay;      // 0x0145c194 (86400.0f)
extern "C" extern const float g_invDay;         // 0x0145c198 (1.1574074e-05f)
extern "C" extern const float g_msPerSec;       // 0x013ec5b4 (1000.0f)
extern "C" extern const float g_minScale;       // 0x013ebc4c (60.0f)
extern "C" extern const float g_minScale2;      // 0x0145c19c (60000.0f)
extern "C" extern const float g_eps;            // 0x0145c190 (1.5258789e-05f)
extern "C" extern const char g_allocFile[];     // 0x013ebb38 (EASTL/allocator.h)
extern "C" extern const char g_allocName[];     // 0x013f09b4 ("Simulator")
union LI { struct { u32 lo; int hi; } s; u64 q; };
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LI* li);
typedef u32 (__thiscall* VCall1)(void* self, void* arg);
typedef u32 (__thiscall* VCall0)(void* self);
typedef u8  (__thiscall* VFlag)(void* self);
bool __cdecl Lookup(void* table, u32 hash, int t, int key, float* out);
struct PropEntry { u32 key; int idx; };
struct SrcEntry { u32 id; HashTable* tbl; };
struct VecU32 { u32* begin; u32* end; u32* cap; };
// ---- items of slice s00af08e0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* __cdecl EAAllocate(u32 size, const char* name, int a, int b, const char* file, int line);  // 0xf473a0
extern "C" Node* __cdecl RBTreeInc(Node* node);                                             // 0x921580
extern "C" void __cdecl RBTreeInsert(Node* node, void* parent, void* base, int side);       // 0x9216a0
extern "C" u32 __stdcall GetSetting9(u32 a, u32 b);                                         // 0x401090
extern "C" bool __cdecl FindProperty(void* rec, u32 key, int* count, int* data);            // 0x6a0990
extern "C" extern u32 g_singleton_167ad74;      // 0x0167ad74
extern "C" extern XStopwatch g_stopwatch;       // 0x0167adf0
extern "C" extern u32 g_default34;              // 0x0167ae24
extern "C" extern u32 g_default38;              // 0x0167ae28
extern "C" extern u32 g_default3c;              // 0x0167ae2c
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LI* li);

// ---- items of slice s00af1910 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPTransform_s00af_1910 {
    u32 mElems[0x38 / 4];                           // +0x00 transform payload
    cSPTransform_s00af_1910* Assign(const cSPTransform_s00af_1910& src);  // 0x00537DC0
};
struct cSweepResult {
    // The +0x00..+0x1F head is copied as one 32-byte aggregate.
    struct Head {
        u32   mNounID;        // +0x00
        void* mpObject;       // +0x04
        float mSpeedFactor;   // +0x08
        int   mbHeadOn;       // +0x0c
        u32   mReserved[4];   // +0x10
    } mHead;
    u32          mHitKind;         // +0x20
    u32          mHitSlot;         // +0x24
    Vec3         mHitCenter;       // +0x28
    Vec3         mHitNormal;       // +0x34
    u8           mbFlag;           // +0x40
    u8           mPad41[3];
    float        mDist;            // +0x44
    Vec3         mHitPos;          // +0x48
    float        mRadius;          // +0x54
    Vec3         mBoxMax;          // +0x58
    Vec3         mBoxMin;          // +0x64
    cSPTransform_s00af_1910 mTransform;       // +0x70 (0x38 bytes)
    Vec3         mMeshPoint;       // +0xa8
    u32          mVertCount;       // +0xb4
    void*        mpVerts;          // +0xb8
    u32          mSurfaceId;       // +0xbc
    u32          mSurfaceFlags;    // +0xc0
    u32          mExtraC4;         // +0xc4
    float        mExtraRadius;     // +0xc8
    Vec3         mExtraCC;         // +0xcc
    Vec3         mExtraD8;         // +0xd8
    Vec3         mExtraE4;         // +0xe4

    cSweepResult& operator=(const cSweepResult& src);   // 0x00af1910
};
// ---- items of slice s00af1910 end

// ---- items of slice s00af1a90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float* normalized_safe(float* out, const float* v);                    // 0x449c20
extern char   FUN_004232c0(const float* a, const float* b);                   // 0x4232c0 Vector3Equal
extern void   FUN_00436ce0(float* out, const float* v);                       // 0x436ce0 Vector3_Normalize
extern float* FUN_00699800(float* out, const float* a, float r,
                           const float* b, const float* c);                   // 0x699800
extern float       DAT_0167ae24, DAT_0167ae28, DAT_0167ae2c;
extern const float DAT_0167ae78, DAT_0167ae7c, DAT_0167ae80;
struct cSPVector3_s00af_1a90;
struct cSPBoundingBox_s00af_1a90 {
    void GetCorners(cSPVector3_s00af_1a90* out) const;                                  // 0x00466320
};
#define OF(off) (*(float*)((char*)p + (off)))
#define OI(off) (*(int*)((char*)p + (off)))
#define OB(off) (*(unsigned char*)((char*)p + (off)))
#define PROC_SAMPLE(px, py, pz)                                                  \
    {                                                                            \
        float _x = (px), _y = (py), _z = (pz);                                   \
        fVar20 = (fVar13 * _y + fVar16 * _x) + fVar19 * _z;                      \
        fVar21 = (fVar15 * _y + fVar10 * _x) + fVar11 * _z;                      \
        float _r = (fVar12 * _y + fVar17 * _x) + fVar9 * _z;                     \
        fVar14 = (fVar20 * local_e0 + fVar21 * local_dc) + _r * local_d8;        \
        fVar20 = fVar20 - fVar14 * local_e0;                                     \
        fVar21 = fVar21 - local_dc * fVar14;                                     \
        if (0.0f < -(((local_fc - local_cc) * (fVar21 - local_c8) -              \
                       (fVar20 - local_cc) * (local_f8 - local_c8)) * param_4)) {\
            local_fc = fVar20;                                                   \
            local_f8 = fVar21;                                                   \
            local_f4 = _r - local_d8 * fVar14;                                   \
        }                                                                        \
    }
#define WTEST1(x, y)                                                             \
    (0.0f < -(((y - fVar13) * (local_f0 - fVar19) -                              \
               (local_ec - fVar13) * (x - fVar19)) * param_4))
#define WTEST2(x, y)                                                             \
    (0.0f < -(((y - fVar13) * (local_fc - fVar19) -                              \
               (x - fVar19) * (local_f8 - fVar13)) * param_4))
// ---- items of slice s00af1a90 end

// ---- items of slice s00af3e00 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct HeightImg { char pad[0x10]; uint16_t* data; };               // +0x10
struct ColorImg { char pad[8]; int dim; char pad2[4]; uint32_t* data; };  // +8 dim, +0x10 data
struct TerrainMap {
    char pad0[8];
    HeightImg* height;   // +8
    ColorImg* color;     // +0xc
    char pad10[0x34 - 0x10];
    float radius;        // +0x34
    float heightScale;   // +0x38
    char pad3c[0x4c - 0x3c];
    float minAlpha;      // +0x4c
};
struct cITerrainSphere {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual TerrainMap* GetMap();  // +0xc
};
struct cPlanetModel {
    char pad[0x24];
    cITerrainSphere* mpISphere;  // +0x24
    char pad28[0xf0 - 0x28];
    bool mbF0;                   // +0xf0
    float __thiscall GetWaterHeight();                         // 0xb7e390
    float __thiscall GetRadiusAt(const Vec3* p);               // 0xb7ef70
    Vec3* __thiscall ToSurface(Vec3* out, const Vec3* in);     // 0xb81630
};
cPlanetModel* SP_PlanetModel();  // 0xb3d350
void __cdecl FUN_00af1610(void* a, cPlanetModel* pm, Vec3* p0, Vec3* p1, Vec3* p2, Vec3* p3, Vec3* p4, float f);
void __cdecl FUN_00af1570(void* a, cPlanetModel* pm, Vec3* p0, Vec3* p1, float f, int z0, int z1);
static __forceinline int CubeIndex(float x, float y, float z, int dim, int dimSq, float half) {
  float ax = fabsf(x), ay = fabsf(y), az = fabsf(z);
  int u, v, face;
  if (!(az < ax) && !(az < ay)) {
    u = (int)((x / z + 1.0f) * half);
    v = (int)((y / az + 1.0f) * half);
    face = (z >= 0.0f) ? 0 : 1;
  } else if (!(ay < ax)) {
    u = (int)((z / y + 1.0f) * half);
    v = (int)((x / ay + 1.0f) * half);
    face = (y >= 0.0f) ? 4 : 5;
  } else {
    u = (int)((y / x + 1.0f) * half);
    v = (int)((z / ax + 1.0f) * half);
    face = (x >= 0.0f) ? 2 : 3;
  }
  if (u == dim) u--;
  if (v == dim) v--;
  return face * dimSq + u + v * dim;
}
struct cRayQueryBase {
  char pad[0xf0];
  float mValue;  // +0xf0
  Vec3 mPoint;   // +0xf4
  void __thiscall AssignBase(const cRayQueryBase& src);  // 0xaf1910
  cRayQueryBase& __thiscall Assign(const cRayQueryBase& src);
};
struct ProbeRay {
  Vec3 dir;
  Vec3 start;
  float t;
};
// ---- items of slice s00af3e00 end

// ---- items of slice s00af4da0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short u16;
typedef float          f32;
extern "C" u8    __cdecl FUN_006989d0(const f32* a, const f32* b, const void* box, f32* t); // 0x006989d0 SP::SegmentBoxIntersect
extern "C" u8    __cdecl FUN_0069a240(const f32* a, const f32* b, const f32* poly, int n, f32* outA, f32* outB); // 0x0069a240 SP::ClipSegmentToPolygon
extern "C" f32   __cdecl FUN_00698b30(const f32* q, const f32* a, const f32* b); // 0x00698b30 SP::QuaternionSlerp
extern "C" f32   __cdecl FUN_00698e00(const f32* out, const f32* p, const f32* a, const f32* b); // 0x00698e00 SP::DistancePointSegment
extern "C" f32 DAT_0145c3e0;   // +FLT_MAX
extern "C" f32 DAT_013f51ac;   // -FLT_MAX
extern "C" f32 DAT_01485720;   // _HK_REAL_ONE (1.0f)
extern "C" f32 DAT_0167ae24;
extern "C" f32 DAT_0167ae28;
extern "C" f32 DAT_0167ae2c;
extern "C" f32 DAT_0167ae78_s00af_4da0;
extern "C" f32 DAT_0167ae7c_s00af_4da0;
extern "C" f32 DAT_0167ae80_s00af_4da0;
extern "C" f32 DAT_0167ae54[];
struct Vec3_s00af_4da0 { f32 x, y, z; };
extern "C" Vec3_s00af_4da0 DAT_0167ae24_v;
struct Mat33 {
    f32 m[9];
    void* __thiscall Assign(const f32* src);   // 0x0041cb40 Matrix33Template<float,0> ctor
};
struct cSPTransform_s00af_4da0 {
    u16   flags0;      // 0x70
    u16   flags2;      // 0x72
    Vec3_s00af_4da0  origin;      // 0x74
    f32   scale;       // 0x80
    Mat33 basis;       // 0x84
    void* __thiscall Assign(const void* src);       // 0x00537dc0 cSPTransform::operator=
    void  __thiscall BackTransformPoint(f32* p);    // 0x004ff6d0
};
struct Orientation { u32 w[8]; };
struct SPShape {
    Orientation orient;    // 0x00
    int         kind;      // 0x20
    int         type;      // 0x24  (1 = span, 2 = polygon)
    Vec3_s00af_4da0        pos;       // 0x28
    Vec3_s00af_4da0        worldPos;  // 0x34
    u8          flag40;    // 0x40
    char        pad41[3];  // 0x41
    f32         radiusA;   // 0x44
    Vec3_s00af_4da0        halfExt;   // 0x48
    f32         extra54;   // 0x54
    Vec3_s00af_4da0        lo;        // 0x58  (running AABB min)
    Vec3_s00af_4da0        hi;        // 0x64  (running AABB max)
    cSPTransform_s00af_4da0 xf;       // 0x70
    Vec3_s00af_4da0        normal;    // 0xa8
    int         fieldB4;   // 0xb4
    int         fieldB8;   // 0xb8
    Vec3_s00af_4da0        contact;   // 0xbc
    f32         depth;     // 0xc8
    SPShape* __thiscall InitDefault();   // 0x00af4da0
};
struct SPBox {
    u16   flags;       // 0x00
    u16   pad02;       // 0x02
    Vec3_s00af_4da0  center;      // 0x04
    f32   scale;       // 0x10
    Mat33 basis;       // 0x14
};
// ---- items of slice s00af4da0 end

// ---- items of slice s00af5b40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPTransform_s00af_5b40 {
    void BackTransformPoint(Vec3* p);  // 0x004ff6d0 (thiscall, ret 4)
    void TransformPoint(Vec3* p);      // 0x0044d4f0 (thiscall, ret 4)
};
bool Vector3_NotEqual(const Vec3* a, const Vec3* b);                    // 0x0041dd30 (cdecl)
Vec3* normalized_safe(Vec3* out, const Vec3* v);                        // 0x00449c20 (cdecl)
float SegmentDistance(const Vec3* p, const Vec3* a, const Vec3* b);     // 0x00698b30 (cdecl, float in st0)
void ClosestOnSegment(Vec3* out, const Vec3* p, const Vec3* a, const Vec3* b);  // 0x00698e00 (cdecl)
bool PointInsidePolygon(const Vec3* verts, int count, const Vec3* p);  // 0x0069a050 (cdecl)
struct Shape {
    uint32_t pad0[9];        // 0x00
    int type;                // +0x24
    Vec3 center;             // +0x28
    uint32_t pad1[(0x48 - 0x34) / 4];
    Vec3 innerPt;            // +0x48
    float radius;            // +0x54
    Vec3 boxMin;             // +0x58
    Vec3 boxMax;             // +0x64
    cSPTransform_s00af_5b40 xform;      // +0x70 (0x38 bytes)
    uint32_t padX[(0xa8 - 0x70 - 1) / 4];
    Vec3 pathRef;            // +0xa8
    int vertCount;           // +0xb4
    Vec3* verts;             // +0xb8
    uint32_t pad2[(0xc8 - 0xbc) / 4];
    float extraRadius;       // +0xc8
    uint32_t pad3[(0xe4 - 0xcc) / 4];
    Vec3 outerPt;            // +0xe4
};
static inline float Sq(float v) { return v * v; }
struct cSPMatrix3_s00af_5b40 {
    float m[9];                                        // +0x00
    cSPMatrix3_s00af_5b40& operator=(const cSPMatrix3_s00af_5b40& other) {
        Assign(other);
        return *this;
    }
    void Assign(const cSPMatrix3_s00af_5b40& other);              // 0x0041cb40
};
struct ShapeCopy {
    uint32_t m_head[8];                                // +0x00
    uint32_t m_field20;                                // +0x20
    uint32_t m_field24;                                // +0x24
    float m_field28;                                   // +0x28
    float m_field2c;                                   // +0x2c
    float m_field30;                                   // +0x30
    float m_field34;                                   // +0x34
    float m_field38;                                   // +0x38
    float m_field3c;                                   // +0x3c
    uint8_t m_field40;                                 // +0x40
    uint8_t m_pad41[3];                                // +0x41
    float m_field44;                                   // +0x44
    float m_inner0;                                    // +0x48
    float m_inner1;                                    // +0x4c
    float m_inner2;                                    // +0x50
    float m_radius;                                    // +0x54
    float m_boxMin0;                                   // +0x58
    float m_boxMin1;                                   // +0x5c
    float m_boxMin2;                                   // +0x60
    float m_boxMax0;                                   // +0x64
    float m_boxMax1;                                   // +0x68
    float m_boxMax2;                                   // +0x6c
    uint16_t m_field70;                                // +0x70
    uint16_t m_field72;                                // +0x72
    float m_field74;                                   // +0x74
    float m_field78;                                   // +0x78
    float m_field7c;                                   // +0x7c
    float m_field80;                                   // +0x80
    cSPMatrix3_s00af_5b40 m_matrix84;                             // +0x84
    float m_fielda8;                                   // +0xa8
    float m_fieldac;                                   // +0xac
    float m_fieldb0;                                   // +0xb0
    uint32_t m_fieldb4;                                // +0xb4
    uint32_t m_fieldb8;                                // +0xb8
    float m_fieldbc;                                   // +0xbc
    float m_fieldc0;                                   // +0xc0
    float m_fieldc4;                                   // +0xc4
    float m_fieldc8;                                   // +0xc8
    float m_fieldcc;                                   // +0xcc
    float m_fieldd0;                                   // +0xd0
    float m_fieldd4;                                   // +0xd4
    float m_fieldd8;                                   // +0xd8
    float m_fielddc;                                   // +0xdc
    float m_fielde0;                                   // +0xe0
    float m_fielde4;                                   // +0xe4
    float m_fielde8;                                   // +0xe8
    float m_fieldec;                                   // +0xec
    ShapeCopy& operator=(const ShapeCopy& other);
};
// ---- items of slice s00af5b40 end

// ---- items of slice s00af6400 begin (TODO(rewrite): local stubs, replace by canonical classes)
__declspec(align(16)) struct Hit {
    uint32_t p00[8];     // +0x00
    int      id;         // +0x20
    int      type;       // +0x24 shape type: 0 sphere, 1 box, 2 polyline, 3 shell
    Vec3     center;     // +0x28
    uint32_t p34[(0x40 - 0x34) / 4];
    int      flag;       // +0x40
    uint32_t p44[(0x54 - 0x44) / 4];
    float    radius;     // +0x54
    uint32_t box[(0x70 - 0x58) / 4];     // +0x58
    uint32_t xform[(0xa8 - 0x70) / 4];   // +0x70
    uint32_t meshPt[(0xb4 - 0xa8) / 4];  // +0xa8
    uint32_t vertCount;  // +0xb4
    Vec3*    verts;      // +0xb8
    uint32_t pBC[(0xc8 - 0xbc) / 4];
    float    extraRadius;// +0xc8
    uint32_t pCC[(0xf0 - 0xcc) / 4];
    float    w;          // +0xf0
    Vec3     pos;        // +0xf4
    uint32_t pFC;

    Hit();                       // 0x00af4da0
    Hit(const Hit& src);         // 0x00af6250
    void Copy(const Hit* src);   // 0x00af1910
};
typedef float (*CastFn)(void* ctx, const Vec3* origin, const Vec3* dir, float maxDist, Hit* hit);
bool  Steer(const Vec3* pos, const Vec3* end, Vec3* outPt, float side, float margin, Hit* hit, int extra);  // 0x00af1a90 (cdecl)
char  ProbeHit(Hit* hit, const Vec3* a, const Vec3* b, int push, char* moved, float margin);                // 0x00af5b40 (cdecl)
bool  SweepSphere(Hit* hit, int id, const Vec3* pos, const Vec3* center, const Vec3* dir, float* len,
                  float margin, float radius, int flag, Hit* hit2);                                         // 0x00af17f0 (cdecl)
bool  SweepBox(Hit* hit, int id, const Vec3* pos, const Vec3* center, const Vec3* dir, float* len,
               float margin, const void* xform, const void* box, int flag, Hit* hit2);                       // 0x00af5060 (cdecl)
bool  SweepMesh(Hit* hit, int id, const Vec3* pos, const Vec3* center, const Vec3* end, const Vec3* dir,
                float* len, float margin, const void* xform, const void* meshPt, float meshRadius,
                const Vec3* verts, uint32_t nVerts, float radius, int flag, Hit* hit2);                     // 0x00af5400 (cdecl)
// ---- items of slice s00af6400 end

// ---- items of slice s00af6bf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Hit_s00af_6bf0 {
    char  p0[0x20];
    int   id;
    char  p1[0x34 - 0x24];
    Vec3  normal;
    bool  flag;
    char  p2[3];
    float dist;
    char  p3[0xf0 - 0x48];
    float w;
    Vec3  pos;

    Hit_s00af_6bf0();                          // 0x00af4da0 (default-initialises the record)
    void CopyBase(const Hit_s00af_6bf0* src);  // 0x00af1910 (copies bytes 0..0xef)
    void CopyAll(const Hit_s00af_6bf0* src);   // 0x00af3e00 (CopyBase + w/pos)
};
namespace SP {
void* PlanetModel();                                  // 0x00b3d350 returns the global model
}
namespace SP {
float* normalized_safe(float* out, const float* v);   // 0x00449c20
}
extern Vec3 gInvalidVec;                              // 0x0167ae24 sentinel vector
typedef float (*CastFn_s00af_6bf0)(void* ctx, const float* origin, const float* dir, float maxDist, Hit_s00af_6bf0* hit);
char ProbeHit(Hit_s00af_6bf0* hit, const float* a, const float* b, bool flag, char* outFlag, float p3);  // 0x00af5b40
int SweepSide(void* ctx, float p3, CastFn_s00af_6bf0 cast, const float* a, const float* b, float side,
              Hit_s00af_6bf0* hit, Hit_s00af_6bf0* outArr, int count, Hit_s00af_6bf0* outBase, int idx, float* outDist, int extra);  // 0x00af6400
static inline bool IsInvalid(const Vec3& v)
{
    return v.x == gInvalidVec.x && v.y == gInvalidVec.y && v.z == gInvalidVec.z;
}
static inline void StoreHitPoint(Hit_s00af_6bf0* dst, const Hit_s00af_6bf0* src)
{
    dst->CopyBase(src);
    dst->w = src->w;
    dst->pos.x = src->pos.x;
    dst->pos.y = src->pos.y;
    dst->pos.z = src->pos.z;
}
// ---- items of slice s00af6bf0 end

// ---- items of slice s00af7c60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kZero;     // 0x01485378 (0.0f, loaded from memory by the original)
extern const float kDefaultPointX;     // 0x016e42d0
extern const float kDefaultPointY;     // 0x016e42d4
extern const float kDefaultPointZ;     // 0x016e42d8
extern const float kDefaultPointW;     // 0x016e42dc
struct Vector3 { float x, y, z; };
extern Vector3 gInvalidVec_s00af_7c60;   // 0x0167ae24 sentinel vector
struct Transform {
    uint16_t mFlags;        // +0x00
    uint16_t mChangeCount;  // +0x02
    Vector3  mOffset;       // +0x04
    float    mScale;        // +0x10
    uint32_t pad14[(0x38 - 0x14) / 4];

    Transform(const Transform& other);                 // 0x0040CE80
    void SetScale(float scale) { mScale = scale; mChangeCount++; }
    void SetOffset(const Vector3& offset) { mOffset = offset; mFlags |= 4; mChangeCount++; }
};
Vector3* normalized_safe(Vector3* out, const Vector3* v);   // 0x00449c20 (cdecl)
struct IProps;
bool GetBoolProperty(IProps* props, uint32_t id, bool* out);  // 0x00407190 (cdecl)
void  operator delete[](void* p);                            // 0x00F47380
struct cSweepResult_s00af_7c60 {
    uint32_t mNounID;         // +0x00
    void*    mpObject;        // +0x04
    float    mSpeedFactor;    // +0x08
    int      mbHeadOn;        // +0x0c
    uint32_t pad10[4];        // +0x10
    void*    mpHitObject;     // +0x20
    uint32_t pad24;           // +0x24
    Vector3  mHitCenter;      // +0x28
    Vector3  mHitNormal;      // +0x34
    bool     mbFlag;          // +0x40
    uint8_t  pad41[3];
    float    mDist;           // +0x44
    Vector3  mHitPos;         // +0x48
    float    mRadius;         // +0x54
    uint32_t pad58[(0xF0 - 0x58) / 4];

    cSweepResult_s00af_7c60();                                // 0x00af4da0
    void Copy(const cSweepResult_s00af_7c60* src);            // 0x00af1910
};
struct cCollisionMesh {
    uint32_t pad00[0x3c / 4];
    float    mRadius;             // +0x3c
    Vector3  mCenter;             // +0x40
    Vector3* mpTrisBegin;         // +0x4c
    Vector3* mpTrisEnd;           // +0x50
    uint32_t GetNumVertices() const { return (uint32_t)(mpTrisEnd - mpTrisBegin); }
};
struct cOwnerObj { uint8_t pad[0x90]; IProps* mpProps; };   // +0x90 property list
struct cSpatialObject {
    uint8_t   pad00[0x34];
    uint32_t  mFlags;       // +0x34
    Vector3   mCenter;      // +0x38
    float     mRadius;      // +0x44
    uint8_t   pad48[0x6c - 0x48];
    void*     mpMeshOwner;  // +0x6c
    cOwnerObj* mpOwner;     // +0x70
    uint8_t   pad74[0x88 - 0x74];
    int       mType;        // +0x88

    Transform* GetTransform();   // 0x00b73e70
};
struct ObjectList {
    cSpatialObject** mpBegin;
    cSpatialObject** mpEnd;
    cSpatialObject** mpCapacity;
    uint32_t         mAllocatorName;
    cSpatialObject** mpPoolBegin;
    int              mOverflow;
    cSpatialObject*  mBuffer[64];

    ObjectList()
    {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 64;
        mOverflow = 0;
    }
    ~ObjectList()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    cSpatialObject*& operator[](int i) { return mpBegin[i]; }
};
struct cObjectManager {
    // objects whose bounds touch the capsule start..end
    int GetObjectsInCapsule(const Vector3* start, const Vector3* end, float radius, ObjectList* out, int flags); // 0x00b7a4a0
    cCollisionMesh* GetCollisionMesh(cSpatialObject* obj);                                                       // 0x00b7c480
};
cObjectManager* ObjectManager();   // 0x00b3d3c0
bool RaySphere(const Vector3* origin, const Vector3* dirScaled, float lenSq, const Vector3* center,
               float radius, float* t);                                          // 0x00af16f0
bool SweepSphereVsMesh(cSweepResult_s00af_7c60* result, void* owner, const Vector3* pos, const Vector3* center,
                       Vector3* endPos, const Vector3* dir, float* dist, float scale,
                       Transform* xf, const Vector3* meshCenter, float meshRadius,
                       Vector3* tris, uint32_t numVerts, float radius, int flags,
                       cSweepResult_s00af_7c60* result2);                                    // 0x00af5400
struct __declspec(align(16)) Vector4 { float x, y, z, w; };
struct hkTransform_s00af_7c60 { uint32_t mData[0x40 / 4]; };
struct hkVector4_s00af_7c60 : Vector4 {
    void setTransformedInversePos(const hkTransform_s00af_7c60* xf, const Vector4* pos);   // 0x010813d0
};
class D961;   // entity tracked by a proxy (also an hkEntity)
struct cContactRecord {
    uint32_t  mType;        // +0x00  source type, or the query's hit flag
    uint32_t  pad04[3];     // +0x04
    Vector4   mPoint;       // +0x10  hit point / source point
    Vector4*  mpPoint;      // +0x20  point storage (query result array)
    uint32_t  pad24;        // +0x24
    void*     mpOwner;      // +0x28
    D961*     mpEntity;     // +0x2c
};
struct SweepInput {
    Vector4 m_vec00;        // +0x00
    float   mRadius;        // +0x10
    float   m_f14;          // +0x14
    uint32_t pad18[2];      // +0x18
};
struct cContactOwner {
    void** mpVtbl;                                 // +0x00
    uint32_t pad04[3];                             // +0x04
    void* GetEntity(uint32_t id);                  // vtable slot 3
};
struct cProxySource {
    uint32_t mField0;       // +0x00
    uint32_t mField4;       // +0x04
    uint32_t mCount8;       // +0x08
};
struct cEntityHolder {
    uint32_t    pad00[4];   // +0x00
    hkTransform_s00af_7c60 mTransform; // +0x10
};
class D961 {
public:
    uint32_t  pad00[3];     // +0x00
    void*     mpField0c;    // +0x0c
    uint32_t  pad10[(0x58 - 0x10) / 4];
    cEntityHolder* mpHolder58;   // +0x58

    int* Find(int* out, int value);              // 0x00496140
    void AddEntityListener(void* listener);           // 0x01088c20
    void RemoveEntityListener(void* listener);        // 0x01088a20
};
void SurfaceHitQuery(const Vector4* pos, void* surface, cContactRecord* out);             // 0x00b665c0
void SurfaceRayQuery(const Vector4* from, void* surface, int kind, cContactRecord* out);  // 0x00b66ed0
void SurfaceSweepQuery(SweepInput* in, void* surface, void* shape, void* ctx, bool local,
                       cContactRecord* out, int zero);                                    // 0x00b669b0
Vector4* DirectionToPoint(Vector4* out, const Vector4* dir);                              // 0x00b65710
class cContactProxy {
public:
    void**    mpVtbl;         // +0x00
    uint32_t  pad04[3];       // +0x04
    Vector4   m_vec10;        // +0x10  current surface direction
    uint32_t  pad20[(0x48 - 0x20) / 4];
    uint8_t   m_b48;          // +0x48
    uint8_t   pad49[3];
    uint32_t  m_type4c;       // +0x4c
    Vector4   m_vec50;        // +0x50  closest surface point
    void*     m_listenerVtbl; // +0x60  embedded hkEntityListener
    uint32_t  pad64;
    D961*     mpEntity;       // +0x68
    hkVector4_s00af_7c60 m_vec70;        // +0x70  world position
    hkVector4_s00af_7c60 m_vec80;        // +0x80  local position
    uint32_t  pad90[(0x9c - 0x90) / 4];
    void*     mpCtx9c;        // +0x9c
    uint32_t  padA0[(0xa8 - 0xa0) / 4];
    float     m_fA8;          // +0xa8
    float     m_fAC;          // +0xac
    void*     mpB0;           // +0xb0
    void*     mpB4;           // +0xb4

    void  ReleaseSource(cProxySource* src);                              // 0x00af84f0
    void  UpdateClosestPoint();                                          // 0x00af8540
    void  SetEntity(void* owner, D961* entity, const Vector4* pos);       // 0x00af8840
    void  SetFromSource(cContactRecord* src);                            // 0x00af8920
    void  Update(bool useLocal, float extra);                            // 0x00af8a10
};
struct cGameDataTransform {
    void** mpVtbl;                             // +0x00
    const Vector3* GetPosition();              // vtable slot 0x2c/4
};
struct cGameDataObject {
    uint32_t pad00[0x34 / 4];
    cGameDataTransform mTransform;             // +0x34
    uint32_t pad38[(0x25c - 0x38) / 4];
    float    mRadius;                          // +0x25c
};
struct cNounGameData {
    uint32_t pad00[0x324 / 4];
    cGameDataObject* mpObject;                 // +0x324
};
struct cGameDataArray {
    uint32_t mCount;                           // +0x00
    void*    mpBegin;                          // +0x04
};
struct cGameNounManager {
    cGameDataArray* GetGameDataVector(void* f1, void* f2, void* f3, void* f4, void* f5);  // 0x00b21340
};
cGameNounManager* NounManager();                                            // 0x00b3d300
void* FindNounGameData(void* list, const Vector3* pos, int flag);           // 0x00ac9310
// ---- items of slice s00af7c60 end

// ---- items of slice s00af9aa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_fOne;          // 0x1485720 = 1.0f
extern float g_f200;          // 0x1477fbc = 200.0f
extern float g_fPiOver3;      // 0x1567344 = 1.0471976f
extern int   g_n16;           // 0x1567338 = 16
extern float g_fFLTMax;       // 0x145c45c = FLT_MAX
extern float g_fEps;          // 0x13ec4b8 = 1e-8f
extern float g_quatIdent[4];  // 0x156737c = {0,0,0,1}
extern float g_defFacing[4];  // 0x167af08
extern float g_defCenter[3];  // 0x167aec4
extern void* g_vftableA;      // 0x145c428
extern void* g_vftableB;      // 0x145c414
extern unsigned long g_hkThreadMemoryTls;   // 0x16e4174
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern void* SP_PlanetModel(void* out, const float* dir);              // 0xb3d350
namespace hkArrayUtil {
void _reserveMore(void* array, int elemSize);                  // 0x107f530
}
namespace hkArrayUtil {
void _reserveExactly(void* array, int count, int elemSize);    // 0x107f4a0
}
class hkThreadMemory {
 public:
  void deallocateChunk(void* p, int size, int align);          // 0x107db10
};
namespace EA {
class IRefCounted {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
namespace EA {
template <class T>
class AutoRefCount_s00af_9aa0 {
 public:
  T* mpObject;
  AutoRefCount_s00af_9aa0() : mpObject(0) {}
  AutoRefCount_s00af_9aa0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s00af_9aa0(const AutoRefCount_s00af_9aa0& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s00af_9aa0() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s00af_9aa0& operator=(T* p) {
    if (p != mpObject) {
      T* const old = mpObject;
      if (p) p->AddRef();
      mpObject = p;
      if (old) old->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace SP {
struct cSPVector3_s00af_9aa0 { float mX, mY, mZ; };
}
namespace SP {
struct cSPQuaternion_s00af_9aa0 { float x, y, z, w; };
}
namespace SP {
class cGameData_s00af_9aa0 : public EA::IRefCounted {};
}
namespace SP {
class cInteractionAgent_s00af_9aa0 : public EA::IRefCounted {};
}
namespace SP {
class cActionCircle_s00af_9aa0 {
 public:
  class tSlot { public:
    bool mOccupied;                                 // +0x0
    char _pad0[3];
    EA::AutoRefCount_s00af_9aa0<cGameData_s00af_9aa0> mpReservingNoun;    // +0x4
    unsigned int mReservingId;                      // +0x8
    cSPVector3_s00af_9aa0 mPos;                                // +0xc

    void Reserve(cGameData_s00af_9aa0* noun);                  // 0xafa030
    void ReserveId(unsigned int id);                // 0xafa070
    void Clear();                                   // 0xafa0a0
    tSlot* CopyConstruct(const tSlot* src);         // 0xafa110
    tSlot* Assign(const tSlot* src);                // 0xafa230
  };

  cSPVector3_s00af_9aa0 mFacing;                               // +0x0
  float mRadius;                                    // +0xc
  float mSlotRadius;                                // +0x10
  cSPVector3_s00af_9aa0 mCenter;                               // +0x14
  float mAltitude;                                  // +0x20
  int mPacking;                                     // +0x24
  bool mbRelative;                                  // +0x28
  char _pad28[3];
  cSPQuaternion_s00af_9aa0 mOrientation;                       // +0x2c
  struct SlotVec {                                  // eastl::sp_vector<Agent> at +0x3c
    EA::AutoRefCount_s00af_9aa0<cInteractionAgent_s00af_9aa0>* mpBegin;
    EA::AutoRefCount_s00af_9aa0<cInteractionAgent_s00af_9aa0>* mpEnd;
    EA::AutoRefCount_s00af_9aa0<cInteractionAgent_s00af_9aa0>* mpCapacity;
    int mAllocator[2];
  } mAgents;
  struct SlotVector {                               // eastl::sp_vector<tSlot> at +0x50
    tSlot* mpBegin;
    tSlot* mpEnd;
    tSlot* mpCapacity;
    int mAllocator[2];
  } mSlots;

  void SetAtCenter(const cSPVector3_s00af_9aa0* center, float radius, const cSPVector3_s00af_9aa0* facing, float altitude);  // 0xaf9cf0
  void SetRelative(const cSPVector3_s00af_9aa0* center, const cSPQuaternion_s00af_9aa0* orient, float radius);              // 0xaf9d60
  int IsNonDefault() const;                          // 0xaf9ee0
  tSlot* FindFreeSlot();                             // 0xaf9f30
  int CountFreeSlots();                              // 0xaf9f60
  int CountOccupiedSlots();                          // 0xaf9fa0
  tSlot* SlotAt(unsigned int index);                 // 0xaf9ff0
  int FindClosestFreeSlot(const cSPVector3_s00af_9aa0* p);      // 0xafa5d0
  int FindClosestFreeSlotWeighted(const cSPVector3_s00af_9aa0* p, const cSPVector3_s00af_9aa0* q, float weight);  // 0xafa7c0
};
}
namespace SP {
struct hkArrayUint {
  unsigned int* m_data;      // +0x0
  int m_size;                // +0x4
  int m_capacityAndFlags;    // +0x8

  void push_back(unsigned int v) {
    if (m_size == (m_capacityAndFlags & 0x3fffffff))
      hkArrayUtil::_reserveMore(this, 4);
    m_data[m_size] = v;
    m_size++;
  }
};
}
namespace SP {
class cEntityListener {
 public:
  bool m0;                    // +0x0
  char _pad0[3];
  void* m4;                   // +0x4
  char _pad8[8];              // +0x8
  float m10, m14, m18, m1c;   // +0x10
  float m20, m24, m28, m2c;   // +0x20
  float m30, m34, m38;        // +0x30
  bool m3c;                   // +0x3c
  char _pad3c[3];
  float m40, m44;             // +0x40
  char m48, m49, m4a;         // +0x48
  char _pad4b;
  int m4c;                    // +0x4c
  float m50, m54, m58, m5c;   // +0x50
  void* m_vtbl;               // +0x60
  cEntityListener* m64;       // +0x64
  void* m68;                  // +0x68
  char _pad6c[4];             // +0x6c
  float m70, m74, m78, m7c;   // +0x70
  float m80, m84, m88, m8c;   // +0x80
  float m90, m94, m98;        // +0x90
  hkArrayUint m9c;            // +0x9c
  float mac;                  // +0xac
  int mb0, mb4;               // +0xb0

  void Attach(int, int, int);          // 0xaf8840
  void AddId(unsigned int id);         // 0xaf9ac0
  void RemoveId(unsigned int id);      // 0xaf9b00
  cEntityListener();                   // 0xaf9b50
  void Destroy();                      // 0xaf9ca0
};
}
namespace SP {
class cListenerHolder {
 public:
  char _pad0[4];
  cEntityListener* m_pListener;        // +0x4
  void Detach(int unused);             // 0xaf9aa0
};
}
using SP::cSPVector3_s00af_9aa0;
using SP::cSPQuaternion_s00af_9aa0;
using SP::cEntityListener;
using SP::cActionCircle_s00af_9aa0;
using SP::cGameData_s00af_9aa0;
namespace eastl {
struct AgentDistanceCompare {
  cSPVector3_s00af_9aa0 mOrigin;
  bool operator()(SP::cInteractionAgent_s00af_9aa0* a, SP::cInteractionAgent_s00af_9aa0* b) const;
};  // namespace eastl
}
struct cPlanetModel_s00af_9aa0 {
  float* __thiscall DirectionToSurfacePosition(void* out, const float* dir);  // 0xb815a0
};
// ---- items of slice s00af9aa0 end

// ---- items of slice s00afab70 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <class T>
class AutoRefCount_s00af_ab70 {
 public:
  T* mpObject;
  AutoRefCount_s00af_ab70() : mpObject(0) {}
  AutoRefCount_s00af_ab70(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s00af_ab70(const AutoRefCount_s00af_ab70& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s00af_ab70() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s00af_ab70& operator=(T* p) {
    if (p != mpObject) {
      T* const old = mpObject;
      if (p) p->AddRef();
      mpObject = p;
      if (old) old->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace SP {
struct cSPVector3_s00af_ab70 { float mX, mY, mZ; };
}
namespace SP {
struct cSPQuaternion { float x, y, z, w; };
}
namespace SP {
class cGameData_s00af_ab70 : public EA::IRefCounted {};
}
namespace SP {
class cInteractionAgent_s00af_ab70 : public EA::IRefCounted {};
}
namespace SP {
class cActionCircle_s00af_ab70 {
 public:
  class tSlot {
   public:
    bool mOccupied;                                 // +0x0
    char _pad0[3];
    EA::AutoRefCount_s00af_ab70<cGameData_s00af_ab70> mpReservingNoun;    // +0x4
    unsigned int mReservingId;                      // +0x8
    cSPVector3_s00af_ab70 mPos;                                // +0xc

    void Clear() {
      *(volatile bool*)&mOccupied = false;
      *(volatile unsigned int*)&mReservingId = 0;
      cGameData_s00af_ab70* old = *(cGameData_s00af_ab70* volatile*)&mpReservingNoun.mpObject;
      mpReservingNoun.mpObject = (cGameData_s00af_ab70*)0;
      if (old) old->Release();
    }
  };

  struct AgentVector {
    EA::AutoRefCount_s00af_ab70<cInteractionAgent_s00af_ab70>* mpBegin;   // +0x0
    EA::AutoRefCount_s00af_ab70<cInteractionAgent_s00af_ab70>* mpEnd;     // +0x4
    EA::AutoRefCount_s00af_ab70<cInteractionAgent_s00af_ab70>* mpCapacity;// +0x8
    int mAllocator[2];                              // +0xc
    void Destroy();                                 // 0xafb7a0
  };

  struct SlotVector {
    tSlot* mpBegin;                                 // +0x0
    tSlot* mpEnd;                                   // +0x4
    tSlot* mpCapacity;                              // +0x8
    int mAllocator[2];                              // +0xc
    int GetSize() const { return (int)(mpEnd - mpBegin); }
    void Destroy();                                 // 0xafb090
  };

  cSPVector3_s00af_ab70 mFacing;                               // +0x00
  float mRadius;                                    // +0x0c
  float mSlotRadius;                                // +0x10
  cSPVector3_s00af_ab70 mCenter;                               // +0x14
  float mAltitude;                                  // +0x20
  int mPacking;                                     // +0x24
  bool mbRelative;                                  // +0x28
  char _pad28[3];
  cSPQuaternion mOrientation;                       // +0x2c
  AgentVector mAgents;                              // +0x3c
  SlotVector mSlots;                                // +0x50

  cActionCircle_s00af_ab70();  // 0x00afba10 (SP::cActionCircle::cActionCircle_s00af_ab70)
  ~cActionCircle_s00af_ab70();  // 0x00afba10 (SP::cActionCircle::cActionCircle_s00af_ab70)

  int StartSnapAttractorEffects(const cSPVector3_s00af_ab70* p);   // 0xafab70
  int FindSlotByAgent(cGameData_s00af_ab70* agent);                // 0xafad30
  tSlot* FindClosestFreeSlotPtr(const cSPVector3_s00af_ab70* p);   // 0xafad70
  void RemoveAgent(cGameData_s00af_ab70* agent);                   // 0xafae50
  void ProjectSlotsOntoPlanet();                        // 0xafaec0
  void ClearSlots();                                    // 0xafafd0
  void RemoveSlotsByReservingId(unsigned int id);       // 0xafb020
  int FindClosestFreeSlot(const cSPVector3_s00af_ab70* p);         // 0xafa5d0
};
}
using SP::cSPVector3_s00af_ab70;
using SP::cActionCircle_s00af_ab70;
using SP::cGameData_s00af_ab70;
// ---- items of slice s00afab70 end

// ---- items of slice s00afbaf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char g_szSimulator[];  // 0x013f09b4
extern const char g_szAllocFile[];  // ".../EASTL/include/EASTL/allocator.h"
struct tFloat4 {
    float       x;
    float       y;
    float       z;
    void*       pCtx;

    tFloat4() {}
    tFloat4(const tFloat4& o) { x = o.x; y = o.y; z = o.z; pCtx = o.pCtx; }
    ~tFloat4() {}
};
void*   __cdecl operator_new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                             const char* pFile, int32_t nLine);                 // 0x00f473a0
void    __cdecl operator_delete_(void* pBlock);                                 // 0x00f47380
void    __cdecl FUN_00c83c90(void* pDst, void* pEnd, void* pSrc);               // 0x00c83c90
void*   __cdecl FUN_00afa430(void* pFirst, void* pLast, void* pOut);            // 0x00afa430
void*   __cdecl FUN_00afa380(void* pFirst, void* pLast, void* pOut);            // 0x00afa380
void*   __cdecl FUN_00afa3f0(void* pFirst, void* pLast, void* pOut);            // 0x00afa3f0
void*   __cdecl FUN_00afa4a0(void* pFirst, void* pLast, void* pOut);            // 0x00afa4a0
void*   __cdecl FUN_00afb430(void* pA, void* pB, void* pC, tFloat4 v1, tFloat4 v2); // 0x00afb430
void*   __cdecl FUN_00afb540(void* pFirst, void* pLast, int32_t nPivot);        // 0x00afb540
void    __cdecl FUN_00afb8f0(int32_t* pBase, int32_t nFirst, int32_t nCount, int32_t nRoot,
                             int32_t nKey, tFloat4 v);                          // 0x00afb8f0
void    __cdecl FUN_00afbf40(int32_t* pBase, int32_t* pLast, tFloat4 v);        // 0x00afbf40
void    __cdecl FUN_00afbfb0(int32_t* pBase, int32_t* pLast, tFloat4 v);        // 0x00afbfb0
void    __cdecl FUN_00afc2a0(void** pFirst, void** pLast, void** pLast2, tFloat4 v); // 0x00afc2a0
void    __cdecl FUN_00afc500(int32_t* pFirst, int32_t* pLast, int32_t nLimit, tFloat4 v); // 0x00afc500
class tSlot {
public:
    virtual void    v00();
    virtual void    v04();                          // +0x04 destructor slot
    void*           mpOwned;                        // +0x04  (owned sub-object pointer)
    uint8_t         mPad08[0x18 - 0x08];

    void        CopyConstruct(const tSlot& src);    // 0x00afa110 (thiscall)
    void        Assign(const tSlot& src);           // 0x00afa230 (thiscall)
};
class cSlotVec {
public:
    tSlot*  mpBegin;                                // +0x00
    tSlot*  mpEnd;                                  // +0x04
    tSlot*  mpCap;                                  // +0x08

    tSlot*      EraseRange(tSlot* pFirst, tSlot* pLast);        // 0x00afc0d0
    void        InsertOne(tSlot* pPos, tSlot* pValue);          // 0x00afc150
};
class cPtrVec {
public:
    void**  mpBegin;                                // +0x00
    void**  mpEnd;                                  // +0x04
    void**  mpCap;                                  // +0x08

    void        PushBack(void** ppValue);           // 0x00afc470
    void        Grow(void* pEnd, void** ppValue);   // 0x00bab900
};
class cActionCircle {
public:
    cSlotVec    mSlots;                             // +0x000  (slot vector: begin/end/cap)
    int32_t     mnField0c;                          // +0x00c
    int32_t     mnField10;                          // +0x010
    int32_t     mnField14;                          // +0x014
    float       mf18;                               // +0x018 (inline slot buffer x)
    float       mf1c;                               // +0x01c
    float       mf20;                               // +0x020
    float       mf24;                               // +0x024
    int32_t     mnField28;                          // +0x028
    int32_t     mnField2c;                          // +0x02c
    int32_t     mnField30;                          // +0x030
    int32_t     mnField34;                          // +0x034
    int32_t     mnField38;                          // +0x038
    void*       mpField3c;                          // +0x03c
    int32_t     mnField40;                          // +0x040
    int32_t     mnField44;                          // +0x044
    float       mfField48;                          // +0x048
    float       mfField4c;                          // +0x04c
    cSlotVec    mSlots2;                            // +0x050  (second slot vector)
    float       mf5c;                               // +0x05c
    int32_t     mn60;                               // +0x060
    float       mf64;                               // +0x064
    float       mf68;                               // +0x068
    float       mf6c;                               // +0x06c
    float       mf70;                               // +0x070
    float       mf74;                               // +0x074
    float       mf78;                               // +0x078
    float       mf7c;                               // +0x07c
    float       mf80;                               // +0x080
    float       mf84;                               // +0x084
    float       mf88;                               // +0x088
    float       mf8c;                               // +0x08c
    float       mf90;                               // +0x090
    float       mf94;                               // +0x094
    uint8_t     mb98;                               // +0x098
    uint8_t     mPad99[3];                          // +0x099
    float       mf9c;                               // +0x09c
    float       mfa0;                               // +0x0a0
    float       mfa4;                               // +0x0a4
    float       mfa8;                               // +0x0a8
    float       mfac;                               // +0x0ac
    float       mfb0;                               // +0x0b0
    float       mfb4;                               // +0x0b4
    float       mfb8;                               // +0x0b8
    float       mfbc;                               // +0x0bc
    float       mfc0;                               // +0x0c0
    float       mfc4;                               // +0x0c4 (unwritten in ctor)
    uint8_t     mbc8;                               // +0x0c8
    uint8_t     mPadc9[3];                          // +0x0c9
    float       mfcc;                               // +0x0cc
    float       mfd0;                               // +0x0d0
    float       mfd4;                               // +0x0d4
    float       mfd8;                               // +0x0d8
    int32_t     mdc;                                // +0x0dc
    int32_t     me0;                                // +0x0e0
    int32_t     me4;                                // +0x0e4
    int32_t     me8;                                // +0x0e8 (unwritten in ctor)
    int32_t     mec;                                // +0x0ec (unwritten in ctor)
    int32_t     mf0;                                // +0x0f0
    int32_t     mf4;                                // +0x0f4
    int32_t     mf8;                                // +0x0f8
    float       mffc;                               // +0x0fc (unwritten in ctor)
    float       mf100;                              // +0x100 (unwritten in ctor)
    float       mf104;                              // +0x104
    float       mf108;                              // +0x108
    float       mf10c;                              // +0x10c
    float       mf110;                              // +0x110
    float       mf114;                              // +0x114
    float       mf118;                              // +0x118
    float       mf11c;                              // +0x11c
    float       mf120;                              // +0x120
    float       mf124;                              // +0x124
    float       mf128;                              // +0x128 (unwritten in ctor)
    uint8_t     mbc12c;                             // +0x12c
    uint8_t     mPad12d[3];                         // +0x12d
    float       mf130;                              // +0x130
    float       mf134;                              // +0x134
    float       mf138;                              // +0x138
    float       mf13c;                              // +0x13c
    int32_t     m140;                               // +0x140
    int32_t     m144;                               // +0x144
    int32_t     m148;                               // +0x148
    int32_t     m14c;                               // +0x14c (unwritten in ctor)
    int32_t     m150;                               // +0x150 (unwritten in ctor)
    int32_t     m154;                               // +0x154
    int32_t     m158;                               // +0x158
    int32_t     m15c;                               // +0x15c
    int32_t     m160;                               // +0x160 (unwritten in ctor)
    int32_t     m164;                               // +0x164 (unwritten in ctor)
    int32_t     m168;                               // +0x168
    int32_t     m16c;                               // +0x16c
    int32_t     m170;                               // +0x170
    int32_t     mnField174;                         // +0x174

    cActionCircle();                                // 0x00afbaf0
    bool        EraseOne(tSlot* pPos);              // 0x00afc410
};
// ---- items of slice s00afbaf0 end

// ---- items of slice s00afd1c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_PI;                  // 0x0167af14
namespace SP {
struct cSPVector3_s00af_d1c0 { float x, y, z; };
}
namespace SP {
struct cSPQuaternion_s00af_d1c0 { float x, y, z, w; };
}
namespace SP {
class cGameData_s00af_d1c0 {
 public:
	virtual void dtor();      // +0
	virtual int AddRef();     // +4
	virtual int Release();    // +8
};
}
namespace SP {
class cGameDataRef {
 public:
	cGameData_s00af_d1c0* mpObject;                    // +0
	void AddRef() { if (mpObject) mpObject->AddRef(); }
	void Release() { if (mpObject) mpObject->Release(); }
};
}
namespace SP {
class cActionCircle_s00af_d1c0 {
 public:
	struct tSlot {                          // 0x18 bytes
		bool mOccupied;                     // +0x0
		char _pad0[3];
		cGameDataRef mReservingNoun;        // +0x4
		unsigned int mReservingId;          // +0x8
		cSPVector3_s00af_d1c0 mPos;                    // +0xc
	};

	struct SlotVector {
		tSlot* mpBegin;                     // +0
		tSlot* mpEnd;                       // +4
		tSlot* mpCapacity;                  // +8

		void Erase(tSlot* first, tSlot* last);              // 0x00afc0d0
		void InsertAtEnd(tSlot* where, const tSlot* value); // 0x00afc150
		void Reserve(int count);                            // 0x00afbe80

		void push_back(const tSlot& value) {
			tSlot* end = mpEnd;
			if (end != mpCapacity) {
				mpEnd = end + 1;
				if (end) {
					end->mOccupied = false;
					end->mReservingNoun.mpObject = 0;
					end->mReservingId = 0;
					end->mPos = value.mPos;
				}
			}
			else {
				InsertAtEnd(end, &value);
			}
		}
	};

	cSPVector3_s00af_d1c0 mFacing;                     // +0x00
	float mRadius;                          // +0x0c
	float mSlotRadius;                      // +0x10
	cSPVector3_s00af_d1c0 mCenter;                     // +0x14
	float mAltitude;                        // +0x20
	int mPacking;                           // +0x24
	bool mbRelative;                        // +0x28
	char _pad29[0x50 - 0x29];
	SlotVector mSlots;                      // +0x50

	void SetSpiralSlots(float radius, int count);                    // 0x00afd1c0
	void SetRingSlots(float radius, float density, int count);       // 0x00afd6d0
	void SetFanSlots(float radius, float spread, int count);         // 0x00afdc00

	// Appends one slot holding pos (the vector's push_back plus the temporary's release).
	void AddSlot(const cSPVector3_s00af_d1c0& pos) {
		tSlot slot;
		slot.mOccupied = false;
		slot.mReservingNoun.mpObject = 0;
		slot.mReservingId = 0;
		slot.mPos = pos;
		mSlots.push_back(slot);
		slot.mReservingNoun.Release();
	}
};
}
namespace SP {
class cPlanetModel_s00af_d1c0 {
 public:
	cSPVector3_s00af_d1c0 DirectionToSurfacePosition(const cSPVector3_s00af_d1c0& dir);    // 0x00b815a0
};
}
namespace SP {
cPlanetModel_s00af_d1c0* PlanetModel_s00af_d1c0();                                        // 0x00b3d350
}
using SP::cSPVector3_s00af_d1c0;
using SP::cSPQuaternion_s00af_d1c0;
using SP::cActionCircle_s00af_d1c0;
extern cSPVector3_s00af_d1c0 g_defaultCenter;  // 0x0167aec4
extern cSPVector3_s00af_d1c0 g_defaultAxis;    // 0x0167af18
extern cSPVector3_s00af_d1c0 g_defaultAxisAlt; // 0x0167af24
static const float kNormEps = 1.0e-08f;   // 0x013ec4b8
static const float kTwo = 2.0f;           // 0x01470f1c
static const float kHalf = 0.5f;          // 0x01471064
static const float kSpiralStep = 0.41666666f;  // 0x0145c464 = 5/12
static const float kDenseLimit = 0.95f;   // 0x013f7344
static cSPVector3_s00af_d1c0 RotateByQuat(const cSPQuaternion_s00af_d1c0& q, const cSPVector3_s00af_d1c0& v)
{
	const float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
	const float xy = q.x * q.y, xz = q.x * q.z, yz = q.y * q.z;
	const float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;

	cSPVector3_s00af_d1c0 r;
	r.x = ((1.0f - (yy + zz) * kTwo) * v.x + (xy - wz) * kTwo * v.y) + (xz + wy) * kTwo * v.z;
	r.y = ((xy + wz) * kTwo * v.x + (1.0f - (xx + zz) * kTwo) * v.y) + (yz - wx) * kTwo * v.z;
	r.z = ((xz - wy) * kTwo * v.x + (yz + wx) * kTwo * v.y) + (1.0f - (xx + yy) * kTwo) * v.z;
	return r;
}
// ---- items of slice s00afd1c0 end

// ---- items of slice s00afdfe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float DAT_013ec4b8;      // 1e-08f guard added to the normal-length sum
extern const float DAT_01567354;      // emitter 1/2 density scale
extern const float DAT_01471064;      // 0.5f
extern const float DAT_01470f1c;      // emitter 3 spacing scale
extern const float DAT_0167aec4, DAT_0167aec8, DAT_0167aecc;   // surface origin x/y/z
extern const float DAT_0167aef4, DAT_0167aef8, DAT_0167aefc;   // default up x/y/z
extern const float DAT_0167af18, DAT_0167af1c, DAT_0167af20;   // alternative up x/y/z
extern "C" void* g_PlanetModel();                                                     // 0x00b3d350
extern "C" float* Func_afa510(float* out, const float* uv, float radius);             // 0x00afa510
extern "C" float* SquareToCircle(float* out, float u, float v);                       // 0x00a7c630
extern "C" void Func_afc500();   // 0x00afc500  quicksort pass setup
extern "C" void Func_afb230();   // 0x00afb230  partition
extern "C" void Func_afb340();   // 0x00afb340  partition (upper half)
extern "C" void Func_afc4b0(void* self, void* key);   // 0x00afc4b0
struct DecalRec { u8 m_hdr; u8 m_pad0[3]; void* m_ptr; void* m_pad1; float m_x, m_y, m_z; };  // 0x18
struct RandomLCG { u32 __thiscall RandomUint32Uniform(u32 range); };                  // 0x00a68fb0
extern RandomLCG g_sMathRandom;                                                       // 0x01601760
struct ArrayVT
{
	void  __thiscall clear(void* a, void* b);          // 0x00afc0d0
	void* __thiscall pushBack(void* value);            // 0x00afc030
	void  __thiscall reserve(int n);                   // 0x00afbe80
	void  __thiscall constructAt(void* zero);          // 0x00afc150
	void  __thiscall eraseOne(void* key);              // 0x00afc4b0
	void  __thiscall removeByKey(void* key);           // 0x00afb130
	void* __thiscall find(void* out, const void* key); // 0x00afb0d0
	void  __thiscall assignMatrix(const void* src);    // 0x0041cb40
	void  __thiscall eraseRange(void* first, void* last, int n, float x, float y, float z);  // 0x00afc500
};
struct ScatterRng { float m_v; float m_w; u32 m_i; u32 m_j; };
static void decalAppend(char* self, float x, float y, float z)
{
	ArrayVT* vec = (ArrayVT*)(self + 0x50);
	DecalRec tmp;
	tmp.m_hdr  = 0;
	tmp.m_ptr  = 0;
	tmp.m_pad1 = 0;
	tmp.m_x = x; tmp.m_y = y; tmp.m_z = z;

	DecalRec* end = *(DecalRec**)(self + 0x54);
	if (end < *(DecalRec**)(self + 0x58)) {
		*(DecalRec**)(self + 0x54) = end + 1;
		if (end) *end = tmp;
	} else {
		vec->constructAt(&tmp);
		if (tmp.m_ptr) {
			void** vt = *(void***)tmp.m_ptr;
			((void(__thiscall*)(void*))vt[1])(tmp.m_ptr);
		}
	}
}
struct SortCtx { float m_a; float m_b; float m_c; u32 m_d; };
typedef void (__cdecl *SortFn)(char*, char*, int, SortCtx);
// ---- items of slice s00afdfe0 end

// ---- items of slice s00afef10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gRadialDensity;            // 0x0167af14
class cVector3 {
public:
    float x;    // +0x00
    float y;    // +0x04
    float z;    // +0x08
    cVector3() {}
    cVector3(float fValue) : x(fValue), y(fValue), z(fValue) {}
};
class cSurfaceDecal {
public:
    uint8_t mbUsed;                     // +0x00
    uint8_t mnPad01[0x0b];              // +0x01
    float mRadius;                      // +0x0c
    float mSize;                        // +0x10
    uint8_t mnPad14[0x04];              // +0x14
    void Emit(uint32_t nKind, float nSize);                    // 0x00afef10
    void Generate(float nRadius);                              // 0x00afc640
    void EmitRadial(float nSize, float nStep, int32_t nCount); // 0x00afd6d0
    void EmitArc(float nSize, float nMin, int32_t nFlags);     // 0x00afdc00
    void EmitRing(float nSize);                                // 0x00afdfe0
    void EmitSweep(float nSize);                               // 0x00afe3a0
    void EmitGrid(float nSize);                                // 0x00afe670
};
class cIntVector {
public:
    int32_t* mpBegin;                   // +0x00
    int32_t* mpEnd;                     // +0x04
    void Resize(int32_t nCount);        // 0x004cd3c0
};
class cSurfaceDecalManager;
void SortDecalsImpl(cSurfaceDecal* pBegin, cSurfaceDecal* pEnd,
                    cVector3 vPosition, cSurfaceDecalManager* pManager); // 0x00afee20
void ShuffleIndices(int32_t* pBegin, int32_t* pEnd, void* pRandom);      // 0x00afb8a0
void InitStackVector(int32_t nCount);                                    // 0x00454b80
class cSurfaceDecalManager {
public:
    uint8_t mnPad00[0x50];              // +0x00
    cSurfaceDecal* mpDecalBegin;        // +0x50
    cSurfaceDecal* mpDecalEnd;          // +0x54
    void SortDecals(const cVector3* pPosition, cIntVector* pOrder); // 0x00afeff0
    cSurfaceDecal* FindFreeDecal();                                  // 0x00aff070
};
// ---- items of slice s00afef10 end

// @ 0x00af08e0
__declspec(noinline) Node* __stdcall NewNode(const Node* src, void* parent)
{
    Node* n = (Node*)EAAllocate(0x20, g_allocName, 0, 0, g_allocFile, 0xd1);
    if (&n->key)
    {
        u32* d = (u32*)&n->key;
        d[0] = src->key;
        d[1] = src->t0;
        d[2] = src->t1;
        d[3] = src->v;
    }
    n->left = 0;
    n->right = 0;
    n->parent = (Node*)parent;
    n->color = src->color;
    return n;
}

// @ 0x00af0940
void __thiscall RBTree::FindBounds(HIter* out, const int* key)
{
    Node* root = this->root;
    Node* lower = (Node*)&this->base;
    if (root != 0)
    {
        int k = *key;
        Node* n = root;
        do
        {
            if (k < n->key)
            {
                lower = n;
                n = n->right;
            }
            else
            {
                n = n->left;
            }
        } while (n != 0);
    }
    Node* upper = (Node*)&this->base;
    if (root != 0)
    {
        int k = *key;
        Node* n = root;
        do
        {
            if (n->key < k)
            {
                n = n->left;
            }
            else
            {
                upper = n;
                n = n->right;
            }
        } while (n != 0);
    }
    out->b = lower;
    out->a = upper;
}

// @ 0x00af09a0
Node* __thiscall RBTree::Clone(Node* src, void* parent)
{
    Node* head = NewNode(src, parent);
    if (src->left != 0)
        head->left = Clone(src->left, head);
    Node* prev = head;
    for (Node* p = src->right; p != 0; p = p->right)
    {
        Node* n = (Node*)EAAllocate(0x20, g_allocName, 0, 0, g_allocFile, 0xd1);
        if (&n->key)
        {
            u32* d = (u32*)&n->key;
            d[0] = p->key;
            d[1] = p->t0;
            d[2] = p->t1;
            d[3] = p->v;
        }
        n->left = 0;
        n->right = 0;
        n->parent = prev;
        n->color = p->color;
        prev->right = n;
        if (p->left != 0)
            n->left = Clone(p->left, n);
        prev = n;
    }
    return head;
}

// @ 0x00af0a60
bool __cdecl Lookup(void* table, u32 hash, int t, int key, float* out)
{
    HashTable* t1 = (HashTable*)table;
    HIter h;
    ((XHash*)t1)->HashFind(&h, &hash);
    if ((HashNode*)h.a != t1->buckets[t1->bucketCount])
    {
        RBTree* tree = (RBTree*)((char*)(HashNode*)h.a + 4);
        tree->FindBounds(&h, &key);
        Node* n = (Node*)h.a;
        for (Node* last = (Node*)h.b; n != last; n = RBTreeInc(n))
        {
            if (t >= n->t0 && t <= n->t1)
            {
                if (out)
                    *out = *(float*)&n->v;
                return true;
            }
        }
    }
    return false;
}

// @ 0x00af0af0
bool __thiscall LayoutMgr::LookupA(void* entity, int key, float* out)
{
    float secs = ((XTimeOfDay*)Instance())->GetSeconds(
        ((XComp*)((XComp*)entity)->Get())->GetPosition());
    float day = *(float*)((char*)Instance() + 0x24);
    float f;
    if (day > g_zero)
        f = secs / day;
    else
        f = secs * g_invDay;
    int ms = (int)((f * g_secPerDay) * g_msPerSec);
    u32 comp = ((XComp*)entity)->Get();
    u32 hash = 0x50a2c197;
    void* arch = ((XSpeciesMgr*)GetSetting9(*(u32*)(comp + 0x88), *(u32*)(comp + 0xf0)))->GetArchetype();
    if (arch != 0)
    {
        comp = ((XComp*)entity)->Get();
        u32 idx = *(u32*)(comp + 0x90);
        u32 cnt = (u32)((*(int*)((char*)arch + 0x3e0) - *(int*)((char*)arch + 0x3dc)) >> 2);
        if (idx < cnt)
            hash = *(u32*)(*(u32*)((char*)arch + 0x3dc) + idx * 4);
    }
    return Lookup(this, hash, ms, key, out);
}

// @ 0x00af0bd0
bool __thiscall LayoutMgr::LookupB(void* entity, int key, float* out)
{
    u32 local[3];
    void* comp = (void*)((XComp*)entity)->GetAlt();
    u32 id = ((VCall1)(*(void***)comp)[0x58 / 4])(comp, local);
    float secs = ((XTimeOfDay*)Instance())->GetSeconds(id);
    float day = *(float*)((char*)Instance() + 0x24);
    float f;
    if (day > g_zero)
        f = secs / day;
    else
        f = secs * g_invDay;
    u8 flag = ((VFlag)(*(void***)((char*)entity + 0xc0))[0x58 / 4])((char*)entity + 0xc0);
    u32 hash = flag ? 0x2d0c5c76 : 0x20bd87a3;
    int ms = (int)((f * g_secPerDay) * g_msPerSec);
    return Lookup((HashTable*)((char*)this + 0x20), hash, ms, key, out);
}

// @ 0x00af0c90
bool __thiscall LayoutMgr::LookupC(void* entity, int key, float* out)
{
    void* obj = (char*)entity + 0x120;
    u32 id = ((VCall0)(*(void***)obj)[0x2c / 4])(obj);
    float secs = ((XTimeOfDay*)Instance())->GetSeconds(id);
    float day = *(float*)((char*)Instance() + 0x24);
    float f;
    if (day > g_zero)
        f = secs / day;
    else
        f = secs * g_invDay;
    u8 flag = ((VFlag)(*(void***)obj)[0x58 / 4])(obj);
    u32 hash = flag ? 0x2d0c5c76 : 0x20bd87a3;
    int ms = (int)((f * g_secPerDay) * g_msPerSec);
    return Lookup((HashTable*)((char*)this + 0x20), hash, ms, key, out);
}

// @ 0x00af0db0
void __thiscall HashTable::FreeChains(HashNode** buckets, u32 count)
{
    for (u32 i = 0; i < count; i++)
    {
        HashNode* n = buckets[i];
        while (n != 0)
        {
            HashNode* cur = n;
            n = n->next;
            InnerNode* p = *(InnerNode**)((char*)cur + 0x10);
            while (p != 0)
            {
                ((XClear*)((char*)cur + 4))->ClearValue(p->val);
                InnerNode* pn = p->next;
                FreeMem(p);
                p = pn;
            }
            FreeMem(cur);
        }
        buckets[i] = 0;
    }
}

// @ 0x00af0f30
void __thiscall LayoutMgr::ClearBucketChains()
{
    mbInit = 0;
    t1.FreeChains(t1.buckets, t1.bucketCount);
    t1.size = 0;
    HashTable* t2p = &t2;
    t2p->FreeChains(t2p->buckets, t2p->bucketCount);
    t2p->size = 0;
}

// @ 0x00af0f70
void* __thiscall HashTable::GetOrCreate(const u32* key)
{
    HIter it;
    ((XHash*)this)->HashFind(&it, key);
    if ((HashNode*)it.a == buckets[bucketCount])
    {
        World tmp;
        RBTree* t = &tmp.tree;
        t->base = &t->base;
        t->end = &t->base;
        t->root = 0;
        t->flag = 0;
        t->size = 0;

        Pair v;
        v.key = *key;
        ((XTreeCopy*)&v.w)->CopyFrom(&tmp);
        ((XHashIns*)this)->InsertVal(&it, &v, 0);
        ((XTreeNuke*)&v.w)->Nuke(v.w.tree.root);
        ((XTreeNuke*)&tmp)->Nuke(tmp.tree.root);
    }
    return (char*)it.a + 4;
}

// @ 0x00af1020
void __thiscall LayoutMgr::BuildTables()
{
    if (mbInit)
        return;
    mbInit = 1;
    void* pm = PropertyManager();
    SrcEntry src[2] = { { 0xbc20ed3a, &t1 }, { 0xcfc92e4b, &t2 } };
    PropEntry map[7] = {
        { 0x44d93bf0, 2 }, { 0x737e2d79, 0 }, { 0x43c23e71, 1 },
        { 0x45cb28e8, 3 }, { 0xa94d6d17, 4 }, { 0xf5f01a87, 5 },
        { 0x1e640af0, 6 },
    };
    void* rec = 0;
    for (int s = 0; s < 2; s++)
    {
        u32 ctx = src[s].id;
        VecU32 list = { 0, 0, 0 };
        ((bool (__thiscall*)(void*, u32, void*))(*(void***)pm)[0x48 / 4])(pm, ctx, &list);
        u32* p = list.begin;
        while (p != list.end)
        {
            u32 id = *p;
            if (rec)
            {
                ((void (__thiscall*)(void*))(*(void***)rec)[1])(rec);
                rec = 0;
            }
            if (((u8 (__thiscall*)(void*, u32, u32, void**))(*(void***)pm)[0x2c / 4])(pm, id, ctx, &rec))
            {
                World* w = (World*)src[s].tbl->GetOrCreate(&id);
                for (u32 e = 0; e < 7; e++)
                {
                    int count = 0;
                    int data = 0;
                    if (!FindProperty(rec, map[e].key, &count, &data))
                        continue;
                    if (count <= 0)
                        continue;
                    int slot = map[e].idx;
                    int off = 0;
                    for (int i = 0; i < count; i++, off += 0xc)
                    {
                        float* d = (float*)(data + off);
                        float f0 = (d[0] * g_minScale) * g_minScale2;
                        int t0 = (int)f0;
                        if (f0 < (float)t0)
                            t0--;
                        float f1 = (d[1] * g_minScale) * g_minScale2;
                        int t1 = (int)f1;
                        if (f1 < (float)t1)
                            t1--;
                        float v = d[2];
                        if (v < g_eps)
                            v = g_one;

                        RBTree* tr = &w->tree;
                        Node* base = (Node*)&tr->base;
                        Node* parent = base;
                        Node* n = tr->root;
                        int side = 0;
                        while (n)
                        {
                            parent = n;
                            n = (slot >= n->key) ? n->left : n->right;
                        }
                        if (parent != base && slot >= parent->key)
                            side = 1;
                        Node* nn = (Node*)EAAllocate(0x20, g_allocName, 0, 0, g_allocFile, 0xd1);
                        if (&nn->key)
                        {
                            nn->key = slot;
                            nn->t0 = t0;
                            nn->t1 = t1;
                            nn->v = *(u32*)&v;
                        }
                        RBTreeInsert(nn, parent, base, side);
                        tr->size++;
                    }
                }
            }
            p++;
        }
        if (list.begin && list.begin[-1])
            FreeMem(list.begin);
    }
    if (rec)
        ((void (__thiscall*)(void*))(*(void***)rec)[1])(rec);
}

// @ 0x00af13b0
void __cdecl CreateLayoutManager()
{
    LayoutMgr* cur = (LayoutMgr*)g_singleton_167ad74;
    if (cur != 0)
        return;
    LayoutMgr* m = (LayoutMgr*)EAAllocate(0x44, g_allocName, 0, 0, 0, 0);
    if (m == 0)
    {
        g_singleton_167ad74 = 0;
    }
    else
    {
        float one = g_one;
        float two = g_two;
        m->t1.f10 = one;
        m->t1.f14 = two;
        m->t1.size = 0;
        m->t1.unk18 = 0;
        m->t1.bucketCount = 1;
        m->t1.buckets = (HashNode**)0x0154df28;
        m->t2.f10 = one;
        m->t2.f14 = two;
        m->t2.size = 0;
        m->t2.unk18 = 0;
        m->t2.bucketCount = 1;
        m->t2.buckets = (HashNode**)0x0154df28;
        m->mbInit = 0;
        g_singleton_167ad74 = (u32)m;
    }
}

// @ 0x00af1430
void __thiscall TimerOwner::Dtor()
{
    vtable = 0x0145c1bc;
    ((XGonzago*)timer)->Dtor();
    ((XList*)&head)->DoClear();
}

// @ 0x00af1450
void __thiscall TimerOwner::Add(const void* wstr)
{
    ((XSPTimer*)timer)->Restart();
    ((XList*)&head)->DoClear();
    ListHead* h = &head;
    h->next = (ListNode*)h;
    h->prev = (ListNode*)h;
    ListNode* n = (ListNode*)EAAllocate(0x18, g_allocName, 0, 0, g_allocFile, 0xd1);
    if (&n->str)
        ((XWString*)&n->str)->Ctor(wstr);
    n->next = (ListNode*)h;
    n->prev = h->prev;
    h->prev->next = n;
    h->prev = n;
}

// @ 0x00af14b0
TimerOwner* __thiscall TimerOwner::Ctor()
{
    vtable = 0x0145c1bc;
    ListHead* h = &head;
    h->next = (ListNode*)h;
    h->prev = (ListNode*)h;
    ((XGonzago*)timer)->Ctor();
    g_stopwatch.SetUnits(4);
    if ((g_stopwatch.lo | g_stopwatch.hi) == 0)
    {
        if (g_stopwatch.units == 1)
        {
            u64 t = __rdtsc();
            g_stopwatch.hi = (u32)(t >> 32);
            g_stopwatch.lo = (u32)t;
            ((XSPTimer*)timer)->Start();
            return this;
        }
        LI li;
        QueryPerformanceCounter(&li);
        g_stopwatch.lo = li.s.lo;
        g_stopwatch.hi = (u32)li.s.hi;
    }
    ((XSPTimer*)timer)->Start();
    return this;
}

// @ 0x00af1540
TimerOwner* __thiscall TimerOwner::Delete(u32 flags)
{
    vtable = 0x0145c1bc;
    ((XGonzago*)timer)->Dtor();
    ((XList*)&head)->DoClear();
    if (flags & 1)
        FreeMem(this);
    return this;
}

// @ 0x00af1570
void __cdecl InitWorld(World* dst, u32 a2, const Vec3* a3, const Vec3* a4, float a5, u8 a6, const Block* blk)
{
    dst->f20 = a2;
    dst->f24 = 0;
    dst->p = *a3;
    dst->q = *a4;
    dst->f54 = a5;
    dst->flag40 = a6;
    dst->d34 = g_default34;
    dst->d38 = g_default38;
    dst->d3c = g_default3c;
    if (blk != 0)
    {
        *(Block*)dst = *blk;
    }
    else
    {
        memset(dst, 0, 0x20);
    }
}

// @ 0x00af1610
void __cdecl InitWorld2(World* dst, u32 a2, const Vec3* a3, const Vec3* a4, const Vec3* a5, const Vec3* a6, const Vec3* a7, float a8)
{
    dst->f20 = a2;
    dst->f24 = 3;
    dst->p = *a3;
    dst->q = *a4;
    dst->f54 = a8;
    dst->r5 = *a5;
    dst->r6 = *a6;
    dst->r7 = *a7;
    dst->flag40 = 0;
    dst->d34 = g_default34;
    dst->d38 = g_default38;
    dst->d3c = g_default3c;
    dst->tree.unk00 = 0;
    dst->tree.base = 0;
    dst->tree.end = 0;
    dst->tree.root = 0;
    *(u32*)&dst->tree.flag = 0;
    dst->tree.size = 0;
    dst->tree.unk18 = 0;
    dst->gap1c = 0;
}

// @ 0x00af16f0
bool __cdecl RaySphere(const Vec3* p, const Vec3* dir, float scale, const Vec3* center, float radius, float* out)
{
    float dx = p->x - center->x;
    float dy = p->y - center->y;
    float dz = p->z - center->z;
    float b = dir->y * dy + dir->z * dz + dir->x * dx;
    float c = dx * dx + dy * dy + dz * dz - radius * radius;
    float disc = b * b - c * scale;
    if (c < 0.0f)
    {
        if (out)
            *out = 0.0f;
        return true;
    }
    if (disc < 0.0f)
        return false;
    float s = (float)sqrt(disc);
    float t = -b - s;
    if (s - b < 0.0f)
        return false;
    if (t > scale)
        return false;
    if (out)
    {
        if (t > 0.0f)
            *out = t / scale;
        else
            *out = 0.0f;
    }
    return true;
}

// @ 0x00af17f0
bool __cdecl SweepWorld(World* dst, u32 id, const Vec3* origin, const Vec3* center, const Vec3* dir, Vec3* tvec, float scale, float radius, u8 flag, const Block* blk)
{
    Vec3 local;
    float t = tvec->x;
    local.x = dir->x * t;
    local.y = dir->y * t;
    local.z = dir->z * t;
    float hit;
    if (RaySphere(origin, &local, t * t, center, radius, &hit))
    {
        if (hit != 0.0f || flag)
        {
            float nt = (tvec->x * hit) * scale;
            tvec->x = nt;
            local.x = dir->x * nt + origin->x;
            local.y = dir->y * nt + origin->y;
            local.z = dir->z * nt + origin->z;
            InitWorld(dst, id, center, &local, radius, flag, blk);
            return true;
        }
    }
    return false;
}

// @ 0x00af1910
cSweepResult& cSweepResult::operator=(const cSweepResult& src)
{
    mHead      = src.mHead;             // +0x00..+0x1F, one aggregate copy
    mHitKind   = src.mHitKind;          // +0x20
    mHitSlot   = src.mHitSlot;          // +0x24
    mHitCenter = src.mHitCenter;        // +0x28
    mHitNormal = src.mHitNormal;        // +0x34
    mbFlag     = src.mbFlag;            // +0x40
    mDist      = src.mDist;             // +0x44
    mHitPos    = src.mHitPos;           // +0x48
    mRadius    = src.mRadius;           // +0x54
    mBoxMin    = src.mBoxMin;           // +0x64 (assigned before the +0x58 box)
    mBoxMax    = src.mBoxMax;           // +0x58
    mTransform.Assign(src.mTransform);  // +0x70, 0x00537DC0
    mMeshPoint    = src.mMeshPoint;     // +0xa8
    mVertCount    = src.mVertCount;     // +0xb4
    mpVerts       = src.mpVerts;        // +0xb8
    mSurfaceId    = src.mSurfaceId;     // +0xbc
    mSurfaceFlags = src.mSurfaceFlags;  // +0xc0
    mExtraC4      = src.mExtraC4;       // +0xc4
    mExtraRadius  = src.mExtraRadius;   // +0xc8
    mExtraCC      = src.mExtraCC;       // +0xcc
    mExtraD8      = src.mExtraD8;       // +0xd8
    mExtraE4      = src.mExtraE4;       // +0xe4
    return *this;
}

// @ 0x00af1a90
bool FUN_00af1a90(float* param_1, float* param_2, float* param_3, float param_4, float param_5, void* p)
{
    char  cVar2;
    float *pfVar3, *pfVar8;
    int   iVar1, iVar4, iVar5, iVar6, iVar7;
    float fVar9, fVar10, fVar11, fVar12, fVar13, fVar14, fVar15, fVar16,
          fVar17, fVar18, fVar19, fVar20, fVar21;
    float local_108, local_104, local_100;
    float local_fc, local_f8, local_f4, local_f0, local_ec, local_e8;
    int   local_e4;
    float local_e0, local_dc, local_d8, local_d4, local_d0, local_cc, local_c8;
    int   local_c4;
    float local_c0, local_bc, local_b4, local_b0, local_ac;
    float local_a8[3], local_9c[3], local_90[3], local_84[3], local_78[3], local_6c[3];
    // The two case-0 normalized_safe inputs are 3-float vectors.  They must be a real
    // contiguous array: passing &local_108 of three separate scalar locals lets the
    // compiler place the y/z stores in unrelated stack slots, so the callee reads
    // garbage for y/z (and the result differs from the original for some inputs).
    float local_v[3];
    float local_va[3];

    switch (OI(0x24)) {
    case 0: {
        local_v[0] = OF(0x28) - param_1[0];
        local_v[1] = OF(0x2c) - param_1[1];
        local_v[2] = OF(0x30) - param_1[2];
        pfVar3 = (float*)((char*)p + 0x28);
        pfVar8 = normalized_safe(local_6c, local_v);
        local_fc = pfVar8[0];
        local_f8 = pfVar8[1];
        local_f4 = pfVar8[2];
        pfVar8 = normalized_safe(local_a8, pfVar3);
        local_v[0] = (pfVar8[2] * local_f8 - pfVar8[1] * local_f4) * param_4;
        local_v[1] = (pfVar8[0] * local_f4 - local_fc * pfVar8[2]) * param_4;
        local_v[2] = (local_fc * pfVar8[1] - pfVar8[0] * local_f8) * param_4;
        pfVar8 = FUN_00699800(local_84, pfVar3, OF(0x54), param_1, local_v);
        param_3[0] = pfVar8[0];
        param_3[1] = pfVar8[1];
        param_3[2] = pfVar8[2];
        if (((param_3[0] == DAT_0167ae24) && (param_3[1] == DAT_0167ae28)) &&
            (param_3[2] == DAT_0167ae2c)) {
            fVar19 = OF(0x54);
            fVar13 = OF(0x2c);
            fVar16 = OF(0x30);
            param_3[0] = pfVar3[0] - local_fc * fVar19;
            param_3[1] = fVar13 - fVar19 * local_f8;
            param_3[2] = fVar16 - fVar19 * local_f4;
            cVar2 = FUN_004232c0(param_3, &DAT_0167ae24);
            if (cVar2 != 0)
                return 0;
        }
        fVar19 = param_1[2];
        fVar13 = param_1[1];
        fVar15 = param_3[2] - fVar19;
        fVar11 = param_3[1] - fVar13;
        fVar16 = param_3[0] - param_1[0];
        if ((fVar15 * fVar15 + fVar11 * fVar11) + fVar16 * fVar16 < 1.5258789e-05f) {
            fVar16 = OF(0x54);
            param_3[0] = local_v[0] * fVar16 + param_1[0];
            param_3[1] = fVar16 * local_v[1] + fVar13;
            param_3[2] = fVar16 * local_v[2] + fVar19;
        }
        if (1.5258789e-05f < param_5) {
            fVar19 = param_3[0];
            local_d4 = param_3[1];
            local_c0 = param_3[2];
            local_v[0] = fVar19 - pfVar3[0];
            local_v[1] = local_d4 - OF(0x2c);
            local_v[2] = local_c0 - OF(0x30);
            pfVar3 = normalized_safe(local_9c, local_v);
            fVar13 = pfVar3[1];
            fVar16 = pfVar3[2];
            param_3[0] = pfVar3[0] * param_5 + fVar19;
            param_3[1] = local_d4 + fVar13 * param_5;
            param_3[2] = local_c0 + fVar16 * param_5;
            return 1;
        }
        break;
    }
    case 1: {
        pfVar3 = (float*)((char*)p + 0x28);
        FUN_00436ce0(local_va, pfVar3);
        local_e0 = local_va[0];
        local_dc = local_va[1];
        local_d8 = local_va[2];
        local_c8 = param_1[1] - OF(0x2c);
        fVar19 = OF(0x48);
        fVar16 = (local_d8 * (param_1[2] - OF(0x30)) + local_dc * local_c8) +
                 (param_1[0] - pfVar3[0]) * local_e0;
        local_cc = (param_1[0] - pfVar3[0]) - local_e0 * fVar16;
        fVar13 = OF(0x4c);
        local_c8 = local_c8 - local_dc * fVar16;
        fVar16 = OF(0x50);
        local_108 = (OF(0x84) * fVar19 + OF(0x9c) * fVar16) + OF(0x90) * fVar13;
        local_104 = (fVar16 * OF(0xa0) + fVar13 * OF(0x94)) + OF(0x88) * fVar19;
        local_100 = (OF(0x8c) * fVar19 + fVar16 * OF(0xa4)) + fVar13 * OF(0x98);
        fVar19 = (local_108 * local_e0 + local_104 * local_dc) + local_100 * local_d8;
        local_108 = local_108 - fVar19 * local_e0;
        local_104 = local_104 - local_dc * fVar19;
        local_100 = local_100 - local_d8 * fVar19;
        float m[24];
        ((const cSPBoundingBox_s00af_1a90*)((char*)p + 0x58))->GetCorners((cSPVector3_s00af_1a90*)m);
        local_fc = local_108;
        local_f8 = local_104;
        local_f4 = local_100;
        fVar19 = OF(0x9c);
        fVar13 = OF(0x90);
        fVar16 = OF(0x84);
        fVar11 = OF(0xa0);
        fVar15 = OF(0x94);
        fVar10 = OF(0x88);
        fVar9 = OF(0xa4);
        fVar12 = OF(0x98);
        fVar17 = OF(0x8c);
        pfVar8 = m + 1;
        iVar7 = 2;
        do {
            PROC_SAMPLE(pfVar8[-1], pfVar8[0], pfVar8[1]);
            PROC_SAMPLE(pfVar8[2], pfVar8[3], pfVar8[4]);
            PROC_SAMPLE(pfVar8[5], pfVar8[6], pfVar8[7]);
            PROC_SAMPLE(pfVar8[8], pfVar8[9], pfVar8[10]);
            pfVar8 += 12;
            iVar7 = iVar7 - 1;
        } while (iVar7 != 0);
        local_fc = pfVar3[0] + local_fc;
        local_f8 = OF(0x2c) + local_f8;
        local_f4 = OF(0x30) + local_f4;
        param_3[0] = local_fc;
        param_3[1] = local_f8;
        param_3[2] = local_f4;
        if (1.5258789e-05f < param_5) {
            fVar9 = param_1[0] - pfVar3[0];
            fVar11 = param_1[2] - OF(0x30);
            fVar16 = param_1[1] - OF(0x2c);
            fVar12 = local_fc - pfVar3[0];
            fVar10 = local_f4 - OF(0x30);
            fVar15 = local_f8 - OF(0x2c);
            fVar19 = 1.0f / sqrtf((fVar16 * fVar16 + (fVar11 * fVar11 + fVar9 * fVar9)) + 1e-08f);
            fVar13 = 1.0f / sqrtf((fVar15 * fVar15 + (fVar10 * fVar10 + fVar12 * fVar12)) + 1e-08f);
            fVar9 = fVar13 * fVar12 + fVar19 * fVar9;
            fVar11 = fVar10 * fVar13 + fVar11 * fVar19;
            fVar13 = fVar15 * fVar13 + fVar16 * fVar19;
            fVar19 = 1.0f / sqrtf((fVar13 * fVar13 + (fVar11 * fVar11 + fVar9 * fVar9)) + 1e-08f);
            param_3[1] = (fVar13 * fVar19) * param_5 + local_f8;
            param_3[2] = (fVar11 * fVar19) * param_5 + local_f4;
            param_3[0] = (fVar19 * fVar9) * param_5 + local_fc;
            return 1;
        }
        break;
    }
    case 2: {
        float* base = (float*)(size_t)OI(0xb8);
        int    cnt  = OI(0xb4);
        fVar19 = OF(0xbc);
        local_f0 = OF(0x48);
        fVar13 = OF(0xc0);
        fVar16 = OF(0xc4);
        local_ec = OF(0x4c);
        local_e8 = OF(0x50);
        local_e4 = -1;
        if (((fVar19 == local_f0) && (fVar13 == local_ec)) && (fVar16 == local_e8)) {
            iVar5 = cnt;
            fVar11 = 3.402823466e+38f;
            iVar7 = 0;
            if (3 < iVar5) {
                pfVar3 = base + 3;
                iVar4 = (iVar5 - 4U >> 2) + 1;
                iVar7 = iVar4 * 4;
                do {
                    fVar15 = ((pfVar3[-3] - fVar19) * (pfVar3[-3] - fVar19) +
                              (pfVar3[-1] - fVar16) * (pfVar3[-1] - fVar16)) +
                             (pfVar3[-2] - fVar13) * (pfVar3[-2] - fVar13);
                    if (fVar15 < fVar11) {
                        local_ec = pfVar3[-2];
                        local_f0 = pfVar3[-3];
                        local_e8 = pfVar3[-1];
                        fVar11 = fVar15;
                    }
                    fVar15 = ((pfVar3[0] - fVar19) * (pfVar3[0] - fVar19) +
                              (pfVar3[2] - fVar16) * (pfVar3[2] - fVar16)) +
                             (pfVar3[1] - fVar13) * (pfVar3[1] - fVar13);
                    if (fVar15 < fVar11) {
                        local_ec = pfVar3[1];
                        local_f0 = pfVar3[0];
                        local_e8 = pfVar3[2];
                        fVar11 = fVar15;
                    }
                    fVar15 = ((pfVar3[3] - fVar19) * (pfVar3[3] - fVar19) +
                              (pfVar3[5] - fVar16) * (pfVar3[5] - fVar16)) +
                             (pfVar3[4] - fVar13) * (pfVar3[4] - fVar13);
                    if (fVar15 < fVar11) {
                        local_ec = pfVar3[4];
                        local_f0 = pfVar3[3];
                        local_e8 = pfVar3[5];
                        fVar11 = fVar15;
                    }
                    fVar15 = ((pfVar3[6] - fVar19) * (pfVar3[6] - fVar19) +
                              (pfVar3[8] - fVar16) * (pfVar3[8] - fVar16)) +
                             (pfVar3[7] - fVar13) * (pfVar3[7] - fVar13);
                    if (fVar15 < fVar11) {
                        local_ec = pfVar3[7];
                        local_f0 = pfVar3[6];
                        local_e8 = pfVar3[8];
                        fVar11 = fVar15;
                    }
                    pfVar3 += 12;
                    iVar4 = iVar4 - 1;
                } while (iVar4 != 0);
            }
            if (iVar7 < iVar5) {
                iVar5 = iVar5 - iVar7;
                pfVar3 = base + iVar7 * 3;
                do {
                    fVar15 = ((pfVar3[0] - fVar19) * (pfVar3[0] - fVar19) +
                              (pfVar3[2] - fVar16) * (pfVar3[2] - fVar16)) +
                             (pfVar3[1] - fVar13) * (pfVar3[1] - fVar13);
                    if (fVar15 < fVar11) {
                        local_ec = pfVar3[1];
                        local_f0 = pfVar3[0];
                        local_e8 = pfVar3[2];
                        fVar11 = fVar15;
                    }
                    pfVar3 += 3;
                    iVar5 = iVar5 - 1;
                } while (iVar5 != 0);
            }
        }
        iVar7 = 0;
        fVar16 = local_f0;
        if (3 < cnt) {
            pfVar3 = base + 3;
            iVar5 = 2;
            pfVar8 = base + 7;
            do {
                if (WTEST1(pfVar3[-3], pfVar3[-2])) {
                    fVar16 = pfVar3[-3];
                    local_ec = pfVar3[-2];
                    local_e8 = pfVar3[-1];
                    local_f0 = fVar16;
                    local_e4 = iVar7;
                }
                if (WTEST1(pfVar3[0], pfVar3[1])) {
                    fVar16 = pfVar3[0];
                    local_ec = pfVar3[1];
                    local_e8 = pfVar3[2];
                    local_e4 = iVar5 - 1;
                    local_f0 = fVar16;
                }
                if (WTEST1(pfVar3[3], pfVar3[4])) {
                    fVar16 = pfVar3[3];
                    local_ec = pfVar3[4];
                    local_e8 = pfVar3[5];
                    local_f0 = fVar16;
                    local_e4 = iVar5;
                }
                if (WTEST1(pfVar3[6], pfVar3[7])) {
                    fVar16 = pfVar3[6];
                    local_ec = pfVar3[7];
                    local_e8 = pfVar3[8];
                    local_e4 = iVar5 + 1;
                    local_f0 = fVar16;
                }
                (void)pfVar8;
                iVar7 = iVar7 + 4;
                pfVar3 += 12;
                pfVar8 += 12;
                iVar5 = iVar5 + 4;
            } while (iVar7 < cnt - 3);
        }
        iVar5 = cnt;
        if (iVar7 < iVar5) {
            pfVar3 = base + iVar7 * 3;
            do {
                if (WTEST1(pfVar3[0], pfVar3[1])) {
                    fVar16 = pfVar3[0];
                    local_ec = pfVar3[1];
                    local_e8 = pfVar3[2];
                    local_e4 = iVar7;
                    local_f0 = fVar16;
                }
                iVar7 = iVar7 + 1;
                pfVar3 += 3;
            } while (iVar7 < iVar5);
        }
        if (local_e4 == -1) {
            local_fc = OF(0xa8);
            local_f8 = OF(0xac);
            iVar7 = 0;
            if (3 < iVar5) {
                pfVar3 = base + 3;
                iVar5 = 2;
                pfVar8 = base + 7;
                do {
                    if (WTEST2(pfVar3[-3], pfVar3[-2])) {
                        local_fc = pfVar3[-3];
                        local_f8 = pfVar3[-2];
                        local_f4 = pfVar3[-1];
                        local_e4 = iVar7;
                    }
                    if (WTEST2(pfVar3[0], pfVar3[1])) {
                        local_fc = pfVar3[0];
                        local_f8 = pfVar3[1];
                        local_f4 = pfVar3[2];
                        local_e4 = iVar5 - 1;
                    }
                    if (WTEST2(pfVar3[3], pfVar3[4])) {
                        local_fc = pfVar3[3];
                        local_f8 = pfVar3[4];
                        local_f4 = pfVar3[5];
                        local_e4 = iVar5;
                    }
                    if (WTEST2(pfVar3[6], pfVar3[7])) {
                        local_fc = pfVar3[6];
                        local_f8 = pfVar3[7];
                        local_f4 = pfVar3[8];
                        local_e4 = iVar5 + 1;
                    }
                    (void)pfVar8;
                    iVar7 = iVar7 + 4;
                    pfVar3 += 12;
                    pfVar8 += 12;
                    iVar5 = iVar5 + 4;
                } while (iVar7 < cnt - 3);
            }
            if (iVar7 < cnt) {
                pfVar3 = base + iVar7 * 3;
                do {
                    if (WTEST2(pfVar3[0], pfVar3[1])) {
                        local_fc = pfVar3[0];
                        local_f8 = pfVar3[1];
                        local_f4 = pfVar3[2];
                        local_e4 = iVar7;
                    }
                    iVar7 = iVar7 + 1;
                    pfVar3 += 3;
                } while (iVar7 < cnt);
            }
            if (local_e4 == -1)
                return 0;
        }
        param_3[0] = fVar16;
        param_3[1] = local_ec;
        param_3[2] = local_e8;
        iVar4 = (local_e4 - 1 + cnt) % cnt;
        local_d0 = 0.0f;
        float* pcur = base + local_e4 * 3;
        pfVar3 = base + iVar4 * 3;
        fVar19 = pcur[0] - pfVar3[0];
        fVar16 = pcur[2] - pfVar3[2];
        fVar13 = pcur[1] - pfVar3[1];
        fVar19 = (fVar19 * fVar19 + fVar16 * fVar16) + fVar13 * fVar13;
        for (; (fVar19 < 1.5258789e-05f && ((int)local_d0 < cnt));
             local_d0 = (float)((int)local_d0 + 1)) {
            iVar4 = (iVar4 - 1 + cnt) % cnt;
            pfVar3 = base + iVar4 * 3;
            fVar19 = pcur[0] - pfVar3[0];
            fVar16 = pcur[2] - pfVar3[2];
            fVar13 = pcur[1] - pfVar3[1];
            fVar19 = (fVar19 * fVar19 + fVar16 * fVar16) + fVar13 * fVar13;
        }
        iVar6 = (local_e4 + 1) % cnt;
        local_d0 = 0.0f;
        pfVar3 = base + iVar6 * 3;
        fVar19 = pcur[0] - pfVar3[0];
        fVar16 = pcur[2] - pfVar3[2];
        fVar13 = pcur[1] - pfVar3[1];
        fVar19 = (fVar19 * fVar19 + fVar16 * fVar16) + fVar13 * fVar13;
        for (; (fVar19 < 1.5258789e-05f && ((int)local_d0 < cnt));
             local_d0 = (float)((int)local_d0 + 1)) {
            iVar6 = (iVar6 + 1) % cnt;
            pfVar3 = base + iVar6 * 3;
            fVar19 = pcur[0] - pfVar3[0];
            fVar16 = pcur[2] - pfVar3[2];
            fVar13 = pcur[1] - pfVar3[1];
            fVar19 = (fVar19 * fVar19 + fVar16 * fVar16) + fVar13 * fVar13;
        }
        fVar19 = pcur[0];
        fVar13 = pcur[1];
        fVar16 = pcur[2];
        local_bc = OF(0x54);
        pfVar3 = pcur;
        float* pa = base + iVar4 * 3;
        fVar11 = pa[0];
        local_d4 = pa[1];
        local_b0 = pa[2];
        float* pb = base + iVar6 * 3;
        local_c0 = pb[1];
        local_ac = pb[0];
        local_d0 = pb[2];
        local_b4 = local_ac - fVar19;
        fVar15 = local_bc + param_5;
        if ((local_b4 * (fVar11 - fVar19) + (local_d0 - fVar16) * (local_b0 - fVar16)) +
                (local_c0 - fVar13) * (local_d4 - fVar13) <= 0.0f) {
            fVar13 = pcur[1] - local_d4;
            local_b0 = pcur[2] - local_b0;
            fVar10 = fVar13 * DAT_0167ae80 - local_b0 * DAT_0167ae7c;
            fVar13 = (fVar19 - fVar11) * DAT_0167ae7c - fVar13 * DAT_0167ae78;
            fVar9 = local_b0 * DAT_0167ae78 - (fVar19 - fVar11) * DAT_0167ae80;
            fVar13 = 1.0f / sqrtf((fVar9 * fVar9 + (fVar13 * fVar13 + fVar10 * fVar10)) + 1e-08f);
            local_d0 = local_d0 - pcur[2];
            fVar16 = local_c0 - pcur[1];
            fVar17 = fVar16 * DAT_0167ae80 - local_d0 * DAT_0167ae7c;
            fVar16 = local_b4 * DAT_0167ae7c - fVar16 * DAT_0167ae78;
            fVar12 = local_d0 * DAT_0167ae78 - local_b4 * DAT_0167ae80;
            fVar16 = 1.0f / sqrtf((fVar12 * fVar12 + (fVar16 * fVar16 + fVar17 * fVar17)) + 1e-08f);
            fVar18 = fVar15 * (fVar13 * fVar10);
            fVar10 = (fVar16 * fVar17) * fVar15;
            fVar17 = (fVar9 * fVar13) * fVar15;
            fVar15 = (fVar12 * fVar16) * fVar15;
            fVar20 = fVar10 + fVar19;
            fVar12 = fVar15 + pcur[1];
            fVar9 = fVar17 + pcur[1];
            fVar15 = (fVar15 + local_c0) - fVar12;
            fVar13 = (fVar10 + local_ac) - fVar20;
            fVar11 = fVar18 + fVar11;
            fVar10 = (fVar18 + fVar19) - fVar11;
            local_d4 = fVar17 + local_d4;
            fVar21 = fVar9 - local_d4;
            fVar16 = fVar10 * fVar15 - fVar21 * fVar13;
            fVar12 = local_d4 - fVar12;
            fVar20 = fVar11 - fVar20;
            fVar13 = fVar12 * fVar13 - fVar20 * fVar15;
            if (fVar16 <= 1.5258789e-05f) {
                if ((fVar13 == 0.0f) && (fVar12 * fVar10 - fVar20 * fVar21 == 0.0f))
                    return 0;
                param_3[0] = (fVar18 + fVar19) + fVar18;
                param_3[1] = fVar9 + fVar17;
                param_3[2] = 0.0f;
            } else {
                fVar13 = (1.0f / fVar16) * fVar13;
                param_3[0] = fVar13 * fVar10 + fVar11;
                param_3[1] = fVar13 * fVar21 + local_d4;
                param_3[2] = 0.0f;
            }
        } else {
            local_d8 = param_1[2] - OF(0x7c);
            fVar19 = param_1[0] - OF(0x74);
            fVar13 = param_1[1] - OF(0x78);
            if (OF(0x80) != 1.0f) {
                fVar16 = 1.0f / OF(0x80);
                fVar19 = fVar16 * fVar19;
                fVar13 = fVar13 * fVar16;
                local_d8 = local_d8 * fVar16;
            }
            local_e0 = fVar19;
            local_dc = fVar13;
            if ((OB(0x70) & 2) != 0) {
                local_e0 = (OF(0x8c) * local_d8 + OF(0x88) * fVar13) + fVar19 * OF(0x84);
                local_dc = (OF(0x98) * local_d8 + OF(0x94) * fVar13) + OF(0x90) * fVar19;
                local_d8 = (OF(0xa4) * local_d8 + OF(0xa0) * fVar13) + OF(0x9c) * fVar19;
            }
            fVar19 = pcur[0] - local_e0;
            local_104 = pcur[1] - local_dc;
            local_100 = pcur[2] - local_d8;
            local_108 = 1.0f / sqrtf((fVar19 * fVar19 +
                                      (local_104 * local_104 + local_100 * local_100)) + 1e-08f);
            local_100 = local_100 * local_108;
            local_104 = local_104 * local_108;
            local_108 = local_108 * fVar19;
            local_f0 = (local_104 * DAT_0167ae80 - local_100 * DAT_0167ae7c) * param_4;
            local_ec = (local_100 * DAT_0167ae78 - local_108 * DAT_0167ae80) * param_4;
            local_e8 = (local_108 * DAT_0167ae7c - local_104 * DAT_0167ae78) * param_4;
            pfVar8 = FUN_00699800(local_90, pcur, local_bc, &local_e0, &local_f0);
            param_3[0] = pfVar8[0];
            param_3[1] = pfVar8[1];
            param_3[2] = pfVar8[2];
            if (((param_3[0] == DAT_0167ae24) && (param_3[1] == DAT_0167ae28)) &&
                (param_3[2] == DAT_0167ae2c)) {
                fVar19 = OF(0x54) * param_5;
                fVar13 = pcur[0] - local_108 * fVar19;
                fVar16 = pcur[1] - local_104 * fVar19;
                fVar19 = pcur[2] - local_100 * fVar19;
                param_3[0] = fVar13;
                param_3[1] = fVar16;
                param_3[2] = fVar19;
                if (((fVar13 == DAT_0167ae24) && (fVar16 == DAT_0167ae28)) &&
                    (fVar19 == DAT_0167ae2c))
                    return 0;
            }
            if (((param_3[0] - local_e0) * (param_3[0] - local_e0) +
                 (param_3[2] - local_d8) * (param_3[2] - local_d8)) +
                    (param_3[1] - local_dc) * (param_3[1] - local_dc) < 1.5258789e-05f) {
                fVar19 = OF(0x54);
                param_3[0] = local_f0 * fVar19 + local_e0;
                param_3[1] = local_ec * fVar19 + local_dc;
                param_3[2] = local_e8 * fVar19 + local_d8;
            }
            if (1.5258789e-05f < param_5) {
                fVar11 = param_3[2] - pcur[2];
                fVar13 = param_3[0] - pcur[0];
                fVar16 = param_3[1] - pcur[1];
                fVar19 = 1.0f / sqrtf((fVar16 * fVar16 + (fVar11 * fVar11 + fVar13 * fVar13)) + 1e-08f);
                param_3[0] = (fVar19 * fVar13) * param_5 + param_3[0];
                param_3[1] = (fVar19 * fVar16) * param_5 + param_3[1];
                param_3[2] = (fVar19 * fVar11) * param_5 + param_3[2];
            }
            fVar13 = param_2[2] - OF(0x7c);
            fVar19 = param_2[0] - OF(0x74);
            local_c8 = param_2[1] - OF(0x78);
            if (OF(0x80) != 1.0f) {
                fVar16 = 1.0f / OF(0x80);
                fVar19 = fVar16 * fVar19;
                local_c8 = fVar16 * local_c8;
                fVar13 = fVar16 * fVar13;
            }
            local_cc = fVar19;
            if ((OB(0x70) & 2) != 0) {
                local_cc = (OF(0x8c) * fVar13 + OF(0x88) * local_c8) + fVar19 * OF(0x84);
                local_c8 = (OF(0x98) * fVar13 + OF(0x94) * local_c8) + fVar19 * OF(0x90);
            }
            local_108 = pcur[0] - local_cc;
            local_104 = pcur[1] - local_c8;
            local_100 = pcur[2];
            param_4 = -param_4;
            local_c4 = 0;
            fVar19 = 1.0f / sqrtf((local_108 * local_108 +
                                   (local_104 * local_104 + local_100 * local_100)) + 1e-08f);
            local_f0 = param_4 * ((local_104 * fVar19) * DAT_0167ae80 -
                                  (local_100 * fVar19) * DAT_0167ae7c);
            local_ec = ((local_100 * fVar19) * DAT_0167ae78 -
                        DAT_0167ae80 * (fVar19 * local_108)) * param_4;
            local_e8 = (DAT_0167ae7c * (fVar19 * local_108) -
                        (local_104 * fVar19) * DAT_0167ae78) * param_4;
            pfVar3 = FUN_00699800(local_78, pcur, OF(0x54), &local_cc, &local_f0);
            if (((pfVar3[0] != DAT_0167ae24) || (pfVar3[1] != DAT_0167ae28)) ||
                (pfVar3[2] != DAT_0167ae2c)) {
                fVar19 = param_3[0];
                fVar10 = fVar19 - pfVar3[0];
                fVar13 = param_3[1];
                fVar11 = fVar13 - pfVar3[1];
                fVar16 = param_3[2];
                fVar15 = fVar16 - pfVar3[2];
                local_e0 = fVar19 - local_e0;
                local_d8 = fVar16 - local_d8;
                local_dc = fVar13 - local_dc;
                fVar11 = sqrtf(fVar10 * fVar10 + (fVar11 * fVar11 + fVar15 * fVar15)) * 0.5f;
                fVar15 = 1.0f / sqrtf((local_dc * local_dc +
                                       (local_d8 * local_d8 + local_e0 * local_e0)) + 1e-08f);
                param_3[0] = fVar19 + fVar11 * (fVar15 * local_e0);
                param_3[1] = (local_dc * fVar15) * fVar11 + fVar13;
                param_3[2] = (local_d8 * fVar15) * fVar11 + fVar16;
            }
        }
        if ((OB(0x70) & 2) != 0) {
            fVar19 = param_3[2];
            fVar13 = param_3[1];
            fVar16 = param_3[0];
            fVar11 = OF(0x94);
            fVar15 = OF(0xa0);
            fVar10 = OF(0x88);
            fVar9 = OF(0xa4);
            fVar12 = OF(0x98);
            fVar17 = OF(0x8c);
            param_3[0] = (OF(0x9c) * fVar19 + OF(0x90) * fVar13) + fVar16 * OF(0x84);
            param_3[1] = (fVar15 * fVar19 + fVar11 * fVar13) + fVar10 * fVar16;
            param_3[2] = (fVar9 * fVar19 + fVar12 * fVar13) + fVar17 * fVar16;
        }
        fVar19 = OF(0x80);
        fVar13 = param_3[1];
        fVar16 = param_3[2];
        param_3[0] = fVar19 * param_3[0];
        param_3[1] = fVar19 * fVar13;
        param_3[2] = fVar19 * fVar16;
        fVar11 = OF(0x78);
        fVar15 = OF(0x7c);
        param_3[0] = OF(0x74) + param_3[0];
        param_3[1] = fVar11 + fVar19 * fVar13;
        param_3[2] = fVar15 + fVar19 * fVar16;
        return 1;
    }
    case 3: {
        if (param_4 <= 0.0f) {
            fVar19 = OF(0xd8);
            fVar13 = OF(0xdc);
            fVar16 = OF(0xe0);
        } else {
            fVar19 = OF(0xcc);
            fVar13 = OF(0xd0);
            fVar16 = OF(0xd4);
        }
        fVar19 = fVar19 - OF(0x48);
        fVar16 = fVar16 - OF(0x50);
        fVar13 = fVar13 - OF(0x4c);
        fVar11 = sqrtf(fVar13 * fVar13 + (fVar16 * fVar16 + fVar19 * fVar19));
        fVar10 = 1.0f / (fVar11 + 1.5258789e-05f);
        param_5 = (OF(0x54) + fVar11) + param_5;
        fVar11 = OF(0x48);
        fVar15 = OF(0x50);
        param_3[1] = OF(0x4c) + (fVar13 * fVar10) * param_5;
        param_3[2] = fVar15 + (fVar16 * fVar10) * param_5;
        param_3[0] = (fVar10 * fVar19) * param_5 + fVar11;
        break;
    }
    }
    return 1;
}

// @ 0x00af3e00
cRayQueryBase& cRayQueryBase::Assign(const cRayQueryBase& src)
{
  AssignBase(src);
  mValue = src.mValue;
  mPoint = src.mPoint;
  return *this;
}

// @ 0x00af3e50
bool FUN_00af3e50(const Vec3* origin, const Vec3* dir, float t0, float unused, float minHeight, float waterBias, void* ctx, float* tMax, bool noWaterHit)
{
  if (1.52587890625e-05f > *tMax) return false;
  bool found = false;
  cPlanetModel* pm = SP_PlanetModel();
  float water = pm->GetWaterHeight();
  TerrainMap* map = pm->mpISphere->GetMap();
  uint16_t* heights = map->height->data;
  int dim = map->color->dim;
  uint32_t* colors = map->color->data;
  int dimSq = dim * dim;
  float radius0 = map->radius;
  float hscale = map->heightScale;
  if (*tMax > radius0 * 2.0f) return false;
  float fdim = (float)dim;
  float cellLen = pm->GetRadiusAt(origin) * (1.0f / fdim);
  float waterTop = water + waterBias;
  float a = map->minAlpha > minHeight ? map->minAlpha : minHeight;
  float b = hscale > 1.0f ? hscale : 1.0f;
  float alphaThr = a / b;
  float t = cellLen + t0;
  if (!(*tMax > t)) return found;
  float half = fdim * 0.5f;
  for (;;) {
    Vec3 p;
    p.x = dir->x * t + origin->x;
    p.y = dir->y * t + origin->y;
    p.z = dir->z * t + origin->z;
    int idx = CubeIndex(p.x, p.y, p.z, dim, dimSq, half);
    float H = (float)((int)heights[idx] - 0x8000) * hscale * 3.0518509447574615e-05f + radius0;
    float alpha = (float)(colors[idx] >> 24) * 0.003921568859368563f;
    bool hit;
    if (alpha > alphaThr && H > waterTop) {
      uint32_t c = colors[idx];
      float nx = (float)(c & 0xff) * 0.007843137718737125f - 1.0f;
      float ny = (float)((c >> 8) & 0xff) * 0.007843137718737125f - 1.0f;
      float nz = (float)((c >> 16) & 0xff) * 0.007843137718737125f - 1.0f;
      float inv = 1.0f / sqrtf(p.x * p.x + p.y * p.y + p.z * p.z);
      float ux = inv * p.x, uy = p.y * inv, uz = p.z * inv;
      // w = n x up, v = w x n
      float w0 = uz * ny - uy * nz;
      float w1 = nz * ux - uz * nx;
      float w2 = uy * nx - ny * ux;
      float v0 = w1 * nz - w2 * ny;
      float v1 = w2 * nx - w0 * nz;
      float v2 = w0 * ny - w1 * nx;
      hit = true;
      float vUp = v2 * uz + v1 * uy + v0 * ux;
      if (0.69f > vUp) {
        float vDir = v0 * dir->x + v2 * dir->z + v1 * dir->y;
        hit = vDir > 0.3f ? hit : false;
      }
    } else {
      hit = false;
    }
    bool refine;
    if (!pm->mbF0 && water >= H) {
      refine = !noWaterHit;
    } else {
      refine = hit;
    }
    if (refine) {
      found = true;
      float m = (t < 2.0f) ? t : 2.0f;
      Vec3 back;
      back.x = p.x - dir->x * m;
      back.y = p.y - dir->y * m;
      back.z = p.z - dir->z * m;
      Vec3 out;
      pm->ToSurface(&out, &back);
      float inv = 1.0f / sqrtf(p.x * p.x + p.z * p.z + p.y * p.y + 9.99999993922529e-09f);
      float ux = inv * p.x, uy = p.y * inv, uz = p.z * inv;
      float dx = dir->x, dy = dir->y, dz = dir->z;
      float q0 = dz * uy - dy * uz;
      float q1 = dx * uz - dz * ux;
      float q2 = dy * ux - dx * uy;
      ProbeRay probe[3];
      probe[0].dir.x = -q0; probe[0].dir.y = -q1; probe[0].dir.z = -q2;
      probe[1].dir.x = q0; probe[1].dir.y = q1; probe[1].dir.z = q2;
      probe[2].dir.x = dx; probe[2].dir.y = dy; probe[2].dir.z = dz;
      probe[0].t = cellLen;
      probe[1].t = cellLen;
      probe[2].t = cellLen;
      for (int i = 0; i < 3; i++) {
        ProbeRay& pr = probe[i];
        while (50.0f > pr.t) {
          Vec3 s;
          s.x = out.x + pr.t * pr.dir.x;
          s.y = out.y + pr.t * pr.dir.y;
          s.z = out.z + pr.t * pr.dir.z;
          int j = CubeIndex(s.x, s.y, s.z, dim, dimSq, half);
          float h2 = (float)((int)heights[j] - 0x8000) * hscale * 3.0518509447574615e-05f + radius0;
          float a2 = (float)(colors[j] >> 24) * 0.003921568859368563f;
          bool above = (a2 > alphaThr && h2 > waterTop);
          if (h2 < water || above) {
            pr.t = pr.t + cellLen;
          } else {
            break;
          }
        }
        Vec3 pp;
        pp.x = pr.t * pr.dir.x + out.x;
        pp.y = pr.dir.y * pr.t + out.y;
        pp.z = pr.dir.z * pr.t + out.z;
        Vec3 tmp;
        pr.start = *pm->ToSurface(&tmp, &pp);
      }
      FUN_00af1610(ctx, pm, &out, &out, &probe[1].start, &probe[0].start, &probe[2].start, t0);
      return found;
    }
    t = t + cellLen;
    if (!(*tMax > t)) break;
  }
  return found;
}

// @ 0x00af4870
bool FUN_00af4870(const Vec3* origin, const Vec3* dir, float t0, float step, void* ctx, float* tMax)
{
  if (1.52587890625e-05f > *tMax) return false;
  bool found = false;
  cPlanetModel* pm = SP_PlanetModel();
  float water = pm->GetWaterHeight();
  TerrainMap* map = pm->mpISphere->GetMap();
  uint16_t* heights = map->height->data;
  int dim = map->color->dim;
  float hscale = map->heightScale;
  float radius0 = map->radius;
  int dimSq = dim * dim;
  float t = t0 + step;
  if (!(*tMax > t)) return found;
  float half = (float)dim * 0.5f;
  for (;;) {
    float px = origin->x + dir->x * t;
    float py = origin->y + dir->y * t;
    float pz = origin->z + dir->z * t;
    int idx = CubeIndex(px, py, pz, dim, dimSq, half);
    float H = (float)((int)heights[idx] - 0x8000) * hscale * 3.0518509447574615e-05f + radius0;
    if (H > water) {
      found = true;
      float s = step;
      if (*tMax > t + s) {
        for (;;) {
          float qx = origin->x + dir->x * (t + s);
          float qy = origin->y + dir->y * (t + s);
          float qz = origin->z + dir->z * (t + s);
          int j = CubeIndex(qx, qy, qz, dim, dimSq, half);
          float h2 = (float)((int)heights[j] - 0x8000) * hscale * 3.0518509447574615e-05f + radius0;
          if (water > h2) break;
          s = s + step;
          if (!(*tMax > s + t)) break;
        }
      }
      float hs = s * 0.5f;
      Vec3 mid;
      mid.x = origin->x + dir->x * (hs + t);
      mid.y = origin->y + dir->y * (hs + t);
      mid.z = origin->z + dir->z * (hs + t);
      FUN_00af1570(ctx, pm, &mid, &mid, hs, 0, 0);
      *tMax = t;
      return found;
    }
    t = t + step;
    if (!(*tMax > t)) break;
  }
  return found;
}

// @ 0x00af4da0
SPShape* __thiscall SPShape::InitDefault()
{
    SPShape* self = this;
    self->radiusA = 0.0f;
    self->kind   = 0;
    self->type   = 0;
    self->flag40 = 0;
    f32 vhi = DAT_0145c3e0;
    f32 tv[3] = { vhi, vhi, vhi };
    memcpy(&self->lo, tv, sizeof(tv));
    f32 vlo = DAT_013f51ac;
    f32 tw[3] = { vlo, vlo, vlo };
    memcpy(&self->hi, tw, sizeof(tw));
    self->xf.flags2 = 0;
    self->xf.flags0 = 0;
    self->xf.origin.x = DAT_0167ae24;
    self->xf.origin.y = DAT_0167ae28;
    self->xf.origin.z = DAT_0167ae2c;
    self->xf.scale = DAT_01485720;
    self->xf.basis.Assign(DAT_0167ae54);
    memset(&self->orient, 0, sizeof(self->orient));
    return self;
}

// @ 0x00af4ea0
extern "C" void __cdecl FUN_00af4ea0(SPShape* self, int kind, const Vec3_s00af_4da0* a, const Vec3_s00af_4da0* b, const void* xform, const f32* src6, u8 flag, const Orientation* orient)
{
    self->kind  = kind;
    self->type  = 1;
    self->pos   = *a;
    self->halfExt = *b;
    self->xf.Assign(xform);
    const Vec3_s00af_4da0* p6 = (const Vec3_s00af_4da0*)src6;
    self->hi = p6[1];
    self->lo = p6[0];
    self->flag40 = flag;
    self->worldPos = DAT_0167ae24_v;
    if (orient) {
        self->orient = *orient;
        return;
    }
    memset(&self->orient, 0, sizeof(self->orient));
}

// @ 0x00af4f70
extern "C" void __cdecl FUN_00af4f70(SPShape* self, int kind, const Vec3_s00af_4da0* a, const Vec3_s00af_4da0* b, f32 f54, const void* xform, const Vec3_s00af_4da0* n, f32 f_c8, int b4, int b8, u8 flag, const Orientation* orient)
{
    self->kind  = kind;
    self->type  = 2;
    self->pos   = *a;
    self->halfExt = *b;
    self->xf.Assign(xform);
    self->extra54 = f54;
    self->normal = *n;
    self->depth = f_c8;
    self->fieldB8 = b4;
    self->fieldB4 = b8;
    self->flag40 = flag;
    self->worldPos = DAT_0167ae24_v;
    if (orient != 0) {
        self->orient = *orient;
        return;
    }
    memset(&self->orient, 0, sizeof(self->orient));
}

// @ 0x00af5060
extern "C" u8 __cdecl FUN_00af5060(SPShape* obj, int kind, const Vec3_s00af_4da0* start, const Vec3_s00af_4da0* arg4, const Vec3_s00af_4da0* dir, f32* out, f32 radius, const SPBox* box, const f32* boxF, int p10, int p11)
{
    f32 invScale;
    Vec3_s00af_4da0 p0, p1;
    f32 t;

    f32 s = *out;
    f32 dx = dir->x * s;
    f32 dy = dir->y * s;
    f32 dz = dir->z * s;

    f32 sw = box->scale;
    f32 ex, ey, ez;
    f32 px = start->x - box->center.x;
    f32 py = start->y - box->center.y;
    f32 pz = start->z - box->center.z;
    if (sw != 1.0f) {
        invScale = 1.0f / sw;
        px *= invScale;
        py *= invScale;
        pz *= invScale;
    }
    ex = start->x + dx;
    ey = start->y + dy;
    ez = start->z + dz;

    p0.x = px; p0.y = py; p0.z = pz;
    if ((box->flags & 2) != 0) {
        p0.x = box->basis.m[2] * pz + box->basis.m[1] * py + box->basis.m[0] * px;
        p0.y = box->basis.m[5] * pz + box->basis.m[4] * py + box->basis.m[3] * px;
        p0.z = box->basis.m[8] * pz + box->basis.m[7] * py + box->basis.m[6] * px;
    }

    f32 qx = ex - box->center.x;
    f32 qy = ey - box->center.y;
    f32 qz = ez - box->center.z;
    if (sw != 1.0f) {
        invScale = 1.0f / sw;
        qx *= invScale;
        qy *= invScale;
        qz *= invScale;
    }
    p1.x = qx; p1.y = qy; p1.z = qz;
    if ((box->flags & 2) != 0) {
        p1.x = box->basis.m[2] * qz + box->basis.m[1] * qy + box->basis.m[0] * qx;
        p1.y = box->basis.m[5] * qz + box->basis.m[4] * qy + box->basis.m[3] * qx;
        p1.z = box->basis.m[8] * qz + box->basis.m[7] * qy + box->basis.m[6] * qx;
    }

    if (!FUN_006989d0(&p0.x, &p1.x, boxF, &t))
        return 0;

    f32 vz = p1.z - p0.z;
    f32 vy = p1.y - p0.y;
    f32 vx = p1.x - p0.x;
    f32 dist = (*out * t) * radius;
    *out = dist;
    f32 sum = vx * vx + (vy * vy + vz * vz);
    f32 invlen = 1.0f / (f32)sqrt((double)sum);
    Vec3_s00af_4da0 contact;
    contact.x = dist * (vx * invlen) + p0.x;
    contact.y = dist * (vy * invlen) + p0.y;
    contact.z = dist * (vz * invlen) + p0.z;
    FUN_00af4ea0(obj, kind, arg4, &contact, box, boxF, (u8)p10, (const Orientation*)p11);
    return 1;
}

// @ 0x00af5400
extern "C" u32 __cdecl FUN_00af5400(SPShape* obj, int kind, const Vec3_s00af_4da0* p3, const Vec3_s00af_4da0* p4, const Vec3_s00af_4da0* p5, const Vec3_s00af_4da0* p6, f32* p7, f32 p8, cSPTransform_s00af_4da0* xform, const Vec3_s00af_4da0* p10, f32 p11, const Vec3_s00af_4da0* poly, int npoly, f32 p14, int p15, const Orientation* p16)
{
    f32 l70, l6c, l68, l64, l60, l5c, l58, l54, l50, l4c, l48, l44, l40, l3c, l38, l34, l30;
    f32 outB;
    f32 l20[7];

    f32 fVar9 = *p7;
    f32 l28 = p6->y * fVar9;
    l60 = p3->z;
    l64 = p3->y;
    l68 = p3->x;
    f32 fVar6 = l68 - p4->x;
    f32 fVar8 = l60 - p4->z;
    f32 fVar7 = l64 - p4->y;
    l70 = (fVar6 * (fVar9 * p6->x) + fVar8 * (p6->z * fVar9)) + fVar7 * l28;
    fVar6 = ((fVar6 * fVar6 + fVar8 * fVar8) + fVar7 * fVar7) - (p11 + p14) * (p11 + p14);
    l6c = l70 * l70 - fVar6 * (fVar9 * fVar9);
    if (fVar6 >= 0.0f) {
        if (l6c < 0.0f)
            return 0;
        l6c = (f32)sqrt((double)l6c);
        if (l6c - l70 < 0.0f)
            return 0;
        if (fVar9 * fVar9 < -l70 - l6c)
            return 0;
    }
    l5c = p5->x;
    l58 = p5->y;
    l54 = p5->z;
    l50 = l68;
    l4c = l64;
    l48 = l60;
    xform->BackTransformPoint(&l50);
    xform->BackTransformPoint(&l5c);
    l64 = l5c - l50;
    l68 = l58 - l4c;
    l70 = l68 * l68 + l64 * l64;
    l48 = 0.0f;
    l54 = 0.0f;
    fVar9 = 1.0f / (f32)sqrt((double)(l70 + 1e-08f));
    l60  = (l68 * fVar9) * DAT_0167ae80_s00af_4da0;
    l44  = l60 - (fVar9 * 0.0f) * DAT_0167ae7c_s00af_4da0;
    l3c  = (fVar9 * l64) * DAT_0167ae7c_s00af_4da0 - (l68 * fVar9) * DAT_0167ae78_s00af_4da0;
    l40  = (fVar9 * 0.0f) * DAT_0167ae78_s00af_4da0 - (fVar9 * l64) * DAT_0167ae80_s00af_4da0;
    fVar9 = (p10->y - l4c) * l64 - (p10->x - l50) * l68;
    if (fVar9 <= 0.0f) {
        if (fVar9 >= 0.0f)
            goto LAB_5895;
        l38 = -l50;
        fVar9 = -l4c;
        l34 = fVar9;
        fVar6 = fVar9 * l68 + l38 * l64;
        if (fVar6 > 0.0f) {
            if (fVar6 < l70) {
                fVar6 = fVar6 / l70;
                l30 = -(fVar6 * 0.0f);
                l34 = -(l68 * fVar6 + l4c);
                fVar9 = -(l64 * fVar6 + l50);
                l38 = fVar9;
                fVar6 = l34 * l34 + l30 * l30;
            } else {
                fVar9 = -l58;
                fVar6 = -l5c * -l5c;
            }
        } else {
            fVar6 = l38 * l38;
        }
        l70 = (f32)sqrt((double)(fVar9 * fVar9 + fVar6));
        if (p14 <= l70)
            l70 = p14;
        fVar9 = l70;
    } else {
        fVar9 = -l50;
        l34 = -l4c;
        l38 = fVar9;
        fVar6 = l34 * l68 + fVar9 * l64;
        if (fVar6 > 0.0f) {
            if (fVar6 < l70) {
                fVar6 = fVar6 / l70;
                l38 = -(l64 * fVar6 + l50);
                l30 = -(fVar6 * 0.0f);
                fVar9 = -(l68 * fVar6 + l4c);
                l34 = fVar9;
                fVar6 = l30 * l30 + l38 * l38;
                goto LAB_572f;
            }
            fVar9 = -l58 * -l58;
            fVar6 = -l5c * -l5c;
        } else {
            fVar6 = l34 * l34;
LAB_572f:
            fVar9 = fVar9 * fVar9;
        }
        l70 = (f32)sqrt((double)(fVar9 + fVar6));
        if (p14 <= (f32)sqrt((double)(fVar9 + fVar6)))
            l70 = p14;
        fVar9 = -l70;
    }
    l44 = l44 * fVar9;
    l48 = l3c * fVar9;
    l40 = l40 * fVar9;
    l5c = l44 + l5c;
    l50 = l44 + l50;
    l58 = l40 + l58;
    l4c = l40 + l4c;
    l3c = l48;

LAB_5895:
    l54 = l48;
    if (FUN_0069a240(&l50, &l5c, &poly->x, npoly, &l38, &outB)) {
        obj->contact.x = l50;
        obj->contact.y = l4c;
        obj->contact.z = l48;
        if (obj->contact.x == l38 && obj->contact.y == l34 && obj->contact.z == l30) {
            obj->contact.x = obj->contact.x - l44;
            obj->contact.y = obj->contact.y - l40;
            obj->contact.z = obj->contact.z - l3c;
        }
        fVar9 = (f32)sqrt((double)(((l30 - l48) * (l30 - l48) +
                                    (l34 - l4c) * (l34 - l4c)) +
                                    (l38 - l50) * (l38 - l50))) - p14;
        f32 l20v = 0.0f;
        if (fVar9 >= 0.0f)
            l20v = fVar9;
        *p7 = l20v * p8;
        FUN_00af4f70(obj, kind, p4, (const Vec3_s00af_4da0*)&l38, p14, xform, p10, p11, (int)poly, npoly,
                     (u8)p15, p16);
        return 1;
    }
    l5c = p5->x;
    l58 = p5->y;
    l54 = p5->z;
    xform->BackTransformPoint(&l5c);
    l54 = 0.0f;
    l44 = poly->x;
    l40 = poly->y;
    l3c = poly->z;
    int iVar3 = 1;
    l6c = 0.0f;
    l70 = p14;
    const Vec3_s00af_4da0* pfVar2 = poly;
    if (1 < npoly) {
        do {
            const Vec3_s00af_4da0* pfVar4 = pfVar2 + 1;
            f32 fVar5 = FUN_00698b30(&l5c, &l44, &pfVar4->x);
            l60 = fVar5;
            if (fVar5 < l70) {
                l70 = l60;
                l6c = (f32)iVar3;
            }
            l44 = pfVar4->x;
            l40 = pfVar2[1].y;
            l3c = pfVar2[1].z;
            iVar3 = iVar3 + 1;
            pfVar2 = pfVar4;
        } while (iVar3 < npoly);
        if (l6c != 0.0f) {
            obj->contact.x = l50;
            obj->contact.y = l4c;
            obj->contact.z = l48;
            FUN_00698e00(l20, &l5c, &poly[(int)l6c - 1].x, &poly[(int)l6c].x);
            FUN_00af4f70(obj, kind, p4, (const Vec3_s00af_4da0*)l20, p14, xform, p10, p11, (int)poly, npoly,
                         (u8)p15, p16);
            return 1;
        }
    }
    return 0;
}

// @ 0x00af5b40
bool ProbeShape(Shape* s, const Vec3* q, Vec3* p, bool push, char* moved, float margin)
{
    bool result = false;
    switch (s->type) {
    case 0: {
        float dx = s->center.x - p->x;
        float dy = s->center.y - p->y;
        float dz = s->center.z - p->z;
        if (s->radius * s->radius <= (dx * dx + dy * dy) + dz * dz)
            return false;
        result = true;
        if (push) {
            Vec3 d, n;
            if (Vector3_NotEqual(p, &s->center)) {
                d.x = p->x - s->center.x;
                d.y = p->y - s->center.y;
                d.z = p->z - s->center.z;
                normalized_safe(&n, &d);
                float k = s->radius + margin;
                p->x = s->center.x + n.x * k;
                p->y = s->center.y + n.y * k;
                p->z = s->center.z + n.z * k;
                *moved = 1;
            }
            if (Vector3_NotEqual(q, &s->center)) {
                d.x = q->x - s->center.x;
                d.y = q->y - s->center.y;
                d.z = q->z - s->center.z;
                normalized_safe(&n, &d);
                float k = s->radius + margin;
                p->x = s->center.x + n.x * k;
                p->y = s->center.y + n.y * k;
                p->z = s->center.z + n.z * k;
                *moved = 1;
            }
        }
        return result;
    }
    case 1: {
        Vec3 t = *p;
        s->xform.BackTransformPoint(&t);
        if (p->x < s->boxMin.x) return false;
        if (s->boxMax.x < p->x) return false;
        if (p->y < s->boxMin.y) return false;
        if (s->boxMax.y < p->y) return false;
        if (p->z < s->boxMin.z) return false;
        if (s->boxMax.z < p->z) return false;
        result = true;
        if (push) *moved = 0;
        return result;
    }
    case 2: {
        Vec3 w = *p;
        float r = s->extraRadius + s->radius;
        float dx = s->center.x - w.x;
        float dz = s->center.z - w.z;
        float dy = s->center.y - w.y;
        if ((dx * dx + dz * dz) + dy * dy > r * r)
            return false;
        s->xform.BackTransformPoint(&w);
        w.z = 0.0f;
        float best = FLT_MAX;
        int bestIdx = 0;
        Vec3 prev = s->verts[0];
        int n = s->vertCount;
        for (int i = 1; i < n; ++i) {
            const Vec3* cur = (const Vec3*)((char*)s->verts + i * 12);
            float d = SegmentDistance(&w, &prev, cur);
            if (d < best) {
                best = d;
                bestIdx = i;
            }
            prev = *cur;
        }
        if (s->radius <= best && !PointInsidePolygon(s->verts, s->vertCount, &w))
            return false;
        result = true;
        if (push && bestIdx != 0) {
            Vec3 c;
            const Vec3* v = s->verts + bestIdx;
            ClosestOnSegment(&c, &w, v - 1, v);
            float dEnd = Sq(s->pathRef.x - c.x) + Sq(s->pathRef.z - c.z) + Sq(s->pathRef.y - c.y);
            float dPt = Sq(s->pathRef.x - w.x) + Sq(s->pathRef.z - w.z) + Sq(s->pathRef.y - w.y);
            Vec3 dir, nrm;
            if (dEnd > dPt) {
                dir.x = w.x - c.x;
                dir.y = w.y - c.y;
                dir.z = w.z - c.z;
            } else {
                dir.x = c.x - w.x;
                dir.y = c.y - w.y;
                dir.z = c.z - w.z;
            }
            dir = *normalized_safe(&nrm, &dir);
            float k = s->radius + margin;
            p->x = dir.x * k + c.x;
            p->y = dir.y * k + c.y;
            p->z = dir.z * k + c.z;
            s->xform.TransformPoint(p);
            *moved = 1;
        }
        return result;
    }
    case 3: {
        float ax = q->x, ay = q->y, az = q->z;
        float t1 = ((p->x - ax) * (p->x - ax) + (p->z - az) * (p->z - az)) + (p->y - ay) * (p->y - ay);
        float s1 = (Sq(s->innerPt.x - ax) + Sq(s->innerPt.z - az)) + Sq(s->innerPt.y - ay);
        if (t1 <= s1)
            return false;
        float s2 = (Sq(s->outerPt.x - ax) + Sq(s->outerPt.z - az)) + Sq(s->outerPt.y - ay);
        if (s2 <= t1)
            return false;
        result = true;
        if (push) *moved = 0;
        return result;
    }
    }
    return result;
}

// @ 0x00af6250
ShapeCopy& ShapeCopy::operator=(const ShapeCopy& other)
{
    ShapeCopy* dst = this;
    const ShapeCopy* src = &other;

    memcpy(dst->m_head, src->m_head, sizeof(dst->m_head));

    dst->m_field20 = src->m_field20;
    dst->m_field24 = src->m_field24;
    dst->m_field28 = src->m_field28;
    dst->m_field2c = src->m_field2c;
    dst->m_field30 = src->m_field30;
    dst->m_field34 = src->m_field34;
    dst->m_field38 = src->m_field38;
    dst->m_field3c = src->m_field3c;
    dst->m_field40 = src->m_field40;
    dst->m_field44 = src->m_field44;
    dst->m_inner0 = src->m_inner0;
    dst->m_inner1 = src->m_inner1;
    dst->m_inner2 = src->m_inner2;
    dst->m_radius = src->m_radius;
    dst->m_boxMin0 = src->m_boxMin0;
    dst->m_boxMin1 = src->m_boxMin1;
    dst->m_boxMin2 = src->m_boxMin2;
    dst->m_boxMax0 = src->m_boxMax0;
    dst->m_boxMax1 = src->m_boxMax1;
    dst->m_boxMax2 = src->m_boxMax2;
    dst->m_field70 = src->m_field70;
    dst->m_field72 = src->m_field72;
    dst->m_field74 = src->m_field74;
    dst->m_field78 = src->m_field78;
    dst->m_field7c = src->m_field7c;
    dst->m_field80 = src->m_field80;
    dst->m_matrix84 = src->m_matrix84;
    dst->m_fielda8 = src->m_fielda8;
    dst->m_fieldac = src->m_fieldac;
    dst->m_fieldb0 = src->m_fieldb0;
    dst->m_fieldb4 = src->m_fieldb4;
    dst->m_fieldb8 = src->m_fieldb8;
    dst->m_fieldbc = src->m_fieldbc;
    dst->m_fieldc0 = src->m_fieldc0;
    dst->m_fieldc4 = src->m_fieldc4;
    dst->m_fieldc8 = src->m_fieldc8;
    dst->m_fieldcc = src->m_fieldcc;
    dst->m_fieldd0 = src->m_fieldd0;
    dst->m_fieldd4 = src->m_fieldd4;
    dst->m_fieldd8 = src->m_fieldd8;
    dst->m_fielddc = src->m_fielddc;
    dst->m_fielde0 = src->m_fielde0;
    dst->m_fielde4 = src->m_fielde4;
    dst->m_fielde8 = src->m_fielde8;
    dst->m_fieldec = src->m_fieldec;
    return *dst;
}

// @ 0x00af6400
int SweepSide(void* ctx, float margin, CastFn cast, const Vec3* start, const Vec3* end, float side, const Hit* src, Hit* out, int count, const Hit* prev, int prevCount, float* outDist, int extra)
{
    Vec3 pos, tgt, dir, back;
    float len, c, t;
    int n = 0;

    pos.x = start->x; pos.y = start->y; pos.z = start->z;
    Hit A(*src);
    Hit B;
    *outDist = 0.0f;

    if (0 < count) {
        Hit* slot = out;
        int ii = 0;
        do {
            int k = 0;
            do {
                if (!Steer(&pos, end, &tgt, side, margin, &A, extra)) {
                    *outDist = FLT_MAX;
                    return n;
                }
                Vec3 d;
                d.x = tgt.x - pos.x;
                d.z = tgt.z - pos.z;
                d.y = tgt.y - pos.y;
                len = sqrtf(d.y * d.y + (d.z * d.z + d.x * d.x));
                float inv = 1.0f / (len + 1.5258789e-05f);
                dir.x = inv * d.x;
                dir.y = d.y * inv;
                dir.z = d.z * inv;
                if (A.type == 0 && Steer(end, &pos, &back, -side, margin, &A, extra)) {
                    len = sqrtf((tgt.y - back.y) * (tgt.y - back.y) +
                                ((tgt.z - back.z) * (tgt.z - back.z) + (tgt.x - back.x) * (tgt.x - back.x))) * 0.5f + len;
                    tgt.x = dir.x * len + pos.x;
                    tgt.y = dir.y * len + pos.y;
                    tgt.z = dir.z * len + pos.z;
                }
                c = cast(ctx, &pos, &dir, len, &B);
                if (B.id == 0)
                    break;
                for (int j = 0; j < prevCount; ++j) {
                    if (prev[j].id == B.id && prev[j].w != side) {
                        *outDist = FLT_MAX;
                        return 0;
                    }
                }
                if (B.id != A.id) {
                    Vec3 e;
                    e.x = end->x; e.y = end->y; e.z = end->z;
                    if (ProbeHit(&B, &pos, &e, 0, 0, margin)) {
                        t = 0.0f;
                        if (0.0f <= c - margin)
                            t = c - margin;
                        if (0.0f < t) {
                            tgt.x = t * dir.x + pos.x;
                            Hit* s = out + n;
                            tgt.y = dir.y * t + pos.y;
                            tgt.z = dir.z * t + pos.z;
                            *outDist = *outDist + t;
                            s->pos.x = tgt.x;
                            s->pos.y = tgt.y;
                            s->pos.z = tgt.z;
                            ++n;
                            s->Copy(&B);
                            s->w = side;
                        }
                        if (n != 0)
                            return n;
                        *outDist = FLT_MAX;
                        return 0;
                    }
                }
                A.Copy(&B);
                ++k;
            } while (k < 12);

            if (k == 12) {
                *outDist = FLT_MAX;
                return 0;
            }
            if (0.0f < len) {
                ++n;
                *outDist = *outDist + len;
                slot->pos.x = tgt.x;
                slot->pos.y = tgt.y;
                slot->pos.z = tgt.z;
                Hit* s = slot;
                ++slot;
                s->Copy(&A);
                s->w = side;
            }

            int idBefore = A.id;
            Vec3 prevPos = pos;
            Vec3 rem;
            rem.x = end->x - tgt.x;
            rem.y = end->y - tgt.y;
            rem.z = end->z - tgt.z;
            float mx = tgt.x - prevPos.x;
            float my = tgt.y - prevPos.y;
            float mz = tgt.z - prevPos.z;
            pos = tgt;
            Vec3 remDir = rem;
            if (!((rem.z * mz + rem.y * my) + rem.x * mx < 0.0f)) {
                len = sqrtf(rem.x * rem.x + (rem.y * rem.y + rem.z * rem.z));
                float inv = 1.0f / (len + 1.5258789e-05f);
                remDir.x = inv * rem.x;
                remDir.y = rem.y * inv;
                remDir.z = rem.z * inv;
                bool ok;
                switch (A.type) {
                case 0:
                    ok = SweepSphere(&A, A.id, &pos, &A.center, &remDir, &len, margin, A.radius, A.flag, &A);
                    break;
                case 1:
                    ok = SweepBox(&A, A.id, &pos, &A.center, &remDir, &len, margin, A.xform, A.box, A.flag, &A);
                    break;
                case 2:
                    ok = SweepMesh(&A, A.id, &pos, &A.center, end, &remDir, &len, margin, A.xform, A.meshPt,
                                   A.extraRadius, A.verts, A.vertCount, A.radius, A.flag, &A);
                    break;
                case 3: {
                    float r = cast(ctx, &pos, &remDir, len, &A);
                    ok = (r <= len && A.id == idBefore);
                    if (ok)
                        goto next;
                    break;
                }
                default:
                    ok = false;
                    break;
                }
                if (!ok) {
                    if (n == 0) {
                        *outDist = FLT_MAX;
                        return 0;
                    }
                    goto finish;
                }
            }
        next:
            ++ii;
        } while (ii < count);
        if (n != 0) {
        finish:
            float fx = end->x - pos.x, fy = end->y - pos.y, fz = end->z - pos.z;
            *outDist = sqrtf((fz * fz + fy * fy) + fx * fx) + *outDist;
            return n;
        }
    }
    *outDist = FLT_MAX;
    return 0;
}

// @ 0x00af6bf0
int TracePlanetPath(void* ctx, const float* initDir, float p3, CastFn_s00af_6bf0 cast, const float* start, const float* end, Hit_s00af_6bf0* out, int maxHits, int* state, float* outLen, const Hit_s00af_6bf0* prev, int extra)
{
    Vec3 pos, target, dir, d;
    float total, len, inv, dist;
    int n, iter;
    bool cont;
    char cs;

    SP::PlanetModel();
    pos.x = start[0]; pos.y = start[1]; pos.z = start[2];
    target.x = end[0]; target.y = end[1]; target.z = end[2];
    cont = true;
    *state = 4;
    total = 0.0f;
    Hit_s00af_6bf0 firstHit;                       // constructed after the setup stores, as in the original
    n = 0;
    iter = 0;

    if (0 < maxHits) {
        while (cont) {
            Hit_s00af_6bf0 hit;
            d.z = target.z - pos.z;
            d.y = target.y - pos.y;
            d.x = target.x - pos.x;
            hit.w = 0.0f;
            len = sqrtf(d.x * d.x + (d.y * d.y + d.z * d.z));
            inv = 1.0f / (len + 1.5258789e-05f);
            dir.x = inv * d.x;
            dir.y = inv * d.y;
            dir.z = inv * d.z;
            dist = cast(ctx, &pos.x, &dir.x, len, &hit);
            hit.dist = dist;
            if (len < dist) {
                cont = false;
                *state = 0;
                goto next;
            }
            hit.pos.x = dir.x * dist + pos.x;
            hit.pos.y = dir.y * dist + pos.y;
            hit.pos.z = dir.z * dist + pos.z;

            if (hit.id == 0) {
                total = dist + total;
                StoreHitPoint(&out[n], &hit);
                n = n + 1;
                if (*state != 5)
                    *state = 3;
                break;
            }
            if (n + 1 == maxHits) {
                total = dist + total;
                hit.w = 1.0f;
                out[n].CopyAll(&hit);
                n = n + 1;
                *state = 5;
                break;
            }
            if (iter == 0)
                firstHit.CopyAll(&hit);
            cs = 0;
            bool okNormal;
            if (!hit.flag || IsInvalid(hit.normal))
                okNormal = true;
            else
                okNormal = false;
            if (ProbeHit(&hit, &pos.x, &target.x, okNormal, &cs, p3) == 0) {
                Hit_s00af_6bf0 negHits[12];
                Hit_s00af_6bf0 posHits[12];
                float bestNeg = FLT_MAX;
                float bestPos = FLT_MAX;
                float prevAdj = 0.0f;
                int cntNeg, cntPos;
                float chosen;

                if (prev != 0) {
                    const Hit_s00af_6bf0* p = prev;
                    for (int i = 0; i < maxHits; ++i, ++p) {
                        if (p->id == hit.id && IsInvalid(hit.normal)) {
                            prevAdj = p->w;
                            break;
                        }
                    }
                }
                cntNeg = SweepSide(ctx, p3, cast, &pos.x, &target.x, -1.0f, &hit, negHits,
                                   maxHits - n, out, n, &bestNeg, extra);
                cntPos = SweepSide(ctx, p3, cast, &pos.x, &target.x, 1.0f, &hit, posHits,
                                   maxHits - n, out, n, &bestPos, extra);
                if (prevAdj == -1.0f && bestNeg != FLT_MAX)
                    bestPos = bestPos * 2.0f;
                if (prevAdj == 1.0f && bestPos != FLT_MAX)
                    bestNeg = bestNeg * 2.0f;

                if ((initDir[0] != gInvalidVec.x || initDir[1] != gInvalidVec.y ||
                     initDir[2] != gInvalidVec.z) && n == 0) {
                    float adj;
                    if (0 < cntNeg) {
                        Vec3 v, nd;
                        float l, il;
                        float tmp[3];
                        v.z = negHits[0].pos.z - pos.z;
                        v.y = negHits[0].pos.y - pos.y;
                        v.x = negHits[0].pos.x - pos.x;
                        l = sqrtf(v.x * v.x + (v.y * v.y + v.z * v.z));
                        il = 1.0f / (l + 1.5258789e-05f);
                        nd.x = il * v.x;
                        nd.y = il * v.y;
                        nd.z = il * v.z;
                        if (IsInvalid(negHits[0].normal)) {
                            adj = -(((initDir[2] * nd.z + initDir[1] * nd.y) + initDir[0] * nd.x) * l);
                        } else {
                            float* nn = SP::normalized_safe(tmp, &negHits[0].normal.x);
                            adj = ((nn[2] * nd.z + nn[1] * nd.y) + nn[0] * nd.x) * (l + 1.0f);
                        }
                        bestNeg = adj + bestNeg;
                    }
                    if (0 < cntPos) {
                        Vec3 v, nd;
                        float l, il;
                        float tmp[3];
                        v.z = posHits[0].pos.z - pos.z;
                        v.y = posHits[0].pos.y - pos.y;
                        v.x = posHits[0].pos.x - pos.x;
                        l = sqrtf(v.x * v.x + (v.y * v.y + v.z * v.z));
                        il = 1.0f / (l + 1.5258789e-05f);
                        nd.x = il * v.x;
                        nd.y = il * v.y;
                        nd.z = il * v.z;
                        if (IsInvalid(posHits[0].normal)) {
                            adj = -(((initDir[2] * nd.z + initDir[1] * nd.y) + initDir[0] * nd.x) * l);
                        } else {
                            float* nn = SP::normalized_safe(tmp, &posHits[0].normal.x);
                            adj = ((nn[2] * nd.z + nn[1] * nd.y) + nn[0] * nd.x) * (l + 1.0f);
                        }
                        bestPos = adj + bestPos;
                    }
                }

                if (bestPos <= bestNeg) {
                    if (bestPos == FLT_MAX) {
                        char r = ProbeHit(&hit, &pos.x, &pos.x, false, 0, 0.0f);
                        cont = false;
                        if (r == 0)
                            *state = 0;
                        else
                            *state = 1;
                        goto next;
                    }
                    chosen = bestPos;
                    if (0 < cntPos) {
                        Hit_s00af_6bf0* dst = out + n;
                        const Hit_s00af_6bf0* src = posHits;
                        n += cntPos;
                        do {
                            StoreHitPoint(dst, src);
                            ++dst;
                            ++src;
                        } while (--cntPos != 0);
                    }
                } else {
                    chosen = bestNeg;
                    if (0 < cntNeg) {
                        Hit_s00af_6bf0* dst = out + n;
                        const Hit_s00af_6bf0* src = negHits;
                        n += cntNeg;
                        do {
                            StoreHitPoint(dst, src);
                            ++dst;
                            ++src;
                        } while (--cntNeg != 0);
                    }
                }
                total = chosen + total;
                pos.x = out[n - 1].pos.x;
                pos.y = out[n - 1].pos.y;
                pos.z = out[n - 1].pos.z;
            } else {
                *state = 5;
                if (!okNormal || cs == 0 || iter > 12) {
                    total = dist + total;
                    hit.w = 1.0f;
                    out[n].CopyAll(&hit);
                    n = n + 1;
                    break;
                }
                if (iter == 0 && ProbeHit(&hit, end, &pos.x, true, &cs, p3) != 0 && !hit.flag) {
                    hit.pos.x = pos.x;
                    hit.pos.y = pos.y;
                    hit.pos.z = pos.z;
                    hit.w = 1.0f;
                    total = sqrtf((pos.z - start[2]) * (pos.z - start[2]) +
                                  (pos.y - start[1]) * (pos.y - start[1]) +
                                  (pos.x - start[0]) * (pos.x - start[0])) + total;
                    out[n].CopyAll(&hit);
                    n = n + 1;
                }
            }
next:
            iter = iter + 1;
            if (maxHits <= n)
                break;
        }
    }

    if ((unsigned int)(*state - 4) < 2) {
        float a0 = start[0], a1 = start[1], a2 = start[2];
        float b0 = end[0], b1 = end[1], b2 = end[2];
        float dx = b0 - a0;
        float dy = b1 - a1;
        float dz = b2 - a2;
        float il = 1.0f / sqrtf((dy * dy + (dz * dz + dx * dx)) + 1e-08f);
        float ndy = il * dy;
        float ndz = il * dz;
        float ndx = il * dx;
        float ib = 1.0f / sqrtf((b0 * b0 + (b1 * b1 + b2 * b2)) + 1e-08f);
        float nx = (ib * b2) * ndy - (ib * b1) * ndz;
        float ny = (ib * b0) * ndz - ndx * (ib * b2);
        float nz = ndx * (ib * b1) - (ib * b0) * ndy;
        float R = firstHit.dist;
        float planeD = -(((a2 + R * ndz) * nz + (a1 + R * ndy) * ny) + (ndx * R + a0) * nx);
        float rsq = R * R;
        int k = 1;
        if (1 < n) {
            const float* cur = &out[1].pos.z;
            const Hit_s00af_6bf0* pv = out;
            do {
                float py = pv->pos.y;
                float denom = ((*cur - pv->pos.z) * nz + (cur[-1] - py) * ny) + (cur[-2] - pv->pos.x) * nx;
                if (denom != 0.0f) {
                    float t = -((((pv->pos.z * nz + py * ny) + nx * pv->pos.x) + planeD) / denom);
                    if (0.0f <= t && t <= 1.0f) {
                        float ez = *cur - pv->pos.z;
                        float qy = (pv->pos.y + t * (cur[-1] - pv->pos.y)) - a1;
                        float qz = (pv->pos.z + t * ez) - a2;
                        float qx = ((cur[-2] - pv->pos.x) * t + pv->pos.x) - a0;
                        if (((qx * qx + qz * qz) + qy * qy < rsq) ||
                            ((qz * ndz + qy * ndy) + qx * ndx < 0.0f)) {
                            float s, vx, vy, vz, iv;
                            total = R;
                            *state = 5;
                            firstHit.w = 1.0f;
                            s = 0.0f;
                            if (0.0f <= R - p3)
                                s = R - p3;
                            vz = end[2] - start[2];
                            vy = end[1] - start[1];
                            vx = end[0] - start[0];
                            n = 1;
                            iv = 1.0f / sqrtf((vx * vx + (vy * vy + vz * vz)) + 1e-08f);
                            firstHit.pos.x = start[0] + s * (iv * vx);
                            firstHit.pos.y = start[1] + s * (vy * iv);
                            firstHit.pos.z = start[2] + s * (vz * iv);
                            out[0].CopyBase(&firstHit);
                            out[0].w = firstHit.w;
                            out[0].pos.x = firstHit.pos.x;
                            out[0].pos.y = firstHit.pos.y;
                            out[0].pos.z = firstHit.pos.z;
                            break;
                        }
                    }
                }
                ++k;
                pv = out + (k - 1);
                cur += 0x40;
            } while (k < n);
        }
    }
    if (outLen != 0)
        *outLen = total;
    return n;
}

// @ 0x00af7c60
bool SweepSphereVsTerrain(const Vector3* pos, const Vector3* dir, float radius, float scale, uint32_t mask, bool refine, cSweepResult_s00af_7c60* result, float* dist)
{
    if (*dist < 1.5258789e-05f || mask == 0xFFFFFFFF)
        return false;

    bool bHit = false;
    cObjectManager* mgr = ObjectManager();
    cSweepResult_s00af_7c60 hit;

    float ox = pos->x, oy = pos->y, oz = pos->z;
    float f = *dist;
    ObjectList list;
    float originLen = sqrtf(pos->x * pos->x + (pos->y * pos->y + pos->z * pos->z));
    Vector3 endPos;
    endPos.x = ox + f * dir->x;
    endPos.y = oy + f * dir->y;
    endPos.z = oz + f * dir->z;
    Vector3 end;
    end.x = pos->x + f * dir->x;
    end.y = pos->y + f * dir->y;
    end.z = pos->z + f * dir->z;
    int count = mgr->GetObjectsInCapsule(pos, &end, radius, &list, 0);

    for (int i = 0; i < count; i++) {
        cSpatialObject* obj = list[i];
        switch (obj->mType) {
        case 0:
            if (mask & 4) continue;
            break;
        case 1:
            if (mask & 2) continue;
            break;
        case 2:
            if (mask & 1) continue;
            break;
        case 3:
            if ((mask & 8) || (obj->mFlags & 1)) continue;
            break;
        case 4:
            if (mask & 8) continue;
            break;
        default:
            continue;
        }

        float objRadius = obj->mRadius;
        float s = *dist;
        float dx = dir->x, dy = dir->y, dz = dir->z;
        Vector3 dirScaled;
        dirScaled.x = dx * s;
        dirScaled.y = dy * s;
        dirScaled.z = dz * s;
        float t;
        if (!RaySphere(pos, &dirScaled, s * s, &obj->mCenter, objRadius + radius, &t) || t == kZero)
            continue;

        float d = (t * s) * scale;
        end.x = dx * d + pos->x;
        end.y = pos->y + dy * d;
        end.z = pos->z + dz * d;

        hit.mNounID = 0; hit.mpObject = 0; hit.mSpeedFactor = 0; hit.mbHeadOn = 0;
        hit.pad10[0] = 0; hit.pad10[1] = 0; hit.pad10[2] = 0; hit.pad10[3] = 0;
        hit.mpHitObject = obj;
        hit.pad24 = 0;
        hit.mHitCenter = obj->mCenter;
        hit.mHitNormal = gInvalidVec_s00af_7c60;
        hit.mbFlag = false;
        hit.mHitPos = end;
        hit.mRadius = objRadius + radius;

        bool big = objRadius > 10.0f || obj->mType == 4;
        bool useMesh = false;
        if (refine) {
            if (obj->mType == 3 && obj->mpMeshOwner != 0) {
                useMesh = true;
            } else if (obj->mType == 4 && obj->mpOwner != 0 &&
                       GetBoolProperty(obj->mpOwner->mpProps, 0x3EB2E21, &big) && big) {
                useMesh = true;
            }
        }

        if (!useMesh) {
            *dist = d;
            result->Copy(&hit);
        } else {
            cCollisionMesh* mesh = mgr->GetCollisionMesh(obj);
            if (mesh == 0) {
                *dist = d;
                result->Copy(&hit);
            } else {
                Transform xf(*obj->GetTransform());
                xf.SetScale(1.0f);
                Vector3 tmp;
                Vector3* n = normalized_safe(&tmp, &obj->mCenter);
                Vector3 center;
                center.y = n->y * originLen;
                center.x = n->x * originLen;
                center.z = n->z * originLen;
                xf.SetOffset(center);
                if (!SweepSphereVsMesh(result, obj, pos, &center, &endPos, dir, dist, scale, &xf,
                                       &mesh->mCenter, mesh->mRadius, mesh->mpTrisBegin,
                                       mesh->GetNumVertices(), radius, 0, 0))
                    continue;
            }
        }

        bHit = true;
        float cur = *dist;
        if (cur < 1.5258789e-05f)
            return true;
        endPos.x = pos->x + cur * dir->x;
        endPos.y = pos->y + cur * dir->y;
        endPos.z = pos->z + cur * dir->z;
    }
    return bHit;
}

// @ 0x00af82e0
bool SweepSphereVsNoun(const Vector3* pos, const Vector3* dir, float scale, cSweepResult_s00af_7c60* result, float* dist)
{
    if (*dist < 1.5258789e-05f)
        return false;

    bool bHit = false;
    cGameNounManager* mgr = NounManager();
    cGameDataArray* vec = mgr->GetGameDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                                                (void*)0x00acdff0, (void*)0x00b1e500,
                                                (void*)0x018c43e8);
    int flag = 0;
    cNounGameData* data = (cNounGameData*)FindNounGameData(&vec->mpBegin, pos, flag);
    if (data != 0)
    {
        cGameDataObject* obj = data->mpObject;
        cGameDataTransform* xf = &obj->mTransform;
        const Vector3* center =
            ((const Vector3* (__thiscall*)(cGameDataTransform*))xf->mpVtbl[0x2c / 4])(xf);
        float radius = obj->mRadius;

        Vector3 dirScaled;
        dirScaled.x = dir->x * *dist;
        dirScaled.y = dir->y * *dist;
        dirScaled.z = dir->z * *dist;

        float t;
        if (RaySphere(pos, &dirScaled, *dist * *dist, center, radius, &t) && t != 0.0f)
        {
            *dist = (*dist * t) * scale;

            result->mHitCenter = *center;
            result->mpHitObject = obj;
            result->pad24 = 0;
            result->mbFlag = false;
            result->mHitPos.x = pos->x + dir->x * *dist;
            result->mHitPos.y = pos->y + dir->y * *dist;
            result->mHitPos.z = pos->z + dir->z * *dist;
            result->mRadius = radius;
            result->mHitNormal = gInvalidVec_s00af_7c60;
            result->mNounID = 0;
            result->mpObject = 0;
            result->mSpeedFactor = 0;
            result->mbHeadOn = 0;
            result->pad10[0] = 0;
            result->pad10[1] = 0;
            result->pad10[2] = 0;
            result->pad10[3] = 0;
            bHit = true;
        }
    }
    return bHit;
}

// @ 0x00af84f0
void cContactProxy::ReleaseSource(cProxySource* src)
{
    if (src->mCount8 != 0)
    {
        ((void (__thiscall*)(void*, cProxySource*))mpVtbl[2])(this, src);
        ((void (__thiscall*)(void*, cProxySource*))mpVtbl[1])(this, src);
    }
}

// @ 0x00af8540
void cContactProxy::UpdateClosestPoint()
{
    Vector4* vec = &m_vec10;
    cContactRecord res;
    res.mpPoint = 0;
    res.pad24 = 0;
    res.mpOwner = 0;
    res.mpEntity = 0;

    SurfaceHitQuery(vec, mpB4, &res);
    if (res.mType != 0)
    {
        float resLenSq = res.mPoint.z * res.mPoint.z + res.mPoint.y * res.mPoint.y +
                         res.mPoint.x * res.mPoint.x;
        float curLenSq = vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
        if (resLenSq > curLenSq)
        {
            vec->x = res.mPoint.x;
            vec->y = res.mPoint.y;
            vec->z = res.mPoint.z;
            vec->w = res.mPoint.w;
        }
    }
}

// @ 0x00af8600
void ProjectBehindPlane(const Vector4* plane, const Vector4* p, Vector4* out)
{
    Vector4 v = *p;
    (void)v;
    float az = plane->z;
    float ay = plane->y;
    float ax = plane->x;
    float yz = ay * p->y + az * p->z;
    float dot = yz + ax * p->x;
    if (dot < 0.0f)
    {
        dot = -dot;
        float sx = ax * dot;
        float sy = ay * dot;
        float sz = az * dot;
        float sw = plane->w * dot;
        out->x = p->x + sx;
        out->y = p->y + sy;
        out->z = p->z + sz;
        out->w = p->w + sw;
    }
    else
    {
        out->w = 0.0f;
        out->z = 0.0f;
        out->y = 0.0f;
        out->x = 0.0f;
    }
}

// @ 0x00af86c0
void ProjectRayToSurface(const Vector4* from, const Vector4* to, void* surface, Vector4* out)
{
    Vector4 fromCopy;
    fromCopy.x = from->x;
    fromCopy.y = from->y;
    fromCopy.z = from->z;
    fromCopy.w = from->w;

    Vector4 dir;
    dir.x = to->x - from->x;
    dir.y = to->y - from->y;
    dir.z = to->z - from->z;
    dir.w = to->w - from->w;

    float lenSq = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
    if (lenSq > 1.0e-06f)
    {
        float len = sqrtf(lenSq);
        float inv = 1.0f / len;
        dir.x *= inv;
        dir.y *= inv;
        dir.z *= inv;
        dir.w *= inv;

        cContactRecord res;
        res.mpPoint = 0;
        res.pad24 = 0;
        res.mpOwner = 0;
        res.mpEntity = 0;
        SurfaceRayQuery(&fromCopy, surface, 6, &res);
        if (res.mType != 0)
        {
            out->x = res.mPoint.x;
            out->y = res.mPoint.y;
            out->z = res.mPoint.z;
            out->w = res.mPoint.w;
            return;
        }
    }
    out->x = to->x;
    out->y = to->y;
    out->z = to->z;
    out->w = to->w;
}

// @ 0x00af8840
void cContactProxy::SetEntity(void* owner, D961* entity, const Vector4* pos)
{
    D961* old = mpEntity;
    if (old != entity)
    {
        if (old != 0)
        {
            int buf[2];
            int* found = old->Find(buf, 0);
            if (*found == 3)
            {
                cContactOwner* holder = (cContactOwner*)old->mpField0c;
                void* obj = holder != 0
                    ? ((void* (__thiscall*)(cContactOwner*, uint32_t))holder->mpVtbl[3])(
                          holder, 0x01186577)
                    : 0;
                ((void (__thiscall*)(void*, void*))(*(void***)obj)[2])(obj, this);
            }
            mpEntity->RemoveEntityListener(&m_listenerVtbl);
        }
        mpEntity = entity;
        if (entity != 0)
        {
            m_type4c = 3;
            entity->AddEntityListener(&m_listenerVtbl);
            ((void (__thiscall*)(void*, void*))(*(void***)owner)[1])(owner, this);
        }
    }

    if (mpEntity != 0)
    {
        m_vec70.setTransformedInversePos(&mpEntity->mpHolder58->mTransform, pos);
        return;
    }
    m_vec80.w = 0.0f;
    m_vec80.z = 0.0f;
    m_vec80.y = 0.0f;
    m_vec80.x = 0.0f;
    m_vec70.w = 0.0f;
    m_vec70.z = 0.0f;
    m_vec70.y = 0.0f;
    m_vec70.x = 0.0f;
}

// @ 0x00af8920
void cContactProxy::SetFromSource(cContactRecord* src)
{
    Vector4 tmp;
    Vector4* vec;

    if (src->mType != 0)
    {
        vec = &m_vec10;
        m_type4c = src->mType;
        vec->x = src->mPoint.x;
        vec->y = src->mPoint.y;
        vec->z = src->mPoint.z;
        vec->w = src->mPoint.w;

        Vector4* p = src->mpPoint;
        if (p == 0)
            p = DirectionToPoint(&tmp, vec);
        m_vec50.x = p->x;
        m_vec50.y = p->y;
        m_vec50.z = p->z;
        m_vec50.w = p->w;
        m_b48 = 0;

        if (src->mType == 3)
        {
            cContactOwner* holder = (cContactOwner*)src->mpOwner;
            void* owner = holder != 0
                ? ((void* (__thiscall*)(cContactOwner*, uint32_t))holder->mpVtbl[3])(
                      holder, 0x01186577)
                : 0;
            SetEntity(owner, src->mpEntity, vec);
        }
    }
    else
    {
        m_type4c = 0;
        Vector4* p = DirectionToPoint(&tmp, &m_vec10);
        m_vec50.x = p->x;
        m_vec50.y = p->y;
        m_vec50.z = p->z;
        m_vec50.w = p->w;
        m_b48 = 0;
    }
}

// @ 0x00af8a10
void cContactProxy::Update(bool useLocal, float extra)
{
    Vector4 buf;
    SweepInput in;
    cContactRecord out;

    out.mpPoint = 0;
    out.pad24 = 0;
    out.mpOwner = 0;
    out.mpEntity = 0;

    Vector4 dir;
    if (useLocal)
    {
        dir.x = m_vec10.x;
        dir.y = m_vec10.y;
        dir.z = m_vec10.z;
        dir.w = m_vec10.w;
    }
    else
    {
        SurfaceHitQuery(&m_vec10, mpB4, &out);
        dir.x = out.mPoint.x;
        dir.y = out.mPoint.y;
        dir.z = out.mPoint.z;
        dir.w = out.mPoint.w;
        out.mPoint.x = kDefaultPointX;
        out.mPoint.y = kDefaultPointY;
        out.mPoint.z = kDefaultPointZ;
        out.mType = 0;
        out.mPoint.w = kDefaultPointW;
        out.pad24 = 0;
        out.mpOwner = 0;
        out.mpEntity = 0;
    }

    in.m_vec00.x = dir.x;
    in.m_vec00.y = dir.y;
    in.m_vec00.z = dir.z;
    in.m_vec00.w = dir.w;
    in.mRadius = m_fA8 + extra;
    in.m_f14 = m_fAC;
    out.mpPoint = &buf;

    SurfaceSweepQuery(&in, mpB4, mpB0, &mpCtx9c, !useLocal, &out, 0);
    SetFromSource(&out);
}

// @ 0x00af9aa0
void SP::cListenerHolder::Detach(int unused)
{
  m_pListener->Attach(0, 0, 0);
}

// @ 0x00af9ac0
void SP::cEntityListener::AddId(unsigned int id)
{
  m9c.push_back(id);
}

// @ 0x00af9b00
void SP::cEntityListener::RemoveId(unsigned int id)
{
  int i = 0;
  int n = m9c.m_size;
  if (0 < n) {
    unsigned int* p = m9c.m_data;
    do {
      if (*p == id) goto found;
      i++;
      p++;
    } while (i < n);
    return;
  found:
    if (i != -1) {
      m9c.m_size--;
      m9c.m_data[i] = m9c.m_data[m9c.m_size];
    }
  }
}

// @ 0x00af9b50
SP::cEntityListener::cEntityListener()
{
  float one = g_fOne;
  float twohundred = g_f200;
  m_vtbl = &g_vftableA;
  m9c.m_data = 0;
  m9c.m_size = 0;
  m9c.m_capacityAndFlags = (int)0x80000000;
  m0 = false;
  m10 = m14 = m18 = m1c = 0.0f;
  m20 = m24 = m28 = m2c = 0.0f;
  m30 = one;
  m34 = one;
  m38 = 0.0f;
  m3c = true;
  m40 = 0.0f;
  m44 = twohundred;
  m4c = 0;
  m50 = 0.0f;
  m54 = 0.0f;
  m58 = one;
  m5c = 0.0f;
  m64 = this;
  m68 = 0;
  m70 = m74 = m78 = m7c = 0.0f;
  m80 = m84 = m88 = m8c = 0.0f;
  m48 = 0;
  m49 = 0;
  m4a = 0;
  m90 = g_fPiOver3;
  m94 = (float)cos(g_fPiOver3);
  m98 = 0.0f;
  if ((m9c.m_capacityAndFlags & 0x3fffffff) < g_n16)
    hkArrayUtil::_reserveExactly(&m9c, g_n16, 4);
  mac = one;
  mb0 = 0;
  mb4 = 0;
}

// @ 0x00af9ca0
void SP::cEntityListener::Destroy()
{
  Attach(0, 0, 0);
  if ((m9c.m_capacityAndFlags & 0x80000000) == 0) {
    int count = m9c.m_capacityAndFlags & 0x3fffffff;
    hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
    tm->deallocateChunk(m9c.m_data, count * 4, 0x14);
  }
  m_vtbl = &g_vftableB;
}

// @ 0x00af9cf0
void SP::cActionCircle_s00af_9aa0::SetAtCenter(const cSPVector3_s00af_9aa0* center, float radius, const cSPVector3_s00af_9aa0* facing, float altitude)
{
  mbRelative = false;
  mOrientation.x = g_quatIdent[0];
  mOrientation.y = g_quatIdent[1];
  mOrientation.z = g_quatIdent[2];
  mOrientation.w = g_quatIdent[3];
  mCenter = *center;
  mRadius = radius;
  mFacing = *facing;
  mAltitude = altitude;
}

// @ 0x00af9d60
void SP::cActionCircle_s00af_9aa0::SetRelative(const cSPVector3_s00af_9aa0* center, const cSPQuaternion_s00af_9aa0* orient, float radius)
{
  mbRelative = true;
  mOrientation = *orient;
  mCenter = *center;
  mRadius = radius;
  mFacing = *(SP::cSPVector3_s00af_9aa0*)g_defFacing;
  mAltitude = 0.0f;
}

// @ 0x00af9dd0
long double FUN_00af9dd0(float param_1, int param_2)
{
  param_2 = param_2 - 1;
  float step = param_1 * 2.0f;
  if (0 < param_2) {
    int i = 6;
    do {
      param_2 = param_2 - i;
      param_1 = step + param_1;
      i = i + 6;
    } while (0 < param_2);
  }
  return (long double)param_1;
}

// @ 0x00af9e20
long double FUN_00af9e20(float param_1, int param_2)
{
  param_2 = param_2 - 1;
  float step = param_1 * 2.0f;
  float f = step;
  int i = 2;
  while (0 < param_2) {
    f = f + step;
    param_2 = param_2 - i;
    i = i + 1;
  }
  return (long double)f;
}

// @ 0x00af9ee0
int SP::cActionCircle_s00af_9aa0::IsNonDefault() const
{
  if (mCenter.mX == g_defCenter[0] && mCenter.mY == g_defCenter[1] &&
      mCenter.mZ == g_defCenter[2] && !mbRelative)
    return 0;
  return 1;
}

// @ 0x00af9f30
SP::cActionCircle_s00af_9aa0::tSlot* SP::cActionCircle_s00af_9aa0::FindFreeSlot()
{
  tSlot* e = mSlots.mpEnd;
  tSlot* p = mSlots.mpBegin;
  while (p != e && p->mOccupied) p++;
  return (p != e) ? p : 0;
}

// @ 0x00af9ff0
SP::cActionCircle_s00af_9aa0::tSlot* SP::cActionCircle_s00af_9aa0::SlotAt(unsigned int index)
{
  if (index < (unsigned int)(mSlots.mpEnd - mSlots.mpBegin))
    return mSlots.mpBegin + index;
  return 0;
}

// @ 0x00afa030
void SP::cActionCircle_s00af_9aa0::tSlot::Reserve(cGameData_s00af_9aa0* noun)
{
  mOccupied = true;
  mpReservingNoun = noun;
}

// @ 0x00afa070
void SP::cActionCircle_s00af_9aa0::tSlot::ReserveId(unsigned int id)
{
  mOccupied = true;
  mReservingId = id;
  cGameData_s00af_9aa0* old = mpReservingNoun.mpObject;
  mpReservingNoun.mpObject = (cGameData_s00af_9aa0*)0;
  if (old) old->Release();
}

// @ 0x00afa0a0
void SP::cActionCircle_s00af_9aa0::tSlot::Clear()
{
  mOccupied = false;
  mReservingId = 0;
  mpReservingNoun = (cGameData_s00af_9aa0*)0;
}

// @ 0x00afa0c0
void FUN_00afa0c0(cSPVector3_s00af_9aa0* dst, const cSPVector3_s00af_9aa0* a, const cSPVector3_s00af_9aa0* b, const cSPVector3_s00af_9aa0* c)
{
  dst[0] = *c;
  dst[1] = *a;
  dst[2] = *b;
}

// @ 0x00afa110
SP::cActionCircle_s00af_9aa0::tSlot* SP::cActionCircle_s00af_9aa0::tSlot::CopyConstruct(const tSlot* src)
{
  mOccupied = src->mOccupied;
  mpReservingNoun.mpObject = src->mpReservingNoun.mpObject;
  if (mpReservingNoun.mpObject) mpReservingNoun.mpObject->AddRef();
  mReservingId = src->mReservingId;
  mPos.mX = src->mPos.mX;
  mPos.mY = src->mPos.mY;
  mPos.mZ = src->mPos.mZ;
  return this;
}

// @ 0x00afa290
void FUN_00afa290(EA::AutoRefCount_s00af_9aa0<SP::cInteractionAgent_s00af_9aa0>* first, EA::AutoRefCount_s00af_9aa0<SP::cInteractionAgent_s00af_9aa0>* last, eastl::AgentDistanceCompare cmp)
{
  for (; first != last; ++first) {
    SP::cInteractionAgent_s00af_9aa0* cur = first->mpObject;
    if (cur) cur->AddRef();
    EA::AutoRefCount_s00af_9aa0<SP::cInteractionAgent_s00af_9aa0>* hole = first;
    while (cmp(cur, (hole - 1)->mpObject)) {
      EA::AutoRefCount_s00af_9aa0<SP::cInteractionAgent_s00af_9aa0>* prev = hole - 1;
      hole->mpObject = prev->mpObject;
      prev->mpObject = 0;
      hole = prev;
    }
    hole->mpObject = cur;
    if (cur) cur->Release();
  }
}

// @ 0x00afa380
SP::cActionCircle_s00af_9aa0::tSlot* FUN_00afa380(SP::cActionCircle_s00af_9aa0::tSlot* first, SP::cActionCircle_s00af_9aa0::tSlot* last, SP::cActionCircle_s00af_9aa0::tSlot* dst)
{
  while (first != last) {
    dst->CopyConstruct(first);
    first++;
    dst++;
  }
  return dst;
}

// @ 0x00afa510
void FUN_00afa510(float* out, const float* dir, float radius)
{
  float dx = dir[0];
  float dy = dir[1];
  float dz = dir[2];
  float inv = 1.0f / (float)sqrt((double)((dx * dx + dy * dy) + dz * dz) + g_fEps);
  float local[3];
  cPlanetModel_s00af_9aa0* model = (cPlanetModel_s00af_9aa0*)SP_PlanetModel(local, dir);
  float* surf = model->DirectionToSurfacePosition(local, dir);
  out[0] = surf[0] + (dx * inv) * radius;
  out[1] = surf[1] + (dy * inv) * radius;
  out[2] = surf[2] + (dz * inv) * radius;
}

// @ 0x00afa5d0
int SP::cActionCircle_s00af_9aa0::FindClosestFreeSlot(const cSPVector3_s00af_9aa0* p)
{
  float best = g_fFLTMax;
  int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
  int i = 0;
  int found = -1;
  if (3 < n) {
    tSlot* a = mSlots.mpBegin;
    tSlot* b = mSlots.mpBegin + 1;
    tSlot* c = mSlots.mpBegin + 2;
    tSlot* d = mSlots.mpBegin + 3;
    do {
      if (!a->mOccupied) {
        float dx = p->mX - a->mPos.mX, dy = p->mY - a->mPos.mY, dz = p->mZ - a->mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i; best = dist; }
      }
      if (!b->mOccupied) {
        float dx = p->mX - b->mPos.mX, dy = p->mY - b->mPos.mY, dz = p->mZ - b->mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i + 1; best = dist; }
      }
      if (!c->mOccupied) {
        float dx = p->mX - c->mPos.mX, dy = p->mY - c->mPos.mY, dz = p->mZ - c->mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i + 2; best = dist; }
      }
      if (!d->mOccupied) {
        float dx = p->mX - d->mPos.mX, dy = p->mY - d->mPos.mY, dz = p->mZ - d->mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i + 3; best = dist; }
      }
      i += 4;
      a += 4;
      b += 4;
      c += 4;
      d += 4;
    } while (i < n - 3);
  }
  for (; i < n; i++) {
    tSlot* s = mSlots.mpBegin + i;
    if (!s->mOccupied) {
      float dx = p->mX - s->mPos.mX, dy = p->mY - s->mPos.mY, dz = p->mZ - s->mPos.mZ;
      float dist = (dx * dx + dy * dy) + dz * dz;
      if (dist < best) { found = i; best = dist; }
    }
  }
  return found;
}

// @ 0x00afa7c0
int SP::cActionCircle_s00af_9aa0::FindClosestFreeSlotWeighted(const cSPVector3_s00af_9aa0* p, const cSPVector3_s00af_9aa0* q, float weight)
{
  float best = g_fFLTMax;
  int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
  int i = 0;
  int found = -1;
  if (3 < n) {
    tSlot* a = mSlots.mpBegin;
    tSlot* b = mSlots.mpBegin + 1;
    tSlot* c = mSlots.mpBegin + 2;
    tSlot* d = mSlots.mpBegin + 3;
    do {
      if (!a->mOccupied) {
        float px = p->mX - a->mPos.mX, py = p->mY - a->mPos.mY, pz = p->mZ - a->mPos.mZ;
        float qx = q->mX - a->mPos.mX, qy = q->mY - a->mPos.mY, qz = q->mZ - a->mPos.mZ;
        float dist = ((py * py + px * px + pz * pz) * weight + qz * qz) + qy * qy + qx * qx;
        if (dist < best) { found = i; best = dist; }
      }
      if (!b->mOccupied) {
        float px = p->mX - b->mPos.mX, py = p->mY - b->mPos.mY, pz = p->mZ - b->mPos.mZ;
        float qx = q->mX - b->mPos.mX, qy = q->mY - b->mPos.mY, qz = q->mZ - b->mPos.mZ;
        float dist = ((py * py + px * px + pz * pz) * weight + qz * qz) + qy * qy + qx * qx;
        if (dist < best) { found = i + 1; best = dist; }
      }
      if (!c->mOccupied) {
        float px = p->mX - c->mPos.mX, py = p->mY - c->mPos.mY, pz = p->mZ - c->mPos.mZ;
        float qx = q->mX - c->mPos.mX, qy = q->mY - c->mPos.mY, qz = q->mZ - c->mPos.mZ;
        float dist = ((py * py + px * px + pz * pz) * weight + qz * qz) + qy * qy + qx * qx;
        if (dist < best) { found = i + 2; best = dist; }
      }
      if (!d->mOccupied) {
        float px = p->mX - d->mPos.mX, py = p->mY - d->mPos.mY, pz = p->mZ - d->mPos.mZ;
        float qx = q->mX - d->mPos.mX, qy = q->mY - d->mPos.mY, qz = q->mZ - d->mPos.mZ;
        float dist = ((py * py + px * px + pz * pz) * weight + qz * qz) + qy * qy + qx * qx;
        if (dist < best) { found = i + 3; best = dist; }
      }
      i += 4;
      a += 4;
      b += 4;
      c += 4;
      d += 4;
    } while (i < n - 3);
  }
  for (; i < n; i++) {
    tSlot* s = mSlots.mpBegin + i;
    if (!s->mOccupied) {
      float px = p->mX - s->mPos.mX, py = p->mY - s->mPos.mY, pz = p->mZ - s->mPos.mZ;
      float qx = q->mX - s->mPos.mX, qy = q->mY - s->mPos.mY, qz = q->mZ - s->mPos.mZ;
      float dist = ((py * py + px * px + pz * pz) * weight + qz * qz) + qy * qy + qx * qx;
      if (dist < best) { found = i; best = dist; }
    }
  }
  return found;
}

// @ 0x00afad30
int SP::cActionCircle_s00af_ab70::FindSlotByAgent(cGameData_s00af_ab70* agent)
{
  int n = mSlots.GetSize();
  int i = 0;
  if (0 < n) {
    tSlot* s = mSlots.mpBegin;
    do {
      if (s->mpReservingNoun.mpObject == agent) return i;
      i++;
      s++;
    } while (i < n);
  }
  return -1;
}

// @ 0x00afad70
SP::cActionCircle_s00af_ab70::tSlot* SP::cActionCircle_s00af_ab70::FindClosestFreeSlotPtr(const cSPVector3_s00af_ab70* p)
{
  int index = FindClosestFreeSlot(p);
  if ((unsigned int)index >= (unsigned int)mSlots.GetSize()) return 0;
  return &mSlots.mpBegin[index];
}

// @ 0x00afc0d0
tSlot* cSlotVec::EraseRange(tSlot* pFirst, tSlot* pLast)
{
    tSlot* pNewEnd = (tSlot*)FUN_00afa430(pLast, mpEnd, pFirst);
    if (pNewEnd < mpEnd) {
        int32_t* pi = (int32_t*)((char*)pNewEnd + 4);
        uint32_t n = ((uint32_t)((char*)mpEnd - (char*)pNewEnd) - 1) / 0x18 + 1;
        do {
            if (*pi != 0) {
                int32_t pObj = *pi;
                (*(void(__thiscall**)(int32_t))((char*)*(int32_t*)pObj + 4))(pObj);
            }
            pi = pi + 6;
            n = n - 1;
        } while (n != 0);
    }
    mpEnd += (pLast - pFirst);
    return pFirst;
}

// @ 0x00afc150
void cSlotVec::InsertOne(tSlot* pPos, tSlot* pValue)
{
    tSlot* pOldEnd = mpEnd;
    if (pOldEnd != mpCap) {
        tSlot* pIns = pValue;
        if (pPos <= pValue && pValue < pOldEnd)
            pIns = (tSlot*)((char*)pValue + 0x18);
        if (pOldEnd != 0)
            ((tSlot*)((char*)pOldEnd - 0x18))->CopyConstruct(*(tSlot*)((char*)pOldEnd - 0x18));
        FUN_00afa4a0(pPos, (char*)pOldEnd - 0x18, pOldEnd);
        pPos->Assign(*pIns);
        mpEnd = (tSlot*)((char*)mpEnd + 0x18);
        return;
    }

    int32_t nCount = (int32_t)((char*)pOldEnd - (char*)mpBegin) / 0x18;
    int32_t nNew;
    tSlot* pNew = 0;
    if (nCount == 0) {
        nNew = 1;
    } else {
        nNew = nCount * 2;
        if (nNew == 0)
            goto alloc_done;
    }
    pNew = (tSlot*)operator_new((uint32_t)(nNew * 0x18), g_szSimulator, 0, 0, g_szAllocFile, 0xd1);
alloc_done:
    tSlot* pB = mpBegin;
    tSlot* pMid = (tSlot*)FUN_00afa380(pB, pPos, pNew);
    FUN_00afa3f0(pB, pPos, pNew);
    if (pMid != 0)
        pMid->CopyConstruct(*pValue);

    tSlot* pOldEnd2 = mpEnd;
    tSlot* pNewEnd = (tSlot*)FUN_00afa380(pPos, pOldEnd2, (char*)pMid + 0x18);
    FUN_00afa3f0(pPos, pOldEnd2, (char*)pMid + 0x18);

    tSlot* pOldBegin = mpBegin;
    if (pOldBegin != 0 && *(int32_t*)((char*)pOldBegin - 4) != 0)
        operator_delete_(pOldBegin);

    mpEnd = pNewEnd;
    mpBegin = pNew;
    mpCap = (tSlot*)((char*)pNew + nNew * 0x18);
}

// @ 0x00afc2a0
void __cdecl FUN_00afc2a0(void** pFirst, void** pLast, void** pLast2, tFloat4 v)
{
    FUN_00afbf40((int32_t*)pFirst, (int32_t*)pLast, v);

    for (void** pp = pFirst; pp < pLast; pp++) {
        int32_t nSlot = (int32_t)*pp;
        int32_t nCtx = *(int32_t*)((char*)v.pCtx + 0x50);
        int32_t nSelf = *(int32_t*)pFirst;
        float fDx = v.x - *(float*)(nCtx + 0xc + nSlot * 0x18);
        float fDy = v.y - *(float*)(nCtx + 0x10 + nSlot * 0x18);
        float fDz = v.z - *(float*)(nCtx + 0x14 + nSlot * 0x18);
        float fDist = fDx * fDx + fDz * fDz + fDy * fDy;

        float fSx = v.x - *(float*)(nCtx + 0xc + nSelf * 0x18);
        float fSy = v.y - *(float*)(nCtx + 0x10 + nSelf * 0x18);
        float fSz = v.z - *(float*)(nCtx + 0x14 + nSelf * 0x18);
        float fSelfDist = fSx * fSx + fSz * fSz + fSy * fSy;

        if (fSelfDist > fDist) {
            *pp = (void*)nSelf;
            FUN_00afb8f0((int32_t*)pFirst, 0,
                         ((int32_t)((char*)pLast - (char*)pFirst)) >> 2,
                         0, nSlot, v);
        }
    }
    FUN_00afbfb0((int32_t*)pFirst, (int32_t*)pLast, v);
}

// @ 0x00afc410
bool cActionCircle::EraseOne(tSlot* pPos)
{
    tSlot* pBegin = mSlots2.mpBegin;
    tSlot* pEnd = mSlots2.mpEnd;
    bool bResult = false;
    if (pBegin != pEnd) {
        while (pBegin != pPos) {
            pBegin = (tSlot*)((char*)pBegin + 0x18);
            if (pBegin == pEnd)
                return bResult;
        }
        if ((tSlot*)((char*)pBegin + 0x18) < pEnd)
            FUN_00afa430((char*)pBegin + 0x18, pEnd, pBegin);
        mSlots2.mpEnd = (tSlot*)((char*)mSlots2.mpEnd - 0x18);
        void** ppField = (void**)((char*)mSlots2.mpEnd + 4);
        if (*ppField != 0) {
            void* pObj = *ppField;
            (*(void(__thiscall**)(void*))((char*)*(void**)pObj + 4))(pObj);
        }
        bResult = true;
    }
    return bResult;
}

// @ 0x00afc470
void cPtrVec::PushBack(void** ppValue)
{
    void** p = mpEnd;
    if (p < mpCap) {
        mpEnd = p + 1;
        if (p != 0) {
            void* pObj = *ppValue;
            *p = pObj;
            if (pObj != 0) {
                (*(void(__thiscall**)(void*))((char*)*(void**)pObj + 0xbc))(pObj);
                return;
            }
        }
        return;
    }
    Grow(p, ppValue);
}

// @ 0x00afc4b0
bool __cdecl FUN_00afc4b0(void** pVec, void** ppKey)
{
    void** p = (void**)pVec[0];
    void** pEnd = (void**)pVec[1];
    if (p != pEnd) {
        void* pKey = *ppKey;
        do {
            if (*p == pKey)
                goto found;
            p = p + 1;
        } while (p != pEnd);
    }
    return false;

found:
    if (p + 1 < pEnd)
        FUN_00c83c90(p + 1, pEnd, p);

    pVec[1] = (void*)((char*)pVec[1] - 4);
    void** pLast = (void**)pVec[1];
    if (*pLast != 0) {
        void* pObj = *pLast;
        (*(void(__thiscall**)(void*))((char*)*(void**)pObj + 0xc0))(pObj);
    }
    return true;
}

// @ 0x00afc500
void __cdecl FUN_00afc500(int32_t* pFirst, int32_t* pLast, int32_t nLimit, tFloat4 v)
{
    uint32_t nBytes = (uint32_t)((char*)pLast - (char*)pFirst) & 0xFFFFFFFC;
    while ((int32_t)nBytes > 0x70 && nLimit > 0) {
        int32_t nMid = (int32_t)(pLast - pFirst);
        int32_t* pPivot = (int32_t*)FUN_00afb430(
            pFirst,
            pFirst + ((nMid >> 2) - (((nMid >> 2) >> 31))) / 2,
            pLast - 1, v, v);
        int32_t* pMid = (int32_t*)FUN_00afb540(pFirst, pLast, *pPivot);
        nLimit = nLimit - 1;
        FUN_00afc500(pMid, pLast, nLimit, v);
        nBytes = (uint32_t)((char*)pMid - (char*)pFirst) & 0xFFFFFFFC;
        pLast = pMid;
    }
    if (nLimit == 0) {
        FUN_00afc2a0((void**)pFirst, (void**)pLast, (void**)pLast, v);
    }
}

// @ 0x00afd1c0
void SP::cActionCircle_s00af_d1c0::SetSpiralSlots(float radius, int count)
{
	mPacking = 7;
	mSlotRadius = radius;
	mSlots.Erase(mSlots.mpBegin, mSlots.mpEnd);

	const float twoRadius = radius * kTwo;

	// Axis the facing vector is turned about, and the cross product used for the row step.
	cSPVector3_s00af_d1c0 axis;
	if (!mbRelative) {
		const float inv = 1.0f / sqrtf(((mFacing.x * mFacing.x + mFacing.y * mFacing.y) +
		                                mFacing.z * mFacing.z) + kNormEps);
		axis.x = mFacing.x * inv;
		axis.y = mFacing.y * inv;
		axis.z = mFacing.z * inv;
	}
	else {
		axis = g_defaultAxis;
	}

	const float crossX = axis.y * mFacing.z - axis.z * mFacing.y;
	const float crossY = axis.z * mFacing.x - axis.x * mFacing.z;
	const float crossZ = axis.x * mFacing.y - axis.y * mFacing.x;

	cSPVector3_s00af_d1c0 first = mbRelative ? g_defaultCenter : mCenter;

	const float sinStep = sinf(g_PI * kSpiralStep);
	const float cosStep = cosf(g_PI * kSpiralStep);

	cSPVector3_s00af_d1c0 step, tangent;
	step.x = (mFacing.x * cosStep + crossX * sinStep) * twoRadius;
	step.y = (mFacing.y * cosStep + crossY * sinStep) * twoRadius;
	step.z = (mFacing.z * cosStep + crossZ * sinStep) * twoRadius;
	tangent.x = -crossX * twoRadius;
	tangent.y = -crossY * twoRadius;
	tangent.z = -crossZ * twoRadius;

	AddSlot(first);

	int remaining = count - 1;
	int rowLength = 2;
	while (remaining > 0) {
		cSPVector3_s00af_d1c0 rowStart;
		rowStart.x = first.x + step.x;
		rowStart.y = first.y + step.y;
		rowStart.z = first.z + step.z;
		first = rowStart;

		cSPVector3_s00af_d1c0 p = rowStart;
		int left = rowLength;
		if (left > 0) {
			do {
				cSPVector3_s00af_d1c0 pos;
				if (!mbRelative) {
					const float altitude = mAltitude;
					const float inv = 1.0f / sqrtf(((p.y * p.y + p.z * p.z) +
					                                p.x * p.x) + kNormEps);
					cSPVector3_s00af_d1c0 dir;
					dir.x = p.x * inv * altitude;
					dir.y = p.y * inv * altitude;
					dir.z = p.z * inv * altitude;
					const cSPVector3_s00af_d1c0 surf = SP::PlanetModel_s00af_d1c0()->DirectionToSurfacePosition(p);
					pos.x = surf.x + dir.x;
					pos.y = surf.y + dir.y;
					pos.z = surf.z + dir.z;
				}
				else {
					pos = p;
				}
				AddSlot(pos);

				p.x = p.x + tangent.x;
				p.y = p.y + tangent.y;
				p.z = p.z + tangent.z;
				--left;
			} while (left != 0);
		}

		remaining -= rowLength;
		++rowLength;
	}

	const cSPVector3_s00af_d1c0& last = (mSlots.mpEnd - 1)->mPos;
	const float dx = last.x - first.x;
	const float dy = last.y - first.y;
	const float dz = last.z - first.z;
	mRadius = sqrtf((dz * dz + dy * dy) + dx * dx) + radius;
}

// @ 0x00afd6d0
void SP::cActionCircle_s00af_d1c0::SetRingSlots(float radius, float density, int count)
{
	mPacking = 1;
	mSlotRadius = radius;
	mSlots.Erase(mSlots.mpBegin, mSlots.mpEnd);

	const float slots = (count > 0) ? (float)count : 1.0f;
	float start = 0.0f;
	float step = 0.0f;
	if (count > 1) {
		start = (g_PI * density) * -kHalf;
		if (density >= kDenseLimit) {
			step = (1.0f / slots) * g_PI;
		}
		else {
			step = (1.0f / (slots - 1.0f)) * (g_PI * density);
		}
	}

	const cSPVector3_s00af_d1c0 center = mbRelative ? g_defaultCenter : mCenter;

	cSPVector3_s00af_d1c0 axis;
	if (!mbRelative) {
		const float inv = 1.0f / sqrtf(((mCenter.z * mCenter.z + mCenter.y * mCenter.y) +
		                                mCenter.x * mCenter.x) + kNormEps);
		axis.x = mCenter.x * inv;
		axis.y = mCenter.y * inv;
		axis.z = mCenter.z * inv;
	}
	else {
		axis = g_defaultAxis;
	}

	float i = 0.0f;
	while (i < slots) {
		const float angle = (i * step + start) * kHalf;
		const float s = sinf(angle);
		const float c = cosf(angle);

		cSPVector3_s00af_d1c0 negFacing;
		negFacing.x = -mFacing.x;
		negFacing.y = -mFacing.y;
		negFacing.z = -mFacing.z;

		cSPQuaternion_s00af_d1c0 q;
		q.x = axis.x * s;
		q.y = axis.y * s;
		q.z = axis.z * s;
		q.w = c;

		const cSPVector3_s00af_d1c0 rotated = RotateByQuat(q, negFacing);
		cSPVector3_s00af_d1c0 p;
		p.x = rotated.x * mRadius + center.x;
		p.y = rotated.y * mRadius + center.y;
		p.z = rotated.z * mRadius + center.z;

		cSPVector3_s00af_d1c0 pos;
		if (!mbRelative) {
			const float altitude = mAltitude;
			const float inv = 1.0f / sqrtf(((p.y * p.y + p.z * p.z) + p.x * p.x) + kNormEps);
			cSPVector3_s00af_d1c0 dir;
			dir.x = p.x * inv * altitude;
			dir.y = p.y * inv * altitude;
			dir.z = p.z * inv * altitude;
			const cSPVector3_s00af_d1c0 surf = SP::PlanetModel_s00af_d1c0()->DirectionToSurfacePosition(p);
			pos.x = surf.x + dir.x;
			pos.y = surf.y + dir.y;
			pos.z = surf.z + dir.z;
		}
		else {
			pos = p;
		}
		AddSlot(pos);

		i = i + 1.0f;
	}
}

// @ 0x00afdc00
void SP::cActionCircle_s00af_d1c0::SetFanSlots(float radius, float spread, int count)
{
	const float total = radius + spread;
	mPacking = 2;
	mRadius = total;
	mSlotRadius = radius;

	const float halfAngle = asin(radius / total);
	const float sides = g_PI / (halfAngle + halfAngle);
	int numSides = (int)sides;
	if (sides < (float)numSides) {
		numSides = numSides - 1;
	}
	if (count > 0 && count < numSides) {
		numSides = count;
	}

	const float step = g_PI / (float)numSides;

	cSPVector3_s00af_d1c0 axis;
	if (!mbRelative) {
		const float inv = 1.0f / sqrtf(((mCenter.z * mCenter.z + mCenter.y * mCenter.y) +
		                                mCenter.x * mCenter.x) + kNormEps);
		const float cx = mCenter.x * inv;
		const float cy = mCenter.y * inv;
		const float cz = mCenter.z * inv;
		axis.x = mFacing.z * cy - mFacing.y * cz;
		axis.y = mFacing.x * cz - mFacing.z * cx;
		axis.z = mFacing.y * cx - mFacing.x * cy;
	}
	else {
		axis = g_defaultAxisAlt;
	}

	mSlots.Erase(mSlots.mpBegin, mSlots.mpEnd);
	mSlots.Reserve(numSides);

	float angle = 0.0f;
	for (int n = numSides; n > 0; --n) {
		const float s = sinf(angle);
		const float c = cosf(angle);

		cSPVector3_s00af_d1c0 p;
		p.x = (mFacing.x * c + axis.x * s) * total;
		p.y = (mFacing.y * c + axis.y * s) * total;
		p.z = (mFacing.z * c + axis.z * s) * total;

		cSPVector3_s00af_d1c0 pos;
		if (!mbRelative) {
			cSPVector3_s00af_d1c0 q;
			q.x = mCenter.x + p.x;
			q.y = mCenter.y + p.y;
			q.z = mCenter.z + p.z;
			const float altitude = mAltitude;
			const float inv = 1.0f / sqrtf(((q.y * q.y + q.z * q.z) + q.x * q.x) + kNormEps);
			cSPVector3_s00af_d1c0 dir;
			dir.x = q.x * inv * altitude;
			dir.y = q.y * inv * altitude;
			dir.z = q.z * inv * altitude;
			const cSPVector3_s00af_d1c0 surf = SP::PlanetModel_s00af_d1c0()->DirectionToSurfacePosition(q);
			pos.x = surf.x + dir.x;
			pos.y = surf.y + dir.y;
			pos.z = surf.z + dir.z;
		}
		else {
			pos = p;
		}
		AddSlot(pos);

		angle = angle + step;
	}
}

// @ 0x00afdfe0
void __fastcall FUN_00afdfe0(void* selfv, float root)
{
	char* self = (char*)selfv;
	float* f = (float*)self;
	ArrayVT* decals = (ArrayVT*)(self + 0x50);

	*(u32*)(self + 0x24) = 3;
	decals->clear(*(void**)(self + 0x54), *(void**)(self + 0x50));

	if (g_PlanetModel() == 0)
		return;

	char alt = *(char*)(self + 0x28);

	// origin
	float ox, oy, oz;
	if (alt) { ox = DAT_0167aec4; oy = DAT_0167aec8; oz = DAT_0167aecc; }
	else     { ox = f[5];         oy = f[6];         oz = f[7];         }

	// frame row 0 (at +0x14/+0x18/+0x1c)
	float a0, a1, a2;
	if (alt) {
		a0 = DAT_0167af18; a1 = DAT_0167af1c; a2 = DAT_0167af20;
	} else {
		float e0 = f[5], e1 = f[6], e2 = f[7];
		float inv = 1.0f / sqrtf(e0 * e0 + e1 * e1 + e2 * e2 + DAT_013ec4b8);
		a0 = e0 * inv; a1 = e1 * inv; a2 = e2 * inv;
	}

	// unit up (at +0x44/+0x48/+0x4c)
	float u0 = DAT_0167aef4, u1 = DAT_0167aef8, u2 = DAT_0167aefc;

	// surface row used by the sweep at +0x1c/+0x20/+0x24
	float s0 = f[0], s1 = f[1], s2 = f[2];
	float rad = f[3];

	// radial field at +0x2c/+0x30/+0x34
	float r0 = s1 * a2 - s2 * a1;
	float r1 = s2 * a0 - s0 * a2;
	float r2 = s0 * a1 - s1 * a0;

	// second row = up x (surface row) at +0x2c/+0x30/+0x34 (reused slots)
	float b0 = u1 * r2 - u2 * r1;
	float b1 = u2 * r0 - u0 * r2;
	float b2 = u0 * r1 - u1 * r0;

	// direction row at +0x6c/+0x70/+0x74, built again from the local frame
	float d0 = b1 * r2 - b2 * r1;
	float d1 = b2 * r0 - b0 * r2;
	float d2 = b0 * r1 - b1 * r0;

	// sample count: (rad*rad * K) / (K*root*root) * 0.5
	float num = rad * rad;
	num *= DAT_01567354;
	float den = DAT_01567354 * root;
	den *= root;
	float ratio = num / den;
	ratio *= DAT_01471064;
	int count = (int)ratio;
	if (count <= 0)
		return;

	ScatterRng rng;
	rng.m_v = 0.0f;
	rng.m_w = u0;
	rng.m_i = 0;
	rng.m_j = 0;

	u32 seed = g_sMathRandom.RandomUint32Uniform(0x2ee0);
	(void)seed;

	float start0 = ox - a0 * d0;
	float start1 = oy - a1 * d1;
	float start2 = oz - a2 * d2;

	do {
		float k = (float)count;
		float p0 = start0 + r0 * k * DAT_01471064;
		float p1 = start1 + r1 * k * DAT_01471064;
		float p2 = start2 + r2 * k * DAT_01471064;

		float c0 = d0 * k * DAT_01471064;
		float c1 = d1 * k * DAT_01471064;
		float c2 = d2 * k * DAT_01471064;
		(void)c0; (void)c1; (void)c2;

		float uv[2];
		SquareToCircle(uv, 0.0f, 0.0f);

		float q0 = uv[0] * (rad - root);
		float q1 = uv[1] * (rad - root);

		// rotated into the local frame, then offset by the origin
		float w0 = (q0 * b0 + q1 * d0) + ox;
		float w1 = (q0 * b1 + q1 * d1) + oy;
		float w2 = (q0 * b2 + q1 * d2) + oz;

		if (*(char*)(self + 0x28) == 0) {
			float tmp[3];
			Func_afa510(tmp, &p0, rad);
			w0 = tmp[0]; w1 = tmp[1]; w2 = tmp[2];
		}

		DecalRec rec;
		rec.m_hdr = 0;
		rec.m_ptr = 0;
		rec.m_pad1 = 0;
		rec.m_x = w0; rec.m_y = w1; rec.m_z = w2;

		void* end = *(void**)(self + 0x54);
		if (end < *(void**)(self + 0x58)) {
			*(void**)(self + 0x54) = (char*)end + 0x18;
			if (end) *(DecalRec*)end = rec;
		} else {
			decals->constructAt(&rec);
			if (rec.m_ptr) {
				void** vt = *(void***)rec.m_ptr;
				((void(__thiscall*)(void*))vt[1])(rec.m_ptr);
			}
		}

		(void)p0; (void)p1; (void)p2;
		(void)w0; (void)w1; (void)w2;
		(void)rng;
	} while (--count != 0);
}

// @ 0x00afe3a0
void __fastcall FUN_00afe3a0(void* selfv, float spacing)
{
	char* self = (char*)selfv;
	float* f = (float*)self;
	ArrayVT* decals = (ArrayVT*)(self + 0x50);

	*(u32*)(self + 0x24) = 4;
	if (g_PlanetModel() == 0)
		return;

	char alt = *(char*)(self + 0x28);

	float ox, oy, oz;
	if (alt) { ox = DAT_0167aec4; oy = DAT_0167aec8; oz = DAT_0167aecc; }
	else     { ox = f[5];         oy = f[6];         oz = f[7];         }

	float a0, a1, a2;
	if (alt) {
		a0 = DAT_0167af18; a1 = DAT_0167af1c; a2 = DAT_0167af20;
	} else {
		float e0 = f[5], e1 = f[6], e2 = f[7];
		float inv = 1.0f / sqrtf(e0 * e0 + e1 * e1 + e2 * e2 + DAT_013ec4b8);
		a0 = e0 * inv; a1 = e1 * inv; a2 = e2 * inv;
	}

	float s0 = f[0], s1 = f[1], s2 = f[2];
	float rad = f[3];

	float r0 = s1 * a2 - s2 * a1;
	float r1 = s2 * a0 - s0 * a2;
	float r2 = s0 * a1 - s1 * a0;

	// step size doubles when the emission direction is the surface normal:
	// (r0,r1,r2)*spacing*2 with the radius-derived direction when alt, else from the row
	float k = rad / spacing;
	int count = (int)k;

	float step0 = r0 * spacing * 2.0f;
	float step1 = r1 * spacing * 2.0f;
	float step2 = r2 * spacing * 2.0f;

	float cnt = (float)count * 0.5f;
	float p0 = ox - step0 * cnt;
	float p1 = oy - step1 * cnt;
	float p2 = oz - step2 * cnt;

	decals->clear(*(void**)(self + 0x54), *(void**)(self + 0x50));

	if (count <= 0)
		return;

	do {
		if (alt) {
			DecalRec rec;
			rec.m_hdr = 0; rec.m_ptr = 0; rec.m_pad1 = 0;
			rec.m_x = p0; rec.m_y = p1; rec.m_z = p2;
			void* end = *(void**)(self + 0x54);
			if (end < *(void**)(self + 0x58)) {
				*(void**)(self + 0x54) = (char*)end + 0x18;
				if (end) *(DecalRec*)end = rec;
			} else {
				decals->constructAt(&rec);
				if (rec.m_ptr) { void** vt = *(void***)rec.m_ptr; ((void(__thiscall*)(void*))vt[1])(rec.m_ptr); }
			}
		} else {
			float tmp[3];
			Func_afa510(tmp, &p0, rad);
			DecalRec rec;
			rec.m_hdr = 0; rec.m_ptr = 0; rec.m_pad1 = 0;
			rec.m_x = tmp[0]; rec.m_y = tmp[1]; rec.m_z = tmp[2];
			void* end = *(void**)(self + 0x54);
			if (end < *(void**)(self + 0x58)) {
				*(void**)(self + 0x54) = (char*)end + 0x18;
				if (end) *(DecalRec*)end = rec;
			} else {
				decals->constructAt(&rec);
				if (rec.m_ptr) { void** vt = *(void***)rec.m_ptr; ((void(__thiscall*)(void*))vt[1])(rec.m_ptr); }
			}
		}
		p0 += step0; p1 += step1; p2 += step2;
	} while (--count != 0);
}

// @ 0x00afe670
void __fastcall FUN_00afe670(void* selfv, void* sel, float spacing)
{
	char* self = (char*)selfv;
	float* f = (float*)self;
	(void)sel;

	*(u32*)(self + 0x24) = 5;

	// surface point
	const float* org = (*(char*)(self + 0x28)) ? &DAT_0167aec4 : f + 5;
	float ox = org[0], oy = org[1], oz = org[2];

	// axis: normalized surface normal, or the alternative up vector
	float a0, a1, a2;
	if (*(char*)(self + 0x28)) {
		a0 = DAT_0167af18; a1 = DAT_0167af1c; a2 = DAT_0167af20;
	} else {
		float e0 = f[5], e1 = f[6], e2 = f[7];
		float inv = 1.0f / sqrtf(e0 * e0 + e1 * e1 + e2 * e2 + DAT_013ec4b8);
		a0 = e0 * inv; a1 = e1 * inv; a2 = e2 * inv;
	}

	float s0 = f[0], s1 = f[1], s2 = f[2];
	float rad = f[3];

	if (!(*(char*)(self + 0x28))) {
		// grid axis is the unit surface normal (computed above, kept in a0/a1/a2)
	}
	float n0 = a0, n1 = a1, n2 = a2;   // unit axis for the grid offsets

	// clear the decal vector and drop the surface point at the origin
	ArrayVT* vec = (ArrayVT*)(self + 0x50);
	vec->clear(*(void**)(self + 0x54), *(void**)(self + 0x50));
	decalAppend(self, ox, oy, oz);

	// step = 2 * spacing
	float step = spacing;
	step *= 2.0f;
	step = spacing * 2.0f;

	float p0 = DAT_01470f1c * spacing;
	float rowScale = p0 * p0;
	rowScale += rowScale;              // 2 * (k*spacing)^2
	rowScale = sqrtf(rowScale);
	// rows = (int)(radius / rowScale) + 1
	int rows = (int)(rad / rowScale) + 1;

	// surface-direction basis at this step
	float c0 = s0 * step;
	float c1 = s1 * step;
	float c2 = s2 * step;

	// grid-direction basis at this step: normal x surface, scaled
	float g0 = (n1 * s2 - n2 * s1) * step;
	float g1 = (n2 * s0 - n0 * s2) * step;
	float g2 = (n0 * s1 - n1 * s0) * step;

	int outer = 1;
	for (; outer < rows; ++outer) {
		float kf = (float)outer;
		// start point of this ring
		float q0 = (ox - g0 * kf) + c0 * kf;
		float q1 = (oy - g1 * kf) + c1 * kf;
		float q2 = (oz - g2 * kf) + c2 * kf;

		int inner = 2 * outer;
		float t0 = q0, t1 = q1, t2 = q2;

		// right edge
		for (int i = inner; i > 0; --i) {
			decalAppend(self, t0, t1, t2);
			t0 += g0; t1 += g1; t2 += g2;
		}
		// top edge
		for (int i = inner; i > 0; --i) {
			decalAppend(self, t0, t1, t2);
			t0 -= c0; t1 -= c1; t2 -= c2;
		}
		// left edge
		for (int i = inner; i > 0; --i) {
			decalAppend(self, t0, t1, t2);
			t0 -= g0; t1 -= g1; t2 -= g2;
		}
		// bottom edge
		for (int i = inner; i > 0; --i) {
			decalAppend(self, t0, t1, t2);
			t0 += c0; t1 += c1; t2 += c2;
		}
	}
}

// @ 0x00afec00
void __fastcall FUN_00afec00(void* selfv, void* /*edx*/, int** sel, float scale)
{
	char* self = (char*)selfv;
	ArrayVT* vec = (ArrayVT*)(self + 0x50);

	*(u32*)(self + 0x24) = 6;
	vec->clear(*(void**)(self + 0x50), *(void**)(self + 0x54));
	*(float*)(self + 0x10) = scale;

	int* first = sel[0];
	int* last  = sel[1];
	if (first == last)
		return;

	int count = (int)((char*)last - (char*)first) / 0xc;
	vec->reserve(count);

	if (count > 0) {
		for (int i = 0; i < count; ++i) {
			const float* p = (const float*)((char*)first + i * 0xc);
			decalAppend(self, p[0], p[1], p[2]);
		}
	}
}

// @ 0x00afed00
void __fastcall FUN_00afed00(void* selfv, void* /*edx*/, void* geom)
{
	char* self = (char*)selfv;
	ArrayVT* vec = (ArrayVT*)(self + 0x50);
	void* ref = geom;

	if (ref) {
		void** vt = *(void***)ref;
		((void(__thiscall*)(void*))vt[0xbc / 4])(ref);   // addRef
	}
	vec->pushBack(&ref);
	if (ref) {
		void** vt = *(void***)ref;
		((void(__thiscall*)(void*))vt[0xc0 / 4])(ref);   // release
	}

	// build the 7-dword record: {0, origin.xyz, origin.xyz}
	float rec[7];
	rec[0] = 0.0f;
	rec[1] = DAT_0167aec4; rec[2] = DAT_0167aec8; rec[3] = DAT_0167aecc;
	rec[4] = DAT_0167aec4; rec[5] = DAT_0167aec8; rec[6] = DAT_0167aecc;

	void* at = vec->pushBack(rec);
	void* dst = at;
	for (int i = 0; i < 7; ++i)
		((u32*)dst)[i] = ((u32*)rec)[i];

	*(u32*)((char*)geom + 0x1a4) = *(u32*)(self + 0x174);
}

// @ 0x00afedf0
void __fastcall FUN_00afedf0(void* selfv, void* /*edx*/, void* key)
{
	char* self = (char*)selfv;

	Func_afc4b0(self, &key);
	((ArrayVT*)(self + 0x38))->removeByKey(&key);
	*(u32*)((char*)key + 0x1a4) = 0;
}

// @ 0x00afee20
void FUN_00afee20(char* first, char* last, SortCtx ctx)
{
	if (first == last)
		return;

	int n = (int)(last - first) >> 2;
	int passes = 0;
	for (int t = n; t != 0; t >>= 1)
		++passes;

	((SortFn)Func_afc500)(first, last, passes * 2 - 2, ctx);

	if (n > 0x1c) {
		((SortFn)Func_afb230)(first, first + 0x70, 0, ctx);
		((SortFn)Func_afb340)(first + 0x70, last, 0, ctx);
	} else {
		((SortFn)Func_afb230)(first, last, 0, ctx);
	}
}

// @ 0x00afef10
void cSurfaceDecal::Emit(uint32_t nKind, float nSize)
{
    mSize = nSize;
    switch (nKind) {
    case 0:
        Generate(0.0f);
        break;
    case 1:
        EmitRadial(nSize, 1.0f,
                   (int32_t)(((mRadius - nSize) / nSize) * gRadialDensity));
        break;
    case 2:
        EmitArc(nSize, mRadius - nSize, 0);
        break;
    case 3:
        EmitRing(nSize);
        break;
    case 4:
        EmitSweep(nSize);
        break;
    case 5:
        EmitGrid(nSize);
        break;
    }
}

// @ 0x00afeff0
void cSurfaceDecalManager::SortDecals(const cVector3* pPosition, cIntVector* pOrder)
{
    int32_t nCount = (int32_t)(((uint8_t*)mpDecalEnd - (uint8_t*)mpDecalBegin) /
                               0x18);
    pOrder->Resize(nCount);
    for (int32_t i = 0; i < nCount; ++i)
        pOrder->mpBegin[i] = i;
    SortDecalsImpl(mpDecalBegin, mpDecalEnd, *pPosition, this);
}

// @ 0x00aff070
cSurfaceDecal* cSurfaceDecalManager::FindFreeDecal()
{
    int32_t nCount = (int32_t)(((uint8_t*)mpDecalEnd - (uint8_t*)mpDecalBegin) /
                               0x18);
    if (nCount == 0)
        return 0;
    int32_t nOrder[64];
    InitStackVector(nCount);
    for (int32_t i = 0; i < nCount && i < 64; ++i)
        nOrder[i] = i;
    ShuffleIndices(nOrder, nOrder + (nCount < 64 ? nCount : 64), 0);
    for (int32_t i = 0; i < nCount && i < 64; ++i) {
        cSurfaceDecal* pDecal = mpDecalBegin + nOrder[i];
        if (pDecal->mbUsed == 0)
            return pDecal;
    }
    return 0;
}

// @ 0x00aff160
uint32_t SmearBits(uint32_t nValue)
{
    nValue |= nValue >> 1;
    nValue |= nValue >> 2;
    nValue |= nValue >> 4;
    nValue |= nValue >> 8;
    return nValue | (nValue >> 16);
}
