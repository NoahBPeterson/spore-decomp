// src/game/SPCreatureAnim/SPCreatureAnimManager.cpp -- migrated from slice(s) s00a0f350, s00a0e4c0, s00a0c690, s00a0aca0, s00a099e0, s00a06d50, s00a03da0, s00a02da0, s00a01810 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/SPCreatureAnimManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cViewer.h"
#include <math.h>
#include "nSPCreatureAnim/creature_instance_data.h"
#include "nSPCreatureAnim/creature_static_data.h"
#include "nSPCreatureAnim/queued_blender.h"
#include <stddef.h>
#include <string.h>
#include "SP/cSPCreatureAnimManager.h"
#include "EA/ArgScript/cCommandBase.h"

// ---- items of slice s00a01810 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct AnimReference {
    uint32_t animID;        // +0x00
    float    duration;      // +0x04
    float    durationScale; // +0x08
};
class RefObj;
class anim_qb;
class anim_query {
public:
    RefObj*      field_0;       // +0x00
    RefObj*      field_4;       // +0x04
    AnimReference anims[8];     // +0x08
    int          field_68;      // +0x68
    int          field_6C;      // +0x6C
    float        field_70;      // +0x70
    float        field_74;      // +0x74
    float        field_78;      // +0x78
    bool         field_7C;      // +0x7C
    int          mode;          // +0x80
    bool         idle;          // +0x84
    float        blendInTime;   // +0x88
    float        field_8C;      // +0x8C
    float        field_90;      // +0x90
    float        field_94;      // +0x94
    float        field_98;      // +0x98
    bool         field_9C;      // +0x9C
    bool         field_9D;      // +0x9D
    float        field_A0;      // +0xA0
    int          field_A4;      // +0xA4
    double       field_A8;      // +0xA8
    int          field_B0;      // +0xB0
    int          field_B4;      // +0xB4
    float        field_B8;      // +0xB8
    int          field_BC;      // +0xBC
    int          field_C0;      // +0xC0
    float        field_C4;      // +0xC4
    float        field_C8;      // +0xC8
    float        field_CC;      // +0xCC
    float        field_D0;      // +0xD0
    bool         field_D4;      // +0xD4
    uint32_t     animID;        // +0xD8
    int          field_DC;      // +0xDC
    int          field_E0;      // +0xE0
    int          field_E4;      // +0xE4
    int          field_E8;      // +0xE8
    int          field_EC;      // +0xEC

    void  Reset();              // 0xa00490
    char  Test();               // 0x9ff020
    void  Set670(int a, int b); // 0xa00670
};
class RefObj {
public:
    char pad[0x1000];
    void  Rel9ae1c0();
    void  Rel9a3630();
    void  Rel9c4cc0();
    float Ac2b0(void* p, RefObj* f0, float v, int a, int b, int c);
    void  Acac0(float v);
};
class anim_qb {
public:
    int          field_0;        // +0x00
    int          field_4;        // +0x04
    anim_query   queries[16];    // +0x08
    int          field_F08;      // +0xF08
    unsigned int field_F0C[16];  // +0xF0C
    int          field_F4C[16];  // +0xF4C
    int          field_F8C;
    int          field_F90;
    int          field_F94;
    int          field_F98;
    int          field_F9C;
    unsigned int field_FA0;
    unsigned int field_FA4;
    unsigned int field_FA8;
    bool         field_FAC;      // +0xFAC
    float        field_FB0;
    float        field_FB4;
    float        field_FB8;
    void*        p_anim_cid;     // +0xFBC
    int          field_FC0;
    float        field_FC4;
    float        field_FC8;
    bool         field_FCC;

    anim_qb();                                   // 0xa01c10
    ~anim_qb();                                  // 0xa01c70
    void UpdateQuery(uint32_t id, float delta);  // 0xa01cd0
    void Foo(int, int);                          // 0xa01f10
    void Update(float dt, bool b, int a, int c); // 0xa01f40
    bool Bar(int);                               // 0xa02440
    void Reset(int flag);                        // 0xa007d0
    void Commit();                               // 0xa00980
    void Remove(int index);                      // 0xa00f10
    void Ret(anim_query* q, int a);              // 0xa00f90
    void D50(int a, int b);                      // 0xa00d50
};
extern "C" void  __cdecl    qb_get2(anim_query** out, anim_qb* qb, int id);
class cAnimatingCreature {
public:
    char pad[0x1000];
    bool IsOrientStartAnim(uint32_t animID);
    bool IsOrientStopAnim(uint32_t animID);
};
// ---- items of slice s00a01810 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void  __cdecl    qb_get2(anim_query** out, anim_qb* qb, int id);

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void qb_set_query(anim_qb* qb, int index, int mode, bool idle);  // 0x00a01810 (stays in the slice: not this object's)

// ---- items of slice s00a02da0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_flt_01551a88;
extern float g_flt_01551a84;
// ---- items of slice s00a02da0 end

// ---- items of slice s00a03da0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct DebugShape
{
	char pad0[0x138];
	float m_offset[3];   // +0x138
};
struct DebugEntry   // 700 bytes
{
	DebugShape* m_shape;   // +0x00
	char pad04[0x0c];
	float m_pos[3];        // +0x10
	float m_qw;            // +0x1c
	float m_qx;            // +0x20
	float m_qy;            // +0x24
	float m_qz;            // +0x28
	char pad2c[700 - 0x2c];
};
struct DebugBody
{
	char pad00[0x18];
	float m_pos[3];        // +0x18
	char pad24[0x3c - 0x24];
	float m_qw;            // +0x3c
	float m_qx;            // +0x40
	float m_qy;            // +0x44
	float m_qz;            // +0x48
	char pad4c[0x70 - 0x4c];
	float m_scale;         // +0x70
	char pad74[0x2e4 - 0x74];
	DebugEntry* m_begin;   // +0x2e4
	DebugEntry* m_end;     // +0x2e8
};
struct DebugTarget
{
	char pad0[4];
	void* m_field4;
};
void SetDebugTransform_00a03da0(DebugTarget* target, const float* matrix3x3, const float* pos, float scale);
bool LockVertices_006ddcc0(int kind, int count, void** outPtr, void* aux);
void UnlockVertices_006ddd40(int kind, DebugTarget* target, int arg);
void BuildBoxVertices_00a02da0(void* out, const float* matrix, const float* pos, const float* negOffset,
                               const float* extents, uint32_t color);
static __forceinline void QuatToMatrix(float* m, float w, float x, float y, float z)
{
	m[0] = 1.0f - (y * y + x * x) * 2.0f;
	m[1] = (x * w - z * y) * 2.0f;
	m[2] = (z * x + y * w) * 2.0f;
	m[3] = (z * y + x * w) * 2.0f;
	m[4] = 1.0f - (y * y + w * w) * 2.0f;
	m[5] = (y * x - z * w) * 2.0f;
	m[6] = (y * w - z * x) * 2.0f;
	m[7] = (z * w + y * x) * 2.0f;
	m[8] = 1.0f - (x * x + w * w) * 2.0f;
}
// ---- items of slice s00a03da0 end

// ---- items of slice s00a06d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool g_cullByPlane;          // 0x01551a91
extern bool g_cullBySphere;         // 0x01551a90
extern const float kMinusBoxHalf;   // 0x01448bc8 (-0.15)
template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
struct Matrix3 { Matrix3() {} float m[9]; };
struct Color4f { float r, g, b, a; };
struct ColorARGB { uint8_t b, g, r, a; };
class Property {
public:
    Property(const uint32_t& value);            // 0x005bf350
    ~Property() { if (mnFlags & 4) Destruct(0); }
    void Destruct(int);                         // 0x0093db80 EA::Variant::Destruct
    int32_t* GetValueInt32();                   // 0x0041e990
    bool* GetValueBool();                       // 0x0041e920
    int32_t* GetValueInt32Alt();                // 0x0060d280 (type 9 or 0x10)
    bool* GetValueBoolAlt();                    // 0x004e42a0 (type 1 or 0x10)
    uint32_t mData[4];
    uint16_t mnFlags;                           // +0x10
    uint16_t mnType;                            // +0x12
};
class PropertyList {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual Property* GetProperty(uint32_t propertyID);   // +0x28
};
class cViewer {
public:
    bool Begin();                                // 0x007c4fd0
    void End();                                  // 0x007c3c10
    void GetCameraLocationInfo(Vector3* pos, int, int, int);  // 0x007c3d30
};
struct ViewerRef { cViewer* p; };
struct ModelResource {
    uint32_t pad0[0x324 / 4];
    float mColorR;          // +0x324
    float mColorG;          // +0x328
    float mColorB;          // +0x32c
    uint32_t pad330[(0x358 - 0x330) / 4];
    Vector3 mBoundsMin;     // +0x358
    Vector3 mBoundsSize;    // +0x364
};
struct Model {
    ModelResource* mpResource;      // +0x00
    uint32_t pad04[(0x18 - 0x04) / 4];
    Vector3 mPosition;              // +0x18
    uint32_t pad24[(0x3c - 0x24) / 4];
    Quaternion mOrientation;        // +0x3c
    uint32_t pad4c[(0x70 - 0x4c) / 4];
    float mScale;                   // +0x70
    uint32_t pad74[(0xe8 - 0x74) / 4];
    Vector3 mArrowBase;             // +0xe8
    Vector3 mArrowDir;              // +0xf4
    uint32_t pad100[(0x2c0 - 0x100) / 4];
    int mHasBody;                   // +0x2c0
};
struct ObjState { uint32_t pad0; uint32_t mFlags; };
struct DrawObject {
    uint32_t pad0[0x50 / 4];
    int mShapeAlt;          // +0x50
    int mShape;             // +0x54
    uint32_t pad58[(0x64 - 0x58) / 4];
    bool mbVisible;         // +0x64
    uint8_t pad65[3];
    uint32_t pad68[(0x74 - 0x68) / 4];
    float mColorR;          // +0x74
    float mColorG;          // +0x78
    float mColorB;          // +0x7c
    float mAlpha;           // +0x80
    uint32_t pad84;
    uint32_t mFlags;        // +0x88
    uint32_t pad8c[(0x17c - 0x8c) / 4];
    Model* mpModel;         // +0x17c
    ObjState* mpState;      // +0x180
};
struct DrawSettings {
    uint32_t pad0[0x50 / 4];
    PropertyList* mpProps;  // +0x50
    uint32_t pad54[(0x80 - 0x54) / 4];
    void* mpDrawContext;    // +0x80
};
typedef float (*RadiusCallback)(void* data, DrawObject* obj, int, int, int, int);
Matrix3 QuaternionToMatrix(const Quaternion& q);                       // 0x009a46a0
Matrix3 MatrixFromVectors(const Vector3& up, const Vector3& dir, int, int);  // 0x00a05890
Vector3 QuaternionVectorTransform(const Quaternion& q, const Vector3& v);    // 0x0099c1a0
float SmoothBlend(float a, float b, float t);                          // 0x009b01e0
float InvSqrt(float x);                                                // 0x009e5c00
void GetModelTransform(Model* m, Vector3* pos, Quaternion* q, int);    // 0x009cd580
void GetObjectColor(DrawObject* obj, Color4f* out);                    // 0x00a04590
void DrawBox(void* ctx, const Matrix3& rot, const Vector3& pos, float scale,
             const Vector3& lo, const Vector3& hi, ColorARGB color, int flags);   // 0x00a03e80
void DrawModelShape(void* ctx, Model* m, ColorARGB c0, ColorARGB c1, int flags);  // 0x00a03f50
extern const ColorARGB kMagenta;    // 0x01448ad4
extern const ColorARGB kGreen;      // 0x01448ad0
static inline bool StateBit(uint32_t flags, int n) { return (flags >> n) & 1; }
class cAnimDebugDraw {
public:
    void Draw(uint8_t pass, int colorMode, ViewerRef& viewer, int flags);

    uint32_t pad0[0x1c / 4];
    DrawSettings* mpSettings;               // +0x1c
    uint32_t pad20;
    DrawObject** mObjectsBegin;             // +0x24
    DrawObject** mObjectsEnd;               // +0x28
    uint32_t pad2c[(0x38 - 0x2c) / 4];
    bool mbCullingEnabled;                  // +0x38
    uint8_t pad39[3];
    RadiusCallback mpRadiusCallback;        // +0x3c
    void* mpRadiusCallbackData;             // +0x40
    uint32_t pad44[(0x3038 - 0x44) / 4];
    bool mbUseDrawModeProperty;             // +0x3038
};
// ---- items of slice s00a06d50 end

// ---- items of slice s00a099e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_00f473a0(unsigned size, const char* tag, int a, int b, const char* file, int line);
extern "C" void  FUN_00f47380(void* p);
extern "C" void* FUN_00a11310(void* first, void* last, void* dest);
extern "C" void* FUN_006e5760(void* dest, unsigned count, void* val);
extern "C" void  FUN_00898b80(void* a, void* b, void* c, void* d, void* e);
extern "C" void  FUN_00abced0(void* a, void* b, void* c);
extern "C" void  FUN_00a177f0(void* first, void* last, void* val);
extern "C" void  FUN_009216a0(void* node, void* where, void* header, int flag);
extern "C" void* FUN_00921580(void* node);
extern "C" void  FUN_00921880(void* node, void* header);
extern "C" void* FUN_00e5c780(void* tree, void* key);
extern "C" void  FUN_0068f950();
extern "C" void  FUN_00579a90();                       // eastl::basic_string<wchar_t>::RangeInitialize
extern "C" void* FUN_0067dcd0();                       // EA::ResourceMan::GetManager
extern "C" void  FUN_00a05830(int n, void* p);
extern "C" void  FUN_00a09560(void* out, void* a, void* b, void* c, void* d);
extern "C" void  FUN_009c67e0(void* a, void* b);
extern "C" void  FUN_009b3450();
extern "C" void  FUN_00a09420(void* a, void* b, void* c);
extern "C" void  FUN_009c26a0(void* p);
extern "C" void  FUN_00a05270(void* p);                // SP::cAnimatingCreature::Release
extern "C" void  FUN_009c4d10(void* p);
extern "C" int   FUN_009aa820(int p);
extern "C" int   FUN_009a37e0(int p);
extern "C" void  FUN_00a05730(void* out, void* p);
extern "C" int   FUN_009a3f50(int p, unsigned n);
extern "C" void  FUN_00a007d0(int a);
extern "C" void  FUN_00a01c70();
extern "C" void  FUN_009ac130(int p);
extern "C" int   FUN_0068f970();                       // SP::cJobManager::ContinueJob
extern "C" void  FUN_00692400(int a);
extern "C" int   FUN_00690120();                       // SP::cJob::GetStatus
extern "C" void  FUN_00a09890(int p);
extern "C" void  FUN_00a09850(int p);
extern "C" void  FUN_00a098d0(void* a, void* b, void* c, void* d);
extern "C" void  FUN_00a057f0(void* a, void* b);
extern "C" void  FUN_00ac97a0(void* a, void* b, void* c);
extern "C" void* FUN_009e0480(void* a, void* b);       // eastl vector<AnalysisInfo>::erase
typedef unsigned char  uint8;
typedef unsigned int   uint32;
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define EASTL_TAG "EASTL"
extern uint32 g_166c084;                               // DAT_0166c084
extern uint32 g_164dc58;                               // DAT_0164dc58
static inline void* vfn(void* o, int off) { return *(void**)(*(char**)o + off); }
typedef void     (__thiscall *vt_v)(void*);
typedef int      (__thiscall *vt_i)(void*);
typedef void     (__thiscall *vt_v_i)(void*, int);
typedef void*    (__thiscall *vt_p_i)(void*, int);
struct SL71
{
    void     v099e0(void* pos, unsigned count, void* val);
    void     v09cf0(void** out, void* where, unsigned* key, char flag);
    void*    v09e70(void* a2, void* a3);
    void     v09f90();
    void     v0a020();
    unsigned v0a0b0(void* a1, unsigned a2, unsigned a3);
    void     v0a360(void* a2, void* a3);
    void*    v0a520(void* a2);
    unsigned v0a600();
    void     v0a6d0(void* a2);
    void     v0a930();
    void     v0aa20(unsigned key);
    void     v0aaa0();
    void*    v0ab90(void* a2);
    void     v0ac10(unsigned n);
};
// ---- items of slice s00a099e0 end

// ---- items of slice s00a0aca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Hash {
uint32_t __cdecl FNV1_String8(const char* pString, uint32_t nInitialValue, int charCase);   // 0x00932e80
}
}
void* __cdecl operator_new(size_t, const char*, int, int, int, int);   // 0x00f473a0
void  __cdecl operator_delete__(void*);                                 // 0x00f47380
struct vector_3 {
    float x, y, z;
    vector_3() {}
    vector_3(const vector_3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct vector_4 {
    float x, y, z, w;
    vector_4() {}
    vector_4(const vector_4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};
struct ResourceKey { uint32_t instance, type, group; };
struct IResource {
    virtual int AddRef();
    virtual int Release();
};
struct ResourceObject {
    void*       vtbl;                   // +0x00
    uint32_t    refcount;               // +0x04
    ResourceKey key;                    // +0x08
};
struct AutoRefCount_s00a0_aca0 {                   // EA::AutoRefCount<IResource>
    IResource* mpObject;
    void** AsPPTypeParam();             // 0x00a16f40 (releases the held object, returns &mpObject)
};
struct creature_static_data;
struct creature_instance_data;
struct anim_creature;
struct StaticPtr {                      // AutoRefCount<creature_static_data> (inline Reset takes a reference)
    creature_static_data* mp;
    StaticPtr() : mp(0) {}
    void Reset(creature_static_data* const& p);
};
struct SlotRef {                        // AutoRefCount<creature_static_data> slot inside the cache
    SlotRef* assign(creature_static_data** p);              // 0x00a056f0
};
struct CacheNode { uint32_t pad[6]; creature_static_data* value; uint32_t pad2[2]; };   // value at +0x18
struct StaticDataCache {                // rbtree at world->cache + 0x18
    void     find(CacheNode** pResult, const uint64_t* key);   // 0x00a05730
    SlotRef* at(const uint64_t* key);                          // 0x00a0ab90 (operator[])
};
struct CacheHolder {
    uint32_t        pad_000[6];
    StaticDataCache cache;              // +0x18
    // +0x1c: header node, i.e. end()
};
struct effect {
    uint32_t pad_000[3];
    float    f0c, f10, f14, f18, f1c, f20, f24;   // +0x0c .. +0x24
    uint8_t  pad_028;
    uint8_t  active;                    // +0x29
    uint8_t  pad_02a[2];
    float    f2c;                       // +0x2c
    void Init(IResource* res, uint32_t a, uint32_t b);      // 0x009caa40 (ret 0xc)
};
struct effect_record {                  // 0x28 bytes, creature_static_data effect table
    uint32_t key0;                      // +0x00
    uint32_t a;                         // +0x04
    float    f08;                       // +0x08
    float    f0c, f10, f14, f18, f1c, f20, f24;   // +0x0c .. +0x24
};
struct creature_model_inst {            // "cmid" (0x3c bytes)
    bool InitFromResource(creature_instance_data* cid, void* world44, IResource* res, const ResourceKey* key, uint8_t b);   // 0x009c8050 (ret 0x14)
    bool InitFromBlocks(creature_instance_data* cid, void* world44, const ResourceKey* key, uint8_t b);                      // 0x009c8230 (ret 0x10)
    creature_model_inst* Construct();                                                                                         // 0x009c8200
    void Destruct();                                                                                                          // 0x00a0a020
};
struct creature_static_data {
    uint32_t pad_000[0x310 / 4];
    uint64_t cache_key;                 // +0x310
    uint32_t pad_318[(0x348 - 0x318) / 4];
    int      refcount;                  // +0x348
    uint32_t pad_34c[(0x398 - 0x34c) / 4];
    effect_record* effects_begin;       // +0x398
    effect_record* effects_end;         // +0x39c

    creature_static_data* Construct();  // 0x009c1f60
    int  AddRef();                      // 0x009b3450
    int  Release();                     // 0x009c26a0
};
inline void StaticPtr::Reset(creature_static_data* const& p) { if (p) p->AddRef(); mp = p; }
struct creature_instance_data {
    uint32_t pad_000;
    anim_creature* root;                // +0x004
    uint32_t pad_008[3];
    int      refcount;                  // +0x014
    uint32_t pad_018[(0x2c0 - 0x18) / 4];
    creature_model_inst* model;         // +0x2c0

    creature_instance_data* Construct();    // 0x009c56c0
    int  AddRef();                          // 0x00a17060
    void Release();                         // 0x009c4cc0
    effect* AddEffect(uint32_t id, int a, int b);   // 0x009cb300 (ret 0xc)
};
struct BakedAnimManager {
    void* PostFeedback(creature_static_data* csd, int arg);   // 0x009abd10 (ret 8)
};
extern BakedAnimManager* g_pBakedAnimManager;                // 0x0166c084
struct queued_blender {
    queued_blender* Construct();                                         // 0x00a01c10
    void Init(creature_instance_data* cid, BakedAnimManager* mgr);      // 0x00a00910 (ret 8)
};
struct anim_creature {                  // 0x19c bytes
    void*    vtbl;                      // +0x00
    uint32_t pad_004[(0x50 - 4) / 4];
    uint32_t userData;                  // +0x050
    uint32_t pad_054[(0x68 - 0x54) / 4];
    uint32_t slotMask;                  // +0x068
    int      f6c;                       // +0x06c
    int      f70;                       // +0x070
    uint32_t pad_074[(0x88 - 0x74) / 4];
    uint32_t flags;                     // +0x088
    uint32_t pad_08c[(0x17c - 0x8c) / 4];
    creature_instance_data* instance;   // +0x17c
    uint32_t pad_180;
    queued_blender* blender;            // +0x184
    uint32_t f188;                      // +0x188
    uint32_t f18c;                      // +0x18c
    void*    world;                     // +0x190
    uint32_t creatureCount;             // +0x194
    int      f198;                      // +0x198

    anim_creature* Construct(const vector_3* pos, const vector_4* rot);   // 0x00a05d60 (ret 8)
};
struct SimpleVector {                   // SP::SimpleVector<anim_creature*>
    anim_creature** mpBegin;
    anim_creature** mpEnd;
    anim_creature** mpCapacity;
    void DoInsertValue(anim_creature** pos, anim_creature* const* value);   // 0x00a80dd0 (ret 8)
};
bool   __cdecl ResolveResource(const ResourceKey* key, void** pResult);                       // 0x004bafc0
bool   __cdecl InitStaticDataFromResource(creature_static_data* csd, IResource* res);         // 0x009cbee0
bool   __cdecl InitStaticDataFromBlocksFile(creature_static_data* csd, const char* name);     // 0x009cd110
void   __cdecl InitInstance(creature_static_data* csd, creature_instance_data* cid, vector_3 pos,
                            vector_4 rot, void* p);                                           // 0x009c52a0
bool   __cdecl ResolveEffectResource(void* p4c, uint32_t key0, int a, int b, void** pResult); // 0x009fc050
void   __cdecl RegisterCreature(anim_creature* ac);                                           // 0x00a05c20
static inline uint32_t ExtractBits(uint32_t v, uint32_t mask)
{
    uint32_t result = 0, bit = 1;
    while (mask) {
        uint32_t rest = mask & (mask - 1);
        uint32_t low = rest ^ mask;
        result |= (-(int)((low & v) != 0)) & bit;
        bit <<= 1;
        v &= ~low;
        mask = rest;
        if (!v) break;
    }
    return result;
}
struct AnimWorld {
    uint32_t pad_000[7];
    CacheHolder* cacheHolder;           // +0x01c
    uint32_t pad_020;
    SimpleVector creatures;             // +0x024
    uint32_t pad_030[2];
    uint8_t  data38[8];                 // +0x038 (passed to InitInstance)
    uint32_t pad_040;
    void*    world44;                   // +0x044
    uint8_t  flag48;                    // +0x048
    uint8_t  pad_049[3];
    void*    p4c;                       // +0x04c
    uint8_t  pad_050[0x3039 - 0x50];
    uint8_t  flag3039;                  // +0x3039
    uint8_t  flag303a;                  // +0x303a

    anim_creature* CreateCreatureController(const ResourceKey* key, ResourceObject** pObj, const char* name,
                                            uint32_t userData, const vector_3* pos, const vector_4* rot,
                                            bool useCache);
};
// ---- items of slice s00a0aca0 end

// ---- items of slice s00a0c690 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);
extern const bool     kDefaultBoolValue;        // 015d115d
extern const int      kDefaultInt32Value;       // 015d1160
extern const uint32_t kDefaultUInt32Value;      // 015d1164
extern const float    kDefaultFloatValue;       // 015d1168
extern const float    kAnimDefaultFloatValue;   // 015d9c6c (this module's own copy)
extern const bool     kAnimDefaultBoolValue;    // 015d9c70
extern int      gAnimFlagB04;       // 01550b04
extern int      gAnimIntB6C;        // 01550b6c
extern float    gAnimFloatB74;      // 01550b74
extern float    gAnimFloatB78;      // 01550b78
extern uint32_t gAnimUIntB7C;       // 01550b7c
extern uint32_t gAnimUIntB80;       // 01550b80
#define VPAD(n) virtual void vpad##n()
struct Vector3_s00a0_c690 {
    float x, y, z;
    Vector3_s00a0_c690() {}
    Vector3_s00a0_c690(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00a0_c690& operator=(const Vector3_s00a0_c690& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Quaternion_s00a0_c690 {
    float x, y, z, w;
    Quaternion_s00a0_c690& operator=(const Quaternion_s00a0_c690& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
};
struct Property_s00a0_c690 {
    void*    mpData;      // +0x00 (external data, or the inline value itself)
    uint32_t pad04[3];
    uint16_t mnFlags;     // +0x10 (0x30 = external data)
    uint16_t mnType;      // +0x12

    void* GetValuePtr()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
    const bool* GetValueBool(const bool* def)
    {
        if (mnType == 1 || mnType == 0x10)
            return (const bool*)GetValuePtr();
        return def;
    }
    const int* GetValueInt32()
    {
        if (mnType == 9 || mnType == 0x10)
            return (const int*)GetValuePtr();
        return &kDefaultInt32Value;
    }
    const uint32_t* GetValueUInt32()
    {
        if (mnType == 10 || mnType == 0x10)
            return (const uint32_t*)GetValuePtr();
        return &kDefaultUInt32Value;
    }
    const float* GetValueFloat(const float* def)
    {
        if (mnType == 13 || mnType == 0x10)
            return (const float*)GetValuePtr();
        return def;
    }
};
struct cPropertyList {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    virtual Property_s00a0_c690* GetProperty(uint32_t id);                         // +0x28
};
struct cViewer_s00a0_c690 {
    uint32_t pad[0xc0 / 4];
    uint32_t mViewProjection[0x10];                                     // +0xc0
    void GetCameraLocationInfo(Vector3_s00a0_c690* pos, int, int, Vector3_s00a0_c690* dir);   // 007c3d30 0x007c3d30
    void ProjectToScreen(Vector3_s00a0_c690* out, const Vector3_s00a0_c690* in);              // 007c4180
};
struct cRenderManager {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11);
    virtual cViewer_s00a0_c690* GetViewer(int index);                              // +0x30
};
cRenderManager* RenderManager();                                        // 0067dd50
struct cApp {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19);
    VPAD(20); VPAD(21);
    virtual cViewer_s00a0_c690* GetViewer();                                       // +0x58
};
cApp* App();                                                            // 0067dd10
struct Frustum {
    uint32_t mData[0xf0 / 4];
    void Set(const uint32_t* viewProjection);                           // 006ffe00
    uint32_t Test(const Vector3_s00a0_c690* center, float radius);                 // 006ffbd0
};
struct creature_static_bounds {
    uint32_t pad[0x358 / 4];
    Vector3_s00a0_c690 mBoundsOrigin;                                              // +0x358
    Vector3_s00a0_c690 mBoundsSize;                                                // +0x364
    float   mBoundsRadius;                                              // +0x370
};
struct creature_mesh_instance_data {
    void SetStateInWorld(bool a, bool b, bool c);                       // 009c6440
};
struct creature_instance_data_s00a0_c690;
template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount& o)
    {
        T* const pNew = o.mpObject;
        T* const pOld = mpObject;
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            mpObject = pNew;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }
};
struct creature_instance_data_s00a0_c690 {
    creature_static_bounds* mpStatic;                                   // +0x00
    uint32_t pad04[2];
    uint8_t  mbReady;                                                   // +0x0c
    uint32_t mSkippedUpdates;                                           // +0x10
    uint32_t pad14;
    Vector3_s00a0_c690  mPosition;                                                 // +0x18
    uint32_t pad24[(0x3c - 0x24) / 4];
    Quaternion_s00a0_c690 mOrientation;                                            // +0x3c
    uint32_t pad4c[(0x6c - 0x4c) / 4];
    float    mScale;                                                    // +0x6c
    uint32_t pad70[(0xd8 - 0x70) / 4];
    float    mAngularSpeed;                                             // +0xd8
    Vector3_s00a0_c690  mVelocity;                                                 // +0xdc
    uint32_t pade8[(0x270 - 0xe8) / 4];
    uint8_t  mbFlag270;                                                 // +0x270
    uint8_t  pad271[3];
    int      mTargetMode;                                               // +0x274
    Vector3_s00a0_c690  mTargetPosition;                                           // +0x278
    Quaternion_s00a0_c690 mTargetOrientation;                                      // +0x284
    AutoRefCount<creature_instance_data_s00a0_c690> mTarget;                       // +0x294
    uint32_t mTargetContextMode;                                        // +0x298
    uint32_t mTargetContextValue;                                       // +0x29c
    uint32_t m2a0;                                                      // +0x2a0
    uint32_t m2a4;                                                      // +0x2a4
    uint32_t mRestIdle;                                                 // +0x2a8
    uint32_t mMoveIdle;                                                 // +0x2ac
    void*    mpDataEvents;                                              // +0x2b0
    uint32_t mDataEventStride;                                          // +0x2b4
    void*    mpTargetData;                                              // +0x2b8
    uint32_t mTargetDataStride;                                         // +0x2bc
    creature_mesh_instance_data* mpMesh;                                // +0x2c0
    Vector3_s00a0_c690  mColor;                                                    // +0x2c4
    uint8_t  pad2d0[6];
    uint8_t  mbFlag2d6;                                                 // +0x2d6
    uint32_t pad2d8[(0x2e4 - 0x2d8) / 4];
    uint8_t* mpAnimsBegin;                                              // +0x2e4 (700-byte elements)
    uint8_t* mpAnimsEnd;                                                // +0x2e8

    void AddRef();                                                      // 00a17060
    void Release();                                                     // 009c4cc0 0x009c4cc0
};
bool IsValidTargetPosition(const Vector3_s00a0_c690* pos);                         // 0059ab70
struct anim_anim_size { uint8_t data[700]; };
__forceinline bool HasValidTarget(creature_instance_data_s00a0_c690* inst)
{
    switch (inst->mTargetMode) {
    case 0:
    case 1:
        return IsValidTargetPosition(&inst->mTargetPosition);
    case 2:
        switch (inst->mTargetContextMode & 0x100003) {
        case 0:
        case 1:
            return inst->mTarget.mpObject && inst->mTarget.mpObject->mbReady;
        case 3:
            return inst->mTarget.mpObject && inst->mTarget.mpObject->mbReady &&
                   inst->mTargetContextValue <
                       (uint32_t)((anim_anim_size*)inst->mTarget.mpObject->mpAnimsEnd -
                                  (anim_anim_size*)inst->mTarget.mpObject->mpAnimsBegin);
        }
        break;
    }
    return false;
}
struct queued_blender_s00a0_c690 {
    void Update(float dt, bool lowLOD, bool noLOD, bool paused);       // 00a01f40
};
struct cModel;
struct cAnimatingCreature_s00a0_c690 {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19);
    VPAD(20);
    virtual void UpdateLOD(int);                                        // +0x54
    VPAD(22); VPAD(23); VPAD(24); VPAD(25); VPAD(26);
    virtual void PrepareUpdate();                                       // +0x6c

    Vector3_s00a0_c690  mPosition;                                                 // +0x04
    Quaternion_s00a0_c690 mOrientation;                                            // +0x10
    uint32_t pad20[(0x3c - 0x20) / 4];
    float    mScale;                                                    // +0x3c
    float    mAngularSpeed;                                             // +0x40
    Vector3_s00a0_c690  mVelocity;                                                 // +0x44
    int      mLODCount;                                                 // +0x50
    int      mLODForced;                                                // +0x54
    uint32_t pad58;
    bool     mbInFrustum;                                               // +0x5c
    uint8_t  pad5d[3];
    float    mScreenSize;                                               // +0x60
    bool     mbDoUpdate;                                                // +0x64
    uint8_t  pad65[3];
    uint32_t pad68[(0x74 - 0x68) / 4];
    Vector3_s00a0_c690  mColor;                                                    // +0x74
    uint32_t pad80;
    bool     mbHasColor;                                                // +0x84
    uint8_t  pad85[3];
    uint32_t pad88;
    uint32_t mDataEvents[(0x14c - 0x8c) / 4];                           // +0x8c
    uint32_t mTargetData[1];                                            // +0x14c
    uint8_t  mbFlag150;                                                 // +0x150
    uint8_t  mbFlag151;                                                 // +0x151
    uint8_t  pad152[2];
    int      mTargetModeRequest;                                        // +0x154
    int      mTargetContextModeRequest;                                 // +0x158
    cAnimatingCreature_s00a0_c690* mpTargetCreature;                               // +0x15c
    uint32_t mTargetContextValue;                                       // +0x160
    Vector3_s00a0_c690  mTargetPosition;                                           // +0x164
    uint32_t mRestIdle;                                                 // +0x170
    uint32_t mMoveIdle;                                                 // +0x174
    uint32_t pad178;
    AutoRefCount<creature_instance_data_s00a0_c690> mpInstance;                    // +0x17c
    cModel*  mpModel;                                                   // +0x180
    queued_blender_s00a0_c690* mpBlender;                                          // +0x184
    uint32_t pad188[(0x194 - 0x188) / 4];
    uint32_t mIndex;                                                    // +0x194

    void SetRestIdleAnimHandle();                                       // 00a02c40 0x00a02c40
};
struct IModelWorld {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19);
    VPAD(20); VPAD(21); VPAD(22); VPAD(23); VPAD(24); VPAD(25); VPAD(26); VPAD(27); VPAD(28); VPAD(29);
    VPAD(30); VPAD(31); VPAD(32); VPAD(33); VPAD(34); VPAD(35); VPAD(36); VPAD(37); VPAD(38); VPAD(39);
    VPAD(40);
    virtual void SetModelGroup(cModel* model, uint32_t group, int index);   // +0xa4
    virtual uint32_t GetModelGroup(cModel* model, int index);               // +0xa8
};
struct cSPCreatureAnimManager {
    uint32_t pad[0x50 / 4];
    cPropertyList* mpProperties;                                        // +0x50
    uint32_t pad54[(0x84 - 0x54) / 4];
    uint32_t mHiddenGroup;                                              // +0x84
};
struct ICoreAllocator;
ICoreAllocator* GetDefaultAllocator();                                  // 00921240
struct CreatureSizeCompare {
    float mThreshold;
    CreatureSizeCompare(float t) : mThreshold(t) {}
};
void StableSortCreatures(cAnimatingCreature_s00a0_c690** first, cAnimatingCreature_s00a0_c690** last,
                         ICoreAllocator& allocator, CreatureSizeCompare compare);   // 00a0a4b0
template <class Compare>
inline void stable_sort(cAnimatingCreature_s00a0_c690** first, cAnimatingCreature_s00a0_c690** last, Compare compare)
{
    StableSortCreatures(first, last, *GetDefaultAllocator(), compare);
}
struct CreatureVector {     // eastl::vector<cAnimatingCreature*, sp_vector_allocator>
    typedef cAnimatingCreature_s00a0_c690* value_type;
    cAnimatingCreature_s00a0_c690** mpBegin;
    cAnimatingCreature_s00a0_c690** mpEnd;
    cAnimatingCreature_s00a0_c690** mpCapacity;
    uint32_t mAllocator;

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void DoInsertValues(cAnimatingCreature_s00a0_c690** position, uint32_t n, cAnimatingCreature_s00a0_c690* const& value);  // 00999dd0
    void erase(cAnimatingCreature_s00a0_c690** first, cAnimatingCreature_s00a0_c690** last)
    {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
    }
    void resize(uint32_t n)
    {
        if (n > (uint32_t)(mpEnd - mpBegin))
            DoInsertValues(mpEnd, n - (uint32_t)(mpEnd - mpBegin), value_type());
        else
            erase(mpBegin + n, mpEnd);
    }
};
class cSPCreatureAnimWorld {
public:
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15);
    virtual void SetCreatureLOD(cAnimatingCreature_s00a0_c690* creature, int lod, int flags);     // +0x40
    VPAD(17);
    virtual void SetMaxCreatureByLOD(int lod, int count);                   // +0x48
    VPAD(19); VPAD(20);
    virtual bool IsPaused();                                                // +0x54

    void Update(float dt, cViewer_s00a0_c690* viewer);

    uint32_t pad04[(0x1c - 4) / 4];
    cSPCreatureAnimManager* mpManager;                                  // +0x1c
    uint32_t pad20;
    CreatureVector mCreatures;                                          // +0x24
    uint32_t pad34[(0x44 - 0x34) / 4];
    IModelWorld* mpModelWorld;                                          // +0x44
    uint32_t pad48[(0x5c - 0x48) / 4];
    int mCurrentCreatureByLOD[3];                                       // +0x5c
};
// ---- items of slice s00a0c690 end

// ---- items of slice s00a0e4c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyString16[];                      // 0x01667bac
typedef unsigned int uint;
struct IFile {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual uint Read(void* buf, uint nBytes);        // +0x30
};
extern int  __cdecl ReadInt32(IFile* f, void* dst, int count, int endian);   // 0x0093a780
extern bool __cdecl ReadBool(IFile* f, void* dst);                           // 0x0093ac80
struct string16 {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; int mAllocator;
    string16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    ~string16() {
        if (((int)((char*)mpCapacity - (char*)mpBegin) & -2) > 2 && mpBegin)
            operator_delete__(mpBegin);
    }
    uint size() const { return (uint)(mpEnd - mpBegin); }
    void assign(const wchar_t* b, const wchar_t* e);      // 0x00423650
    void append(uint n, wchar_t c);                       // 0x0042d2e0
    void resizeOut(uint n);                               // 0x00429520
    string16& operator=(const string16& x) { if (&x != this) assign(x.mpBegin, x.mpEnd); return *this; }
    void erase(wchar_t* first, wchar_t* last) {
        if (first != last) {
            memmove(first, last, (uint)((mpEnd - last) + 1) * sizeof(wchar_t));
            mpEnd -= (last - first);
        }
    }
    void resize(uint n) {
        const uint s = size();
        if (n < s) erase(mpBegin + n, mpEnd);
        else if (n > s) append(n - s, 0);
    }
};
struct Item {                 // 0x1c
    float w0, w4;             // defaults 1.0f, -1.0f
    int   w8;
    string16 name;            // +0x0c
};
struct SpAlloc { int mData[2]; };
struct Sub;
struct ItemVec {              // eastl::vector<Item, sp_vector_allocator> (0x14)
    Item* mpBegin; Item* mpEnd; Item* mpCapacity; SpAlloc mAllocator;
    void resize(uint n);                                  // 0x00a0d660
};
struct Sub {                  // 0x18
    ItemVec items;            // +0x00
    int i14;                  // +0x14
};
struct SubVec {               // eastl::vector<Sub, sp_vector_allocator> (0x14)
    Sub* mpBegin; Sub* mpEnd; Sub* mpCapacity; SpAlloc mAllocator;
    void resize(uint n);                                  // 0x00a0e0b0
    void DestroyRange(Sub* first, Sub* last);             // 0x00a0aca0 (thiscall, ecx unused)
    void assign(const SubVec& o);                         // 0x00a0dd90
    ~SubVec() {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};
struct Entry {                // 0x40
    uint     key;             // +0x00
    string16 name;            // +0x04
    float    f14;             // +0x14
    float    f18;             // +0x18 (reset value -1.0f)
    bool     b1c, b1d, b1e;   // +0x1c
    int      i20, i24, i28;   // +0x20 (i28 reset value 4)
    SubVec   subs;            // +0x2c
    void Reset();                                         // 0x00a0e250
    Entry() { subs.mpBegin = 0; subs.mpEnd = 0; subs.mpCapacity = 0; Reset(); }
};
struct RBNode { RBNode* right; RBNode* left; RBNode* parent; char color; };
struct EntryNode : RBNode { Entry value; };               // value at +0x10
struct EntryMap {
    int pad0;
    RBNode anchor;            // +0x04
    uint size;
    Entry* GetOrInsert(const uint* key);                  // 0x00a0e530 (thiscall, returns &node->value)
};
extern EntryMap gEntryMap;                                // 0x01551a68
// ---- items of slice s00a0e4c0 end

// ---- items of slice s00a0f350 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
void* __cdecl operator new(size_t, const char*, int, int, int, int);   // 0xf473a0
struct AnimMgr;
struct IServer {                 // EA::Messaging::Server
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8();
    virtual void AddHandler(void* handler, u32 msgId);          // +0x24
};
struct IMaterialMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9();
    virtual void* GetMaterial(u32 id);                           // +0x28
};
struct IRefObj {
    virtual void v0();
    virtual void Release();                                      // +4
};
struct IPropData {               // property value
    u32* mData;                  // +0
    u8   pad[0xc];
    u8   mFlags;                 // +0x10
    u8   pad2;
    u16  mType;                  // +0x12
};
struct IPropList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9();
    virtual IPropData* GetProperty(u32 id);                      // +0x28
};
struct IPropMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void GetPropertyList(u32 id, int, IRefObj** out);    // +0x2c
};
struct ICheatMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void AddCommand(const char* name, void* cmd, int);   // +0x18
};
struct IResMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void* GetResource(u32 id, int, int);                 // +0x20
};
struct PtrVec {
    u32** mBegin;
    u32** mEnd;
    u32** mCap;
    void DoInsertValue(u32** pos, u32* const& v);   // 0x4558a0
    void push_back(u32* const& v) {
        if (mEnd < mCap) { u32** p = mEnd++; if (p) *p = v; }
        else DoInsertValue(mEnd, v);
    }
};
struct AnimRefHolder {           // object at [mgr+0x84], vector at +8
    u8 pad[8];
    PtrVec mVec;
};
struct RefA {
    RefA();                                            // 0x77d1d0
    u8 pad[0x1c];
};
struct RefB {
    RefB();                                            // 0x40d010
    void InsertResource(int, void*);                   // 0x77cb10
    u8 pad[0x70];
};
struct RefC {
    RefC();                                            // 0x432cf0
    u8 pad[0xc];
    u8 mKind; u8 pad1[3];
    float mA, mB, mC, mD;
};
struct CmdBase {
    CmdBase();                                         // 0x83c800
    virtual void Run() = 0;
    u8 pad[0xc];
};
struct BlocksModeCmd : CmdBase {
    AnimMgr* mMgr;
    virtual void Run() {}
};
struct AutoHandlerRec {
    IServer* mServer; void* mHandler; const u32* mIds; u32 mCount; u32 mFlag;
};
extern u32 g_animMsgIds[2];            // 0x155182c
extern u32 g_defaultPropVal[];         // 0x15d1164
extern AnimMgr* g_animMgr;             // 0x166cc08
struct SomeObj {
    bool Prep();                                       // 0x9a9920
};
struct SomeObj2 {
    void Fn(void*, int);                               // 0x9ab540
};
extern SomeObj g_obj_166c058;
extern SomeObj2* g_obj_166c084;
IMaterialMgr* GetMaterialManager();       // 0x67dd70
IResMgr*      GetResMgr();                // 0x67dd60
IPropMgr*     GetPropertyManager();       // 0x67de30
IServer*      GetMessageServer();         // 0x67dcc0
ICheatMgr*    GetCheatManager();          // 0x67de20
void          FUN_00a059d0(AnimMgr*);
void*         FUN_009a37a0(void*);
void          FUN_009a4020(void*, int);
struct RefSlot {
    void Assign(void* p);                              // 0x41d8b0
};
struct AnimMgr {
    u8     pad0[0x4c];
    IPropList* mPropertyList;    // +0x50
    AutoHandlerRec mAuto;        // +0x54
    u8     pad1[0x80 - 0x68];
    void*  mMaterial;            // +0x80? see Init
    AnimRefHolder* mHolder;      // +0x84

    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual void SetAppMode(u32 mode);                 // +0x3c

    void ReadAnimList(int);                            // 0xa0f080
    bool Init(bool flag);
};
struct Msg { u8 pad[8]; u32 mSel; u8 pad2[0xc]; void* mData; };
struct AnimHandler {
    u8 pad[0x78]; u32 mAppMode;
    void Do08ba0();                                    // 0xa08ba0
    bool HandleMessage(u32 id, Msg* m);
};
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
// ---- items of slice s00a0f350 end

// @ 0x00a01b50
bool qb_enable(anim_qb* qb, int animID)
{
    if (animID != 0) {
        anim_query* found[2];
        qb_get2(found, qb, animID);
        if (found[1] != 0) {
            anim_query* p = found[1];
            qb_set_query(qb, (int)(((char*)p - (char*)qb) - 8) / 0xf0, p->mode, p->idle);
            found[0]->field_7C = true;
            p->field_7C = true;
            return true;
        }
        anim_query* p = found[0];
        qb_set_query(qb, (int)(((char*)p - (char*)qb) - 8) / 0xf0, p->mode, p->idle);
        p->field_7C = true;
        return true;
    }
    return false;
}

// @ 0x00a02710
bool cAnimatingCreature::IsOrientStartAnim(uint32_t animID) // @ 0xa02710
{
    if (animID == 0x4866d8e || animID == 0x452b634 || animID == 0x5cb2176)
        return true;
    return false;
}

// @ 0x00a02740
bool cAnimatingCreature::IsOrientStopAnim(uint32_t animID) // @ 0xa02740
{
    if (animID == 0x4866db9 || animID == 0x4866dc3 || animID == 0x4866dcb || animID == 0x4866dd4 ||
        animID == 0x5cb21ae || animID == 0x5cb21af || animID == 0x5cb21b0 || animID == 0x452b651 ||
        animID == 0x4482911 || animID == 0x4482918 || animID == 0x448291f)
        return true;
    return false;
}

// @ 0x00a02da0
void BuildBoxVertices_00a02da0(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5, float param_6)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  float fVar47;
  float fVar48;
  
  fVar1 = *param_2;
  fVar2 = param_2[3];
  fVar3 = param_2[6];
  fVar4 = param_2[1];
  fVar5 = param_2[4];
  fVar6 = param_2[7];
  fVar15 = -fVar1;
  fVar16 = -fVar2;
  fVar17 = -fVar3;
  fVar18 = -fVar4;
  fVar19 = -fVar5;
  fVar20 = -fVar6;
  fVar7 = param_2[2];
  fVar8 = param_2[5];
  fVar9 = param_2[8];
  fVar21 = -fVar7;
  fVar22 = -fVar8;
  fVar23 = -fVar9;
  fVar10 = *param_4;
  fVar11 = param_4[1];
  fVar46 = param_4[2];
  fVar47 = *param_3 + fVar46 * fVar7;
  fVar13 = fVar8 * fVar46 + param_3[1];
  fVar14 = fVar9 * fVar46 + param_3[2];
  fVar46 = *param_5;
  fVar12 = param_5[1];
  fVar44 = param_5[2];
  fVar24 = *param_3 + fVar44 * fVar7;
  fVar26 = fVar8 * fVar44 + param_3[1];
  fVar27 = fVar11 * fVar4 + fVar10 * fVar1;
  fVar25 = fVar9 * fVar44 + param_3[2];
  fVar28 = fVar5 * fVar11 + fVar2 * fVar10;
  fVar29 = fVar27 + fVar47;
  fVar30 = fVar28 + fVar13;
  fVar31 = fVar6 * fVar11 + fVar3 * fVar10;
  fVar48 = fVar14 + fVar31;
  fVar27 = fVar27 + fVar24;
  fVar28 = fVar28 + fVar26;
  fVar31 = fVar25 + fVar31;
  fVar32 = fVar12 * fVar4 + fVar10 * fVar1;
  fVar33 = fVar5 * fVar12 + fVar2 * fVar10;
  fVar34 = fVar32 + fVar47;
  fVar35 = fVar33 + fVar13;
  fVar36 = fVar6 * fVar12 + fVar3 * fVar10;
  fVar37 = fVar36 + fVar14;
  fVar32 = fVar32 + fVar24;
  fVar33 = fVar33 + fVar26;
  fVar36 = fVar25 + fVar36;
  fVar38 = fVar46 * fVar1 + fVar11 * fVar4;
  fVar39 = fVar2 * fVar46 + fVar5 * fVar11;
  fVar40 = fVar38 + fVar47;
  fVar41 = fVar39 + fVar13;
  fVar42 = fVar3 * fVar46 + fVar6 * fVar11;
  fVar43 = fVar42 + fVar14;
  fVar38 = fVar38 + fVar24;
  fVar39 = fVar39 + fVar26;
  fVar42 = fVar25 + fVar42;
  fVar44 = fVar12 * fVar4 + fVar46 * fVar1;
  fVar45 = fVar5 * fVar12 + fVar2 * fVar46;
  fVar47 = fVar44 + fVar47;
  fVar13 = fVar45 + fVar13;
  fVar46 = fVar6 * fVar12 + fVar3 * fVar46;
  fVar14 = fVar46 + fVar14;
  fVar44 = fVar44 + fVar24;
  *param_1 = fVar29;
  fVar45 = fVar45 + fVar26;
  param_1[1] = fVar30;
  fVar46 = fVar46 + fVar25;
  param_1[2] = fVar48;
  param_1[4] = fVar16;
  param_1[5] = fVar17;
  fVar11 = g_flt_01551a88;
  param_1[3] = fVar15;
  fVar10 = g_flt_01551a84;
  param_1[6] = param_6;
  param_1[7] = fVar11;
  param_1[8] = fVar10;
  param_1[9] = fVar27;
  param_1[10] = fVar28;
  param_1[0xb] = fVar31;
  param_1[0xc] = fVar15;
  param_1[0xd] = fVar16;
  param_1[0xe] = fVar17;
  param_1[0xf] = param_6;
  param_1[0x10] = 0.0f;
  param_1[0x11] = fVar10;
  param_1[0x12] = fVar32;
  param_1[0x13] = fVar33;
  param_1[0x14] = fVar36;
  param_1[0x15] = fVar15;
  param_1[0x16] = fVar16;
  param_1[0x17] = fVar17;
  param_1[0x18] = param_6;
  param_1[0x19] = 0.0f;
  param_1[0x1a] = 0.0f;
  param_1[0x1b] = fVar34;
  param_1[0x1c] = fVar35;
  param_1[0x1d] = fVar37;
  param_1[0x1e] = fVar15;
  param_1[0x1f] = fVar16;
  param_1[0x20] = fVar17;
  param_1[0x22] = fVar11;
  param_1[0x21] = param_6;
  param_1[0x23] = 0.0f;
  param_1[0x24] = fVar29;
  param_1[0x25] = fVar30;
  param_1[0x26] = fVar48;
  param_1[0x27] = fVar18;
  param_1[0x28] = fVar19;
  param_1[0x29] = fVar20;
  param_1[0x2a] = param_6;
  param_1[0x2b] = fVar11;
  param_1[0x2c] = fVar10;
  param_1[0x2d] = fVar40;
  param_1[0x2e] = fVar41;
  param_1[0x2f] = fVar43;
  param_1[0x30] = fVar18;
  param_1[0x31] = fVar19;
  param_1[0x32] = fVar20;
  param_1[0x33] = param_6;
  param_1[0x34] = 0.0f;
  param_1[0x35] = fVar10;
  param_1[0x36] = fVar38;
  param_1[0x37] = fVar39;
  param_1[0x38] = fVar42;
  param_1[0x39] = fVar18;
  param_1[0x3a] = fVar19;
  param_1[0x3b] = fVar20;
  param_1[0x3c] = param_6;
  param_1[0x3d] = 0.0f;
  param_1[0x3e] = 0.0f;
  param_1[0x3f] = fVar27;
  param_1[0x40] = fVar28;
  param_1[0x41] = fVar31;
  param_1[0x42] = fVar18;
  param_1[0x43] = fVar19;
  param_1[0x44] = fVar20;
  param_1[0x46] = fVar11;
  param_1[0x45] = param_6;
  param_1[0x47] = 0.0f;
  param_1[0x48] = fVar29;
  param_1[0x49] = fVar30;
  param_1[0x4a] = fVar48;
  param_1[0x4b] = fVar21;
  param_1[0x4c] = fVar22;
  param_1[0x4d] = fVar23;
  param_1[0x4e] = param_6;
  param_1[0x4f] = fVar11;
  param_1[0x50] = fVar10;
  param_1[0x51] = fVar34;
  param_1[0x52] = fVar35;
  param_1[0x53] = fVar37;
  param_1[0x54] = fVar21;
  param_1[0x55] = fVar22;
  param_1[0x56] = fVar23;
  param_1[0x57] = param_6;
  param_1[0x58] = 0.0f;
  param_1[0x59] = fVar10;
  param_1[0x5a] = fVar47;
  param_1[0x5b] = fVar13;
  param_1[0x5c] = fVar14;
  param_1[0x5d] = fVar21;
  param_1[0x5e] = fVar22;
  param_1[0x5f] = fVar23;
  param_1[0x60] = param_6;
  param_1[0x61] = 0.0f;
  param_1[0x62] = 0.0f;
  param_1[99] = fVar40;
  param_1[100] = fVar41;
  param_1[0x65] = fVar43;
  param_1[0x66] = fVar21;
  param_1[0x67] = fVar22;
  param_1[0x68] = fVar23;
  param_1[0x6a] = fVar11;
  param_1[0x69] = param_6;
  param_1[0x6b] = 0.0f;
  param_1[0x6c] = fVar44;
  param_1[0x6d] = fVar45;
  param_1[0x6e] = fVar46;
  param_1[0x6f] = fVar1;
  param_1[0x70] = fVar2;
  param_1[0x71] = fVar3;
  param_1[0x73] = fVar11;
  param_1[0x72] = param_6;
  param_1[0x74] = fVar10;
  param_1[0x75] = fVar38;
  param_1[0x76] = fVar39;
  param_1[0x77] = fVar42;
  param_1[0x78] = fVar1;
  param_1[0x7a] = fVar3;
  param_1[0x79] = fVar2;
  param_1[0x7b] = param_6;
  param_1[0x7c] = 0.0f;
  param_1[0x7d] = fVar10;
  param_1[0x7e] = fVar40;
  param_1[0x7f] = fVar41;
  param_1[0x80] = fVar43;
  param_1[0x81] = fVar1;
  param_1[0x83] = fVar3;
  param_1[0x82] = fVar2;
  param_1[0x84] = param_6;
  param_1[0x85] = 0.0f;
  param_1[0x86] = 0.0f;
  param_1[0x87] = fVar47;
  param_1[0x88] = fVar13;
  param_1[0x89] = fVar14;
  param_1[0x8a] = fVar1;
  param_1[0x8c] = fVar3;
  param_1[0x8b] = fVar2;
  param_1[0x8d] = param_6;
  param_1[0x8e] = fVar11;
  param_1[0x8f] = 0.0f;
  param_1[0x90] = fVar44;
  param_1[0x91] = fVar45;
  param_1[0x92] = fVar46;
  param_1[0x93] = fVar4;
  param_1[0x94] = fVar5;
  param_1[0x95] = fVar6;
  param_1[0x97] = fVar11;
  param_1[0x96] = param_6;
  param_1[0x98] = fVar10;
  param_1[0x99] = fVar47;
  param_1[0x9a] = fVar13;
  param_1[0x9b] = fVar14;
  param_1[0x9c] = fVar4;
  param_1[0x9d] = fVar5;
  param_1[0x9e] = fVar6;
  param_1[0xa0] = 0.0f;
  param_1[0x9f] = param_6;
  param_1[0xa1] = fVar10;
  param_1[0xa2] = fVar34;
  param_1[0xa3] = fVar35;
  param_1[0xa4] = fVar37;
  param_1[0xa6] = fVar5;
  param_1[0xa5] = fVar4;
  param_1[0xa7] = fVar6;
  param_1[0xa8] = param_6;
  param_1[0xa9] = 0.0f;
  param_1[0xaa] = 0.0f;
  param_1[0xac] = fVar33;
  param_1[0xad] = fVar36;
  param_1[0xab] = fVar32;
  param_1[0xaf] = fVar5;
  param_1[0xae] = fVar4;
  param_1[0xb0] = fVar6;
  param_1[0xb1] = param_6;
  param_1[0xb2] = fVar11;
  param_1[0xb3] = 0.0f;
  param_1[0xb4] = fVar44;
  param_1[0xb5] = fVar45;
  param_1[0xb6] = fVar46;
  param_1[0xb7] = fVar7;
  param_1[0xb8] = fVar8;
  param_1[0xb9] = fVar9;
  param_1[0xba] = param_6;
  param_1[0xbb] = fVar11;
  param_1[0xbc] = fVar10;
  param_1[0xbe] = fVar33;
  param_1[0xbd] = fVar32;
  param_1[0xbf] = fVar36;
  param_1[0xc0] = fVar7;
  param_1[0xc1] = fVar8;
  param_1[0xc2] = fVar9;
  param_1[0xc4] = 0.0f;
  param_1[0xc5] = fVar10;
  param_1[0xc3] = param_6;
  param_1[0xc6] = fVar27;
  param_1[199] = fVar28;
  param_1[200] = fVar31;
  param_1[0xc9] = fVar7;
  param_1[0xca] = fVar8;
  param_1[0xcb] = fVar9;
  param_1[0xcd] = 0.0f;
  param_1[0xcc] = param_6;
  param_1[0xce] = 0.0f;
  param_1[0xcf] = fVar38;
  param_1[0xd0] = fVar39;
  param_1[0xd1] = fVar42;
  param_1[0xd2] = fVar7;
  param_1[0xd3] = fVar8;
  param_1[0xd4] = fVar9;
  param_1[0xd5] = param_6;
  param_1[0xd6] = fVar11;
  param_1[0xd7] = 0.0f;
  return;
}

// @ 0x00a03f50
void DrawBodyBoxes_00a03f50(DebugTarget* target, DebugBody* body, uint32_t color3, uint32_t color4, int arg5)
{
	float m[9];
	QuatToMatrix(m, body->m_qw, body->m_qx, body->m_qy, body->m_qz);
	SetDebugTransform_00a03da0(target, m, body->m_pos, body->m_scale);

	float invScale = 1.0f / body->m_scale;
	unsigned count = body->m_end - body->m_begin;
	void* verts;
	char aux[4];

	if (!LockVertices_006ddcc0(4, count * 0x18, &verts, aux))
	{
		for (unsigned i = 0; i < count; i++)
		{
			DebugEntry* e = body->m_begin + i;
			if (LockVertices_006ddcc0(4, 0x18, &verts, aux))
			{
				const uint32_t* color = &color4;
				if (i != 0)
					color = &color3;
				DebugShape* shape = e->m_shape;
				float negOffset[3];
				negOffset[0] = -shape->m_offset[0];
				negOffset[1] = -shape->m_offset[1];
				negOffset[2] = -shape->m_offset[2];
				float pos[3];
				pos[0] = e->m_pos[0] * invScale;
				pos[1] = e->m_pos[1] * invScale;
				pos[2] = e->m_pos[2] * invScale;
				QuatToMatrix(m, e->m_qw, e->m_qx, e->m_qy, e->m_qz);
				BuildBoxVertices_00a02da0(verts, m, pos, negOffset, shape->m_offset, *color);
				UnlockVertices_006ddd40(3, target, arg5);
			}
		}
		return;
	}

	char* out = (char*)verts;
	for (unsigned i = 0; i < count; i++)
	{
		DebugEntry* e = body->m_begin + i;
		const uint32_t* color = &color4;
		if (i != 0)
			color = &color3;
		DebugShape* shape = e->m_shape;
		float negOffset[3];
		negOffset[0] = -shape->m_offset[0];
		negOffset[1] = -shape->m_offset[1];
		negOffset[2] = -shape->m_offset[2];
		float pos[3];
		pos[0] = e->m_pos[0] * invScale;
		pos[1] = e->m_pos[1] * invScale;
		pos[2] = e->m_pos[2] * invScale;
		QuatToMatrix(m, e->m_qw, e->m_qx, e->m_qy, e->m_qz);
		BuildBoxVertices_00a02da0(out, m, pos, negOffset, shape->m_offset, *color);
		out += 0x360;
	}
	UnlockVertices_006ddd40(3, target, arg5);
}

// @ 0x00a06d50
void cAnimDebugDraw::Draw(uint8_t pass, int colorMode, ViewerRef& viewer, int flags)
{
    if (viewer.p && viewer.p->Begin()) {
        if (mpSettings && mpSettings->mpDrawContext && mpSettings->mpProps) {
            bool useObjectColor = *mpSettings->mpProps->GetProperty(0xe0e98b25)->GetValueBoolAlt();
            int drawMode = *(mbUseDrawModeProperty
                                 ? mpSettings->mpProps->GetProperty(0xc2dafabb)
                                 : &Property(0u))->GetValueInt32Alt();
            int axesMode = *mpSettings->mpProps->GetProperty(0x567ad0f2)->GetValueInt32();
            int boxMode = *mpSettings->mpProps->GetProperty(0xcaea3820)->GetValueInt32();
            bool checkState = *mpSettings->mpProps->GetProperty(0x3d781d85)->GetValueBool();
            mpSettings->mpProps->GetProperty(0x32710aa4);
            void* ctx = mpSettings->mpDrawContext;

            bool cull = false;
            if (mbCullingEnabled && pass == 5) {
                if (*mpSettings->mpProps->GetProperty(0xe536de74)->GetValueBool())
                    cull = true;
            }
            bool needSetup = cull;
            Vector3 camDir;
            camDir.x = 0.0f;
            camDir.y = 0.0f;
            camDir.z = 0.0f;
            float planeDist;
            float radius;

            for (int i = (int)(mObjectsEnd - mObjectsBegin) - 1; i >= 0; --i) {
                DrawObject* obj = mObjectsBegin[i];
                if (!obj)
                    continue;
                Model* model = obj->mpModel;
                if (!model || !obj->mbVisible)
                    continue;

                switch (pass) {
                case 1:
                    if (obj->mAlpha < 1.0f)
                        continue;
                    break;
                case 2:
                    if (obj->mAlpha >= 1.0f)
                        continue;
                    break;
                }

                bool flagged = StateBit(obj->mFlags, 1);
                if (model->mHasBody != 0) {
                    if (checkState) {
                        ObjState* st = obj->mpState;
                        flagged |= !(st && StateBit(st->mFlags, 14) && !StateBit(st->mFlags, 18));
                    }
                } else
                    flagged = true;

                if (drawMode == 1 || (drawMode != -1 && flagged)) {
                    float fade = 1.0f;
                    if (needSetup) {
                        needSetup = false;
                        RadiusCallback cb = mpRadiusCallback;
                        if (cb) {
                            radius = cb(mpRadiusCallbackData, obj, 0, 0, 0, 1);
                            Vector3 camPos;
                            viewer.p->GetCameraLocationInfo(&camPos, 0, 0, 0);
                            float dist = sqrtf(camPos.x * camPos.x + camPos.y * camPos.y + camPos.z * camPos.z);
                            float inv = 1.0f / (dist + 1e-8f);
                            camDir.x = -camPos.x * inv;
                            camDir.y = -camPos.y * inv;
                            camDir.z = -camPos.z * inv;
                            float d2 = dist * dist - radius * radius;
                            if (d2 > 0.0f) {
                                planeDist = d2 * inv - dist;
                                goto cullTest;
                            }
                        }
                        cull = false;
                        goto colors;
                    }
                cullTest:
                    if (cull) {
                        if (g_cullByPlane) {
                            ModelResource* res = model->mpResource;
                            float s = model->mScale;
                            float hs = s * 0.5f;
                            Vector3 center;
                            center.x = res->mBoundsMin.x * s + res->mBoundsSize.x * hs;
                            center.y = res->mBoundsMin.y * s + res->mBoundsSize.y * hs;
                            center.z = res->mBoundsMin.z * s + res->mBoundsSize.z * hs;
                            Vector3 r = QuaternionVectorTransform(model->mOrientation, center);
                            float proj = (model->mPosition.x + r.x) * camDir.x
                                       + (model->mPosition.y + r.y) * camDir.y
                                       + (model->mPosition.z + r.z) * camDir.z;
                            if (proj > planeDist)
                                continue;
                            float nearDist = planeDist - 3.0f;
                            if (proj > nearDist)
                                fade = 1.0f - SmoothBlend(nearDist, planeDist, proj);
                        }
                        if (g_cullBySphere) {
                            Vector3 p = model->mPosition;
                            float lenSq = p.x * p.x + p.y * p.y + p.z * p.z;
                            float radiusSq = radius * radius;
                            if (lenSq > radiusSq) {
                                const Vector3& d = model->mArrowDir;
                                Vector3 a;
                                a.x = p.y * d.z - p.z * d.y;
                                a.y = p.z * d.x - p.x * d.z;
                                a.z = p.x * d.y - p.y * d.x;
                                Vector3 b;
                                b.x = a.y * d.z - a.z * d.y;
                                b.y = a.z * d.x - a.x * d.z;
                                b.z = a.x * d.y - a.y * d.x;
                                float bLenSq = b.x * b.x + b.y * b.y + b.z * b.z;
                                if (bLenSq < 1e-5f) {
                                    float rr = radius + 0.1f;
                                    if (lenSq > rr * rr)
                                        continue;
                                } else {
                                    float inv = InvSqrt(bLenSq);
                                    float t = (b.x * inv) * p.x + (b.y * inv) * p.y + (b.z * inv) * p.z;
                                    float disc = t * t - (lenSq - radiusSq);
                                    if (!(disc >= 0.0f))
                                        continue;
                                    float hs = model->mScale * 0.5f;
                                    ModelResource* res = model->mpResource;
                                    float ex = res->mBoundsSize.x * hs;
                                    float ey = res->mBoundsSize.y * hs;
                                    float hit = -t - sqrtf(disc);
                                    if (hit * hit > ex * ex + ey * ey)
                                        continue;
                                }
                            }
                        }
                    }
                colors:
                    ColorARGB color;
                    if (useObjectColor) {
                        Color4f c;
                        GetObjectColor(obj, &c);
                        color.b = (uint8_t)(int)(c.b * 255.0f);
                        color.g = (uint8_t)(int)(c.g * 255.0f);
                        color.r = (uint8_t)(int)(c.r * 255.0f);
                        color.a = (uint8_t)(int)(c.a * fade * 255.0f);
                    } else if (colorMode == 0x10) {
                        color.b = (uint8_t)(int)(obj->mColorB * 255.0f);
                        color.g = (uint8_t)(int)(obj->mColorG * 255.0f);
                        color.r = (uint8_t)(int)(obj->mColorR * 255.0f);
                        color.a = (uint8_t)(int)(obj->mAlpha * fade * 255.0f);
                    } else {
                        ModelResource* res = model->mpResource;
                        color.b = Max((uint8_t)0x20, (uint8_t)(int)(res->mColorB * 255.0f));
                        color.g = Max((uint8_t)0x20, (uint8_t)(int)(res->mColorG * 255.0f));
                        color.r = Max((uint8_t)0x20, (uint8_t)(int)(res->mColorR * 255.0f));
                        color.a = (uint8_t)(int)(obj->mAlpha * fade * 255.0f);
                    }

                    int shape = obj->mShape;
                    if (shape == 4)
                        shape = obj->mShapeAlt;
                    switch (shape) {
                    case 0: {
                        ModelResource* res = model->mpResource;
                        float s = model->mScale;
                        Vector3 lo;
                        lo.x = s * res->mBoundsMin.x;
                        lo.y = res->mBoundsMin.y * s;
                        lo.z = res->mBoundsMin.z * s;
                        Vector3 hi;
                        hi.x = res->mBoundsSize.x * s + lo.x;
                        hi.y = res->mBoundsSize.y * s + lo.y;
                        hi.z = res->mBoundsSize.z * s + lo.z;
                        DrawBox(ctx, QuaternionToMatrix(model->mOrientation), model->mPosition, 1.0f,
                                lo, hi, color, flags);
                        break;
                    }
                    case 1:
                    case 2:
                        DrawModelShape(ctx, model, color, color, flags);
                        break;
                    }
                }

                if (boxMode == 1 || (boxMode != -1 && (obj->mFlags & 4))) {
                    Vector3 pos;
                    pos.x = 0.0f;
                    pos.y = 0.0f;
                    pos.z = 0.0f;
                    Quaternion q;
                    q.x = 0.0f;
                    q.y = 0.0f;
                    q.z = 0.0f;
                    q.w = 1.0f;
                    GetModelTransform(model, &pos, &q, 0);
                    Vector3 hi;
                    hi.x = 0.15f;
                    hi.y = 0.15f;
                    hi.z = 0.15f;
                    Vector3 lo;
                    lo.x = kMinusBoxHalf;
                    lo.y = kMinusBoxHalf;
                    lo.z = kMinusBoxHalf;
                    DrawBox(ctx, QuaternionToMatrix(q), pos, 1.0f, lo, hi, kMagenta, flags);

                    Vector3 diff;
                    diff.x = pos.x - model->mPosition.x;
                    diff.y = pos.y - model->mPosition.y;
                    diff.z = pos.z - model->mPosition.z;
                    Vector3 lineHi;
                    lineHi.x = 0.025f;
                    lineHi.y = 0.025f;
                    lineHi.z = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
                    Vector3 up;
                    up.x = 0.0f;
                    up.y = 0.0f;
                    up.z = 1.0f;
                    Vector3 zero;
                    zero.x = 0.0f;
                    zero.y = 0.0f;
                    zero.z = 0.0f;
                    DrawBox(ctx, MatrixFromVectors(up, diff, 0, 0), model->mPosition, 1.0f,
                            zero, lineHi, kMagenta, flags);
                }

                if (axesMode == 1) {
                    Vector3 hi;
                    hi.x = 0.15f;
                    hi.y = 0.15f;
                    hi.z = 0.05f;
                    Vector3 up;
                    up.x = 0.0f;
                    up.y = 0.0f;
                    up.z = 1.0f;
                    Matrix3 rot = MatrixFromVectors(up, model->mArrowDir, 0, 0);
                    Vector3 lo;
                    lo.x = kMinusBoxHalf;
                    lo.y = kMinusBoxHalf;
                    lo.z = -0.05f;
                    Vector3 pos;
                    pos.x = model->mArrowDir.x * 0.05f + model->mArrowBase.x;
                    pos.y = model->mArrowBase.y + model->mArrowDir.y * 0.05f;
                    pos.z = model->mArrowBase.z + model->mArrowDir.z * 0.05f;
                    DrawBox(ctx, rot, pos, 1.0f, lo, hi, kGreen, flags);
                }
            }
        }
        viewer.p->End();
    }
}

// @ 0x00a099e0
void SL71::v099e0(void* pos, unsigned count, void* val)
{
    char* self = (char*)this;
    char* begin = *(char**)self;
    char* end   = *(char**)(self + 4);
    unsigned room = (unsigned)((*(char**)(self + 8) - end) / 0xc);
    if (room < count)
    {
        unsigned size = (unsigned)((end - begin) / 0xc);
        unsigned newCap = size * 2;
        if (size == 0)
            newCap = 1;
        unsigned need = size + count;
        if (need < newCap)
            need = newCap;
        char* buf;
        if (need == 0)
            buf = 0;
        else
            buf = (char*)FUN_00f473a0(need * 0xc, EASTL_TAG, 0, 0, ALLOC_FILE, 0xd1);
        char* p1 = (char*)FUN_00a11310(begin, pos, buf);
        FUN_006e5760(p1, count, val);
        char* p2 = (char*)FUN_00a11310(pos, end, p1 + count * 0xc);
        char* old = begin;
        if (old != 0 && old != *(char**)(self + 0x10))
            FUN_00f47380(old);
        *(char**)self = buf;
        *(char**)(self + 4) = p2;
        *(char**)(self + 8) = buf + need * 0xc;
    }
    else if (count != 0)
    {
        unsigned local_c = ((unsigned*)val)[0];
        unsigned local_8 = ((unsigned*)val)[1];
        unsigned local_4 = ((unsigned*)val)[2];
        unsigned avail = (unsigned)((end - (char*)pos) / 0xc);
        if (count < avail)
        {
            char* src = end - count * 0xc;
            FUN_00898b80(&val, src, end, end, pos);
            *(char**)(self + 4) = end + count * 0xc;
            FUN_00abced0(pos, src, end);
            FUN_00a177f0(pos, (char*)pos + count * 0xc, &local_c);
            return;
        }
        unsigned extra = count - avail;
        FUN_006e5760(end, extra, &local_c);
        *(char**)(self + 4) = end + extra * 0xc;
        FUN_00898b80(&pos, pos, end, *(char**)(self + 4), pos);
        *(char**)(self + 4) = *(char**)(self + 4) + avail * 0xc;
        FUN_00a177f0((char*)pos, end, &local_c);
    }
}

// @ 0x00a09cf0
void SL71::v09cf0(void** out, void* where, unsigned* key, char flag)
{
    char* self = (char*)this;
    int b;
    if (flag == 0 && where != (void*)(self + 4) &&
        *(unsigned*)((char*)where + 0x10) <= *key)
        b = 1;
    else
        b = 0;
    char* node = (char*)FUN_00f473a0(0x18, EASTL_TAG, 0, 0, ALLOC_FILE, 0xd1);
    char* n16 = node + 0x10;
    if (n16 != 0)
    {
        *(unsigned*)n16 = key[0];
        unsigned v = key[1];
        *(unsigned*)(n16 + 4) = v;
        if (v != 0)
            ((void (__fastcall *)(void*))FUN_0068f950)((void*)v);
    }
    FUN_009216a0(node, where, self + 4, b);
    *(int*)(self + 0x14) += 1;
    *out = node;
}

// @ 0x00a09e70
void* SL71::v09e70(void* a2, void* a3)
{
    char* self = (char*)this;
    *(void**)(self + 0)    = (void*)0x1448f68;
    *(void**)(self + 4)    = (void*)0x1448f54;
    *(void**)(self + 8)    = 0;
    *(void**)(self + 0xc)  = 0;
    *(void**)(self + 0x10) = 0;
    *(void**)(self + 0x14) = 0;
    ((void (__fastcall *)(void*))FUN_00579a90)(a3);   // RangeInitialize(a3), ecx = this+0x18
    *(void**)(self + 0x1c) = a2;
    if (a2 != 0)
        ((vt_v)*(void**)a2)(a2);
    *(unsigned*)(self + 0x20) = 1;
    *(void**)(self + 0x24) = 0;
    *(void**)(self + 0x28) = 0;
    *(void**)(self + 0x2c) = 0;
    *(uint8*)(self + 0x38) = 0;
    *(void**)(self + 0x3c) = 0;
    *(void**)(self + 0x40) = 0;
    *(void**)(self + 0x44) = 0;
    *(uint8*)(self + 0x48) = 1;
    *(void**)(self + 0x4c) = 0;
    char* p = self + 0x68;
    char* q = self + 0x90;
    for (int i = 0xfe; i >= 0; --i)
    {
        *(void**)(p + 4) = 0;
        *(void**)(p + 8) = 0;
        *(void**)(p + 0xc) = 0;
        *(void**)(p + 0x10) = 0;
        *(void**)(p + 0x14) = 0;
        *(void**)(p + 0x18) = 0;
        *(void**)(p + 0x1c) = 0;
        *(void**)(p + 0x20) = 0;
        *(unsigned*)(q - 8) = 0x3f800000;
        *(unsigned*)(q - 24) = 0x3f800000;
        *(unsigned*)p = 0x3f800000;
        *(void**)(q + 4) = 0;
        *(void**)q = 0;
        *(void**)(q - 4) = 0;
        p += 0x30;
        q += 0x30;
    }
    *(uint8*)(self + 0x303a) = 0;
    *(uint8*)(self + 0x3038) = 1;
    *(uint8*)(self + 0x3039) = 1;
    return self;
}

// @ 0x00a09f90
void SL71::v09f90()
{
    char* self = (char*)this;
    void* p;
    p = *(void**)(self + 0x4c);
    if (p) ((vt_v)vfn(p, 4))(p);
    p = *(void**)(self + 0x44);
    if (p) ((vt_v)vfn(p, 4))(p);
    p = *(void**)(self + 0x24);
    if (p && *(int*)((char*)p - 4) != 0)
        FUN_00f47380(p);
    p = *(void**)(self + 0x1c);
    if (p) ((vt_v)vfn(p, 4))(p);
    p = *(void**)(self + 0xc);
    if (p && (2 < (int)((*(char**)(self + 0x14) - (char*)p) & 0xfffffffeU)))
        FUN_00f47380(p);
    *(void**)(self + 4) = (void*)0x13ec458;
    *(void**)(self + 0) = (void*)0x13eb938;
}

// @ 0x00a0a020
void SL71::v0a020()
{
    char* self = (char*)this;
    FUN_009c67e0(*(void**)(self + 0x28), *(void**)(self + 0x2c));
    void* p = *(void**)(self + 0x28);
    if (p && *(int*)((char*)p - 4) != 0)
        FUN_00f47380(p);
    p = *(void**)(self + 0x10);
    if (p && *(int*)((char*)p - 4) != 0)
        FUN_00f47380(p);
    void* q = *(void**)(self + 8);
    if (q)
    {
        if ((int)*(unsigned*)((char*)q + 0x40) < 2)
            ((vt_v_i)vfn(q, 0x170))(q, *(unsigned*)((char*)q + 4) >> 0x1f);
        else
            *(int*)((char*)q + 0x40) -= 1;
    }
    void* r = *(void**)(self + 4);
    if (r)
        ((vt_v)vfn(r, 4))(r);
}

// @ 0x00a0a0b0
unsigned SL71::v0a0b0(void* a1, unsigned a2, unsigned a3)
{
    if (a3 == 0)
        return 0;
    unsigned local_10 = (unsigned)(size_t)a1;
    unsigned local_c  = a2;
    unsigned local_8  = a3;
    ((void (__fastcall *)(void*))FUN_009b3450)((void*)(size_t)a3);
    FUN_00a09420(&a1, &local_10, (void*)(size_t)(a3 & 0xffffff00));
    FUN_009c26a0((void*)(size_t)a3);
    return a2 & 0xff;
}

// @ 0x00a0a120
unsigned f0a120()
{
    void* local_40 = (void*)0x13eb428;
    unsigned local_3c = 0xee17c6ad;
    unsigned local_20 = 0;
    void* mgr = FUN_0067dcd0();
    if (((vt_i)vfn(mgr, 0x38))(mgr) != 0)
    {
        // The full resource walk / WildcardMatch / job kick-off sequence is not
        // reconstructed (unreachable-block warnings in the original). best-effort.
    }
    if (local_20 && *(int*)(local_20 - 4) != 0)
        FUN_00f47380((void*)local_20);
    (void)local_40;
    (void)local_3c;
    return 0;
}

// @ 0x00a0a360
void SL71::v0a360(void* a2, void* a3)
{
    char* self = (char*)this;
    char* end = *(char**)(self + 4);
    if (end != *(char**)(self + 8))
    {
        if ((char*)a2 <= (char*)a3 && (char*)a3 < end)
            a3 = (char*)a3 + 1;
        if (end)
        {
            void* ref = *(void**)(end - 4);
            *(void**)end = ref;
            if (ref)
                ((vt_v)*(void**)ref)(ref);
        }
        FUN_00ac97a0(a2, *(char**)(self + 4) - 4, *(char**)(self + 4));
        a3 = *(void**)a3;
        void* old = *(void**)a2;
        if (a3 != old)
        {
            if (a3)
                ((vt_v)*(void**)a3)(a3);
            *(void**)a2 = a3;
            if (old)
                ((vt_v)vfn(old, 4))(old);
        }
        *(char**)(self + 4) += 4;
        return;
    }
    int n = (int)(end - *(char**)self) >> 2;
    if (n == 0)
        n = 1;
    else
        n *= 2;
    void* buf = n ? FUN_00f473a0(n * 4, EASTL_TAG, 0, 0, ALLOC_FILE, 0xd1) : 0;
    size_t bytes = (char*)a2 - *(char**)self;
    char* d = (char*)FUN_00a11310(*(void**)self, a2, buf);
    void* elem = *(void**)a3;
    if (d)
    {
        *(void**)d = elem;
        if (elem)
            ((vt_v)*(void**)elem)(elem);
    }
    char* d2 = (char*)FUN_00a11310(a2, *(void**)end, d + 4);
    char* oldp = *(char**)self;
    if (oldp != 0 && *(int*)(oldp - 4) != 0)
        FUN_00f47380(oldp);
    *(char**)(self + 4) = d2;
    *(char**)self = (char*)buf;
    *(char**)(self + 8) = (char*)buf + n * 4;
    (void)bytes;
}

// @ 0x00a0a520
void* SL71::v0a520(void* a2)
{
    char* self = (char*)this;
    char* p = (char*)a2;
    FUN_00a05830((int)((*(char**)(p + 4) - *(char**)p) / 0x1c), p + 0xc);
    char* out = 0;
    FUN_00a09560(&out, *(void**)p, *(void**)(p + 4), *(void**)self, p);
    *(void**)(self + 4) = out;
    return self;
}

// @ 0x00a0a580
int f0a580(unsigned* a1, unsigned* a2, int a3)
{
    if (a1 == a2)
        return a3;
    do
    {
        char* p = (char*)a1;
        char* e = *(char**)(p + 4);
        for (char* q = *(char**)p; q < e; q += 0x1c)
        {
            char* r = *(char**)(q + 0xc);
            if (2 < (int)((*(char**)(q + 0x14) - r) & 0xfffffffeU) && r != 0)
                FUN_00f47380(r);
        }
        char* base = *(char**)p;
        if (base != 0 && *(int*)(base - 4) != 0)
            FUN_00f47380(base);
        a1 += 6;
        a3 += 0x18;
    } while (a1 != a2);
    return a3;
}

// @ 0x00a0a600
unsigned SL71::v0a600()
{
    char* self = (char*)this;
    unsigned count = (unsigned)((*(char**)(self + 0x28) - *(char**)(self + 0x24)) >> 2);
    for (unsigned i = 0; i < count; ++i)
        ((vt_v_i)vfn(self, 0x3c))(self, *(int*)(*(char**)(self + 0x24) + i * 4));
    void* src = *(void**)(self + 0x28);
    void* dst = *(void**)(self + 0x24);
    FUN_00a11310(dst, src, 0);
    int diff = (int)((char*)src - (char*)dst) >> 2;
    *(int*)(self + 0x28) = *(int*)(self + 0x28) + diff * -4;
    void* r = *(void**)(self + 0x44);
    if (r)
    {
        *(void**)(self + 0x44) = 0;
        ((vt_v)vfn(r, 4))(r);
    }
    char* base = *(char**)(self + 0x1c);
    char* stop = *(char**)(base + 0x6c);
    char* it = *(char**)(base + 0x68);
    while (it != stop && *(int*)it != (int)(size_t)self)
        it += 4;
    if ((char*)it + 4 < stop)
        FUN_00898b80(it + 4, stop, it, 0, 0);
    *(char**)(base + 0x6c) = stop - 4;
    void* r2 = *(void**)(base + 0x6c);
    if (*(int*)r2 != 0)
        ((vt_v)vfn((void*)(size_t)*(int*)r2, 4))((void*)(size_t)*(int*)r2);
    void* r3 = *(void**)(self + 0x1c);
    if (r3)
    {
        *(void**)(self + 0x1c) = 0;
        ((vt_v)vfn(r3, 4))(r3);
    }
    return 1;
}

// @ 0x00a0a6d0
void SL71::v0a6d0(void* a2)
{
    char* self = (char*)this;
    char* c = (char*)a2;
    if (c == 0 || *(void**)c == 0)
        return;
    if (*(void**)(c + 0x15c))
    {
        *(void**)(c + 0x15c) = 0;
        FUN_00a05270(c);
    }
    int inst = *(int*)c;
    if (*(int*)(inst + 0x294))
    {
        *(int*)(inst + 0x294) = 0;
        FUN_009c26a0((void*)(size_t)inst);
    }
    int saved = *(int*)inst;
    if (saved)
        FUN_009b3450();
    void* v2 = *(void**)(c + 0x30);
    if (v2)
    {
        FUN_00a007d0(1);
        FUN_00a01c70();
        FUN_00f47380(v2);
        *(void**)(c + 0x30) = 0;
    }
    *(void**)(c + 4) = 0;
    int obj = *(int*)(inst + 0x2c0);
    void* keep = 0;
    if (obj)
    {
        void* inner = *(void**)(obj + 8);
        if (inner)
        {
            *(int*)((char*)inner + 0x40) += 1;
            keep = inner;
        }
    }
    if (obj)
    {
        ((SL71*)(size_t)obj)->v0a020();
        FUN_00f47380((void*)(size_t)obj);
    }
    *(int*)(inst + 0x2c0) = 0;
    if (keep)
    {
        unsigned* k = (unsigned*)keep;
        if ((int)k[0x10] < 2)
            ((vt_v_i)vfn(keep, 0x170))(keep, k[1] >> 0x1f);
        else
            k[0x10] -= 1;
    }
    FUN_009c4d10((void*)(size_t)inst);
    if (*(void**)c)
    {
        *(void**)c = 0;
        FUN_009c26a0((void*)(size_t)inst);
    }
    if (saved)
    {
        int iVar6 = FUN_009aa820(saved);
        int lc = FUN_009a37e0(saved);
        int slot = *(int*)(self + 0x1c);
        int local_4 = 0;
        lc = iVar6 + 1 + lc;
        FUN_00a05730(&local_4, (void*)((char*)(size_t)saved + 0x310));
        int b = local_4 != slot + 0x1c;
        if (b)
            lc += 1;
        if (*(int*)(saved + 0x348) == lc)
        {
            *(uint8*)(saved + 0x34c) = 1;
            if (!b)
            {
                FUN_009a3f50(saved, 0xffffffff);
                if (saved)
                    FUN_009c26a0((void*)(size_t)saved);
            }
        }
    }
    FUN_00a05270(c);
}

// @ 0x00a0a930
void SL71::v0a930()
{
    char* self = (char*)this;
    ((vt_v)vfn(self, 0x38))((void*)self);
    if (g_166c084 != 0)
        FUN_009ac130(*(int*)(self + 0x10));
    void* sobj = *(void**)(self + 0x50);
    unsigned* node = (unsigned*)((vt_p_i)vfn(sobj, 0x28))(sobj, 0xce55aeb1);
    short s = *(short*)((char*)node + 0x12);
    unsigned* pv;
    if (s == 10 || s == 0x10)
    {
        if ((*((uint8*)node + 0x10) & 0x30) == 0)
            pv = (unsigned*)(-(unsigned)(s != 0) & (unsigned)(size_t)node);
        else
            pv = *(unsigned**)node;
    }
    else
        pv = &g_164dc58;
    unsigned total = *pv;
    unsigned done = 0;
    char* it = *(char**)(self + 0x20);
    if (it == self + 0x1c)
        return;
    do
    {
        if (total <= done)
            return;
        int inst = *(int*)(it + 0x18);
        if (inst != 0 && *(char*)(inst + 0x34c) != 0)
        {
            int n = FUN_009a3f50(inst, total - done);
            done += n;
            if (*(int*)(inst + 0x348) == 1)
            {
                *(int*)(self + 0x2c) -= 1;
                void* next = FUN_00921580(it);
                FUN_00921880(it, self + 0x1c);
                if (*(int*)(it + 0x18) != 0)
                    FUN_009c26a0((void*)(size_t)*(int*)(it + 0x18));
                FUN_00f47380(it);
                done += 1;
                it = (char*)next;
                continue;
            }
        }
        it = (char*)FUN_00921580(it);
    } while (it != self + 0x1c);
}

// @ 0x00a0aa20
void SL71::v0aa20(unsigned key)
{
    char* self = (char*)this;
    unsigned k = key;
    void* node = FUN_00e5c780(self + 0x30, &k);
    char* n = (char*)node;
    if (n != self + 0x38)
    {
        if (*(int*)(n + 0x14) != 0)
        {
            int st = FUN_0068f970();
            if (1 < (unsigned)(st - 7))
                FUN_00692400(1);
        }
        *(int*)(self + 0x48) -= 1;
        FUN_00921580(n);
        FUN_00921880(n, self + 0x38);
        if (*(int*)(n + 0x14) != 0)
            FUN_00690120();
        FUN_00f47380(n);
    }
}

// @ 0x00a0aaa0
void SL71::v0aaa0()
{
    char* self = (char*)this;
    *(void**)(self + 0) = (void*)0x1448fe8;
    *(void**)(self + 4) = (void*)0x1448fd4;
    *(void**)(self + 8) = (void*)0x1448fc4;
    void* pu = *(void**)(self + 0x84);
    if (pu)
    {
        int* pc = (int*)((char*)pu + 4);
        int v = *pc;
        *pc = v - 1;
        if (v == 1)
        {
            *pc = 1;
            ((vt_v_i)*(void**)pu)(pu, 1);
        }
    }
    void* r = *(void**)(self + 0x50);
    if (r)
        ((vt_v)vfn(r, 4))(r);
    FUN_00a09890(*(int*)(self + 0x40));
    FUN_00a09850(*(int*)(self + 0x24));
    *(void**)(self + 8) = (void*)0x13ec458;
    *(void**)(self + 4) = (void*)0x1448f54;
    *(void**)(self + 0) = (void*)0x13eb938;
}

// @ 0x00a0ab90
void* SL71::v0ab90(void* a2)
{
    char* self = (char*)this;
    unsigned* p = (unsigned*)a2;
    unsigned* q = p;
    FUN_00a057f0(&q, p);
    unsigned* r = q;
    if (r == (unsigned*)(self + 4) ||
        (p[1] <= r[5] && (p[1] < r[5] || *p < r[4])))
    {
        unsigned local_10 = p[0];
        unsigned local_c  = p[1];
        unsigned local_8  = 0;
        unsigned* masked = (unsigned*)((size_t)r & 0xffffff00);
        FUN_00a098d0(&masked, r, &local_10, masked);
        r = masked;
    }
    return (char*)r + 0x18;
}

// @ 0x00a0ac10
void SL71::v0ac10(unsigned n)
{
    char* self = (char*)this;
    char* begin = *(char**)self;
    char* end   = *(char**)(self + 4);
    unsigned size = (unsigned)((end - begin) / 0xc);
    if (size < n)
    {
        struct { unsigned a; unsigned b; unsigned c; } v;
        v.c = 0x3f800000;
        v.a = 0;
        v.b = 0xbf800000;
        v099e0(end, n - size, &v);
        return;
    }
    FUN_009e0480(begin + n * 0xc, end);
}

// @ 0x00a0b260
anim_creature* AnimWorld::CreateCreatureController(const ResourceKey* key, ResourceObject** pObj, const char* name, uint32_t userData, const vector_3* pos, const vector_4* rot, bool useCache)
{
    uint64_t cacheKey = 0;
    CacheNode* it;
    StaticPtr csdRef;                       // the reference owned by this function
    AutoRefCount_s00a0_aca0 res;
    bool found;
    if (useCache) {
        if (key) {
            cacheKey = (uint64_t)key->instance | ((uint64_t)key->group << 32);
        } else if (pObj) {
            const ResourceObject* obj = *pObj;
            cacheKey = (uint64_t)obj->key.instance | ((uint64_t)obj->key.group << 32);
        } else if (name) {
            cacheKey = (uint64_t)EA::Hash::FNV1_String8(name, 0x811c9dc5, 1) << 16;
        } else {
            return 0;
        }
    }

    creature_static_data* csd = 0;          // working pointer
    res.mpObject = 0;
    found = false;
    if (useCache) {
        cacheHolder->cache.find(&it, &cacheKey);
        if (it != (CacheNode*)((char*)cacheHolder + 0x1c)) {
            creature_static_data* hit = it->value;
            if (hit) {
                csdRef.Reset(hit);
                csd = hit;
            }
            found = true;
        }
    }
    if (!csd) {
        void* mem = operator_new(0x410, "Anim/World/new_csd", 0, 0, 0, 0);
        if (mem) {
            creature_static_data* fresh = ((creature_static_data*)mem)->Construct();
            if (fresh) {
                csdRef.Reset(fresh);
                csd = fresh;
            }
        }
        bool ok;
        if (key) {
            if (res.mpObject) {
                IResource* old = res.mpObject;
                res.mpObject = 0;
                old->Release();
            }
            if (ResolveResource(key, (void**)&res.mpObject))
                ok = InitStaticDataFromResource(csd, res.mpObject);
            else
                goto tryObject;
        } else {
        tryObject:
            if (pObj)
                ok = InitStaticDataFromResource(csd, (IResource*)*pObj);
            else if (name)
                ok = InitStaticDataFromBlocksFile(csd, name);
            else
                ok = false;
        }
        if (!ok) {
            if (res.mpObject) res.mpObject->Release();
            if (csdRef.mp) csdRef.mp->Release();
            return 0;
        }
        if (useCache) {
            csd->cache_key = cacheKey;
            cacheHolder->cache.at(&cacheKey)->assign(&csdRef.mp);
        } else {
            csd->cache_key = 0;
        }
    }

    creature_instance_data* cid = 0;
    void* cidMem = operator_new(0x1930, "Anim/World/new_cid", 0, 0, 0, 0);
    if (cidMem) {
        cid = ((creature_instance_data*)cidMem)->Construct();
        if (cid) cid->AddRef();
    }
    InitInstance(csd, cid, *pos, *rot, data38);

    bool failed = false;
    if (world44 && flag48) {
        bool ok;
        if (key && (res.mpObject || ResolveResource(key, res.AsPPTypeParam()))) {
            void* m = operator_new(0x3c, "Anim/World/new_cmid", 0, 0, 0, 0);
            creature_model_inst* cmid = m ? ((creature_model_inst*)m)->Construct() : 0;
            cid->model = cmid;
            ok = cmid->InitFromResource(cid, world44, res.mpObject, key, flag303a);
        } else if (pObj) {
            void* m = operator_new(0x3c, "Anim/World/new_cmid", 0, 0, 0, 0);
            creature_model_inst* cmid = m ? ((creature_model_inst*)m)->Construct() : 0;
            cid->model = cmid;
            ok = cmid->InitFromBlocks(cid, world44, (const ResourceKey*)pObj, flag303a);
        } else {
            ok = false;
        }
        if (!ok) {
            creature_model_inst* old = cid->model;
            if (old) {
                old->Destruct();
                operator_delete__(old);
            }
            cid->model = 0;
            failed = true;
        } else {
            uint32_t count = (uint32_t)(csd->effects_end - csd->effects_begin);
            for (uint32_t i = 0; i < count; ++i) {
                effect_record* rec = &csd->effects_begin[i];
                IResource* tmp = 0;
                if (ResolveEffectResource(p4c, rec->key0, 0, 0, (void**)&tmp)) {
                    effect* e = cid->AddEffect(0x782efd3, 1, 0);
                    e->Init(tmp, rec->a, i);
                    e->f0c = rec->f0c; e->f10 = rec->f10; e->f14 = rec->f14; e->f18 = rec->f18;
                    e->f1c = rec->f1c; e->f20 = rec->f20; e->f24 = rec->f24;
                    e->active = 1;
                    e->f2c = rec->f08;
                }
                if (tmp) tmp->Release();
            }
        }
    }

    if (flag3039 && !found && useCache)
        g_pBakedAnimManager->PostFeedback(csd, 1);

    anim_creature* ac = 0;
    void* acMem = operator_new(0x19c, "Anim/World/new_ac", 0, 0, 0, 0);
    if (acMem) ac = ((anim_creature*)acMem)->Construct(pos, rot);
    creature_instance_data* oldInst = ac->instance;
    if (cid != oldInst) {
        if (cid) cid->AddRef();
        ac->instance = cid;
        if (oldInst) oldInst->Release();
    }
    ac->userData = userData;
    ac->world = this;
    void* qbMem = operator_new(0xfd0, "Anim/World/new_qb", 0, 0, 0, 0);
    queued_blender* qb = qbMem ? ((queued_blender*)qbMem)->Construct() : 0;
    ac->blender = qb;
    qb->Init(cid, g_pBakedAnimManager);
    ac->f18c = 0;
    ac->f188 = 0;
    ac->creatureCount = (uint32_t)(creatures.mpEnd - creatures.mpBegin);
    ac->flags |= failed ? 2 : 0;
    const int none = -1;
    ac->f70 = none;
    ac->f6c = none;
    ac->slotMask = 1u << ExtractBits(none + 3, 0x20007);
    ac->f198++;
    if (creatures.mpEnd < creatures.mpCapacity) {
        anim_creature** e = creatures.mpEnd++;
        if (e) *e = ac;
    } else {
        creatures.DoInsertValue(creatures.mpEnd, &ac);
    }
    cid->root = ac;
    RegisterCreature(ac);
    cid->Release();
    if (res.mpObject) res.mpObject->Release();
    if (csdRef.mp) csdRef.mp->Release();
    return ac;
}

// @ 0x00a0c690
void cSPCreatureAnimWorld::Update(float dt, cViewer_s00a0_c690* viewer)
{
    if (mCreatures.mpBegin == mCreatures.mpEnd)
        return;

    dt *= *mpManager->mpProperties->GetProperty(0xf29f5604)->GetValueFloat(&kDefaultFloatValue);
    gAnimFlagB04 = *mpManager->mpProperties->GetProperty(0xf113323d)->GetValueBool(&kDefaultBoolValue);
    gAnimIntB6C = *mpManager->mpProperties->GetProperty(0xcbb76b7a)->GetValueInt32();
    float lod2Size = *mpManager->mpProperties->GetProperty(0xa22260b1)->GetValueFloat(&kAnimDefaultFloatValue);
    CreatureSizeCompare sizeCompare(*mpManager->mpProperties->GetProperty(0x18c01e40)->GetValueFloat(&kAnimDefaultFloatValue));
    bool hideWhenOutOfGroup = *mpManager->mpProperties->GetProperty(0xe0e98b25)->GetValueBool(&kAnimDefaultBoolValue);
    SetMaxCreatureByLOD(2, *mpManager->mpProperties->GetProperty(0x17128238)->GetValueInt32());
    SetMaxCreatureByLOD(1, *mpManager->mpProperties->GetProperty(0xf2f23c29)->GetValueInt32());
    SetMaxCreatureByLOD(0, *mpManager->mpProperties->GetProperty(0xf987c782)->GetValueInt32());
    gAnimFloatB74 = *mpManager->mpProperties->GetProperty(0xb9a5e29c)->GetValueFloat(&kDefaultFloatValue);
    gAnimFloatB78 = *mpManager->mpProperties->GetProperty(0xee48fd58)->GetValueFloat(&kDefaultFloatValue);
    gAnimUIntB7C = *mpManager->mpProperties->GetProperty(0x52451e18)->GetValueUInt32();
    gAnimUIntB80 = *mpManager->mpProperties->GetProperty(0x71ae0ceb)->GetValueUInt32();

    mCurrentCreatureByLOD[0] = 0;
    mCurrentCreatureByLOD[1] = 0;
    mCurrentCreatureByLOD[2] = 0;

    Vector3_s00a0_c690 cameraDir;
    Vector3_s00a0_c690 cameraPos;
    Frustum frustum;
    if (!viewer)
        viewer = RenderManager()->GetViewer(0);
    if (viewer) {
        viewer->GetCameraLocationInfo(&cameraPos, 0, 0, &cameraDir);
        frustum.Set(viewer->mViewProjection);
    }

    // Cull and measure every creature.
    uint32_t count = mCreatures.size();
    for (uint32_t i = 0; i < count; ++i) {
        cAnimatingCreature_s00a0_c690* creature = mCreatures.mpBegin[i];
        if (!creature)
            continue;
        creature_instance_data_s00a0_c690* inst = creature->mpInstance.mpObject;
        if (!inst)
            continue;
        inst->mbFlag2d6 = creature->mbFlag151;

        const creature_static_bounds* bounds = inst->mpStatic;
        float scale = creature->mScale;
        Vector3_s00a0_c690 origin(bounds->mBoundsOrigin.x * scale, bounds->mBoundsOrigin.y * scale, bounds->mBoundsOrigin.z * scale);
        Vector3_s00a0_c690 size(bounds->mBoundsSize.x * scale, bounds->mBoundsSize.y * scale, bounds->mBoundsSize.z * scale);
        float diameter = bounds->mBoundsRadius * scale;
        Vector3_s00a0_c690 center(origin.x + size.x * 0.5f, origin.y + size.y * 0.5f, origin.z + size.z * 0.5f);
        float radius = diameter * 0.5f;

        const Quaternion_s00a0_c690& q = inst->mOrientation;
        float yw = q.y * q.w, xw = q.x * q.w, zw = q.z * q.w;
        float xx = -(q.x * q.x), yx = q.y * q.x, zx = q.z * q.x;
        float yy = -(q.y * q.y), zy = q.z * q.y, zz = -(q.z * q.z);
        // rotate the local center by the instance orientation: v + 2 * (M' * v)
        Vector3_s00a0_c690 rotated;
        rotated.x = (zz + yy) * center.x + (yx - zw) * center.y + (zx + yw) * center.z;
        rotated.z = (zx - yw) * center.x + (zy + xw) * center.y + (yy + xx) * center.z;
        Vector3_s00a0_c690 worldCenter(
            inst->mPosition.x + (rotated.x * 2.0f + center.x),
            inst->mPosition.y + (((yx + zw) * center.x + (zz + xx) * center.y + (zy - xw) * center.z) * 2.0f + center.y),
            inst->mPosition.z + (rotated.z * 2.0f + center.z));

        creature->mbInFrustum = (~(frustum.Test(&worldCenter, radius) >> 6)) & 1;
        if (creature->mbInFrustum) {
            Vector3_s00a0_c690 screenCenter;
            App()->GetViewer()->ProjectToScreen(&screenCenter, &worldCenter);
            Vector3_s00a0_c690 edge(cameraDir.x * radius + worldCenter.x,
                         cameraDir.y * radius + worldCenter.y,
                         cameraDir.z * radius + worldCenter.z);
            Vector3_s00a0_c690 screenEdge;
            App()->GetViewer()->ProjectToScreen(&screenEdge, &edge);
            float dx = screenEdge.x - screenCenter.x;
            float dy = screenEdge.y - screenCenter.y;
            float dz = screenEdge.z - screenCenter.z;
            creature->mScreenSize = dx * dx + dz * dz + dy * dy;
        } else {
            creature->mScreenSize = 0.0f;
        }
    }

    stable_sort(mCreatures.mpBegin, mCreatures.mpEnd, sizeCompare);

    // Drop everything from the first null entry on.
    count = mCreatures.size();
    for (uint32_t i = 0; i < count; ++i) {
        if (!mCreatures.mpBegin[i]) {
            mCreatures.resize(i);
            break;
        }
    }

    count = mCreatures.size();
    for (uint32_t i = 0; i < count; ++i) {
        cAnimatingCreature_s00a0_c690* creature = mCreatures.mpBegin[i];
        creature_instance_data_s00a0_c690* inst = creature->mpInstance.mpObject;
        creature->mIndex = i;
        if (!inst)
            continue;

        if (!creature->mbDoUpdate) {
            if (inst->mpMesh)
                inst->mpMesh->SetStateInWorld(true, true, false);
            continue;
        }

        if (!creature->mbInFrustum)
            SetCreatureLOD(creature, 0, 0);
        else if (creature->mScreenSize >= lod2Size)
            SetCreatureLOD(creature, 2, 0);
        else if (creature->mScreenSize >= sizeCompare.mThreshold)
            SetCreatureLOD(creature, 1, 0);
        else
            SetCreatureLOD(creature, 0, 0);

        int lodCount = creature->mLODForced == 4 ? creature->mLODCount : creature->mLODForced;
        if (lodCount > 0)
            creature->UpdateLOD(0);
        else
            creature->mpInstance.mpObject->mSkippedUpdates++;

        if (creature->mpModel && mpManager->mHiddenGroup) {
            uint32_t group = mpModelWorld->GetModelGroup(creature->mpModel, -1);
            if (hideWhenOutOfGroup) {
                if (!group)
                    mpModelWorld->SetModelGroup(creature->mpModel, mpManager->mHiddenGroup, -1);
            } else if (group == mpManager->mHiddenGroup) {
                mpModelWorld->SetModelGroup(creature->mpModel, 0, -1);
            }
        }

        inst->mbFlag270 = creature->mbFlag150;
        inst->mPosition = creature->mPosition;
        inst->mOrientation = creature->mOrientation;
        inst->mScale = creature->mScale;
        inst->mVelocity = creature->mVelocity;
        inst->mAngularSpeed = creature->mAngularSpeed;
        creature->mAngularSpeed = 0.0f;
        creature->mVelocity.x = 0.0f;
        creature->mVelocity.y = 0.0f;
        creature->mVelocity.z = 0.0f;

        switch (creature->mTargetModeRequest) {
        case 0:  inst->mTargetMode = 2; break;
        case 2:  inst->mTargetMode = 1; break;
        default: inst->mTargetMode = 0; break;
        }

        inst->mTarget = creature->mpTargetCreature ? creature->mpTargetCreature->mpInstance
                                                   : AutoRefCount<creature_instance_data_s00a0_c690>();

        inst->mTargetPosition = creature->mTargetPosition;
        inst->mTargetOrientation.x = 0.0f;
        inst->mTargetOrientation.y = 0.0f;
        inst->mTargetOrientation.z = 0.0f;
        inst->mTargetOrientation.w = 1.0f;

        uint32_t contextMode;
        switch (creature->mTargetContextModeRequest) {
        case 1:  contextMode = 1; break;
        case 2:  contextMode = 3; break;
        default: contextMode = 0; break;
        }
        inst->mTargetContextMode = contextMode;
        inst->mTargetContextValue = creature->mTargetContextValue;
        inst->m2a0 = 0;
        inst->m2a4 = 0;

        if (!HasValidTarget(inst)) {
            inst->mTargetMode = 0;
            inst->mTargetPosition.x = 0.0f;
            inst->mTargetPosition.y = -10.0f;
            inst->mTargetPosition.z = 1.0f;
        }

        creature->PrepareUpdate();
        inst->mRestIdle = creature->mRestIdle;
        inst->mMoveIdle = creature->mMoveIdle;
        inst->mpDataEvents = creature->mDataEvents;
        inst->mpTargetData = creature->mTargetData;
        inst->mTargetDataStride = 0x10;
        inst->mDataEventStride = 0xc;
        inst->mColor = creature->mbHasColor ? creature->mColor : Vector3_s00a0_c690(1.0f, 1.0f, 1.0f);

        creature->mpBlender->Update(dt, lodCount < 2, lodCount == 0, IsPaused());
        creature->SetRestIdleAnimHandle();
    }
}

// @ 0x00a0ea10
bool __stdcall ReadAnimTable(IFile* f)
{
    int magic;
    uint version;
    ReadInt32(f, &magic, 1, 0);
    ReadInt32(f, &version, 1, 0);
    if (version - 5 <= 5) {
    uint count;
    ReadInt32(f, &count, 1, 0);
    for (uint n = 0; n < count; n++) {
        Entry e;
        e.Reset();

        if (version > 8) {
            ReadInt32(f, &e.key, 1, 0);
            uint len = 0;
            ReadInt32(f, &len, 1, 0);
            e.name.resizeOut(len);
            f->Read(e.name.mpBegin, len * 2);
            ReadInt32(f, &e.f14, 1, 0);
            ReadInt32(f, &e.f18, 1, 0);
            ReadBool(f, &e.b1c);
            ReadBool(f, &e.b1d);
            if (version >= 10)
                ReadBool(f, &e.b1e);
            ReadInt32(f, &e.i20, 1, 0);
            ReadInt32(f, &e.i24, 1, 0);
            int tmp;
            ReadInt32(f, &tmp, 1, 0);
            e.i28 = tmp;

            uint nSubs;
            ReadInt32(f, &nSubs, 1, 0);
            e.subs.resize(nSubs);
            for (uint j = 0; j < nSubs; j++) {
                Sub* s = &e.subs.mpBegin[j];
                ReadInt32(f, &s->i14, 1, 0);
                uint m;
                ReadInt32(f, &m, 1, 0);
                s->items.resize(m);
                for (uint k = 0; k < m; k++) {
                    Item* it = &s->items.mpBegin[k];
                    ReadInt32(f, &it->w0, 1, 0);
                    ReadInt32(f, &it->w4, 1, 0);
                    ReadInt32(f, &it->w8, 1, 0);
                    uint l2 = 0;
                    ReadInt32(f, &l2, 1, 0);
                    it->name.resize(l2);
                    f->Read(it->name.mpBegin, l2 * 2);
                }
            }
        
        } else {
            ReadInt32(f, &e.key, 1, 0);
            if (version >= 8)
                ReadInt32(f, &e.f14, 1, 0);
            e.subs.resize(1);

            uint c = 0;
            ReadInt32(f, &c, 1, 0);
            e.subs.mpBegin->items.resize(c);
            for (uint i = 0; i < c; i++) {
                string16& nm = e.subs.mpBegin->items.mpBegin[i].name;
                uint len = 0;
                ReadInt32(f, &len, 1, 0);
                nm.resize(len);
                f->Read(nm.mpBegin, len * 2);
            }
            for (uint i = 0; i < c; i++)
                ReadInt32(f, &e.subs.mpBegin->items.mpBegin[i].w8, 1, 0);

            Sub* s0 = e.subs.mpBegin;
            if (s0->items.mpBegin != s0->items.mpEnd) {
                string16* nm0 = &s0->items.mpBegin->name;
                if (nm0 != &e.name)
                    e.name.assign(nm0->mpBegin, nm0->mpEnd);
            }

            float a, b;
            ReadInt32(f, &a, 1, 0);
            ReadInt32(f, &b, 1, 0);
            for (uint i = 0; i < c; i++) {
                e.subs.mpBegin->items.mpBegin[i].w4 = b;
                e.subs.mpBegin->items.mpBegin[i].w0 = a;
            }
            ReadBool(f, &e.b1c);
            if (version >= 6)
                ReadInt32(f, &e.f18, 1, 0);
            ReadBool(f, &e.b1d);
            ReadInt32(f, &e.i20, 1, 0);
            if (version < 7)
                e.i24 = e.i20;
            else
                ReadInt32(f, &e.i24, 1, 0);
            int tmp;
            ReadInt32(f, &tmp, 1, 0);
            e.i28 = tmp;
        }

        // merge into the global map: insert unless a record with this key and a newer f18 exists
        RBNode* header = &gEntryMap.anchor;
        RBNode* x = header->parent;
        RBNode* y = header;
        while (x) {
            if (!(((EntryNode*)x)->value.key < e.key)) {
                y = x;
                x = x->left;
            } else
                x = x->right;
        }
        if (y == header || e.key < ((EntryNode*)y)->value.key || e.f14 >= ((EntryNode*)y)->value.f18) {
            Entry* d = gEntryMap.GetOrInsert(&e.key);
            d->key = e.key;
            d->name = e.name;
            d->f14 = e.f14;
            d->f18 = e.f18;
            d->b1c = e.b1c;
            d->b1d = e.b1d;
            d->b1e = e.b1e;
            d->i20 = e.i20;
            d->i24 = e.i24;
            d->i28 = e.i28;
            d->subs.assign(e.subs);
        }
    }
    return true;
    }
    return false;
}

// @ 0x00a0f350
bool AnimMgr::Init(bool flag)
{
    g_animMgr = this;
    if (!g_obj_166c058.Prep())
        return false;
    ReadAnimList(1);
    if (!mMaterial && GetMaterialManager())
        mMaterial = GetMaterialManager()->GetMaterial(0xb660f636);
    if (!mHolder && GetResMgr()) {
        RefA* a = new("Anim", 0, 0, 0, 0) RefA();
        ((RefSlot*)&mHolder)->Assign(a);
        RefB* b = new("Anim", 0, 0, 0, 0) RefB();
        b->InsertResource(0, GetResMgr()->GetResource(0xbd77bb98, 0, 0));
        RefC* c = new("Anim", 0, 0, 0, 0) RefC();
        c->mA = 20.0f;
        c->mKind = 6;
        c->mB = 0.0f;
        c->mC = 1.0f;
        c->mD = 0.0f;
        u32* tv = (u32*)b;
        mHolder->mVec.push_back(tv);
        tv = (u32*)c;
        mHolder->mVec.push_back(tv);
    }
    IPropMgr* pm = GetPropertyManager();
    if (mPropertyList) {
        IPropList* old = mPropertyList;
        mPropertyList = 0;
        ((IRefObj*)old)->Release();
    }
    pm->GetPropertyList(0x1347ba4d, 0, (IRefObj**)&mPropertyList);
    IServer* srv = GetMessageServer();
    u32 off = 0;
    if (srv) {
        void* handler = (u8*)this + 4;
        mAuto.mServer = srv;
        mAuto.mHandler = handler;
        mAuto.mIds = g_animMsgIds;
        mAuto.mCount = 2;
        mAuto.mFlag = 0;
        if (handler) {
            do {
                srv->AddHandler(handler, *(u32*)((u8*)g_animMsgIds + off));
                off += 4;
            } while (off < 8);
        }
    }
    if (flag)
        FUN_00a059d0(this);
    IPropData* pd = mPropertyList->GetProperty(0x213eb74f);
    u16 type = pd->mType;
    u32* v;
    if (type == 10 || type == 16) {
        if (pd->mFlags & 0x30)
            v = pd->mData;
        else
            v = (u32*)(-(u32)(type != 0) & (u32)pd);
    } else {
        v = g_defaultPropVal;
    }
    SetAppMode(*v);
    ICheatMgr* cm = GetCheatManager();
    if (cm) {
        BlocksModeCmd* cmd = new("Anim", 0, 0, 0, 0) BlocksModeCmd();
        if (cmd) cmd->mMgr = this;
        cm->AddCommand("blocksmode", cmd, 0);
    }
    return true;
}

// @ 0x00a0f610
bool AnimHandler::HandleMessage(u32 id, Msg* m)
{
    switch (id) {
    case 0xf62add: {
        void* data = m->mData;
        switch (m->mSel) {
        case 0x25df0112:
            Do08ba0();
            break;
        case 0x4aeb6bc6:
            ((AnimMgr*)((char*)this - 4))->ReadAnimList(1);
            return false;
        case 0xee17c6ad: {
            void* p = FUN_009a37a0(data);
            if (p) {
                FUN_009a4020(p, -1);
                g_obj_166c084->Fn(p, -1);
            }
            return true;
        }
        }
        break;
    }
    case 0x22d1adc:
        mAppMode = m->mSel;
        return false;
    }
    return false;
}
