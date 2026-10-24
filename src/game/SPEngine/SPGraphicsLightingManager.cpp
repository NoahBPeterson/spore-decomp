// src/game/SPEngine/SPGraphicsLightingManager.cpp -- migrated from slice(s) s009272c0, s00782860, s0070de90, s0070ced0, s0070c040, s0070aed0, s0070a5b0, s00709cf0, s00708f40, s00708100, s007070d0, s00706170, s00705660, s007046e0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsLightingManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cLightingManager.h"
#include "SP/cShaderDataLightingInfo.h"
#include <intrin.h>
#include <xmmintrin.h>
#include <math.h>
#include <algorithm>
#include <new>
#include "SP/cLightingWorld.h"
#include "SP/cLightingConfig.h"
#include <string.h>
#include "EA/Swarm/cIMap.h"
#include "cSPColorRGB.h"
#include "EA/Variant.h"
#include "cSPVector3.h"
#include "SP/cLight.h"
#include "SP/cPropertyList.h"
#include "EA/ResourceMan/Key.h"
#include "EA/AutoRefCount.h"
#include "SP/cLocalLightInfo.h"
#pragma intrinsic(_InterlockedExchange)

// ---- items of slice s007046e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct __declspec(align(16)) V32 { __m128 a, b; };
struct Big {
    char pad[0x18];
    int f18, f1c, f20, f24, f28, f2c, f30;
    void set_7050e0(int a, int* p);
    void get_705190(int* out);
};
struct Big50 {
    char pad[0x48];
    int f48, f4c, f50;
    void get_705190(int* out);
};
struct Fog98 { int x[0x26]; };
struct BigF8 {
    char pad[0xf8];
    Fog98 fog;
    void set_7051b0(const Fog98* src);
};
struct E5 { int f0, f1, f2, f3, f4; };
struct cShaderDataLightingInfo {
    uint8_t  mType;         // +0x00
    uint8_t  mNumCoeffs;    // +0x01
    uint16_t mDummy;        // +0x02
    int      f04, f08, f0c; // +0x04
    float    mCelStrength;  // +0x10
    char     pad14[0xc];    // +0x14
    __m128   mBaseLight;    // +0x20
    __m128   mCoeffs[25];   // +0x30
    cShaderDataLightingInfo& operator=(const cShaderDataLightingInfo& s);
};
// ---- items of slice s007046e0 end

// ---- items of slice s00705660 begin (TODO(rewrite): local stubs, replace by canonical classes)
void __stdcall sub_406540(void*, void*, int, int, void*); // EASTL fill/uninitialized helper
void __fastcall sub_620230(void*);                // intrusive_list_base dtor
void  sub_f47380(void*);                          // operator delete
struct W5920 {
    uint32_t pad[4];        // 0x00
    int**    m10;           // 0x10
    int* get();
};
struct S11 {
    int   a, b, c;          // 0x00
    float d, e, f, g, h;    // 0x0c
    int   i, j, k;          // 0x20
    S11& operator=(const S11& s);
};
struct S7 {
    float f[7];
    S7& operator=(const S7& s);
};
struct W5ef0 {
    void* buf0;             // 0x00
    uint32_t pad[4];
    void* buf14;            // 0x14
    uint32_t pad2[5];
    void dtor();
};
struct W5970 {
    uint32_t pad[4];
    float* m10;             // 0x10
    float f(int a2, float p3);
};
struct V4 { float x, y, z, w; };
struct V3 { float x, y, z; };
struct W5a20 {
    uint32_t pad[0x12];     // 0x00
    V3    mSun;             // 0x48
    int   nphases;          // 0x54
    V4    phases[1];        // 0x58
    void setAtm(float* v, int n, float* ph);
};
struct W5af0 {
    uint32_t pad[6];        // 0x00
    int*     begin;         // 0x18
    int*     end;           // 0x1c
    void* find(int key);
};
void fn705030() {}
struct V4b { float x, y, z, w; };
struct Big5b50 {
    uint8_t  f0;            // 0x00
    uint8_t  f1;            // 0x01
    uint16_t f2;            // 0x02
    float    f4, f8, fc, f10; // 0x04
    char     pad14[0xc];    // 0x14
    __m128   m20;           // 0x20
    V4b      coeffs[25];    // 0x30
    Big5b50* copy(const Big5b50* s);
};
// ---- items of slice s00705660 end

// ---- items of slice s00706170 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_0162991c, g_016299f4, g_01629ad8, g_01629928;     // 0x0162991c, 0x016299f4, 0x01629ad8, 0x01629928
void* sub_f473d0(int, int, int, const char*, int, int, const char*, int);
void  sub_705b50(void);                           // copy-ctor body (0x00705b50)
struct IVoid { virtual void v0(); virtual void v1(); };
struct W6870 {
    int* m0;
    int get(unsigned idx);
};
struct W6890 {
    int* m0;
    int get(unsigned idx);
};
struct W6920 {
    int** m0;
    unsigned next(unsigned idx);
};
struct W6980 {
    int** m0;
    unsigned next(unsigned idx);
};
struct W69e0 {
    int** m0;
    unsigned next(unsigned idx);
};
struct W67f0 {
    char pad0[0xa8];
    void* pA8;              // 0xa8
    char padAC[0x10];
    void* pBC;              // 0xbc
    ~W67f0();
};
struct W68c0 {
    char pad[0x1c0];
    float f1c0, f1c4, f1c8;
    int   f1cc, f1d0;
    W68c0* copyFrom(const W68c0* s);
};
struct Vec20 { void* b; void* e; void* c; Vec20* init(int n, int unused); };
struct Vec10 { void* b; void* e; void* c; Vec10* init(int n, int unused); };
struct E9 { int a; float b, c, d, e, f, g, h, i; };
struct TreeFind { void find(void* result, void* key); };
struct W6840 {
    char pad0[0x2c];        // 0x00
    TreeFind tree;          // 0x2c  (rbtree with anchor at 0x30)
    int GetLightingWorld(int key);
};
struct Vec3f { float x, y, z; };
struct Mat3f { float m[9]; };
struct V4Ret { __m128 v; float f(int i) const { return ((const float*)&v)[i]; } };
void SH_Accumulate(const float* dir, int n, const __m128* in, __m128* out);      // 0x00794e60 -> 0x00784560
void SH_RotateZHAdd(const float* dir, int n, const __m128* in, __m128* out);     // 0x00794e70 -> 0x00785500
void SH_Rotate(const Mat3f* m, int n, const __m128* in, __m128* out);            // 0x00795eb0 -> 0x007864c0
void SH_AddGroundBounce(int n, __m128* buf, const __m128* a, const __m128* b);   // 0x00784420
void SH_ZonalCoeffs(float t, float* out);                                        // 0x007831d0
void SH_ApplyNormalizationConstants(int n, __m128* buf);                         // 0x00783590
void MatrixFromDirection(const Vec3f* dir, Mat3f* out);                          // 0x006983a0
struct SHGroundQuery {
virtual void q0();
virtual void q1();
virtual void q2();
virtual void q3();
virtual void q4();
virtual void q5();
virtual void q6();
virtual void q7();
virtual void q8();
virtual void q9();
virtual void q10();
    virtual float* Query(float* scratch, const Vec3f* pos);                      // +0x2c
};
struct LightCfg {
    char pad00[0xbc];
    __m128* vecBegin;                // +0xbc
    __m128* vecEnd;                  // +0xc0
    char padc4[0x18];
    float groundScaleB;              // +0xdc
    float groundScaleA;              // +0xe0
    char pade4[0x20];
    float zhColor[4];                // +0x104
    float riseBias;                  // +0x114
    float riseScale;                 // +0x118
    float setBias;                   // +0x11c
    float setScale;                  // +0x120
    float baseA;                     // +0x124
    float baseB;                     // +0x128
};
struct EnvSample {
    char pad00;
    unsigned char bandsByte;         // +1
    char pad02[2];
    Vec3f sunDir;                    // +4
    float blendA;                    // +0x10
    char pad14[0xc];
    __m128 hdr;                      // +0x20
    __m128 coeffs[25];               // +0x30 ...
    Vec3f pos;                       // +0x1c0
    char pad1cc[4];
    int groundFlag;                  // +0x1d0
};
struct EnvLW {
    char pad00[0x10];
    LightCfg* cfg;                   // +0x10
    char pad14[0x20];
    int nBands;                      // +0x34 (vector count)
    int nOut;                        // +0x38
    char pad3c[0x98];
    float lightPos[3];               // +0xd4
    char padE0[0x10];
    __m128 dayCoeffs[7];             // +0xf0
    __m128 nightCoeffs[7];           // +0x160
    char padD0[0x240 - 0x160 - 7 * 16];
    Vec3f sunDir;                    // +0x240
    SHGroundQuery* ground;           // +0x24c

    void UpdateEnvLightSample(EnvSample* out);
};
static inline void Clamp01(float* x, const float* hi)
{
    _mm_store_ss(x, _mm_min_ss(_mm_max_ss(_mm_setzero_ps(), _mm_load_ss(x)), _mm_load_ss(hi)));
}
// ---- items of slice s00706170 end

// ---- items of slice s007070d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
    void EastlFree(...); // 0x00f47380
void* __cdecl EastlAlloc8(uint32_t n, uint32_t align, int a, const char* name, int b, int c,
                          const char* file, int line);
void* __cdecl EastlAlloc6(uint32_t n, const char* name, int a, int b, const char* file, int line);
void  __cdecl EastlFree(void* p); // 0x00f47380
struct Vector4 { float f[4]; };
struct cSPVector3_s0070_70d0 { float x, y, z; };
Vector4* CopyVec4(Vector4* first, Vector4* last, Vector4* result);
Vector4* CopyBackVec4(Vector4* first, Vector4* last, Vector4* resultEnd);
Vector4* UninitCopyVec4(Vector4* first, Vector4* last, Vector4* result);
struct Vec4 {
    Vector4* mpBegin;
    Vector4* mpEnd;
    Vector4* mpCapacity;
    Vector4* DoRealloc(uint32_t n, const Vector4* first, const Vector4* last);
    Vec4& operator=(const Vec4& x);
    void DoInsertValues(Vector4* position, Vector4* source);
    void InsertValuesAt(Vector4* position, uint32_t n, const Vector4* value);
};
struct Buf28 {
    char pad0[0x28];
    void* mpBlock;
    char pad2[0xc];
    void* mpDefault;
    void Free();
};
struct VObj {
    virtual void slot0();
    virtual void slot1();
};
struct NukeNode {
    VObj* mpObj;
    char pad0[0xa4];
    void* mpA8;
    char pad1[0x10];
    void* mpBC;
    char pad2[0x144 - 0xc0];
};
struct Rbtree {
    void DoNukeSubtree(NukeNode* first, NukeNode* last);
};
struct SlotVec28 {
    int* mpBlocks;
    char pad4[0x14];
    uint32_t mField18;
    uint32_t mField1c;
    uint32_t Next(uint32_t idx);
    uint32_t DestroyNext(uint32_t idx);
    void Release(uint32_t idx);
    void ReleaseDestroy(uint32_t idx);
};
struct SlotVecC4 {
    int* mpBlocks;
    char pad4[0x14];
    uint32_t mField18;
    uint32_t mField1c;
    uint32_t Next(uint32_t idx);
    void DestroyEntry(uint32_t idx);
};
struct Allocator {
    void Destroy(void* p);
};
extern Allocator* g_pAlloc;     // 0x016c8b44
struct SlotDeque {
    void** mpBegin;
    void** mpEnd;
    char pad8[0xc];
    int mField14;
    void DestroyAll(int unused);
};
struct cShaderDataLightingInfo_s0070_70d0 {
    char pad[0x1c0];
    cShaderDataLightingInfo_s0070_70d0& operator=(const cShaderDataLightingInfo_s0070_70d0& x);
};
struct EnvEntry {
    cShaderDataLightingInfo_s0070_70d0 mShaderData;   // +0x000
    cSPVector3_s0070_70d0 mPosition;                  // +0x1c0
    int mPad1cc;                           // +0x1cc
    uint32_t mCelStrength;                 // +0x1d0
};
struct IntrusiveList { ~IntrusiveList(); };
struct Elem38 {
    int mTag;               // +0x00
    void* mp4;              // +0x04
    char pad8[0x10];
    void* mp18;             // +0x18
    char pad1c[0x14];
    IntrusiveList mList;    // +0x30
};
struct Deque38 {
    char pad0[4];
    void* mpData;           // +0x04
    char pad8[0xc];
    int mIndex14;           // +0x14
    void PopDestroy();
};
struct cLightingWorld {
    char pad[0x1000];
    void CreateEnvLightSample(EnvEntry* pEntry, const cSPVector3_s0070_70d0* pPos, uint32_t celStrength);
    void UpdateEnvLightSample(EnvEntry* pEntry);
    void GetLocalShaderData(void* e);
    void ReleaseLocalCache(void* e);
    void UpdateLightPosition(uint32_t id, const cSPVector3_s0070_70d0* pos);
    void RemoveLightFromList(uint32_t id, int index, int* list);
    void UpdateLocalLightSample(int* info);
};
void FillVec4(Vector4* first, Vector4* last, const Vector4* value);        // 0x705e90
void UninitFillVec4(Vector4* first, uint32_t n, const Vector4* value);     // 0x705ec0
struct SHObject { char pad[0x24]; };
void CopySHO(SHObject* first, SHObject* last, SHObject* result);                 // 0x707630
void UninitCopySHO5(SHObject** out, SHObject* src, SHObject* dst, SHObject* dstEnd, SHObject* srcEnd); // 0x706c80
struct VecSHO {
    SHObject* mpBegin;      // +0x00
    SHObject* mpEnd;        // +0x04
    SHObject* mpCapacity;   // +0x08
    SHObject* mpInline;     // +0x10
    SHObject* DoRealloc(uint32_t n, SHObject* first, SHObject* last);   // 0x7079a0
    VecSHO& operator=(const VecSHO& x);
};
struct Vec8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    char* mpInline;
    void DoInsertValues(char* position, uint32_t n, const void* value);
};
void MoveElems8(char* dst, char* src, uint32_t n);          // 0x76ffd0
void CopyElems8(char* first, char* last, char* dst);        // 0x73fe50
void UninitFill8(char* dst, uint32_t n, const void* value); // 0xa52da0
void* UninitCopy8(char* first, char* last, char* dst);      // 0x006ac440
void CopyAssign8(char* first, char* last, char* dst);       // 0x0099efa0
void __cdecl AddSphereLighting(Vector4* dst, void* base, int count, Vector4 value); // 0x7961d0
struct __declspec(align(16)) V32_s0070_70d0 { float f[8]; };
V32_s0070_70d0* UninitCopy32(V32_s0070_70d0* first, V32_s0070_70d0* last, V32_s0070_70d0* result);      // 0x7051e0
V32_s0070_70d0* CopyBack32(V32_s0070_70d0* first, V32_s0070_70d0* last, V32_s0070_70d0* resultEnd);     // 0x705220
struct Vec32 {
    V32_s0070_70d0* mpBegin;
    V32_s0070_70d0* mpEnd;
    V32_s0070_70d0* mpCapacity;
    void DoInsertValue(V32_s0070_70d0* position, const V32_s0070_70d0* value);
};
// ---- items of slice s007070d0 end

// ---- items of slice s00708100 begin (TODO(rewrite): local stubs, replace by canonical classes)
void ReleaseElem(void* p);                            // 0x007610F0

// free-list vector at cLightingWorld + 0x478 (fixed_vector<int,128>)
struct LightFreeVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    void DoInsertValue(void** position, void* const& value);  // 0x006C1570
};
struct CellInfo_s0070_8100 { int x, y; };
struct V32_s0070_8100 { union { float f[8]; uint32_t u[8]; }; };
struct VecCell {
    CellInfo_s0070_8100* mpBegin;      // +0x00
    CellInfo_s0070_8100* mpEnd;        // +0x04
    CellInfo_s0070_8100* mpCapacity;   // +0x08
    char pad_c[4];
    CellInfo_s0070_8100* mpInline;     // +0x10
    CellInfo_s0070_8100* DoRealloc(uint32_t n, const CellInfo_s0070_8100* first, const CellInfo_s0070_8100* last);  // 0x754f80
    void assign(const CellInfo_s0070_8100* first, const CellInfo_s0070_8100* last, int tag);
};
void* MoveRange5(void** out, const CellInfo_s0070_8100* first, const CellInfo_s0070_8100* last, CellInfo_s0070_8100* dst,
                 const CellInfo_s0070_8100* end);               // 0x76ffd0
struct Vec8b {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    void resize(uint32_t n);
    void DoInsertValues(char* position, uint32_t n, const void* value);  // 0x707d10
    void Erase(char* first, char* last);                                 // 0xd018d0
};
struct Vec16 {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    void resize(uint32_t n);
    void DoInsertValues16(char* position, uint32_t n, const void* value);  // 0x77d510
};
void Copy16(char* first, char* last, char* result);    // 0x705250
struct ClearVec {
    char pad0[0x4c];
    void** mpBegin;     // +0x4c
    void** mpEnd;       // +0x50
    char pad54[0xc];
    void* mpExtra;      // +0x60
    void clear();
};
struct IdVec_s0070_8100 {
    uint32_t* mpBegin;       // +0x00
    uint32_t* mpEnd;         // +0x04
    uint32_t* mpCapacity;    // +0x08
    void DoInsertValue(uint32_t* position, const uint32_t& value);  // 0x4558a0
};

struct SampleVec {
    V32_s0070_8100* mpBegin;            // +0x00
    V32_s0070_8100* mpEnd;              // +0x04
    V32_s0070_8100* mpCapacity;         // +0x08
    char pad0c[8];
    IdVec_s0070_8100 mIds;              // +0x14
    char pad20[8];
    int mCount;              // +0x28
    void DoInsertValue(V32_s0070_8100* position, const V32_s0070_8100* value);   // 0x707a50
};
struct cLightingWorld_s0070_8100 {
    void RemoveLight(uint32_t id);  // 0x007085a0 (cLightingWorld::RemoveLight)
    void RemoveLightFromList(uint32_t id, int index, int* list);  // 0x00707270 (cLightingWorld::RemoveLightFromList)
    void DestroyLightingInfo(void* e);  // 0x00708710 (cLightingWorld::DestroyLightingInfo)
    void ReleaseLocalCache(void* e);  // 0x00707790 (cLightingWorld::ReleaseLocalCache)
    void AddLocalSample(uint32_t id, int index, SampleVec* vec);  // 0x00708810 (cLightingWorld::AddLocalSample)
};
struct cLightingConfig_s0070_8100 {
    cLightingConfig_s0070_8100& operator=(const cLightingConfig_s0070_8100& x);
};
void release(void* p);
// ---- items of slice s00708100 end

// ---- items of slice s00708f40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_lm_vtbl0;
extern int g_lm_vtbl1;
extern int g_lm_vtbl2;
extern int g_lm_vtbl3;
extern int g_lm_vtbl4;
extern float g_lm_f0;   // 0x1535980
extern float g_lm_f1;   // 0x1535984
extern float g_lm_f2;   // 0x1535988
extern float g_defAmbient[3];                                   // 0x015359f8
extern uint32_t g_cfgAmbient[3];                                // 0x01629884
struct LightingManager {
    void Init();
};
struct IEffect {                                                // ref-counted effect object
    virtual void AddRef();
    virtual void Release();
    virtual void Lock();                                        // +0x08
    virtual void Unlock();                                      // +0x0c
    virtual int GetValue();                                     // +0x10
};
#define PV(n) virtual void pv##n();
struct IEffectsManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual IEffect* GetEffect(uint32_t id, int arg);           // +0x8c
};
struct IMessageServer {
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void Post(uint32_t id, int a, int b);               // +0x14
};
namespace SP {
IEffectsManager* EffectsManager();                              // 0x0067ddd0
}
namespace SP {
IMessageServer* MessageServer();                                // 0x0067dcc0
}
struct Vec3 {
    float x, y, z;
    Vec3(float a, float b, float c) { x = a; y = b; z = c; }
    Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
};
uint32_t __cdecl PackDirLight(Vec3 a, Vec3 b);                  // 0x007623f0
uint32_t __cdecl PackSunLight(Vec3 pos, Vec3 axis, float w);    // 0x007624c0
__declspec(align(16)) struct Vector4_s0070_8f40 {
    union {
        __m128 m;
        struct { float x, y, z, w; };
    };
    Vector4_s0070_8f40() {}
    Vector4_s0070_8f40(float a, float b, float c, float d) : m(_mm_set_ps(d, c, b, a)) {}
    Vector4_s0070_8f40(__m128 v) : m(v) {}
    Vector4_s0070_8f40(const Vector4_s0070_8f40& o) : m(o.m) {}
    Vector4_s0070_8f40& operator=(const Vector4_s0070_8f40& o) { m = o.m; return *this; }
};
static inline bool Bit(unsigned v, int n) { return (v >> n) & 1; }
static inline bool FlagSet(unsigned v, unsigned m) { return (v & m) != 0; }
struct U32Vec {                                                 // eastl::vector<uint32_t>
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    void DoInsertValue(uint32_t* pos, const uint32_t& v);       // 0x006ec4a0 (thiscall, ret 8)
    void push_back(uint32_t v)
    {
        if (mpEnd < mpCap)
            ::new (mpEnd++) uint32_t(v);
        else
            DoInsertValue(mpEnd, v);
    }
};
struct DirLight {                                               // 0x1c bytes at Config+8
    float px, py, pz;       // +0x00
    float k;                // +0x0c
    float dx, dy, dz;       // +0x10
};
struct Config {                                                 // object at cLightingWorld+0x10
    char pad00[4];
    uint32_t mFlags;        // +0x04 (bits 0-3: DirLight present, 4: ambient override, 5: sun)
    DirLight mLights[4];    // +0x08
    float m78, m7c, m80;    // +0x78
    float m84;              // +0x84 (sun scale)
    float m88;              // +0x88
    float vx, vy, vz;       // +0x8c
    uint32_t mAmbient[3];   // +0x98
    char padA4[0x18];
    Vector4_s0070_8f40* mAddBegin;     // +0xbc
    Vector4_s0070_8f40* mAddEnd;       // +0xc0
    char padC4[0xc];
    float mScale;           // +0xd0
    char padD4[8];
    float mEffectA;         // +0xdc
    float mEffectB;         // +0xe0
    char padE4[0x40];
    float mIntensity;       // +0x124
    bool HasLight(int mask) const { return (mFlags & mask) != 0; }
};
template <int STRIDE>
struct SlotDeque_s0070_8f40 {                                              // spstl::slot_deque
    char** mpBegin;         // +0x00
    char** mpEnd;           // +0x04
    char pad08[0xc];
    int mLast;              // +0x14
    int mFirst;             // +0x18
    int Capacity() const { int n = (int)(mpEnd - mpBegin); return n * 128 + mLast - 0x7f; }
    char* Entry(unsigned idx) const { return mpBegin[idx >> 7] + (idx & 0x7f) * STRIDE; }
};
struct LightingInfo {                                           // at cLightingWorld+0x260
    char pad00;
    unsigned char mNumBands;    // +0x01
    char pad02[0xe];
    float mIntensity;           // +0x10
    char pad14[0x1c];
    Vector4_s0070_8f40 mCoeffs[25];        // +0x30
};
template <class T> static inline const T& MinRef(const T& a, const T& b) { return (a < b) ? a : b; }
struct cLightingWorld_s0070_8f40 {
    char pad00[0x10];
    Config* mCfg;                   // +0x10
    char pad14[4];
    int mField18;                   // +0x18
    char pad1c[0x24];
    float mAmbient[3];              // +0x40
    U32Vec mDirLights;              // +0x4c
    char pad58[8];
    uint32_t mSunLight;             // +0x60
    uint8_t mFlags;                 // +0x64
    char pad65[3];
    float mPos[3];                  // +0x68
    float mScale;                   // +0x74
    float m[9];                     // +0x78
    char pad9c[0x44];
    bool mDirty;                    // +0xe0
    char pade1[0x16b];
    IEffect* mEffect;               // +0x24c
    int mEffectValue;               // +0x250
    char pad254[0xc];
    LightingInfo mInfo;             // +0x260
    char pad_[0x424 - 0x260 - sizeof(LightingInfo)];
    bool mEnabled;                  // +0x424
    char pad425[0x16b];
    bool mEnvFlag;                  // +0x590
    char pad591[3];
    SlotDeque_s0070_8f40<0x1f0> mEnvCache;     // +0x594
    char pad5b0[0x58];
    SlotDeque_s0070_8f40<0x1e0> mLocalCache;   // +0x608

    void PreUpdate();                                           // 0x007087a0
    void UpdateEnvLightSample(void* sample);                    // 0x00706170
    void UpdateLocalLightSample(int handle);                    // 0x00707370
    void ApplyGlobalState(int* state);  // 0x00708f40 (cLightingWorld::ApplyGlobalState)
    void ApplyConfig();
};
// ---- items of slice s00708f40 end

// ---- items of slice s00709cf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Alloc {
    void Destroy(void* p);
};
extern Alloc* g_pAlloc_s0070_9cf0;                                // 0x016C8B44
struct ClearDeque {
    void** mpBegin;     // +0x00
    void** mpEnd;       // +0x04
    char pad8[0xc];
    int mField14;       // +0x14
    void ClearImpl(int unused);
};
struct StateSource {
    void* Create(void* state);          // 0x705af0
};
struct cLightingWorld_s0070_9cf0 {
    void SetLightingState(void* state);  // 0x0070a560 (cLightingWorld::SetLightingState)
    void Update();                       // 0x7094c0
    void Shutdown();  // 0x0070a3f0 (cLightingWorld::Shutdown)
    bool LoadProperties();
    void ConfigFromProperties(int* self);
    void DestroySlotDequeEh();           // 0x70a070
    void ConstructSampleVec(int n);      // 0x70a0d0
    void CopyConfig(int* self);          // 0x70a130
};
// ---- items of slice s00709cf0 end

// ---- items of slice s0070a5b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl RBTreeIncrement(void* node);             // 0x00921580
void  __cdecl RBTreeErase(void* node, void* anchor);   // 0x00921880
struct Property {
    char pad00[0x10];
    unsigned short mFlags;   // +0x10
    unsigned short mType;    // +0x12
    int* GetInt();           // Property::GetInt (0x0041e990)
};
static inline float PropertyFloat(Property* p)
{
    float* data = (float*)p;
    if (p->mFlags & 0x30)
        data = *(float**)p;
    return *data;
}
class PropertyList {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool GetProperty(uint32_t id, Property*& result);   // +0x24
};
extern PropertyList* sAppProperties;                            // 0x015fd918
struct EffectRef {
    IEffect* mp;
    EffectRef& operator=(IEffect* p);                           // AutoRefCount::operator= (0x00b5f950)
};
struct Vec3_s0070_a5b0 {
    float x, y, z;
    Vec3_s0070_a5b0& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
};
struct Vec4u : Vec3_s0070_a5b0 { float w; };                               // unaligned 16-byte vector
__declspec(align(16)) struct Vector4_s0070_a5b0 {
    union {
        __m128 m;
        struct { float x, y, z, w; };
    };
    Vector4_s0070_a5b0() {}
    Vector4_s0070_a5b0(__m128 v) : m(v) {}
    Vector4_s0070_a5b0(const Vector4_s0070_a5b0& o) : m(o.m) {}
    Vector4_s0070_a5b0& operator=(const Vector4_s0070_a5b0& o) { m = o.m; return *this; }
    bool operator==(const Vector4_s0070_a5b0& o) const
    {
        bool r = _mm_movemask_ps(_mm_cmpeq_ps(m, o.m)) == 0xf;
        return r;
    }
};
void __cdecl CalcAtmosphereZH(int count, Vec4u* dirs, int numBands, Vector4_s0070_a5b0* out);        // 0x00796420
void __cdecl SHAccumulate(const float* dir, int numBands, const Vector4_s0070_a5b0* coeffs, Vector4_s0070_a5b0* out); // 0x00794e60
void __cdecl ApplyNormalizationConstants(int numBands, Vector4_s0070_a5b0* coeffs);                   // 0x00783590
struct FixedVec4 {
    Vec4u* mpBegin;
    Vec4u* mpEnd;
    Vec4u* mpCapacity;
    char pad0c[4];
    void* mpPool;
    char pad14[4];
    Vec4u mStorage[8];
    FixedVec4(int n);                                           // 0x0070a0d0
    ~FixedVec4() { if (mpBegin && mpBegin != mpPool) EastlFree(mpBegin); }
    Vec4u& operator[](int i) { return mpBegin[i]; }
};
static inline Vector4_s0070_a5b0 Desaturate(const Vector4_s0070_a5b0& v, float t)
{
    Vector4_s0070_a5b0 c = v;
    float lum = v.y * 0.587f + v.x * 0.299f + v.z * 0.114f;
    Vector4_s0070_a5b0 gray(_mm_set_ps(c.w, lum, lum, lum));
    return Vector4_s0070_a5b0(_mm_add_ps(_mm_mul_ps(_mm_sub_ps(v.m, gray.m), _mm_set1_ps(t)), gray.m));
}
struct World {                                                  // object at cLightingWorld+0x0c
    char pad00[0x48];
    Vec3_s0070_a5b0 mDir;              // +0x48
    int mNumLights;         // +0x54
    Vec4u mLights[1];       // +0x58
};
struct Config_s0070_a5b0 {                                                 // object at cLightingWorld+0x10
    PropertyList* mProps;   // +0x00
    char pad04[0xb8];
    Vector4_s0070_a5b0* mAddBegin;     // +0xbc
    Vector4_s0070_a5b0* mAddEnd;       // +0xc0
    char pad0c4[0xc];
    float mScale;           // +0xd0
    float mSunThreshold;    // +0xd4
    float mLightScale;      // +0xd8
    float mEffectA;         // +0xdc
    float mEffectB;         // +0xe0
    Vec4u mColors[3];       // +0xe4
};
template <int STRIDE>
struct SlotDeque_s0070_a5b0 {                                              // spstl::slot_deque
    char** mpBegin;         // +0x00
    char** mpEnd;           // +0x04
    char pad08[0xc];
    int mLast;              // +0x14
    int mFirst;             // +0x18
    int Capacity() const { int n = (int)(mpEnd - mpBegin); return n * 128 + mLast - 0x7f; }
    char* Entry(unsigned idx) const { return mpBegin[idx >> 7] + (idx & 0x7f) * STRIDE; }
};
struct DequeIter {                                              // eastl::deque iterator, 0x2c-byte elements
    char* mpCur;
    char* mpBegin;
    char* mpEnd;
    char** mpSub;
};
struct DequeWalker {                                            // forward walk over a DequeIter
    char* mpCur;
    char* mpEnd;
    char** mpSub;
    DequeWalker(const DequeIter& it) : mpCur(it.mpCur), mpEnd(it.mpEnd), mpSub(it.mpSub) {}
    void Next()
    {
        mpCur += 0x2c;
        if (mpCur == mpEnd) {
            ++mpSub;
            mpCur = *mpSub;
            mpEnd = mpCur + 0xb0;
        }
    }
};
struct LightingInfo_s0070_a5b0 {                                           // at cLightingWorld+0x260
    char pad00;
    unsigned char mNumBands;    // +0x01
    char pad02[2];
    Vec3_s0070_a5b0 mDir;                  // +0x04
    char pad10[0x10];
    Vector4_s0070_a5b0 mAmbient;           // +0x20
    Vector4_s0070_a5b0 mCoeffs[25];        // +0x30
};
struct cLightingWorld_s0070_a5b0 {
    char pad00[0xc];
    World* mWorld;                  // +0x0c
    Config_s0070_a5b0* mCfg;                   // +0x10
    char pad14[0x20];
    int mNumBands;                  // +0x34
    int mNumCoeffs;                 // +0x38
    int mBudget;                    // +0x3c
    char pad40[0xa0];
    bool mDirty;                    // +0xe0
    char pade1[0xf];
    Vector4_s0070_a5b0 mZH[3][7];              // +0xf0
    Vec3_s0070_a5b0 mSun;                      // +0x240
    EffectRef mEffect;              // +0x24c
    int mEffectValue;               // +0x250
    char pad254[0xc];
    LightingInfo_s0070_a5b0 mInfo;             // +0x260
    LightingInfo_s0070_a5b0* mActive;          // +0x420
    bool mEnabled;                  // +0x424
    char pad425[0x2f];
    DequeIter mFirst;               // +0x454
    DequeIter mLast;                // +0x464
    char pad474[0x120];
    SlotDeque_s0070_a5b0<0x1f0> mEnvCache;     // +0x594
    char pad5b0[0x18];
    int mEnvIdx;                    // +0x5c8
    bool mEnvRescan;                // +0x5cc
    int mLocalCount;                // +0x5d0
    char pad5d4[0x34];
    SlotDeque_s0070_a5b0<0x1e0> mLocalCache;   // +0x608
    char pad624[0x38];
    int mLocalIdx;                  // +0x65c
    bool mLocalRescan;              // +0x660

    void Update(uint32_t param);  // 0x0070a5b0 (cLightingWorld::Update)
    void Shutdown();  // 0x0070a3f0 (cLightingWorld::Shutdown)
    void UpdateEnvLightSample(void* sample);                    // 0x00706170
    void UpdateLocalLightSample(int handle);                    // 0x00707370
};
struct RBTree {
    void Find(void* out, const void* key);   // 0xE5C780
};
// ---- items of slice s0070a5b0 end

// ---- items of slice s0070aed0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gDefaultFloat;               // 0x015D1168
void EastlFree(void* p) throw();  // 0x00F47380
struct Vector2 { float x, y; };
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3& operator+=(const Vector3& o) {
        x += o.x;
        y += o.y;
        z += o.z;
        return *this;
    }
};
inline Vector3 operator*(const Vector3& v, float s) { return Vector3(v.x * s, v.y * s, v.z * s); }
struct ColorRGB {
    float r, g, b;
    ColorRGB() {}
    ColorRGB(const ColorRGB& o) : r(o.r), g(o.g), b(o.b) {}
};
struct PlainVector4 { float x, y, z, w; };
struct Vector4_s0070_aed0 {
    __m128 v;
    Vector4_s0070_aed0() {}
    Vector4_s0070_aed0(float x, float y, float z, float w) { v = _mm_setr_ps(x, y, z, w); }
    Vector4_s0070_aed0(__m128 m) : v(m) {}
    Vector4_s0070_aed0& operator*=(float s) { v = _mm_mul_ps(v, _mm_set1_ps(s)); return *this; }
};
inline Vector4_s0070_aed0 operator*(float s, const Vector4_s0070_aed0& a) { return Vector4_s0070_aed0(_mm_mul_ps(_mm_set1_ps(s), a.v)); }
namespace EA {
namespace ResourceMan {
struct Key_s0070_aed0 {
    uint32_t mInstance;  // +0x0
    uint32_t mType;      // +0x4
    uint32_t mGroup;     // +0x8
};
}
}
namespace EA {
namespace ResourceMan {
class IResource {
public:
    virtual int AddRef();
    virtual int Release();
};
}
}
namespace EA {
namespace ResourceMan {
class IResourceManager {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual bool GetResource(const Key_s0070_aed0& key, IResource** ppResource, int arg_8, void* pDBPF,
                             void* pFactory, const Key_s0070_aed0* pCacheName);  // 0x0c
};
}
}
namespace EA {
namespace ResourceMan {
IResourceManager* GetManager();  // 0x0067DCD0
}
}
namespace EA {
struct Variant_s0070_aed0 {
    uint32_t mData[4];  // +0x0
    uint16_t mFlags;    // +0x10
    uint16_t mTypeId;   // +0x12

    void* GetStorage() {
        if (mFlags & 0x30) return *(void**)this;
        return mTypeId ? (void*)this : 0;
    }
    int GetCount() {
        if (mFlags & 0x30) return (int)mData[2];
        return mTypeId != 0;
    }
    const bool& GetBool();  // 0x0041E920
};
}
const Vector3& DefaultVector3();          // 0x006BB5E0
const ColorRGB& DefaultColorRGB();        // 0x006BB600
const EA::ResourceMan::Key_s0070_aed0& DefaultKey();  // 0x006BB640
extern const ColorRGB kColorWhite;        // 0x01629884
inline const float& AsFloat(EA::Variant_s0070_aed0* p) {
    if (p->mTypeId == 0xd || p->mTypeId == 0x10) return *(float*)p->GetStorage();
    return gDefaultFloat;
}
inline const Vector3& AsVector3(EA::Variant_s0070_aed0* p) {
    if (p->mTypeId == 0x31 || p->mTypeId == 0x10) return *(Vector3*)p->GetStorage();
    return DefaultVector3();
}
inline const ColorRGB& AsColorRGB(EA::Variant_s0070_aed0* p) {
    if (p->mTypeId == 0x32 || p->mTypeId == 0x10) return *(ColorRGB*)p->GetStorage();
    return DefaultColorRGB();
}
inline const EA::ResourceMan::Key_s0070_aed0& AsKey(EA::Variant_s0070_aed0* p) {
    if (p->mTypeId == 0x20 || p->mTypeId == 0x10) return *(EA::ResourceMan::Key_s0070_aed0*)p->GetStorage();
    return DefaultKey();
}
namespace SP {
class cPropertyList_s0070_aed0 {
public:
    virtual int AddRef();   // 0x00
    virtual int Release() throw();  // 0x04
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual bool GetPropertyA(uint32_t key, EA::Variant_s0070_aed0** out) const;
    virtual bool GetProperty(uint32_t key, EA::Variant_s0070_aed0** out) const;  // 0x24
};
}
namespace SP {
bool GetPropertyAsColorRGB(const cPropertyList_s0070_aed0* list, uint32_t key, ColorRGB* out);  // 0x006A11B0
}
namespace SP {
bool GetPropertyAsVector2(const cPropertyList_s0070_aed0* list, uint32_t key, Vector2* out);    // 0x006A10C0
}
namespace SP {
bool GetPropertyAsVector4(const cPropertyList_s0070_aed0* list, uint32_t key, PlainVector4* out);  // 0x006A1160
}
namespace SP {
bool GetPropertyArrayVector3(const cPropertyList_s0070_aed0* list, uint32_t key, int* count, Vector3** out);  // 0x006A0990
}
namespace SP {
bool GetPropertyArrayColorRGB(const cPropertyList_s0070_aed0* list, uint32_t key, int* count, ColorRGB** out);  // 0x006A0A70
}
namespace SP {
bool GetPropertyArrayVector4(const cPropertyList_s0070_aed0* list, uint32_t key, int* count, PlainVector4** out);  // 0x006A0A00
}
namespace SP {
void RemoveNormalizationConstants(int numBands, Vector4_s0070_aed0* coeffs);  // 0x00783830
}
namespace SP {
void ApplyNormalizationConstants(int numBands, Vector4_s0070_aed0* coeffs);   // 0x00783590
}
namespace SP {
void FindSHCoeffsFromHemiEnvMap(EA::ResourceMan::IResource* res, int numCoeffs, Vector4_s0070_aed0* coeffs);  // 0x00783FB0
}
namespace SP {
void FindSHCoeffsFromHDRCubeMap(EA::ResourceMan::IResource* res, int numBands, Vector4_s0070_aed0* coeffs);   // 0x00795EC0
}
namespace SP {
void CalcAtmosphereZH(int count, const PlainVector4* phases, int numBands, float* zh);  // 0x00796420
}
namespace SP {
void RotateZHToSH(const Vector3& dir, int numBands, const float* zh, Vector4_s0070_aed0* coeffs);  // 0x00794E60
}
namespace SP {
void RotateZHToSHAdd(const Vector3& dir, int numBands, const Vector4_s0070_aed0& color, const float* zh,
                     Vector4_s0070_aed0* coeffs);  // 0x00794E80
}
namespace SP {
void AddGroundBounce(int numBands, Vector4_s0070_aed0* coeffs, const Vector4_s0070_aed0& diffuse, const Vector4_s0070_aed0& specular);  // 0x00784420
}
namespace SP {
void GetHemisphereZH(float* zh);           // 0x00783380
}
namespace SP {
void GetConeZH(float cosAngle, float* zh);  // 0x007831D0
}
namespace EA {
template <class T> class AutoRefCount_s0070_aed0 {
public:
    AutoRefCount_s0070_aed0() : mpObject(0) {}
    __forceinline ~AutoRefCount_s0070_aed0() {
        if (mpObject) mpObject->Release();
    }
    AutoRefCount_s0070_aed0& operator=(T* p) {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    T** AsPPTypeParam() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    T* get() const { return mpObject; }
    T* mpObject;
};  // namespace EA
}
namespace eastl {
template <class T> inline const T& min(const T& a, const T& b) { return (b < a) ? b : a; }
}
template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    __forceinline ~SpVector() {
        if (mpBegin && ((int*)mpBegin)[-1] != 0) EastlFree(mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
};
struct LightFlags {
    uint32_t mWord;
    void set(uint32_t i) {
        if (i < 7) mWord |= ((uint32_t)1 << (i & 31));
    }
};
namespace SP {
struct cLight_s0070_aed0 {
    ColorRGB mColor;   // +0x0
    float mStrength;   // +0xc
    Vector3 mDir;      // +0x10
};
}
namespace SP {
class cLightingConfig_s0070_aed0 {
public:
    cLightingConfig_s0070_aed0();                                       // 0x00706DD0
    cLightingConfig_s0070_aed0& operator=(const cLightingConfig_s0070_aed0& other);  // 0x007089A0
    ~cLightingConfig_s0070_aed0() {}

    EA::AutoRefCount_s0070_aed0<cPropertyList_s0070_aed0> mpPropList;  // +0x00
    LightFlags mFlags;                           // +0x04
    cLight_s0070_aed0 mLights[4];                           // +0x08
    ColorRGB mPointLightColor;                   // +0x78
    float mPointLightStrength;                   // +0x84
    float mPointLightRadius;                     // +0x88
    Vector3 mPointLightPos;                      // +0x8c
    ColorRGB mSkylight;                          // +0x98
    bool mbCameraSpaceLighting;                  // +0xa4
    SpVector<Vector4_s0070_aed0> mSHObjects;                // +0xa8
    SpVector<Vector4_s0070_aed0> mSHCoeffs;                 // +0xbc
    float mPlanetAtmosphere;                     // +0xd0
    float mBounceDiffCos;                        // +0xd4
    float mBounceSpec;                           // +0xd8
    float field_DC;                              // +0xdc
    float field_E0;                              // +0xe0
    PlainVector4 mColourPhaseAdd[3];             // +0xe4
    float mSunStart;                             // +0x114
    float mSunInvRange;                          // +0x118
    float mNightStart;                           // +0x11c
    float mNightInvRange;                        // +0x120
    Vector2 field_124;                           // +0x124
    Vector2 mCelRange;                           // +0x12c
    bool mTerrainLightEnabled;                   // +0x134
    float mTerrainLightStrength;                 // +0x138
    float mTerrainLightSize;                     // +0x13c
    float mTerrainLightHeightDropoff;            // +0x140
};
}
namespace SP {
class cLightingManager_s0070_aed0 {
public:
    void FillLightingStateFromConfig(cPropertyList_s0070_aed0* props, cLightingConfig_s0070_aed0* config);  // 0x0070aed0 (SP::cLightingManager::FillLightingStateFromConfig)
    void AddSHCoeffs(cLightingConfig_s0070_aed0* config, Vector4_s0070_aed0* coeffs, int numBands, cPropertyList_s0070_aed0* props,
                     uint32_t scaleKey);  // 0x00709CF0

    uint32_t pad[4];      // +0x00
    int mNumSHBands;      // +0x10
    int mNumSHCoeffs;     // +0x14
};
}
inline bool GetFloatProperty(const SP::cPropertyList_s0070_aed0* props, uint32_t key, float* out) {
    EA::Variant_s0070_aed0* prop;
    if (props->GetProperty(key, &prop) && prop->mTypeId == 0xd) {
        *out = *(float*)prop->GetStorage();
        return true;
    }
    return false;
}
inline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline Vector3 Normalize(const Vector3& v) {
    float lenSq = Dot(v, v) + 1e-8f;
    float len = sqrtf(lenSq);
    float inv = 1.0f / len;
    return Vector3(v.x * inv, inv * v.y, inv * v.z);
}
// ---- items of slice s0070aed0 end

// ---- items of slice s0070c040 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct CellInfo { int x, y; };
struct cSPVector3_s0070_c040 { float x, y, z; };
struct FixedCellVector {
    CellInfo* mpBegin;      // +0x00
    CellInfo* mpEnd;        // +0x04
    CellInfo* mpCapacity;   // +0x08
    char pad_c[4];
    CellInfo* mpInline;     // +0x10
    FixedCellVector(const FixedCellVector& x);                           // 0x70c3a0
    void assign(const CellInfo* first, const CellInfo* last, int tag);   // 0x708340
};
struct cLocalLightInfo {
    cSPVector3_s0070_c040 mColour;     // +0x00
    float mSize;            // +0x0c
    cSPVector3_s0070_c040 mPosition;   // +0x10
    float mStrength;        // +0x1c
    void* mDecal;           // +0x20
    bool mGlobal;           // +0x24
    FixedCellVector mCells; // +0x28
    cLocalLightInfo(const cLocalLightInfo& x);
};
struct cLocalLightCellInit {
    bool mGlobal;            // +0x00
    bool mInUse;             // +0x01
    short mType;             // +0x02
    cSPVector3_s0070_c040 mColour; // +0x04
    float mSize;             // +0x10
    uint8_t mPad14[0x0c];    // +0x14 (alignment padding before the 16-byte member)
    uint32_t mExtra[4];      // +0x20
    uint8_t mCells[0x1a0];   // +0x30
};
struct SlotVecCell {
    int* mpBlocks;          // +0x00
    char pad4[0x14];
    uint32_t mField18;
    uint32_t mField1c;
    uint32_t create(const void* init);   // 0x70c200
};
struct cLightingWorld_s0070_c040 {
    void CreateLocalLightSample(int info);  // 0x0070c410 (cLightingWorld::CreateLocalLightSample)
    void UpdateLocalLightSample(int info);     // 0x707370
    void UpdateLightingInfo(void* cfg);        // 0x70cab0
    void CreateEnvLightSampleEx(void* a, void* b, void* c);
};
// ---- items of slice s0070c040 end

// ---- items of slice s0070ced0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void* __cdecl EAlloc(size_t n, const char* name, int a, unsigned b, const char* file, int line); // 0x00f473a0
void  __cdecl EFree(void* p);                                                                    // 0x00f47380
void* __cdecl GAlloc(size_t n, unsigned align, int a, const char* name, int b, int c, int d, int e); // 0x00f473d0
void __cdecl   InitAtmBuffer(void* p, int zero, int n);          // 0x011e073e
void* __cdecl  ConfigRangeOp1(void*, void*, void*);              // 0x00708ec0
void* __cdecl   MessageServer(void);                             // 0x0067dcc0
struct HM { void Assign(const void*); };                          // 0x0041cb40
struct HD3D { void Op(int); };                                    // 0x00705db0
struct H63c { void Free(); };                                     // 0x0070a070
struct H608 { void Free(); };                                     // 0x00702500
struct H44c { void Free(); };                                     // 0x00706a40
struct HList { void Dtor(); };                                    // 0x00620230
struct HDeque { void Dtor(); };                                   // 0x0070c040
struct HMap { void* Find(void* key); };                           // 0x0074f200
struct HNuke { void Nuke(void* node); };                          // 0x00707690
struct HSmall { void Op(); };                                     // 0x0070a2a0
unsigned __cdecl SlotCreate(void* self, int* out);                // 0x0070cce0
int __cdecl CellListBuild(int a, const float* colour, float size, int b); // 0x00705740
int __cdecl CellListFilter(int a, int b);                         // 0x00705050
void __cdecl NotifyLightAdded(void* info);                        // 0x00705f40
struct HShut { void Shutdown(); };                                // 0x0070a3f0
struct HNode { void Dtor(void* node); };                          // 0x00d0c930
struct MServer {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5(int, int, int);
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
virtual void m10();
    virtual void Unsubscribe(void* handler, int msg, int a3);
};
struct cLightingConfig {
    unsigned char _d[0x144];
    cLightingConfig();
    cLightingConfig(const cLightingConfig&);
    cLightingConfig& operator=(const cLightingConfig&);
    ~cLightingConfig();
};
cLightingConfig* __cdecl ConfigUninitCopy(cLightingConfig* first, cLightingConfig* last, cLightingConfig* dst); // 0x00708500
void             __cdecl ConfigDestruct(cLightingConfig* first, cLightingConfig* last, cLightingConfig* dst);   // 0x00706d60
cLightingConfig* __cdecl ConfigCopyBackward(cLightingConfig* first, cLightingConfig* last, cLightingConfig* dstEnd); // 0x00708f00
cLightingConfig* __cdecl ConfigUninitFillN(cLightingConfig* dst, unsigned n, const cLightingConfig* value, cLightingConfig* extra); // 0x00708480
cLightingConfig* __cdecl ConfigUninitMoveN(cLightingConfig* out, cLightingConfig* first, cLightingConfig* last, const cLightingConfig* value); // 0x00708400
void             __cdecl ConfigFill(cLightingConfig* first, cLightingConfig* last, const cLightingConfig* value);   // 0x0070a270
struct ConfigVec {
    cLightingConfig* mpBegin;     // +0x00
    cLightingConfig* mpEnd;       // +0x04
    cLightingConfig* mpCapacity;  // +0x08

    void DoInsertValue(cLightingConfig* position, const cLightingConfig& value);
    void DoInsertValues(cLightingConfig* position, unsigned n, const cLightingConfig& value);
};
struct cLightingWorld_s0070_ced0 {
    unsigned char _b[0x670];
    cLightingWorld_s0070_ced0(char* debugName);  // 0x0070d2c0 (cLightingWorld::cLightingWorld_s0070_ced0)
    ~cLightingWorld_s0070_ced0();  // 0x0070d2c0 (cLightingWorld::cLightingWorld_s0070_ced0)
};
struct VObj_s0070_ced0 { virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
virtual void f4();
virtual void f5();
virtual void f6();
virtual void f7();
virtual void f8();
virtual void f9();
virtual void f10();
virtual void f11();
              virtual void f12(void*); virtual void f13(); };
struct cLightingManager {
    unsigned char _d[0x1e0];
    cLightingWorld_s0070_ced0* MakeWorld(int owner, int a3, void* arg4);
    char Shutdown();
};
// ---- items of slice s0070ced0 end

// ---- items of slice s0070de90 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl PropertyManager(void);        // 0x0067de30
struct LConfig { unsigned char _d[0x144]; LConfig(); LConfig(const LConfig&); LConfig& operator=(const LConfig&); ~LConfig(); };
struct LConfigVec {
    LConfig* mpBegin; LConfig* mpEnd; LConfig* mpCap;
    void DoInsertValues(LConfig* pos, unsigned n, const LConfig& v); // 0x70d080
    LConfig* Erase(LConfig* first, LConfig* last);                   // 0x70ce80
};
LConfig* __cdecl LConfig_Default(LConfig* out);                      // 0x70dd50
void ReloadLightingStates(void* self);  // 0x70e160
struct MsgReg { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
                virtual void a8(void*, int); virtual void a9(); virtual void a10(); virtual void a11(); };
void __cdecl FillLightingStateFromConfig(void* a, void* b);   // 0x0070aed0
void __cdecl RBTreeInc(void* n);                              // 0x00921580
namespace __equiv_ann1 {
struct LConfig {
    ~LConfig();   // 0x00f47380 (equiv t3)
};
}
// ---- items of slice s0070de90 end

// ---- items of slice s00782860 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_153ae10;
extern float g_16340e0, g_16341d8, g_1634090, g_1634068, g_16340d8, g_1634108, g_16340a0;
#pragma intrinsic(_InterlockedExchangeAdd)
// ---- items of slice s00782860 end

// ---- items of slice s009272c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void  __stdcall EnterCriticalSection(void*);
extern "C" __declspec(dllimport) void  __stdcall LeaveCriticalSection(void*);
struct CriSec {
    uint8_t pad[0x18];
    int     ref;      // +0x18
};
struct cLocalLightInfo_s0092_72c0 {
    uint8_t pad[0x4e4];
    CriSec* mCS;      // +0x4e4
    void Sub(int);    // 0x00926fd0
    void Release(int param);  // @ 0x009276c0
};
// ---- items of slice s009272c0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void LConfigVec_Resize(LConfigVec* self, unsigned n);  // 0x0070e060 (stays in the slice: not this object's)

// @ 0x00705050
int FUN_00705050(int n, E5* p)
{
    int s = 0;
    for (int i = 0; i < n; i++)
        s += (p[i].f4 - p[i].f2) * (p[i].f3 - p[i].f1);
    return s;
}

// @ 0x007050e0
void Big::set_7050e0(int a, int* p)
{
    f18 = a;
    if (p != 0) {
        f28 = p[3];
        f2c = p[4];
        f30 = p[5];
        f1c = p[0];
        f20 = p[1];
        f24 = p[2];
    }
}

// @ 0x00705120
cShaderDataLightingInfo& cShaderDataLightingInfo::operator=(const cShaderDataLightingInfo& s)
{
    mType = s.mType;
    mNumCoeffs = s.mNumCoeffs;
    mDummy = s.mDummy;
    f04 = s.f04;
    f08 = s.f08;
    f0c = s.f0c;
    mCelStrength = s.mCelStrength;
    mBaseLight = s.mBaseLight;
    for (int i = 0; i < 25; i++)
        mCoeffs[i] = s.mCoeffs[i];
    return *this;
}

// @ 0x00705190
void Big50::get_705190(int* out)
{
    out[0] = f48;
    out[1] = f4c;
    out[2] = f50;
}

// @ 0x007051b0
void BigF8::set_7051b0(const Fog98* src)
{ fog = *src; }

// @ 0x007051e0
V32* copy_7051e0(const V32* first, const V32* last, V32* out)
{
    for (; first != last; ++first, ++out) {
        if (out) {
            out->a = _mm_load_ps((const float*)&first->a);
            out->b = _mm_load_ps((const float*)&first->b);
        }
    }
    return out;
}

// @ 0x00705220
V32* copy_backward_705220(const V32* first, const V32* last, V32* out)
{
    while (last != first) {
        --last;
        --out;
        out->a = _mm_load_ps((const float*)&last->a);
        out->b = _mm_load_ps((const float*)&last->b);
    }
    return out;
}

// @ 0x007052e0
int FUN_007052e0(float* v, float param)
{
    if (param < 0.5f)
        return -1;
    float x = v[0], y = v[1], z = v[2];
    float ax = fabsf(x), ay = fabsf(y), az = fabsf(z);
    float r7, r8;
    int face;
    if (az < ax || az < ay) {
        if (ay < ax) {
            r7 = (y / x + 1.0f) * 0.5f;
            r8 = (z / ax + 1.0f) * 0.5f;
            face = 2;
            if (x < 0.0f)
                face = 3;
        } else {
            r7 = (z / y + 1.0f) * 0.5f;
            r8 = (x / ay + 1.0f) * 0.5f;
            face = (y < 0.0f) ? 5 : 4;
        }
    } else {
        r7 = (x / z + 1.0f) * 0.5f;
        r8 = (y / az + 1.0f) * 0.5f;
        face = (z < 0.0f) ? 1 : 0;
    }
    int A = _mm_cvtss_si32(_mm_set_ss(r8 * 32.0f));
    int B = _mm_cvtss_si32(_mm_set_ss(r7 * 32.0f));
    return ((face * 32 - (A >> 5)) + A) * 32 - (B >> 5) + B;
}

// @ 0x00705470
int FUN_00705470(float* v, float param)
{
    if (param == 0.0f)
        return -1;
    float x = v[0], y = v[1], z = v[2];
    if ((x * x + y * y) + z * z < 10.0f)
        return -1;
    float ax = fabsf(x), ay = fabsf(y), az = fabsf(z);
    float r7, r8;
    int face;
    if (az < ax || az < ay) {
        if (ay < ax) {
            r7 = (y / x + 1.0f) * 0.5f;
            r8 = (z / ax + 1.0f) * 0.5f;
            face = 2;
            if (x < 0.0f)
                face = 3;
        } else {
            r7 = (z / y + 1.0f) * 0.5f;
            r8 = (x / ay + 1.0f) * 0.5f;
            face = (y < 0.0f) ? 5 : 4;
        }
    } else {
        r7 = (x / z + 1.0f) * 0.5f;
        r8 = (y / az + 1.0f) * 0.5f;
        face = (z < 0.0f) ? 1 : 0;
    }
    int A = _mm_cvtss_si32(_mm_set_ss(r8 * 16.0f));
    int B = _mm_cvtss_si32(_mm_set_ss(r7 * 16.0f));
    return ((face * 16 - (A >> 4)) + A) * 16 - (B >> 4) + B;
}

// retail inlined the SSE1 ftol helper, which converts with the rounding `cvtss2si`
// rather than the truncating `cvttss2si` cl emits for a plain cast (EA's asm helper).
__forceinline int RoundToInt_705660(float f) { __asm cvtss2si eax, f }

// @ 0x00705660
int FUN_00705660(float* a, float* b, float param)
{
    if (param == 0.0f)
        return -1;
    int u1 = RoundToInt_705660(((a[0] - b[0]) / (b[3] - b[0])) * 16.0f);
    int u2 = RoundToInt_705660(((a[1] - b[1]) / (b[4] - b[1])) * 16.0f);
    int u3 = RoundToInt_705660(((a[2] - b[2]) / (b[5] - b[2])) * 4.0f);
    if ((((u2 | u1) & 0xfffffff3) | u3) & 0xfffffffc)
        return -1;
    return (u3 * 16 + u2) * 16 + u1;
}

// retail's float->int step rounds with cvtss2si and corrects by one (EA's inline ftol);
// cl's plain cast truncates (cvttss2si), so the rounding comes from the asm helper.
__forceinline int RoundInt_705740(float f) { __asm cvtss2si eax, f }
__forceinline int FloorInt_705740(float f)
{
    int r = RoundInt_705740(f);
    if (!(f >= (float)r))       // unordered counts as below, like the original's ucomiss/cmovb
        --r;
    return r;
}
__forceinline int CeilInt_705740(float f)
{
    int r = RoundInt_705740(f);
    if (!((float)r >= f))
        ++r;
    return r;
}

int FUN_006850b0(int, int*, int*);             // rectangle splitter (see slice s00684ee0)

// @ 0x00705740
void FUN_00705740(int n, float* b, float scale, int out)
{
    float bx = b[0], by = b[1], bz = b[2];
    float ax = fabsf(bx), ay = fabsf(by), az = fabsf(bz);
    int   face;
    float u;
    if (az >= ax && az >= ay) {                 // dominant axis: z
        face = (bz >= 0.0f) ? 0 : 1;
        u = (bx / bz + 1.0f) * 0.5f;
    } else if (ay >= ax) {                      // dominant axis: y
        face = (by >= 0.0f) ? 4 : 5;
        u = (bz / by + 1.0f) * 0.5f;
    } else {                                    // dominant axis: x
        face = (bx >= 0.0f) ? 2 : 3;
        u = (by / bx + 1.0f) * 0.5f;
    }
    // retail kept the length and the scaled radius in x87 (double intermediates with
    // /arch:SSE), rounding to float only at the store; the face blend stays in SSE.
    float nf = (float)n;
    double len = sqrt((double)by * by + (double)bz * bz + (double)bx * bx);
    float radius = (float)(nf / len * (double)scale);
    // single-precision SSE steps, rounding after every op like the original's addss/mulss chain
    __m128 tv = _mm_set_ss(u);
    tv = _mm_add_ss(tv, _mm_set_ss(1.0f));
    tv = _mm_mul_ss(tv, _mm_set_ss(0.5f));
    tv = _mm_mul_ss(tv, _mm_set_ss(nf));
    tv = _mm_sub_ss(tv, _mm_set_ss(radius));
    volatile float t = _mm_cvtss_f32(tv);
    int rect[5];
    rect[0] = face;
    rect[1] = FloorInt_705740(t);
    rect[2] = FloorInt_705740(t);
    rect[3] = CeilInt_705740(t);
    rect[4] = CeilInt_705740(t);
    FUN_006850b0(n, rect, (int*)out);    // eax is left holding the split count, like retail
}

// @ 0x00705920
int* W5920::get()
{
    int** p = m10;
    return p ? *p : 0;
}

// EA fast-math helpers: the ratio stays in x87 (the original kept its extended
// intermediates) and the clamp is SSE maxss/minss (a NaN ratio becomes 1.0f).
__forceinline float Ratio_705970(float hi, float t, float d)
{
    float r;
    __asm {
        fld   hi
        fsub  t
        fdiv  d
        fstp  r
    }
    return r;
}
__forceinline float Clamp01_705970(float v)
{
    float one = 1.0f;
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, v
        minss xmm0, one
        movss v, xmm0
    }
    return v;
}

// @ 0x00705970
float W5970::f(int a2, float p3)
{
    (void)a2;
    float d = m10[0x4c] - m10[0x4b];
    if (d < 0.0f)
        return 1.0f;
    if (d == 0.0f) {
        if (p3 < m10[0x4b])
            return 1.0f;
        return 0.0f;
    }
    return Clamp01_705970(Ratio_705970(m10[0x4c], p3, d));
}

// @ 0x00705a20
void W5a20::setAtm(float* v, int n, float* ph)
{
    // the length+sqrt+reciprocal stay in x87 (double intermediates: with /arch:SSE
    // doubles are x87), and `inv` reaches the products rounded to float first.
    double len = (double)v[0] * v[0] + (double)v[1] * v[1] + (double)v[2] * v[2] + 1e-8f;
    volatile float inv = (float)(1.0 / sqrt(len));
    V3 sun = { v[0] * inv, inv * v[1], inv * v[2] };
    mSun = sun;
    nphases = n;
    int cnt = std::min(n, 10);
    for (int i = 0; i < cnt; i++)
        phases[i] = ((const V4*)ph)[i];     // phases are 16-byte records, copied as words
}

// @ 0x00705af0
void* W5af0::find(int key)
{
    int n = (int)((char*)end - (char*)begin) / 0x144;
    for (int i = 0; i < n; i++) {
        int* p = (int*)((char*)begin + i * 0x144);
        if (*p != 0 && *(int*)(*p + 8) == key)
            return p;
    }
    return 0;
}

// @ 0x00705b50
Big5b50* Big5b50::copy(const Big5b50* s)
{
    f0 = s->f0;
    f1 = s->f1;
    f2 = s->f2;
    f4 = s->f4;
    f8 = s->f8;
    fc = s->fc;
    f10 = s->f10;
    m20 = s->m20;
    sub_406540(&coeffs[0], (void*)&s->coeffs[0], 0x10, 0x19, (void*)fn705030);
    return this;
}

// @ 0x00705bb0
S11& S11::operator=(const S11& s)
{
    a = s.a; b = s.b; c = s.c;
    d = s.d; e = s.e; f = s.f; g = s.g; h = s.h;
    i = s.i; j = s.j; k = s.k;
    return *this;
}

// @ 0x00705c00
S7& S7::operator=(const S7& s)
{
    f[0] = s.f[0]; f[1] = s.f[1]; f[2] = s.f[2]; f[3] = s.f[3];
    f[4] = s.f[4]; f[5] = s.f[5]; f[6] = s.f[6];
    return *this;
}

// @ 0x00705c40
void copy_705c40(V32** endp, V32* first, V32* last, V32* dst)
{
    *endp = dst;
    if (first != last) {
        do {
            if (dst) {
                dst->a = _mm_load_ps((const float*)&first->a);
                dst->b = _mm_load_ps((const float*)&first->b);
            }
            ++first;
            ++dst;
        } while (first != last);
        *endp = dst;
    }
    // retail's allocator kept the end-report pointer in eax across the loop and spilled
    // `first` into its argument slot instead; cl's /O2 parks the end report in esi, so the
    // leftover eax callers may read is restored here (single instruction, no logic).
    __asm mov eax, endp
}

// @ 0x00705c80
void FUN_00705c80(void* self, int n)
{ (void)self; (void)n; }

// @ 0x00705db0
void FUN_00705db0(void* self, unsigned n)
{ (void)self; (void)n; }

// @ 0x00705e90
void fill_705e90(__m128* first, __m128* last, const __m128* value)
{
    for (; first != last; ++first)
        *first = *value;
}

// @ 0x00705ec0
void fill_705ec0(__m128* first, unsigned n, const __m128* value)
{
    // the cursor copy makes the entry load `first` land in eax before the count test,
    // which is what retail leaves in eax for n == 0
    __m128* p = first;
    for (unsigned i = n; i != 0; --i) {
        if (p)
            *p = *value;
        ++p;
    }
}

// @ 0x00705ef0
void W5ef0::dtor()
{
    sub_620230((char*)this + 0x2c);
    void* q = buf14;
    if (q != 0 && *(int*)((char*)q - 4) != 0)
        sub_f47380(q);
    q = buf0;
    if (q != 0 && *(int*)((char*)q - 4) != 0)
        sub_f47380(q);
}

// @ 0x00705f40
void FUN_00705f40(void* self, void* a)
{ (void)self; (void)a; }

// @ 0x00706170
void EnvLW::UpdateEnvLightSample(EnvSample* out)
{
    __m128 R, tmp[7], buf180[49], buf490[49], rz[7];
    float zh[8];
    Mat3f m;

    MatrixFromDirection(&out->pos, &m);
    LightCfg* cfg = this->cfg;
    const Vec3f* dir = &sunDir;
    float t0 = (dir->y * m.m[7] + dir->z * m.m[8]) + dir->x * m.m[6];
    float blend = 0.0f;
    float one = 1.0f;
    if (t0 > 0.0f) {
        float x = (t0 - cfg->riseBias) * cfg->riseScale;
        Clamp01(&x, &one);
        for (int i = 0; i < nBands; i++)
            tmp[i] = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(dayCoeffs[i], nightCoeffs[i]), _mm_set1_ps(x)), nightCoeffs[i]);
    } else {
        float x = (-t0 - cfg->setBias) * cfg->setScale;
        Clamp01(&x, &one);
        for (int i = 0; i < nBands; i++)
            tmp[i] = _mm_mul_ps(_mm_set1_ps(1.0f - x), nightCoeffs[i]);
        blend = x;
    }

    Vec3f d;
    d.x = lightPos[0] - out->pos.x;
    d.y = lightPos[1] - out->pos.y;
    d.z = lightPos[2] - out->pos.z;
    float inv = 1.0f / (float)sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
    float c = (dir->z * (d.z * inv) + dir->y * (d.y * inv)) + dir->x * (inv * d.x);
    float c2 = c * c;
    __m128 cc = _mm_set1_ps(c);
    R = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_mul_ps(_mm_set1_ps(g_0162991c), tmp[1]), cc),
                              _mm_mul_ps(_mm_set1_ps(g_016299f4), tmp[0])),
                   _mm_mul_ps(_mm_mul_ps(_mm_set1_ps(g_01629ad8), tmp[2]), _mm_set1_ps(c2 * 3.0f - 1.0f)));
    R = _mm_add_ps(R, _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(_mm_set1_ps(g_01629928), tmp[3]), cc),
                                 _mm_set1_ps(c2 * 5.0f - 3.0f)));

    if (blend < 1.0f) {
        if (out->groundFlag >= 0 && ground != 0 &&
            (out->pos.x * out->pos.x + out->pos.y * out->pos.y) + out->pos.z * out->pos.z > 10.0f) {
            Vec3f d2;
            d2.x = m.m[0] * dir->x + m.m[1] * dir->y + m.m[2] * dir->z;
            d2.y = m.m[3] * dir->x + m.m[4] * dir->y + m.m[5] * dir->z;
            d2.z = m.m[6] * dir->x + m.m[7] * dir->y + m.m[8] * dir->z;
            SH_Accumulate(&d2.x, nBands, tmp, buf490);
            float q[4];
            float* g = ground->Query(q, &out->pos);
            __m128 P = _mm_set_ps(g[3], g[2], g[1], g[0]);
            __m128 va = _mm_mul_ps(_mm_set1_ps(cfg->groundScaleA), P);
            __m128 vb = _mm_mul_ps(_mm_set1_ps(cfg->groundScaleB), P);
            SH_AddGroundBounce(nBands, buf490, &vb, &va);
            SH_Rotate(&m, nBands, buf490, buf180);
        } else {
            SH_Accumulate(&dir->x, nBands, tmp, buf180);
        }
    }

    if (blend > 0.0f) {
        SH_ZonalCoeffs(cfg->zhColor[3], zh);
        for (int i = 0; i < nBands; i++) {
            float z = zh[i];
            float r0 = z * (cfg->zhColor[0] * blend);
            float r1 = z * (blend * cfg->zhColor[1]);
            float r2 = z * (blend * cfg->zhColor[2]);
            float r3 = z * (blend * cfg->zhColor[3]);
            rz[i] = _mm_set_ps(r3, r2, r1, r0);
        }
        if (blend >= 1.0f)
            SH_Accumulate(&m.m[6], nBands, rz, buf180);
        else
            SH_RotateZHAdd(&m.m[6], nBands, rz, buf180);
    }

    SH_ApplyNormalizationConstants(nBands, buf180);
    out->bandsByte = (unsigned char)nOut;
    for (int i = 0; i < nOut; i++)
        out->coeffs[i] = buf180[i];
    out->sunDir = *dir;
    out->blendA = (cfg->baseB - cfg->baseA) * blend + cfg->baseA;
    out->hdr = R;
    ((float*)&out->hdr)[3] = blend;

    LightCfg* c3 = this->cfg;
    if (c3->vecBegin != c3->vecEnd) {
        int cnt = (int)(c3->vecEnd - c3->vecBegin);
        const int* pm = (nOut < cnt) ? &nOut : &cnt;
        for (int i = 0; i < *pm; i++)
            out->coeffs[i] = _mm_add_ps(this->cfg->vecBegin[i], out->coeffs[i]);
    }
}

// @ 0x007067f0
W67f0::~W67f0()
{
    void* p = pBC;
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        sub_f47380(p);
    p = pA8;
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        sub_f47380(p);
    void* q = *(void**)this;
    if (q != 0)
        ((IVoid*)q)->v1();
}

// @ 0x00706840
int W6840::GetLightingWorld(int key)
{
    void* it;
    tree.find(&it, &key);
    if (it != (char*)this + 0x30)
        return *(int*)((char*)it + 0x14);
    return 0;
}

// @ 0x00706870
int W6870::get(unsigned idx)
{
    return m0[idx >> 7] + 0x10 + (idx & 0x7f) * 0x1f0;
}

// @ 0x00706890
int W6890::get(unsigned idx)
{
    return m0[idx >> 7] + 4 + (idx & 0x7f) * 0x38;
}

// @ 0x007068c0
W68c0* W68c0::copyFrom(const W68c0* s)
{
    ((void*(__thiscall*)(void*, const void*))&sub_705b50)(this, s);
    f1c0 = s->f1c0;
    f1c4 = s->f1c4;
    f1c8 = s->f1c8;
    f1cc = s->f1cc;
    f1d0 = s->f1d0;
    return this;
}

// @ 0x00706920
unsigned W6920::next(unsigned idx)
{
    unsigned v = *(unsigned*)((idx & 0x7f) * 0xc4 + (char*)m0[idx >> 7]);
    do {
        if ((v >> 30) & 1)
            return 0x3fffffff;
        ++idx;
        v = *(unsigned*)((idx & 0x7f) * 0xc4 + (char*)m0[idx >> 7]);
    } while ((int)v < 0);
    return idx;
}

// @ 0x00706980
unsigned W6980::next(unsigned idx)
{
    unsigned v = *(unsigned*)((idx & 0x7f) * 0x1f0 + (char*)m0[idx >> 7]);
    do {
        if ((v >> 30) & 1)
            return 0x3fffffff;
        ++idx;
        v = *(unsigned*)((idx & 0x7f) * 0x1f0 + (char*)m0[idx >> 7]);
    } while ((int)v < 0);
    return idx;
}

// @ 0x007069e0
unsigned W69e0::next(unsigned idx)
{
    unsigned v = *(unsigned*)((idx & 0x7f) * 0x1e0 + (char*)m0[idx >> 7]);
    do {
        if ((v >> 30) & 1)
            return 0x3fffffff;
        ++idx;
        v = *(unsigned*)((idx & 0x7f) * 0x1e0 + (char*)m0[idx >> 7]);
    } while ((int)v < 0);
    return idx;
}

// @ 0x00706ab0
Vector4* UninitCopyVec4(Vector4* first, Vector4* last, Vector4* result)
{
    Vector4* p = result;
    for (; first != last; ++first, ++p)
        *(__m128*)p = *(const __m128*)first;
    return p;
}

// @ 0x00706af0
Vec20* Vec20::init(int n, int unused)
{
    (void)unused;
    if (n != 0) {
        void* p = sub_f473d0(n << 5, 0x10, 0, "Graphics", 0, 0,
                             "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xe5);
        b = p;
        e = p;
        c = (char*)p + (n << 5);
    } else {
        b = 0; e = 0; c = 0;
    }
    return this;
}

// @ 0x00706b50
void FUN_00706b50(void* self, void* a)
{ (void)self; (void)a; }

// @ 0x00706c80
E9** FUN_00706c80(E9** out, E9* first, E9* last, E9* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst != 0) {
                dst->a = first->a;
                dst->b = first->b;
                dst->c = first->c;
                dst->d = first->d;
                dst->e = first->e;
                dst->f = first->f;
                dst->g = first->g;
                dst->h = first->h;
                dst->i = first->i;
            }
            ++first;
            ++dst;
        } while (first != last);
        *out = dst;
    }
    return out;
}

// @ 0x00706d00
Vec10* Vec10::init(int n, int unused)
{
    (void)unused;
    if (n != 0) {
        void* p = sub_f473d0(n << 4, 0x10, 0, "Graphics", 0, 0,
                             "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xe5);
        b = p;
        e = p;
        c = (char*)p + (n << 4);
    } else {
        b = 0; e = 0; c = 0;
    }
    return this;
}

// @ 0x00706dd0
void FUN_00706dd0(void* self)
{ (void)self; }

// @ 0x007070d0
void SP::cLightingWorld::UpdateLightPosition(unsigned int id, cSPVector3 const & pos)
{
    int iVar7 = (id & 0x7f) * 0xc4;
    int iVar5 = ((uint32_t)id >> 7) * 4;
    int iVar6 = *(int*)(*(int*)((char*)this + 0x428) + iVar5);
    char* entry = (char*)iVar6 + 4 + iVar7;
    if (entry[0x24] != 0) {
        int cell = *(int*)(*(int*)(entry + 0x28) + 4) * 0x20;
        float* p = (float*)(*(int*)((char*)this + 0x5d4) + cell + 0x10);
        p[0] = pos.x;
        p[1] = pos.y;
        p[2] = pos.z;
        ++*(int*)((char*)this + 0x5fc);
        *(char*)((char*)this + 0x660) = 1;
    }
    int* p20 = *(int**)(entry + 0x20);
    if (p20) {
        if (*(int*)(*(int*)((char*)this + 0x428) + 0x20) == 0) {
            *(int*)(entry + 0x20) = 0;
        } else {
            p20[1] = *(int*)&pos.x;
            p20[2] = *(int*)&pos.y;
            *(uint16_t*)p20 |= 4;
            ++*(uint16_t*)((char*)p20 + 2);
            p20[3] = *(int*)&pos.z;
            void* mgr = *(void**)((char*)this + 0x448);
            ((void(__thiscall*)(void*, int*))(*(void***)mgr)[5])(mgr, p20);
        }
    }
    float* out = (float*)(*(int*)(*(int*)((char*)this + 0x428) + iVar5) + 0x14 + iVar7);
    out[0] = pos.x;
    out[1] = pos.y;
    out[2] = pos.z;
}

// @ 0x00707270
void cLightingWorld::RemoveLightFromList(uint32_t id, int index, int* list)
{
    int iVar3 = *(int*)((char*)this + 0x428);
    char* entry = (char*)(*(int*)(iVar3 + ((uint32_t)id >> 7) * 4) + 4 + (id & 0x7f) * 0xc4);
    uint32_t uVar4 = *(uint32_t*)(list[6] - 4);
    if (uVar4 != id) {
        int* piVar1 = (int*)(*(int*)(entry + 0x28) + index * 8);
        int iVar5 = *piVar1;
        int iVar6 = piVar1[1];
        char* other = (char*)(*(int*)(iVar3 + (uVar4 >> 7) * 4) + 4 + (uVar4 & 0x7f) * 0xc4);
        int count = (*(int*)(other + 0x2c) - *(int*)(other + 0x28)) >> 3;
        for (int i = 0; i < count; ++i) {
            if (*(int*)(*(int*)(other + 0x28) + i * 8) == iVar5)
                *(int*)(*(int*)(other + 0x28) + i * 8 + 4) = iVar6;
        }
        int* dst = (int*)(*(int*)(list[0]) + iVar6 * 0x20);
        int* src = (int*)(list[1] - 0x20);
        dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2]; dst[3] = src[3];
        dst[4] = src[4]; dst[5] = src[5]; dst[6] = src[6]; dst[7] = src[7];
        *(int*)(list[5] + iVar6 * 4) = *(int*)(list[6] - 4);
    }
    list[1] -= 0x20;
    list[6] -= 4;
    ++list[10];
    *(int*)(*(int*)(entry + 0x28) + index * 8) = -1;
    *(int*)(*(int*)(entry + 0x28) + index * 8 + 4) = -1;
}

// @ 0x00707370
void cLightingWorld::UpdateLocalLightSample(int* info)
{
    float* pfVar1 = (float*)(*(int*)(*(int*)((char*)this + 0x608) + ((uint32_t)info[9] >> 7) * 4)
                             + 0x10 + (info[9] & 0x7f) * 0x1e0);
    float* pSrc;
    if (info[10] < 0)
        pSrc = (float*)((char*)this + 0x260);
    else
        pSrc = (float*)(*(int*)(*(int*)((char*)this + 0x594) + ((uint32_t)info[10] >> 7) * 4)
                        + 0x10 + (info[10] & 0x7f) * 0x1f0);
    for (int k = 0; k < 0x70; ++k)
        pfVar1[k] = pSrc[k];
    *((uint8_t*)pfVar1 + 1) = *(uint8_t*)((char*)this + 0x38);
    float fVar7;
    if (*(char*)((char*)this + 0x424) != 0)
        fVar7 = pfVar1[0xb];
    else
        fVar7 = 1.0f;
    fVar7 = *(float*)&info[7] * fVar7;
    if (0.0f < fVar7) {
        int uVar3 = *(int*)((char*)this + 0x5d4);
        if (uVar3 != *(int*)((char*)this + 0x5d8)) {
            Vector4 val;
            val.f[0] = *(float*)&info[3];
            val.f[1] = *(float*)&info[4];
            val.f[2] = *(float*)&info[5];
            val.f[3] = fVar7;
            AddSphereLighting((Vector4*)(pfVar1 + 3), (void*)uVar3,
                              (*(int*)((char*)this + 0x5d8) - uVar3) >> 5, val);
        }
        int li = info[8];
        if (li >= 0) {
            int* piVar2 = (int*)(*(int*)(*(int*)((char*)this + 0x63c) + ((uint32_t)li >> 7) * 4)
                                 + 4 + (li & 0x7f) * 0x38);
            int base = piVar2[0];
            Vector4 val;
            val.f[0] = *(float*)&info[3];
            val.f[1] = *(float*)&info[4];
            val.f[2] = *(float*)&info[5];
            val.f[3] = fVar7;
            AddSphereLighting((Vector4*)(pfVar1 + 3), (void*)base, (piVar2[1] - base) >> 5, val);
        }
    }
    *info = (int)pfVar1;
}

// @ 0x007074e0
void cLightingWorld::CreateEnvLightSample(EnvEntry* pEntry, const cSPVector3_s0070_70d0* pPos, uint32_t celStrength)
{
    pEntry->mPosition = *pPos;
    pEntry->mShaderData = *(cShaderDataLightingInfo_s0070_70d0*)((char*)this + 0x260);
    pEntry->mPad1cc = 0;
    pEntry->mCelStrength = celStrength;
    UpdateEnvLightSample(pEntry);
}

// @ 0x00707540
void SlotVec28::Release(uint32_t idx)
{
    uint32_t* slot = (uint32_t*)((idx & 0x7f) * 0x1f0 + *(int*)((char*)mpBlocks + (idx >> 7) * 4));
    *slot = (*slot & 0xc0000000) | (mField1c & 0x3fffffff) | 0x80000000;
    mField1c = idx;
    if (mField18 == idx)
        mField18 = Next(idx);
}

// @ 0x00707590
void SlotVec28::ReleaseDestroy(uint32_t idx)
{
    uint32_t* slot = (uint32_t*)((idx & 0x7f) * 0x1e0 + *(int*)((char*)mpBlocks + (idx >> 7) * 4));
    *slot = (*slot & 0xc0000000) | (mField1c & 0x3fffffff) | 0x80000000;
    mField1c = idx;
    if (mField18 == idx)
        mField18 = DestroyNext(idx);
}

// @ 0x007075e0
void SlotDeque::DestroyAll(int)
{
    while (mpBegin != mpEnd) {
        if (mField14 == 0) {
            g_pAlloc->Destroy(mpEnd[-1]);
            mpEnd -= 1;
            mField14 = 0x7f;
        } else {
            --mField14;
        }
    }
}

// @ 0x00707660
Vector4* CopyVec4(Vector4* first, Vector4* last, Vector4* result)
{
    for (; first != last; ++first, ++result)
        *(__m128*)result = *(const __m128*)first;
    return result;
}

// @ 0x00707690
void Rbtree::DoNukeSubtree(NukeNode* first, NukeNode* last)
{
    for (; first < last; first = (NukeNode*)((char*)first + 0x144)) {
        if (first->mpBC && ((int*)first->mpBC)[-1] != 0)
            EastlFree(first->mpBC);
        if (first->mpA8 && ((int*)first->mpA8)[-1] != 0)
            EastlFree(first->mpA8);
        if (first->mpObj)
            first->mpObj->slot1();
    }
}

// @ 0x007076f0
Vector4* CopyBackVec4(Vector4* first, Vector4* last, Vector4* resultEnd)
{
    while (last != first)
        *(__m128*)--resultEnd = *(const __m128*)--last;
    return resultEnd;
}

// @ 0x00707720
void Buf28::Free()
{
    void* p = mpBlock;
    if (p && p != mpDefault)
        EastlFree(p);
}

// @ 0x00707740
void cLightingWorld::GetLocalShaderData(void* e)
{
    int idx = *(int*)((char*)e + 0x28);
    if (idx >= 0)
        *(void**)e = (void*)(*(int*)(*(int*)((char*)this + 0x594) + ((uint32_t)idx >> 7) * 4)
                             + 0x10 + (idx & 0x7f) * 0x1f0);
    else
        *(void**)e = (char*)this + 0x260;
    ((SlotVec28*)((char*)this + 0x608))->ReleaseDestroy(*(uint32_t*)((char*)e + 0x24));
    *(int*)((char*)e + 0x24) = -1;
}

// @ 0x00707790
void cLightingWorld_s0070_8100::ReleaseLocalCache(void* e)
{
    int idx = *(int*)((char*)e + 0x28);
    char* p = (char*)(*(int*)(*(int*)((char*)this + 0x594) + ((uint32_t)idx >> 7) * 4)
                      + 0x10 + (idx & 0x7f) * 0x1f0);
    if (--*(int*)(p + 0x1cc) == 0) {
        int g = *(int*)(p + 0x1d0);
        if (g >= 0) {
            int* grid = *(int**)((char*)this + 0x5b4);
            grid[g] = -1;
        }
        ((SlotVec28*)((char*)this + 0x594))->Release(*(uint32_t*)((char*)e + 0x28));
    }
    *(int*)((char*)e + 0x28) = -1;
}

// @ 0x007077f0
Vec4& Vec4::operator=(const Vec4& x)
{
    if (this != &x) {
        const Vector4* first = x.mpBegin;
        const Vector4* last = x.mpEnd;
        const uint32_t n = (uint32_t)(last - first);
        if (n > (uint32_t)(mpCapacity - mpBegin)) {
            Vector4* pNewData = DoRealloc(n, first, last);
            if (mpBegin && ((int*)mpBegin)[-1] != 0)
                EastlFree(mpBegin);
            mpBegin = pNewData;
            mpEnd = pNewData + n;
            mpCapacity = mpEnd;
        } else if (n <= (uint32_t)(mpEnd - mpBegin)) {
            CopyVec4((Vector4*)first, (Vector4*)last, mpBegin);
            mpEnd = mpBegin + n;
        } else {
            const Vector4* position = first + (mpEnd - mpBegin);
            CopyVec4((Vector4*)first, (Vector4*)position, mpBegin);
            UninitCopyVec4((Vector4*)position, (Vector4*)last, mpEnd);
            mpEnd = mpBegin + n;
        }
    }
    return *this;
}

// @ 0x00707a00
void Vec4::DoInsertValues(Vector4* position, Vector4* source)
{
    Vector4* pEnd = mpEnd;
    for (; source != pEnd; ++source, ++position)
        *(__m128*)position = *(const __m128*)source;
    mpEnd += position - source;
}

// @ 0x00707a50
void Vec32::DoInsertValue(V32_s0070_70d0* position, const V32_s0070_70d0* value)
{
    V32_s0070_70d0* pEnd = mpEnd;
    if (pEnd != mpCapacity) {
        const V32_s0070_70d0* v = value;
        if (v >= position && v < pEnd)
            v = (const V32_s0070_70d0*)((const char*)v + 0x20);
        if (pEnd)
            *pEnd = pEnd[-1];
        CopyBack32(position, pEnd - 1, pEnd);
        *position = *v;
        ++mpEnd;
    } else {
        uint32_t n = (uint32_t)(pEnd - mpBegin);
        if (n == 0) n = 1;
        else n *= 2;
        V32_s0070_70d0* pNewData = n ? (V32_s0070_70d0*)EastlAlloc8(n * 0x20, 0x10, 0, "Graphics", 0, 0,
                          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xe5)
                          : 0;
        V32_s0070_70d0* q = UninitCopy32(mpBegin, position, pNewData);
        if (q)
            *q = *value;
        V32_s0070_70d0* q2 = UninitCopy32(position, mpEnd, q + 1);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            EastlFree(mpBegin);
        mpCapacity = pNewData + n;
        mpBegin = pNewData;
        mpEnd = q2;
    }
}

// @ 0x00707b70
void Vec4::InsertValuesAt(Vector4* position, uint32_t n, const Vector4* value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const Vector4 temp = *value;
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            if (n < nExtra) {
                UninitCopyVec4(mpEnd - n, mpEnd, mpEnd);
                CopyBackVec4(position, mpEnd - n, mpEnd);
                FillVec4(position, position + n, &temp);
            } else {
                UninitFillVec4(mpEnd, n - nExtra, &temp);
                UninitCopyVec4(position, mpEnd, mpEnd + (n - nExtra));
                FillVec4(position, mpEnd, &temp);
            }
            mpEnd += n;
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        uint32_t nGrowSize = nPrevSize * 2;
        if (nPrevSize == 0) nGrowSize = 1;
        uint32_t nNewSize = nPrevSize + n;
        if (nNewSize < nGrowSize) nNewSize = nGrowSize;
        Vector4* pNewData = nNewSize ? (Vector4*)EastlAlloc8(nNewSize * 0x10, 0x10, 0, "Graphics", 0, 0,
                                 "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xe5)
                              : 0;
        Vector4* pNewEnd = UninitCopyVec4(mpBegin, position, pNewData);
        UninitFillVec4(pNewEnd, n, value);
        pNewEnd = UninitCopyVec4(position, mpEnd, pNewEnd + n);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            EastlFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00707d10
void Vec8::DoInsertValues(char* position, uint32_t n, const void* value)
{
    if (n <= (uint32_t)((mpCapacity - mpEnd) >> 3)) {
        if (n != 0) {
            char* pEnd = mpEnd;
            const char* v = (const char*)value;
            const uint32_t nExtra = (uint32_t)((pEnd - position) >> 3);
            if (n < nExtra) {
                MoveElems8(pEnd, pEnd - n * 8, n * 8);
                CopyElems8(position, pEnd - n * 8, pEnd);
                UninitFill8(position, n, v);
            } else {
                UninitFill8(pEnd, n - nExtra, v);
                UninitCopy8(position, pEnd, pEnd + (n - nExtra) * 8);
                CopyAssign8(position, pEnd, (char*)v);
            }
            mpEnd += n * 8;
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)((mpEnd - mpBegin) >> 3);
        uint32_t nGrowSize = nPrevSize * 2;
        if (nPrevSize == 0) nGrowSize = 1;
        uint32_t nNewSize = nPrevSize + n;
        if (nNewSize < nGrowSize) nNewSize = nGrowSize;
        char* pNewData = nNewSize
            ? (char*)EastlAlloc6(nNewSize * 8, "Graphics", 0, 0,
                                 "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
            : 0;
        char* pNewEnd = (char*)UninitCopy8(mpBegin, position, pNewData);
        UninitFill8(pNewEnd, n, value);
        pNewEnd = (char*)UninitCopy8(position, mpEnd, pNewEnd + n * 8);
        if (mpBegin && mpBegin != mpInline)
            EastlFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize * 8;
    }
}

// @ 0x00707ed0
void SlotVecC4::DestroyEntry(uint32_t idx)
{
    uint32_t* slot = (uint32_t*)((idx & 0x7f) * 0xc4 + *(int*)((char*)mpBlocks + (idx >> 7) * 4));
    void* p = *(void**)((char*)slot + 0x2c);
    if (p && p != *(void**)((char*)slot + 0x3c))
        EastlFree(p);
    *slot = (mField1c & 0x3fffffff) | (*slot & 0xc0000000) | 0x80000000;
    mField1c = idx;
    if (mField18 == idx)
        mField18 = Next(idx);
}

// @ 0x00707f40
void Deque38::PopDestroy()
{
    Elem38* elem = (Elem38*)(*(int*)((char*)mpData - 4) + mIndex14 * 0x38);
    if (((elem->mTag >> 31) & 1) == 0) {
        elem->mList.~IntrusiveList();
        if (elem->mp18 && ((int*)elem->mp18)[-1] != 0)
            EastlFree(elem->mp18);
        if (elem->mp4 && ((int*)elem->mp4)[-1] != 0)
            EastlFree(elem->mp4);
    }
    if (mIndex14 == 0) {
        g_pAlloc->Destroy((void*)*(int*)((char*)mpData - 4));
        mpData = (char*)mpData - 4;
        mIndex14 = 0x7f;
        return;
    }
    --mIndex14;
}

// @ 0x00707fd0
VecSHO& VecSHO::operator=(const VecSHO& x)
{
    if (this != &x) {
        const uint32_t n = (uint32_t)((x.mpEnd - x.mpBegin) / 0x24);
        if (n > (uint32_t)((mpCapacity - mpBegin) / 0x24)) {
            SHObject* pNewData = DoRealloc(n, x.mpBegin, x.mpEnd);
            if (mpBegin && ((int*)mpBegin)[-1] != 0)
                EastlFree(mpBegin);
            mpBegin = pNewData;
            mpEnd = pNewData + n;
            mpCapacity = mpEnd;
        } else {
            const uint32_t nSize = (uint32_t)((mpEnd - mpBegin) / 0x24);
            if (n <= nSize) {
                CopySHO(x.mpBegin, x.mpEnd, mpBegin);
                mpEnd = mpBegin + n;
            } else {
                CopySHO(x.mpBegin, x.mpBegin + nSize, mpBegin);
                SHObject* out = x.mpEnd;
                UninitCopySHO5(&out, x.mpBegin + nSize, mpEnd, mpEnd, x.mpEnd);
                mpEnd = mpBegin + n;
            }
        }
    }
    return *this;
}

// @ 0x00708100
void* ConstructRange(void* self, void* src)
{
    (void)self;
    (void)src;
    return self;
}

// @ 0x00708340
void VecCell::assign(const CellInfo_s0070_8100* first, const CellInfo_s0070_8100* last, int)
{
    const uint32_t n = (uint32_t)(last - first);
    CellInfo_s0070_8100* p = mpBegin;
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        CellInfo_s0070_8100* pNew = DoRealloc(n, first, last);
        if (mpBegin && mpBegin != mpInline)
            EastlFree(mpBegin);
        mpBegin = pNew;
        mpCapacity = pNew + n;
        mpEnd = pNew + n;
        return;
    }
    if (n <= (uint32_t)(mpEnd - p)) {
        for (; first != last; ++first, ++p)
            *p = *first;
        mpEnd = p;
        return;
    }
    const CellInfo_s0070_8100* mid = first + (mpEnd - mpBegin);
    for (; first != mid; ++first, ++p)
        *p = *first;
    CellInfo_s0070_8100* newEnd;
    MoveRange5((void**)&newEnd, mid, last, mpEnd, last);
    mpEnd = newEnd;
}

// @ 0x00708500
void* CopyConstructRange(void* first, void* last, void* dst)
{
    (void)first;
    (void)last;
    return dst;
}

// @ 0x007085a0
void cLightingWorld_s0070_8100::RemoveLight(uint32_t id)
{
    int iVar7 = (id & 0x7f) * 0xc4;
    int iVar1 = *(int*)(*(int*)((char*)this + 0x428) + ((uint32_t)id >> 7) * 4);
    char* entry = (char*)iVar1 + iVar7 + 4;
    if (*(char*)(iVar1 + 0x28 + iVar7) != 0) {
        char* cells = (char*)this + 0x5d4;
        RemoveLightFromList(id, 0, (int*)cells);
        if (*(int*)cells == *(int*)((char*)this + 0x5d8)) {
            char* head = (char*)this + 0x600;
            void* node = *(void**)((char*)this + 0x600);
            void* end = *(void**)head ? (void*)(*(int*)((char*)this + 0x600) - 4) : 0;
            void* tail = *(void**)head ? (void*)(head - 4) : 0;
            (void)tail;
            void* last = *(void**)((char*)this + 0x600);
            void* stop = last ? (void*)(*(int*)((char*)this + 0x600) - 4) : 0;
            while (node != stop) {
                char* e = (char*)node;
                int cacheId = *(int*)(e + 0x28);
                if (cacheId >= 0)
                    *(void**)e = (void*)(*(int*)(*(int*)((char*)this + 0x594) + ((uint32_t)cacheId >> 7) * 4)
                                         + 0x10 + (cacheId & 0x7f) * 0x1f0);
                else
                    *(void**)e = (char*)this + 0x260;
                ((SlotVec28*)((char*)this + 0x608))->ReleaseDestroy(*(uint32_t*)(e + 0x24));
                *(int*)(e + 0x24) = -1;
                int* nx = *(int**)(e + 4);
                node = nx ? (void*)(nx - 1) : 0;
                if (node == end)
                    break;
            }
            *(char*)((char*)this + 0x660) = 1;
        }
    }
    --*(int*)((char*)this + 0x5d0);
    int* mgr = *(int**)((char*)this + 0x448);
    if (mgr) {
        int v = *(int*)(entry + 0x20);
        if (v)
            ((void(__thiscall*)(void*, int))(*(void***)mgr)[6])(mgr, v);
    }
    ((SlotVecC4*)((char*)this + 0x428))->DestroyEntry(id);
}

// @ 0x00708710
void cLightingWorld_s0070_8100::DestroyLightingInfo(void* e)
{
    if (e == (char*)this + 0x420)
        return;
    if (*(int*)((char*)e + 0x28) >= 0)
        ReleaseLocalCache(e);
    if (*(int*)((char*)e + 0x24) >= 0) {
        ((SlotVec28*)((char*)this + 0x608))->ReleaseDestroy(*(uint32_t*)((char*)e + 0x24));
        *(int*)((char*)e + 0x24) = -1;
    }
    *(int*)((char*)e + 0x20) = -1;
    int* next = *(int**)((char*)e + 8);
    int prev = *(int*)((char*)e + 4);
    *next = prev;
    *(int**)(prev + 4) = next;
    *(int*)((char*)e + 4) = 0;
    *(int*)((char*)e + 8) = 0;
    LightFreeVec* freeList = (LightFreeVec*)((char*)this + 0x478);
    void** p = freeList->mpEnd;
    if (p < freeList->mpCapacity) {
        freeList->mpEnd = p + 1;
        if (p) {
            *p = e;
            return;
        }
    } else {
        freeList->DoInsertValue(p, e);
    }
}

// @ 0x007087a0
void ClearVec::clear()
{
    int n = (int)(mpEnd - mpBegin);
    for (int i = 0; i < n; ++i)
        ReleaseElem(mpBegin[i]);
    memcpy(mpBegin, mpEnd, 0);
    mpEnd -= mpEnd - mpBegin;
    if (mpExtra) {
        ReleaseElem(mpExtra);
        mpExtra = 0;
    }
}

// @ 0x00708810
void cLightingWorld_s0070_8100::AddLocalSample(uint32_t id, int index, SampleVec* vec)
{
    char* entry = (char*)(*(int*)(*(int*)((char*)this + 0x428) + ((uint32_t)id >> 7) * 4))
                  + 4 + (id & 0x7f) * 0xc4;
    *(int*)(*(int*)(entry + 0x28) + 4 + index * 8) =
        (int)(((char*)vec->mpEnd - (char*)vec->mpBegin) >> 5);
    V32_s0070_8100* p = vec->mpEnd;
    if (p < vec->mpCapacity) {
        vec->mpEnd = p + 1;
    } else {
        V32_s0070_8100 tmp;
        vec->DoInsertValue(p, &tmp);
    }
    V32_s0070_8100* dst = (V32_s0070_8100*)((char*)vec->mpEnd - 0x20);
    const V32_s0070_8100* src = (const V32_s0070_8100*)entry;
    dst->u[0] = src->u[0];
    dst->u[1] = src->u[1];
    dst->u[2] = src->u[2];
    dst->u[3] = src->u[7];
    dst->u[4] = src->u[4];
    dst->u[5] = src->u[5];
    dst->u[6] = src->u[6];
    dst->u[7] = src->u[3];
    uint32_t* ip = vec->mIds.mpEnd;
    if (ip < vec->mIds.mpCapacity) {
        vec->mIds.mpEnd = ip + 1;
        if (ip)
            *ip = id;
    } else {
        uint32_t local = id;
        vec->mIds.DoInsertValue(ip, local);
    }
    ++vec->mCount;
}

// @ 0x00708900
void DestroyLightingManager(int* self)
{
    (void)self;
}

// @ 0x007089a0
cLightingConfig_s0070_8100& cLightingConfig_s0070_8100::operator=(const cLightingConfig_s0070_8100& x)
{
    if (this != &x) {
        const char* s = (const char*)&x;
        char* d = (char*)this;
        for (int i = 0; i < 0xa4; ++i) d[i] = s[i];
        d[0xa4] = s[0xa4];
        release(d + 0x18);
        for (int i = 0xb0; i < 0x13c; ++i) d[i] = s[i];
    }
    return *this;
}

// @ 0x00708d90
void Vec8b::resize(uint32_t n)
{
    const uint32_t size = (uint32_t)((mpEnd - mpBegin) >> 3);
    if (n > size) {
        uint64_t z = 0;
        DoInsertValues(mpEnd, n - size, &z);
    } else {
        Erase(mpBegin + n * 8, mpEnd);
    }
}

// @ 0x00708df0
void* ConstructVec(int* self, int a, int b)
{
    (void)a;
    (void)b;
    return self;
}

// @ 0x00708e60
void Vec16::resize(uint32_t n)
{
    const uint32_t size = (uint32_t)((mpEnd - mpBegin) >> 4);
    if (n > size) {
        uint32_t buf[4];
        DoInsertValues16(mpEnd, n - size, buf);
        return;
    }
    char* mid = mpBegin + n * 0x10;
    Copy16(mpEnd, mpEnd, mid);
    mpEnd -= ((uint32_t)(mpEnd - mid) >> 4) * 0x10;
}

// @ 0x007094c0
void cLightingWorld_s0070_8f40::ApplyConfig()
{
    PreUpdate();
    Config* cfg = mCfg;
    if (!cfg) {
        mAmbient[0] = g_defAmbient[0] * 0.1f;
        mAmbient[1] = g_defAmbient[1] * 0.1f;
        mAmbient[2] = g_defAmbient[2] * 0.1f;
        mDirLights.push_back(PackDirLight(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 0.7f, 1.0f)));
        mDirLights.push_back(PackDirLight(Vec3(-1.0f, -1.0f, -1.0f), Vec3(0.7f, 1.0f, 1.0f)));
    } else {
        ((uint32_t*)mAmbient)[0] = g_cfgAmbient[0];
        ((uint32_t*)mAmbient)[1] = g_cfgAmbient[1];
        ((uint32_t*)mAmbient)[2] = g_cfgAmbient[2];
        if (Bit(cfg->mFlags, 4)) {
            ((uint32_t*)mAmbient)[0] = cfg->mAmbient[0];
            ((uint32_t*)mAmbient)[1] = cfg->mAmbient[1];
            ((uint32_t*)mAmbient)[2] = cfg->mAmbient[2];
        }
        if (Bit(cfg->mFlags, 5)) {
            float a = cfg->m84;
            float vx = cfg->vx, vy = cfg->vy, vz = cfg->vz;
            float p = cfg->m7c * a;
            float q = a * cfg->m80;
            float last = cfg->m88;
            float r = a * cfg->m78;
            if (mFlags & 2) {
                float nx = (m[3] * vy + m[6] * vz) + m[0] * vx;
                float ny = (m[1] * vx + m[4] * vy) + m[7] * vz;
                float nz = (m[2] * vx + m[5] * vy) + m[8] * vz;
                vx = nx;
                vy = ny;
                vz = nz;
            }
            float s = mScale;
            mSunLight = PackSunLight(Vec3(s * vx + mPos[0], mPos[1] + vy * s, mPos[2] + s * vz), Vec3(r, p, q), last);
        }
        {
            unsigned i = 0;
            unsigned mask = 1;
            for (int off = 0; off < 0x70; off += 0x1c, i++, mask = (mask << 1) | (mask >> 31)) {
                if (i < 7 && FlagSet(mCfg->mFlags, mask)) {
                    Config* c = mCfg;
                    float n1 = -*(float*)((char*)c + off + 0x18);
                    float n2 = -*(float*)((char*)c + off + 0x1c);
                    float n3 = -*(float*)((char*)c + off + 0x20);
                    float d1 = *(float*)((char*)c + off + 0xc) - mAmbient[1];
                    float d2 = *(float*)((char*)c + off + 0x10) - mAmbient[2];
                    float d0 = *(float*)((char*)c + off + 8) - mAmbient[0];
                    float k = *(float*)((char*)c + off + 0x14);
                    float t = k * d1;
                    float u = k * d0;
                    float v = k * d2;
                    float ox = n1, oy = n2, oz = n3;
                    if (mFlags & 2) {
                        ox = (m[3] * n2 + m[6] * n3) + n1 * m[0];
                        oy = (m[1] * n1 + m[4] * n2) + m[7] * n3;
                        oz = (m[2] * n1 + m[5] * n2) + m[8] * n3;
                    }
                    mDirLights.push_back(PackDirLight(Vec3(ox, oy, oz), Vec3(u, t, v)));
                }
            }
        }
        cfg = mCfg;
        mDirty = mEnabled;
        mEnabled = cfg->mScale > 0.0f;
        cfg = mCfg;
        if (cfg->mAddBegin == cfg->mAddEnd) {
            mInfo.mNumBands = 0;
        } else {
            int count = (int)(cfg->mAddEnd - cfg->mAddBegin);
            int limit = 25;
            const int& n = MinRef(count, limit);
            mInfo.mNumBands = (unsigned char)n;
            for (int i = 0; i < mInfo.mNumBands; i++)
                mInfo.mCoeffs[i] = mCfg->mAddBegin[i];
        }
        {
            Vector4_s0070_8f40 zero(0.0f, 0.0f, 0.0f, 0.0f);
            for (int i = mInfo.mNumBands; i < 25; i++)
                mInfo.mCoeffs[i] = zero;
        }
        mInfo.mIntensity = mCfg->mIntensity;
    }

    cfg = mCfg;
    if (cfg && mEnabled && (cfg->mEffectA > 0.0f || cfg->mEffectB > 0.0f)) {
        IEffect* effect = SP::EffectsManager()->GetEffect(0x16f280b, 0);
        IEffect* old = mEffect;
        if (effect != old) {
            if (effect)
                effect->AddRef();
            mEffect = effect;
            if (old)
                old->Release();
        }
        if (mEffect)
            mEffectValue = mEffect->GetValue();
    } else {
        IEffect* old = mEffect;
        if (old) {
            mEffect = 0;
            old->Release();
        }
    }
    if (mEnabled) {
        mEnvFlag = true;
        mField18 = 2;
    }
    {
        int limit = mEnvCache.Capacity();
        for (int i = 0; i < limit; i++) {
            if ((unsigned)i < (unsigned)mEnvCache.Capacity()) {
                if (!Bit(*(unsigned*)mEnvCache.Entry(i), 31))
                    UpdateEnvLightSample(mEnvCache.Entry(i) + 0x10);
            }
        }
    }
    {
        int limit = mLocalCache.Capacity();
        for (int i = 0; i < limit; i++) {
            if ((unsigned)i < (unsigned)mLocalCache.Capacity()) {
                if (!Bit(*(unsigned*)mLocalCache.Entry(i), 31))
                    UpdateLocalLightSample(*(int*)(mLocalCache.Entry(i) + 0x1d0));
            }
        }
    }
    if (mEnvFlag)
        SP::MessageServer()->Post(0x2495f34, 0, 0);
}

// @ 0x00709c40
void LightingManager::Init()
{
    char* p = (char*)this;
    int z = 0;
    *(void**)(p + 4) = &g_lm_vtbl0;
    *(void**)(p + 8) = &g_lm_vtbl1;
    *(int*)(p + 0xc) = z;
    *(void**)(p) = &g_lm_vtbl2;
    *(void**)(p + 4) = &g_lm_vtbl3;
    *(void**)(p + 8) = &g_lm_vtbl4;
    *(int*)(p + 0x10) = 4;
    *(int*)(p + 0x14) = 0x10;
    *(int*)(p + 0x18) = z;
    *(int*)(p + 0x1c) = z;
    *(int*)(p + 0x20) = z;
    *(int*)(p + 0x34) = z;
    *(int*)(p + 0x38) = z;
    *(int*)(p + 0x3c) = z;
    void** q = (void**)(p + 0x30);
    *q = q;
    *(void**)(p + 0x34) = q;
    *(int*)(p + 0x38) = z;
    *(char*)(p + 0x3c) = (char)z;
    *(int*)(p + 0x40) = z;
    *(float*)(p + 0x48) = g_lm_f0;
    *(float*)(p + 0x4c) = g_lm_f1;
    *(float*)(p + 0x50) = g_lm_f2;
    *(int*)(p + 0x54) = z;
}

// @ 0x00709cf0
bool cLightingWorld_s0070_9cf0::LoadProperties()
{
    return true;
}

// @ 0x0070a070
void cLightingWorld_s0070_9cf0::DestroySlotDequeEh()
{
}

// @ 0x0070a0d0
void cLightingWorld_s0070_9cf0::ConstructSampleVec(int)
{
}

// @ 0x0070a130
void cLightingWorld_s0070_9cf0::CopyConfig(int* self)
{
    (void)self;
}

// @ 0x0070a1f0
void ClearDeque::ClearImpl(int)
{
    while (mpBegin != mpEnd) {
        char* e = (char*)(mField14 * 0xc4 + *(int*)((char*)mpEnd - 4));
        if (((*(int*)e >> 31) & 1) == 0) {
            void* x = *(void**)(e + 0x2c);
            if (x && x != *(void**)(e + 0x3c))
                EastlFree(x);
        }
        if (mField14 == 0) {
            g_pAlloc_s0070_9cf0->Destroy(*(void**)((char*)mpEnd - 4));
            mpEnd -= 1;
            mField14 = 0x7f;
        } else {
            --mField14;
        }
    }
}

// @ 0x0070a2a0
void cLightingWorld_s0070_9cf0::ConfigFromProperties(int* self)
{
    (void)self;
}

// @ 0x0070a3f0
void cLightingWorld_s0070_9cf0::Shutdown()
{
}

// @ 0x0070a560
void cLightingWorld_s0070_9cf0::SetLightingState(void* state)
{
    if (*(void**)((char*)this + 0x14) != state) {
        if (state) {
            void* v = ((StateSource*)*(void**)((char*)this + 0xc))->Create(state);
            *(void**)((char*)this + 0x10) = v;
            _ReadWriteBarrier();
            *(void**)((char*)this + 0x14) = state;
            Update();
        } else {
            *(void**)((char*)this + 0x10) = 0;
            *(void**)((char*)this + 0x14) = state;
            Update();
        }
    }
}

// @ 0x0070a5b0
void cLightingWorld_s0070_a5b0::Update(uint32_t param)
{
    if (!mCfg)
        return;

    PropertyList* props = sAppProperties;
    if (props) {
        Property* prop;
        if (props->GetProperty(0x641a468, prop) && prop->mType == 9) {
            int bands = *prop->GetInt();
            mNumBands = bands;
            mNumCoeffs = bands * bands;
        }
        if (props->GetProperty(0x641a467, prop) && prop->mType == 9)
            mBudget = *prop->GetInt();
    }

    Config_s0070_a5b0* cfg = mCfg;
    if (cfg) {
        if (mEnabled) {
            IEffect* effect = 0;
            int effectValue = 0;
            if (cfg->mEffectA > 0.0f || cfg->mEffectB > 0.0f) {
                effect = SP::EffectsManager()->GetEffect(0x16f280b, 0);
                if (effect)
                    effectValue = effect->GetValue();
            }
            if (mEffect.mp != effect || mEffectValue != effectValue) {
                mEffect = effect;
                mEffectValue = effectValue;
                mEnvRescan = true;
            }
        }
    }

    if (mEnabled) {
        FixedVec4 dirs(mWorld->mNumLights + 1);
        for (int i = 0; i < mWorld->mNumLights; i++) {
            dirs[i] = mWorld->mLights[i];
            dirs[i] *= mCfg->mLightScale;
        }

        Vector4_s0070_a5b0 work[56];
        Vector4_s0070_a5b0* zh = work;
        Vector4_s0070_a5b0* sh = work + 7;
        for (int j = 0; j < 3; j++) {
            dirs[mWorld->mNumLights] = mCfg->mColors[j];
            CalcAtmosphereZH(mWorld->mNumLights + 1, &dirs[0], mNumBands, zh);

            PropertyList* pl = mCfg->mProps;
            if (pl) {
                Property* prop;
                if (pl->GetProperty(0x2478ee3, prop) && prop->mType == 0xd) {
                    float sat = PropertyFloat(prop);
                    for (int k = 0; k < mNumBands; k++) {
                        zh[k] = Desaturate(zh[k], sat);
                    }
                }
            }
            for (int k = 0; k < mNumBands; k++) {
                __m128 scale = _mm_set1_ps(mCfg->mScale);
                zh[k].m = _mm_mul_ps(scale, zh[k].m);
            }

            bool changed = false;
            for (int k = 0; k < mNumBands; k++) {
                if (!(mZH[j][k] == zh[k])) {
                    mDirty = true;
                    break;
                }
            }
            if (mDirty) {
                for (int k = 0; k < mNumBands; k++)
                    mZH[j][k] = zh[k];
            }
        }

        World* world = mWorld;
        Vec3_s0070_a5b0& sun = mSun;
        float d = sun.z * world->mDir.z + sun.y * world->mDir.y + world->mDir.x * sun.x;
        if (mCfg->mSunThreshold > d) {
            mDirty = true;
            sun = world->mDir;
        }

        cfg = mCfg;
        if (cfg->mEffectA > 0.0f || cfg->mEffectB > 0.0f) {
            IEffect* effect = SP::EffectsManager()->GetEffect(0x16f280b, 0);
            if (mEffect.mp != effect) {
                IEffect* old = mEffect.mp;
                if (effect != old) {
                    if (effect)
                        effect->AddRef();
                    mEffect.mp = effect;
                    if (old)
                        old->Release();
                }
                mDirty = true;
            }
        }

        SHAccumulate(&sun.x, mNumBands, &mZH[0][0], sh);
        ApplyNormalizationConstants(mNumBands, sh + 1);
        mInfo.mNumBands = (unsigned char)mNumCoeffs;
        for (int i = 0; i < mNumCoeffs; i++)
            mInfo.mCoeffs[i] = sh[i];

        cfg = mCfg;
        if (cfg->mAddBegin != cfg->mAddEnd) {
            int count = (int)(cfg->mAddEnd - cfg->mAddBegin);
            int limit = 25;
            const int& n = (limit < count) ? limit : count;
            for (int i = 0; i < n; i++)
                mInfo.mCoeffs[i].m = _mm_add_ps(mCfg->mAddBegin[i].m, mInfo.mCoeffs[i].m);
        }
        mInfo.mDir = sun;
        mInfo.mAmbient = mInfo.mCoeffs[0];
        mActive = &mInfo;
    } else {
        if (mInfo.mNumBands > 0)
            mActive = &mInfo;
        else
            mActive = 0;
    }

    if (mDirty) {
        if (mEnabled) {
            mEnvRescan = true;
        } else {
            for (DequeWalker it(mFirst); it.mpCur != mLast.mpCur; it.Next())
                *(LightingInfo_s0070_a5b0**)it.mpCur = &mInfo;
            mEnvIdx = -1;
        }
        mDirty = false;
    }

    if (mEnvIdx < 0) {
        if (mEnvRescan) {
            if (mEnvCache.mFirst != 0x3fffffff)
                mEnvIdx = mEnvCache.mFirst;
            mEnvRescan = false;
        }
        if (mEnvIdx < 0)
            goto localPass;
    }
    if (mEffect.mp)
        mEffect.mp->Lock();
    {
        int limit = mEnvCache.Capacity();
        int budget = mBudget;
        if (mEnvIdx < limit) {
            while (mEnvIdx < limit && budget > 0) {
                if ((unsigned)mEnvIdx < (unsigned)mEnvCache.Capacity()) {
                    if (!Bit(*(unsigned*)mEnvCache.Entry(mEnvIdx), 31)) {
                        UpdateEnvLightSample(mEnvCache.Entry(mEnvIdx) + 0x10);
                        budget--;
                    }
                }
                mEnvIdx++;
            }
        }
        if (mEnvIdx >= limit) {
            mEnvIdx = -1;
            if (mLocalCount > 0)
                mLocalRescan = true;
        }
    }
    if (mEffect.mp)
        mEffect.mp->Unlock();

localPass:
    if (mLocalIdx < 0 && mLocalRescan) {
        if (mLocalCache.mFirst != 0x3fffffff)
            mLocalIdx = mLocalCache.mFirst;
        mLocalRescan = false;
    }
    if (mLocalIdx >= 0) {
        int limit = mLocalCache.Capacity();
        int budget = mBudget;
        if (mLocalIdx < limit) {
            while (mLocalIdx < limit && budget > 0) {
                if ((unsigned)mLocalIdx < (unsigned)mLocalCache.Capacity()) {
                    if (!Bit(*(unsigned*)mLocalCache.Entry(mLocalIdx), 31)) {
                        UpdateLocalLightSample(*(int*)(mLocalCache.Entry(mLocalIdx) + 0x1d0));
                        budget--;
                    }
                }
                mLocalIdx++;
            }
        }
        if (mLocalIdx >= limit)
            mLocalIdx = -1;
    }
}

// @ 0x0070ae40
void SP::cLightingManager::Update(unsigned int param)
{
    for (char* it = *(char**)((char*)this + 0x34); it != (char*)this + 0x30;
         it = (char*)RBTreeIncrement(it)) {
        (*(SP::cLightingWorld**)(it + 0x14))->Update(param);
    }
}

// @ 0x0070ae70
void SP::cLightingManager::RemoveLightingWorld(unsigned int key)
{
    char* it;
    ((RBTree*)((char*)this + 0x2c))->Find(&it, &key);
    if (it != (char*)this + 0x30) {
        (*(SP::cLightingWorld**)(it + 0x14))->Shutdown();
        --*(int*)((char*)this + 0x40);
        RBTreeIncrement(it);
        RBTreeErase(it, (char*)this + 0x30);
        SP::cLightingWorld* w = *(SP::cLightingWorld**)(it + 0x14);
        if (w)
            ((void(__thiscall*)(SP::cLightingWorld*))(*(void***)w)[1])(w);
        EastlFree(it);
    }
}

// @ 0x0070aed0
void SP::cLightingManager_s0070_aed0::FillLightingStateFromConfig(cPropertyList_s0070_aed0* props, cLightingConfig_s0070_aed0* config)
{
    EA::Variant_s0070_aed0* prop;
    Vector4_s0070_aed0 coeffs[49];

    *config = SP::cLightingConfig_s0070_aed0();
    config->mpPropList = props;

    if (props) {
        EA::Variant_s0070_aed0* camProp;
        if (props->GetProperty(0x100eac6, &camProp) && camProp->mTypeId == 1)
            config->mbCameraSpaceLighting = camProp->GetBool();
    }

    // skylight colour and strength
    if (props->GetProperty(0x100eab6, &prop)) {
        config->mSkylight = AsColorRGB(prop);
        if (props->GetProperty(0x100eab7, &prop)) {
            float s = AsFloat(prop);
            float r = config->mSkylight.r * s;
            float g = config->mSkylight.g * s;
            float b = config->mSkylight.b * s;
            config->mSkylight.r = r;
            config->mSkylight.g = g;
            config->mSkylight.b = b;
        }
        config->mFlags.set(4);
    }

    // point light
    if (props->GetProperty(0x100eac7, &prop)) {
        config->mFlags.set(5);
        config->mPointLightPos = AsVector3(prop);
    }
    if (props->GetProperty(0x100eac8, &prop)) {
        const Vector3& c = AsVector3(prop);
        float r = c.x, g = c.y, b = c.z;
        config->mPointLightColor.r = r;
        config->mPointLightColor.g = g;
        config->mPointLightColor.b = b;
    }
    if (props->GetProperty(0x100eac9, &prop))
        config->mPointLightStrength = AsFloat(prop);
    if (props->GetProperty(0x100eaca, &prop))
        config->mPointLightRadius = AsFloat(prop);

    // directional lights: (dir, colour, strength) keys per light
    SP::cLight_s0070_aed0* light = config->mLights;
    uint32_t i = 0;
    for (uint32_t key = 0x100eab9; (int)key < 0x100eac5; key += 3) {
        if (props->GetProperty(key - 1, &prop)) {
            config->mFlags.set(i);
            light->mDir = Normalize(AsVector3(prop));
        }
        if (props->GetProperty(key, &prop))
            light->mColor = AsColorRGB(prop);
        if (props->GetProperty(key + 1, &prop))
            light->mStrength = AsFloat(prop);
        ++i;
        ++light;
    }

    // explicit SH coefficients
    int count;
    ColorRGB* shColors;
    if (SP::GetPropertyArrayColorRGB(props, 0x100eac5, &count, &shColors)) {
        memset(coeffs, 0, sizeof(coeffs));
        int n = eastl::min(count, mNumSHCoeffs);
        for (int j = 0; j < n; ++j)
            coeffs[j] = Vector4_s0070_aed0(shColors[j].r, shColors[j].g, shColors[j].b, 1.0f);
        SP::RemoveNormalizationConstants(mNumSHBands, coeffs);
        AddSHCoeffs(config, coeffs, mNumSHBands, props, 0x56784b9);
    }

    // hemisphere environment map
    if (props->GetProperty(0x100eacb, &prop)) {
        const EA::ResourceMan::Key_s0070_aed0& srcKey = AsKey(prop);
        EA::ResourceMan::Key_s0070_aed0 key = srcKey;
        key.mType = 0x3e421ed;
        EA::AutoRefCount_s0070_aed0<EA::ResourceMan::IResource> res;
        if (EA::ResourceMan::GetManager()->GetResource(srcKey, res.AsPPTypeParam(), 0, 0, 0, &key) ||
            EA::ResourceMan::GetManager()->GetResource(key, res.AsPPTypeParam(), 0, 0, 0, 0)) {
            SP::FindSHCoeffsFromHemiEnvMap(res.get(), mNumSHCoeffs, coeffs);
            AddSHCoeffs(config, coeffs, mNumSHBands, props, 0x56784c9);
        }
    }

    // HDR cube map
    if (props->GetProperty(0x477d61d, &prop)) {
        const EA::ResourceMan::Key_s0070_aed0& srcKey = AsKey(prop);
        EA::AutoRefCount_s0070_aed0<EA::ResourceMan::IResource> res;
        EA::ResourceMan::Key_s0070_aed0 key = srcKey;
        key.mType = 0x3e421ef;
        if (EA::ResourceMan::GetManager()->GetResource(srcKey, res.AsPPTypeParam(), 0, 0, 0, &key) ||
            EA::ResourceMan::GetManager()->GetResource(key, res.AsPPTypeParam(), 0, 0, 0, 0)) {
            SP::FindSHCoeffsFromHDRCubeMap(res.get(), mNumSHBands, coeffs);
            for (int j = 0; j < mNumSHCoeffs; ++j)
                coeffs[j] *= 256.0f;
            AddSHCoeffs(config, coeffs, mNumSHBands, props, 0x56784d9);
        }
    }

    // atmosphere phases
    if (props->GetProperty(0x100eacd, &prop) && prop->mTypeId == 0x33 && (prop->mFlags & 0x10)) {
        float zh[31];
        int n = prop->GetCount();
        SP::CalcAtmosphereZH(n, (const PlainVector4*)prop->GetStorage(), mNumSHBands, zh);
        float k = (float)(1.0 / sqrt(3.0));
        Vector3 dir(k, k, k);
        SP::RotateZHToSH(dir, mNumSHBands, zh, coeffs);
        AddSHCoeffs(config, coeffs, mNumSHBands, props, 0x56784e9);
    }

    // hemisphere colours (upper, optional lower)
    Vector3* hemi;
    if (SP::GetPropertyArrayVector3(props, 0x566caea, &count, &hemi) && count > 0) {
        float zh[7];
        SP::GetHemisphereZH(zh);
        memset(coeffs, 0, sizeof(coeffs));
        int j;
        for (j = 0; j < mNumSHBands; ++j) {
            float c = zh[j];
            *(Vector3*)&coeffs[(j + 1) * j] += hemi[0] * c;
        }
        for (j = 0; j < mNumSHBands; ++j) {
            if (j & 1) zh[j] = -zh[j];
        }
        if (count == 1) {
            for (j = 0; j < mNumSHBands; ++j) {
                float c = zh[j];
                *(Vector3*)&coeffs[(j + 1) * j] += Vector3(c, c, c);
            }
        } else {
            for (j = 0; j < mNumSHBands; ++j) {
                float c = zh[j];
                float* d = (float*)&coeffs[(j + 1) * j];
                d[0] += c * hemi[1].x;
                d[1] += hemi[1].y * c;
                d[2] += hemi[1].z * c;
            }
        }
        AddSHCoeffs(config, coeffs, mNumSHBands, props, 0x56784f9);
    }

    // cone lights: pairs of (colour.rgb + intensity, direction + cos angle)
    PlainVector4* cones;
    if (SP::GetPropertyArrayVector4(props, 0x566cae9, &count, &cones)) {
        count &= ~1;
        memset(coeffs, 0, sizeof(coeffs));
        Vector4_s0070_aed0 zero(0.0f, 0.0f, 0.0f, 0.0f);
        for (int j = 0; j < count; j += 2) {
            Vector4_s0070_aed0 tmp(cones[j].x, cones[j].y, cones[j].z, cones[j].w);
            ((float*)&tmp)[3] = ((float*)&zero)[0];
            Vector4_s0070_aed0 color = tmp;
            Vector3 dir;
            dir.x = cones[j + 1].x;
            dir.y = cones[j + 1].y;
            dir.z = cones[j + 1].z;
            float intensity = cones[j].w;
            float zh[7];
            SP::GetConeZH(cones[j + 1].w, zh);
            SP::RotateZHToSHAdd(dir, mNumSHBands, intensity * color, zh, coeffs);
        }
        AddSHCoeffs(config, coeffs, mNumSHBands, props, 0x5678419);
    }

    // ground bounce
    if (!config->mSHCoeffs.empty()) {
        ColorRGB diffuse;
        if (SP::GetPropertyAsColorRGB(props, 0x100eace, &diffuse)) {
            ColorRGB specular = kColorWhite;
            SP::GetPropertyAsColorRGB(props, 0x100eacf, &specular);
            SP::AddGroundBounce(mNumSHBands, config->mSHCoeffs.mpBegin,
                            Vector4_s0070_aed0(diffuse.r, diffuse.g, diffuse.b, 1.0f),
                            Vector4_s0070_aed0(specular.r, specular.g, specular.b, 1.0f));
        }
    }
    if (!config->mSHCoeffs.empty())
        SP::ApplyNormalizationConstants(mNumSHBands, config->mSHCoeffs.mpBegin);

    GetFloatProperty(props, 0x2478ed7, &config->mPlanetAtmosphere);
    float angle = 1.0f;
    GetFloatProperty(props, 0x64dab03, &angle);
    config->mBounceDiffCos = cosf(angle * 0.017453292f);
    GetFloatProperty(props, 0x696cb45, &config->mBounceSpec);
    GetFloatProperty(props, 0x2478eda, &config->field_DC);
    GetFloatProperty(props, 0x2478edb, &config->field_E0);
    SP::GetPropertyAsVector4(props, 0x2478edc, &config->mColourPhaseAdd[0]);
    SP::GetPropertyAsVector4(props, 0x2478edd, &config->mColourPhaseAdd[1]);
    SP::GetPropertyAsVector4(props, 0x2478ede, &config->mColourPhaseAdd[2]);
    GetFloatProperty(props, 0x2478edf, &config->mSunStart);
    {
        EA::Variant_s0070_aed0* p;
        if (props->GetProperty(0x2478ee0, &p) && p->mTypeId == 0xd)
            config->mSunInvRange = 1.0f / (*(float*)p->GetStorage() + 1e-6f);
    }
    GetFloatProperty(props, 0x2478ee1, &config->mNightStart);
    {
        EA::Variant_s0070_aed0* p;
        if (props->GetProperty(0x2478ee2, &p) && p->mTypeId == 0xd)
            config->mNightInvRange = 1.0f / (*(float*)p->GetStorage() + 1e-6f);
    }
    SP::GetPropertyAsVector2(props, 0x49b94d5, &config->field_124);
    SP::GetPropertyAsVector2(props, 0x49b94d6, &config->mCelRange);
    {
        EA::Variant_s0070_aed0* p;
        if (props->GetProperty(0x4adacd8, &p) && p->mTypeId == 1)
            config->mTerrainLightEnabled = *(bool*)p->GetStorage();
    }
    GetFloatProperty(props, 0x4adacd9, &config->mTerrainLightStrength);
    GetFloatProperty(props, 0x4adacda, &config->mTerrainLightSize);
    GetFloatProperty(props, 0x4adacdb, &config->mTerrainLightHeightDropoff);

    // global SH intensity scale
    if (props->GetProperty(0x100eac4, &prop)) {
        float scale = AsFloat(prop);
        int n = config->mSHCoeffs.size();
        for (int j = 0; j < n; ++j)
            config->mSHCoeffs.mpBegin[j] = scale * config->mSHCoeffs.mpBegin[j];
    }
}

// @ 0x0070c040
void SimpleDequeDtor(void* self)
{
    (void)self;
}

// @ 0x0070c090
void SlotVecCreateEnv(void* self, const void* init)
{
    (void)self;
    (void)init;
}

// @ 0x0070c200
uint32_t SlotVecCellCreate(SlotVecCell*, const void*)
{
    return 0;
}

// @ 0x0070c3a0
void FixedCellVectorCtor(void* self)
{
    (void)self;
}

// @ 0x0070c410
void cLightingWorld_s0070_c040::CreateLocalLightSample(int info)
{
    cLocalLightCellInit init;
    init.mGlobal = false;
    init.mInUse = false;
    init.mType = 0;
    init.mColour.x = 0.0f;
    init.mColour.y = 0.0f;
    init.mColour.z = 0.0f;
    init.mSize = 0.0f;
    init.mExtra[0] = 0;
    init.mExtra[1] = 0;
    init.mExtra[2] = 0;
    init.mExtra[3] = 0;
    uint32_t id = ((SlotVecCell*)((char*)this + 0x608))->create(&init);
    *(uint32_t*)((char*)info + 0x24) = id;
    int base = *(int*)(*(int*)((char*)this + 0x608) + ((uint32_t)id >> 7) * 4);
    *(int*)(base + 0x1d0 + (id & 0x7f) * 0x1e0) = info;
    UpdateLocalLightSample(info);
}

// @ 0x0070c4b0
void SlotVectorHelperA(void* self)
{
    (void)self;
}

// @ 0x0070c5e0
void SlotVectorHelperB(void* self)
{
    (void)self;
}

// @ 0x0070c7c0
cLocalLightInfo::cLocalLightInfo(const cLocalLightInfo& x)
: mColour(x.mColour), mSize(x.mSize), mPosition(x.mPosition), mStrength(x.mStrength),
      mDecal(x.mDecal), mGlobal(x.mGlobal), mCells(x.mCells)
{
}

// @ 0x0070c830
void SlotVectorHelperC(void* self)
{
    (void)self;
}

// @ 0x0070cab0
void SP::cLightingWorld::UpdateLightingInfo(float a0, cSPVector3 const & a2, SP::cLightingInfo * a3)
{
}

// @ 0x0070cce0
void SlotVecCreateLocal(void* self, const void* init)
{
    (void)self;
    (void)init;
}

// @ 0x0070ced0
void ConfigVec::DoInsertValue(cLightingConfig* position, const cLightingConfig& value)
{
    if (mpEnd != mpCapacity) // size < capacity
    {
        const cLightingConfig* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        new ((void*)mpEnd) cLightingConfig(*(mpEnd - 1));
        ConfigCopyBackward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    }
    else // size == capacity
    {
        const unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNewSize = nPrevSize ? nPrevSize * 2 : 1;
        cLightingConfig* pNewData;
        if (nNewSize == 0)
            pNewData = 0;
        else
            pNewData = (cLightingConfig*)EAlloc(nNewSize * sizeof(cLightingConfig), "Graphics", 0, 0, ALLOC_FILE, 0xd1);

        cLightingConfig* pNewEnd = ConfigUninitCopy(mpBegin, position, pNewData);
        ConfigDestruct(mpBegin, position, pNewData);
        new ((void*)pNewEnd) cLightingConfig(value);
        cLightingConfig* pEnd = ConfigUninitCopy(position, mpEnd, pNewEnd + 1);
        ConfigDestruct(position, mpEnd, pNewEnd + 1);

        cLightingConfig* pOld = mpBegin;
        if ((pOld != 0) && (*(int*)((char*)pOld - 4) != 0))
            EFree(pOld);

        mpBegin = pNewData;
        mpEnd = pEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x0070d080
void ConfigVec::DoInsertValues(cLightingConfig* position, unsigned n, const cLightingConfig& value)
{
    if (n > (unsigned)(mpCapacity - mpEnd))
    {
        const unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nGrowSize = nPrevSize ? nPrevSize * 2 : 1;
        unsigned nNewSize = nPrevSize + n;
        if (nNewSize < nGrowSize)
            nNewSize = nGrowSize;
        cLightingConfig* pNewData = (nNewSize == 0)
            ? 0 : (cLightingConfig*)EAlloc(nNewSize * sizeof(cLightingConfig), "Graphics", 0, 0, ALLOC_FILE, 0xd1);

        cLightingConfig* pNewEnd = ConfigUninitCopy(mpBegin, position, pNewData);
        ConfigDestruct(mpBegin, position, pNewData);
        ConfigUninitFillN(pNewEnd, n, &value, mpBegin);
        cLightingConfig* pEnd = ConfigUninitCopy(position, mpEnd, pNewEnd + n);
        ConfigDestruct(position, mpEnd, pNewEnd + n);

        cLightingConfig* pOld = mpBegin;
        if ((pOld != 0) && (*(int*)((char*)pOld - 4) != 0))
            EFree(pOld);

        mpBegin = pNewData;
        mpEnd = pEnd;
        mpCapacity = pNewData + nNewSize;
    }
    else if (n != 0)
    {
        cLightingConfig temp(value);
        const unsigned nExtra = (unsigned)(mpEnd - position);
        if (n < nExtra)
        {
            ConfigUninitMoveN(0, mpEnd - n, mpEnd, &temp);
            ConfigCopyBackward(position, mpEnd - n, mpEnd);
            ConfigFill(position, position + n, &temp);
        }
        else
        {
            ConfigUninitFillN(mpEnd, n - nExtra, &temp, mpEnd);
            ConfigUninitMoveN(0, position, mpEnd, &temp);
            ConfigFill(position, mpEnd, &temp);
        }
        mpEnd += n;
        temp.~cLightingConfig();
    }
}

// @ 0x0070d2c0
cLightingWorld_s0070_ced0::cLightingWorld_s0070_ced0(char* debugName)
{
    unsigned char* p = _b;
    unsigned char* q;

    *(void**)(p + 0x00) = (void*)0x0140c760;
    *(void**)(p + 0x04) = (void*)0x0140c74c;
    *(int*)(p + 0x08) = 0;
    *(void**)(p + 0x0c) = debugName;
    *(int*)(p + 0x10) = 0;
    *(int*)(p + 0x14) = 0;
    *(int*)(p + 0x18) = 0;
    *(float*)(p + 0x1c) = *(const float*)0x013f9c6c;
    *(float*)(p + 0x20) = *(const float*)0x013f9c6c;
    *(int*)(p + 0x24) = 0;
    *(float*)(p + 0x28) = *(const float*)0x013ec4d0;
    *(float*)(p + 0x2c) = *(const float*)0x013ec4d0;
    *(float*)(p + 0x30) = *(const float*)0x013f1cac;
    *(int*)(p + 0x34) = 4;
    *(int*)(p + 0x38) = 0x10;
    *(int*)(p + 0x3c) = 0xc8;
    *(float*)(p + 0x40) = *(const float*)0x01629884;
    *(float*)(p + 0x44) = *(const float*)0x01629888;
    *(float*)(p + 0x48) = *(const float*)0x0162988c;
    *(int*)(p + 0x4c) = 0;
    *(int*)(p + 0x50) = 0;
    *(int*)(p + 0x54) = 0;
    *(int*)(p + 0x60) = 0;
    *(unsigned short*)(p + 0x64) = 0;
    *(unsigned short*)(p + 0x66) = 0;
    *(float*)(p + 0x68) = *(const float*)0x01629858;
    *(float*)(p + 0x6c) = *(const float*)0x0162985c;
    *(float*)(p + 0x70) = *(const float*)0x01629860;
    *(float*)(p + 0x74) = *(const float*)0x01485720;
    ((HM*)(p + 0x78))->Assign((const void*)0x016299ac);
    *(unsigned short*)(p + 0x9c) = 0;
    *(unsigned short*)(p + 0x9e) = 0;
    *(float*)(p + 0xa0) = *(const float*)0x01629858;
    *(float*)(p + 0xa4) = *(const float*)0x0162985c;
    *(float*)(p + 0xa8) = *(const float*)0x01629860;
    *(float*)(p + 0xac) = *(const float*)0x01485720;
    ((HM*)(p + 0xb0))->Assign((const void*)0x016299ac);
    *(float*)(p + 0xd4) = *(const float*)0x01629858;
    *(float*)(p + 0xd8) = *(const float*)0x0162985c;
    *(float*)(p + 0xdc) = *(const float*)0x01629860;
    *(unsigned char*)(p + 0xe0) = 0;
    *(float*)(p + 0x240) = *(const float*)0x01629858;
    *(float*)(p + 0x244) = *(const float*)0x0162985c;
    *(float*)(p + 0x248) = *(const float*)0x01629860;
    *(int*)(p + 0x24c) = 0;
    *(int*)(p + 0x250) = 0;
    *(unsigned char*)(p + 0x260) = 0;
    *(unsigned char*)(p + 0x261) = 0;
    *(unsigned short*)(p + 0x262) = 0;
    *(int*)(p + 0x264) = 0;
    *(int*)(p + 0x268) = 0;
    *(int*)(p + 0x26c) = 0;
    *(int*)(p + 0x270) = 0;
    *(int*)(p + 0x280) = 0;
    *(int*)(p + 0x284) = 0;
    *(int*)(p + 0x288) = 0;
    *(int*)(p + 0x28c) = 0;
    *(int*)(p + 0x420) = 0;
    *(unsigned char*)(p + 0x424) = 0;
    *(int*)(p + 0x428) = 0;
    *(int*)(p + 0x42c) = 0;
    *(int*)(p + 0x430) = 0;
    *(int*)(p + 0x43c) = 0x7f;
    *(int*)(p + 0x440) = 0x3fffffff;
    *(int*)(p + 0x444) = 0x3fffffff;
    *(int*)(p + 0x448) = 0;
    q = p + 0x44c;
    *(int*)(q + 0x00) = 0;
    *(int*)(q + 0x04) = 0;
    *(int*)(q + 0x08) = 0;
    *(int*)(q + 0x0c) = 0;
    *(int*)(q + 0x10) = 0;
    *(int*)(q + 0x14) = 0;
    ((HD3D*)q)->Op(0);
    *(int*)(q + 0x18) = 0;
    *(int*)(q + 0x1c) = 0;
    *(int*)(q + 0x20) = 0;
    *(int*)(q + 0x24) = 0;
    q = p + 0x490;
    *(void**)(p + 0x488) = q;
    *(void**)(p + 0x47c) = q;
    *(void**)(p + 0x478) = q;
    *(void**)(p + 0x480) = q + 0x100;
    *(unsigned char*)(p + 0x590) = 0;
    *(int*)(p + 0x594) = 0;
    *(int*)(p + 0x598) = 0;
    *(int*)(p + 0x59c) = 0;
    *(int*)(p + 0x5ac) = 0x3fffffff;
    *(int*)(p + 0x5b0) = 0x3fffffff;
    *(int*)(p + 0x5a8) = 0x7f;
    *(int*)(p + 0x5b4) = 0;
    *(int*)(p + 0x5b8) = 0;
    *(int*)(p + 0x5bc) = 0;
    *(unsigned char*)(p + 0x5cc) = 0;
    *(int*)(p + 0x5d0) = 0;
    *(int*)(p + 0x5c8) = -1;
    *(int*)(p + 0x5d4) = 0;
    *(int*)(p + 0x5d8) = 0;
    *(int*)(p + 0x5dc) = 0;
    *(int*)(p + 0x5e8) = 0;
    *(int*)(p + 0x5ec) = 0;
    *(int*)(p + 0x5f0) = 0;
    *(int*)(p + 0x5fc) = 0;
    q = p + 0x600;
    *(void**)(q + 4) = q;
    *(void**)(q + 0) = q;
    *(int*)(p + 0x608) = 0;
    *(int*)(p + 0x60c) = 0;
    *(int*)(p + 0x610) = 0;
    *(int*)(p + 0x61c) = 0x7f;
    *(int*)(p + 0x620) = 0x3fffffff;
    *(int*)(p + 0x624) = 0x3fffffff;
    *(int*)(p + 0x628) = 0;
    *(int*)(p + 0x62c) = 0;
    *(int*)(p + 0x630) = 0;
    *(int*)(p + 0x63c) = 0;
    *(int*)(p + 0x640) = 0;
    *(int*)(p + 0x644) = 0;
    *(int*)(p + 0x650) = 0x7f;
    *(int*)(p + 0x654) = 0x3fffffff;
    *(int*)(p + 0x658) = 0x3fffffff;
    *(int*)(p + 0x65c) = -1;
    *(unsigned char*)(p + 0x660) = 0;
    *(int*)(p + 0x420) = 0;
    InitAtmBuffer(p + 0xf0, 0, 0x150);
}

// @ 0x0070d6d0
cLightingWorld_s0070_ced0::~cLightingWorld_s0070_ced0()
{
    unsigned char* p = _b;
    ((H63c*)(p + 0x63c))->Free();
    if ((*(int*)(p + 0x628) != 0) && (*(int*)(*(int*)(p + 0x628) - 4) != 0))
        EFree(*(void**)(p + 0x628));
    ((H608*)(p + 0x608))->Free();
    ((HList*)(p + 0x600))->Dtor();
    if ((*(int*)(p + 0x5e8) != 0) && (*(int*)(*(int*)(p + 0x5e8) - 4) != 0))
        EFree(*(void**)(p + 0x5e8));
    if ((*(int*)(p + 0x5d4) != 0) && (*(int*)(*(int*)(p + 0x5d4) - 4) != 0))
        EFree(*(void**)(p + 0x5d4));
    if ((*(int*)(p + 0x5b4) != 0) && (*(int*)(*(int*)(p + 0x5b4) - 4) != 0))
        EFree(*(void**)(p + 0x5b4));
    ((H608*)(p + 0x594))->Free();
    {
        int e = *(int*)(p + 0x478);
        if ((e != 0) && (e != *(int*)(p + 0x488)))
            EFree((void*)e);
    }
    ((H44c*)(p + 0x44c))->Free();
    if (*(void**)(p + 0x448) != 0)
        ((VObj_s0070_ced0*)*(void**)(p + 0x448))->f3();
    ((HDeque*)(p + 0x428))->Dtor();
    if (*(void**)(p + 0x24c) != 0)
        ((VObj_s0070_ced0*)*(void**)(p + 0x24c))->f1();
    if ((*(int*)(p + 0x4c) != 0) && (*(int*)(*(int*)(p + 0x4c) - 4) != 0))
        EFree(*(void**)(p + 0x4c));
    *(void**)(p + 0x04) = (void*)0x013ec458;
    *(void**)(p + 0x00) = (void*)0x013eb938;
}

// @ 0x0070d850
unsigned cLightingWorld_AddLight(cLightingWorld_s0070_ced0* self, const float* colour, const float* position, float strength, float size)
{
    unsigned char* p = self->_b;
    if (*(void**)(p + 0x10) == 0)
        return 0xffffffff;

    // reserve a slot in mLocalLights (slot_deque create)
    unsigned slot = SlotCreate(p + 0x428, 0);
    unsigned char* info = (unsigned char*)(*(int*)(*(int*)(p + 0x628) + (slot >> 7) * 4)
                                           + 4 + (slot & 0x7f) * 0xc4);
    InitAtmBuffer(info, 0, 0xc0);

    *(float*)(info + 0x10) = colour[0];
    *(float*)(info + 0x14) = colour[1];
    *(float*)(info + 0x18) = colour[2];
    *(float*)(info + 0x00) = position[0];
    *(float*)(info + 0x04) = position[1];
    *(float*)(info + 0x08) = position[2];
    *(float*)(info + 0x0c) = size;
    *(float*)(info + 0x1c) = strength / (size + 1e-06f);
    *(unsigned char*)(info + 0x24) = 1;
    ++*(int*)(p + 0x5d0);

    if (*(unsigned char*)(info + 0x24) == 0)
    {
        int cells = CellListBuild(0x10, colour, size, 0);
        cells = CellListFilter(cells, 0);
    }
    // ... build per-cell entries into mGlobalLights (omitted detail)
    *(unsigned char*)(p + 0x660) = 1;
    if ((*(unsigned char*)(*(int*)(p + 0x10) + 0x134) != 0) && (*(int*)(p + 0x448) != 0))
        NotifyLightAdded(info);
    if (*(unsigned char*)(p + 0x590) == 0)
    {
        *(unsigned char*)(p + 0x590) = 1;
        void* ms = MessageServer();
        ((MServer*)ms)->m5(0x2495f34, 0, 0);
    }
    return slot;
}

// @ 0x0070dc90
cLightingWorld_s0070_ced0* cLightingManager::MakeWorld(int owner, int a3, void* arg4)
{
    cLightingWorld_s0070_ced0* world = (cLightingWorld_s0070_ced0*)GAlloc(0x670, 0x10, 0, "Graphics", 0, 0, 0, 0);
    if (world != 0)
        world = new (world) cLightingWorld_s0070_ced0((char*)owner);
    ((HSmall*)world)->Op();
    if (arg4 != 0)
        ((VObj_s0070_ced0*)world)->f12(arg4);
    void* slot = ((HMap*)((char*)this + 0x2c))->Find(&owner);
    void* old = *(void**)slot;
    if (world != old)
    {
        if (world != 0)
            ((VObj_s0070_ced0*)world)->f0();
        *(void**)slot = world;
        if (old != 0)
            ((VObj_s0070_ced0*)old)->f1();
    }
    return world;
}

// @ 0x0070ddd0
bool SP::cLightingManager::Shutdown()
{
    unsigned char* p = (unsigned char*)this;
    void* ms = MessageServer();
    if (ms != 0)
    {
        void* handler = (this != 0) ? (p + 4) : 0;
        ((MServer*)ms)->Unsubscribe(handler, 0xf62def, (int)0xffffd8f1);
    }
    // clear mLightingStates + mIDToWorldMap
    void* r = ConfigRangeOp1((void*)*(int*)(p + 0x1c), (void*)*(int*)(p + 0x1c), (void*)*(int*)(p + 0x18));
    ((HNuke*)(p + 0x18))->Nuke(r);
    {
        int begin = *(int*)(p + 0x18);
        int end = *(int*)(p + 0x1c);
        *(int*)(p + 0x1c) = end + ((end - begin) / 0x144) * 0x144;
    }
    void* n = (void*)*(int*)(p + 0x34);
    void* head = (void*)(p + 0x30);
    while (n != head)
    {
        ((HShut*)*(void**)((char*)n + 0x14))->Shutdown();
        n = RBTreeIncrement(n);
    }
    ((HNode*)(p + 0x2c))->Dtor((void*)*(int*)(p + 0x38));
    *(int*)(p + 0x34) = (int)head;
    *(int*)(p + 0x30) = (int)head;
    *(int*)(p + 0x38) = 0;
    *(unsigned char*)(p + 0x3c) = 0;
    *(int*)(p + 0x40) = 0;
    return 1;
}

// @ 0x0070de90
int cLightingManager_HandleMessage(void* self, int msg, void* data)
{
    if (msg != 0xf62def)
        return 0;
    int id = *(int*)((char*)data + 0x10);
    if (id == *(int*)0x01535b38)
    {
        int state = *(int*)((char*)data + 0x18);
        int count = (*(int*)((char*)self + 0x18) - *(int*)((char*)self + 0x14)) / 0x144;
        void* found = 0;
        int i = 0;
        for (; i < count; i++)
        {
            void* cfg = (void*)(*(int*)((char*)self + 0x14) + i * 0x144);
            if (*(void**)cfg != 0 && *(int*)(*(int*)cfg + 8) == state)
                break;
        }
        if (i < count)
        {
            void* cfg = (void*)(*(int*)((char*)self + 0x14) + i * 0x144);
            FillLightingStateFromConfig(cfg, cfg);
            found = cfg;
        }
        else
        {
            void* pm = PropertyManager();
            void** vt = *(void***)pm;
            void* prop = 0;
            if (((char(__thiscall*)(void*, int, int, void**))vt[0x2c / 4])(pm, state, id, &prop))
            {
                LConfig tmp;
                LConfig_Default(&tmp);
                LConfigVec_Resize((LConfigVec*)((char*)self + 0x14), count + 1);
                LConfig* last = *(LConfig**)((char*)self + 0x18) - 1;
                FillLightingStateFromConfig((void*)prop, last);
                tmp.~LConfig();
                found = last;
            }
        }
        if (found != 0)
        {
            void* node = (void*)*(int*)((char*)self + 0x30);
            void* head = (char*)self + 0x2c;
            while (node != head)
            {
                void* w = *(void**)((char*)node + 0x14);
                if (*(void**)((char*)w + 0x10) == found)
                    RBTreeInc(node);
                node = (void*)*(int*)node; // advance placeholder
                break;
            }
        }
    }
    return 1;
}

// @ 0x0070e280
bool SP::cLightingManager::Init()
{
    void* self = this;
    ((void(__thiscall*)(void*))ReloadLightingStates)(self);
    void* ms = MessageServer();
    if (ms != 0)
    {
        if (self != 0)
            ((MsgReg*)ms)->a8((char*)self + 4, 0xf62def);
        else
            ((MsgReg*)ms)->a8(0, 0xf62def);
    }
    return 1;
}

// @ 0x007831d0
void FUN_007831d0(float x, float* out)
{
    float x2 = x * x;
    float x3 = x2 * x;
    out[0] = (((1.0f - x) * g_16340e0) * g_153ae10) * 2.0f;
    float f6 = (1.0f - x2) * g_16341d8;
    float f4 = (0.5f - (x2 * 7.5f + ((x3 * x3) * 10.5f - (x2 * x2) * 17.5f))) * g_1634090;
    out[1] = ((1.0f - x2) * g_1634068) * g_153ae10;
    out[5] = (f4 * g_153ae10) * 2.0f;
    out[2] = ((f6 * g_153ae10) * x) * 2.0f;
    float f3 = ((x3 * 10.0f - (x3 * x2) * 7.0f) - x * 3.0f) * g_16340d8;
    out[3] = ((((6.0f - x2 * 5.0f) * x2 - 1.0f) * g_1634108) * g_153ae10) * 0.5f;
    out[4] = (f3 * g_153ae10) * 2.0f;
    out[6] = ((-((x3 * 35.0f + (((x2 * x2) * x3) * 33.0f - (x3 * x2) * 63.0f)) - x * 5.0f) * g_16340a0) * g_153ae10) * 2.0f;
}

// @ 0x00783410
void FUN_00783410(float angle, int n, float* v)
{
    if (n <= 1)
        return;
    float co = (float)cos((double)angle);
    float si = (float)sin((double)angle);
    float* p = v + 4;
    // first column pair rotation (2x2)
    float a = p[-4], b = p[-3], c = p[-2], d = p[-1];
    p[-4] = co * a - si * p[0];
    p[-3] = co * b - si * p[1];
    p[-2] = co * c - si * p[2];
    p[-1] = co * d - si * p[3];
    (void)a; (void)b; (void)c; (void)d;
    // remaining blocks (see partial.txt)
}

// @ 0x009276c0
void cLocalLightInfo_s0092_72c0::Release(int param)
{
    if (param != 0) {
        CriSec* cs = mCS;
        if (cs != 0) {
            EnterCriticalSection(cs);
            cs->ref++;
        }
        Sub(param);
        if (cs != 0) {
            cs->ref--;
            LeaveCriticalSection(cs);
        }
    }
}
