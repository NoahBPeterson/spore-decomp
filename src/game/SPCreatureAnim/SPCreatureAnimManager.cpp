// src/game/SPCreatureAnim/SPCreatureAnimManager.cpp -- migrated from slice(s) s00a0d2d0, s00a0bcf0, s00a08b00, s00a07ae0, s00a06600, s00a05c20, s00a04d20, s00a027a0, s00a00980, s009ffa00, s009feb30, s00a0f350, s00a0e4c0, s00a0c690, s00a0aca0, s00a099e0, s00a06d50, s00a03da0, s00a02da0, s00a01810 by tools/migrate/rewrite.py
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
#include <intrin.h>
#include "SP/cAnimatingCreature.h"
#include "EA/Variant.h"
#include "EA/ArgScript/cArguments.h"
#include "SP/cJob.h"
#include <stdio.h>
#include <wchar.h>

// ---- items of slice s00a01810 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" extern const float g_1485720;
extern "C" extern const float g_13eb1bc;
extern "C" extern const float g_13f6a3c;
extern "C" extern const float g_13ec480;
extern "C" extern const float g_1550b78;
extern "C" extern const float g_1550b74;
extern "C" extern const float g_15517d0;
extern "C" void  __stdcall  vci(void* dst, int size, int count, void* ctor);
extern "C" void  __cdecl    animref_ctor();
extern "C" float __cdecl    f_9b01e0(float a, float b, float c);
extern "C" void  __cdecl    f_9b3bc0(void* a);
extern "C" void  __cdecl    f_9bb910(void* a);
extern "C" float __cdecl    f_9a2c90(void* a, float b, char c, int d);
extern "C" char  __cdecl    f_9a38f0(void* a, int b, void* c);
extern "C" int   __cdecl    f_9a4430(int a, int b, int c);
extern "C" int   __cdecl    f_9a4550(void* a, int b);
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
class CObj {
public:
    char pad[0x400];
    void T660();
    void T060();
    void T0b0();
};
class RefObj {
public:
    char   pad[0xb0];
    double mBlendA;          // +0xb0
    double mBlendB;          // +0xb8
    char   pad_rest[0x1000 - 0xc0];
    void  Rel9ae1c0();
    void  Rel9a3630();
    void  Rel9c4cc0();
    float Ac2b0();                                                   // 0x9ac2b0
    void  Acac0(float scale, void* cid, RefObj* f0, float blend, int a, int b, int c);  // 0x9acac0
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
extern "C" int   __cdecl    qb_free_slot(anim_qb* qb);
extern "C" char  __cdecl    qb_find2(anim_qb* qb, anim_query* q);
extern "C" void  __cdecl    qb_add(anim_qb* qb, anim_query* q, int a, int b);
extern "C" anim_query* __cdecl qb_get(anim_qb* qb, int id);
extern "C" void  __cdecl    qb_get2(anim_query** out, anim_qb* qb, int id);
extern "C" void  __cdecl    f_99e110(float a, void* b, RefObj* c, int d, int e, int f);
class cAnimatingCreature {
public:
    char pad[0x1000];
    bool IsOrientStartAnim(uint32_t animID);
    bool IsOrientStopAnim(uint32_t animID);
};
// ---- items of slice s00a01810 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void qb_set_query(anim_qb* qb, int index, int mode, bool idle);  // 0x00a01810 (stays in the slice: not this object's)

// ---- items of slice s00a02da0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_flt_01551a88;
extern float g_flt_01551a84;
// ---- items of slice s00a02da0 end

// ---- items of slice s00a03da0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_009ff750(void* mgr);                            // 0x9ff750
extern "C" void* FUN_009ff6f0(void* mgr, int id);                    // 0x9ff6f0
extern "C" int   FUN_0099d0b0(void* a, void* b, void* c, void* d);   // 0x99d0b0
extern "C" __declspec(dllimport) double modf(double x, double* iptr);  // msvcr90!modf
extern "C" float* FUN_009a46a0(float* out, const float* quat);       // 0x9a46a0
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
const float* FUN_00a03da0(void* target, const float* matrix3x3, const float* pos, float scale);
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
struct IUnknown_s00a0_3da0
{
	virtual void AddRef();
	virtual void Release();
};
struct PartSlot   // 0x14 bytes, element of the part list
{
	char pad00[0x0c];
	void* m_inst;   // +0x0c  (child render instance)
};
struct PartList
{
	char pad00[0x28];
	char* m_begin;  // +0x28
	char* m_end;    // +0x2c

	// thiscall members of the part list itself (ecx = this)
	void FUN_009c6fc0(void* mgrpart, float a, float b, float c, float d,
	                  int e, int f, unsigned char g);   // 0x9c6fc0
};
struct RenderInst
{
	char pad00[8];
	unsigned short m_flags;     // +0x08  (bit 1 = basis dirty, bit 2 = position dirty)
	signed short m_dirty;       // +0x0a  bump counter
	float m_x;                  // +0x0c
	float m_y;                  // +0x10
	float m_z;                  // +0x14
	float m_scale;              // +0x18
	float m_basis[9];           // +0x1c
	char pad40[4];              // +0x40  (unused by these functions)
	uint32_t m_bits0;           // +0x44  (model-group bits 0..31)
	uint32_t m_bits1;           // +0x48  (model-group bits 32..63)
	char pad4c[0x64 - 0x4c];
	IUnknown_s00a0_3da0* m_model;          // +0x64  ref-counted model pointer
};
struct AnimBody
{
	void* m_data;               // +0x00  points at the raw transform storage
	char pad04[0x18 - 4];
	float m_px;                 // +0x18
	float m_py;                 // +0x1c
	float m_pz;                 // +0x20
	char pad24[0x3c - 0x24];
	float m_qw;                 // +0x3c
	float m_qx;                 // +0x40
	float m_qy;                 // +0x44
	float m_qz;                 // +0x48
	char pad4c[0x70 - 0x4c];
	float m_scale;              // +0x70
	char pad74[0x2c0 - 0x74];
	PartList* m_parts;          // +0x2c0
	char pad2c4[0x2d4 - 0x2c4];
	unsigned char m_field2d4;   // +0x2d4
	unsigned char m_field2d5;   // +0x2d5
	char pad2d6[0x1684 - 0x2d6];
	int m_field1684;            // +0x1684
	char pad1688[0x168d - 0x1688];
	unsigned char m_field168d;  // +0x168d

	// thiscall members of the physics body itself (ecx = this)
	void FUN_009b3b20(void* a, void* b, int c);                       // 0x9b3b20
	void FUN_009b3920(const float* pos, const float* quat);           // 0x9b3920
};
struct Mgr193
{
	char pad00[0x1c];
	void* m_field1c;   // +0x1c
};
struct LookupEntry
{
	void* m_obj;               // +0x00
	char pad04[0xc0 - 4];
	uint32_t m_fieldC0;        // +0xc0
};
struct cAnimatingCreature_s00a0_3da0
{
	char pad00[4];
	char m_frame04[0x0c];       // +0x04  (target frame position, for the body transform helper)
	char m_frame10[0x40];       // +0x10
	int m_mode50;               // +0x50
	int m_mode54;               // +0x54
	char pad58[0x74 - 0x58];
	float m_blendX;             // +0x74
	float m_blendY;             // +0x78
	float m_blendZ;             // +0x7c
	float m_blendW;             // +0x80
	unsigned char m_flag84;     // +0x84
	char pad85[0x17c - 0x85];
	AnimBody* m_body;           // +0x17c
	RenderInst* m_inst;         // +0x180
	void* m_lookup184;          // +0x184
	void* m_field188;           // +0x188  (unused by these functions)
	void* m_field18c;           // +0x18c  (unused by these functions)
	Mgr193* m_scene190;         // +0x190

	void FUN_00a04550(int index, const float* value);
	void FUN_00a047d0(unsigned char param2);
	int  FUN_00a048b0(int id, int a3, int a4, int a5);
	bool FUN_00a04900(int unused);
	bool FUN_00a04940(int id);
	bool FUN_00a04990(int id);
	float FUN_00a049f0(int id);
	void FUN_00a04ab0(unsigned char value);
	void FUN_00a04ad0(int value);
	void FUN_00a04af0(IUnknown_s00a0_3da0* model);
	void FUN_00a04bb0(unsigned index, unsigned char enable);
	void FUN_00a04ca0(unsigned char value);
	void FUN_00a04cc0(unsigned char value);
};
float* FUN_00a04590(cAnimatingCreature_s00a0_3da0* self, float* out);              // 0x00a04590
void FUN_00a04630(cAnimatingCreature_s00a0_3da0* self, unsigned char param2, unsigned char param3);  // 0x00a04630
#define g_softStateDirty      (*(uint32_t*)0x16f9528)
#define g_transformType       (*(uint32_t*)0x16f96a0)
#define g_transformPtr        (*(void**)0x16fa380)
#define g_transformLocal      ((float*)0x16fa4f0)
#define g_posNegate           (*(const uint32_t*)0x13eb8b0)
#define g_minusOne            (*(const float*)0x13eb1bc)
#define g_uintToFloat         (*(const float*)0x13f4fd0)
static void AssignModel(RenderInst* inst, IUnknown_s00a0_3da0* model)
{
	if (!inst)
		return;
	IUnknown_s00a0_3da0* old = inst->m_model;
	if (model == old)
		return;
	if (model)
		model->AddRef();
	inst->m_model = model;
	if (old)
		old->Release();
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
    void**   v09cf0(void** out, void* where, unsigned* key, char flag);
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
extern void __cdecl PrintError(const char* msg, const char* group);       // 0x00e31100
typedef unsigned int uint;
struct IFile {
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
virtual void v10(int, int);
virtual void v11();
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
    union { int i14; float f14; };
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
    Entry(const Entry& o);                                // 0x00a0d7a0
    Entry& operator=(const Entry& o);                     // 0x00a0df30
};
struct RBNode { RBNode* right; RBNode* left; RBNode* parent; char color; };
struct EntryNode : RBNode { Entry value; };               // value at +0x10
struct AnimNode_s00a0_e4c0 : RBNode { uint key; Entry value; };      // key +0x10, value +0x14
struct EntryMap {
    int pad0;
    RBNode anchor;            // +0x04
    uint size;
    Entry* GetOrInsert(const uint* key);                  // 0x00a0e530 (thiscall, returns &node->value)
    void Insert(void* out, RBNode* hint, const void* pair, int flag); // 0x00a0e180
    void Find(RBNode** out, const uint* key);             // 0x00e5c780
    void DoNukeSubtree(RBNode* root);                     // 0x00a0d9c0
};
extern EntryMap gEntryMap;                                // 0x01551a68
struct EntryPair {
    uint key;
    Entry value;
    EntryPair(uint k, const Entry& v) : key(k), value(v) {}
};
struct AnimParseContext {     // 0x58
    uint   mMagic;            // +0x00 (0x02328502)
    float  mF4;               // +0x04
    EntryMap* mpMap;          // +0x08
    Entry  mEntry;            // +0x0c
    float  mF4c;              // +0x4c
    float  mW0;               // +0x50
    float  mW4;               // +0x54
    AnimParseContext(EntryMap* map);                      // 0x00a0e4c0
    ~AnimParseContext();                                  // 0x00a0d420
};
struct AnimCommandA {         // cAnimCommand (vtable 0x1448be4, OnEndBlock at +0x14)
    int mPad[12];             // +0x00..0x2f
    AnimParseContext* mpContext;                          // +0x30
    void OnEndBlock(char flag);                           // 0x00a0e690
};
struct AnimCommandB {         // cAnimCommand variant (vtable 0x1448d10)
    int mPad[12];
    AnimParseContext* mpContext;                          // +0x30
    void OnEndBlock(char flag);                           // 0x00a0e840
};
extern uint __cdecl FNV1_String16(const wchar_t* s, uint seed, int mode); // 0x00932f30
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

// ---- items of slice s009feb30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_timer;               // 0x015509f0
struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {} };
struct CreatureStatic { char pad[0x3f5]; char field_3f5; };
struct CreatureSub {
    int field_00;
    void FUN_009e3f70(int a, int b);                              // 0x009e3f70
    void FUN_009e4600(Vec3 v, int a, int b, int c, int d);        // 0x009e4600
};
struct CreatureInst {
    CreatureStatic* mStatic;       // +0x00
    char   pad_04[0x6c];
    float  mScale;                 // +0x70
    char   pad_74[0x1ec];
    char   field_260;              // +0x260
    char   pad_261[3];
    float  field_264;
    float  field_268;
    float  field_26c;
    char   pad_270[0x88];
    CreatureSub mSub;              // +0x2f8
    char   pad_2f8[0x1680 - 0x2f8 - 4 - 0];
    char   field_1680;
    char   pad_1681[0xb];
    char   field_168c;
    void FUN_009b8760(float dt);                                  // 0x009b8760
    void FUN_009b7b10(int a, int b);                              // 0x009b7b10
    void FUN_009b8720(float a);                                   // 0x009b8720
    void FUN_009b8d50(float dt);                                  // 0x009b8d50
    void FUN_009b8e40(float a);                                   // 0x009b8e40
    void FUN_009ba040(float dt, float a);                         // 0x009ba040
    void FUN_009c0680();                                          // 0x009c0680
    void FUN_009b8f40(float a);                                   // 0x009b8f40
    void UpdateWiggles(float dt, float a);                        // 0x009bb4f0
};
void __cdecl FUN_009bc580(CreatureInst* inst, float dt);        // 0x009bc580
void __cdecl FUN_0099d460(float a, CreatureInst* inst, int g, float b); // 0x0099d460
void __cdecl FUN_c2e4e0(CreatureInst* inst);                    // 0x00c2e4e0
struct AnimGoal {
    int      field_00;       // +0x00
    int      field_04;       // +0x04
    int      mChildren[24];  // +0x08  (8 slots * 3 dwords, stride 0x0c)
    int      mChildCount;    // +0x68
    int      field_6c;       // +0x6c  packed handle of the active child
    float    field_70;       // +0x70
    float    field_74;       // +0x74
    float    field_78;       // +0x78
    uint8_t  field_7c;       // +0x7c
    char     pad_7d[3];
    int      field_80;       // +0x80
    uint8_t  field_84;       // +0x84
    char     pad_85[3];
    float    field_88;       // +0x88
    float    field_8c;       // +0x8c
    char     pad_90[4];
    float    field_94;       // +0x94
    char     pad_98[8];
    float    field_a0;       // +0xa0
    char     pad_a4[4];
    double   field_a8;       // +0xa8
    char     pad_b0[4];
    uint32_t field_b4;       // +0xb4
    char     pad_b8[4];
    int      field_bc;       // +0xbc
    int      field_c0;       // +0xc0
    float    field_c4;       // +0xc4
    char     pad_c8[4];
    float    field_cc;       // +0xcc
    float    field_d0;       // +0xd0
    uint8_t  field_d4;       // +0xd4
    char     pad_d5[3];
    int      field_d8;       // +0xd8
    char     pad_dc[0xf0 - 0xdc];

    void Init();
    void CopyFiltersFrom(AnimGoal* o);
    int  IsActive();
};
struct QueuedBlender {
    char     pad_00[8];
    AnimGoal mGoals[16];     // +0x08, stride 0xf0
    char     pad_f08[4];
    uint32_t mActive[16];    // +0xf0c
    uint32_t mQueue[16];     // +0xf4c
    uint32_t field_f8c;      // +0xf8c
    char     pad_f90[0xc];
    int      field_f9c;      // +0xf9c  queue write cursor
    int      field_fa0;      // +0xfa0  queue read cursor
    uint32_t mCurrent;       // +0xfa4
    uint32_t mPending;       // +0xfa8
    uint8_t  field_fac;      // +0xfac
    char     pad_fad[3];
    float    field_fb0;      // +0xfb0
    float    field_fb4;      // +0xfb4
    char     pad_fb8[4];
    CreatureInst* field_fbc;  // +0xfbc

    int      Count();
    int      FindFreeSlot();            // FUN_009ff380
    void     TransitionToNextAnimation();  // FUN_009ff440
    void     UpdateGoals(float dt, char param_3);
    int      QueuedToActive();
};
// ---- items of slice s009feb30 end

// ---- items of slice s009ffa00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_defaultA;         // 0x01550b78
extern float g_defaultB;         // 0x01550b74
extern "C" int   __cdecl FUN_009a4550(void* a, void* b);                 // 0x009a4550
extern "C" void  __cdecl FUN_009a3680(int a, int key);                   // 0x009a3680
struct GoalObj {                 // refcounted payload of AnimGoal::field_00
    char    pad_00[0xad];
    char    field_ad;
    char    pad_ae[0x0a];
    double  field_b8;
    void AddRef();               // 0x0099c970
    void Release();              // 0x009a3630
    void FUN_009a3080(int a);    // 0x009a3080
    void FUN_009a3220(int a, void* b, int c);   // 0x009a3220
    GoalObj* FUN_009a34a0();     // 0x009a34a0 (ctor)
};
struct GoalObj2 {                // refcounted payload of AnimGoal::field_04
    void AddRef();               // 0x009ac2a0
    void Release();              // 0x009ae1c0
};
struct TmpObj { void FUN_0099f0b0(); };       // 0x0099f0b0
struct CreatureInst_s009f_fa00 {
    char pad[0x0];
    void Release();              // 0x009c4cc0 (nSPCreatureAnim::creature_instance_data::Release)
    void AddRef();               // 0x00a17060
};
struct ChildSlot { int id; float a; float b; };
struct AnimGoal_s009f_fa00;
struct GoalPool {                // eastl::vector<GoalObj*> of recycled objects
    GoalObj** begin;
    GoalObj** end;
    GoalObj** cap;
    void FUN_009ab170(GoalObj** where, AnimGoal_s009f_fa00* src);   // 0x009ab170 (thiscall)
};
extern GoalPool* g_goalPool;     // 0x0166c064
extern "C" void  __cdecl FUN_009a1ad0(GoalObj* p);                       // 0x009a1ad0
extern "C" GoalObj* __cdecl FUN_009a37a0_s009f_fa00(int key);                       // 0x009a37a0
extern "C" char  __cdecl FUN_009a38f0(void* a, int key, TmpObj** out);   // 0x009a38f0
struct AnimGoal_s009f_fa00 {
    GoalObj*  field_00;      // +0x00
    GoalObj2* field_04;      // +0x04
    int       mChildren[24]; // +0x08
    int       mChildCount;   // +0x68
    int       field_6c;      // +0x6c
    float     field_70;
    float     field_74;
    float     field_78;
    uint8_t   field_7c;
    char      pad_7d[3];
    int       field_80;
    uint8_t   field_84;
    char      pad_85[3];
    float     field_88;
    float     field_8c;
    float     field_90;
    float     field_94;
    float     field_98;
    uint8_t   field_9c;
    uint8_t   field_9d;
    char      pad_9e[2];
    float     field_a0;
    char      pad_a4[4];
    double    field_a8;
    int       field_b0;
    int       field_b4;
    float     field_b8;
    int       field_bc;
    int       field_c0;
    float     field_c4;
    float     field_c8;
    float     field_cc;
    float     field_d0;
    uint8_t   field_d4;
    char      pad_d5[3];
    int       field_d8;
    int       field_dc;
    int       field_e0;
    int       field_e4;
    int       field_e8;
    int       field_ec;

    AnimGoal_s009f_fa00* operator=(AnimGoal_s009f_fa00* o);   // 0x009ffb50 (thiscall, ret 4)
    void Reset();                       // 0x00a00490
    void Stop(char a, char b);          // 0x00a00670
    void FUN_009aa4c0(GoalObj** src);   // 0x009aa4c0
};
struct QueuedBlender_s009f_fa00 {
    uint32_t     mSeq;               // +0x000
    uint32_t     pad_04;
    AnimGoal_s009f_fa00     mGoals[16];         // +0x008, stride 0xf0
    uint32_t     field_f08;          // +0xf08
    uint32_t     mActive[16];        // +0xf0c
    uint32_t     mQueue[16];         // +0xf4c
    char         pad_f8c[0x10];
    int          field_f9c;          // +0xf9c
    int          field_fa0;          // +0xfa0
    uint32_t     mCurrent;           // +0xfa4
    uint32_t     mPending;           // +0xfa8
    uint8_t      field_fac;          // +0xfac
    char         pad_fad[3];
    float        field_fb0;          // +0xfb0
    float        field_fb4;          // +0xfb4
    float        field_fb8;          // +0xfb8
    CreatureInst_s009f_fa00* field_fbc;         // +0xfbc
    int          field_fc0;          // +0xfc0
    float        field_fc4;          // +0xfc4
    float        field_fc8;          // +0xfc8
    uint8_t      field_fcc;          // +0xfcc

    void ResetAll(char full);                      // 0x00a007d0
    void SetCreature(CreatureInst_s009f_fa00* c, int v);      // 0x00a00910
    void ClearPendingGoal();                       // 0x00a008b0
    void SelectPending(uint32_t handle);           // 0x00a006f0
};
struct GoalPair { AnimGoal_s009f_fa00* first; AnimGoal_s009f_fa00* second; };
// ---- items of slice s009ffa00 end

// ---- items of slice s00a00980 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct QueuedBlender_s00a0_0980;
struct AnimCommand {
    void*         mAnim;            // +0x00
    void*         mAnimBaked;       // +0x04
    uint          mDeferred[8][3];  // +0x08 .. +0x68 (8 ids * 0xc)
    uint          mDeferredIdx;     // +0x68
    uint          mLinkedHandle;    // +0x6c
    float         mDurationOverride;// +0x70
    uint          mHandle;          // +0x74
    float         mDelay;           // +0x78
    uint          mPad7c;           // +0x7c
    uint          mPad80;           // +0x80
    bool          mFlag84;          // +0x84
    char          mPad85[3];        // +0x85
    float         mCursor;          // +0x88
    uint          mPad8c;           // +0x8c
    uint          mPad90;           // +0x90
    uint          mPad94;           // +0x94
    float         mWeight98;        // +0x98
    uint          mPad9c;           // +0x9c
    float         mA0;              // +0xa0
    uint          mPadA4[3];        // +0xa4 .. +0xb0
    uint          mSeq;             // +0xb0
    uint          mSeqGen;          // +0xb4
    float         mBakeScale;       // +0xb8
    uint          mAnimId;          // +0xbc
    uint          mStatus;          // +0xc0
    float         mTransition;      // +0xc4
    int           mEnabled;         // +0xc8
    uint          mPadCC;           // +0xcc
    float         mWeightD0;        // +0xd0
    bool          mActiveD4;        // +0xd4
    char          mPadD5[7];        // +0xd5 .. +0xdc
    int           mCb1;             // +0xdc callback fn ptr
    uint          mCb1a;            // +0xe0
    uint          mCb1b;            // +0xe4
    int           mCb2;             // +0xe8 callback fn ptr
    uint          mCb2a;            // +0xec
};
struct QueuedBlender_s00a0_0980 {
    uint        mSeq;               // +0x000
    uint        mPad04;             // +0x004
    AnimCommand mCommands[16];      // +0x008 (0xf0 each)
    uint        mCommandsTail;      // +0xf08
    uint        mActive[16];        // +0xf0c
    uint        mQueued[16];        // +0xf4c
    bool        mNewlyActivated[16];// +0xf8c
    uint        mQueueTail;         // +0xf9c
    uint        mQueueHead;         // +0xfa0
    uint        mPrimary;           // +0xfa4
    uint        mDefault;           // +0xfa8
    bool        mFlagFac;           // +0xfac
    char        mPadFad[3];         // +0xfad
    uint        mPadFb0;            // +0xfb0
    uint        mPadFb4;            // +0xfb4
    float       mEaseTime;          // +0xfb8
    void*       mCreature;          // +0xfbc
    void*       mBakedMgr;          // +0xfc0
    uint        mPadFc4;            // +0xfc4
    uint        mPadFc8;            // +0xfc8
    bool        mFlagFcc;           // +0xfcc

    void ClearQueued();                          // 00a00980 0x00a00980
    void FUN_00a00c40(uint param);               // 00a00c40 0x00a00c40
    void Activate(uint idx, char force);         // 00a00d50
    void Deactivate(uint idx);                   // 00a00f10
    void FUN_00a00f90(AnimCommand* cmd, uint x); // 00a00f90
    void FUN_00a01050(uint x);                   // 00a01050 0x00a01050
    void UpdateCreatureBodies(uint a2, float a3, float a4, uint a5,
                              uint a6, uint a7, float a8); // 00a010c0
};
struct XC {
    void  FUN_00a00490();
    void* FUN_009a34a0();
    void  FUN_0099c970();
    void  FUN_009a3630();
    void  FUN_009ae1c0();
    void  FUN_009a3220(uint, uint, uint);
    void  FUN_009fee90();
    void  FUN_00a00670(bool, int);
    void  FUN_009ff440();
    uint  FUN_009ff380();
    uint  FUN_009ff040();
    uint  FUN_009aa8a0(uint, uint, uint);
    void  FUN_009abe90(uint, uint, uint, uint);
    void  FUN_009a9b90(uint);
    void  FUN_00a008b0();
    void  FUN_009b9090();
    float FUN_009ac2b0(float, float, int, uint);
    float FUN_009afe90(float);
    void  FUN_009ffb50();
};
void  __cdecl FUN_009a2cc0(uint, uint);
// ---- items of slice s00a00980 end

// ---- items of slice s00a027a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
bool   __stdcall IsOrientStopAnim(uint32 id);                 // 0x00a02740
void*  __cdecl   FindSlot(void* table, uint32 v);             // 0x009ff6f0
void*  __cdecl   RootSlot(void* table);                       // 0x009ff750
bool   __cdecl   QuerySlotA(void* table, int v, int flags);   // 0x009ff7c0
int    __cdecl   QuerySlotB(void* table, int v);              // 0x009ff7a0
uint32 __cdecl   PackHandle(uint32 v, uint8 idx);             // 0x009fef70
void   __cdecl   Forward3(void* table, int a, int b, int c);  // 0x00a00180
void   __cdecl   BigForward(int, int, int, int, int, int);    // 0x009b2340
struct Node {                                                 // 0xf0 bytes, table+8
    char   pad0[0xb4];
    uint32 value;                                             // +0xb4
    char   pad1[0xd8 - 0xb8];
    uint32 id;                                                // +0xd8
    char   pad2[0xf0 - 0xdc];
};
struct HandleTable {
    char   pad0[8];
    Node   nodes[16];                                         // +0x008
    char   pad1[0xf0c - 0xf08];
    uint32 tbl[16];                                           // +0x00f0c
    char   pad2[0xf8c - 0xf4c];
    uint8  live[16];                                          // +0x00f8c

    void __thiscall Detach(void* p, int flags);               // 0x00a00f90
    void __thiscall Remove(int v);                            // 0x00a01050
};
struct cAnimatingCreature_s00a0_27a0 {
    char          pad00[0x38];
    uint8         f38;                                        // +0x038
    char          pad39[3];
    int           f3c;                                        // +0x03c
    int           f40;                                        // +0x040
    char          pad44[4];
    uint8         f48;                                        // +0x048
    char          pad49[7];
    int           sel50[2];                                   // +0x050 / +0x054
    char          pad58[0x154 - 0x58];
    int           f154;                                       // +0x154
    char          pad158[0x164 - 0x158];
    int           f164;                                       // +0x164
    int           f168;                                       // +0x168
    int           f16c;                                       // +0x16c
    char          pad170[0x184 - 0x170];
    HandleTable*  table;                                      // +0x184
    uint32        f188;                                       // +0x188

    void __thiscall Forward(int a, int b, int c);             // 0x00a02a00
    bool __thiscall Attach(int v);                            // 0x00a02ab0
    bool __thiscall Detach(int v);                            // 0x00a02b00
    bool __thiscall QueryA(int v);                            // 0x00a02b40
    bool __thiscall QueryB(int v);                            // 0x00a02b70
    int  __thiscall Selector();                               // 0x00a02bd0
    void __thiscall SetMode(const int* v, uint8 b);           // 0x00a02bf0
    void __thiscall SetRestIdleAnimHandle();                  // 0x00a02c40
    uint8 __thiscall Swap48(uint8 v);                         // 0x00a02cd0
    void __thiscall Set38(uint8 a, int b, int c);             // 0x00a02ce0
    void __thiscall SetSel(int i, int v);                     // 0x00a02d00
};
struct RootThunk { void* __thiscall RootOnly(void* p); };
// ---- items of slice s00a027a0 end

// ---- items of slice s00a04d20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_maxFloat;    // 0x01448a84 = FLT_MAX
extern float g_two;         // 0x01470f1c = 2.0f
extern float g_one;         // 0x01485720 = 1.0f
extern float g_tiny;        // 0x01551a8c = 0.001f
extern float g_piOver2;     // 0x01447a08 = 1.5707964f
extern int   g_thingFlag;   // 0x01551a7c (nonzero => a global object exists)
extern uint8_t g_thingData; // 0x01551a68
double __cdecl FUN_011e08f0(double v);   // 0x011e08f0 (x87 pow helper, cdecl)
struct Vector4 {
    float x, y, z, w;
};
struct BodyShapeEntry {
    uint32_t f00;
    uint32_t f04;
    uint32_t f08;
    uint32_t f0c;
    float    off[3];        // +0x10 local offset of this sub-shape
    float    pad1c[0x2bc - 0x1c];
};
struct RigidBody {
    uint8_t  pad00[0x18];
    float    pos[3];        // +0x18 world position
    uint8_t  pad24[0x3c - 0x24];
    float    quat[4];       // +0x3c w,x,y,z
    uint8_t  pad4c[0x2e0 - 0x4c];
    uint8_t  dirtyFlag;     // +0x2e0
    uint8_t  pad2e1[0x2e4 - 0x2e1];
    BodyShapeEntry* begin;  // +0x2e4
    BodyShapeEntry* end;    // +0x2e8
};
struct AnimGoalInfo;
struct queued_blender;
struct CreatureStaticData {
    long AddRef() const;    // 0x009b3450
    long Release() const;   // 0x009c26a0
};
struct StaticDataSlot {
    CreatureStaticData* p;              // +0x00
    void** SwapStaticData(CreatureStaticData** src);   // 0x00a056f0
};
struct AnimGoalInfo {
    AnimGoalInfo* p0;       // +0x00 (a goal pointer whose target we touch)
    uint8_t  pad04[0x10 - 0x04];
    float    local10;       // +0x10
    float    local14;       // +0x14
    float    local18;       // +0x18
    uint8_t  pad1c[0x6c - 0x1c];
    uint32_t flag6c;        // +0x6c (00a051c0 tests this)
    uint8_t  pad70[0xa8 - 0x70];
    double   timeA8;        // +0xa8
    uint32_t fB0;           // +0xb0
    double   vB8;           // +0xb8 (double)
    uint32_t zeroC0;        // +0xc0
    uint8_t  padC4[0xd8 - 0xc4];
    uint32_t fD8;           // +0xd8
};
struct AnimViewer {
    void**   vtbl;          // +0x00
    uint8_t  pad04[0x20 - 0x04];
    uint32_t region;        // +0x20
};
struct cAnimatingCreature_s00a0_4d20 {
    void**   vtbl;              // +0x000
    uint8_t  pad004[0x178 - 0x04];
    uint32_t mWorldRegion;      // +0x178
    RigidBody* mRegionObj;      // +0x17c (body / object; +0x2e0 flag)
    uint8_t  pad180[0x184 - 0x180];
    queued_blender* mBlender;   // +0x184
    uint32_t mCurGoal;          // +0x188
    uint32_t mPrevGoal;         // +0x18c
    AnimViewer* mViewer;        // +0x190
    uint8_t  pad194[0x198 - 0x194];
    int32_t  mRefCount;         // +0x198
    uint8_t  pad19c[0x1d8 - 0x19c];
    uint8_t  mFlag1d8;          // +0x1d8

    bool  ClosestBodyPosition(const Vector3& query, Vector3& out); // 0x00a04d20
    void  GetCurrentAnimation(uint32_t* outIdx, float* outTime, int* outValue, int* outFlags); // 0x00a05150
    bool  GetGoalTimes(uint32_t handle, float* outTime, float* outValue);      // 0x00a051c0
    void  MarkWorldRegion(bool force);                                         // 0x00a05220
    int   Release();                                                           // 0x00a05270
    void  UpdateGoalFade();                                                    // 0x00a05360
    void  ApplyAnimState(uint32_t mode);                                       // 0x00a05a70
};
struct WrappedAnim {
    void**   vtbl;          // +0x00
    uint8_t  pad04[0x1c - 0x04];
    void*    mOwner;        // +0x1c (its +0x50 is a property interface)
    uint8_t  pad20[0x44 - 0x20];
    void*    mAttachments;  // +0x44
    uint8_t  f48;           // +0x48
    uint8_t  pad49[0x5c - 0x49];
    uint32_t mCount0;       // +0x5c
    uint32_t mCount1;       // +0x60
    uint32_t mChosen;       // +0x64
    uint8_t  pad68[0x3038 - 0x68];
    uint8_t  mFlag3038;     // +0x3038
    uint8_t  mFlag3039;     // +0x3039
    uint8_t  mFlag303a;     // +0x303a

    char SetFlagFromProperty(bool value);   // 0x00a054a0
    bool InitThing(void* attachments, uint8_t a, uint32_t b, uint8_t c, uint8_t d); // 0x00a05510
};
struct AnimPimpl {
    void**   vtbl;      // +0x00
    void*    impl;      // +0x04

    int GetStateA();                    // 0x00a055a0
    int GetStateB(int a1, int a2);      // 0x00a055c0
    int GetStateC(int a1, int a2);      // 0x00a055e0
    int GetStateD();                    // 0x00a05610
};
struct GoalList {
    uint8_t  pad00[0x50];
    int      mSlots[8];     // +0x50
    int      mCounts[8];    // +0x5c .. overlaps; classic overlapping-array trick

    int SelectFor(void* owner, int index, char useIndex); // 0x00a05660
};
struct var_t {
    void*    value;     // +0x00
    uint8_t  pad04[0x0c];
    uint16_t flags;     // +0x10
    uint16_t type;      // +0x12
};
void   FUN_009bd340(RigidBody* o);                              // 0x009bd340
float  FUN_009d3530(void* o);                                   // 0x009d3530
void   FUN_009b3920(const float* a, const float* b);            // 0x009b3920 Set@TargetFrame
AnimGoalInfo* FUN_009ff750_s00a0_4d20(queued_blender* b);                  // 0x009ff750
AnimGoalInfo* FUN_009ff6f0_s00a0_4d20(queued_blender* b, uint handle);     // 0x009ff6f0
int    FUN_009fef90(queued_blender* b, AnimGoalInfo* g);        // 0x009fef90
void   FUN_009fef50(AnimGoalInfo* g, float v);                  // 0x009fef50 (ret 4)
void   FUN_009fef20(AnimGoalInfo* b, AnimGoalInfo* g);          // 0x009fef20
void   FUN_009edb70(Vector4* out, const float* a, const float* b, uint32_t p4, uint32_t p5); // 0x009edb70
void   FUN_00c373d0();                                          // 0x00c373d0
void*  SP_PropertyManager();                                    // 0x0067de30
bool   SP_GetPropertyAsUint32Array(void* a, uint32_t k, uint32_t** out, uint32_t* count); // 0x006a0840
void*  Sim_GetPoliticalID(void* gameData);                      // 0x0097e850
void   Variant_SetU32(var_t* v, uint32_t value);                // 0x00422eb0
void   Variant_Destruct(var_t* v, bool b);                      // 0x0093db80
void   FUN_00a02d80(void* p);                                   // 0x00a02d80
float AnimProgress(void* animObj);
struct RBTreeHead {
    uint8_t  pad00[0xc];
    char*    root;      // +0x0c

    void* FindLower(void** outNode, uint32_t* key);   // 0x00a05730
    void* FindRaw(void** outNode, uint32_t* key);     // 0x00a057f0
};
struct CallbackPair {
    uint8_t  pad00[0x20];
    void*    arg;       // +0x20
    void*    fn;        // +0x24

    bool SetCallbackPair(void* newObj);   // 0x00a057a0
};
struct Vec28 {
    void*  begin;       // +0x00
    void*  end;         // +0x04
    void*  cap;         // +0x08

    Vec28* Construct(int count, int unused);   // 0x00a05830
};
// ---- items of slice s00a04d20 end

// ---- items of slice s00a05c20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* const s_animCreatureVtbl[];
extern uint32_t* g_feedbackTime;        // 0x0166cc08 (+0x14 holds the time stamp)
extern float g_variantFloatDefault;     // 0x015d1168
extern uint32_t g_variantUintDefault;   // 0x015d9c68
extern uint8_t  g_variantBoolDefault;   // 0x015d9c70
extern float    g_f1;                   // 0x015518e0..ec (1.0f x4) -- four separate slots
extern float    g_f2;
extern float    g_f3;
extern float    g_f4;
extern const float g_half;              // 0x01471064
extern const float g_zero;              // 0x01485378
struct Vector3_s00a0_5c20 {
    float x, y, z;
    Vector3_s00a0_5c20() {}
    Vector3_s00a0_5c20(const Vector3_s00a0_5c20& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3_s00a0_5c20& operator=(const Vector3_s00a0_5c20& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Vector4_s00a0_5c20 {
    float x, y, z, w;
    Vector4_s00a0_5c20() {}
    Vector4_s00a0_5c20(const Vector4_s00a0_5c20& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
    Vector4_s00a0_5c20& operator=(const Vector4_s00a0_5c20& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
};
struct BoundingBox {
    Vector3_s00a0_5c20 mn;                         // +0x00
    Vector3_s00a0_5c20 mx;                         // +0x0c
    void Reset();                       // 0x00409c00 (thiscall, ret 0)
    void Extend(const Vector3_s00a0_5c20& v);      // 0x0041bd50 (thiscall, ret 4)
};
struct anim_creature_s00a0_5c20;
struct queued_blender_s00a0_5c20;
struct creature_instance_data_s00a0_5c20;
struct RefObj_s00a0_5c20 {                         // resource object returned by the creator vtable
    uint32_t pad00;                     // +0x00
    uint32_t flags;                     // +0x04
    uint32_t pad08[0x38 / 4];           // +0x08 .. +0x3f
    uint32_t refcount;                  // +0x40
    uint32_t pad44[(0x6c - 0x44) / 4];  // +0x44 .. +0x6b
    float    f6c;                       // +0x6c
    BoundingBox box;                    // +0x70
};
struct Creator {
    virtual RefObj_s00a0_5c20* slot0();
    virtual RefObj_s00a0_5c20* slot1();
    virtual RefObj_s00a0_5c20* slot2();
    virtual RefObj_s00a0_5c20* Create(uint32_t a, uint32_t b, uint32_t c);   // vtable slot 3 (vtbl+0xc)
};
struct AnimData {                       // *(creature_instance_data + 0)
    uint8_t pad[0x358];
    float   minx, miny, minz;           // +0x358
    float   sizeX, sizeY, sizeZ;        // +0x364
    float   f370;                       // +0x370
};
struct creature_instance_data_s00a0_5c20 {
    void*    field0;                    // +0x000
    uint32_t pad04[(0x2c0 / 4) - 1];    // +0x004
    void*    model;                     // +0x2c0
};
struct queued_blender_s00a0_5c20 {
    void SetBakeParam(float dt, bool first);                                                    // 0x009ff4b0 (ret 8)
    void UpdateCreatureBodies(uint a1, float a2, float a3, uint a4, uint a5, uint a6, float a7); // 0x00a010c0 (ret 0x1c)
};
struct anim_creature_s00a0_5c20 {                  // 0x19c bytes
    void*    vtbl;                      // +0x00 (set explicitly by the ctor)

    Vector3_s00a0_5c20  mPos;                      // +0x04
    Vector4_s00a0_5c20  mRot;                      // +0x10
    uint32_t pad20[7];                  // +0x20 .. +0x3b
    float    f3c;                       // +0x3c
    float    f40, f44, f48, f4c;        // +0x40 .. +0x4c
    uint32_t f50;                       // +0x50
    uint32_t f54;                       // +0x54
    uint32_t f58;                       // +0x58
    uint32_t pad5c;                     // +0x5c
    uint32_t f60;                       // +0x60
    uint8_t  f64;                       // +0x64
    uint8_t  pad65[3];
    float    slots[7];                  // +0x68 .. +0x83
    uint8_t  f84;                       // +0x84
    uint8_t  pad85[3];
    uint32_t f88;                       // +0x88
    struct { int32_t a, b; uint32_t c; } arr8c[16];  // +0x8c .. +0x14b
    uint32_t f14c;                      // +0x14c
    uint8_t  f150;                      // +0x150
    uint8_t  f151;                      // +0x151
    uint8_t  pad152[2];
    uint32_t f154;                      // +0x154
    uint32_t f158;                      // +0x158
    anim_creature_s00a0_5c20* f15c;                // +0x15c
    uint32_t f160;                      // +0x160
    float    f164;                      // +0x164
    float    f168;                      // +0x168
    float    f16c;                      // +0x16c
    uint32_t f170;                      // +0x170
    int32_t  f174;                      // +0x174
    uint32_t f178;                      // +0x178
    creature_instance_data_s00a0_5c20* instance;   // +0x17c
    RefObj_s00a0_5c20*  f180;                      // +0x180
    queued_blender_s00a0_5c20* blender;            // +0x184
    uint32_t f188;                      // +0x188
    uint32_t f18c;                      // +0x18c
    void*    world;                     // +0x190
    uint32_t f194;                      // +0x194
    int32_t  f198;                      // +0x198

    anim_creature_s00a0_5c20(const Vector3_s00a0_5c20& pos, const Vector4_s00a0_5c20& rot);   // 0x00a05d60 (ret 8)

    void  Release();                                          // 0x00a05270
    void  SetTargetRoot(anim_creature_s00a0_5c20* target);               // 0x00a06250
    void  SetTargetBody(anim_creature_s00a0_5c20* target, uint value);   // 0x00a062a0
    float GetFeedbackValue(uint key);                         // 0x00a060a0
};
void __cdecl RegisterCreature(anim_creature_s00a0_5c20* ac);   // 0x00a05c20
void __cdecl UpdateBakeTarget(anim_creature_s00a0_5c20* ac, uint value, bool b);   // 0x00a04630
struct FeedbackRecord {                 // 0x1c bytes
    float    f0;
    float    f4;
    uint32_t f8;
    uint32_t fC;
    uint32_t f10;
    uint32_t f14;
    uint32_t f18;
};
struct FeedbackEvent {                  // 0x18 bytes
    FeedbackRecord* begin;              // +0x00
    FeedbackRecord* end;                // +0x04
    uint32_t f08, f0c, f10;             // +0x08
    float    time;                      // +0x14
};
struct FeedbackNode {
    uint32_t        pad00[0x10];        // +0x00 .. +0x3f
    FeedbackEvent*  begin;              // +0x40
    FeedbackEvent*  end;                // +0x44
};
struct FeedbackTree {                   // rbtree<unsigned, ...>
    void find(FeedbackNode** pResult, const uint* key);   // 0x00e5c780 (ret 8)
};
extern FeedbackTree g_feedbackTree;     // 0x01551a68
extern FeedbackNode g_feedbackEnd;      // 0x01551a6c (end sentinel node)
struct OutRec {                         // feedback output record (3 dwords)
    int32_t z;
    float   y;
    float   x;
};
struct Rng {
    double GenerateDouble();            // 0x009362d0 (ret 0)
};
extern Rng g_rng;                       // 0x0166cd30
bool  __cdecl LookupA(void* data, uint key, void** pOut);           // 0x009a38f0
void* __cdecl LookupB(void* a, uint key, void* c);                  // 0x009a4430
uint  __cdecl LookupC(void* data, void* o);                         // 0x009a4550
struct XC_s00a0_5c20 {                             // object helpers (Prepare / Release)
    void  Prepare();                                            // 0x0099c660
    void  Release();                                            // 0x0099d060
    uint32_t pad[0x11c / 4];
    float f11c;                                                 // +0x11c
    float f120;                                                 // +0x120
};
struct FbHandle {                       // object looked up into `p`
    void Release();                                             // 0x0099f0b0
};
struct Variant {                        // 0x14 bytes
    void*    mValue;                    // +0x00
    uint32_t pad04[3];                  // +0x04 .. +0x0f
    uint16_t mFlags;                    // +0x10
    uint16_t mType;                     // +0x12
    void Destruct(bool b);              // 0x0093db80 (thiscall, ret 4)
};
struct PropHolder {                     // property bag at mManager + 0x50
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
    virtual Variant* GetProperty(uint32_t id);          // slot 10 (vtbl+0x28)
};
struct cViewer_s00a0_5c20 {
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
virtual void c5();
virtual void c6();
virtual void c7();
virtual void c8();
virtual void c9();
virtual void c10();
virtual void c11();
    virtual void* c12(uint32_t a);                      // slot 12 (vtbl+0x30)

    void GetCameraLocationInfo(Vector3_s00a0_5c20* out, int a, int b, int c);   // 0x007c3d30 (ret 0x10)
};
struct AnimWorld_s00a0_5c20 {
virtual void w0();
virtual void w1();
virtual void w2();
virtual void w3();
virtual void w4();
virtual void w5();
virtual void w6();
virtual void w7();
virtual void w8();
virtual void w9();
virtual void w10();
virtual void w11();
virtual void w12();
virtual void w13();
virtual void w14();
virtual void w15();
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
    virtual void w20();
    virtual uint w21(uint a, float b);                  // slot 21 (vtbl+0x54)

    uint32_t pad04[6];                  // +0x04 .. +0x1b
    void*    mManager;                  // +0x1c
    uint32_t mSeq;                      // +0x20
    anim_creature_s00a0_5c20** mpBegin;            // +0x24
    anim_creature_s00a0_5c20** mpEnd;              // +0x28
    uint32_t pad2c[8];                  // +0x2c .. +0x4b
    void*    mEffectsWorld;             // +0x4c
    uint8_t  pad50[0x3038 - 0x50];      // +0x50 .. +0x3037
    uint8_t  mAutoBaking;               // +0x3038

    void UpdateAutoBaking(float dt, cViewer_s00a0_5c20* viewer);   // 0x00a06310 (ret 8)
};
struct VariantBuilder {
    void SetU32(uint32_t* pValue);      // 0x00422eb0 (thiscall, ret 4)
};
extern const float g_one_s00a0_5c20;               // 0x01485720
cViewer_s00a0_5c20* __cdecl GetViewer();           // 0x0067dd50
// ---- items of slice s00a05c20 end

// ---- items of slice s00a06600 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace checkerlib {
class vector_3_s00a0_6600 { public: float x, y, z; };
}
namespace checkerlib {
class vector_4_s00a0_6600 { public: float x, y, z, w; };
}
namespace nSPCreatureAnim {
struct creature_instance_data_s00a0_6600;
}
namespace nSPCreatureAnim {
struct pose_bone {
    uint32_t pad_000;                    // +0x000
    checkerlib::vector_3_s00a0_6600 position;                   // +0x004
    checkerlib::vector_4_s00a0_6600 orientation;                // +0x010 (x, y, z, w)
    checkerlib::vector_3_s00a0_6600 cached_axis;                // +0x020 (creature +0x160)
    checkerlib::vector_4_s00a0_6600 cached_orientation;         // +0x02c (creature +0x170)
    uint8_t  pad_03c[0x64 - 0x3c];       // +0x03c
    uint8_t  enabled;                    // +0x064
    uint8_t  pad_065[0x17c - 0x065];     // +0x065
    creature_instance_data_s00a0_6600* creature;    // +0x17c
};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s00a0_6600 {
    uint32_t pad_000[0x10 / 4];          // +0x000
    uint8_t  flags_010;                  // +0x010 (low 5 bits: orientation already unit)
    uint8_t  pad_011[0x18 - 0x11];       // +0x011
    checkerlib::vector_3_s00a0_6600 position;                   // +0x018
    uint32_t pad_024[(0x030 - 0x24) / 4];// +0x024
    float    f_030;                      // +0x030
    float    f_034;                      // +0x034
    float    f_038;                      // +0x038
    checkerlib::vector_4_s00a0_6600 orientation;                // +0x03c (x, y, z, w)
    uint32_t pad_04c[(0x05c - 0x4c) / 4];// +0x04c
    checkerlib::vector_4_s00a0_6600 q_05c;                      // +0x05c (x, y, z, w)
    uint32_t pad_06c[(0x118 - 0x6c) / 4];// +0x06c
    checkerlib::vector_3_s00a0_6600 v_118;                      // +0x118 (rotation axis * angle, unscaled)
    uint32_t pad_124;                    // +0x124
    float    f_128;                      // +0x128
    float    f_12c;                      // +0x12c
    float    f_130;                      // +0x130
    float    f_134;                      // +0x134
    uint32_t pad_138[(0x160 - 0x138) / 4];// +0x138 (extent lives here, see s009bfc20)
    checkerlib::vector_3_s00a0_6600 v_160;                      // +0x160 (rotation axis * angle, scaled)
    uint32_t pad_16c;                    // +0x16c
    checkerlib::vector_4_s00a0_6600 q_170;                      // +0x170 (x, y, z, w)

    float GetGroundHeight(const checkerlib::vector_3_s00a0_6600* pos, checkerlib::vector_3_s00a0_6600* normal);   // 0x009b6220
    checkerlib::vector_3_s00a0_6600* GetGroundUp(checkerlib::vector_3_s00a0_6600* out, const checkerlib::vector_3_s00a0_6600* pos);      // 0x009b62c0
};
}
namespace nSPCreatureAnim {
struct pose_bone_set {
    void**   vtable;                     // +0x000
    uint32_t pad_004[(0x24 - 0x04) / 4]; // +0x004
    pose_bone** bone_begin;              // +0x024
    pose_bone** bone_end;                // +0x028

    void Refresh(float elapsed, int mode);
};
}
namespace nSPCreatureAnim {
typedef void (__thiscall* pose_set_notify)(pose_bone_set* set, float elapsed, int mode);
}
static __forceinline checkerlib::vector_3_s00a0_6600 InvRotate(const checkerlib::vector_4_s00a0_6600& q, const checkerlib::vector_3_s00a0_6600& v,
                                        const checkerlib::vector_3_s00a0_6600& add)
{
    checkerlib::vector_3_s00a0_6600 r;
    r.x = ((-(q.z * q.z) + -(q.y * q.y)) * v.x + (q.z * q.x + q.y * q.w) * v.z +
           (q.y * q.x - q.z * q.w) * v.y) * 2.0f + v.x + add.x;
    r.y = ((-(q.z * q.z) + -(q.x * q.x)) * v.y + (q.z * q.y - q.x * q.w) * v.z +
           (q.y * q.x + q.z * q.w) * v.x) * 2.0f + v.y + add.y;
    r.z = ((-(q.y * q.y) + -(q.x * q.x)) * v.z + (q.z * q.x - q.y * q.w) * v.x +
           (q.z * q.y + q.x * q.w) * v.y) * 2.0f + v.z + add.z;
    return r;
}
// ---- items of slice s00a06600 end

// ---- items of slice s00a07ae0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int      g_fbCount;           // 0x01551a7c
extern void* RBTreeIncrement(void* node);            // 0x00921580
extern float    g_f1550b84;          // 0x01550b84
typedef unsigned long long uint64;
struct V12 {                            // virtual slots 0x00 .. 0x2c
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
virtual void a8();
virtual void a9();
virtual void a10();
virtual void a11();
};
struct V13 {                            // virtual slots 0x00 .. 0x30
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
virtual void c5();
virtual void c6();
virtual void c7();
virtual void c8();
virtual void c9();
virtual void c10();
virtual void c11();
    virtual void c12();
};
struct V37 {                            // virtual slots 0x00 .. 0x90
virtual void d0();
virtual void d1();
virtual void d2();
virtual void d3();
virtual void d4();
virtual void d5();
virtual void d6();
virtual void d7();
virtual void d8();
virtual void d9();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
virtual void d14();
virtual void d15();
virtual void d16();
virtual void d17();
virtual void d18();
virtual void d19();
virtual void d20();
virtual void d21();
virtual void d22();
virtual void d23();
virtual void d24();
virtual void d25();
virtual void d26();
virtual void d27();
virtual void d28();
virtual void d29();
virtual void d30();
virtual void d31();
virtual void d32();
virtual void d33();
virtual void d34();
virtual void d35();
    virtual void d36();
};
struct Host : V37 {
    virtual int  h37(void*);            // 0x94
    virtual void h38();                 // 0x98
    virtual int  h39(void*);            // 0x9c
    virtual int  h40(void*);            // 0xa0
};
struct IStream {
    virtual void  s0();                                    // 0x00
    virtual void  s1();                                    // 0x04
    virtual void  s2();                                    // 0x08
    virtual void  s3();                                    // 0x0c
    virtual void  s4();                                    // 0x10
    virtual void  s5();                                    // 0x14
    virtual void* s6();                                    // 0x18
    virtual void  s7();                                    // 0x1c
    virtual void  s8();                                    // 0x20
    virtual void  s9();                                    // 0x24
    virtual void  s10();                                   // 0x28
    virtual void  s11();                                   // 0x2c
    virtual void  s12();                                   // 0x30
    virtual bool  s13(void*, void*, int, int, int, int);   // 0x34
    virtual void  s14(void*, int);                         // 0x38
};
struct ResMan : V13 {
virtual void  m13();
virtual void m14();
virtual void m15();
virtual void m16();
virtual void  m17();
virtual void m18();
virtual void m19();
virtual void m20();
    virtual void  m21();
    virtual void* m22(void*);                             // 0x58
};
struct ResObj : V13 {
    virtual void  o13(void*);                             // 0x34
virtual void  o14();
virtual void o15();
virtual void o16();
virtual void o17();
virtual void  o18();
virtual void o19();
virtual void o20();
virtual void o21();
virtual void  o22();
virtual void o23();
    virtual void* o24(void*, int);                        // 0x60
};
struct RespObj {
    virtual void  r0();
    virtual void  r1();
    virtual void  r2();                                   // 0x08
virtual void  r3();
virtual void r4();
virtual void r5();
    virtual void* r6();                                   // 0x18
virtual void  r7();
virtual void r8();
    virtual void  r9();                                   // 0x24
    virtual void  r10();
    virtual int   r11();                                  // 0x2c
    virtual int   r12(void*, int);                        // 0x30
};
struct WObj : V12 {
    virtual void* w12(void*);                             // 0x30
};
struct OutObj {                                          // job output object
virtual void o0();
virtual void o1();
virtual void o2();
};
struct TreeObj {                                         // eastl::rbtree anchor
    void* find(void** out, const void* key);             // 0x00e5c780
};
struct Job {                                             // SP::cJob-ish
    uint32_t pad00[8];                                   // +0x00 .. +0x1f
    OutObj*  out;                                        // +0x20
    int  ContinueJob();                                  // 0x0068f970 (thiscall)
    void Wait();                                         // 0x006926b0 (thiscall)
};
struct JobNode {                                         // node of the manager map
    uint32_t pad00[5];                                   // +0x00 .. +0x13
    Job*     job;                                        // +0x14
};
struct AnimInfo {                                        // *(cmd + 0xc)
    uint32_t pad00[3];                                   // +0x00 .. +0x0b
    int32_t  f0c;                                        // +0x0c
    uint32_t pad10[6];                                   // +0x10 .. +0x27
    uint8_t  b28, b29, b2a;
    uint8_t  pad2b;
    uint32_t f2c;                                        // +0x2c
    uint32_t f30;                                        // +0x30
    uint32_t f34;                                        // +0x34
    uint32_t f38;                                        // +0x38
    uint32_t f3c;                                        // +0x3c
    uint32_t f40;                                        // +0x40
    uint32_t f44;                                        // +0x44
};
struct CArgs {                                           // EA::ArgScript::cArguments
    int*         MainArguments(int n);                                    // 0x00838320
    const char** MainArguments(int* pCount, int a, int b);                // 0x00838020
};
struct Cmd {
    void*     f0;                                        // +0x00
    Host*     host;                                      // +0x04
    void*     f8;                                        // +0x08
    AnimInfo* data;                                      // +0x0c

    void Set0c(CArgs*);       // 0xa0 -> +0x0c
    void Set34(CArgs*);       // 0x9c -> +0x34
    void Set28(CArgs*);       // 0x94 -> +0x28
    void Set29(CArgs*);       // 0x94 -> +0x29
    void Set2a(CArgs*);       // 0x94 -> +0x2a
    void Mask2c(CArgs*);
    void Mask30(CArgs*);
};
struct Mgr {
    void* FbApplyFilter(const void* key, uint* filter);   // 0x00a07fc0
    Job*  FeedbackJob(uint key, char flag);    // 0x00a08090
    bool  SelectFeedbackRecord(uint key);      // 0x00a08110
    bool  WriteAnimList(IStream* s);           // 0x00a081b0
    bool  WriteAnimListFile(IStream* file);    // 0x00a08490
};
struct FbNode {
    uint32_t pad00[0x10];                                // +0x00 .. +0x3f
    uint8_t* evBegin;                                    // +0x40
    uint8_t* evEnd;                                      // +0x44
};
extern TreeObj  g_fbTree;            // 0x01551a68
extern FbNode   g_fbEnd;             // 0x01551a6c (end sentinel)
extern FbNode*  g_fbRoot;            // 0x01551a70
struct AnimRecord {                                      // 0x1c
    float     f0, f4;
    uint32_t  f8;
    uint16_t* v_c;                                       // +0x0c
    uint16_t* v_10;                                      // +0x10
    uint32_t  pad14, pad18;
};
struct AnimEvent {                                       // 0x18
    AnimRecord* begin;                                   // +0x00
    AnimRecord* end;                                     // +0x04
    uint32_t    pad08, pad0c, pad10;
    float       time;                                    // +0x14
};
struct AnimNode {
    uint32_t    pad00[5];                                // +0x00 .. +0x13
    int32_t     key;                                     // +0x14
    uint16_t*   seqBegin;                                // +0x18
    uint16_t*   seqEnd;                                  // +0x1c
    uint32_t    pad20, pad24;
    float       f28;                                     // +0x28
    float       f2c;                                     // +0x2c
    uint8_t     b30, b31, b32;
    uint8_t     pad33;
    uint32_t    d34, d38, d3c;                           // +0x34 / +0x38 / +0x3c
    AnimEvent*  evBegin;                                 // +0x40
    AnimEvent*  evEnd;                                   // +0x44
};
struct Vec14 {                                           // {u8* p0; u8* p4;}
    uint8_t* p0;                                         // +0x00
    uint8_t* p4;                                         // +0x04
};
struct Elem14 {                                          // 0x14
    uint8_t*  str;                                       // +0x00
    uint8_t*  strEnd;                                    // +0x04
    uint32_t  pad08, pad0c;
    uint32_t  f10;                                       // +0x10
};
struct Node3 {                                           // node value at +0x10
    uint32_t pad00[4];                                   // +0x00 .. +0x0f
    uint32_t a10;                                        // +0x10
    uint32_t a14;                                        // +0x14
    uint32_t a18;                                        // +0x18
};
struct NodeVec {                                         // node value {key; u32 vec}
    uint32_t  pad00[4];                                  // +0x00 .. +0x0f
    uint32_t  key;                                       // +0x10
    uint32_t* vecBegin;                                  // +0x14
    uint32_t* vecEnd;                                    // +0x18
};
struct Elem16 {                                          // 0x10
    uint32_t a0;
    float    f4, f8;
    uint32_t aC;
};
struct NodeVec16 {                                       // node value {key; Elem16 vec}
    uint32_t pad00[4];                                   // +0x00 .. +0x0f
    uint32_t key;                                        // +0x10
    Elem16*  vecBegin;                                   // +0x14
    Elem16*  vecEnd;                                     // +0x18
};
struct MapHead {                                         // {node* end@4; node* root@8; ... count@0x14}
    uint32_t pad00;
    uint8_t* end;                                        // +0x04
    uint8_t* root;                                       // +0x08
    uint32_t pad0c, pad10;
    uint32_t count;                                      // +0x14
};
extern Vec14*   g_p070;              // 0x0166c070
extern MapHead* g_p074;              // 0x0166c074
extern MapHead* g_p078;              // 0x0166c078
extern MapHead* g_p080;              // 0x0166c080
extern ResObj*  g_p166cc08;          // 0x0166cc08
void*   __cdecl GetManager();                                       // 0x0067dcd0
void    __cdecl GetTickCount100ns(uint64* out);                     // 0x0091ffd0
void*   __cdecl FUN_009a4430(int a, void* b, int c);                // 0x009a4430
void*   __cdecl ZoneObject_new(int size, const char* name, int, int, int, int);   // 0x00926020
void*   __cdecl EAAllocate(uint size, const char* name, int, int, int, int);      // 0x00f473a0
bool    __cdecl FUN_00a057a0(void* a, void* b);                     // 0x00a057a0
void*   __cdecl ReadAnimationStaticDataFromStreamWrapper(void*, void*, void*);    // 0x0099ed90
void*   __cdecl ReadGaitRecordStaticDataFromStreamWrapper(void*);   // 0x009e59b0
void*   __cdecl operator_new_arr(void* p, int a, int b);            // 0x011e073e
bool __cdecl WriteU32(IStream* s, void* p, int n, int a);           // 0x0093aa70
bool __cdecl StreamWrite(IStream* s, void* p, int n);               // 0x0093a9a0
bool __cdecl WriteCString(IStream* s, void* p, int n, int a);       // 0x0093adb0
struct Blob {
    uint32_t pad0;                                       // +0x00
    void*    obj;                                        // +0x04
    volatile long refs;                                  // +0x08
    uint32_t padc;                                       // +0x0c
    int32_t  f10;                                        // +0x10
    void* Init(void* a, const char* s);                  // 0x0093bca0 (thiscall)
};
struct GFAR {                                            // GraphicsFactoryAsyncRequest
    void* Cons(void* a, void* b, const char* s);         // 0x0093c270 (thiscall)
};
struct Slot {                                            // object at cmd+0x14
    void* v;                                             // +0x00
    void set(void* v);                                   // 0x0099ecb0 (thiscall)
};
struct SharedObj {                                       // blob payload
    virtual void sd0(int);
};
inline void BlobAddRef(Blob* b)
{
    if (b)
        _InterlockedIncrement(&b->refs);
}
inline void BlobRelease(Blob* b)
{
    if (!b)
        return;
    if (_InterlockedDecrement(&b->refs) == 0) {
        b->refs = 1;
        if (b->obj)
            ((SharedObj*)b->obj)->sd0(1);
    }
}
// ---- items of slice s00a07ae0 end

// ---- items of slice s00a08b00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_s_animID;             // 0x0155181c
extern void* g_s_animName;           // 0x01551820
extern void* g_s_duration;           // 0x01551824
extern void* g_s_durationScale;      // 0x01551828
extern void* g_s_endMode;            // 0x015517fc
extern void* g_s_idle;               // 0x01551800
extern void* g_s_blendInTime;        // 0x01551804
extern void* g_s_allowLocomotion;    // 0x015517f8
extern void* g_s_disableToolOverlay; // 0x01551808
extern void* g_s_matchVariantForTool;// 0x0155180c
extern void* g_s_priorityOverride;   // 0x01551814
extern void* g_s_choice;             // 0x015517ec
extern void* g_s_randomizeChoice;    // 0x015517f4
extern void* g_s_animation;          // 0x015517f0
void* __cdecl FUN_009de6e0(void* a, const void* b);                  // 0x009de6e0
void* __cdecl FUN_00a08a20(const void* key);                         // 0x00a08a20
void* __cdecl WCopy(void* dst, const void* src, uint n);             // 0x011e0744
void* __cdecl RBTreeDecrement(void* node);                           // 0x009215c0
void  __cdecl RBTreeInsert(void* node, void* hint, void* anchor, int side);   // 0x009216a0
void* __cdecl EAAllocate(uint size, const char* name, int, int, const char* file, int line); // 0x00f473a0
struct CmdBase_s00a0_8b00 { void Ctor(); };                                     // 0x0083c800
struct ChoiceBase { void Ctor(); };                                  // 0x0083cdd0
struct StaticData {                                                  // nSPCreatureAnim::creature_static_data
    int AddRef() const;                                              // 0x009b3450
    int Release() const;                                             // 0x009c26a0
};
struct InstanceData { int Release() const; };                        // 0x009c4cc0
struct AnimCreatureBase { int Release(); };                          // 0x00a05270
struct Job_s00a0_8b00 {                                                         // SP::cJob-ish
    void*    f00;                                                    // +0x00
    void*    f04;                                                    // +0x04
    uint32_t pad08[4];                                               // +0x08 .. +0x17
    uint32_t f18;                                                    // +0x18
    int  AddRef();                                                   // 0x0068f950
    int  Release();                                                  // 0x00690120
    void Arm();                                                      // 0x006909b0
};
struct WideStr {                                                     // 3-pointer string
    uint16_t* begin;                                                 // +0x00
    uint16_t* end;                                                   // +0x04
    uint16_t* cap;                                                   // +0x08
    void AllocateSelf(int n);                                        // 0x00429760
    void Assign(const uint16_t* b, const uint16_t* e);               // 0x00423650
};
struct Rec {                                                         // 0x1c anim record
    float    f0;                                                     // +0x00
    float    f4;                                                     // +0x04
    uint32_t f8;                                                     // +0x08
    WideStr  s;                                                      // +0x0c
    uint32_t f18;                                                    // +0x18
    Rec();
    Rec(const Rec& o);
};
struct TreeNode {                                                    // 0x20
    void*    left;                                                   // +0x00
    void*    right;                                                  // +0x04
    void*    up;                                                     // +0x08
    uint32_t color;                                                  // +0x0c
    uint32_t key0;                                                   // +0x10
    uint32_t key1;                                                   // +0x14
    void*    obj;                                                    // +0x18
};
struct Pair { void* node; uint8_t inserted; };                       // 8 bytes
struct Tree {
    uint32_t pad00;                                                  // +0x00
    void*    anchor;                                                 // +0x04
    void*    endNode;                                                // +0x08
    void*    root;                                                   // +0x0c
    uint32_t pad10;                                                  // +0x10
    uint32_t count;                                                  // +0x14

    void* insertAt(void** out, void* hint, uint* key, char flag);            // 0x00a08b00
    Pair* insertHint(Pair* out, const uint* key, void* dummy);               // 0x00a09420
    Pair* insertOrFind(Pair* out, void* hint, uint* key, int unused);        // 0x00a098d0
};
struct MapNodeA {                                                    // +0x18 = static data
    MapNodeA* left;                                                  // +0x00
    MapNodeA* right;                                                 // +0x04
    uint32_t  pad08[4];                                              // +0x08 .. +0x17
    void*     obj;                                                   // +0x18
};
struct MapNodeB {                                                    // +0x14 = job
    MapNodeB* left;                                                  // +0x00
    MapNodeB* right;                                                 // +0x04
    uint32_t  pad08[3];                                              // +0x08 .. +0x13
    void*     job;                                                   // +0x14
};
struct MapA { void Destroy(MapNodeA* n); };                          // 0x00a09850
struct MapB { void Destroy(MapNodeB* n); };                          // 0x00a09890
struct LayoutMgr {                                                   // 0x0166c06c
    uint32_t pad00;                                                  // +0x00
    void*    f04;                                                    // +0x04
    void*    f08;                                                    // +0x08
    void*    child;                                                  // +0x0c
    uint32_t f10;                                                    // +0x10
    uint32_t count;                                                  // +0x14
    void FreeTree(void* p);                                          // 0x009a9600
};
extern LayoutMgr* g_p166c06c;                                        // 0x0166c06c
struct RObj {                                                        // 0x0166cc08
    uint32_t pad00[26];                                              // +0x00 .. +0x67
    void**   v68;                                                    // +0x68
    void**   v6c;                                                    // +0x6c
};
extern RObj* g_p166cc08_s00a0_8b00;                                             // 0x0166cc08
struct ElemA {                                                       // element of v68
    uint32_t pad00[9];                                               // +0x00 .. +0x23
    void**   v24;                                                    // +0x24
    void**   v28;                                                    // +0x28
};
struct StateObj {
    uint8_t  pad0[0x17c];                                            // +0x000
    void*    obj;                                                    // +0x17c
    uint8_t  pad180[0x2f8 - 0x180];                                  // +0x180
    int32_t  nStates;                                                // +0x2f8
    int32_t  counts[1];                                              // +0x2fc (stride 0x10, data at +0x314)
};
struct ICmdReg {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void AddCommand(const void* name, void* cmd);            // +0x18
    void OnReg(void* parser, int state);                             // 0x0083c780
};
struct OnRegObj {
    ICmdReg  reg;                                                    // vtable @ +0x00
    uint32_t pad04[0xb];                                             // +0x04 .. +0x2f
    uint32_t f30;                                                    // +0x30 = state

    void OnRegisterAnimCommand(void* parser, int state);             // 0x00a08cf0
    void OnRegisterAnim(void* parser, int state);                    // 0x00a08fc0
    void OnRegisterChoice(void* parser, int state);                  // 0x00a09020
};
struct cAnimatingCreature_s00a0_8b00 {
    virtual void ac0();                                              // vtable @ +0x00
    uint8_t  pad04[0x15c - 0x04];                                    // +0x004 .. +0x15b
    void*    f15c;                                                   // +0x15c
    uint8_t  pad160[0x17c - 0x160];                                  // +0x160 .. +0x17b
    void*    f17c;                                                   // +0x17c
    void* scalar_deleting_destructor(uint8_t param_2);               // 0x00a08cb0
};
struct ResMan_s00a0_8b00 {
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
virtual void v12();
virtual void v13();
    virtual bool v14(void* out, const void* key, int zero);          // +0x38
};
struct HostObj {                                                     // the Init argument
virtual void h0();
virtual void h1();
virtual void h2();
virtual void h3();
virtual void h4();
virtual void h5();
virtual void h6();
virtual void h7();
virtual void h8();
virtual void h9();
virtual void h10();
virtual void h11();
    virtual void h12();
    virtual bool h13(void* elem, void** out, int a, int b, int c, int d);   // +0x34
};
struct CRes {
virtual void r0();
virtual void r1();
virtual void r2();
virtual void r3();
virtual void r4();
virtual void r5();
    virtual void* r6();                                              // +0x18
virtual void r7();
virtual void r8();
    virtual void r9();                                               // +0x24
};
// ---- items of slice s00a08b00 end

// ---- items of slice s00a0bcf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  g_kNegOne_13eb1bc;        // 0x013eb1bc
extern void*  g_pRandom_166cd30;        // 0x0166cd30 (EA::Random::RandomMersenneTwister)
typedef unsigned short uint16;
const char* const kEastlFile =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
struct WideStr_s00a0_bcf0 {                        // 3-pointer wide string (0x0c)
    uint16* begin;                      // +0x00
    uint16* end;                        // +0x04
    uint16* cap;                        // +0x08
    void AllocateSelf(int n);                        // 0x00429760
    void Assign(const uint16* b, const uint16* e);   // 0x00423650
};
extern uint16 gEmptyStr16_1667bac;      // 0x01667bac (shared empty wide string)
void* __cdecl memcpy_thunk(void* dst, const void* src, uint n);  // 0x011e0744
struct Rec_s00a0_bcf0 {                            // 0x1c anim record
    float    f0;                        // +0x00
    float    f4;                        // +0x04
    uint32_t f8;                        // +0x08
    WideStr_s00a0_bcf0  s;                         // +0x0c
    uint32_t f18;                       // +0x18
    Rec_s00a0_bcf0();
};
inline void __forceinline RecCloneInline(Rec_s00a0_bcf0* dst, const Rec_s00a0_bcf0* src)
{
    dst->f0 = src->f0;
    dst->f4 = src->f4;
    dst->f8 = src->f8;
    dst->s.begin = 0;
    dst->s.end = 0;
    dst->s.cap = 0;

    const uint16* sb = src->s.begin;
    const uint16* se = src->s.end;
    int chars = (int)(se - sb);
    if (chars <= 0) {
        dst->s.begin = &gEmptyStr16_1667bac;
        dst->s.end = &gEmptyStr16_1667bac;
        dst->s.cap = (uint16*)((char*)&gEmptyStr16_1667bac + 2);
    } else {
        uint16* buf = (uint16*)EAAllocate(2 * (chars + 1), "EASTL", 0, 0, kEastlFile, 0xd1);
        dst->s.begin = buf;
        dst->s.end = buf;
        dst->s.cap = buf + (chars + 1);
    }
    memcpy_thunk(dst->s.begin, sb, 2 * chars);
    dst->s.end = (uint16*)((char*)dst->s.begin + 2 * chars);
}
Rec_s00a0_bcf0* __cdecl FUN_00a095f0(Rec_s00a0_bcf0* first, Rec_s00a0_bcf0* last, Rec_s00a0_bcf0* dst);        // 0x00a095f0
Rec_s00a0_bcf0* __cdecl FUN_00a09630(Rec_s00a0_bcf0* first, Rec_s00a0_bcf0* last, Rec_s00a0_bcf0* dst);        // 0x00a09630
Rec_s00a0_bcf0* __cdecl FUN_00a096e0(Rec_s00a0_bcf0* first, Rec_s00a0_bcf0* last, Rec_s00a0_bcf0* dst);        // 0x00a096e0
void __cdecl FUN_00a095a0(Rec_s00a0_bcf0* dst, Rec_s00a0_bcf0* last, const Rec_s00a0_bcf0* value);  // 0x00a095a0
void __cdecl FUN_00a09cc0(Rec_s00a0_bcf0* p, uint n, const Rec_s00a0_bcf0& a);           // 0x00a09cc0
void __cdecl RecConstruct(Rec_s00a0_bcf0* dst, const Rec_s00a0_bcf0* src);                // 0x00a093b0
struct CursorRec { Rec_s00a0_bcf0* p; };
CursorRec* __cdecl FUN_00a09560(CursorRec* out, Rec_s00a0_bcf0* first, Rec_s00a0_bcf0* last, Rec_s00a0_bcf0* init); // 0x00a09560
struct ItemVec_s00a0_bcf0 {                        // eastl::vector<Rec, sp_vector_allocator> (0x14)
    Rec_s00a0_bcf0*  mpBegin;                      // +0x00
    Rec_s00a0_bcf0*  mpEnd;                        // +0x04
    Rec_s00a0_bcf0*  mpCapacity;                   // +0x08
    int   mAllocator;                   // +0x0c
    int   mAllocator2;                  // +0x10

    Rec_s00a0_bcf0* DoInsertValue(Rec_s00a0_bcf0* position, const Rec_s00a0_bcf0& value);            // 0x00a0bcf0
    void DoInsertValues(Rec_s00a0_bcf0* position, uint n, const Rec_s00a0_bcf0& value);   // 0x00a0be60
    void AssignRange(const ItemVec_s00a0_bcf0* o);                             // 0x00a0b110
};
struct Sub_s00a0_bcf0 {                            // 0x18
    ItemVec_s00a0_bcf0 items;                      // +0x00
    float   f14;                        // +0x14
};
struct SubItemVec {                     // eastl::vector<Sub, sp_vector_allocator> (0x14)
    Sub_s00a0_bcf0* mpBegin;                       // +0x00
    Sub_s00a0_bcf0* mpEnd;                         // +0x04
    Sub_s00a0_bcf0* mpCapacity;                    // +0x08
    int  mAllocator;                    // +0x0c
};
SubItemVec* __cdecl ConstructSubCursor(SubItemVec* out, const Sub_s00a0_bcf0* first, const Sub_s00a0_bcf0* last, Sub_s00a0_bcf0* init); // 0x00a0c090
Sub_s00a0_bcf0* __cdecl ReverseCopySubs(Sub_s00a0_bcf0* first, Sub_s00a0_bcf0* last, Sub_s00a0_bcf0* dst);                                          // 0x00a0c230
struct Vec3_s00a0_bcf0 { float x, y, z; };
struct Vec3VecSmall {
    Vec3_s00a0_bcf0* mpBegin;
    Vec3_s00a0_bcf0* mpEnd;
    Vec3_s00a0_bcf0* mpCapacity;
    void  resize(uint n);               // 0x00a0ac10
};
struct FBNode {                         // rbtree node holding a cFeedbackEvent value
    void*    l;                         // +0x00
    void*    r;                         // +0x04
    void*    up;                        // +0x08
    uint32_t color;                     // +0x0c
    uint32_t key;                       // +0x10
    uint32_t pad14;                     // +0x14
    uint32_t pad18;                     // +0x18
    uint32_t pad1c;                     // +0x1c
    uint32_t pad20;                     // +0x20
    uint32_t pad24;                     // +0x24
    uint32_t pad28;                     // +0x28
    float    f2c;                       // +0x2c
    uint8_t  b30;                       // +0x30
    uint8_t  pad31;                     // +0x31
    uint8_t  b32;                       // +0x32
    uint8_t  pad33;                     // +0x33
    uint32_t pad34;                     // +0x34
    uint32_t pad38;                     // +0x38
    int      i3c;                       // +0x3c
    Sub_s00a0_bcf0*     subsBegin;                 // +0x40
    Sub_s00a0_bcf0*     subsEnd;                   // +0x44
};
struct FBMap {                          // rbtree<unsigned, pair<const unsigned, AutoRefCount<cFeedbackEvent>>>
    uint32_t pad0;                      // +0x00
    void*    anchor;                    // +0x04
    FBNode* find(FBNode** out, const uint32_t* key);  // 0x00e5c780
};
extern FBMap g_fbMap_1551a68;           // 0x01551a68
void* __cdecl FUN_00a01a00(void* qb, void* def, const Vec3_s00a0_bcf0* pos, int count); // 0x00a01a00
void  __cdecl FUN_00a001f0(void* qb, void* h, int a);                        // 0x00a001f0
void  __cdecl FUN_00a00240(void* qb, void* h, unsigned char v);               // 0x00a00240
void  __cdecl FUN_00a00290(void* qb, void* h, float v);                       // 0x00a00290
void  __cdecl FUN_00a002f0(void* qb, void* h, int v);                         // 0x00a002f0
void  __cdecl FUN_009ffee0(void* qb, void* h, float v);                       // 0x009ffee0
void  __cdecl FUN_00a00080(void* qb, void* h, uint32_t id);                   // 0x00a00080
void  __cdecl FUN_00a00450(void* qb, void* h, void* cb, uint32_t id);         // 0x00a00450
void  __cdecl FUN_00a05ee0();                                                 // 0x00a05ee0
bool  __cdecl qb_enable(void* qb, int animID);                                // 0x00a01b50
double RandomGenerateDouble(void* self);   // 0x009362d0 (ecx = singleton)
struct AnimFbOwner {                    // `this` for the feedback dispatch
    uint32_t pad000[0x184 / 4];         // +0x000
    void*    mpQB;                      // +0x184
    void*    mpFbTarget;                // +0x188 (unused here)
    char*    mpAnimDefHolder;           // +0x18c (holder whose +0x1c -> +0x14 is the def)
    uint32_t c640(uint32_t id, uint32_t* outIndex);   // 0x00a0c640
    void     c670(uint32_t id, uint32_t* outIndex);   // 0x00a0c670
};
// ---- items of slice s00a0bcf0 end

// ---- items of slice s00a0d2d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct WideStr_s00a0_d2d0 {                                                     // DynamicString, 16 bytes
    uint16_t* begin;                                                 // +0x00
    uint16_t* end;                                                   // +0x04
    uint16_t* cap;                                                   // +0x08
    void*     a0c;                                                   // +0x0c
    void AllocateSelf(int n);                                        // 0x00429760
    void Assign(const uint16_t* b, const uint16_t* e);               // 0x00423650
};
typedef WideStr_s00a0_d2d0 WStr;
void  __cdecl RemoveHandler(void* h, void* a, void* b, void* c, void* d); // 0x00571db0
void  __cdecl FUN_009a9680();                                        // 0x009a9680
void* __stdcall FUN_00a0ad10(void** out, void* hint, void* key, char flag);  // 0x00a0ad10
void  __cdecl FUN_00a0c090(void** out, void* first, void* last, void* dst, void* src); // 0x00a0c090
void  __cdecl FUN_00a0c230(void* a, void* b, void* c);               // 0x00a0c230
void* __cdecl FUN_00a0d740(uint n, void* first, void* last);         // 0x00a0d740
void  __cdecl FUN_00a0ade0(void* dst, uint count, const void* value); // 0x00a0ade0
void* __cdecl FUN_00a0af70(void* first, void* last, void* dst);      // 0x00a0af70
void  __cdecl FUN_00a0a580(void* a, void* b, void* c);               // 0x00a0a580
void* __cdecl FUN_00a0a520(void* v);                                  // 0x00a0a520
void  __cdecl FUN_00a0dee0(void* first, void* last);                 // 0x00a0dee0
void  __cdecl FUN_00a09810(void* first, void* last);                 // 0x00a09810
bool  __cdecl FUN_00a09740(void* obj, void** out);                   // 0x00a09740
WStr*  __cdecl ConvertToString16(void* out, const char* s, int n);   // 0x0093c5a0
struct KFBase {                                                      // 0x14-byte sub-object
    uint32_t w[5];
    void operator=(const KFBase& o);                                 // 0x00a0b110
};
struct KF {                                                          // 0x18 element
    KFBase b;                                                        // +0x00
    float  prob;                                                     // +0x14
};
struct VHelper { void dtor(void* b, void* e); };                     // 0x00a0aca0
struct RecDtor { void dtor(void* b, void* e); };                     // 0x00a0bc90
struct Rec_s00a0_d2d0 {                                                         // 0x1c record
    float    f0;                                                     // +0x00
    float    f4;                                                     // +0x04
    uint32_t f8;                                                     // +0x08
    WideStr_s00a0_d2d0  s;                                                      // +0x0c
    uint32_t f18;                                                    // +0x18
    void ctorFrom(const Rec_s00a0_d2d0& o);                                     // 0x00a093b0
};
struct KVec {                                                        // vector<KF>
    KF* begin;                                                       // +0x00
    KF* end;                                                         // +0x04
    KF* cap;                                                         // +0x08
    void* copyCtor(const KVec& src);                                 // 0x00a0d350
    KVec& operator=(const KVec& o);                                  // 0x00a0dd90
    void  resize(uint a);                                            // 0x00a0e0b0
    void  insertAt(KF* pos, uint count, const KF& value);            // 0x00a0da40
};
struct RecVec {                                                      // vector<Rec>
    Rec_s00a0_d2d0* begin;                                                      // +0x00
    Rec_s00a0_d2d0* end;                                                        // +0x04
    Rec_s00a0_d2d0* cap;                                                        // +0x08
    void resize(uint a);                                             // 0x00a0d660
    void growAt(Rec_s00a0_d2d0* end, const Rec_s00a0_d2d0& value);                         // 0x00a0bcf0
};
struct Parser {
    const char** MainArguments(int n);                               // 0x00838320
    const char** OptionArguments(const char* name, int n);           // 0x00838330
};
struct Host2 {
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
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
    virtual void  v35(void* x);                                      // +0x8c
virtual void  v36();
virtual void v37();
    virtual float v38(const char* s);                                // +0x98
    virtual void  v39();
    virtual uint  v40(const char* s);                                // +0xa0
};
struct JobRef { void operator=(const JobRef& o); };                  // 0x00630540
struct Job_s00a0_d2d0    { int Release(); };                                    // 0x00690120
struct RefCounted {
    virtual void Destroy(bool del);                                  // vtable +0x00
    int refcount;                                                    // +0x04
};
struct StaticData_s00a0_d2d0 {  // 0x009c1dc0 / 0x009c26a0
    int Clear(void* p);
    int Release();
};
struct TreeMap {                                                     // rbtree<uint,JobRef>
    uint   pad00;                                                    // +0x00
    void*  anchor;                                                   // +0x04
    void*  endNode;                                                  // +0x08
    void*  root;                                                     // +0x0c
    uint   pad10;                                                    // +0x10
    uint   count;                                                    // +0x14
    void* findOrInsert(uint* key);                                   // 0x00a0d2d0
    void* find(void** out, const void* key);                         // 0x00e5c780
};
struct AnimNode_s00a0_d2d0 {                                                    // anim-data tree node
    AnimNode_s00a0_d2d0* l;                                                     // +0x00
    AnimNode_s00a0_d2d0* r;                                                     // +0x04
    uint8_t   pad08[0x10];                                           // +0x08 .. +0x17
    WideStr_s00a0_d2d0   s;                                                     // +0x18
    uint8_t   pad24[0x18];                                           // +0x28 .. +0x3f
    KVec      vec;                                                   // +0x40
};
struct AnimTree {
    uint32_t pad00;                                                  // +0x00
    void*    anchor;                                                 // +0x04
    void*    endNode;                                                // +0x08
    void*    root;                                                   // +0x0c
    uint8_t  color;                                                  // +0x10
    uint8_t  pad11[3];                                               // +0x11
    uint32_t count;                                                  // +0x14
    void nukeSubtree(AnimNode_s00a0_d2d0* n);                                   // 0x00a0d9c0
};
struct ViewerData {                                                  // 0x00a0d420 this
    uint8_t  pad00[0x10];                                            // +0x00
    WideStr_s00a0_d2d0  s;                                                      // +0x10
    uint8_t  pad1c[0x18];                                            // +0x20 .. +0x37
    KVec     vec;                                                    // +0x38
    void Clear();                                                    // 0x00a0d420
};
struct S {
    uint32_t id;                                                     // +0x00
    WideStr_s00a0_d2d0  s;                                                      // +0x04
    float    f14;                                                    // +0x14
    float    f18;                                                    // +0x18
    uint8_t  b1c, b1d, b1e;                                          // +0x1c,1d,1e
    uint32_t f20;                                                    // +0x20
    uint32_t f24;                                                    // +0x24
    uint32_t f28;                                                    // +0x28
    KVec     vec;                                                    // +0x2c
    S(const S& o);                                                   // 0x00a0d7a0
    S& operator=(const S& o);                                        // 0x00a0df30
    void reset();                                                    // 0x00a0e250
};
struct ObjA {                                                        // this+0xc -> this
    uint8_t pad00[0x38];                                             // +0x00
    RecVec* pv;                                                      // +0x38
};
struct Obj {                                                         // command state at this+0x30
    uint8_t pad00[0x04];                                             // +0x00
    float   f04;                                                     // +0x04
    uint8_t pad08[0x04];                                             // +0x08
    S       s;                                                       // +0x0c
    uint8_t pad44[0x08];                                             // +0x44 .. +0x4b
    float   f4c;                                                     // +0x4c
    float   f50;                                                     // +0x50
    float   f54;                                                     // +0x54
};
struct Cmd_s00a0_d2d0 {
    uint8_t pad00[0x04];                                             // +0x00
    Host2*  f04;                                                     // +0x04
    uint8_t pad08[0x28];                                             // +0x08 .. +0x2f
    Obj*    f30;                                                     // +0x30
    void Execute_470(void* parser);                                  // 0x00a0d470
    void notify(uint key);                                           // 0x00a0d570
    void ResetCmd(void* parser);                                     // 0x00a0e2e0
    void AddProb(void* parser);                                      // 0x00a0e350
    void SetName(void* parser);                                      // 0x00a0e3f0
};
struct CleanupObj {                                                  // 0x00a0dfa0 this
    uint8_t  pad00[0x54];                                            // +0x00 .. +0x53
    void*    f54;                                                    // +0x54
    void*    f58;                                                    // +0x58
    void*    f5c;                                                    // +0x5c
    void*    f60;                                                    // +0x60
    void*    f64;                                                    // +0x64
    uint8_t  pad68[0x80 - 0x68];                                     // +0x68 .. +0x7f
    uint32_t f80;                                                    // +0x80
    RefCounted* f84;                                                 // +0x84
    bool Unregister();                                               // 0x00a0dfa0
};
struct XObj { void* f0; void Reset(); };                             // 0x166c058 object
extern XObj       g_x166c058;                                        // 0x0166c058
extern void*      g_p166cc08_s00a0_d2d0;                                        // 0x0166cc08
extern AnimTree   g_tree1551a68;                                     // 0x01551a68
// ---- items of slice s00a0d2d0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __cdecl FUN_00a0d850(KF* first, KF* last, const KF* value);  // 0x00a0d850 (stays in the slice: not this object's)

// @ 0x009ff4b0
void QueuedBlender::UpdateGoals(float dt, char param_3)
{
    FUN_009bc580(field_fbc, dt);
    if (param_3 == 0)
        field_fbc->FUN_009b8760(dt);

    for (int i = 0; i < 16; ++i) {
        uint32_t v = mActive[i];
        if (v < 0x10) {
            AnimGoal* g = (AnimGoal*)((char*)this + v * 0xf0 + 8);
            if (g->field_c0 != 0 && field_fac != 0 && param_3 == 0)
                FUN_0099d460(g->field_94, field_fbc, g->field_00, field_fb0);
        }
    }

    if (param_3 == 0) {
        if (field_fbc->field_260 != 0 && 1e-06f < field_fb4) {
            if (field_fbc->mSub.field_00 == 0) {
                field_fbc->mSub.FUN_009e3f70(6, 4);
                field_fbc->FUN_009b7b10(0, 0);
            }
            CreatureInst* c = field_fbc;
            float inv = 1.0f / c->mScale;
            field_fbc->mSub.FUN_009e4600(Vec3(c->field_264 * inv, c->field_268 * inv, c->field_26c), 0, 0, 0, 0);
            field_fbc->FUN_009b8720(field_fb4);
            field_fbc->FUN_009b8d50(dt);
            field_fbc->FUN_009b8e40(field_fb4);
            if (field_fac != 0 && field_fbc->field_1680 != 0)
                field_fbc->FUN_009ba040(dt, field_fb4);
            if (g_timer != 0 && field_fbc->mStatic->field_3f5 == 0 && field_fbc->field_168c != 0)
                field_fbc->FUN_009c0680();
            field_fbc->FUN_009b8f40(field_fb4);
        }
        if (field_fac != 0)
            field_fbc->UpdateWiggles(dt, field_fb4);
    }
    FUN_c2e4e0(field_fbc);
}

// @ 0x009ff6f0
AnimGoal* __cdecl FindGoalByHandle(QueuedBlender* blender, uint32_t handle)
{
    if (handle != 0) {
        AnimGoal* g = (AnimGoal*)((char*)blender + (handle & 0xff) * 0xf0 - 0xe8);
        if (g->field_b4 == (handle >> 8)) {
            if (g->field_00 != 0)
                return g;
            uint32_t h2 = (uint32_t)g->field_6c;
            if (h2 != 0) {
                g = (AnimGoal*)((char*)blender + (h2 & 0xff) * 0xf0 - 0xe8);
                if (g->field_b4 == (h2 >> 8) && g->field_00 != 0)
                    return g;
            }
        }
    }
    return 0;
}

// @ 0x009ff750
AnimGoal* __cdecl GetCurrentGoal(QueuedBlender* b)
{
    uint32_t a = b->mCurrent;
    if (a < 0x10) {
        uint32_t idx = b->mActive[a];
        if (idx < 0x10) {
            AnimGoal* g = (AnimGoal*)((char*)b + idx * 0xf0 + 8);
            if (g->field_00 != 0)
                return g;
            uint32_t c = (uint32_t)g->mChildCount;
            if (c < 8 && g->mChildren[c * 3] != 0)
                return g;
        }
    }
    return 0;
}

// @ 0x009ff7a0
int __cdecl FindGoalValue(QueuedBlender* blender, uint32_t handle)
{
    AnimGoal* g = FindGoalByHandle(blender, handle);
    return g ? g->field_00 : 0;
}

// @ 0x009ff7c0
bool __cdecl FindGoalByID(QueuedBlender* b, int goalId, int* outHandle)
{
    int i;
    for (i = 0; i < 16; ++i) {
        uint32_t v = b->mQueue[i];
        if (v < 0x10) {
            AnimGoal* g = (AnimGoal*)((char*)b + v * 0xf0 + 8);
            if (g->field_00 != 0 && g->field_d8 == goalId) {
                if (outHandle)
                    *outHandle = (uint8_t)b->mQueue[i] + 1 + (int)g->field_b4 * 0x100;
                return true;
            }
        }
    }
    for (i = 0; i < 16; ++i) {
        uint32_t v = b->mActive[i];
        if (v < 0x10) {
            AnimGoal* g = (AnimGoal*)((char*)b + v * 0xf0 + 8);
            if (g->field_00 != 0 && g->field_d8 == goalId) {
                if (outHandle)
                    *outHandle = (uint8_t)b->mActive[i] + 1 + (int)g->field_b4 * 0x100;
                return true;
            }
        }
    }
    return false;
}

// @ 0x009ffa00
bool __cdecl LoadGoalChildren(QueuedBlender_s009f_fa00* b, AnimGoal_s009f_fa00* g)
{
    while ((uint32_t)g->mChildCount < 8) {
        int key = g->mChildren[g->mChildCount * 3];
        GoalObj* o = FUN_009a37a0_s009f_fa00(key);
        if (o == 0) {
            TmpObj* tmp = 0;
            if (!FUN_009a38f0(*(void**)b->field_fbc, key, &tmp)) {
                FUN_009a3680(0, key);
                if (tmp)
                    tmp->FUN_0099f0b0();
                return false;
            }
            ++g->mChildCount;
            if (tmp)
                tmp->FUN_0099f0b0();
        } else {
            int r = FUN_009a4550(*(void**)b->field_fbc, o);
            if (r != 0) {
                GoalObj* old;
                if (g_goalPool->begin == g_goalPool->end) {
                    GoalObj* mem = (GoalObj*)operator_new(0xe0, "Anim/aid", 0, 0, 0, 0);
                    GoalObj* n = mem ? mem->FUN_009a34a0() : 0;
                    old = g->field_00;
                    if (n != old) {
                        if (n)
                            n->AddRef();
                        g->field_00 = n;
                        if (old)
                            old->Release();
                    }
                } else {
                    g->FUN_009aa4c0(g_goalPool->end - 1);
                    g_goalPool->end -= 1;
                    old = *g_goalPool->end;
                    if (old)
                        old->Release();
                }
                g->field_00->FUN_009a3220((int)o, b->field_fbc, r);
                return true;
            }
            ++g->mChildCount;
        }
    }
    return true;
}

// @ 0x009ffdb0
bool __cdecl IsPendingGoal(QueuedBlender_s009f_fa00* b, uint32_t handle)
{
    extern AnimGoal_s009f_fa00* __cdecl FindGoalByHandle(QueuedBlender_s009f_fa00*, uint32_t);   // 0x009ff6f0
    AnimGoal_s009f_fa00* g = 0;
    if (handle != 0) {
        g = FindGoalByHandle(b, handle);
    } else {
        if (b->mCurrent < 0x10) {
            uint32_t v = b->mActive[b->mCurrent];
            if (v < 0x10)
                g = (AnimGoal_s009f_fa00*)((char*)b + v * 0xf0 + 8);
        }
    }
    return g == (AnimGoal_s009f_fa00*)((char*)b + b->mPending * 0xf0 + 8);
}

// @ 0x009ffe10
void __cdecl ResolveGoalPair(GoalPair* out, QueuedBlender_s009f_fa00* b, uint32_t handle)
{
    AnimGoal_s009f_fa00* a = 0;
    AnimGoal_s009f_fa00* c = 0;
    if (handle != 0) {
        AnimGoal_s009f_fa00* g = (AnimGoal_s009f_fa00*)((char*)b + (handle & 0xff) * 0xf0 - 0xe8);
        if (g->field_b4 == (int)(handle >> 8)) {
            a = g;
            uint32_t h2 = (uint32_t)g->field_6c;
            if (h2 != 0) {
                AnimGoal_s009f_fa00* g2 = (AnimGoal_s009f_fa00*)((char*)b + (h2 & 0xff) * 0xf0 - 0xe8);
                if (g2->field_b4 == (int)(h2 >> 8))
                    c = g2;
            }
        }
    }
    out->second = c;
    out->first = a;
}

// @ 0x00a00180
int __cdecl SetGoalFieldE0(QueuedBlender_s009f_fa00* b, uint32_t handle, int lo, int hi)
{
    GoalPair p;
    ResolveGoalPair(&p, b, handle);
    if (p.first) {
        p.first->field_e0 = lo;
        p.first->field_e4 = hi;
    }
    if (p.second) {
        p.second->field_e0 = lo;
        p.second->field_e4 = hi;
    }
    if (p.first == 0 && p.second == 0)
        return 0;
    return 1;
}

// @ 0x00a002f0
int __cdecl SetGoalFlagD4(QueuedBlender_s009f_fa00* b, uint32_t handle, char v)
{
    GoalPair p;
    ResolveGoalPair(&p, b, handle);
    if (p.first) {
        p.first->field_d4 = v;
        if (p.first->field_00)
            p.first->field_00->field_ad = v;
    }
    if (p.first == 0 && p.second == 0)
        return 0;
    return 1;
}

// @ 0x00a00340
int __cdecl SetGoalFieldCC(QueuedBlender_s009f_fa00* b, uint32_t handle, float v)
{
    GoalPair p;
    ResolveGoalPair(&p, b, handle);
    if (p.first) {
        p.first->field_cc = v;
        if (p.first->field_00)
            p.first->field_00->field_b8 = v;
    }
    if (p.second) {
        p.second->field_cc = v;
        if (p.second->field_00)
            p.second->field_00->field_b8 = v;
    }
    if (p.first == 0 && p.second == 0)
        return 0;
    return 1;
}

// @ 0x00a003c0
int __cdecl ScaleGoalFieldD0(QueuedBlender_s009f_fa00* b, uint32_t handle, float v)
{
    GoalPair p;
    ResolveGoalPair(&p, b, handle);
    if (p.first) {
        p.first->field_d0 = v;
        if (p.first->field_00)
            p.first->field_00->field_b8 = v * p.first->field_00->field_b8;
    }
    if (p.second) {
        p.second->field_d0 = v;
        if (p.second->field_00)
            p.second->field_00->field_b8 = v * p.second->field_00->field_b8;
    }
    if (p.first == 0 && p.second == 0)
        return 0;
    return 1;
}

// @ 0x00a00450
bool __cdecl SetGoalFieldE8(QueuedBlender_s009f_fa00* b, uint32_t handle, int lo, int hi)
{
    GoalPair p;
    ResolveGoalPair(&p, b, handle);
    AnimGoal_s009f_fa00* a = p.first;
    if (a) {
        a->field_e8 = lo;
        a->field_ec = hi;
    }
    return (bool)a;
}

// @ 0x00a00490
void AnimGoal_s009f_fa00::Reset()
{
    GoalObj* p = field_00;
    field_a8 = 0.0;
    field_70 = 0.0f;
    field_74 = 0.0f;
    field_78 = 0.0f;
    field_7c = 0;
    field_88 = 0.0f;
    field_80 = 1;
    field_84 = 0;
    field_94 = 1.0f;
    field_98 = 0.0f;
    field_8c = 0.0f;
    field_90 = 1.0f;
    field_cc = -1.0f;
    field_d0 = 1.0f;
    field_d4 = 0;
    field_9c = 0;
    field_9d = 0;
    field_a0 = 0.0f;
    field_b0 = 0;
    field_b4 = 0;
    field_b8 = 0.0f;
    field_bc = 0;
    field_c0 = 0;
    field_c4 = 0.0f;
    field_c8 = 0.0f;
    if (p) {
        FUN_009a1ad0(p);
        field_00->FUN_009a3080(0);
        GoalPool* pool = g_goalPool;
        GoalObj** top = pool->end;
        if (top < pool->cap) {
            pool->end = top + 1;
            if (top) {
                GoalObj* q = field_00;
                *top = q;
                if (q)
                    q->AddRef();
            }
        } else {
            pool->FUN_009ab170(top, this);
        }
        if (field_00) {
            GoalObj* t = field_00;
            field_00 = 0;
            t->Release();
        }
    }
    if (field_04) {
        GoalObj2* t = field_04;
        field_04 = 0;
        t->Release();
    }
    // children 0..7: {obj, -1.0f, 1.0f}
    ChildSlot* cs = (ChildSlot*)mChildren;
    for (int i = 0; i < 8; ++i) {
        cs[i].id = 0;
        cs[i].b = 1.0f;
        cs[i].a = -1.0f;
    }
    mChildCount = 0;
    field_6c = 0;
    field_d8 = 0;
    field_dc = 0;
    field_e0 = 0;
    field_e4 = 0;
    field_e8 = 0;
    field_ec = 0;
}

// @ 0x00a00670
void AnimGoal_s009f_fa00::Stop(char a, char b)
{
    if (b == 0 && (field_00 != 0 || ((uint32_t)mChildCount < 8 && mChildren[mChildCount * 3] != 0)) &&
        field_c0 != 0) {
        if (field_c0 != 3) {
            field_c0 = 3;
            field_c4 = field_78;
        }
    } else if (a != 0) {
        Reset();
    } else {
        if (field_00)
            FUN_009a1ad0(field_00);
        field_c4 = 0.0f;
        field_c0 = 0;
    }
}

// @ 0x00a007d0
void QueuedBlender_s009f_fa00::ResetAll(char full)
{
    if (full) {
        mSeq = 1;
        _ReadWriteBarrier();
        CreatureInst_s009f_fa00* c = field_fbc;
        if (c) {
            field_fbc = 0;
            c->Release();
        }
        field_fc0 = 0;
    }
    field_fac = 0;
    field_fb0 = 0.0f;
    field_f08 = 0xffffffff;
    field_f9c = -1;
    field_fa0 = -1;
    mCurrent = 0xffffffff;
    mPending = 0xffffffff;
    field_fb4 = 1.0f;
    field_fb8 = 0.0f;
    field_fc4 = g_defaultA;
    float fb = g_defaultB;
    field_fcc = 0;
    field_fc8 = fb;
    for (int i = 0; i < 16; ++i) {
        mGoals[i].Reset();
        mActive[i] = 0xffffffff;
        mQueue[i] = 0xffffffff;
    }
}

// @ 0x00a00910
void QueuedBlender_s009f_fa00::SetCreature(CreatureInst_s009f_fa00* c, int v)
{
    ResetAll(1);
    CreatureInst_s009f_fa00* old = field_fbc;
    if (c != old) {
        if (c)
            c->AddRef();
        field_fbc = c;
        if (old)
            old->Release();
    }
    field_fc0 = v;
}

// @ 0x00a00d50
void QueuedBlender_s00a0_0980::Activate(uint i, char force)
{
    if (i >= 0x10) return;
    uint v = mActive[i];
    if (v >= 0x10) return;
    AnimCommand* c = &mCommands[v];
    if (c->mWeightD0 > 0.0f)
        FUN_00a00c40(i);
    v = mActive[i];
    c = &mCommands[v];
    if (c->mEnabled != 0) return;
    void* anim = c->mAnim;
    if (c->mLinkedHandle == 0 && c->mCb1 != 0) {
        ((void (__cdecl*)(uint, uint, QueuedBlender_s00a0_0980*, uint))c->mCb1)
            (c->mCb1a, c->mCb1b, this, c->mSeq * 0x100 + 1 + (v & 0xff));
    }
    if (!mFlagFcc) {
        c->mStatus = 2;
        c->mWeight98 = 0.0f;
        mFlagFcc = true;
    } else {
        c->mStatus = 1;
    }
    c->mTransition = c->mCursor;
    FUN_009a2cc0((uint)anim, c->mAnimId);
    *(double*)((char*)anim + 0xb0) = (double)c->mDurationOverride;
    if (c->mFlag84) {
        uint d = mDefault;
        if (mActive[mPrimary] == d)
            mPrimary = i;
        AnimCommand* dc = &mCommands[d];
        if (dc->mEnabled == 0) {
            ((XC*)this)->FUN_00a008b0();
        } else {
            uint v2 = mActive[i];
            if (v2 != d && v2 < 0x10 && d < 0x10)
                ((XC*)dc)->FUN_00a00670(1, 0);
        }
        mDefault = mActive[i];
    }
    if (force) {
        uint creature = *(uint*)mCreature;
        ((XC*)mBakedMgr)->FUN_009abe90(creature, (uint)anim, c->mAnimId, 0);
        uint r = ((XC*)mBakedMgr)->FUN_009aa8a0(creature, (uint)anim, c->mAnimId);
        ((XC*)&c->mAnimBaked)->FUN_009a9b90(r);
    }
    mNewlyActivated[i] = true;
}

// @ 0x00a00f90
void QueuedBlender_s00a0_0980::FUN_00a00f90(AnimCommand* cmd, uint x)
{
    bool b1 = (mDefault < 0x10) && (cmd == &mCommands[mDefault]);
    bool b2 = (mPrimary < 0x10) && (cmd == &mCommands[mActive[mPrimary]]);
    if (!b1 || mQueueHead != 0xffffffffu) {
        ((XC*)cmd)->FUN_00a00670(!b1, (int)x);
        if (cmd->mStatus == 0) {
            uint* p = mActive;
            int n = 0x10;
            do {
                if (cmd == &mCommands[*p])
                    *p = 0xffffffffu;
                p++;
                n--;
            } while (n != 0);
        }
        if (b2)
            ((XC*)this)->FUN_009ff440();
    }
}

// @ 0x00a01a00
int qb_add_query(anim_qb* qb, int param_2, AnimReference* refs, unsigned int param_4)
{
    if (param_2 == 0)
        return 0;
    unsigned int slot = qb_free_slot(qb);
    if (slot >= 16)
        return 0;
    anim_query* q = &qb->queries[slot];
    q->Reset();
    unsigned int n = param_4 < 9 ? param_4 : 8;
    if (n != 0) {
        AnimReference* dst = (AnimReference*)((char*)q + 8);
        do {
            *dst = *refs;
            ++refs;
            ++dst;
            --n;
        } while (n != 0);
    }
    q->field_A8 = 0.0;
    q->field_B0 = 0;
    q->field_70 = 0.0f;
    q->field_74 = g_13f6a3c;
    q->field_D4 = false;
    q->field_BC = 0;
    q->animID = 0;
    q->field_7C = false;
    q->idle = false;
    q->field_8C = g_1485720;
    q->field_A0 = g_1485720;
    q->field_78 = g_13ec480;
    q->field_CC = g_13eb1bc;
    q->field_D0 = g_1485720;
    q->blendInTime = g_13ec480;
    q->mode = 1;
    q->field_B4 = qb->field_0;
    unsigned int id = (unsigned int)qb->field_0 * 256 + 1 + (slot & 0xff);
    if (!qb_find2(qb, q))
        qb_add(qb, q, id, param_2);
    return id;
}

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

// @ 0x00a01c10
anim_qb::anim_qb()
{
    // retail interleaves the first two zero stores between the 4th `push` and the call
    anim_query* p = queries;
    for (int i = 15; i >= 0; --i) {
        anim_query& q = *p;
        AnimReference* a = q.anims;
        q.field_0 = 0;
        q.field_4 = 0;
        vci(a, sizeof(AnimReference), 8, (void*)animref_ctor);
        q.Reset();
        ++p;
    }
    p_anim_cid = 0;
    Reset(1);
}

// @ 0x00a01c70
anim_qb::~anim_qb()
{
    Reset(1);
    if (p_anim_cid)
        ((RefObj*)p_anim_cid)->Rel9c4cc0();
    anim_query* p = &queries[16];
    for (int i = 15; i >= 0; --i) {
        anim_query& q = *--p;
        q.Reset();
        if (q.field_4)
            q.field_4->Rel9ae1c0();
        if (q.field_0)
            q.field_0->Rel9a3630();
    }
}

// @ 0x00a01cd0
void anim_qb::UpdateQuery(uint32_t param_1, float param_2)
{
    unsigned int idx = (param_1 & 0xff) - 1;
    if (idx >= 16)
        return;
    anim_query* q = &queries[idx];
    if (q->field_B4 != (int)(param_1 >> 8))
        return;

    float v = q->field_C8 - param_2;
    int otherIdx = (q->field_6C & 0xff) - 1;
    anim_query* other = &queries[otherIdx];
    q->field_C8 = v;

    if (q->field_C0 != 0)
        return;
    if (q->field_0 == 0) {
        if (other->field_C0 == 3)
            return;
        if (!qb_find2(this, q))
            return;
        if (q->field_0 == 0)
            return;
    }
    if (!(v <= 0.0f))
        return;
    if (other->field_C0 != 3) {
        RefObj* target = q->field_0;
        ((unsigned char*)target)[0xad] = q->field_D4;
        float a = other->field_CC;
        if (a >= 0.0f) {
            q->field_CC = a;
            target->mBlendB = a;
        } else {
            int i = q->field_68 + 1;
            float b = *(float*)((char*)q + i * 12);
            if (b >= 0.0f) {
                q->field_CC = b;
                target->mBlendB = b;
            }
        }
        float c = other->field_D0;
        if (c == g_1485720) {
            int i = q->field_68 + 1;
            float d = *(float*)((char*)q + i * 12 + 0x10);
            if (d != g_1485720) {
                q->field_D0 = d;
                target->mBlendB *= d;
            }
        } else {
            q->field_D0 = c;
            target->mBlendB *= c;
        }
    }
    q->field_0->mBlendA = q->field_C8 * g_13eb1bc;
    q->field_A8 = other->field_A8;

    int i;
    for (i = 0; i < 16; ++i)
        if (field_F0C[i] == -1)
            break;
    if (i < 16) {
        int val = (int)idx;
        field_F0C[i] = val;
        int old = field_FA4;
        if (field_F0C[old] == otherIdx)
            field_FA4 = i;
        if (q->idle && field_FA8 == otherIdx)
            field_FA8 = val;
    }

    q->field_6C = 0;
    other->field_6C = 0;
    if (other->field_C0 == 0) {
        for (int k = 0; k < 16; ++k) {
            int v2 = field_F0C[k] * 0xf0;
            if (other == (anim_query*)((char*)this + v2 + 8))
                Remove(k);
        }
    } else {
        other->Set670(q->idle ? 0 : 1, 0);
    }
}

// @ 0x00a01f10
void anim_qb::Foo(int a, int b)
{
    anim_query* q = qb_get(this, a);
    if (q)
        Ret(q, b);
}

// @ 0x00a01f40
void anim_qb::Update(float dt, bool b, int a, int c)
{
    field_FB4 = 0.0f;
    field_FB8 = 0.0f;
    float w = field_FC4;
    float notW = 0.0f;
    if (b) {
        w = w - dt;
        if (w < 0.0f)
            w = 0.0f;
        field_FC4 = w;
    } else {
        w = w + dt;
        if (w > g_1550b78)
            w = g_1550b78;
        field_FC4 = w;
    }
    if (g_1550b78 > 0.0f && dt > 0.0f) {
        float t = f_9b01e0(0.0f, g_1550b78, w);
        notW = 1.0f - t;
        field_FAC = (w > 0.0f);
    } else {
        if (!b) {
            notW = 0.0f;
            field_FC4 = g_1550b78;
            field_FAC = true;
        } else {
            notW = 1.0f;
            field_FC4 = 0.0f;
            field_FAC = false;
        }
    }

    if (*(char*)((char*)p_anim_cid + 0x261) == 0) {
        float x = field_FC8 + dt;
        if (x > g_1550b74)
            x = g_1550b74;
        field_FC8 = x;
    } else {
        field_FC8 = 0.0f;
    }
    field_FB0 = f_9b01e0(0.0f, g_1550b74, field_FC8);

    field_F8C = 0;
    field_F90 = 0;
    field_F94 = 0;
    field_F98 = 0;

    for (int i = 0; i < 16; ++i) {
        int qi = field_F0C[i];
        if ((unsigned)qi < 16) {
            anim_query& qq = queries[qi];
            if (qq.field_0 != 0 ||
                ((unsigned)qq.field_68 < 8 && qq.anims[qq.field_68].animID != 0)) {
                qq.field_94 = 0.0f;
                qq.field_98 = 0.0f;
                if (qq.field_6C != 0)
                    UpdateQuery(qq.field_6C, dt);
                if (qq.field_0 != 0) {
                    if (qq.field_C0 == 0)
                        D50(i, c);
                    if (qq.field_C0 != 0) {
                        float f = 1.0f;
                        if (qq.field_C0 == 1) {
                            float x = qq.blendInTime;
                            f = (x > 0.0f) ? f_9b01e0(0.0f, x, qq.field_C4) : 0.0f;
                            f = 1.0f - f;
                        } else if (qq.field_C0 == 3) {
                            float x = qq.field_78;
                            f = (x > 0.0f) ? f_9b01e0(0.0f, x, qq.field_C4) : 0.0f;
                        }
                        f = qq.field_90 * qq.field_8C * f;
                        if (f < g_15517d0)
                            f = 0.0f;
                        qq.field_94 = f;
                        qq.field_98 = f * notW;
                        field_FB4 += f;
                        field_FB8 += qq.field_98;
                        float r = f_9a2c90(qq.field_0, dt, field_FAC, 1);
                        qq.field_B8 = r;
                        qq.field_A8 = qq.field_A8 + dt;
                    }
                }
            } else {
                Remove(i);
            }
        } else {
            Remove(i);
        }
    }

    f_9b3bc0(p_anim_cid);

    for (int i = 0; i < 16; ++i) {
        int qi = field_F0C[i];
        if ((unsigned)qi < 16) {
            anim_query& qq = queries[qi];
            if (qq.field_0 != 0 && qq.field_C0 != 0) {
                if (!field_FAC || qq.field_94 <= 0.0f) {
                    qq.field_9C = false;
                } else {
                    f_99e110(qq.field_94, p_anim_cid, qq.field_0, 1, 0, qq.field_9C ? 0 : 1);
                    qq.field_9C = true;
                }
                if (!(char)c || qq.field_98 <= 0.0f || qq.field_4 == 0) {
                    qq.field_9D = false;
                } else {
                    RefObj* o = qq.field_4;
                    o->Acac0(o->Ac2b0() * qq.field_B8, p_anim_cid, qq.field_0, qq.field_98, 1, 0,
                             qq.field_9D ? 0 : 1);
                    qq.field_9D = true;
                }
            }
        }
    }

    f_9bb910(p_anim_cid);
}

// @ 0x00a02440
bool anim_qb::Bar(int param)
{
    anim_query* q = qb_get(this, param);
    if (q != 0) {
        if (q->field_6C == 0)
            return true;
        while ((unsigned int)q->field_68 < 8) {
            void* p = *(void**)((char*)q + 8 + q->field_68 * 12);
            int out = 0;
            if (!f_9a38f0(*(void**)p_anim_cid, (int)p, &out)) {
                int r = f_9a4430(0, (int)p, 0);
                if (r != 0) {
                    ((CObj*)r)->T660();
                    int r2 = f_9a4550(*(void**)p_anim_cid, r);
                    if (r2 != 0) {
                        ((CObj*)r)->T060();
                        if (out != 0)
                            ((CObj*)out)->T0b0();
                        UpdateQuery((uint32_t)param, 0.0f);
                        return true;
                    }
                    ((CObj*)r)->T060();
                }
            } else if (out != 0) {
                ((CObj*)out)->T0b0();
                UpdateQuery((uint32_t)param, 0.0f);
                return true;
            }
            q->field_68 = q->field_68 + 1;
            if (out != 0)
                ((CObj*)out)->T0b0();
        }
    }
    return false;
}

// @ 0x00a02530
extern "C" int __cdecl RaySlab(float* p, float* d, float* o, float* m, float ex, float ey, float ez, float* tMax, float* nrm)
{
    float half[3];
    half[0] = ex * 0.5f;
    half[1] = ey * 0.5f;
    half[2] = ez * 0.5f;
    float tFar = -3.402823466e+38F;
    float tNear = 3.402823466e+38F;
    for (unsigned int j = 0; j < 6; ++j) {
        unsigned int ax = j >> 1;
        float sgn = (j & 1) ? 1.0f : -1.0f;
        float m0 = m[ax] * sgn;
        float m1 = m[3 + ax] * sgn;
        float m2 = m[6 + ax] * sgn;
        float denom = d[2] * m2 + d[1] * m1 + d[0] * m0;
        float t;
        if (denom >= -1e-06f && denom <= 1e-06f) {
            t = 3.402823466e+38F;
        } else {
            float dotO = o[2] * m2;
            dotO = dotO + o[1] * m1;
            dotO = dotO + o[0] * m0;
            t = half[ax] - dotO;
            t = t + p[2] * m2;
            t = t + p[1] * m1;
            t = t + p[0] * m0;
            t = t * (-1.0f / denom);
        }
        if (denom < 0.0f) {
            if (t < tNear)
                tNear = t;
        } else {
            if (tFar < t) {
                tFar = t;
                if (nrm) {
                    nrm[0] = -m0;
                    nrm[1] = -m1;
                    nrm[2] = -m2;
                }
            }
        }
    }
    if (tMax)
        *tMax = tFar;
    return (tNear - tFar) > 1e-06f;
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

// @ 0x00a027a0
bool __stdcall IsOrientIdleAnim(uint32 id)
{
    if (id != 0x4866d8e && id != 0x452b634 && id != 0x5cb2176) {
        if (!IsOrientStopAnim(id) &&
            id != 0x4866dab && id != 0x5cb2177 && id != 0x44828e9 &&
            id != 0x4482906 && id != 0x452b64a)
            return false;
    }
    return true;
}

// @ 0x00a02800
bool __stdcall IsRestIdleAnim(uint32 id)
{
    if (id != 0x2481de5 && id != 0x27844ad && id != 0x4330667 && id != 0x5b6ddae) {
        if (!IsOrientIdleAnim(id))
            return false;
    }
    return true;
}

// @ 0x00a02840
bool __stdcall IsMoveIdleAnim(uint32 id)
{
    if (id == 0x2481de6 || id == 0x354559b || id == 0x35455a4 ||
        id == 0x4485a08 || id == 0x4485a0f)
        return true;
    return false;
}

// @ 0x00a02a00
void __thiscall cAnimatingCreature_s00a0_27a0::Forward(int a, int b, int c)
{
    Forward3(table, a, b, c);
}

// @ 0x00a02ab0
bool __thiscall cAnimatingCreature_s00a0_27a0::Attach(int v)
{
    void* p = v ? FindSlot(table, (uint32)v) : RootSlot(table);
    if (p)
        table->Detach(p, 0);
    return true;
}

// @ 0x00a02b00
bool __thiscall cAnimatingCreature_s00a0_27a0::Detach(int v)
{
    table->Remove(v);
    return true;
}

// @ 0x00a02b40
bool __thiscall cAnimatingCreature_s00a0_27a0::QueryA(int v)
{
    if (table)
        return QuerySlotA(table, v, 0);
    return false;
}

// @ 0x00a02b70
bool __thiscall cAnimatingCreature_s00a0_27a0::QueryB(int v)
{
    if (table) {
        bool found = QuerySlotB(table, v) != 0;
        return found;
    }
    return false;
}

// @ 0x00a02bd0
int __thiscall cAnimatingCreature_s00a0_27a0::Selector()
{
    int v = sel50[1];
    if (v == 4)
        v = sel50[0];
    return v;
}

// @ 0x00a02bf0
void __thiscall cAnimatingCreature_s00a0_27a0::SetMode(const int* v, uint8 b)
{
    f154 = (b != 0) + 1;
    f164 = v[0];
    f168 = v[1];
    f16c = v[2];
}

// @ 0x00a02c40
void __thiscall cAnimatingCreature_s00a0_27a0::SetRestIdleAnimHandle()
{
    for (uint32 i = 0; i < 16; i++) {
        if (table->live[i]) {
            uint32 idx = table->tbl[i];
            Node* n = &table->nodes[idx];
            if (n->id == 0x2481de5 || n->id == 0x27844ad || n->id == 0x4330667 || n->id == 0x5b6ddae ||
                IsOrientIdleAnim(n->id))
                f188 = PackHandle(n->value, (uint8)idx);
        }
    }
}

// @ 0x00a02cd0
uint8 __thiscall cAnimatingCreature_s00a0_27a0::Swap48(uint8 v)
{
    uint8 old = f48;
    f48 = v;
    return old;
}

// @ 0x00a02ce0
void __thiscall cAnimatingCreature_s00a0_27a0::Set38(uint8 a, int b, int c)
{
    f38 = a;
    f3c = b;
    f40 = c;
}

// @ 0x00a02d00
void __thiscall cAnimatingCreature_s00a0_27a0::SetSel(int i, int v)
{
    sel50[i] = v;
}

// @ 0x00a02d40
void __stdcall Forward5(int a, int b, int c, int d, int e)
{
    BigForward(a, b, c, d, e, 0);
}

// @ 0x00a02d70
void* __thiscall RootThunk::RootOnly(void* p)
{
    return RootSlot(p);
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

// @ 0x00a03da0
const float* FUN_00a03da0(void* target, const float* m, const float* pos, float scale)
{
	(void)target;
	g_softStateDirty |= 1;
	g_transformType = 2;
	g_transformPtr = g_transformLocal;

	float* d = g_transformLocal;
	d[0] = m[0] * scale; d[1] = m[3] * scale; d[2] = m[6] * scale; d[3] = m[0] * scale;
	d[4] = m[1] * scale; d[5] = m[4] * scale; d[6] = m[7] * scale; d[7] = m[1] * scale;
	d[8] = m[2] * scale; d[9] = m[5] * scale; d[10] = m[8] * scale; d[11] = m[2] * scale;
	d[12] = pos[0]; d[13] = pos[1]; d[14] = pos[2]; d[15] = pos[0];
	return m;
}

// @ 0x00a03e80
void FUN_00a03e80(DebugTarget* target, const float* m, const float* pos, float scale, const float* negOffset, const float* extents, uint32_t color, int arg8)
{
	FUN_00a03da0(target, m, pos, scale);

	void* verts;
	char aux[4];
	if (!LockVertices_006ddcc0(4, 0x18, &verts, aux))
		return;

	float basis[9];
	float center[3];
	basis[1] = 0.0f; basis[2] = 0.0f; basis[3] = 0.0f;
	basis[5] = 0.0f; basis[6] = 0.0f; basis[7] = 0.0f;
	basis[8] = 1.0f; basis[4] = 1.0f; basis[0] = 1.0f;
	center[0] = 0.0f; center[1] = 0.0f; center[2] = 0.0f;
	BuildBoxVertices_00a02da0(verts, basis, center, negOffset, extents, color);
	UnlockVertices_006ddd40(3, target, arg8);
}

// @ 0x00a03f50
void DrawBodyBoxes_00a03f50(DebugTarget* target, DebugBody* body, uint32_t color3, uint32_t color4, int arg5)
{
	float m[9];
	QuatToMatrix(m, body->m_qw, body->m_qx, body->m_qy, body->m_qz);
	FUN_00a03da0(target, m, body->m_pos, body->m_scale);

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

// @ 0x00a04550
void cAnimatingCreature_s00a0_3da0::FUN_00a04550(int index, const float* value)
{
	AnimBody* body = m_body;
	if (!body)
		return;
	float* data = (float*)body->m_data;
	if (!data)
		return;
	if ((unsigned)index >= 3)
		return;
	float* dst = data + index * 3 + 0xc9;
	dst[0] = value[0];
	dst[1] = value[1];
	dst[2] = value[2];
}

// @ 0x00a04590
float* FUN_00a04590(cAnimatingCreature_s00a0_3da0* self, float* out)
{
	int mode = self->m_mode54;
	if (mode == 4)
		mode = self->m_mode50;
	if (mode == 0)
	{
		out[0] = 1.0f; out[1] = 0.0f; out[2] = 0.0f; out[3] = 1.0f;
	}
	else if (mode == 1)
	{
		out[0] = 1.0f; out[1] = 0.0f; out[2] = 1.0f; out[3] = 1.0f;
	}
	else if (mode == 2)
	{
		out[0] = 0.0f; out[1] = 0.0f; out[2] = 1.0f; out[3] = 1.0f;
	}
	else
	{
		return (float*)(size_t)(mode - 2);
	}
	return out;
}

// @ 0x00a04630
void FUN_00a04630(cAnimatingCreature_s00a0_3da0* self, unsigned char param2, unsigned char param3)
{
	AnimBody* body = self->m_body;
	if (body->m_parts == 0)
	{
		RenderInst* inst = self->m_inst;
		if (inst != 0)
		{
			inst->m_x = body->m_px;
			inst->m_y = body->m_py;
			inst->m_z = body->m_pz;
			inst->m_flags |= 4;
			inst->m_dirty++;

			uint32_t quat[4];
			quat[0] = *(uint32_t*)&body->m_qw ^ g_posNegate;
			quat[1] = *(uint32_t*)&body->m_qx ^ g_posNegate;
			quat[2] = *(uint32_t*)&body->m_qy ^ g_posNegate;
			quat[3] = *(uint32_t*)&body->m_qz;

			float local[9];
			float* mat = FUN_009a46a0(local, (const float*)quat);
			for (int i = 0; i < 9; i++)
				inst->m_basis[i] = mat[i];
			inst->m_flags |= 2;
			inst->m_dirty++;
			inst->m_scale = body->m_scale;
			inst->m_dirty++;
		}
		return;
	}

	float blend[4];
	blend[0] = self->m_blendX;
	blend[1] = self->m_blendY;
	blend[2] = self->m_blendZ;
	blend[3] = self->m_blendW;
	unsigned char flag = self->m_flag84;
	int mode = self->m_mode54;
	if (mode == 4)
		mode = self->m_mode50;
	char* mgrpart = (char*)self->m_scene190 + 0x68;
	if (param2)
	{
		flag = 0;
		typedef float* (*BlendFn)(cAnimatingCreature_s00a0_3da0*, float*);
		BlendFn volatile blendFn = &FUN_00a04590;
		blendFn(self, blend);
	}
	float d = param3 ? 0.0f : blend[3];

	body->m_parts->FUN_009c6fc0(mgrpart,
	                            blend[0], blend[1], blend[2], d,
	                            mode == 2, mode > 0 ? 1 : 0, flag);
}

// @ 0x00a048b0
int cAnimatingCreature_s00a0_3da0::FUN_00a048b0(int id, int a3, int a4, int a5)
{
	void* e = FUN_009ff6f0(m_lookup184, id);
	void* result = 0;
	if (e != 0)
	{
		void* obj = *(void**)e;
		if (obj != 0 && *((uint32_t*)obj) != 0)
			result = *((void**)((char*)obj + 8));
	}
	if (result != 0)
		return FUN_0099d0b0(result, (void*)a3, (void*)a4, (void*)a5);
	return -1;
}

// @ 0x00a04900
bool cAnimatingCreature_s00a0_3da0::FUN_00a04900(int unused)
{
	(void)unused;
	bool result;
	LookupEntry* e = (LookupEntry*)FUN_009ff750(m_lookup184);
	if (e == 0)
	{
		result = true;
	}
	else
	{
		void* obj = e->m_obj;
		if (*(unsigned char*)((char*)obj + 0xac) == 0 && e->m_fieldC0 != 0)
			result = true;
		else
			result = false;
	}
	return result;
}

// @ 0x00a04940
bool cAnimatingCreature_s00a0_3da0::FUN_00a04940(int id)
{
	LookupEntry* e = id ? (LookupEntry*)FUN_009ff6f0(m_lookup184, id)
	                    : (LookupEntry*)FUN_009ff750(m_lookup184);
	if (e != 0 && e->m_obj != 0)
	{
		if (e->m_fieldC0 == 3)
			return true;
		return false;
	}
	return true;
}

// @ 0x00a04990
bool cAnimatingCreature_s00a0_3da0::FUN_00a04990(int id)
{
	LookupEntry* e = id ? (LookupEntry*)FUN_009ff6f0(m_lookup184, id)
	                    : (LookupEntry*)FUN_009ff750(m_lookup184);
	if (e != 0 && *(uint32_t*)e != 0)
	{
		if (*(float*)((char*)e + 0xa0) == g_minusOne)
			return true;
	}
	return false;
}

// @ 0x00a049f0
float cAnimatingCreature_s00a0_3da0::FUN_00a049f0(int id)
{
	float out = 0.0f;
	LookupEntry* e = id ? (LookupEntry*)FUN_009ff6f0(m_lookup184, id)
	                    : (LookupEntry*)FUN_009ff750(m_lookup184);
	if (e && e->m_obj)
	{
		void* obj = e->m_obj;
		double f = *(double*)((char*)obj + 0xb0) / *(double*)((char*)obj + 0xb8);
		double ipart;
		double frac = modf(f, &ipart);
		if ((float)f < 0.0f)
			frac = 1.0 - frac;
		int whole = *(int*)((char*)e + 0xb0);
		double sum = (double)whole;
		if (whole < 0)
			sum += g_uintToFloat;
		sum += frac;
		out = (float)sum;
	}
	return out;
}

// @ 0x00a04ab0
void cAnimatingCreature_s00a0_3da0::FUN_00a04ab0(unsigned char value)
{
	AnimBody* body = m_body;
	if (!body)
		return;
	body->m_field168d = value;
}

// @ 0x00a04ad0
void cAnimatingCreature_s00a0_3da0::FUN_00a04ad0(int value)
{
	AnimBody* body = m_body;
	if (!body)
		return;
	body->m_field1684 = value;
}

// @ 0x00a04af0
void cAnimatingCreature_s00a0_3da0::FUN_00a04af0(IUnknown_s00a0_3da0* model)
{
	AssignModel(m_inst, model);

	AnimBody* body = m_body;
	if (!body)
		return;
	PartList* parts = body->m_parts;
	if (!parts)
		return;
	unsigned count = (unsigned)((parts->m_end - parts->m_begin) / 0x14);
	if (count == 0)
		return;
	for (unsigned i = 0; i < count; i++)
	{
		PartSlot* slot = (PartSlot*)(m_body->m_parts->m_begin + i * 0x14);
		AssignModel((RenderInst*)slot->m_inst, model);
	}
}

// @ 0x00a04bb0
void cAnimatingCreature_s00a0_3da0::FUN_00a04bb0(unsigned index, unsigned char enable)
{
	RenderInst* inst = m_inst;
	if (!inst)
		return;

	if (index < 0x40)
	{
		uint32_t bit = 1u << (index & 0x1f);
		uint32_t* word = &inst->m_bits0 + (index >> 5);
		if (enable)
			*word |= bit;
		else
			*word &= ~bit;
	}

	AnimBody* body = m_body;
	if (!body)
		return;
	PartList* parts = body->m_parts;
	if (!parts)
		return;
	unsigned count = (unsigned)((parts->m_end - parts->m_begin) / 0x14);
	if (count == 0)
		return;
	for (unsigned i = 0; i < count; i++)
	{
		PartSlot* slot = (PartSlot*)(parts->m_begin + i * 0x14);
		RenderInst* child = (RenderInst*)slot->m_inst;
		if (!child)
			continue;
		if (index < 0x40)
		{
			uint32_t bit = 1u << (index & 0x1f);
			uint32_t* word = &child->m_bits0 + (index >> 5);
			if (enable)
				*word |= bit;
			else
				*word &= ~bit;
		}
		child->m_flags &= ~8;
	}
}

// @ 0x00a04ca0
void cAnimatingCreature_s00a0_3da0::FUN_00a04ca0(unsigned char value)
{
	AnimBody* body = m_body;
	body->m_field2d4 = value;
}

// @ 0x00a04cc0
void cAnimatingCreature_s00a0_3da0::FUN_00a04cc0(unsigned char value)
{
	AnimBody* body = m_body;
	body->m_field2d5 = value;
}

// @ 0x00a04d20
bool cAnimatingCreature_s00a0_4d20::ClosestBodyPosition(const Vector3& query, Vector3& out)
{
    RigidBody* body = mRegionObj;
    BodyShapeEntry* b = body->begin;
    BodyShapeEntry* e = body->end;
    BodyShapeEntry* best = 0;
    float bestDist = g_maxFloat;
    if (b != e) {
        float qw = body->quat[0];
        float qx = body->quat[1];
        float qy = body->quat[2];
        float qz = body->quat[3];
        float px = body->pos[0];
        float py = body->pos[1];
        float pz = body->pos[2];
        for (;;) {
            float ox = b->off[0];
            float oy = b->off[1];
            float oz = b->off[2];
            float dx = query.x - (px +
                        ((ox * (-(qy * qy) - (qx * qx)) + oy * (qx * qw - qy * qz)) +
                         oz * (qy * qw + qx * qz)) * g_two + ox);
            float dz = query.z - (pz +
                        ((ox * (qy * qw - qx * qz) + oy * (qy * qx + qw * qz)) +
                         oz * (-(qx * qx) - (qw * qw))) * g_two + oz);
            float dy = query.y - (py +
                        ((ox * (qx * qw + qy * qz) + oy * (-(qy * qy) - (qw * qw))) +
                         oz * (qy * qx - qw * qz)) * g_two + oy);
            float d = (dy * dy + dz * dz) + dx * dx;
            if (best == 0 || d < bestDist) {
                best = b;
                bestDist = d;
            }
            b = (BodyShapeEntry*)((char*)b + 0x2bc);
            if (b == e) break;
        }
        if (best != 0) {
            RigidBody* body2 = mRegionObj;
            float qw2 = body2->quat[0];
            float qx2 = body2->quat[1];
            float qy2 = body2->quat[2];
            float qz2 = body2->quat[3];
            float sx = best->off[0];
            float sy = best->off[1];
            float sz = best->off[2];
            out.x = ((sx * (-(qy2 * qy2) - (qx2 * qx2)) +
                      sz * (qy2 * qw2 + qx2 * qz2) +
                      sy * (qx2 * qw2 - qy2 * qz2)) * g_two + sx) + body2->pos[0];
            out.y = ((sx * (qx2 * qw2 + qy2 * qz2) +
                      sy * (-(qy2 * qy2) - (qw2 * qw2)) +
                      sz * (qy2 * qx2 - qw2 * qz2)) * g_two + sy) + body2->pos[1];
            out.z = ((sx * (qy2 * qw2 - qx2 * qz2) +
                      sy * (qy2 * qx2 + qw2 * qz2) +
                      sz * (-(qx2 * qx2) - (qw2 * qw2))) * g_two + sz) + body2->pos[2];
            return true;
        }
    }
    return false;
}

// @ 0x00a05150
void cAnimatingCreature_s00a0_4d20::GetCurrentAnimation(uint32_t* outIdx, float* outTime, int* outValue, int* outFlags)
{
    AnimGoalInfo* g = FUN_009ff750_s00a0_4d20(mBlender);
    if (g == 0) return;
    if (outIdx != 0) *outIdx = g->fD8;
    if (outFlags != 0) *outFlags = FUN_009fef90(mBlender, g);
    if (g->p0 != 0) {
        if (outTime != 0) *outTime = (float)g->timeA8;
        if (outValue != 0) *outValue = (int)g->fB0;
    }
}

// @ 0x00a051c0
bool cAnimatingCreature_s00a0_4d20::GetGoalTimes(uint32_t handle, float* outTime, float* outValue)
{
    AnimGoalInfo* g = FUN_009ff6f0_s00a0_4d20(mBlender, handle);
    if (g == 0) return false;
    if (g->flag6c != 0) return false;
    if (outTime != 0) *outTime = (float)g->p0->vB8;
    if (outValue != 0) *outValue = (float)g->timeA8;
    return true;
}

// @ 0x00a05220
void cAnimatingCreature_s00a0_4d20::MarkWorldRegion(bool force)
{
    if (force || mWorldRegion < mViewer->region) {
        if (mRegionObj != 0) {
            FUN_009bd340(mRegionObj);
            mRegionObj->dirtyFlag = 1;
        }
        mWorldRegion = mViewer->region;
    }
}

// @ 0x00a05270
int cAnimatingCreature_s00a0_4d20::Release()
{
    int n = mRefCount - 1;
    int z = 0;
    int* p = (n > 0) ? &n : &z;
    int v = *p;
    mRefCount = v;
    if (v > 0) return v;
    mRefCount = 1;
    if (mRegionObj != 0) {
        AnimViewer* vw = mViewer;
        if (vw != 0) {
            ((void(__thiscall*)(void*, cAnimatingCreature_s00a0_4d20*))((*(void***)vw)[0x3c / 4]))(vw, this);
        }
    }
    ((void(__thiscall*)(cAnimatingCreature_s00a0_4d20*, int))vtbl[0x7c / 4])(this, 1);
    return 0;
}

// @ 0x00a052e0
float AnimProgress(void* animObj)
{
    float raw = FUN_009d3530((char*)animObj + 0x15b8);
    float frac = raw / *(float*)(*(char**)animObj + 0x3ec);
    if (!(frac > 0.0f)) frac = 0.0f;
    if (frac > 1.0f) frac = 1.0f;
    float p = (float)FUN_011e08f0((double)frac);
    float s = (float)sin(p * g_piOver2);
    if (!(s > g_tiny)) return 0.0f;
    return s;
}

// @ 0x00a05360
void cAnimatingCreature_s00a0_4d20::UpdateGoalFade()
{
    AnimGoalInfo* prev = 0;
    AnimGoalInfo* cur = 0;
    if (mPrevGoal != 0) {
        prev = FUN_009ff6f0_s00a0_4d20(mBlender, mPrevGoal);
        if (prev != 0) FUN_009fef50(prev, 0.0f);
    }
    if (mCurGoal != 0) {
        cur = FUN_009ff6f0_s00a0_4d20(mBlender, mCurGoal);
        if (cur != 0) FUN_009fef50(cur, 1.0f);
    }
    if (mCurGoal != mPrevGoal && cur != 0 && prev != 0 && cur->zeroC0 != 0) {
        float t = AnimProgress(mRegionObj);
        FUN_009fef50(cur, 1.0f - t);
        FUN_009fef50(prev, t);
        AnimGoalInfo* g = prev->p0;
        if (g != 0) {
            void* gd = (void*)((char*)mRegionObj + 0x15b8);
            void* pol = Sim_GetPoliticalID(gd);
            FUN_00c373d0();
            float f = 0.0f;   // result of the above is in st0 in the original
            g->fB0 = (uint32_t)(f * g->vB8);
        }
        FUN_009fef20(prev, cur);
    }
}

// @ 0x00a054a0
char WrappedAnim::SetFlagFromProperty(bool value)
{
    char old = mFlag3038;
    void* iface = *(void**)((char*)mOwner + 0x50);
    var_t* var = (var_t*)(*(void*(__thiscall**)(void*, uint32_t))(*(void***)iface + 10))(iface, 0xf0a16bfc);
    char* p;
    uint16_t ty = var->type;
    if (ty == 1 || ty == 0x10) {
        if ((var->flags & 0x30) != 0) p = *(char**)var;
        else p = (ty != 0) ? (char*)var : 0;
    } else {
        p = (char*)0x15d115d;
    }
    if (*p != 0) {
        mFlag3038 = value;
        return old;
    }
    mFlag3038 = 1;
    return old;
}

// @ 0x00a05510
bool WrappedAnim::InitThing(void* attachments, uint8_t a, uint32_t b, uint8_t c, uint8_t d)
{
    void* old = mAttachments;
    if (attachments != old) {
        if (attachments != 0) ((void(__thiscall**)(void*))*(void***)attachments)[0](attachments);
        mAttachments = attachments;
        if (old != 0) ((void(__thiscall**)(void*))*(void***)old)[1](old);
    }
    f48 = a;
    mCount0 = 0;
    mCount1 = 0;
    mChosen = 0;
    mFlag3039 = c;
    mFlag303a = d;
    return true;
}

// @ 0x00a055a0
int AnimPimpl::GetStateA()
{
    void* p = impl;
    if (p != 0) return ((int(__thiscall**)(void*, int))*(void***)p)[0x24 / 4](p, 0);
    return -1;
}

// @ 0x00a055c0
int AnimPimpl::GetStateB(int a1, int a2)
{
    void* p = impl;
    if (p != 0) return ((int(__thiscall**)(void*, int, int))*(void***)p)[0x30 / 4](p, a1, a2);
    return -1;
}

// @ 0x00a055e0
int AnimPimpl::GetStateC(int a1, int a2)
{
    void* p = impl;
    if (p != 0) {
        if (((bool(__thiscall**)(void*, int, int))*(void***)p)[0x38 / 4](p, a1, a2)) return a2;
    }
    return -1;
}

// @ 0x00a05610
int AnimPimpl::GetStateD()
{
    void* p = impl;
    if (p != 0) return ((int(__thiscall**)(void*))*(void***)p)[0x2c / 4](p);
    return -1;
}

// @ 0x00a05660
int GoalList::SelectFor(void* owner, int index, char useIndex)
{
    char* o = (char*)owner;
    int chosen = 0;
    if (useIndex) {
        *(int*)(o + 0x54) = index;
        ++mCounts[index];
        chosen = index;
    }
    if (index >= 0) {
        int* slot = &mSlots[index];
        for (;;) {
            if (slot[3] < *slot || index == 0) {
                *(int*)(o + 0x50) = index;
                if (!useIndex) {
                    ++mCounts[index];
                    chosen = *(int*)(o + 0x50);
                }
                break;
            }
            --index;
            --slot;
            if (index < 0) break;
        }
    }
    if (chosen != 0 && chosen != *(int*)(o + 0x58)) {
        char* rb = *(char**)(o + 0x17c);
        FUN_009b3920((const float*)(rb + 0x18), (const float*)(rb + 0x3c));
    }
    *(int*)(o + 0x58) = chosen;
    return chosen;
}

// @ 0x00a056e0
void* GetGlobalThing()
{
    return g_thingFlag ? (void*)&g_thingData : 0;
}

// @ 0x00a056f0
void** StaticDataSlot::SwapStaticData(CreatureStaticData** src)
{
    CreatureStaticData* nv = *src;
    CreatureStaticData* ov = p;
    if (nv != ov) {
        if (nv != 0) nv->AddRef();
        p = nv;
        if (ov != 0) ov->Release();
    }
    return (void**)this;
}

// @ 0x00a05730
void* RBTreeHead::FindLower(void** outNode, uint32_t* key)
{
    char* sentinel = (char*)this + 4;
    char* pos = sentinel;
    char* node = root;
    if (node != 0) {
        uint32_t klo = key[0];
        uint32_t khi = key[1];
        for (;;) {
            uint32_t nhi = *(uint32_t*)(node + 0x14);
            uint32_t nlo;
            if (nhi < khi) {
                node = *(char**)node;
            } else if (nhi > khi) {
                pos = node;
                node = *(char**)(node + 4);
            } else if ((nlo = *(uint32_t*)(node + 0x10)) < klo) {
                node = *(char**)node;
            } else {
                pos = node;
                node = *(char**)(node + 4);
            }
            if (node == 0) break;
        }
    }
    char* result = sentinel;
    if (pos != sentinel) {
        uint32_t klo = key[0];
        uint32_t khi = key[1];
        uint32_t phi = *(uint32_t*)(pos + 0x14);
        if (khi > phi || (khi == phi && klo >= *(uint32_t*)(pos + 0x10))) {
            *outNode = pos;
            return outNode;
        }
    }
    *outNode = result;
    return outNode;
}

// @ 0x00a057a0
bool CallbackPair::SetCallbackPair(void* newObj)
{
    void (*oldFn)(void*);
    void* oldArg;
    if (newObj != 0) {
        void** vt = *(void***)newObj;
        ((void(__thiscall*)(void*))vt[1])(newObj);
        oldFn = *(void(**)(void*))((char*)this + 0x24);
        oldArg = *(void**)((char*)this + 0x20);
        *(void**)((char*)this + 0x20) = newObj;
        *(void**)((char*)this + 0x24) = (void*)FUN_00a02d80;
    } else {
        oldFn = *(void(**)(void*))((char*)this + 0x24);
        oldArg = *(void**)((char*)this + 0x20);
        *(void**)((char*)this + 0x20) = 0;
        *(void**)((char*)this + 0x24) = 0;
    }
    if (oldFn != 0) oldFn(oldArg);
    return true;
}

// @ 0x00a057f0
void* RBTreeHead::FindRaw(void** outNode, uint32_t* key)
{
    char* sentinel = (char*)this + 4;
    char* pos = sentinel;
    char* node = root;
    if (node != 0) {
        uint32_t klo = key[0];
        uint32_t khi = key[1];
        for (;;) {
            uint32_t nhi = *(uint32_t*)(node + 0x14);
            if (nhi < khi) {
                node = *(char**)node;
            } else if (nhi > khi) {
                pos = node;
                node = *(char**)(node + 4);
            } else if (*(uint32_t*)(node + 0x10) < klo) {
                node = *(char**)node;
            } else {
                pos = node;
                node = *(char**)(node + 4);
            }
            if (node == 0) break;
        }
    }
    *outNode = pos;
    return outNode;
}

// @ 0x00a05830
Vec28* Vec28::Construct(int count, int unused)
{
    (void)unused;
    void* p = 0;
    if (count != 0) {
        p = FUN_00f473a0(count * 0x1c, "EASTL", 0, 0,
                         "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                         0xd1);
    }
    this->begin = p;
    this->end = p;
    this->cap = (char*)p + count * 0x1c;
    return this;
}

// @ 0x00a05890
void* RotationAtoBWrap(void* out, float* a, float* b, uint32_t p4, uint32_t p5)
{
    float nb[3];
    nb[0] = a[0]; nb[1] = a[1]; nb[2] = a[2];
    float lb = (float)sqrt((double)(nb[2] * nb[2] + nb[1] * nb[1] + nb[0] * nb[0]));
    if (lb != 0.0f) {
        float inv = g_one / lb;
        nb[0] *= inv; nb[1] *= inv; nb[2] *= inv;
    }
    float na[3];
    na[0] = b[0]; na[1] = b[1]; na[2] = b[2];
    float la = (float)sqrt((double)(na[2] * na[2] + na[1] * na[1] + na[0] * na[0]));
    if (la != 0.0f) {
        float inv = g_one / la;
        na[0] *= inv; na[1] *= inv; na[2] *= inv;
    }
    FUN_009edb70((Vector4*)out, nb, na, p4, p5);
    return out;
}

// @ 0x00a059d0
namespace SP {
void DoAnimationPreload(cSPCreatureAnimManager * a1)
{
    uint32_t* obj = 0;
    void* pm = SP_PropertyManager();
    (*(void(__thiscall**)(void*, uint32_t, int, uint32_t**))(*(void***)pm + 0x2c / 4))(pm, 0x5de9bcff, 0, &obj);
    if (obj == 0) return;
    uint32_t* data = 0;
    uint32_t count = 0;
    if (SP_GetPropertyAsUint32Array(obj, 0xacdab823, &data, &count)) {
        for (int i = 0; i < (int)count; ++i) {
            (*(void(__thiscall**)(void*, uint32_t))(*(void***)obj + 0x44 / 4))(obj, data[i]);
        }
    }
    (*(void(__thiscall**)(void*))(*(void***)obj + 1))(obj);
}
}  // namespace SP

// @ 0x00a05a70
void cAnimatingCreature_s00a0_4d20::ApplyAnimState(uint32_t mode)
{
    (void)mode;
    if (mViewer == 0) return;
    void* iface = *(void**)((char*)mViewer + 0x50);
    if (iface == 0) return;

    var_t* var = (var_t*)(*(void*(__thiscall**)(void*, uint32_t))(*(void***)iface + 10))(iface, 0xc2dafabb);
    uint16_t ty = var->type;
    char* p;
    if (ty == 9 || ty == 0x10) {
        if ((var->flags & 0x30) != 0) p = *(char**)var;
        else p = (ty != 0) ? (char*)var : 0;
    } else {
        p = (char*)0x15d9c68;
    }
    int32_t cur = *(int32_t*)p;

    if (cur == 1) {
        var_t v1;
        Variant_SetU32(&v1, 0);
        (*(void(__thiscall**)(void*, uint32_t, var_t*))(*(void***)iface + 5))(iface, 0xc2dafabb, &v1);
        if ((v1.flags & 4) != 0) Variant_Destruct(&v1, false);
        var_t v2;
        Variant_SetU32(&v2, 0);
        (*(void(__thiscall**)(void*, uint32_t, var_t*))(*(void***)iface + 5))(iface, 0xda61d1c, &v2);
        if ((v2.flags & 4) != 0) Variant_Destruct(&v2, false);
    } else {
        var_t v1;
        Variant_SetU32(&v1, 1);
        (*(void(__thiscall**)(void*, uint32_t, var_t*))(*(void***)iface + 5))(iface, 0xc2dafabb, &v1);
        if ((v1.flags & 4) != 0) Variant_Destruct(&v1, false);
        var_t v2;
        Variant_SetU32(&v2, 0xffffffff);
        (*(void(__thiscall**)(void*, uint32_t, var_t*))(*(void***)iface + 5))(iface, 0xda61d1c, &v2);
        if ((v2.flags & 4) != 0) Variant_Destruct(&v2, false);
    }
}

// @ 0x00a05c20
void __cdecl RegisterCreature(anim_creature_s00a0_5c20* ac)
{
    void* model = ac->instance->model;
    if (model != 0) {
        ac->f180 = (RefObj_s00a0_5c20*)*(uint32_t*)((char*)model + 8);
        return;
    }
    if (ac->f180 != 0)
        return;

    Creator* creator = *(Creator**)((char*)ac->world + 0x44);
    ac->f180 = creator->Create(0x2ebcd6a6u, 0xd94352edu, 0);
    ac->f180->refcount++;
    if (ac->f180 == 0)
        return;

    ac->f180->flags |= 0x200;
    ac->f180->box.Reset();

    AnimData* data = *(AnimData**)ac->instance;

    Vector3_s00a0_5c20 mn, mx;
    mn.x = data->minx;
    mn.y = data->miny;
    mn.z = data->minz;
    mx.x = data->sizeX + data->minx;
    mx.y = data->sizeY + data->miny;
    mx.z = data->sizeZ + data->minz;

    ac->f180->box.Extend(mn);
    ac->f180->box.Extend(mx);
    ac->f180->f6c = data->f370 * g_half;
}

// @ 0x00a05d60
anim_creature_s00a0_5c20::anim_creature_s00a0_5c20(const Vector3_s00a0_5c20& pos, const Vector4_s00a0_5c20& rot)
{
    *(void**)this = (void*)s_animCreatureVtbl;

    mPos = pos;
    mRot = rot;

    f3c  = 1.0f;
    f40  = 0.0f;
    f44  = 0.0f;
    f48  = 0.0f;
    f4c  = 0.0f;
    f50  = 0;
    f54  = 4;
    f58  = 0;
    f64  = 1;
    slots[3] = g_f1;
    slots[4] = g_f2;
    slots[5] = g_f3;
    slots[6] = g_f4;
    f84  = 0;
    f88  = 1;
    {
        int32_t* p = (int32_t*)arr8c;
        for (int i = 15; i >= 0; --i) {
            p[0] = -1;
            p[1] = -1;
            p[2] = 0;
            p += 3;
        }
    }
    f150 = 1;
    f154 = 1;
    f14c = 0;
    f151 = 0;
    f158 = 0;
    f15c = 0;
    f160 = 0;
    _ReadWriteBarrier();
    f164 = 0.0f;
    f168 = -10.0f;
    f16c = 1.0f;
    f170 = 0;
    f174 = -1;
    f178 = 0;
    instance = 0;
    _ReadWriteBarrier();
    f180 = 0;
    blender = 0;
    f188 = 0;
    f18c = 0;
    f194 = 0;
    f198 = 0;
}

// @ 0x00a05ee0
uint __cdecl GetFeedbackRecords(uint key, uint unused, OutRec* out, uint maxCount, uint* outTime)
{
    FeedbackNode* it;
    g_feedbackTree.find(&it, &key);

    if (out == 0 || it == &g_feedbackEnd)
        return 0;

    uint n = (uint)(it->end - it->begin);
    uint pick = 0;
    if (n > 1) {
        double r = g_rng.GenerateDouble();
        for (uint i = 0; i < n; ++i) {
            if (r < it->begin[i].time) {
                pick = i;
                break;
            }
        }
    }

    FeedbackEvent* e = it->begin + pick;
    uint count = (uint)(e->end - e->begin);
    uint num   = maxCount < count ? maxCount : count;

    for (uint i = 0; i < num; ++i) {
        out[i].z = (int32_t)e->begin[i].f8;
        out[i].y = e->begin[i].f4;
        out[i].x = e->begin[i].f0;
    }

    if (outTime != 0)
        *outTime = g_feedbackTime[5];

    return num;
}

// @ 0x00a060a0
float anim_creature_s00a0_5c20::GetFeedbackValue(uint key)
{
    FeedbackNode* it;
    g_feedbackTree.find(&it, &key);

    if (it == &g_feedbackEnd)
        return 0.0f;

    uint n = (uint)(it->end - it->begin);
    if (n != 1)
        return 0.0f;

    FeedbackEvent* e = it->begin;
    uint cnt = (uint)(e->end - e->begin);
    if (cnt == 0)
        return 0.0f;

    for (uint i = 0; i < cnt; ++i) {
        FeedbackRecord* rec = e->begin + i;
        FbHandle* p = 0;
        bool ok = LookupA(*(void**)instance, rec->f8, (void**)&p);
        if (!ok) {
            XC_s00a0_5c20* o = (XC_s00a0_5c20*)LookupB(0, rec->f8, 0);
            if (o != 0) {
                o->Prepare();
                if (LookupC(*(void**)instance, o) != 0) {
                    o->Release();
                    if (p != 0) p->Release();
                } else {
                    o->Release();
                    if (p != 0) p->Release();
                    continue;
                }
            } else {
                if (p != 0) p->Release();
                continue;
            }
        } else {
            if (p != 0) p->Release();
        }

        float level = rec->f4;
        if (level >= g_zero)
            return rec->f0 * level;

        XC_s00a0_5c20* o2 = (XC_s00a0_5c20*)LookupB(0, rec->f8, 0);
        if (o2 == 0)
            return 0.0f;
        o2->Prepare();
        float v = (o2->f120 - g_one_s00a0_5c20) * o2->f11c * rec->f0;
        o2->Release();
        return v;
    }
    return 0.0f;
}

// @ 0x00a06250
void anim_creature_s00a0_5c20::SetTargetRoot(anim_creature_s00a0_5c20* target)
{
    f154 = 0;
    f158 = 1;
    anim_creature_s00a0_5c20* old = f15c;
    if (target != old) {
        if (target != 0)
            target->f198++;
        f15c = target;
        if (old != 0)
            old->Release();
    }
    f160 = 0;
}

// @ 0x00a062a0
void anim_creature_s00a0_5c20::SetTargetBody(anim_creature_s00a0_5c20* target, uint value)
{
    f154 = 0;
    f158 = 2;
    anim_creature_s00a0_5c20* old = f15c;
    if (target == old) {
        f160 = value;
        return;
    }
    if (target != 0)
        target->f198++;
    f15c = target;
    if (old != 0)
        old->Release();
    f160 = value;
}

// @ 0x00a06310
void AnimWorld_s00a0_5c20::UpdateAutoBaking(float dt, cViewer_s00a0_5c20* viewer)
{
    AnimWorld_s00a0_5c20* world = this;
    if (world->mpBegin == world->mpEnd)
        return;

    PropHolder* props = (PropHolder*)((char*)world->mManager + 0x50);

    Variant* dv = props->GetProperty(0xf29f5604u);
    float dtScale;
    {
        uint16_t t = dv->mType;
        float* p;
        if (t == 0xd || t == 0x10)
            p = (dv->mFlags & 0x30) ? (float*)dv->mValue : (t ? (float*)dv : 0);
        else
            p = &g_variantFloatDefault;
        dtScale = *p;
    }
    dt = dtScale * dt;

    uint32_t flag;
    bool     madeVariant = false;
    Variant  tmp;
    if (world->mAutoBaking) {
        Variant* fv = props->GetProperty(0xda61d1cu);
        uint16_t t = fv->mType;
        if (t == 9 || t == 0x10) {
            if (fv->mFlags & 0x30)
                flag = *(uint32_t*)fv->mValue;
            else
                flag = t ? *(uint32_t*)fv : 0;
        } else {
            flag = g_variantUintDefault;
        }
    } else {
        tmp.mFlags = 0;
        tmp.mType  = 0;
        uint32_t zero = 0;
        ((VariantBuilder*)&tmp)->SetU32(&zero);
        madeVariant = true;
        uint16_t t = tmp.mType;
        if (t == 9 || t == 0x10) {
            if (tmp.mFlags & 0x30)
                flag = *(uint32_t*)tmp.mValue;
            else
                flag = t ? *(uint32_t*)&tmp : 0;
        } else {
            flag = g_variantUintDefault;
        }
    }
    if (madeVariant && (tmp.mFlags & 4))
        tmp.Destruct(false);

    bool  bakeFlag;
    {
        Variant* bv = props->GetProperty(0xe0e98b25u);
        uint16_t t = bv->mType;
        if (t == 1 || t == 0x10) {
            if (bv->mFlags & 0x30)
                bakeFlag = *(uint8_t*)bv->mValue != 0;
            else
                bakeFlag = t ? (*(uint8_t*)bv != 0) : false;
        } else {
            bakeFlag = g_variantBoolDefault != 0;
        }
    }

    Vector3_s00a0_5c20 camPos;
    cViewer_s00a0_5c20* v = viewer;
    if (v == 0) {
        v = (cViewer_s00a0_5c20*)GetViewer()->c12(0);
    }
    if (v != 0)
        v->GetCameraLocationInfo(&camPos, 0, 0, 0);

    uint n = (uint)(world->mpEnd - world->mpBegin);
    for (uint i = 0; i < n; ++i) {
        anim_creature_s00a0_5c20* ac = world->mpBegin[i];
        if (!ac->f64)
            continue;
        uint idx = ac->f54 == 4 ? ac->f50 : ac->f54;
        ac->blender->SetBakeParam(dt, idx == 0);
    }

    float power = (float)pow((double)(dt / 0.1f), 0.1);

    uint m = (uint)(world->mpEnd - world->mpBegin);
    for (uint i = 0; i < m; ++i) {
        anim_creature_s00a0_5c20* ac = world->mpBegin[i];
        if (!ac->f64)
            continue;
        uint idx = ac->f54 == 4 ? ac->f50 : ac->f54;
        uint handle = *(uint*)&ac->slots[idx];
        creature_instance_data_s00a0_5c20* inst = ac->instance;

        float dz = camPos.z - *(float*)((char*)inst + 0x20);
        float dy = camPos.y - *(float*)((char*)inst + 0x1c);
        float dx = camPos.x - *(float*)((char*)inst + 0x18);
        float distSq = dz * dz + dy * dy + dx * dx;

        uint shouldBake = world->w21(handle, distSq);
        ac->blender->UpdateCreatureBodies(
            (uint)(size_t)world->mEffectsWorld, dt, power, idx == 0, shouldBake, handle, distSq);

        if (ac->instance != 0) {
            RegisterCreature(ac);
            uint state;
            if (flag == 0xffffffffu)      state = 0;
            else if (flag == 1)           state = 1;
            else                          state = ac->f88 & 1;
            UpdateBakeTarget(ac, flag, state == 0);
        }
    }

    world->mSeq++;
}

// @ 0x00a06600
void nSPCreatureAnim::pose_bone_set::Refresh(float elapsed, int mode)
{
    if (this->bone_begin == this->bone_end)
        return;

    ((nSPCreatureAnim::pose_set_notify)this->vtable[10])(this, elapsed, mode);

    uint32_t count = (uint32_t)(this->bone_end - this->bone_begin);
    for (uint32_t i = 0; i < count; i++) {
        nSPCreatureAnim::pose_bone* bone = this->bone_begin[i];
        if (!bone->enabled)
            continue;

        nSPCreatureAnim::creature_instance_data_s00a0_6600* c = bone->creature;
        float base_height = c->GetGroundHeight(&c->position, 0);

        bone->cached_axis.x = c->v_160.x;
        bone->cached_axis.y = c->v_160.y;
        bone->cached_axis.z = c->v_160.z;
        bone->cached_orientation.x = c->q_170.x;
        bone->cached_orientation.y = c->q_170.y;
        bone->cached_orientation.z = c->q_170.z;
        bone->cached_orientation.w = c->q_170.w;

        checkerlib::vector_3_s00a0_6600 offset = InvRotate(bone->orientation, c->v_160, bone->position);
        bone->position.x = offset.x;
        bone->position.y = offset.y;
        bone->position.z = offset.z;

        float qx = bone->orientation.x;
        float qy = bone->orientation.y;
        float qz = bone->orientation.z;
        float qw = bone->orientation.w;
        float ax = c->q_170.x;
        float ay = c->q_170.y;
        float az = c->q_170.z;
        float aw = c->q_170.w;
        bone->orientation.x = ((qx * aw + ax * qw) - ay * qz) + az * qy;
        bone->orientation.y = ((qy * aw + ax * qz) + ay * qw) - az * qx;
        bone->orientation.z = ((qz * aw - qy * ax) + ay * qx) + az * qw;
        bone->orientation.w = ((qw * aw - qx * ax) - qy * ay) - qz * az;

        if ((c->flags_010 & 0x1f) == 0) {
            float inv = 1.0f / sqrtf(bone->orientation.x * bone->orientation.x +
                                     bone->orientation.y * bone->orientation.y +
                                     bone->orientation.z * bone->orientation.z +
                                     bone->orientation.w * bone->orientation.w);
            bone->orientation.x *= inv;
            bone->orientation.y *= inv;
            bone->orientation.z *= inv;
            bone->orientation.w *= inv;
        }

        c->f_030 = bone->position.x;
        c->f_034 = bone->position.y;
        c->f_038 = bone->position.z;
        c->q_05c.x = bone->orientation.x;
        c->q_05c.y = bone->orientation.y;
        c->q_05c.z = bone->orientation.z;
        c->q_05c.w = bone->orientation.w;

        checkerlib::vector_3_s00a0_6600 spin = InvRotate(bone->orientation, c->v_118, bone->position);
        c->position.x = spin.x;
        c->position.y = spin.y;
        c->position.z = spin.z;

        qx = bone->orientation.x;
        qy = bone->orientation.y;
        qz = bone->orientation.z;
        qw = bone->orientation.w;
        float rw = c->f_128;
        float rx = c->f_134;
        float ry = c->f_130;
        float rz = c->f_12c;
        c->orientation.x = ((rw * qw + qx * rx) - rz * qz) + ry * qy;
        c->orientation.y = ((qz * rw + rz * qw) + qy * rx) - ry * qx;
        c->orientation.z = ((qz * rx - qy * rw) + ry * qw) + rz * qx;
        c->orientation.w = ((qw * rx - rw * qx) - qy * rz) - ry * qz;

        float height = c->GetGroundHeight(&c->position, 0);
        float lift = height - base_height;
        checkerlib::vector_3_s00a0_6600 up;
        c->GetGroundUp(&up, &c->position);
        c->position.x = up.x * lift + c->position.x;
        c->position.y = c->position.y + up.y * lift;
        c->position.z = c->position.z + up.z * lift;
    }

    ((nSPCreatureAnim::pose_set_notify)this->vtable[11])(this, elapsed, mode);
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

// @ 0x00a07ae0
void Cmd::Set0c(CArgs* a)
{
    int* r = a->MainArguments(1);
    int v = host->h40((void*)r[0]);
    *(int*)((char*)data + 0xc) = v;
}

// @ 0x00a07b70
void Cmd::Set34(CArgs* a)
{
    int* r = a->MainArguments(1);
    int v = host->h39((void*)r[0]);
    *(int*)((char*)data + 0x34) = v;
}

// @ 0x00a07ba0
void Cmd::Set28(CArgs* a)
{
    int* r = a->MainArguments(1);
    uint8_t v = (uint8_t)host->h37((void*)r[0]);
    data->b28 = v;
}

// @ 0x00a07c00
void Cmd::Set29(CArgs* a)
{
    int* r = a->MainArguments(1);
    uint8_t v = (uint8_t)host->h37((void*)r[0]);
    data->b29 = v;
}

// @ 0x00a07c30
void Cmd::Mask2c(CArgs* a)
{
    int count = 0;
    const char** argv = a->MainArguments(&count, 1, 0x7fffffff);
    int i = 0;
    if (count > 0) {
        do {
            int v = host->h39((void*)argv[i]);
            if (v < 0) {
                data->f2c = 0xffffffff;
                return;
            }
            unsigned m = 1u << v;
            ++i;
            data->f2c |= m;
        } while (i < count);
    }
}

// @ 0x00a07cb0
void Cmd::Mask30(CArgs* a)
{
    int count = 0;
    const char** argv = a->MainArguments(&count, 1, 0x7fffffff);
    int i = 0;
    if (count > 0) {
        do {
            int v = host->h39((void*)argv[i]);
            if (v < 0) {
                data->f30 = 0xffffffff;
                return;
            }
            unsigned m = 1u << v;
            ++i;
            data->f30 |= m;
        } while (i < count);
    }
}

// @ 0x00a07d60
void Cmd::Set2a(CArgs* a)
{
    int* r = a->MainArguments(1);
    uint8_t v = (uint8_t)host->h37((void*)r[0]);
    data->b2a = v;
}

// @ 0x00a07d90
void __stdcall FUN_00a07d90(uint key)
{
    FbNode* n;
    g_fbTree.find((void**)&n, &key);
    if (n == &g_fbEnd)
        return;

    int evCount = (int)((n->evEnd - n->evBegin) / 0x18);
    if (evCount == 0)
        return;

    for (int i = 0; i < evCount; ++i) {
        uint8_t* ev = n->evBegin + i * 0x18;
        uint8_t* recBegin = *(uint8_t**)ev;
        uint8_t* recEnd   = *(uint8_t**)(ev + 4);
        int recCount = (int)((recEnd - recBegin) / 0x1c);
        for (int j = 0; j < recCount; ++j)
            FUN_009a4430(0, *(void**)(recBegin + j * 0x1c + 8), 0);
    }
}

// @ 0x00a07e40
bool __cdecl FUN_00a07e40(void* a1, RespObj* req)
{
    void* p = req->r6();
    int n = ((RespObj*)p)->r11();
    if (n == -1) {
        req->r2();
        return false;
    }

    Blob* b = (Blob*)ZoneObject_new(0x18, "Anim/BackgroundLoading", 0, 0, 0, 0);
    if (b)
        b = (Blob*)b->Init((void*)n, "Anim/BackgroundLoading/SharedPointer");
    BlobAddRef(b);

    char* dst = (char*)b->f10;
    int rem = n;
    while (rem > 0) {
        int wrote = ((RespObj*)p)->r12(dst, rem);
        if (wrote == -1)
            break;
        rem -= wrote;
        dst += wrote;
    }

    req->r9();

    if (rem != 0) {
        BlobRelease(b);
        req->r2();
        return false;
    }

    RespObj* rq = (RespObj*)EAAllocate(0x24, "Anim/BackgroundLoading", 0, 0, 0, 0);
    if (rq) {
        rq = (RespObj*)((GFAR*)rq)->Cons(b, (void*)n, "Anim/BackgroundLoading/MemoryStream");
        rq->r1();
    }

    bool res = FUN_00a057a0(a1, rq);
    if (rq)
        rq->r2();
    BlobRelease(b);
    req->r2();
    return res;
}

// @ 0x00a07fc0
void* Mgr::FbApplyFilter(const void* key, uint* filter)
{
    FbNode* n;
    void* last = g_fbTree.find((void**)&n, &key);
    if (n == &g_fbEnd)
        return last;

    int evCount = (int)((n->evEnd - n->evBegin) / 0x18);
    for (int i = 0; i < evCount; ++i) {
        if (filter == 0 || *filter == (uint)i) {
            uint8_t* ev = n->evBegin + i * 0x18;
            uint8_t* recBegin = *(uint8_t**)ev;
            uint8_t* recEnd   = *(uint8_t**)(ev + 4);
            int recCount = (int)((recEnd - recBegin) / 0x1c);
            for (int j = 0; j < recCount; ++j)
                last = ((WObj*)this)->w12(*(void**)(recBegin + j * 0x1c + 8));
        }
    }
    return last;
}

// @ 0x00a08090
Job* Mgr::FeedbackJob(uint key, char flag)
{
    JobNode* n;
    ((TreeObj*)((char*)this + 0x34))->find((void**)&n, &key);
    if (n == (JobNode*)((char*)this + 0x38))
        return 0;

    if (!flag && n->job != 0 && (uint)(n->job->ContinueJob() - 7) > 1)
        return 0;

    if (n->job != 0) {
        n->job->Wait();
        OutObj* p = n->job->out;
        if (p) {
            p->o1();
            p->o2();
            return (Job*)p;
        }
    }
    return 0;
}

// @ 0x00a08110
bool Mgr::SelectFeedbackRecord(uint key)
{
    FbNode* n;
    g_fbTree.find((void**)&n, &key);
    if (n == &g_fbEnd)
        return false;

    uint8_t* ev = n->evBegin;
    if (ev == n->evEnd)
        return false;

    uint8_t* rec = *(uint8_t**)ev;
    if (rec == *(uint8_t**)(ev + 4))
        return false;

    Slot* slot = (Slot*)((char*)this + 0x14);
    void* r = FUN_009a4430(0, *(void**)(rec + 8), 0);
    slot->set(r);
    return slot->v != 0;
}

// @ 0x00a08180
void* __stdcall FUN_00a08180(const uint* key)
{
    FbNode* n;
    g_fbTree.find((void**)&n, &key);
    if (n != &g_fbEnd)
        return (char*)n + 0x14;
    return 0;
}

// @ 0x00a081b0
bool Mgr::WriteAnimList(IStream* s)
{
    uint32_t magic = 0x74736c61;
    WriteU32(s, &magic, 1, 0);
    uint32_t ver = 0xa;
    WriteU32(s, &ver, 1, 0);
    uint32_t count = (uint32_t)g_fbCount;
    WriteU32(s, &count, 1, 0);

    for (AnimNode* n = (AnimNode*)g_fbRoot; n != (AnimNode*)&g_fbEnd;
         n = (AnimNode*)RBTreeIncrement(n)) {
        int32_t key = n->key;
        WriteU32(s, &key, 1, 0);

        int seqN = (int)((n->seqEnd - n->seqBegin) >> 1);
        WriteU32(s, &seqN, 1, 0);
        s->s14(n->seqBegin, (int)((n->seqEnd - n->seqBegin) >> 1) * 2);

        uint32_t f28 = *(uint32_t*)&n->f28;
        WriteU32(s, &f28, 1, 0);
        uint32_t f2c = *(uint32_t*)&n->f2c;
        WriteU32(s, &f2c, 1, 0);

        uint8_t b30 = n->b30 != 0;
        StreamWrite(s, &b30, 1);
        uint8_t b31 = n->b31 != 0;
        StreamWrite(s, &b31, 1);
        uint8_t b32 = n->b32 != 0;
        StreamWrite(s, &b32, 1);

        uint32_t d34 = n->d34;
        WriteU32(s, &d34, 1, 0);
        uint32_t d38 = n->d38;
        WriteU32(s, &d38, 1, 0);
        uint32_t d3c = n->d3c;
        WriteU32(s, &d3c, 1, 0);

        int evCount = (int)((n->evEnd - n->evBegin) / 0x18);
        WriteU32(s, &evCount, 1, 0);
        if (evCount > 0) {
            for (int i = 0; i < evCount; ++i) {
                AnimEvent* ev = n->evBegin + i;
                uint32_t t = *(uint32_t*)&ev->time;
                WriteU32(s, &t, 1, 0);

                int recCount = (int)((ev->end - ev->begin) / 0x1c);
                WriteU32(s, &recCount, 1, 0);
                if (recCount > 0) {
                    for (int j = 0; j < recCount; ++j) {
                        AnimRecord* r = ev->begin + j;
                        uint32_t f0 = *(uint32_t*)&r->f0;
                        WriteU32(s, &f0, 1, 0);
                        uint32_t f4 = *(uint32_t*)&r->f4;
                        WriteU32(s, &f4, 1, 0);
                        uint32_t f8 = r->f8;
                        WriteU32(s, &f8, 1, 0);
                        int vn = (int)((r->v_10 - r->v_c) >> 1);
                        WriteU32(s, &vn, 1, 0);
                        s->s14(r->v_c, (int)((r->v_10 - r->v_c) >> 1) * 2);
                    }
                }
            }
        }
    }
    return true;
}

// @ 0x00a08490
bool Mgr::WriteAnimListFile(IStream* file)
{
    uint64 ts = 0;
    GetTickCount100ns(&ts);

    struct { uint32_t lo; uint32_t magic; uint32_t hi; } k;
    k.lo = (uint32_t)ts;
    k.magic = 0x4aeb6bc6;
    k.hi = (uint32_t)(ts >> 32);

    IStream* h = 0;
    if (!file->s13(&k, &h, 2, 6, 1, 0)) {
        if (h)
            h->s2();
        return false;
    }

    void* r = h->s6();
    bool res = WriteAnimList((IStream*)r);
    h->s9();
    if (h)
        h->s2();
    return res;
}

// @ 0x00a08540
bool __cdecl FUN_00a08540(IStream* s)
{
    uint64 ts = 0;
    GetTickCount100ns(&ts);

    struct { uint32_t lo; uint32_t magic; uint32_t hi; } k;
    k.lo = (uint32_t)ts;
    k.magic = 0x7c19aa7a;
    k.hi = (uint32_t)(ts >> 32);

    IStream* h = 0;
    if (!s->s13(&k, &h, 2, 6, 1, 0)) {
        if (h)
            h->s2();
        return false;
    }

    IStream* r = (IStream*)h->s6();

    uint32_t magic = 0x70637470;
    WriteU32(r, &magic, 1, 0);
    uint32_t ver = 4;
    WriteU32(r, &ver, 1, 0);
    uint32_t f = *(uint32_t*)&g_f1550b84;
    WriteU32(r, &f, 1, 0);

    Vec14* v = g_p070;
    uint32_t n0 = (uint32_t)((v->p4 - v->p0) / 0x14);
    WriteU32(r, &n0, 1, 0);
    for (uint32_t i = 0; i < n0; ++i) {
        Elem14* e = (Elem14*)(v->p0 + i * 0x14);
        WriteCString(r, e->str, (int)(e->strEnd - e->str), 0);
        uint32_t x = e->f10;
        WriteU32(r, &x, 1, 0);
    }

    MapHead* m1 = g_p074;
    uint32_t c1 = m1->count;
    WriteU32(r, &c1, 1, 0);
    for (uint8_t* nd = m1->root; nd != m1->end; nd = (uint8_t*)RBTreeIncrement(nd)) {
        Node3* v1 = (Node3*)nd;
        WriteU32(r, &v1->a10, 1, 0);
        WriteU32(r, &v1->a14, 1, 0);
        WriteU32(r, &v1->a18, 1, 0);
    }

    MapHead* m2 = g_p080;
    uint32_t c2 = m2->count;
    WriteU32(r, &c2, 1, 0);
    for (uint8_t* nd = m2->root; nd != m2->end; nd = (uint8_t*)RBTreeIncrement(nd)) {
        NodeVec* nv = (NodeVec*)nd;
        WriteU32(r, &nv->key, 1, 0);
        int cnt = (int)((nv->vecEnd - nv->vecBegin) >> 2);
        WriteU32(r, &cnt, 1, 0);
        for (int i = 0; i < cnt; ++i) {
            uint32_t x = nv->vecBegin[i];
            WriteU32(r, &x, 1, 0);
        }
    }

    MapHead* m3 = g_p078;
    uint32_t c3 = m3->count;
    WriteU32(r, &c3, 1, 0);
    for (uint8_t* nd = m3->root; nd != m3->end; nd = (uint8_t*)RBTreeIncrement(nd)) {
        NodeVec16* nv = (NodeVec16*)nd;
        WriteU32(r, &nv->key, 1, 0);
        int cnt = (int)((nv->vecEnd - nv->vecBegin) >> 4);
        WriteU32(r, &cnt, 1, 0);
        for (int i = 0; i < cnt; ++i) {
            Elem16* e = nv->vecBegin + i;
            WriteU32(r, &e->a0, 1, 0);
            uint32_t f4 = *(uint32_t*)&e->f4;
            WriteU32(r, &f4, 1, 0);
            uint32_t f8 = *(uint32_t*)&e->f8;
            WriteU32(r, &f8, 1, 0);
            WriteU32(r, &e->aC, 1, 0);
        }
    }

    h->s9();
    if (h)
        h->s2();
    return true;
}

// @ 0x00a088e0
void* __cdecl FUN_00a088e0(void* param)
{
    void* result = 0;
    IStream* handle = 0;
    bool didRead = false;

    struct { void* p; uint32_t magic; uint32_t pad; } key;
    key.p = param;
    key.magic = 0xee17c6ad;
    key.pad = 0;

    IStream* obj = (IStream*)g_p166cc08->o24(param, 1);
    if (obj == 0) {
        ResMan* m = (ResMan*)GetManager();
        IStream* r = (IStream*)m->m22(&key);
        if (r == 0)
            goto done;
        if (handle) {
            handle->s2();
            handle = 0;
        }
        if (!r->s13((void*)&key, &handle, 1, 6, 1, 0))
            goto done;
        obj = (IStream*)handle->s6();
    } else {
        didRead = true;
    }

    if (obj != 0) {
        struct { void** vtbl; IStream* obj; } w;
        w.vtbl = (void**)0x1448b30;
        w.obj = obj;
        obj->s1();

        char buf[0x100];
        buf[0] = 0;
        operator_new_arr(buf, 0, 0xff);
        result = ReadAnimationStaticDataFromStreamWrapper(&w, buf, &key);
        if (didRead)
            g_p166cc08->o13(param);
        w.obj->s2();
    }

done:
    if (handle) {
        handle->s9();
        handle->s2();
    }
    return result;
}

// @ 0x00a08a20
void* __cdecl FUN_00a08a20(void* param)
{
    void* result = 0;
    IStream* handle = 0;

    struct { void* p; uint32_t magic; uint32_t pad; } key;
    key.p = param;
    key.magic = 0x25df0112;
    key.pad = 0;

    ResMan* m = (ResMan*)GetManager();
    IStream* r = (IStream*)m->m22(&key);
    if (r != 0) {
        if (handle) {
            handle->s2();
            handle = 0;
        }
        if (r->s13((void*)&key, &handle, 1, 6, 1, 0)) {
            IStream* obj = (IStream*)handle->s6();
            if (obj != 0) {
                struct { void** vtbl; IStream* obj; } w;
                w.vtbl = (void**)0x1448b30;
                w.obj = obj;
                obj->s1();
                result = ReadGaitRecordStaticDataFromStreamWrapper(&w);
                w.vtbl = (void**)0x1448b30;
                if (w.obj)
                    w.obj->s2();
            }
        }
    }

    if (handle) {
        handle->s9();
        handle->s2();
    }
    return result;
}

// @ 0x00a08b00
void* Tree::insertAt(void** out, void* hint, uint* key, char flag)
{
    int side;
    if (flag == 0
        && hint != (void*)((char*)this + 4)
        && key[1] >= *(uint*)((char*)hint + 0x14)
        && (key[1] != *(uint*)((char*)hint + 0x14) || key[0] >= *(uint*)((char*)hint + 0x10)))
        side = 1;
    else
        side = 0;

    TreeNode* n = (TreeNode*)EAAllocate(
        0x20, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    uint32_t* dst = (uint32_t*)((char*)n + 0x10);
    if (dst != 0) {
        dst[0] = key[0];
        dst[1] = key[1];
        void* o = *(void**)((char*)key + 8);
        *(void**)((char*)dst + 8) = o;
        if (o != 0)
            ((StaticData*)o)->AddRef();
    }
    RBTreeInsert(n, hint, (char*)this + 4, side);
    ++*(uint32_t*)((char*)this + 0x14);
    *out = n;
    // Retail leaves the `out` slot pointer in eax at the ret (dead for callers, but the
    // LTCG contract compares it), so hand it back here.
    return out;
}

// @ 0x00a08ba0
void __cdecl FUN_00a08ba0(void)
{
    if (g_p166cc08_s00a0_8b00 == 0)
        return;
    LayoutMgr* mgr = g_p166c06c;
    if (mgr == 0)
        return;

    mgr->FreeTree(mgr->child);
    mgr->f08 = (char*)mgr + 4;
    mgr->child = 0;
    mgr->f10 = 0;
    mgr->count = 0;
    mgr->f04 = (char*)mgr + 4;

    uint nOuter = (uint)((g_p166cc08_s00a0_8b00->v6c - g_p166cc08_s00a0_8b00->v68) >> 2);
    for (uint i = 0; i < nOuter; ++i) {
        ElemA* e = (ElemA*)g_p166cc08_s00a0_8b00->v68[i];
        uint nMid = (uint)((e->v28 - e->v24) >> 2);
        for (uint j = 0; j < nMid; ++j) {
            void* o = e->v24[j];
            if (o != 0) {
                StateObj* q = *(StateObj**)((char*)o + 0x17c);
                if (q != 0) {
                    int n = q->nStates;
                    if (n > 0) {
                        int* cnt = q->counts;
                        uint8_t* vec = (uint8_t*)q + 0x314;
                        for (int a = 0; a < n; ++a) {
                            int m = *cnt;
                            if (m > 0) {
                                uint32_t* v = (uint32_t*)vec;
                                for (int b = 0; b < m; ++b)
                                    v[b] = 0;
                            }
                            *cnt = 0;
                            ++cnt;
                            vec += 0x10;
                        }
                    }
                    q->nStates = 0;
                }
            }
        }
    }
}

// @ 0x00a08cb0
void* cAnimatingCreature_s00a0_8b00::scalar_deleting_destructor(uint8_t param_2)
{
    *(void**)this = (void*)0x1448b48;
    _ReadWriteBarrier();
    if (f17c != 0)
        ((InstanceData*)f17c)->Release();
    if (f15c != 0)
        ((AnimCreatureBase*)f15c)->Release();
    if ((param_2 & 1) != 0)
        operator_delete__(this);
    return this;
}

// @ 0x00a08cf0
void OnRegObj::OnRegisterAnimCommand(void* parser, int state)
{
    f30 = state;
    reg.OnReg(parser, state);

    void* c = EAAllocate(0x10, "ArgScript/OldAnimID", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448c08;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_animID, c);

    c = EAAllocate(0x10, "ArgScript/OldAnimName", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448c20;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_animName, c);

    c = EAAllocate(0x10, "ArgScript/OldDuration", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448c38;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_duration, c);

    c = EAAllocate(0x10, "ArgScript/OldDurationScale", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448c50;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_durationScale, c);

    c = EAAllocate(0x10, "ArgScript/EndMode", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448c68;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_endMode, c);

    c = EAAllocate(0x10, "ArgScript/Idle", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448c80;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_idle, c);

    c = EAAllocate(0x10, "ArgScript/BlendInTime", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448c98;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_blendInTime, c);

    c = EAAllocate(0x10, "ArgScript/AllowLocomotion", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448cb0;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_allowLocomotion, c);

    c = EAAllocate(0x10, "ArgScript/DisableToolOverlayMask", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448cc8;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_disableToolOverlay, c);

    c = EAAllocate(0x10, "ArgScript/MatchVariantForToolMask", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448ce0;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_matchVariantForTool, c);

    c = EAAllocate(0x10, "ArgScript/PriorityOverride", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448cf8;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_priorityOverride, c);
}

// @ 0x00a08fc0
void OnRegObj::OnRegisterAnim(void* parser, int state)
{
    f30 = state;
    reg.OnReg(parser, state);

    void* c = EAAllocate(0x10, "ArgScript/Animation", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448d58;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_animation, c);
}

// @ 0x00a09020
void OnRegObj::OnRegisterChoice(void* parser, int state)
{
    f30 = state;
    reg.OnReg(parser, state);

    void* c = EAAllocate(0x34, "ArgScript/Choice", 0, 0, 0, 0);
    if (c != 0) {
        ((ChoiceBase*)c)->Ctor();
        *(void**)c = (void*)0x1448d34;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_choice, c);

    c = EAAllocate(0x10, "ArgScript/RandomizeChoicePerLoop", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448d70;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_randomizeChoice, c);

    c = EAAllocate(0x10, "ArgScript/EndMode", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448c68;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_endMode, c);

    c = EAAllocate(0x10, "ArgScript/Idle", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448c80;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_idle, c);

    c = EAAllocate(0x10, "ArgScript/BlendInTime", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448c98;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_blendInTime, c);

    c = EAAllocate(0x10, "ArgScript/AllowLocomotion", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448cb0;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_allowLocomotion, c);

    c = EAAllocate(0x10, "ArgScript/DisableToolOverlayMask", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448cc8;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_disableToolOverlay, c);

    c = EAAllocate(0x10, "ArgScript/MatchVariantForToolMask", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448ce0;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_matchVariantForTool, c);

    c = EAAllocate(0x10, "ArgScript/PriorityOverride", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase_s00a0_8b00*)c)->Ctor();
        *(void**)c = (void*)0x1448cf8;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_priorityOverride, c);
}

// @ 0x00a09280
bool __stdcall FUN_00a09280(void* mgr)
{
    bool     ok = true;
    void**   vecBegin = 0;
    void**   vecEnd = 0;
    void**   vecCap = 0;
    struct { const void* p; uint32_t h; } key;
    key.p = (const void*)0x13eb428;
    key.h = 0x25df0112;

    ResMan_s00a0_8b00* rm = (ResMan_s00a0_8b00*)GetManager();
    if (!rm->v14(&vecBegin, &key, 0))
        goto cleanup;
    if (vecBegin == vecEnd)
        goto cleanup;

    {
        HostObj* host = (HostObj*)mgr;
        const void* type = (const void*)0x1448b30;
        for (void** it = vecBegin; it != vecEnd; it += 3) {
            void* out = 0;
            if (host->h13(*it, &out, 2, 6, 1, 0)) {
                CRes* r = (CRes*)out;
                void* p = r->r6();
                struct { const void* t; void* p; } sp;
                sp.t = type;
                sp.p = p;
                if (p != 0)
                    ((CRes*)p)->r1();
                void* q = FUN_00a08a20(*it);
                if (q != 0)
                    FUN_009de6e0(q, &sp);
                sp.t = type;
                if (p != 0)
                    ((CRes*)p)->r2();
                out = sp.p;
            } else {
                ok = false;
            }
            if (out != 0) {
                ((CRes*)out)->r9();
                ((CRes*)out)->r2();
            }
        }
    }

cleanup:
    if (vecBegin != 0 && *(void**)((char*)vecBegin - 4) != 0)
        operator_delete__(vecBegin);
    return ok;
}

// @ 0x00a093b0
Rec::Rec(const Rec& o)
{
    f0 = o.f0;
    f4 = o.f4;
    f8 = o.f8;
    s.begin = 0;
    s.end = 0;
    s.cap = 0;
    uint16_t* src = o.s.begin;
    int n = (int)(o.s.end - src);
    s.AllocateSelf(n + 1);
    uint16_t* dst = s.begin;
    WCopy(dst, src, (uint)n * 2);
    s.end = (uint16_t*)((char*)dst + n * 2);
    *s.end = 0;
}

// @ 0x00a09420
Pair* Tree::insertHint(Pair* out, const uint* key, void* dummy)
{
    char  side = 1;
    void* pos = (char*)this + 4;
    void* cur = *(void**)((char*)this + 0xc);
    if (cur != 0) {
        uint k0 = key[0];
        uint k1 = key[1];
        do {
            uint n1 = *(uint*)((char*)cur + 0x14);
            uint n0 = *(uint*)((char*)cur + 0x10);
            if (k1 > n1)
                side = 0;
            else if (k1 < n1)
                side = 1;
            else
                side = (k0 < n0);
            pos = cur;
            cur = side ? *(void**)((char*)cur + 4) : *(void**)cur;
        } while (cur != 0);
    }

    void* probe = pos;                       // the node the insert is parented to
    void* prev  = pos;                       // the neighbour the lower-bound test uses
    if (side) {
        if (pos == *(void**)((char*)this + 8))
            goto doInsert;
        prev = RBTreeDecrement(pos);
    }
    if (*(uint*)((char*)prev + 0x14) > key[1]
        || (*(uint*)((char*)prev + 0x14) == key[1]
            && *(uint*)((char*)prev + 0x10) >= key[0])) {
        out->node = prev;
        out->inserted = 0;
        return out;
    }

doInsert:
    {
        void* n;
        insertAt(&n, probe, (uint*)key, 0);
        out->node = n;
        out->inserted = 1;
    }
    return out;
}

// @ 0x00a094d0
void* __cdecl FUN_00a094d0(void** first1, void** last1, void** first2, void** last2, void** out)
{
    for (;;) {
        if (first1 == last1 || first2 == last2) {
            uint n1 = (uint)(last1 - first1);
            out = (void**)WCopy(out, first1, n1 * 4);
            out += n1;
            uint n2 = (uint)(last2 - first2);
            out = (void**)WCopy(out, first2, n2 * 4);
            out += n2;
            return out;
        }
        void* b = *first2;
        void* a = *first1;
        if (b == 0) goto takeA;
        if (a == 0) goto takeB;
        if (*(uint8_t*)((char*)b + 0x5c) == 0) goto takeA;
        if (*(uint8_t*)((char*)a + 0x5c) == 0) goto takeB;
        {
            float fb = *(float*)((char*)b + 0x60);
            float fa = *(float*)((char*)a + 0x60);
            if (fb > fa) goto takeB;
        }
    takeA:
        *out = a; ++first1;
    next:
        ++out;
        continue;
    takeB:
        *out = b; ++first2;
        goto next;
    }
}

// @ 0x00a095a0
void __cdecl FUN_00a095a0(Rec* dst, Rec* last, const Rec* value)
{
    while (dst != last) {
        dst->f0 = value->f0;
        dst->f4 = value->f4;
        dst->f8 = value->f8;
        if (&dst->s != &value->s)
            dst->s.Assign(value->s.begin, value->s.end);
        ++dst;
    }
}

// @ 0x00a09630
Rec* __cdecl FUN_00a09630(Rec* first, Rec* last, Rec* dst)
{
    if (first != last) {
        do {
            uint16_t* p = first->s.begin;
            int len = (int)((char*)first->s.cap - (char*)p) & 0xfffffffe;
            if (len > 2 && p != 0)
                operator_delete__(p);
            ++first;
            ++dst;
        } while (first != last);
        return dst;
    }
    return dst;
}

// @ 0x00a09680
Rec* __cdecl FUN_00a09680(Rec* first, Rec* last, Rec* dst)
{
    if (first != last) {
        Rec* d = dst;
        do {
            d->f0 = first->f0;
            d->f4 = first->f4;
            d->f8 = first->f8;
            if (&first->s != &d->s)
                d->s.Assign(first->s.begin, first->s.end);
            ++first;
            ++d;
        } while (first != last);
        return d;
    }
    return dst;
}

// @ 0x00a096e0
Rec* __cdecl FUN_00a096e0(Rec* first, Rec* last, Rec* dst)
{
    if (last != first) {
        do {
            --last;
            --dst;
            dst->f0 = last->f0;
            dst->f4 = last->f4;
            dst->f8 = last->f8;
            if (&last->s != &dst->s)
                dst->s.Assign(last->s.begin, last->s.end);
        } while (last != first);
        return dst;
    }
    return dst;
}

// @ 0x00a09810
void __stdcall FUN_00a09810(Rec* first, Rec* last)
{
    for (; first < last; ++first) {
        uint16_t* p = first->s.begin;
        int len = (int)((char*)first->s.cap - (char*)p) & 0xfffffffe;
        if (len > 2 && p != 0)
            operator_delete__(p);
    }
}

// @ 0x00a09850
void MapA::Destroy(MapNodeA* n)
{
    while (n != 0) {
        Destroy(n->left);
        MapNodeA* next = n->right;
        if (n->obj != 0)
            ((StaticData*)n->obj)->Release();
        operator_delete__(n);
        n = next;
    }
}

// @ 0x00a09890
void MapB::Destroy(MapNodeB* n)
{
    while (n != 0) {
        Destroy(n->left);
        MapNodeB* next = n->right;
        if (n->job != 0)
            ((Job_s00a0_8b00*)n->job)->Release();
        operator_delete__(n);
        n = next;
    }
}

// @ 0x00a098d0
Pair* Tree::insertOrFind(Pair* out, void* hint, uint* key, int unused)
{
    void* root = *(void**)((char*)this + 4);
    if (hint == root || hint == (void*)((char*)this + 4)) {
        if (*(uint*)((char*)this + 0x14) != 0
            && *(uint*)((char*)root + 0x14) <= key[1]
            && (*(uint*)((char*)root + 0x14) < key[1]
                || *(uint*)((char*)root + 0x10) < key[0])) {
            insertAt((void**)out, root, key, 0);
            return out;
        }
        Pair local;
        insertHint(&local, key, (void*)((uint)key & 0xffffff00u));
        out->node = local.node;
        return out;
    }

    void* inc = RBTreeIncrement(hint);
    uint k0 = key[0];
    uint k1 = key[1];
    if (*(uint*)((char*)hint + 0x14) <= k1
        && (*(uint*)((char*)hint + 0x14) < k1 || *(uint*)((char*)hint + 0x10) < k0)
        && k1 <= *(uint*)((char*)inc + 0x14)
        && (k1 < *(uint*)((char*)inc + 0x14) || k0 < *(uint*)((char*)inc + 0x10))) {
        int side;
        void* h;
        if (*(int*)hint != 0) {
            h = inc;
            side = 1;
        } else {
            h = hint;
            side = 0;
        }
        insertAt((void**)out, h, key, side);
        return out;
    }

    Pair local;
    insertHint(&local, key, (void*)((uint)key & 0xffffff00u));
    out->node = local.node;
    return out;
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
        struct FillValue { unsigned x, y, z; };
        FillValue local;
        local.x = ((unsigned*)val)[0];
        local.y = ((unsigned*)val)[1];
        local.z = ((unsigned*)val)[2];
        unsigned avail = (unsigned)((end - (char*)pos) / 0xc);
        if (count < avail)
        {
            char* src = end - count * 0xc;
            FUN_00898b80(&val, src, end, end, pos);
            *(char**)(self + 4) = end + count * 0xc;
            FUN_00abced0(pos, src, end);
            FUN_00a177f0(pos, (char*)pos + count * 0xc, &local);
            return;
        }
        unsigned extra = count - avail;
        FUN_006e5760(end, extra, &local);
        *(char**)(self + 4) = end + extra * 0xc;
        FUN_00898b80(&pos, pos, end, *(char**)(self + 4), pos);
        *(char**)(self + 4) = *(char**)(self + 4) + avail * 0xc;
        FUN_00a177f0((char*)pos, end, &local);
    }
}

// @ 0x00a09cf0
void** SL71::v09cf0(void** out, void* where, unsigned* key, char flag)
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
    return out;
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

// @ 0x00a0bcf0
Rec_s00a0_bcf0* ItemVec_s00a0_bcf0::DoInsertValue(Rec_s00a0_bcf0* position, const Rec_s00a0_bcf0& value)
{
    Rec_s00a0_bcf0* end = mpEnd;
    if (end != mpCapacity) {
        if (position <= &value && &value < end)
            position = (Rec_s00a0_bcf0*)((char*)&value + 0x1c);
        if (end != 0) {
            // Construct the slot one past the end from the last live element, then
            // shift [position, end-1) one to the right and store `value` at position.
            RecConstruct(end, (Rec_s00a0_bcf0*)((char*)end - 0x1c));
        }
        FUN_00a096e0(position, (Rec_s00a0_bcf0*)((char*)end - 0x1c), end);
        position->f0 = ((Rec_s00a0_bcf0*)&value)->f0;
        position->f4 = ((Rec_s00a0_bcf0*)&value)->f4;
        position->f8 = ((Rec_s00a0_bcf0*)&value)->f8;
        if (&position->s != &((Rec_s00a0_bcf0*)&value)->s)
            position->s.Assign(((Rec_s00a0_bcf0*)&value)->s.begin, ((Rec_s00a0_bcf0*)&value)->s.end);
        mpEnd = (Rec_s00a0_bcf0*)((char*)mpEnd + 0x1c);
        return 0;
    }

    uint nOld = (uint)(((char*)end - (char*)mpBegin) / 0x1c);
    uint nCap;
    if (nOld == 0)
        nCap = 1;
    else
        nCap = nOld * 2;
    Rec_s00a0_bcf0* pNew;
    if (nCap == 0)
        pNew = 0;
    else
        pNew = (Rec_s00a0_bcf0*)EAAllocate(nCap * 0x1c, "EASTL", 0, 0, kEastlFile, 0xd1);

    Rec_s00a0_bcf0* begin = mpBegin;
    Rec_s00a0_bcf0* pos = FUN_00a095f0(begin, position, pNew);
    FUN_00a09630(begin, position, pNew);
    if (pos != 0)
        RecConstruct(pos, (const Rec_s00a0_bcf0*)&value);
    Rec_s00a0_bcf0* oldEnd = mpEnd;
    Rec_s00a0_bcf0* newEnd = FUN_00a095f0(position, oldEnd, (Rec_s00a0_bcf0*)((char*)pos + 0x1c));
    FUN_00a09630(position, oldEnd, (Rec_s00a0_bcf0*)((char*)pos + 0x1c));
    begin = mpBegin;
    if (begin != 0 && ((int*)begin)[-1] != 0)
        operator_delete__(begin);
    mpEnd = newEnd;
    mpBegin = pNew;
    mpCapacity = (Rec_s00a0_bcf0*)((char*)pNew + nCap * 0x1c);
    return 0;
}

// @ 0x00a0be60
void ItemVec_s00a0_bcf0::DoInsertValues(Rec_s00a0_bcf0* position, uint n, const Rec_s00a0_bcf0& value)
{
    uint size = (uint)(((char*)mpEnd - (char*)mpBegin) / 0x1c);
    if (n > size) {
        uint newCap = (uint)(((char*)mpEnd - (char*)mpBegin) / 0x1c) * 2;
        if (size == 0)
            newCap = 1;
        uint need = size + n;
        if (newCap > need)
            need = newCap;
        Rec_s00a0_bcf0* pNew;
        if (need == 0)
            pNew = 0;
        else
            pNew = (Rec_s00a0_bcf0*)EAAllocate(need * 0x1c, "EASTL", 0, 0, kEastlFile, 0xd1);
        Rec_s00a0_bcf0* begin = mpBegin;
        Rec_s00a0_bcf0* pos = FUN_00a095f0(begin, position, pNew);
        FUN_00a09630(begin, position, pNew);
        FUN_00a09cc0(pos, n, value);
        Rec_s00a0_bcf0* mid = (Rec_s00a0_bcf0*)((char*)pos + n * 0x1c);
        Rec_s00a0_bcf0* oldEnd = mpEnd;
        Rec_s00a0_bcf0* newEnd = FUN_00a095f0(position, oldEnd, mid);
        FUN_00a09630(position, oldEnd, mid);
        begin = mpBegin;
        if (begin != 0 && ((int*)begin)[-1] != 0)
            operator_delete__(begin);
        mpEnd = newEnd;
        mpBegin = pNew;
        mpCapacity = (Rec_s00a0_bcf0*)((char*)pNew + need * 0x1c);
        return;
    }
    if (n == 0)
        return;

    CursorRec buf;
    FUN_00a09560(&buf, (Rec_s00a0_bcf0*)&value, (Rec_s00a0_bcf0*)((char*)&value + 0x1c), 0);

    Rec_s00a0_bcf0* end = mpEnd;
    uint have = (uint)(((char*)end - (char*)position) / 0x1c);
    Rec_s00a0_bcf0* src;
    if (n < have) {
        // Shift the tail right, then overwrite the gap with `value`.
        src = (Rec_s00a0_bcf0*)((char*)end - n * 0x1c);
        FUN_00a09560(&buf, src, end, end);
        mpEnd = (Rec_s00a0_bcf0*)((char*)mpEnd + n * 0x1c);
        FUN_00a096e0(position, src, end);
        src = (Rec_s00a0_bcf0*)((char*)position + n * 0x1c);
    } else {
        FUN_00a09cc0(end, n - have, buf.p ? *buf.p : value);
        Rec_s00a0_bcf0* oldEnd = mpEnd;
        mpEnd = (Rec_s00a0_bcf0*)((char*)mpEnd + (n - have) * 0x1c);
        FUN_00a09560(&buf, position, oldEnd, (Rec_s00a0_bcf0*)mpEnd);
        mpEnd = (Rec_s00a0_bcf0*)((char*)mpEnd + have * 0x1c);
        src = position;
    }
    FUN_00a095a0(position, src, (const Rec_s00a0_bcf0*)&value);
    if (buf.p != 0 && ((int*)buf.p)[-1] != 0)
        operator_delete__(buf.p);
}

// @ 0x00a0c090
SubItemVec* __cdecl ConstructSubCursor(SubItemVec* out, const Sub_s00a0_bcf0* first, const Sub_s00a0_bcf0* last, Sub_s00a0_bcf0* init)
{
    out->mpBegin = init;
    for (; first != last; first = (const Sub_s00a0_bcf0*)((const char*)first + 0x18)) {
        Sub_s00a0_bcf0* d = out->mpBegin;
        if (d != 0) {
            uint n = (uint)(((char*)first->items.mpEnd - (char*)first->items.mpBegin) / 0x1c);
            Rec_s00a0_bcf0* buf;
            if (n == 0)
                buf = 0;
            else
                buf = (Rec_s00a0_bcf0*)EAAllocate(n * 0x1c, "EASTL", 0, 0, kEastlFile, 0xd1);
            d->items.mpCapacity = (Rec_s00a0_bcf0*)((char*)buf + n * 0x1c);
            d->items.mpBegin = buf;
            d->items.mpEnd = buf;
            for (Rec_s00a0_bcf0* s = first->items.mpBegin; s != first->items.mpEnd; ++s) {
                Rec_s00a0_bcf0* dst = d->items.mpEnd;
                if (dst != 0)
                    RecCloneInline(dst, s);
                d->items.mpEnd = (Rec_s00a0_bcf0*)((char*)dst + 0x1c);
            }
            d->items.mpEnd = (Rec_s00a0_bcf0*)((char*)buf + n * 0x1c);
            d->f14 = first->f14;
        }
        out->mpBegin = (Sub_s00a0_bcf0*)((char*)out->mpBegin + 0x18);
    }
    return out;
}

// @ 0x00a0c230
Sub_s00a0_bcf0* __cdecl ReverseCopySubs(Sub_s00a0_bcf0* first, Sub_s00a0_bcf0* last, Sub_s00a0_bcf0* dst)
{
    if (last != first) {
        do {
            last = (Sub_s00a0_bcf0*)((char*)last - 0x18);
            dst = (Sub_s00a0_bcf0*)((char*)dst - 0x18);
            dst->items.AssignRange(&last->items);
            dst->f14 = last->f14;
        } while (last != first);
    }
    return dst;
}

// @ 0x00a0c270
uint32_t __cdecl FUN_00a0c270(AnimFbOwner* self, uint32_t id, uint32_t* outIndex)
{
    FBNode* node;
    g_fbMap_1551a68.find(&node, &id);
    if (node == (FBNode*)&g_fbMap_1551a68.anchor)
        return 0;
    if (node->subsBegin == node->subsEnd)
        return 0;

    uint32_t subCount = (uint32_t)(((char*)node->subsEnd - (char*)node->subsBegin) / 0x18);
    uint32_t idx = 0;
    if (subCount > 1) {
        if (outIndex != 0 && *outIndex != 0xffffffffu && *outIndex < subCount) {
            idx = *outIndex;
        } else {
            double r = RandomGenerateDouble(g_pRandom_166cd30);
            Sub_s00a0_bcf0* subs = node->subsBegin;
            for (uint32_t i = 0; i < subCount; ++i) {
                if (subs[i].f14 > r) {
                    idx = i;
                    break;
                }
            }
        }
    }
    if (outIndex != 0)
        *outIndex = idx;

    Sub_s00a0_bcf0* chosen = (Sub_s00a0_bcf0*)((char*)node->subsBegin + idx * 0x18);
    if (chosen->items.mpBegin == chosen->items.mpEnd)
        return 0;

    uint32_t n = (uint32_t)(((char*)chosen->items.mpEnd - (char*)chosen->items.mpBegin) / 0x1c);
    Vec3_s00a0_bcf0 buf[16];
    Vec3VecSmall tmp;
    tmp.mpBegin = buf;
    tmp.mpEnd = buf;
    tmp.mpCapacity = buf + 16;
    tmp.resize(n);

    for (uint32_t i = 0; i < n; ++i) {
        Rec_s00a0_bcf0* s = (Rec_s00a0_bcf0*)((char*)chosen->items.mpBegin + i * 0x1c);
        buf[i].x = s->f8;
        buf[i].y = s->f4;
        buf[i].z = s->f0;
    }

    char* holder = self->mpAnimDefHolder;
    void* def = *(void**)(*(char**)holder + 0x14);
    void* qb = self->mpQB;
    void* h = FUN_00a01a00(qb, def, buf, (int)n);
    FUN_00a001f0(qb, h, 0);
    FUN_00a00240(qb, h, node->b30);
    float f2c = node->f2c;
    if (f2c >= 0.0f)
        FUN_00a00290(qb, h, f2c);
    FUN_00a00080(qb, h, id);

    if (node->i3c == 1) {
        FUN_00a002f0(qb, h, 1);
        FUN_009ffee0(qb, h, g_kNegOne_13eb1bc);
        if (node->b32 != 0 && subCount > 1)
            FUN_00a00450(qb, h, (void*)&FUN_00a05ee0, id);
    } else if (node->i3c == 2) {
        FUN_00a002f0(qb, h, 0);
        FUN_009ffee0(qb, h, g_kNegOne_13eb1bc);
    } else {
        FUN_00a002f0(qb, h, 0);
        FUN_009ffee0(qb, h, 1.0f);
    }

    if (tmp.mpBegin != 0 && tmp.mpBegin != buf)
        operator_delete__(tmp.mpBegin);
    return (uint32_t)(uint)h;
}

// @ 0x00a0c640
uint32_t AnimFbOwner::c640(uint32_t id, uint32_t* outIndex)
{
    uint32_t h = FUN_00a0c270(this, id, outIndex);
    qb_enable(mpQB, (int)h);
    return h;
}

// @ 0x00a0c670
void AnimFbOwner::c670(uint32_t id, uint32_t* outIndex)
{
    FUN_00a0c270(this, id, outIndex);
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

// @ 0x00a0d2d0
void* TreeMap::findOrInsert(uint* key)
{
    void* e  = root;
    void* lb = (char*)this + 4;
    if (e != 0) {
        do {
            uint nk = *(uint*)((char*)e + 0x10);
            if (nk < *key) {
                e = *(void**)e;
            } else {
                lb = e;
                e = *(void**)((char*)e + 4);
            }
        } while (e != 0);
    }
    if (lb != (char*)this + 4 && *(uint*)((char*)lb + 0x10) <= *key)
        return (char*)lb + 0x14;

    uint k[2];
    k[0] = *key;
    k[1] = 0;
    void* out;
    FUN_00a0ad10(&out, lb, k, 0);
    return (char*)out + 0x14;
}

// @ 0x00a0d350
void* KVec::copyCtor(const KVec& src)
{
    int n = (int)(src.end - src.begin);
    KF* base;
    if (n == 0)
        base = 0;
    else
        base = (KF*)EAAllocate(n * 0x18, "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    cap = (KF*)((char*)base + n * 0x18);
    begin = base;
    end = base;
    void* out;
    FUN_00a0c090(&out, src.begin, src.end, base, (void*)&src);
    end = (KF*)out;
    return this;
}

// @ 0x00a0d3e0
KF* __cdecl FUN_00a0d3e0(KF* first, KF* last, KF* dst)
{
    while (first != last) {
        dst->b = first->b;
        dst->prob = first->prob;
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x00a0d420
void ViewerData::Clear()
{
    VHelper* vh = (VHelper*)&vec;
    vh->dtor(vec.begin, vec.end);
    if (vec.begin != 0 && *(int*)((char*)vec.begin - 4) != 0)
        operator_delete__(vec.begin);

    uint16_t* b = s.begin;
    int gap = (int)(((char*)s.cap - (char*)b) & 0xfffffffe);
    if (gap > 2 && b != 0)
        operator_delete__(b);
}

// @ 0x00a0d470
void Cmd_s00a0_d2d0::Execute_470(void* parser)
{
    const char** a = ((Parser*)parser)->MainArguments(1);

    Rec_s00a0_d2d0 r;
    r.f0 = 1.0f;
    r.f4 = -1.0f;
    r.f8 = 0;
    r.s.begin = (uint16_t*)0x01667bac;
    r.s.end   = (uint16_t*)0x01667bac;
    r.s.cap   = (uint16_t*)0x01667bae;

    ObjA* o = (ObjA*)f30;
    RecVec* v = o->pv;
    if (v->end < v->cap) {
        Rec_s00a0_d2d0* slot = v->end;
        v->end = slot + 1;
        if (slot != 0)
            slot->ctorFrom(r);
    } else {
        v->growAt(v->end, r);
    }

    if ((((char*)r.s.cap - (char*)r.s.begin) & 0xfffffffe) > 2 && r.s.begin != 0)
        operator_delete__(r.s.begin);

    Rec_s00a0_d2d0* last = v->end - 1;
    WStr tmp;
    WStr* p = ConvertToString16(&tmp, a[0], -1);
    if (p != &last->s)
        last->s.Assign(p->begin, p->end);

    if ((((char*)tmp.cap - (char*)tmp.begin) & 0xfffffffe) > 2 && tmp.begin != 0)
        operator_delete__(tmp.begin);
}

// @ 0x00a0d570
void Cmd_s00a0_d2d0::notify(uint key)
{
    void* out;
    if (g_x166c058.f0 == 0)
        return;
    TreeMap* g = (TreeMap*)g_x166c058.f0;
    g->find(&out, &key);
    if (out != (char*)g + 4)
        return;
    TreeMap* t = (TreeMap*)((char*)this + 0x34);
    t->find(&out, &key);
    if (out != (char*)this + 0x38)
        return;

    struct K3 { uint a, b, c; } k;
    k.a = key;
    k.b = 0xee17c6ad;
    k.c = 0;

    void* mgr = GetManager();
    void* r = (void*)(*(void*(**)(void*, void*))(*(char**)mgr + 0x58))(mgr, &k);
    if (r == 0)
        return;

    void* b1 = 0;
    uint c1 = 0;
    bool ok = (bool)(*(char(**)(void*, void**, uint*, int, int, int))(*(char**)r + 0x34))(
        r, &b1, &c1, 1, 6, 1);
    if (!ok)
        goto release;
    {
        void* job = 0;
        FUN_00a09740(out, &job);
        void* slot = t->findOrInsert(&key);
        ((JobRef*)slot)->operator=(*(JobRef*)&job);
        if (job != 0)
            ((Job_s00a0_d2d0*)job)->Release();
    }
release:
    if (out != 0)
        (*(void(**)(void*))(*(char**)out + 8))(out);
}

// @ 0x00a0d9c0
void AnimTree::nukeSubtree(AnimNode_s00a0_d2d0* n)
{
    while (n != 0) {
        nukeSubtree(n->l);
        AnimNode_s00a0_d2d0* next = n->r;
        VHelper* vh = (VHelper*)&n->vec;
        vh->dtor(n->vec.begin, n->vec.end);
        if (n->vec.begin != 0 && *(int*)((char*)n->vec.begin - 4) != 0)
            operator_delete__(n->vec.begin);
        uint16_t* b = n->s.begin;
        int gap = (int)(((char*)n->s.cap - (char*)b) & 0xfffffffe);
        if (gap > 2 && b != 0)
            operator_delete__(b);
        operator_delete__(n);
        n = next;
    }
}

// @ 0x00a0da40
void KVec::insertAt(KF* pos, uint count, const KF& value)
{
    uint n = (uint)(end - begin);
    if ((uint)(cap - begin) >= count) {
        if (count != 0) {
            FUN_00a0a520((void*)&value);
            float p = value.prob;
            uint tail = (uint)((KF*)end - pos);
            if (count < tail) {
                KF* bail = end - count;
                void* out;
                FUN_00a0c090(&out, bail, end, end, end);
                end = (KF*)((char*)end + count * 0x18);
                FUN_00a0c230(pos, bail, (void*)out);
                FUN_00a0d850(pos, (KF*)((char*)pos + count * 0x18), &value);
            } else {
                FUN_00a0ade0(end, count - tail, &value);
                end = (KF*)((char*)end + (count - tail) * 0x18);
                void* out;
                FUN_00a0c090(&out, pos, (void*)(end), end, end);
                end = (KF*)((char*)end + tail * 0x18);
                FUN_00a0d850(pos, (KF*)end, &value);
            }
            FUN_00a09810((void*)&value, (void*)((char*)&value + 1));
            (void)p;
        }
        return;
    }

    uint old = (uint)((char*)end - (char*)begin) / 0x18;
    uint want = old * 2;
    if (old == 0)
        want = 1;
    uint need = old + count;
    if (need < want)
        need = want;
    KF* nb;
    if (need == 0)
        nb = 0;
    else
        nb = (KF*)EAAllocate(need * 0x18, "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    KF* m1 = (KF*)FUN_00a0af70(begin, pos, nb);
    FUN_00a0a580(begin, pos, nb);
    FUN_00a0ade0(m1, count, &value);
    KF* m2 = (KF*)((char*)m1 + count * 0x18);
    KF* e1 = end;
    KF* m3 = (KF*)FUN_00a0af70(pos, e1, m2);
    FUN_00a0a580(pos, e1, m2);
    if (begin != 0 && *(int*)((char*)begin - 4) != 0)
        operator_delete__(begin);
    begin = nb;
    end = m3;
    cap = (KF*)((char*)nb + need * 0x18);
}

// @ 0x00a0dd90
KVec& KVec::operator=(const KVec& o)
{
    if (&o != this) {
        uint n = (uint)(o.end - o.begin);
        if ((uint)(cap - begin) < n) {
            KF* nb = (KF*)FUN_00a0d740(n, o.begin, o.end);
            VHelper* vh = (VHelper*)this;
            vh->dtor(begin, end);
            if (begin != 0 && *(int*)((char*)begin - 4) != 0)
                operator_delete__(begin);
            cap = (KF*)((char*)nb + n * 0x18);
            begin = nb;
            end = (KF*)((char*)nb + n * 0x18);
        } else {
            uint have = (uint)(end - begin);
            if (have < n) {
                FUN_00a0d3e0(o.begin, o.begin + have, begin);
                void* out;
                FUN_00a0c090(&out, o.begin + have, o.end, end, o.end);
                end = (KF*)((char*)begin + n * 0x18);
            } else {
                KF* r = FUN_00a0d3e0(o.begin, o.end, begin);
                VHelper* vh = (VHelper*)this;
                vh->dtor(r, end);
                end = (KF*)((char*)begin + n * 0x18);
            }
        }
    }
    return *this;
}

// @ 0x00a0df30
S& S::operator=(const S& o)
{
    id = o.id;
    WideStr_s00a0_d2d0* src = (WideStr_s00a0_d2d0*)&o.s;
    if (src != &s)
        s.Assign(src->begin, src->end);
    f14 = o.f14;
    f18 = o.f18;
    b1c = o.b1c;
    b1d = o.b1d;
    b1e = o.b1e;
    f20 = o.f20;
    f24 = o.f24;
    f28 = o.f28;
    vec = o.vec;
    return *this;
}

// @ 0x00a0dfa0
bool CleanupObj::Unregister()
{
    if (f54 != 0) {
        void* h = f54;
        f54 = 0;
        RemoveHandler(h, f58, f5c, f60, f64);
    }
    f80 = 0;
    if (f84 != 0) {
        RefCounted* p = f84;
        f84 = 0;
        if (_InterlockedExchangeAdd((volatile long*)&p->refcount, -1) == 1) {
            _InterlockedExchange((volatile long*)&p->refcount, 1);
            p->Destroy(true);
        }
    }
    {
        void* anchor = (char*)this + 0x1c;
        for (void* it = *(void**)((char*)this + 0x20); it != anchor;
             it = RBTreeIncrement(it)) {
            void* sd = *(void**)((char*)it + 0x18);
            if (sd != 0) {
                ((StaticData_s00a0_d2d0*)sd)->Clear(0);
                sd = *(void**)((char*)it + 0x18);
                if (sd != 0) {
                    *(void**)((char*)it + 0x18) = 0;
                    ((StaticData_s00a0_d2d0*)sd)->Release();
                }
            }
        }
    }
    ((AnimTree*)((char*)this + 0x18))->nukeSubtree(*(AnimNode_s00a0_d2d0**)((char*)this + 0x24));
    {
        void** anchor = (void**)((char*)this + 0x1c);
        anchor[0] = anchor;
        *(void**)((char*)this + 0x20) = anchor;
        *(void**)((char*)this + 0x24) = 0;
        *((uint8_t*)this + 0x28) = 0;
        *(void**)((char*)this + 0x2c) = 0;
    }
    g_tree1551a68.nukeSubtree((AnimNode_s00a0_d2d0*)g_tree1551a68.root);
    g_tree1551a68.anchor  = &g_tree1551a68.anchor;
    g_tree1551a68.endNode = &g_tree1551a68.anchor;
    g_tree1551a68.root    = 0;
    g_tree1551a68.color   = 0;
    g_tree1551a68.count   = 0;
    FUN_009a9680();
    g_p166cc08_s00a0_d2d0 = 0;
    return true;
}

// @ 0x00a0e0b0
void KVec::resize(uint a)
{
    uint n = (uint)(end - begin);
    if (a > n) {
        KF tmp;
        tmp.b.w[0] = 0;
        tmp.b.w[1] = 0;
        tmp.b.w[2] = 0;
        tmp.prob = 1.0f;
        RecDtor* rd = (RecDtor*)&tmp;
        rd->dtor(0, 0);
        insertAt(end, a - n, tmp);
        FUN_00a09810((void*)tmp.b.w, (void*)((char*)tmp.b.w + 4));
        if (tmp.b.w[0] != 0 && *(int*)((char*)tmp.b.w[0] - 4) != 0)
            operator_delete__((void*)tmp.b.w[0]);
    } else {
        FUN_00a0dee0(begin + a, end);
    }
}

// @ 0x00a0e250
void S::reset()
{
    id = 0xffffffff;
    if (s.end != s.begin) {
        *s.begin = 0;
        s.end = s.begin;
    }
    f14 = 0.0f;
    f18 = -1.0f;
    b1c = 0;
    b1d = 0;
    b1e = 0;
    f20 = 0;
    f24 = 0;
    f28 = 4;

    KF* b = vec.begin;
    KF* e = vec.end;
    KF* r = FUN_00a0d3e0(e, e, b);
    VHelper* vh = (VHelper*)&vec;
    vh->dtor(r, e);
    vec.end = (KF*)((char*)vec.end + ((uint)((char*)e - (char*)b) / 0x18) * 0x18);
}

// @ 0x00a0e2e0
void Cmd_s00a0_d2d0::ResetCmd(void* parser)
{
    (void)parser;
    f30->s.reset();
    f30->f4c = 0.0f;
    f30->f50 = 1.0f;
    f30->f54 = -1.0f;
    f30->s.f14 = f30->f04;
    f30->s.vec.resize(1);
    f04->v35(this);
}

// @ 0x00a0e350
void Cmd_s00a0_d2d0::AddProb(void* parser)
{
    f30->s.vec.resize((uint)(f30->s.vec.end - f30->s.vec.begin) + 1);
    float f = 1.0f;
    const char** a = ((Parser*)parser)->OptionArguments("probability", 1);
    if (a != 0)
        f = f04->v38(a[0]);
    f30->s.vec.end[-1].prob = f;
    f30->f4c += f;
    f04->v35(this);
}

// @ 0x00a0e3f0
void Cmd_s00a0_d2d0::SetName(void* parser)
{
    f30->s.reset();
    f30->f4c = 0.0f;
    f30->f50 = 1.0f;
    f30->f54 = -1.0f;
    f30->s.f14 = f30->f04;
    const char** a = ((Parser*)parser)->MainArguments(2);
    f30->s.id = f04->v40(a[0]);
    WStr tmp;
    WStr* p = ConvertToString16(&tmp, a[1], -1);
    if (p != &f30->s.s)
        f30->s.s.Assign(p->begin, p->end);
    int gap = (int)(((char*)tmp.cap - (char*)tmp.begin) & 0xfffffffe);
    if (gap > 2 && tmp.begin != 0)
        operator_delete__(tmp.begin);
    f04->v35(this);
}

// @ 0x00a0e4c0
AnimParseContext::AnimParseContext(EntryMap* map)
: mMagic(0x2328502), mF4(0.0f), mpMap(map), mF4c(0.0f), mW0(1.0f), mW4(-1.0f)
{
}

// @ 0x00a0e530
Entry* EntryMap::GetOrInsert(const uint* key)
{
    RBNode* header = &anchor;
    RBNode* x = header->parent;
    RBNode* y = header;
    while (x) {
        if (((AnimNode_s00a0_e4c0*)x)->key < *key) {
            x = x->right;
        } else {
            y = x;
            x = x->left;
        }
    }
    if (y == header || *key < ((AnimNode_s00a0_e4c0*)y)->key) {
        Entry e;
        EntryPair pair(*key, e);
        union { AnimNode_s00a0_e4c0* node; uint raw; uint8_t byte; } out;
        out.byte = 0;
        Insert(&out.node, y, &pair, out.raw);
        return &out.node->value;
    }
    return &((AnimNode_s00a0_e4c0*)y)->value;
}

// @ 0x00a0e690
void AnimCommandA::OnEndBlock(char flag)
{
    if (flag) return;
    if (mpContext->mEntry.subs.mpBegin == mpContext->mEntry.subs.mpEnd) {
        PrintError("AnimList parsing error: no existing mChoices!?\n", "AnimList parsing error!");
        return;
    }
    uint n = (uint)(mpContext->mEntry.subs.mpBegin->items.mpEnd
                  - mpContext->mEntry.subs.mpBegin->items.mpBegin);
    for (uint i = 0; i < n; i++) {
        Item* it = &mpContext->mEntry.subs.mpBegin->items.mpBegin[i];
        wchar_t* full = it->name.mpBegin;
        wchar_t* slash = wcsrchr(full, L'/');
        wchar_t* base = slash ? slash + 1 : full;
        if (i == 0) {
            wchar_t* end = base;
            while (*end) ++end;
            mpContext->mEntry.name.assign(base, end);
        }
        it->w8 = FNV1_String16(base, 0x811c9dc5, 1);
        it->w0 = mpContext->mW0;
        it->w4 = mpContext->mW4;
    }
    if (mpContext->mEntry.i28 == 4) {
        char buf[1024];
        sprintf(buf, "animId 0x%08x : No end mode defined", mpContext->mEntry.key);
        PrintError(buf, "AnimList parsing error!");
        return;
    }
    RBNode* found;
    mpContext->mpMap->Find(&found, &mpContext->mEntry.key);
    if (found == &mpContext->mpMap->anchor || mpContext->mEntry.f14 >= ((AnimNode_s00a0_e4c0*)found)->value.f14) {
        Entry* d = mpContext->mpMap->GetOrInsert(&mpContext->mEntry.key);
        *d = mpContext->mEntry;
    }
}

// @ 0x00a0e840
void AnimCommandB::OnEndBlock(char flag)
{
    if (flag) return;
    if (mpContext->mEntry.subs.mpBegin == mpContext->mEntry.subs.mpEnd) return;
    float scale = 1.0f;
    if (mpContext->mF4c > 0.0f) scale = 1.0f / mpContext->mF4c;
    uint n = (uint)(mpContext->mEntry.subs.mpEnd - mpContext->mEntry.subs.mpBegin);
    float prev = 0.0f;
    for (uint i = 0; i < n; i++) {
        float v = mpContext->mEntry.subs.mpBegin[i].f14 * scale + prev;
        mpContext->mEntry.subs.mpBegin[i].f14 = v;
        prev = v;
    }
    mpContext->mEntry.subs.mpEnd[-1].f14 = 1.0f;
    if (mpContext->mEntry.i28 == 4) {
        char buf[1024];
        sprintf(buf, "animId 0x%08x : No end mode defined", mpContext->mEntry.key);
        PrintError(buf, "AnimList parsing error!");
        return;
    }
    RBNode* found;
    mpContext->mpMap->Find(&found, &mpContext->mEntry.key);
    if (found == &mpContext->mpMap->anchor || mpContext->mEntry.f14 >= ((AnimNode_s00a0_e4c0*)found)->value.f14) {
        Entry* d = mpContext->mpMap->GetOrInsert(&mpContext->mEntry.key);
        *d = mpContext->mEntry;
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
