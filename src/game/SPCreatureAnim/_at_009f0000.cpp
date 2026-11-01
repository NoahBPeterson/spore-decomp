// src/game/SPCreatureAnim/_at_009f0000.cpp -- migrated from slice(s) s009ffa00, s009feb30, s009fdb00, s009fb8e0, s009fa9a0, s009f9b40 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/_at_009f0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" const float g_014853e0;          // 0x014853e0
extern "C" const float g_01551638;          // 0x01551638
extern "C" const float g_0166c990;          // 0x0166c990
extern "C" const float g_0155163c;          // 0x0155163c
extern "C" const float g_01550b08;          // 0x01550b08
extern "C" const float g_01551678;          // 0x01551678
extern "C" const float g_0155167c;          // 0x0155167c
extern "C" const float g_01551680;          // 0x01551680
extern "C" const float g_01551684;          // 0x01551684
extern "C" float* fn_0099c1a0(float* out, const float* quat, const float* vec); // 0x0099C1A0
extern "C" float* fn_009ac7a0(float* a, float* b, float* c, int d);  // 0x009AC7A0
extern "C" const float g_01550b00;          // 0x01550b00
extern "C" const float g_013f11c8;          // 0x013f11c8
extern "C" const float g_01485378;          // 0x01485378
extern "C" const int g_01550afc;            // 0x01550afc
#ifndef S009F9B40_H
#endif
#include <string.h>
#include <math.h>
#include "EA/ArgScript/cCommandBase.h"
#include "nSPCreatureAnim/creature_instance_data.h"
#include <intrin.h>

// ---- items of slice s009f9b40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct AnimLayout;
struct AnimHierarchy
{
    char pad0[0x128];
    float m_quat[4];        // +0x128
    char pad138[0x204 - 0x138];
    int m_204;              // +0x204
    int m_208;              // +0x208
    int m_20c;              // +0x20C
    char pad210[0x344 - 0x210];
    float m_v344[3];        // +0x344
    float m_v350[3];        // +0x350
    float m_v35c[3];        // +0x35C
    char pad368[0x370 - 0x368];
    unsigned char m_flag370;    // +0x370
    unsigned char m_flag371;    // +0x371
};
struct AnimNodeBlock
{
    char pad0[0x190];
    float m_src[7];         // +0x190..+0x1A8
};
struct AnimLayout
{
    AnimHierarchy* m_hier;      // +0x00
    char pad04[4];
    AnimNodeBlock* m_nodes;     // +0x08
    char pad0C[4];
    unsigned char m_flag10;     // +0x10
    char pad11[0x38 - 0x11];
    unsigned char m_flag38;     // +0x38
    char pad39[0x70 - 0x39];
    float m_f70;                // +0x70
    char pad74[0x138 - 0x74];
    float m_f138;               // +0x138
    char pad13C[4];
    float m_f140;               // +0x140
    char pad144[4];
    float m_quat[4];            // +0x148..+0x154
    float m_v158[3];            // +0x158
    float m_v164[3];            // +0x164
    float m_mat[7];             // +0x170..+0x188
    char pad18C[4];
    float m_src[7];             // +0x190..+0x1A8
    int m_counter;              // +0x1AC
    float m_f1b0;               // +0x1B0
    float m_f1b4;               // +0x1B4
    union
    {
        float m_f1b8;           // +0x1B8
        unsigned char m_cache[0x40];// +0x1B8 (same slot, byte view)
    };
    unsigned char m_mirror[0x40];// +0x1F8
    char pad238[0x2e4 - 0x238];
    unsigned char* m_poolBegin; // +0x2E4
    unsigned char* m_poolEnd;   // +0x2E8
    char pad2EC[0x370 - 0x2EC];
    unsigned char m_flag370;    // +0x370
    unsigned char m_flag371;    // +0x371
};
extern "C" const float g_014853e0;          // 0x014853e0
extern "C" const float g_01551638;          // 0x01551638
extern "C" const float g_0166c990;          // 0x0166c990
extern "C" const float g_0155163c;          // 0x0155163c
extern "C" const float g_01550b08;          // 0x01550b08
extern "C" const float g_01551678;          // 0x01551678
extern "C" const float g_0155167c;          // 0x0155167c
extern "C" const float g_01551680;          // 0x01551680
extern "C" const float g_01551684;          // 0x01551684
extern "C" void fn_009fa310(AnimLayout* owner, AnimLayout* self);   // 0x009FA310
extern "C" void fn_009f9e20(AnimLayout* owner, AnimLayout* self);   // 0x009F9E20
extern "C" void fn_009fa170(AnimLayout* self);                      // 0x009FA170
extern "C" float* fn_0099c1a0(float* out, const float* quat, const float* vec); // 0x0099C1A0
extern "C" float* fn_009ac7a0(float* a, float* b, float* c, int d);  // 0x009AC7A0
extern "C" const float g_01550b00;          // 0x01550b00
extern "C" const float g_013f11c8;          // 0x013f11c8
extern "C" const float g_01485378;          // 0x01485378
extern "C" const int g_01550afc;            // 0x01550afc
// ---- items of slice s009f9b40 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void fn_009fa310(AnimLayout* owner, AnimLayout* self);   // 0x009FA310
extern "C" void fn_009f9e20(AnimLayout* owner, AnimLayout* self);   // 0x009F9E20
extern "C" void fn_009fa170(AnimLayout* self);                      // 0x009FA170

// ---- items of slice s009fa9a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int   g_01550ad8;                                      // +0x1550ad8
extern float g_01550adc;                                      // +0x1550adc
extern float g_01550ae0;                                      // +0x1550ae0
extern float g_01550ae4;                                      // +0x1550ae4
extern float g_01550ae8;                                      // +0x1550ae8
extern float g_01550aec;                                      // +0x1550aec
extern float g_01550af0;                                      // +0x1550af0
extern float g_01551648;                                      // +0x1551648
extern float g_0166c980;                                      // +0x166c980
struct Vec3_s009fa9a0 { float x, y, z; };
struct Quat_s009fa9a0 { float x, y, z, w; };
struct Jnt_s009fa9a0 { Vec3_s009fa9a0 pos; Quat_s009fa9a0 rot; float _pad; };
struct B_s009fa9a0;
struct Cr_s009fa9a0 {
	char _pad000[0x70];
	float m70;                    // +0x70
	char _pad074[0xa4 - 0x74];
	Vec3_s009fa9a0 mA4;           // +0xa4
	char _pad0b0[0xbc - 0xb0];
	Vec3_s009fa9a0 mBC;           // +0xbc
	Quat_s009fa9a0 mC8;           // +0xc8
	char _pad0d8[0x1ac - 0xd8];
	int  m1ac;                    // +0x1ac
	char _pad1b0[0x204 - 0x1b0];
	int  m204;                    // +0x204
	char _pad208[0x20c - 0x208];
	int  m20c;                    // +0x20c
	char _pad210[0x2e4 - 0x210];
	B_s009fa9a0* mBodiesBegin;    // +0x2e4
	B_s009fa9a0* mBodiesEnd;      // +0x2e8
	char _pad2ec[0x35c - 0x2ec];
	Vec3_s009fa9a0 m35c;          // +0x35c
	float m368;                   // +0x368
	char _pad36c[0x370 - 0x36c];
	char  m370;                   // +0x370
	char _pad371[0x374 - 0x371];
	float m374;                   // +0x374
};
struct B_s009fa9a0 {
	Cr_s009fa9a0* owner;          // +0x00  back-pointer to the creature
	int _m04;                     // +0x04
	B_s009fa9a0*  link;           // +0x08  neighbouring body
	char _pad00c[0x144 - 0x0c];
	int  m144;                    // +0x144
	Quat_s009fa9a0 m148;          // +0x148  joint orientation
	Vec3_s009fa9a0 m158;          // +0x158  angular velocity
	Vec3_s009fa9a0 m164;          // +0x164  accumulated torque
	Jnt_s009fa9a0  jnt[2];        // +0x170, +0x190
};
void F_009b4ba0(void* out, const void* q, int n);          // 0x009b4ba0
void F_0099c1a0(void* out, const void* q, const void* v);  // 0x0099c1a0  checkerlib::QuaternionVectorTransform
void F_0099c310(void* out, const void* q, const void* v);  // 0x0099c310
void F_009fa170(B_s009fa9a0* body);                        // 0x009fa170
void F_009f9dc0(Cr_s009fa9a0* cr, B_s009fa9a0* b);         // 0x009f9dc0
void F_009f9e20(Cr_s009fa9a0* cr, B_s009fa9a0* b);         // 0x009f9e20
void F_009fa770(Cr_s009fa9a0* cr, B_s009fa9a0* b);         // 0x009fa770
void F_009fa870(Cr_s009fa9a0* cr, B_s009fa9a0* b);         // 0x009fa870
extern int   g_01550afc_s009f_a9a0;                                      // +0x1550afc
extern float g_01551678_s009f_a9a0;                                      // +0x1551678
extern float g_0155167c_s009f_a9a0;                                      // +0x155167c
extern float g_01551680_s009f_a9a0;                                      // +0x1551680
extern float g_01551684_s009f_a9a0;                                      // +0x1551684
void f_009fa9a0(float* out, Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt);
void f_009fae30(float* out, Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt);
void f_009fb090(float* out, Cr_s009fa9a0* cr, B_s009fa9a0* body);
void f_009fb130(B_s009fa9a0* body, float dt);
void f_009fb510(Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt);
void f_009fb7c0(Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt);
void f_009fb830(Cr_s009fa9a0* cr, float dt);
// ---- items of slice s009fa9a0 end

// ---- items of slice s009fb8e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*  EA_Audio_GetSystemAT();                 // 0x00a206f0
extern void*  SP_AudioSystem();                       // 0x0067cb00
extern void*  SP_EffectsManager();                    // 0x0067ddd0
extern void   FUN_009fb830(void* self, float v);      // 0x009fb830
extern float  g_166c978;   // 0x0166c978  timer max
extern float  g_166c974;   // 0x0166c974  timer period
extern float  g_13ec4b8;   // 0x013ec4b8  epsilon
extern void*  g_166c074;   // 0x0166c074
extern void*  g_166c078;   // 0x0166c078
extern void*  g_166c07c;   // 0x0166c07c
extern void*  g_166c080;   // 0x0166c080
extern float  g_166ca38;   // 0x0166ca38
extern float  g_166ca3c;   // 0x0166ca3c
extern float  g_166ca40;   // 0x0166ca40
extern float  g_1485720;   // 0x01485720 (1.0f)
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
struct FUN_009b3010 { void reset(); };                // 0x009b3010 (thiscall)
extern uint32 EA_Hash_FNV1_String8(const char* s, uint32 seed, int len);   // 0x00932e80
extern uint8  g_166cb6c;   // 0x0166cb6c  matrix literal
typedef void  (__thiscall *vt_v0)(void*);
typedef void  (__thiscall *vt_v_i)(void*, int);
typedef void  (__thiscall *vt_v_ii)(void*, int, int);
typedef void  (__thiscall *vt_v_iii)(void*, int, int, int);
typedef int   (__thiscall *vt_i_i)(void*, int);
typedef float (__thiscall *vt_f_i)(void*, int);
typedef void  (__thiscall *vt_v_if)(void*, int, float);
typedef void  (__thiscall *vt_v_p)(void*, void*);
typedef char  (__thiscall *vt_c_pii)(void*, void*, int, void**);
typedef void* (__thiscall *vt_p0)(void*);
#define VT(obj, off)  (*(void***)(obj))[(off) / 4]
static const float& minf(const float& a, const float& b) { return a > b ? b : a; }
struct FUN_0041cb40 { void ctor(void* src); };   // 0x0041cb40 (thiscall, ret 4)
struct EventDesc {
    uint16 flags;      // +0x00
    uint16 count;      // +0x02
    float  f04;        // +0x04
    float  f08;        // +0x08
    float  f0c;        // +0x0c
    float  f10;        // +0x10
    float  m[9];       // +0x14
};
struct V3 { float x, y, z; };
struct M9 { float m[9]; };
__declspec(noinline)

// ================================================================== @ 0x009fc090

// ================================================================== @ 0x009fc0f0

struct RBFind { void find(uint32* out, const uint32* key); };   // 0x00e5c780 (thiscall, ret 8)
// ---- items of slice s009fb8e0 end

// ---- items of slice s009fdb00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void   ElemFree(void* p);                                       // 0x00f47380
extern void* DoInsertValue(void* this_, void* pos, int flag);          // 0x0011e0744
struct SimpleVec32 {
    uint32* begin;
    uint32* end;
    uint32* cap;
    void DoInsertValue(uint32* pos, const uint32* value);              // 0x004558a0
};
struct MapIdxC {
    void* f0;
    void* anchor0;
    void* anchor1;
    void* root;
    void* f10;
    uint32 size;
    uint32* insert(const uint32& key);                                 // 0x009fe560
    void* insertImpl(void* out, void* hint, const void* key, const void* value, int flag); // 0x009fe490
};
struct VecImpl { void DoAllocate(uint32 n, const void* allocSrc); };   // 0x004aa350
// ---- items of slice s009fdb00 end

// ---- items of slice s009feb30 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
static inline const float& clampMax(const float& a, const float& b) { return a < b ? b : a; }
static inline const float& clampMin(const float& a, const float& b) { return a < b ? a : b; }
// ---- items of slice s009feb30 end

// ---- items of slice s009ffa00 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct AnimGoal_s009f_fa00;
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
// ---- items of slice s009ffa00 end

// @ 0x009f9c60
float animLayoutScale(AnimLayout* self)
{
    float d = self->m_f140 * self->m_f138;
    d = d * g_014853e0;
    d = d / g_01551638;
    float inv = 1.0f / sqrtf(d);
    float r;
    if (inv > g_0166c990)
        r = inv;
    else
        r = g_0166c990;
    if (r > g_0155163c)
        r = g_0155163c;
    if (self->m_flag371 != 0)
        r *= g_01550b08;
    return r;
}

// @ 0x009f9dc0
void animLayoutSyncMat(void* unused, AnimLayout* self)
{
    self->m_mat[0] = self->m_src[0];
    self->m_mat[1] = self->m_src[1];
    self->m_mat[2] = self->m_src[2];
    self->m_mat[3] = self->m_src[3];
    self->m_mat[4] = self->m_src[4];
    self->m_mat[5] = self->m_src[5];
    self->m_mat[6] = self->m_src[6];
}

// @ 0x009f9e20
void fn_009f9e20(AnimLayout* owner, AnimLayout* self)
{
    AnimHierarchy* h = self->m_hier;
    AnimNodeBlock* nodes = self->m_nodes;

    float A = nodes->m_src[3];
    float F = nodes->m_src[4];
    float E = nodes->m_src[5];
    float Dw = nodes->m_src[6];
    float B = h->m_quat[0];
    float Z = h->m_quat[1];
    float C = h->m_quat[2];
    float W = h->m_quat[3];

    // the original's association: (((B*Dw + A*W) - Z*E) + C*F) and so on; the parentheses keep the
    // /fp:fast reassociator from regrouping the terms (a 1-ulp difference shows up in the equiv test)
    float r1 = ((B * Dw + A * W) - Z * E) + C * F;
    float r2 = ((E * B + Z * Dw) + F * W) - C * A;
    float r3 = ((E * W - F * B) + C * Dw) + Z * A;
    float r4 = ((Dw * W - B * A) - F * Z) - C * E;

    float q0 = self->m_quat[0];
    float q1 = self->m_quat[1];
    float q2 = self->m_quat[2];
    float q3 = self->m_quat[3];

    float o0 = ((q0 * r4 + q3 * r1) - q1 * r3) + q2 * r2;
    float o1 = ((q1 * r4 + q0 * r3) + q3 * r2) - q2 * r1;
    float o2 = (q3 * r3 - q0 * r2) + q2 * r4 + q1 * r1;
    float o3 = (q3 * r4 - q0 * r1) - q1 * r2 - q2 * r3;

    self->m_src[3] = o0;
    self->m_src[4] = o1;
    self->m_src[6] = o3;
    self->m_src[5] = o2;

    float f = owner->m_f70;

    float v1[3];
    v1[0] = h->m_v350[0] * f;
    v1[1] = h->m_v350[1] * f;
    v1[2] = h->m_v350[2] * f;

    float out1[3];
    fn_0099c1a0(out1, nodes->m_src + 3, v1);

    float px = nodes->m_src[0] + out1[0];
    float py = nodes->m_src[1] + out1[1];
    float pz = nodes->m_src[2] + out1[2];
    self->m_f1b4 = py;
    self->m_f1b0 = px;
    self->m_f1b8 = pz;

    float v2[3];
    v2[0] = h->m_v344[0] * f;
    v2[1] = h->m_v344[1] * f;
    v2[2] = h->m_v344[2] * f;

    float out2[3];
    fn_0099c1a0(out2, self->m_src + 3, v2);

    self->m_src[0] = self->m_f1b0 - out2[0];
    self->m_src[1] = self->m_f1b4 - out2[1];
    self->m_src[2] = self->m_f1b8 - out2[2];
    self->m_flag38 = 1;
}

// @ 0x009fa170
void fn_009fa170(AnimLayout* self)
{
    float w = fabsf(self->m_quat[3]);
    float d = w - g_01550b00;
    // The shipped guard compares the epsilon slot (0x13F11C8) against K - |w| (x87 FCOMIP st(2)),
    // i.e. it proceeds only while the real part sits at the target magnitude.
    if (!(d < g_013f11c8))
        return;

    float x = self->m_quat[0];
    float y = self->m_quat[1];
    float z = self->m_quat[2];
    // the original sums x*x, then z*z, then y*y (fld [esp+4] = x, fld [esp+0x14] = z, fld [esp] = y);
    // the numerator is the constant 1 - K*K (K stays on the x87 stack across the guard)
    float s = sqrtf((1.0f - g_01550b00 * g_01550b00) / (x * x + z * z + y * y));

    self->m_quat[0] = x * s;
    self->m_quat[1] = y * s;
    self->m_quat[2] = z * s;
    self->m_quat[3] = g_01550b00;

    // it accumulates (v1*y + v2*z) + v0*x; keep that order against /fp:fast reassociation
    float dot = (self->m_v158[1] * y + self->m_v158[2] * z) + self->m_v158[0] * x;
    if (!(dot > g_01485378))
        return;

    float len2 = (self->m_v158[0] * self->m_v158[0] + self->m_v158[1] * self->m_v158[1])
                 + self->m_v158[2] * self->m_v158[2];
    if (!(len2 > g_013f11c8))
        return;

    // the x87 chain recomputes the length in extended precision (no overflow) and divides *dot* twice:
    // first by the recomputed length, then by sqrt(len2) as stored
    float len = sqrtf(self->m_v158[0] * self->m_v158[0] + self->m_v158[1] * self->m_v158[1]
                      + self->m_v158[2] * self->m_v158[2]);
    float k = 1.0f - (dot / len) / sqrtf(len2);
    self->m_v158[0] = self->m_v158[0] * k;
    self->m_v158[1] = self->m_v158[1] * k;
    self->m_v158[2] = self->m_v158[2] * k;
}

// @ 0x009fa310
void fn_009fa310(AnimLayout* owner, AnimLayout* self)
{
    AnimHierarchy* h = self->m_hier;

    if (h->m_flag370 != 0)
    {
        float f = owner->m_f70;
        AnimNodeBlock* nodes = self->m_nodes;

        float vq[3];
        vq[0] = h->m_v350[0] * f;
        vq[1] = h->m_v350[1] * f;
        vq[2] = h->m_v350[2] * f;

        float out1[3];
        fn_0099c1a0(out1, nodes->m_src + 3, vq);

        float P[3];
        P[0] = nodes->m_src[0] + out1[0];
        P[1] = nodes->m_src[1] + out1[1];
        P[2] = nodes->m_src[2] + out1[2];

        float vc[3];
        vc[0] = h->m_v35c[0] * f;
        vc[1] = h->m_v35c[1] * f;
        vc[2] = h->m_v35c[2] * f;

        float out2[3];
        fn_0099c1a0(out2, self->m_src + 3, vc);

        float D[4];
        D[0] = P[0] - (self->m_f1b0 - out2[0]);
        D[1] = P[1] - (self->m_f1b4 - out2[1]);
        D[2] = P[2] - (self->m_f1b8 - out2[2]);
        D[3] = 0.0f;

        float A = nodes->m_src[3];
        float F = nodes->m_src[4];
        float E = nodes->m_src[5];
        float Dw = nodes->m_src[6];
        float B = h->m_quat[0];
        float Z = h->m_quat[1];
        float C = h->m_quat[2];
        float W = h->m_quat[3];

        float r1 = B * Dw + A * W - Z * E + C * F;
        float r2a = E * B;
        float r2b = r2a + Z * Dw;
        float r2c = r2b + F * W;
        float r2 = r2c - C * A;
        float r3 = E * W - F * B + C * Dw + Z * A;
        float r4 = Dw * W - B * A - F * Z - C * E;

        // R^T * D built from the quaternion (x,y,z,w) = (r1,r2,r3,r4). The negated pairwise
        // products are separate temporaries because the original builds them with a sign flip and
        // then adds/subtracts them, which decides the sign of a propagated NaN.
        float nr4r2 = -(r4 * r2);
        float nr4r3 = -(r4 * r3);
        float nr1r1 = -(r1 * r1);
        float nr2r2 = -(r2 * r2);
        float nr3r3 = -(r3 * r3);
        float nr4r1 = -(r4 * r1);

        float c0a = r3 * r1 + nr4r2;
        float c0b = r2 * r1 - nr4r3;
        float c0c = nr2r2 + nr3r3;

        float c1a = r3 * r2 - nr4r1;
        float c1b = nr3r3 + nr1r1;
        float c1c = r2 * r1 + nr4r3;

        float c2a = nr2r2 + nr1r1;
        float c2b = r3 * r2 + nr4r1;
        float c2c = r3 * r1 - nr4r2;

        float t0 = c0a * D[2] + c0b * D[1];
        float m0 = D[0] + 2.0f * (t0 + c0c * D[0]);

        float t1 = c1a * D[2] + c1b * D[1];
        float m1 = D[1] + 2.0f * (t1 + c1c * D[0]);

        float t2 = c2a * D[2] + c2b * D[1];
        float m2 = D[2] + 2.0f * (t2 + c2c * D[0]);

        float M[3];
        M[0] = m0;
        M[1] = m1;
        M[2] = m2;

        fn_009ac7a0(D, vc, M, 0);
        self->m_quat[0] = D[0];
        self->m_quat[1] = D[1];
        self->m_quat[2] = D[2];
        self->m_quat[3] = D[3];

        if (g_01550afc != 0)
            fn_009fa170(self);
    }
    else
    {
        self->m_quat[0] = g_01551678;
        self->m_quat[1] = g_0155167c;
        self->m_quat[2] = g_01551680;
        self->m_quat[3] = g_01551684;
    }

    self->m_v158[0] = 0.0f;
    self->m_v158[1] = 0.0f;
    self->m_v158[2] = 0.0f;
    self->m_v164[0] = 0.0f;
    self->m_v164[1] = 0.0f;
    self->m_v164[2] = 0.0f;

    fn_009f9e20(owner, self);
    animLayoutSyncMat(owner, self);
}

// @ 0x009fa770
void animLayoutEvaluateAll(AnimLayout* owner, AnimLayout* self)
{
    fn_009fa310(owner, self);

    AnimHierarchy* h = self->m_hier;
    unsigned n = (unsigned)h->m_20c;
    int off = h->m_204 * 0x2bc;
    for (unsigned i = 0; i < n; i++)
    {
        fn_009fa310(owner, (AnimLayout*)((char*)owner->m_poolBegin + off));
        off += 0x2bc;
    }
}

// @ 0x009fa7d0
void animLayoutResetOne(AnimLayout* owner, AnimLayout* self)
{
    self->m_quat[0] = g_01551678;
    self->m_quat[1] = g_0155167c;
    self->m_quat[2] = g_01551680;
    self->m_quat[3] = g_01551684;

    self->m_v158[0] = 0.0f;
    self->m_v158[1] = 0.0f;
    self->m_v158[2] = 0.0f;
    self->m_v164[0] = 0.0f;
    self->m_v164[1] = 0.0f;
    self->m_v164[2] = 0.0f;

    fn_009f9e20(owner, self);
    animLayoutSyncMat(owner, self);
}

// @ 0x009fa870
void animLayoutResetAll(AnimLayout* owner, AnimLayout* self)
{
    animLayoutResetOne(owner, self);

    AnimHierarchy* h = self->m_hier;
    int idx = h->m_204;
    unsigned n = (unsigned)h->m_20c;
    int off = idx * 0x2bc;
    for (unsigned i = 0; i < n; i++)
    {
        AnimLayout* e = (AnimLayout*)((char*)owner->m_poolBegin + off);
        e->m_quat[0] = g_01551678;
        e->m_quat[1] = g_0155167c;
        e->m_quat[2] = g_01551680;
        e->m_quat[3] = g_01551684;
        e->m_v158[0] = 0.0f;
        e->m_v158[1] = 0.0f;
        e->m_v158[2] = 0.0f;
        e->m_v164[0] = 0.0f;
        e->m_v164[1] = 0.0f;
        e->m_v164[2] = 0.0f;
        fn_009f9e20(owner, e);
        e->m_mat[0] = e->m_src[0];
        e->m_mat[1] = e->m_src[1];
        e->m_mat[2] = e->m_src[2];
        e->m_mat[3] = e->m_src[3];
        e->m_mat[4] = e->m_src[4];
        e->m_mat[5] = e->m_src[5];
        e->m_mat[6] = e->m_src[6];
        off += 0x2bc;
    }
}

// @ 0x009fa9a0
void f_009fa9a0(float* out, Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt)
{
	B_s009fa9a0* p = body->link;
	float u = p->jnt[0].rot.x;       // +0x17c
	float v = p->jnt[0].rot.z;       // +0x184
	float w = p->jnt[0].rot.y;       // +0x180
	float t = p->jnt[0].rot.w;       // +0x188
	float a0 = cr->mC8.x;
	float a1 = cr->mC8.y;
	float a2 = cr->mC8.z;
	float a3 = cr->mC8.w;

	float r7 = -((v * w + t * u) * 2.0f);
	float r6 = -(1.0f - (v * v + u * u) * 2.0f);
	float r3 = -((w * u - v * t) * 2.0f);

	float c0 = (((a2 * a0 + -(a1 * a3)) * r7 + (a1 * a0 - -(a2 * a3)) * r6) +
	            (-(a2 * a2) + -(a1 * a1)) * r3) * 2.0f + r3;
	float c1 = (((-(a1 * a1) + -(a0 * a0)) * r7 + (a2 * a1 + -(a0 * a3)) * r6) +
	            (a2 * a0 - -(a1 * a3)) * r3) * 2.0f + r7;
	float c2 = (((a2 * a1 - -(a0 * a3)) * r7 + (-(a2 * a2) + -(a0 * a0)) * r6) +
	            (a1 * a0 + -(a2 * a3)) * r3) * 2.0f + r6;

	float q0 = p->jnt[1].rot.x;      // +0x19c
	float q1 = p->jnt[1].rot.y;      // +0x1a0
	float q2 = p->jnt[1].rot.z;      // +0x1a4
	float q3 = p->jnt[1].rot.w;      // +0x1a8
	float s7 = -((q1 * q0 - q2 * q3) * 2.0f);
	float s6 = -((q2 * q1 + q3 * q0) * 2.0f);
	float s3 = -(1.0f - (q2 * q2 + q0 * q0) * 2.0f);

	float tf = -(g_01550adc / (dt + 1e-8f));
	float y7 = (s6 * c2 - s3 * c1) * tf;
	float y3 = (c1 * s7 - s6 * c0) * tf;
	float y0 = (s3 * c0 - c2 * s7) * tf;

	float e0 = body->jnt[1].rot.x;
	float e1 = body->jnt[1].rot.y;
	float e2 = body->jnt[1].rot.z;
	float e3 = body->jnt[1].rot.w;

	out[0] = (((-(e2 * e2) + -(e1 * e1)) * y7 + (e2 * e0 + -(e1 * e3)) * y0) +
	          (e1 * e0 - -(e2 * e3)) * y3) * 2.0f + y7;
	out[1] = (((-(e2 * e2) + -(e0 * e0)) * y3 + (e2 * e1 - -(e0 * e3)) * y0) +
	          (e1 * e0 + -(e2 * e3)) * y7) * 2.0f + y3;
	out[2] = (((-(e1 * e1) + -(e0 * e0)) * y0 + (e2 * e1 + -(e0 * e3)) * y3) +
	          (e2 * e0 - -(e1 * e3)) * y7) * 2.0f + y0;
}

// @ 0x009fae30
void f_009fae30(float* out, Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt)
{
	B_s009fa9a0* p = body->link;
	float inv = 1.0f / (dt * dt + 1e-8f);
	float dx = p->jnt[1].pos.x - p->jnt[0].pos.x;
	float dy = p->jnt[1].pos.y - p->jnt[0].pos.y;
	float dz = p->jnt[1].pos.z - p->jnt[0].pos.z;

	float ax = cr->mA4.x * g_01550ae4 + (cr->mBC.x * g_01550ae0 + dx * g_01550ae8 * inv);
	float ay = cr->mA4.y * g_01550ae4 + (cr->mBC.y * g_01550ae0 + dy * g_01550ae8 * inv);
	float az = cr->mA4.z * g_01550ae4 + (cr->mBC.z * g_01550ae0 + dz * g_01550ae8 * inv);

	if ((az * az + ay * ay) + ax * ax > 1e-6f)
	{
		Cr_s009fa9a0* ty = body->owner;
		Vec3_s009fa9a0 r;
		F_0099c1a0(&r, &body->jnt[1].rot, &ty->m35c);

		float f = 1.0f / ((ty->m368 * cr->m70) * -1.0f);
		float rx = r.x * f;
		float ry = r.y * f;
		float rz = r.z * f;
		float sc = ty->m374;

		Vec3_s009fa9a0 c;
		c.x = sc * (rz * ay - ry * az);
		c.y = sc * (rx * az - rz * ax);
		c.z = sc * (ry * ax - rx * ay);

		Vec3_s009fa9a0 res;
		F_0099c310(&res, &body->jnt[1].rot, &c);
		out[0] = res.x;
		out[1] = res.y;
		out[2] = res.z;
		return;
	}

	out[0] = 0.0f;
	out[1] = 0.0f;
	out[2] = 0.0f;
}

// @ 0x009fb090
void f_009fb090(float* out, Cr_s009fa9a0* cr, B_s009fa9a0* body)
{
	float v[4];
	F_009b4ba0(v, &body->m148, 0);
	if (v[3] > 1e-6f)
	{
		float f = -(((v[3] * 1.6f + 1.0f) * v[3]) * g_01550aec);
		out[0] = f * v[0];
		out[1] = f * v[1];
		out[2] = f * v[2];
		return;
	}
	out[0] = 0.0f;
	out[1] = 0.0f;
	out[2] = 0.0f;
}

// @ 0x009fb130
void f_009fb130(B_s009fa9a0* body, float dt)
{
	body->m158.y = body->m158.y + body->m164.y * dt;
	body->m158.z = body->m158.z + body->m164.z * dt;
	body->m158.x = body->m158.x + body->m164.x * dt;

	float n2 = (body->m158.x * body->m158.x + body->m158.y * body->m158.y) +
	           body->m158.z * body->m158.z;
	if (g_0166c980 < n2)
	{
		float f = g_01551648 / sqrtf(n2);
		body->m158.x = f * body->m158.x;
		body->m158.y = f * body->m158.y;
		body->m158.z = f * body->m158.z;
	}

	float h = dt * 0.5f;
	float wx = body->m158.x * h;
	float wy = body->m158.y * h;
	float wz = body->m158.z * h;
	float zero = h * 0.0f;

	float qx = body->m148.x, qy = body->m148.y, qz = body->m148.z, qw = body->m148.w;
	float dx = ((qx * zero + qw * wx) - qy * wz) + qz * wy;
	float dy = ((qy * zero + qx * wz) + qw * wy) - qz * wx;
	float dz = ((qw * wz - qx * wy) + qz * zero) + qy * wx;
	float dw = ((qw * zero - qx * wx) - qy * wy) - qz * wz;
	body->m148.x = dx + body->m148.x;
	body->m148.y = dy + body->m148.y;
	body->m148.z = dz + body->m148.z;
	body->m148.w = dw + body->m148.w;

	float len = sqrtf(((body->m148.x * body->m148.x + body->m148.y * body->m148.y) +
	                   body->m148.z * body->m148.z) + body->m148.w * body->m148.w);
	if (len != 0.0f)
	{
		float inv = 1.0f / len;
		body->m148.x = body->m148.x * inv;
		body->m148.y = body->m148.y * inv;
		body->m148.z = body->m148.z * inv;
		body->m148.w = body->m148.w * inv;
	}

	if (g_01550afc_s009f_a9a0 != 0)
		F_009fa170(body);

	if ((1.0f - fabsf(body->m148.w) < 1e-6f) &&
	    ((body->m158.x * body->m158.x + body->m158.y * body->m158.y) +
	     body->m158.z * body->m158.z < 1e-6f))
	{
		body->m148.x = g_01551678_s009f_a9a0;
		body->m148.y = g_0155167c_s009f_a9a0;
		body->m148.z = g_01551680_s009f_a9a0;
		body->m148.w = g_01551684_s009f_a9a0;
		body->m158.x = 0.0f;
		body->m158.y = 0.0f;
		body->m158.z = 0.0f;
	}
}

// @ 0x009fb510
void f_009fb510(Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt)
{
	if (body->owner->m370 != 0 && body->link != 0)
	{
		if (g_01550ad8 != 0)
		{
			Vec3_s009fa9a0 t;
			f_009fa9a0(&t.x, cr, body, dt);
			body->m164.x = body->m164.x + t.x;
			body->m164.y = body->m164.y + t.y;
			body->m164.z = body->m164.z + t.z;
		}

		Vec3_s009fa9a0 t2;
		f_009fae30(&t2.x, cr, body, dt);
		body->m164.x = body->m164.x + t2.x;
		body->m164.y = body->m164.y + t2.y;
		body->m164.z = body->m164.z + t2.z;

		Vec3_s009fa9a0 t3;
		f_009fb090(&t3.x, cr, body);
		body->m164.x = body->m164.x + t3.x;
		body->m164.y = body->m164.y + t3.y;
		body->m164.z = body->m164.z + t3.z;

		float damp = -g_01550af0;
		body->m164.x = body->m164.x + body->m158.x * damp;
		body->m164.y = body->m164.y + body->m158.y * damp;
		body->m164.z = body->m164.z + body->m158.z * damp;

		f_009fb130(body, dt);
		F_009f9e20(cr, body);
		return;
	}

	float qw = body->m148.w;
	if (qw < 0.0f)
		qw = qw - 1.0f;
	else
		qw = qw + 1.0f;
	body->m148.w = qw;

	float len = sqrtf(((body->m148.x * body->m148.x + body->m148.y * body->m148.y) +
	                   body->m148.z * body->m148.z) + body->m148.w * body->m148.w);
	if (len != 0.0f)
	{
		float inv = 1.0f / len;
		body->m148.x = body->m148.x * inv;
		body->m148.y = body->m148.y * inv;
		body->m148.z = body->m148.z * inv;
		body->m148.w = body->m148.w * inv;
	}
	body->m158.x = 0.0f;
	body->m158.y = 0.0f;
	body->m158.z = 0.0f;

	F_009f9e20(cr, body);
}

// @ 0x009fb7c0
void f_009fb7c0(Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt)
{
	f_009fb510(cr, body, dt);
	Cr_s009fa9a0* ty = body->owner;
	int m = ty->m204;
	if ((unsigned)ty->m20c <= 0u)
		return;
	unsigned n = ty->m20c;
	do
	{
		f_009fb510(cr, (B_s009fa9a0*)((char*)cr->mBodiesBegin + m * 0x2bc), dt);
		m += 1;
	} while (--n);
}

// @ 0x009fb830
void f_009fb830(Cr_s009fa9a0* cr, float dt)
{
	int n = (int)((char*)cr->mBodiesEnd - (char*)cr->mBodiesBegin) / 700;
	if (n == 0)
		return;
	int off = 0;
	for (int i = n; i != 0; --i)
	{
		B_s009fa9a0* el = (B_s009fa9a0*)((char*)cr->mBodiesBegin + off);
		int m = el->m144;
		if (m > 0 && el->link != 0 && el->link->m144 == 0)
		{
			if (m == 1)
			{
				F_009f9dc0(cr, el->link);
				if (cr->m1ac <= 1)
					F_009fa870(cr, el);
				else
					F_009fa770(cr, el);
				el->m144 = el->m144 + 1;
			}
			f_009fb7c0(cr, el, dt);
		}
		off += 700;
	}
}

// @ 0x009fb8e0
void ResetBodyRenderState(int inst)
{
    float* base = (float*)*(void**)(inst + 0x2e4);
    int count = (int)(((char*)*(void**)(inst + 0x2e8) - (char*)base) / 700);
    for (int i = 0; i < count; ++i) {
        float* e = base + i * 175;
        float* z = e + (0x164 / 4);
        float* d = e + (0x170 / 4);
        float* s = e + (0x190 / 4);
        z[0] = 0.0f;
        z[1] = 0.0f;
        z[2] = 0.0f;
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
        d[4] = s[4];
        d[5] = s[5];
        d[6] = s[6];
    }
}

// @ 0x009fbb80
void AdvanceTimer(void* self, float dt)
{
    if (!self)
        return;
    if (*(uint8*)((char*)self + 0x1794) == 0)
        return;

    float* pf = (float*)((char*)self + 0x1798);
    *pf = *pf + dt;
    *pf = minf(*pf, g_166c978);
    float v = *pf;

    int n;
    float step;
    if (g_166c974 > v) {
        n = 1;
        step = v;
        *pf = 0.0f;
    } else {
        step = g_166c974;
        *pf = fmod(v, step);
        n = (int)(v / (step + g_13ec4b8));
    }
    for (int i = 0; i < n; ++i) {
        FUN_009fb830(self, step);
        ResetBodyRenderState((int)self);
    }
}

// @ 0x009fbc50
void AudioSetListener3(int a1, float b, float c, float d)
{
    void* s = EA_Audio_GetSystemAT();
    if (!s)
        return;
    ((vt_v_i)VT(s, 0x38))(s, 0x3475373);
    ((vt_v_ii)VT(s, 0x40))(s, 0x3475385, a1);
    ((vt_v_if)VT(s, 0x3c))(s, 0x3475391, b);
    ((vt_v_if)VT(s, 0x3c))(s, 0x3475395, c);
    ((vt_v_if)VT(s, 0x3c))(s, 0x3475398, d);
    ((vt_v0)VT(s, 0x58))(s);
}

// @ 0x009fbcd0
void AudioSetEvent9(void* p, int v)
{
    if (p)
        ((vt_v_iii)VT(p, 0x40))(p, 9, v, 1);
}

// @ 0x009fbcf0
void AudioSetEvent10(void* p, int v)
{
    if (p)
        ((vt_v_iii)VT(p, 0x44))(p, 10, (int)&v, 1);
}

// @ 0x009fbd10
void AudioSetFlag(void* p, char v)
{
    if (p)
        ((vt_v_i)VT(p, 0xc))(p, v == 0);
}

// @ 0x009fbd30
void AudioSetEvent5(void* p, int v)
{
    if (p)
        ((vt_v_iii)VT(p, 0x40))(p, 5, v, 1);
}

// @ 0x009fbd50
void AudioSetEvent1(void* p, int v)
{
    if (p)
        ((vt_v_iii)VT(p, 0x44))(p, 1, (int)&v, 1);
}

// @ 0x009fbd70
void AudioSetListener2(int p2, char v)
{
    void* s = EA_Audio_GetSystemAT();
    if (!s)
        return;
    ((vt_v_i)VT(s, 0x38))(s, 0x347536b);
    ((vt_v_ii)VT(s, 0x40))(s, 0x3475385, p2);
    ((vt_v_ii)VT(s, 0x40))(s, 0x34753a0, v == 0);
    ((vt_v0)VT(s, 0x58))(s);
}

// @ 0x009fbdd0
char AudioQueryA(int x)
{
    void* s = EA_Audio_GetSystemAT();
    if (s)
        return ((vt_i_i)VT(s, 0x28))(s, x);
    return 0;
}

// @ 0x009fbe00
void AudioQueryB(int x)
{
    void* s = EA_Audio_GetSystemAT();
    if (s)
        ((vt_v_i)VT(s, 0x2c))(s, x);
}

// @ 0x009fbe20
float AudioQueryC(int x)
{
    float r;
    if (SP_AudioSystem()) {
        void* s = SP_AudioSystem();
        r = ((vt_f_i)VT(s, 0x44))(s, x);
    } else r = 0.0f;
    return r;
}

// @ 0x009fbe50
void AudioSetListener3v(int a1, float* v)
{
    AudioSetListener3(a1, v[0], v[1], v[2]);
}

// @ 0x009fbe80
void EffectsEmitEvent(void* self, int group, void* mat)
{
    if (!self)
        return;

    M9 tmp;
    EventDesc desc;
    desc.flags = 0;
    desc.count = 0;
    desc.f04 = g_166ca38;
    desc.f08 = g_166ca3c;
    desc.f0c = g_166ca40;
    desc.f10 = g_1485720;
    ((FUN_0041cb40*)desc.m)->ctor(&g_166cb6c);

    ((vt_v_p)VT(self, 0x20))(self, &desc);

    if (group) {
        desc.flags |= 4;
        desc.count += 1;
        *(V3*)&desc.f04 = *(V3*)group;
    }
    if (mat) {
        float* s = (float*)mat;
        tmp.m[0] = s[0]; tmp.m[3] = s[1]; tmp.m[6] = s[2];
        tmp.m[1] = s[3]; tmp.m[4] = s[4]; tmp.m[7] = s[5];
        tmp.m[2] = s[6]; tmp.m[5] = s[7]; tmp.m[8] = s[8];
        *(M9*)desc.m = tmp;
        desc.flags |= 2;
        desc.count += 1;
    }
    ((vt_v_p)VT(self, 0x18))(self, &desc);
}

// @ 0x009fbfc0
bool EffectsSpawn(void* a, int b, void* c, int d, int e, void** out)
{
    void* local = 0;
    if (!out)
        out = &local;
    if (!SP_EffectsManager())
        goto fail;
    {
        void* mgr = a;
        if (!mgr) {
            void* sys = SP_EffectsManager();
            mgr = ((vt_p0)VT(sys, 0x5c))(sys);
        }
        if (b)
            return false;
        if (((vt_c_pii)VT(mgr, 8))(mgr, c, 0, out)) {
            EffectsEmitEvent(*out, d, (void*)e);
            ((vt_v_i)VT(*out, 8))(*out, 0);
            if (local)
                ((vt_v0)VT(local, 4))(local);
            return true;
        }
    }
fail:
    *out = 0;
    return false;
}

// @ 0x009fc050
bool EffectsSpawnThunk(int a, int b, int c, int d, int e)
{
    return EffectsSpawn((void*)a, 0, (void*)b, c, d, (void**)e);
}

// @ 0x009fc0f0
int FeedbackLookupName(const char* name)
{
    if (!name)
        return 0;
    uint32 out;
    uint32 h = EA_Hash_FNV1_String8(name, 0x811c9dc5, 1);
    RBFind* tree = (RBFind*)g_166c074;
    tree->find(&out, &h);
    if ((void*)out != (char*)tree + 4)
        return *(int*)(out + 0x14);
    return 0;
}

// @ 0x009fc140
void BehaviorTableExpand(int self)
{
    char* p = (char*)self;
    int i = 0;
    while (*(int*)(p + 8 + i * 4) != 0) {
        ++i;
        if (i >= 0x20)
            break;
    }
    int j = 0;
    char* flags = p + 0x88;
    for (; j < 0x20; ++j) {
        uint32 key = *(uint32*)(p + 8 + j * 4);
        if (key == 0)
            break;
        char* tree = (char*)g_166c080;
        char* head = tree + 4;
        char* node = *(char**)(tree + 0xc);
        char* parent = head;
        while (node) {
            if (*(uint32*)(node + 0x10) < key) {
                node = *(char**)node;
            } else {
                parent = node;
                node = *(char**)(node + 4);
            }
        }
        if (parent == head || key < *(uint32*)(parent + 0x10))
            parent = head;
        if (parent != head) {
            uint32 cnt = (uint32)((*(char**)(parent + 0x18) - *(char**)(parent + 0x14)) >> 2);
            char* vb = *(char**)(parent + 0x14);
            for (uint32 k = 0; k < cnt; ++k) {
                *(uint32*)(p + 8 + i * 4) = *(uint32*)(vb + k * 4);
                *(char*)(p + 0x88 + i) = flags[j];
                ++i;
            }
        }
    }
    ((FUN_009b3010*)p)->reset();
}

// @ 0x009fc220
void BehaviorTableDedup(int self)
{
    char* p = (char*)self;
    BehaviorTableExpand(self);
    int* slots = (int*)(p + 8);
    char* flags = p + 0x88;
    for (int n = 0; n < 0x20; ++n) {
        int v = slots[n];
        if (v == 0)
            continue;
        for (int k = n + 1; k < 0x20; ++k) {
            if (slots[k] != 0 && slots[k] == v) {
                slots[k] = 0;
                if ((uint8)flags[n] < (uint8)flags[k])
                    flags[n] = flags[k];
            }
        }
    }
    // compact empty slots
    int hi = 0x1f;
    for (int lo = 0; lo < hi; ++lo) {
        if (slots[lo] == 0 && lo < hi) {
            while (hi > lo && slots[hi] == 0)
                --hi;
            if (hi > lo) {
                slots[lo] = slots[hi];
                flags[lo] = flags[hi];
                slots[hi] = 0;
                --hi;
            }
        }
    }
    ((FUN_009b3010*)p)->reset();
}

// @ 0x009fc310
int BehaviorLookup(uint32* p)
{
    uint32 key = p[0] & 0x100003;
    uint32 sel = p[0] & 0x801c00;
    if (key == 0) {
        key = p[1];
    } else if (key == 1) {
        key = 0x746f6f72;
    } else {
        return (int)(size_t)g_166c07c;
    }
    if (sel == 0x1800 || sel == 0x1c00 || sel == 0x800400)
        key = p[2];
    if (!key)
        return (int)(size_t)g_166c07c;
    uint32 out;
    RBFind* tree = (RBFind*)g_166c078;
    tree->find(&out, &key);
    if ((void*)out == (char*)tree + 4)
        return (int)(size_t)g_166c07c;
    return *(int*)(out + 0x14);
}

// @ 0x009fe560
uint32* MapIdxC::insert(const uint32& key)
{
    char* root = (char*)this->root;
    char* result = (char*)this + 4;
    char* anchor = (char*)this + 4;
    while (root) {
        if (*(uint32*)(root + 0x10) < key)
            root = *(char**)root;
        else {
            result = root;
            root = *(char**)(root + 4);
        }
    }
    if (result != anchor && key >= *(uint32*)(result + 0x10))
        return (uint32*)(result + 0x14);
    SimpleVec32 tmp;
    tmp.begin = 0;
    tmp.end = 0;
    tmp.cap = 0;
    ((VecImpl*)&tmp)->DoAllocate(0, (char*)this + 0x10);
    tmp.end = (uint32*)DoInsertValue(tmp.begin, 0, 0);
    void* out = 0;
    insertImpl(&out, result, 0, &tmp, 0);
    if (tmp.begin != 0 && *(int*)((char*)tmp.begin - 4) != 0)
        ElemFree(tmp.begin);
    return (uint32*)((char*)out + 0x14);
}

// @ 0x009fee90
void AnimGoal::Init()
{
    field_a8 = 0.0;
    field_70 = 0.0f;
    field_74 = -0.2f;
    field_d4 = 0;
    field_8c = 1.0f;
    field_a0 = 1.0f;
    field_78 = 0.2f;
    field_cc = -1.0f;
    field_d0 = 1.0f;
    field_bc = 0;
    field_d8 = 0;
    field_7c = 0;
    field_88 = 0.2f;
    field_80 = 1;
    field_84 = 0;
}

// @ 0x009fef20
void AnimGoal::CopyFiltersFrom(AnimGoal* o)
{
    field_88 = o->field_88;
    field_78 = o->field_78;
    field_c4 = o->field_c4;
}

// @ 0x009ff880
#pragma optimize("gt", off)
void __cdecl UpdateGoalWeight(int src, AnimGoal* g)
{
    int state = g->field_c0;
    if (state == 0)
        return;
    if (state == 1) {
        float t = (g->field_88 > 1e-05f) ? g->field_c4 / g->field_88 : 0.0f;
        float lo = 0.0f, hi = 1.0f;
        const float& c = clampMin(clampMax(lo, t), hi);
        if (c < 0.99999f)
            g->field_78 = *(float*)(src + 0x88) / (1.0f - c);
        else
            g->field_78 = 0.0f;
    } else if (state == 3) {
        float t = (g->field_78 > 1e-05f) ? g->field_c4 / g->field_78 : 0.0f;
        float hi = 1.0f, lo = 0.0f;
        const float& c = clampMin(clampMax(lo, t), hi);
        if (c > 1e-05f)
            g->field_78 = *(float*)(src + 0x88) / c;
        else
            g->field_78 = 0.0f;
    } else {
        g->field_78 = *(float*)(src + 0x88);
    }
    g->field_c4 = *(float*)(src + 0x88);
    if (g->field_78 != 0.0f)
        g->field_c0 = 3;
    else
        g->field_c0 = 0;
}
#pragma optimize("", on)

// @ 0x009ffb50
AnimGoal_s009f_fa00* AnimGoal_s009f_fa00::operator=(AnimGoal_s009f_fa00* o)
{
    GoalObj* n0 = o->field_00;
    GoalObj* old0 = field_00;
    if (n0 != old0) {
        if (n0)
            n0->AddRef();
        field_00 = n0;
        if (old0)
            old0->Release();
    }
    GoalObj2* n1 = o->field_04;
    GoalObj2* old1 = field_04;
    if (n1 != old1) {
        if (n1)
            n1->AddRef();
        field_04 = n1;
        if (old1)
            old1->Release();
    }
    mChildren[0] = o->mChildren[0];
    mChildren[1] = o->mChildren[1];
    mChildren[2] = o->mChildren[2];
    mChildren[3] = o->mChildren[3];
    mChildren[4] = o->mChildren[4];
    mChildren[5] = o->mChildren[5];
    mChildren[6] = o->mChildren[6];
    mChildren[7] = o->mChildren[7];
    mChildren[8] = o->mChildren[8];
    mChildren[9] = o->mChildren[9];
    mChildren[10] = o->mChildren[10];
    mChildren[11] = o->mChildren[11];
    mChildren[12] = o->mChildren[12];
    mChildren[13] = o->mChildren[13];
    mChildren[14] = o->mChildren[14];
    mChildren[15] = o->mChildren[15];
    mChildren[16] = o->mChildren[16];
    mChildren[17] = o->mChildren[17];
    mChildren[18] = o->mChildren[18];
    mChildren[19] = o->mChildren[19];
    mChildren[20] = o->mChildren[20];
    mChildren[21] = o->mChildren[21];
    mChildren[22] = o->mChildren[22];
    mChildren[23] = o->mChildren[23];
    mChildCount = o->mChildCount;
    field_6c = o->field_6c;
    field_70 = o->field_70;
    field_74 = o->field_74;
    field_78 = o->field_78;
    field_7c = o->field_7c;
    field_80 = o->field_80;
    field_84 = o->field_84;
    field_88 = o->field_88;
    field_8c = o->field_8c;
    field_90 = o->field_90;
    field_94 = o->field_94;
    field_98 = o->field_98;
    field_9c = o->field_9c;
    field_9d = o->field_9d;
    field_a0 = o->field_a0;
    field_a8 = o->field_a8;
    field_b0 = o->field_b0;
    field_b4 = o->field_b4;
    field_b8 = o->field_b8;
    field_bc = o->field_bc;
    field_c0 = o->field_c0;
    field_c4 = o->field_c4;
    field_c8 = o->field_c8;
    field_cc = o->field_cc;
    field_d0 = o->field_d0;
    field_d4 = o->field_d4;
    field_d8 = o->field_d8;
    field_dc = o->field_dc;
    field_e0 = o->field_e0;
    field_e4 = o->field_e4;
    field_e8 = o->field_e8;
    field_ec = o->field_ec;
    return this;
}
