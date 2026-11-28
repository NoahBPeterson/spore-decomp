// src/game/Swarm/_at_00a80000.cpp -- migrated from slice(s) s00a85c00, s00a86b30, s00a84ca0, s00a83c00, s00a81110 by tools/migrate/rewrite.py
// Object file: Swarm/_at_00a80000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_13ef094[];
extern "C" char g_1457fd8[];

// the slices' own placement new/delete win over <new>'s (a slice includes <new>; C2084 otherwise)
#define __PLACEMENT_NEW_INLINE

#include "game/types.h"
#include "EA/Swarm/cVisualEffect.h"

// unnamed retail callees and globals (address in the comment)
extern const float DAT_01485720;                       // 1.0f
extern const float DAT_0167790c;
extern const float DAT_0167776c, DAT_01677770, DAT_01677774;
extern char  DAT_01677818[];                           // source Matrix3 for Matrix3::Assign
extern "C" void  FUN_007cdbe0(float* out, float* box);                                 // 0x007cdbe0
#include <math.h>
#include <xmmintrin.h>
#include "EA/Swarm/cEffectParams.h"
#include "EA/Swarm/cIComponent.h"
#include "EA/Swarm/cTransform.h"
#include <string.h>
#include "cSPTransform.h"
#include <intrin.h>
#include <new>

// ---- items of slice s00a81110 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
extern const float DAT_01485720;                       // 1.0f
extern const float DAT_0167790c;
extern const float DAT_0167776c, DAT_01677770, DAT_01677774;
extern char  DAT_01677818[];                           // source Matrix3 for Matrix3::Assign
struct Matrix3 { float m[9]; };                        // 0x24
struct ExtCallees {
    void* __thiscall ctorCell();                       // 0x00a80920
    void* __thiscall ctorSurfaceDecals();              // 0x00a80ac0
    void* __thiscall mapInsert(u32 key);               // 0x00a810a0
    void* __thiscall mapFind(void** out, u32 key);     // 0x00a7bf40  (ret 8)
    void  __thiscall resize(int n);                    // 0x004c0410  (ret 4)
    void* __thiscall assign(const void* src);          // 0x00537dc0  (ret 4)
    void* __thiscall insert(void* pos, void** val);    // 0x00a80dd0  (ret 8)
};
extern "C" void  FUN_007cdbe0(float* out, float* box);                                 // 0x007cdbe0
struct RandomLCG { double __thiscall RandomDoubleUniform(); };   // 0x009360d0
extern RandomLCG g_sRandom;                                      // 0x016778dc
namespace EA {
namespace Swarm {
class cSurfaceDecalManager {                           // size 0xa8 (dev layout)
public:
    void* AddDecal(int unused, u32 key, const void* xform, float scale);  // 0x00a81110
    void  SetSurface(void* surface, void* transform);  // 0x00a81310
};
}
}
using EA::Swarm::cSurfaceDecalManager;
// ---- items of slice s00a81110 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern RandomLCG g_sRandom;                                      // 0x016778dc

// ---- items of slice s00a83c00 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IOStream;
bool WriteUint32(IOStream* s, const void* p, uint32_t n, int endian);     // 0x0093aa70
bool WriteUint16(IOStream* s, const void* p, uint32_t n, int endian);     // 0x0093a9d0
bool StreamWrite(IOStream* s, const void* p, uint32_t n);                 // 0x0093a9a0
bool ReadInt32(IOStream* s, void* p, uint32_t n, int endian);             // 0x0093a780
bool ReadUint16(IOStream* s, void* p, uint32_t n, int endian);            // 0x0093a700
bool ReadUint8(IOStream* s, void* p, uint32_t n);                         // 0x0093a6c0
inline bool WriteV32(IOStream* s, uint32_t v) { return WriteUint32(s, &v, 1, 0); }
inline bool WriteV32(IOStream* s, int v) { return WriteUint32(s, &v, 1, 0); }
inline bool WriteF32(IOStream* s, float v) { return WriteUint32(s, &v, 1, 0); }
inline bool WriteV16(IOStream* s, uint16_t v) { return WriteUint16(s, &v, 1, 0); }
inline bool WriteBool(IOStream* s, bool v) { return StreamWrite(s, &v, 1); }
void  FUN_007d01f0(IOStream* s, void* v);                      // 0x007d01f0
void  FUN_007d0250(IOStream* s, void* v);                      // 0x007d0250
void* EAAllocate(uint32_t size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void* EAAllocate(uint32_t size, const char* name, int a, int b,
                 const char* file, int line);                  // same, EASTL allocator form
void  operator delete(void* p);                                // 0x00f47380
inline void  operator delete(void*, void*) {}
struct ResizableVec { void __thiscall resize(int n); };                 // 0xa6f010
void  FUN_00a6a2f0(void* dst, const void* src);
void  FUN_00a6a9c0(void* dst, void* a, void* b, void* c, void* d);
void  FUN_00a6eab0(void* a, void* b, void* c);
void* FUN_00a6e9a0(void* a, void* b, void* c);
void  FUN_00a6e460(void* a, void* b, void* c);
void  FUN_00a847f0(void* dst, u32 n, const void* src);
void  FUN_00a84820(void* a, void* b, void* c);
void* WriteTransform(IOStream* s, void* v);                    // 0x00a84460
void  WriteRec(IOStream* s, void* v);                          // 0x00a84510
void* WriteRecList(IOStream* s, void* v);                      // 0x00a846c0
void* WriteDescRec(IOStream* s, void* v);                      // 0x00a84720
void* ReadLODScales(IOStream* s, void* v);                     // 0x00a84850
void  ReadDescRec(IOStream* s, void* v);                       // 0x00a848d0
void  ResizeDescRecs(void* self, u32 n, const void* val, void* out); // 0x00a84a80
struct StreamW { virtual void v0();virtual void v1();virtual void v2();virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
    virtual void v12();virtual void v13();virtual void write(const void* data, int size); };
struct StreamR { virtual void v0();virtual void v1();virtual void v2();virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
    virtual void read(void* data, int size); };
// ---- items of slice s00a83c00 end

// ---- items of slice s00a84ca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void  __cdecl operator_delete__(void* p);                            // 0x00f47380
extern void  __cdecl FUN_00a84d40(void* s, void* d);                        // 0x00a84d40
extern void  __cdecl FUN_0093a780(void* s, void* p, int n, int z);          // 0x0093a780
extern void  __cdecl FUN_0093a700(void* s, void* p, int n, int z);          // 0x0093a700
extern void  __cdecl FUN_0093a800(void* s, void* p, int n, int z);          // 0x0093a800
extern void  __cdecl FUN_0093a6c0(void* s, void* p, int n);                 // 0x0093a6c0
extern void  __cdecl FUN_007d27d0(void* s, void* p);                        // 0x007d27d0
extern int   __cdecl FUN_0093a9a0(void* s, void* p, int n);                 // 0x0093a9a0
extern int   __cdecl FUN_0093ab10(void* s, void* p, int a, int b);          // 0x0093ab10
extern int   __cdecl FUN_0093a9d0(void* s, void* p, int a, int b);          // 0x0093a9d0
extern int   __cdecl FUN_0093aa70(void* s, void* p, int a, int b);          // 0x0093aa70
static inline bool Bit(uint32_t v, int n) { return (v >> n) & 1; }
struct Mat3  { void __thiscall Assign(const void* src); };                  // 0x0041cb40
struct Xf    { void __thiscall RotateZ(float); void __thiscall PreRotateX(float);
               void __thiscall RotateY(float); };                           // 0x7d1ac0/0x5a2d90/0x6b9050
struct Trn   { void __thiscall PreTransformBy(const void* src); };          // 0x537f40
struct SpTr  { void* __thiscall Assign(const void* src); };                 // 0x537dc0
struct Cfg
{
    void*    vt;         // 0x00
    void*    p04;        // 0x04
    uint32_t flags;      // 0x08
    uint16_t w0c;        // 0x0c
    uint16_t p0e;        // 0x0e
    float    f10;        // 0x10
    void*    arr14;      // 0x14
    void*    e14;        // 0x18
    uint32_t p1c;        // 0x1c
    uint32_t p20;        // 0x20
    uint32_t p24;        // 0x24
    void*    arr28;      // 0x28
    void*    e28;        // 0x2c
    uint32_t p30;        // 0x30
    uint32_t p34;        // 0x34
    uint32_t p38;        // 0x38
    void*    arr3c;      // 0x3c
    void*    e3c;        // 0x40
    uint32_t p44;        // 0x44
    uint32_t p48;        // 0x48
    uint32_t p4c;        // 0x4c
    void*    arr50;      // 0x50
    void*    e50;        // 0x54
    uint32_t p58;        // 0x58
    uint32_t p5c;        // 0x5c
    uint32_t p60;        // 0x60
    void*    arr64;      // 0x64
    void*    e64;        // 0x68
    uint32_t p6c;        // 0x6c
    uint32_t p70;        // 0x70
    uint32_t p74;        // 0x74
    void*    arr78;      // 0x78
    void*    e78;        // 0x7c
    uint32_t p80;        // 0x80
    uint32_t p84;        // 0x84
    uint32_t p88;        // 0x88
    void*    arr8c;      // 0x8c
    void*    e8c;        // 0x90
    uint32_t p94;        // 0x94
    uint32_t p98;        // 0x98
    uint32_t p9c;        // 0x9c
    uint32_t a0;         // 0xa0
    uint32_t a4;         // 0xa4
    uint16_t wa8;        // 0xa8
    uint16_t paa;        // 0xaa

    Cfg* __fastcall Ctor();
    void __fastcall Release();
};
struct Sim
{
    void*    vt;         // 0x00
    void*    p04;        // 0x04
    uint32_t p08;        // 0x08
    Cfg*     cfg;        // 0x0c
    void*    h10;        // 0x10
    uint8_t  b14;        // 0x14
    uint8_t  b15;        // 0x15
    uint16_t w16;        // 0x16
    float    f18;        // 0x18
    float    f1c;        // 0x1c
    float    f20;        // 0x20
    uint16_t w24;        // 0x24
    uint16_t w26;        // 0x26
    float    f28;        // 0x28
    float    f2c;        // 0x2c
    float    f30;        // 0x30
    float    f34;        // 0x34
    uint8_t  m38[0x24];  // 0x38
    float    f5c;        // 0x5c
    float    f60;        // 0x60
    float    f64;        // 0x64
    int32_t  i68;        // 0x68

    Sim* __thiscall Ctor(void* cfg);
    void __thiscall Activate(bool);
    void __thiscall Deactivate(bool);
    void __fastcall Sample();
    void __thiscall Build();
    void __thiscall Tick(float dt, void* a, void* b);
    void __thiscall SetCfg(void* c, void* d, void* e);
    void __thiscall Apply(void* src, void* x);
};
typedef void* (__thiscall *VF1)(void*);
typedef int   (__thiscall *VFI)(void*);
static float Curve(void* begin, void* end, float t)
{
    int n = (int)(((char*)end - (char*)begin) >> 2) - 1;
    if (n == 0)
        return *(float*)begin;
    float f = (float)(uint32_t)n * t;
    int i = (int)f;
    float frac = f - (float)i;
    float* base = (float*)begin;
    if (frac > 0.0f)
        return base[i] + (base[i + 1] - base[i]) * frac;
    return base[i];
}
struct Head14 { uint16_t w0, w2; float f4, f8, fC, f10; };
struct Buf30  { Head14 h; uint32_t m00, m04, m08, m0c, m10, m14, m18, m1c, m20; };
struct Tmp84
{
    uint32_t s00, s04, s08, s0c, s10, s14, s18, s1c;
    uint32_t s20, s24, s28, s2c, s30, s34, s38, s3c;
    uint32_t s40;
    void*    p44;        // 0x44
    uint32_t s48, s4c, s50, s54, s58, s5c, s60;
    uint32_t s64, s68, s6c, s70, s74, s78, s7c, s80;
    void* __thiscall New();
};
struct Vec84
{
    void* begin;         // 0x00
    void* end;           // 0x04
    void __thiscall Grow(void* e, uint32_t n, void* p);
    void __thiscall Erase(void* a, void* b);
    void __thiscall Reserve(uint32_t n);
};
struct Heap5
{
    uint32_t pad00[0x34 / 4];
    void*    p34;        // 0x34
    uint32_t pad38[(0x48 - 0x38) / 4];
    void*    p48;        // 0x48
    uint32_t pad4c[(0x5c - 0x4c) / 4];
    void*    p5c;        // 0x5c
    uint32_t pad60[(0x70 - 0x60) / 4];
    void*    p70;        // 0x70
    uint32_t pad74[(0x84 - 0x74) / 4];
    void*    p84;        // 0x84

    void __fastcall Release();
};
// ---- items of slice s00a84ca0 end

// ---- items of slice s00a86b30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gf_one;        // 0x01485720
extern float gfa;           // 0x016780dc
extern float gfb;           // 0x016780e0
extern float gfc;           // 0x016780e4
extern float gf_tenth;      // 0x01488874
extern float gf_neg_10000;  // 0x01418f90
extern float gf_pos_10000;  // 0x013f0620
extern char  g_default_matrix[];   // 0x01678188
extern float gf_def3c;   // 0x01457d54
typedef unsigned int uint;
struct ElemTail {
    int a, b, c, d, e, f;
    void __thiscall CopyFrom(const ElemTail* o);   // 0x006f50f0
    ElemTail& __thiscall operator=(const ElemTail& o);  // 0x006f5cd0
};
struct Elem {
    void* p0;        // +0x00
    int   pad4;      // +0x04 (not copied)
    void* p8;        // +0x08
    void* pc;        // +0x0c
    float f10;       // +0x10
    float f14, f18, f1c, f20, f24, f28, f2c, f30, f34;
    void* p38;       // +0x38
    void* p3c;       // +0x3c
    ElemTail tail;   // +0x40

    Elem* __thiscall CopyFrom(const Elem* o);
    Elem* __thiscall AssignFrom(const Elem* o);
};
struct ElemVec {
    Elem* begin;
    Elem* end;
    Elem* cap;
};
extern bool __cdecl WriteUint32(void* stream, const uint* v, int count, int endian);  // 0x0093aa70
extern void __cdecl WriteElem(void* stream, const Elem* e);                            // 0x00a7f1d0
void* __cdecl EAAllocate(unsigned size, const char* alloc, int a, int b, const char* file, int line); // 0x00f473a0
struct SimVectorF {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    __declspec(nothrow) ~SimVectorF() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator_delete__(mpBegin); }
};
struct SimVector58 {
    Elem* mpBegin;
    Elem* mpEnd;
    Elem* mpCapacity;
    void __thiscall FreeRange(Elem* first, Elem* last);   // 0x00a87300
    void __thiscall Insert(Elem* pos, unsigned count, const Elem* value);  // 0x00a87980
    SimVector58* __thiscall Assign(SimVector58* src);                      // 0x00a87b90
    void __thiscall EraseRange(Elem* first, Elem* last);                   // 0x00a87cd0
    void __thiscall Resize(unsigned n);
    __declspec(nothrow) ~SimVector58()
    {
        FreeRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};
struct Sim_s00a8_6b30 {
    char pad00[0x8];        // vptr + refcount
    char pad08[0x58];
    SimVectorF v60;         // +0x060
    char pad6c[0xc];
    SimVectorF v78;         // +0x078
    char pad84[0x8];
    SimVectorF v8c;         // +0x08c
    char pad98[0x8];
    SimVectorF va0;         // +0x0a0
    char pad_ac[0x20];
    SimVectorF vcc;         // +0x0cc
    char pad_d8[0x14];
    SimVectorF vec;         // +0x0ec
    char pad_f8[0xc];
    SimVector58 v104;       // +0x104
    char pad110[0x5c];
    SimVectorF v16c;        // +0x16c
};
struct Matrix3_s00a8_6b30 {
    char data[0x24];
    void __thiscall Assign(const void* m);   // 0x0041cb40
};
template <class T> static inline T& Fld(void* base, unsigned off) { return *(T*)((char*)base + off); }
struct TransOps {
    char data[0x38];
    TransOps* __thiscall Assign(const void* src);   // 0x00537dc0
};
extern TransOps* __cdecl MulTrans(TransOps* out, const void* a, const void* b);  // 0x007d5590
struct RefcThing {
    TransOps* __thiscall Assign(const void* src);   // 0x00537dc0
    unsigned short flags;    // +0x00
    unsigned short count;    // +0x02
    char pad04[0xc];
    float f10;               // +0x10
    char pad14[0x34];
    float f48;               // +0x48
};
struct Notifier {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void Notify(void* p);    // +0x14
};
struct SimOps {
    void __thiscall Apply(void* a2, void* a3);
};
struct VecInitStub { void __thiscall Init(int count, Elem** cap); };           // 0x00a87860
extern void* __cdecl VecDoAssign(void** out, Elem* begin, Elem* end, void* a, void* b); // 0x00a87340
struct VecAssigner {
    void* p0;
    void* p4;
    VecAssigner* __thiscall Assign(ElemVec* src);
};
extern Elem* __cdecl UninitCopy(Elem* first, Elem* last, Elem* dst);        // 0x00a87380
extern void  __cdecl DestroyRange3(Elem* first, Elem* last, Elem* mem);     // 0x00a87240
extern Elem* __cdecl FillElems(Elem* dst, unsigned count, const Elem* v);   // 0x00a87440
extern Elem* __cdecl CopyCtorElem(Elem* dst, const Elem* src);              // 0x00a87280
extern Elem* __cdecl CopyRange3(Elem* first, Elem* last, Elem* dst);        // 0x00a87470
extern void  __cdecl CopyBack3(Elem* first, Elem* last, Elem* dst);         // 0x00a874b0
extern void  __cdecl DestroyLocal3(Elem* first, Elem* last, const Elem* v); // 0x00a87810
extern Elem* __cdecl AllocCopyRange(unsigned count, Elem* first, Elem* last); // 0x00a878c0
// ---- items of slice s00a86b30 end

// ---- items of slice s00a85c00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_13f21d4[];
extern "C" char g_145812c[];
extern "C" char g_1458130[];
extern const float DAT_01485378;          // 0.0f
extern const float DAT_013ebca0;          // 0.0001f
extern const float DAT_01564f38;
extern const float DAT_01677fbc;
extern const float DAT_01677fc0;
extern const float DAT_01677fc4;
extern const float DAT_01678068[];        // 3x3 identity
extern "C" void FUN_007ed920(void* s, void* dst);                          // embed-reader
extern "C" float FUN_00a78f80(float x);                                    // exp/curve helper
extern const float DAT_01486110;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t  uint8;
struct Matrix3_s00a8_5c00 {
    float m[9];
    Matrix3_s00a8_5c00(const Matrix3_s00a8_5c00& o);            // 0x0041cb40
    Matrix3_s00a8_5c00& operator=(const Matrix3_s00a8_5c00& o);
};
struct FloatCurve {
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    uint32 mAllocator[2];
};
struct cIRefObj {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void SetHandle(uint32 h);
};
struct cDistributeDescInit;
struct cSimulatorWorld;
struct cDistributeSimulator {
    volatile uint32 mVtbl00;              // +0x000 (GmeIComponent / simulator)
    volatile uint32 mVtbl04;              // +0x004 (GmeRefCount)
    uint32 pad08;
    cDistributeDescInit* mDesc;           // +0x00c
    uint8  mActive;                       // +0x010
    uint8  pad11[3];
    uint16 mFlags14;                      // +0x014
    uint16 mModCount16;                   // +0x016
    float  mCenterX;                      // +0x018
    float  mCenterY;                      // +0x01c
    float  mCenterZ;                      // +0x020
    float  mRadius;                       // +0x024
    char   pad28[0x38 - 0x28];
    uint32 pad38[(0x4c - 0x38) / 4];
    float  mParam4c;                      // +0x04c
    float  mParam50;                      // +0x050
    float  mParam54;                      // +0x054
    float  mParam58;                      // +0x058
    float  mParam5c;                      // +0x05c
    float  mParam60;                      // +0x060
    float  mParam64;                      // +0x064
    float  mParam68;                      // +0x068
    float  mParam6c;                      // +0x06c
    float  mParam70;                      // +0x070
    float  mParam74;                      // +0x074
    float  mParam78;                      // +0x078
    uint8  mParam7c;                      // +0x07c
    char   pad7d[0x84 - 0x7d];
    float  mParam84;                      // +0x084
    cIRefObj* mpRef88;                    // +0x088
    cIRefObj* mpRef8c;                    // +0x08c
    void*  mHandle90;                     // +0x090
    char   pad94[0x98 - 0x94];
    long long mValueL;                    // +0x098 (int pair: lo = mParam98, hi = mParam9c)
    char   padA0[0xb0 - 0xa0];
    uint32 mHandleB0;                     // +0x0b0
    uint32 mHandleB4;                     // +0x0b4

    cDistributeSimulator(uint32 desc);                    // 0x00a86120
    void* Destroy(uint32 flags);                          // 0x00a86210
    void Initialize(int a, cSimulatorWorld* world, int c); // 0x00a86270
    void Update(float dt);                                // 0x00a86590

    bool OnMessage(int msg, int* pValue, int a3);         // 0x00a85ed0
    bool SetParams(int msg, float* p, int a3);            // 0x00a86050
    void SetEmitterFlags(bool on);                        // 0x00a860e0
    void Deactivate(int unused);                          // 0x00a86010
    void ReleaseEmitter();                                // 0x00a85fb0
};
struct cSimulatorWorld {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual cIRefObj* GetObjByIdx(uint8 idx);             // +0x24
    virtual void SlotA();
    virtual void SlotB();
    virtual void SlotC();
    virtual void SlotD();
    virtual void SlotE();
    virtual void SlotF();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot1a();
    virtual void Slot1b();
    virtual void Slot1c();
    virtual void Slot1d();
    virtual void Slot1e();
    virtual void Slot1f();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual cIRefObj* GetObjById(uint32 idLo, uint32 idHi); // +0x8c
};
void* EAAllocate(uint32 size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
struct RandomLCG_s00a8_5c00 { double RandomDoubleUniform(); };
extern RandomLCG_s00a8_5c00 sRandom_Swarm;           // 0x016778dc
extern "C" void FUN_00a85b00_s00a8_5c00(void* s, void* dst);                          // float-curve reader 2
extern "C" void FUN_00a6c7a0(int owner, int index, int* outCount, uint32** outPtr, int** outCount2);
struct cDistributeDescInit {
    volatile uint32 mVtbl00;              // +0x000
    volatile uint32 mVtbl04;              // +0x004
    uint32 mMask;                         // +0x008 (bitset; bit0 mode, bit1 map)
    uint8  mParam0c;                      // +0x00c
    uint8  mParam0d;                      // +0x00d
    uint16 mParam0e;                      // +0x00e
    uint32 mParam10;                      // +0x010
    uint32 mParam14;                      // +0x014
    uint8  mParam18;                      // +0x018
    uint8  mParam19;                      // +0x019
    uint8  mParam1a;                      // +0x01a
    uint8  mParam1b;                      // +0x01b
    uint16 mParam1c;                      // +0x01c
    uint16 pad1e;                         // +0x01e
    float  mParam20;                      // +0x020
    uint32 pad24[(0x28 - 0x24) / 4];
    uint32 mParam28;                      // +0x028
    uint32 mParam2c;                      // +0x02c
    float  mParam30;                      // +0x030
    FloatCurve mCurve34;                  // +0x034
    FloatCurve mCurve48;                  // +0x048
    FloatCurve mCurve5c;                  // +0x05c
    FloatCurve mCurve70;                  // +0x070
    FloatCurve mCurve84;                  // +0x084
    float  mParam98;                      // +0x098
    float  mParam9c;                      // +0x09c
    float  mParamA0;                      // +0x0a0
    float  mParamA4;                      // +0x0a4
    float  mParamA8;                      // +0x0a8
    float  mParamAC;                      // +0x0ac
    uint32 mParamB0;                      // +0x0b0
    uint32 mParamB4;                      // +0x0b4

    cDistributeDescInit();
};
static inline float* AllocFloats(int count) {
    float* p = (float*)EAAllocate(count * 4, "EASTL", 0, 0, "EASTL/allocator.h", 0xd1);
    return p;
}
struct cDescIO {
    uint32 pad00[2];
    uint32 mMask;                         // +0x08 (low 3 bits kept)
    uint8  mParam0c;                      // +0x0c
    uint8  mParam0d;                      // +0x0d
    uint16 pad0e;                         // +0x0e
    FloatCurve mCurve10;                  // +0x10
    uint32 pad24[(0x30 - 0x24) / 4];
    uint32 mParam30;                      // +0x30
    FloatCurve mCurve34;                  // +0x34
    FloatCurve mCurve48;                  // +0x48
    FloatCurve mCurve5c;                  // +0x5c
    FloatCurve mCurve70;                  // +0x70
    FloatCurve mCurve84;                  // +0x84
    uint32 mParam98;                      // +0x98
    uint32 mParam9c;                      // +0x9c
    uint32 mParamA0;                      // +0xa0
    uint32 mParamA4;                      // +0xa4
    uint32 mParamA8;                      // +0xa8
    uint32 mParamAC;                      // +0xac
};
// ---- items of slice s00a85c00 end

// @ 0x00a81310
void EA::Swarm::cSurfaceDecalManager::SetSurface(void* surface, void* transform)
{
    char* self = (char*)this;

    if (*(void**)(self + 0x10) != 0) {
        void* cur = *(void**)(self + 0x10);
        void** vt = *(void***)cur;
        ((void(__thiscall*)(void*, u32))vt[9])(cur, *(u32*)(self + 0x70));  // slot 0x24
        // clear the 0x70 vector: memmove(begin, end, 0) then end = begin
        *(void**)(self + 0x74) = *(void**)(self + 0x70);
    }

    void* old = *(void**)(self + 0x10);
    if (surface != old) {
        if (surface) ((void(__thiscall*)(void*))(*(void***)surface)[1])(surface);  // AddRef
        *(void**)(self + 0x10) = surface;
        if (old) ((void(__thiscall*)(void*))(*(void***)old)[0])(old);              // Release
    }

    void* s = *(void**)(self + 0x10);
    if (s == 0) return;

    int count = ((int(__thiscall*)(void*))(*(void***)s)[7])(s);                   // slot 0x1c
    char* vec = self + 0x70;
    ((ExtCallees*)vec)->resize(count);

    float* data = *(float**)(self + 0x70);
    void** vt = *(void***)s;
    if (transform != 0) {
        Matrix3 m1, m2;
        float v[3];
        v[0] = DAT_0167776c; v[1] = DAT_01677770; v[2] = DAT_01677774;
        m1 = *(Matrix3*)DAT_01677818;
        m2 = *(Matrix3*)DAT_01677818;
        ((void(__thiscall*)(void*, void*, Matrix3*, Matrix3*, float*))vt[8])(
            s, transform, &m1, &m2, data);
    } else {
        Matrix3 m1, m2;
        m1 = *(Matrix3*)DAT_01677818;
        m2 = *(Matrix3*)DAT_01677818;
        ((void(__thiscall*)(void*, void*, Matrix3*, Matrix3*, float*))vt[8])(
            s, self + 0x18, &m1, &m2, data);
    }
}

// @ 0x00a81530
void* __fastcall FUN_00a81530(void* table)
{
    int i = 0;
    float scale = DAT_01485720 / DAT_0167790c;
    float* t = (float*)table;
    do {
        float a = (float)i * scale;
        t[i * 2 + 0] = (float)sin((double)a);
        t[i * 2 + 1] = (float)cos((double)a);
        ++i;
    } while (i < 16);
    return table;}

// @ 0x00a81580
float* FUN_00a81580(float* p, float* box)
{
    float cx = (box[3] + box[0]) * 0.5f;
    float cy = (box[4] + box[1]) * 0.5f;
    float cz = (box[5] + box[2]) * 0.5f;
    float ex = box[3] - cx;
    float ey = box[4] - cy;
    float ez = box[5] - cz;
    ex *= ex; ey *= ey; ez *= ez;
    float ix = ex <= 0.0f ? 0.0f : 1.0f / ex;
    float iy = ey <= 0.0f ? 0.0f : 1.0f / ey;
    float iz = ez <= 0.0f ? 0.0f : 1.0f / ez;
    float dx, dy, dz;
    do {
        FUN_007cdbe0(p, box);
        dx = p[0] - cx;
        dy = p[1] - cy;
        dz = p[2] - cz;
    } while (1.0f < ix * (dx * dx) + iy * (dy * dy) + iz * (dz * dz));
    return p;
}

// @ 0x00a816d0
void FUN_00a816d0(float* out, float* box)
{
    float x, y, z;
    do {
        x = (float)(g_sRandom.RandomDoubleUniform() * 2.0 - 1.0);
        y = (float)(g_sRandom.RandomDoubleUniform() * 2.0 - 1.0);
        z = (float)(g_sRandom.RandomDoubleUniform() * 2.0 - 1.0);
    } while (x * x + y * y + z * z > 1.0f);
    out[0] = ((box[3] - box[0]) * x + (box[0] + box[3])) * 0.5f;
    out[1] = ((box[4] - box[1]) * y + (box[1] + box[4])) * 0.5f;
    out[2] = ((box[5] - box[2]) * z + (box[2] + box[5])) * 0.5f;
}

// @ 0x00a817c0
void FUN_00a817c0(float* out, float* box, float radius)
{
    float x, y, z, len, t;
    do {
        x = (float)(g_sRandom.RandomDoubleUniform() * 2.0 - 1.0);
        y = (float)(g_sRandom.RandomDoubleUniform() * 2.0 - 1.0);
        z = (float)(g_sRandom.RandomDoubleUniform() * 2.0 - 1.0);
        len = sqrtf(x * x + y * y);
        t = len - 0.5f;
    } while (0.25f - t * t < z * z);
    float s = radius + (1.0f - radius) / sqrtf(x * x + y * y);
    out[0] = ((box[3] - box[0]) * (x * s) + (box[0] + box[3])) * 0.5f;
    out[1] = ((box[4] - box[1]) * (y * s) + (box[1] + box[4])) * 0.5f;
    out[2] = ((box[5] - box[2]) * (z * radius) + (box[2] + box[5])) * 0.5f;
}

// @ 0x00a818f0
void FUN_00a818f0(float* in, float* out)
{
    out[3] = in[0]; out[4] = in[1]; out[5] = in[2];
    float y  = in[1];
    float nx = -in[0];
    float len = sqrtf(nx * nx + y * y);
    float c0, c1, c2;
    if (len <= 0.0f) {
        out[0] = 0.0f; out[1] = 1.0f; out[2] = 0.0f;
        c0 = 1.0f; c1 = 0.0f; c2 = 0.0f;
    } else {
        float inv = 1.0f / len;
        float a = y * inv;
        float b = inv * nx;
        float c = inv * 0.0f;
        out[0] = a; out[1] = b; out[2] = c;
        c0 = in[2] * b - in[1] * c;
        c1 = in[0] * c - in[2] * a;
        c2 = in[1] * a - in[0] * b;
    }
    out[6] = c0; out[7] = c1; out[8] = c2;
}

// @ 0x00a81a20
void FUN_00a81a20(float* in, float* out)
{
    out[0] = in[0]; out[1] = in[1]; out[2] = in[2];
    float a = in[0];
    float b = -in[1];
    float len = sqrtf(a * a + b * b);
    float c0, c1, c2;
    if (len <= 0.0f) {
        out[3] = 1.0f; out[4] = 0.0f; out[5] = 0.0f;
        c0 = 0.0f; c1 = 1.0f; c2 = 0.0f;
    } else {
        float inv = 1.0f / len;
        float u = inv * b;
        float v = a * inv;
        float w = inv * -0.0f;
        out[3] = u; out[4] = v; out[5] = w;
        c0 = in[1] * w - in[2] * v;
        c2 = in[0] * v - in[1] * u;
        c1 = in[2] * u - in[0] * w;
    }
    out[6] = c0; out[7] = c1; out[8] = c2;
}

// @ 0x00a81b80
void FUN_00a81b80(float* in, float* out)
{
    out[6] = in[0]; out[7] = in[1]; out[8] = in[2];
    float ax = in[0], ay = in[1], az = in[2];
    if (fabsf(ay) < fabsf(ax)) {
        float nx = -ax;
        float nz = -az;
        float inv = 1.0f / sqrtf(nz * nz + nx * nx);
        float u = nx * inv;
        float v = inv * nz;
        float w = inv * -0.0f;
        out[3] = ay * u - az * w;
        out[4] = az * v - ax * u;
        out[0] = v;
        out[5] = ax * w - ay * v;
        out[1] = w;
        out[2] = u;
    } else {
        float ny = -ay;
        float inv = 1.0f / sqrtf(az * az + ny * ny);
        float u = az * inv;
        float v = ny * inv;
        float w = inv * 0.0f;
        out[0] = az * u - ay * v;
        out[1] = ax * v - az * w;
        out[3] = w;
        out[2] = ay * w - ax * u;
        out[4] = u;
        out[5] = v;
    }
}

// @ 0x00a84460
void* WriteTransform(IOStream* s, void* v)
{
    char* range = (char*)v;
    uint32_t n = (uint32_t)((*(char**)(range + 4) - *(char**)range) / 0xc);
    WriteV32(s, n);
    for (uint32_t i = 0; i < n; ++i) {
        char* e = *(char**)range + i * 0xc;
        WriteF32(s, ((float*)e)[0]);
        WriteF32(s, ((float*)e)[1]);
        WriteF32(s, ((float*)e)[2]);
    }
    return s;
}

// @ 0x00a84510
void WriteRec(IOStream* s, void* v)
{
    char* p = (char*)v;
    WriteBool(s, *(bool*)p);                                   // mCmptType
    WriteV32(s, *(const uint32_t*)(p + 4));                    // mFlags (16:16)
    FUN_007d01f0(s, p + 8);                                    // mLocalXform
    WriteBool(s, *(bool*)(p + 0x40));                          // mLODBegin
    WriteBool(s, *(bool*)(p + 0x41));                          // mLODEnd
    WriteTransform(s, p + 0x44);                               // mLODScales
    WriteF32(s, *(float*)(p + 0x58));                          // mEmitScaleBegin
    WriteF32(s, *(float*)(p + 0x5c));                          // mEmitScaleEnd
    WriteF32(s, *(float*)(p + 0x60));                          // mMassScaleBegin
    WriteF32(s, *(float*)(p + 0x64));                          // mMassScaleEnd
    WriteF32(s, *(float*)(p + 0x68));                          // mSizeScaleBegin
    WriteF32(s, *(float*)(p + 0x6c));                          // mSizeScaleEnd
    WriteV32(s, *(const uint32_t*)(p + 0x70));                 // mAppFlags
    WriteV32(s, *(const uint32_t*)(p + 0x74));                 // mAppFlagsMask
    WriteV16(s, *(uint16_t*)(p + 0x78));                       // mSelectionGroup
    WriteV16(s, *(uint16_t*)(p + 0x7a));                       // mSelectionChance
    WriteF32(s, *(float*)(p + 0x7c));                          // mTimeScale
    WriteV32(s, *(const uint32_t*)(p + 0x80));                 // mDescIndex
}

// @ 0x00a846c0
void* WriteRecList(IOStream* s, void* v)
{
    char* range = (char*)v;
    uint32_t n = (uint32_t)((*(char**)(range + 4) - *(char**)range) / 0x84);
    WriteV32(s, n);
    for (uint32_t i = 0; i < n; ++i)
        WriteRec(s, *(char**)range + i * 0x84);
    return s;
}

// @ 0x00a84720
void* WriteDescRec(IOStream* s, void* v)
{
    char* p = (char*)v;
    WriteV32(s, *(const uint32_t*)(p + 0x00));
    WriteV32(s, *(const uint32_t*)(p + 0x04));
    WriteV32(s, *(const uint32_t*)(p + 0x08));
    ((StreamW*)s)->write(p + 0x0c, 8);
    WriteF32(s, *(float*)(p + 0x14));
    WriteBool(s, *(bool*)(p + 0x18));
    FUN_007d0250(s, p + 0x1c);
    ((StreamW*)s)->write(p + 0x30, 0xc);
    WriteV32(s, *(const uint32_t*)(p + 0x40));
    return WriteRecList(s, p + 0x44);
}

// @ 0x00a84850
void* ReadLODScales(IOStream* s, void* v)
{
    uint32_t n = 0;
    ReadInt32(s, &n, 1, 0);
    ((ResizableVec*)v)->resize((int)n);                        // 0x00a6f010
    for (uint32_t i = 0; i < n; ++i) {
        char* e = *(char**)v + i * 0xc;
        ReadInt32(s, e, 1, 0);
        ReadInt32(s, e + 4, 1, 0);
        ReadInt32(s, e + 8, 1, 0);
    }
    return s;
}

// @ 0x00a848d0
void ReadDescRec(IOStream* s, void* v)
{    uint8_t b;
    ReadUint8(s, &b, 1);
    char* p = (char*)v;
    *(uint32_t*)p = b & 0xff;
    ReadInt32(s, &v, 1, 0);
    *(uint32_t*)(p + 4) = (u32)v & 0x1ff;
    char* q = p + 8;                                           // cached base (ebx)
    ReadUint16(s, q, 1, 0);
    ReadInt32(s, q + 0x10, 1, 0);
    ((StreamR*)s)->read(q + 0x14, 0x24);
    ((StreamR*)s)->read(q + 4, 0xc);
    ReadUint8(s, p + 0x40, 1);
    ReadUint8(s, p + 0x41, 1);
    ReadLODScales(s, p + 0x44);
    ReadInt32(s, p + 0x58, 1, 0);
    ReadInt32(s, p + 0x5c, 1, 0);
    ReadInt32(s, p + 0x60, 1, 0);
    ReadInt32(s, p + 0x64, 1, 0);
    ReadInt32(s, p + 0x68, 1, 0);
    ReadInt32(s, p + 0x6c, 1, 0);
    ReadInt32(s, p + 0x70, 1, 0);
    ReadInt32(s, p + 0x74, 1, 0);
    ReadUint16(s, p + 0x78, 1, 0);
    ReadUint16(s, p + 0x7a, 1, 0);
    ReadInt32(s, p + 0x7c, 1, 0);
    ReadInt32(s, p + 0x80, 1, 0);}

// @ 0x00a84a80
void ResizeDescRecs(void* self, u32 n, const void* val, void* out)
{
    char* v = (char*)self;
    u32 cap = (u32)((*(char**)(v + 8) - *(char**)(v + 4)) / 0x84);
    if (cap < n) {
        char* begin = *(char**)v;
        char* end = *(char**)(v + 4);
        u32 have = (u32)((end - begin) / 0x84);
        u32 want = have * 2;
        if (want == 0) want = 1;
        u32 total = have + n;
        if (total > want) want = total;
        char* mem = want ? (char*)EAAllocate(want * 0x84, "EASTL", 0, 0,
                          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
                        : 0;
        void* first = (void*)FUN_00a6e9a0(begin, (void*)val, mem);
        FUN_00a6e460(begin, (void*)val, mem);
        FUN_00a847f0(first, n, val);
        void* mid = (void*)FUN_00a6e9a0((void*)val, end, (char*)first + n * 0x84);
        FUN_00a6e460((void*)val, end, (char*)first + n * 0x84);
        if (begin && ((int*)begin)[-1] != 0) operator delete(begin);
        *(char**)v = mem;
        *(char**)(v + 4) = (char*)mid;
        *(char**)(v + 8) = mem + want * 0x84;
        return;
    }
    if (n != 0) {
        FUN_00a6a2f0(out, val);
        char* end = *(char**)(v + 4);
        u32 have = (u32)((end - (char*)val) / 0x84);
        char* inserted;
        if (n < have) {
            char* last = end - n * 0x84;
            FUN_00a6a9c0(out, last, end, end, out);
            *(char**)(v + 4) += n * 0x84;
            FUN_00a6eab0((void*)val, last, end);
            inserted = (char*)val + n * 0x84;
        } else {
            FUN_00a847f0(end, n - have, out);
            *(char**)(v + 4) += (n - have) * 0x84;
            FUN_00a6a9c0(out, (void*)val, end, *(char**)(v + 4), out);
            *(char**)(v + 4) += have * 0x84;
            inserted = end;
        }
        FUN_00a84820((void*)val, inserted, out);
    }
}

// @ 0x00a84ca0
void __thiscall Vec84::Reserve(uint32_t n)
{
    if (n > (uint32_t)(((char*)this->end - (char*)this->begin) / 0x84)) {
        Tmp84 tmp;
        void* p = tmp.New();
        this->Grow(this->end,
                   n - (uint32_t)(((char*)this->end - (char*)this->begin) / 0x84), p);
        if (tmp.p44 != 0 && *(int32_t*)((char*)tmp.p44 - 4) != 0)
            operator_delete__(tmp.p44);
    } else {
        this->Erase((char*)this->begin + n * 0x84, this->end);
    }
}

// @ 0x00a84da0
extern "C" void FUN_00a84da0(void* s, void* unused, void* d)
{
    uint32_t tmp;
    FUN_0093a780(s, &tmp, 1, 0);
    *(uint32_t*)((char*)d + 0x00) = tmp & 0x3fffff;
    FUN_0093a780(s, (char*)d + 0x04, 1, 0);
    FUN_0093a780(s, (char*)d + 0x08, 1, 0);
    (*(void (__thiscall**)(void*, void*, int))(*(uint32_t**)s + 0xc))(s, (char*)d + 0x0c, 8);
    FUN_0093a780(s, (char*)d + 0x14, 1, 0);
    FUN_0093a6c0(s, (char*)d + 0x18, 1);
    FUN_007d27d0(s, (char*)d + 0x1c);
    (*(void (__thiscall**)(void*, void*, int))(*(uint32_t**)s + 0xc))(s, (char*)d + 0x30, 0xc);
    FUN_0093a780(s, (char*)d + 0x40, 1, 0);
    FUN_00a84d40(s, (char*)d + 0x44);
}

// @ 0x00a84e50
void __fastcall Cfg::Release()
{
    if (this->arr8c != 0 && *(int32_t*)((char*)this->arr8c - 4) != 0)
        operator_delete__(this->arr8c);
    if (this->arr78 != 0 && *(int32_t*)((char*)this->arr78 - 4) != 0)
        operator_delete__(this->arr78);
    if (this->arr64 != 0 && *(int32_t*)((char*)this->arr64 - 4) != 0)
        operator_delete__(this->arr64);
    if (this->arr50 != 0 && *(int32_t*)((char*)this->arr50 - 4) != 0)
        operator_delete__(this->arr50);
    if (this->arr3c != 0 && *(int32_t*)((char*)this->arr3c - 4) != 0)
        operator_delete__(this->arr3c);
    if (this->arr28 != 0 && *(int32_t*)((char*)this->arr28 - 4) != 0)
        operator_delete__(this->arr28);
    if (this->arr14 != 0 && *(int32_t*)((char*)this->arr14 - 4) != 0)
        operator_delete__(this->arr14);
    *(void**)this = (void*)g_13ef094;
}

// @ 0x00a84f00
Cfg* __fastcall Cfg::Ctor()
{
    volatile uint32_t* v = (volatile uint32_t*)this;
    v[1] = 0;                                          // 0x04
    v[0] = (int)g_1457fd8;                                  // 0x00
    v[2] = 0;                                          // 0x08
    *(volatile float*)((char*)this + 0x10) = 1.0f;
    *(volatile uint16_t*)((char*)this + 0x0c) = 0;
    v[5] = 0;
    v[6] = 0;
    v[7] = 0;
    v[0x0a] = 0;
    v[0x0b] = 0;
    v[0x0c] = 0;
    v[0x0f] = 0;
    v[0x10] = 0;
    v[0x11] = 0;
    v[0x14] = 0;
    v[0x15] = 0;
    v[0x16] = 0;
    v[0x19] = 0;
    v[0x1a] = 0;
    v[0x1b] = 0;
    v[0x1e] = 0;
    v[0x1f] = 0;
    v[0x20] = 0;
    v[0x23] = 0;
    v[0x24] = 0;
    v[0x25] = 0;
    v[0x28] = 0;
    v[0x29] = 0;
    *(volatile uint16_t*)((char*)this + 0xa8) = 0x100;
    return this;
}

// @ 0x00a84fb0
extern "C" void FUN_00a84fb0(void* s, int, char* d)
{
    uint32_t tmp;
    FUN_0093a780(s, &tmp, 1, 0);
    *(uint32_t*)(d + 0x08) = tmp & 0x3ff;
    FUN_0093a700(s, d + 0x0c, 1, 0);
    FUN_0093a780(s, d + 0x10, 1, 0);
    FUN_007d27d0(s, d + 0x14);
    FUN_007d27d0(s, d + 0x28);
    FUN_007d27d0(s, d + 0x3c);
    FUN_007d27d0(s, d + 0x50);
    FUN_007d27d0(s, d + 0x64);
    FUN_007d27d0(s, d + 0x78);
    FUN_007d27d0(s, d + 0x8c);
    FUN_0093a800(s, d + 0xa0, 1, 0);
    FUN_0093a700(s, d + 0xa8, 1, 0);
}

// @ 0x00a85070
void __thiscall Sim::SetCfg(void* c, void* d, void* e)
{
    void* o = (*(VF1*)(*(uint32_t**)c + 0x20 / 4))(c);
    this->h10 = (void*)(*(VFI*)(*(uint32_t**)o + 0x60 / 4))(o);
    (void)d; (void)e;
}

// @ 0x00a85090
extern "C" int FUN_00a85090(int a1, void* a2, int* out, int count)
{
    int r = 0;
    uint32_t lo = *(uint32_t*)((char*)a2 + 0xa0);
    uint32_t hi = *(uint32_t*)((char*)a2 + 0xa4);
    if ((lo & hi) != 0xffffffffu) {
        r = 1;
        if (count > 0) {
            out[0] = lo;
            out[1] = hi;
            out[2] = 8;
        }
    }
    (void)a1;
    return r;
}

// @ 0x00a850d0
void __thiscall Sim::Activate(bool)
{    if (this->b14 != 0)
        return;
    this->b14 = 1;
    if (this->h10 != 0) {
        if (Bit(this->cfg->flags, 2))
            (*(void (__thiscall**)(void*))(*(uint32_t**)this->h10 + 0x18 / 4))(this->h10);
        uint32_t f = this->cfg->flags;
        if (Bit(f, 4)) {
            if (Bit(f, 6)) {
                (*(void (__thiscall**)(void*, uint32_t, void*))(*(uint32_t**)this->h10 + 0x1c / 4))
                    (this->h10, this->cfg->wa8, (void*)((char*)this + 0x28));
            } else {
                (*(void (__thiscall**)(void*, uint32_t, void*))(*(uint32_t**)this->h10 + 0x1c / 4))
                    (this->h10, this->cfg->wa8, 0);
            }
        }
        this->i68 = -1;
        if (Bit(this->cfg->flags, 1)) {
            (*(void (__thiscall**)(void*, uint32_t, uint32_t))(*(uint32_t**)this->h10 + 0x0c / 4))
                (this->h10, this->cfg->a0, this->cfg->a4);
        } else if (this->cfg->f10 > 0.0f) {
            this->i68 = (*(int (__thiscall**)(void*, uint32_t, uint32_t))(*(uint32_t**)this->h10 + 0x10 / 4))
                (this->h10, this->cfg->a0, this->cfg->a4);
            if (this->i68 < 0) {
                this->b14 = 0;
                return;
            }
        }
    }
    this->f1c = 0.0f;
    this->f20 = 0.0f;
    if (this->cfg->f10 > 0.0f)
        this->f18 = 1.0f / this->cfg->f10;
    else
        this->f18 = 0.0f;
}

// @ 0x00a851d0
void __fastcall Sim::Sample()
{
    Cfg* c = this->cfg;
    if (c->arr64 != c->e64)
        this->f5c = Curve(c->arr64, c->e64, this->f1c);
    c = this->cfg;
    if (c->arr78 != c->e78)
        this->f60 = Curve(c->arr78, c->e78, this->f1c);
    c = this->cfg;
    if (c->arr8c != c->e8c)
        this->f64 = Curve(c->arr8c, c->e8c, this->f1c);
    Cfg* cc = this->cfg;
    void* h = this->h10;
    (*(void (__thiscall**)(void*, float, float, float, uint32_t))(*(uint32_t**)h + 0x08 / 4))
        (h, this->f5c, this->f60, this->f64, cc->w0c);
}

// @ 0x00a853b0
Sim* __thiscall Sim::Ctor(void* cfg)
{
    *(void**)((char*)this + 0x04) = (void*)0x13ef094;
    *(uint32_t*)((char*)this + 0x08) = 0;
    this->cfg = (Cfg*)cfg;
    this->f18 = 0.0f;
    this->f1c = 0.0f;
    this->f20 = 0.0f;
    *(void**)this = (void*)0x1458024;
    *(void**)((char*)this + 0x04) = (void*)0x14599e8;
    this->h10 = 0;
    this->b14 = 0;
    this->w26 = 0;
    this->w24 = 0;
    float a = *(float*)0x1677d7c;
    this->f28 = a;
    float b = *(float*)0x1677d80;
    this->f2c = b;
    float c = *(float*)0x1677d84;
    this->f30 = c;
    float d = *(float*)0x1485720;
    this->f34 = d;
    ((Mat3*)((char*)this + 0x38))->Assign((void*)0x1677e28);
    float k = *(float*)0x13eb1bc;
    this->f5c = k;
    this->f60 = k;
    this->f64 = k;
    this->i68 = -1;
    return this;
}

// @ 0x00a85460
void __thiscall Sim::Build()
{
    Xf local;
    *(float*)((char*)&local + 0x10) = this->f28;
    *(float*)((char*)&local + 0x14) = this->f2c;
    *(float*)((char*)&local + 0x18) = this->f30;
    *(float*)((char*)&local + 0x1c) = this->f34;
    *(uint16_t*)((char*)&local + 0x00) = this->w24;
    *(uint16_t*)((char*)&local + 0x02) = this->w26;
    ((Mat3*)((char*)&local + 0x14))->Assign((char*)this + 0x38);

    Cfg* c = this->cfg;
    if (c->arr14 != c->e14)
        local.RotateZ(Curve(c->arr14, c->e14, this->f1c) * *(float*)0x1677e14);

    c = this->cfg;
    if (c->arr28 != c->e28)
        local.PreRotateX(Curve(c->arr28, c->e28, this->f1c) * *(float*)0x1677e14);

    c = this->cfg;
    if (c->arr3c != c->e3c)
        local.RotateY(Curve(c->arr3c, c->e3c, this->f1c) * *(float*)0x1677e14);

    c = this->cfg;
    if (c->arr50 != c->e50)
        *(float*)((char*)&local + 0x0c) = Curve(c->arr50, c->e50, this->f1c) * *(float*)0x1677e14;

    Cfg* cc = this->cfg;
    void* h = this->h10;
    (*(void (__thiscall**)(void*, void*, uint32_t))(*(uint32_t**)h + 0x04 / 4))
        (h, &local, cc->w0c);
}

// Effect handle stand-in: the slots Sim::Deactivate calls.
struct SimEffectHandle {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void Stop(int32_t id);                         // +0x14
    virtual void Hide();                                   // +0x18
    virtual void Detach(uint32_t key, void* transform);    // +0x1c
};

// @ 0x00a85790
void __thiscall Sim::Deactivate(bool)
{
    if (this->b14 == 0)
        return;
    this->b14 = 0;
    if (this->h10 == 0)
        return;
    if (Bit(this->cfg->flags, 3) || Bit(this->cfg->flags, 5)) {
        if (this->cfg->flags & 1)
            this->Build();
        if (Bit(this->cfg->flags, 3))
            ((SimEffectHandle*)this->h10)->Hide();
        if (Bit(this->cfg->flags, 5)) {
            if (Bit(this->cfg->flags, 6))
                ((SimEffectHandle*)this->h10)->Detach(this->cfg->wa8, &this->f28);
            else
                ((SimEffectHandle*)this->h10)->Detach(this->cfg->wa8, 0);
        }
    }
    if (this->i68 >= 0) {
        ((SimEffectHandle*)this->h10)->Stop(this->i68);
        this->i68 = -1;
    }
}

// @ 0x00a85840
void __thiscall Sim::Apply(void* src, void* x)
{
    Buf30 buf;
    Head14* hx = (Head14*)x;
    buf.h.w0  = hx->w0;
    buf.h.w2  = hx->w2;
    buf.h.f4  = hx->f4;
    buf.h.f8  = hx->f8;
    buf.h.fC  = hx->fC;
    buf.h.f10 = hx->f10;
    ((Mat3*)&buf.m00)->Assign((char*)x + 0x14);
    ((Trn*)&buf)->PreTransformBy(src);
    ((SpTr*)((char*)this + 0x24))->Assign(&buf);
}

// @ 0x00a858c0
void __thiscall Sim::Tick(float dt, void* a, void* b)
{
    this->f1c = dt * this->f18 + this->f1c;
    if (this->f1c > 1.0f) {
        if (Bit(this->cfg->flags, 7)) {
            int i = (int)this->f1c;
            if (this->f1c < (float)i)
                i--;
            this->f1c = this->f1c - (float)i;
        } else {
            this->f1c = 1.0f;
        }
    }
    if (this->h10 != 0) {
        if (Bit(this->cfg->flags, 0))
            this->Build();
        if (this->h10 != 0 && Bit(this->cfg->flags, 9))
            this->Sample();
    }
    if (this->f18 == 0.0f || this->f1c == 1.0f) {
        if (Bit(this->cfg->flags, 8))
            (*(void (__thiscall**)(void*, void*))(*(uint32_t**)this + 0x0c / 4))(this, 0);
    }
    (void)a; (void)b;
}

// @ 0x00a85a20
extern "C" void* FUN_00a85a20(void* s, void* src)
{
    uint64_t q;
    uint8_t b;
    q = *(uint64_t*)src;
    FUN_0093ab10(s, &q, 1, 0);
    b = *(uint8_t*)((char*)src + 8);
    FUN_0093a9a0(s, &b, 1);
    b = *(uint8_t*)((char*)src + 9);
    FUN_0093a9a0(s, &b, 1);
    b = *(uint8_t*)((char*)src + 0xa);
    FUN_0093a9a0(s, &b, 1);
    b = *(uint8_t*)((char*)src + 0xb);
    FUN_0093a9a0(s, &b, 1);
    uint32_t dw = *(uint16_t*)((char*)src + 0xc);
    FUN_0093a9d0(s, &dw, 1, 0);
    float fl = *(float*)((char*)src + 0x10);
    FUN_0093aa70(s, &fl, 1, 0);
    q = *(uint64_t*)((char*)src + 0x18);
    FUN_0093ab10(s, &q, 1, 0);
    return s;
}

// @ 0x00a85b00
extern "C" void* FUN_00a85b00(void* s, void* d)
{
    FUN_0093a800(s, d, 1, 0);
    FUN_0093a6c0(s, (char*)d + 8, 1);
    FUN_0093a6c0(s, (char*)d + 9, 1);
    FUN_0093a6c0(s, (char*)d + 0xa, 1);
    FUN_0093a6c0(s, (char*)d + 0xb, 1);
    FUN_0093a700(s, (char*)d + 0xc, 1, 0);
    FUN_0093a780(s, (char*)d + 0x10, 1, 0);
    FUN_0093a800(s, (char*)d + 0x18, 1, 0);
    return s;
}

// @ 0x00a85b80
void __fastcall Heap5::Release()
{
    if (this->p84 != 0 && *(int32_t*)((char*)this->p84 - 4) != 0)
        operator_delete__(this->p84);
    if (this->p70 != 0 && *(int32_t*)((char*)this->p70 - 4) != 0)
        operator_delete__(this->p70);
    if (this->p5c != 0 && *(int32_t*)((char*)this->p5c - 4) != 0)
        operator_delete__(this->p5c);
    if (this->p48 != 0 && *(int32_t*)((char*)this->p48 - 4) != 0)
        operator_delete__(this->p48);
    if (this->p34 != 0 && *(int32_t*)((char*)this->p34 - 4) != 0)
        operator_delete__(this->p34);
    *(void**)this = (void*)g_13ef094;
}

// @ 0x00a85c00
cDistributeDescInit::cDistributeDescInit()
{
    mVtbl04 = 0;
    mVtbl00 = 0x014580ec;
    mMask = 0;
    mParam0c = 0;
    mParam0d = 0;
    mParam0e = 0;
    mParam10 = 0xffffffff;
    mParam14 = 0xffffffff;
    mParam18 = 0;
    mParam19 = 0;
    mParam1a = 0;
    mParam1b = 0;
    mParam1c = 0;
    mParam20 = 0.0f;
    mParam28 = 0xffffffff;
    mParam2c = 0xffffffff;
    mParam30 = DAT_01486110;

    mCurve34.mpBegin = AllocFloats(1);
    mCurve34.mpCapacity = mCurve34.mpBegin + 1;
    mCurve34.mpBegin[0] = 0.0f;
    mCurve34.mpEnd = mCurve34.mpBegin + 1;

    mCurve48.mpBegin = AllocFloats(1);
    mCurve48.mpCapacity = mCurve48.mpBegin + 1;
    mCurve48.mpBegin[0] = DAT_01485720;
    mCurve48.mpEnd = mCurve48.mpBegin + 1;

    mCurve5c.mpBegin = AllocFloats(1);
    mCurve5c.mpCapacity = mCurve5c.mpBegin + 1;
    mCurve5c.mpBegin[0] = DAT_01485720;
    mCurve5c.mpEnd = mCurve5c.mpBegin + 1;

    mCurve70.mpBegin = AllocFloats(3);
    mCurve70.mpEnd = mCurve70.mpBegin;
    mCurve70.mpCapacity = mCurve70.mpBegin + 3;
    if (mCurve70.mpBegin != 0) {
        mCurve70.mpBegin[0] = DAT_01485720;
        mCurve70.mpBegin[1] = DAT_01485720;
        mCurve70.mpBegin[2] = DAT_01485720;
    }
    mCurve70.mpEnd = mCurve70.mpBegin + 3;

    mCurve84.mpBegin = AllocFloats(1);
    mCurve84.mpCapacity = mCurve84.mpBegin + 1;
    mCurve84.mpBegin[0] = DAT_01485720;
    mCurve84.mpEnd = mCurve84.mpBegin + 1;

    mParam98 = 0;
    mParam9c = 0;
    mParamA0 = 0;
    mParamA4 = 0x3f800000;
    mParamA8 = 0;
    mParamAC = 0;
    mParamB0 = 0xffffffff;
    mParamB4 = 0xffffffff;
}

// @ 0x00a85dd0
void ReadDesc(void* stream, void* dst)
{
    cDescIO* d = (cDescIO*)dst;
    uint32 tmp = 0;
    FUN_0093a780(stream, &tmp, 1, 0);
    d->mMask = tmp & 7;
    FUN_0093a6c0(stream, &d->mParam0c, 1);
    FUN_0093a6c0(stream, &d->mParam0d, 1);
    FUN_00a85b00_s00a8_5c00(stream, &d->mCurve10);
    FUN_0093a780(stream, &d->mParam30, 1, 0);
    FUN_007d27d0(stream, &d->mCurve34);
    FUN_007d27d0(stream, &d->mCurve48);
    FUN_007d27d0(stream, &d->mCurve5c);
    FUN_007ed920(stream, &d->mCurve70);
    FUN_007d27d0(stream, &d->mCurve84);
    FUN_0093a780(stream, &d->mParam98, 1, 0);
    FUN_0093a780(stream, &d->mParam9c, 1, 0);
    FUN_0093a780(stream, &d->mParamA0, 1, 0);
    FUN_0093a780(stream, &d->mParamA4, 1, 0);
    // d->mParamA8: 8 raw bytes read through the stream vtable slot +0x30.
    (*(void(__thiscall**)(void*, void*, int))(*(uint32*)stream + 0x30))(stream, (char*)dst + 0xa8, 8);
    FUN_0093a800(stream, (char*)dst + 0xb0, 1, 0);
}

// @ 0x00a85ed0
bool cDistributeSimulator::OnMessage(int msg, int* pValue, int a3)
{
    switch (msg) {
    case 1: {
        long long v = *pValue;
        if (mValueL != v) {
            mValueL = v;
            if (mActive) {
                (*(void(__thiscall**)(cDistributeSimulator*, int))(mVtbl00 + 0xc))(this, 1);
                (*(void(__thiscall**)(cDistributeSimulator*, int))(mVtbl00 + 8))(this, 0);
            }
        }
        return true;
    }
    default:
        return false;
    }
}

// @ 0x00a85f30
int EnumGroupOverrides(void* unused, char* obj, uint32* out, int limit)
{    int count = 0;
    FUN_00a6c7a0((int)(obj + 0x10), 0, &count, (uint32**)&out, (int**)&limit);
    uint64_t k = *(uint64_t*)(obj + 0xb0);
    if (k != 0xffffffffffffffffULL) {
        ++count;
        if (limit > 0) {
            *(uint64_t*)out = k;
            out[2] = 5;
        }
    }
    return count;}

// @ 0x00a85fb0
void cDistributeSimulator::ReleaseEmitter()
{
    if (mActive)
        (*(void(__thiscall**)(cDistributeSimulator*, int))(mVtbl00 + 0xc))(this, 1);
    if (mpRef88 != 0) {
        (*(void(__thiscall**)(cIRefObj*))(*(uint32*)mpRef88 + 0xc))(mpRef88);
        cIRefObj* p = mpRef88;
        if (p != 0) {
            mpRef88 = 0;
            (*(void(__thiscall**)(cIRefObj*))(*(uint32*)p + 4))(p);
        }
    }
    cIRefObj* q = mpRef8c;
    if (q != 0) {
        mpRef8c = 0;
        (*(void(__thiscall**)(cIRefObj*))(*(uint32*)q + 0xc))(q);
    }
}

// @ 0x00a86010
void cDistributeSimulator::Deactivate(int unused)
{
    if (mActive) {
        mActive = 0;
        if (mHandle90 != 0) {
            (*(void(__thiscall**)(cIRefObj*, void*))(*(uint32*)mpRef8c + 0x18))(mpRef8c, mHandle90);
            mHandle90 = 0;
        }
    }
}

// 0x00a86050: not byte-exact; the byte-exact version is the lifted one in match/slices/s00a86050/s00a86050.cpp
bool cDistributeSimulator::SetParams(int msg, float* p, int a3)
{
    switch (msg) {
    case 4:
        mParam78 = p[0];
        return true;
    case 0xc: {
        float num = p[4] - p[1];
        float denom = p[3] - p[0];
        mParam74 = num / denom;
        mParam50 = 0.0f;
        if ((mDesc->mMask & 1) != 0)
            mParam70 = denom;
        mParam7c = 1;
        return true;
    }
    case 0x101:
        mParam54 = p[1];
        mParam5c = p[2];
        mParam58 = p[4];
        mParam60 = p[5];
        return true;
    default:
        return false;
    }
}

// @ 0x00a860e0
void cDistributeSimulator::SetEmitterFlags(bool on)
{
    void* h = mHandle90;
    if (h == 0)
        return;
    if (on)
        *(uint32*)((char*)h + 0x64) |= 1;
    else
        *(uint32*)((char*)h + 0x64) &= 0xfffffffe;
    mpRef8c->SetHandle((uint32)mHandle90);
}

// @ 0x00a86120
cDistributeSimulator::cDistributeSimulator(uint32 desc)
{
    mVtbl04 = (int)g_13ef094;
    pad08 = 0;
    mVtbl00 = (int)g_1458130;
    mVtbl04 = (int)g_145812c;
    mDesc = (cDistributeDescInit*)desc;
    mActive = 0;
    mFlags14 = 0;
    mModCount16 = 0;
    mCenterX = DAT_01677fbc;
    mCenterY = DAT_01677fc0;
    mCenterZ = DAT_01677fc4;
    mRadius = DAT_01485720;
    *(Matrix3_s00a8_5c00*)((char*)this + 0x28) = *(const Matrix3_s00a8_5c00*)&DAT_01678068;
    float one = DAT_01485720;
    mParam54 = one;
    mParam58 = one;
    mParam5c = one;
    mParam60 = one;
    mParam7c = 0;
    mParam64 = one;
    mParam68 = one;
    mParam6c = one;
    mParam70 = one;
    mParam74 = one;
    mParam78 = one;
    mParam84 = one;
    mpRef88 = 0;
    mpRef8c = 0;
    _ReadWriteBarrier();
    mValueL = 0xffffffffffffffffLL;
    mHandle90 = 0;
}

// @ 0x00a86210
void* cDistributeSimulator::Destroy(uint32 flags)
{
    mVtbl00 = (int)g_1458130;
    mVtbl04 = (int)g_145812c;
    _ReadWriteBarrier();
    if (mpRef8c) {
        cIRefObj* r = mpRef8c;
        (*(void(__thiscall**)(cIRefObj*))(*(uint32*)r + 0xc))(r);
    }
    if (mpRef88 != 0)
        (*(void(__thiscall**)(cIRefObj*))(*(uint32*)mpRef88 + 4))(mpRef88);
    mVtbl00 = (int)g_13f21d4;
    mVtbl04 = (int)g_13ef094;
    if (flags & 1)
        operator_delete__(this);
    return this;
}

// @ 0x00a86270
void cDistributeSimulator::Initialize(int a, cSimulatorWorld* world, int c)
{
    cDistributeDescInit* d = mDesc;
    float minSize = DAT_013ebca0;
    const float* src = &d->mParam30;
    if (!(d->mParam30 > DAT_013ebca0))
        src = &minSize;
    mParam84 = DAT_01485720 / *src;

    // Randomised size-vary around 1.0, clamped to [1-vary, 1+vary].
    {
        double lo = 1.0 - d->mParam98;
        double hi = 1.0 + d->mParam98;
        double r = sRandom_Swarm.RandomDoubleUniform();
        double v = r * (hi - lo) + lo;
        if (v < hi) {
            if (v < lo) v = lo;
        } else {
            v = hi;
        }
        mParam64 = (float)v;
    }
    {
        double lo = 1.0 - d->mParam9c;
        double hi = 1.0 + d->mParam9c;
        double r = sRandom_Swarm.RandomDoubleUniform();
        double v = r * (hi - lo) + lo;
        if (v < hi) {
            if (v < lo) v = lo;
        } else {
            v = hi;
        }
        mParam68 = (float)v;
    }
    if (d->mParamA0 > DAT_01485378)
        mParam6c = FUN_00a78f80(d->mParamA0);
    else
        mParam6c = DAT_01485720;

    mParam4c = mParam68;

    cIRefObj* obj = world->GetObjByIdx(d->mParam0c);
    cIRefObj* old = mpRef8c;
    if (obj != old) {
        if (obj != 0)
            (*(void(__thiscall**)(cIRefObj*))(*(uint32*)obj + 8))(obj);
        mpRef8c = obj;
        if (old != 0)
            (*(void(__thiscall**)(cIRefObj*))(*(uint32*)old + 0xc))(old);
    }

    if ((d->mMask >> 1) & 1) {
        mParam7c = 1;
        cIRefObj* m = world->GetObjById(d->mParamB0, d->mParamB4);
        if (m != 0) {
            float v = DAT_01564f38;
            float pt[6];
            pt[0] = v;
            pt[1] = -v;
            pt[2] = v;
            pt[3] = v;
            pt[4] = -v;
            pt[5] = -v;
            (*(void(__thiscall**)(cIRefObj*, float*))(*(uint32*)m + 0x14))(m, &pt[1]);
            mFlags14 |= 4;
            mModCount16 += 1;
            float cx = (pt[2] + pt[0]) * 0.5f;
            float cy = (pt[3] + pt[1]) * 0.5f;
            float cz = (pt[4] + pt[0]) * 0.5f;
            mCenterX = cx;
            mCenterY = cy;
            mCenterZ = cz;
            float dx = pt[1] - pt[0];
            float dy = pt[3] - pt[1];
            mModCount16 += 1;
            mRadius = (dx <= dy) ? dx : dy;
        }
    }

    uint32 idLo = d->mParamB0;
    uint32 idHi = d->mParamB4;
    if ((idLo & idHi) != 0xffffffff) {
        cIRefObj* r = world->GetObjById(idLo, idHi);
        cIRefObj* old2 = mpRef88;
        if (r != old2) {
            if (r != 0)
                (*(void(__thiscall**)(cIRefObj*))(*(uint32*)r))(r);
            mpRef88 = r;
            if (old2 != 0)
                (*(void(__thiscall**)(cIRefObj*))(*(uint32*)old2 + 4))(old2);
        }
    }
    if (mpRef88 != 0)
        (*(void(__thiscall**)(cIRefObj*))(*(uint32*)mpRef88 + 8))(mpRef88);
}

// 0x00a870b0: not byte-exact; the byte-exact version is the lifted one in match/slices/s00a870b0/s00a870b0.cpp
void __thiscall SimOps::Apply(void* a2, void* a3)
{
    if (Fld<unsigned char>(this, 0x7c) != 0)
        return;
    TransOps tmp;
    TransOps* dst = (TransOps*)((char*)this + 0x14);
    TransOps* r = MulTrans(&tmp, a2, a3);
    dst->Assign(r);
    if (((Fld<unsigned>(Fld<void*>(this, 0x0c), 0x08) >> 2) % 2) == 0)
        return;
    TransOps* other = Fld<TransOps*>(this, 0x90);
    if (other == 0)
        return;
    other->Assign(dst);
    float f = *Fld<float*>(Fld<void*>(this, 0x0c), 0x48) * Fld<float>(this, 0x68);
    RefcThing* t = Fld<RefcThing*>(this, 0x90);
    t->flags |= 1;
    t->count++;
    f *= t->f10;
    t->f10 = f;
    Fld<RefcThing*>(this, 0x90)->f48 = *Fld<float*>(Fld<void*>(this, 0x0c), 0x34) * Fld<float>(this, 0x6c);
    Fld<Notifier*>(this, 0x8c)->Notify(Fld<RefcThing*>(this, 0x90));
}

// @ 0x00a871e0
void* __cdecl SerializeElems(void* stream, ElemVec* v)
{
    int count = (int)((char*)v->end - (char*)v->begin) / 0x58;
    int written = count;
    WriteUint32(stream, (const uint*)&written, 1, 0);
    for (uint i = 0; i < (uint)count; i++)
        WriteElem(stream, &v->begin[i]);
    return stream;
}

// @ 0x00a87280
Elem* __thiscall Elem::CopyFrom(const Elem* o)
{
    p0 = o->p0;
    p8 = o->p8;
    pc = o->pc;
    f10 = o->f10;
    f14 = o->f14;
    f18 = o->f18;
    f1c = o->f1c;
    f20 = o->f20;
    f24 = o->f24;
    f28 = o->f28;
    f2c = o->f2c;
    f30 = o->f30;
    f34 = o->f34;
    p38 = o->p38;
    p3c = o->p3c;
    tail.CopyFrom(&o->tail);
    return this;
}

// @ 0x00a873c0
Elem* __thiscall Elem::AssignFrom(const Elem* o)
{
    p0 = o->p0;
    p8 = o->p8;
    pc = o->pc;
    f10 = o->f10;
    f14 = o->f14;
    f18 = o->f18;
    f1c = o->f1c;
    f20 = o->f20;
    f24 = o->f24;
    f28 = o->f28;
    f2c = o->f2c;
    f30 = o->f30;
    f34 = o->f34;
    p38 = o->p38;
    p3c = o->p3c;
    tail = o->tail;
    return this;
}

// @ 0x00a874f0
void* __fastcall SimCtor(Sim_s00a8_6b30* self)
{
    float one = gf_one;
    unsigned short zlo = 0;
    unsigned short zhi = 0;
    Fld<unsigned>(self, 0x004) = 0;
    Fld<unsigned>(self, 0x000) = 0x01458270;
    Fld<unsigned>(self, 0x008) = 0;
    Fld<unsigned>(self, 0x00c) = 1;
    Fld<unsigned char>(self, 0x014) = 0;
    Fld<unsigned>(self, 0x018) = 0;
    Fld<unsigned char>(self, 0x01c) = 0;
    Fld<float>(self, 0x020) = one;
    Fld<unsigned>(self, 0x010) = 0xffffffff;
    Fld<unsigned short>(self, 0x026) = zhi;
    Fld<unsigned short>(self, 0x024) = zlo;
    Fld<float>(self, 0x028) = gfa;
    Fld<float>(self, 0x02c) = gfb;
    Fld<float>(self, 0x030) = gfc;
    Fld<float>(self, 0x034) = one;
    ((Matrix3_s00a8_6b30*)((char*)self + 0x38))->Assign(g_default_matrix);
    Fld<float>(self, 0x05c) = gf_tenth;
    Fld<unsigned>(self, 0x060) = 0;
    Fld<unsigned>(self, 0x064) = 0;
    Fld<unsigned>(self, 0x068) = 0;
    Fld<float>(self, 0x074) = 0.0f;
    Fld<unsigned>(self, 0x078) = 0;
    Fld<unsigned>(self, 0x07c) = 0;
    Fld<unsigned>(self, 0x080) = 0;
    Fld<unsigned>(self, 0x08c) = 0;
    Fld<unsigned>(self, 0x090) = 0;
    Fld<unsigned>(self, 0x094) = 0;
    Fld<unsigned>(self, 0x0a0) = 0;
    Fld<unsigned>(self, 0x0a4) = 0;
    Fld<unsigned>(self, 0x0a8) = 0;
    Fld<float>(self, 0x0b4) = 0.0f;
    Fld<float>(self, 0x0b8) = 0.0f;
    Fld<float>(self, 0x0bc) = 0.0f;
    Fld<float>(self, 0x0c0) = 0.0f;
    Fld<float>(self, 0x0c4) = 0.0f;
    Fld<float>(self, 0x0c8) = 0.0f;
    Fld<unsigned>(self, 0x0cc) = 0;
    Fld<unsigned>(self, 0x0d0) = 0;
    Fld<unsigned>(self, 0x0d4) = 0;
    Fld<float>(self, 0x0e0) = gfa;
    Fld<float>(self, 0x0e4) = gfb;
    Fld<float>(self, 0x0e8) = gfc;
    Fld<unsigned>(self, 0x0ec) = 0;
    Fld<unsigned>(self, 0x0f0) = 0;
    Fld<unsigned>(self, 0x0f4) = 0;
    Fld<float>(self, 0x100) = 0.0f;
    Fld<unsigned>(self, 0x104) = 0;
    Fld<unsigned>(self, 0x108) = 0;
    Fld<unsigned>(self, 0x10c) = 0;
    Fld<unsigned>(self, 0x118) = 0xffffffff;
    Fld<unsigned>(self, 0x11c) = 0xffffffff;
    Fld<unsigned>(self, 0x120) = 0xffffffff;
    Fld<unsigned>(self, 0x124) = 0xffffffff;
    Fld<unsigned>(self, 0x128) = 0xffffffff;
    Fld<unsigned>(self, 0x12c) = 0xffffffff;
    Fld<float>(self, 0x130) = gf_neg_10000;
    Fld<float>(self, 0x134) = gf_pos_10000;
    Fld<unsigned>(self, 0x138) = 0xffffffff;
    Fld<unsigned>(self, 0x13c) = 0xffffffff;
    Fld<unsigned char>(self, 0x140) = 0;
    Fld<unsigned char>(self, 0x141) = 0;
    Fld<unsigned char>(self, 0x142) = 0;
    Fld<unsigned char>(self, 0x143) = 0;
    Fld<unsigned>(self, 0x150) = 0xffffffff;
    Fld<unsigned>(self, 0x154) = 0xffffffff;
    Fld<float>(self, 0x148) = 0.0f;
    Fld<unsigned short>(self, 0x144) = 0;
    Fld<unsigned char>(self, 0x158) = 0;
    Fld<unsigned>(self, 0x15c) = 0;
    Fld<unsigned>(self, 0x160) = 0;
    Fld<unsigned>(self, 0x164) = 0;
    Fld<float>(self, 0x168) = 0.0f;
    Fld<unsigned>(self, 0x16c) = 0;
    Fld<unsigned>(self, 0x170) = 0;
    Fld<unsigned>(self, 0x174) = 0;
    return self;
}

// @ 0x00a87720
void __fastcall Sim_Dtor(Sim_s00a8_6b30* self)
{
    self->v16c.~SimVectorF();
    self->v104.~SimVector58();
    self->vec.~SimVectorF();
    self->vcc.~SimVectorF();
    self->va0.~SimVectorF();
    self->v8c.~SimVectorF();
    self->v78.~SimVectorF();
    self->v60.~SimVectorF();
    *(void**)self = (void*)g_13ef094;
}

// @ 0x00a87920
VecAssigner* __thiscall VecAssigner::Assign(ElemVec* src)
{
    int count = (int)((char*)src->end - (char*)src->begin) / 0x58;
    ((VecInitStub*)this)->Init(count, (Elem**)((char*)src + 0xc));
    VecDoAssign((void**)&src, src->begin, src->end, p0, src);
    p4 = src;
    return this;
}

// @ 0x00a87980
void __thiscall SimVector58::Insert(Elem* pos, unsigned count, const Elem* value)
{
    unsigned cap = (unsigned)(((char*)mpCapacity - (char*)mpBegin) / 0x58);
    if (cap < count) {
        unsigned oldCount = (unsigned)(((char*)mpEnd - (char*)mpBegin) / 0x58);
        unsigned newCap = oldCount * 2;
        if (oldCount == 0)
            newCap = 1;
        unsigned needed = oldCount + count;
        if (newCap < needed)
            newCap = needed;
        Elem* newMem = 0;
        if (newCap != 0)
            newMem = (Elem*)EAAllocate(newCap * 0x58, "EASTL", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        Elem* newPos = UninitCopy(mpBegin, pos, newMem);
        DestroyRange3(mpBegin, pos, newMem);
        Elem* newEnd = FillElems(newPos, count, value);
        newEnd = UninitCopy(pos, mpEnd, newEnd);
        DestroyRange3(pos, mpEnd, newMem + count);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
        mpBegin = newMem;
        mpEnd = newEnd;
        mpCapacity = newMem + newCap;
        return;
    }
    if (count == 0)
        return;
    Elem tmp;
    CopyCtorElem(&tmp, value);
    Elem* oldEnd = mpEnd;
    unsigned after = (unsigned)(((char*)oldEnd - (char*)pos) / 0x58);
    if (count < after) {
        Elem* cut = oldEnd - count;
        VecDoAssign((void**)&pos, cut, oldEnd, oldEnd, pos);
        mpEnd = oldEnd + count;
        CopyBack3(pos, cut, oldEnd);
        Elem* newEnd = pos + count;
        DestroyLocal3(pos, newEnd, &tmp);
    } else {
        FillElems(oldEnd, count - after, &tmp);
        mpEnd = oldEnd + (count - after);
        VecDoAssign((void**)&pos, pos, oldEnd, mpEnd, pos);
        mpEnd = mpEnd + after;
        DestroyLocal3(pos, oldEnd, &tmp);
    }
}

// @ 0x00a87b90
SimVector58* __thiscall SimVector58::Assign(SimVector58* src)
{
    if (src == this)
        return this;
    unsigned srcCount = (unsigned)(((char*)src->mpEnd - (char*)src->mpBegin) / 0x58);
    unsigned myCap = (unsigned)(((char*)mpCapacity - (char*)mpBegin) / 0x58);
    if (myCap < srcCount) {
        Elem* nb = AllocCopyRange(srcCount, src->mpBegin, src->mpEnd);
        FreeRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
        mpEnd = nb + srcCount;
        mpBegin = nb;
        mpCapacity = nb + srcCount;
        return this;
    }
    unsigned myCount = (unsigned)(((char*)mpEnd - (char*)mpBegin) / 0x58);
    if (myCount < srcCount) {
        CopyRange3(src->mpBegin, src->mpBegin + myCount, mpBegin);
        VecDoAssign((void**)&src, src->mpBegin + myCount, src->mpEnd, mpEnd, src->mpEnd);
        mpEnd = mpBegin + srcCount;
    } else {
        Elem* e = CopyRange3(src->mpBegin, src->mpEnd, mpBegin);
        FreeRange(e, mpEnd);
        mpEnd = mpBegin + srcCount;
    }
    return this;
}

// @ 0x00a87e60
void __thiscall SimVector58::Resize(unsigned n)
{
    Elem* begin = mpBegin;
    unsigned want = n;
    int count = (int)((char*)mpEnd - (char*)begin) / 0x58;
    if (want > (unsigned)count) {
        Elem def;
        Fld<unsigned>(&def, 0x00) = 0;
        Fld<unsigned>(&def, 0x40) = 0;
        Fld<unsigned>(&def, 0x44) = 0;
        Fld<unsigned>(&def, 0x48) = 0;
        Fld<unsigned>(&def, 0x08) = 0xffffffff;
        Fld<unsigned>(&def, 0x0c) = 0xffffffff;
        Fld<unsigned>(&def, 0x3c) = 0xffffffff;
        Fld<float>(&def, 0x1c) = 0.0f;
        Fld<float>(&def, 0x20) = 0.0f;
        Fld<float>(&def, 0x24) = 0.0f;
        Fld<float>(&def, 0x2c) = 0.0f;
        Fld<float>(&def, 0x30) = 0.0f;
        Fld<float>(&def, 0x34) = 0.0f;
        Fld<float>(&def, 0x14) = gf_one;
        Fld<float>(&def, 0x18) = gf_one;
        Fld<float>(&def, 0x28) = gf_one;
        Fld<float>(&def, 0x38) = gf_def3c;
        Insert(mpEnd, want - (unsigned)count, &def);
        return;
    }
    EraseRange(begin + want, mpEnd);
}
