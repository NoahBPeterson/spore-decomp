// slice s00b4d220 -- Simulator physics / Havok gameplay glue:
//   a GB1 physics-object base (ctor / small ctors / copy helpers), a shape-phantom subclass, a
//   Havok rigid-body factory, and a family of capsule/collision-position helpers that read the
//   object's position and orientation through the virtual interface (vt+0x2c/0x30/0x68).
//
// This range is ordinary game/physics code, not RenderWare-4 core, so byte-exactness is pursued.
// Objects are raw byte spans accessed at fixed offsets; interface calls go through the vtable slots
// the original uses (offsets noted inline).
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed   int   i32;

static inline u32  ld32(char* b, u32 off) { return *(u32*)(b + off); }
static inline void st32(char* b, u32 off, u32 v) { *(u32*)(b + off) = v; }
static inline u8   ld8 (char* b, u32 off) { return *(u8*)(b + off); }
static inline void st8 (char* b, u32 off, u8 v) { *(u8*)(b + off) = v; }
static inline float ldf(char* b, u32 off) { return *(float*)(b + off); }
static inline void stf (char* b, u32 off, float v) { *(float*)(b + off) = v; }

// callees reached with `this` in ecx: model them as members of opaque structs (the compiler emits a
// __thiscall call: `this` in ecx, remaining args pushed), matching the original exactly.
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
struct StyleOps { void dummy(); };

// Havok rigid-body factory callees, reached with `this` in ecx (declaration-only placeholders:
// chk masks the relocated call target, so the missing definition is fine).
struct RigidBody {
    void* ctor(const void* cinfo);              // 0x010878b0 ??
    void  addEntityListener(const void* l);     // 0x01088c20
};

// vtable slots whose target is only known at run time.  Model a slot as a pointer-to-member of
// HkObj so MSVC emits a __thiscall call (`this` in ecx, args pushed) exactly like the original.
typedef float* (HkObj::*PMemGetVec)();                        // vt+0x2c / vt+0x68 return a vec3
typedef u32    (HkObj::*PMemTagInt)(u32 tag);                 // vt+0xb8 tag query
typedef float* (HkObj::*PMemGetMatrix)();                     // vt+0x30 returns a transform
typedef void   (HkObj::*PMemSetVec)(const float* v);          // vt+0x38 set position
typedef void*  (HkObj::*PMemFindRes)(u32 tag, int id);        // vtb+0x48 resource find
typedef u32    (HkObj::*PMemGetType)();                       // vtb+0x18 resource type
typedef void   (HkObj::*PMemReleaseRes)(int a, char* obj, int b); // vtb+0x44 release
typedef void*  (HkObj::*PMemAlloc)(int size, u32 tag);        // hkMemory vt+0x10 alloc

static inline PMemGetVec    slotGetVec(u32 a)    { PMemGetVec p;    *(u32*)&p = a; return p; }
static inline PMemTagInt    slotTagInt(u32 a)    { PMemTagInt p;    *(u32*)&p = a; return p; }
static inline PMemGetMatrix slotGetMatrix(u32 a) { PMemGetMatrix p; *(u32*)&p = a; return p; }
static inline PMemSetVec    slotSetVec(u32 a)    { PMemSetVec p;    *(u32*)&p = a; return p; }
static inline PMemFindRes   slotFindRes(u32 a)   { PMemFindRes p;   *(u32*)&p = a; return p; }
static inline PMemGetType   slotGetType(u32 a)   { PMemGetType p;   *(u32*)&p = a; return p; }
static inline PMemReleaseRes slotRelease(u32 a)  { PMemReleaseRes p;*(u32*)&p = a; return p; }
static inline PMemAlloc     slotAlloc(u32 a)     { PMemAlloc p;     *(u32*)&p = a; return p; }

void* __cdecl ResourceMan_GetManager(void);                 // 0x0067dcd0
u8    __cdecl Obj_59ab70(const float* v);                   // 0x0059ab70 (point-in-region test)
float* __cdecl Obj_59aed0(float* out, const float* v, const char* mtx); // 0x0059aed0 (transform)
void* __cdecl Obj_bbb500(u32 a, u32 b);                     // 0x00bbbe10 thunk -> 0x00bbb500
void* __cdecl EAAllocate(u32 size, const char* cat, int a, int b, int c, int d); // 0x00f473a0
void  __cdecl Obj_b5a410(void);                             // 0x00b5a410
void  __cdecl Obj_b41020(void);                             // 0x00b41020

extern char* g_hkMemory_s_instance;      // 0x016e4178
extern char* g_mgr_listeners;            // 0x01569cdc
extern float g_halfF;                    // 0x01471064  (0.5f)
extern float g_oneF;                     // 0x01485720  (1.0f)
extern float g_twoF;                     // 0x01470f1c  (2.0f)
extern float g_negF;                     // 0x013eb8b0  (sign bit)
extern float g_4f;                       // 0x013eecd8  (4.0f / box size const)
extern float g_scale3f;                  // 0x013f6bf8
extern float g_capsuleF;                 // 0x013eb95c
extern float g_40f;                      // 0x01569b18
extern float g_densBase;                 // 0x014853e0
extern double g_powBase;                 // 0x01432200
extern char  g_useSabotage;              // 0x0167ecd8
extern char* g_physObj;                  // 0x0167ecd0
extern char* g_physPool;                 // 0x0167eb70
extern char* g_someGlobal;               // 0x0167eb88

// ==================================================================================================
// 0x00b4da40  capsule collision solve (returns 1 when the impulse is non-zero)
// ==================================================================================================
// @ 0x00b4da40
u32 __cdecl FUN_00b4da40(float* p)
{
    float d1 = p[0x11] - p[0x15];
    float d2 = p[0x12] - p[0x16];
    float d3 = p[0x10] - p[0x14];
    float d4 = p[0x13] - p[0x17];

    float inv = 0.0f;
    float dot = d1 * d1 + d2 * d2 + d3 * d3;
    if (dot != 0.0f) inv = 1.0f / (float)sqrtf(dot);

    float e1 = d1 * inv;
    float e2 = d2 * inv;
    float e3 = d3 * inv;
    float e4 = d4 * inv;

    float a1 = p[8]  - p[0xc];
    float a2 = p[9]  - p[0xd];
    float a3 = p[10] - p[0xe];

    p[0x28] = (float)sqrtf(a1 * a1 + a2 * a2 + a3 * a3);

    float k = 1.0f / p[0x18] + 1.0f / p[0x19];
    float s = -(p[0x1a] + 1.0f);
    float num = (a3 * s) * e3 + (a2 * s) * e2 + (a1 * s) * e1;
    float den = (p[2] * (p[2] * k) + p[1] * (p[1] * k)) + p[0] * (p[0] * k);
    p[0x1c] = num / den;

    float j = p[0x1c] * (1.0f / p[0x18]);
    p[0x20] = j * e1;
    p[0x21] = j * e2;
    p[0x22] = j * e3;
    p[0x23] = j * e4;

    float j2 = -(p[0x1c] * (1.0f / p[0x19]));
    p[0x24] = j2 * e1;
    p[0x25] = j2 * e2;
    p[0x26] = j2 * e3;
    p[0x27] = j2 * e4;

    if (p[0x22] * e3 + p[0x21] * e2 + p[0x20] * e1 < 0.0f) {
        p[0x23] = 0.0f; p[0x22] = 0.0f; p[0x21] = 0.0f; p[0x20] = 0.0f;
    }
    if (0.0f < p[0x26] * e3 + p[0x25] * e2 + p[0x24] * e1) {
        p[0x27] = 0.0f; p[0x26] = 0.0f; p[0x25] = 0.0f; p[0x24] = 0.0f;
    }
    return p[0x1c] != 0.0f ? 1u : 0u;
}

// ==================================================================================================
// 0x00b4d3f0  copy an 0x50-byte block (skipping the two holes at +8/+0xc)
// ==================================================================================================
struct Blk50 { float f[0x14]; void* copyFrom(const void* src); };   // 0x50 bytes, holes at +8,+0xc
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

// ==================================================================================================
// 0x00b4d470  repack a source object (sparse offsets) into a dense 0x7a-byte record
// ==================================================================================================
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

// ==================================================================================================
// 0x00b4d540  clear/init an 0x74-byte record (scalar 1.0 at +0x10, tag 2 at +0x14, rest zero)
// ==================================================================================================
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

// ==================================================================================================
// 0x00b4d5d0  7-arg init of a 0x74-byte record (vec3 header + scalars, rest zero)
// ==================================================================================================
// @ 0x00b4d5d0
void* __fastcall FUN_00b4d5d0(char* self, char* a, u32 b, float c, u32 d, u32 e, u32 f)
{
    st32(self, 0x0, ld32(a, 0));
    st32(self, 0x4, ld32(a, 4));
    st32(self, 0x8, ld32(a, 8));
    st32(self, 0xc, b);
    stf(self, 0x10, c);
    st32(self, 0x14, d);
    st32(self, 0x18, f);
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
    st32(self, 0x70, e);
    return self;
}

// ==================================================================================================
// 0x00b4d670  scale a plane/direction by -(param+1); returns scale*param4
// ==================================================================================================
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

// ==================================================================================================
// 0x00b4d720  find resource tag 0x448ae7e2, and if its type is 0x532db75, release it
// ==================================================================================================
// @ 0x00b4d720
void __cdecl FUN_00b4d720(void)
{
    typedef void* (__thiscall *FindFn)(void* self, u32 tag, int id);
    typedef u32   (__thiscall *TypeFn)(void* self);
    typedef void  (__thiscall *ReleaseFn)(void* self, int a, void* obj, int b);
    void* mgr = ResourceMan_GetManager();
    void* obj = ((FindFn)(*(void***)mgr)[0x48 / 4])(mgr, 0x448ae7e2u, -1);
    if (obj) {
        u32 type = ((TypeFn)(*(void***)obj)[0x18 / 4])(obj);
        if (type == 0x532db75u) {
            void* mgr2 = ResourceMan_GetManager();
            ((ReleaseFn)(*(void***)mgr2)[0x44 / 4])(mgr2, 0, obj, 0);
        }
    }
}

// ==================================================================================================
// 0x00b4d770  walk a linked chain at +0x70, bumping a 16-bit counter on each tagged node
// ==================================================================================================
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

// ==================================================================================================
// 0x00b4d7a0  add three Havok world properties from (radius, ?, solid flag)
// ==================================================================================================
// @ 0x00b4d7a0
void __fastcall FUN_00b4d7a0(char* self, int, float radius, float tag, u8 solid)
{
    ((HkObj*)self)->hkAddProperty(2, *(u32*)&radius, 0);
    float r = radius * g_capsuleF * g_40f / g_densBase;
    ((HkObj*)self)->hkAddProperty(3, *(u32*)&r, 0);
    ((HkObj*)self)->hkAddProperty(8, solid ? 1u : 0u, solid ? 0u : 0u);
}

// ==================================================================================================
// 0x00b4d820  hkSimpleShapePhantom subclass ctor (base ctor + vtable + flag clear)
// ==================================================================================================
// @ 0x00b4d820
void* __fastcall FUN_00b4d820(char* self, int, const void* shape, const void* xform, u32 a)
{
    ((HkObj*)self)->hkPhantomCtor(shape, xform, a);
    st32(self, 0, 0x1461330u);
    st8(self, 0x130, 0);
    return self;
}

// ==================================================================================================
// 0x00b4d850  overlapping-collidable filter -> forward to hkSimpleShapePhantom::addOverlapping
// ==================================================================================================
// @ 0x00b4d850
void __fastcall FUN_00b4d850(char* self, int, char* c)
{
    if (ld8(self, 0x130) != 0) return;
    if (ld8(c, 0x18) == 2 && ld8(c + ld32(c, 0x10), 0x130) != 0) return;
    ((HkObj*)self)->hkAddOverlapping(c);
}

// ==================================================================================================
// 0x00b4d880  SP::Havok::CreateRigidBody -- allocate an hkRigidBody and register the listener
// ==================================================================================================
// @ 0x00b4d880
void* __cdecl CreateRigidBody(const void* cinfo)
{
    typedef void* (__thiscall *AllocFn)(void* self, int size, u32 tag);
    void* mem = g_hkMemory_s_instance;
    void* p = ((AllocFn)(*(void***)mem)[0x10 / 4])(mem, 0xd0, 0x2a);
    *(u16*)((char*)p + 4) = 0xd0;
    void* body = ((RigidBody*)p)->ctor(cinfo);
    ((RigidBody*)body)->addEntityListener(&g_mgr_listeners);
    return body;
}

// ==================================================================================================
// 0x00b4d8c0  clear the global physics-object pointer
// ==================================================================================================
// @ 0x00b4d8c0
void __cdecl FUN_00b4d8c0(void)
{
    if (g_physObj != 0) g_physObj = 0;
}

// ==================================================================================================
// 0x00b4d8e0  choose an LOD/id from a tag query and push it to the object at +8
// ==================================================================================================
// @ 0x00b4d8e0
void __cdecl FUN_00b4d8e0(char* self, char* obj)
{
    typedef u32 (__thiscall *TagFn)(void* self, u32 tag);
    TagFn fn = (TagFn)(*(void***)self)[0xb8 / 4];
    i32 v;
    if (ld8(self, 0x50) & 0x80)
        v = (i32)((-(u32)(fn(self, 0x116dd1bu) != 0)) & 0xfffffffeu) + 5;
    else
        v = (i32)((-(u32)(fn(self, 0x116dd1bu) != 0)) & 0xfffffffeu) + 4;
    if (ld32(obj, 8) != 0) {
        st32(obj, 0x38, (u32)v);
        void* t = (void*)ld32(obj, 8);
        ((HkObj*)t)->hk104fa0((int)(size_t)obj, 0, 1);
    }
}

// ==================================================================================================
// 0x00b4d930  set the two capsule constants at +0x14e8/+0x14ec
// ==================================================================================================
// @ 0x00b4d930
void __fastcall FUN_00b4d930(char* self)
{
    stf(self, 0x14e8, g_useSabotage ? g_scale3f : 0.0f);
    stf(self, 0x14ec, g_oneF);
}

// ==================================================================================================
// 0x00b4d980  copy a 0x84-byte record (vec3 header, scalars, an 0x50 sub-block, trailing word)
// ==================================================================================================
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

// ==================================================================================================
// 0x00b4dd70  physics-object position/orientation sync on a game-data change
// ==================================================================================================
// @ 0x00b4dd70
void __cdecl FUN_00b4dd70(char* obj, char* gamedata)
{
    typedef void (__thiscall *Fn)(char*);
    if (!gamedata) return;

    u32 haveObj = obj ? (((HkObj*)obj)->*(PMemTagInt)slotTagInt(*(u32*)obj + 0xb8))(0x116dd1bu) : 0;

    if (ld8(obj, 0xa4) == 1) {
        float* m = (((HkObj*)obj)->*(PMemGetVec)slotGetVec(*(u32*)obj + 0x2c))();
        float v[4];
        v[0] = m[0]; v[1] = m[1]; v[2] = m[2]; v[3] = 0.0f;
        ((HkObj*)gamedata)->aef7e0(v);
    } else {
        float* p = ((HkObj*)gamedata)->politicalID();
        float v[3];
        v[0] = p[0]; v[1] = p[1]; v[2] = p[2];
        if (Obj_59ab70(v)) {
            (((HkObj*)obj)->*(PMemSetVec)slotSetVec(*(u32*)obj + 0x38))(v);
        }
        st8(obj, 0x77, *(i32*)(gamedata + 0xcc) > 0);
    }

    u32 tag = (((HkObj*)obj)->*(PMemTagInt)slotTagInt(*(u32*)obj + 0xb8))(0xce9f6639u);
    st8(obj, 0xa4, 0);
    if (tag) {
        float v = ldf(gamedata, 0x140);
        const float* src = (const float*)(gamedata + 0x100);
        ((HkObj*)(size_t)tag)->c0dd70(src, v, src);
    }

    if (haveObj) {
        float* p = ((HkObj*)obj)->aef400();
        float v[3];
        v[0] = p[0]; v[1] = p[1]; v[2] = p[2];
        const float* arg = v;
        if (!Obj_59ab70(v)) arg = (const float*)0x167ecf4;
        ((HkObj*)(size_t)haveObj)->c41d60(arg);
    }
}

// ==================================================================================================
// 0x00b4dee0  compute a capsule/sphere contact point from the object's position and bounds
// ==================================================================================================
// @ 0x00b4dee0
void __cdecl FUN_00b4dee0(char* self, u8 flag, float* out)
{
    float x, y, z;
    if (flag) {
        float* p = (((HkObj*)self)->*(PMemGetVec)slotGetVec(*(u32*)self + 0x2c))();
        x = p[0]; y = p[1]; z = p[2];
    } else {
        float* b = (((HkObj*)self)->*(PMemGetVec)slotGetVec(*(u32*)self + 0x68))();
        x = (b[0] + b[3]) * g_halfF;
        y = (b[4] + b[1]) * g_halfF;
        z = (b[5] + b[2]) * g_halfF;
        float mtx = 0.0f;
        char* m = (char*)(((HkObj*)self)->*(PMemGetMatrix)slotGetMatrix(*(u32*)self + 0x30))();
        float tmp[3];
        tmp[0] = x; tmp[1] = y; tmp[2] = z;
        float dst[4];
        Obj_59aed0(dst, tmp, m);
        x = dst[0]; y = dst[1]; z = dst[2];
        float* p = (((HkObj*)self)->*(PMemGetVec)slotGetVec(*(u32*)self + 0x2c))();
        x += p[0]; y += p[1]; z += p[2];
    }
    out[0] = x;
    out[3] = 0.0f;
    out[2] = z;
    out[1] = y;
}

// ==================================================================================================
// 0x00b4dfe0  snap a position to the object's centre (when no match found for tag 6)
// ==================================================================================================
// @ 0x00b4dfe0
void __cdecl FUN_00b4dfe0(char* self, char* obj, float* pos)
{
    char* src = (char*)ld32(obj, 0x58);
    pos[0] = ldf(src, 0x40);
    pos[1] = ldf(src, 0x44);
    pos[2] = ldf(src, 0x48);

    i32 key;
    if (((HkObj*)obj)->find961(&key, 6)[0] == 0) {
        float* b = (((HkObj*)self)->*(PMemGetVec)slotGetVec(*(u32*)self + 0x68))();
        float c[3];
        c[0] = (b[3] + b[0]) * g_halfF;
        c[1] = (b[4] + b[1]) * g_halfF;
        c[2] = (b[5] + b[2]) * g_halfF;
        char* m = (char*)(((HkObj*)self)->*(PMemGetMatrix)slotGetMatrix(*(u32*)self + 0x30))();
        float dst[4];
        Obj_59aed0(dst, c, m);
        pos[0] -= dst[0];
        pos[1] -= dst[1];
        pos[2] -= dst[2];
    }
}

// ==================================================================================================
// 0x00b4e0c0  same snap as 00b4dfe0 but keyed on tag 6 being present
// ==================================================================================================
// @ 0x00b4e0c0
void __cdecl FUN_00b4e0c0(char* self, char* obj, float* out)
{
    i32 key;
    float x, y, z;
    if (((HkObj*)obj)->find961(&key, 6)[0] != 0) {
        float* p = (((HkObj*)self)->*(PMemGetVec)slotGetVec(*(u32*)self + 0x2c))();
        x = p[0]; y = p[1]; z = p[2];
    } else {
        float* b = (((HkObj*)self)->*(PMemGetVec)slotGetVec(*(u32*)self + 0x68))();
        x = (b[0] + b[3]) * g_halfF;
        y = (b[4] + b[1]) * g_halfF;
        z = (b[5] + b[2]) * g_halfF;
        char* m = (char*)(((HkObj*)self)->*(PMemGetMatrix)slotGetMatrix(*(u32*)self + 0x30))();
        float tmp[3];
        tmp[0] = x; tmp[1] = y; tmp[2] = z;
        float dst[4];
        Obj_59aed0(dst, tmp, m);
        x = dst[0]; y = dst[1]; z = dst[2];
        float* p = (((HkObj*)self)->*(PMemGetVec)slotGetVec(*(u32*)self + 0x2c))();
        x += p[0]; y += p[1]; z += p[2];
    }
    out[0] = x;
    out[3] = 0.0f;
    out[2] = z;
    out[1] = y;
}

// ==================================================================================================
// 0x00b4d220  GB1 constructor (base cGonzagoSubsystem + the physics-object vtable family)
// ==================================================================================================
// @ 0x00b4d220
void* __fastcall FUN_00b4d220(char* self)
{
    st32(self, 0, 0x13eb384u);
    ((HkObj*)(self + 4))->gonzagoCtor();

    stf(self, 0x34, g_oneF);
    stf(self, 0x38, g_4f);
    st32(self + 4, 0, 0x14611e0u);
    st32(self, 0, 0x1461230u);
    st32(self, 0x8, 0x14611dcu);
    st32(self, 0x20, 2);
    st8(self, 0x24, 1);
    st8(self, 0x25, 1);
    st8(self, 0x27, 1);
    st8(self, 0x30, 1);
    st8(self, 0x32, 1);
    st32(self, 0x3c, 0xffffffffu);
    st8(self, 0x26, 0);
    st8(self, 0x28, 0);
    st8(self, 0x31, 0);
    stf(self, 0x50, g_oneF);
    stf(self, 0x54, g_twoF);
    st32(self, 0x44, 0x154df28u);
    st32(self, 0x4c, 0);
    st32(self, 0x58, 0);
    char* ring = self + 0x78;
    st32(self, 0x48, 1);
    st32(self, 0x60, (u32)(size_t)ring);
    st32(self, 0x64, (u32)(size_t)ring);
    st32(self, 0x68, (u32)(size_t)(ring + 0x400));
    st32(self, 0x74, 0);
    st32(self, 0x478, 0);
    char t[8];
    ((HkObj*)(self + 0x47c))->b4b1d0(t + 4, t);
    stf(self, 0x14d8, g_oneF);
    stf(self, 0x14dc, g_twoF);
    st32(self, 0x14d0, 1);
    st32(self, 0x14cc, 0x154df28u);
    st32(self, 0x14d4, 0);
    st32(self, 0x14e0, 0);
    g_someGlobal = 0;
    Obj_b5a410();
    ((HkObj*)self)->b4d930();
    char* pool = (char*)EAAllocate(0xbc, "Simulator/cPhysics", 0, 0, 0, 0);
    if (pool) { ((HkObj*)pool)->b46ff0(); }
    else pool = 0;
    g_physPool = pool;
    *(u32*)pool = 0;
    *(u32*)(pool + 4) = (u32)(size_t)Obj_bbb500(0x1000, 0x1000);
    ((HkObj*)(pool + 8))->b72080(0x3c, 0x800);
    ((HkObj*)(pool + 0x3c))->b72080(0x138, 0x1000);
    ((HkObj*)self)->b4d140();
    Obj_b41020();
    return self;
}
