// src/game/SPGonzago/_at_00b40000.cpp -- migrated from slice(s) s00b4fd80, s00b4ed50, s00b4e1d0, s00b4d220, s00b4b590, s00b4a720, s00b498d0, s00b48f20, s00b48110, s00b47600, s00b46660, s00b45170, s00b43290, s00b42760, s00b41900, s00b40a20 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00b40000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern bool  g_defaultBool;    // 0x015d9c70
extern int   g_defaultInt;     // 0x015d9c68
extern float g_defaultFloat;   // 0x015d9c6c
extern float g_156964c, g_1569650, g_1569654, g_156965c, g_15695f0, g_15695f4,
	g_1569678, g_1569680, g_1569684, g_1569688, g_156968c, g_1569690, g_1569694;
extern float g_hkRealOne;                  // 0x01485720
extern float g_013eb960;                   // 0x013eb960
extern float g_01470f1c;                   // 0x01470f1c
extern float g_013ec4d0;                   // 0x013ec4d0
extern float g_013f1cac;                   // 0x013f1cac
extern float g_f167eb78, g_f167eb7c, g_f167eb80, g_f167eb84;   // 0x0167eb78..
extern float g_f15695fc, g_f15695f8, g_f1569648;               // 0x015695f8..
#include <math.h>
#include <float.h>
#include "SP/cPlanet.h"
#include "SP/cPlanetModel.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cTribeTool.h"
#include <xmmintrin.h>
#include <new>
#include "SP/cLocomotiveObject.h"
#include <intrin.h>
#include <stddef.h>

// ---- items of slice s00b40a20 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
struct BoundingBox
{
	Vec3 min;
	Vec3 max;
	BoundingBox();   // 0x00576b40
};
struct cSPTransform_s00b4_0a20
{
	unsigned short mFlags;
	unsigned short mModificationCount;
	Vec3 mTranslation;
	float mScale;
	float mRotation[9];
	cSPTransform_s00b4_0a20();                          // 0x00409930
	void BackTransformPoint(Vec3* p);        // 0x004ff6d0
	void TransformVector(Vec3* v);           // 0x0049d640
};
struct Hull
{
	char pad0[0x4c];
	Vec3* m_begin;   // +0x4c
	Vec3* m_end;     // +0x50
};
struct GeomData
{
	char pad0[0x71];
	char m_isPolygon;   // +0x71
};
struct Contact
{
	Vec3 m_pointA[16];   // +0x000
	Vec3 m_pointB[16];   // +0x0c0
	int m_count;         // +0x180
	Vec3 m_normal;       // +0x184
	float m_zero;        // +0x190
	Vec3 m_separation;   // +0x194
};
class Geom
{
public:
	void GetCenter(Vec3* out);                    // 0x00b3d9c0
	float GetRadius();                            // 0x00b3d630
	Hull* GetHull();                              // 0x00b3d6a0
	void GetTransform(cSPTransform_s00b4_0a20* out);         // 0x00b3f6c0
	void GetBoundingBox(BoundingBox* out);        // 0x00b3f420

	int m_pad0;
	int m_type;           // +4
	char pad8[0x38];
	GeomData* m_data;     // +0x40
};
float SegmentDistance_00698b30(const Vec3* p, const Vec3* a, const Vec3* b);
void ClosestPointOnSegment_00698e00(Vec3* out, const Vec3* p, const Vec3* a, const Vec3* b);
void NormalizedSafe_00449c20(Vec3* out, const Vec3* in);
char PointInPolygon_0069a050(const Vec3* verts, int count, const Vec3* p);
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
extern bool  g_defaultBool;    // 0x015d9c70
extern int   g_defaultInt;     // 0x015d9c68
extern float g_defaultFloat;   // 0x015d9c6c
struct Property                        // EA::Property entry (flags +0x10, type +0x12)
{
	void* data;             // +0
	uint32 pad[3];
	uint16 flags;           // +0x10
	uint16 type;            // +0x12
	// Type-mismatch fallbacks live in the shared default globals above.
	void* GetStorage() { if (flags & 0x30) { return data; } else if (type) return this; return 0; }
	bool*  GetBool()  { if (type == 1  || type == 0x10) return (bool*)GetStorage();  return &g_defaultBool; }
	int*   GetInt()   { if (type == 9  || type == 0x10) return (int*)GetStorage();   return &g_defaultInt; }
	float* GetFloat() { if (type == 13 || type == 0x10) return (float*)GetStorage(); return &g_defaultFloat; }
};
struct IPropertyList                   // vt[1] = Release, vt[0x24] = GetProperty
{
	virtual void v0();          // +0
	virtual void Release();     // +4
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
	virtual bool GetProperty(uint32 key, Property** out);   // +0x24
};
struct IPropertyManager                // vt[0x30] = GetPropertyList
{
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
	virtual bool GetPropertyList(uint32 key, IPropertyList** out);   // +0x30
};
IPropertyManager* PropertyManager();   // 0x0067de30
struct PropListPtr                    // AutoRefCount<IPropertyList>
{
	IPropertyList* mp;
	IPropertyList** AsOutParam() { if (mp) { IPropertyList* o = mp; mp = 0; o->Release(); } return &mp; }
	~PropListPtr() { if (mp) mp->Release(); }
};
extern float g_156964c, g_1569650, g_1569654, g_156965c, g_15695f0, g_15695f4,
	g_1569678, g_1569680, g_1569684, g_1569688, g_156968c, g_1569690, g_1569694;
struct SphereTuning { uint8 pad0[0xa8]; float fA8; float fAC; float fB0; float fB4; int iB8; };
extern SphereTuning* g_pTuning;            // 0x0167eb70
extern float g_hkRealOne;                  // 0x01485720
extern float g_013eb960;                   // 0x013eb960
extern float g_01470f1c;                   // 0x01470f1c
extern float g_013ec4d0;                   // 0x013ec4d0
extern float g_013f1cac;                   // 0x013f1cac
extern float g_f167eb78, g_f167eb7c, g_f167eb80, g_f167eb84;   // 0x0167eb78..
extern float g_f15695fc, g_f15695f8, g_f1569648;               // 0x015695f8..
void LoadPlanetTuning(IPropertyList* list);   // 0x00b51460
struct CapsuleShape
{
	uint8 pad0[0x31];
	bool  m_b31;                  // +0x31
	bool  m_b32;                  // +0x32
	void CapsuleConstant();                          // 0x00b4d930
	void LoadSphereTuning(IPropertyList* list);      // 0x00b41390
};
// ---- items of slice s00b40a20 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern SphereTuning* g_pTuning;            // 0x0167eb70

// ---- items of slice s00b41900 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float h;             // 0x01471064 (0.5f)
extern "C" void* __cdecl memset(void*, int, unsigned);    // 0x011e073e
extern float g_lavaScale;   // 0x0167eb78
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};
struct Matrix3 {
    float m[3][3];
    Matrix3() {}
    __declspec(noinline) Matrix3(const Matrix3& o);   // 0x0041cb40
    __declspec(noinline) Matrix3& operator=(const Matrix3& o);
    Matrix3& SetIdentity();
};
extern Matrix3 g_identity;
Matrix3& Matrix3::SetIdentity()
{
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
    return *this;
}
__forceinline Vector3 operator*(const Vector3& v, const Matrix3& m)
{
    return Vector3(v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
                   v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
                   v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]);
}
__forceinline Vector3 operator*(float s, const Vector3& v)
{
    return Vector3(s * v.x, s * v.y, s * v.z);
}
__forceinline Vector3 operator*(const Vector3& v, float s)
{
    return s * v;
}
__forceinline Vector3 operator+(const Vector3& a, const Vector3& b)
{
    return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}
__forceinline Vector3 operator-(const Vector3& a, const Vector3& b)
{
    return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}
__forceinline float Dot(const Vector3& a, const Vector3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
extern const Vector3 kZero;        // 0x0167eb8c
Matrix3 g_identity = Matrix3().SetIdentity();
struct cSPTransform_s00b4_1900 {
    enum { kFlagScale = 1, kFlagRotation = 2, kFlagOffset = 4 };
    uint16_t mFlags;               // +0x00
    uint16_t mModificationCount;   // +0x02
    Vector3 mTranslation;          // +0x04
    float mScale;                  // +0x10
    Matrix3 mRotation;             // +0x14

    cSPTransform_s00b4_1900();
};
__declspec(noinline) cSPTransform_s00b4_1900::cSPTransform_s00b4_1900()
{
    mFlags = 0;
    mModificationCount = 0;
    mTranslation = kZero;
    mScale = 1.0f;
    mRotation = g_identity;
}
struct BoundingBox_s00b4_1900 {
    Vector3 lower, upper;
};
class CollisionShape {
public:
    uint32_t pad00[3];
    int mShapeType;                // +0x0c: 0/1 sphere-like, 2 box, other
    uint32_t pad10[(0xf8 - 0x10) / 4];
    Vector3 mAxes[3];              // +0x0f8: box axes (rows)
    Vector3 mLocalPointA;          // +0x11c
    Vector3 mLocalPointB;          // +0x128

    void GetCenter(Vector3* out);                 // 0x00b3d9c0
    float GetRadius();                            // 0x00b3d630
    void AddToBoundingBox(BoundingBox_s00b4_1900* box);      // 0x00b3f420
    void GetTransform(cSPTransform_s00b4_1900* out);         // 0x00b3f6c0

    void GetWorldPoints(Vector3* a, Vector3* b);
    void ProjectDirection(const Vector3& dir, float* centerDot, float* extent);
};
void* __cdecl EAAllocate(uint32_t size, const char* pName, int a, int b, const char* file,
                         int line);                       // 0x00f473a0
void __cdecl operator_delete(void* p);                    // 0x00f47380
void __cdecl TriangleNormal(Vector3* out, const Vector3* a, const Vector3* b, Vector3 c); // 0x00b3d8d0
struct RaycastFanCaster {
    bool CastFan(const float* fan, void* a2, void* a3, void* a4, const Vector3* contacts,
                 int* pCount);                            // 0x00b3ef30
    int CastFanTriangle(const float* fan, void* a2, void* a3, void* a4, Vector3* out,
                        const Vector3* contacts);
};
struct NearFilter {
    bool __thiscall IsValid(void* p);     // 0x00c02600
};
struct NearRange {
    void** mpBegin;                       // +0
    void** mpEnd;                         // +4
};
struct NearIter {
    void** mpCurrent;                     // +0
    void** mpEnd;                         // +4
    NearFilter mFilter;                   // +8

    __thiscall NearIter(const NearRange& range, bool bAuto);
    void Advance();            // 0x00b3d850
};
struct PoolNode {
    void* mpObject;       // +0
    PoolNode* mpNext;     // +4
};
#define G0  virtual void z00();
#define G1  G0  virtual void z01();
#define G2  G1  virtual void z02();
#define G3  G2  virtual void z03();
#define G4  G3  virtual void z04();
#define G5  G4  virtual void z05();
#define G6  G5  virtual void z06();
#define G7  G6  virtual void z07();
#define G8  G7  virtual void z08();
#define G9  G8  virtual void z09();
#define G10 G9  virtual void z10();
#define G11 G10 virtual void z11();
#define G12 G11 virtual void z12();
#define G13 G12 virtual void z13();
#define G14 G13 virtual void z14();
#define G15 G14 virtual void z15();
#define G16 G15 virtual void z16();
#define G17 G16 virtual void z17();
#define G18 G17 virtual void z18();
#define G19 G18 virtual void z19();
#define G20 G19 virtual void z20();
#define G21 G20 virtual void z21();
#define G22 G21 virtual void z22();
#define G23 G22 virtual void z23();
#define G24 G23 virtual void z24();
#define G25 G24 virtual void z25();
#define G26 G25 virtual void z26();
#define G27 G26 virtual void z27();
#define G28 G27 virtual void z28();
#define G29 G28 virtual void z29();
#define G30 G29 virtual void z30();
#define G31 G30 virtual void z31();
#define G32 G31 virtual void z32();
#define G33 G32 virtual void z33();
#define G34 G33 virtual void z34();
#define G35 G34 virtual void z35();
#define G36 G35 virtual void z36();
#define G37 G36 virtual void z37();
#define G38 G37 virtual void z38();
#define G39 G38 virtual void z39();
#define G40 G39 virtual void z40();
#define G41 G40 virtual void z41();
#define G42 G41 virtual void z42();
#define G43 G42 virtual void z43();
#define G44 G43 virtual void z44();
#define G45 G44 virtual void z45();
#define G46 G45 virtual void z46();
#define G47 G46 virtual void z47();
struct V46 { G46 virtual uint32_t AddRef(); };   // AddRef at +0xbc
struct V47 { G47 virtual void Release(); };      // Release at +0xc0
struct Obj {
    virtual uint32_t AddRef();      // vtable +0xbc
    virtual void Release();         // vtable +0xc0
};
struct Pool {
    uint32_t pad00[(0x1c - 0x00) / 4];
    PoolNode* mpFreeList;         // +0x1c
    uint32_t pad20[(0x24 - 0x20) / 4];
    PoolNode* mpBegin;            // +0x24
    PoolNode* mpEnd;              // +0x28
    uint32_t mNodeSize;           // +0x2c
    PoolNode* mpSentinel;         // +0x30

    PoolNode* NewNode(Obj** ppObj);
    void FreeBuckets(PoolNode** buckets, uint32_t count);
};
struct HNode {
    uint32_t mKey;         // +0
    Obj* mpValue;          // +4
    HNode* mpNext;         // +8
};
struct RefObj {
    virtual void AddRef();
};
struct HashTable {
    uint32_t m0;                 // +0x00
    HNode** mpBucketArray;       // +0x04
    uint32_t mnBucketCount;      // +0x08
    uint32_t mnElementCount;     // +0x0c
    uint32_t m10;                // +0x10
    uint32_t m14;                // +0x14
    uint32_t m18;                // +0x18
    Pool mPool;                  // +0x1c

    __thiscall HashTable(const HashTable& other);
};
extern HNode* g_emptyBucketArray;   // 0x0154df28
struct KeyPair {
    int mKey;       // +0
    int mValue;     // +4
};
struct MsgTableNode {
    uint32_t mKey;          // +0x0
    uint32_t mValue;        // +0x4
    MsgTableNode* mpNext;   // +0x8
};
struct MsgTableIter {
    MsgTableNode* mpNode;        // +0x0
    MsgTableNode** mpBucket;     // +0x4
};
struct MsgTable {
    uint32_t mRehashPolicy;      // +0x0
    MsgTableNode** mpBuckets;    // +0x4
    uint32_t mnBucketCount;      // +0x8

    void find(MsgTableIter* pOut, const uint32_t& key) const;   // 0x00645ed0
    MsgTableNode* End() const { return mpBuckets[mnBucketCount]; }
};
struct cMessageContext {
    uint32_t mDefaultValue;      // +0x00
    MsgTable mTable;             // +0x04
};
struct cSPProperty {
    G21 virtual uint32_t GetFlag58();    // vtable +0x58
    uint32_t pad04[(0x34 - 0x04) / 4];
    uint32_t mName34;            // +0x34: name blob, hashed by 0x00f21a90
    uint32_t mFlags38;           // +0x38
    uint32_t pad3c[(0x10c - 0x3c) / 4];
    void* mpObject10c;           // +0x10c
    uint32_t pad110[(0x228 - 0x110) / 4];
    uint32_t m228;               // +0x228
    uint32_t pad22c[(0xb1c - 0x22c) / 4];
    int mValueB1c;               // +0xb1c
    uint32_t padB20[(0xb58 - 0xb20) / 4];
    uint32_t mFlagsB58;          // +0xb58
};
class cCreatureBase {
public:
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
    virtual uint32_t GetMessageId();                    // +0x20
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
    virtual void v044();
    virtual bool GetFlag48();                           // +0x48
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void v070();
    virtual float GetScale();                           // +0x74
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual void v090();
virtual void v094();
virtual void v098();
virtual void v09c();
virtual void v0a0();
virtual void v0a4();
virtual void v0a8();
virtual void v0ac();
virtual void v0b0();
virtual void v0b4();
    virtual void* GetSubObject(uint32_t id);            // +0xb8

    uint32_t GetValue114();                             // 0x0096b8f0

    uint32_t pad00[(0x50 - 0x04) / 4];
    uint32_t mFlags50;           // +0x50
    uint32_t pad54[(0x110 - 0x54) / 4];
    int mType110;                // +0x110
    uint32_t mValue114;          // +0x114
    uint32_t pad118[(0x130 - 0x118) / 4];
    uint32_t mName130;           // +0x130
    uint32_t mPtr134;            // +0x134
};
struct cPropertySource {
    uint32_t pad00[(0x04 - 0x00) / 4];
    MsgTable mTable;             // +0x04
};
class cPropertyRegistry {
public:
    uint32_t pad00[(0x20 - 0x00) / 4];
    uint32_t m20;                           // +0x20

    cPropertySource* GetMessageSource(uint32_t id);   // 0x00b532f0
};
cPropertyRegistry* __cdecl GetPropertyRegistry();       // 0x00b3d310
cSPProperty* __cdecl FindProperty(void* self, uint32_t id);     // 0x00ac80d0
uint32_t __cdecl HashName(const void* pName);                   // 0x00f21a90
int __cdecl GetCurrentGameMode();                               // 0x00b5b800
void* __fastcall CastObject(void* p);                           // 0x00c90460
struct AttackObject {
    G22 virtual void Release();            // +0x5c

    uint32_t pad04[(0xf90 - 0x04) / 4];
    uint8_t mFlagF90;                      // +0xf90
};
struct XformMsgHeader {
    uint16_t mFlags;                       // +0x00
    uint16_t mModCount;                    // +0x02
};
struct XformMsg {
    XformMsgHeader mHeader;                // +0x00
    Vector3 mTranslation;                  // +0x04
    float mScale;                          // +0x10
    Matrix3 mRotation;                     // +0x14

    void SetTarget(const Vector3& pos);    // 0x00571d40
};
class cAttackCreature {
public:
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
    virtual bool HasAttack();              // +0x48
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void v070();
    virtual float GetScale();              // +0x74
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual void v090();
virtual void v094();
virtual void v098();
virtual void v09c();
virtual void v0a0();
virtual void v0a4();
virtual void v0a8();
virtual void v0ac();
virtual void v0b0();
virtual void v0b4();
    virtual AttackObject* GetAttack(uint32_t id);   // +0xb8

    uint32_t pad00[(0x50 - 0x04) / 4];
    uint32_t mFlags50;                     // +0x50
};
class cEffectHost {
public:
virtual void v00();
virtual void v04();
    virtual void Apply(uint32_t a);           // +0x08
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void ReceiveMessage(void* msg);   // +0x18
};
class cEffectsManager {
public:
    G10 virtual bool Use(uint32_t id, uint32_t a, uint32_t* pArg);   // +0x2c
};
class cPlanet {
public:
    float GetLavaSomething();              // 0x00c70a20
};
class cTerraformTuning {
public:
    float GetLavaThreshold();              // 0x01049bf0
};
class cTerraformHeight {
public:
    float GetTerraformHeight(const Vector3* pPos, bool b);   // 0x00b7e430
};
cPlanet* __cdecl GetActivePlanet();                     // 0x01021260
cTerraformTuning* __cdecl GetTerraformTuning();         // 0x01049a10
cTerraformHeight* __cdecl GetTerraformHeightObj();      // 0x00b3d350
cEffectsManager* __cdecl GetEffectsManager();           // 0x0067ddd0
void* __cdecl AsPPTypeParam(void* pOut);                // 0x00a16f40
void __fastcall XformMsgCtor(XformMsg* self);           // 0x00434040
void __cdecl Matrix3FromQuaternion(Matrix3* out, const void* pQuat);   // 0x0059c190
// ---- items of slice s00b41900 end

// ---- items of slice s00b42760 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const int kBoxFaceCorners[6][4];     // 0x01461158: corner indices of the 6 faces (-x,+x,-y,+y,-z,+z)
struct Vector3_s00b4_2760 {
    float x, y, z;
    Vector3_s00b4_2760() {}
    Vector3_s00b4_2760(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    __forceinline Vector3_s00b4_2760 operator+(const Vector3_s00b4_2760& b) const { return Vector3_s00b4_2760(x + b.x, y + b.y, z + b.z); }
    __forceinline Vector3_s00b4_2760 operator-(const Vector3_s00b4_2760& b) const { return Vector3_s00b4_2760(x - b.x, y - b.y, z - b.z); }
    __forceinline Vector3_s00b4_2760 operator*(float s) const { return Vector3_s00b4_2760(x * s, y * s, z * s); }
    __forceinline Vector3_s00b4_2760 operator-() const { return Vector3_s00b4_2760(-x, -y, -z); }
};
__forceinline float Dot_s00b4_2760(const Vector3_s00b4_2760& a, const Vector3_s00b4_2760& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
struct BoundingBox_s00b4_2760 {
    Vector3_s00b4_2760 lower, upper;
};
__forceinline const Vector3_s00b4_2760* UnitCubeCorners()
{
    static const Vector3_s00b4_2760 sCorners[8] = {
        Vector3_s00b4_2760(-1.0f, -1.0f, -1.0f),
        Vector3_s00b4_2760(1.0f, -1.0f, -1.0f),
        Vector3_s00b4_2760(1.0f, -1.0f, 1.0f),
        Vector3_s00b4_2760(-1.0f, -1.0f, 1.0f),
        Vector3_s00b4_2760(-1.0f, 1.0f, -1.0f),
        Vector3_s00b4_2760(1.0f, 1.0f, -1.0f),
        Vector3_s00b4_2760(1.0f, 1.0f, 1.0f),
        Vector3_s00b4_2760(-1.0f, 1.0f, 1.0f),
    };
    return sCorners;
}
class CollisionShape_s00b4_2760 {
public:
    uint32_t pad00[3];
    int mShapeType;             // +0x0c: 0/1 sphere-like, otherwise box
    uint32_t pad10[(0xf8 - 0x10) / 4];
    Vector3_s00b4_2760 mAxes[3];           // +0xf8: box axes (rows)

    void GetCenter(Vector3_s00b4_2760* out);                   // 0x00b3d9c0
    float GetRadius();                              // 0x00b3d630
    void AddToBoundingBox(BoundingBox_s00b4_2760* box);        // 0x00b3f420

    int GetSupportFeature(const Vector3_s00b4_2760& dir, Vector3_s00b4_2760* out, CollisionShape_s00b4_2760* other);
};
// ---- items of slice s00b42760 end

// ---- items of slice s00b43290 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char* g_167eb70;                 // 0x0167eb70  World70*
extern "C" float g_167eb8c;                 // 0x0167eb8c contact normal.x
extern "C" float g_167eb90;                 // 0x0167eb90 contact normal.y
extern "C" float g_167eb94;                 // 0x0167eb94 contact normal.z
extern "C" char  g_167ec08;                 // 0x0167ec08 Matrix3 source
extern "C" void  FUN_00b3f3a0(void*, void*);                        // 0x00b3f3a0
extern "C" void  FUN_004fc990(void*, void*, void*);                // 0x004fc990
extern "C" float FUN_00b3dcd0();                                   // 0x00b3dcd0
extern "C" void* FUN_00477820(void*, void*, float);                // 0x00477820
extern "C" void  FUN_00b3d9c0(void*, void*);                       // 0x00b3d9c0
extern "C" void  FUN_00b42370(void*, void*, void*);                // 0x00b42370
extern "C" float FUN_00b3d630(void*);                              // 0x00b3d630
extern "C" float FUN_00698b30(void*, void*, void*);                // 0x00698b30
extern "C" void  FUN_00698e00(void*, void*, void*, void*);         // 0x00698e00
extern "C" float FUN_00b3dfa0(void*, void*, void*, void*, void*, void*); // 0x00b3dfa0
extern "C" void  FUN_00b3f420(void*);                              // 0x00b3f420
extern "C" void  FUN_0041cb40(void*, void*);                       // 0x0041cb40 Matrix3::Assign
extern "C" int   FUN_00b3f6c0(void*);                              // 0x00b3f6c0
extern "C" int   FUN_00b3fe40(void*, float, void*, void*, int, void*); // 0x00b3fe40 SphereVsBoxContact
extern "C" void  FUN_00b645ed0(void*, void*, void*);               // 0x00645ed0 hashtable::find
extern "C" void  FUN_00bbc330(int, int);                           // 0x00bbc330
extern "C" void  FUN_00b72260(int);                                // 0x00b72260
extern "C" void  FUN_01068380(void*, void*);                       // 0x01068380 deque erase/clear
typedef unsigned int  u32;
struct X {
    void FUN_00b43290();                 // thiscall: compose two bases into this+0xa4 / +0xf8
};
// ---- items of slice s00b43290 end

// ---- items of slice s00b45170 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void     FUN_00f47380(void* p);
extern "C" void*    FUN_00f473a0(unsigned size, void* name, int p1, int p2, void* file, int line);
extern "C" void*    FUN_0067dcc0();
extern "C" void     FUN_00b4d720();
extern "C" void     FUN_00b5a390();
extern "C" void     FUN_00b54340(void* a, void* b, void* c);
extern "C" void     FUN_00b544c0(void* a, void* b);
extern "C" void     FUN_00b544f0(void* a, void* b);
extern "C" void     FUN_00b3f260(void** outEnd, void* first, void* last, void* mem, void* src);
extern "C" unsigned FUN_00b54520(void* a);
extern void*         gHashOwner;      // 0x0167eb70
extern unsigned char gFlag167eb75;    // 0x0167eb75
struct V3f { float x, y, z; };
struct cIter {
    void*         mNode;      // 0x00
    void**        mBucket;    // 0x04
    unsigned char mInserted;  // 0x08
};
struct cRehashResult {
    unsigned char mFlag;      // 0x00
    char          mPad01[3];
    int           mNewCount;  // 0x04
};
struct cHtNode {
    void* mKey;               // 0x00
    void* mNext;              // 0x04
};
struct cValNode {
    void* mKey;               // 0x00
    void* mValue;             // 0x04
};
struct cVal {
    int           mPad00;     // 0x00
    int           mPad04;     // 0x04
    int           mPad08;     // 0x08
    int           mPad0c;     // 0x0c
    int           mPad10;     // 0x10
    int           mPad14;     // 0x14
    int           mPad18;     // 0x18
    float         mF1c;       // 0x1c
    float         mF20;       // 0x20
    float         mF24;       // 0x24
    int           mPad28;     // 0x28
    int           mPad2c;     // 0x2c
    int           mPad30;     // 0x30
    unsigned char mFlag34;    // 0x34
    char          mPad35[3];
    int           mField38;   // 0x38
    int           mField3c;   // 0x3c

    void SetValue(void* p);                // 0x00b3dec0
};
struct cValH {
    void Register(void* a, void* b);       // 0x00c446d0
};
struct cRehash16 {
    int mPad00;               // 0x00
    int mPad04;               // 0x04
    int mPad08;               // 0x08

    void Make(void* out, int bucketCount, int nodeCount, int flag);  // 0x00921440
};
struct cHash16 {
    int    mPad00;            // 0x00
    void** mBuckets;          // 0x04
    int    mBucketCount;      // 0x08
    int    mNodeCount;        // 0x0c
    int    mPad10;            // 0x10
    int    mPad14;            // 0x14
    int    mPad18;            // 0x18

    void Destroy();                            // 0x00c2e4e0
    void SetBuckets(void* buckets, int count); // 0x00693230
    void FreeNodes(void* buckets, int count);  // 0x007611f0
    void Find(void* out, void* key);           // 0x00645ed0
};
struct cHash30 {
    int       mPad00;         // 0x00
    void**    mBuckets;       // 0x04
    int       mBucketCount;   // 0x08
    int       mNodeCount;     // 0x0c
    cRehash16 mRehash;        // 0x10
    void*     mFreeList;      // 0x1c
    int       mPad20;         // 0x20
    void*     mPoolLo;        // 0x24
    void*     mPoolHi;        // 0x28
    int       mPad2c;         // 0x2c
    void*     mSentinel;      // 0x30

    int   Remove(void* keyPtr);               // 0x00b45ab0
    cIter Insert(void* keyPtr, void* arg2);   // 0x00b45b50
    void* NewNode(void* keyPtr);              // 0x00b41dc0
    void  Resize(int count);                  // 0x00ef7c00
};
struct cObj42760 {
    int GetVec(V3f* dst, V3f* src, void* arg);   // 0x00b42760
};
struct cVec3c {
    void* mBegin;             // 0x00
    void* mEnd;               // 0x04
    void* mCap;               // 0x08

    void* InitCopy(const cVec3c* src);        // 0x00b45c10
};
struct cIface2c {
    virtual void d00() {} virtual void d01() {} virtual void d02() {} virtual void d03() {}
    virtual void d04() {} virtual void d05() {} virtual void d06() {} virtual void d07() {}
    virtual void d08() {} virtual void d09() {} virtual void d10() {}
    virtual void Send(void* sender, int msg, int param) {}
};
struct cIfaceB8 {
    virtual void d00() {} virtual void d01() {} virtual void d02() {} virtual void d03() {}
    virtual void d04() {} virtual void d05() {} virtual void d06() {} virtual void d07() {}
    virtual void d08() {} virtual void d09() {} virtual void d10() {} virtual void d11() {}
    virtual void d12() {} virtual void d13() {} virtual void d14() {} virtual void d15() {}
    virtual void d16() {} virtual void d17() {} virtual void d18() {} virtual void d19() {}
    virtual void d20() {} virtual void d21() {} virtual void d22() {} virtual void d23() {}
    virtual void d24() {} virtual void d25() {} virtual void d26() {} virtual void d27() {}
    virtual void d28() {} virtual void d29() {} virtual void d30() {} virtual void d31() {}
    virtual void d32() {} virtual void d33() {} virtual void d34() {} virtual void d35() {}
    virtual void d36() {} virtual void d37() {} virtual void d38() {} virtual void d39() {}
    virtual void d40() {} virtual void d41() {} virtual void d42() {} virtual void d43() {}
    virtual void d44() {} virtual void d45() {}
    virtual void* Get(int param) { return 0; }
};
struct cKeyObj {
    virtual void d00() {} virtual void d01() {} virtual void d02() {} virtual void d03() {}
    virtual void d04() {} virtual void d05() {} virtual void d06() {} virtual void d07() {}
    virtual void d08() {} virtual void d09() {} virtual void d10() {} virtual void d11() {}
    virtual void d12() {} virtual void d13() {} virtual void d14() {} virtual void d15() {}
    virtual void d16() {} virtual void d17() {} virtual void d18() {} virtual void d19() {}
    virtual void d20() {} virtual void d21() {} virtual void d22() {} virtual void d23() {}
    virtual void d24() {} virtual void d25() {} virtual void d26() {} virtual void d27() {}
    virtual void d28() {} virtual void d29() {} virtual void d30() {} virtual void d31() {}
    virtual void d32() {} virtual void d33() {} virtual void d34() {} virtual void d35() {}
    virtual void d36() {} virtual void d37() {} virtual void d38() {} virtual void d39() {}
    virtual void d40() {} virtual void d41() {} virtual void d42() {} virtual void d43() {}
    virtual void d44() {} virtual void d45() {} virtual void d46() {} virtual void d47() {}
    virtual void Destroy() {}
};
struct cObj45170 {
    char     mPad00[8];       // 0x00 .. 0x07
    cHash16  mSub08;          // 0x08 .. 0x23
    void*    mPtr24;          // 0x24
    char     mPad28[0x14];    // 0x28 .. 0x3b
    cHash16  mSub3c;          // 0x3c .. 0x57
    cHash16  mSub58;          // 0x58 .. 0x73
    char     mPad74[4];       // 0x74
    void*    mPtr78;          // 0x78
    char     mPad7c[0x14];    // 0x7c .. 0x8f
    void*    mPtr90;          // 0x90

    void Destroy();                          // 0x00b45170
};
struct cObj451f0 {
    char     mPad00[0x3c];    // 0x00 .. 0x3b
    cHash16  mHash3c;         // 0x3c

    void OnEvent();                          // 0x00b451f0
};
struct cObj452b0 {
    char     mPad00[0x40];    // 0x00 .. 0x3f
    cHash16  mHash40;         // 0x40

    void F();                                // 0x00b452b0
};
struct cObj452xx {
    char mPad00[0x20];        // 0x00 .. 0x1f
    int  mMode20;             // 0x20

    void     Dispatch(void* p2, void* p3, void* p4);   // 0x00b452f0
    void     Mode0A(void* p2);                         // 0x00b453a0
    void     Mode0B(void* p2);                         // 0x00b45410
    unsigned GetFlag(void* p2);                        // 0x00b45480
};
struct cFOut {
    V3f  v0;                  // 0x000 .. 0x00b
    char mPad0c[0xb4];        // 0x00c .. 0x0bf
    V3f  vc0;                 // 0x0c0 .. 0x0cb
    char mPadcc[0xb4];        // 0x0cc .. 0x17f
    union {
        int   i;
        float f;
    }    mField180;           // 0x180
    V3f  v184;                // 0x184
    V3f  v190;                // 0x190
    V3f  v19c;                // 0x19c
};
struct cObj45540 {
    int  mPad00;              // 0x000
    V3f  mFirst[0x20];        // 0x004 .. 0x183
    V3f  mSecond[0x20];       // 0x184 .. 0x303
    int  mCount1;             // 0x304
    int  mCount2;             // 0x308
    int  mPad30c;             // 0x30c

    bool  Build(void* p2, void* p3, float* p4, float* p5, cFOut* p6);   // 0x00b45540
    int Sub860(V3f* a, V3f* b, V3f* c, void* d, void* e);            // 0x00b3e860
    int Sub980(V3f* a, V3f* b, V3f* c, V3f* d, void* e, void* f);    // 0x00b3e980
    int Sub1900(V3f* a, int n, V3f* b, int m, void* c, void* d);     // 0x00b41900
};
// ---- items of slice s00b45170 end

// ---- items of slice s00b46660 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void _ReadWriteBarrier(void);
extern char gF5cObject[];         // 0x0154df28
extern "C" int* Fn_00b41ea0(int* pBegin, int* pEnd, int* pValue, unsigned char flag); // 0x00b41ea0
extern char gAimConst;                 // 0x0167ec2c
extern int  g_nAimFlag;                // 0x0167ecd0
extern "C" void __cdecl Fn_00b43710(void* pObj);              // 0x00b43710
extern "C" void __cdecl Fn_00b530e0(void* pObj, void* pRec);  // 0x00b530e0
#pragma intrinsic(_ReadWriteBarrier)
struct Vec3f { float x, y, z; };
struct Vec4f { float x, y, z, w; };
extern Vec3f g_ZeroVec;                 // 0x0167eb8c
class cPlanetModel {
public:
    float GetWaterHeight();                                      // 0x00b7e390
    float GetScale();                                            // 0x00b7e490
    Vec3f* ProjectToTangent(Vec3f* out, Vec3f* pos);             // 0x00b7e3b0 (ret 8)
    Vec3f* DirectionToSurfacePosition(Vec3f* out, Vec3f* dir);   // 0x00b815a0 (ret 8)
    Vec4f* OrientationAt(Vec4f* out, Vec3f* pos, Vec3f* up);     // 0x00b7f1f0 (ret 0xc)
    float GetRadiusAt(Vec3f* pos);                               // 0x00b7ef70 (ret 4)
};
class cMoverTarget {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
    virtual Vec3f* GetPosition();                 // +0x2c
    virtual Vec3f* GetUp();                       // +0x30
    virtual void v0d();
    virtual void SetPosition(Vec3f* p);           // +0x38
    virtual void SetOrientation(Vec4f* q);        // +0x3c
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
virtual void v2e();
virtual void v2f();
virtual void v30();
virtual void v31();
    virtual float GetRotateFactor();              // +0xc8
    void SetVelocityDir(Vec3f* v);                // 0x00c41d60 (ret 4)
    void SetAngularDir(Vec3f* v);                 // 0x00c41d90 (ret 4)
    char pad[0x48];
    uint32_t flags;                               // +0x50
};
cPlanetModel* PlanetModel();                      // 0x00b3d350
Vec3f* Normalize(Vec3f* out, Vec3f* in);          // 0x00436ce0 (cdecl)
float Dot3(Vec3f* v);                             // 0x004885d0 (v . v)
float VectorLength(Vec3f* v);                     // 0x0040ae50
Vec4f* QuatDelta(Vec4f* out, Vec4f* w, Vec4f* q); // 0x007dcb00 (cdecl)
Vec4f* QuatNormalize(Vec4f* out, Vec4f* q);       // 0x00799320 (cdecl)
void ApplyPlanetCorrection(Vec3f* pos, cMoverTarget* obj);   // 0x00b444c0 (cdecl)
class cSurfaceMover {
public:
    virtual void vfn0();
    float GetSpeed();                             // 0x00b3dcd0
    void GetOrientation(Vec4f* out);              // 0x00b3f300 (ret 4)
    void Update(float dt);                        // 0x00b46660

    int mode;                                     // +4
    char pad0[0x14];
    Vec3f vel;                                    // +0x1c
    Vec3f angVel;                                 // +0x28
    char onSurface;                               // +0x34
    char flag35;                                  // +0x35
    char active;                                  // +0x36
    char pad3;
    char pad4[8];
    cMoverTarget* obj;                            // +0x40
};
struct cMoverIterator {
    int   GetPriority();          // 0x00e31100 UTCWin::IWinProc::GetPriority
    void* Next(int* pKey);        // 0x00b72230
};
struct cMoverRegistry {
    char           mPad00[0x3c];
    cMoverIterator mIter;         // +0x3c
};
extern cMoverRegistry* g_pMoverRegistry;   // 0x0167eb70
struct cMoverTargetFlags {
    char mPad00[0x70];
    unsigned char mFlag70;        // +0x70
    char mPad71[0x75 - 0x71];
    unsigned char mFlag75;        // +0x75
};
struct cCurvePoint {
    char mData[0x3c];
    void CopyFrom(cCurvePoint* pOther);   // 0x00ac1ff0
};
struct cCurve {
    void AssignFrom(cCurve* pOther);      // 0x00b45c10
    char  mPad00[0x14];
    cCurvePoint mPoint;                   // +0x14
    float mF50;                           // +0x50
    float mF54;                           // +0x54
    float mF58;                           // +0x58
    unsigned int mF5c;                    // +0x5c
    float mF60;                           // +0x60
    float mF64;                           // +0x64
    float mF68;                           // +0x68
    float mF6c;                           // +0x6c
    unsigned int mF70;                    // +0x70
    cCurve* Assign(cCurve* pOther);       // 0x00b46d90
};
struct cVecHolder {
    float x, y, z;
    void Clear();                 // 0x00743b50 cModelWorld::VecClear
};
struct cHolder {
    char        mPad00[0x08];
    cVecHolder  mVec1;            // +0x08
    char        mPad14[0x24 - 0x14];
    unsigned int mF24;            // +0x24
    unsigned int mF28;            // +0x28
    unsigned int mF2c;            // +0x2c
    char        mPad30[0x3c - 0x30];
    cVecHolder  mVec2;            // +0x3c
    char        mPad48[0x5c - 0x48];
    void*       mpF5c;            // +0x5c
    unsigned int mF60;            // +0x60
    unsigned int mF64;            // +0x64
    float       mF68;             // +0x68
    float       mF6c;             // +0x6c
    unsigned int mF70;            // +0x70
    char        mPad74[0x78 - 0x74];
    unsigned int mF78;            // +0x78
    unsigned int mF7c;            // +0x7c
    unsigned int mF80;            // +0x80
    char        mPad84[0x90 - 0x84];
    unsigned int mF90;            // +0x90
    unsigned int mF94;            // +0x94
    unsigned int mF98;            // +0x98
    cHolder* Init();              // 0x00b46ff0
};
void Fn_00b452b0();               // 0x00b452b0
struct cSwitchHolder {
    char         mPad00[0x3c];
    int          mState;          // +0x3c
    void Cleanup();               // 0x00b47060
};
struct cRange {
    int* mpBegin;                 // +0x00
    int* mpEnd;                   // +0x04
    char mPad08[0x14 - 0x08];
    unsigned char mF14;           // +0x14
    int* Find(int* pValue);       // 0x00b47570
};
class cRandomLCG {
public:
    unsigned RandomUint32Uniform(unsigned n);   // 0x00a68fb0
};
void Fn_010216a0(int* pA, int* pB);   // 0x010216a0
class cAimObject {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
virtual void v0b();
    virtual Vec4f* GetOrientation();              // +0x30
virtual void v0d();
virtual void v0e();
    virtual void SetOrientation(Vec4f* pQ);       // +0x3c
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
    virtual void GetTargetOrientation(Vec4f* pOut); // +0x5c
};
extern "C" void  __stdcall Fn_00d58510(Vec3f* pOut, cAimObject* pObj, float fValue); // 0x00d58510
extern "C" Vec3f* __cdecl  Fn_0059aed0(Vec3f* pOut, const void* pConst, const Vec3f* pIn); // 0x0059aed0
extern "C" Vec4f* __stdcall Slerp(Vec4f* pOut, const Vec4f* pA, const Vec4f* pB, float t); // 0x005b2500
extern "C" bool  __cdecl  Fn_00b3d550(Vec4f* pQuat);  // 0x00b3d550
class cStoredObject {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
virtual void AddRef();
    virtual void Release();                                          // +0xc0
};
class cRegistrarObject {
public:
virtual void v00();
virtual void v01();
virtual void v02();
    virtual void* GetByTag(unsigned int nTag);    // +0x0c
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual unsigned int GetId();                 // +0x20
};
struct cRecordList {
    void Append(void** ppRecord);                 // 0x00b45ab0
};
struct cMoverOwner {
    char          mPad00[0x60];
    cStoredObject** mpBegin;                      // +0x60
    cStoredObject** mpEnd;                        // +0x64
    char          mPad68[0x47c - 0x68];
    cRecordList   mRecordList;                    // +0x47c
    void Register(cRegistrarObject* pObj);        // 0x00b470b0
};
struct cSlabBox {
    void Compute(float* pDir, float* pLo, float* pHi);   // 0x00b425b0
};
struct cSlabTester {
    char mFlag;                                   // +0x00
    bool Clip(void* pBoxA, void* pBoxB, float* pNormal, float* pV,
              float fDistance, float* pBest, unsigned char* pMask,
              float* pMin, float* pMax, float* pNegDir, float* pPosDir);
};
// ---- items of slice s00b46660 end

// ---- items of slice s00b47600 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct V3 { float x, y, z; };
static inline V3 MakeV3(float x, float y, float z) { V3 r; r.x = x; r.y = y; r.z = z; return r; }
template<class T> static inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
template<class T> static inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
struct Mat3 { float m[9]; };
struct BBox { V3 mn, mx; };
struct PropHolder;
struct Part25c { uint32_t pad[0x25c / 4]; float f25c; };
struct Obj_s00b4_7600 {
    uint32_t m0;
    uint32_t m4;                    // +4
    uint32_t m8;                    // +8
    int state;                      // +0xc
    float f10, f14, f18;            // +0x10..
    uint32_t pad1[6];               // +0x1c..0x33
    uint8_t b34, b35, b36, b37;
    uint32_t m38, m3c;
    Part25c* m40;
    V3 v44, v50;                    // +0x44, +0x50
    Mat3 m5c;                       // +0x5c
    Mat3 m80;                       // +0x80
    uint32_t pad2[9];               // +0xa4..0xc7
    V3 vc8, vd4, ve0, vec;          // +0xc8..
    uint32_t pad3[9];               // +0xf8..0x11b
    float f11c, f120, f124, f128, f12c, f130, f134;
    float F_b3d630();
    void F_b3f420(BBox* b);
    const BBox* F_b3f730(BBox* b);
    void F_b43290();
    void F_b3dbb0();
};
struct cObj;
struct Pool_s00b4_7600 {
    int F_b72160();
    Obj_s00b4_7600* F_b72210(int h);
    void F_b72260(int h);           // 0x00b72260  release handle
};
struct HashNode {
    void* mpKey;                    // +0x00
    Obj_s00b4_7600* mpObj;                     // +0x04
};
struct HashIter {
    HashNode* mpNode;               // +0x00
    HashNode** mpBucket;            // +0x04
    bool operator==(const HashIter& x) const { return mpNode == x.mpNode; }
};
struct Map {
    void* mpPad0;                   // +0x00
    HashNode** mpBucketArray;       // +0x04
    uint32_t mnBucketCount;         // +0x08
    HashIter end() const
    {
        HashIter i;
        i.mpNode = mpBucketArray[mnBucketCount];
        i.mpBucket = mpBucketArray + mnBucketCount;
        return i;
    }
    HashIter find(cObj* const& key) const;      // 0x00645ed0
    HashIter erase(HashIter it);                // 0x01068380
    Obj_s00b4_7600** F_b474c0(const uint32_t* key);
};
struct Mgr {
    uint32_t m0;
    uint32_t m4;                    // +4
    uint32_t pad0[(0x3c - 8) / 4];
    Pool_s00b4_7600 pool;                      // +0x3c
    uint32_t pad1[(0x58 - 0x40) / 4];
    Map map;                        // +0x58
    uint32_t pad2[(0xb4 - 0x64) / 4];
    float ratio;                    // +0xb4
};
extern Mgr* g_mgr;                  // 0x0167eb70
extern V3 g_v;                      // 0x0167eb8c
int GetTutorialToolPrice(PropHolder* p, int key, int def);      // 0x004e1c30
float GetPropertyFloat(PropHolder* p, int key, float def);      // 0x004e1c70
int F_ac8fa0(PropHolder* p, int key, int a);
Mat3* F_4fc990(Mat3* out, const Mat3* in, float* det);
int F_bbc300(uint32_t a, int h, V3* mn, V3* mx);
struct Elem44 { uint32_t w[11]; };                  // 44 bytes
struct Vec44 {
    Elem44* mpBegin;                                // +0x00
    Elem44* mpEnd;                                  // +0x04
    Elem44* mpCapacity;                             // +0x08
    void DoInsertValue(Elem44* position, const Elem44& value);   // 0x00b47600
};
void* F_f473a0(unsigned size, const char* pName, int flags, int dbgFlags,
               const char* pFile, int line);        // 0x00f473a0  operator new
void  F_f47380(void* p);                            // 0x00f47380  operator delete
Elem44* F_b3d890(Elem44* first, Elem44* last, Elem44* dest);   // 0x00b3d890
static inline void CopyBackward44(Elem44* first, Elem44* last, Elem44* result)
{
    while (last != first)
        *--result = *--last;
}
static const char kAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static Elem44* DoAllocate44(unsigned n)
{
    return n ? (Elem44*)F_f473a0(n * sizeof(Elem44), "Simulator", 0, 0,
                                 kAllocFile, 0xd1) : 0;
}
struct cObj {
    void** mpVtbl;                  // +0x00
    uint8_t pad04[0x50 - 0x04];
    uint8_t b50;                    // +0x50  bit 7 suppresses the property pass
    uint8_t pad51[0x54 - 0x51];
    int32_t m54;                    // +0x54  message-source handle
    int32_t m58;                    // +0x58  override handle
    uint8_t pad5c[0x70 - 0x5c];
    uint8_t b70;                    // +0x70
    uint8_t pad71[0x75 - 0x71];
    uint8_t b75;                    // +0x75
};
#define VSLOT(p, off) (*(void***)(p))[(off) / 4]
static __forceinline void* ObjSubTag(cObj* p, uint32_t id)
{
    return ((void* (__thiscall*)(cObj*, uint32_t))VSLOT(p, 0xb8))(p, id);
}
static __forceinline uint32_t ObjId(cObj* p)
{
    return ((uint32_t (__thiscall*)(cObj*))VSLOT(p, 0x20))(p);
}
static __forceinline void ObjBox(cObj* p, BBox* pBox)
{
    ((void (__thiscall*)(cObj*, BBox*))VSLOT(p, 0x6c))(p, pBox);
}
static __forceinline void ObjVCall0(void* p)
{
    ((void (__thiscall*)(void*))VSLOT(p, 0))(p);
}
static __forceinline void ObjVCall1(void* p)
{
    ((void (__thiscall*)(void*))VSLOT(p, 4))(p);
}
struct cSim {
    void* GetMsgSource(uint32_t id);                // 0x00b532f0
};
cSim* GetSim();                                     // 0x00b3d310
void* F_b41ee0(void* a, void* b);                   // 0x00b41ee0
char  F_64f350(void* p, uint32_t id, int flag);     // 0x0064f350
int   F_ac8fa0(void* p, uint32_t id, int v);        // 0x00ac8fa0
void  F_bbc320(int self, int h, const V3* mn, const V3* mx);   // 0x00bbc320
void  F_bbc330(int self, int h);                    // 0x00bbc330
// ---- items of slice s00b47600 end

// ---- items of slice s00b48110 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_167eb8c;      // 0x0167eb8c  zero vector x
extern float g_167eb90;      // 0x0167eb90  zero vector y
extern float g_167eb94;      // 0x0167eb94  zero vector z
extern float g_146113c;      // 0x0146113c  +1e20f
extern float g_14611c0;      // 0x014611c0  -1e20f
extern float g_1461154;      // 0x01461154  squared-length epsilon
extern int   g_1569a88;      // 0x01569a88  per-tick object budget (game mode A)
extern char  g_1601760;      // 0x01601760  random LCG instance
extern void* __cdecl FUN_00b5b800();                                    // GetCurrentGameMode
extern void* __cdecl FUN_00b41ee0(void* a, void* b);
extern void  __cdecl FUN_00b539e0(void* p);
extern void  __cdecl FUN_00b43710(void* p);
extern void  __cdecl FUN_00b47ee0(void* p);
extern void  __cdecl FUN_00b475b0(void** pBegin, void** pEnd, void* pRandom);
extern const float g_1488874;    // 0x01488874  0.1f
extern const float g_13eb8a0;    // 0x013eb8a0  0.25f
extern const float g_13f7344;    // 0x013f7344  0.95f
extern const float g_1470f1c;    // 0x01470f1c  2.0f
extern const float g_1471064;    // 0x01471064  0.5f
extern void __cdecl operator_delete__(void* p);                  // 0x00f47380
#pragma intrinsic(sqrt)
typedef unsigned int  uint;
typedef unsigned char uchar;
extern uint  g_167ecc0;      // 0x0167ecc0  "useGameplayPhantom" once-guard
extern uint  g_167ecbc;      // 0x0167ecbc  cached FNV hash
struct cGameObject {
    char  mPad00[0x75];                                          // +0x00
    uchar mFlag76;                                               // +0x76
    char  mPad77[0x50];                                          // +0x77
};
struct cGameVtbl {
    void (*v00)();
    void (*v04)();
    void (*v08)();
    cGameObject* (*GetSubTag)(void* pThis, uint id);               // +0x0c
    void (*v10)();
    void (*v14)();
    void (*v18)();
    void (*v1c)();
    uint (*GetId)(void* pThis);                                    // +0x20
    void (*v24)();
    void (*v28)();
    void (*v2c)();
    void (*v30)();
    void (*v34)();
    void (*v38)();
    void (*v3c)();
    void (*v40)();
    void (*v44)();
    void (*v48)();
    void (*v4c)();
    void (*v50)();
    void (*v54)();
    void (*v58)();
    void (*v5c)();
    void (*v60)();
    void (*v64)();
    void (*v68)();
    void (*v6c)();
    void (*v70)();
    void (*v74)();
    void (*v78)();
    void (*v7c)();
    void (*v80)();
    void (*v84)();
    void (*v88)();
    void (*v8c)();
    void (*v90)();
    void (*v94)();
    void (*v98)();
    void (*v9c)();
    void (*va0)();
    void (*va4)();
    void (*va8)();
    void (*vac)();
    void (*vb0)();
    void (*vb4)();
    void (*vb8)();
    void (*AddRef)(void* pThis);                                   // +0xbc
    void (*Release)(void* pThis);                                  // +0xc0
    void (*vc4)();
    void (*vc8)();
    void (*vcc)();
    void (*vd0)();
    void (*vd4)();
    void (*vd8)();
    void (*vdc)();
    void (*ve0)();
    void (*ve4)();
    void (*ve8)();
    void (*vec)();
    void (*Update)(void* pThis);                                   // +0xf0
};
inline void* vtOf(cGameObject* p) { return *(void**)p; }
inline void   vtAddRef(cGameObject* p)            { ((cGameVtbl*)vtOf(p))->AddRef(p); }
inline void   vtRelease(cGameObject* p)           { ((cGameVtbl*)vtOf(p))->Release(p); }
inline cGameObject* vtGetSubTag(cGameObject* p, uint id)
                                                  { return ((cGameVtbl*)vtOf(p))->GetSubTag(p, id); }
inline uint   vtGetId(cGameObject* p)             { return ((cGameVtbl*)vtOf(p))->GetId(p); }
struct cSurfaceObj {
    char  mPad00[0x0c];
    int   mKind;                                                 // +0x0c
    Vec3* FUN_00b3da90(Vec3* pOut, int nIndex, cSurfaceObj* pOther);  // 0x00b3da90
};
struct cIter_s00b4_8110 { void* mpNode; void* mpBucket; uchar mInserted; };
struct cRecordMap {
    char   mPad00[4];
    void** mpBuckets;                                            // +0x04
    uint   mCount;                                               // +0x08
    void*  mpField0c;                                            // +0x0c
    void Insert(cIter_s00b4_8110* pOut, void** ppKey, bool bFlag);          // 0x00b45b50
    void find(cIter_s00b4_8110* pOut, const uint* pKey);                    // 0x00645ed0
};
struct cIceEntry { int mField0; float mValue; };                 // 8 byte entries
struct cSim_s00b4_8110 {
    uchar  mClipFlag;                                            // +0x00
    char   mPad01[0x1f];                                         // +0x01
    int    mMode;                                                // +0x20
    char   mPad24[0x3c];                                         // +0x24
    cGameObject** mpObjBegin;                                    // +0x60
    cGameObject** mpObjEnd;                                      // +0x64
    char   mPad68[0x410];                                        // +0x68
    int    mObjIndex;                                            // +0x478
    cRecordMap mRecords;                                         // +0x47c

    void* GetMsgSource(uint id);                                 // 0x00b532f0
    void  FUN_00b5a260(cGameObject* p2, cGameObject* p3);        // 0x00b5a260
    void  Fn_00b48770(cGameObject* pObj, bool bFlag);            // 0x00b48770
    void  Fn_00b48920();                                         // 0x00b48920
    bool  Fn_00b489d0(cSurfaceObj* pA, cSurfaceObj* pB, Vec3* pNormal,
                      float fLimit, float* pOutT, Vec3* pOutVec); // 0x00b489d0
    bool  Clip(void* pBoxA, void* pBoxB, Vec3* pNormal, Vec3* pV,
               float fDistance, Vec3* pBest, uchar* pMask,
               float* pMin, float* pMax, Vec3* pNegDir, Vec3* pPosDir); // 0x00b47200
};
struct cUpdateObj {
    char  mPad00[0x76];                                          // +0x00
    uchar mFlag76;                                               // +0x76
    void  Update();                                              // vtable +0xf0
};
struct cWorldObj {
    char   mPad00[0x58];                                         // +0x00
    cRecordMap mMap58;                                           // +0x58
    char   mPad68[0x10];                                         // +0x68
    cIceEntry* mpIceBegin;                                       // +0x78
    cIceEntry* mpIceEnd;                                         // +0x7c
};
extern cWorldObj* g_167eb70_s00b4_8110;                                     // 0x0167eb70
extern char  __cdecl FUN_0064f350(void* pNode, uint key, int flag);
extern uint  __cdecl FUN_00932e80(const char* s, uint seed, int c);
static const int& Min_s00b4_8110(const int& a, const int& b) { return a < b ? a : b; }
static int SampleCount(int k)
{
    int n;
    if (k < 0)
        n = 0;
    else if (k <= 1)
        n = 1;
    else if (k == 2)
        n = 3;
    else
        n = 0;
    return n;
}
struct SteerNode {
    char mPad00[4];
    int  mField04;                                               // +0x04
    char mPad08[0x24];                                           // +0x08
};
struct SteerVec {
    SteerNode* mpBegin;                                          // +0x00
    SteerNode* mpEnd;                                            // +0x04
    SteerNode* mpCap;                                            // +0x08
    void push_back();                                            // 0x00b48e00
    void DoInsertValue(SteerNode* pWhere, SteerNode* pValue);    // 0x00b47600
};
struct Quat { float x, y, z, w; };
struct Waypoint { float f[15]; };                                 // 0x3c bytes
struct cLocomotionRequest {
    Waypoint* mpBegin;                                           // +0x00
    Waypoint* mpEnd;                                             // +0x04
    char      mPad08[0x14 - 0x08];                               // +0x08
    Vec3      mDst;                                              // +0x14 (head of the 0x3c-byte
                                                                 //       current waypoint)
    float     mGoalStopDistance;                                 // +0x20
    char      mPad24[0x50 - 0x24];                               // +0x24
    Vec3      mField50;                                          // +0x50 reference direction
    int       mType;                                             // +0x5c (0 none, 1/3 follow, 2 hold)
    float     mAcceptableStopDistance;                           // +0x60
    float     mField64;                                          // +0x64 alignment threshold
    float     mPrevDistance;                                     // +0x68
    float     mElapsed;                                          // +0x6c
    int       mField70;                                          // +0x70

    cLocomotionRequest();                                        // 0x00ac9850
    cLocomotionRequest(const cLocomotionRequest& o);             // 0x00b46d90 (ret 4)
    void EraseWaypoint(const Waypoint* pWhere);                  // 0x00b47520 (ret 4)
    ~cLocomotionRequest()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};
class cSteerLoco {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
    virtual const Vec3* GetPosition();                           // +0x2c
    virtual Quat* GetOrientation();                              // +0x30
virtual void v0d();
virtual void v0e();
    virtual void SetOrientation(const Quat* pQ);                 // +0x3c
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
    virtual const Vec3* GetDirection(Vec3* pOut);                // +0x5c
virtual void v18();
virtual void v19();
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
    virtual void FnB8(const void* pArg);                         // +0xb8
virtual void v2f();
virtual void v30();
    virtual void SetDesiredSpeed(float fSpeed, int nFlag);       // +0xc4
    virtual float GetDesiredSpeed();                             // +0xc8
    virtual void v33();                                          // +0xcc
    virtual float FnD0();                                        // +0xd0
virtual void v35();
virtual void v36();
    virtual void SetRequest(const cLocomotionRequest& r);        // +0xdc

    char  mPad04[0x77 - 0x04];                                   // +0x04
    uchar mFlag77;                                               // +0x77
    char  mPad78[0x1e8 - 0x78];                                  // +0x78
    float mTurnRate;                                             // +0x1e8

    Vec3* GetVelocity();                                         // 0x00d20610
    void  GetSteerDirection(Vec3* pOut);                         // 0x00c44080
    cLocomotionRequest* GetRequest();                            // 0x00c41ec0
};
struct cSteerState {
    Vec3        mVelocity;                                       // +0x00
    char        mPad0c[0x10 - 0x0c];                             // +0x0c
    float       mDt;                                             // +0x10
    cSteerLoco* mpObject;                                        // +0x14
};
struct cPlanetModel_s00b4_8110 {
    Quat* BuildSurfaceOrientation2(Quat* pOut, const Vec3* pPos, const Vec3* pUp);  // 0x00b7f250 ret 0xc
    Vec3* DirectionToSurfacePosition(Vec3* pOut, const Vec3* pDir);                 // 0x00b815a0 ret 8
};
extern cPlanetModel_s00b4_8110* __cdecl PlanetModel_s00b4_8110();                      // 0x00b3d350
extern Vec3* __cdecl NormalizedSafe(Vec3* pOut, const Vec3* pIn);// 0x00449c20
extern Quat __cdecl Slerp(const Quat& a, const Quat& b, float t); // 0x005b2500
extern float __stdcall Fn_00b46df0(cSteerLoco* pObj, const Vec3* pTarget, float dt, float fSpeed, float fTurn);  // 0x00b46df0
struct Steering {
    void Update(cSteerState* pState);                            // 0x00b48110 (ret 4)
};
// ---- items of slice s00b48110 end

// ---- items of slice s00b48f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float DAT_0167eb8c;   // 0x167eb8c  invalid-vector sentinel x
extern "C" float DAT_0167eb90;   // 0x167eb90  invalid-vector sentinel y
extern "C" float DAT_0167eb94;   // 0x167eb94  invalid-vector sentinel z
extern "C" int   FUN_00c41ec0();   // 0xc41ec0  __fastcall(this) -> this+0x1f4
extern "C" void  FUN_00b48e00();   // 0xb48e00  __fastcall(this) SteerVec::push_back
extern "C" void* FUN_00d20610();   // 0xd20610  cLocomotiveObject::GetVelocity (fastcall)
extern "C" void* FUN_00436ce0(void*, void*);                  // 0x436ce0  Vector3_Normalize
extern "C" void  FUN_00699800(void*, void*, float, void*, void*); // 0x699800 SegmentPhysics
extern "C" void* FUN_00449c20(void*, void*);                  // 0x449c20  SP::normalized_safe
extern "C" int   FUN_00b3d310();   // 0xb3d310
extern "C" int   FUN_00c0c2f0();   // 0xc0c2f0  fastcall(this) -> this+0xeac
extern "C" int*  FUN_00b41a40();   // 0xb41a40  (thiscall, 2 args)
extern "C" int   FUN_00c03520();   // 0xc03520  (thiscall, 1 arg, ret 4)
extern "C" int   FUN_00c02600();   // 0xc02600  SP::IsValidNeighbourEntry (thiscall, 1 arg, ret 4)
extern "C" void  FUN_00b3d870();   // 0xb3d870  __fastcall(this) -> *this += 4
extern "C" int*  FUN_00c420d0();   // 0xc420d0  __fastcall(this) -> this+0x278
extern "C" int   FUN_00bc96a0();   // 0xbc96a0  PlayIdleAnimation (thiscall, 2 args)
extern "C" int   FUN_00d99980(int); // 0xd99980 SP::GetAnimalFromStimulus
extern "C" void* FUN_00b3d350();   // 0xb3d350  SP::PlanetModel
extern "C" float FUN_00b7e430();   // 0xb7e430  (thiscall, 2 args) -> float
extern "C" void  FUN_00b7ee70();   // 0xb7ee70  (thiscall, 2 args)
extern "C" void  FUN_00b47600();   // 0xb47600  SteerVec::DoInsertValue (thiscall, 2 args)
inline void* VFn(void* o, int byteoff) { return (*(void***)o)[byteoff / 4]; }
// ---- items of slice s00b48f20 end

// ---- items of slice s00b498d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_Mode_1654c05;                     // 0x01654c05
struct C {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
    virtual const V3* GetDirection();           // slot 11  (+0x2c)
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
    virtual void s28();
    virtual float GetRadius();                  // slot 29  (+0x74)
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
virtual void s44();
virtual void s45();
    virtual C* GetComponent(uint32_t id);       // slot 46  (+0xb8)
    virtual void s47();

    int  FUN_00c0c2f0();                        // 0x00c0c2f0 (this->[0xeac])
    bool Flag388();                             // 0x00c0c0e0  ?Flag388@C@@QAE_NXZ

    char     pad04[0xb58 - 0x04];
    uint32_t m_b58;                             // +0xb58  bit 9 = "strategy active" flag
    char     padb5c[0xf90 - 0xb5c];
    char     m_f90;                             // +0xf90
};
__forceinline bool BitTest(const uint32_t* f, int n) { return ((*f >> n) & 1) != 0; }
struct ActionCtx {
    char pad00[0x80];
    C*   m_creature;                            // +0x80
};
struct Found {
    char    pad00[0x34];
    uint8_t m_34;                               // +0x34  bit 0: dead / already ignored
    char    pad35[0x44 - 0x35];
    float   m_44;                               // +0x44  radius
    char    pad48[0x88 - 0x48];
    int     m_88;                               // +0x88  object class
};
template<class T, int N> struct FixedVector {
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator[2];
    int      mBufferHeader;
    T        mBuffer[N];

    __forceinline FixedVector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + N), mBufferHeader(0) {}
    __forceinline ~FixedVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin); }
};
struct Sim { char pad20[0x20]; int m_20; };
Sim* GetSim_s00b4_98d0();                                  // 0x00b3d310
struct ObjectFinder {
    void Query(const V3* dir, void* out, uint32_t mask, float radius, int flag, const V3* p);   // 0x00b79c30
};
ObjectFinder* GetObjectFinder();                // 0x00b3d3c0
void* GetCurrentGameMode_s00b4_98d0();                     // 0x00b5b800
void FUN_00b48f20(ActionCtx* ctx, float a, void* b, float c);   // 0x00b48f20
// ---- items of slice s00b498d0 end

// ---- items of slice s00b4a720 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool gFlag74;          // 0x167eb74
extern "C" void* __cdecl FUN_00921340(int n); // 0x921340
extern "C" bool __stdcall FUN_00b489d0(void* a, void* b, float* delta, float dist,
                                       float* outA, float* outB); // 0xb489d0
extern "C" bool __stdcall FUN_00b45540(void* a, void* b, void* c, void* d, void* e); // 0xb45540
extern "C" void* __cdecl FUN_00b41ea0(void* first, void* last, void* key, unsigned flags); // 0xb41ea0
extern "C" char __cdecl FUN_00b3fc80(void* node); // 0xb3fc80
extern float g_1461150;             // +FLT_MAX
extern float g_13f51ac;             // -FLT_MAX
extern float g_167eb8c, g_167eb90, g_167eb94;
extern float g_1485720;             // 1.0f
struct Vec3_s00b4_a720 {
    float x, y, z;
    Vec3_s00b4_a720() {}
    Vec3_s00b4_a720(float a, float b, float c) { x = a; y = b; z = c; }
    Vec3_s00b4_a720(const Vec3_s00b4_a720& o) { x = o.x; y = o.y; z = o.z; }
};
struct Impulse { float x, y, z; int mode; };
struct Planet {
    bool IsLoaded();                    // 0xb7ec40
    float GetRadiusAt(const Vec3_s00b4_a720* p);   // 0xb7ef70
    float GetWaterHeight();             // 0xb7e390
    float FUN_00b7e490();               // 0xb7e490
    Vec3_s00b4_a720* FUN_00b7e3b0(Vec3_s00b4_a720* out, const Vec3_s00b4_a720* p);  // 0xb7e3b0
};
struct Bounds { float pad0[2]; float lo; float pad1[2]; float hi; };
struct Sim_s00b4_a720 { char pad[0x31]; bool b31; };
struct Component {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual const void* GetType();      // +0x20
};
struct ComponentB : Component { bool FUN_00c232c0(); };
struct Loco {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
    virtual const Vec3_s00b4_a720* GetPosition();                 // +0x2c
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
    virtual Bounds* GetBounds();                       // +0x68
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
    virtual Component* GetComponent(uint32_t id);      // +0xb8
virtual void v47();
virtual void v48();
virtual void v49();
virtual void v50();
    virtual void v51();
    virtual float GetMaxAccel();                       // +0xd0
virtual void v53();
virtual void v54();
virtual void v55();
virtual void v56();
virtual void v57();
virtual void v58();
virtual void v59();
virtual void v60();
    virtual void v61();
    virtual bool IsIdleAnimating();                    // +0xf8

    char pad04[0x50 - 4];
    uint32_t mFlags;                                   // +0x50
    char pad54[0x71 - 0x54];
    char mFlag71;                                      // +0x71
    char pad72[5];
    bool mGrounded;                                    // +0x77
    char pad78[0xf0 - 0x78];
    Impulse* mImpBegin;                                // +0xf0
    Impulse* mImpEnd;                                  // +0xf4
    char padf8[0x1c8 - 0xf8];
    Vec3_s00b4_a720 mVelocity;                                    // +0x1c8
    Vec3_s00b4_a720 mAngVelocity;                                 // +0x1d4
    char pad1e0[0x1f0 - 0x1e0];
    int mPlanetCorrection;                             // +0x1f0
    char pad1f4[0x268 - 0x1f4];
    bool mSelfPowered;                                 // +0x268
    char pad269[0x4cc - 0x269];
    int mStrategy;                                     // +0x4cc

    const Vec3_s00b4_a720* GetVelocity();                         // 0xd20610
    void SetVelocity(const Vec3_s00b4_a720* v);                   // 0xc41d60
    void SetAngularVelocity(const Vec3_s00b4_a720* v);            // 0xc41d90
    void FUN_00c431a0(uint32_t dt);                    // 0xc431a0
};
extern Vec3_s00b4_a720 kZero_s00b4_a720;            // 0x167eb8c
Planet* GetPlanetModel();     // 0xb3d350
Sim_s00b4_a720* GetSim_s00b4_a720();                // 0xb3d310
void* GetUniverseContext();   // 0x1021080
bool FUN_0059ab70(const Vec3_s00b4_a720* v);  // 0x59ab70
void FUN_00b444c0(const Vec3_s00b4_a720* v, Loco* self);  // 0xb444c0
static const void* const kTypeA = (const void*)0x18eb45e;
static const void* const kTypeB = (const void*)0x18eb4b7;
static inline float VelDot(const Vec3_s00b4_a720* v, const Vec3_s00b4_a720& acc, const Vec3_s00b4_a720* pos)
{
    return ((v->x + acc.x) * pos->x + (v->z + acc.z) * pos->z) + (v->y + acc.y) * pos->y;
}
typedef unsigned short u16;
typedef unsigned char  u8;
struct FixedPoolBase {
    void Init(void* buf, unsigned size, unsigned elem, int a, int b); // 0x921260
};
struct PoolDesc {
    void* head;        // +0x00
    int   pad04;       // +0x04
    void* begin;       // +0x08
    void* end;         // +0x0c
    int   elem;        // +0x10
    void* alloc;       // +0x14
};
struct PoolBase {
    int SizeFor(int n); // 0x9213c0
};
struct F2 { float a, b; F2() {} F2(float x, float y) { a = x; b = y; } };
struct B4B060 {
    bool run(void* a1, void* a2, float* a3, float* a4, float f5, float f6,
             void* out); // 0xb4b060
};
struct B4B1D0 {
    int init(void* a, void* b); // 0xb4b1d0
    void FUN_00b41a80(void* h, void* a, void** pb, void** pb2, void* bv,
                      void** pb3, void* desc); // 0xb41a80
    void DoFreeNodes(int n);                   // 0xef7c00
};
struct PairVec {
    int* begin;        // +0x00
    int* end;          // +0x04
    char pad08[0x0c];  // +0x08
    u8   flags14;      // +0x14
    char pad15[3];     // +0x15
    int remove(int* key); // 0xb4b2b0
};
struct Matrix33 { float m[9]; void Assign(const void* src); }; // 0x41cb40
struct Box26 { Vec3_s00b4_a720 lo; Vec3_s00b4_a720 hi; };
struct SphLocal { short s0, s1; float x, y, z, r; };
struct ContactLocals {
    float local5c[3];   // +0x00
    Box26 box;          // +0x0c
    SphLocal sph;       // +0x24
    Matrix33 mtx;       // +0x38
};
struct ContactObj {
    void  FUN_00b3d9c0(void* out); // 0xb3d9c0
    float FUN_00b3d630();          // 0xb3d630
    void  FUN_00b3f420(void* box); // 0xb3f420
    int   FUN_00b3f6c0(void* sph); // 0xb3f6c0
};
struct EventNode {
    u32 f0;            // +0x00
    u32 f4;            // +0x04
    u32 f8;            // +0x08
    char pad0c[0x2c];  // +0x0c
    u32 f38;           // +0x38
};
struct EventMgr {
    char pad00[0x1c];
    int GetPriority();              // 0xe31100
    EventNode* Find(int* key);      // 0xb72230
    void Remove(void* node);        // 0xb72260
};
struct WorldB4 {
    int field00;       // +0x00
    char pad04[4];     // +0x04
    EventMgr mgr;      // +0x08
    PairVec pairs;     // +0x24
    char pad3c[0x7c];  // +0x3c..0xb7
    int fieldB8;       // +0xb8
};
extern u8    g_167ecc4;             // 0x167ecc4
extern float g_167ec08_s00b4_a720;             // matrix source
extern void* g_167eb70_s00b4_a720;             // world pointer cell
// ---- items of slice s00b4a720 end

// ---- items of slice s00b4b590 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* __fastcall FUN_00c797b0(void* c, int edx, void* node, void* val);
extern void* __fastcall FUN_00c72d00(void* c, int edx, void* node, void* val);
extern void  __fastcall FUN_00b48e40(void* c, int edx, void* first, void* last);
extern void* __cdecl  FUN_00b532f0(void* self);
extern void  __cdecl  FUN_00b47730(void* a, void* b, int c, int d, int e, int f);
extern void  __cdecl  FUN_00afc470(void** ref);
extern void  __cdecl  FUN_00b47e00(void* a, void* b, void* c);
extern void  __cdecl  FUN_00b56090(void* a, void* b, void* c, void* d);
extern void  __cdecl  FUN_00b45b50(void* k, void** ref, int flag);
extern float __cdecl  FUN_00b3dcd0(void* o);
extern char  __cdecl  FUN_00b3dd40(void* o);
extern char  __cdecl  FUN_00b3d5f0(void* o);
extern void* __fastcall FUN_00b72160(void* ht);
extern void* __fastcall FUN_00b721d0(void* ht, int edx, void* key);
extern void* __fastcall FUN_00b72210(void* ht, int edx, void* val);
extern void* __fastcall FUN_00b47570(void* ht, int edx, void* out);
extern void* __fastcall FUN_00564a10(void* map, int edx, void* key);  // vector_map::operator[]
extern void* __cdecl  FUN_00bbbe20(void* o, void* key);
extern void  __fastcall FUN_00b4b2b0(void* ht, int edx, void* key);
extern void  __cdecl  FUN_00b43790(void* a, void* b, void* c, float f);
extern void  __cdecl  FUN_00b43990(void* a, void* b, void* c, float f);
extern void  __cdecl  FUN_00b43bc0(void* a, void* b, void* c, float f);
extern void  __cdecl  FUN_00b43d50(void* a, void* b, void* c, float f);
extern void  __cdecl  FUN_00b40a20(void* a, void* b, void* c, float f);
extern void  __cdecl  FUN_00b4b320(void* a, void* b, void* c, float f);
extern char  __fastcall FUN_00b4b060(void* self, int edx, void* a, void* b, void* c, void* d, float f, float g, void* h);
extern void  __cdecl  FUN_00b3e3e0(void* a, void* b, void* c, float f);
extern void  __cdecl  FUN_00b4bc20(void* a, void* b, void* c, void* d, float f, float g);
struct IVtbl { void* slot[0x40]; };
#define VSLOT_s00b4_b590(obj, off) (((IVtbl*)*(void**)(obj))->slot[(off) / 4])
typedef uint  (__fastcall* GetTypeFn)(void* self, int edx);       // vtable +0x20
typedef void* (__fastcall* GetSubFn)(void* self, int edx, uint id); // vtable +0x0c
extern uchar  g_167eb75;        // 0x0167eb75
extern uint   g_167eb88;        // 0x0167eb88
extern uchar  g_1569ab8;        // 0x01569ab8
extern uchar  g_15acb40;        // 0x015acb40
extern uint   g_167eccc;        // 0x0167eccc
extern uint   g_167ecc8;        // 0x0167ecc8
struct Iter { void* node; void* bucket; };
struct HT {
    char   pad0[4];
    void** arr;                 // +0x04
    uint   count;               // +0x08
    void*  f0c;                 // +0x0c
};
struct World70;
extern World70* g_167eb70_s00b4_b590;      // 0x0167eb70
struct World70 {
    uint   f0;                  // +0x00
    void*  f4;                  // +0x04
    char   pad8[0x1c];          // +0x08
    HT     ht24;                // +0x24
    char   pad34[4];            // +0x34
    uchar  f38;                 // +0x38
    char   pad39[0x1f];         // +0x39
    HT     ht58;                // +0x58
    char   pad68[0x10];
    HT     ht78;                // +0x78
    char   pad88[4];
    HT     ht90;                // +0x90
    char   pad9c[0x0c];
    float  a8;                  // +0xa8
    float  ac;                  // +0xac
};
extern uint  __cdecl  FUN_00b3d700(uint a, uint b);
// Prefixes of the two native containers used during world-state cleanup.
struct VectorRange_s00b4_b7b0 {
    void* mpBegin;
    void* mpEnd;
    void Erase(void* first, void* last); // 0x00b48e40: thiscall, ret 8
};
struct HashRange_s00b4_b7b0 {
    uint mAllocator;
    void* mpBuckets;
    uint mnBucketCount;
    uint mnElementCount;
    uint mPoolStorage[9];
    void Clear(void* buckets, uint count); // 0x00b41e20: thiscall, ret 8
};
struct WorldCleanup_s00b4_b7b0 {
    uint mPrefix[0x60 / 4];
    VectorRange_s00b4_b7b0 mObjects;
    uint mMiddle[(0x47c - 0x68) / 4];
    HashRange_s00b4_b7b0 mObjectLookup;
    void Clear();
};
typedef char WorldCleanupVectorOffset_s00b4_b7b0[
    offsetof(WorldCleanup_s00b4_b7b0, mObjects) == 0x60 ? 1 : -1];
typedef char WorldCleanupHashOffset_s00b4_b7b0[
    offsetof(WorldCleanup_s00b4_b7b0, mObjectLookup) == 0x47c ? 1 : -1];

extern uint  __cdecl  FUN_00bbb110(void* o);                   // StarGridCount
extern void  __cdecl  FUN_00b4b910(uint mode);
// ---- items of slice s00b4b590 end

// ---- items of slice s00b4d220 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_oneF;                     // 0x01485720  (1.0f)
extern float g_scale3f;                  // 0x013f6bf8
extern char  g_useSabotage;              // 0x0167ecd8
extern char* g_physObj;                  // 0x0167ecd0
typedef signed   int   i32;
static inline u32  ld32(char* b, u32 off) { return *(u32*)(b + off); }
static inline void st32(char* b, u32 off, u32 v) { *(u32*)(b + off) = v; }
static inline u8   ld8 (char* b, u32 off) { return *(u8*)(b + off); }
static inline void st8 (char* b, u32 off, u8 v) { *(u8*)(b + off) = v; }
static inline float ldf(char* b, u32 off) { return *(float*)(b + off); }
static inline void stf (char* b, u32 off, float v) { *(float*)(b + off) = v; }
struct HkObj {
    void  aef7e0(const float* v);                            // 0x00aef7e0
    float* aef400();                                         // 0x00aef400
    i32*  find961(i32* out, i32 key);                        // 0x00496140 ?Find@D961
    void  c0dd70(const float* dst, float v, const float* src); // 0x00c0dd70
    void  c41d60(const float* v);                            // 0x00c41d60
    float* politicalID();                                    // 0x0097e850 (returns this+0x10)
    void  b4d140();                                          // 0x00b4d140
    void  b72080(int a, int b);                              // 0x00b72080
    void  b4b1d0(char* a, char* b);                          // 0x00b4b1d0
    void  b46ff0();                                          // 0x00b46ff0
    void  b4d930();                                          // 0x00b4d930
    void* gonzagoCtor();                                     // 0x00b5b960

    // Havok factory callees
    void  hkRigidBodyCtor(const void* cinfo);                // 0x010878b0
    void  hkAddEntityListener(const void* l);                // 0x01088c20
    void  hkAddProperty(u32 a, u32 b, u32 c);                // 0x010825a0
    void  hkPhantomCtor(const void* shape, const void* xform, u32 a); // 0x0108c750
    void  hkAddOverlapping(char* c);                         // 0x0108c620
    i32   hk104fa0(int a, int b, int c);                     // 0x01084fa0
};
struct Blk50 { float f[0x14]; void* copyFrom(const void* src); };   // 0x50 bytes, holes at +8,+0xc
// ---- items of slice s00b4d220 end

// ---- items of slice s00b4e1d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_pi;        // 0x01569b18  (3.14159f)
extern float g_third;     // 0x013f26dc  (0.33333334f)
extern float g_three;     // 0x013eb95c  (3.0f)
extern float g_one;       // 0x015695f8  (1.0f)
extern float g_two;       // 0x01470f1c  (2.0f)
extern float g_eps;       // 0x014612dc  (1.5258789e-05f)
extern float g_thr1;      // 0x01569ae8  (1.0f)
extern float g_thr400;    // 0x01569aec  (400.0f)
extern float g_thr10000;  // 0x01569af0  (10000.0f)
extern float g_thr50;     // 0x01569af4  (50.0f)
u32   __cdecl GetSystemAT();                          // 0x00a206f0 EA::Audio::GetSystemAT
u32   __cdecl GetRecorderState();                     // 0x00435e90
void  __cdecl KillSetiEffects(u32 id, u32 state);     // 0x00435ed0 SP::cSPUISpace::KillSetiEffects
void  __cdecl SetGlobalProperty(u32 id, float v);     // 0x005ca880
u32   __cdecl GetCurrentGameMode_s00b4_e1d0();                   // 0x00b5b800 SP::GetCurrentGameMode
u32   __cdecl AudioSystem();                          // 0x0067cb00 SP::AudioSystem
void  __cdecl Simulator_OnEvent(void* info);          // 0x00f31220 Simulator_OnEvent
void  __cdecl FUN_00b4d470(char* dst, char* src);     // 0x00b4d470 repack into a dense record
void  __cdecl FUN_00b4dee0(char* self, u8 flag, float* out); // 0x00b4dee0 capsule/sphere contact
struct HkObj_s00b4_e1d0 {
    i32* find961(i32* out, i32 key);                  // 0x00496140 ?Find@D961
};
typedef float* (__thiscall *FnGetVec)(void* self, int a);
typedef char*  (__thiscall *FnGetByName)(void* self, char* name);
struct hkBool_s00b4_e1d0 {
    u8 b;
    hkBool_s00b4_e1d0();
    hkBool_s00b4_e1d0(const hkBool_s00b4_e1d0&);
    hkBool_s00b4_e1d0& operator=(const hkBool_s00b4_e1d0&);
};
struct hkMatrix3_s00b4_e1d0 {
    hkBool_s00b4_e1d0 isApproximatelyEqual(const hkMatrix3_s00b4_e1d0& other, float eps) const;   // 0x010815a0
};
struct hkShapePhantom {
    void setTransform(const void* xf);                // 0x0108db50
    void setPosition(const float* v, float w);        // 0x0108dbb0
};
struct hkTransform_s00b4_e1d0 { float rot[12]; float tr[4]; };   // column-major hkRotation + hkVector4
struct cCollisionInfo {
    u32   collisionType;      // +0x00
    float data[0x19];         // +0x04 .. +0x67
    void* pGameDataA;         // +0x68
    void* pGameDataB;         // +0x6c
    u8    tail[0xa];          // +0x70 .. +0x79
    cCollisionInfo();         // 0x00b3d8c0
};
extern u32   g_recorder;  // 0x0167ece8
extern u32   g_patchId;   // 0x0167ece4
extern void (__cdecl* g_eventHandler)(void*);  // 0x0167eb88
// ---- items of slice s00b4e1d0 end

// ---- items of slice s00b4ed50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
extern const float kRestThreshold;      // 0x01569ac4
extern bool gUseTangential;             // 0x01569ab9
extern const float kForceScaleA;        // 0x0167eb7c
extern const float kForceScaleB;        // 0x0167eb80
extern const float kTorqueScale;        // 0x0167eb84
extern const float kAabbMargin;                 // 0x01485720
#pragma warning(disable: 4100)
typedef float hkReal;
class __declspec(align(16)) hkVector4_s00b4_ed50 {
public:
    hkReal x, y, z, w;
    hkVector4_s00b4_ed50() {}
    hkVector4_s00b4_ed50(hkReal _x, hkReal _y, hkReal _z, hkReal _w) : x(_x), y(_y), z(_z), w(_w) {}
    hkVector4_s00b4_ed50(const hkVector4_s00b4_ed50& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    void operator=(const hkVector4_s00b4_ed50& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
};
class hkBool_s00b4_ed50 {
public:
    hkBool_s00b4_ed50() {}
    hkBool_s00b4_ed50(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
private:
    char m_bool;
};
static __forceinline hkReal hkSqrtInverse(hkReal r) { return (hkReal)(1.0f / sqrt(r)); }
static __forceinline double LengthXYZ(const hkVector4_s00b4_ed50& v)
{
    return sqrt((double)v.x * v.x + (double)v.y * v.y + (double)v.z * v.z);
}
static __forceinline double LengthXZY(const hkVector4_s00b4_ed50& v)
{
    return sqrt((double)v.x * v.x + (double)v.z * v.z + (double)v.y * v.y);
}
struct hkPropertyValue_s00b4_ed50 {
    union { int i; float f; void* p; };
    int hi;
    hkPropertyValue_s00b4_ed50() {}
};
class hkRigidMotion {
public:
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
    virtual void applyLinearImpulse(const hkVector4_s00b4_ed50& imp);       // slot 24 (+0x60)
    virtual void s25();
    virtual void applyAngularImpulse(const hkVector4_s00b4_ed50& imp);      // slot 26 (+0x68)

    // (hkVector4 members would pad the vptr out to 16 bytes, so address them by offset)
    const hkVector4_s00b4_ed50* position() const { return (const hkVector4_s00b4_ed50*)((const char*)this + 0x40); }
    const hkVector4_s00b4_ed50* velocity() const { return (const hkVector4_s00b4_ed50*)((const char*)this + 0x60); }   // xyz used

    float getMass() const;          // 0x01088270
};
struct Owner {
    char pad00[0xa0];
    hkVector4_s00b4_ed50 m_pending;            // +0xa0  accumulated change (impulse / mass)
    float m_invScale;               // +0xb0
    char padb4[0xc8 - 0xb4];
    bool m_flagC8;                  // +0xc8
    char padc9[3];
    int m_intCC;                    // +0xcc

    const hkVector4_s00b4_ed50* GetPending();                  // 0x00aef400 (returns this + 0xa0)
    void AddImpulse(const hkVector4_s00b4_ed50* v);            // 0x00aef570
};
class hkEntity_s00b4_ed50 {
public:
    char pad00[0x4c];
    int m_propBase;                 // +0x4c
    int m_propCount;                // +0x50
    char pad54[4];
    hkRigidMotion* m_motion;        // +0x58
    char pad5c[0x99 - 0x5c];
    bool m_flag99;                  // +0x99

    hkPropertyValue_s00b4_ed50 getProperty(uint32_t key) const;    // 0x00496140
    hkBool_s00b4_ed50 isActive() const;                            // 0x01088ac0
    void activate();                                    // 0x01088ae0
};
struct Aabb { float v[6]; };       // min xyz, max xyz
class Loco_s00b4_ed50 {
public:
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
    virtual Bounds* GetBounds();                    // slot 26 (+0x68)
    virtual const Aabb* GetAabb(Aabb* out);         // slot 27 (+0x6c)

    char pad04[0x75 - 4];
    bool m_flag75;                  // +0x75
    char pad76;
    bool m_grounded;                // +0x77

    float FUN_00c887c0();           // 0x00c887c0
};
struct GoalState { char pad[0x5c]; int m_value; };
struct GoalHolder { GoalState* FUN_00c41ec0(); };       // 0x00c41ec0
struct Sim_s00b4_ed50 { char pad[0x26]; bool b26; };
Sim_s00b4_ed50* __cdecl GetSim_s00b4_ed50();                                  // 0x00b3d310
struct Planet_s00b4_ed50 { float GetRadiusAt(const hkVector4_s00b4_ed50* p); };   // 0x00b7ef70
Planet_s00b4_ed50* __cdecl GetPlanetModel_s00b4_ed50();                       // 0x00b3d350
bool __cdecl FUN_00b4ec70(hkVector4_s00b4_ed50* out, float a, float b, float c, const hkVector4_s00b4_ed50* dir, float d);
const hkVector4_s00b4_ed50* __cdecl FUN_00b658c0(hkVector4_s00b4_ed50* out, hkEntity_s00b4_ed50* e);   // 0x00b658c0
const hkVector4_s00b4_ed50* __cdecl FUN_00b65950(hkVector4_s00b4_ed50* out, hkEntity_s00b4_ed50* e);   // 0x00b65950
class hkMemoryManager {
public:
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
    virtual void* allocate(int nbytes, int align);              // slot 4 (+0x10)
    virtual void  deallocate(void* p, int nbytes, int tag);     // slot 5 (+0x14)
};
extern hkMemoryManager* gMemoryManager;         // 0x016e4178
struct Vector3_s00b4_ed50 { float x, y, z; };
extern Vector3_s00b4_ed50 gPerpBase;                       // 0x0167ecf4
class hkWorld_s00b4_ed50 {
public:
    char pad00[0x84];
    void* m_array;                              // +0x84
    char pad88[4];
    void* m_broadphase;                         // +0x8c
    void addAabb(const hkVector4_s00b4_ed50* aabb);        // 0x01083ff0
    void touch(const hkVector4_s00b4_ed50* a, const hkVector4_s00b4_ed50* b);   // 0x01083ff1 (never called)
    void removeEntity(char* flag, void* obj);   // 0x01083110
};
class hkRefObject {
public:
    void* mVtable;                              // +0x00
    unsigned short mSizeAndFlags;               // +0x04
    unsigned short mRefCount;                   // +0x06
    hkWorld_s00b4_ed50* mWorld;                            // +0x08

    void removeReference();                     // 0x0109ae60
    void baseDtor();                            // 0x0108c790
    void* scalarDtor(int flags);
};
extern hkRefObject* gRegistered_167ecd4;        // 0x0167ecd4
struct ListenerRef {            // arg->mRef
    char pad00[0x10];
    int  mEntityOffset;         // +0x10  self-relative offset of the entity
    char pad14[4];
    char mActive;               // +0x18  must be 1
};
struct ListenerArg {
    hkEntity_s00b4_ed50* mEntity;          // +0x00
    ListenerRef* mRef;          // +0x04
    char mEnabled;              // +0x08
};
struct EntityLink { char pad00[0xc]; hkEntity_s00b4_ed50* mLinked; };   // hkEntity +0x0c
class ListOwner {
public:
    void append(void* p);       // 0x00aef2c0
    void remove(void* p);       // 0x00aef2d0
};
class hkPerpVectors {
public:
    void* mVtable;                              // +0x00
    unsigned short mSizeAndFlags;               // +0x04
    unsigned short mRefCount;                   // +0x06
    unsigned int mFlags;                        // +0x08
    float mScale;                               // +0x0c
    hkVector4_s00b4_ed50 mA;                               // +0x10
    hkVector4_s00b4_ed50 mB;                               // +0x20
    hkPerpVectors(const hkVector4_s00b4_ed50& a, const hkVector4_s00b4_ed50& b, float scale);   // 0x010c2730
};
struct Mat50 {
    float m0;                                   // +0x00
    float m4;                                   // +0x04
    char pad08[8];
    float m16[16];                              // +0x10
    void CopyFrom(const Mat50& src);            // 0x00b4d3f0
};
struct Inner {
    int m0;                                     // +0x00
    int m4;                                     // +0x04
    int m8;                                     // +0x08
    int mC;                                     // +0x0c
    float m10;                                  // +0x10
    int m14;                                    // +0x14
    int m18;                                    // +0x18
    char pad1c[4];
    Mat50 mH;                                   // +0x20
    int m70;                                    // +0x70

    Inner() {}
    Inner(const Inner& src);
};
struct Key3 { int m0, m4, m8; };
class Outer {
public:
    int m0;                                     // +0x00
    int m4;                                     // +0x04
    int m8;                                     // +0x08
    char pad0c[4];
    Inner mInner;                               // +0x10
    Outer(const Key3& key, const Inner& inner);
};
struct RenderCfg {
    int mModeA;                                 // +0x00 (0x01569af8) = 4
    int mModeB;                                 // +0x04 (0x01569afc) = 2
    float mScale;                               // +0x08 (0.3)
    float mBias;                                // +0x0c (0.05)
    float mLimit;                               // +0x10 (10)
};
extern RenderCfg gRenderCfg;                    // 0x01569af8
struct FlagWord { char pad00[4]; unsigned int mFlags; };    // +0x04
int __cdecl FUN_00b65250(void* obj, int mode, float value, int index);   // 0x00b65250
int __cdecl FUN_00b653d0(void* obj, int mode, float value, int index);   // 0x00b653d0
struct Node90 {
    unsigned int mKey0;                         // +0x00
    unsigned int mKey4;                         // +0x04
    char pad08[0x88];
    Node90* mNext;                              // +0x90
};
struct LinkNode {
    unsigned int mKey0;                         // +0x00
    unsigned int mKey4;                         // +0x04
    unsigned int mKey8;                         // +0x08
    char pad0c[0x84];
    LinkNode* mNext;                            // +0x90
};
struct Bucket90 { Node90* mHead; };
struct It90 { Node90* mNode; Bucket90* mBucket; };
class Table90 {
public:
    char pad00[0xc];
    int mCount;                                 // +0x0c
    It90 erase(Node90* node, Bucket90* bucket);
};
struct Node10 {
    unsigned int mKey0;                         // +0x00    unsigned int mKey4;                         // +0x04
    unsigned int mKey8;                         // +0x08
    unsigned int mKeyC;                         // +0x0c
    Node10* mNext;                              // +0x10
};
struct Bucket10 { Node10* mHead; };
struct It10 { Node10* mNode; Bucket10* mBucket; };
class Table10 {
public:
    char pad00[0xc];
    int mCount;                                 // +0x0c
    It10 erase(Node10* node, Bucket10* bucket);
};
struct NodeB {
    unsigned int mHash0;                        // +0x00
    unsigned int mHash4;                        // +0x04
    char pad08[4];
    NodeB* mNext;                               // +0x0c
};
class TableB {
public:
    char pad00[4];
    NodeB** mBuckets;                           // +0x04
    unsigned int mNumBuckets;                   // +0x08
    int mCount;                                 // +0x0c
    char pad10[0xc];
    NodeB* mFreeList;                           // +0x1c
    char pad20[4];
    char* mHeapLo;                              // +0x24
    char* mHeapHi;                              // +0x28
    char pad2c[4];
    void* mStatic;                              // +0x30

    NodeB** reserveBuckets(unsigned int n);     // 0x00c763d0
    void rehash(unsigned int n);
};
struct PropHolder_s00b4_ed50 {
    char pad00[0x80];
    float mVecX;                                // +0x80
    float mVecY;                                // +0x84
    float mVecZ;                                // +0x88
    float mVecW;                                // +0x8c
    char pad90[4];
    float mPropA;                               // +0x94
    float mPropB;                               // +0x98
    float mPropC;                               // +0x9c
    float mPropD;                               // +0xa0
    char padA4[0xc];
    signed char mFlag;                          // +0xb0
};
float __cdecl SP_GetPropertyFloat(void* set, unsigned int key, float def);      // 0x004e1c70
int   __cdecl SP_GetPropertyChar(void* set, unsigned int key, int def);         // 0x004e1c30
bool  __cdecl SP_GetPropertyAsVector3(void* set, unsigned int key, Vector3_s00b4_ed50* out);  // 0x006a1110
// ---- items of slice s00b4ed50 end

// ---- items of slice s00b4fd80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_167ece4;   // 0x0167ece4
extern float    g_1569ae8;   // 0x01569ae8
extern float    g_1569aec;   // 0x01569aec
extern float    g_1569af0;   // 0x01569af0
extern float    g_1569af4;   // 0x01569af4
extern void* g_vtblFB0;         // 0x01461390
extern const float kNeg200;     // 0x0146138c = -200.0f
extern const float kPos200;     // 0x01477fbc = 200.0f
struct Variant {
    int            mData;    // +0x00 (pointer when flags & 0x30)
    char           pad04[0xc];
    unsigned char  mFlags;   // +0x10
    char           pad11;
    short          mType;    // +0x12
};
struct IVarHost {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual void v8();
    virtual bool GetProp(unsigned id, Variant** out);   // +0x24
};
static __forceinline int ReadIntProp(IVarHost* obj, unsigned id, int def)
{
    if (obj) {
        Variant* v;
        if (obj->GetProp(id, &v)) {
            short t = v->mType;
            if (t == 10 || t == 0x10) {
                if (v->mFlags & 0x30) return *(int*)v->mData;
                return *(int*)(v ? v : 0);
            }
        }
    }
    return def;
}
static __forceinline float ReadFloatProp(IVarHost* obj, unsigned id, float def)
{
    if (obj) {
        Variant* v;
        if (obj->GetProp(id, &v)) {
            short t = v->mType;
            if (t == 0xd || t == 0x10) {
                if (v->mFlags & 0x30) return *(float*)v->mData;
                return *(float*)(v ? v : 0);
            }
        }
    }
    return def;
}
struct RC {
    virtual void Release(int);   // +0x00
    int   mRef;                  // +0x04
};
struct IChildSrc {
virtual void c0();
virtual void c1();
virtual void c2();
    virtual void* GetChild();    // +0x0c
};
struct RCNode {
    char  pad24[0x24];
    IChildSrc* m24;              // +0x24
};
struct RC2 : RC {
    char  pad08[0x1c];
    RCNode* m24;                 // +0x24
};
static __forceinline void AssignRC(RC** slot, RC* np)
{
    RC* old = *slot;
    if (np != old) {
        if (np) np->mRef++;
        *slot = np;
        if (old) {
            if (--old->mRef == 0) {
                old->mRef = 1;
                old->Release(1);
            }
        }
    }
}
struct ChildObj {
    virtual void v0();
    char  pad04[4];
    RC*   m08;                  // +0x08
    RC*   m0c;                  // +0x0c
    int   m10;
    char  pad14[0x20];
    float f34;                  // +0x34
    float f38;                  // +0x38
};
struct ObjFFB0 : RC2 {
    void* ctor(RC* param);      // 0x00b4ffb0
};
// ---- items of slice s00b4fd80 end

// @ 0x00b40a20
void CollideSphereShape_00b40a20(Geom* a, Geom* b, Contact* out)
{
	Vec3 ca, cb;
	a->GetCenter(&ca);
	b->GetCenter(&cb);
	float rA = a->GetRadius();
	float rB = b->GetRadius();

	Vec3 d;
	d.x = cb.x - ca.x;
	d.y = cb.y - ca.y;
	d.z = cb.z - ca.z;
	float sum = rB + rA;
	float distSq = (d.x * d.x + d.z * d.z) + d.y * d.y;
	if (!(sum * sum > distSq))
		return;

	Vec3 pt;
	pt.x = d.x;
	pt.y = d.y;
	pt.z = d.z;
	char hullFlag = 1;
	if (b->m_type == 0)
		hullFlag = b->m_data->m_isPolygon;
	else if (b->m_type == 1)
		hullFlag = b->m_data->m_isPolygon;
	bool useHull = hullFlag != 0;

	if (useHull)
	{
		Hull* hull = b->GetHull();
		if (hull && (unsigned)(hull->m_end - hull->m_begin) >= 3)
		{
			cSPTransform_s00b4_0a20 t;
			b->GetTransform(&t);
			t.mScale = 1.0f;
			t.mModificationCount++;
			pt.x = ca.x;
			pt.y = ca.y;
			pt.z = ca.z;
			t.BackTransformPoint(&pt);
			float ptz = pt.z;
			{
				BoundingBox box;
				b->GetBoundingBox(&box);
				if (ptz > box.max.z - box.min.z)
					return;
			}

			pt.z = 0.0f;
			Vec3& prev = cb;   // B's centre is dead on this path (every exit below returns)
			prev.x = hull->m_begin[0].x;
			prev.y = hull->m_begin[0].y;
			prev.z = hull->m_begin[0].z;
			int n = hull->m_end - hull->m_begin;
			float best = FLT_MAX;
			int bestIdx = 0;
			for (int i = 1; i < n; i++)
			{
				const Vec3* cur = hull->m_begin + i;
				float dist = SegmentDistance_00698b30(&pt, &prev, cur);
				if (dist < best)
				{
					best = dist;
					bestIdx = i;
				}
				prev = *cur;
			}
			if (bestIdx == 0 || !(rA > best))
				return;

			const Vec3* edgeEnd = hull->m_begin + bestIdx;
			Vec3 closest;
			ClosestPointOnSegment_00698e00(&closest, &pt, edgeEnd - 1, edgeEnd);
			{
				Vec3 diff;
				diff.x = closest.x - pt.x;
				diff.y = closest.y - pt.y;
				diff.z = closest.z - pt.z;
				NormalizedSafe_00449c20(&d, &diff);
			}
			float pen = rA - best;
			if (PointInPolygon_0069a050(hull->m_begin, hull->m_end - hull->m_begin, &pt))
			{
				d.x = d.x * -1.0f;
				d.y = d.y * -1.0f;
				d.z = d.z * -1.0f;
				pen = best;
			}
			t.TransformVector(&d);

			float depth = rA - pen;
			out->m_pointA[0].x = d.x * depth + ca.x;
			out->m_pointA[0].y = d.y * depth + ca.y;
			out->m_pointA[0].z = d.z * depth + ca.z;
			out->m_pointB[0] = out->m_pointA[0];
			out->m_normal = d;
			out->m_count = 1;
			out->m_separation.x = out->m_normal.x * pen;
			out->m_separation.y = out->m_normal.y * pen;
			out->m_separation.z = out->m_normal.z * pen;
			out->m_zero = 0.0f;
			return;
		}
	}

	float dist = (float)sqrt((double)distSq);
	float pen = sum - dist;
	float inv = 1.0f / (dist + 1.5258789e-05f);
	Vec3 n;
	n.y = d.y * inv;
	n.z = d.z * inv;
	n.x = inv * d.x;
	float depthA = rA - pen;
	out->m_pointA[0].x = n.x * depthA + ca.x;
	out->m_pointA[0].y = n.y * depthA + ca.y;
	out->m_pointA[0].z = n.z * depthA + ca.z;
	float depthB = rB - pen;
	out->m_pointB[0].x = cb.x - n.x * depthB;
	out->m_pointB[0].y = cb.y - n.y * depthB;
	out->m_pointB[0].z = cb.z - n.z * depthB;
	out->m_normal = n;
	out->m_count = 1;
	out->m_separation.x = out->m_normal.x * pen;
	out->m_separation.y = out->m_normal.y * pen;
	out->m_separation.z = out->m_normal.z * pen;
	out->m_zero = 0.0f;
}

// @ 0x00b41020
void FUN_00b41020()
{
	PropListPtr bag;
	bag.mp = 0;
	if (PropertyManager()->GetPropertyList(0x93e8e9b7, bag.AsOutParam()))
	{
#define READPROP(key, dst) \
	if (!bag.mp) return; \
	{ Property* p; if (bag.mp->GetProperty(key, &p) && p->type == 13) dst = *p->GetFloat(); }
	READPROP(0x319c4a93u, g_156964c)
	READPROP(0x119c4ad5u, g_1569650)
	READPROP(0x519c4ad7u, g_1569654)
	READPROP(0x519c4ad9u, g_156965c)
	READPROP(0xd19da711u, g_15695f0)
	READPROP(0x31b02eeau, g_15695f4)
	READPROP(0xd1b02eecu, g_1569678)
	READPROP(0x51d13278u, g_1569680)
	READPROP(0x31d2512fu, g_1569684)
	READPROP(0x11d27e35u, g_1569688)
	READPROP(0x11d39e51u, g_156968c)
	READPROP(0x11d3a085u, g_1569690)
	READPROP(0xb1d3a61bu, g_1569694)
#undef READPROP
	}
}

// @ 0x00b41390
void CapsuleShape::LoadSphereTuning(IPropertyList* list)
{
	LoadPlanetTuning(list);
	CapsuleConstant();
	Property* p;
	m_b31 = (list && list->GetProperty(0x21859677u, &p)) ? *p->GetBool() : false;
	m_b32 = 1;
	g_pTuning->fA8 = (list && list->GetProperty(0xc03f2383u, &p)) ? *p->GetFloat() : g_hkRealOne;
	g_pTuning->fAC = (list && list->GetProperty(0xa098ae0au, &p)) ? *p->GetFloat() : g_013eb960;
	g_pTuning->fB0 = (list && list->GetProperty(0xfb8c381cu, &p)) ? *p->GetFloat() : 0.0f;
	g_pTuning->iB8 = (list && list->GetProperty(0x96b2b086u, &p)) ? *p->GetInt() : 10;
	g_pTuning->fB4 = (list && list->GetProperty(0x182b28dau, &p)) ? *p->GetFloat() : g_01470f1c;
	g_f15695fc = (list && list->GetProperty(0x45b2dc22u, &p)) ? *p->GetFloat() : g_013ec4d0;
	g_f167eb78 = (list && list->GetProperty(0x85a22616u, &p)) ? *p->GetFloat() : 0.0f;
	g_f15695f8 = (list && list->GetProperty(0xb06ebb0eu, &p)) ? *p->GetFloat() : 0.0f;
	g_f167eb7c = (list && list->GetProperty(0x1cd0a1fu, &p)) ? *p->GetFloat() : g_hkRealOne;
	g_f167eb80 = (list && list->GetProperty(0xd087a9d6u, &p)) ? *p->GetFloat() : g_hkRealOne;
	g_f167eb84 = (list && list->GetProperty(0xaf48a431u, &p)) ? *p->GetFloat() : g_hkRealOne;
	g_f1569648 = (list && list->GetProperty(0x617d0eeau, &p)) ? *p->GetFloat() : g_013f1cac;
}

// @ 0x00b41900
int RaycastFanCaster::CastFanTriangle(const float* fan, void* a2, void* a3, void* a4, Vector3* out, const Vector3* contacts)
{
    int nContacts = 0;
    if (!CastFan(fan, a2, a3, a4, contacts, &nContacts))
        return 0;

    Vector3 normal;
    TriangleNormal(&normal, (const Vector3*)fan, (const Vector3*)(fan + 3),
                   *(const Vector3*)(fan + 6));

    float d0 = fan[1] * normal.y + fan[2] * normal.z;
    d0 += fan[0] * normal.x;

    const Vector3* in = contacts;
    for (int i = 0; i < nContacts; i++) {
        Vector3 p = in[i];
        float d = (p.z * normal.z + p.y * normal.y) + p.x * normal.x - d0;
        out[i].x = p.x - d * normal.x;
        out[i].y = p.y - d * normal.y;
        out[i].z = p.z - d * normal.z;
    }
    return nContacts;
}

// @ 0x00b41a40
NearIter::NearIter(const NearRange& range, bool)
{
    mpCurrent = range.mpBegin;
    mpEnd = range.mpEnd;
    if (mpCurrent != mpEnd && !mFilter.IsValid(*mpCurrent))
        Advance();
}

// @ 0x00b41c80
HashTable::HashTable(const HashTable& other)
{
    m0 = other.m0;
    mnBucketCount = other.mnBucketCount;
    mnElementCount = other.mnElementCount;
    m10 = other.m10;
    m14 = other.m14;
    m18 = other.m18;
    if (mnElementCount != 0) {
        unsigned size = mnBucketCount * 4;
        HNode* buckets =
            (HNode*)EAAllocate(
                size + 4, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        memset(buckets, 0, size);
        ((uint32_t*)buckets)[size / 4] = 0xffffffff;
        mpBucketArray = (HNode**)buckets;
        for (uint32_t i = 0; i < other.mnBucketCount; i++) {
            HNode** link = &mpBucketArray[i];
            for (HNode* src = other.mpBucketArray[i]; src; src = src->mpNext) {
                HNode* node =
                    (HNode*)EAAllocate(
                        0xc, "Simulator", 0, 0,
                        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                        0xd1);
                if (node) {
                    node->mKey = src->mKey;
                    node->mpValue = src->mpValue;
                    if (node->mpValue)
                        ((RefObj*)node->mpValue)->AddRef();
                    node->mpNext = 0;
                }
                *link = node;
                link = &node->mpNext;
            }
        }
    } else {
        mnBucketCount = 1;
        mpBucketArray = (HNode**)&g_emptyBucketArray;
        mnElementCount = 0;
        m18 = 0;
    }
}

// @ 0x00b41dc0
PoolNode* Pool::NewNode(Obj** ppObj)
{
    PoolNode* node = mpFreeList;
    if (node)
        mpFreeList = (PoolNode*)node->mpObject;
    else
        node = (PoolNode*)EAAllocate(
            mNodeSize, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    if (node) {
        Obj* pObj = *ppObj;
        node->mpObject = pObj;
        if (pObj)
            ((V46*)pObj)->AddRef();
    }
    node->mpNext = 0;
    return node;
}

// @ 0x00b41e20
void Pool::FreeBuckets(PoolNode** buckets, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++) {
        PoolNode* node = buckets[i];
        while (node) {
            PoolNode* next = node->mpNext;
            if (node->mpObject)
                ((V47*)node->mpObject)->Release();
            if (node != mpSentinel) {
                if (node >= mpBegin && node < mpEnd) {
                    node->mpObject = mpFreeList;
                    mpFreeList = node;
                } else {
                    operator_delete(node);
                }
            }
            node = next;
        }
        buckets[i] = 0;
    }
}

// @ 0x00b41ea0
KeyPair* LowerBoundPair(KeyPair* begin, KeyPair* end, const int* pKey)
{
    int count = (int)(end - begin);
    if (count > 0) {
        do {
            int half = count >> 1;
            if (begin[half].mKey < *pKey) {
                begin += half + 1;
                count += -1 - half;
            } else {
                count = half;
            }
        } while (count > 0);
    }
    return begin;
}

// @ 0x00b41ee0
uint32_t GetMessageValue(cCreatureBase* self, cMessageContext* pContext)
{
    if (!pContext)
        return 0;

    uint32_t defaultValue = pContext->mDefaultValue;
    const MsgTable* pTable = &pContext->mTable;
    uint32_t key = 0;

    switch (self->GetMessageId()) {
    case 0x2a8fb3f:
        key = ((self->GetMessageId() == 0x2a8fb3f) ? self : 0)->GetValue114();
        break;

    case 0x18c8f0c:
        if (!FindProperty(self, 0x18c8f0c)->GetFlag58())
            defaultValue = 0;
        break;

    case 0x18c6de8:
        switch (FindProperty(self, 0x18c6de8)->mValueB1c) {
        case 0:
            key = 0x28346586;
            break;
        case 1:
            key = 0x9e3c3dfa;
            break;
        case 2:
            key = 0x3e9c273b;
            break;
        }
        break;

    case 0x18c88e4: {
        cSPProperty* pProp = FindProperty(self, 0x18c88e4);
        if (pProp->mFlags38)
            key = HashName(&pProp->mName34);
        else if (pProp->m228 == 0x5d97f762)
            key = 0x5d97f762;
        else
            defaultValue = 0;
        break;
    }

    case 0x18eb45e:
        if ((FindProperty(self, 0x18eb45e)->mFlagsB58 >> 9) & 1)
            if (GetCurrentGameMode() == 0x1654c05)
                key = 0xd8c67022;
        break;

    case 0x3a2511e: {
        cCreatureBase* p = (self->GetMessageId() == 0x3a2511e) ? self : 0;
        if (p->mPtr134) {
            pTable = &GetPropertyRegistry()->GetMessageSource(0x18c88e4)->mTable;
            key = HashName(&p->mName130);
        } else {
            key = p->GetValue114();
            if (key == 0) {
                switch (p->mType110) {
                case 1:
                    key = 0xe1c134a8;
                    break;
                case 2:
                    key = 0x67fe5dc7;
                    break;
                case 3:
                    key = 0x6b7a9a63;
                    break;
                case 6:
                    key = 0x713c33f8;
                    break;
                case 7:
                    key = 0x2081b4f5;
                    break;
                }
            }
        }
        break;
    }

    case 0x629bafe:
        if (!CastObject(FindProperty(self, 0x629bafe)->mpObject10c))
            defaultValue = 0;
        break;

    case 0x52aa6122:
        if (GetPropertyRegistry()->m20)
            defaultValue = 0;
        break;
    }

    MsgTableIter it;
    pTable->find(&it, key);
    if (it.mpNode != pTable->End())
        return it.mpNode->mValue;
    return defaultValue;
}

// @ 0x00b421b0
void UpdateRangedAttacks(cAttackCreature* self, bool bActive, const Vector3* pPos, const void* pQuat)
{
    uint32_t flags = self->mFlags50;
    bool bWasActive = (flags & 0x1000) == 0x1000;
    if (!bActive) {
        self->mFlags50 = flags & ~0x1000u;
        return;
    }
    self->mFlags50 = flags | 0x1000;
    if (bWasActive)
        return;

    float height = GetActivePlanet()->GetLavaSomething();
    float threshold = GetTerraformTuning()->GetLavaThreshold();
    if (height > threshold)
        return;

    AttackObject* pAttack = self->GetAttack(0xce9f6639);
    if (!self->HasAttack() || !pPos || !pQuat ||
        (pAttack != 0 && pAttack->mFlagF90 == 0))
        goto done;

    if (GetTerraformHeightObj()->GetTerraformHeight(pPos, true) <= g_lavaScale)
        goto done;

    {
        cEffectsManager* pManager = GetEffectsManager();
        void* pEffect = 0;
        uint32_t* pArg = (uint32_t*)AsPPTypeParam(&pEffect);
        if (!pManager->Use(0x7484a8e4, 0, pArg))
            goto done;

        XformMsg msg;
        XformMsgCtor(&msg);
        msg.SetTarget(*pPos);
        Matrix3FromQuaternion(&msg.mRotation, pQuat);
        msg.mHeader.mFlags |= 2;
        msg.mHeader.mModCount++;
        msg.mScale = self->GetScale();
        msg.mHeader.mModCount++;
        cEffectHost* pTarget = (cEffectHost*)pEffect;
        pTarget->ReceiveMessage(&msg);
        pTarget->Apply(0);
    }

done:
    if (pAttack)
        pAttack->Release();
}

// @ 0x00b42370
void CollisionShape::GetWorldPoints(Vector3* a, Vector3* b)
{
    cSPTransform_s00b4_1900 xform;
    GetTransform(&xform);
    *a = mLocalPointA;
    *b = mLocalPointB;
    if (xform.mFlags & cSPTransform_s00b4_1900::kFlagRotation) {
        *a = *a * xform.mRotation;
    }
    *a = *a * xform.mScale + xform.mTranslation;
    if (xform.mFlags & cSPTransform_s00b4_1900::kFlagRotation)
        *b = *b * xform.mRotation;
    *b = *b * xform.mScale + xform.mTranslation;
}

// @ 0x00b425b0
void CollisionShape::ProjectDirection(const Vector3& dir, float* centerDot, float* extent)
{
    Vector3 center;
    GetCenter(&center);

    BoundingBox_s00b4_1900 box;
    box.lower.x = FLT_MAX;
    box.lower.y = FLT_MAX;
    box.lower.z = FLT_MAX;
    box.upper.x = -FLT_MAX;
    box.upper.y = -FLT_MAX;
    box.upper.z = -FLT_MAX;
    AddToBoundingBox(&box);

    float fx = (box.upper.x - box.lower.x) * h * 0.5f;
    float fy = (box.upper.y - box.lower.y) * h * 0.5f;
    float fz = (box.upper.z - box.lower.z) * h * 0.5f;
    if (mShapeType != 2) {
        float r = GetRadius();
        fx = r;
        fy = r;
        fz = r;
    }
    Vector3 ext(fx, fy, fz);

    *centerDot = Dot(dir, center);
    float ex = fabs(Dot(mAxes[2], dir)) * ext.x;
    float ey = fabs(Dot(mAxes[0], dir)) * ext.y;
    float ez = fabs(Dot(mAxes[1], dir)) * ext.z;
    *extent = (float)((ex + ey) + ez);
}

// @ 0x00b42760
int CollisionShape_s00b4_2760::GetSupportFeature(const Vector3_s00b4_2760& dir, Vector3_s00b4_2760* out, CollisionShape_s00b4_2760* other)
{
    if (mShapeType != 0 && mShapeType != 1) {
        const Vector3_s00b4_2760* kCorners = UnitCubeCorners();
        Vector3_s00b4_2760 center;

        BoundingBox_s00b4_2760 box;
        box.lower.x = FLT_MAX;
        box.lower.y = FLT_MAX;
        box.lower.z = FLT_MAX;
        box.upper.x = -FLT_MAX;
        box.upper.y = -FLT_MAX;
        box.upper.z = -FLT_MAX;
        AddToBoundingBox(&box);
        Vector3_s00b4_2760 ext = (box.upper - box.lower) * 0.5f;
        float halfExt[3];
        halfExt[0] = ext.x;
        halfExt[1] = ext.y;
        halfExt[2] = ext.z;

        GetCenter(&center);

        float dots[3];
        int i;
        for (i = 0; i < 3; i++) {
            float d = Dot_s00b4_2760(mAxes[i], dir);
            dots[i] = d;
            if (fabsf(d) > 0.9999f) {
                // face
                int face;
                if (0.0f > d)
                    face = i * 2;
                else
                    face = i * 2 + 1;
                for (int k = 0; k < 4; k++) {
                    const Vector3_s00b4_2760& c = kCorners[kBoxFaceCorners[face][k]];
                    Vector3_s00b4_2760 v(-(ext.x * c.x), -(ext.y * c.y), -(ext.z * c.z));
                    out[k] = center + mAxes[0] * v.x + mAxes[1] * v.y + mAxes[2] * v.z;
                }
                return 4;
            }
        }

        for (i = 0; i < 3; i++) {
            if (fabsf(dots[i]) < 0.0026f) {
                // edge along axis i
                int j = (i + 1) % 3;
                int k = (i + 2) % 3;
                float vk = -(halfExt[k] * (0.0f > dots[k] ? -1.0f : 1.0f));
                float vj = -(halfExt[j] * (0.0f > dots[j] ? -1.0f : 1.0f));
                Vector3_s00b4_2760 p = center + mAxes[j] * vj + mAxes[k] * vk;
                Vector3_s00b4_2760 half = mAxes[i] * -halfExt[i];
                out[0] = p + half;
                out[1] = p - half;
                return 2;
            }
        }

        // corner
        float vz = -(ext.z * (0.0f > dots[2] ? -1.0f : 1.0f));
        float vy = -(ext.y * (0.0f > dots[1] ? -1.0f : 1.0f));
        float vx = -(ext.x * (0.0f > dots[0] ? -1.0f : 1.0f));
        *out = center + mAxes[0] * vx + mAxes[1] * vy + mAxes[2] * vz;
        return 1;
    }

    // sphere: the point of this sphere towards the other shape's center
    {
        Vector3_s00b4_2760 a;
        GetCenter(&a);
        Vector3_s00b4_2760 b;
        other->GetCenter(&b);
        Vector3_s00b4_2760 d = b - a;
        float invLen = 1.0f / sqrtf(d.x * d.x + d.y * d.y + d.z * d.z + 1e-8f);
        Vector3_s00b4_2760 n(invLen * d.x, d.y * invLen, d.z * invLen);
        float r = GetRadius();
        *out = n * r + a;
        return 1;
    }
}

// @ 0x00b43290
void X::FUN_00b43290()
{
    void* self = this;
    float la8, la4, la0, l9c, l98, l94, l90, l8c, l88;      // basis A (FUN_00b3f3a0)
    float l80, l7c, l78, l74, l70, l6c, l68, l64, l60, l5c, l58, l54, l50, l4c, l84;
    float l48, l44, l40, l3c, l38, l34, l30, l2c, l28;
    float l24[5];
    float l10, lc, l8, l4;
    float f1, f2, f3, f8, f9, f10, f11, f12, f13;

    FUN_00b3f3a0(self, &la8);
    FUN_004fc990(&l70, &la8, &l80);

    l4c = *(float*)((char*)self + 0x68);
    f1  = *(float*)((char*)self + 0x5c);
    l80 = *(float*)((char*)self + 0x74);
    l7c = *(float*)((char*)self + 0x6c);
    f9  = (f1 * la8 + l4c * la4) + l80 * la0;
    f2  = *(float*)((char*)self + 0x78);
    l84 = *(float*)((char*)self + 0x70);
    l78 = *(float*)((char*)self + 0x60);
    f11 = (l78 * la8 + l7c * la4) + f2 * la0;
    f3  = *(float*)((char*)self + 0x7c);
    l74 = *(float*)((char*)self + 0x64);
    f12 = (l74 * la8 + l84 * la4) + f3 * la0;
    f10 = (f1 * l9c + l4c * l98) + l80 * l94;
    f13 = (l78 * l9c + l7c * l98) + f2 * l94;
    l10 = (l74 * l9c + l84 * l98) + f3 * l94;
    lc  = (f1 * l90 + l4c * l8c) + l80 * l88;
    l8  = (l78 * l90 + l7c * l8c) + f2 * l88;
    l4  = (l74 * l90 + l84 * l8c) + f3 * l88;

    l48 = (f11 * l64 + f12 * l58) + f9  * l70;
    l44 = (f9  * l6c + f11 * l60) + f12 * l54;
    l40 = (f9  * l68 + f11 * l5c) + f12 * l50;
    l3c = (f13 * l64 + l10 * l58) + f10 * l70;
    l34 = (f10 * l68 + f13 * l5c) + l10 * l50;
    l38 = (f10 * l6c + f13 * l60) + l10 * l54;
    l30 = (l8  * l64 + l4  * l58) + lc  * l70;
    l2c = (lc  * l6c + l8  * l60) + l4  * l54;
    l28 = (lc  * l68 + l8  * l5c) + l4  * l50;

    float* dst = (float*)((char*)self + 0xa4);
    dst[0] = l48; dst[1] = l44; dst[2] = l40; dst[3] = l3c; dst[4] = l38;
    dst[5] = l34; dst[6] = l30; dst[7] = l2c; dst[8] = l28;

    f8 = FUN_00b3dcd0();
    const float* src = (const float*)FUN_00477820(l24, dst, f8);
    for (int i = 0; i < 9; ++i)
        dst[i] = src[i];

    float* q = (float*)((char*)self + 0xf8);
    q[0] = la8; q[1] = la4; q[2] = la0; q[3] = l9c; q[4] = l98;
    q[5] = l94; q[6] = l90; q[7] = l8c; q[8] = l88;
}

// @ 0x00b43710
void __cdecl FUN_00b43710(u32 key)
{
    char* w = g_167eb70;
    char* ht = w + 0x58;                                  // hashtable at +0x58
    void* arr   = *(void**)(ht + 4);
    int   count = *(int*)(ht + 8);

    void* it_node = 0;
    FUN_00b645ed0(ht, &it_node, &key);                    // find(&it, &key)

    if (it_node != *(void**)((char*)arr + (u32)count * 4)) {
        int* pair = *(int**)((char*)it_node + 4);
        FUN_00bbc330(*(int*)(w + 4), pair[2]);
        FUN_00b72260(pair[0]);
        FUN_01068380(w + 0x58, &it_node);
    }
}

// @ 0x00b43790
void __cdecl FUN_00b43790(void* a, void* b, float* out)
{
    float vA[4];                       // local_30
    float qa[3], qb[3];                // local_c, local_24
    float p[3];                        // local_18, local_14, local_10

    FUN_00b3d9c0(a, vA);
    FUN_00b42370(b, qa, qb);
    float f2  = FUN_00b3d630(a);
    float fv4 = *(float*)((char*)b + 0x134) * *(float*)((char*)b + 0x10) + f2;
    float f3  = FUN_00698b30(vA, qa, qb);

    if (f3 <= fv4) {
        FUN_00698e00(p, vA, qa, qb);
        p[0] -= vA[0];
        p[1] -= vA[1];
        p[2] -= vA[2];
        *(int*)(out + 0x60) = 1;                                   // out+0x180
        float f1 = 1.0f / sqrt((p[0] * p[0] + (p[1] * p[1] + p[2] * p[2])) + 1e-08f);
        float fv4b = fv4 - f3;
        float fv2  = f2 - fv4b;
        out[0] = (f1 * p[0]) * fv2 + vA[0];
        out[1] = (p[1] * f1) * fv2 + vA[1];
        out[2] = (p[2] * f1) * fv2 + vA[2];
        out[0x30] = out[0];
        out[0x31] = out[1];
        out[0x32] = out[2];
        out[0x61] = f1 * p[0];
        out[0x62] = p[1] * f1;
        out[99]   = p[2] * f1;
        out[0x65] = out[0x61] * fv4b;
        out[0x66] = out[0x62] * fv4b;
        out[0x67] = out[99]   * fv4b;
        out[100]  = 0.0f;
    }
}

// @ 0x00b43990
void __cdecl FUN_00b43990(void* param_1, void* param_2, float* param_3)
{
    float qa[3], qb[3];                // local_c, local_18
    float qc[3], qd[3];                // local_24, local_30
    float r1[3];                       // local_48, local_44, local_40
    float r2[3];                       // local_3c, local_38, local_34

    FUN_00b42370(param_1, qa, qb);
    FUN_00b42370(param_2, qc, qd);

    float f4 = *(float*)((char*)param_2 + 0x134) * *(float*)((char*)param_2 + 0x10);
    float f3 = *(float*)((char*)param_1 + 0x134) * *(float*)((char*)param_1 + 0x10);
    float f5 = f4 + f3;
    float f2 = FUN_00b3dfa0(qa, qb, qc, qd, r1, r2);

    if (f2 <= f5) {
        float f7 = r2[2] - r1[2];
        float f6 = r2[1] - r1[1];
        float f8 = r2[0] - r1[0];
        f5 = f5 - f2;
        f3 = f3 - f5;
        float f1 = 1.0f / sqrt((f8 * f8 + (f6 * f6 + f7 * f7)) + 1e-08f);
        f8 = f1 * f8;
        f6 = f6 * f1;
        f7 = f7 * f1;
        param_3[0] = f8 * f3 + r1[0];
        f4 = f4 - f5;
        param_3[1] = f6 * f3 + r1[1];
        param_3[2] = f7 * f3 + r1[2];
        param_3[0x31] = r2[1] - f6 * f4;
        param_3[0x32] = r2[2] - f7 * f4;
        param_3[0x30] = r2[0] - f8 * f4;
        param_3[0x61] = f8;
        param_3[0x62] = f6;
        *(int*)(param_3 + 0x60) = 1;                               // param_3+0x180
        param_3[99]   = f7;
        param_3[0x65] = f5 * param_3[0x61];
        param_3[0x66] = param_3[0x62] * f5;
        param_3[0x67] = param_3[99]   * f5;
        param_3[100]  = 0.0f;
    }
}

// @ 0x00b43bc0
void __cdecl FUN_00b43bc0(void* param_1, void* param_2, void* param_3)
{
    float g68[3], g5c[3];              // local_68, local_5c  (two query points)
    float box[6];                      // local_50..local_3c  (min/max working box)
    float sph[6];                      // local_38..local_28  (centre + radius)
    float mtx[12];                     // local_24  (Matrix33Template)

    FUN_00b42370(param_1, g68, g5c);
    float f2 = *(float*)((char*)param_1 + 0x134) * *(float*)((char*)param_1 + 0x10);

    unsigned fm = 0x7f7fffffu, fn = 0xff7fffffu;
    box[0] = box[1] = box[2] = *(float*)&fm;
    box[3] = box[4] = box[5] = *(float*)&fn;
    FUN_00b3f420(box);

    sph[0] = 0.0f; sph[1] = 0.0f;                  // local_38 / local_36
    sph[2] = g_167eb8c;
    sph[3] = g_167eb90;
    sph[4] = g_167eb94;
    sph[5] = 1.0f;

    FUN_0041cb40(mtx, &g_167ec08);
    int flags = FUN_00b3f6c0(sph);

    if (*(char*)((char*)param_1 + 0x34) == 0 || *(char*)((char*)param_2 + 0x34) == 0)
        flags = 1;
    else
        flags &= 0xffffff00;

    FUN_00b3fe40(g68, f2, box, sph, flags, param_3);

    if (*(int*)((char*)param_3 + 0x180) == 0) {
        if (*(char*)((char*)param_1 + 0x34) == 0 || *(char*)((char*)param_2 + 0x34) == 0)
            flags = 1;
        else
            flags &= 0xffffff00;
        FUN_00b3fe40(g5c, f2, box, sph, flags, param_3);
    }
}

// @ 0x00b45170
void cObj45170::Destroy()
{
    if (mPtr90 != 0) FUN_00f47380(mPtr90);
    if (mPtr78 != 0) FUN_00f47380(mPtr78);

    mSub58.SetBuckets(mSub58.mBuckets, mSub58.mBucketCount);
    mSub58.mNodeCount = 0;
    if ((unsigned)mSub58.mBucketCount > 1u) FUN_00f47380(mSub58.mBuckets);

    mSub3c.Destroy();
    if (mPtr24 != 0) FUN_00f47380(mPtr24);
    mSub08.Destroy();
}

// @ 0x00b451f0
void cObj451f0::OnEvent()
{
    if (FUN_0067dcc0() != 0)
    {
        void* sender = (char*)this - 4;

        cIface2c* o = (cIface2c*)FUN_0067dcc0();
        o->Send(sender, 0x182c582, 0xffffd8f1);
        o = (cIface2c*)FUN_0067dcc0();
        o->Send(sender, 0x1a0219e, 0xffffd8f1);
        o = (cIface2c*)FUN_0067dcc0();
        o->Send(sender, 0x25630b7, 0xffffd8f1);
        o = (cIface2c*)FUN_0067dcc0();
        o->Send(sender, 0x31018b9, 0xffffd8f1);
        o = (cIface2c*)FUN_0067dcc0();
        o->Send(sender, 0xf62def, 0xffffd8f1);
    }

    FUN_00b4d720();

    mHash3c.FreeNodes(mHash3c.mBuckets, mHash3c.mBucketCount);
    mHash3c.mNodeCount = 0;
}

// @ 0x00b452b0
void cObj452b0::F()
{
    if (gFlag167eb75 != 0) gFlag167eb75 = 0;

    FUN_00b5a390();

    mHash40.FreeNodes(mHash40.mBuckets, mHash40.mBucketCount);
    mHash40.mNodeCount = 0;
}

// @ 0x00b452f0
void cObj452xx::Dispatch(void* p2, void* p3, void* p4)
{
    if (mMode20 == 0)
    {
        FUN_00b54340(p2, p3, p4);
        return;
    }

    if (p2 != 0)
    {
        void* r = ((cIfaceB8*)p2)->Get(0x116dd1b);
        if (r != 0)
        {
            ((cValH*)r)->Register(p3, 0);
            return;
        }
    }

    if (mMode20 == 1)
    {
        cHash16* ht = (cHash16*)((char*)gHashOwner + 0x58);
        void* node = 0;
        ht->Find(&node, &p2);
        if (node != ht->mBuckets[ht->mBucketCount])
        {
            cVal* v = (cVal*)((cValNode*)node)->mValue;
            v->SetValue(p3);
            v->mFlag34 = 0;
        }
    }
}

// @ 0x00b453a0
void cObj452xx::Mode0A(void* p2)
{
    int m = mMode20;

    if (m == 0)
    {
        FUN_00b544c0(p2, 0);
        return;
    }
    if (m - 1 != 0) return;

    cHash16* ht = (cHash16*)((char*)gHashOwner + 0x58);
    void* node = 0;
    ht->Find(&node, &p2);
    if (node != ht->mBuckets[ht->mBucketCount])
    {
        cVal* v = (cVal*)((cValNode*)node)->mValue;
        v->mField38 = v->mField3c;
    }
}

// @ 0x00b45410
void cObj452xx::Mode0B(void* p2)
{
    int m = mMode20;

    if (m == 0)
    {
        FUN_00b544f0(p2, 0);
        return;
    }
    if (m - 1 != 0) return;

    cHash16* ht = (cHash16*)((char*)gHashOwner + 0x58);
    void* node = 0;
    ht->Find(&node, &p2);
    if (node != ht->mBuckets[ht->mBucketCount])
    {
        cVal* v = (cVal*)((cValNode*)node)->mValue;
        v->mField38 = 0;
    }
}

// @ 0x00b45480
unsigned cObj452xx::GetFlag(void* p2)
{
    int m = mMode20;

    if (m == 0) return FUN_00b54520(p2);

    unsigned r = (unsigned)(m - 1);

    if (r == 0)
    {
        cHash16* ht = (cHash16*)((char*)gHashOwner + 0x58);
        void* node = 0;
        ht->Find(&node, &p2);
        if (node != ht->mBuckets[ht->mBucketCount])
        {
            cVal* v = (cVal*)((cValNode*)node)->mValue;
            float s = v->mF1c * v->mF1c + v->mF20 * v->mF20 + v->mF24 * v->mF24;
            return (s > 1.52587890625e-05f) ? 1u : 0u;
        }
        r = (unsigned)node;
    }

    return r & 0xffffff00u;
}

// @ 0x00b45540
bool cObj45540::Build(void* p2, void* p3, float* p4, float* p5, cFOut* p6)
{
    V3f neg;
    neg.x = -p6->v184.x;
    neg.y = -p6->v184.y;
    neg.z = -p6->v184.z;

    int c1 = ((cObj42760*)p2)->GetVec(&neg, &mFirst[0], p3);
    mCount1 = c1;
    int c2 = ((cObj42760*)p3)->GetVec(&p6->v184, &mSecond[0], p2);
    mCount2 = c2;

    for (int i = 0; i < mCount1; i++)
    {
        float f = p6->v190.x;
        mFirst[i].x += p4[0] * f;
        mFirst[i].y += p4[1] * f;
        mFirst[i].z += p4[2] * f;
    }

    for (int i = 0; i < mCount2; i++)
    {
        float f = p6->v190.x;
        mSecond[i].x += p5[0] * f;
        mSecond[i].y += p5[1] * f;
        mSecond[i].z += p5[2] * f;
    }

    c1 = mCount1;
    c2 = mCount2;

    if (c1 == 1)
    {
        if (c2 == 1)
        {
            p6->v0 = mFirst[0];
            p6->vc0 = mSecond[0];
            p6->mField180.i = 1;
            return true;
        }

        if (c2 == 2)
        {
            p6->mField180.i = Sub860(&mFirst[0], &mSecond[0], &mSecond[1], p6, &p6->vc0);
            return true;
        }

        // cross-product block (V1 = mSecond[1], V2 = mSecond[2], V3 = mSecond[0])
        V3f& V1 = mSecond[1];
        V3f& V2 = mSecond[2];
        V3f& V3 = mSecond[0];
        V3f& A  = mFirst[0];

        float dx = V2.x - V1.x;
        float dy = V2.y - V1.y;
        float dz = V2.z - V1.z;
        float ex = V1.x - V3.x;
        float ey = V1.y - V3.y;
        float ez = V1.z - V3.z;

        float py = ez * dx - dz * ex;
        float pz = dy * ex - ey * dx;
        float px = dz * ey - dy * ez;

        double s2 = (double)pz * pz + (double)py * py + (double)px * px;
        float n = (float)(1.0 / sqrt(s2));
        px *= n;
        py *= n;
        pz *= n;

        float dot = ((A.x * px + A.z * pz) + A.y * py) - ((V3.z * pz + V3.y * py) + V3.x * px);

        p6->v0.x = A.x;
        p6->v0.y = A.y;
        p6->v0.z = A.z;
        p6->vc0.x = A.x - px * dot;
        p6->vc0.y = A.y - py * dot;
        p6->vc0.z = A.z - pz * dot;
        p6->mField180.i = 1;
        return true;
    }

    if (c1 == 2)
    {
        if (c2 == 1)
        {
            p6->mField180.i = Sub860(&mSecond[0], &mFirst[0], &mFirst[1], &p6->vc0, p6);
            return true;
        }

        if (c2 == 2)
        {
            p6->mField180.i = Sub980(&mFirst[0], &mFirst[1], &mSecond[0], &mSecond[1], p6, &p6->vc0);
            return true;
        }

        p6->mField180.i = Sub1900(&mSecond[0], c2, &mFirst[0], 2, &p6->vc0, p6);
        return true;
    }

    if (c2 == 1)
    {
        // cross-product block (V1 = mFirst[1], V2 = mFirst[2], V3 = mSecond[0])
        V3f& V1 = mFirst[1];
        V3f& V2 = mFirst[2];
        V3f& V3 = mSecond[0];
        V3f& A  = mFirst[0];

        float dx = V2.x - V1.x;
        float dy = V2.y - V1.y;
        float dz = V2.z - V1.z;
        float ex = V1.x - V3.x;
        float ey = V1.y - V3.y;
        float ez = V1.z - V3.z;

        float py = ez * dx - dz * ex;
        float pz = dy * ex - ey * dx;
        float px = dz * ey - dy * ez;

        double s2 = (double)pz * pz + (double)py * py + (double)px * px;
        float n = (float)(1.0 / sqrt(s2));
        px *= n;
        py *= n;
        pz *= n;

        float dot = ((V3.z * pz + V3.y * py) + V3.x * px) - ((A.z * pz + A.y * py) + px * A.x);

        p6->vc0.x = V3.x;
        p6->vc0.y = V3.y;
        p6->vc0.z = V3.z;
        p6->v0.x = V3.x - px * dot;
        p6->v0.y = V3.y - py * dot;
        p6->v0.z = V3.z - pz * dot;
        p6->mField180.i = 1;
        return true;
    }

    p6->mField180.i = Sub1900(&mFirst[0], c1, &mSecond[0], c2, p6, &p6->vc0);
    return true;
}

// @ 0x00b45ab0
int cHash30::Remove(void* keyPtr)
{
    int   before = mNodeCount;
    void* key    = *(void**)keyPtr;

    void** slot = &mBuckets[(unsigned)key % (unsigned)mBucketCount];
    void*  node = *slot;

    while (node != 0)
    {
        cHtNode* n = (cHtNode*)node;

        if (n->mKey == key)
        {
            *slot = n->mNext;

            if (n->mKey != 0) ((cKeyObj*)n->mKey)->Destroy();

            if (node != mSentinel)
            {
                if (node < mPoolLo || node >= mPoolHi)
                {
                    FUN_00f47380(node);
                }
                else
                {
                    n->mKey     = mFreeList;
                    mFreeList   = node;
                }
            }

            mNodeCount--;
            node = *slot;
            continue;
        }

        slot = &n->mNext;
        node = *slot;
    }

    return before - mNodeCount;
}

// @ 0x00b45b50
cIter cHash30::Insert(void* keyPtr, void* arg2)
{
    cIter out;

    void* key = *(void**)keyPtr;

    unsigned idx  = (unsigned)key % (unsigned)mBucketCount;
    cHtNode* node = (cHtNode*)mBuckets[idx];

    while (node != 0)
    {
        if (node->mKey == key)
        {
            out.mNode     = node;
            out.mBucket   = &mBuckets[idx];
            out.mInserted = 0;
            return out;
        }
        node = (cHtNode*)node->mNext;
    }

    cRehashResult r;
    mRehash.Make(&r, mBucketCount, mNodeCount, 1);

    cHtNode* nn  = (cHtNode*)NewNode(keyPtr);
    unsigned idx2 = idx;

    if (r.mFlag != 0)
    {
        idx2 = (unsigned)key % (unsigned)r.mNewCount;
        Resize(r.mNewCount);
    }

    nn->mNext      = mBuckets[idx2];
    mBuckets[idx2] = nn;
    mNodeCount++;

    out.mNode     = nn;
    out.mBucket   = &mBuckets[idx2];
    out.mInserted = 1;
    return out;
}

// @ 0x00b45c10
void* cVec3c::InitCopy(const cVec3c* src)
{
    unsigned count = (unsigned)((int)((char*)src->mEnd - (char*)src->mBegin) / 0x3c);
    void*    mem   = 0;

    if (count != 0)
    {
        mem = FUN_00f473a0(count * 0x3c, (void*)0x13f09b4, 0, 0, (void*)0x13ebb38, 0xd1);
    }

    mCap   = (char*)mem + count * 0x3c;
    mBegin = mem;
    mEnd   = mem;

    void* out = (void*)src;
    FUN_00b3f260(&out, src->mBegin, src->mEnd, mem, (void*)src);
    mEnd = out;

    return this;
}

// @ 0x00b46660
void cSurfaceMover::Update(float dt)
{
    if (!(1.5258789e-05f < GetSpeed()))
        return;
    if (!active)
        return;
    switch (mode) {
    case 0:
        if (vel.x != g_ZeroVec.x || vel.y != g_ZeroVec.y || vel.z != g_ZeroVec.z) {
            Vec3f* pv = &vel;
            obj->SetVelocityDir(pv);
            obj->SetAngularDir(&angVel);
            Vec4f q;
            GetOrientation(&q);
            Vec4f w = { angVel.x, angVel.y, angVel.z, 0.0f };
            Vec4f tmp;
            Vec4f* d = QuatDelta(&tmp, &w, &q);
            q.x = (d->x * 0.5f) * dt + q.x;
            q.y = q.y + (d->y * 0.5f) * dt;
            q.z = q.z + (d->z * 0.5f) * dt;
            q.w = q.w + (d->w * 0.5f) * dt;
            Vec4f tmp2;
            Vec4f* n = QuatNormalize(&tmp2, &q);
            q.x = n->x; q.y = n->y; q.z = n->z; q.w = n->w;
            if (obj->GetRotateFactor() == 0.0f)
                obj->SetOrientation(&q);
            Vec3f* p = obj->GetPosition();
            Vec3f tgt;
            tgt.x = pv->x * dt + p->x;
            tgt.y = pv->y * dt + p->y;
            tgt.z = pv->z * dt + p->z;
            ApplyPlanetCorrection(&tgt, obj);
        }
        break;
    case 1: {
        Vec3f* pv = &vel;
        if (pv->x != g_ZeroVec.x || pv->y != g_ZeroVec.y || pv->z != g_ZeroVec.z) {
            cPlanetModel* planet = PlanetModel();
            float scale = planet->GetScale();
            if (onSurface) {
                Vec3f t1, n1, t2;
                planet->ProjectToTangent(&t1, obj->GetPosition());
                Normalize(&n1, &t1);
                Vec3f* p = Normalize(&t2, obj->GetPosition());
                float px = p->x * scale, py = p->y * scale, pz = p->z * scale;
                float step = ((-n1.z * pz + -n1.y * py) + -n1.x * px) * dt;
                float step2 = step * step;
                if (Dot3(pv) < step2) {
                    pv->x = g_ZeroVec.x;
                    vel.y = g_ZeroVec.y;
                    vel.z = g_ZeroVec.z;
                    angVel.x = g_ZeroVec.x;
                    angVel.y = g_ZeroVec.y;
                    angVel.z = g_ZeroVec.z;
                    active = 0;
                } else {
                    Vec3f t3;
                    Vec3f* nv = Normalize(&t3, pv);
                    float nx = -nv->x, ny = -nv->y, nz = -nv->z;
                    pv->x = pv->x + nx * step;
                    vel.y = ny * step + vel.y;
                    vel.z = nz * step + vel.z;
                }
            } else {
                float len = VectorLength(obj->GetPosition());
                if (len > 1.5258789e-05f) {
                    Vec3f* p = obj->GetPosition();
                    float inv = 1.0f / len;
                    pv->x = ((inv * p->x) * scale) * dt + pv->x;
                    vel.y = ((p->y * inv) * scale) * dt + vel.y;
                    vel.z = ((p->z * inv) * scale) * dt + vel.z;
                } else {
                    onSurface = 1;
                }
            }
            Vec4f q;
            GetOrientation(&q);
            Vec4f w = { angVel.x, angVel.y, angVel.z, 0.0f };
            Vec4f tmp;
            Vec4f* d = QuatDelta(&tmp, &w, &q);
            q.x = (d->x * 0.5f) * dt + q.x;
            q.y = q.y + (d->y * 0.5f) * dt;
            q.z = q.z + (d->z * 0.5f) * dt;
            q.w = q.w + (d->w * 0.5f) * dt;
            Vec4f tmp2;
            Vec4f* n = QuatNormalize(&tmp2, &q);
            q.x = n->x; q.y = n->y; q.z = n->z; q.w = n->w;
            obj->SetOrientation(&q);
            Vec3f* p = obj->GetPosition();
            Vec3f tgt;
            tgt.x = pv->x * dt + p->x;
            tgt.y = vel.y * dt + p->y;
            tgt.z = vel.z * dt + p->z;
            Vec3f surf;
            obj->SetPosition(planet->DirectionToSurfacePosition(&surf, &tgt));
            cMoverTarget* o = obj;
            Vec4f ori;
            o->SetOrientation(planet->OrientationAt(&ori, o->GetPosition(), o->GetUp()));
            obj->flags &= 0xfffffffe;
            if (!onSurface) {
                Vec3f* pos = obj->GetPosition();
                float wh = planet->GetWaterHeight();
                float rad = planet->GetRadiusAt(pos);
                float* m = &wh;
                if (!(wh > rad)) m = &rad;
                onSurface = (float)fabs(*m - VectorLength(pos)) < 1.5258789e-05f;
            }
        }
        break;
    }
    }
}

// @ 0x00b46d10
void Fn_00b46d10(float dt)
{
    int key = g_pMoverRegistry->mIter.GetPriority();
    cMoverIterator* pIter = &g_pMoverRegistry->mIter;
    void* pNext = pIter->Next(&key);
    while (pNext != 0) {
        cSurfaceMover* pMover = (cSurfaceMover*)pNext;
        bool bUpdate = false;
        int nType = pMover->mode;
        switch (nType) {
        case 0: {
            cMoverTargetFlags* pFlags = (cMoverTargetFlags*)pMover->obj;
            if (pFlags->mFlag75 != 0 &&
                (pFlags->mFlag70 != 0 || pMover->flag35 != 0))
                bUpdate = true;
            break;
        }
        case 1: {
            cMoverTargetFlags* pFlags = (cMoverTargetFlags*)pMover->obj;
            if (pFlags->mFlag75 != 0 &&
                (pFlags->mFlag70 != 0 || pMover->flag35 != 0))
                bUpdate = true;
            break;
        }
        case 2:
            bUpdate = true;
            break;
        }
        if (bUpdate)
            pMover->Update(dt);
        pIter = &g_pMoverRegistry->mIter;
        pNext = pIter->Next(&key);
    }
}

// @ 0x00b46d90
cCurve* cCurve::Assign(cCurve* pOther)
{
    AssignFrom(pOther);
    mPoint.CopyFrom(&pOther->mPoint);
    mF50 = pOther->mF50;
    mF54 = pOther->mF54;
    mF58 = pOther->mF58;
    mF5c = pOther->mF5c;
    mF60 = pOther->mF60;
    mF64 = pOther->mF64;
    mF68 = pOther->mF68;
    mF6c = pOther->mF6c;
    mF70 = pOther->mF70;
    return this;
}

// @ 0x00b46df0
float __stdcall Fn_00b46df0(cAimObject* pObj, float fA2, float fA3, float fA4, float fA5)
{
    Vec3f vIn;
    Vec3f vRef;
    Vec4f qTarget;
    Vec4f qNew;

    Fn_00d58510(&vIn, pObj, fA2);
    pObj->GetTargetOrientation(&qTarget);
    Fn_0059aed0(&vRef, &gAimConst, &vIn);

    float fDot = qTarget.x * vRef.x + qTarget.y * vRef.y + qTarget.z * vRef.z;
    float fCos = fDot;
    if (fCos > 1.0f) fCos = 1.0f;
    if (fCos < 0.0f) fCos = 0.0f;

    float fProd = fCos * fA4;
    float fAngle = (float)acos(fCos);

    // Bail out on a non-finite angle.
    union { float f; unsigned int u; } bits;
    bits.f = fAngle;
    if ((bits.u & 0x7fffffffu) != 0) {
        unsigned int e = (bits.u + 0xff800000u) & 0x7f800000u;
        if (e >= 0x7f000000u)
            return fProd;
    }

    float t;
    if (fAngle > 0.0f) {
        float fT = (fA3 * fA5) / fAngle;
        t = (fT > 1.0f) ? 1.0f : fT;
    } else {
        t = 1.0f;
    }

    Vec4f* pCur = pObj->GetOrientation();
    Slerp(&qNew, pCur, &qTarget, t);
    if (Fn_00b3d550(&qNew))
        pObj->SetOrientation(&qNew);

    return fProd;
}

// @ 0x00b46ff0
cHolder* cHolder::Init()
{
    mVec1.Clear();
    mF24 = 0;
    mF28 = 0;
    mF2c = 0;
    mVec2.Clear();
    mF68 = 1.0f;
    _ReadWriteBarrier();
    mF6c = 2.0f;
    _ReadWriteBarrier();
    mF64 = 0;
    mF70 = 0;
    mF60 = 1;
    mpF5c = (void*)&gF5cObject;
    _ReadWriteBarrier();
    mF78 = 0;
    mF7c = 0;
    mF80 = 0;
    mF90 = 0;
    mF94 = 0;
    mF98 = 0;
    return this;
}

// @ 0x00b47060
void cSwitchHolder::Cleanup()
{
    if (mState == -1)
        return;
    switch (mState) {
    case 0x1654c00:
    case 0x1654c01:
    case 0x1654c02:
    case 0x1654c04:
    case 0x1654c05:
    case 0x1654c10:
        Fn_00b452b0();
        break;
    }
    mState = -1;
}

// @ 0x00b470b0
void cMoverOwner::Register(cRegistrarObject* pObj)
{
    if (pObj->GetId() == 0x3ed8573u) {
        Fn_00b43710((pObj->GetId() == 0x3ed8573u) ? (void*)pObj : 0);
        return;
    }

    cStoredObject* pStored = (cStoredObject*)pObj->GetByTag(0x1186577u);
    if (pStored)
        pStored->AddRef();
    void* pRec = pObj->GetByTag(0x116dd1bu);

    if (pStored) {
        if (pRec == 0) {
            mRecordList.Append((void**)&pStored);
        } else {
            int nCount = (int)(mpEnd - mpBegin);
            for (int i = 0; i < nCount; ++i) {
                if (mpBegin[i] == (cStoredObject*)pRec) {
                    cStoredObject* pLast = mpBegin[nCount - 1];
                    cStoredObject* pFound = mpBegin[i];
                    if (pLast != pFound) {
                        if (pLast)
                            pLast->AddRef();
                        mpBegin[i] = pLast;
                        if (pFound)
                            pFound->Release();
                    }
                    --mpEnd;
                    cStoredObject* pRemoved = *mpEnd;
                    if (pRemoved)
                        pRemoved->Release();
                    break;
                }
            }
        }

        Fn_00b43710(pStored);
        if (g_nAimFlag)
            Fn_00b530e0(pStored, pRec);
        pStored->Release();
    }
}

// @ 0x00b47200
bool cSlabTester::Clip(void* pBoxA, void* pBoxB, float* pNormal, float* pV, float fDistance, float* pBest, unsigned char* pMask, float* pMin, float* pMax, float* pNegDir, float* pPosDir)
{
    float fLo1, fHi1;
    float fLo2, fHi2;
    ((cSlabBox*)pBoxA)->Compute(pV, &fHi1, &fLo1);
    ((cSlabBox*)pBoxB)->Compute(pV, &fHi2, &fLo2);

    float tNear = (fHi2 - fLo2) - fLo1 - fHi1;
    float tFar = (fHi2 + fLo2) + fLo1 - fHi1;
    bool bHit = (tNear > 0.0f) || (tFar > 0.0f);

    if (mFlag != 0 && ((*pMask = *pMask & (bHit ? 1 : 0)), *pMask != 0)) {
        float fScale = (fabsf(tNear) < fabsf(tFar)) ? tNear : tFar;
        fScale = -(fScale / fDistance);
        float vx = pV[0] * fScale;
        float vy = pV[1] * fScale;
        float vz = pV[2] * fScale;
        if (vx * vx + vy * vy + vz * vz <
            pBest[0] * pBest[0] + pBest[1] * pBest[1] + pBest[2] * pBest[2]) {
            pBest[0] = vx;
            pBest[1] = vy;
            pBest[2] = vz;
        }
    }

    float fDot = pNormal[0] * pV[0] + pNormal[1] * pV[1] + pNormal[2] * pV[2];
    if (fabsf(fDot) < 1.5258789e-05f)
        return bHit;

    float fSign = -1.0f;
    float fInv = 1.0f / fDot;
    float fA = -(fInv * tNear);
    float fB = -(fInv * tFar);
    float fMin = fA;
    float fMax = fB;
    if (fB < fA) {
        fSign = 1.0f;
        fMin = fB;
        fMax = fA;
    }

    float fCurMax = *pMax;
    if (fCurMax != 1e20f && fMin > fCurMax)
        return false;
    if (*pMin != -1e20f && *pMin > fMax)
        return false;

    if (fMax < fCurMax || fCurMax == 1e20f) {
        *pMax = fMax;
        float vx = pV[0] * fSign;
        float vy = pV[1] * fSign;
        float vz = pV[2] * fSign;
        pPosDir[0] = vx;
        pPosDir[1] = vy;
        pPosDir[2] = vz;
    }
    if (*pMin < fMin || *pMin == -1e20f) {
        *pMin = fMin;
        fSign = -fSign;
        float vx = pV[0] * fSign;
        float vy = pV[1] * fSign;
        float vz = pV[2] * fSign;
        pNegDir[0] = vx;
        pNegDir[1] = vy;
        pNegDir[2] = vz;
    }
    return true;
}

// @ 0x00b47570
int* cRange::Find(int* pValue)
{
    int* pEnd = mpEnd;
    int* p = Fn_00b41ea0(mpBegin, pEnd, pValue, mF14);
    if (p == pEnd || *pValue < *p)
        return pEnd;
    if (p == p + 2)               // redundant sentinel guard present in the original
        return pEnd;
    return p;
}

// @ 0x00b475b0
void Fn_00b475b0(int* pBegin, int* pEnd, cRandomLCG* pRandom)
{
    for (int* p = pBegin + 1; p < pEnd; ++p) {
        unsigned n = (unsigned)(p - pBegin) + 1;
        unsigned idx = pRandom->RandomUint32Uniform(n);
        int* pOther = pBegin + idx;
        Fn_010216a0(p, pOther);
    }
}

// @ 0x00b47600
void Vec44::DoInsertValue(Elem44* position, const Elem44& value)
{
    if (mpEnd != mpCapacity) {
        const Elem44* pValue = &value;
        if ((&value >= position) && (&value < mpEnd))
            ++pValue;
        new(mpEnd) Elem44(*(mpEnd - 1));
        CopyBackward44(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNewSize = nPrevSize ? 2 * nPrevSize : 1;
        Elem44* const pNewData = DoAllocate44(nNewSize);
        Elem44* pNewPosition = F_b3d890(mpBegin, position, pNewData);
        new(pNewPosition) Elem44(value);
        Elem44* pNewEnd = F_b3d890(position, mpEnd, pNewPosition + 1);
        if (mpBegin && ((int*)mpBegin)[-1])
            F_f47380(mpBegin);
        mpEnd = pNewEnd;
        mpBegin = pNewData;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00b47730
Obj_s00b4_7600* F_b47730(uint32_t key, Part25c* a2, uint32_t a3, int kind, PropHolder* a5, int a6)
{
    BBox box;
    int h = g_mgr->pool.F_b72160();
    if (h != 0) {
        Obj_s00b4_7600* o = g_mgr->pool.F_b72210(h);
        o->m40 = a2;
        o->m4 = a3;
        o->b35 = 0;
        o->b34 = 1;
        o->b36 = 0;
        o->b37 = 0;
        o->state = GetTutorialToolPrice(a5, 0x2f5ab240, a6);
        o->f10 = GetPropertyFloat(a5, 0xce3f2a3a, 1.0f);
        o->f14 = GetPropertyFloat(a5, 0xc87942af, 1.0f);
        o->m38 = o->m3c = F_ac8fa0(a5, 0x1970f7f8, kind);
        o->f18 = 0.0f;
        float lim = GetPropertyFloat(a5, 0xb20c1347, FLT_MAX);
        if (o->state == 0 && o->F_b3d630() > lim)
            o->f18 = lim;
        if (kind == 5)
            o->f18 = a2->f25c;

        box.mn = MakeV3(FLT_MAX, FLT_MAX, FLT_MAX);
        box.mx = MakeV3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
        o->F_b3f420(&box);

        if (o->state == 4) {
            o->state = 0;
            float d[3];
        d[0] = box.mx.x - box.mn.x;
        d[1] = box.mx.y - box.mn.y;
        d[2] = box.mx.z - box.mn.z;
        float hi = Max(Max(d[0], d[1]), d[2]);
        if (hi > g_mgr->ratio * Min(Min(d[0], d[1]), d[2]))
                o->state = 2;
        }

        if (o->state == 1) {
            float k = o->f14;
            float a = (box.mx.x - box.mn.x) * k;
            float b = (box.mx.y - box.mn.y) * k;
            float c = (box.mx.z - box.mn.z) * k;
            float r = o->f10 * 0.5f;
            V3 p, q;
            p.x = g_v.x; p.y = g_v.y; p.z = g_v.z;
            q.x = g_v.x; q.y = g_v.y; q.z = g_v.z;
            float m;
            if (c > b && c > a) {
                float s = sqrtf(a * a + b * b) * r;
                m = Min(s, lim);
                p.z = c * 0.5f - m;
                q.z = -p.z;
            } else if (b > a) {
                float s = sqrtf(a * a + c * c) * r;
                m = Min(s, lim);
                p.y = b * 0.5f - m;
                q.y = -p.y;
            } else {
                float s = sqrtf(b * b + c * c) * r;
                m = Min(s, lim);
                p.x = a * 0.5f - m;
                q.x = -p.x;
            }
            float dx = p.x - q.x, dy = p.y - q.y, dz = p.z - q.z;
            if (1.5258789e-05f <= sqrtf((dz * dz + dy * dy) + dx * dx)) {
                float cy = (box.mx.y + box.mn.y) * 0.5f;
                float cz = (box.mx.z + box.mn.z) * 0.5f;
                float cx = (box.mx.x + box.mn.x) * 0.5f;
                o->f11c = cx + p.x;
                o->f120 = cy + p.y;
                o->f124 = cz + p.z;
                o->f128 = cx + q.x;
                o->f12c = cy + q.y;
                o->f130 = cz + q.z;
                o->f134 = m;
            } else {
                o->state = 0;
            }
        }

        const BBox* bb = o->F_b3f730(&box);
        box.mn = bb->mn;
        box.mx = bb->mx;
        float ex = box.mx.x - box.mn.x;
        float ey = box.mx.y - box.mn.y;
        float ez = box.mx.z - box.mn.z;
        float ex2 = ex * ex, ey2 = ey * ey, ez2 = ez * ez;
        {
            Mat3 inertia;
            inertia.m[0] = (ez2 + ey2) * 0.083333336f;
            inertia.m[1] = 0.0f;
            inertia.m[2] = 0.0f;
            inertia.m[3] = 0.0f;
            inertia.m[4] = (ez2 + ex2) * 0.083333336f;
            inertia.m[5] = 0.0f;
            inertia.m[6] = 0.0f;
            inertia.m[7] = 0.0f;
            inertia.m[8] = (ey2 + ex2) * 0.083333336f;
            o->m80 = inertia;
            o->v44 = g_v;
            o->v50 = g_v;
            o->vc8 = g_v;
            o->vd4 = g_v;
            o->ve0 = g_v;
            o->vec = g_v;
            float det;
            F_4fc990(&inertia, &o->m80, &det);
            o->m5c = inertia;
        }
        o->F_b43290();
        o->m8 = F_bbc300(g_mgr->m4, h, &box.mn, &box.mx);
        *g_mgr->map.F_b474c0(&key) = o;
        o->F_b3dbb0();
        return o;
    }
    return 0;
}

// @ 0x00b47e00
void F_b47e00(void* a1, cObj* a2, void* a3)
{
    void* sub = a2 ? ObjSubTag(a2, 0x17f243bu) : 0;
    void* o = F_b41ee0(sub, a3);
    if (!o)
        return;
    ObjVCall0(o);
    if ((a2->b50 & 0x80) == 0 && F_64f350(o, 0xcf3b981du, 1)) {
        int v = a2->m58 ? a2->m58 : a2->m54;
        v = F_ac8fa0(o, 0x93336c12u, v);
        a2->m54 = v;
        void* pParent;
        uint32_t bOwn;
        if (a1) {
            pParent = a1;
            bOwn = 0;
        } else {
            pParent = a2;
            bOwn = 1;
        }
        Obj_s00b4_7600* r = F_b47730((uint32_t)a2, (Part25c*)pParent, bOwn, 1,
                          (PropHolder*)o, 0);
        if (r)
            r->b35 = (ObjSubTag(a2, 0xe9cb8bau) != 0);
        ObjVCall1(o);
        return;
    }
    ObjVCall1(o);
}

// @ 0x00b47ee0
void F_b47ee0(cObj* key)
{
    Mgr* w = g_mgr;
    HashIter it = w->map.find(key);
    if (key->b75 && key->b70) {
        if (it == w->map.end()) {
            void* pA = ObjSubTag(key, 0x17f243bu);
            void* pB = ObjSubTag(key, 0x116dd1bu);
            if (pA)
                F_b47e00(pB, key, GetSim()->GetMsgSource(ObjId((cObj*)pA)));
            return;
        }
        BBox box;
        ObjBox(key, &box);
        Obj_s00b4_7600* o = it.mpNode->mpObj;
        float s = o->f14;
        float cx = (box.mn.x + box.mx.x) * 0.5f;
        float cy = (box.mn.y + box.mx.y) * 0.5f;
        float cz = (box.mn.z + box.mx.z) * 0.5f;
        box.mn.x = cx + (box.mn.x - cx) * s;
        box.mn.y = cy + (box.mn.y - cy) * s;
        box.mn.z = cz + (box.mn.z - cz) * s;
        box.mx.x = cx + (box.mx.x - cx) * s;
        box.mx.y = cy + (box.mx.y - cy) * s;
        box.mx.z = cz + (box.mx.z - cz) * s;
        F_bbc320(w->m4, o->m8, &box.mn, &box.mx);
        o->F_b3dbb0();
        return;
    }
    if (it == w->map.end())
        return;
    Obj_s00b4_7600* o = it.mpNode->mpObj;
    F_bbc330(w->m4, o->m8);
    g_mgr->pool.F_b72260(o->m0);
    it = w->map.erase(it);
}

// @ 0x00b48110
void Steering::Update(cSteerState* pState)
{
    pState->mpObject->FnD0();
    pState->mpObject->GetVelocity();
    pState->mpObject->FnB8((const void*)0x0137e8e0);

    Vec3 vDir;
    pState->mpObject->GetSteerDirection(&vDir);
    float fLen = (float)sqrt(vDir.x * vDir.x + vDir.y * vDir.y + vDir.z * vDir.z);
    if (g_1461154 <= fLen) {
        float fInv = 1.0f / fLen;
        vDir.x = fInv * vDir.x;
        vDir.y = vDir.y * fInv;
        vDir.z = vDir.z * fInv;
    } else {
        Vec3 vTmp;
        const Vec3* pv = pState->mpObject->GetDirection(&vTmp);
        vDir.x = pv->x * g_1488874;
        vDir.y = pv->y * g_1488874;
        vDir.z = pv->z * g_1488874;
    }

    const Vec3* pp = pState->mpObject->GetPosition();
    Vec3 vPos;
    vPos.x = pp->x;
    vPos.y = pp->y;
    vPos.z = pp->z;
    Vec3 vUp;
    pState->mpObject->GetDirection(&vUp);
    float fSpeed = pState->mpObject->GetDesiredSpeed();
    float fTurn  = pState->mpObject->mTurnRate;
    cLocomotionRequest* pReq = pState->mpObject->GetRequest();
    cPlanetModel_s00b4_8110* pPlanet = PlanetModel_s00b4_8110();

    int   nType = pReq->mType;
    float fDist;
    if (nType == 0) {
        fDist = 0.0f;
    } else {
        float dz = vPos.z - pReq->mDst.z;
        float dy = vPos.y - pReq->mDst.y;
        float dx = vPos.x - pReq->mDst.x;
        fDist = (float)sqrt(dz * dz + dy * dy + dx * dx);
    }

    if (pState->mpObject->mFlag77 == 0) {
        const Vec3* pv = pState->mpObject->GetVelocity();
        pState->mVelocity = *pv;
        const Vec3* pPos = pState->mpObject->GetPosition();
        Vec3 vGround;
        pState->mpObject->GetDirection(&vGround);
        Quat q;
        pPlanet->BuildSurfaceOrientation2(&q, pPos, &vGround);
        q = Slerp(*pState->mpObject->GetOrientation(), q, pState->mDt);
        pState->mpObject->SetOrientation(&q);
        return;
    }

    float fGoalStop = pReq->mGoalStopDistance;
    bool  notHold3  = nType != 3;
    bool  bStop     = false;
    if (nType == 0) {
        fSpeed = 0.0f;
    } else if (nType != 2) {
        bool bProgressed;
        if (fDist < pReq->mPrevDistance) {
            bProgressed = false;
        } else {
            float fElapsed = pState->mDt + pReq->mElapsed;
            pReq->mElapsed = fElapsed;
            bProgressed = true;
            if (g_13eb8a0 < fElapsed) {
                Vec3 vSurf;
                Vec3* pv = pPlanet->DirectionToSurfacePosition(&vSurf, &pReq->mDst);
                pReq->mDst = *pv;
            }
        }
        if (fGoalStop > fDist) {
            bStop = true;
        } else if (pState->mDt * fSpeed < fDist) {
            if (bProgressed && fDist < pReq->mAcceptableStopDistance)
                bStop = true;
        } else {
            fSpeed = (fDist / pState->mDt) * g_13f7344;
        }
        pReq->mPrevDistance = fDist;
        if (bStop) {
            if (pReq->mpBegin == pReq->mpEnd) {
                fSpeed = 0.0f;
            } else {
                pReq->mElapsed = 0.0f;
                Waypoint* pFirst = pReq->mpBegin;
                *(Waypoint*)&pReq->mDst = *pFirst;
                pReq->EraseWaypoint(pFirst);
                bStop = false;
            }
        }
    }

    if (nType != 0 && fDist < (fSpeed / fTurn) * g_1470f1c) {
        Vec3 vDelta;
        vDelta.x = pReq->mDst.x - vPos.x;
        vDelta.y = pReq->mDst.y - vPos.y;
        vDelta.z = pReq->mDst.z - vPos.z;
        Vec3 vNorm;
        const Vec3* pn = NormalizedSafe(&vNorm, &vDelta);
        float fDot = pn->y * vUp.y + pn->z * vUp.z + pn->x * vUp.x;
        if (fDot < g_1471064) {
            float fCap = (fDist * fTurn) * g_1471064;
            const float* pf = &fCap;
            if (fSpeed <= fCap)
                pf = &fSpeed;
            fSpeed = *pf;
        }
    }

    Vec3 vTarget;
    vTarget.x = vPos.x + vDir.x;
    vTarget.y = vPos.y + vDir.y;
    vTarget.z = vPos.z + vDir.z;
    float fAmount = Fn_00b46df0(pState->mpObject, &vTarget, pState->mDt, fSpeed, fTurn);
    if (fAmount > 0.0f) {
        pState->mVelocity.x = vDir.x * fSpeed;
        pState->mVelocity.y = vDir.y * fSpeed;
        pState->mVelocity.z = vDir.z * fSpeed;
    } else {
        pState->mVelocity.x = 0.0f;
        pState->mVelocity.y = 0.0f;
        pState->mVelocity.z = 0.0f;
    }

    if (!notHold3) {
        Vec3 vTmp;
        const Vec3* pv = pState->mpObject->GetDirection(&vTmp);
        float fAlign = pv->z * pReq->mField50.z
                     + pv->y * pReq->mField50.y
                     + pv->x * pReq->mField50.x;
        notHold3 = true;
        if (!(fAlign > pReq->mField64))
            notHold3 = false;
    }

    if (bStop) {
        if (notHold3) {
            {
                cLocomotionRequest goal;
                pState->mpObject->SetRequest(goal);
            }
            pState->mpObject->SetDesiredSpeed(0.0f, 1);
            pState->mVelocity.x = 0.0f;
            pState->mVelocity.y = 0.0f;
            pState->mVelocity.z = 0.0f;
        } else {
            {
                cLocomotionRequest goal(*pState->mpObject->GetRequest());
                goal.mDst = vPos;
                pState->mpObject->SetRequest(goal);
            }
        }
    }
}

// @ 0x00b48770
void cSim_s00b4_8110::Fn_00b48770(cGameObject* pObj, bool bFlag)
{
    cGameObject* pRec;

    if (pObj) {
        pRec = vtGetSubTag(pObj, 0x0116dd1b);
        if (pRec) {
            cGameObject** pEnd = mpObjEnd;
            cGameObject** p = mpObjBegin;
            while (p != pEnd && *p != pRec)
                ++p;
            if (p == pEnd)
                return;
        }
    } else {
        pRec = 0;
    }

    if ((g_167ecc0 & 1) == 0) {
        g_167ecc0 |= 1;
        g_167ecbc = FUN_00932e80("useGameplayPhantom", 0x811c9dc5u, 1);
    }

    uint  id    = vtGetId(pObj);
    void* key   = GetMsgSource(id);
    void* pNode = FUN_00b41ee0(pObj, key);
    if (!pNode)
        return;
    if (!FUN_0064f350(pNode, 0xcf3b981du, 1) &&
        !FUN_0064f350(pNode, g_167ecbc, 0))
        return;

    cGameObject* pStored = vtGetSubTag(pObj, 0x01186577);
    if (!pStored)
        return;

    if (!pRec) {
        vtAddRef(pStored);
        cIter_s00b4_8110 it;
        bool  bInserted = false;
        mRecords.Insert(&it, (void**)&pStored, bInserted);
        if (pStored)
            vtRelease(pStored);
    }

    if (mMode == 0) {
        if (bFlag)
            FUN_00b5a260(pStored, pRec);
        else
            FUN_00b539e0(pStored);
    } else if (mMode == 1) {
        cIter_s00b4_8110 it;
        uint  mapKey = (uint)pStored;
        g_167eb70_s00b4_8110->mMap58.find(&it, &mapKey);
        if (it.mpNode != g_167eb70_s00b4_8110->mMap58.mpBuckets[g_167eb70_s00b4_8110->mMap58.mCount]) {
            FUN_00b43710(pStored);
            FUN_00b47ee0(pStored);
        }
    }
}

// @ 0x00b48920
void cSim_s00b4_8110::Fn_00b48920()
{
    int  nAmount = (FUN_00b5b800() == (void*)0x01654c10) ? g_1569a88 : 10;
    int  nCur    = mObjIndex;
    int  nTarget = nCur + nAmount;
    int  nCount  = (int)(mpObjEnd - mpObjBegin);
    int  nLimit  = Min_s00b4_8110(nTarget, nCount);

    while (mObjIndex < nLimit) {
        cUpdateObj* p = (cUpdateObj*)mpObjBegin[mObjIndex];
        if (p->mFlag76)
            p->Update();
        ++mObjIndex;
    }

    int nFinal = (int)(mpObjEnd - mpObjBegin);
    if (nLimit == nFinal) {
        _ReadWriteBarrier();
        mObjIndex = 0;
        FUN_00b475b0((void**)mpObjBegin, (void**)mpObjEnd, &g_1601760);
    }
}

// @ 0x00b489d0
bool cSim_s00b4_8110::Fn_00b489d0(cSurfaceObj* pA, cSurfaceObj* pB, Vec3* pNormal, float fLimit, float* pOutT, Vec3* pOutVec)
{
    int  kindA = pA->mKind;
    int  kindB = pB->mKind;

    Vec3 vBest;
    vBest.x = g_146113c;
    vBest.y = g_146113c;
    vBest.z = g_146113c;
    bool bMask = true;

    int nA1 = SampleCount(kindA);
    int nB1 = SampleCount(kindB);
    int nA2 = SampleCount(kindA);
    int nB2 = SampleCount(kindB);

    *pOutT = fLimit;
    float fMin = g_14611c0;
    float fMax = g_146113c;
    Vec3  vNeg;
    vNeg.x = g_167eb8c;
    vNeg.y = g_167eb90;
    vNeg.z = g_167eb94;
    Vec3  vPos;
    vPos.x = g_167eb8c;
    vPos.y = g_167eb90;
    vPos.z = g_167eb94;
    Vec3  vDir;
    Vec3  vSampleA;
    Vec3  vSampleB;

    for (int i = 0; i < nA1; ++i) {
        pA->FUN_00b3da90(&vDir, i, pB);
        if (!Clip(pA, pB, pNormal, &vDir, 1.0f, &vBest, (uchar*)&bMask,
                  &fMin, &fMax, &vNeg, &vPos))
            return false;
    }

    for (int i = 0; i < nB1; ++i) {
        pB->FUN_00b3da90(&vDir, i, pB);
        if (!Clip(pA, pB, pNormal, &vDir, 1.0f, &vBest, (uchar*)&bMask,
                  &fMin, &fMax, &vNeg, &vPos))
            return false;
    }

    for (int i = 0; i < nA2; ++i) {
        for (int j = 0; j < nB2; ++j) {
            Vec3* pvA = pB->FUN_00b3da90(&vSampleA, j, pA);
            Vec3* pvB = pA->FUN_00b3da90(&vSampleB, i, pB);
            vDir.x = pvA->z * pvB->y - pvA->y * pvB->z;
            vDir.z = pvB->x * pvA->y - pvA->x * pvB->y;
            vDir.y = pvA->x * pvB->z - pvB->x * pvA->z;
            float len2 = vDir.z * vDir.z + vDir.y * vDir.y + vDir.x * vDir.x;
            if (len2 >= g_1461154) {
                if (!Clip(pA, pB, pNormal, &vDir, len2, &vBest, (uchar*)&bMask,
                          &fMin, &fMax, &vNeg, &vPos))
                    return false;
            }
        }
    }

    if (fMin > fLimit || fMax < 0.0f)
        return false;

    if (mClipFlag) {
        if (fMin > 0.0f) {
            *pOutT = fMin;
            *pOutVec = vNeg;
        } else {
            if (!bMask)
                return false;
            *pOutT = 0.0f;
            *pOutVec = vBest;
        }
    } else {
        if (fabsf(fMax) < fabsf(fMin)) {
            *pOutT = fMax;
            *pOutVec = vPos;
        } else {
            *pOutT = fMin;
            *pOutVec = vNeg;
        }
    }
    return true;
}

// @ 0x00b48e00
void SteerVec::push_back()
{
    if (mpEnd < mpCap) {
        SteerNode* p = mpEnd;
        mpEnd = p + 1;
        if (p)
            p->mField04 = 1;
    } else {
        SteerNode tmp;
        tmp.mField04 = 1;
        DoInsertValue(mpEnd, &tmp);
    }
}

// @ 0x00b48ea0
void __cdecl FUN_00b48ea0(float dt)
{
    cIceEntry* it = g_167eb70_s00b4_8110->mpIceBegin;
    cIceEntry* p  = it + 1;
    if (it != g_167eb70_s00b4_8110->mpIceEnd) {
        do {
            _ReadWriteBarrier();
            it->mValue -= dt;
            if (it->mValue <= 0.0f) {
                cIceEntry* pEnd = g_167eb70_s00b4_8110->mpIceEnd;
                cIceEntry* s = p;
                while (s != pEnd) {
                    s[-1] = *s;
                    ++s;
                }
                --g_167eb70_s00b4_8110->mpIceEnd;
            } else {
                ++it;
                ++p;
            }
        } while (it != g_167eb70_s00b4_8110->mpIceEnd);
    }
}

// @ 0x00b48f20
void FUN_00b48f20(float* param_1, float param_2, float* param_3, float param_4)
{
  float* pfVar1 = param_3;
  float local_30 = param_3[0] - param_1[0];
  float fVar5 = param_2 + param_4;
  float local_2c = param_3[1] - param_1[1];
  float local_28 = param_3[2] - param_1[2];
  float fVar6 = sqrtf(local_28 * local_28 + (local_2c * local_2c + local_30 * local_30));

  float t2 = fVar5 + 2.0f;
  float t1 = fVar5 * 1.5f;
  float maxd = (t1 <= t2) ? t1 : t2;

  float param_4b = ((float (__thiscall*)(void*))VFn(*(void**)((char*)param_1 + 0x80), 0xc8))(*(void**)((char*)param_1 + 0x80));

  if (fVar6 < maxd) {
    float inv = 1.0f / fVar6;
    float fStack_24 = inv * local_30;
    float fStack_20 = local_2c * inv;
    float fStack_1c = local_28 * inv;

    int iVar2 = ((int (__fastcall*)(void*))FUN_00c41ec0)(*(void**)((char*)param_1 + 0x80));
    if (*(int*)((char*)iVar2 + 0x5c) != 0) {
      float dx = pfVar1[0] - *(float*)((char*)iVar2 + 0x14);
      float dz = pfVar1[2] - *(float*)((char*)iVar2 + 0x1c);
      float dy = pfVar1[1] - *(float*)((char*)iVar2 + 0x18);
      if ((dx * dx + dz * dz + dy * dy) < fVar5 * fVar5) {
        float ax = param_1[0] - *(float*)((char*)iVar2 + 0x14);
        float az = param_1[2] - *(float*)((char*)iVar2 + 0x1c);
        float ay = param_1[1] - *(float*)((char*)iVar2 + 0x18);
        if ((ax * ax + az * az + ay * ay) < fVar6 * fVar6) return;
      }
      ((void (__fastcall*)(void*))FUN_00b48e00)((char*)param_1 + 0x84);
      float* e = (float*)(*(int*)((char*)param_1 + 0x88) - 0x2c);
      e[5] = 0.3f;
      *(int*)e = 1;
      e[2] = pfVar1[0];
      e[3] = pfVar1[1];
      e[4] = pfVar1[2];
      e[6] = fVar5;
      e[7] = maxd;
    }

    float* vel = (float*)((void* (__fastcall*)(void*))FUN_00d20610)(*(void**)((char*)param_1 + 0x80));
    float fStack_3c = vel[0];
    float fStack_38 = vel[1];
    float fStack_34 = vel[2];

    if (sqrtf(fStack_38 * fStack_38 + (fStack_34 * fStack_34 + fStack_3c * fStack_3c)) < param_4b
        && *(int*)((char*)iVar2 + 0x5c) != 0) {
      fStack_3c = *(float*)((char*)iVar2 + 0x14) - param_1[0];
      fStack_38 = *(float*)((char*)iVar2 + 0x18) - param_1[1];
      fStack_34 = *(float*)((char*)iVar2 + 0x1c) - param_1[2];
      if (fStack_3c == DAT_0167eb8c && fStack_38 == DAT_0167eb90 && fStack_34 == DAT_0167eb94)
        return;
      float fStack_18[3];
      float* n = (float*)FUN_00436ce0(fStack_18, &fStack_3c);
      fStack_3c = n[0];
      fStack_38 = n[1];
      fStack_34 = n[2];
      if (1.0f < param_4b) {
        fStack_3c = fStack_3c * param_4b;
        fStack_38 = fStack_38 * param_4b;
        fStack_34 = fStack_34 * param_4b;
      }
    }

    float dot = (fStack_38 * local_2c + fStack_3c * local_30) + fStack_34 * local_28;
    if (0.0f < dot) {
      local_30 = param_1[0];
      local_2c = param_1[1];
      local_28 = param_1[2];
      if (fVar6 < fVar5 && 1.5258789e-05f < fVar6) {
        float k = (fVar5 - fVar6) + 0.1f;
        local_30 = local_30 - fStack_24 * k;
        local_2c = local_2c - fStack_20 * k;
        local_28 = local_28 - fStack_1c * k;
      }
      float fStack_18[3];
      FUN_00699800(fStack_18, pfVar1, fVar5, &local_30, &fStack_3c);
      if (fStack_18[0] != DAT_0167eb8c || fStack_18[1] != DAT_0167eb90 || fStack_18[2] != DAT_0167eb94) {
        fStack_24 = fStack_18[0] - local_30;
        fStack_20 = fStack_18[1] - local_2c;
        fStack_1c = fStack_18[2] - local_28;
        float auStack_c[3];
        float* n2 = (float*)FUN_00449c20(auStack_c, &fStack_24);
        fStack_24 = dot * n2[0];
        fStack_20 = n2[1] * dot;
        fStack_1c = n2[2] * dot;
        ((void (__fastcall*)(void*))FUN_00b48e00)((char*)param_1 + 0x84);
        float* e = (float*)(*(int*)((char*)param_1 + 0x88) - 0x2c);
        *(int*)e = 2;
        e[2] = fStack_24;
        e[3] = fStack_20;
        e[4] = fStack_1c;
      }
    }
  }
}

// @ 0x00b493e0
void FUN_00b493e0(void* param_1)
{
  int* edi;
  if (*(void**)((char*)param_1 + 0x80) == 0) {
    edi = 0;
  } else {
    void* o = *(void**)((char*)param_1 + 0x80);
    edi = (int*)((int (__thiscall*)(void*, int))VFn(o, 0xb8))(o, 0xce9f6639);
    if (edi != 0) {
      if (*(char*)((char*)edi + 0xf90) == 0) return;
      int i = ((int (__fastcall*)(void*))FUN_00c0c2f0)(edi);
      if (i < 2) return;
    }
  }

  void* o2 = *(void**)((char*)param_1 + 0x80);
  float* vel = (float*)((void* (__fastcall*)(void*))FUN_00d20610)(o2);
  if (vel[0] == DAT_0167eb8c && vel[1] == DAT_0167eb90 && vel[2] == DAT_0167eb94)
    return;

  {
    void* o3 = *(void**)((char*)param_1 + 0x80);
    float fStack_2c = ((float (__thiscall*)(void*))VFn(o3, 0x74))(o3);
    float auStack_c[3];
    ((void (__thiscall*)(void*, void*))VFn(o3, 0x5c))(o3, auStack_c);

    int* p3 = edi;
    if (p3 == 0 || ((void* (__thiscall*)(void*))VFn(p3, 0x20))(p3) != (void*)0x18eb45e) {
      // 0xb496b9 : walk the c420d0 list
      void* o4 = *(void**)((char*)param_1 + 0x80);
      int* pit = ((int* (__fastcall*)(void*))FUN_00c420d0)(o4);
      int* it = (int*)pit[0];
      int* end = (int*)pit[1];
      while (it != end) {
        int* e = (int*)*it;
        if (*(char*)((char*)e + 0x70) != 0
            && *(char*)((char*)e + 0x75) != 0
            && (*(unsigned char*)((char*)e + 0x50) & 0x10) == 0) {
          float v74 = ((float (__thiscall*)(void*))VFn(e, 0x74))(e);
          void* u = ((void* (__thiscall*)(void*))VFn(e, 0x2c))(e);
          FUN_00b48f20((float*)param_1, fStack_2c, (float*)u, v74);
        }
        ++it;
      }
      return;
    }

    int x = FUN_00b3d310();
    if (*(int*)((char*)x + 0x20) == 0) {
      // 0xb49569 : idle-animation driven target
      if (((*(unsigned int*)((char*)p3 + 0xb58) >> 8) & 1) == 0
          && FUN_00b5b800() == (void*)0x1654c01) {
        int r = ((int (__thiscall*)(void*, int, int))FUN_00bc96a0)(
            (void*)(*(int*)((char*)p3 + 0xb4c) + 8), 0x4000000, 0);
        if (r != 0) {
          int a = FUN_00d99980(r);
          if (a != 0) {
            void* esi2 = (void*)(a + 0xc0);
            float v74 = ((float (__thiscall*)(void*))VFn(esi2, 0x74))(esi2);
            void* u = ((void* (__thiscall*)(void*))VFn(esi2, 0x2c))(esi2);
            FUN_00b48f20((float*)param_1, fStack_2c, (float*)u, v74 * 5.0f);
          }
        }
      }
    } else {
      // 0xb494bd : walk the neighbour vector at p3+0x1124
      int* vec[2];
      void* tmp;
      ((int* (__thiscall*)(void*, void*, void*))FUN_00b41a40)((void*)vec, (void*)((char*)p3 + 0x1124), &tmp);
      int* it = vec[0];
      int* end = vec[1];
      while (it != end) {
        int* e8 = *(int**)((char*)*it + 8);
        void* obj2 = e8 ? (void*)((char*)e8 + 0xc0) : 0;
        if (*(char*)((char*)obj2 + 0x70) != 0) {
          float v74 = ((float (__thiscall*)(void*))VFn(obj2, 0x74))(obj2);
          void* u = ((void* (__thiscall*)(void*))VFn(obj2, 0x2c))(obj2);
          FUN_00b48f20((float*)param_1, fStack_2c, (float*)u, v74);
        }
        do {
          ++it;
          if (it == end) goto done;
        } while (((int (__thiscall*)(void*, void*))FUN_00c02600)(&it, (void*)*it) == 0);
      }
    }

  done:
    // 0xb495e4 : walk the second vector at p3+0x140c
    int* it2 = *(int**)((char*)p3 + 0x140c);
    int* end2 = *(int**)((char*)p3 + 0x1410);
    if (it2 == end2) return;
    if (((int (__thiscall*)(void*, void*))FUN_00c03520)(&it2, (void*)*it2) == 0) {
      ((void (__fastcall*)(void*))FUN_00b3d870)(&it2);
    }
    if (it2 == end2) return;
    do {
      int* e8 = *(int**)((char*)*it2 + 8);
      void* obj3 = e8 ? ((void* (__thiscall*)(void*, int))VFn(e8, 0xc))(e8, 0x1186577) : 0;
      if (*(char*)((char*)obj3 + 0x70) != 0) {
        float v74 = ((float (__thiscall*)(void*))VFn(obj3, 0x74))(obj3);
        void* u = ((void* (__thiscall*)(void*))VFn(obj3, 0x2c))(obj3);
        FUN_00b48f20((float*)param_1, fStack_2c, (float*)u, v74);
      }
      do {
        ++it2;
        if (it2 == end2) return;
      } while (((int (__thiscall*)(void*, void*))FUN_00c03520)(&it2, (void*)*it2) == 0);
    } while (it2 != end2);
    return;
  }
}

// @ 0x00b49730
void FUN_00b49730(void* param_1)
{
  int* esi;
  if (*(void**)((char*)param_1 + 0x80) == 0) {
    esi = 0;
  } else {
    void* o = *(void**)((char*)param_1 + 0x80);
    esi = (int*)((int (__thiscall*)(void*, int))VFn(o, 0xb8))(o, 0xd0036e08);
    if (esi != 0) {
      if (*(int*)((char*)esi + 0x2b0) == 3) return;
      if (*(char*)((char*)esi + 0xf90) == 0) return;
    }
  }

  int* edi = (int*)FUN_00b3d350();
  float r = ((float (__thiscall*)(void*, void*, int))FUN_00b7e430)(edi, param_1, 0);
  if (r > -1.0f) {
    float fStack_38[3];
    ((void (__thiscall*)(void*, float*, void*))FUN_00b7ee70)(edi, fStack_38, param_1);

    float scale = 0.5f;
    if (((*(unsigned int*)((char*)esi + 0xb58) >> 9) & 1) != 0) {
      if (FUN_00b5b800() == (void*)0x1654c05) scale = 5.0f;
      else scale = 0.5f;
    }

    float a = (-1.0f - r) * -1.0f;
    float m = (1.0f <= a) ? 1.0f : a;
    float k = m * scale;

    float c0 = fStack_38[0] * k;
    float c1 = fStack_38[1] * k;
    float c2 = fStack_38[2] * k;

    unsigned end = *(unsigned*)((char*)param_1 + 0x88);
    if (end < *(unsigned*)((char*)param_1 + 0x8c)) {
      *(unsigned*)((char*)param_1 + 0x88) = end + 0x2c;
      if (end != 0) *(int*)(end + 4) = 1;
    } else {
      int val[0x2c / 4];
      val[1] = 1;
      ((void (__thiscall*)(void*, void*, void*))FUN_00b47600)((char*)param_1 + 0x84, (void*)end, val);
    }
    int* e = (int*)(*(int*)((char*)param_1 + 0x88) - 0x2c);
    *(int*)e = 2;
    *(float*)((char*)e + 8) = c0;
    *(float*)((char*)e + 0xc) = c1;
    *(float*)((char*)e + 0x10) = c2;
  }
}

// @ 0x00b498d0
void FUN_00b498d0(ActionCtx* param_1)
{
    C* c;
    if (param_1->m_creature != 0) {
        c = param_1->m_creature->GetComponent(0xce9f6639);
        if (c != 0) {
            if (c->m_f90 == 0) return;
            if (c->FUN_00c0c2f0() < 2) return;
        }
    } else {
        c = 0;
    }

    if (GetSim_s00b4_98d0()->m_20 != 0
        || BitTest(&c->m_b58, 9)
        || c->Flag388()
        || GetCurrentGameMode_s00b4_98d0() == &g_Mode_1654c05)
    {
        uint32_t slot;                                  // placeholder for the f temp slot
        float f = param_1->m_creature->GetRadius();
        float hi = f + 2.0f;
        float lo = f * 1.5f;
        (void)slot;
        float* p = &hi;
        if (lo <= hi) p = &lo;

        FixedVector<Found*, 256> list;
        ObjectFinder* finder = GetObjectFinder();
        finder->Query(param_1->m_creature->GetDirection(), &list, 0x1f, *p, 0, 0);

        for (Found** it = list.mpBegin; it != list.mpEnd; ++it) {
            Found* o = *it;
            if (o->m_88 == 3 && (o->m_34 & 1)) continue;
            FUN_00b48f20(param_1, hi, (char*)o + 0x38, o->m_44);
        }
    }
}

// @ 0x00b4a720
void FUN_00b4a720(Loco* self, uint32_t dtMs, char flag, char applyCorrection)
{
    float dt = (float)dtMs * 0.001f;
    const Vec3_s00b4_a720* pv = self->GetVelocity();
    Vec3_s00b4_a720 vel0 = *pv;
    Vec3_s00b4_a720 acc = kZero_s00b4_a720;
    bool replace = false;

    for (Impulse* p = self->mImpBegin; p != self->mImpEnd; ++p) {
        switch (p->mode) {
        case 1:
            replace = true;
        case 0:
            acc.x = acc.x + p->x;
            acc.y = p->y + acc.y;
            acc.z = p->z + acc.z;
            break;
        }
    }
    {
        // mImpulses.clear(): erase(begin, end)
        Impulse* last = self->mImpEnd;
        Impulse* first = self->mImpBegin;
        Impulse* d = first;
        for (Impulse* s = last; s != last; ++s, ++d)
            *d = *s;
        self->mImpEnd = self->mImpEnd - (last - d);
    }
    if (!FUN_0059ab70(&acc))
        acc = kZero_s00b4_a720;

    Planet* pm = GetPlanetModel();
    bool grounded = self->mGrounded;
    switch (self->mPlanetCorrection) {
    case 0:
    case 1:
        flag = 0;
        if (!GetUniverseContext() && pm && pm->IsLoaded()) {
            float r = pm->GetRadiusAt(self->GetPosition());
            float w = pm->GetWaterHeight();
            Bounds* b = self->GetBounds();
            float h = (b->hi - b->lo) * 0.55f;
            if (r > w - h) {
                grounded = true;
                self->mGrounded = grounded;
            } else {
                grounded = false;
                self->mGrounded = grounded;
            }
        } else {
            self->mGrounded = true;
        }
        break;
    case 2:
    case 3: {
        const Vec3_s00b4_a720* pos = self->GetPosition();
        if (pm) {
            float r = pm->GetRadiusAt(pos);
            if (gFlag74) {
                float w = pm->GetWaterHeight();
                const float* m = &w;
                if (!(w > r))
                    m = &r;
                r = *m;
            }
            float lim = r + 1.52587890625e-05f;
            if (lim * lim < (pos->x * pos->x + pos->y * pos->y) + pos->z * pos->z ||
                0.0f < VelDot(self->GetVelocity(), acc, pos))
                grounded = false;
            else
                grounded = true;
            if (!gFlag74) {
                float w = pm->GetWaterHeight();
                Bounds* b = self->GetBounds();
                float h = (b->hi - b->lo) * 0.55f;
                if (r < w - h)
                    grounded = false;
            }
        }
        self->mGrounded = grounded;
        break;
    }
    case 4:
        self->mGrounded = false;
        break;
    case 5:
        self->mGrounded = false;
        flag = 0;
        break;
    case 6:
        flag = 0;
        break;
    }

    if (self->IsIdleAnimating()) {
        if (self->mSelfPowered) {
            self->FUN_00c431a0(dtMs);
            self->SetAngularVelocity(&kZero_s00b4_a720);
        }
    } else if (grounded) {
        self->SetVelocity(&kZero_s00b4_a720);
        self->SetAngularVelocity(&kZero_s00b4_a720);
    }

    Vec3_s00b4_a720 newVel;
    if (replace) {
        vel0.x = 0.0f; vel0.y = 0.0f; vel0.z = 0.0f;
        newVel.x = 0.0f; newVel.y = 0.0f; newVel.z = 0.0f;
    } else {
        const Vec3_s00b4_a720* v = self->GetVelocity();
        newVel = *v;
    }

    Component* comp = self->GetComponent(0xce9f6639);
    if (!GetSim_s00b4_a720()->b31 && comp) {
        bool ok = true;
        if (comp->GetType() != kTypeA) {
            ComponentB* cb = (comp->GetType() == kTypeB) ? (ComponentB*)comp : 0;
            if (!cb->FUN_00c232c0())
                ok = false;
        }
        if (ok) {
            float inv = 1.0f / dt;
            float ax = (newVel.x - vel0.x) * inv;
            float ay = (newVel.y - vel0.y) * inv;
            float az = (newVel.z - vel0.z) * inv;
            float aa = (az * az + ay * ay) + ax * ax;
            float len = sqrtf(aa);
            if (0.0f < (ay * vel0.y + az * vel0.z) + ax * vel0.x &&
                self->GetMaxAccel() < len) {
                float lim = self->GetMaxAccel();
                float k = 1.0f / sqrtf(aa + 1e-08f);
                newVel.x = (((k * ax) * lim) * dt) + vel0.x;
                newVel.y = (((ay * k) * lim) * dt) + vel0.y;
                newVel.z = (((az * k) * lim) * dt) + vel0.z;
            }
        }
    }
    newVel.x = newVel.x + acc.x;
    newVel.y = newVel.y + acc.y;
    newVel.z = newVel.z + acc.z;

    if (pm && !(self->mFlags & 0x100) && !self->mFlag71) {
        float F = pm->FUN_00b7e490();
        if ((!self->mSelfPowered || self->mStrategy == 0) && self->mGrounded) {
            const Vec3_s00b4_a720* pos = self->GetPosition();
            const Vec3_s00b4_a720* n0 = pm->FUN_00b7e3b0(&vel0, pos);
            float ni = 1.0f / sqrtf(n0->z * n0->z + n0->y * n0->y + n0->x * n0->x);
            Vec3_s00b4_a720 n;
            n.x = ni * n0->x; n.y = ni * n0->y; n.z = ni * n0->z;
            const Vec3_s00b4_a720* q = self->GetPosition();
            float qi = 1.0f / sqrtf(q->z * q->z + q->y * q->y + q->x * q->x);
            float h = ((-n.z * ((q->z * qi) * F) + -n.y * ((q->y * qi) * F)) +
                       -n.x * ((qi * q->x) * F)) * dt;
            float vv = (newVel.z * newVel.z + newVel.y * newVel.y) + newVel.x * newVel.x;
            if (vv < h * h) {
                newVel = kZero_s00b4_a720;
            } else {
                float k = 1.0f / sqrtf(vv);
                newVel.x = -(k * newVel.x) * h + newVel.x;
                newVel.y = -(newVel.y * k) * h + newVel.y;
                newVel.z = -(newVel.z * k) * h + newVel.z;
            }
        } else if (flag && !self->mGrounded) {
            const Vec3_s00b4_a720* p = self->GetPosition();
            float len = sqrtf(p->z * p->z + p->y * p->y + p->x * p->x);
            if (1.52587890625e-05f < len) {
                const Vec3_s00b4_a720* p2 = self->GetPosition();
                float k = 1.0f / len;
                newVel.x = ((k * p2->x) * F) * dt + newVel.x;
                newVel.y = ((p2->y * k) * F) * dt + newVel.y;
                newVel.z = ((p2->z * k) * F) * dt + newVel.z;
            }
        }
    }
    self->SetVelocity(&newVel);
    if (applyCorrection) {
        const Vec3_s00b4_a720* p = self->GetPosition();
        Vec3_s00b4_a720 out;
        out.x = newVel.x * dt + p->x;
        out.y = newVel.y * dt + p->y;
        out.z = newVel.z * dt + p->z;
        FUN_00b444c0(&out, self);
    }
}

// @ 0x00b4b060
bool B4B060::run(void* a1, void* a2, float* a3, float* a4, float f5, float f6, void* out)
{
    if (!a1 || !a2)
        return false;

    Vec3_s00b4_a720 delta;
    delta.x = a4[0];
    delta.y = a4[1];
    delta.z = a4[2];
    delta.x = delta.x - a3[0];
    delta.y = delta.y - a3[1];
    delta.z = delta.z - a3[2];

    float* pmin;
    if (f5 <= f6)
        pmin = &f5;
    else
        pmin = &f6;

    float* plane = (float*)((char*)out + 0x184);
    float* hit   = (float*)((char*)out + 0x190);

    if (!FUN_00b489d0(a1, a2, &delta.x, *pmin, hit, plane))
        return false;

    if (*hit == 0.0f) {
        u32* p = (u32*)plane;
        *(u32*)((char*)out + 0x194) = p[0];
        *(u32*)((char*)out + 0x198) = p[1];
        *(u32*)((char*)out + 0x19c) = p[2];
    }

    float x = plane[0];
    float y = plane[1];
    float z = plane[2];
    float inv = 1.0f / sqrtf((x * x + y * y) + z * z);
    x = x * inv;
    plane[0] = x;
    y = y * inv;
    plane[1] = y;
    z = z * inv;
    plane[2] = z;

    return FUN_00b45540(a1, a2, a3, a4, out) != 0;
}

// @ 0x00b4b1d0
int B4B1D0::init(void* a, void* b)
{
    PoolDesc d;
    char* base = (char*)this + 0x43c;

    d.head = 0;
    ((FixedPoolBase*)&d)->Init(base, 0x800, 8, 4, 0);
    d.begin = base;
    d.end = base + 0x800;
    d.elem = 8;
    d.alloc = (char*)this + 0x34;

    int h = (int)FUN_00921340(0x101);
    this->FUN_00b41a80((void*)h, a, (void**)&b, (void**)&b, b, (void**)&b, &d);

    F2* f = (F2*)&d;
    f->a = 10000.0f;
    f->b = 2.0f;
    *(F2*)((char*)this + 0x10) = *f;
    d.begin = 0;
    *(int*)((char*)this + 0x18) = (int)d.begin;

    unsigned n = (unsigned)((PoolBase*)&d)->SizeFor(*(int*)((char*)this + 0xc));
    if (n > *(unsigned*)((char*)this + 8))
        DoFreeNodes((int)n);
    return (int)this;
}

// @ 0x00b4b2b0
int PairVec::remove(int* key)
{
    int* last = this->end;
    int* it = (int*)FUN_00b41ea0(this->begin, last, key, this->flags14);
    if (it == last || *key < *it || it == it + 2)
        it = last;
    if (it == last)
        return 0;

    int* src = it + 2;
    if (src < last) {
        do {
            it[0] = src[0];
            it[1] = src[1];
            src += 2;
            it += 2;
        } while (src != last);
    }
    this->end = this->end - 2;
    return 1;
}

// @ 0x00b4b320
void __cdecl FUN_00b4b320(void* a, void* b, void* nrm, float f)
{
    ContactLocals L;

    ((ContactObj*)a)->FUN_00b3d9c0(L.local5c);
    float radius = ((ContactObj*)a)->FUN_00b3d630();

    if (g_167ecc4 != 0) {
        ((B4B060*)0x15696f0)->run(a, b, (float*)((char*)a + 0x1c),
                                   (float*)((char*)b + 0x1c), f, f, nrm);
        return;
    }

    L.box.lo = Vec3_s00b4_a720(g_1461150, g_1461150, g_1461150);
    L.box.hi = Vec3_s00b4_a720(g_13f51ac, g_13f51ac, g_13f51ac);
    ((ContactObj*)b)->FUN_00b3f420(&L.box);

    L.sph.s0 = 0;
    L.sph.s1 = 0;
    L.sph.x = g_167eb8c;
    L.sph.y = g_167eb90;
    L.sph.z = g_167eb94;
    L.sph.r = g_1485720;
    L.mtx.Assign(&g_167ec08_s00b4_a720);

    u32 flags = (u32)((ContactObj*)b)->FUN_00b3f6c0(&L.sph);
    if (*(char*)((char*)a + 0x34) == 0 || *(char*)((char*)b + 0x34) == 0)
        flags = 1;
    else
        flags &= 0xffffff00u;

    FUN_00b3fe40(L.local5c, radius, &L.box, &L.sph, (int)flags, nrm);
}

// @ 0x00b4b4a0
void __cdecl FUN_00b4b4a0()
{
    int one = 1;
    int* pn = &((WorldB4*)g_167eb70_s00b4_a720)->fieldB8;
    if (*pn <= 1)
        pn = &one;
    int n = *pn;

    if (n > 0) {
    int remaining = n;
    do {
        int key = ((WorldB4*)g_167eb70_s00b4_a720)->mgr.GetPriority();
        EventNode* e;
        while ((e = ((WorldB4*)g_167eb70_s00b4_a720)->mgr.Find(&key)) != 0) {
            if (e->f38 != (u32)((WorldB4*)g_167eb70_s00b4_a720)->field00 ||
                !FUN_00b3fc80(e)) {
                u32 a = e->f4;
                u32 b = e->f8;
                ((WorldB4*)g_167eb70_s00b4_a720)->mgr.Remove((void*)e->f0);

                union {
                    u32 u;
                    struct { u16 lo, hi; } s;
                } pair;
                if (a < b) {
                    pair.s.hi = (u16)a;
                    pair.s.lo = (u16)b;
                } else {
                    pair.s.hi = (u16)b;
                    pair.s.lo = (u16)a;
                }
                u32 pairValue = pair.u;
                ((WorldB4*)g_167eb70_s00b4_a720)->pairs.remove((int*)&pairValue);
            }
        }
    } while (--remaining);
    }
}

// @ 0x00b4b590
void __fastcall FUN_00b4b590(void* self, int /*edx*/, void* obj)
{
    char* s = (char*)self;

    if (*(int*)(s + 0x20) == 1 &&
        ((GetTypeFn)VSLOT_s00b4_b590(obj, 0x20))(obj, 0) == 0x3ed8573u) {
        if (FUN_00b5b800() != (void*)0x01654c05) {
            uint u = ((GetTypeFn)VSLOT_s00b4_b590(obj, 0x20))(obj, 0);
            uint r = (uint)(-(int)(u != 0x3ed8573u)) & (uint)obj;
            if (*(int*)(r + 0x64) >= 0) {
                int e = 3, g = 7;
                if (*(int*)(r + 0x88) < 3) { g = 6; e = 0; }
                FUN_00b47730((void*)r, (void*)r, 2, g, 0, e);
            }
        }
    } else if (obj != 0) {
        void* p1 = ((GetSubFn)VSLOT_s00b4_b590(obj, 0x0c))(obj, 0, 0x01186577u);
        void* p2 = ((GetSubFn)VSLOT_s00b4_b590(obj, 0x0c))(obj, 0, 0x0116dd1bu);
        if (p1 != 0) {
            if (p2 != 0) {
                void* ref = p2;
                ((void (__fastcall*)(void*, int))VSLOT_s00b4_b590(p2, 0xbc))(p2, 0);
                FUN_00afc470(&ref);
                if (ref != 0)
                    ((void (__fastcall*)(void*, int))VSLOT_s00b4_b590(ref, 0xc0))(ref, 0);
            }
            if ((g_167eccc & 1) == 0) {
                g_167eccc |= 1;
                g_167ecc8 = FUN_00932e80("useGameplayPhantom", 0x811c9dc5u, 1);
            }
            void* key = FUN_00b532f0((void*)((GetTypeFn)VSLOT_s00b4_b590(obj, 0x20))(obj, 0));
            void* node = FUN_00b41ee0(obj, key);
            if (node != 0 &&
                (FUN_0064f350(node, 0xcf3b981du, 1) ||
                 FUN_0064f350(node, g_167ecc8, 0))) {
                if (*(int*)(s + 0x20) == 0) {
                    FUN_00b56090(obj, p1, p2, key);
                } else if (*(int*)(s + 0x20) == 1 && *(char*)((char*)p1 + 0x75) != 0) {
                    World70* w = g_167eb70_s00b4_b590;
                    uint kk = (uint)key;
                    uint ee = (uint)w->ht58.arr[w->ht58.count];
                    Iter it;
                    it.node = 0;
                    it.bucket = 0;
                    if ((uint)it.node == ee) { (void)kk; }
                    FUN_00b47e00(p2, p1, key);
                }
                if (p2 == 0) {
                    void* ref = p1;
                    ((void (__fastcall*)(void*, int))VSLOT_s00b4_b590(p1, 0xbc))(p1, 0);
                    FUN_00b45b50(&ref, &ref, 0);
                    if (ref != 0)
                        ((void (__fastcall*)(void*, int))VSLOT_s00b4_b590(ref, 0xc0))(ref, 0);
                }
            }
        }
    }
}

// @ 0x00b4b7b0
void WorldCleanup_s00b4_b7b0::Clear()
{
    void* first = mObjects.mpBegin;
    void* last = mObjects.mpEnd;
    mObjects.Erase(first, last);
    HashRange_s00b4_b7b0& lookup = mObjectLookup;
    void* buckets = lookup.mpBuckets;
    lookup.Clear(buckets, lookup.mnBucketCount);
    lookup.mnElementCount = 0;
}

// @ 0x00b4b7f0
void* __fastcall FUN_00b4b7f0(void* self, int /*edx*/, int* key)
{
    int* p  = (int*)self;
    int* first = (int*)*p;       // +0x00 begin
    int* last  = (int*)p[1];     // +0x04 end
    uchar cmp = *(uchar*)((char*)p + 0x14);

    int* it = (int*)FUN_00b41ea0(first, last, key, cmp);
    if (it == last || *key < *it) {
        int  k = *key;
        int  local[2];
        local[1] = 0;
        local[0] = k;
        if (it == last || *it <= k) {
            first = it;
            it = last;
        }
        it = (int*)FUN_00b41ea0(first, it, local, cmp);
        if (it == last || k < *it)
            it = (int*)FUN_00c797b0(p, 0, it, local);
    }
    return (char*)it + 4;
}

// @ 0x00b4b880
void* __fastcall FUN_00b4b880(void* self, int /*edx*/, int* key)
{
    int* p  = (int*)self;
    int* lo = (int*)*p;          // +0x00 begin
    int* hi = (int*)p[1];        // +0x04 end
    int* it = (int*)FUN_00b41ea0(lo, hi, key, *(uchar*)((char*)p + 0x14));
    if (it == hi || *key < *it) {
        int   k = *key;
        float f0 = 0.0f;
        if (it != hi && *it <= k) { lo = it; it = hi; }
        int tmp[2];
        tmp[0] = k;
        tmp[1] = *(int*)&f0;
        it = (int*)FUN_00b41ea0(lo, it, tmp, *(uchar*)((char*)p + 0x14));
        if (it == hi || k < *it) it = (int*)FUN_00c72d00(p, 0, it, tmp);
    }
    return (char*)it + 4;
}

// @ 0x00b4b910
void __cdecl FUN_00b4b910(uint /*mode*/)
{
    uint key;
    FUN_00b48e40((char*)g_167eb70_s00b4_b590 + 0x90, 0,
                 *(void**)((char*)g_167eb70_s00b4_b590 + 0x94),
                 *(void**)((char*)g_167eb70_s00b4_b590 + 0x90));
    key = 0;
    *(uint*)FUN_00564a10((char*)g_167eb70_s00b4_b590 + 0x90, 0, &key) = 0;
    key = 1;
    *(uint*)FUN_00564a10((char*)g_167eb70_s00b4_b590 + 0x90, 0, &key) |= 0xfde;
    key = 2;
    *(uint*)FUN_00564a10((char*)g_167eb70_s00b4_b590 + 0x90, 0, &key) |= 0xfde;
    key = 3;
    *(uint*)FUN_00564a10((char*)g_167eb70_s00b4_b590 + 0x90, 0, &key) |= 0xfde;
    key = 8;
    *(uint*)FUN_00564a10((char*)g_167eb70_s00b4_b590 + 0x90, 0, &key) |= 0xfde;
    key = 7;
    *(uint*)FUN_00564a10((char*)g_167eb70_s00b4_b590 + 0x90, 0, &key) |= 0xfde;
    key = 4;
    *(uint*)FUN_00564a10((char*)g_167eb70_s00b4_b590 + 0x90, 0, &key) |= 0x9ae;
    key = 10;
    *(uint*)FUN_00564a10((char*)g_167eb70_s00b4_b590 + 0x90, 0, &key) |= 0x98e;
    key = 9;
    *(uint*)FUN_00564a10((char*)g_167eb70_s00b4_b590 + 0x90, 0, &key) |= 0x9ae;
    key = 6;
    *(uint*)FUN_00564a10((char*)g_167eb70_s00b4_b590 + 0x90, 0, &key) |= 0x9ee;
    key = 5;
    *(uint*)FUN_00564a10((char*)g_167eb70_s00b4_b590 + 0x90, 0, &key) |= 0xa10;
    key = 0xb;
    *(uint*)FUN_00564a10((char*)g_167eb70_s00b4_b590 + 0x90, 0, &key) |= 0xffe;
}

// @ 0x00b4bae0
int __cdecl FUN_00b4bae0(uint a, uint b)
{
    union { uint u; struct { uint16_t lo, hi; } s; } pair;
    if (a < b) { pair.s.hi = (uint16_t)a; pair.s.lo = (uint16_t)b; }
    else       { pair.s.hi = (uint16_t)b; pair.s.lo = (uint16_t)a; }

    char* w = (char*)g_167eb70_s00b4_b590;
    void* end = *(void**)(w + 0x28);
    void* it  = FUN_00b41ea0(*(void**)(w + 0x24), end, &pair, *(uchar*)(w + 0x38));
    if (it == end || pair.u < *(uint*)it) it = end;

    if (it != *(void**)(w + 0x28)) {
        uint* v = (uint*)FUN_00b4b7f0((char*)g_167eb70_s00b4_b590 + 0x24, 0, (int*)&pair.u);
        void* node = FUN_00b721d0((char*)g_167eb70_s00b4_b590 + 8, 0, (void*)*v);
        if (node != 0 && *(uint*)((char*)node + 4) == a && *(uint*)((char*)node + 8) == b)
            return (int)node;
        FUN_00b4b2b0((char*)g_167eb70_s00b4_b590 + 0x24, 0, &pair);
    }
    return 0;
}

// @ 0x00b4bba0
int __cdecl FUN_00b4bba0(uint a, uint b)
{
    void* rec = FUN_00b72160((char*)g_167eb70_s00b4_b590 + 8);
    int node = (int)FUN_00b72210((char*)g_167eb70_s00b4_b590 + 8, 0, rec);
    *(uint*)(node + 4)  = a;
    *(uint*)(node + 8)  = b;
    *(float*)(node + 0x24) = 0.0f;

    union { uint u; struct { uint16_t lo, hi; } s; } pair;
    if (a < b) { pair.s.hi = (uint16_t)a; pair.s.lo = (uint16_t)b; }
    else       { pair.s.hi = (uint16_t)b; pair.s.lo = (uint16_t)a; }

    uint* v = (uint*)FUN_00b4b7f0((char*)g_167eb70_s00b4_b590 + 0x24, 0, (int*)&pair.u);
    *v = (uint)rec;
    return node;
}

// @ 0x00b4bc20
void __cdecl FUN_00b4bc20(char* a, char* b, float* p3, float* p4, float f1, float f2)
{
    *(uchar*)(a + 0x37) = 1;
    *(uchar*)(b + 0x37) = 1;
    int rec = FUN_00b4bae0(*(uint*)a, *(uint*)b);
    if (rec == 0) rec = FUN_00b4bba0(*(uint*)a, *(uint*)b);
    *(uint*)(rec + 0xc)  = *(uint*)p3;
    *(uint*)(rec + 0x10) = *(uint*)((char*)p3 + 4);
    *(uint*)(rec + 0x14) = *(uint*)((char*)p3 + 8);
    *(uint*)(rec + 0x18) = *(uint*)p4;
    *(uint*)(rec + 0x1c) = *(uint*)((char*)p4 + 4);
    *(uint*)(rec + 0x20) = *(uint*)((char*)p4 + 8);
    *(uint*)(rec + 0x38) = *(uint*)g_167eb70_s00b4_b590;
    float d1 = FUN_00b3dcd0(a);
    float d2 = FUN_00b3dcd0(b);
    *(float*)(rec + 0x30) = 1.0f / (d2 + d1);

    float cur = *(float*)(rec + 0x24);
    float m = (cur > -f1) ? cur : -f1;
    *(float*)(rec + 0x24) = m;
    float acc = m + g_167eb70_s00b4_b590->ac;
    float s = (acc >= 0.0f) ? acc : 0.0f;
    float r = (s / f2) * -0.1f;
    *(float*)(rec + 0x34) = r;
    *(float*)(rec + 0x34) = g_167eb70_s00b4_b590->a8 * r;
}

// @ 0x00b4bd40
uchar __cdecl FUN_00b4bd40(char* a, char* b)
{
    if (a == 0 || b == 0) return 0;

    if (*(int*)(a + 4) == 0) {
        if (*(char*)(*(char**)(a + 0x40) + 0x71) == 0) goto checks;
    } else if (*(int*)(a + 4) == 1) {
        if (*(char*)(*(char**)(a + 0x40) + 0x71) == 0) goto checks;
    }

    if (*(int*)(b + 4) == 0) {
        if (*(char*)(*(char**)(b + 0x40) + 0x71) != 0) return 0;
    } else if (*(int*)(b + 4) == 1) {
        if (*(char*)(*(char**)(b + 0x40) + 0x71) != 0) return 0;
    } else {
        return 0;
    }

checks:
    if (FUN_00b3dd40(a)) return 0;
    if (FUN_00b3dd40(b)) return 0;
    if (!FUN_00b3d5f0(a)) return 0;
    if (!FUN_00b3d5f0(b)) return 0;

    uint key = FUN_00b3d700(*(uint*)a, *(uint*)b);
    char* w = (char*)g_167eb70_s00b4_b590;
    if (FUN_00b47570((char*)w + 0x78, 0, &key) == *(void**)(w + 0x7c)) {
        uint* v = (uint*)FUN_00564a10((char*)w + 0x90, 0, a + 0x38);
        if ((*v & (1u << (*(uchar*)(b + 0x38) & 0x1f))) != 0) {
            if (*(int*)(a + 4) == 0 && *(int*)(b + 4) == 0) {
                *(uint*)(*(char**)(a + 0x40) + 0x1a0) = 0x7f7fffff;
                *(uint*)(*(char**)(b + 0x40) + 0x1a0) = 0x7f7fffff;
            }
            return 1;
        }
    }
    return 0;
}

// @ 0x00b4be50
void __cdecl FUN_00b4be50(char* a, char* b, float f)
{
    char* s = b;
    char* t = a;
    if (!FUN_00b4bd40(t, s)) return;

    if ((uint)t < (uint)s) { char* x = t; t = s; s = x; }
    if (*(int*)(t + 0xc) < *(int*)(s + 0xc)) { char* x = t; t = s; s = x; }

    float nrm[3];
    nrm[0] = g_167eb8c;
    nrm[1] = g_167eb90;
    nrm[2] = g_167eb94;
    int count = 0;
    float contacts[32][3];

    switch (*(int*)(t + 0xc)) {
    case 0:
        switch (*(int*)(s + 0xc)) {
        case 0:  FUN_00b3e3e0(t, s, nrm, f); break;
        case 1:  FUN_00b43790(t, s, nrm, f); break;
        case 2:  FUN_00b4b320(t, s, nrm, f); break;
        case 3:  FUN_00b40a20(t, s, nrm, f); break;
        default: return;
        }
        break;
    case 1:
        switch (*(int*)(s + 0xc)) {
        case 1:  FUN_00b43990(t, s, nrm, f); break;
        case 2:  FUN_00b43bc0(t, s, nrm, f); break;
        case 3:  FUN_00b43d50(t, s, nrm, f); break;
        default: return;
        }
        break;
    case 2:
        switch (*(int*)(s + 0xc)) {
        case 2:
            if (!FUN_00b4b060((void*)0x015696f0, 0, t, s, t + 0x1c, s + 0x1c, f, f, nrm)) return;
            break;
        case 3: {
            char* x = t; t = s; s = x;
            FUN_00b4b320(t, s, nrm, f);
            break;
        }
        default: return;
        }
        break;
    case 3:
        FUN_00b3e3e0(t, s, nrm, f);
        break;
    default:
        return;
    }

    if (count > 0) {
        float r = (float)sqrt(nrm[2] * nrm[2] + nrm[1] * nrm[1] + nrm[0] * nrm[0]);
        for (int i = 0; i < count; ++i)
            FUN_00b4bc20(t, s, contacts[i], (float*)&nrm[2], r, f);
    }
}

// @ 0x00b4c0e0
void __cdecl FUN_00b4c0e0(float f)
{
    uint count = FUN_00bbb110(*(void**)((char*)g_167eb70_s00b4_b590 + 4));
    void* it = FUN_00bbbe20(*(void**)((char*)g_167eb70_s00b4_b590 + 4), &count);
    while (it != 0) {
        void* e = FUN_00b721d0((char*)g_167eb70_s00b4_b590 + 0x3c, (int)*(void**)it, *(void**)it);
        void* o = FUN_00b721d0((char*)g_167eb70_s00b4_b590 + 0x3c, (int)*(void**)it, *((void**)it + 1));
        if (e != 0 && o != 0) FUN_00b4be50((char*)e, (char*)o, f);
        it = FUN_00bbbe20(*(void**)((char*)g_167eb70_s00b4_b590 + 4), &count);
    }
}

// @ 0x00b4c170
void __fastcall FUN_00b4c170(void* self, int /*edx*/, int mode)
{
    char* s = (char*)self;
    if (*(int*)(s + 0x3c) == mode) return;

    *(uchar*)(s + 0x24) = 1;
    *(int*)(s + 0x2c) = 1;
    g_167eb88 = 0;

    switch (mode) {
    case 0x01654c01:
        *(int*)(s + 0x20) = 0;
        *(uchar*)(s + 0x25) = 1;
        *(uchar*)(s + 0x26) = 0;
        *(uchar*)(s + 0x27) = 1;
        *(uchar*)(s + 0x28) = 0;
        g_1569ab8 = 1;
        *(int*)(s + 0x2c) = 0;
        break;
    case 0x01654c02:
        *(int*)(s + 0x20) = 1;
        break;
    case 0x01654c10:
        *(int*)(s + 0x20) = 0;
        *(uchar*)(s + 0x25) = 1;
        *(uchar*)(s + 0x26) = 1;
        *(uchar*)(s + 0x27) = 0;
        *(uchar*)(s + 0x28) = 1;
        g_1569ab8 = (g_15acb40 == 0);
        *(int*)(s + 0x2c) = 0;
        break;
    case 0x01654c00:
    case 0x01654c04:
    case 0x01654c05:
    case 0x01654c06:
    default:
        *(int*)(s + 0x20) = 2;
        break;
    }

    FUN_00b4b910((uint)mode);
    *(int*)(s + 0x3c) = mode;

    switch (mode) {
    case 0x01654c00:
    case 0x01654c01:
    case 0x01654c02:
    case 0x01654c04:
    case 0x01654c05:
    case 0x01654c10:
        if (g_167eb75 == 0) g_167eb75 = 1;
        break;
    }
}

// @ 0x00b4d3f0
void* Blk50::copyFrom(const void* src)
{
    const float* s = (const float*)src;
    f[0] = s[0]; f[1] = s[1];
    f[4] = s[4]; f[5] = s[5]; f[6] = s[6]; f[7] = s[7];
    f[8] = s[8]; f[9] = s[9]; f[10] = s[10]; f[11] = s[11];
    f[12] = s[12]; f[13] = s[13]; f[14] = s[14]; f[15] = s[15];
    f[16] = s[16]; f[17] = s[17]; f[18] = s[18]; f[19] = s[19];
    return this;
}

// @ 0x00b4d470
void __cdecl FUN_00b4d470(char* dst, char* src)
{
    stf(dst, 0x4, ldf(src, 0x70));
    st32(dst, 0x8,  ld32(src, 0x10));
    st32(dst, 0xc,  ld32(src, 0x14));
    st32(dst, 0x10, ld32(src, 0x18));
    st32(dst, 0x14, ld32(src, 0x0));
    st32(dst, 0x18, ld32(src, 0x4));
    st32(dst, 0x1c, ld32(src, 0x8));
    st32(dst, 0x20, ld32(src, 0x80));
    st32(dst, 0x24, ld32(src, 0x84));
    st32(dst, 0x28, ld32(src, 0x88));
    st32(dst, 0x2c, ld32(src, 0x90));
    st32(dst, 0x30, ld32(src, 0x94));
    st32(dst, 0x34, ld32(src, 0x98));
    st32(dst, 0x38, ld32(src, 0x20));
    st32(dst, 0x3c, ld32(src, 0x24));
    st32(dst, 0x40, ld32(src, 0x28));
    st32(dst, 0x44, ld32(src, 0x30));
    st32(dst, 0x48, ld32(src, 0x34));
    st32(dst, 0x4c, ld32(src, 0x38));
    st32(dst, 0x50, ld32(src, 0x40));
    st32(dst, 0x54, ld32(src, 0x44));
    st32(dst, 0x58, ld32(src, 0x48));
    st32(dst, 0x5c, ld32(src, 0x50));
    st32(dst, 0x60, ld32(src, 0x54));
    st32(dst, 0x64, ld32(src, 0x58));
    stf(dst, 0x70, ldf(src, 0x60));
    stf(dst, 0x74, ldf(src, 0x64));
    st8(dst, 0x78, ld8(src, 0x6c));
    st8(dst, 0x79, ld8(src, 0x6d));
}

// @ 0x00b4d540
void* __fastcall FUN_00b4d540(char* self)
{
    stf(self, 0x10, g_oneF);
    st32(self, 0x14, 2);
    st32(self, 0x0, 0);
    st32(self, 0x4, 0);
    st32(self, 0x8, 0);
    st32(self, 0xc, 0);
    st32(self, 0x18, 0);
    stf(self, 0x20, 0.0f);
    stf(self, 0x24, 0.0f);
    stf(self, 0x3c, 0.0f);
    stf(self, 0x38, 0.0f);
    stf(self, 0x34, 0.0f);
    stf(self, 0x30, 0.0f);
    stf(self, 0x40, 0.0f);
    stf(self, 0x44, 0.0f);
    stf(self, 0x48, 0.0f);
    stf(self, 0x4c, 0.0f);
    stf(self, 0x50, 0.0f);
    stf(self, 0x54, 0.0f);
    stf(self, 0x58, 0.0f);
    stf(self, 0x5c, 0.0f);
    stf(self, 0x60, 0.0f);
    stf(self, 0x64, 0.0f);
    stf(self, 0x68, 0.0f);
    stf(self, 0x6c, 0.0f);
    st32(self, 0x70, 0);
    return self;
}

// @ 0x00b4d670
float __cdecl FUN_00b4d670(float* n, float t, float* d, float s, float* out)
{
    float f = -(t + g_oneF);
    float dot = n[2] * (d[2] * f) + n[1] * (d[1] * f) + n[0] * (d[0] * f);
    out[0] = n[0] * dot;
    out[1] = n[1] * dot;
    out[2] = n[2] * dot;
    out[3] = n[3] * dot;
    return dot * s;
}

// @ 0x00b4d770
void __fastcall FUN_00b4d770(char* self)
{
    do {
        char* n = (char*)ld32(self, 0x18);
        if (!n) n = (char*)ld32(self, 0xc);
        if (*(u16*)(n + 4) != 0) *(u16*)(n + 6) = (u16)(*(u16*)(n + 6) + 1);
        self = (char*)ld32(self, 0x70);
    } while (self);
}

// @ 0x00b4d850
void __fastcall FUN_00b4d850(char* self, int, char* c)
{
    if (ld8(self, 0x130) != 0) return;
    if (ld8(c, 0x18) == 2 && ld8(c + ld32(c, 0x10), 0x130) != 0) return;
    ((HkObj*)self)->hkAddOverlapping(c);
}

// @ 0x00b4d8c0
void __cdecl FUN_00b4d8c0(void)
{
    if (g_physObj != 0) g_physObj = 0;
}

// @ 0x00b4d930
void __fastcall FUN_00b4d930(char* self)
{
    stf(self, 0x14e8, g_useSabotage ? g_scale3f : 0.0f);
    stf(self, 0x14ec, g_oneF);
}

// @ 0x00b4d980
void* __fastcall FUN_00b4d980(char* self, int, char* src)
{
    st32(self, 0x0, ld32(src, 0x0));
    st32(self, 0x4, ld32(src, 0x4));
    st32(self, 0x8, ld32(src, 0x8));
    st32(self, 0x10, ld32(src, 0x10));
    st32(self, 0x14, ld32(src, 0x14));
    st32(self, 0x18, ld32(src, 0x18));
    st32(self, 0x1c, ld32(src, 0x1c));
    stf(self, 0x20, ldf(src, 0x20));
    st32(self, 0x24, ld32(src, 0x24));
    st32(self, 0x28, ld32(src, 0x28));
    ((Blk50*)(self + 0x30))->copyFrom(src + 0x30);
    st32(self, 0x80, ld32(src, 0x80));
    return self;
}

// @ 0x00b4e1d0
void __cdecl FUN_00b4e1d0(char* a1, char* a2)
{
    i32 key;
    i32* found = ((HkObj_s00b4_e1d0*)a2)->find961(&key, 6);
    u8 flag = (found[0] != 0);

    float* pp = ((FnGetVec)(*(void**)(*(u32*)a1 + 0x2c)))(a1, 0);
    float pos[4];
    pos[0] = pp[0];
    pos[1] = pp[1];
    pos[2] = pp[2];
    pos[3] = 0.0f;
    FUN_00b4dee0(a1, flag, pos);

    float* q = ((FnGetVec)(*(void**)(*(u32*)a1 + 0x30)))(a1, 0);
    float x = q[0], y = q[1], z = q[2], w = q[3];

    hkTransform_s00b4_e1d0 xf;
    xf.rot[0]  = 1.0f - (z * z + y * y) * g_two;
    xf.rot[1]  = (w * z + y * x) * g_two;
    xf.rot[2]  = (z * x - w * y) * g_two;
    xf.rot[3]  = 0.0f;
    xf.rot[4]  = (y * x - w * z) * g_two;
    xf.rot[5]  = 1.0f - (z * z + x * x) * g_two;
    xf.rot[6]  = (w * x + z * y) * g_two;
    xf.rot[7]  = 0.0f;
    xf.rot[8]  = (w * y + z * x) * g_two;
    xf.rot[9]  = (z * y - w * x) * g_two;
    xf.rot[10] = 1.0f - (y * y + x * x) * g_two;
    xf.rot[11] = 0.0f;
    xf.tr[0] = pos[0];
    xf.tr[1] = pos[1];
    xf.tr[2] = pos[2];
    xf.tr[3] = pos[3];

    char* tr = *(char**)(a2 + 0x24);
    if (((hkMatrix3_s00b4_e1d0*)tr)->isApproximatelyEqual(*(hkMatrix3_s00b4_e1d0*)xf.rot, 0.001f).b == 0) {
        ((hkShapePhantom*)a2)->setTransform(&xf);
        return;
    }
    float* cur = (float*)(tr + 0x30);
    if (fabsf(pos[0] - cur[0]) > 0.001f ||
        fabsf(pos[1] - cur[1]) > 0.001f ||
        fabsf(pos[2] - cur[2]) > 0.001f) {
        ((hkShapePhantom*)a2)->setPosition(pos, 0.0f);
    }
}

// @ 0x00b4e620
void __cdecl FUN_00b4e620(u32 a1, float a2, float a3, u32 a4, float a5, float a6, float* a7)
{
    u32 sys = GetSystemAT();
    if ((sys != 0) && (a1 != 0) && (a4 != 0) && (g_thr1 < a2 + a5)) {
        float v[3];
        v[0] = a7[0];
        v[1] = a7[1];
        v[2] = a7[2];
        float thr = g_thr400;
        if ((g_thr50 < a3) || (g_thr50 < a6)) {
            thr = g_thr10000;
        }
        float* p = ((FnGetVec)(*(void**)(*(u32*)sys + 0x10)))((void*)sys, 0);
        float dy = p[1] - v[1];
        float dx = p[0] - v[0];
        float dz = p[2] - v[2];
        if (dz * dz + dx * dx + dy * dy <= thr) {
            if (g_recorder == 0) {
                g_recorder = GetRecorderState();
                KillSetiEffects(g_patchId, g_recorder);
            }
            SetGlobalProperty(0x393e0cdeu, (float)a1);
            SetGlobalProperty(0x393e0cddu, (float)a4);
            SetGlobalProperty(0x50c5d67u, a7[0]);
            SetGlobalProperty(0x50c5d66u, a7[1]);
            SetGlobalProperty(0x50c5d65u, a7[2]);
            SetGlobalProperty(0xbdf087bcu, a2);
            SetGlobalProperty(0xbdf087bfu, a5);
            SetGlobalProperty(0x64b5d38bu, a3);
            SetGlobalProperty(0x64b5d388u, a6);
            SetGlobalProperty(0xe7166a0u, 0.0f);
        }
    }
}

// @ 0x00b4e820
void __cdecl FUN_00b4e820(char* a1, char a2, char a3, float* a4)
{
    if (a3 != 0) {
        if (GetCurrentGameMode_s00b4_e1d0() == 0x1654c10u) {
            cCollisionInfo info;
            FUN_00b4d470((char*)&info, (char*)a4);
            info.collisionType = 0;
            info.pGameDataA = a1;
            Simulator_OnEvent(&info);
        }
        if (AudioSystem() != 0) {
            char* t;
            if (a1 != 0) {
                FnGetByName getByName = (FnGetByName)(*(void**)(*(u32*)a1 + 0xc));
                t = getByName(a1, (char*)0x1186577);
            } else {
                t = 0;
            }
            char* tgt = *(char**)(t + 0x58);
            if (tgt == 0) {
                tgt = *(char**)(t + 0x54);
            }
            float scale = *(float*)(t + 0x8c);
            if (a2 != 0) {
                FUN_00b4e620((u32)tgt,
                             -((a4[10] * a4[2] + a4[9] * a4[1]) + a4[8] * a4[0]),
                             a4[0x18] * scale,
                             3, 0.0f, 0.0f, a4 + 4);
            } else {
                FUN_00b4e620((u32)tgt,
                             (a4[0xe] * a4[2] + a4[0xd] * a4[1]) + a4[0xc] * a4[0],
                             a4[0x19] * scale,
                             3, 0.0f, 0.0f, a4 + 4);
            }
        }
    }
}

// @ 0x00b4e980
void __cdecl FUN_00b4e980(char* a1, u32 a2, u32 a3, char a4, char a5, float* a6)
{
    if (a5 != 0) {
        if (g_eventHandler != 0) {
            cCollisionInfo info;
            FUN_00b4d470((char*)&info, (char*)a6);
            info.collisionType = 1;
            info.pGameDataA = a1;
            g_eventHandler(&info);
        }
        if (AudioSystem() != 0) {
            char* t;
            if (a1 != 0) {
                FnGetByName getByName = (FnGetByName)(*(void**)(*(u32*)a1 + 0xc));
                t = getByName(a1, (char*)0x1186577);
            } else {
                t = 0;
            }
            char* tgt = *(char**)(t + 0x58);
            if (tgt == 0) {
                tgt = *(char**)(t + 0x54);
            }
            float scale = *(float*)(t + 0x8c);
            if (a4 != 0) {
                FUN_00b4e620((u32)tgt,
                             -((a6[10] * a6[2] + a6[9] * a6[1]) + a6[8] * a6[0]),
                             a6[0x18] * scale,
                             a3, 0.0f, 0.0f, a6 + 4);
            } else {
                FUN_00b4e620((u32)tgt,
                             (a6[0xe] * a6[2] + a6[0xd] * a6[1]) + a6[0xc] * a6[0],
                             a6[0x19] * scale,
                             a3, 0.0f, 0.0f, a6 + 4);
            }
        }
        (void)a2;
    }
}

// @ 0x00b4ead0
void __cdecl FUN_00b4ead0(char* a1, char* a2, char a3, float* a4)
{
    if (a3 != 0) {
        if (GetCurrentGameMode_s00b4_e1d0() == 0x1654c10u) {
            cCollisionInfo info;
            FUN_00b4d470((char*)&info, (char*)a4);
            info.collisionType = 2;
            info.pGameDataA = a1;
            info.pGameDataB = a2;
            Simulator_OnEvent(&info);
        }
        if (g_eventHandler != 0) {
            cCollisionInfo info;
            FUN_00b4d470((char*)&info, (char*)a4);
            info.collisionType = 2;
            info.pGameDataA = a1;
            info.pGameDataB = a2;
            g_eventHandler(&info);
        }
        if (AudioSystem() != 0) {
            char* t1;
            if (a1 != 0) {
                t1 = ((FnGetByName)(*(void**)(*(u32*)a1 + 0xc)))(a1, (char*)0x1186577);
            } else {
                t1 = 0;
            }
            char* t2;
            if (a2 != 0) {
                t2 = ((FnGetByName)(*(void**)(*(u32*)a2 + 0xc)))(a2, (char*)0x1186577);
            } else {
                t2 = 0;
            }
            char* tg1 = *(char**)(t1 + 0x58);
            if (tg1 == 0) {
                tg1 = *(char**)(t1 + 0x54);
            }
            char* tg2 = *(char**)(t2 + 0x58);
            if (tg2 == 0) {
                tg2 = *(char**)(t2 + 0x54);
            }
            FUN_00b4e620((u32)tg1,
                         -((a4[9] * a4[1] + a4[10] * a4[2]) + a4[0] * a4[8]),
                         *(float*)(t1 + 0x8c) * a4[0x18],
                         (u32)tg2,
                         (a4[0xd] * a4[1] + a4[0xe] * a4[2]) + a4[0xc] * a4[0],
                         *(float*)(t2 + 0x8c) * a4[0x19],
                         a4 + 4);
        }
    }
}

// @ 0x00b4ec70
u8 __cdecl FUN_00b4ec70(float* out, float a, float b, float c, const float* in, float scale)
{
    float t;
    if (a <= 0.0f) {
        return 0;
    }
    t = c - (a - b);
    if (t <= g_eps) {
        return 0;
    }
    if (0.0f <= t) {
        if (t > b * g_two) t = b * g_two;
    } else {
        t = 0.0f;
    }
    float v = -((((((t * t) * b) * g_three - (t * t) * t) *
                  (g_pi * g_third)) * g_one) * scale);
    out[0] = in[0] * v;
    out[1] = in[1] * v;
    out[2] = in[2] * v;
    out[3] = in[3] * v;
    return 1;
}

// @ 0x00b4ed50
bool __cdecl FUN_00b4ed50(float dt, Loco_s00b4_ed50* obj, GoalHolder* goal, hkEntity_s00b4_ed50* ent, float depthRef, float limit)
{
    if (!ent || ent->m_flag99 || !obj->m_flag75)
        return false;

    bool result = false;
    Owner* owner = (Owner*)ent->getProperty(4).p;
    if (ent->isActive() && (GetSim_s00b4_ed50()->b26 || obj->FUN_00c887c0() < kRestThreshold)) {
        hkVector4_s00b4_ed50 a;            // property-3 value, correction vector, then the radial/tangent split
        hkVector4_s00b4_ed50 b;            // box centre scratch, then the impulse
        hkVector4_s00b4_ed50 c;            // radial direction, then the tangential part / torque
        *(int*)&a.x = ent->getProperty(3).i;
        const hkVector4_s00b4_ed50* pos = ent->m_motion->position();
        Bounds* bounds = obj->GetBounds();

        // radial direction of the position
        const hkReal lenSq = pos->x * pos->x + pos->y * pos->y + pos->z * pos->z;
        hkReal inv = 0.0f;
        if (lenSq != 0.0f)
            inv = hkSqrtInverse(lenSq);
        c.x = pos->x * inv;
        c.y = pos->y * inv;
        c.z = pos->z * inv;
        c.w = pos->w * inv;

        float centre = (bounds->hi - bounds->lo) * 0.5f + bounds->lo;
        float radial;
        if (ent->getProperty(8).i != 0) {
            Aabb box;
            const Aabb* ab = obj->GetAabb(&box);
            b.x = (ab->v[0] + ab->v[3]) * 0.5f;
            b.z = (ab->v[5] + ab->v[2]) * 0.5f;
            b.y = (ab->v[4] + ab->v[1]) * 0.5f;
            radial = (float)(LengthXZY(b) - centre);
        } else {
            const hkVector4_s00b4_ed50* v = ent->m_motion->velocity();
            radial = (float)LengthXYZ(*v);
        }

        GetPlanetModel_s00b4_ed50()->GetRadiusAt(pos);
        double posLen = LengthXYZ(*pos);
        double depth = ((double)depthRef - posLen) + (bounds->hi - bounds->lo) * 0.5f;
        if (!(depth > 0.0) || !FUN_00b4ec70(&a, radial, a.x, depthRef, &c, limit))
            return false;

        b.x = a.x * dt;
        b.y = a.y * dt;
        b.z = a.z * dt;
        b.w = a.w * dt;
        result = true;
        obj->m_grounded = false;

        if (owner) {
            owner->m_intCC = 0;
            owner->m_flagC8 = true;
            bool noGoal = goal && goal->FUN_00c41ec0()->m_value == 0;
            float wTerm, wScale;
            if (gUseTangential && !noGoal) {
                const hkVector4_s00b4_ed50* u = owner->GetPending();
                float d = (u->x * c.x + u->z * c.z) + u->y * c.y;
                a.x = d * c.x;
                a.y = c.y * d;
                a.z = c.z * d;
                a.w = c.w * d;
                c.x = u->x - a.x;
                c.y = u->y - a.y;
                c.z = u->z - a.z;
                c.w = u->w - a.w;
                float mass = ent->m_motion->getMass();
                float s1 = -((mass * kForceScaleA) * dt);
                b.x = s1 * a.x + b.x;
                b.y = a.y * s1 + b.y;
                b.z = a.z * s1 + b.z;
                b.w = a.w * s1 + b.w;
                mass = ent->m_motion->getMass();
                float s2 = -((mass * kForceScaleB) * dt);
                b.x = s2 * c.x + b.x;
                b.y = c.y * s2 + b.y;
                b.z = c.z * s2 + b.z;
                wTerm = c.w;
                wScale = s2;
            } else {
                float mass = ent->m_motion->getMass();
                const hkVector4_s00b4_ed50* u = owner->GetPending();
                float s = -((mass * kForceScaleA) * dt);
                b.x = u->x * s + b.x;
                b.y = u->y * s + b.y;
                b.z = u->z * s + b.z;
                wTerm = u->w;
                wScale = s;
            }
            b.w = wTerm * wScale + b.w;
            owner->AddImpulse(&b);
            return result;
        }

        // no owner proxy: push the rigid motion directly
        float mass = ent->m_motion->getMass();
        hkVector4_s00b4_ed50 tmp;
        const hkVector4_s00b4_ed50* r = FUN_00b658c0(&tmp, ent);
        float s = -((mass * kForceScaleA) * dt);
        b.x = r->x * s + b.x;
        b.y = r->y * s + b.y;
        b.z = r->z * s + b.z;
        b.w = r->w * s + b.w;
        mass = ent->m_motion->getMass();
        const hkVector4_s00b4_ed50* r2 = FUN_00b65950(&tmp, ent);
        float s3 = -((mass * kTorqueScale) * dt);
        c.x = s3 * r2->x;
        c.y = r2->y * s3;
        c.z = r2->z * s3;
        c.w = r2->w * s3;
        ent->activate();
        ent->m_motion->applyLinearImpulse(b);
        ent->activate();
        ent->m_motion->applyAngularImpulse(c);
    }
    return result;
}

// @ 0x00b4f3e0
void __stdcall FUN_00b4f3e0(ListenerArg* arg)
{
    ListenerRef* ref = arg->mRef;
    if (ref->mActive != 1)
        return;
    hkEntity_s00b4_ed50* e = (hkEntity_s00b4_ed50*)((char*)ref + ref->mEntityOffset);
    if (!e)
        return;
    hkEntity_s00b4_ed50* ent = arg->mEntity;
    if (e == ((EntityLink*)ent)->mLinked)
        return;
    void* p = e->getProperty(4).p;
    if (p)
        ((ListOwner*)p)->append(ent);
}

// @ 0x00b4f420
void __stdcall FUN_00b4f420(ListenerArg* arg)
{
    if (!arg->mEnabled)
        return;
    ListenerRef* ref = arg->mRef;
    if (ref->mActive != 1)
        return;
    hkEntity_s00b4_ed50* e = (hkEntity_s00b4_ed50*)((char*)ref + ref->mEntityOffset);
    if (!e)
        return;
    hkEntity_s00b4_ed50* ent = arg->mEntity;
    if (e == ((EntityLink*)ent)->mLinked)
        return;
    void* p = e->getProperty(4).p;
    if (p)
        ((ListOwner*)p)->remove(ent);
}

// @ 0x00b4f470
hkPerpVectors* __cdecl FUN_00b4f470(const Vector3_s00b4_ed50* v)
{
    float w;
    float sx = gPerpBase.x, sy = gPerpBase.y, sz = gPerpBase.z;
    float tx = gPerpBase.x, ty = gPerpBase.y, tz = gPerpBase.z;
    const float y = v->y;
    const float z = v->z;

    if (z > y && z > v->x) {
        w = 0.25f * (v->x + y);
        tz = 0.5f * z - w;
        sz = -tz;
    } else if (y > v->x) {
        w = 0.25f * (v->x + z);
        ty = 0.5f * y - w;
        sy = -ty;
    } else {
        w = 0.25f * (y + z);
        tx = 0.5f * v->x - w;
        sx = -tx;
    }

    hkPerpVectors* obj = (hkPerpVectors*)gMemoryManager->allocate(0x30, 0x24);
    obj->mSizeAndFlags = 0x30;
    hkVector4_s00b4_ed50 a(tx, ty, tz, 0.0f);
    hkVector4_s00b4_ed50 b(sx, sy, sz, 0.0f);
    new (obj) hkPerpVectors(a, b, w);
    return obj;
}

// @ 0x00b4f610
Inner::Inner(const Inner& src)
{
    m0 = src.m0;
    m4 = src.m4;
    m8 = src.m8;
    mC = src.mC;
    m10 = src.m10;
    m14 = src.m14;
    m18 = src.m18;
    mH.CopyFrom(src.mH);
    m70 = src.m70;
}

// @ 0x00b4f660
int __cdecl FUN_00b4f660(void* obj, float value, int index, int kind)
{
    int r = 0;
    if (obj) {
        unsigned int flags = ((FlagWord*)obj)->mFlags;
        bool enabled = (flags & 0x4000) != 0;
        bool skipped = (flags & 0x40000) != 0;
        if (enabled) {
            int i = index;
            float f = value;
            if (!skipped) {
                if (kind == 3)
                    r = FUN_00b653d0(obj, gRenderCfg.mModeA, f, i);
                else if (kind == 6)
                    r = FUN_00b65250(obj, gRenderCfg.mModeB, f, i);
            }
        }
    }
    return r;
}

// @ 0x00b4f6d0
void __cdecl FUN_00b4f6d0(Loco_s00b4_ed50* loco, hkRefObject* ent)
{
    if (!ent)
        return;
    if (loco) {
        Aabb box;
        hkVector4_s00b4_ed50 lo, hi;
        loco->GetAabb(&box);
        const float margin = kAabbMargin;
        box.v[0] = box.v[0] - margin;
        box.v[1] = box.v[1] - margin;
        box.v[2] = box.v[2] - margin;
        box.v[3] = box.v[3] + margin;
        box.v[4] = box.v[4] + margin;
        box.v[5] = box.v[5] + margin;
        lo = hkVector4_s00b4_ed50(box.v[0], box.v[1], box.v[2], 0.0f);
        hi = hkVector4_s00b4_ed50(box.v[3], box.v[4], box.v[5], 0.0f);
        ent->mWorld->addAabb(&lo);
    }
    char flag;
    ent->mWorld->removeEntity(&flag, ent);
}

// @ 0x00b4f7c0
void* hkRefObject::scalarDtor(int flags)
{
    baseDtor();
    if (flags & 1)
        gMemoryManager->deallocate(this, mSizeAndFlags, 0x2e);
    return this;
}

// @ 0x00b4f7f0
void __cdecl FUN_00b4f7f0()
{
    if (!gRegistered_167ecd4)
        return;
    gRegistered_167ecd4->removeReference();
    if (gRegistered_167ecd4) {
        __declspec(align(16)) hkVector4_s00b4_ed50 scratch;
        gRegistered_167ecd4->mWorld->removeEntity(((char*)&scratch) + 15, gRegistered_167ecd4);
    }
    gRegistered_167ecd4 = 0;
}

// @ 0x00b4f830
Outer::Outer(const Key3& key, const Inner& inner)
{
    m0 = key.m0;
    m4 = key.m4;
    m8 = key.m8;
    mInner.m0 = inner.m0;
    mInner.m4 = inner.m4;
    mInner.m8 = inner.m8;
    mInner.mC = inner.mC;
    mInner.m10 = inner.m10;
    mInner.m14 = inner.m14;
    mInner.m18 = inner.m18;
    mInner.mH.CopyFrom(inner.mH);
    mInner.m70 = inner.m70;
}

// @ 0x00b4f8a0
It90 Table90::erase(Node90* node, Bucket90* bucket)
{
    It90 it;
    it.mNode = node->mNext;
    it.mBucket = bucket;
    while (!it.mNode) {
        unsigned int step = sizeof(Bucket90);
        it.mBucket = (Bucket90*)((char*)it.mBucket + step);
        it.mNode = it.mBucket->mHead;
    }
    if (bucket->mHead == node) {
        bucket->mHead = node->mNext;
        ::operator delete[](node);
        this->mCount = this->mCount - 1;
        return it;
    }
    Node90* prev = bucket->mHead;
    Node90* p = prev->mNext;
    while (p != node) {
        prev = p;
        p = p->mNext;
    }
    prev->mNext = node->mNext;
    ::operator delete[](node);
    Table90* self2 = this;
    --self2->mCount;
    return it;
}

// @ 0x00b4f930
It10 Table10::erase(Node10* node, Bucket10* bucket)
{
    It10 it;
    it.mNode = node->mNext;
    it.mBucket = bucket;
    while (!it.mNode) {
        unsigned int step = sizeof(Bucket10);
        it.mBucket = (Bucket10*)((char*)it.mBucket + step);
        it.mNode = it.mBucket->mHead;
    }
    if (bucket->mHead == node) {
        Bucket10* self = bucket;
        self->mHead = node->mNext;
        ::operator delete[](node);
        int n = mCount;
        mCount = n - 1;
        return it;
    }
    Node10* prev = bucket->mHead;
    Node10* p = prev->mNext;
    while (p != node) {
        prev = p;
        p = p->mNext;
    }
    prev->mNext = node->mNext;
    ::operator delete[](node);
    this->mCount = this->mCount - 1;
    return it;
}

// @ 0x00b4fae0
LinkNode* __stdcall FUN_00b4fae0(LinkNode* head, const Key3* key, int unused)
{
    if (!head)
        return 0;
    do {
        if (key->m0 == (int)head->mKey0 && key->m4 == (int)head->mKey4 && key->m8 == (int)head->mKey8)
            return head;
        head = head->mNext;
    } while (head);
    return 0;
}

// @ 0x00b4fbd0
void TableB::rehash(unsigned int n)
{
    NodeB** newBuckets = reserveBuckets(n);
    for (unsigned int i = 0; i < mNumBuckets; ++i) {
        NodeB* node = mBuckets[i];
        while (node) {
            unsigned int h = (node->mHash0 + node->mHash4) % n;
            NodeB* next = node->mNext;
            mBuckets[i] = next;
            node->mNext = newBuckets[h];
            newBuckets[h] = node;
            node = next;
            (void)node;
        }
    }
    if (mNumBuckets > 1 && mBuckets != (NodeB**)mStatic) {
        if ((char*)mBuckets < mHeapLo || (char*)mBuckets >= mHeapHi) {
            ::operator delete[](mBuckets);
        } else {
            *(NodeB**)mBuckets = mFreeList;
            mFreeList = (NodeB*)mBuckets;
        }
    }
    mBuckets = newBuckets;
    mNumBuckets = n;
}

// @ 0x00b4fc80
void __cdecl FUN_00b4fc80(PropHolder_s00b4_ed50* self, void* unused, void* props)
{
    if (!props)
        return;
    self->mPropB = SP_GetPropertyFloat(props, 0x635002bd, self->mPropB);
    self->mPropA = SP_GetPropertyFloat(props, 0x959b621c, self->mPropA);
    self->mPropC = SP_GetPropertyFloat(props, 0xfe64124b, self->mPropC);
    self->mPropD = SP_GetPropertyFloat(props, 0xc09b2ebf, self->mPropD);
    self->mFlag = SP_GetPropertyChar(props, 0x57a59e5f, self->mFlag);
    Vector3_s00b4_ed50 v;
    if (SP_GetPropertyAsVector3(props, 0xfc485e65, &v)) {
        self->mVecX = v.x;
        self->mVecY = v.y;
        self->mVecZ = v.z;
        self->mVecW = 0.0f;
    }
}

// @ 0x00b4fd80
void __cdecl FUN_00b4fd80(IVarHost* obj)
{
    g_167ece4 = (unsigned)ReadIntProp(obj, 0x7a2456e2, 0x3759d899);
    g_1569ae8 = ReadFloatProp(obj, 0x19b1e0f2, 1.0f);
    float f = ReadFloatProp(obj, 0x9c9f1c1b, 20.0f);
    g_1569aec = f * f;
    f = ReadFloatProp(obj, 0x421ce80f, 100.0f);
    g_1569af0 = f * f;
    g_1569af4 = ReadFloatProp(obj, 0x8ca0ae12, 100.0f);
}

// @ 0x00b4ffb0
void* __thiscall ObjFFB0::ctor(RC* param)
{
    *(RC**)((char*)this + 0x34) = param;
    *(int*)((char*)this + 8) = 0;
    *(void**)this = &g_vtblFB0;
    *(short*)((char*)this + 6) = 1;
    *(RC**)((char*)this + 0x38) = 0;
    *(RC**)((char*)this + 0x3c) = 0;

    ChildObj* child = (ChildObj*)this->m24->m24->GetChild();

    AssignRC((RC**)((char*)this + 0x38), child->m0c);
    AssignRC((RC**)((char*)this + 0x3c), child->m08);

    RC* m3c = *(RC**)((char*)this + 0x3c);
    *(int*)((char*)this + 0x40) = *(int*)((char*)m3c + 0x10);
    int n = *(int*)((char*)m3c + 8);
    *(int*)((char*)this + 0x44) = n;
    *(int*)((char*)this + 0x48) = n * n;
    *(float*)((char*)this + 0x4c) = child->f34;
    *(float*)((char*)this + 0x50) = child->f38;

    float neg = kNeg200;
    *(float*)((char*)this + 0x10) = neg;
    *(float*)((char*)this + 0x14) = neg;
    *(float*)((char*)this + 0x18) = neg;
    *(float*)((char*)this + 0x1c) = neg;
    float pos = kPos200;
    *(float*)((char*)this + 0x20) = pos;
    *(float*)((char*)this + 0x24) = pos;
    *(float*)((char*)this + 0x28) = pos;
    *(float*)((char*)this + 0x2c) = pos;
    return this;
}
