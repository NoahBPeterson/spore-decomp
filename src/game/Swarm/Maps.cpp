// src/game/Swarm/Maps.cpp -- migrated from slice(s) s00a76cf0, s00a75dd0, s00a75000, s00a77c80 by tools/migrate/rewrite.py
// Object file: Swarm/Maps.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <intrin.h>
#include <xmmintrin.h>

// ---- items of slice s00a77c80 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t size, const char* pName, int a, int b, const char* file, int line);  // 0xf473a0
void* operator new[](size_t size, const char* pName, int a, int b, const char* file, int line);
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
bool ReadInt32(void* s, void* p, unsigned n, int endian);    // 0x93a780
bool ReadBytes(void* s, void* p, unsigned n);                // 0x93a6c0
struct IRefObj { virtual void AddRef(); virtual void Release(); };   // slots 0 (AddRef), 1 (Release)
struct B4 {                      // second base at +4: vptr + counter
    virtual ~B4() {}
    int mRef;
    B4() { mRef = 0; }
};
struct MapInfoBase : IRefObj, B4 {   // 0xc bytes (Swarm::MapInfo, 0x00a77e00)
    MapInfoBase();
    virtual void Release();
    virtual ~MapInfoBase() {}
};
struct IItem { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
               virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(uint32_t a); };
struct MapInfoMid : IRefObj, B4 {    // 0x40 bytes
    uint32_t mUnk0c[4];
    bool     mB1c;
    int      mI20, mI24;
    float    mF28, mF2c;
    int      mI30;
    bool     mOwnsItem;
    IItem*   mpItem;
    bool     mB3c;
    MapInfoMid() { mB1c = false; mI20 = 0; mI24 = 0; mF28 = 1.0f; mF2c = 1.0f; mI30 = 0;
                   mOwnsItem = false; mpItem = 0; mB3c = false; }
    virtual void Apply();
    // @ 0x00a77f50  (deleting dtor of MapInfoMid)
    virtual ~MapInfoMid() { if (mpItem && mOwnsItem) mpItem->v7(mI30); }
};
struct MapInfoD2 : MapInfoMid {  // 0x44 bytes
    uint32_t x[1];
    MapInfoD2();                                         // 0x00a77fa0
    void Init76070(void*, int, int, bool, void*, bool);  // 0x00a76070
    virtual void Apply(); };
struct MapInfoD3 : MapInfoMid {  // 0x48 bytes
    uint32_t x[2];
    MapInfoD3();                                         // 0x00a78000
    void Init76420(void*, int, int, bool, void*, bool);  // 0x00a76420
    virtual void Apply(); };
struct MapInfoD4 : MapInfoMid {  // 0x48 bytes
    uint32_t x[2];
    MapInfoD4();                                         // 0x00a78050
    void Init769b0(void*, int, int, bool, void*);        // 0x00a769b0
    virtual void Apply(); };
struct MapInfoD5 : MapInfoMid {  // 0x50 bytes
    uint32_t x[4];
    MapInfoD5();                                         // 0x00a780a0
    void Init76b80(void*, int, int, bool, void*);        // 0x00a76b80
    virtual void Apply(); };
struct MapInfoMid2 : MapInfoMid { uint32_t x40; MapInfoMid2() { x40 = 0; } };
struct MapInfoD6 : MapInfoMid2 {  // 0x48 bytes
    uint32_t x44;
    MapInfoD6();                                         // 0x00a781a0
    void Init76070(void*, int, int, bool, void*, bool);  // 0x00a76070
    virtual void Apply(); };
struct MapInfoD0 : MapInfoMid {  // 0x50 bytes; used for kinds 2/3
    uint32_t x[4];
    MapInfoD0();                                         // 0x00a77ef0
    void Init75810(void*, int, int, bool, void*, bool);  // 0x00a75810
    void Init758b0(void*, int, int, bool, void*, int, bool);   // 0x00a758b0
    virtual void Apply(); };
struct MapInfoD7 : MapInfoMid {  // 0x80 bytes
    uint32_t x[0x10];
    MapInfoD7();                                         // 0x00a76cf0 (other slice)
    void Init77b70(int, void*, void*);                   // 0x00a77b70
    void Init75340(int, uint32_t, uint32_t);             // 0x00a75340
    void Init752d0(int, void*);                          // 0x00a752d0
    virtual void Apply(); };
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
struct RefHolder {
    IRefObj* p;
    RefHolder& operator=(IRefObj* o);   // 0x00b5f950 (out of line)
    ~RefHolder() { if (p) p->Release(); }
};
static inline bool BitAt(uint32_t v, int n) { return ((v >> n) & 1) != 0; }
// ---- items of slice s00a77c80 end

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
// ---- items of slice s00a75dd0 end

// ---- items of slice s00a76cf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" extern float g_1676da0;
extern "C" extern float g_1676da4;
extern "C" extern float g_1676da8;
extern "C" extern float g_1676dac;
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
// ---- items of slice s00a76cf0 end

// @ 0x00a752d0
namespace EA { namespace Swarm {
void cMapInfo::SetColor(int idx, const Vec4* c)
{
    uint32_t* dst;
    if (idx == 0) {
        dst = (uint32_t*)((char*)this + 0x40);
        dst[0] = *(const uint32_t*)((const char*)c + 0);
        dst[1] = *(const uint32_t*)((const char*)c + 4);
        dst[2] = *(const uint32_t*)((const char*)c + 8);
        dst[3] = *(const uint32_t*)((const char*)c + 0xc);
        return;
    }
    if (idx == 1) {
        dst = (uint32_t*)((char*)this + 0x50);
        dst[0] = *(const uint32_t*)((const char*)c + 0);
        dst[1] = *(const uint32_t*)((const char*)c + 4);
        dst[2] = *(const uint32_t*)((const char*)c + 8);
        dst[3] = *(const uint32_t*)((const char*)c + 0xc);
        return;
    }
    if (idx == 2) {
        dst = (uint32_t*)((char*)this + 0x60);
        dst[0] = *(const uint32_t*)((const char*)c + 0);
        dst[1] = *(const uint32_t*)((const char*)c + 4);
        dst[2] = *(const uint32_t*)((const char*)c + 8);
        dst[3] = *(const uint32_t*)((const char*)c + 0xc);
    }
}
}}  // namespace EA::Swarm

// @ 0x00a75340
namespace EA { namespace Swarm {
void cMapInfo::SetPoint(int idx, uint32_t a, uint32_t b)
{
    if (idx == 0) {
        *(uint32_t*)((char*)this + 0x28) = a;
        *(uint32_t*)((char*)this + 0x2c) = b;
        return;
    }
    if (idx == 1) {
        *(uint32_t*)((char*)this + 0x30) = a;
        *(uint32_t*)((char*)this + 0x34) = b;
        return;
    }
    if (idx == 2) {
        *(uint32_t*)((char*)this + 0x38) = a;
        *(uint32_t*)((char*)this + 0x3c) = b;
    }
}
}}  // namespace EA::Swarm

// @ 0x00a75810
namespace EA { namespace Swarm {
void cMapInfo::InitA(const float* rect, uint8_t a, void* b, int c, uint8_t d)
{
    mbWrap3c = d;
    mMinX = rect[0];
    mMinY = rect[1];
    mMaxX = rect[2];
    mMaxY = rect[3];
    mbWrap1c = a;
    mpOwner38 = (IcOwner*)b;
    mbValid34 = ((bool (__thiscall*)(void*, int, void*, int))(*(void***)b)[0x14 / 4])(b, 10, 0, 0);
    if (!mbValid34) {
        m20 = 2;
        m24 = 2;
        mpPixels40 = (uint32_t*)0x014575d4;
        mScaleX = 1.0f / (mMaxX - mMinX);
        mScaleY = 1.0f / (mMaxY - mMinY);
    }
}
}}  // namespace EA::Swarm

// @ 0x00a758b0
namespace EA { namespace Swarm {
void cMapInfo::InitB(const float* rect, uint8_t a, void* b, int c, uint8_t d, int e)
{
    mbWrap3c = d;
    mMinX = rect[0];
    mMinY = rect[1];
    mMaxX = rect[2];
    mMaxY = rect[3];
    mbWrap1c = a;
    mpOwner38 = (IcOwner*)b;
    mbValid34 = ((bool (__thiscall*)(void*, int, void*, int))(*(void***)b)[0x14 / 4])(b, 11, 0, 0);
    if (mbValid34) {
        m48 = 2;
        m4c = e;
        return;
    }
    m20 = 2;
    m24 = 2;
    mpPixels40 = (uint32_t*)0x014575d4;
    mScaleX = 1.0f / (mMaxX - mMinX);
    mScaleY = 1.0f / (mMaxY - mMinY);
}
}}  // namespace EA::Swarm

// @ 0x00a76070
namespace EA { namespace Swarm {
void cMapInfo_s00a7_5dd0::Init11(const float* rect, int a2, int a3, uint8_t a4, IcOwner_s00a7_5dd0* owner, uint8_t a6)
{
    mbWrap3c = a6;
    mMinX = rect[0];
    mMinY = rect[1];
    mMaxX = rect[2];
    mMaxY = rect[3];
    mbWrap1c = a4;
    mpOwner38 = owner;
    bool ok = owner->v14(0xb, a2, a3, &mpGrid);
    mbValid34 = ok;
    if (!ok) {
        m20 = 2;
        m24 = 2;
        mpPixels40 = (uint32_t*)0x014575d8;
        mScaleX = 1.0f / (mMaxX - mMinX);
        mScaleY = 1.0f / (mMaxY - mMinY);
    }
}
}}  // namespace EA::Swarm

// @ 0x00a76420
namespace EA { namespace Swarm {
void cMapInfo_s00a7_5dd0::Init9(const float* rect, int a2, int a3, uint8_t a4, IcOwner_s00a7_5dd0* owner, uint8_t a6)
{
    mbWrap3c = a6;
    mMinX = rect[0];
    mMinY = rect[1];
    mMaxX = rect[2];
    mMaxY = rect[3];
    mbWrap1c = a4;
    mpOwner38 = owner;
    bool ok = owner->v14(9, a2, a3, &mpGrid);
    mbValid34 = ok;
    if (!ok) {
        m20 = 2;
        m24 = 2;
        mpPixels40 = (uint32_t*)0x014575d4;
        mScaleX = 1.0f / (mMaxX - mMinX);
        mScaleY = 1.0f / (mMaxY - mMinY);
    }
}
}}  // namespace EA::Swarm

// @ 0x00a769b0
namespace EA { namespace Swarm {
void cMapInfo_s00a7_5dd0::Init12(const float* rect, int a2, int a3, uint8_t a4, IcOwner_s00a7_5dd0* owner)
{
    float* dst = &mMinX;
    for (int i = 0; i < 4; ++i)
        dst[i] = rect[i];
    mbWrap1c = a4;
    mpOwner38 = owner;
    bool ok = owner->v14(0xc, a2, a3, &mpGrid);
    mbValid34 = ok;
    if (!ok) {
        m20 = 2;
        m24 = 2;
        mpPixels40 = (uint32_t*)0x014575d4;
        mScaleX = 1.0f / (mMaxX - mMinX);
        mScaleY = 1.0f / (mMaxY - mMinY);
    }
}
}}  // namespace EA::Swarm

// @ 0x00a76b80
namespace EA { namespace Swarm {
void cMapInfo_s00a7_5dd0::Init13(const float* rect, int a2, int a3, uint8_t a4, IcOwner_s00a7_5dd0* owner)
{
    float* dst = &mMinX;
    for (int i = 0; i < 4; ++i)
        dst[i] = rect[i];
    mbWrap1c = a4;
    mpOwner38 = owner;
    bool ok = owner->v14(0xd, a2, a3, &mpGrid);
    mbValid34 = ok;
    if (!ok) {
        m20 = 2;
        m24 = 2;
        mpPixels40 = (uint32_t*)0x014575d4;
        mScaleX = 1.0f / (mMaxX - mMinX);
        mScaleY = 1.0f / (mMaxY - mMinY);
    }
}
}}  // namespace EA::Swarm

// @ 0x00a76cf0
MapInfo::MapInfo()
{
    *(void* volatile*)this = 0;      // placeholder for the GmeRefCount vtable
    *(void* volatile*)((char*)this + 4) = 0;   // second store of the same vtable
    m08 = 0;
    m0c = 0;
    m10 = 1;
    m28 = 0xffffffff;
    m2c = 0xffffffff;
    m30 = 0xffffffff;
    m34 = 0xffffffff;
    m38 = 0xffffffff;
    m3c = 0xffffffff;
    m40 = g_1676da0;
    m44 = g_1676da4;
    m48 = g_1676da8;
    m4c = g_1676dac;
    m50 = g_1676da0;
    m54 = g_1676da4;
    m58 = g_1676da8;
    m5c = g_1676dac;
    m60 = g_1676da0;
    m64 = g_1676da4;
    m68 = g_1676da8;
    m6c = g_1676dac;
    mp70 = 0;
    mp74 = 0;
    mp78 = 0;
    mp7c = 0;}

// @ 0x00a77b70
void MapInfo::Set(int kind, float* rect, IPxSource* src)
{
    m14 = kind;
    m18 = rect[0];
    m1c = rect[1];
    m20 = rect[2];
    m24 = rect[3];
    IPxSource* pOld = mp7c;
    if (src != pOld) {
        if (src) src->AddRef();
        mp7c = src;
        if (pOld) pOld->Release();
    }
}

// @ 0x00a77e00
MapInfoBase::MapInfoBase()
{}

// @ 0x00a77e20
void ReadMapDescription(IStream* s, int unused, MapDescription* d)
{
    ReadUInt64(s, &d->mA8, 1, 0);
    int32_t v;
    ReadInt32(s, &v, 1, 0);
    d->mFlags = v & 0x3ff;
    uint8_t b;
    ReadBytes(s, &b, 1);
    d->mKind = b;
    ReadUInt64(s, &d->mI18, 1, 0);
    s->Read(d->mV20, 0x10);
    ReadBytes(s, &d->mType30, 1);
    ReadBytes(s, &d->mFlag31, 1);
    for (int i = 0; i < 4; ++i) ReadUInt64(s, &d->mPairs[i * 2], 1, 0);
    for (int i = 0; i < 4; ++i) s->Read(&d->mVecs[i * 4], 0x10);
}

// @ 0x00a77ef0
MapInfoD0::MapInfoD0()
{ x[0] = 0; x[1] = 0; x[2] = 0; x[3] = 0; }

// @ 0x00a77fa0
MapInfoD2::MapInfoD2()
{ x[0] = 0; }

// @ 0x00a78000
MapInfoD3::MapInfoD3()
{ x[0] = 0; x[1] = 0; }

// @ 0x00a78050
MapInfoD4::MapInfoD4()
{ x[0] = 0; x[1] = 0; }

// @ 0x00a780a0
MapInfoD5::MapInfoD5()
{ x[0] = 0; x[1] = 0; x[2] = 0; x[3] = 0; }

// @ 0x00a781a0
MapInfoD6::MapInfoD6()
{ x44 = 0; }

// @ 0x00a781f0
void Add(MapDescription* d, IContext* ctx)
{
    void* sink = ctx->GetSink();
    RefHolder result;
    result.p = 0;
    switch (d->mKind) {
    case 3:
        if (d->mType30 != 4) {
            MapInfoD0* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD0();
            uint32_t f = d->mFlags;
            o->Init758b0(d->mV20, d->mI18, d->mI1c, BitAt(f, 0), sink, d->mType30, BitAt(f, 1));
            result = o;
        } else {
            MapInfoD2* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD2();
            uint32_t f = d->mFlags;
            o->Init76070(d->mV20, d->mI18, d->mI1c, BitAt(f, 0), sink, BitAt(f, 1));
            result = o;
        }
        break;
    case 4:
    case 5: {
        MapInfoD6* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD6();
        uint32_t f = d->mFlags;
        o->Init76070(d->mV20, d->mI18, d->mI1c, BitAt(f, 0), sink, BitAt(f, 1));
        result = o;
        break; }
    case 2: {
        MapInfoD0* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD0();
        uint32_t f = d->mFlags;
        o->Init75810(d->mV20, d->mI18, d->mI1c, BitAt(f, 0), sink, BitAt(f, 1));
        result = o;
        break; }
    case 1: {
        MapInfoD3* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD3();
        uint32_t f = d->mFlags;
        o->Init76420(d->mV20, d->mI18, d->mI1c, BitAt(f, 0), sink, BitAt(f, 1));
        result = o;
        break; }
    case 6: {
        MapInfoD7* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD7();
        o->Init77b70(d->mFlag31, d->mV20, sink);
        for (int i = 0; i < 4; ++i) {
            uint32_t m = 1u << i;
            if ((unsigned)(i + 2) < 10 && (d->mFlags & _rotl(m, 2)) != 0)
                o->Init75340(i, d->mPairs[i * 2], d->mPairs[i * 2 + 1]);
            else if ((unsigned)(i + 6) < 10 && (d->mFlags & _rotl(m, 6)) != 0)
                o->Init752d0(i, &d->mVecs[i * 4]);
        }
        if (!o) return;
        o->AddRef();
        result.p = o;
        break; }
    case 7: {
        MapInfoD4* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD4();
        o->Init769b0(d->mV20, d->mI18, d->mI1c, BitAt(d->mFlags, 0), sink);
        result = o;
        break; }
    case 8: {
        MapInfoD5* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD5();
        o->Init76b80(d->mV20, d->mI18, d->mI1c, BitAt(d->mFlags, 0), sink);
        result = o;
        break; }

    case 0:
        result = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoBase();
        break;
    default:
        return;
    }
    if (result.p) ctx->AddEntry(d->mA8, d->mAC, result.p);
}
