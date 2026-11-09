// src/game/Swarm/_at_00a70000.cpp -- migrated from slice(s) s00a7b370, s00a78ce0, s00a77c80, s00a76cf0, s00a75dd0, s00a75000 by tools/migrate/rewrite.py
// Object file: Swarm/_at_00a70000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <xmmintrin.h>
#include <intrin.h>

// ---- items of slice s00a75000 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Swarm {
struct Vec4 { float x, y, z, w; };
}
}
namespace EA {
namespace Swarm {
struct IcOwner {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual bool RequestGrid(void* src, int* a, int* b, int* out); // slot 0x18
};
}
}
namespace EA {
namespace Swarm {
struct cMapInfo {
    void*       mpvtable;    // +0x00
    uint32_t    m04;         // +0x04
    uint32_t    m08;         // +0x08
    float       mMinX;       // +0x0c
    float       mMinY;       // +0x10
    float       mMaxX;       // +0x14
    float       mMaxY;       // +0x18
    uint8_t     mbWrap1c;    // +0x1c
    uint32_t    m20;         // +0x20
    uint32_t    m24;         // +0x24
    float       mScaleX;     // +0x28
    float       mScaleY;     // +0x2c
    void*       mpGrid;      // +0x30
    uint8_t     mbValid34;   // +0x34
    IcOwner*    mpOwner38;   // +0x38
    uint8_t     mbWrap3c;    // +0x3c
    uint32_t*   mpPixels40;  // +0x40
    int32_t     m44;         // +0x44
    int32_t     m48;         // +0x48
    int32_t     m4c;         // +0x4c
    uint32_t    m50;         // +0x50
    uint32_t    m54;         // +0x54
    uint32_t    m58;         // +0x58
    uint32_t    m5c;         // +0x5c
    uint32_t    m60;         // +0x60
    uint32_t    m64;         // +0x64
    uint32_t    m68;         // +0x68
    uint32_t    m6c;         // +0x6c

    float  Get1c();                                          // 0x00a75010
    void   MapToCell(float rx, float ry, int* px, int* py,
                     float* fx, float* fy);                  // 0x00a75020
    void   Normalize();                                      // 0x00a75120
    void   NormalizeNoWrap();                                // 0x00a751a0
    void   NormalizeFloor();                                 // 0x00a75200
    void   NormalizeRound();                                 // 0x00a75270
    void   SetColor(int idx, const Vec4* c);                 // 0x00a752d0
    void   SetPoint(int idx, uint32_t a, uint32_t b);        // 0x00a75340

    void   UnpackColor(float* out, int packed, uint32_t a);  // 0x00a754f0
    int    ClassifyOrientation(const float* n, int* out);    // 0x00a75560

    void   SetVec3(float* out, uint32_t a);                  // 0x00a756a0 (stdcall)
    float* MulScale(float* out, float* s);                   // 0x00a756d0
    void   Fill(float* out, uint32_t a);                     // 0x00a75720
    void   GetBounds(float* out);                            // 0x00a75750
    bool   Contains(const float* p);                         // 0x00a757c0
    void   InitA(const float* rect, uint8_t a, void* b, int c, uint8_t d); // 0x00a75810
    void   InitB(const float* rect, uint8_t a, void* b, int c, uint8_t d, int e); // 0x00a758b0
    float  SampleBilinear(const float* p);                   // 0x00a75960
    void   SampleBicubic(float* out, const float* p);        // 0x00a75a30
    void   NormalizeVec(float* out, uint32_t a);             // 0x00a75d00
};
}
}
namespace EA {
namespace Swarm {
float __stdcall cMapInfo_One(void*);                                     // 0x00a75000
}
}
namespace EA {
namespace Swarm {
void  __cdecl   cMapInfo_ResetGrid(void* a, uint32_t* b);                      // 0x00a75390
}
}
namespace EA {
namespace Swarm {
void  __cdecl   cMapInfo_SortRect2(float* out, const float* a, const float* b);  // 0x00a753b0
}
}
namespace EA {
namespace Swarm {
void  __cdecl   cMapInfo_SortRect3(float* out, const float* b, const float* a);  // 0x00a75410
}
}
namespace EA {
namespace Swarm {
void  __cdecl   cMapInfo_SortRect3R(float* out, const float* b, const float* a); // 0x00a75480
}
}
// ---- items of slice s00a75000 end

// ---- items of slice s00a75dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(sqrt)
namespace EA {
namespace Swarm {
struct IcOwner_s00a7_5dd0 {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual bool v14(int id, int a, int b, void* out);              // +0x14
    virtual bool RequestGrid(void* src, int* a, int* b, int* out);  // +0x18
};
}
}
namespace EA {
namespace Swarm {
struct cMapInfo_s00a7_5dd0 {
    void*       mpvtable;    // +0x00
    uint32_t    m04;         // +0x04
    uint32_t    m08;         // +0x08
    float       mMinX;       // +0x0c
    float       mMinY;       // +0x10
    float       mMaxX;       // +0x14
    float       mMaxY;       // +0x18
    uint8_t     mbWrap1c;    // +0x1c
    uint32_t    m20;         // +0x20
    uint32_t    m24;         // +0x24
    float       mScaleX;     // +0x28
    float       mScaleY;     // +0x2c
    void*       mpGrid;      // +0x30
    uint8_t     mbValid34;   // +0x34
    IcOwner_s00a7_5dd0*    mpOwner38;   // +0x38
    uint8_t     mbWrap3c;    // +0x3c
    uint32_t*   mpPixels40;  // +0x40
    int32_t     m44;         // +0x44
    int32_t     m48;         // +0x48
    int32_t     m4c;         // +0x4c

    // shared with slice s00a75000
    void  MapToCell(float rx, float ry, int* px, int* py, float* fx, float* fy); // 0x00a75020
    void  UnpackColor(float* out, int packed, uint32_t a);                       // 0x00a754f0

    void   SampleColorClamp(float* out, const float* p);        // 0x00a75dd0
    void   Init11(const float* rect, int a2, int a3, uint8_t a4, IcOwner_s00a7_5dd0* owner, uint8_t a6); // 0x00a76070
    float  SampleAlpha(const float* p);                         // 0x00a76110
    void   SampleDir(float* out, uint32_t a);                   // 0x00a761d0
    void   SampleColor(float* out, const float* p);             // 0x00a76240
    void   Init9(const float* rect, int a2, int a3, uint8_t a4, IcOwner_s00a7_5dd0* owner, uint8_t a6);  // 0x00a76420
    float  SampleBit(const float* p);                           // 0x00a764c0
    void   SampleNormal(float* out, const float* p);            // 0x00a765f0
    float* SampleTangent(float* out, uint32_t a);               // 0x00a76970
    void   SampleScalar4(float* out, uint32_t a);               // 0x00a76990
    void   Init12(const float* rect, int a2, int a3, uint8_t a4, IcOwner_s00a7_5dd0* owner); // 0x00a769b0
    float  SampleBitOriented(const float* p);                   // 0x00a76a50
    void   NormalizeVec3(float* out, const float* v);           // 0x00a76b30
    void   Init13(const float* rect, int a2, int a3, uint8_t a4, IcOwner_s00a7_5dd0* owner); // 0x00a76b80
    float  SampleByteOriented(const float* p);                  // 0x00a76c20
    float* SampleVec3(float* out, uint32_t a);                  // 0x00a76cd0
};
}
}
namespace EA {
namespace Swarm {
int __cdecl ClassifyOrientation(const float* n, int* cls, float* u, float* v);
}
}
namespace EA {
namespace Swarm {
static __forceinline float Clamp01(float v)
{
    __m128 x = _mm_set_ss(v);
    x = _mm_max_ss(x, _mm_setzero_ps());
    x = _mm_min_ss(x, _mm_set_ss(1.0f));
    return _mm_cvtss_f32(x);
}
}
}
// ---- items of slice s00a75dd0 end

// ---- items of slice s00a76cf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" extern float g_1676d7c;   // Vector3 zero-init (dynamic initializer 0x013094a0)
extern "C" extern float g_1676d80;
extern "C" extern float g_1676d84;
extern "C" extern float g_1676da0;
extern "C" extern float g_1676da4;
extern "C" extern float g_1676da8;
extern "C" extern float g_1676dac;
extern "C" extern const float g_13eeda0;   //  8.0f
struct IRefObj { virtual void AddRef(); virtual void Release(); };   // slots 0 / 4
struct IValue {
    virtual void  v00();
    virtual void  v04();
    virtual void  AddRef();                                   // +0x08
    virtual void  Release();                                  // +0x0c
    virtual int   Count();                                    // +0x10
    virtual void  v14();
    virtual bool  Test(float* p);                             // +0x18
    virtual bool  Empty();                                    // +0x1c
    virtual float Scale(float x);                             // +0x20
    virtual float* EvalVec3(float* out, int id);              // +0x24
    virtual float* EvalVec4(float* out, int id);              // +0x28
    virtual float* EvalVec4b(float* out, int id);             // +0x2c
};
struct IPxSource : IRefObj {
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual IValue* Fetch(uint32_t a, uint32_t b);   // slot 0x2c
};
struct SwarmRef : IRefObj {
    int      mRefCount;     // +0x04
    SwarmRef() { mRefCount = 0; }
};
struct MapInfo : SwarmRef {
    uint32_t m08;                       // +0x08
    uint32_t m0c;                       // +0x0c
    uint32_t m10;                       // +0x10  nesting counter (AddRef/Release)
    uint32_t m14;                       // +0x14  operation kind (0..6)
    float    m18;                       // +0x18  rect min X
    float    m1c;                       // +0x1c  rect min Y
    float    m20;                       // +0x20  rect max X
    float    m24;                       // +0x24  rect max Y
    uint32_t m28;                       // +0x28  packed colour 0 (grid source a)
    uint32_t m2c;                       // +0x2c  packed colour 0 (grid source b)
    uint32_t m30;                       // +0x30
    uint32_t m34;                       // +0x34
    uint32_t m38;                       // +0x38
    uint32_t m3c;                       // +0x3c
    float    m40, m44, m48, m4c;        // +0x40  tuple 0 (point or colour)
    float    m50, m54, m58, m5c;        // +0x50  tuple 1
    float    m60, m64, m68, m6c;        // +0x60  tuple 2
    IValue* mp70;                       // +0x70
    IValue* mp74;                       // +0x74
    IValue* mp78;                       // +0x78
    IPxSource* mp7c;                    // +0x7c

    MapInfo();                                                        // 0x00a76cf0
    void Update();                                                    // 0x00a76df0
    void ReleaseTemps();                                              // 0x00a76ef0
    int  SumCounts();                                                 // 0x00a76f70
    void GetRect(float* out);                                         // 0x00a76fb0
    bool ContainsPoint(float* p);                                     // 0x00a77020
    bool IsEmpty();                                                   // 0x00a770a0
    float Eval(float x);                                              // 0x00a77100
    float* EvalVec3(float* out, int id);                              // 0x00a77250
    float* EvalVec4(float* out, int id);                              // 0x00a775a0
    float* EvalVec4b(float* out, int id);                             // 0x00a77830
    void Set(int kind, float* rect, IPxSource* src);                  // 0x00a77b70
};
void  cMapInfo_SortRect2(float* out, const float* a, const float* b);    // 0x00a753b0
void  cMapInfo_SortRect3(float* out, const float* b, const float* a);    // 0x00a75410
void  cMapInfo_SortRect3R(float* out, const float* b, const float* a);   // 0x00a75480
void  Swarm_Normalize(float* out, const float* v);                       // 0x006e6df0
void  Swarm_Min(float* out, const float* a, const float* b);             // 0x006e6e30
// ---- items of slice s00a76cf0 end

// ---- items of slice s00a77c80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char kEastlAllocFile[];  // ".../EASTL/allocator.h"
extern const float kRadScale;   // 0x015549dc
extern void* g_MapInfoFns[8];   // 0x01675a00
extern void* g_MaterialFns[8];   // 0x01675a24
extern const float kSineScale;       // 0x016770d8
extern const float kSineStep;        // 0x01677160
extern const float kSineTable[];     // 0x01677840
void* operator new(size_t size, const char* pName, int a, int b, const char* file, int line);  // 0xf473a0
void* operator new[](size_t size, const char* pName, int a, int b, const char* file, int line);
void operator_delete__(void* p);   // 0xf47380 (operator delete[]-style, plain cdecl)
struct IStream {
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
    virtual int Read(void* dst, uint32_t size);   // +0x30
};
bool ReadUInt64(void* s, void* p, unsigned n, int endian);   // 0x93a800
bool ReadUInt16(void* s, void* p, unsigned n, int endian);   // 0x93a700
bool ReadInt32(void* s, void* p, unsigned n, int endian);    // 0x93a780
bool ReadBytes(void* s, void* p, unsigned n);                // 0x93a6c0
struct B4 {                      // second base at +4: vptr + counter
    virtual ~B4() {}
    int mRef;
    B4() { mRef = 0; }
};
struct AutoRef {
    IRefObj* p;
    __forceinline ~AutoRef() { if (p) p->Release(); }
};
struct MapInfoHolder : IRefObj, B4 {
    uint32_t pad[0x19];
    AutoRef mRef70, mRef74, mRef78, mRef7c;
    MapInfoHolder();
};
struct MapDescription {
    virtual void d0();
    uint32_t mField4;          // +4
    uint32_t mA8, mAC;         // +8, +0xc  (read as one 64-bit id)
    uint32_t mFlags;           // +0x10
    uint32_t mKind;            // +0x14
    int      mI18, mI1c;       // +0x18, +0x1c
    float    mV20[4];          // +0x20 (16 bytes read raw)
    int8_t   mType30;          // +0x30
    int8_t   mFlag31;          // +0x31
    uint32_t mPad32;
    uint32_t mPairs[8];        // +0x38: 4 x 64-bit
    float    mVecs[16];        // +0x58: 4 x 16 bytes
    MapDescription();
};
struct IContext {
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
    virtual void* GetSink();                                   // +0x14
virtual void c6();
virtual void c7();
virtual void c8();
virtual void c9();
virtual void c10();
virtual void c11();
virtual void c12();
virtual void c13();
virtual void c14();
virtual void c15();
virtual void c16();
virtual void c17();
virtual void c18();
virtual void c19();
virtual void c20();
virtual void c21();
virtual void c22();
virtual void c23();
virtual void c24();
virtual void c25();
virtual void c26();
virtual void c27();
virtual void c28();
virtual void c29();
virtual void c30();
virtual void c31();
virtual void c32();
virtual void c33();
    virtual void AddEntry(uint32_t a, uint32_t b, IRefObj* o);  // +0x88
};
void AddFunc();                  // 0x00a75390
void ReadFunc();                 // 0x00a78150
void Add(MapDescription* d, IContext* ctx);  // 0x00a781f0 (defined below; used by a stub's inline body)
struct IEntries { virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3();
virtual void e4();
virtual void e5();
virtual void e6();
virtual void e7();
                  virtual void Add(uint32_t a, uint32_t b, void* d); };
struct MaterialParam {          // 0x18 bytes
    uint32_t mIdLo, mIdHi;      // +0
    union { int32_t i; float f; void* p; uint8_t b; uint32_t u32[2]; } mValue;   // +8
    int16_t  mCount;            // +0x10
    int8_t   mType;             // +0x12
    uint8_t  mPad13;
    uint32_t mPad14;
};
struct DefaultCopyTag {};
struct GenIter { MaterialParam* p; };
MaterialParam* UninitCopy(MaterialParam* first, MaterialParam* last, MaterialParam* dest);      // 0x00720200
GenIter*       UninitCopyGen(GenIter* out, MaterialParam* first, MaterialParam* last, MaterialParam* dest); // 0x00720d70
MaterialParam* CopyBackward(MaterialParam* first, MaterialParam* last, MaterialParam* destEnd); // 0x00cc8b50
void           FillRange(MaterialParam* first, MaterialParam* last, const MaterialParam* v);    // 0x007144b0
void           UninitFillN(MaterialParam* dest, uint32_t n, const MaterialParam* v);            // 0x00714910
void           UninitFillN(MaterialParam* dest, uint32_t n, const MaterialParam* v, DefaultCopyTag t);
MaterialParam* CopyPtr(MaterialParam* first, MaterialParam* last, MaterialParam* dest);         // 0x00720250
struct ParamVec {
    MaterialParam* mpBegin;
    MaterialParam* mpEnd;
    MaterialParam* mpCapacity;
    __forceinline ~ParamVec() { if (mpBegin && ((int*)mpBegin)[-1]) operator_delete__(mpBegin); }
    void erase(MaterialParam* first, MaterialParam* last) {
        MaterialParam* dst = first;
        for (MaterialParam* src = last; src != mpEnd; ++src, ++dst) *dst = *src;
        mpEnd -= (last - first);
    }
    void insert(MaterialParam* position, uint32_t n, const MaterialParam& value);   // 0x00a787f0
    void resize(uint32_t n);                                                       // 0x00a789e0
};
struct MaterialDescription : B4 {
    virtual ~MaterialDescription();
    uint32_t mIdA[2];          // +8
    uint32_t mIdB[2];          // +0x10
    ParamVec mParams;          // +0x18
    uint32_t mPad24[3];
    MaterialDescription() {
        mIdA[0] = 0xffffffff; mIdA[1] = 0xffffffff; mIdB[0] = 0xffffffff; mIdB[1] = 0xffffffff;
        mParams.mpBegin = 0; mParams.mpEnd = 0; mParams.mpCapacity = 0;
    }
    void Clear();              // 0x00a78a80
};
void ReadParams(IStream* s, ParamVec* v);
void SetSerializer();            // 0x00c2e4e0
// ---- items of slice s00a77c80 end

// ---- items of slice s00a78ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl asin(double);                          // 0x011e08bc lib_cblock asin
extern float g_SinFreq;                                          // 0x016770d8 16 / 2pi
extern float g_SinPeriod;                                        // 0x01677160 2pi / 16
extern float g_TwoPi;                                            // 0x01677174 2pi
extern float g_SinTable[32];                                     // 0x01677840 {sin, cos} of i * period
extern float g_HalfPi;                                           // 0x01554b54 pi / 2
extern float g_Three;                                            // 0x013eb95c 3.0f
#pragma intrinsic(fabs)
typedef unsigned int uint32;
double __cdecl cConfigManagerUnnamedB90(float* pair);            // 0x007cdb90 random float of a pair
float  FUN_00a78c80(float pitch);                                // 0x00a78c80 pitch helper
namespace EA {
namespace Random {
class RandomLinearCongruential_s00a7_8ce0 {                                  // 0x009360d0
public:
    double RandomDoubleUniform();  // 0x009360d0 (EA::Random::RandomLinearCongruential::RandomDoubleUniform)
};
}
}
typedef EA::Random::RandomLinearCongruential_s00a7_8ce0 ExtRandom;
extern ExtRandom g_Random;                                       // 0x016778dc shared math RNG
struct Vec3 { float x, y, z; };
struct Rec7 { float f[7]; };                                      // 0x1c
struct Xform {                                                    // 0x38
    unsigned flags;              // +0x00
    Vec3     translation;        // +0x04
    float    scale;              // +0x10
    float    m[9];               // +0x14
    void InverseTransformDir(Vec3* v) const;
    void TransformDir(Vec3* v) const;
};
struct ImpulseTable {                                             // impulse falloff description
    float* begin;                // +0x00 keyed speed table
    float* end;                  // +0x04
    int    pad0[3];              // +0x08
    float  speed;                // +0x14 distance the table spans
    float  threshold;            // +0x18 below this the impulse is dropped
};
struct KeyDesc {                                                  // per-state steering description
    float  aLo, aHi;             // +0x00
    float  bLo, bHi;             // +0x08
    float  jitter;               // +0x10
    float  spread;               // +0x14
    float  weight;               // +0x18
    float* keysBegin;            // +0x1c
    float* keysEnd;              // +0x20
    int    pad[3];               // +0x24
    unsigned char mode;          // +0x30
};
struct cRWState {                                                 // 0x18
    float f0;                    // +0x00
    float a;                     // +0x04
    float b;                     // +0x08
    float phase;                 // +0x0c
    float pitch;                 // +0x10
    int   frame;                 // +0x14
    void Update(const KeyDesc* d);
    void AccumulateForce(Vec3* force);
    void Init(const KeyDesc* d, const Vec3* dir, bool instant);
};
struct KeyList { Rec7* begin; Rec7* end; };
struct State {                                                    // key state record
    int   unk0;                   // +0x00
    float g;                      // +0x04
    Vec3  a;                      // +0x08
    Vec3  b;                      // +0x14
};
struct KeyRec {                                                   // 0x1c stream record
    float f0;                     // +0x00
    Vec3  a;                      // +0x04
    Vec3  b;                      // +0x10
    float c;                      // +0x18
};
struct KeyRecB {                                                  // 0x1c stream record (no id)
    Vec3  a;                      // +0x00
    Vec3  b;                      // +0x0c
    float c;                      // +0x18
};
struct IStream_s00a7_8ce0 {
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
virtual void v11();
    virtual int  Read(void* data, uint32 size);                   // +0x30
    virtual void v13();
    virtual bool Write(const void* data, uint32 size);            // +0x38
};
bool ReadInt32(IStream_s00a7_8ce0* s, int* p, uint32 count, int endian);     // 0x0093a780
bool WriteUint32(IStream_s00a7_8ce0* s, const uint32* p, uint32 count, int endian); // 0x0093aa70
inline bool WriteFloat32(IStream_s00a7_8ce0* s, float value) { return WriteUint32(s, (uint32*)&value, 1, 0); }
static __forceinline double Clamp(double v, double lo, double hi)
{
    if (v < hi) {
        if (lo <= v)
            return v;
        return lo;
    }
    return hi;
}
// ---- items of slice s00a78ce0 end

// ---- items of slice s00a7b370 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* ReadIntVector(void* s, void* vec);                     // 0x7d27d0
struct RcObj {                   // slot 2 = deleting destructor, counter at +4
    virtual void v0();
    virtual void v1();
    virtual ~RcObj();
    long mRef;
    long Release();              // 0x00a7ba90
};
struct IFace12 {                  // interface used by the two thunks below
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void p10();
virtual void p11();
    virtual bool Op12(void* x);   // +0x30
    virtual bool Op13(void* x);   // +0x34
};
struct ISource {
virtual void q0();
virtual void q1();
virtual void q2();
virtual void q3();
virtual void q4();
virtual void q5();
    virtual void* GetItem();       // +0x18
};
struct Forwarder {
    char pad[0x14];
    IFace12* mpTarget;             // +0x14
};
struct CountedBase {
    virtual ~CountedBase() {}
    long mRef;
    CountedBase() { _InterlockedExchange(&mRef, 0); }
};
struct CountedBase2 {
    virtual void AddRef();
    virtual void Release();
    virtual ~CountedBase2() {}
    long mRef;
    CountedBase2() { _InterlockedExchange(&mRef, 0); }
};
struct RecordReadObj : CountedBase {         // 0x00a7bb80
    RecordReadObj();
    virtual ~RecordReadObj() {}
};
struct IRefA { virtual void AddRef(); virtual void Release(); };   // slot 0 AddRef, 1 Release
struct CollectionBase : CountedBase2 {
    uint32_t mVec[3];                         // +8
    CollectionBase() { mVec[0] = 0; mVec[1] = 0; mVec[2] = 0; }
    virtual void AddRef();
    virtual void Release();
};
struct CollectionResource : CollectionBase {  // 0x18 bytes
    IRefA*   mpRes;                           // +0x14
    CollectionResource() { mpRes = 0; }
    virtual void AddRef();
    virtual void Release();
};
struct IVec3Source { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
                     virtual const uint32_t* GetVec(); };   // +0x10
struct ICreator {
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
virtual void c5();
virtual void c6();
virtual void c7();
    virtual void c8();
    virtual bool Create(IVec3Source* a, CollectionResource* r, int arg, uint32_t tag);   // +0x24
};
IRefA* GetDefaultResource();   // 0x00a6b970
struct Loader {
    ICreator* creator() { return (ICreator*)this; }
    bool Load(IVec3Source* a, CollectionResource** out, int arg, uint32_t tag);   // 0x00a7bba0
};
struct IFactory {
virtual void f0();
virtual void f1();
virtual void f2();
    virtual bool Create(void* q, CollectionResource** out, int a, int b, int c, int d);   // +0xc
};
IFactory* GetFactory();   // 0x008de1a0
struct QueryDesc { int mParam; uint32_t mTagA; uint32_t mTagB; };
struct ResultObj {
    virtual void AddRef();
    virtual void Release();
    char pad[0x14 - 4];
    int mField14;
};
struct IRefT1 { virtual void Release(); virtual void AddRef(); };   // slot 0 Release, 1 AddRef
struct IRefT2 { virtual void AddRef(); virtual void Release(); };   // slot 0 AddRef, 1 Release
struct HKey { uint32_t a, b; };
template<class T> struct HNode {
    HKey key;          // +0
    T*   value;        // +8
    uint32_t pad0c;
    HNode* next;       // +0x10
    uint32_t pad14;
};
struct HIter {
    void*  node;
    void** bucket;
    HIter() {}
    HIter(const HIter& o) { node = o.node; bucket = o.bucket; }
};
struct HTag {};
struct HInsRes {              // eastl::pair<iterator, bool>
    HIter first;
    bool  second;
    HInsRes() {}
    HInsRes(const HInsRes& o) : first(o.first), second(o.second) {}
};
template<class T> struct HPair {
    HKey key;
    T*   value;
};
struct HashMapBase {
    uint32_t pad0;
    HNode<void>** mBuckets;     // +4
    uint32_t      mBucketCount; // +8
    HIter find(const HKey& k);  // 0x00a7bf40
};
struct HashMap1 : HashMapBase {
    HInsRes insert(const HPair<IRefT1>& v, HTag t);   // 0x00a7be70
    IRefT1** Subscript(const HKey& k);              // operator[] at 0x00a7c100
};
struct HashMap2 : HashMapBase {
    HInsRes insert(const HPair<IRefT2>& v, HTag t);   // 0x00a7bfb0
    IRefT2** Subscript(const HKey& k);              // operator[] at 0x00a7c180
};
struct Registry {
    char pad[4];
    HashMap1 mMap1;      // +4
    char pad2[0x24 - 0x4 - sizeof(HashMap1)];
    HashMap2 mMap2;      // +0x24
    void Set1(HKey key, IRefT1* val);   // 0x00a7c200
    void Set2(HKey key, IRefT2* val);   // 0x00a7c240
};
struct Halton2 {
    float mX;       // +0  base 2
    float mY;       // +4  base 3
    int   mIndex;   // +8
    volatile int mDigits3; // +0xc
    int   Next();            // 0x00a7c350
    Halton2(int index);      // 0x00a7c3d0
};
struct Halton3 {
    float mX;       // +0  base 2
    float mY;       // +4  base 3
    float mZ;       // +8  base 5
    int   mIndex;   // +0xc
    volatile int mDigits3; // +0x10
    volatile int mDigits5; // +0x14
    int   Next();            // 0x00a7c450
    Halton3(int index);      // 0x00a7c540
};
// ---- items of slice s00a7b370 end

// @ 0x00a75000
namespace EA { namespace Swarm {
float __stdcall cMapInfo_One(void*)
{
    return 1.0f;
}
}}  // namespace EA::Swarm

// @ 0x00a75020
namespace EA { namespace Swarm {
void cMapInfo::MapToCell(float rx, float ry, int* px, int* py, float* fx, float* fy)
{
    float u = (rx - mMinX) * mScaleX;
    float v = (ry - mMinY) * mScaleY;

    int cx = (int)u;
    if (u < (float)cx)
        cx -= 1;
    *px = cx;

    int cy = (int)v;
    if (v < (float)cy)
        cy -= 1;
    *py = cy;

    *fx = u - (float)cx;
    *fy = v - (float)cy;

    if (mbWrap3c) {
        int m = m20 - 1;
        *px = cx % m;
        if (*px < 0)
            *px += m;
        int n = m24 - 1;
        *py = cy % n;
        if (*py < 0)
            *py += n;
    } else {
        int m = m20 - 1;
        *px = cx - (cx >= m);
        int n = m24 - 1;
        *py = cy - (cy >= n);
    }
}
}}  // namespace EA::Swarm

// @ 0x00a75120
namespace EA { namespace Swarm {
void cMapInfo::Normalize()
{
    if (mpPixels40)
        return;
    mpOwner38->RequestGrid(mpGrid, (int*)&m20, (int*)&m24, (int*)&mpPixels40);
    mpPixels40 = (uint32_t*)((char*)mpPixels40 + m4c);
    int cols = (int)m20;
    m44 = (1 << m48) * cols;
    mScaleX = (float)(cols - 1) / (mMaxX - mMinX);
    mScaleY = (float)((int)m24 - 1) / (mMaxY - mMinY);
}
}}  // namespace EA::Swarm

// @ 0x00a751a0
namespace EA { namespace Swarm {
void cMapInfo::NormalizeNoWrap()
{
    if (mpPixels40)
        return;
    mpOwner38->RequestGrid(mpGrid, (int*)&m20, (int*)&m24, (int*)&mpPixels40);
    mScaleX = (float)((int)m20 - 1) / (mMaxX - mMinX);
    mScaleY = (float)((int)m24 - 1) / (mMaxY - mMinY);
}
}}  // namespace EA::Swarm

// @ 0x00a75200
namespace EA { namespace Swarm {
void cMapInfo::NormalizeFloor()
{
    if (mpPixels40)
        return;
    mpOwner38->RequestGrid(mpGrid, (int*)&m20, (int*)&m24, (int*)&mpPixels40);
    m44 = ((int)m20 + 7) >> 3;
    mScaleX = (float)((int)m20 - 1) / (mMaxX - mMinX);
    mScaleY = (float)((int)m24 - 1) / (mMaxY - mMinY);
}
}}  // namespace EA::Swarm

// @ 0x00a75270
namespace EA { namespace Swarm {
void cMapInfo::NormalizeRound()
{
    if (mpPixels40)
        return;
    mpOwner38->RequestGrid(mpGrid, (int*)&m20, (int*)&m24, (int*)&mpPixels40);
    m44 = ((int)m20 + 7) >> 3;
    mScaleX = (float)((int)m20 - 1) / (mMaxX - mMinX);
    mScaleY = (float)((int)m20 - 1) / (mMaxY - mMinY);
}
}}  // namespace EA::Swarm

// @ 0x00a75390
namespace EA { namespace Swarm {
void __cdecl cMapInfo_ResetGrid(void* a, uint32_t* b)
{
    void* p = *(void**)((char*)a + 8);
    int n = *(int*)((char*)a + 0xc);
    ((void (__thiscall*)(uint32_t*, void*, int, int))(*(void***)b)[0x88 / 4])(b, p, n, 0);
}
}}  // namespace EA::Swarm

// @ 0x00a753b0
namespace EA { namespace Swarm {
void cMapInfo_SortRect2(float* out, const float* b, const float* a)
{
    const float* p2 = (a[2] < b[2]) ? a + 2 : b + 2;
    const float* p1 = (a[1] < b[1]) ? a + 1 : b + 1;
    const float* p0 = (a[0] < b[0]) ? a : b;
    out[0] = *p0;
    out[1] = *p1;
    out[2] = *p2;
}
}}  // namespace EA::Swarm

// @ 0x00a75410
namespace EA { namespace Swarm {
void cMapInfo_SortRect3(float* out, const float* b, const float* a)
{
    const float* p3 = (a[3] < b[3]) ? a + 3 : b + 3;
    const float* p2 = (a[2] < b[2]) ? a + 2 : b + 2;
    const float* p1 = (a[1] < b[1]) ? a + 1 : b + 1;
    const float* p0 = (a[0] < b[0]) ? a : b;
    *out = p0[0];
    out[1] = p1[0];
    out[2] = p2[0];
    out[3] = p3[0];
}
}}  // namespace EA::Swarm

// @ 0x00a75480
namespace EA { namespace Swarm {
void cMapInfo_SortRect3R(float* out, const float* b, const float* a)
{
    const float* p3 = (a[3] > b[3]) ? a + 3 : b + 3;
    const float* p2 = (a[2] > b[2]) ? a + 2 : b + 2;
    const float* p1 = (a[1] > b[1]) ? a + 1 : b + 1;
    const float* p0 = (a[0] > b[0]) ? a : b;
    out[0] = *p0;
    out[1] = *p1;
    out[2] = *p2;
    out[3] = *p3;
}
}}  // namespace EA::Swarm

// @ 0x00a754f0
namespace EA { namespace Swarm {
void cMapInfo::UnpackColor(float* out, int packed, uint32_t a)
{
    uint32_t v = mpPixels40[m20 * a + packed];
    out[0] = (float)((v >> 16) & 0xff);
    out[1] = (float)((v >> 8) & 0xff);
    out[2] = (float)(v & 0xff);
    out[3] = (float)(uint32_t)(v >> 24);
}
}}  // namespace EA::Swarm

// @ 0x00a75560
namespace EA { namespace Swarm {
int cMapInfo::ClassifyOrientation(const float* n, int* out)
{
    float ax = n[0], ay = n[1], az = n[2];
    float aax = ax < 0 ? -ax : ax;
    float aay = ay < 0 ? -ay : ay;
    float aaz = az < 0 ? -az : az;
    float u, v;
    int cls;
    if (aaz >= aay && aaz >= aax) {
        u = -ax / az;
        v = ay / aaz;
        if (az < 0.0f) {
            *out = 2;
        } else {
            *out = 0;
        }
    } else if (aay >= aax) {
        u = -ax / aay;
        v = az / ay;
        cls = (ay < 0.0f) ? 1 : 3;
        *out = cls;
    } else {
        u = -az / ax;
        v = ay / aax;
        cls = (ax < 0.0f) ? 5 : 4;
        *out = cls;
        if (cls == 4) {
            u = -u;
            v = -v;
        }
    }
    return cls;
}
}}  // namespace EA::Swarm

// @ 0x00a756d0
namespace EA { namespace Swarm {
float* cMapInfo::MulScale(float* out, float* s)
{
    float f = (float)((double (__thiscall*)(cMapInfo*, float*))(*(void***)this)[0x20 / 4])(this, s);
    float v[3];
    float* r = ((float* (__thiscall*)(cMapInfo*, float*, float*))(*(void***)this)[0x24 / 4])(this, v, s);
    out[0] = f * r[0];
    out[1] = f * r[1];
    out[2] = f * r[2];
    return out;
}
}}  // namespace EA::Swarm

// @ 0x00a75720
namespace EA { namespace Swarm {
void cMapInfo::Fill(float* out, uint32_t a)
{
    double w = ((double (__thiscall*)(cMapInfo*, uint32_t))(*(void***)this)[0x20 / 4])(this, a);
    out[0] = 1.0f;
    out[1] = 1.0f;
    out[2] = 1.0f;
    out[3] = w;
}
}}  // namespace EA::Swarm

// @ 0x00a75750
namespace EA { namespace Swarm {
void cMapInfo::GetBounds(float* out)
{
    float t[6];
    t[0] = mMinX;
    t[1] = mMaxX;
    t[2] = mMinY;
    t[3] = mMaxY;
    t[4] = 0.0f;
    t[5] = 0.0f;
    out[0] = t[0];
    out[1] = t[1];
    out[2] = t[2];
    out[3] = t[3];
    out[4] = t[4];
    out[5] = t[5];
}
}}  // namespace EA::Swarm

// @ 0x00a757c0
namespace EA { namespace Swarm {
bool cMapInfo::Contains(const float* p)
{
    if (mbWrap3c)
        return true;
    if (p[0] < mMinX)
        return false;
    if (mMaxX <= p[0])
        return false;
    if (p[1] < mMinY)
        return false;
    if (mMaxY <= p[1])
        return false;
    return true;
}
}}  // namespace EA::Swarm

// @ 0x00a75960
namespace EA { namespace Swarm {
float cMapInfo::SampleBilinear(const float* p)
{
    int cx, cy;
    float fx, fy;
    MapToCell(p[0], p[1], &cx, &cy, &fx, &fy);

    int stride = m44;
    int sh = m48;
    uint8_t* px = (uint8_t*)mpPixels40;

    float v00 = (float)px[stride * cy + (int)cx];
    float v10 = (float)px[stride * (cy + 1) + (int)cx];
    float top = v00 + (v10 - v00) * fy;
    int c1 = cx + 1;
    float v01 = (float)px[stride * cy + c1];
    float v11 = (float)px[stride * (cy + 1) + c1];
    float bot = v01 + (v11 - v01) * fy;
    return (top + (bot - top) * fy) * (1.0f / 255.0f);
}
}}  // namespace EA::Swarm

// @ 0x00a75a30
namespace EA { namespace Swarm {
void cMapInfo::SampleBicubic(float* out, const float* p)
{
    int cx, cy;
    float fx, fy;
    MapToCell(p[0], p[1], &cx, &cy, &fx, &fy);

    int stride = m44;
    uint8_t* px = (uint8_t*)mpPixels40;
    int sh = m48;

    int c0 = cx - 1; if (c0 <= 0) c0 = 0;
    int c1 = cx + 1; if (c1 >= (int)m20 - 1) c1 = (int)m20 - 1;
    int c2 = cx + 2; if (c2 >= (int)m20 - 1) c2 = (int)m20 - 1;
    int r0 = cy - 1; if (r0 <= 0) r0 = 0;
    int r1 = cy + 1; if (r1 >= (int)m24 - 1) r1 = (int)m24 - 1;
    int r2 = cy + 2; if (r2 >= (int)m24 - 1) r2 = (int)m24 - 1;

    // 4x4 neighbourhood (row-major, rows r0..r2 and cy, cols c0..c2 and cx).
    float s[4][4];
    int rows[4] = { r0, cy, r1, r2 };
    int cols[4] = { c0, cx, c1, c2 };
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            s[r][c] = (float)px[(uint32_t)rows[r] * stride + ((uint32_t)cols[c] << sh)];
    (void)fy; (void)fx;
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
}
}}  // namespace EA::Swarm

// @ 0x00a75d00
namespace EA { namespace Swarm {
void cMapInfo::NormalizeVec(float* out, uint32_t a)
{
    float v[4];
    ((void (__thiscall*)(cMapInfo*, float*, uint32_t))(*(void***)this)[0x2c / 4])(this, v, a);
    float x = v[0] * 2.0f - 1.0f;
    float y = v[1] * 2.0f - 1.0f;
    float z = v[2] * 2.0f - 1.0f;
    float len = 1.0f / sqrtf(x * x + y * y + z * z + 1e-9f);
    out[0] = v[3] * x * len;
    out[1] = v[3] * y * len;
    out[2] = v[3] * z * len;
}
}}  // namespace EA::Swarm

// @ 0x00a75dd0
namespace EA { namespace Swarm {
void cMapInfo_s00a7_5dd0::SampleColorClamp(float* out, const float* p)
{
    int cx, cy;
    float fx, fy;
    MapToCell(p[0], p[1], &cx, &cy, &fx, &fy);

    float a[4], b[4], c[4], d[4];
    UnpackColor(a, cx, cy);
    UnpackColor(b, cx, cy + 1);
    for (int i = 0; i < 4; ++i)
        b[i] = (b[i] - a[i]) * fx + a[i];

    UnpackColor(c, cx + 1, cy);
    UnpackColor(d, cx + 1, cy + 1);
    for (int i = 0; i < 4; ++i)
        out[i] = ((((d[i] - c[i]) * fx + c[i]) - b[i]) * fy + b[i]) * (1.0f / 254.0f);

    for (int i = 0; i < 3; ++i)
        out[i] = Clamp01(out[i]);
}
}}  // namespace EA::Swarm

// @ 0x00a76110
namespace EA { namespace Swarm {
float cMapInfo_s00a7_5dd0::SampleAlpha(const float* p)
{
    int cx, cy;
    float fx, fy;
    MapToCell(p[0], p[1], &cx, &cy, &fx, &fy);

    const uint8_t* q = (const uint8_t*)mpPixels40;
    int stride = (int)m20;
    int i0 = stride * cy + cx;
    int i1 = stride * (cy + 1) + cx;

    float A = (float)q[i0 * 4 + 3];
    float B = (float)q[i0 * 4 + 7];
    float C = (float)q[i1 * 4 + 3];
    float D = (float)q[i1 * 4 + 7];

    float R = (C - A) * fx + A;
    float S = (D - B) * fx + B;
    return (R + (S - R) * fy) * (1.0f / 255.0f);
}
}}  // namespace EA::Swarm

// @ 0x00a761d0
namespace EA { namespace Swarm {
void cMapInfo_s00a7_5dd0::SampleDir(float* out, uint32_t a)
{
    float v[4];
    ((void (__thiscall*)(cMapInfo_s00a7_5dd0*, float*, uint32_t))(*(void***)this)[0x2c / 4])(this, v, a);
    out[0] = v[0] * 2.0f - 1.0f;
    out[1] = v[1] * 2.0f - 1.0f;
    out[2] = v[2] * 2.0f - 1.0f;
}
}}  // namespace EA::Swarm

// @ 0x00a76240
namespace EA { namespace Swarm {
void cMapInfo_s00a7_5dd0::SampleColor(float* out, const float* p)
{
    int cx, cy;
    float fx, fy;
    MapToCell(p[0], p[1], &cx, &cy, &fx, &fy);

    float a[4], b[4], c[4], d[4];
    UnpackColor(a, cx, cy);
    UnpackColor(b, cx, cy + 1);
    for (int i = 0; i < 4; ++i)
        b[i] = (b[i] - a[i]) * fx + a[i];

    UnpackColor(c, cx + 1, cy);
    UnpackColor(d, cx + 1, cy + 1);
    for (int i = 0; i < 4; ++i)
        out[i] = ((((d[i] - c[i]) * fx + c[i]) - b[i]) * fy + b[i]) * (1.0f / 255.0f);
}
}}  // namespace EA::Swarm

// @ 0x00a764c0
namespace EA { namespace Swarm {
float cMapInfo_s00a7_5dd0::SampleBit(const float* p)
{
    int cx, cy;
    float fx, fy;
    MapToCell(p[0], p[1], &cx, &cy, &fx, &fy);

    const uint8_t* q = (const uint8_t*)mpPixels40;
    int stride = m44;
    int row0 = stride * cy;
    int row1 = stride * (cy + 1);

    float A = (float)((q[row0 + (cx >> 3)] >> (cx & 7)) & 1);
    float B = (float)((q[row1 + (cx >> 3)] >> (cx & 7)) & 1);
    int c1 = cx + 1;
    float C = (float)((q[row0 + (c1 >> 3)] >> (c1 & 7)) & 1);
    float D = (float)((q[row1 + (c1 >> 3)] >> (c1 & 7)) & 1);

    float R = (B - A) * fx + A;
    float S = (D - C) * fx + C;
    return ((S - R) * fy + R) > 0.5f ? 1.0f : 0.0f;
}
}}  // namespace EA::Swarm

// @ 0x00a765f0
namespace EA { namespace Swarm {
void cMapInfo_s00a7_5dd0::SampleNormal(float* out, const float* p)
{
    int cx, cy;
    float fx, fy;
    MapToCell(p[0], p[1], &cx, &cy, &fx, &fy);

    const uint8_t* q = (const uint8_t*)mpPixels40;
    int stride = m44;

    int cols = (int)m20;
    int rows = (int)m24;
    int c0 = cx - 1; if (c0 < 0) c0 = 0;
    int c1 = cx + 1; if (c1 >= cols - 1) c1 = cols - 1;
    int c2 = cx + 2; if (c2 >= cols - 1) c2 = cols - 1;
    int r0 = cy - 1; if (r0 < 0) r0 = 0;
    int r1 = cy + 1; if (r1 >= rows - 1) r1 = rows - 1;
    int r2 = cy + 2; if (r2 >= rows - 1) r2 = rows - 1;

#define BIT(col, row) ((float)((q[(row) * stride + ((col) >> 3)] >> ((col) & 7)) & 1))

    float A  = BIT(cx, cy);
    float B  = BIT(cx, r1);
    float C  = BIT(cx, r0);
    float L  = BIT(cx, r2);
    float D  = BIT(c1, cy);
    float E  = BIT(c1, r1);
    float F  = BIT(c1, r0);
    float J2 = BIT(c1, r2);
    float G  = BIT(c0, cy);
    float H  = BIT(c0, r1);
    float I  = BIT(c2, cy);
    float P  = BIT(c2, r1);

    float t1 = B - C;
    float t2 = ((L - A) - t1) * fy + t1;
    float t3 = E - F;
    float t4 = ((I - A) - (D - G)) * fx + (D - G);
    float t5 = E - H;

    float nx = (((((P - B) - t5) * fx + t5) - t4) * fy + t4) * mScaleX * -0.5f;
    float ny = (((((J2 - D) - t3) * fy + t3) - t2) * fx + t2) * mScaleY * -0.5f;

    out[0] = nx;
    out[1] = ny;
    out[2] = 1.0f;

    float len = 1.0f / sqrtf(out[0] * out[0] + out[1] * out[1] + out[2] * out[2]);
    out[2] = len;
    out[0] = nx * len;
    out[1] = ny * len;
#undef BIT
}
}}  // namespace EA::Swarm

// @ 0x00a76970
namespace EA { namespace Swarm {
float* cMapInfo_s00a7_5dd0::SampleTangent(float* out, uint32_t a)
{
    ((void (__thiscall*)(cMapInfo_s00a7_5dd0*, float*, uint32_t))(*(void***)this)[0x24 / 4])(this, out, a);
    out[2] = 0.0f;
    return out;
}
}}  // namespace EA::Swarm

// @ 0x00a76990
namespace EA { namespace Swarm {
void cMapInfo_s00a7_5dd0::SampleScalar4(float* out, uint32_t a)
{
    float v = ((float (__thiscall*)(cMapInfo_s00a7_5dd0*, uint32_t))(*(void***)this)[0x20 / 4])(this, a);
    out[0] = v;
    out[1] = v;
    out[2] = v;
    out[3] = v;
}
}}  // namespace EA::Swarm

// @ 0x00a76a50
namespace EA { namespace Swarm {
float cMapInfo_s00a7_5dd0::SampleBitOriented(const float* p)
{
    int cls;
    float u, v;
    ClassifyOrientation(p, &cls, &u, &v);

    int stride = (int)m20;
    float xf = (float)stride * u;
    int ix = (int)xf;
    if (xf < (float)ix)
        ix -= 1;
    float yf = (float)stride * v;
    int iy = (int)yf;
    if (yf < (float)iy)
        iy -= 1;

    const uint8_t* q = (const uint8_t*)mpPixels40;
    int idx = (stride * cls + iy) * m44 + (ix >> 3);
    return ((q[idx] >> (ix & 7)) & 1) > 0.5f ? 1.0f : 0.0f;
}
}}  // namespace EA::Swarm

// @ 0x00a76b30
namespace EA { namespace Swarm {
void cMapInfo_s00a7_5dd0::NormalizeVec3(float* out, const float* v)
{
    float len = 1.0f / sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + 1e-9f);
    out[0] = v[0] * len;
    out[1] = v[1] * len;
    out[2] = v[2] * len;
}
}}  // namespace EA::Swarm

// @ 0x00a76c20
namespace EA { namespace Swarm {
float cMapInfo_s00a7_5dd0::SampleByteOriented(const float* p)
{
    int cls;
    float u, v;
    ClassifyOrientation(p, &cls, &u, &v);

    int stride = (int)m20;
    float xf = (float)stride * u;
    int ix = (int)xf;
    if (xf < (float)ix)
        ix -= 1;
    float yf = (float)stride * v;
    int iy = (int)yf;
    if (yf < (float)iy)
        iy -= 1;

    const uint8_t* q = (const uint8_t*)mpPixels40;
    int idx = (stride * cls + iy) * stride + ix;
    return (float)q[idx] * (1.0f / 255.0f);
}
}}  // namespace EA::Swarm

// @ 0x00a76cd0
namespace EA { namespace Swarm {
float* cMapInfo_s00a7_5dd0::SampleVec3(float* out, uint32_t a)
{
    ((void (__thiscall*)(cMapInfo_s00a7_5dd0*, float*, uint32_t))(*(void***)this)[0x24 / 4])(this, out, a);
    return out;
}
}}  // namespace EA::Swarm

// @ 0x00a76df0
void MapInfo::Update()
{
    if (m10 == 0) {
        uint32_t a = m28, b = m2c;
        if ((a & b) != 0xffffffff) {
            IValue* pNew = mp7c->Fetch(a, b);
            IValue* pOld = mp70;
            if (pNew != pOld) {
                if (pNew) ((IRefObj*)pNew)->AddRef();
                mp70 = pNew;
                if (pOld) ((IRefObj*)pOld)->Release();
            }
        }
        a = m30; b = m34;
        if ((a & b) != 0xffffffff) {
            IValue* pNew = mp7c->Fetch(a, b);
            IValue* pOld = mp74;
            if (pNew != pOld) {
                if (pNew) ((IRefObj*)pNew)->AddRef();
                mp74 = pNew;
                if (pOld) ((IRefObj*)pOld)->Release();
            }
        }
        a = m38; b = m3c;
        if ((a & b) != 0xffffffff) {
            IValue* pNew = mp7c->Fetch(a, b);
            IValue* pOld = mp78;
            if (pNew != pOld) {
                if (pNew) ((IRefObj*)pNew)->AddRef();
                mp78 = pNew;
                if (pOld) ((IRefObj*)pOld)->Release();
            }
        }
    }
    m10++;
    if (mp70) mp70->AddRef();
    if (mp74) mp74->AddRef();
    if (mp78) mp78->AddRef();
}

// @ 0x00a76ef0
void MapInfo::ReleaseTemps()
{
    if (mp70) mp70->Release();
    if (mp74) mp74->Release();
    if (mp78) mp78->Release();
    if (--m10 == 0) {
        if (mp70) { IValue* p = mp70; mp70 = 0; ((IRefObj*)p)->Release(); }
        if (mp74) { IValue* p = mp74; mp74 = 0; ((IRefObj*)p)->Release(); }
        if (mp78) { IValue* p = mp78; mp78 = 0; ((IRefObj*)p)->Release(); }
    }
}

// @ 0x00a76f70
int MapInfo::SumCounts()
{
    int n = 0;
    IValue* p = mp70;
    if (p) n = p->Count();
    p = mp74;
    if (p) n += p->Count();
    p = mp78;
    if (p) n += p->Count();
    return n;
}

// @ 0x00a76fb0
void MapInfo::GetRect(float* out)
{
    float v[6];
    v[0] = m18;
    v[1] = m20;
    v[2] = m1c;
    v[3] = m24;
    v[4] = 0.0f;
    v[5] = 0.0f;

    out[0] = v[0];
    out[1] = v[1];
    out[2] = v[2];
    out[3] = v[3];
    out[4] = v[4];
    out[5] = v[5];
}

// @ 0x00a77020
bool MapInfo::ContainsPoint(float* p)
{
    IValue* v = mp70;
    if (v && !v->Test(p)) return false;
    v = mp74;
    if (v && !v->Test(p)) return false;
    v = mp78;
    if (v && !v->Test(p)) return false;
    return m18 <= p[0] && p[0] < m20 && m1c <= p[1] && p[1] < m24;
}

// @ 0x00a770a0
bool MapInfo::IsEmpty()
{
    if (mp70 == 0 && mp74 == 0 && mp78 == 0) return false;
    IValue* v = mp70;
    if (v && !v->Empty()) return false;
    v = mp74;
    if (v && !v->Empty()) return false;
    v = mp78;
    if (v && !v->Empty()) return false;
    return true;
}

// @ 0x00a77100
float MapInfo::Eval(float x)
{
    float a, b, c;
    if (mp70) a = (float)mp70->Scale(x);
    else       a = m40;
    if (mp74) b = (float)mp74->Scale(x);
    else       b = m50;
    if (mp78) c = (float)mp78->Scale(x);
    else       c = m60;

    switch (m14) {
    case 0: return a;
    case 1: return b + a;
    case 2: return b * a;
    case 3: return a - b;
    case 4: return a < b ? a : b;
    case 5: return a <= b ? b : a;
    case 6: return c + b * a;
    default: return 0.0f;
    }
}

// @ 0x00a77250
float* MapInfo::EvalVec3(float* out, int id)
{
    int a[3], b[3], c[3];
    if (mp70) {
        int* r = (int*)mp70->EvalVec3((float*)a, id);
        a[0] = r[0]; a[1] = r[1]; a[2] = r[2];
    } else if (m14 == 6 || m14 == 2) {
        float x = m40;
        ((float*)a)[0] = x;
        ((float*)a)[1] = x;
        ((float*)a)[2] = 1.0f;
    } else {
        ((float*)a)[0] = m40; ((float*)a)[1] = m44; ((float*)a)[2] = m48;
    }
    if (mp74) {
        int* r = (int*)mp74->EvalVec3((float*)b, id);
        b[0] = r[0]; b[1] = r[1]; b[2] = r[2];
    } else if (m14 == 6 || m14 == 2) {
        float x = m50;
        ((float*)b)[0] = x;
        ((float*)b)[1] = x;
        ((float*)b)[2] = 1.0f;
    } else {
        ((float*)b)[0] = m50; ((float*)b)[1] = m54; ((float*)b)[2] = m58;
    }
    if (mp78) {
        int* r = (int*)mp78->EvalVec3((float*)c, id);
        c[0] = r[0]; c[1] = r[1]; c[2] = r[2];
    } else {
        ((float*)c)[0] = m60; ((float*)c)[1] = m64; ((float*)c)[2] = m68;
    }
    float* fa = (float*)a; float* fb = (float*)b; float* fc = (float*)c;
    switch (m14) {
    case 0:
        out[0] = fa[0]; out[1] = fa[1]; out[2] = fa[2];
        break;
    case 1: {
        float t[3];
        t[0] = fb[0] + fa[0]; t[1] = fb[1] + fa[1]; t[2] = fb[2] + fa[2];
        Swarm_Normalize(out, t);
        break; }
    case 2: {
        float t[3];
        t[0] = fb[0] * fa[0]; t[1] = fb[1] * fa[1]; t[2] = fb[2] * fa[2];
        Swarm_Normalize(out, t);
        break; }
    case 3: {
        float t[3];
        t[0] = fa[0] - fb[0]; t[1] = fa[1] - fb[1]; t[2] = fa[2] - fb[2];
        Swarm_Normalize(out, t);
        break; }
    case 4:
        cMapInfo_SortRect2(out, fb, fa);
        break;
    case 5:
        Swarm_Min(out, fb, fa);
        break;
    case 6: {
        float t[3];
        t[0] = fb[0] * fa[0] + fc[0];
        t[1] = fc[1] + fb[1] * fa[1];
        t[2] = fc[2] + fb[2] * fa[2];
        Swarm_Normalize(out, t);
        break; }
    default:
        out[0] = g_1676d7c;
        out[1] = g_1676d80;
        out[2] = g_1676d84;
        break;
    }
    return out;
}

// @ 0x00a775a0
float* MapInfo::EvalVec4(float* out, int id)
{
    float a[3], b[3], c[3];
    if (mp70) {
        float tmp[3];
        float* r = (float*)mp70->EvalVec4(tmp, id);
        a[0] = r[0]; a[1] = r[1]; a[2] = r[2];
    } else {
        a[0] = m40; a[1] = m44; a[2] = m48;
    }
    if (mp74) {
        float tmp[3];
        float* r = (float*)mp74->EvalVec4(tmp, id);
        b[0] = r[0]; b[1] = r[1]; b[2] = r[2];
    } else {
        b[0] = m50; b[1] = m54; b[2] = m58;
    }
    if (mp78) {
        float tmp[3];
        float* r = (float*)mp78->EvalVec4(tmp, id);
        c[0] = r[0]; c[1] = r[1]; c[2] = r[2];
    } else {
        c[0] = m60; c[1] = m64; c[2] = m68;
    }
    switch (m14) {
    case 0:
        out[0] = a[0]; out[1] = a[1]; out[2] = a[2];
        break;
    case 1:
        out[0] = b[0] + a[0]; out[1] = b[1] + a[1]; out[2] = b[2] + a[2];
        break;
    case 2:
        out[0] = b[0] * a[0]; out[1] = b[1] * a[1]; out[2] = b[2] * a[2];
        break;
    case 3:
        out[0] = a[0] - b[0]; out[1] = a[1] - b[1]; out[2] = a[2] - b[2];
        break;
    case 4:
        cMapInfo_SortRect2(out, b, a);
        break;
    case 5:
        Swarm_Min(out, b, a);
        break;
    case 6:
        out[0] = b[0] * a[0] + c[0];
        out[1] = c[1] + b[1] * a[1];
        out[2] = c[2] + b[2] * a[2];
        break;
    default:
        out[0] = g_1676d7c;
        out[1] = g_1676d80;
        out[2] = g_1676d84;
        break;
    }
    return out;
}

// @ 0x00a77830
float* MapInfo::EvalVec4b(float* out, int id)
{
    float a[4], b[4], c[4];
    if (mp70) {
        float tmp[4];
        float* r = (float*)mp70->EvalVec4b(tmp, id);
        a[0] = r[0]; a[1] = r[1]; a[2] = r[2]; a[3] = r[3];
    } else {
        a[0] = m40; a[1] = m44; a[2] = m48; a[3] = m4c;
    }
    if (mp74) {
        float tmp[4];
        float* r = (float*)mp74->EvalVec4b(tmp, id);
        b[0] = r[0]; b[1] = r[1]; b[2] = r[2]; b[3] = r[3];
    } else {
        b[0] = m50; b[1] = m54; b[2] = m58; b[3] = m5c;
    }
    if (mp78) {
        float tmp[4];
        float* r = (float*)mp78->EvalVec4b(tmp, id);
        c[0] = r[0]; c[1] = r[1]; c[2] = r[2]; c[3] = r[3];
    } else {
        c[0] = m60; c[1] = m64; c[2] = m68; c[3] = m6c;
    }
    switch (m14) {
    case 0:
        out[0] = a[0]; out[1] = a[1]; out[2] = a[2]; out[3] = a[3];
        break;
    case 1:
        out[0] = b[0] + a[0]; out[1] = b[1] + a[1]; out[2] = b[2] + a[2]; out[3] = b[3] + a[3];
        break;
    case 2:
        out[0] = b[0] * a[0]; out[1] = b[1] * a[1]; out[2] = b[2] * a[2]; out[3] = b[3] * a[3];
        break;
    case 3:
        out[0] = a[0] - b[0]; out[1] = a[1] - b[1]; out[2] = a[2] - b[2]; out[3] = a[3] - b[3];
        break;
    case 4:
        cMapInfo_SortRect3(out, b, a);
        break;
    case 5:
        cMapInfo_SortRect3R(out, b, a);
        break;
    case 6:
        out[0] = b[0] * a[0] + c[0];
        out[1] = c[1] + b[1] * a[1];
        out[2] = c[2] + b[2] * a[2];
        out[3] = c[3] + b[3] * a[3];
        break;
    default:
        out[0] = g_1676da0;
        out[1] = g_1676da4;
        out[2] = g_1676da8;
        out[3] = g_1676dac;
        break;
    }
    return out;
}

// @ 0x00a77bd0
void __stdcall MapInfo_DefaultRect44(float* out)
{
    float v[6];
    v[0] = -4.0f;
    v[2] = -4.0f;
    v[1] = 4.0f;
    v[3] = 4.0f;
    v[4] = 0.0f;
    v[5] = 0.0f;

    out[0] = v[0];
    out[1] = v[1];
    out[2] = v[2];
    out[3] = v[3];
    out[4] = v[4];
    out[5] = v[5];
}

// @ 0x00a77c40
bool __stdcall MapInfo_TileContains(float* p)
{
    return 0.0f <= p[0] && p[0] < g_13eeda0 && 0.0f <= p[1] && p[1] < g_13eeda0;
}

// @ 0x00a77c80
float __stdcall WaveSum(const float* v)
{
    float a = sinf(v[0] * kRadScale);
    float b = sinf(kRadScale * v[1] * 0.5f);
    return (b + 1.0f) * 0.1f + (a + 1.0f) * 0.3f;
}

// @ 0x00a77cc0
float* __stdcall InvLengthSqScale(float* out, const float* v)
{
    float s = 1.0f / (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    out[0] = v[0] * s;
    out[1] = v[1] * s;
    out[2] = v[2] * s;
    return out;
}

// @ 0x00a77d30
void __stdcall WaveVec4(float* out, const float* v)
{
    float a = v[0] * kRadScale;
    float b = kRadScale * v[1] * 0.5f;
    out[2] = 1.0f;
    float x = (sinf(a) + 1.0f) * 0.3f + (sinf(b) + 1.0f) * 0.1f;
    float y = (cosf(b) + 1.0f) * 0.1f + (cosf(a) + 1.0f) * 0.3f;
    out[0] = x;
    out[1] = y;
    out[3] = y * x;
}

// @ 0x00a77da0
void __stdcall WaveNormal(float* out, const float* v)
{
    float x = cosf(v[0] * kRadScale) * kRadScale * -0.3f;
    float y = cosf(kRadScale * v[1] * 0.5f) * kRadScale * -0.05f;
    float inv = 1.0f / sqrtf(x * x + y * y + 1.0f);
    out[0] = x * inv;
    out[1] = y * inv;
    out[2] = inv;
}

// @ 0x00a780f0
MapInfoHolder::MapInfoHolder()
{}

// @ 0x00a78560
void InitMapInfoTable()
{
    g_MapInfoFns[0] = (void*)&Add;
    g_MapInfoFns[1] = (void*)&AddFunc;
    g_MapInfoFns[2] = (void*)&ReadFunc;
    g_MapInfoFns[5] = 0;
    g_MapInfoFns[6] = 0;
}

// @ 0x00a78590
MapDescription::MapDescription()
{
    mField4 = 0;
    mFlags = 0; mKind = 0;
    mI18 = -1; mI1c = -1;
    mV20[0] = -1.0f; mV20[1] = -1.0f; mV20[2] = 1.0f; mV20[3] = 1.0f;
    mType30 = 4;
    mFlag31 = 0;
}

// @ 0x00a785e0
void AddMapDescription(MapDescription* d, IContext* ctx)
{
    IEntries* e = (IEntries*)ctx->GetSink();
    e->Add(d->mA8, d->mAC, d);
}

// @ 0x00a78610
void ReadMaterialParam(IStream* s, MaterialParam* o)
{
    ReadUInt64(s, o, 1, 0);
    ReadBytes(s, &o->mType, 1);
    switch (o->mType) {
    case 0:
    case 1:
        ReadInt32(s, &o->mValue.i, 1, 0);
        return;
    case 2:
        ReadBytes(s, &o->mValue.b, 1);
        return;
    case 3: {
        int16_t n;
        ReadUInt16(s, &n, 1, 0);
        o->mCount = n;
        o->mValue.p = new("Swarm/MaterialParams", 0, 0, 0, 0) int32_t[n];
        for (int i = 0; i < n; ++i)
            ReadInt32(s, (int32_t*)o->mValue.p + i, 1, 0);
        return; }
    case 4: {
        int16_t n;
        ReadUInt16(s, &n, 1, 0);
        o->mCount = n;
        o->mValue.p = new("Swarm/MaterialParams", 0, 0, 0, 0) int32_t[n];
        for (int i = 0; i < n; ++i)
            ReadInt32(s, (int32_t*)o->mValue.p + i, 1, 0);
        return; }
    case 5: {
        int16_t n;
        ReadUInt16(s, &n, 1, 0);
        o->mCount = n;
        o->mValue.p = new("Swarm/MaterialParams", 0, 0, 0, 0) char[n];
        for (int i = 0; i < n; ++i)
            ReadBytes(s, (char*)o->mValue.p + i, 1);
        return; }
    case 6:
        ReadUInt64(s, &o->mValue, 1, 0);
        return;
    }
}

// @ 0x00a787f0
void ParamVec::insert(MaterialParam* position, uint32_t n, const MaterialParam& value)
{
    if (n > (uint32_t)(mpCapacity - mpEnd)) {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        uint32_t nGrowSize = nPrevSize ? nPrevSize * 2 : 1;
        uint32_t nNewSize = nPrevSize + n;
        if (nGrowSize > nNewSize) nNewSize = nGrowSize;
        MaterialParam* pNewData = 0;
        if (nNewSize)
            pNewData = (MaterialParam*)operator new(nNewSize * sizeof(MaterialParam), "EASTL", 0, 0, kEastlAllocFile, 0xd1);
        MaterialParam* pNewEnd = UninitCopy(mpBegin, position, pNewData);
        UninitFillN(pNewEnd, n, &value, DefaultCopyTag());
        pNewEnd = UninitCopy(position, mpEnd, pNewEnd + n);
        if (mpBegin && ((int*)mpBegin)[-1]) operator_delete__(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    } else if (n != 0) {
        const MaterialParam temp = value;
        MaterialParam* const pOldEnd = mpEnd;
        const uint32_t nExtra = (uint32_t)(pOldEnd - position);
        if (n < nExtra) {
            GenIter tmp;
            UninitCopyGen(&tmp, pOldEnd - n, pOldEnd, pOldEnd);
            mpEnd += n;
            CopyBackward(position, pOldEnd - n, pOldEnd);
            FillRange(position, position + n, &temp);
        } else {
            UninitFillN(pOldEnd, n - nExtra, &temp);
            mpEnd += n - nExtra;
            GenIter tmp;
            UninitCopyGen(&tmp, position, pOldEnd, mpEnd);
            mpEnd += nExtra;
            FillRange(position, pOldEnd, &temp);
        }
    }
}

// @ 0x00a789e0
void ParamVec::resize(uint32_t n)
{
    MaterialParam* pEnd = mpEnd;
    uint32_t size = (uint32_t)(pEnd - mpBegin);
    if (n > size) {
        MaterialParam v;
        v.mIdLo = 0xffffffff; v.mIdHi = 0xffffffff;
        v.mCount = 0; v.mType = 7; v.mPad13 = 0;
        insert(pEnd, n - size, v);
    } else {
        MaterialParam* newEnd = mpBegin + n;
        CopyPtr(pEnd, pEnd, newEnd);
        mpEnd -= (pEnd - newEnd);
    }
}

// @ 0x00a78a80
void MaterialDescription::Clear()
{
    int count = (int)(mParams.mpEnd - mParams.mpBegin);
    for (int i = 0; i < count; ++i) {
        MaterialParam* p = mParams.mpBegin + i;
        if (p->mCount != 0) operator_delete__(p->mValue.p);
    }
    mIdB[0] = 0xffffffff; mIdB[1] = 0xffffffff;
    mParams.erase(mParams.mpBegin, mParams.mpEnd);
}

// @ 0x00a78b90
MaterialDescription* ReadMaterialDescription(IStream* s)
{
    MaterialDescription* d = new("Swarm/MaterialDescription", 0, 0, 0, 0) MaterialDescription();
    ReadUInt64(s, &d->mIdA, 1, 0);
    ReadUInt64(s, &d->mIdB, 1, 0);
    ReadParams(s, &d->mParams);
    return d;
}

// @ 0x00a78c10
void InitMaterialTable()
{
    g_MaterialFns[0] = (void*)&AddMapDescription;
    g_MaterialFns[1] = (void*)&SetSerializer;
    g_MaterialFns[2] = (void*)&ReadMaterialDescription;
    g_MaterialFns[5] = 0;
    g_MaterialFns[6] = 0;
}

// @ 0x00a78c40
MaterialDescription::~MaterialDescription()
{
    Clear();
}

// @ 0x00a78c80
float FastSine(float x)
{
    float t = kSineScale * x + 12582912.0f;
    uint32_t bits = *(uint32_t*)&t;
    uint32_t idx = (bits & 0xf) * 2;
    int k = (int)(bits - 0x4b400000);
    float r = x - (float)k * kSineStep;
    float a = kSineTable[idx], b = kSineTable[idx + 1];
    return a + (b - a * r * 0.5f) * r;
}

// @ 0x00a78ce0
__declspec(noinline) void FastSinCos(float angle, float* outSin, float* outCos)
{
    float scaled = g_SinFreq * angle + 12582912.0f;
    unsigned idx = *(unsigned*)&scaled & 0xf;
    int ip = *(int*)&scaled + (int)0xB4C00000u;
    float frac = angle - (float)ip * g_SinPeriod;
    float* e = &g_SinTable[idx * 2];
    float& a = e[0];
    float& b = e[1];
    *outSin = (b - (a * frac) * 0.5f) * frac + a;
    *outCos = b - ((b * frac) * 0.5f + a) * frac;
}

// @ 0x00a78d90
__declspec(noinline) long double FastAtan2(float y, float x)
{
    float ay = (float)fabs(y) + 1e-10f;
    float ax = (float)fabs(x);
    float t = (ay - ax) / (ax + ay);
    float r = (0.9817f - (t * t) * 0.1963f) * t;
    if (x < 0.0f)
        r = g_HalfPi * g_Three - r;
    else
        r = g_HalfPi + r;
    if (y < 0.0f)
        r = -r;
    return r;
}

// @ 0x00a78e30
__declspec(noinline) Rec7* CopyRec7(Rec7* first, Rec7* last, Rec7* dst)
{
    while (first != last) {
        if (dst)
            *dst = *first;
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x00a78e90
void Xform::InverseTransformDir(Vec3* v) const
{
    if (scale != 1.0f) {
        float inv = 1.0f / scale;
        v->x = v->x * inv;
        v->y = inv * v->y;
        v->z = inv * v->z;
    }
    if (flags & 2) {
        float z = v->z;
        float y = v->y;
        float x = v->x;
        Vec3 t;
        t.x = (m[1] * y + m[2] * z) + m[0] * x;
        t.y = (m[4] * y + m[5] * z) + m[3] * x;
        t.z = (m[7] * y + m[8] * z) + m[6] * x;
        *v = t;
    }
}

// @ 0x00a78f80
__declspec(noinline) double RandomSymmetric(float range)
{
    double lo = -(double)range;
    double hi = (double)range;
    double v = g_Random.RandomDoubleUniform() * (hi - lo) + lo;
    return Clamp(v, lo, hi);
}

// @ 0x00a78fd0
__declspec(noinline) void SphericalDir(const Vec3* v, float* outYaw, float* outPitch)
{
    float x = v->x;
    float y = v->y;
    float d = x * x + y * y;
    if (d < 1e-6f) {
        float half = 1.5707964f;
        *outYaw = 0.0f;
        if (v->z < 0.0f)
            *outPitch = -half;
        else
            *outPitch = half;
        return;
    }
    *outYaw = (float)FastAtan2(y, x);
    *outPitch = (float)asin((double)v->z / sqrt((double)d + (double)v->z * (double)v->z));
}

// @ 0x00a790a0
void cRWState::Update(const KeyDesc* d)
{
    {
        double lo = d->aLo;
        double hi = d->aHi;
        float v = (float)Clamp(g_Random.RandomDoubleUniform() * (hi - lo) + lo, lo, hi);
        f0 = f0 + v;
    }
    {
        double lo = d->bLo;
        double hi = d->bHi;
        float v = (float)Clamp(g_Random.RandomDoubleUniform() * (hi - lo) + lo, lo, hi);
        if (d->weight < 0.5f) {
            b = v;
            a = d->weight * v * 2.0f;
        } else {
            b = (1.0f - d->weight) * v * 2.0f;
            a = v;
        }
    }
    if (d->weight < 1.0f) {
        float r = (float)RandomSymmetric(d->jitter + 1e-5f);
        float w = g_TwoPi;
        phase = w * r + phase;
        float sp = d->spread * w;
        if (r >= 0.0f)
            phase = sp + phase;
        else
            phase = phase - sp;
    }
    if (d->weight > 0.0f) {
        float r = (float)RandomSymmetric(d->jitter + 1e-5f);
        float w = g_TwoPi;
        pitch = w * r + pitch;
        float sp = d->spread * w;
        if (r >= 0.0f)
            pitch = sp + pitch;
        else
            pitch = pitch - sp;
    }
    if (d->keysBegin != d->keysEnd) {
        int n = (int)(d->keysEnd - d->keysBegin);
        unsigned i = frame;
        float w = g_TwoPi;
        if (i < (unsigned)n) {
            phase = d->keysBegin[i] * w + phase;
            if (phase > w)
                phase = phase - w;
            if (phase < -w)
                phase = phase + w;
            frame = ++i;
            if (i >= (unsigned)n) {
                if (d->mode == 0) {
                    frame = 0;
                    return;
                }
                if (d->mode == 1)
                    n--;
                frame = n;
            }
        }
    }
}

// @ 0x00a79300
void cRWState::AccumulateForce(Vec3* force)
{
    if (a == 0.0f) {
        if (b == 0.0f)
            return;
        float sn, cs;
        FastSinCos(phase, &sn, &cs);
        force->x = cs * b + force->x;
        force->y = sn * b + force->y;
        return;
    }
    if (b == 0.0f) {
        force->z = FUN_00a78c80(pitch) * a + force->z;
        return;
    }
    float s1, c1, s2, c2;
    FastSinCos(pitch, &s1, &c1);
    FastSinCos(phase, &s2, &c2);
    force->x = (s2 * c1) * b + force->x;
    force->y = (c2 * c1) * b + force->y;
    force->z = s1 * a + force->z;
}

// @ 0x00a79430
void cRWState::Init(const KeyDesc* d, const Vec3* dir, bool instant)
{
    SphericalDir(dir, &phase, &pitch);
    frame = 0;
    if (!instant) {
        f0 = 0.0f;
        Update(d);
    } else {
        f0 = (float)cConfigManagerUnnamedB90((float*)d);
        float v = (float)cConfigManagerUnnamedB90((float*)((const char*)d + 8));
        if (d->weight < 0.5f) {
            b = v;
            a = d->weight * v * 2.0f;
        } else {
            b = (1.0f - d->weight) * v * 2.0f;
            a = v;
        }
    }
}

// @ 0x00a79500
bool ApplyDirectedImpulse(const ImpulseTable* tbl, const Vec3* dir, float magnitude, Vec3* force)
{
    float x = dir->x;
    float y = dir->y;
    float z = dir->z;
    float len2 = (z * z + y * y) + x * x;
    if (0.0f < len2) {
        float len = (float)sqrt((double)len2);
        if (len < tbl->threshold)
            return false;
        float inv = 1.0f / len;
        float t = len / tbl->speed;
        float u = t > 1.0f ? 1.0f : t;
        int n = (int)(tbl->end - tbl->begin) - 1;
        float s;
        if (n == 0) {
            s = tbl->begin[0];
        } else {
            float f = (float)(unsigned)n * u;
            int i = (int)f;
            float fr = f - (float)i;
            if (fr <= 0.0f)
                s = tbl->begin[i];
            else
                s = (tbl->begin[i + 1] - tbl->begin[i]) * fr + tbl->begin[i];
        }
        float nx = inv * x;
        float ny = y * inv;
        float nz = z * inv;
        float m = s * magnitude;
        force->x = nx * m + force->x;
        force->y = ny * m + force->y;
        force->z = nz * m + force->z;
    }
    return true;
}

// @ 0x00a79660
bool ReadState(State* dst, const KeyList* src)
{
    if (src->begin == src->end)
        return false;
    if (src->begin->f[6] != 0.0f)
        return false;
    dst->a = *(Vec3*)&src->begin->f[0];
    dst->b = *(Vec3*)&src->begin->f[3];
    float last = src->end[-1].f[6];
    if (0.0f < last)
        dst->g = last;
    return true;
}

// @ 0x00a796d0
void ReadRec(IStream_s00a7_8ce0* s, KeyRec* r)
{
    ReadInt32(s, (int*)&r->f0, 1, 0);
    s->Read(&r->a, 0xc);
    s->Read(&r->b, 0xc);
}

// @ 0x00a79710
void WriteRec(IStream_s00a7_8ce0* s, KeyRec* r)
{
    WriteFloat32(s, r->f0);
    s->Write(&r->a, 0xc);
    s->Write(&r->b, 0xc);
}

// @ 0x00a79760
void ReadRecB(IStream_s00a7_8ce0* s, KeyRecB* r)
{
    s->Read(&r->a, 0xc);
    s->Read(&r->b, 0xc);
    ReadInt32(s, (int*)&r->c, 1, 0);
}

// @ 0x00a797a0
void WriteRecB(IStream_s00a7_8ce0* s, KeyRecB* r)
{
    s->Write(&r->a, 0xc);
    s->Write(&r->b, 0xc);
    WriteFloat32(s, r->c);
}

// @ 0x00a7b9a0
void ReadRecordA(IStream* s, uint8_t* o)
{
    s->Read(o, 8);
    s->Read(o + 8, 8);
    ReadInt32(s, o + 0x10, 1, 0);
    ReadInt32(s, o + 0x14, 1, 0);
    ReadInt32(s, o + 0x18, 1, 0);
    ReadIntVector(s, o + 0x1c);
    ReadBytes(s, o + 0x30, 1);
}

// @ 0x00a7ba10
void ReadRecordB(IStream* s, uint8_t* o)
{
    ReadIntVector(s, o);
    ReadInt32(s, o + 0x14, 1, 0);
    ReadInt32(s, o + 0x18, 1, 0);
}

// @ 0x00a7ba60
int __stdcall QueryTypeId(uint32_t* out, unsigned n)
{
    if (out) {
        if (n >= 1) {
            *out = 0xea5118b0;
        } else return 0;
    }
    return 1;
}

// @ 0x00a7ba90
long RcObj::Release()
{
    long n = _InterlockedDecrement(&mRef);
    if (n == 0) {
        _InterlockedExchange(&mRef, 1);
        delete this;
    }
    return n;
}

// @ 0x00a7bac0
bool __stdcall ForwardOp12(ISource* src, Forwarder* fw, int unused, uint32_t tag)
{
    bool r = false;
    void* item = src->GetItem();
    if (tag == 0xea5118b0)
        r = fw->mpTarget->Op12(item);
    return r;
}

// @ 0x00a7bb00
bool __stdcall ForwardOp13(Forwarder* fw, ISource* src, int unused, uint32_t tag)
{
    bool r = false;
    void* item = src->GetItem();
    if (tag == 0xea5118b0)
        r = fw->mpTarget->Op13(item);
    return r;
}

// @ 0x00a7bb80
RecordReadObj::RecordReadObj()
{}

// @ 0x00a7bba0
bool Loader::Load(IVec3Source* a, CollectionResource** out, int arg, uint32_t tag)
{
    if (tag == 0xea5118b0) {
        CollectionResource* obj = new("Swarm/CollectionResource", 0, 0, 0, 0) CollectionResource();
        IRefA* res = GetDefaultResource();
        IRefA* old = obj->mpRes;
        if (res != old) {
            if (res) res->AddRef();
            obj->mpRes = res;
            if (old) old->Release();
        }
        if (obj) {
            obj->AddRef();
            if (creator()->Create(a, obj, arg, 0xea5118b0)) {
                *out = obj;
                obj->AddRef();
                const uint32_t* v = a->GetVec();
                (*out)->mVec[0] = v[0];
                (*out)->mVec[1] = v[1];
                (*out)->mVec[2] = v[2];
                obj->Release();
                return true;
            }
            obj->Release();
        }
    }
    return false;
}

// @ 0x00a7bca0
int GetResourceField(int param)
{
    IFactory* f = GetFactory();
    if (f) {
        QueryDesc q;
        q.mParam = param;
        q.mTagA = 0xea5118b0;
        q.mTagB = 0xea5118b1;
        ResultObj* res = 0;
        if (f->Create(&q, (CollectionResource**)&res, 0, 0, 0, 0)) {
            int r = res->mField14;
            res->Release();
            return r;
        }
        if (res) res->Release();
    }
    return 0;
}

// @ 0x00a7bd20
HNode<IRefT1>* __stdcall AllocNode1(const HPair<IRefT1>* src)
{
    HNode<IRefT1>* p = (HNode<IRefT1>*)operator new(0x18, "EASTL", 0, 0, kEastlAllocFile, 0xd1);
    if (p) {
        p->key.a = src->key.a;
        p->key.b = src->key.b;
        p->value = src->value;
        if (p->value) p->value->AddRef();
    }
    p->next = 0;
    return p;
}

// @ 0x00a7be20
HNode<IRefT2>* __stdcall AllocNode2(const HPair<IRefT2>* src)
{
    HNode<IRefT2>* p = (HNode<IRefT2>*)operator new(0x18, "EASTL", 0, 0, kEastlAllocFile, 0xd1);
    if (p) {
        p->key.a = src->key.a;
        p->key.b = src->key.b;
        p->value = src->value;
        if (p->value) p->value->AddRef();
    }
    p->next = 0;
    return p;
}

// @ 0x00a7bf40
HIter HashMapBase::find(const HKey& k)
{
    uint32_t idx = k.a % mBucketCount;
    HNode<void>** pBucket = mBuckets + idx;
    HIter it;
    it.node = *pBucket;
    it.bucket = (void**)pBucket;
    HNode<void>* n = (HNode<void>*)it.node;
    if (n) {
        do {
            if (k.a == n->key.a && k.b == n->key.b)
                return HIter(it);
            n = n->next;
            it.node = n;
        } while (n);
    }
    it.bucket = (void**)(mBuckets + mBucketCount);
    it.node = *it.bucket;
    return HIter(it);
}

// @ 0x00a7c100
IRefT1** HashMap1::Subscript(const HKey& k)
{
    {
        HIter it = find(k);
        if (it.node != mBuckets[mBucketCount])
            return &((HNode<IRefT1>*)it.node)->value;
    }
    HPair<IRefT1> p;
    p.key = k;
    p.value = 0;
    HInsRes ins = insert(p, HTag());
    IRefT1** r = &((HNode<IRefT1>*)ins.first.node)->value;
    if (p.value) p.value->Release();
    return r;
}

// @ 0x00a7c180
IRefT2** HashMap2::Subscript(const HKey& k)
{
    {
        HIter it = find(k);
        if (it.node != mBuckets[mBucketCount])
            return &((HNode<IRefT2>*)it.node)->value;
    }
    HPair<IRefT2> p;
    p.key = k;
    p.value = 0;
    HInsRes ins = insert(p, HTag());
    IRefT2** r = &((HNode<IRefT2>*)ins.first.node)->value;
    if (p.value) p.value->Release();
    return r;
}

// @ 0x00a7c200
void Registry::Set1(HKey key, IRefT1* val)
{
    IRefT1** slot = mMap1.Subscript(key);
    IRefT1* old = *slot;
    if (val != old) {
        if (val) val->AddRef();
        *slot = val;
        if (old) old->Release();
    }
}

// @ 0x00a7c240
void Registry::Set2(HKey key, IRefT2* val)
{
    IRefT2** slot = mMap2.Subscript(key);
    IRefT2* old = *slot;
    if (val != old) {
        if (val) val->AddRef();
        *slot = val;
        if (old) old->Release();
    }
}

// @ 0x00a7c280
__declspec(noinline) float VanDerCorput(uint32_t v)
{
    uint32_t a = (((v >> 1) ^ (v + v)) & 0x55555555) ^ (v << 1);
    uint32_t b = (((a >> 2) ^ (a * 4)) & 0x33333333) ^ (a << 2);
    v = (((b >> 4) ^ (b << 4)) & 0x0f0f0f0f) ^ (b * 16);
    union { uint32_t u; float f; } r;
    r.u = (((v >> 16) & 0xfe) | (v & 0xff00)) >> 1 | ((v & 0xff) | 0x7f00) << 15;
    return r.f - 1.0f;
}

// @ 0x00a7c300
__declspec(noinline) float RadicalInverse2(int n)
{
    float r = 0.0f;
    float result = 0.0f;
    float f = 0.5f;
    for (; n > 0; n >>= 1) {
        if (n & 1) {
            r = f + r;
            result = r;
        }
        f = f * 0.5f;
    }
    return result;
}

// @ 0x00a7c350
int Halton2::Next()
{
    mIndex = mIndex + 1;
    mX = VanDerCorput(mIndex);
    mDigits3 = mDigits3 + 1;
    uint32_t mask = 3;
    int step = 1;
    float f = 1.0f / 3.0f;
    if ((mDigits3 & 3) == 3) {
        do {
            mDigits3 = mDigits3 + step;
            mY = mY - f * 2.0f;
            mask = mask * 4;
            step = step * 4;
            f = f * (1.0f / 3.0f);
        } while (((uint32_t)mDigits3 & mask) == mask);
    }
    mY = mY + f;
    return mIndex;
}

// @ 0x00a7c3d0
Halton2::Halton2(int index)
{
    mX = RadicalInverse2(index);
    mY = 0.0f;
    mIndex = index;
    mDigits3 = 0;
    float f = 1.0f / 3.0f;
    uint8_t shift = 0;
    for (; index != 0; index /= 3) {
        int digit = index % 3;
        mDigits3 |= digit << shift;
        shift += 2;
        mY = (float)digit * f + mY;
        f = f * (1.0f / 3.0f);
    }
}

// @ 0x00a7c450
int Halton3::Next()
{
    mIndex = mIndex + 1;
    mX = VanDerCorput(mIndex);
    mDigits3 = mDigits3 + 1;
    uint32_t mask = 3;
    int step = 1;
    float f = 1.0f / 3.0f;
    if ((mDigits3 & 3) == 3) {
        do {
            mDigits3 = mDigits3 + step;
            mY = mY - f * 2.0f;
            mask = mask * 4;
            step = step * 4;
            f = f * (1.0f / 3.0f);
        } while (((uint32_t)mDigits3 & mask) == mask);
    }
    mY = mY + f;
    mDigits5 = mDigits5 + 1;
    uint32_t mask5 = 7;
    uint32_t want5 = 5;
    int step5 = 3;
    float f5 = 0.2f;
    if ((mDigits5 & 7) == 5) {
        do {
            mDigits5 = mDigits5 + step5;
            mask5 = mask5 * 8;
            mZ = mZ - f5 * 4.0f;
            want5 = want5 * 8;
            step5 = step5 * 8;
            f5 = f5 * 0.2f;
        } while ((mask5 & (uint32_t)mDigits5) == want5);
    }
    mZ = mZ + f5;
    return mIndex;
}

// @ 0x00a7c540
Halton3::Halton3(int index)
{
    mX = RadicalInverse2(index);
    int n = index;
    mIndex = index;
    mY = 0.0f;
    mDigits3 = 0;
    float f = 1.0f / 3.0f;
    uint8_t shift = 0;
    for (int m = n; m != 0; m /= 3) {
        int digit = m % 3;
        mDigits3 |= digit << shift;
        shift += 2;
        mY = (float)digit * f + mY;
        f = f * (1.0f / 3.0f);
    }
    shift = 0;
    mZ = 0.0f;
    mDigits5 = 0;
    f = 0.2f;
    for (int m = n; m != 0; m /= 5) {
        int digit = m % 5;
        mDigits5 |= digit << shift;
        shift += 3;
        mZ = (float)digit * f + mZ;
        f = f * 0.2f;
    }
}
